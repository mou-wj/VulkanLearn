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






}

void LimitsAndFormatsTest::FormatsTest()
{
}



NS_TEST_END