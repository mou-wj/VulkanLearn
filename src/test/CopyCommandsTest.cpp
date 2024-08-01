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
		VkBuffer srcBuffer{/*��������һ����Ч��VkBuffer*/};
		VkImage dstImage{/*��������һ����Ч��VkImage*/ };
		VkBufferImageCopy bufferImageCopyRegion{};
		bufferImageCopyRegion.bufferImageHeight = 1;
		bufferImageCopyRegion.bufferOffset = 0;
		bufferImageCopyRegion.bufferRowLength = 1;
		bufferImageCopyRegion.imageExtent = VkExtent3D{ .width = 1,.height = 1,.depth = 1 };
		bufferImageCopyRegion.imageOffset = VkOffset3D{ .x = 0,.y = 0,.z = 0 };
		bufferImageCopyRegion.imageSubresource = VkImageSubresourceLayers //ָ��destination image��subresource�� VkImageSubresourceLayers
		{
			.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT,//�� VkImageAspectFlagBits���ֵλ���룬ָ��Ҫ������color, depth �Լ�/���� stencil aspects
			.mipLevel = 0,//Ҫ������mipmap level
			.baseArrayLayer = 0,//Ҫ�����ĵ�һ��layer
			.layerCount = 1//Ҫ������layer�ĸ��� 
		};

		//����buffer��image  
		vkCmdCopyBufferToImage(commandBuffer, srcBuffer/*srcBuffer,ָ��source VkBuffer*/, dstImage/*dstImage��ָ��destination VkImage*/, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL/*dstImageLayout , destination image ��subresources ��layout*/, 
			1/*regionCount��Ҫ������������*/, &bufferImageCopyRegion/*pRegions��һ�� VkBufferImageCopy ����ָ�룬ָ��Ҫ����������*/);
		/*
		vkCmdCopyBufferToImage��Ч�÷�:
		1.���dstImage Ϊnon-sparse�Ļ���ָ����disjoint plane �����Ѿ��󶨵�һ�������������ĵ�����VkDeviceMemory��
		2.pRegions��ÿ��Ԫ�ص�imageSubresource.mipLevel����С�ڴ���srcImage��VkImageCreateInfoָ����mipLevels
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
		22.���VK_EXT_depth_range_unrestricted û�п�������pRegions�е�ÿ��imageSubresource����depth aspect��Ԫ�أ���srcBuffer�е�ֵ������[0,1]��Χ��
		23.���dstImage����ΪVK_IMAGE_TYPE_1D�����pRegions��ÿ��Ԫ�أ�imageOffset.y�������0��imageExtent.height����Ϊ1
		24.���dstImage������ΪVK_IMAGE_TYPE_1D ���� VK_IMAGE_TYPE_2D����pRegions��ÿ��Ԫ�ص�imageOffset.z�������0��imageExtent.depth����Ϊ1
		25.��pRegions��ÿ��Ԫ�أ�imageOffset.x����ΪdstImage��VkFormat�� texel block extent width�ı�����  imageOffset.y����ΪdstImage��VkFormat�� texel block extent height�ı���, imageOffset.z����ΪdstImage��VkFormat�� texel block extent depth�ı���
		26.��pRegions��ÿ��Ԫ�أ���1�����imageOffset.x + extent.width������srcSubresourceָ����subresource��width����extent.width����ΪdstImage��VkFormat�� texel block extent width�ı�����
								   ��2�����imageOffset.y + extent.height������srcSubresourceָ����subresource��height����extent.height����ΪdstImage��VkFormat�� texel block extent height�ı�����
								   ��3�����imageOffset.z + extent.depth������srcSubresourceָ����subresource��depth����extent.depth����ΪdstImage��VkFormat�� texel block extent depth�ı���
		27.pRegions��ÿ��Ԫ�أ�imageSubresource.aspectMask����ָ��dstImage�е�aspects
		29.���dstImage����һ��multi-planar image format����pRegions��ÿ��Ԫ�ص�imageSubresource.aspectMask������һ��������Ч��multi-planar aspect mask bit
		30.���dstImage����ΪVK_IMAGE_TYPE_3D����pRegions��ÿ��Ԫ�أ�imageSubresource.baseArrayLayer����Ϊ0����imageSubresource.layerCount����Ϊ1
		31.����pRegions��ÿ��Ԫ�أ�bufferRowLength ������dstImage��VkFormat�� texel block extent width�ı�����bufferImageHeight ������dstImage��VkFormat�� texel block extent height�ı���
		32.����pRegions��ÿ��Ԫ�أ�bufferRowLength����texel block extent width Ȼ����� dstImage��texel block size ����С�ڵ���pow(2,31) -1
		33.���dstImage �Ȳ���һ��depth/stencil format �ֲ���һ��multi-planar format�����pRegions��ÿ��Ԫ�أ�bufferOffset ������texel block size�ı���
		34.���dstImage ��һ��multi-planar format�����pRegions��ÿ��Ԫ�أ�bufferOffset �����Ǻ�imageSubresource ��format �� aspectMask���ݵ�format��Ԫ�ش�С�ı������μ� Compatible Formats of Planes of Multi-Planar Formats p4057
		35.���dstImage ��һ��depth/stencil format�����pRegions���κ�Ԫ�أ�bufferOffset ������4�ı���
		*/



	}

}



NS_TEST_END