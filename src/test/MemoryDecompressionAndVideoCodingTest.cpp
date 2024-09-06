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
			videoCapabilitiesKHR.pictureAccessGranularity = VkExtent2D{.width = 1,.height = 1};//��image��Ϊvideo picture resources����ʱ����С��������
			videoCapabilitiesKHR.minCodedExtent = VkExtent2D{ .width = 1,.height = 1 };//����֡��frame������Сwidth�Լ�height
			videoCapabilitiesKHR.maxCodedExtent = VkExtent2D{ .width = 1,.height = 1 };//����֡��frame�������width�Լ�height
			videoCapabilitiesKHR.maxDpbSlots = 2;//һ��video session��֧�ֵ�����DPB slots������
			videoCapabilitiesKHR.maxActiveReferencePictures = 2;//һ�� video coding ��������ʹ�õ�active reference pictures���������
			videoCapabilitiesKHR.stdHeaderVersion = VkExtensionProperties{.extensionName = "header",.specVersion = 1};// Ϊһ��VkExtensionProperties����¼��׼��Ƶͷ�����Լ�video profile֧�ֵİ汾
		
		}


		// Video Format Capabilities  �μ�p3419
		{
			//�о�ָ�� video profile֧�ֵ�output, input �Լ� DPB image ��formats �Ͷ�Ӧ������
			VkPhysicalDeviceVideoFormatInfoKHR physicalDeviceVideoFormatInfoKHR{};
			physicalDeviceVideoFormatInfoKHR.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VIDEO_FORMAT_INFO_KHR;
			physicalDeviceVideoFormatInfoKHR.pNext = nullptr;//���԰��� VkVideoProfileListInfoKHR
			physicalDeviceVideoFormatInfoKHR.imageUsage = VK_IMAGE_USAGE_VIDEO_DECODE_DPB_BIT_KHR;

			uint32_t videoFormatPropertyCount = 0;
			std::vector<VkVideoFormatPropertiesKHR> videoFormatPropertiesKHRs{};
			VkResult result/*���ؽ����Ϣ�������֧�� VkVideoProfileListInfoKHR::pProfiles�е��κ�һ���򷵻�֮ǰ�����Ĵ�����Ϣ�������֧��VkPhysicalDeviceVideoFormatInfoKHR::imageUsage�򷵻�VK_ERROR_IMAGE_USAGE_NOT_SUPPORTED_KHR*/ 
					= vkGetPhysicalDeviceVideoFormatPropertiesKHR(physicalDevice, &physicalDeviceVideoFormatInfoKHR, &videoFormatPropertyCount, nullptr);
			videoFormatPropertiesKHRs.resize(videoFormatPropertyCount);
			VkResult result/*���ؽ����Ϣ�������֧�� VkVideoProfileListInfoKHR::pProfiles�е��κ�һ���򷵻�֮ǰ�����Ĵ�����Ϣ�������֧��VkPhysicalDeviceVideoFormatInfoKHR::imageUsage�򷵻�VK_ERROR_IMAGE_USAGE_NOT_SUPPORTED_KHR*/
					= vkGetPhysicalDeviceVideoFormatPropertiesKHR(physicalDevice, &physicalDeviceVideoFormatInfoKHR, &videoFormatPropertyCount, videoFormatPropertiesKHRs.data());
		}
	}

}



NS_TEST_END