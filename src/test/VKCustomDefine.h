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










NS_TEST_END