#include "../common/Global.h"
#include "../common/TestBase.h"
NS_TEST_BEGIN

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

NS_TEST_END