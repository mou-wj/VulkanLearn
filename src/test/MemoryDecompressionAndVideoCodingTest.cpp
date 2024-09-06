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
			videoCapabilitiesKHR.pictureAccessGranularity = VkExtent2D{.width = 1,.height = 1};//将image作为video picture resources访问时的最小访问粒度
			videoCapabilitiesKHR.minCodedExtent = VkExtent2D{ .width = 1,.height = 1 };//编码帧（frame）的最小width以及height
			videoCapabilitiesKHR.maxCodedExtent = VkExtent2D{ .width = 1,.height = 1 };//编码帧（frame）的最大width以及height
			videoCapabilitiesKHR.maxDpbSlots = 2;//一个video session中支持的最多的DPB slots的数量
			videoCapabilitiesKHR.maxActiveReferencePictures = 2;//一个 video coding 操作可以使用的active reference pictures的最大数量
			videoCapabilitiesKHR.stdHeaderVersion = VkExtensionProperties{.extensionName = "header",.specVersion = 1};// 为一个VkExtensionProperties，记录标准视频头名字以及video profile支持的版本
		
		}


		// Video Format Capabilities  参见p3419
		{
			//列举指定 video profile支持的output, input 以及 DPB image 的formats 和对应的容量
			VkPhysicalDeviceVideoFormatInfoKHR physicalDeviceVideoFormatInfoKHR{};
			physicalDeviceVideoFormatInfoKHR.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VIDEO_FORMAT_INFO_KHR;
			physicalDeviceVideoFormatInfoKHR.pNext = nullptr;//可以包含 VkVideoProfileListInfoKHR
			physicalDeviceVideoFormatInfoKHR.imageUsage = VK_IMAGE_USAGE_VIDEO_DECODE_DPB_BIT_KHR;

			uint32_t videoFormatPropertyCount = 0;
			std::vector<VkVideoFormatPropertiesKHR> videoFormatPropertiesKHRs{};
			VkResult result/*返回结果信息，如果不支持 VkVideoProfileListInfoKHR::pProfiles中的任何一个则返回之前描述的错误信息，如果不支持VkPhysicalDeviceVideoFormatInfoKHR::imageUsage则返回VK_ERROR_IMAGE_USAGE_NOT_SUPPORTED_KHR*/ 
					= vkGetPhysicalDeviceVideoFormatPropertiesKHR(physicalDevice, &physicalDeviceVideoFormatInfoKHR, &videoFormatPropertyCount, nullptr);
			videoFormatPropertiesKHRs.resize(videoFormatPropertyCount);
			VkResult result/*返回结果信息，如果不支持 VkVideoProfileListInfoKHR::pProfiles中的任何一个则返回之前描述的错误信息，如果不支持VkPhysicalDeviceVideoFormatInfoKHR::imageUsage则返回VK_ERROR_IMAGE_USAGE_NOT_SUPPORTED_KHR*/
					= vkGetPhysicalDeviceVideoFormatPropertiesKHR(physicalDevice, &physicalDeviceVideoFormatInfoKHR, &videoFormatPropertyCount, videoFormatPropertiesKHRs.data());
		}
	}

}



NS_TEST_END