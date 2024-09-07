#include "MemoryDecompressionAndVideoCodingTest.h"
#include "vulkan/vulkan_beta.h"
NS_TEST_BEGIN
MemoryDecompressionAndVideoCodingTest::MemoryDecompressionAndVideoCodingTest()
{
}

void MemoryDecompressionAndVideoCodingTest::run()
{
}

MemoryDecompressionAndVideoCodingTest::~MemoryDecompressionAndVideoCodingTest()
{
}

void MemoryDecompressionAndVideoCodingTest::MemoryDecompressionTest()
{
	VkCommandBuffer commandBuffer{/*假设这是一个有效的VkCommandBuffer*/ };


	//解压缩一个或者多个内存区域中的数据
	VkDecompressMemoryRegionNV decompressMemoryRegionNV{};
	decompressMemoryRegionNV.srcAddress = VkDeviceAddress{/*假设这是一个有效的VkDeviceAddress*/ };//为压缩的数据的存储地址
	decompressMemoryRegionNV.dstAddress = VkDeviceAddress{/*假设这是一个有效的VkDeviceAddress*/ };//为要存放解压缩的数据的目的地址
	decompressMemoryRegionNV.compressedSize = 1;//为压缩的数据的字节数大小
	decompressMemoryRegionNV.decompressedSize = 2; //为解压缩的数据的字节数大小
	decompressMemoryRegionNV.decompressionMethod = VK_MEMORY_DECOMPRESSION_METHOD_GDEFLATE_1_0_BIT_NV;//一个只含有一个bit设置的 VkMemoryDecompressionMethodFlagBitsNV组合之位掩码，指明解压缩的方法。 VK_MEMORY_DECOMPRESSION_METHOD_GDEFLATE_1_0_BIT_NV : 指明 GDeflate 1.0 算法用于解压数据.
	/*
	VkDecompressMemoryRegionNV有效用法:
	1.srcAddress 必须对齐到4字节
	2.srcAddress 到 srcAddress + compressedSize地址范围中的内存必须是有效的且绑定到一个VkDeviceMemory 上
	3.dstAddress 必须对齐到4字节
	4.如果decompressionMethod 为VK_MEMORY_DECOMPRESSION_METHOD_GDEFLATE_1_0_BIT_NV，则decompressedSize必须小于等于65536 字节
	5.dstAddress 到 dstAddress + compressedSize地址范围中的内存必须是有效的且绑定到一个VkDeviceMemory 上
	6.decompressedSize 必须足够大以容纳基于decompressionMethod方法解压缩后的数据
	7.decompressionMethod 必须只有一个bit设置
	8.srcAddress 到 srcAddress + compressedSize地址范围中的内存不能和dstAddress 到 dstAddress + compressedSize地址范围中的内存有重叠
	*/

	vkCmdDecompressMemoryNV(commandBuffer, 1, &decompressMemoryRegionNV);// memoryDecompression 特性必须开启



	//解压缩一个或者多个内存区域中的数据,其中相关参数包含在buffer中
	vkCmdDecompressMemoryIndirectCountNV(commandBuffer,
		VkDeviceAddress{/*假设这是一个有效的VkDeviceAddress*/ }/*indirectCommandsAddress,为包含VkDecompressMemoryRegionNV 结构体数组的设备地址，指明相关解压缩参数.*/,
		VkDeviceAddress{/*假设这是一个有效的VkDeviceAddress*/ }/*indirectCommandsCountAddress,为存放解压缩操作次数的设备地址.*/,
		sizeof(VkDecompressMemoryRegionNV)/*stride,为indirectCommandsAddress 中连续参数组之间的字节步长.*/);
	/*
	vkCmdDecompressMemoryIndirectCountNV有效用法:
	1.memoryDecompression 特性必须开启
	2.indirectCommandsAddress 所指的buffer如果是non-sparse的，则该buffer必须绑定到完整的连续的单独的VkDeviceMemory上，且该buffer必须以VK_BUFFER_USAGE_INDIRECT_BUFFER_BIT创建
	3.indirectCommandsCountAddress 所指的buffer如果是non-sparse的，则该buffer必须绑定到完整的连续的单独的VkDeviceMemory上，且该buffer必须以VK_BUFFER_USAGE_INDIRECT_BUFFER_BIT创建
	4.indirectCommandsCountAddress 必须是4的倍数
	5.存放在indirectCommandsCountAddress中的计数值必须小于等于VkPhysicalDeviceMemoryDecompressionPropertiesNV::maxDecompressionIndirectCount
	6.stride 必须是4的倍数且大于等于sizeof(VkDecompressMemoryRegionNV) 
	7.如果存放在indirectCommandsCountAddress中的计数值为1，则(offset + sizeof(VkDecompressMemoryRegionNV)) 必须小于等于indirectCommandsAddress 所指的buffer的大小
	8.如果存放在indirectCommandsCountAddress中的计数值大于1，则indirectCommandsAddress + sizeof(VkDecompressMemoryRegionNV) + (stride × (indirectCommandsCountAddress中的计数值 - 1)) 必须小于等于indirectCommandsAddress 所指的buffer中最后一个有效的地址
	*/

}

void MemoryDecompressionAndVideoCodingTest::VideoCodingTest()
{
	/*
	vulkan 实现可能提供一个多多个队列组以及一些接口命令用来支持video 编码操作，要执行video 编码需要将相关命令记录到command buffer 然后提交进行执行。
	*/

	
	//Video Picture Resources  参见p3402
	{
		/*
		早video 编码中，多维度arrays的image可以引用为video picture resources，其可能包含一些额外的信息。

		这些image以VkImage的形式存在，其VkImageView 可以用于 decode output pictures, encode input pictures, reconstructed pictures, 以及/或者 reference pictures.
		
		*/


		//指定 video picture resource 的参数
		VkVideoPictureResourceInfoKHR videoPictureResourceInfoKHR{};
		videoPictureResourceInfoKHR.sType = VK_STRUCTURE_TYPE_VIDEO_PROFILE_INFO_KHR;
		videoPictureResourceInfoKHR.pNext = nullptr;
		videoPictureResourceInfoKHR.baseArrayLayer = 0;//为使用的基于imageViewBinding所指的VkImageView中的 array layers的索引，必须小于创建imageViewBinding的VkImageViewCreateInfo::subresourceRange.layerCount
		videoPictureResourceInfoKHR.codedExtent = VkExtent2D{ .width = 1,.height = 1 };//为要使用image subresource的texel的范围
		videoPictureResourceInfoKHR.codedOffset = VkOffset2D{ .x = 0,.y = 0 };//为要使用image subresource的texel的偏移值
		videoPictureResourceInfoKHR.imageViewBinding = VkImageView{/*假设这是一个有效的VkImageView*/ };
	

	}


	//Decoded Picture Buffer  参见p3404
	{
		/*
		一个完整的video coding pipeline将压缩的video比特流重建为图像。

		decoded picture buffer (DPB)为包含了一组可用于video coding的图像信息的可索引的数据结构，其中可索引的单独实体为 decoded picture buffer (DPB) slots。索引范围从0 到 N-1，其中N为 DPB的容量。每个DPB slot包含一个video frame，可以引用到一个picture也可以最多引用到两个picture，这两个picture分别组成video frame的top 以及bottom。其中这些slots的状态由video session管理，其他的由VkImage存储。

		另外，实现可能关联一些不透明的metadata到 DPB slots,这些数据可以由video session管理或者直接存放到 DPB slots，前者可以让这些metadata在多个video session间共享，后者则会独立于video session。
		
		*/

		
		// DPB Slot States  参见p3405
		{
			/*
			DPB slot的状态为激活或者未激活，最初都是未激活的状态。
			
			DPB slot可以在video coding中作为  picture reconstruction操作的target的时候激活，其中设置 reconstructed picture为 reference picture。

			video coding 操作是否成功可以通过 VkQueryResultStatusKHR 进行查询。

			DPB slot可以在应用端设置或者在遇到一些指定情况时执行video coding后变成未激活状态。参见p3405
			*/
		}

	}


	//Video Profiles  参见p3406
	{
		/*
		VkVideoProfileInfoKHR可以作为vkGetPhysicalDeviceVideoCapabilitiesKHR 的输入参数或者链入 vkGetPhysicalDeviceVideoFormatPropertiesKHR或者vkGetPhysicalDeviceImageFormatProperties2的pProfiles即VkVideoProfileListInfoKHR的pNext中 ，可能返回一些错误信息:
		VK_ERROR_VIDEO_PICTURE_LAYOUT_NOT_SUPPORTED_KHR : 指明请求的video picture layout（传入VkVideoProfileInfoKHR.pNext中的VkVideoDecodeH264ProfileInfoKHR的pictureLayout）不支持
		VK_ERROR_VIDEO_PROFILE_OPERATION_NOT_SUPPORTED_KHR : 指明videoCodecOperation指定的video profile operation不支持
		VK_ERROR_VIDEO_PROFILE_FORMAT_NOT_SUPPORTED_KHR : 指明chromaSubsampling, lumaBitDepth, 或者 chromaBitDepth指定的video format参数不支持
		VK_ERROR_VIDEO_PROFILE_CODEC_NOT_SUPPORTED_KHR : 指明对应video codec operation的codec-specific参数不支持
		
		*/
		VkVideoProfileInfoKHR videoProfileInfoKHR{};
		videoProfileInfoKHR.sType = VK_STRUCTURE_TYPE_VIDEO_PROFILE_INFO_KHR;
		videoProfileInfoKHR.pNext = nullptr;
		videoProfileInfoKHR.chromaBitDepth = VK_VIDEO_COMPONENT_BIT_DEPTH_12_BIT_KHR;/*VkVideoComponentBitDepthFlagBitsKHR 组合值位掩码指明 video chroma bit depth 信息
		VkVideoComponentBitDepthFlagBitsKHR:
		VK_VIDEO_COMPONENT_BIT_DEPTH_8_BIT_KHR : 指明一个 component bit depth 为 8 bits.
		VK_VIDEO_COMPONENT_BIT_DEPTH_10_BIT_KHR : 指明一个 component bit depth 为 10 bits.
		VK_VIDEO_COMPONENT_BIT_DEPTH_12_BIT_KHR : 指明一个 component bit depth 为 12 bits.
		
		*/
		videoProfileInfoKHR.chromaSubsampling = VK_VIDEO_CHROMA_SUBSAMPLING_420_BIT_KHR;/* VkVideoChromaSubsamplingFlagBitsKHR组合值位掩码指明video chroma subsampling信息
		VkVideoChromaSubsamplingFlagBitsKHR:
		VK_VIDEO_CHROMA_SUBSAMPLING_MONOCHROME_BIT_KHR : 指定format为monochrome.
		VK_VIDEO_CHROMA_SUBSAMPLING_420_BIT_KHR : 指定format为 4:2:0 chroma subsampled, 即两个chroma components的水平采样以及垂直采样的采样速率为以luma component的采样速率的一半
		VK_VIDEO_CHROMA_SUBSAMPLING_422_BIT_KHR : 指定format为 4:2:2 chroma subsampled, 即两个chroma components的水平采样的采样速率为以luma component的采样速率的一半
		VK_VIDEO_CHROMA_SUBSAMPLING_444_BIT_KHR : 指定format为 4:4:4 chroma sampled, 即Y′CBCR format的三个component的采样率相同，没有chroma subsampling
		
		*/
		videoProfileInfoKHR.lumaBitDepth = VK_VIDEO_COMPONENT_BIT_DEPTH_12_BIT_KHR;//VkVideoComponentBitDepthFlagBitsKHR 组合值位掩码指明 video luma bit depth 信息
		videoProfileInfoKHR.videoCodecOperation = VK_VIDEO_CODEC_OPERATION_DECODE_H264_BIT_KHR;/*一个 VkVideoCodecOperationFlagBitsKHR 指明video code 操作
		VkVideoCodecOperationFlagBitsKHR:
		VK_VIDEO_CODEC_OPERATION_NONE_KHR : 指定不支持任何video codec operations.
		VK_VIDEO_CODEC_OPERATION_DECODE_H264_BIT_KHR : 指定支持 H.264 decode operations.
		VK_VIDEO_CODEC_OPERATION_DECODE_H265_BIT_KHR : 指定支持 H.265 decode operations.
		VK_VIDEO_CODEC_OPERATION_DECODE_AV1_BIT_KHR : 指定支持 AV1 decode operations.
		VK_VIDEO_CODEC_OPERATION_ENCODE_H264_BIT_KHR : 指定支持 H.264 encode operations.
		VK_VIDEO_CODEC_OPERATION_ENCODE_H265_BIT_KHR : 指定支持 H.265 encode operations.
		*/
		
		/*
		VkVideoProfileInfoKHR有效用法:
		1.chromaSubsampling 必须只含有一个bit设置
		2.lumaBitDepth 必须只含有一个bit设置
		3.如果chromaSubsampling 不为VK_VIDEO_CHROMA_SUBSAMPLING_MONOCHROME_BIT_KHR，则chromaBitDepth 必须只含有一个bit设置
		4.如果videoCodecOperation 不为VK_VIDEO_CODEC_OPERATION_DECODE_H264_BIT_KHR，则pNext中必须包含一个VkVideoDecodeH264ProfileInfoKHR
		5.如果videoCodecOperation 不为VK_VIDEO_CODEC_OPERATION_DECODE_H265_BIT_KHR，则pNext中必须包含一个VkVideoDecodeH265ProfileInfoKHR
		6.如果videoCodecOperation 不为VK_VIDEO_CODEC_OPERATION_DECODE_AV1_BIT_KHR，则pNext中必须包含一个VkVideoDecodeAV1ProfileInfoKHR
		7.如果videoCodecOperation 不为VK_VIDEO_CODEC_OPERATION_ENCODE_H264_BIT_KHR，则pNext中必须包含一个VkVideoEncodeH264ProfileInfoKHR
		8.如果videoCodecOperation 不为VK_VIDEO_CODEC_OPERATION_ENCODE_H265_BIT_KHR，则pNext中必须包含一个VkVideoEncodeH265ProfileInfoKHR
		*/



		//VkVideoDecodeUsageInfoKHR 用于指定video decode使用的额外信息，添加到 VkVideoProfileInfoKHR.pNext中
		VkVideoDecodeUsageInfoKHR videoDecodeUsageInfoKHR{};
		videoDecodeUsageInfoKHR.sType = VK_STRUCTURE_TYPE_VIDEO_DECODE_USAGE_INFO_KHR;
		videoDecodeUsageInfoKHR.pNext = nullptr;
		videoDecodeUsageInfoKHR.videoUsageHints = VK_VIDEO_DECODE_USAGE_DEFAULT_KHR;/* VkVideoDecodeUsageFlagBitsKHR 组合值位掩码，指明video decode profile的预期用法提示
		VkVideoDecodeUsageFlagBitsKHR:
		VK_VIDEO_DECODE_USAGE_TRANSCODING_BIT_KHR : 指明video decoding 预期用来连接video encoding将一video bitstream以相同以及/或者不同的codecs进行转编码
		VK_VIDEO_DECODE_USAGE_OFFLINE_BIT_KHR : 指明video decoding 预期用来消耗一local video bitstream
		VK_VIDEO_DECODE_USAGE_STREAMING_BIT_KHR : 指明video decoding 预期用来消耗一作为从网络上接收的连续的流的video bitstream

		*/

		

		//VkVideoEncodeUsageInfoKHR 用于指定video encode使用的额外信息，添加到 VkVideoProfileInfoKHR.pNext中
		VkVideoEncodeUsageInfoKHR videoEncodeUsageInfoKHR{};
		videoEncodeUsageInfoKHR.sType = VK_STRUCTURE_TYPE_MAX_ENUM;//没有定义所以这里定义为非法值
		videoEncodeUsageInfoKHR.pNext = nullptr;
		videoEncodeUsageInfoKHR.tuningMode = VK_VIDEO_ENCODE_TUNING_MODE_DEFAULT_KHR;/* VkVideoEncodeTuningModeKHR 值，指明用 video profile进行编码时的调制模式
		VkVideoEncodeTuningModeKHR:
		VK_VIDEO_ENCODE_TUNING_MODE_DEFAULT_KHR : 指明为默认的调制模式
		VK_VIDEO_ENCODE_TUNING_MODE_HIGH_QUALITY_KHR : 指明video encoding要以高质量进行调制。使用该模式时，实现可能会允许视频编码操作的延迟，以提高质量
		VK_VIDEO_ENCODE_TUNING_MODE_LOW_LATENCY_KHR : 指明video encoding要以低延迟进行调制。使用该模式时，实现可能会对质量有所妥协，以提高性能以及降低video encode操作的延迟。
		VK_VIDEO_ENCODE_TUNING_MODE_ULTRA_LOW_LATENCY_KHR : 指明video encoding要以超低延迟进行调制。使用该模式时，实现可能会对质量有所妥协，以最大化性能以及最小化video encode操作的延迟。
		VK_VIDEO_ENCODE_TUNING_MODE_LOSSLESS_KHR : 指明video encoding要以无损进行调制。使用该模式时， video encode操作产生无损输出。
		
		*/
		videoEncodeUsageInfoKHR.videoContentHints = VK_VIDEO_ENCODE_CONTENT_DEFAULT_KHR;/*VkVideoEncodeContentFlagBitsKHR 组合值位掩码，指明使用video encode profile的编码内存提示
		VkVideoEncodeContentFlagBitsKHR:
		VK_VIDEO_ENCODE_CONTENT_CAMERA_BIT_KHR : 指明video encoding 预期用来编码相机内容
		VK_VIDEO_ENCODE_CONTENT_DESKTOP_BIT_KHR : 指明video encoding 预期用来编码桌面（desktop）内容
		VK_VIDEO_ENCODE_CONTENT_RENDERED_BIT_KHR : 指明video encoding 预期用来编码渲染（如游戏）内容
		*/
		videoEncodeUsageInfoKHR.videoUsageHints = VK_VIDEO_ENCODE_USAGE_DEFAULT_KHR;/*VkVideoEncodeUsageFlagBitsKHR 组合值位掩码，指明video encode profile的预期用法提示
		VkVideoEncodeUsageFlagBitsKHR:
		VK_VIDEO_ENCODE_USAGE_TRANSCODING_BIT_KHR : 指明video encoding 预期用来连接video decoding将一video bitstream以相同以及/或者不同的codecs进行转编码
		VK_VIDEO_ENCODE_USAGE_STREAMING_BIT_KHR : 指明video encoding 预期用来产生一个期望发送到网络上的作为一个连续流的 video bitstream
		VK_VIDEO_ENCODE_USAGE_RECORDING_BIT_KHR : 指明video encoding 预期用来实时记录offline consumption
		VK_VIDEO_ENCODE_USAGE_CONFERENCING_BIT_KHR : 指明video encoding 预期用在视频会议场景中
		*/


		// VkVideoProfileListInfoKHR
		VkVideoProfileListInfoKHR  videoProfileListInfoKHR{};
		videoProfileListInfoKHR.sType = VK_STRUCTURE_TYPE_VIDEO_PROFILE_LIST_INFO_KHR;
		videoProfileListInfoKHR.pNext = nullptr;
		videoProfileListInfoKHR.profileCount = 1;// pProfiles 中的元素个数
		videoProfileListInfoKHR.pProfiles = &videoProfileInfoKHR;//一组VkVideoProfileInfoKHR 数组指针，其中不能有超过一个的元素的 videoCodecOperation指明decode operation
	}


	//Video Capabilities  参见p3416
	{
		//Video Coding Capabilities 参见p3416
		{
			struct VideoCapabilitiesKHREXT {
				VkVideoDecodeAV1CapabilitiesKHR videoDecodeAV1CapabilitiesKHR{};//手动定义
				VkVideoDecodeCapabilitiesKHR videoDecodeCapabilitiesKHR{};
				VkVideoDecodeH264CapabilitiesKHR videoDecodeH264CapabilitiesKHR{};
				VkVideoDecodeH265CapabilitiesKHR videoDecodeH265CapabilitiesKHR{};
				VkVideoEncodeCapabilitiesKHR videoEncodeCapabilitiesKHR{};
				VkVideoEncodeH264CapabilitiesKHR videoEncodeH264CapabilitiesKHR{};//手动定义
				VkVideoEncodeH265CapabilitiesKHR videoEncodeH265CapabilitiesKHR{};//手动定义
				VideoCapabilitiesKHREXT() {
					Init();
				}
				void Init() {
					videoDecodeAV1CapabilitiesKHR.sType = VK_STRUCTURE_TYPE_MAX_ENUM;//没有定义，这里定义为非法值
					videoDecodeAV1CapabilitiesKHR.pNext = nullptr;
					videoDecodeCapabilitiesKHR.sType = VK_STRUCTURE_TYPE_VIDEO_DECODE_CAPABILITIES_KHR;
					videoDecodeCapabilitiesKHR.pNext = nullptr;
					videoDecodeH264CapabilitiesKHR.sType = VK_STRUCTURE_TYPE_VIDEO_DECODE_H264_CAPABILITIES_KHR;
					videoDecodeH264CapabilitiesKHR.pNext = nullptr;
					videoDecodeH265CapabilitiesKHR.sType = VK_STRUCTURE_TYPE_VIDEO_DECODE_H265_CAPABILITIES_KHR;
					videoDecodeH265CapabilitiesKHR.pNext = nullptr;
					videoEncodeCapabilitiesKHR.sType = VK_STRUCTURE_TYPE_MAX_ENUM;//没有定义，这里定义为非法值
					videoEncodeCapabilitiesKHR.pNext = nullptr;
					videoEncodeH264CapabilitiesKHR.sType = VK_STRUCTURE_TYPE_MAX_ENUM;//没有定义，这里定义为非法值
					videoEncodeH264CapabilitiesKHR.pNext = nullptr;
					videoEncodeH265CapabilitiesKHR.sType = VK_STRUCTURE_TYPE_MAX_ENUM;//没有定义，这里定义为非法值
					videoEncodeH265CapabilitiesKHR.pNext = nullptr;
				}

			};


			//查询指定video profile的 video coding容量
			VkVideoProfileInfoKHR videoProfileInfoKHR{/*假设这是一个有效的VkVideoProfileInfoKHR*/ };//前面已经描述过了，这里不再复述
			VkVideoCapabilitiesKHR videoCapabilitiesKHR{};
			videoCapabilitiesKHR.sType = VK_STRUCTURE_TYPE_VIDEO_CAPABILITIES_KHR;
			VideoCapabilitiesKHREXT videoCapabilitiesKHREXT{};
			videoCapabilitiesKHR.pNext = &videoCapabilitiesKHREXT.videoDecodeAV1CapabilitiesKHR;
			VkResult result/*返回结果信息，如果有错误间之前描述的错误信息*/ = vkGetPhysicalDeviceVideoCapabilitiesKHR(physicalDevice, &videoProfileInfoKHR, &videoCapabilitiesKHR);//假设返回了正确结果
			/*
			vkGetPhysicalDeviceVideoCapabilitiesKHR有效用法:
			1.如果pVideoProfile->videoCodecOperation指定一个decode operation，则pCapabilities->pNext中必须包含一个VkVideoDecodeCapabilitiesKHR
			2.如果pVideoProfile->videoCodecOperation为VK_VIDEO_CODEC_OPERATION_DECODE_H264_BIT_KHR，则pCapabilities->pNext中必须包含一个VkVideoDecodeH264CapabilitiesKHR
			3.如果pVideoProfile->videoCodecOperation为VK_VIDEO_CODEC_OPERATION_DECODE_H265_BIT_KHR，则pCapabilities->pNext中必须包含一个VkVideoDecodeH265CapabilitiesKHR
			4.如果pVideoProfile->videoCodecOperation为VK_VIDEO_CODEC_OPERATION_DECODE_AV1_BIT_KHR，则pCapabilities->pNext中必须包含一个VkVideoDecodeAV1CapabilitiesKHR
			5.如果pVideoProfile->videoCodecOperation指定一个encode operation，则pCapabilities->pNext中必须包含一个VkVideoEncodeCapabilitiesKHR
			6.如果pVideoProfile->videoCodecOperation为VK_VIDEO_CODEC_OPERATION_ENCODE_H264_BIT_KHR，则pCapabilities->pNext中必须包含一个VkVideoEncodeH264CapabilitiesKHR
			7.如果pVideoProfile->videoCodecOperation为VK_VIDEO_CODEC_OPERATION_ENCODE_H265_BIT_KHR，则pCapabilities->pNext中必须包含一个VkVideoEncodeH265CapabilitiesKHR
			*/

			videoCapabilitiesKHR.flags = VK_VIDEO_CAPABILITY_PROTECTED_CONTENT_BIT_KHR;/*VkVideoCapabilityFlagBitsKHR 组合值位掩码指明容量标志
			VkVideoCapabilityFlagBitsKHR:
			VK_VIDEO_CAPABILITY_PROTECTED_CONTENT_BIT_KHR : 指明video sessions 支持产生以及消耗protected内容
			VK_VIDEO_CAPABILITY_SEPARATE_REFERENCE_IMAGES_BIT_KHR : 指明关联到video session 的DPB slots的video picture resources可以存储在不同的 VkImage中。如果该标志不支持，则只能存放在同一个VkImage中（使用不同layer）
			*/
			videoCapabilitiesKHR.minBitstreamBufferOffsetAlignment = 4;//bitstream buffer的最小对齐偏移量
			videoCapabilitiesKHR.minBitstreamBufferSizeAlignment = 4;//bitstream buffer的最小范围大小
			videoCapabilitiesKHR.pictureAccessGranularity = VkExtent2D{ .width = 1,.height = 1 };//将image作为video picture resources访问时的最小访问粒度
			videoCapabilitiesKHR.minCodedExtent = VkExtent2D{ .width = 1,.height = 1 };//编码帧（frame）的最小width以及height
			videoCapabilitiesKHR.maxCodedExtent = VkExtent2D{ .width = 1,.height = 1 };//编码帧（frame）的最大width以及height
			videoCapabilitiesKHR.maxDpbSlots = 2;//一个video session中支持的最多的DPB slots的数量
			videoCapabilitiesKHR.maxActiveReferencePictures = 2;//一个 video coding 操作可以使用的active reference pictures的最大数量
			videoCapabilitiesKHR.stdHeaderVersion = VkExtensionProperties{ .extensionName = "header",.specVersion = 1 };// 为一个VkExtensionProperties，记录标准视频头名字以及video profile支持的版本

		}


		// Video Format Capabilities  参见p3419
		{
			//列举指定 video profile支持的output, input 以及 DPB image 的formats 和对应的容量
			VkPhysicalDeviceVideoFormatInfoKHR physicalDeviceVideoFormatInfoKHR{};
			physicalDeviceVideoFormatInfoKHR.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VIDEO_FORMAT_INFO_KHR;
			physicalDeviceVideoFormatInfoKHR.pNext = nullptr;//可以包含 VkVideoProfileListInfoKHR
			physicalDeviceVideoFormatInfoKHR.imageUsage = VK_IMAGE_USAGE_VIDEO_DECODE_DPB_BIT_KHR;//VkImageUsageFlagBits 组合值位掩码，指明video image的预期用途

			uint32_t videoFormatPropertyCount = 0;
			std::vector<VkVideoFormatPropertiesKHR> videoFormatPropertiesKHRs{};
			VkResult result/*返回结果信息，如果不支持 VkVideoProfileListInfoKHR::pProfiles中的任何一个则返回之前描述的错误信息，如果不支持VkPhysicalDeviceVideoFormatInfoKHR::imageUsage则返回VK_ERROR_IMAGE_USAGE_NOT_SUPPORTED_KHR*/
				= vkGetPhysicalDeviceVideoFormatPropertiesKHR(physicalDevice, &physicalDeviceVideoFormatInfoKHR, &videoFormatPropertyCount, nullptr);
			videoFormatPropertiesKHRs.resize(videoFormatPropertyCount);
			VkResult result/*返回结果信息，如果不支持 VkVideoProfileListInfoKHR::pProfiles中的任何一个则返回之前描述的错误信息，如果不支持VkPhysicalDeviceVideoFormatInfoKHR::imageUsage则返回VK_ERROR_IMAGE_USAGE_NOT_SUPPORTED_KHR*/
				= vkGetPhysicalDeviceVideoFormatPropertiesKHR(physicalDevice, &physicalDeviceVideoFormatInfoKHR, &videoFormatPropertyCount, videoFormatPropertiesKHRs.data());//假设成功返回了一个元素
			/*
			vkGetPhysicalDeviceVideoFormatPropertiesKHR接口使用的一些其他重要信息见p3420


			vkGetPhysicalDeviceVideoFormatPropertiesKHR有效用法:
			1. pVideoFormatInfo->pNext中必须包含一个 profileCount 大于0的  VkVideoProfileListInfoKHR

			*/

			VkVideoFormatPropertiesKHR& videoFormatPropertiesKHR = videoFormatPropertiesKHRs[0];
			videoFormatPropertiesKHR.sType = VK_STRUCTURE_TYPE_VIDEO_FORMAT_PROPERTIES_KHR;
			videoFormatPropertiesKHR.pNext = nullptr;
			videoFormatPropertiesKHR.format = VK_FORMAT_R8G8B8A8_SRGB;//一个 VkFormat 值指明可以和指定的video profiles以及  image usages 使用的format
			videoFormatPropertiesKHR.componentMapping = VkComponentMapping{ .r = VK_COMPONENT_SWIZZLE_IDENTITY,
																		   .g = VK_COMPONENT_SWIZZLE_IDENTITY,
																		   .b = VK_COMPONENT_SWIZZLE_IDENTITY ,
																		   .a = VK_COMPONENT_SWIZZLE_IDENTITY };//一个 VkComponentMapping 值指明format的颜色通道的顺序，用于描述从video encoder input 到产生video decoder output颜色通道顺序如何重新排列
			videoFormatPropertiesKHR.imageCreateFlags = VK_IMAGE_CREATE_DISJOINT_BIT;//VkImageCreateFlagBits 组合值位掩码指明该format支持的image创建标志
			videoFormatPropertiesKHR.imageType = VK_IMAGE_TYPE_2D;//VkImageType 值指明该format支持的image类型
			videoFormatPropertiesKHR.imageTiling = VK_IMAGE_TILING_OPTIMAL;//VkImageTiling 值指明该format支持的image tiling
			videoFormatPropertiesKHR.imageUsageFlags = VK_IMAGE_USAGE_VIDEO_DECODE_DPB_BIT_KHR;//VkImageUsageFlagBits 组合值位掩码指明该format支持的image用途





		}
	}



	// Video Session  参见p3425
	{
		/*
		video sessions 用于表达和维护使用指定 video profile的video decode 或者 encode操作状态的对象
		
		*/


		VkVideoSessionKHR videoSessionKHR{};

		//Creating a Video Session  参见p3425
		{
			VkVideoProfileInfoKHR videoProfileInfoKHR{/*假设这是一个有效的VkVideoProfileInfoKHR*/ };//前面已经描述过了，这里不再复述
			VkExtensionProperties extensionProperties{/*假设这是一个有效的VkExtensionProperties*/ };//前面已经描述过了，这里不再复述


			struct VideoSessionCreateInfoKHREXT {

				VkVideoEncodeH264SessionCreateInfoKHR videoEncodeH264SessionCreateInfoKHR{};
				VkVideoEncodeH265SessionCreateInfoKHR videoEncodeH265SessionCreateInfoKHR{};
				VideoSessionCreateInfoKHREXT() {
					Init();
				}
				void Init() {
					videoEncodeH264SessionCreateInfoKHR.sType = VK_STRUCTURE_TYPE_MAX_ENUM;//没有定义，这里定义为非法值
					videoEncodeH264SessionCreateInfoKHR.pNext = nullptr;
					videoEncodeH265SessionCreateInfoKHR.sType = VK_STRUCTURE_TYPE_MAX_ENUM;//没有定义，这里定义为非法值
					videoEncodeH265SessionCreateInfoKHR.pNext = nullptr;

				}
			};


			VkVideoSessionCreateInfoKHR videoSessionCreateInfoKHR{};
			videoSessionCreateInfoKHR.sType = VK_STRUCTURE_TYPE_VIDEO_SESSION_CREATE_INFO_KHR;
			VideoSessionCreateInfoKHREXT videoSessionCreateInfoKHREXT{};
			videoSessionCreateInfoKHR.pNext = &videoSessionCreateInfoKHREXT.videoEncodeH264SessionCreateInfoKHR;
			videoSessionCreateInfoKHR.queueFamilyIndex = 0;//为创建的session 要使用的queue family index
			videoSessionCreateInfoKHR.flags = VK_VIDEO_SESSION_CREATE_PROTECTED_CONTENT_BIT_KHR;/* VkVideoSessionCreateFlagBitsKHR 组合值位掩码，指明创建标志
			VkVideoSessionCreateFlagBitsKHR:
			VK_VIDEO_SESSION_CREATE_PROTECTED_CONTENT_BIT_KHR : 指定创建的session使用protected video content
			VK_VIDEO_SESSION_CREATE_ALLOW_ENCODE_PARAMETER_OPTIMIZATIONS_BIT_KHR : 指定实现可以基于指定的video profile的信息以及使用的video encode quality level 允许重写video session以及codec-specific参数以优化video encode operations
			VK_VIDEO_SESSION_CREATE_INLINE_QUERIES_BIT_KHR : 指定创建的session可以在video coding内部执行queries

			*/
			videoSessionCreateInfoKHR.pVideoProfile = &videoProfileInfoKHR;//一个VkVideoProfileInfoKHR 指针，指明要使用的video profile
			videoSessionCreateInfoKHR.pictureFormat = VK_FORMAT_R8G8B8A8_SRGB;//VkFormat 值指明要使用的image format.要为pVideoProfile->videoCodecOperation 所对的picture可用的format
			videoSessionCreateInfoKHR.maxCodedExtent = VkExtent2D{ .width = 1,.height = 1 };//为创建的session要使用的编码帧（frame）的最大width以及height
			videoSessionCreateInfoKHR.referencePictureFormat = VK_FORMAT_R8G8B8A8_SRGB;//VkFormat 值指明创建的session要使用的存放在PDB 中的reference picture format.
			videoSessionCreateInfoKHR.maxDpbSlots = 2;//为创建的session要使用的DPB slots的最大数量
			videoSessionCreateInfoKHR.maxActiveReferencePictures = 2;//为创建的session在一个 video coding操作中可使用的active reference pictures的最大数量
			videoSessionCreateInfoKHR.pStdHeaderVersion = &extensionProperties;//为 VkExtensionProperties 指针，记录pVideoProfile->videoCodecOperation 要使用的标准视频头名字以及video profile支持的版本
			/*
			VkVideoSessionCreateInfoKHR有效用法:
			1.如果 protectedMemory特性未开启或者如果调用vkGetPhysicalDeviceVideoCapabilitiesKHR传入pVideoProfile所指的video profile返回的 VkVideoCapabilitiesKHR::flags 不包含VK_VIDEO_CAPABILITY_PROTECTED_CONTENT_BIT_KHR，则flags 不能包含VK_VIDEO_SESSION_CREATE_PROTECTED_CONTENT_BIT_KHR
			2.如果flags 包含VK_VIDEO_SESSION_CREATE_INLINE_QUERIES_BIT_KHR ，则videoMaintenance1 必须开启
			3.pVideoProfile 必须是一个支持的video profile
			4.maxDpbSlots 必须小于等于调用vkGetPhysicalDeviceVideoCapabilitiesKHR传入pVideoProfile所指的video profile返回的  VkVideoCapabilitiesKHR::maxDpbSlots
			5.maxActiveReferencePictures 必须小于等于调用vkGetPhysicalDeviceVideoCapabilitiesKHR传入pVideoProfile所指的video profile返回的  VkVideoCapabilitiesKHR::maxActiveReferencePictures
			6.如果maxDpbSlots 或者 maxActiveReferencePictures 为0，则另一个值也必须为0
			7.maxCodedExtent 必须在调用vkGetPhysicalDeviceVideoCapabilitiesKHR传入pVideoProfile所指的video profile返回的VkVideoCapabilitiesKHR::minCodedExtent 和 VkVideoCapabilitiesKHR::maxCodedExtent 之间
			8.如果pVideoProfile->videoCodecOperation 指定一个decode operation 且maxActiveReferencePictures 大于0，则referencePictureFormat 必须是支持的一个decode DPB formats，参见调用vkGetPhysicalDeviceVideoFormatPropertiesKHR 返回的 VkVideoFormatPropertiesKHR::format，调用参数pVideoFormatInfo->imageUsage 必须包含VK_IMAGE_USAGE_VIDEO_DECODE_DPB_BIT_KHR，且pVideoFormatInfo->pNetx中必须包含一个VkVideoProfileListInfoKHR，VkVideoProfileListInfoKHR.pProfiles必须包含一个与pVideoProfile匹配的profile
			9.如果pVideoProfile->videoCodecOperation 指定一个encode operation 且maxActiveReferencePictures 大于0，则referencePictureFormat 必须是支持的一个decode 以及encode DPB formats，参见调用vkGetPhysicalDeviceVideoFormatPropertiesKHR 返回的 VkVideoFormatPropertiesKHR::format，调用参数pVideoFormatInfo->imageUsage 必须包含VK_IMAGE_USAGE_VIDEO_ENCODE_DPB_BIT_KHR，且pVideoFormatInfo->pNetx中必须包含一个VkVideoProfileListInfoKHR，VkVideoProfileListInfoKHR.pProfiles必须包含一个与pVideoProfile匹配的profile
			10.如果pVideoProfile->videoCodecOperation 指定一个decode operation ，则pictureFormat 必须是支持的一个decode output formats，参见调用vkGetPhysicalDeviceVideoFormatPropertiesKHR 返回的 VkVideoFormatPropertiesKHR::format，调用参数pVideoFormatInfo->imageUsage 必须包含VK_IMAGE_USAGE_VIDEO_DECODE_DST_BIT_KHR，且pVideoFormatInfo->pNetx中必须包含一个VkVideoProfileListInfoKHR，VkVideoProfileListInfoKHR.pProfiles必须包含一个与pVideoProfile匹配的profile
			11.如果pVideoProfile->videoCodecOperation 指定一个encode operation ，则pictureFormat 必须是支持的一个encode input formats，参见调用vkGetPhysicalDeviceVideoFormatPropertiesKHR 返回的 VkVideoFormatPropertiesKHR::format，调用参数pVideoFormatInfo->imageUsage 必须包含VK_IMAGE_USAGE_VIDEO_ENCODE_SRC_BIT_KHR，且pVideoFormatInfo->pNetx中必须包含一个VkVideoProfileListInfoKHR，VkVideoProfileListInfoKHR.pProfiles必须包含一个与pVideoProfile匹配的profile
			12.pStdHeaderVersion->extensionName 必须匹配调用vkGetPhysicalDeviceVideoCapabilitiesKHR传入pVideoProfile所指的video profile返回的  VkVideoCapabilitiesKHR::stdHeaderVersion.extensionName
			13.pStdHeaderVersion->specVersion 必须小于等于调用vkGetPhysicalDeviceVideoCapabilitiesKHR传入pVideoProfile所指的video profile返回的  VkVideoCapabilitiesKHR::stdHeaderVersion.specVersion
			14.如果pVideoProfile->videoCodecOperation 为VK_VIDEO_CODEC_OPERATION_ENCODE_H264_BIT_KHR，且pNext中包含一个VkVideoEncodeH264SessionCreateInfoKHR，则VkVideoEncodeH264SessionCreateInfoKHR.maxLevelIdc 必须小于等于调用vkGetPhysicalDeviceVideoCapabilitiesKHR传入pVideoProfile所指的video profile返回的 VkVideoEncodeH264CapabilitiesKHR::maxLevelIdc
			15.如果pVideoProfile->videoCodecOperation 为VK_VIDEO_CODEC_OPERATION_ENCODE_H265_BIT_KHR，且pNext中包含一个VkVideoEncodeH265SessionCreateInfoKHR，则VkVideoEncodeH265SessionCreateInfoKHR.maxLevelIdc 必须小于等于调用vkGetPhysicalDeviceVideoCapabilitiesKHR传入pVideoProfile所指的video profile返回的 VkVideoEncodeH265CapabilitiesKHR::maxLevelIdc
			*/


			//该接口使用的一些其他注意信息见p3425
			vkCreateVideoSessionKHR(device, &videoSessionCreateInfoKHR, nullptr, &videoSessionKHR);

		}

		//Destroying a Video Session 参见p3432
		{
			//销毁VkVideoSessionKHR
			vkDestroyVideoSessionKHR(device, videoSessionKHR, nullptr);
			/*
			vkDestroyVideoSessionKHR有效用法:
			1.引用到videoSession 的提交的命令必须完成执行
			2.如果创建 videoSession 时提供了 VkAllocationCallbacks，则这里也需要提供一个兼容的callback函数
			3.如果创建 videoSession 时没有提供 VkAllocationCallbacks，则pAllocator 必须为NULL

			*/
		}


		//Video Session Memory Association  参见p3432
		{
			/*
			在创建了 video session后，在使用该video session进行视频编码操作之前，需要将video session 绑定到内存对象上。内存的分配是分离的。session 可能根据一个无符号整数值（memory binding）进行内存绑定且可能进行多次。

			*/


			//查询video session的内存需求
			uint32_t videomSessionMemoryRequirementsCount = 0;
			std::vector<VkVideoSessionMemoryRequirementsKHR> videoSessionMemoryRequirementsKHRs{};
			vkGetVideoSessionMemoryRequirementsKHR(device, videoSessionKHR, &videomSessionMemoryRequirementsCount, nullptr);
			videoSessionMemoryRequirementsKHRs.resize(videomSessionMemoryRequirementsCount);
			vkGetVideoSessionMemoryRequirementsKHR(device, videoSessionKHR, &videomSessionMemoryRequirementsCount, videoSessionMemoryRequirementsKHRs.data());//假设成功返回了一个元素

			VkVideoSessionMemoryRequirementsKHR& videoSessionMemoryRequirementsKHR = videoSessionMemoryRequirementsKHRs[0];
			videoSessionMemoryRequirementsKHR.sType = VK_STRUCTURE_TYPE_VIDEO_SESSION_MEMORY_REQUIREMENTS_KHR;
			videoSessionMemoryRequirementsKHR.pNext = nullptr;
			videoSessionMemoryRequirementsKHR.memoryBindIndex = 0;//为 memory binding的索引
			videoSessionMemoryRequirementsKHR.memoryRequirements = VkMemoryRequirements{ .size = 1024, .alignment = 16, .memoryTypeBits = 0x0000000F }/*假设这是一个有效的VkMemoryRequirements*/;// VkMemoryRequirements 值，指明memoryBindIndex 所指的memory binding所需的内存需求



			//绑定memory到video session
			VkBindVideoSessionMemoryInfoKHR bindVideoSessionMemoryInfoKHR{};
			bindVideoSessionMemoryInfoKHR.sType = VK_STRUCTURE_TYPE_BIND_VIDEO_SESSION_MEMORY_INFO_KHR;
			bindVideoSessionMemoryInfoKHR.pNext = nullptr;
			bindVideoSessionMemoryInfoKHR.memory = VkDeviceMemory{/*假设这是一个有效的VkDeviceMemory*/ };//为分配的要绑定到video session的 memoryBindIndex所指的memory binding的设备内存
			bindVideoSessionMemoryInfoKHR.memoryBindIndex = 0;//为要绑定的 memory binding的索引
			bindVideoSessionMemoryInfoKHR.memoryOffset = 0;//为memory 中要绑定的内存的起始字节偏移量
			bindVideoSessionMemoryInfoKHR.memorySize = 1;//为memory 中要绑定的从memoryOffset开始的内存字节范围
			/*
			VkBindVideoSessionMemoryInfoKHR有效用法:
			1.memoryOffset 必须小于等于memory的大小
			2.memorySize 必须小于等于memory的大小减去memoryOffset
			*/


			vkBindVideoSessionMemoryKHR(device, videoSessionKHR, 1, &bindVideoSessionMemoryInfoKHR);
			/*
			vkBindVideoSessionMemoryKHR有效用法:
			1.pBindSessionMemoryInfos 中任何元素的memoryBindIndex 所指的 memory binding不能已经绑定到一个内存对象
			2.pBindSessionMemoryInfos 中每个元素的memoryBindIndex 在pBindSessionMemoryInfos 中必须是唯一的
			3.pBindSessionMemoryInfos 中每个元素必须有一个对应的VkMemoryRequirements
			4.如果pBindSessionMemoryInfos的一个元素由一个对应的VkMemoryRequirements，则该元素的memory对象必须使用其对应的VkMemoryRequirements的memoryTypeBits中类型创建
			5.如果pBindSessionMemoryInfos的一个元素由一个对应的VkMemoryRequirements，则该元素的memoryOffset 必须是其对应的VkMemoryRequirements的alignment的整数倍
			6.如果pBindSessionMemoryInfos的一个元素由一个对应的VkMemoryRequirements，则该元素的memorySize 必须等于其对应的VkMemoryRequirements的size
			*/


		}
	}



	//Video Profile Compatibility  参见p3437
	{
		/*
		在 video session 中使用的和 video profile 兼容的资源以及queryPool的创建需要满足一定条件。

		对VkBuffer:
			 VkBufferCreateInfo::pNext 包含一个其 pProfiles中含有一个元素匹配video profile的 VkVideoProfileListInfoKHR ，VkBufferCreateInfo::usage 含有VK_BUFFER_USAGE_VIDEO_DECODE_SRC_BIT_KHR ，VK_BUFFER_USAGE_VIDEO_DECODE_DST_BIT_KHR， VK_BUFFER_USAGE_VIDEO_ENCODE_SRC_BIT_KHR， 或者VK_BUFFER_USAGE_VIDEO_ENCODE_DST_BIT_KHR。 或者 VkBufferCreateInfo::flags 含 VK_BUFFER_CREATE_VIDEO_PROFILE_INDEPENDENT_BIT_KHR
		对VkImage
			 VkImageCreateInfo::pNext 包含一个其 pProfiles中含有一个元素匹配video profile的 VkVideoProfileListInfoKHR , VkImageCreateInfo::usage含有 VK_IMAGE_USAGE_VIDEO_DECODE_SRC_BIT_KHR，VK_IMAGE_USAGE_VIDEO_DECODE_DST_BIT_KHR，VK_IMAGE_USAGE_VIDEO_DECODE_DPB_BIT_KHR，VK_IMAGE_USAGE_VIDEO_ENCODE_SRC_BIT_KHR，VK_IMAGE_USAGE_VIDEO_ENCODE_DST_BIT_KHR 或者VK_IMAGE_USAGE_VIDEO_ENCODE_DPB_BIT_KHR。
			 或者 VkImageCreateInfo::flags 含  VK_IMAGE_CREATE_VIDEO_PROFILE_INDEPENDENT_BIT_KHR.然后VkImageCreateInfo的 format ，flags，imageType，tiling要等与vkGetPhysicalDeviceVideoFormatPropertiesKHR返回的VkVideoFormatPropertiesKHR中的相应值，usage要包含在其相应值中。
		对VkImageView:
			只要满足其VkImage兼容即可
		对VkQueryPool:
			VkQueryPoolCreateInfo::pNext 包含一个其 pProfiles中含有一个元素匹配video profile的 VkVideoProfileListInfoKHR ，VkQueryPoolCreateInfo::queryType 含有VK_QUERY_TYPE_RESULT_STATUS_ONLY_KHR 或者 VK_QUERY_TYPE_VIDEO_ENCODE_FEEDBACK_KHR
		*/
	}

	//Video Session Parameters 参见p3438
	{
		/*
		video session parameters 用来存放使用在video session的预处理codec-specific参数的对象。能够在记录video coding 操作到command buffer时使用的参数数量。

		存储在video session parameters 对象中的参数不可改变，要加入新的参数，需要调用 vkUpdateVideoSessionParametersKHR ，每调用一次，其内部 update sequence counter递增1
	
		对于不同的video codec operation其video session parameters 中存储的参数不尽相同。
		*/


		VkVideoSessionParametersKHR videoSessionParametersKHR{};

		// Creating Video Session Parameters  参见p3439
		{

			struct VideoSessionParametersCreateInfoKHREXT {
				VkVideoDecodeAV1SessionParametersCreateInfoKHR  videoDecodeAV1SessionParametersCreateInfoKHR{};
				VkVideoDecodeH264SessionParametersCreateInfoKHR videoDecodeH264SessionParametersCreateInfoKHR{};
				VkVideoDecodeH265SessionParametersCreateInfoKHR videoDecodeH265SessionParametersCreateInfoKHR{};
				VkVideoEncodeH264SessionParametersCreateInfoKHR videoEncodeH264SessionParametersCreateInfoKHR{};
				VkVideoEncodeH265SessionParametersCreateInfoKHR videoEncodeH265SessionParametersCreateInfoKHR{};
				VkVideoEncodeQualityLevelInfoKHR videoEncodeQualityLevelInfoKHR{};
				VideoSessionParametersCreateInfoKHREXT() {
					Init();
				}
				void Init() {
					videoDecodeAV1SessionParametersCreateInfoKHR.sType = VK_STRUCTURE_TYPE_MAX_ENUM;//没有定义，这里定义为非法值
					videoDecodeAV1SessionParametersCreateInfoKHR.pNext = nullptr;
					videoDecodeH264SessionParametersCreateInfoKHR.sType = VK_STRUCTURE_TYPE_VIDEO_DECODE_H264_SESSION_PARAMETERS_CREATE_INFO_KHR;
					videoDecodeH264SessionParametersCreateInfoKHR.pNext = nullptr;
					videoDecodeH265SessionParametersCreateInfoKHR.sType = VK_STRUCTURE_TYPE_VIDEO_DECODE_H265_SESSION_PARAMETERS_CREATE_INFO_KHR;
					videoDecodeH265SessionParametersCreateInfoKHR.pNext = nullptr;
					videoEncodeH264SessionParametersCreateInfoKHR.sType = VK_STRUCTURE_TYPE_MAX_ENUM;//没有定义，这里定义为非法值
					videoEncodeH264SessionParametersCreateInfoKHR.pNext = nullptr;
					videoEncodeH265SessionParametersCreateInfoKHR.sType = VK_STRUCTURE_TYPE_MAX_ENUM;//没有定义，这里定义为非法值
					videoEncodeH265SessionParametersCreateInfoKHR.pNext = nullptr;
					videoEncodeQualityLevelInfoKHR.sType = VK_STRUCTURE_TYPE_MAX_ENUM;//没有定义，这里定义为非法值
					videoEncodeQualityLevelInfoKHR.pNext = nullptr;


				}
			};


			VkVideoSessionParametersCreateInfoKHR videoSessionParametersCreateInfoKHR{};//该结构体根据videoSession的对应video codec operation 不同，可以容纳在该结构体中的参数存在一些限制，具体见 *** p3445 - p3447 （简单将就是先装入pNext中VkVideoEncodeH265SessionParametersCreateInfoKHR的相关参数，再装入videoSessionParametersTemplate中不重复的参数）
			videoSessionParametersCreateInfoKHR.sType = VK_STRUCTURE_TYPE_VIDEO_SESSION_PARAMETERS_CREATE_INFO_KHR;
			VideoSessionParametersCreateInfoKHREXT videoSessionParametersCreateInfoKHREXT{};
			videoSessionParametersCreateInfoKHR.pNext = &videoSessionParametersCreateInfoKHREXT.videoDecodeAV1SessionParametersCreateInfoKHR;
			videoSessionParametersCreateInfoKHR.flags = 0;//保留未来使用
			videoSessionParametersCreateInfoKHR.videoSession = VkVideoSessionKHR{/*假设这是一个有效的VkVideoSessionKHR*/ };//为video session parameters 要对哪个video session创建
			videoSessionParametersCreateInfoKHR.videoSessionParametersTemplate = VkVideoSessionParametersKHR{/*假设这是一个有效的VkVideoSessionParametersKHR*/ };//如果不为VK_NULL_HANDLE则必须是一个有效的VkVideoSessionParametersKHR，用于将该对象中的参数作为模板创建一个新的video session parameters VkVideoSessionParametersKHR对象
			/*
			VkVideoSessionParametersCreateInfoKHR有效用法:
			1.如果videoSessionParametersTemplate 不为VK_NULL_HANDLE，则（1）其必须是对videoSession 创建的
																	   （2）如果videoSession 以一个encode operation 创建，则videoSession的qualityLevel 必须等于videoSessionParametersTemplate创建时的video encode quality level
			2.如果videoSession 以video codec operation VK_VIDEO_CODEC_OPERATION_DECODE_H264_BIT_KHR创建，则（1）pNext中必须包含一个VkVideoDecodeH264SessionParametersCreateInfoKHR
																										   （2）pNext中VkVideoDecodeH264SessionParametersCreateInfoKHR的spsAddList的元素数量必须小于等于其maxStdSPSCount
																										   （3）pNext中VkVideoDecodeH264SessionParametersCreateInfoKHR的ppsAddList的元素数量必须小于等于其maxStdPPSCount
			3.如果videoSession 以video codec operation VK_VIDEO_CODEC_OPERATION_DECODE_H265_BIT_KHR创建，则（1）pNext中必须包含一个VkVideoDecodeH265SessionParametersCreateInfoKHR
																										   （2）pNext中VkVideoDecodeH265SessionParametersCreateInfoKHR的vpsAddList的元素数量必须小于等于其maxStdVPSCount
																										   （3）pNext中VkVideoDecodeH265SessionParametersCreateInfoKHR的spsAddList的元素数量必须小于等于其maxStdSPSCount
																										   （4）pNext中VkVideoDecodeH265SessionParametersCreateInfoKHR的ppsAddList的元素数量必须小于等于其maxStdPPSCount
			4.如果videoSession 以video codec operation VK_VIDEO_CODEC_OPERATION_DECODE_AV1_BIT_KHR创建，则 （1）videoSessionParametersTemplate 必须为VK_NULL_HANDLE
																										   （2）pNext中必须包含一个VkVideoDecodeAV1SessionParametersCreateInfoKHR
			5.如果videoSession 以video codec operation VK_VIDEO_CODEC_OPERATION_ENCODE_H264_BIT_KHR创建，则（1）pNext中必须包含一个VkVideoEncodeH264SessionParametersCreateInfoKHR
																										   （2）pNext中VkVideoEncodeH264SessionParametersCreateInfoKHR的spsAddList的元素数量必须小于等于其maxStdSPSCount
																										   （3）pNext中VkVideoEncodeH264SessionParametersCreateInfoKHR的ppsAddList的元素数量必须小于等于其maxStdPPSCount
			6.如果videoSession 以video codec operation VK_VIDEO_CODEC_OPERATION_ENCODE_H265_BIT_KHR创建，则（1）pNext中必须包含一个VkVideoEncodeH265SessionParametersCreateInfoKHR
																										   （2）pNext中VkVideoEncodeH265SessionParametersCreateInfoKHR的vpsAddList的元素数量必须小于等于其maxStdVPSCount
																										   （3）pNext中VkVideoEncodeH265SessionParametersCreateInfoKHR的spsAddList的元素数量必须小于等于其maxStdSPSCount
																										   （4）pNext中VkVideoEncodeH265SessionParametersCreateInfoKHR的ppsAddList的元素数量必须小于等于其maxStdPPSCount
																										   （5）对每个ppsAddList中的元素，其num_tile_columns_minus1 必须小于调用 vkGetPhysicalDeviceVideoCapabilitiesKHR 传入videoSession 创建时的video profile 返回 VkVideoEncodeH265CapabilitiesKHR::maxTiles.width
																										   （6）对每个ppsAddList中的元素，其num_tile_rows_minus1 必须小于调用 vkGetPhysicalDeviceVideoCapabilitiesKHR 传入videoSession 创建时的video profile 返回 VkVideoEncodeH265CapabilitiesKHR::maxTiles.height

			*/



			//创建  ，创建过程中该参数对象根据不同的video codec operation装入了那些参数，如何装入见  *** p3441 - p3443
			vkCreateVideoSessionParametersKHR(device, &videoSessionParametersCreateInfoKHR, nullptr, &videoSessionParametersKHR);

		}


		//Destroying Video Session Parameters  参见p3451
		{
			//销毁
			vkDestroyVideoSessionParametersKHR(device, videoSessionParametersKHR, nullptr);
			/*
			vkDestroyVideoSessionParametersKHR有效用法:
			1.引用到videoSessionParameters 的提交的命令必须完成执行
			2.如果创建 videoSessionParameters 时提供了 VkAllocationCallbacks，则这里也需要提供一个兼容的callback函数
			3.如果创建 videoSessionParameters 时没有提供 VkAllocationCallbacks，则pAllocator 必须为NULL
			*/
		}


		// Updating Video Session Parameters  参见p3452
		{
			//更新

			VkVideoSessionParametersUpdateInfoKHR videoSessionParametersUpdateInfoKHR{};
			videoSessionParametersUpdateInfoKHR.sType = VK_STRUCTURE_TYPE_VIDEO_SESSION_PARAMETERS_CREATE_INFO_KHR;
			videoSessionParametersUpdateInfoKHR.pNext = nullptr;//可以包含VkVideoDecodeH264SessionParametersAddInfoKHR, VkVideoDecodeH265SessionParametersAddInfoKHR, VkVideoEncodeH264SessionParametersAddInfoKHR, 或者 VkVideoEncodeH265SessionParametersAddInfoKHR
			videoSessionParametersUpdateInfoKHR.updateSequenceCount = 1;//为为该video session parameters 设置的新的 update sequence count 值

			//当命令执行成功后，  videoSessionParameters中的 update sequence counter就会变为pUpdateInfo->updateSequenceCount ，如果pUpdateInfo->pNext 中包含一些别的参数，则这些参数会添加到该videoSessionParameters对象中，具体添加什么，怎么添加根据videoSessionParameters所对的codec-specific operation的类型有所区别
			vkUpdateVideoSessionParametersKHR(device, videoSessionParametersKHR/* videoSessionParameters*/, &videoSessionParametersUpdateInfoKHR/*pUpdateInfo*/);
			/*
			vkUpdateVideoSessionParametersKHR有效用法:
			1.pUpdateInfo->updateSequenceCount 必须等于当前videoSessionParameters的 update sequence counter加1
			2.如果videoSessionParameters 以video codec operation VK_VIDEO_CODEC_OPERATION_DECODE_H264_BIT_KHR创建，则（1）如果pUpdateInfo->pNext中包含一个VkVideoDecodeH264SessionParametersAddInfoKHR，则当前videoSessionParameters 中不能包含一个seq_parameter_set_id 匹配VkVideoDecodeH264SessionParametersAddInfoKHR::pStdSPSs 中任何元素的 StdVideoH264SequenceParameterSet实体
																													 （2）当前videoSessionParameters 中存储的 StdVideoH264SequenceParameterSet实体的数量加上pUpdateInfo->pNext中的VkVideoDecodeH264SessionParametersAddInfoKHR::stdSPSCount 必须小于等于创建videoSessionParameters 的 VkVideoDecodeH264SessionParametersCreateInfoKHR::maxStdSPSCount
																													 （3）如果pUpdateInfo->pNext中包含一个VkVideoDecodeH264SessionParametersAddInfoKHR，则当前videoSessionParameters 中不能包含一个seq_parameter_set_id 以及pic_parameter_set_id 都匹配VkVideoDecodeH264SessionParametersAddInfoKHR::pStdPPSs 中任何元素的 StdVideoH264PictureParameterSet实体
																													 （4）当前videoSessionParameters 中存储的 StdVideoH264PictureParameterSet实体的数量加上pUpdateInfo->pNext中的VkVideoDecodeH264SessionParametersAddInfoKHR::stdPPSCount 必须小于等于创建videoSessionParameters 的 VkVideoDecodeH264SessionParametersCreateInfoKHR::maxStdPPSCount

			3.如果videoSessionParameters 以video codec operation VK_VIDEO_CODEC_OPERATION_DECODE_H265_BIT_KHR创建，则（1）如果pUpdateInfo->pNext中包含一个VkVideoDecodeH265SessionParametersAddInfoKHR，则当前videoSessionParameters 中不能包含一个vps_video_parameter_set_id 匹配VkVideoDecodeH265SessionParametersAddInfoKHR::pStdVPSs 中任何元素的 StdVideoH265VideoParameterSet实体
																													 （2）当前videoSessionParameters 中存储的 StdVideoH265VideoParameterSet实体的数量加上pUpdateInfo->pNext中的VkVideoDecodeH265SessionParametersAddInfoKHR::stdVPSCount 必须小于等于创建videoSessionParameters 的 VkVideoDecodeH265SessionParametersCreateInfoKHR::maxStdVPSCount
																													 （3）如果pUpdateInfo->pNext中包含一个VkVideoDecodeH265SessionParametersAddInfoKHR，则当前videoSessionParameters 中不能包含一个sps_video_parameter_set_id 和 sps_seq_parameter_set_id 都匹配VkVideoDecodeH265SessionParametersAddInfoKHR::pStdSPSs 中任何元素的 StdVideoH265SequenceParameterSet实体
																													 （4）当前videoSessionParameters 中存储的 StdVideoH265SequenceParameterSet实体的数量加上pUpdateInfo->pNext中的VkVideoDecodeH265SessionParametersAddInfoKHR::stdSPSCount 必须小于等于创建videoSessionParameters 的 VkVideoDecodeH265SessionParametersCreateInfoKHR::maxStdSPSCount
																													 （5）如果pUpdateInfo->pNext中包含一个VkVideoDecodeH265SessionParametersAddInfoKHR，则当前videoSessionParameters 中不能包含一个sps_video_parameter_set_id, pps_seq_parameter_set_id, 以及 pps_pic_parameter_set_id 全都匹配VkVideoDecodeH265SessionParametersAddInfoKHR::pStdPPSs 中任何元素的 StdVideoH265PictureParameterSet实体
																													 （6）当前videoSessionParameters 中存储的 StdVideoH265PictureParameterSet实体的数量加上pUpdateInfo->pNext中的VkVideoDecodeH265SessionParametersAddInfoKHR::stdPPSCount 必须小于等于创建videoSessionParameters 的 VkVideoDecodeH265SessionParametersCreateInfoKHR::maxStdPPSCount

			4.如果videoSessionParameters 不能以video codec operation为 VK_VIDEO_CODEC_OPERATION_DECODE_AV1_BIT_KHR创建
			5.如果videoSessionParameters 以video codec operation VK_VIDEO_CODEC_OPERATION_ENCODE_H264_BIT_KHR创建，则（1）如果pUpdateInfo->pNext中包含一个VkVideoEncodeH264SessionParametersAddInfoKHR，则当前videoSessionParameters 中不能包含一个seq_parameter_set_id 匹配VkVideoEncodeH264SessionParametersAddInfoKHR::pStdSPSs 中任何元素的 StdVideoH264SequenceParameterSet实体
																													 （2）当前videoSessionParameters 中存储的 StdVideoH264SequenceParameterSet实体的数量加上pUpdateInfo->pNext中的VkVideoEncodeH264SessionParametersAddInfoKHR::stdSPSCount 必须小于等于创建videoSessionParameters 的 VkVideoEncodeH264SessionParametersCreateInfoKHR::maxStdSPSCount
																													 （3）如果pUpdateInfo->pNext中包含一个VkVideoEncodeH264SessionParametersAddInfoKHR，则当前videoSessionParameters 中不能包含一个seq_parameter_set_id 以及pic_parameter_set_id 都匹配VkVideoEncodeH264SessionParametersAddInfoKHR::pStdPPSs 中任何元素的 StdVideoH264PictureParameterSet实体
																													 （4）当前videoSessionParameters 中存储的 StdVideoH264PictureParameterSet实体的数量加上pUpdateInfo->pNext中的VkVideoEncodeH264SessionParametersAddInfoKHR::stdPPSCount 必须小于等于创建videoSessionParameters 的 VkVideoEncodeH264SessionParametersCreateInfoKHR::maxStdPPSCount
			6.如果videoSessionParameters 以video codec operation VK_VIDEO_CODEC_OPERATION_ENCODE_H265_BIT_KHR创建，则（1）如果pUpdateInfo->pNext中包含一个VkVideoEncodeH265SessionParametersAddInfoKHR，则当前videoSessionParameters 中不能包含一个vps_video_parameter_set_id 匹配VkVideoDecodeH265SessionParametersAddInfoKHR::pStdVPSs 中任何元素的 StdVideoH265VideoParameterSet实体
																													 （2）当前videoSessionParameters 中存储的 StdVideoH265VideoParameterSet实体的数量加上pUpdateInfo->pNext中的VkVideoEncodeH265SessionParametersAddInfoKHR::stdVPSCount 必须小于等于创建videoSessionParameters 的 VkVideoEncodeH265SessionParametersCreateInfoKHR::maxStdVPSCount
																													 （3）如果pUpdateInfo->pNext中包含一个VkVideoEncodeH265SessionParametersAddInfoKHR，则当前videoSessionParameters 中不能包含一个sps_video_parameter_set_id 和 sps_seq_parameter_set_id 都匹配VkVideoEncodeH265SessionParametersAddInfoKHR::pStdSPSs 中任何元素的 StdVideoH265SequenceParameterSet实体
																													 （4）当前videoSessionParameters 中存储的 StdVideoH265SequenceParameterSet实体的数量加上pUpdateInfo->pNext中的VkVideoEncodeH265SessionParametersAddInfoKHR::stdSPSCount 必须小于等于创建videoSessionParameters 的 VkVideoEncodeH265SessionParametersCreateInfoKHR::maxStdSPSCount
																													 （5）如果pUpdateInfo->pNext中包含一个VkVideoEncodeH265SessionParametersAddInfoKHR，则当前videoSessionParameters 中不能包含一个sps_video_parameter_set_id, pps_seq_parameter_set_id, 以及 pps_pic_parameter_set_id 全都匹配VkVideoEncodeH265SessionParametersAddInfoKHR::pStdPPSs 中任何元素的 StdVideoH265PictureParameterSet实体
																													 （6）当前videoSessionParameters 中存储的 StdVideoH265PictureParameterSet实体的数量加上pUpdateInfo->pNext中的VkVideoEncodeH265SessionParametersAddInfoKHR::stdPPSCount 必须小于等于创建videoSessionParameters 的 VkVideoEncodeH265SessionParametersCreateInfoKHR::maxStdPPSCount
																													 （7）如果pUpdateInfo->pNext中包含一个VkVideoEncodeH265SessionParametersAddInfoKHR，对每个VkVideoEncodeH265SessionParametersAddInfoKHR::pStdPPSs中的元素，则其num_tile_columns_minus1 必须小于调用 vkGetPhysicalDeviceVideoCapabilitiesKHR 传入videoSessionParameters 创建时的video profile 返回 VkVideoEncodeH265CapabilitiesKHR::maxTiles.width
																													 （8）如果pUpdateInfo->pNext中包含一个VkVideoEncodeH265SessionParametersAddInfoKHR，对每个VkVideoEncodeH265SessionParametersAddInfoKHR::pStdPPSs中的元素，则其num_tile_rows_minus1 必须小于调用 vkGetPhysicalDeviceVideoCapabilitiesKHR 传入videoSessionParameters 创建时的video profile 返回 VkVideoEncodeH265CapabilitiesKHR::maxTiles.height

			*/



		}
	}

	VkCommandBuffer commandBuffer{/*假设这是一个有效的VkCommandBuffer*/};


	//Video Coding Scope  参见p3459
	{
		/*
		应用只能将video coding commands 记录到video coding scope 中
		*/



		struct VideoBeginCodingInfoKHREXT {
			VkVideoEncodeH264GopRemainingFrameInfoKHR videoEncodeH264GopRemainingFrameInfoKHR{};
			VkVideoEncodeH264RateControlInfoKHR  videoEncodeH264RateControlInfoKHR{};
			VkVideoEncodeH265GopRemainingFrameInfoKHR videoEncodeH265GopRemainingFrameInfoKHR{};
			VkVideoEncodeH265RateControlInfoKHR videoEncodeH265RateControlInfoKHR{};
			VkVideoEncodeRateControlInfoKHR videoEncodeRateControlInfoKHR{};
			VideoBeginCodingInfoKHREXT() {
				Init();

			}
			void Init() {
				videoEncodeH264GopRemainingFrameInfoKHR.sType = VK_STRUCTURE_TYPE_MAX_ENUM;//没有定义所以定义为非法值
				videoEncodeH264GopRemainingFrameInfoKHR.pNext = nullptr;
				videoEncodeH264RateControlInfoKHR.sType = VK_STRUCTURE_TYPE_MAX_ENUM;//没有定义所以定义为非法值
				videoEncodeH264RateControlInfoKHR.pNext = nullptr;
				videoEncodeH265GopRemainingFrameInfoKHR.sType = VK_STRUCTURE_TYPE_MAX_ENUM;//没有定义所以定义为非法值
				videoEncodeH265GopRemainingFrameInfoKHR.pNext = nullptr;
				videoEncodeH265RateControlInfoKHR.sType = VK_STRUCTURE_TYPE_MAX_ENUM;//没有定义所以定义为非法值
				videoEncodeH265RateControlInfoKHR.pNext = nullptr;
				videoEncodeRateControlInfoKHR.sType = VK_STRUCTURE_TYPE_MAX_ENUM;//没有定义所以定义为非法值
				videoEncodeRateControlInfoKHR.pNext = nullptr;
			}
		};


		//开始一个 Video Coding Scope  参见p3459
		VkVideoBeginCodingInfoKHR videoBeginCodingInfoKHR{};
		videoBeginCodingInfoKHR.sType = VK_STRUCTURE_TYPE_VIDEO_BEGIN_CODING_INFO_KHR;
		VideoBeginCodingInfoKHREXT videoBeginCodingInfoKHREXT{};
		videoBeginCodingInfoKHR.pNext = &videoBeginCodingInfoKHREXT.videoEncodeH264GopRemainingFrameInfoKHR;//可以包含VkVideoEncodeRateControlInfoKHR 来指明期望的编码速率但不改变当前配置的编码速率
		videoBeginCodingInfoKHR.flags = 0;//保留未来使用
		videoBeginCodingInfoKHR.videoSession = VkVideoSessionKHR{/*假设这是一个有效的VkVideoSessionKHR*/ };//指定绑定的用于处理video commands的 video session
		videoBeginCodingInfoKHR.videoSessionParameters = VkVideoSessionParametersKHR{/*假设这是一个有效的VkVideoSessionParametersKHR*/ };//为VK_NULL_HANDLE或者 VkVideoSessionParametersKHR句柄，指明绑定的用于处理video commands的 VkVideoSessionParametersKHR，如果为VK_NULL_HANDLE，则说明不绑定任何 video session parameters
		videoBeginCodingInfoKHR.referenceSlotCount = 1;// pReferenceSlots 中元素个数
		VkVideoReferenceSlotInfoKHR videoReferenceSlotInfoKHR{};
		{

			struct VideoReferenceSlotInfoKHREXT
			{
				VkVideoDecodeAV1DpbSlotInfoKHR videoDecodeAV1DpbSlotInfoKHR{};
				VkVideoDecodeH264DpbSlotInfoKHR videoDecodeH264DpbSlotInfoKHR{};
				VkVideoDecodeH265DpbSlotInfoKHR videoDecodeH265DpbSlotInfoKHR{};
				VkVideoEncodeH264DpbSlotInfoKHR videoEncodeH264DpbSlotInfoKHR{};
				VkVideoEncodeH265DpbSlotInfoKHR videoEncodeH265DpbSlotInfoKHR{};
				VideoReferenceSlotInfoKHREXT() {
					Init();
				}
				void Init() {
					videoDecodeAV1DpbSlotInfoKHR.sType = VK_STRUCTURE_TYPE_MAX_ENUM;//没有定义所以这里定义为非法值
					videoDecodeAV1DpbSlotInfoKHR.pNext = nullptr;
					videoDecodeH264DpbSlotInfoKHR.sType = VK_STRUCTURE_TYPE_VIDEO_DECODE_H264_DPB_SLOT_INFO_KHR;
					videoDecodeH264DpbSlotInfoKHR.pNext = nullptr;
					videoDecodeH265DpbSlotInfoKHR.sType = VK_STRUCTURE_TYPE_VIDEO_DECODE_H265_DPB_SLOT_INFO_KHR;
					videoDecodeH265DpbSlotInfoKHR.pNext = nullptr;
					videoEncodeH264DpbSlotInfoKHR.sType = VK_STRUCTURE_TYPE_MAX_ENUM;
					videoEncodeH264DpbSlotInfoKHR.pNext = nullptr;
					videoEncodeH265DpbSlotInfoKHR.sType = VK_STRUCTURE_TYPE_MAX_ENUM;
					videoEncodeH265DpbSlotInfoKHR.pNext = nullptr;

				}
			};

			videoReferenceSlotInfoKHR.sType = VK_STRUCTURE_TYPE_VIDEO_REFERENCE_SLOT_INFO_KHR;
			videoReferenceSlotInfoKHR.pNext = nullptr;
			videoReferenceSlotInfoKHR.slotIndex = 0;//为 DPB slot的索引或者一个负数
			VkVideoPictureResourceInfoKHR videoPictureResourceInfoKHR{};
			{
				videoPictureResourceInfoKHR.sType = VK_STRUCTURE_TYPE_VIDEO_PICTURE_RESOURCE_INFO_KHR;
				videoPictureResourceInfoKHR.pNext = nullptr;
				videoPictureResourceInfoKHR.imageViewBinding = VkImageView{/*假设这是一个有效的VkImageView*/ };
				videoPictureResourceInfoKHR.baseArrayLayer = 0;
				videoPictureResourceInfoKHR.codedExtent = VkExtent2D{ .width = 1,.height = 1 }/*假设这是一个有效的VkExtent2D*/;
				videoPictureResourceInfoKHR.codedOffset = VkOffset2D{ .x = 0,.y = 0 }/*假设这是一个有效的VkOffset2D*/;
			}
			videoReferenceSlotInfoKHR.pPictureResource = &videoPictureResourceInfoKHR;//为NULL或者 VkVideoPictureResourceInfoKHR 指针，描述关联到slotIndex的 video picture resource
		}
		videoBeginCodingInfoKHR.pReferenceSlots = &videoReferenceSlotInfoKHR;//一组 VkVideoReferenceSlotInfoKHR 数组指针，指明用于确定 bound reference picture resources的信息以及其关联的初始的 DPB slot 索引
		/*
		VkVideoBeginCodingInfoKHR有效用法:
		1.videoSession 的所有memory bindings（通过vkGetVideoSessionMemoryRequirementsKHR 返回的）都必须绑定内存对象
		2.每个pReferenceSlots 中指明的非负VkVideoReferenceSlotInfoKHR::slotIndex 必须小于创建videoSession的 VkVideoSessionCreateInfoKHR::maxDpbSlots 指定的最大DPB槽数
		3.每个pReferenceSlots 中指明的非NULL VkVideoReferenceSlotInfoKHR::pPictureResource 必须在pReferenceSlots 中是唯一的
		4.如果pReferenceSlots 中任何元素的pPictureResource 不为NULL，则（1）其pPictureResource->imageViewBinding 所指的VkImageView 必须兼容videoSession 创建时候的video profile
		（2）其pPictureResource->imageViewBinding 所指的VkImageView 必须匹配videoSession 创建时候的VkVideoSessionCreateInfoKHR::referencePictureFormat
		（3）该元素的codedOffset 必须为codedOffsetGranularity（见p3464）的整数倍
		（4）该元素的codedExtent 必须在videoSession创建时候的VkVideoSessionCreateInfoKHR::minCodedExtent 和 VkVideoSessionCreateInfoKHR::maxCodedExtent 之间
		5.如果VkVideoCapabilitiesKHR::flags 不包含VK_VIDEO_CAPABILITY_SEPARATE_REFERENCE_IMAGES_BIT_KHR（调用vkGetPhysicalDeviceVideoCapabilitiesKHR传入videoSession创建时的video profile返回的），则所有pReferenceSlots元素中的pPictureResource->imageViewBinding 不为VK_NULL_HANDLE的必须从同一个VkImage上创建
		6.如果videoSession 以一个decode operation 且任何pReferenceSlots中元素的slotIndex 成员不是负数，则其pPictureResource->imageViewBinding 所指的VkImageView必须以VK_IMAGE_USAGE_VIDEO_DECODE_DPB_BIT_KHR 创建
		7.如果videoSession 以一个encode operation 且任何pReferenceSlots中元素的slotIndex 成员不是负数，则其pPictureResource->imageViewBinding 所指的VkImageView必须以VK_IMAGE_USAGE_VIDEO_ENCODE_DPB_BIT_KHR 创建
		8.如果videoSession 以一个video codec operation VK_VIDEO_CODEC_OPERATION_DECODE_H264_BIT_KHR , VK_VIDEO_CODEC_OPERATION_DECODE_H265_BIT_KHR ,VK_VIDEO_CODEC_OPERATION_DECODE_AV1_BIT_KHR ,VK_VIDEO_CODEC_OPERATION_ENCODE_H264_BIT_KHR  或者 VK_VIDEO_CODEC_OPERATION_ENCODE_H265_BIT_KHR 创建，则videoSessionParameters 不能为VK_NULL_HANDLE
		9.如果videoSessionParameters 不为VK_NULL_HANDLE，则必须是在创建时指定其VkVideoSessionParametersCreateInfoKHR::videoSession 为 pBeginInfo->videoSession创建

		*/


		//该命令调用后的一些规则详情见p3459
		vkCmdBeginVideoCodingKHR(commandBuffer, &videoBeginCodingInfoKHR);
		/*
		vkCmdBeginVideoCodingKHR有效用法:
		1.commandBuffer所在的VkCommandPool的队列组必须支持pBeginInfo->videoSession 创建时的video codec operation，见vkGetPhysicalDeviceQueueFamilyProperties2 返回的VkQueueFamilyVideoPropertiesKHR::videoCodecOperations
		2.该命令调用是不能由激活的queries
		3.如果commandBuffer是unprotected command buffer，且protectedNoFault不支持，则pBeginInfo->videoSession 不能以VK_VIDEO_SESSION_CREATE_PROTECTED_CONTENT_BIT_KHR 创建
		4.如果commandBuffer是protected command buffer，且protectedNoFault不支持，则pBeginInfo->videoSession 必须以VK_VIDEO_SESSION_CREATE_PROTECTED_CONTENT_BIT_KHR 创建
		5.如果commandBuffer是unprotected command buffer，且protectedNoFault支持，且pBeginInfo->pReferenceSlots 中的任何元素的pPictureResource 不为NULL，则该元素的pPictureResource->imageViewBinding 不能指定一个从protected image 上创建的VkImageView
		6.如果commandBuffer是protected command buffer，且protectedNoFault支持，且pBeginInfo->pReferenceSlots 中的任何元素的pPictureResource 不为NULL，则该元素的pPictureResource->imageViewBinding 必须指定一个从protected image 上创建的VkImageView
		7.如果任何pBeginInfo->pReferenceSlots中的元素的slotIndex 成员不是负数，则其必须指定在该命令在设备上执行期时处于激活状态的DPB slot 的索引
		8.pBeginInfo->pReferenceSlots中每个non-NULL pPictureResource指定的video picture resource，且其对应的slotIndex 不是负数，则该video picture resource 必须匹配在该命令在设备上执行期时关联到pBeginInfo->videoSession的DPB slot的video picture resource
		9.如果pBeginInfo->videoSession 以一个video encode operation 创建，且pBeginInfo->pNext 不包含一个VkVideoEncodeRateControlInfoKHR，则在该命令在设备上执行期时pBeginInfo->videoSession配置的 rate control mode 必须为VK_VIDEO_ENCODE_RATE_CONTROL_MODE_DEFAULT_KHR
		10.如果pBeginInfo->videoSession 以一个video encode operation 创建，且pBeginInfo->pNext 包含一个VkVideoEncodeRateControlInfoKHR，则其该结构体参数必须匹配在该命令在设备上执行期时pBeginInfo->videoSession配置的 rate control mode
		11.如果pBeginInfo->videoSession 以一个 video codec operation 为VK_VIDEO_CODEC_OPERATION_ENCODE_H264_BIT_KHR创建，且当前的rate control mode不为VK_VIDEO_ENCODE_RATE_CONTROL_MODE_DEFAULT_KHR 或者 VK_VIDEO_ENCODE_RATE_CONTROL_MODE_DISABLED_BIT_KHR，且调用vkGetPhysicalDeviceVideoCapabilitiesKHR传入pBeginInfo->videoSession创建时的 video profile 返回的VkVideoEncodeH264CapabilitiesKHR::requiresGopRemainingFrames 为VK_TRUE，则pBeginInfo->pNext中必须包含一个useGopRemainingFrames 为VK_TRUE的VkVideoEncodeH264GopRemainingFrameInfoKHR结构体
		12.如果pBeginInfo->videoSession 以一个 video codec operation 为VK_VIDEO_CODEC_OPERATION_ENCODE_H265_BIT_KHR创建，且当前的rate control mode不为VK_VIDEO_ENCODE_RATE_CONTROL_MODE_DEFAULT_KHR 或者 VK_VIDEO_ENCODE_RATE_CONTROL_MODE_DISABLED_BIT_KHR，且调用vkGetPhysicalDeviceVideoCapabilitiesKHR传入pBeginInfo->videoSession创建时的 video profile 返回的VkVideoEncodeH265CapabilitiesKHR::requiresGopRemainingFrames 为VK_TRUE，则pBeginInfo->pNext中必须包含一个useGopRemainingFrames 为VK_TRUE的VkVideoEncodeH265GopRemainingFrameInfoKHR结构体
		*/




		//结束一个 Video Coding Scope  参见p3467
		VkVideoEndCodingInfoKHR videoEndCodingInfoKHR{};
		videoEndCodingInfoKHR.sType = VK_STRUCTURE_TYPE_VIDEO_END_CODING_INFO_KHR;
		videoEndCodingInfoKHR.pNext = nullptr;
		videoEndCodingInfoKHR.flags = 0;//保留未来使用

		//该命令会导致之前vkCmdBeginVideoCodingKHR开始的scope中 绑定的所有reference picture resources解绑
		vkCmdEndVideoCodingKHR(commandBuffer, &videoEndCodingInfoKHR);//当前不能有激活的queries
	}

	//Video Coding Control  参见p3469
	{
		struct VideoCodingControlInfoKHREXT
		{
			VkVideoEncodeH264RateControlInfoKHR videoEncodeH264RateControlInfoKHR{};
			VkVideoEncodeH265RateControlInfoKHR videoEncodeH265RateControlInfoKHR{};
			VkVideoEncodeQualityLevelInfoKHR videoEncodeQualityLevelInfoKHR{};
			VkVideoEncodeRateControlInfoKHR videoEncodeRateControlInfoKHR{};
			VideoCodingControlInfoKHREXT() {
				Init();
			}
			void Init() {
				videoEncodeH264RateControlInfoKHR.sType = VK_STRUCTURE_TYPE_MAX_ENUM;//未定义所以这里定义为非法值
				videoEncodeH264RateControlInfoKHR.pNext = nullptr;
				videoEncodeH265RateControlInfoKHR.sType = VK_STRUCTURE_TYPE_MAX_ENUM;//未定义所以这里定义为非法值
				videoEncodeH265RateControlInfoKHR.pNext = nullptr;
				videoEncodeQualityLevelInfoKHR.sType = VK_STRUCTURE_TYPE_MAX_ENUM;//未定义所以这里定义为非法值
				videoEncodeQualityLevelInfoKHR.pNext = nullptr;
				videoEncodeRateControlInfoKHR.sType = VK_STRUCTURE_TYPE_MAX_ENUM;//未定义所以这里定义为非法值
				videoEncodeRateControlInfoKHR.pNext = nullptr;
			}
		};

		//动态控制当前绑定的 video session ，具体如何控制见p3470, 简单将就是根据flags中的值以及pNext中的值将绑定的video session重置或者改变某些控制参数
		VkVideoCodingControlInfoKHR videoCodingControlInfoKHR{};
		videoCodingControlInfoKHR.sType = VK_STRUCTURE_TYPE_VIDEO_CODING_CONTROL_INFO_KHR;
		VideoCodingControlInfoKHREXT videoCodingControlInfoKHREXT{};
		videoCodingControlInfoKHR.pNext = &videoCodingControlInfoKHREXT.videoEncodeH264RateControlInfoKHR;
		videoCodingControlInfoKHR.flags = VK_VIDEO_CODING_CONTROL_RESET_BIT_KHR;/*为 VkVideoCodingControlFlagsKHR 组合值位掩码指明控制标志
		VkVideoCodingControlFlagsKHR:
		VK_VIDEO_CODING_CONTROL_RESET_BIT_KHR : 指明请求在应用其他coding控制参数之前重置绑定的video session
		VK_VIDEO_CODING_CONTROL_ENCODE_RATE_CONTROL_BIT_KHR : 指明coding控制参数包含video encode rate control参数（见VkVideoEncodeRateControlInfoKHR）
		VK_VIDEO_CODING_CONTROL_ENCODE_QUALITY_LEVEL_BIT_KHR : 指明coding控制参数包含video encode quality level参数（见VkVideoEncodeQualityLevelInfoKHR）
		*/
		
		
		/*
		VkVideoCodingControlInfoKHR有效用法:
		1.如果flags 包含VK_VIDEO_CODING_CONTROL_ENCODE_RATE_CONTROL_BIT_KHR，则pNext中必须包含一个VkVideoEncodeRateControlInfoKHR
		2.如果flags 包含VK_VIDEO_CODING_CONTROL_ENCODE_QUALITY_LEVEL_BIT_KHR，则pNext中必须包含一个VkVideoEncodeQualityLevelInfoKHR
		*/
		

		//开始 Video Coding Scope

		vkCmdControlVideoCodingKHR(commandBuffer, &videoCodingControlInfoKHR);
		/*
		vkCmdControlVideoCodingKHR有效用法:
		1.如果pCodingControlInfo->flags 中不包含VK_VIDEO_CODING_CONTROL_RESET_BIT_KHR，则绑定的video session 在该命令在设备上执行的时候不能为非初始化的状态
		2.如果绑定的video session 不以一个encode operation 创建，则pCodingControlInfo->flags 不能包含VK_VIDEO_CODING_CONTROL_ENCODE_RATE_CONTROL_BIT_KHR 或者 VK_VIDEO_CODING_CONTROL_ENCODE_QUALITY_LEVEL_BIT_KHR
		
		*/


		//结束 Video Coding Scope

	}


	//Inline Queries  参见p3473
	{
		/*
		如果video session 以VK_VIDEO_SESSION_CREATE_INLINE_QUERIES_BIT_KHR 创建，则在video coding scope 中使用 vkCmdBeginQuery 开始query是不允许的，
		要查询需要在video coding commands的参数（ vkCmdDecodeVideoKHR的 pDecodeInfo 或者  vkCmdEncodeVideoKHR的 pEncodeInfo）的pNext中包含一个queryPool为一个有效的VkQueryPool的 VkVideoInlineQueryInfoKHR
		
		*/

		//VkVideoInlineQueryInfoKHR
		VkVideoInlineQueryInfoKHR videoInlineQueryInfoKHR{};
		videoInlineQueryInfoKHR.sType = VK_STRUCTURE_TYPE_MAX_ENUM;//未定义所以这里定义为非法值
		videoInlineQueryInfoKHR.pNext = nullptr;
		videoInlineQueryInfoKHR.queryPool = VkQueryPool{/*假设这是一个有效的VkQueryPool*/ };//为VK_NULL_HANDLE 或者一个有效的管理query结果的 VkQueryPool
		videoInlineQueryInfoKHR.firstQuery = 0;//为存放第一个 video coding operation 查询结果的queryPool中的query的索引，后续的查询结果会顺序存放在后续的query索引中
		videoInlineQueryInfoKHR.queryCount = 1;//为执行的query的次数
		/*
		VkVideoInlineQueryInfoKHR有效用法:
		1.如果queryPool 不为VK_NULL_HANDLE，则（1）firstQuery 必须小于queryPool中的queries数量
											  （2）firstQuery + queryCount 必须小于等于queryPool中的queries数量

		*/


	}

}



NS_TEST_END