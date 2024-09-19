#include "../common/Global.h"
#include "../common/TestBase.h"
NS_TEST_BEGIN
//有些安装的vulkan中不含的结构体或者接口会在这里自定义一下


// Provided by VK_NV_device_generated_commands_compute
typedef struct VkComputePipelineIndirectBufferInfoNV {
	VkStructureType sType;
	const void* pNext;
	VkDeviceAddress deviceAddress;
	VkDeviceSize size;
	VkDeviceAddress pipelineDeviceAddressCaptureReplay;
} VkComputePipelineIndirectBufferInfoNV;

// Provided by VK_ANDROID_external_memory_android_hardware_buffer
typedef struct VkExternalFormatANDROID {
	VkStructureType    sType;
	void* pNext;
	uint64_t           externalFormat;
} VkExternalFormatANDROID;
typedef VkFlags VkPipelineCreateFlags2KHR;
// Provided by VK_KHR_maintenance5
typedef struct VkPipelineCreateFlags2CreateInfoKHR {
	VkStructureType              sType;
	const void* pNext;
	VkPipelineCreateFlags2KHR    flags;
} VkPipelineCreateFlags2CreateInfoKHR;
// Provided by VK_AMDX_shader_enqueue
typedef struct VkPipelineShaderStageNodeCreateInfoAMDX {
	VkStructureType    sType;
	const void* pNext;
	const char* pName;
	uint32_t             index;
} VkPipelineShaderStageNodeCreateInfoAMDX;

// Provided by VK_KHR_dynamic_rendering_local_read
typedef struct VkRenderingAttachmentLocationInfoKHR {
	VkStructureType    sType;
	const void* pNext;
	uint32_t           colorAttachmentCount;
	const uint32_t* pColorAttachmentLocations;
} VkRenderingAttachmentLocationInfoKHR;

// Provided by VK_KHR_dynamic_rendering_local_read
typedef struct VkRenderingInputAttachmentIndexInfoKHR {
	VkStructureType    sType;
	const void* pNext;
	uint32_t           colorAttachmentCount;
	const uint32_t* pColorAttachmentInputIndices;
	const uint32_t* pDepthInputAttachmentIndex;
	const uint32_t* pStencilInputAttachmentIndex;
} VkRenderingInputAttachmentIndexInfoKHR;


// Provided by VK_KHR_maintenance5
typedef VkFlags64 VkBufferUsageFlags2KHR;


// Provided by VK_KHR_maintenance5
typedef struct VkBufferUsageFlags2CreateInfoKHR {
    VkStructureType           sType;
    const void* pNext;
    VkBufferUsageFlags2KHR    usage;
} VkBufferUsageFlags2CreateInfoKHR;




// Provided by VK_KHR_maintenance6 with VK_EXT_descriptor_buffer
typedef struct VkSetDescriptorBufferOffsetsInfoEXT {
    VkStructureType        sType;
    const void* pNext;
    VkShaderStageFlags     stageFlags;
    VkPipelineLayout       layout;
    uint32_t               firstSet;
    uint32_t               setCount;
    const uint32_t* pBufferIndices;
    const VkDeviceSize* pOffsets;
} VkSetDescriptorBufferOffsetsInfoEXT;

// Provided by VK_KHR_maintenance6 with VK_EXT_descriptor_buffer
void vkCmdSetDescriptorBufferOffsets2EXT(
    VkCommandBuffer commandBuffer,
    const VkSetDescriptorBufferOffsetsInfoEXT* pSetDescriptorBufferOffsetsInfo) {

}



// Provided by VK_KHR_maintenance6 with VK_EXT_descriptor_buffer
typedef struct VkBindDescriptorBufferEmbeddedSamplersInfoEXT {
    VkStructureType       sType;
    const void* pNext;
    VkShaderStageFlags    stageFlags;
    VkPipelineLayout      layout;
    uint32_t              set;
} VkBindDescriptorBufferEmbeddedSamplersInfoEXT;

// Provided by VK_KHR_maintenance6 with VK_EXT_descriptor_buffer
void vkCmdBindDescriptorBufferEmbeddedSamplers2EXT(
    VkCommandBuffer commandBuffer,
    const VkBindDescriptorBufferEmbeddedSamplersInfoEXT*
    pBindDescriptorBufferEmbeddedSamplersInfo) {
}

// Provided by VK_KHR_dynamic_rendering_local_read
void vkCmdSetRenderingAttachmentLocationsKHR(
	VkCommandBuffer commandBuffer,
	const VkRenderingAttachmentLocationInfoKHR* pLocationInfo) {
}



// Provided by VK_KHR_dynamic_rendering_local_read
void vkCmdSetRenderingInputAttachmentIndicesKHR(
	VkCommandBuffer commandBuffer,
	const VkRenderingInputAttachmentIndexInfoKHR* pLocationInfo) {}

typedef uint32_t StdVideoAV1Profile;//这里先自己定义
// Provided by VK_KHR_video_decode_av1
typedef struct VkVideoDecodeAV1ProfileInfoKHR {
	VkStructureType       sType;
	const void* pNext;
	StdVideoAV1Profile    stdProfile;
	VkBool32              filmGrainSupport;
} VkVideoDecodeAV1ProfileInfoKHR;


// Provided by VK_KHR_video_encode_h264
typedef struct VkVideoEncodeH264ProfileInfoKHR {
	VkStructureType           sType;
	const void* pNext;
	StdVideoH264ProfileIdc    stdProfileIdc;
} VkVideoEncodeH264ProfileInfoKHR;


// Provided by VK_KHR_video_encode_h265
typedef struct VkVideoEncodeH265ProfileInfoKHR {
	VkStructureType           sType;
	const void* pNext;
	StdVideoH265ProfileIdc    stdProfileIdc;
} VkVideoEncodeH265ProfileInfoKHR;



// Provided by VK_EXT_host_image_copy
typedef VkFlags VkHostImageCopyFlagsEXT;
// Provided by VK_EXT_host_image_copy
typedef struct VkImageToMemoryCopyEXT {
	VkStructureType             sType;
	const void* pNext;
	void* pHostPointer;
	uint32_t                    memoryRowLength;
	uint32_t                    memoryImageHeight;
	VkImageSubresourceLayers    imageSubresource;
	VkOffset3D                  imageOffset;
	VkExtent3D                  imageExtent;
} VkImageToMemoryCopyEXT;

// Provided by VK_EXT_host_image_copy
typedef struct VkCopyImageToMemoryInfoEXT {
	VkStructureType                  sType;
	const void* pNext;
	VkHostImageCopyFlagsEXT          flags;
	VkImage                          srcImage;
	VkImageLayout                    srcImageLayout;
	uint32_t                         regionCount;
	const VkImageToMemoryCopyEXT* pRegions;
} VkCopyImageToMemoryInfoEXT;


// Provided by VK_EXT_host_image_copy
typedef struct VkCopyImageToImageInfoEXT {
	VkStructureType            sType;
	const void* pNext;
	VkHostImageCopyFlagsEXT    flags;
	VkImage                    srcImage;
	VkImageLayout              srcImageLayout;
	VkImage                    dstImage;
	VkImageLayout              dstImageLayout;
	uint32_t                   regionCount;
	const VkImageCopy2* pRegions;
} VkCopyImageToImageInfoEXT;

// Provided by VK_QCOM_filter_cubic_weights
typedef enum VkCubicFilterWeightsQCOM {
	VK_CUBIC_FILTER_WEIGHTS_CATMULL_ROM_QCOM = 0,
	VK_CUBIC_FILTER_WEIGHTS_ZERO_TANGENT_CARDINAL_QCOM = 1,
	VK_CUBIC_FILTER_WEIGHTS_B_SPLINE_QCOM = 2,
	VK_CUBIC_FILTER_WEIGHTS_MITCHELL_NETRAVALI_QCOM = 3,
} VkCubicFilterWeightsQCOM;

// Provided by VK_QCOM_filter_cubic_weights
typedef struct VkBlitImageCubicWeightsInfoQCOM {
	VkStructureType             sType;
	const void* pNext;
	VkCubicFilterWeightsQCOM    cubicWeights;
} VkBlitImageCubicWeightsInfoQCOM;



// Provided by VK_KHR_vertex_attribute_divisor
typedef struct VkVertexInputBindingDivisorDescriptionKHR {
	uint32_t    binding;
	uint32_t    divisor;
} VkVertexInputBindingDivisorDescriptionKHR;
// Provided by VK_EXT_vertex_attribute_divisor
typedef VkVertexInputBindingDivisorDescriptionKHR VkVertexInputBindingDivisorDescriptionEXT;


// Provided by VK_KHR_vertex_attribute_divisor
typedef struct VkPipelineVertexInputDivisorStateCreateInfoKHR {
	VkStructureType                                     sType;
	const void* pNext;
	uint32_t                                            vertexBindingDivisorCount;
	const VkVertexInputBindingDivisorDescriptionKHR* pVertexBindingDivisors;
} VkPipelineVertexInputDivisorStateCreateInfoKHR;

// Provided by VK_EXT_depth_bias_control
typedef enum VkDepthBiasRepresentationEXT {
	VK_DEPTH_BIAS_REPRESENTATION_LEAST_REPRESENTABLE_VALUE_FORMAT_EXT = 0,
	VK_DEPTH_BIAS_REPRESENTATION_LEAST_REPRESENTABLE_VALUE_FORCE_UNORM_EXT = 1,
	VK_DEPTH_BIAS_REPRESENTATION_FLOAT_EXT = 2,
} VkDepthBiasRepresentationEXT;

// Provided by VK_EXT_depth_bias_control
typedef struct VkDepthBiasRepresentationInfoEXT {
	VkStructureType                 sType;
	const void* pNext;
	VkDepthBiasRepresentationEXT    depthBiasRepresentation;
	VkBool32                        depthBiasExact;
} VkDepthBiasRepresentationInfoEXT;

// Provided by VK_KHR_line_rasterization
typedef enum VkLineRasterizationModeKHR {
	VK_LINE_RASTERIZATION_MODE_DEFAULT_KHR = 0,
	VK_LINE_RASTERIZATION_MODE_RECTANGULAR_KHR = 1,
	VK_LINE_RASTERIZATION_MODE_BRESENHAM_KHR = 2,
	VK_LINE_RASTERIZATION_MODE_RECTANGULAR_SMOOTH_KHR = 3,
	VK_LINE_RASTERIZATION_MODE_DEFAULT_EXT = VK_LINE_RASTERIZATION_MODE_DEFAULT_KHR,
	VK_LINE_RASTERIZATION_MODE_RECTANGULAR_EXT = VK_LINE_RASTERIZATION_MODE_RECTANGULAR_KHR,
	VK_LINE_RASTERIZATION_MODE_BRESENHAM_EXT = VK_LINE_RASTERIZATION_MODE_BRESENHAM_KHR,
	VK_LINE_RASTERIZATION_MODE_RECTANGULAR_SMOOTH_EXT = VK_LINE_RASTERIZATION_MODE_RECTANGULAR_SMOOTH_KHR,
} VkLineRasterizationModeKHR;

// Provided by VK_KHR_line_rasterization
typedef struct VkPipelineRasterizationLineStateCreateInfoKHR {
	VkStructureType               sType;
	const void* pNext;
	VkLineRasterizationModeKHR    lineRasterizationMode;
	VkBool32                      stippledLineEnable;
	uint32_t                      lineStippleFactor;
	uint16_t                      lineStipplePattern;
} VkPipelineRasterizationLineStateCreateInfoKHR;



// Provided by VK_EXT_depth_bias_control
typedef struct VkDepthBiasInfoEXT {
	VkStructureType    sType;
	const void* pNext;
	float              depthBiasConstantFactor;
	float              depthBiasClamp;
	float              depthBiasSlopeFactor;
} VkDepthBiasInfoEXT;

// Provided by VK_EXT_depth_bias_control
void vkCmdSetDepthBias2EXT(
	VkCommandBuffer commandBuffer,
	const VkDepthBiasInfoEXT* pDepthBiasInfo) {

}

// Provided by VK_NV_cuda_kernel_launch
VK_DEFINE_NON_DISPATCHABLE_HANDLE(VkCudaFunctionNV)

// Provided by VK_NV_cuda_kernel_launch
typedef struct VkCudaLaunchInfoNV {
	VkStructureType sType;
	const void* pNext;
	VkCudaFunctionNV function;
	uint32_t gridDimX;
	uint32_t gridDimY;
	uint32_t gridDimZ;
	uint32_t blockDimX;
	uint32_t blockDimY;
	uint32_t blockDimZ;
	uint32_t sharedMemBytes;
	size_t paramCount;
	const void* const* pParams;
	size_t extraCount;
	const void* const* pExtras;
} VkCudaLaunchInfoNV;

// Provided by VK_NV_cuda_kernel_launch
void vkCmdCudaLaunchKernelNV(
	VkCommandBuffer commandBuffer,
	const VkCudaLaunchInfoNV* pLaunchInfo) {

}


// Provided by VK_EXT_frame_boundary
typedef VkFlags VkFrameBoundaryFlagsEXT;

// Provided by VK_EXT_frame_boundary
typedef struct VkFrameBoundaryEXT {
	VkStructureType            sType;
	const void* pNext;
	VkFrameBoundaryFlagsEXT    flags;
	uint64_t                   frameID;
	uint32_t                   imageCount;
	const VkImage* pImages;
	uint32_t                   bufferCount;
	const VkBuffer* pBuffers;
	uint64_t                   tagName;
	size_t                     tagSize;
	const void* pTag;
} VkFrameBoundaryEXT;


// Provided by VK_NV_low_latency2
typedef struct VkLatencySurfaceCapabilitiesNV {
	VkStructureType      sType;
	const void* pNext;
	uint32_t             presentModeCount;
	VkPresentModeKHR* pPresentModes;
} VkLatencySurfaceCapabilitiesNV;

// Provided by VK_NV_low_latency2
typedef struct VkSwapchainLatencyCreateInfoNV {
	VkStructureType    sType;
	const void* pNext;
	VkBool32           latencyModeEnable;
} VkSwapchainLatencyCreateInfoNV;




// Provided by VK_NV_displacement_micromap
typedef struct VkAccelerationStructureTrianglesDisplacementMicromapNV {
	VkStructureType                     sType;
	void* pNext;
	VkFormat                            displacementBiasAndScaleFormat;
	VkFormat                            displacementVectorFormat;
	VkDeviceOrHostAddressConstKHR       displacementBiasAndScaleBuffer;
	VkDeviceSize                        displacementBiasAndScaleStride;
	VkDeviceOrHostAddressConstKHR       displacementVectorBuffer;
	VkDeviceSize                        displacementVectorStride;
	VkDeviceOrHostAddressConstKHR       displacedMicromapPrimitiveFlags;
	VkDeviceSize                        displacedMicromapPrimitiveFlagsStride;
	VkIndexType                         indexType;
	VkDeviceOrHostAddressConstKHR       indexBuffer;
	VkDeviceSize                        indexStride;
	uint32_t                            baseTriangle;
	uint32_t                            usageCountsCount;
	const VkMicromapUsageEXT* pUsageCounts;
	const VkMicromapUsageEXT* const* ppUsageCounts;
	VkMicromapEXT                       micromap;
} VkAccelerationStructureTrianglesDisplacementMicromapNV;

typedef uint32_t StdVideoAV1Level;
// Provided by VK_KHR_video_decode_av1
typedef struct VkVideoDecodeAV1CapabilitiesKHR {
	VkStructureType     sType;
	void* pNext;
	StdVideoAV1Level    maxLevel;
} VkVideoDecodeAV1CapabilitiesKHR;


typedef VkFlags VkVideoEncodeH264CapabilityFlagsKHR;

typedef VkFlags VkVideoEncodeH264StdFlagsKHR;

// Provided by VK_KHR_video_encode_h264
typedef struct VkVideoEncodeH264CapabilitiesKHR {
	VkStructureType                        sType;
	void* pNext;
	VkVideoEncodeH264CapabilityFlagsKHR    flags;
	StdVideoH264LevelIdc                   maxLevelIdc;
	uint32_t                               maxSliceCount;
	uint32_t                               maxPPictureL0ReferenceCount;
	uint32_t                               maxBPictureL0ReferenceCount;
	uint32_t                               maxL1ReferenceCount;
	uint32_t                               maxTemporalLayerCount;
	VkBool32                               expectDyadicTemporalLayerPattern;
	int32_t                                minQp;
	int32_t                                maxQp;
	VkBool32                               prefersGopRemainingFrames;
	VkBool32                               requiresGopRemainingFrames;
	VkVideoEncodeH264StdFlagsKHR           stdSyntaxFlags;
} VkVideoEncodeH264CapabilitiesKHR;


typedef VkFlags VkVideoEncodeH265CapabilityFlagsKHR;

typedef VkFlags VkVideoEncodeH265StdFlagsKHR;

typedef VkFlags VkVideoEncodeH265CtbSizeFlagsKHR;

typedef VkFlags VkVideoEncodeH265TransformBlockSizeFlagsKHR;

// Provided by VK_KHR_video_encode_h265
typedef struct VkVideoEncodeH265CapabilitiesKHR {
	VkStructureType                                sType;
	void* pNext;
	VkVideoEncodeH265CapabilityFlagsKHR            flags;
	StdVideoH265LevelIdc                           maxLevelIdc;
	uint32_t                                       maxSliceSegmentCount;
	VkExtent2D                                     maxTiles;
	VkVideoEncodeH265CtbSizeFlagsKHR               ctbSizes;
	VkVideoEncodeH265TransformBlockSizeFlagsKHR    transformBlockSizes;
	uint32_t                                       maxPPictureL0ReferenceCount;
	uint32_t                                       maxBPictureL0ReferenceCount;
	uint32_t                                       maxL1ReferenceCount;
	uint32_t                                       maxSubLayerCount;
	VkBool32                                       expectDyadicTemporalSubLayerPattern;
	int32_t                                        minQp;
	int32_t                                        maxQp;
	VkBool32                                       prefersGopRemainingFrames;
	VkBool32                                       requiresGopRemainingFrames;
	VkVideoEncodeH265StdFlagsKHR                   stdSyntaxFlags;
} VkVideoEncodeH265CapabilitiesKHR;




// Provided by VK_KHR_video_encode_h264
typedef struct VkVideoEncodeH264SessionCreateInfoKHR {
	VkStructureType         sType;
	const void* pNext;
	VkBool32                useMaxLevelIdc;
	StdVideoH264LevelIdc    maxLevelIdc;
} VkVideoEncodeH264SessionCreateInfoKHR;

// Provided by VK_KHR_video_encode_h265
typedef struct VkVideoEncodeH265SessionCreateInfoKHR {
	VkStructureType         sType;
	const void* pNext;
	VkBool32                useMaxLevelIdc;
	StdVideoH265LevelIdc    maxLevelIdc;
} VkVideoEncodeH265SessionCreateInfoKHR;

typedef uint32_t StdVideoAV1SequenceHeader;//这里任意自定义一个

// Provided by VK_KHR_video_decode_av1
typedef struct VkVideoDecodeAV1SessionParametersCreateInfoKHR {
	VkStructureType                     sType;
	const void* pNext;
	const StdVideoAV1SequenceHeader* pStdSequenceHeader;
} VkVideoDecodeAV1SessionParametersCreateInfoKHR;


// Provided by VK_KHR_video_encode_h264
typedef struct VkVideoEncodeH264SessionParametersAddInfoKHR {
	VkStructureType                            sType;
	const void* pNext;
	uint32_t                                   stdSPSCount;
	const StdVideoH264SequenceParameterSet* pStdSPSs;
	uint32_t                                   stdPPSCount;
	const StdVideoH264PictureParameterSet* pStdPPSs;
} VkVideoEncodeH264SessionParametersAddInfoKHR;

typedef struct VkVideoEncodeH264SessionParametersCreateInfoKHR {
	VkStructureType sType;
	const void* pNext;
	uint32_t maxStdSPSCount;
	uint32_t maxStdPPSCount;
	const VkVideoEncodeH264SessionParametersAddInfoKHR* pParametersAddInfo;
} VkVideoEncodeH264SessionParametersCreateInfoKHR;

// Provided by VK_KHR_video_encode_h265
typedef struct VkVideoEncodeH265SessionParametersAddInfoKHR {
	VkStructureType                            sType;
	const void* pNext;
	uint32_t                                   stdVPSCount;
	const StdVideoH265VideoParameterSet* pStdVPSs;
	uint32_t                                   stdSPSCount;
	const StdVideoH265SequenceParameterSet* pStdSPSs;
	uint32_t                                   stdPPSCount;
	const StdVideoH265PictureParameterSet* pStdPPSs;
} VkVideoEncodeH265SessionParametersAddInfoKHR;

// Provided by VK_KHR_video_encode_h265
typedef struct VkVideoEncodeH265SessionParametersCreateInfoKHR {
	VkStructureType                                        sType;
	const void* pNext;
	uint32_t                                               maxStdVPSCount;
	uint32_t                                               maxStdSPSCount;
	uint32_t                                               maxStdPPSCount;
	const VkVideoEncodeH265SessionParametersAddInfoKHR* pParametersAddInfo;
} VkVideoEncodeH265SessionParametersCreateInfoKHR;


// Provided by VK_KHR_video_encode_queue
typedef struct VkVideoEncodeQualityLevelInfoKHR {
	VkStructureType    sType;
	const void* pNext;
	uint32_t           qualityLevel;
} VkVideoEncodeQualityLevelInfoKHR;


// Provided by VK_KHR_video_encode_h264
typedef struct VkVideoEncodeH264GopRemainingFrameInfoKHR {
	VkStructureType    sType;
	const void* pNext;
	VkBool32           useGopRemainingFrames;
	uint32_t           gopRemainingI;
	uint32_t           gopRemainingP;
	uint32_t           gopRemainingB;
} VkVideoEncodeH264GopRemainingFrameInfoKHR;

typedef VkFlags VkVideoEncodeH264RateControlFlagsKHR;

// Provided by VK_KHR_video_encode_h264
typedef struct VkVideoEncodeH264RateControlInfoKHR {
	VkStructureType                         sType;
	const void* pNext;
	VkVideoEncodeH264RateControlFlagsKHR    flags;
	uint32_t                                gopFrameCount;
	uint32_t                                idrPeriod;
	uint32_t                                consecutiveBFrameCount;
	uint32_t                                temporalLayerCount;
} VkVideoEncodeH264RateControlInfoKHR;

// Provided by VK_KHR_video_encode_h265
typedef struct VkVideoEncodeH265GopRemainingFrameInfoKHR {
	VkStructureType    sType;
	const void* pNext;
	VkBool32           useGopRemainingFrames;
	uint32_t           gopRemainingI;
	uint32_t           gopRemainingP;
	uint32_t           gopRemainingB;
} VkVideoEncodeH265GopRemainingFrameInfoKHR;

typedef VkFlags VkVideoEncodeH265RateControlFlagsKHR;

// Provided by VK_KHR_video_encode_h265
typedef struct VkVideoEncodeH265RateControlInfoKHR {
	VkStructureType                         sType;
	const void* pNext;
	VkVideoEncodeH265RateControlFlagsKHR    flags;
	uint32_t                                gopFrameCount;
	uint32_t                                idrPeriod;
	uint32_t                                consecutiveBFrameCount;
	uint32_t                                subLayerCount;
} VkVideoEncodeH265RateControlInfoKHR;

typedef uint32_t StdVideoDecodeAV1ReferenceInfo;//这里任意定义一个只做示例

// Provided by VK_KHR_video_decode_av1
typedef struct VkVideoDecodeAV1DpbSlotInfoKHR {
	VkStructureType                          sType;
	const void* pNext;
	const StdVideoDecodeAV1ReferenceInfo* pStdReferenceInfo;
} VkVideoDecodeAV1DpbSlotInfoKHR;

typedef uint32_t StdVideoEncodeH264ReferenceInfo;//这里任意定义一个只做示例

// Provided by VK_KHR_video_encode_h264
typedef struct VkVideoEncodeH264DpbSlotInfoKHR {
	VkStructureType                           sType;
	const void* pNext;
	const StdVideoEncodeH264ReferenceInfo* pStdReferenceInfo;
} VkVideoEncodeH264DpbSlotInfoKHR;

typedef uint32_t StdVideoEncodeH265ReferenceInfo;//这里任意定义一个只做示例

// Provided by VK_KHR_video_encode_h265
typedef struct VkVideoEncodeH265DpbSlotInfoKHR {
	VkStructureType                           sType;
	const void* pNext;
	const StdVideoEncodeH265ReferenceInfo* pStdReferenceInfo;
} VkVideoEncodeH265DpbSlotInfoKHR;



// Provided by VK_KHR_video_maintenance1
typedef struct VkVideoInlineQueryInfoKHR {
	VkStructureType    sType;
	const void* pNext;
	VkQueryPool        queryPool;
	uint32_t           firstQuery;
	uint32_t           queryCount;
} VkVideoInlineQueryInfoKHR;

typedef uint32_t StdVideoDecodeAV1PictureInfo;//这里任意定义一个只做示例

#define VK_MAX_VIDEO_AV1_REFERENCES_PER_FRAME_KHR 1 //这里任意定义一个只做示例

// Provided by VK_KHR_video_decode_av1
typedef struct VkVideoDecodeAV1PictureInfoKHR {
	VkStructureType                        sType;
	const void* pNext;
	const StdVideoDecodeAV1PictureInfo* pStdPictureInfo;
	int32_t                                referenceNameSlotIndices[VK_MAX_VIDEO_AV1_REFERENCES_PER_FRAME_KHR];
	uint32_t                               frameHeaderOffset;
	uint32_t                               tileCount;
	const uint32_t* pTileOffsets;
	const uint32_t* pTileSizes;
} VkVideoDecodeAV1PictureInfoKHR;


// Provided by VK_KHR_video_encode_h264
typedef struct VkVideoEncodeH264NaluSliceInfoKHR {
	VkStructureType                         sType;
	const void* pNext;
	int32_t                                 constantQp;
	const StdVideoEncodeH264SliceHeader* pStdSliceHeader;
} VkVideoEncodeH264NaluSliceInfoKHR;

// Provided by VK_KHR_video_encode_h264
typedef struct VkVideoEncodeH264PictureInfoKHR {
	VkStructureType                             sType;
	const void* pNext;
	uint32_t                                    naluSliceEntryCount;
	const VkVideoEncodeH264NaluSliceInfoKHR* pNaluSliceEntries;
	const StdVideoEncodeH264PictureInfo* pStdPictureInfo;
	VkBool32                                    generatePrefixNalu;
} VkVideoEncodeH264PictureInfoKHR;

// Provided by VK_KHR_video_encode_h265
typedef struct VkVideoEncodeH265NaluSliceSegmentInfoKHR {
	VkStructureType                                sType;
	const void* pNext;
	int32_t                                        constantQp;
	const StdVideoEncodeH265SliceSegmentHeader* pStdSliceSegmentHeader;
} VkVideoEncodeH265NaluSliceSegmentInfoKHR;

// Provided by VK_KHR_video_encode_h265
typedef struct VkVideoEncodeH265PictureInfoKHR {
	VkStructureType                                    sType;
	const void* pNext;
	uint32_t                                           naluSliceSegmentEntryCount;
	const VkVideoEncodeH265NaluSliceSegmentInfoKHR* pNaluSliceSegmentEntries;
	const StdVideoEncodeH265PictureInfo* pStdPictureInfo;
} VkVideoEncodeH265PictureInfoKHR;

// Provided by VK_KHR_video_encode_h264
typedef struct VkVideoEncodeH264QpKHR {
	int32_t    qpI;
	int32_t    qpP;
	int32_t    qpB;
} VkVideoEncodeH264QpKHR;

// Provided by VK_KHR_video_encode_h264
typedef struct VkVideoEncodeH264QualityLevelPropertiesKHR {
	VkStructureType                         sType;
	void* pNext;
	VkVideoEncodeH264RateControlFlagsKHR    preferredRateControlFlags;
	uint32_t                                preferredGopFrameCount;
	uint32_t                                preferredIdrPeriod;
	uint32_t                                preferredConsecutiveBFrameCount;
	uint32_t                                preferredTemporalLayerCount;
	VkVideoEncodeH264QpKHR                  preferredConstantQp;
	uint32_t                                preferredMaxL0ReferenceCount;
	uint32_t                                preferredMaxL1ReferenceCount;
	VkBool32                                preferredStdEntropyCodingModeFlag;
} VkVideoEncodeH264QualityLevelPropertiesKHR;


// Provided by VK_KHR_video_encode_h264
typedef struct VkVideoEncodeH264SessionParametersGetInfoKHR {
	VkStructureType    sType;
	const void* pNext;
	VkBool32           writeStdSPS;
	VkBool32           writeStdPPS;
	uint32_t           stdSPSId;
	uint32_t           stdPPSId;
} VkVideoEncodeH264SessionParametersGetInfoKHR;


// Provided by VK_KHR_video_encode_h264
typedef struct VkVideoEncodeH264SessionParametersFeedbackInfoKHR {
	VkStructureType    sType;
	void* pNext;
	VkBool32           hasStdSPSOverrides;
	VkBool32           hasStdPPSOverrides;
} VkVideoEncodeH264SessionParametersFeedbackInfoKHR;

// Provided by VK_KHR_video_encode_h264
typedef struct VkVideoEncodeH264FrameSizeKHR {
	uint32_t    frameISize;
	uint32_t    framePSize;
	uint32_t    frameBSize;
} VkVideoEncodeH264FrameSizeKHR;

// Provided by VK_KHR_video_encode_h264
typedef struct VkVideoEncodeH264RateControlLayerInfoKHR {
	VkStructureType                  sType;
	const void* pNext;
	VkBool32                         useMinQp;
	VkVideoEncodeH264QpKHR           minQp;
	VkBool32                         useMaxQp;
	VkVideoEncodeH264QpKHR           maxQp;
	VkBool32                         useMaxFrameSize;
	VkVideoEncodeH264FrameSizeKHR    maxFrameSize;
} VkVideoEncodeH264RateControlLayerInfoKHR;

// Provided by VK_KHR_video_encode_h265
typedef struct VkVideoEncodeH265QpKHR {
	int32_t    qpI;
	int32_t    qpP;
	int32_t    qpB;
} VkVideoEncodeH265QpKHR;

// Provided by VK_KHR_video_encode_h265
typedef struct VkVideoEncodeH265QualityLevelPropertiesKHR {
	VkStructureType                         sType;
	void* pNext;
	VkVideoEncodeH265RateControlFlagsKHR    preferredRateControlFlags;
	uint32_t                                preferredGopFrameCount;
	uint32_t                                preferredIdrPeriod;
	uint32_t                                preferredConsecutiveBFrameCount;
	uint32_t                                preferredSubLayerCount;
	VkVideoEncodeH265QpKHR                  preferredConstantQp;
	uint32_t                                preferredMaxL0ReferenceCount;
	uint32_t                                preferredMaxL1ReferenceCount;
} VkVideoEncodeH265QualityLevelPropertiesKHR;


// Provided by VK_KHR_video_encode_h265
typedef struct VkVideoEncodeH265SessionParametersGetInfoKHR {
	VkStructureType    sType;
	const void* pNext;
	VkBool32           writeStdVPS;
	VkBool32           writeStdSPS;
	VkBool32           writeStdPPS;
	uint32_t           stdVPSId;
	uint32_t           stdSPSId;
	uint32_t           stdPPSId;
} VkVideoEncodeH265SessionParametersGetInfoKHR;


// Provided by VK_KHR_video_encode_h265
typedef struct VkVideoEncodeH265SessionParametersFeedbackInfoKHR {
	VkStructureType    sType;
	void* pNext;
	VkBool32           hasStdVPSOverrides;
	VkBool32           hasStdSPSOverrides;
	VkBool32           hasStdPPSOverrides;
} VkVideoEncodeH265SessionParametersFeedbackInfoKHR;

// Provided by VK_KHR_video_encode_h265
typedef struct VkVideoEncodeH265FrameSizeKHR {
	uint32_t    frameISize;
	uint32_t    framePSize;
	uint32_t    frameBSize;
} VkVideoEncodeH265FrameSizeKHR;

// Provided by VK_KHR_video_encode_h265
typedef struct VkVideoEncodeH265RateControlLayerInfoKHR {
	VkStructureType                  sType;
	const void* pNext;
	VkBool32                         useMinQp;
	VkVideoEncodeH265QpKHR           minQp;
	VkBool32                         useMaxQp;
	VkVideoEncodeH265QpKHR           maxQp;
	VkBool32                         useMaxFrameSize;
	VkVideoEncodeH265FrameSizeKHR    maxFrameSize;
} VkVideoEncodeH265RateControlLayerInfoKHR;


// Provided by VK_KHR_vertex_attribute_divisor
typedef struct VkPhysicalDeviceVertexAttributeDivisorFeaturesKHR {
	VkStructureType sType;
	void* pNext;
	VkBool32 vertexAttributeInstanceRateDivisor;
	VkBool32 vertexAttributeInstanceRateZeroDivisor;
} VkPhysicalDeviceVertexAttributeDivisorFeaturesKHR;


// Provided by VK_QNX_external_memory_screen_buffer
typedef struct VkPhysicalDeviceExternalMemoryScreenBufferFeaturesQNX {
	VkStructureType sType;
	void* pNext;
	VkBool32 screenBufferImport;
} VkPhysicalDeviceExternalMemoryScreenBufferFeaturesQNX;


// Provided by VK_KHR_index_type_uint8
typedef struct VkPhysicalDeviceIndexTypeUint8FeaturesKHR {
	VkStructureType sType;
	void* pNext;
	VkBool32 indexTypeUint8;
} VkPhysicalDeviceIndexTypeUint8FeaturesKHR;


// Provided by VK_EXT_legacy_vertex_attributes
typedef struct VkPhysicalDeviceLegacyVertexAttributesFeaturesEXT {
	VkStructureType sType;
	void* pNext;
	VkBool32 legacyVertexAttributes;
} VkPhysicalDeviceLegacyVertexAttributesFeaturesEXT;


// Provided by VK_KHR_line_rasterization
typedef struct VkPhysicalDeviceLineRasterizationFeaturesKHR {
	VkStructureType sType;
	void* pNext;
	VkBool32 rectangularLines;
	VkBool32 bresenhamLines;
	VkBool32 smoothLines;
	VkBool32 stippledRectangularLines;
	VkBool32 stippledBresenhamLines;
	VkBool32 stippledSmoothLines;
} VkPhysicalDeviceLineRasterizationFeaturesKHR;


// Provided by VK_KHR_video_maintenance1
typedef struct VkPhysicalDeviceVideoMaintenance1FeaturesKHR {
	VkStructureType sType;
	void* pNext;
	VkBool32 videoMaintenance1;
} VkPhysicalDeviceVideoMaintenance1FeaturesKHR;



NS_TEST_END