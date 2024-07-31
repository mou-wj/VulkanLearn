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
		VkClearColorValue colorClearValue{ 0,0,0,1 };
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
}







NS_TEST_END