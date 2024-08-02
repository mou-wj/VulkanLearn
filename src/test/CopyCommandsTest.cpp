#include "CopyCommandsTest.h"
NS_TEST_BEGIN
CopyCommandsTest::CopyCommandsTest()
{
}

void CopyCommandsTest::run()
{
}

CopyCommandsTest::~CopyCommandsTest()
{
}

void CopyCommandsTest::CommandsTest()
{
	//copy commands���� buffer �Լ� image data ����Ϊ��transfer��

	VkCommandBuffer commandBuffer{/*��������һ����Ч��VkCommandBuffer*/ };

	// Copying Data Between Buffers �μ�p1622
	{
		//��buffers�俽������
		VkBuffer srcBuffer{/*��������һ����Ч��VkBuffer*/ };
		VkBuffer dstBuffer{/*��������һ����Ч��VkBuffer*/ };
		VkBufferCopy copyRegion{};
		copyRegion.srcOffset = 0;//ΪsrcBuffer��ʼ�ֽڵ��ֽ�ƫ����
		copyRegion.dstOffset = 0;//ΪdstBuffer��ʼ�ֽڵ��ֽ�ƫ����
		copyRegion.size = 1;//Ҫ�������ֽڴ�С���������0
		vkCmdCopyBuffer(commandBuffer, srcBuffer/*srcBuffer��������source buffer*/, dstBuffer/*dstBuffer��������destination buffer*/,
			1/*regionCount��Ҫ��������������*/, &copyRegion/*pRegions��һ��VkBufferCopy����ָ�룬ָ��Ҫ����������,�������ָ����srcBuffer��dstBuffer���ڴ�����ص�������ص����ڴ��ж�������δ�����*/);
		/*
		vkCmdCopyBuffer��Ч�÷�:
		1.���commandBufferΪunprotected command buffer���Ҳ�֧��protectedNoFault����srcBuffer,dstBuffer����Ϊһ��protected buffer
		2.���commandBufferΪprotected command buffer���Ҳ�֧��protectedNoFault����dstBuffer����Ϊһ��unprotected buffer
		3.pRegions��ÿ��Ԫ�ص�srcOffset����С�ڵ���srcBuffer�Ĵ�С��dstOffset����С�ڵ���dstBuffer�Ĵ�С
		4.pRegions��ÿ��Ԫ�ص�size����С�ڵ���srcBuffer�Ĵ�С��ȥsrcOffset���ұ���С��dstBuffer�Ĵ�С��ȥdstOffset
		5.pRegions��Ԫ��ָ����source region�Ĳ����Լ�destination region�Ĳ����������ڴ������ص�
		6.srcBuffer������VK_BUFFER_USAGE_TRANSFER_SRC_BIT�������������bufferΪnon-sparse�ģ���������Ѿ��󶨵�һ����������������VkDeviceMemory����
		7.dstBuffer������VK_BUFFER_USAGE_TRANSFER_DST_BIT�������������bufferΪnon-sparse�ģ���������Ѿ��󶨵�һ����������������VkDeviceMemory����

		*/



		VkCopyBufferInfo2 copyBufferInfo2{};
		copyBufferInfo2.sType = VK_STRUCTURE_TYPE_COPY_BUFFER_INFO_2;
		copyBufferInfo2.pNext = nullptr;
		copyBufferInfo2.srcBuffer = srcBuffer;//������source buffer
		copyBufferInfo2.dstBuffer = dstBuffer;//������destination buffer
		copyBufferInfo2.regionCount = 1;//Ҫ��������������
		VkBufferCopy2 copyRegion2{};
		{
			copyRegion2.sType = VK_STRUCTURE_TYPE_BUFFER_COPY_2;
			copyRegion2.pNext = nullptr;
			copyRegion2.srcOffset = 0;//ΪsrcBuffer��ʼ�ֽڵ��ֽ�ƫ����
			copyRegion2.dstOffset = 0;//ΪdstBuffer��ʼ�ֽڵ��ֽ�ƫ����
			copyRegion2.size = 1;//Ҫ�������ֽڴ�С���������0
		}
	

		copyBufferInfo2.pRegions = &copyRegion2;//һ��VkBufferCopy2����ָ�룬ָ��Ҫ����������
		/*
		1.pRegions��ÿ��Ԫ�ص�srcOffset����С�ڵ���srcBuffer�Ĵ�С��dstOffset����С�ڵ���dstBuffer�Ĵ�С
		2.pRegions��ÿ��Ԫ�ص�size����С�ڵ���srcBuffer�Ĵ�С��ȥsrcOffset���ұ���С��dstBuffer�Ĵ�С��ȥdstOffset
		3.pRegions��Ԫ��ָ����source region�Ĳ����Լ�destination region�Ĳ����������ڴ������ص�
		4.srcBuffer������VK_BUFFER_USAGE_TRANSFER_SRC_BIT�������������bufferΪnon-sparse�ģ���������Ѿ��󶨵�һ����������������VkDeviceMemory����
		5.dstBuffer������VK_BUFFER_USAGE_TRANSFER_DST_BIT�������������bufferΪnon-sparse�ģ���������Ѿ��󶨵�һ����������������VkDeviceMemory����
		*/



		//buffers�俽�����ȼ���vkCmdCopyBuffer2KHR
		vkCmdCopyBuffer2(commandBuffer, &copyBufferInfo2);//pCopyBufferInfo->pRegions����ָ����srcBuffer��dstBuffer���ڴ�����ص�������ص����ڴ��ж�������δ�����
		/*
		vkCmdCopyBuffer2��Ч�÷�:
		1.���commandBufferΪunprotected command buffer���Ҳ�֧��protectedNoFault����srcBuffer,dstBuffer����Ϊһ��protected buffer
		2.���commandBufferΪprotected command buffer���Ҳ�֧��protectedNoFault����dstBuffer����Ϊһ��unprotected image
		
		*/
	}


	// Copying Data Between Images  �μ�p1629
	{
		//��images����п���
		VkImage srcImage{/*��������һ����Ч��VkImage*/};
		VkImage dstImage{/*��������һ����Ч��VkImage*/};
		VkImageCopy copyImage{};
		copyImage.srcOffset = VkOffset3D{.x = 0,.y = 0,.z = 0};//source image�е�x��y��z�Ļ���texel��ƫ����
		copyImage.srcSubresource = VkImageSubresourceLayers //ָ��source image��subresource�� VkImageSubresourceLayers
			{
			.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT,//�� VkImageAspectFlagBits���ֵλ���룬ָ��Ҫ������color, depth �Լ�/���� stencil aspects
			.mipLevel = 0,//Ҫ������mipmap level
			.baseArrayLayer = 0,//Ҫ�����ĵ�һ��layer
			.layerCount = 1//Ҫ������layer�ĸ��� 
			/*
			VkImageSubresourceLayers��Ч�÷�:
			1.���aspectMask����VK_IMAGE_ASPECT_COLOR_BIT�����䲻�ܰ���VK_IMAGE_ASPECT_DEPTH_BIT����VK_IMAGE_ASPECT_STENCIL_BIT�е�һ��
			2.aspectMask���ܰ���VK_IMAGE_ASPECT_METADATA_BIT�����ܶ�index i����VK_IMAGE_ASPECT_MEMORY_PLANE_i_BIT_EXT
			3.���maintenance5����û�п�������layerCount ����ΪVK_REMAINING_ARRAY_LAYERS
			4.���layerCount ��ΪVK_REMAINING_ARRAY_LAYERS����layerCount�������0
			*/
			};

		copyImage.dstOffset = VkOffset3D{ .x = 0,.y = 0,.z = 0 };//destination image�е�x��y��z�Ļ���texel��ƫ����
		copyImage.srcSubresource = VkImageSubresourceLayers //ָ��destination image��subresource�� VkImageSubresourceLayers
			{
			.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT,
			.mipLevel = 0,
			.baseArrayLayer = 0,
			.layerCount = 1
			};
		copyImage.extent = VkExtent3D{.width =  1,.height = 1,.depth = 1 };//��Ҫ������image ����texel��width, height �Լ� depth.
		/*
		VkImageCopy��Ч�÷�:
		1.���VK_KHR_sampler_ycbcr_conversion ��չû�п�������VkPhysicalDeviceProperties::apiVersionС��Vulkan 1.1,��srcSubresource �Լ� dstSubresource��aspectMask��layerCount����ƥ��
		2.extent.width��extent.height��extent.depth ����Ϊ0
		*/



		vkCmdCopyImage(commandBuffer, srcImage/*srcImage,������source image*/, VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL/*srcImageLayout����ǰsrcImage��subresource��layout*/,
			dstImage/*dstImage,������destination image*/, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL/*dstImageLayout����ǰdstImage��subresource��layout*/, 
			1/*regionCount,Ҫ��������������*/, &copyImage/*pRegions��һ�� VkImageCopy����ָ�룬ָ��Ҫ����������*/);//�������ָ����srcBuffer��dstBuffer���ڴ�����ص�������ص����ڴ��ж�������δ�����,������Ϣ��p1629
		/*
		vkCmdCopyImage��Ч�÷�:
		1.���commandBufferΪunprotected command buffer���Ҳ�֧��protectedNoFault����srcImage,dstImage����Ϊһ��protected image
		2.���commandBufferΪprotected command buffer���Ҳ�֧��protectedNoFault����dstImage����Ϊһ��unprotected image
		3.pRegions��Ԫ��ָ����source region�Ĳ����Լ�destination region�Ĳ����������ڴ������ص�
		4.srcImage��format features�������VK_FORMAT_FEATURE_TRANSFER_SRC_BIT
		5.srcImageLayout����ָ�����������ִ����VkDevice��ʱpRegions��srcImage��subresources��layout
		6.srcImageLayout����ΪVK_IMAGE_LAYOUT_SHARED_PRESENT_KHR, VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL, ���� VK_IMAGE_LAYOUT_GENERAL
		7.���srcImage��dstImage��ͬ����pRegions���κ�Ԫ�ذ���mipLevelƥ����array layers�ص���srcSubresource �� dstSubresource����srcImageLayout �� dstImageLayout ����Ϊ VK_IMAGE_LAYOUT_GENERAL ���� VK_IMAGE_LAYOUT_SHARED_PRESENT_KHR
		8.dstImage��format features�������VK_FORMAT_FEATURE_TRANSFER_DST_BIT
		9.dstImageLayout����ָ�����������ִ����VkDevice��ʱpRegions��dstImage��subresources��layout
		10.dstImageLayout����ΪVK_IMAGE_LAYOUT_SHARED_PRESENT_KHR, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, ���� VK_IMAGE_LAYOUT_GENERAL
		11.���srcImage �� dstImage��VkFormat����һ�� multi-planar format����srcImage �� dstImage��VkFormat������size-compatible��С���ݵ�
		12.����ӿ����漰��multi-planar image��һ��plane����image��VkFormat��plane�����Ǽ��ݵģ��μ� the description of compatible planes p4057
		13.���srcImage �� dstImage��VkFormat��һ��compressed image format����formats��������ͬ��texel block extent
		14.srcImage �� dstImage��sample count����ƥ��
		15.pRegions��ÿ��Ԫ�ص�srcOffset��extent��dstOffset��extent�������commandBuffer���ڵ�VkCommandPool�Ķ������image��transfer granularity requirements���μ�VkQueueFamilyProperties
		16.���srcImage��dstImage��������һ��multi-planar image format����pRegions��ÿ��Ԫ�ص�srcSubresource.aspectMask�Լ�dstSubresource.aspectMask����ƥ��
		17.���srcImage����һ��multi-planar image format����pRegions��ÿ��Ԫ�ص�srcSubresource.aspectMask������һ��������Ч��multi-planar aspect mask bit
		18.���dstImage����һ��multi-planar image format����pRegions��ÿ��Ԫ�ص�dstSubresource.aspectMask������һ��������Ч��multi-planar aspect mask bit
		19.���srcImage����һ��multi-planar image format������dstImage������һ��multi-planar image format ��pRegions��ÿ��Ԫ�ص�dstSubresource.aspectMask������VK_IMAGE_ASPECT_COLOR_BIT
		20.���dstImage����һ��multi-planar image format������srcImage������һ��multi-planar image format ��pRegions��ÿ��Ԫ�ص�srcSubresource.aspectMask������VK_IMAGE_ASPECT_COLOR_BIT
		21.���VK_KHR_maintenance1 ��չû�п���������VkPhysicalDeviceProperties::apiVersionС��Vulkan 1.1����srcImage����dstImage֮һ������ΪVK_IMAGE_TYPE_3D����pRegions��ÿ��Ԫ�أ�srcSubresource.baseArrayLayer�Լ�dstSubresource.baseArrayLayer����Ϊ0��srcSubresource.layerCount��dstSubresource.layerCount����Ϊ1
		22.���srcImage����ΪVK_IMAGE_TYPE_3D����pRegions��ÿ��Ԫ�أ�srcSubresource.baseArrayLayer����Ϊ0����srcSubresource.layerCount����Ϊ1
		23.���dstImage����ΪVK_IMAGE_TYPE_3D����pRegions��ÿ��Ԫ�أ�dstSubresource.baseArrayLayer����Ϊ0����dstSubresource.layerCount����Ϊ1
		24.pRegions��ÿ��Ԫ�أ�srcSubresource.aspectMask����ָ��srcImage�е�aspects��dstSubresource.aspectMask����ָ��dstImage�е�aspects
		25.pRegions��ÿ��Ԫ�أ�srcOffset.x�Լ�(extent.width + srcOffset.x) ����ͬʱ���ڵ���0����С�ڵ���ָ����srcImage��srcSubresource�е�width,  srcOffset.y�Լ�(extent.height + srcOffset.y) ����ͬʱ���ڵ���0����С�ڵ���ָ����srcImage��srcSubresource�е�height
		26.���srcImage����ΪVK_IMAGE_TYPE_1D����pRegions�е�ÿ��Ԫ�أ�srcOffset.y����Ϊ0����extent.height����Ϊ1��srcOffset.z����Ϊ0����extent.depth����Ϊ1
		27.���srcImage����ΪVK_IMAGE_TYPE_3D����pRegions�е�ÿ��Ԫ�أ�srcOffset.z�Լ�(extent.depth + srcOffset.z) ����ͬʱ���ڵ���0��С�ڵ���ָ����srcImage��srcSubresource�е�depth
		28.���dstImage����ΪVK_IMAGE_TYPE_1D����pRegions�е�ÿ��Ԫ�أ�dstOffset.z����Ϊ0����extent.depth����Ϊ1
		29.���srcImage����ΪVK_IMAGE_TYPE_2D����pRegions�е�ÿ��Ԫ�أ�srcOffset.z����Ϊ0
		30.���dstImage����ΪVK_IMAGE_TYPE_2D����pRegions�е�ÿ��Ԫ�أ�dstOffset.z����Ϊ0
		31.���VK_KHR_maintenance1 ��չû�п�������VkPhysicalDeviceProperties::apiVersionС��Vulkan 1.1����1��srcImage��dstImage��������ͬ������
																									       ��2����� srcImage ���� dstImage����ΪVK_IMAGE_TYPE_2D����pRegions��ÿ��Ԫ�أ�extent.depth����Ϊ1
		32.���srcImage��dstImage�����Ͳ�ͬ����maintenance5û�п���������һ�����ͱ���ΪVK_IMAGE_TYPE_3D��������һ�����ͱ���ΪVK_IMAGE_TYPE_2D
		33.���srcImage��dstImage��������ͬ����1����pRegions��ÿ��Ԫ�أ����srcSubresource��dstSubresource��layerCount������VK_REMAINING_ARRAY_LAYERS����srcSubresource ���� dstSubresource��layerCount����ƥ��
											  ��2����pRegions��ÿ��Ԫ�أ����srcSubresource����dstSubresource����һ����layerCountΪVK_REMAINING_ARRAY_LAYERS��������һ����layerCount����ΪVK_REMAINING_ARRAY_LAYERS���ߵ��ڴ�����imageʱ��VkImageCreateInfo��arrayLayers��ȥbaseArrayLayer
		34.���srcImage��dstImage�����Ͷ�ΪVK_IMAGE_TYPE_2D����pRegions��ÿ��Ԫ�أ�extent.depth����Ϊ1
		35.���srcImage����ΪVK_IMAGE_TYPE_2D����dstImage����ΪVK_IMAGE_TYPE_3D����pRegions�е�ÿ��Ԫ�أ�extent.depth�������srcSubresource.layerCount
		36.���dstImage����ΪVK_IMAGE_TYPE_2D����srcImage����ΪVK_IMAGE_TYPE_3D����pRegions�е�ÿ��Ԫ�أ�extent.depth�������dstSubresource.layerCount
		37.����pRegions��ÿ��Ԫ�أ�dstOffset.x�Լ�(extent.width + dstOffset.x)����ͬʱ���ڵ���0��С�ڵ���dstImageָ����subresource��width,  dstOffset.y�Լ�(extent.height + dstOffset.y)����ͬʱ���ڵ���0��С�ڵ���dstImageָ����subresource��height
		38.���dstImage����ΪVK_IMAGE_TYPE_1D�����pRegions��ÿ��Ԫ�أ�dstOffset.y�������0��extent.height����Ϊ1
		39.���dstImage����ΪVK_IMAGE_TYPE_3D�����pRegions��ÿ��Ԫ�أ�dstOffset.z��(extent.depth + dstOffset.z)����ͬʱ���ڵ���0��С�ڵ���dstImageָ����subresource��depth
		40.��pRegions��ÿ��Ԫ�أ�srcOffset.x����ΪsrcImage��VkFormat�� texel block extent width�ı�����  srcOffset.y����ΪsrcImage��VkFormat�� texel block extent height�ı���,srcOffset.z����ΪsrcImage��VkFormat�� texel block extent depth�ı���
		41.��pRegions��ÿ��Ԫ�أ�dstOffset.x����ΪdstImage��VkFormat�� texel block extent width�ı�����  dstOffset.y����ΪdstImage��VkFormat�� texel block extent height�ı���,dstOffset.z����ΪdstImage��VkFormat�� texel block extent depth�ı���
		42.��pRegions��ÿ��Ԫ�أ���1�����srcOffset.x + extent.width������srcSubresourceָ����subresource��width����extent.width����ΪsrcImage��VkFormat�� texel block extent width�ı�����
								   ��2�����srcOffset.y + extent.height������srcSubresourceָ����subresource��height����extent.height����ΪsrcImage��VkFormat�� texel block extent height�ı�����
								   ��3�����srcOffset.z + extent.depth������srcSubresourceָ����subresource��depth����extent.depth����ΪsrcImage��VkFormat�� texel block extent depth�ı���
		43.��pRegions��ÿ��Ԫ�أ���1�����dstOffset.x + extent.width������dstSubresourceָ����subresource��width����extent.width����ΪdstImage��VkFormat�� texel block extent width�ı�����
								   ��2�����dstOffset.y + extent.height������dstSubresourceָ����subresource��height����extent.height����ΪdstImage��VkFormat�� texel block extent height�ı�����
								   ��3�����dstOffset.z + extent.depth������dstSubresourceָ����subresource��depth����extent.depth����ΪdstImage��VkFormat�� texel block extent depth�ı���
		44.���pRegions���κ�Ԫ�ص�aspect�����κγ�VK_IMAGE_ASPECT_STENCIL_BIT֮���mask����srcImage����һ��separate stencil usage��������һ����ؽṹ����pNext�У�����VK_IMAGE_USAGE_TRANSFER_SRC_BIT��������ڴ���srcImage��VkImageCreateInfo::usage��
		45.���pRegions���κ�Ԫ�ص�aspect�����κγ�VK_IMAGE_ASPECT_STENCIL_BIT֮���mask����dstImage����һ��separate stencil usage��������һ����ؽṹ����pNext�У�����VK_IMAGE_USAGE_TRANSFER_DST_BIT��������ڴ���dstImage��VkImageCreateInfo::usage��
		46.���pRegions���κ�Ԫ�ص�aspect����VK_IMAGE_ASPECT_STENCIL_BIT ��srcImage��һ��separate stencil usage��������һ����ؽṹ����pNext�У�����VK_IMAGE_USAGE_TRANSFER_SRC_BIT��������ڴ���srcImage��VkImageStencilUsageCreateInfo::stencilUsage��
		47.���pRegions���κ�Ԫ�ص�aspect����VK_IMAGE_ASPECT_STENCIL_BIT ��dstImage��һ��separate stencil usage��������һ����ؽṹ����pNext�У�����VK_IMAGE_USAGE_TRANSFER_DST_BIT��������ڴ���dstImage��VkImageStencilUsageCreateInfo::stencilUsage��
		48.���srcImageΪ non-sparse����image����ָ����disjoint plane�����Ѿ��󶨵������������ĵ�����VkDeviceMemory��
		49.pRegions��ÿ��Ԫ�ص�srcSubresource.mipLevel����С�ڴ���srcImage��VkImageCreateInfoָ����mipLevels
		50.���pRegions��ÿ��Ԫ�ص�srcSubresource.layerCount��ΪVK_REMAINING_ARRAY_LAYERS�����Ԫ�ص�srcSubresource.baseArrayLayer + srcSubresource.layerCount ����С�ڵ��ڴ���srcImage��VkImageCreateInfoָ����arrayLayers
		51.srcImage������VK_IMAGE_CREATE_SUBSAMPLED_BIT_EXT����
		52.���dstImageΪ non-sparse����image����ָ����disjoint plane�����Ѿ��󶨵������������ĵ�����VkDeviceMemory��
		53.pRegions��ÿ��Ԫ�ص�dstSubresource.mipLevel����С�ڴ���dstImage��VkImageCreateInfoָ����mipLevels
		54.���pRegions��ÿ��Ԫ�ص�dstSubresource.layerCount��ΪVK_REMAINING_ARRAY_LAYERS�����Ԫ�ص�dstSubresource.baseArrayLayer + dstSubresource.layerCount ����С�ڵ��ڴ���dstImage��VkImageCreateInfoָ����arrayLayers
		55.dstImage������VK_IMAGE_CREATE_SUBSAMPLED_BIT_EXT����
		*/

		VkCopyImageInfo2 copyImageInfo2{};
		copyImageInfo2.sType = VK_STRUCTURE_TYPE_COPY_IMAGE_INFO_2;
		copyImageInfo2.pNext = nullptr;
		copyImageInfo2.srcImage = srcImage;//ָ��Ҫ������source image
		copyImageInfo2.srcImageLayout = VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL;//ָ��source image��subresources��layout
		copyImageInfo2.dstImage = dstImage;//ָ��Ҫ������destination image
		copyImageInfo2.dstImageLayout = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;//ָ��destination image��subresources��layout
		copyImageInfo2.regionCount = 1;//ָ��Ҫ����������
		VkImageCopy2 copyImage2{};//�ȼ���VkImageCopy2KHR
		{
			copyImage2.sType = VK_STRUCTURE_TYPE_IMAGE_COPY_2;
			copyImage2.pNext = nullptr;
			copyImage2.srcOffset = VkOffset3D{ .x = 0,.y = 0,.z = 0 };//source image�е�x��y��z�Ļ���texel��ƫ����
			copyImage2.srcSubresource = VkImageSubresourceLayers{/*��������һ����Ч��VkImageSubresourceLayers���μ�ǰ���VkImageSubresourceLayers������*/ };//ָ��source image��subresource�� VkImageSubresourceLayers
			copyImage2.dstOffset = VkOffset3D{ .x = 0,.y = 0,.z = 0 };//destination image�е�x��y��z�Ļ���texel��ƫ����
			copyImage2.dstSubresource = VkImageSubresourceLayers{/*��������һ����Ч��VkImageSubresourceLayers���μ�ǰ���VkImageSubresourceLayers������*/ };//ָ��destination image��subresource�� VkImageSubresourceLayers
			copyImage2.extent = VkExtent3D{ .width = 1,.height = 1,.depth = 1 };//��Ҫ������image ����texel��width, height �Լ� depth.
			/*
			VkImageCopy2��Ч�÷�:
			1.���VK_KHR_sampler_ycbcr_conversion ��չû�п�������VkPhysicalDeviceProperties::apiVersionС��Vulkan 1.1,��srcSubresource �Լ� dstSubresource��aspectMask��layerCount����ƥ��
			2.extent.width��extent.height��extent.depth ����Ϊ0
			*/

		}
		copyImageInfo2.pRegions = &copyImage2;//��һ�� VkImageCopy2 ����ָ��ָ��Ҫ����������
		/*
		VkCopyImageInfo2��Ч�÷�:
		1.pRegions��Ԫ��ָ����source region�Ĳ����Լ�destination region�Ĳ����������ڴ������ص�
		2.srcImage��format features�������VK_FORMAT_FEATURE_TRANSFER_SRC_BIT
		3.srcImageLayout����ָ�����������ִ����VkDevice��ʱpRegions��srcImage��subresources��layout
		4.srcImageLayout����ΪVK_IMAGE_LAYOUT_SHARED_PRESENT_KHR, VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL, ���� VK_IMAGE_LAYOUT_GENERAL
		5.���srcImage��dstImage��ͬ����pRegions���κ�Ԫ�ذ���mipLevelƥ����array layers�ص���srcSubresource �� dstSubresource����srcImageLayout �� dstImageLayout ����Ϊ VK_IMAGE_LAYOUT_GENERAL ���� VK_IMAGE_LAYOUT_SHARED_PRESENT_KHR
		6.dstImage��format features�������VK_FORMAT_FEATURE_TRANSFER_DST_BIT
		7.dstImageLayout����ָ�����������ִ����VkDevice��ʱpRegions��dstImage��subresources��layout
		8.dstImageLayout����ΪVK_IMAGE_LAYOUT_SHARED_PRESENT_KHR, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, ���� VK_IMAGE_LAYOUT_GENERAL
		9.���srcImage �� dstImage��VkFormat����һ�� multi-planar format����srcImage �� dstImage��VkFormat������size-compatible��С���ݵ�
		10.����ӿ����漰��multi-planar image��һ��plane����image��VkFormat��plane�����Ǽ��ݵģ��μ� the description of compatible planes p4057
		12.���srcImage �� dstImage��VkFormat��һ��compressed image format����formats��������ͬ��texel block extent
		13.srcImage �� dstImage��sample count����ƥ��
		14.pRegions��ÿ��Ԫ�ص�srcOffset��extent��dstOffset��extent�������commandBuffer���ڵ�VkCommandPool�Ķ������image��transfer granularity requirements���μ�VkQueueFamilyProperties
		15.���srcImage��dstImage��������һ��multi-planar image format����pRegions��ÿ��Ԫ�ص�srcSubresource.aspectMask�Լ�dstSubresource.aspectMask����ƥ��
		16.���srcImage����һ��multi-planar image format����pRegions��ÿ��Ԫ�ص�srcSubresource.aspectMask������һ��������Ч��multi-planar aspect mask bit
		17.���dstImage����һ��multi-planar image format����pRegions��ÿ��Ԫ�ص�dstSubresource.aspectMask������һ��������Ч��multi-planar aspect mask bit
		18.���srcImage����һ��multi-planar image format������dstImage������һ��multi-planar image format ��pRegions��ÿ��Ԫ�ص�dstSubresource.aspectMask������VK_IMAGE_ASPECT_COLOR_BIT
		19.���dstImage����һ��multi-planar image format������srcImage������һ��multi-planar image format ��pRegions��ÿ��Ԫ�ص�srcSubresource.aspectMask������VK_IMAGE_ASPECT_COLOR_BIT
		20.���VK_KHR_maintenance1 ��չû�п���������VkPhysicalDeviceProperties::apiVersionС��Vulkan 1.1����srcImage����dstImage֮һ������ΪVK_IMAGE_TYPE_3D����pRegions��ÿ��Ԫ�أ�srcSubresource.baseArrayLayer�Լ�dstSubresource.baseArrayLayer����Ϊ0��srcSubresource.layerCount��dstSubresource.layerCount����Ϊ1
		21.���srcImage����ΪVK_IMAGE_TYPE_3D����pRegions��ÿ��Ԫ�أ�srcSubresource.baseArrayLayer����Ϊ0����srcSubresource.layerCount����Ϊ1
		22.���dstImage����ΪVK_IMAGE_TYPE_3D����pRegions��ÿ��Ԫ�أ�dstSubresource.baseArrayLayer����Ϊ0����dstSubresource.layerCount����Ϊ1
		23.pRegions��ÿ��Ԫ�أ�srcSubresource.aspectMask����ָ��srcImage�е�aspects��dstSubresource.aspectMask����ָ��dstImage�е�aspects
		24.pRegions��ÿ��Ԫ�أ�srcOffset.x�Լ�(extent.width + srcOffset.x) ����ͬʱ���ڵ���0����С�ڵ���ָ����srcImage��srcSubresource�е�width,  srcOffset.y�Լ�(extent.height + srcOffset.y) ����ͬʱ���ڵ���0����С�ڵ���ָ����srcImage��srcSubresource�е�height
		25.���srcImage����ΪVK_IMAGE_TYPE_1D����pRegions�е�ÿ��Ԫ�أ�srcOffset.y����Ϊ0����extent.height����Ϊ1��srcOffset.z����Ϊ0����extent.depth����Ϊ1
		26.���srcImage����ΪVK_IMAGE_TYPE_3D����pRegions�е�ÿ��Ԫ�أ�srcOffset.z�Լ�(extent.depth + srcOffset.z) ����ͬʱ���ڵ���0��С�ڵ���ָ����srcImage��srcSubresource�е�depth
		27.���dstImage����ΪVK_IMAGE_TYPE_1D����pRegions�е�ÿ��Ԫ�أ�dstOffset.z����Ϊ0����extent.depth����Ϊ1
		28.���srcImage����ΪVK_IMAGE_TYPE_2D����pRegions�е�ÿ��Ԫ�أ�srcOffset.z����Ϊ0
		29.���dstImage����ΪVK_IMAGE_TYPE_2D����pRegions�е�ÿ��Ԫ�أ�dstOffset.z����Ϊ0
		30.���VK_KHR_maintenance1 ��չû�п�������VkPhysicalDeviceProperties::apiVersionС��Vulkan 1.1����1��srcImage��dstImage��������ͬ������
																										   ��2����� srcImage ���� dstImage����ΪVK_IMAGE_TYPE_2D����pRegions��ÿ��Ԫ�أ�extent.depth����Ϊ1
		31.���srcImage��dstImage�����Ͳ�ͬ����maintenance5û�п���������һ�����ͱ���ΪVK_IMAGE_TYPE_3D��������һ�����ͱ���ΪVK_IMAGE_TYPE_2D
		32.���srcImage��dstImage��������ͬ����1����pRegions��ÿ��Ԫ�أ����srcSubresource��dstSubresource��layerCount������VK_REMAINING_ARRAY_LAYERS����srcSubresource ���� dstSubresource��layerCount����ƥ��
											  ��2����pRegions��ÿ��Ԫ�أ����srcSubresource����dstSubresource����һ����layerCountΪVK_REMAINING_ARRAY_LAYERS��������һ����layerCount����ΪVK_REMAINING_ARRAY_LAYERS���ߵ��ڴ�����imageʱ��VkImageCreateInfo��arrayLayers��ȥbaseArrayLayer
		33.���srcImage��dstImage�����Ͷ�ΪVK_IMAGE_TYPE_2D����pRegions��ÿ��Ԫ�أ�extent.depth����Ϊ1
		34.���srcImage����ΪVK_IMAGE_TYPE_2D����dstImage����ΪVK_IMAGE_TYPE_3D����pRegions�е�ÿ��Ԫ�أ�extent.depth�������srcSubresource.layerCount
		35.���dstImage����ΪVK_IMAGE_TYPE_2D����srcImage����ΪVK_IMAGE_TYPE_3D����pRegions�е�ÿ��Ԫ�أ�extent.depth�������dstSubresource.layerCount
		36.����pRegions��ÿ��Ԫ�أ�dstOffset.x�Լ�(extent.width + dstOffset.x)����ͬʱ���ڵ���0��С�ڵ���dstImageָ����subresource��width,  dstOffset.y�Լ�(extent.height + dstOffset.y)����ͬʱ���ڵ���0��С�ڵ���dstImageָ����subresource��height
		37.���dstImage����ΪVK_IMAGE_TYPE_1D�����pRegions��ÿ��Ԫ�أ�dstOffset.y�������0��extent.height����Ϊ1
		38.���dstImage����ΪVK_IMAGE_TYPE_3D�����pRegions��ÿ��Ԫ�أ�dstOffset.z��(extent.depth + dstOffset.z)����ͬʱ���ڵ���0��С�ڵ���dstImageָ����subresource��depth
		39.��pRegions��ÿ��Ԫ�أ�srcOffset.x����ΪsrcImage��VkFormat�� texel block extent width�ı�����  srcOffset.y����ΪsrcImage��VkFormat�� texel block extent height�ı���,srcOffset.z����ΪsrcImage��VkFormat�� texel block extent depth�ı���
		40.��pRegions��ÿ��Ԫ�أ�dstOffset.x����ΪdstImage��VkFormat�� texel block extent width�ı�����  dstOffset.y����ΪdstImage��VkFormat�� texel block extent height�ı���,dstOffset.z����ΪdstImage��VkFormat�� texel block extent depth�ı���
		41.��pRegions��ÿ��Ԫ�أ���1�����srcOffset.x + extent.width������srcSubresourceָ����subresource��width����extent.width����ΪsrcImage��VkFormat�� texel block extent width�ı�����
								   ��2�����srcOffset.y + extent.height������srcSubresourceָ����subresource��height����extent.height����ΪsrcImage��VkFormat�� texel block extent height�ı�����
								   ��3�����srcOffset.z + extent.depth������srcSubresourceָ����subresource��depth����extent.depth����ΪsrcImage��VkFormat�� texel block extent depth�ı���
		42.��pRegions��ÿ��Ԫ�أ���1�����dstOffset.x + extent.width������dstSubresourceָ����subresource��width����extent.width����ΪdstImage��VkFormat�� texel block extent width�ı�����
								   ��2�����dstOffset.y + extent.height������dstSubresourceָ����subresource��height����extent.height����ΪdstImage��VkFormat�� texel block extent height�ı�����
								   ��3�����dstOffset.z + extent.depth������dstSubresourceָ����subresource��depth����extent.depth����ΪdstImage��VkFormat�� texel block extent depth�ı���
		43.���pRegions���κ�Ԫ�ص�aspect�����κγ�VK_IMAGE_ASPECT_STENCIL_BIT֮���mask����srcImage����һ��separate stencil usage��������һ����ؽṹ����pNext�У�����VK_IMAGE_USAGE_TRANSFER_SRC_BIT��������ڴ���srcImage��VkImageCreateInfo::usage��
		44.���pRegions���κ�Ԫ�ص�aspect�����κγ�VK_IMAGE_ASPECT_STENCIL_BIT֮���mask����dstImage����һ��separate stencil usage��������һ����ؽṹ����pNext�У�����VK_IMAGE_USAGE_TRANSFER_DST_BIT��������ڴ���dstImage��VkImageCreateInfo::usage��
		45.���pRegions���κ�Ԫ�ص�aspect����VK_IMAGE_ASPECT_STENCIL_BIT ��srcImage��һ��separate stencil usage��������һ����ؽṹ����pNext�У�����VK_IMAGE_USAGE_TRANSFER_SRC_BIT��������ڴ���srcImage��VkImageStencilUsageCreateInfo::stencilUsage��
		46.���pRegions���κ�Ԫ�ص�aspect����VK_IMAGE_ASPECT_STENCIL_BIT ��dstImage��һ��separate stencil usage��������һ����ؽṹ����pNext�У�����VK_IMAGE_USAGE_TRANSFER_DST_BIT��������ڴ���dstImage��VkImageStencilUsageCreateInfo::stencilUsage��
		47.���srcImageΪ non-sparse����image����ָ����disjoint plane�����Ѿ��󶨵������������ĵ�����VkDeviceMemory��
		48.pRegions��ÿ��Ԫ�ص�srcSubresource.mipLevel����С�ڴ���srcImage��VkImageCreateInfoָ����mipLevels
		49.���pRegions��ÿ��Ԫ�ص�srcSubresource.layerCount��ΪVK_REMAINING_ARRAY_LAYERS�����Ԫ�ص�srcSubresource.baseArrayLayer + srcSubresource.layerCount ����С�ڵ��ڴ���srcImage��VkImageCreateInfoָ����arrayLayers
		50.srcImage������VK_IMAGE_CREATE_SUBSAMPLED_BIT_EXT����
		51.���dstImageΪ non-sparse����image����ָ����disjoint plane�����Ѿ��󶨵������������ĵ�����VkDeviceMemory��
		52.pRegions��ÿ��Ԫ�ص�dstSubresource.mipLevel����С�ڴ���dstImage��VkImageCreateInfoָ����mipLevels
		53.���pRegions��ÿ��Ԫ�ص�dstSubresource.layerCount��ΪVK_REMAINING_ARRAY_LAYERS�����Ԫ�ص�dstSubresource.baseArrayLayer + dstSubresource.layerCount ����С�ڵ��ڴ���dstImage��VkImageCreateInfoָ����arrayLayers
		54.dstImage������VK_IMAGE_CREATE_SUBSAMPLED_BIT_EXT����

		*/



		//images�俽������ͬ��vkCmdCopyImage2KHR
		vkCmdCopyImage2(commandBuffer, &copyImageInfo2);
		/*
		vkCmdCopyImage2��Ч�÷�:
		1.���commandBufferΪunprotected command buffer���Ҳ�֧��protectedNoFault����srcImage,dstImage����Ϊһ��protected image
		2.���commandBufferΪprotected command buffer���Ҳ�֧��protectedNoFault����dstImage����Ϊһ��unprotected image
		*/

	}




	// Copying Data Between Buffers and Images �μ�p1648
	{
		//��buffer��image֮�俽�����ݣ�������whole texel blocksΪ������λ  �μ�p1649 - p1652

		//����buffer ��image
		{
			VkBuffer srcBuffer{/*��������һ����Ч��VkBuffer*/ };
			VkImage dstImage{/*��������һ����Ч��VkImage*/ };
			VkBufferImageCopy bufferImageCopyRegion{};
			bufferImageCopyRegion.bufferImageHeight = 1;//ָ������texel��������ĸ߶ȣ����Ƶ�ַ���㣬���Ϊ0����imageExtent��ά���ǽ������е�
			bufferImageCopyRegion.bufferOffset = 0;//��buffer�е���ʼ�ֽ�ƫ����
			bufferImageCopyRegion.bufferRowLength = 1;//ָ������texel��������Ŀ�ȣ����Ƶ�ַ���㣬���Ϊ0����imageExtent��ά���ǽ������е�
			bufferImageCopyRegion.imageExtent = VkExtent3D{ .width = 1,.height = 1,.depth = 1 };////ѡ��image��texel�������width��height��depth�Ĵ�С
			bufferImageCopyRegion.imageOffset = VkOffset3D{ .x = 0,.y = 0,.z = 0 };//ѡ��image��texel�������x��y��zƫ��ֵ
			bufferImageCopyRegion.imageSubresource = VkImageSubresourceLayers //ָ��destination image��subresource�� VkImageSubresourceLayers
			{
				.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT,//�� VkImageAspectFlagBits���ֵλ���룬ָ��Ҫ������color, depth �Լ�/���� stencil aspects
				.mipLevel = 0,//Ҫ������mipmap level
				.baseArrayLayer = 0,//Ҫ�����ĵ�һ��layer
				.layerCount = 1//Ҫ������layer�ĸ��� 
			};
			/*
			VkBufferImageCopy��Ч�÷�:
			1.bufferRowLength ����Ϊ0�����ߵ��ڴ��ڵ���imageExtent��width
			2.bufferImageHeight ����Ϊ0�����ߵ��ڴ��ڵ���imageExtent��height
			3.imageSubresource.aspectMaskֻ�ܺ���һ����������
			4.imageExtent.width��imageExtent.height��imageExtent.depth����Ϊ0
			*/



			//����buffer��image  
			vkCmdCopyBufferToImage(commandBuffer, srcBuffer/*srcBuffer,ָ��source VkBuffer*/, dstImage/*dstImage��ָ��destination VkImage*/, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL/*dstImageLayout , destination image ��subresources ��layout*/,
				1/*regionCount��Ҫ������������*/, &bufferImageCopyRegion/*pRegions��һ�� VkBufferImageCopy ����ָ�룬ָ��Ҫ����������*/);
			/*
			vkCmdCopyBufferToImage��Ч�÷�:
			1.���dstImage Ϊnon-sparse�Ļ���ָ����disjoint plane �����Ѿ��󶨵�һ�������������ĵ�����VkDeviceMemory��
			2.pRegions��ÿ��Ԫ�ص�imageSubresource.mipLevel����С�ڴ���dstImage��VkImageCreateInfoָ����mipLevels
			3.���pRegions��ÿ��Ԫ�ص�imageSubresource.layerCount��ΪVK_REMAINING_ARRAY_LAYERS�����Ԫ�ص�imageSubresource.baseArrayLayer + imageSubresource.layerCount ����С�ڵ��ڴ���dstImage��VkImageCreateInfoָ����arrayLayers
			4.dstImage������VK_IMAGE_CREATE_SUBSAMPLED_BIT_EXT����
			5.pRegions��ÿ��Ԫ��ָ����image region���������dstImage��imageSubresourceָ����subresource��Χ��
			6.��pRegions��ÿ��Ԫ�صģ�imageOffset.x�Լ�(imageExtent.width + imageOffset.x)����ͬʱ���ڵ���0��С�ڵ���dstImageָ����imageSubresource��width,  imageOffset.y�Լ�(imageExtent.height + imageExtent.y)����ͬʱ���ڵ���0��С�ڵ���dstImageָ����imageSubresource��height��
						imageOffset.z�Լ�(imageExtent.depth + imageExtent.z)����ͬʱ���ڵ���0��С�ڵ���dstImageָ����imageSubresource��depth
			7.dstImage��sample count ����Ϊ VK_SAMPLE_COUNT_1_BIT
			8.���commandBufferΪunprotected command buffer���Ҳ�֧��protectedNoFault����srcBuffer ������һ��protected buffer,dstImage����Ϊһ��protected image
			9.���commandBufferΪprotected command buffer���Ҳ�֧��protectedNoFault����dstImage����Ϊһ��unprotected image
			10.���commandBuffer���ڵ�VkCommandPool�Ķ����岻֧��VK_QUEUE_GRAPHICS_BIT ����VK_QUEUE_COMPUTE_BIT����pRegions���κ�Ԫ�ص�bufferOffset������4�ı���
			11.pRegions��ÿ��Ԫ�ص�imageOffset��imageExtent�������commandBuffer���ڵ�VkCommandPool�Ķ������image��transfer granularity requirements���μ�VkQueueFamilyProperties
			12.���commandBuffer���ڵ�VkCommandPool�Ķ����岻֧��VK_QUEUE_GRAPHICS_BIT�������pRegions�е�ÿ��Ԫ�أ���imageSubresource.aspectMask����ΪVK_IMAGE_ASPECT_DEPTH_BIT ����VK_IMAGE_ASPECT_STENCIL_BIT
			13.����pRegions��ÿ��Ԫ�أ� srcBuffer�����㹻�����ܹ���  Buffer �� Image Addressing����
			14.pRegions��Ԫ��ָ����source region�Ĳ����Լ�destination region�Ĳ����������ڴ������ص�
			15.srcBuffer������VK_BUFFER_USAGE_TRANSFER_SRC_BIT ����
			16.dstImage��format features�������VK_FORMAT_FEATURE_TRANSFER_DST_BIT
			17.���srcBuffer Ϊnon-sparse����������Ѿ��󶨵�һ�������������ĵ�����VkDeviceMemory��
			18.dstImage������VK_IMAGE_USAGE_TRANSFER_DST_BIT ����
			19.dstImageLayout����ָ�����������ִ����VkDevice��ʱpRegions��dstImage��subresources��layout
			20.dstImageLayout����ΪVK_IMAGE_LAYOUT_SHARED_PRESENT_KHR, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, ���� VK_IMAGE_LAYOUT_GENERAL
			21.���VK_EXT_depth_range_unrestricted û�п�������pRegions�е�ÿ��imageSubresource����depth aspect��Ԫ�أ���srcBuffer�е�ֵ������[0,1]��Χ��
			22.���dstImage����ΪVK_IMAGE_TYPE_1D�����pRegions��ÿ��Ԫ�أ�imageOffset.y�������0��imageExtent.height����Ϊ1
			23.���dstImage������ΪVK_IMAGE_TYPE_1D ���� VK_IMAGE_TYPE_2D����pRegions��ÿ��Ԫ�ص�imageOffset.z�������0��imageExtent.depth����Ϊ1
			24.��pRegions��ÿ��Ԫ�أ�imageOffset.x����ΪdstImage��VkFormat�� texel block extent width�ı�����  imageOffset.y����ΪdstImage��VkFormat�� texel block extent height�ı���, imageOffset.z����ΪdstImage��VkFormat�� texel block extent depth�ı���
			25.��pRegions��ÿ��Ԫ�أ���1�����imageOffset.x + extent.width������srcSubresourceָ����subresource��width����extent.width����ΪdstImage��VkFormat�� texel block extent width�ı�����
									   ��2�����imageOffset.y + extent.height������srcSubresourceָ����subresource��height����extent.height����ΪdstImage��VkFormat�� texel block extent height�ı�����
									   ��3�����imageOffset.z + extent.depth������srcSubresourceָ����subresource��depth����extent.depth����ΪdstImage��VkFormat�� texel block extent depth�ı���
			26.pRegions��ÿ��Ԫ�أ�imageSubresource.aspectMask����ָ��dstImage�е�aspects
			27.���dstImage����һ��multi-planar image format����pRegions��ÿ��Ԫ�ص�imageSubresource.aspectMask������һ��������Ч��multi-planar aspect mask bit
			28.���dstImage����ΪVK_IMAGE_TYPE_3D����pRegions��ÿ��Ԫ�أ�imageSubresource.baseArrayLayer����Ϊ0����imageSubresource.layerCount����Ϊ1
			29.����pRegions��ÿ��Ԫ�أ�bufferRowLength ������dstImage��VkFormat�� texel block extent width�ı�����bufferImageHeight ������dstImage��VkFormat�� texel block extent height�ı���
			30.����pRegions��ÿ��Ԫ�أ�bufferRowLength����texel block extent width Ȼ����� dstImage��texel block size ����С�ڵ���pow(2,31) -1
			31.���dstImage �Ȳ���һ��depth/stencil format �ֲ���һ��multi-planar format�����pRegions��ÿ��Ԫ�أ�bufferOffset ������texel block size�ı���
			32.���dstImage ��һ��multi-planar format�����pRegions��ÿ��Ԫ�أ�bufferOffset �����Ǻ�imageSubresource ��format �� aspectMask���ݵ�format��Ԫ�ش�С�ı������μ� Compatible Formats of Planes of Multi-Planar Formats p4057
			33.���dstImage ��һ��depth/stencil format�����pRegions���κ�Ԫ�أ�bufferOffset ������4�ı���
			*/


			VkCopyBufferToImageInfo2 bufferImageCopyInfo2{};//�ȼ���VkCopyBufferToImageInfo2KHR
			bufferImageCopyInfo2.sType = VK_STRUCTURE_TYPE_COPY_BUFFER_TO_IMAGE_INFO_2;
			bufferImageCopyInfo2.pNext = nullptr;
			bufferImageCopyInfo2.srcBuffer = srcBuffer;//ָ��source buffer
			bufferImageCopyInfo2.dstImage = dstImage;//ָ��destination image
			bufferImageCopyInfo2.dstImageLayout = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;//ָ��image ��subresources��layout
			bufferImageCopyInfo2.regionCount = 1;//ָ��Ҫ�������������
			VkBufferImageCopy2 bufferImageCopyRegion2{};//�ȼ���VkCopyBufferToImageInfo2KHR
			{
				bufferImageCopyRegion2.sType = VK_STRUCTURE_TYPE_BUFFER_IMAGE_COPY_2;
				VkCopyCommandTransformInfoQCOM copyCommandTransformInfoQCOM{};//ָ�����������е���ת��Ϣ
				{
					copyCommandTransformInfoQCOM.sType = VK_STRUCTURE_TYPE_COPY_COMMAND_TRANSFORM_INFO_QCOM;
					copyCommandTransformInfoQCOM.pNext = nullptr;
					copyCommandTransformInfoQCOM.transform = VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR;//ֻ��ΪVK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR, VK_SURFACE_TRANSFORM_ROTATE_90_BIT_KHR, VK_SURFACE_TRANSFORM_ROTATE_180_BIT_KHR, ����VK_SURFACE_TRANSFORM_ROTATE_270_BIT_KHR
				}

				bufferImageCopyRegion2.pNext = &copyCommandTransformInfoQCOM;//���԰���һ��VkCopyCommandTransformInfoQCOM
				bufferImageCopyRegion2.bufferImageHeight = 1;//ָ������texel��������ĸ߶ȣ����Ƶ�ַ���㣬���Ϊ0����imageExtent��ά���ǽ������е�
				bufferImageCopyRegion2.bufferOffset = 0;//��buffer�е���ʼ�ֽ�ƫ����
				bufferImageCopyRegion2.bufferRowLength = 1;//ָ������texel��������Ŀ�ȣ����Ƶ�ַ���㣬���Ϊ0����imageExtent��ά���ǽ������е�
				bufferImageCopyRegion2.imageExtent = VkExtent3D{ .width = 1,.height = 1,.depth = 1 };////ѡ��image��texel�������width��height��depth�Ĵ�С
				bufferImageCopyRegion2.imageOffset = VkOffset3D{ .x = 0,.y = 0,.z = 0 };//image�е�x��y��z�Ļ���texel��ƫ����
				bufferImageCopyRegion2.imageSubresource = VkImageSubresourceLayers //ָ��image��subresource�� VkImageSubresourceLayers
				{
					.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT,//�� VkImageAspectFlagBits���ֵλ���룬ָ��Ҫ������color, depth �Լ�/���� stencil aspects
					.mipLevel = 0,//Ҫ������mipmap level
					.baseArrayLayer = 0,//Ҫ�����ĵ�һ��layer
					.layerCount = 1//Ҫ������layer�ĸ��� 
				};
				/*

				VkBufferImageCopy2��Ч�÷�:
				1.bufferRowLength ����Ϊ0�����ߵ��ڴ��ڵ���imageExtent��width
				2.bufferImageHeight ����Ϊ0�����ߵ��ڴ��ڵ���imageExtent��height
				3.imageSubresource.aspectMaskֻ�ܺ���һ����������
				4.imageExtent.width��imageExtent.height��imageExtent.depth����Ϊ0
				*/
			}
			bufferImageCopyInfo2.pRegions = &bufferImageCopyRegion2;//һ��VkBufferImageCopy2 ����ָ�룬ָ��Ҫ����������
			/*
			VkCopyBufferToImageInfo2��Ч�÷�:
			1.���pRegions�е�ÿ��Ԫ�ص�pNext�в�����VkCopyCommandTransformInfoQCOM����Ԫ��ָ����image region���������dstImage��imageSubresource ָ���ķ�Χ��
			2.���pRegions�е�ÿ��Ԫ�ص�pNext�а���VkCopyCommandTransformInfoQCOM����rotated destination region ���������dstImage��imageSubresource ָ���ķ�Χ�У��μ�p1650 [copies-buffers-images-rotation-addressing]
			3.���pRegions�е��κ�Ԫ�ص�pNext�а���VkCopyCommandTransformInfoQCOM����dstImage������1x1x1 texel block extent��dstImage �����ͱ���ΪVK_IMAGE_TYPE_2D��dstImage������һ��multi-planar format
			4.����pRegions��ÿ��Ԫ�أ� srcBuffer�����㹻�����ܹ���  Buffer �� Image Addressing����
			5.pRegions��Ԫ��ָ����source region�Ĳ����Լ�destination region�Ĳ����������ڴ������ص�
			6.srcBuffer������VK_BUFFER_USAGE_TRANSFER_SRC_BIT ����
			7.dstImage��format features�������VK_FORMAT_FEATURE_TRANSFER_DST_BIT
			8.���srcBuffer Ϊnon-sparse����������Ѿ��󶨵�һ�������������ĵ�����VkDeviceMemory��
			9.dstImage������VK_IMAGE_USAGE_TRANSFER_DST_BIT ����
			10.dstImageLayout����ָ�����������ִ����VkDevice��ʱpRegions��dstImage��subresources��layout
			10.dstImageLayout����ΪVK_IMAGE_LAYOUT_SHARED_PRESENT_KHR, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, ���� VK_IMAGE_LAYOUT_GENERAL
			11.���VK_EXT_depth_range_unrestricted û�п�������pRegions�е�ÿ��imageSubresource����depth aspect��Ԫ�أ���srcBuffer�е�ֵ������[0,1]��Χ��
			12.���dstImage Ϊnon-sparse���� disjoint plane��image ��plane�����Ѿ��󶨵�һ�������������ĵ�����VkDeviceMemory��
			13.pRegions��ÿ��Ԫ�ص�imageSubresource.mipLevel����С�ڴ���dstImage��VkImageCreateInfoָ����mipLevels
			14.���pRegions��ÿ��Ԫ�ص�imageSubresource.layerCount��ΪVK_REMAINING_ARRAY_LAYERS�����Ԫ�ص�imageSubresource.baseArrayLayer + imageSubresource.layerCount ����С�ڵ��ڴ���dstImage��VkImageCreateInfoָ����arrayLayers
			15.dstImage������VK_IMAGE_CREATE_SUBSAMPLED_BIT_EXT����
			16.dstImage��sample count ����Ϊ VK_SAMPLE_COUNT_1_BIT
			17.���dstImage����ΪVK_IMAGE_TYPE_1D�����pRegions��ÿ��Ԫ�أ�imageOffset.y�������0��imageExtent.height����Ϊ1
			18.��pRegions��ÿ��Ԫ�صģ�imageOffset.z�Լ�(imageExtent.depth + imageExtent.z)����ͬʱ���ڵ���0��С�ڵ���dstImageָ����imageSubresource��depth
			19.���dstImage������ΪVK_IMAGE_TYPE_1D ���� VK_IMAGE_TYPE_2D����pRegions��ÿ��Ԫ�ص�imageOffset.z�������0��imageExtent.depth����Ϊ1
			20.��pRegions��ÿ��Ԫ�أ�imageOffset.x����ΪdstImage��VkFormat�� texel block extent width�ı�����  imageOffset.y����ΪdstImage��VkFormat�� texel block extent height�ı���, imageOffset.z����ΪdstImage��VkFormat�� texel block extent depth�ı���
			21.��pRegions��ÿ��Ԫ�أ���1�����imageOffset.x + extent.width������srcSubresourceָ����subresource��width����extent.width����ΪdstImage��VkFormat�� texel block extent width�ı�����
									   ��2�����imageOffset.y + extent.height������srcSubresourceָ����subresource��height����extent.height����ΪdstImage��VkFormat�� texel block extent height�ı�����
									   ��3�����imageOffset.z + extent.depth������srcSubresourceָ����subresource��depth����extent.depth����ΪdstImage��VkFormat�� texel block extent depth�ı���
			22.pRegions��ÿ��Ԫ�أ�imageSubresource.aspectMask����ָ��dstImage�е�aspects
			23.���dstImage����һ��multi-planar image format����pRegions��ÿ��Ԫ�ص�imageSubresource.aspectMask������һ��������Ч��multi-planar aspect mask bit
			24.���dstImage����ΪVK_IMAGE_TYPE_3D����pRegions��ÿ��Ԫ�أ�imageSubresource.baseArrayLayer����Ϊ0����imageSubresource.layerCount����Ϊ1
			25.����pRegions��ÿ��Ԫ�أ�bufferRowLength ������dstImage��VkFormat�� texel block extent width�ı�����bufferImageHeight ������dstImage��VkFormat�� texel block extent height�ı���
			26.����pRegions��ÿ��Ԫ�أ�bufferRowLength����texel block extent width Ȼ����� dstImage��texel block size ����С�ڵ���pow(2,31) -1
			27.���dstImage �Ȳ���һ��depth/stencil format �ֲ���һ��multi-planar format�����pRegions��ÿ��Ԫ�أ�bufferOffset ������texel block size�ı���
			28.���dstImage ��һ��multi-planar format�����pRegions��ÿ��Ԫ�أ�bufferOffset �����Ǻ�imageSubresource ��format �� aspectMask���ݵ�format��Ԫ�ش�С�ı������μ� Compatible Formats of Planes of Multi-Planar Formats p4057
			29.���dstImage ��һ��depth/stencil format�����pRegions���κ�Ԫ�أ�bufferOffset ������4�ı���
			30.����pRegions��ÿ��pNext�в���VkCopyCommandTransformInfoQCOM��Ԫ�أ�imageOffset.x�Լ�(imageExtent.width + imageOffset.x)����ͬʱ���ڵ���0��С�ڵ���dstImageָ����imageSubresource��width,  imageOffset.y�Լ�(imageExtent.height + imageExtent.y)����ͬʱ���ڵ���0��С�ڵ���dstImageָ����imageSubresource��height
			*/


			//����buffer ��image �ȼ��� vkCmdCopyBufferToImage2KHR
			vkCmdCopyBufferToImage2(commandBuffer, &bufferImageCopyInfo2);
			/*
			vkCmdCopyBufferToImage2��Ч�÷�:
			1.���commandBufferΪunprotected command buffer���Ҳ�֧��protectedNoFault����srcBuffer ������һ��protected buffer,dstImage����Ϊһ��protected image
			2.���commandBufferΪprotected command buffer���Ҳ�֧��protectedNoFault����dstImage����Ϊһ��unprotected image
			3.���commandBuffer���ڵ�VkCommandPool�Ķ����岻֧��VK_QUEUE_GRAPHICS_BIT ����VK_QUEUE_COMPUTE_BIT����pCopyBufferToImageInfo->pRegions���κ�Ԫ�ص�bufferOffset������4�ı���
			4.pCopyBufferToImageInfo->pRegions��ÿ��Ԫ�ص�imageOffset��imageExtent�������commandBuffer���ڵ�VkCommandPool�Ķ������image��transfer granularity requirements���μ�VkQueueFamilyProperties
			5.���commandBuffer���ڵ�VkCommandPool�Ķ����岻֧��VK_QUEUE_GRAPHICS_BIT�������pCopyBufferToImageInfo->pRegions�е�ÿ��Ԫ�أ���imageSubresource.aspectMask����ΪVK_IMAGE_ASPECT_DEPTH_BIT ����VK_IMAGE_ASPECT_STENCIL_BIT
			*/


		}



		//����image ��buffer
		{
			VkImage srcImage{/*��������һ����Ч��VkImage*/ };
			VkBuffer dstBuffer{/*��������һ����Ч��VkBuffer*/ };

			VkBufferImageCopy imageBufferCopyRegion{};
			imageBufferCopyRegion.bufferImageHeight = 1;
			imageBufferCopyRegion.bufferOffset = 0;
			imageBufferCopyRegion.bufferRowLength = 1;
			imageBufferCopyRegion.imageExtent = VkExtent3D{ .width = 1,.height = 1,.depth = 1 };
			imageBufferCopyRegion.imageOffset = VkOffset3D{ .x = 0,.y = 0,.z = 0 };
			imageBufferCopyRegion.imageSubresource = VkImageSubresourceLayers //ָ��source image��subresource�� VkImageSubresourceLayers
			{
				.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT,//�� VkImageAspectFlagBits���ֵλ���룬ָ��Ҫ������color, depth �Լ�/���� stencil aspects
				.mipLevel = 0,//Ҫ������mipmap level
				.baseArrayLayer = 0,//Ҫ�����ĵ�һ��layer
				.layerCount = 1//Ҫ������layer�ĸ��� 
			};


			//����image��buffer

			vkCmdCopyImageToBuffer(commandBuffer, srcImage/*srcImage��ָ��source VkImage*/, VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL/*srcImageLayout , source image ��subresources ��layout*/,
				dstBuffer/*dstBuffer,ָ��destination VkBuffer*/, 1/*regionCount��Ҫ������������*/, &imageBufferCopyRegion/*pRegions��һ�� VkBufferImageCopy ����ָ�룬ָ��Ҫ����������*/);
			/*
			vkCmdCopyImageToBuffer��Ч�÷�:
			1.���srcImage Ϊnon-sparse�Ļ���ָ����disjoint plane �����Ѿ��󶨵�һ�������������ĵ�����VkDeviceMemory��
			2.pRegions��ÿ��Ԫ�ص�imageSubresource.mipLevel����С�ڴ���srcImage��VkImageCreateInfoָ����mipLevels
			3.���pRegions��ÿ��Ԫ�ص�imageSubresource.layerCount��ΪVK_REMAINING_ARRAY_LAYERS�����Ԫ�ص�imageSubresource.baseArrayLayer + imageSubresource.layerCount ����С�ڵ��ڴ���srcImage��VkImageCreateInfoָ����arrayLayers
			4.srcImage������VK_IMAGE_CREATE_SUBSAMPLED_BIT_EXT����
			5.pRegions��ÿ��Ԫ��ָ����image region���������srcImage��imageSubresourceָ����subresource��Χ��
			6.��pRegions��ÿ��Ԫ�صģ�imageOffset.x�Լ�(imageExtent.width + imageOffset.x)����ͬʱ���ڵ���0��С�ڵ���srcImageָ����imageSubresource��width,  imageOffset.y�Լ�(imageExtent.height + imageExtent.y)����ͬʱ���ڵ���0��С�ڵ���srcImageָ����imageSubresource��height��
						imageOffset.z�Լ�(imageExtent.depth + imageExtent.z)����ͬʱ���ڵ���0��С�ڵ���srcImageָ����imageSubresource��depth
			7.srcImage��sample count ����Ϊ VK_SAMPLE_COUNT_1_BIT
			8.���commandBufferΪunprotected command buffer���Ҳ�֧��protectedNoFault����dstBuffer ������һ��protected buffer,srcImage����Ϊһ��protected image
			9.���commandBufferΪprotected command buffer���Ҳ�֧��protectedNoFault����dstBuffer����Ϊһ��unprotected buffer
			10.���commandBuffer���ڵ�VkCommandPool�Ķ����岻֧��VK_QUEUE_GRAPHICS_BIT ����VK_QUEUE_COMPUTE_BIT����pRegions���κ�Ԫ�ص�bufferOffset������4�ı���
			11.pRegions��ÿ��Ԫ�ص�imageOffset��imageExtent�������commandBuffer���ڵ�VkCommandPool�Ķ������image��transfer granularity requirements���μ�VkQueueFamilyProperties
			12.���commandBuffer���ڵ�VkCommandPool�Ķ����岻֧��VK_QUEUE_GRAPHICS_BIT�������pRegions�е�ÿ��Ԫ�أ���imageSubresource.aspectMask����ΪVK_IMAGE_ASPECT_DEPTH_BIT ����VK_IMAGE_ASPECT_STENCIL_BIT
			13.����pRegions��ÿ��Ԫ�أ� dstBuffer�����㹻�����ܹ���  Buffer �� Image Addressing����
			14.pRegions��Ԫ��ָ����source region�Ĳ����Լ�destination region�Ĳ����������ڴ������ص�
			15.srcImage������VK_IMAGE_USAGE_TRANSFER_SRC_BIT ����
			16.srcImage��format features�������VK_FORMAT_FEATURE_TRANSFER_SRC_BIT
			17.dstBuffer������VK_BUFFER_USAGE_TRANSFER_DST_BIT ����
			18.���dstBuffer Ϊnon-sparse����������Ѿ��󶨵�һ�������������ĵ�����VkDeviceMemory��
			19.srcImageLayout����ָ�����������ִ����VkDevice��ʱpRegions��srcImage��subresources��layout
			20.srcImageLayout����ΪVK_IMAGE_LAYOUT_SHARED_PRESENT_KHR, VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL, ���� VK_IMAGE_LAYOUT_GENERAL
			21.���srcImage����ΪVK_IMAGE_TYPE_1D�����pRegions��ÿ��Ԫ�أ�imageOffset.y�������0��imageExtent.height����Ϊ1
			22.���srcImage������ΪVK_IMAGE_TYPE_1D ���� VK_IMAGE_TYPE_2D����pRegions��ÿ��Ԫ�ص�imageOffset.z�������0��imageExtent.depth����Ϊ1
			23.��pRegions��ÿ��Ԫ�أ�imageOffset.x����ΪsrcImage��VkFormat�� texel block extent width�ı�����  imageOffset.y����ΪsrcImage��VkFormat�� texel block extent height�ı���, imageOffset.z����ΪsrcImage��VkFormat�� texel block extent depth�ı���
			24.��pRegions��ÿ��Ԫ�أ���1�����imageOffset.x + extent.width������srcSubresourceָ����subresource��width����extent.width����ΪsrcImage��VkFormat�� texel block extent width�ı�����
									   ��2�����imageOffset.y + extent.height������srcSubresourceָ����subresource��height����extent.height����ΪsrcImage��VkFormat�� texel block extent height�ı�����
									   ��3�����imageOffset.z + extent.depth������srcSubresourceָ����subresource��depth����extent.depth����ΪsrcImage��VkFormat�� texel block extent depth�ı���
			25.pRegions��ÿ��Ԫ�أ�imageSubresource.aspectMask����ָ��srcImage�е�aspects
			26.���srcImage����һ��multi-planar image format����pRegions��ÿ��Ԫ�ص�imageSubresource.aspectMask������һ��������Ч��multi-planar aspect mask bit
			27.���srcImage����ΪVK_IMAGE_TYPE_3D����pRegions��ÿ��Ԫ�أ�imageSubresource.baseArrayLayer����Ϊ0����imageSubresource.layerCount����Ϊ1
			28.����pRegions��ÿ��Ԫ�أ�bufferRowLength ������srcImage��VkFormat�� texel block extent width�ı�����bufferImageHeight ������srcImage��VkFormat�� texel block extent height�ı���
			29.����pRegions��ÿ��Ԫ�أ�bufferRowLength����texel block extent width Ȼ����� srcImage��texel block size ����С�ڵ���pow(2,31) -1
			30.���srcImage �Ȳ���һ��depth/stencil format �ֲ���һ��multi-planar format�����pRegions��ÿ��Ԫ�أ�bufferOffset ������texel block size�ı���
			31.���srcImage ��һ��multi-planar format�����pRegions��ÿ��Ԫ�أ�bufferOffset �����Ǻ�imageSubresource ��format �� aspectMask���ݵ�format��Ԫ�ش�С�ı������μ� Compatible Formats of Planes of Multi-Planar Formats p4057
			32.���srcImage ��һ��depth/stencil format�����pRegions���κ�Ԫ�أ�bufferOffset ������4�ı���

			*/




			VkCopyImageToBufferInfo2 imageBufferCopyInfo2{};//�ȼ���VkCopyImageToBufferInfo2KHR
			imageBufferCopyInfo2.sType = VK_STRUCTURE_TYPE_COPY_IMAGE_TO_BUFFER_INFO_2;
			imageBufferCopyInfo2.pNext = nullptr;
			imageBufferCopyInfo2.srcImage = srcImage;//ָ��source image
			imageBufferCopyInfo2.srcImageLayout = VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL;//ָ��source image��subresources��layout
			imageBufferCopyInfo2.dstBuffer = dstBuffer;//ָ��destination buffer
			imageBufferCopyInfo2.regionCount = 1;//ָ��Ҫ��������������
			VkBufferImageCopy2 imageBufferCopyRegion2{};//�ȼ���VkCopyBufferToImageInfo2KHR
			{
				imageBufferCopyRegion2.sType = VK_STRUCTURE_TYPE_BUFFER_IMAGE_COPY_2;
				imageBufferCopyRegion2.pNext = nullptr;
				imageBufferCopyRegion2.bufferImageHeight = 1;//ָ������texel��������ĸ߶ȣ����Ƶ�ַ���㣬���Ϊ0����imageExtent��ά���ǽ������е�
				imageBufferCopyRegion2.bufferOffset = 0;//��buffer�е���ʼ�ֽ�ƫ����
				imageBufferCopyRegion2.bufferRowLength = 1;//ָ������texel��������Ŀ�ȣ����Ƶ�ַ���㣬���Ϊ0����imageExtent��ά���ǽ������е�
				imageBufferCopyRegion2.imageExtent = VkExtent3D{ .width = 1,.height = 1,.depth = 1 };////ѡ��image��texel�������width��height��depth�Ĵ�С
				imageBufferCopyRegion2.imageOffset = VkOffset3D{ .x = 0,.y = 0,.z = 0 };//image�е�x��y��z�Ļ���texel��ƫ����
				imageBufferCopyRegion2.imageSubresource = VkImageSubresourceLayers //ָ��image��subresource�� VkImageSubresourceLayers
				{
					.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT,//�� VkImageAspectFlagBits���ֵλ���룬ָ��Ҫ������color, depth �Լ�/���� stencil aspects
					.mipLevel = 0,//Ҫ������mipmap level
					.baseArrayLayer = 0,//Ҫ�����ĵ�һ��layer
					.layerCount = 1//Ҫ������layer�ĸ��� 
				};
			}
			imageBufferCopyInfo2.pRegions = &imageBufferCopyRegion2;//һ��VkBufferImageCopy2 ����ָ�룬ָ��Ҫ����������
			/*
			VkCopyImageToBufferInfo2��Ч�÷�:
			1.���pRegions�е�ÿ��Ԫ�ص�pNext�в�����VkCopyCommandTransformInfoQCOM����Ԫ��ָ����image region���������srcImage��imageSubresource ָ���ķ�Χ��
			2.���pRegions�е�ÿ��Ԫ�ص�pNext�а���VkCopyCommandTransformInfoQCOM����rotated destination region ���������srcImage��imageSubresource ָ���ķ�Χ�У��μ�p1650 [copies-buffers-images-rotation-addressing]
			3.���pRegions�е��κ�Ԫ�ص�pNext�а���VkCopyCommandTransformInfoQCOM����srcImage������1x1x1 texel block extent��srcImage �����ͱ���ΪVK_IMAGE_TYPE_2D��srcImage������һ��multi-planar format
			4.����pRegions��ÿ��Ԫ�أ� dstBuffer�����㹻�����ܹ���  Buffer �� Image Addressing����
			5.pRegions��Ԫ��ָ����source region�Ĳ����Լ�destination region�Ĳ����������ڴ������ص�
			6.srcImage������VK_IMAGE_USAGE_TRANSFER_SRC_BIT ����
			7.srcImage��format features�������VK_FORMAT_FEATURE_TRANSFER_SRC_BIT
			8.dstBuffer������VK_BUFFER_USAGE_TRANSFER_DST_BIT ����
			9.���dstBuffer Ϊnon-sparse����������Ѿ��󶨵�һ�������������ĵ�����VkDeviceMemory��
			10.srcImageLayout����ָ�����������ִ����VkDevice��ʱpRegions��srcImage��subresources��layout
			10.srcImageLayout����ΪVK_IMAGE_LAYOUT_SHARED_PRESENT_KHR, VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL, ���� VK_IMAGE_LAYOUT_GENERAL
						11.���VK_EXT_depth_range_unrestricted û�п�������pRegions�е�ÿ��imageSubresource����depth aspect��Ԫ�أ���srcBuffer�е�ֵ������[0,1]��Χ��
			11.���srcImage Ϊnon-sparse���� disjoint plane��image ��plane�����Ѿ��󶨵�һ�������������ĵ�����VkDeviceMemory��
			12.pRegions��ÿ��Ԫ�ص�imageSubresource.mipLevel����С�ڴ���srcImage��VkImageCreateInfoָ����mipLevels
			13.���pRegions��ÿ��Ԫ�ص�imageSubresource.layerCount��ΪVK_REMAINING_ARRAY_LAYERS�����Ԫ�ص�imageSubresource.baseArrayLayer + imageSubresource.layerCount ����С�ڵ��ڴ���srcImage��VkImageCreateInfoָ����arrayLayers
			14.srcImage������VK_IMAGE_CREATE_SUBSAMPLED_BIT_EXT����
			15.srcImage��sample count ����Ϊ VK_SAMPLE_COUNT_1_BIT
			16.���srcImage����ΪVK_IMAGE_TYPE_1D�����pRegions��ÿ��Ԫ�أ�imageOffset.y�������0��imageExtent.height����Ϊ1
			17.��pRegions��ÿ��Ԫ�صģ�imageOffset.z�Լ�(imageExtent.depth + imageExtent.z)����ͬʱ���ڵ���0��С�ڵ���srcImageָ����imageSubresource��depth
			18.���srcImage������ΪVK_IMAGE_TYPE_1D ���� VK_IMAGE_TYPE_2D����pRegions��ÿ��Ԫ�ص�imageOffset.z�������0��imageExtent.depth����Ϊ1
			19.��pRegions��ÿ��Ԫ�أ�imageOffset.x����ΪsrcImage��VkFormat�� texel block extent width�ı�����  imageOffset.y����ΪsrcImage��VkFormat�� texel block extent height�ı���, imageOffset.z����ΪsrcImage��VkFormat�� texel block extent depth�ı���
			20.��pRegions��ÿ��Ԫ�أ���1�����imageOffset.x + extent.width������srcSubresourceָ����subresource��width����extent.width����ΪsrcImage��VkFormat�� texel block extent width�ı�����
									   ��2�����imageOffset.y + extent.height������srcSubresourceָ����subresource��height����extent.height����ΪsrcImage��VkFormat�� texel block extent height�ı�����
									   ��3�����imageOffset.z + extent.depth������srcSubresourceָ����subresource��depth����extent.depth����ΪsrcImage��VkFormat�� texel block extent depth�ı���
			21.pRegions��ÿ��Ԫ�أ�imageSubresource.aspectMask����ָ��srcImage�е�aspects
			22.���srcImage����һ��multi-planar image format����pRegions��ÿ��Ԫ�ص�imageSubresource.aspectMask������һ��������Ч��multi-planar aspect mask bit
			23.���srcImage����ΪVK_IMAGE_TYPE_3D����pRegions��ÿ��Ԫ�أ�imageSubresource.baseArrayLayer����Ϊ0����imageSubresource.layerCount����Ϊ1
			24.����pRegions��ÿ��Ԫ�أ�bufferRowLength ������srcImage��VkFormat�� texel block extent width�ı�����bufferImageHeight ������srcImage��VkFormat�� texel block extent height�ı���
			25.����pRegions��ÿ��Ԫ�أ�bufferRowLength����texel block extent width Ȼ����� srcImage��texel block size ����С�ڵ���pow(2,31) -1
			26.���srcImage �Ȳ���һ��depth/stencil format �ֲ���һ��multi-planar format�����pRegions��ÿ��Ԫ�أ�bufferOffset ������texel block size�ı���
			27.���srcImage ��һ��multi-planar format�����pRegions��ÿ��Ԫ�أ�bufferOffset �����Ǻ�imageSubresource ��format �� aspectMask���ݵ�format��Ԫ�ش�С�ı������μ� Compatible Formats of Planes of Multi-Planar Formats p4057
			28.���srcImage ��һ��depth/stencil format�����pRegions���κ�Ԫ�أ�bufferOffset ������4�ı���
			30.����pRegions��ÿ��pNext�в���VkCopyCommandTransformInfoQCOM��Ԫ�أ�imageOffset.x�Լ�(imageExtent.width + imageOffset.x)����ͬʱ���ڵ���0��С�ڵ���srcImageָ����imageSubresource��width,  imageOffset.y�Լ�(imageExtent.height + imageExtent.y)����ͬʱ���ڵ���0��С�ڵ���srcImageָ����imageSubresource��height
			
			*/
			
			
			
			//����image��buffer   �ȼ���vkCmdCopyImageToBuffer2KHR
			vkCmdCopyImageToBuffer2(commandBuffer, &imageBufferCopyInfo2);
			/*
			vkCmdCopyImageToBuffer2��Ч�÷�:
			1.���commandBufferΪunprotected command buffer���Ҳ�֧��protectedNoFault����srcImage ������һ��protected image,dstBuffer����Ϊһ��protected buffer
			2.���commandBufferΪprotected command buffer���Ҳ�֧��protectedNoFault����dstBuffer����Ϊһ��unprotected buffer
			3.���commandBuffer���ڵ�VkCommandPool�Ķ����岻֧��VK_QUEUE_GRAPHICS_BIT ����VK_QUEUE_COMPUTE_BIT����pCopyBufferToImageInfo->pRegions���κ�Ԫ�ص�bufferOffset������4�ı���
			4.pCopyBufferToImageInfo->pRegions��ÿ��Ԫ�ص�imageOffset��imageExtent�������commandBuffer���ڵ�VkCommandPool�Ķ������image��transfer granularity requirements���μ�VkQueueFamilyProperties
			
			*/
		}


		//����host memory ��image
		{
			VkImage dstImage{/*��������һ����Ч��VkImage*/ };
			void* srcHostMemoryPointer{/*��������һ����Ч��host�˵��ڴ�ָ��*/};

			VkCopyMemoryToImageInfoEXT hostMemoryImageCopyInfoEXT{};
			hostMemoryImageCopyInfoEXT.sType = VK_STRUCTURE_TYPE_COPY_MEMORY_TO_IMAGE_INFO_EXT;
			hostMemoryImageCopyInfoEXT.pNext = nullptr;
			hostMemoryImageCopyInfoEXT.flags = VK_HOST_IMAGE_COPY_MEMCPY_EXT;//VkHostImageCopyFlagBitsEXT���ֵλ���룬ָ�����⿽������
			hostMemoryImageCopyInfoEXT.dstImage = dstImage;//ָ��destination image
			hostMemoryImageCopyInfoEXT.dstImageLayout = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;//ָ��image ��subresources��layout
			hostMemoryImageCopyInfoEXT.regionCount = 1;//ָ���������������
			VkMemoryToImageCopyEXT memoryImageCopyRegion{};
			{
				memoryImageCopyRegion.sType = VK_STRUCTURE_TYPE_MEMORY_TO_IMAGE_COPY_EXT;
				memoryImageCopyRegion.pNext = nullptr;
				memoryImageCopyRegion.memoryImageHeight = 1;//ָ������texel��������ĸ߶ȣ����Ƶ�ַ���㣬���Ϊ0����imageExtent��ά���ǽ������е�
				memoryImageCopyRegion.memoryRowLength = 1;//ָ������texel��������Ŀ�ȣ����Ƶ�ַ���㣬���Ϊ0����imageExtent��ά���ǽ������е�
				memoryImageCopyRegion.pHostPointer = srcHostMemoryPointer;//host�˵��ڴ��ַ��ָ����������
				memoryImageCopyRegion.imageExtent = VkExtent3D{ .width = 1,.height = 1,.depth = 1 };//ѡ��image��texel�������width��height��depth�Ĵ�С
				memoryImageCopyRegion.imageOffset = VkOffset3D{ .x = 0,.y = 0,.z = 0 };//image�е�x��y��z�Ļ���texel��ƫ����
				memoryImageCopyRegion.imageSubresource = VkImageSubresourceLayers //ָ��destination image��subresource�� VkImageSubresourceLayers
				{
					.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT,//�� VkImageAspectFlagBits���ֵλ���룬ָ��Ҫ������color, depth �Լ�/���� stencil aspects
					.mipLevel = 0,//Ҫ������mipmap level
					.baseArrayLayer = 0,//Ҫ�����ĵ�һ��layer
					.layerCount = 1//Ҫ������layer�ĸ��� 
				};
				/*
				VkMemoryToImageCopyEXT��Ч�÷�:
				1.pHostPointer����ָ��һ���㹻Buffer and Image Addressing����pRegions������Ԫ��ָ���������host���ڴ��ַ
				2.pRegions��Ԫ��ָ����source region�Ĳ����Լ�destination region�Ĳ����������ڴ������ص�
				3.memoryRowLength ����Ϊ0�����ߵ��ڴ��ڵ���imageExtent��width
				4.memoryImageHeight ����Ϊ0�����ߵ��ڴ��ڵ���imageExtent��height
				5.imageSubresource.aspectMaskֻ�ܺ���һ����������
				6.imageExtent.width��imageExtent.height��imageExtent.depth����Ϊ0
				*/
			}
			hostMemoryImageCopyInfoEXT.pRegions = &memoryImageCopyRegion;//һ��VkMemoryToImageCopyEXT����ָ�룬ָ��Ҫ����������
			/*
			VkCopyMemoryToImageInfoEXT��Ч�÷�:
			1.���dstImage��sparse�ģ��������ɷ��ʵ����������memory range�����Ѿ����ˣ��μ�Binding Resource Memory p3007
			2.������ʵ���dstImage��stencil aspect����dstImage ����	separate stencil usage������dstImage����ʱ��VkImageCreateInfo::usage�б������VK_IMAGE_USAGE_HOST_TRANSFER_BIT_EXT
			3.������ʵ���dstImage��stencil aspect����dstImage �� separate stencil usage������dstImage����ʱ��VkImageStencilUsageCreateInfo::stencilUsage�б������VK_IMAGE_USAGE_HOST_TRANSFER_BIT_EXT
			4.������ʵ���dstImage��non-stencil aspect��dstImage����ʱ��VkImageCreateInfo::usage�б������VK_IMAGE_USAGE_HOST_TRANSFER_BIT_EXT
			5.���flags ����VK_HOST_IMAGE_COPY_MEMCPY_EXT����1��pRegions��ÿ��Ԫ�ص�imageOffset��x, y, �Լ� z����Ϊ0
															 ��2��pRegions��ÿ��Ԫ�ص�imageExtent�������dstImage��imageSubresourceָ����subresource��ά�ȷ�Χ
			6.���dstImage��non-sparse�ģ���image ��ָ����disjoint plane�����Ѿ��󶨵�һ�������������ĵ�����VkDeviceMemory��
			7.pRegions��ÿ��Ԫ�ص�imageSubresource.mipLevel����С�ڴ���dstImage��VkImageCreateInfoָ����mipLevels
			8.���pRegions��ÿ��Ԫ�ص�imageSubresource.layerCount��ΪVK_REMAINING_ARRAY_LAYERS�����Ԫ�ص�imageSubresource.baseArrayLayer + imageSubresource.layerCount ����С�ڵ��ڴ���dstImage��VkImageCreateInfoָ����arrayLayers
			9.dstImage������VK_IMAGE_CREATE_SUBSAMPLED_BIT_EXT����
			10.pRegions�е�ÿ��Ԫ��ָ����image region���������dstImage��imageSubresourceָ����subresource�ķ�Χ��
			11.��pRegions��ÿ��Ԫ�صģ�imageOffset.x�Լ�(imageExtent.width + imageOffset.x)����ͬʱ���ڵ���0��С�ڵ���dstImageָ����imageSubresource��width,  imageOffset.y�Լ�(imageExtent.height + imageExtent.y)����ͬʱ���ڵ���0��С�ڵ���dstImageָ����imageSubresource��height��
										imageOffset.z�Լ�(imageExtent.depth + imageExtent.z)����ͬʱ���ڵ���0��С�ڵ���dstImageָ����imageSubresource��height
			12.dstImage��sample count ����Ϊ VK_SAMPLE_COUNT_1_BIT	
			13.���dstImage����ΪVK_IMAGE_TYPE_1D�����pRegions��ÿ��Ԫ�أ�imageOffset.y�������0��imageExtent.height����Ϊ1
			14.���dstImage������ΪVK_IMAGE_TYPE_1D ���� VK_IMAGE_TYPE_2D����pRegions��ÿ��Ԫ�ص�imageOffset.z�������0��imageExtent.depth����Ϊ1
			15.��pRegions��ÿ��Ԫ�أ�imageOffset.x����ΪdstImage��VkFormat�� texel block extent width�ı�����  imageOffset.y����ΪdstImage��VkFormat�� texel block extent height�ı���, imageOffset.z����ΪdstImage��VkFormat�� texel block extent depth�ı���
			16.��pRegions��ÿ��Ԫ�أ���1�����imageOffset.x + extent.width������srcSubresourceָ����subresource��width����extent.width����ΪdstImage��VkFormat�� texel block extent width�ı�����
									   ��2�����imageOffset.y + extent.height������srcSubresourceָ����subresource��height����extent.height����ΪdstImage��VkFormat�� texel block extent height�ı�����
									   ��3�����imageOffset.z + extent.depth������srcSubresourceָ����subresource��depth����extent.depth����ΪdstImage��VkFormat�� texel block extent depth�ı���
			17.pRegions��ÿ��Ԫ�أ�imageSubresource.aspectMask����ָ��dstImage�е�aspects
			18.���dstImage����һ��multi-planar image format����pRegions��ÿ��Ԫ�ص�imageSubresource.aspectMask������һ��������Ч��multi-planar aspect mask bit
			19.���dstImage����ΪVK_IMAGE_TYPE_3D����pRegions��ÿ��Ԫ�أ�imageSubresource.baseArrayLayer����Ϊ0����imageSubresource.layerCount����Ϊ1
			20.����pRegions��ÿ��Ԫ�أ�memoryRowLength ������dstImage��VkFormat�� texel block extent width�ı�����memoryImageHeight ������dstImage��VkFormat�� texel block extent height�ı���
			21.����pRegions��ÿ��Ԫ�أ�memoryRowLength����texel block extent width Ȼ����� dstImage��texel block size ����С�ڵ���pow(2,31) -1
			22.dstImageLayout����ָ����ǰdstImage��pRegionsָ����subresources��layout
			23.dstImageLayout�����Ƿ��ص�VkPhysicalDeviceHostImageCopyPropertiesEXT::pCopyDstLayouts�е�һ��layout
			24.���flags����VK_HOST_IMAGE_COPY_MEMCPY_EXT��memoryRowLength��memoryImageHeight����ͬʱΪ0
			*/
			

			//����host memory��image   ���������ȫ��飬������ҪӦ���ֶ���֤�漰�����������ز��������Ѿ����
			vkCopyMemoryToImageEXT(device, &hostMemoryImageCopyInfoEXT);// hostImageCopy ���Ա��뿪��

		}



		//����image ��host memory 
		{
			VkImage srcImage{/*��������һ����Ч��VkImage*/ };
			void* dstHostMemoryPointer{/*��������һ����Ч��ָ��host���ڴ��ָ��*/ };

			VkCopyImageToMemoryInfoEXT imageMemoryCopyInfo{};
			imageMemoryCopyInfo.sType = VK_STRUCTURE_TYPE_COPY_IMAGE_TO_MEMORY_INFO_EXT;
			imageMemoryCopyInfo.pNext = nullptr;
			imageMemoryCopyInfo.srcImage = srcImage;
			imageMemoryCopyInfo.srcImageLayout = VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL;
			imageMemoryCopyInfo.regionCount = 1;
			VkImageToMemoryCopyEXT imageMemoryCopyRegion{};
			{
				imageMemoryCopyRegion.sType = VK_STRUCTURE_TYPE_IMAGE_TO_MEMORY_COPY_EXT;
				imageMemoryCopyRegion.pNext = nullptr;
				imageMemoryCopyRegion.memoryImageHeight = 1;//ָ������texel��������ĸ߶ȣ����Ƶ�ַ���㣬���Ϊ0����imageExtent��ά���ǽ������е�
				imageMemoryCopyRegion.memoryRowLength = 1;//ָ������texel��������Ŀ�ȣ����Ƶ�ַ���㣬���Ϊ0����imageExtent��ά���ǽ������е�
				imageMemoryCopyRegion.pHostPointer = dstHostMemoryPointer;//host�˵��ڴ��ַ��ָ����������
				imageMemoryCopyRegion.imageExtent = VkExtent3D{ .width = 1,.height = 1,.depth = 1 };//ѡ��image��texel�������width��height��depth�Ĵ�С
				imageMemoryCopyRegion.imageOffset = VkOffset3D{ .x = 0,.y = 0,.z = 0 };//image�е�x��y��z�Ļ���texel��ƫ����
				imageMemoryCopyRegion.imageSubresource = VkImageSubresourceLayers //ָ��source image��subresource�� VkImageSubresourceLayers
				{
					.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT,//�� VkImageAspectFlagBits���ֵλ���룬ָ��Ҫ������color, depth �Լ�/���� stencil aspects
					.mipLevel = 0,//Ҫ������mipmap level
					.baseArrayLayer = 0,//Ҫ�����ĵ�һ��layer
					.layerCount = 1//Ҫ������layer�ĸ��� 
				};
			}
			imageMemoryCopyInfo.pRegions = &imageMemoryCopyRegion;


			vkCopyImageToMemoryEXT(device, &imageMemoryCopyInfo);// hostImageCopy���Ա��뿪��


		}


	}

}



NS_TEST_END