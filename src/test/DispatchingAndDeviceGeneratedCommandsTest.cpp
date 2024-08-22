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
	Dispatching commands�����ִ���Dispatch���ᴥ����compute pipeline�н��еĹ��������ø�����ǰ�������compute pipeline
	*/

	VkCommandBuffer commandBuffer{/*��������һ����Ч��VkCommandBuffer*/ };

	//dispatch local workgroups    ���������װһ������groupCountX �� groupCountY �� groupCountZ��local work groups�� global work group 
	vkCmdDispatch(commandBuffer, 1/*groupCountX,Ϊdispatch��local workgroups �� X ά�ȵ�����.*/, 1/*groupCountY,Ϊdispatch��local workgroups �� Y ά�ȵ�����.*/, 1/*groupCountZ,Ϊdispatch��local workgroups �� Z ά�ȵ�����.*/);
	/*
	vkCmdDispatch��Ч�÷�:
    1.���һ��VkSampler����magFilter����minFilter����VK_FILTER_LINEAR��������1�����reductionModeΪVK_SAMPLER_REDUCTION_MODE_WEIGHTED_AVERAGE��������ڲ���һ��VkImageView��Ϊ������Ľ����compareEnableΪVK_FALSE�����image view��format features�������VK_FORMAT_FEATURE_SAMPLED_IMAGE_FILTER_LINEAR_BIT
                                                                             ��2�����reductionModeΪVK_SAMPLER_REDUCTION_MODE_MIN ����VK_SAMPLER_REDUCTION_MODE_MAX֮һ ���ڲ���һ��VkImageView��Ϊ������Ľ�������image view��format features�������VK_FORMAT_FEATURE_SAMPLED_IMAGE_FILTER_MINMAX_BIT
    2.���һ��VkSampler����mipmapMode ����VK_SAMPLER_MIPMAP_MODE_LINEAR��������1�����reductionModeΪVK_SAMPLER_REDUCTION_MODE_WEIGHTED_AVERAGE��������ڲ���һ��VkImageView��Ϊ������Ľ����compareEnableΪVK_FALSE�����image view��format features�������VK_FORMAT_FEATURE_SAMPLED_IMAGE_FILTER_LINEAR_BIT
                                                                             ��2�����reductionModeΪVK_SAMPLER_REDUCTION_MODE_MIN ����VK_SAMPLER_REDUCTION_MODE_MAX֮һ ���ڲ���һ��VkImageView��Ϊ������Ľ�������image view��format features�������VK_FORMAT_FEATURE_SAMPLED_IMAGE_FILTER_MINMAX_BIT
    3.���һ��VkSampler����unnormalizedCoordinates����VK_TRUE���ڲ���һ��VkImageView��Ϊ������Ľ����������1����image view��levelCount�Լ�layerCount����Ϊ1
                                                                                                            ��2����image view��viewType����ΪVK_IMAGE_VIEW_TYPE_1D ���� VK_IMAGE_VIEW_TYPE_2D
    4.���һ��VkImageView�Ĳ�����depth comparison��������image view��format features�������VK_FORMAT_FEATURE_2_SAMPLED_IMAGE_DEPTH_COMPARISON_BIT
    5.���һ��VkImageViewʹ��atomic operations��Ϊ������Ľ�����з��ʣ���image view��format features�������VK_FORMAT_FEATURE_STORAGE_IMAGE_ATOMIC_BIT
    6.���һ��VK_DESCRIPTOR_TYPE_STORAGE_TEXEL_BUFFER���͵� descriptorʹ��atomic operations��Ϊ������Ľ�����з��ʣ���storage texel buffer��format features�������VK_FORMAT_FEATURE_STORAGE_TEXEL_BUFFER_ATOMIC_BIT
    7.���һ����VK_FILTER_CUBIC_EXT���в�����VkImageView��Ϊ������Ľ������image view��format features�������VK_FORMAT_FEATURE_SAMPLED_IMAGE_FILTER_CUBIC_BIT_EXT
    8.���VK_EXT_filter_cubic��չû�п����������κ�һ����VK_FILTER_CUBIC_EXT���в�����VkImageView��Ϊ������Ľ��������VkImageViewType����ΪVK_IMAGE_VIEW_TYPE_3D, VK_IMAGE_VIEW_TYPE_CUBE, ���� VK_IMAGE_VIEW_TYPE_CUBE_ARRAY
    9.�κ�һ����VK_FILTER_CUBIC_EXT���в�������Ϊ������Ľ����VkImageView����VkImageViewType��format ����֧��cubic filtering���μ�vkGetPhysicalDeviceImageFormatProperties2���ص�VkFilterCubicImageViewImageFormatPropertiesEXT::filterCubic
    10.�κ�һ����VK_FILTER_CUBIC_EXT���в�����reduction modeΪVK_SAMPLER_REDUCTION_MODE_MIN ���� VK_SAMPLER_REDUCTION_MODE_MAX֮һ����Ϊ������Ľ����VkImageView����VkImageViewType��format ����֧�ִ�minmax filtering��cubic filtering���μ�vkGetPhysicalDeviceImageFormatProperties2���ص�VkFilterCubicImageViewImageFormatPropertiesEXT::filterCubicMinmax
    11.���cubicRangeClamp����û�п����������κ�һ����VK_FILTER_CUBIC_EXT���в���VkImageView����Ϊ������Ľ����VkSamplerReductionModeCreateInfo::reductionMode����ΪVK_SAMPLER_REDUCTION_MODE_WEIGHTED_AVERAGE_RANGECLAMP_QCOM
    12.�κ�һ����VkSamplerReductionModeCreateInfo::reductionModeΪVK_SAMPLER_REDUCTION_MODE_WEIGHTED_AVERAGE_RANGECLAMP_QCOM���в�������Ϊ������Ľ����VkImageView������VK_FILTER_CUBIC_EXT���в���
    13.���selectableCubicWeights����û�п����������κ�һ����VK_FILTER_CUBIC_EXT���в���VkImageView����Ϊ������Ľ����VkSamplerCubicWeightsCreateInfoQCOM::cubicWeights����ΪVK_CUBIC_FILTER_WEIGHTS_CATMULL_ROM_QCOM
    14.�κ�һ����VkImageCreateInfo::flags��VK_IMAGE_CREATE_CORNER_SAMPLED_BIT_NV�����Ĳ�����Ϊ����������VkImage������VkSamplerAddressModeΪVK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE ���в���
    15.�����κ���Ϊstorage imageд���VkImageView������OpTypeImage��formatδ֪�����image view�� format features�������VK_FORMAT_FEATURE_2_STORAGE_WRITE_WITHOUT_FORMAT_BIT
    16.�����κ���Ϊstorage image��ȡ��VkImageView������OpTypeImage��formatδ֪�����image view�� format features�������VK_FORMAT_FEATURE_2_STORAGE_READ_WITHOUT_FORMAT_BIT
    17.�����κ���Ϊstorage storage texel bufferд���VkBufferView������OpTypeImage��formatδ֪�����buffer view�� buffer features�������VK_FORMAT_FEATURE_2_STORAGE_WRITE_WITHOUT_FORMAT_BIT
    18.�����κ���Ϊstorage storage texel buffer��ȡ��VkBufferView������OpTypeImage��formatδ֪�����buffer view�� buffer features�������VK_FORMAT_FEATURE_2_STORAGE_READ_WITHOUT_FORMAT_BIT
    19.����ÿ���ڰ󶨵�shader�о�̬ʹ�õ�set n��һ��descriptor set���뱻�󶨵���ͬpipeline bind point��set n������set n����ʹ�����ǰVkPipeline��VkPipelineLayout���ߺʹ�����ǰVkShaderEXT��VkDescriptorSetLayout �����set n���Ĳ��ּ��ݣ��μ�Pipeline Layout Compatibility p1280
    20.����ÿ���ڰ󶨵�shader�о�̬ʹ�õ�push constant��һ��push constantֵ���뱻�󶨵���ͬpipeline bind point�Ķ�Ӧ������push constant����ʹ�����ǰVkPipeline��VkPipelineLayout���ߺʹ�����ǰVkShaderEXT��VkDescriptorSetLayout �����еĶ�Ӧ���Ĳ��ּ��ݣ��μ�Pipeline Layout Compatibility p1280
    21.���maintenance4����û�п����������ÿ���ڰ󶨵�shader�о�̬ʹ�õ�push constant��һ��push constantֵ���뱻���õ���ͬpipeline bind point�Ķ�Ӧ������push constant����ʹ�����ǰVkPipeline��VkPipelineLayout���ߺʹ�����ǰVkShaderEXT��VkDescriptorSetLayout �����еĶ�Ӧ���Ĳ��ּ��ݣ��μ�Pipeline Layout Compatibility p1280
    22.ÿһ��ͨ��vkCmdBindDescriptorSets�󶨵�descriptor set��descriptors,����Ǳ�����VK_PIPELINE_CREATE_DESCRIPTOR_BUFFER_BIT_EXT�����ģ����Ѿ��󶨵�������ʹ�õ�pipeline bind point��VkPipeline��̬ʹ�õģ�����Щdescriptors��������Ч�ģ��μ� descriptor validity p1328
    23.���ͨ��vkCmdBindDescriptorSetsָ���󶨵�pipeline bind point��VkPipelineҪʹ�õ�descriptors����󶨵�VkPipeline������VK_PIPELINE_CREATE_DESCRIPTOR_BUFFER_BIT_EXT����
    24.��vkCmdSetDescriptorBufferOffsetsEXT��ָ���󶨵�descriptor buffers��descriptors����1������󶨵�pipeline bind point�ĸ������ʹ�õ�VkPipeline��VK_PIPELINE_CREATE_DESCRIPTOR_BUFFER_BIT_EXT����������Щdescriptors�Ƕ�̬ʹ�õģ�����Щdescriptors��������Ч��
                                                                                          ��2������󶨵�pipeline bind point�Ķ�Ӧstage�ĸ������ʹ�õ�VkShaderEXT������Щdescriptors�Ƕ�̬ʹ�õģ�����Щdescriptors��������Ч��
    25.��vkCmdSetDescriptorBufferOffsetsEXT��ָ����descriptors�ڰ󶨵�pipeline bind point��VkPipeline��ʹ�ã���VkPipeline������VK_PIPELINE_CREATE_DESCRIPTOR_BUFFER_BIT_EXT����
    26.���һ��descriptor����VK_PIPELINE_CREATE_DESCRIPTOR_BUFFER_BIT_EXT������VkPipeline�ж�̬ʹ�ã���descriptor memory������פ���ڴ�
    27.���һ��descriptor������VkDescriptorSetLayout��VK_DESCRIPTOR_SET_LAYOUT_CREATE_DESCRIPTOR_BUFFER_BIT_EXT������VkShaderEXT�ж�̬ʹ�ã���descriptor memory������פ���ڴ�
    28.���shaderObject ����û�п�����һ����Ч��pipeline����󶨵��������ʹ�õİ󶨵�pipeline bind point��
    29.���һ��pipeline�󶨵�������ʹ�õ�pipeline bind point�ϣ��������κζ�̬state �������������κθ�VkPipeline ��û��ָ���Ķ�̬ state
    30.���һ��VkPipeline�󶨵�������ʹ�õ�pipeline bind point�� �����κ�һ�������һ��ʹ��unnormalized coordinates��VkSampler�� VkShaderEXT�󶨵�������ʹ�õ�pipeline bind point�ϵ�pipeline�Ķ�Ӧstage����
                                                                                ��1�����κ�shader stage�У�VkSampler�������������κ�����ΪVK_IMAGE_VIEW_TYPE_3D, VK_IMAGE_VIEW_TYPE_CUBE, VK_IMAGE_VIEW_TYPE_1D_ARRAY, VK_IMAGE_VIEW_TYPE_2D_ARRAY ���� VK_IMAGE_VIEW_TYPE_CUBE_ARRAY��VkImageView
                                                                                ��2�����κ�shader stage�У���VkSampler���ܺ��κδ��������д���ImplicitLod��Dref ���� Proj ��SPIR-V OpImageSample* ���� OpImageSparseSample*ָ��һ��ʹ��
                                                                                ��3�����κ�shader stage�У���VkSampler���ܺ��κΰ��� LOD bias����offset ֵ ��SPIR-V OpImageSample* or OpImageSparseSample*ָ��һ��ʹ��
    31.���shaderObject������һ����Ч��pipeline����󶨵�������ʹ�õ�pipeline bind point�ϻ���һ����Ч��shader objects�Լ�VK_NULL_HANDLE����ϱ���󶨵�������ʹ�õ�pipeline bind pointÿһ��֧�ֵ�shader stage��
    32.��ΰ󶨵�������ʹ�õ�pipeline bind point�ϵ�VkPipeline���κ�stage�����һ��uniform buffer���Ҹ�stage��uniformBuffers��������VK_PIPELINE_ROBUSTNESS_BUFFER_BEHAVIOR_ROBUST_BUFFER_ACCESS_EXT����VK_PIPELINE_ROBUSTNESS_BUFFER_BEHAVIOR_ROBUST_BUFFER_ACCESS_2_EXT ��������robustBufferAccess����δ���������stage�Ͳ��ܷ��ʰ󶨵���ͬpipeline bind point��descriptor setָ����buffer��Χ���ֵ
    33.���robustBufferAccess����δ���������κλ����uniform buffer�İ󶨵�������ʹ�õ�pipeline bind point�϶�Ӧshader stage��VkShaderEXT�����䲻�ܷ��ʰ󶨵���ͬpipeline bind point��descriptor setָ����buffer��Χ���ֵ
    34.��ΰ󶨵�������ʹ�õ�pipeline bind point�ϵ�VkPipeline���κ�stage�����һ��storage buffer���Ҹ�stage��storageBuffers��������VK_PIPELINE_ROBUSTNESS_BUFFER_BEHAVIOR_ROBUST_BUFFER_ACCESS_EXT����VK_PIPELINE_ROBUSTNESS_BUFFER_BEHAVIOR_ROBUST_BUFFER_ACCESS_2_EXT ��������robustBufferAccess����δ���������stage�Ͳ��ܷ��ʰ󶨵���ͬpipeline bind point��descriptor setָ����buffer��Χ���ֵ
    35.���robustBufferAccess����δ���������κλ����storage buffer�İ󶨵�������ʹ�õ�pipeline bind point�϶�Ӧshader stage��VkShaderEXT�����䲻�ܷ��ʰ󶨵���ͬpipeline bind point��descriptor setָ����buffer��Χ���ֵ
    36.���commandBuffer ��һ��unprotected command buffer����protectedNoFault δ֧�֣����κΰ󶨵�shaders���ʵ���Դ������һ��protected resource
    37.���һ���󶨵�shader����һ��VkSampler ���� VkImageView ����������sampler Y��C BCR conversion����ֻ��ʹ��OpImageSample* ���� OpImageSparseSample*ָ�����ʹ��ConstOffset �Լ� Offset������
    38.���һ��VkImageView��Ϊ������Ľ�����з��ʣ���1��image view ��viewType ����ƥ��Instruction/Sampler/Image View Validation p1481��������OpTypeImage��Dim������
                                                      ��2��image view ��foamrt��numeric type ����ƥ��OpTypeImage��Sampled Type������
    39.���һ��VkImageView��һ������VK_FORMAT_A8_UNORM_KHR��format������ͨ��OpImageWrite��Ϊ������Ľ�����з��ʣ���������Texel ��������Type�������ٰ����� image view�� format���е�components�ĸ�����ͬ��components����
    40.���һ��VkImageView��VK_FORMAT_A8_UNORM_KHR��format������ͨ��OpImageWrite��Ϊ������Ľ�����з��ʣ���������Texel ��������Type�������4��components
    41.���һ��VkBufferViewͨ��OpImageWrite��Ϊ������Ľ�����з��ʣ���������Texel ��������Type�������ٰ����� buffer view�� format���е�components�ĸ�����ͬ��components����
    42.���һ����64-bit component��VkFormat��VkImageView��Ϊ������Ľ�����з��ʣ���������OpTypeImage��������SampledType�Ŀ�ȱ���Ϊ64
    43.���һ��������64-bit component��VkFormat��VkImageView��Ϊ������Ľ�����з��ʣ���������OpTypeImage��������SampledType�Ŀ�ȱ���Ϊ32
    44.���һ����64-bit component��VkFormat��VkBufferView��Ϊ������Ľ�����з��ʣ���������OpTypeImage��������SampledType�Ŀ�ȱ���Ϊ64λ
    45.���һ��������64-bit component��VkFormat��VkBufferView��Ϊ������Ľ�����з��ʣ���������OpTypeImage��������SampledType�Ŀ�ȱ���Ϊ32
    46.���sparseImageInt64Atomics ����δ����������VK_IMAGE_CREATE_SPARSE_RESIDENCY_BIT������VkImage�����ܱ�SampledType���Ϊ64λ��OpTypeImage��atomic instructions����
    47.���sparseImageInt64Atomics ����δ����������VK_BUFFER_CREATE_SPARSE_RESIDENCY_BIT������VkBuffer�����ܱ�SampledType���Ϊ64λ��OpTypeImage��atomic instructions����
    48.���OpImageWeightedSampleQCOM��������һ����Ϊ������Ľ����VkImageView�����image view��format features�������VK_FORMAT_FEATURE_2_WEIGHT_SAMPLED_IMAGE_BIT_QCOM
    49.���OpImageWeightedSampleQCOM��������һ����Ϊ������Ľ����sample weight image��VkImageView�����image view��format features�������VK_FORMAT_FEATURE_2_WEIGHT_IMAGE_BIT_QCOM
    50.���OpImageBoxFilterQCOM��������һ����Ϊ������Ľ����VkImageView�����image view��format features�������VK_FORMAT_FEATURE_2_BOX_FILTER_SAMPLED_BIT_QCOM
    51.���OpImageBlockMatchSSDQCOM������ OpImageBlockMatchSADQCOM������ȡһ����Ϊ������Ľ����VkImageView����1����image view��format features�������VK_FORMAT_FEATURE_2_BLOCK_MATCHING_BIT_QCOM
                                                                                                               ��2������Ƕ�ȡ��reference image��ָ����reference coordinates������integer texel coordinate validation ʱ��ʧ��
    52.���OpImageWeightedSampleQCOM, OpImageBoxFilterQCOM, OpImageBlockMatchWindowSSDQCOM, OpImageBlockMatchWindowSADQCOM, OpImageBlockMatchGatherSSDQCOM,
                                                OpImageBlockMatchGatherSADQCOM, OpImageBlockMatchSSDQCOM, ���� OpImageBlockMatchSADQCOM��������һ����Ϊ������Ľ����VkImageView�����VkSampler������VK_SAMPLER_CREATE_IMAGE_PROCESSING_BIT_QCOM����
    53.����κγ���OpImageWeightedSampleQCOM, OpImageBoxFilterQCOM, OpImageBlockMatchWindowSSDQCOM, OpImageBlockMatchWindowSADQCOM, OpImageBlockMatchGatherSSDQCOM, OpImageBlockMatchGatherSADQCOM, OpImageBlockMatchSSDQCOM, ���� OpImageBlockMatchSADQCOM֮���ָ��ʹ��VkSampler���в�����Ϊ������Ľ�������sampler������VK_SAMPLER_CREATE_IMAGE_PROCESSING_BIT_QCOM ����
    54.���OpImageBlockMatchWindow*QCOM or OpImageBlockMatchGather*QCOMָ��������ȡVkImageView��Ϊ������Ľ������1��VkImageView��format features�������VK_FORMAT_FEATURE_2_BLOCK_MATCHING_BIT_QCOM
                                                                                                                  ��2��VkImageView��format����ֻ����һ��component
    55.���OpImageBlockMatchWindow*QCOM or OpImageBlockMatchGather*QCOMָ��������ȡһ�����õ�image��Ϊ������Ľ������ָ���� reference coordinates������integer texel coordinate validation ʱ��ʧ��
    56.�κθ�����ִ�е�shader invocation�����Ѿ���ֹ
    57.�����һ������λΪVK_DESCRIPTOR_TYPE_SAMPLE_WEIGHT_IMAGE_QCOM, VK_DESCRIPTOR_TYPE_BLOCK_MATCH_IMAGE_QCOM, VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE, VK_DESCRIPTOR_TYPE_STORAGE_IMAGE, ���� VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT������һ����descriptor��Ϊ������Ľ�����з��ʣ����descriptor��ָ��image subresource��layout����͸�descriptor��д��ʱ��layout��ͬ��
	58.���commandBuffer ��һ��protected command buffer����protectedNoFault δ֧�֣���1���κΰ󶨵�shadersд���ʵ���Դ������һ��unprotected resource
                                                                                      ��2��pipeline�󶨵�pipeline stage�г���framebuffer-space ��compute stages֮���pipeline stage����д���κΰ󶨵���Դ
    59.����󶨵�������ʹ�õ�pipeline���κ�shader stageʹ����RayQueryKHR capability����commandBuffer������һ��protected command buffer
    60.groupCountX ����С�ڵ���VkPhysicalDeviceLimits::maxComputeWorkGroupCount[0]��groupCountY ����С�ڵ���VkPhysicalDeviceLimits::maxComputeWorkGroupCount[1]��groupCountZ ����С�ڵ���VkPhysicalDeviceLimits::maxComputeWorkGroupCount[2]

	*/


    VkDispatchIndirectCommand dispatchIndirectCommand{};
    dispatchIndirectCommand.x = 1;//Ϊdispatch��local workgroups �� X ά�ȵ�����������С�ڵ���VkPhysicalDeviceLimits::maxComputeWorkGroupCount[0]
    dispatchIndirectCommand.y = 1;//Ϊdispatch��local workgroups �� Y ά�ȵ�����������С�ڵ���VkPhysicalDeviceLimits::maxComputeWorkGroupCount[1]
    dispatchIndirectCommand.z = 1;//Ϊdispatch��local workgroups �� Z ά�ȵ�����������С�ڵ���VkPhysicalDeviceLimits::maxComputeWorkGroupCount[2]

    //��¼һ����ӵ�dispatch command    �� ����buffer����VkDispatchIndirectCommand������֯
    vkCmdDispatchIndirect(commandBuffer, VkBuffer{/*��������һ����Ч��VkBuffer*/ }/*buffer,Ϊ����dispatch parameters��buffer.*/, 0/*offset��Ϊbuffer�еĲ�������ʼ�ֽ�ƫ����.*/);
    /*
    vkCmdDispatchIndirect��Ч�÷�:
    1.���һ��VkSampler����magFilter����minFilter����VK_FILTER_LINEAR��������1�����reductionModeΪVK_SAMPLER_REDUCTION_MODE_WEIGHTED_AVERAGE��������ڲ���һ��VkImageView��Ϊ������Ľ����compareEnableΪVK_FALSE�����image view��format features�������VK_FORMAT_FEATURE_SAMPLED_IMAGE_FILTER_LINEAR_BIT
                                                                             ��2�����reductionModeΪVK_SAMPLER_REDUCTION_MODE_MIN ����VK_SAMPLER_REDUCTION_MODE_MAX֮һ ���ڲ���һ��VkImageView��Ϊ������Ľ�������image view��format features�������VK_FORMAT_FEATURE_SAMPLED_IMAGE_FILTER_MINMAX_BIT
    2.���һ��VkSampler����mipmapMode ����VK_SAMPLER_MIPMAP_MODE_LINEAR��������1�����reductionModeΪVK_SAMPLER_REDUCTION_MODE_WEIGHTED_AVERAGE��������ڲ���һ��VkImageView��Ϊ������Ľ����compareEnableΪVK_FALSE�����image view��format features�������VK_FORMAT_FEATURE_SAMPLED_IMAGE_FILTER_LINEAR_BIT
                                                                             ��2�����reductionModeΪVK_SAMPLER_REDUCTION_MODE_MIN ����VK_SAMPLER_REDUCTION_MODE_MAX֮һ ���ڲ���һ��VkImageView��Ϊ������Ľ�������image view��format features�������VK_FORMAT_FEATURE_SAMPLED_IMAGE_FILTER_MINMAX_BIT
    3.���һ��VkSampler����unnormalizedCoordinates����VK_TRUE���ڲ���һ��VkImageView��Ϊ������Ľ����������1����image view��levelCount�Լ�layerCount����Ϊ1
                                                                                                            ��2����image view��viewType����ΪVK_IMAGE_VIEW_TYPE_1D ���� VK_IMAGE_VIEW_TYPE_2D
    4.���һ��VkImageView�Ĳ�����depth comparison��������image view��format features�������VK_FORMAT_FEATURE_2_SAMPLED_IMAGE_DEPTH_COMPARISON_BIT
    5.���һ��VkImageViewʹ��atomic operations��Ϊ������Ľ�����з��ʣ���image view��format features�������VK_FORMAT_FEATURE_STORAGE_IMAGE_ATOMIC_BIT
    6.���һ��VK_DESCRIPTOR_TYPE_STORAGE_TEXEL_BUFFER���͵� descriptorʹ��atomic operations��Ϊ������Ľ�����з��ʣ���storage texel buffer��format features�������VK_FORMAT_FEATURE_STORAGE_TEXEL_BUFFER_ATOMIC_BIT
    7.���һ����VK_FILTER_CUBIC_EXT���в�����VkImageView��Ϊ������Ľ������image view��format features�������VK_FORMAT_FEATURE_SAMPLED_IMAGE_FILTER_CUBIC_BIT_EXT
    8.���VK_EXT_filter_cubic��չû�п����������κ�һ����VK_FILTER_CUBIC_EXT���в�����VkImageView��Ϊ������Ľ��������VkImageViewType����ΪVK_IMAGE_VIEW_TYPE_3D, VK_IMAGE_VIEW_TYPE_CUBE, ���� VK_IMAGE_VIEW_TYPE_CUBE_ARRAY
    9.�κ�һ����VK_FILTER_CUBIC_EXT���в�������Ϊ������Ľ����VkImageView����VkImageViewType��format ����֧��cubic filtering���μ�vkGetPhysicalDeviceImageFormatProperties2���ص�VkFilterCubicImageViewImageFormatPropertiesEXT::filterCubic
    10.�κ�һ����VK_FILTER_CUBIC_EXT���в�����reduction modeΪVK_SAMPLER_REDUCTION_MODE_MIN ���� VK_SAMPLER_REDUCTION_MODE_MAX֮һ����Ϊ������Ľ����VkImageView����VkImageViewType��format ����֧�ִ�minmax filtering��cubic filtering���μ�vkGetPhysicalDeviceImageFormatProperties2���ص�VkFilterCubicImageViewImageFormatPropertiesEXT::filterCubicMinmax
    11.���cubicRangeClamp����û�п����������κ�һ����VK_FILTER_CUBIC_EXT���в���VkImageView����Ϊ������Ľ����VkSamplerReductionModeCreateInfo::reductionMode����ΪVK_SAMPLER_REDUCTION_MODE_WEIGHTED_AVERAGE_RANGECLAMP_QCOM
    12.�κ�һ����VkSamplerReductionModeCreateInfo::reductionModeΪVK_SAMPLER_REDUCTION_MODE_WEIGHTED_AVERAGE_RANGECLAMP_QCOM���в�������Ϊ������Ľ����VkImageView������VK_FILTER_CUBIC_EXT���в���
    13.���selectableCubicWeights����û�п����������κ�һ����VK_FILTER_CUBIC_EXT���в���VkImageView����Ϊ������Ľ����VkSamplerCubicWeightsCreateInfoQCOM::cubicWeights����ΪVK_CUBIC_FILTER_WEIGHTS_CATMULL_ROM_QCOM
    14.�κ�һ����VkImageCreateInfo::flags��VK_IMAGE_CREATE_CORNER_SAMPLED_BIT_NV�����Ĳ�����Ϊ����������VkImage������VkSamplerAddressModeΪVK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE ���в���
    15.�����κ���Ϊstorage imageд���VkImageView������OpTypeImage��formatδ֪�����image view�� format features�������VK_FORMAT_FEATURE_2_STORAGE_WRITE_WITHOUT_FORMAT_BIT
    16.�����κ���Ϊstorage image��ȡ��VkImageView������OpTypeImage��formatδ֪�����image view�� format features�������VK_FORMAT_FEATURE_2_STORAGE_READ_WITHOUT_FORMAT_BIT
    17.�����κ���Ϊstorage storage texel bufferд���VkBufferView������OpTypeImage��formatδ֪�����buffer view�� buffer features�������VK_FORMAT_FEATURE_2_STORAGE_WRITE_WITHOUT_FORMAT_BIT
    18.�����κ���Ϊstorage storage texel buffer��ȡ��VkBufferView������OpTypeImage��formatδ֪�����buffer view�� buffer features�������VK_FORMAT_FEATURE_2_STORAGE_READ_WITHOUT_FORMAT_BIT
    19.����ÿ���ڰ󶨵�shader�о�̬ʹ�õ�set n��һ��descriptor set���뱻�󶨵���ͬpipeline bind point��set n������set n����ʹ�����ǰVkPipeline��VkPipelineLayout���ߺʹ�����ǰVkShaderEXT��VkDescriptorSetLayout �����set n���Ĳ��ּ��ݣ��μ�Pipeline Layout Compatibility p1280
    20.����ÿ���ڰ󶨵�shader�о�̬ʹ�õ�push constant��һ��push constantֵ���뱻�󶨵���ͬpipeline bind point�Ķ�Ӧ������push constant����ʹ�����ǰVkPipeline��VkPipelineLayout���ߺʹ�����ǰVkShaderEXT��VkDescriptorSetLayout �����еĶ�Ӧ���Ĳ��ּ��ݣ��μ�Pipeline Layout Compatibility p1280
    21.���maintenance4����û�п����������ÿ���ڰ󶨵�shader�о�̬ʹ�õ�push constant��һ��push constantֵ���뱻���õ���ͬpipeline bind point�Ķ�Ӧ������push constant����ʹ�����ǰVkPipeline��VkPipelineLayout���ߺʹ�����ǰVkShaderEXT��VkDescriptorSetLayout �����еĶ�Ӧ���Ĳ��ּ��ݣ��μ�Pipeline Layout Compatibility p1280
    22.ÿһ��ͨ��vkCmdBindDescriptorSets�󶨵�descriptor set��descriptors,����Ǳ�����VK_PIPELINE_CREATE_DESCRIPTOR_BUFFER_BIT_EXT�����ģ����Ѿ��󶨵�������ʹ�õ�pipeline bind point��VkPipeline��̬ʹ�õģ�����Щdescriptors��������Ч�ģ��μ� descriptor validity p1328
    23.���ͨ��vkCmdBindDescriptorSetsָ���󶨵�pipeline bind point��VkPipelineҪʹ�õ�descriptors����󶨵�VkPipeline������VK_PIPELINE_CREATE_DESCRIPTOR_BUFFER_BIT_EXT����
    24.��vkCmdSetDescriptorBufferOffsetsEXT��ָ���󶨵�descriptor buffers��descriptors����1������󶨵�pipeline bind point�ĸ������ʹ�õ�VkPipeline��VK_PIPELINE_CREATE_DESCRIPTOR_BUFFER_BIT_EXT����������Щdescriptors�Ƕ�̬ʹ�õģ�����Щdescriptors��������Ч��
                                                                                          ��2������󶨵�pipeline bind point�Ķ�Ӧstage�ĸ������ʹ�õ�VkShaderEXT������Щdescriptors�Ƕ�̬ʹ�õģ�����Щdescriptors��������Ч��
    25.��vkCmdSetDescriptorBufferOffsetsEXT��ָ����descriptors�ڰ󶨵�pipeline bind point��VkPipeline��ʹ�ã���VkPipeline������VK_PIPELINE_CREATE_DESCRIPTOR_BUFFER_BIT_EXT����
    26.���һ��descriptor����VK_PIPELINE_CREATE_DESCRIPTOR_BUFFER_BIT_EXT������VkPipeline�ж�̬ʹ�ã���descriptor memory������פ���ڴ�
    27.���һ��descriptor������VkDescriptorSetLayout��VK_DESCRIPTOR_SET_LAYOUT_CREATE_DESCRIPTOR_BUFFER_BIT_EXT������VkShaderEXT�ж�̬ʹ�ã���descriptor memory������פ���ڴ�
    28.���shaderObject ����û�п�����һ����Ч��pipeline����󶨵��������ʹ�õİ󶨵�pipeline bind point��
    29.���һ��pipeline�󶨵�������ʹ�õ�pipeline bind point�ϣ��������κζ�̬state �������������κθ�VkPipeline ��û��ָ���Ķ�̬ state
    30.���һ��VkPipeline�󶨵�������ʹ�õ�pipeline bind point�� �����κ�һ�������һ��ʹ��unnormalized coordinates��VkSampler�� VkShaderEXT�󶨵�������ʹ�õ�pipeline bind point�ϵ�pipeline�Ķ�Ӧstage����
                                                                                ��1�����κ�shader stage�У�VkSampler�������������κ�����ΪVK_IMAGE_VIEW_TYPE_3D, VK_IMAGE_VIEW_TYPE_CUBE, VK_IMAGE_VIEW_TYPE_1D_ARRAY, VK_IMAGE_VIEW_TYPE_2D_ARRAY ���� VK_IMAGE_VIEW_TYPE_CUBE_ARRAY��VkImageView
                                                                                ��2�����κ�shader stage�У���VkSampler���ܺ��κδ��������д���ImplicitLod��Dref ���� Proj ��SPIR-V OpImageSample* ���� OpImageSparseSample*ָ��һ��ʹ��
                                                                                ��3�����κ�shader stage�У���VkSampler���ܺ��κΰ��� LOD bias����offset ֵ ��SPIR-V OpImageSample* or OpImageSparseSample*ָ��һ��ʹ��
    31.���shaderObject������һ����Ч��pipeline����󶨵�������ʹ�õ�pipeline bind point�ϻ���һ����Ч��shader objects�Լ�VK_NULL_HANDLE����ϱ���󶨵�������ʹ�õ�pipeline bind pointÿһ��֧�ֵ�shader stage��
    32.��ΰ󶨵�������ʹ�õ�pipeline bind point�ϵ�VkPipeline���κ�stage�����һ��uniform buffer���Ҹ�stage��uniformBuffers��������VK_PIPELINE_ROBUSTNESS_BUFFER_BEHAVIOR_ROBUST_BUFFER_ACCESS_EXT����VK_PIPELINE_ROBUSTNESS_BUFFER_BEHAVIOR_ROBUST_BUFFER_ACCESS_2_EXT ��������robustBufferAccess����δ���������stage�Ͳ��ܷ��ʰ󶨵���ͬpipeline bind point��descriptor setָ����buffer��Χ���ֵ
    33.���robustBufferAccess����δ���������κλ����uniform buffer�İ󶨵�������ʹ�õ�pipeline bind point�϶�Ӧshader stage��VkShaderEXT�����䲻�ܷ��ʰ󶨵���ͬpipeline bind point��descriptor setָ����buffer��Χ���ֵ
    34.��ΰ󶨵�������ʹ�õ�pipeline bind point�ϵ�VkPipeline���κ�stage�����һ��storage buffer���Ҹ�stage��storageBuffers��������VK_PIPELINE_ROBUSTNESS_BUFFER_BEHAVIOR_ROBUST_BUFFER_ACCESS_EXT����VK_PIPELINE_ROBUSTNESS_BUFFER_BEHAVIOR_ROBUST_BUFFER_ACCESS_2_EXT ��������robustBufferAccess����δ���������stage�Ͳ��ܷ��ʰ󶨵���ͬpipeline bind point��descriptor setָ����buffer��Χ���ֵ
    35.���robustBufferAccess����δ���������κλ����storage buffer�İ󶨵�������ʹ�õ�pipeline bind point�϶�Ӧshader stage��VkShaderEXT�����䲻�ܷ��ʰ󶨵���ͬpipeline bind point��descriptor setָ����buffer��Χ���ֵ
    36.���commandBuffer ��һ��unprotected command buffer����protectedNoFault δ֧�֣����κΰ󶨵�shaders���ʵ���Դ������һ��protected resource
    37.���һ���󶨵�shader����һ��VkSampler ���� VkImageView ����������sampler Y��C BCR conversion����ֻ��ʹ��OpImageSample* ���� OpImageSparseSample*ָ�����ʹ��ConstOffset �Լ� Offset������
    38.���һ��VkImageView��Ϊ������Ľ�����з��ʣ���1��image view ��viewType ����ƥ��Instruction/Sampler/Image View Validation p1481��������OpTypeImage��Dim������
                                                      ��2��image view ��foamrt��numeric type ����ƥ��OpTypeImage��Sampled Type������
    39.���һ��VkImageView��һ������VK_FORMAT_A8_UNORM_KHR��format������ͨ��OpImageWrite��Ϊ������Ľ�����з��ʣ���������Texel ��������Type�������ٰ����� image view�� format���е�components�ĸ�����ͬ��components����
    40.���һ��VkImageView��VK_FORMAT_A8_UNORM_KHR��format������ͨ��OpImageWrite��Ϊ������Ľ�����з��ʣ���������Texel ��������Type�������4��components
    41.���һ��VkBufferViewͨ��OpImageWrite��Ϊ������Ľ�����з��ʣ���������Texel ��������Type�������ٰ����� buffer view�� format���е�components�ĸ�����ͬ��components����
    42.���һ����64-bit component��VkFormat��VkImageView��Ϊ������Ľ�����з��ʣ���������OpTypeImage��������SampledType�Ŀ�ȱ���Ϊ64
    43.���һ��������64-bit component��VkFormat��VkImageView��Ϊ������Ľ�����з��ʣ���������OpTypeImage��������SampledType�Ŀ�ȱ���Ϊ32
    44.���һ����64-bit component��VkFormat��VkBufferView��Ϊ������Ľ�����з��ʣ���������OpTypeImage��������SampledType�Ŀ�ȱ���Ϊ64λ
    45.���һ��������64-bit component��VkFormat��VkBufferView��Ϊ������Ľ�����з��ʣ���������OpTypeImage��������SampledType�Ŀ�ȱ���Ϊ32
    46.���sparseImageInt64Atomics ����δ����������VK_IMAGE_CREATE_SPARSE_RESIDENCY_BIT������VkImage�����ܱ�SampledType���Ϊ64λ��OpTypeImage��atomic instructions����
    47.���sparseImageInt64Atomics ����δ����������VK_BUFFER_CREATE_SPARSE_RESIDENCY_BIT������VkBuffer�����ܱ�SampledType���Ϊ64λ��OpTypeImage��atomic instructions����
    48.���OpImageWeightedSampleQCOM��������һ����Ϊ������Ľ����VkImageView�����image view��format features�������VK_FORMAT_FEATURE_2_WEIGHT_SAMPLED_IMAGE_BIT_QCOM
    49.���OpImageWeightedSampleQCOM��������һ����Ϊ������Ľ����sample weight image��VkImageView�����image view��format features�������VK_FORMAT_FEATURE_2_WEIGHT_IMAGE_BIT_QCOM
    50.���OpImageBoxFilterQCOM��������һ����Ϊ������Ľ����VkImageView�����image view��format features�������VK_FORMAT_FEATURE_2_BOX_FILTER_SAMPLED_BIT_QCOM
    51.���OpImageBlockMatchSSDQCOM������ OpImageBlockMatchSADQCOM������ȡһ����Ϊ������Ľ����VkImageView����1����image view��format features�������VK_FORMAT_FEATURE_2_BLOCK_MATCHING_BIT_QCOM
                                                                                                               ��2������Ƕ�ȡ��reference image��ָ����reference coordinates������integer texel coordinate validation ʱ��ʧ��
    52.���OpImageWeightedSampleQCOM, OpImageBoxFilterQCOM, OpImageBlockMatchWindowSSDQCOM, OpImageBlockMatchWindowSADQCOM, OpImageBlockMatchGatherSSDQCOM,
                                                OpImageBlockMatchGatherSADQCOM, OpImageBlockMatchSSDQCOM, ���� OpImageBlockMatchSADQCOM��������һ����Ϊ������Ľ����VkImageView�����VkSampler������VK_SAMPLER_CREATE_IMAGE_PROCESSING_BIT_QCOM����
    53.����κγ���OpImageWeightedSampleQCOM, OpImageBoxFilterQCOM, OpImageBlockMatchWindowSSDQCOM, OpImageBlockMatchWindowSADQCOM, OpImageBlockMatchGatherSSDQCOM, OpImageBlockMatchGatherSADQCOM, OpImageBlockMatchSSDQCOM, ���� OpImageBlockMatchSADQCOM֮���ָ��ʹ��VkSampler���в�����Ϊ������Ľ�������sampler������VK_SAMPLER_CREATE_IMAGE_PROCESSING_BIT_QCOM ����
    54.���OpImageBlockMatchWindow*QCOM or OpImageBlockMatchGather*QCOMָ��������ȡVkImageView��Ϊ������Ľ������1��VkImageView��format features�������VK_FORMAT_FEATURE_2_BLOCK_MATCHING_BIT_QCOM
                                                                                                                  ��2��VkImageView��format����ֻ����һ��component
    55.���OpImageBlockMatchWindow*QCOM or OpImageBlockMatchGather*QCOMָ��������ȡһ�����õ�image��Ϊ������Ľ������ָ���� reference coordinates������integer texel coordinate validation ʱ��ʧ��
    56.�κθ�����ִ�е�shader invocation�����Ѿ���ֹ
    57.�����һ������λΪVK_DESCRIPTOR_TYPE_SAMPLE_WEIGHT_IMAGE_QCOM, VK_DESCRIPTOR_TYPE_BLOCK_MATCH_IMAGE_QCOM, VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE, VK_DESCRIPTOR_TYPE_STORAGE_IMAGE, ���� VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT������һ����descriptor��Ϊ������Ľ�����з��ʣ����descriptor��ָ��image subresource��layout����͸�descriptor��д��ʱ��layout��ͬ��
    58.���buffer��non-sparse�ģ��������󶨵���ȫ�������ĵ�����VkDeviceMemory��
    59.buffer������VK_BUFFER_USAGE_INDIRECT_BUFFER_BIT ����
    60.offset������4�ı���
    61.commandBuffer������һ��protected command buffer
    62.VkDispatchIndirectCommand�Ĵ�С����offset����С�ڵ���buffer�Ĵ�С
    
    */



    //��¼һ��WorkgroupId�и�����������0Ϊ����ֵ��dispatch command��   ��ͬ��vkCmdDispatchBaseKHR  ,���������װһ������groupCountX �� groupCountY �� groupCountZ��local work groups�� global work group ���� WorkgroupIdÿ�������ĵķ�ΧΪ[[baseGroup*, baseGroup * +groupCount*), vkCmdDispatch ��ͬ�� vkCmdDispatchBase(0, 0, 0, groupCountX, groupCountY, groupCountZ).
    vkCmdDispatchBase(commandBuffer, 1/* baseGroupX,ΪWorkgroupId��X ����ֵ����ʼֵ.*/, 1/* baseGroupY,ΪWorkgroupId��Y ����ֵ����ʼֵ.*/, 1/* baseGroupZ,ΪWorkgroupId��Z ����ֵ����ʼֵ.*/,
        1/*groupCountX,Ϊdispatch��local workgroups �� X ά�ȵ�����.*/, 1/*groupCountY,Ϊdispatch��local workgroups �� Y ά�ȵ�����.*/, 1/*groupCountZ,Ϊdispatch��local workgroups �� Z ά�ȵ�����.*/);
    /*
    vkCmdDispatchBase��Ч�÷�:
    1.���һ��VkSampler����magFilter����minFilter����VK_FILTER_LINEAR��������1�����reductionModeΪVK_SAMPLER_REDUCTION_MODE_WEIGHTED_AVERAGE��������ڲ���һ��VkImageView��Ϊ������Ľ����compareEnableΪVK_FALSE�����image view��format features�������VK_FORMAT_FEATURE_SAMPLED_IMAGE_FILTER_LINEAR_BIT
                                                                             ��2�����reductionModeΪVK_SAMPLER_REDUCTION_MODE_MIN ����VK_SAMPLER_REDUCTION_MODE_MAX֮һ ���ڲ���һ��VkImageView��Ϊ������Ľ�������image view��format features�������VK_FORMAT_FEATURE_SAMPLED_IMAGE_FILTER_MINMAX_BIT
    2.���һ��VkSampler����mipmapMode ����VK_SAMPLER_MIPMAP_MODE_LINEAR��������1�����reductionModeΪVK_SAMPLER_REDUCTION_MODE_WEIGHTED_AVERAGE��������ڲ���һ��VkImageView��Ϊ������Ľ����compareEnableΪVK_FALSE�����image view��format features�������VK_FORMAT_FEATURE_SAMPLED_IMAGE_FILTER_LINEAR_BIT
                                                                             ��2�����reductionModeΪVK_SAMPLER_REDUCTION_MODE_MIN ����VK_SAMPLER_REDUCTION_MODE_MAX֮һ ���ڲ���һ��VkImageView��Ϊ������Ľ�������image view��format features�������VK_FORMAT_FEATURE_SAMPLED_IMAGE_FILTER_MINMAX_BIT
    3.���һ��VkSampler����unnormalizedCoordinates����VK_TRUE���ڲ���һ��VkImageView��Ϊ������Ľ����������1����image view��levelCount�Լ�layerCount����Ϊ1
                                                                                                            ��2����image view��viewType����ΪVK_IMAGE_VIEW_TYPE_1D ���� VK_IMAGE_VIEW_TYPE_2D
    4.���һ��VkImageView�Ĳ�����depth comparison��������image view��format features�������VK_FORMAT_FEATURE_2_SAMPLED_IMAGE_DEPTH_COMPARISON_BIT
    5.���һ��VkImageViewʹ��atomic operations��Ϊ������Ľ�����з��ʣ���image view��format features�������VK_FORMAT_FEATURE_STORAGE_IMAGE_ATOMIC_BIT
    6.���һ��VK_DESCRIPTOR_TYPE_STORAGE_TEXEL_BUFFER���͵� descriptorʹ��atomic operations��Ϊ������Ľ�����з��ʣ���storage texel buffer��format features�������VK_FORMAT_FEATURE_STORAGE_TEXEL_BUFFER_ATOMIC_BIT
    7.���һ����VK_FILTER_CUBIC_EXT���в�����VkImageView��Ϊ������Ľ������image view��format features�������VK_FORMAT_FEATURE_SAMPLED_IMAGE_FILTER_CUBIC_BIT_EXT
    8.���VK_EXT_filter_cubic��չû�п����������κ�һ����VK_FILTER_CUBIC_EXT���в�����VkImageView��Ϊ������Ľ��������VkImageViewType����ΪVK_IMAGE_VIEW_TYPE_3D, VK_IMAGE_VIEW_TYPE_CUBE, ���� VK_IMAGE_VIEW_TYPE_CUBE_ARRAY
    9.�κ�һ����VK_FILTER_CUBIC_EXT���в�������Ϊ������Ľ����VkImageView����VkImageViewType��format ����֧��cubic filtering���μ�vkGetPhysicalDeviceImageFormatProperties2���ص�VkFilterCubicImageViewImageFormatPropertiesEXT::filterCubic
    10.�κ�һ����VK_FILTER_CUBIC_EXT���в�����reduction modeΪVK_SAMPLER_REDUCTION_MODE_MIN ���� VK_SAMPLER_REDUCTION_MODE_MAX֮һ����Ϊ������Ľ����VkImageView����VkImageViewType��format ����֧�ִ�minmax filtering��cubic filtering���μ�vkGetPhysicalDeviceImageFormatProperties2���ص�VkFilterCubicImageViewImageFormatPropertiesEXT::filterCubicMinmax
    11.���cubicRangeClamp����û�п����������κ�һ����VK_FILTER_CUBIC_EXT���в���VkImageView����Ϊ������Ľ����VkSamplerReductionModeCreateInfo::reductionMode����ΪVK_SAMPLER_REDUCTION_MODE_WEIGHTED_AVERAGE_RANGECLAMP_QCOM
    12.�κ�һ����VkSamplerReductionModeCreateInfo::reductionModeΪVK_SAMPLER_REDUCTION_MODE_WEIGHTED_AVERAGE_RANGECLAMP_QCOM���в�������Ϊ������Ľ����VkImageView������VK_FILTER_CUBIC_EXT���в���
    13.���selectableCubicWeights����û�п����������κ�һ����VK_FILTER_CUBIC_EXT���в���VkImageView����Ϊ������Ľ����VkSamplerCubicWeightsCreateInfoQCOM::cubicWeights����ΪVK_CUBIC_FILTER_WEIGHTS_CATMULL_ROM_QCOM
    14.�κ�һ����VkImageCreateInfo::flags��VK_IMAGE_CREATE_CORNER_SAMPLED_BIT_NV�����Ĳ�����Ϊ����������VkImage������VkSamplerAddressModeΪVK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE ���в���
    15.�����κ���Ϊstorage imageд���VkImageView������OpTypeImage��formatδ֪�����image view�� format features�������VK_FORMAT_FEATURE_2_STORAGE_WRITE_WITHOUT_FORMAT_BIT
    16.�����κ���Ϊstorage image��ȡ��VkImageView������OpTypeImage��formatδ֪�����image view�� format features�������VK_FORMAT_FEATURE_2_STORAGE_READ_WITHOUT_FORMAT_BIT
    17.�����κ���Ϊstorage storage texel bufferд���VkBufferView������OpTypeImage��formatδ֪�����buffer view�� buffer features�������VK_FORMAT_FEATURE_2_STORAGE_WRITE_WITHOUT_FORMAT_BIT
    18.�����κ���Ϊstorage storage texel buffer��ȡ��VkBufferView������OpTypeImage��formatδ֪�����buffer view�� buffer features�������VK_FORMAT_FEATURE_2_STORAGE_READ_WITHOUT_FORMAT_BIT
    19.����ÿ���ڰ󶨵�shader�о�̬ʹ�õ�set n��һ��descriptor set���뱻�󶨵���ͬpipeline bind point��set n������set n����ʹ�����ǰVkPipeline��VkPipelineLayout���ߺʹ�����ǰVkShaderEXT��VkDescriptorSetLayout �����set n���Ĳ��ּ��ݣ��μ�Pipeline Layout Compatibility p1280
    20.����ÿ���ڰ󶨵�shader�о�̬ʹ�õ�push constant��һ��push constantֵ���뱻�󶨵���ͬpipeline bind point�Ķ�Ӧ������push constant����ʹ�����ǰVkPipeline��VkPipelineLayout���ߺʹ�����ǰVkShaderEXT��VkDescriptorSetLayout �����еĶ�Ӧ���Ĳ��ּ��ݣ��μ�Pipeline Layout Compatibility p1280
    21.���maintenance4����û�п����������ÿ���ڰ󶨵�shader�о�̬ʹ�õ�push constant��һ��push constantֵ���뱻���õ���ͬpipeline bind point�Ķ�Ӧ������push constant����ʹ�����ǰVkPipeline��VkPipelineLayout���ߺʹ�����ǰVkShaderEXT��VkDescriptorSetLayout �����еĶ�Ӧ���Ĳ��ּ��ݣ��μ�Pipeline Layout Compatibility p1280
    22.ÿһ��ͨ��vkCmdBindDescriptorSets�󶨵�descriptor set��descriptors,����Ǳ�����VK_PIPELINE_CREATE_DESCRIPTOR_BUFFER_BIT_EXT�����ģ����Ѿ��󶨵�������ʹ�õ�pipeline bind point��VkPipeline��̬ʹ�õģ�����Щdescriptors��������Ч�ģ��μ� descriptor validity p1328
    23.���ͨ��vkCmdBindDescriptorSetsָ���󶨵�pipeline bind point��VkPipelineҪʹ�õ�descriptors����󶨵�VkPipeline������VK_PIPELINE_CREATE_DESCRIPTOR_BUFFER_BIT_EXT����
    24.��vkCmdSetDescriptorBufferOffsetsEXT��ָ���󶨵�descriptor buffers��descriptors����1������󶨵�pipeline bind point�ĸ������ʹ�õ�VkPipeline��VK_PIPELINE_CREATE_DESCRIPTOR_BUFFER_BIT_EXT����������Щdescriptors�Ƕ�̬ʹ�õģ�����Щdescriptors��������Ч��
                                                                                          ��2������󶨵�pipeline bind point�Ķ�Ӧstage�ĸ������ʹ�õ�VkShaderEXT������Щdescriptors�Ƕ�̬ʹ�õģ�����Щdescriptors��������Ч��
    25.��vkCmdSetDescriptorBufferOffsetsEXT��ָ����descriptors�ڰ󶨵�pipeline bind point��VkPipeline��ʹ�ã���VkPipeline������VK_PIPELINE_CREATE_DESCRIPTOR_BUFFER_BIT_EXT����
    26.���һ��descriptor����VK_PIPELINE_CREATE_DESCRIPTOR_BUFFER_BIT_EXT������VkPipeline�ж�̬ʹ�ã���descriptor memory������פ���ڴ�
    27.���һ��descriptor������VkDescriptorSetLayout��VK_DESCRIPTOR_SET_LAYOUT_CREATE_DESCRIPTOR_BUFFER_BIT_EXT������VkShaderEXT�ж�̬ʹ�ã���descriptor memory������פ���ڴ�
    28.���shaderObject ����û�п�����һ����Ч��pipeline����󶨵��������ʹ�õİ󶨵�pipeline bind point��
    29.���һ��pipeline�󶨵�������ʹ�õ�pipeline bind point�ϣ��������κζ�̬state �������������κθ�VkPipeline ��û��ָ���Ķ�̬ state
    30.���һ��VkPipeline�󶨵�������ʹ�õ�pipeline bind point�� �����κ�һ�������һ��ʹ��unnormalized coordinates��VkSampler�� VkShaderEXT�󶨵�������ʹ�õ�pipeline bind point�ϵ�pipeline�Ķ�Ӧstage����
                                                                                ��1�����κ�shader stage�У�VkSampler�������������κ�����ΪVK_IMAGE_VIEW_TYPE_3D, VK_IMAGE_VIEW_TYPE_CUBE, VK_IMAGE_VIEW_TYPE_1D_ARRAY, VK_IMAGE_VIEW_TYPE_2D_ARRAY ���� VK_IMAGE_VIEW_TYPE_CUBE_ARRAY��VkImageView
                                                                                ��2�����κ�shader stage�У���VkSampler���ܺ��κδ��������д���ImplicitLod��Dref ���� Proj ��SPIR-V OpImageSample* ���� OpImageSparseSample*ָ��һ��ʹ��
                                                                                ��3�����κ�shader stage�У���VkSampler���ܺ��κΰ��� LOD bias����offset ֵ ��SPIR-V OpImageSample* or OpImageSparseSample*ָ��һ��ʹ��
    31.���shaderObject������һ����Ч��pipeline����󶨵�������ʹ�õ�pipeline bind point�ϻ���һ����Ч��shader objects�Լ�VK_NULL_HANDLE����ϱ���󶨵�������ʹ�õ�pipeline bind pointÿһ��֧�ֵ�shader stage��
    32.��ΰ󶨵�������ʹ�õ�pipeline bind point�ϵ�VkPipeline���κ�stage�����һ��uniform buffer���Ҹ�stage��uniformBuffers��������VK_PIPELINE_ROBUSTNESS_BUFFER_BEHAVIOR_ROBUST_BUFFER_ACCESS_EXT����VK_PIPELINE_ROBUSTNESS_BUFFER_BEHAVIOR_ROBUST_BUFFER_ACCESS_2_EXT ��������robustBufferAccess����δ���������stage�Ͳ��ܷ��ʰ󶨵���ͬpipeline bind point��descriptor setָ����buffer��Χ���ֵ
    33.���robustBufferAccess����δ���������κλ����uniform buffer�İ󶨵�������ʹ�õ�pipeline bind point�϶�Ӧshader stage��VkShaderEXT�����䲻�ܷ��ʰ󶨵���ͬpipeline bind point��descriptor setָ����buffer��Χ���ֵ
    34.��ΰ󶨵�������ʹ�õ�pipeline bind point�ϵ�VkPipeline���κ�stage�����һ��storage buffer���Ҹ�stage��storageBuffers��������VK_PIPELINE_ROBUSTNESS_BUFFER_BEHAVIOR_ROBUST_BUFFER_ACCESS_EXT����VK_PIPELINE_ROBUSTNESS_BUFFER_BEHAVIOR_ROBUST_BUFFER_ACCESS_2_EXT ��������robustBufferAccess����δ���������stage�Ͳ��ܷ��ʰ󶨵���ͬpipeline bind point��descriptor setָ����buffer��Χ���ֵ
    35.���robustBufferAccess����δ���������κλ����storage buffer�İ󶨵�������ʹ�õ�pipeline bind point�϶�Ӧshader stage��VkShaderEXT�����䲻�ܷ��ʰ󶨵���ͬpipeline bind point��descriptor setָ����buffer��Χ���ֵ
    36.���commandBuffer ��һ��unprotected command buffer����protectedNoFault δ֧�֣����κΰ󶨵�shaders���ʵ���Դ������һ��protected resource
    37.���һ���󶨵�shader����һ��VkSampler ���� VkImageView ����������sampler Y��C BCR conversion����ֻ��ʹ��OpImageSample* ���� OpImageSparseSample*ָ�����ʹ��ConstOffset �Լ� Offset������
    38.���һ��VkImageView��Ϊ������Ľ�����з��ʣ���1��image view ��viewType ����ƥ��Instruction/Sampler/Image View Validation p1481��������OpTypeImage��Dim������
                                                      ��2��image view ��foamrt��numeric type ����ƥ��OpTypeImage��Sampled Type������
    39.���һ��VkImageView��һ������VK_FORMAT_A8_UNORM_KHR��format������ͨ��OpImageWrite��Ϊ������Ľ�����з��ʣ���������Texel ��������Type�������ٰ����� image view�� format���е�components�ĸ�����ͬ��components����
    40.���һ��VkImageView��VK_FORMAT_A8_UNORM_KHR��format������ͨ��OpImageWrite��Ϊ������Ľ�����з��ʣ���������Texel ��������Type�������4��components
    41.���һ��VkBufferViewͨ��OpImageWrite��Ϊ������Ľ�����з��ʣ���������Texel ��������Type�������ٰ����� buffer view�� format���е�components�ĸ�����ͬ��components����
    42.���һ����64-bit component��VkFormat��VkImageView��Ϊ������Ľ�����з��ʣ���������OpTypeImage��������SampledType�Ŀ�ȱ���Ϊ64
    43.���һ��������64-bit component��VkFormat��VkImageView��Ϊ������Ľ�����з��ʣ���������OpTypeImage��������SampledType�Ŀ�ȱ���Ϊ32
    44.���һ����64-bit component��VkFormat��VkBufferView��Ϊ������Ľ�����з��ʣ���������OpTypeImage��������SampledType�Ŀ�ȱ���Ϊ64λ
    45.���һ��������64-bit component��VkFormat��VkBufferView��Ϊ������Ľ�����з��ʣ���������OpTypeImage��������SampledType�Ŀ�ȱ���Ϊ32
    46.���sparseImageInt64Atomics ����δ����������VK_IMAGE_CREATE_SPARSE_RESIDENCY_BIT������VkImage�����ܱ�SampledType���Ϊ64λ��OpTypeImage��atomic instructions����
    47.���sparseImageInt64Atomics ����δ����������VK_BUFFER_CREATE_SPARSE_RESIDENCY_BIT������VkBuffer�����ܱ�SampledType���Ϊ64λ��OpTypeImage��atomic instructions����
    48.���OpImageWeightedSampleQCOM��������һ����Ϊ������Ľ����VkImageView�����image view��format features�������VK_FORMAT_FEATURE_2_WEIGHT_SAMPLED_IMAGE_BIT_QCOM
    49.���OpImageWeightedSampleQCOM��������һ����Ϊ������Ľ����sample weight image��VkImageView�����image view��format features�������VK_FORMAT_FEATURE_2_WEIGHT_IMAGE_BIT_QCOM
    50.���OpImageBoxFilterQCOM��������һ����Ϊ������Ľ����VkImageView�����image view��format features�������VK_FORMAT_FEATURE_2_BOX_FILTER_SAMPLED_BIT_QCOM
    51.���OpImageBlockMatchSSDQCOM������ OpImageBlockMatchSADQCOM������ȡһ����Ϊ������Ľ����VkImageView����1����image view��format features�������VK_FORMAT_FEATURE_2_BLOCK_MATCHING_BIT_QCOM
                                                                                                               ��2������Ƕ�ȡ��reference image��ָ����reference coordinates������integer texel coordinate validation ʱ��ʧ��
    52.���OpImageWeightedSampleQCOM, OpImageBoxFilterQCOM, OpImageBlockMatchWindowSSDQCOM, OpImageBlockMatchWindowSADQCOM, OpImageBlockMatchGatherSSDQCOM,
                                                OpImageBlockMatchGatherSADQCOM, OpImageBlockMatchSSDQCOM, ���� OpImageBlockMatchSADQCOM��������һ����Ϊ������Ľ����VkImageView�����VkSampler������VK_SAMPLER_CREATE_IMAGE_PROCESSING_BIT_QCOM����
    53.����κγ���OpImageWeightedSampleQCOM, OpImageBoxFilterQCOM, OpImageBlockMatchWindowSSDQCOM, OpImageBlockMatchWindowSADQCOM, OpImageBlockMatchGatherSSDQCOM, OpImageBlockMatchGatherSADQCOM, OpImageBlockMatchSSDQCOM, ���� OpImageBlockMatchSADQCOM֮���ָ��ʹ��VkSampler���в�����Ϊ������Ľ�������sampler������VK_SAMPLER_CREATE_IMAGE_PROCESSING_BIT_QCOM ����
    54.���OpImageBlockMatchWindow*QCOM or OpImageBlockMatchGather*QCOMָ��������ȡVkImageView��Ϊ������Ľ������1��VkImageView��format features�������VK_FORMAT_FEATURE_2_BLOCK_MATCHING_BIT_QCOM
                                                                                                                  ��2��VkImageView��format����ֻ����һ��component
    55.���OpImageBlockMatchWindow*QCOM or OpImageBlockMatchGather*QCOMָ��������ȡһ�����õ�image��Ϊ������Ľ������ָ���� reference coordinates������integer texel coordinate validation ʱ��ʧ��
    56.�κθ�����ִ�е�shader invocation�����Ѿ���ֹ
    57.�����һ������λΪVK_DESCRIPTOR_TYPE_SAMPLE_WEIGHT_IMAGE_QCOM, VK_DESCRIPTOR_TYPE_BLOCK_MATCH_IMAGE_QCOM, VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE, VK_DESCRIPTOR_TYPE_STORAGE_IMAGE, ���� VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT������һ����descriptor��Ϊ������Ľ�����з��ʣ����descriptor��ָ��image subresource��layout����͸�descriptor��д��ʱ��layout��ͬ��
    58.���commandBuffer ��һ��protected command buffer����protectedNoFault δ֧�֣���1���κΰ󶨵�shadersд���ʵ���Դ������һ��unprotected resource
                                                                                      ��2��pipeline�󶨵�pipeline stage�г���framebuffer-space ��compute stages֮���pipeline stage����д���κΰ󶨵���Դ
    59.����󶨵�������ʹ�õ�pipeline���κ�shader stageʹ����RayQueryKHR capability����commandBuffer������һ��protected command buffer
    60.baseGroupX ����С�ڵ���VkPhysicalDeviceLimits::maxComputeWorkGroupCount[0]��baseGroupY ����С�ڵ���VkPhysicalDeviceLimits::maxComputeWorkGroupCount[1]��baseGroupZ ����С�ڵ���VkPhysicalDeviceLimits::maxComputeWorkGroupCount[2]
    61.groupCountX ����С�ڵ���VkPhysicalDeviceLimits::maxComputeWorkGroupCount[0]��ȥbaseGroupX��groupCountY ����С�ڵ���VkPhysicalDeviceLimits::maxComputeWorkGroupCount[1]��ȥbaseGroupY��groupCountZ ����С�ڵ���VkPhysicalDeviceLimits::maxComputeWorkGroupCount[2]��ȥbaseGroupZ
    62.���baseGroupX, baseGroupY, or baseGroupZ����Ϊ0����󶨵�compute pipeline����shader object������VK_PIPELINE_CREATE_DISPATCH_BASE��־������

    */


    //subpass shading���Ե�ǰsubpass��render area��ά��dispatch һЩ compute work group������ָ���� work group size���л��֣���ʱ����ʹ�� subpassLoad����
    //��¼һ��subpass shading       �����������װһ������(render area size / local workgroup size) ��ceil local work groups�� global work group
    vkCmdSubpassShadingHUAWEI(commandBuffer);
    /*
    vkCmdSubpassShadingHUAWEI��Ч�÷�:
    1.���һ��VkSampler����magFilter����minFilter����VK_FILTER_LINEAR��������1�����reductionModeΪVK_SAMPLER_REDUCTION_MODE_WEIGHTED_AVERAGE��������ڲ���һ��VkImageView��Ϊ������Ľ����compareEnableΪVK_FALSE�����image view��format features�������VK_FORMAT_FEATURE_SAMPLED_IMAGE_FILTER_LINEAR_BIT
                                                                             ��2�����reductionModeΪVK_SAMPLER_REDUCTION_MODE_MIN ����VK_SAMPLER_REDUCTION_MODE_MAX֮һ ���ڲ���һ��VkImageView��Ϊ������Ľ�������image view��format features�������VK_FORMAT_FEATURE_SAMPLED_IMAGE_FILTER_MINMAX_BIT
    2.���һ��VkSampler����mipmapMode ����VK_SAMPLER_MIPMAP_MODE_LINEAR��������1�����reductionModeΪVK_SAMPLER_REDUCTION_MODE_WEIGHTED_AVERAGE��������ڲ���һ��VkImageView��Ϊ������Ľ����compareEnableΪVK_FALSE�����image view��format features�������VK_FORMAT_FEATURE_SAMPLED_IMAGE_FILTER_LINEAR_BIT
                                                                             ��2�����reductionModeΪVK_SAMPLER_REDUCTION_MODE_MIN ����VK_SAMPLER_REDUCTION_MODE_MAX֮һ ���ڲ���һ��VkImageView��Ϊ������Ľ�������image view��format features�������VK_FORMAT_FEATURE_SAMPLED_IMAGE_FILTER_MINMAX_BIT
    3.���һ��VkSampler����unnormalizedCoordinates����VK_TRUE���ڲ���һ��VkImageView��Ϊ������Ľ����������1����image view��levelCount�Լ�layerCount����Ϊ1
                                                                                                            ��2����image view��viewType����ΪVK_IMAGE_VIEW_TYPE_1D ���� VK_IMAGE_VIEW_TYPE_2D
    4.���һ��VkImageView�Ĳ�����depth comparison��������image view��format features�������VK_FORMAT_FEATURE_2_SAMPLED_IMAGE_DEPTH_COMPARISON_BIT
    5.���һ��VkImageViewʹ��atomic operations��Ϊ������Ľ�����з��ʣ���image view��format features�������VK_FORMAT_FEATURE_STORAGE_IMAGE_ATOMIC_BIT
    6.���һ��VK_DESCRIPTOR_TYPE_STORAGE_TEXEL_BUFFER���͵� descriptorʹ��atomic operations��Ϊ������Ľ�����з��ʣ���storage texel buffer��format features�������VK_FORMAT_FEATURE_STORAGE_TEXEL_BUFFER_ATOMIC_BIT
    7.���һ����VK_FILTER_CUBIC_EXT���в�����VkImageView��Ϊ������Ľ������image view��format features�������VK_FORMAT_FEATURE_SAMPLED_IMAGE_FILTER_CUBIC_BIT_EXT
    8.���VK_EXT_filter_cubic��չû�п����������κ�һ����VK_FILTER_CUBIC_EXT���в�����VkImageView��Ϊ������Ľ��������VkImageViewType����ΪVK_IMAGE_VIEW_TYPE_3D, VK_IMAGE_VIEW_TYPE_CUBE, ���� VK_IMAGE_VIEW_TYPE_CUBE_ARRAY
    9.�κ�һ����VK_FILTER_CUBIC_EXT���в�������Ϊ������Ľ����VkImageView����VkImageViewType��format ����֧��cubic filtering���μ�vkGetPhysicalDeviceImageFormatProperties2���ص�VkFilterCubicImageViewImageFormatPropertiesEXT::filterCubic
    10.�κ�һ����VK_FILTER_CUBIC_EXT���в�����reduction modeΪVK_SAMPLER_REDUCTION_MODE_MIN ���� VK_SAMPLER_REDUCTION_MODE_MAX֮һ����Ϊ������Ľ����VkImageView����VkImageViewType��format ����֧�ִ�minmax filtering��cubic filtering���μ�vkGetPhysicalDeviceImageFormatProperties2���ص�VkFilterCubicImageViewImageFormatPropertiesEXT::filterCubicMinmax
    11.���cubicRangeClamp����û�п����������κ�һ����VK_FILTER_CUBIC_EXT���в���VkImageView����Ϊ������Ľ����VkSamplerReductionModeCreateInfo::reductionMode����ΪVK_SAMPLER_REDUCTION_MODE_WEIGHTED_AVERAGE_RANGECLAMP_QCOM
    12.�κ�һ����VkSamplerReductionModeCreateInfo::reductionModeΪVK_SAMPLER_REDUCTION_MODE_WEIGHTED_AVERAGE_RANGECLAMP_QCOM���в�������Ϊ������Ľ����VkImageView������VK_FILTER_CUBIC_EXT���в���
    13.���selectableCubicWeights����û�п����������κ�һ����VK_FILTER_CUBIC_EXT���в���VkImageView����Ϊ������Ľ����VkSamplerCubicWeightsCreateInfoQCOM::cubicWeights����ΪVK_CUBIC_FILTER_WEIGHTS_CATMULL_ROM_QCOM
    14.�κ�һ����VkImageCreateInfo::flags��VK_IMAGE_CREATE_CORNER_SAMPLED_BIT_NV�����Ĳ�����Ϊ����������VkImage������VkSamplerAddressModeΪVK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE ���в���
    15.�����κ���Ϊstorage imageд���VkImageView������OpTypeImage��formatδ֪�����image view�� format features�������VK_FORMAT_FEATURE_2_STORAGE_WRITE_WITHOUT_FORMAT_BIT
    16.�����κ���Ϊstorage image��ȡ��VkImageView������OpTypeImage��formatδ֪�����image view�� format features�������VK_FORMAT_FEATURE_2_STORAGE_READ_WITHOUT_FORMAT_BIT
    17.�����κ���Ϊstorage storage texel bufferд���VkBufferView������OpTypeImage��formatδ֪�����buffer view�� buffer features�������VK_FORMAT_FEATURE_2_STORAGE_WRITE_WITHOUT_FORMAT_BIT
    18.�����κ���Ϊstorage storage texel buffer��ȡ��VkBufferView������OpTypeImage��formatδ֪�����buffer view�� buffer features�������VK_FORMAT_FEATURE_2_STORAGE_READ_WITHOUT_FORMAT_BIT
    19.����ÿ���ڰ󶨵�shader�о�̬ʹ�õ�set n��һ��descriptor set���뱻�󶨵���ͬpipeline bind point��set n������set n����ʹ�����ǰVkPipeline��VkPipelineLayout���ߺʹ�����ǰVkShaderEXT��VkDescriptorSetLayout �����set n���Ĳ��ּ��ݣ��μ�Pipeline Layout Compatibility p1280
    20.����ÿ���ڰ󶨵�shader�о�̬ʹ�õ�push constant��һ��push constantֵ���뱻�󶨵���ͬpipeline bind point�Ķ�Ӧ������push constant����ʹ�����ǰVkPipeline��VkPipelineLayout���ߺʹ�����ǰVkShaderEXT��VkDescriptorSetLayout �����еĶ�Ӧ���Ĳ��ּ��ݣ��μ�Pipeline Layout Compatibility p1280
    21.���maintenance4����û�п����������ÿ���ڰ󶨵�shader�о�̬ʹ�õ�push constant��һ��push constantֵ���뱻���õ���ͬpipeline bind point�Ķ�Ӧ������push constant����ʹ�����ǰVkPipeline��VkPipelineLayout���ߺʹ�����ǰVkShaderEXT��VkDescriptorSetLayout �����еĶ�Ӧ���Ĳ��ּ��ݣ��μ�Pipeline Layout Compatibility p1280
    22.ÿһ��ͨ��vkCmdBindDescriptorSets�󶨵�descriptor set��descriptors,����Ǳ�����VK_PIPELINE_CREATE_DESCRIPTOR_BUFFER_BIT_EXT�����ģ����Ѿ��󶨵�������ʹ�õ�pipeline bind point��VkPipeline��̬ʹ�õģ�����Щdescriptors��������Ч�ģ��μ� descriptor validity p1328
    23.���ͨ��vkCmdBindDescriptorSetsָ���󶨵�pipeline bind point��VkPipelineҪʹ�õ�descriptors����󶨵�VkPipeline������VK_PIPELINE_CREATE_DESCRIPTOR_BUFFER_BIT_EXT����
    24.��vkCmdSetDescriptorBufferOffsetsEXT��ָ���󶨵�descriptor buffers��descriptors����1������󶨵�pipeline bind point�ĸ������ʹ�õ�VkPipeline��VK_PIPELINE_CREATE_DESCRIPTOR_BUFFER_BIT_EXT����������Щdescriptors�Ƕ�̬ʹ�õģ�����Щdescriptors��������Ч��
                                                                                          ��2������󶨵�pipeline bind point�Ķ�Ӧstage�ĸ������ʹ�õ�VkShaderEXT������Щdescriptors�Ƕ�̬ʹ�õģ�����Щdescriptors��������Ч��
    25.��vkCmdSetDescriptorBufferOffsetsEXT��ָ����descriptors�ڰ󶨵�pipeline bind point��VkPipeline��ʹ�ã���VkPipeline������VK_PIPELINE_CREATE_DESCRIPTOR_BUFFER_BIT_EXT����
    26.���һ��descriptor����VK_PIPELINE_CREATE_DESCRIPTOR_BUFFER_BIT_EXT������VkPipeline�ж�̬ʹ�ã���descriptor memory������פ���ڴ�
    27.���һ��descriptor������VkDescriptorSetLayout��VK_DESCRIPTOR_SET_LAYOUT_CREATE_DESCRIPTOR_BUFFER_BIT_EXT������VkShaderEXT�ж�̬ʹ�ã���descriptor memory������פ���ڴ�
    28.���shaderObject ����û�п�����һ����Ч��pipeline����󶨵��������ʹ�õİ󶨵�pipeline bind point��
    29.���һ��pipeline�󶨵�������ʹ�õ�pipeline bind point�ϣ��������κζ�̬state �������������κθ�VkPipeline ��û��ָ���Ķ�̬ state
    30.���һ��VkPipeline�󶨵�������ʹ�õ�pipeline bind point�� �����κ�һ�������һ��ʹ��unnormalized coordinates��VkSampler�� VkShaderEXT�󶨵�������ʹ�õ�pipeline bind point�ϵ�pipeline�Ķ�Ӧstage����
                                                                                ��1�����κ�shader stage�У�VkSampler�������������κ�����ΪVK_IMAGE_VIEW_TYPE_3D, VK_IMAGE_VIEW_TYPE_CUBE, VK_IMAGE_VIEW_TYPE_1D_ARRAY, VK_IMAGE_VIEW_TYPE_2D_ARRAY ���� VK_IMAGE_VIEW_TYPE_CUBE_ARRAY��VkImageView
                                                                                ��2�����κ�shader stage�У���VkSampler���ܺ��κδ��������д���ImplicitLod��Dref ���� Proj ��SPIR-V OpImageSample* ���� OpImageSparseSample*ָ��һ��ʹ��
                                                                                ��3�����κ�shader stage�У���VkSampler���ܺ��κΰ��� LOD bias����offset ֵ ��SPIR-V OpImageSample* or OpImageSparseSample*ָ��һ��ʹ��
    31.���shaderObject������һ����Ч��pipeline����󶨵�������ʹ�õ�pipeline bind point�ϻ���һ����Ч��shader objects�Լ�VK_NULL_HANDLE����ϱ���󶨵�������ʹ�õ�pipeline bind pointÿһ��֧�ֵ�shader stage��
    32.��ΰ󶨵�������ʹ�õ�pipeline bind point�ϵ�VkPipeline���κ�stage�����һ��uniform buffer���Ҹ�stage��uniformBuffers��������VK_PIPELINE_ROBUSTNESS_BUFFER_BEHAVIOR_ROBUST_BUFFER_ACCESS_EXT����VK_PIPELINE_ROBUSTNESS_BUFFER_BEHAVIOR_ROBUST_BUFFER_ACCESS_2_EXT ��������robustBufferAccess����δ���������stage�Ͳ��ܷ��ʰ󶨵���ͬpipeline bind point��descriptor setָ����buffer��Χ���ֵ
    33.���robustBufferAccess����δ���������κλ����uniform buffer�İ󶨵�������ʹ�õ�pipeline bind point�϶�Ӧshader stage��VkShaderEXT�����䲻�ܷ��ʰ󶨵���ͬpipeline bind point��descriptor setָ����buffer��Χ���ֵ
    34.��ΰ󶨵�������ʹ�õ�pipeline bind point�ϵ�VkPipeline���κ�stage�����һ��storage buffer���Ҹ�stage��storageBuffers��������VK_PIPELINE_ROBUSTNESS_BUFFER_BEHAVIOR_ROBUST_BUFFER_ACCESS_EXT����VK_PIPELINE_ROBUSTNESS_BUFFER_BEHAVIOR_ROBUST_BUFFER_ACCESS_2_EXT ��������robustBufferAccess����δ���������stage�Ͳ��ܷ��ʰ󶨵���ͬpipeline bind point��descriptor setָ����buffer��Χ���ֵ
    35.���robustBufferAccess����δ���������κλ����storage buffer�İ󶨵�������ʹ�õ�pipeline bind point�϶�Ӧshader stage��VkShaderEXT�����䲻�ܷ��ʰ󶨵���ͬpipeline bind point��descriptor setָ����buffer��Χ���ֵ
    36.���commandBuffer ��һ��unprotected command buffer����protectedNoFault δ֧�֣����κΰ󶨵�shaders���ʵ���Դ������һ��protected resource
    37.���һ���󶨵�shader����һ��VkSampler ���� VkImageView ����������sampler Y��C BCR conversion����ֻ��ʹ��OpImageSample* ���� OpImageSparseSample*ָ�����ʹ��ConstOffset �Լ� Offset������
    38.���һ��VkImageView��Ϊ������Ľ�����з��ʣ���1��image view ��viewType ����ƥ��Instruction/Sampler/Image View Validation p1481��������OpTypeImage��Dim������
                                                      ��2��image view ��foamrt��numeric type ����ƥ��OpTypeImage��Sampled Type������
    39.���һ��VkImageView��һ������VK_FORMAT_A8_UNORM_KHR��format������ͨ��OpImageWrite��Ϊ������Ľ�����з��ʣ���������Texel ��������Type�������ٰ����� image view�� format���е�components�ĸ�����ͬ��components����
    40.���һ��VkImageView��VK_FORMAT_A8_UNORM_KHR��format������ͨ��OpImageWrite��Ϊ������Ľ�����з��ʣ���������Texel ��������Type�������4��components
    41.���һ��VkBufferViewͨ��OpImageWrite��Ϊ������Ľ�����з��ʣ���������Texel ��������Type�������ٰ����� buffer view�� format���е�components�ĸ�����ͬ��components����
    42.���һ����64-bit component��VkFormat��VkImageView��Ϊ������Ľ�����з��ʣ���������OpTypeImage��������SampledType�Ŀ�ȱ���Ϊ64
    43.���һ��������64-bit component��VkFormat��VkImageView��Ϊ������Ľ�����з��ʣ���������OpTypeImage��������SampledType�Ŀ�ȱ���Ϊ32
    44.���һ����64-bit component��VkFormat��VkBufferView��Ϊ������Ľ�����з��ʣ���������OpTypeImage��������SampledType�Ŀ�ȱ���Ϊ64λ
    45.���һ��������64-bit component��VkFormat��VkBufferView��Ϊ������Ľ�����з��ʣ���������OpTypeImage��������SampledType�Ŀ�ȱ���Ϊ32
    46.���sparseImageInt64Atomics ����δ����������VK_IMAGE_CREATE_SPARSE_RESIDENCY_BIT������VkImage�����ܱ�SampledType���Ϊ64λ��OpTypeImage��atomic instructions����
    47.���sparseImageInt64Atomics ����δ����������VK_BUFFER_CREATE_SPARSE_RESIDENCY_BIT������VkBuffer�����ܱ�SampledType���Ϊ64λ��OpTypeImage��atomic instructions����
    48.���OpImageWeightedSampleQCOM��������һ����Ϊ������Ľ����VkImageView�����image view��format features�������VK_FORMAT_FEATURE_2_WEIGHT_SAMPLED_IMAGE_BIT_QCOM
    49.���OpImageWeightedSampleQCOM��������һ����Ϊ������Ľ����sample weight image��VkImageView�����image view��format features�������VK_FORMAT_FEATURE_2_WEIGHT_IMAGE_BIT_QCOM
    50.���OpImageBoxFilterQCOM��������һ����Ϊ������Ľ����VkImageView�����image view��format features�������VK_FORMAT_FEATURE_2_BOX_FILTER_SAMPLED_BIT_QCOM
    51.���OpImageBlockMatchSSDQCOM������ OpImageBlockMatchSADQCOM������ȡһ����Ϊ������Ľ����VkImageView����1����image view��format features�������VK_FORMAT_FEATURE_2_BLOCK_MATCHING_BIT_QCOM
                                                                                                               ��2������Ƕ�ȡ��reference image��ָ����reference coordinates������integer texel coordinate validation ʱ��ʧ��
    52.���OpImageWeightedSampleQCOM, OpImageBoxFilterQCOM, OpImageBlockMatchWindowSSDQCOM, OpImageBlockMatchWindowSADQCOM, OpImageBlockMatchGatherSSDQCOM,
                                                OpImageBlockMatchGatherSADQCOM, OpImageBlockMatchSSDQCOM, ���� OpImageBlockMatchSADQCOM��������һ����Ϊ������Ľ����VkImageView�����VkSampler������VK_SAMPLER_CREATE_IMAGE_PROCESSING_BIT_QCOM����
    53.����κγ���OpImageWeightedSampleQCOM, OpImageBoxFilterQCOM, OpImageBlockMatchWindowSSDQCOM, OpImageBlockMatchWindowSADQCOM, OpImageBlockMatchGatherSSDQCOM, OpImageBlockMatchGatherSADQCOM, OpImageBlockMatchSSDQCOM, ���� OpImageBlockMatchSADQCOM֮���ָ��ʹ��VkSampler���в�����Ϊ������Ľ�������sampler������VK_SAMPLER_CREATE_IMAGE_PROCESSING_BIT_QCOM ����
    54.���OpImageBlockMatchWindow*QCOM or OpImageBlockMatchGather*QCOMָ��������ȡVkImageView��Ϊ������Ľ������1��VkImageView��format features�������VK_FORMAT_FEATURE_2_BLOCK_MATCHING_BIT_QCOM
                                                                                                                  ��2��VkImageView��format����ֻ����һ��component
    55.���OpImageBlockMatchWindow*QCOM or OpImageBlockMatchGather*QCOMָ��������ȡһ�����õ�image��Ϊ������Ľ������ָ���� reference coordinates������integer texel coordinate validation ʱ��ʧ��
    56.�κθ�����ִ�е�shader invocation�����Ѿ���ֹ
    57.�����һ������λΪVK_DESCRIPTOR_TYPE_SAMPLE_WEIGHT_IMAGE_QCOM, VK_DESCRIPTOR_TYPE_BLOCK_MATCH_IMAGE_QCOM, VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE, VK_DESCRIPTOR_TYPE_STORAGE_IMAGE, ���� VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT������һ����descriptor��Ϊ������Ľ�����з��ʣ����descriptor��ָ��image subresource��layout����͸�descriptor��д��ʱ��layout��ͬ��
    58.�����������subpass�е����Ұ󶨵�ΪVK_PIPELINE_BIND_POINT_SUBPASS_SHADING_HUAWEI��ͬʱ��subpass�оͲ����ٵ��û������ֻ�ܵ��ø�����
    */



    //Dispatch Command for CUDA PTX Kernels   �μ�p2899
    {
        /*
        Compute kernels ������ SPIR-V ���� PTX code�ṩ����ʹ��PTX kernels�Ļ�dispatch���ƻ��������𣬲μ�https://docs.nvidia.com/cuda/. 
        
        ��¼dispatching CUDA kernel����֮ǰҪ�ȴ���CUDA module����CUDA Modules.p705
        */

        VkCudaLaunchInfoNV cudaLaunchInfoNV{};//�ýṹ���еĲ���ʮ�ֽӽ�CUDA-Driver�Ľӿ�
        cudaLaunchInfoNV.sType = VK_STRUCTURE_TYPE_MAX_ENUM;//��Ϊ���Լ��������������Ϊ�Ƿ�ֵ
        cudaLaunchInfoNV.pNext = nullptr;
        cudaLaunchInfoNV.function = VK_NULL_HANDLE;//Ϊ����launch��CUDA-Driver handle
        cudaLaunchInfoNV.gridDimX = 1;//Ϊdispatch��local workgroups �� X ά�ȵ�����,����С�ڵ��� VkPhysicalDeviceLimits::maxComputeWorkGroupCount[0]
        cudaLaunchInfoNV.gridDimY = 1;//Ϊdispatch��local workgroups �� Y ά�ȵ�����,����С�ڵ��� VkPhysicalDeviceLimits::maxComputeWorkGroupCount[1]
        cudaLaunchInfoNV.gridDimZ = 1;//Ϊdispatch��local workgroups �� Z ά�ȵ�����,����С�ڵ��� VkPhysicalDeviceLimits::maxComputeWorkGroupCount[2]
        cudaLaunchInfoNV.blockDimX = 1;//ΪX ά�ȵĿ��С
        cudaLaunchInfoNV.blockDimY = 1;//ΪY ά�ȵĿ��С
        cudaLaunchInfoNV.blockDimZ = 1;//ΪZ ά�ȵĿ��С
        cudaLaunchInfoNV.sharedMemBytes = 0;//��ÿ���߳̿�Ķ�̬�����ڴ��С��
        cudaLaunchInfoNV.paramCount = 1;//pParams��Ԫ�ظ���
        cudaLaunchInfoNV.pParams = nullptr;//ÿ����ӦΪ���ݸ�function�Ĳ�����function��Ҫ��������������͵��ṩ��������
        cudaLaunchInfoNV.extraCount = 0;//����δ��ʹ��
        cudaLaunchInfoNV.pExtras = nullptr;//����δ��ʹ��
        /*
        VkCudaLaunchInfoNV��Ч�÷�:
        1.gridDimX����С�ڵ��� VkPhysicalDeviceLimits::maxComputeWorkGroupCount[0],gridDimY����С�ڵ��� VkPhysicalDeviceLimits::maxComputeWorkGroupCount[1],gridDimZ����С�ڵ��� VkPhysicalDeviceLimits::maxComputeWorkGroupCount[2]
        2.paramCount�������pParams���оٵĲ�������
        3.pParams����ָ��paramCount�����������飬��Щ������Ӧfunction����Ҫ�Ĳ���
        4.extraCount ����Ϊ0��pExtras����ΪNULL

        */


        //��¼ CUDA kernel launch����    ��������ִ�л���װ����gridDimX �� gridDimY �� gridDimZ ��local workgroups��global workgroup
        vkCmdCudaLaunchKernelNV(commandBuffer, &cudaLaunchInfoNV/*pLaunchInfo,Ϊһ��VkCudaLaunchInfoNV����ָ�룬����grid(������workgroup) dimension , function handle �Լ���ز���.*/);
    


        // Resource Sharing from Vulkan to the CUDA Kernel    ������δ�vulkan ���ݵ�cuda������,�򵥽�����vulkan����ֱ�ӷ���cuda����Դ�������޸ģ�ֻ�ܴ��θ�cuda��������cuda�Լ�ȥ�����Լ����ʾ�������   p2902

    }

}

void DispatchingAndDeviceGeneratedCommandsTest::DeviceGeneratedCommandsTest()
{
    /*
    �����device������command buffer�е�commands���ݣ���Ҫ�������²���:
    > ͨ�� VkIndirectCommandsLayoutNV ָ��command buffer�����ɵ�commands��˳��
    > ��ѡ���ʹ��graphics pipelines�ܹ��󶨵�shader groups
    > ͨ��vkGetBufferDeviceAddressEXT��ȡ����buffers���豸��ַ
    > ͨ��vkGetPipelineIndirectDeviceAddressNV��ȡ���԰�����device generated rendering��compute pipeline���豸��ַ
    > ���һ�����߶��VkBuffer�����е����ݻᱻ����ΪVkIndirectCommandsLayoutNV
    > ʹ��vkGetGeneratedCommandsMemoryRequirementsNV��ȡ�ķ�����Ϣ����һ��Ԥ����VkBuffer��
    > ��ѡ����һ������Ķ�����ͨ��vkCmdPreprocessGeneratedCommandsNV Ԥ������������
    > ����������Ҫ������Ȼ��ͨ��vkCmdExecuteGeneratedCommandsNV�����Լ�ִ��ʵ�ʵ�commands
    */



}



NS_TEST_END