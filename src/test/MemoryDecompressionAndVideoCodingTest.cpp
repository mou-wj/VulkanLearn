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


	//Video Decode Operations  参见p3474
	{
		/*
		video decode operations 消耗来自video bitstream buffer 以及一个或多个 reference pictures中压缩的数据，然后产生一个 decode output picture 以及可选的一个reconstructed  picture
		
		video decode operations 中对资源的同步在VK_PIPELINE_STAGE_2_VIDEO_DECODE_BIT_KHR stage，其中用于该操作输入的资源以 VK_ACCESS_2_VIDEO_DECODE_READ_BIT_KHR 访问，输出以VK_ACCESS_2_VIDEO_DECODE_WRITE_BIT_KHR 访问。用于在操作中的image的layout在除了该image只用于作为一个decode output picture 为VK_IMAGE_LAYOUT_VIDEO_DECODE_DST_KHR，其他情况下为VK_IMAGE_LAYOUT_VIDEO_DECODE_DPB_KHR
		*/


		// Codec-Specific Semantics 参见p3475  简单描述就是video decode operations的一些步骤或者行为是 codec-specific，即对应不用的codec操作类型，这些步骤和行为可能有所不用

		// Video Decode Operation Steps  参见p3475  简单描述video decode operations的一些步骤为： 读取压缩的数据 -> 执行重建操作 -> 写出解码数据


		//Capabilities 参见p3476
		{

			//VkVideoDecodeCapabilitiesKHR 可以包含在调用 vkGetPhysicalDeviceVideoCapabilitiesKHR传入的 VkVideoCapabilitiesKHR.pNext中用于返回视频解码能力的信息
			//VkVideoCapabilitiesKHR.pNext
			VkVideoDecodeCapabilitiesKHR videoDecodeCapabilitiesKHR{};
			videoDecodeCapabilitiesKHR.sType = VK_STRUCTURE_TYPE_VIDEO_DECODE_CAPABILITIES_KHR;
			videoDecodeCapabilitiesKHR.pNext = nullptr;
			videoDecodeCapabilitiesKHR.flags = VK_VIDEO_DECODE_CAPABILITY_DPB_AND_OUTPUT_COINCIDE_BIT_KHR;/*为 VkVideoDecodeCapabilityFlagBitsKHR 组合值位掩码指明支持的视频解码能力
			VkVideoDecodeCapabilityFlagBitsKHR:
			VK_VIDEO_DECODE_CAPABILITY_DPB_AND_OUTPUT_COINCIDE_BIT_KHR : 指明在一个video decode operation中支持使用相同的video picture 作为reconstructed picture 和decode output picture
			VK_VIDEO_DECODE_CAPABILITY_DPB_AND_OUTPUT_DISTINCT_BIT_KHR : 指明在一个video decode operation中支持使用不同的video picture 作为reconstructed picture 和decode output picture
			*/


		}


		//Video Decode Commands 参见p3477
		{
			VkCommandBuffer commandBuffer{/*假设这是一个有效的VkCommandBuffer*/ };

			struct VideoDecodeInfoKHREXT {
				VkVideoDecodeAV1PictureInfoKHR videoDecodeAV1PictureInfoKHR{};
				VkVideoDecodeH264PictureInfoKHR videoDecodeH264PictureInfoKHR{};
				VkVideoDecodeH265PictureInfoKHR videoDecodeH265PictureInfoKHR{};
				VkVideoInlineQueryInfoKHR videoInlineQueryInfoKHR{};
				VideoDecodeInfoKHREXT() {
					Init();
				}
				void Init() {
					videoDecodeAV1PictureInfoKHR.sType = VK_STRUCTURE_TYPE_MAX_ENUM;//未定义所以这里定义为非法值
					videoDecodeAV1PictureInfoKHR.pNext = nullptr;
					videoDecodeH264PictureInfoKHR.sType = VK_STRUCTURE_TYPE_VIDEO_DECODE_H264_PICTURE_INFO_KHR;
					videoDecodeH264PictureInfoKHR.pNext = nullptr;
					videoDecodeH265PictureInfoKHR.sType = VK_STRUCTURE_TYPE_VIDEO_DECODE_H265_PICTURE_INFO_KHR;
					videoDecodeH265PictureInfoKHR.pNext = nullptr;
					videoInlineQueryInfoKHR.sType = VK_STRUCTURE_TYPE_MAX_ENUM;//未定义所以这里定义为非法值
					videoInlineQueryInfoKHR.pNext = nullptr;;
				}


			};



			//启动opCount个 video decode operations
			VkVideoDecodeInfoKHR videoDecodeInfoKHR{};
			videoDecodeInfoKHR.sType = VK_STRUCTURE_TYPE_VIDEO_DECODE_INFO_KHR;
			VideoDecodeInfoKHREXT videoDecodeInfoKHREXT{};
			videoDecodeInfoKHR.pNext = &videoDecodeInfoKHREXT.videoDecodeAV1PictureInfoKHR;
			videoDecodeInfoKHR.flags = 0;//保留未来使用
			videoDecodeInfoKHR.srcBuffer = VkBuffer{/*假设这是一个有效的VkBuffer*/};//为读取 encoded bitstream的 source video bitstream buffer
			videoDecodeInfoKHR.srcBufferOffset = 0;//srcBuffer 中的起始字节偏移量
			videoDecodeInfoKHR.srcBufferRange = 4;//srcBuffer 中从srcBufferOffset开始的字节数
			VkVideoPictureResourceInfoKHR dstPictureResource{};
			{
				dstPictureResource.sType = VK_STRUCTURE_TYPE_VIDEO_PICTURE_RESOURCE_INFO_KHR;
				dstPictureResource.pNext = nullptr;
				dstPictureResource.baseArrayLayer = 0;
				dstPictureResource.codedExtent = VkExtent2D{ .width = 1,.height = 1 };
				dstPictureResource.codedOffset = VkOffset2D{ .x = 0,.y = 0 };
				dstPictureResource.imageViewBinding = VkImageView{/*假设这是一个有效的VkImageView*/ };
			}
			videoDecodeInfoKHR.dstPictureResource = dstPictureResource;//指明用于Decode Output Picture的video picture resource
			VkVideoReferenceSlotInfoKHR videoReferenceSlotInfoKHR{};
			{
				videoReferenceSlotInfoKHR.sType = VK_STRUCTURE_TYPE_VIDEO_REFERENCE_SLOT_INFO_KHR;
				videoReferenceSlotInfoKHR.pNext = nullptr;
				videoReferenceSlotInfoKHR.slotIndex = 0;
				VkVideoPictureResourceInfoKHR testPictureResource{/*假设这是一个有效的VkVideoPictureResourceInfoKHR*/ };
				videoReferenceSlotInfoKHR.pPictureResource = &testPictureResource;

			}
			videoDecodeInfoKHR.pSetupReferenceSlot = &videoReferenceSlotInfoKHR;//为NULL或者VkVideoReferenceSlotInfoKHR 指针， 指明可选的Reconstructed Picture 信息
			videoDecodeInfoKHR.referenceSlotCount = 1;// pReferenceSlots 中元素个数
			videoDecodeInfoKHR.pReferenceSlots = &videoReferenceSlotInfoKHR;//为NULL或者VkVideoReferenceSlotInfoKHR 数组指针，描述用于video decode operation 的DPB slots 以及对应的 reference picture （激活的Reference Picture 组）
			/*
			VkVideoDecodeInfoKHR有效用法:
			1.srcBuffer 必须以VK_BUFFER_USAGE_VIDEO_DECODE_SRC_BIT_KHR 标记创建
			2.srcBufferOffset 必须小于srcBuffer的大小
			3.srcBufferRange 必须小于等于srcBuffer的大小 减去srcBufferOffset
			4.如果pSetupReferenceSlot 不为NULL，则其slotIndex 不能为负数，其pPictureResource 不能为NULL
			5.pReferenceSlots 中每个元素的slotIndex 不能为负数，pPictureResource 不能为NULL

			*/


			//该接口的其他注意信息以及使用时一些参数的限制信息见 *** p3478 - p3480
			vkCmdDecodeVideoKHR(commandBuffer, &videoDecodeInfoKHR);
			/*
			vkCmdDecodeVideoKHR有效用法:
			1.绑定的video session 必须以一个 decode operation 创建，且在该命令在设备上执行的时候video session 不能为非初始化的状态
			2.对每个激活的query，对应query type的激活的query 索引加上 opCount 必须小于等于该query type的最后一个激活的query 索引加1
			3.如果绑定的video session 以VK_VIDEO_SESSION_CREATE_INLINE_QUERIES_BIT_KHR 创建，且pDecodeInfo->pNext中包含一个queryPool 指定一个有效的VkQueryPool的VkVideoInlineQueryInfoKHR，则（1）VkVideoInlineQueryInfoKHR::queryCount 必须等于opCount
																																															 （2）所有该命令使用的VkVideoInlineQueryInfoKHR中的query必须为unavailable的状态
																																															 （3）则用于创建VkVideoInlineQueryInfoKHR.queryPool的 queryType 必须为VK_QUERY_TYPE_RESULT_STATUS_ONLY_KHR
																																															 （4）VkVideoInlineQueryInfoKHR.queryPool 必须要以VkQueryPoolCreateInfo.pNext中包含一个和video session创建时VkVideoSessionCreateInfoKHR::pVideoProfile 中一个元素相等的VkVideoProfileInfoKHR 创建
																																															 （5）如果用于创建VkVideoInlineQueryInfoKHR.queryPool的 queryType 必须为VK_QUERY_TYPE_RESULT_STATUS_ONLY_KHR，则commandBuffer所在的VkCommandPool的队列族必须支持result status queries，见队列族的VkQueueFamilyQueryResultStatusPropertiesKHR::queryResultStatusSupport
			4.pDecodeInfo->srcBuffer 必须兼容于绑定的video session 创建时使用的video profile
			5.如果commandBuffer是unprotected command buffer 且protectedNoFault不支持，则pDecodeInfo->srcBuffer 不能是protected buffer
			6.如果commandBuffer是protected command buffer 且protectedNoFault不支持，则pDecodeInfo->srcBuffer 必须是protected buffer
			7.pDecodeInfo->srcBufferOffset 必须是调用vkGetPhysicalDeviceVideoCapabilitiesKHR传入绑定video session创建时的video profile返回的VkVideoCapabilitiesKHR::minBitstreamBufferOffsetAlignment的整数倍
			8.pDecodeInfo->srcBufferRange 必须是调用vkGetPhysicalDeviceVideoCapabilitiesKHR传入绑定video session创建时的video profile返回的VkVideoCapabilitiesKHR::minBitstreamBufferSizeAlignment的整数倍
			9.如果pDecodeInfo->pSetupReferenceSlot 不为NULL，则调用vkGetPhysicalDeviceVideoCapabilitiesKHR传入绑定video session创建时的video profile返回VkVideoDecodeCapabilitiesKHR::flags 不包含VK_VIDEO_DECODE_CAPABILITY_DPB_AND_OUTPUT_COINCIDE_BIT_KHR，则pDecodeInfo->dstPictureResource 以及 pDecodeInfo->pSetupReferenceSlot->pPictureResource 指定的video picture resources 必须匹配
			10.如果pDecodeInfo->pSetupReferenceSlot 不为NULL，则调用vkGetPhysicalDeviceVideoCapabilitiesKHR传入绑定video session创建时的video profile返回VkVideoDecodeCapabilitiesKHR::flags 不包含VK_VIDEO_DECODE_CAPABILITY_DPB_AND_OUTPUT_COINCIDE_BIT_KHR，且绑定的video session不以video codec operation 创建或者VkVideoDecodeAV1ProfileInfoKHR::filmGrainSupport不为VK_TRUE，或者decoded picture的film grain 未开启，则pDecodeInfo->dstPictureResource 以及 pDecodeInfo->pSetupReferenceSlot->pPictureResource 指定的video picture resources 必须匹配
			11.pDecodeInfo->dstPictureResource.imageViewBinding 必须兼容绑定的video session创建时的video profile
			12.pDecodeInfo->dstPictureResource.imageViewBinding 的format必须匹配创建video session时使用的VkVideoSessionCreateInfoKHR::pictureFormat
			13.pDecodeInfo->dstPictureResource.codedOffset 必须是codedOffsetGranularity 的整数倍
			14.pDecodeInfo->dstPictureResource.codedExtent 必须在创建video session 时使用的VkVideoSessionCreateInfoKHR::minCodedExtent 和 VkVideoSessionCreateInfoKHR::maxCodedExtent 之间
			15.pDecodeInfo->dstPictureResource.imageViewBinding 必须以VK_IMAGE_USAGE_VIDEO_DECODE_DST_BIT_KHR 创建
			16.如果commandBuffer是unprotected command buffer 且protectedNoFault不支持，则pDecodeInfo->dstPictureResource.imageViewBinding 不能从protected image 上创建
			17.如果commandBuffer是protected command buffer 且protectedNoFault不支持，则pDecodeInfo->dstPictureResource.imageViewBinding 必须从protected image 上创建
			18.pDecodeInfo->pSetupReferenceSlot 必须不为NULL除非绑定的video session 被创建时指定了VkVideoSessionCreateInfoKHR::maxDpbSlots 为0
			19.如果 pDecodeInfo->pSetupReferenceSlot 不为NULL，则（1）pDecodeInfo->pSetupReferenceSlot->slotIndex 必须小于等于创建video session 时 VkVideoSessionCreateInfoKHR::maxDpbSlots 指定的最大DPB槽数量
																 （2）pDecodeInfo->pSetupReferenceSlot->pPictureResource->codedOffset 必须为codedOffsetGranularity 的整数倍
																 （3）pDecodeInfo->pSetupReferenceSlot->pPictureResource 必须匹配一个绑定的reference picture resource
			20.activeReferencePictureCount 必须小于等于创建video session 时指定的 VkVideoSessionCreateInfoKHR::maxActiveReferencePictures
			21.pDecodeInfo->pReferenceSlots 中每个元素的slotIndex 必须小于等于创建video session 时 VkVideoSessionCreateInfoKHR::maxDpbSlots 指定的最大DPB槽数量
			22.每个pDecodeInfo->pReferenceSlots 元素的pPictureResource 所指的VkVideoPictureResourceInfoKHR::codedOffset 必须为codedOffsetGranularity 的整数倍
			23.每个pDecodeInfo->pReferenceSlots 元素的pPictureResource 必须匹配一个绑定的关联到其slotIndex指定的DPB slot 索引上的reference picture resource
			24.每个pDecodeInfo->pReferenceSlots 元素的pPictureResource 所指的video picture resource 必须在pDecodeInfo->pReferenceSlots 中是唯一的
			25.dpbFrameUseCount，dpbFrameUseCount 以及dpbBottomFieldUseCount中所有元素必须小于等于1 （这三个量是隐含的，通过计算出来的，具体见p3478 - p3480）
			26.如果 pDecodeInfo->pSetupReferenceSlot 为NULL 或者pDecodeInfo->pSetupReferenceSlot->pPictureResource 没有引用到和pDecodeInfo->dstPictureResource 相同的image subresource，则pDecodeInfo->dstPictureResource 引用的image subresource 在该命令在设备上执行时layout必须为 VK_IMAGE_LAYOUT_VIDEO_DECODE_DST_KHR
			27.如果 pDecodeInfo->pSetupReferenceSlot 不为NULL 且pDecodeInfo->pSetupReferenceSlot->pPictureResource 引用到和pDecodeInfo->dstPictureResource 相同的image subresource，则pDecodeInfo->dstPictureResource 引用的image subresource 在该命令在设备上执行时layout必须为 VK_IMAGE_LAYOUT_VIDEO_DECODE_DPB_KHR
			28.如果pDecodeInfo->pSetupReferenceSlot 不为NULL，则pDecodeInfo->pSetupReferenceSlot->pPictureResource 所指的image subresource 在该命令在设备上执行时layout必须为 VK_IMAGE_LAYOUT_VIDEO_DECODE_DPB_KHR
			29.pDecodeInfo->pReferenceSlots 中每个元素的pPictureResource 引用的image subresource 在该命令在设备上执行时layout必须为 VK_IMAGE_LAYOUT_VIDEO_DECODE_DPB_KHR
			30.如果绑定的video session 以video codec operation 为 VK_VIDEO_CODEC_OPERATION_DECODE_H264_BIT_KHR 创建，则（1）pDecodeInfo->pNext中必须包含一个VkVideoDecodeH264PictureInfoKHR结构
																													   （2）如果video session不以支持interlaced frame 创建，则decode output picture 必须代表一个frame
																													   （3）则pDecodeInfo->pNext中的VkVideoDecodeH264PictureInfoKHR.pSliceOffsets 的所有元素 必须小于pDecodeInfo->srcBufferRange
																													   （4）绑定的video session parameters 必须包含seq_parameter_set_id 匹配pDecodeInfo->pNext中VkVideoDecodeH264PictureInfoKHR::pStdPictureInfo 中元素的StdVideoDecodeH264PictureInfo::seq_parameter_set_id的 StdVideoH264SequenceParameterSet 实体
																													   （5）绑定的video session parameters 必须包含seq_parameter_set_id 以及pic_parameter_set_id 匹配pDecodeInfo->pNext中VkVideoDecodeH264PictureInfoKHR::pStdPictureInfo 中元素的 StdVideoDecodeH264PictureInfo::seq_parameter_set_id 以及StdVideoDecodeH264PictureInfo::pic_parameter_set_id 的 StdVideoH264PictureParameterSet 实体
																													   （6）如果pDecodeInfo->pSetupReferenceSlot 不为NULL，则pDecodeInfo->pSetupReferenceSlot->pNext中必须包含一个VkVideoDecodeH264DpbSlotInfoKHR
																													   （7）如果video session不以支持interlaced frame 创建，且pDecodeInfo->pSetupReferenceSlot 不为NULL，则reconstructed picture 必须代表一个frame
																													   （8）则pDecodeInfo->pReferenceSlots中每个元素的pNext中必须包含一个VkVideoDecodeH264DpbSlotInfoKHR
																													   （9）如果video session不以支持interlaced frame 创建，则pDecodeInfo->pReferenceSlots 中每个激活的reference picture 必须代表一个frame
																													   （10）如果pDecodeInfo->pSetupReferenceSlot 不为NULL，且 decode output picture 表示一个frame，则reconstructed picture 也必须表示一个frame
																													   （11）如果pDecodeInfo->pSetupReferenceSlot 不为NULL，且 decode output picture 表示一个top field，则reconstructed picture 也必须表示一个top field
																													   （12）如果pDecodeInfo->pSetupReferenceSlot 不为NULL，且 decode output picture 表示一个bottom field，则reconstructed picture 也必须表示一个bottom field
																													   （13）如果pDecodeInfo->pReferenceSlots 中一个激活的reference picture 代表一个frame，则该元素的slotIndex指定的关联到frame picture的 DPB slot index 必须匹配在该命令在设备上执行时相同元素的pPictureResource 所指的video picture resource
																													   （14）如果pDecodeInfo->pReferenceSlots 中一个激活的reference picture 代表一个top field，则该元素的slotIndex指定的关联到top field picture的 DPB slot index 必须匹配在该命令在设备上执行时相同元素的pPictureResource 所指的video picture resource
																													   （15）如果pDecodeInfo->pReferenceSlots 中一个激活的reference picture 代表一个bottom field，则该元素的slotIndex指定的关联到bottom field picture的 DPB slot index 必须匹配在该命令在设备上执行时相同元素的pPictureResource 所指的video picture resource
			31.如果绑定的video session 以video codec operation 为 VK_VIDEO_CODEC_OPERATION_DECODE_H265_BIT_KHR 创建，则（1）pDecodeInfo->pNext中必须包含一个VkVideoDecodeH265PictureInfoKHR结构
																													   （2）则pDecodeInfo->pNext中的VkVideoDecodeH265PictureInfoKHR.pSliceSegmentOffsets 的所有元素 必须小于pDecodeInfo->srcBufferRange
																													   （3）绑定的video session parameters 必须包含vps_video_parameter_set_id 匹配pDecodeInfo->pNext中VkVideoDecodeH265PictureInfoKHR::pStdPictureInfo 中元素的StdVideoDecodeH265PictureInfo::sps_video_parameter_set_id的 StdVideoH265VideoParameterSet 实体
																													   （4）绑定的video session parameters 必须包含sps_video_parameter_set_id 以及 sps_seq_parameter_set_id 匹配pDecodeInfo->pNext中VkVideoDecodeH265PictureInfoKHR::pStdPictureInfo 中元素的StdVideoDecodeH265PictureInfo::sps_video_parameter_set_id 以及 StdVideoDecodeH265PictureInfo::pps_seq_parameter_set_id 的 StdVideoH265SequenceParameterSet 实体
																													   （5）绑定的video session parameters 必须包含sps_video_parameter_set_id, pps_seq_parameter_set_id, 以及 pps_pic_parameter_set_id 都匹配pDecodeInfo->pNext中VkVideoDecodeH265PictureInfoKHR::pStdPictureInfo 中元素的StdVideoDecodeH265PictureInfo::sps_video_parameter_set_id, StdVideoDecodeH265PictureInfo::pps_seq_parameter_set_id, 以及 StdVideoDecodeH265PictureInfo::pps_pic_parameter_set_id 的 StdVideoH265PictureParameterSet 实体
																													   （6）如果pDecodeInfo->pSetupReferenceSlot 不为NULL，则pDecodeInfo->pSetupReferenceSlot->pNext中必须包含一个VkVideoDecodeH265DpbSlotInfoKHR
																													   （7）则pDecodeInfo->pReferenceSlots中每个元素的pNext中必须包含一个VkVideoDecodeH265DpbSlotInfoKHR
			32.如果绑定的video session 以video codec operation 为 VK_VIDEO_CODEC_OPERATION_DECODE_AV1_BIT_KHR 创建，则（1）如果也已VkVideoDecodeAV1ProfileInfoKHR::filmGrainSupport 设为VK_FALSE创建，则decoded picture不能开启film grain
																													  （2）如果pDecodeInfo->pSetupReferenceSlot 不为NULL，且decoded picture 开启film grain，则pDecodeInfo->dstPictureResource 以及pDecodeInfo->pSetupReferenceSlot->pPictureResource 所指的video picture resources 不能匹配
																													  （3）pDecodeInfo->pNext中必须包含一个VkVideoDecodeAV1PictureInfoKHR结构
																													  （4）则pDecodeInfo->pNext中的VkVideoDecodeAV1PictureInfoKHR.frameHeaderOffset 必须小于pDecodeInfo->srcBufferRange的最小值
																													  （5）则pDecodeInfo->pNext中的VkVideoDecodeAV1PictureInfoKHR.pTileOffsets 的所有元素 必须小于pDecodeInfo->srcBufferRange
																													  （6）则pDecodeInfo->pNext中的VkVideoDecodeAV1PictureInfoKHR 中pTileOffsets 以及pTileSizes 的任意i元素，其pTileOffsets[i] + pTileSizes[i]  必须小于等于pDecodeInfo->srcBufferRange
																													  （7）如果pDecodeInfo->pSetupReferenceSlot 不为NULL，则pDecodeInfo->pSetupReferenceSlot->pNext中必须包含一个VkVideoDecodeAV1DpbSlotInfoKHR
																													  （8）则pDecodeInfo->pReferenceSlots中每个元素的pNext中必须包含一个VkVideoDecodeAV1DpbSlotInfoKHR
																													  （9）则pDecodeInfo->pNext中的VkVideoDecodeAV1PictureInfoKHR.referenceNameSlotIndices 中的每个元素必须为负数或者 必须等于pDecodeInfo->pReferenceSlots 中一个元素的slotIndex
																													  （10）则pDecodeInfo->pReferenceSlots 中每个元素的slotIndex 必须等于  pDecodeInfo->pNext中的VkVideoDecodeAV1PictureInfoKHR.referenceNameSlotIndices 中的一个元素值

			*/
		}

	}


	//H.264 Decode Operations  参见p3491
	{}
	{
		/*
		video decode operations 使用一个 H.264 decode profile 来将符合ITU-T H.264 Specification 描述的video stream进行解码

		操作中处理的一些数据结构会对应到ITU-T H.264 Specification 中的对应对象:
			 StdVideoH264SequenceParameterSet ->  H.264 sequence parameter set
			 StdVideoH264PictureParameterSet  ->   H.264 picture parameter set
			 StdVideoDecodeH264PictureInfo   ->    H.264 picture information
			 StdVideoDecodeH264ReferenceInfo ->   H.264 reference information
		*/


		//H.264 Decode Bitstream Data Access  主要描述video bitstream buffer中存储的数据格式，  其他详细信息参见p3492 ***

		//H.264 Decode Picture Data Access  主要描述如何访问video picture resource中的image 数据， 其他详细信息参见p3492  ***


		// H.264 Decode Profile 参见p3493
		{
			/*
			video profile 支持H.264 video decode operations 需要将VkVideoProfileInfoKHR::videoCodecOperation 设置为VK_VIDEO_CODEC_OPERATION_DECODE_H264_BIT_KHR ，且在 VkVideoProfileInfoKHR::pNext 中添加一个VkVideoDecodeH264ProfileInfoKHR
			*/

			VkVideoDecodeH264ProfileInfoKHR videoDecodeH264ProfileInfoKHR{};
			videoDecodeH264ProfileInfoKHR.sType = VK_STRUCTURE_TYPE_VIDEO_DECODE_H264_PROFILE_INFO_KHR;
			videoDecodeH264ProfileInfoKHR.pNext = nullptr;
			videoDecodeH264ProfileInfoKHR.pictureLayout = VK_VIDEO_DECODE_H264_PICTURE_LAYOUT_INTERLACED_INTERLEAVED_LINES_BIT_KHR;//为一个 VkVideoDecodeH264PictureLayoutFlagBitsKHR 值，指明用于解码 H.264 video sequence的picture layout
			/*
			VkVideoDecodeH264PictureLayoutFlagBitsKHR:
			VK_VIDEO_DECODE_H264_PICTURE_LAYOUT_PROGRESSIVE_KHR : 指明支持progressive content （渐进式内容）。该flags实际值为0
			VK_VIDEO_DECODE_H264_PICTURE_LAYOUT_INTERLACED_INTERLEAVED_LINES_BIT_KHR : 指明支持或者使用一个interlaced content的picture layout，指明所有属于top field 的行将解码到picture resource的偶数行，所有属于bottom field 的行将解码到picture resource的奇数行。
			VK_VIDEO_DECODE_H264_PICTURE_LAYOUT_INTERLACED_SEPARATE_PLANES_BIT_KHR : 指明支持或者使用一个interlaced content的picture layout，指明所有属于一个 field 的行将成组解码到picture resource的一个image subregion中，组成frame的两个fields可以存储在相同image的image subresource中的不同subregion 或者存储在不同的image subresource中。
			
			*/
			videoDecodeH264ProfileInfoKHR.stdProfileIdc = STD_VIDEO_H264_PROFILE_IDC_MAIN;//为一个StdVideoH264ProfileIdc 值，指明H.264 codec profile IDC（定义在 ITU-T H.264 Specification中的A.2章节）



		}


		//H.264 Decode Capabilities  参见p3495
		{
			/*
			当调用 vkGetPhysicalDeviceVideoCapabilitiesKHR 查询 H.264 decode profile能力时,需要在VkVideoCapabilitiesKHR::pNext 中添加一个VkVideoDecodeH264CapabilitiesKHR来返回profile-specific 能力

			*/

			VkVideoDecodeH264CapabilitiesKHR videoDecodeH264CapabilitiesKHR{};
			videoDecodeH264CapabilitiesKHR.sType = VK_STRUCTURE_TYPE_VIDEO_DECODE_H264_CAPABILITIES_KHR;
			videoDecodeH264CapabilitiesKHR.pNext = nullptr;
			videoDecodeH264CapabilitiesKHR.fieldOffsetGranularity = VkOffset2D{ .x = 1,.y = 0 };//为当使用picture layout为VK_VIDEO_DECODE_H264_PICTURE_LAYOUT_INTERLACED_SEPARATE_PLANES_BIT_KHR的 一个video picture resource的VkVideoPictureResourceInfoKHR::codedOffset的最小对齐粒度
			videoDecodeH264CapabilitiesKHR.maxLevelIdc = STD_VIDEO_H264_LEVEL_IDC_1_0;//一个StdVideoH264LevelIdc 值，指明该profile支持的最大的H.264 level，其中值格式为STD_VIDEO_H264_LEVEL_IDC_<major>_<minor> 指明H.264 level， <major>.<minor> 参见 ITU-T H.264 Specification的A.3章节


		}


		//H.264 Decode Parameter Sets  参见p3495
		{
			/*
			以VK_VIDEO_CODEC_OPERATION_DECODE_H264_BIT_KHR创建的 video session parameters 会包含以下参数组:
				> H.264 Sequence Parameter Sets (SPS)参数组（见 ITU-T H.264 Specification）,对应StdVideoH264SequenceParameterSet ，参数组中参数的具体描述 见p3496 *** ;
				> H.264 Picture Parameter Sets (PPS)参数组（见 ITU-T H.264 Specification）,对应 StdVideoH264PictureParameterSet ，参数组中参数的具体描述 见p3496 *** ;

			*/


			//当一个video session parameters 以VK_VIDEO_CODEC_OPERATION_DECODE_H264_BIT_KHR 创建时，  VkVideoSessionParametersCreateInfoKHR::pNext 中必须包含一个 VkVideoDecodeH264SessionParametersCreateInfoKHR 指明该对象的初始容量
			VkVideoDecodeH264SessionParametersCreateInfoKHR videoDecodeH264SessionParametersCreateInfoKHR{};
			videoDecodeH264SessionParametersCreateInfoKHR.sType = VK_STRUCTURE_TYPE_VIDEO_DECODE_H264_SESSION_PARAMETERS_CREATE_INFO_KHR;
			videoDecodeH264SessionParametersCreateInfoKHR.pNext = nullptr;
			videoDecodeH264SessionParametersCreateInfoKHR.maxStdSPSCount = 1;//为创建的 VkVideoSessionParametersKHR 能包含的H.264 SPS 实体的最大数量
			videoDecodeH264SessionParametersCreateInfoKHR.maxStdPPSCount = 1;//为创建的 VkVideoSessionParametersKHR 能包含的H.264 PPS 实体的最大数量
			VkVideoDecodeH264SessionParametersAddInfoKHR videoDecodeH264SessionParametersAddInfoKHR{};
			{
				videoDecodeH264SessionParametersAddInfoKHR.sType = VK_STRUCTURE_TYPE_VIDEO_DECODE_H264_SESSION_PARAMETERS_ADD_INFO_KHR;
				videoDecodeH264SessionParametersAddInfoKHR.pNext = nullptr;
				videoDecodeH264SessionParametersAddInfoKHR.stdSPSCount = 1;//为pStdSPSs 中的元素个数
				StdVideoH264SequenceParameterSet stdVideoH264SequenceParameterSet{/*假设这是一个有效的StdVideoH264SequenceParameterSet 结构体*/ };
				videoDecodeH264SessionParametersAddInfoKHR.pStdSPSs = &stdVideoH264SequenceParameterSet;//一组StdVideoH264SequenceParameterSet 数组指针指明添加的H.264 SPS 实体
				videoDecodeH264SessionParametersAddInfoKHR.stdPPSCount = 1;//为pStdPPSs 中的元素个数
				StdVideoH264PictureParameterSet stdVideoH264PictureParameterSet{/*假设这是一个有效的StdVideoH264PictureParameterSet 结构体*/ };
				videoDecodeH264SessionParametersAddInfoKHR.pStdPPSs = &stdVideoH264PictureParameterSet;//一组 StdVideoH264PictureParameterSet 数组指针指明添加的H.264 PPS 实体
				/*
				VkVideoDecodeH264SessionParametersAddInfoKHR有效用法:
				1.pStdSPSs中每个StdVideoH264SequenceParameterSet元素的 seq_parameter_set_id必须是唯一的
				2.pStdPPSs中每个StdVideoH264PictureParameterSet元素的 seq_parameter_set_id 以及 pic_parameter_set_id 参数对必须是唯一的
				*/
			}
			videoDecodeH264SessionParametersCreateInfoKHR.pParametersAddInfo = &videoDecodeH264SessionParametersAddInfoKHR;//为NULL或者一个 VkVideoDecodeH264SessionParametersAddInfoKHR 指针指明创建时添加的H.264 parameters


		}


		//H.264 Decoding Parameters  参见p3499
		{
			//在vkCmdDecodeVideoKHR 的 VkVideoDecodeInfoKHR.pNext中包含VkVideoDecodeH264PictureInfoKHR 指定 H.264 decode operation的codec-specific picture 信息，这些信息如何解释参见 p3499 ***
			VkVideoDecodeH264PictureInfoKHR  videoDecodeH264PictureInfoKHR{};
			videoDecodeH264PictureInfoKHR.sType = VK_STRUCTURE_TYPE_VIDEO_DECODE_H264_PICTURE_INFO_KHR;
			videoDecodeH264PictureInfoKHR.pNext = nullptr;
			videoDecodeH264PictureInfoKHR.sliceCount = 1;//pSliceOffsets 中的元素个数
			uint32_t sliceOffset = 0;
			videoDecodeH264PictureInfoKHR.pSliceOffsets = &sliceOffset;//指明picture中每个slice数据在 VkVideoDecodeInfoKHR指定的 video bitstream buffer 范围中的起始字节偏移量
			StdVideoDecodeH264PictureInfo stdVideoDecodeH264PictureInfo{/*假设这是一个有效的StdVideoDecodeH264PictureInfo 结构体*/ };
			videoDecodeH264PictureInfoKHR.pStdPictureInfo = &stdVideoDecodeH264PictureInfo;//一个StdVideoDecodeH264PictureInfo 的指针，指明 H.264 picture information


			//可以在 VkVideoDecodeInfoKHR::pSetupReferenceSlot->pNext 以及  VkVideoDecodeInfoKHR::pReferenceSlots->pNext 中包含VkVideoDecodeH264DpbSlotInfoKHR  来指明codec-specific reference picture information，具体信息如何解释见  p3501 ***
			VkVideoDecodeH264DpbSlotInfoKHR  videoDecodeH264DpbSlotInfoKHR{};
			videoDecodeH264DpbSlotInfoKHR.sType = VK_STRUCTURE_TYPE_VIDEO_DECODE_H264_DPB_SLOT_INFO_KHR;
			videoDecodeH264DpbSlotInfoKHR.pNext = nullptr;
			StdVideoDecodeH264ReferenceInfo stdVideoDecodeH264ReferenceInfo{/*假设这是一个有效的StdVideoDecodeH264ReferenceInfo 结构体*/ };
			videoDecodeH264DpbSlotInfoKHR.pStdReferenceInfo = &stdVideoDecodeH264ReferenceInfo;//一个StdVideoDecodeH264ReferenceInfo 指针，指明 H.264 reference information

		}


		//H.264 Decode Requirements  参见p3503
		{
			/*
			要支持H.264 decoding，则physical device至少要含有一个支持VK_VIDEO_CODEC_OPERATION_DECODE_H264_BIT_KHR的队列族，见vkGetPhysicalDeviceQueueFamilyProperties2返回的VkQueueFamilyVideoPropertiesKHR::videoCodecOperations

			除此之外，还要求physical device要必须支持指定的需要，具体见p3503
			Table 51. Required Video Std Header Versions
			Table 52. Required Video Capabilities

			*/
		}
	}


	//H.265 Decode Operations  参见p3504
	{}
	{
		/*
		video decode operations 使用一个 H.265 decode profile 来将符合ITU-T H.265 Specification 描述的video stream进行解码
		
		操作中处理的一些数据结构会对应到ITU-T H.265 Specification 中的对应对象:
			 StdVideoH265VideoParameterSet   ->   H.265 video parameter set
			 StdVideoH265SequenceParameterSet ->  H.265 sequence parameter set
			 StdVideoH265PictureParameterSet  ->   H.265 picture parameter set
			 StdVideoDecodeH265PictureInfo   ->    H.265 picture information
			 StdVideoDecodeH265ReferenceInfo ->   H.265 reference information
		*/

		//H.265 Decode Bitstream Data Access  主要描述video bitstream buffer中存储的数据格式，  其他详细信息参见p3505 ***

		//H.265 Decode Picture Data Access  主要描述如何访问video picture resource中的image 数据， 其他详细信息参见p3505  ***



		// H.265 Decode Profile 参见p3506
		{
			/*
			video profile 支持H.265 video decode operations 需要将VkVideoProfileInfoKHR::videoCodecOperation 设置为VK_VIDEO_CODEC_OPERATION_DECODE_H265_BIT_KHR ，且在 VkVideoProfileInfoKHR::pNext 中添加一个VkVideoDecodeH265ProfileInfoKHR
			*/

			VkVideoDecodeH265ProfileInfoKHR videoDecodeH265ProfileInfoKHR{};
			videoDecodeH265ProfileInfoKHR.sType = VK_STRUCTURE_TYPE_VIDEO_DECODE_H265_PROFILE_INFO_KHR;
			videoDecodeH265ProfileInfoKHR.pNext = nullptr;
			videoDecodeH265ProfileInfoKHR.stdProfileIdc = STD_VIDEO_H265_PROFILE_IDC_MAIN;//为一个StdVideoH265ProfileIdc 值，指明H.265 codec profile IDC（定义在 ITU-T H.265 Specification中的A.3章节）

		}

		//H.265 Decode Capabilities  参见p3506
		{
			/*
			当调用 vkGetPhysicalDeviceVideoCapabilitiesKHR 查询 H.265 decode profile能力时,需要在VkVideoCapabilitiesKHR::pNext 中添加一个VkVideoDecodeH265CapabilitiesKHR来返回profile-specific 能力

			*/

			VkVideoDecodeH265CapabilitiesKHR videoDecodeH265CapabilitiesKHR{};
			videoDecodeH265CapabilitiesKHR.sType = VK_STRUCTURE_TYPE_VIDEO_DECODE_H265_CAPABILITIES_KHR;
			videoDecodeH265CapabilitiesKHR.pNext = nullptr;
			videoDecodeH265CapabilitiesKHR.maxLevelIdc = STD_VIDEO_H265_LEVEL_IDC_1_0;//一个StdVideoH265LevelIdc 值，指明该profile支持的最大的H.265 level，其中值格式为STD_VIDEO_H265_LEVEL_IDC_<major>_<minor> 指明H.265 level， <major>.<minor> 参见 ITU-T H.265 Specification的A.4章节


		}


		//H.265 Decode Parameter Sets  参见p3507
		{
			/*
			以VK_VIDEO_CODEC_OPERATION_DECODE_H265_BIT_KHR创建的 video session parameters 会包含以下参数组:
				> H.265 Video Parameter Sets (VPS) 参数组（见 ITU-T H.265 Specification）,对应StdVideoH265VideoParameterSet ，参数组中参数的具体描述 见p3507 *** ;
				> H.265 Sequence Parameter Sets (SPS)参数组（见 ITU-T H.265 Specification）,对应StdVideoH265SequenceParameterSet ，参数组中参数的具体描述 见p3508 *** ;
				> H.265 Picture Parameter Sets (PPS)参数组（见 ITU-T H.265 Specification）,对应 StdVideoH265PictureParameterSet ，参数组中参数的具体描述 见p3511 *** ;

			*/


			//当一个video session parameters 以VK_VIDEO_CODEC_OPERATION_DECODE_H265_BIT_KHR 创建时，  VkVideoSessionParametersCreateInfoKHR::pNext 中必须包含一个 VkVideoDecodeH265SessionParametersCreateInfoKHR 指明该对象的初始容量
			VkVideoDecodeH265SessionParametersCreateInfoKHR videoDecodeH265SessionParametersCreateInfoKHR{};
			videoDecodeH265SessionParametersCreateInfoKHR.sType = VK_STRUCTURE_TYPE_VIDEO_DECODE_H265_SESSION_PARAMETERS_CREATE_INFO_KHR;
			videoDecodeH265SessionParametersCreateInfoKHR.pNext = nullptr;
			videoDecodeH265SessionParametersCreateInfoKHR.maxStdVPSCount = 1;//为创建的 VkVideoSessionParametersKHR 能包含的H.265 VPS 实体的最大数量
			videoDecodeH265SessionParametersCreateInfoKHR.maxStdSPSCount = 1;//为创建的 VkVideoSessionParametersKHR 能包含的H.265 SPS 实体的最大数量
			videoDecodeH265SessionParametersCreateInfoKHR.maxStdPPSCount = 1;//为创建的 VkVideoSessionParametersKHR 能包含的H.265 PPS 实体的最大数量
			VkVideoDecodeH265SessionParametersAddInfoKHR videoDecodeH265SessionParametersAddInfoKHR{};
			{
				videoDecodeH265SessionParametersAddInfoKHR.sType = VK_STRUCTURE_TYPE_VIDEO_DECODE_H265_SESSION_PARAMETERS_ADD_INFO_KHR;
				videoDecodeH265SessionParametersAddInfoKHR.pNext = nullptr;
				videoDecodeH265SessionParametersAddInfoKHR.stdVPSCount = 1;//为pStdVPSs 中的元素个数
				StdVideoH265VideoParameterSet stdVideoH265VideoParameterSet{/*假设这是一个有效的StdVideoH265VideoParameterSet 结构体*/ };//一组StdVideoH265VideoParameterSet 数组指针指明添加的H.265 VPS 实体
				videoDecodeH265SessionParametersAddInfoKHR.pStdVPSs = &stdVideoH265VideoParameterSet;
				videoDecodeH265SessionParametersAddInfoKHR.stdSPSCount = 1;//为pStdSPSs 中的元素个数
				StdVideoH265SequenceParameterSet stdVideoH265SequenceParameterSet{/*假设这是一个有效的StdVideoH265SequenceParameterSet 结构体*/ };
				videoDecodeH265SessionParametersAddInfoKHR.pStdSPSs = &stdVideoH265SequenceParameterSet;//一组StdVideoH265SequenceParameterSet 数组指针指明添加的H.265 SPS 实体
				videoDecodeH265SessionParametersAddInfoKHR.stdPPSCount = 1;//为pStdPPSs 中的元素个数
				StdVideoH265PictureParameterSet stdVideoH265PictureParameterSet{/*假设这是一个有效的StdVideoH265PictureParameterSet 结构体*/ };
				videoDecodeH265SessionParametersAddInfoKHR.pStdPPSs = &stdVideoH265PictureParameterSet;//一组 StdVideoH265PictureParameterSet 数组指针指明添加的H.265 PPS 实体
				/*
				VkVideoDecodeH265SessionParametersAddInfoKHR有效用法:
				1.pStdVPSs中每个StdVideoH265VideoParameterSet元素的 vps_video_parameter_set_id必须是唯一的
				2.pStdSPSs中每个StdVideoH265PictureParameterSet元素的 sps_video_parameter_set_id 以及 sps_seq_parameter_set_id 参数对必须是唯一的
				3.pStdPPSs中每个StdVideoH265PictureParameterSet元素的 sps_video_parameter_set_id,pps_seq_parameter_set_id以及 pps_pic_parameter_set_id的参数三元组必须是唯一的
				*/
			}
			videoDecodeH265SessionParametersCreateInfoKHR.pParametersAddInfo = &videoDecodeH265SessionParametersAddInfoKHR;//为NULL或者一个 VkVideoDecodeH265SessionParametersAddInfoKHR 指针指明创建时添加的H.265 parameters


		}




		//H.265 Decoding Parameters  参见p3513
		{
			//在vkCmdDecodeVideoKHR 的 VkVideoDecodeInfoKHR.pNext中包含VkVideoDecodeH265PictureInfoKHR 指定 H.265 decode operation的codec-specific picture 信息，这些信息如何解释参见 p3514 ***
			VkVideoDecodeH265PictureInfoKHR  videoDecodeH265PictureInfoKHR{};
			videoDecodeH265PictureInfoKHR.sType = VK_STRUCTURE_TYPE_VIDEO_DECODE_H265_PICTURE_INFO_KHR;
			videoDecodeH265PictureInfoKHR.pNext = nullptr;
			videoDecodeH265PictureInfoKHR.sliceSegmentCount = 1;//pSliceSegmentOffsets 中的元素个数
			uint32_t sliceSegmentOffset = 0;
			videoDecodeH265PictureInfoKHR.pSliceSegmentOffsets = &sliceSegmentOffset;//指明picture中每个slice segments数据在 VkVideoDecodeInfoKHR指定的 video bitstream buffer 范围中的起始字节偏移量
			StdVideoDecodeH265PictureInfo stdVideoDecodeH265PictureInfo{/*假设这是一个有效的StdVideoDecodeH265PictureInfo 结构体*/ };
			videoDecodeH265PictureInfoKHR.pStdPictureInfo = &stdVideoDecodeH265PictureInfo;//一个StdVideoDecodeH265PictureInfo 的指针，指明 H.265 picture information


			//可以在 VkVideoDecodeInfoKHR::pSetupReferenceSlot->pNext 以及  VkVideoDecodeInfoKHR::pReferenceSlots->pNext 中包含VkVideoDecodeH265DpbSlotInfoKHR  来指明codec-specific reference picture information，具体信息如何解释见  p3517 ***
			VkVideoDecodeH265DpbSlotInfoKHR  videoDecodeH265DpbSlotInfoKHR{};
			videoDecodeH265DpbSlotInfoKHR.sType = VK_STRUCTURE_TYPE_VIDEO_DECODE_H265_DPB_SLOT_INFO_KHR;
			videoDecodeH265DpbSlotInfoKHR.pNext = nullptr;
			StdVideoDecodeH265ReferenceInfo stdVideoDecodeH265ReferenceInfo{/*假设这是一个有效的StdVideoDecodeH265ReferenceInfo 结构体*/ };
			videoDecodeH265DpbSlotInfoKHR.pStdReferenceInfo = &stdVideoDecodeH265ReferenceInfo;//一个StdVideoDecodeH265ReferenceInfo 指针，指明 H.265 reference information

		}

		//H.265 Decode Requirements  参见p3517
		{
			/*
			要支持H.265 decoding，则physical device至少要含有一个支持VK_VIDEO_CODEC_OPERATION_DECODE_H265_BIT_KHR的队列族，见vkGetPhysicalDeviceQueueFamilyProperties2返回的VkQueueFamilyVideoPropertiesKHR::videoCodecOperations

			除此之外，还要求physical device要必须支持指定的需要，具体见p3517
			Table 53. Required Video Std Header Versions
			Table 54. Required Video Capabilities

			*/
		}
	}


	//AV1 Decode Operations  参见p3518
	{}
	{
		/*
		video decode operations 使用一个AV1 decode profile 来将符合 AV1 Specification描述的video stream进行解码
		
		操作中处理的一些数据结构会对应到AV1 Specification 中的对应对象:
			 StdVideoAV1SequenceHeader   ->   存储在video session parameters中指定 active sequence header
			 StdVideoDecodeAV1PictureInfo ->   AV1 picture information
			 StdVideoDecodeAV1ReferenceInfo  ->  AV1 reference information
		*/


		//AV1 Decode Bitstream Data Access  主要描述video bitstream buffer中存储的数据格式，  其他详细信息参见p3519 ***

		//AV1 Decode Picture Data Access  主要描述如何访问video picture resource中的image 数据，  其他详细信息参见p3519  ***


		//AV1 Reference Names and Semantics  参见p3520,  主要描述为不同的 reference frames有不同的语义，所以用StdVideoAV1ReferenceName 类型的不同枚举值来引用不同的reference frames
		
		
		//AV1 Decode Profile 参见p3520
		{
			/*
			video profile 支持AV1 video decode operations 需要将VkVideoProfileInfoKHR::videoCodecOperation 设置为VK_VIDEO_CODEC_OPERATION_DECODE_AV1_BIT_KHR ，且在 VkVideoProfileInfoKHR::pNext 中添加一个 VkVideoDecodeAV1ProfileInfoKHR
			*/
		
			VkVideoDecodeAV1ProfileInfoKHR  videoDecodeAV1ProfileInfoKHR{};
			videoDecodeAV1ProfileInfoKHR.sType = VK_STRUCTURE_TYPE_MAX_ENUM;//没有定义所以这里定义为非法值
			videoDecodeAV1ProfileInfoKHR.pNext = nullptr;
			videoDecodeAV1ProfileInfoKHR.filmGrainSupport = VK_TRUE;//指明是否支持AV1 film grain（定义在AV1 Specification中的 7.8.3节），如果为VK_TRUE，则对video profile创建的video session可以在decode操作中开启film grain
			videoDecodeAV1ProfileInfoKHR.stdProfile = 0;//为一个StdVideoAV1Profile 值，指明AV1 codec profile（定义在 AV1 Specification中的A.2章节）
		
				}
		
		
		//AV1 Decode Capabilities  参见p3521
		{
			/*
			当调用 vkGetPhysicalDeviceVideoCapabilitiesKHR 查询 AV1 decode profile能力时,需要在VkVideoCapabilitiesKHR::pNext 中添加一个VkVideoDecodeAV1CapabilitiesKHR来返回profile-specific 能力
		
			*/
		
			VkVideoDecodeAV1CapabilitiesKHR videoDecodeAV1CapabilitiesKHR{};
			videoDecodeAV1CapabilitiesKHR.sType = VK_STRUCTURE_TYPE_MAX_ENUM;//没有定义所以这里定义为非法值
			videoDecodeAV1CapabilitiesKHR.pNext = nullptr;
			videoDecodeAV1CapabilitiesKHR.maxLevel = 0;//一个StdVideoAV1Level 值，指明该profile支持的最大的AV1 level（参见AV1 Specification的A.3章节）
		
		
		}
		
		
		//AV1 Decode Parameter Sets  参见p3522
		{
			/*
			以VK_VIDEO_CODEC_OPERATION_DECODE_AV1_BIT_KHR创建的 video session parameters 会包含以下参数:
				> AV1 Sequence Header 数据结构（见 AV1 Specification）,对应StdVideoAV1SequenceHeader ，参数组中参数的具体描述 见p3522 *** ;
		
			*/
		
		
			//当一个video session parameters 以VK_VIDEO_CODEC_OPERATION_DECODE_AV1_BIT_KHR 创建时，  VkVideoSessionParametersCreateInfoKHR::pNext 中必须包含一个 VkVideoDecodeAV1SessionParametersCreateInfoKHR 指明该对象的内容
			VkVideoDecodeAV1SessionParametersCreateInfoKHR videoDecodeAV1SessionParametersCreateInfoKHR{};
			videoDecodeAV1SessionParametersCreateInfoKHR.sType = VK_STRUCTURE_TYPE_MAX_ENUM;//没有定义所以这里定义为非法值
			videoDecodeAV1SessionParametersCreateInfoKHR.pNext = nullptr;
			StdVideoAV1SequenceHeader stdVideoAV1SequenceHeader{};
			videoDecodeAV1SessionParametersCreateInfoKHR.pStdSequenceHeader = &stdVideoAV1SequenceHeader;//为一个 StdVideoAV1SequenceHeader 的指针，描述存储在video session parameters对象中的 AV1 sequence header，在创建video session parameters时指定，不可以通过vkUpdateVideoSessionParametersKHR 更新
		
		}
		
		
		//AV1 Decoding Parameters  参见p3513
		{
			//在vkCmdDecodeVideoKHR 的 VkVideoDecodeInfoKHR.pNext中包含VkVideoDecodeAV1PictureInfoKHR 指定 AV1 decode operation的codec-specific picture 信息，这些信息如何解释参见 p3524 - p3526***
			VkVideoDecodeAV1PictureInfoKHR  videoDecodeAV1PictureInfoKHR{};
			videoDecodeAV1PictureInfoKHR.sType = VK_STRUCTURE_TYPE_MAX_ENUM;//没有定义所以这里定义为非法值
			videoDecodeAV1PictureInfoKHR.pNext = nullptr;
			StdVideoDecodeAV1PictureInfo stdVideoDecodeAV1PictureInfo{/*假设这是一个有效的StdVideoDecodeAV1PictureInfo*/ };
			videoDecodeAV1PictureInfoKHR.pStdPictureInfo = &stdVideoDecodeAV1PictureInfo; //一个StdVideoDecodeAV1PictureInfo 指针，指明 AV1 picture information
			videoDecodeAV1PictureInfoKHR.referenceNameSlotIndices[VK_MAX_VIDEO_AV1_REFERENCES_PER_FRAME_KHR];//为VK_MAX_VIDEO_AV1_REFERENCES_PER_FRAME_KHR 个整数值的数组，每个元素为一个负数或者指明对应 AV1 reference name的 DPB slot 索引，AV1 reference name frame的DPB slot索引为 referenceNameSlotIndices[frame - STD_VIDEO_AV1_REFERENCE_NAME_LAST_FRAME]
			for (uint32_t i = 0; i < VK_MAX_VIDEO_AV1_REFERENCES_PER_FRAME_KHR; i++)
			{
				videoDecodeAV1PictureInfoKHR.referenceNameSlotIndices[i] = 0;
			}
			videoDecodeAV1PictureInfoKHR.frameHeaderOffset = 0;//为AV1 frame header OBU在 VkVideoDecodeInfoKHR中指定的 video bitstream buffer的范围内的起始字节偏移量
			videoDecodeAV1PictureInfoKHR.tileCount = 1;//为 pTileOffsets 以及 pTileSizes中的元素个数
			uint32_t tileOffset = 0, tileSize = 4;
			videoDecodeAV1PictureInfoKHR.pTileOffsets = &tileOffset;//为 picture的tiles在 VkVideoDecodeInfoKHR中指定的 video bitstream buffer的范围内的起始字节偏移量的数组指针
			videoDecodeAV1PictureInfoKHR.pTileSizes = &tileSize;//为 picture的tiles在 VkVideoDecodeInfoKHR中指定的 video bitstream buffer的范围内的字节数量大小的数组指针
		
		
			//可以在 VkVideoDecodeInfoKHR::pSetupReferenceSlot->pNext 以及  VkVideoDecodeInfoKHR::pReferenceSlots->pNext 中包含VkVideoDecodeAV1DpbSlotInfoKHR  来指明codec-specific reference picture information，具体信息如何解释见  p3527 ***
			VkVideoDecodeAV1DpbSlotInfoKHR  videoDecodeAV1DpbSlotInfoKHR{};
			videoDecodeAV1DpbSlotInfoKHR.sType = VK_STRUCTURE_TYPE_MAX_ENUM;//没有定义所以这里定义为非法值
			videoDecodeAV1DpbSlotInfoKHR.pNext = nullptr;
			StdVideoDecodeAV1ReferenceInfo stdVideoDecodeAV1ReferenceInfo{/*假设这是一个有效的StdVideoDecodeAV1ReferenceInfo 结构体*/ };
			videoDecodeAV1DpbSlotInfoKHR.pStdReferenceInfo = &stdVideoDecodeAV1ReferenceInfo;//一个StdVideoDecodeAV1ReferenceInfo 指针，指明 AV1 reference information
		
		}
		
		
		// AV1 Decode Requirements  参见p3528
		{
			/*
			要支持 AV1 decoding，则physical device至少要含有一个支持VK_VIDEO_CODEC_OPERATION_DECODE_AV1_BIT_KHR的队列族，见vkGetPhysicalDeviceQueueFamilyProperties2返回的VkQueueFamilyVideoPropertiesKHR::videoCodecOperations
		
			除此之外，还要求physical device要必须支持指定的需要，具体见p3528
			Table 55. Required Video Std Header Versions
			Table 56. Required Video Capabilities
		
			*/
		}
	}



	// Video Encode Operations  参见3529
	{}
	{
		/*
		video encode operations 消耗一个 encode input picture 以及零个或者多个 reference pictures中来产生存储到video bitstream buffer  以及可选的一个reconstructed  picture 中的压缩的数据
		
		video encode operations 中对资源的同步在VK_PIPELINE_STAGE_2_VIDEO_ENCODE_BIT_KHR stage，其中用于该操作输入的资源以 VK_ACCESS_2_VIDEO_ENCODE_READ_BIT_KHR. 访问，输出以VK_ACCESS_2_VIDEO_ENCODE_WRITE_BIT_KHR 访问。用于在操作中的image的layout在除了该image只用于作为一个encode input picture 为 VK_IMAGE_LAYOUT_VIDEO_ENCODE_SRC_KHR，其他情况下为VK_IMAGE_LAYOUT_VIDEO_ENCODE_DPB_KHR
		*/
		
		
		// Codec-Specific Semantics 参见p3530  
		{
			/*
			video encode operations的一些步骤或者行为是 codec-specific，即对应不用的codec操作类型，这些步骤和行为可能有所不同
			*/

			//Video Encode Parameter Overrides  参见p3531  , 简单讲就是根据压缩编制，实现一般在其Video Std headers中包含一部分codec-specific parameters，因为存放全部的codec-specific parameters是不现实的，所以实现允许修改这些codec-specific parameters。
		}

		//Video Encode Operation Steps  参见p3531  简单描述为video encode operations的一些步骤为： 读取 input picture的数据 -> 确定编码质量等信息然后执行编码操作 -> 写入编码数据到video bitstream buffer  ->如果有需要则根据编码数据执行 picture reconstruction然后输出写入 reconstructed picture 

		//Capabilities 参见p3532
		{

			// VkVideoEncodeCapabilitiesKHR 可以包含在调用 vkGetPhysicalDeviceVideoCapabilitiesKHR传入的 VkVideoCapabilitiesKHR.pNext中用于返回视频编码能力的信息
			//VkVideoCapabilitiesKHR.pNext
			VkVideoEncodeCapabilitiesKHR videoEncodeCapabilitiesKHR{};
			videoEncodeCapabilitiesKHR.sType = VK_STRUCTURE_TYPE_MAX_ENUM;//没有定义这里设置为非法值
			videoEncodeCapabilitiesKHR.pNext = nullptr;
			videoEncodeCapabilitiesKHR.flags = VK_VIDEO_ENCODE_CAPABILITY_PRECEDING_EXTERNALLY_ENCODED_BYTES_BIT_KHR;/*VkVideoEncodeCapabilityFlagBitsKHR 组合值位掩码，描述编码支持的特性
			VkVideoEncodeCapabilityFlagBitsKHR:
			VK_VIDEO_ENCODE_CAPABILITY_PRECEDING_EXTERNALLY_ENCODED_BYTES_BIT_KHR : 指明实现支持使用VkVideoEncodeInfoKHR::precedingExternallyEncodedBytes
			VK_VIDEO_ENCODE_CAPABILITY_INSUFFICIENT_BITSTREAM_BUFFER_RANGE_DETECTION_BIT_KHR : 指明实现能够当提供的destination video bitstream buffer的内存范围不够大以容纳video encode operation编码的bitstream data时能够检测以及将VK_QUERY_RESULT_STATUS_INSUFFICIENT_BITSTREAM_BUFFER_RANGE_KHR 报告到query result status			
			*/
			videoEncodeCapabilitiesKHR.rateControlModes = VK_VIDEO_ENCODE_RATE_CONTROL_MODE_DEFAULT_KHR;//VkVideoEncodeRateControlModeFlagBitsKHR 组合值位掩码，指明支持的 rate control modes
			videoEncodeCapabilitiesKHR.maxRateControlLayers = 1;//指明支持的 rate control layers的最大数量
			videoEncodeCapabilitiesKHR.maxBitrate = 1;//指明支持的最大比特速率
			videoEncodeCapabilitiesKHR.maxQualityLevels = 1;//指明支持的离散video encode quality levels的最大等级数量，至少要支持一个
			videoEncodeCapabilitiesKHR.encodeInputPictureGranularity = VkExtent2D{.width = 1,.height = 1};//指明被编码的 encode input picture数据的粒度，最大可能到 codec-specific coding block size的粒度
			videoEncodeCapabilitiesKHR.supportedEncodeFeedbackFlags = VK_VIDEO_ENCODE_FEEDBACK_BITSTREAM_BUFFER_OFFSET_BIT_KHR;//VkVideoEncodeFeedbackFlagBitsKHR 组合值位掩码，指明支持的 video encode feedback queries标志，至少要包含VK_VIDEO_ENCODE_FEEDBACK_BITSTREAM_BUFFER_OFFSET_BIT_KHR 以及VK_VIDEO_ENCODE_FEEDBACK_BITSTREAM_BYTES_WRITTEN_BIT_KHR


		}


		// Video Encode Quality Levels  参见p3535
		{
			/*
			实现对video encode profile可以支持多个 video encode quality levels，这些等级控制在编码过程中的工具以及算法的种类以及数量。一般来说，使用的video encode quality level越高，则使用的工具或者算法越多，编码质量越好，但这并不是绝对的。
			
			*/

			//查询指定video encode profile支持的 video encode quality level
			VkPhysicalDeviceVideoEncodeQualityLevelInfoKHR physicalDeviceVideoEncodeQualityLevelInfoKHR{};
			physicalDeviceVideoEncodeQualityLevelInfoKHR.sType = VK_STRUCTURE_TYPE_MAX_ENUM;//没有定义这里定义为非法值
			physicalDeviceVideoEncodeQualityLevelInfoKHR.pNext = nullptr;
			VkVideoProfileInfoKHR videoProfileInfoKHR{/*假设这是一个有效的VkVideoProfileInfoKHR*/};//前面已经描述过，这里不再复述
			physicalDeviceVideoEncodeQualityLevelInfoKHR.pVideoProfile = &videoProfileInfoKHR;//为 VkVideoProfileInfoKHR 指针，指明要查询video encode quality level 属性的video profile
			physicalDeviceVideoEncodeQualityLevelInfoKHR.qualityLevel = 0;//指明要查询属性的video encode quality level
			/*
			VkPhysicalDeviceVideoEncodeQualityLevelInfoKHR有效用法:
			1.pVideoProfile 必须时支持的video profile
			2.pVideoProfile->videoCodecOperation 必须指定一个encode operation
			3.qualityLevel 必须小于调用vkGetPhysicalDeviceVideoCapabilitiesKHR 传入pVideoProfile指定的video profile返回的VkVideoEncodeCapabilitiesKHR::maxQualityLevels
			*/


			VkVideoEncodeQualityLevelPropertiesKHR videoEncodeQualityLevelPropertiesKHR{};
			videoEncodeQualityLevelPropertiesKHR.sType = VK_STRUCTURE_TYPE_MAX_ENUM;//没有定义这里定义为非法值
			videoEncodeQualityLevelPropertiesKHR.pNext = nullptr;//可以包含一个 VkVideoEncodeH264QualityLevelPropertiesKHR 或者VkVideoEncodeH265QualityLevelPropertiesKHR
			videoEncodeQualityLevelPropertiesKHR.preferredRateControlLayerCount = 0;//为返回的更适合用于 video encode quality level 的 rate control layers的数量
			videoEncodeQualityLevelPropertiesKHR.preferredRateControlMode = VK_VIDEO_ENCODE_RATE_CONTROL_MODE_DEFAULT_KHR;//为返回的 VkVideoEncodeRateControlModeFlagBitsKHR值，指明该video encode quality level更适合的 rate control mode

			vkGetPhysicalDeviceVideoEncodeQualityLevelPropertiesKHR(physicalDevice, &physicalDeviceVideoEncodeQualityLevelInfoKHR, &videoEncodeQualityLevelPropertiesKHR);//假设正确返回了结果
			/*
			vkGetPhysicalDeviceVideoEncodeQualityLevelPropertiesKHR有效用法:
			1.如果pQualityLevelInfo->pVideoProfile->videoCodecOperation为VK_VIDEO_CODEC_OPERATION_ENCODE_H264_BIT_KHR，则pQualityLevelProperties->pNext中必须包含一个VkVideoEncodeH264QualityLevelPropertiesKHR
			2.如果pQualityLevelInfo->pVideoProfile->videoCodecOperation为VK_VIDEO_CODEC_OPERATION_ENCODE_H265_BIT_KHR，则pQualityLevelProperties->pNext中必须包含一个VkVideoEncodeH265QualityLevelPropertiesKHR
			*/


			//VkVideoEncodeQualityLevelInfoKHR可以在 VkVideoSessionParametersCreateInfoKHR.pNext中包含 指定video session要使用的 video encode quality level或者 在VkVideoCodingControlInfoKHR.pNext中包含 来改变当前使用的video encode quality level
			VkVideoEncodeQualityLevelInfoKHR  videoEncodeQualityLevelInfoKHR{};
			videoEncodeQualityLevelInfoKHR.sType = VK_STRUCTURE_TYPE_MAX_ENUM;//没有定义这里设置为非法值
			videoEncodeQualityLevelInfoKHR.pNext = nullptr;
			videoEncodeQualityLevelInfoKHR.qualityLevel = 0;//使用的 video encode quality level，必须小于调用vkGetPhysicalDeviceVideoCapabilitiesKHR 传入对应的video profile返回的VkVideoEncodeCapabilitiesKHR::maxQualityLevels
		}


		//Retrieving Encoded Session Parameters  参见p3539
		{
			/*
			根据使用的压缩标准，存储在video session中的codec-specific parameters可能需要单独编码然后存放到最终的video bitstream data中，在这种情况下应用就需要先video session parameters 中获取编码的参数数据

			*/


			//从video session parameters 中获取编码的参数数据
			VkVideoEncodeSessionParametersGetInfoKHR videoEncodeSessionParametersGetInfoKHR{};
			videoEncodeSessionParametersGetInfoKHR.sType = VK_STRUCTURE_TYPE_MAX_ENUM;//没有定义这里定义为非法值
			videoEncodeSessionParametersGetInfoKHR.pNext = nullptr;//可能包含 VkVideoEncodeH264SessionParametersGetInfoKHR 或者VkVideoEncodeH265SessionParametersGetInfoKHR
			videoEncodeSessionParametersGetInfoKHR.videoSessionParameters = VkVideoSessionParametersKHR{/*假设这是一个有效的VkVideoSessionParametersKHR*/ };//指明要从哪个VkVideoSessionParametersKHR获取编码的参数

			VkVideoEncodeSessionParametersFeedbackInfoKHR videoEncodeSessionParametersFeedbackInfoKHR{};
			videoEncodeSessionParametersFeedbackInfoKHR.sType = VK_STRUCTURE_TYPE_MAX_ENUM;//没有定义这里定义为非法值
			videoEncodeSessionParametersFeedbackInfoKHR.pNext = nullptr;//可能包含VkVideoEncodeH264SessionParametersFeedbackInfoKHR 或者 VkVideoEncodeH265SessionParametersFeedbackInfoKHR
			videoEncodeSessionParametersFeedbackInfoKHR.hasOverrides = VK_FALSE;//指明请求的参数数据是否已经被复写修改过

			size_t encodedSize = 0;
			std::vector<char> encodedData;

			vkGetEncodedVideoSessionParametersKHR(device, &videoEncodeSessionParametersGetInfoKHR, &videoEncodeSessionParametersFeedbackInfoKHR, &encodedSize, nullptr);
			encodedData.resize(encodedSize);
			vkGetEncodedVideoSessionParametersKHR(device, &videoEncodeSessionParametersGetInfoKHR, &videoEncodeSessionParametersFeedbackInfoKHR, &encodedSize, encodedData.data());
			/*
			vkGetEncodedVideoSessionParametersKHR有效用法:
			1.pVideoSessionParametersInfo->videoSessionParameters 必须以一个encode operation 创建
			2.如果pVideoSessionParametersInfo->videoSessionParameters 以 video codec operation VK_VIDEO_CODEC_OPERATION_ENCODE_H264_BIT_KHR 创建，则（1）pVideoSessionParametersInfo.pNext中必须包含一个VkVideoEncodeH264SessionParametersGetInfoKHR
																																					（2）如果pVideoSessionParametersInfo.pNext中VkVideoEncodeH264SessionParametersGetInfoKHR.writeStdSPS为VK_TRUE，则pVideoSessionParametersInfo->videoSessionParameters中必须包含一个seq_parameter_set_id 匹配VkVideoEncodeH264SessionParametersGetInfoKHR::stdSPSId的 StdVideoH264SequenceParameterSet实体
																																					（3）如果pVideoSessionParametersInfo.pNext中VkVideoEncodeH264SessionParametersGetInfoKHR.writeStdPPS为VK_TRUE，则pVideoSessionParametersInfo->videoSessionParameters中必须包含一个seq_parameter_set_id 以及 pic_parameter_set_id 都各自匹配VkVideoEncodeH264SessionParametersGetInfoKHR::stdSPSId以及  VkVideoEncodeH264SessionParametersGetInfoKHR::stdPPSId的 StdVideoH264PictureParameterSet实体
			3.如果pVideoSessionParametersInfo->videoSessionParameters 以 video codec operation VK_VIDEO_CODEC_OPERATION_ENCODE_H265_BIT_KHR 创建，则（1）pVideoSessionParametersInfo.pNext中必须包含一个VkVideoEncodeH265SessionParametersGetInfoKHR
																																					（2）如果pVideoSessionParametersInfo.pNext中VkVideoEncodeH265SessionParametersGetInfoKHR.writeStdVPS为VK_TRUE，则pVideoSessionParametersInfo->videoSessionParameters中必须包含一个vps_video_parameter_set_id 匹配VkVideoEncodeH265SessionParametersGetInfoKHR::stdVPSId的 StdVideoH265VideoParameterSet实体
																																					（3）如果pVideoSessionParametersInfo.pNext中VkVideoEncodeH265SessionParametersGetInfoKHR.writeStdSPS为VK_TRUE，则pVideoSessionParametersInfo->videoSessionParameters中必须包含一个sps_video_parameter_set_id 以及 sps_seq_parameter_set_id 都各自匹配VkVideoEncodeH265SessionParametersGetInfoKHR::stdVPSId以及  VkVideoEncodeH265SessionParametersGetInfoKHR::stdSPSId的 StdVideoH265SequenceParameterSet实体
																																					（4）如果pVideoSessionParametersInfo.pNext中VkVideoEncodeH265SessionParametersGetInfoKHR.writeStdPPS为VK_TRUE，则pVideoSessionParametersInfo->videoSessionParameters中必须包含一个sps_video_parameter_set_id, pps_seq_parameter_set_id, 以及 pps_pic_parameter_set_id 都各自匹配VkVideoEncodeH265SessionParametersGetInfoKHR::stdVPSId,VkVideoEncodeH265SessionParametersGetInfoKHR::stdSPSId, 以及VkVideoEncodeH265SessionParametersGetInfoKHR::stdPPSId的 StdVideoH265PictureParameterSet实体
 
			*/


		}


		//Video Encode Commands  参见p3544
		{
			VkCommandBuffer commandBuffer{/*假设这是一个有效的VkCommandBuffer*/ };

			struct VideoEncodeInfoKHREXT {
				VkVideoEncodeH264PictureInfoKHR videoEncodeH264PictureInfoKHR{};
				VkVideoEncodeH265PictureInfoKHR videoEncodeH265PictureInfoKHR{};
				VkVideoInlineQueryInfoKHR videoInlineQueryInfoKHR{};
				VideoEncodeInfoKHREXT() {
					Init();
				}
				void Init() {
					videoEncodeH264PictureInfoKHR.sType = VK_STRUCTURE_TYPE_MAX_ENUM;//没有定义所以这里定义为非法值
					videoEncodeH264PictureInfoKHR.pNext = nullptr;
					videoEncodeH265PictureInfoKHR.sType = VK_STRUCTURE_TYPE_MAX_ENUM;//没有定义所以这里定义为非法值
					videoEncodeH265PictureInfoKHR.pNext = nullptr;
					videoInlineQueryInfoKHR.sType = VK_STRUCTURE_TYPE_MAX_ENUM;//没有定义所以这里定义为非法值
					videoInlineQueryInfoKHR.pNext = nullptr;
				}
			};

			//启动opCount个 video encode operations
			VkVideoEncodeInfoKHR videoEncodeInfoKHR{};
			videoEncodeInfoKHR.sType = VK_STRUCTURE_TYPE_MAX_ENUM;//没有定义所以这里定义为非法值
			VideoEncodeInfoKHREXT videoEncodeInfoKHREXT{};
			videoEncodeInfoKHR.pNext = &videoEncodeInfoKHREXT.videoEncodeH264PictureInfoKHR;
			videoEncodeInfoKHR.flags = VK_VIDEO_ENCODE_TUNING_MODE_DEFAULT_KHR;
			videoEncodeInfoKHR.dstBuffer = VkBuffer{/*假设这是一个有效的VkBuffer*/ };//为存放 encoded bitstream的 destination video bitstream buffer
			videoEncodeInfoKHR.dstBufferOffset = 0;//dstBuffer 中的起始字节偏移量
			videoEncodeInfoKHR.dstBufferRange = 4;//dstBuffer 中从dstBufferOffset开始的可以存放的bitstream的最大字节数
			VkVideoPictureResourceInfoKHR srcPictureResource{};
			{
				srcPictureResource.sType = VK_STRUCTURE_TYPE_VIDEO_PICTURE_RESOURCE_INFO_KHR;
				srcPictureResource.pNext = nullptr;
				srcPictureResource.baseArrayLayer = 0;
				srcPictureResource.codedExtent = VkExtent2D{ .width = 1,.height = 1 };
				srcPictureResource.codedOffset = VkOffset2D{ .x = 0,.y = 0 };
				srcPictureResource.imageViewBinding = VkImageView{/*假设这是一个有效的VkImageView*/ };
			}
			videoEncodeInfoKHR.srcPictureResource = srcPictureResource;//指明用于Encode Input Picture的video picture resource
			VkVideoReferenceSlotInfoKHR videoReferenceSlotInfoKHR{};
			{
				videoReferenceSlotInfoKHR.sType = VK_STRUCTURE_TYPE_VIDEO_REFERENCE_SLOT_INFO_KHR;
				videoReferenceSlotInfoKHR.pNext = nullptr;
				videoReferenceSlotInfoKHR.slotIndex = 0;
				VkVideoPictureResourceInfoKHR testPictureResource{/*假设这是一个有效的VkVideoPictureResourceInfoKHR*/ };
				videoReferenceSlotInfoKHR.pPictureResource = &testPictureResource;

			}
			videoEncodeInfoKHR.pSetupReferenceSlot = &videoReferenceSlotInfoKHR;//为NULL或者VkVideoReferenceSlotInfoKHR 指针， 指明可选的Reconstructed Picture 信息
			videoEncodeInfoKHR.referenceSlotCount = 1;// pReferenceSlots 中元素个数
			videoEncodeInfoKHR.pReferenceSlots = &videoReferenceSlotInfoKHR;//为NULL或者VkVideoReferenceSlotInfoKHR 数组指针，描述用于video encode operation 的DPB slots 以及对应的 reference picture （激活的Reference Picture 组）
			videoEncodeInfoKHR.precedingExternallyEncodedBytes = 0;//为应用外部编码到 video bitstream的字节数，用于更新实现的速率控制算法的内部状态，以考虑这些外部编码的字节所消耗的比特率预算。
			/*
			VkVideoEncodeInfoKHR有效用法:
			1.dstBuffer 必须以VK_BUFFER_USAGE_VIDEO_DECODE_DST_BIT_KHR 标记创建
			2.dstBufferOffset 必须小于dstBuffer的大小
			3.dstBufferRange 必须小于等于dstBuffer的大小 减去dstBufferOffset
			4.如果pSetupReferenceSlot 不为NULL，则其slotIndex 不能为负数，其pPictureResource 不能为NULL
			5.pReferenceSlots 中每个元素的slotIndex 不能为负数，pPictureResource 不能为NULL

			*/


			//该接口的其他注意信息以及使用时一些参数的限制信息见 *** p3544- p3547
			vkCmdEncodeVideoKHR(commandBuffer, &videoEncodeInfoKHR);
			/*
			vkCmdEncodeVideoKHR有效用法:
			1.绑定的video session 必须以一个 encode operation 创建，且在该命令在设备上执行的时候video session 不能为非初始化的状态
			2.该命令在设备上执行的时候，绑定的video session parameters 必须以当前绑定的video session设置的video encode quality level 创建
			3.对每个激活的query，对应query type的激活的query 索引加上 opCount 必须小于等于该query type的最后一个激活的query 索引加1
			4.如果绑定的video session 以VK_VIDEO_SESSION_CREATE_INLINE_QUERIES_BIT_KHR 创建，且pEncodeInfo->pNext中包含一个queryPool 指定一个有效的VkQueryPool的VkVideoInlineQueryInfoKHR，则（1）VkVideoInlineQueryInfoKHR::queryCount 必须等于opCount
																																															 （2）所有该命令使用的VkVideoInlineQueryInfoKHR中的query必须为unavailable的状态
																																															 （3）则用于创建VkVideoInlineQueryInfoKHR.queryPool的 queryType 必须为VK_QUERY_TYPE_RESULT_STATUS_ONLY_KHR 或者VK_QUERY_TYPE_VIDEO_ENCODE_FEEDBACK_KHR
																																															 （4）VkVideoInlineQueryInfoKHR.queryPool 必须要以VkQueryPoolCreateInfo.pNext中包含一个和video session创建时VkVideoSessionCreateInfoKHR::pVideoProfile 中一个元素相等的VkVideoProfileInfoKHR 创建
																																															 （5）如果用于创建VkVideoInlineQueryInfoKHR.queryPool的 queryType 为VK_QUERY_TYPE_RESULT_STATUS_ONLY_KHR，则commandBuffer所在的VkCommandPool的队列族必须支持result status queries，见队列族的VkQueueFamilyQueryResultStatusPropertiesKHR::queryResultStatusSupport
			5.pEncodeInfo->dstBuffer 必须兼容于绑定的video session 创建时使用的video profile
			6.如果commandBuffer是unprotected command buffer 且protectedNoFault不支持，则pEncodeInfo->dstBuffer 不能是protected buffer
			7.如果commandBuffer是protected command buffer 且protectedNoFault不支持，则pEncodeInfo->dstBuffer 必须是protected buffer
			8.pEncodeInfo->dstBufferOffset 必须是调用vkGetPhysicalDeviceVideoCapabilitiesKHR传入绑定video session创建时的video profile返回的VkVideoCapabilitiesKHR::minBitstreamBufferOffsetAlignment的整数倍
			9.pEncodeInfo->dstBufferRange 必须是调用vkGetPhysicalDeviceVideoCapabilitiesKHR传入绑定video session创建时的video profile返回的VkVideoCapabilitiesKHR::minBitstreamBufferSizeAlignment的整数倍
			10.pEncodeInfo->srcPictureResource.imageViewBinding 必须兼容绑定的video session创建时的video profile
			11.pEncodeInfo->srcPictureResource.imageViewBinding 的format必须匹配创建video session时使用的VkVideoSessionCreateInfoKHR::pictureFormat
			12.pEncodeInfo->srcPictureResource.codedOffset 必须是codedOffsetGranularity 的整数倍
			13.pEncodeInfo->srcPictureResource.codedExtent 必须在创建video session 时使用的VkVideoSessionCreateInfoKHR::minCodedExtent 和 VkVideoSessionCreateInfoKHR::maxCodedExtent 之间
			14.pEncodeInfo->srcPictureResource.imageViewBinding 必须以VK_IMAGE_USAGE_VIDEO_ENCODE_SRC_BIT_KHR 创建
			15.如果commandBuffer是unprotected command buffer 且protectedNoFault不支持，则pEncodeInfo->srcPictureResource.imageViewBinding 不能从protected image 上创建
			16.如果commandBuffer是protected command buffer 且protectedNoFault不支持，则pEncodeInfo->srcPictureResource.imageViewBinding 必须从protected image 上创建
			17.pEncodeInfo->pSetupReferenceSlot 必须不为NULL除非绑定的video session 被创建时指定了VkVideoSessionCreateInfoKHR::maxDpbSlots 为0
			18.如果 pEncodeInfo->pSetupReferenceSlot 不为NULL，则（1）pEncodeInfo->pSetupReferenceSlot->slotIndex 必须小于等于创建video session 时 VkVideoSessionCreateInfoKHR::maxDpbSlots 指定的最大DPB槽数量
																 （2）pEncodeInfo->pSetupReferenceSlot->pPictureResource->codedOffset 必须为codedOffsetGranularity 的整数倍
																 （3）pEncodeInfo->pSetupReferenceSlot->pPictureResource 必须匹配一个绑定的reference picture resource

			19.activeReferencePictureCount 必须小于等于创建video session 时指定的 VkVideoSessionCreateInfoKHR::maxActiveReferencePictures
			20.pEncodeInfo->pReferenceSlots 中每个元素的slotIndex 必须小于等于创建video session 时 VkVideoSessionCreateInfoKHR::maxDpbSlots 指定的最大DPB槽数量
			21.每个pEncodeInfo->pReferenceSlots 元素的pPictureResource 所指的VkVideoPictureResourceInfoKHR::codedOffset 必须为codedOffsetGranularity 的整数倍
			22.每个pEncodeInfo->pReferenceSlots 元素的pPictureResource 必须匹配一个绑定的关联到其slotIndex指定的DPB slot 索引上的reference picture resource
			23.每个pEncodeInfo->pReferenceSlots 元素的pPictureResource 所指的video picture resource 必须在pEncodeInfo->pReferenceSlots 中是唯一的
			24.dpbFrameUseCount中所有元素必须小于等于1 （这个量是隐含的，通过计算出来的，具体见p3545）
			25.pEncodeInfo->pReferenceSlots 中每个元素的pPictureResource 引用的image subresource 在该命令在设备上执行时layout必须为 VK_IMAGE_LAYOUT_VIDEO_ENCODE_SRC_KHR
			26.如果pEncodeInfo->pSetupReferenceSlot 不为NULL，则pEncodeInfo->pSetupReferenceSlot->pPictureResource 所指的image subresource 在该命令在设备上执行时layout必须为 VK_IMAGE_LAYOUT_VIDEO_ENCODE_DPB_KHR
			27.pEncodeInfo->pReferenceSlots->pPictureResource 所指的image subresource 在该命令在设备上执行时layout必须为 VK_IMAGE_LAYOUT_VIDEO_ENCODE_DPB_KHR
			28.如果绑定的video session 以video codec operation 为 VK_VIDEO_CODEC_OPERATION_ENCODE_H264_BIT_KHR 创建，则	（1）pEncodeInfo->pNext中必须包含一个VkVideoEncodeH264PictureInfoKHR结构
																														（2）绑定的video session parameters 必须包含seq_parameter_set_id 匹配pEncodeInfo->pNext中VkVideoEncodeH264PictureInfoKHR::pStdPictureInfo 中元素的StdVideoEncodeH264PictureInfo::seq_parameter_set_id的 StdVideoH264SequenceParameterSet 实体
																														（3）绑定的video session parameters 必须包含seq_parameter_set_id 以及pic_parameter_set_id 匹配pEncodeInfo->pNext中VkVideoEncodeH264PictureInfoKHR::pStdPictureInfo 中元素的 StdVideoEncodeH264PictureInfo::seq_parameter_set_id 以及StdVideoEncodeH264PictureInfo::pic_parameter_set_id 的 StdVideoH264PictureParameterSet 实体
																														（4）如果pEncodeInfo->pSetupReferenceSlot 不为NULL，则pEncodeInfo->pSetupReferenceSlot->pNext中必须包含一个VkVideoEncodeH264DpbSlotInfoKHR
																														（5）则pEncodeInfo->pReferenceSlots中每个元素的pNext中必须包含一个VkVideoEncodeH264DpbSlotInfoKHR
																														（6）且当前的rate control mode为VK_VIDEO_ENCODE_RATE_CONTROL_MODE_DISABLED_BIT_KHR，则对包含在pEncodeInfo->pNext中的VkVideoEncodeH264PictureInfoKHR.pNaluSliceEntries中的所有元素 VkVideoEncodeH264NaluSliceInfoKHR::constantQp 必须为0
																														（7）且当前的rate control mode为VK_VIDEO_ENCODE_RATE_CONTROL_MODE_DISABLED_BIT_KHR，则对包含在pEncodeInfo->pNext中的VkVideoEncodeH264PictureInfoKHR.pNaluSliceEntries中的所有元素 VkVideoEncodeH264NaluSliceInfoKHR::constantQp 必须为 在VkVideoEncodeH264CapabilitiesKHR::minQp 到VkVideoEncodeH264CapabilitiesKHR::maxQp之间（通过vkGetPhysicalDeviceVideoCapabilitiesKHR传入video session创建时的video profile返回）
																														（8）如果通过vkGetPhysicalDeviceVideoCapabilitiesKHR传入video session创建时的video profile返回的VkVideoEncodeH264CapabilitiesKHR::flags 不包含VK_VIDEO_ENCODE_H264_CAPABILITY_PER_SLICE_CONSTANT_QP_BIT_KHR，则对包含在pEncodeInfo->pNext中的VkVideoEncodeH264PictureInfoKHR.pNaluSliceEntries中的所有元素 VkVideoEncodeH264NaluSliceInfoKHR::constantQp 值必须相同
																														（9）则对包含在pEncodeInfo->pNext中的VkVideoEncodeH264PictureInfoKHR.naluSliceEntryCount 必须小于等于minCodingBlockExtent.width * minCodingBlockExtent.height （minCodingBlockExtent是计算出来的，具体计算见p3546）
																														（10）如果通过vkGetPhysicalDeviceVideoCapabilitiesKHR传入video session创建时的video profile返回的VkVideoEncodeH264CapabilitiesKHR::flags 不包含VK_VIDEO_ENCODE_H264_CAPABILITY_ROW_UNALIGNED_SLICE_BIT_KHR，则对包含在pEncodeInfo->pNext中的VkVideoEncodeH264PictureInfoKHR.naluSliceEntryCount 必须小于等于minCodingBlockExtent.height  （minCodingBlockExtent是计算出来的，具体计算见p3546）
																														（11）且pEncodeInfo->pNext 包含VkVideoEncodeH264PictureInfoKHR，且pEncodeInfo->referenceSlotCount 大于0，则VkVideoEncodeH264PictureInfoKHR::pStdPictureInfo->pRefLists 必须不为NULL
																														（12）且pEncodeInfo->pNext 包含VkVideoEncodeH264PictureInfoKHR，且VkVideoEncodeH264PictureInfoKHR::pStdPictureInfo->pRefLists 不为NULL，则VkVideoEncodeH264PictureInfoKHR::pStdPictureInfo->pRefLists中每个元素StdVideoEncodeH264ReferenceListsInfo的RefPicList0 以及RefPicList1 中的每个元素必须为STD_VIDEO_H264_NO_REFERENCE_PICTURE 或者为pEncodeInfo->pReferenceSlots中的一个元素的slotIndex
																														（13）且pEncodeInfo->pNext 包含VkVideoEncodeH264PictureInfoKHR，且pEncodeInfo->referenceSlotCount 大于0，则pEncodeInfo->pReferenceSlots中的每个元素的slotIndex 必须等于VkVideoEncodeH264PictureInfoKHR::pStdPictureInfo->pRefLists中一个元素StdVideoEncodeH264ReferenceListsInfo的RefPicList0 或者RefPicList1 中的一个元素
																														（14）如果通过vkGetPhysicalDeviceVideoCapabilitiesKHR传入video session创建时的video profile返回的VkVideoEncodeH264CapabilitiesKHR::maxPPictureL0ReferenceCount 为0，则h264L0PictureTypes 以及h264L1PictureTypes 中的每个元素h264PictureType 不能为STD_VIDEO_H264_PICTURE_TYPE_P （h264L0PictureTypes以及h264L1PictureTypes是一个计算出来的数组，具体计算见p3546）
																														（15）如果通过vkGetPhysicalDeviceVideoCapabilitiesKHR传入video session创建时的video profile返回的VkVideoEncodeH264CapabilitiesKHR::maxBPictureL0ReferenceCount 以及VkVideoEncodeH264CapabilitiesKHR::maxL1ReferenceCount 都为0，则h264L0PictureTypes 以及h264L1PictureTypes 中的每个元素h264PictureType 不能为STD_VIDEO_H264_PICTURE_TYPE_B （h264L0PictureTypes以及h264L1PictureTypes是一个计算出来的数组，具体计算见p3546）
																														（16）如果通过vkGetPhysicalDeviceVideoCapabilitiesKHR传入video session创建时的video profile返回的VkVideoEncodeH264CapabilitiesKHR::flags 不包含VK_VIDEO_ENCODE_H264_CAPABILITY_B_FRAME_IN_L0_LIST_BIT_KHR， 则h264L0PictureTypes 中每个元素不能为 STD_VIDEO_H264_PICTURE_TYPE_B （h264L0PictureTypes是一个计算出来的数组，具体计算见p3546）
																														（17）如果通过vkGetPhysicalDeviceVideoCapabilitiesKHR传入video session创建时的video profile返回的VkVideoEncodeH264CapabilitiesKHR::flags 不包含VK_VIDEO_ENCODE_H264_CAPABILITY_B_FRAME_IN_L1_LIST_BIT_KHR， 则h264L1PictureTypes 中每个元素不能为 STD_VIDEO_H264_PICTURE_TYPE_B （h264L1PictureTypes是一个计算出来的数组，具体计算见p3546）



			29.如果绑定的video session 以video codec operation 为 VK_VIDEO_CODEC_OPERATION_ENCODE_H265_BIT_KHR 创建，则（1）pDecodeInfo->pNext中必须包含一个VkVideoEncodeH265PictureInfoKHR结构
																													   （2）绑定的video session parameters 必须包含vps_video_parameter_set_id 匹配pEncodeInfo->pNext中VkVideoEncodeH265PictureInfoKHR::pStdPictureInfo 中元素的StdVideoEncodeH265PictureInfo::sps_video_parameter_set_id的 StdVideoH265VideoParameterSet 实体
																													   （3）绑定的video session parameters 必须包含sps_video_parameter_set_id 以及 sps_seq_parameter_set_id 匹配pEncodeInfo->pNext中VkVideoEncodeH265PictureInfoKHR::pStdPictureInfo 中元素的StdVideoEncodeH265PictureInfo::sps_video_parameter_set_id 以及 StdVideoEncodeH265PictureInfo::pps_seq_parameter_set_id 的 StdVideoH265SequenceParameterSet 实体
																													   （4）绑定的video session parameters 必须包含sps_video_parameter_set_id, pps_seq_parameter_set_id, 以及 pps_pic_parameter_set_id 都匹配pEncodeInfo->pNext中VkVideoEncodeH265PictureInfoKHR::pStdPictureInfo 中元素的StdVideoEncodeH265PictureInfo::sps_video_parameter_set_id, StdVideoEncodeH265PictureInfo::pps_seq_parameter_set_id, 以及 StdVideoEncodeH265PictureInfo::pps_pic_parameter_set_id 的 StdVideoH265PictureParameterSet 实体
																													   （5）如果pEncodeInfo->pSetupReferenceSlot 不为NULL，则pEncodeInfo->pSetupReferenceSlot->pNext中必须包含一个VkVideoEncodeH265DpbSlotInfoKHR
																													   （6）则pEncodeInfo->pReferenceSlots中每个元素的pNext中必须包含一个VkVideoEncodeH265DpbSlotInfoKHR
																													   （7）且当前的rate control mode为VK_VIDEO_ENCODE_RATE_CONTROL_MODE_DISABLED_BIT_KHR，则对包含在pEncodeInfo->pNext中的VkVideoEncodeH265PictureInfoKHR.pNaluSliceSegmentEntries中的所有元素 VkVideoEncodeH265NaluSliceSegmentInfoKHR::constantQp 必须为0
																													   （8）且当前的rate control mode为VK_VIDEO_ENCODE_RATE_CONTROL_MODE_DISABLED_BIT_KHR，则对包含在pEncodeInfo->pNext中的VkVideoEncodeH265PictureInfoKHR.pNaluSliceSegmentEntries中的所有元素 VkVideoEncodeH265NaluSliceSegmentInfoKHR::constantQp 必须为 在VkVideoEncodeH265CapabilitiesKHR::minQp 到VkVideoEncodeH265CapabilitiesKHR::maxQp之间（通过vkGetPhysicalDeviceVideoCapabilitiesKHR传入video session创建时的video profile返回）
																													   （9）如果通过vkGetPhysicalDeviceVideoCapabilitiesKHR传入video session创建时的video profile返回的VkVideoEncodeH265CapabilitiesKHR::flags 不包含VK_VIDEO_ENCODE_H265_CAPABILITY_PER_SLICE_SEGMENT_CONSTANT_QP_BIT_KHR，则对包含在pEncodeInfo->pNext中的VkVideoEncodeH265PictureInfoKHR.pNaluSliceSegmentEntries中的所有元素 VkVideoEncodeH265NaluSliceSegmentInfoKHR::constantQp 值必须相同
																													   （10）则对包含在pEncodeInfo->pNext中的VkVideoEncodeH265PictureInfoKHR.naluSliceSegmentEntryCount 必须小于等于minCodingBlockExtent.width * minCodingBlockExtent.height （minCodingBlockExtent是计算出来的，具体计算见p3546）
																													   （11）如果通过vkGetPhysicalDeviceVideoCapabilitiesKHR传入video session创建时的video profile返回的VkVideoEncodeH265CapabilitiesKHR::flags 不包含VK_VIDEO_ENCODE_H265_CAPABILITY_ROW_UNALIGNED_SLICE_SEGMENT_BIT_KHR，则对包含在pEncodeInfo->pNext中的VkVideoEncodeH265PictureInfoKHR.naluSliceSegmentEntryCount 必须小于等于minCodingBlockExtent.height  （minCodingBlockExtent是计算出来的，具体计算见p3546）
																													   （12）且pEncodeInfo->pNext 包含VkVideoEncodeH265PictureInfoKHR，且pEncodeInfo->referenceSlotCount 大于0，则VkVideoEncodeH265PictureInfoKHR::pStdPictureInfo->pRefLists 必须不为NULL
																													   （13）且pEncodeInfo->pNext 包含VkVideoEncodeH265PictureInfoKHR，且VkVideoEncodeH265PictureInfoKHR::pStdPictureInfo->pRefLists 不为NULL，则VkVideoEncodeH265PictureInfoKHR::pStdPictureInfo->pRefLists中每个元素StdVideoEncodeH265ReferenceListsInfo的RefPicList0 以及RefPicList1 中的每个元素必须为STD_VIDEO_H265_NO_REFERENCE_PICTURE 或者为pEncodeInfo->pReferenceSlots中的一个元素的slotIndex
																													   （14）且pEncodeInfo->pNext 包含VkVideoEncodeH265PictureInfoKHR，且pEncodeInfo->referenceSlotCount 大于0，则pEncodeInfo->pReferenceSlots中的每个元素的slotIndex 必须等于VkVideoEncodeH265PictureInfoKHR::pStdPictureInfo->pRefLists中一个元素StdVideoEncodeH265ReferenceListsInfo的RefPicList0 或者RefPicList1 中的一个元素
																													   （15）如果通过vkGetPhysicalDeviceVideoCapabilitiesKHR传入video session创建时的video profile返回的VkVideoEncodeH265CapabilitiesKHR::maxPPictureL0ReferenceCount 为0，则h265L0PictureTypes 以及h265L1PictureTypes 中的每个元素h265PictureType 不能为STD_VIDEO_H265_PICTURE_TYPE_P （h265L0PictureTypes以及h265L1PictureTypes是一个计算出来的数组，具体计算见p3547）
																													   （16）如果通过vkGetPhysicalDeviceVideoCapabilitiesKHR传入video session创建时的video profile返回的VkVideoEncodeH265CapabilitiesKHR::maxBPictureL0ReferenceCount 以及VkVideoEncodeH265CapabilitiesKHR::maxL1ReferenceCount 都为0，则h265L0PictureTypes 以及h265L1PictureTypes 中的每个元素h265PictureType 不能为STD_VIDEO_H265_PICTURE_TYPE_B （h265L0PictureTypes以及h265L1PictureTypes是一个计算出来的数组，具体计算见p3547）
																													   （17）如果通过vkGetPhysicalDeviceVideoCapabilitiesKHR传入video session创建时的video profile返回的VkVideoEncodeH265CapabilitiesKHR::flags 不包含VK_VIDEO_ENCODE_H265_CAPABILITY_B_FRAME_IN_L0_LIST_BIT_KHR， 则h265L0PictureTypes 中每个元素不能为 STD_VIDEO_H265_PICTURE_TYPE_B （h265L0PictureTypes是一个计算出来的数组，具体计算见p3547）
																													   （18）如果通过vkGetPhysicalDeviceVideoCapabilitiesKHR传入video session创建时的video profile返回的VkVideoEncodeH265CapabilitiesKHR::flags 不包含VK_VIDEO_ENCODE_H265_CAPABILITY_B_FRAME_IN_L1_LIST_BIT_KHR， 则h265L1PictureTypes 中每个元素不能为 STD_VIDEO_H265_PICTURE_TYPE_B （h265L1PictureTypes是一个计算出来的数组，具体计算见p3547）

			*/

		}

	}

	//Video Encode Rate Control  参见p3559
	{}
	{
		/*
		video coding 使用 bitrate 来衡量每秒编码的video bitstream data的大小，且为 encoded bitstream data 大小和使用 frame rate的函数。

		速率控制算法可以在video encode operations 中用来调节bitrate的大小。

		*/


		// Rate Control Modes  参见p3560
		{
			/*
			当重置了video session后是无法控制速率的，只有在改变了video session的速率配置后才可以。

			速率控制有两类：
				> Per-operation rate control  - 针对每个video encode operation ,速率间接受大小，质量或者其他encoding参数控制
				> Stream-level rate control  -  在多个video encode operations 中直接指定速率，而不受encoding参数的控制
			*/

			//VkVideoEncodeRateControlModeFlagBitsKHR 速率控制模式
			VkVideoEncodeRateControlModeFlagBitsKHR rateControlMode = VK_VIDEO_ENCODE_RATE_CONTROL_MODE_CBR_BIT_KHR;
			/*
			VkVideoEncodeRateControlModeFlagBitsKHR:
			VK_VIDEO_ENCODE_RATE_CONTROL_MODE_DEFAULT_KHR : 指定使用implementation-specific 速率控制
			VK_VIDEO_ENCODE_RATE_CONTROL_MODE_DISABLED_BIT_KHR : 速率控制被禁用，应用将指定每个操作的速率控制参数来控制编码质量，在这种模式下，编码pictures将使用的速率和之前的编码操作的速率独立。根据具体类型将分别使用VkVideoEncodeH264NaluSliceInfoKHR::constantQp 或者VkVideoEncodeH265NaluSliceSegmentInfoKHR::constantQp 来控制编码质量
			VK_VIDEO_ENCODE_RATE_CONTROL_MODE_CBR_BIT_KHR : 指定使用constant bitrate (CBR) 速率控制，在这种模式下实现将在服从其他速率参数限制的情况下尝试使用固定常量的速率来产生编码的bitstream
			VK_VIDEO_ENCODE_RATE_CONTROL_MODE_VBR_BIT_KHR : 指定使用variable bitrate (VBR) 速率控制，在这种模式下实现将在服从其他速率参数限制的情况下尝试使用可变的速率来产生编码的bitstream。

			*/
		}


		//Leaky Bucket Model   leaky bucket model 用于 stream-level rate control，简单将就是相当于在video encoder 以及decoder 之间加入了一个接口，编码的数据会不断通过这个接口让decoder获取然后处理，这可以有效避免两者处理速率不匹配时产生的 underflow 以及overflow，其他详细描述见p3561。


		//Rate Control Layers  参见p3562   简单将就是一些标准允许将encoded pictures关联到指定的video coding layers，这样stream-level rate control就可以使用一个或者多个 rate control layers 来进行配置

		//Rate Control State  参见p3562
		{
			/*
			rate control state 在video session中维护，其参数通过VkVideoEncodeRateControlInfoKHR 来指定。主要指定rate control state 以及 rate control layers， 具体如何指定见p3562
			*/


			//在VkVideoBeginCodingInfoKHR.pNext中或者  VkVideoCodingControlInfoKHR.pNext中包含VkVideoEncodeRateControlInfoKHR 来配置或者更新编码速率控制配置
			VkVideoEncodeRateControlInfoKHR videoEncodeRateControlInfoKHR{};
			videoEncodeRateControlInfoKHR.sType = VK_STRUCTURE_TYPE_MAX_ENUM;//没有指定这里设置为非法值
			videoEncodeRateControlInfoKHR.pNext = nullptr;
			videoEncodeRateControlInfoKHR.flags = 0;//保留未来使用
			videoEncodeRateControlInfoKHR.rateControlMode = VK_VIDEO_ENCODE_RATE_CONTROL_MODE_CBR_BIT_KHR;//一个 VkVideoEncodeRateControlModeFlagBitsKHR 值指明 rate control mode
			videoEncodeRateControlInfoKHR.layerCount = 1;//pLayers 中元素个数
			VkVideoEncodeRateControlLayerInfoKHR videoEncodeRateControlLayerInfoKHR{};//指定每个单独的rate control layer的配置
			{
				videoEncodeRateControlLayerInfoKHR.sType = VK_STRUCTURE_TYPE_MAX_ENUM;//没有定义这里定义为非法值
				videoEncodeRateControlLayerInfoKHR.pNext = nullptr;//可以包含 VkVideoEncodeH264RateControlLayerInfoKHR 或者VkVideoEncodeH265RateControlLayerInfoKHR
				videoEncodeRateControlLayerInfoKHR.averageBitrate = 256;//为实现的速率控制算法指定的平均bitrate
				videoEncodeRateControlLayerInfoKHR.maxBitrate = 256;//为实现的速率控制算法指定的峰值bitrate
				videoEncodeRateControlLayerInfoKHR.frameRateNumerator = 1;//为实现的速率控制算法估定的frame rate的分子，必须大于0
				videoEncodeRateControlLayerInfoKHR.frameRateDenominator = 1;///为实现的速率控制算法估定的frame rate的分母，必须大于0
				videoEncodeRateControlLayerInfoKHR.virtualBufferSizeInMs = 256;//为毫秒内对 leaky bucket model的速率控制算法使用的virtual buffer的大小
				videoEncodeRateControlLayerInfoKHR.initialVirtualBufferSizeInMs = 256;//为毫秒内对 leaky bucket model的速率控制算法使用的virtual buffer的初始容量
			}
			videoEncodeRateControlInfoKHR.pLayers = &videoEncodeRateControlLayerInfoKHR;//一组VkVideoEncodeRateControlLayerInfoKHR 数组指针，指明各个rate control layer的速率控制配置
			/*
			VkVideoEncodeRateControlInfoKHR有效用法:
			1.如果rateControlMode 为VK_VIDEO_ENCODE_RATE_CONTROL_MODE_DEFAULT_KHR 或者VK_VIDEO_ENCODE_RATE_CONTROL_MODE_DISABLED_BIT_KHR，则layerCount 必须为0
			2.如果rateControlMode 为VK_VIDEO_ENCODE_RATE_CONTROL_MODE_CBR_BIT_KHR 或者VK_VIDEO_ENCODE_RATE_CONTROL_MODE_VBR_BIT_KHR，则layerCount 必须大于0
			3.如果rateControlMode 不为VK_VIDEO_ENCODE_RATE_CONTROL_MODE_DEFAULT_KHR，则其必须指定一个包含在调用vkGetPhysicalDeviceVideoCapabilitiesKHR传入使用的video profile 返回的VkVideoEncodeCapabilitiesKHR::rateControlModes中的一个比特设置
			4.layerCount 必须小于等于调用vkGetPhysicalDeviceVideoCapabilitiesKHR传入使用的video profile 返回的VkVideoEncodeCapabilitiesKHR::maxRateControlLayers
			5.对pLayers 中的每个元素，其averageBitrate 成员必须在1到调用vkGetPhysicalDeviceVideoCapabilitiesKHR传入使用的video profile 返回的VkVideoEncodeCapabilitiesKHR::maxBitrate 给出
			6.对pLayers 中的每个元素，其maxBitrate 成员必须在1到调用vkGetPhysicalDeviceVideoCapabilitiesKHR传入使用的video profile 返回的VkVideoEncodeCapabilitiesKHR::maxBitrate 给出
			7.如果rateControlMode 为VK_VIDEO_ENCODE_RATE_CONTROL_MODE_CBR_BIT_KHR，则对pLayers 中的每个元素，其averageBitrate 成员必须等于其 maxBitrate 成员
			8.如果rateControlMode 为VK_VIDEO_ENCODE_RATE_CONTROL_MODE_VBR_BIT_KHR，则对pLayers 中的每个元素，其averageBitrate 成员必须小于或等于其 maxBitrate 成员
			9.如果layerCount 不为0，则virtualBufferSizeInMs 必须大于0
			10.如果layerCount 不为0，则initialVirtualBufferSizeInMs 必须小于 virtualBufferSizeInMs
			11.如果使用的video profile的videoCodecOperation 为VK_VIDEO_CODEC_OPERATION_ENCODE_H264_BIT_KHR，且pNext包含一个VkVideoEncodeH264RateControlInfoKHR结构体，且layerCount 大于1 ，则layerCount必须等于VkVideoEncodeH264RateControlInfoKHR::temporalLayerCount
			12.如果使用的video profile的videoCodecOperation 为VK_VIDEO_CODEC_OPERATION_ENCODE_H265_BIT_KHR，且pNext包含一个VkVideoEncodeH265RateControlInfoKHR结构体，且layerCount 大于1 ，则layerCount必须等于VkVideoEncodeH265RateControlInfoKHR::subLayerCount
			*/


		}

	}


	// H.264 Encode Operations  参见p3568
	{
		/*
		video encode operations 使用一个 H.264 encode profile 来将符合ITU-T H.264 Specification 描述的video stream进行编码
		
		操作中处理的一些数据结构会对应到ITU-T H.264 Specification 中的对应对象:
			 StdVideoH264SequenceParameterSet ->  H.264 sequence parameter set
			 StdVideoH264PictureParameterSet  ->   H.264 picture parameter set
			 StdVideoEncodeH264PictureInfo   ->    H.264 picture information
			 StdVideoEncodeH264SliceHeader  ->   H.264 slice header parameters 
			 StdVideoEncodeH264ReferenceInfo ->   H.264 reference information
		*/


		//H.264 Encode Parameter Overrides  参见p3568
		{
			/*
			实现可能复写以下参数:
				> StdVideoH264SequenceParameterSet
				> StdVideoH264PictureParameterSet
				> StdVideoEncodeH264PictureInfo
				> StdVideoEncodeH264SliceHeader
				> StdVideoEncodeH264ReferenceInfo
			但不能复写:
                > StdVideoEncodeH264PictureInfo::primary_pic_type
                > StdVideoEncodeH264SliceHeader::slice_type

			如果实现复写了这些参数，则可以通过vkGetEncodedVideoSessionParametersKHR 来确定是否复写了。
			*/
		}


		//H.264 Encode Bitstream Data Access  主要描述video bitstream buffer中存储的数据格式，  其他详细信息参见p3569 ***

		//H.264 Encode Picture Data Access  主要描述如何访问video picture resource中的image 数据， 其他详细信息参见p3569  ***


		// H.264 Frame, Picture, and Slice   主要描述H.264 pictures在编码操作中被划分为slices，每个slice可以使用不同的类型进行编码，而根据这些slice重建的constructed pictures也有不同的类型，      具体参见p3570  
		

		// H.264 Encode Profile 参见p3571
		{
			/*
			video profile 支持H.264 video encode operations 需要将VkVideoProfileInfoKHR::videoCodecOperation 设置为VK_VIDEO_CODEC_OPERATION_ENCODE_H264_BIT_KHR ，且在 VkVideoProfileInfoKHR::pNext 中添加一个VkVideoEncodeH264ProfileInfoKHR
			*/

			VkVideoEncodeH264ProfileInfoKHR videoEncodeH264ProfileInfoKHR{};
			videoEncodeH264ProfileInfoKHR.sType = VK_STRUCTURE_TYPE_MAX_ENUM;//没有定义这里设置为非法值
			videoEncodeH264ProfileInfoKHR.pNext = nullptr;
			videoEncodeH264ProfileInfoKHR.stdProfileIdc = STD_VIDEO_H264_PROFILE_IDC_BASELINE;//一个StdVideoH264ProfileIdc 值，指明H.264 codec profile IDC（定义在 ITU-T H.264 Specification的 A.2节）


		}


		//H.264 Encode Capabilities  参见p3571
		{
			/*
			当调用 vkGetPhysicalDeviceVideoCapabilitiesKHR 查询 H.264 encode profile能力时,需要在VkVideoCapabilitiesKHR::pNext 中添加一个VkVideoEncodeH264CapabilitiesKHR来返回profile-specific 能力

			*/

			VkVideoEncodeH264CapabilitiesKHR videoEncodeH264CapabilitiesKHR{};
			videoEncodeH264CapabilitiesKHR.sType = VK_STRUCTURE_TYPE_MAX_ENUM;//没有定义，这里定义为非法值
			videoEncodeH264CapabilitiesKHR.pNext = nullptr;
			videoEncodeH264CapabilitiesKHR.flags = 0;/* VkVideoEncodeH264CapabilityFlagBitsKHR 组合值位掩码，指明支持的H.264 编码能力	
			VkVideoEncodeH264CapabilityFlagBitsKHR:
			VK_VIDEO_ENCODE_H264_CAPABILITY_HRD_COMPLIANCE_BIT_KHR : 指明如果任何active SPS的StdVideoH264SpsVuiFlags的nal_hrd_parameters_present_flag 或者 vcl_hrd_parameters_present_flag设置为1， 实现是否可以生成HRD相符的bitstreams
			VK_VIDEO_ENCODE_H264_CAPABILITY_PREDICTION_WEIGHT_TABLE_GENERATED_BIT_KHR  : 指明当编码一个P picture或者 B picture ，如果各自active SPS的StdVideoH264PpsFlags::weighted_pred_flag 设置为1或者 StdVideoH264PictureParameterSet::weighted_bipred_idc 设置为STD_VIDEO_H264_WEIGHTED_BIPRED_IDC_EXPLICIT，则实现能够内部决定pred_weight_table的syntax（定义在ITU-T H.264 Specification的7.4.3.2 节），且应用不需要在H.264 sliceheader parameters 中提供一个weight table
			VK_VIDEO_ENCODE_H264_CAPABILITY_ROW_UNALIGNED_SLICE_BIT_KHR : 指明支持有多个slices的frame的每个slice可能在macroblock row中以任何偏移值开始或者结束。如果不支持则所有slice只能在macroblock row的开始处开始，在结束处结束
			VK_VIDEO_ENCODE_H264_CAPABILITY_DIFFERENT_SLICE_TYPE_BIT_KHR : 指明含多个slices的frame被编码时，实现允许根据定义在H.264 slice header parameters中的StdVideoEncodeH264SliceHeader::slice_type来编码每一个slice。如果不支持，则frame中的所有slice必须以对应到frame 的picture type的slice_type进行编码。 
			VK_VIDEO_ENCODE_H264_CAPABILITY_B_FRAME_IN_L0_LIST_BIT_KHR : 指明支持使用一个B frame 作为一个L0 引用，在H.264 picture information 中的StdVideoEncodeH264ReferenceListsInfo::RefPicList0进行指定
			VK_VIDEO_ENCODE_H264_CAPABILITY_B_FRAME_IN_L1_LIST_BIT_KHR : 指明支持使用一个B frame 作为一个L1 引用，在H.264 picture information 中的StdVideoEncodeH264ReferenceListsInfo::RefPicList1进行指定
			VK_VIDEO_ENCODE_H264_CAPABILITY_PER_PICTURE_TYPE_MIN_MAX_QP_BIT_KHR : 指定支持在VkVideoEncodeH264QpKHR中指定不同的QP值
			VK_VIDEO_ENCODE_H264_CAPABILITY_PER_SLICE_CONSTANT_QP_BIT_KHR : 指定支持为每一个slice指定不同的QP值
			VK_VIDEO_ENCODE_H264_CAPABILITY_GENERATE_PREFIX_NALU_BIT_KHR : 指定支持通过在VkVideoEncodeH264PictureInfoKHR::generatePrefixNalu 设置为 VK_TRUE来产生prefix NAL units（可见H.264 Encode Bitstream Data Access p3569）
			
			*/
			videoEncodeH264CapabilitiesKHR.maxLevelIdc = STD_VIDEO_H264_LEVEL_IDC_1_0;//一个StdVideoH264LevelIdc 值，指明该profile支持的最大的H.264 level，其中值格式为STD_VIDEO_H264_LEVEL_IDC_<major>_<minor> 指明H.264 level， <major>.<minor> 参见 ITU-T H.264 Specification的A.3章节
			videoEncodeH264CapabilitiesKHR.maxSliceCount = 1;//指明对一个picture的可编码的slices的最大数量，该参数可被其他codec-specific参数影响
			videoEncodeH264CapabilitiesKHR.maxPPictureL0ReferenceCount = 1;//实现支持的P pictures的引用列表L0中reference pictures的最大引用数量，该参数不绝对，因为可能会被实现复写L0列表
			videoEncodeH264CapabilitiesKHR.maxBPictureL0ReferenceCount = 1;//实现支持的B pictures的引用列表L0中reference pictures的最大引用数量，该参数不绝对，因为可能会被实现复写L0列表
			videoEncodeH264CapabilitiesKHR.maxL1ReferenceCount = 1;//实现支持的B pictures（如果支持）的引用列表L1中reference pictures的最大引用数量，该参数不绝对，因为可能会被实现复写L1列表
			videoEncodeH264CapabilitiesKHR.maxTemporalLayerCount = 1;//为实现支持的H.264 temporal layers的最大数量
			videoEncodeH264CapabilitiesKHR.expectDyadicTemporalLayerPattern = 1;//指明当编码多个temporal layers时， rate control algorithms 期望使用一个 dyadic temporal layer pattern
			videoEncodeH264CapabilitiesKHR.minQp = 1;//指明支持的最小QP 值
			videoEncodeH264CapabilitiesKHR.maxQp = 1;//指明支持的最大QP 值
			videoEncodeH264CapabilitiesKHR.prefersGopRemainingFrames = VK_TRUE;//指明当开始一个 video coding scope时，rate control algorithm偏好应用指定在当前pictures组中剩余的各个类型的frame的数量
			videoEncodeH264CapabilitiesKHR.requiresGopRemainingFrames = VK_TRUE;//指明当开始一个 video coding scope时，rate control algorithm需要应用指定在当前pictures组中剩余的各个类型的frame的数量
			videoEncodeH264CapabilitiesKHR.stdSyntaxFlags = 0;/*VkVideoEncodeH264StdFlagBitsKHR 组合值位掩码，指明 H.264 syntax 元素的能力
			VkVideoEncodeH264StdFlagBitsKHR:
			VK_VIDEO_ENCODE_H264_STD_SEPARATE_COLOR_PLANE_FLAG_SET_BIT_KHR : 指定是否实现支持使用一个应用提供的值给SPS中的StdVideoH264SpsFlags::separate_colour_plane_flag（该值为1时）的值
			VK_VIDEO_ENCODE_H264_STD_QPPRIME_Y_ZERO_TRANSFORM_BYPASS_FLAG_SET_BIT_KHR : 指明是否实现支持使用一个应用提供的值给SPS中的StdVideoH264SpsFlags::qpprime_y_zero_transform_bypass_flag（该值为1时）的值
			VK_VIDEO_ENCODE_H264_STD_SCALING_MATRIX_PRESENT_FLAG_SET_BIT_KHR :指明是否实现支持使用一个应用提供的值给SPS中的StdVideoH264SpsFlags::seq_scaling_matrix_present_flag（该值为1时）或者StdVideoH264PpsFlags::pic_scaling_matrix_present_flag（当该值为1时）的值
			VK_VIDEO_ENCODE_H264_STD_CHROMA_QP_INDEX_OFFSET_BIT_KHR : 指明是否实现支持使用一个应用提供的值给PPS中的StdVideoH264PictureParameterSet::chroma_qp_index_offset（该值不为0时）的值
			VK_VIDEO_ENCODE_H264_STD_SECOND_CHROMA_QP_INDEX_OFFSET_BIT_KHR : 指明是否实现支持使用一个应用提供的值给PPS中的StdVideoH264PictureParameterSet::second_chroma_qp_index_offset（该值不为0时）的值
			VK_VIDEO_ENCODE_H264_STD_PIC_INIT_QP_MINUS26_BIT_KHR : 指明是否实现支持使用一个应用提供的值给PPS中的StdVideoH264PictureParameterSet::pic_init_qp_minus26（该值不为0时）的值
			VK_VIDEO_ENCODE_H264_STD_WEIGHTED_PRED_FLAG_SET_BIT_KHR : 指明是否实现支持使用一个应用提供的值给PPS中的StdVideoH264PpsFlags::weighted_pred_flag（该值为1时）的值
			VK_VIDEO_ENCODE_H264_STD_WEIGHTED_BIPRED_IDC_EXPLICIT_BIT_KHR : 指明是否实现支持使用一个应用提供的值给PPS中的StdVideoH264PictureParameterSet::weighted_bipred_idc（该值为STD_VIDEO_H264_WEIGHTED_BIPRED_IDC_EXPLICIT 时）的值
			VK_VIDEO_ENCODE_H264_STD_WEIGHTED_BIPRED_IDC_IMPLICIT_BIT_KHR : 指明是否实现支持使用一个应用提供的值给PPS中的StdVideoH264PictureParameterSet::weighted_bipred_idc（该值为STD_VIDEO_H264_WEIGHTED_BIPRED_IDC_IMPLICIT 时）的值
			VK_VIDEO_ENCODE_H264_STD_TRANSFORM_8X8_MODE_FLAG_SET_BIT_KHR : 指明是否实现支持使用一个应用提供的值给PPS中的StdVideoH264PpsFlags::transform_8x8_mode_flag（该值为1时）的值
			VK_VIDEO_ENCODE_H264_STD_DIRECT_SPATIAL_MV_PRED_FLAG_UNSET_BIT_KHR : 指明是否实现支持使用一个应用提供的值给H.264 slice header parameters中的StdVideoEncodeH264SliceHeaderFlags::direct_spatial_mv_pred_flag（该值为0时）的值
			VK_VIDEO_ENCODE_H264_STD_ENTROPY_CODING_MODE_FLAG_UNSET_BIT_KHR : 指明是否实现支持CAVLC entropy coding（定义在ITU-T H.264 Specification的9.2节），且支持使用一个应用提供的值给PPS中的StdVideoH264PpsFlags::entropy_coding_mode_flag（该值为0时）的值
			VK_VIDEO_ENCODE_H264_STD_ENTROPY_CODING_MODE_FLAG_SET_BIT_KHR : 指明是否实现支持CABAC entropy coding（定义在ITU-T H.264 Specification的9.3节），且支持使用一个应用提供的值给PPS中的StdVideoH264PpsFlags::entropy_coding_mode_flag（该值为1时）的值
			VK_VIDEO_ENCODE_H264_STD_DIRECT_8X8_INFERENCE_FLAG_UNSET_BIT_KHR : 指定是否实现支持使用一个应用提供的值给SPS中的StdVideoH264SpsFlags::direct_8x8_inference_flag（该值为0时）的值
			VK_VIDEO_ENCODE_H264_STD_CONSTRAINED_INTRA_PRED_FLAG_SET_BIT_KHR : 指定是否实现支持使用一个应用提供的值给PPS中的StdVideoH264PpsFlags::constrained_intra_pred_flag（该值为1时）的值
			VK_VIDEO_ENCODE_H264_STD_DEBLOCKING_FILTER_DISABLED_BIT_KHR : 指明是否实现支持使用一个应用提供的值给H.264 slice header parameters中的StdVideoEncodeH264SliceHeader::disable_deblocking_filter_idc（该值为STD_VIDEO_H264_DISABLE_DEBLOCKING_FILTER_IDC_DISABLED 时）的值
			VK_VIDEO_ENCODE_H264_STD_DEBLOCKING_FILTER_ENABLED_BIT_KHR : 指明是否实现支持使用一个应用提供的值给H.264 slice header parameters中的StdVideoEncodeH264SliceHeader::disable_deblocking_filter_idc（该值为STD_VIDEO_H264_DISABLE_DEBLOCKING_FILTER_IDC_ENABLED 时）的值
			VK_VIDEO_ENCODE_H264_STD_DEBLOCKING_FILTER_PARTIAL_BIT_KHR : 指明是否实现支持使用一个应用提供的值给H.264 slice header parameters中的StdVideoEncodeH264SliceHeader::disable_deblocking_filter_idc（该值为STD_VIDEO_H264_DISABLE_DEBLOCKING_FILTER_IDC_PARTIAL 时）的值
			VK_VIDEO_ENCODE_H264_STD_SLICE_QP_DELTA_BIT_KHR : 指明是否实现支持使用一个应用提供的值给H.264 slice header parameters中的StdVideoEncodeH264SliceHeader::slice_qp_delta（该值在编码的frame中的各个slices中相等时）的值
			VK_VIDEO_ENCODE_H264_STD_DIFFERENT_SLICE_QP_DELTA_BIT_KHR : 指明是否实现支持使用一个应用提供的值给H.264 slice header parameters中的StdVideoEncodeH264SliceHeader::slice_qp_delta（该值在编码的frame中的各个slices中不等时）的值
						
			*/


		}


		// H.264 Encode Quality Level Properties  参见p3577
		{
			/*
			当调用vkGetPhysicalDeviceVideoEncodeQualityLevelPropertiesKHR 传入 pVideoProfile->videoCodecOperation specified 为 VK_VIDEO_CODEC_OPERATION_ENCODE_H264_BIT_KHR 时，必须在 VkVideoEncodeQualityLevelPropertiesKHR.pNext中包含一个VkVideoEncodeH264QualityLevelPropertiesKHR 来返回额外的H.264 编码的 video encode quality level属性,
			*/

			VkVideoEncodeH264QualityLevelPropertiesKHR  videoEncodeH264QualityLevelPropertiesKHR{};
			videoEncodeH264QualityLevelPropertiesKHR.sType = VK_STRUCTURE_TYPE_MAX_ENUM;//没有定义这里设置为非法值
			videoEncodeH264QualityLevelPropertiesKHR.pNext = nullptr;
			videoEncodeH264QualityLevelPropertiesKHR.preferredRateControlFlags = 0;//VkVideoEncodeH264RateControlFlagBitsKHR 组合值位掩码，指明 VkVideoEncodeH264RateControlInfoKHR::flags 偏好使用的标志
			videoEncodeH264QualityLevelPropertiesKHR.preferredGopFrameCount = 1;//指明VkVideoEncodeH264RateControlInfoKHR::gopFrameCount 偏好使用的值
			videoEncodeH264QualityLevelPropertiesKHR.preferredIdrPeriod = 1;//指明VkVideoEncodeH264RateControlInfoKHR::idrPeriod 偏好使用的值
			videoEncodeH264QualityLevelPropertiesKHR.preferredConsecutiveBFrameCount = 1;//指明VkVideoEncodeH264RateControlInfoKHR::consecutiveBFrameCount 偏好使用的值
			videoEncodeH264QualityLevelPropertiesKHR.preferredTemporalLayerCount = 1;//指明VkVideoEncodeH264RateControlInfoKHR::temporalLayerCount 偏好使用的值
			videoEncodeH264QualityLevelPropertiesKHR.preferredConstantQp = VkVideoEncodeH264QpKHR{ .qpI = 0,.qpP = 0,.qpB = 0};//指明当使用rate control mode VK_VIDEO_ENCODE_RATE_CONTROL_MODE_DISABLED_BIT_KHR时 每个picture的VkVideoEncodeH264NaluSliceInfoKHR::constantQp 偏好使用的值
			videoEncodeH264QualityLevelPropertiesKHR.preferredMaxL0ReferenceCount = 0;//指明 reference list L0 中偏好使用的引用picture 的最大数量
			videoEncodeH264QualityLevelPropertiesKHR.preferredMaxL1ReferenceCount = 0;//指明 reference list L1 中偏好使用的引用picture 的最大数量
			videoEncodeH264QualityLevelPropertiesKHR.preferredStdEntropyCodingModeFlag = 0;//指明 StdVideoH264PpsFlags::entropy_coding_mode_flag 偏好使用的值

		}


		//H.264 Encode Session  参见p3578
		{
			/*
			创建一个使用 H.264 encode profile的 video session时可以在 VkVideoSessionCreateInfoKHR.pNext中包含一个VkVideoEncodeH264SessionCreateInfoKHR 指定额外的参数
			*/

			VkVideoEncodeH264SessionCreateInfoKHR  videoEncodeH264SessionCreateInfoKHR{};
			videoEncodeH264SessionCreateInfoKHR.sType = VK_STRUCTURE_TYPE_MAX_ENUM;
			videoEncodeH264SessionCreateInfoKHR.pNext = nullptr;
			videoEncodeH264SessionCreateInfoKHR.maxLevelIdc = STD_VIDEO_H264_LEVEL_IDC_1_0;//一个StdVideoH264LevelIdc 值指明创建video session产生的video bitstreams 使用的 H.264 level的上届，格式为STD_VIDEO_H264_LEVEL_IDC_<major>_<minor>，其中 <major>.<minor> 定义在 ITU-T H.264 Specification 的A.3节
			videoEncodeH264SessionCreateInfoKHR.useMaxLevelIdc = VK_TRUE;//指明实现是否使用maxLevelIdc，如果为VK_FALSE，则maxLevelIdc 忽略然后使用vkGetPhysicalDeviceVideoCapabilitiesKHR返回的VkVideoEncodeH264CapabilitiesKHR::maxLevelIdc
		}


		//H.264 Encode Parameter Sets  参见p3579
		{

			/*
			以VK_VIDEO_CODEC_OPERATION_ENCODE_H264_BIT_KHR创建的 video session parameters 会包含以下参数组:
				> H.264 Sequence Parameter Sets (SPS)参数组（见 ITU-T H.264 Specification）,对应StdVideoH264SequenceParameterSet ，参数组中参数的具体描述 见p3496 *** ;
				> H.264 Picture Parameter Sets (PPS)参数组（见 ITU-T H.264 Specification）,对应 StdVideoH264PictureParameterSet ，参数组中参数的具体描述 见p3496 *** ;
			这些参数可能被实现复写，所以需要调用vkGetEncodedVideoSessionParametersKHR 来确定实现是否复写了这些参数
			*/
			
			
			//当一个video session parameters 以VK_VIDEO_CODEC_OPERATION_ENCODE_H264_BIT_KHR 创建时，  VkVideoSessionParametersCreateInfoKHR::pNext 中必须包含一个 VkVideoEncodeH264SessionParametersCreateInfoKHR 指明该对象的初始容量
			VkVideoEncodeH264SessionParametersCreateInfoKHR videoEncodeH264SessionParametersCreateInfoKHR{};
			videoEncodeH264SessionParametersCreateInfoKHR.sType = VK_STRUCTURE_TYPE_MAX_ENUM;//没有定义所以这里定义为非法值
			videoEncodeH264SessionParametersCreateInfoKHR.pNext = nullptr;
			videoEncodeH264SessionParametersCreateInfoKHR.maxStdSPSCount = 1;//为创建的 VkVideoSessionParametersKHR 能包含的H.264 SPS 实体的最大数量
			videoEncodeH264SessionParametersCreateInfoKHR.maxStdPPSCount = 1;//为创建的 VkVideoSessionParametersKHR 能包含的H.264 PPS 实体的最大数量
			VkVideoEncodeH264SessionParametersAddInfoKHR videoEncodeH264SessionParametersAddInfoKHR{};//该结构体可以在VkVideoEncodeH264SessionParametersCreateInfoKHR.pParametersAddInfo中使用指定创建时的参数或者 在 VkVideoSessionParametersUpdateInfoKHR.pNext中包含指明更新的参数
			{
				videoEncodeH264SessionParametersAddInfoKHR.sType = VK_STRUCTURE_TYPE_MAX_ENUM;
				videoEncodeH264SessionParametersAddInfoKHR.pNext = nullptr;
				videoEncodeH264SessionParametersAddInfoKHR.stdSPSCount = 1;//为pStdSPSs 中的元素个数
				StdVideoH264SequenceParameterSet stdVideoH264SequenceParameterSet{/*假设这是一个有效的StdVideoH264SequenceParameterSet 结构体*/ };
				videoEncodeH264SessionParametersAddInfoKHR.pStdSPSs = &stdVideoH264SequenceParameterSet;//一组StdVideoH264SequenceParameterSet 数组指针指明添加的H.264 SPS 实体
				videoEncodeH264SessionParametersAddInfoKHR.stdPPSCount = 1;//为pStdPPSs 中的元素个数
				StdVideoH264PictureParameterSet stdVideoH264PictureParameterSet{/*假设这是一个有效的StdVideoH264PictureParameterSet 结构体*/ };
				videoEncodeH264SessionParametersAddInfoKHR.pStdPPSs = &stdVideoH264PictureParameterSet;//一组 StdVideoH264PictureParameterSet 数组指针指明添加的H.264 PPS 实体
				/*
				VkVideoEncodeH264SessionParametersAddInfoKHR有效用法:
				1.pStdSPSs中每个StdVideoH264SequenceParameterSet元素的 seq_parameter_set_id必须是唯一的
				2.pStdPPSs中每个StdVideoH264PictureParameterSet元素的 seq_parameter_set_id 以及 pic_parameter_set_id 参数对必须是唯一的
				*/
			}
			videoEncodeH264SessionParametersCreateInfoKHR.pParametersAddInfo = &videoEncodeH264SessionParametersAddInfoKHR;//为NULL或者一个 VkVideoEncodeH264SessionParametersAddInfoKHR 指针指明创建时添加的H.264 parameters


			//调用vkGetEncodedVideoSessionParametersKHR 时，在VkVideoEncodeSessionParametersGetInfoKHR.pNextVkVideoEncodeH264SessionParametersGetInfoKHR 来指定讲编码的参数数据写出的控制信息（如果设置将先写出SPS,在写出PPS）
			VkVideoEncodeH264SessionParametersGetInfoKHR videoEncodeH264SessionParametersGetInfoKHR{};
			videoEncodeH264SessionParametersGetInfoKHR.sType = VK_STRUCTURE_TYPE_MAX_ENUM;
			videoEncodeH264SessionParametersGetInfoKHR.pNext = nullptr;
			videoEncodeH264SessionParametersGetInfoKHR.stdPPSId = 0;//指明用来指定要获取的H.264 picture parameter set(s)的H.264 picture parameter set ID（当 writeStdPPS 设置为 VK_TRUE.）
			videoEncodeH264SessionParametersGetInfoKHR.stdSPSId = 0;//指明用来指定要获取的H.264 sequence 以及/或者 picture parameter set(s)的H.264 sequence parameter set ID
			videoEncodeH264SessionParametersGetInfoKHR.writeStdPPS = VK_TRUE;//指明是否请求获取 stdPPSId 指定的编码的 H.264 picture parameter set
			videoEncodeH264SessionParametersGetInfoKHR.writeStdSPS = VK_TRUE;//指明是否请求获取 stdSPSId 以及 stdPPSId 指定的编码的 H.264 sequence parameter set， 和 writeStdPPS 至少有一个为VK_TRUE


			VkVideoEncodeH264SessionParametersFeedbackInfoKHR videoEncodeH264SessionParametersFeedbackInfoKHR{};
			videoEncodeH264SessionParametersFeedbackInfoKHR.sType = VK_STRUCTURE_TYPE_MAX_ENUM;//没有定义这里设置为非法值
			videoEncodeH264SessionParametersFeedbackInfoKHR.pNext = nullptr;
			videoEncodeH264SessionParametersFeedbackInfoKHR.hasStdPPSOverrides = VK_TRUE;//指明任何请求（通过VkVideoEncodeH264SessionParametersGetInfoKHR::writeStdPPS请求）的 H.264 picture parameter set 是否被实现复写
			videoEncodeH264SessionParametersFeedbackInfoKHR.hasStdSPSOverrides = VK_FALSE;//指明任何请求（通过VkVideoEncodeH264SessionParametersGetInfoKHR::writeStdSPS请求）的 H.264 sequence parameter set 是否被实现复写



		}


		//H.264 Encoding Parameters  参见p3584
		{
			//在vkCmdEncodeVideoKHR 的  VkVideoEncodeInfoKHR.pNext中包含VkVideoEncodeH264PictureInfoKHR 指定 H.264 encode operation的codec-specific picture 信息，这些信息如何解释参见 p3585 ***
			VkVideoEncodeH264PictureInfoKHR   videoEncodeH264PictureInfoKHR{};
			videoEncodeH264PictureInfoKHR.sType = VK_STRUCTURE_TYPE_MAX_ENUM;//没有定义这里设置为非法值
			videoEncodeH264PictureInfoKHR.pNext = nullptr;
			videoEncodeH264PictureInfoKHR.naluSliceEntryCount = 1;//pNaluSliceEntries 中元素个数
			VkVideoEncodeH264NaluSliceInfoKHR videoEncodeH264NaluSliceInfoKHR{};
			{
				videoEncodeH264NaluSliceInfoKHR.sType = VK_STRUCTURE_TYPE_MAX_ENUM;//没有定义这里设置为非法值
				videoEncodeH264NaluSliceInfoKHR.pNext = nullptr;
				videoEncodeH264NaluSliceInfoKHR.constantQp = 0;
				StdVideoEncodeH264SliceHeader stdVideoEncodeH264SliceHeader{/*假设这是一个有效的StdVideoEncodeH264SliceHeader*/};
				videoEncodeH264NaluSliceInfoKHR.pStdSliceHeader = &stdVideoEncodeH264SliceHeader;
			}
			videoEncodeH264PictureInfoKHR.pNaluSliceEntries = &videoEncodeH264NaluSliceInfoKHR;//VkVideoEncodeH264NaluSliceInfoKHR 数组指针，指明input picture中每个编码的H.264 slices 的参数
			StdVideoEncodeH264PictureInfo stdVideoEncodeH264PictureInfo{/*假设这是一个有效的StdVideoEncodeH264PictureInfo*/};
			videoEncodeH264PictureInfoKHR.pStdPictureInfo = &stdVideoEncodeH264PictureInfo;//一个StdVideoEncodeH264PictureInfo 的指针，指明 H.264 picture information
			videoEncodeH264PictureInfoKHR.generatePrefixNalu = VK_FALSE;//控制是否在 slice NALUs产生到target bitstream之前生成 prefix NALUs（见ITU-T H.264 Specification 的7.3.2.12 以及 7.4.2.12节的定义）
			/*
			VkVideoEncodeH264PictureInfoKHR有效用法:

			
			
			
			*/

			//可以在 VkVideoDecodeInfoKHR::pSetupReferenceSlot->pNext 以及  VkVideoDecodeInfoKHR::pReferenceSlots->pNext 中包含VkVideoDecodeH264DpbSlotInfoKHR  来指明codec-specific reference picture information，具体信息如何解释见  p3501 ***
			VkVideoDecodeH264DpbSlotInfoKHR  videoDecodeH264DpbSlotInfoKHR{};
			videoDecodeH264DpbSlotInfoKHR.sType = VK_STRUCTURE_TYPE_VIDEO_DECODE_H264_DPB_SLOT_INFO_KHR;
			videoDecodeH264DpbSlotInfoKHR.pNext = nullptr;
			StdVideoDecodeH264ReferenceInfo stdVideoDecodeH264ReferenceInfo{/*假设这是一个有效的StdVideoDecodeH264ReferenceInfo 结构体*/ };
			videoDecodeH264DpbSlotInfoKHR.pStdReferenceInfo = &stdVideoDecodeH264ReferenceInfo;//一个StdVideoDecodeH264ReferenceInfo 指针，指明 H.264 reference information

		}

	}

}



NS_TEST_END