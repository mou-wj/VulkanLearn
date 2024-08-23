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

    
    
    //Indirect Commands Layout  参见p2905
    {
        /*
        设备端命令生成通过对命令令牌的原子顺序的迭代处理进行，其在VkIndirectCommandsLayoutNV中表示，每个VkIndirectCommandsLayoutNV必须有一个命令令牌且必须是原子顺序中的最后一个
        */

        VkIndirectCommandsLayoutNV indirectCommandsLayoutNV{};
        //Creation and Deletion  参见p2905
        {


            VkIndirectCommandsLayoutCreateInfoNV indirectCommandsLayoutCreateInfoNV{};
            indirectCommandsLayoutCreateInfoNV.sType = VK_STRUCTURE_TYPE_INDIRECT_COMMANDS_LAYOUT_TOKEN_NV;
            indirectCommandsLayoutCreateInfoNV.pNext = nullptr;
            indirectCommandsLayoutCreateInfoNV.flags = 0;//为VkIndirectCommandsLayoutUsageFlagBitsNV组合值位掩码，指明这个layout的用法提示
            /*
            VkIndirectCommandsLayoutUsageFlagBitsNV:
            VK_INDIRECT_COMMANDS_LAYOUT_USAGE_EXPLICIT_PREPROCESS_BIT_NV:  指明该layout总是用于调用vkCmdPreprocessGeneratedCommandsNV手动控制预处理步骤以及调用vkCmdExecuteGeneratedCommandsNV设置isPreprocessed为VK_TRUE来进行执行
            VK_INDIRECT_COMMANDS_LAYOUT_USAGE_INDEXED_SEQUENCES_BIT_NV:  指明顺序的输入数据不是隐式的从索引0到sequencesUsed，而是从用户提供的VkBuffer中的编码的索引开始的
            VK_INDIRECT_COMMANDS_LAYOUT_USAGE_UNORDERED_SEQUENCES_BIT_NV:  指明顺序的处理操作可以不以一个implementation-dependent的顺序保证使用相同的输入数据是一致的，如果pipelineBindPoint为 VK_PIPELINE_BIND_POINT_COMPUTE则该标志是忽略的，dispatch sequence总是无序的

            
            */
            indirectCommandsLayoutCreateInfoNV.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;//为该layout的VkPipelineBindPoint 值
            indirectCommandsLayoutCreateInfoNV.streamCount = 1;//提供令牌输入的流的数量
            uint32_t streamStride = 3;
            indirectCommandsLayoutCreateInfoNV.pStreamStrides = &streamStride;//定义每个流的字节步长的数组
            indirectCommandsLayoutCreateInfoNV.tokenCount = 1;//单个命令序列的长度
            VkIndirectCommandsLayoutTokenNV indirectCommandsLayoutTokenNV{};
            {
                /*
                Tokenized Command Processing  参见p2915
                
                简单将就是一个token对应一条命令，这些命令的输入参数保存在stream中，通过每个token的类型判断是哪一条命令，然后从stream中获取对应输入参数，然后执行这条命令
                */
                indirectCommandsLayoutTokenNV.sType = VK_STRUCTURE_TYPE_INDIRECT_COMMANDS_LAYOUT_TOKEN_NV;
                indirectCommandsLayoutTokenNV.pNext = nullptr;
                indirectCommandsLayoutTokenNV.tokenType = VK_INDIRECT_COMMANDS_TOKEN_TYPE_DISPATCH_NV;//一个VkIndirectCommandsTokenTypeNV值指明token command 类型
                /*
                VkIndirectCommandsTokenTypeNV:   （对应一个命令）
                Token type                                                    Equivalent command
                VK_INDIRECT_COMMANDS_TOKEN_TYPE_SHADER_GROUP_NV              vkCmdBindPipelineShaderGroupNV
                VK_INDIRECT_COMMANDS_TOKEN_TYPE_STATE_FLAGS_NV               -
                VK_INDIRECT_COMMANDS_TOKEN_TYPE_INDEX_BUFFER_NV              vkCmdBindIndexBuffer
                VK_INDIRECT_COMMANDS_TOKEN_TYPE_VERTEX_BUFFER_NV             vkCmdBindVertexBuffers
                VK_INDIRECT_COMMANDS_TOKEN_TYPE_PUSH_CONSTANT_NV             vkCmdPushConstants
                VK_INDIRECT_COMMANDS_TOKEN_TYPE_DRAW_INDEXED_NV              vkCmdDrawIndexedIndirect
                VK_INDIRECT_COMMANDS_TOKEN_TYPE_DRAW_NV                      vkCmdDrawIndirect
                VK_INDIRECT_COMMANDS_TOKEN_TYPE_DRAW_TASKS_NV                vkCmdDrawMeshTasksIndirectNV
                VK_INDIRECT_COMMANDS_TOKEN_TYPE_DRAW_MESH_TASKS_NV           vkCmdDrawMeshTasksIndirectEXT
                VK_INDIRECT_COMMANDS_TOKEN_TYPE_PIPELINE_NV                  vkCmdBindPipeline
                VK_INDIRECT_COMMANDS_TOKEN_TYPE_DISPATCH_NV                  vkCmdDispatchIndirect


                */

                indirectCommandsLayoutTokenNV.stream = 0;//是包含token参数数据的输入流的索引。
                indirectCommandsLayoutTokenNV.offset = 0;//是包含token参数数据的输入流的参数的起始字节偏移量
                indirectCommandsLayoutTokenNV.vertexBindingUnit = 0;//用于vertex buffer binding命令
                indirectCommandsLayoutTokenNV.vertexDynamicStride = VK_FALSE;//设置是否vertex buffer stride由绑定的command提供而不是当前绑定的pipeline stage提供
                indirectCommandsLayoutTokenNV.pushconstantPipelineLayout = VkPipelineLayout{/*假设这是一个有效的VkPipelineLayout*/ };//为用于push constant command的layout
                indirectCommandsLayoutTokenNV.pushconstantShaderStageFlags = VK_SHADER_STAGE_ALL_GRAPHICS;//为用于push constant command的shader stage
                indirectCommandsLayoutTokenNV.pushconstantOffset = 0;//为用于push constant command的offset
                indirectCommandsLayoutTokenNV.pushconstantSize = 0;//为用于push constant command的size
                indirectCommandsLayoutTokenNV.indirectStateFlags = VK_INDIRECT_STATE_FLAG_FRONTFACE_BIT_NV;//VkIndirectStateFlagsNV, 该值的比特域指明对应激活的shader stage，  VK_INDIRECT_STATE_FLAG_FRONTFACE_BIT_NV : 允许后续绘制命令转换VkFrontFace rasterization state
                indirectCommandsLayoutTokenNV.indexTypeCount = 1;//为可选的pIndexTypes 以及 pIndexTypeValues数组的大小，如果不为0，则可以允许注册一个自定义的uint32_t值指定一个VkIndexType
                VkIndexType indexType = VK_INDEX_TYPE_UINT8_EXT;

                indirectCommandsLayoutTokenNV.pIndexTypes = &indexType;//一组VkIndexType数组指针
                uint32_t indexValue = 0;
                indirectCommandsLayoutTokenNV.pIndexTypeValues = &indexValue;//一组uint32_t数组指针，其中每个uint32_t元素对应pIndexTypes中对应元素的VkIndexType
                /*
                VkIndirectCommandsLayoutTokenNV有效用法:
                1.stream必须小于VkIndirectCommandsLayoutCreateInfoNV::streamCount
                2.offset必须小于等于VkPhysicalDeviceDeviceGeneratedCommandsPropertiesNV::maxIndirectCommandsTokenOffset          
                3.offset必须对齐到tokenType的标量对齐字节数或者minIndirectCommandsBufferOffsetAlignment中小的哪个
                4.如果tokenType为VK_INDIRECT_COMMANDS_TOKEN_TYPE_VERTEX_BUFFER_NV，则vertexBindingUnit 必须满足对应command的设备支持的限制
                5.如果tokenType为VK_INDIRECT_COMMANDS_TOKEN_TYPE_PUSH_CONSTANT_NV，则（1）pushconstantPipelineLayout必须是有效的
                                                                                     （2）pushconstantOffset，pushconstantSize必须是4的倍数
                                                                                     （3）pushconstantOffset必须小于VkPhysicalDeviceLimits::maxPushConstantsSize
                                                                                     （4）pushconstantSize必须小于等于VkPhysicalDeviceLimits::maxPushConstantsSize 减去pushconstantOffset
                                                                                     （5）对pushconstantShaderStageFlags的指定的shader stage的以及由 pushconstantOffset 以及 pushconstantSize指定的范围内的byte,pushconstantPipelineLayout中必须包含该byte以及shader stage
                                                                                     （6）对pushconstantOffset 以及 pushconstantSize指定的范围的每个字节以及 每个包含该字节的push constant range，pushconstantShaderStageFlags必须包含所有push constant range的VkPushConstantRange::stageFlags指定的stage
                6.如果tokenType为VK_INDIRECT_COMMANDS_TOKEN_TYPE_STATE_FLAGS_NV，indirectStateFlags必须为0
                */
            }
            indirectCommandsLayoutCreateInfoNV.pTokens = &indirectCommandsLayoutTokenNV;//一组VkIndirectCommandsLayoutTokenNV数组指针，详细描述每个命令令牌
            /*
            VkIndirectCommandsLayoutCreateInfoNV有效用法:
            1.pipelineBindPoint 必须为VK_PIPELINE_BIND_POINT_GRAPHICS 或者 VK_PIPELINE_BIND_POINT_COMPUTE
            2.tokenCount必须大于0小于等于VkPhysicalDeviceDeviceGeneratedCommandsPropertiesNV::maxIndirectCommandsTokenCount
            3.如果pTokens 包含一个VK_INDIRECT_COMMANDS_TOKEN_TYPE_SHADER_GROUP_NV 类型的元素，则该元素必须是第一个元素且该类性的元素只能含有一个
            4.如果pTokens 包含一个VK_INDIRECT_COMMANDS_TOKEN_TYPE_PIPELINE_NV 类型的元素，则该元素必须是第一个元素且该类性的元素只能含有一个
            5.如果pTokens 包含一个VK_INDIRECT_COMMANDS_TOKEN_TYPE_STATE_FLAGS_NV 类型的元素，则该类性的元素只能含有一个
            6.pTokens中的state tokens必须在(VK_INDIRECT_COMMANDS_TOKEN_TYPE_DRAW_NV,
                                            VK_INDIRECT_COMMANDS_TOKEN_TYPE_DRAW_INDEXED_NV,
                                            VK_INDIRECT_COMMANDS_TOKEN_TYPE_DRAW_TASKS_NV,
                                            VK_INDIRECT_COMMANDS_TOKEN_TYPE_DRAW_MESH_TASKS_NV ,
                                            VK_INDIRECT_COMMANDS_TOKEN_TYPE_DISPATCH_NV )这些action tokens前
            7.pTokens中的内容必须包含一个和pipelineBindPoint兼容的action command token
            8.streamCount必须大于0小于等于VkPhysicalDeviceDeviceGeneratedCommandsPropertiesNV::maxIndirectCommandsStreamCount
            9.pStreamStrides中的每个元素必须大于0小于等于VkPhysicalDeviceDeviceGeneratedCommandsPropertiesNV::maxIndirectCommandsStreamStride，此外，还必须确保每个令牌输入的对齐方式
            10.如果pipelineBindPoint 为VK_PIPELINE_BIND_POINT_COMPUTE，则（1）VkPhysicalDeviceDeviceGeneratedCommandsComputeFeaturesNV::deviceGeneratedCompute 特性必须开启
                                                                         （2）pTokens中的state tokens必须只能包含VK_INDIRECT_COMMANDS_TOKEN_TYPE_DISPATCH_NV,VK_INDIRECT_COMMANDS_TOKEN_TYPE_PIPELINE_NV, 或者VK_INDIRECT_COMMANDS_TOKEN_TYPE_PUSH_CONSTANT_NV类型的
                                                                         （3）如果pTokens中包含VK_INDIRECT_COMMANDS_TOKEN_TYPE_PIPELINE_NV类型的，则VkPhysicalDeviceDeviceGeneratedCommandsComputeFeaturesNV::deviceGeneratedComputePipelines特性必须开启

            */



            //创建VkIndirectCommandsLayoutNV       ， VkPhysicalDeviceDeviceGeneratedCommandsFeaturesNV::deviceGeneratedCommands特性必须开启
            vkCreateIndirectCommandsLayoutNV(device, &indirectCommandsLayoutCreateInfoNV, nullptr, &indirectCommandsLayoutNV);



            //销毁VkIndirectCommandsLayoutNV
            vkDestroyIndirectCommandsLayoutNV(device, indirectCommandsLayoutNV, nullptr);
            /*
            vkDestroyIndirectCommandsLayoutNV有效用法:
            1.所有引用到indirectCommandsLayout的提交的命令必须完成执行
            2.如果创建indirectCommandsLayout提供了VkAllocationCallbacks，则这里也需要提供一个兼容的callbacks
            3.如果创建indirectCommandsLayout没有提供VkAllocationCallbacks，则这里的pAllocator必须为NULL
            4.VkPhysicalDeviceDeviceGeneratedCommandsFeaturesNV::deviceGeneratedCommands 特性必须开启

            */

        }

        
        // Token Input Streams  参见p2911
        {
            //
            /*
            VkIndirectCommandsStreamNV 指明处理commands tokens的时候这些tokens的输入数据

            input streams可以包含原始的uint32_t参数，可用于间接命令:
                                                                    VkDrawIndirectCommand
                                                                    VkDrawIndexedIndirectCommand
                                                                    VkDrawMeshTasksIndirectCommandNV
                                                                    VkDrawMeshTasksIndirectCommandEXT
                                                                    VkDispatchIndirectCommand
            */
            VkIndirectCommandsStreamNV indirectCommandsStreamNV{};
            indirectCommandsStreamNV.buffer = VkBuffer{/*假设这是一个有效的VkBuffer*/ };//指明存储每个序列的函数命令的VkBuffer，这些参数可以被设备写入
            indirectCommandsStreamNV.offset = 0;//指明这些参数的起始字节偏移量
            /*
            VkIndirectCommandsStreamNV有效用法:
            1.buffer必须以VK_BUFFER_USAGE_INDIRECT_BUFFER_BIT 创建
            2.offset 必须对齐到VkPhysicalDeviceDeviceGeneratedCommandsPropertiesNV::minIndirectCommandsBufferOffsetAlignment
            3.如果buffer是non-sparse的则其必须绑定到完整的连续的单独的VkDeviceMemory对象
            */

            VkBindShaderGroupIndirectCommandNV bindShaderGroupIndirectCommandNV{};
            bindShaderGroupIndirectCommandNV.groupIndex = 0;//指明使用当前绑定的pipeline的哪个shader group
            /*
            VkBindShaderGroupIndirectCommandNV有效用法:
            1.当前绑定的pipeline，或者该结构体引用的pipeline，必须以VK_PIPELINE_CREATE_INDIRECT_BINDABLE_BIT_NV创建
            2.groupIndex索引必须在当前绑定的pipeline的可使用的shader groups的范围内，见vkCmdBindPipelineShaderGroupNV

            */


            //VkBindIndexBufferIndirectCommandNV指明类型为VK_INDIRECT_COMMANDS_TOKEN_TYPE_INDEX_BUFFER_NV token的输入参数
            VkBindIndexBufferIndirectCommandNV bindIndexBufferIndirectCommandNV{};
            bindIndexBufferIndirectCommandNV.bufferAddress = 0;//指定用于index buffer的VkBuffer的物理地址
            bindIndexBufferIndirectCommandNV.indexType = VK_INDEX_TYPE_UINT8_EXT;//是一个 VkIndexType值，指明如何解释buffer中的索引值，除了为Vulkan枚举类型外，一个自定义的uint32_t值可以映射到VkIndirectCommandsLayoutTokenNV::pIndexTypes 和 VkIndirectCommandsLayoutTokenNV::pIndexTypeValues定义的 VkIndexType
            bindIndexBufferIndirectCommandNV.size = 1;//为从bufferAddress开始可访问的字节大小
            /*
            VkBindIndexBufferIndirectCommandNV有效用法:
            1.bufferAddress所在的buffer必须以VK_BUFFER_USAGE_INDEX_BUFFER_BIT创建
            2.bufferAddress必须对齐到使用的indexType
            3.bufferAddress所在的buffer如果不是non-sparse的则其必须绑定到完整的连续的单独的VkDeviceMemory对象

            */


            //VkBindVertexBufferIndirectCommandNV指明类型为VK_INDIRECT_COMMANDS_TOKEN_TYPE_VERTEX_BUFFER_NV token的输入参数
            VkBindVertexBufferIndirectCommandNV bindVertexBufferIndirectCommandNV{};
            bindVertexBufferIndirectCommandNV.bufferAddress = 0;//指定用于vertex 输入绑定的vertex buffer的VkBuffer的物理地址
            bindVertexBufferIndirectCommandNV.stride = 3;//是vertex 输入绑定的字节步长，如 VkVertexInputBindingDescription::stride.  这里只会在设置了VkIndirectCommandsLayoutTokenNV::vertexDynamicStride才使用，否则会直接从当前绑定的pipeline上继承
            bindVertexBufferIndirectCommandNV.size = 1;//为从bufferAddress开始可访问的字节大小
            /*
            VkBindVertexBufferIndirectCommandNV有效用法:
            1.bufferAddress所在的buffer必须以VK_BUFFER_USAGE_VERTEX_BUFFER_BIT创建
            2.bufferAddress所在的buffer如果不是non-sparse的则其必须绑定到完整的连续的单独的VkDeviceMemory对象

            */


            //VkSetStateFlagsIndirectCommandNV 指明类型为VK_INDIRECT_COMMANDS_TOKEN_TYPE_STATE_FLAGS_NV token的输入参数, 其在VkIndirectCommandsLayoutNV的VkIndirectStateFlagBitsNV指定的stage参数会改变
            VkSetStateFlagsIndirectCommandNV setStateFlagsIndirectCommandNV{};
            setStateFlagsIndirectCommandNV.data = 0x00000001;//编码该命令改变的参数，如果某bit（对应一个shader stage）为0，表示VK_FRONT_FACE_CLOCKWISE，否则表示为VK_FRONT_FACE_COUNTER_CLOCKWISE

            //VkBindPipelineIndirectCommandNV指明类型为VK_INDIRECT_COMMANDS_TOKEN_TYPE_PIPELINE_NV token的输入参数
            VkBindPipelineIndirectCommandNV bindPipelineIndirectCommandNV{};
            bindPipelineIndirectCommandNV.pipelineAddress = 0;//指明在device generated rendering使用的compute pipeline的设备地址
            /*
            VkBindPipelineIndirectCommandNV有效用法:
            1.VkPhysicalDeviceDeviceGeneratedCommandsComputeFeaturesNV::deviceGeneratedComputePipelines 特性必须开启
            2.引用的pipeline，（1）必须以VK_PIPELINE_CREATE_INDIRECT_BINDABLE_BIT_NV创建
                              （2）必须用vkCmdUpdatePipelineIndirectBufferNV更新
                              （3）其设备地址必须调用vkGetPipelineIndirectDeviceAddressNV查询

            */




        }


    }



    //Indirect Commands Generation and Execution 参见p2922
    {
        //在设备端产生命令需要预处理buffer，创建该buffer需要查询相关内存需求
        VkGeneratedCommandsMemoryRequirementsInfoNV generatedCommandsMemoryRequirementsInfoNV{};
        generatedCommandsMemoryRequirementsInfoNV.sType = VK_STRUCTURE_TYPE_GENERATED_COMMANDS_MEMORY_REQUIREMENTS_INFO_NV;
        generatedCommandsMemoryRequirementsInfoNV.pNext = nullptr;
        generatedCommandsMemoryRequirementsInfoNV.pipelineBindPoint = VK_PIPELINE_BIND_POINT_COMPUTE;//为pipeline的VkPipelineBindPoint，指明该buffer memory要打算在哪里使用
        generatedCommandsMemoryRequirementsInfoNV.pipeline = VkPipeline{/*假设这是一个有效的VkPipeline*/ };//为VkPipeline，指明该buffer memory要打算在哪里使用
        generatedCommandsMemoryRequirementsInfoNV.maxSequencesCount = 1;//为该buffer memory可以和其他state提供的可使用的最大序列的数量
        /*
        VkGeneratedCommandsMemoryRequirementsInfoNV有效用法:
        1.maxSequencesCount必须小于等于VkPhysicalDeviceDeviceGeneratedCommandsPropertiesNV::maxIndirectSequenceCount
        2.如果pipelineBindPoint为VK_PIPELINE_BIND_POINT_GRAPHICS，pipeline必须是有效的
        3.如果pipelineBindPoint为VK_PIPELINE_BIND_POINT_COMPUTE， （1）如果indirectCommandsLayout不以含有一个VK_INDIRECT_COMMANDS_TOKEN_TYPE_PIPELINE_NV类型的token创建，则 pipeline必须是有效的
                                                                  （2）如果indirectCommandsLayout以含有一个VK_INDIRECT_COMMANDS_TOKEN_TYPE_PIPELINE_NV类型的token创建，则 pipeline必须VK_NULL_HANDLE

        */


        VkMemoryRequirements2 memoryRequirements2{};
        memoryRequirements2.sType = VK_STRUCTURE_TYPE_MEMORY_REQUIREMENTS_2;
        memoryRequirements2.pNext = nullptr;
        memoryRequirements2.memoryRequirements = VkMemoryRequirements{
            .size = 0,
            .alignment = 0,
            .memoryTypeBits = 0
        };
        vkGetGeneratedCommandsMemoryRequirementsNV(device, &generatedCommandsMemoryRequirementsInfoNV, &memoryRequirements2);
        /*
        vkGetGeneratedCommandsMemoryRequirementsNV有效用法:
        1.VkPhysicalDeviceDeviceGeneratedCommandsFeaturesNV::deviceGeneratedCommands 特性必须开启
        2.如果pInfo->pipelineBindPoint为VK_PIPELINE_BIND_POINT_COMPUTE，则VkPhysicalDeviceDeviceGeneratedCommandsComputeFeaturesNV::deviceGeneratedCompute 特性必须开启

        */


        //要在 Device-Generated Commands,中绑定一个compute pipeline，需要查询该pipeline的设备地址
        VkPipelineIndirectDeviceAddressInfoNV pipelineIndirectDeviceAddressInfoNV{};
        pipelineIndirectDeviceAddressInfoNV.sType = VK_STRUCTURE_TYPE_PIPELINE_INDIRECT_DEVICE_ADDRESS_INFO_NV;
        pipelineIndirectDeviceAddressInfoNV.pNext = nullptr;
        pipelineIndirectDeviceAddressInfoNV.pipeline = VkPipeline{/*假设这是一个有效的VkPipeline*/ };//指明要查询地址的pipeline
        pipelineIndirectDeviceAddressInfoNV.pipelineBindPoint = VK_PIPELINE_BIND_POINT_COMPUTE;//为一个 VkPipelineBindPoint 值，指明要查询地址的pipeline的类型
        /*
        VkPipelineIndirectDeviceAddressInfoNV有效用法:
        1.pipelineBindPoint 必须为VK_PIPELINE_BIND_POINT_COMPUTE
        2.pipeline 必须以VK_PIPELINE_CREATE_INDIRECT_BINDABLE_BIT_NV创建
        3.pipeline必须以含有VkComputePipelineIndirectBufferInfoNV创建，指明一个有效的其metadata可以保存的地址

        */

        vkGetPipelineIndirectDeviceAddressNV(device, &pipelineIndirectDeviceAddressInfoNV);//VkPhysicalDeviceDeviceGeneratedCommandsComputeFeaturesNV::deviceGeneratedComputePipelines 特性必须开启



        //确定compute pipeline的metadata的内存需求
        VkComputePipelineCreateInfo computePipelineCreateInfo{/*假设这是一个有效的VkComputePipelineCreateInfo*/};
        VkMemoryRequirements2 computePipelineMemoryRequirements2{};
        computePipelineMemoryRequirements2.sType = VK_STRUCTURE_TYPE_MEMORY_REQUIREMENTS_2;
        computePipelineMemoryRequirements2.pNext = nullptr;
        computePipelineMemoryRequirements2.memoryRequirements = VkMemoryRequirements{
            .size = 0,
            .alignment = 0,
            .memoryTypeBits = 0
        };

        vkGetPipelineIndirectMemoryRequirementsNV(device, &computePipelineCreateInfo, &computePipelineMemoryRequirements2);
        /*
        vkGetPipelineIndirectMemoryRequirementsNV有效用法:
        1.VkPhysicalDeviceDeviceGeneratedCommandsComputeFeaturesNV::deviceGeneratedComputePipelines 特性必须开启
        2.pCreateInfo->flags 必须包含VK_PIPELINE_CREATE_INDIRECT_BINDABLE_BIT_NV

        */


        VkCommandBuffer commandBuffer{/*假设这是一个有效的VkCommandBuffer*/ };
        VkGeneratedCommandsInfoNV generatedCommandsInfoNV{};
        generatedCommandsInfoNV.sType = VK_STRUCTURE_TYPE_GENERATED_COMMANDS_INFO_NV;
        generatedCommandsInfoNV.pNext = nullptr;
        generatedCommandsInfoNV.pipelineBindPoint = VK_PIPELINE_BIND_POINT_COMPUTE;
        generatedCommandsInfoNV.pipeline = VkPipeline{/*假设这是一个有效的VkPipeline*/};
        VkIndirectCommandsLayoutNV indirectCommandsLayoutNV{/*假设这是一个有效的VkIndirectCommandsLayoutNV*/ };//前面已经描述过了，这里简单提一下
        generatedCommandsInfoNV.indirectCommandsLayout = indirectCommandsLayoutNV;
        generatedCommandsInfoNV.streamCount  = 1;
        VkIndirectCommandsStreamNV indirectCommandsStreamNV{/*假设这是一个有效的VkIndirectCommandsStreamNV*/ };//前面已经描述过了，这里简单提一下
        generatedCommandsInfoNV.pStreams = &indirectCommandsStreamNV;
        generatedCommandsInfoNV.sequencesCount = 0;
        generatedCommandsInfoNV.preprocessBuffer = VkBuffer{/*假设这是一个有效的VkBuffer*/};
        generatedCommandsInfoNV.preprocessOffset = 0;
        generatedCommandsInfoNV.preprocessSize = 1;
        generatedCommandsInfoNV.sequencesCountBuffer = VkBuffer{/*假设这是一个有效的VkBuffer*/ };
        generatedCommandsInfoNV.sequencesCountOffset = 0;
        generatedCommandsInfoNV.sequencesIndexBuffer = VkBuffer{/*假设这是一个有效的VkBuffer*/ };
        generatedCommandsInfoNV.sequencesIndexOffset = 0;
        //设备端的命令的实际生成和执行通过一个命令即可   ,如果VkGeneratedCommandsInfoNV::indirectCommandsLayout以VK_INDIRECT_COMMANDS_LAYOUT_USAGE_UNORDERED_SEQUENCES_BIT_NV创建，则这些命令执行是无序的，且获取不必要和VkGeneratedCommandsInfoNV::pStreams中的顺序相同
        vkCmdExecuteGeneratedCommandsNV(commandBuffer, VK_TRUE, &generatedCommandsInfoNV);
        /*
        vkCmdExecuteGeneratedCommandsNV有效用法:
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
        58.当前的 render pass  必须和绑定到VK_PIPELINE_BIND_POINT_GRAPHICS上的VkPipeline 创建时候的VkGraphicsPipelineCreateInfo中指定的renderPass兼容
        59.当前的 render pass  的subpass index必须和绑定到VK_PIPELINE_BIND_POINT_GRAPHICS上的VkPipeline 创建时候的VkGraphicsPipelineCreateInfo中指定的subpass相同
        60.如果任何shader静态访问一个input attachment，则有效的descriptor必须通过VkDescriptorSet被绑定到该pipeline中
        61.如果任何该pipeline执行shader以SubpassData的Dim操作符访问一个OpTypeImage变量，则该变量必须被一个对应当前subpass的input attachment的InputAttachmentIndex修饰
        62.在subpass中访问的Input attachment views必须以和该subpass相同定义的VkFormat创建，且必须以一个和当前绑定的VkFramebuffer的该附件引用的subpass的pInputAttachments[InputAttachmentIndex]附件兼容的VkImageView创建，参见Fragment Input Attachment Compatibility p1408
        63.在动态render pass中访问以VkRenderingInputAttachmentIndexInfoKHR的InputAttachmentIndex，或者VkRenderingInputAttachmentIndexInfoKHR:pDepthInputAttachmentIndex 或者 VkRenderingInputAttachmentIndexInfoKHR:pStencilInputAttachmentIndex为NULL情况下不指定InputAttachmentIndex的引用的Input attachment views，必须以和VkRenderingInfo中对应color, depth, 或者 stencil attachment兼容的VkImageView创建
        64.如果VkRenderingInputAttachmentIndexInfoKHR::pDepthInputAttachmentIndex 以及 VkRenderingInputAttachmentIndexInfoKHR::pStencilInputAttachmentIndex不为NULL，则在动态render pass中通过shader object访问Input attachment views必须指明InputAttachmentIndex
        65.如果在动态render pass中通过shader object访问Input attachment views指明了InputAttachmentIndex，则InputAttachmentIndex必须匹配VkRenderingInputAttachmentIndexInfoKHR中的index
        66.当前render pass所用的附件对应的image subresource底层内存的写入只能作为该命令的一个附件写入
        67.如果一个color attachment在之前的该subpass的命令中以load, store, 或者 resolve operations进行了写入，则其layout不为VK_IMAGE_LAYOUT_ATTACHMENT_FEEDBACK_LOOP_OPTIMAL_EXT，且有当前绑定的pipeline设有VK_PIPELINE_CREATE_COLOR_ATTACHMENT_FEEDBACK_LOOP_BIT_EXT，或者
                                        最后的vkCmdSetAttachmentFeedbackLoopEnableEXT调用包含VK_IMAGE_ASPECT_COLOR_BIT以及 没有绑定的pipeline 或者绑定的pipeline以VK_DYNAMIC_STATE_ATTACHMENT_FEEDBACK_LOOP_ENABLE_EXT创建，则该附件只能以附件进行访问的，这两种情况中之一
        68.如果一个depth attachment在之前的该subpass的命令中以load, store, 或者 resolve operations进行了写入，则其layout不为VK_IMAGE_LAYOUT_ATTACHMENT_FEEDBACK_LOOP_OPTIMAL_EXT，且有当前绑定的pipeline设有VK_PIPELINE_CREATE_DEPTH_STENCIL_ATTACHMENT_FEEDBACK_LOOP_BIT_EXT，或者
                                        最后的vkCmdSetAttachmentFeedbackLoopEnableEXT调用包含VK_IMAGE_ASPECT_DEPTH_BIT以及 没有绑定的pipeline 或者绑定的pipeline以VK_DYNAMIC_STATE_ATTACHMENT_FEEDBACK_LOOP_ENABLE_EXT创建，则该附件只能以附件进行访问的，这两种情况中之一
        69.如果一个stencil attachment在之前的该subpass的命令中以load, store, 或者 resolve operations进行了写入，则其layout不为VK_IMAGE_LAYOUT_ATTACHMENT_FEEDBACK_LOOP_OPTIMAL_EXT，且有当前绑定的pipeline设有VK_PIPELINE_CREATE_DEPTH_STENCIL_ATTACHMENT_FEEDBACK_LOOP_BIT_EXT，或者
                                        最后的vkCmdSetAttachmentFeedbackLoopEnableEXT调用包含VK_IMAGE_ASPECT_STENCIL_BIT以及 没有绑定的pipeline 或者绑定的pipeline以VK_DYNAMIC_STATE_ATTACHMENT_FEEDBACK_LOOP_ENABLE_EXT创建，则该附件只能以附件进行访问的，这两种情况中之一
        70.如果一个attachment在之前的该subpass的命令中以load, store, 或者 resolve operations进行了写入,则该附件就不能再以除作为一个附件，storage image或者sampled image被该命令访问
        71.如果在之前的命令的subpass中以用作附件外的方式访问访问了一个当权subpass的附件所对的image subresource，则该命令就不能再将该image subresource用作附件进行写入
        72.如果当前render pass使用一个depth/stencil attachment，则（1）如果depth aspect的layout为read-only的layout，则不能启用depth writes
                                                                  （2）如果stencil aspect的layout为read-only的layout，front 以及 back writeMask不为0，且stencil 测试开启，则所有stencil 操作必须为VK_STENCIL_OP_KEEP
        73.如果绑定的graphics pipeline，（1）以VK_DYNAMIC_STATE_VIEWPORT动态state开启创建，则vkCmdSetViewport必须在该命令之前设置
                                        （2）以VK_DYNAMIC_STATE_SCISSOR动态state开启创建，则vkCmdSetScissor必须在该命令之前设置
                                        （3）以VK_DYNAMIC_STATE_LINE_WIDTH动态state开启创建，则vkCmdSetLineWidth必须在该命令之前设置
                                        （4）以VK_DYNAMIC_STATE_DEPTH_BIAS动态state开启创建，则vkCmdSetDepthBias或者vkCmdSetDepthBias2EXT 必须在该命令之前设置
                                        （5）以VK_DYNAMIC_STATE_BLEND_CONSTANTS动态state开启创建，则vkCmdSetBlendConstants 必须在该命令之前设置
                                        （6）以VK_DYNAMIC_STATE_DEPTH_BOUNDS动态state开启创建，且如果当前depthBoundsTestEnable为VK_TRUE， 则vkCmdSetDepthBounds 必须在该命令之前设置
                                        （7）以VK_DYNAMIC_STATE_STENCIL_COMPARE_MASK动态state开启创建，且如果当前stencilTestEnable为VK_TRUE， 则vkCmdSetStencilCompareMask 必须在该命令之前设置
                                        （8）以VK_DYNAMIC_STATE_STENCIL_WRITE_MASK动态state开启创建，且如果当前stencilTestEnable为VK_TRUE， 则vkCmdSetStencilWriteMask 必须在该命令之前设置
                                        （9）以VK_DYNAMIC_STATE_STENCIL_REFERENCE动态state开启创建，且如果当前stencilTestEnable为VK_TRUE， 则vkCmdSetStencilReference 必须在该命令之前设置
                                        （10）以VK_DYNAMIC_STATE_SAMPLE_LOCATIONS_EXT动态state开启创建， 则vkCmdSetSampleLocationsEXT 必须在该命令之前设置
                                        （11）以VK_DYNAMIC_STATE_CULL_MODE动态state开启创建， 则vkCmdSetCullMode 必须在该命令之前设置
                                        （12）以VK_DYNAMIC_STATE_FRONT_FACE动态state开启创建， 则vkCmdSetFrontFace 必须在该命令之前设置
                                        （13）以VK_DYNAMIC_STATE_DEPTH_TEST_ENABLE动态state开启创建， 则vkCmdSetDepthTestEnable 必须在该命令之前设置
                                        （14）以VK_DYNAMIC_STATE_DEPTH_WRITE_ENABLE动态state开启创建， 则vkCmdSetDepthWriteEnable 必须在该命令之前设置
                                        （15）以VK_DYNAMIC_STATE_DEPTH_COMPARE_OP动态state开启创建， 则vkCmdSetDepthCompareOp 必须在该命令之前设置
                                        （16）以VK_DYNAMIC_STATE_DEPTH_BOUNDS_TEST_ENABLE动态state开启创建， 则vkCmdSetDepthBoundsTestEnable 必须在该命令之前设置
                                        （17）以VK_DYNAMIC_STATE_STENCIL_TEST_ENABLE动态state开启创建， 则vkCmdSetStencilTestEnable 必须在该命令之前设置
                                        （18）以VK_DYNAMIC_STATE_STENCIL_OP动态state开启创建， 则vkCmdSetStencilOp 必须在该命令之前设置
                                        （19）以VK_DYNAMIC_STATE_VIEWPORT_WITH_COUNT但不以VK_DYNAMIC_STATE_SCISSOR_WITH_COUNT 动态state开启创建， 则vkCmdSetViewportWithCount 必须在该命令之前设置，且vkCmdSetViewportWithCount设置的viewportCount必须匹配pipeline的VkPipelineViewportStateCreateInfo::scissorCount
                                        （20）以VK_DYNAMIC_STATE_SCISSOR_WITH_COUNT但不以VK_DYNAMIC_STATE_VIEWPORT_WITH_COUNT 动态state开启创建， 则vkCmdSetScissorWithCount 必须在该命令之前设置，且vkCmdSetScissorWithCount设置的scissorCount必须匹配pipeline的VkPipelineViewportStateCreateInfo::viewportCount
                                        （21）以VK_DYNAMIC_STATE_SCISSOR_WITH_COUNT和VK_DYNAMIC_STATE_VIEWPORT_WITH_COUNT 动态state同时开启创建， 则vkCmdSetViewportWithCount以及vkCmdSetScissorWithCount 必须在该命令之前设置，且vkCmdSetViewportWithCount设置的viewportCount必须匹配vkCmdSetScissorWithCount设置的scissorCount
                                        （22）以VK_DYNAMIC_STATE_VIEWPORT_WITH_COUNT但不以VK_DYNAMIC_STATE_VIEWPORT_W_SCALING_NV 动态state开启创建， 则绑定的pipeline必须以VkPipelineViewportWScalingStateCreateInfoNV::viewportCount 大于等于最近vkCmdSetViewportWithCount设置的viewportCount创建
                                        （23）以VK_DYNAMIC_STATE_VIEWPORT_WITH_COUNT和VK_DYNAMIC_STATE_VIEWPORT_W_SCALING_NV 动态state开启创建， 则最近调用的vkCmdSetViewportWScalingNV设置的viewportCount 必须大于等于最近vkCmdSetViewportWithCount设置的viewportCount
                                        （24）以VK_DYNAMIC_STATE_VIEWPORT_WITH_COUNT但不以VK_DYNAMIC_STATE_VIEWPORT_SHADING_RATE_PALETTE_NV 动态state开启创建， 则绑定的pipeline必须以VkPipelineViewportShadingRateImageStateCreateInfoNV::viewportCount 大于等于最近vkCmdSetViewportWithCount设置的viewportCount创建
                                        （25）以VK_DYNAMIC_STATE_VIEWPORT_WITH_COUNT和VK_DYNAMIC_STATE_VIEWPORT_SHADING_RATE_PALETTE_NV 动态state开启创建， 则最近调用的vkCmdSetViewportShadingRatePaletteNV设置的viewportCount 必须大于等于最近vkCmdSetViewportWithCount设置的viewportCount
                                        （26）以VK_DYNAMIC_STATE_VIEWPORT_WITH_COUNT动态state开启且VkPipelineViewportStateCreateInfo的pNext中含有一个VkPipelineViewportSwizzleStateCreateInfoNV 创建， 则绑定的pipeline必须以VkPipelineViewportSwizzleStateCreateInfoNV::viewportCount 大于等于最近vkCmdSetViewportWithCount设置的viewportCount创建
                                        （27）以VK_DYNAMIC_STATE_VIEWPORT_WITH_COUNT动态state开启且VkPipelineViewportStateCreateInfo的pNext中含有一个VkPipelineViewportExclusiveScissorStateCreateInfoNV 创建， 则绑定的pipeline必须以VkPipelineViewportExclusiveScissorStateCreateInfoNV::exclusiveScissorCount 大于等于最近vkCmdSetViewportWithCount设置的viewportCount创建
                                        （28）以VK_DYNAMIC_STATE_EXCLUSIVE_SCISSOR_ENABLE_NV动态state开启创建， 则vkCmdSetExclusiveScissorEnableNV 必须在该命令之前设置
                                        （29）以VK_DYNAMIC_STATE_EXCLUSIVE_SCISSOR_NV动态state开启创建， 则vkCmdSetExclusiveScissorNV 必须在该命令之前设置
                                        （30）以VK_DYNAMIC_STATE_RASTERIZER_DISCARD_ENABLE动态state开启创建， 则vkCmdSetRasterizerDiscardEnable 必须在该命令之前设置
                                        （31）以VK_DYNAMIC_STATE_DEPTH_BIAS_ENABLE动态state开启创建， 则vkCmdSetDepthBiasEnable 必须在该命令之前设置
                                        （32）以VK_DYNAMIC_STATE_LOGIC_OP_EXT动态state开启创建， 则vkCmdSetLogicOpEXT 必须在该命令之前设置且参数logicOp必须是一个有效的VkLogicOp值
        74.如果一个shader object绑定到任何graphics stage，且最靠近当前命令的vkCmdSetRasterizerDiscardEnable设置rasterizerDiscardEnable为VK_FALSE，则
                                        （1）如果最靠近当前命令的vkCmdSetPolygonModeEXT设置polygonMode为VK_POLYGON_MODE_LINE或者是任何line topology，则vkCmdSetLineWidth必须在该命令之前设置
                                        （2）如果最靠近当前命令的vkCmdSetDepthBiasEnable设置depthBiasEnable为VK_TRUE，则vkCmdSetDepthBias 或者 vkCmdSetDepthBias2EXT必须在该命令之前设置
                                        （3）如果最靠近当前命令的vkCmdSetDepthBoundsTestEnable设置depthBoundsTestEnable为VK_TRUE，则vkCmdSetDepthBounds必须在该命令之前设置
                                        （4）如果最靠近当前命令的vkCmdSetStencilTestEnable设置stencilTestEnable为VK_TRUE，则vkCmdSetStencilCompareMask必须在该命令之前设置
                                        （5）如果最靠近当前命令的vkCmdSetStencilTestEnable设置stencilTestEnable为VK_TRUE，则vkCmdSetStencilWriteMask必须在该命令之前设置
                                        （6）如果最靠近当前命令的vkCmdSetStencilTestEnable设置stencilTestEnable为VK_TRUE，则vkCmdSetStencilReference必须在该命令之前设置
                                        （7）如果最靠近当前命令的vkCmdSetSampleLocationsEnableEXT设置sampleLocationsEnable为VK_TRUE，则vkCmdSetSampleLocationsEXT必须在该命令之前设置
                                        （8）则vkCmdSetCullMode必须在该命令之前设置
                                        （9）则vkCmdSetFrontFace必须在该命令之前设置
                                        （10）则vkCmdSetDepthTestEnable 必须在该命令之前设置
                                        （11）则vkCmdSetDepthWriteEnable 必须在该命令之前设置
                                        （12）如果最靠近当前命令的vkCmdSetDepthTestEnable设置depthTestEnable为VK_TRUE，则vkCmdSetDepthCompareOp 必须在该命令之前设置
                                        （13）则vkCmdSetDepthBoundsTestEnable 必须在该命令之前设置
                                        （14）则vkCmdSetStencilTestEnable 必须在该命令之前设置
                                        （15）如果最靠近当前命令的vkCmdSetStencilTestEnable设置stencilTestEnable为VK_TRUE，则vkCmdSetStencilOp 必须在该命令之前设置
                                        （16）
                                        （17）如果shadingRateImage特性开启，则vkCmdSetCoarseSampleOrderNV 必须在该命令之前设置
                                        （18）如果shadingRateImage特性开启，且最靠近当前命令的vkCmdSetShadingRateImageEnableNV设置shadingRateImageEnable为VK_TRUE，则vkCmdSetViewportShadingRatePaletteNV 必须在该命令之前设置
                                        （19）如果shadingRateImage特性开启，且最靠近当前命令的vkCmdSetShadingRateImageEnableNV设置shadingRateImageEnable为VK_TRUE，则最近的vkCmdSetViewportShadingRatePaletteNV设置的viewportCount 必须大于等于vkCmdSetViewportWithCount设置的viewportCount
                                        （20）则vkCmdSetDepthBiasEnable必须在该命令之前设置
        75.如果一个输出line primitives的shader object绑定到VK_SHADER_STAGE_TESSELLATION_EVALUATION_BIT 或者 VK_SHADER_STAGE_GEOMETRY_BIT，且最靠近当前命令的vkCmdSetRasterizerDiscardEnable设置rasterizerDiscardEnable为VK_FALSE，则vkCmdSetLineWidth必须在该命令之前设置
        76.如果一个shader object绑定到VK_SHADER_STAGE_FRAGMENT_BIT stage，且最靠近当前命令的vkCmdSetRasterizerDiscardEnable设置rasterizerDiscardEnable为VK_FALSE，且最靠近当前命令的vkCmdSetColorBlendEnableEXT设置pColorBlendEnables任何元素为VK_TRUE，且
                            最靠近当前命令的vkCmdSetColorBlendEquationEXT设置pColorBlendEquations相同元素的VkColorBlendEquationEXT的VkBlendFactor成员为VK_BLEND_FACTOR_CONSTANT_COLOR, VK_BLEND_FACTOR_ONE_MINUS_CONSTANT_COLOR, VK_BLEND_FACTOR_CONSTANT_ALPHA, 或者 VK_BLEND_FACTOR_ONE_MINUS_CONSTANT_ALPHA，则vkCmdSetBlendConstants必须在该命令之前设置
        77.如果该命令记录在开启了multiview的render pass instance中，则最大的instance 索引必须小于等于VkPhysicalDeviceMultiviewProperties::maxMultiviewInstanceIndex
        78.如果绑定的graphics pipeline以VkPipelineSampleLocationsStateCreateInfoEXT::sampleLocationsEnable设置为VK_TRUE创建且当前的subpass含有一个 depth/stencil attachment，则该attachment必须以VK_IMAGE_CREATE_SAMPLE_LOCATIONS_COMPATIBLE_DEPTH_BIT_EXT创建
        >>78.5  .如果一个shader object绑定到任何graphics stage，则则（1）vkCmdSetViewportWithCount 和vkCmdSetScissorWithCount 必须同时在该命令之前设置，且vkCmdSetViewportWithCount设置的viewportCount必须匹配vkCmdSetScissorWithCount设置的scissorCount
                                                                    （2）则vkCmdSetRasterizerDiscardEnable 必须在该命令之前设置
        79.如果VK_NV_clip_space_w_scaling拓展开启，且shader object绑定到任何graphics stage，且最近的vkCmdSetViewportWScalingEnableNV设置viewportWScalingEnable为VK_TRUE，则（1）vkCmdSetViewportWScalingNV必须在该命令前设置
                                                                                                                                                                           （2）最近vkCmdSetViewportWScalingNV设置的viewportCount必须大于等于vkCmdSetViewportWithCount设置的viewportCount
        80.如果exclusiveScissor 特性开启，且shader object绑定到任何graphics stage，，则（1）vkCmdSetExclusiveScissorEnableNV必须在该命令前设置
                                                                                       （2）最近的vkCmdSetExclusiveScissorEnableNV调用设置的pExclusiveScissorEnables中的任何元素为VK_TRUE,则vkCmdSetExclusiveScissorNV必须在该命令前设置
        81.如果一个shader object绑定到VK_SHADER_STAGE_FRAGMENT_BIT stage，且最靠近当前命令的vkCmdSetRasterizerDiscardEnable设置rasterizerDiscardEnable为VK_FALSE，且最靠近当前命令的vkCmdSetLogicOpEnableEXT设置logicOpEnable任何元素为VK_TRUE，则vkCmdSetLogicOpEXT 必须在该命令之前设置且参数logicOp必须是一个有效的VkLogicOp值
        82.如果primitiveFragmentShadingRateWithMultipleViewports限制不支持，则（1）如果绑定的graphics pipeline以VK_DYNAMIC_STATE_VIEWPORT_WITH_COUNT动态state开启创建，且任何该pipeline的shader stage会写入PrimitiveShadingRateKHR built-in修饰的变量，则vkCmdSetViewportWithCount 必须在该命令之前设置且参数viewportCount必须是1
                                                                              （2）任何绑定的graphics pipeline的shader stage会写入PrimitiveShadingRateKHR built-in修饰的变量，则vkCmdSetViewportWithCount 必须在该命令之前设置且参数viewportCount必须是1
        83.如果graphics pipeline中未开启rasterization，则对subpass中的每个color attachment，如果其对应的image view 的format features不包含VK_FORMAT_FEATURE_COLOR_ATTACHMENT_BLEND_BIT，则pColorBlendState中其对应pAttachments中元素的blendEnable必须为VK_FALSE
        84.如果一个shader object绑定到VK_SHADER_STAGE_FRAGMENT_BIT stage，且最靠近当前命令的vkCmdSetRasterizerDiscardEnable设置rasterizerDiscardEnable为VK_FALSE，则对于render pass中的每个color attachment，如果其对应的image view 的format features不包含VK_FORMAT_FEATURE_COLOR_ATTACHMENT_BLEND_BIT， 则最近的vkCmdSetColorBlendEnableEXT设置的pColorBlendEnables中该附件的对应元素必须为VK_FALSE
        85.如果graphics pipeline中未开启rasterization，有VK_AMD_mixed_attachment_samples拓展未开启，VK_NV_framebuffer_mixed_samples拓展未开启，multisampledRenderToSingleSampled特性未开启，则当前绑定的pipeline的rasterizationSamples必须和当前subpass的color 以及/或者 depth/stencil attachments的相同
        86.如果一个shader object绑定到任何graphics stage，且最近的vkCmdSetRasterizerDiscardEnable设置rasterizerDiscardEnable为VK_FALSE，且有VK_AMD_mixed_attachment_samples拓展未开启，VK_NV_framebuffer_mixed_samples拓展未开启，multisampledRenderToSingleSampled特性未开启，则最近vkCmdSetRasterizationSamplesEXT设置的rasterizationSamples必须和当前subpass的color 以及/或者 depth/stencil attachments的相同
        87.如果一个shader object绑定到任何graphics stage，则当前的render pass instance必须以vkCmdBeginRendering开始
        88.如果当前的render pass instance以vkCmdBeginRendering开始，（1）如果pDepthAttachment的imageView不为VK_NULL_HANDLE，且pDepthAttachment的layout不为VK_IMAGE_LAYOUT_DEPTH_STENCIL_READ_ONLY_OPTIMAL，则该命令不能写入任何值到depth attachment
                                                                    （2）如果pStencilAttachment的imageView不为VK_NULL_HANDLE，且pStencilAttachment的layout不为VK_IMAGE_LAYOUT_DEPTH_STENCIL_READ_ONLY_OPTIMAL，则该命令不能写入任何值到stencil attachment
                                                                    （3）如果pDepthAttachment的imageView不为VK_NULL_HANDLE，且pDepthAttachment的layout为VK_IMAGE_LAYOUT_DEPTH_READ_ONLY_STENCIL_ATTACHMENT_OPTIMAL，则该命令不能写入任何值到depth attachment
                                                                    （4）如果pStencilAttachment的imageView不为VK_NULL_HANDLE，且pStencilAttachment的layout为VK_IMAGE_LAYOUT_DEPTH_ATTACHMENT_STENCIL_READ_ONLY_OPTIMAL，则该命令不能写入任何值到stencil attachment
                                                                    （5）如果pDepthAttachment的imageView不为VK_NULL_HANDLE，且pDepthAttachment的layout为VK_IMAGE_LAYOUT_DEPTH_READ_ONLY_OPTIMAL，则该命令不能写入任何值到depth attachment
                                                                    （6）如果pStencilAttachment的imageView不为VK_NULL_HANDLE，且pStencilAttachment的layout为VK_IMAGE_LAYOUT_STENCIL_READ_ONLY_OPTIMAL，则该命令不能写入任何值到stencil attachment
                                                                    （7）则当前绑定的graphics pipeline必须以含VkPipelineRenderingCreateInfo::viewMask等于VkRenderingInfo::viewMask创建
                                                                    （8）如果带有VkRenderingInfo::colorAttachmentCount为1，则没有shader object绑定到任何graphics stage，且一个color attachment的 resolve mode为VK_RESOLVE_MODE_EXTERNAL_FORMAT_DOWNSAMPLE_ANDROID，则VkRenderingInfo::pColorAttachments中每个resolveImageView不为VK_NULL_HANDLE的元素其对应image必须以和创建当前绑定的pipeline 相同的VkExternalFormatANDROID::externalFormat创建
                                                                    （9）如果没有shader object绑定到任何graphics stage，如果绑定的graphics pipeline以一个非零值VkExternalFormatANDROID::externalFormat创建且启用VK_DYNAMIC_STATE_COLOR_BLEND_ENABLE_EXT动态设置，则vkCmdSetColorBlendEnableEXT必须在该命令前设置blend enable为VK_FALSE
                                                                    （10）如果没有shader object绑定到任何graphics stage，如果绑定的graphics pipeline以一个非零值VkExternalFormatANDROID::externalFormat创建且启用VK_DYNAMIC_STATE_RASTERIZATION_SAMPLES_EXT动态设置，则vkCmdSetRasterizationSamplesEXT必须在该命令前设置rasterizationSamples为VK_SAMPLE_COUNT_1_BIT
                                                                    （11）如果没有shader object绑定到任何graphics stage，如果绑定的graphics pipeline以一个非零值VkExternalFormatANDROID::externalFormat创建且启用VK_DYNAMIC_STATE_FRAGMENT_SHADING_RATE_KHR动态设置，则vkCmdSetFragmentShadingRateKHR必须在该命令前设置pFragmentSize->width为1，pFragmentSize->height为1
        89.如果dynamicRenderingUnusedAttachments特性未开启，且当前的render pass instance以vkCmdBeginRendering开始，则
                                                                （1）当前绑定的graphics pipeline必须以含VkPipelineRenderingCreateInfo::colorAttachmentCount等于VkRenderingInfo::colorAttachmentCount创建
                                                                （2）如果VkRenderingInfo::colorAttachmentCount大于0，则VkRenderingInfo::pColorAttachments 中每一个其imageView不为VK_NULL_HANDLE的元素的VkImageView必须以VkFormat对应绑定的graphics pipeline的VkPipelineRenderingCreateInfo::pColorAttachmentFormats指明的format创建
                                                                （3）如果VkRenderingInfo::colorAttachmentCount大于0，则VkRenderingInfo::pColorAttachments 中每一个其imageView为VK_NULL_HANDLE的元素对应绑定的graphics pipeline的VkPipelineRenderingCreateInfo::pColorAttachmentFormats指明的format必须为VK_FORMAT_UNDEFINED
                                                                （4）如果VkRenderingInfo::pDepthAttachment->imageView为VK_NULL_HANDLE，则创建当前绑定的graphics pipeline的VkPipelineRenderingCreateInfo::depthAttachmentFormat必须为VK_FORMAT_UNDEFINED
                                                                （5）如果VkRenderingInfo::pDepthAttachment->imageView不为VK_NULL_HANDLE，则创建当前绑定的graphics pipeline的VkPipelineRenderingCreateInfo::depthAttachmentFormat必须和创建VkRenderingInfo::pDepthAttachment->imageView的VkFormat相同
                                                                （6）如果VkRenderingInfo::pStencilAttachment->imageView为VK_NULL_HANDLE，则创建当前绑定的graphics pipeline的VkPipelineRenderingCreateInfo::stencilAttachmentFormat必须为VK_FORMAT_UNDEFINED
                                                                （7）如果VkRenderingInfo::pStencilAttachment->imageView不为VK_NULL_HANDLE，则创建当前绑定的graphics pipeline的VkPipelineRenderingCreateInfo::stencilAttachmentFormat必须和创建VkRenderingInfo::pStencilAttachment->imageView的VkFormat相同
        90.如果dynamicRenderingUnusedAttachments特性开启，且当前的render pass instance以vkCmdBeginRendering开始，则
                                                                （1）如果VkRenderingInfo::colorAttachmentCount大于0，则VkRenderingInfo::pColorAttachments 中每一个其imageView不为VK_NULL_HANDLE的元素的VkImageView必须以VkFormat对应绑定的graphics pipeline的VkPipelineRenderingCreateInfo::pColorAttachmentFormats指明的format创建，或者是对应元素为VK_FORMAT_UNDEFINED创建
                                                                （2）如果VkRenderingInfo::pDepthAttachment->imageView不为VK_NULL_HANDLE，且创建当前绑定的graphics pipeline的VkPipelineRenderingCreateInfo::depthAttachmentFormat和创建VkRenderingInfo::pDepthAttachment->imageView的VkFormat不同，则该format必须为VK_FORMAT_UNDEFINED
                                                                （3）如果VkRenderingInfo::pStencilAttachment->imageView不为VK_NULL_HANDLE，且创建当前绑定的graphics pipeline的VkPipelineRenderingCreateInfo::stencilAttachmentFormat和创建VkRenderingInfo::pStencilAttachment->imageView的VkFormat不同，则该format必须为VK_FORMAT_UNDEFINED
        91.如果没有shader object绑定到任何graphics stage，且当前的render pass instance以vkCmdBeginRendering开始且VkRenderingInfo::colorAttachmentCount为1，且一个color attachment的 resolve mode为VK_RESOLVE_MODE_EXTERNAL_FORMAT_DOWNSAMPLE_ANDROID，则VkRenderingInfo::pColorAttachments中每个resolveImageView不为VK_NULL_HANDLE的元素其对应image必须以和创建当前绑定的pipeline 相同的VkExternalFormatANDROID::externalFormat创建
        92.如果有一个shader object绑定到任何graphics stage，且当前的render pass 包含一个使用VK_RESOLVE_MODE_EXTERNAL_FORMAT_DOWNSAMPLE_ANDROID resolve mode的color attachment，则（1）vkCmdSetColorBlendEnableEXT必须在该命令前设置blend enable为VK_FALSE
                                                                                                                                                                                 （2）则vkCmdSetRasterizationSamplesEXT必须在该命令前设置rasterizationSamples为VK_SAMPLE_COUNT_1_BIT
                                                                                                                                                                                 （3）则vkCmdSetFragmentShadingRateKHR必须在该命令前设置pFragmentSize->width为1，pFragmentSize->height为1
        93.如果绑定的graphics pipeline，（1）以VK_DYNAMIC_STATE_COLOR_WRITE_ENABLE_EXT动态state开启创建， 则vkCmdSetColorWriteEnableEXT 必须在该命令之前设置，且设置的attachmentCount必须大于等于创建当前绑定的pipeline的VkPipelineColorBlendStateCreateInfo::attachmentCount
                                        （2）以VK_DYNAMIC_STATE_DISCARD_RECTANGLE_EXT动态state开启创建， 则vkCmdSetDiscardRectangleEXT 必须在该命令之前为每个VkPipelineDiscardRectangleStateCreateInfoEXT::discardRectangleCount指明的discard rectangle 设置
                                        （3）以VK_DYNAMIC_STATE_DISCARD_RECTANGLE_ENABLE_EXT动态state开启创建， 则vkCmdSetDiscardRectangleEnableEXT 必须在该命令之前设置
                                        （4）以VK_DYNAMIC_STATE_DISCARD_RECTANGLE_MODE_EXT动态state开启创建， 则vkCmdSetDiscardRectangleModeEXT 必须在该命令之前设置
        94.如果有一个shader object绑定到VK_SHADER_STAGE_FRAGMENT_BIT stage，且最靠近当前命令的vkCmdSetRasterizerDiscardEnable设置rasterizerDiscardEnable为VK_FALSE，则
                                        （1）如果colorWriteEnable特性在device上开启，则vkCmdSetColorWriteEnableEXT 必须在该命令之前设置，且设置的attachmentCount必须大于等于当前render pass instance的color attachment的数量
                                        （2）如果VK_EXT_discard_rectangles拓展开启，且最近的vkCmdSetDiscardRectangleEnableEXT设置discardRectangleEnable为VK_TRUE， 则vkCmdSetDiscardRectangleEXT 必须在该命令之前设置
                                        （3）如果VK_EXT_discard_rectangles拓展开启， 则vkCmdSetDiscardRectangleEnableEXT 必须在该命令之前设置
                                        （4）如果VK_EXT_discard_rectangles拓展开启， 则最近的vkCmdSetDiscardRectangleEnableEXT设置discardRectangleEnable为VK_TRUE，则vkCmdSetDiscardRectangleModeEXT 必须在该命令之前设置
        95.如果当前的render pass instance以vkCmdBeginRendering开始，则（1）如果VkRenderingFragmentShadingRateAttachmentInfoKHR::imageView不为VK_NULL_HANDLE，则当前绑定的graphics pipeline必须以VK_PIPELINE_CREATE_RENDERING_FRAGMENT_SHADING_RATE_ATTACHMENT_BIT_KHR创建
                                                                      （2）如果VkRenderingFragmentDensityMapAttachmentInfoEXT::imageView不为VK_NULL_HANDLE，则当前绑定的graphics pipeline必须以VK_PIPELINE_CREATE_RENDERING_FRAGMENT_DENSITY_MAP_ATTACHMENT_BIT_EXT创建
                                                                      （3）且含VkRenderingInfo::colorAttachmentCount大于0，如果当前的绑定的pipeline以含有一个VkAttachmentSampleCountInfoAMD或者VkAttachmentSampleCountInfoNV创建，则VkRenderingInfo::pColorAttachments中每个imageView不为VK_NULL_HANDLE的元素的imageView，必须以当前pipeline的VkAttachmentSampleCountInfoAMD 或者 VkAttachmentSampleCountInfoNV中的pColorAttachmentSamples中对应元素的sample count进行创建
                                                                      （4）如果当前的绑定的pipeline以含有一个VkAttachmentSampleCountInfoAMD或者VkAttachmentSampleCountInfoNV创建，且VkRenderingInfo::pDepthAttachment中的imageView不为VK_NULL_HANDLE，则当前pipeline的VkAttachmentSampleCountInfoAMD 或者 VkAttachmentSampleCountInfoNV中的depthStencilAttachmentSamples必须等于创建VkRenderingInfo::pDepthAttachment->imageView的sample count
                                                                      （5）如果当前的绑定的pipeline以含有一个VkAttachmentSampleCountInfoAMD或者VkAttachmentSampleCountInfoNV创建，且VkRenderingInfo::pStencilAttachment中的imageView不为VK_NULL_HANDLE，则当前pipeline的VkAttachmentSampleCountInfoAMD 或者 VkAttachmentSampleCountInfoNV中的depthStencilAttachmentSamples必须等于创建VkRenderingInfo::pStencilAttachment->imageView的sample count
                                                                      （6）且含VkRenderingInfo::colorAttachmentCount大于0，如果当前的绑定的pipeline不以含有一个VkAttachmentSampleCountInfoAMD或者VkAttachmentSampleCountInfoNV创建，且multisampledRenderToSingleSampled特性没有开启，则VkRenderingInfo::pColorAttachments中每个imageView不为VK_NULL_HANDLE的元素的imageView，其创建的sample count必须等于当前绑定的graphics pipeline的rasterizationSamples
                                                                      （7）如果当前的绑定的pipeline不以含有一个VkAttachmentSampleCountInfoAMD或者VkAttachmentSampleCountInfoNV创建，且VkRenderingInfo::pDepthAttachment中的imageView不为VK_NULL_HANDLE，且multisampledRenderToSingleSampled特性没有开启，则当前pipeline的rasterizationSamples 必须等于创建VkRenderingInfo::pDepthAttachment->imageView的sample count
                                                                      （8）如果当前的绑定的pipeline不以含有一个VkAttachmentSampleCountInfoAMD或者VkAttachmentSampleCountInfoNV创建，且VkRenderingInfo::pStencilAttachment中的imageView不为VK_NULL_HANDLE，且multisampledRenderToSingleSampled特性没有开启，则当前pipeline的rasterizationSamples 必须等于创建VkRenderingInfo::pStencilAttachment->imageView的sample count
                                                                      （9）当前绑定的pipeline必须VkGraphicsPipelineCreateInfo::renderPass为VK_NULL_HANDLE创建
                                                                      （10）如果绑定的pipeline的fragment shader静态写入一个color attachment，且color write mask不为0，启用了color writes，且该附件对应的VkRenderingInfo::pColorAttachments->imageView 不为VK_NULL_HANDLE，则对应的创建pipeline的VkPipelineRenderingCreateInfo::pColorAttachmentFormats中的元素不能为VK_FORMAT_UNDEFINED
                                                                      （11）如果绑定的pipeline启用了depth test，启用了depth writes，且VkRenderingInfo::pDepthAttachment->imageView 不为VK_NULL_HANDLE，则创建pipeline的VkPipelineRenderingCreateInfo::depthAttachmentFormat不能为VK_FORMAT_UNDEFINED
                                                                      （12）如果绑定的pipeline启用了stencil test，且VkRenderingInfo::pStencilAttachment->imageView 不为VK_NULL_HANDLE，则创建pipeline的VkPipelineRenderingCreateInfo::stencilAttachmentFormat不能为VK_FORMAT_UNDEFINED
        96.如果该命令在以vkCmdBeginRendering开始的render pass instance中调用，且VkRenderingInfo的pNext中包含一个multisampledRenderToSingleSampledEnable设为VK_TRUE的VkMultisampledRenderToSingleSampledInfoEXT，则当前绑定的graphics pipeline的rasterizationSamples必须等于VkMultisampledRenderToSingleSampledInfoEXT::rasterizationSamples
        97.如果primitivesGeneratedQueryWithRasterizerDiscard特性未开启，且VK_QUERY_TYPE_PRIMITIVES_GENERATED_EXT query激活，则不能启用rasterization discard
        98如果primitivesGeneratedQueryWithNonZeroStreams特性未开启，且VK_QUERY_TYPE_PRIMITIVES_GENERATED_EXT query激活，则 绑定的graphics pipeline不能以VkPipelineRasterizationStateStreamCreateInfoEXT::rasterizationStream为非零值创建
        98.如果绑定的graphics pipeline，（1）以VK_DYNAMIC_STATE_TESSELLATION_DOMAIN_ORIGIN_EXT动态state开启创建，则vkCmdSetTessellationDomainOriginEXT必须在该命令之前设置
                                        （2）以VK_DYNAMIC_STATE_DEPTH_CLAMP_ENABLE_EXT动态state开启创建，则vkCmdSetDepthClampEnableEXT必须在该命令之前设置
                                        （3）以VK_DYNAMIC_STATE_POLYGON_MODE_EXT动态state开启创建，则vkCmdSetPolygonModeEXT必须在该命令之前设置
                                        （4）以VK_DYNAMIC_STATE_RASTERIZATION_SAMPLES_EXT动态state开启创建，则vkCmdSetRasterizationSamplesEXT必须在该命令之前设置
                                        （5）以VK_DYNAMIC_STATE_SAMPLE_MASK_EXT动态state开启创建，则vkCmdSetSampleMaskEXT必须在该命令之前设置
                                        （6）以VK_DYNAMIC_STATE_ALPHA_TO_COVERAGE_ENABLE_EXT动态state开启创建，则vkCmdSetAlphaToCoverageEnableEXT必须在该命令之前设置
                                        （7）以VK_DYNAMIC_STATE_ALPHA_TO_COVERAGE_ENABLE_EXT动态state开启创建，则最近的vkCmdSetAlphaToCoverageEnableEXT设置alphaToCoverageEnable为VK_TRUE，则Fragment Output Interface中 Index 0的Location 0必须有一个含alpha Component的变量
                                        （8）以VK_DYNAMIC_STATE_ALPHA_TO_ONE_ENABLE_EXT动态state开启创建，则vkCmdSetAlphaToOneEnableEXT必须在该命令之前设置
                                        （9）以VK_DYNAMIC_STATE_LOGIC_OP_ENABLE_EXT动态state开启创建，则vkCmdSetLogicOpEnableEXT必须在该命令之前设置
                                        （10）以VK_DYNAMIC_STATE_COLOR_BLEND_ENABLE_EXT动态state开启创建，则vkCmdSetColorBlendEnableEXT必须在该命令之前设置
                                        （11）以VK_DYNAMIC_STATE_COLOR_BLEND_EQUATION_EXT动态state开启创建，则vkCmdSetColorBlendEquationEXT必须在该命令之前设置
                                        （12）以VK_DYNAMIC_STATE_COLOR_WRITE_MASK_EXT动态state开启创建，则vkCmdSetColorWriteMaskEXT必须在该命令之前设置

        99.如果一个shader object绑定到VK_SHADER_STAGE_TESSELLATION_EVALUATION_BIT stage，则vkCmdSetTessellationDomainOriginEXT必须在该命令之前设置
        100.如果一个shader object绑定到任何graphics stage，且最近的vkCmdSetRasterizerDiscardEnable设置rasterizerDiscardEnable为VK_FALSE，则
                                                        （1）如果depthClamp特性启用，则vkCmdSetDepthClampEnableEXT必须在该命令之前设置
                                                        （2）则vkCmdSetPolygonModeEXT必须在该命令之前设置
                                                        （3）则vkCmdSetRasterizationSamplesEXT必须在该命令之前设置
                                                        （4）则vkCmdSetSampleMaskEXT必须在该命令之前设置
                                                        （5）则vkCmdSetAlphaToCoverageEnableEXT必须在该命令之前设置
                                                        （6）如果alphaToOne特性启用，则vkCmdSetAlphaToOneEnableEXT必须在该命令之前设置

        101.如果一个shader object绑定到任何graphics stage，且最近的vkCmdSetAlphaToCoverageEnableEXT设置alphaToCoverageEnable为VK_TRUE，则Fragment Output Interface中 Index 0的Location 0必须有一个含alpha Component的变量
        102.如果一个shader object绑定到VK_SHADER_STAGE_FRAGMENT_BIT stage，且最近的vkCmdSetRasterizerDiscardEnable设置rasterizerDiscardEnable为VK_FALSE，则
                                            （1）如果logicOp特性开启 ,vkCmdSetLogicOpEnableEXT必须在该命令之前设置
                                            （2）如果绑定了color attachments，则vkCmdSetColorBlendEnableEXT必须在该命令之前设置
                                            （3）如果最近的vkCmdSetColorBlendEnableEXT设置任何附件在pColorBlendEnables中的值为VK_TRUE ，则vkCmdSetColorBlendEquationEXT必须在该命令之前设置
                                            （4）如果绑定了color attachments，则vkCmdSetColorWriteMaskEXT必须在该命令之前设置
        103.如果绑定的graphics pipeline，（1）以VK_DYNAMIC_STATE_RASTERIZATION_STREAM_EXT动态state开启创建，则vkCmdSetRasterizationStreamEXT必须在该命令之前设置
                                         （2）以VK_DYNAMIC_STATE_CONSERVATIVE_RASTERIZATION_MODE_EXT动态state开启创建，则vkCmdSetConservativeRasterizationModeEXT必须在该命令之前设置
                                         （3）以VK_DYNAMIC_STATE_EXTRA_PRIMITIVE_OVERESTIMATION_SIZE_EXT动态state开启创建，则vkCmdSetExtraPrimitiveOverestimationSizeEXT必须在该命令之前设置
                                         （4）以VK_DYNAMIC_STATE_DEPTH_CLIP_ENABLE_EXT动态state开启创建，则vkCmdSetDepthClipEnableEXT必须在该命令之前设置
                                         （5）以VK_DYNAMIC_STATE_SAMPLE_LOCATIONS_ENABLE_EXT动态state开启创建，则vkCmdSetSampleLocationsEnableEXT必须在该命令之前设置
                                         （6）以VK_DYNAMIC_STATE_COLOR_BLEND_ADVANCED_EXT动态state开启创建，则vkCmdSetColorBlendAdvancedEXT必须在该命令之前设置
                                         （7）以VK_DYNAMIC_STATE_PROVOKING_VERTEX_MODE_EXT动态state开启创建，则vkCmdSetProvokingVertexModeEXT必须在该命令之前设置
                                         （8）以VK_DYNAMIC_STATE_LINE_RASTERIZATION_MODE_EXT动态state开启创建，则vkCmdSetLineRasterizationModeEXT必须在该命令之前设置
                                         （9）以VK_DYNAMIC_STATE_LINE_STIPPLE_ENABLE_EXT动态state开启创建，则vkCmdSetLineStippleEnableEXT必须在该命令之前设置
                                         （10）以VK_DYNAMIC_STATE_LINE_STIPPLE_KHR动态state开启创建，则vkCmdSetLineStippleKHR必须在该命令之前设置
                                         （11）以VK_DYNAMIC_STATE_DEPTH_CLIP_NEGATIVE_ONE_TO_ONE_EXT动态state开启创建，则vkCmdSetDepthClipNegativeOneToOneEXT必须在该命令之前设置
                                         （12）以VK_DYNAMIC_STATE_VIEWPORT_W_SCALING_ENABLE_NV动态state开启创建，则vkCmdSetViewportWScalingEnableNV必须在该命令之前设置
                                         （13）以VK_DYNAMIC_STATE_VIEWPORT_SWIZZLE_NV动态state开启创建，则vkCmdSetViewportSwizzleNV必须在该命令之前设置
                                         （14）以VK_DYNAMIC_STATE_COVERAGE_TO_COLOR_ENABLE_NV动态state开启创建，则vkCmdSetCoverageToColorEnableNV必须在该命令之前设置
                                         （15）以VK_DYNAMIC_STATE_COVERAGE_TO_COLOR_LOCATION_NV动态state开启创建，则vkCmdSetCoverageToColorLocationNV必须在该命令之前设置
                                         （16）以VK_DYNAMIC_STATE_COVERAGE_MODULATION_MODE_NV动态state开启创建，则vkCmdSetCoverageModulationModeNV必须在该命令之前设置
                                         （17）以VK_DYNAMIC_STATE_COVERAGE_MODULATION_TABLE_ENABLE_NV动态state开启创建，则vkCmdSetCoverageModulationTableEnableNV必须在该命令之前设置
                                         （18）以VK_DYNAMIC_STATE_COVERAGE_MODULATION_TABLE_NV动态state开启创建，则vkCmdSetCoverageModulationTableNV必须在该命令之前设置
                                         （19）以VK_DYNAMIC_STATE_SHADING_RATE_IMAGE_ENABLE_NV动态state开启创建，则vkCmdSetShadingRateImageEnableNV必须在该命令之前设置
                                         （20）以VK_DYNAMIC_STATE_REPRESENTATIVE_FRAGMENT_TEST_ENABLE_NV动态state开启创建，则vkCmdSetRepresentativeFragmentTestEnableNV必须在该命令之前设置
                                         （21）以VK_DYNAMIC_STATE_COVERAGE_REDUCTION_MODE_NV动态state开启创建，则vkCmdSetCoverageReductionModeNV必须在该命令之前设置

        104.如果一个shader object绑定到VK_SHADER_STAGE_GEOMETRY_BIT stage，且如果geometryStreams 特性开启，则vkCmdSetRasterizationStreamEXT必须在该命令之前设置
        105.如果一个shader object绑定到任何graphics stage，且最近的vkCmdSetRasterizerDiscardEnable设置rasterizerDiscardEnable为VK_FALSE，则
                                （1）如果VK_EXT_conservative_rasterization 拓展开启，vkCmdSetConservativeRasterizationModeEXT必须在该命令之前设置
                                （2）如果VK_EXT_conservative_rasterization 拓展开启，且最近的vkCmdSetConservativeRasterizationModeEXT设置conservativeRasterizationMode为VK_CONSERVATIVE_RASTERIZATION_MODE_OVERESTIMATE_EXT，则vkCmdSetExtraPrimitiveOverestimationSizeEXT必须在该命令之前设置
                                （3）如果VK_EXT_sample_locations 拓展开启，则vkCmdSetSampleLocationsEnableEXT必须在该命令之前设置
        106.如果一个shader object绑定到任何graphics stage，且depthClipEnable 特性开启，则vkCmdSetDepthClipEnableEXT必须在该命令之前设置
        107.如果如果一个shader object绑定到任何VK_SHADER_STAGE_FRAGMENT_BIT stage，且最近的vkCmdSetRasterizerDiscardEnable设置rasterizerDiscardEnable为VK_FALSE，且如果VK_EXT_blend_operation_advanced 拓展开启，则vkCmdSetColorBlendEquationEXT 和 vkCmdSetColorBlendAdvancedEXT中至少一个必须在该命令之前设置
        108.如果一个shader object绑定到VK_SHADER_STAGE_VERTEX_BIT stage，且最近的vkCmdSetRasterizerDiscardEnable设置rasterizerDiscardEnable为VK_FALSE，如果VK_EXT_provoking_vertex拓展开启， 则vkCmdSetProvokingVertexModeEXT必须在该命令之前设置
        109.如果VK_KHR_line_rasterization 或者 VK_EXT_line_rasterization拓展开启，则（1）如果一个shader object绑定到任意一个graphics stage，且最近的vkCmdSetRasterizerDiscardEnable设置rasterizerDiscardEnable为VK_FALSE，且最近的vkCmdSetPolygonModeEXT设置polygonMode 为VK_POLYGON_MODE_LINE ，则vkCmdSetLineRasterizationModeEXT必须在该命令之前设置
                                                                                    （2）如果一个shader object绑定到VK_SHADER_STAGE_VERTEX_BIT stage，且最近的vkCmdSetRasterizerDiscardEnable设置rasterizerDiscardEnable为VK_FALSE，且最近的vkCmdSetPrimitiveTopology设置primitiveTopology 为任何line topology ，则vkCmdSetLineRasterizationModeEXT必须在该命令之前设置
                                                                                    （3）如果一个输出为line primitive的shader object绑定到VK_SHADER_STAGE_TESSELLATION_EVALUATION_BIT 或 VK_SHADER_STAGE_GEOMETRY_BIT stage，且最近的vkCmdSetRasterizerDiscardEnable设置rasterizerDiscardEnable为VK_FALSE，则vkCmdSetLineRasterizationModeEXT必须在该命令之前设置
                                                                                    （4）如果一个shader object绑定到任意一个graphics stage，且最近的vkCmdSetRasterizerDiscardEnable设置rasterizerDiscardEnable为VK_FALSE，且最近的vkCmdSetPolygonModeEXT设置polygonMode 为VK_POLYGON_MODE_LINE ，则vkCmdSetLineStippleEnableEXT必须在该命令之前设置
                                                                                    （5）如果一个shader object绑定到VK_SHADER_STAGE_VERTEX_BIT stage，且最近的vkCmdSetRasterizerDiscardEnable设置rasterizerDiscardEnable为VK_FALSE，且最近的vkCmdSetPrimitiveTopology设置primitiveTopology 为任何line topology ，则vkCmdSetLineStippleEnableEXT必须在该命令之前设置
                                                                                    （6）如果一个输出为line primitive的shader object绑定到VK_SHADER_STAGE_TESSELLATION_EVALUATION_BIT 或 VK_SHADER_STAGE_GEOMETRY_BIT stage，且最近的vkCmdSetRasterizerDiscardEnable设置rasterizerDiscardEnable为VK_FALSE，则vkCmdSetLineStippleEnableEXT必须在该命令之前设置
                                                                                    （7）如果一个shader object绑定到任意一个graphics stage，且最近的vkCmdSetRasterizerDiscardEnable设置rasterizerDiscardEnable为VK_FALSE，且最近的vkCmdSetLineStippleEnableEXT设置stippledLineEnable 为VK_TRUE ，则vkCmdSetLineStippleEXT必须在该命令之前设置
        110.如果一个shader object绑定到任何graphics stage，（1）如果depthClipControl 特性开启，则vkCmdSetDepthClipNegativeOneToOneEXT必须在该命令之前设置
                                                           （2）VK_NV_clip_space_w_scaling 拓展开启，则vkCmdSetViewportWScalingEnableNV必须在该命令之前设置
                                                           （3）VK_NV_viewport_swizzle 拓展开启，则vkCmdSetViewportSwizzleNV必须在该命令之前设置
        111.如果如果一个shader object绑定到任何VK_SHADER_STAGE_FRAGMENT_BIT stage，且最近的vkCmdSetRasterizerDiscardEnable设置rasterizerDiscardEnable为VK_FALSE，则
                            （1）如果VK_NV_fragment_coverage_to_color 拓展开启，则vkCmdSetCoverageToColorEnableNV 必须在该命令之前设置
                            （2）如果VK_NV_fragment_coverage_to_color 拓展开启，且最近的vkCmdSetCoverageToColorEnableNV 设置coverageToColorEnable 为VK_TRUE，则vkCmdSetCoverageToColorLocationNV 必须在该命令之前设置
                            （3）如果pipelineFragmentShadingRate 特性开启，则vkCmdSetFragmentShadingRateKHR 必须在该命令之前设置
        112.如果一个shader object绑定到任何graphics stage，且最近的vkCmdSetRasterizerDiscardEnable设置rasterizerDiscardEnable为VK_FALSE，则
                                    （1）如果VK_NV_framebuffer_mixed_samples 拓展开启，则vkCmdSetCoverageModulationModeNV 必须在该命令之前设置
                                    （2）如果VK_NV_framebuffer_mixed_samples 拓展开启，且最近的vkCmdSetCoverageModulationModeNV设置coverageModulationMode为任何除VK_COVERAGE_MODULATION_MODE_NONE_NV之外的值，则vkCmdSetCoverageModulationTableEnableNV 必须在该命令之前设置
                                    （3）如果VK_NV_framebuffer_mixed_samples 拓展开启，最近的vkCmdSetCoverageModulationTableEnableNV设置coverageModulationTableEnable为VK_TRUE，则vkCmdSetCoverageModulationTableNV 必须在该命令之前设置
                                    （4）如果shadingRateImage 特性开启，则vkCmdSetShadingRateImageEnableNV 必须在该命令之前设置
                                    （5）如果representativeFragmentTest 特性开启，则vkCmdSetRepresentativeFragmentTestEnableNV 必须在该命令之前设置
                                    （6）如果coverageReductionMode 特性开启，则vkCmdSetCoverageReductionModeNV 必须在该命令之前设置
        113.如果绑定的graphics pipeline，（1）以VK_DYNAMIC_STATE_COLOR_BLEND_ENABLE_EXT动态state开启创建，且最近的vkCmdSetColorBlendEnableEXT设置任何附件在pColorBlendEnables中的值为VK_TRUE 则subpas中这些附件对应的image view的format features中必须包含VK_FORMAT_FEATURE_COLOR_ATTACHMENT_BLEND_BIT
                                         （2）以VK_DYNAMIC_STATE_RASTERIZATION_SAMPLES_EXT动态state开启创建，且当前subpass不使用任何color和/或者 depth/stencil attachments，则最后的vkCmdSetRasterizationSamplesEXT设置的rasterizationSamples必须符合zero￾attachment subpass的规则
                                         （3）以VK_DYNAMIC_STATE_SAMPLE_MASK_EXT不以VK_DYNAMIC_STATE_RASTERIZATION_SAMPLES_EXT 动态state开启创建，则最后调用的vkCmdSetSampleMaskEXT中设置的samples参数必须大于等于创建该pipeline的VkPipelineMultisampleStateCreateInfo::rasterizationSamples
                                         （4）以VK_DYNAMIC_STATE_SAMPLE_MASK_EXT和 VK_DYNAMIC_STATE_RASTERIZATION_SAMPLES_EXT 动态state开启创建，则最后调用的vkCmdSetSampleMaskEXT中设置的samples参数必须大于等于最后的vkCmdSetRasterizationSamplesEXT设置的rasterizationSamples
                                         （5）以VK_DYNAMIC_STATE_RASTERIZATION_SAMPLES_EXT动态state开启创建，且VK_AMD_mixed_attachment_samples和VK_NV_framebuffer_mixed_samples拓展都没有开启，则最后的vkCmdSetRasterizationSamplesEXT设置的rasterizationSamples必须等于subpass中color和/或者 depth/stencil attachments使用的相同
                                         （6）以VK_DYNAMIC_STATE_RASTERIZATION_SAMPLES_EXT动态state开启创建，或者一个shader object绑定到任意graphics stage，且当前的subpass包含一个multisampledRenderToSingleSampledEnable 为VK_TRUE的VkMultisampledRenderToSingleSampledInfoEXT，则最后的vkCmdSetRasterizationSamplesEXT设置的rasterizationSamples必须等于该VkMultisampledRenderToSingleSampledInfoEXT中的对应成员
                                         （7）以VK_DYNAMIC_STATE_COLOR_BLEND_ENABLE_EXT动态state开启创建，则vkCmdSetColorBlendEnableEXT 必须在该命令之前设置，且vkCmdSetColorBlendEnableEXT必须为从firstAttachment开始的attachmentCount个当前subpass所有激活的color attachments指定值
                                         （8）以VK_DYNAMIC_STATE_COLOR_BLEND_EQUATION_EXT动态state开启创建，则vkCmdSetColorBlendEquationEXT 必须在该命令之前设置，且vkCmdSetColorBlendEquationEXT必须为从firstAttachment开始的attachmentCount个当前subpass所有激活的color attachments指定blend equations
                                         （9）以VK_DYNAMIC_STATE_COLOR_WRITE_MASK_EXT动态state开启创建，则vkCmdSetColorWriteMaskEXT 必须在该命令之前设置，且vkCmdSetColorWriteMaskEXT必须为从firstAttachment开始的attachmentCount个当前subpass所有激活的color attachments指定color write mask
                                         （10）以VK_DYNAMIC_STATE_COLOR_BLEND_ADVANCED_EXT动态state开启创建，则vkCmdSetColorBlendAdvancedEXT 必须在该命令之前设置，且vkCmdSetColorBlendAdvancedEXT必须为从firstAttachment开始的attachmentCount个当前subpass所有激活blend的color attachments指定advanced blend equations
                                         （11）以VK_DYNAMIC_STATE_COLOR_BLEND_ADVANCED_EXT和VK_DYNAMIC_STATE_COLOR_BLEND_ENABLE_EXT动态state开启创建，且最后的vkCmdSetColorBlendEnableEXT和vkCmdSetColorBlendAdvancedEXT设置启用了advanced blending，则当前subpass中激活的color attachments的数量不能超过advancedBlendMaxColorAttachments
                                         （12）以VK_DYNAMIC_STATE_RASTERIZATION_STREAM_EXT动态state开启创建，且如果primitivesGeneratedQueryWithNonZeroStreams特性未开启且VK_QUERY_TYPE_PRIMITIVES_GENERATED_EXT query已经激活，则最后的vkCmdSetRasterizationStreamEXT必须设置rasterizationStream为0
                                         （13）以VK_DYNAMIC_STATE_SAMPLE_LOCATIONS_EXT但不以VK_DYNAMIC_STATE_RASTERIZATION_SAMPLES_EXT动态state开启创建，则最后的vkCmdSetSampleLocationsEXT设置的pSampleLocationsInfo->sampleLocationsPerPixel必须等于创建pipeline的VkPipelineMultisampleStateCreateInfo::rasterizationSamples
                                         （14）以VK_DYNAMIC_STATE_SAMPLE_LOCATIONS_EXT和VK_DYNAMIC_STATE_RASTERIZATION_SAMPLES_EXT动态state开启创建，则最后的vkCmdSetSampleLocationsEXT设置的pSampleLocationsInfo->sampleLocationsPerPixel必须等于最后vkCmdSetRasterizationSamplesEXT设置的rasterizationSamples
                                         （15）以VK_DYNAMIC_STATE_RASTERIZATION_SAMPLES_EXT但不以VK_DYNAMIC_STATE_SAMPLE_LOCATIONS_EXT动态state开启创建，且绑定的pipeline的VkPipelineSampleLocationsStateCreateInfoEXT::sampleLocationsEnable为VK_TRUE 或者以VK_DYNAMIC_STATE_SAMPLE_LOCATIONS_ENABLE_EXT动态state开启，则sampleLocationsInfo.sampleLocationsPerPixel 必须等于最后vkCmdSetRasterizationSamplesEXT设置的rasterizationSamples
                                         （16）以VK_DYNAMIC_STATE_COVERAGE_TO_COLOR_ENABLE_NV动态state开启创建，且最后的vkCmdSetCoverageToColorEnableNV设置coverageToColorEnable为VK_TRUE，则当前subpass必须有color attachment，且该attachment的format必须为VK_FORMAT_R8_UINT, VK_FORMAT_R8_SINT, VK_FORMAT_R16_UINT, VK_FORMAT_R16_SINT, VK_FORMAT_R32_UINT, 或者 VK_FORMAT_R32_SINT，且该attachment的location 有最后的vkCmdSetCoverageToColorLocationNV设置的coverageToColorLocation决定
                                         （17）以VK_DYNAMIC_STATE_COVERAGE_TO_COLOR_ENABLE_NV和VK_DYNAMIC_STATE_RASTERIZATION_SAMPLES_EXT 动态state开启创建，且如果VK_NV_coverage_reduction_mode 拓展开启，则当前的 coverageReductionMode，rasterizationSamples 以及color 以及 depth/stencil attachments（如果subpass有）的sample count必须是有效的返回值vkGetPhysicalDeviceSupportedFramebufferMixedSamplesCombinationsNV的值的组合
                                         （18）以VK_DYNAMIC_STATE_VIEWPORT_WITH_COUNT但不以VK_DYNAMIC_STATE_VIEWPORT_SWIZZLE_NV 动态state开启创建，则绑定的graphics pipeline的VkPipelineViewportSwizzleStateCreateInfoNV::viewportCount 必须大于等于最后vkCmdSetViewportWithCount设置的viewportCount
                                         （19）以VK_DYNAMIC_STATE_VIEWPORT_WITH_COUNT和VK_DYNAMIC_STATE_VIEWPORT_SWIZZLE_NV 动态state开启创建，则最后vkCmdSetViewportSwizzleNV设置的viewportCount 必须大于等于最后vkCmdSetViewportWithCount设置的viewportCount
                                         （20）以VK_DYNAMIC_STATE_LINE_STIPPLE_ENABLE_EXT或者 VK_DYNAMIC_STATE_LINE_RASTERIZATION_MODE_EXT 动态state开启创建，如果当前的stippledLineEnable为VK_TRUE，且当前的lineRasterizationMode为VK_LINE_RASTERIZATION_MODE_RECTANGULAR_KHR，则stippledRectangularLines 特性必须开启
                                         （21）以VK_DYNAMIC_STATE_LINE_STIPPLE_ENABLE_EXT或者 VK_DYNAMIC_STATE_LINE_RASTERIZATION_MODE_EXT 动态state开启创建，如果当前的stippledLineEnable为VK_TRUE，且当前的lineRasterizationMode为VK_LINE_RASTERIZATION_MODE_BRESENHAM_KHR，则stippledBresenhamLines 特性必须开启
                                         （22）以VK_DYNAMIC_STATE_LINE_STIPPLE_ENABLE_EXT或者 VK_DYNAMIC_STATE_LINE_RASTERIZATION_MODE_EXT 动态state开启创建，如果当前的stippledLineEnable为VK_TRUE，且当前的lineRasterizationMode为VK_LINE_RASTERIZATION_MODE_RECTANGULAR_SMOOTH_KHR，则stippledSmoothLines 特性必须开启
                                         （23）以VK_DYNAMIC_STATE_LINE_STIPPLE_ENABLE_EXT或者 VK_DYNAMIC_STATE_LINE_RASTERIZATION_MODE_EXT 动态state开启创建，如果当前的stippledLineEnable为VK_TRUE，且当前的lineRasterizationMode为VK_LINE_RASTERIZATION_MODE_DEFAULT_KHR，则stippledRectangularLines 特性必须开启且VkPhysicalDeviceLimits::strictLines 必须为VK_TRUE
                                         （24）以VK_DYNAMIC_STATE_CONSERVATIVE_RASTERIZATION_MODE_EXT 动态state开启创建，且conservativePointAndLineRasterization不支持，最后的 pre-rasterization shader stage输出的有效图元拓扑为点或者线，则最后vkCmdSetConservativeRasterizationModeEXT设置的conservativeRasterizationMode 必须为VK_CONSERVATIVE_RASTERIZATION_MODE_DISABLED_EXT
                                         （25）以VK_DYNAMIC_STATE_ATTACHMENT_FEEDBACK_LOOP_ENABLE_EXT 动态state开启创建，则vkCmdSetAttachmentFeedbackLoopEnableEXT 必须在该命令之前调用
        114.如果一个shader object绑定到 VK_SHADER_STAGE_FRAGMENT_BIT stage，且最近的vkCmdSetRasterizerDiscardEnable设置rasterizerDiscardEnable为VK_FALSE，则
                                                                                            （1）则vkCmdSetColorBlendEnableEXT 必须在该命令之前设置，且vkCmdSetColorBlendEnableEXT指定的firstAttachment开始的attachmentCount的值必须为当前subpass所有激活的color attachments指定
                                                                                            （2）则vkCmdSetColorBlendEquationEXT 必须在该命令之前设置，且vkCmdSetColorBlendEquationEXT必须为从firstAttachment开始的attachmentCount个当前subpass所有激活的color attachments指定blend equations
                                                                                            （3）则vkCmdSetColorWriteMaskEXT 必须在该命令之前设置，且vkCmdSetColorWriteMaskEXT必须为从firstAttachment开始的attachmentCount个当前subpass所有激活的color attachments指定color write mask
                                                                                            （4）如果VK_NV_fragment_coverage_to_color拓展开启， 最后的vkCmdSetCoverageToColorEnableNV设置coverageToColorEnable为VK_TRUE，则当前subpass必须有color attachment，且该attachment的format必须为VK_FORMAT_R8_UINT, VK_FORMAT_R8_SINT, VK_FORMAT_R16_UINT, VK_FORMAT_R16_SINT, VK_FORMAT_R32_UINT, 或者 VK_FORMAT_R32_SINT，且该attachment的location 有最后的vkCmdSetCoverageToColorLocationNV设置的coverageToColorLocation决定
        115.如果一个shader object绑定到 VK_SHADER_STAGE_FRAGMENT_BIT stage，（1）如果绑定的graphics pipeline以VK_DYNAMIC_STATE_SAMPLE_LOCATIONS_ENABLE_EXT动态state开启创建，且最近的vkCmdSetSampleLocationsEnableEXT设置sampleLocationsEnable为VK_TRUE，且该subpass含有depth/stencil attachment，则该附件必须以VK_IMAGE_CREATE_SAMPLE_LOCATIONS_COMPATIBLE_DEPTH_BIT_EXT创建
                                                                            （2）如果绑定的graphics pipeline以VK_DYNAMIC_STATE_SAMPLE_LOCATIONS_EXT和VK_DYNAMIC_STATE_SAMPLE_LOCATIONS_ENABLE_EXT 动态state开启创建，且最近的vkCmdSetSampleLocationsEnableEXT设置sampleLocationsEnable为VK_TRUE，则 最后vkCmdSetSampleLocationsEXT设置的sampleLocationsInfo.sampleLocationGridSize.width以及height 必须等于被调用vkGetPhysicalDeviceMultisamplePropertiesEXT传入rasterizationSamples返回的VkMultisamplePropertiesEXT::sampleLocationGridSize.width以及height一一对应均匀整除
                                                                            （3）如果绑定的graphics pipeline以VK_DYNAMIC_STATE_SAMPLE_LOCATIONS_ENABLE_EXT 动态state开启创建，且最近的vkCmdSetSampleLocationsEnableEXT设置sampleLocationsEnable为VK_TRUE，则fragment shader代码中不能静态使用扩展指令InterpolateAtSample
                                                                            （4）如果绑定的graphics pipeline以VK_DYNAMIC_STATE_RASTERIZATION_SAMPLES_EXT但不以VK_DYNAMIC_STATE_SAMPLE_LOCATIONS_EXT 动态state开启创建，且绑定的pipeline的VkPipelineSampleLocationsStateCreateInfoEXT::sampleLocationsEnable为VK_TRUE 或者以VK_DYNAMIC_STATE_SAMPLE_LOCATIONS_ENABLE_EXT动态state开启，则 最后vkCmdSetRasterizationSamplesEXT设置的sampleLocationsInfo.sampleLocationGridSize.width以及height 必须等于被调用vkGetPhysicalDeviceMultisamplePropertiesEXT传入和vkCmdSetRasterizationSamplesEXT设置的相同rasterizationSamples的samples返回的VkMultisamplePropertiesEXT::sampleLocationGridSize.width以及height一一对应均匀整除
        116.如果一个shader object绑定到任何graphics stage，（1）如果绑定的graphics pipeline以VK_DYNAMIC_STATE_COVERAGE_MODULATION_TABLE_ENABLE_NV 动态state开启创建，且最近的vkCmdSetCoverageModulationTableEnableNV设置coverageModulationTableEnable为VK_TRUE，则最近的vkCmdSetCoverageModulationTableNV 设置的coverageModulationTableCount 必须等于当前rasterizationSamples除以当前subppas的color samples
                                                           （2）如果VK_NV_viewport_swizzle 拓展开启，则最后vkCmdSetViewportSwizzleNV设置的viewportCount 必须大于等于最后vkCmdSetViewportWithCount设置的viewportCount
        117.如果VK_NV_framebuffer_mixed_samples 拓展开启，且如果在绑定的graphics pipeline中当前subpass有一个depth/stencil attachment以及dep test, stencil test, 或depth bounds test 启用，则当前rasterizationSamples 必须等于depth/stencil attachment的sample count
        118.如果VK_NV_framebuffer_mixed_samples 拓展开启，且如果最后的vkCmdSetRasterizationSamplesEXT设置的当前subpass的任何color attachments的rasterizationSamples 都大于 color samples，则sampleShadingEnable 必须为VK_FALSE
        119.如果当前绑定的graphics pipeline以VkGraphicsPipelineCreateInfo::pStages中的元素的VkPipelineShaderStageCreateInfo::stage设置为VK_SHADER_STAGE_VERTEX_BIT, VK_SHADER_STAGE_TESSELLATION_CONTROL_BIT, VK_SHADER_STAGE_TESSELLATION_EVALUATION_BIT 或者 VK_SHADER_STAGE_GEOMETRY_BIT创建，则Mesh Shader Queries 不能激活
        120.如果dynamic state继承自VkCommandBufferInheritanceViewportScissorInfoNV，则这些动态state的设置必须在该命令之前设置
        121.如果没有绑定graphics pipeline，则（1）vkCmdBindShadersEXT必须在当前command buffer中调用，且参数pStages中含有一个VK_SHADER_STAGE_VERTEX_BIT
                                             （2）如果tessellationShader 特性开启，vkCmdBindShadersEXT必须在当前command buffer中调用，且参数pStages中含有一个VK_SHADER_STAGE_TESSELLATION_CONTROL_BIT，VK_SHADER_STAGE_TESSELLATION_EVALUATION_BIT
                                             （3）如果geometryShader 特性开启，vkCmdBindShadersEXT必须在当前command buffer中调用，且参数pStages中含有一个VK_SHADER_STAGE_GEOMETRY_BIT
                                             （4）vkCmdBindShadersEXT必须在当前command buffer中调用，且参数pStages中含有一个VK_SHADER_STAGE_FRAGMENT_BIT
                                             （5）如果taskShader 特性开启，vkCmdBindShadersEXT必须在当前command buffer中调用，且参数pStages中含有一个VK_SHADER_STAGE_TASK_BIT_EXT
                                             （6）如果meshShader 特性开启，vkCmdBindShadersEXT必须在当前command buffer中调用，且参数pStages中含有一个VK_SHADER_STAGE_MESH_BIT_EXT
                                             （8）如果至少taskShader 和 meshShader一个特性开启，VK_SHADER_STAGE_VERTEX_BIT 或者VK_SHADER_STAGE_MESH_BIT_EXT stages中的一个必须含有有效的VkShaderEXT绑定，另外一个则不含有VkShaderEXT绑定
                                             （9）如果taskShader 和 meshShader特性同时开启，且一个有效的VkShaderEXT 绑定到VK_SHADER_STAGE_MESH_BIT_EXT stage，且该VkShaderEXT不以VK_SHADER_CREATE_NO_TASK_SHADER_BIT_EXT 创建，则一个有效的VkShaderEXT必须绑定到VK_SHADER_STAGE_TASK_BIT_EXT stage
                                             （10）如果taskShader 和 meshShader特性同时开启，且一个有效的VkShaderEXT 绑定到VK_SHADER_STAGE_MESH_BIT_EXT stage，且该VkShaderEXT以VK_SHADER_CREATE_NO_TASK_SHADER_BIT_EXT 创建，则不能有VkShaderEXT绑定到VK_SHADER_STAGE_TASK_BIT_EXT stage
                                             （11）如果一个有效的VkShaderEXT 绑定到VK_SHADER_STAGE_VERTEX_BIT stage，则不能有VkShaderEXT绑定到VK_SHADER_STAGE_TASK_BIT_EXT stage或者VK_SHADER_STAGE_MESH_BIT_EXT stage中的一个
        122.如果任何绑定的graphics shader以VK_SHADER_CREATE_LINK_STAGE_BIT_EXT 创建，（1）所有在相同vkCreateShadersEXT中以VK_SHADER_CREATE_LINK_STAGE_BIT_EXT创建的shaders必须也要绑定
                                                                                     （2）任何相同vkCreateShadersEXT中不以VK_SHADER_CREATE_LINK_STAGE_BIT_EXT创建的shaders不能有任何VkShaderEXT绑定
        123.所有绑定的graphics shader objects 必须以相同或者相同定义的push constant ranges创建
        124.所有绑定的graphics shader objects 必须以相同或者相同定义的descriptor set layouts的数组创建
        125.如果当前的render pass instance以vkCmdBeginRendering开始，且VkRenderingInfo::colorAttachmentCount为1，且有一个resolve mode为 VK_RESOLVE_MODE_EXTERNAL_FORMAT_DOWNSAMPLE_ANDROID 的color attachment，且绑定了fragment shader，则DepthReplacing 和 StencilRefReplacingEXT execution modes 不能声明
        126.如果一个shader object绑定到 VK_SHADER_STAGE_FRAGMENT_BIT stage，且最近的vkCmdSetRasterizerDiscardEnable设置rasterizerDiscardEnable为VK_FALSE，则 （1）如果attachmentFeedbackLoopDynamicState 特性开启，则 vkCmdSetAttachmentFeedbackLoopEnableEXT 必须在该命令之前调用
        127.如果包含一个fragment shader stage的绑定的graphics pipeline，（1）且该pipeline以VkPipelineDynamicStateCreateInfo::pDynamicStates中设置有VK_DYNAMIC_STATE_DEPTH_WRITE_ENABLE创建，且该fragment shader声明了EarlyFragmentTests execution mode且使用了OpDepthAttachmentReadEXT，则最后vkCmdSetDepthWriteEnable 设置的 depthWriteEnable 必须为VK_FALSE
                                                                        （2）且该pipeline以VkPipelineDynamicStateCreateInfo::pDynamicStates中设置有VK_DYNAMIC_STATE_STENCIL_WRITE_MASK创建，且该fragment shader声明了EarlyFragmentTests execution mode且使用了OpStencilAttachmentReadEXT，则最后vkCmdSetStencilWriteMask 设置的 writeMask 必须为0
        128.如果一个shader object绑定到任何graphics stage 或者绑定的graphics pipeline 以VK_DYNAMIC_STATE_COLOR_WRITE_MASK_EXT 动态state开启创建，且任何color attachment的format为VK_FORMAT_E5B9G9R9_UFLOAT_PACK32，则vkCmdSetColorWriteMaskEXT设置的pColorWriteMasks参数的对应元素必须包含VK_COLOR_COMPONENT_R_BIT, VK_COLOR_COMPONENT_G_BIT, 和 VK_COLOR_COMPONENT_B_BIT，或者都不包含
        129.如果任何附件开启了blending，且该附件的source 或者 destination blend factors使用第二个颜色输入，则该命令执行的Fragment Execution Model静态使用的任何输出output attachment的Location的最大值必须小于maxFragmentDualSrcAttachments
        130.如果当前的render pass instance以vkCmdBeginRendering开始，（1）如果没有任何shader object绑定到任何graphics stage，则vkCmdSetRenderingAttachmentLocationsKHR 设置的VkRenderingAttachmentLocationInfoKHR::pColorAttachmentLocations中的每个元素必须匹配设置在当前绑定的graphics pipeline中的对应元素
                                                                     （2）如果没有任何shader object绑定到任何graphics stage，绑定的graphics pipeline中的input attchment 索引中映射的附件必须匹配在当前render pass instance的VkRenderingInputAttachmentIndexInfoKHR中设置的
        131.如果当前的render pass instance以vkCmdBeginRendering开始且以VK_RENDERING_ENABLE_LEGACY_DITHERING_BIT_EXT标志开始，则绑定的graphics pipeline必须以VK_PIPELINE_CREATE_2_ENABLE_LEGACY_DITHERING_BIT_EXT创建
        132.如果绑定的graphics pipeline以VK_PIPELINE_CREATE_2_ENABLE_LEGACY_DITHERING_BIT_EXT创建，则当前的render pass 必须以vkCmdBeginRendering开始且以VK_RENDERING_ENABLE_LEGACY_DITHERING_BIT_EXT标志开始
        135.所有在vertex shader entry point 的 interface通过声明的vertex input variables访问的vertex input bindings必须是有效的buffer绑定或者为VK_NULL_HANDLE绑定
        136.如果nullDescriptor 特性未开启，则所有在vertex shader entry point 的 interface通过声明的vertex input variables访问的vertex input bindings不能为VK_NULL_HANDLE绑定
        137.如果robustBufferAccess 特性未开启，且pipeline的创建不对vertexInputs以VK_PIPELINE_ROBUSTNESS_BUFFER_BEHAVIOR_ROBUST_BUFFER_ACCESS_EXT开启创建，则对于指定的vertex buffer binding，任何获取的顶点属性数据必须包含在对应的vertex buffer binding中，参见Vertex Input Description p2586
        138.如果一个shader object绑定到VK_SHADER_STAGE_VERTEX_BIT stage或者绑定的graphics pipeline以VK_DYNAMIC_STATE_PRIMITIVE_TOPOLOGY动态state开启创建，则vkCmdSetPrimitiveTopology必须在该命令前设置
        140.如果绑定的graphics pipeline以VK_DYNAMIC_STATE_PRIMITIVE_TOPOLOGY动态state开启创建，且dynamicPrimitiveTopologyUnrestricted为VK_FALSE，则vkCmdSetPrimitiveTopology设置的primitiveTopology 必须和pipeline创建的VkPipelineInputAssemblyStateCreateInfo::topology相同
        141.如果绑定的graphics pipeline以VK_DYNAMIC_STATE_VERTEX_INPUT_BINDING_STRIDE_EXT但不以VK_DYNAMIC_STATE_VERTEX_INPUT_EXT 动态state开启创建，则vkCmdBindVertexBuffers2EXT必须在该命令前设置，且pStrides参数不能为NULL
        142.如果一个shader object绑定到VK_SHADER_STAGE_VERTEX_BIT stage或者绑定的graphics pipeline以VK_DYNAMIC_STATE_VERTEX_INPUT_EXT动态state开启创建，则
                                            （1）vkCmdSetVertexInputEXT必须在该命令前设置
                                            （2）所有以Input storage class修饰的Vertex Execution Model OpEntryPoint中的变量其Location必须包含在VkVertexInputAttributeDescription2EXT::location指定的location
                                            （3）如果满足legacyVertexAttributes未开启或者Vertex Execution Model OpEntryPoint中给定对应Location的Input variable的 SPIR-V Type为64-bit的中的一个，则Vertex Execution Model OpEntryPoint中对应Location的所有Input variable的numeric type必须和VkVertexInputAttributeDescription2EXT::format的相同
                                            （4）如果VkVertexInputAttributeDescription2EXT::format含有64-bit 分量，Vertex Execution Model OpEntryPoint中对应Location的所有Input variable的scalar width必须是64-bit的
                                            （5）如果Vertex Execution Model OpEntryPoint中对应Location的Input variable的scalar width是64-bit的，则对应VkVertexInputAttributeDescription2EXT::format必须含有64-bit 分量
                                            （6）如果VkVertexInputAttributeDescription2EXT::format含有64-bit 分量，则Vertex Execution Model OpEntryPoint中对应Location的所有Input variable不能使用该format未呈现的分量
        143.如果一个shader object绑定到VK_SHADER_STAGE_VERTEX_BIT stage且最近的vkCmdSetPrimitiveTopology设置primitiveTopology为VK_PRIMITIVE_TOPOLOGY_PATCH_LIST，或者绑定的graphics pipeline以VK_DYNAMIC_STATE_PATCH_CONTROL_POINTS_EXT动态state开启创建，则vkCmdSetPatchControlPointsEXT必须在该命令前设置
        144.如果一个shader object绑定到VK_SHADER_STAGE_VERTEX_BIT stage或者绑定的graphics pipeline以VK_DYNAMIC_STATE_PRIMITIVE_RESTART_ENABLE动态state开启创建，则vkCmdSetPrimitiveRestartEnable必须在该命令前设置
        145.如果primitiveTopologyListRestart特性未开启，且topology 为VK_PRIMITIVE_TOPOLOGY_POINT_LIST, VK_PRIMITIVE_TOPOLOGY_LINE_LIST, VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST, VK_PRIMITIVE_TOPOLOGY_LINE_LIST_WITH_ADJACENCY, 或者 VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST_WITH_ADJACENCY，
                    且有一个shader object绑定到VK_SHADER_STAGE_VERTEX_BIT stage或者绑定的graphics pipeline以VK_DYNAMIC_STATE_PRIMITIVE_RESTART_ENABLE动态state开启创建，则vkCmdSetPrimitiveRestartEnable必须设置为VK_FALSE
        146.绑定的graphics pipeline不能以VkGraphicsPipelineCreateInfo::pStages中元素的VkPipelineShaderStageCreateInfo::stage设置为VK_SHADER_STAGE_TASK_BIT_EXT 或者 VK_SHADER_STAGE_MESH_BIT_EXT创建
        147.不能有shader object绑定到VK_SHADER_STAGE_TASK_BIT_EXT或者 VK_SHADER_STAGE_MESH_BIT_EXT中的一个stage
        148.commandBuffer不能为protected command buffer
        149.如果isPreprocessed 为VK_TRUE，则使用和其引用的input buffers（所有除了VkGeneratedCommandsInfoNV::preprocessBuffer）的pGeneratedCommandsInfo相同内容的vkCmdPreprocessGeneratedCommandsNV必须已经在debice上执行过了，且pGeneratedCommandsInfo的indirectCommandsLayout 必须以VK_INDIRECT_COMMANDS_LAYOUT_USAGE_EXPLICIT_PREPROCESS_BIT_NV 创建
        150.VkGeneratedCommandsInfoNV::pipeline  必须匹配当前绑定在VkGeneratedCommandsInfoNV::pipelineBindPoint上的pipeline    
        151.不能激活Transform feedback
        152.VkPhysicalDeviceDeviceGeneratedCommandsFeaturesNV::deviceGeneratedCommands 必须开启
        */

    }
}



NS_TEST_END