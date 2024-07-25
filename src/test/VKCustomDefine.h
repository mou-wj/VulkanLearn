#include "../common/Global.h"
#include "../common/TestBase.h"
NS_TEST_BEGIN

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


NS_TEST_END