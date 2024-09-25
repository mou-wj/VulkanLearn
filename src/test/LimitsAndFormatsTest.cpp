#include "LimitsAndFormatsTest.h"
NS_TEST_BEGIN
LimitsAndFormatsTest::LimitsAndFormatsTest()
{
}

void LimitsAndFormatsTest::run()
{
}

LimitsAndFormatsTest::~LimitsAndFormatsTest()
{
}

void LimitsAndFormatsTest::LimitsTest()
{
	//limits��Ӧ����Ҫ��ʶ���� ����ʵ�ֵĵ���С���ƣ���������Լ�����device���Ե����ƣ���Щ���Ƽ� VkPhysicalDeviceLimits ����VkPhysicalDeviceProperties����VkPhysicalDeviceProperties2����������properties
    VkPhysicalDeviceProperties physicalDeviceProperties{};
    vkGetPhysicalDeviceProperties(physicalDevice, &physicalDeviceProperties);


	VkPhysicalDeviceLimits &physicalDeviceLimits = physicalDeviceProperties.limits;
    physicalDeviceLimits.maxImageDimension1D;//ָ���ɴ�����imageTypeΪVK_IMAGE_TYPE_1D ��image��width�����ֵ����ĳЩimage������������£���ֵ���ܳ��������оٵ�ֵ�������vkGetPhysicalDeviceImageFormatProperties
    physicalDeviceLimits.maxImageDimension2D;//ָ���ɴ�����imageTypeΪVK_IMAGE_TYPE_2D�Ҳ���VK_IMAGE_CREATE_CUBE_COMPATIBLE_BIT ��image��width ���� height�����ֵ����ĳЩimage������������£���ֵ���ܳ��������оٵ�ֵ�������vkGetPhysicalDeviceImageFormatProperties
    physicalDeviceLimits.maxImageDimension3D;//ָ���ɴ�����imageTypeΪ VK_IMAGE_TYPE_3D ��image��width ��height����depth �����ֵ����ĳЩimage������������£���ֵ���ܳ��������оٵ�ֵ�������vkGetPhysicalDeviceImageFormatProperties
    physicalDeviceLimits.maxImageDimensionCube;//ָ���ɴ�����imageTypeΪVK_IMAGE_TYPE_2D�Һ�VK_IMAGE_CREATE_CUBE_COMPATIBLE_BIT ��image��width ���� height�����ֵ����ĳЩimage������������£���ֵ���ܳ��������оٵ�ֵ�������vkGetPhysicalDeviceImageFormatProperties
    physicalDeviceLimits.maxImageArrayLayers;//Ϊimage������layer��
    physicalDeviceLimits.maxTexelBufferElements;//Ϊһ����VK_BUFFER_USAGE_UNIFORM_TEXEL_BUFFER_BIT ���� VK_BUFFER_USAGE_STORAGE_TEXEL_BUFFER_BIT ������buffer��buffer view�п�Ѱַ��texel���������
    physicalDeviceLimits.maxUniformBufferRange;//ָ����VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER ���� VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC���͵�descriptors�Ĵ��ݸ� vkUpdateDescriptorSets��VkDescriptorBufferInfo.range���������ֵ
    physicalDeviceLimits.maxStorageBufferRange;//ָ����VK_DESCRIPTOR_TYPE_STORAGE_BUFFER ���� VK_DESCRIPTOR_TYPE_STORAGE_BUFFER_DYNAMIC���͵�descriptors�Ĵ��ݸ� vkUpdateDescriptorSets��VkDescriptorBufferInfo.range���������ֵ
    physicalDeviceLimits.maxPushConstantsSize;//Ϊpush constance �ڴ�ص�����ֽڴ�С����VkPipelineLayoutCreateInfo.pPushConstantRanges��ÿ��Ԫ�صģ�size + offset������С�ڸ�ֵ
    physicalDeviceLimits.maxMemoryAllocationCount;//ΪvkAllocateMemory �����device memory������������
    physicalDeviceLimits.maxSamplerAllocationCount;//ΪvkCreateSampler ������sampler������������
    physicalDeviceLimits.bufferImageGranularity;//Ϊ buffer ���� linear image resources����optimal image resources������ͬһVkDeviceMemory�������ڽӰ��Ҳ��ظ����ֽ�����
    physicalDeviceLimits.sparseAddressSpaceSize;//Ϊsparse memory resources���ܵĿ��õĵ�ַ�ֽڿռ䣬���� extendedSparseAddressSpace ���Ծ���Ķ���Ŀ��ÿռ���ܻᱻ��չ
    physicalDeviceLimits.maxBoundDescriptorSets;//Ϊpipelineͬһʱ�����ʹ�õ�descriptor set����������shader module��DescriptorSet��������С�ڸ�ֵ
    physicalDeviceLimits.maxPerStageDescriptorSamplers;//Ϊpipeline layout��һ��shader stage�п��Է��ʵ�sampler�����������ֻ�з���������ͻ�������������descriptor�Ż��������ƣ���p3912
    physicalDeviceLimits.maxPerStageDescriptorUniformBuffers;//Ϊpipeline layout��һ��shader stage�п��Է��ʵ�uniform buffers�����������ֻ�з���������ͻ�������������descriptor�Ż��������ƣ���p3912
    physicalDeviceLimits.maxPerStageDescriptorStorageBuffers;//Ϊpipeline layout��һ��shader stage�п��Է��ʵ�storage buffers�����������ֻ�з���������ͻ�������������descriptor�Ż��������ƣ���p3913
    physicalDeviceLimits.maxPerStageDescriptorSampledImages;//Ϊpipeline layout��һ��shader stage�п��Է��ʵ�sampled images�����������ֻ�з���������ͻ�������������descriptor�Ż��������ƣ���p3913
    physicalDeviceLimits.maxPerStageDescriptorStorageImages;//Ϊpipeline layout��һ��shader stage�п��Է��ʵ�storage images�����������ֻ�з���������ͻ�������������descriptor�Ż��������ƣ���p3913
    physicalDeviceLimits.maxPerStageDescriptorInputAttachments;//Ϊpipeline layout��һ��shader stage�п��Է��ʵ�input attachment�����������ֻ�з���������ͻ�������������descriptor�Ż��������ƣ���p3913
    physicalDeviceLimits.maxPerStageResources;//Ϊpipeline layout��һ��shader stage�п��Է��ʵ���Դresources�����������ֻ�з���������ͻ�������������descriptor�Ż��������ƣ���p3913
    physicalDeviceLimits.maxDescriptorSetSamplers;//Ϊһ��pipeline layout�п��԰�����samplers�����������ֻ�з���������ͻ�������������descriptor�Ż��������ƣ���p3914
    physicalDeviceLimits.maxDescriptorSetUniformBuffers;//Ϊһ��pipeline layout�п��԰�����uniform buffers�����������ֻ�з���������ͻ�������������descriptor�Ż��������ƣ���p3914
    physicalDeviceLimits.maxDescriptorSetUniformBuffersDynamic;//Ϊһ��pipeline layout�п��԰�����dynamic uniform buffers�����������ֻ�з���������ͻ�������������descriptor�Ż��������ƣ���p3914
    physicalDeviceLimits.maxDescriptorSetStorageBuffers;//Ϊһ��pipeline layout�п��԰����� storage buffers�����������ֻ�з���������ͻ�������������descriptor�Ż��������ƣ���p3914
    physicalDeviceLimits.maxDescriptorSetStorageBuffersDynamic;//Ϊһ��pipeline layout�п��԰�����dynamic storage buffers�����������ֻ�з���������ͻ�������������descriptor�Ż��������ƣ���p3914
    physicalDeviceLimits.maxDescriptorSetSampledImages;//Ϊһ��pipeline layout�п��԰�����sampled images�����������ֻ�з���������ͻ�������������descriptor�Ż��������ƣ���p3914
    physicalDeviceLimits.maxDescriptorSetStorageImages;//Ϊһ��pipeline layout�п��԰�����storage images�����������ֻ�з���������ͻ�������������descriptor�Ż��������ƣ���p3914
    physicalDeviceLimits.maxDescriptorSetInputAttachments;//Ϊһ��pipeline layout�п��԰�����input attachment�����������ֻ�з���������ͻ�������������descriptor�Ż��������ƣ���p3914
    physicalDeviceLimits.maxVertexInputAttributes;//Ϊgraphics pipeline�п���ָ����vertex input attributes�������������ϸ������p3915
    physicalDeviceLimits.maxVertexInputBindings;//Ϊgraphics pipeline�п���ָ�����ṩvertex input attributes��vertex buffer�������������ϸ������p3915
    physicalDeviceLimits.maxVertexInputAttributeOffset;//Ϊ������ӵ� vertex input binding stride��vertex input attribute offset�����ֵ����ϸ������p3915
    physicalDeviceLimits.maxVertexInputBindingStride;//Ϊһ�� vertex input binding�п���ָ����vertex input binding stride�����ֵ����ϸ������p3915
    physicalDeviceLimits.maxVertexOutputComponents;//Ϊshader ������������������ֵ
    physicalDeviceLimits.maxTessellationGenerationLevel;//Ϊfixed-function tessellation primitive generator ֧�ֵ� tessellation generation level�����ֵ
    physicalDeviceLimits.maxTessellationPatchSize;//Ϊtessellation control shader �Լ� tessellation primitive generator���Դ����ÿ��patch�Ķ����������ֵ����ϸ������p3915 
    physicalDeviceLimits.maxTessellationControlPerVertexInputComponents;//Ϊ�����ṩ�� tessellation control shader stage��Ϊper-vertex inputs����������ķ�����������С
    physicalDeviceLimits.maxTessellationControlPerVertexOutputComponents;//Ϊ���Դ� tessellation control shader stage�����per-vertex output variables�ķ�����������С
    physicalDeviceLimits.maxTessellationControlPerPatchOutputComponents;//Ϊ���Դ� tessellation control shader stage�����per-patch output variables�ķ�����������С
    physicalDeviceLimits.maxTessellationControlTotalOutputComponents;//Ϊ���Դ� tessellation control shader stage�����per-vertex �Լ� per-patch output variables�ķ�������������С
    physicalDeviceLimits.maxTessellationEvaluationInputComponents;//Ϊ�����ṩ�� tessellation evaluation shader stage��Ϊper-vertex inputs����������ķ�����������С
    physicalDeviceLimits.maxTessellationEvaluationOutputComponents;//Ϊ���Դ� tessellation evaluation shader stage�����per-vertex output variables�ķ�����������С
    physicalDeviceLimits.maxGeometryShaderInvocations;//Ϊinstanced geometry shaders���Ե��õ��������
    physicalDeviceLimits.maxGeometryInputComponents;//Ϊ�����ṩ�� geometry shader stage��Ϊinputs����������ķ�����������С
    physicalDeviceLimits.maxGeometryOutputComponents;//Ϊ���Դ� geometry shader stage�����output variables�ķ�����������С
    physicalDeviceLimits.maxGeometryOutputVertices;//Ϊ�κ�geometry shader ���Է������󶥵���
    physicalDeviceLimits.maxGeometryTotalOutputComponents;//Ϊ���Դ� geometry shader stage��������з��䶥���output variables�ķ���������������С
    physicalDeviceLimits.maxFragmentInputComponents;//Ϊ�����ṩ�� fragment shader stage��Ϊinputs����������ķ�����������С
    physicalDeviceLimits.maxFragmentOutputAttachments;//Ϊ���Դ� fragment shader stage����д���ĵ�output attachments���������
    physicalDeviceLimits.maxFragmentDualSrcAttachments;//Ϊ������blending��ʹ����һ��dual source blend modesʱ���Դ� fragment shader stage����д���ĵ�output attachments���������
    physicalDeviceLimits.maxFragmentCombinedOutputResources;//Ϊ fragment shader stage�п���ʹ�õ� storage buffers, storage images�Լ� Location ��������� color attachments���������������
    physicalDeviceLimits.maxComputeSharedMemorySize;//Ϊcompute shader stage �� shader modules ���� Workgroup storage class ����������GLSL����shared�������ı���������ֽڴ洢��С
    physicalDeviceLimits.maxComputeWorkGroupCount[3];//Ϊһ��dispatching command �ɷ���local workgroups������С���ֱ��ӦX��Y��Z
    physicalDeviceLimits.maxComputeWorkGroupInvocations;//Ϊһ��local workgroup�п��Ե��õ�compute shader�ܹ���������������������p3916
    physicalDeviceLimits.maxComputeWorkGroupSize[3];//Ϊÿ��ά�� local compute workgroup������С�����������p3916
    physicalDeviceLimits.subPixelPrecisionBits;//Ϊframebuffer coordinates��subpixel ���ȵ����bit��
    physicalDeviceLimits.subTexelPrecisionBits;//Ϊ��������minification and magnification filters��image����Ļ��־��ȵ�bit�������������p3916
    physicalDeviceLimits.mipmapPrecisionBits;//��ȷ��ÿ�� mip ���� mip ���˽���Ĺ���ʱ���� mipmap ���ص� LOD ������нض�ʱ��ʹ�õ�λ���������������p3916
    physicalDeviceLimits.maxDrawIndexedIndexValue;//Ϊʹ��32-bit ����ʱindexed draw calls����ʹ�õ��������ֵ
    physicalDeviceLimits.maxDrawIndirectCount;//Ϊ indirect drawing calls ����֧�ֵ����draw count
    physicalDeviceLimits.maxSamplerLodBias;//Ϊabsolute sampler LOD bias�����ֵ��������Ϣ��p3917
    physicalDeviceLimits.maxSamplerAnisotropy;//Ϊ sampler anisotropy����󼶱�������Ϣ��p3917
    physicalDeviceLimits.maxViewports;//Ϊ active viewports�����������������Ϣ��p3917
    physicalDeviceLimits.maxViewportDimensions[2];//Ϊ viewportά��width�Լ�height�����ֵ��������Ϣ��p3917
    physicalDeviceLimits.viewportBoundsRange[2];//Ϊviewport��corners��������� [minimum, maximum]��Χ��������Ϣ��p3917
    physicalDeviceLimits.viewportSubPixelBits;//Ϊviewport�߽��subpixel���ȵ�bit��
    physicalDeviceLimits.minMemoryMapAlignment;//Ϊ��host�ڴ�ռ�����host �ɼ���memory�ڴ������ֽڶ������Сֵ��������Ϣ��p3917
    physicalDeviceLimits.minTexelBufferOffsetAlignment;//Ϊtexel buffers�� VkBufferViewCreateInfo.offset���Ե��ֽڶ������Сֵ��Ϊ2��ָ����������Ϣ��p3917
    physicalDeviceLimits.minUniformBufferOffsetAlignment;//Ϊuniform buffers�� VkDescriptorBufferInfo.offset���Ե��ֽڶ������Сֵ��Ϊ2��ָ����������Ϣ��p3917
    physicalDeviceLimits.minStorageBufferOffsetAlignment;//Ϊstorage buffers�� VkDescriptorBufferInfo.offset���Ե��ֽڶ������Сֵ��Ϊ2��ָ����������Ϣ��p3917
    physicalDeviceLimits.minTexelOffset;//Ϊ�κ�OpImageSample* ���� OpImageFetch*  imageָ���ConstOffset image����������Сƫ��ֵ
    physicalDeviceLimits.maxTexelOffset;//Ϊ�κ�OpImageSample* ���� OpImageFetch*  imageָ���ConstOffset image�����������ƫ��ֵ
    physicalDeviceLimits.minTexelGatherOffset;//Ϊ�κ� OpImage*Gather  imageָ���Offset, ConstOffset, ���� ConstOffsets image����������Сƫ��ֵ
    physicalDeviceLimits.maxTexelGatherOffset;//Ϊ�κ� OpImage*Gather  imageָ���Offset, ConstOffset, ���� ConstOffsets image����������Сƫ��ֵ
    physicalDeviceLimits.minInterpolationOffset;//ΪInterpolateAtOffset ��չָ��� Offset����������С����Сֵ
    physicalDeviceLimits.maxInterpolationOffset;//ΪInterpolateAtOffset ��չָ��� Offset����������������ֵ
    physicalDeviceLimits.subPixelInterpolationOffsetBits;//ִ��InterpolateAtOffset��չָ��ʱ��x��yƫ���������Զ���ֵ���������С��λ��
    physicalDeviceLimits.maxFramebufferWidth;//Ϊframebuffer��width�����ֵ
    physicalDeviceLimits.maxFramebufferHeight;//Ϊframebuffer��height�����ֵ
    physicalDeviceLimits.maxFramebufferLayers;//Ϊframebuffer�к���layers���������
    physicalDeviceLimits.framebufferColorSampleCounts;//Ϊ���и�ʽΪ������߶�������framebuffer color attachments֧�ֵ�sample counts��VkSampleCountFlagBits���ֵ
    physicalDeviceLimits.framebufferDepthSampleCounts;//Ϊ���и�ʽ����depth��framebuffer depth/stencil attachments֧�ֵ�depth sample counts��VkSampleCountFlagBits���ֵ
    physicalDeviceLimits.framebufferStencilSampleCounts;//Ϊ���и�ʽ����stencil��framebuffer depth/stencil attachments֧�ֵ�stencil sample counts��VkSampleCountFlagBits���ֵ
    physicalDeviceLimits.framebufferNoAttachmentsSampleCounts;//Ϊ����������subpass ֧�ֵ�sample counts��VkSampleCountFlagBits���ֵ
    physicalDeviceLimits.maxColorAttachments;//Ϊrender pass��subpass����ʹ�õ�color attachments���������
    physicalDeviceLimits.sampledImageColorSampleCounts;// VkSampleCountFlagBits ���ֵλ���룬ָ��������VK_IMAGE_TILING_OPTIMAL�����ģ�usage����VK_IMAGE_USAGE_SAMPLED_BIT�Һ�non-integer color format������2D image֧�ֵ�sample counts
    physicalDeviceLimits.sampledImageIntegerSampleCounts;// VkSampleCountFlagBits ���ֵλ���룬ָ��������VK_IMAGE_TILING_OPTIMAL�����ģ�usage����VK_IMAGE_USAGE_SAMPLED_BIT�Һ�integer color format������2D image֧�ֵ�sample counts
    physicalDeviceLimits.sampledImageDepthSampleCounts;// VkSampleCountFlagBits ���ֵλ���룬ָ��������VK_IMAGE_TILING_OPTIMAL�����ģ�usage����VK_IMAGE_USAGE_SAMPLED_BIT�Һ�depth format������2D image֧�ֵ�sample counts
    physicalDeviceLimits.sampledImageStencilSampleCounts;// VkSampleCountFlagBits ���ֵλ���룬ָ��������VK_IMAGE_TILING_OPTIMAL�����ģ�usage����VK_IMAGE_USAGE_SAMPLED_BIT�Һ�stencil format������2D image֧�ֵ�sample counts
    physicalDeviceLimits.storageImageSampleCounts;// VkSampleCountFlagBits ���ֵλ���룬ָ��������VK_IMAGE_TILING_OPTIMAL�����ģ�usage����VK_IMAGE_USAGE_STORAGE_BIT������2D image֧�ֵ�sample counts
    physicalDeviceLimits.maxSampleMaskWords;//Ϊ��SampleMask �����ı���������Ԫ�ص��������
    physicalDeviceLimits.timestampComputeAndGraphics;//ָ��֧������graphics �Լ� compute queues�ϵ�timestamps��������Ϣ��p3919
    physicalDeviceLimits.timestampPeriod;//Ϊtimastamp query����1����Ҫ��������
    physicalDeviceLimits.maxClipDistances;//Ϊ������һ��shader stage�� clip distances�����ֵ
    physicalDeviceLimits.maxCullDistances;//Ϊ������һ��shader stage�� cull distances�����ֵ
    physicalDeviceLimits.maxCombinedClipAndCullDistances;//Ϊ������һ��shader stage�İ󶨵� clip�Լ�cull distances�����������ֵ
    physicalDeviceLimits.discreteQueuePriorities;//Ϊ���� VkDeviceQueueCreateInfo::pQueuePriorities��ÿ��Ԫ��ֵ�Ŀ�������Ϊ���е���ɢ���Ե��������
    physicalDeviceLimits.pointSizeRange[2];//Ϊpoint size�� PointSize��Ƕ������֧�ֵĴ�С��Χ[minimum,maximum]
    physicalDeviceLimits.lineWidthRange[2];//Ϊ�߿� ��դ�� lineWidth������֧�ֵĴ�С��Χ[minimum,maximum]
    physicalDeviceLimits.pointSizeGranularity;//Ϊpoint size�� PointSize��Ƕ������֧�ֵĴ�С��Χ�ڵļ������
    physicalDeviceLimits.lineWidthGranularity;//Ϊ�߿� ��դ�� lineWidth������֧�ֵĴ�С��Χ�ڵļ������
    physicalDeviceLimits.strictLines;//ָ���Ƿ��߰�����ѡ�������й�դ����������Ϣ��p3920
    physicalDeviceLimits.standardSampleLocations;//ָ���Ƿ��դ���Ƿ��Ƿ��׼�Ĳ�����λ�ã�������Ϣ��p3920
    physicalDeviceLimits.optimalBufferCopyOffsetAlignment;//Ϊ��ѵ�buffer offset alignment�������ֽڣ�������:vkCmdCopyBufferToImage2, vkCmdCopyBufferToImage, vkCmdCopyImageToBuffer2, vkCmdCopyImageToBuffer,vkCopyMemoryToImageEXT �Լ� vkCopyImageToMemoryEXT
    physicalDeviceLimits.optimalBufferCopyRowPitchAlignment;//Ϊ��ѵ�buffer row pitch alignment�������ֽڣ�������:vkCmdCopyBufferToImage2, vkCmdCopyBufferToImage, vkCmdCopyImageToBuffer2, vkCmdCopyImageToBuffer,vkCopyMemoryToImageEXT �Լ� vkCopyImageToMemoryEXT
    physicalDeviceLimits.nonCoherentAtomSize;//Ϊ�������� host-mapped device memoryʱ���ڴ淶Χ���ֽڴ�С�Լ��ֽڶ���


    //VkSampleCountFlagBits
    VkSampleCountFlagBits sampleCountFlagBits{};
    /*
    VK_SAMPLE_COUNT_1_BIT  : ָ��һ��image�� one sample per pixel.
    VK_SAMPLE_COUNT_2_BIT  : ָ��һ��image�� 2 samples per pixel.
    VK_SAMPLE_COUNT_4_BIT  : ָ��һ��image�� 4 samples per pixel.
    VK_SAMPLE_COUNT_8_BIT  : ָ��һ��image�� 8 samples per pixel.
    VK_SAMPLE_COUNT_16_BIT  : ָ��һ��image�� 16 samples per pixel.
    VK_SAMPLE_COUNT_32_BIT  : ָ��һ��image�� 32 samples per pixel.
    VK_SAMPLE_COUNT_64_BIT  : ָ��һ��image�� 64 samples per pixel.  
    */


    //��ȡ���Ժ�limit
    VkPhysicalDeviceProperties2 physicalDeviceProperties2{};
    vkGetPhysicalDeviceProperties2(physicalDevice, &physicalDeviceProperties2);


    //VkPhysicalDevicePushDescriptorPropertiesKHR  ,���԰�����VkPhysicalDeviceProperties2.pNext��
    VkPhysicalDevicePushDescriptorPropertiesKHR physicalDevicePushDescriptorPropertiesKHR{};
    physicalDevicePushDescriptorPropertiesKHR.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PUSH_DESCRIPTOR_PROPERTIES_KHR;
    physicalDevicePushDescriptorPropertiesKHR.pNext = nullptr;
    physicalDevicePushDescriptorPropertiesKHR.maxPushDescriptors = 10;//ָ����VK_DESCRIPTOR_SET_LAYOUT_CREATE_PUSH_DESCRIPTOR_BIT_KHR������descriptor set layout�п���ʹ�õ�descriptors���������


    //VkPhysicalDeviceMultiviewProperties  ���ȼ���VkPhysicalDeviceMultiviewPropertiesKHR,���԰�����VkPhysicalDeviceProperties2.pNext��
    VkPhysicalDeviceMultiviewProperties physicalDeviceMultiviewProperties{};
    physicalDeviceMultiviewProperties.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MULTIVIEW_PROPERTIES;
    physicalDeviceMultiviewProperties.pNext = nullptr;
    physicalDeviceMultiviewProperties.maxMultiviewViewCount = 10;//Ϊ����subpass�п���ʹ�õ�viewport���������ֵ��1����
    physicalDeviceMultiviewProperties.maxMultiviewInstanceIndex = 10;//Ϊһ����multiview render pass ʵ���м�¼�Ļ������������ɵ�instance index�����ֵ


    //VkPhysicalDeviceFloatControlsProperties  ���ȼ���VkPhysicalDeviceFloatControlsPropertiesKHR,���԰�����VkPhysicalDeviceProperties2.pNext��
    VkPhysicalDeviceFloatControlsProperties physicalDeviceFloatControlsProperties{};
    physicalDeviceFloatControlsProperties.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FLOAT_CONTROLS_PROPERTIES_KHR;
    physicalDeviceFloatControlsProperties.pNext = nullptr;
    physicalDeviceFloatControlsProperties.denormBehaviorIndependence = VK_SHADER_FLOAT_CONTROLS_INDEPENDENCE_ALL;//һ�� VkShaderFloatControlsIndependence ֵ��ָ�� denorm behavior�ܹ���������Ƿ�Բ�ͬ��bit��Ƚ��ж���������
    /*
    VkShaderFloatControlsIndependence �ȼ���VkShaderFloatControlsIndependenceKHR:
    VK_SHADER_FLOAT_CONTROLS_INDEPENDENCE_32_BIT_ONLY : ָ��shader float controls��32-bit�������Ŀ��Ե������ã������������͵�bit��ȱ��������������Ϊ��ͬ��
    VK_SHADER_FLOAT_CONTROLS_INDEPENDENCE_ALL specifies : ָ��shader float controls������bit��ȿ��Ե�������
    VK_SHADER_FLOAT_CONTROLS_INDEPENDENCE_NONE specifies : ָ��shader float controls������bit��ȱ�������Ϊ��ͬ��

    */
    physicalDeviceFloatControlsProperties.roundingModeIndependence = VK_SHADER_FLOAT_CONTROLS_INDEPENDENCE_ALL;//һ�� VkShaderFloatControlsIndependence ֵ��ָ��rounding modes�ܹ���������Ƿ�Բ�ͬ��bit��Ƚ��ж���������
    physicalDeviceFloatControlsProperties.shaderSignedZeroInfNanPreserveFloat16 = VK_FALSE;//ָ������0��NaN�Լ������Ƿ���16-bit��������б�������Ҳָ���Ƿ�SignedZeroInfNanPreserve execution mode������16-bit��������
    physicalDeviceFloatControlsProperties.shaderSignedZeroInfNanPreserveFloat32 = VK_FALSE;//ָ������0��NaN�Լ������Ƿ���32-bit��������б�������Ҳָ���Ƿ�SignedZeroInfNanPreserve execution mode������32-bit��������
    physicalDeviceFloatControlsProperties.shaderSignedZeroInfNanPreserveFloat64 = VK_FALSE;//ָ������0��NaN�Լ������Ƿ���64-bit��������б�������Ҳָ���Ƿ�SignedZeroInfNanPreserve execution mode������64-bit��������
    physicalDeviceFloatControlsProperties.shaderDenormPreserveFloat16 = VK_FALSE;//ָ��denormals �ǹ�����Ƿ���16-bit��������б�������Ҳָ���Ƿ�DenormPreserve execution mode������16-bit��������
    physicalDeviceFloatControlsProperties.shaderDenormPreserveFloat32 = VK_FALSE;//ָ��denormals �ǹ�����Ƿ���32-bit��������б�������Ҳָ���Ƿ�DenormPreserve execution mode������32-bit��������
    physicalDeviceFloatControlsProperties.shaderDenormPreserveFloat64 = VK_FALSE;//ָ��denormals �ǹ�����Ƿ���64-bit��������б�������Ҳָ���Ƿ�DenormPreserve execution mode������64-bit��������
    physicalDeviceFloatControlsProperties.shaderDenormFlushToZeroFloat16 = VK_FALSE;//ָ��denormals �ǹ�����Ƿ���16-bit��������б�ˢ��Ϊ0��Ҳָ���Ƿ�DenormFlushToZero execution mode������16-bit��������
    physicalDeviceFloatControlsProperties.shaderDenormFlushToZeroFloat32 = VK_FALSE;//ָ��denormals �ǹ�����Ƿ���32-bit��������б�ˢ��Ϊ0��Ҳָ���Ƿ�DenormFlushToZero execution mode������32-bit��������
    physicalDeviceFloatControlsProperties.shaderDenormFlushToZeroFloat64 = VK_FALSE;//ָ��denormals �ǹ�����Ƿ���64-bit��������б�ˢ��Ϊ0��Ҳָ���Ƿ�DenormFlushToZero execution mode������64-bit��������
    physicalDeviceFloatControlsProperties.shaderRoundingModeRTEFloat16 = VK_FALSE;//ָ���Ƿ���16-bit�����㷨��ת��ָ����֧��round-to-nearest-even rounding mode��Ҳָ���Ƿ�RoundingModeRTE execution mode������16-bit��������
    physicalDeviceFloatControlsProperties.shaderRoundingModeRTEFloat32 = VK_FALSE;//ָ���Ƿ���32-bit�����㷨��ת��ָ����֧��round-to-nearest-even rounding mode��Ҳָ���Ƿ�RoundingModeRTE execution mode������32-bit��������
    physicalDeviceFloatControlsProperties.shaderRoundingModeRTEFloat64 = VK_FALSE;//ָ���Ƿ���64-bit�����㷨��ת��ָ����֧��round-to-nearest-even rounding mode��Ҳָ���Ƿ�RoundingModeRTE execution mode������64-bit��������
    physicalDeviceFloatControlsProperties.shaderRoundingModeRTZFloat16 = VK_FALSE;//ָ���Ƿ���16-bit�����㷨��ת��ָ����֧��round-towards-zero rounding mode��Ҳָ���Ƿ�RoundingModeRTZ execution mode������16-bit��������
    physicalDeviceFloatControlsProperties.shaderRoundingModeRTZFloat32 = VK_FALSE;//ָ���Ƿ���32-bit�����㷨��ת��ָ����֧��round-towards-zero rounding mode��Ҳָ���Ƿ�RoundingModeRTZ execution mode������32-bit��������
    physicalDeviceFloatControlsProperties.shaderRoundingModeRTZFloat64 = VK_FALSE;//ָ���Ƿ���64-bit�����㷨��ת��ָ����֧��round-towards-zero rounding mode��Ҳָ���Ƿ�RoundingModeRTZ execution mode������64-bit��������



    //VkPhysicalDeviceDiscardRectanglePropertiesEXT ,���԰�����VkPhysicalDeviceProperties2.pNext��
    VkPhysicalDeviceDiscardRectanglePropertiesEXT physicalDeviceDiscardRectanglePropertiesEXT{};
    physicalDeviceDiscardRectanglePropertiesEXT.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DISCARD_RECTANGLE_PROPERTIES_EXT;
    physicalDeviceDiscardRectanglePropertiesEXT.pNext = nullptr;
    physicalDeviceDiscardRectanglePropertiesEXT.maxDiscardRectangles = 10;//Ϊ����ָ����active discard rectangles���������


    //VkPhysicalDeviceSampleLocationsPropertiesEXT ,���԰�����VkPhysicalDeviceProperties2.pNext��
    VkPhysicalDeviceSampleLocationsPropertiesEXT physicalDeviceSampleLocationsPropertiesEXT{};
    physicalDeviceSampleLocationsPropertiesEXT.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SAMPLE_LOCATIONS_PROPERTIES_EXT;
    physicalDeviceSampleLocationsPropertiesEXT.pNext = nullptr;
    physicalDeviceSampleLocationsPropertiesEXT.sampleLocationSampleCounts;//Ϊ VkSampleCountFlagBits ���ֵλ���룬ָ��sample count֧���Զ��������λ��
    physicalDeviceSampleLocationsPropertiesEXT.maxSampleLocationGridSize;//Ϊ sampleLocationSampleCounts ��֧�ֵ����в���������в�ͬλ�õ� pixel grid ������С
    physicalDeviceSampleLocationsPropertiesEXT.sampleLocationCoordinateRange[2];//Ϊ֧�ֵ�sample location coordinates�ķ�Χ
	physicalDeviceSampleLocationsPropertiesEXT.sampleLocationSubPixelBits;//sample locations��subpixel���ȵ�bit��
	physicalDeviceSampleLocationsPropertiesEXT.variableSampleLocations;//ָ����������pipeline���Ұ󶨵�command buffer��subpass�е�sample locations����ƥ�䣬���ΪVK_TRUE��������ͬsubpass��sample locations��ͬ�����������ͬ


    //VkPhysicalDeviceLegacyVertexAttributesPropertiesEXT ,���԰�����VkPhysicalDeviceProperties2.pNext��
    VkPhysicalDeviceLegacyVertexAttributesPropertiesEXT physicalDeviceLegacyVertexAttributesPropertiesEXT{};
    physicalDeviceLegacyVertexAttributesPropertiesEXT.sType = VK_STRUCTURE_TYPE_MAX_ENUM;//û�ж������ﶨ��Ϊ�Ƿ�ֵ
    physicalDeviceLegacyVertexAttributesPropertiesEXT.pNext = nullptr;
    physicalDeviceLegacyVertexAttributesPropertiesEXT.nativeUnalignedPerformance = VK_FALSE;//ָ������� aligned fetches��unaligned vertex fetches ����������Ե���ʾ����


    //VkPhysicalDeviceExternalMemoryHostPropertiesEXT ,���԰�����VkPhysicalDeviceProperties2.pNext��
    VkPhysicalDeviceExternalMemoryHostPropertiesEXT physicalDeviceExternalMemoryHostPropertiesEXT{};
    physicalDeviceExternalMemoryHostPropertiesEXT.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_EXTERNAL_MEMORY_HOST_PROPERTIES_EXT;
    physicalDeviceExternalMemoryHostPropertiesEXT.pNext = nullptr;
	physicalDeviceExternalMemoryHostPropertiesEXT.minImportedHostPointerAlignment = VK_FALSE;//ָ�����Ե��뵽vulkan �����hostָ��Ļ���ַ�Լ���С���ֽڶ���Ҫ�󣬱�����2��ָ��


    //VkPhysicalDeviceMultiviewPerViewAttributesPropertiesNVX ,���԰�����VkPhysicalDeviceProperties2.pNext��
    VkPhysicalDeviceMultiviewPerViewAttributesPropertiesNVX physicalDeviceMultiviewPerViewAttributesPropertiesNVX{};
    physicalDeviceMultiviewPerViewAttributesPropertiesNVX.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MULTIVIEW_PER_VIEW_ATTRIBUTES_PROPERTIES_NVX;
    physicalDeviceMultiviewPerViewAttributesPropertiesNVX.pNext = nullptr;
    physicalDeviceMultiviewPerViewAttributesPropertiesNVX.perViewPositionAllComponents = VK_FALSE;//ָ���Ƿ�֧�� per-view��λ�õ������������Ժ�X������ͬ


    //VkPhysicalDevicePointClippingProperties����ͬ�� VkPhysicalDevicePointClippingPropertiesKHR ,���԰�����VkPhysicalDeviceProperties2.pNext��
    VkPhysicalDevicePointClippingProperties physicalDevicePointClippingProperties{};
    physicalDevicePointClippingProperties.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_POINT_CLIPPING_PROPERTIES;
    physicalDevicePointClippingProperties.pNext = nullptr;
	physicalDevicePointClippingProperties.pointClippingBehavior;//һ��VkPointClippingBehavior ֵָ��֧�ֵ�point clipping behavior


    //VkPhysicalDeviceSubgroupProperties  ,���԰�����VkPhysicalDeviceProperties2.pNext��
    VkPhysicalDeviceSubgroupProperties physicalDeviceSubgroupProperties{};
    physicalDeviceSubgroupProperties.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SUBGROUP_PROPERTIES;
    physicalDeviceSubgroupProperties.pNext = nullptr;
    physicalDeviceSubgroupProperties.subgroupSize;//Ϊÿ��subgroup��Ĭ�ϵ��ô�����������ϸ��Ϣ��p3930
	physicalDeviceSubgroupProperties.supportedStages;//Ϊ VkShaderStageFlagBits ���ֵ������֧��subgroup scope��group operations��shader stages��������ϸ��Ϣ��p3930
	physicalDeviceSubgroupProperties.supportedOperations;//Ϊ VkSubgroupFeatureFlagBits ���ֵ������device֧��subgroup scope��subgroup operations ���ϣ�������ϸ��Ϣ��p3930
    /*
    VkSubgroupFeatureFlagBits:
    VK_SUBGROUP_FEATURE_BASIC_BIT : ָ��device�����ܰ���GroupNonUniform��SPIR-V shader modules��
    VK_SUBGROUP_FEATURE_VOTE_BIT : ָ��device�����ܰ���GroupNonUniformVote��SPIR-V shader modules��
    VK_SUBGROUP_FEATURE_ARITHMETIC_BIT : ָ��device�����ܰ���GroupNonUniformArithmetic��SPIR-V shader modules��
    VK_SUBGROUP_FEATURE_BALLOT_BIT specifies : ָ��device�����ܰ���GroupNonUniformBallot��SPIR-V shader modules��
    VK_SUBGROUP_FEATURE_SHUFFLE_BIT : ָ��device�����ܰ���GroupNonUniformShuffle��SPIR-V shader modules��
    VK_SUBGROUP_FEATURE_SHUFFLE_RELATIVE_BIT : ָ��device�����ܰ���GroupNonUniformShuffleRelative��SPIR-V shader modules��
    VK_SUBGROUP_FEATURE_CLUSTERED_BIT : ָ��device�����ܰ���GroupNonUniformClustered��SPIR-V shader modules��
    VK_SUBGROUP_FEATURE_QUAD_BIT : ָ��device�����ܰ���GroupNonUniformQuad��SPIR-V shader modules��
    VK_SUBGROUP_FEATURE_PARTITIONED_BIT_NV : ָ��device�����ܰ���GroupNonUniformPartitionedNV��SPIR-V shader modules��
    VK_SUBGROUP_FEATURE_ROTATE_BIT_KHR : ָ��device�����ܰ���GroupNonUniformRotateKHR��SPIR-V shader modules��
    VK_SUBGROUP_FEATURE_ROTATE_CLUSTERED_BIT_KHR : ָ��device������ʹ��OpGroupNonUniformRotateKHR��ClusterSize��������SPIR-V shader modules��    
    
    */
    physicalDeviceSubgroupProperties.quadOperationsInAllStages;//ָ���Ƿ�����stages֧�� quad group operations������ֻ�����Ƶ�fragment �Լ� compute stages.



    //VkPhysicalDeviceSubgroupSizeControlProperties  ���ȼ���VkPhysicalDeviceSubgroupSizeControlPropertiesEXT �����԰�����VkPhysicalDeviceProperties2.pNext��
    VkPhysicalDeviceSubgroupSizeControlProperties physicalDeviceSubgroupSizeControlProperties{};
    physicalDeviceSubgroupSizeControlProperties.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SUBGROUP_PROPERTIES;
    physicalDeviceSubgroupSizeControlProperties.pNext = nullptr;
    physicalDeviceSubgroupSizeControlProperties.minSubgroupSize;//Ϊdevice֧�ֵ���С��subgroup ��С��Ϊ2��ָ����������ϸ��Ϣ��p3932
    physicalDeviceSubgroupSizeControlProperties.maxSubgroupSize;//Ϊdevice֧�ֵ�����subgroup ��С��Ϊ2��ָ����������ϸ��Ϣ��p3932
    physicalDeviceSubgroupSizeControlProperties.maxComputeWorkgroupSubgroups;//Ϊworkgroup��֧�ֵ�subgroup ���������
    physicalDeviceSubgroupSizeControlProperties.requiredSubgroupSizeStages;//VkShaderStageFlagsֵ��Ϊ��Ҫָ��subgroup��С��һ��shader stage���


    //VkPhysicalDeviceBlendOperationAdvancedPropertiesEXT �����԰�����VkPhysicalDeviceProperties2.pNext��
    VkPhysicalDeviceBlendOperationAdvancedPropertiesEXT physicalDeviceBlendOperationAdvancedPropertiesEXT{};
    physicalDeviceBlendOperationAdvancedPropertiesEXT.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_BLEND_OPERATION_ADVANCED_PROPERTIES_EXT;
    physicalDeviceBlendOperationAdvancedPropertiesEXT.pNext = nullptr;
    physicalDeviceBlendOperationAdvancedPropertiesEXT.advancedBlendMaxColorAttachments;//����ʹ�� advanced blend operation��pipeline����ֵΪsubpass�п���ʹ�õ�color attachment���������ֵ��1
    physicalDeviceBlendOperationAdvancedPropertiesEXT.advancedBlendIndependentBlend;//ָ��ÿ��atttachment��advanced blend operations�Ƿ���Բ�ͬ
    physicalDeviceBlendOperationAdvancedPropertiesEXT.advancedBlendNonPremultipliedSrcColor;//ָ���Ƿ�source color ����������non-premultiplied�ģ����ΪVK_FALSE���� VkPipelineColorBlendAdvancedStateCreateInfoEXT::srcPremultiplied ����ΪVK_TRUE
    physicalDeviceBlendOperationAdvancedPropertiesEXT.advancedBlendNonPremultipliedDstColor;//ָ���Ƿ�destination color ����������non-premultiplied�ģ����ΪVK_FALSE���� VkPipelineColorBlendAdvancedStateCreateInfoEXT::dstPremultiplied ����ΪVK_TRUE
    physicalDeviceBlendOperationAdvancedPropertiesEXT.advancedBlendCorrelatedOverlap;//ָ���Ƿ�overlap mode ������������صģ����ΪVK_FALSE���� VkPipelineColorBlendAdvancedStateCreateInfoEXT::blendOverlap ����ΪVK_BLEND_OVERLAP_UNCORRELATED_EXT
    physicalDeviceBlendOperationAdvancedPropertiesEXT.advancedBlendAllOperations;//ָ���Ƿ�֧�����е�advanced blend operationö��ֵ


    //VkPhysicalDeviceVertexAttributeDivisorPropertiesEXT �����԰�����VkPhysicalDeviceProperties2.pNext��
    VkPhysicalDeviceVertexAttributeDivisorPropertiesEXT physicalDeviceVertexAttributeDivisorPropertiesEXT{};
    physicalDeviceVertexAttributeDivisorPropertiesEXT.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VERTEX_ATTRIBUTE_DIVISOR_PROPERTIES_EXT;
    physicalDeviceVertexAttributeDivisorPropertiesEXT.pNext = nullptr;
    physicalDeviceVertexAttributeDivisorPropertiesEXT.maxVertexAttribDivisor;//Ϊ�� instanced rendering ����ʱ���ܹ��ظ�vertex attribute data��instances���������


    //VkPhysicalDeviceVertexAttributeDivisorPropertiesKHR �����԰�����VkPhysicalDeviceProperties2.pNext��
    VkPhysicalDeviceVertexAttributeDivisorPropertiesKHR physicalDeviceVertexAttributeDivisorPropertiesKHR{};
    physicalDeviceVertexAttributeDivisorPropertiesKHR.sType = VK_STRUCTURE_TYPE_MAX_ENUM;//û�ж������ﶨ��Ϊ�Ƿ�ֵ
    physicalDeviceVertexAttributeDivisorPropertiesKHR.pNext = nullptr;
    physicalDeviceVertexAttributeDivisorPropertiesKHR.maxVertexAttribDivisor;//Ϊ�� instanced rendering ����ʱ���ܹ��ظ�vertex attribute data��instances���������
    physicalDeviceVertexAttributeDivisorPropertiesKHR.supportsNonZeroFirstInstance;//ָ���Ƿ�֧�ֵ�VkVertexInputBindingDivisorDescriptionKHR::divisor ��Ϊ1 ʱdrawing commands��firstInstance �����Ƿ����Ϊ ��0ֵ


    //VkPhysicalDeviceSamplerFilterMinmaxProperties ���ȼ���VkPhysicalDeviceSamplerFilterMinmaxPropertiesEXT �����԰�����VkPhysicalDeviceProperties2.pNext��
    VkPhysicalDeviceSamplerFilterMinmaxProperties physicalDeviceSamplerFilterMinmaxProperties{};
    physicalDeviceSamplerFilterMinmaxProperties.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SAMPLER_FILTER_MINMAX_PROPERTIES;
    physicalDeviceSamplerFilterMinmaxProperties.pNext = nullptr;
    physicalDeviceSamplerFilterMinmaxProperties.filterMinmaxSingleComponentFormats;//ָ���Ƿ���С��format����֧��min/max filtering����ϸ��Ϣ��p3936
    physicalDeviceSamplerFilterMinmaxProperties.filterMinmaxImageComponentMapping;//ָ���Ƿ�֧�ֵ�����min/max filtering ��ʱ����Զ�image��non-identity component mapping


    //VkPhysicalDeviceProtectedMemoryProperties ���ȼ���VkPhysicalDeviceSamplerFilterMinmaxPropertiesEXT �����԰�����VkPhysicalDeviceProperties2.pNext��
    VkPhysicalDeviceProtectedMemoryProperties physicalDeviceProtectedMemoryProperties{};
    physicalDeviceProtectedMemoryProperties.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PROTECTED_MEMORY_FEATURES;
    physicalDeviceProtectedMemoryProperties.pNext = nullptr;
    physicalDeviceProtectedMemoryProperties.protectedNoFault;//ָ����Ӧ�ó��������ܱ����Ķ��в�����д��δ�ܱ������ڴ棬�� protected memory ��ȡunprotected queue ���������� protected queue ������ִ�в�ѯ�����������VK_TRUE�������д�뽫��������д�롢��ȡ�Ͳ�ѯ��δ����ֵ������ undefined ֵ�����������VK_FALSE����Ӧ�ó��򲻵�ִ����Щ����


    //VkPhysicalDeviceMaintenance3Properties ���ȼ���VkPhysicalDeviceMaintenance3PropertiesKHR �����԰�����VkPhysicalDeviceProperties2.pNext��
    VkPhysicalDeviceMaintenance3Properties physicalDeviceMaintenance3Properties{};
    physicalDeviceMaintenance3Properties.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MAINTENANCE_3_PROPERTIES;
    physicalDeviceMaintenance3Properties.pNext = nullptr;
    physicalDeviceMaintenance3Properties.maxPerSetDescriptors;//Ϊһ��descriptor set����������descriptors���ܺ͵��������
    physicalDeviceMaintenance3Properties.maxMemoryAllocationSize;//Ϊ���Դ�����memory allocation������С


    //VkPhysicalDeviceMaintenance4Properties ���ȼ���VkPhysicalDeviceMaintenance4PropertiesKHR �����԰�����VkPhysicalDeviceProperties2.pNext��
    VkPhysicalDeviceMaintenance4Properties physicalDeviceMaintenance4Properties{};
    physicalDeviceMaintenance4Properties.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MAINTENANCE_4_PROPERTIES;
    physicalDeviceMaintenance4Properties.pNext = nullptr;
    physicalDeviceMaintenance4Properties.maxBufferSize;//Ϊ���Դ�����VkBuffer������С


    //VkPhysicalDeviceMaintenance5PropertiesKHR  �����԰�����VkPhysicalDeviceProperties2.pNext��
    VkPhysicalDeviceMaintenance5PropertiesKHR physicalDeviceMaintenance5PropertiesKHR{};
    physicalDeviceMaintenance5PropertiesKHR.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MAINTENANCE_5_PROPERTIES_KHR;
    physicalDeviceMaintenance5PropertiesKHR.pNext = nullptr;
    physicalDeviceMaintenance5PropertiesKHR.earlyFragmentMultisampleCoverageAfterSampleCounting;//ָ��fragment shading �Լ� multisample coverage operations �Ƿ�����EarlyFragmentTests execution mode��fragment shaders�� sample counting ֮��ִ��
    physicalDeviceMaintenance5PropertiesKHR.earlyFragmentSampleMaskTestBeforeSampleCounting;//ָ��sample mask test operation �Ƿ�����EarlyFragmentTests execution mode��fragment shaders�� sample counting ֮ǰִ��
    physicalDeviceMaintenance5PropertiesKHR.depthStencilSwizzleOneSupport;//ָ����VK_COMPONENT_SWIZZLE_ONE ��depth/stencil texturing operations�Ƿ��ж�����Ϊ
    physicalDeviceMaintenance5PropertiesKHR.polygonModePointSize;//ָ����VK_POLYGON_MODE_POINT��poligons�Ĺ�դ����point size�Ƿ��� PointSize ����
    physicalDeviceMaintenance5PropertiesKHR.nonStrictSinglePixelWideLinesUseParallelogram;//ָ���߿�Ϊ1.0�� non-strict line �Ƿ�ʹ��Bresenham �㷨��ƽ���ı��εķ�ʽ���й�դ��
    physicalDeviceMaintenance5PropertiesKHR.nonStrictWideLinesUseParallelogram;//ָ���߿����1.0�� non-strict line �Ƿ�ʹ��Bresenham �㷨��ƽ���ı��εķ�ʽ���й�դ��


    //VkPhysicalDeviceMaintenance6PropertiesKHR  �����԰�����VkPhysicalDeviceProperties2.pNext��
    VkPhysicalDeviceMaintenance6PropertiesKHR physicalDeviceMaintenance6PropertiesKHR{};
    physicalDeviceMaintenance6PropertiesKHR.sType = VK_STRUCTURE_TYPE_MAX_ENUM;//û�ж������ﶨ��Ϊ�Ƿ�ֵ
    physicalDeviceMaintenance6PropertiesKHR.pNext = nullptr;
    physicalDeviceMaintenance6PropertiesKHR.blockTexelViewCompatibleMultipleLayers;//ָ���Ƿ�֧�ִ���һ���� VK_IMAGE_CREATE_BLOCK_TEXEL_VIEW_COMPATIBLE_BIT ��subresourceRange��layerCount����1��image view
    physicalDeviceMaintenance6PropertiesKHR.maxCombinedImageSamplerDescriptorCount;//ָ��֧�ֿ������������κ���Ҫһ��Y��CBCR conversion �ĸ�ʽ��combined image sampler���������
    physicalDeviceMaintenance6PropertiesKHR.fragmentShadingRateClampCombinerInputs;//ָ���Ƿ���������Ϊ combiner operations ��p2696


    //VkPhysicalDeviceMeshShaderPropertiesNV  �����԰�����VkPhysicalDeviceProperties2.pNext��
    VkPhysicalDeviceMeshShaderPropertiesNV physicalDeviceMeshShaderPropertiesNV{};
    physicalDeviceMeshShaderPropertiesNV.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MESH_SHADER_PROPERTIES_NV;
    physicalDeviceMeshShaderPropertiesNV.pNext = nullptr;
    physicalDeviceMeshShaderPropertiesNV.maxDrawMeshTasksCount;//Ϊ���Ա�һ��draw mesh tasks command ������local workgroups ���������
    physicalDeviceMeshShaderPropertiesNV.maxTaskWorkGroupInvocations;//Ϊһ��local workgroup ���Դ�����task shader���õ����������������ϸ��Ϣ��p3941
    physicalDeviceMeshShaderPropertiesNV.maxTaskWorkGroupSize[3];//Ϊ local task workgroup��ά�ȵ�����С���ֱ����X��Y��Zά�ȣ�������ϸ��Ϣ��p3941
    physicalDeviceMeshShaderPropertiesNV.maxTaskTotalMemorySize;//Ϊtask shader ������shared �Լ�output memory�󶨵�����ֽڴ�С
    physicalDeviceMeshShaderPropertiesNV.maxTaskOutputCount;//Ϊһ��task shader workgroup ���Է����output tasks���������
    physicalDeviceMeshShaderPropertiesNV.maxMeshWorkGroupInvocations;//Ϊһ��local workgroup ���Դ�����mesh shader���õ����������������ϸ��Ϣ��p3941
    physicalDeviceMeshShaderPropertiesNV.maxMeshWorkGroupSize[3];//Ϊ local mesh workgroup��ά�ȵ�����С���ֱ����X��Y��Zά�ȣ�������ϸ��Ϣ��p3941
    physicalDeviceMeshShaderPropertiesNV.maxMeshTotalMemorySize;//Ϊmesh shader ������shared �Լ�output memory�󶨵�����ֽڴ�С
    physicalDeviceMeshShaderPropertiesNV.maxMeshOutputVertices;//Ϊmesh shader ������Դ洢�Ķ�����������
    physicalDeviceMeshShaderPropertiesNV.maxMeshOutputPrimitives;//Ϊmesh shader ������Դ洢��ͼԪ���������
    physicalDeviceMeshShaderPropertiesNV.maxMeshMultiviewViewCount;//Ϊmesh shader ����ʹ�õ�multiview views���������
    physicalDeviceMeshShaderPropertiesNV.meshOutputPerVertexGranularity;//Ϊmesh vertex outputs��������ȣ�������mesh shader����ʹ�õ��ڴ�ռ䣬С��maxMeshTotalMemorySize
    physicalDeviceMeshShaderPropertiesNV.meshOutputPerPrimitiveGranularity;//Ϊper-primitive mesh outputs��������ȣ�������mesh shader����ʹ�õ��ڴ�ռ䣬С��maxMeshTotalMemorySize


    //VkPhysicalDeviceMeshShaderPropertiesNV  �����԰�����VkPhysicalDeviceProperties2.pNext��
    VkPhysicalDeviceMeshShaderPropertiesEXT physicalDeviceMeshShaderPropertiesEXT{};
    physicalDeviceMeshShaderPropertiesEXT.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MESH_SHADER_PROPERTIES_EXT;
    physicalDeviceMeshShaderPropertiesEXT.pNext = nullptr;
    physicalDeviceMeshShaderPropertiesEXT.maxTaskWorkGroupTotalCount;//Ϊ���Ա�һ��mesh draw tasks command ������local workgroups �������������
    physicalDeviceMeshShaderPropertiesEXT.maxTaskWorkGroupCount[3];//Ϊ���Ա�һ��mesh draw tasks command ������local workgroups ������������ֱ����ά��X��Y��Z��������ϸ��Ϣ��p3943
    physicalDeviceMeshShaderPropertiesEXT.maxTaskWorkGroupInvocations;//Ϊһ��local workgroup ���Դ�����task shader���õ����������������ϸ��Ϣ��p3943
    physicalDeviceMeshShaderPropertiesEXT.maxTaskWorkGroupSize[3];//Ϊ local task workgroup��ά�ȵ�����С���ֱ����X��Y��Zά�ȣ�������ϸ��Ϣ��p3943
    physicalDeviceMeshShaderPropertiesEXT.maxTaskPayloadSize;//Ϊtask shader stage��shader module���� TaskPayloadWorkgroupEXT storage class�����ı������õ��ܵ����洢�ֽڿռ�
    physicalDeviceMeshShaderPropertiesEXT.maxTaskSharedMemorySize;//Ϊtask shader stage��shader module���� Workgroup storage class�����ı������õ��ܵ����洢�ֽڿռ�
    physicalDeviceMeshShaderPropertiesEXT.maxTaskPayloadAndSharedMemorySize;//Ϊtask shader stage��shader module����TaskPayloadWorkgroupEXT ���� Workgroup storage class�����ı������õ��ܵ����洢�ֽڿռ�
    physicalDeviceMeshShaderPropertiesEXT.maxMeshWorkGroupTotalCount;//Ϊһ��task shader workgroup ���Է���� local output tasks���������
    physicalDeviceMeshShaderPropertiesEXT.maxMeshWorkGroupCount[3];//Ϊһ��task shader workgroup ���Է���� local output tasksÿ��ά�ȵ����������������ϸ��Ϣ��p3944
    physicalDeviceMeshShaderPropertiesEXT.maxMeshWorkGroupInvocations;//Ϊһ��local workgroup ���Դ�����mesh shader���õ����������������ϸ��Ϣ��p3944
    physicalDeviceMeshShaderPropertiesEXT.maxMeshWorkGroupSize[3];//Ϊ local mesh workgroup��ά�ȵ�����С���ֱ����X��Y��Zά�ȣ�������ϸ��Ϣ��p3944
    physicalDeviceMeshShaderPropertiesEXT.maxMeshSharedMemorySize;//Ϊmesh shader stage��shader module���� Workgroup storage class�����ı������õ��ܵ����洢�ֽڿռ�
    physicalDeviceMeshShaderPropertiesEXT.maxMeshPayloadAndSharedMemorySize;//Ϊmesh shader stage��shader module����TaskPayloadWorkgroupEXT ���� Workgroup storage class�����ı������õ��ܵ����洢�ֽڿռ�
    physicalDeviceMeshShaderPropertiesEXT.maxMeshOutputMemorySize;//Ϊmesh shader stage��shader module������������õ��ܵ����洢�ֽڿռ�
    physicalDeviceMeshShaderPropertiesEXT.maxMeshPayloadAndOutputMemorySize;//Ϊmesh shader stage��shader module���� TaskPayloadWorkgroupEXT storage class�����ı�����������������õ��ܵ����洢�ֽڿռ�
    physicalDeviceMeshShaderPropertiesEXT.maxMeshOutputComponents;//Ϊmesh shader stage �������������������
    physicalDeviceMeshShaderPropertiesEXT.maxMeshOutputVertices;//Ϊһ��mesh shader workgroup ���Է���Ķ�����������
    physicalDeviceMeshShaderPropertiesEXT.maxMeshOutputPrimitives;//Ϊһ��mesh shader workgroup ���Է����ͼԪ���������
    physicalDeviceMeshShaderPropertiesEXT.maxMeshOutputLayers;//Ϊһ��mesh shader workgroup ���������layer���������ֵ��1
    physicalDeviceMeshShaderPropertiesEXT.maxMeshMultiviewViewCount;//Ϊmesh shader ����ʹ�õ� view�����������ֵ��1
    physicalDeviceMeshShaderPropertiesEXT.meshOutputPerVertexGranularity;//Ϊ�����������ȣ�С�ڵ���maxMeshOutputMemorySize������������Ϣ��p3945
    physicalDeviceMeshShaderPropertiesEXT.meshOutputPerPrimitiveGranularity;//ΪͼԪ���������С�ڵ���maxMeshOutputMemorySize������������Ϣ��p3945
    physicalDeviceMeshShaderPropertiesEXT.maxPreferredTaskWorkGroupInvocations;//Ϊ�����������ѡ��һ��workgroup�к��еĵ�task shader invocations����
    physicalDeviceMeshShaderPropertiesEXT.maxPreferredMeshWorkGroupInvocations;//Ϊ�����������ѡ��һ��workgroup�к��еĵ�mesh shader invocations����
    physicalDeviceMeshShaderPropertiesEXT.prefersLocalInvocationVertexOutput;//ָ����array ����ƥ��LocalInvocationIndexʱ��mesh shader����vertex output arrayд�������Ƿ����������
    physicalDeviceMeshShaderPropertiesEXT.prefersLocalInvocationPrimitiveOutput;//ָ����array ����ƥ��LocalInvocationIndexʱ��mesh shader����primitive output arrayд�������Ƿ����������
    physicalDeviceMeshShaderPropertiesEXT.prefersCompactVertexOutput;//ָ���Ƿ�Ӧ����mesh shader���Զ���culling����ն��������Ϊ�˸��õ����ܱ��֣����򱣳ֶ���ԭ����λ�ÿ��ܸ���
    physicalDeviceMeshShaderPropertiesEXT.prefersCompactPrimitiveOutput;//ָ���Ƿ�Ӧ����mesh shader���Զ���culling�����ͼԪ�����Ϊ�˸��õ����ܱ��֣�����ʹ��CullPrimitiveEXT���ܸ���


    //VkPhysicalDeviceDescriptorIndexingProperties ���ȼ���VkPhysicalDeviceDescriptorIndexingPropertiesEXT �����԰�����VkPhysicalDeviceProperties2.pNext��
    VkPhysicalDeviceDescriptorIndexingProperties physicalDeviceDescriptorIndexingProperties{};
    physicalDeviceDescriptorIndexingProperties.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DESCRIPTOR_INDEXING_PROPERTIES;
    physicalDeviceDescriptorIndexingProperties.pNext = nullptr;
    physicalDeviceDescriptorIndexingProperties.maxUpdateAfterBindDescriptorsInAllPools;//ָ�����к�VK_DESCRIPTOR_POOL_CREATE_UPDATE_AFTER_BIND_BIT������descriptor pool�����ܰ������������͵�descriptors�������������
    physicalDeviceDescriptorIndexingProperties.shaderUniformBufferArrayNonUniformIndexingNative;//ָ���Ƿ�uniform buffer descriptors ֧��nonuniform indexing��������ϸ��Ϣ��p3947
    physicalDeviceDescriptorIndexingProperties.shaderSampledImageArrayNonUniformIndexingNative;//ָ���Ƿ�sampler �Լ� image descriptors ֧��nonuniform indexing��������ϸ��Ϣ��p3947
    physicalDeviceDescriptorIndexingProperties.shaderStorageBufferArrayNonUniformIndexingNative;//ָ���Ƿ�storage buffer descriptors ֧��nonuniform indexing��������ϸ��Ϣ��p3947
    physicalDeviceDescriptorIndexingProperties.shaderStorageImageArrayNonUniformIndexingNative;//ָ���Ƿ�storage image descriptors ֧��nonuniform indexing��������ϸ��Ϣ��p3947
    physicalDeviceDescriptorIndexingProperties.shaderInputAttachmentArrayNonUniformIndexingNative;//ָ���Ƿ�input attachment descriptors ֧��nonuniform indexing��������ϸ��Ϣ��p3947
    physicalDeviceDescriptorIndexingProperties.robustBufferAccessUpdateAfterBind;//ָ���Ƿ� robustBufferAccess���Ժ� descriptorBindingUniformBufferUpdateAfterBind, descriptorBindingStorageBufferUpdateAfterBind, descriptorBindingUniformTexelBufferUpdateAfterBind, �Լ� / ���� descriptorBindingStorageTexelBufferUpdateAfterBind ͬʱ����
    physicalDeviceDescriptorIndexingProperties.quadDivergentImplicitLod;//������ָ���image �Լ�/���� sampler������quad�ڲ�һ��ʱ������ͼ���������ʽLOD�����Ƿ�����ȷ����Ľ��
    physicalDeviceDescriptorIndexingProperties.maxPerStageDescriptorUpdateAfterBindSamplers;//������maxPerStageDescriptorSamplers��ֻ����descriptors��ͳ�ƴ��Դ������л��߲�����VK_DESCRIPTOR_SET_LAYOUT_CREATE_UPDATE_AFTER_BIND_POOL_BIT ��descriptor sets��ͳ��
    physicalDeviceDescriptorIndexingProperties.maxPerStageDescriptorUpdateAfterBindUniformBuffers;//������maxPerStageDescriptorUniformBuffers��ֻ����descriptors��ͳ�ƴ��Դ������л��߲�����VK_DESCRIPTOR_SET_LAYOUT_CREATE_UPDATE_AFTER_BIND_POOL_BIT ��descriptor sets��ͳ��
    physicalDeviceDescriptorIndexingProperties.maxPerStageDescriptorUpdateAfterBindStorageBuffers;//������maxPerStageDescriptorStorageBuffers��ֻ����descriptors��ͳ�ƴ��Դ������л��߲�����VK_DESCRIPTOR_SET_LAYOUT_CREATE_UPDATE_AFTER_BIND_POOL_BIT ��descriptor sets��ͳ��
    physicalDeviceDescriptorIndexingProperties.maxPerStageDescriptorUpdateAfterBindSampledImages;//������maxPerStageDescriptorSampledImages��ֻ����descriptors��ͳ�ƴ��Դ������л��߲�����VK_DESCRIPTOR_SET_LAYOUT_CREATE_UPDATE_AFTER_BIND_POOL_BIT ��descriptor sets��ͳ��
    physicalDeviceDescriptorIndexingProperties.maxPerStageDescriptorUpdateAfterBindStorageImages;//������maxPerStageDescriptorStorageImages��ֻ����descriptors��ͳ�ƴ��Դ������л��߲�����VK_DESCRIPTOR_SET_LAYOUT_CREATE_UPDATE_AFTER_BIND_POOL_BIT ��descriptor sets��ͳ��
    physicalDeviceDescriptorIndexingProperties.maxPerStageDescriptorUpdateAfterBindInputAttachments;//������maxPerStageDescriptorInputAttachments��ֻ����descriptors��ͳ�ƴ��Դ������л��߲�����VK_DESCRIPTOR_SET_LAYOUT_CREATE_UPDATE_AFTER_BIND_POOL_BIT ��descriptor sets��ͳ��
    physicalDeviceDescriptorIndexingProperties.maxPerStageUpdateAfterBindResources;//������maxPerStageResources��ֻ����descriptors��ͳ�ƴ��Դ������л��߲�����VK_DESCRIPTOR_SET_LAYOUT_CREATE_UPDATE_AFTER_BIND_POOL_BIT ��descriptor sets��ͳ��
    physicalDeviceDescriptorIndexingProperties.maxDescriptorSetUpdateAfterBindSamplers;//������maxDescriptorSetSamplers��ֻ����descriptors��ͳ�ƴ��Դ������л��߲�����VK_DESCRIPTOR_SET_LAYOUT_CREATE_UPDATE_AFTER_BIND_POOL_BIT ��descriptor sets��ͳ��
    physicalDeviceDescriptorIndexingProperties.maxDescriptorSetUpdateAfterBindUniformBuffers;//������maxDescriptorSetUniformBuffers��ֻ����descriptors��ͳ�ƴ��Դ������л��߲�����VK_DESCRIPTOR_SET_LAYOUT_CREATE_UPDATE_AFTER_BIND_POOL_BIT ��descriptor sets��ͳ��
    physicalDeviceDescriptorIndexingProperties.maxDescriptorSetUpdateAfterBindUniformBuffersDynamic;//������maxDescriptorSetUniformBuffersDynamic��ֻ����descriptors��ͳ�ƴ��Դ������л��߲�����VK_DESCRIPTOR_SET_LAYOUT_CREATE_UPDATE_AFTER_BIND_POOL_BIT ��descriptor sets��ͳ��,������Ϣ��p3948
    physicalDeviceDescriptorIndexingProperties.maxDescriptorSetUpdateAfterBindStorageBuffers;//������maxDescriptorSetStorageBuffers��ֻ����descriptors��ͳ�ƴ��Դ������л��߲�����VK_DESCRIPTOR_SET_LAYOUT_CREATE_UPDATE_AFTER_BIND_POOL_BIT ��descriptor sets��ͳ��
    physicalDeviceDescriptorIndexingProperties.maxDescriptorSetUpdateAfterBindStorageBuffersDynamic;//������maxDescriptorSetStorageBuffersDynamic��ֻ����descriptors��ͳ�ƴ��Դ������л��߲�����VK_DESCRIPTOR_SET_LAYOUT_CREATE_UPDATE_AFTER_BIND_POOL_BIT ��descriptor sets��ͳ��,������Ϣ��p3948
    physicalDeviceDescriptorIndexingProperties.maxDescriptorSetUpdateAfterBindSampledImages;//������maxDescriptorSetSampledImages��ֻ����descriptors��ͳ�ƴ��Դ������л��߲�����VK_DESCRIPTOR_SET_LAYOUT_CREATE_UPDATE_AFTER_BIND_POOL_BIT ��descriptor sets��ͳ��
    physicalDeviceDescriptorIndexingProperties.maxDescriptorSetUpdateAfterBindStorageImages;//������maxDescriptorSetStorageImages��ֻ����descriptors��ͳ�ƴ��Դ������л��߲�����VK_DESCRIPTOR_SET_LAYOUT_CREATE_UPDATE_AFTER_BIND_POOL_BIT ��descriptor sets��ͳ��
    physicalDeviceDescriptorIndexingProperties.maxDescriptorSetUpdateAfterBindInputAttachments;//������maxDescriptorSetInputAttachments��ֻ����descriptors��ͳ�ƴ��Դ������л��߲�����VK_DESCRIPTOR_SET_LAYOUT_CREATE_UPDATE_AFTER_BIND_POOL_BIT ��descriptor sets��ͳ��


    //VkPhysicalDeviceInlineUniformBlockProperties ���ȼ���VkPhysicalDeviceInlineUniformBlockPropertiesEXT �����԰�����VkPhysicalDeviceProperties2.pNext��
    VkPhysicalDeviceInlineUniformBlockProperties physicalDeviceInlineUniformBlockProperties{};
    physicalDeviceInlineUniformBlockProperties.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_INLINE_UNIFORM_BLOCK_PROPERTIES;
    physicalDeviceInlineUniformBlockProperties.pNext = nullptr;
    physicalDeviceInlineUniformBlockProperties.maxInlineUniformBlockSize;//һ�� inline uniform block �󶨵�����ֽ���
    physicalDeviceInlineUniformBlockProperties.maxPerStageDescriptorInlineUniformBlocks;//Ϊһ��pipeline layout��һ��shader stage���Է��ʵ� inline uniform block �󶨵�����ֽ���������������p3949
    physicalDeviceInlineUniformBlockProperties.maxPerStageDescriptorUpdateAfterBindInlineUniformBlocks;//������maxPerStageDescriptorInlineUniformBlocks��ֻ����descriptors��ͳ�ƴ��Դ������л��߲�����VK_DESCRIPTOR_SET_LAYOUT_CREATE_UPDATE_AFTER_BIND_POOL_BIT ��descriptor sets��ͳ��
    physicalDeviceInlineUniformBlockProperties.maxDescriptorSetInlineUniformBlocks;//�ڿ����йܵ���ɫ���׶κ�����������ŵĹܵ������У����԰��������������е�inline uniform block bindings���������������������p3949
    physicalDeviceInlineUniformBlockProperties.maxDescriptorSetUpdateAfterBindInlineUniformBlocks;//������maxDescriptorSetInlineUniformBlocks��ֻ����descriptors��ͳ�ƴ��Դ������л��߲�����VK_DESCRIPTOR_SET_LAYOUT_CREATE_UPDATE_AFTER_BIND_POOL_BIT ��descriptor sets��ͳ��


    //VkPhysicalDeviceConservativeRasterizationPropertiesEXT  �����԰�����VkPhysicalDeviceProperties2.pNext��
    VkPhysicalDeviceConservativeRasterizationPropertiesEXT physicalDeviceConservativeRasterizationPropertiesEXT{};
    physicalDeviceConservativeRasterizationPropertiesEXT.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_CONSERVATIVE_RASTERIZATION_PROPERTIES_EXT;
    physicalDeviceConservativeRasterizationPropertiesEXT.pNext = nullptr;
    physicalDeviceConservativeRasterizationPropertiesEXT.primitiveOverestimationSize;//��conservative rasterization overestimation mode�����ɵ�ͼԪ�ı߽��pixels�Ĵ�С�Ƿ������ˣ�����������p3950
    physicalDeviceConservativeRasterizationPropertiesEXT.maxExtraPrimitiveOverestimationSize;//Ϊpipeline state��֧�ֵ�extra overestimation��pixels������С
    physicalDeviceConservativeRasterizationPropertiesEXT.extraPrimitiveOverestimationSizeGranularity;//Ϊpipeline state�п���ָ����0.0 �� maxExtraPrimitiveOverestimationSize��Χ��extra overestimation�����ȣ�����������p3950
    physicalDeviceConservativeRasterizationPropertiesEXT.primitiveUnderestimation;//ָ���Ƿ����֧��VK_CONSERVATIVE_RASTERIZATION_MODE_OVERESTIMATE_EXT �����֧��VK_CONSERVATIVE_RASTERIZATION_MODE_UNDERESTIMATE_EXT conservative rasterization mode
    physicalDeviceConservativeRasterizationPropertiesEXT.conservativePointAndLineRasterization;//ָ���Ƿ�֧�ֶ� point �� line primitives �Լ� triangle primitives�� conservative rasterization������ֻ֧�ֶ�������ͼԪ��
    physicalDeviceConservativeRasterizationPropertiesEXT.degenerateTrianglesRasterized;//ΪVK_FALSE���򽫰�������������ͼԪ�޳�����Ϊ����դ�������������ΪVK_TRUE�����޳���ЩͼԪ������ʹ����fragmentʹ��provoking�������Ժ����ֵ
    physicalDeviceConservativeRasterizationPropertiesEXT.degenerateLinesRasterized;//ΪVK_FALSE���򽫰��㳤����ͼԪ�޳�����Ϊ����դ�������������ΪVK_TRUE�����޳���ЩͼԪ������ʹ����fragmentʹ��provoking�������Ժ����ֵ
    physicalDeviceConservativeRasterizationPropertiesEXT.fullyCoveredFragmentShaderInputVariable;//���ΪVK_TRUE����֧��SPIR-V���ñ���fragment shader input variable FullyCoveredEXT��ָ���Ƿ���conservative rasterization��fragment �����Ƿ�ͼԪ��ȫ����
    physicalDeviceConservativeRasterizationPropertiesEXT.conservativeRasterizationPostDepthCoverage;//���ΪVK_TRUE����ָ��֧�ֿ���conservative rasterizationʱͬʱ����PostDepthCoverage execution mode


    //VkPhysicalDeviceFragmentDensityMapPropertiesEXT  �����԰�����VkPhysicalDeviceProperties2.pNext��
    VkPhysicalDeviceFragmentDensityMapPropertiesEXT physicalDeviceFragmentDensityMapPropertiesEXT{};
    physicalDeviceFragmentDensityMapPropertiesEXT.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FRAGMENT_DENSITY_MAP_PROPERTIES_EXT;
    physicalDeviceFragmentDensityMapPropertiesEXT.pNext = nullptr;
    physicalDeviceFragmentDensityMapPropertiesEXT.minFragmentDensityTexelSize;//ָ����С fragment density texel size
    physicalDeviceFragmentDensityMapPropertiesEXT.maxFragmentDensityTexelSize;//ָ����� fragment density texel size
    physicalDeviceFragmentDensityMapPropertiesEXT.fragmentDensityInvocations;//ָ����ÿ�����ǵĲ�������ܻ���ö����fragment shader


    //VkPhysicalDeviceFragmentDensityMap2PropertiesEXT  �����԰�����VkPhysicalDeviceProperties2.pNext��
    VkPhysicalDeviceFragmentDensityMap2PropertiesEXT physicalDeviceFragmentDensityMap2PropertiesEXT{};
    physicalDeviceFragmentDensityMap2PropertiesEXT.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FRAGMENT_DENSITY_MAP_2_PROPERTIES_EXT;
    physicalDeviceFragmentDensityMap2PropertiesEXT.pNext = nullptr;
    physicalDeviceFragmentDensityMap2PropertiesEXT.subsampledLoads;//ָ����subsampled attachments�Լ��ز�������image���ݶ�ȡ���Ƿ�����²�����render pass��fragment density
    physicalDeviceFragmentDensityMap2PropertiesEXT.subsampledCoarseReconstructionEarlyAccess;//ָ����fragment shader�����ð���VK_SAMPLER_CREATE_SUBSAMPLED_COARSE_RECONSTRUCTION_BIT_EXT������samplers��image���ݽ��ж�ȡʱ����VK_PIPELINE_STAGE_VERTEX_SHADER_BIT�׶δ�������Ķ�ȡ
    physicalDeviceFragmentDensityMap2PropertiesEXT.maxSubsampledArrayLayers;//Ϊ֧������subsampled samplers��VkImageView��array layer���������
    physicalDeviceFragmentDensityMap2PropertiesEXT.maxDescriptorSetSubsampledSamplers;//Ϊ���԰�����һ�� VkPipelineLayout�е�subsampled samplers���������


    //VkPhysicalDeviceFragmentDensityMapOffsetPropertiesQCOM  �����԰�����VkPhysicalDeviceProperties2.pNext��
    VkPhysicalDeviceFragmentDensityMapOffsetPropertiesQCOM physicalDeviceFragmentDensityMapOffsetPropertiesQCOM{};
    physicalDeviceFragmentDensityMapOffsetPropertiesQCOM.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FRAGMENT_DENSITY_MAP_OFFSET_PROPERTIES_QCOM;
    physicalDeviceFragmentDensityMapOffsetPropertiesQCOM.pNext = nullptr;
    physicalDeviceFragmentDensityMapOffsetPropertiesQCOM.fragmentDensityOffsetGranularity;//ָ�� fragment density offsets������


    //VkPhysicalDeviceShaderCorePropertiesAMD  �����԰�����VkPhysicalDeviceProperties2.pNext��
    VkPhysicalDeviceShaderCorePropertiesAMD physicalDeviceShaderCorePropertiesAMD{};
    physicalDeviceShaderCorePropertiesAMD.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_CORE_PROPERTIES_AMD;
    physicalDeviceShaderCorePropertiesAMD.pNext = nullptr;
    physicalDeviceShaderCorePropertiesAMD.shaderEngineCount;//Ϊ��physical device�е�shader core���ҵ���shader engine������
    physicalDeviceShaderCorePropertiesAMD.shaderArraysPerEngineCount;//ָ��shader engine�� shader arrays������������������p3954
    physicalDeviceShaderCorePropertiesAMD.computeUnitsPerShaderArray;//ָ��һ��shader array��compute units������������������p3954
    physicalDeviceShaderCorePropertiesAMD.simdPerComputeUnit;//ָ��һ��compute unit��SIMD��������һ��SIMD��һ��ʱ��ֻ�ܳ���һ��ָ��
    physicalDeviceShaderCorePropertiesAMD.wavefrontsPerSimd;//
    physicalDeviceShaderCorePropertiesAMD.wavefrontSize;//Ϊһ��subgroup������С
    physicalDeviceShaderCorePropertiesAMD.sgprsPerSimd;//ָ��ÿ��SIMD�б���ͨ�üĴ��� SGPR������
    physicalDeviceShaderCorePropertiesAMD.minSgprAllocation;//ָ�������wave�ı���ͨ�üĴ��� SGPR����С����
    physicalDeviceShaderCorePropertiesAMD.maxSgprAllocation;//ָ�������wave�ı���ͨ�üĴ��� SGPR���������
    physicalDeviceShaderCorePropertiesAMD.sgprAllocationGranularity;//ָ�������wave�ı���ͨ�üĴ��� SGPR�ķ�������
    physicalDeviceShaderCorePropertiesAMD.vgprsPerSimd;//ָ��ÿ��SIMD������ͨ�üĴ��� VGPR������
    physicalDeviceShaderCorePropertiesAMD.minVgprAllocation;//ָ�������wave������ͨ�üĴ��� VGPR����С����
    physicalDeviceShaderCorePropertiesAMD.maxVgprAllocation;//ָ�������wave������ͨ�üĴ��� VGPR���������
    physicalDeviceShaderCorePropertiesAMD.vgprAllocationGranularity;//ָ�������wave������ͨ�üĴ��� VGPR�ķ�������


    //VkPhysicalDeviceShaderCoreProperties2AMD  �����԰�����VkPhysicalDeviceProperties2.pNext��
    VkPhysicalDeviceShaderCoreProperties2AMD physicalDeviceShaderCoreProperties2AMD{};
    physicalDeviceShaderCoreProperties2AMD.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_CORE_PROPERTIES_2_AMD;
    physicalDeviceShaderCoreProperties2AMD.pNext = nullptr;
    physicalDeviceShaderCoreProperties2AMD.shaderCoreFeatures;//VkShaderCorePropertiesFlagBitsAMD ���ֵλ����ָ��shader core֧�ֵ�һ������
    physicalDeviceShaderCoreProperties2AMD.activeComputeUnitCount;//ָ���Ѿ����õ� compute units������


    //VkPhysicalDeviceDepthStencilResolveProperties  ���ȼ���VkPhysicalDeviceDepthStencilResolvePropertiesKHR �����԰�����VkPhysicalDeviceProperties2.pNext��
    VkPhysicalDeviceDepthStencilResolveProperties physicalDeviceDepthStencilResolveProperties{};
    physicalDeviceDepthStencilResolveProperties.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DEPTH_STENCIL_RESOLVE_PROPERTIES;
    physicalDeviceDepthStencilResolveProperties.pNext = nullptr;
    physicalDeviceDepthStencilResolveProperties.supportedDepthResolveModes;//VkResolveModeFlagBits ���ֵλ����ָ��֧�ֵ�depth resolve modes��������Ϣ��p3956
    physicalDeviceDepthStencilResolveProperties.supportedStencilResolveModes;//VkResolveModeFlagBits ���ֵλ����ָ��֧�ֵ�stencil resolve modes��������Ϣ��p3956
    physicalDeviceDepthStencilResolveProperties.independentResolveNone;//ָ���Ƿ�֧�� depth �Լ� stencil resolve modes Ϊ��ͬ��ֵ������һ��ΪVK_RESOLVE_MODE_NONE
    physicalDeviceDepthStencilResolveProperties.independentResolve;//ָ���Ƿ�֧�ֶ�֧�ֵ�depth �Լ� stencil resolve modes���������


    //VkPhysicalDevicePerformanceQueryPropertiesKHR  �����԰�����VkPhysicalDeviceProperties2.pNext��
    VkPhysicalDevicePerformanceQueryPropertiesKHR physicalDevicePerformanceQueryPropertiesKHR{};
    physicalDevicePerformanceQueryPropertiesKHR.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PERFORMANCE_QUERY_PROPERTIES_KHR;
    physicalDevicePerformanceQueryPropertiesKHR.pNext = nullptr;
    physicalDevicePerformanceQueryPropertiesKHR.allowCommandBufferQueryCopies;//ָ���Ƿ�performance query pools�������� vkCmdCopyQueryPoolResults


    //VkPhysicalDeviceShadingRateImagePropertiesNV  �����԰�����VkPhysicalDeviceProperties2.pNext��
    VkPhysicalDeviceShadingRateImagePropertiesNV physicalDeviceShadingRateImagePropertiesNV{};
    physicalDeviceShadingRateImagePropertiesNV.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADING_RATE_IMAGE_PROPERTIES_NV;
    physicalDeviceShadingRateImagePropertiesNV.pNext = nullptr;
    physicalDeviceShadingRateImagePropertiesNV.shadingRateTexelSize;//ָ��shading rate image��ÿ��texel��Ӧ��framebuffer�������width�Լ�height
    physicalDeviceShadingRateImagePropertiesNV.shadingRatePaletteSize;//ָ��shading rate image֧�ֵ�paletteʵ����������
    physicalDeviceShadingRateImagePropertiesNV.shadingRateMaxCoarseSamples;//ָ��һ��fragment���ܰ����Ĳ�������������������������p3958


    //VkPhysicalDeviceMemoryDecompressionPropertiesNV  �����԰�����VkPhysicalDeviceProperties2.pNext��
    VkPhysicalDeviceMemoryDecompressionPropertiesNV physicalDeviceMemoryDecompressionPropertiesNV{};
    physicalDeviceMemoryDecompressionPropertiesNV.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MEMORY_DECOMPRESSION_PROPERTIES_NV;
    physicalDeviceMemoryDecompressionPropertiesNV.pNext = nullptr;
    physicalDeviceMemoryDecompressionPropertiesNV.decompressionMethods;// VkMemoryDecompressionMethodFlagBitsNV ���ֵλ���룬ָ��֧�ֵ��ڴ��ѹ����
    physicalDeviceMemoryDecompressionPropertiesNV.maxDecompressionIndirectCount;//ָ��֧�ֵ� vkCmdDecompressMemoryIndirectCountNV ������countBuffer�а�����count ֵ�����ֵ


    //VkPhysicalDeviceMemoryDecompressionPropertiesNV  �����԰�����VkPhysicalDeviceProperties2.pNext��
    VkPhysicalDeviceTransformFeedbackPropertiesEXT physicalDeviceTransformFeedbackPropertiesEXT{};
    physicalDeviceTransformFeedbackPropertiesEXT.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_TRANSFORM_FEEDBACK_PROPERTIES_EXT;
    physicalDeviceTransformFeedbackPropertiesEXT.pNext = nullptr;
    physicalDeviceTransformFeedbackPropertiesEXT.maxTransformFeedbackStreams;//ָ�����Դ������� GeometryStreams������geometry shaders �����vertex streams ���������������������p3959
    physicalDeviceTransformFeedbackPropertiesEXT.maxTransformFeedbackBuffers;//ָ�������������� last pre-rasterization shader stage ����� ��transform feedback buffers ���������
    physicalDeviceTransformFeedbackPropertiesEXT.maxTransformFeedbackBufferSize;//ָ�� vkCmdBindTransformFeedbackBuffersEXT�п��԰󶨵�һ��transform feedback buffer������С
    physicalDeviceTransformFeedbackPropertiesEXT.maxTransformFeedbackStreamDataSize;//ָ�����Բ���Ĺ�����һ��vertex stream��һ����� transform feedback buffers�ж�����������������ֽڴ�С
    physicalDeviceTransformFeedbackPropertiesEXT.maxTransformFeedbackBufferDataSize;//ָ��ָ�� transform feedback buffers�п��Բ���Ķ������ݵ�����ֽ���
    physicalDeviceTransformFeedbackPropertiesEXT.maxTransformFeedbackBufferDataStride;//Ϊbuffer��ÿ������Ķ�������֮���ֱ�Ӳ���
    physicalDeviceTransformFeedbackPropertiesEXT.transformFeedbackQueries;//ָ���Ƿ�֧��VK_QUERY_TYPE_TRANSFORM_FEEDBACK_STREAM_EXT query type
    physicalDeviceTransformFeedbackPropertiesEXT.transformFeedbackStreamsLinesTriangles;//ָ����һ�����߶�� vertex stream ���ʱ���Ƿ�֧��geometry shader OpExecutionMode����֧��OutputPoints ֮��Ҳ֧��OutputLineStrip �Լ� OutputTriangleStrip
    physicalDeviceTransformFeedbackPropertiesEXT.transformFeedbackRasterizationStreamSelect;//ָ���Ƿ�֧��GeometryStreams SPIR-V capability�ҿ�����VkPipelineRasterizationStateStreamCreateInfoEXT ���������ڹ�դ���� vertex stream output
    physicalDeviceTransformFeedbackPropertiesEXT.transformFeedbackDraw;//ָ���Ƿ�֧��ʹ��vkCmdDrawIndirectByteCountEXT


    //VkPhysicalDeviceCopyMemoryIndirectPropertiesNV  �����԰�����VkPhysicalDeviceProperties2.pNext��
    VkPhysicalDeviceCopyMemoryIndirectPropertiesNV physicalDeviceCopyMemoryIndirectPropertiesNV{};
    physicalDeviceCopyMemoryIndirectPropertiesNV.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_COPY_MEMORY_INDIRECT_PROPERTIES_NV;
    physicalDeviceCopyMemoryIndirectPropertiesNV.pNext = nullptr;
    physicalDeviceCopyMemoryIndirectPropertiesNV.supportedQueues;// VkQueueFlagBits ���ֵλ���룬ָ�� indirect copy commands֧�ֵĶ���


    //VkPhysicalDeviceRayTracingPropertiesNV  �����԰�����VkPhysicalDeviceProperties2.pNext��
    VkPhysicalDeviceRayTracingPropertiesNV physicalDeviceRayTracingPropertiesNV{};
    physicalDeviceRayTracingPropertiesNV.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_RAY_TRACING_PROPERTIES_NV;
    physicalDeviceRayTracingPropertiesNV.pNext = nullptr;
    physicalDeviceRayTracingPropertiesNV.shaderGroupHandleSize;//ָ��shader header���ֽڴ�С
    physicalDeviceRayTracingPropertiesNV.maxRecursionDepth;//ָ��trace command����������ݹ����
    physicalDeviceRayTracingPropertiesNV.maxShaderGroupStride;//Ϊshader binding table��shader groups֮�������ֽڲ���
    physicalDeviceRayTracingPropertiesNV.shaderGroupBaseAlignment;//Ϊshader binding table�Ļ����ڴ����Ҫ��
    physicalDeviceRayTracingPropertiesNV.maxGeometryCount;//Ϊ bottom level acceleration strcuture��geometry���������
    physicalDeviceRayTracingPropertiesNV.maxInstanceCount;//Ϊ top level acceleration strcuture��instance���������
    physicalDeviceRayTracingPropertiesNV.maxTriangleCount;//Ϊ bottom level acceleration strcuture������geometry�������ε��������
    physicalDeviceRayTracingPropertiesNV.maxDescriptorSetAccelerationStructures;//Ϊ descriptor set�п��Ժ��е�acceleration strcuture descriptors���������


    //VkPhysicalDeviceAccelerationStructurePropertiesKHR  �����԰�����VkPhysicalDeviceProperties2.pNext��
    VkPhysicalDeviceAccelerationStructurePropertiesKHR physicalDeviceAccelerationStructurePropertiesKHR{};
    physicalDeviceAccelerationStructurePropertiesKHR.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_ACCELERATION_STRUCTURE_PROPERTIES_KHR;
    physicalDeviceAccelerationStructurePropertiesKHR.pNext = nullptr;
    physicalDeviceAccelerationStructurePropertiesKHR.maxGeometryCount;//Ϊ bottom level acceleration strcuture��geometry���������
    physicalDeviceAccelerationStructurePropertiesKHR.maxInstanceCount;//Ϊ top level acceleration strcuture��instance���������
    physicalDeviceAccelerationStructurePropertiesKHR.maxPrimitiveCount;//Ϊ bottom level acceleration strcuture������geometry��AABB���������ε��������
    physicalDeviceAccelerationStructurePropertiesKHR.maxPerStageDescriptorAccelerationStructures;//Ϊһ��pipeline layout�е�һ��shader stage���Է��ʵ�acceleration structure binding���������������������p3962
    physicalDeviceAccelerationStructurePropertiesKHR.maxPerStageDescriptorUpdateAfterBindAccelerationStructures;// ������maxPerStageDescriptorAccelerationStructures��ֻ����descriptors��ͳ�ƴ��Դ������л��߲�����VK_DESCRIPTOR_SET_LAYOUT_CREATE_UPDATE_AFTER_BIND_POOL_BIT ��descriptor sets��ͳ��
    physicalDeviceAccelerationStructurePropertiesKHR.maxDescriptorSetAccelerationStructures;//Ϊ����pipeline shader stages �Լ� descriptor set ����У� һ��pipeline layout�е�һ�� descriptor bindings���ܺ��е�acceleration structure descriptors�����������������Ϣ��p3963
    physicalDeviceAccelerationStructurePropertiesKHR.maxDescriptorSetUpdateAfterBindAccelerationStructures;// ������maxDescriptorSetAccelerationStructures��ֻ����descriptors��ͳ�ƴ��Դ������л��߲�����VK_DESCRIPTOR_SET_LAYOUT_CREATE_UPDATE_AFTER_BIND_POOL_BIT ��descriptor sets��ͳ��
    physicalDeviceAccelerationStructurePropertiesKHR.minAccelerationStructureScratchOffsetAlignment;//Ϊ���ݸ�һ��acceleration structure build command��scratch���ݵ���С�ֽڶ��룬����Ϊ2��ָ��


    //VkPhysicalDeviceRayTracingPipelinePropertiesKHR  �����԰�����VkPhysicalDeviceProperties2.pNext��
    VkPhysicalDeviceRayTracingPipelinePropertiesKHR physicalDeviceRayTracingPipelinePropertiesKHR{};
    physicalDeviceRayTracingPipelinePropertiesKHR.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_RAY_TRACING_PIPELINE_PROPERTIES_KHR;
    physicalDeviceRayTracingPipelinePropertiesKHR.pNext = nullptr;
    physicalDeviceRayTracingPipelinePropertiesKHR.shaderGroupHandleSize;//ָ��shader header���ֽڴ�С
    physicalDeviceRayTracingPipelinePropertiesKHR.maxRayRecursionDepth;//ָ��trace command����������ݹ����
    physicalDeviceRayTracingPipelinePropertiesKHR.maxShaderGroupStride;//Ϊshader binding table��shader groups֮�������ֽڲ���
    physicalDeviceRayTracingPipelinePropertiesKHR.shaderGroupBaseAlignment;//Ϊshader binding table�Ļ����ڴ����Ҫ��
    physicalDeviceRayTracingPipelinePropertiesKHR.shaderGroupHandleCaptureReplaySize;//Ϊ shader group handles ������ͻطŵ���Ϣ��Ҫ���ֽ���
	physicalDeviceRayTracingPipelinePropertiesKHR.maxRayDispatchInvocationCount;//Ϊ���� vkCmdTraceRaysIndirectKHR ���� vkCmdTraceRaysKHR�����п��԰�����ray generation shader invocations���������
    physicalDeviceRayTracingPipelinePropertiesKHR.shaderGroupHandleAlignment;//Ϊshader binding table ��ÿ��ʵ����Ҫ���ֽڶ���Ҫ��Ϊ2��ָ��
    physicalDeviceRayTracingPipelinePropertiesKHR.maxRayHitAttributeSize;//Ϊray attribute structure������ֽ���


    //VkPhysicalDeviceCooperativeMatrixPropertiesNV  �����԰�����VkPhysicalDeviceProperties2.pNext��
    VkPhysicalDeviceCooperativeMatrixPropertiesNV physicalDeviceCooperativeMatrixPropertiesNV{};
    physicalDeviceCooperativeMatrixPropertiesNV.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_COOPERATIVE_MATRIX_PROPERTIES_NV;
    physicalDeviceCooperativeMatrixPropertiesNV.pNext = nullptr;
    physicalDeviceCooperativeMatrixPropertiesNV.cooperativeMatrixSupportedStages;// VkShaderStageFlagBits ���ֵ������cooperative matrix instructions֧�ֵ�shader stages


    //VkPhysicalDeviceCooperativeMatrixPropertiesKHR  �����԰�����VkPhysicalDeviceProperties2.pNext��
    VkPhysicalDeviceCooperativeMatrixPropertiesKHR physicalDeviceCooperativeMatrixPropertiesHKR{};
    physicalDeviceCooperativeMatrixPropertiesHKR.sType = VK_STRUCTURE_TYPE_MAX_ENUM;//û�ж������ﶨ��Ϊ�Ƿ�ֵ
    physicalDeviceCooperativeMatrixPropertiesHKR.pNext = nullptr;
    physicalDeviceCooperativeMatrixPropertiesHKR.cooperativeMatrixSupportedStages;// VkShaderStageFlagBits ���ֵ������cooperative matrix instructions֧�ֵ�shader stages

    //VkPhysicalDeviceShaderSMBuiltinsPropertiesNV  �����԰�����VkPhysicalDeviceProperties2.pNext��
    VkPhysicalDeviceShaderSMBuiltinsPropertiesNV physicalDeviceShaderSMBuiltinsPropertiesNV{};
    physicalDeviceShaderSMBuiltinsPropertiesNV.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_SM_BUILTINS_PROPERTIES_NV;
    physicalDeviceShaderSMBuiltinsPropertiesNV.pNext = nullptr;
    physicalDeviceShaderSMBuiltinsPropertiesNV.shaderSMCount;// device�ϵ�SM������
	physicalDeviceShaderSMBuiltinsPropertiesNV.shaderWarpsPerSM;//Ϊһ��SM��ͬʱ���е�warp������


    //VkPhysicalDeviceTexelBufferAlignmentProperties ���ȼ���VkPhysicalDeviceTexelBufferAlignmentPropertiesEXT  �����԰�����VkPhysicalDeviceProperties2.pNext��
    VkPhysicalDeviceTexelBufferAlignmentProperties physicalDeviceTexelBufferAlignmentProperties{};
    physicalDeviceTexelBufferAlignmentProperties.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_TEXEL_BUFFER_ALIGNMENT_PROPERTIES;
    physicalDeviceTexelBufferAlignmentProperties.pNext = nullptr;
	physicalDeviceTexelBufferAlignmentProperties.storageTexelBufferOffsetAlignmentBytes;//Ϊ���������κ�format��storage texel buffer���ֽڶ���Ҫ��Ϊ2��ָ��
	physicalDeviceTexelBufferAlignmentProperties.storageTexelBufferOffsetSingleTexelAlignment;//Ϊ���������κ�format��storage texel buffer�ĵ���texel�Ķ���Ҫ��Ϊ2��ָ��
	physicalDeviceTexelBufferAlignmentProperties.uniformTexelBufferOffsetAlignmentBytes;//Ϊ���������κ�format��uniform texel buffer���ֽڶ���Ҫ��Ϊ2��ָ��
	physicalDeviceTexelBufferAlignmentProperties.uniformTexelBufferOffsetSingleTexelAlignment;//Ϊ���������κ�format��uniform texel buffer�ĵ���texel�Ķ���Ҫ��Ϊ2��ָ��


    //VkPhysicalDeviceTimelineSemaphoreProperties ���ȼ���VkPhysicalDeviceTimelineSemaphorePropertiesKHR  �����԰�����VkPhysicalDeviceProperties2.pNext��
    VkPhysicalDeviceTimelineSemaphoreProperties physicalDeviceTimelineSemaphoreProperties{};
    physicalDeviceTimelineSemaphoreProperties.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_TIMELINE_SEMAPHORE_PROPERTIES;
    physicalDeviceTimelineSemaphoreProperties.pNext = nullptr;
    physicalDeviceTimelineSemaphoreProperties.maxTimelineSemaphoreValueDifference;//Ϊtimeline semaphore�ĵ�ǰֵ���κι����semaphore�ȴ��Լ�������ֵ֮���ֵ�����ֵ


    //VkPhysicalDeviceLineRasterizationPropertiesKHR ���ȼ���VkPhysicalDeviceLineRasterizationPropertiesEXT  �����԰�����VkPhysicalDeviceProperties2.pNext��
    VkPhysicalDeviceLineRasterizationPropertiesKHR physicalDeviceLineRasterizationPropertiesKHR{};
	physicalDeviceLineRasterizationPropertiesKHR.sType = VK_STRUCTURE_TYPE_MAX_ENUM;//û�ж������ﶨ��Ϊ�Ƿ�ֵ
    physicalDeviceLineRasterizationPropertiesKHR.pNext = nullptr;
	physicalDeviceLineRasterizationPropertiesKHR.lineSubPixelPrecisionBits;//Ϊline rasterization��framebuffer ������xf��yf�� subpixel���ȵ�λ����Ϊ2��ָ��


    //VkPhysicalDeviceRobustness2PropertiesEXT  �����԰�����VkPhysicalDeviceProperties2.pNext��
    VkPhysicalDeviceRobustness2PropertiesEXT physicalDeviceRobustness2PropertiesEXT{};
    physicalDeviceRobustness2PropertiesEXT.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_ROBUSTNESS_2_PROPERTIES_EXT;
    physicalDeviceRobustness2PropertiesEXT.pNext = nullptr;
    physicalDeviceRobustness2PropertiesEXT.robustStorageBufferAccessSizeAlignment;//Ϊ������robustBufferAccess2 ������ʹ��bounds-checking��storage buffer descriptor����ķ�Χ���ֽ���������Ϊ1��4
    physicalDeviceRobustness2PropertiesEXT.robustUniformBufferAccessSizeAlignment;//Ϊ������robustBufferAccess2 ������ʹ��bounds-checking��uniform buffer descriptor����ķ�Χ���ֽ���������Ϊ [1, 256]��Χ�ڵ�2��ָ��


    //VkPhysicalDeviceDeviceGeneratedCommandsPropertiesNV  �����԰�����VkPhysicalDeviceProperties2.pNext��
    VkPhysicalDeviceDeviceGeneratedCommandsPropertiesNV physicalDeviceDeviceGeneratedCommandsPropertiesNV{};
    physicalDeviceDeviceGeneratedCommandsPropertiesNV.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DEVICE_GENERATED_COMMANDS_PROPERTIES_NV;
    physicalDeviceDeviceGeneratedCommandsPropertiesNV.pNext = nullptr;
    physicalDeviceDeviceGeneratedCommandsPropertiesNV.maxGraphicsShaderGroupCount;//ΪVkGraphicsPipelineShaderGroupsCreateInfoNV ��shader groups���������
    physicalDeviceDeviceGeneratedCommandsPropertiesNV.maxIndirectSequenceCount;//ΪVkGeneratedCommandsInfoNV �Լ�VkGeneratedCommandsMemoryRequirementsInfoNV �����е��������
    physicalDeviceDeviceGeneratedCommandsPropertiesNV.maxIndirectCommandsTokenCount;//ΪVkIndirectCommandsLayoutCreateInfoNV ��tokens ���������
    physicalDeviceDeviceGeneratedCommandsPropertiesNV.maxIndirectCommandsStreamCount;//ΪVkIndirectCommandsLayoutCreateInfoNV ��streams ���������
    physicalDeviceDeviceGeneratedCommandsPropertiesNV.maxIndirectCommandsTokenOffset;//Ϊ VkIndirectCommandsLayoutTokenNV ��offset �����ֵ
    physicalDeviceDeviceGeneratedCommandsPropertiesNV.maxIndirectCommandsStreamStride;//ΪVkIndirectCommandsLayoutCreateInfoNV ��stream stride ���������
	physicalDeviceDeviceGeneratedCommandsPropertiesNV.minSequencesCountBufferOffsetAlignment;//Ϊ VkGeneratedCommandsInfoNV ���ڴ��ַ����ʹ�õ���С�ֽڶ���
    physicalDeviceDeviceGeneratedCommandsPropertiesNV.minSequencesIndexBufferOffsetAlignment;//Ϊ  VkGeneratedCommandsInfoNV ���ڴ��ַ����ʹ�õ���С�ֽڶ���
    physicalDeviceDeviceGeneratedCommandsPropertiesNV.minIndirectCommandsBufferOffsetAlignment;//Ϊ  VkIndirectCommandsStreamNV ���ڴ��ַ�Լ�VkGeneratedCommandsInfoNV ��Ԥ����buffer����ʹ�õ���С�ֽڶ���


    //VkPhysicalDevicePortabilitySubsetPropertiesKHR  �����԰�����VkPhysicalDeviceProperties2.pNext��
    VkPhysicalDevicePortabilitySubsetPropertiesKHR physicalDevicePortabilitySubsetPropertiesKHR{};
    physicalDevicePortabilitySubsetPropertiesKHR.sType = VK_STRUCTURE_TYPE_MAX_ENUM;//û�ж������ﶨ��Ϊ�Ƿ�ֵ
    physicalDevicePortabilitySubsetPropertiesKHR.pNext = nullptr;
	physicalDevicePortabilitySubsetPropertiesKHR.minVertexInputBindingStrideAlignment;//Ϊvertex input binding stride����С�ֽڶ���Ҫ��Ϊ2��ָ��


    //VkPhysicalDeviceFragmentShadingRatePropertiesKHR  �����԰�����VkPhysicalDeviceProperties2.pNext��
    VkPhysicalDeviceFragmentShadingRatePropertiesKHR physicalDeviceFragmentShadingRatePropertiesKHR{};
    physicalDeviceFragmentShadingRatePropertiesKHR.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FRAGMENT_SHADING_RATE_PROPERTIES_KHR;
    physicalDeviceFragmentShadingRatePropertiesKHR.pNext = nullptr;
	physicalDeviceFragmentShadingRatePropertiesKHR.minFragmentShadingRateAttachmentTexelSize;//ָ��fragment shading rate attachmentÿ��texel ��Ӧ��framebuffer �����width�Լ�height����Сֵ������������p3971
    physicalDeviceFragmentShadingRatePropertiesKHR.maxFragmentShadingRateAttachmentTexelSize;//ָ��fragment shading rate attachmentÿ��texel ��Ӧ��framebuffer �����width�Լ�height�����ֵ������������p3971
	physicalDeviceFragmentShadingRatePropertiesKHR.maxFragmentShadingRateAttachmentTexelSizeAspectRatio;//ָ��fragment shading rate attachmentÿ��texel ��Ӧ��framebuffer �����width�Լ�height�ı�ֵ�����ֵ������������p3971
    physicalDeviceFragmentShadingRatePropertiesKHR.primitiveFragmentShadingRateWithMultipleViewports;//ָ���Ƿ� primitive fragment shading rate ���Ժ�multiple viewports һ��ʹ�ã�����������p3972
    physicalDeviceFragmentShadingRatePropertiesKHR.layeredShadingRateAttachments;//ָ��һ�� shading rate attachment image view���Ժ����layer����������������p3972
    physicalDeviceFragmentShadingRatePropertiesKHR.fragmentShadingRateNonTrivialCombinerOps;//ָ����VK_FRAGMENT_SHADING_RATE_COMBINER_OP_KEEP_KHR ����VK_FRAGMENT_SHADING_RATE_COMBINER_OP_REPLACE_KHR ֮���VkFragmentShadingRateCombinerOpKHR ö��ֵ�Ƿ����ʹ��
	physicalDeviceFragmentShadingRatePropertiesKHR.maxFragmentSize;//ָ��һ��fragment֧�ֵ�width��height�����ֵ������������p3972
    physicalDeviceFragmentShadingRatePropertiesKHR.maxFragmentSizeAspectRatio;//ָ��һ��fragment֧�ֵ�width��height��ֵ�����ֵ������������p3972
	physicalDeviceFragmentShadingRatePropertiesKHR.maxFragmentShadingRateCoverageSamples;//ָ��һ��fragment��coverage samples���������������������p3972
    physicalDeviceFragmentShadingRatePropertiesKHR.maxFragmentShadingRateRasterizationSamples;// VkSampleCountFlagBits ���ֵλ���룬ָ����һ��fragment�������pixelsʱ֧�ֵ� sample rate�����ֵ
	physicalDeviceFragmentShadingRatePropertiesKHR.fragmentShadingRateWithShaderDepthStencilWrites;//ָ���Ƿ�֧����fragment shader�ж�multi-pixel fragmentͨ�� FragDepth ���� FragStencilRefEXTд������Լ�stencilֵ������������p3973
    physicalDeviceFragmentShadingRatePropertiesKHR.fragmentShadingRateWithSampleMask;//ָ���Ƿ�֧�ֶ� multi-pixel fragments���� VkPipelineMultisampleStateCreateInfo::pSampleMask ����ЧλΪ0������������p3973
	physicalDeviceFragmentShadingRatePropertiesKHR.fragmentShadingRateWithShaderSampleMask;//ָ���Ƿ�֧�ֶ�дmulti-pixel fragment��SampleMask ������������p3973
	physicalDeviceFragmentShadingRatePropertiesKHR.fragmentShadingRateWithConservativeRasterization;//ָ���� multi-pixel fragments�Ƿ�֧��conservative rasterization ������������p3973
    physicalDeviceFragmentShadingRatePropertiesKHR.fragmentShadingRateWithFragmentShaderInterlock;//ָ���� multi-pixel fragments�Ƿ�֧�� fragment shader interlock ������������p3973
	physicalDeviceFragmentShadingRatePropertiesKHR.fragmentShadingRateWithCustomSampleLocations;//ָ���� multi-pixel fragments�Ƿ�֧�� custom sample locations ������������p3973
	physicalDeviceFragmentShadingRatePropertiesKHR.fragmentShadingRateStrictMultiplyCombiner;//ָ��VK_FRAGMENT_SHADING_RATE_COMBINER_OP_MUL_KHR �Ƿ�ȷ��ִ�г˷�����������������p3974


    //VkPhysicalDeviceFragmentShadingRateEnumsPropertiesNV  �����԰�����VkPhysicalDeviceProperties2.pNext��
    VkPhysicalDeviceFragmentShadingRateEnumsPropertiesNV physicalDeviceFragmentShadingRateEnumsPropertiesNV{};
    physicalDeviceFragmentShadingRateEnumsPropertiesNV.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FRAGMENT_SHADING_RATE_ENUMS_PROPERTIES_NV;
    physicalDeviceFragmentShadingRateEnumsPropertiesNV.pNext = nullptr;
	physicalDeviceFragmentShadingRateEnumsPropertiesNV.maxFragmentShadingRateInvocationCount;//һ�� VkSampleCountFlagBits ֵָ��pipeline��primitive, �Լ� attachment fragment shading rates��һ��fragment�ܹ����õ�fragment shader��������������������p3975


    //VkPhysicalDeviceCustomBorderColorPropertiesEXT  �����԰�����VkPhysicalDeviceProperties2.pNext��
    VkPhysicalDeviceCustomBorderColorPropertiesEXT physicalDeviceCustomBorderColorPropertiesEXT{};
    physicalDeviceCustomBorderColorPropertiesEXT.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_CUSTOM_BORDER_COLOR_PROPERTIES_EXT;
    physicalDeviceCustomBorderColorPropertiesEXT.pNext = nullptr;
	physicalDeviceCustomBorderColorPropertiesEXT.maxCustomBorderColorSamplers;//Ϊ����ͬʱ������device�ϵĺ�custom border color�� samplers���������


    //VkPhysicalDeviceProvokingVertexPropertiesEXT  �����԰�����VkPhysicalDeviceProperties2.pNext��
    VkPhysicalDeviceProvokingVertexPropertiesEXT physicalDeviceProvokingVertexPropertiesEXT{};
    physicalDeviceProvokingVertexPropertiesEXT.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PROVOKING_VERTEX_PROPERTIES_EXT;
    physicalDeviceProvokingVertexPropertiesEXT.pNext = nullptr;
    physicalDeviceProvokingVertexPropertiesEXT.provokingVertexModePerPipeline;//ָ���Ƿ�graphics pipeline����ͬrender passʵ����ʹ�ò�ͬ��provoking vertex modes
    physicalDeviceProvokingVertexPropertiesEXT.transformFeedbackPreservesTriangleFanProvokingVertex;//ָ����д��triangle fanͼԪ���㵽transform feedback�Ƿ���Ա���provoking vertex order


    //VkPhysicalDeviceDescriptorBufferPropertiesEXT  �����԰�����VkPhysicalDeviceProperties2.pNext��
    VkPhysicalDeviceDescriptorBufferPropertiesEXT physicalDeviceDescriptorBufferPropertiesEXT{};
    physicalDeviceDescriptorBufferPropertiesEXT.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DESCRIPTOR_BUFFER_PROPERTIES_EXT;
    physicalDeviceDescriptorBufferPropertiesEXT.pNext = nullptr;
    physicalDeviceDescriptorBufferPropertiesEXT.combinedImageSamplerDescriptorSingleArray;//��ʾʵ�ֲ���Ҫ��VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER������������Ϊͼ������������д�����������������������ǲ���������������
    physicalDeviceDescriptorBufferPropertiesEXT.bufferlessPushDescriptors;//ָ����ʹ��push descriptors ʱ����Ҫ��һ���� VK_BUFFER_USAGE_PUSH_DESCRIPTORS_DESCRIPTOR_BUFFER_BIT_EXT ������buffer
    physicalDeviceDescriptorBufferPropertiesEXT.allowSamplerImageViewPostSubmitCreation;//ָ�����Թ����� command buffer �ύ�����ڻ�ȡdescriptor���ݴ����� VkSampler ���� VkImageView��������
    physicalDeviceDescriptorBufferPropertiesEXT.descriptorBufferOffsetAlignment;//ָ�������õ�descriptor buffer����Ҫ��ƫ�Ƶ��ֽڶ���
    physicalDeviceDescriptorBufferPropertiesEXT.maxDescriptorBufferBindings;//ָ�����԰󶨵�descriptor buffers ��embedded immutable sampler sets���������������
    physicalDeviceDescriptorBufferPropertiesEXT.maxResourceDescriptorBufferBindings;//ָ�����԰󶨵�resource descriptor buffers ���������
    physicalDeviceDescriptorBufferPropertiesEXT.maxSamplerDescriptorBufferBindings;//ָ�����԰󶨵�sampler descriptor buffers ���������
	physicalDeviceDescriptorBufferPropertiesEXT.maxEmbeddedImmutableSamplerBindings;//ָ�����԰󶨵�embedded immutable sampler sets ���������
	physicalDeviceDescriptorBufferPropertiesEXT.maxEmbeddedImmutableSamplers;//ָ������ͬʱ������device�ϵ���VK_DESCRIPTOR_SET_LAYOUT_CREATE_EMBEDDED_IMMUTABLE_SAMPLERS_BIT_EXT������descriptor set layouts�Լ��Ӹ�layout ������pipeline�в��ظ���immutable samplers�������������
    physicalDeviceDescriptorBufferPropertiesEXT.bufferCaptureReplayDescriptorDataSize;//ָ����buffers����ͻط�opaque data������ֽ�����С
	physicalDeviceDescriptorBufferPropertiesEXT.imageCaptureReplayDescriptorDataSize;//ָ����images����ͻط�opaque data������ֽ�����С
    physicalDeviceDescriptorBufferPropertiesEXT.imageViewCaptureReplayDescriptorDataSize;//ָ����image views����ͻط�opaque data������ֽ�����С
    physicalDeviceDescriptorBufferPropertiesEXT.samplerCaptureReplayDescriptorDataSize;//ָ����samplers����ͻط�opaque data������ֽ�����С
    physicalDeviceDescriptorBufferPropertiesEXT.accelerationStructureCaptureReplayDescriptorDataSize;//ָ����acceleration structures����ͻط�opaque data������ֽ�����С
    physicalDeviceDescriptorBufferPropertiesEXT.samplerDescriptorSize;//ָ�� VK_DESCRIPTOR_TYPE_SAMPLER ����descriptor���ֽڴ�С
	physicalDeviceDescriptorBufferPropertiesEXT.combinedImageSamplerDescriptorSize;//ָ�� VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER ����descriptor���ֽڴ�С
	physicalDeviceDescriptorBufferPropertiesEXT.sampledImageDescriptorSize;//ָ�� VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE ����descriptor���ֽڴ�С
    physicalDeviceDescriptorBufferPropertiesEXT.storageImageDescriptorSize;//ָ�� VK_DESCRIPTOR_TYPE_STORAGE_IMAGE ����descriptor���ֽڴ�С
	physicalDeviceDescriptorBufferPropertiesEXT.uniformTexelBufferDescriptorSize;//ָ����� robustBufferAccess���� ������ʱ VK_DESCRIPTOR_TYPE_UNIFORM_TEXEL_BUFFER ����descriptor���ֽڴ�С
	physicalDeviceDescriptorBufferPropertiesEXT.robustUniformTexelBufferDescriptorSize;//ָ����� robustBufferAccess ���Կ���ʱ VK_DESCRIPTOR_TYPE_UNIFORM_TEXEL_BUFFER ����descriptor���ֽڴ�С
	physicalDeviceDescriptorBufferPropertiesEXT.storageTexelBufferDescriptorSize;//ָ����� robustBufferAccess���� ������ʱ VK_DESCRIPTOR_TYPE_STORAGE_TEXEL_BUFFER ����descriptor���ֽڴ�С
	physicalDeviceDescriptorBufferPropertiesEXT.robustStorageTexelBufferDescriptorSize;//ָ����� robustBufferAccess ���Կ���ʱ VK_DESCRIPTOR_TYPE_STORAGE_TEXEL_BUFFER ����descriptor���ֽڴ�С
	physicalDeviceDescriptorBufferPropertiesEXT.uniformBufferDescriptorSize;//ָ�� VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER ����descriptor���ֽڴ�С
    physicalDeviceDescriptorBufferPropertiesEXT.robustUniformBufferDescriptorSize;//ָ����� robustBufferAccess ���Կ���ʱ VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER ����descriptor���ֽڴ�С
    physicalDeviceDescriptorBufferPropertiesEXT.storageBufferDescriptorSize;//ָ�� VK_DESCRIPTOR_TYPE_STORAGE_BUFFER ����descriptor���ֽڴ�С
    physicalDeviceDescriptorBufferPropertiesEXT.robustStorageBufferDescriptorSize;//ָ����� robustBufferAccess ���Կ���ʱ VK_DESCRIPTOR_TYPE_STORAGE_BUFFER ����descriptor���ֽڴ�С
    physicalDeviceDescriptorBufferPropertiesEXT.inputAttachmentDescriptorSize;//ָ�� VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT ����descriptor���ֽڴ�С
    physicalDeviceDescriptorBufferPropertiesEXT.accelerationStructureDescriptorSize;//ָ�� VK_DESCRIPTOR_TYPE_ACCELERATION_STRUCTURE_KHR ���� VK_DESCRIPTOR_TYPE_ACCELERATION_STRUCTURE_NV ����descriptor���ֽڴ�С
    physicalDeviceDescriptorBufferPropertiesEXT.maxSamplerDescriptorBufferRange;//Ϊһ��shader���Է��ʵ�sampler descriptor buffer binding�ĵ�ַ������ֽڷ�Χ
	physicalDeviceDescriptorBufferPropertiesEXT.maxResourceDescriptorBufferRange;//Ϊһ��shader���Է��ʵ�resource descriptor buffer binding�ĵ�ַ������ֽڷ�Χ
	physicalDeviceDescriptorBufferPropertiesEXT.samplerDescriptorBufferAddressSpaceSize;//Ϊ��VK_BUFFER_USAGE_SAMPLER_DESCRIPTOR_BUFFER_BIT_EXT������descriptor buffers�Ŀɷ��ʵ�ַ�ռ������ֽ���
    physicalDeviceDescriptorBufferPropertiesEXT.resourceDescriptorBufferAddressSpaceSize;//Ϊ��VK_BUFFER_USAGE_RESOURCE_DESCRIPTOR_BUFFER_BIT_EXT������descriptor buffers�Ŀɷ��ʵ�ַ�ռ������ֽ���
    physicalDeviceDescriptorBufferPropertiesEXT.descriptorBufferAddressSpaceSize;//Ϊͬʱ�� VK_BUFFER_USAGE_SAMPLER_DESCRIPTOR_BUFFER_BIT_EXT�� VK_BUFFER_USAGE_RESOURCE_DESCRIPTOR_BUFFER_BIT_EXT������descriptor buffers�Ŀɷ��ʵ�ַ�ռ������ֽ���


    //VkPhysicalDeviceDescriptorBufferDensityMapPropertiesEXT  �����԰�����VkPhysicalDeviceProperties2.pNext��
    VkPhysicalDeviceDescriptorBufferDensityMapPropertiesEXT physicalDeviceDescriptorBufferDensityMapPropertiesEXT{};
    physicalDeviceDescriptorBufferDensityMapPropertiesEXT.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DESCRIPTOR_BUFFER_DENSITY_MAP_PROPERTIES_EXT;
    physicalDeviceDescriptorBufferDensityMapPropertiesEXT.pNext = nullptr;
	physicalDeviceDescriptorBufferDensityMapPropertiesEXT.combinedImageSamplerDensityMapDescriptorSize;//Ϊ��VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER������������VK_SAMPLER_CREATE_SUBSAMPLED_BIT_EXT ������descriptor ���ֽڴ�С





}

void LimitsAndFormatsTest::FormatsTest()
{
}



NS_TEST_END