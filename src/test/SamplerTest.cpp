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
		samplerBlockMatchWindowCreateInfoQCOM.sType = VK_STRUCTURE_TYPE_MAX_ENUM;//因为没有定义所以这里设置为最大值
		samplerBlockMatchWindowCreateInfoQCOM.pNext = nullptr;
		samplerBorderColorComponentMappingCreateInfoEXT.sType = VK_STRUCTURE_TYPE_SAMPLER_BORDER_COLOR_COMPONENT_MAPPING_CREATE_INFO_EXT;
		samplerBorderColorComponentMappingCreateInfoEXT.pNext = nullptr;
		samplerCubicWeightsCreateInfoQCOM.sType = VK_STRUCTURE_TYPE_MAX_ENUM;//因为没有定义所以这里设置为最大值
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
	//VkSampler 说明了image sampler的状态，用于在shaders 中进行对image 内存的访问以及应用滤波以及其他变换操作
	VkSampler sampler{};

	VkSamplerCreateInfo samplerCreateInfo{};
	samplerCreateInfo.sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO;
		SamplerCreateInfoEXT samplerCreateInfoEXT{};
	samplerCreateInfo.pNext = &samplerCreateInfoEXT.OpaqueCaptureDescriptorDataCreateInfoEXT;
	samplerCreateInfo.flags = VK_SAMPLER_CREATE_SUBSAMPLED_BIT_EXT;/* 是 VkSamplerCreateFlagBits 组合值的位掩码，指明sampler的额外属性
	VkSamplerCreateFlagBits:
	VK_SAMPLER_CREATE_SUBSAMPLED_BIT_EXT:  指明sampler将从一个创建时flags含有VK_IMAGE_CREATE_SUBSAMPLED_BIT_EXT 的image中读取数据
	VK_SAMPLER_CREATE_SUBSAMPLED_COARSE_RECONSTRUCTION_BIT_EXT:  指明当重建一个subsampled image的访问的纹理的全部color 值时将采用估计值的方式
	VK_SAMPLER_CREATE_NON_SEAMLESS_CUBE_MAP_BIT_EXT:  指明不会处理cube map的边缘像素
	VK_SAMPLER_CREATE_IMAGE_PROCESSING_BIT_QCOM:  指明sampler将从使用OpImageWeightedSampleQCOM, OpImageBoxFilterQCOM, OpImageBlockMatchGatherSSDQCOM, OpImageBlockMatchGatherSADQCOM, OpImageBlockMatchWindowSSDQCOM,
																OpImageBlockMatchWindowSADQCOM, OpImageBlockMatchSSDQCOM, 或者 OpImageBlockMatchSADQCOM的 image中读取数据
	

	VK_SAMPLER_CREATE_DESCRIPTOR_BUFFER_CAPTURE_REPLAY_BIT_EXT:  指明sampler可以在capturing 和 replaying 用作 descriptor，(e.g. 对于 trace capture 和 replay),可从VkOpaqueCaptureDescriptorDataCreateInfoEXT 中查看更多信息

	*/
	samplerCreateInfo.addressModeU = VK_SAMPLER_ADDRESS_MODE_REPEAT;//是一个 VkSamplerAddressMode值，指定了当对U坐标进行采样时超出[0,1]范围时使用的寻址模式
	/*
	VkSamplerAddressMode:
	VK_SAMPLER_ADDRESS_MODE_REPEAT:  指定使用repeat wrap mode
	VK_SAMPLER_ADDRESS_MODE_MIRRORED_REPEAT:  指定使用 mirrored repeat wrap mode 
	VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE:  指定使用 clamp to edge wrap mode 
	VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_BORDER:  指定使用clamp to border wrap mode
	VK_SAMPLER_ADDRESS_MODE_MIRROR_CLAMP_TO_EDGE:  指定使用 mirror clamp to edge wrap，只在samplerMirrorClampToEdge 开启或者VK_KHR_sampler_mirror_clamp_to_edg 拓展开启了才有效

	wrap mode详情见 Wrapping Operation p1510

	*/
	samplerCreateInfo.addressModeV = VK_SAMPLER_ADDRESS_MODE_REPEAT;//是一个 VkSamplerAddressMode值，指定了当对V坐标进行采样时超出[0,1]范围时使用的寻址模式
	samplerCreateInfo.addressModeW = VK_SAMPLER_ADDRESS_MODE_REPEAT;//是一个 VkSamplerAddressMode值，指定了当对W坐标进行采样时超出[0,1]范围时使用的寻址模式
	samplerCreateInfo.borderColor = VkBorderColor::VK_BORDER_COLOR_FLOAT_OPAQUE_BLACK;/*是一个 VkBorderColor值，指定了使用的预先定义的颜色，当对边界处的像素进行采样时使用
	VkBorderColor:
	VK_BORDER_COLOR_FLOAT_TRANSPARENT_BLACK: 指定为一个浮点格式的透明的黑色
	VK_BORDER_COLOR_INT_TRANSPARENT_BLACK:  指定为一个整形格式的透明的黑色
	VK_BORDER_COLOR_FLOAT_OPAQUE_BLACK:  指定为一个浮点格式的不透明的黑色
	VK_BORDER_COLOR_INT_OPAQUE_BLACK:  指定为一个整形格式的不透明的黑色
	VK_BORDER_COLOR_FLOAT_OPAQUE_WHITE:  指定为一个浮点格式的不透明的白色
	VK_BORDER_COLOR_INT_OPAQUE_WHITE:  指定为一个整形格式的不透明的白色
	VK_BORDER_COLOR_FLOAT_CUSTOM_EXT:  指定为VkSamplerCreateInfo::pNext中的VkSamplerCustomBorderColorCreateInfoEXT 的浮点类型的颜色值作为其颜色
	VK_BORDER_COLOR_INT_CUSTOM_EXT:  指定为VkSamplerCreateInfo::pNext中的VkSamplerCustomBorderColorCreateInfoEXT 的整形类型的颜色值作为其颜色


	详情见  Texel Replacement p1486
	
	*/
	samplerCreateInfo.anisotropyEnable = VK_FALSE;//控制是否开启 anisotropic filtering ，参见 Texel Anisotropic Filtering p1515
	samplerCreateInfo.maxAnisotropy = 1;//是shader取clamp的anisotropy 值，只有当anisotropyEnable 为VK_TRUE才有效，
	samplerCreateInfo.compareEnable = VK_FALSE;//控制是否开启在查找采样时对一个引用的值reference进行比较操作，参见 Comparison p1505
	samplerCreateInfo.compareOp = VK_COMPARE_OP_LESS;/*是一个 VkCompareOp值，指定了在filter前获取数据时进行比较操作时使用的比较操作，见 Depth Compare Operation p1488,比较操作将返回比较的结果true或者false
	VkCompareOp:
	VK_COMPARE_OP_NEVER: 指定比较结果永远为false.
	VK_COMPARE_OP_LESS: 指定一个比较操作 reference < test. 
	VK_COMPARE_OP_EQUAL: 指定一个比较操作 reference = test. 
	VK_COMPARE_OP_LESS_OR_EQUAL: 指定一个比较操作 reference ≤ test. 
	VK_COMPARE_OP_GREATER: 指定一个比较操作 reference > test. 
	VK_COMPARE_OP_NOT_EQUAL: 指定一个比较操作 reference ≠ test.
	VK_COMPARE_OP_GREATER_OR_EQUAL : 指定一个比较操作 reference ≥ test. 
	VK_COMPARE_OP_ALWAYS: 指定比较结果永远为true.
	
	*/
	
	samplerCreateInfo.magFilter = VK_FILTER_LINEAR;//是一个VkFilter值，指定要应用于查找采样的magnification filter
	/*
	VkFilter:
	VK_FILTER_NEAREST:  指定 nearest filtering.
	VK_FILTER_LINEAR:  指定  linear filtering.
	VK_FILTER_CUBIC_EXT:  指定  cubic filtering.
	
	filter细节见  Texel Filtering. p1511
	*/
	samplerCreateInfo.minFilter = VK_FILTER_LINEAR;// 是一个VkFilter值，它指定要应用于查找采样的minification filter
	samplerCreateInfo.minLod = 0;//用来限制计算的LOD值的最小值，参见p1505 LOD Operation
	samplerCreateInfo.maxLod = 1;//用来限制计算的LOD值的最大值，参见p1505 LOD Operation,可以设置为 VK_LOD_CLAMP_NONE指明不进行LOD最大值限制
	samplerCreateInfo.mipLodBias = 0;//一个添加到mipmap LOD计算中以及SPIV-V代码中image采样函数的提供的mipmap的偏移量，参见p1505  LOD Operation
	samplerCreateInfo.mipmapMode = VK_SAMPLER_MIPMAP_MODE_LINEAR;/*是一个 VkSamplerMipmapMode值指明要应用于查找采样的mipmap filter
	VkSamplerMipmapMode:
	VK_SAMPLER_MIPMAP_MODE_NEAREST:  指明 nearest filtering.
	VK_SAMPLER_MIPMAP_MODE_LINEAR:  指明 linear filtering.
	
	filter细节见  Texel Filtering. p1511
	*/
	samplerCreateInfo.unnormalizedCoordinates = VK_FALSE;//控制是否使用非标准化或标准化的纹理坐标来寻址图像的纹理。当设置为VK_TRUE时，用于查找文本的图像坐标的范围从零到图像的每个维度的大小。当设置为VK_FALSE时，图像坐标每个维度的范围为0到1。
	/*
	VkSamplerCreateInfo有效用法:
	1.mipLodBias的绝对值必须小于或等于VkPhysicalDeviceLimits::maxSamplerLodBias。
	2.如果VK_KHR_portability_subset 拓展开启，且VkPhysicalDevicePortabilitySubsetFeaturesKHR::samplerMipLodBias 为VK_FALSE， 则mipLodBias必须为0。
	3.maxLod 必须大于等于minLod
	4.如果samplerAnisotropy 特性没有开启，anisotropyEnable 必须为VK_FALSE
	5.如果anisotropyEnable 为VK_TRUE，则maxAnisotropy 必须大于等于1.0，且必须小于或等于VkPhysicalDeviceLimits::maxSamplerAnisotropy。
	6.如果sampler的Y′CBCR conversion 开启，且sampler的Y′CBCR conversion的potential format features 不支持VK_FORMAT_FEATURE_SAMPLED_IMAGE_YCBCR_CONVERSION_SEPARATE_RECONSTRUCTION_FILTER_BIT，minFilter 和 magFilter 必须等于sampler的Y′CBCR conversion的chromaFilter。
	7.如果unnormalizedCoordinates 为VK_TRUE，则（1）minFilter 和 magFilter 必须相等。
											   （2）mipmapMode 必须为VK_SAMPLER_MIPMAP_MODE_NEAREST
											   （3）minLod 和 maxLod 必须为0
											   （4）addressModeU 和addressModeV 每一个必须为VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE 或者VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_BORDER
											   （5）anisotropyEnable 必须为VK_FALSE
											   （6）compareEnable必须为VK_FALSE

	8.如果addressModeU, addressModeV 或者 addressModeW 任意一个为VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_BORDER，则borderColor 必须是一个有效的VkBorderColor 值
	9.如果sampler Y′CBCR conversion 开启，则（1）addressModeU, addressModeV 和 addressModeW 必须为VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE，anisotropyEnable 必须为VK_FALSE，unnormalizedCoordinates 必须为VK_FALSE。
											 （2）如果pNext中含有一个VkSamplerReductionModeCreateInfo，则该数据结构的sampler reduction mode 必须设置为VK_SAMPLER_REDUCTION_MODE_WEIGHTED_AVERAGE
	10.如果samplerFilterMinmax 没有开启，且pNext中含有一个VkSamplerReductionModeCreateInfo，则该数据结构的sampler reduction mode 必须设置为VK_SAMPLER_REDUCTION_MODE_WEIGHTED_AVERAGE
	11.如果samplerMirrorClampToEdge 没有开启，且如果VK_KHR_sampler_mirror_clamp_to_edge 拓展没有开启，则addressModeU, addressModeV 和 addressModeW 必须不为VK_SAMPLER_ADDRESS_MODE_MIRROR_CLAMP_TO_EDGE
	12.如果compareEnable 为VK_TRUE，则compareOp 必须是一个有效的VkCompareOp值
	13.如果magFilter 或minFilter 是VK_FILTER_CUBIC_EXT，anisotropyEnable 必须为VK_FALSE
	14.如果VK_EXT_filter_cubic 拓展没有开启，且如果magFilter 或 minFilter 为VK_FILTER_CUBIC_EXT，则VkSamplerReductionModeCreateInfo中的 reductionMode 必须为VK_SAMPLER_REDUCTION_MODE_WEIGHTED_AVERAGE
	15.如果compareEnable 为VK_TRUE，则VkSamplerReductionModeCreateInfo 的 reductionMode 必须为VK_SAMPLER_REDUCTION_MODE_WEIGHTED_AVERAGE
	16.如果flags 包含 VK_SAMPLER_CREATE_SUBSAMPLED_BIT_EXT, 则（1） minFilter 和 magFilter 必须相等
															  （2）mipmapMode 必须为VK_SAMPLER_MIPMAP_MODE_NEAREST
															  （3）minLod 和 maxLod 必须为0
															  （4）addressModeU 和addressModeV 每一个必须为VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE 或者VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_BORDER
															  （5）anisotropyEnable 必须为VK_FALSE
															  （6）compareEnable必须为VK_FALSE
	17.如果nonSeamlessCubeMap 特性没有开启，flags 必须不包含 VK_SAMPLER_CREATE_NON_SEAMLESS_CUBE_MAP_BIT_EXT
	18.如果borderColor 是VK_BORDER_COLOR_FLOAT_CUSTOM_EXT 或者VK_BORDER_COLOR_INT_CUSTOM_EXT 中的一个，则（1）pNext中必须包含一个VkSamplerCustomBorderColorCreateInfoEXT
																										 （2）如果VkSamplerCustomBorderColorCreateInfoEXT::format 不是VK_FORMAT_UNDEFINED，则VkSamplerCustomBorderColorCreateInfoEXT::customBorderColor 必须在format的有效范围内
	19.如果customBorderColors 特性没有开启，borderColor 就不能是VK_BORDER_COLOR_FLOAT_CUSTOM_EXT 或者VK_BORDER_COLOR_INT_CUSTOM_EXT 
	20.使用自定义的border colors的samplers的最大可以同时创建的数量由VkPhysicalDeviceLimits::maxCustomBorderColorSamplers 给出。
	21.如果flags包含VK_SAMPLER_CREATE_DESCRIPTOR_BUFFER_CAPTURE_REPLAY_BIT_EXT，则descriptorBufferCaptureReplay 特性必须开启。
	22.如果pNext中包含一个VkOpaqueCaptureDescriptorDataCreateInfoEXT，则flags必须包含VK_SAMPLER_CREATE_DESCRIPTOR_BUFFER_CAPTURE_REPLAY_BIT_EXT。
	23.如果flags包含VK_SAMPLER_CREATE_IMAGE_PROCESSING_BIT_QCOM，则（1） minFilter 和 magFilter 必须为VK_FILTER_NEAREST
																   （2）mipmapMode 必须为VK_SAMPLER_MIPMAP_MODE_NEAREST
																   （3）minLod 和 maxLod 必须为0
																   （4）addressModeU 和addressModeV 每一个必须为VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE 或者VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_BORDER
																   （5）如果addressModeU 或addressModeV为 VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_BORDER，则borderColor必须为VK_BORDER_COLOR_FLOAT_TRANSPARENT_BLACK
																   （6）anisotropyEnable 必须为VK_FALSE
																   （7）compareEnable必须为VK_FALSE
	
	*/


	//VkSamplerReductionModeCreateInfo
	VkSamplerReductionModeCreateInfo& samplerReductionModeCreateInfo = samplerCreateInfoEXT.samplerReductionModeCreateInfo;
	samplerReductionModeCreateInfo.reductionMode = VK_SAMPLER_REDUCTION_MODE_MAX;/*是一个 VkSamplerReductionMode值，指定了纹理滤波时如何绑定纹理值，如果这个结构体没有被包含，则默认使用 VK_SAMPLER_REDUCTION_MODE_WEIGHTED_AVERAGE
	VkSamplerReductionMode:
	VK_SAMPLER_REDUCTION_MODE_WEIGHTED_AVERAGE:  指定通过计算footprint中的值的加权平均值来组合成texel值，权重由image operations p1508章节中定义的权重决定。
	VK_SAMPLER_REDUCTION_MODE_MIN:  指定通过使用footprint中非零权重的component-wise的最小值来组合成texel值。
	VK_SAMPLER_REDUCTION_MODE_MAX:  指定通过使用footprint中非零权重的component-wise的最大值来组合成texel值。
	VK_SAMPLER_REDUCTION_MODE_WEIGHTED_AVERAGE_RANGECLAMP_QCOM: 指明遵循VK_SAMPLER_REDUCTION_MODE_WEIGHTED_AVERAGE 的方式来组合成texel值，然后进行范围限制，见 texel range clamp p1514
	*/



	//VkSamplerCubicWeightsCreateInfoQCOM
	VkSamplerCubicWeightsCreateInfoQCOM& samplerCubicWeightsCreateInfoQCOM = samplerCreateInfoEXT.samplerCubicWeightsCreateInfoQCOM;
	samplerCubicWeightsCreateInfoQCOM.cubicWeights = VK_CUBIC_FILTER_WEIGHTS_B_SPLINE_QCOM;/*是一个 VkCubicFilterWeightsQCOM 值，指明使用那个 cubic 权重，如果不包含该结构体，则默认使用 VK_CUBIC_FILTER_WEIGHTS_CATMULL_ROM_QCOM.
	VkCubicFilterWeightsQCOM:
	VK_CUBIC_FILTER_WEIGHTS_CATMULL_ROM_QCOM:  指定 Catmull-Rom weights.
	VK_CUBIC_FILTER_WEIGHTS_ZERO_TANGENT_CARDINAL_QCOM:  指定  Zero Tangent Cardinal weights.
	VK_CUBIC_FILTER_WEIGHTS_B_SPLINE_QCOM:  指定  B-Spline weights.
	VK_CUBIC_FILTER_WEIGHTS_MITCHELL_NETRAVALI_QCOM:  指定 Mitchell-Netravali weights.
	*/



	//Sampler Y′CBCR Conversion
	{
		//创建一个VkSamplerYcbcrConversion(等同于VkSamplerYcbcrConversionKHR ) 句柄
		VkSamplerYcbcrConversion conversion{};
		{
			VkSamplerYcbcrConversionCreateInfo samplerYcbcrConversionCreateInfo{};
			samplerYcbcrConversionCreateInfo.sType = VK_STRUCTURE_TYPE_SAMPLER_YCBCR_CONVERSION_CREATE_INFO;
			
			//VkSamplerYcbcrConversionCreateInfo.pNext
			VkExternalFormatANDROID externalFormatANDROID{};
			VkExternalFormatQNX externalFormatQNX{};
			VkSamplerYcbcrConversionYcbcrDegammaCreateInfoQCOM  samplerYcbcrConversionYcbcrDegammaCreateInfoQCOM{};//VkSamplerYcbcrConversionCreateInfo.pNext包含了该结构体可以指定一个 sRGB 到Y′CBCR的R,G和B分量一个线性转换
			{
				samplerYcbcrConversionYcbcrDegammaCreateInfoQCOM.sType = VK_STRUCTURE_TYPE_MAX_ENUM;//因为没有定义，所以这里设置为非法值
				samplerYcbcrConversionYcbcrDegammaCreateInfoQCOM.pNext = nullptr;
				samplerYcbcrConversionYcbcrDegammaCreateInfoQCOM.enableCbCrDegamma = VK_FALSE;//指明 sRGB 到Y′CBCR的R,B分量的线性转换
				samplerYcbcrConversionYcbcrDegammaCreateInfoQCOM.enableYDegamma = VK_FALSE;//指明 sRGB 到Y′CBCR的G分量的线性转换



			}
			samplerYcbcrConversionCreateInfo.pNext = &externalFormatANDROID;//可以含有VkExternalFormatANDROID, VkExternalFormatQNX, 或者 VkSamplerYcbcrConversionYcbcrDegammaCreateInfoQCOM
			samplerYcbcrConversionCreateInfo.chromaFilter = VK_FILTER_LINEAR;//是 chroma 重建的滤波类型,更多信息查看Sampler Y′CBCR Conversion p1496
			samplerYcbcrConversionCreateInfo.components = VkComponentMapping{/*假设只是一个有效的VkComponentMapping结构体*/};//应用一个基于 VkComponentSwizzle的VkComponentMapping，优先于range 展开以及颜色空间转换
			samplerYcbcrConversionCreateInfo.forceExplicitReconstruction = VK_FALSE;//确保重建能够显式执行，当然需要被支持
			samplerYcbcrConversionCreateInfo.format = VK_FORMAT_A1R5G5B5_UNORM_PACK16;//是image 的format，指定color 信息要从其中获取
			samplerYcbcrConversionCreateInfo.ycbcrModel = VK_SAMPLER_YCBCR_MODEL_CONVERSION_RGB_IDENTITY;/*是一个VkSamplerYcbcrModelConversion值，描述了用于在颜色模型之间进行转换的颜色转换矩阵。
			VkSamplerYcbcrModelConversion(等价于VkSamplerYcbcrModelConversionKHR):

			VK_SAMPLER_YCBCR_MODEL_CONVERSION_RGB_IDENTITY:  指明conversion的输入值不会被改变
			VK_SAMPLER_YCBCR_MODEL_CONVERSION_YCBCR_IDENTITY:  指明没有颜色模型转换，输入值范围被拓展为Y′CBCR格式
			VK_SAMPLER_YCBCR_MODEL_CONVERSION_YCBCR_709:  指明颜色模型转换从Y′CBCR到R′G′B′的转换矩阵遵循Khronos Data Format Specification（p5）. 中的BT.709 Y′CBCR conversion片段描述的BT.709 规则
			VK_SAMPLER_YCBCR_MODEL_CONVERSION_YCBCR_601:  指明颜色模型转换从Y′CBCR到R′G′B′的转换矩阵遵循Khronos Data Format Specification（p5）. 中的BT.601 Y′CBCR conversion片段描述的BT.601 规则
			VK_SAMPLER_YCBCR_MODEL_CONVERSION_YCBCR_2020:  指明颜色模型转换从Y′CBCR到R′G′B′的转换矩阵遵循Khronos Data Format Specification（p5）. 中的BT.2020 Y′CBCR conversion片段描述的BT.2020 规则
			
			这里的转换好像就是
			Y′CBCR   RGB
			Y′    -->  G
			CB     -->  B
			CR     -->  R

			*/
			samplerYcbcrConversionCreateInfo.ycbcrRange = VK_SAMPLER_YCBCR_RANGE_ITU_FULL;/*是一个VkSamplerYcbcrRange值，指明了编码的值是否有上下界，或者是使用整个数值区间
			VkSamplerYcbcrRange（等同于VkSamplerYcbcrRangeKHR）:
			VK_SAMPLER_YCBCR_RANGE_ITU_FULL:  指定编码值的全范围是有效的，并根据国际电联的ITU “full range”量化规则进行解释
			VK_SAMPLER_YCBCR_RANGE_ITU_NARROW:  指明编码值的数值范围保留上下界，剩余值根据ITU“narrow range”量化规则进行扩展
			
			更多细节见 Sampler Y′CBCR Range Expansion p1496
			*/
			
			samplerYcbcrConversionCreateInfo.xChromaOffset = VK_CHROMA_LOCATION_COSITED_EVEN;//是一个VkChromaLocation值， 描述了在x维中与降采样 chroma 分量相关联的采样点位置。xChromaOffset对chroma 分量没有水平降采样的格式没有影响。
			/*
			VkChromaLocation（等同于VkChromaLocationKHR）:
			VK_CHROMA_LOCATION_COSITED_EVEN:  指定降采样chroma采样点与均匀坐标的luma采样点对齐
			VK_CHROMA_LOCATION_MIDPOINT:  指定降采样chroma采样点位于均匀坐标的luma采样点和最近的更大的奇数luma采样点之间的中点处
			*/
			samplerYcbcrConversionCreateInfo.yChromaOffset = VK_CHROMA_LOCATION_MIDPOINT;//是一个VkChromaLocation值，描述了在y维中与降采样 chroma 分量相关联的采样位置。yChromaOffset对chroma 分量没有垂直降采样的格式没有影响。
			/*
			VkSamplerYcbcrConversionCreateInfo有效用法:
			1.如果external format conversion被创建，则format 必须为VK_FORMAT_UNDEFINED
			2.如果external format conversion未被创建，则format必须是unsigned normalized 值 (i.e.  format必须为一个 UNORM format)
			3.sampler Y′CBCR conversion 的	potential format features 必须支持VK_FORMAT_FEATURE_MIDPOINT_CHROMA_SAMPLES_BIT 或者VK_FORMAT_FEATURE_COSITED_CHROMA_SAMPLES_BIT
			4.如果sampler Y′CBCR conversion 的	potential format features 不支持VK_FORMAT_FEATURE_COSITED_CHROMA_SAMPLES_BIT，xChromaOffset 和 yChromaOffset 不能为VK_CHROMA_LOCATION_COSITED_EVEN如果其对应分量为降采样的
			5.如果sampler Y′CBCR conversion 的	potential format features 不支持VK_FORMAT_FEATURE_MIDPOINT_CHROMA_SAMPLES_BIT，xChromaOffset 和 yChromaOffset 不能为VK_CHROMA_LOCATION_MIDPOINT如果其对应分量为降采样的
			6.如果format 含有 _422 or _420 后缀, 则（1） components.g 必须是identity swizzle 
												   （2） components.a 必须是identity swizzle ,VK_COMPONENT_SWIZZLE_ONE或者VK_COMPONENT_SWIZZLE_ZERO
												   （3） components.r 必须是identity swizzle 或 VK_COMPONENT_SWIZZLE_B
												   （4） components.b 必须是identity swizzle 或 VK_COMPONENT_SWIZZLE_R
												   （5）如果components.r 或 components.b 中的一个为identity swizzle，则两个都必须为identity swizzle
			7.如果ycbcrModel 不为VK_SAMPLER_YCBCR_MODEL_CONVERSION_RGB_IDENTITY，则components.r, components.g, 和 components.b 必须对应format的分量，即components.r, components.g, 和 components.b 不能为VK_COMPONENT_SWIZZLE_ZERO或者VK_COMPONENT_SWIZZLE_ONE，也不能对应到包含转换到RGBA后为0或1的分量。
			8.如果ycbcrRange 为VK_SAMPLER_YCBCR_RANGE_ITU_FULL，则通过应用component swizzle 到format获取得到的R, G 和 B 分量必须每个都含有8位以上。
			9.如果sampler Y′CBCR conversion 的	potential format features 不支持VK_FORMAT_FEATURE_SAMPLED_IMAGE_YCBCR_CONVERSION_CHROMA_RECONSTRUCTION_EXPLICIT_FORCEABLE_BIT，则forceExplicitReconstruction 必须为VK_FALSE
			10.如果sampler Y′CBCR conversion 的	potential format features 不支持VK_FORMAT_FEATURE_SAMPLED_IMAGE_YCBCR_CONVERSION_LINEAR_FILTER_BIT，则chromaFilter 不能为VK_FILTER_LINEAR
			11.如果pNext中包含一个VkSamplerYcbcrConversionYcbcrDegammaCreateInfoQCOM，且如果ycbcrDegamma 特性没有开启，则（1）VkSamplerYcbcrConversionYcbcrDegammaCreateInfoQCOM::enableYDegamma 必须为VK_FALSE
																														 （2）VkSamplerYcbcrConversionYcbcrDegammaCreateInfoQCOM::enableCbCrDegamma 必须为VK_FALSE
			12.如果pNext中包含一个VkSamplerYcbcrConversionYcbcrDegammaCreateInfoQCOM，format必须是一个R,G和B分量为8比特的格式。

			*/





			//创建一个VkSamplerYcbcrConversion句柄，等用于vkCreateSamplerYcbcrConversionKHR
			vkCreateSamplerYcbcrConversion(device, &samplerYcbcrConversionCreateInfo, nullptr, &conversion);// samplerYcbcrConversion 特性必须开启



			//销毁 sampler Y′CBCR conversion ,等同于vkDestroySamplerYcbcrConversionKHR
			vkDestroySamplerYcbcrConversion(device, conversion, nullptr);

		
		}


		//创建一个开启了Y′CBCR conversion的sampler
		VkSamplerYcbcrConversionInfo& samplerYcbcrConversionInfo = samplerCreateInfoEXT.samplerYcbcrConversionInfo;
		samplerYcbcrConversionInfo.conversion = VkSamplerYcbcrConversion{/*假设这是一个有效的VkSamplerYcbcrConversion句柄*/};//一个通过vkCreateSamplerYcbcrConversion 创建的 VkSamplerYcbcrConversion句柄
	}

	//VkSamplerCustomBorderColorCreateInfoEXT
	VkSamplerCustomBorderColorCreateInfoEXT& samplerCustomBorderColorCreateInfoEXT = samplerCreateInfoEXT.samplerCustomBorderColorCreateInfoEXT;
	samplerCustomBorderColorCreateInfoEXT.format = VK_FORMAT_R8G8B8A8_SRGB;//是一个 VkFormat 指明了sample image view的格式，如果 customBorderColorWithoutFormat 特性没有开启的化该值可能是VK_FORMAT_UNDEFINED
	samplerCustomBorderColorCreateInfoEXT.customBorderColor = VkClearColorValue{ 1,0,0,1 };//一个VkClearColorValue值，用于指定自定义需要的边界颜色
	/*
	VkSamplerCustomBorderColorCreateInfoEXT有效用法：
	1.如果format 不为VK_FORMAT_UNDEFINED，且format不是一个depth/stencil format，则VkSamplerCreateInfo::borderColor 必须匹配format提供的sampled type。参见 Interpretation of Numeric Format（p4063） 的表格
	2.如果customBorderColorWithoutFormat 特性没有开启，则format 不能为VK_FORMAT_UNDEFINED
	3.如果sampler用于采样一个 VK_FORMAT_B4G4R4A4_UNORM_PACK16,VK_FORMAT_B5G6R5_UNORM_PACK16, VK_FORMAT_A1B5G5R5_UNORM_PACK16_KHR, 或者 VK_FORMAT_B5G5R5A1_UNORM_PACK16 格式的image view，则format不能为VK_FORMAT_UNDEFINED

	*/



	//VkSamplerBorderColorComponentMappingCreateInfoEXT     》》》 borderColorSwizzle特性必须开启
	//在sampler 以VK_BORDER_COLOR_FLOAT_OPAQUE_BLACK, VK_BORDER_COLOR_INT_OPAQUE_BLACK, VK_BORDER_COLOR_FLOAT_CUSTOM_EXT, 或者 VK_BORDER_COLOR_INT_CUSTOM_EXT的border color创建，且sampler将绑定到一个不含 identity swizzle的image view，且 VkPhysicalDeviceBorderColorSwizzleFeaturesEXT::borderColorSwizzleFromImage 特性未开启，则可以包含该结构体 用于指定border color分量的映射关系。
	VkSamplerBorderColorComponentMappingCreateInfoEXT& samplerBorderColorComponentMappingCreateInfoEXT = samplerCreateInfoEXT.samplerBorderColorComponentMappingCreateInfoEXT;
	samplerBorderColorComponentMappingCreateInfoEXT.srgb = VK_TRUE;//表示sampler将与具有sRGB编码的图像格式的image view相绑定。
	samplerBorderColorComponentMappingCreateInfoEXT.components = VkComponentMapping{
		VK_COMPONENT_SWIZZLE_IDENTITY,VK_COMPONENT_SWIZZLE_IDENTITY,VK_COMPONENT_SWIZZLE_IDENTITY,VK_COMPONENT_SWIZZLE_IDENTITY };//是一个 VkComponentMapping 指明了border color分量的映射关系。bolder color 和shader中image 指令使用该bolder color返回的vec结果的分量映射关系



	//VkSamplerBlockMatchWindowCreateInfoQCOM
	VkSamplerBlockMatchWindowCreateInfoQCOM& samplerBlockMatchWindowCreateInfoQCOM = samplerCreateInfoEXT.samplerBlockMatchWindowCreateInfoQCOM;
	samplerBlockMatchWindowCreateInfoQCOM.windowCompareMode = VK_BLOCK_MATCH_WINDOW_COMPARE_MODE_MIN_QCOM;/*是一个 VkBlockMatchWindowCompareModeQCOM 值，用于指定比较模式。
	VkBlockMatchWindowCompareModeQCOM:

	VK_BLOCK_MATCH_WINDOW_COMPARE_MODE_MIN_QCOM:  指定窗口块匹配操作返回窗口内的最小错误。
	VK_BLOCK_MATCH_WINDOW_COMPARE_MODE_MAX_QCOM:  指定窗口块匹配操作返回窗口内的最大错误。

	*/
	samplerBlockMatchWindowCreateInfoQCOM.windowExtent = VkExtent2D{ 1,1 };//是一个 VkExtent2D 值指明了block匹配的窗口大小的width以及height。不能大于VkPhysicalDeviceImageProcessing2PropertiesQCOM::maxBlockMatchWindow


	vkCreateSampler(device, &samplerCreateInfo, nullptr, &sampler);//创建sampler时要注意 VkPhysicalDeviceLimits::maxSamplerAllocationCount的限制



	vkDestroySampler(device, sampler, nullptr);


}









NS_TEST_END
