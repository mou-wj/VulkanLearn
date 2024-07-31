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
		VkClearColorValue colorClearValue{ 0,0,0,1 };//依次对应R,G,B,A通道的清空值,类型根据具体的format确定
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
		depthStencelClearValue.depth = 0;//depth component的清空值,浮点值
		depthStencelClearValue.stencil = 1;//stencil component的清空值，整数值
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
	{
		

		VkClearValue colorClearValue{ 0,0,0,1 };
		colorClearValue.color = { 0,0,0,1 };//VkClearColorValue  依次对应R,G,B,A通道的清空值,类型根据具体的format确定
		colorClearValue.depthStencil = { 0,1 };//VkClearDepthStencilValue  依次对应depth component的清空值,浮点值, stencil component的清空值，整数值
		VkClearAttachment colorAttachment{/*假设这是一个有效的VkClearAttachment*/};
		colorAttachment.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;//选择要清空的颜色附件的color, depth 以及/或者 stencil aspects
		colorAttachment.clearValue = colorClearValue;//是清空附件的color 或者 depth/stencil 的 VkClearValue值
		colorAttachment.colorAttachment = 0;//只有aspectMask中设置了VK_IMAGE_ASPECT_COLOR_BIT才有意义，在这种情况下指向当前绑定的color attachment的索引
		/*
		VkClearAttachment有效用法:
		1.如果aspectMask包含VK_IMAGE_ASPECT_COLOR_BIT，则aspectMask就不能包含VK_IMAGE_ASPECT_DEPTH_BIT 或者 VK_IMAGE_ASPECT_STENCIL_BIT
		2.aspectMask不能包含VK_IMAGE_ASPECT_METADATA_BIT
		3.aspectMask不能包含VK_IMAGE_ASPECT_PLANE_i_BIT_EXT，对于任何i	
		*/


		VkClearRect clearRect{/*假设这是一个有效的VkClearRect*/ };
		clearRect.baseArrayLayer = 0;//指明第一个要清空的layer的索引
		clearRect.layerCount = 1;//指明要清空的layer的数量
		clearRect.rect.offset.x = 0;//指定二维清空区域的左上角x坐标
		clearRect.rect.offset.y = 0;//指定二维清空区域的左上角y坐标
		clearRect.rect.extent.width = 1;//指定二维清空区域的宽度
		clearRect.rect.extent.height = 1;//指定二维清空区域的高度

		//在render pass instance 中清空一个或多个 color 以及 depth / stencil attachments 的区域    不是transfer command，
		vkCmdClearAttachments(commandBuffer, 1/*attachmentCount ,pAttachments中元素个数*/, &colorAttachment/*pAttachments， 一组 VkClearAttachment的数组指针，指明要清空的使用clear value附件 */,
						1/* rectCount，  pRects中元素个数*/, &clearRect/* pRects，一组 VkClearRect 的数组地址，指明选择的附件的清除的区域*/);

		/*
		vkCmdClearAttachments有效用法:
		1.如果当前render pass instance不使用dynamic rendering，则（1）如果pAttachments的任何元素的aspectMask 包含VK_IMAGE_ASPECT_DEPTH_BIT，则当前subpass instance的depth-stencil attachment必须是VK_ATTACHMENT_UNUSED或者attachment format包含depth component
																 （2）如果pAttachments的任何元素的aspectMask 包含VK_IMAGE_ASPECT_STENCIL_BIT，则当前subpass instance的depth-stencil attachment必须是VK_ATTACHMENT_UNUSED或者attachment format包含stencil component
		2.如果pAttachments的任何元素的aspectMask包含VK_IMAGE_ASPECT_COLOR_BIT，则colorAttachment必须是当前render pass instance中有效的color attachment index
		3.pRects中每个元素的rect.extent.width, rect.extent.height必须大于0
		4.pRects中每个元素的rect指明的区域必须包含在当前render pass instance的render area范围内
		5.pRects中每个元素的layers必须包含在每一个pAttachments中元素引用的attachment的layers范围内，且对pRects每个元素，VkClearRect::baseArrayLayer + VkClearRect::layerCount必须小于等于当前render pass instance每一个pAttachments中元素引用的attachment的layers范围内
		6.pRects的每个元素的layers不能为0
		7.如果commandBuffer为unprotected command buffer，且不支持protectedNoFault，则每一个attachment的不能为一个protected image
		8.如果commandBuffer为protected command buffer，且不支持protectedNoFault，则每一个attachment不能为一个unprotected image
		9.如果当前render pass instance使用multiview，则pRects的每个元素的baseArrayLayer必须为0，layerCount必须为1
		10.pAttachments的每个元素的colorAttachment不能指向一个通过VkRenderingAttachmentLocationInfoKHR映射到VK_ATTACHMENT_UNUSED的附件
		11.如果subpass执行一个external format resolve，则pAttachments的任何元素的aspectMask不能包含VK_IMAGE_ASPECT_PLANE_i_BIT，对于任何i
		*/
	}


	// Clear Values 见p1615

	//Filling Buffers
	{
		VkBuffer buffer{/*假设这是一个有效的VkBuffer*/ };
		
		//清空buffer   这个命令认为是transfer的
		vkCmdFillBuffer(commandBuffer, buffer/*dstBuffer，要清空的VkBuffer*/, 0/*dstOffset ,要清空的buffer的开始字节偏移，必须是4的倍数*/,
						VK_WHOLE_SIZE/*size,从dstOffset开始要清空的字节大小，要么为4的倍数，要么为VK_WHOLE_SIZE */, 0/*data,是个4字节数据，用于填充buffer，填充buffer按照host端的大小端方式进行*/);//清空buffer中从offset 0 到 VK_WHOLE_SIZE的范围，用0填充
		/*
		vkCmdFillBuffer有效用法:
		1.dstOffset必须小于dstBuffer的size
		2.dstOffset必须是4的倍数
		3.如果size 不为VK_WHOLE_SIZE，则size必须大于0，且必须小于等于dstBuffer的size减去dstOffset，且必须是4的倍数
		4.dstBuffer必须以VK_BUFFER_USAGE_TRANSFER_DST_BIT usage flag创建
		5.如果VK_KHR_maintenance1 拓展未启用，且VkPhysicalDeviceProperties::apiVersion小于1.1，则commandBuffer所属的VkCommandPool的队列族必须支持graphics或compute操作
		6.如果dstBuffer是non-sparse的，则该buffer必须已经绑定到一个完整连续单独的VkDeviceMemory上
		7.如果commandBuffer为unprotected command buffer，且不支持protectedNoFault，则dstBuffer不能为一个protected buffer
		8.如果commandBuffer为protected command buffer，且不支持protectedNoFault，则dstBuffer不能为一个unprotected buffer

		*/

	}

	// Updating Buffers 参见p1618
	{
		VkBuffer buffer{/*假设这是一个有效的VkBuffer*/ };
		uint32_t updateData;
		//更新内联到command buffer中的buffer数据  数据会先拷贝到command buffer然后在执行命令时在拷贝到dstBuffer中  这个命令认为是transfer的
		vkCmdUpdateBuffer(commandBuffer, buffer/*dstBuffer，要更新的VkBuffer*/, 0/*dstOffset ,要更新的buffer的开始字节偏移，必须是4的倍数*/, sizeof(updateData)/*dataSize,从dstOffset开始要更新的字节大小，为4的倍数 ，必须小于65536*/, &updateData/*pData，为buffer更新的源数据，大小至少是dataSize*/);
		/*
		vkCmdUpdateBuffer有效用法:
		1.dstOffset必须小于dstBuffer的size
		2.dataSize必须小于等于dstBuffer的size减去dstOffset，且必须是4的倍数，且必须小于65536
		3.dstBuffer必须以VK_BUFFER_USAGE_TRANSFER_DST_BIT usage flag创建
		4.如果dstBuffer是non-sparse的，则该buffer必须已经绑定到一个完整连续单独的VkDeviceMemory上
		5.dataSize 必须是4的倍数
		6.如果commandBuffer为unprotected command buffer，且不支持protectedNoFault，则dstBuffer不能为一个protected buffer
		7.如果commandBuffer为protected command buffer，且不支持protectedNoFault，则dstBuffer不能为一个unprotected buffer

		*/
	}
}







NS_TEST_END