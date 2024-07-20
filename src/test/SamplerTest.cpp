#include "SamplerTest.h"
#include <vulkan/vulkan_android.h>
// Provided by VK_QCOM_image_processing2
typedef enum VkBlockMatchWindowCompareModeQCOM {
	VK_BLOCK_MATCH_WINDOW_COMPARE_MODE_MIN_QCOM = 0,
	VK_BLOCK_MATCH_WINDOW_COMPARE_MODE_MAX_QCOM = 1,
} VkBlockMatchWindowCompareModeQCOM;

// Provided by VK_QCOM_image_processing2
typedef struct VkSamplerBlockMatchWindowCreateInfoQCOM {
	VkStructureType                      sType;
	const void* pNext;
	VkExtent2D                           windowExtent;
	VkBlockMatchWindowCompareModeQCOM    windowCompareMode;
} VkSamplerBlockMatchWindowCreateInfoQCOM;



// Provided by VK_QCOM_filter_cubic_weights
typedef enum VkCubicFilterWeightsQCOM {
	VK_CUBIC_FILTER_WEIGHTS_CATMULL_ROM_QCOM = 0,
	VK_CUBIC_FILTER_WEIGHTS_ZERO_TANGENT_CARDINAL_QCOM = 1,
	VK_CUBIC_FILTER_WEIGHTS_B_SPLINE_QCOM = 2,
	VK_CUBIC_FILTER_WEIGHTS_MITCHELL_NETRAVALI_QCOM = 3,
} VkCubicFilterWeightsQCOM;


// Provided by VK_QCOM_filter_cubic_weights
typedef struct VkSamplerCubicWeightsCreateInfoQCOM {
	VkStructureType             sType;
	const void* pNext;
	VkCubicFilterWeightsQCOM    cubicWeights;
} VkSamplerCubicWeightsCreateInfoQCOM;


// Provided by VK_QNX_external_memory_screen_buffer
typedef struct VkExternalFormatQNX {
	VkStructureType    sType;
	void* pNext;
	uint64_t           externalFormat;
} VkExternalFormatQNX;

// Provided by VK_QCOM_ycbcr_degamma
typedef struct VkSamplerYcbcrConversionYcbcrDegammaCreateInfoQCOM {
	VkStructureType    sType;
	void* pNext;
	VkBool32           enableYDegamma;
	VkBool32           enableCbCrDegamma;
} VkSamplerYcbcrConversionYcbcrDegammaCreateInfoQCOM;


NS_TEST_BEGIN




SamplerTest::SamplerTest()
{
}

void SamplerTest::run()
{
}

SamplerTest::~SamplerTest()
{
}

struct SamplerCreateInfoEXT {
	VkOpaqueCaptureDescriptorDataCreateInfoEXT OpaqueCaptureDescriptorDataCreateInfoEXT{};
	VkSamplerBlockMatchWindowCreateInfoQCOM samplerBlockMatchWindowCreateInfoQCOM{};
	VkSamplerBorderColorComponentMappingCreateInfoEXT samplerBorderColorComponentMappingCreateInfoEXT{};
	VkSamplerCubicWeightsCreateInfoQCOM	samplerCubicWeightsCreateInfoQCOM{};
	VkSamplerCustomBorderColorCreateInfoEXT samplerCustomBorderColorCreateInfoEXT{};
	VkSamplerReductionModeCreateInfo samplerReductionModeCreateInfo{};
	VkSamplerYcbcrConversionInfo samplerYcbcrConversionInfo{};
	SamplerCreateInfoEXT() {
		Init();
	}
	void Init() {
		OpaqueCaptureDescriptorDataCreateInfoEXT.sType = VK_STRUCTURE_TYPE_OPAQUE_CAPTURE_DESCRIPTOR_DATA_CREATE_INFO_EXT;
		OpaqueCaptureDescriptorDataCreateInfoEXT.pNext = nullptr;
		samplerBlockMatchWindowCreateInfoQCOM.sType = VK_STRUCTURE_TYPE_MAX_ENUM;//��Ϊû�ж���������������Ϊ���ֵ
		samplerBlockMatchWindowCreateInfoQCOM.pNext = nullptr;
		samplerBorderColorComponentMappingCreateInfoEXT.sType = VK_STRUCTURE_TYPE_SAMPLER_BORDER_COLOR_COMPONENT_MAPPING_CREATE_INFO_EXT;
		samplerBorderColorComponentMappingCreateInfoEXT.pNext = nullptr;
		samplerCubicWeightsCreateInfoQCOM.sType = VK_STRUCTURE_TYPE_MAX_ENUM;//��Ϊû�ж���������������Ϊ���ֵ
		samplerCubicWeightsCreateInfoQCOM.pNext = nullptr;
		samplerCustomBorderColorCreateInfoEXT.sType = VK_STRUCTURE_TYPE_SAMPLER_CUSTOM_BORDER_COLOR_CREATE_INFO_EXT;
		samplerCustomBorderColorCreateInfoEXT.pNext = nullptr;
		samplerReductionModeCreateInfo.sType = VK_STRUCTURE_TYPE_SAMPLER_REDUCTION_MODE_CREATE_INFO;
		samplerReductionModeCreateInfo.pNext = nullptr;
		samplerYcbcrConversionInfo.sType = VK_STRUCTURE_TYPE_SAMPLER_YCBCR_CONVERSION_INFO;
		samplerYcbcrConversionInfo.pNext = nullptr;


	}



};




void SamplerTest::SamplerCreateTest()
{
	//VkSampler ˵����image sampler��״̬��������shaders �н��ж�image �ڴ�ķ����Լ�Ӧ���˲��Լ������任����
	VkSampler sampler{};

	VkSamplerCreateInfo samplerCreateInfo{};
	samplerCreateInfo.sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO;
		SamplerCreateInfoEXT samplerCreateInfoEXT{};
	samplerCreateInfo.pNext = &samplerCreateInfoEXT.OpaqueCaptureDescriptorDataCreateInfoEXT;
	samplerCreateInfo.flags = VK_SAMPLER_CREATE_SUBSAMPLED_BIT_EXT;/* �� VkSamplerCreateFlagBits ���ֵ��λ���룬ָ��sampler�Ķ�������
	VkSamplerCreateFlagBits:
	VK_SAMPLER_CREATE_SUBSAMPLED_BIT_EXT:  ָ��sampler����һ������ʱflags����VK_IMAGE_CREATE_SUBSAMPLED_BIT_EXT ��image�ж�ȡ����
	VK_SAMPLER_CREATE_SUBSAMPLED_COARSE_RECONSTRUCTION_BIT_EXT:  ָ�����ؽ�һ��subsampled image�ķ��ʵ������ȫ��color ֵʱ�����ù���ֵ�ķ�ʽ
	VK_SAMPLER_CREATE_NON_SEAMLESS_CUBE_MAP_BIT_EXT:  ָ�����ᴦ��cube map�ı�Ե����
	VK_SAMPLER_CREATE_IMAGE_PROCESSING_BIT_QCOM:  ָ��sampler����ʹ��OpImageWeightedSampleQCOM, OpImageBoxFilterQCOM, OpImageBlockMatchGatherSSDQCOM, OpImageBlockMatchGatherSADQCOM, OpImageBlockMatchWindowSSDQCOM,
																OpImageBlockMatchWindowSADQCOM, OpImageBlockMatchSSDQCOM, ���� OpImageBlockMatchSADQCOM�� image�ж�ȡ����
	

	VK_SAMPLER_CREATE_DESCRIPTOR_BUFFER_CAPTURE_REPLAY_BIT_EXT:  ָ��sampler������capturing �� replaying ���� descriptor��(e.g. ���� trace capture �� replay),�ɴ�VkOpaqueCaptureDescriptorDataCreateInfoEXT �в鿴������Ϣ

	*/
	samplerCreateInfo.addressModeU = VK_SAMPLER_ADDRESS_MODE_REPEAT;//��һ�� VkSamplerAddressModeֵ��ָ���˵���U������в���ʱ����[0,1]��Χʱʹ�õ�Ѱַģʽ
	/*
	VkSamplerAddressMode:
	VK_SAMPLER_ADDRESS_MODE_REPEAT:  ָ��ʹ��repeat wrap mode
	VK_SAMPLER_ADDRESS_MODE_MIRRORED_REPEAT:  ָ��ʹ�� mirrored repeat wrap mode 
	VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE:  ָ��ʹ�� clamp to edge wrap mode 
	VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_BORDER:  ָ��ʹ��clamp to border wrap mode
	VK_SAMPLER_ADDRESS_MODE_MIRROR_CLAMP_TO_EDGE:  ָ��ʹ�� mirror clamp to edge wrap��ֻ��samplerMirrorClampToEdge ��������VK_KHR_sampler_mirror_clamp_to_edg ��չ�����˲���Ч

	wrap mode����� Wrapping Operation p1510

	*/
	samplerCreateInfo.addressModeV = VK_SAMPLER_ADDRESS_MODE_REPEAT;//��һ�� VkSamplerAddressModeֵ��ָ���˵���V������в���ʱ����[0,1]��Χʱʹ�õ�Ѱַģʽ
	samplerCreateInfo.addressModeW = VK_SAMPLER_ADDRESS_MODE_REPEAT;//��һ�� VkSamplerAddressModeֵ��ָ���˵���W������в���ʱ����[0,1]��Χʱʹ�õ�Ѱַģʽ
	samplerCreateInfo.borderColor = VkBorderColor::VK_BORDER_COLOR_FLOAT_OPAQUE_BLACK;/*��һ�� VkBorderColorֵ��ָ����ʹ�õ�Ԥ�ȶ������ɫ�����Ա߽紦�����ؽ��в���ʱʹ��
	VkBorderColor:
	VK_BORDER_COLOR_FLOAT_TRANSPARENT_BLACK: ָ��Ϊһ�������ʽ��͸���ĺ�ɫ
	VK_BORDER_COLOR_INT_TRANSPARENT_BLACK:  ָ��Ϊһ�����θ�ʽ��͸���ĺ�ɫ
	VK_BORDER_COLOR_FLOAT_OPAQUE_BLACK:  ָ��Ϊһ�������ʽ�Ĳ�͸���ĺ�ɫ
	VK_BORDER_COLOR_INT_OPAQUE_BLACK:  ָ��Ϊһ�����θ�ʽ�Ĳ�͸���ĺ�ɫ
	VK_BORDER_COLOR_FLOAT_OPAQUE_WHITE:  ָ��Ϊһ�������ʽ�Ĳ�͸���İ�ɫ
	VK_BORDER_COLOR_INT_OPAQUE_WHITE:  ָ��Ϊһ�����θ�ʽ�Ĳ�͸���İ�ɫ
	VK_BORDER_COLOR_FLOAT_CUSTOM_EXT:  ָ��ΪVkSamplerCreateInfo::pNext�е�VkSamplerCustomBorderColorCreateInfoEXT �ĸ������͵���ɫֵ��Ϊ����ɫ
	VK_BORDER_COLOR_INT_CUSTOM_EXT:  ָ��ΪVkSamplerCreateInfo::pNext�е�VkSamplerCustomBorderColorCreateInfoEXT ���������͵���ɫֵ��Ϊ����ɫ


	�����  Texel Replacement p1486
	
	*/
	samplerCreateInfo.anisotropyEnable = VK_FALSE;//�����Ƿ��� anisotropic filtering ���μ� Texel Anisotropic Filtering p1515
	samplerCreateInfo.maxAnisotropy = 1;//��shaderȡclamp��anisotropy ֵ��ֻ�е�anisotropyEnable ΪVK_TRUE����Ч��
	samplerCreateInfo.compareEnable = VK_FALSE;//�����Ƿ����ڲ��Ҳ���ʱ��һ�����õ�ֵreference���бȽϲ������μ� Comparison p1505
	samplerCreateInfo.compareOp = VK_COMPARE_OP_LESS;/*��һ�� VkCompareOpֵ��ָ������filterǰ��ȡ����ʱ���бȽϲ���ʱʹ�õıȽϲ������� Depth Compare Operation p1488,�Ƚϲ��������رȽϵĽ��true����false
	VkCompareOp:
	VK_COMPARE_OP_NEVER: ָ���ȽϽ����ԶΪfalse.
	VK_COMPARE_OP_LESS: ָ��һ���Ƚϲ��� reference < test. 
	VK_COMPARE_OP_EQUAL: ָ��һ���Ƚϲ��� reference = test. 
	VK_COMPARE_OP_LESS_OR_EQUAL: ָ��һ���Ƚϲ��� reference �� test. 
	VK_COMPARE_OP_GREATER: ָ��һ���Ƚϲ��� reference > test. 
	VK_COMPARE_OP_NOT_EQUAL: ָ��һ���Ƚϲ��� reference �� test.
	VK_COMPARE_OP_GREATER_OR_EQUAL : ָ��һ���Ƚϲ��� reference �� test. 
	VK_COMPARE_OP_ALWAYS: ָ���ȽϽ����ԶΪtrue.
	
	*/
	
	samplerCreateInfo.magFilter = VK_FILTER_LINEAR;//��һ��VkFilterֵ��ָ��ҪӦ���ڲ��Ҳ�����magnification filter
	/*
	VkFilter:
	VK_FILTER_NEAREST:  ָ�� nearest filtering.
	VK_FILTER_LINEAR:  ָ��  linear filtering.
	VK_FILTER_CUBIC_EXT:  ָ��  cubic filtering.
	
	filterϸ�ڼ�  Texel Filtering. p1511
	*/
	samplerCreateInfo.minFilter = VK_FILTER_LINEAR;// ��һ��VkFilterֵ����ָ��ҪӦ���ڲ��Ҳ�����minification filter
	samplerCreateInfo.minLod = 0;//�������Ƽ����LODֵ����Сֵ���μ�p1505 LOD Operation
	samplerCreateInfo.maxLod = 1;//�������Ƽ����LODֵ�����ֵ���μ�p1505 LOD Operation,��������Ϊ VK_LOD_CLAMP_NONEָ��������LOD���ֵ����
	samplerCreateInfo.mipLodBias = 0;//һ����ӵ�mipmap LOD�������Լ�SPIV-V������image�����������ṩ��mipmap��ƫ�������μ�p1505  LOD Operation
	samplerCreateInfo.mipmapMode = VK_SAMPLER_MIPMAP_MODE_LINEAR;/*��һ�� VkSamplerMipmapModeֵָ��ҪӦ���ڲ��Ҳ�����mipmap filter
	VkSamplerMipmapMode:
	VK_SAMPLER_MIPMAP_MODE_NEAREST:  ָ�� nearest filtering.
	VK_SAMPLER_MIPMAP_MODE_LINEAR:  ָ�� linear filtering.
	
	filterϸ�ڼ�  Texel Filtering. p1511
	*/
	samplerCreateInfo.unnormalizedCoordinates = VK_FALSE;//�����Ƿ�ʹ�÷Ǳ�׼�����׼��������������Ѱַͼ�������������ΪVK_TRUEʱ�����ڲ����ı���ͼ������ķ�Χ���㵽ͼ���ÿ��ά�ȵĴ�С��������ΪVK_FALSEʱ��ͼ������ÿ��ά�ȵķ�ΧΪ0��1��
	/*
	VkSamplerCreateInfo��Ч�÷�:
	1.mipLodBias�ľ���ֵ����С�ڻ����VkPhysicalDeviceLimits::maxSamplerLodBias��
	2.���VK_KHR_portability_subset ��չ��������VkPhysicalDevicePortabilitySubsetFeaturesKHR::samplerMipLodBias ΪVK_FALSE�� ��mipLodBias����Ϊ0��
	3.maxLod ������ڵ���minLod
	4.���samplerAnisotropy ����û�п�����anisotropyEnable ����ΪVK_FALSE
	5.���anisotropyEnable ΪVK_TRUE����maxAnisotropy ������ڵ���1.0���ұ���С�ڻ����VkPhysicalDeviceLimits::maxSamplerAnisotropy��
	6.���sampler��Y��CBCR conversion ��������sampler��Y��CBCR conversion��potential format features ��֧��VK_FORMAT_FEATURE_SAMPLED_IMAGE_YCBCR_CONVERSION_SEPARATE_RECONSTRUCTION_FILTER_BIT��minFilter �� magFilter �������sampler��Y��CBCR conversion��chromaFilter��
	7.���unnormalizedCoordinates ΪVK_TRUE����1��minFilter �� magFilter ������ȡ�
											   ��2��mipmapMode ����ΪVK_SAMPLER_MIPMAP_MODE_NEAREST
											   ��3��minLod �� maxLod ����Ϊ0
											   ��4��addressModeU ��addressModeV ÿһ������ΪVK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE ����VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_BORDER
											   ��5��anisotropyEnable ����ΪVK_FALSE
											   ��6��compareEnable����ΪVK_FALSE

	8.���addressModeU, addressModeV ���� addressModeW ����һ��ΪVK_SAMPLER_ADDRESS_MODE_CLAMP_TO_BORDER����borderColor ������һ����Ч��VkBorderColor ֵ
	9.���sampler Y��CBCR conversion ��������1��addressModeU, addressModeV �� addressModeW ����ΪVK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE��anisotropyEnable ����ΪVK_FALSE��unnormalizedCoordinates ����ΪVK_FALSE��
											 ��2�����pNext�к���һ��VkSamplerReductionModeCreateInfo��������ݽṹ��sampler reduction mode ��������ΪVK_SAMPLER_REDUCTION_MODE_WEIGHTED_AVERAGE
	10.���samplerFilterMinmax û�п�������pNext�к���һ��VkSamplerReductionModeCreateInfo��������ݽṹ��sampler reduction mode ��������ΪVK_SAMPLER_REDUCTION_MODE_WEIGHTED_AVERAGE
	11.���samplerMirrorClampToEdge û�п����������VK_KHR_sampler_mirror_clamp_to_edge ��չû�п�������addressModeU, addressModeV �� addressModeW ���벻ΪVK_SAMPLER_ADDRESS_MODE_MIRROR_CLAMP_TO_EDGE
	12.���compareEnable ΪVK_TRUE����compareOp ������һ����Ч��VkCompareOpֵ
	13.���magFilter ��minFilter ��VK_FILTER_CUBIC_EXT��anisotropyEnable ����ΪVK_FALSE
	14.���VK_EXT_filter_cubic ��չû�п����������magFilter �� minFilter ΪVK_FILTER_CUBIC_EXT����VkSamplerReductionModeCreateInfo�е� reductionMode ����ΪVK_SAMPLER_REDUCTION_MODE_WEIGHTED_AVERAGE
	15.���compareEnable ΪVK_TRUE����VkSamplerReductionModeCreateInfo �� reductionMode ����ΪVK_SAMPLER_REDUCTION_MODE_WEIGHTED_AVERAGE
	16.���flags ���� VK_SAMPLER_CREATE_SUBSAMPLED_BIT_EXT, ��1�� minFilter �� magFilter �������
															  ��2��mipmapMode ����ΪVK_SAMPLER_MIPMAP_MODE_NEAREST
															  ��3��minLod �� maxLod ����Ϊ0
															  ��4��addressModeU ��addressModeV ÿһ������ΪVK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE ����VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_BORDER
															  ��5��anisotropyEnable ����ΪVK_FALSE
															  ��6��compareEnable����ΪVK_FALSE
	17.���nonSeamlessCubeMap ����û�п�����flags ���벻���� VK_SAMPLER_CREATE_NON_SEAMLESS_CUBE_MAP_BIT_EXT
	18.���borderColor ��VK_BORDER_COLOR_FLOAT_CUSTOM_EXT ����VK_BORDER_COLOR_INT_CUSTOM_EXT �е�һ������1��pNext�б������һ��VkSamplerCustomBorderColorCreateInfoEXT
																										 ��2�����VkSamplerCustomBorderColorCreateInfoEXT::format ����VK_FORMAT_UNDEFINED����VkSamplerCustomBorderColorCreateInfoEXT::customBorderColor ������format����Ч��Χ��
	19.���customBorderColors ����û�п�����borderColor �Ͳ�����VK_BORDER_COLOR_FLOAT_CUSTOM_EXT ����VK_BORDER_COLOR_INT_CUSTOM_EXT 
	20.ʹ���Զ����border colors��samplers��������ͬʱ������������VkPhysicalDeviceLimits::maxCustomBorderColorSamplers ������
	21.���flags����VK_SAMPLER_CREATE_DESCRIPTOR_BUFFER_CAPTURE_REPLAY_BIT_EXT����descriptorBufferCaptureReplay ���Ա��뿪����
	22.���pNext�а���һ��VkOpaqueCaptureDescriptorDataCreateInfoEXT����flags�������VK_SAMPLER_CREATE_DESCRIPTOR_BUFFER_CAPTURE_REPLAY_BIT_EXT��
	23.���flags����VK_SAMPLER_CREATE_IMAGE_PROCESSING_BIT_QCOM����1�� minFilter �� magFilter ����ΪVK_FILTER_NEAREST
																   ��2��mipmapMode ����ΪVK_SAMPLER_MIPMAP_MODE_NEAREST
																   ��3��minLod �� maxLod ����Ϊ0
																   ��4��addressModeU ��addressModeV ÿһ������ΪVK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE ����VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_BORDER
																   ��5�����addressModeU ��addressModeVΪ VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_BORDER����borderColor����ΪVK_BORDER_COLOR_FLOAT_TRANSPARENT_BLACK
																   ��6��anisotropyEnable ����ΪVK_FALSE
																   ��7��compareEnable����ΪVK_FALSE
	
	*/


	//VkSamplerReductionModeCreateInfo
	VkSamplerReductionModeCreateInfo& samplerReductionModeCreateInfo = samplerCreateInfoEXT.samplerReductionModeCreateInfo;
	samplerReductionModeCreateInfo.reductionMode = VK_SAMPLER_REDUCTION_MODE_MAX;/*��һ�� VkSamplerReductionModeֵ��ָ���������˲�ʱ��ΰ�����ֵ���������ṹ��û�б���������Ĭ��ʹ�� VK_SAMPLER_REDUCTION_MODE_WEIGHTED_AVERAGE
	VkSamplerReductionMode:
	VK_SAMPLER_REDUCTION_MODE_WEIGHTED_AVERAGE:  ָ��ͨ������footprint�е�ֵ�ļ�Ȩƽ��ֵ����ϳ�texelֵ��Ȩ����image operations p1508�½��ж����Ȩ�ؾ�����
	VK_SAMPLER_REDUCTION_MODE_MIN:  ָ��ͨ��ʹ��footprint�з���Ȩ�ص�component-wise����Сֵ����ϳ�texelֵ��
	VK_SAMPLER_REDUCTION_MODE_MAX:  ָ��ͨ��ʹ��footprint�з���Ȩ�ص�component-wise�����ֵ����ϳ�texelֵ��
	VK_SAMPLER_REDUCTION_MODE_WEIGHTED_AVERAGE_RANGECLAMP_QCOM: ָ����ѭVK_SAMPLER_REDUCTION_MODE_WEIGHTED_AVERAGE �ķ�ʽ����ϳ�texelֵ��Ȼ����з�Χ���ƣ��� texel range clamp p1514
	*/



	//VkSamplerCubicWeightsCreateInfoQCOM
	VkSamplerCubicWeightsCreateInfoQCOM& samplerCubicWeightsCreateInfoQCOM = samplerCreateInfoEXT.samplerCubicWeightsCreateInfoQCOM;
	samplerCubicWeightsCreateInfoQCOM.cubicWeights = VK_CUBIC_FILTER_WEIGHTS_B_SPLINE_QCOM;/*��һ�� VkCubicFilterWeightsQCOM ֵ��ָ��ʹ���Ǹ� cubic Ȩ�أ�����������ýṹ�壬��Ĭ��ʹ�� VK_CUBIC_FILTER_WEIGHTS_CATMULL_ROM_QCOM.
	VkCubicFilterWeightsQCOM:
	VK_CUBIC_FILTER_WEIGHTS_CATMULL_ROM_QCOM:  ָ�� Catmull-Rom weights.
	VK_CUBIC_FILTER_WEIGHTS_ZERO_TANGENT_CARDINAL_QCOM:  ָ��  Zero Tangent Cardinal weights.
	VK_CUBIC_FILTER_WEIGHTS_B_SPLINE_QCOM:  ָ��  B-Spline weights.
	VK_CUBIC_FILTER_WEIGHTS_MITCHELL_NETRAVALI_QCOM:  ָ�� Mitchell-Netravali weights.
	*/



	//Sampler Y��CBCR Conversion
	{
		//����һ��VkSamplerYcbcrConversion(��ͬ��VkSamplerYcbcrConversionKHR ) ���
		VkSamplerYcbcrConversion conversion{};
		{
			VkSamplerYcbcrConversionCreateInfo samplerYcbcrConversionCreateInfo{};
			samplerYcbcrConversionCreateInfo.sType = VK_STRUCTURE_TYPE_SAMPLER_YCBCR_CONVERSION_CREATE_INFO;
			
			//VkSamplerYcbcrConversionCreateInfo.pNext
			VkExternalFormatANDROID externalFormatANDROID{};
			VkExternalFormatQNX externalFormatQNX{};
			VkSamplerYcbcrConversionYcbcrDegammaCreateInfoQCOM  samplerYcbcrConversionYcbcrDegammaCreateInfoQCOM{};//VkSamplerYcbcrConversionCreateInfo.pNext�����˸ýṹ�����ָ��һ�� sRGB ��Y��CBCR��R,G��B����һ������ת��
			{
				samplerYcbcrConversionYcbcrDegammaCreateInfoQCOM.sType = VK_STRUCTURE_TYPE_MAX_ENUM;//��Ϊû�ж��壬������������Ϊ�Ƿ�ֵ
				samplerYcbcrConversionYcbcrDegammaCreateInfoQCOM.pNext = nullptr;
				samplerYcbcrConversionYcbcrDegammaCreateInfoQCOM.enableCbCrDegamma = VK_FALSE;//ָ�� sRGB ��Y��CBCR��R,B����������ת��
				samplerYcbcrConversionYcbcrDegammaCreateInfoQCOM.enableYDegamma = VK_FALSE;//ָ�� sRGB ��Y��CBCR��G����������ת��



			}
			samplerYcbcrConversionCreateInfo.pNext = &externalFormatANDROID;//���Ժ���VkExternalFormatANDROID, VkExternalFormatQNX, ���� VkSamplerYcbcrConversionYcbcrDegammaCreateInfoQCOM
			samplerYcbcrConversionCreateInfo.chromaFilter = VK_FILTER_LINEAR;//�� chroma �ؽ����˲�����,������Ϣ�鿴Sampler Y��CBCR Conversion p1496
			samplerYcbcrConversionCreateInfo.components = VkComponentMapping{/*����ֻ��һ����Ч��VkComponentMapping�ṹ��*/};//Ӧ��һ������ VkComponentSwizzle��VkComponentMapping��������range չ���Լ���ɫ�ռ�ת��
			samplerYcbcrConversionCreateInfo.forceExplicitReconstruction = VK_FALSE;//ȷ���ؽ��ܹ���ʽִ�У���Ȼ��Ҫ��֧��
			samplerYcbcrConversionCreateInfo.format = VK_FORMAT_A1R5G5B5_UNORM_PACK16;//��image ��format��ָ��color ��ϢҪ�����л�ȡ
			samplerYcbcrConversionCreateInfo.ycbcrModel = VK_SAMPLER_YCBCR_MODEL_CONVERSION_RGB_IDENTITY;/*��һ��VkSamplerYcbcrModelConversionֵ����������������ɫģ��֮�����ת������ɫת������
			VkSamplerYcbcrModelConversion(�ȼ���VkSamplerYcbcrModelConversionKHR):

			VK_SAMPLER_YCBCR_MODEL_CONVERSION_RGB_IDENTITY:  ָ��conversion������ֵ���ᱻ�ı�
			VK_SAMPLER_YCBCR_MODEL_CONVERSION_YCBCR_IDENTITY:  ָ��û����ɫģ��ת��������ֵ��Χ����չΪY��CBCR��ʽ
			VK_SAMPLER_YCBCR_MODEL_CONVERSION_YCBCR_709:  ָ����ɫģ��ת����Y��CBCR��R��G��B���ת��������ѭKhronos Data Format Specification��p5��. �е�BT.709 Y��CBCR conversionƬ��������BT.709 ����
			VK_SAMPLER_YCBCR_MODEL_CONVERSION_YCBCR_601:  ָ����ɫģ��ת����Y��CBCR��R��G��B���ת��������ѭKhronos Data Format Specification��p5��. �е�BT.601 Y��CBCR conversionƬ��������BT.601 ����
			VK_SAMPLER_YCBCR_MODEL_CONVERSION_YCBCR_2020:  ָ����ɫģ��ת����Y��CBCR��R��G��B���ת��������ѭKhronos Data Format Specification��p5��. �е�BT.2020 Y��CBCR conversionƬ��������BT.2020 ����
			
			�����ת���������
			Y��CBCR   RGB
			Y��    -->  G
			CB     -->  B
			CR     -->  R

			*/
			samplerYcbcrConversionCreateInfo.ycbcrRange = VK_SAMPLER_YCBCR_RANGE_ITU_FULL;/*��һ��VkSamplerYcbcrRangeֵ��ָ���˱����ֵ�Ƿ������½磬������ʹ��������ֵ����
			VkSamplerYcbcrRange����ͬ��VkSamplerYcbcrRangeKHR��:
			VK_SAMPLER_YCBCR_RANGE_ITU_FULL:  ָ������ֵ��ȫ��Χ����Ч�ģ������ݹ��ʵ�����ITU ��full range������������н���
			VK_SAMPLER_YCBCR_RANGE_ITU_NARROW:  ָ������ֵ����ֵ��Χ�������½磬ʣ��ֵ����ITU��narrow range���������������չ
			
			����ϸ�ڼ� Sampler Y��CBCR Range Expansion p1496
			*/
			
			samplerYcbcrConversionCreateInfo.xChromaOffset = VK_CHROMA_LOCATION_COSITED_EVEN;//��һ��VkChromaLocationֵ�� ��������xά���뽵���� chroma ����������Ĳ�����λ�á�xChromaOffset��chroma ����û��ˮƽ�������ĸ�ʽû��Ӱ�졣
			/*
			VkChromaLocation����ͬ��VkChromaLocationKHR��:
			VK_CHROMA_LOCATION_COSITED_EVEN:  ָ��������chroma����������������luma���������
			VK_CHROMA_LOCATION_MIDPOINT:  ָ��������chroma������λ�ھ��������luma�����������ĸ��������luma������֮����е㴦
			*/
			samplerYcbcrConversionCreateInfo.yChromaOffset = VK_CHROMA_LOCATION_MIDPOINT;//��һ��VkChromaLocationֵ����������yά���뽵���� chroma ����������Ĳ���λ�á�yChromaOffset��chroma ����û�д�ֱ�������ĸ�ʽû��Ӱ�졣
			/*
			VkSamplerYcbcrConversionCreateInfo��Ч�÷�:
			1.���external format conversion����������format ����ΪVK_FORMAT_UNDEFINED
			2.���external format conversionδ����������format������unsigned normalized ֵ (i.e.  format����Ϊһ�� UNORM format)
			3.sampler Y��CBCR conversion ��	potential format features ����֧��VK_FORMAT_FEATURE_MIDPOINT_CHROMA_SAMPLES_BIT ����VK_FORMAT_FEATURE_COSITED_CHROMA_SAMPLES_BIT
			4.���sampler Y��CBCR conversion ��	potential format features ��֧��VK_FORMAT_FEATURE_COSITED_CHROMA_SAMPLES_BIT��xChromaOffset �� yChromaOffset ����ΪVK_CHROMA_LOCATION_COSITED_EVEN������Ӧ����Ϊ��������
			5.���sampler Y��CBCR conversion ��	potential format features ��֧��VK_FORMAT_FEATURE_MIDPOINT_CHROMA_SAMPLES_BIT��xChromaOffset �� yChromaOffset ����ΪVK_CHROMA_LOCATION_MIDPOINT������Ӧ����Ϊ��������
			6.���format ���� _422 or _420 ��׺, ��1�� components.g ������identity swizzle 
												   ��2�� components.a ������identity swizzle ,VK_COMPONENT_SWIZZLE_ONE����VK_COMPONENT_SWIZZLE_ZERO
												   ��3�� components.r ������identity swizzle �� VK_COMPONENT_SWIZZLE_B
												   ��4�� components.b ������identity swizzle �� VK_COMPONENT_SWIZZLE_R
												   ��5�����components.r �� components.b �е�һ��Ϊidentity swizzle��������������Ϊidentity swizzle
			7.���ycbcrModel ��ΪVK_SAMPLER_YCBCR_MODEL_CONVERSION_RGB_IDENTITY����components.r, components.g, �� components.b �����Ӧformat�ķ�������components.r, components.g, �� components.b ����ΪVK_COMPONENT_SWIZZLE_ZERO����VK_COMPONENT_SWIZZLE_ONE��Ҳ���ܶ�Ӧ������ת����RGBA��Ϊ0��1�ķ�����
			8.���ycbcrRange ΪVK_SAMPLER_YCBCR_RANGE_ITU_FULL����ͨ��Ӧ��component swizzle ��format��ȡ�õ���R, G �� B ��������ÿ��������8λ���ϡ�
			9.���sampler Y��CBCR conversion ��	potential format features ��֧��VK_FORMAT_FEATURE_SAMPLED_IMAGE_YCBCR_CONVERSION_CHROMA_RECONSTRUCTION_EXPLICIT_FORCEABLE_BIT����forceExplicitReconstruction ����ΪVK_FALSE
			10.���sampler Y��CBCR conversion ��	potential format features ��֧��VK_FORMAT_FEATURE_SAMPLED_IMAGE_YCBCR_CONVERSION_LINEAR_FILTER_BIT����chromaFilter ����ΪVK_FILTER_LINEAR
			11.���pNext�а���һ��VkSamplerYcbcrConversionYcbcrDegammaCreateInfoQCOM�������ycbcrDegamma ����û�п�������1��VkSamplerYcbcrConversionYcbcrDegammaCreateInfoQCOM::enableYDegamma ����ΪVK_FALSE
																														 ��2��VkSamplerYcbcrConversionYcbcrDegammaCreateInfoQCOM::enableCbCrDegamma ����ΪVK_FALSE
			12.���pNext�а���һ��VkSamplerYcbcrConversionYcbcrDegammaCreateInfoQCOM��format������һ��R,G��B����Ϊ8���صĸ�ʽ��

			*/





			//����һ��VkSamplerYcbcrConversion�����������vkCreateSamplerYcbcrConversionKHR
			vkCreateSamplerYcbcrConversion(device, &samplerYcbcrConversionCreateInfo, nullptr, &conversion);// samplerYcbcrConversion ���Ա��뿪��



			//���� sampler Y��CBCR conversion ,��ͬ��vkDestroySamplerYcbcrConversionKHR
			vkDestroySamplerYcbcrConversion(device, conversion, nullptr);

		
		}


		//����һ��������Y��CBCR conversion��sampler
		VkSamplerYcbcrConversionInfo& samplerYcbcrConversionInfo = samplerCreateInfoEXT.samplerYcbcrConversionInfo;
		samplerYcbcrConversionInfo.conversion = VkSamplerYcbcrConversion{/*��������һ����Ч��VkSamplerYcbcrConversion���*/};//һ��ͨ��vkCreateSamplerYcbcrConversion ������ VkSamplerYcbcrConversion���
	}

	//VkSamplerCustomBorderColorCreateInfoEXT
	VkSamplerCustomBorderColorCreateInfoEXT& samplerCustomBorderColorCreateInfoEXT = samplerCreateInfoEXT.samplerCustomBorderColorCreateInfoEXT;
	samplerCustomBorderColorCreateInfoEXT.format = VK_FORMAT_R8G8B8A8_SRGB;//��һ�� VkFormat ָ����sample image view�ĸ�ʽ����� customBorderColorWithoutFormat ����û�п����Ļ���ֵ������VK_FORMAT_UNDEFINED
	samplerCustomBorderColorCreateInfoEXT.customBorderColor = VkClearColorValue{ 1,0,0,1 };//һ��VkClearColorValueֵ������ָ���Զ�����Ҫ�ı߽���ɫ
	/*
	VkSamplerCustomBorderColorCreateInfoEXT��Ч�÷���
	1.���format ��ΪVK_FORMAT_UNDEFINED����format����һ��depth/stencil format����VkSamplerCreateInfo::borderColor ����ƥ��format�ṩ��sampled type���μ� Interpretation of Numeric Format��p4063�� �ı��
	2.���customBorderColorWithoutFormat ����û�п�������format ����ΪVK_FORMAT_UNDEFINED
	3.���sampler���ڲ���һ�� VK_FORMAT_B4G4R4A4_UNORM_PACK16,VK_FORMAT_B5G6R5_UNORM_PACK16, VK_FORMAT_A1B5G5R5_UNORM_PACK16_KHR, ���� VK_FORMAT_B5G5R5A1_UNORM_PACK16 ��ʽ��image view����format����ΪVK_FORMAT_UNDEFINED

	*/



	//VkSamplerBorderColorComponentMappingCreateInfoEXT     ������ borderColorSwizzle���Ա��뿪��
	//��sampler ��VK_BORDER_COLOR_FLOAT_OPAQUE_BLACK, VK_BORDER_COLOR_INT_OPAQUE_BLACK, VK_BORDER_COLOR_FLOAT_CUSTOM_EXT, ���� VK_BORDER_COLOR_INT_CUSTOM_EXT��border color��������sampler���󶨵�һ������ identity swizzle��image view���� VkPhysicalDeviceBorderColorSwizzleFeaturesEXT::borderColorSwizzleFromImage ����δ����������԰����ýṹ�� ����ָ��border color������ӳ���ϵ��
	VkSamplerBorderColorComponentMappingCreateInfoEXT& samplerBorderColorComponentMappingCreateInfoEXT = samplerCreateInfoEXT.samplerBorderColorComponentMappingCreateInfoEXT;
	samplerBorderColorComponentMappingCreateInfoEXT.srgb = VK_TRUE;//��ʾsampler�������sRGB�����ͼ���ʽ��image view��󶨡�
	samplerBorderColorComponentMappingCreateInfoEXT.components = VkComponentMapping{
		VK_COMPONENT_SWIZZLE_IDENTITY,VK_COMPONENT_SWIZZLE_IDENTITY,VK_COMPONENT_SWIZZLE_IDENTITY,VK_COMPONENT_SWIZZLE_IDENTITY };//��һ�� VkComponentMapping ָ����border color������ӳ���ϵ��bolder color ��shader��image ָ��ʹ�ø�bolder color���ص�vec����ķ���ӳ���ϵ



	//VkSamplerBlockMatchWindowCreateInfoQCOM
	VkSamplerBlockMatchWindowCreateInfoQCOM& samplerBlockMatchWindowCreateInfoQCOM = samplerCreateInfoEXT.samplerBlockMatchWindowCreateInfoQCOM;
	samplerBlockMatchWindowCreateInfoQCOM.windowCompareMode = VK_BLOCK_MATCH_WINDOW_COMPARE_MODE_MIN_QCOM;/*��һ�� VkBlockMatchWindowCompareModeQCOM ֵ������ָ���Ƚ�ģʽ��
	VkBlockMatchWindowCompareModeQCOM:

	VK_BLOCK_MATCH_WINDOW_COMPARE_MODE_MIN_QCOM:  ָ�����ڿ�ƥ��������ش����ڵ���С����
	VK_BLOCK_MATCH_WINDOW_COMPARE_MODE_MAX_QCOM:  ָ�����ڿ�ƥ��������ش����ڵ�������

	*/
	samplerBlockMatchWindowCreateInfoQCOM.windowExtent = VkExtent2D{ 1,1 };//��һ�� VkExtent2D ֵָ����blockƥ��Ĵ��ڴ�С��width�Լ�height�����ܴ���VkPhysicalDeviceImageProcessing2PropertiesQCOM::maxBlockMatchWindow


	vkCreateSampler(device, &samplerCreateInfo, nullptr, &sampler);//����samplerʱҪע�� VkPhysicalDeviceLimits::maxSamplerAllocationCount������



	vkDestroySampler(device, sampler, nullptr);


}









NS_TEST_END
