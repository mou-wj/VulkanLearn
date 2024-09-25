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



    //VkPhysicalDeviceDiscardRectanglePropertiesEXT ,可以包含在VkPhysicalDeviceProperties2.pNext中
    VkPhysicalDeviceDiscardRectanglePropertiesEXT physicalDeviceDiscardRectanglePropertiesEXT{};
    physicalDeviceDiscardRectanglePropertiesEXT.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DISCARD_RECTANGLE_PROPERTIES_EXT;
    physicalDeviceDiscardRectanglePropertiesEXT.pNext = nullptr;
    physicalDeviceDiscardRectanglePropertiesEXT.maxDiscardRectangles = 10;//为可以指定的active discard rectangles的最大数量


    //VkPhysicalDeviceSampleLocationsPropertiesEXT ,可以包含在VkPhysicalDeviceProperties2.pNext中
    VkPhysicalDeviceSampleLocationsPropertiesEXT physicalDeviceSampleLocationsPropertiesEXT{};
    physicalDeviceSampleLocationsPropertiesEXT.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SAMPLE_LOCATIONS_PROPERTIES_EXT;
    physicalDeviceSampleLocationsPropertiesEXT.pNext = nullptr;
    physicalDeviceSampleLocationsPropertiesEXT.sampleLocationSampleCounts;//为 VkSampleCountFlagBits 组合值位掩码，指明sample count支持自定义采样点位置
    physicalDeviceSampleLocationsPropertiesEXT.maxSampleLocationGridSize;//为 sampleLocationSampleCounts 中支持的所有采样点可以有不同位置的 pixel grid 的最大大小
    physicalDeviceSampleLocationsPropertiesEXT.sampleLocationCoordinateRange[2];//为支持的sample location coordinates的范围
	physicalDeviceSampleLocationsPropertiesEXT.sampleLocationSubPixelBits;//sample locations的subpixel精度的bit数
	physicalDeviceSampleLocationsPropertiesEXT.variableSampleLocations;//指定用于所有pipeline的且绑定到command buffer中subpass中的sample locations必须匹配，如果为VK_TRUE，则允许不同subpass的sample locations不同，否则必须相同


    //VkPhysicalDeviceLegacyVertexAttributesPropertiesEXT ,可以包含在VkPhysicalDeviceProperties2.pNext中
    VkPhysicalDeviceLegacyVertexAttributesPropertiesEXT physicalDeviceLegacyVertexAttributesPropertiesEXT{};
    physicalDeviceLegacyVertexAttributesPropertiesEXT.sType = VK_STRUCTURE_TYPE_MAX_ENUM;//没有定义这里定义为非法值
    physicalDeviceLegacyVertexAttributesPropertiesEXT.pNext = nullptr;
    physicalDeviceLegacyVertexAttributesPropertiesEXT.nativeUnalignedPerformance = VK_FALSE;//指定相比于 aligned fetches，unaligned vertex fetches 不会造成明显的显示问题


    //VkPhysicalDeviceExternalMemoryHostPropertiesEXT ,可以包含在VkPhysicalDeviceProperties2.pNext中
    VkPhysicalDeviceExternalMemoryHostPropertiesEXT physicalDeviceExternalMemoryHostPropertiesEXT{};
    physicalDeviceExternalMemoryHostPropertiesEXT.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_EXTERNAL_MEMORY_HOST_PROPERTIES_EXT;
    physicalDeviceExternalMemoryHostPropertiesEXT.pNext = nullptr;
	physicalDeviceExternalMemoryHostPropertiesEXT.minImportedHostPointerAlignment = VK_FALSE;//指明可以导入到vulkan 对象的host指针的基地址以及大小的字节对齐要求，必须是2的指数


    //VkPhysicalDeviceMultiviewPerViewAttributesPropertiesNVX ,可以包含在VkPhysicalDeviceProperties2.pNext中
    VkPhysicalDeviceMultiviewPerViewAttributesPropertiesNVX physicalDeviceMultiviewPerViewAttributesPropertiesNVX{};
    physicalDeviceMultiviewPerViewAttributesPropertiesNVX.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MULTIVIEW_PER_VIEW_ATTRIBUTES_PROPERTIES_NVX;
    physicalDeviceMultiviewPerViewAttributesPropertiesNVX.pNext = nullptr;
    physicalDeviceMultiviewPerViewAttributesPropertiesNVX.perViewPositionAllComponents = VK_FALSE;//指明是否支持 per-view的位置的其他分量可以和X分量不同


    //VkPhysicalDevicePointClippingProperties，等同于 VkPhysicalDevicePointClippingPropertiesKHR ,可以包含在VkPhysicalDeviceProperties2.pNext中
    VkPhysicalDevicePointClippingProperties physicalDevicePointClippingProperties{};
    physicalDevicePointClippingProperties.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_POINT_CLIPPING_PROPERTIES;
    physicalDevicePointClippingProperties.pNext = nullptr;
	physicalDevicePointClippingProperties.pointClippingBehavior;//一个VkPointClippingBehavior 值指明支持的point clipping behavior


    //VkPhysicalDeviceSubgroupProperties  ,可以包含在VkPhysicalDeviceProperties2.pNext中
    VkPhysicalDeviceSubgroupProperties physicalDeviceSubgroupProperties{};
    physicalDeviceSubgroupProperties.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SUBGROUP_PROPERTIES;
    physicalDeviceSubgroupProperties.pNext = nullptr;
    physicalDeviceSubgroupProperties.subgroupSize;//为每个subgroup的默认调用次数，其他详细信息见p3930
	physicalDeviceSubgroupProperties.supportedStages;//为 VkShaderStageFlagBits 组合值，描述支持subgroup scope的group operations的shader stages，其他详细信息见p3930
	physicalDeviceSubgroupProperties.supportedOperations;//为 VkSubgroupFeatureFlagBits 组合值，描述device支持subgroup scope的subgroup operations 集合，其他详细信息见p3930
    /*
    VkSubgroupFeatureFlagBits:
    VK_SUBGROUP_FEATURE_BASIC_BIT : 指明device将接受包含GroupNonUniform的SPIR-V shader modules。
    VK_SUBGROUP_FEATURE_VOTE_BIT : 指明device将接受包含GroupNonUniformVote的SPIR-V shader modules。
    VK_SUBGROUP_FEATURE_ARITHMETIC_BIT : 指明device将接受包含GroupNonUniformArithmetic的SPIR-V shader modules。
    VK_SUBGROUP_FEATURE_BALLOT_BIT specifies : 指明device将接受包含GroupNonUniformBallot的SPIR-V shader modules。
    VK_SUBGROUP_FEATURE_SHUFFLE_BIT : 指明device将接受包含GroupNonUniformShuffle的SPIR-V shader modules。
    VK_SUBGROUP_FEATURE_SHUFFLE_RELATIVE_BIT : 指明device将接受包含GroupNonUniformShuffleRelative的SPIR-V shader modules。
    VK_SUBGROUP_FEATURE_CLUSTERED_BIT : 指明device将接受包含GroupNonUniformClustered的SPIR-V shader modules。
    VK_SUBGROUP_FEATURE_QUAD_BIT : 指明device将接受包含GroupNonUniformQuad的SPIR-V shader modules。
    VK_SUBGROUP_FEATURE_PARTITIONED_BIT_NV : 指明device将接受包含GroupNonUniformPartitionedNV的SPIR-V shader modules。
    VK_SUBGROUP_FEATURE_ROTATE_BIT_KHR : 指明device将接受包含GroupNonUniformRotateKHR的SPIR-V shader modules。
    VK_SUBGROUP_FEATURE_ROTATE_CLUSTERED_BIT_KHR : 指明device将接受使用OpGroupNonUniformRotateKHR的ClusterSize操作符的SPIR-V shader modules。    
    
    */
    physicalDeviceSubgroupProperties.quadOperationsInAllStages;//指明是否所有stages支持 quad group operations，或者只是限制到fragment 以及 compute stages.



    //VkPhysicalDeviceSubgroupSizeControlProperties  ，等价于VkPhysicalDeviceSubgroupSizeControlPropertiesEXT ，可以包含在VkPhysicalDeviceProperties2.pNext中
    VkPhysicalDeviceSubgroupSizeControlProperties physicalDeviceSubgroupSizeControlProperties{};
    physicalDeviceSubgroupSizeControlProperties.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SUBGROUP_PROPERTIES;
    physicalDeviceSubgroupSizeControlProperties.pNext = nullptr;
    physicalDeviceSubgroupSizeControlProperties.minSubgroupSize;//为device支持的最小的subgroup 大小，为2的指数，其他详细信息见p3932
    physicalDeviceSubgroupSizeControlProperties.maxSubgroupSize;//为device支持的最大的subgroup 大小，为2的指数，其他详细信息见p3932
    physicalDeviceSubgroupSizeControlProperties.maxComputeWorkgroupSubgroups;//为workgroup中支持的subgroup 的最大数量
    physicalDeviceSubgroupSizeControlProperties.requiredSubgroupSizeStages;//VkShaderStageFlags值，为需要指定subgroup大小的一组shader stage组合


    //VkPhysicalDeviceBlendOperationAdvancedPropertiesEXT ，可以包含在VkPhysicalDeviceProperties2.pNext中
    VkPhysicalDeviceBlendOperationAdvancedPropertiesEXT physicalDeviceBlendOperationAdvancedPropertiesEXT{};
    physicalDeviceBlendOperationAdvancedPropertiesEXT.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_BLEND_OPERATION_ADVANCED_PROPERTIES_EXT;
    physicalDeviceBlendOperationAdvancedPropertiesEXT.pNext = nullptr;
    physicalDeviceBlendOperationAdvancedPropertiesEXT.advancedBlendMaxColorAttachments;//对于使用 advanced blend operation的pipeline，该值为subpass中可以使用的color attachment索引的最大值加1
    physicalDeviceBlendOperationAdvancedPropertiesEXT.advancedBlendIndependentBlend;//指明每个atttachment的advanced blend operations是否可以不同
    physicalDeviceBlendOperationAdvancedPropertiesEXT.advancedBlendNonPremultipliedSrcColor;//指明是否source color 可以认作是non-premultiplied的，如果为VK_FALSE，则 VkPipelineColorBlendAdvancedStateCreateInfoEXT::srcPremultiplied 必须为VK_TRUE
    physicalDeviceBlendOperationAdvancedPropertiesEXT.advancedBlendNonPremultipliedDstColor;//指明是否destination color 可以认作是non-premultiplied的，如果为VK_FALSE，则 VkPipelineColorBlendAdvancedStateCreateInfoEXT::dstPremultiplied 必须为VK_TRUE
    physicalDeviceBlendOperationAdvancedPropertiesEXT.advancedBlendCorrelatedOverlap;//指明是否overlap mode 可以认作是相关的，如果为VK_FALSE，则 VkPipelineColorBlendAdvancedStateCreateInfoEXT::blendOverlap 必须为VK_BLEND_OVERLAP_UNCORRELATED_EXT
    physicalDeviceBlendOperationAdvancedPropertiesEXT.advancedBlendAllOperations;//指明是否支持所有的advanced blend operation枚举值


    //VkPhysicalDeviceVertexAttributeDivisorPropertiesEXT ，可以包含在VkPhysicalDeviceProperties2.pNext中
    VkPhysicalDeviceVertexAttributeDivisorPropertiesEXT physicalDeviceVertexAttributeDivisorPropertiesEXT{};
    physicalDeviceVertexAttributeDivisorPropertiesEXT.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VERTEX_ATTRIBUTE_DIVISOR_PROPERTIES_EXT;
    physicalDeviceVertexAttributeDivisorPropertiesEXT.pNext = nullptr;
    physicalDeviceVertexAttributeDivisorPropertiesEXT.maxVertexAttribDivisor;//为当 instanced rendering 开启时，能够重复vertex attribute data的instances的最大数量


    //VkPhysicalDeviceVertexAttributeDivisorPropertiesKHR ，可以包含在VkPhysicalDeviceProperties2.pNext中
    VkPhysicalDeviceVertexAttributeDivisorPropertiesKHR physicalDeviceVertexAttributeDivisorPropertiesKHR{};
    physicalDeviceVertexAttributeDivisorPropertiesKHR.sType = VK_STRUCTURE_TYPE_MAX_ENUM;//没有定义这里定义为非法值
    physicalDeviceVertexAttributeDivisorPropertiesKHR.pNext = nullptr;
    physicalDeviceVertexAttributeDivisorPropertiesKHR.maxVertexAttribDivisor;//为当 instanced rendering 开启时，能够重复vertex attribute data的instances的最大数量
    physicalDeviceVertexAttributeDivisorPropertiesKHR.supportsNonZeroFirstInstance;//指明是否支持当VkVertexInputBindingDivisorDescriptionKHR::divisor 不为1 时drawing commands的firstInstance 参数是否可以为 非0值


    //VkPhysicalDeviceSamplerFilterMinmaxProperties ，等价于VkPhysicalDeviceSamplerFilterMinmaxPropertiesEXT ，可以包含在VkPhysicalDeviceProperties2.pNext中
    VkPhysicalDeviceSamplerFilterMinmaxProperties physicalDeviceSamplerFilterMinmaxProperties{};
    physicalDeviceSamplerFilterMinmaxProperties.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SAMPLER_FILTER_MINMAX_PROPERTIES;
    physicalDeviceSamplerFilterMinmaxProperties.pNext = nullptr;
    physicalDeviceSamplerFilterMinmaxProperties.filterMinmaxSingleComponentFormats;//指明是否最小的format集合支持min/max filtering，详细信息见p3936
    physicalDeviceSamplerFilterMinmaxProperties.filterMinmaxImageComponentMapping;//指明是否支持当进行min/max filtering 的时候可以对image做non-identity component mapping


    //VkPhysicalDeviceProtectedMemoryProperties ，等价于VkPhysicalDeviceSamplerFilterMinmaxPropertiesEXT ，可以包含在VkPhysicalDeviceProperties2.pNext中
    VkPhysicalDeviceProtectedMemoryProperties physicalDeviceProtectedMemoryProperties{};
    physicalDeviceProtectedMemoryProperties.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PROTECTED_MEMORY_FEATURES;
    physicalDeviceProtectedMemoryProperties.pNext = nullptr;
    physicalDeviceProtectedMemoryProperties.protectedNoFault;//指定当应用程序尝试在受保护的队列操作中写入未受保护的内存，从 protected memory 读取unprotected queue 操作，或在 protected queue 操作中执行查询。如果此限制VK_TRUE，则此类写入将被丢弃或写入、读取和查询的未定义值将返回 undefined 值。如果此限制VK_FALSE，则应用程序不得执行这些操作


    //VkPhysicalDeviceMaintenance3Properties ，等价于VkPhysicalDeviceMaintenance3PropertiesKHR ，可以包含在VkPhysicalDeviceProperties2.pNext中
    VkPhysicalDeviceMaintenance3Properties physicalDeviceMaintenance3Properties{};
    physicalDeviceMaintenance3Properties.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MAINTENANCE_3_PROPERTIES;
    physicalDeviceMaintenance3Properties.pNext = nullptr;
    physicalDeviceMaintenance3Properties.maxPerSetDescriptors;//为一个descriptor set中所有类型descriptors的总和的最大数量
    physicalDeviceMaintenance3Properties.maxMemoryAllocationSize;//为可以创建的memory allocation的最大大小


    //VkPhysicalDeviceMaintenance4Properties ，等价于VkPhysicalDeviceMaintenance4PropertiesKHR ，可以包含在VkPhysicalDeviceProperties2.pNext中
    VkPhysicalDeviceMaintenance4Properties physicalDeviceMaintenance4Properties{};
    physicalDeviceMaintenance4Properties.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MAINTENANCE_4_PROPERTIES;
    physicalDeviceMaintenance4Properties.pNext = nullptr;
    physicalDeviceMaintenance4Properties.maxBufferSize;//为可以创建的VkBuffer的最大大小


    //VkPhysicalDeviceMaintenance5PropertiesKHR  ，可以包含在VkPhysicalDeviceProperties2.pNext中
    VkPhysicalDeviceMaintenance5PropertiesKHR physicalDeviceMaintenance5PropertiesKHR{};
    physicalDeviceMaintenance5PropertiesKHR.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MAINTENANCE_5_PROPERTIES_KHR;
    physicalDeviceMaintenance5PropertiesKHR.pNext = nullptr;
    physicalDeviceMaintenance5PropertiesKHR.earlyFragmentMultisampleCoverageAfterSampleCounting;//指明fragment shading 以及 multisample coverage operations 是否在有EarlyFragmentTests execution mode的fragment shaders的 sample counting 之后执行
    physicalDeviceMaintenance5PropertiesKHR.earlyFragmentSampleMaskTestBeforeSampleCounting;//指明sample mask test operation 是否在有EarlyFragmentTests execution mode的fragment shaders的 sample counting 之前执行
    physicalDeviceMaintenance5PropertiesKHR.depthStencilSwizzleOneSupport;//指明有VK_COMPONENT_SWIZZLE_ONE 的depth/stencil texturing operations是否有定义行为
    physicalDeviceMaintenance5PropertiesKHR.polygonModePointSize;//指明有VK_POLYGON_MODE_POINT的poligons的光栅化的point size是否由 PointSize 控制
    physicalDeviceMaintenance5PropertiesKHR.nonStrictSinglePixelWideLinesUseParallelogram;//指明线宽为1.0的 non-strict line 是否使用Bresenham 算法以平行四边形的方式进行光栅化
    physicalDeviceMaintenance5PropertiesKHR.nonStrictWideLinesUseParallelogram;//指明线宽大于1.0的 non-strict line 是否使用Bresenham 算法以平行四边形的方式进行光栅化


    //VkPhysicalDeviceMaintenance6PropertiesKHR  ，可以包含在VkPhysicalDeviceProperties2.pNext中
    VkPhysicalDeviceMaintenance6PropertiesKHR physicalDeviceMaintenance6PropertiesKHR{};
    physicalDeviceMaintenance6PropertiesKHR.sType = VK_STRUCTURE_TYPE_MAX_ENUM;//没有定义这里定义为非法值
    physicalDeviceMaintenance6PropertiesKHR.pNext = nullptr;
    physicalDeviceMaintenance6PropertiesKHR.blockTexelViewCompatibleMultipleLayers;//指明是否支持创建一个含 VK_IMAGE_CREATE_BLOCK_TEXEL_VIEW_COMPATIBLE_BIT 且subresourceRange的layerCount大于1的image view
    physicalDeviceMaintenance6PropertiesKHR.maxCombinedImageSamplerDescriptorCount;//指明支持可以用来访问任何需要一个Y′CBCR conversion 的格式的combined image sampler的最大数量
    physicalDeviceMaintenance6PropertiesKHR.fragmentShadingRateClampCombinerInputs;//指明是否限制输入为 combiner operations 见p2696


    //VkPhysicalDeviceMeshShaderPropertiesNV  ，可以包含在VkPhysicalDeviceProperties2.pNext中
    VkPhysicalDeviceMeshShaderPropertiesNV physicalDeviceMeshShaderPropertiesNV{};
    physicalDeviceMeshShaderPropertiesNV.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MESH_SHADER_PROPERTIES_NV;
    physicalDeviceMeshShaderPropertiesNV.pNext = nullptr;
    physicalDeviceMeshShaderPropertiesNV.maxDrawMeshTasksCount;//为可以被一个draw mesh tasks command 触发的local workgroups 的最大数量
    physicalDeviceMeshShaderPropertiesNV.maxTaskWorkGroupInvocations;//为一个local workgroup 可以触发的task shader调用的最大总数，其他详细信息见p3941
    physicalDeviceMeshShaderPropertiesNV.maxTaskWorkGroupSize[3];//为 local task workgroup的维度的最大大小，分别对于X，Y，Z维度，其他详细信息见p3941
    physicalDeviceMeshShaderPropertiesNV.maxTaskTotalMemorySize;//为task shader 可用于shared 以及output memory绑定的最大字节大小
    physicalDeviceMeshShaderPropertiesNV.maxTaskOutputCount;//为一个task shader workgroup 可以发射的output tasks的最大数量
    physicalDeviceMeshShaderPropertiesNV.maxMeshWorkGroupInvocations;//为一个local workgroup 可以触发的mesh shader调用的最大总数，其他详细信息见p3941
    physicalDeviceMeshShaderPropertiesNV.maxMeshWorkGroupSize[3];//为 local mesh workgroup的维度的最大大小，分别对于X，Y，Z维度，其他详细信息见p3941
    physicalDeviceMeshShaderPropertiesNV.maxMeshTotalMemorySize;//为mesh shader 可用于shared 以及output memory绑定的最大字节大小
    physicalDeviceMeshShaderPropertiesNV.maxMeshOutputVertices;//为mesh shader 输出可以存储的顶点的最大数量
    physicalDeviceMeshShaderPropertiesNV.maxMeshOutputPrimitives;//为mesh shader 输出可以存储的图元的最大数量
    physicalDeviceMeshShaderPropertiesNV.maxMeshMultiviewViewCount;//为mesh shader 可以使用的multiview views的最大数量
    physicalDeviceMeshShaderPropertiesNV.meshOutputPerVertexGranularity;//为mesh vertex outputs分配的粒度，可用于mesh shader计算使用的内存空间，小于maxMeshTotalMemorySize
    physicalDeviceMeshShaderPropertiesNV.meshOutputPerPrimitiveGranularity;//为per-primitive mesh outputs分配的粒度，可用于mesh shader计算使用的内存空间，小于maxMeshTotalMemorySize


    //VkPhysicalDeviceMeshShaderPropertiesNV  ，可以包含在VkPhysicalDeviceProperties2.pNext中
    VkPhysicalDeviceMeshShaderPropertiesEXT physicalDeviceMeshShaderPropertiesEXT{};
    physicalDeviceMeshShaderPropertiesEXT.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MESH_SHADER_PROPERTIES_EXT;
    physicalDeviceMeshShaderPropertiesEXT.pNext = nullptr;
    physicalDeviceMeshShaderPropertiesEXT.maxTaskWorkGroupTotalCount;//为可以被一个mesh draw tasks command 触发的local workgroups 总数的最大数量
    physicalDeviceMeshShaderPropertiesEXT.maxTaskWorkGroupCount[3];//为可以被一个mesh draw tasks command 触发的local workgroups 的最大数量，分别对于维度X，Y，Z，其他详细信息见p3943
    physicalDeviceMeshShaderPropertiesEXT.maxTaskWorkGroupInvocations;//为一个local workgroup 可以触发的task shader调用的最大总数，其他详细信息见p3943
    physicalDeviceMeshShaderPropertiesEXT.maxTaskWorkGroupSize[3];//为 local task workgroup的维度的最大大小，分别对于X，Y，Z维度，其他详细信息见p3943
    physicalDeviceMeshShaderPropertiesEXT.maxTaskPayloadSize;//为task shader stage中shader module中以 TaskPayloadWorkgroupEXT storage class声明的变量可用的总的最大存储字节空间
    physicalDeviceMeshShaderPropertiesEXT.maxTaskSharedMemorySize;//为task shader stage中shader module中以 Workgroup storage class声明的变量可用的总的最大存储字节空间
    physicalDeviceMeshShaderPropertiesEXT.maxTaskPayloadAndSharedMemorySize;//为task shader stage中shader module中以TaskPayloadWorkgroupEXT 或者 Workgroup storage class声明的变量可用的总的最大存储字节空间
    physicalDeviceMeshShaderPropertiesEXT.maxMeshWorkGroupTotalCount;//为一个task shader workgroup 可以发射的 local output tasks的最大数量
    physicalDeviceMeshShaderPropertiesEXT.maxMeshWorkGroupCount[3];//为一个task shader workgroup 可以发射的 local output tasks每个维度的最大数量，其他详细信息见p3944
    physicalDeviceMeshShaderPropertiesEXT.maxMeshWorkGroupInvocations;//为一个local workgroup 可以触发的mesh shader调用的最大总数，其他详细信息见p3944
    physicalDeviceMeshShaderPropertiesEXT.maxMeshWorkGroupSize[3];//为 local mesh workgroup的维度的最大大小，分别对于X，Y，Z维度，其他详细信息见p3944
    physicalDeviceMeshShaderPropertiesEXT.maxMeshSharedMemorySize;//为mesh shader stage中shader module中以 Workgroup storage class声明的变量可用的总的最大存储字节空间
    physicalDeviceMeshShaderPropertiesEXT.maxMeshPayloadAndSharedMemorySize;//为mesh shader stage中shader module中以TaskPayloadWorkgroupEXT 或者 Workgroup storage class声明的变量可用的总的最大存储字节空间
    physicalDeviceMeshShaderPropertiesEXT.maxMeshOutputMemorySize;//为mesh shader stage中shader module中输出变量可用的总的最大存储字节空间
    physicalDeviceMeshShaderPropertiesEXT.maxMeshPayloadAndOutputMemorySize;//为mesh shader stage中shader module中以 TaskPayloadWorkgroupEXT storage class声明的变量或者输出变量可用的总的最大存储字节空间
    physicalDeviceMeshShaderPropertiesEXT.maxMeshOutputComponents;//为mesh shader stage 中输出变量的最大分量数
    physicalDeviceMeshShaderPropertiesEXT.maxMeshOutputVertices;//为一个mesh shader workgroup 可以发射的顶点的最大数量
    physicalDeviceMeshShaderPropertiesEXT.maxMeshOutputPrimitives;//为一个mesh shader workgroup 可以发射的图元的最大数量
    physicalDeviceMeshShaderPropertiesEXT.maxMeshOutputLayers;//为一个mesh shader workgroup 可以输出的layer索引的最大值加1
    physicalDeviceMeshShaderPropertiesEXT.maxMeshMultiviewViewCount;//为mesh shader 可以使用的 view的索引的最大值加1
    physicalDeviceMeshShaderPropertiesEXT.meshOutputPerVertexGranularity;//为顶点分配的粒度，小于等于maxMeshOutputMemorySize，其他具体信息见p3945
    physicalDeviceMeshShaderPropertiesEXT.meshOutputPerPrimitiveGranularity;//为图元分配的粒度小于等于maxMeshOutputMemorySize，其他具体信息见p3945
    physicalDeviceMeshShaderPropertiesEXT.maxPreferredTaskWorkGroupInvocations;//为最佳性能下首选的一个workgroup中含有的的task shader invocations数量
    physicalDeviceMeshShaderPropertiesEXT.maxPreferredMeshWorkGroupInvocations;//为最佳性能下首选的一个workgroup中含有的的mesh shader invocations数量
    physicalDeviceMeshShaderPropertiesEXT.prefersLocalInvocationVertexOutput;//指明当array 索引匹配LocalInvocationIndex时在mesh shader中向vertex output array写入数据是否有最佳性能
    physicalDeviceMeshShaderPropertiesEXT.prefersLocalInvocationPrimitiveOutput;//指明当array 索引匹配LocalInvocationIndex时在mesh shader中向primitive output array写入数据是否有最佳性能
    physicalDeviceMeshShaderPropertiesEXT.prefersCompactVertexOutput;//指明是否应该在mesh shader的自定义culling后紧凑顶点输出以为了更好的性能表现，否则保持顶点原来的位置可能更好
    physicalDeviceMeshShaderPropertiesEXT.prefersCompactPrimitiveOutput;//指明是否应该在mesh shader的自定义culling后紧凑图元输出以为了更好的性能表现，否则使用CullPrimitiveEXT可能更好


    //VkPhysicalDeviceDescriptorIndexingProperties ，等价于VkPhysicalDeviceDescriptorIndexingPropertiesEXT ，可以包含在VkPhysicalDeviceProperties2.pNext中
    VkPhysicalDeviceDescriptorIndexingProperties physicalDeviceDescriptorIndexingProperties{};
    physicalDeviceDescriptorIndexingProperties.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DESCRIPTOR_INDEXING_PROPERTIES;
    physicalDeviceDescriptorIndexingProperties.pNext = nullptr;
    physicalDeviceDescriptorIndexingProperties.maxUpdateAfterBindDescriptorsInAllPools;//指明所有含VK_DESCRIPTOR_POOL_CREATE_UPDATE_AFTER_BIND_BIT创建的descriptor pool中所能包含的所有类型的descriptors总数的最大数量
    physicalDeviceDescriptorIndexingProperties.shaderUniformBufferArrayNonUniformIndexingNative;//指明是否uniform buffer descriptors 支持nonuniform indexing，其他详细信息见p3947
    physicalDeviceDescriptorIndexingProperties.shaderSampledImageArrayNonUniformIndexingNative;//指明是否sampler 以及 image descriptors 支持nonuniform indexing，其他详细信息见p3947
    physicalDeviceDescriptorIndexingProperties.shaderStorageBufferArrayNonUniformIndexingNative;//指明是否storage buffer descriptors 支持nonuniform indexing，其他详细信息见p3947
    physicalDeviceDescriptorIndexingProperties.shaderStorageImageArrayNonUniformIndexingNative;//指明是否storage image descriptors 支持nonuniform indexing，其他详细信息见p3947
    physicalDeviceDescriptorIndexingProperties.shaderInputAttachmentArrayNonUniformIndexingNative;//指明是否input attachment descriptors 支持nonuniform indexing，其他详细信息见p3947
    physicalDeviceDescriptorIndexingProperties.robustBufferAccessUpdateAfterBind;//指明是否 robustBufferAccess可以和 descriptorBindingUniformBufferUpdateAfterBind, descriptorBindingStorageBufferUpdateAfterBind, descriptorBindingUniformTexelBufferUpdateAfterBind, 以及 / 或者 descriptorBindingStorageTexelBufferUpdateAfterBind 同时开启
    physicalDeviceDescriptorIndexingProperties.quadDivergentImplicitLod;//当用于指令的image 以及/或者 sampler对象在quad内不一致时，用于图像操作的隐式LOD计算是否有明确定义的结果
    physicalDeviceDescriptorIndexingProperties.maxPerStageDescriptorUpdateAfterBindSamplers;//类似于maxPerStageDescriptorSamplers，只不过descriptors的统计从以创建含有或者不含有VK_DESCRIPTOR_SET_LAYOUT_CREATE_UPDATE_AFTER_BIND_POOL_BIT 的descriptor sets中统计
    physicalDeviceDescriptorIndexingProperties.maxPerStageDescriptorUpdateAfterBindUniformBuffers;//类似于maxPerStageDescriptorUniformBuffers，只不过descriptors的统计从以创建含有或者不含有VK_DESCRIPTOR_SET_LAYOUT_CREATE_UPDATE_AFTER_BIND_POOL_BIT 的descriptor sets中统计
    physicalDeviceDescriptorIndexingProperties.maxPerStageDescriptorUpdateAfterBindStorageBuffers;//类似于maxPerStageDescriptorStorageBuffers，只不过descriptors的统计从以创建含有或者不含有VK_DESCRIPTOR_SET_LAYOUT_CREATE_UPDATE_AFTER_BIND_POOL_BIT 的descriptor sets中统计
    physicalDeviceDescriptorIndexingProperties.maxPerStageDescriptorUpdateAfterBindSampledImages;//类似于maxPerStageDescriptorSampledImages，只不过descriptors的统计从以创建含有或者不含有VK_DESCRIPTOR_SET_LAYOUT_CREATE_UPDATE_AFTER_BIND_POOL_BIT 的descriptor sets中统计
    physicalDeviceDescriptorIndexingProperties.maxPerStageDescriptorUpdateAfterBindStorageImages;//类似于maxPerStageDescriptorStorageImages，只不过descriptors的统计从以创建含有或者不含有VK_DESCRIPTOR_SET_LAYOUT_CREATE_UPDATE_AFTER_BIND_POOL_BIT 的descriptor sets中统计
    physicalDeviceDescriptorIndexingProperties.maxPerStageDescriptorUpdateAfterBindInputAttachments;//类似于maxPerStageDescriptorInputAttachments，只不过descriptors的统计从以创建含有或者不含有VK_DESCRIPTOR_SET_LAYOUT_CREATE_UPDATE_AFTER_BIND_POOL_BIT 的descriptor sets中统计
    physicalDeviceDescriptorIndexingProperties.maxPerStageUpdateAfterBindResources;//类似于maxPerStageResources，只不过descriptors的统计从以创建含有或者不含有VK_DESCRIPTOR_SET_LAYOUT_CREATE_UPDATE_AFTER_BIND_POOL_BIT 的descriptor sets中统计
    physicalDeviceDescriptorIndexingProperties.maxDescriptorSetUpdateAfterBindSamplers;//类似于maxDescriptorSetSamplers，只不过descriptors的统计从以创建含有或者不含有VK_DESCRIPTOR_SET_LAYOUT_CREATE_UPDATE_AFTER_BIND_POOL_BIT 的descriptor sets中统计
    physicalDeviceDescriptorIndexingProperties.maxDescriptorSetUpdateAfterBindUniformBuffers;//类似于maxDescriptorSetUniformBuffers，只不过descriptors的统计从以创建含有或者不含有VK_DESCRIPTOR_SET_LAYOUT_CREATE_UPDATE_AFTER_BIND_POOL_BIT 的descriptor sets中统计
    physicalDeviceDescriptorIndexingProperties.maxDescriptorSetUpdateAfterBindUniformBuffersDynamic;//类似于maxDescriptorSetUniformBuffersDynamic，只不过descriptors的统计从以创建含有或者不含有VK_DESCRIPTOR_SET_LAYOUT_CREATE_UPDATE_AFTER_BIND_POOL_BIT 的descriptor sets中统计,其他信息见p3948
    physicalDeviceDescriptorIndexingProperties.maxDescriptorSetUpdateAfterBindStorageBuffers;//类似于maxDescriptorSetStorageBuffers，只不过descriptors的统计从以创建含有或者不含有VK_DESCRIPTOR_SET_LAYOUT_CREATE_UPDATE_AFTER_BIND_POOL_BIT 的descriptor sets中统计
    physicalDeviceDescriptorIndexingProperties.maxDescriptorSetUpdateAfterBindStorageBuffersDynamic;//类似于maxDescriptorSetStorageBuffersDynamic，只不过descriptors的统计从以创建含有或者不含有VK_DESCRIPTOR_SET_LAYOUT_CREATE_UPDATE_AFTER_BIND_POOL_BIT 的descriptor sets中统计,其他信息见p3948
    physicalDeviceDescriptorIndexingProperties.maxDescriptorSetUpdateAfterBindSampledImages;//类似于maxDescriptorSetSampledImages，只不过descriptors的统计从以创建含有或者不含有VK_DESCRIPTOR_SET_LAYOUT_CREATE_UPDATE_AFTER_BIND_POOL_BIT 的descriptor sets中统计
    physicalDeviceDescriptorIndexingProperties.maxDescriptorSetUpdateAfterBindStorageImages;//类似于maxDescriptorSetStorageImages，只不过descriptors的统计从以创建含有或者不含有VK_DESCRIPTOR_SET_LAYOUT_CREATE_UPDATE_AFTER_BIND_POOL_BIT 的descriptor sets中统计
    physicalDeviceDescriptorIndexingProperties.maxDescriptorSetUpdateAfterBindInputAttachments;//类似于maxDescriptorSetInputAttachments，只不过descriptors的统计从以创建含有或者不含有VK_DESCRIPTOR_SET_LAYOUT_CREATE_UPDATE_AFTER_BIND_POOL_BIT 的descriptor sets中统计


    //VkPhysicalDeviceInlineUniformBlockProperties ，等价于VkPhysicalDeviceInlineUniformBlockPropertiesEXT ，可以包含在VkPhysicalDeviceProperties2.pNext中
    VkPhysicalDeviceInlineUniformBlockProperties physicalDeviceInlineUniformBlockProperties{};
    physicalDeviceInlineUniformBlockProperties.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_INLINE_UNIFORM_BLOCK_PROPERTIES;
    physicalDeviceInlineUniformBlockProperties.pNext = nullptr;
    physicalDeviceInlineUniformBlockProperties.maxInlineUniformBlockSize;//一个 inline uniform block 绑定的最大字节数
    physicalDeviceInlineUniformBlockProperties.maxPerStageDescriptorInlineUniformBlocks;//为一个pipeline layout中一个shader stage可以访问的 inline uniform block 绑定的最大字节数，其他描述见p3949
    physicalDeviceInlineUniformBlockProperties.maxPerStageDescriptorUpdateAfterBindInlineUniformBlocks;//类似于maxPerStageDescriptorInlineUniformBlocks，只不过descriptors的统计从以创建含有或者不含有VK_DESCRIPTOR_SET_LAYOUT_CREATE_UPDATE_AFTER_BIND_POOL_BIT 的descriptor sets中统计
    physicalDeviceInlineUniformBlockProperties.maxDescriptorSetInlineUniformBlocks;//在跨所有管道着色器阶段和描述符集编号的管道布局中，可以包含在描述符绑定中的inline uniform block bindings的最大数量，其他描述见p3949
    physicalDeviceInlineUniformBlockProperties.maxDescriptorSetUpdateAfterBindInlineUniformBlocks;//类似于maxDescriptorSetInlineUniformBlocks，只不过descriptors的统计从以创建含有或者不含有VK_DESCRIPTOR_SET_LAYOUT_CREATE_UPDATE_AFTER_BIND_POOL_BIT 的descriptor sets中统计


    //VkPhysicalDeviceConservativeRasterizationPropertiesEXT  ，可以包含在VkPhysicalDeviceProperties2.pNext中
    VkPhysicalDeviceConservativeRasterizationPropertiesEXT physicalDeviceConservativeRasterizationPropertiesEXT{};
    physicalDeviceConservativeRasterizationPropertiesEXT.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_CONSERVATIVE_RASTERIZATION_PROPERTIES_EXT;
    physicalDeviceConservativeRasterizationPropertiesEXT.pNext = nullptr;
    physicalDeviceConservativeRasterizationPropertiesEXT.primitiveOverestimationSize;//在conservative rasterization overestimation mode中生成的图元的边界的pixels的大小是否增加了，其它描述见p3950
    physicalDeviceConservativeRasterizationPropertiesEXT.maxExtraPrimitiveOverestimationSize;//为pipeline state中支持的extra overestimation的pixels的最大大小
    physicalDeviceConservativeRasterizationPropertiesEXT.extraPrimitiveOverestimationSizeGranularity;//为pipeline state中可以指定在0.0 到 maxExtraPrimitiveOverestimationSize范围内extra overestimation的粒度，其它描述见p3950
    physicalDeviceConservativeRasterizationPropertiesEXT.primitiveUnderestimation;//指明是否除了支持VK_CONSERVATIVE_RASTERIZATION_MODE_OVERESTIMATE_EXT 外额外支持VK_CONSERVATIVE_RASTERIZATION_MODE_UNDERESTIMATE_EXT conservative rasterization mode
    physicalDeviceConservativeRasterizationPropertiesEXT.conservativePointAndLineRasterization;//指明是否支持对 point ， line primitives 以及 triangle primitives的 conservative rasterization，否则只支持对三角形图元的
    physicalDeviceConservativeRasterizationPropertiesEXT.degenerateTrianglesRasterized;//为VK_FALSE，则将吧零区域三角形图元剔除并化为定点栅格化像素网格。如果为VK_TRUE，则不剔除这些图元，并且使用其fragment使用provoking顶点属性和深度值
    physicalDeviceConservativeRasterizationPropertiesEXT.degenerateLinesRasterized;//为VK_FALSE，则将吧零长度线图元剔除并化为定点栅格化像素网格。如果为VK_TRUE，则不剔除这些图元，并且使用其fragment使用provoking顶点属性和深度值
    physicalDeviceConservativeRasterizationPropertiesEXT.fullyCoveredFragmentShaderInputVariable;//如果为VK_TRUE，则支持SPIR-V内置变量fragment shader input variable FullyCoveredEXT，指定是否开启conservative rasterization且fragment 区域是否被图元完全覆盖
    physicalDeviceConservativeRasterizationPropertiesEXT.conservativeRasterizationPostDepthCoverage;//如果为VK_TRUE，则指明支持开启conservative rasterization时同时开启PostDepthCoverage execution mode


    //VkPhysicalDeviceFragmentDensityMapPropertiesEXT  ，可以包含在VkPhysicalDeviceProperties2.pNext中
    VkPhysicalDeviceFragmentDensityMapPropertiesEXT physicalDeviceFragmentDensityMapPropertiesEXT{};
    physicalDeviceFragmentDensityMapPropertiesEXT.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FRAGMENT_DENSITY_MAP_PROPERTIES_EXT;
    physicalDeviceFragmentDensityMapPropertiesEXT.pNext = nullptr;
    physicalDeviceFragmentDensityMapPropertiesEXT.minFragmentDensityTexelSize;//指明最小 fragment density texel size
    physicalDeviceFragmentDensityMapPropertiesEXT.maxFragmentDensityTexelSize;//指明最大 fragment density texel size
    physicalDeviceFragmentDensityMapPropertiesEXT.fragmentDensityInvocations;//指明对每个覆盖的采样点可能会调用额外的fragment shader


    //VkPhysicalDeviceFragmentDensityMap2PropertiesEXT  ，可以包含在VkPhysicalDeviceProperties2.pNext中
    VkPhysicalDeviceFragmentDensityMap2PropertiesEXT physicalDeviceFragmentDensityMap2PropertiesEXT{};
    physicalDeviceFragmentDensityMap2PropertiesEXT.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FRAGMENT_DENSITY_MAP_2_PROPERTIES_EXT;
    physicalDeviceFragmentDensityMap2PropertiesEXT.pNext = nullptr;
    physicalDeviceFragmentDensityMap2PropertiesEXT.subsampledLoads;//指明对subsampled attachments以加载操作进行image数据读取是是否会重新采样的render pass的fragment density
    physicalDeviceFragmentDensityMap2PropertiesEXT.subsampledCoarseReconstructionEarlyAccess;//指明在fragment shader中以用包含VK_SAMPLER_CREATE_SUBSAMPLED_COARSE_RECONSTRUCTION_BIT_EXT创建的samplers对image数据进行读取时会在VK_PIPELINE_STAGE_VERTEX_SHADER_BIT阶段触发额外的读取
    physicalDeviceFragmentDensityMap2PropertiesEXT.maxSubsampledArrayLayers;//为支持用于subsampled samplers的VkImageView的array layer的最大数量
    physicalDeviceFragmentDensityMap2PropertiesEXT.maxDescriptorSetSubsampledSamplers;//为可以包含在一个 VkPipelineLayout中的subsampled samplers的最大数量


    //VkPhysicalDeviceFragmentDensityMapOffsetPropertiesQCOM  ，可以包含在VkPhysicalDeviceProperties2.pNext中
    VkPhysicalDeviceFragmentDensityMapOffsetPropertiesQCOM physicalDeviceFragmentDensityMapOffsetPropertiesQCOM{};
    physicalDeviceFragmentDensityMapOffsetPropertiesQCOM.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FRAGMENT_DENSITY_MAP_OFFSET_PROPERTIES_QCOM;
    physicalDeviceFragmentDensityMapOffsetPropertiesQCOM.pNext = nullptr;
    physicalDeviceFragmentDensityMapOffsetPropertiesQCOM.fragmentDensityOffsetGranularity;//指明 fragment density offsets的粒度


    //VkPhysicalDeviceShaderCorePropertiesAMD  ，可以包含在VkPhysicalDeviceProperties2.pNext中
    VkPhysicalDeviceShaderCorePropertiesAMD physicalDeviceShaderCorePropertiesAMD{};
    physicalDeviceShaderCorePropertiesAMD.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_CORE_PROPERTIES_AMD;
    physicalDeviceShaderCorePropertiesAMD.pNext = nullptr;
    physicalDeviceShaderCorePropertiesAMD.shaderEngineCount;//为在physical device中的shader core中找到的shader engine的数量
    physicalDeviceShaderCorePropertiesAMD.shaderArraysPerEngineCount;//指明shader engine中 shader arrays的数量，其他描述见p3954
    physicalDeviceShaderCorePropertiesAMD.computeUnitsPerShaderArray;//指明一个shader array中compute units的数量，其他描述见p3954
    physicalDeviceShaderCorePropertiesAMD.simdPerComputeUnit;//指明一个compute unit中SIMD的数量，一个SIMD在一个时刻只能除了一条指令
    physicalDeviceShaderCorePropertiesAMD.wavefrontsPerSimd;//
    physicalDeviceShaderCorePropertiesAMD.wavefrontSize;//为一个subgroup的最大大小
    physicalDeviceShaderCorePropertiesAMD.sgprsPerSimd;//指明每个SIMD中标量通用寄存器 SGPR的数量
    physicalDeviceShaderCorePropertiesAMD.minSgprAllocation;//指明分配给wave的标量通用寄存器 SGPR的最小数量
    physicalDeviceShaderCorePropertiesAMD.maxSgprAllocation;//指明分配给wave的标量通用寄存器 SGPR的最大数量
    physicalDeviceShaderCorePropertiesAMD.sgprAllocationGranularity;//指明分配给wave的标量通用寄存器 SGPR的分配粒度
    physicalDeviceShaderCorePropertiesAMD.vgprsPerSimd;//指明每个SIMD中向量通用寄存器 VGPR的数量
    physicalDeviceShaderCorePropertiesAMD.minVgprAllocation;//指明分配给wave的向量通用寄存器 VGPR的最小数量
    physicalDeviceShaderCorePropertiesAMD.maxVgprAllocation;//指明分配给wave的向量通用寄存器 VGPR的最大数量
    physicalDeviceShaderCorePropertiesAMD.vgprAllocationGranularity;//指明分配给wave的向量通用寄存器 VGPR的分配粒度


    //VkPhysicalDeviceShaderCoreProperties2AMD  ，可以包含在VkPhysicalDeviceProperties2.pNext中
    VkPhysicalDeviceShaderCoreProperties2AMD physicalDeviceShaderCoreProperties2AMD{};
    physicalDeviceShaderCoreProperties2AMD.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_CORE_PROPERTIES_2_AMD;
    physicalDeviceShaderCoreProperties2AMD.pNext = nullptr;
    physicalDeviceShaderCoreProperties2AMD.shaderCoreFeatures;//VkShaderCorePropertiesFlagBitsAMD 组合值位掩码指明shader core支持的一组特性
    physicalDeviceShaderCoreProperties2AMD.activeComputeUnitCount;//指明已经启用的 compute units的数量


    //VkPhysicalDeviceDepthStencilResolveProperties  ，等价于VkPhysicalDeviceDepthStencilResolvePropertiesKHR ，可以包含在VkPhysicalDeviceProperties2.pNext中
    VkPhysicalDeviceDepthStencilResolveProperties physicalDeviceDepthStencilResolveProperties{};
    physicalDeviceDepthStencilResolveProperties.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DEPTH_STENCIL_RESOLVE_PROPERTIES;
    physicalDeviceDepthStencilResolveProperties.pNext = nullptr;
    physicalDeviceDepthStencilResolveProperties.supportedDepthResolveModes;//VkResolveModeFlagBits 组合值位掩码指明支持的depth resolve modes，其他信息见p3956
    physicalDeviceDepthStencilResolveProperties.supportedStencilResolveModes;//VkResolveModeFlagBits 组合值位掩码指明支持的stencil resolve modes，其他信息见p3956
    physicalDeviceDepthStencilResolveProperties.independentResolveNone;//指明是否支持 depth 以及 stencil resolve modes 为不同的值，其中一个为VK_RESOLVE_MODE_NONE
    physicalDeviceDepthStencilResolveProperties.independentResolve;//指明是否支持对支持的depth 以及 stencil resolve modes的任意组合


    //VkPhysicalDevicePerformanceQueryPropertiesKHR  ，可以包含在VkPhysicalDeviceProperties2.pNext中
    VkPhysicalDevicePerformanceQueryPropertiesKHR physicalDevicePerformanceQueryPropertiesKHR{};
    physicalDevicePerformanceQueryPropertiesKHR.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PERFORMANCE_QUERY_PROPERTIES_KHR;
    physicalDevicePerformanceQueryPropertiesKHR.pNext = nullptr;
    physicalDevicePerformanceQueryPropertiesKHR.allowCommandBufferQueryCopies;//指明是否performance query pools可以用于 vkCmdCopyQueryPoolResults


    //VkPhysicalDeviceShadingRateImagePropertiesNV  ，可以包含在VkPhysicalDeviceProperties2.pNext中
    VkPhysicalDeviceShadingRateImagePropertiesNV physicalDeviceShadingRateImagePropertiesNV{};
    physicalDeviceShadingRateImagePropertiesNV.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADING_RATE_IMAGE_PROPERTIES_NV;
    physicalDeviceShadingRateImagePropertiesNV.pNext = nullptr;
    physicalDeviceShadingRateImagePropertiesNV.shadingRateTexelSize;//指明shading rate image中每个texel对应的framebuffer中区域的width以及height
    physicalDeviceShadingRateImagePropertiesNV.shadingRatePaletteSize;//指明shading rate image支持的palette实体的最大数量
    physicalDeviceShadingRateImagePropertiesNV.shadingRateMaxCoarseSamples;//指明一个fragment中能包含的采样点的最大数量，其他描述见p3958


    //VkPhysicalDeviceMemoryDecompressionPropertiesNV  ，可以包含在VkPhysicalDeviceProperties2.pNext中
    VkPhysicalDeviceMemoryDecompressionPropertiesNV physicalDeviceMemoryDecompressionPropertiesNV{};
    physicalDeviceMemoryDecompressionPropertiesNV.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MEMORY_DECOMPRESSION_PROPERTIES_NV;
    physicalDeviceMemoryDecompressionPropertiesNV.pNext = nullptr;
    physicalDeviceMemoryDecompressionPropertiesNV.decompressionMethods;// VkMemoryDecompressionMethodFlagBitsNV 组合值位掩码，指明支持的内存解压方法
    physicalDeviceMemoryDecompressionPropertiesNV.maxDecompressionIndirectCount;//指明支持的 vkCmdDecompressMemoryIndirectCountNV 命令中countBuffer中包含的count 值的最大值


    //VkPhysicalDeviceMemoryDecompressionPropertiesNV  ，可以包含在VkPhysicalDeviceProperties2.pNext中
    VkPhysicalDeviceTransformFeedbackPropertiesEXT physicalDeviceTransformFeedbackPropertiesEXT{};
    physicalDeviceTransformFeedbackPropertiesEXT.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_TRANSFORM_FEEDBACK_PROPERTIES_EXT;
    physicalDeviceTransformFeedbackPropertiesEXT.pNext = nullptr;
    physicalDeviceTransformFeedbackPropertiesEXT.maxTransformFeedbackStreams;//指明可以从申明了 GeometryStreams能力的geometry shaders 输出的vertex streams 的最大数量，其他描述见p3959
    physicalDeviceTransformFeedbackPropertiesEXT.maxTransformFeedbackBuffers;//指明可以用来捕获 last pre-rasterization shader stage 的输出 的transform feedback buffers 的最大数量
    physicalDeviceTransformFeedbackPropertiesEXT.maxTransformFeedbackBufferSize;//指明 vkCmdBindTransformFeedbackBuffersEXT中可以绑定的一个transform feedback buffer的最大大小
    physicalDeviceTransformFeedbackPropertiesEXT.maxTransformFeedbackStreamDataSize;//指明可以捕获的关联到一个vertex stream的一个或多 transform feedback buffers中顶点数据总数的最大字节大小
    physicalDeviceTransformFeedbackPropertiesEXT.maxTransformFeedbackBufferDataSize;//指明指定 transform feedback buffers中可以捕获的顶点数据的最大字节量
    physicalDeviceTransformFeedbackPropertiesEXT.maxTransformFeedbackBufferDataStride;//为buffer中每个捕获的顶点数据之间的直接步长
    physicalDeviceTransformFeedbackPropertiesEXT.transformFeedbackQueries;//指明是否支持VK_QUERY_TYPE_TRANSFORM_FEEDBACK_STREAM_EXT query type
    physicalDeviceTransformFeedbackPropertiesEXT.transformFeedbackStreamsLinesTriangles;//指明当一个或者多个 vertex stream 输出时，是否支持geometry shader OpExecutionMode除了支持OutputPoints 之外也支持OutputLineStrip 以及 OutputTriangleStrip
    physicalDeviceTransformFeedbackPropertiesEXT.transformFeedbackRasterizationStreamSelect;//指明是否支持GeometryStreams SPIR-V capability且可以用VkPipelineRasterizationStateStreamCreateInfoEXT 来更新用于光栅化的 vertex stream output
    physicalDeviceTransformFeedbackPropertiesEXT.transformFeedbackDraw;//指明是否支持使用vkCmdDrawIndirectByteCountEXT


    //VkPhysicalDeviceCopyMemoryIndirectPropertiesNV  ，可以包含在VkPhysicalDeviceProperties2.pNext中
    VkPhysicalDeviceCopyMemoryIndirectPropertiesNV physicalDeviceCopyMemoryIndirectPropertiesNV{};
    physicalDeviceCopyMemoryIndirectPropertiesNV.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_COPY_MEMORY_INDIRECT_PROPERTIES_NV;
    physicalDeviceCopyMemoryIndirectPropertiesNV.pNext = nullptr;
    physicalDeviceCopyMemoryIndirectPropertiesNV.supportedQueues;// VkQueueFlagBits 组合值位掩码，指明 indirect copy commands支持的队列


    //VkPhysicalDeviceRayTracingPropertiesNV  ，可以包含在VkPhysicalDeviceProperties2.pNext中
    VkPhysicalDeviceRayTracingPropertiesNV physicalDeviceRayTracingPropertiesNV{};
    physicalDeviceRayTracingPropertiesNV.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_RAY_TRACING_PROPERTIES_NV;
    physicalDeviceRayTracingPropertiesNV.pNext = nullptr;
    physicalDeviceRayTracingPropertiesNV.shaderGroupHandleSize;//指明shader header的字节大小
    physicalDeviceRayTracingPropertiesNV.maxRecursionDepth;//指明trace command中允许的最大递归深度
    physicalDeviceRayTracingPropertiesNV.maxShaderGroupStride;//为shader binding table中shader groups之间的最大字节步长
    physicalDeviceRayTracingPropertiesNV.shaderGroupBaseAlignment;//为shader binding table的基本内存对齐要求
    physicalDeviceRayTracingPropertiesNV.maxGeometryCount;//为 bottom level acceleration strcuture中geometry的最大数量
    physicalDeviceRayTracingPropertiesNV.maxInstanceCount;//为 top level acceleration strcuture中instance的最大数量
    physicalDeviceRayTracingPropertiesNV.maxTriangleCount;//为 bottom level acceleration strcuture中所有geometry中三角形的最大数量
    physicalDeviceRayTracingPropertiesNV.maxDescriptorSetAccelerationStructures;//为 descriptor set中可以含有的acceleration strcuture descriptors的最大数量


    //VkPhysicalDeviceAccelerationStructurePropertiesKHR  ，可以包含在VkPhysicalDeviceProperties2.pNext中
    VkPhysicalDeviceAccelerationStructurePropertiesKHR physicalDeviceAccelerationStructurePropertiesKHR{};
    physicalDeviceAccelerationStructurePropertiesKHR.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_ACCELERATION_STRUCTURE_PROPERTIES_KHR;
    physicalDeviceAccelerationStructurePropertiesKHR.pNext = nullptr;
    physicalDeviceAccelerationStructurePropertiesKHR.maxGeometryCount;//为 bottom level acceleration strcuture中geometry的最大数量
    physicalDeviceAccelerationStructurePropertiesKHR.maxInstanceCount;//为 top level acceleration strcuture中instance的最大数量
    physicalDeviceAccelerationStructurePropertiesKHR.maxPrimitiveCount;//为 bottom level acceleration strcuture中所有geometry中AABB或者三角形的最大数量
    physicalDeviceAccelerationStructurePropertiesKHR.maxPerStageDescriptorAccelerationStructures;//为一个pipeline layout中的一个shader stage可以访问的acceleration structure binding的最大数量，其他描述见p3962
    physicalDeviceAccelerationStructurePropertiesKHR.maxPerStageDescriptorUpdateAfterBindAccelerationStructures;// 类似于maxPerStageDescriptorAccelerationStructures，只不过descriptors的统计从以创建含有或者不含有VK_DESCRIPTOR_SET_LAYOUT_CREATE_UPDATE_AFTER_BIND_POOL_BIT 的descriptor sets中统计
    physicalDeviceAccelerationStructurePropertiesKHR.maxDescriptorSetAccelerationStructures;//为所有pipeline shader stages 以及 descriptor set 编号中， 一个pipeline layout中的一个 descriptor bindings中能含有的acceleration structure descriptors的最大数量，其他信息见p3963
    physicalDeviceAccelerationStructurePropertiesKHR.maxDescriptorSetUpdateAfterBindAccelerationStructures;// 类似于maxDescriptorSetAccelerationStructures，只不过descriptors的统计从以创建含有或者不含有VK_DESCRIPTOR_SET_LAYOUT_CREATE_UPDATE_AFTER_BIND_POOL_BIT 的descriptor sets中统计
    physicalDeviceAccelerationStructurePropertiesKHR.minAccelerationStructureScratchOffsetAlignment;//为传递给一个acceleration structure build command的scratch数据的最小字节对齐，必须为2的指数


    //VkPhysicalDeviceRayTracingPipelinePropertiesKHR  ，可以包含在VkPhysicalDeviceProperties2.pNext中
    VkPhysicalDeviceRayTracingPipelinePropertiesKHR physicalDeviceRayTracingPipelinePropertiesKHR{};
    physicalDeviceRayTracingPipelinePropertiesKHR.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_RAY_TRACING_PIPELINE_PROPERTIES_KHR;
    physicalDeviceRayTracingPipelinePropertiesKHR.pNext = nullptr;
    physicalDeviceRayTracingPipelinePropertiesKHR.shaderGroupHandleSize;//指明shader header的字节大小
    physicalDeviceRayTracingPipelinePropertiesKHR.maxRayRecursionDepth;//指明trace command中允许的最大递归深度
    physicalDeviceRayTracingPipelinePropertiesKHR.maxShaderGroupStride;//为shader binding table中shader groups之间的最大字节步长
    physicalDeviceRayTracingPipelinePropertiesKHR.shaderGroupBaseAlignment;//为shader binding table的基本内存对齐要求
    physicalDeviceRayTracingPipelinePropertiesKHR.shaderGroupHandleCaptureReplaySize;//为 shader group handles 做捕获和回放的信息需要的字节数
	physicalDeviceRayTracingPipelinePropertiesKHR.maxRayDispatchInvocationCount;//为单个 vkCmdTraceRaysIndirectKHR 或者 vkCmdTraceRaysKHR调用中可以包含的ray generation shader invocations的最大数量
    physicalDeviceRayTracingPipelinePropertiesKHR.shaderGroupHandleAlignment;//为shader binding table 中每个实体需要的字节对齐要求，为2的指数
    physicalDeviceRayTracingPipelinePropertiesKHR.maxRayHitAttributeSize;//为ray attribute structure的最大字节数


    //VkPhysicalDeviceCooperativeMatrixPropertiesNV  ，可以包含在VkPhysicalDeviceProperties2.pNext中
    VkPhysicalDeviceCooperativeMatrixPropertiesNV physicalDeviceCooperativeMatrixPropertiesNV{};
    physicalDeviceCooperativeMatrixPropertiesNV.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_COOPERATIVE_MATRIX_PROPERTIES_NV;
    physicalDeviceCooperativeMatrixPropertiesNV.pNext = nullptr;
    physicalDeviceCooperativeMatrixPropertiesNV.cooperativeMatrixSupportedStages;// VkShaderStageFlagBits 组合值，描述cooperative matrix instructions支持的shader stages


    //VkPhysicalDeviceCooperativeMatrixPropertiesKHR  ，可以包含在VkPhysicalDeviceProperties2.pNext中
    VkPhysicalDeviceCooperativeMatrixPropertiesKHR physicalDeviceCooperativeMatrixPropertiesHKR{};
    physicalDeviceCooperativeMatrixPropertiesHKR.sType = VK_STRUCTURE_TYPE_MAX_ENUM;//没有定义这里定义为非法值
    physicalDeviceCooperativeMatrixPropertiesHKR.pNext = nullptr;
    physicalDeviceCooperativeMatrixPropertiesHKR.cooperativeMatrixSupportedStages;// VkShaderStageFlagBits 组合值，描述cooperative matrix instructions支持的shader stages

    //VkPhysicalDeviceShaderSMBuiltinsPropertiesNV  ，可以包含在VkPhysicalDeviceProperties2.pNext中
    VkPhysicalDeviceShaderSMBuiltinsPropertiesNV physicalDeviceShaderSMBuiltinsPropertiesNV{};
    physicalDeviceShaderSMBuiltinsPropertiesNV.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_SM_BUILTINS_PROPERTIES_NV;
    physicalDeviceShaderSMBuiltinsPropertiesNV.pNext = nullptr;
    physicalDeviceShaderSMBuiltinsPropertiesNV.shaderSMCount;// device上的SM的数量
	physicalDeviceShaderSMBuiltinsPropertiesNV.shaderWarpsPerSM;//为一个SM中同时运行的warp的数量


    //VkPhysicalDeviceTexelBufferAlignmentProperties ，等价于VkPhysicalDeviceTexelBufferAlignmentPropertiesEXT  ，可以包含在VkPhysicalDeviceProperties2.pNext中
    VkPhysicalDeviceTexelBufferAlignmentProperties physicalDeviceTexelBufferAlignmentProperties{};
    physicalDeviceTexelBufferAlignmentProperties.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_TEXEL_BUFFER_ALIGNMENT_PROPERTIES;
    physicalDeviceTexelBufferAlignmentProperties.pNext = nullptr;
	physicalDeviceTexelBufferAlignmentProperties.storageTexelBufferOffsetAlignmentBytes;//为足以满足任何format的storage texel buffer的字节对齐要求，为2的指数
	physicalDeviceTexelBufferAlignmentProperties.storageTexelBufferOffsetSingleTexelAlignment;//为足以满足任何format的storage texel buffer的单个texel的对齐要求，为2的指数
	physicalDeviceTexelBufferAlignmentProperties.uniformTexelBufferOffsetAlignmentBytes;//为足以满足任何format的uniform texel buffer的字节对齐要求，为2的指数
	physicalDeviceTexelBufferAlignmentProperties.uniformTexelBufferOffsetSingleTexelAlignment;//为足以满足任何format的uniform texel buffer的单个texel的对齐要求，为2的指数


    //VkPhysicalDeviceTimelineSemaphoreProperties ，等价于VkPhysicalDeviceTimelineSemaphorePropertiesKHR  ，可以包含在VkPhysicalDeviceProperties2.pNext中
    VkPhysicalDeviceTimelineSemaphoreProperties physicalDeviceTimelineSemaphoreProperties{};
    physicalDeviceTimelineSemaphoreProperties.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_TIMELINE_SEMAPHORE_PROPERTIES;
    physicalDeviceTimelineSemaphoreProperties.pNext = nullptr;
    physicalDeviceTimelineSemaphoreProperties.maxTimelineSemaphoreValueDifference;//为timeline semaphore的当前值和任何挂起的semaphore等待以及触发的值之间差值的最大值


    //VkPhysicalDeviceLineRasterizationPropertiesKHR ，等价于VkPhysicalDeviceLineRasterizationPropertiesEXT  ，可以包含在VkPhysicalDeviceProperties2.pNext中
    VkPhysicalDeviceLineRasterizationPropertiesKHR physicalDeviceLineRasterizationPropertiesKHR{};
	physicalDeviceLineRasterizationPropertiesKHR.sType = VK_STRUCTURE_TYPE_MAX_ENUM;//没有定义这里定义为非法值
    physicalDeviceLineRasterizationPropertiesKHR.pNext = nullptr;
	physicalDeviceLineRasterizationPropertiesKHR.lineSubPixelPrecisionBits;//为line rasterization的framebuffer 坐标中xf，yf的 subpixel精度的位数，为2的指数


    //VkPhysicalDeviceRobustness2PropertiesEXT  ，可以包含在VkPhysicalDeviceProperties2.pNext中
    VkPhysicalDeviceRobustness2PropertiesEXT physicalDeviceRobustness2PropertiesEXT{};
    physicalDeviceRobustness2PropertiesEXT.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_ROBUSTNESS_2_PROPERTIES_EXT;
    physicalDeviceRobustness2PropertiesEXT.pNext = nullptr;
    physicalDeviceRobustness2PropertiesEXT.robustStorageBufferAccessSizeAlignment;//为当开启robustBufferAccess2 特性且使用bounds-checking是storage buffer descriptor舍入的范围的字节数，必须为1或4
    physicalDeviceRobustness2PropertiesEXT.robustUniformBufferAccessSizeAlignment;//为当开启robustBufferAccess2 特性且使用bounds-checking是uniform buffer descriptor舍入的范围的字节数，必须为 [1, 256]范围内的2的指数


    //VkPhysicalDeviceDeviceGeneratedCommandsPropertiesNV  ，可以包含在VkPhysicalDeviceProperties2.pNext中
    VkPhysicalDeviceDeviceGeneratedCommandsPropertiesNV physicalDeviceDeviceGeneratedCommandsPropertiesNV{};
    physicalDeviceDeviceGeneratedCommandsPropertiesNV.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DEVICE_GENERATED_COMMANDS_PROPERTIES_NV;
    physicalDeviceDeviceGeneratedCommandsPropertiesNV.pNext = nullptr;
    physicalDeviceDeviceGeneratedCommandsPropertiesNV.maxGraphicsShaderGroupCount;//为VkGraphicsPipelineShaderGroupsCreateInfoNV 中shader groups的最大数量
    physicalDeviceDeviceGeneratedCommandsPropertiesNV.maxIndirectSequenceCount;//为VkGeneratedCommandsInfoNV 以及VkGeneratedCommandsMemoryRequirementsInfoNV 中序列的最大数量
    physicalDeviceDeviceGeneratedCommandsPropertiesNV.maxIndirectCommandsTokenCount;//为VkIndirectCommandsLayoutCreateInfoNV 中tokens 的最大数量
    physicalDeviceDeviceGeneratedCommandsPropertiesNV.maxIndirectCommandsStreamCount;//为VkIndirectCommandsLayoutCreateInfoNV 中streams 的最大数量
    physicalDeviceDeviceGeneratedCommandsPropertiesNV.maxIndirectCommandsTokenOffset;//为 VkIndirectCommandsLayoutTokenNV 中offset 的最大值
    physicalDeviceDeviceGeneratedCommandsPropertiesNV.maxIndirectCommandsStreamStride;//为VkIndirectCommandsLayoutCreateInfoNV 中stream stride 的最大数量
	physicalDeviceDeviceGeneratedCommandsPropertiesNV.minSequencesCountBufferOffsetAlignment;//为 VkGeneratedCommandsInfoNV 中内存地址可以使用的最小字节对齐
    physicalDeviceDeviceGeneratedCommandsPropertiesNV.minSequencesIndexBufferOffsetAlignment;//为  VkGeneratedCommandsInfoNV 中内存地址可以使用的最小字节对齐
    physicalDeviceDeviceGeneratedCommandsPropertiesNV.minIndirectCommandsBufferOffsetAlignment;//为  VkIndirectCommandsStreamNV 中内存地址以及VkGeneratedCommandsInfoNV 中预处理buffer可以使用的最小字节对齐


    //VkPhysicalDevicePortabilitySubsetPropertiesKHR  ，可以包含在VkPhysicalDeviceProperties2.pNext中
    VkPhysicalDevicePortabilitySubsetPropertiesKHR physicalDevicePortabilitySubsetPropertiesKHR{};
    physicalDevicePortabilitySubsetPropertiesKHR.sType = VK_STRUCTURE_TYPE_MAX_ENUM;//没有定义这里定义为非法值
    physicalDevicePortabilitySubsetPropertiesKHR.pNext = nullptr;
	physicalDevicePortabilitySubsetPropertiesKHR.minVertexInputBindingStrideAlignment;//为vertex input binding stride的最小字节对齐要求，为2的指数


    //VkPhysicalDeviceFragmentShadingRatePropertiesKHR  ，可以包含在VkPhysicalDeviceProperties2.pNext中
    VkPhysicalDeviceFragmentShadingRatePropertiesKHR physicalDeviceFragmentShadingRatePropertiesKHR{};
    physicalDeviceFragmentShadingRatePropertiesKHR.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FRAGMENT_SHADING_RATE_PROPERTIES_KHR;
    physicalDeviceFragmentShadingRatePropertiesKHR.pNext = nullptr;
	physicalDeviceFragmentShadingRatePropertiesKHR.minFragmentShadingRateAttachmentTexelSize;//指明fragment shading rate attachment每个texel 对应的framebuffer 区域的width以及height的最小值，其他描述见p3971
    physicalDeviceFragmentShadingRatePropertiesKHR.maxFragmentShadingRateAttachmentTexelSize;//指明fragment shading rate attachment每个texel 对应的framebuffer 区域的width以及height的最大值，其他描述见p3971
	physicalDeviceFragmentShadingRatePropertiesKHR.maxFragmentShadingRateAttachmentTexelSizeAspectRatio;//指明fragment shading rate attachment每个texel 对应的framebuffer 区域的width以及height的比值的最大值，其他描述见p3971
    physicalDeviceFragmentShadingRatePropertiesKHR.primitiveFragmentShadingRateWithMultipleViewports;//指明是否 primitive fragment shading rate 可以和multiple viewports 一起使用，其他描述见p3972
    physicalDeviceFragmentShadingRatePropertiesKHR.layeredShadingRateAttachments;//指明一个 shading rate attachment image view可以含多个layer创建，其他描述见p3972
    physicalDeviceFragmentShadingRatePropertiesKHR.fragmentShadingRateNonTrivialCombinerOps;//指明除VK_FRAGMENT_SHADING_RATE_COMBINER_OP_KEEP_KHR 或者VK_FRAGMENT_SHADING_RATE_COMBINER_OP_REPLACE_KHR 之外的VkFragmentShadingRateCombinerOpKHR 枚举值是否可以使用
	physicalDeviceFragmentShadingRatePropertiesKHR.maxFragmentSize;//指明一个fragment支持的width和height的最大值，其他描述见p3972
    physicalDeviceFragmentShadingRatePropertiesKHR.maxFragmentSizeAspectRatio;//指明一个fragment支持的width和height比值的最大值，其他描述见p3972
	physicalDeviceFragmentShadingRatePropertiesKHR.maxFragmentShadingRateCoverageSamples;//指明一个fragment的coverage samples的最大数量，其他描述见p3972
    physicalDeviceFragmentShadingRatePropertiesKHR.maxFragmentShadingRateRasterizationSamples;// VkSampleCountFlagBits 组合值位掩码，指明当一个fragment包含多个pixels时支持的 sample rate的最大值
	physicalDeviceFragmentShadingRatePropertiesKHR.fragmentShadingRateWithShaderDepthStencilWrites;//指明是否支持在fragment shader中对multi-pixel fragment通过 FragDepth 或者 FragStencilRefEXT写入深度以及stencil值，其他描述见p3973
    physicalDeviceFragmentShadingRatePropertiesKHR.fragmentShadingRateWithSampleMask;//指明是否支持对 multi-pixel fragments设置 VkPipelineMultisampleStateCreateInfo::pSampleMask 中有效位为0，其他描述见p3973
	physicalDeviceFragmentShadingRatePropertiesKHR.fragmentShadingRateWithShaderSampleMask;//指明是否支持读写multi-pixel fragment的SampleMask ，其他描述见p3973
	physicalDeviceFragmentShadingRatePropertiesKHR.fragmentShadingRateWithConservativeRasterization;//指明对 multi-pixel fragments是否支持conservative rasterization ，其他描述见p3973
    physicalDeviceFragmentShadingRatePropertiesKHR.fragmentShadingRateWithFragmentShaderInterlock;//指明对 multi-pixel fragments是否支持 fragment shader interlock ，其他描述见p3973
	physicalDeviceFragmentShadingRatePropertiesKHR.fragmentShadingRateWithCustomSampleLocations;//指明对 multi-pixel fragments是否支持 custom sample locations ，其他描述见p3973
	physicalDeviceFragmentShadingRatePropertiesKHR.fragmentShadingRateStrictMultiplyCombiner;//指明VK_FRAGMENT_SHADING_RATE_COMBINER_OP_MUL_KHR 是否精确的执行乘法操作，其他描述见p3974


    //VkPhysicalDeviceFragmentShadingRateEnumsPropertiesNV  ，可以包含在VkPhysicalDeviceProperties2.pNext中
    VkPhysicalDeviceFragmentShadingRateEnumsPropertiesNV physicalDeviceFragmentShadingRateEnumsPropertiesNV{};
    physicalDeviceFragmentShadingRateEnumsPropertiesNV.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FRAGMENT_SHADING_RATE_ENUMS_PROPERTIES_NV;
    physicalDeviceFragmentShadingRateEnumsPropertiesNV.pNext = nullptr;
	physicalDeviceFragmentShadingRateEnumsPropertiesNV.maxFragmentShadingRateInvocationCount;//一个 VkSampleCountFlagBits 值指明pipeline，primitive, 以及 attachment fragment shading rates中一个fragment能够调用的fragment shader的最大次数，其他描述见p3975


    //VkPhysicalDeviceCustomBorderColorPropertiesEXT  ，可以包含在VkPhysicalDeviceProperties2.pNext中
    VkPhysicalDeviceCustomBorderColorPropertiesEXT physicalDeviceCustomBorderColorPropertiesEXT{};
    physicalDeviceCustomBorderColorPropertiesEXT.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_CUSTOM_BORDER_COLOR_PROPERTIES_EXT;
    physicalDeviceCustomBorderColorPropertiesEXT.pNext = nullptr;
	physicalDeviceCustomBorderColorPropertiesEXT.maxCustomBorderColorSamplers;//为可以同时存在在device上的含custom border color的 samplers的最大数量


    //VkPhysicalDeviceProvokingVertexPropertiesEXT  ，可以包含在VkPhysicalDeviceProperties2.pNext中
    VkPhysicalDeviceProvokingVertexPropertiesEXT physicalDeviceProvokingVertexPropertiesEXT{};
    physicalDeviceProvokingVertexPropertiesEXT.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PROVOKING_VERTEX_PROPERTIES_EXT;
    physicalDeviceProvokingVertexPropertiesEXT.pNext = nullptr;
    physicalDeviceProvokingVertexPropertiesEXT.provokingVertexModePerPipeline;//指明是否graphics pipeline在相同render pass实例中使用不同的provoking vertex modes
    physicalDeviceProvokingVertexPropertiesEXT.transformFeedbackPreservesTriangleFanProvokingVertex;//指明当写入triangle fan图元顶点到transform feedback是否可以保留provoking vertex order


    //VkPhysicalDeviceDescriptorBufferPropertiesEXT  ，可以包含在VkPhysicalDeviceProperties2.pNext中
    VkPhysicalDeviceDescriptorBufferPropertiesEXT physicalDeviceDescriptorBufferPropertiesEXT{};
    physicalDeviceDescriptorBufferPropertiesEXT.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DESCRIPTOR_BUFFER_PROPERTIES_EXT;
    physicalDeviceDescriptorBufferPropertiesEXT.pNext = nullptr;
    physicalDeviceDescriptorBufferPropertiesEXT.combinedImageSamplerDescriptorSingleArray;//表示实现不需要将VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER描述符数组作为图像描述符数组写入描述符缓冲区，紧接着是采样器描述符数组
    physicalDeviceDescriptorBufferPropertiesEXT.bufferlessPushDescriptors;//指明当使用push descriptors 时不需要绑定一个以 VK_BUFFER_USAGE_PUSH_DESCRIPTORS_DESCRIPTOR_BUFFER_BIT_EXT 创建的buffer
    physicalDeviceDescriptorBufferPropertiesEXT.allowSamplerImageViewPostSubmitCreation;//指明对以关联到 command buffer 提交的用于获取descriptor数据创建的 VkSampler 或者 VkImageView不做限制
    physicalDeviceDescriptorBufferPropertiesEXT.descriptorBufferOffsetAlignment;//指明当设置到descriptor buffer中需要的偏移的字节对齐
    physicalDeviceDescriptorBufferPropertiesEXT.maxDescriptorBufferBindings;//指明可以绑定的descriptor buffers 和embedded immutable sampler sets的总数的最大数量
    physicalDeviceDescriptorBufferPropertiesEXT.maxResourceDescriptorBufferBindings;//指明可以绑定的resource descriptor buffers 的最大数量
    physicalDeviceDescriptorBufferPropertiesEXT.maxSamplerDescriptorBufferBindings;//指明可以绑定的sampler descriptor buffers 的最大数量
	physicalDeviceDescriptorBufferPropertiesEXT.maxEmbeddedImmutableSamplerBindings;//指明可以绑定的embedded immutable sampler sets 的最大数量
	physicalDeviceDescriptorBufferPropertiesEXT.maxEmbeddedImmutableSamplers;//指明可以同时存在在device上的以VK_DESCRIPTOR_SET_LAYOUT_CREATE_EMBEDDED_IMMUTABLE_SAMPLERS_BIT_EXT创建的descriptor set layouts以及从该layout 创建的pipeline中不重复的immutable samplers总数的最大数量
    physicalDeviceDescriptorBufferPropertiesEXT.bufferCaptureReplayDescriptorDataSize;//指明用buffers捕获和回放opaque data的最大字节数大小
	physicalDeviceDescriptorBufferPropertiesEXT.imageCaptureReplayDescriptorDataSize;//指明用images捕获和回放opaque data的最大字节数大小
    physicalDeviceDescriptorBufferPropertiesEXT.imageViewCaptureReplayDescriptorDataSize;//指明用image views捕获和回放opaque data的最大字节数大小
    physicalDeviceDescriptorBufferPropertiesEXT.samplerCaptureReplayDescriptorDataSize;//指明用samplers捕获和回放opaque data的最大字节数大小
    physicalDeviceDescriptorBufferPropertiesEXT.accelerationStructureCaptureReplayDescriptorDataSize;//指明用acceleration structures捕获和回放opaque data的最大字节数大小
    physicalDeviceDescriptorBufferPropertiesEXT.samplerDescriptorSize;//指明 VK_DESCRIPTOR_TYPE_SAMPLER 类型descriptor的字节大小
	physicalDeviceDescriptorBufferPropertiesEXT.combinedImageSamplerDescriptorSize;//指明 VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER 类型descriptor的字节大小
	physicalDeviceDescriptorBufferPropertiesEXT.sampledImageDescriptorSize;//指明 VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE 类型descriptor的字节大小
    physicalDeviceDescriptorBufferPropertiesEXT.storageImageDescriptorSize;//指明 VK_DESCRIPTOR_TYPE_STORAGE_IMAGE 类型descriptor的字节大小
	physicalDeviceDescriptorBufferPropertiesEXT.uniformTexelBufferDescriptorSize;//指明如果 robustBufferAccess特性 不开启时 VK_DESCRIPTOR_TYPE_UNIFORM_TEXEL_BUFFER 类型descriptor的字节大小
	physicalDeviceDescriptorBufferPropertiesEXT.robustUniformTexelBufferDescriptorSize;//指明如果 robustBufferAccess 特性开启时 VK_DESCRIPTOR_TYPE_UNIFORM_TEXEL_BUFFER 类型descriptor的字节大小
	physicalDeviceDescriptorBufferPropertiesEXT.storageTexelBufferDescriptorSize;//指明如果 robustBufferAccess特性 不开启时 VK_DESCRIPTOR_TYPE_STORAGE_TEXEL_BUFFER 类型descriptor的字节大小
	physicalDeviceDescriptorBufferPropertiesEXT.robustStorageTexelBufferDescriptorSize;//指明如果 robustBufferAccess 特性开启时 VK_DESCRIPTOR_TYPE_STORAGE_TEXEL_BUFFER 类型descriptor的字节大小
	physicalDeviceDescriptorBufferPropertiesEXT.uniformBufferDescriptorSize;//指明 VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER 类型descriptor的字节大小
    physicalDeviceDescriptorBufferPropertiesEXT.robustUniformBufferDescriptorSize;//指明如果 robustBufferAccess 特性开启时 VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER 类型descriptor的字节大小
    physicalDeviceDescriptorBufferPropertiesEXT.storageBufferDescriptorSize;//指明 VK_DESCRIPTOR_TYPE_STORAGE_BUFFER 类型descriptor的字节大小
    physicalDeviceDescriptorBufferPropertiesEXT.robustStorageBufferDescriptorSize;//指明如果 robustBufferAccess 特性开启时 VK_DESCRIPTOR_TYPE_STORAGE_BUFFER 类型descriptor的字节大小
    physicalDeviceDescriptorBufferPropertiesEXT.inputAttachmentDescriptorSize;//指明 VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT 类型descriptor的字节大小
    physicalDeviceDescriptorBufferPropertiesEXT.accelerationStructureDescriptorSize;//指明 VK_DESCRIPTOR_TYPE_ACCELERATION_STRUCTURE_KHR 或者 VK_DESCRIPTOR_TYPE_ACCELERATION_STRUCTURE_NV 类型descriptor的字节大小
    physicalDeviceDescriptorBufferPropertiesEXT.maxSamplerDescriptorBufferRange;//为一个shader可以访问的sampler descriptor buffer binding的地址的最大字节范围
	physicalDeviceDescriptorBufferPropertiesEXT.maxResourceDescriptorBufferRange;//为一个shader可以访问的resource descriptor buffer binding的地址的最大字节范围
	physicalDeviceDescriptorBufferPropertiesEXT.samplerDescriptorBufferAddressSpaceSize;//为以VK_BUFFER_USAGE_SAMPLER_DESCRIPTOR_BUFFER_BIT_EXT创建的descriptor buffers的可访问地址空间的最大字节数
    physicalDeviceDescriptorBufferPropertiesEXT.resourceDescriptorBufferAddressSpaceSize;//为以VK_BUFFER_USAGE_RESOURCE_DESCRIPTOR_BUFFER_BIT_EXT创建的descriptor buffers的可访问地址空间的最大字节数
    physicalDeviceDescriptorBufferPropertiesEXT.descriptorBufferAddressSpaceSize;//为同时以 VK_BUFFER_USAGE_SAMPLER_DESCRIPTOR_BUFFER_BIT_EXT和 VK_BUFFER_USAGE_RESOURCE_DESCRIPTOR_BUFFER_BIT_EXT创建的descriptor buffers的可访问地址空间的最大字节数


    //VkPhysicalDeviceDescriptorBufferDensityMapPropertiesEXT  ，可以包含在VkPhysicalDeviceProperties2.pNext中
    VkPhysicalDeviceDescriptorBufferDensityMapPropertiesEXT physicalDeviceDescriptorBufferDensityMapPropertiesEXT{};
    physicalDeviceDescriptorBufferDensityMapPropertiesEXT.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DESCRIPTOR_BUFFER_DENSITY_MAP_PROPERTIES_EXT;
    physicalDeviceDescriptorBufferDensityMapPropertiesEXT.pNext = nullptr;
	physicalDeviceDescriptorBufferDensityMapPropertiesEXT.combinedImageSamplerDensityMapDescriptorSize;//为以VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER类型且设置有VK_SAMPLER_CREATE_SUBSAMPLED_BIT_EXT 创建的descriptor 的字节大小





}

void LimitsAndFormatsTest::FormatsTest()
{
}



NS_TEST_END