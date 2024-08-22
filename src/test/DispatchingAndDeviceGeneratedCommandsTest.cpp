#include "DispatchingAndDeviceGeneratedCommandsTest.h"

NS_TEST_BEGIN

DispatchingAndDeviceGeneratedCommandsTest::DispatchingAndDeviceGeneratedCommandsTest()
{
}

void DispatchingAndDeviceGeneratedCommandsTest::run()
{
}

DispatchingAndDeviceGeneratedCommandsTest::~DispatchingAndDeviceGeneratedCommandsTest()
{
}

void DispatchingAndDeviceGeneratedCommandsTest::DispatchingCommandsTest()
{
	/*
	Dispatching commands（名字带有Dispatch）会触发在compute pipeline中进行的工作。调用该命令前必须绑定了compute pipeline
	*/

	VkCommandBuffer commandBuffer{/*假设这是一个有效的VkCommandBuffer*/ };

	//dispatch local workgroups    该命令会组装一个含有groupCountX × groupCountY × groupCountZ个local work groups的 global work group 
	vkCmdDispatch(commandBuffer, 1/*groupCountX,为dispatch的local workgroups 的 X 维度的数量.*/, 1/*groupCountY,为dispatch的local workgroups 的 Y 维度的数量.*/, 1/*groupCountZ,为dispatch的local workgroups 的 Z 维度的数量.*/);
	/*
	vkCmdDispatch有效用法:
    1.如果一个VkSampler以其magFilter或者minFilter等于VK_FILTER_LINEAR创建，则（1）如果reductionMode为VK_SAMPLER_REDUCTION_MODE_WEIGHTED_AVERAGE，如果用于采样一个VkImageView作为该命令的结果的compareEnable为VK_FALSE，则该image view的format features必须包含VK_FORMAT_FEATURE_SAMPLED_IMAGE_FILTER_LINEAR_BIT
                                                                             （2）如果reductionMode为VK_SAMPLER_REDUCTION_MODE_MIN 或者VK_SAMPLER_REDUCTION_MODE_MAX之一 用于采样一个VkImageView作为该命令的结果，则该image view的format features必须包含VK_FORMAT_FEATURE_SAMPLED_IMAGE_FILTER_MINMAX_BIT
    2.如果一个VkSampler以其mipmapMode 等于VK_SAMPLER_MIPMAP_MODE_LINEAR创建，则（1）如果reductionMode为VK_SAMPLER_REDUCTION_MODE_WEIGHTED_AVERAGE，如果用于采样一个VkImageView作为该命令的结果的compareEnable为VK_FALSE，则该image view的format features必须包含VK_FORMAT_FEATURE_SAMPLED_IMAGE_FILTER_LINEAR_BIT
                                                                             （2）如果reductionMode为VK_SAMPLER_REDUCTION_MODE_MIN 或者VK_SAMPLER_REDUCTION_MODE_MAX之一 用于采样一个VkImageView作为该命令的结果，则该image view的format features必须包含VK_FORMAT_FEATURE_SAMPLED_IMAGE_FILTER_MINMAX_BIT
    3.如果一个VkSampler以其unnormalizedCoordinates等于VK_TRUE用于采样一个VkImageView作为该命令的结果创建，则（1）该image view的levelCount以及layerCount必须为1
                                                                                                            （2）该image view的viewType必须为VK_IMAGE_VIEW_TYPE_1D 或者 VK_IMAGE_VIEW_TYPE_2D
    4.如果一个VkImageView的采样带depth comparison操作，则image view的format features必须包含VK_FORMAT_FEATURE_2_SAMPLED_IMAGE_DEPTH_COMPARISON_BIT
    5.如果一个VkImageView使用atomic operations作为该命令的结果进行访问，则image view的format features必须包含VK_FORMAT_FEATURE_STORAGE_IMAGE_ATOMIC_BIT
    6.如果一个VK_DESCRIPTOR_TYPE_STORAGE_TEXEL_BUFFER类型的 descriptor使用atomic operations作为该命令的结果进行访问，则storage texel buffer的format features必须包含VK_FORMAT_FEATURE_STORAGE_TEXEL_BUFFER_ATOMIC_BIT
    7.如果一个以VK_FILTER_CUBIC_EXT进行采样的VkImageView作为该命令的结果，则image view的format features必须包含VK_FORMAT_FEATURE_SAMPLED_IMAGE_FILTER_CUBIC_BIT_EXT
    8.如果VK_EXT_filter_cubic拓展没有开启，且有任何一个以VK_FILTER_CUBIC_EXT进行采样的VkImageView作为该命令的结果，则其VkImageViewType不能为VK_IMAGE_VIEW_TYPE_3D, VK_IMAGE_VIEW_TYPE_CUBE, 或者 VK_IMAGE_VIEW_TYPE_CUBE_ARRAY
    9.任何一个以VK_FILTER_CUBIC_EXT进行采样的作为该命令的结果的VkImageView，其VkImageViewType和format 必须支持cubic filtering，参见vkGetPhysicalDeviceImageFormatProperties2返回的VkFilterCubicImageViewImageFormatPropertiesEXT::filterCubic
    10.任何一个以VK_FILTER_CUBIC_EXT进行采样且reduction mode为VK_SAMPLER_REDUCTION_MODE_MIN 或者 VK_SAMPLER_REDUCTION_MODE_MAX之一的作为该命令的结果的VkImageView，其VkImageViewType和format 必须支持带minmax filtering的cubic filtering，参见vkGetPhysicalDeviceImageFormatProperties2返回的VkFilterCubicImageViewImageFormatPropertiesEXT::filterCubicMinmax
    11.如果cubicRangeClamp特性没有开启，则有任何一个以VK_FILTER_CUBIC_EXT进行采样VkImageView的作为该命令的结果，VkSamplerReductionModeCreateInfo::reductionMode不能为VK_SAMPLER_REDUCTION_MODE_WEIGHTED_AVERAGE_RANGECLAMP_QCOM
    12.任何一个以VkSamplerReductionModeCreateInfo::reductionMode为VK_SAMPLER_REDUCTION_MODE_WEIGHTED_AVERAGE_RANGECLAMP_QCOM进行采样的作为该命令的结果的VkImageView必须以VK_FILTER_CUBIC_EXT进行采样
    13.如果selectableCubicWeights特性没有开启，则有任何一个以VK_FILTER_CUBIC_EXT进行采样VkImageView的作为该命令的结果，VkSamplerCubicWeightsCreateInfoQCOM::cubicWeights必须为VK_CUBIC_FILTER_WEIGHTS_CATMULL_ROM_QCOM
    14.任何一个以VkImageCreateInfo::flags含VK_IMAGE_CREATE_CORNER_SAMPLED_BIT_NV创建的采样作为该命令结果的VkImage必须以VkSamplerAddressMode为VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE 进行采样
    15.对于任何作为storage image写入的VkImageView，且其OpTypeImage的format未知，则该image view的 format features必须包含VK_FORMAT_FEATURE_2_STORAGE_WRITE_WITHOUT_FORMAT_BIT
    16.对于任何作为storage image读取的VkImageView，且其OpTypeImage的format未知，则该image view的 format features必须包含VK_FORMAT_FEATURE_2_STORAGE_READ_WITHOUT_FORMAT_BIT
    17.对于任何作为storage storage texel buffer写入的VkBufferView，且其OpTypeImage的format未知，则该buffer view的 buffer features必须包含VK_FORMAT_FEATURE_2_STORAGE_WRITE_WITHOUT_FORMAT_BIT
    18.对于任何作为storage storage texel buffer读取的VkBufferView，且其OpTypeImage的format未知，则该buffer view的 buffer features必须包含VK_FORMAT_FEATURE_2_STORAGE_READ_WITHOUT_FORMAT_BIT
    19.对于每个在绑定的shader中静态使用的set n，一个descriptor set必须被绑定到相同pipeline bind point的set n处，该set n必须和创建当前VkPipeline的VkPipelineLayout或者和创建当前VkShaderEXT的VkDescriptorSetLayout 数组的set n处的布局兼容，参见Pipeline Layout Compatibility p1280
    20.对于每个在绑定的shader中静态使用的push constant，一个push constant值必须被绑定到相同pipeline bind point的对应处，该push constant必须和创建当前VkPipeline的VkPipelineLayout或者和创建当前VkShaderEXT的VkDescriptorSetLayout 数组中的对应处的布局兼容，参见Pipeline Layout Compatibility p1280
    21.如果maintenance4特性没有开启，则对于每个在绑定的shader中静态使用的push constant，一个push constant值必须被设置到相同pipeline bind point的对应处，该push constant必须和创建当前VkPipeline的VkPipelineLayout或者和创建当前VkShaderEXT的VkDescriptorSetLayout 数组中的对应处的布局兼容，参见Pipeline Layout Compatibility p1280
    22.每一个通过vkCmdBindDescriptorSets绑定的descriptor set的descriptors,如果是被不以VK_PIPELINE_CREATE_DESCRIPTOR_BUFFER_BIT_EXT创建的，且已经绑定到该命令使用的pipeline bind point的VkPipeline静态使用的，则这些descriptors必须是有效的，参见 descriptor validity p1328
    23.如果通过vkCmdBindDescriptorSets指定绑定到pipeline bind point的VkPipeline要使用的descriptors，则绑定的VkPipeline不能以VK_PIPELINE_CREATE_DESCRIPTOR_BUFFER_BIT_EXT创建
    24.在vkCmdSetDescriptorBufferOffsetsEXT中指定绑定的descriptor buffers的descriptors，则（1）如果绑定到pipeline bind point的该命令会使用的VkPipeline以VK_PIPELINE_CREATE_DESCRIPTOR_BUFFER_BIT_EXT创建，且这些descriptors是动态使用的，则这些descriptors必须是有效的
                                                                                          （2）如果绑定到pipeline bind point的对应stage的该命令会使用的VkShaderEXT，且这些descriptors是动态使用的，则这些descriptors必须是有效的
    25.在vkCmdSetDescriptorBufferOffsetsEXT中指定的descriptors在绑定到pipeline bind point的VkPipeline中使用，则VkPipeline必须以VK_PIPELINE_CREATE_DESCRIPTOR_BUFFER_BIT_EXT创建
    26.如果一个descriptor在以VK_PIPELINE_CREATE_DESCRIPTOR_BUFFER_BIT_EXT创建的VkPipeline中动态使用，则descriptor memory必须是驻留内存
    27.如果一个descriptor在以其VkDescriptorSetLayout以VK_DESCRIPTOR_SET_LAYOUT_CREATE_DESCRIPTOR_BUFFER_BIT_EXT创建的VkShaderEXT中动态使用，则descriptor memory必须是驻留内存
    28.如果shaderObject 特性没有开启，一个有效的pipeline必须绑定到这个命令使用的绑定到pipeline bind point上
    29.如果一个pipeline绑定到该命令使用的pipeline bind point上，则不能有任何动态state 设置命令设置任何该VkPipeline 中没有指定的动态 state
    30.如果一个VkPipeline绑定到该命令使用的pipeline bind point上 或者任何一个会访问一个使用unnormalized coordinates的VkSampler的 VkShaderEXT绑定到该命令使用的pipeline bind point上的pipeline的对应stage，则
                                                                                （1）在任何shader stage中，VkSampler不能用来采样任何类型为VK_IMAGE_VIEW_TYPE_3D, VK_IMAGE_VIEW_TYPE_CUBE, VK_IMAGE_VIEW_TYPE_1D_ARRAY, VK_IMAGE_VIEW_TYPE_2D_ARRAY 或者 VK_IMAGE_VIEW_TYPE_CUBE_ARRAY的VkImageView
                                                                                （2）在任何shader stage中，该VkSampler不能和任何带有名字中带有ImplicitLod，Dref 或者 Proj 的SPIR-V OpImageSample* 或者 OpImageSparseSample*指令一起使用
                                                                                （3）在任何shader stage中，该VkSampler不能和任何包含 LOD bias或者offset 值 的SPIR-V OpImageSample* or OpImageSparseSample*指令一起使用
    31.如果shaderObject开启，一个有效的pipeline必须绑定到该命令使用的pipeline bind point上或者一个有效的shader objects以及VK_NULL_HANDLE的组合必须绑定到该命令使用的pipeline bind point每一个支持的shader stage上
    32.如何绑定到该命令使用的pipeline bind point上的VkPipeline的任何stage会访问一个uniform buffer，且该stage对uniformBuffers不以启用VK_PIPELINE_ROBUSTNESS_BUFFER_BEHAVIOR_ROBUST_BUFFER_ACCESS_EXT或者VK_PIPELINE_ROBUSTNESS_BUFFER_BEHAVIOR_ROBUST_BUFFER_ACCESS_2_EXT 创建，且robustBufferAccess特性未开启，则该stage就不能访问绑定到相同pipeline bind point的descriptor set指定的buffer范围外的值
    33.如果robustBufferAccess特性未开启，且任何会访问uniform buffer的绑定到该命令使用的pipeline bind point上对应shader stage的VkShaderEXT，则其不能访问绑定到相同pipeline bind point的descriptor set指定的buffer范围外的值
    34.如何绑定到该命令使用的pipeline bind point上的VkPipeline的任何stage会访问一个storage buffer，且该stage对storageBuffers不以启用VK_PIPELINE_ROBUSTNESS_BUFFER_BEHAVIOR_ROBUST_BUFFER_ACCESS_EXT或者VK_PIPELINE_ROBUSTNESS_BUFFER_BEHAVIOR_ROBUST_BUFFER_ACCESS_2_EXT 创建，且robustBufferAccess特性未开启，则该stage就不能访问绑定到相同pipeline bind point的descriptor set指定的buffer范围外的值
    35.如果robustBufferAccess特性未开启，且任何会访问storage buffer的绑定到该命令使用的pipeline bind point上对应shader stage的VkShaderEXT，则其不能访问绑定到相同pipeline bind point的descriptor set指定的buffer范围外的值
    36.如果commandBuffer 是一个unprotected command buffer，且protectedNoFault 未支持，则任何绑定的shaders访问的资源不能是一个protected resource
    37.如果一个绑定的shader访问一个VkSampler 或者 VkImageView ，且启用了sampler Y′C BCR conversion，则只能使用OpImageSample* 或者 OpImageSparseSample*指令，不能使用ConstOffset 以及 Offset操作符
    38.如果一个VkImageView作为该命令的结果进行访问，则（1）image view 的viewType 必须匹配Instruction/Sampler/Image View Validation p1481中描述的OpTypeImage的Dim操作符
                                                      （2）image view 的foamrt的numeric type 必须匹配OpTypeImage的Sampled Type操作符
    39.如果一个VkImageView以一个不是VK_FORMAT_A8_UNORM_KHR的format创建且通过OpImageWrite作为该命令的结果进行访问，则该命令的Texel 操作符的Type必须至少包含和 image view的 format含有的components的个数相同的components个数
    40.如果一个VkImageView以VK_FORMAT_A8_UNORM_KHR的format创建且通过OpImageWrite作为该命令的结果进行访问，则该命令的Texel 操作符的Type必须包含4个components
    41.如果一个VkBufferView通过OpImageWrite作为该命令的结果进行访问，则该命令的Texel 操作符的Type必须至少包含和 buffer view的 format含有的components的个数相同的components个数
    42.如果一个带64-bit component的VkFormat的VkImageView作为该命令的结果进行访问，则该命令的OpTypeImage操作符的SampledType的宽度必须为64
    43.如果一个带少于64-bit component的VkFormat的VkImageView作为该命令的结果进行访问，则该命令的OpTypeImage操作符的SampledType的宽度必须为32
    44.如果一个带64-bit component的VkFormat的VkBufferView作为该命令的结果进行访问，则该命令的OpTypeImage操作符的SampledType的宽度必须为64位
    45.如果一个带少于64-bit component的VkFormat的VkBufferView作为该命令的结果进行访问，则该命令的OpTypeImage操作符的SampledType的宽度必须为32
    46.如果sparseImageInt64Atomics 特性未开启，则以VK_IMAGE_CREATE_SPARSE_RESIDENCY_BIT创建的VkImage对象不能被SampledType宽度为64位的OpTypeImage的atomic instructions访问
    47.如果sparseImageInt64Atomics 特性未开启，则以VK_BUFFER_CREATE_SPARSE_RESIDENCY_BIT创建的VkBuffer对象不能被SampledType宽度为64位的OpTypeImage的atomic instructions访问
    48.如果OpImageWeightedSampleQCOM用来采样一个作为该命令的结果的VkImageView，则该image view的format features必须包含VK_FORMAT_FEATURE_2_WEIGHT_SAMPLED_IMAGE_BIT_QCOM
    49.如果OpImageWeightedSampleQCOM用来采样一个作为该命令的结果的sample weight image的VkImageView，则该image view的format features必须包含VK_FORMAT_FEATURE_2_WEIGHT_IMAGE_BIT_QCOM
    50.如果OpImageBoxFilterQCOM用来采样一个作为该命令的结果的VkImageView，则该image view的format features必须包含VK_FORMAT_FEATURE_2_BOX_FILTER_SAMPLED_BIT_QCOM
    51.如果OpImageBlockMatchSSDQCOM，或者 OpImageBlockMatchSADQCOM用来读取一个作为该命令的结果的VkImageView，则（1）该image view的format features必须包含VK_FORMAT_FEATURE_2_BLOCK_MATCHING_BIT_QCOM
                                                                                                               （2）如果是读取的reference image，指定的reference coordinates不能在integer texel coordinate validation 时候失败
    52.如果OpImageWeightedSampleQCOM, OpImageBoxFilterQCOM, OpImageBlockMatchWindowSSDQCOM, OpImageBlockMatchWindowSADQCOM, OpImageBlockMatchGatherSSDQCOM,
                                                OpImageBlockMatchGatherSADQCOM, OpImageBlockMatchSSDQCOM, 或者 OpImageBlockMatchSADQCOM用来采样一个作为该命令的结果的VkImageView，则该VkSampler必须以VK_SAMPLER_CREATE_IMAGE_PROCESSING_BIT_QCOM创建
    53.如果任何除了OpImageWeightedSampleQCOM, OpImageBoxFilterQCOM, OpImageBlockMatchWindowSSDQCOM, OpImageBlockMatchWindowSADQCOM, OpImageBlockMatchGatherSSDQCOM, OpImageBlockMatchGatherSADQCOM, OpImageBlockMatchSSDQCOM, 或者 OpImageBlockMatchSADQCOM之外的指令使用VkSampler进行采样作为该命令的结果，则该sampler不能以VK_SAMPLER_CREATE_IMAGE_PROCESSING_BIT_QCOM 创建
    54.如果OpImageBlockMatchWindow*QCOM or OpImageBlockMatchGather*QCOM指令用来读取VkImageView作为该命令的结果，则（1）VkImageView的format features必须包含VK_FORMAT_FEATURE_2_BLOCK_MATCHING_BIT_QCOM
                                                                                                                  （2）VkImageView的format必须只含有一个component
    55.如果OpImageBlockMatchWindow*QCOM or OpImageBlockMatchGather*QCOM指令用来读取一个引用的image作为该命令的结果，则指定的 reference coordinates不能在integer texel coordinate validation 时候失败
    56.任何该命令执行的shader invocation必须已经终止
    57.如果有一个类型位为VK_DESCRIPTOR_TYPE_SAMPLE_WEIGHT_IMAGE_QCOM, VK_DESCRIPTOR_TYPE_BLOCK_MATCH_IMAGE_QCOM, VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE, VK_DESCRIPTOR_TYPE_STORAGE_IMAGE, 或者 VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT中任意一个的descriptor作为该命令的结果进行访问，则该descriptor所指的image subresource的layout必须和该descriptor被写入时的layout相同。
	58.如果commandBuffer 是一个protected command buffer，且protectedNoFault 未支持，则（1）任何绑定的shaders写访问的资源不能是一个unprotected resource
                                                                                      （2）pipeline绑定的pipeline stage中除了framebuffer-space 和compute stages之外的pipeline stage不能写入任何绑定的资源
    59.如果绑定到该命令使用的pipeline的任何shader stage使用了RayQueryKHR capability，则commandBuffer不能是一个protected command buffer
    60.groupCountX 必须小于等于VkPhysicalDeviceLimits::maxComputeWorkGroupCount[0]，groupCountY 必须小于等于VkPhysicalDeviceLimits::maxComputeWorkGroupCount[1]，groupCountZ 必须小于等于VkPhysicalDeviceLimits::maxComputeWorkGroupCount[2]

	*/


    VkDispatchIndirectCommand dispatchIndirectCommand{};
    dispatchIndirectCommand.x = 1;//为dispatch的local workgroups 的 X 维度的数量，必须小于等于VkPhysicalDeviceLimits::maxComputeWorkGroupCount[0]
    dispatchIndirectCommand.y = 1;//为dispatch的local workgroups 的 Y 维度的数量，必须小于等于VkPhysicalDeviceLimits::maxComputeWorkGroupCount[1]
    dispatchIndirectCommand.z = 1;//为dispatch的local workgroups 的 Z 维度的数量，必须小于等于VkPhysicalDeviceLimits::maxComputeWorkGroupCount[2]

    //记录一个间接的dispatch command    ， 参数buffer中以VkDispatchIndirectCommand进行组织
    vkCmdDispatchIndirect(commandBuffer, VkBuffer{/*假设这是一个有效的VkBuffer*/ }/*buffer,为包含dispatch parameters的buffer.*/, 0/*offset，为buffer中的参数的起始字节偏移量.*/);
    /*
    vkCmdDispatchIndirect有效用法:
    1.如果一个VkSampler以其magFilter或者minFilter等于VK_FILTER_LINEAR创建，则（1）如果reductionMode为VK_SAMPLER_REDUCTION_MODE_WEIGHTED_AVERAGE，如果用于采样一个VkImageView作为该命令的结果的compareEnable为VK_FALSE，则该image view的format features必须包含VK_FORMAT_FEATURE_SAMPLED_IMAGE_FILTER_LINEAR_BIT
                                                                             （2）如果reductionMode为VK_SAMPLER_REDUCTION_MODE_MIN 或者VK_SAMPLER_REDUCTION_MODE_MAX之一 用于采样一个VkImageView作为该命令的结果，则该image view的format features必须包含VK_FORMAT_FEATURE_SAMPLED_IMAGE_FILTER_MINMAX_BIT
    2.如果一个VkSampler以其mipmapMode 等于VK_SAMPLER_MIPMAP_MODE_LINEAR创建，则（1）如果reductionMode为VK_SAMPLER_REDUCTION_MODE_WEIGHTED_AVERAGE，如果用于采样一个VkImageView作为该命令的结果的compareEnable为VK_FALSE，则该image view的format features必须包含VK_FORMAT_FEATURE_SAMPLED_IMAGE_FILTER_LINEAR_BIT
                                                                             （2）如果reductionMode为VK_SAMPLER_REDUCTION_MODE_MIN 或者VK_SAMPLER_REDUCTION_MODE_MAX之一 用于采样一个VkImageView作为该命令的结果，则该image view的format features必须包含VK_FORMAT_FEATURE_SAMPLED_IMAGE_FILTER_MINMAX_BIT
    3.如果一个VkSampler以其unnormalizedCoordinates等于VK_TRUE用于采样一个VkImageView作为该命令的结果创建，则（1）该image view的levelCount以及layerCount必须为1
                                                                                                            （2）该image view的viewType必须为VK_IMAGE_VIEW_TYPE_1D 或者 VK_IMAGE_VIEW_TYPE_2D
    4.如果一个VkImageView的采样带depth comparison操作，则image view的format features必须包含VK_FORMAT_FEATURE_2_SAMPLED_IMAGE_DEPTH_COMPARISON_BIT
    5.如果一个VkImageView使用atomic operations作为该命令的结果进行访问，则image view的format features必须包含VK_FORMAT_FEATURE_STORAGE_IMAGE_ATOMIC_BIT
    6.如果一个VK_DESCRIPTOR_TYPE_STORAGE_TEXEL_BUFFER类型的 descriptor使用atomic operations作为该命令的结果进行访问，则storage texel buffer的format features必须包含VK_FORMAT_FEATURE_STORAGE_TEXEL_BUFFER_ATOMIC_BIT
    7.如果一个以VK_FILTER_CUBIC_EXT进行采样的VkImageView作为该命令的结果，则image view的format features必须包含VK_FORMAT_FEATURE_SAMPLED_IMAGE_FILTER_CUBIC_BIT_EXT
    8.如果VK_EXT_filter_cubic拓展没有开启，且有任何一个以VK_FILTER_CUBIC_EXT进行采样的VkImageView作为该命令的结果，则其VkImageViewType不能为VK_IMAGE_VIEW_TYPE_3D, VK_IMAGE_VIEW_TYPE_CUBE, 或者 VK_IMAGE_VIEW_TYPE_CUBE_ARRAY
    9.任何一个以VK_FILTER_CUBIC_EXT进行采样的作为该命令的结果的VkImageView，其VkImageViewType和format 必须支持cubic filtering，参见vkGetPhysicalDeviceImageFormatProperties2返回的VkFilterCubicImageViewImageFormatPropertiesEXT::filterCubic
    10.任何一个以VK_FILTER_CUBIC_EXT进行采样且reduction mode为VK_SAMPLER_REDUCTION_MODE_MIN 或者 VK_SAMPLER_REDUCTION_MODE_MAX之一的作为该命令的结果的VkImageView，其VkImageViewType和format 必须支持带minmax filtering的cubic filtering，参见vkGetPhysicalDeviceImageFormatProperties2返回的VkFilterCubicImageViewImageFormatPropertiesEXT::filterCubicMinmax
    11.如果cubicRangeClamp特性没有开启，则有任何一个以VK_FILTER_CUBIC_EXT进行采样VkImageView的作为该命令的结果，VkSamplerReductionModeCreateInfo::reductionMode不能为VK_SAMPLER_REDUCTION_MODE_WEIGHTED_AVERAGE_RANGECLAMP_QCOM
    12.任何一个以VkSamplerReductionModeCreateInfo::reductionMode为VK_SAMPLER_REDUCTION_MODE_WEIGHTED_AVERAGE_RANGECLAMP_QCOM进行采样的作为该命令的结果的VkImageView必须以VK_FILTER_CUBIC_EXT进行采样
    13.如果selectableCubicWeights特性没有开启，则有任何一个以VK_FILTER_CUBIC_EXT进行采样VkImageView的作为该命令的结果，VkSamplerCubicWeightsCreateInfoQCOM::cubicWeights必须为VK_CUBIC_FILTER_WEIGHTS_CATMULL_ROM_QCOM
    14.任何一个以VkImageCreateInfo::flags含VK_IMAGE_CREATE_CORNER_SAMPLED_BIT_NV创建的采样作为该命令结果的VkImage必须以VkSamplerAddressMode为VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE 进行采样
    15.对于任何作为storage image写入的VkImageView，且其OpTypeImage的format未知，则该image view的 format features必须包含VK_FORMAT_FEATURE_2_STORAGE_WRITE_WITHOUT_FORMAT_BIT
    16.对于任何作为storage image读取的VkImageView，且其OpTypeImage的format未知，则该image view的 format features必须包含VK_FORMAT_FEATURE_2_STORAGE_READ_WITHOUT_FORMAT_BIT
    17.对于任何作为storage storage texel buffer写入的VkBufferView，且其OpTypeImage的format未知，则该buffer view的 buffer features必须包含VK_FORMAT_FEATURE_2_STORAGE_WRITE_WITHOUT_FORMAT_BIT
    18.对于任何作为storage storage texel buffer读取的VkBufferView，且其OpTypeImage的format未知，则该buffer view的 buffer features必须包含VK_FORMAT_FEATURE_2_STORAGE_READ_WITHOUT_FORMAT_BIT
    19.对于每个在绑定的shader中静态使用的set n，一个descriptor set必须被绑定到相同pipeline bind point的set n处，该set n必须和创建当前VkPipeline的VkPipelineLayout或者和创建当前VkShaderEXT的VkDescriptorSetLayout 数组的set n处的布局兼容，参见Pipeline Layout Compatibility p1280
    20.对于每个在绑定的shader中静态使用的push constant，一个push constant值必须被绑定到相同pipeline bind point的对应处，该push constant必须和创建当前VkPipeline的VkPipelineLayout或者和创建当前VkShaderEXT的VkDescriptorSetLayout 数组中的对应处的布局兼容，参见Pipeline Layout Compatibility p1280
    21.如果maintenance4特性没有开启，则对于每个在绑定的shader中静态使用的push constant，一个push constant值必须被设置到相同pipeline bind point的对应处，该push constant必须和创建当前VkPipeline的VkPipelineLayout或者和创建当前VkShaderEXT的VkDescriptorSetLayout 数组中的对应处的布局兼容，参见Pipeline Layout Compatibility p1280
    22.每一个通过vkCmdBindDescriptorSets绑定的descriptor set的descriptors,如果是被不以VK_PIPELINE_CREATE_DESCRIPTOR_BUFFER_BIT_EXT创建的，且已经绑定到该命令使用的pipeline bind point的VkPipeline静态使用的，则这些descriptors必须是有效的，参见 descriptor validity p1328
    23.如果通过vkCmdBindDescriptorSets指定绑定到pipeline bind point的VkPipeline要使用的descriptors，则绑定的VkPipeline不能以VK_PIPELINE_CREATE_DESCRIPTOR_BUFFER_BIT_EXT创建
    24.在vkCmdSetDescriptorBufferOffsetsEXT中指定绑定的descriptor buffers的descriptors，则（1）如果绑定到pipeline bind point的该命令会使用的VkPipeline以VK_PIPELINE_CREATE_DESCRIPTOR_BUFFER_BIT_EXT创建，且这些descriptors是动态使用的，则这些descriptors必须是有效的
                                                                                          （2）如果绑定到pipeline bind point的对应stage的该命令会使用的VkShaderEXT，且这些descriptors是动态使用的，则这些descriptors必须是有效的
    25.在vkCmdSetDescriptorBufferOffsetsEXT中指定的descriptors在绑定到pipeline bind point的VkPipeline中使用，则VkPipeline必须以VK_PIPELINE_CREATE_DESCRIPTOR_BUFFER_BIT_EXT创建
    26.如果一个descriptor在以VK_PIPELINE_CREATE_DESCRIPTOR_BUFFER_BIT_EXT创建的VkPipeline中动态使用，则descriptor memory必须是驻留内存
    27.如果一个descriptor在以其VkDescriptorSetLayout以VK_DESCRIPTOR_SET_LAYOUT_CREATE_DESCRIPTOR_BUFFER_BIT_EXT创建的VkShaderEXT中动态使用，则descriptor memory必须是驻留内存
    28.如果shaderObject 特性没有开启，一个有效的pipeline必须绑定到这个命令使用的绑定到pipeline bind point上
    29.如果一个pipeline绑定到该命令使用的pipeline bind point上，则不能有任何动态state 设置命令设置任何该VkPipeline 中没有指定的动态 state
    30.如果一个VkPipeline绑定到该命令使用的pipeline bind point上 或者任何一个会访问一个使用unnormalized coordinates的VkSampler的 VkShaderEXT绑定到该命令使用的pipeline bind point上的pipeline的对应stage，则
                                                                                （1）在任何shader stage中，VkSampler不能用来采样任何类型为VK_IMAGE_VIEW_TYPE_3D, VK_IMAGE_VIEW_TYPE_CUBE, VK_IMAGE_VIEW_TYPE_1D_ARRAY, VK_IMAGE_VIEW_TYPE_2D_ARRAY 或者 VK_IMAGE_VIEW_TYPE_CUBE_ARRAY的VkImageView
                                                                                （2）在任何shader stage中，该VkSampler不能和任何带有名字中带有ImplicitLod，Dref 或者 Proj 的SPIR-V OpImageSample* 或者 OpImageSparseSample*指令一起使用
                                                                                （3）在任何shader stage中，该VkSampler不能和任何包含 LOD bias或者offset 值 的SPIR-V OpImageSample* or OpImageSparseSample*指令一起使用
    31.如果shaderObject开启，一个有效的pipeline必须绑定到该命令使用的pipeline bind point上或者一个有效的shader objects以及VK_NULL_HANDLE的组合必须绑定到该命令使用的pipeline bind point每一个支持的shader stage上
    32.如何绑定到该命令使用的pipeline bind point上的VkPipeline的任何stage会访问一个uniform buffer，且该stage对uniformBuffers不以启用VK_PIPELINE_ROBUSTNESS_BUFFER_BEHAVIOR_ROBUST_BUFFER_ACCESS_EXT或者VK_PIPELINE_ROBUSTNESS_BUFFER_BEHAVIOR_ROBUST_BUFFER_ACCESS_2_EXT 创建，且robustBufferAccess特性未开启，则该stage就不能访问绑定到相同pipeline bind point的descriptor set指定的buffer范围外的值
    33.如果robustBufferAccess特性未开启，且任何会访问uniform buffer的绑定到该命令使用的pipeline bind point上对应shader stage的VkShaderEXT，则其不能访问绑定到相同pipeline bind point的descriptor set指定的buffer范围外的值
    34.如何绑定到该命令使用的pipeline bind point上的VkPipeline的任何stage会访问一个storage buffer，且该stage对storageBuffers不以启用VK_PIPELINE_ROBUSTNESS_BUFFER_BEHAVIOR_ROBUST_BUFFER_ACCESS_EXT或者VK_PIPELINE_ROBUSTNESS_BUFFER_BEHAVIOR_ROBUST_BUFFER_ACCESS_2_EXT 创建，且robustBufferAccess特性未开启，则该stage就不能访问绑定到相同pipeline bind point的descriptor set指定的buffer范围外的值
    35.如果robustBufferAccess特性未开启，且任何会访问storage buffer的绑定到该命令使用的pipeline bind point上对应shader stage的VkShaderEXT，则其不能访问绑定到相同pipeline bind point的descriptor set指定的buffer范围外的值
    36.如果commandBuffer 是一个unprotected command buffer，且protectedNoFault 未支持，则任何绑定的shaders访问的资源不能是一个protected resource
    37.如果一个绑定的shader访问一个VkSampler 或者 VkImageView ，且启用了sampler Y′C BCR conversion，则只能使用OpImageSample* 或者 OpImageSparseSample*指令，不能使用ConstOffset 以及 Offset操作符
    38.如果一个VkImageView作为该命令的结果进行访问，则（1）image view 的viewType 必须匹配Instruction/Sampler/Image View Validation p1481中描述的OpTypeImage的Dim操作符
                                                      （2）image view 的foamrt的numeric type 必须匹配OpTypeImage的Sampled Type操作符
    39.如果一个VkImageView以一个不是VK_FORMAT_A8_UNORM_KHR的format创建且通过OpImageWrite作为该命令的结果进行访问，则该命令的Texel 操作符的Type必须至少包含和 image view的 format含有的components的个数相同的components个数
    40.如果一个VkImageView以VK_FORMAT_A8_UNORM_KHR的format创建且通过OpImageWrite作为该命令的结果进行访问，则该命令的Texel 操作符的Type必须包含4个components
    41.如果一个VkBufferView通过OpImageWrite作为该命令的结果进行访问，则该命令的Texel 操作符的Type必须至少包含和 buffer view的 format含有的components的个数相同的components个数
    42.如果一个带64-bit component的VkFormat的VkImageView作为该命令的结果进行访问，则该命令的OpTypeImage操作符的SampledType的宽度必须为64
    43.如果一个带少于64-bit component的VkFormat的VkImageView作为该命令的结果进行访问，则该命令的OpTypeImage操作符的SampledType的宽度必须为32
    44.如果一个带64-bit component的VkFormat的VkBufferView作为该命令的结果进行访问，则该命令的OpTypeImage操作符的SampledType的宽度必须为64位
    45.如果一个带少于64-bit component的VkFormat的VkBufferView作为该命令的结果进行访问，则该命令的OpTypeImage操作符的SampledType的宽度必须为32
    46.如果sparseImageInt64Atomics 特性未开启，则以VK_IMAGE_CREATE_SPARSE_RESIDENCY_BIT创建的VkImage对象不能被SampledType宽度为64位的OpTypeImage的atomic instructions访问
    47.如果sparseImageInt64Atomics 特性未开启，则以VK_BUFFER_CREATE_SPARSE_RESIDENCY_BIT创建的VkBuffer对象不能被SampledType宽度为64位的OpTypeImage的atomic instructions访问
    48.如果OpImageWeightedSampleQCOM用来采样一个作为该命令的结果的VkImageView，则该image view的format features必须包含VK_FORMAT_FEATURE_2_WEIGHT_SAMPLED_IMAGE_BIT_QCOM
    49.如果OpImageWeightedSampleQCOM用来采样一个作为该命令的结果的sample weight image的VkImageView，则该image view的format features必须包含VK_FORMAT_FEATURE_2_WEIGHT_IMAGE_BIT_QCOM
    50.如果OpImageBoxFilterQCOM用来采样一个作为该命令的结果的VkImageView，则该image view的format features必须包含VK_FORMAT_FEATURE_2_BOX_FILTER_SAMPLED_BIT_QCOM
    51.如果OpImageBlockMatchSSDQCOM，或者 OpImageBlockMatchSADQCOM用来读取一个作为该命令的结果的VkImageView，则（1）该image view的format features必须包含VK_FORMAT_FEATURE_2_BLOCK_MATCHING_BIT_QCOM
                                                                                                               （2）如果是读取的reference image，指定的reference coordinates不能在integer texel coordinate validation 时候失败
    52.如果OpImageWeightedSampleQCOM, OpImageBoxFilterQCOM, OpImageBlockMatchWindowSSDQCOM, OpImageBlockMatchWindowSADQCOM, OpImageBlockMatchGatherSSDQCOM,
                                                OpImageBlockMatchGatherSADQCOM, OpImageBlockMatchSSDQCOM, 或者 OpImageBlockMatchSADQCOM用来采样一个作为该命令的结果的VkImageView，则该VkSampler必须以VK_SAMPLER_CREATE_IMAGE_PROCESSING_BIT_QCOM创建
    53.如果任何除了OpImageWeightedSampleQCOM, OpImageBoxFilterQCOM, OpImageBlockMatchWindowSSDQCOM, OpImageBlockMatchWindowSADQCOM, OpImageBlockMatchGatherSSDQCOM, OpImageBlockMatchGatherSADQCOM, OpImageBlockMatchSSDQCOM, 或者 OpImageBlockMatchSADQCOM之外的指令使用VkSampler进行采样作为该命令的结果，则该sampler不能以VK_SAMPLER_CREATE_IMAGE_PROCESSING_BIT_QCOM 创建
    54.如果OpImageBlockMatchWindow*QCOM or OpImageBlockMatchGather*QCOM指令用来读取VkImageView作为该命令的结果，则（1）VkImageView的format features必须包含VK_FORMAT_FEATURE_2_BLOCK_MATCHING_BIT_QCOM
                                                                                                                  （2）VkImageView的format必须只含有一个component
    55.如果OpImageBlockMatchWindow*QCOM or OpImageBlockMatchGather*QCOM指令用来读取一个引用的image作为该命令的结果，则指定的 reference coordinates不能在integer texel coordinate validation 时候失败
    56.任何该命令执行的shader invocation必须已经终止
    57.如果有一个类型位为VK_DESCRIPTOR_TYPE_SAMPLE_WEIGHT_IMAGE_QCOM, VK_DESCRIPTOR_TYPE_BLOCK_MATCH_IMAGE_QCOM, VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE, VK_DESCRIPTOR_TYPE_STORAGE_IMAGE, 或者 VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT中任意一个的descriptor作为该命令的结果进行访问，则该descriptor所指的image subresource的layout必须和该descriptor被写入时的layout相同。
    58.如果buffer是non-sparse的，则其必须绑定到完全的连续的单独的VkDeviceMemory上
    59.buffer必须以VK_BUFFER_USAGE_INDIRECT_BUFFER_BIT 创建
    60.offset必须是4的倍数
    61.commandBuffer不能是一个protected command buffer
    62.VkDispatchIndirectCommand的大小加上offset必须小于等于buffer的大小
    
    */



    //记录一个WorkgroupId中各个分量不以0为基础值的dispatch command，   等同于vkCmdDispatchBaseKHR  ,该命令会组装一个含有groupCountX × groupCountY × groupCountZ个local work groups的 global work group ，其 WorkgroupId每个分量的的范围为[[baseGroup*, baseGroup * +groupCount*), vkCmdDispatch 等同于 vkCmdDispatchBase(0, 0, 0, groupCountX, groupCountY, groupCountZ).
    vkCmdDispatchBase(commandBuffer, 1/* baseGroupX,为WorkgroupId的X 分量值的起始值.*/, 1/* baseGroupY,为WorkgroupId的Y 分量值的起始值.*/, 1/* baseGroupZ,为WorkgroupId的Z 分量值的起始值.*/,
        1/*groupCountX,为dispatch的local workgroups 的 X 维度的数量.*/, 1/*groupCountY,为dispatch的local workgroups 的 Y 维度的数量.*/, 1/*groupCountZ,为dispatch的local workgroups 的 Z 维度的数量.*/);
    /*
    vkCmdDispatchBase有效用法:
    1.如果一个VkSampler以其magFilter或者minFilter等于VK_FILTER_LINEAR创建，则（1）如果reductionMode为VK_SAMPLER_REDUCTION_MODE_WEIGHTED_AVERAGE，如果用于采样一个VkImageView作为该命令的结果的compareEnable为VK_FALSE，则该image view的format features必须包含VK_FORMAT_FEATURE_SAMPLED_IMAGE_FILTER_LINEAR_BIT
                                                                             （2）如果reductionMode为VK_SAMPLER_REDUCTION_MODE_MIN 或者VK_SAMPLER_REDUCTION_MODE_MAX之一 用于采样一个VkImageView作为该命令的结果，则该image view的format features必须包含VK_FORMAT_FEATURE_SAMPLED_IMAGE_FILTER_MINMAX_BIT
    2.如果一个VkSampler以其mipmapMode 等于VK_SAMPLER_MIPMAP_MODE_LINEAR创建，则（1）如果reductionMode为VK_SAMPLER_REDUCTION_MODE_WEIGHTED_AVERAGE，如果用于采样一个VkImageView作为该命令的结果的compareEnable为VK_FALSE，则该image view的format features必须包含VK_FORMAT_FEATURE_SAMPLED_IMAGE_FILTER_LINEAR_BIT
                                                                             （2）如果reductionMode为VK_SAMPLER_REDUCTION_MODE_MIN 或者VK_SAMPLER_REDUCTION_MODE_MAX之一 用于采样一个VkImageView作为该命令的结果，则该image view的format features必须包含VK_FORMAT_FEATURE_SAMPLED_IMAGE_FILTER_MINMAX_BIT
    3.如果一个VkSampler以其unnormalizedCoordinates等于VK_TRUE用于采样一个VkImageView作为该命令的结果创建，则（1）该image view的levelCount以及layerCount必须为1
                                                                                                            （2）该image view的viewType必须为VK_IMAGE_VIEW_TYPE_1D 或者 VK_IMAGE_VIEW_TYPE_2D
    4.如果一个VkImageView的采样带depth comparison操作，则image view的format features必须包含VK_FORMAT_FEATURE_2_SAMPLED_IMAGE_DEPTH_COMPARISON_BIT
    5.如果一个VkImageView使用atomic operations作为该命令的结果进行访问，则image view的format features必须包含VK_FORMAT_FEATURE_STORAGE_IMAGE_ATOMIC_BIT
    6.如果一个VK_DESCRIPTOR_TYPE_STORAGE_TEXEL_BUFFER类型的 descriptor使用atomic operations作为该命令的结果进行访问，则storage texel buffer的format features必须包含VK_FORMAT_FEATURE_STORAGE_TEXEL_BUFFER_ATOMIC_BIT
    7.如果一个以VK_FILTER_CUBIC_EXT进行采样的VkImageView作为该命令的结果，则image view的format features必须包含VK_FORMAT_FEATURE_SAMPLED_IMAGE_FILTER_CUBIC_BIT_EXT
    8.如果VK_EXT_filter_cubic拓展没有开启，且有任何一个以VK_FILTER_CUBIC_EXT进行采样的VkImageView作为该命令的结果，则其VkImageViewType不能为VK_IMAGE_VIEW_TYPE_3D, VK_IMAGE_VIEW_TYPE_CUBE, 或者 VK_IMAGE_VIEW_TYPE_CUBE_ARRAY
    9.任何一个以VK_FILTER_CUBIC_EXT进行采样的作为该命令的结果的VkImageView，其VkImageViewType和format 必须支持cubic filtering，参见vkGetPhysicalDeviceImageFormatProperties2返回的VkFilterCubicImageViewImageFormatPropertiesEXT::filterCubic
    10.任何一个以VK_FILTER_CUBIC_EXT进行采样且reduction mode为VK_SAMPLER_REDUCTION_MODE_MIN 或者 VK_SAMPLER_REDUCTION_MODE_MAX之一的作为该命令的结果的VkImageView，其VkImageViewType和format 必须支持带minmax filtering的cubic filtering，参见vkGetPhysicalDeviceImageFormatProperties2返回的VkFilterCubicImageViewImageFormatPropertiesEXT::filterCubicMinmax
    11.如果cubicRangeClamp特性没有开启，则有任何一个以VK_FILTER_CUBIC_EXT进行采样VkImageView的作为该命令的结果，VkSamplerReductionModeCreateInfo::reductionMode不能为VK_SAMPLER_REDUCTION_MODE_WEIGHTED_AVERAGE_RANGECLAMP_QCOM
    12.任何一个以VkSamplerReductionModeCreateInfo::reductionMode为VK_SAMPLER_REDUCTION_MODE_WEIGHTED_AVERAGE_RANGECLAMP_QCOM进行采样的作为该命令的结果的VkImageView必须以VK_FILTER_CUBIC_EXT进行采样
    13.如果selectableCubicWeights特性没有开启，则有任何一个以VK_FILTER_CUBIC_EXT进行采样VkImageView的作为该命令的结果，VkSamplerCubicWeightsCreateInfoQCOM::cubicWeights必须为VK_CUBIC_FILTER_WEIGHTS_CATMULL_ROM_QCOM
    14.任何一个以VkImageCreateInfo::flags含VK_IMAGE_CREATE_CORNER_SAMPLED_BIT_NV创建的采样作为该命令结果的VkImage必须以VkSamplerAddressMode为VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE 进行采样
    15.对于任何作为storage image写入的VkImageView，且其OpTypeImage的format未知，则该image view的 format features必须包含VK_FORMAT_FEATURE_2_STORAGE_WRITE_WITHOUT_FORMAT_BIT
    16.对于任何作为storage image读取的VkImageView，且其OpTypeImage的format未知，则该image view的 format features必须包含VK_FORMAT_FEATURE_2_STORAGE_READ_WITHOUT_FORMAT_BIT
    17.对于任何作为storage storage texel buffer写入的VkBufferView，且其OpTypeImage的format未知，则该buffer view的 buffer features必须包含VK_FORMAT_FEATURE_2_STORAGE_WRITE_WITHOUT_FORMAT_BIT
    18.对于任何作为storage storage texel buffer读取的VkBufferView，且其OpTypeImage的format未知，则该buffer view的 buffer features必须包含VK_FORMAT_FEATURE_2_STORAGE_READ_WITHOUT_FORMAT_BIT
    19.对于每个在绑定的shader中静态使用的set n，一个descriptor set必须被绑定到相同pipeline bind point的set n处，该set n必须和创建当前VkPipeline的VkPipelineLayout或者和创建当前VkShaderEXT的VkDescriptorSetLayout 数组的set n处的布局兼容，参见Pipeline Layout Compatibility p1280
    20.对于每个在绑定的shader中静态使用的push constant，一个push constant值必须被绑定到相同pipeline bind point的对应处，该push constant必须和创建当前VkPipeline的VkPipelineLayout或者和创建当前VkShaderEXT的VkDescriptorSetLayout 数组中的对应处的布局兼容，参见Pipeline Layout Compatibility p1280
    21.如果maintenance4特性没有开启，则对于每个在绑定的shader中静态使用的push constant，一个push constant值必须被设置到相同pipeline bind point的对应处，该push constant必须和创建当前VkPipeline的VkPipelineLayout或者和创建当前VkShaderEXT的VkDescriptorSetLayout 数组中的对应处的布局兼容，参见Pipeline Layout Compatibility p1280
    22.每一个通过vkCmdBindDescriptorSets绑定的descriptor set的descriptors,如果是被不以VK_PIPELINE_CREATE_DESCRIPTOR_BUFFER_BIT_EXT创建的，且已经绑定到该命令使用的pipeline bind point的VkPipeline静态使用的，则这些descriptors必须是有效的，参见 descriptor validity p1328
    23.如果通过vkCmdBindDescriptorSets指定绑定到pipeline bind point的VkPipeline要使用的descriptors，则绑定的VkPipeline不能以VK_PIPELINE_CREATE_DESCRIPTOR_BUFFER_BIT_EXT创建
    24.在vkCmdSetDescriptorBufferOffsetsEXT中指定绑定的descriptor buffers的descriptors，则（1）如果绑定到pipeline bind point的该命令会使用的VkPipeline以VK_PIPELINE_CREATE_DESCRIPTOR_BUFFER_BIT_EXT创建，且这些descriptors是动态使用的，则这些descriptors必须是有效的
                                                                                          （2）如果绑定到pipeline bind point的对应stage的该命令会使用的VkShaderEXT，且这些descriptors是动态使用的，则这些descriptors必须是有效的
    25.在vkCmdSetDescriptorBufferOffsetsEXT中指定的descriptors在绑定到pipeline bind point的VkPipeline中使用，则VkPipeline必须以VK_PIPELINE_CREATE_DESCRIPTOR_BUFFER_BIT_EXT创建
    26.如果一个descriptor在以VK_PIPELINE_CREATE_DESCRIPTOR_BUFFER_BIT_EXT创建的VkPipeline中动态使用，则descriptor memory必须是驻留内存
    27.如果一个descriptor在以其VkDescriptorSetLayout以VK_DESCRIPTOR_SET_LAYOUT_CREATE_DESCRIPTOR_BUFFER_BIT_EXT创建的VkShaderEXT中动态使用，则descriptor memory必须是驻留内存
    28.如果shaderObject 特性没有开启，一个有效的pipeline必须绑定到这个命令使用的绑定到pipeline bind point上
    29.如果一个pipeline绑定到该命令使用的pipeline bind point上，则不能有任何动态state 设置命令设置任何该VkPipeline 中没有指定的动态 state
    30.如果一个VkPipeline绑定到该命令使用的pipeline bind point上 或者任何一个会访问一个使用unnormalized coordinates的VkSampler的 VkShaderEXT绑定到该命令使用的pipeline bind point上的pipeline的对应stage，则
                                                                                （1）在任何shader stage中，VkSampler不能用来采样任何类型为VK_IMAGE_VIEW_TYPE_3D, VK_IMAGE_VIEW_TYPE_CUBE, VK_IMAGE_VIEW_TYPE_1D_ARRAY, VK_IMAGE_VIEW_TYPE_2D_ARRAY 或者 VK_IMAGE_VIEW_TYPE_CUBE_ARRAY的VkImageView
                                                                                （2）在任何shader stage中，该VkSampler不能和任何带有名字中带有ImplicitLod，Dref 或者 Proj 的SPIR-V OpImageSample* 或者 OpImageSparseSample*指令一起使用
                                                                                （3）在任何shader stage中，该VkSampler不能和任何包含 LOD bias或者offset 值 的SPIR-V OpImageSample* or OpImageSparseSample*指令一起使用
    31.如果shaderObject开启，一个有效的pipeline必须绑定到该命令使用的pipeline bind point上或者一个有效的shader objects以及VK_NULL_HANDLE的组合必须绑定到该命令使用的pipeline bind point每一个支持的shader stage上
    32.如何绑定到该命令使用的pipeline bind point上的VkPipeline的任何stage会访问一个uniform buffer，且该stage对uniformBuffers不以启用VK_PIPELINE_ROBUSTNESS_BUFFER_BEHAVIOR_ROBUST_BUFFER_ACCESS_EXT或者VK_PIPELINE_ROBUSTNESS_BUFFER_BEHAVIOR_ROBUST_BUFFER_ACCESS_2_EXT 创建，且robustBufferAccess特性未开启，则该stage就不能访问绑定到相同pipeline bind point的descriptor set指定的buffer范围外的值
    33.如果robustBufferAccess特性未开启，且任何会访问uniform buffer的绑定到该命令使用的pipeline bind point上对应shader stage的VkShaderEXT，则其不能访问绑定到相同pipeline bind point的descriptor set指定的buffer范围外的值
    34.如何绑定到该命令使用的pipeline bind point上的VkPipeline的任何stage会访问一个storage buffer，且该stage对storageBuffers不以启用VK_PIPELINE_ROBUSTNESS_BUFFER_BEHAVIOR_ROBUST_BUFFER_ACCESS_EXT或者VK_PIPELINE_ROBUSTNESS_BUFFER_BEHAVIOR_ROBUST_BUFFER_ACCESS_2_EXT 创建，且robustBufferAccess特性未开启，则该stage就不能访问绑定到相同pipeline bind point的descriptor set指定的buffer范围外的值
    35.如果robustBufferAccess特性未开启，且任何会访问storage buffer的绑定到该命令使用的pipeline bind point上对应shader stage的VkShaderEXT，则其不能访问绑定到相同pipeline bind point的descriptor set指定的buffer范围外的值
    36.如果commandBuffer 是一个unprotected command buffer，且protectedNoFault 未支持，则任何绑定的shaders访问的资源不能是一个protected resource
    37.如果一个绑定的shader访问一个VkSampler 或者 VkImageView ，且启用了sampler Y′C BCR conversion，则只能使用OpImageSample* 或者 OpImageSparseSample*指令，不能使用ConstOffset 以及 Offset操作符
    38.如果一个VkImageView作为该命令的结果进行访问，则（1）image view 的viewType 必须匹配Instruction/Sampler/Image View Validation p1481中描述的OpTypeImage的Dim操作符
                                                      （2）image view 的foamrt的numeric type 必须匹配OpTypeImage的Sampled Type操作符
    39.如果一个VkImageView以一个不是VK_FORMAT_A8_UNORM_KHR的format创建且通过OpImageWrite作为该命令的结果进行访问，则该命令的Texel 操作符的Type必须至少包含和 image view的 format含有的components的个数相同的components个数
    40.如果一个VkImageView以VK_FORMAT_A8_UNORM_KHR的format创建且通过OpImageWrite作为该命令的结果进行访问，则该命令的Texel 操作符的Type必须包含4个components
    41.如果一个VkBufferView通过OpImageWrite作为该命令的结果进行访问，则该命令的Texel 操作符的Type必须至少包含和 buffer view的 format含有的components的个数相同的components个数
    42.如果一个带64-bit component的VkFormat的VkImageView作为该命令的结果进行访问，则该命令的OpTypeImage操作符的SampledType的宽度必须为64
    43.如果一个带少于64-bit component的VkFormat的VkImageView作为该命令的结果进行访问，则该命令的OpTypeImage操作符的SampledType的宽度必须为32
    44.如果一个带64-bit component的VkFormat的VkBufferView作为该命令的结果进行访问，则该命令的OpTypeImage操作符的SampledType的宽度必须为64位
    45.如果一个带少于64-bit component的VkFormat的VkBufferView作为该命令的结果进行访问，则该命令的OpTypeImage操作符的SampledType的宽度必须为32
    46.如果sparseImageInt64Atomics 特性未开启，则以VK_IMAGE_CREATE_SPARSE_RESIDENCY_BIT创建的VkImage对象不能被SampledType宽度为64位的OpTypeImage的atomic instructions访问
    47.如果sparseImageInt64Atomics 特性未开启，则以VK_BUFFER_CREATE_SPARSE_RESIDENCY_BIT创建的VkBuffer对象不能被SampledType宽度为64位的OpTypeImage的atomic instructions访问
    48.如果OpImageWeightedSampleQCOM用来采样一个作为该命令的结果的VkImageView，则该image view的format features必须包含VK_FORMAT_FEATURE_2_WEIGHT_SAMPLED_IMAGE_BIT_QCOM
    49.如果OpImageWeightedSampleQCOM用来采样一个作为该命令的结果的sample weight image的VkImageView，则该image view的format features必须包含VK_FORMAT_FEATURE_2_WEIGHT_IMAGE_BIT_QCOM
    50.如果OpImageBoxFilterQCOM用来采样一个作为该命令的结果的VkImageView，则该image view的format features必须包含VK_FORMAT_FEATURE_2_BOX_FILTER_SAMPLED_BIT_QCOM
    51.如果OpImageBlockMatchSSDQCOM，或者 OpImageBlockMatchSADQCOM用来读取一个作为该命令的结果的VkImageView，则（1）该image view的format features必须包含VK_FORMAT_FEATURE_2_BLOCK_MATCHING_BIT_QCOM
                                                                                                               （2）如果是读取的reference image，指定的reference coordinates不能在integer texel coordinate validation 时候失败
    52.如果OpImageWeightedSampleQCOM, OpImageBoxFilterQCOM, OpImageBlockMatchWindowSSDQCOM, OpImageBlockMatchWindowSADQCOM, OpImageBlockMatchGatherSSDQCOM,
                                                OpImageBlockMatchGatherSADQCOM, OpImageBlockMatchSSDQCOM, 或者 OpImageBlockMatchSADQCOM用来采样一个作为该命令的结果的VkImageView，则该VkSampler必须以VK_SAMPLER_CREATE_IMAGE_PROCESSING_BIT_QCOM创建
    53.如果任何除了OpImageWeightedSampleQCOM, OpImageBoxFilterQCOM, OpImageBlockMatchWindowSSDQCOM, OpImageBlockMatchWindowSADQCOM, OpImageBlockMatchGatherSSDQCOM, OpImageBlockMatchGatherSADQCOM, OpImageBlockMatchSSDQCOM, 或者 OpImageBlockMatchSADQCOM之外的指令使用VkSampler进行采样作为该命令的结果，则该sampler不能以VK_SAMPLER_CREATE_IMAGE_PROCESSING_BIT_QCOM 创建
    54.如果OpImageBlockMatchWindow*QCOM or OpImageBlockMatchGather*QCOM指令用来读取VkImageView作为该命令的结果，则（1）VkImageView的format features必须包含VK_FORMAT_FEATURE_2_BLOCK_MATCHING_BIT_QCOM
                                                                                                                  （2）VkImageView的format必须只含有一个component
    55.如果OpImageBlockMatchWindow*QCOM or OpImageBlockMatchGather*QCOM指令用来读取一个引用的image作为该命令的结果，则指定的 reference coordinates不能在integer texel coordinate validation 时候失败
    56.任何该命令执行的shader invocation必须已经终止
    57.如果有一个类型位为VK_DESCRIPTOR_TYPE_SAMPLE_WEIGHT_IMAGE_QCOM, VK_DESCRIPTOR_TYPE_BLOCK_MATCH_IMAGE_QCOM, VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE, VK_DESCRIPTOR_TYPE_STORAGE_IMAGE, 或者 VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT中任意一个的descriptor作为该命令的结果进行访问，则该descriptor所指的image subresource的layout必须和该descriptor被写入时的layout相同。
    58.如果commandBuffer 是一个protected command buffer，且protectedNoFault 未支持，则（1）任何绑定的shaders写访问的资源不能是一个unprotected resource
                                                                                      （2）pipeline绑定的pipeline stage中除了framebuffer-space 和compute stages之外的pipeline stage不能写入任何绑定的资源
    59.如果绑定到该命令使用的pipeline的任何shader stage使用了RayQueryKHR capability，则commandBuffer不能是一个protected command buffer
    60.baseGroupX 必须小于等于VkPhysicalDeviceLimits::maxComputeWorkGroupCount[0]，baseGroupY 必须小于等于VkPhysicalDeviceLimits::maxComputeWorkGroupCount[1]，baseGroupZ 必须小于等于VkPhysicalDeviceLimits::maxComputeWorkGroupCount[2]
    61.groupCountX 必须小于等于VkPhysicalDeviceLimits::maxComputeWorkGroupCount[0]减去baseGroupX，groupCountY 必须小于等于VkPhysicalDeviceLimits::maxComputeWorkGroupCount[1]减去baseGroupY，groupCountZ 必须小于等于VkPhysicalDeviceLimits::maxComputeWorkGroupCount[2]减去baseGroupZ
    62.如果baseGroupX, baseGroupY, or baseGroupZ都不为0，则绑定的compute pipeline或者shader object必须以VK_PIPELINE_CREATE_DISPATCH_BASE标志创建，

    */


    //subpass shading将以当前subpass的render area的维度dispatch 一些 compute work group并按照指定的 work group size进行划分，此时允许使用 subpassLoad命令
    //记录一个subpass shading       ，该命令会组装一个含有(render area size / local workgroup size) 个ceil local work groups的 global work group
    vkCmdSubpassShadingHUAWEI(commandBuffer);
    /*
    vkCmdSubpassShadingHUAWEI有效用法:
    1.如果一个VkSampler以其magFilter或者minFilter等于VK_FILTER_LINEAR创建，则（1）如果reductionMode为VK_SAMPLER_REDUCTION_MODE_WEIGHTED_AVERAGE，如果用于采样一个VkImageView作为该命令的结果的compareEnable为VK_FALSE，则该image view的format features必须包含VK_FORMAT_FEATURE_SAMPLED_IMAGE_FILTER_LINEAR_BIT
                                                                             （2）如果reductionMode为VK_SAMPLER_REDUCTION_MODE_MIN 或者VK_SAMPLER_REDUCTION_MODE_MAX之一 用于采样一个VkImageView作为该命令的结果，则该image view的format features必须包含VK_FORMAT_FEATURE_SAMPLED_IMAGE_FILTER_MINMAX_BIT
    2.如果一个VkSampler以其mipmapMode 等于VK_SAMPLER_MIPMAP_MODE_LINEAR创建，则（1）如果reductionMode为VK_SAMPLER_REDUCTION_MODE_WEIGHTED_AVERAGE，如果用于采样一个VkImageView作为该命令的结果的compareEnable为VK_FALSE，则该image view的format features必须包含VK_FORMAT_FEATURE_SAMPLED_IMAGE_FILTER_LINEAR_BIT
                                                                             （2）如果reductionMode为VK_SAMPLER_REDUCTION_MODE_MIN 或者VK_SAMPLER_REDUCTION_MODE_MAX之一 用于采样一个VkImageView作为该命令的结果，则该image view的format features必须包含VK_FORMAT_FEATURE_SAMPLED_IMAGE_FILTER_MINMAX_BIT
    3.如果一个VkSampler以其unnormalizedCoordinates等于VK_TRUE用于采样一个VkImageView作为该命令的结果创建，则（1）该image view的levelCount以及layerCount必须为1
                                                                                                            （2）该image view的viewType必须为VK_IMAGE_VIEW_TYPE_1D 或者 VK_IMAGE_VIEW_TYPE_2D
    4.如果一个VkImageView的采样带depth comparison操作，则image view的format features必须包含VK_FORMAT_FEATURE_2_SAMPLED_IMAGE_DEPTH_COMPARISON_BIT
    5.如果一个VkImageView使用atomic operations作为该命令的结果进行访问，则image view的format features必须包含VK_FORMAT_FEATURE_STORAGE_IMAGE_ATOMIC_BIT
    6.如果一个VK_DESCRIPTOR_TYPE_STORAGE_TEXEL_BUFFER类型的 descriptor使用atomic operations作为该命令的结果进行访问，则storage texel buffer的format features必须包含VK_FORMAT_FEATURE_STORAGE_TEXEL_BUFFER_ATOMIC_BIT
    7.如果一个以VK_FILTER_CUBIC_EXT进行采样的VkImageView作为该命令的结果，则image view的format features必须包含VK_FORMAT_FEATURE_SAMPLED_IMAGE_FILTER_CUBIC_BIT_EXT
    8.如果VK_EXT_filter_cubic拓展没有开启，且有任何一个以VK_FILTER_CUBIC_EXT进行采样的VkImageView作为该命令的结果，则其VkImageViewType不能为VK_IMAGE_VIEW_TYPE_3D, VK_IMAGE_VIEW_TYPE_CUBE, 或者 VK_IMAGE_VIEW_TYPE_CUBE_ARRAY
    9.任何一个以VK_FILTER_CUBIC_EXT进行采样的作为该命令的结果的VkImageView，其VkImageViewType和format 必须支持cubic filtering，参见vkGetPhysicalDeviceImageFormatProperties2返回的VkFilterCubicImageViewImageFormatPropertiesEXT::filterCubic
    10.任何一个以VK_FILTER_CUBIC_EXT进行采样且reduction mode为VK_SAMPLER_REDUCTION_MODE_MIN 或者 VK_SAMPLER_REDUCTION_MODE_MAX之一的作为该命令的结果的VkImageView，其VkImageViewType和format 必须支持带minmax filtering的cubic filtering，参见vkGetPhysicalDeviceImageFormatProperties2返回的VkFilterCubicImageViewImageFormatPropertiesEXT::filterCubicMinmax
    11.如果cubicRangeClamp特性没有开启，则有任何一个以VK_FILTER_CUBIC_EXT进行采样VkImageView的作为该命令的结果，VkSamplerReductionModeCreateInfo::reductionMode不能为VK_SAMPLER_REDUCTION_MODE_WEIGHTED_AVERAGE_RANGECLAMP_QCOM
    12.任何一个以VkSamplerReductionModeCreateInfo::reductionMode为VK_SAMPLER_REDUCTION_MODE_WEIGHTED_AVERAGE_RANGECLAMP_QCOM进行采样的作为该命令的结果的VkImageView必须以VK_FILTER_CUBIC_EXT进行采样
    13.如果selectableCubicWeights特性没有开启，则有任何一个以VK_FILTER_CUBIC_EXT进行采样VkImageView的作为该命令的结果，VkSamplerCubicWeightsCreateInfoQCOM::cubicWeights必须为VK_CUBIC_FILTER_WEIGHTS_CATMULL_ROM_QCOM
    14.任何一个以VkImageCreateInfo::flags含VK_IMAGE_CREATE_CORNER_SAMPLED_BIT_NV创建的采样作为该命令结果的VkImage必须以VkSamplerAddressMode为VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE 进行采样
    15.对于任何作为storage image写入的VkImageView，且其OpTypeImage的format未知，则该image view的 format features必须包含VK_FORMAT_FEATURE_2_STORAGE_WRITE_WITHOUT_FORMAT_BIT
    16.对于任何作为storage image读取的VkImageView，且其OpTypeImage的format未知，则该image view的 format features必须包含VK_FORMAT_FEATURE_2_STORAGE_READ_WITHOUT_FORMAT_BIT
    17.对于任何作为storage storage texel buffer写入的VkBufferView，且其OpTypeImage的format未知，则该buffer view的 buffer features必须包含VK_FORMAT_FEATURE_2_STORAGE_WRITE_WITHOUT_FORMAT_BIT
    18.对于任何作为storage storage texel buffer读取的VkBufferView，且其OpTypeImage的format未知，则该buffer view的 buffer features必须包含VK_FORMAT_FEATURE_2_STORAGE_READ_WITHOUT_FORMAT_BIT
    19.对于每个在绑定的shader中静态使用的set n，一个descriptor set必须被绑定到相同pipeline bind point的set n处，该set n必须和创建当前VkPipeline的VkPipelineLayout或者和创建当前VkShaderEXT的VkDescriptorSetLayout 数组的set n处的布局兼容，参见Pipeline Layout Compatibility p1280
    20.对于每个在绑定的shader中静态使用的push constant，一个push constant值必须被绑定到相同pipeline bind point的对应处，该push constant必须和创建当前VkPipeline的VkPipelineLayout或者和创建当前VkShaderEXT的VkDescriptorSetLayout 数组中的对应处的布局兼容，参见Pipeline Layout Compatibility p1280
    21.如果maintenance4特性没有开启，则对于每个在绑定的shader中静态使用的push constant，一个push constant值必须被设置到相同pipeline bind point的对应处，该push constant必须和创建当前VkPipeline的VkPipelineLayout或者和创建当前VkShaderEXT的VkDescriptorSetLayout 数组中的对应处的布局兼容，参见Pipeline Layout Compatibility p1280
    22.每一个通过vkCmdBindDescriptorSets绑定的descriptor set的descriptors,如果是被不以VK_PIPELINE_CREATE_DESCRIPTOR_BUFFER_BIT_EXT创建的，且已经绑定到该命令使用的pipeline bind point的VkPipeline静态使用的，则这些descriptors必须是有效的，参见 descriptor validity p1328
    23.如果通过vkCmdBindDescriptorSets指定绑定到pipeline bind point的VkPipeline要使用的descriptors，则绑定的VkPipeline不能以VK_PIPELINE_CREATE_DESCRIPTOR_BUFFER_BIT_EXT创建
    24.在vkCmdSetDescriptorBufferOffsetsEXT中指定绑定的descriptor buffers的descriptors，则（1）如果绑定到pipeline bind point的该命令会使用的VkPipeline以VK_PIPELINE_CREATE_DESCRIPTOR_BUFFER_BIT_EXT创建，且这些descriptors是动态使用的，则这些descriptors必须是有效的
                                                                                          （2）如果绑定到pipeline bind point的对应stage的该命令会使用的VkShaderEXT，且这些descriptors是动态使用的，则这些descriptors必须是有效的
    25.在vkCmdSetDescriptorBufferOffsetsEXT中指定的descriptors在绑定到pipeline bind point的VkPipeline中使用，则VkPipeline必须以VK_PIPELINE_CREATE_DESCRIPTOR_BUFFER_BIT_EXT创建
    26.如果一个descriptor在以VK_PIPELINE_CREATE_DESCRIPTOR_BUFFER_BIT_EXT创建的VkPipeline中动态使用，则descriptor memory必须是驻留内存
    27.如果一个descriptor在以其VkDescriptorSetLayout以VK_DESCRIPTOR_SET_LAYOUT_CREATE_DESCRIPTOR_BUFFER_BIT_EXT创建的VkShaderEXT中动态使用，则descriptor memory必须是驻留内存
    28.如果shaderObject 特性没有开启，一个有效的pipeline必须绑定到这个命令使用的绑定到pipeline bind point上
    29.如果一个pipeline绑定到该命令使用的pipeline bind point上，则不能有任何动态state 设置命令设置任何该VkPipeline 中没有指定的动态 state
    30.如果一个VkPipeline绑定到该命令使用的pipeline bind point上 或者任何一个会访问一个使用unnormalized coordinates的VkSampler的 VkShaderEXT绑定到该命令使用的pipeline bind point上的pipeline的对应stage，则
                                                                                （1）在任何shader stage中，VkSampler不能用来采样任何类型为VK_IMAGE_VIEW_TYPE_3D, VK_IMAGE_VIEW_TYPE_CUBE, VK_IMAGE_VIEW_TYPE_1D_ARRAY, VK_IMAGE_VIEW_TYPE_2D_ARRAY 或者 VK_IMAGE_VIEW_TYPE_CUBE_ARRAY的VkImageView
                                                                                （2）在任何shader stage中，该VkSampler不能和任何带有名字中带有ImplicitLod，Dref 或者 Proj 的SPIR-V OpImageSample* 或者 OpImageSparseSample*指令一起使用
                                                                                （3）在任何shader stage中，该VkSampler不能和任何包含 LOD bias或者offset 值 的SPIR-V OpImageSample* or OpImageSparseSample*指令一起使用
    31.如果shaderObject开启，一个有效的pipeline必须绑定到该命令使用的pipeline bind point上或者一个有效的shader objects以及VK_NULL_HANDLE的组合必须绑定到该命令使用的pipeline bind point每一个支持的shader stage上
    32.如何绑定到该命令使用的pipeline bind point上的VkPipeline的任何stage会访问一个uniform buffer，且该stage对uniformBuffers不以启用VK_PIPELINE_ROBUSTNESS_BUFFER_BEHAVIOR_ROBUST_BUFFER_ACCESS_EXT或者VK_PIPELINE_ROBUSTNESS_BUFFER_BEHAVIOR_ROBUST_BUFFER_ACCESS_2_EXT 创建，且robustBufferAccess特性未开启，则该stage就不能访问绑定到相同pipeline bind point的descriptor set指定的buffer范围外的值
    33.如果robustBufferAccess特性未开启，且任何会访问uniform buffer的绑定到该命令使用的pipeline bind point上对应shader stage的VkShaderEXT，则其不能访问绑定到相同pipeline bind point的descriptor set指定的buffer范围外的值
    34.如何绑定到该命令使用的pipeline bind point上的VkPipeline的任何stage会访问一个storage buffer，且该stage对storageBuffers不以启用VK_PIPELINE_ROBUSTNESS_BUFFER_BEHAVIOR_ROBUST_BUFFER_ACCESS_EXT或者VK_PIPELINE_ROBUSTNESS_BUFFER_BEHAVIOR_ROBUST_BUFFER_ACCESS_2_EXT 创建，且robustBufferAccess特性未开启，则该stage就不能访问绑定到相同pipeline bind point的descriptor set指定的buffer范围外的值
    35.如果robustBufferAccess特性未开启，且任何会访问storage buffer的绑定到该命令使用的pipeline bind point上对应shader stage的VkShaderEXT，则其不能访问绑定到相同pipeline bind point的descriptor set指定的buffer范围外的值
    36.如果commandBuffer 是一个unprotected command buffer，且protectedNoFault 未支持，则任何绑定的shaders访问的资源不能是一个protected resource
    37.如果一个绑定的shader访问一个VkSampler 或者 VkImageView ，且启用了sampler Y′C BCR conversion，则只能使用OpImageSample* 或者 OpImageSparseSample*指令，不能使用ConstOffset 以及 Offset操作符
    38.如果一个VkImageView作为该命令的结果进行访问，则（1）image view 的viewType 必须匹配Instruction/Sampler/Image View Validation p1481中描述的OpTypeImage的Dim操作符
                                                      （2）image view 的foamrt的numeric type 必须匹配OpTypeImage的Sampled Type操作符
    39.如果一个VkImageView以一个不是VK_FORMAT_A8_UNORM_KHR的format创建且通过OpImageWrite作为该命令的结果进行访问，则该命令的Texel 操作符的Type必须至少包含和 image view的 format含有的components的个数相同的components个数
    40.如果一个VkImageView以VK_FORMAT_A8_UNORM_KHR的format创建且通过OpImageWrite作为该命令的结果进行访问，则该命令的Texel 操作符的Type必须包含4个components
    41.如果一个VkBufferView通过OpImageWrite作为该命令的结果进行访问，则该命令的Texel 操作符的Type必须至少包含和 buffer view的 format含有的components的个数相同的components个数
    42.如果一个带64-bit component的VkFormat的VkImageView作为该命令的结果进行访问，则该命令的OpTypeImage操作符的SampledType的宽度必须为64
    43.如果一个带少于64-bit component的VkFormat的VkImageView作为该命令的结果进行访问，则该命令的OpTypeImage操作符的SampledType的宽度必须为32
    44.如果一个带64-bit component的VkFormat的VkBufferView作为该命令的结果进行访问，则该命令的OpTypeImage操作符的SampledType的宽度必须为64位
    45.如果一个带少于64-bit component的VkFormat的VkBufferView作为该命令的结果进行访问，则该命令的OpTypeImage操作符的SampledType的宽度必须为32
    46.如果sparseImageInt64Atomics 特性未开启，则以VK_IMAGE_CREATE_SPARSE_RESIDENCY_BIT创建的VkImage对象不能被SampledType宽度为64位的OpTypeImage的atomic instructions访问
    47.如果sparseImageInt64Atomics 特性未开启，则以VK_BUFFER_CREATE_SPARSE_RESIDENCY_BIT创建的VkBuffer对象不能被SampledType宽度为64位的OpTypeImage的atomic instructions访问
    48.如果OpImageWeightedSampleQCOM用来采样一个作为该命令的结果的VkImageView，则该image view的format features必须包含VK_FORMAT_FEATURE_2_WEIGHT_SAMPLED_IMAGE_BIT_QCOM
    49.如果OpImageWeightedSampleQCOM用来采样一个作为该命令的结果的sample weight image的VkImageView，则该image view的format features必须包含VK_FORMAT_FEATURE_2_WEIGHT_IMAGE_BIT_QCOM
    50.如果OpImageBoxFilterQCOM用来采样一个作为该命令的结果的VkImageView，则该image view的format features必须包含VK_FORMAT_FEATURE_2_BOX_FILTER_SAMPLED_BIT_QCOM
    51.如果OpImageBlockMatchSSDQCOM，或者 OpImageBlockMatchSADQCOM用来读取一个作为该命令的结果的VkImageView，则（1）该image view的format features必须包含VK_FORMAT_FEATURE_2_BLOCK_MATCHING_BIT_QCOM
                                                                                                               （2）如果是读取的reference image，指定的reference coordinates不能在integer texel coordinate validation 时候失败
    52.如果OpImageWeightedSampleQCOM, OpImageBoxFilterQCOM, OpImageBlockMatchWindowSSDQCOM, OpImageBlockMatchWindowSADQCOM, OpImageBlockMatchGatherSSDQCOM,
                                                OpImageBlockMatchGatherSADQCOM, OpImageBlockMatchSSDQCOM, 或者 OpImageBlockMatchSADQCOM用来采样一个作为该命令的结果的VkImageView，则该VkSampler必须以VK_SAMPLER_CREATE_IMAGE_PROCESSING_BIT_QCOM创建
    53.如果任何除了OpImageWeightedSampleQCOM, OpImageBoxFilterQCOM, OpImageBlockMatchWindowSSDQCOM, OpImageBlockMatchWindowSADQCOM, OpImageBlockMatchGatherSSDQCOM, OpImageBlockMatchGatherSADQCOM, OpImageBlockMatchSSDQCOM, 或者 OpImageBlockMatchSADQCOM之外的指令使用VkSampler进行采样作为该命令的结果，则该sampler不能以VK_SAMPLER_CREATE_IMAGE_PROCESSING_BIT_QCOM 创建
    54.如果OpImageBlockMatchWindow*QCOM or OpImageBlockMatchGather*QCOM指令用来读取VkImageView作为该命令的结果，则（1）VkImageView的format features必须包含VK_FORMAT_FEATURE_2_BLOCK_MATCHING_BIT_QCOM
                                                                                                                  （2）VkImageView的format必须只含有一个component
    55.如果OpImageBlockMatchWindow*QCOM or OpImageBlockMatchGather*QCOM指令用来读取一个引用的image作为该命令的结果，则指定的 reference coordinates不能在integer texel coordinate validation 时候失败
    56.任何该命令执行的shader invocation必须已经终止
    57.如果有一个类型位为VK_DESCRIPTOR_TYPE_SAMPLE_WEIGHT_IMAGE_QCOM, VK_DESCRIPTOR_TYPE_BLOCK_MATCH_IMAGE_QCOM, VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE, VK_DESCRIPTOR_TYPE_STORAGE_IMAGE, 或者 VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT中任意一个的descriptor作为该命令的结果进行访问，则该descriptor所指的image subresource的layout必须和该descriptor被写入时的layout相同。
    58.改命令必须在subpass中调用且绑定点为VK_PIPELINE_BIND_POINT_SUBPASS_SHADING_HUAWEI，同时该subpass中就不能再调用绘制命令，只能调用该命令
    */



    //Dispatch Command for CUDA PTX Kernels   参见p2899
    {
        /*
        Compute kernels 可以由 SPIR-V 或者 PTX code提供，但使用PTX kernels的话dispatch机制会有所区别，参见https://docs.nvidia.com/cuda/. 
        
        记录dispatching CUDA kernel命令之前要先创建CUDA module，见CUDA Modules.p705
        */

        VkCudaLaunchInfoNV cudaLaunchInfoNV{};//该结构体中的参数十分接近CUDA-Driver的接口
        cudaLaunchInfoNV.sType = VK_STRUCTURE_TYPE_MAX_ENUM;//因为是自己定义的所以设置为非法值
        cudaLaunchInfoNV.pNext = nullptr;
        cudaLaunchInfoNV.function = VK_NULL_HANDLE;//为函数launch的CUDA-Driver handle
        cudaLaunchInfoNV.gridDimX = 1;//为dispatch的local workgroups 的 X 维度的数量,必须小于等于 VkPhysicalDeviceLimits::maxComputeWorkGroupCount[0]
        cudaLaunchInfoNV.gridDimY = 1;//为dispatch的local workgroups 的 Y 维度的数量,必须小于等于 VkPhysicalDeviceLimits::maxComputeWorkGroupCount[1]
        cudaLaunchInfoNV.gridDimZ = 1;//为dispatch的local workgroups 的 Z 维度的数量,必须小于等于 VkPhysicalDeviceLimits::maxComputeWorkGroupCount[2]
        cudaLaunchInfoNV.blockDimX = 1;//为X 维度的块大小
        cudaLaunchInfoNV.blockDimY = 1;//为Y 维度的块大小
        cudaLaunchInfoNV.blockDimZ = 1;//为Z 维度的块大小
        cudaLaunchInfoNV.sharedMemBytes = 0;//是每个线程块的动态共享内存大小。
        cudaLaunchInfoNV.paramCount = 1;//pParams中元素个数
        cudaLaunchInfoNV.pParams = nullptr;//每个对应为传递给function的参数，function需要几个参数，这里就得提供几个参数
        cudaLaunchInfoNV.extraCount = 0;//保留未来使用
        cudaLaunchInfoNV.pExtras = nullptr;//保留未来使用
        /*
        VkCudaLaunchInfoNV有效用法:
        1.gridDimX必须小于等于 VkPhysicalDeviceLimits::maxComputeWorkGroupCount[0],gridDimY必须小于等于 VkPhysicalDeviceLimits::maxComputeWorkGroupCount[1],gridDimZ必须小于等于 VkPhysicalDeviceLimits::maxComputeWorkGroupCount[2]
        2.paramCount必须等于pParams中列举的参数个数
        3.pParams必须指向paramCount个参数的数组，这些参数对应function中需要的参数
        4.extraCount 必须为0，pExtras必须为NULL

        */


        //记录 CUDA kernel launch命令    ，该命令执行会组装含有gridDimX × gridDimY × gridDimZ 个local workgroups的global workgroup
        vkCmdCudaLaunchKernelNV(commandBuffer, &cudaLaunchInfoNV/*pLaunchInfo,为一个VkCudaLaunchInfoNV对象指针，定义grid(类似于workgroup) dimension , function handle 以及相关参数.*/);
    


        // Resource Sharing from Vulkan to the CUDA Kernel    数据如何从vulkan 传递到cuda代码中,简单将就是vulkan不能直接访问cuda的资源来进行修改，只能传参给cuda函数，让cuda自己去处理，以及相关示例代码见   p2902

    }

}

void DispatchingAndDeviceGeneratedCommandsTest::DeviceGeneratedCommandsTest()
{
    /*
    如何再device上生成command buffer中的commands内容，需要参照以下步骤:
    > 通过 VkIndirectCommandsLayoutNV 指定command buffer中生成的commands的顺序
    > 可选择的使用graphics pipelines能够绑定的shader groups
    > 通过vkGetBufferDeviceAddressEXT获取设置buffers的设备地址
    > 通过vkGetPipelineIndirectDeviceAddressNV获取可以绑定用来device generated rendering的compute pipeline的设备地址
    > 填充一个或者多个VkBuffer，其中的内容会被解释为VkIndirectCommandsLayoutNV
    > 使用vkGetGeneratedCommandsMemoryRequirementsNV获取的分配信息创建一个预处理VkBuffer，
    > 可选的在一个分离的动作中通过vkCmdPreprocessGeneratedCommandsNV 预处理输入数据
    > 传递所有需要的数据然后通过vkCmdExecuteGeneratedCommandsNV产生以及执行实际的commands
    */



}



NS_TEST_END