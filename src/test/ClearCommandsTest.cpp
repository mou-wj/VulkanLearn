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
	VkCommandBuffer commandBuffer{/*假设这是一个有效的VkCommandBuffer*/}; 

	//Clearing Images Outside a Render Pass Instance 参见p1605
	{
		//Color 以及 depth/stencil images可以在render pass instance外调用vkCmdClearColorImage 或者 vkCmdClearDepthStencilImage被清空
		

		VkImage colorImage{/*假设这是一个有效的VkImage*/ };//
		VkClearColorValue colorClearValue{ 0,0,0,1 };
		VkImageSubresourceRange colorSubresourceRange{};
		colorSubresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
		colorSubresourceRange.baseArrayLayer = 0;
		colorSubresourceRange.baseMipLevel = 0;
		colorSubresourceRange.layerCount = 1;
		colorSubresourceRange.levelCount = 1;
		//清空color image的一个或多个subresource ranges
		vkCmdClearColorImage(commandBuffer, colorImage/*image,指明要被清空的VkImage*/, 
			VK_IMAGE_LAYOUT_SHARED_PRESENT_KHR/*imageLayout，指明要被清空的image的subresources的布局,只能为VK_IMAGE_LAYOUT_SHARED_PRESENT_KHR, VK_IMAGE_LAYOUT_GENERAL 或者 VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL.*/,
			&colorClearValue/*pColor,指明清空后的值的 VkClearColorValue指针*/, 
			1/*rangeConut,指明清空的pRanges的个数*/, &colorSubresourceRange/*pRanges,一组VkImageSubresourceRange的数组指针，指明要清空的subresources范围*/);
		/*
		vkCmdClearColorImage有效用法:
		1.image 的format feature必须包含VK_FORMAT_FEATURE_TRANSFER_DST_BIT
		2.image必须以VK_IMAGE_USAGE_TRANSFER_DST_BIT 创建
		3.image不能使用任何需要sampler Y′CBCR conversion的format
		4.如果image是non-sparse的，则该image必须已经绑定到一个完整连续单独的VkDeviceMemory上
		5.imageLayout 必须指定pRanges中指定的image的执行在VkDevice上的subresource ranges的layout
		6.imageLayout必须为VK_IMAGE_LAYOUT_SHARED_PRESENT_KHR, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL 或者 VK_IMAGE_LAYOUT_GENERAL
		7.pRanges中每个元素的VkImageSubresourceRange::aspectMask必须只能包含VK_IMAGE_ASPECT_COLOR_BIT
		8.pRanges中每个元素的VkImageSubresourceRange::baseMipLevel必须小于创建image时的VkImageCreateInfo指定的mipLevels
		9.对pRanges中每个元素VkImageSubresourceRange，如果该元素的levelCount不为VK_REMAINING_MIP_LEVELS，则该元素的baseMipLevel + levelCount必须小于等于创建image时的VkImageCreateInfo指定的mipLevels
		10.pRanges中每个元素的VkImageSubresourceRange::baseArrayLayer必须小于创建image时的VkImageCreateInfo指定的arrayLayers
		11.对pRanges中每个元素VkImageSubresourceRange，如果该元素的baseArrayLayer不为VK_REMAINING_ARRAY_LAYERS，则该元素的 baseArrayLayer + layerCount必须小于等于创建image时的VkImageCreateInfo指定的arrayLayers
		12.image不能包含一个compressed或者depth/stencil format
		13.pColor必须指向一个有效的VkClearColorValue
		14.如果commandBuffer为unprotected command buffer，且不支持protectedNoFault，则image不能为一个protected image
		15.如果commandBuffer为protected command buffer，且不支持protectedNoFault，则image不能为一个unprotected image

		
		*/

		VkImage depthStencilImage{/*假设这是一个有效的VkImage*/ };//
		VkClearDepthStencilValue depthStencelClearValue{ 0,1 };
		VkImageSubresourceRange depthStencilSubresourceRange{};
		depthStencilSubresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
		depthStencilSubresourceRange.baseArrayLayer = 0;
		depthStencilSubresourceRange.baseMipLevel = 0;
		depthStencilSubresourceRange.layerCount = 1;
		depthStencilSubresourceRange.levelCount = 1;
		//清空depth/stencil image的一个或多个subresource ranges
		vkCmdClearDepthStencilImage(commandBuffer, colorImage/*image,指明要被清空的VkImage*/,
			VK_IMAGE_LAYOUT_SHARED_PRESENT_KHR/*imageLayout，指明要被清空的image的subresources的布局,只能为 VK_IMAGE_LAYOUT_GENERAL 或者 VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL.*/,
			&depthStencelClearValue/*pDepthStencil,指明清空后的值的  VkClearDepthStencilValue指针*/,
			1/*rangeConut,指明清空的pRanges的个数*/, &depthStencilSubresourceRange/*pRanges,一组VkImageSubresourceRange的数组指针，指明要清空的subresources范围*/);
		/*
		vkCmdClearDepthStencilImage有效用法:
		1.image 的format feature必须包含VK_FORMAT_FEATURE_TRANSFER_DST_BIT
		2.如果pRanges的任何元素的aspect包含VK_IMAGE_ASPECT_STENCIL_BIT，则（1）如果image以一个分离的stencil usage创建，则创建image的VkImageStencilUsageCreateInfo::stencilUsage必须包含VK_IMAGE_USAGE_TRANSFER_DST_BIT
																		  （2）如果image不以一个分离的stencil usage创建，则创建image的VkImageCreateInfo::usage 必须包含VK_IMAGE_USAGE_TRANSFER_DST_BIT
		3.如果pRanges的任何元素的aspect包含VK_IMAGE_ASPECT_DEPTH_BIT，则创建image的VkImageCreateInfo::usage 必须包含VK_IMAGE_USAGE_TRANSFER_DST_BIT
		4.如果image是non-sparse的，则该image必须已经绑定到一个完整连续单独的VkDeviceMemory上
		5.imageLayout 必须指定pRanges中指定的image的执行在VkDevice上的subresource ranges的layout
		6.imageLayout必须为 VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL 或者 VK_IMAGE_LAYOUT_GENERAL
		7.pRanges中每个元素的VkImageSubresourceRange::aspectMask必须不能包含除VK_IMAGE_ASPECT_DEPTH_BIT或者VK_IMAGE_ASPECT_STENCIL_BIT 之外的mask位
		8.如果image的format不包含一个stencil component，则pRanges中每个元素的VkImageSubresourceRange::aspectMask不能包含VK_IMAGE_ASPECT_STENCIL_BIT
		9.如果image的format不包含一个depth component，则pRanges中每个元素的VkImageSubresourceRange::aspectMask不能包含VK_IMAGE_ASPECT_DEPTH_BIT
		10.pRanges中每个元素的VkImageSubresourceRange::baseMipLevel必须小于创建image时的VkImageCreateInfo指定的mipLevels
		11.对pRanges中每个元素VkImageSubresourceRange，如果该元素的levelCount不为VK_REMAINING_MIP_LEVELS，则该元素的baseMipLevel + levelCount必须小于等于创建image时的VkImageCreateInfo指定的mipLevels
		12.pRanges中每个元素的VkImageSubresourceRange::baseArrayLayer必须小于创建image时的VkImageCreateInfo指定的arrayLayers
		13.对pRanges中每个元素VkImageSubresourceRange，如果该元素的baseArrayLayer不为VK_REMAINING_ARRAY_LAYERS，则该元素的 baseArrayLayer + layerCount必须小于等于创建image时的VkImageCreateInfo指定的arrayLayers
		14.image必须包含一个depth/stencil format
		15.如果commandBuffer为unprotected command buffer，且不支持protectedNoFault，则image不能为一个protected image
		16.如果commandBuffer为protected command buffer，且不支持protectedNoFault，则image不能为一个unprotected image
		
		*/
	}


	// Clearing Images Inside a Render Pass Instance 参见p1611
}







NS_TEST_END