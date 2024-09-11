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
	VkCommandBuffer commandBuffer{/*��������һ����Ч��VkCommandBuffer*/ };


	//��ѹ��һ�����߶���ڴ������е�����
	VkDecompressMemoryRegionNV decompressMemoryRegionNV{};
	decompressMemoryRegionNV.srcAddress = VkDeviceAddress{/*��������һ����Ч��VkDeviceAddress*/ };//Ϊѹ�������ݵĴ洢��ַ
	decompressMemoryRegionNV.dstAddress = VkDeviceAddress{/*��������һ����Ч��VkDeviceAddress*/ };//ΪҪ��Ž�ѹ�������ݵ�Ŀ�ĵ�ַ
	decompressMemoryRegionNV.compressedSize = 1;//Ϊѹ�������ݵ��ֽ�����С
	decompressMemoryRegionNV.decompressedSize = 2; //Ϊ��ѹ�������ݵ��ֽ�����С
	decompressMemoryRegionNV.decompressionMethod = VK_MEMORY_DECOMPRESSION_METHOD_GDEFLATE_1_0_BIT_NV;//һ��ֻ����һ��bit���õ� VkMemoryDecompressionMethodFlagBitsNV���֮λ���룬ָ����ѹ���ķ����� VK_MEMORY_DECOMPRESSION_METHOD_GDEFLATE_1_0_BIT_NV : ָ�� GDeflate 1.0 �㷨���ڽ�ѹ����.
	/*
	VkDecompressMemoryRegionNV��Ч�÷�:
	1.srcAddress ������뵽4�ֽ�
	2.srcAddress �� srcAddress + compressedSize��ַ��Χ�е��ڴ��������Ч���Ұ󶨵�һ��VkDeviceMemory ��
	3.dstAddress ������뵽4�ֽ�
	4.���decompressionMethod ΪVK_MEMORY_DECOMPRESSION_METHOD_GDEFLATE_1_0_BIT_NV����decompressedSize����С�ڵ���65536 �ֽ�
	5.dstAddress �� dstAddress + compressedSize��ַ��Χ�е��ڴ��������Ч���Ұ󶨵�һ��VkDeviceMemory ��
	6.decompressedSize �����㹻�������ɻ���decompressionMethod������ѹ���������
	7.decompressionMethod ����ֻ��һ��bit����
	8.srcAddress �� srcAddress + compressedSize��ַ��Χ�е��ڴ治�ܺ�dstAddress �� dstAddress + compressedSize��ַ��Χ�е��ڴ����ص�
	*/

	vkCmdDecompressMemoryNV(commandBuffer, 1, &decompressMemoryRegionNV);// memoryDecompression ���Ա��뿪��



	//��ѹ��һ�����߶���ڴ������е�����,������ز���������buffer��
	vkCmdDecompressMemoryIndirectCountNV(commandBuffer,
		VkDeviceAddress{/*��������һ����Ч��VkDeviceAddress*/ }/*indirectCommandsAddress,Ϊ����VkDecompressMemoryRegionNV �ṹ��������豸��ַ��ָ����ؽ�ѹ������.*/,
		VkDeviceAddress{/*��������һ����Ч��VkDeviceAddress*/ }/*indirectCommandsCountAddress,Ϊ��Ž�ѹ�������������豸��ַ.*/,
		sizeof(VkDecompressMemoryRegionNV)/*stride,ΪindirectCommandsAddress ������������֮����ֽڲ���.*/);
	/*
	vkCmdDecompressMemoryIndirectCountNV��Ч�÷�:
	1.memoryDecompression ���Ա��뿪��
	2.indirectCommandsAddress ��ָ��buffer�����non-sparse�ģ����buffer����󶨵������������ĵ�����VkDeviceMemory�ϣ��Ҹ�buffer������VK_BUFFER_USAGE_INDIRECT_BUFFER_BIT����
	3.indirectCommandsCountAddress ��ָ��buffer�����non-sparse�ģ����buffer����󶨵������������ĵ�����VkDeviceMemory�ϣ��Ҹ�buffer������VK_BUFFER_USAGE_INDIRECT_BUFFER_BIT����
	4.indirectCommandsCountAddress ������4�ı���
	5.�����indirectCommandsCountAddress�еļ���ֵ����С�ڵ���VkPhysicalDeviceMemoryDecompressionPropertiesNV::maxDecompressionIndirectCount
	6.stride ������4�ı����Ҵ��ڵ���sizeof(VkDecompressMemoryRegionNV) 
	7.��������indirectCommandsCountAddress�еļ���ֵΪ1����(offset + sizeof(VkDecompressMemoryRegionNV)) ����С�ڵ���indirectCommandsAddress ��ָ��buffer�Ĵ�С
	8.��������indirectCommandsCountAddress�еļ���ֵ����1����indirectCommandsAddress + sizeof(VkDecompressMemoryRegionNV) + (stride �� (indirectCommandsCountAddress�еļ���ֵ - 1)) ����С�ڵ���indirectCommandsAddress ��ָ��buffer�����һ����Ч�ĵ�ַ
	*/

}

void MemoryDecompressionAndVideoCodingTest::VideoCodingTest()
{
	/*
	vulkan ʵ�ֿ����ṩһ�������������Լ�һЩ�ӿ���������֧��video ���������Ҫִ��video ������Ҫ����������¼��command buffer Ȼ���ύ����ִ�С�
	*/

	
	//Video Picture Resources  �μ�p3402
	{
		/*
		��video �����У���ά��arrays��image��������Ϊvideo picture resources������ܰ���һЩ�������Ϣ��

		��Щimage��VkImage����ʽ���ڣ���VkImageView �������� decode output pictures, encode input pictures, reconstructed pictures, �Լ�/���� reference pictures.
		
		*/


		//ָ�� video picture resource �Ĳ���
		VkVideoPictureResourceInfoKHR videoPictureResourceInfoKHR{};
		videoPictureResourceInfoKHR.sType = VK_STRUCTURE_TYPE_VIDEO_PROFILE_INFO_KHR;
		videoPictureResourceInfoKHR.pNext = nullptr;
		videoPictureResourceInfoKHR.baseArrayLayer = 0;//Ϊʹ�õĻ���imageViewBinding��ָ��VkImageView�е� array layers������������С�ڴ���imageViewBinding��VkImageViewCreateInfo::subresourceRange.layerCount
		videoPictureResourceInfoKHR.codedExtent = VkExtent2D{ .width = 1,.height = 1 };//ΪҪʹ��image subresource��texel�ķ�Χ
		videoPictureResourceInfoKHR.codedOffset = VkOffset2D{ .x = 0,.y = 0 };//ΪҪʹ��image subresource��texel��ƫ��ֵ
		videoPictureResourceInfoKHR.imageViewBinding = VkImageView{/*��������һ����Ч��VkImageView*/ };
	

	}


	//Decoded Picture Buffer  �μ�p3404
	{
		/*
		һ��������video coding pipeline��ѹ����video�������ؽ�Ϊͼ��

		decoded picture buffer (DPB)Ϊ������һ�������video coding��ͼ����Ϣ�Ŀ����������ݽṹ�����п������ĵ���ʵ��Ϊ decoded picture buffer (DPB) slots��������Χ��0 �� N-1������NΪ DPB��������ÿ��DPB slot����һ��video frame���������õ�һ��pictureҲ����������õ�����picture��������picture�ֱ����video frame��top �Լ�bottom��������Щslots��״̬��video session������������VkImage�洢��

		���⣬ʵ�ֿ��ܹ���һЩ��͸����metadata�� DPB slots,��Щ���ݿ�����video session�������ֱ�Ӵ�ŵ� DPB slots��ǰ�߿�������Щmetadata�ڶ��video session�乲��������������video session��
		
		*/

		
		// DPB Slot States  �μ�p3405
		{
			/*
			DPB slot��״̬Ϊ�������δ����������δ�����״̬��
			
			DPB slot������video coding����Ϊ  picture reconstruction������target��ʱ�򼤻�������� reconstructed pictureΪ reference picture��

			video coding �����Ƿ�ɹ�����ͨ�� VkQueryResultStatusKHR ���в�ѯ��

			DPB slot������Ӧ�ö����û���������һЩָ�����ʱִ��video coding����δ����״̬���μ�p3405
			*/
		}

	}


	//Video Profiles  �μ�p3406
	{
		/*
		VkVideoProfileInfoKHR������ΪvkGetPhysicalDeviceVideoCapabilitiesKHR ����������������� vkGetPhysicalDeviceVideoFormatPropertiesKHR����vkGetPhysicalDeviceImageFormatProperties2��pProfiles��VkVideoProfileListInfoKHR��pNext�� �����ܷ���һЩ������Ϣ:
		VK_ERROR_VIDEO_PICTURE_LAYOUT_NOT_SUPPORTED_KHR : ָ�������video picture layout������VkVideoProfileInfoKHR.pNext�е�VkVideoDecodeH264ProfileInfoKHR��pictureLayout����֧��
		VK_ERROR_VIDEO_PROFILE_OPERATION_NOT_SUPPORTED_KHR : ָ��videoCodecOperationָ����video profile operation��֧��
		VK_ERROR_VIDEO_PROFILE_FORMAT_NOT_SUPPORTED_KHR : ָ��chromaSubsampling, lumaBitDepth, ���� chromaBitDepthָ����video format������֧��
		VK_ERROR_VIDEO_PROFILE_CODEC_NOT_SUPPORTED_KHR : ָ����Ӧvideo codec operation��codec-specific������֧��
		
		*/
		VkVideoProfileInfoKHR videoProfileInfoKHR{};
		videoProfileInfoKHR.sType = VK_STRUCTURE_TYPE_VIDEO_PROFILE_INFO_KHR;
		videoProfileInfoKHR.pNext = nullptr;
		videoProfileInfoKHR.chromaBitDepth = VK_VIDEO_COMPONENT_BIT_DEPTH_12_BIT_KHR;/*VkVideoComponentBitDepthFlagBitsKHR ���ֵλ����ָ�� video chroma bit depth ��Ϣ
		VkVideoComponentBitDepthFlagBitsKHR:
		VK_VIDEO_COMPONENT_BIT_DEPTH_8_BIT_KHR : ָ��һ�� component bit depth Ϊ 8 bits.
		VK_VIDEO_COMPONENT_BIT_DEPTH_10_BIT_KHR : ָ��һ�� component bit depth Ϊ 10 bits.
		VK_VIDEO_COMPONENT_BIT_DEPTH_12_BIT_KHR : ָ��һ�� component bit depth Ϊ 12 bits.
		
		*/
		videoProfileInfoKHR.chromaSubsampling = VK_VIDEO_CHROMA_SUBSAMPLING_420_BIT_KHR;/* VkVideoChromaSubsamplingFlagBitsKHR���ֵλ����ָ��video chroma subsampling��Ϣ
		VkVideoChromaSubsamplingFlagBitsKHR:
		VK_VIDEO_CHROMA_SUBSAMPLING_MONOCHROME_BIT_KHR : ָ��formatΪmonochrome.
		VK_VIDEO_CHROMA_SUBSAMPLING_420_BIT_KHR : ָ��formatΪ 4:2:0 chroma subsampled, ������chroma components��ˮƽ�����Լ���ֱ�����Ĳ�������Ϊ��luma component�Ĳ������ʵ�һ��
		VK_VIDEO_CHROMA_SUBSAMPLING_422_BIT_KHR : ָ��formatΪ 4:2:2 chroma subsampled, ������chroma components��ˮƽ�����Ĳ�������Ϊ��luma component�Ĳ������ʵ�һ��
		VK_VIDEO_CHROMA_SUBSAMPLING_444_BIT_KHR : ָ��formatΪ 4:4:4 chroma sampled, ��Y��CBCR format������component�Ĳ�������ͬ��û��chroma subsampling
		
		*/
		videoProfileInfoKHR.lumaBitDepth = VK_VIDEO_COMPONENT_BIT_DEPTH_12_BIT_KHR;//VkVideoComponentBitDepthFlagBitsKHR ���ֵλ����ָ�� video luma bit depth ��Ϣ
		videoProfileInfoKHR.videoCodecOperation = VK_VIDEO_CODEC_OPERATION_DECODE_H264_BIT_KHR;/*һ�� VkVideoCodecOperationFlagBitsKHR ָ��video code ����
		VkVideoCodecOperationFlagBitsKHR:
		VK_VIDEO_CODEC_OPERATION_NONE_KHR : ָ����֧���κ�video codec operations.
		VK_VIDEO_CODEC_OPERATION_DECODE_H264_BIT_KHR : ָ��֧�� H.264 decode operations.
		VK_VIDEO_CODEC_OPERATION_DECODE_H265_BIT_KHR : ָ��֧�� H.265 decode operations.
		VK_VIDEO_CODEC_OPERATION_DECODE_AV1_BIT_KHR : ָ��֧�� AV1 decode operations.
		VK_VIDEO_CODEC_OPERATION_ENCODE_H264_BIT_KHR : ָ��֧�� H.264 encode operations.
		VK_VIDEO_CODEC_OPERATION_ENCODE_H265_BIT_KHR : ָ��֧�� H.265 encode operations.
		*/
		
		/*
		VkVideoProfileInfoKHR��Ч�÷�:
		1.chromaSubsampling ����ֻ����һ��bit����
		2.lumaBitDepth ����ֻ����һ��bit����
		3.���chromaSubsampling ��ΪVK_VIDEO_CHROMA_SUBSAMPLING_MONOCHROME_BIT_KHR����chromaBitDepth ����ֻ����һ��bit����
		4.���videoCodecOperation ��ΪVK_VIDEO_CODEC_OPERATION_DECODE_H264_BIT_KHR����pNext�б������һ��VkVideoDecodeH264ProfileInfoKHR
		5.���videoCodecOperation ��ΪVK_VIDEO_CODEC_OPERATION_DECODE_H265_BIT_KHR����pNext�б������һ��VkVideoDecodeH265ProfileInfoKHR
		6.���videoCodecOperation ��ΪVK_VIDEO_CODEC_OPERATION_DECODE_AV1_BIT_KHR����pNext�б������һ��VkVideoDecodeAV1ProfileInfoKHR
		7.���videoCodecOperation ��ΪVK_VIDEO_CODEC_OPERATION_ENCODE_H264_BIT_KHR����pNext�б������һ��VkVideoEncodeH264ProfileInfoKHR
		8.���videoCodecOperation ��ΪVK_VIDEO_CODEC_OPERATION_ENCODE_H265_BIT_KHR����pNext�б������һ��VkVideoEncodeH265ProfileInfoKHR
		*/



		//VkVideoDecodeUsageInfoKHR ����ָ��video decodeʹ�õĶ�����Ϣ����ӵ� VkVideoProfileInfoKHR.pNext��
		VkVideoDecodeUsageInfoKHR videoDecodeUsageInfoKHR{};
		videoDecodeUsageInfoKHR.sType = VK_STRUCTURE_TYPE_VIDEO_DECODE_USAGE_INFO_KHR;
		videoDecodeUsageInfoKHR.pNext = nullptr;
		videoDecodeUsageInfoKHR.videoUsageHints = VK_VIDEO_DECODE_USAGE_DEFAULT_KHR;/* VkVideoDecodeUsageFlagBitsKHR ���ֵλ���룬ָ��video decode profile��Ԥ���÷���ʾ
		VkVideoDecodeUsageFlagBitsKHR:
		VK_VIDEO_DECODE_USAGE_TRANSCODING_BIT_KHR : ָ��video decoding Ԥ����������video encoding��һvideo bitstream����ͬ�Լ�/���߲�ͬ��codecs����ת����
		VK_VIDEO_DECODE_USAGE_OFFLINE_BIT_KHR : ָ��video decoding Ԥ����������һlocal video bitstream
		VK_VIDEO_DECODE_USAGE_STREAMING_BIT_KHR : ָ��video decoding Ԥ����������һ��Ϊ�������Ͻ��յ�����������video bitstream

		*/

		

		//VkVideoEncodeUsageInfoKHR ����ָ��video encodeʹ�õĶ�����Ϣ����ӵ� VkVideoProfileInfoKHR.pNext��
		VkVideoEncodeUsageInfoKHR videoEncodeUsageInfoKHR{};
		videoEncodeUsageInfoKHR.sType = VK_STRUCTURE_TYPE_MAX_ENUM;//û�ж����������ﶨ��Ϊ�Ƿ�ֵ
		videoEncodeUsageInfoKHR.pNext = nullptr;
		videoEncodeUsageInfoKHR.tuningMode = VK_VIDEO_ENCODE_TUNING_MODE_DEFAULT_KHR;/* VkVideoEncodeTuningModeKHR ֵ��ָ���� video profile���б���ʱ�ĵ���ģʽ
		VkVideoEncodeTuningModeKHR:
		VK_VIDEO_ENCODE_TUNING_MODE_DEFAULT_KHR : ָ��ΪĬ�ϵĵ���ģʽ
		VK_VIDEO_ENCODE_TUNING_MODE_HIGH_QUALITY_KHR : ָ��video encodingҪ�Ը��������е��ơ�ʹ�ø�ģʽʱ��ʵ�ֿ��ܻ�������Ƶ����������ӳ٣����������
		VK_VIDEO_ENCODE_TUNING_MODE_LOW_LATENCY_KHR : ָ��video encodingҪ�Ե��ӳٽ��е��ơ�ʹ�ø�ģʽʱ��ʵ�ֿ��ܻ������������Э������������Լ�����video encode�������ӳ١�
		VK_VIDEO_ENCODE_TUNING_MODE_ULTRA_LOW_LATENCY_KHR : ָ��video encodingҪ�Գ����ӳٽ��е��ơ�ʹ�ø�ģʽʱ��ʵ�ֿ��ܻ������������Э������������Լ���С��video encode�������ӳ١�
		VK_VIDEO_ENCODE_TUNING_MODE_LOSSLESS_KHR : ָ��video encodingҪ��������е��ơ�ʹ�ø�ģʽʱ�� video encode�����������������
		
		*/
		videoEncodeUsageInfoKHR.videoContentHints = VK_VIDEO_ENCODE_CONTENT_DEFAULT_KHR;/*VkVideoEncodeContentFlagBitsKHR ���ֵλ���룬ָ��ʹ��video encode profile�ı����ڴ���ʾ
		VkVideoEncodeContentFlagBitsKHR:
		VK_VIDEO_ENCODE_CONTENT_CAMERA_BIT_KHR : ָ��video encoding Ԥ�����������������
		VK_VIDEO_ENCODE_CONTENT_DESKTOP_BIT_KHR : ָ��video encoding Ԥ�������������棨desktop������
		VK_VIDEO_ENCODE_CONTENT_RENDERED_BIT_KHR : ָ��video encoding Ԥ������������Ⱦ������Ϸ������
		*/
		videoEncodeUsageInfoKHR.videoUsageHints = VK_VIDEO_ENCODE_USAGE_DEFAULT_KHR;/*VkVideoEncodeUsageFlagBitsKHR ���ֵλ���룬ָ��video encode profile��Ԥ���÷���ʾ
		VkVideoEncodeUsageFlagBitsKHR:
		VK_VIDEO_ENCODE_USAGE_TRANSCODING_BIT_KHR : ָ��video encoding Ԥ����������video decoding��һvideo bitstream����ͬ�Լ�/���߲�ͬ��codecs����ת����
		VK_VIDEO_ENCODE_USAGE_STREAMING_BIT_KHR : ָ��video encoding Ԥ����������һ���������͵������ϵ���Ϊһ���������� video bitstream
		VK_VIDEO_ENCODE_USAGE_RECORDING_BIT_KHR : ָ��video encoding Ԥ������ʵʱ��¼offline consumption
		VK_VIDEO_ENCODE_USAGE_CONFERENCING_BIT_KHR : ָ��video encoding Ԥ��������Ƶ���鳡����
		*/


		// VkVideoProfileListInfoKHR
		VkVideoProfileListInfoKHR  videoProfileListInfoKHR{};
		videoProfileListInfoKHR.sType = VK_STRUCTURE_TYPE_VIDEO_PROFILE_LIST_INFO_KHR;
		videoProfileListInfoKHR.pNext = nullptr;
		videoProfileListInfoKHR.profileCount = 1;// pProfiles �е�Ԫ�ظ���
		videoProfileListInfoKHR.pProfiles = &videoProfileInfoKHR;//һ��VkVideoProfileInfoKHR ����ָ�룬���в����г���һ����Ԫ�ص� videoCodecOperationָ��decode operation
	}


	//Video Capabilities  �μ�p3416
	{
		//Video Coding Capabilities �μ�p3416
		{
			struct VideoCapabilitiesKHREXT {
				VkVideoDecodeAV1CapabilitiesKHR videoDecodeAV1CapabilitiesKHR{};//�ֶ�����
				VkVideoDecodeCapabilitiesKHR videoDecodeCapabilitiesKHR{};
				VkVideoDecodeH264CapabilitiesKHR videoDecodeH264CapabilitiesKHR{};
				VkVideoDecodeH265CapabilitiesKHR videoDecodeH265CapabilitiesKHR{};
				VkVideoEncodeCapabilitiesKHR videoEncodeCapabilitiesKHR{};
				VkVideoEncodeH264CapabilitiesKHR videoEncodeH264CapabilitiesKHR{};//�ֶ�����
				VkVideoEncodeH265CapabilitiesKHR videoEncodeH265CapabilitiesKHR{};//�ֶ�����
				VideoCapabilitiesKHREXT() {
					Init();
				}
				void Init() {
					videoDecodeAV1CapabilitiesKHR.sType = VK_STRUCTURE_TYPE_MAX_ENUM;//û�ж��壬���ﶨ��Ϊ�Ƿ�ֵ
					videoDecodeAV1CapabilitiesKHR.pNext = nullptr;
					videoDecodeCapabilitiesKHR.sType = VK_STRUCTURE_TYPE_VIDEO_DECODE_CAPABILITIES_KHR;
					videoDecodeCapabilitiesKHR.pNext = nullptr;
					videoDecodeH264CapabilitiesKHR.sType = VK_STRUCTURE_TYPE_VIDEO_DECODE_H264_CAPABILITIES_KHR;
					videoDecodeH264CapabilitiesKHR.pNext = nullptr;
					videoDecodeH265CapabilitiesKHR.sType = VK_STRUCTURE_TYPE_VIDEO_DECODE_H265_CAPABILITIES_KHR;
					videoDecodeH265CapabilitiesKHR.pNext = nullptr;
					videoEncodeCapabilitiesKHR.sType = VK_STRUCTURE_TYPE_MAX_ENUM;//û�ж��壬���ﶨ��Ϊ�Ƿ�ֵ
					videoEncodeCapabilitiesKHR.pNext = nullptr;
					videoEncodeH264CapabilitiesKHR.sType = VK_STRUCTURE_TYPE_MAX_ENUM;//û�ж��壬���ﶨ��Ϊ�Ƿ�ֵ
					videoEncodeH264CapabilitiesKHR.pNext = nullptr;
					videoEncodeH265CapabilitiesKHR.sType = VK_STRUCTURE_TYPE_MAX_ENUM;//û�ж��壬���ﶨ��Ϊ�Ƿ�ֵ
					videoEncodeH265CapabilitiesKHR.pNext = nullptr;
				}

			};


			//��ѯָ��video profile�� video coding����
			VkVideoProfileInfoKHR videoProfileInfoKHR{/*��������һ����Ч��VkVideoProfileInfoKHR*/ };//ǰ���Ѿ��������ˣ����ﲻ�ٸ���
			VkVideoCapabilitiesKHR videoCapabilitiesKHR{};
			videoCapabilitiesKHR.sType = VK_STRUCTURE_TYPE_VIDEO_CAPABILITIES_KHR;
			VideoCapabilitiesKHREXT videoCapabilitiesKHREXT{};
			videoCapabilitiesKHR.pNext = &videoCapabilitiesKHREXT.videoDecodeAV1CapabilitiesKHR;
			VkResult result/*���ؽ����Ϣ������д����֮ǰ�����Ĵ�����Ϣ*/ = vkGetPhysicalDeviceVideoCapabilitiesKHR(physicalDevice, &videoProfileInfoKHR, &videoCapabilitiesKHR);//���践������ȷ���
			/*
			vkGetPhysicalDeviceVideoCapabilitiesKHR��Ч�÷�:
			1.���pVideoProfile->videoCodecOperationָ��һ��decode operation����pCapabilities->pNext�б������һ��VkVideoDecodeCapabilitiesKHR
			2.���pVideoProfile->videoCodecOperationΪVK_VIDEO_CODEC_OPERATION_DECODE_H264_BIT_KHR����pCapabilities->pNext�б������һ��VkVideoDecodeH264CapabilitiesKHR
			3.���pVideoProfile->videoCodecOperationΪVK_VIDEO_CODEC_OPERATION_DECODE_H265_BIT_KHR����pCapabilities->pNext�б������һ��VkVideoDecodeH265CapabilitiesKHR
			4.���pVideoProfile->videoCodecOperationΪVK_VIDEO_CODEC_OPERATION_DECODE_AV1_BIT_KHR����pCapabilities->pNext�б������һ��VkVideoDecodeAV1CapabilitiesKHR
			5.���pVideoProfile->videoCodecOperationָ��һ��encode operation����pCapabilities->pNext�б������һ��VkVideoEncodeCapabilitiesKHR
			6.���pVideoProfile->videoCodecOperationΪVK_VIDEO_CODEC_OPERATION_ENCODE_H264_BIT_KHR����pCapabilities->pNext�б������һ��VkVideoEncodeH264CapabilitiesKHR
			7.���pVideoProfile->videoCodecOperationΪVK_VIDEO_CODEC_OPERATION_ENCODE_H265_BIT_KHR����pCapabilities->pNext�б������һ��VkVideoEncodeH265CapabilitiesKHR
			*/

			videoCapabilitiesKHR.flags = VK_VIDEO_CAPABILITY_PROTECTED_CONTENT_BIT_KHR;/*VkVideoCapabilityFlagBitsKHR ���ֵλ����ָ��������־
			VkVideoCapabilityFlagBitsKHR:
			VK_VIDEO_CAPABILITY_PROTECTED_CONTENT_BIT_KHR : ָ��video sessions ֧�ֲ����Լ�����protected����
			VK_VIDEO_CAPABILITY_SEPARATE_REFERENCE_IMAGES_BIT_KHR : ָ��������video session ��DPB slots��video picture resources���Դ洢�ڲ�ͬ�� VkImage�С�����ñ�־��֧�֣���ֻ�ܴ����ͬһ��VkImage�У�ʹ�ò�ͬlayer��
			*/
			videoCapabilitiesKHR.minBitstreamBufferOffsetAlignment = 4;//bitstream buffer����С����ƫ����
			videoCapabilitiesKHR.minBitstreamBufferSizeAlignment = 4;//bitstream buffer����С��Χ��С
			videoCapabilitiesKHR.pictureAccessGranularity = VkExtent2D{ .width = 1,.height = 1 };//��image��Ϊvideo picture resources����ʱ����С��������
			videoCapabilitiesKHR.minCodedExtent = VkExtent2D{ .width = 1,.height = 1 };//����֡��frame������Сwidth�Լ�height
			videoCapabilitiesKHR.maxCodedExtent = VkExtent2D{ .width = 1,.height = 1 };//����֡��frame�������width�Լ�height
			videoCapabilitiesKHR.maxDpbSlots = 2;//һ��video session��֧�ֵ�����DPB slots������
			videoCapabilitiesKHR.maxActiveReferencePictures = 2;//һ�� video coding ��������ʹ�õ�active reference pictures���������
			videoCapabilitiesKHR.stdHeaderVersion = VkExtensionProperties{ .extensionName = "header",.specVersion = 1 };// Ϊһ��VkExtensionProperties����¼��׼��Ƶͷ�����Լ�video profile֧�ֵİ汾

		}


		// Video Format Capabilities  �μ�p3419
		{
			//�о�ָ�� video profile֧�ֵ�output, input �Լ� DPB image ��formats �Ͷ�Ӧ������
			VkPhysicalDeviceVideoFormatInfoKHR physicalDeviceVideoFormatInfoKHR{};
			physicalDeviceVideoFormatInfoKHR.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VIDEO_FORMAT_INFO_KHR;
			physicalDeviceVideoFormatInfoKHR.pNext = nullptr;//���԰��� VkVideoProfileListInfoKHR
			physicalDeviceVideoFormatInfoKHR.imageUsage = VK_IMAGE_USAGE_VIDEO_DECODE_DPB_BIT_KHR;//VkImageUsageFlagBits ���ֵλ���룬ָ��video image��Ԥ����;

			uint32_t videoFormatPropertyCount = 0;
			std::vector<VkVideoFormatPropertiesKHR> videoFormatPropertiesKHRs{};
			VkResult result/*���ؽ����Ϣ�������֧�� VkVideoProfileListInfoKHR::pProfiles�е��κ�һ���򷵻�֮ǰ�����Ĵ�����Ϣ�������֧��VkPhysicalDeviceVideoFormatInfoKHR::imageUsage�򷵻�VK_ERROR_IMAGE_USAGE_NOT_SUPPORTED_KHR*/
				= vkGetPhysicalDeviceVideoFormatPropertiesKHR(physicalDevice, &physicalDeviceVideoFormatInfoKHR, &videoFormatPropertyCount, nullptr);
			videoFormatPropertiesKHRs.resize(videoFormatPropertyCount);
			VkResult result/*���ؽ����Ϣ�������֧�� VkVideoProfileListInfoKHR::pProfiles�е��κ�һ���򷵻�֮ǰ�����Ĵ�����Ϣ�������֧��VkPhysicalDeviceVideoFormatInfoKHR::imageUsage�򷵻�VK_ERROR_IMAGE_USAGE_NOT_SUPPORTED_KHR*/
				= vkGetPhysicalDeviceVideoFormatPropertiesKHR(physicalDevice, &physicalDeviceVideoFormatInfoKHR, &videoFormatPropertyCount, videoFormatPropertiesKHRs.data());//����ɹ�������һ��Ԫ��
			/*
			vkGetPhysicalDeviceVideoFormatPropertiesKHR�ӿ�ʹ�õ�һЩ������Ҫ��Ϣ��p3420


			vkGetPhysicalDeviceVideoFormatPropertiesKHR��Ч�÷�:
			1. pVideoFormatInfo->pNext�б������һ�� profileCount ����0��  VkVideoProfileListInfoKHR

			*/

			VkVideoFormatPropertiesKHR& videoFormatPropertiesKHR = videoFormatPropertiesKHRs[0];
			videoFormatPropertiesKHR.sType = VK_STRUCTURE_TYPE_VIDEO_FORMAT_PROPERTIES_KHR;
			videoFormatPropertiesKHR.pNext = nullptr;
			videoFormatPropertiesKHR.format = VK_FORMAT_R8G8B8A8_SRGB;//һ�� VkFormat ֵָ�����Ժ�ָ����video profiles�Լ�  image usages ʹ�õ�format
			videoFormatPropertiesKHR.componentMapping = VkComponentMapping{ .r = VK_COMPONENT_SWIZZLE_IDENTITY,
																		   .g = VK_COMPONENT_SWIZZLE_IDENTITY,
																		   .b = VK_COMPONENT_SWIZZLE_IDENTITY ,
																		   .a = VK_COMPONENT_SWIZZLE_IDENTITY };//һ�� VkComponentMapping ֵָ��format����ɫͨ����˳������������video encoder input ������video decoder output��ɫͨ��˳�������������
			videoFormatPropertiesKHR.imageCreateFlags = VK_IMAGE_CREATE_DISJOINT_BIT;//VkImageCreateFlagBits ���ֵλ����ָ����format֧�ֵ�image������־
			videoFormatPropertiesKHR.imageType = VK_IMAGE_TYPE_2D;//VkImageType ֵָ����format֧�ֵ�image����
			videoFormatPropertiesKHR.imageTiling = VK_IMAGE_TILING_OPTIMAL;//VkImageTiling ֵָ����format֧�ֵ�image tiling
			videoFormatPropertiesKHR.imageUsageFlags = VK_IMAGE_USAGE_VIDEO_DECODE_DPB_BIT_KHR;//VkImageUsageFlagBits ���ֵλ����ָ����format֧�ֵ�image��;





		}
	}



	// Video Session  �μ�p3425
	{
		/*
		video sessions ���ڱ���ά��ʹ��ָ�� video profile��video decode ���� encode����״̬�Ķ���
		
		*/


		VkVideoSessionKHR videoSessionKHR{};

		//Creating a Video Session  �μ�p3425
		{
			VkVideoProfileInfoKHR videoProfileInfoKHR{/*��������һ����Ч��VkVideoProfileInfoKHR*/ };//ǰ���Ѿ��������ˣ����ﲻ�ٸ���
			VkExtensionProperties extensionProperties{/*��������һ����Ч��VkExtensionProperties*/ };//ǰ���Ѿ��������ˣ����ﲻ�ٸ���


			struct VideoSessionCreateInfoKHREXT {

				VkVideoEncodeH264SessionCreateInfoKHR videoEncodeH264SessionCreateInfoKHR{};
				VkVideoEncodeH265SessionCreateInfoKHR videoEncodeH265SessionCreateInfoKHR{};
				VideoSessionCreateInfoKHREXT() {
					Init();
				}
				void Init() {
					videoEncodeH264SessionCreateInfoKHR.sType = VK_STRUCTURE_TYPE_MAX_ENUM;//û�ж��壬���ﶨ��Ϊ�Ƿ�ֵ
					videoEncodeH264SessionCreateInfoKHR.pNext = nullptr;
					videoEncodeH265SessionCreateInfoKHR.sType = VK_STRUCTURE_TYPE_MAX_ENUM;//û�ж��壬���ﶨ��Ϊ�Ƿ�ֵ
					videoEncodeH265SessionCreateInfoKHR.pNext = nullptr;

				}
			};


			VkVideoSessionCreateInfoKHR videoSessionCreateInfoKHR{};
			videoSessionCreateInfoKHR.sType = VK_STRUCTURE_TYPE_VIDEO_SESSION_CREATE_INFO_KHR;
			VideoSessionCreateInfoKHREXT videoSessionCreateInfoKHREXT{};
			videoSessionCreateInfoKHR.pNext = &videoSessionCreateInfoKHREXT.videoEncodeH264SessionCreateInfoKHR;
			videoSessionCreateInfoKHR.queueFamilyIndex = 0;//Ϊ������session Ҫʹ�õ�queue family index
			videoSessionCreateInfoKHR.flags = VK_VIDEO_SESSION_CREATE_PROTECTED_CONTENT_BIT_KHR;/* VkVideoSessionCreateFlagBitsKHR ���ֵλ���룬ָ��������־
			VkVideoSessionCreateFlagBitsKHR:
			VK_VIDEO_SESSION_CREATE_PROTECTED_CONTENT_BIT_KHR : ָ��������sessionʹ��protected video content
			VK_VIDEO_SESSION_CREATE_ALLOW_ENCODE_PARAMETER_OPTIMIZATIONS_BIT_KHR : ָ��ʵ�ֿ��Ի���ָ����video profile����Ϣ�Լ�ʹ�õ�video encode quality level ������дvideo session�Լ�codec-specific�������Ż�video encode operations
			VK_VIDEO_SESSION_CREATE_INLINE_QUERIES_BIT_KHR : ָ��������session������video coding�ڲ�ִ��queries

			*/
			videoSessionCreateInfoKHR.pVideoProfile = &videoProfileInfoKHR;//һ��VkVideoProfileInfoKHR ָ�룬ָ��Ҫʹ�õ�video profile
			videoSessionCreateInfoKHR.pictureFormat = VK_FORMAT_R8G8B8A8_SRGB;//VkFormat ֵָ��Ҫʹ�õ�image format.ҪΪpVideoProfile->videoCodecOperation ���Ե�picture���õ�format
			videoSessionCreateInfoKHR.maxCodedExtent = VkExtent2D{ .width = 1,.height = 1 };//Ϊ������sessionҪʹ�õı���֡��frame�������width�Լ�height
			videoSessionCreateInfoKHR.referencePictureFormat = VK_FORMAT_R8G8B8A8_SRGB;//VkFormat ֵָ��������sessionҪʹ�õĴ����PDB �е�reference picture format.
			videoSessionCreateInfoKHR.maxDpbSlots = 2;//Ϊ������sessionҪʹ�õ�DPB slots���������
			videoSessionCreateInfoKHR.maxActiveReferencePictures = 2;//Ϊ������session��һ�� video coding�����п�ʹ�õ�active reference pictures���������
			videoSessionCreateInfoKHR.pStdHeaderVersion = &extensionProperties;//Ϊ VkExtensionProperties ָ�룬��¼pVideoProfile->videoCodecOperation Ҫʹ�õı�׼��Ƶͷ�����Լ�video profile֧�ֵİ汾
			/*
			VkVideoSessionCreateInfoKHR��Ч�÷�:
			1.��� protectedMemory����δ���������������vkGetPhysicalDeviceVideoCapabilitiesKHR����pVideoProfile��ָ��video profile���ص� VkVideoCapabilitiesKHR::flags ������VK_VIDEO_CAPABILITY_PROTECTED_CONTENT_BIT_KHR����flags ���ܰ���VK_VIDEO_SESSION_CREATE_PROTECTED_CONTENT_BIT_KHR
			2.���flags ����VK_VIDEO_SESSION_CREATE_INLINE_QUERIES_BIT_KHR ����videoMaintenance1 ���뿪��
			3.pVideoProfile ������һ��֧�ֵ�video profile
			4.maxDpbSlots ����С�ڵ��ڵ���vkGetPhysicalDeviceVideoCapabilitiesKHR����pVideoProfile��ָ��video profile���ص�  VkVideoCapabilitiesKHR::maxDpbSlots
			5.maxActiveReferencePictures ����С�ڵ��ڵ���vkGetPhysicalDeviceVideoCapabilitiesKHR����pVideoProfile��ָ��video profile���ص�  VkVideoCapabilitiesKHR::maxActiveReferencePictures
			6.���maxDpbSlots ���� maxActiveReferencePictures Ϊ0������һ��ֵҲ����Ϊ0
			7.maxCodedExtent �����ڵ���vkGetPhysicalDeviceVideoCapabilitiesKHR����pVideoProfile��ָ��video profile���ص�VkVideoCapabilitiesKHR::minCodedExtent �� VkVideoCapabilitiesKHR::maxCodedExtent ֮��
			8.���pVideoProfile->videoCodecOperation ָ��һ��decode operation ��maxActiveReferencePictures ����0����referencePictureFormat ������֧�ֵ�һ��decode DPB formats���μ�����vkGetPhysicalDeviceVideoFormatPropertiesKHR ���ص� VkVideoFormatPropertiesKHR::format�����ò���pVideoFormatInfo->imageUsage �������VK_IMAGE_USAGE_VIDEO_DECODE_DPB_BIT_KHR����pVideoFormatInfo->pNetx�б������һ��VkVideoProfileListInfoKHR��VkVideoProfileListInfoKHR.pProfiles�������һ����pVideoProfileƥ���profile
			9.���pVideoProfile->videoCodecOperation ָ��һ��encode operation ��maxActiveReferencePictures ����0����referencePictureFormat ������֧�ֵ�һ��decode �Լ�encode DPB formats���μ�����vkGetPhysicalDeviceVideoFormatPropertiesKHR ���ص� VkVideoFormatPropertiesKHR::format�����ò���pVideoFormatInfo->imageUsage �������VK_IMAGE_USAGE_VIDEO_ENCODE_DPB_BIT_KHR����pVideoFormatInfo->pNetx�б������һ��VkVideoProfileListInfoKHR��VkVideoProfileListInfoKHR.pProfiles�������һ����pVideoProfileƥ���profile
			10.���pVideoProfile->videoCodecOperation ָ��һ��decode operation ����pictureFormat ������֧�ֵ�һ��decode output formats���μ�����vkGetPhysicalDeviceVideoFormatPropertiesKHR ���ص� VkVideoFormatPropertiesKHR::format�����ò���pVideoFormatInfo->imageUsage �������VK_IMAGE_USAGE_VIDEO_DECODE_DST_BIT_KHR����pVideoFormatInfo->pNetx�б������һ��VkVideoProfileListInfoKHR��VkVideoProfileListInfoKHR.pProfiles�������һ����pVideoProfileƥ���profile
			11.���pVideoProfile->videoCodecOperation ָ��һ��encode operation ����pictureFormat ������֧�ֵ�һ��encode input formats���μ�����vkGetPhysicalDeviceVideoFormatPropertiesKHR ���ص� VkVideoFormatPropertiesKHR::format�����ò���pVideoFormatInfo->imageUsage �������VK_IMAGE_USAGE_VIDEO_ENCODE_SRC_BIT_KHR����pVideoFormatInfo->pNetx�б������һ��VkVideoProfileListInfoKHR��VkVideoProfileListInfoKHR.pProfiles�������һ����pVideoProfileƥ���profile
			12.pStdHeaderVersion->extensionName ����ƥ�����vkGetPhysicalDeviceVideoCapabilitiesKHR����pVideoProfile��ָ��video profile���ص�  VkVideoCapabilitiesKHR::stdHeaderVersion.extensionName
			13.pStdHeaderVersion->specVersion ����С�ڵ��ڵ���vkGetPhysicalDeviceVideoCapabilitiesKHR����pVideoProfile��ָ��video profile���ص�  VkVideoCapabilitiesKHR::stdHeaderVersion.specVersion
			14.���pVideoProfile->videoCodecOperation ΪVK_VIDEO_CODEC_OPERATION_ENCODE_H264_BIT_KHR����pNext�а���һ��VkVideoEncodeH264SessionCreateInfoKHR����VkVideoEncodeH264SessionCreateInfoKHR.maxLevelIdc ����С�ڵ��ڵ���vkGetPhysicalDeviceVideoCapabilitiesKHR����pVideoProfile��ָ��video profile���ص� VkVideoEncodeH264CapabilitiesKHR::maxLevelIdc
			15.���pVideoProfile->videoCodecOperation ΪVK_VIDEO_CODEC_OPERATION_ENCODE_H265_BIT_KHR����pNext�а���һ��VkVideoEncodeH265SessionCreateInfoKHR����VkVideoEncodeH265SessionCreateInfoKHR.maxLevelIdc ����С�ڵ��ڵ���vkGetPhysicalDeviceVideoCapabilitiesKHR����pVideoProfile��ָ��video profile���ص� VkVideoEncodeH265CapabilitiesKHR::maxLevelIdc
			*/


			//�ýӿ�ʹ�õ�һЩ����ע����Ϣ��p3425
			vkCreateVideoSessionKHR(device, &videoSessionCreateInfoKHR, nullptr, &videoSessionKHR);

		}

		//Destroying a Video Session �μ�p3432
		{
			//����VkVideoSessionKHR
			vkDestroyVideoSessionKHR(device, videoSessionKHR, nullptr);
			/*
			vkDestroyVideoSessionKHR��Ч�÷�:
			1.���õ�videoSession ���ύ������������ִ��
			2.������� videoSession ʱ�ṩ�� VkAllocationCallbacks��������Ҳ��Ҫ�ṩһ�����ݵ�callback����
			3.������� videoSession ʱû���ṩ VkAllocationCallbacks����pAllocator ����ΪNULL

			*/
		}


		//Video Session Memory Association  �μ�p3432
		{
			/*
			�ڴ����� video session����ʹ�ø�video session������Ƶ�������֮ǰ����Ҫ��video session �󶨵��ڴ�����ϡ��ڴ�ķ����Ƿ���ġ�session ���ܸ���һ���޷�������ֵ��memory binding�������ڴ���ҿ��ܽ��ж�Ρ�

			*/


			//��ѯvideo session���ڴ�����
			uint32_t videomSessionMemoryRequirementsCount = 0;
			std::vector<VkVideoSessionMemoryRequirementsKHR> videoSessionMemoryRequirementsKHRs{};
			vkGetVideoSessionMemoryRequirementsKHR(device, videoSessionKHR, &videomSessionMemoryRequirementsCount, nullptr);
			videoSessionMemoryRequirementsKHRs.resize(videomSessionMemoryRequirementsCount);
			vkGetVideoSessionMemoryRequirementsKHR(device, videoSessionKHR, &videomSessionMemoryRequirementsCount, videoSessionMemoryRequirementsKHRs.data());//����ɹ�������һ��Ԫ��

			VkVideoSessionMemoryRequirementsKHR& videoSessionMemoryRequirementsKHR = videoSessionMemoryRequirementsKHRs[0];
			videoSessionMemoryRequirementsKHR.sType = VK_STRUCTURE_TYPE_VIDEO_SESSION_MEMORY_REQUIREMENTS_KHR;
			videoSessionMemoryRequirementsKHR.pNext = nullptr;
			videoSessionMemoryRequirementsKHR.memoryBindIndex = 0;//Ϊ memory binding������
			videoSessionMemoryRequirementsKHR.memoryRequirements = VkMemoryRequirements{ .size = 1024, .alignment = 16, .memoryTypeBits = 0x0000000F }/*��������һ����Ч��VkMemoryRequirements*/;// VkMemoryRequirements ֵ��ָ��memoryBindIndex ��ָ��memory binding������ڴ�����



			//��memory��video session
			VkBindVideoSessionMemoryInfoKHR bindVideoSessionMemoryInfoKHR{};
			bindVideoSessionMemoryInfoKHR.sType = VK_STRUCTURE_TYPE_BIND_VIDEO_SESSION_MEMORY_INFO_KHR;
			bindVideoSessionMemoryInfoKHR.pNext = nullptr;
			bindVideoSessionMemoryInfoKHR.memory = VkDeviceMemory{/*��������һ����Ч��VkDeviceMemory*/ };//Ϊ�����Ҫ�󶨵�video session�� memoryBindIndex��ָ��memory binding���豸�ڴ�
			bindVideoSessionMemoryInfoKHR.memoryBindIndex = 0;//ΪҪ�󶨵� memory binding������
			bindVideoSessionMemoryInfoKHR.memoryOffset = 0;//Ϊmemory ��Ҫ�󶨵��ڴ����ʼ�ֽ�ƫ����
			bindVideoSessionMemoryInfoKHR.memorySize = 1;//Ϊmemory ��Ҫ�󶨵Ĵ�memoryOffset��ʼ���ڴ��ֽڷ�Χ
			/*
			VkBindVideoSessionMemoryInfoKHR��Ч�÷�:
			1.memoryOffset ����С�ڵ���memory�Ĵ�С
			2.memorySize ����С�ڵ���memory�Ĵ�С��ȥmemoryOffset
			*/


			vkBindVideoSessionMemoryKHR(device, videoSessionKHR, 1, &bindVideoSessionMemoryInfoKHR);
			/*
			vkBindVideoSessionMemoryKHR��Ч�÷�:
			1.pBindSessionMemoryInfos ���κ�Ԫ�ص�memoryBindIndex ��ָ�� memory binding�����Ѿ��󶨵�һ���ڴ����
			2.pBindSessionMemoryInfos ��ÿ��Ԫ�ص�memoryBindIndex ��pBindSessionMemoryInfos �б�����Ψһ��
			3.pBindSessionMemoryInfos ��ÿ��Ԫ�ر�����һ����Ӧ��VkMemoryRequirements
			4.���pBindSessionMemoryInfos��һ��Ԫ����һ����Ӧ��VkMemoryRequirements�����Ԫ�ص�memory�������ʹ�����Ӧ��VkMemoryRequirements��memoryTypeBits�����ʹ���
			5.���pBindSessionMemoryInfos��һ��Ԫ����һ����Ӧ��VkMemoryRequirements�����Ԫ�ص�memoryOffset ���������Ӧ��VkMemoryRequirements��alignment��������
			6.���pBindSessionMemoryInfos��һ��Ԫ����һ����Ӧ��VkMemoryRequirements�����Ԫ�ص�memorySize ����������Ӧ��VkMemoryRequirements��size
			*/


		}
	}



	//Video Profile Compatibility  �μ�p3437
	{
		/*
		�� video session ��ʹ�õĺ� video profile ���ݵ���Դ�Լ�queryPool�Ĵ�����Ҫ����һ��������

		��VkBuffer:
			 VkBufferCreateInfo::pNext ����һ���� pProfiles�к���һ��Ԫ��ƥ��video profile�� VkVideoProfileListInfoKHR ��VkBufferCreateInfo::usage ����VK_BUFFER_USAGE_VIDEO_DECODE_SRC_BIT_KHR ��VK_BUFFER_USAGE_VIDEO_DECODE_DST_BIT_KHR�� VK_BUFFER_USAGE_VIDEO_ENCODE_SRC_BIT_KHR�� ����VK_BUFFER_USAGE_VIDEO_ENCODE_DST_BIT_KHR�� ���� VkBufferCreateInfo::flags �� VK_BUFFER_CREATE_VIDEO_PROFILE_INDEPENDENT_BIT_KHR
		��VkImage
			 VkImageCreateInfo::pNext ����һ���� pProfiles�к���һ��Ԫ��ƥ��video profile�� VkVideoProfileListInfoKHR , VkImageCreateInfo::usage���� VK_IMAGE_USAGE_VIDEO_DECODE_SRC_BIT_KHR��VK_IMAGE_USAGE_VIDEO_DECODE_DST_BIT_KHR��VK_IMAGE_USAGE_VIDEO_DECODE_DPB_BIT_KHR��VK_IMAGE_USAGE_VIDEO_ENCODE_SRC_BIT_KHR��VK_IMAGE_USAGE_VIDEO_ENCODE_DST_BIT_KHR ����VK_IMAGE_USAGE_VIDEO_ENCODE_DPB_BIT_KHR��
			 ���� VkImageCreateInfo::flags ��  VK_IMAGE_CREATE_VIDEO_PROFILE_INDEPENDENT_BIT_KHR.Ȼ��VkImageCreateInfo�� format ��flags��imageType��tilingҪ����vkGetPhysicalDeviceVideoFormatPropertiesKHR���ص�VkVideoFormatPropertiesKHR�е���Ӧֵ��usageҪ����������Ӧֵ�С�
		��VkImageView:
			ֻҪ������VkImage���ݼ���
		��VkQueryPool:
			VkQueryPoolCreateInfo::pNext ����һ���� pProfiles�к���һ��Ԫ��ƥ��video profile�� VkVideoProfileListInfoKHR ��VkQueryPoolCreateInfo::queryType ����VK_QUERY_TYPE_RESULT_STATUS_ONLY_KHR ���� VK_QUERY_TYPE_VIDEO_ENCODE_FEEDBACK_KHR
		*/
	}

	//Video Session Parameters �μ�p3438
	{
		/*
		video session parameters �������ʹ����video session��Ԥ����codec-specific�����Ķ����ܹ��ڼ�¼video coding ������command bufferʱʹ�õĲ���������

		�洢��video session parameters �����еĲ������ɸı䣬Ҫ�����µĲ�������Ҫ���� vkUpdateVideoSessionParametersKHR ��ÿ����һ�Σ����ڲ� update sequence counter����1
	
		���ڲ�ͬ��video codec operation��video session parameters �д洢�Ĳ���������ͬ��
		*/


		VkVideoSessionParametersKHR videoSessionParametersKHR{};

		// Creating Video Session Parameters  �μ�p3439
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
					videoDecodeAV1SessionParametersCreateInfoKHR.sType = VK_STRUCTURE_TYPE_MAX_ENUM;//û�ж��壬���ﶨ��Ϊ�Ƿ�ֵ
					videoDecodeAV1SessionParametersCreateInfoKHR.pNext = nullptr;
					videoDecodeH264SessionParametersCreateInfoKHR.sType = VK_STRUCTURE_TYPE_VIDEO_DECODE_H264_SESSION_PARAMETERS_CREATE_INFO_KHR;
					videoDecodeH264SessionParametersCreateInfoKHR.pNext = nullptr;
					videoDecodeH265SessionParametersCreateInfoKHR.sType = VK_STRUCTURE_TYPE_VIDEO_DECODE_H265_SESSION_PARAMETERS_CREATE_INFO_KHR;
					videoDecodeH265SessionParametersCreateInfoKHR.pNext = nullptr;
					videoEncodeH264SessionParametersCreateInfoKHR.sType = VK_STRUCTURE_TYPE_MAX_ENUM;//û�ж��壬���ﶨ��Ϊ�Ƿ�ֵ
					videoEncodeH264SessionParametersCreateInfoKHR.pNext = nullptr;
					videoEncodeH265SessionParametersCreateInfoKHR.sType = VK_STRUCTURE_TYPE_MAX_ENUM;//û�ж��壬���ﶨ��Ϊ�Ƿ�ֵ
					videoEncodeH265SessionParametersCreateInfoKHR.pNext = nullptr;
					videoEncodeQualityLevelInfoKHR.sType = VK_STRUCTURE_TYPE_MAX_ENUM;//û�ж��壬���ﶨ��Ϊ�Ƿ�ֵ
					videoEncodeQualityLevelInfoKHR.pNext = nullptr;


				}
			};


			VkVideoSessionParametersCreateInfoKHR videoSessionParametersCreateInfoKHR{};//�ýṹ�����videoSession�Ķ�Ӧvideo codec operation ��ͬ�����������ڸýṹ���еĲ�������һЩ���ƣ������ *** p3445 - p3447 ���򵥽�������װ��pNext��VkVideoEncodeH265SessionParametersCreateInfoKHR����ز�������װ��videoSessionParametersTemplate�в��ظ��Ĳ�����
			videoSessionParametersCreateInfoKHR.sType = VK_STRUCTURE_TYPE_VIDEO_SESSION_PARAMETERS_CREATE_INFO_KHR;
			VideoSessionParametersCreateInfoKHREXT videoSessionParametersCreateInfoKHREXT{};
			videoSessionParametersCreateInfoKHR.pNext = &videoSessionParametersCreateInfoKHREXT.videoDecodeAV1SessionParametersCreateInfoKHR;
			videoSessionParametersCreateInfoKHR.flags = 0;//����δ��ʹ��
			videoSessionParametersCreateInfoKHR.videoSession = VkVideoSessionKHR{/*��������һ����Ч��VkVideoSessionKHR*/ };//Ϊvideo session parameters Ҫ���ĸ�video session����
			videoSessionParametersCreateInfoKHR.videoSessionParametersTemplate = VkVideoSessionParametersKHR{/*��������һ����Ч��VkVideoSessionParametersKHR*/ };//�����ΪVK_NULL_HANDLE�������һ����Ч��VkVideoSessionParametersKHR�����ڽ��ö����еĲ�����Ϊģ�崴��һ���µ�video session parameters VkVideoSessionParametersKHR����
			/*
			VkVideoSessionParametersCreateInfoKHR��Ч�÷�:
			1.���videoSessionParametersTemplate ��ΪVK_NULL_HANDLE����1��������Ƕ�videoSession ������
																	   ��2�����videoSession ��һ��encode operation ��������videoSession��qualityLevel �������videoSessionParametersTemplate����ʱ��video encode quality level
			2.���videoSession ��video codec operation VK_VIDEO_CODEC_OPERATION_DECODE_H264_BIT_KHR��������1��pNext�б������һ��VkVideoDecodeH264SessionParametersCreateInfoKHR
																										   ��2��pNext��VkVideoDecodeH264SessionParametersCreateInfoKHR��spsAddList��Ԫ����������С�ڵ�����maxStdSPSCount
																										   ��3��pNext��VkVideoDecodeH264SessionParametersCreateInfoKHR��ppsAddList��Ԫ����������С�ڵ�����maxStdPPSCount
			3.���videoSession ��video codec operation VK_VIDEO_CODEC_OPERATION_DECODE_H265_BIT_KHR��������1��pNext�б������һ��VkVideoDecodeH265SessionParametersCreateInfoKHR
																										   ��2��pNext��VkVideoDecodeH265SessionParametersCreateInfoKHR��vpsAddList��Ԫ����������С�ڵ�����maxStdVPSCount
																										   ��3��pNext��VkVideoDecodeH265SessionParametersCreateInfoKHR��spsAddList��Ԫ����������С�ڵ�����maxStdSPSCount
																										   ��4��pNext��VkVideoDecodeH265SessionParametersCreateInfoKHR��ppsAddList��Ԫ����������С�ڵ�����maxStdPPSCount
			4.���videoSession ��video codec operation VK_VIDEO_CODEC_OPERATION_DECODE_AV1_BIT_KHR�������� ��1��videoSessionParametersTemplate ����ΪVK_NULL_HANDLE
																										   ��2��pNext�б������һ��VkVideoDecodeAV1SessionParametersCreateInfoKHR
			5.���videoSession ��video codec operation VK_VIDEO_CODEC_OPERATION_ENCODE_H264_BIT_KHR��������1��pNext�б������һ��VkVideoEncodeH264SessionParametersCreateInfoKHR
																										   ��2��pNext��VkVideoEncodeH264SessionParametersCreateInfoKHR��spsAddList��Ԫ����������С�ڵ�����maxStdSPSCount
																										   ��3��pNext��VkVideoEncodeH264SessionParametersCreateInfoKHR��ppsAddList��Ԫ����������С�ڵ�����maxStdPPSCount
			6.���videoSession ��video codec operation VK_VIDEO_CODEC_OPERATION_ENCODE_H265_BIT_KHR��������1��pNext�б������һ��VkVideoEncodeH265SessionParametersCreateInfoKHR
																										   ��2��pNext��VkVideoEncodeH265SessionParametersCreateInfoKHR��vpsAddList��Ԫ����������С�ڵ�����maxStdVPSCount
																										   ��3��pNext��VkVideoEncodeH265SessionParametersCreateInfoKHR��spsAddList��Ԫ����������С�ڵ�����maxStdSPSCount
																										   ��4��pNext��VkVideoEncodeH265SessionParametersCreateInfoKHR��ppsAddList��Ԫ����������С�ڵ�����maxStdPPSCount
																										   ��5����ÿ��ppsAddList�е�Ԫ�أ���num_tile_columns_minus1 ����С�ڵ��� vkGetPhysicalDeviceVideoCapabilitiesKHR ����videoSession ����ʱ��video profile ���� VkVideoEncodeH265CapabilitiesKHR::maxTiles.width
																										   ��6����ÿ��ppsAddList�е�Ԫ�أ���num_tile_rows_minus1 ����С�ڵ��� vkGetPhysicalDeviceVideoCapabilitiesKHR ����videoSession ����ʱ��video profile ���� VkVideoEncodeH265CapabilitiesKHR::maxTiles.height

			*/



			//����  �����������иò���������ݲ�ͬ��video codec operationװ������Щ���������װ���  *** p3441 - p3443
			vkCreateVideoSessionParametersKHR(device, &videoSessionParametersCreateInfoKHR, nullptr, &videoSessionParametersKHR);

		}


		//Destroying Video Session Parameters  �μ�p3451
		{
			//����
			vkDestroyVideoSessionParametersKHR(device, videoSessionParametersKHR, nullptr);
			/*
			vkDestroyVideoSessionParametersKHR��Ч�÷�:
			1.���õ�videoSessionParameters ���ύ������������ִ��
			2.������� videoSessionParameters ʱ�ṩ�� VkAllocationCallbacks��������Ҳ��Ҫ�ṩһ�����ݵ�callback����
			3.������� videoSessionParameters ʱû���ṩ VkAllocationCallbacks����pAllocator ����ΪNULL
			*/
		}


		// Updating Video Session Parameters  �μ�p3452
		{
			//����

			VkVideoSessionParametersUpdateInfoKHR videoSessionParametersUpdateInfoKHR{};
			videoSessionParametersUpdateInfoKHR.sType = VK_STRUCTURE_TYPE_VIDEO_SESSION_PARAMETERS_CREATE_INFO_KHR;
			videoSessionParametersUpdateInfoKHR.pNext = nullptr;//���԰���VkVideoDecodeH264SessionParametersAddInfoKHR, VkVideoDecodeH265SessionParametersAddInfoKHR, VkVideoEncodeH264SessionParametersAddInfoKHR, ���� VkVideoEncodeH265SessionParametersAddInfoKHR
			videoSessionParametersUpdateInfoKHR.updateSequenceCount = 1;//ΪΪ��video session parameters ���õ��µ� update sequence count ֵ

			//������ִ�гɹ���  videoSessionParameters�е� update sequence counter�ͻ��ΪpUpdateInfo->updateSequenceCount �����pUpdateInfo->pNext �а���һЩ��Ĳ���������Щ��������ӵ���videoSessionParameters�����У��������ʲô����ô��Ӹ���videoSessionParameters���Ե�codec-specific operation��������������
			vkUpdateVideoSessionParametersKHR(device, videoSessionParametersKHR/* videoSessionParameters*/, &videoSessionParametersUpdateInfoKHR/*pUpdateInfo*/);
			/*
			vkUpdateVideoSessionParametersKHR��Ч�÷�:
			1.pUpdateInfo->updateSequenceCount ������ڵ�ǰvideoSessionParameters�� update sequence counter��1
			2.���videoSessionParameters ��video codec operation VK_VIDEO_CODEC_OPERATION_DECODE_H264_BIT_KHR��������1�����pUpdateInfo->pNext�а���һ��VkVideoDecodeH264SessionParametersAddInfoKHR����ǰvideoSessionParameters �в��ܰ���һ��seq_parameter_set_id ƥ��VkVideoDecodeH264SessionParametersAddInfoKHR::pStdSPSs ���κ�Ԫ�ص� StdVideoH264SequenceParameterSetʵ��
																													 ��2����ǰvideoSessionParameters �д洢�� StdVideoH264SequenceParameterSetʵ�����������pUpdateInfo->pNext�е�VkVideoDecodeH264SessionParametersAddInfoKHR::stdSPSCount ����С�ڵ��ڴ���videoSessionParameters �� VkVideoDecodeH264SessionParametersCreateInfoKHR::maxStdSPSCount
																													 ��3�����pUpdateInfo->pNext�а���һ��VkVideoDecodeH264SessionParametersAddInfoKHR����ǰvideoSessionParameters �в��ܰ���һ��seq_parameter_set_id �Լ�pic_parameter_set_id ��ƥ��VkVideoDecodeH264SessionParametersAddInfoKHR::pStdPPSs ���κ�Ԫ�ص� StdVideoH264PictureParameterSetʵ��
																													 ��4����ǰvideoSessionParameters �д洢�� StdVideoH264PictureParameterSetʵ�����������pUpdateInfo->pNext�е�VkVideoDecodeH264SessionParametersAddInfoKHR::stdPPSCount ����С�ڵ��ڴ���videoSessionParameters �� VkVideoDecodeH264SessionParametersCreateInfoKHR::maxStdPPSCount

			3.���videoSessionParameters ��video codec operation VK_VIDEO_CODEC_OPERATION_DECODE_H265_BIT_KHR��������1�����pUpdateInfo->pNext�а���һ��VkVideoDecodeH265SessionParametersAddInfoKHR����ǰvideoSessionParameters �в��ܰ���һ��vps_video_parameter_set_id ƥ��VkVideoDecodeH265SessionParametersAddInfoKHR::pStdVPSs ���κ�Ԫ�ص� StdVideoH265VideoParameterSetʵ��
																													 ��2����ǰvideoSessionParameters �д洢�� StdVideoH265VideoParameterSetʵ�����������pUpdateInfo->pNext�е�VkVideoDecodeH265SessionParametersAddInfoKHR::stdVPSCount ����С�ڵ��ڴ���videoSessionParameters �� VkVideoDecodeH265SessionParametersCreateInfoKHR::maxStdVPSCount
																													 ��3�����pUpdateInfo->pNext�а���һ��VkVideoDecodeH265SessionParametersAddInfoKHR����ǰvideoSessionParameters �в��ܰ���һ��sps_video_parameter_set_id �� sps_seq_parameter_set_id ��ƥ��VkVideoDecodeH265SessionParametersAddInfoKHR::pStdSPSs ���κ�Ԫ�ص� StdVideoH265SequenceParameterSetʵ��
																													 ��4����ǰvideoSessionParameters �д洢�� StdVideoH265SequenceParameterSetʵ�����������pUpdateInfo->pNext�е�VkVideoDecodeH265SessionParametersAddInfoKHR::stdSPSCount ����С�ڵ��ڴ���videoSessionParameters �� VkVideoDecodeH265SessionParametersCreateInfoKHR::maxStdSPSCount
																													 ��5�����pUpdateInfo->pNext�а���һ��VkVideoDecodeH265SessionParametersAddInfoKHR����ǰvideoSessionParameters �в��ܰ���һ��sps_video_parameter_set_id, pps_seq_parameter_set_id, �Լ� pps_pic_parameter_set_id ȫ��ƥ��VkVideoDecodeH265SessionParametersAddInfoKHR::pStdPPSs ���κ�Ԫ�ص� StdVideoH265PictureParameterSetʵ��
																													 ��6����ǰvideoSessionParameters �д洢�� StdVideoH265PictureParameterSetʵ�����������pUpdateInfo->pNext�е�VkVideoDecodeH265SessionParametersAddInfoKHR::stdPPSCount ����С�ڵ��ڴ���videoSessionParameters �� VkVideoDecodeH265SessionParametersCreateInfoKHR::maxStdPPSCount

			4.���videoSessionParameters ������video codec operationΪ VK_VIDEO_CODEC_OPERATION_DECODE_AV1_BIT_KHR����
			5.���videoSessionParameters ��video codec operation VK_VIDEO_CODEC_OPERATION_ENCODE_H264_BIT_KHR��������1�����pUpdateInfo->pNext�а���һ��VkVideoEncodeH264SessionParametersAddInfoKHR����ǰvideoSessionParameters �в��ܰ���һ��seq_parameter_set_id ƥ��VkVideoEncodeH264SessionParametersAddInfoKHR::pStdSPSs ���κ�Ԫ�ص� StdVideoH264SequenceParameterSetʵ��
																													 ��2����ǰvideoSessionParameters �д洢�� StdVideoH264SequenceParameterSetʵ�����������pUpdateInfo->pNext�е�VkVideoEncodeH264SessionParametersAddInfoKHR::stdSPSCount ����С�ڵ��ڴ���videoSessionParameters �� VkVideoEncodeH264SessionParametersCreateInfoKHR::maxStdSPSCount
																													 ��3�����pUpdateInfo->pNext�а���һ��VkVideoEncodeH264SessionParametersAddInfoKHR����ǰvideoSessionParameters �в��ܰ���һ��seq_parameter_set_id �Լ�pic_parameter_set_id ��ƥ��VkVideoEncodeH264SessionParametersAddInfoKHR::pStdPPSs ���κ�Ԫ�ص� StdVideoH264PictureParameterSetʵ��
																													 ��4����ǰvideoSessionParameters �д洢�� StdVideoH264PictureParameterSetʵ�����������pUpdateInfo->pNext�е�VkVideoEncodeH264SessionParametersAddInfoKHR::stdPPSCount ����С�ڵ��ڴ���videoSessionParameters �� VkVideoEncodeH264SessionParametersCreateInfoKHR::maxStdPPSCount
			6.���videoSessionParameters ��video codec operation VK_VIDEO_CODEC_OPERATION_ENCODE_H265_BIT_KHR��������1�����pUpdateInfo->pNext�а���һ��VkVideoEncodeH265SessionParametersAddInfoKHR����ǰvideoSessionParameters �в��ܰ���һ��vps_video_parameter_set_id ƥ��VkVideoDecodeH265SessionParametersAddInfoKHR::pStdVPSs ���κ�Ԫ�ص� StdVideoH265VideoParameterSetʵ��
																													 ��2����ǰvideoSessionParameters �д洢�� StdVideoH265VideoParameterSetʵ�����������pUpdateInfo->pNext�е�VkVideoEncodeH265SessionParametersAddInfoKHR::stdVPSCount ����С�ڵ��ڴ���videoSessionParameters �� VkVideoEncodeH265SessionParametersCreateInfoKHR::maxStdVPSCount
																													 ��3�����pUpdateInfo->pNext�а���һ��VkVideoEncodeH265SessionParametersAddInfoKHR����ǰvideoSessionParameters �в��ܰ���һ��sps_video_parameter_set_id �� sps_seq_parameter_set_id ��ƥ��VkVideoEncodeH265SessionParametersAddInfoKHR::pStdSPSs ���κ�Ԫ�ص� StdVideoH265SequenceParameterSetʵ��
																													 ��4����ǰvideoSessionParameters �д洢�� StdVideoH265SequenceParameterSetʵ�����������pUpdateInfo->pNext�е�VkVideoEncodeH265SessionParametersAddInfoKHR::stdSPSCount ����С�ڵ��ڴ���videoSessionParameters �� VkVideoEncodeH265SessionParametersCreateInfoKHR::maxStdSPSCount
																													 ��5�����pUpdateInfo->pNext�а���һ��VkVideoEncodeH265SessionParametersAddInfoKHR����ǰvideoSessionParameters �в��ܰ���һ��sps_video_parameter_set_id, pps_seq_parameter_set_id, �Լ� pps_pic_parameter_set_id ȫ��ƥ��VkVideoEncodeH265SessionParametersAddInfoKHR::pStdPPSs ���κ�Ԫ�ص� StdVideoH265PictureParameterSetʵ��
																													 ��6����ǰvideoSessionParameters �д洢�� StdVideoH265PictureParameterSetʵ�����������pUpdateInfo->pNext�е�VkVideoEncodeH265SessionParametersAddInfoKHR::stdPPSCount ����С�ڵ��ڴ���videoSessionParameters �� VkVideoEncodeH265SessionParametersCreateInfoKHR::maxStdPPSCount
																													 ��7�����pUpdateInfo->pNext�а���һ��VkVideoEncodeH265SessionParametersAddInfoKHR����ÿ��VkVideoEncodeH265SessionParametersAddInfoKHR::pStdPPSs�е�Ԫ�أ�����num_tile_columns_minus1 ����С�ڵ��� vkGetPhysicalDeviceVideoCapabilitiesKHR ����videoSessionParameters ����ʱ��video profile ���� VkVideoEncodeH265CapabilitiesKHR::maxTiles.width
																													 ��8�����pUpdateInfo->pNext�а���һ��VkVideoEncodeH265SessionParametersAddInfoKHR����ÿ��VkVideoEncodeH265SessionParametersAddInfoKHR::pStdPPSs�е�Ԫ�أ�����num_tile_rows_minus1 ����С�ڵ��� vkGetPhysicalDeviceVideoCapabilitiesKHR ����videoSessionParameters ����ʱ��video profile ���� VkVideoEncodeH265CapabilitiesKHR::maxTiles.height

			*/



		}
	}

	VkCommandBuffer commandBuffer{/*��������һ����Ч��VkCommandBuffer*/};


	//Video Coding Scope  �μ�p3459
	{
		/*
		Ӧ��ֻ�ܽ�video coding commands ��¼��video coding scope ��
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
				videoEncodeH264GopRemainingFrameInfoKHR.sType = VK_STRUCTURE_TYPE_MAX_ENUM;//û�ж������Զ���Ϊ�Ƿ�ֵ
				videoEncodeH264GopRemainingFrameInfoKHR.pNext = nullptr;
				videoEncodeH264RateControlInfoKHR.sType = VK_STRUCTURE_TYPE_MAX_ENUM;//û�ж������Զ���Ϊ�Ƿ�ֵ
				videoEncodeH264RateControlInfoKHR.pNext = nullptr;
				videoEncodeH265GopRemainingFrameInfoKHR.sType = VK_STRUCTURE_TYPE_MAX_ENUM;//û�ж������Զ���Ϊ�Ƿ�ֵ
				videoEncodeH265GopRemainingFrameInfoKHR.pNext = nullptr;
				videoEncodeH265RateControlInfoKHR.sType = VK_STRUCTURE_TYPE_MAX_ENUM;//û�ж������Զ���Ϊ�Ƿ�ֵ
				videoEncodeH265RateControlInfoKHR.pNext = nullptr;
				videoEncodeRateControlInfoKHR.sType = VK_STRUCTURE_TYPE_MAX_ENUM;//û�ж������Զ���Ϊ�Ƿ�ֵ
				videoEncodeRateControlInfoKHR.pNext = nullptr;
			}
		};


		//��ʼһ�� Video Coding Scope  �μ�p3459
		VkVideoBeginCodingInfoKHR videoBeginCodingInfoKHR{};
		videoBeginCodingInfoKHR.sType = VK_STRUCTURE_TYPE_VIDEO_BEGIN_CODING_INFO_KHR;
		VideoBeginCodingInfoKHREXT videoBeginCodingInfoKHREXT{};
		videoBeginCodingInfoKHR.pNext = &videoBeginCodingInfoKHREXT.videoEncodeH264GopRemainingFrameInfoKHR;//���԰���VkVideoEncodeRateControlInfoKHR ��ָ�������ı������ʵ����ı䵱ǰ���õı�������
		videoBeginCodingInfoKHR.flags = 0;//����δ��ʹ��
		videoBeginCodingInfoKHR.videoSession = VkVideoSessionKHR{/*��������һ����Ч��VkVideoSessionKHR*/ };//ָ���󶨵����ڴ���video commands�� video session
		videoBeginCodingInfoKHR.videoSessionParameters = VkVideoSessionParametersKHR{/*��������һ����Ч��VkVideoSessionParametersKHR*/ };//ΪVK_NULL_HANDLE���� VkVideoSessionParametersKHR�����ָ���󶨵����ڴ���video commands�� VkVideoSessionParametersKHR�����ΪVK_NULL_HANDLE����˵�������κ� video session parameters
		videoBeginCodingInfoKHR.referenceSlotCount = 1;// pReferenceSlots ��Ԫ�ظ���
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
					videoDecodeAV1DpbSlotInfoKHR.sType = VK_STRUCTURE_TYPE_MAX_ENUM;//û�ж����������ﶨ��Ϊ�Ƿ�ֵ
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
			videoReferenceSlotInfoKHR.slotIndex = 0;//Ϊ DPB slot����������һ������
			VkVideoPictureResourceInfoKHR videoPictureResourceInfoKHR{};
			{
				videoPictureResourceInfoKHR.sType = VK_STRUCTURE_TYPE_VIDEO_PICTURE_RESOURCE_INFO_KHR;
				videoPictureResourceInfoKHR.pNext = nullptr;
				videoPictureResourceInfoKHR.imageViewBinding = VkImageView{/*��������һ����Ч��VkImageView*/ };
				videoPictureResourceInfoKHR.baseArrayLayer = 0;
				videoPictureResourceInfoKHR.codedExtent = VkExtent2D{ .width = 1,.height = 1 }/*��������һ����Ч��VkExtent2D*/;
				videoPictureResourceInfoKHR.codedOffset = VkOffset2D{ .x = 0,.y = 0 }/*��������һ����Ч��VkOffset2D*/;
			}
			videoReferenceSlotInfoKHR.pPictureResource = &videoPictureResourceInfoKHR;//ΪNULL���� VkVideoPictureResourceInfoKHR ָ�룬����������slotIndex�� video picture resource
		}
		videoBeginCodingInfoKHR.pReferenceSlots = &videoReferenceSlotInfoKHR;//һ�� VkVideoReferenceSlotInfoKHR ����ָ�룬ָ������ȷ�� bound reference picture resources����Ϣ�Լ�������ĳ�ʼ�� DPB slot ����
		/*
		VkVideoBeginCodingInfoKHR��Ч�÷�:
		1.videoSession ������memory bindings��ͨ��vkGetVideoSessionMemoryRequirementsKHR ���صģ���������ڴ����
		2.ÿ��pReferenceSlots ��ָ���ķǸ�VkVideoReferenceSlotInfoKHR::slotIndex ����С�ڴ���videoSession�� VkVideoSessionCreateInfoKHR::maxDpbSlots ָ�������DPB����
		3.ÿ��pReferenceSlots ��ָ���ķ�NULL VkVideoReferenceSlotInfoKHR::pPictureResource ������pReferenceSlots ����Ψһ��
		4.���pReferenceSlots ���κ�Ԫ�ص�pPictureResource ��ΪNULL����1����pPictureResource->imageViewBinding ��ָ��VkImageView �������videoSession ����ʱ���video profile
		��2����pPictureResource->imageViewBinding ��ָ��VkImageView ����ƥ��videoSession ����ʱ���VkVideoSessionCreateInfoKHR::referencePictureFormat
		��3����Ԫ�ص�codedOffset ����ΪcodedOffsetGranularity����p3464����������
		��4����Ԫ�ص�codedExtent ������videoSession����ʱ���VkVideoSessionCreateInfoKHR::minCodedExtent �� VkVideoSessionCreateInfoKHR::maxCodedExtent ֮��
		5.���VkVideoCapabilitiesKHR::flags ������VK_VIDEO_CAPABILITY_SEPARATE_REFERENCE_IMAGES_BIT_KHR������vkGetPhysicalDeviceVideoCapabilitiesKHR����videoSession����ʱ��video profile���صģ���������pReferenceSlotsԪ���е�pPictureResource->imageViewBinding ��ΪVK_NULL_HANDLE�ı����ͬһ��VkImage�ϴ���
		6.���videoSession ��һ��decode operation ���κ�pReferenceSlots��Ԫ�ص�slotIndex ��Ա���Ǹ���������pPictureResource->imageViewBinding ��ָ��VkImageView������VK_IMAGE_USAGE_VIDEO_DECODE_DPB_BIT_KHR ����
		7.���videoSession ��һ��encode operation ���κ�pReferenceSlots��Ԫ�ص�slotIndex ��Ա���Ǹ���������pPictureResource->imageViewBinding ��ָ��VkImageView������VK_IMAGE_USAGE_VIDEO_ENCODE_DPB_BIT_KHR ����
		8.���videoSession ��һ��video codec operation VK_VIDEO_CODEC_OPERATION_DECODE_H264_BIT_KHR , VK_VIDEO_CODEC_OPERATION_DECODE_H265_BIT_KHR ,VK_VIDEO_CODEC_OPERATION_DECODE_AV1_BIT_KHR ,VK_VIDEO_CODEC_OPERATION_ENCODE_H264_BIT_KHR  ���� VK_VIDEO_CODEC_OPERATION_ENCODE_H265_BIT_KHR ��������videoSessionParameters ����ΪVK_NULL_HANDLE
		9.���videoSessionParameters ��ΪVK_NULL_HANDLE����������ڴ���ʱָ����VkVideoSessionParametersCreateInfoKHR::videoSession Ϊ pBeginInfo->videoSession����

		*/


		//��������ú��һЩ���������p3459
		vkCmdBeginVideoCodingKHR(commandBuffer, &videoBeginCodingInfoKHR);
		/*
		vkCmdBeginVideoCodingKHR��Ч�÷�:
		1.commandBuffer���ڵ�VkCommandPool�Ķ��������֧��pBeginInfo->videoSession ����ʱ��video codec operation����vkGetPhysicalDeviceQueueFamilyProperties2 ���ص�VkQueueFamilyVideoPropertiesKHR::videoCodecOperations
		2.����������ǲ����ɼ����queries
		3.���commandBuffer��unprotected command buffer����protectedNoFault��֧�֣���pBeginInfo->videoSession ������VK_VIDEO_SESSION_CREATE_PROTECTED_CONTENT_BIT_KHR ����
		4.���commandBuffer��protected command buffer����protectedNoFault��֧�֣���pBeginInfo->videoSession ������VK_VIDEO_SESSION_CREATE_PROTECTED_CONTENT_BIT_KHR ����
		5.���commandBuffer��unprotected command buffer����protectedNoFault֧�֣���pBeginInfo->pReferenceSlots �е��κ�Ԫ�ص�pPictureResource ��ΪNULL�����Ԫ�ص�pPictureResource->imageViewBinding ����ָ��һ����protected image �ϴ�����VkImageView
		6.���commandBuffer��protected command buffer����protectedNoFault֧�֣���pBeginInfo->pReferenceSlots �е��κ�Ԫ�ص�pPictureResource ��ΪNULL�����Ԫ�ص�pPictureResource->imageViewBinding ����ָ��һ����protected image �ϴ�����VkImageView
		7.����κ�pBeginInfo->pReferenceSlots�е�Ԫ�ص�slotIndex ��Ա���Ǹ������������ָ���ڸ��������豸��ִ����ʱ���ڼ���״̬��DPB slot ������
		8.pBeginInfo->pReferenceSlots��ÿ��non-NULL pPictureResourceָ����video picture resource�������Ӧ��slotIndex ���Ǹ��������video picture resource ����ƥ���ڸ��������豸��ִ����ʱ������pBeginInfo->videoSession��DPB slot��video picture resource
		9.���pBeginInfo->videoSession ��һ��video encode operation ��������pBeginInfo->pNext ������һ��VkVideoEncodeRateControlInfoKHR�����ڸ��������豸��ִ����ʱpBeginInfo->videoSession���õ� rate control mode ����ΪVK_VIDEO_ENCODE_RATE_CONTROL_MODE_DEFAULT_KHR
		10.���pBeginInfo->videoSession ��һ��video encode operation ��������pBeginInfo->pNext ����һ��VkVideoEncodeRateControlInfoKHR������ýṹ���������ƥ���ڸ��������豸��ִ����ʱpBeginInfo->videoSession���õ� rate control mode
		11.���pBeginInfo->videoSession ��һ�� video codec operation ΪVK_VIDEO_CODEC_OPERATION_ENCODE_H264_BIT_KHR�������ҵ�ǰ��rate control mode��ΪVK_VIDEO_ENCODE_RATE_CONTROL_MODE_DEFAULT_KHR ���� VK_VIDEO_ENCODE_RATE_CONTROL_MODE_DISABLED_BIT_KHR���ҵ���vkGetPhysicalDeviceVideoCapabilitiesKHR����pBeginInfo->videoSession����ʱ�� video profile ���ص�VkVideoEncodeH264CapabilitiesKHR::requiresGopRemainingFrames ΪVK_TRUE����pBeginInfo->pNext�б������һ��useGopRemainingFrames ΪVK_TRUE��VkVideoEncodeH264GopRemainingFrameInfoKHR�ṹ��
		12.���pBeginInfo->videoSession ��һ�� video codec operation ΪVK_VIDEO_CODEC_OPERATION_ENCODE_H265_BIT_KHR�������ҵ�ǰ��rate control mode��ΪVK_VIDEO_ENCODE_RATE_CONTROL_MODE_DEFAULT_KHR ���� VK_VIDEO_ENCODE_RATE_CONTROL_MODE_DISABLED_BIT_KHR���ҵ���vkGetPhysicalDeviceVideoCapabilitiesKHR����pBeginInfo->videoSession����ʱ�� video profile ���ص�VkVideoEncodeH265CapabilitiesKHR::requiresGopRemainingFrames ΪVK_TRUE����pBeginInfo->pNext�б������һ��useGopRemainingFrames ΪVK_TRUE��VkVideoEncodeH265GopRemainingFrameInfoKHR�ṹ��
		*/




		//����һ�� Video Coding Scope  �μ�p3467
		VkVideoEndCodingInfoKHR videoEndCodingInfoKHR{};
		videoEndCodingInfoKHR.sType = VK_STRUCTURE_TYPE_VIDEO_END_CODING_INFO_KHR;
		videoEndCodingInfoKHR.pNext = nullptr;
		videoEndCodingInfoKHR.flags = 0;//����δ��ʹ��

		//������ᵼ��֮ǰvkCmdBeginVideoCodingKHR��ʼ��scope�� �󶨵�����reference picture resources���
		vkCmdEndVideoCodingKHR(commandBuffer, &videoEndCodingInfoKHR);//��ǰ�����м����queries
	}

	//Video Coding Control  �μ�p3469
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
				videoEncodeH264RateControlInfoKHR.sType = VK_STRUCTURE_TYPE_MAX_ENUM;//δ�����������ﶨ��Ϊ�Ƿ�ֵ
				videoEncodeH264RateControlInfoKHR.pNext = nullptr;
				videoEncodeH265RateControlInfoKHR.sType = VK_STRUCTURE_TYPE_MAX_ENUM;//δ�����������ﶨ��Ϊ�Ƿ�ֵ
				videoEncodeH265RateControlInfoKHR.pNext = nullptr;
				videoEncodeQualityLevelInfoKHR.sType = VK_STRUCTURE_TYPE_MAX_ENUM;//δ�����������ﶨ��Ϊ�Ƿ�ֵ
				videoEncodeQualityLevelInfoKHR.pNext = nullptr;
				videoEncodeRateControlInfoKHR.sType = VK_STRUCTURE_TYPE_MAX_ENUM;//δ�����������ﶨ��Ϊ�Ƿ�ֵ
				videoEncodeRateControlInfoKHR.pNext = nullptr;
			}
		};

		//��̬���Ƶ�ǰ�󶨵� video session ��������ο��Ƽ�p3470, �򵥽����Ǹ���flags�е�ֵ�Լ�pNext�е�ֵ���󶨵�video session���û��߸ı�ĳЩ���Ʋ���
		VkVideoCodingControlInfoKHR videoCodingControlInfoKHR{};
		videoCodingControlInfoKHR.sType = VK_STRUCTURE_TYPE_VIDEO_CODING_CONTROL_INFO_KHR;
		VideoCodingControlInfoKHREXT videoCodingControlInfoKHREXT{};
		videoCodingControlInfoKHR.pNext = &videoCodingControlInfoKHREXT.videoEncodeH264RateControlInfoKHR;
		videoCodingControlInfoKHR.flags = VK_VIDEO_CODING_CONTROL_RESET_BIT_KHR;/*Ϊ VkVideoCodingControlFlagsKHR ���ֵλ����ָ�����Ʊ�־
		VkVideoCodingControlFlagsKHR:
		VK_VIDEO_CODING_CONTROL_RESET_BIT_KHR : ָ��������Ӧ������coding���Ʋ���֮ǰ���ð󶨵�video session
		VK_VIDEO_CODING_CONTROL_ENCODE_RATE_CONTROL_BIT_KHR : ָ��coding���Ʋ�������video encode rate control��������VkVideoEncodeRateControlInfoKHR��
		VK_VIDEO_CODING_CONTROL_ENCODE_QUALITY_LEVEL_BIT_KHR : ָ��coding���Ʋ�������video encode quality level��������VkVideoEncodeQualityLevelInfoKHR��
		*/
		
		
		/*
		VkVideoCodingControlInfoKHR��Ч�÷�:
		1.���flags ����VK_VIDEO_CODING_CONTROL_ENCODE_RATE_CONTROL_BIT_KHR����pNext�б������һ��VkVideoEncodeRateControlInfoKHR
		2.���flags ����VK_VIDEO_CODING_CONTROL_ENCODE_QUALITY_LEVEL_BIT_KHR����pNext�б������һ��VkVideoEncodeQualityLevelInfoKHR
		*/
		

		//��ʼ Video Coding Scope

		vkCmdControlVideoCodingKHR(commandBuffer, &videoCodingControlInfoKHR);
		/*
		vkCmdControlVideoCodingKHR��Ч�÷�:
		1.���pCodingControlInfo->flags �в�����VK_VIDEO_CODING_CONTROL_RESET_BIT_KHR����󶨵�video session �ڸ��������豸��ִ�е�ʱ����Ϊ�ǳ�ʼ����״̬
		2.����󶨵�video session ����һ��encode operation ��������pCodingControlInfo->flags ���ܰ���VK_VIDEO_CODING_CONTROL_ENCODE_RATE_CONTROL_BIT_KHR ���� VK_VIDEO_CODING_CONTROL_ENCODE_QUALITY_LEVEL_BIT_KHR
		
		*/


		//���� Video Coding Scope

	}


	//Inline Queries  �μ�p3473
	{
		/*
		���video session ��VK_VIDEO_SESSION_CREATE_INLINE_QUERIES_BIT_KHR ����������video coding scope ��ʹ�� vkCmdBeginQuery ��ʼquery�ǲ�����ģ�
		Ҫ��ѯ��Ҫ��video coding commands�Ĳ����� vkCmdDecodeVideoKHR�� pDecodeInfo ����  vkCmdEncodeVideoKHR�� pEncodeInfo����pNext�а���һ��queryPoolΪһ����Ч��VkQueryPool�� VkVideoInlineQueryInfoKHR
		
		*/

		//VkVideoInlineQueryInfoKHR
		VkVideoInlineQueryInfoKHR videoInlineQueryInfoKHR{};
		videoInlineQueryInfoKHR.sType = VK_STRUCTURE_TYPE_MAX_ENUM;//δ�����������ﶨ��Ϊ�Ƿ�ֵ
		videoInlineQueryInfoKHR.pNext = nullptr;
		videoInlineQueryInfoKHR.queryPool = VkQueryPool{/*��������һ����Ч��VkQueryPool*/ };//ΪVK_NULL_HANDLE ����һ����Ч�Ĺ���query����� VkQueryPool
		videoInlineQueryInfoKHR.firstQuery = 0;//Ϊ��ŵ�һ�� video coding operation ��ѯ�����queryPool�е�query�������������Ĳ�ѯ�����˳�����ں�����query������
		videoInlineQueryInfoKHR.queryCount = 1;//Ϊִ�е�query�Ĵ���
		/*
		VkVideoInlineQueryInfoKHR��Ч�÷�:
		1.���queryPool ��ΪVK_NULL_HANDLE����1��firstQuery ����С��queryPool�е�queries����
											  ��2��firstQuery + queryCount ����С�ڵ���queryPool�е�queries����

		*/


	}


	//Video Decode Operations  �μ�p3474
	{
		/*
		video decode operations ��������video bitstream buffer �Լ�һ������ reference pictures��ѹ�������ݣ�Ȼ�����һ�� decode output picture �Լ���ѡ��һ��reconstructed  picture
		
		video decode operations �ж���Դ��ͬ����VK_PIPELINE_STAGE_2_VIDEO_DECODE_BIT_KHR stage���������ڸò����������Դ�� VK_ACCESS_2_VIDEO_DECODE_READ_BIT_KHR ���ʣ������VK_ACCESS_2_VIDEO_DECODE_WRITE_BIT_KHR ���ʡ������ڲ����е�image��layout�ڳ��˸�imageֻ������Ϊһ��decode output picture ΪVK_IMAGE_LAYOUT_VIDEO_DECODE_DST_KHR�����������ΪVK_IMAGE_LAYOUT_VIDEO_DECODE_DPB_KHR
		*/


		// Codec-Specific Semantics �μ�p3475  ����������video decode operations��һЩ���������Ϊ�� codec-specific������Ӧ���õ�codec�������ͣ���Щ�������Ϊ������������

		// Video Decode Operation Steps  �μ�p3475  ������video decode operations��һЩ����Ϊ�� ��ȡѹ�������� -> ִ���ؽ����� -> д����������


		//Capabilities �μ�p3476
		{

			//VkVideoDecodeCapabilitiesKHR ���԰����ڵ��� vkGetPhysicalDeviceVideoCapabilitiesKHR����� VkVideoCapabilitiesKHR.pNext�����ڷ�����Ƶ������������Ϣ
			//VkVideoCapabilitiesKHR.pNext
			VkVideoDecodeCapabilitiesKHR videoDecodeCapabilitiesKHR{};
			videoDecodeCapabilitiesKHR.sType = VK_STRUCTURE_TYPE_VIDEO_DECODE_CAPABILITIES_KHR;
			videoDecodeCapabilitiesKHR.pNext = nullptr;
			videoDecodeCapabilitiesKHR.flags = VK_VIDEO_DECODE_CAPABILITY_DPB_AND_OUTPUT_COINCIDE_BIT_KHR;/*Ϊ VkVideoDecodeCapabilityFlagBitsKHR ���ֵλ����ָ��֧�ֵ���Ƶ��������
			VkVideoDecodeCapabilityFlagBitsKHR:
			VK_VIDEO_DECODE_CAPABILITY_DPB_AND_OUTPUT_COINCIDE_BIT_KHR : ָ����һ��video decode operation��֧��ʹ����ͬ��video picture ��Ϊreconstructed picture ��decode output picture
			VK_VIDEO_DECODE_CAPABILITY_DPB_AND_OUTPUT_DISTINCT_BIT_KHR : ָ����һ��video decode operation��֧��ʹ�ò�ͬ��video picture ��Ϊreconstructed picture ��decode output picture
			*/


		}


		//Video Decode Commands �μ�p3477
		{
			VkCommandBuffer commandBuffer{/*��������һ����Ч��VkCommandBuffer*/ };

			struct VideoDecodeInfoKHREXT {
				VkVideoDecodeAV1PictureInfoKHR videoDecodeAV1PictureInfoKHR{};
				VkVideoDecodeH264PictureInfoKHR videoDecodeH264PictureInfoKHR{};
				VkVideoDecodeH265PictureInfoKHR videoDecodeH265PictureInfoKHR{};
				VkVideoInlineQueryInfoKHR videoInlineQueryInfoKHR{};
				VideoDecodeInfoKHREXT() {
					Init();
				}
				void Init() {
					videoDecodeAV1PictureInfoKHR.sType = VK_STRUCTURE_TYPE_MAX_ENUM;//δ�����������ﶨ��Ϊ�Ƿ�ֵ
					videoDecodeAV1PictureInfoKHR.pNext = nullptr;
					videoDecodeH264PictureInfoKHR.sType = VK_STRUCTURE_TYPE_VIDEO_DECODE_H264_PICTURE_INFO_KHR;
					videoDecodeH264PictureInfoKHR.pNext = nullptr;
					videoDecodeH265PictureInfoKHR.sType = VK_STRUCTURE_TYPE_VIDEO_DECODE_H265_PICTURE_INFO_KHR;
					videoDecodeH265PictureInfoKHR.pNext = nullptr;
					videoInlineQueryInfoKHR.sType = VK_STRUCTURE_TYPE_MAX_ENUM;//δ�����������ﶨ��Ϊ�Ƿ�ֵ
					videoInlineQueryInfoKHR.pNext = nullptr;;
				}


			};



			//����opCount�� video decode operations
			VkVideoDecodeInfoKHR videoDecodeInfoKHR{};
			videoDecodeInfoKHR.sType = VK_STRUCTURE_TYPE_VIDEO_DECODE_INFO_KHR;
			VideoDecodeInfoKHREXT videoDecodeInfoKHREXT{};
			videoDecodeInfoKHR.pNext = &videoDecodeInfoKHREXT.videoDecodeAV1PictureInfoKHR;
			videoDecodeInfoKHR.flags = 0;//����δ��ʹ��
			videoDecodeInfoKHR.srcBuffer = VkBuffer{/*��������һ����Ч��VkBuffer*/};//Ϊ��ȡ encoded bitstream�� source video bitstream buffer
			videoDecodeInfoKHR.srcBufferOffset = 0;//srcBuffer �е���ʼ�ֽ�ƫ����
			videoDecodeInfoKHR.srcBufferRange = 4;//srcBuffer �д�srcBufferOffset��ʼ���ֽ���
			VkVideoPictureResourceInfoKHR dstPictureResource{};
			{
				dstPictureResource.sType = VK_STRUCTURE_TYPE_VIDEO_PICTURE_RESOURCE_INFO_KHR;
				dstPictureResource.pNext = nullptr;
				dstPictureResource.baseArrayLayer = 0;
				dstPictureResource.codedExtent = VkExtent2D{ .width = 1,.height = 1 };
				dstPictureResource.codedOffset = VkOffset2D{ .x = 0,.y = 0 };
				dstPictureResource.imageViewBinding = VkImageView{/*��������һ����Ч��VkImageView*/ };
			}
			videoDecodeInfoKHR.dstPictureResource = dstPictureResource;//ָ������Decode Output Picture��video picture resource
			VkVideoReferenceSlotInfoKHR videoReferenceSlotInfoKHR{};
			{
				videoReferenceSlotInfoKHR.sType = VK_STRUCTURE_TYPE_VIDEO_REFERENCE_SLOT_INFO_KHR;
				videoReferenceSlotInfoKHR.pNext = nullptr;
				videoReferenceSlotInfoKHR.slotIndex = 0;
				VkVideoPictureResourceInfoKHR testPictureResource{/*��������һ����Ч��VkVideoPictureResourceInfoKHR*/ };
				videoReferenceSlotInfoKHR.pPictureResource = &testPictureResource;

			}
			videoDecodeInfoKHR.pSetupReferenceSlot = &videoReferenceSlotInfoKHR;//ΪNULL����VkVideoReferenceSlotInfoKHR ָ�룬 ָ����ѡ��Reconstructed Picture ��Ϣ
			videoDecodeInfoKHR.referenceSlotCount = 1;// pReferenceSlots ��Ԫ�ظ���
			videoDecodeInfoKHR.pReferenceSlots = &videoReferenceSlotInfoKHR;//ΪNULL����VkVideoReferenceSlotInfoKHR ����ָ�룬��������video decode operation ��DPB slots �Լ���Ӧ�� reference picture �������Reference Picture �飩
			/*
			VkVideoDecodeInfoKHR��Ч�÷�:
			1.srcBuffer ������VK_BUFFER_USAGE_VIDEO_DECODE_SRC_BIT_KHR ��Ǵ���
			2.srcBufferOffset ����С��srcBuffer�Ĵ�С
			3.srcBufferRange ����С�ڵ���srcBuffer�Ĵ�С ��ȥsrcBufferOffset
			4.���pSetupReferenceSlot ��ΪNULL������slotIndex ����Ϊ��������pPictureResource ����ΪNULL
			5.pReferenceSlots ��ÿ��Ԫ�ص�slotIndex ����Ϊ������pPictureResource ����ΪNULL

			*/


			//�ýӿڵ�����ע����Ϣ�Լ�ʹ��ʱһЩ������������Ϣ�� *** p3478 - p3480
			vkCmdDecodeVideoKHR(commandBuffer, &videoDecodeInfoKHR);
			/*
			vkCmdDecodeVideoKHR��Ч�÷�:
			1.�󶨵�video session ������һ�� decode operation ���������ڸ��������豸��ִ�е�ʱ��video session ����Ϊ�ǳ�ʼ����״̬
			2.��ÿ�������query����Ӧquery type�ļ����query �������� opCount ����С�ڵ��ڸ�query type�����һ�������query ������1
			3.����󶨵�video session ��VK_VIDEO_SESSION_CREATE_INLINE_QUERIES_BIT_KHR ��������pDecodeInfo->pNext�а���һ��queryPool ָ��һ����Ч��VkQueryPool��VkVideoInlineQueryInfoKHR����1��VkVideoInlineQueryInfoKHR::queryCount �������opCount
																																															 ��2�����и�����ʹ�õ�VkVideoInlineQueryInfoKHR�е�query����Ϊunavailable��״̬
																																															 ��3�������ڴ���VkVideoInlineQueryInfoKHR.queryPool�� queryType ����ΪVK_QUERY_TYPE_RESULT_STATUS_ONLY_KHR
																																															 ��4��VkVideoInlineQueryInfoKHR.queryPool ����Ҫ��VkQueryPoolCreateInfo.pNext�а���һ����video session����ʱVkVideoSessionCreateInfoKHR::pVideoProfile ��һ��Ԫ����ȵ�VkVideoProfileInfoKHR ����
																																															 ��5��������ڴ���VkVideoInlineQueryInfoKHR.queryPool�� queryType ����ΪVK_QUERY_TYPE_RESULT_STATUS_ONLY_KHR����commandBuffer���ڵ�VkCommandPool�Ķ��������֧��result status queries�����������VkQueueFamilyQueryResultStatusPropertiesKHR::queryResultStatusSupport
			4.pDecodeInfo->srcBuffer ��������ڰ󶨵�video session ����ʱʹ�õ�video profile
			5.���commandBuffer��unprotected command buffer ��protectedNoFault��֧�֣���pDecodeInfo->srcBuffer ������protected buffer
			6.���commandBuffer��protected command buffer ��protectedNoFault��֧�֣���pDecodeInfo->srcBuffer ������protected buffer
			7.pDecodeInfo->srcBufferOffset �����ǵ���vkGetPhysicalDeviceVideoCapabilitiesKHR�����video session����ʱ��video profile���ص�VkVideoCapabilitiesKHR::minBitstreamBufferOffsetAlignment��������
			8.pDecodeInfo->srcBufferRange �����ǵ���vkGetPhysicalDeviceVideoCapabilitiesKHR�����video session����ʱ��video profile���ص�VkVideoCapabilitiesKHR::minBitstreamBufferSizeAlignment��������
			9.���pDecodeInfo->pSetupReferenceSlot ��ΪNULL�������vkGetPhysicalDeviceVideoCapabilitiesKHR�����video session����ʱ��video profile����VkVideoDecodeCapabilitiesKHR::flags ������VK_VIDEO_DECODE_CAPABILITY_DPB_AND_OUTPUT_COINCIDE_BIT_KHR����pDecodeInfo->dstPictureResource �Լ� pDecodeInfo->pSetupReferenceSlot->pPictureResource ָ����video picture resources ����ƥ��
			10.���pDecodeInfo->pSetupReferenceSlot ��ΪNULL�������vkGetPhysicalDeviceVideoCapabilitiesKHR�����video session����ʱ��video profile����VkVideoDecodeCapabilitiesKHR::flags ������VK_VIDEO_DECODE_CAPABILITY_DPB_AND_OUTPUT_COINCIDE_BIT_KHR���Ұ󶨵�video session����video codec operation ��������VkVideoDecodeAV1ProfileInfoKHR::filmGrainSupport��ΪVK_TRUE������decoded picture��film grain δ��������pDecodeInfo->dstPictureResource �Լ� pDecodeInfo->pSetupReferenceSlot->pPictureResource ָ����video picture resources ����ƥ��
			11.pDecodeInfo->dstPictureResource.imageViewBinding ������ݰ󶨵�video session����ʱ��video profile
			12.pDecodeInfo->dstPictureResource.imageViewBinding ��format����ƥ�䴴��video sessionʱʹ�õ�VkVideoSessionCreateInfoKHR::pictureFormat
			13.pDecodeInfo->dstPictureResource.codedOffset ������codedOffsetGranularity ��������
			14.pDecodeInfo->dstPictureResource.codedExtent �����ڴ���video session ʱʹ�õ�VkVideoSessionCreateInfoKHR::minCodedExtent �� VkVideoSessionCreateInfoKHR::maxCodedExtent ֮��
			15.pDecodeInfo->dstPictureResource.imageViewBinding ������VK_IMAGE_USAGE_VIDEO_DECODE_DST_BIT_KHR ����
			16.���commandBuffer��unprotected command buffer ��protectedNoFault��֧�֣���pDecodeInfo->dstPictureResource.imageViewBinding ���ܴ�protected image �ϴ���
			17.���commandBuffer��protected command buffer ��protectedNoFault��֧�֣���pDecodeInfo->dstPictureResource.imageViewBinding �����protected image �ϴ���
			18.pDecodeInfo->pSetupReferenceSlot ���벻ΪNULL���ǰ󶨵�video session ������ʱָ����VkVideoSessionCreateInfoKHR::maxDpbSlots Ϊ0
			19.��� pDecodeInfo->pSetupReferenceSlot ��ΪNULL����1��pDecodeInfo->pSetupReferenceSlot->slotIndex ����С�ڵ��ڴ���video session ʱ VkVideoSessionCreateInfoKHR::maxDpbSlots ָ�������DPB������
																 ��2��pDecodeInfo->pSetupReferenceSlot->pPictureResource->codedOffset ����ΪcodedOffsetGranularity ��������
																 ��3��pDecodeInfo->pSetupReferenceSlot->pPictureResource ����ƥ��һ���󶨵�reference picture resource
			20.activeReferencePictureCount ����С�ڵ��ڴ���video session ʱָ���� VkVideoSessionCreateInfoKHR::maxActiveReferencePictures
			21.pDecodeInfo->pReferenceSlots ��ÿ��Ԫ�ص�slotIndex ����С�ڵ��ڴ���video session ʱ VkVideoSessionCreateInfoKHR::maxDpbSlots ָ�������DPB������
			22.ÿ��pDecodeInfo->pReferenceSlots Ԫ�ص�pPictureResource ��ָ��VkVideoPictureResourceInfoKHR::codedOffset ����ΪcodedOffsetGranularity ��������
			23.ÿ��pDecodeInfo->pReferenceSlots Ԫ�ص�pPictureResource ����ƥ��һ���󶨵Ĺ�������slotIndexָ����DPB slot �����ϵ�reference picture resource
			24.ÿ��pDecodeInfo->pReferenceSlots Ԫ�ص�pPictureResource ��ָ��video picture resource ������pDecodeInfo->pReferenceSlots ����Ψһ��
			25.dpbFrameUseCount��dpbFrameUseCount �Լ�dpbBottomFieldUseCount������Ԫ�ر���С�ڵ���1 �����������������ģ�ͨ����������ģ������p3478 - p3480��
			26.��� pDecodeInfo->pSetupReferenceSlot ΪNULL ����pDecodeInfo->pSetupReferenceSlot->pPictureResource û�����õ���pDecodeInfo->dstPictureResource ��ͬ��image subresource����pDecodeInfo->dstPictureResource ���õ�image subresource �ڸ��������豸��ִ��ʱlayout����Ϊ VK_IMAGE_LAYOUT_VIDEO_DECODE_DST_KHR
			27.��� pDecodeInfo->pSetupReferenceSlot ��ΪNULL ��pDecodeInfo->pSetupReferenceSlot->pPictureResource ���õ���pDecodeInfo->dstPictureResource ��ͬ��image subresource����pDecodeInfo->dstPictureResource ���õ�image subresource �ڸ��������豸��ִ��ʱlayout����Ϊ VK_IMAGE_LAYOUT_VIDEO_DECODE_DPB_KHR
			28.���pDecodeInfo->pSetupReferenceSlot ��ΪNULL����pDecodeInfo->pSetupReferenceSlot->pPictureResource ��ָ��image subresource �ڸ��������豸��ִ��ʱlayout����Ϊ VK_IMAGE_LAYOUT_VIDEO_DECODE_DPB_KHR
			29.pDecodeInfo->pReferenceSlots ��ÿ��Ԫ�ص�pPictureResource ���õ�image subresource �ڸ��������豸��ִ��ʱlayout����Ϊ VK_IMAGE_LAYOUT_VIDEO_DECODE_DPB_KHR
			30.����󶨵�video session ��video codec operation Ϊ VK_VIDEO_CODEC_OPERATION_DECODE_H264_BIT_KHR ��������1��pDecodeInfo->pNext�б������һ��VkVideoDecodeH264PictureInfoKHR�ṹ
																													   ��2�����video session����֧��interlaced frame ��������decode output picture �������һ��frame
																													   ��3����pDecodeInfo->pNext�е�VkVideoDecodeH264PictureInfoKHR.pSliceOffsets ������Ԫ�� ����С��pDecodeInfo->srcBufferRange
																													   ��4���󶨵�video session parameters �������seq_parameter_set_id ƥ��pDecodeInfo->pNext��VkVideoDecodeH264PictureInfoKHR::pStdPictureInfo ��Ԫ�ص�StdVideoDecodeH264PictureInfo::seq_parameter_set_id�� StdVideoH264SequenceParameterSet ʵ��
																													   ��5���󶨵�video session parameters �������seq_parameter_set_id �Լ�pic_parameter_set_id ƥ��pDecodeInfo->pNext��VkVideoDecodeH264PictureInfoKHR::pStdPictureInfo ��Ԫ�ص� StdVideoDecodeH264PictureInfo::seq_parameter_set_id �Լ�StdVideoDecodeH264PictureInfo::pic_parameter_set_id �� StdVideoH264PictureParameterSet ʵ��
																													   ��6�����pDecodeInfo->pSetupReferenceSlot ��ΪNULL����pDecodeInfo->pSetupReferenceSlot->pNext�б������һ��VkVideoDecodeH264DpbSlotInfoKHR
																													   ��7�����video session����֧��interlaced frame ��������pDecodeInfo->pSetupReferenceSlot ��ΪNULL����reconstructed picture �������һ��frame
																													   ��8����pDecodeInfo->pReferenceSlots��ÿ��Ԫ�ص�pNext�б������һ��VkVideoDecodeH264DpbSlotInfoKHR
																													   ��9�����video session����֧��interlaced frame ��������pDecodeInfo->pReferenceSlots ��ÿ�������reference picture �������һ��frame
																													   ��10�����pDecodeInfo->pSetupReferenceSlot ��ΪNULL���� decode output picture ��ʾһ��frame����reconstructed picture Ҳ�����ʾһ��frame
																													   ��11�����pDecodeInfo->pSetupReferenceSlot ��ΪNULL���� decode output picture ��ʾһ��top field����reconstructed picture Ҳ�����ʾһ��top field
																													   ��12�����pDecodeInfo->pSetupReferenceSlot ��ΪNULL���� decode output picture ��ʾһ��bottom field����reconstructed picture Ҳ�����ʾһ��bottom field
																													   ��13�����pDecodeInfo->pReferenceSlots ��һ�������reference picture ����һ��frame�����Ԫ�ص�slotIndexָ���Ĺ�����frame picture�� DPB slot index ����ƥ���ڸ��������豸��ִ��ʱ��ͬԪ�ص�pPictureResource ��ָ��video picture resource
																													   ��14�����pDecodeInfo->pReferenceSlots ��һ�������reference picture ����һ��top field�����Ԫ�ص�slotIndexָ���Ĺ�����top field picture�� DPB slot index ����ƥ���ڸ��������豸��ִ��ʱ��ͬԪ�ص�pPictureResource ��ָ��video picture resource
																													   ��15�����pDecodeInfo->pReferenceSlots ��һ�������reference picture ����һ��bottom field�����Ԫ�ص�slotIndexָ���Ĺ�����bottom field picture�� DPB slot index ����ƥ���ڸ��������豸��ִ��ʱ��ͬԪ�ص�pPictureResource ��ָ��video picture resource
			31.����󶨵�video session ��video codec operation Ϊ VK_VIDEO_CODEC_OPERATION_DECODE_H265_BIT_KHR ��������1��pDecodeInfo->pNext�б������һ��VkVideoDecodeH265PictureInfoKHR�ṹ
																													   ��2����pDecodeInfo->pNext�е�VkVideoDecodeH265PictureInfoKHR.pSliceSegmentOffsets ������Ԫ�� ����С��pDecodeInfo->srcBufferRange
																													   ��3���󶨵�video session parameters �������vps_video_parameter_set_id ƥ��pDecodeInfo->pNext��VkVideoDecodeH265PictureInfoKHR::pStdPictureInfo ��Ԫ�ص�StdVideoDecodeH265PictureInfo::sps_video_parameter_set_id�� StdVideoH265VideoParameterSet ʵ��
																													   ��4���󶨵�video session parameters �������sps_video_parameter_set_id �Լ� sps_seq_parameter_set_id ƥ��pDecodeInfo->pNext��VkVideoDecodeH265PictureInfoKHR::pStdPictureInfo ��Ԫ�ص�StdVideoDecodeH265PictureInfo::sps_video_parameter_set_id �Լ� StdVideoDecodeH265PictureInfo::pps_seq_parameter_set_id �� StdVideoH265SequenceParameterSet ʵ��
																													   ��5���󶨵�video session parameters �������sps_video_parameter_set_id, pps_seq_parameter_set_id, �Լ� pps_pic_parameter_set_id ��ƥ��pDecodeInfo->pNext��VkVideoDecodeH265PictureInfoKHR::pStdPictureInfo ��Ԫ�ص�StdVideoDecodeH265PictureInfo::sps_video_parameter_set_id, StdVideoDecodeH265PictureInfo::pps_seq_parameter_set_id, �Լ� StdVideoDecodeH265PictureInfo::pps_pic_parameter_set_id �� StdVideoH265PictureParameterSet ʵ��
																													   ��6�����pDecodeInfo->pSetupReferenceSlot ��ΪNULL����pDecodeInfo->pSetupReferenceSlot->pNext�б������һ��VkVideoDecodeH265DpbSlotInfoKHR
																													   ��7����pDecodeInfo->pReferenceSlots��ÿ��Ԫ�ص�pNext�б������һ��VkVideoDecodeH265DpbSlotInfoKHR
			32.����󶨵�video session ��video codec operation Ϊ VK_VIDEO_CODEC_OPERATION_DECODE_AV1_BIT_KHR ��������1�����Ҳ��VkVideoDecodeAV1ProfileInfoKHR::filmGrainSupport ��ΪVK_FALSE��������decoded picture���ܿ���film grain
																													  ��2�����pDecodeInfo->pSetupReferenceSlot ��ΪNULL����decoded picture ����film grain����pDecodeInfo->dstPictureResource �Լ�pDecodeInfo->pSetupReferenceSlot->pPictureResource ��ָ��video picture resources ����ƥ��
																													  ��3��pDecodeInfo->pNext�б������һ��VkVideoDecodeAV1PictureInfoKHR�ṹ
																													  ��4����pDecodeInfo->pNext�е�VkVideoDecodeAV1PictureInfoKHR.frameHeaderOffset ����С��pDecodeInfo->srcBufferRange����Сֵ
																													  ��5����pDecodeInfo->pNext�е�VkVideoDecodeAV1PictureInfoKHR.pTileOffsets ������Ԫ�� ����С��pDecodeInfo->srcBufferRange
																													  ��6����pDecodeInfo->pNext�е�VkVideoDecodeAV1PictureInfoKHR ��pTileOffsets �Լ�pTileSizes ������iԪ�أ���pTileOffsets[i] + pTileSizes[i]  ����С�ڵ���pDecodeInfo->srcBufferRange
																													  ��7�����pDecodeInfo->pSetupReferenceSlot ��ΪNULL����pDecodeInfo->pSetupReferenceSlot->pNext�б������һ��VkVideoDecodeAV1DpbSlotInfoKHR
																													  ��8����pDecodeInfo->pReferenceSlots��ÿ��Ԫ�ص�pNext�б������һ��VkVideoDecodeAV1DpbSlotInfoKHR
																													  ��9����pDecodeInfo->pNext�е�VkVideoDecodeAV1PictureInfoKHR.referenceNameSlotIndices �е�ÿ��Ԫ�ر���Ϊ�������� �������pDecodeInfo->pReferenceSlots ��һ��Ԫ�ص�slotIndex
																													  ��10����pDecodeInfo->pReferenceSlots ��ÿ��Ԫ�ص�slotIndex �������  pDecodeInfo->pNext�е�VkVideoDecodeAV1PictureInfoKHR.referenceNameSlotIndices �е�һ��Ԫ��ֵ

			*/
		}

	}


	//H.264 Decode Operations  �μ�p3491
	{}
	{
		/*
		video decode operations ʹ��һ�� H.264 decode profile ��������ITU-T H.264 Specification ������video stream���н���

		�����д����һЩ���ݽṹ���Ӧ��ITU-T H.264 Specification �еĶ�Ӧ����:
			 StdVideoH264SequenceParameterSet ->  H.264 sequence parameter set
			 StdVideoH264PictureParameterSet  ->   H.264 picture parameter set
			 StdVideoDecodeH264PictureInfo   ->    H.264 picture information
			 StdVideoDecodeH264ReferenceInfo ->   H.264 reference information
		*/


		//H.264 Decode Bitstream Data Access  ��Ҫ����video bitstream buffer�д洢�����ݸ�ʽ��  ������ϸ��Ϣ�μ�p3492 ***

		//H.264 Decode Picture Data Access  ��Ҫ������η���video picture resource�е�image ���ݣ� ������ϸ��Ϣ�μ�p3492  ***


		// H.264 Decode Profile �μ�p3493
		{
			/*
			video profile ֧��H.264 video decode operations ��Ҫ��VkVideoProfileInfoKHR::videoCodecOperation ����ΪVK_VIDEO_CODEC_OPERATION_DECODE_H264_BIT_KHR ������ VkVideoProfileInfoKHR::pNext �����һ��VkVideoDecodeH264ProfileInfoKHR
			*/

			VkVideoDecodeH264ProfileInfoKHR videoDecodeH264ProfileInfoKHR{};
			videoDecodeH264ProfileInfoKHR.sType = VK_STRUCTURE_TYPE_VIDEO_DECODE_H264_PROFILE_INFO_KHR;
			videoDecodeH264ProfileInfoKHR.pNext = nullptr;
			videoDecodeH264ProfileInfoKHR.pictureLayout = VK_VIDEO_DECODE_H264_PICTURE_LAYOUT_INTERLACED_INTERLEAVED_LINES_BIT_KHR;//Ϊһ�� VkVideoDecodeH264PictureLayoutFlagBitsKHR ֵ��ָ�����ڽ��� H.264 video sequence��picture layout
			/*
			VkVideoDecodeH264PictureLayoutFlagBitsKHR:
			VK_VIDEO_DECODE_H264_PICTURE_LAYOUT_PROGRESSIVE_KHR : ָ��֧��progressive content ������ʽ���ݣ�����flagsʵ��ֵΪ0
			VK_VIDEO_DECODE_H264_PICTURE_LAYOUT_INTERLACED_INTERLEAVED_LINES_BIT_KHR : ָ��֧�ֻ���ʹ��һ��interlaced content��picture layout��ָ����������top field ���н����뵽picture resource��ż���У���������bottom field ���н����뵽picture resource�������С�
			VK_VIDEO_DECODE_H264_PICTURE_LAYOUT_INTERLACED_SEPARATE_PLANES_BIT_KHR : ָ��֧�ֻ���ʹ��һ��interlaced content��picture layout��ָ����������һ�� field ���н�������뵽picture resource��һ��image subregion�У����frame������fields���Դ洢����ͬimage��image subresource�еĲ�ͬsubregion ���ߴ洢�ڲ�ͬ��image subresource�С�
			
			*/
			videoDecodeH264ProfileInfoKHR.stdProfileIdc = STD_VIDEO_H264_PROFILE_IDC_MAIN;//Ϊһ��StdVideoH264ProfileIdc ֵ��ָ��H.264 codec profile IDC�������� ITU-T H.264 Specification�е�A.2�½ڣ�



		}


		//H.264 Decode Capabilities  �μ�p3495
		{
			/*
			������ vkGetPhysicalDeviceVideoCapabilitiesKHR ��ѯ H.264 decode profile����ʱ,��Ҫ��VkVideoCapabilitiesKHR::pNext �����һ��VkVideoDecodeH264CapabilitiesKHR������profile-specific ����

			*/

			VkVideoDecodeH264CapabilitiesKHR videoDecodeH264CapabilitiesKHR{};
			videoDecodeH264CapabilitiesKHR.sType = VK_STRUCTURE_TYPE_VIDEO_DECODE_H264_CAPABILITIES_KHR;
			videoDecodeH264CapabilitiesKHR.pNext = nullptr;
			videoDecodeH264CapabilitiesKHR.fieldOffsetGranularity = VkOffset2D{ .x = 1,.y = 0 };//Ϊ��ʹ��picture layoutΪVK_VIDEO_DECODE_H264_PICTURE_LAYOUT_INTERLACED_SEPARATE_PLANES_BIT_KHR�� һ��video picture resource��VkVideoPictureResourceInfoKHR::codedOffset����С��������
			videoDecodeH264CapabilitiesKHR.maxLevelIdc = STD_VIDEO_H264_LEVEL_IDC_1_0;//һ��StdVideoH264LevelIdc ֵ��ָ����profile֧�ֵ�����H.264 level������ֵ��ʽΪSTD_VIDEO_H264_LEVEL_IDC_<major>_<minor> ָ��H.264 level�� <major>.<minor> �μ� ITU-T H.264 Specification��A.3�½�


		}


		//H.264 Decode Parameter Sets  �μ�p3495
		{
			/*
			��VK_VIDEO_CODEC_OPERATION_DECODE_H264_BIT_KHR������ video session parameters ��������²�����:
				> H.264 Sequence Parameter Sets (SPS)�����飨�� ITU-T H.264 Specification��,��ӦStdVideoH264SequenceParameterSet ���������в����ľ������� ��p3496 *** ;
				> H.264 Picture Parameter Sets (PPS)�����飨�� ITU-T H.264 Specification��,��Ӧ StdVideoH264PictureParameterSet ���������в����ľ������� ��p3496 *** ;

			*/


			//��һ��video session parameters ��VK_VIDEO_CODEC_OPERATION_DECODE_H264_BIT_KHR ����ʱ��  VkVideoSessionParametersCreateInfoKHR::pNext �б������һ�� VkVideoDecodeH264SessionParametersCreateInfoKHR ָ���ö���ĳ�ʼ����
			VkVideoDecodeH264SessionParametersCreateInfoKHR videoDecodeH264SessionParametersCreateInfoKHR{};
			videoDecodeH264SessionParametersCreateInfoKHR.sType = VK_STRUCTURE_TYPE_VIDEO_DECODE_H264_SESSION_PARAMETERS_CREATE_INFO_KHR;
			videoDecodeH264SessionParametersCreateInfoKHR.pNext = nullptr;
			videoDecodeH264SessionParametersCreateInfoKHR.maxStdSPSCount = 1;//Ϊ������ VkVideoSessionParametersKHR �ܰ�����H.264 SPS ʵ����������
			videoDecodeH264SessionParametersCreateInfoKHR.maxStdPPSCount = 1;//Ϊ������ VkVideoSessionParametersKHR �ܰ�����H.264 PPS ʵ����������
			VkVideoDecodeH264SessionParametersAddInfoKHR videoDecodeH264SessionParametersAddInfoKHR{};
			{
				videoDecodeH264SessionParametersAddInfoKHR.sType = VK_STRUCTURE_TYPE_VIDEO_DECODE_H264_SESSION_PARAMETERS_ADD_INFO_KHR;
				videoDecodeH264SessionParametersAddInfoKHR.pNext = nullptr;
				videoDecodeH264SessionParametersAddInfoKHR.stdSPSCount = 1;//ΪpStdSPSs �е�Ԫ�ظ���
				StdVideoH264SequenceParameterSet stdVideoH264SequenceParameterSet{/*��������һ����Ч��StdVideoH264SequenceParameterSet �ṹ��*/ };
				videoDecodeH264SessionParametersAddInfoKHR.pStdSPSs = &stdVideoH264SequenceParameterSet;//һ��StdVideoH264SequenceParameterSet ����ָ��ָ����ӵ�H.264 SPS ʵ��
				videoDecodeH264SessionParametersAddInfoKHR.stdPPSCount = 1;//ΪpStdPPSs �е�Ԫ�ظ���
				StdVideoH264PictureParameterSet stdVideoH264PictureParameterSet{/*��������һ����Ч��StdVideoH264PictureParameterSet �ṹ��*/ };
				videoDecodeH264SessionParametersAddInfoKHR.pStdPPSs = &stdVideoH264PictureParameterSet;//һ�� StdVideoH264PictureParameterSet ����ָ��ָ����ӵ�H.264 PPS ʵ��
				/*
				VkVideoDecodeH264SessionParametersAddInfoKHR��Ч�÷�:
				1.pStdSPSs��ÿ��StdVideoH264SequenceParameterSetԪ�ص� seq_parameter_set_id������Ψһ��
				2.pStdPPSs��ÿ��StdVideoH264PictureParameterSetԪ�ص� seq_parameter_set_id �Լ� pic_parameter_set_id �����Ա�����Ψһ��
				*/
			}
			videoDecodeH264SessionParametersCreateInfoKHR.pParametersAddInfo = &videoDecodeH264SessionParametersAddInfoKHR;//ΪNULL����һ�� VkVideoDecodeH264SessionParametersAddInfoKHR ָ��ָ������ʱ��ӵ�H.264 parameters


		}


		//H.264 Decoding Parameters  �μ�p3499
		{
			//��vkCmdDecodeVideoKHR �� VkVideoDecodeInfoKHR.pNext�а���VkVideoDecodeH264PictureInfoKHR ָ�� H.264 decode operation��codec-specific picture ��Ϣ����Щ��Ϣ��ν��Ͳμ� p3499 ***
			VkVideoDecodeH264PictureInfoKHR  videoDecodeH264PictureInfoKHR{};
			videoDecodeH264PictureInfoKHR.sType = VK_STRUCTURE_TYPE_VIDEO_DECODE_H264_PICTURE_INFO_KHR;
			videoDecodeH264PictureInfoKHR.pNext = nullptr;
			videoDecodeH264PictureInfoKHR.sliceCount = 1;//pSliceOffsets �е�Ԫ�ظ���
			uint32_t sliceOffset = 0;
			videoDecodeH264PictureInfoKHR.pSliceOffsets = &sliceOffset;//ָ��picture��ÿ��slice������ VkVideoDecodeInfoKHRָ���� video bitstream buffer ��Χ�е���ʼ�ֽ�ƫ����
			StdVideoDecodeH264PictureInfo stdVideoDecodeH264PictureInfo{/*��������һ����Ч��StdVideoDecodeH264PictureInfo �ṹ��*/ };
			videoDecodeH264PictureInfoKHR.pStdPictureInfo = &stdVideoDecodeH264PictureInfo;//һ��StdVideoDecodeH264PictureInfo ��ָ�룬ָ�� H.264 picture information


			//������ VkVideoDecodeInfoKHR::pSetupReferenceSlot->pNext �Լ�  VkVideoDecodeInfoKHR::pReferenceSlots->pNext �а���VkVideoDecodeH264DpbSlotInfoKHR  ��ָ��codec-specific reference picture information��������Ϣ��ν��ͼ�  p3501 ***
			VkVideoDecodeH264DpbSlotInfoKHR  videoDecodeH264DpbSlotInfoKHR{};
			videoDecodeH264DpbSlotInfoKHR.sType = VK_STRUCTURE_TYPE_VIDEO_DECODE_H264_DPB_SLOT_INFO_KHR;
			videoDecodeH264DpbSlotInfoKHR.pNext = nullptr;
			StdVideoDecodeH264ReferenceInfo stdVideoDecodeH264ReferenceInfo{/*��������һ����Ч��StdVideoDecodeH264ReferenceInfo �ṹ��*/ };
			videoDecodeH264DpbSlotInfoKHR.pStdReferenceInfo = &stdVideoDecodeH264ReferenceInfo;//һ��StdVideoDecodeH264ReferenceInfo ָ�룬ָ�� H.264 reference information

		}


		//H.264 Decode Requirements  �μ�p3503
		{
			/*
			Ҫ֧��H.264 decoding����physical device����Ҫ����һ��֧��VK_VIDEO_CODEC_OPERATION_DECODE_H264_BIT_KHR�Ķ����壬��vkGetPhysicalDeviceQueueFamilyProperties2���ص�VkQueueFamilyVideoPropertiesKHR::videoCodecOperations

			����֮�⣬��Ҫ��physical deviceҪ����֧��ָ������Ҫ�������p3503
			Table 51. Required Video Std Header Versions
			Table 52. Required Video Capabilities

			*/
		}
	}


	//H.265 Decode Operations  �μ�p3504
	{}
	{
		/*
		video decode operations ʹ��һ�� H.265 decode profile ��������ITU-T H.265 Specification ������video stream���н���
		
		�����д����һЩ���ݽṹ���Ӧ��ITU-T H.265 Specification �еĶ�Ӧ����:
			 StdVideoH265VideoParameterSet   ->   H.265 video parameter set
			 StdVideoH265SequenceParameterSet ->  H.265 sequence parameter set
			 StdVideoH265PictureParameterSet  ->   H.265 picture parameter set
			 StdVideoDecodeH265PictureInfo   ->    H.265 picture information
			 StdVideoDecodeH265ReferenceInfo ->   H.265 reference information
		*/

		//H.265 Decode Bitstream Data Access  ��Ҫ����video bitstream buffer�д洢�����ݸ�ʽ��  ������ϸ��Ϣ�μ�p3505 ***

		//H.265 Decode Picture Data Access  ��Ҫ������η���video picture resource�е�image ���ݣ� ������ϸ��Ϣ�μ�p3505  ***



		// H.265 Decode Profile �μ�p3506
		{
			/*
			video profile ֧��H.265 video decode operations ��Ҫ��VkVideoProfileInfoKHR::videoCodecOperation ����ΪVK_VIDEO_CODEC_OPERATION_DECODE_H265_BIT_KHR ������ VkVideoProfileInfoKHR::pNext �����һ��VkVideoDecodeH265ProfileInfoKHR
			*/

			VkVideoDecodeH265ProfileInfoKHR videoDecodeH265ProfileInfoKHR{};
			videoDecodeH265ProfileInfoKHR.sType = VK_STRUCTURE_TYPE_VIDEO_DECODE_H265_PROFILE_INFO_KHR;
			videoDecodeH265ProfileInfoKHR.pNext = nullptr;
			videoDecodeH265ProfileInfoKHR.stdProfileIdc = STD_VIDEO_H265_PROFILE_IDC_MAIN;//Ϊһ��StdVideoH265ProfileIdc ֵ��ָ��H.265 codec profile IDC�������� ITU-T H.265 Specification�е�A.3�½ڣ�

		}

		//H.265 Decode Capabilities  �μ�p3506
		{
			/*
			������ vkGetPhysicalDeviceVideoCapabilitiesKHR ��ѯ H.265 decode profile����ʱ,��Ҫ��VkVideoCapabilitiesKHR::pNext �����һ��VkVideoDecodeH265CapabilitiesKHR������profile-specific ����

			*/

			VkVideoDecodeH265CapabilitiesKHR videoDecodeH265CapabilitiesKHR{};
			videoDecodeH265CapabilitiesKHR.sType = VK_STRUCTURE_TYPE_VIDEO_DECODE_H265_CAPABILITIES_KHR;
			videoDecodeH265CapabilitiesKHR.pNext = nullptr;
			videoDecodeH265CapabilitiesKHR.maxLevelIdc = STD_VIDEO_H265_LEVEL_IDC_1_0;//һ��StdVideoH265LevelIdc ֵ��ָ����profile֧�ֵ�����H.265 level������ֵ��ʽΪSTD_VIDEO_H265_LEVEL_IDC_<major>_<minor> ָ��H.265 level�� <major>.<minor> �μ� ITU-T H.265 Specification��A.4�½�


		}


		//H.265 Decode Parameter Sets  �μ�p3507
		{
			/*
			��VK_VIDEO_CODEC_OPERATION_DECODE_H265_BIT_KHR������ video session parameters ��������²�����:
				> H.265 Video Parameter Sets (VPS) �����飨�� ITU-T H.265 Specification��,��ӦStdVideoH265VideoParameterSet ���������в����ľ������� ��p3507 *** ;
				> H.265 Sequence Parameter Sets (SPS)�����飨�� ITU-T H.265 Specification��,��ӦStdVideoH265SequenceParameterSet ���������в����ľ������� ��p3508 *** ;
				> H.265 Picture Parameter Sets (PPS)�����飨�� ITU-T H.265 Specification��,��Ӧ StdVideoH265PictureParameterSet ���������в����ľ������� ��p3511 *** ;

			*/


			//��һ��video session parameters ��VK_VIDEO_CODEC_OPERATION_DECODE_H265_BIT_KHR ����ʱ��  VkVideoSessionParametersCreateInfoKHR::pNext �б������һ�� VkVideoDecodeH265SessionParametersCreateInfoKHR ָ���ö���ĳ�ʼ����
			VkVideoDecodeH265SessionParametersCreateInfoKHR videoDecodeH265SessionParametersCreateInfoKHR{};
			videoDecodeH265SessionParametersCreateInfoKHR.sType = VK_STRUCTURE_TYPE_VIDEO_DECODE_H265_SESSION_PARAMETERS_CREATE_INFO_KHR;
			videoDecodeH265SessionParametersCreateInfoKHR.pNext = nullptr;
			videoDecodeH265SessionParametersCreateInfoKHR.maxStdVPSCount = 1;//Ϊ������ VkVideoSessionParametersKHR �ܰ�����H.265 VPS ʵ����������
			videoDecodeH265SessionParametersCreateInfoKHR.maxStdSPSCount = 1;//Ϊ������ VkVideoSessionParametersKHR �ܰ�����H.265 SPS ʵ����������
			videoDecodeH265SessionParametersCreateInfoKHR.maxStdPPSCount = 1;//Ϊ������ VkVideoSessionParametersKHR �ܰ�����H.265 PPS ʵ����������
			VkVideoDecodeH265SessionParametersAddInfoKHR videoDecodeH265SessionParametersAddInfoKHR{};
			{
				videoDecodeH265SessionParametersAddInfoKHR.sType = VK_STRUCTURE_TYPE_VIDEO_DECODE_H265_SESSION_PARAMETERS_ADD_INFO_KHR;
				videoDecodeH265SessionParametersAddInfoKHR.pNext = nullptr;
				videoDecodeH265SessionParametersAddInfoKHR.stdVPSCount = 1;//ΪpStdVPSs �е�Ԫ�ظ���
				StdVideoH265VideoParameterSet stdVideoH265VideoParameterSet{/*��������һ����Ч��StdVideoH265VideoParameterSet �ṹ��*/ };//һ��StdVideoH265VideoParameterSet ����ָ��ָ����ӵ�H.265 VPS ʵ��
				videoDecodeH265SessionParametersAddInfoKHR.pStdVPSs = &stdVideoH265VideoParameterSet;
				videoDecodeH265SessionParametersAddInfoKHR.stdSPSCount = 1;//ΪpStdSPSs �е�Ԫ�ظ���
				StdVideoH265SequenceParameterSet stdVideoH265SequenceParameterSet{/*��������һ����Ч��StdVideoH265SequenceParameterSet �ṹ��*/ };
				videoDecodeH265SessionParametersAddInfoKHR.pStdSPSs = &stdVideoH265SequenceParameterSet;//һ��StdVideoH265SequenceParameterSet ����ָ��ָ����ӵ�H.265 SPS ʵ��
				videoDecodeH265SessionParametersAddInfoKHR.stdPPSCount = 1;//ΪpStdPPSs �е�Ԫ�ظ���
				StdVideoH265PictureParameterSet stdVideoH265PictureParameterSet{/*��������һ����Ч��StdVideoH265PictureParameterSet �ṹ��*/ };
				videoDecodeH265SessionParametersAddInfoKHR.pStdPPSs = &stdVideoH265PictureParameterSet;//һ�� StdVideoH265PictureParameterSet ����ָ��ָ����ӵ�H.265 PPS ʵ��
				/*
				VkVideoDecodeH265SessionParametersAddInfoKHR��Ч�÷�:
				1.pStdVPSs��ÿ��StdVideoH265VideoParameterSetԪ�ص� vps_video_parameter_set_id������Ψһ��
				2.pStdSPSs��ÿ��StdVideoH265PictureParameterSetԪ�ص� sps_video_parameter_set_id �Լ� sps_seq_parameter_set_id �����Ա�����Ψһ��
				3.pStdPPSs��ÿ��StdVideoH265PictureParameterSetԪ�ص� sps_video_parameter_set_id,pps_seq_parameter_set_id�Լ� pps_pic_parameter_set_id�Ĳ�����Ԫ�������Ψһ��
				*/
			}
			videoDecodeH265SessionParametersCreateInfoKHR.pParametersAddInfo = &videoDecodeH265SessionParametersAddInfoKHR;//ΪNULL����һ�� VkVideoDecodeH265SessionParametersAddInfoKHR ָ��ָ������ʱ��ӵ�H.265 parameters


		}




		//H.265 Decoding Parameters  �μ�p3513
		{
			//��vkCmdDecodeVideoKHR �� VkVideoDecodeInfoKHR.pNext�а���VkVideoDecodeH265PictureInfoKHR ָ�� H.265 decode operation��codec-specific picture ��Ϣ����Щ��Ϣ��ν��Ͳμ� p3514 ***
			VkVideoDecodeH265PictureInfoKHR  videoDecodeH265PictureInfoKHR{};
			videoDecodeH265PictureInfoKHR.sType = VK_STRUCTURE_TYPE_VIDEO_DECODE_H265_PICTURE_INFO_KHR;
			videoDecodeH265PictureInfoKHR.pNext = nullptr;
			videoDecodeH265PictureInfoKHR.sliceSegmentCount = 1;//pSliceSegmentOffsets �е�Ԫ�ظ���
			uint32_t sliceSegmentOffset = 0;
			videoDecodeH265PictureInfoKHR.pSliceSegmentOffsets = &sliceSegmentOffset;//ָ��picture��ÿ��slice segments������ VkVideoDecodeInfoKHRָ���� video bitstream buffer ��Χ�е���ʼ�ֽ�ƫ����
			StdVideoDecodeH265PictureInfo stdVideoDecodeH265PictureInfo{/*��������һ����Ч��StdVideoDecodeH265PictureInfo �ṹ��*/ };
			videoDecodeH265PictureInfoKHR.pStdPictureInfo = &stdVideoDecodeH265PictureInfo;//һ��StdVideoDecodeH265PictureInfo ��ָ�룬ָ�� H.265 picture information


			//������ VkVideoDecodeInfoKHR::pSetupReferenceSlot->pNext �Լ�  VkVideoDecodeInfoKHR::pReferenceSlots->pNext �а���VkVideoDecodeH265DpbSlotInfoKHR  ��ָ��codec-specific reference picture information��������Ϣ��ν��ͼ�  p3517 ***
			VkVideoDecodeH265DpbSlotInfoKHR  videoDecodeH265DpbSlotInfoKHR{};
			videoDecodeH265DpbSlotInfoKHR.sType = VK_STRUCTURE_TYPE_VIDEO_DECODE_H265_DPB_SLOT_INFO_KHR;
			videoDecodeH265DpbSlotInfoKHR.pNext = nullptr;
			StdVideoDecodeH265ReferenceInfo stdVideoDecodeH265ReferenceInfo{/*��������һ����Ч��StdVideoDecodeH265ReferenceInfo �ṹ��*/ };
			videoDecodeH265DpbSlotInfoKHR.pStdReferenceInfo = &stdVideoDecodeH265ReferenceInfo;//һ��StdVideoDecodeH265ReferenceInfo ָ�룬ָ�� H.265 reference information

		}

		//H.265 Decode Requirements  �μ�p3517
		{
			/*
			Ҫ֧��H.265 decoding����physical device����Ҫ����һ��֧��VK_VIDEO_CODEC_OPERATION_DECODE_H265_BIT_KHR�Ķ����壬��vkGetPhysicalDeviceQueueFamilyProperties2���ص�VkQueueFamilyVideoPropertiesKHR::videoCodecOperations

			����֮�⣬��Ҫ��physical deviceҪ����֧��ָ������Ҫ�������p3517
			Table 53. Required Video Std Header Versions
			Table 54. Required Video Capabilities

			*/
		}
	}


	//AV1 Decode Operations  �μ�p3518
	{}
	{
		/*
		video decode operations ʹ��һ��AV1 decode profile �������� AV1 Specification������video stream���н���
		
		�����д����һЩ���ݽṹ���Ӧ��AV1 Specification �еĶ�Ӧ����:
			 StdVideoAV1SequenceHeader   ->   �洢��video session parameters��ָ�� active sequence header
			 StdVideoDecodeAV1PictureInfo ->   AV1 picture information
			 StdVideoDecodeAV1ReferenceInfo  ->  AV1 reference information
		*/


		//AV1 Decode Bitstream Data Access  ��Ҫ����video bitstream buffer�д洢�����ݸ�ʽ��  ������ϸ��Ϣ�μ�p3519 ***

		//AV1 Decode Picture Data Access  ��Ҫ������η���video picture resource�е�image ���ݣ�  ������ϸ��Ϣ�μ�p3519  ***


		//AV1 Reference Names and Semantics  �μ�p3520,  ��Ҫ����Ϊ��ͬ�� reference frames�в�ͬ�����壬������StdVideoAV1ReferenceName ���͵Ĳ�ͬö��ֵ�����ò�ͬ��reference frames
		
		
		//AV1 Decode Profile �μ�p3520
		{
			/*
			video profile ֧��AV1 video decode operations ��Ҫ��VkVideoProfileInfoKHR::videoCodecOperation ����ΪVK_VIDEO_CODEC_OPERATION_DECODE_AV1_BIT_KHR ������ VkVideoProfileInfoKHR::pNext �����һ�� VkVideoDecodeAV1ProfileInfoKHR
			*/
		
			VkVideoDecodeAV1ProfileInfoKHR  videoDecodeAV1ProfileInfoKHR{};
			videoDecodeAV1ProfileInfoKHR.sType = VK_STRUCTURE_TYPE_MAX_ENUM;//û�ж����������ﶨ��Ϊ�Ƿ�ֵ
			videoDecodeAV1ProfileInfoKHR.pNext = nullptr;
			videoDecodeAV1ProfileInfoKHR.filmGrainSupport = VK_TRUE;//ָ���Ƿ�֧��AV1 film grain��������AV1 Specification�е� 7.8.3�ڣ������ΪVK_TRUE�����video profile������video session������decode�����п���film grain
			videoDecodeAV1ProfileInfoKHR.stdProfile = 0;//Ϊһ��StdVideoAV1Profile ֵ��ָ��AV1 codec profile�������� AV1 Specification�е�A.2�½ڣ�
		
				}
		
		
		//AV1 Decode Capabilities  �μ�p3521
		{
			/*
			������ vkGetPhysicalDeviceVideoCapabilitiesKHR ��ѯ AV1 decode profile����ʱ,��Ҫ��VkVideoCapabilitiesKHR::pNext �����һ��VkVideoDecodeAV1CapabilitiesKHR������profile-specific ����
		
			*/
		
			VkVideoDecodeAV1CapabilitiesKHR videoDecodeAV1CapabilitiesKHR{};
			videoDecodeAV1CapabilitiesKHR.sType = VK_STRUCTURE_TYPE_MAX_ENUM;//û�ж����������ﶨ��Ϊ�Ƿ�ֵ
			videoDecodeAV1CapabilitiesKHR.pNext = nullptr;
			videoDecodeAV1CapabilitiesKHR.maxLevel = 0;//һ��StdVideoAV1Level ֵ��ָ����profile֧�ֵ�����AV1 level���μ�AV1 Specification��A.3�½ڣ�
		
		
		}
		
		
		//AV1 Decode Parameter Sets  �μ�p3522
		{
			/*
			��VK_VIDEO_CODEC_OPERATION_DECODE_AV1_BIT_KHR������ video session parameters ��������²���:
				> AV1 Sequence Header ���ݽṹ���� AV1 Specification��,��ӦStdVideoAV1SequenceHeader ���������в����ľ������� ��p3522 *** ;
		
			*/
		
		
			//��һ��video session parameters ��VK_VIDEO_CODEC_OPERATION_DECODE_AV1_BIT_KHR ����ʱ��  VkVideoSessionParametersCreateInfoKHR::pNext �б������һ�� VkVideoDecodeAV1SessionParametersCreateInfoKHR ָ���ö��������
			VkVideoDecodeAV1SessionParametersCreateInfoKHR videoDecodeAV1SessionParametersCreateInfoKHR{};
			videoDecodeAV1SessionParametersCreateInfoKHR.sType = VK_STRUCTURE_TYPE_MAX_ENUM;//û�ж����������ﶨ��Ϊ�Ƿ�ֵ
			videoDecodeAV1SessionParametersCreateInfoKHR.pNext = nullptr;
			StdVideoAV1SequenceHeader stdVideoAV1SequenceHeader{};
			videoDecodeAV1SessionParametersCreateInfoKHR.pStdSequenceHeader = &stdVideoAV1SequenceHeader;//Ϊһ�� StdVideoAV1SequenceHeader ��ָ�룬�����洢��video session parameters�����е� AV1 sequence header���ڴ���video session parametersʱָ����������ͨ��vkUpdateVideoSessionParametersKHR ����
		
		}
		
		
		//AV1 Decoding Parameters  �μ�p3513
		{
			//��vkCmdDecodeVideoKHR �� VkVideoDecodeInfoKHR.pNext�а���VkVideoDecodeAV1PictureInfoKHR ָ�� AV1 decode operation��codec-specific picture ��Ϣ����Щ��Ϣ��ν��Ͳμ� p3524 - p3526***
			VkVideoDecodeAV1PictureInfoKHR  videoDecodeAV1PictureInfoKHR{};
			videoDecodeAV1PictureInfoKHR.sType = VK_STRUCTURE_TYPE_MAX_ENUM;//û�ж����������ﶨ��Ϊ�Ƿ�ֵ
			videoDecodeAV1PictureInfoKHR.pNext = nullptr;
			StdVideoDecodeAV1PictureInfo stdVideoDecodeAV1PictureInfo{/*��������һ����Ч��StdVideoDecodeAV1PictureInfo*/ };
			videoDecodeAV1PictureInfoKHR.pStdPictureInfo = &stdVideoDecodeAV1PictureInfo; //һ��StdVideoDecodeAV1PictureInfo ָ�룬ָ�� AV1 picture information
			videoDecodeAV1PictureInfoKHR.referenceNameSlotIndices[VK_MAX_VIDEO_AV1_REFERENCES_PER_FRAME_KHR];//ΪVK_MAX_VIDEO_AV1_REFERENCES_PER_FRAME_KHR ������ֵ�����飬ÿ��Ԫ��Ϊһ����������ָ����Ӧ AV1 reference name�� DPB slot ������AV1 reference name frame��DPB slot����Ϊ referenceNameSlotIndices[frame - STD_VIDEO_AV1_REFERENCE_NAME_LAST_FRAME]
			for (uint32_t i = 0; i < VK_MAX_VIDEO_AV1_REFERENCES_PER_FRAME_KHR; i++)
			{
				videoDecodeAV1PictureInfoKHR.referenceNameSlotIndices[i] = 0;
			}
			videoDecodeAV1PictureInfoKHR.frameHeaderOffset = 0;//ΪAV1 frame header OBU�� VkVideoDecodeInfoKHR��ָ���� video bitstream buffer�ķ�Χ�ڵ���ʼ�ֽ�ƫ����
			videoDecodeAV1PictureInfoKHR.tileCount = 1;//Ϊ pTileOffsets �Լ� pTileSizes�е�Ԫ�ظ���
			uint32_t tileOffset = 0, tileSize = 4;
			videoDecodeAV1PictureInfoKHR.pTileOffsets = &tileOffset;//Ϊ picture��tiles�� VkVideoDecodeInfoKHR��ָ���� video bitstream buffer�ķ�Χ�ڵ���ʼ�ֽ�ƫ����������ָ��
			videoDecodeAV1PictureInfoKHR.pTileSizes = &tileSize;//Ϊ picture��tiles�� VkVideoDecodeInfoKHR��ָ���� video bitstream buffer�ķ�Χ�ڵ��ֽ�������С������ָ��
		
		
			//������ VkVideoDecodeInfoKHR::pSetupReferenceSlot->pNext �Լ�  VkVideoDecodeInfoKHR::pReferenceSlots->pNext �а���VkVideoDecodeAV1DpbSlotInfoKHR  ��ָ��codec-specific reference picture information��������Ϣ��ν��ͼ�  p3527 ***
			VkVideoDecodeAV1DpbSlotInfoKHR  videoDecodeAV1DpbSlotInfoKHR{};
			videoDecodeAV1DpbSlotInfoKHR.sType = VK_STRUCTURE_TYPE_MAX_ENUM;//û�ж����������ﶨ��Ϊ�Ƿ�ֵ
			videoDecodeAV1DpbSlotInfoKHR.pNext = nullptr;
			StdVideoDecodeAV1ReferenceInfo stdVideoDecodeAV1ReferenceInfo{/*��������һ����Ч��StdVideoDecodeAV1ReferenceInfo �ṹ��*/ };
			videoDecodeAV1DpbSlotInfoKHR.pStdReferenceInfo = &stdVideoDecodeAV1ReferenceInfo;//һ��StdVideoDecodeAV1ReferenceInfo ָ�룬ָ�� AV1 reference information
		
		}
		
		
		// AV1 Decode Requirements  �μ�p3528
		{
			/*
			Ҫ֧�� AV1 decoding����physical device����Ҫ����һ��֧��VK_VIDEO_CODEC_OPERATION_DECODE_AV1_BIT_KHR�Ķ����壬��vkGetPhysicalDeviceQueueFamilyProperties2���ص�VkQueueFamilyVideoPropertiesKHR::videoCodecOperations
		
			����֮�⣬��Ҫ��physical deviceҪ����֧��ָ������Ҫ�������p3528
			Table 55. Required Video Std Header Versions
			Table 56. Required Video Capabilities
		
			*/
		}
	}



	// Video Encode Operations  �μ�3529
	{}
	{
		/*
		video encode operations ����һ�� encode input picture �Լ�������߶�� reference pictures���������洢��video bitstream buffer  �Լ���ѡ��һ��reconstructed  picture �е�ѹ��������
		
		video encode operations �ж���Դ��ͬ����VK_PIPELINE_STAGE_2_VIDEO_ENCODE_BIT_KHR stage���������ڸò����������Դ�� VK_ACCESS_2_VIDEO_ENCODE_READ_BIT_KHR. ���ʣ������VK_ACCESS_2_VIDEO_ENCODE_WRITE_BIT_KHR ���ʡ������ڲ����е�image��layout�ڳ��˸�imageֻ������Ϊһ��encode input picture Ϊ VK_IMAGE_LAYOUT_VIDEO_ENCODE_SRC_KHR�����������ΪVK_IMAGE_LAYOUT_VIDEO_ENCODE_DPB_KHR
		*/
		
		
		// Codec-Specific Semantics �μ�p3530  
		{
			/*
			video encode operations��һЩ���������Ϊ�� codec-specific������Ӧ���õ�codec�������ͣ���Щ�������Ϊ����������ͬ
			*/

			//Video Encode Parameter Overrides  �μ�p3531  , �򵥽����Ǹ���ѹ�����ƣ�ʵ��һ������Video Std headers�а���һ����codec-specific parameters����Ϊ���ȫ����codec-specific parameters�ǲ���ʵ�ģ�����ʵ�������޸���Щcodec-specific parameters��
		}

		//Video Encode Operation Steps  �μ�p3531  ������Ϊvideo encode operations��һЩ����Ϊ�� ��ȡ input picture������ -> ȷ��������������ϢȻ��ִ�б������ -> д��������ݵ�video bitstream buffer  ->�������Ҫ����ݱ�������ִ�� picture reconstructionȻ�����д�� reconstructed picture 

		//Capabilities �μ�p3532
		{

			// VkVideoEncodeCapabilitiesKHR ���԰����ڵ��� vkGetPhysicalDeviceVideoCapabilitiesKHR����� VkVideoCapabilitiesKHR.pNext�����ڷ�����Ƶ������������Ϣ
			//VkVideoCapabilitiesKHR.pNext
			VkVideoEncodeCapabilitiesKHR videoEncodeCapabilitiesKHR{};
			videoEncodeCapabilitiesKHR.sType = VK_STRUCTURE_TYPE_MAX_ENUM;//û�ж�����������Ϊ�Ƿ�ֵ
			videoEncodeCapabilitiesKHR.pNext = nullptr;
			videoEncodeCapabilitiesKHR.flags = VK_VIDEO_ENCODE_CAPABILITY_PRECEDING_EXTERNALLY_ENCODED_BYTES_BIT_KHR;/*VkVideoEncodeCapabilityFlagBitsKHR ���ֵλ���룬��������֧�ֵ�����
			VkVideoEncodeCapabilityFlagBitsKHR:
			VK_VIDEO_ENCODE_CAPABILITY_PRECEDING_EXTERNALLY_ENCODED_BYTES_BIT_KHR : ָ��ʵ��֧��ʹ��VkVideoEncodeInfoKHR::precedingExternallyEncodedBytes
			VK_VIDEO_ENCODE_CAPABILITY_INSUFFICIENT_BITSTREAM_BUFFER_RANGE_DETECTION_BIT_KHR : ָ��ʵ���ܹ����ṩ��destination video bitstream buffer���ڴ淶Χ������������video encode operation�����bitstream dataʱ�ܹ�����Լ���VK_QUERY_RESULT_STATUS_INSUFFICIENT_BITSTREAM_BUFFER_RANGE_KHR ���浽query result status			
			*/
			videoEncodeCapabilitiesKHR.rateControlModes = VK_VIDEO_ENCODE_RATE_CONTROL_MODE_DEFAULT_KHR;//VkVideoEncodeRateControlModeFlagBitsKHR ���ֵλ���룬ָ��֧�ֵ� rate control modes
			videoEncodeCapabilitiesKHR.maxRateControlLayers = 1;//ָ��֧�ֵ� rate control layers���������
			videoEncodeCapabilitiesKHR.maxBitrate = 1;//ָ��֧�ֵ�����������
			videoEncodeCapabilitiesKHR.maxQualityLevels = 1;//ָ��֧�ֵ���ɢvideo encode quality levels�����ȼ�����������Ҫ֧��һ��
			videoEncodeCapabilitiesKHR.encodeInputPictureGranularity = VkExtent2D{.width = 1,.height = 1};//ָ��������� encode input picture���ݵ����ȣ������ܵ� codec-specific coding block size������
			videoEncodeCapabilitiesKHR.supportedEncodeFeedbackFlags = VK_VIDEO_ENCODE_FEEDBACK_BITSTREAM_BUFFER_OFFSET_BIT_KHR;//VkVideoEncodeFeedbackFlagBitsKHR ���ֵλ���룬ָ��֧�ֵ� video encode feedback queries��־������Ҫ����VK_VIDEO_ENCODE_FEEDBACK_BITSTREAM_BUFFER_OFFSET_BIT_KHR �Լ�VK_VIDEO_ENCODE_FEEDBACK_BITSTREAM_BYTES_WRITTEN_BIT_KHR


		}


		// Video Encode Quality Levels  �μ�p3535
		{
			/*
			ʵ�ֶ�video encode profile����֧�ֶ�� video encode quality levels����Щ�ȼ������ڱ�������еĹ����Լ��㷨�������Լ�������һ����˵��ʹ�õ�video encode quality levelԽ�ߣ���ʹ�õĹ��߻����㷨Խ�࣬��������Խ�ã����Ⲣ���Ǿ��Եġ�
			
			*/

			//��ѯָ��video encode profile֧�ֵ� video encode quality level
			VkPhysicalDeviceVideoEncodeQualityLevelInfoKHR physicalDeviceVideoEncodeQualityLevelInfoKHR{};
			physicalDeviceVideoEncodeQualityLevelInfoKHR.sType = VK_STRUCTURE_TYPE_MAX_ENUM;//û�ж������ﶨ��Ϊ�Ƿ�ֵ
			physicalDeviceVideoEncodeQualityLevelInfoKHR.pNext = nullptr;
			VkVideoProfileInfoKHR videoProfileInfoKHR{/*��������һ����Ч��VkVideoProfileInfoKHR*/};//ǰ���Ѿ������������ﲻ�ٸ���
			physicalDeviceVideoEncodeQualityLevelInfoKHR.pVideoProfile = &videoProfileInfoKHR;//Ϊ VkVideoProfileInfoKHR ָ�룬ָ��Ҫ��ѯvideo encode quality level ���Ե�video profile
			physicalDeviceVideoEncodeQualityLevelInfoKHR.qualityLevel = 0;//ָ��Ҫ��ѯ���Ե�video encode quality level
			/*
			VkPhysicalDeviceVideoEncodeQualityLevelInfoKHR��Ч�÷�:
			1.pVideoProfile ����ʱ֧�ֵ�video profile
			2.pVideoProfile->videoCodecOperation ����ָ��һ��encode operation
			3.qualityLevel ����С�ڵ���vkGetPhysicalDeviceVideoCapabilitiesKHR ����pVideoProfileָ����video profile���ص�VkVideoEncodeCapabilitiesKHR::maxQualityLevels
			*/


			VkVideoEncodeQualityLevelPropertiesKHR videoEncodeQualityLevelPropertiesKHR{};
			videoEncodeQualityLevelPropertiesKHR.sType = VK_STRUCTURE_TYPE_MAX_ENUM;//û�ж������ﶨ��Ϊ�Ƿ�ֵ
			videoEncodeQualityLevelPropertiesKHR.pNext = nullptr;//���԰���һ�� VkVideoEncodeH264QualityLevelPropertiesKHR ����VkVideoEncodeH265QualityLevelPropertiesKHR
			videoEncodeQualityLevelPropertiesKHR.preferredRateControlLayerCount = 0;//Ϊ���صĸ��ʺ����� video encode quality level �� rate control layers������
			videoEncodeQualityLevelPropertiesKHR.preferredRateControlMode = VK_VIDEO_ENCODE_RATE_CONTROL_MODE_DEFAULT_KHR;//Ϊ���ص� VkVideoEncodeRateControlModeFlagBitsKHRֵ��ָ����video encode quality level���ʺϵ� rate control mode

			vkGetPhysicalDeviceVideoEncodeQualityLevelPropertiesKHR(physicalDevice, &physicalDeviceVideoEncodeQualityLevelInfoKHR, &videoEncodeQualityLevelPropertiesKHR);//������ȷ�����˽��
			/*
			vkGetPhysicalDeviceVideoEncodeQualityLevelPropertiesKHR��Ч�÷�:
			1.���pQualityLevelInfo->pVideoProfile->videoCodecOperationΪVK_VIDEO_CODEC_OPERATION_ENCODE_H264_BIT_KHR����pQualityLevelProperties->pNext�б������һ��VkVideoEncodeH264QualityLevelPropertiesKHR
			2.���pQualityLevelInfo->pVideoProfile->videoCodecOperationΪVK_VIDEO_CODEC_OPERATION_ENCODE_H265_BIT_KHR����pQualityLevelProperties->pNext�б������һ��VkVideoEncodeH265QualityLevelPropertiesKHR
			*/


			//VkVideoEncodeQualityLevelInfoKHR������ VkVideoSessionParametersCreateInfoKHR.pNext�а��� ָ��video sessionҪʹ�õ� video encode quality level���� ��VkVideoCodingControlInfoKHR.pNext�а��� ���ı䵱ǰʹ�õ�video encode quality level
			VkVideoEncodeQualityLevelInfoKHR  videoEncodeQualityLevelInfoKHR{};
			videoEncodeQualityLevelInfoKHR.sType = VK_STRUCTURE_TYPE_MAX_ENUM;//û�ж�����������Ϊ�Ƿ�ֵ
			videoEncodeQualityLevelInfoKHR.pNext = nullptr;
			videoEncodeQualityLevelInfoKHR.qualityLevel = 0;//ʹ�õ� video encode quality level������С�ڵ���vkGetPhysicalDeviceVideoCapabilitiesKHR �����Ӧ��video profile���ص�VkVideoEncodeCapabilitiesKHR::maxQualityLevels
		}


		//Retrieving Encoded Session Parameters  �μ�p3539
		{
			/*
			����ʹ�õ�ѹ����׼���洢��video session�е�codec-specific parameters������Ҫ��������Ȼ���ŵ����յ�video bitstream data�У������������Ӧ�þ���Ҫ��video session parameters �л�ȡ����Ĳ�������

			*/


			//��video session parameters �л�ȡ����Ĳ�������
			VkVideoEncodeSessionParametersGetInfoKHR videoEncodeSessionParametersGetInfoKHR{};
			videoEncodeSessionParametersGetInfoKHR.sType = VK_STRUCTURE_TYPE_MAX_ENUM;//û�ж������ﶨ��Ϊ�Ƿ�ֵ
			videoEncodeSessionParametersGetInfoKHR.pNext = nullptr;//���ܰ��� VkVideoEncodeH264SessionParametersGetInfoKHR ����VkVideoEncodeH265SessionParametersGetInfoKHR
			videoEncodeSessionParametersGetInfoKHR.videoSessionParameters = VkVideoSessionParametersKHR{/*��������һ����Ч��VkVideoSessionParametersKHR*/ };//ָ��Ҫ���ĸ�VkVideoSessionParametersKHR��ȡ����Ĳ���

			VkVideoEncodeSessionParametersFeedbackInfoKHR videoEncodeSessionParametersFeedbackInfoKHR{};
			videoEncodeSessionParametersFeedbackInfoKHR.sType = VK_STRUCTURE_TYPE_MAX_ENUM;//û�ж������ﶨ��Ϊ�Ƿ�ֵ
			videoEncodeSessionParametersFeedbackInfoKHR.pNext = nullptr;//���ܰ���VkVideoEncodeH264SessionParametersFeedbackInfoKHR ���� VkVideoEncodeH265SessionParametersFeedbackInfoKHR
			videoEncodeSessionParametersFeedbackInfoKHR.hasOverrides = VK_FALSE;//ָ������Ĳ��������Ƿ��Ѿ�����д�޸Ĺ�

			size_t encodedSize = 0;
			std::vector<char> encodedData;

			vkGetEncodedVideoSessionParametersKHR(device, &videoEncodeSessionParametersGetInfoKHR, &videoEncodeSessionParametersFeedbackInfoKHR, &encodedSize, nullptr);
			encodedData.resize(encodedSize);
			vkGetEncodedVideoSessionParametersKHR(device, &videoEncodeSessionParametersGetInfoKHR, &videoEncodeSessionParametersFeedbackInfoKHR, &encodedSize, encodedData.data());
			/*
			vkGetEncodedVideoSessionParametersKHR��Ч�÷�:
			1.pVideoSessionParametersInfo->videoSessionParameters ������һ��encode operation ����
			2.���pVideoSessionParametersInfo->videoSessionParameters �� video codec operation VK_VIDEO_CODEC_OPERATION_ENCODE_H264_BIT_KHR ��������1��pVideoSessionParametersInfo.pNext�б������һ��VkVideoEncodeH264SessionParametersGetInfoKHR
																																					��2�����pVideoSessionParametersInfo.pNext��VkVideoEncodeH264SessionParametersGetInfoKHR.writeStdSPSΪVK_TRUE����pVideoSessionParametersInfo->videoSessionParameters�б������һ��seq_parameter_set_id ƥ��VkVideoEncodeH264SessionParametersGetInfoKHR::stdSPSId�� StdVideoH264SequenceParameterSetʵ��
																																					��3�����pVideoSessionParametersInfo.pNext��VkVideoEncodeH264SessionParametersGetInfoKHR.writeStdPPSΪVK_TRUE����pVideoSessionParametersInfo->videoSessionParameters�б������һ��seq_parameter_set_id �Լ� pic_parameter_set_id ������ƥ��VkVideoEncodeH264SessionParametersGetInfoKHR::stdSPSId�Լ�  VkVideoEncodeH264SessionParametersGetInfoKHR::stdPPSId�� StdVideoH264PictureParameterSetʵ��
			3.���pVideoSessionParametersInfo->videoSessionParameters �� video codec operation VK_VIDEO_CODEC_OPERATION_ENCODE_H265_BIT_KHR ��������1��pVideoSessionParametersInfo.pNext�б������һ��VkVideoEncodeH265SessionParametersGetInfoKHR
																																					��2�����pVideoSessionParametersInfo.pNext��VkVideoEncodeH265SessionParametersGetInfoKHR.writeStdVPSΪVK_TRUE����pVideoSessionParametersInfo->videoSessionParameters�б������һ��vps_video_parameter_set_id ƥ��VkVideoEncodeH265SessionParametersGetInfoKHR::stdVPSId�� StdVideoH265VideoParameterSetʵ��
																																					��3�����pVideoSessionParametersInfo.pNext��VkVideoEncodeH265SessionParametersGetInfoKHR.writeStdSPSΪVK_TRUE����pVideoSessionParametersInfo->videoSessionParameters�б������һ��sps_video_parameter_set_id �Լ� sps_seq_parameter_set_id ������ƥ��VkVideoEncodeH265SessionParametersGetInfoKHR::stdVPSId�Լ�  VkVideoEncodeH265SessionParametersGetInfoKHR::stdSPSId�� StdVideoH265SequenceParameterSetʵ��
																																					��4�����pVideoSessionParametersInfo.pNext��VkVideoEncodeH265SessionParametersGetInfoKHR.writeStdPPSΪVK_TRUE����pVideoSessionParametersInfo->videoSessionParameters�б������һ��sps_video_parameter_set_id, pps_seq_parameter_set_id, �Լ� pps_pic_parameter_set_id ������ƥ��VkVideoEncodeH265SessionParametersGetInfoKHR::stdVPSId,VkVideoEncodeH265SessionParametersGetInfoKHR::stdSPSId, �Լ�VkVideoEncodeH265SessionParametersGetInfoKHR::stdPPSId�� StdVideoH265PictureParameterSetʵ��
 
			*/


		}


		//Video Encode Commands  �μ�p3544
		{
			VkCommandBuffer commandBuffer{/*��������һ����Ч��VkCommandBuffer*/ };

			struct VideoEncodeInfoKHREXT {
				VkVideoEncodeH264PictureInfoKHR videoEncodeH264PictureInfoKHR{};
				VkVideoEncodeH265PictureInfoKHR videoEncodeH265PictureInfoKHR{};
				VkVideoInlineQueryInfoKHR videoInlineQueryInfoKHR{};
				VideoEncodeInfoKHREXT() {
					Init();
				}
				void Init() {
					videoEncodeH264PictureInfoKHR.sType = VK_STRUCTURE_TYPE_MAX_ENUM;//û�ж����������ﶨ��Ϊ�Ƿ�ֵ
					videoEncodeH264PictureInfoKHR.pNext = nullptr;
					videoEncodeH265PictureInfoKHR.sType = VK_STRUCTURE_TYPE_MAX_ENUM;//û�ж����������ﶨ��Ϊ�Ƿ�ֵ
					videoEncodeH265PictureInfoKHR.pNext = nullptr;
					videoInlineQueryInfoKHR.sType = VK_STRUCTURE_TYPE_MAX_ENUM;//û�ж����������ﶨ��Ϊ�Ƿ�ֵ
					videoInlineQueryInfoKHR.pNext = nullptr;
				}
			};

			//����opCount�� video encode operations
			VkVideoEncodeInfoKHR videoEncodeInfoKHR{};
			videoEncodeInfoKHR.sType = VK_STRUCTURE_TYPE_MAX_ENUM;//û�ж����������ﶨ��Ϊ�Ƿ�ֵ
			VideoEncodeInfoKHREXT videoEncodeInfoKHREXT{};
			videoEncodeInfoKHR.pNext = &videoEncodeInfoKHREXT.videoEncodeH264PictureInfoKHR;
			videoEncodeInfoKHR.flags = VK_VIDEO_ENCODE_TUNING_MODE_DEFAULT_KHR;
			videoEncodeInfoKHR.dstBuffer = VkBuffer{/*��������һ����Ч��VkBuffer*/ };//Ϊ��� encoded bitstream�� destination video bitstream buffer
			videoEncodeInfoKHR.dstBufferOffset = 0;//dstBuffer �е���ʼ�ֽ�ƫ����
			videoEncodeInfoKHR.dstBufferRange = 4;//dstBuffer �д�dstBufferOffset��ʼ�Ŀ��Դ�ŵ�bitstream������ֽ���
			VkVideoPictureResourceInfoKHR srcPictureResource{};
			{
				srcPictureResource.sType = VK_STRUCTURE_TYPE_VIDEO_PICTURE_RESOURCE_INFO_KHR;
				srcPictureResource.pNext = nullptr;
				srcPictureResource.baseArrayLayer = 0;
				srcPictureResource.codedExtent = VkExtent2D{ .width = 1,.height = 1 };
				srcPictureResource.codedOffset = VkOffset2D{ .x = 0,.y = 0 };
				srcPictureResource.imageViewBinding = VkImageView{/*��������һ����Ч��VkImageView*/ };
			}
			videoEncodeInfoKHR.srcPictureResource = srcPictureResource;//ָ������Encode Input Picture��video picture resource
			VkVideoReferenceSlotInfoKHR videoReferenceSlotInfoKHR{};
			{
				videoReferenceSlotInfoKHR.sType = VK_STRUCTURE_TYPE_VIDEO_REFERENCE_SLOT_INFO_KHR;
				videoReferenceSlotInfoKHR.pNext = nullptr;
				videoReferenceSlotInfoKHR.slotIndex = 0;
				VkVideoPictureResourceInfoKHR testPictureResource{/*��������һ����Ч��VkVideoPictureResourceInfoKHR*/ };
				videoReferenceSlotInfoKHR.pPictureResource = &testPictureResource;

			}
			videoEncodeInfoKHR.pSetupReferenceSlot = &videoReferenceSlotInfoKHR;//ΪNULL����VkVideoReferenceSlotInfoKHR ָ�룬 ָ����ѡ��Reconstructed Picture ��Ϣ
			videoEncodeInfoKHR.referenceSlotCount = 1;// pReferenceSlots ��Ԫ�ظ���
			videoEncodeInfoKHR.pReferenceSlots = &videoReferenceSlotInfoKHR;//ΪNULL����VkVideoReferenceSlotInfoKHR ����ָ�룬��������video encode operation ��DPB slots �Լ���Ӧ�� reference picture �������Reference Picture �飩
			videoEncodeInfoKHR.precedingExternallyEncodedBytes = 0;//ΪӦ���ⲿ���뵽 video bitstream���ֽ��������ڸ���ʵ�ֵ����ʿ����㷨���ڲ�״̬���Կ�����Щ�ⲿ������ֽ������ĵı�����Ԥ�㡣
			/*
			VkVideoEncodeInfoKHR��Ч�÷�:
			1.dstBuffer ������VK_BUFFER_USAGE_VIDEO_DECODE_DST_BIT_KHR ��Ǵ���
			2.dstBufferOffset ����С��dstBuffer�Ĵ�С
			3.dstBufferRange ����С�ڵ���dstBuffer�Ĵ�С ��ȥdstBufferOffset
			4.���pSetupReferenceSlot ��ΪNULL������slotIndex ����Ϊ��������pPictureResource ����ΪNULL
			5.pReferenceSlots ��ÿ��Ԫ�ص�slotIndex ����Ϊ������pPictureResource ����ΪNULL

			*/


			//�ýӿڵ�����ע����Ϣ�Լ�ʹ��ʱһЩ������������Ϣ�� *** p3544- p3547
			vkCmdEncodeVideoKHR(commandBuffer, &videoEncodeInfoKHR);
			/*
			vkCmdEncodeVideoKHR��Ч�÷�:
			1.�󶨵�video session ������һ�� encode operation ���������ڸ��������豸��ִ�е�ʱ��video session ����Ϊ�ǳ�ʼ����״̬
			2.���������豸��ִ�е�ʱ�򣬰󶨵�video session parameters �����Ե�ǰ�󶨵�video session���õ�video encode quality level ����
			3.��ÿ�������query����Ӧquery type�ļ����query �������� opCount ����С�ڵ��ڸ�query type�����һ�������query ������1
			4.����󶨵�video session ��VK_VIDEO_SESSION_CREATE_INLINE_QUERIES_BIT_KHR ��������pEncodeInfo->pNext�а���һ��queryPool ָ��һ����Ч��VkQueryPool��VkVideoInlineQueryInfoKHR����1��VkVideoInlineQueryInfoKHR::queryCount �������opCount
																																															 ��2�����и�����ʹ�õ�VkVideoInlineQueryInfoKHR�е�query����Ϊunavailable��״̬
																																															 ��3�������ڴ���VkVideoInlineQueryInfoKHR.queryPool�� queryType ����ΪVK_QUERY_TYPE_RESULT_STATUS_ONLY_KHR ����VK_QUERY_TYPE_VIDEO_ENCODE_FEEDBACK_KHR
																																															 ��4��VkVideoInlineQueryInfoKHR.queryPool ����Ҫ��VkQueryPoolCreateInfo.pNext�а���һ����video session����ʱVkVideoSessionCreateInfoKHR::pVideoProfile ��һ��Ԫ����ȵ�VkVideoProfileInfoKHR ����
																																															 ��5��������ڴ���VkVideoInlineQueryInfoKHR.queryPool�� queryType ΪVK_QUERY_TYPE_RESULT_STATUS_ONLY_KHR����commandBuffer���ڵ�VkCommandPool�Ķ��������֧��result status queries�����������VkQueueFamilyQueryResultStatusPropertiesKHR::queryResultStatusSupport
			5.pEncodeInfo->dstBuffer ��������ڰ󶨵�video session ����ʱʹ�õ�video profile
			6.���commandBuffer��unprotected command buffer ��protectedNoFault��֧�֣���pEncodeInfo->dstBuffer ������protected buffer
			7.���commandBuffer��protected command buffer ��protectedNoFault��֧�֣���pEncodeInfo->dstBuffer ������protected buffer
			8.pEncodeInfo->dstBufferOffset �����ǵ���vkGetPhysicalDeviceVideoCapabilitiesKHR�����video session����ʱ��video profile���ص�VkVideoCapabilitiesKHR::minBitstreamBufferOffsetAlignment��������
			9.pEncodeInfo->dstBufferRange �����ǵ���vkGetPhysicalDeviceVideoCapabilitiesKHR�����video session����ʱ��video profile���ص�VkVideoCapabilitiesKHR::minBitstreamBufferSizeAlignment��������
			10.pEncodeInfo->srcPictureResource.imageViewBinding ������ݰ󶨵�video session����ʱ��video profile
			11.pEncodeInfo->srcPictureResource.imageViewBinding ��format����ƥ�䴴��video sessionʱʹ�õ�VkVideoSessionCreateInfoKHR::pictureFormat
			12.pEncodeInfo->srcPictureResource.codedOffset ������codedOffsetGranularity ��������
			13.pEncodeInfo->srcPictureResource.codedExtent �����ڴ���video session ʱʹ�õ�VkVideoSessionCreateInfoKHR::minCodedExtent �� VkVideoSessionCreateInfoKHR::maxCodedExtent ֮��
			14.pEncodeInfo->srcPictureResource.imageViewBinding ������VK_IMAGE_USAGE_VIDEO_ENCODE_SRC_BIT_KHR ����
			15.���commandBuffer��unprotected command buffer ��protectedNoFault��֧�֣���pEncodeInfo->srcPictureResource.imageViewBinding ���ܴ�protected image �ϴ���
			16.���commandBuffer��protected command buffer ��protectedNoFault��֧�֣���pEncodeInfo->srcPictureResource.imageViewBinding �����protected image �ϴ���
			17.pEncodeInfo->pSetupReferenceSlot ���벻ΪNULL���ǰ󶨵�video session ������ʱָ����VkVideoSessionCreateInfoKHR::maxDpbSlots Ϊ0
			18.��� pEncodeInfo->pSetupReferenceSlot ��ΪNULL����1��pEncodeInfo->pSetupReferenceSlot->slotIndex ����С�ڵ��ڴ���video session ʱ VkVideoSessionCreateInfoKHR::maxDpbSlots ָ�������DPB������
																 ��2��pEncodeInfo->pSetupReferenceSlot->pPictureResource->codedOffset ����ΪcodedOffsetGranularity ��������
																 ��3��pEncodeInfo->pSetupReferenceSlot->pPictureResource ����ƥ��һ���󶨵�reference picture resource

			19.activeReferencePictureCount ����С�ڵ��ڴ���video session ʱָ���� VkVideoSessionCreateInfoKHR::maxActiveReferencePictures
			20.pEncodeInfo->pReferenceSlots ��ÿ��Ԫ�ص�slotIndex ����С�ڵ��ڴ���video session ʱ VkVideoSessionCreateInfoKHR::maxDpbSlots ָ�������DPB������
			21.ÿ��pEncodeInfo->pReferenceSlots Ԫ�ص�pPictureResource ��ָ��VkVideoPictureResourceInfoKHR::codedOffset ����ΪcodedOffsetGranularity ��������
			22.ÿ��pEncodeInfo->pReferenceSlots Ԫ�ص�pPictureResource ����ƥ��һ���󶨵Ĺ�������slotIndexָ����DPB slot �����ϵ�reference picture resource
			23.ÿ��pEncodeInfo->pReferenceSlots Ԫ�ص�pPictureResource ��ָ��video picture resource ������pEncodeInfo->pReferenceSlots ����Ψһ��
			24.dpbFrameUseCount������Ԫ�ر���С�ڵ���1 ��������������ģ�ͨ����������ģ������p3545��
			25.pEncodeInfo->pReferenceSlots ��ÿ��Ԫ�ص�pPictureResource ���õ�image subresource �ڸ��������豸��ִ��ʱlayout����Ϊ VK_IMAGE_LAYOUT_VIDEO_ENCODE_SRC_KHR
			26.���pEncodeInfo->pSetupReferenceSlot ��ΪNULL����pEncodeInfo->pSetupReferenceSlot->pPictureResource ��ָ��image subresource �ڸ��������豸��ִ��ʱlayout����Ϊ VK_IMAGE_LAYOUT_VIDEO_ENCODE_DPB_KHR
			27.pEncodeInfo->pReferenceSlots->pPictureResource ��ָ��image subresource �ڸ��������豸��ִ��ʱlayout����Ϊ VK_IMAGE_LAYOUT_VIDEO_ENCODE_DPB_KHR
			28.����󶨵�video session ��video codec operation Ϊ VK_VIDEO_CODEC_OPERATION_ENCODE_H264_BIT_KHR ��������	��1��pEncodeInfo->pNext�б������һ��VkVideoEncodeH264PictureInfoKHR�ṹ
																														��2���󶨵�video session parameters �������seq_parameter_set_id ƥ��pEncodeInfo->pNext��VkVideoEncodeH264PictureInfoKHR::pStdPictureInfo ��Ԫ�ص�StdVideoEncodeH264PictureInfo::seq_parameter_set_id�� StdVideoH264SequenceParameterSet ʵ��
																														��3���󶨵�video session parameters �������seq_parameter_set_id �Լ�pic_parameter_set_id ƥ��pEncodeInfo->pNext��VkVideoEncodeH264PictureInfoKHR::pStdPictureInfo ��Ԫ�ص� StdVideoEncodeH264PictureInfo::seq_parameter_set_id �Լ�StdVideoEncodeH264PictureInfo::pic_parameter_set_id �� StdVideoH264PictureParameterSet ʵ��
																														��4�����pEncodeInfo->pSetupReferenceSlot ��ΪNULL����pEncodeInfo->pSetupReferenceSlot->pNext�б������һ��VkVideoEncodeH264DpbSlotInfoKHR
																														��5����pEncodeInfo->pReferenceSlots��ÿ��Ԫ�ص�pNext�б������һ��VkVideoEncodeH264DpbSlotInfoKHR
																														��6���ҵ�ǰ��rate control modeΪVK_VIDEO_ENCODE_RATE_CONTROL_MODE_DISABLED_BIT_KHR����԰�����pEncodeInfo->pNext�е�VkVideoEncodeH264PictureInfoKHR.pNaluSliceEntries�е�����Ԫ�� VkVideoEncodeH264NaluSliceInfoKHR::constantQp ����Ϊ0
																														��7���ҵ�ǰ��rate control modeΪVK_VIDEO_ENCODE_RATE_CONTROL_MODE_DISABLED_BIT_KHR����԰�����pEncodeInfo->pNext�е�VkVideoEncodeH264PictureInfoKHR.pNaluSliceEntries�е�����Ԫ�� VkVideoEncodeH264NaluSliceInfoKHR::constantQp ����Ϊ ��VkVideoEncodeH264CapabilitiesKHR::minQp ��VkVideoEncodeH264CapabilitiesKHR::maxQp֮�䣨ͨ��vkGetPhysicalDeviceVideoCapabilitiesKHR����video session����ʱ��video profile���أ�
																														��8�����ͨ��vkGetPhysicalDeviceVideoCapabilitiesKHR����video session����ʱ��video profile���ص�VkVideoEncodeH264CapabilitiesKHR::flags ������VK_VIDEO_ENCODE_H264_CAPABILITY_PER_SLICE_CONSTANT_QP_BIT_KHR����԰�����pEncodeInfo->pNext�е�VkVideoEncodeH264PictureInfoKHR.pNaluSliceEntries�е�����Ԫ�� VkVideoEncodeH264NaluSliceInfoKHR::constantQp ֵ������ͬ
																														��9����԰�����pEncodeInfo->pNext�е�VkVideoEncodeH264PictureInfoKHR.naluSliceEntryCount ����С�ڵ���minCodingBlockExtent.width * minCodingBlockExtent.height ��minCodingBlockExtent�Ǽ�������ģ���������p3546��
																														��10�����ͨ��vkGetPhysicalDeviceVideoCapabilitiesKHR����video session����ʱ��video profile���ص�VkVideoEncodeH264CapabilitiesKHR::flags ������VK_VIDEO_ENCODE_H264_CAPABILITY_ROW_UNALIGNED_SLICE_BIT_KHR����԰�����pEncodeInfo->pNext�е�VkVideoEncodeH264PictureInfoKHR.naluSliceEntryCount ����С�ڵ���minCodingBlockExtent.height  ��minCodingBlockExtent�Ǽ�������ģ���������p3546��
																														��11����pEncodeInfo->pNext ����VkVideoEncodeH264PictureInfoKHR����pEncodeInfo->referenceSlotCount ����0����VkVideoEncodeH264PictureInfoKHR::pStdPictureInfo->pRefLists ���벻ΪNULL
																														��12����pEncodeInfo->pNext ����VkVideoEncodeH264PictureInfoKHR����VkVideoEncodeH264PictureInfoKHR::pStdPictureInfo->pRefLists ��ΪNULL����VkVideoEncodeH264PictureInfoKHR::pStdPictureInfo->pRefLists��ÿ��Ԫ��StdVideoEncodeH264ReferenceListsInfo��RefPicList0 �Լ�RefPicList1 �е�ÿ��Ԫ�ر���ΪSTD_VIDEO_H264_NO_REFERENCE_PICTURE ����ΪpEncodeInfo->pReferenceSlots�е�һ��Ԫ�ص�slotIndex
																														��13����pEncodeInfo->pNext ����VkVideoEncodeH264PictureInfoKHR����pEncodeInfo->referenceSlotCount ����0����pEncodeInfo->pReferenceSlots�е�ÿ��Ԫ�ص�slotIndex �������VkVideoEncodeH264PictureInfoKHR::pStdPictureInfo->pRefLists��һ��Ԫ��StdVideoEncodeH264ReferenceListsInfo��RefPicList0 ����RefPicList1 �е�һ��Ԫ��
																														��14�����ͨ��vkGetPhysicalDeviceVideoCapabilitiesKHR����video session����ʱ��video profile���ص�VkVideoEncodeH264CapabilitiesKHR::maxPPictureL0ReferenceCount Ϊ0����h264L0PictureTypes �Լ�h264L1PictureTypes �е�ÿ��Ԫ��h264PictureType ����ΪSTD_VIDEO_H264_PICTURE_TYPE_P ��h264L0PictureTypes�Լ�h264L1PictureTypes��һ��������������飬��������p3546��
																														��15�����ͨ��vkGetPhysicalDeviceVideoCapabilitiesKHR����video session����ʱ��video profile���ص�VkVideoEncodeH264CapabilitiesKHR::maxBPictureL0ReferenceCount �Լ�VkVideoEncodeH264CapabilitiesKHR::maxL1ReferenceCount ��Ϊ0����h264L0PictureTypes �Լ�h264L1PictureTypes �е�ÿ��Ԫ��h264PictureType ����ΪSTD_VIDEO_H264_PICTURE_TYPE_B ��h264L0PictureTypes�Լ�h264L1PictureTypes��һ��������������飬��������p3546��
																														��16�����ͨ��vkGetPhysicalDeviceVideoCapabilitiesKHR����video session����ʱ��video profile���ص�VkVideoEncodeH264CapabilitiesKHR::flags ������VK_VIDEO_ENCODE_H264_CAPABILITY_B_FRAME_IN_L0_LIST_BIT_KHR�� ��h264L0PictureTypes ��ÿ��Ԫ�ز���Ϊ STD_VIDEO_H264_PICTURE_TYPE_B ��h264L0PictureTypes��һ��������������飬��������p3546��
																														��17�����ͨ��vkGetPhysicalDeviceVideoCapabilitiesKHR����video session����ʱ��video profile���ص�VkVideoEncodeH264CapabilitiesKHR::flags ������VK_VIDEO_ENCODE_H264_CAPABILITY_B_FRAME_IN_L1_LIST_BIT_KHR�� ��h264L1PictureTypes ��ÿ��Ԫ�ز���Ϊ STD_VIDEO_H264_PICTURE_TYPE_B ��h264L1PictureTypes��һ��������������飬��������p3546��



			29.����󶨵�video session ��video codec operation Ϊ VK_VIDEO_CODEC_OPERATION_ENCODE_H265_BIT_KHR ��������1��pDecodeInfo->pNext�б������һ��VkVideoEncodeH265PictureInfoKHR�ṹ
																													   ��2���󶨵�video session parameters �������vps_video_parameter_set_id ƥ��pEncodeInfo->pNext��VkVideoEncodeH265PictureInfoKHR::pStdPictureInfo ��Ԫ�ص�StdVideoEncodeH265PictureInfo::sps_video_parameter_set_id�� StdVideoH265VideoParameterSet ʵ��
																													   ��3���󶨵�video session parameters �������sps_video_parameter_set_id �Լ� sps_seq_parameter_set_id ƥ��pEncodeInfo->pNext��VkVideoEncodeH265PictureInfoKHR::pStdPictureInfo ��Ԫ�ص�StdVideoEncodeH265PictureInfo::sps_video_parameter_set_id �Լ� StdVideoEncodeH265PictureInfo::pps_seq_parameter_set_id �� StdVideoH265SequenceParameterSet ʵ��
																													   ��4���󶨵�video session parameters �������sps_video_parameter_set_id, pps_seq_parameter_set_id, �Լ� pps_pic_parameter_set_id ��ƥ��pEncodeInfo->pNext��VkVideoEncodeH265PictureInfoKHR::pStdPictureInfo ��Ԫ�ص�StdVideoEncodeH265PictureInfo::sps_video_parameter_set_id, StdVideoEncodeH265PictureInfo::pps_seq_parameter_set_id, �Լ� StdVideoEncodeH265PictureInfo::pps_pic_parameter_set_id �� StdVideoH265PictureParameterSet ʵ��
																													   ��5�����pEncodeInfo->pSetupReferenceSlot ��ΪNULL����pEncodeInfo->pSetupReferenceSlot->pNext�б������һ��VkVideoEncodeH265DpbSlotInfoKHR
																													   ��6����pEncodeInfo->pReferenceSlots��ÿ��Ԫ�ص�pNext�б������һ��VkVideoEncodeH265DpbSlotInfoKHR
																													   ��7���ҵ�ǰ��rate control modeΪVK_VIDEO_ENCODE_RATE_CONTROL_MODE_DISABLED_BIT_KHR����԰�����pEncodeInfo->pNext�е�VkVideoEncodeH265PictureInfoKHR.pNaluSliceSegmentEntries�е�����Ԫ�� VkVideoEncodeH265NaluSliceSegmentInfoKHR::constantQp ����Ϊ0
																													   ��8���ҵ�ǰ��rate control modeΪVK_VIDEO_ENCODE_RATE_CONTROL_MODE_DISABLED_BIT_KHR����԰�����pEncodeInfo->pNext�е�VkVideoEncodeH265PictureInfoKHR.pNaluSliceSegmentEntries�е�����Ԫ�� VkVideoEncodeH265NaluSliceSegmentInfoKHR::constantQp ����Ϊ ��VkVideoEncodeH265CapabilitiesKHR::minQp ��VkVideoEncodeH265CapabilitiesKHR::maxQp֮�䣨ͨ��vkGetPhysicalDeviceVideoCapabilitiesKHR����video session����ʱ��video profile���أ�
																													   ��9�����ͨ��vkGetPhysicalDeviceVideoCapabilitiesKHR����video session����ʱ��video profile���ص�VkVideoEncodeH265CapabilitiesKHR::flags ������VK_VIDEO_ENCODE_H265_CAPABILITY_PER_SLICE_SEGMENT_CONSTANT_QP_BIT_KHR����԰�����pEncodeInfo->pNext�е�VkVideoEncodeH265PictureInfoKHR.pNaluSliceSegmentEntries�е�����Ԫ�� VkVideoEncodeH265NaluSliceSegmentInfoKHR::constantQp ֵ������ͬ
																													   ��10����԰�����pEncodeInfo->pNext�е�VkVideoEncodeH265PictureInfoKHR.naluSliceSegmentEntryCount ����С�ڵ���minCodingBlockExtent.width * minCodingBlockExtent.height ��minCodingBlockExtent�Ǽ�������ģ���������p3546��
																													   ��11�����ͨ��vkGetPhysicalDeviceVideoCapabilitiesKHR����video session����ʱ��video profile���ص�VkVideoEncodeH265CapabilitiesKHR::flags ������VK_VIDEO_ENCODE_H265_CAPABILITY_ROW_UNALIGNED_SLICE_SEGMENT_BIT_KHR����԰�����pEncodeInfo->pNext�е�VkVideoEncodeH265PictureInfoKHR.naluSliceSegmentEntryCount ����С�ڵ���minCodingBlockExtent.height  ��minCodingBlockExtent�Ǽ�������ģ���������p3546��
																													   ��12����pEncodeInfo->pNext ����VkVideoEncodeH265PictureInfoKHR����pEncodeInfo->referenceSlotCount ����0����VkVideoEncodeH265PictureInfoKHR::pStdPictureInfo->pRefLists ���벻ΪNULL
																													   ��13����pEncodeInfo->pNext ����VkVideoEncodeH265PictureInfoKHR����VkVideoEncodeH265PictureInfoKHR::pStdPictureInfo->pRefLists ��ΪNULL����VkVideoEncodeH265PictureInfoKHR::pStdPictureInfo->pRefLists��ÿ��Ԫ��StdVideoEncodeH265ReferenceListsInfo��RefPicList0 �Լ�RefPicList1 �е�ÿ��Ԫ�ر���ΪSTD_VIDEO_H265_NO_REFERENCE_PICTURE ����ΪpEncodeInfo->pReferenceSlots�е�һ��Ԫ�ص�slotIndex
																													   ��14����pEncodeInfo->pNext ����VkVideoEncodeH265PictureInfoKHR����pEncodeInfo->referenceSlotCount ����0����pEncodeInfo->pReferenceSlots�е�ÿ��Ԫ�ص�slotIndex �������VkVideoEncodeH265PictureInfoKHR::pStdPictureInfo->pRefLists��һ��Ԫ��StdVideoEncodeH265ReferenceListsInfo��RefPicList0 ����RefPicList1 �е�һ��Ԫ��
																													   ��15�����ͨ��vkGetPhysicalDeviceVideoCapabilitiesKHR����video session����ʱ��video profile���ص�VkVideoEncodeH265CapabilitiesKHR::maxPPictureL0ReferenceCount Ϊ0����h265L0PictureTypes �Լ�h265L1PictureTypes �е�ÿ��Ԫ��h265PictureType ����ΪSTD_VIDEO_H265_PICTURE_TYPE_P ��h265L0PictureTypes�Լ�h265L1PictureTypes��һ��������������飬��������p3547��
																													   ��16�����ͨ��vkGetPhysicalDeviceVideoCapabilitiesKHR����video session����ʱ��video profile���ص�VkVideoEncodeH265CapabilitiesKHR::maxBPictureL0ReferenceCount �Լ�VkVideoEncodeH265CapabilitiesKHR::maxL1ReferenceCount ��Ϊ0����h265L0PictureTypes �Լ�h265L1PictureTypes �е�ÿ��Ԫ��h265PictureType ����ΪSTD_VIDEO_H265_PICTURE_TYPE_B ��h265L0PictureTypes�Լ�h265L1PictureTypes��һ��������������飬��������p3547��
																													   ��17�����ͨ��vkGetPhysicalDeviceVideoCapabilitiesKHR����video session����ʱ��video profile���ص�VkVideoEncodeH265CapabilitiesKHR::flags ������VK_VIDEO_ENCODE_H265_CAPABILITY_B_FRAME_IN_L0_LIST_BIT_KHR�� ��h265L0PictureTypes ��ÿ��Ԫ�ز���Ϊ STD_VIDEO_H265_PICTURE_TYPE_B ��h265L0PictureTypes��һ��������������飬��������p3547��
																													   ��18�����ͨ��vkGetPhysicalDeviceVideoCapabilitiesKHR����video session����ʱ��video profile���ص�VkVideoEncodeH265CapabilitiesKHR::flags ������VK_VIDEO_ENCODE_H265_CAPABILITY_B_FRAME_IN_L1_LIST_BIT_KHR�� ��h265L1PictureTypes ��ÿ��Ԫ�ز���Ϊ STD_VIDEO_H265_PICTURE_TYPE_B ��h265L1PictureTypes��һ��������������飬��������p3547��

			*/

		}

	}

	//Video Encode Rate Control  �μ�p3559
	{}
	{
		/*
		video coding ʹ�� bitrate ������ÿ������video bitstream data�Ĵ�С����Ϊ encoded bitstream data ��С��ʹ�� frame rate�ĺ�����

		���ʿ����㷨������video encode operations ����������bitrate�Ĵ�С��

		*/


		// Rate Control Modes  �μ�p3560
		{
			/*
			��������video session�����޷��������ʵģ�ֻ���ڸı���video session���������ú�ſ��ԡ�

			���ʿ��������ࣺ
				> Per-operation rate control  - ���ÿ��video encode operation ,���ʼ���ܴ�С��������������encoding��������
				> Stream-level rate control  -  �ڶ��video encode operations ��ֱ��ָ�����ʣ�������encoding�����Ŀ���
			*/

			//VkVideoEncodeRateControlModeFlagBitsKHR ���ʿ���ģʽ
			VkVideoEncodeRateControlModeFlagBitsKHR rateControlMode = VK_VIDEO_ENCODE_RATE_CONTROL_MODE_CBR_BIT_KHR;
			/*
			VkVideoEncodeRateControlModeFlagBitsKHR:
			VK_VIDEO_ENCODE_RATE_CONTROL_MODE_DEFAULT_KHR : ָ��ʹ��implementation-specific ���ʿ���
			VK_VIDEO_ENCODE_RATE_CONTROL_MODE_DISABLED_BIT_KHR : ���ʿ��Ʊ����ã�Ӧ�ý�ָ��ÿ�����������ʿ��Ʋ��������Ʊ���������������ģʽ�£�����pictures��ʹ�õ����ʺ�֮ǰ�ı�����������ʶ��������ݾ������ͽ��ֱ�ʹ��VkVideoEncodeH264NaluSliceInfoKHR::constantQp ����VkVideoEncodeH265NaluSliceSegmentInfoKHR::constantQp �����Ʊ�������
			VK_VIDEO_ENCODE_RATE_CONTROL_MODE_CBR_BIT_KHR : ָ��ʹ��constant bitrate (CBR) ���ʿ��ƣ�������ģʽ��ʵ�ֽ��ڷ����������ʲ������Ƶ�����³���ʹ�ù̶����������������������bitstream
			VK_VIDEO_ENCODE_RATE_CONTROL_MODE_VBR_BIT_KHR : ָ��ʹ��variable bitrate (VBR) ���ʿ��ƣ�������ģʽ��ʵ�ֽ��ڷ����������ʲ������Ƶ�����³���ʹ�ÿɱ�����������������bitstream��

			*/
		}


		//Leaky Bucket Model   leaky bucket model ���� stream-level rate control���򵥽������൱����video encoder �Լ�decoder ֮�������һ���ӿڣ���������ݻ᲻��ͨ������ӿ���decoder��ȡȻ�����������Ч�������ߴ������ʲ�ƥ��ʱ������ underflow �Լ�overflow��������ϸ������p3561��


		//Rate Control Layers  �μ�p3562   �򵥽�����һЩ��׼����encoded pictures������ָ����video coding layers������stream-level rate control�Ϳ���ʹ��һ�����߶�� rate control layers ����������

		//Rate Control State  �μ�p3562
		{
			/*
			rate control state ��video session��ά���������ͨ��VkVideoEncodeRateControlInfoKHR ��ָ������Ҫָ��rate control state �Լ� rate control layers�� �������ָ����p3562
			*/


			//��VkVideoBeginCodingInfoKHR.pNext�л���  VkVideoCodingControlInfoKHR.pNext�а���VkVideoEncodeRateControlInfoKHR �����û��߸��±������ʿ�������
			VkVideoEncodeRateControlInfoKHR videoEncodeRateControlInfoKHR{};
			videoEncodeRateControlInfoKHR.sType = VK_STRUCTURE_TYPE_MAX_ENUM;//û��ָ����������Ϊ�Ƿ�ֵ
			videoEncodeRateControlInfoKHR.pNext = nullptr;
			videoEncodeRateControlInfoKHR.flags = 0;//����δ��ʹ��
			videoEncodeRateControlInfoKHR.rateControlMode = VK_VIDEO_ENCODE_RATE_CONTROL_MODE_CBR_BIT_KHR;//һ�� VkVideoEncodeRateControlModeFlagBitsKHR ֵָ�� rate control mode
			videoEncodeRateControlInfoKHR.layerCount = 1;//pLayers ��Ԫ�ظ���
			VkVideoEncodeRateControlLayerInfoKHR videoEncodeRateControlLayerInfoKHR{};//ָ��ÿ��������rate control layer������
			{
				videoEncodeRateControlLayerInfoKHR.sType = VK_STRUCTURE_TYPE_MAX_ENUM;//û�ж������ﶨ��Ϊ�Ƿ�ֵ
				videoEncodeRateControlLayerInfoKHR.pNext = nullptr;//���԰��� VkVideoEncodeH264RateControlLayerInfoKHR ����VkVideoEncodeH265RateControlLayerInfoKHR
				videoEncodeRateControlLayerInfoKHR.averageBitrate = 256;//Ϊʵ�ֵ����ʿ����㷨ָ����ƽ��bitrate
				videoEncodeRateControlLayerInfoKHR.maxBitrate = 256;//Ϊʵ�ֵ����ʿ����㷨ָ���ķ�ֵbitrate
				videoEncodeRateControlLayerInfoKHR.frameRateNumerator = 1;//Ϊʵ�ֵ����ʿ����㷨������frame rate�ķ��ӣ��������0
				videoEncodeRateControlLayerInfoKHR.frameRateDenominator = 1;///Ϊʵ�ֵ����ʿ����㷨������frame rate�ķ�ĸ���������0
				videoEncodeRateControlLayerInfoKHR.virtualBufferSizeInMs = 256;//Ϊ�����ڶ� leaky bucket model�����ʿ����㷨ʹ�õ�virtual buffer�Ĵ�С
				videoEncodeRateControlLayerInfoKHR.initialVirtualBufferSizeInMs = 256;//Ϊ�����ڶ� leaky bucket model�����ʿ����㷨ʹ�õ�virtual buffer�ĳ�ʼ����
			}
			videoEncodeRateControlInfoKHR.pLayers = &videoEncodeRateControlLayerInfoKHR;//һ��VkVideoEncodeRateControlLayerInfoKHR ����ָ�룬ָ������rate control layer�����ʿ�������
			/*
			VkVideoEncodeRateControlInfoKHR��Ч�÷�:
			1.���rateControlMode ΪVK_VIDEO_ENCODE_RATE_CONTROL_MODE_DEFAULT_KHR ����VK_VIDEO_ENCODE_RATE_CONTROL_MODE_DISABLED_BIT_KHR����layerCount ����Ϊ0
			2.���rateControlMode ΪVK_VIDEO_ENCODE_RATE_CONTROL_MODE_CBR_BIT_KHR ����VK_VIDEO_ENCODE_RATE_CONTROL_MODE_VBR_BIT_KHR����layerCount �������0
			3.���rateControlMode ��ΪVK_VIDEO_ENCODE_RATE_CONTROL_MODE_DEFAULT_KHR���������ָ��һ�������ڵ���vkGetPhysicalDeviceVideoCapabilitiesKHR����ʹ�õ�video profile ���ص�VkVideoEncodeCapabilitiesKHR::rateControlModes�е�һ����������
			4.layerCount ����С�ڵ��ڵ���vkGetPhysicalDeviceVideoCapabilitiesKHR����ʹ�õ�video profile ���ص�VkVideoEncodeCapabilitiesKHR::maxRateControlLayers
			5.��pLayers �е�ÿ��Ԫ�أ���averageBitrate ��Ա������1������vkGetPhysicalDeviceVideoCapabilitiesKHR����ʹ�õ�video profile ���ص�VkVideoEncodeCapabilitiesKHR::maxBitrate ����
			6.��pLayers �е�ÿ��Ԫ�أ���maxBitrate ��Ա������1������vkGetPhysicalDeviceVideoCapabilitiesKHR����ʹ�õ�video profile ���ص�VkVideoEncodeCapabilitiesKHR::maxBitrate ����
			7.���rateControlMode ΪVK_VIDEO_ENCODE_RATE_CONTROL_MODE_CBR_BIT_KHR�����pLayers �е�ÿ��Ԫ�أ���averageBitrate ��Ա��������� maxBitrate ��Ա
			8.���rateControlMode ΪVK_VIDEO_ENCODE_RATE_CONTROL_MODE_VBR_BIT_KHR�����pLayers �е�ÿ��Ԫ�أ���averageBitrate ��Ա����С�ڻ������ maxBitrate ��Ա
			9.���layerCount ��Ϊ0����virtualBufferSizeInMs �������0
			10.���layerCount ��Ϊ0����initialVirtualBufferSizeInMs ����С�� virtualBufferSizeInMs
			11.���ʹ�õ�video profile��videoCodecOperation ΪVK_VIDEO_CODEC_OPERATION_ENCODE_H264_BIT_KHR����pNext����һ��VkVideoEncodeH264RateControlInfoKHR�ṹ�壬��layerCount ����1 ����layerCount�������VkVideoEncodeH264RateControlInfoKHR::temporalLayerCount
			12.���ʹ�õ�video profile��videoCodecOperation ΪVK_VIDEO_CODEC_OPERATION_ENCODE_H265_BIT_KHR����pNext����һ��VkVideoEncodeH265RateControlInfoKHR�ṹ�壬��layerCount ����1 ����layerCount�������VkVideoEncodeH265RateControlInfoKHR::subLayerCount
			*/


		}

	}


	// H.264 Encode Operations  �μ�p3568
	{
		/*
		video encode operations ʹ��һ�� H.264 encode profile ��������ITU-T H.264 Specification ������video stream���б���
		
		�����д����һЩ���ݽṹ���Ӧ��ITU-T H.264 Specification �еĶ�Ӧ����:
			 StdVideoH264SequenceParameterSet ->  H.264 sequence parameter set
			 StdVideoH264PictureParameterSet  ->   H.264 picture parameter set
			 StdVideoEncodeH264PictureInfo   ->    H.264 picture information
			 StdVideoEncodeH264SliceHeader  ->   H.264 slice header parameters 
			 StdVideoEncodeH264ReferenceInfo ->   H.264 reference information
		*/


		//H.264 Encode Parameter Overrides  �μ�p3568
		{
			/*
			ʵ�ֿ��ܸ�д���²���:
				> StdVideoH264SequenceParameterSet
				> StdVideoH264PictureParameterSet
				> StdVideoEncodeH264PictureInfo
				> StdVideoEncodeH264SliceHeader
				> StdVideoEncodeH264ReferenceInfo
			�����ܸ�д:
                > StdVideoEncodeH264PictureInfo::primary_pic_type
                > StdVideoEncodeH264SliceHeader::slice_type

			���ʵ�ָ�д����Щ�����������ͨ��vkGetEncodedVideoSessionParametersKHR ��ȷ���Ƿ�д�ˡ�
			*/
		}


		//H.264 Encode Bitstream Data Access  ��Ҫ����video bitstream buffer�д洢�����ݸ�ʽ��  ������ϸ��Ϣ�μ�p3569 ***

		//H.264 Encode Picture Data Access  ��Ҫ������η���video picture resource�е�image ���ݣ� ������ϸ��Ϣ�μ�p3569  ***


		// H.264 Frame, Picture, and Slice   ��Ҫ����H.264 pictures�ڱ�������б�����Ϊslices��ÿ��slice����ʹ�ò�ͬ�����ͽ��б��룬��������Щslice�ؽ���constructed picturesҲ�в�ͬ�����ͣ�      ����μ�p3570  
		

		// H.264 Encode Profile �μ�p3571
		{
			/*
			video profile ֧��H.264 video encode operations ��Ҫ��VkVideoProfileInfoKHR::videoCodecOperation ����ΪVK_VIDEO_CODEC_OPERATION_ENCODE_H264_BIT_KHR ������ VkVideoProfileInfoKHR::pNext �����һ��VkVideoEncodeH264ProfileInfoKHR
			*/

			VkVideoEncodeH264ProfileInfoKHR videoEncodeH264ProfileInfoKHR{};
			videoEncodeH264ProfileInfoKHR.sType = VK_STRUCTURE_TYPE_MAX_ENUM;//û�ж�����������Ϊ�Ƿ�ֵ
			videoEncodeH264ProfileInfoKHR.pNext = nullptr;
			videoEncodeH264ProfileInfoKHR.stdProfileIdc = STD_VIDEO_H264_PROFILE_IDC_BASELINE;//һ��StdVideoH264ProfileIdc ֵ��ָ��H.264 codec profile IDC�������� ITU-T H.264 Specification�� A.2�ڣ�


		}


		//H.264 Encode Capabilities  �μ�p3571
		{
			/*
			������ vkGetPhysicalDeviceVideoCapabilitiesKHR ��ѯ H.264 encode profile����ʱ,��Ҫ��VkVideoCapabilitiesKHR::pNext �����һ��VkVideoEncodeH264CapabilitiesKHR������profile-specific ����

			*/

			VkVideoEncodeH264CapabilitiesKHR videoEncodeH264CapabilitiesKHR{};
			videoEncodeH264CapabilitiesKHR.sType = VK_STRUCTURE_TYPE_MAX_ENUM;//û�ж��壬���ﶨ��Ϊ�Ƿ�ֵ
			videoEncodeH264CapabilitiesKHR.pNext = nullptr;
			videoEncodeH264CapabilitiesKHR.flags = 0;/* VkVideoEncodeH264CapabilityFlagBitsKHR ���ֵλ���룬ָ��֧�ֵ�H.264 ��������	
			VkVideoEncodeH264CapabilityFlagBitsKHR:
			VK_VIDEO_ENCODE_H264_CAPABILITY_HRD_COMPLIANCE_BIT_KHR : ָ������κ�active SPS��StdVideoH264SpsVuiFlags��nal_hrd_parameters_present_flag ���� vcl_hrd_parameters_present_flag����Ϊ1�� ʵ���Ƿ��������HRD�����bitstreams
			VK_VIDEO_ENCODE_H264_CAPABILITY_PREDICTION_WEIGHT_TABLE_GENERATED_BIT_KHR  : ָ��������һ��P picture���� B picture ���������active SPS��StdVideoH264PpsFlags::weighted_pred_flag ����Ϊ1���� StdVideoH264PictureParameterSet::weighted_bipred_idc ����ΪSTD_VIDEO_H264_WEIGHTED_BIPRED_IDC_EXPLICIT����ʵ���ܹ��ڲ�����pred_weight_table��syntax��������ITU-T H.264 Specification��7.4.3.2 �ڣ�����Ӧ�ò���Ҫ��H.264 sliceheader parameters ���ṩһ��weight table
			VK_VIDEO_ENCODE_H264_CAPABILITY_ROW_UNALIGNED_SLICE_BIT_KHR : ָ��֧���ж��slices��frame��ÿ��slice������macroblock row�����κ�ƫ��ֵ��ʼ���߽����������֧��������sliceֻ����macroblock row�Ŀ�ʼ����ʼ���ڽ���������
			VK_VIDEO_ENCODE_H264_CAPABILITY_DIFFERENT_SLICE_TYPE_BIT_KHR : ָ�������slices��frame������ʱ��ʵ��������ݶ�����H.264 slice header parameters�е�StdVideoEncodeH264SliceHeader::slice_type������ÿһ��slice�������֧�֣���frame�е�����slice�����Զ�Ӧ��frame ��picture type��slice_type���б��롣 
			VK_VIDEO_ENCODE_H264_CAPABILITY_B_FRAME_IN_L0_LIST_BIT_KHR : ָ��֧��ʹ��һ��B frame ��Ϊһ��L0 ���ã���H.264 picture information �е�StdVideoEncodeH264ReferenceListsInfo::RefPicList0����ָ��
			VK_VIDEO_ENCODE_H264_CAPABILITY_B_FRAME_IN_L1_LIST_BIT_KHR : ָ��֧��ʹ��һ��B frame ��Ϊһ��L1 ���ã���H.264 picture information �е�StdVideoEncodeH264ReferenceListsInfo::RefPicList1����ָ��
			VK_VIDEO_ENCODE_H264_CAPABILITY_PER_PICTURE_TYPE_MIN_MAX_QP_BIT_KHR : ָ��֧����VkVideoEncodeH264QpKHR��ָ����ͬ��QPֵ
			VK_VIDEO_ENCODE_H264_CAPABILITY_PER_SLICE_CONSTANT_QP_BIT_KHR : ָ��֧��Ϊÿһ��sliceָ����ͬ��QPֵ
			VK_VIDEO_ENCODE_H264_CAPABILITY_GENERATE_PREFIX_NALU_BIT_KHR : ָ��֧��ͨ����VkVideoEncodeH264PictureInfoKHR::generatePrefixNalu ����Ϊ VK_TRUE������prefix NAL units���ɼ�H.264 Encode Bitstream Data Access p3569��
			
			*/
			videoEncodeH264CapabilitiesKHR.maxLevelIdc = STD_VIDEO_H264_LEVEL_IDC_1_0;//һ��StdVideoH264LevelIdc ֵ��ָ����profile֧�ֵ�����H.264 level������ֵ��ʽΪSTD_VIDEO_H264_LEVEL_IDC_<major>_<minor> ָ��H.264 level�� <major>.<minor> �μ� ITU-T H.264 Specification��A.3�½�
			videoEncodeH264CapabilitiesKHR.maxSliceCount = 1;//ָ����һ��picture�Ŀɱ����slices������������ò����ɱ�����codec-specific����Ӱ��
			videoEncodeH264CapabilitiesKHR.maxPPictureL0ReferenceCount = 1;//ʵ��֧�ֵ�P pictures�������б�L0��reference pictures����������������ò��������ԣ���Ϊ���ܻᱻʵ�ָ�дL0�б�
			videoEncodeH264CapabilitiesKHR.maxBPictureL0ReferenceCount = 1;//ʵ��֧�ֵ�B pictures�������б�L0��reference pictures����������������ò��������ԣ���Ϊ���ܻᱻʵ�ָ�дL0�б�
			videoEncodeH264CapabilitiesKHR.maxL1ReferenceCount = 1;//ʵ��֧�ֵ�B pictures�����֧�֣��������б�L1��reference pictures����������������ò��������ԣ���Ϊ���ܻᱻʵ�ָ�дL1�б�
			videoEncodeH264CapabilitiesKHR.maxTemporalLayerCount = 1;//Ϊʵ��֧�ֵ�H.264 temporal layers���������
			videoEncodeH264CapabilitiesKHR.expectDyadicTemporalLayerPattern = 1;//ָ����������temporal layersʱ�� rate control algorithms ����ʹ��һ�� dyadic temporal layer pattern
			videoEncodeH264CapabilitiesKHR.minQp = 1;//ָ��֧�ֵ���СQP ֵ
			videoEncodeH264CapabilitiesKHR.maxQp = 1;//ָ��֧�ֵ����QP ֵ
			videoEncodeH264CapabilitiesKHR.prefersGopRemainingFrames = VK_TRUE;//ָ������ʼһ�� video coding scopeʱ��rate control algorithmƫ��Ӧ��ָ���ڵ�ǰpictures����ʣ��ĸ������͵�frame������
			videoEncodeH264CapabilitiesKHR.requiresGopRemainingFrames = VK_TRUE;//ָ������ʼһ�� video coding scopeʱ��rate control algorithm��ҪӦ��ָ���ڵ�ǰpictures����ʣ��ĸ������͵�frame������
			videoEncodeH264CapabilitiesKHR.stdSyntaxFlags = 0;/*VkVideoEncodeH264StdFlagBitsKHR ���ֵλ���룬ָ�� H.264 syntax Ԫ�ص�����
			VkVideoEncodeH264StdFlagBitsKHR:
			VK_VIDEO_ENCODE_H264_STD_SEPARATE_COLOR_PLANE_FLAG_SET_BIT_KHR : ָ���Ƿ�ʵ��֧��ʹ��һ��Ӧ���ṩ��ֵ��SPS�е�StdVideoH264SpsFlags::separate_colour_plane_flag����ֵΪ1ʱ����ֵ
			VK_VIDEO_ENCODE_H264_STD_QPPRIME_Y_ZERO_TRANSFORM_BYPASS_FLAG_SET_BIT_KHR : ָ���Ƿ�ʵ��֧��ʹ��һ��Ӧ���ṩ��ֵ��SPS�е�StdVideoH264SpsFlags::qpprime_y_zero_transform_bypass_flag����ֵΪ1ʱ����ֵ
			VK_VIDEO_ENCODE_H264_STD_SCALING_MATRIX_PRESENT_FLAG_SET_BIT_KHR :ָ���Ƿ�ʵ��֧��ʹ��һ��Ӧ���ṩ��ֵ��SPS�е�StdVideoH264SpsFlags::seq_scaling_matrix_present_flag����ֵΪ1ʱ������StdVideoH264PpsFlags::pic_scaling_matrix_present_flag������ֵΪ1ʱ����ֵ
			VK_VIDEO_ENCODE_H264_STD_CHROMA_QP_INDEX_OFFSET_BIT_KHR : ָ���Ƿ�ʵ��֧��ʹ��һ��Ӧ���ṩ��ֵ��PPS�е�StdVideoH264PictureParameterSet::chroma_qp_index_offset����ֵ��Ϊ0ʱ����ֵ
			VK_VIDEO_ENCODE_H264_STD_SECOND_CHROMA_QP_INDEX_OFFSET_BIT_KHR : ָ���Ƿ�ʵ��֧��ʹ��һ��Ӧ���ṩ��ֵ��PPS�е�StdVideoH264PictureParameterSet::second_chroma_qp_index_offset����ֵ��Ϊ0ʱ����ֵ
			VK_VIDEO_ENCODE_H264_STD_PIC_INIT_QP_MINUS26_BIT_KHR : ָ���Ƿ�ʵ��֧��ʹ��һ��Ӧ���ṩ��ֵ��PPS�е�StdVideoH264PictureParameterSet::pic_init_qp_minus26����ֵ��Ϊ0ʱ����ֵ
			VK_VIDEO_ENCODE_H264_STD_WEIGHTED_PRED_FLAG_SET_BIT_KHR : ָ���Ƿ�ʵ��֧��ʹ��һ��Ӧ���ṩ��ֵ��PPS�е�StdVideoH264PpsFlags::weighted_pred_flag����ֵΪ1ʱ����ֵ
			VK_VIDEO_ENCODE_H264_STD_WEIGHTED_BIPRED_IDC_EXPLICIT_BIT_KHR : ָ���Ƿ�ʵ��֧��ʹ��һ��Ӧ���ṩ��ֵ��PPS�е�StdVideoH264PictureParameterSet::weighted_bipred_idc����ֵΪSTD_VIDEO_H264_WEIGHTED_BIPRED_IDC_EXPLICIT ʱ����ֵ
			VK_VIDEO_ENCODE_H264_STD_WEIGHTED_BIPRED_IDC_IMPLICIT_BIT_KHR : ָ���Ƿ�ʵ��֧��ʹ��һ��Ӧ���ṩ��ֵ��PPS�е�StdVideoH264PictureParameterSet::weighted_bipred_idc����ֵΪSTD_VIDEO_H264_WEIGHTED_BIPRED_IDC_IMPLICIT ʱ����ֵ
			VK_VIDEO_ENCODE_H264_STD_TRANSFORM_8X8_MODE_FLAG_SET_BIT_KHR : ָ���Ƿ�ʵ��֧��ʹ��һ��Ӧ���ṩ��ֵ��PPS�е�StdVideoH264PpsFlags::transform_8x8_mode_flag����ֵΪ1ʱ����ֵ
			VK_VIDEO_ENCODE_H264_STD_DIRECT_SPATIAL_MV_PRED_FLAG_UNSET_BIT_KHR : ָ���Ƿ�ʵ��֧��ʹ��һ��Ӧ���ṩ��ֵ��H.264 slice header parameters�е�StdVideoEncodeH264SliceHeaderFlags::direct_spatial_mv_pred_flag����ֵΪ0ʱ����ֵ
			VK_VIDEO_ENCODE_H264_STD_ENTROPY_CODING_MODE_FLAG_UNSET_BIT_KHR : ָ���Ƿ�ʵ��֧��CAVLC entropy coding��������ITU-T H.264 Specification��9.2�ڣ�����֧��ʹ��һ��Ӧ���ṩ��ֵ��PPS�е�StdVideoH264PpsFlags::entropy_coding_mode_flag����ֵΪ0ʱ����ֵ
			VK_VIDEO_ENCODE_H264_STD_ENTROPY_CODING_MODE_FLAG_SET_BIT_KHR : ָ���Ƿ�ʵ��֧��CABAC entropy coding��������ITU-T H.264 Specification��9.3�ڣ�����֧��ʹ��һ��Ӧ���ṩ��ֵ��PPS�е�StdVideoH264PpsFlags::entropy_coding_mode_flag����ֵΪ1ʱ����ֵ
			VK_VIDEO_ENCODE_H264_STD_DIRECT_8X8_INFERENCE_FLAG_UNSET_BIT_KHR : ָ���Ƿ�ʵ��֧��ʹ��һ��Ӧ���ṩ��ֵ��SPS�е�StdVideoH264SpsFlags::direct_8x8_inference_flag����ֵΪ0ʱ����ֵ
			VK_VIDEO_ENCODE_H264_STD_CONSTRAINED_INTRA_PRED_FLAG_SET_BIT_KHR : ָ���Ƿ�ʵ��֧��ʹ��һ��Ӧ���ṩ��ֵ��PPS�е�StdVideoH264PpsFlags::constrained_intra_pred_flag����ֵΪ1ʱ����ֵ
			VK_VIDEO_ENCODE_H264_STD_DEBLOCKING_FILTER_DISABLED_BIT_KHR : ָ���Ƿ�ʵ��֧��ʹ��һ��Ӧ���ṩ��ֵ��H.264 slice header parameters�е�StdVideoEncodeH264SliceHeader::disable_deblocking_filter_idc����ֵΪSTD_VIDEO_H264_DISABLE_DEBLOCKING_FILTER_IDC_DISABLED ʱ����ֵ
			VK_VIDEO_ENCODE_H264_STD_DEBLOCKING_FILTER_ENABLED_BIT_KHR : ָ���Ƿ�ʵ��֧��ʹ��һ��Ӧ���ṩ��ֵ��H.264 slice header parameters�е�StdVideoEncodeH264SliceHeader::disable_deblocking_filter_idc����ֵΪSTD_VIDEO_H264_DISABLE_DEBLOCKING_FILTER_IDC_ENABLED ʱ����ֵ
			VK_VIDEO_ENCODE_H264_STD_DEBLOCKING_FILTER_PARTIAL_BIT_KHR : ָ���Ƿ�ʵ��֧��ʹ��һ��Ӧ���ṩ��ֵ��H.264 slice header parameters�е�StdVideoEncodeH264SliceHeader::disable_deblocking_filter_idc����ֵΪSTD_VIDEO_H264_DISABLE_DEBLOCKING_FILTER_IDC_PARTIAL ʱ����ֵ
			VK_VIDEO_ENCODE_H264_STD_SLICE_QP_DELTA_BIT_KHR : ָ���Ƿ�ʵ��֧��ʹ��һ��Ӧ���ṩ��ֵ��H.264 slice header parameters�е�StdVideoEncodeH264SliceHeader::slice_qp_delta����ֵ�ڱ����frame�еĸ���slices�����ʱ����ֵ
			VK_VIDEO_ENCODE_H264_STD_DIFFERENT_SLICE_QP_DELTA_BIT_KHR : ָ���Ƿ�ʵ��֧��ʹ��һ��Ӧ���ṩ��ֵ��H.264 slice header parameters�е�StdVideoEncodeH264SliceHeader::slice_qp_delta����ֵ�ڱ����frame�еĸ���slices�в���ʱ����ֵ
						
			*/


		}


		// H.264 Encode Quality Level Properties  �μ�p3577
		{
			/*
			������vkGetPhysicalDeviceVideoEncodeQualityLevelPropertiesKHR ���� pVideoProfile->videoCodecOperation specified Ϊ VK_VIDEO_CODEC_OPERATION_ENCODE_H264_BIT_KHR ʱ�������� VkVideoEncodeQualityLevelPropertiesKHR.pNext�а���һ��VkVideoEncodeH264QualityLevelPropertiesKHR �����ض����H.264 ����� video encode quality level����,
			*/

			VkVideoEncodeH264QualityLevelPropertiesKHR  videoEncodeH264QualityLevelPropertiesKHR{};
			videoEncodeH264QualityLevelPropertiesKHR.sType = VK_STRUCTURE_TYPE_MAX_ENUM;//û�ж�����������Ϊ�Ƿ�ֵ
			videoEncodeH264QualityLevelPropertiesKHR.pNext = nullptr;
			videoEncodeH264QualityLevelPropertiesKHR.preferredRateControlFlags = 0;//VkVideoEncodeH264RateControlFlagBitsKHR ���ֵλ���룬ָ�� VkVideoEncodeH264RateControlInfoKHR::flags ƫ��ʹ�õı�־
			videoEncodeH264QualityLevelPropertiesKHR.preferredGopFrameCount = 1;//ָ��VkVideoEncodeH264RateControlInfoKHR::gopFrameCount ƫ��ʹ�õ�ֵ
			videoEncodeH264QualityLevelPropertiesKHR.preferredIdrPeriod = 1;//ָ��VkVideoEncodeH264RateControlInfoKHR::idrPeriod ƫ��ʹ�õ�ֵ
			videoEncodeH264QualityLevelPropertiesKHR.preferredConsecutiveBFrameCount = 1;//ָ��VkVideoEncodeH264RateControlInfoKHR::consecutiveBFrameCount ƫ��ʹ�õ�ֵ
			videoEncodeH264QualityLevelPropertiesKHR.preferredTemporalLayerCount = 1;//ָ��VkVideoEncodeH264RateControlInfoKHR::temporalLayerCount ƫ��ʹ�õ�ֵ
			videoEncodeH264QualityLevelPropertiesKHR.preferredConstantQp = VkVideoEncodeH264QpKHR{ .qpI = 0,.qpP = 0,.qpB = 0};//ָ����ʹ��rate control mode VK_VIDEO_ENCODE_RATE_CONTROL_MODE_DISABLED_BIT_KHRʱ ÿ��picture��VkVideoEncodeH264NaluSliceInfoKHR::constantQp ƫ��ʹ�õ�ֵ
			videoEncodeH264QualityLevelPropertiesKHR.preferredMaxL0ReferenceCount = 0;//ָ�� reference list L0 ��ƫ��ʹ�õ�����picture ���������
			videoEncodeH264QualityLevelPropertiesKHR.preferredMaxL1ReferenceCount = 0;//ָ�� reference list L1 ��ƫ��ʹ�õ�����picture ���������
			videoEncodeH264QualityLevelPropertiesKHR.preferredStdEntropyCodingModeFlag = 0;//ָ�� StdVideoH264PpsFlags::entropy_coding_mode_flag ƫ��ʹ�õ�ֵ

		}


		//H.264 Encode Session  �μ�p3578
		{
			/*
			����һ��ʹ�� H.264 encode profile�� video sessionʱ������ VkVideoSessionCreateInfoKHR.pNext�а���һ��VkVideoEncodeH264SessionCreateInfoKHR ָ������Ĳ���
			*/

			VkVideoEncodeH264SessionCreateInfoKHR  videoEncodeH264SessionCreateInfoKHR{};
			videoEncodeH264SessionCreateInfoKHR.sType = VK_STRUCTURE_TYPE_MAX_ENUM;
			videoEncodeH264SessionCreateInfoKHR.pNext = nullptr;
			videoEncodeH264SessionCreateInfoKHR.maxLevelIdc = STD_VIDEO_H264_LEVEL_IDC_1_0;//һ��StdVideoH264LevelIdc ֵָ������video session������video bitstreams ʹ�õ� H.264 level���Ͻ죬��ʽΪSTD_VIDEO_H264_LEVEL_IDC_<major>_<minor>������ <major>.<minor> ������ ITU-T H.264 Specification ��A.3��
			videoEncodeH264SessionCreateInfoKHR.useMaxLevelIdc = VK_TRUE;//ָ��ʵ���Ƿ�ʹ��maxLevelIdc�����ΪVK_FALSE����maxLevelIdc ����Ȼ��ʹ��vkGetPhysicalDeviceVideoCapabilitiesKHR���ص�VkVideoEncodeH264CapabilitiesKHR::maxLevelIdc
		}


		//H.264 Encode Parameter Sets  �μ�p3579
		{

			/*
			��VK_VIDEO_CODEC_OPERATION_ENCODE_H264_BIT_KHR������ video session parameters ��������²�����:
				> H.264 Sequence Parameter Sets (SPS)�����飨�� ITU-T H.264 Specification��,��ӦStdVideoH264SequenceParameterSet ���������в����ľ������� ��p3496 *** ;
				> H.264 Picture Parameter Sets (PPS)�����飨�� ITU-T H.264 Specification��,��Ӧ StdVideoH264PictureParameterSet ���������в����ľ������� ��p3496 *** ;
			��Щ�������ܱ�ʵ�ָ�д��������Ҫ����vkGetEncodedVideoSessionParametersKHR ��ȷ��ʵ���Ƿ�д����Щ����
			*/
			
			
			//��һ��video session parameters ��VK_VIDEO_CODEC_OPERATION_ENCODE_H264_BIT_KHR ����ʱ��  VkVideoSessionParametersCreateInfoKHR::pNext �б������һ�� VkVideoEncodeH264SessionParametersCreateInfoKHR ָ���ö���ĳ�ʼ����
			VkVideoEncodeH264SessionParametersCreateInfoKHR videoEncodeH264SessionParametersCreateInfoKHR{};
			videoEncodeH264SessionParametersCreateInfoKHR.sType = VK_STRUCTURE_TYPE_MAX_ENUM;//û�ж����������ﶨ��Ϊ�Ƿ�ֵ
			videoEncodeH264SessionParametersCreateInfoKHR.pNext = nullptr;
			videoEncodeH264SessionParametersCreateInfoKHR.maxStdSPSCount = 1;//Ϊ������ VkVideoSessionParametersKHR �ܰ�����H.264 SPS ʵ����������
			videoEncodeH264SessionParametersCreateInfoKHR.maxStdPPSCount = 1;//Ϊ������ VkVideoSessionParametersKHR �ܰ�����H.264 PPS ʵ����������
			VkVideoEncodeH264SessionParametersAddInfoKHR videoEncodeH264SessionParametersAddInfoKHR{};//�ýṹ�������VkVideoEncodeH264SessionParametersCreateInfoKHR.pParametersAddInfo��ʹ��ָ������ʱ�Ĳ������� �� VkVideoSessionParametersUpdateInfoKHR.pNext�а���ָ�����µĲ���
			{
				videoEncodeH264SessionParametersAddInfoKHR.sType = VK_STRUCTURE_TYPE_MAX_ENUM;
				videoEncodeH264SessionParametersAddInfoKHR.pNext = nullptr;
				videoEncodeH264SessionParametersAddInfoKHR.stdSPSCount = 1;//ΪpStdSPSs �е�Ԫ�ظ���
				StdVideoH264SequenceParameterSet stdVideoH264SequenceParameterSet{/*��������һ����Ч��StdVideoH264SequenceParameterSet �ṹ��*/ };
				videoEncodeH264SessionParametersAddInfoKHR.pStdSPSs = &stdVideoH264SequenceParameterSet;//һ��StdVideoH264SequenceParameterSet ����ָ��ָ����ӵ�H.264 SPS ʵ��
				videoEncodeH264SessionParametersAddInfoKHR.stdPPSCount = 1;//ΪpStdPPSs �е�Ԫ�ظ���
				StdVideoH264PictureParameterSet stdVideoH264PictureParameterSet{/*��������һ����Ч��StdVideoH264PictureParameterSet �ṹ��*/ };
				videoEncodeH264SessionParametersAddInfoKHR.pStdPPSs = &stdVideoH264PictureParameterSet;//һ�� StdVideoH264PictureParameterSet ����ָ��ָ����ӵ�H.264 PPS ʵ��
				/*
				VkVideoEncodeH264SessionParametersAddInfoKHR��Ч�÷�:
				1.pStdSPSs��ÿ��StdVideoH264SequenceParameterSetԪ�ص� seq_parameter_set_id������Ψһ��
				2.pStdPPSs��ÿ��StdVideoH264PictureParameterSetԪ�ص� seq_parameter_set_id �Լ� pic_parameter_set_id �����Ա�����Ψһ��
				*/
			}
			videoEncodeH264SessionParametersCreateInfoKHR.pParametersAddInfo = &videoEncodeH264SessionParametersAddInfoKHR;//ΪNULL����һ�� VkVideoEncodeH264SessionParametersAddInfoKHR ָ��ָ������ʱ��ӵ�H.264 parameters


			//����vkGetEncodedVideoSessionParametersKHR ʱ����VkVideoEncodeSessionParametersGetInfoKHR.pNextVkVideoEncodeH264SessionParametersGetInfoKHR ��ָ��������Ĳ�������д���Ŀ�����Ϣ��������ý���д��SPS,��д��PPS��
			VkVideoEncodeH264SessionParametersGetInfoKHR videoEncodeH264SessionParametersGetInfoKHR{};
			videoEncodeH264SessionParametersGetInfoKHR.sType = VK_STRUCTURE_TYPE_MAX_ENUM;
			videoEncodeH264SessionParametersGetInfoKHR.pNext = nullptr;
			videoEncodeH264SessionParametersGetInfoKHR.stdPPSId = 0;//ָ������ָ��Ҫ��ȡ��H.264 picture parameter set(s)��H.264 picture parameter set ID���� writeStdPPS ����Ϊ VK_TRUE.��
			videoEncodeH264SessionParametersGetInfoKHR.stdSPSId = 0;//ָ������ָ��Ҫ��ȡ��H.264 sequence �Լ�/���� picture parameter set(s)��H.264 sequence parameter set ID
			videoEncodeH264SessionParametersGetInfoKHR.writeStdPPS = VK_TRUE;//ָ���Ƿ������ȡ stdPPSId ָ���ı���� H.264 picture parameter set
			videoEncodeH264SessionParametersGetInfoKHR.writeStdSPS = VK_TRUE;//ָ���Ƿ������ȡ stdSPSId �Լ� stdPPSId ָ���ı���� H.264 sequence parameter set�� �� writeStdPPS ������һ��ΪVK_TRUE


			VkVideoEncodeH264SessionParametersFeedbackInfoKHR videoEncodeH264SessionParametersFeedbackInfoKHR{};
			videoEncodeH264SessionParametersFeedbackInfoKHR.sType = VK_STRUCTURE_TYPE_MAX_ENUM;//û�ж�����������Ϊ�Ƿ�ֵ
			videoEncodeH264SessionParametersFeedbackInfoKHR.pNext = nullptr;
			videoEncodeH264SessionParametersFeedbackInfoKHR.hasStdPPSOverrides = VK_TRUE;//ָ���κ�����ͨ��VkVideoEncodeH264SessionParametersGetInfoKHR::writeStdPPS���󣩵� H.264 picture parameter set �Ƿ�ʵ�ָ�д
			videoEncodeH264SessionParametersFeedbackInfoKHR.hasStdSPSOverrides = VK_FALSE;//ָ���κ�����ͨ��VkVideoEncodeH264SessionParametersGetInfoKHR::writeStdSPS���󣩵� H.264 sequence parameter set �Ƿ�ʵ�ָ�д



		}


		//H.264 Encoding Parameters  �μ�p3584
		{
			//��vkCmdEncodeVideoKHR ��  VkVideoEncodeInfoKHR.pNext�а���VkVideoEncodeH264PictureInfoKHR ָ�� H.264 encode operation��codec-specific picture ��Ϣ����Щ��Ϣ��ν��Ͳμ� p3585 ***
			VkVideoEncodeH264PictureInfoKHR   videoEncodeH264PictureInfoKHR{};
			videoEncodeH264PictureInfoKHR.sType = VK_STRUCTURE_TYPE_MAX_ENUM;//û�ж�����������Ϊ�Ƿ�ֵ
			videoEncodeH264PictureInfoKHR.pNext = nullptr;
			videoEncodeH264PictureInfoKHR.naluSliceEntryCount = 1;//pNaluSliceEntries ��Ԫ�ظ���
			VkVideoEncodeH264NaluSliceInfoKHR videoEncodeH264NaluSliceInfoKHR{};
			{
				videoEncodeH264NaluSliceInfoKHR.sType = VK_STRUCTURE_TYPE_MAX_ENUM;//û�ж�����������Ϊ�Ƿ�ֵ
				videoEncodeH264NaluSliceInfoKHR.pNext = nullptr;
				videoEncodeH264NaluSliceInfoKHR.constantQp = 0;
				StdVideoEncodeH264SliceHeader stdVideoEncodeH264SliceHeader{/*��������һ����Ч��StdVideoEncodeH264SliceHeader*/};
				videoEncodeH264NaluSliceInfoKHR.pStdSliceHeader = &stdVideoEncodeH264SliceHeader;
			}
			videoEncodeH264PictureInfoKHR.pNaluSliceEntries = &videoEncodeH264NaluSliceInfoKHR;//VkVideoEncodeH264NaluSliceInfoKHR ����ָ�룬ָ��input picture��ÿ�������H.264 slices �Ĳ���
			StdVideoEncodeH264PictureInfo stdVideoEncodeH264PictureInfo{/*��������һ����Ч��StdVideoEncodeH264PictureInfo*/};
			videoEncodeH264PictureInfoKHR.pStdPictureInfo = &stdVideoEncodeH264PictureInfo;//һ��StdVideoEncodeH264PictureInfo ��ָ�룬ָ�� H.264 picture information
			videoEncodeH264PictureInfoKHR.generatePrefixNalu = VK_FALSE;//�����Ƿ��� slice NALUs������target bitstream֮ǰ���� prefix NALUs����ITU-T H.264 Specification ��7.3.2.12 �Լ� 7.4.2.12�ڵĶ��壩
			/*
			VkVideoEncodeH264PictureInfoKHR��Ч�÷�:

			
			
			
			*/

			//������ VkVideoDecodeInfoKHR::pSetupReferenceSlot->pNext �Լ�  VkVideoDecodeInfoKHR::pReferenceSlots->pNext �а���VkVideoDecodeH264DpbSlotInfoKHR  ��ָ��codec-specific reference picture information��������Ϣ��ν��ͼ�  p3501 ***
			VkVideoDecodeH264DpbSlotInfoKHR  videoDecodeH264DpbSlotInfoKHR{};
			videoDecodeH264DpbSlotInfoKHR.sType = VK_STRUCTURE_TYPE_VIDEO_DECODE_H264_DPB_SLOT_INFO_KHR;
			videoDecodeH264DpbSlotInfoKHR.pNext = nullptr;
			StdVideoDecodeH264ReferenceInfo stdVideoDecodeH264ReferenceInfo{/*��������һ����Ч��StdVideoDecodeH264ReferenceInfo �ṹ��*/ };
			videoDecodeH264DpbSlotInfoKHR.pStdReferenceInfo = &stdVideoDecodeH264ReferenceInfo;//һ��StdVideoDecodeH264ReferenceInfo ָ�룬ָ�� H.264 reference information

		}

	}

}



NS_TEST_END