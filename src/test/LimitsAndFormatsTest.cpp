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
	//limits是应用需要意识到的 依赖实现的的最小限制，最大限制以及其他device属性的限制，这些限制见 VkPhysicalDeviceLimits 或者VkPhysicalDeviceProperties或者VkPhysicalDeviceProperties2，或其他的properties
    VkPhysicalDeviceProperties physicalDeviceProperties{};
    vkGetPhysicalDeviceProperties(physicalDevice, &physicalDeviceProperties);


	VkPhysicalDeviceLimits &physicalDeviceLimits = physicalDeviceProperties.limits;
    physicalDeviceLimits.maxImageDimension1D;//指明可创建的imageType为VK_IMAGE_TYPE_1D 的image的width的最大值，在某些image创建参数组合下，该值可能超过这里列举的值，具体见vkGetPhysicalDeviceImageFormatProperties
    physicalDeviceLimits.maxImageDimension2D;//指明可创建的imageType为VK_IMAGE_TYPE_2D且不含VK_IMAGE_CREATE_CUBE_COMPATIBLE_BIT 的image的width 或者 height的最大值，在某些image创建参数组合下，该值可能超过这里列举的值，具体见vkGetPhysicalDeviceImageFormatProperties
    physicalDeviceLimits.maxImageDimension3D;//指明可创建的imageType为 VK_IMAGE_TYPE_3D 的image的width ，height或者depth 的最大值，在某些image创建参数组合下，该值可能超过这里列举的值，具体见vkGetPhysicalDeviceImageFormatProperties
    physicalDeviceLimits.maxImageDimensionCube;//指明可创建的imageType为VK_IMAGE_TYPE_2D且含VK_IMAGE_CREATE_CUBE_COMPATIBLE_BIT 的image的width 或者 height的最大值，在某些image创建参数组合下，该值可能超过这里列举的值，具体见vkGetPhysicalDeviceImageFormatProperties
    physicalDeviceLimits.maxImageArrayLayers;//为image中最大的layer数
    physicalDeviceLimits.maxTexelBufferElements;//为一个以VK_BUFFER_USAGE_UNIFORM_TEXEL_BUFFER_BIT 或者 VK_BUFFER_USAGE_STORAGE_TEXEL_BUFFER_BIT 创建的buffer的buffer view中可寻址的texel的最大数量
    physicalDeviceLimits.maxUniformBufferRange;//指明对VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER 或者 VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC类型的descriptors的传递给 vkUpdateDescriptorSets的VkDescriptorBufferInfo.range参数的最大值
    physicalDeviceLimits.maxStorageBufferRange;//指明对VK_DESCRIPTOR_TYPE_STORAGE_BUFFER 或者 VK_DESCRIPTOR_TYPE_STORAGE_BUFFER_DYNAMIC类型的descriptors的传递给 vkUpdateDescriptorSets的VkDescriptorBufferInfo.range参数的最大值
    physicalDeviceLimits.maxPushConstantsSize;//为push constance 内存池的最大字节大小，对VkPipelineLayoutCreateInfo.pPushConstantRanges的每个元素的（size + offset）必须小于该值
    physicalDeviceLimits.maxMemoryAllocationCount;//为vkAllocateMemory 分配的device memory对象的最大数量
    physicalDeviceLimits.maxSamplerAllocationCount;//为vkCreateSampler 创建的sampler对象的最大数量
    physicalDeviceLimits.bufferImageGranularity;//为 buffer 或者 linear image resources或者optimal image resources可以在同一VkDeviceMemory对象中邻接绑定且不重复的字节粒度
    physicalDeviceLimits.sparseAddressSpaceSize;//为sparse memory resources的总的可用的地址字节空间，根据 extendedSparseAddressSpace 特性具体的对象的可用空间可能会被拓展
    physicalDeviceLimits.maxBoundDescriptorSets;//为pipeline同一时间可以使用的descriptor set的数量，且shader module中DescriptorSet声明必须小于该值
    physicalDeviceLimits.maxPerStageDescriptorSamplers;//为pipeline layout中一个shader stage中可以访问的sampler的最大数量，只有符合相关类型或者其他条件的descriptor才会计入此限制，见p3912
    physicalDeviceLimits.maxPerStageDescriptorUniformBuffers;//为pipeline layout中一个shader stage中可以访问的uniform buffers的最大数量，只有符合相关类型或者其他条件的descriptor才会计入此限制，见p3912
    physicalDeviceLimits.maxPerStageDescriptorStorageBuffers;//为pipeline layout中一个shader stage中可以访问的storage buffers的最大数量，只有符合相关类型或者其他条件的descriptor才会计入此限制，见p3913
    physicalDeviceLimits.maxPerStageDescriptorSampledImages;//为pipeline layout中一个shader stage中可以访问的sampled images的最大数量，只有符合相关类型或者其他条件的descriptor才会计入此限制，见p3913
    physicalDeviceLimits.maxPerStageDescriptorStorageImages;//为pipeline layout中一个shader stage中可以访问的storage images的最大数量，只有符合相关类型或者其他条件的descriptor才会计入此限制，见p3913
    physicalDeviceLimits.maxPerStageDescriptorInputAttachments;//为pipeline layout中一个shader stage中可以访问的input attachment的最大数量，只有符合相关类型或者其他条件的descriptor才会计入此限制，见p3913
    physicalDeviceLimits.maxPerStageResources;//为pipeline layout中一个shader stage中可以访问的资源resources的最大数量，只有符合相关类型或者其他条件的descriptor才会计入此限制，见p3913
    physicalDeviceLimits.maxDescriptorSetSamplers;//为一个pipeline layout中可以包含的samplers的最大数量，只有符合相关类型或者其他条件的descriptor才会计入此限制，见p3914
    physicalDeviceLimits.maxDescriptorSetUniformBuffers;//为一个pipeline layout中可以包含的uniform buffers的最大数量，只有符合相关类型或者其他条件的descriptor才会计入此限制，见p3914
    physicalDeviceLimits.maxDescriptorSetUniformBuffersDynamic;//为一个pipeline layout中可以包含的dynamic uniform buffers的最大数量，只有符合相关类型或者其他条件的descriptor才会计入此限制，见p3914
    physicalDeviceLimits.maxDescriptorSetStorageBuffers;//为一个pipeline layout中可以包含的 storage buffers的最大数量，只有符合相关类型或者其他条件的descriptor才会计入此限制，见p3914
    physicalDeviceLimits.maxDescriptorSetStorageBuffersDynamic;//为一个pipeline layout中可以包含的dynamic storage buffers的最大数量，只有符合相关类型或者其他条件的descriptor才会计入此限制，见p3914
    physicalDeviceLimits.maxDescriptorSetSampledImages;//为一个pipeline layout中可以包含的sampled images的最大数量，只有符合相关类型或者其他条件的descriptor才会计入此限制，见p3914
    physicalDeviceLimits.maxDescriptorSetStorageImages;//为一个pipeline layout中可以包含的storage images的最大数量，只有符合相关类型或者其他条件的descriptor才会计入此限制，见p3914
    physicalDeviceLimits.maxDescriptorSetInputAttachments;//为一个pipeline layout中可以包含的input attachment的最大数量，只有符合相关类型或者其他条件的descriptor才会计入此限制，见p3914
    physicalDeviceLimits.maxVertexInputAttributes;//为graphics pipeline中可以指定的vertex input attributes的最大数量，详细描述见p3915
    physicalDeviceLimits.maxVertexInputBindings;//为graphics pipeline中可以指定的提供vertex input attributes的vertex buffer的最大数量，详细描述见p3915
    physicalDeviceLimits.maxVertexInputAttributeOffset;//为可以添加到 vertex input binding stride的vertex input attribute offset的最大值，详细描述见p3915
    physicalDeviceLimits.maxVertexInputBindingStride;//为一个 vertex input binding中可以指定的vertex input binding stride的最大值，详细描述见p3915
    physicalDeviceLimits.maxVertexOutputComponents;//为shader 输出变量分量数的最大值
    physicalDeviceLimits.maxTessellationGenerationLevel;//为fixed-function tessellation primitive generator 支持的 tessellation generation level的最大值
    physicalDeviceLimits.maxTessellationPatchSize;//为tessellation control shader 以及 tessellation primitive generator可以处理的每个patch的顶点数的最大值，详细描述见p3915 
    physicalDeviceLimits.maxTessellationControlPerVertexInputComponents;//为可以提供给 tessellation control shader stage作为per-vertex inputs的输入变量的分量数的最大大小
    physicalDeviceLimits.maxTessellationControlPerVertexOutputComponents;//为可以从 tessellation control shader stage输出的per-vertex output variables的分量数的最大大小
    physicalDeviceLimits.maxTessellationControlPerPatchOutputComponents;//为可以从 tessellation control shader stage输出的per-patch output variables的分量数的最大大小
    physicalDeviceLimits.maxTessellationControlTotalOutputComponents;//为可以从 tessellation control shader stage输出的per-vertex 以及 per-patch output variables的分量总数的最大大小
    physicalDeviceLimits.maxTessellationEvaluationInputComponents;//为可以提供给 tessellation evaluation shader stage作为per-vertex inputs的输入变量的分量数的最大大小
    physicalDeviceLimits.maxTessellationEvaluationOutputComponents;//为可以从 tessellation evaluation shader stage输出的per-vertex output variables的分量数的最大大小
    physicalDeviceLimits.maxGeometryShaderInvocations;//为instanced geometry shaders可以调用的最大数量
    physicalDeviceLimits.maxGeometryInputComponents;//为可以提供给 geometry shader stage作为inputs的输入变量的分量数的最大大小
    physicalDeviceLimits.maxGeometryOutputComponents;//为可以从 geometry shader stage输出的output variables的分量数的最大大小
    physicalDeviceLimits.maxGeometryOutputVertices;//为任何geometry shader 可以发射的最大顶点数
    physicalDeviceLimits.maxGeometryTotalOutputComponents;//为可以从 geometry shader stage输出的所有发射顶点的output variables的分量数总数的最大大小
    physicalDeviceLimits.maxFragmentInputComponents;//为可以提供给 fragment shader stage作为inputs的输入变量的分量数的最大大小
    physicalDeviceLimits.maxFragmentOutputAttachments;//为可以从 fragment shader stage可以写出的的output attachments的最大数量
    physicalDeviceLimits.maxFragmentDualSrcAttachments;//为当开启blending且使用了一种dual source blend modes时可以从 fragment shader stage可以写出的的output attachments的最大数量
    physicalDeviceLimits.maxFragmentCombinedOutputResources;//为 fragment shader stage中可以使用的 storage buffers, storage images以及 Location 声明的输出 color attachments的总数的最大数量
    physicalDeviceLimits.maxComputeSharedMemorySize;//为compute shader stage 中 shader modules 中以 Workgroup storage class 声明（或者GLSL中以shared声明）的变量的最大字节存储大小
    physicalDeviceLimits.maxComputeWorkGroupCount[3];//为一个dispatching command 派发的local workgroups的最大大小，分别对应X，Y，Z
    physicalDeviceLimits.maxComputeWorkGroupInvocations;//为一个local workgroup中可以调用的compute shader总共的最大数量，其他详情见p3916
    physicalDeviceLimits.maxComputeWorkGroupSize[3];//为每个维度 local compute workgroup的最大大小，其他详情见p3916
    physicalDeviceLimits.subPixelPrecisionBits;//为framebuffer coordinates中subpixel 精度的最大bit数
    physicalDeviceLimits.subTexelPrecisionBits;//为沿着用于minification and magnification filters的image的轴的划分精度的bit数，其他详情见p3916
    physicalDeviceLimits.mipmapPrecisionBits;//是确定每个 mip 级对 mip 过滤结果的贡献时，对 mipmap 加载的 LOD 计算进行截断时所使用的位数的数量，详情见p3916
    physicalDeviceLimits.maxDrawIndexedIndexValue;//为使用32-bit 索引时indexed draw calls可以使用的最大索引值
    physicalDeviceLimits.maxDrawIndirectCount;//为 indirect drawing calls 可以支持的最大draw count
    physicalDeviceLimits.maxSamplerLodBias;//为absolute sampler LOD bias的最大值，其他信息见p3917
    physicalDeviceLimits.maxSamplerAnisotropy;//为 sampler anisotropy的最大级别，其他信息见p3917
    physicalDeviceLimits.maxViewports;//为 active viewports的最大数量，其他信息见p3917
    physicalDeviceLimits.maxViewportDimensions[2];//为 viewport维度width以及height的最大值，其他信息见p3917
    physicalDeviceLimits.viewportBoundsRange[2];//为viewport的corners必须包含的 [minimum, maximum]范围，其他信息见p3917
    physicalDeviceLimits.viewportSubPixelBits;//为viewport边界的subpixel精度的bit数
    physicalDeviceLimits.minMemoryMapAlignment;//为在host内存空间分配的host 可见的memory内存分配的字节对齐的最小值，其他信息见p3917
    physicalDeviceLimits.minTexelBufferOffsetAlignment;//为texel buffers的 VkBufferViewCreateInfo.offset所对的字节对齐的最小值，为2的指数，其他信息见p3917
    physicalDeviceLimits.minUniformBufferOffsetAlignment;//为uniform buffers的 VkDescriptorBufferInfo.offset所对的字节对齐的最小值，为2的指数，其他信息见p3917
    physicalDeviceLimits.minStorageBufferOffsetAlignment;//为storage buffers的 VkDescriptorBufferInfo.offset所对的字节对齐的最小值，为2的指数，其他信息见p3917
    physicalDeviceLimits.minTexelOffset;//为任何OpImageSample* 或者 OpImageFetch*  image指令的ConstOffset image操作符的最小偏移值
    physicalDeviceLimits.maxTexelOffset;//为任何OpImageSample* 或者 OpImageFetch*  image指令的ConstOffset image操作符的最大偏移值
    physicalDeviceLimits.minTexelGatherOffset;//为任何 OpImage*Gather  image指令的Offset, ConstOffset, 或者 ConstOffsets image操作符的最小偏移值
    physicalDeviceLimits.maxTexelGatherOffset;//为任何 OpImage*Gather  image指令的Offset, ConstOffset, 或者 ConstOffsets image操作符的最小偏移值
    physicalDeviceLimits.minInterpolationOffset;//为InterpolateAtOffset 拓展指令的 Offset操作符的最小负最小值
    physicalDeviceLimits.maxInterpolationOffset;//为InterpolateAtOffset 拓展指令的 Offset操作符的最大正最大值
    physicalDeviceLimits.subPixelInterpolationOffsetBits;//执行InterpolateAtOffset扩展指令时，x和y偏移量可能以定点值进行舍入的小数位数
    physicalDeviceLimits.maxFramebufferWidth;//为framebuffer的width的最大值
    physicalDeviceLimits.maxFramebufferHeight;//为framebuffer的height的最大值
    physicalDeviceLimits.maxFramebufferLayers;//为framebuffer中含有layers的最大数量
    physicalDeviceLimits.framebufferColorSampleCounts;//为所有格式为浮点或者顶点数的framebuffer color attachments支持的sample counts的VkSampleCountFlagBits组合值
    physicalDeviceLimits.framebufferDepthSampleCounts;//为所有格式包含depth的framebuffer depth/stencil attachments支持的depth sample counts的VkSampleCountFlagBits组合值
    physicalDeviceLimits.framebufferStencilSampleCounts;//为所有格式包含stencil的framebuffer depth/stencil attachments支持的stencil sample counts的VkSampleCountFlagBits组合值
    physicalDeviceLimits.framebufferNoAttachmentsSampleCounts;//为不含附件的subpass 支持的sample counts的VkSampleCountFlagBits组合值
    physicalDeviceLimits.maxColorAttachments;//为render pass中subpass可以使用的color attachments的最大数量
    physicalDeviceLimits.sampledImageColorSampleCounts;// VkSampleCountFlagBits 组合值位掩码，指明所有以VK_IMAGE_TILING_OPTIMAL创建的，usage包含VK_IMAGE_USAGE_SAMPLED_BIT且含non-integer color format的所有2D image支持的sample counts
    physicalDeviceLimits.sampledImageIntegerSampleCounts;// VkSampleCountFlagBits 组合值位掩码，指明所有以VK_IMAGE_TILING_OPTIMAL创建的，usage包含VK_IMAGE_USAGE_SAMPLED_BIT且含integer color format的所有2D image支持的sample counts
    physicalDeviceLimits.sampledImageDepthSampleCounts;// VkSampleCountFlagBits 组合值位掩码，指明所有以VK_IMAGE_TILING_OPTIMAL创建的，usage包含VK_IMAGE_USAGE_SAMPLED_BIT且含depth format的所有2D image支持的sample counts
    physicalDeviceLimits.sampledImageStencilSampleCounts;// VkSampleCountFlagBits 组合值位掩码，指明所有以VK_IMAGE_TILING_OPTIMAL创建的，usage包含VK_IMAGE_USAGE_SAMPLED_BIT且含stencil format的所有2D image支持的sample counts
    physicalDeviceLimits.storageImageSampleCounts;// VkSampleCountFlagBits 组合值位掩码，指明所有以VK_IMAGE_TILING_OPTIMAL创建的，usage包含VK_IMAGE_USAGE_STORAGE_BIT的所有2D image支持的sample counts
    physicalDeviceLimits.maxSampleMaskWords;//为以SampleMask 声明的变量的数组元素的最大数量
    physicalDeviceLimits.timestampComputeAndGraphics;//指明支持所有graphics 以及 compute queues上的timestamps，其他信息见p3919
    physicalDeviceLimits.timestampPeriod;//为timastamp query增加1所需要的纳秒数
    physicalDeviceLimits.maxClipDistances;//为可用于一个shader stage的 clip distances的最大值
    physicalDeviceLimits.maxCullDistances;//为可用于一个shader stage的 cull distances的最大值
    physicalDeviceLimits.maxCombinedClipAndCullDistances;//为可用于一个shader stage的绑定的 clip以及cull distances的数量的最大值
    physicalDeviceLimits.discreteQueuePriorities;//为基于 VkDeviceQueueCreateInfo::pQueuePriorities中每个元素值的可以排列为队列的离散属性的最大数量
    physicalDeviceLimits.pointSizeRange[2];//为point size（ PointSize内嵌变量）支持的大小范围[minimum,maximum]
    physicalDeviceLimits.lineWidthRange[2];//为线宽（ 光栅化 lineWidth参数）支持的大小范围[minimum,maximum]
    physicalDeviceLimits.pointSizeGranularity;//为point size（ PointSize内嵌变量）支持的大小范围内的间隔粒度
    physicalDeviceLimits.lineWidthGranularity;//为线宽（ 光栅化 lineWidth参数）支持的大小范围内的间隔粒度
    physicalDeviceLimits.strictLines;//指明是否线按照首选方法进行光栅化，其他信息见p3920
    physicalDeviceLimits.standardSampleLocations;//指明是否光栅化是否是否标准的采样点位置，其他信息见p3920
    physicalDeviceLimits.optimalBufferCopyOffsetAlignment;//为最佳的buffer offset alignment，基于字节，对命令:vkCmdCopyBufferToImage2, vkCmdCopyBufferToImage, vkCmdCopyImageToBuffer2, vkCmdCopyImageToBuffer,vkCopyMemoryToImageEXT 以及 vkCopyImageToMemoryEXT
    physicalDeviceLimits.optimalBufferCopyRowPitchAlignment;//为最佳的buffer row pitch alignment，基于字节，对命令:vkCmdCopyBufferToImage2, vkCmdCopyBufferToImage, vkCmdCopyImageToBuffer2, vkCmdCopyImageToBuffer,vkCopyMemoryToImageEXT 以及 vkCopyImageToMemoryEXT
    physicalDeviceLimits.nonCoherentAtomSize;//为并发访问 host-mapped device memory时的内存范围的字节大小以及字节对齐


    //VkSampleCountFlagBits
    VkSampleCountFlagBits sampleCountFlagBits{};
    /*
    VK_SAMPLE_COUNT_1_BIT  : 指明一个image含 one sample per pixel.
    VK_SAMPLE_COUNT_2_BIT  : 指明一个image含 2 samples per pixel.
    VK_SAMPLE_COUNT_4_BIT  : 指明一个image含 4 samples per pixel.
    VK_SAMPLE_COUNT_8_BIT  : 指明一个image含 8 samples per pixel.
    VK_SAMPLE_COUNT_16_BIT  : 指明一个image含 16 samples per pixel.
    VK_SAMPLE_COUNT_32_BIT  : 指明一个image含 32 samples per pixel.
    VK_SAMPLE_COUNT_64_BIT  : 指明一个image含 64 samples per pixel.  
    */


    //获取属性和limit
    VkPhysicalDeviceProperties2 physicalDeviceProperties2{};
    vkGetPhysicalDeviceProperties2(physicalDevice, &physicalDeviceProperties2);


    //VkPhysicalDevicePushDescriptorPropertiesKHR  ,可以包含在VkPhysicalDeviceProperties2.pNext中
    VkPhysicalDevicePushDescriptorPropertiesKHR physicalDevicePushDescriptorPropertiesKHR{};
    physicalDevicePushDescriptorPropertiesKHR.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PUSH_DESCRIPTOR_PROPERTIES_KHR;
    physicalDevicePushDescriptorPropertiesKHR.pNext = nullptr;
    physicalDevicePushDescriptorPropertiesKHR.maxPushDescriptors = 10;//指明以VK_DESCRIPTOR_SET_LAYOUT_CREATE_PUSH_DESCRIPTOR_BIT_KHR创建的descriptor set layout中可以使用的descriptors的最大数量


    //VkPhysicalDeviceMultiviewProperties  ，等价于VkPhysicalDeviceMultiviewPropertiesKHR,可以包含在VkPhysicalDeviceProperties2.pNext中
    VkPhysicalDeviceMultiviewProperties physicalDeviceMultiviewProperties{};
    physicalDeviceMultiviewProperties.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MULTIVIEW_PROPERTIES;
    physicalDeviceMultiviewProperties.pNext = nullptr;
    physicalDeviceMultiviewProperties.maxMultiviewViewCount = 10;//为比在subpass中可以使用的viewport索引的最大值大1的数
    physicalDeviceMultiviewProperties.maxMultiviewInstanceIndex = 10;//为一个在multiview render pass 实例中记录的绘制命令能生成的instance index的最大值


    //VkPhysicalDeviceFloatControlsProperties  ，等价于VkPhysicalDeviceFloatControlsPropertiesKHR,可以包含在VkPhysicalDeviceProperties2.pNext中
    VkPhysicalDeviceFloatControlsProperties physicalDeviceFloatControlsProperties{};
    physicalDeviceFloatControlsProperties.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FLOAT_CONTROLS_PROPERTIES_KHR;
    physicalDeviceFloatControlsProperties.pNext = nullptr;
    physicalDeviceFloatControlsProperties.denormBehaviorIndependence = VK_SHADER_FLOAT_CONTROLS_INDEPENDENCE_ALL;//一个 VkShaderFloatControlsIndependence 值，指明 denorm behavior能够或者如何是否对不同的bit宽度进行独立的设置
    /*
    VkShaderFloatControlsIndependence 等价于VkShaderFloatControlsIndependenceKHR:
    VK_SHADER_FLOAT_CONTROLS_INDEPENDENCE_32_BIT_ONLY : 指明shader float controls对32-bit浮点数的可以单独设置，其他浮点类型的bit宽度必须和其他的设置为相同的
    VK_SHADER_FLOAT_CONTROLS_INDEPENDENCE_ALL specifies : 指明shader float controls对所有bit宽度可以单独设置
    VK_SHADER_FLOAT_CONTROLS_INDEPENDENCE_NONE specifies : 指明shader float controls对所有bit宽度必须设置为相同的

    */
    physicalDeviceFloatControlsProperties.roundingModeIndependence = VK_SHADER_FLOAT_CONTROLS_INDEPENDENCE_ALL;//一个 VkShaderFloatControlsIndependence 值，指明rounding modes能够或者如何是否对不同的bit宽度进行独立的设置
    physicalDeviceFloatControlsProperties.shaderSignedZeroInfNanPreserveFloat16 = VK_FALSE;//指明符号0，NaN以及±∞是否在16-bit浮点计算中被保留，也指明是否SignedZeroInfNanPreserve execution mode可用于16-bit浮点类型
    physicalDeviceFloatControlsProperties.shaderSignedZeroInfNanPreserveFloat32 = VK_FALSE;//指明符号0，NaN以及±∞是否在32-bit浮点计算中被保留，也指明是否SignedZeroInfNanPreserve execution mode可用于32-bit浮点类型
    physicalDeviceFloatControlsProperties.shaderSignedZeroInfNanPreserveFloat64 = VK_FALSE;//指明符号0，NaN以及±∞是否在64-bit浮点计算中被保留，也指明是否SignedZeroInfNanPreserve execution mode可用于64-bit浮点类型
    physicalDeviceFloatControlsProperties.shaderDenormPreserveFloat16 = VK_FALSE;//指明denormals 非规格化数是否在16-bit浮点计算中被保留，也指明是否DenormPreserve execution mode可用于16-bit浮点类型
    physicalDeviceFloatControlsProperties.shaderDenormPreserveFloat32 = VK_FALSE;//指明denormals 非规格化数是否在32-bit浮点计算中被保留，也指明是否DenormPreserve execution mode可用于32-bit浮点类型
    physicalDeviceFloatControlsProperties.shaderDenormPreserveFloat64 = VK_FALSE;//指明denormals 非规格化数是否在64-bit浮点计算中被保留，也指明是否DenormPreserve execution mode可用于64-bit浮点类型
    physicalDeviceFloatControlsProperties.shaderDenormFlushToZeroFloat16 = VK_FALSE;//指明denormals 非规格化数是否在16-bit浮点计算中被刷新为0，也指明是否DenormFlushToZero execution mode可用于16-bit浮点类型
    physicalDeviceFloatControlsProperties.shaderDenormFlushToZeroFloat32 = VK_FALSE;//指明denormals 非规格化数是否在32-bit浮点计算中被刷新为0，也指明是否DenormFlushToZero execution mode可用于32-bit浮点类型
    physicalDeviceFloatControlsProperties.shaderDenormFlushToZeroFloat64 = VK_FALSE;//指明denormals 非规格化数是否在64-bit浮点计算中被刷新为0，也指明是否DenormFlushToZero execution mode可用于64-bit浮点类型
    physicalDeviceFloatControlsProperties.shaderRoundingModeRTEFloat16 = VK_FALSE;//指明是否在16-bit浮点算法和转换指令中支持round-to-nearest-even rounding mode，也指明是否RoundingModeRTE execution mode可用于16-bit浮点类型
    physicalDeviceFloatControlsProperties.shaderRoundingModeRTEFloat32 = VK_FALSE;//指明是否在32-bit浮点算法和转换指令中支持round-to-nearest-even rounding mode，也指明是否RoundingModeRTE execution mode可用于32-bit浮点类型
    physicalDeviceFloatControlsProperties.shaderRoundingModeRTEFloat64 = VK_FALSE;//指明是否在64-bit浮点算法和转换指令中支持round-to-nearest-even rounding mode，也指明是否RoundingModeRTE execution mode可用于64-bit浮点类型
    physicalDeviceFloatControlsProperties.shaderRoundingModeRTZFloat16 = VK_FALSE;//指明是否在16-bit浮点算法和转换指令中支持round-towards-zero rounding mode，也指明是否RoundingModeRTZ execution mode可用于16-bit浮点类型
    physicalDeviceFloatControlsProperties.shaderRoundingModeRTZFloat32 = VK_FALSE;//指明是否在32-bit浮点算法和转换指令中支持round-towards-zero rounding mode，也指明是否RoundingModeRTZ execution mode可用于32-bit浮点类型
    physicalDeviceFloatControlsProperties.shaderRoundingModeRTZFloat64 = VK_FALSE;//指明是否在64-bit浮点算法和转换指令中支持round-towards-zero rounding mode，也指明是否RoundingModeRTZ execution mode可用于64-bit浮点类型






}

void LimitsAndFormatsTest::FormatsTest()
{
}



NS_TEST_END