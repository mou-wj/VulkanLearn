#include "ClearCommandsTest.h"
NS_TEST_BEGIN
ClearCommandsTest::ClearCommandsTest()
{
}

void ClearCommandsTest::run()
{
}

ClearCommandsTest::~ClearCommandsTest()
{
}

void ClearCommandsTest::CommandsTest()
{
	VkCommandBuffer commandBuffer{/*��������һ����Ч��VkCommandBuffer*/}; 

	//Clearing Images Outside a Render Pass Instance �μ�p1605
	{
		//Color �Լ� depth/stencil images������render pass instance�����vkCmdClearColorImage ���� vkCmdClearDepthStencilImage�����
		

		VkImage colorImage{/*��������һ����Ч��VkImage*/ };//
		VkClearColorValue colorClearValue{ 0,0,0,1 };//���ζ�ӦR,G,B,Aͨ�������ֵ,���͸��ݾ����formatȷ��
		VkImageSubresourceRange colorSubresourceRange{};
		colorSubresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
		colorSubresourceRange.baseArrayLayer = 0;
		colorSubresourceRange.baseMipLevel = 0;
		colorSubresourceRange.layerCount = 1;
		colorSubresourceRange.levelCount = 1;
		//���color image��һ������subresource ranges
		vkCmdClearColorImage(commandBuffer, colorImage/*image,ָ��Ҫ����յ�VkImage*/, 
			VK_IMAGE_LAYOUT_SHARED_PRESENT_KHR/*imageLayout��ָ��Ҫ����յ�image��subresources�Ĳ���,ֻ��ΪVK_IMAGE_LAYOUT_SHARED_PRESENT_KHR, VK_IMAGE_LAYOUT_GENERAL ���� VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL.*/,
			&colorClearValue/*pColor,ָ����պ��ֵ�� VkClearColorValueָ��*/, 
			1/*rangeConut,ָ����յ�pRanges�ĸ���*/, &colorSubresourceRange/*pRanges,һ��VkImageSubresourceRange������ָ�룬ָ��Ҫ��յ�subresources��Χ*/);
		/*
		vkCmdClearColorImage��Ч�÷�:
		1.image ��format feature�������VK_FORMAT_FEATURE_TRANSFER_DST_BIT
		2.image������VK_IMAGE_USAGE_TRANSFER_DST_BIT ����
		3.image����ʹ���κ���Ҫsampler Y��CBCR conversion��format
		4.���image��non-sparse�ģ����image�����Ѿ��󶨵�һ����������������VkDeviceMemory��
		5.imageLayout ����ָ��pRanges��ָ����image��ִ����VkDevice�ϵ�subresource ranges��layout
		6.imageLayout����ΪVK_IMAGE_LAYOUT_SHARED_PRESENT_KHR, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL ���� VK_IMAGE_LAYOUT_GENERAL
		7.pRanges��ÿ��Ԫ�ص�VkImageSubresourceRange::aspectMask����ֻ�ܰ���VK_IMAGE_ASPECT_COLOR_BIT
		8.pRanges��ÿ��Ԫ�ص�VkImageSubresourceRange::baseMipLevel����С�ڴ���imageʱ��VkImageCreateInfoָ����mipLevels
		9.��pRanges��ÿ��Ԫ��VkImageSubresourceRange�������Ԫ�ص�levelCount��ΪVK_REMAINING_MIP_LEVELS�����Ԫ�ص�baseMipLevel + levelCount����С�ڵ��ڴ���imageʱ��VkImageCreateInfoָ����mipLevels
		10.pRanges��ÿ��Ԫ�ص�VkImageSubresourceRange::baseArrayLayer����С�ڴ���imageʱ��VkImageCreateInfoָ����arrayLayers
		11.��pRanges��ÿ��Ԫ��VkImageSubresourceRange�������Ԫ�ص�baseArrayLayer��ΪVK_REMAINING_ARRAY_LAYERS�����Ԫ�ص� baseArrayLayer + layerCount����С�ڵ��ڴ���imageʱ��VkImageCreateInfoָ����arrayLayers
		12.image���ܰ���һ��compressed����depth/stencil format
		13.pColor����ָ��һ����Ч��VkClearColorValue
		14.���commandBufferΪunprotected command buffer���Ҳ�֧��protectedNoFault����image����Ϊһ��protected image
		15.���commandBufferΪprotected command buffer���Ҳ�֧��protectedNoFault����image����Ϊһ��unprotected image

		
		*/

		VkImage depthStencilImage{/*��������һ����Ч��VkImage*/ };//
		VkClearDepthStencilValue depthStencelClearValue{ 0,1 };
		depthStencelClearValue.depth = 0;//depth component�����ֵ,����ֵ
		depthStencelClearValue.stencil = 1;//stencil component�����ֵ������ֵ
		VkImageSubresourceRange depthStencilSubresourceRange{};
		depthStencilSubresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
		depthStencilSubresourceRange.baseArrayLayer = 0;
		depthStencilSubresourceRange.baseMipLevel = 0;
		depthStencilSubresourceRange.layerCount = 1;
		depthStencilSubresourceRange.levelCount = 1;
		//���depth/stencil image��һ������subresource ranges
		vkCmdClearDepthStencilImage(commandBuffer, colorImage/*image,ָ��Ҫ����յ�VkImage*/,
			VK_IMAGE_LAYOUT_SHARED_PRESENT_KHR/*imageLayout��ָ��Ҫ����յ�image��subresources�Ĳ���,ֻ��Ϊ VK_IMAGE_LAYOUT_GENERAL ���� VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL.*/,
			&depthStencelClearValue/*pDepthStencil,ָ����պ��ֵ��  VkClearDepthStencilValueָ��*/,
			1/*rangeConut,ָ����յ�pRanges�ĸ���*/, &depthStencilSubresourceRange/*pRanges,һ��VkImageSubresourceRange������ָ�룬ָ��Ҫ��յ�subresources��Χ*/);
		/*
		vkCmdClearDepthStencilImage��Ч�÷�:
		1.image ��format feature�������VK_FORMAT_FEATURE_TRANSFER_DST_BIT
		2.���pRanges���κ�Ԫ�ص�aspect����VK_IMAGE_ASPECT_STENCIL_BIT����1�����image��һ�������stencil usage�������򴴽�image��VkImageStencilUsageCreateInfo::stencilUsage�������VK_IMAGE_USAGE_TRANSFER_DST_BIT
																		  ��2�����image����һ�������stencil usage�������򴴽�image��VkImageCreateInfo::usage �������VK_IMAGE_USAGE_TRANSFER_DST_BIT
		3.���pRanges���κ�Ԫ�ص�aspect����VK_IMAGE_ASPECT_DEPTH_BIT���򴴽�image��VkImageCreateInfo::usage �������VK_IMAGE_USAGE_TRANSFER_DST_BIT
		4.���image��non-sparse�ģ����image�����Ѿ��󶨵�һ����������������VkDeviceMemory��
		5.imageLayout ����ָ��pRanges��ָ����image��ִ����VkDevice�ϵ�subresource ranges��layout
		6.imageLayout����Ϊ VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL ���� VK_IMAGE_LAYOUT_GENERAL
		7.pRanges��ÿ��Ԫ�ص�VkImageSubresourceRange::aspectMask���벻�ܰ�����VK_IMAGE_ASPECT_DEPTH_BIT����VK_IMAGE_ASPECT_STENCIL_BIT ֮���maskλ
		8.���image��format������һ��stencil component����pRanges��ÿ��Ԫ�ص�VkImageSubresourceRange::aspectMask���ܰ���VK_IMAGE_ASPECT_STENCIL_BIT
		9.���image��format������һ��depth component����pRanges��ÿ��Ԫ�ص�VkImageSubresourceRange::aspectMask���ܰ���VK_IMAGE_ASPECT_DEPTH_BIT
		10.pRanges��ÿ��Ԫ�ص�VkImageSubresourceRange::baseMipLevel����С�ڴ���imageʱ��VkImageCreateInfoָ����mipLevels
		11.��pRanges��ÿ��Ԫ��VkImageSubresourceRange�������Ԫ�ص�levelCount��ΪVK_REMAINING_MIP_LEVELS�����Ԫ�ص�baseMipLevel + levelCount����С�ڵ��ڴ���imageʱ��VkImageCreateInfoָ����mipLevels
		12.pRanges��ÿ��Ԫ�ص�VkImageSubresourceRange::baseArrayLayer����С�ڴ���imageʱ��VkImageCreateInfoָ����arrayLayers
		13.��pRanges��ÿ��Ԫ��VkImageSubresourceRange�������Ԫ�ص�baseArrayLayer��ΪVK_REMAINING_ARRAY_LAYERS�����Ԫ�ص� baseArrayLayer + layerCount����С�ڵ��ڴ���imageʱ��VkImageCreateInfoָ����arrayLayers
		14.image�������һ��depth/stencil format
		15.���commandBufferΪunprotected command buffer���Ҳ�֧��protectedNoFault����image����Ϊһ��protected image
		16.���commandBufferΪprotected command buffer���Ҳ�֧��protectedNoFault����image����Ϊһ��unprotected image
		
		*/
	}


	// Clearing Images Inside a Render Pass Instance �μ�p1611
	{
		

		VkClearValue colorClearValue{ 0,0,0,1 };
		colorClearValue.color = { 0,0,0,1 };//VkClearColorValue  ���ζ�ӦR,G,B,Aͨ�������ֵ,���͸��ݾ����formatȷ��
		colorClearValue.depthStencil = { 0,1 };//VkClearDepthStencilValue  ���ζ�Ӧdepth component�����ֵ,����ֵ, stencil component�����ֵ������ֵ
		VkClearAttachment colorAttachment{/*��������һ����Ч��VkClearAttachment*/};
		colorAttachment.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;//ѡ��Ҫ��յ���ɫ������color, depth �Լ�/���� stencil aspects
		colorAttachment.clearValue = colorClearValue;//����ո�����color ���� depth/stencil �� VkClearValueֵ
		colorAttachment.colorAttachment = 0;//ֻ��aspectMask��������VK_IMAGE_ASPECT_COLOR_BIT�������壬�����������ָ��ǰ�󶨵�color attachment������
		/*
		VkClearAttachment��Ч�÷�:
		1.���aspectMask����VK_IMAGE_ASPECT_COLOR_BIT����aspectMask�Ͳ��ܰ���VK_IMAGE_ASPECT_DEPTH_BIT ���� VK_IMAGE_ASPECT_STENCIL_BIT
		2.aspectMask���ܰ���VK_IMAGE_ASPECT_METADATA_BIT
		3.aspectMask���ܰ���VK_IMAGE_ASPECT_PLANE_i_BIT_EXT�������κ�i	
		*/


		VkClearRect clearRect{/*��������һ����Ч��VkClearRect*/ };
		clearRect.baseArrayLayer = 0;//ָ����һ��Ҫ��յ�layer������
		clearRect.layerCount = 1;//ָ��Ҫ��յ�layer������
		clearRect.rect.offset.x = 0;//ָ����ά�����������Ͻ�x����
		clearRect.rect.offset.y = 0;//ָ����ά�����������Ͻ�y����
		clearRect.rect.extent.width = 1;//ָ����ά�������Ŀ��
		clearRect.rect.extent.height = 1;//ָ����ά�������ĸ߶�

		//��render pass instance �����һ������ color �Լ� depth / stencil attachments ������    ����transfer command��
		vkCmdClearAttachments(commandBuffer, 1/*attachmentCount ,pAttachments��Ԫ�ظ���*/, &colorAttachment/*pAttachments�� һ�� VkClearAttachment������ָ�룬ָ��Ҫ��յ�ʹ��clear value���� */,
						1/* rectCount��  pRects��Ԫ�ظ���*/, &clearRect/* pRects��һ�� VkClearRect �������ַ��ָ��ѡ��ĸ��������������*/);

		/*
		vkCmdClearAttachments��Ч�÷�:
		1.�����ǰrender pass instance��ʹ��dynamic rendering����1�����pAttachments���κ�Ԫ�ص�aspectMask ����VK_IMAGE_ASPECT_DEPTH_BIT����ǰsubpass instance��depth-stencil attachment������VK_ATTACHMENT_UNUSED����attachment format����depth component
																 ��2�����pAttachments���κ�Ԫ�ص�aspectMask ����VK_IMAGE_ASPECT_STENCIL_BIT����ǰsubpass instance��depth-stencil attachment������VK_ATTACHMENT_UNUSED����attachment format����stencil component
		2.���pAttachments���κ�Ԫ�ص�aspectMask����VK_IMAGE_ASPECT_COLOR_BIT����colorAttachment�����ǵ�ǰrender pass instance����Ч��color attachment index
		3.pRects��ÿ��Ԫ�ص�rect.extent.width, rect.extent.height�������0
		4.pRects��ÿ��Ԫ�ص�rectָ���������������ڵ�ǰrender pass instance��render area��Χ��
		5.pRects��ÿ��Ԫ�ص�layers���������ÿһ��pAttachments��Ԫ�����õ�attachment��layers��Χ�ڣ��Ҷ�pRectsÿ��Ԫ�أ�VkClearRect::baseArrayLayer + VkClearRect::layerCount����С�ڵ��ڵ�ǰrender pass instanceÿһ��pAttachments��Ԫ�����õ�attachment��layers��Χ��
		6.pRects��ÿ��Ԫ�ص�layers����Ϊ0
		7.���commandBufferΪunprotected command buffer���Ҳ�֧��protectedNoFault����ÿһ��attachment�Ĳ���Ϊһ��protected image
		8.���commandBufferΪprotected command buffer���Ҳ�֧��protectedNoFault����ÿһ��attachment����Ϊһ��unprotected image
		9.�����ǰrender pass instanceʹ��multiview����pRects��ÿ��Ԫ�ص�baseArrayLayer����Ϊ0��layerCount����Ϊ1
		10.pAttachments��ÿ��Ԫ�ص�colorAttachment����ָ��һ��ͨ��VkRenderingAttachmentLocationInfoKHRӳ�䵽VK_ATTACHMENT_UNUSED�ĸ���
		11.���subpassִ��һ��external format resolve����pAttachments���κ�Ԫ�ص�aspectMask���ܰ���VK_IMAGE_ASPECT_PLANE_i_BIT�������κ�i
		*/
	}


	// Clear Values ��p1615

	//Filling Buffers
	{
		VkBuffer buffer{/*��������һ����Ч��VkBuffer*/ };
		
		//���buffer   ���������Ϊ��transfer��
		vkCmdFillBuffer(commandBuffer, buffer/*dstBuffer��Ҫ��յ�VkBuffer*/, 0/*dstOffset ,Ҫ��յ�buffer�Ŀ�ʼ�ֽ�ƫ�ƣ�������4�ı���*/,
						VK_WHOLE_SIZE/*size,��dstOffset��ʼҪ��յ��ֽڴ�С��ҪôΪ4�ı�����ҪôΪVK_WHOLE_SIZE */, 0/*data,�Ǹ�4�ֽ����ݣ��������buffer�����buffer����host�˵Ĵ�С�˷�ʽ����*/);//���buffer�д�offset 0 �� VK_WHOLE_SIZE�ķ�Χ����0���
		/*
		vkCmdFillBuffer��Ч�÷�:
		1.dstOffset����С��dstBuffer��size
		2.dstOffset������4�ı���
		3.���size ��ΪVK_WHOLE_SIZE����size�������0���ұ���С�ڵ���dstBuffer��size��ȥdstOffset���ұ�����4�ı���
		4.dstBuffer������VK_BUFFER_USAGE_TRANSFER_DST_BIT usage flag����
		5.���VK_KHR_maintenance1 ��չδ���ã���VkPhysicalDeviceProperties::apiVersionС��1.1����commandBuffer������VkCommandPool�Ķ��������֧��graphics��compute����
		6.���dstBuffer��non-sparse�ģ����buffer�����Ѿ��󶨵�һ����������������VkDeviceMemory��
		7.���commandBufferΪunprotected command buffer���Ҳ�֧��protectedNoFault����dstBuffer����Ϊһ��protected buffer
		8.���commandBufferΪprotected command buffer���Ҳ�֧��protectedNoFault����dstBuffer����Ϊһ��unprotected buffer

		*/

	}

	// Updating Buffers �μ�p1618
	{
		VkBuffer buffer{/*��������һ����Ч��VkBuffer*/ };
		uint32_t updateData;
		//����������command buffer�е�buffer����  ���ݻ��ȿ�����command bufferȻ����ִ������ʱ�ڿ�����dstBuffer��  ���������Ϊ��transfer��
		vkCmdUpdateBuffer(commandBuffer, buffer/*dstBuffer��Ҫ���µ�VkBuffer*/, 0/*dstOffset ,Ҫ���µ�buffer�Ŀ�ʼ�ֽ�ƫ�ƣ�������4�ı���*/, sizeof(updateData)/*dataSize,��dstOffset��ʼҪ���µ��ֽڴ�С��Ϊ4�ı��� ������С��65536*/, &updateData/*pData��Ϊbuffer���µ�Դ���ݣ���С������dataSize*/);
		/*
		vkCmdUpdateBuffer��Ч�÷�:
		1.dstOffset����С��dstBuffer��size
		2.dataSize����С�ڵ���dstBuffer��size��ȥdstOffset���ұ�����4�ı������ұ���С��65536
		3.dstBuffer������VK_BUFFER_USAGE_TRANSFER_DST_BIT usage flag����
		4.���dstBuffer��non-sparse�ģ����buffer�����Ѿ��󶨵�һ����������������VkDeviceMemory��
		5.dataSize ������4�ı���
		6.���commandBufferΪunprotected command buffer���Ҳ�֧��protectedNoFault����dstBuffer����Ϊһ��protected buffer
		7.���commandBufferΪprotected command buffer���Ҳ�֧��protectedNoFault����dstBuffer����Ϊһ��unprotected buffer

		*/
	}
}







NS_TEST_END