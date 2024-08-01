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
	//copy commands拷贝 buffer 以及 image data ，认为是transfer的

	VkCommandBuffer commandBuffer{/*假设这是一个有效的VkCommandBuffer*/ };

	// Copying Data Between Buffers 参见p1622
	{
		//在buffers间拷贝数据
		VkBuffer srcBuffer{/*假设这是一个有效的VkBuffer*/ };
		VkBuffer dstBuffer{/*假设这是一个有效的VkBuffer*/ };
		VkBufferCopy copyRegion{};
		copyRegion.srcOffset = 0;//为srcBuffer开始字节的字节偏移量
		copyRegion.dstOffset = 0;//为dstBuffer开始字节的字节偏移量
		copyRegion.size = 1;//要拷贝的字节大小，必须大于0
		vkCmdCopyBuffer(commandBuffer, srcBuffer/*srcBuffer，拷贝的source buffer*/, dstBuffer/*dstBuffer，拷贝的destination buffer*/,
			1/*regionCount，要拷贝的区域数量*/, &copyRegion/*pRegions，一组VkBufferCopy数组指针，指明要拷贝的区域,如果区域指明的srcBuffer和dstBuffer的内存存在重叠，则从重叠的内存中读数据是未定义的*/);
		/*
		vkCmdCopyBuffer有效用法:
		1.如果commandBuffer为unprotected command buffer，且不支持protectedNoFault，则srcBuffer,dstBuffer不能为一个protected buffer
		2.如果commandBuffer为protected command buffer，且不支持protectedNoFault，则dstBuffer不能为一个unprotected buffer
		3.pRegions中每个元素的srcOffset必须小于等于srcBuffer的大小，dstOffset必须小于等于dstBuffer的大小
		4.pRegions中每个元素的size必须小于等于srcBuffer的大小减去srcOffset，且必须小于dstBuffer的大小减去dstOffset
		5.pRegions的元素指明的source region的并集以及destination region的并集不能在内存上有重叠
		6.srcBuffer必须以VK_BUFFER_USAGE_TRANSFER_SRC_BIT创建，且如果该buffer为non-sparse的，则其必须已经绑定到一个完整连续单独的VkDeviceMemory上了
		7.dstBuffer必须以VK_BUFFER_USAGE_TRANSFER_DST_BIT创建，且如果该buffer为non-sparse的，则其必须已经绑定到一个完整连续单独的VkDeviceMemory上了

		*/



		VkCopyBufferInfo2 copyBufferInfo2{};
		copyBufferInfo2.sType = VK_STRUCTURE_TYPE_COPY_BUFFER_INFO_2;
		copyBufferInfo2.pNext = nullptr;
		copyBufferInfo2.srcBuffer = srcBuffer;//拷贝的source buffer
		copyBufferInfo2.dstBuffer = dstBuffer;//拷贝的destination buffer
		copyBufferInfo2.regionCount = 1;//要拷贝的区域数量
		VkBufferCopy2 copyRegion2{};
		{
			copyRegion2.sType = VK_STRUCTURE_TYPE_BUFFER_COPY_2;
			copyRegion2.pNext = nullptr;
			copyRegion2.srcOffset = 0;//为srcBuffer开始字节的字节偏移量
			copyRegion2.dstOffset = 0;//为dstBuffer开始字节的字节偏移量
			copyRegion2.size = 1;//要拷贝的字节大小，必须大于0
		}
	

		copyBufferInfo2.pRegions = &copyRegion2;//一组VkBufferCopy2数组指针，指明要拷贝的区域
		/*
		1.pRegions中每个元素的srcOffset必须小于等于srcBuffer的大小，dstOffset必须小于等于dstBuffer的大小
		2.pRegions中每个元素的size必须小于等于srcBuffer的大小减去srcOffset，且必须小于dstBuffer的大小减去dstOffset
		3.pRegions的元素指明的source region的并集以及destination region的并集不能在内存上有重叠
		4.srcBuffer必须以VK_BUFFER_USAGE_TRANSFER_SRC_BIT创建，且如果该buffer为non-sparse的，则其必须已经绑定到一个完整连续单独的VkDeviceMemory上了
		5.dstBuffer必须以VK_BUFFER_USAGE_TRANSFER_DST_BIT创建，且如果该buffer为non-sparse的，则其必须已经绑定到一个完整连续单独的VkDeviceMemory上了
		*/



		//buffers间拷贝，等价于vkCmdCopyBuffer2KHR
		vkCmdCopyBuffer2(commandBuffer, &copyBufferInfo2);//pCopyBufferInfo->pRegions区域指明的srcBuffer和dstBuffer的内存存在重叠，则从重叠的内存中读数据是未定义的
		/*
		vkCmdCopyBuffer2有效用法:
		1.如果commandBuffer为unprotected command buffer，且不支持protectedNoFault，则srcBuffer,dstBuffer不能为一个protected buffer
		2.如果commandBuffer为protected command buffer，且不支持protectedNoFault，则dstBuffer不能为一个unprotected image
		
		*/
	}


	// Copying Data Between Images  参见p1629
	{
		//在images间进行拷贝
		VkImage srcImage{/*假设这是一个有效的VkImage*/};
		VkImage dstImage{/*假设这是一个有效的VkImage*/};
		VkImageCopy copyImage{};
		copyImage.srcOffset = VkOffset3D{.x = 0,.y = 0,.z = 0};//source image中的x，y，z的基于texel的偏移量
		copyImage.srcSubresource = VkImageSubresourceLayers //指明source image的subresource的 VkImageSubresourceLayers
			{
			.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT,//是 VkImageAspectFlagBits组合值位掩码，指明要拷贝的color, depth 以及/或者 stencil aspects
			.mipLevel = 0,//要拷贝的mipmap level
			.baseArrayLayer = 0,//要拷贝的第一个layer
			.layerCount = 1//要拷贝的layer的个数 
			/*
			VkImageSubresourceLayers有效用法:
			1.如果aspectMask包含VK_IMAGE_ASPECT_COLOR_BIT，则其不能包含VK_IMAGE_ASPECT_DEPTH_BIT或者VK_IMAGE_ASPECT_STENCIL_BIT中的一个
			2.aspectMask不能包含VK_IMAGE_ASPECT_METADATA_BIT，不能对index i包含VK_IMAGE_ASPECT_MEMORY_PLANE_i_BIT_EXT
			3.如果maintenance5特性没有开启，则layerCount 不能为VK_REMAINING_ARRAY_LAYERS
			4.如果layerCount 不为VK_REMAINING_ARRAY_LAYERS，则layerCount必须大于0
			*/
			};

		copyImage.dstOffset = VkOffset3D{ .x = 0,.y = 0,.z = 0 };//destination image中的x，y，z的基于texel的偏移量
		copyImage.srcSubresource = VkImageSubresourceLayers //指明destination image的subresource的 VkImageSubresourceLayers
			{
			.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT,
			.mipLevel = 0,
			.baseArrayLayer = 0,
			.layerCount = 1
			};
		copyImage.extent = VkExtent3D{.width =  1,.height = 1,.depth = 1 };//是要拷贝的image 基于texel的width, height 以及 depth.
		/*
		VkImageCopy有效用法:
		1.如果VK_KHR_sampler_ycbcr_conversion 拓展没有开启，且VkPhysicalDeviceProperties::apiVersion小于Vulkan 1.1,则srcSubresource 以及 dstSubresource的aspectMask，layerCount必须匹配
		2.extent.width，extent.height，extent.depth 不能为0
		*/



		vkCmdCopyImage(commandBuffer, srcImage/*srcImage,拷贝的source image*/, VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL/*srcImageLayout，当前srcImage的subresource的layout*/,
			dstImage/*dstImage,拷贝的destination image*/, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL/*dstImageLayout，当前dstImage的subresource的layout*/, 
			1/*regionCount,要拷贝的区域数量*/, &copyImage/*pRegions，一组 VkImageCopy数组指针，指明要拷贝的区域*/);//如果区域指明的srcBuffer和dstBuffer的内存存在重叠，则从重叠的内存中读数据是未定义的,其他信息见p1629
		/*
		vkCmdCopyImage有效用法:
		1.如果commandBuffer为unprotected command buffer，且不支持protectedNoFault，则srcImage,dstImage不能为一个protected image
		2.如果commandBuffer为protected command buffer，且不支持protectedNoFault，则dstImage不能为一个unprotected image
		3.pRegions的元素指明的source region的并集以及destination region的并集不能在内存上有重叠
		4.srcImage的format features必须包含VK_FORMAT_FEATURE_TRANSFER_SRC_BIT
		5.srcImageLayout必须指明在这个命令执行在VkDevice上时pRegions中srcImage的subresources的layout
		6.srcImageLayout必须为VK_IMAGE_LAYOUT_SHARED_PRESENT_KHR, VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL, 或者 VK_IMAGE_LAYOUT_GENERAL
		7.如果srcImage和dstImage相同，且pRegions的任何元素包含mipLevel匹配且array layers重叠的srcSubresource 和 dstSubresource，则srcImageLayout 和 dstImageLayout 必须为 VK_IMAGE_LAYOUT_GENERAL 或者 VK_IMAGE_LAYOUT_SHARED_PRESENT_KHR
		8.dstImage的format features必须包含VK_FORMAT_FEATURE_TRANSFER_DST_BIT
		9.dstImageLayout必须指明在这个命令执行在VkDevice上时pRegions中dstImage的subresources的layout
		10.dstImageLayout必须为VK_IMAGE_LAYOUT_SHARED_PRESENT_KHR, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, 或者 VK_IMAGE_LAYOUT_GENERAL
		11.如果srcImage 和 dstImage的VkFormat不是一个 multi-planar format，则srcImage 和 dstImage的VkFormat必须是size-compatible大小兼容的
		12.如果从拷贝涉及到multi-planar image的一个plane，则image的VkFormat和plane必须是兼容的，参见 the description of compatible planes p4057
		13.如果srcImage 和 dstImage的VkFormat是一个compressed image format，则formats必须有相同的texel block extent
		14.srcImage 和 dstImage的sample count必须匹配
		15.pRegions中每个元素的srcOffset和extent、dstOffset和extent必须符合commandBuffer所在的VkCommandPool的队列族的image的transfer granularity requirements，参见VkQueueFamilyProperties
		16.如果srcImage和dstImage都不含有一个multi-planar image format，则pRegions中每个元素的srcSubresource.aspectMask以及dstSubresource.aspectMask必须匹配
		17.如果srcImage含有一个multi-planar image format，则pRegions中每个元素的srcSubresource.aspectMask必须是一个单独有效的multi-planar aspect mask bit
		18.如果dstImage含有一个multi-planar image format，则pRegions中每个元素的dstSubresource.aspectMask必须是一个单独有效的multi-planar aspect mask bit
		19.如果srcImage含有一个multi-planar image format，但是dstImage不含有一个multi-planar image format 则pRegions中每个元素的dstSubresource.aspectMask必须是VK_IMAGE_ASPECT_COLOR_BIT
		20.如果dstImage含有一个multi-planar image format，但是srcImage不含有一个multi-planar image format 则pRegions中每个元素的srcSubresource.aspectMask必须是VK_IMAGE_ASPECT_COLOR_BIT
		21.如果VK_KHR_maintenance1 拓展没有开启，或者VkPhysicalDeviceProperties::apiVersion小于Vulkan 1.1，且srcImage或者dstImage之一的类型为VK_IMAGE_TYPE_3D，则pRegions的每个元素，srcSubresource.baseArrayLayer以及dstSubresource.baseArrayLayer必须为0，srcSubresource.layerCount和dstSubresource.layerCount必须为1
		22.如果srcImage类型为VK_IMAGE_TYPE_3D，则pRegions的每个元素，srcSubresource.baseArrayLayer必须为0，且srcSubresource.layerCount必须为1
		23.如果dstImage类型为VK_IMAGE_TYPE_3D，则pRegions的每个元素，dstSubresource.baseArrayLayer必须为0，且dstSubresource.layerCount必须为1
		24.pRegions的每个元素，srcSubresource.aspectMask必须指明srcImage中的aspects，dstSubresource.aspectMask必须指明dstImage中的aspects
		25.pRegions的每个元素，srcOffset.x以及(extent.width + srcOffset.x) 必须同时大于等于0，且小于等于指定的srcImage的srcSubresource中的width,  srcOffset.y以及(extent.height + srcOffset.y) 必须同时大于等于0，且小于等于指定的srcImage的srcSubresource中的height
		26.如果srcImage类型为VK_IMAGE_TYPE_1D，则pRegions中的每个元素，srcOffset.y必须为0，且extent.height必须为1，srcOffset.z必须为0，且extent.depth必须为1
		27.如果srcImage类型为VK_IMAGE_TYPE_3D，则pRegions中的每个元素，srcOffset.z以及(extent.depth + srcOffset.z) 必须同时大于等于0且小于等于指定的srcImage的srcSubresource中的depth
		28.如果dstImage类型为VK_IMAGE_TYPE_1D，则pRegions中的每个元素，dstOffset.z必须为0，且extent.depth必须为1
		29.如果srcImage类型为VK_IMAGE_TYPE_2D，则pRegions中的每个元素，srcOffset.z必须为0
		30.如果dstImage类型为VK_IMAGE_TYPE_2D，则pRegions中的每个元素，dstOffset.z必须为0
		31.如果VK_KHR_maintenance1 拓展没有开启，且VkPhysicalDeviceProperties::apiVersion小于Vulkan 1.1，则（1）srcImage和dstImage必须是相同的类型
																									       （2）如果 srcImage 或者 dstImage类型为VK_IMAGE_TYPE_2D，则pRegions的每个元素，extent.depth必须为1
		32.如果srcImage和dstImage的类型不同，且maintenance5没有开启，其中一个类型必须为VK_IMAGE_TYPE_3D，且另外一个类型必须为VK_IMAGE_TYPE_2D
		33.如果srcImage和dstImage的类型相同，则（1）对pRegions的每个元素，如果srcSubresource和dstSubresource的layerCount都不是VK_REMAINING_ARRAY_LAYERS，则srcSubresource 或者 dstSubresource的layerCount必须匹配
											  （2）对pRegions的每个元素，如果srcSubresource或者dstSubresource其中一个的layerCount为VK_REMAINING_ARRAY_LAYERS，则另外一个的layerCount必须为VK_REMAINING_ARRAY_LAYERS或者等于创建该image时的VkImageCreateInfo的arrayLayers减去baseArrayLayer
		34.如果srcImage和dstImage的类型都为VK_IMAGE_TYPE_2D，则pRegions的每个元素，extent.depth必须为1
		35.如果srcImage类型为VK_IMAGE_TYPE_2D，且dstImage类型为VK_IMAGE_TYPE_3D，则pRegions中的每个元素，extent.depth必须等于srcSubresource.layerCount
		36.如果dstImage类型为VK_IMAGE_TYPE_2D，且srcImage类型为VK_IMAGE_TYPE_3D，则pRegions中的每个元素，extent.depth必须等于dstSubresource.layerCount
		37.对于pRegions的每个元素，dstOffset.x以及(extent.width + dstOffset.x)必须同时大于等于0且小于等于dstImage指定的subresource的width,  dstOffset.y以及(extent.height + dstOffset.y)必须同时大于等于0且小于等于dstImage指定的subresource的height
		38.如果dstImage类型为VK_IMAGE_TYPE_1D，则对pRegions的每个元素，dstOffset.y必须等于0且extent.height必须为1
		39.如果dstImage类型为VK_IMAGE_TYPE_3D，则对pRegions的每个元素，dstOffset.z和(extent.depth + dstOffset.z)必须同时大于等于0且小于等于dstImage指定的subresource的depth
		40.对pRegions的每个元素，srcOffset.x必须为srcImage的VkFormat的 texel block extent width的倍数，  srcOffset.y必须为srcImage的VkFormat的 texel block extent height的倍数,srcOffset.z必须为srcImage的VkFormat的 texel block extent depth的倍数
		41.对pRegions的每个元素，dstOffset.x必须为dstImage的VkFormat的 texel block extent width的倍数，  dstOffset.y必须为dstImage的VkFormat的 texel block extent height的倍数,dstOffset.z必须为dstImage的VkFormat的 texel block extent depth的倍数
		42.对pRegions的每个元素，则（1）如果srcOffset.x + extent.width不等于srcSubresource指定的subresource的width，则extent.width必须为srcImage的VkFormat的 texel block extent width的倍数，
								   （2）如果srcOffset.y + extent.height不等于srcSubresource指定的subresource的height，则extent.height必须为srcImage的VkFormat的 texel block extent height的倍数，
								   （3）如果srcOffset.z + extent.depth不等于srcSubresource指定的subresource的depth，则extent.depth必须为srcImage的VkFormat的 texel block extent depth的倍数
		43.对pRegions的每个元素，则（1）如果dstOffset.x + extent.width不等于dstSubresource指定的subresource的width，则extent.width必须为dstImage的VkFormat的 texel block extent width的倍数，
								   （2）如果dstOffset.y + extent.height不等于dstSubresource指定的subresource的height，则extent.height必须为dstImage的VkFormat的 texel block extent height的倍数，
								   （3）如果dstOffset.z + extent.depth不等于dstSubresource指定的subresource的depth，则extent.depth必须为dstImage的VkFormat的 texel block extent depth的倍数
		44.如果pRegions中任何元素的aspect包含任何除VK_IMAGE_ASPECT_STENCIL_BIT之外的mask或者srcImage不以一个separate stencil usage创建（含一个相关结构体在pNext中），则VK_IMAGE_USAGE_TRANSFER_SRC_BIT必须包含在创建srcImage的VkImageCreateInfo::usage中
		45.如果pRegions中任何元素的aspect包含任何除VK_IMAGE_ASPECT_STENCIL_BIT之外的mask或者dstImage不以一个separate stencil usage创建（含一个相关结构体在pNext中），则VK_IMAGE_USAGE_TRANSFER_DST_BIT必须包含在创建dstImage的VkImageCreateInfo::usage中
		46.如果pRegions中任何元素的aspect包含VK_IMAGE_ASPECT_STENCIL_BIT 且srcImage以一个separate stencil usage创建（含一个相关结构体在pNext中），则VK_IMAGE_USAGE_TRANSFER_SRC_BIT必须包含在创建srcImage的VkImageStencilUsageCreateInfo::stencilUsage中
		47.如果pRegions中任何元素的aspect包含VK_IMAGE_ASPECT_STENCIL_BIT 且dstImage以一个separate stencil usage创建（含一个相关结构体在pNext中），则VK_IMAGE_USAGE_TRANSFER_DST_BIT必须包含在创建dstImage的VkImageStencilUsageCreateInfo::stencilUsage中
		48.如果srcImage为 non-sparse的则image或者指定的disjoint plane必须已经绑定到完整的连续的单独的VkDeviceMemory上
		49.pRegions的每个元素的srcSubresource.mipLevel必须小于创建srcImage的VkImageCreateInfo指定的mipLevels
		50.如果pRegions的每个元素的srcSubresource.layerCount不为VK_REMAINING_ARRAY_LAYERS，则该元素的srcSubresource.baseArrayLayer + srcSubresource.layerCount 必须小于等于创建srcImage的VkImageCreateInfo指定的arrayLayers
		51.srcImage不能以VK_IMAGE_CREATE_SUBSAMPLED_BIT_EXT创建
		52.如果dstImage为 non-sparse的则image或者指定的disjoint plane必须已经绑定到完整的连续的单独的VkDeviceMemory上
		53.pRegions的每个元素的dstSubresource.mipLevel必须小于创建dstImage的VkImageCreateInfo指定的mipLevels
		54.如果pRegions的每个元素的dstSubresource.layerCount不为VK_REMAINING_ARRAY_LAYERS，则该元素的dstSubresource.baseArrayLayer + dstSubresource.layerCount 必须小于等于创建dstImage的VkImageCreateInfo指定的arrayLayers
		55.dstImage不能以VK_IMAGE_CREATE_SUBSAMPLED_BIT_EXT创建
		*/

		VkCopyImageInfo2 copyImageInfo2{};
		copyImageInfo2.sType = VK_STRUCTURE_TYPE_COPY_IMAGE_INFO_2;
		copyImageInfo2.pNext = nullptr;
		copyImageInfo2.srcImage = srcImage;//指明要拷贝的source image
		copyImageInfo2.srcImageLayout = VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL;//指明source image的subresources的layout
		copyImageInfo2.dstImage = dstImage;//指明要拷贝的destination image
		copyImageInfo2.dstImageLayout = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;//指明destination image的subresources的layout
		copyImageInfo2.regionCount = 1;//指明要拷贝的数量
		VkImageCopy2 copyImage2{};
		{
			copyImage2.sType = VK_STRUCTURE_TYPE_IMAGE_COPY_2;
			copyImage2.pNext = nullptr;
			copyImage2.srcOffset = VkOffset3D{ .x = 0,.y = 0,.z = 0 };//source image中的x，y，z的基于texel的偏移量
			copyImage2.srcSubresource = VkImageSubresourceLayers{/*假设这是一个有效的VkImageSubresourceLayers，参见前面对VkImageSubresourceLayers的描述*/ };//指明source image的subresource的 VkImageSubresourceLayers
			copyImage2.dstOffset = VkOffset3D{ .x = 0,.y = 0,.z = 0 };//destination image中的x，y，z的基于texel的偏移量
			copyImage2.dstSubresource = VkImageSubresourceLayers{/*假设这是一个有效的VkImageSubresourceLayers，参见前面对VkImageSubresourceLayers的描述*/ };//指明destination image的subresource的 VkImageSubresourceLayers
			copyImage2.extent = VkExtent3D{ .width = 1,.height = 1,.depth = 1 };//是要拷贝的image 基于texel的width, height 以及 depth.
		}
		copyImageInfo2.pRegions = &copyImage2;//是一组 VkImageCopy2 数组指针指明要拷贝的区域
		/*
		VkCopyImageInfo2有效用法:
		1.pRegions的元素指明的source region的并集以及destination region的并集不能在内存上有重叠
		2.srcImage的format features必须包含VK_FORMAT_FEATURE_TRANSFER_SRC_BIT
		3.srcImageLayout必须指明在这个命令执行在VkDevice上时pRegions中srcImage的subresources的layout
		4.srcImageLayout必须为VK_IMAGE_LAYOUT_SHARED_PRESENT_KHR, VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL, 或者 VK_IMAGE_LAYOUT_GENERAL
		5.如果srcImage和dstImage相同，且pRegions的任何元素包含mipLevel匹配且array layers重叠的srcSubresource 和 dstSubresource，则srcImageLayout 和 dstImageLayout 必须为 VK_IMAGE_LAYOUT_GENERAL 或者 VK_IMAGE_LAYOUT_SHARED_PRESENT_KHR
		6.dstImage的format features必须包含VK_FORMAT_FEATURE_TRANSFER_DST_BIT
		7.dstImageLayout必须指明在这个命令执行在VkDevice上时pRegions中dstImage的subresources的layout
		8.dstImageLayout必须为VK_IMAGE_LAYOUT_SHARED_PRESENT_KHR, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, 或者 VK_IMAGE_LAYOUT_GENERAL
		9.如果srcImage 和 dstImage的VkFormat不是一个 multi-planar format，则srcImage 和 dstImage的VkFormat必须是size-compatible大小兼容的
		10.如果从拷贝涉及到multi-planar image的一个plane，则image的VkFormat和plane必须是兼容的，参见 the description of compatible planes p4057
		12.如果srcImage 和 dstImage的VkFormat是一个compressed image format，则formats必须有相同的texel block extent
		13.srcImage 和 dstImage的sample count必须匹配
		14.pRegions中每个元素的srcOffset和extent、dstOffset和extent必须符合commandBuffer所在的VkCommandPool的队列族的image的transfer granularity requirements，参见VkQueueFamilyProperties
		15.如果srcImage和dstImage都不含有一个multi-planar image format，则pRegions中每个元素的srcSubresource.aspectMask以及dstSubresource.aspectMask必须匹配
		16.如果srcImage含有一个multi-planar image format，则pRegions中每个元素的srcSubresource.aspectMask必须是一个单独有效的multi-planar aspect mask bit
		17.如果dstImage含有一个multi-planar image format，则pRegions中每个元素的dstSubresource.aspectMask必须是一个单独有效的multi-planar aspect mask bit
		18.如果srcImage含有一个multi-planar image format，但是dstImage不含有一个multi-planar image format 则pRegions中每个元素的dstSubresource.aspectMask必须是VK_IMAGE_ASPECT_COLOR_BIT
		19.如果dstImage含有一个multi-planar image format，但是srcImage不含有一个multi-planar image format 则pRegions中每个元素的srcSubresource.aspectMask必须是VK_IMAGE_ASPECT_COLOR_BIT
		20.如果VK_KHR_maintenance1 拓展没有开启，或者VkPhysicalDeviceProperties::apiVersion小于Vulkan 1.1，且srcImage或者dstImage之一的类型为VK_IMAGE_TYPE_3D，则pRegions的每个元素，srcSubresource.baseArrayLayer以及dstSubresource.baseArrayLayer必须为0，srcSubresource.layerCount和dstSubresource.layerCount必须为1
		21.如果srcImage类型为VK_IMAGE_TYPE_3D，则pRegions的每个元素，srcSubresource.baseArrayLayer必须为0，且srcSubresource.layerCount必须为1
		22.如果dstImage类型为VK_IMAGE_TYPE_3D，则pRegions的每个元素，dstSubresource.baseArrayLayer必须为0，且dstSubresource.layerCount必须为1
		23.pRegions的每个元素，srcSubresource.aspectMask必须指明srcImage中的aspects，dstSubresource.aspectMask必须指明dstImage中的aspects
		24.pRegions的每个元素，srcOffset.x以及(extent.width + srcOffset.x) 必须同时大于等于0，且小于等于指定的srcImage的srcSubresource中的width,  srcOffset.y以及(extent.height + srcOffset.y) 必须同时大于等于0，且小于等于指定的srcImage的srcSubresource中的height
		25.如果srcImage类型为VK_IMAGE_TYPE_1D，则pRegions中的每个元素，srcOffset.y必须为0，且extent.height必须为1，srcOffset.z必须为0，且extent.depth必须为1
		26.如果srcImage类型为VK_IMAGE_TYPE_3D，则pRegions中的每个元素，srcOffset.z以及(extent.depth + srcOffset.z) 必须同时大于等于0且小于等于指定的srcImage的srcSubresource中的depth
		27.如果dstImage类型为VK_IMAGE_TYPE_1D，则pRegions中的每个元素，dstOffset.z必须为0，且extent.depth必须为1
		28.如果srcImage类型为VK_IMAGE_TYPE_2D，则pRegions中的每个元素，srcOffset.z必须为0
		29.如果dstImage类型为VK_IMAGE_TYPE_2D，则pRegions中的每个元素，dstOffset.z必须为0
		30.如果VK_KHR_maintenance1 拓展没有开启，且VkPhysicalDeviceProperties::apiVersion小于Vulkan 1.1，则（1）srcImage和dstImage必须是相同的类型
																										   （2）如果 srcImage 或者 dstImage类型为VK_IMAGE_TYPE_2D，则pRegions的每个元素，extent.depth必须为1
		31.如果srcImage和dstImage的类型不同，且maintenance5没有开启，其中一个类型必须为VK_IMAGE_TYPE_3D，且另外一个类型必须为VK_IMAGE_TYPE_2D
		32.如果srcImage和dstImage的类型相同，则（1）对pRegions的每个元素，如果srcSubresource和dstSubresource的layerCount都不是VK_REMAINING_ARRAY_LAYERS，则srcSubresource 或者 dstSubresource的layerCount必须匹配
											  （2）对pRegions的每个元素，如果srcSubresource或者dstSubresource其中一个的layerCount为VK_REMAINING_ARRAY_LAYERS，则另外一个的layerCount必须为VK_REMAINING_ARRAY_LAYERS或者等于创建该image时的VkImageCreateInfo的arrayLayers减去baseArrayLayer
		33.如果srcImage和dstImage的类型都为VK_IMAGE_TYPE_2D，则pRegions的每个元素，extent.depth必须为1
		34.如果srcImage类型为VK_IMAGE_TYPE_2D，且dstImage类型为VK_IMAGE_TYPE_3D，则pRegions中的每个元素，extent.depth必须等于srcSubresource.layerCount
		35.如果dstImage类型为VK_IMAGE_TYPE_2D，且srcImage类型为VK_IMAGE_TYPE_3D，则pRegions中的每个元素，extent.depth必须等于dstSubresource.layerCount
		36.对于pRegions的每个元素，dstOffset.x以及(extent.width + dstOffset.x)必须同时大于等于0且小于等于dstImage指定的subresource的width,  dstOffset.y以及(extent.height + dstOffset.y)必须同时大于等于0且小于等于dstImage指定的subresource的height
		37.如果dstImage类型为VK_IMAGE_TYPE_1D，则对pRegions的每个元素，dstOffset.y必须等于0且extent.height必须为1
		38.如果dstImage类型为VK_IMAGE_TYPE_3D，则对pRegions的每个元素，dstOffset.z和(extent.depth + dstOffset.z)必须同时大于等于0且小于等于dstImage指定的subresource的depth
		39.对pRegions的每个元素，srcOffset.x必须为srcImage的VkFormat的 texel block extent width的倍数，  srcOffset.y必须为srcImage的VkFormat的 texel block extent height的倍数,srcOffset.z必须为srcImage的VkFormat的 texel block extent depth的倍数
		40.对pRegions的每个元素，dstOffset.x必须为dstImage的VkFormat的 texel block extent width的倍数，  dstOffset.y必须为dstImage的VkFormat的 texel block extent height的倍数,dstOffset.z必须为dstImage的VkFormat的 texel block extent depth的倍数
		41.对pRegions的每个元素，则（1）如果srcOffset.x + extent.width不等于srcSubresource指定的subresource的width，则extent.width必须为srcImage的VkFormat的 texel block extent width的倍数，
								   （2）如果srcOffset.y + extent.height不等于srcSubresource指定的subresource的height，则extent.height必须为srcImage的VkFormat的 texel block extent height的倍数，
								   （3）如果srcOffset.z + extent.depth不等于srcSubresource指定的subresource的depth，则extent.depth必须为srcImage的VkFormat的 texel block extent depth的倍数
		42.对pRegions的每个元素，则（1）如果dstOffset.x + extent.width不等于dstSubresource指定的subresource的width，则extent.width必须为dstImage的VkFormat的 texel block extent width的倍数，
								   （2）如果dstOffset.y + extent.height不等于dstSubresource指定的subresource的height，则extent.height必须为dstImage的VkFormat的 texel block extent height的倍数，
								   （3）如果dstOffset.z + extent.depth不等于dstSubresource指定的subresource的depth，则extent.depth必须为dstImage的VkFormat的 texel block extent depth的倍数
		43.如果pRegions中任何元素的aspect包含任何除VK_IMAGE_ASPECT_STENCIL_BIT之外的mask或者srcImage不以一个separate stencil usage创建（含一个相关结构体在pNext中），则VK_IMAGE_USAGE_TRANSFER_SRC_BIT必须包含在创建srcImage的VkImageCreateInfo::usage中
		44.如果pRegions中任何元素的aspect包含任何除VK_IMAGE_ASPECT_STENCIL_BIT之外的mask或者dstImage不以一个separate stencil usage创建（含一个相关结构体在pNext中），则VK_IMAGE_USAGE_TRANSFER_DST_BIT必须包含在创建dstImage的VkImageCreateInfo::usage中
		45.如果pRegions中任何元素的aspect包含VK_IMAGE_ASPECT_STENCIL_BIT 且srcImage以一个separate stencil usage创建（含一个相关结构体在pNext中），则VK_IMAGE_USAGE_TRANSFER_SRC_BIT必须包含在创建srcImage的VkImageStencilUsageCreateInfo::stencilUsage中
		46.如果pRegions中任何元素的aspect包含VK_IMAGE_ASPECT_STENCIL_BIT 且dstImage以一个separate stencil usage创建（含一个相关结构体在pNext中），则VK_IMAGE_USAGE_TRANSFER_DST_BIT必须包含在创建dstImage的VkImageStencilUsageCreateInfo::stencilUsage中
		47.如果srcImage为 non-sparse的则image或者指定的disjoint plane必须已经绑定到完整的连续的单独的VkDeviceMemory上
		48.pRegions的每个元素的srcSubresource.mipLevel必须小于创建srcImage的VkImageCreateInfo指定的mipLevels
		49.如果pRegions的每个元素的srcSubresource.layerCount不为VK_REMAINING_ARRAY_LAYERS，则该元素的srcSubresource.baseArrayLayer + srcSubresource.layerCount 必须小于等于创建srcImage的VkImageCreateInfo指定的arrayLayers
		50.srcImage不能以VK_IMAGE_CREATE_SUBSAMPLED_BIT_EXT创建
		51.如果dstImage为 non-sparse的则image或者指定的disjoint plane必须已经绑定到完整的连续的单独的VkDeviceMemory上
		52.pRegions的每个元素的dstSubresource.mipLevel必须小于创建dstImage的VkImageCreateInfo指定的mipLevels
		53.如果pRegions的每个元素的dstSubresource.layerCount不为VK_REMAINING_ARRAY_LAYERS，则该元素的dstSubresource.baseArrayLayer + dstSubresource.layerCount 必须小于等于创建dstImage的VkImageCreateInfo指定的arrayLayers
		54.dstImage不能以VK_IMAGE_CREATE_SUBSAMPLED_BIT_EXT创建
		
		*/



		//images间拷贝，等同于vkCmdCopyImage2KHR
		vkCmdCopyImage2(commandBuffer, &copyImageInfo2);
		/*
		vkCmdCopyImage2有效用法:
		1.如果commandBuffer为unprotected command buffer，且不支持protectedNoFault，则srcImage,dstImage不能为一个protected image
		2.如果commandBuffer为protected command buffer，且不支持protectedNoFault，则dstImage不能为一个unprotected image
		*/

	}


}



NS_TEST_END