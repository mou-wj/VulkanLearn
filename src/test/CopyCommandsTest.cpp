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

void CopyCommandsTest::CommonCopyCommandsTest()
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
		VkImageCopy2 copyImage2{};//等价于VkImageCopy2KHR
		{
			copyImage2.sType = VK_STRUCTURE_TYPE_IMAGE_COPY_2;
			copyImage2.pNext = nullptr;
			copyImage2.srcOffset = VkOffset3D{ .x = 0,.y = 0,.z = 0 };//source image中的x，y，z的基于texel的偏移量
			copyImage2.srcSubresource = VkImageSubresourceLayers{/*假设这是一个有效的VkImageSubresourceLayers，参见前面对VkImageSubresourceLayers的描述*/ };//指明source image的subresource的 VkImageSubresourceLayers
			copyImage2.dstOffset = VkOffset3D{ .x = 0,.y = 0,.z = 0 };//destination image中的x，y，z的基于texel的偏移量
			copyImage2.dstSubresource = VkImageSubresourceLayers{/*假设这是一个有效的VkImageSubresourceLayers，参见前面对VkImageSubresourceLayers的描述*/ };//指明destination image的subresource的 VkImageSubresourceLayers
			copyImage2.extent = VkExtent3D{ .width = 1,.height = 1,.depth = 1 };//是要拷贝的image 基于texel的width, height 以及 depth.
			/*
			VkImageCopy2有效用法:
			1.如果VK_KHR_sampler_ycbcr_conversion 拓展没有开启，且VkPhysicalDeviceProperties::apiVersion小于Vulkan 1.1,则srcSubresource 以及 dstSubresource的aspectMask，layerCount必须匹配
			2.extent.width，extent.height，extent.depth 不能为0
			*/

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




	// Copying Data Between Buffers and Images 参见p1648
	{}
	{
		//在buffer和image之间拷贝数据，拷贝以whole texel blocks为基本单位  参见p1649 - p1652

		//拷贝buffer 到image
		{
			VkBuffer srcBuffer{/*假设这是一个有效的VkBuffer*/ };
			VkImage dstImage{/*假设这是一个有效的VkImage*/ };
			VkBufferImageCopy bufferImageCopyRegion{};
			bufferImageCopyRegion.bufferImageHeight = 1;//指定包含texel的子区域的高度，控制地址计算，如果为0，则imageExtent该维度是紧密排列的
			bufferImageCopyRegion.bufferOffset = 0;//是buffer中的起始字节偏移量
			bufferImageCopyRegion.bufferRowLength = 1;//指定包含texel的子区域的宽度，控制地址计算，如果为0，则imageExtent该维度是紧密排列的
			bufferImageCopyRegion.imageExtent = VkExtent3D{ .width = 1,.height = 1,.depth = 1 };////选择image的texel子区域的width，height，depth的大小
			bufferImageCopyRegion.imageOffset = VkOffset3D{ .x = 0,.y = 0,.z = 0 };//选择image的texel子区域的x，y，z偏移值
			bufferImageCopyRegion.imageSubresource = VkImageSubresourceLayers //指明destination image的subresource的 VkImageSubresourceLayers
			{
				.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT,//是 VkImageAspectFlagBits组合值位掩码，指明要拷贝的color, depth 以及/或者 stencil aspects
				.mipLevel = 0,//要拷贝的mipmap level
				.baseArrayLayer = 0,//要拷贝的第一个layer
				.layerCount = 1//要拷贝的layer的个数 
			};
			/*
			VkBufferImageCopy有效用法:
			1.bufferRowLength 必须为0，或者等于大于等于imageExtent的width
			2.bufferImageHeight 必须为0，或者等于大于等于imageExtent的height
			3.imageSubresource.aspectMask只能含有一个比特设置
			4.imageExtent.width，imageExtent.height，imageExtent.depth不能为0
			*/



			//拷贝buffer到image  
			vkCmdCopyBufferToImage(commandBuffer, srcBuffer/*srcBuffer,指明source VkBuffer*/, dstImage/*dstImage，指明destination VkImage*/, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL/*dstImageLayout , destination image 的subresources 的layout*/,
				1/*regionCount，要拷贝的区域数*/, &bufferImageCopyRegion/*pRegions，一组 VkBufferImageCopy 数组指针，指明要拷贝的区域*/);
			/*
			vkCmdCopyBufferToImage有效用法:
			1.如果dstImage 为non-sparse的或者指定的disjoint plane 必须已经绑定到一个完整的连续的单独的VkDeviceMemory上
			2.pRegions的每个元素的imageSubresource.mipLevel必须小于创建dstImage的VkImageCreateInfo指定的mipLevels
			3.如果pRegions的每个元素的imageSubresource.layerCount不为VK_REMAINING_ARRAY_LAYERS，则该元素的imageSubresource.baseArrayLayer + imageSubresource.layerCount 必须小于等于创建dstImage的VkImageCreateInfo指定的arrayLayers
			4.dstImage不能以VK_IMAGE_CREATE_SUBSAMPLED_BIT_EXT创建
			5.pRegions的每个元素指定的image region必须包含在dstImage的imageSubresource指定的subresource范围内
			6.对pRegions的每个元素的，imageOffset.x以及(imageExtent.width + imageOffset.x)必须同时大于等于0且小于等于dstImage指定的imageSubresource的width,  imageOffset.y以及(imageExtent.height + imageExtent.y)必须同时大于等于0且小于等于dstImage指定的imageSubresource的height，
						imageOffset.z以及(imageExtent.depth + imageOffset.z)必须同时大于等于0且小于等于dstImage指定的imageSubresource的depth
			7.dstImage的sample count 必须为 VK_SAMPLE_COUNT_1_BIT
			8.如果commandBuffer为unprotected command buffer，且不支持protectedNoFault，则srcBuffer 不能是一个protected buffer,dstImage不能为一个protected image
			9.如果commandBuffer为protected command buffer，且不支持protectedNoFault，则dstImage不能为一个unprotected image
			10.如果commandBuffer所在的VkCommandPool的队列族不支持VK_QUEUE_GRAPHICS_BIT 或者VK_QUEUE_COMPUTE_BIT，则pRegions的任何元素的bufferOffset必须是4的倍数
			11.pRegions中每个元素的imageOffset和imageExtent必须符合commandBuffer所在的VkCommandPool的队列族的image的transfer granularity requirements，参见VkQueueFamilyProperties
			12.如果commandBuffer所在的VkCommandPool的队列族不支持VK_QUEUE_GRAPHICS_BIT，则对于pRegions中的每个元素，其imageSubresource.aspectMask不能为VK_IMAGE_ASPECT_DEPTH_BIT 或者VK_IMAGE_ASPECT_STENCIL_BIT
			13.对于pRegions中每个元素， srcBuffer必须足够大以能够供  Buffer 和 Image Addressing访问
			14.pRegions的元素指明的source region的并集以及destination region的并集不能在内存上有重叠
			15.srcBuffer必须以VK_BUFFER_USAGE_TRANSFER_SRC_BIT 创建
			16.dstImage的format features必须包含VK_FORMAT_FEATURE_TRANSFER_DST_BIT
			17.如果srcBuffer 为non-sparse的则其必须已经绑定到一个完整的连续的单独的VkDeviceMemory上
			18.dstImage必须以VK_IMAGE_USAGE_TRANSFER_DST_BIT 创建
			19.dstImageLayout必须指明在这个命令执行在VkDevice上时pRegions中dstImage的subresources的layout
			20.dstImageLayout必须为VK_IMAGE_LAYOUT_SHARED_PRESENT_KHR, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, 或者 VK_IMAGE_LAYOUT_GENERAL
			21.如果VK_EXT_depth_range_unrestricted 没有开启，则pRegions中的每个imageSubresource包含depth aspect的元素，其srcBuffer中的值必须在[0,1]范围内
			22.如果dstImage类型为VK_IMAGE_TYPE_1D，则对pRegions的每个元素，imageOffset.y必须等于0且imageExtent.height必须为1
			23.如果dstImage的类型为VK_IMAGE_TYPE_1D 或者 VK_IMAGE_TYPE_2D，则pRegions的每个元素的imageOffset.z必须等于0且imageExtent.depth必须为1
			24.对pRegions的每个元素，imageOffset.x必须为dstImage的VkFormat的 texel block extent width的倍数，  imageOffset.y必须为dstImage的VkFormat的 texel block extent height的倍数, imageOffset.z必须为dstImage的VkFormat的 texel block extent depth的倍数
			25.对pRegions的每个元素，则（1）如果imageOffset.x + extent.width不等于srcSubresource指定的subresource的width，则extent.width必须为dstImage的VkFormat的 texel block extent width的倍数，
									   （2）如果imageOffset.y + extent.height不等于srcSubresource指定的subresource的height，则extent.height必须为dstImage的VkFormat的 texel block extent height的倍数，
									   （3）如果imageOffset.z + extent.depth不等于srcSubresource指定的subresource的depth，则extent.depth必须为dstImage的VkFormat的 texel block extent depth的倍数
			26.pRegions的每个元素，imageSubresource.aspectMask必须指明dstImage中的aspects
			27.如果dstImage含有一个multi-planar image format，则pRegions中每个元素的imageSubresource.aspectMask必须是一个单独有效的multi-planar aspect mask bit
			28.如果dstImage类型为VK_IMAGE_TYPE_3D，则pRegions的每个元素，imageSubresource.baseArrayLayer必须为0，且imageSubresource.layerCount必须为1
			29.对于pRegions的每个元素，bufferRowLength 必须是dstImage的VkFormat的 texel block extent width的倍数，bufferImageHeight 必须是dstImage的VkFormat的 texel block extent height的倍数
			30.对于pRegions的每个元素，bufferRowLength除以texel block extent width 然后乘以 dstImage的texel block size 必须小于等于pow(2,31) -1
			31.如果dstImage 既不含一个depth/stencil format 又不含一个multi-planar format，则对pRegions的每个元素，bufferOffset 必须是texel block size的倍数
			32.如果dstImage 含一个multi-planar format，则对pRegions的每个元素，bufferOffset 必须是和imageSubresource 的format 和 aspectMask兼容的format的元素大小的倍数，参见 Compatible Formats of Planes of Multi-Planar Formats p4057
			33.如果dstImage 含一个depth/stencil format，则对pRegions的任何元素，bufferOffset 必须是4的倍数
			*/


			VkCopyBufferToImageInfo2 bufferImageCopyInfo2{};//等价于VkCopyBufferToImageInfo2KHR
			bufferImageCopyInfo2.sType = VK_STRUCTURE_TYPE_COPY_BUFFER_TO_IMAGE_INFO_2;
			bufferImageCopyInfo2.pNext = nullptr;
			bufferImageCopyInfo2.srcBuffer = srcBuffer;//指明source buffer
			bufferImageCopyInfo2.dstImage = dstImage;//指明destination image
			bufferImageCopyInfo2.dstImageLayout = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;//指明image 的subresources的layout
			bufferImageCopyInfo2.regionCount = 1;//指明要拷贝的区域个数
			VkBufferImageCopy2 bufferImageCopyRegion2{};//等价于VkCopyBufferToImageInfo2KHR
			{
				bufferImageCopyRegion2.sType = VK_STRUCTURE_TYPE_BUFFER_IMAGE_COPY_2;
				VkCopyCommandTransformInfoQCOM copyCommandTransformInfoQCOM{};//指明拷贝命令中的旋转信息
				{
					copyCommandTransformInfoQCOM.sType = VK_STRUCTURE_TYPE_COPY_COMMAND_TRANSFORM_INFO_QCOM;
					copyCommandTransformInfoQCOM.pNext = nullptr;
					copyCommandTransformInfoQCOM.transform = VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR;//只能为VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR, VK_SURFACE_TRANSFORM_ROTATE_90_BIT_KHR, VK_SURFACE_TRANSFORM_ROTATE_180_BIT_KHR, 或者VK_SURFACE_TRANSFORM_ROTATE_270_BIT_KHR
				}

				bufferImageCopyRegion2.pNext = &copyCommandTransformInfoQCOM;//可以包含一个VkCopyCommandTransformInfoQCOM
				bufferImageCopyRegion2.bufferImageHeight = 1;//指定包含texel的子区域的高度，控制地址计算，如果为0，则imageExtent该维度是紧密排列的
				bufferImageCopyRegion2.bufferOffset = 0;//是buffer中的起始字节偏移量
				bufferImageCopyRegion2.bufferRowLength = 1;//指定包含texel的子区域的宽度，控制地址计算，如果为0，则imageExtent该维度是紧密排列的
				bufferImageCopyRegion2.imageExtent = VkExtent3D{ .width = 1,.height = 1,.depth = 1 };////选择image的texel子区域的width，height，depth的大小
				bufferImageCopyRegion2.imageOffset = VkOffset3D{ .x = 0,.y = 0,.z = 0 };//image中的x，y，z的基于texel的偏移量
				bufferImageCopyRegion2.imageSubresource = VkImageSubresourceLayers //指明image的subresource的 VkImageSubresourceLayers
				{
					.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT,//是 VkImageAspectFlagBits组合值位掩码，指明要拷贝的color, depth 以及/或者 stencil aspects
					.mipLevel = 0,//要拷贝的mipmap level
					.baseArrayLayer = 0,//要拷贝的第一个layer
					.layerCount = 1//要拷贝的layer的个数 
				};
				/*

				VkBufferImageCopy2有效用法:
				1.bufferRowLength 必须为0，或者等于大于等于imageExtent的width
				2.bufferImageHeight 必须为0，或者等于大于等于imageExtent的height
				3.imageSubresource.aspectMask只能含有一个比特设置
				4.imageExtent.width，imageExtent.height，imageExtent.depth不能为0
				*/
			}
			bufferImageCopyInfo2.pRegions = &bufferImageCopyRegion2;//一组VkBufferImageCopy2 数组指针，指明要拷贝的区域
			/*
			VkCopyBufferToImageInfo2有效用法:
			1.如果pRegions中的每个元素的pNext中不包含VkCopyCommandTransformInfoQCOM，则元素指明的image region必须包含在dstImage的imageSubresource 指明的范围中
			2.如果pRegions中的每个元素的pNext中包含VkCopyCommandTransformInfoQCOM，则rotated destination region 必须包含在dstImage的imageSubresource 指明的范围中，参见p1650 [copies-buffers-images-rotation-addressing]
			3.如果pRegions中的任何元素的pNext中包含VkCopyCommandTransformInfoQCOM，则dstImage必须有1x1x1 texel block extent，dstImage 的类型必须为VK_IMAGE_TYPE_2D，dstImage不能有一个multi-planar format
			4.对于pRegions中每个元素， srcBuffer必须足够大以能够供  Buffer 和 Image Addressing访问
			5.pRegions的元素指明的source region的并集以及destination region的并集不能在内存上有重叠
			6.srcBuffer必须以VK_BUFFER_USAGE_TRANSFER_SRC_BIT 创建
			7.dstImage的format features必须包含VK_FORMAT_FEATURE_TRANSFER_DST_BIT
			8.如果srcBuffer 为non-sparse的则其必须已经绑定到一个完整的连续的单独的VkDeviceMemory上
			9.dstImage必须以VK_IMAGE_USAGE_TRANSFER_DST_BIT 创建
			10.dstImageLayout必须指明在这个命令执行在VkDevice上时pRegions中dstImage的subresources的layout
			10.dstImageLayout必须为VK_IMAGE_LAYOUT_SHARED_PRESENT_KHR, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, 或者 VK_IMAGE_LAYOUT_GENERAL
			11.如果VK_EXT_depth_range_unrestricted 没有开启，则pRegions中的每个imageSubresource包含depth aspect的元素，其srcBuffer中的值必须在[0,1]范围内
			12.如果dstImage 为non-sparse或者 disjoint plane的image 或plane必须已经绑定到一个完整的连续的单独的VkDeviceMemory上
			13.pRegions的每个元素的imageSubresource.mipLevel必须小于创建dstImage的VkImageCreateInfo指定的mipLevels
			14.如果pRegions的每个元素的imageSubresource.layerCount不为VK_REMAINING_ARRAY_LAYERS，则该元素的imageSubresource.baseArrayLayer + imageSubresource.layerCount 必须小于等于创建dstImage的VkImageCreateInfo指定的arrayLayers
			15.dstImage不能以VK_IMAGE_CREATE_SUBSAMPLED_BIT_EXT创建
			16.dstImage的sample count 必须为 VK_SAMPLE_COUNT_1_BIT
			17.如果dstImage类型为VK_IMAGE_TYPE_1D，则对pRegions的每个元素，imageOffset.y必须等于0且imageExtent.height必须为1
			18.对pRegions的每个元素的，imageOffset.z以及(imageExtent.depth + imageOffset.z)必须同时大于等于0且小于等于dstImage指定的imageSubresource的depth
			19.如果dstImage的类型为VK_IMAGE_TYPE_1D 或者 VK_IMAGE_TYPE_2D，则pRegions的每个元素的imageOffset.z必须等于0且imageExtent.depth必须为1
			20.对pRegions的每个元素，imageOffset.x必须为dstImage的VkFormat的 texel block extent width的倍数，  imageOffset.y必须为dstImage的VkFormat的 texel block extent height的倍数, imageOffset.z必须为dstImage的VkFormat的 texel block extent depth的倍数
			21.对pRegions的每个元素，则（1）如果imageOffset.x + extent.width不等于srcSubresource指定的subresource的width，则extent.width必须为dstImage的VkFormat的 texel block extent width的倍数，
									   （2）如果imageOffset.y + extent.height不等于srcSubresource指定的subresource的height，则extent.height必须为dstImage的VkFormat的 texel block extent height的倍数，
									   （3）如果imageOffset.z + extent.depth不等于srcSubresource指定的subresource的depth，则extent.depth必须为dstImage的VkFormat的 texel block extent depth的倍数
			22.pRegions的每个元素，imageSubresource.aspectMask必须指明dstImage中的aspects
			23.如果dstImage含有一个multi-planar image format，则pRegions中每个元素的imageSubresource.aspectMask必须是一个单独有效的multi-planar aspect mask bit
			24.如果dstImage类型为VK_IMAGE_TYPE_3D，则pRegions的每个元素，imageSubresource.baseArrayLayer必须为0，且imageSubresource.layerCount必须为1
			25.对于pRegions的每个元素，bufferRowLength 必须是dstImage的VkFormat的 texel block extent width的倍数，bufferImageHeight 必须是dstImage的VkFormat的 texel block extent height的倍数
			26.对于pRegions的每个元素，bufferRowLength除以texel block extent width 然后乘以 dstImage的texel block size 必须小于等于pow(2,31) -1
			27.如果dstImage 既不含一个depth/stencil format 又不含一个multi-planar format，则对pRegions的每个元素，bufferOffset 必须是texel block size的倍数
			28.如果dstImage 含一个multi-planar format，则对pRegions的每个元素，bufferOffset 必须是和imageSubresource 的format 和 aspectMask兼容的format的元素大小的倍数，参见 Compatible Formats of Planes of Multi-Planar Formats p4057
			29.如果dstImage 含一个depth/stencil format，则对pRegions的任何元素，bufferOffset 必须是4的倍数
			30.对于pRegions中每个pNext中不含VkCopyCommandTransformInfoQCOM的元素，imageOffset.x以及(imageExtent.width + imageOffset.x)必须同时大于等于0且小于等于dstImage指定的imageSubresource的width,  imageOffset.y以及(imageExtent.height + imageExtent.y)必须同时大于等于0且小于等于dstImage指定的imageSubresource的height
			*/


			//拷贝buffer 到image 等价于 vkCmdCopyBufferToImage2KHR
			vkCmdCopyBufferToImage2(commandBuffer, &bufferImageCopyInfo2);
			/*
			vkCmdCopyBufferToImage2有效用法:
			1.如果commandBuffer为unprotected command buffer，且不支持protectedNoFault，则srcBuffer 不能是一个protected buffer,dstImage不能为一个protected image
			2.如果commandBuffer为protected command buffer，且不支持protectedNoFault，则dstImage不能为一个unprotected image
			3.如果commandBuffer所在的VkCommandPool的队列族不支持VK_QUEUE_GRAPHICS_BIT 或者VK_QUEUE_COMPUTE_BIT，则pCopyBufferToImageInfo->pRegions的任何元素的bufferOffset必须是4的倍数
			4.pCopyBufferToImageInfo->pRegions中每个元素的imageOffset和imageExtent必须符合commandBuffer所在的VkCommandPool的队列族的image的transfer granularity requirements，参见VkQueueFamilyProperties
			5.如果commandBuffer所在的VkCommandPool的队列族不支持VK_QUEUE_GRAPHICS_BIT，则对于pCopyBufferToImageInfo->pRegions中的每个元素，其imageSubresource.aspectMask不能为VK_IMAGE_ASPECT_DEPTH_BIT 或者VK_IMAGE_ASPECT_STENCIL_BIT
			*/


		}



		//拷贝image 到buffer
		{
			VkImage srcImage{/*假设这是一个有效的VkImage*/ };
			VkBuffer dstBuffer{/*假设这是一个有效的VkBuffer*/ };

			VkBufferImageCopy imageBufferCopyRegion{};
			imageBufferCopyRegion.bufferImageHeight = 1;
			imageBufferCopyRegion.bufferOffset = 0;
			imageBufferCopyRegion.bufferRowLength = 1;
			imageBufferCopyRegion.imageExtent = VkExtent3D{ .width = 1,.height = 1,.depth = 1 };
			imageBufferCopyRegion.imageOffset = VkOffset3D{ .x = 0,.y = 0,.z = 0 };
			imageBufferCopyRegion.imageSubresource = VkImageSubresourceLayers //指明source image的subresource的 VkImageSubresourceLayers
			{
				.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT,//是 VkImageAspectFlagBits组合值位掩码，指明要拷贝的color, depth 以及/或者 stencil aspects
				.mipLevel = 0,//要拷贝的mipmap level
				.baseArrayLayer = 0,//要拷贝的第一个layer
				.layerCount = 1//要拷贝的layer的个数 
			};


			//拷贝image到buffer

			vkCmdCopyImageToBuffer(commandBuffer, srcImage/*srcImage，指明source VkImage*/, VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL/*srcImageLayout , source image 的subresources 的layout*/,
				dstBuffer/*dstBuffer,指明destination VkBuffer*/, 1/*regionCount，要拷贝的区域数*/, &imageBufferCopyRegion/*pRegions，一组 VkBufferImageCopy 数组指针，指明要拷贝的区域*/);
			/*
			vkCmdCopyImageToBuffer有效用法:
			1.如果srcImage 为non-sparse的或者指定的disjoint plane 必须已经绑定到一个完整的连续的单独的VkDeviceMemory上
			2.pRegions的每个元素的imageSubresource.mipLevel必须小于创建srcImage的VkImageCreateInfo指定的mipLevels
			3.如果pRegions的每个元素的imageSubresource.layerCount不为VK_REMAINING_ARRAY_LAYERS，则该元素的imageSubresource.baseArrayLayer + imageSubresource.layerCount 必须小于等于创建srcImage的VkImageCreateInfo指定的arrayLayers
			4.srcImage不能以VK_IMAGE_CREATE_SUBSAMPLED_BIT_EXT创建
			5.pRegions的每个元素指定的image region必须包含在srcImage的imageSubresource指定的subresource范围内
			6.对pRegions的每个元素的，imageOffset.x以及(imageExtent.width + imageOffset.x)必须同时大于等于0且小于等于srcImage指定的imageSubresource的width,  imageOffset.y以及(imageExtent.height + imageExtent.y)必须同时大于等于0且小于等于srcImage指定的imageSubresource的height，
						imageOffset.z以及(imageExtent.depth + imageOffset.z)必须同时大于等于0且小于等于srcImage指定的imageSubresource的depth
			7.srcImage的sample count 必须为 VK_SAMPLE_COUNT_1_BIT
			8.如果commandBuffer为unprotected command buffer，且不支持protectedNoFault，则dstBuffer 不能是一个protected buffer,srcImage不能为一个protected image
			9.如果commandBuffer为protected command buffer，且不支持protectedNoFault，则dstBuffer不能为一个unprotected buffer
			10.如果commandBuffer所在的VkCommandPool的队列族不支持VK_QUEUE_GRAPHICS_BIT 或者VK_QUEUE_COMPUTE_BIT，则pRegions的任何元素的bufferOffset必须是4的倍数
			11.pRegions中每个元素的imageOffset和imageExtent必须符合commandBuffer所在的VkCommandPool的队列族的image的transfer granularity requirements，参见VkQueueFamilyProperties
			12.如果commandBuffer所在的VkCommandPool的队列族不支持VK_QUEUE_GRAPHICS_BIT，则对于pRegions中的每个元素，其imageSubresource.aspectMask不能为VK_IMAGE_ASPECT_DEPTH_BIT 或者VK_IMAGE_ASPECT_STENCIL_BIT
			13.对于pRegions中每个元素， dstBuffer必须足够大以能够供  Buffer 和 Image Addressing访问
			14.pRegions的元素指明的source region的并集以及destination region的并集不能在内存上有重叠
			15.srcImage必须以VK_IMAGE_USAGE_TRANSFER_SRC_BIT 创建
			16.srcImage的format features必须包含VK_FORMAT_FEATURE_TRANSFER_SRC_BIT
			17.dstBuffer必须以VK_BUFFER_USAGE_TRANSFER_DST_BIT 创建
			18.如果dstBuffer 为non-sparse的则其必须已经绑定到一个完整的连续的单独的VkDeviceMemory上
			19.srcImageLayout必须指明在这个命令执行在VkDevice上时pRegions中srcImage的subresources的layout
			20.srcImageLayout必须为VK_IMAGE_LAYOUT_SHARED_PRESENT_KHR, VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL, 或者 VK_IMAGE_LAYOUT_GENERAL
			21.如果srcImage类型为VK_IMAGE_TYPE_1D，则对pRegions的每个元素，imageOffset.y必须等于0且imageExtent.height必须为1
			22.如果srcImage的类型为VK_IMAGE_TYPE_1D 或者 VK_IMAGE_TYPE_2D，则pRegions的每个元素的imageOffset.z必须等于0且imageExtent.depth必须为1
			23.对pRegions的每个元素，imageOffset.x必须为srcImage的VkFormat的 texel block extent width的倍数，  imageOffset.y必须为srcImage的VkFormat的 texel block extent height的倍数, imageOffset.z必须为srcImage的VkFormat的 texel block extent depth的倍数
			24.对pRegions的每个元素，则（1）如果imageOffset.x + extent.width不等于srcSubresource指定的subresource的width，则extent.width必须为srcImage的VkFormat的 texel block extent width的倍数，
									   （2）如果imageOffset.y + extent.height不等于srcSubresource指定的subresource的height，则extent.height必须为srcImage的VkFormat的 texel block extent height的倍数，
									   （3）如果imageOffset.z + extent.depth不等于srcSubresource指定的subresource的depth，则extent.depth必须为srcImage的VkFormat的 texel block extent depth的倍数
			25.pRegions的每个元素，imageSubresource.aspectMask必须指明srcImage中的aspects
			26.如果srcImage含有一个multi-planar image format，则pRegions中每个元素的imageSubresource.aspectMask必须是一个单独有效的multi-planar aspect mask bit
			27.如果srcImage类型为VK_IMAGE_TYPE_3D，则pRegions的每个元素，imageSubresource.baseArrayLayer必须为0，且imageSubresource.layerCount必须为1
			28.对于pRegions的每个元素，bufferRowLength 必须是srcImage的VkFormat的 texel block extent width的倍数，bufferImageHeight 必须是srcImage的VkFormat的 texel block extent height的倍数
			29.对于pRegions的每个元素，bufferRowLength除以texel block extent width 然后乘以 srcImage的texel block size 必须小于等于pow(2,31) -1
			30.如果srcImage 既不含一个depth/stencil format 又不含一个multi-planar format，则对pRegions的每个元素，bufferOffset 必须是texel block size的倍数
			31.如果srcImage 含一个multi-planar format，则对pRegions的每个元素，bufferOffset 必须是和imageSubresource 的format 和 aspectMask兼容的format的元素大小的倍数，参见 Compatible Formats of Planes of Multi-Planar Formats p4057
			32.如果srcImage 含一个depth/stencil format，则对pRegions的任何元素，bufferOffset 必须是4的倍数

			*/




			VkCopyImageToBufferInfo2 imageBufferCopyInfo2{};//等价于VkCopyImageToBufferInfo2KHR
			imageBufferCopyInfo2.sType = VK_STRUCTURE_TYPE_COPY_IMAGE_TO_BUFFER_INFO_2;
			imageBufferCopyInfo2.pNext = nullptr;
			imageBufferCopyInfo2.srcImage = srcImage;//指定source image
			imageBufferCopyInfo2.srcImageLayout = VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL;//指定source image的subresources的layout
			imageBufferCopyInfo2.dstBuffer = dstBuffer;//指定destination buffer
			imageBufferCopyInfo2.regionCount = 1;//指定要拷贝的区域数量
			VkBufferImageCopy2 imageBufferCopyRegion2{};//等价于VkCopyBufferToImageInfo2KHR
			{
				imageBufferCopyRegion2.sType = VK_STRUCTURE_TYPE_BUFFER_IMAGE_COPY_2;
				imageBufferCopyRegion2.pNext = nullptr;
				imageBufferCopyRegion2.bufferImageHeight = 1;//指定包含texel的子区域的高度，控制地址计算，如果为0，则imageExtent该维度是紧密排列的
				imageBufferCopyRegion2.bufferOffset = 0;//是buffer中的起始字节偏移量
				imageBufferCopyRegion2.bufferRowLength = 1;//指定包含texel的子区域的宽度，控制地址计算，如果为0，则imageExtent该维度是紧密排列的
				imageBufferCopyRegion2.imageExtent = VkExtent3D{ .width = 1,.height = 1,.depth = 1 };////选择image的texel子区域的width，height，depth的大小
				imageBufferCopyRegion2.imageOffset = VkOffset3D{ .x = 0,.y = 0,.z = 0 };//image中的x，y，z的基于texel的偏移量
				imageBufferCopyRegion2.imageSubresource = VkImageSubresourceLayers //指明image的subresource的 VkImageSubresourceLayers
				{
					.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT,//是 VkImageAspectFlagBits组合值位掩码，指明要拷贝的color, depth 以及/或者 stencil aspects
					.mipLevel = 0,//要拷贝的mipmap level
					.baseArrayLayer = 0,//要拷贝的第一个layer
					.layerCount = 1//要拷贝的layer的个数 
				};
			}
			imageBufferCopyInfo2.pRegions = &imageBufferCopyRegion2;//一组VkBufferImageCopy2 数组指针，指明要拷贝的区域
			/*
			VkCopyImageToBufferInfo2有效用法:
			1.如果pRegions中的每个元素的pNext中不包含VkCopyCommandTransformInfoQCOM，则元素指明的image region必须包含在srcImage的imageSubresource 指明的范围中
			2.如果pRegions中的每个元素的pNext中包含VkCopyCommandTransformInfoQCOM，则rotated destination region 必须包含在srcImage的imageSubresource 指明的范围中，参见p1650 [copies-buffers-images-rotation-addressing]
			3.如果pRegions中的任何元素的pNext中包含VkCopyCommandTransformInfoQCOM，则srcImage必须有1x1x1 texel block extent，srcImage 的类型必须为VK_IMAGE_TYPE_2D，srcImage不能有一个multi-planar format
			4.对于pRegions中每个元素， dstBuffer必须足够大以能够供  Buffer 和 Image Addressing访问
			5.pRegions的元素指明的source region的并集以及destination region的并集不能在内存上有重叠
			6.srcImage必须以VK_IMAGE_USAGE_TRANSFER_SRC_BIT 创建
			7.srcImage的format features必须包含VK_FORMAT_FEATURE_TRANSFER_SRC_BIT
			8.dstBuffer必须以VK_BUFFER_USAGE_TRANSFER_DST_BIT 创建
			9.如果dstBuffer 为non-sparse的则其必须已经绑定到一个完整的连续的单独的VkDeviceMemory上
			10.srcImageLayout必须指明在这个命令执行在VkDevice上时pRegions中srcImage的subresources的layout
			10.srcImageLayout必须为VK_IMAGE_LAYOUT_SHARED_PRESENT_KHR, VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL, 或者 VK_IMAGE_LAYOUT_GENERAL
						11.如果VK_EXT_depth_range_unrestricted 没有开启，则pRegions中的每个imageSubresource包含depth aspect的元素，其srcBuffer中的值必须在[0,1]范围内
			11.如果srcImage 为non-sparse或者 disjoint plane的image 或plane必须已经绑定到一个完整的连续的单独的VkDeviceMemory上
			12.pRegions的每个元素的imageSubresource.mipLevel必须小于创建srcImage的VkImageCreateInfo指定的mipLevels
			13.如果pRegions的每个元素的imageSubresource.layerCount不为VK_REMAINING_ARRAY_LAYERS，则该元素的imageSubresource.baseArrayLayer + imageSubresource.layerCount 必须小于等于创建srcImage的VkImageCreateInfo指定的arrayLayers
			14.srcImage不能以VK_IMAGE_CREATE_SUBSAMPLED_BIT_EXT创建
			15.srcImage的sample count 必须为 VK_SAMPLE_COUNT_1_BIT
			16.如果srcImage类型为VK_IMAGE_TYPE_1D，则对pRegions的每个元素，imageOffset.y必须等于0且imageExtent.height必须为1
			17.对pRegions的每个元素的，imageOffset.z以及(imageExtent.depth + imageOffset.z)必须同时大于等于0且小于等于srcImage指定的imageSubresource的depth
			18.如果srcImage的类型为VK_IMAGE_TYPE_1D 或者 VK_IMAGE_TYPE_2D，则pRegions的每个元素的imageOffset.z必须等于0且imageExtent.depth必须为1
			19.对pRegions的每个元素，imageOffset.x必须为srcImage的VkFormat的 texel block extent width的倍数，  imageOffset.y必须为srcImage的VkFormat的 texel block extent height的倍数, imageOffset.z必须为srcImage的VkFormat的 texel block extent depth的倍数
			20.对pRegions的每个元素，则（1）如果imageOffset.x + extent.width不等于srcSubresource指定的subresource的width，则extent.width必须为srcImage的VkFormat的 texel block extent width的倍数，
									   （2）如果imageOffset.y + extent.height不等于srcSubresource指定的subresource的height，则extent.height必须为srcImage的VkFormat的 texel block extent height的倍数，
									   （3）如果imageOffset.z + extent.depth不等于srcSubresource指定的subresource的depth，则extent.depth必须为srcImage的VkFormat的 texel block extent depth的倍数
			21.pRegions的每个元素，imageSubresource.aspectMask必须指明srcImage中的aspects
			22.如果srcImage含有一个multi-planar image format，则pRegions中每个元素的imageSubresource.aspectMask必须是一个单独有效的multi-planar aspect mask bit
			23.如果srcImage类型为VK_IMAGE_TYPE_3D，则pRegions的每个元素，imageSubresource.baseArrayLayer必须为0，且imageSubresource.layerCount必须为1
			24.对于pRegions的每个元素，bufferRowLength 必须是srcImage的VkFormat的 texel block extent width的倍数，bufferImageHeight 必须是srcImage的VkFormat的 texel block extent height的倍数
			25.对于pRegions的每个元素，bufferRowLength除以texel block extent width 然后乘以 srcImage的texel block size 必须小于等于pow(2,31) -1
			26.如果srcImage 既不含一个depth/stencil format 又不含一个multi-planar format，则对pRegions的每个元素，bufferOffset 必须是texel block size的倍数
			27.如果srcImage 含一个multi-planar format，则对pRegions的每个元素，bufferOffset 必须是和imageSubresource 的format 和 aspectMask兼容的format的元素大小的倍数，参见 Compatible Formats of Planes of Multi-Planar Formats p4057
			28.如果srcImage 含一个depth/stencil format，则对pRegions的任何元素，bufferOffset 必须是4的倍数
			30.对于pRegions中每个pNext中不含VkCopyCommandTransformInfoQCOM的元素，imageOffset.x以及(imageExtent.width + imageOffset.x)必须同时大于等于0且小于等于srcImage指定的imageSubresource的width,  imageOffset.y以及(imageExtent.height + imageExtent.y)必须同时大于等于0且小于等于srcImage指定的imageSubresource的height
			
			*/
			
			
			
			//拷贝image到buffer   等价于vkCmdCopyImageToBuffer2KHR
			vkCmdCopyImageToBuffer2(commandBuffer, &imageBufferCopyInfo2);
			/*
			vkCmdCopyImageToBuffer2有效用法:
			1.如果commandBuffer为unprotected command buffer，且不支持protectedNoFault，则srcImage 不能是一个protected image,dstBuffer不能为一个protected buffer
			2.如果commandBuffer为protected command buffer，且不支持protectedNoFault，则dstBuffer不能为一个unprotected buffer
			3.如果commandBuffer所在的VkCommandPool的队列族不支持VK_QUEUE_GRAPHICS_BIT 或者VK_QUEUE_COMPUTE_BIT，则pCopyBufferToImageInfo->pRegions的任何元素的bufferOffset必须是4的倍数
			4.pCopyBufferToImageInfo->pRegions中每个元素的imageOffset和imageExtent必须符合commandBuffer所在的VkCommandPool的队列族的image的transfer granularity requirements，参见VkQueueFamilyProperties
			
			*/
		}


		//拷贝host memory 到image
		{
			VkImage dstImage{/*假设这是一个有效的VkImage*/ };
			void* srcHostMemoryPointer{/*假设这是一个有效的host端的内存指针*/};

			VkCopyMemoryToImageInfoEXT hostMemoryImageCopyInfoEXT{};
			hostMemoryImageCopyInfoEXT.sType = VK_STRUCTURE_TYPE_COPY_MEMORY_TO_IMAGE_INFO_EXT;
			hostMemoryImageCopyInfoEXT.pNext = nullptr;
			hostMemoryImageCopyInfoEXT.flags = VK_HOST_IMAGE_COPY_MEMCPY_EXT;/*VkHostImageCopyFlagBitsEXT组合值位掩码，指明额外拷贝参数
			VkHostImageCopyFlagBitsEXT:
			VK_HOST_IMAGE_COPY_MEMCPY_EXT:  指定在数据复制期间不应用内存布局切换,原封不动的数据拷贝？？？
			
			*/
			hostMemoryImageCopyInfoEXT.dstImage = dstImage;//指明destination image
			hostMemoryImageCopyInfoEXT.dstImageLayout = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;//指明image 的subresources的layout
			hostMemoryImageCopyInfoEXT.regionCount = 1;//指明拷贝区域的数量
			VkMemoryToImageCopyEXT memoryImageCopyRegion{};
			{
				memoryImageCopyRegion.sType = VK_STRUCTURE_TYPE_MEMORY_TO_IMAGE_COPY_EXT;
				memoryImageCopyRegion.pNext = nullptr;
				memoryImageCopyRegion.memoryImageHeight = 1;//指定包含texel的子区域的高度，控制地址计算，如果为0，则imageExtent该维度是紧密排列的
				memoryImageCopyRegion.memoryRowLength = 1;//指定包含texel的子区域的宽度，控制地址计算，如果为0，则imageExtent该维度是紧密排列的
				memoryImageCopyRegion.pHostPointer = srcHostMemoryPointer;//host端的内存地址，指明从哪里拷贝
				memoryImageCopyRegion.imageExtent = VkExtent3D{ .width = 1,.height = 1,.depth = 1 };//选择image的texel子区域的width，height，depth的大小
				memoryImageCopyRegion.imageOffset = VkOffset3D{ .x = 0,.y = 0,.z = 0 };//image中的x，y，z的基于texel的偏移量
				memoryImageCopyRegion.imageSubresource = VkImageSubresourceLayers //指明destination image的subresource的 VkImageSubresourceLayers
				{
					.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT,//是 VkImageAspectFlagBits组合值位掩码，指明要拷贝的color, depth 以及/或者 stencil aspects
					.mipLevel = 0,//要拷贝的mipmap level
					.baseArrayLayer = 0,//要拷贝的第一个layer
					.layerCount = 1//要拷贝的layer的个数 
				};
				/*
				VkMemoryToImageCopyEXT有效用法:
				1.pHostPointer必须指向一个足够Buffer and Image Addressing访问pRegions中所有元素指明的区域的host端内存地址
				2.pRegions的元素指明的source region的并集以及destination region的并集不能在内存上有重叠
				3.memoryRowLength 必须为0，或者等于大于等于imageExtent的width
				4.memoryImageHeight 必须为0，或者等于大于等于imageExtent的height
				5.imageSubresource.aspectMask只能含有一个比特设置
				6.imageExtent.width，imageExtent.height，imageExtent.depth不能为0
				*/
			}
			hostMemoryImageCopyInfoEXT.pRegions = &memoryImageCopyRegion;//一组VkMemoryToImageCopyEXT数组指针，指明要拷贝的区域
			/*
			VkCopyMemoryToImageInfoEXT有效用法:
			1.如果dstImage是sparse的，则该命令可访问的所有区域的memory range必须已经绑定了，参见Binding Resource Memory p3007
			2.如果访问的是dstImage的stencil aspect，且dstImage 不以	separate stencil usage创建，dstImage创建时的VkImageCreateInfo::usage中必须包含VK_IMAGE_USAGE_HOST_TRANSFER_BIT_EXT
			3.如果访问的是dstImage的stencil aspect，且dstImage 以 separate stencil usage创建，dstImage创建时的VkImageStencilUsageCreateInfo::stencilUsage中必须包含VK_IMAGE_USAGE_HOST_TRANSFER_BIT_EXT
			4.如果访问的是dstImage的non-stencil aspect，dstImage创建时的VkImageCreateInfo::usage中必须包含VK_IMAGE_USAGE_HOST_TRANSFER_BIT_EXT
			5.如果flags 包含VK_HOST_IMAGE_COPY_MEMCPY_EXT，则（1）pRegions的每个元素的imageOffset的x, y, 以及 z必须为0
															 （2）pRegions的每个元素的imageExtent必须等于dstImage的imageSubresource指定的subresource的维度范围
			6.如果dstImage是non-sparse的，则image 或指定的disjoint plane必须已经绑定到一个完整的连续的单独的VkDeviceMemory上
			7.pRegions的每个元素的imageSubresource.mipLevel必须小于创建dstImage的VkImageCreateInfo指定的mipLevels
			8.如果pRegions的每个元素的imageSubresource.layerCount不为VK_REMAINING_ARRAY_LAYERS，则该元素的imageSubresource.baseArrayLayer + imageSubresource.layerCount 必须小于等于创建dstImage的VkImageCreateInfo指定的arrayLayers
			9.dstImage不能以VK_IMAGE_CREATE_SUBSAMPLED_BIT_EXT创建
			10.pRegions中的每个元素指定的image region必须包含在dstImage的imageSubresource指定的subresource的范围中
			11.对pRegions的每个元素的，imageOffset.x以及(imageExtent.width + imageOffset.x)必须同时大于等于0且小于等于dstImage指定的imageSubresource的width,  imageOffset.y以及(imageExtent.height + imageExtent.y)必须同时大于等于0且小于等于dstImage指定的imageSubresource的height，
										imageOffset.z以及(imageExtent.depth + imageOffset.z)必须同时大于等于0且小于等于dstImage指定的imageSubresource的height
			12.dstImage的sample count 必须为 VK_SAMPLE_COUNT_1_BIT	
			13.如果dstImage类型为VK_IMAGE_TYPE_1D，则对pRegions的每个元素，imageOffset.y必须等于0且imageExtent.height必须为1
			14.如果dstImage的类型为VK_IMAGE_TYPE_1D 或者 VK_IMAGE_TYPE_2D，则pRegions的每个元素的imageOffset.z必须等于0且imageExtent.depth必须为1
			15.对pRegions的每个元素，imageOffset.x必须为dstImage的VkFormat的 texel block extent width的倍数，  imageOffset.y必须为dstImage的VkFormat的 texel block extent height的倍数, imageOffset.z必须为dstImage的VkFormat的 texel block extent depth的倍数
			16.对pRegions的每个元素，则（1）如果imageOffset.x + extent.width不等于srcSubresource指定的subresource的width，则extent.width必须为dstImage的VkFormat的 texel block extent width的倍数，
									   （2）如果imageOffset.y + extent.height不等于srcSubresource指定的subresource的height，则extent.height必须为dstImage的VkFormat的 texel block extent height的倍数，
									   （3）如果imageOffset.z + extent.depth不等于srcSubresource指定的subresource的depth，则extent.depth必须为dstImage的VkFormat的 texel block extent depth的倍数
			17.pRegions的每个元素，imageSubresource.aspectMask必须指明dstImage中的aspects
			18.如果dstImage含有一个multi-planar image format，则pRegions中每个元素的imageSubresource.aspectMask必须是一个单独有效的multi-planar aspect mask bit
			19.如果dstImage类型为VK_IMAGE_TYPE_3D，则pRegions的每个元素，imageSubresource.baseArrayLayer必须为0，且imageSubresource.layerCount必须为1
			20.对于pRegions的每个元素，memoryRowLength 必须是dstImage的VkFormat的 texel block extent width的倍数，memoryImageHeight 必须是dstImage的VkFormat的 texel block extent height的倍数
			21.对于pRegions的每个元素，memoryRowLength除以texel block extent width 然后乘以 dstImage的texel block size 必须小于等于pow(2,31) -1
			22.dstImageLayout必须指明当前dstImage的pRegions指明的subresources的layout
			23.dstImageLayout必须是返回的VkPhysicalDeviceHostImageCopyPropertiesEXT::pCopyDstLayouts中的一个layout
			24.如果flags包含VK_HOST_IMAGE_COPY_MEMCPY_EXT，memoryRowLength和memoryImageHeight必须同时为0
			*/
			

			//拷贝host memory到image   该命令不做安全检查，所以需要应用手动保证涉及到的区域的相关操作必须已经完成
			vkCopyMemoryToImageEXT(device, &hostMemoryImageCopyInfoEXT);// hostImageCopy 特性必须开启

		}



		//拷贝image 到host memory 
		{
			VkImage srcImage{/*假设这是一个有效的VkImage*/ };
			void* dstHostMemoryPointer{/*假设这是一个有效的指向host端内存的指针*/ };

			VkCopyImageToMemoryInfoEXT imageMemoryCopyInfo{};
			imageMemoryCopyInfo.sType = VK_STRUCTURE_TYPE_COPY_IMAGE_TO_MEMORY_INFO_EXT;
			imageMemoryCopyInfo.pNext = nullptr;
			imageMemoryCopyInfo.flags = 0;//VkHostImageCopyFlagBitsEXT组合值位掩码，控制拷贝行为
			imageMemoryCopyInfo.srcImage = srcImage;//指定source image
			imageMemoryCopyInfo.srcImageLayout = VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL;//指定source image的subresources的layout
			imageMemoryCopyInfo.regionCount = 1;//指定要拷贝的区域个数
			VkImageToMemoryCopyEXT imageMemoryCopyRegion{};
			{
				imageMemoryCopyRegion.sType = VK_STRUCTURE_TYPE_IMAGE_TO_MEMORY_COPY_EXT;
				imageMemoryCopyRegion.pNext = nullptr;
				imageMemoryCopyRegion.memoryImageHeight = 1;//指定包含texel的子区域的高度，控制地址计算，如果为0，则imageExtent该维度是紧密排列的
				imageMemoryCopyRegion.memoryRowLength = 1;//指定包含texel的子区域的宽度，控制地址计算，如果为0，则imageExtent该维度是紧密排列的
				imageMemoryCopyRegion.pHostPointer = dstHostMemoryPointer;//host端的内存地址，指明从拷贝到哪里
				imageMemoryCopyRegion.imageExtent = VkExtent3D{ .width = 1,.height = 1,.depth = 1 };//选择image的texel子区域的width，height，depth的大小
				imageMemoryCopyRegion.imageOffset = VkOffset3D{ .x = 0,.y = 0,.z = 0 };//image中的x，y，z的基于texel的偏移量
				imageMemoryCopyRegion.imageSubresource = VkImageSubresourceLayers //指明source image的subresource的 VkImageSubresourceLayers
				{
					.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT,//是 VkImageAspectFlagBits组合值位掩码，指明要拷贝的color, depth 以及/或者 stencil aspects
					.mipLevel = 0,//要拷贝的mipmap level
					.baseArrayLayer = 0,//要拷贝的第一个layer
					.layerCount = 1//要拷贝的layer的个数 
				};
				/*
				VkImageToMemoryCopyEXT有效用法:
				1.pHostPointer必须指向一个足够Buffer and Image Addressing访问pRegions中所有元素指明的区域的host端内存地址
				2.pRegions的元素指明的source region的并集以及destination region的并集不能在内存上有重叠
				3.memoryRowLength 必须为0，或者等于大于等于imageExtent的width
				4.memoryImageHeight 必须为0，或者等于大于等于imageExtent的height
				5.imageSubresource.aspectMask只能含有一个比特设置
				6.imageExtent.width，imageExtent.height，imageExtent.depth不能为0
				*/
			}
			imageMemoryCopyInfo.pRegions = &imageMemoryCopyRegion;// 一组 VkImageToMemoryCopyEXT 数组指针，指明要拷贝的区域
			/*
			VkCopyImageToMemoryInfoEXT有效用法:
			1.如果srcImage是sparse的，则该命令可访问的所有区域的memory range必须已经绑定了，参见Binding Resource Memory p3007
			2.如果访问的是srcImage的stencil aspect，且srcImage 不以	separate stencil usage创建，srcImage创建时的VkImageCreateInfo::usage中必须包含VK_IMAGE_USAGE_HOST_TRANSFER_BIT_EXT
			3.如果访问的是srcImage的stencil aspect，且srcImage 以 separate stencil usage创建，srcImage创建时的VkImageStencilUsageCreateInfo::stencilUsage中必须包含VK_IMAGE_USAGE_HOST_TRANSFER_BIT_EXT
			4.如果访问的是srcImage的non-stencil aspect，srcImage创建时的VkImageCreateInfo::usage中必须包含VK_IMAGE_USAGE_HOST_TRANSFER_BIT_EXT
			5.如果flags 包含VK_HOST_IMAGE_COPY_MEMCPY_EXT，则（1）pRegions的每个元素的imageOffset的x, y, 以及 z必须为0
															 （2）pRegions的每个元素的imageExtent必须等于srcImage的imageSubresource指定的subresource的维度范围
			6.如果srcImage是non-sparse的，则image 或指定的disjoint plane必须已经绑定到一个完整的连续的单独的VkDeviceMemory上
			7.pRegions的每个元素的imageSubresource.mipLevel必须小于创建srcImage的VkImageCreateInfo指定的mipLevels
			8.如果pRegions的每个元素的imageSubresource.layerCount不为VK_REMAINING_ARRAY_LAYERS，则该元素的imageSubresource.baseArrayLayer + imageSubresource.layerCount 必须小于等于创建srcImage的VkImageCreateInfo指定的arrayLayers
			9.srcImage不能以VK_IMAGE_CREATE_SUBSAMPLED_BIT_EXT创建
			10.pRegions中的每个元素指定的image region必须包含在srcImage的imageSubresource指定的subresource的范围中
			11.对pRegions的每个元素的，imageOffset.x以及(imageExtent.width + imageOffset.x)必须同时大于等于0且小于等于srcImage指定的imageSubresource的width,  imageOffset.y以及(imageExtent.height + imageExtent.y)必须同时大于等于0且小于等于srcImage指定的imageSubresource的height，
										imageOffset.z以及(imageExtent.depth + imageOffset.z)必须同时大于等于0且小于等于srcImage指定的imageSubresource的height
			12.srcImage的sample count 必须为 VK_SAMPLE_COUNT_1_BIT	
			13.如果srcImage类型为VK_IMAGE_TYPE_1D，则对pRegions的每个元素，imageOffset.y必须等于0且imageExtent.height必须为1
			14.如果srcImage的类型为VK_IMAGE_TYPE_1D 或者 VK_IMAGE_TYPE_2D，则pRegions的每个元素的imageOffset.z必须等于0且imageExtent.depth必须为1
			15.对pRegions的每个元素，imageOffset.x必须为srcImage的VkFormat的 texel block extent width的倍数，  imageOffset.y必须为srcImage的VkFormat的 texel block extent height的倍数, imageOffset.z必须为srcImage的VkFormat的 texel block extent depth的倍数
			16.对pRegions的每个元素，则（1）如果imageOffset.x + extent.width不等于srcSubresource指定的subresource的width，则extent.width必须为srcImage的VkFormat的 texel block extent width的倍数，
									   （2）如果imageOffset.y + extent.height不等于srcSubresource指定的subresource的height，则extent.height必须为srcImage的VkFormat的 texel block extent height的倍数，
									   （3）如果imageOffset.z + extent.depth不等于srcSubresource指定的subresource的depth，则extent.depth必须为srcImage的VkFormat的 texel block extent depth的倍数
			17.pRegions的每个元素，imageSubresource.aspectMask必须指明srcImage中的aspects
			18.如果srcImage含有一个multi-planar image format，则pRegions中每个元素的imageSubresource.aspectMask必须是一个单独有效的multi-planar aspect mask bit
			19.如果srcImage类型为VK_IMAGE_TYPE_3D，则pRegions的每个元素，imageSubresource.baseArrayLayer必须为0，且imageSubresource.layerCount必须为1
			20.对于pRegions的每个元素，memoryRowLength 必须是srcImage的VkFormat的 texel block extent width的倍数，memoryImageHeight 必须是srcImage的VkFormat的 texel block extent height的倍数
			21.对于pRegions的每个元素，memoryRowLength除以texel block extent width 然后乘以 srcImage的texel block size 必须小于等于pow(2,31) -1
			22.srcImageLayout必须指明当前srcImage的pRegions指明的subresources的layout
			23.srcImageLayout必须是返回的VkPhysicalDeviceHostImageCopyPropertiesEXT::pCopyDstLayouts中的一个layout
			24.如果flags包含VK_HOST_IMAGE_COPY_MEMCPY_EXT，memoryRowLength和memoryImageHeight必须同时为0
			
			*/



			//拷贝image到host memory   该命令不做安全检查，所以需要应用手动保证涉及到的区域的相关操作必须已经完成
			vkCopyImageToMemoryEXT(device, &imageMemoryCopyInfo);// hostImageCopy特性必须开启


		}


		//host端 拷贝image 到image
		{
			VkImage srcImage{/*假设这是一个有效的VkImage*/};
			VkImage dstImage{/*假设这是一个有效的VkImage*/ };

			VkCopyImageToImageInfoEXT imageImageCopyInfoEXT{};
			imageImageCopyInfoEXT.sType = VK_STRUCTURE_TYPE_COPY_IMAGE_TO_IMAGE_INFO_EXT;
			imageImageCopyInfoEXT.flags = 0;//VkHostImageCopyFlagBitsEXT 组合值位掩码，用于指定拷贝的额外参数
			imageImageCopyInfoEXT.srcImage = srcImage;//指定source image
			imageImageCopyInfoEXT.srcImageLayout = VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL;//指定source image的subresources的layout
			imageImageCopyInfoEXT.dstImage = dstImage;//指定destination image
			imageImageCopyInfoEXT.dstImageLayout = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;//指定destination image的subresources的layout
			imageImageCopyInfoEXT.regionCount = 1;//指定要拷贝的区域个数
			VkImageCopy2 imageCopyRegion2{};//等价于VkImageCopy2KHR
			{
				imageCopyRegion2.sType = VK_STRUCTURE_TYPE_IMAGE_COPY_2;
				imageCopyRegion2.pNext = nullptr;
				imageCopyRegion2.srcOffset = VkOffset3D{ .x = 0,.y = 0,.z = 0 };//source image中的x，y，z的基于texel的偏移量
				imageCopyRegion2.srcSubresource = VkImageSubresourceLayers{/*假设这是一个有效的VkImageSubresourceLayers，参见前面对VkImageSubresourceLayers的描述*/ };//指明source image的subresource的 VkImageSubresourceLayers
				imageCopyRegion2.dstOffset = VkOffset3D{ .x = 0,.y = 0,.z = 0 };//destination image中的x，y，z的基于texel的偏移量
				imageCopyRegion2.dstSubresource = VkImageSubresourceLayers{/*假设这是一个有效的VkImageSubresourceLayers，参见前面对VkImageSubresourceLayers的描述*/ };//指明destination image的subresource的 VkImageSubresourceLayers
				imageCopyRegion2.extent = VkExtent3D{ .width = 1,.height = 1,.depth = 1 };//是要拷贝的image 基于texel的width, height 以及 depth.
				/*
				VkImageCopy2有效用法:
				1.如果VK_KHR_sampler_ycbcr_conversion 拓展没有开启，且VkPhysicalDeviceProperties::apiVersion小于Vulkan 1.1,则srcSubresource 以及 dstSubresource的aspectMask，layerCount必须匹配
				2.extent.width，extent.height，extent.depth 不能为0
				*/

			}
			imageImageCopyInfoEXT.pRegions = &imageCopyRegion2;//一组VkImageCopy2结构体数组指针，用于指定要拷贝的区域
			/*
			VkCopyImageToImageInfoEXT有效用法:
			1.srcImage 和 dstImage必须以相同的创建参数创建
			2.如果srcImage是sparse的，则该命令可访问的所有区域的memory range必须已经绑定了，参见Binding Resource Memory p3007
			3.如果访问的是srcImage的stencil aspect，且srcImage 不以	separate stencil usage创建，srcImage创建时的VkImageCreateInfo::usage中必须包含VK_IMAGE_USAGE_HOST_TRANSFER_BIT_EXT
			4.如果访问的是srcImage的stencil aspect，且srcImage 以 separate stencil usage创建，srcImage创建时的VkImageStencilUsageCreateInfo::stencilUsage中必须包含VK_IMAGE_USAGE_HOST_TRANSFER_BIT_EXT
			5.如果访问的是srcImage的non-stencil aspect，srcImage创建时的VkImageCreateInfo::usage中必须包含VK_IMAGE_USAGE_HOST_TRANSFER_BIT_EXT
			6.如果flags 包含VK_HOST_IMAGE_COPY_MEMCPY_EXT，则（1）pRegions的每个元素的srcOffset的x, y, 以及 z必须为0
															 （2）pRegions的每个元素的extent必须等于srcImage的srcSubresource指定的subresource的维度范围
			7.如果srcImage是non-sparse的，则image 或指定的disjoint plane必须已经绑定到一个完整的连续的单独的VkDeviceMemory上
			8.pRegions的每个元素的srcSubresource.mipLevel必须小于创建srcImage的VkImageCreateInfo指定的mipLevels
			9.如果pRegions的每个元素的srcSubresource.layerCount不为VK_REMAINING_ARRAY_LAYERS，则该元素的srcSubresource.baseArrayLayer + srcSubresource.layerCount 必须小于等于创建srcImage的VkImageCreateInfo指定的arrayLayers
			10.srcImage不能以VK_IMAGE_CREATE_SUBSAMPLED_BIT_EXT创建
			11.pRegions中的每个元素指定的image region必须包含在srcImage的srcSubresource指定的subresource的范围中
			12.对pRegions的每个元素的，srcOffset.x以及(extent.width + srcOffset.x)必须同时大于等于0且小于等于srcImage指定的srcSubresource的width,  srcOffset.y以及(extent.height + srcOffset.y)必须同时大于等于0且小于等于srcImage指定的srcSubresource的height，
										srcOffset.z以及(extent.depth + srcOffset.z)必须同时大于等于0且小于等于srcImage指定的srcSubresource的height
			13.如果srcImage类型为VK_IMAGE_TYPE_1D，则对pRegions的每个元素，srcOffset.y必须等于0且extent.height必须为1
			14.如果srcImage的类型为VK_IMAGE_TYPE_1D 或者 VK_IMAGE_TYPE_2D，则pRegions的每个元素的srcOffset.z必须等于0且extent.depth必须为1
			15.对pRegions的每个元素，srcOffset.x必须为srcImage的VkFormat的 texel block extent width的倍数，  srcOffset.y必须为srcImage的VkFormat的 texel block extent height的倍数, srcOffset.z必须为srcImage的VkFormat的 texel block extent depth的倍数
			16.对pRegions的每个元素，则（1）如果srcOffset.x + extent.width不等于srcSubresource指定的subresource的width，则extent.width必须为srcImage的VkFormat的 texel block extent width的倍数，
									   （2）如果srcOffset.y + extent.height不等于srcSubresource指定的subresource的height，则extent.height必须为srcImage的VkFormat的 texel block extent height的倍数，
									   （3）如果srcOffset.z + extent.depth不等于srcSubresource指定的subresource的depth，则extent.depth必须为srcImage的VkFormat的 texel block extent depth的倍数
			17.pRegions的每个元素，srcSubresource.aspectMask必须指明srcImage中的aspects
			18.如果srcImage含有一个multi-planar image format，则pRegions中每个元素的srcSubresource.aspectMask必须是一个单独有效的multi-planar aspect mask bit
			19.如果srcImage类型为VK_IMAGE_TYPE_3D，则pRegions的每个元素，srcSubresource.baseArrayLayer必须为0，且srcSubresource.layerCount必须为1
			20.如果dstImage是sparse的，则该命令可访问的所有区域的memory range必须已经绑定了，参见Binding Resource Memory p3007
			21如果访问的是dstImage的stencil aspect，且dstImage 不以	separate stencil usage创建，dstImage创建时的VkImageCreateInfo::usage中必须包含VK_IMAGE_USAGE_HOST_TRANSFER_BIT_EXT
			22.如果访问的是dstImage的stencil aspect，且dstImage 以 separate stencil usage创建，dstImage创建时的VkImageStencilUsageCreateInfo::stencilUsage中必须包含VK_IMAGE_USAGE_HOST_TRANSFER_BIT_EXT
			23.如果访问的是dstImage的non-stencil aspect，dstImage创建时的VkImageCreateInfo::usage中必须包含VK_IMAGE_USAGE_HOST_TRANSFER_BIT_EXT
			24.如果flags 包含VK_HOST_IMAGE_COPY_MEMCPY_EXT，则（1）pRegions的每个元素的dstOffset的x, y, 以及 z必须为0
															  （2）pRegions的每个元素的extent必须等于dstImage的dstSubresource指定的subresource的维度范围
			25.如果dstImage是non-sparse的，则image 或指定的disjoint plane必须已经绑定到一个完整的连续的单独的VkDeviceMemory上
			26.pRegions的每个元素的dstSubresource.mipLevel必须小于创建dstImage的VkImageCreateInfo指定的mipLevels
			27.如果pRegions的每个元素的dstSubresource.layerCount不为VK_REMAINING_ARRAY_LAYERS，则该元素的dstSubresource.baseArrayLayer + dstSubresource.layerCount 必须小于等于创建dstImage的VkImageCreateInfo指定的arrayLayers
			28.dstImage不能以VK_IMAGE_CREATE_SUBSAMPLED_BIT_EXT创建
			29.pRegions中的每个元素指定的image region必须包含在dstImage的dstSubresource指定的subresource的范围中
			30.对pRegions的每个元素的，dstOffset.x以及(extent.width + dstOffset.x)必须同时大于等于0且小于等于dstImage指定的dstSubresource的width,  dstOffset.y以及(extent.height + dstOffset.y)必须同时大于等于0且小于等于dstImage指定的dstSubresource的height，
										dstOffset.z以及(extent.depth + dstOffset.z)必须同时大于等于0且小于等于dstImage指定的dstSubresource的height
			31.如果dstImage类型为VK_IMAGE_TYPE_1D，则对pRegions的每个元素，dstOffset.y必须等于0且extent.height必须为1
			32.如果dstImage的类型为VK_IMAGE_TYPE_1D 或者 VK_IMAGE_TYPE_2D，则pRegions的每个元素的dstOffset.z必须等于0且extent.depth必须为1
			33.对pRegions的每个元素，dstOffset.x必须为dstImage的VkFormat的 texel block extent width的倍数，  dstOffset.y必须为dstImage的VkFormat的 texel block extent height的倍数, dstOffset.z必须为dstImage的VkFormat的 texel block extent depth的倍数
			34.对pRegions的每个元素，则（1）如果dstOffset.x + extent.width不等于dstSubresource指定的subresource的width，则extent.width必须为dstImage的VkFormat的 texel block extent width的倍数，
									   （2）如果dstOffset.y + extent.height不等于dstSubresource指定的subresource的height，则extent.height必须为dstImage的VkFormat的 texel block extent height的倍数，
									   （3）如果dstOffset.z + extent.depth不等于dstSubresource指定的subresource的depth，则extent.depth必须为dstImage的VkFormat的 texel block extent depth的倍数
			35.pRegions的每个元素，dstSubresource.aspectMask必须指明dstImage中的aspects
			36.如果dstImage含有一个multi-planar image format，则pRegions中每个元素的dstSubresource.aspectMask必须是一个单独有效的multi-planar aspect mask bit
			37.如果dstImage类型为VK_IMAGE_TYPE_3D，则pRegions的每个元素，dstSubresource.baseArrayLayer必须为0，且dstSubresource.layerCount必须为1
			38.srcImageLayout必须指明当前srcImage的pRegions指明的subresources的layout
			39.dstImageLayout必须指明当前dstImage的pRegions指明的subresources的layout
			40.srcImageLayout必须是返回的VkPhysicalDeviceHostImageCopyPropertiesEXT::pCopyDstLayouts中的一个layout
			41.dstImageLayout必须是返回的VkPhysicalDeviceHostImageCopyPropertiesEXT::pCopyDstLayouts中的一个layout

			*/



			//host  端拷贝image到image
			vkCopyImageToImageEXT(device, &imageImageCopyInfoEXT);// hostImageCopy特性必须开启
		}


	}


	//Indirect Copies p1697
	{}
	{

		//当创建command buffer时拷贝参数不明确时候，可以使用 indirect copies

		VkCopyMemoryIndirectCommandNV copyMemoryIndirectCommandNV{};
		copyMemoryIndirectCommandNV.srcAddress = VkDeviceAddress{/*假设这是一个有效的VkDeviceAddress*/ };//拷贝的 source device memory的起始地址，必须对齐到4字节
		copyMemoryIndirectCommandNV.dstAddress = VkDeviceAddress{/*假设这是一个有效的VkDeviceAddress*/ };//拷贝的 destination device memory的起始地址，必须对齐到4字节
		copyMemoryIndirectCommandNV.size = VkDeviceSize{ 1 /*假设这是一个有效的size*/ };//拷贝的字节数，必须对齐到4字节


		//通过在buffer中间接指定copy parameters 的方式来拷贝两个memory region的数据
		vkCmdCopyMemoryIndirectNV(commandBuffer, VkDeviceAddress{/*假设这是一个有效的VkDeviceAddress*/ }/*copyBufferAddress,为指明copy parameters的buffer地址，该buffer的内存布局为 VkCopyMemoryIndirectCommandNV的数组*/
		, 0/* copyCount，指明要执行拷贝的次数，可以为0*/, 1/*stride，为buffer中两个连续copy parameters直接的字节步长间隔*/);
		/*
		vkCmdCopyMemoryIndirectNV有效用法:
		1.indirectCopy 特性必须开启
		2.copyBufferAddress必须对齐到4字节
		3.stride 必须为4的倍数 且必须大于等于 sizeof(VkCopyMemoryIndirectCommandNV)
		4.commandBuffer所在的VkCommandPool的队列族必须支持至少VkPhysicalDeviceCopyMemoryIndirectPropertiesNV::supportedQueues中的一个
		*/







		VkCopyMemoryToImageIndirectCommandNV copyMemoryToImageIndirectCommandNV{};
		copyMemoryToImageIndirectCommandNV.srcAddress = VkDeviceAddress{/*假设这是一个有效的VkDeviceAddress*/ };//拷贝的 source device memory的起始地址，必须对齐到4字节
		copyMemoryToImageIndirectCommandNV.bufferImageHeight = 1;//指定包含texel的子区域的高度，控制地址计算，如果为0，则imageExtent该维度是紧密排列的 ， 必须为0或者大于等于imageExtent该维度height的大小
		copyMemoryToImageIndirectCommandNV.bufferRowLength = 1;//指定包含texel的子区域的宽度，控制地址计算，如果为0，则imageExtent该维度是紧密排列的 ， 必须为0或者大于等于imageExtent该维度width的大小
		copyMemoryToImageIndirectCommandNV.imageExtent = VkExtent3D{ .width = 1,.height = 1,.depth = 1 };////选择image的texel子区域的width，height，depth的大小 ， 必须指定有效的destination image的extent，可以为0
		copyMemoryToImageIndirectCommandNV.imageOffset = VkOffset3D{ .x = 0,.y = 0,.z = 0 };//选择image的texel子区域的x，y，z偏移值,  必须指定有效的destination image的offset
		copyMemoryToImageIndirectCommandNV.imageSubresource = VkImageSubresourceLayers //指明destination image的subresource的 VkImageSubresourceLayers，必须和记录在vkCmdCopyMemoryToImageIndirectNV 命令的 pImageSubresources参数中指定的参数相匹配
		{
			.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT,//是 VkImageAspectFlagBits组合值位掩码，指明要拷贝的color, depth 以及/或者 stencil aspects
			.mipLevel = 0,//要拷贝的mipmap level
			.baseArrayLayer = 0,//要拷贝的第一个layer
			.layerCount = 1//要拷贝的layer的个数 
		};


		VkImage dstImage{/*假设这是一个有效的VkImage*/};
		VkImageSubresourceLayers dstImageSubresource{};
		dstImageSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
		dstImageSubresource.mipLevel = 0;
		dstImageSubresource.baseArrayLayer = 0;
		dstImageSubresource.layerCount = 1;

		//通过在buffer中间接指定copy parameters 的方式来拷贝memory region的数据到image
		vkCmdCopyMemoryToImageIndirectNV(commandBuffer, VkDeviceAddress{/*假设这是一个有效的VkDeviceAddress*/ }/*copyBufferAddress,为指明copy parameters的buffer地址，该buffer的内存布局为 copyMemoryToImageIndirectCommandNV的数组*/
			, 0/* copyCount，指明要执行拷贝的次数，可以为0*/, 1/*stride，为buffer中两个连续copy parameters直接的字节步长间隔*/,
			dstImage/*dstImage,指明destination image */, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL/*dstImageLayout ，指明destination image的subresources的layout*/, 
			& dstImageSubresource/*pImageSubresources，copyCount个 VkImageSubresourceLayers 数组指针，指明要拷贝到的image的subresources*/);
		/*
		vkCmdCopyMemoryToImageIndirectNV有效用法:
		1.indirectCopy 特性必须开启
		2.dstImage不能为protected image
		3.pImageSubresources中每个元素的aspectMask只能含有一个比特设置
		4.copyBufferAddress中每个元素指定的 image region必须包含在dstImage的范围中
		5.dstImage必须以VK_IMAGE_USAGE_TRANSFER_DST_BIT 创建
		6.如果dstImage是non-sparse的，则image 必须已经绑定到一个完整的连续的单独的VkDeviceMemory上
		7.dstImage的sample count 必须为 VK_SAMPLE_COUNT_1_BIT	
		8.在该命令执行在VkDevice上时，dstImageLayout必须指明当前dstImage的的subresources的layout
		9.dstImageLayout必须为VK_IMAGE_LAYOUT_SHARED_PRESENT_KHR, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, 或者 VK_IMAGE_LAYOUT_GENERAL
		10.每个region中指定的mipLevel必须小于创建dstImage时VkImageCreateInfo中的mipLevels
		11.如果某个region的layerCount不为VK_REMAINING_ARRAY_LAYERS，则该region的baseArrayLayer + layerCount 必须小于等于创建dstImage的VkImageCreateInfo指定的arrayLayers
		12.每个region的imageOffset和imageExtent必须符合commandBuffer所在的VkCommandPool的队列族的image的transfer granularity requirements，参见VkQueueFamilyProperties
		13.dstImage不能以VK_IMAGE_CREATE_SUBSAMPLED_BIT_EXT创建
		14.如果commandBuffer所在的VkCommandPool的队列族不支持VK_QUEUE_GRAPHICS_BIT，则对于每个region，其aspectMask不能为VK_IMAGE_ASPECT_DEPTH_BIT 或者VK_IMAGE_ASPECT_STENCIL_BIT
		15.对于copyBufferAddress中的每个region，imageOffset.y 和 (imageExtent.height + imageOffset.y) 必须都大于等于0，且小于等于指定subresource的高度
		16.offset 必须为4字节对齐
		17.stride 必须为4的倍数 且必须大于等于 sizeof(VkCopyMemoryToImageIndirectCommandNV)
		*/



	}





}

void CopyCommandsTest::ScaleCopyAndResolveCommandsTest()
{

	VkCommandBuffer commandBuffer{/*假设这是一个有效的VkCommandBuffer*/ };
	1;
	// Image Copies With Scaling 参见p1703
	{

		VkImage srcImage{/*假设这是一个有效的VkImage*/ };
		VkImage dstImage{/*假设这是一个有效的VkImage*/ };
		VkImageBlit blitRegion{};
		blitRegion.srcOffsets[0] = VkOffset3D{.x = 0,.y = 0,.z = 0};//指明 srcSubresource中source region的边界的最小值，即xmin，ymin，zmin
		blitRegion.srcOffsets[1] = VkOffset3D{ .x = 0,.y = 0,.z = 0 };//指明 srcSubresource中source region的边界的最大值，即xmax，ymax，zmax
		blitRegion.srcSubresource = VkImageSubresourceLayers //指明source image的subresource的 VkImageSubresourceLayers
		{
			.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT,//是 VkImageAspectFlagBits组合值位掩码，指明要blit的color, depth 以及/或者 stencil aspects
			.mipLevel = 0,//要blit的mipmap level
			.baseArrayLayer = 0,//要blit的第一个layer
			.layerCount = 1//要blit的layer的个数 
		};
		blitRegion.dstOffsets[0] = VkOffset3D{ .x = 0,.y = 0,.z = 0 };//指明 dstSubresource中destination region的边界的最小值，即xmin，ymin，zmin
		blitRegion.dstOffsets[1] = VkOffset3D{ .x = 0,.y = 0,.z = 0 };//指明 dstSubresource中destination region的边界的最大值，即xmax，ymax，zmax
		blitRegion.dstSubresource = VkImageSubresourceLayers //指明destination image的subresource的 VkImageSubresourceLayers
		{
			.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT,//是 VkImageAspectFlagBits组合值位掩码，指明要blit的color, depth 以及/或者 stencil aspects
			.mipLevel = 0,//要blit的mipmap level
			.baseArrayLayer = 0,//要blit的第一个layer
			.layerCount = 1//要blit的layer的个数 
		};
		/*
		VkImageBlit有效用法:
		1.srcSubresource 和 dstSubresource的aspectMask 必须匹配
		2.如果srcSubresource 或者 dstSubresource的layerCount都不为VK_REMAINING_ARRAY_LAYERS，则srcSubresource 和 dstSubresource的layerCount 必须匹配
		3.如果srcSubresource 或者 dstSubresource其中之一的layerCount为VK_REMAINING_ARRAY_LAYERS，则另外一个的layerCount 必须为VK_REMAINING_ARRAY_LAYERS或者等于创建该image的arrayLayers 减去 baseArrayLayer
		*/



		//将source image的区域复制到destination image中，可能执行格式转换、任意缩放和过滤，该命令不能对multisampled的image使用
		vkCmdBlitImage(commandBuffer, srcImage/*srcImage，指定source image*/, VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL/*srcImageLayout，指定source image的subresources的layout*/, 
			dstImage/*dstImage，指定destination image*/, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL/*dstImageLayout，指定destination image的subresources的layout*/,
			1/*regionCount，指明要blit的区域数量*/, &blitRegion/*pRegions，一组 VkImageBlit 数组指针，指明要blit的区域*/, VK_FILTER_LINEAR/*filter，指明需要缩放时的滤波类型的VkFilter*/);
		/*
		vkCmdBlitImage有效用法:
		1.如果commandBuffer为unprotected command buffer，且不支持protectedNoFault，则srcImage,dstImage不能为一个protected image
		2.如果commandBuffer为protected command buffer，且不支持protectedNoFault，则dstImage不能为一个unprotected image
		3.pRegions的元素指明的source region必须包含在srcImage的范围中，destination region 必须包含在dstImage的范围中
		4.pRegions的元素指明的destination region的内存区域并集不能和可能blit operation采样的内存区域在内存上有重叠
		5.srcImage的format features必须包含VK_FORMAT_FEATURE_BLIT_SRC_BIT
		6.srcImage不能使用一个需要sampler Y′CBCR conversion的format
		7.srcImage必须以VK_IMAGE_USAGE_TRANSFER_SRC_BIT 创建
		8.如果srcImage为 non-sparse的则image必须已经绑定到完整的连续的单独的VkDeviceMemory上
		9.在当前命令执行在VkDevice上时，srcImageLayout必须指明当前srcImage的subresources的layout
		10.srcImageLayout必须为VK_IMAGE_LAYOUT_SHARED_PRESENT_KHR, VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL, 或者 VK_IMAGE_LAYOUT_GENERAL
		11.如果srcImage和dstImage相同，且pRegions的任何元素包含mipLevel匹配且array layers重叠的srcSubresource 和 dstSubresource，则srcImageLayout 和 dstImageLayout 必须为 VK_IMAGE_LAYOUT_GENERAL 或者 VK_IMAGE_LAYOUT_SHARED_PRESENT_KHR
		12.dstImage的format features必须包含VK_FORMAT_FEATURE_BLIT_DST_BIT
		13.dstImage不能使用一个需要sampler Y′CBCR conversion的format
		14.dstImage必须以VK_IMAGE_USAGE_TRANSFER_DST_BIT 创建
		15.如果dstImage为 non-sparse的则image必须已经绑定到完整的连续的单独的VkDeviceMemory上
		16.在当前命令执行在VkDevice上时，dstImageLayout必须指明当前dstImage的subresources的layout
		17.dstImageLayout必须为VK_IMAGE_LAYOUT_SHARED_PRESENT_KHR, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, 或者 VK_IMAGE_LAYOUT_GENERAL
		18.如果srcImage 或者 dstImage其中之一以signed integer VkFormat创建，则另外一个也必须以signed integer VkFormat创建，如果其中之一以unsigned integer VkFormat创建，则另外一个也必须以unsigned integer VkFormat创建
		19.如果srcImage 或者 dstImage其中之一以depth/stencil format创建，则另外一个也必须含有一个相同的format
		20.如果srcImage 以depth/stencil format创建，则filter 必须为 VK_FILTER_NEAREST
		21.srcImage的sample count 必须为 VK_SAMPLE_COUNT_1_BIT	
		22.dstImage的sample count 必须为 VK_SAMPLE_COUNT_1_BIT	
		23.如果filter 为 VK_FILTER_LINEAR，则srcImage的format features必须包含VK_FORMAT_FEATURE_SAMPLED_IMAGE_FILTER_LINEAR_BIT
		24.如果filter 为 VK_FILTER_CUBIC_EXT，则（1）srcImage的format features必须包含VK_FORMAT_FEATURE_SAMPLED_IMAGE_FILTER_CUBIC_BIT_EXT
												（2）srcImage 的类型必须为VK_IMAGE_TYPE_2D
		25.pRegions的每个元素的srcSubresource.mipLevel必须小于创建srcImage的VkImageCreateInfo指定的mipLevels
		26.pRegions的每个元素的dstSubresource.mipLevel必须小于创建dstImage的VkImageCreateInfo指定的mipLevels
		27.如果pRegions的每个元素的srcSubresource.layerCount不为VK_REMAINING_ARRAY_LAYERS，则该元素的srcSubresource.baseArrayLayer + srcSubresource.layerCount 必须小于等于创建srcImage的VkImageCreateInfo指定的arrayLayers
		28.如果pRegions的每个元素的dstSubresource.layerCount不为VK_REMAINING_ARRAY_LAYERS，则该元素的dstSubresource.baseArrayLayer + dstSubresource.layerCount 必须小于等于创建dstImage的VkImageCreateInfo指定的arrayLayers
		29.srcImage和dstImage不能以VK_IMAGE_CREATE_SUBSAMPLED_BIT_EXT创建
		30.如果srcImage或者dstImage其中之一类型为VK_IMAGE_TYPE_3D，则pRegions的每个元素，srcSubresource.baseArrayLayer和dstSubresource.baseArrayLayer必须为0，且srcSubresource.layerCount和dstSubresource.layerCount必须为1
		31.pRegions的每个元素，srcSubresource.aspectMask必须指明srcImage中的aspects，dstSubresource.aspectMask必须指明dstImage中的aspects
		32.对pRegions的每个元素,srcOffsets[0].x 和 srcOffsets[1].x必须同时大于等于0且小于等于指定的srcImage的srcSubresource中的width，srcOffsets[0].y 和 srcOffsets[1].y必须同时大于等于0且小于等于指定的srcImage的srcSubresource中的height, srcOffsets[0].z 和 srcOffsets[1].z必须同时大于等于0且小于等于指定的srcImage的srcSubresource中的depth
		33.如果srcImage类型为VK_IMAGE_TYPE_1D，则对pRegions的每个元素，srcOffsets[0].y必须等于0且srcOffsets[1].y必须为1
		34.如果srcImage类型为VK_IMAGE_TYPE_1D 或VK_IMAGE_TYPE_2D，则对pRegions的每个元素，srcOffsets[0].z必须等于0且srcOffsets[1].z必须为1
		35.对pRegions的每个元素,dstOffsets[0].x 和 dstOffsets[1].x必须同时大于等于0且小于等于指定的dstImage的dstSubresource中的width，dstOffsets[0].y 和 dstOffsets[1].y必须同时大于等于0且小于等于指定的dstImage的dstSubresource中的height, dstOffsets[0].z 和 dstOffsets[1].z必须同时大于等于0且小于等于指定的dstImage的dstSubresource中的depth
		36.如果dstImage类型为VK_IMAGE_TYPE_1D，则对pRegions的每个元素，dstOffsets[0].y必须等于0且dstOffsets[1].y必须为1
		37.如果dstImage类型为VK_IMAGE_TYPE_1D 或VK_IMAGE_TYPE_2D，则对pRegions的每个元素，dstOffsets[0].z必须等于0且dstOffsets[1].z必须为1
		*/


		VkBlitImageInfo2 blitInfo2{};
		blitInfo2.sType = VK_STRUCTURE_TYPE_BLIT_IMAGE_INFO_2;
		VkBlitImageCubicWeightsInfoQCOM  blitImageCubicWeightsInfoQCOM{};//
		{
			blitImageCubicWeightsInfoQCOM.sType = VK_STRUCTURE_TYPE_MAX_ENUM;//没有定义，所以设置为非法值
			blitImageCubicWeightsInfoQCOM.pNext = nullptr;
			blitImageCubicWeightsInfoQCOM.cubicWeights = VK_CUBIC_FILTER_WEIGHTS_B_SPLINE_QCOM;//一个 VkCubicFilterWeightsQCOM值控制blit的cubic filter weights
		}

		blitInfo2.pNext = &blitImageCubicWeightsInfoQCOM;//可以包含一个 VkBlitImageCubicWeightsInfoQCOM
		blitInfo2.srcImage = srcImage;//指定source image
		blitInfo2.srcImageLayout = VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL;//指定source image的subresources的layout
		blitInfo2.dstImage = dstImage;//指定destination image
		blitInfo2.dstImageLayout = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;//指定destination image的subresources的layout
		blitInfo2.filter = VK_FILTER_LINEAR;//指明需要缩放时的滤波类型的VkFilter
		blitInfo2.regionCount = 1;//指明要blit的区域数量
		VkImageBlit2 blitRegion2{};//等价于VkImageBlit2KHR
		{
			blitRegion2.sType = VK_STRUCTURE_TYPE_IMAGE_BLIT_2;
			VkCopyCommandTransformInfoQCOM copyCommandTransformInfoQCOM{};//指明blit前的旋转操作
			{
				copyCommandTransformInfoQCOM.sType = VK_STRUCTURE_TYPE_COPY_COMMAND_TRANSFORM_INFO_QCOM;
				copyCommandTransformInfoQCOM.pNext = nullptr;
				copyCommandTransformInfoQCOM.transform = VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR;
			}
			blitRegion2.pNext = &copyCommandTransformInfoQCOM;//可以包含一个VkCopyCommandTransformInfoQCOM
			blitRegion2.srcOffsets[0] = VkOffset3D{ .x = 0,.y = 0,.z = 0 };//指明 srcSubresource中source region的边界的最小值，即xmin，ymin，zmin
			blitRegion2.srcOffsets[1] = VkOffset3D{ .x = 0,.y = 0,.z = 0 };//指明 srcSubresource中source region的边界的最大值，即xmax，ymax，zmax
			blitRegion2.srcSubresource = VkImageSubresourceLayers //指明source image的subresource的 VkImageSubresourceLayers
			{
				.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT,//是 VkImageAspectFlagBits组合值位掩码，指明要blit的color, depth 以及/或者 stencil aspects
				.mipLevel = 0,//要blit的mipmap level
				.baseArrayLayer = 0,//要blit的第一个layer
				.layerCount = 1//要blit的layer的个数 
			};
			blitRegion2.dstOffsets[0] = VkOffset3D{ .x = 0,.y = 0,.z = 0 };//指明 dstSubresource中destination region的边界的最小值，即xmin，ymin，zmin
			blitRegion2.dstOffsets[1] = VkOffset3D{ .x = 0,.y = 0,.z = 0 };//指明 dstSubresource中destination region的边界的最大值，即xmax，ymax，zmax
			blitRegion2.dstSubresource = VkImageSubresourceLayers //指明destination image的subresource的 VkImageSubresourceLayers
			{
				.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT,//是 VkImageAspectFlagBits组合值位掩码，指明要blit的color, depth 以及/或者 stencil aspects
				.mipLevel = 0,//要blit的mipmap level
				.baseArrayLayer = 0,//要blit的第一个layer
				.layerCount = 1//要blit的layer的个数 
			};
			/*
			VkImageBlit2有效用法
			1.srcSubresource 和 dstSubresource的aspectMask 必须匹配
			2.如果srcSubresource 或者 dstSubresource的layerCount都不为VK_REMAINING_ARRAY_LAYERS，则srcSubresource 和 dstSubresource的layerCount 必须匹配
			3.如果srcSubresource 或者 dstSubresource其中之一的layerCount为VK_REMAINING_ARRAY_LAYERS，则另外一个的layerCount 必须为VK_REMAINING_ARRAY_LAYERS或者等于创建该image的arrayLayers 减去 baseArrayLayer
			*/
		}
		blitInfo2.pRegions = &blitRegion2;//一组 VkImageBlit2 数组指针，指明要blit的区域
		/*
		VkBlitImageInfo2有效用法:
		1.pRegions的元素指明的source region必须包含在srcImage的范围中，destination region 必须包含在dstImage的范围中
		2.pRegions的元素指明的destination region的内存区域并集不能和可能blit operation采样的内存区域在内存上有重叠
		3.srcImage的format features必须包含VK_FORMAT_FEATURE_BLIT_SRC_BIT
		4.srcImage不能使用一个需要sampler Y′CBCR conversion的format
		5.srcImage必须以VK_IMAGE_USAGE_TRANSFER_SRC_BIT 创建
		6.如果srcImage为 non-sparse的则image必须已经绑定到完整的连续的单独的VkDeviceMemory上
		7.在当前命令执行在VkDevice上时，srcImageLayout必须指明当前srcImage的subresources的layout
		8.srcImageLayout必须为VK_IMAGE_LAYOUT_SHARED_PRESENT_KHR, VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL, 或者 VK_IMAGE_LAYOUT_GENERAL
		9.如果srcImage和dstImage相同，且pRegions的任何元素包含mipLevel匹配且array layers重叠的srcSubresource 和 dstSubresource，则srcImageLayout 和 dstImageLayout 必须为 VK_IMAGE_LAYOUT_GENERAL 或者 VK_IMAGE_LAYOUT_SHARED_PRESENT_KHR
		10.dstImage的format features必须包含VK_FORMAT_FEATURE_BLIT_DST_BIT
		11.dstImage不能使用一个需要sampler Y′CBCR conversion的format
		12.dstImage必须以VK_IMAGE_USAGE_TRANSFER_DST_BIT 创建
		13.如果dstImage为 non-sparse的则image必须已经绑定到完整的连续的单独的VkDeviceMemory上
		14.在当前命令执行在VkDevice上时，dstImageLayout必须指明当前dstImage的subresources的layout
		15.dstImageLayout必须为VK_IMAGE_LAYOUT_SHARED_PRESENT_KHR, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, 或者 VK_IMAGE_LAYOUT_GENERAL
		16.如果srcImage 或者 dstImage其中之一以signed integer VkFormat创建，则另外一个也必须以signed integer VkFormat创建，如果其中之一以unsigned integer VkFormat创建，则另外一个也必须以unsigned integer VkFormat创建
		17.如果srcImage 或者 dstImage其中之一以depth/stencil format创建，则另外一个也必须含有一个相同的format
		18.如果srcImage 以depth/stencil format创建，则filter 必须为 VK_FILTER_NEAREST
		19.srcImage的sample count 必须为 VK_SAMPLE_COUNT_1_BIT
		20.dstImage的sample count 必须为 VK_SAMPLE_COUNT_1_BIT
		21.如果filter 为 VK_FILTER_LINEAR，则srcImage的format features必须包含VK_FORMAT_FEATURE_SAMPLED_IMAGE_FILTER_LINEAR_BIT
		22.如果filter 为 VK_FILTER_CUBIC_EXT，则（1）srcImage的format features必须包含VK_FORMAT_FEATURE_SAMPLED_IMAGE_FILTER_CUBIC_BIT_EXT
												（2）srcImage 的类型必须为VK_IMAGE_TYPE_2D
		23.pRegions的每个元素的srcSubresource.mipLevel必须小于创建srcImage的VkImageCreateInfo指定的mipLevels
		24.pRegions的每个元素的dstSubresource.mipLevel必须小于创建dstImage的VkImageCreateInfo指定的mipLevels
		25.如果pRegions的每个元素的srcSubresource.layerCount不为VK_REMAINING_ARRAY_LAYERS，则该元素的srcSubresource.baseArrayLayer + srcSubresource.layerCount 必须小于等于创建srcImage的VkImageCreateInfo指定的arrayLayers
		26.如果pRegions的每个元素的dstSubresource.layerCount不为VK_REMAINING_ARRAY_LAYERS，则该元素的dstSubresource.baseArrayLayer + dstSubresource.layerCount 必须小于等于创建dstImage的VkImageCreateInfo指定的arrayLayers
		27.srcImage和dstImage不能以VK_IMAGE_CREATE_SUBSAMPLED_BIT_EXT创建
		28.如果srcImage或者dstImage其中之一类型为VK_IMAGE_TYPE_3D，则pRegions的每个元素，srcSubresource.baseArrayLayer和dstSubresource.baseArrayLayer必须为0，且srcSubresource.layerCount和dstSubresource.layerCount必须为1
		29.pRegions的每个元素，srcSubresource.aspectMask必须指明srcImage中的aspects，dstSubresource.aspectMask必须指明dstImage中的aspects
		30.对pRegions的每个元素,srcOffsets[0].x 和 srcOffsets[1].x必须同时大于等于0且小于等于指定的srcImage的srcSubresource中的width，srcOffsets[0].y 和 srcOffsets[1].y必须同时大于等于0且小于等于指定的srcImage的srcSubresource中的height, srcOffsets[0].z 和 srcOffsets[1].z必须同时大于等于0且小于等于指定的srcImage的srcSubresource中的depth
		31.如果srcImage类型为VK_IMAGE_TYPE_1D，则对pRegions的每个元素，srcOffsets[0].y必须等于0且srcOffsets[1].y必须为1
		32.如果srcImage类型为VK_IMAGE_TYPE_1D 或VK_IMAGE_TYPE_2D，则对pRegions的每个元素，srcOffsets[0].z必须等于0且srcOffsets[1].z必须为1
		33.对pRegions的每个元素,dstOffsets[0].x 和 dstOffsets[1].x必须同时大于等于0且小于等于指定的dstImage的dstSubresource中的width，dstOffsets[0].y 和 dstOffsets[1].y必须同时大于等于0且小于等于指定的dstImage的dstSubresource中的height, dstOffsets[0].z 和 dstOffsets[1].z必须同时大于等于0且小于等于指定的dstImage的dstSubresource中的depth
		34.如果dstImage类型为VK_IMAGE_TYPE_1D，则对pRegions的每个元素，dstOffsets[0].y必须等于0且dstOffsets[1].y必须为1
		35.如果dstImage类型为VK_IMAGE_TYPE_1D 或VK_IMAGE_TYPE_2D，则对pRegions的每个元素，dstOffsets[0].z必须等于0且dstOffsets[1].z必须为1
		36.如果pRegions中的任何元素的pNext中包含一个VkCopyCommandTransformInfoQCOM结构体，则（1）srcImage和dstImage不能是block-compressed图像
																							（2）srcImage 的类型必须为VK_IMAGE_TYPE_2D
																							（3）srcImage不能有一个multi-planar format
		37.如果filter为VK_FILTER_CUBIC_EXT且如果selectableCubicWeights特性未开启，则cubic weights 必须为VK_CUBIC_FILTER_WEIGHTS_CATMULL_ROM_QCOM

		*/


		//将source image的区域复制到destination image中，可能执行格式转换、任意缩放和过滤，该命令不能对multisampled的image使用  等价于vkCmdBlitImage2KHR
		vkCmdBlitImage2(commandBuffer, &blitInfo2);
		/*
		vkCmdBlitImage2有效用法:
		1.如果commandBuffer为unprotected command buffer，且不支持protectedNoFault，则srcImage,dstImage不能为一个protected image
		2.如果commandBuffer为protected command buffer，且不支持protectedNoFault，则dstImage不能为一个unprotected image
		*/


		// Image Blits With Scaling and Rotation p1720

	}

	
	2;
	//Resolving Multisample Images 参见p1722
	{

		VkImage srcImage{/*假设这是一个有效的VkImage*/ };
		VkImage dstImage{/*假设这是一个有效的VkImage*/ };

		VkImageResolve imageResolveRegion{};
		imageResolveRegion.srcOffset = VkOffset3D{ .x = 0,.y = 0,.z = 0 };//指明 srcSubresource中source sub-region的基于texel的x，y，z的初始偏移值
		imageResolveRegion.srcSubresource = VkImageSubresourceLayers //指明source image的subresource的 VkImageSubresourceLayers
		{
			.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT,//是 VkImageAspectFlagBits组合值位掩码，指明要resolve的 aspects，不支持 depth/stencil iamges
			.mipLevel = 0,//要resolve的mipmap level
			.baseArrayLayer = 0,//要resolve的第一个layer
			.layerCount = 1//要resolve的layer的个数 
		};
		imageResolveRegion.dstOffset = VkOffset3D{ .x = 0,.y = 0,.z = 0 };//指明 dstSubresource中destination sub-region的基于texel的x，y，z的初始偏移值
		imageResolveRegion.dstSubresource = VkImageSubresourceLayers //指明destination image的subresource的 VkImageSubresourceLayers
		{
			.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT,//是 VkImageAspectFlagBits组合值位掩码，指明要resolve的 aspects，不支持 depth/stencil iamges
			.mipLevel = 0,//要resolve的mipmap level
			.baseArrayLayer = 0,//要resolve的第一个layer
			.layerCount = 1//要resolve的layer的个数 
		};
		imageResolveRegion.extent = VkExtent3D{ .width = 1,.height = 1,.depth = 1 };//指明要resolve的区域的wdith,height,depth大小
		/*
		VkImageResolve有效用法:
		1.srcSubresource 和 dstSubresource的aspectMask 只能包含VK_IMAGE_ASPECT_COLOR_BIT
		2.如果srcSubresource 或者 dstSubresource的layerCount都不为VK_REMAINING_ARRAY_LAYERS，则srcSubresource 和 dstSubresource的layerCount 必须匹配
		3.如果srcSubresource 或者 dstSubresource其中之一的layerCount为VK_REMAINING_ARRAY_LAYERS，则另外一个的layerCount 必须为VK_REMAINING_ARRAY_LAYERS或者等于创建该image的arrayLayers 减去 baseArrayLayer
		*/

		//将一个multisample color image	转换为一个单色的non-multisampled image，该命令可以对multisampled的image使用
		vkCmdResolveImage(commandBuffer, 
			srcImage/*srcImage，指定source image*/, VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL/*srcImageLayout，指定source image的subresources的layout*/,
			dstImage/*dstImage，指定destination image*/, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL/*dstImageLayout，指定destination image的subresources的layout*/,
			1/*regionCount，指明要blit的区域数量*/, &imageResolveRegion/*pRegions，一组  VkImageResolve 数组指针，指明要resolve的区域*/);
		/*
		vkCmdResolveImage有效用法:
		1.如果commandBuffer为unprotected command buffer，且不支持protectedNoFault，则srcImage,dstImage不能为一个protected image
		2.如果commandBuffer为protected command buffer，且不支持protectedNoFault，则dstImage不能为一个unprotected image
		3.pRegions的元素指明的source region的并集和destination region的并集在内存上不能有重叠
		4.如果srcImage为 non-sparse的则image必须已经绑定到完整的连续的单独的VkDeviceMemory上
		5.srcImage必须有一个除了VK_SAMPLE_COUNT_1_BIT外有效的sample count
		6.如果dstImage为 non-sparse的则image必须已经绑定到完整的连续的单独的VkDeviceMemory上
		7.dstImage的sample count 必须为 VK_SAMPLE_COUNT_1_BIT	
		8.在当前命令执行在VkDevice上时，srcImageLayout必须指明当前srcImage的subresources的layout
		9.srcImageLayout必须为VK_IMAGE_LAYOUT_SHARED_PRESENT_KHR, VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL, 或者 VK_IMAGE_LAYOUT_GENERAL
		10.在当前命令执行在VkDevice上时，dstImageLayout必须指明当前dstImage的subresources的layout
		11.dstImageLayout必须为VK_IMAGE_LAYOUT_SHARED_PRESENT_KHR, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, 或者 VK_IMAGE_LAYOUT_GENERAL
		12.dstImage的format features必须包含VK_FORMAT_FEATURE_COLOR_ATTACHMENT_BIT
		13.如果linearColorAttachment 特性开启且dstImage以VK_IMAGE_TILING_LINEAR创建，则dstImage的format features必须包含VK_FORMAT_FEATURE_2_LINEAR_COLOR_ATTACHMENT_BIT_NV
		14.srcImage 和 dstImage必须以相同的format创建
		15.pRegions的每个元素的srcSubresource.mipLevel必须小于创建srcImage的VkImageCreateInfo指定的mipLevels
		16.pRegions的每个元素的dstSubresource.mipLevel必须小于创建dstImage的VkImageCreateInfo指定的mipLevels
		17.如果pRegions的每个元素的srcSubresource.layerCount不为VK_REMAINING_ARRAY_LAYERS，则该元素的srcSubresource.baseArrayLayer + srcSubresource.layerCount 必须小于等于创建srcImage的VkImageCreateInfo指定的arrayLayers
		18.如果pRegions的每个元素的dstSubresource.layerCount不为VK_REMAINING_ARRAY_LAYERS，则该元素的dstSubresource.baseArrayLayer + dstSubresource.layerCount 必须小于等于创建dstImage的VkImageCreateInfo指定的arrayLayers
		19.srcImage和dstImage不能以VK_IMAGE_CREATE_SUBSAMPLED_BIT_EXT创建
		20.如果dstImage类型为VK_IMAGE_TYPE_3D，则pRegions的每个元素，srcSubresource.layerCount必须为1， srcSubresource.baseArrayLayer必须为0，且srcSubresource.layerCount必须为1
		21.对于pRegions的每个元素，srcOffset.x 以及 (extent.width + srcOffset.x)必须同时大于等于0且小于等于指定的srcImage的srcSubresource中的width，srcOffset.y 以及 (extent.height + srcOffset.y)必须同时大于等于0且小于等于指定的srcImage的srcSubresource中的height,
									srcOffset.z 以及 (extent.depth + srcOffset.z)必须同时大于等于0且小于等于指定的srcImage的srcSubresource中的depth
		22.如果srcImage类型为VK_IMAGE_TYPE_1D，则对pRegions的每个元素，srcOffset.y必须等于0且extent.height必须为1
		23.如果srcImage类型为VK_IMAGE_TYPE_1D 或VK_IMAGE_TYPE_2D，则对pRegions的每个元素，srcOffset.z必须等于0且extent.depth必须为1
		24.对于pRegions的每个元素，dstOffset.x 以及 (extent.width + dstOffset.x)必须同时大于等于0且小于等于指定的dstImage的dstSubresource中的width，dstOffset.y 以及 (extent.height + dstOffset.y)必须同时大于等于0且小于等于指定的dstImage的dstSubresource中的height,
									dstOffset.z 以及 (extent.depth + dstOffset.z)必须同时大于等于0且小于等于指定的dstImage的dstSubresource中的depth
		24.如果dstImage类型为VK_IMAGE_TYPE_1D，则对pRegions的每个元素，dstOffset.y必须等于0且extent.height必须为1
		25.如果dstImage类型为VK_IMAGE_TYPE_1D 或VK_IMAGE_TYPE_2D，则对pRegions的每个元素，dstOffset.z必须等于0且extent.depth必须为1
		26.srcImage必须以VK_IMAGE_USAGE_TRANSFER_SRC_BIT 创建
		27.srcImage的format features必须包含VK_FORMAT_FEATURE_TRANSFER_SRC_BIT
		28.dstImage必须以VK_IMAGE_USAGE_TRANSFER_DST_BIT 创建
		29.dstImage的format features必须包含VK_FORMAT_FEATURE_TRANSFER_DST_BIT
		*/

		VkResolveImageInfo2 resolveImageInfo2{};//等价于VkResolveImageInfo2KHR
		resolveImageInfo2.sType = VK_STRUCTURE_TYPE_RESOLVE_IMAGE_INFO_2;
		resolveImageInfo2.pNext = nullptr;
		resolveImageInfo2.srcImage = srcImage;//指定source image
		resolveImageInfo2.srcImageLayout = VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL;//指定source image的subresources的layout
		resolveImageInfo2.dstImage = dstImage;//指定destination image
		resolveImageInfo2.dstImageLayout = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;//指定destination image的subresources的layout
		resolveImageInfo2.regionCount = 1;//指明要resolve的区域数量
		VkImageResolve2 imageResolveRegion2{};//等价于VkImageResolve2KHR
		{
			imageResolveRegion2.sType = VK_STRUCTURE_TYPE_IMAGE_RESOLVE_2;
			imageResolveRegion2.pNext = nullptr;
			imageResolveRegion2.srcOffset = VkOffset3D{ .x = 0,.y = 0,.z = 0 };//指明 srcSubresource中source sub-region的基于texel的x，y，z的初始偏移值
			imageResolveRegion2.srcSubresource = VkImageSubresourceLayers //指明source image的subresource的 VkImageSubresourceLayers
			{
				.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT,//是 VkImageAspectFlagBits组合值位掩码，指明要resolve的 aspects，不支持 depth/stencil iamges
				.mipLevel = 0,//要resolve的mipmap level
				.baseArrayLayer = 0,//要resolve的第一个layer
				.layerCount = 1//要resolve的layer的个数 
			};
			imageResolveRegion2.dstOffset = VkOffset3D{ .x = 0,.y = 0,.z = 0 };//指明 dstSubresource中destination sub-region的基于texel的x，y，z的初始偏移值
			imageResolveRegion2.dstSubresource = VkImageSubresourceLayers //指明destination image的subresource的 VkImageSubresourceLayers
			{
				.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT,//是 VkImageAspectFlagBits组合值位掩码，指明要resolve的 aspects，不支持 depth/stencil iamges
				.mipLevel = 0,//要resolve的mipmap level
				.baseArrayLayer = 0,//要resolve的第一个layer
				.layerCount = 1//要resolve的layer的个数 
			};
			imageResolveRegion2.extent = VkExtent3D{ .width = 1,.height = 1,.depth = 1 };//指明要resolve的区域的wdith,height,depth大小
			/*
			VkImageResolve2有效用法:
			1.srcSubresource 和 dstSubresource的aspectMask 只能包含VK_IMAGE_ASPECT_COLOR_BIT
			2.如果srcSubresource 或者 dstSubresource的layerCount都不为VK_REMAINING_ARRAY_LAYERS，则srcSubresource 和 dstSubresource的layerCount 必须匹配
			3.如果srcSubresource 或者 dstSubresource其中之一的layerCount为VK_REMAINING_ARRAY_LAYERS，则另外一个的layerCount 必须为VK_REMAINING_ARRAY_LAYERS或者等于创建该image的arrayLayers 减去 baseArrayLayer
			
			*/

		}
		resolveImageInfo2.pRegions = &imageResolveRegion2;//一组VkImageResolve2结构体数组指针，用于指定要resolve的区域
		/*
		VkResolveImageInfo2有效用法

		1.pRegions的元素指明的source region的并集和destination region的并集在内存上不能有重叠
		2.如果srcImage为 non-sparse的则image必须已经绑定到完整的连续的单独的VkDeviceMemory上
		3.srcImage必须有一个除了VK_SAMPLE_COUNT_1_BIT外有效的sample count
		4.如果dstImage为 non-sparse的则image必须已经绑定到完整的连续的单独的VkDeviceMemory上
		5.dstImage的sample count 必须为 VK_SAMPLE_COUNT_1_BIT	
		6.在当前命令执行在VkDevice上时，srcImageLayout必须指明当前srcImage的subresources的layout
		7.srcImageLayout必须为VK_IMAGE_LAYOUT_SHARED_PRESENT_KHR, VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL, 或者 VK_IMAGE_LAYOUT_GENERAL
		8.在当前命令执行在VkDevice上时，dstImageLayout必须指明当前dstImage的subresources的layout
		9.dstImageLayout必须为VK_IMAGE_LAYOUT_SHARED_PRESENT_KHR, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, 或者 VK_IMAGE_LAYOUT_GENERAL
		10.dstImage的format features必须包含VK_FORMAT_FEATURE_COLOR_ATTACHMENT_BIT
		11.如果linearColorAttachment 特性开启且dstImage以VK_IMAGE_TILING_LINEAR创建，则dstImage的format features必须包含VK_FORMAT_FEATURE_2_LINEAR_COLOR_ATTACHMENT_BIT_NV
		12.srcImage 和 dstImage必须以相同的format创建
		13.pRegions的每个元素的srcSubresource.mipLevel必须小于创建srcImage的VkImageCreateInfo指定的mipLevels
		14.pRegions的每个元素的dstSubresource.mipLevel必须小于创建dstImage的VkImageCreateInfo指定的mipLevels
		15.如果pRegions的每个元素的srcSubresource.layerCount不为VK_REMAINING_ARRAY_LAYERS，则该元素的srcSubresource.baseArrayLayer + srcSubresource.layerCount 必须小于等于创建srcImage的VkImageCreateInfo指定的arrayLayers
		16.如果pRegions的每个元素的dstSubresource.layerCount不为VK_REMAINING_ARRAY_LAYERS，则该元素的dstSubresource.baseArrayLayer + dstSubresource.layerCount 必须小于等于创建dstImage的VkImageCreateInfo指定的arrayLayers
		17.srcImage和dstImage不能以VK_IMAGE_CREATE_SUBSAMPLED_BIT_EXT创建
		18.如果dstImage类型为VK_IMAGE_TYPE_3D，则pRegions的每个元素，srcSubresource.layerCount必须为1， srcSubresource.baseArrayLayer必须为0，且srcSubresource.layerCount必须为1
		19.对于pRegions的每个元素，srcOffset.x 以及 (extent.width + srcOffset.x)必须同时大于等于0且小于等于指定的srcImage的srcSubresource中的width，srcOffset.y 以及 (extent.height + srcOffset.y)必须同时大于等于0且小于等于指定的srcImage的srcSubresource中的height,
									srcOffset.z 以及 (extent.depth + srcOffset.z)必须同时大于等于0且小于等于指定的srcImage的srcSubresource中的depth
		20.如果srcImage类型为VK_IMAGE_TYPE_1D，则对pRegions的每个元素，srcOffset.y必须等于0且extent.height必须为1
		21.如果srcImage类型为VK_IMAGE_TYPE_1D 或VK_IMAGE_TYPE_2D，则对pRegions的每个元素，srcOffset.z必须等于0且extent.depth必须为1
		22.对于pRegions的每个元素，dstOffset.x 以及 (extent.width + dstOffset.x)必须同时大于等于0且小于等于指定的dstImage的dstSubresource中的width，dstOffset.y 以及 (extent.height + dstOffset.y)必须同时大于等于0且小于等于指定的dstImage的dstSubresource中的height,
									dstOffset.z 以及 (extent.depth + dstOffset.z)必须同时大于等于0且小于等于指定的dstImage的dstSubresource中的depth
		23.如果dstImage类型为VK_IMAGE_TYPE_1D，则对pRegions的每个元素，dstOffset.y必须等于0且extent.height必须为1
		24.如果dstImage类型为VK_IMAGE_TYPE_1D 或VK_IMAGE_TYPE_2D，则对pRegions的每个元素，dstOffset.z必须等于0且extent.depth必须为1
		25.srcImage必须以VK_IMAGE_USAGE_TRANSFER_SRC_BIT 创建
		26.srcImage的format features必须包含VK_FORMAT_FEATURE_TRANSFER_SRC_BIT
		27.dstImage必须以VK_IMAGE_USAGE_TRANSFER_DST_BIT 创建
		28.dstImage的format features必须包含VK_FORMAT_FEATURE_TRANSFER_DST_BIT
		*/




		//将一个multisample color image	转换为一个单色的non-multisampled image，该命令可以对multisampled的image使用, 等价于vkCmdResolveImage2KHR
		vkCmdResolveImage2(commandBuffer, &resolveImageInfo2);
		/*
		vkCmdResolveImage2有效用法
		1.如果commandBuffer为unprotected command buffer，且不支持protectedNoFault，则srcImage,dstImage不能为一个protected image
		2.如果commandBuffer为protected command buffer，且不支持protectedNoFault，则dstImage不能为一个unprotected image
		*/


	}

}

void CopyCommandsTest::BufferMarkersCommandsTest()
{
	VkCommandBuffer commandBuffer{/*假设这是一个有效的VkCommandBuffer*/ };
	VkBuffer dstBuffer{/*假设这是一个有效的VkBuffer*/ };

	//Buffer Markers 参见p1735
	//将一个32位的标记值作为一个流水线操作写入到一个缓冲区中
	vkCmdWriteBufferMarker2AMD(commandBuffer, 
		VK_PIPELINE_STAGE_2_TRANSFER_BIT_KHR/*stage，VkPipelineStageFlagBits2值，指明哪个pipeline stage的执行完成会触发标记的写入*/, dstBuffer/* dstBuffer,为要写入标记的VkBuffer.*/,
		0/*dstOffset，是标记要写入的buffer的起始字节偏移量*/, 0/*marker，为 32-bit的标记值*/);
	/*
	vkCmdWriteBufferMarker2AMD有效用法:
	1.如果geometryShader 特性没有开启，则stage 不能包含 VK_PIPELINE_STAGE_2_GEOMETRY_SHADER_BIT
	2.如果tessellationShader 特性没有开启，则stage 不能包含 VK_PIPELINE_STAGE_2_TESSELLATION_CONTROL_SHADER_BIT 或 VK_PIPELINE_STAGE_2_TESSELLATION_EVALUATION_SHADER_BIT
	3.如果conditionalRendering 特性没有开启，则stage 不能包含 VK_PIPELINE_STAGE_2_CONDITIONAL_RENDERING_BIT_EXT
	4.如果fragmentDensityMap 特性没有开启，则stage 不能包含 VK_PIPELINE_STAGE_2_FRAGMENT_DENSITY_PROCESS_BIT_EXT
	5.如果transformFeedback 特性没有开启，则stage 不能包含 VK_PIPELINE_STAGE_2_TRANSFORM_FEEDBACK_BIT_EXT
	6.如果meshShader 特性没有开启，则stage 不能包含 VK_PIPELINE_STAGE_2_MESH_SHADER_BIT_EXT
	7.如果taskShader 特性没有开启，则stage 不能包含 VK_PIPELINE_STAGE_2_TASK_SHADER_BIT_EXT
	8.如果shadingRateImage 或 attachmentFragmentShadingRate 特性都没有开启，则stage 不能包含 VK_PIPELINE_STAGE_2_FRAGMENT_SHADING_RATE_ATTACHMENT_BIT_KHR
	9.如果subpassShading 特性没有开启，则stage 不能包含 VK_PIPELINE_STAGE_2_SUBPASS_SHADER_BIT_HUAWEI
	10.如果invocationMask 特性没有开启，则stage 不能包含 VK_PIPELINE_STAGE_2_INVOCATION_MASK_BIT_HUAWEI
	11.如果VK_NV_ray_tracing拓展或者 rayTracingPipeline 特性没有开启，则stage 不能包含 VK_PIPELINE_STAGE_2_RAY_TRACING_SHADER_BIT_KHR
	12.synchronization2特性必须开启
	13.stage 必须包含一个有效的单独的pipeline stage
	14.stage 必须包含仅一个有效的pipeline stage，且该stage必须是与commandBuffer所属的VkCommandPool的queue family所支持的stage
	15.dstOffset 必须小于或等于dstBuffer的大小减去4字节
	16.dstBuffer 必须以VK_BUFFER_USAGE_TRANSFER_DST_BIT 创建
	17.如果dstBuffer为 non-sparse的则其必须已经绑定到完整的连续的单独的VkDeviceMemory上
	18.dstOffset 必须是4的倍数
	*/


	//将一个32位的标记值作为一个流水线操作写入到一个缓冲区中
	vkCmdWriteBufferMarkerAMD(commandBuffer,
		VK_PIPELINE_STAGE_TRANSFER_BIT/*pipelineStage， VkPipelineStageFlagBits 值，指明哪个pipeline stage的执行完成会触发标记的写入*/, dstBuffer/* dstBuffer,为要写入标记的VkBuffer.*/,
		0/*dstOffset，是标记要写入的buffer的起始字节偏移量*/, 0/*marker，为 32-bit的标记值*/);
	/*
	vkCmdWriteBufferMarkerAMD有效用法:
	1.pipelineStage 必须包含仅一个有效的pipeline stage，且该pipelineStage必须是与commandBuffer所属的VkCommandPool的queue family所支持的stage
	2.如果geometryShader 特性没有开启，则pipelineStage 不能包含 VK_PIPELINE_STAGE_GEOMETRY_SHADER_BIT
	3.如果tessellationShader 特性没有开启，则pipelineStage 不能包含 VK_PIPELINE_STAGE_TESSELLATION_CONTROL_SHADER_BIT 或 VK_PIPELINE_STAGE_TESSELLATION_EVALUATION_SHADER_BIT
	4.如果conditionalRendering 特性没有开启，则pipelineStage 不能包含 VK_PIPELINE_STAGE_CONDITIONAL_RENDERING_BIT_EXT
	5.如果fragmentDensityMap 特性没有开启，则pipelineStage 不能包含 VK_PIPELINE_STAGE_FRAGMENT_DENSITY_PROCESS_BIT_EXT
	6.如果transformFeedback 特性没有开启，则pipelineStage 不能包含 VK_PIPELINE_STAGE_TRANSFORM_FEEDBACK_BIT_EXT
	7.如果meshShader 特性没有开启，则pipelineStage 不能包含 VK_PIPELINE_STAGE_MESH_SHADER_BIT_EXT
	8.如果taskShader 特性没有开启，则pipelineStage 不能包含 VK_PIPELINE_STAGE_TASK_SHADER_BIT_EXT
	9.如果shadingRateImage 或 attachmentFragmentShadingRate 特性都没有开启，则pipelineStage 不能包含 VK_PIPELINE_STAGE_FRAGMENT_SHADING_RATE_ATTACHMENT_BIT_KHR
	10.如果synchronization2特性没有开启，则pipelineStage不能为VK_PIPELINE_STAGE_NONE
	11.如果VK_NV_ray_tracing拓展或者 rayTracingPipeline 特性没有开启，则pipelineStage 不能包含 VK_PIPELINE_STAGE_RAY_TRACING_SHADER_BIT_KHR
	12.dstOffset 必须小于或等于dstBuffer的大小减去4字节
	13.dstBuffer 必须以VK_BUFFER_USAGE_TRANSFER_DST_BIT 创建
	14.如果dstBuffer为 non-sparse的则其必须已经绑定到完整的连续的单独的VkDeviceMemory上
	15.dstOffset 必须是4的倍数
	*/
}



NS_TEST_END