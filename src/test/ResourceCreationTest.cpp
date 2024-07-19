#include "ResourceCreationTest.h"
#include <Windows.h>
#include <vulkan/vulkan_core.h>
#include <vulkan/vulkan_win32.h>
#include <winnt.h>
#include <vulkan/vulkan_metal.h>
#include <vulkan/vulkan_android.h>
typedef uint32_t zx_handle_t;//因为zx_handle_t 是google的开源操作系统fuchsia的句柄类型，所以这里定义一个uint32_t类型的句柄类型zx_handle_t，不起实际作用只是为了通过编译
#include <vulkan/vulkan_fuchsia.h>
#include <vulkan/vulkan_screen.h>

// Provided by VK_KHR_maintenance5
typedef VkFlags64 VkBufferUsageFlags2KHR;
// Provided by VK_KHR_maintenance5
// Flag bits for VkBufferUsageFlagBits2KHR
typedef VkFlags64 VkBufferUsageFlagBits2KHR;
static const VkBufferUsageFlagBits2KHR VK_BUFFER_USAGE_2_TRANSFER_SRC_BIT_KHR = //指定缓冲区可以用作transfer command的source（请参见VK_PIPELINE_STAGE_TRANSFER_BIT的定义)。
0x00000001ULL;
static const VkBufferUsageFlagBits2KHR VK_BUFFER_USAGE_2_TRANSFER_DST_BIT_KHR = //指定缓冲区可以用作transfer command的destination
0x00000002ULL;
static const VkBufferUsageFlagBits2KHR VK_BUFFER_USAGE_2_UNIFORM_TEXEL_BUFFER_BIT_KHR //指定缓冲区可以使用来创建适合于占用VK_DESCRIPTOR_TYPE_UNIFORM_TEXEL_BUFFER类型的VkDescriptorSet 的slot的VkBufferView。
= 0x00000004ULL;
static const VkBufferUsageFlagBits2KHR VK_BUFFER_USAGE_2_STORAGE_TEXEL_BUFFER_BIT_KHR //指定缓冲区可以使用来创建适合于占用VK_DESCRIPTOR_TYPE_STORAGE_TEXEL_BUFFER类型的VkDescriptorSet 的slot的VkBufferView。
= 0x00000008ULL;
static const VkBufferUsageFlagBits2KHR VK_BUFFER_USAGE_2_UNIFORM_BUFFER_BIT_KHR = //指定该缓冲区可以在适合于占用VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER或VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC类型的VkDescriptorSet 的slot的 的VkDescriptorBufferInfo中使用该缓冲区。
0x00000010ULL;
static const VkBufferUsageFlagBits2KHR VK_BUFFER_USAGE_2_STORAGE_BUFFER_BIT_KHR = //指定该缓冲区可以在适合于占用VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER 或 VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC.类型的VkDescriptorSet 的slot的 的VkDescriptorBufferInfo中使用该缓冲区。
0x00000020ULL;
static const VkBufferUsageFlagBits2KHR VK_BUFFER_USAGE_2_INDEX_BUFFER_BIT_KHR = //指定该缓冲区适合于作为参数传递给vkCmdBindIndexBuffer2KHR和vkCmdBindIndexBuffer。
0x00000040ULL;
static const VkBufferUsageFlagBits2KHR VK_BUFFER_USAGE_2_VERTEX_BUFFER_BIT_KHR = //指定该缓冲区适合于将其作为 pBuffers 数组的一个元素传递给vkCmdBindVertexBuffer。
0x00000080ULL;
static const VkBufferUsageFlagBits2KHR VK_BUFFER_USAGE_2_INDIRECT_BUFFER_BIT_KHR = //指定缓冲区适合于作为缓冲区参数传递给vkCmdDrawIndirect、vkCmdDrawIndexedIndirect、vkCmdDrawMeshTasksIndirectNV，vkCmdDrawMeshTasksIndirectCountNV，vkCmdDrawMeshTasksIndirectEXT，vkCmdDrawMeshTasksIndirectCountEXT，vkCmdDrawClusterIndirectHUAWEI，或 vkCmdDispatchIndirect。它也适用于作为VkIndirectCommandsStreamNV的buffer成员或 VkGeneratedCommandsInfoNV的sequencesCountBuffer ，sequencesIndexBuffer 或 preprocessedBuffer  成员
0x00000100ULL;
// Provided by VK_KHR_maintenance5 with VK_AMDX_shader_enqueue
static const VkBufferUsageFlagBits2KHR
VK_BUFFER_USAGE_2_EXECUTION_GRAPH_SCRATCH_BIT_AMDX = 0x02000000ULL; //指明缓冲区用于 execution graph dispatch 的 scratch memory  
// Provided by VK_KHR_maintenance5 with VK_EXT_conditional_rendering
static const VkBufferUsageFlagBits2KHR VK_BUFFER_USAGE_2_CONDITIONAL_RENDERING_BIT_EXT //指定缓冲区适合于作为缓冲区参数传递给vkCmdBeginConditionalRenderingEXT.
= 0x00000200ULL;
// Provided by VK_KHR_maintenance5 with VK_KHR_ray_tracing_pipeline
static const VkBufferUsageFlagBits2KHR VK_BUFFER_USAGE_2_SHADER_BINDING_TABLE_BIT_KHR //指定该缓冲区适合用来作为 Shader Binding Table.
= 0x00000400ULL;
// Provided by VK_KHR_maintenance5 with VK_NV_ray_tracing
static const VkBufferUsageFlagBits2KHR VK_BUFFER_USAGE_2_RAY_TRACING_BIT_NV = //指定该缓冲区适合在vkCmdTraceRaysNV中使用
0x00000400ULL;
// Provided by VK_KHR_maintenance5 with VK_EXT_transform_feedback
static const VkBufferUsageFlagBits2KHR
VK_BUFFER_USAGE_2_TRANSFORM_FEEDBACK_BUFFER_BIT_EXT = 0x00000800ULL; //指定该缓冲区适合用于与vkCmdBindTransformFeedbackBuffersEXT.中绑定作为转换反馈缓冲区
// Provided by VK_KHR_maintenance5 with VK_EXT_transform_feedback
static const VkBufferUsageFlagBits2KHR
VK_BUFFER_USAGE_2_TRANSFORM_FEEDBACK_COUNTER_BUFFER_BIT_EXT = 0x00001000ULL;//指定该缓冲区适合用于vkCmdBeginTransformFeedbackEXT和vkCmdEndTransformFeedbackEXT中作为计数器缓冲区
// Provided by VK_KHR_maintenance5 with VK_KHR_video_decode_queue
static const VkBufferUsageFlagBits2KHR VK_BUFFER_USAGE_2_VIDEO_DECODE_SRC_BIT_KHR = //指定在 video decode operation.中可以用作源视频位流缓冲区。
0x00002000ULL;
// Provided by VK_KHR_maintenance5 with VK_KHR_video_decode_queue
static const VkBufferUsageFlagBits2KHR VK_BUFFER_USAGE_2_VIDEO_DECODE_DST_BIT_KHR = //被保留以供将来使用。
0x00004000ULL;
// Provided by VK_KHR_maintenance5 with VK_KHR_video_encode_queue
static const VkBufferUsageFlagBits2KHR VK_BUFFER_USAGE_2_VIDEO_ENCODE_DST_BIT_KHR = //指定在 video encode operation 中，该缓冲区可以用作目标视频位流缓冲区。
0x00008000ULL;
// Provided by VK_KHR_maintenance5 with VK_KHR_video_encode_queue
static const VkBufferUsageFlagBits2KHR VK_BUFFER_USAGE_2_VIDEO_ENCODE_SRC_BIT_KHR = //被保留以供将来使用。
0x00010000ULL;
// Provided by VK_KHR_maintenance5 with (VK_VERSION_1_2 or VK_KHR_buffer_device_address) or VK_EXT_buffer_device_address
static const VkBufferUsageFlagBits2KHR VK_BUFFER_USAGE_2_SHADER_DEVICE_ADDRESS_BIT_KHR //指定缓冲区可以通过 vkGetBufferDeviceAddress 获取缓冲区设备地址，并使用该地址从shader中访问缓冲区的内存
= 0x00020000ULL;
// Provided by VK_KHR_acceleration_structure with VK_KHR_maintenance5
static const VkBufferUsageFlagBits2KHR
VK_BUFFER_USAGE_2_ACCELERATION_STRUCTURE_BUILD_INPUT_READ_ONLY_BIT_KHR = //指定该缓冲区适合用作 acceleration structure build.的只读输入。
0x00080000ULL;
// Provided by VK_KHR_acceleration_structure with VK_KHR_maintenance5
static const VkBufferUsageFlagBits2KHR
VK_BUFFER_USAGE_2_ACCELERATION_STRUCTURE_STORAGE_BIT_KHR = 0x00100000ULL; //指定该缓冲区适用于VkAccelerationStructureKHR的存储空间
// Provided by VK_KHR_maintenance5 with VK_EXT_descriptor_buffer
static const VkBufferUsageFlagBits2KHR
VK_BUFFER_USAGE_2_SAMPLER_DESCRIPTOR_BUFFER_BIT_EXT = 0x00200000ULL;//指定当缓冲区绑定为描述符缓冲区时指明缓冲区适合sampler 以及 combined image sampler descriptors。如果为 combined image sampler descriptors则还必须指定VK_BUFFER_USAGE_2_RESOURCE_DESCRIPTOR_BUFFER_BIT_EXT.
// Provided by VK_KHR_maintenance5 with VK_EXT_descriptor_buffer
static const VkBufferUsageFlagBits2KHR
VK_BUFFER_USAGE_2_RESOURCE_DESCRIPTOR_BUFFER_BIT_EXT = 0x00400000ULL;//指定缓冲区适合于在绑定为描述符缓冲区时包含resource descriptors。
// Provided by VK_KHR_maintenance5 with VK_EXT_descriptor_buffer
static const VkBufferUsageFlagBits2KHR
VK_BUFFER_USAGE_2_PUSH_DESCRIPTORS_DESCRIPTOR_BUFFER_BIT_EXT = 0x04000000ULL;//指定在绑定时，当使用push descriptors时，实现可以使用该缓冲区来支持push descriptors。
// Provided by VK_KHR_maintenance5 with VK_EXT_opacity_micromap
static const VkBufferUsageFlagBits2KHR
VK_BUFFER_USAGE_2_MICROMAP_BUILD_INPUT_READ_ONLY_BIT_EXT = 0x00800000ULL;
// Provided by VK_KHR_maintenance5 with VK_EXT_opacity_micromap
static const VkBufferUsageFlagBits2KHR VK_BUFFER_USAGE_2_MICROMAP_STORAGE_BIT_EXT =
0x01000000ULL;




// Provided by VK_KHR_maintenance5
typedef struct VkBufferUsageFlags2CreateInfoKHR {
	VkStructureType           sType;
	const void* pNext;
	VkBufferUsageFlags2KHR    usage;
} VkBufferUsageFlags2CreateInfoKHR;



// Provided by VK_QNX_external_memory_screen_buffer
typedef struct VkExternalFormatQNX {
	VkStructureType    sType;
	void* pNext;
	uint64_t           externalFormat;
} VkExternalFormatQNX;


// Provided by VK_MESA_image_alignment_control
typedef struct VkImageAlignmentControlCreateInfoMESA {
	VkStructureType    sType;
	const void* pNext;
	uint32_t           maximumRequestedAlignment;
} VkImageAlignmentControlCreateInfoMESA;

NS_TEST_BEGIN


ResourceCreationTest::ResourceCreationTest()
{
}

void ResourceCreationTest::run()
{
}

ResourceCreationTest::~ResourceCreationTest()
{
}

struct BufferCreateInfoEXT {

	VkBufferCollectionBufferCreateInfoFUCHSIA	bufferCollectionBufferCreateInfoFUCHSIA{};
	VkBufferDeviceAddressCreateInfoEXT 		bufferDeviceAddressCreateInfoEXT{};
	VkBufferOpaqueCaptureAddressCreateInfo 	bufferOpaqueCaptureAddressCreateInfo{};
	VkBufferUsageFlags2CreateInfoKHR 		bufferUsageFlags2CreateInfoKHR{};
	VkDedicatedAllocationBufferCreateInfoNV 	dedicatedAllocationBufferCreateInfoNV{};
	VkExternalMemoryBufferCreateInfo 		externalMemoryBufferCreateInfo{};
	VkOpaqueCaptureDescriptorDataCreateInfoEXT opaqueCaptureDescriptorDataCreateInfoEXT{};
	VkVideoProfileListInfoKHR videoProfileListInfoKHR{};
	BufferCreateInfoEXT() {
		Init();
	}
	void Init() {
		bufferCollectionBufferCreateInfoFUCHSIA.sType = VK_STRUCTURE_TYPE_BUFFER_COLLECTION_BUFFER_CREATE_INFO_FUCHSIA;
		bufferCollectionBufferCreateInfoFUCHSIA.pNext = &bufferDeviceAddressCreateInfoEXT;
		bufferDeviceAddressCreateInfoEXT.sType = VK_STRUCTURE_TYPE_BUFFER_DEVICE_ADDRESS_CREATE_INFO_EXT;
		bufferDeviceAddressCreateInfoEXT.pNext = &bufferOpaqueCaptureAddressCreateInfo;
		bufferOpaqueCaptureAddressCreateInfo.sType = VK_STRUCTURE_TYPE_BUFFER_OPAQUE_CAPTURE_ADDRESS_CREATE_INFO;
		bufferOpaqueCaptureAddressCreateInfo.pNext = &bufferUsageFlags2CreateInfoKHR;
		bufferUsageFlags2CreateInfoKHR.sType = VK_STRUCTURE_TYPE_MAX_ENUM;//没有定义则先设置为VK_STRUCTURE_TYPE_MAX_ENUM
		bufferUsageFlags2CreateInfoKHR.pNext = &dedicatedAllocationBufferCreateInfoNV;
		dedicatedAllocationBufferCreateInfoNV.sType = VK_STRUCTURE_TYPE_DEDICATED_ALLOCATION_BUFFER_CREATE_INFO_NV;
		dedicatedAllocationBufferCreateInfoNV.pNext = &externalMemoryBufferCreateInfo;
		externalMemoryBufferCreateInfo.sType = VK_STRUCTURE_TYPE_EXTERNAL_MEMORY_BUFFER_CREATE_INFO;
		externalMemoryBufferCreateInfo.pNext = &opaqueCaptureDescriptorDataCreateInfoEXT;
		opaqueCaptureDescriptorDataCreateInfoEXT.sType = VK_STRUCTURE_TYPE_OPAQUE_CAPTURE_DESCRIPTOR_DATA_CREATE_INFO_EXT;
		opaqueCaptureDescriptorDataCreateInfoEXT.pNext = &videoProfileListInfoKHR;
		videoProfileListInfoKHR.sType = VK_STRUCTURE_TYPE_VIDEO_PROFILE_LIST_INFO_KHR;
		videoProfileListInfoKHR.pNext = nullptr;
		


	}
};

void ResourceCreationTest::BufferCreateTest()
{
	VkBuffer buffer{ VK_NULL_HANDLE };
	VkBufferCreateInfo bufferCreateInfo{};
	bufferCreateInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
		BufferCreateInfoEXT bufferCreateInfoEXT{};
	bufferCreateInfo.pNext = &bufferCreateInfoEXT.bufferCollectionBufferCreateInfoFUCHSIA;
	bufferCreateInfo.flags = 0;/*是 VkBufferCreateFlagBits组合值的一个位掩码，指定缓冲区的附加参数。
	VkBufferCreateFlagBits：
	
    VK_BUFFER_CREATE_SPARSE_BINDING_BIT:    指明 buffer 将使用sparse memory binding来备份缓冲区.
    VK_BUFFER_CREATE_SPARSE_RESIDENCY_BIT:    指明 buffer 将使用sparse memory binding来部分备份缓冲区. 以该flag创建则必须也要以VK_BUFFER_CREATE_SPARSE_BINDING_BIT创建
    VK_BUFFER_CREATE_SPARSE_ALIASED_BIT:    指明 buffer 将使用内存范围会同时备份到其他buffer（或该buffer的不同部分）的 sparse memory binding来备份缓冲区，以该flag创建则必须也要以VK_BUFFER_CREATE_SPARSE_BINDING_BIT创建
    VK_BUFFER_CREATE_PROTECTED_BIT:    指明buffer是一个 protected buffer.
    VK_BUFFER_CREATE_DEVICE_ADDRESS_CAPTURE_REPLAY_BIT:    指明buffer的地址可以在后续的运行中被保留或重用，参见VkBufferOpaqueCaptureAddressCreateInfo 
    VK_BUFFER_CREATE_DESCRIPTOR_BUFFER_CAPTURE_REPLAY_BIT_EXT:   指明buffer 可以在capturing 和 replaying (e.g. for trace capture and replay)中用作descriptor buffers ，参见VkOpaqueCaptureDescriptorDataCreateInfoEXT
    VK_BUFFER_CREATE_VIDEO_PROFILE_INDEPENDENT_BIT_KHR:   指明buffer可以用在video coding operations中而不需要在buffer创建的时间指明buffer 被使用时需要的video profiles集 
	
	*/
	bufferCreateInfo.queueFamilyIndexCount = 0;//是pQueueFamilyIndices中的队列族索引索引个数
	bufferCreateInfo.pQueueFamilyIndices = VK_NULL_HANDLE;//是指向将访问此buffer的队列族索引数组的指针。如果共享模式不是VK_SHARING_MODE_CONCURRENT，则被忽略
	bufferCreateInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;//是一个 VkSharingMode 值，指定buffer被多个队列族访问时的共享模式。
	bufferCreateInfo.size = 1;//是要创建的缓冲区的字节大小
	bufferCreateInfo.usage = VK_BUFFER_USAGE_VERTEX_BUFFER_BIT;/* 是 VkBufferUsageFlagBits组合值的位掩码，指定buffer的用途
	
	
    VK_BUFFER_USAGE_TRANSFER_SRC_BIT： 指定缓冲区可以用作transfer command的source（请参见VK_PIPELINE_STAGE_TRANSFER_BIT的定义)。
    VK_BUFFER_USAGE_TRANSFER_DST_BIT: 指定缓冲区可以用作transfer command的destination（请参见VK_PIPELINE_STAGE_TRANSFER_BIT的定义)。
    VK_BUFFER_USAGE_UNIFORM_TEXEL_BUFFER_BIT:  指定缓冲区可以使用来创建适合于占用VK_DESCRIPTOR_TYPE_UNIFORM_TEXEL_BUFFER类型的VkDescriptorSet 的slot的VkBufferView。
    VK_BUFFER_USAGE_STORAGE_TEXEL_BUFFER_BIT:  指定缓冲区可以使用来创建适合于占用VK_DESCRIPTOR_TYPE_STORAGE_TEXEL_BUFFER类型的VkDescriptorSet 的slot的VkBufferView。
    VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT:  指定该缓冲区可以在适合于占用VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER或VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC类型的VkDescriptorSet 的slot的 的VkDescriptorBufferInfo中使用该缓冲区。
    VK_BUFFER_USAGE_STORAGE_BUFFER_BIT:  指定该缓冲区可以在适合于占用VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER 或 VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC.类型的VkDescriptorSet 的slot的 的VkDescriptorBufferInfo中使用该缓冲区。
    VK_BUFFER_USAGE_INDEX_BUFFER_BIT: 指定该缓冲区适合于作为参数传递给vkCmdBindIndexBuffer2KHR和vkCmdBindIndexBuffer。
    VK_BUFFER_USAGE_VERTEX_BUFFER_BIT:    指定该缓冲区适合于将其作为 pBuffers 数组的一个元素传递给vkCmdBindVertexBuffer。
    VK_BUFFER_USAGE_INDIRECT_BUFFER_BIT:    指定缓冲区适合于作为缓冲区参数传递给vkCmdDrawIndirect、vkCmdDrawIndexedIndirect、vkCmdDrawMeshTasksIndirectNV，vkCmdDrawMeshTasksIndirectCountNV，vkCmdDrawMeshTasksIndirectEXT，vkCmdDrawMeshTasksIndirectCountEXT，vkCmdDrawClusterIndirectHUAWEI，或 vkCmdDispatchIndirect。它也适用于作为VkIndirectCommandsStreamNV的buffer成员或 VkGeneratedCommandsInfoNV的sequencesCountBuffer ，sequencesIndexBuffer 或 preprocessedBuffer  成员
    VK_BUFFER_USAGE_CONDITIONAL_RENDERING_BIT_EXT:   指定缓冲区适合于作为缓冲区参数传递给vkCmdBeginConditionalRenderingEXT.
    VK_BUFFER_USAGE_TRANSFORM_FEEDBACK_BUFFER_BIT_EXT:    指定该缓冲区适合用于与vkCmdBindTransformFeedbackBuffersEXT.中绑定作为转换反馈缓冲区
    VK_BUFFER_USAGE_TRANSFORM_FEEDBACK_COUNTER_BUFFER_BIT_EXT:    指定该缓冲区适合用于vkCmdBeginTransformFeedbackEXT和vkCmdEndTransformFeedbackEXT中作为计数器缓冲区
    VK_BUFFER_USAGE_SAMPLER_DESCRIPTOR_BUFFER_BIT_EXT:    指定当缓冲区绑定为描述符缓冲区时指明缓冲区适合sampler 以及 combined image sampler descriptors。如果为 combined image sampler descriptors则还必须指定VK_BUFFER_USAGE_RESOURCE_DESCRIPTOR_BUFFER_BIT_EXT.
    VK_BUFFER_USAGE_RESOURCE_DESCRIPTOR_BUFFER_BIT_EXT:    指定缓冲区适合于在绑定为描述符缓冲区时包含resource descriptors。.
    VK_BUFFER_USAGE_PUSH_DESCRIPTORS_DESCRIPTOR_BUFFER_BIT_EXT:    指定在绑定时，当使用push descriptors时，实现可以使用该缓冲区来支持push descriptors。
    VK_BUFFER_USAGE_RAY_TRACING_BIT_NV:   指定该缓冲区适合在vkCmdTraceRaysNV中使用
    VK_BUFFER_USAGE_SHADER_BINDING_TABLE_BIT_KHR:    指定该缓冲区适合用来作为 Shader Binding Table.
    VK_BUFFER_USAGE_ACCELERATION_STRUCTURE_BUILD_INPUT_READ_ONLY_BIT_KHR:   指定该缓冲区适合用作 acceleration structure build.的只读输入。
    VK_BUFFER_USAGE_ACCELERATION_STRUCTURE_STORAGE_BIT_KHR:    指定该缓冲区适用于VkAccelerationStructureKHR的存储空间
    VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT:    指定缓冲区可以通过 vkGetBufferDeviceAddress 获取缓冲区设备地址，并使用该地址从shader中访问缓冲区的内存
    VK_BUFFER_USAGE_VIDEO_DECODE_SRC_BIT_KHR:    指定在 video decode operation.中可以用作源视频位流缓冲区。 
    VK_BUFFER_USAGE_VIDEO_DECODE_DST_BIT_KHR :   被保留将来使用。
    VK_BUFFER_USAGE_VIDEO_ENCODE_DST_BIT_KHR:   指定在 video encode operation 中，该缓冲区可以用作目标视频位流缓冲区。 
    VK_BUFFER_USAGE_VIDEO_ENCODE_SRC_BIT_KHR:   被保留将来使用。
    VK_BUFFER_USAGE_EXECUTION_GRAPH_SCRATCH_BIT_AMDX:   指明缓冲区用于 execution graph dispatch 的 scratch memory  
	*/

	
	
	
	
	
	/*
	VkBufferCreateInfo有效用法：
	1.如果pNext中包含一个VkBufferUsageFlags2CreateInfoKHR结构体，则usage必须是有效的VkBufferUsageFlagBits组合值。且不再使用VkBufferCreateInfo.usage
	2.如果pNext中不包含一个VkBufferUsageFlags2CreateInfoKHR结构体，则usage就不能为 0
	3.size必须大于0
	4.如果sharingMode为 VK_SHARING_MODE_CONCURRENT，则（1）pQueueFamilyIndices 必须为有效的queueFamilyIndexCount 个uint32_t 值表明队列簇索引的数组指针
	（2）queueFamilyIndexCount必须大于 1
	（3）pQueueFamilyIndices中的每个元素必须是唯一的，且必须小于 vkGetPhysicalDeviceQueueFamilyProperties2 或 vkGetPhysicalDeviceQueueFamilyProperties 接口返回的physicalDevice的pQueueFamilyPropertyCount（表明有多少个队列簇）值
	5.如果sparseBinding 特性没有开启， flags 不能包含 VK_BUFFER_CREATE_SPARSE_BINDING_BIT
	6.如果sparseResidencyBuffer 特性没有开启，flags 不能包含VK_BUFFER_CREATE_SPARSE_RESIDENCY_BIT
	7.如果sparseResidencyAliased 特性没有开启，flags 不能包含VK_BUFFER_CREATE_SPARSE_ALIASED_BIT
	8.如果flags 包含VK_BUFFER_CREATE_SPARSE_RESIDENCY_BIT 或VK_BUFFER_CREATE_SPARSE_ALIASED_BIT，则其必须也包含VK_BUFFER_CREATE_SPARSE_BINDING_BIT
	9.如果pNext中包含一个VkExternalMemoryBufferCreateInfo，该结构体的handleTypes成员必须只包含 VkExternalBufferProperties::externalMemoryProperties.compatibleHandleTypes 中有的VkExternalMemoryHandleTypeFlagBits值，VkExternalBufferProperties::externalMemoryProperties.compatibleHandleTypes
					可以用过传入一个pExternalBufferInfo->handleType 为 VkExternalMemoryBufferCreateInfo::handleTypes的任意一个类型调用vkGetPhysicalDeviceExternalBufferProperties 来获得返回的值
	10.如果protectedMemory 特性没有开启，flags 不能包含VK_BUFFER_CREATE_PROTECTED_BIT
	11.如果flags中包含VK_BUFFER_CREATE_SPARSE_BINDING_BIT, VK_BUFFER_CREATE_SPARSE_RESIDENCY_BIT, 或者 VK_BUFFER_CREATE_SPARSE_ALIASED_BIT 任何一个，则便不能再包含VK_BUFFER_CREATE_PROTECTED_BIT
	12.如果pNext中包含一个dedicatedAllocation为VK_TRUE的 VkDedicatedAllocationBufferCreateInfoNV，则flags不能包含VK_BUFFER_CREATE_SPARSE_BINDING_BIT, VK_BUFFER_CREATE_SPARSE_RESIDENCY_BIT, 或者 VK_BUFFER_CREATE_SPARSE_ALIASED_BIT
	13.如果VkBufferDeviceAddressCreateInfoEXT::deviceAddress 不为0，flags 必须包含VK_BUFFER_CREATE_DEVICE_ADDRESS_CAPTURE_REPLAY_BIT
	14.如果VkBufferOpaqueCaptureAddressCreateInfo::opaqueCaptureAddress 不为0，flags 必须包含VK_BUFFER_CREATE_DEVICE_ADDRESS_CAPTURE_REPLAY_BIT
	15.如果flags 包含VK_BUFFER_CREATE_DEVICE_ADDRESS_CAPTURE_REPLAY_BIT，则bufferDeviceAddressCaptureReplay 特性必须开启
	16.如果usage 包含VK_BUFFER_USAGE_VIDEO_DECODE_SRC_BIT_KHR 或 VK_BUFFER_USAGE_VIDEO_DECODE_DST_BIT_KHR，且flags 不包含VK_BUFFER_CREATE_VIDEO_PROFILE_INDEPENDENT_BIT_KHR，则pNext中必须包含一个profileCount 大于0且pProfiles 包含至少一个videoCodecOperation指明了解码操作的VkVideoProfileInfoKHR 的VkVideoProfileListInfoKHR
	17.如果usage 包含VK_BUFFER_USAGE_VIDEO_ENCODE_SRC_BIT_KHR 或 VK_BUFFER_USAGE_VIDEO_ENCODE_DST_BIT_KHR，且flags 不包含VK_BUFFER_CREATE_VIDEO_PROFILE_INDEPENDENT_BIT_KHR，则pNext中必须包含一个profileCount 大于0且pProfiles 包含至少一个videoCodecOperation指明了编码操作的VkVideoProfileInfoKHR 的VkVideoProfileListInfoKHR
	18.如果flags包含VK_BUFFER_CREATE_VIDEO_PROFILE_INDEPENDENT_BIT_KHR，则videoMaintenance1 必须开启
	19.size 必须小于或等于 VkPhysicalDeviceMaintenance4Properties::maxBufferSize
	20.如果usage 包含VK_BUFFER_USAGE_SAMPLER_DESCRIPTOR_BUFFER_BIT_EXT，创建这个VkBuffer必须不导致所有有效的使用VK_BUFFER_USAGE_SAMPLER_DESCRIPTOR_BUFFER_BIT_EXT的 VkBuffer的space 的总和超过  VkPhysicalDeviceDescriptorBufferPropertiesEXT::samplerDescriptorBufferAddressSpaceSize 或 VkPhysicalDeviceDescriptorBufferPropertiesEXT::descriptorBufferAddressSpaceSize 
	21.如果usage 包含VK_BUFFER_USAGE_RESOURCE_DESCRIPTOR_BUFFER_BIT_EXT，创建这个VkBuffer必须不导致所有有效的使用VK_BUFFER_USAGE_SAMPLER_DESCRIPTOR_BUFFER_BIT_EXT的 VkBuffer的space 的总和超过  VkPhysicalDeviceDescriptorBufferPropertiesEXT::resourceDescriptorBufferAddressSpaceSize 或 VkPhysicalDeviceDescriptorBufferPropertiesEXT::descriptorBufferAddressSpaceSize 
	22.如果flags包含VK_BUFFER_CREATE_DESCRIPTOR_BUFFER_CAPTURE_REPLAY_BIT_EXT，则descriptorBufferCaptureReplay 特性必须开启
	23.如果pNext中包含一个  VkOpaqueCaptureDescriptorDataCreateInfoEXT，flags 必须包含VK_BUFFER_CREATE_DESCRIPTOR_BUFFER_CAPTURE_REPLAY_BIT_EXT
	24.如果usage 包含VK_BUFFER_USAGE_PUSH_DESCRIPTORS_DESCRIPTOR_BUFFER_BIT_EXT，则（1）descriptorBufferPushDescriptors 特性必须开启
																				   （2）VkPhysicalDeviceDescriptorBufferPropertiesEXT::bufferlessPushDescriptors 必须为VK_FALSE
																				   （3）usage 必须至少包含VK_BUFFER_USAGE_RESOURCE_DESCRIPTOR_BUFFER_BIT_EXT 或 VK_BUFFER_USAGE_SAMPLER_DESCRIPTOR_BUFFER_BIT_EXT
	25.如果flags 包含VK_BUFFER_CREATE_PROTECTED_BIT，则usage 不能包含任何一个 VK_BUFFER_USAGE_TRANSFORM_FEEDBACK_BUFFER_BIT_EXT, VK_BUFFER_USAGE_TRANSFORM_FEEDBACK_COUNTER_BUFFER_BIT_EXT, VK_BUFFER_USAGE_CONDITIONAL_RENDERING_BIT_EXT, VK_BUFFER_USAGE_ACCELERATION_STRUCTURE_BUILD_INPUT_READ_ONLY_BIT_KHR, VK_BUFFER_USAGE_ACCELERATION_STRUCTURE_STORAGE_BIT_KHR, VK_BUFFER_USAGE_SHADER_BINDING_TABLE_BIT_KHR, 
																	VK_BUFFER_USAGE_SAMPLER_DESCRIPTOR_BUFFER_BIT_EXT, VK_BUFFER_USAGE_RESOURCE_DESCRIPTOR_BUFFER_BIT_EXT, VK_BUFFER_USAGE_PUSH_DESCRIPTORS_DESCRIPTOR_BUFFER_BIT_EXT, VK_BUFFER_USAGE_MICROMAP_BUILD_INPUT_READ_ONLY_BIT_EXT, VK_BUFFER_USAGE_MICROMAP_STORAGE_BIT
	*/


	//VkBufferUsageFlags2CreateInfoKHR
	VkBufferUsageFlags2CreateInfoKHR& bufferUsageFlags2CreateInfoKHR = bufferCreateInfoEXT.bufferUsageFlags2CreateInfoKHR;
	bufferUsageFlags2CreateInfoKHR.usage = 0;//是一个 VkBufferUsageFlagBits2KHR 组合值的位掩码，指定缓冲区的允许使用。



	//VkDedicatedAllocationBufferCreateInfoNV
	//VkDedicatedAllocationBufferCreateInfoNV 结构体用于控制创建具有专用分配的缓冲区。
	VkDedicatedAllocationBufferCreateInfoNV& dedicatedAllocationBufferCreateInfoNV = bufferCreateInfoEXT.dedicatedAllocationBufferCreateInfoNV;
	dedicatedAllocationBufferCreateInfoNV.dedicatedAllocation = VK_FALSE;//指定缓冲区是否将有一个绑定到它的专用分配。

	//VkExternalMemoryBufferCreateInfo
	//VkExternalMemoryBufferCreateInfo 结构体用于定义可以用作缓冲区的备份存储区的外部内存的句柄类型
	VkExternalMemoryBufferCreateInfo& externalMemoryBufferCreateInfo = bufferCreateInfoEXT.externalMemoryBufferCreateInfo;
	externalMemoryBufferCreateInfo.handleTypes = VK_EXTERNAL_MEMORY_HANDLE_TYPE_OPAQUE_FD_BIT;//是VkExternalMemoryHandleTypeFlagBits组合值的位掩码，指明一个或多个外部内存句柄类型，可以用于缓冲区备份存储区。


	//VkBufferOpaqueCaptureAddressCreateInfo
	// VkBufferOpaqueCaptureAddressCreateInfo等价于VkBufferOpaqueCaptureAddressCreateInfoKHR
	//VkBufferOpaqueCaptureAddressCreateInfo 结构体用于为一个缓冲区请求一个特定的设备地址
	VkBufferOpaqueCaptureAddressCreateInfo& bufferOpaqueCaptureAddressCreateInfo = bufferCreateInfoEXT.bufferOpaqueCaptureAddressCreateInfo;
	bufferOpaqueCaptureAddressCreateInfo.opaqueCaptureAddress = NULL;//是buffer的不透明捕获地址。如果为NULL,表示不请求地址。如果不为NULL，则必须为用以buffer调用vkGetBufferOpaqueCaptureAddress 返回的地址


	//VkBufferDeviceAddressCreateInfoEXT
	//VkBufferDeviceAddressCreateInfoEXT为一个缓冲区请求一个特定的设备地址
	VkBufferDeviceAddressCreateInfoEXT& bufferDeviceAddressCreateInfoEXT = bufferCreateInfoEXT.bufferDeviceAddressCreateInfoEXT;
	bufferDeviceAddressCreateInfoEXT.deviceAddress = NULL;//是buffer请求的设备地址。如果为NULL,表示不请求设备地址。如果不为NULL，则它必须是从同一实现上相同创建的缓冲区中检索到的地址。缓冲区还必须绑定到一个相同创建的VkDeviceMemory


	//VkBufferCollectionBufferCreateInfoFUCHSIA
	//
	VkBufferCollectionBufferCreateInfoFUCHSIA& bufferCollectionBufferCreateInfoFUCHSIA = bufferCreateInfoEXT.bufferCollectionBufferCreateInfoFUCHSIA;
	bufferCollectionBufferCreateInfoFUCHSIA.collection; //为 VkBufferCollectionFUCHSIA 的句柄
	bufferCollectionBufferCreateInfoFUCHSIA.index = 0;//是 collection 中的索引，指明这个缓冲区在 collection 中的位置以及从哪个内存导入。





	vkCreateBuffer(device, &bufferCreateInfo, nullptr, &buffer);/*
	vkCreateBuffer有效用法:
	1.如果pCreateInfo 中的flags包含VK_BUFFER_CREATE_SPARSE_BINDING_BIT，且extendedSparseAddressSpace 特性没有开启，则（1）创建这个VkBuffer 需要的sparse memory数量不能导致在device上 的所有有效的sparse resources memory的总和超过 VkPhysicalDeviceLimits::sparseAddressSpaceSize
																													 （2）如果pCreateInfo的usage包含VkPhysicalDeviceExtendedSparseAddressSpacePropertiesNV::extendedSparseBufferUsageFlags 中不含有的比特位，则在去除了pCreateInfo的flags中包含VkPhysicalDeviceExtendedSparseAddressSpacePropertiesNV::extendedSparseBufferUsageFlags比特位创建的VkBuffer和VkImage后，
																															创建这个VkBuffer 需要的sparse memory数量不能导致在device上 的所有有效的sparse resources memory的总和超过 VkPhysicalDeviceLimits::sparseAddressSpaceSize
	2.如果pCreateInfo 中的flags包含VK_BUFFER_CREATE_SPARSE_BINDING_BIT，且extendedSparseAddressSpace 特性开启，创建这个VkBuffer 需要的sparse resources数量不能导致在device上 的所有有效的sparse resources的总和超过 VkPhysicalDeviceExtendedSparseAddressSpacePropertiesNV::extendedSparseAddressSpaceSize

	3.如果为了在pCreateInfo的pNext中加入一个VkBufferCollectionBufferCreateInfoFUCHSIA导入一个VkBufferCollectionFUCHSIA 而使用这个VkBuffer，则 pCreateInfo必须匹配 调用vkSetBufferCollectionBufferConstraintsFUCHSIA设置buffer collection的限制的时候的 VkBufferConstraintsInfoFUCHSIA::createInfo

	*/

	vkDestroyBuffer(device, buffer, nullptr);








}

void ResourceCreationTest::BufferViewCreateTest()
{
	//buffer view表示了缓冲区的连续范围和用于解释数据的特定格式。buffer view使着色器能够使用图像操作访问缓冲区内容

	VkBuffer allocatedBuffer;
	VkBufferView bufferView;

	VkBufferViewCreateInfo bufferViewCreateInfo{};
	bufferViewCreateInfo.sType = VK_STRUCTURE_TYPE_BUFFER_VIEW_CREATE_INFO;
	bufferViewCreateInfo.pNext = nullptr;//可以含有VkBufferUsageFlags2CreateInfoKHR 或 VkExportMetalObjectCreateInfoEXT
	bufferViewCreateInfo.flags = 0;//保留将来使用
	bufferViewCreateInfo.buffer = allocatedBuffer;//指buffer view将创建哪个buffer的view
	bufferViewCreateInfo.offset = 0;//是与buffer的基本地址之间以字节为单位的偏移量。从着色器访问buffer view时，将使用相对于此起始偏移量的寻址。
	bufferViewCreateInfo.range = VK_WHOLE_SIZE;//是buffer view的字节大小。如果范围等于VK_WHOLE_SIZE，则使用从offset到buffer 结束这个范围。如果使用VK_WHOLE_SIZE，并且缓冲区的剩余大小不是这个format的  texel block size的倍数，则使用最近的较小的倍数。
	bufferViewCreateInfo.format = VK_FORMAT_S8_UINT;//是一个描述buffer中数据元素的格式的VkFormat
	/*
	VkBufferViewCreateInfo有效用法：
	1.offset 必须小于buffer的大小
	2.如果range 不等于VK_WHOLE_SIZE，则（1）range 必须大于0，且必须是format的texel block size的整数倍
									   （2）texel buffer 元素的数量(range / (texel block size)) × (texels per block))必须小于 VkPhysicalDeviceLimits::maxTexelBufferElements，其中texel block size和texels per block是在Compatible Formats表中的该format定义的(texel block size是format的字节大小，texels per block是format的texel块的数量)。
									   （3）offset + range 必须小于或等于buffer的大小
	3.如果range 等于VK_WHOLE_SIZE，则（1）texel buffer 元素的数量((size - offset) / (texel block size)) × (texels per block))必须小于 VkPhysicalDeviceLimits::maxTexelBufferElements，其中size对应buffer的大小 ,texel block size和texels per block是在Compatible Formats表中的该format定义的(texel block size是format的字节大小，texels per block是format的texel块的数量)。
	4.buffer的创建必须含有至少VK_BUFFER_USAGE_UNIFORM_TEXEL_BUFFER_BIT 或 VK_BUFFER_USAGE_STORAGE_TEXEL_BUFFER_BIT中的一个
	5.如果buffer view usage 包含VK_BUFFER_USAGE_UNIFORM_TEXEL_BUFFER_BIT，则format的 format features 包含 VK_FORMAT_FEATURE_UNIFORM_TEXEL_BUFFER_BIT
	6.如果buffer view usage 包含VK_BUFFER_USAGE_STORAGE_TEXEL_BUFFER_BIT，则format的 format features 包含 VK_FORMAT_FEATURE_STORAGE_TEXEL_BUFFER_BIT
	7.如果buffer 不是sparse,则buffer必须绑定到一个完整的连续的VkDeviceMemory对象
	8.如果texelBufferAlignment 特性没有开启，则offset 必须是 VkPhysicalDeviceLimits::minTexelBufferOffsetAlignment 的整数倍
	9.如果texelBufferAlignment 特性开启，且如果buffer创建时以VK_BUFFER_USAGE_STORAGE_TEXEL_BUFFER_BIT创建， 则offset 必须是 VkPhysicalDeviceTexelBufferAlignmentProperties::storageTexelBufferOffsetAlignmentBytes 的整数倍，或者，如果VkPhysicalDeviceTexelBufferAlignmentProperties::storageTexelBufferOffsetSingleTexelAlignment 为 VK_TRUE,则offset 必须是format的texel block size，或者，如果format的texel block size是3的倍数，则offset 是format的单个componnet的字节大小。
	10.如果texelBufferAlignment 特性开启，且如果buffer创建时以VK_BUFFER_USAGE_UNIFORM_TEXEL_BUFFER_BIT创建， 则offset 必须是小于 VkPhysicalDeviceTexelBufferAlignmentProperties::uniformTexelBufferOffsetAlignmentBytes 的数的整数倍，或者，如果VkPhysicalDeviceTexelBufferAlignmentProperties::uniformTexelBufferOffsetSingleTexelAlignment 为 VK_TRUE,则offset 必须是format的texel block size，或者，如果format的texel block size是3的倍数，则offset 是format的单个componnet的字节大小。
	11.如果pNext中包含 VkExportMetalObjectCreateInfoEXT，则该结构体的exportObjectType成员必须是VK_EXPORT_METAL_OBJECT_TYPE_METAL_TEXTURE_BIT_EXT
	12.如果pNext中包含VkBufferUsageFlags2CreateInfoKHR，则该结构体的usage 必须是VK_BUFFER_USAGE_2_UNIFORM_TEXEL_BUFFER_BIT_KHR 或 VK_BUFFER_USAGE_2_STORAGE_TEXEL_BUFFER_BIT_KHR，且为 VkBufferCreateInfo::usage 或者 VkBufferCreateInfo::pNext中的 VkBufferUsageFlags2CreateInfoKHR::usage 的子集

	*/

	vkDestroyBufferView(device, bufferView, nullptr);


}

struct ImageCreateInfoEXT {
	VkBufferCollectionImageCreateInfoFUCHSIA bufferCollectionImageCreateInfoFUCHSIA{};
	VkDedicatedAllocationImageCreateInfoNV dedicatedAllocationImageCreateInfoNV{};
	VkExportMetalObjectCreateInfoEXT exportMetalObjectCreateInfoEXT{};
	VkExternalFormatANDROID  externalFormatANDROID{};
	VkExternalFormatQNX externalFormatQNX{};
	VkExternalMemoryImageCreateInfo externalMemoryImageCreateInfo{};
	VkExternalMemoryImageCreateInfoNV externalMemoryImageCreateInfoNV{};
	VkImageAlignmentControlCreateInfoMESA imageAlignmentControlCreateInfoMESA{};
	VkImageCompressionControlEXT imageCompressionControlEXT{};
	VkImageDrmFormatModifierExplicitCreateInfoEXT imageDrmFormatModifierExplicitCreateInfoEXT{};
	VkImageDrmFormatModifierListCreateInfoEXT imageDrmFormatModifierListCreateInfoEXT{};
	VkImageFormatListCreateInfo imageFormatListCreateInfo{};
	VkImageStencilUsageCreateInfo imageStencilUsageCreateInfo{};
	VkImageSwapchainCreateInfoKHR imageSwapchainCreateInfoKHR{};
	VkImportMetalIOSurfaceInfoEXT importMetalIOSurfaceInfoEXT{};
	VkImportMetalTextureInfoEXT importMetalTextureInfoEXT{};
	VkOpaqueCaptureDescriptorDataCreateInfoEXT opaqueCaptureDescriptorDataCreateInfoEXT{};
	VkOpticalFlowImageFormatInfoNV opticalFlowImageFormatInfoNV{};
	VkVideoProfileListInfoKHR videoProfileListInfoKHR{};
	ImageCreateInfoEXT() {
		Init();
	}
	//从这里这里开始后续类型*CreateInfoEXT的结构体初始化的时候都不在链接pNext了
	void Init() {
		bufferCollectionImageCreateInfoFUCHSIA.sType = VK_STRUCTURE_TYPE_BUFFER_COLLECTION_IMAGE_CREATE_INFO_FUCHSIA;
		dedicatedAllocationImageCreateInfoNV.sType = VK_STRUCTURE_TYPE_DEDICATED_ALLOCATION_IMAGE_CREATE_INFO_NV;
		exportMetalObjectCreateInfoEXT.sType = VK_STRUCTURE_TYPE_EXPORT_METAL_OBJECT_CREATE_INFO_EXT;
		externalFormatANDROID.sType = VK_STRUCTURE_TYPE_EXTERNAL_FORMAT_ANDROID;
		externalFormatQNX.sType = VK_STRUCTURE_TYPE_MAX_ENUM;//没有定义这里设置为无效值
		externalMemoryImageCreateInfo.sType = VK_STRUCTURE_TYPE_EXTERNAL_MEMORY_IMAGE_CREATE_INFO;
		externalMemoryImageCreateInfoNV.sType = VK_STRUCTURE_TYPE_EXTERNAL_MEMORY_IMAGE_CREATE_INFO_NV;
		imageAlignmentControlCreateInfoMESA.sType = VK_STRUCTURE_TYPE_MAX_ENUM;//没有定义这里设置为无效值
		imageCompressionControlEXT.sType = VK_STRUCTURE_TYPE_IMAGE_COMPRESSION_CONTROL_EXT;
		imageDrmFormatModifierExplicitCreateInfoEXT.sType = VK_STRUCTURE_TYPE_IMAGE_DRM_FORMAT_MODIFIER_EXPLICIT_CREATE_INFO_EXT;
		imageDrmFormatModifierListCreateInfoEXT.sType = VK_STRUCTURE_TYPE_IMAGE_DRM_FORMAT_MODIFIER_LIST_CREATE_INFO_EXT;
		imageFormatListCreateInfo.sType = VK_STRUCTURE_TYPE_IMAGE_FORMAT_LIST_CREATE_INFO;
		imageStencilUsageCreateInfo.sType = VK_STRUCTURE_TYPE_IMAGE_STENCIL_USAGE_CREATE_INFO;
		imageSwapchainCreateInfoKHR.sType = VK_STRUCTURE_TYPE_IMAGE_SWAPCHAIN_CREATE_INFO_KHR;
		importMetalIOSurfaceInfoEXT.sType = VK_STRUCTURE_TYPE_IMPORT_METAL_IO_SURFACE_INFO_EXT;
		importMetalTextureInfoEXT.sType = VK_STRUCTURE_TYPE_IMPORT_METAL_TEXTURE_INFO_EXT;
		opaqueCaptureDescriptorDataCreateInfoEXT.sType = VK_STRUCTURE_TYPE_OPAQUE_CAPTURE_DESCRIPTOR_DATA_CREATE_INFO_EXT;
		opticalFlowImageFormatInfoNV.sType = VK_STRUCTURE_TYPE_OPTICAL_FLOW_IMAGE_FORMAT_INFO_NV;
		videoProfileListInfoKHR.sType = VK_STRUCTURE_TYPE_VIDEO_PROFILE_LIST_INFO_KHR;


	}
};


void ResourceCreationTest::ImageCreateTest()
{
	//image 代表多达3维的 一个多维的数据数组

	VkImage image;
	VkImageCreateInfo imageCreateInfo{};
	imageCreateInfo.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
	ImageCreateInfoEXT imageCreateInfoEXT{};
	imageCreateInfo.pNext = &imageCreateInfoEXT.bufferCollectionImageCreateInfoFUCHSIA;
	imageCreateInfo.flags = 0;//是 VkImageCreateFlagBits的组合值，指明image的额外参数
	/*
	VkImageCreateFlagBits：

	VK_IMAGE_CREATE_SPARSE_BINDING_BIT:  指明image将使用sparse memory binding来备份
	VK_IMAGE_CREATE_SPARSE_RESIDENCY_BIT：指明image 可以使用sparse memory binding来部分备份，以该flag创建则也需要以VK_IMAGE_CREATE_SPARSE_BINDING_BIT创建
	VK_IMAGE_CREATE_SPARSE_ALIASED_BIT： 指明image 可以使用sparse memory binding来部分备份，其memory range可能会同时备份到其他的image中（或者本image的不同部分），以该flag创建则也需要以VK_IMAGE_CREATE_SPARSE_BINDING_BIT创建
	VK_IMAGE_CREATE_MUTABLE_FORMAT_BIT： 指明image 可以用来创建一个不同format 的VkImageView，对于multi-planar formats，VK_IMAGE_CREATE_MUTABLE_FORMAT_BIT指明VkImageView可以被认为是image的一个plane
	VK_IMAGE_CREATE_CUBE_COMPATIBLE_BIT：指明image 可以用来创建一个类型为 VK_IMAGE_VIEW_TYPE_CUBE 或者 VK_IMAGE_VIEW_TYPE_CUBE_ARRAY 的VkImageView
	VK_IMAGE_CREATE_2D_ARRAY_COMPATIBLE_BIT：指明image 可以用来创建一个类型为VK_IMAGE_VIEW_TYPE_2D 或 VK_IMAGE_VIEW_TYPE_2D_ARRAY的VkImageView
	VK_IMAGE_CREATE_2D_VIEW_COMPATIBLE_BIT_EXT：指明image 可以用来创建一个类型为VK_IMAGE_VIEW_TYPE_2D 的VkImageView
	VK_IMAGE_CREATE_PROTECTED_BIT：指明image 是一个  protected image.
	VK_IMAGE_CREATE_SPLIT_INSTANCE_BIND_REGIONS_BIT：指明image 可以在vkBindImageMemory2命令中和splitInstanceBindRegionCount为非0值的VkBindImageMemoryDeviceGroupInfo一起使用，这个flag 也让image 使用标准的sparse image block dimensions
	VK_IMAGE_CREATE_BLOCK_TEXEL_VIEW_COMPATIBLE_BIT：指明image 有一个压缩format，可以用来创建一个有非压缩format的VkImageView，iamge view的texel对应image的 压缩的texel block。
	VK_IMAGE_CREATE_EXTENDED_USAGE_BIT：指明image 可以以一个本image的usage不支持的format但是至少支持一个从这个image上创建的VkImageView的format上创建
	VK_IMAGE_CREATE_DISJOINT_BIT：指明有一个multi-planar format 的image 的必须其每个plane 要分离地绑定到内存，而不是直接全部绑定到一块单独的内存上，这个主要是为了区分disjoint image和非disjoint image
	VK_IMAGE_CREATE_ALIAS_BIT ：指定使用相同创建参数创建并指向相同内存的两个图像可以彼此一致地解释内存的内容，并遵循内存混叠部分中描述的规则。该标志进一步指定，不相交图像的每个平面可以与单平面图像共享内存中的非线性表示，
										并且单平面图像可以与多平面不相交图像的平面共享内存中的非线性表示。如果pNext链包含一个VkExternalMemoryImageCreateInfo或VkExternalMemoryImageCreateInfoNV结构，其把手类型成员不是0，则像设置VK_IMAGE_CREATE_ALIAS_BIT一样。
	VK_IMAGE_CREATE_SAMPLE_LOCATIONS_COMPATIBLE_DEPTH_BIT_EXT ：指定有一个depth 或者 depth/stencil format 的image 可以在作为 depth/stencil attachment使用的时候使用自定义的采样位置
	VK_IMAGE_CREATE_CORNER_SAMPLED_BIT_NV：指定  image 是一个 corner-sampled image.
	VK_IMAGE_CREATE_SUBSAMPLED_BIT_EXT：指定  image 可以有一个subsampled format，当作为一个含有fragment density map attachment 的render pass的附件被写入的时候或许是更优的方式，但是访问这种subsampled image有更多限制（详情见p1061）

	VK_IMAGE_CREATE_FRAGMENT_DENSITY_MAP_OFFSET_BIT_QCOM ：指定可以在具有非零fragment density map offsets的渲染过程中使用图像。在带有非零偏移量的渲染通道中，必须使用VK_IMAGE_CREATE_FRAGMENT_DENSITY_MAP_OFFSET_BIT_QCOM创建fragment density map attachments, input attachments, color attachments, depth/stencil attachment, resolve attachments, 以及 preserve attachments

	VK_IMAGE_CREATE_DESCRIPTOR_BUFFER_CAPTURE_REPLAY_BIT_EXT： 指定image 可以用来作为一个descriptor buffers 的capturing 和replaying(e.g. for trace capture and replay)，详情参见VkOpaqueCaptureDescriptorDataCreateInfoEXT
	VK_IMAGE_CREATE_MULTISAMPLED_RENDER_TO_SINGLE_SAMPLED_BIT_EXT： 指定image 可以用在 multisampled rendering 中作为single-sampled framebuffer attachment
	VK_IMAGE_CREATE_VIDEO_PROFILE_INDEPENDENT_BIT_KHR：指定image 可以用在video coding operations 而不需要在创建过程中指定video profiles，除非这个image只作为 DPB pictures，则只要考虑image与的video配置兼容。

	*/
	imageCreateInfo.format = VK_FORMAT_A1R5G5B5_UNORM_PACK16;//是一种VkFormat，描述了将包含在图像中的texel blocks的格式和类型。
	imageCreateInfo.usage = VK_IMAGE_USAGE_SAMPLED_BIT;/*//是 VkImageUsageFlagBits 的组合值指明image用途
	VkImageUsageFlagBits：

	VK_IMAGE_USAGE_TRANSFER_SRC_BIT：指明image 可以用作transfer command的source
	VK_IMAGE_USAGE_TRANSFER_DST_BIT：指明image  可以用作transfer command的destination
	VK_IMAGE_USAGE_SAMPLED_BIT：  指明image  可以用来创建一个适用于VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE或者VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER的占据一个 VkDescriptorSet slot的VkImageView，用于shader采样。
	VK_IMAGE_USAGE_STORAGE_BIT： 指明image  可以用来创建一个适用于VK_DESCRIPTOR_TYPE_STORAGE_IMAGE 的占据一个 VkDescriptorSet slot的VkImageView，
	VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT：  指明image 可以用来创建一个适用于作为VkFramebuffer 的color 或 resolve attachment 的VkImageView
	VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT：  指明image 可以用来创建一个适用于作为VkFramebuffer 的depth/stencil 或 depth/stencil resolve attachment 的VkImageView
	VK_IMAGE_USAGE_TRANSIENT_ATTACHMENT_BIT：  指明实现可能支持VK_MEMORY_PROPERTY_LAZILY_ALLOCATED_BIT的memory allocations来备份一个 image，这个位可以设置用来创建一个适用于作为 color, resolve, depth/stencil, 或者 input attachment的VkImageView.
	VK_IMAGE_USAGE_INPUT_ATTACHMENT_BIT：  指明image 可以用来创建一个适用于VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT 的占据一个 VkDescriptorSet slot的VkImageView，在shader中作为input attachment读取，在VkFrameBuffer中作为input attachment 使用
	VK_IMAGE_USAGE_FRAGMENT_DENSITY_MAP_BIT_EXT：  指明image 可以用来创建一个适用于fragment density map image的VkImageView
	VK_IMAGE_USAGE_FRAGMENT_SHADING_RATE_ATTACHMENT_BIT_KHR：  指明image 可以用来创建一个适用于fragment shading rate attachment 或者 shading rate image的VkImageView
	VK_IMAGE_USAGE_VIDEO_DECODE_DST_BIT_KHR： 指明image 可以用来作为一个video decode operation 的output picture
	VK_IMAGE_USAGE_VIDEO_DECODE_SRC_BIT_KHR：保留未来使用.
	VK_IMAGE_USAGE_VIDEO_DECODE_DPB_BIT_KHR：  指明image 可以用来作为一个video decode operation 的一个output reconstructed picture 或者 input reference picture
	VK_IMAGE_USAGE_VIDEO_ENCODE_DST_BIT_KHR：保留未来使用.
	VK_IMAGE_USAGE_VIDEO_ENCODE_SRC_BIT_KHR：  指明image 可以用来作为一个video encode operation 的input picture
	VK_IMAGE_USAGE_VIDEO_ENCODE_DPB_BIT_KHR：  指明image 可以用来作为一个video encode operation 的一个output reconstructed picture 或者 input reference picture
	VK_IMAGE_USAGE_ATTACHMENT_FEEDBACK_LOOP_BIT_EXT： 指明image 可以转换布局到VK_IMAGE_LAYOUT_ATTACHMENT_FEEDBACK_LOOP_OPTIMAL_EXT，在同一个render pass中被使用作为VkFramebuffer 的color 或者 depth/stencil attachment 或者shader的read-only input resource (sampled image, combined image sampler 或者 input attachment)的时候
	VK_IMAGE_USAGE_HOST_TRANSFER_BIT_EXT：  指明image 可以用在host端的copy 命令和layout transitions中


	*/
	imageCreateInfo.tiling = VK_IMAGE_TILING_OPTIMAL;/*指明image的 texel blocks的内存排布的一个 VkImageTiling
	
	VkImageTiling：指明image中的texel blocks的内存排布
	VK_IMAGE_TILING_OPTIMAL：指明是优化排布 (texels 以基于实现的方式进行排布，为了更高效的的内存访问).
	VK_IMAGE_TILING_LINEAR：指明是线性排布 (texels 在内存中以行序优先（row-major）的方式进行排布，每行可能存在内存补丁（padding）).
	VK_IMAGE_TILING_DRM_FORMAT_MODIFIER_EXT：指明image的排布由Linux DRM format modifier决定，而modifier又在image 创建时候由VkImageDrmFormatModifierListCreateInfoEXT 或者 VkImageDrmFormatModifierExplicitCreateInfoEXT指定，查询modifier可调用vkGetImageDrmFormatModifierPropertiesEXT
	
	*/
	imageCreateInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;//是一个 VkSharingMode 值，指定图像在它将被多个队列族访问时的共享模式。
	imageCreateInfo.queueFamilyIndexCount = 0;//pQueueFamilyIndices的元素个数
	imageCreateInfo.pQueueFamilyIndices = VK_NULL_HANDLE;//是指向将访问此图像的队列族索引数组的指针。如果共享模式不是VK_SHARING_MODE_CONCURRENT，则被忽略。
	imageCreateInfo.samples = VK_SAMPLE_COUNT_1_BIT;// 是一个指定samples per texel采样数的 VkSampleCountFlagBits
	imageCreateInfo.imageType = VK_IMAGE_TYPE_2D;/*是一个指定image的基本维度的VkImageType值。从图像类型的目的上讲，array textures中的layers不计入维度
	
	VkImageType
	VK_IMAGE_TYPE_1D ：指明一个一维image.
	VK_IMAGE_TYPE_2D ：指明一个二维image.
	VK_IMAGE_TYPE_3D ：指明一个三维image.

	*/
	imageCreateInfo.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED; /*是一个VkImageLayout 值，指定图像的所有image subresources (mips 以及 layers)的初始VkAmageLayout 值。请参见Image Layout p1078
	VkImageLayout:
    VK_IMAGE_LAYOUT_UNDEFINED:  指定layout未知，Image memory不能转换到这个layout，这个layout不能用作VkImageCreateInfo的initialLayout。这个layout可以在layout transition命令中代替当前image的layout，但是这样做会导致image的memory中的值变成未定义的。
    VK_IMAGE_LAYOUT_PREINITIALIZED:  指定image的内存在已定义的layout中，并且可以由数据填充，但它尚未被驱动程序初始化。Image memory不能转换到此布局中。此布局可以用作VkImageCreateInfo的initialLayout成员。此布局旨在用作其内容由主机写入的图像的初始布局，因此，可以立即将数据写入内存，而无需首先执行布局转换。目前，VK_IMAGE_LAYOUT_PREINITIALIZED只对linear image有用，因为没有为VK_IMAGE_TILING_OPTIMAL图像定义的标准布局。
    VK_IMAGE_LAYOUT_GENERAL:  支持所有的device访问类型 
    VK_IMAGE_LAYOUT_ATTACHMENT_OPTIMAL:  指定 一个只能用在graphics pipeline中用作attachment访问的layout
    VK_IMAGE_LAYOUT_READ_ONLY_OPTIMAL:  指定 一个作为附件，或者shader中作为一个sampled image，combied image/sampler,或者input attachment 的只读的layout
    VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL:  指定只能在VkFramebuffer中作为color或者resolve attachment，这个layout只对创建时usage含有VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT的image subresource 或者image有效。
    VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL:  指定一个作为允许读写的 depth/stencil attachment的含有depth/stencil format的 image 的depth和stencil两个aspect的layout，等价于 VK_IMAGE_LAYOUT_DEPTH_ATTACHMENT_OPTIMAL & VK_IMAGE_LAYOUT_STENCIL_ATTACHMENT_OPTIMAL
    VK_IMAGE_LAYOUT_DEPTH_STENCIL_READ_ONLY_OPTIMAL:  指定一个作为只读的 depth/stencil attachment的含有depth/stencil format的 image 的depth和stencil两个aspect的layout，等价于 VK_IMAGE_LAYOUT_DEPTH_READ_ONLY_OPTIMAL & VK_IMAGE_LAYOUT_STENCIL_READ_ONLY_OPTIMAL
    VK_IMAGE_LAYOUT_DEPTH_READ_ONLY_STENCIL_ATTACHMENT_OPTIMAL:  指定一个含有depth/stencil format的 image作为 允许stencil 读写的 stencil attachment和允许 depth 只读的 depth attachment ，或者在shaders中作为sampled image，combied image或者input attachment 的depth/stencil的layout，等价于 VK_IMAGE_LAYOUT_DEPTH_READ_ONLY_OPTIMAL & VK_IMAGE_LAYOUT_STENCIL_ATTACHMENT_OPTIMAL
    VK_IMAGE_LAYOUT_DEPTH_ATTACHMENT_STENCIL_READ_ONLY_OPTIMAL:  指定一个含有depth/stencil format的 image作为 允许depth 读写的 depth attachment和允许 stencil 只读的 stencil attachment ，或者在shaders中作为sampled image，combied image或者input attachment 的depth/stencil的layout，等价于 VK_IMAGE_LAYOUT_DEPTH_ATTACHMENT_OPTIMAL & VK_IMAGE_LAYOUT_STENCIL_READ_ONLY_OPTIMAL
    VK_IMAGE_LAYOUT_DEPTH_ATTACHMENT_OPTIMAL:  指定一个含有depth/stencil format的 image作为 允许depth 读写的 depth attachment的depth aspect的layout
    VK_IMAGE_LAYOUT_DEPTH_READ_ONLY_OPTIMAL:  指定一个含有depth/stencil format的 image作为 只允许depth 读的 depth attachment或者 在shaders中作为sampled image，combied image或者input attachment 的depth aspect的layout
    VK_IMAGE_LAYOUT_STENCIL_ATTACHMENT_OPTIMAL:  指定一个含有depth/stencil format的 image作为 允许stencil 读写的 stencil attachment的stencil aspect的layout
    VK_IMAGE_LAYOUT_STENCIL_READ_ONLY_OPTIMAL:  指定一个含有depth/stencil format的 image作为 只允许stencil 读的 stencil attachment或者 在shaders中作为sampled image，combied image或者input attachment 的stencil aspect的layout
    VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL:  指定一个 在shaders中作为sampled image，combied image或者input attachment 的只读访问的layout，这个layout只对创建时usage含有VK_IMAGE_USAGE_SAMPLED_BIT或 VK_IMAGE_USAGE_INPUT_ATTACHMENT_BIT的image subresource 或者image有效。
    VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL: 必须用在transfer command中作为source image参数(参见定义 VK_PIPELINE_STAGE_TRANSFER_BIT相关的命令)，这个layout只对创建时usage含有 VK_IMAGE_USAGE_TRANSFER_SRC_BIT 的image subresource 或者image有效。
    VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL: 必须用在transfer command中作为destination image参数(参见定义 VK_PIPELINE_STAGE_TRANSFER_BIT相关的命令)，这个layout只对创建时usage含有 VK_IMAGE_USAGE_TRANSFER_DST_BIT 的image subresource 或者image有效。
    VK_IMAGE_LAYOUT_PRESENT_SRC_KHR:  必须用来显示一个可显示的image，这个layout只对创建时usage含有 VK_IMAGE_USAGE_TRANSFER_DST_BIT 的image subresource 或者image有效。
    VK_IMAGE_LAYOUT_SHARED_PRESENT_KHR: 仅对共享的可显示的image有效，并且必须用于图像支持的任何使用。
    VK_IMAGE_LAYOUT_FRAGMENT_SHADING_RATE_ATTACHMENT_OPTIMAL_KHR:  必须用作一个fragment shading rate attachment 或者 shading rate image，这个layout只对创建时usage含有 VK_IMAGE_USAGE_FRAGMENT_SHADING_RATE_ATTACHMENT_BIT_KHR 的image subresource 或者image有效。
    VK_IMAGE_LAYOUT_FRAGMENT_DENSITY_MAP_OPTIMAL_EXT:  必须在VkRenderPass中用作一个fragment density map attachment ，这个layout只对创建时usage含有 VK_IMAGE_USAGE_FRAGMENT_DENSITY_MAP_BIT_EXT 的image subresource 或者image有效。
    VK_IMAGE_LAYOUT_VIDEO_DECODE_DST_KHR:  必须在video decode operation中用作一个decode output picture ，这个layout只对创建时usage含有 VK_IMAGE_USAGE_VIDEO_DECODE_DST_BIT_KHR 的image subresource 或者image有效。
    VK_IMAGE_LAYOUT_VIDEO_DECODE_SRC_KHR: 保留未来使用
    VK_IMAGE_LAYOUT_VIDEO_DECODE_DPB_KHR:  必须在video decode operation中用作一个output reconstructed picture 或者 input reference picture ，这个layout只对创建时usage含有 VK_IMAGE_USAGE_VIDEO_DECODE_DPB_BIT_KHR 的image subresource 或者image有效。
    VK_IMAGE_LAYOUT_VIDEO_ENCODE_DST_KHR: 保留未来使用
    VK_IMAGE_LAYOUT_VIDEO_ENCODE_SRC_KHR:  必须在video encode operation中用作一个encode input picture ，这个layout只对创建时usage含有 VK_IMAGE_USAGE_VIDEO_ENCODE_SRC_BIT_KHR 的image subresource 或者image有效。
    VK_IMAGE_LAYOUT_VIDEO_ENCODE_DPB_KHR:  必须在video encode operation中用作一个output reconstructed picture 或者 input reference picture ，这个layout只对创建时usage含有 VK_IMAGE_USAGE_VIDEO_ENCODE_DPB_BIT_KHR 的image subresource 或者image有效。
    VK_IMAGE_LAYOUT_ATTACHMENT_FEEDBACK_LOOP_OPTIMAL_EXT:  必须仅作为VkFrameBuffer中的color attachment或depth/stencil attachment使用，且或在shaders中作为sampled image, combined image/sampler, 或者 input attachment进行只读访问。此layout仅对启用VK_IMAGE_USAGE_ATTACHMENT_FEEDBACK_LOOP_BIT_EXT，且还启用 VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT或VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT，或者是VK_IMAGE_USAGE_INPUT_ATTACHMENT_BIT或VK_IMAGE_USAGE_SAMPLED_BIT 创建的image subresource 或者image有效。
    VK_IMAGE_LAYOUT_RENDERING_LOCAL_READ_KHR:  必须仅用作storage image、color 或者 depth/stencil attachment 以及 input attachment。此布局仅对使用VK_IMAGE_USAGE_STORAGE_BIT，或者是使用了VK_IMAGE_USAGE_INPUT_ATTACHMENT_BIT 和 VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT 或 VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT两个其中一个创建的image subresource 或者image有效。
	*/
	imageCreateInfo.mipLevels = 1;//描述可用于对image的缩小采样的细节级别的数量。mipmap level的数量
	imageCreateInfo.arrayLayers = 1;//image中layer的数量
	imageCreateInfo.extent = VkExtent3D{ 1,1 ,1 };//是一个VkExtent3D，描述了base lavel的每个维度中的数据元素的数量。
	/*
	image creation limits:
	1.VkImageCreateInfo::arrayLayers受 imageCreateMaxArrayLayers限制，VkImageCreateInfo::samples受VkImageCreateInfo::samples限制
	2.如果让 uint64_t imageCreateDrmFormatModifiers[]为 Linux DRM format modifiers的集合，则:
			（1）如果tiling 不为 VK_IMAGE_TILING_DRM_FORMAT_MODIFIER_EXT，则imageCreateDrmFormatModifiers 为空
			（2）如果VkImageCreateInfo::pNext包含VkImageDrmFormatModifierExplicitCreateInfoEXT，则imageCreateDrmFormatModifiers 包含一个modifier，VkImageDrmFormatModifierExplicitCreateInfoEXT::drmFormatModifier
			（3）如果VkImageCreateInfo::pNext包含VkImageDrmFormatModifierListCreateInfoEXT，则imageCreateDrmFormatModifiers 包含VkImageDrmFormatModifierListCreateInfoEXT::pDrmFormatModifiers中的所有modifier
	3.如果让 VkBool32 imageCreateMaybeLinear 指明是否 resultant image 是 linear的，则
			（1）如果tiling 是 VK_IMAGE_TILING_LINEAR,则imageCreateMaybeLinear 为 VK_TRUE
			（2）如果tiling 是VK_IMAGE_TILING_OPTIMAL，则imageCreateMaybeLinear 为 VK_FALSE
			（3）如果tiling 是VK_IMAGE_TILING_DRM_FORMAT_MODIFIER_EXT，则imageCreateMaybeLinear 为 VK_TRUE有且只有在imageCreateDrmFormatModifiers 包含DRM_FORMAT_MOD_LINEAR的时候
	4.如果让 VkFormatFeatureFlags imageCreateFormatFeatures是一个image创建时候有效的format features，则
			（1）如果tiling 是 VK_IMAGE_TILING_LINEAR,则imageCreateFormatFeatures 是通过vkGetPhysicalDeviceFormatProperties 传入一个等于VkImageCreateInfo::format的format参数后返回的VkFormatProperties::linearTilingFeatures 中的值
			（2）如果tiling 是VK_IMAGE_TILING_OPTIMAL，且如果pNext中包含一个非0的externalFormat的VkExternalFormatANDROID或VkExternalFormatQNX结构，则imageCreateFormatFeatures 是通过vkGetPhysicalDeviceFormatProperties 传入一个等于VkImageCreateInfo::format的format参数后返回的VkFormatProperties::optimalTilingFeatures 中的值
			（3）如果tiling 是VK_IMAGE_TILING_OPTIMAL，则如果pNext中包含一个非0的externalFormat的VkExternalFormatANDROID，则imageCreateFormatFeatures 是通过vkGetAndroidHardwareBufferPropertiesANDROID 传入匹配externalFormat的参数获得的VkAndroidHardwareBufferFormatPropertiesANDROID::formatFeatures 中的值
			（4）如果tiling 是VK_IMAGE_TILING_OPTIMAL，则如果pNext中包含一个非0的externalFormat的VkExternalFormatQNX，则imageCreateFormatFeatures 是通过vkGetScreenBufferPropertiesQNX 传入匹配externalFormat的参数获得的VkScreenBufferFormatPropertiesQNX::formatFeatures 中的值
			（5）如果pNext 中包含VkBufferCollectionImageCreateInfoFUCHSIA，则imageCreateFormatFeatures 是通过vkGetBufferCollectionPropertiesFUCHSIA是通过传入一个collection参数等于当前VkBufferCollectionImageCreateInfoFUCHSIA返回的 VkBufferCollectionPropertiesFUCHSIA::formatFeatures中的值
			（6）如果tiling 是VK_IMAGE_TILING_DRM_FORMAT_MODIFIER_EXT，则imageCreateFormatFeatures 是通过vkGetPhysicalDeviceFormatProperties2 传入VkImageFormatProperties::format等于VkImageCreateInfo::format返回的链接到VkFormatProperties2.pNext中的的 VkDrmFormatModifierPropertiesListEXT 结构体中的值做运算而来，---通过收集返回的数组中那些drmFormatModifier 属于 imageCreateDrmFormatModifiers的VkDrmFormatModifierPropertiesListEXT::pDrmFormatModifierProperties中的所有元素，和这些元素的drmFormatModifierTilingFeatures位取交集的值。
	5.如果让  VkImageFormatProperties2 imageCreateImageFormatPropertiesList[]定义如下：
		（1）如果VkImageCreateInfo::pNext 不包含有非0值externalFormat的VkExternalFormatANDROID 或者VkExternalFormatQNX，则imageCreateImageFormatPropertiesList为vkGetPhysicalDeviceImageFormatProperties2调用返回的结构体列表，如下
			1）VkPhysicalDeviceImageFormatInfo2::format, imageType, tiling, usage, 以及 flags必须和VkImageCreateInfo中的相等
			2）如果VkImageCreateInfo::pNext 中包含handleTypes不为0的VkExternalMemoryImageCreateInfo，则VkPhysicalDeviceImageFormatInfo2::pNext 必须包含一个handleType不为0的VkPhysicalDeviceExternalImageFormatInfo，且必须为每一个 VkExternalMemoryImageCreateInfo::handleTypes 中的handleType调用vkGetPhysicalDeviceImageFormatProperties2来正确设置VkPhysicalDeviceExternalImageFormatInfo::handleType

			3）如果VkImageCreateInfo::pNext 中不包含VkExternalMemoryImageCreateInfo，或者是包含handleTypes为0的VkExternalMemoryImageCreateInfo，则VkPhysicalDeviceImageFormatInfo2::pNext 必须不包含VkPhysicalDeviceExternalImageFormatInfo或者包含一个handleType为0的VkPhysicalDeviceExternalImageFormatInfo
			4）如果VkImageCreateInfo::pNext 中包含VkVideoProfileListInfoKHR，则VkPhysicalDeviceImageFormatInfo2::pNext 必须也包含同样的VkVideoProfileListInfoKHR
			5）如果tiling 为VK_IMAGE_TILING_DRM_FORMAT_MODIFIER_EXT，则
				-- VkPhysicalDeviceImageFormatInfo2::pNext 必须包含一个sharingMode等于VkImageCreateInfo::sharingMode的VkPhysicalDeviceImageDrmFormatModifierInfoEXT
				-- 如果sharingMode 为VK_SHARING_MODE_CONCURRENT，则queueFamilyIndexCount 以及pQueueFamilyIndices 必须等于VkImageCreateInfo中的
				--如果flags 包含VK_IMAGE_CREATE_MUTABLE_FORMAT_BIT，则包含在VkPhysicalDeviceImageFormatInfo2的pNext中的VkImageFormatListCreateInfo必须等于包含在VkImageCreateInfo的pNext中的
				--如果VkImageCreateInfo::pNext包含一个VkImageCompressionControlEXT，则VkPhysicalDeviceImageFormatInfo2::pNext 必须包含一个等效的结构体
				--必须为imageCreateDrmFormatModifiers 的每个modifier 调用vkGetPhysicalDeviceImageFormatProperties2，来成功设置VkPhysicalDeviceImageDrmFormatModifierInfoEXT::drmFormatModifier
			6）如果tiling 不为VK_IMAGE_TILING_DRM_FORMAT_MODIFIER_EXT，则VkPhysicalDeviceImageFormatInfo2::pNext 不能包含VkPhysicalDeviceImageDrmFormatModifierInfoEXT
			7）如果vkGetPhysicalDeviceImageFormatProperties2 调用返回error，则imageCreateImageFormatPropertiesList 定义为空列表
		（2）如果VkImageCreateInfo::pNext 中包含一个非0的externalFormat的VkExternalFormatANDROID，则imageCreateImageFormatPropertiesList 包含一个单独元素，该元素满足：
			1）VkImageFormatProperties::maxMipLevels 为⌊log2(max(extent.width, extent.height, extent.depth))⌋ + 1
			2）VkImageFormatProperties::maxArrayLayers为 VkPhysicalDeviceLimits::maxImageArrayLayers
			3）VkImageFormatProperties::maxExtent的每个component为 VkPhysicalDeviceLimits::maxImageDimension2D
			4）VkImageFormatProperties::sampleCounts包含 VK_SAMPLE_COUNT_1_BIT
	6.如果让uint32_t imageCreateMaxMipLevels为imageCreateImageFormatPropertiesList 的VkImageFormatProperties::maxMipLevels的最小值，则该值为未定义如果imageCreateImageFormatPropertiesList为空。
	7.如果让uint32_t imageCreateMaxArrayLayers为imageCreateImageFormatPropertiesList 的VkImageFormatProperties::maxArrayLayers的最小值，则该值为未定义如果imageCreateImageFormatPropertiesList为空。
	8.如果让 VkExtent3D imageCreateMaxExtent为imageCreateImageFormatPropertiesList 的VkImageFormatProperties::maxExtent的component-wise最小值，则该值为未定义如果imageCreateImageFormatPropertiesList为空。
	9.如果让VkSampleCountFlags imageCreateSampleCounts 为imageCreateImageFormatPropertiesList 的VkImageFormatProperties::sampleCounts的交集，则该值为未定义如果imageCreateImageFormatPropertiesList为空。
	10.如果让VkVideoFormatPropertiesKHR videoFormatProperties[] 定义如下：
		（1）如果VkImageCreateInfo::pNext 包含VkVideoProfileListInfoKHR，则videoFormatProperties 为调用vkGetPhysicalDeviceVideoFormatPropertiesKHR返回的结构体列表，返回的这些结构体的VkPhysicalDeviceVideoFormatInfoKHR::imageUsage等于VkImageCreateInfo的usage，
				VkPhysicalDeviceVideoFormatInfoKHR::pNext包含和VkImageCreateInfo.pNext相同的VkVideoProfileListInfoKHR
		（2）如果VkImageCreateInfo::pNext不包含VkVideoProfileListInfoKHR，则videoFormatProperties 为空列表
	11.如果让VkBool32 supportedVideoFormat指示是否该image 参数 被指定的video profiles 支持：
		（1）如果supportedVideoFormat 为VK_TRUE，则videoFormatProperties 列表中至少有一个元素满足：
			1）VkImageCreateInfo::format等于VkVideoFormatPropertiesKHR::format
			2）VkImageCreateInfo::flags只包含VkVideoFormatPropertiesKHR::imageCreateFlags中设置的位
			3）VkImageCreateInfo::imageType等于VkVideoFormatPropertiesKHR::imageType
			4）VkImageCreateInfo::tiling 等于 VkVideoFormatPropertiesKHR::imageTiling
			5）VkImageCreateInfo::usage 只包含 VkVideoFormatPropertiesKHR::imageUsageFlags 中的位，或者 VkImageCreateInfo::flags 包含 VK_IMAGE_CREATE_EXTENDED_USAGE_BIT
		（2）否则 supportedVideoFormat 为 VK_FALSE.


	VkImageCreateInfo有效用法：
	1.imageCreateMaxMipLevels, imageCreateMaxArrayLayers, imageCreateMaxExtent, 以及 imageCreateSampleCounts都不能是未定义的，参见image creation limits
	2.如果sharingMode 为VK_SHARING_MODE_CONCURRENT，则（1）pQueueFamilyIndices 必须是 queueFamilyIndexCount 个有效 uint32_t数组首地址
		（2）queueFamilyIndexCount 必须大于1
		（3）pQueueFamilyIndices 中的每个元素必须是唯一的，且小于vkGetPhysicalDeviceQueueFamilyProperties或者vkGetPhysicalDeviceQueueFamilyProperties2为device的physical device调用返回的pQueueFamilyPropertyCount所指的值
	3.如果pNext 包含一个VkExternalFormatANDROID，且该结构体体的externalFormat 不为0，则format 必须为VK_FORMAT_UNDEFINED
	4.如果pNext 不包含一个VkExternalFormatANDROID，或这是包含该结构体但其externalFormat为0则format 必须不为VK_FORMAT_UNDEFINED

	5.extent.width ，extent.height, extent.depth， mipLevels和 arrayLayers必须大于0
	6.如果flags 包含VK_IMAGE_CREATE_CUBE_COMPATIBLE_BIT，则imageType 必须是VK_IMAGE_TYPE_2D，extent.width 和 extent.height必须相同，arrayLayers必须大于等于6

	7.如果flags 包含VK_IMAGE_USAGE_FRAGMENT_DENSITY_MAP_BIT_EXT，则imageType 必须是VK_IMAGE_TYPE_2D
	8.如果flags 包含VK_IMAGE_CREATE_2D_ARRAY_COMPATIBLE_BIT，则imageType 必须是VK_IMAGE_TYPE_3D，flags不能包含VK_IMAGE_CREATE_SPARSE_ALIASED_BIT, VK_IMAGE_CREATE_SPARSE_BINDING_BIT, 或者 VK_IMAGE_CREATE_SPARSE_RESIDENCY_BIT
	9.如果flags 包含VK_IMAGE_CREATE_2D_VIEW_COMPATIBLE_BIT_EXT，则imageType 必须是VK_IMAGE_TYPE_3D

	10.extent.width必须小于等于 imageCreateMaxExtent.width，extent.height 必须小于等于 imageCreateMaxExtent.height,extent.depth 必须小于等于 imageCreateMaxExtent.depth,参见image creation limits
	11.如果imageType 为VK_IMAGE_TYPE_1D，则extent.height 和 extent.depth都必须为1
	12.如果imageType 为VK_IMAGE_TYPE_2D，则extent.depth必须为1
	13.mipLevels必须小于等于 基于extent.width, extent.height, 以及 extent.depth的一个完成的mipmap的level数量，且必须小于等于imageCreateMaxMipLevels（参见image creation limits）
	14.arrayLayers 必须小于等于imageCreateMaxArrayLayers（参见image creation limits）
	15.如果imageType 为VK_IMAGE_TYPE_3D，则arrayLayers必须为1
	16.如果samples 不为VK_SAMPLE_COUNT_1_BIT，则imageType 必须是VK_IMAGE_TYPE_2D，flags 不能包含VK_IMAGE_CREATE_CUBE_COMPATIBLE_BIT, mipLevels 必须为1, 且imageCreateMaybeLinear（参见image creation limits）必须为VK_FALSE，usage不能包含VK_IMAGE_USAGE_FRAGMENT_DENSITY_MAP_BIT_EXT
	17.如果usage 包含VK_IMAGE_USAGE_TRANSIENT_ATTACHMENT_BIT，不能设置除了VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT, VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT, 和 VK_IMAGE_USAGE_INPUT_ATTACHMENT_BIT之外的其他usage
	18.如果usage 包含VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT，VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT，VK_IMAGE_USAGE_TRANSIENT_ATTACHMENT_BIT，或者VK_IMAGE_USAGE_INPUT_ATTACHMENT_BIT，extent.width 和 extent.height 必须小于等于VkPhysicalDeviceLimits::maxFramebufferWidth 和 VkPhysicalDeviceLimits::maxFramebufferHeight
	19.如果fragmentDensityMapOffset 特性没有开启且usage 包含VK_IMAGE_USAGE_FRAGMENT_DENSITY_MAP_BIT_EXT，则extent.width 和 extent.height 必须小于等于 maxFrameBufferWidth/ minFragmentDensityTexelSize.width 和 maxFrameBufferHeight/ minFragmentDensityTexelSize.height（取上界）
	20.如果usage包含VK_IMAGE_USAGE_TRANSIENT_ATTACHMENT_BIT ，usage也必须包含VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT, VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT, 或 VK_IMAGE_USAGE_INPUT_ATTACHMENT_BIT中的至少一个
	21.samples必须是一个有效设置在imageCreateSampleCounts中的VkSampleCountFlagBits（参见image creation limits）
	22.如果shaderStorageImageMultisample 特性没有开启且usage 包含VK_IMAGE_USAGE_STORAGE_BIT，samples 必须为VK_SAMPLE_COUNT_1_BIT
	23.如果sparseBinding 特性未开启，flags 不能包含VK_IMAGE_CREATE_SPARSE_BINDING_BIT
	24.如果sparseResidencyAliased 特性未开启，flags 不能包含VK_IMAGE_CREATE_SPARSE_ALIASED_BIT
	25.如果tiling 为VK_IMAGE_TILING_LINEAR，flags 不能包含VK_IMAGE_CREATE_SPARSE_RESIDENCY_BIT
	26.如果imageType 为VK_IMAGE_TYPE_1D，flags 不能包含VK_IMAGE_CREATE_SPARSE_RESIDENCY_BIT
	27.如果sparseResidencyImage2D 特性没有开启，且imageType为VK_IMAGE_TYPE_2D，flags 不能包含VK_IMAGE_CREATE_SPARSE_RESIDENCY_BIT
	28.如果sparseResidencyImage3D 特性没有开启，且imageType为VK_IMAGE_TYPE_3D，flags 不能包含VK_IMAGE_CREATE_SPARSE_RESIDENCY_BIT
	29.如果sparseResidency2Samples 特性没有开启，且imageType为VK_IMAGE_TYPE_2D，且samples 必须为VK_SAMPLE_COUNT_2_BIT，则flags 不能包含VK_IMAGE_CREATE_SPARSE_RESIDENCY_BIT
	30.如果sparseResidency4Samples 特性没有开启，imageType 为VK_IMAGE_TYPE_2D，samples 为VK_SAMPLE_COUNT_4_BIT，则flags 不能包含VK_IMAGE_CREATE_SPARSE_RESIDENCY_BIT
	31.如果sparseResidency8Samples 特性没有开启，imageType 为VK_IMAGE_TYPE_2D，samples 为VK_SAMPLE_COUNT_8_BIT，则flags 不能包含VK_IMAGE_CREATE_SPARSE_RESIDENCY_BIT
	32.如果sparseResidency16Samples 特性没有开启，imageType 为VK_IMAGE_TYPE_2D，samples 为VK_SAMPLE_COUNT_16_BIT，则flags 不能包含VK_IMAGE_CREATE_SPARSE_RESIDENCY_BIT
	33.如果flags 包含VK_IMAGE_CREATE_SPARSE_RESIDENCY_BIT 或VK_IMAGE_CREATE_SPARSE_ALIASED_BIT，则flags 必须也包含VK_IMAGE_CREATE_SPARSE_BINDING_BIT
	34.如果VK_IMAGE_CREATE_SPARSE_BINDING_BIT, VK_IMAGE_CREATE_SPARSE_RESIDENCY_BIT, 或者 VK_IMAGE_CREATE_SPARSE_ALIASED_BIT任何一个被设置，则就不能设置VK_IMAGE_USAGE_TRANSIENT_ATTACHMENT_BIT
	35.如果protectedMemory 特性没有开启，flags 不能包含VK_IMAGE_CREATE_PROTECTED_BIT
	36.如果VK_IMAGE_CREATE_SPARSE_BINDING_BIT, VK_IMAGE_CREATE_SPARSE_RESIDENCY_BIT, 或者 VK_IMAGE_CREATE_SPARSE_ALIASED_BIT 任何一个被设置，则就不能设置VK_IMAGE_CREATE_PROTECTED_BIT
	37.如果pNextz中包含一个VkExternalMemoryImageCreateInfoNV结构，则（1）pNext就不能包含一个VkExternalMemoryImageCreateInfo结构
																	（2）VkExternalMemoryImageCreateInfo的handleTypes 只能包含VkExternalImageFormatProperties::externalMemoryProperties.compatibleHandleTypes中的位，通过调用vkGetPhysicalDeviceImageFormatProperties2获取，其 format, imageType, tiling, usage, and
																					flags参数等于VkImageCreateInfo的参数，其VkExternalImageFormatProperties的pNext中VkPhysicalDeviceExternalImageFormatInfo的handleType 为VkExternalMemoryImageCreateInfo::handleTypes任何一个指定的句柄类型。
																	（3）其handleTypes 必须只能含有也包含在VkExternalImageFormatPropertiesNV::externalMemoryProperties.compatibleHandleTypes中的位，通过VkExternalImageFormatPropertiesNV::externalMemoryProperties.compatibleHandleTypes获取，传入的参数format, imageType, tiling, usage, 和 flags
																					等于VkImageCreateInfo中的参数，externalHandleType等于任何一个VkExternalMemoryImageCreateInfoNV::handleTypes中指定的句柄类型
	38.如果logical device以VkDeviceGroupDeviceCreateInfo::physicalDeviceCount = 1创建，flags 不能包含VK_IMAGE_CREATE_SPLIT_INSTANCE_BIND_REGIONS_BIT
	39.如果flags包含VK_IMAGE_CREATE_SPLIT_INSTANCE_BIND_REGIONS_BIT，则mipLevels 必须为1 ，arrayLayers必须为1，imageType必须为VK_IMAGE_TYPE_2D，imageCreateMaybeLinear (参见 image creation limits) 必须为 VK_FALSE
	40.如果flags包含VK_IMAGE_CREATE_BLOCK_TEXEL_VIEW_COMPATIBLE_BIT,则（1）format 必须是compressed image format
																	  （2）flags 必须也包含VK_IMAGE_CREATE_MUTABLE_FORMAT_BIT
	41.initialLayout 必须为VK_IMAGE_LAYOUT_UNDEFINED 或者VK_IMAGE_LAYOUT_PREINITIALIZED
	42.如果pNext中包含一个handleTypes不为0的VkExternalMemoryImageCreateInfo或者VkExternalMemoryImageCreateInfoNV，initialLayout必须为VK_IMAGE_LAYOUT_UNDEFINED
	43.如果image format 是一个 需要 sampler Y′CBCR conversion的format，则mipLevels 必须为1，samples必须为VK_SAMPLE_COUNT_1_BIT，imageType必须为VK_IMAGE_TYPE_2D
	44.如果format 是一个 multi-planar format，则（1）imageCreateFormatFeatures 不包含VK_FORMAT_FEATURE_DISJOINT_BIT（参见image creation limits），则flags 不能包含VK_IMAGE_CREATE_DISJOINT_BIT
												（2）如果flags不包含VK_IMAGE_CREATE_ALIAS_BIT，则flags 不能包含VK_IMAGE_CREATE_DISJOINT_BIT
	45.如果format有一个 _422或 _420后缀，extent.width必须是2的倍数，如果有_420后缀，extent.height必须是2的倍数
	46.如果format 是一个 VK_FORMAT_PVTRC1_*_IMG 格式，extent.width必须是2的指数，且extent.height必须是2的指数
	47.如果tiling 是VK_IMAGE_TILING_DRM_FORMAT_MODIFIER_EXT，则pNext中必须包含一个VkImageDrmFormatModifierListCreateInfoEXT或VkImageDrmFormatModifierExplicitCreateInfoEXT结构
	48.如果pNext中包含一个VkImageDrmFormatModifierListCreateInfoEXT或者VkImageDrmFormatModifierExplicitCreateInfoEXT，tiling就必须为VK_IMAGE_TILING_DRM_FORMAT_MODIFIER_EXT
	49.如果tiling 是VK_IMAGE_TILING_DRM_FORMAT_MODIFIER_EXT且flags包含VK_IMAGE_CREATE_MUTABLE_FORMAT_BIT，则pNext中必须包含一个VkImageFormatListCreateInfo结构，且viewFormatCount必须大于0
	50.如果flags包含 VK_IMAGE_CREATE_SAMPLE_LOCATIONS_COMPATIBLE_DEPTH_BIT_EXT，format就必须为一个depth 或者depth/stencil format，
	51.如果pNext中包含一个handleTypes包含VK_EXTERNAL_MEMORY_HANDLE_TYPE_ANDROID_HARDWARE_BUFFER_BIT_ANDROID的 VkExternalMemoryImageCreateInfo，则imageType必须为VK_IMAGE_TYPE_2D，mipmaps必须等于1或者基于extent.width, extent.height, 和 extent.depth的一个完整mipmap的等级个数
	52.如果pNext中包含一个externalFormat不为0的VkExternalFormatANDROID，则（1）flags 不能包含VK_IMAGE_CREATE_MUTABLE_FORMAT_BIT
																		  （2）usage 不能包含任何除VK_IMAGE_USAGE_INPUT_ATTACHMENT_BIT，VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT, 或者VK_IMAGE_USAGE_SAMPLED_BIT之外的值
																		  （3）如果externalFormatResolve 特性没有开启，usage 不能包含VK_IMAGE_USAGE_INPUT_ATTACHMENT_BIT 或者 VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT
																		  （4）tiling 必须为VK_IMAGE_TILING_OPTIMAL
	53.如果pNext中包含一个handleTypes 包含VK_EXTERNAL_MEMORY_HANDLE_TYPE_SCREEN_BUFFER_BIT_QNX的VkExternalMemoryImageCreateInfo，则imageType必须为VK_IMAGE_TYPE_2D，mipmaps必须等于1或者基于extent.width, extent.height, 和 extent.depth的一个完整mipmap的等级个数
	54.如果pNext中包含一个externalFormat 不为0的VkExternalFormatQNX，则flags 不能包含VK_IMAGE_CREATE_MUTABLE_FORMAT_BIT，usage 只能为VK_IMAGE_USAGE_SAMPLED_BIT，tiling 必须为VK_IMAGE_TILING_OPTIMAL
	55.如果format是一个depth-stencil format，usage包含VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT，且pNext中包含一个VkImageStencilUsageCreateInfo，则VkImageStencilUsageCreateInfo::stencilUsage 必须也包含VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT
	56.如果format是一个depth-stencil format，usage不包含VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT，且pNext中包含一个VkImageStencilUsageCreateInfo，则VkImageStencilUsageCreateInfo::stencilUsage 必须不包含VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT
	57.如果format是一个depth-stencil format，usage包含VK_IMAGE_USAGE_TRANSIENT_ATTACHMENT_BIT，且pNext中包含一个VkImageStencilUsageCreateInfo，则VkImageStencilUsageCreateInfo::stencilUsage 必须也包含VK_IMAGE_USAGE_TRANSIENT_ATTACHMENT_BIT
	58.	如果format是一个depth-stencil format，usage不包含VK_IMAGE_USAGE_TRANSIENT_ATTACHMENT_BIT，且pNext中包含一个VkImageStencilUsageCreateInfo，则VkImageStencilUsageCreateInfo::stencilUsage 必须不包含VK_IMAGE_USAGE_TRANSIENT_ATTACHMENT_BIT
	59.如果format是一个depth-stencil format，且pNext中包含一个stencilUsage包含VK_IMAGE_USAGE_INPUT_ATTACHMENT_BIT的VkImageStencilUsageCreateInfo，则extent.width 必须小于等于VkPhysicalDeviceLimits::maxFramebufferWidth，extent.height 必须小于等于VkPhysicalDeviceLimits::maxFramebufferHeight
	60.如果shaderStorageImageMultisample 特性没有开启，format是一个depth-stencil format，且pNext中包含一个stencilUsage包含VK_IMAGE_USAGE_STORAGE_BIT的VkImageStencilUsageCreateInfo，则samples 必须为VK_SAMPLE_COUNT_1_BIT
	61.如果flags 包含VK_IMAGE_CREATE_CORNER_SAMPLED_BIT_NV，则（1）iamgeType 不能为VK_IMAGE_TYPE_2D 或 VK_IMAGE_TYPE_3D
															  （2）flags不能包含VK_IMAGE_CREATE_CUBE_COMPATIBLE_BIT且format 不能为一个depth/stencil format
															  （3）如果imageType 为 VK_IMAGE_TYPE_2D，extent.width 和 extent.height 必须大于1
															  （4）如果imageType 为 VK_IMAGE_TYPE_3D，extent.width, extent.height, 和 extent.depth 必须大于1
	62.如果usage 包含VK_IMAGE_USAGE_FRAGMENT_SHADING_RATE_ATTACHMENT_BIT_KHR，imageType 必须为 VK_IMAGE_TYPE_2D，samples必须为VK_SAMPLE_COUNT_1_BIT，
	63.如果shadingRateImage 特性开启且usage 包含VK_IMAGE_USAGE_SHADING_RATE_IMAGE_BIT_NV，tiling 必须为VK_IMAGE_TILING_OPTIMAL
	64.如果flags 包含VK_IMAGE_CREATE_SUBSAMPLED_BIT_EXT，tiling必须为VK_IMAGE_TILING_OPTIMAL，iamgeType必须为VK_IMAGE_TYPE_2D，flags 不能包含 VK_IMAGE_TYPE_2D ，mipLevels必须为1
	65.如果usage 包含VK_IMAGE_USAGE_INVOCATION_MASK_BIT_HUAWEI，tiling必须为VK_IMAGE_TILING_LINEAR
	66.如果VK_KHR_portability_subset拓展开启，则（1）如果VkPhysicalDevicePortabilitySubsetFeaturesKHR::imageView2DOn3DImage为 VK_FALSE，则flags不能包含VK_IMAGE_CREATE_2D_ARRAY_COMPATIBLE_BIT
												（2）如果VkPhysicalDevicePortabilitySubsetFeaturesKHR::multisampleArrayImage为VK_FALSE，且samples 不为VK_SAMPLE_COUNT_1_BIT，则arrayLayers必须为1
	67.如果pNext中包含一个viewFormatCount不为0的VkImageFormatListCreateInfo，则VkImageFormatListCreateInfo::pViewFormats的每一个元素必须和compatibility table中描述的format兼容的format，如果flags包含VK_IMAGE_CREATE_BLOCK_TEXEL_VIEW_COMPATIBLE_BIT，则是一个非压缩的size-compatible 的format
	68.如果flags 不包含VK_IMAGE_CREATE_MUTABLE_FORMAT_BIT且pNext中包含一个VkImageFormatListCreateInfo，则VkImageFormatListCreateInfo::viewFormatCount 必须为0或1
	69.如果usage 包含VK_IMAGE_USAGE_VIDEO_DECODE_SRC_BIT_KHR ，VK_IMAGE_USAGE_VIDEO_DECODE_DST_BIT_KHR或者VK_IMAGE_USAGE_VIDEO_DECODE_DPB_BIT_KHR 且flags 不包含VK_IMAGE_CREATE_VIDEO_PROFILE_INDEPENDENT_BIT_KHR，则pNext 中必须包含一个VkVideoProfileListInfoKHR结构，且VkVideoProfileListInfoKHR::profileCount 必须大于0，且VkVideoProfileListInfoKHR::pProfiles 必须包含至少一个VkVideoProfileInfoKHR结构指明一个decode operation
	70.如果usage 包含VK_IMAGE_USAGE_VIDEO_ENCODE_SRC_BIT_KHR ，VK_IMAGE_USAGE_VIDEO_ENCODE_DST_BIT_KHR或者VK_IMAGE_USAGE_VIDEO_ENCODE_DPB_BIT_KHR 且flags 不包含VK_IMAGE_CREATE_VIDEO_PROFILE_INDEPENDENT_BIT_KHR，则pNext 中必须包含一个VkVideoProfileListInfoKHR结构，且VkVideoProfileListInfoKHR::profileCount 必须大于0，且VkVideoProfileListInfoKHR::pProfiles 必须包含至少一个VkVideoProfileInfoKHR结构指明一个encode operation
	71.如果flags 包含VK_IMAGE_CREATE_VIDEO_PROFILE_INDEPENDENT_BIT_KHR，则（1）videoMaintenance1 必须开启
																		  （2）如果usage 不包含VK_IMAGE_USAGE_VIDEO_DECODE_DST_BIT_KHR，则usage 不能包含VK_IMAGE_USAGE_VIDEO_DECODE_DPB_BIT_KHR
																		  （3）usage 不能包含VK_IMAGE_USAGE_VIDEO_ENCODE_DPB_BIT_KHR
	72.如果pNext中包含一个profileCount 大于0的VkVideoProfileListInfoKHR，则supportedVideoFormat 必须为VK_TRUE
	73.如果VkImage 用来从VkBufferCollectionFUCHSIA 中导入memory，则pNext中应该包含一个VkBufferCollectionImageCreateInfoFUCHSIA
	74.如果multisampledRenderToSingleSampled 特性没有开启，flags不能包含VK_IMAGE_CREATE_MULTISAMPLED_RENDER_TO_SINGLE_SAMPLED_BIT_EXT
	75.如果flags包含 VK_IMAGE_CREATE_MULTISAMPLED_RENDER_TO_SINGLE_SAMPLED_BIT_EXT，samples 必须为VK_SAMPLE_COUNT_1_BIT
	76.如果pNext中包含一个VkImageCompressionControlEXT ，则（1）如果format为一个multi￾planar format，且VkImageCompressionControlEXT::flags 包含VK_IMAGE_COMPRESSION_FIXED_RATE_EXPLICIT_EXT，则VkImageCompressionControlEXT::compressionControlPlaneCount 必须等于format的plane数量
														   （2）如果format不为一个multi￾planar format，且VkImageCompressionControlEXT::flags 包含VK_IMAGE_COMPRESSION_FIXED_RATE_EXPLICIT_EXT，则VkImageCompressionControlEXT::compressionControlPlaneCount 必须等于1
														   （3）pNext中就不能包含一个VkImageDrmFormatModifierExplicitCreateInfoEXT
	77.如果flags 包含VK_IMAGE_CREATE_DESCRIPTOR_BUFFER_CAPTURE_REPLAY_BIT_EXT，则descriptorBufferCaptureReplay 特性必须开启
	78.如果pNext中包含一个VkOpaqueCaptureDescriptorDataCreateInfoEXT，flags 必须包含VK_IMAGE_CREATE_DESCRIPTOR_BUFFER_CAPTURE_REPLAY_BIT_EXT
	79.如果pNext中包含一个VkExportMetalObjectCreateInfoEXT，exportObjectType 必须是VK_EXPORT_METAL_OBJECT_TYPE_METAL_TEXTURE_BIT_EXT 或 VK_EXPORT_METAL_OBJECT_TYPE_METAL_IOSURFACE_BIT_EXT
	80.如果pNext中包含一个VkImportMetalTextureInfoEXT，则（1）其VkImportMetalTextureInfoEXT.plane 必须是VK_IMAGE_ASPECT_PLANE_0_BIT, VK_IMAGE_ASPECT_PLANE_1_BIT, 或 VK_IMAGE_ASPECT_PLANE_2_BIT
														 （2）image不含有一个multi-planar format，则kImportMetalTextureInfoEXT::plane 必须为VK_IMAGE_ASPECT_PLANE_0_BIT
														 （3）image含有一个只含有两个plane的multi-planar format，则kImportMetalTextureInfoEXT::plane 不能为VK_IMAGE_ASPECT_PLANE_2_BIT
	82.如果imageCreateFormatFeatures（参见image creation limits）不含有VK_FORMAT_FEATURE_2_HOST_IMAGE_TRANSFER_BIT_EXT，则usage 不能包含VK_IMAGE_USAGE_HOST_TRANSFER_BIT_EXT
	83.如果pNext中包含一个VkImageAlignmentControlCreateInfoMESA，tiling 必须为VK_IMAGE_TILING_OPTIMAL，pNext中就不能包含一个VkExternalMemoryImageCreateInfo

	*/


	//VkBufferCollectionImageCreateInfoFUCHSIA
	VkBufferCollectionImageCreateInfoFUCHSIA& bufferCollectionImageCreateInfo = imageCreateInfoEXT.bufferCollectionImageCreateInfoFUCHSIA;
	bufferCollectionImageCreateInfo.collection;//一个 VkBufferCollectionFUCHSIA 句柄
	bufferCollectionImageCreateInfo.index = 0;//是将从其中导入内存的buffer collection中的缓冲区的索引


	//VkImageStencilUsageCreateInfo
	VkImageStencilUsageCreateInfo& imageStencilUsageCreateInfo = imageCreateInfoEXT.imageStencilUsageCreateInfo;
	imageStencilUsageCreateInfo.stencilUsage = VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT;//是一个 VkImageUsageFlagBits组合值的位掩码，描述了image的stencil方面的预期用途。只指定stencil的用途，可以将该结构体链接到 VkPhysicalDeviceImageFormatInfo2并调用vkGetPhysicalDeviceImageFormatProperties2 查询额外的
	/*
	VkImageStencilUsageCreateInfo有效用法:
	1.stencilUsage 包含VK_IMAGE_USAGE_TRANSIENT_ATTACHMENT_BIT，其就不能包含除VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT 或者 VK_IMAGE_USAGE_INPUT_ATTACHMENT_BIT外的其他值
	*/

	//VkDedicatedAllocationImageCreateInfoNV
	//该结构体控制image是否会有一个绑定到它的专用内存分配。
	VkDedicatedAllocationImageCreateInfoNV& dedicatedAllocationImageCreateInfoNV = imageCreateInfoEXT.dedicatedAllocationImageCreateInfoNV;
	dedicatedAllocationImageCreateInfoNV.dedicatedAllocation = VK_FALSE;//指定image是否具有绑定到它的 dedicated allocation (专用分配)。
	/*
	VkDedicatedAllocationImageCreateInfoNV有效用法：
	1.如果 dedicatedAllocation 为 VK_TRUE, VkImageCreateInfo::flags 不能包含VK_IMAGE_CREATE_SPARSE_BINDING_BIT, VK_IMAGE_CREATE_SPARSE_RESIDENCY_BIT, 或者 VK_IMAGE_CREATE_SPARSE_ALIASED_BIT
	*/


	// VkExternalMemoryImageCreateInfo
	//该结构体 定义一组备份存储当前image的外部memory handle type
	VkExternalMemoryImageCreateInfo& externalMemoryImageCreateInfo = imageCreateInfoEXT.externalMemoryImageCreateInfo;
	externalMemoryImageCreateInfo.handleTypes = VK_EXTERNAL_MEMORY_HANDLE_TYPE_OPAQUE_FD_BIT;//是零或一个指定一个或多个外部内存句柄类型的VkExternalMemoryHandleTypeFlagBits组合值的位掩码。

	// VkExternalMemoryImageCreateInfoNV
	//该结构体 定义一组备份存储当前image的外部memory handle type
	VkExternalMemoryImageCreateInfoNV& externalMemoryImageCreateInfoNV = imageCreateInfoEXT.externalMemoryImageCreateInfoNV;
	externalMemoryImageCreateInfoNV.handleTypes = VK_EXTERNAL_MEMORY_HANDLE_TYPE_OPAQUE_FD_BIT;//是零或一个指定一个或多个外部内存句柄类型的VkExternalMemoryHandleTypeFlagBits组合值的位掩码。


	//VkExternalFormatANDROID
	VkExternalFormatANDROID& externalFormatANDROID = imageCreateInfoEXT.externalFormatANDROID;
	externalFormatANDROID.externalFormat = VK_FORMAT_UNDEFINED;//是为外部格式的实现定义的标识符
	/*
	VkExternalFormatANDROID有效用法：
	1.externalFormat 必须为0或者一个通过vkGetAndroidHardwareBufferPropertiesANDROID调用返回的VkAndroidHardwareBufferFormatPropertiesANDROID 中的externalFormat中一个值

	*/

	// VkExternalFormatQNX
	//该结构体创建一个QNX external format image
	VkExternalFormatQNX& externalFormatQNX = imageCreateInfoEXT.externalFormatQNX;
	externalFormatQNX.externalFormat = 0;//是为外部格式的实现定义的标识符
	/*
	VkExternalFormatQNX有效用法：
	1.externalFormat 必须为0或者一个通过vkGetScreenBufferPropertiesQNX调用返回的VkScreenBufferFormatPropertiesQNX 中的externalFormat中一个值
	*/

	//VkImageSwapchainCreateInfoKHR
	//该结构体表明创建的image将绑定到一个swapchain的memory上
	VkImageSwapchainCreateInfoKHR& imageSwapchainCreateInfoKHR = imageCreateInfoEXT.imageSwapchainCreateInfoKHR;
	imageSwapchainCreateInfoKHR.swapchain = VkSwapchainKHR{/*假设这是一个有效的VkSwapchainKHR*/ };//是VK_NULL_HANDLE或image将被绑定到的交换链的句柄。
	/*
	VkImageSwapchainCreateInfoKHR有效用法：
	1.如果swapchain不为VK_NULL_HANDLE，则VkImageCreateInfo的相关参数必须和创建swapchain时其image所用的参数匹配。

	*/

	//VkImageFormatListCreateInfo
	//该结构体包含所有在创建image view时所用到的format的集合
	VkImageFormatListCreateInfo& imageFormatListCreateInfo = imageCreateInfoEXT.imageFormatListCreateInfo;
	imageFormatListCreateInfo.viewFormatCount = 0;//viewFormatCount是viewFormats数组的元素个数。如果为0，则pViewFormats被忽略，image的创建将和不含该结构体时创建的一样
	imageFormatListCreateInfo.pViewFormats = VK_NULL_HANDLE;//是指向VkFormat值数组的指针，指定在创建此image的image view时可以使用的所有格式。如果viewFormatCount 不为0，则pViewFormats 中不能有元素为VK_FORMAT_UNDIFIED



	// VkImageDrmFormatModifierListCreateInfoEXT
	//该结构体指明image创建时将以列举在该结构体中的 Linux DRM format modifiers的一个元素创建，具体是哪一个取决于实现
	VkImageDrmFormatModifierListCreateInfoEXT& imageDrmFormatModifierListCreateInfoEXT = imageCreateInfoEXT.imageDrmFormatModifierListCreateInfoEXT;
	imageDrmFormatModifierListCreateInfoEXT.drmFormatModifierCount = 1;//是pDrmFormatModifiers中的元素个数
	uint64_t drmFormatModifier;
	imageDrmFormatModifierListCreateInfoEXT.pDrmFormatModifiers = &drmFormatModifier;//是一个 Linux DRM format modifiers数组首地址指针
	/*
	VkImageDrmFormatModifierListCreateInfoEXT有效用法：
	1.pDrmFormatModifiers中每个元素必须和VkImageCreateInfo的pNext中的通过查询获得的VkPhysicalDeviceImageFormatInfo2.pNext中的VkPhysicalDeviceImageDrmFormatModifierInfoEXT的参数兼容
	2.drmFormatModifierCount必须大于0
	*/

	//VkImageDrmFormatModifierExplicitCreateInfoEXT
	//该结构体指明image创建时将以该结构体中的 Linux DRM format modifiers 以及 memory layout 创建
	VkImageDrmFormatModifierExplicitCreateInfoEXT& imageDrmFormatModifierExplicitCreateInfoEXT = imageCreateInfoEXT.imageDrmFormatModifierExplicitCreateInfoEXT;
	imageDrmFormatModifierExplicitCreateInfoEXT.drmFormatModifierPlaneCount = 1;//是image中memory plane的数量（参见VkDrmFormatModifierPropertiesEXT）以及pPlaneLayouts 数组的长度。
	imageDrmFormatModifierExplicitCreateInfoEXT.drmFormatModifier = 0;//是image创建的  Linux DRM format modifier
	VkSubresourceLayout planeLayout;
	imageDrmFormatModifierExplicitCreateInfoEXT.pPlaneLayouts = &planeLayout;//是一个指向描述image memory plane的 VkSubresourceLayout结构数组的指针。第i个元素描述 image的第i个memory plane layout（VK_IMAGE_ASPECT_MEMORY_PLANE_i_BIT_EXT），每个元素的size会被忽略
	/*
	VkImageDrmFormatModifierExplicitCreateInfoEXT有效用法：
	1.drmFormatModifier必须和VkImageCreateInfo的pNext中的通过查询获得的VkPhysicalDeviceImageFormatInfo2.pNext中的VkPhysicalDeviceImageDrmFormatModifierInfoEXT的参数兼容
	2.drmFormatModifierPlaneCount必须等于关联到VkImageCreateInfo::format和drmFormatModifier的VkDrmFormatModifierPropertiesEXT::drmFormatModifierPlaneCount相同，通过查询VkDrmFormatModifierPropertiesListEXT获取
	3.pPlaneLayouts的每个元素的size必须为0，如果VkImageCreateInfo::arrayLayers 为1，则每个元素的arrayPitch 必须为0，如果VkImageCreateInfo::extent.depth 为1，则每个元素的depthPitch 必须为0

	*/


	// VkImageCompressionControlEXT
	{
	VkImageCompressionControlEXT& imageCompressionControlEXT = imageCreateInfoEXT.imageCompressionControlEXT;
	imageCompressionControlEXT.flags = 0;//是一个 VkImageCompressionControlFlagBitsEXT 组合值，指定了image压缩控制的选项。
	/*
	VkImageCompressionFlagBitsEXT:
	VK_IMAGE_COMPRESSION_DEFAULT_EXT：指明iamge使用默认压缩设置，实现不能使用fixed-rate 压缩
	VK_IMAGE_COMPRESSION_FIXED_RATE_DEFAULT_EXT： 指明实现可能会选择任何支持的fixed-rate 压缩设置基于image的属性采取实现定义的行为
	VK_IMAGE_COMPRESSION_FIXED_RATE_EXPLICIT_EXT： 指明fixed-rate 压缩可能会被使用且允许通过VkImageCompressionControlEXT::pFixedRateFlags指定压缩速率
	VK_IMAGE_COMPRESSION_DISABLED_EXT： 指明所有lossless 压缩和 fixed-rate 压缩应该被禁用
	*/
	imageCompressionControlEXT.pFixedRateFlags = VK_NULL_HANDLE;/*是NULL或指向VkImageCompressionFixedRateFlagsEXT位字段数组的指针，描述每个图像平面允许的固定速率压缩率。如果flags不包含VK_IMAGE_COMPRESSION_FIXED_RATE_EXPLICIT_EXT，则会忽略它。第i个元素指明image的第i个 memory plane的固定速率压缩率。
	VkImageCompressionFixedRateFlagBitsEXT:

	VK_IMAGE_COMPRESSION_FIXED_RATE_NONE_EXT： 指明 fixed-rate 压缩不会被使用
	VK_IMAGE_COMPRESSION_FIXED_RATE_1BPC_BIT_EXT： 指明fixed-rate 压缩每个component使用[1,2)中的一个bitrate
	VK_IMAGE_COMPRESSION_FIXED_RATE_2BPC_BIT_EXT： 指明fixed-rate 压缩每个component使用[2,3)中的一个bitrate
	VK_IMAGE_COMPRESSION_FIXED_RATE_3BPC_BIT_EXT： 指明fixed-rate 压缩每个component使用[3,4)中的一个bitrate
	VK_IMAGE_COMPRESSION_FIXED_RATE_4BPC_BIT_EXT： 指明fixed-rate 压缩每个component使用[4,5)中的一个bitrate
	VK_IMAGE_COMPRESSION_FIXED_RATE_5BPC_BIT_EXT： 指明fixed-rate 压缩每个component使用[5,6)中的一个bitrate
	VK_IMAGE_COMPRESSION_FIXED_RATE_6BPC_BIT_EXT： 指明fixed-rate 压缩每个component使用[6,7)中的一个bitrate
	VK_IMAGE_COMPRESSION_FIXED_RATE_7BPC_BIT_EXT： 指明fixed-rate 压缩每个component使用[7,8)中的一个bitrate
	VK_IMAGE_COMPRESSION_FIXED_RATE_8BPC_BIT_EXT： 指明fixed-rate 压缩每个component使用[8,9)中的一个bitrate
	VK_IMAGE_COMPRESSION_FIXED_RATE_9BPC_BIT_EXT： 指明fixed-rate 压缩每个component使用[9,10)中的一个bitrate
	VK_IMAGE_COMPRESSION_FIXED_RATE_10BPC_BIT_EXT： 指明fixed-rate 压缩每个component使用[10,11)中的一个bitrate
	VK_IMAGE_COMPRESSION_FIXED_RATE_11BPC_BIT_EXT： 指明fixed-rate 压缩每个component使用[11,12)中的一个bitrate
	VK_IMAGE_COMPRESSION_FIXED_RATE_12BPC_BIT_EXT： 指明fixed-rate 压缩每个component使用至少12个bitrate

	//这里的机制不是很清楚，待后续深入


	//查询图像的压缩速率属性
	---->调用vkGetImageSubresourceLayout2KHR 或者 vkGetImageSubresourceLayout2EXT.传入pNext中含有一个 VkImageCompressionPropertiesEXT的VkSubresourceLayout2EXT
	//查询format的压缩速率属性
	---->调用vkGetPhysicalDeviceImageFormatProperties2.传入pNext中含有一个VkImageCompressionPropertiesEXT的  VkImageFormatProperties2

	*/
	{
		//查询图像的压缩速率属性
		//---- > 调用vkGetImageSubresourceLayout2KHR 或者 vkGetImageSubresourceLayout2EXT.传入pNext中含有一个 VkImageCompressionPropertiesEXT的VkSubresourceLayout2EXT
		//查询format的压缩速率属性
		//---- > 调用vkGetPhysicalDeviceImageFormatProperties2.传入pNext中含有一个VkImageCompressionPropertiesEXT的  VkImageFormatProperties2
		//由于固定速率压缩默认禁用，传递给vkGetPhysicalDeviceImageFormatProperties2的VkImageCompressionPropertiesEXT结构不会表示任何固定速率压缩支持，除非VkPhysicalDeviceImageFormatInfo2结构的pNext链中也包含VkImageCompressionControlEXT结构
		VkImageCompressionPropertiesEXT imageCompressionPropertiesEXT{};
		imageCompressionPropertiesEXT.sType = VK_STRUCTURE_TYPE_IMAGE_COMPRESSION_PROPERTIES_EXT;
		imageCompressionPropertiesEXT.pNext = nullptr;
		imageCompressionPropertiesEXT.imageCompressionFlags;//返回一个描述应用于图像的压缩控件的值。该值将是VK_IMAGE_COMPRESSION_DEFAULT_EXT表示没有固定速率压缩，VK_IMAGE_COMPRESSION_FIXED_RATE_EXPLICIT_EXT表示固定速率压缩，或者VK_IMAGE_COMPRESSION_DISABLED_EXT表示没有压缩。
		imageCompressionPropertiesEXT.imageCompressionFixedRateFlags;//返回一个VkImageCompressionFixedRateFlagsEXT值，它描述了应用于图像的指定方面的压缩率。
	}

	imageCompressionControlEXT.compressionControlPlaneCount = 1;//是pFixedRateFlags数组的长度。
	/*
	VkImageCompressionControlEXT有效用法:
	1.flags必须是VK_IMAGE_COMPRESSION_DEFAULT_EXT, VK_IMAGE_COMPRESSION_FIXED_RATE_DEFAULT_EXT, VK_IMAGE_COMPRESSION_FIXED_RATE_EXPLICIT_EXT,或者 VK_IMAGE_COMPRESSION_DISABLED_EXT其中一个
	2.如果flags 包含VK_IMAGE_COMPRESSION_FIXED_RATE_EXPLICIT_EXT，则pFixedRateFlags必须不为NULL，
	*/
	}



	//VkImageAlignmentControlCreateInfoMESA
	//该结构体描述了image的对齐方式
	VkImageAlignmentControlCreateInfoMESA& imageAlignmentControlCreateInfoMESA = imageCreateInfoEXT.imageAlignmentControlCreateInfoMESA;
	imageAlignmentControlCreateInfoMESA.maximumRequestedAlignment = 16;//指定image的最大对齐方式。不能大于VkMemoryRequirements::alignment
	/*
	VkImageAlignmentControlCreateInfoMESA有效用法:
	1.如果maximumRequestedAlignment 不为0，则它必须是2的幂，和supportedImageAlignmentMask的位与操作结果必须不为0
	2.imageAlignmentControl在device上必须开启

	*/



	vkCreateImage(device, &imageCreateInfo, nullptr, &image);/*
	vkCreateImage有效用法:
	1.如果pCreateInfo 中的flags包含VK_IMAGE_CREATE_SPARSE_BINDING_BIT，且extendedSparseAddressSpace 特性没有开启，则创建这个VkImage 需要的sparse memory数量不能导致在device上 的所有有效的sparse resources memory的总和超过 VkPhysicalDeviceLimits::sparseAddressSpaceSize
	
	2.如果pCreateInfo 中的flags包含VK_IMAGE_CREATE_SPARSE_BINDING_BIT，且extendedSparseAddressSpace 特性开启，pCreateInfo的 usage不包含VkPhysicalDeviceExtendedSparseAddressSpacePropertiesNV::extendedSparseImageUsageFlags中有的，则排除掉以pCreateInfo的usage包含在VkPhysicalDeviceExtendedSparseAddressSpacePropertiesNV::extendedSparseBufferUsageFlags中创建的VkBuffer和pCreateInfo的usage包含在
					VkPhysicalDeviceExtendedSparseAddressSpacePropertiesNV::extendedSparseImageUsageFlags创建的VkImage外，创建这个VkImage 需要的sparse memory数量不能导致在device上 的所有有效的sparse resources memory的总和超过 VkPhysicalDeviceLimits::sparseAddressSpaceSize
	3.如果pCreateInfo 中的flags包含VK_IMAGE_CREATE_SPARSE_BINDING_BIT,且extendedSparseAddressSpace 特性开启,创建这个VkImage 需要的sparse memory数量不能导致在device上 的所有有效的sparse resources memory的总和超过 VkPhysicalDeviceExtendedSparseAddressSpacePropertiesNV::extendedSparseAddressSpaceSize
	4.如果pCreateInfo 中的pNext中含有一个VkBufferCollectionImageCreateInfoFUCHSIA，则pCreateInfo必须匹配在匹配标准小 系统选定的除了VkImageCreateInfo::extent 以及VkImageCreateInfo::usage的VkImageCreateInfo

	*/



	//image subresource layout
	{
		/*
		image坐标地址计算：
		1.非压缩format：
			// (x,y,z,layer) are in texel coordinates
			address(x,y,z,layer) = layer*arrayPitch + z*depthPitch + y*rowPitch + x*elementSize + offset
		2.压缩format
			// (x,y,z,layer) are in compressed texel block coordinates
			address(x,y,z,layer) = layer*arrayPitch + z*depthPitch + y*rowPitch + x*compressedTexelBlockByteSize + offset;
		*/

		VkSubresourceLayout subresourceLayout;
		subresourceLayout.arrayPitch;//描述了当前image subresource每一个array layer所需要的字节内存大小
		subresourceLayout.rowPitch;//描述了当前image subresource每一行texel所需要的字节内存大小
		subresourceLayout.depthPitch;//描述了3维图像当前image subresource每一个slice之间所需要的字节内存大小
		subresourceLayout.offset;//是当前image subresource从image的开头或者image subresource开始的plane 开始的字节偏移量
		subresourceLayout.size;//是该image subresource的字节大小，包含rowPitch中需要的额外内存
		VkImageSubresource imageSubresource;
		imageSubresource.arrayLayer = 0;//指明array layer
		imageSubresource.aspectMask = VK_IMAGE_ASPECT_PLANE_0_BIT;//是一个指明 image aspect的 VkImageAspectFlags 值
		imageSubresource.mipLevel = 0;//指明mipmap level
		//查询image subresource 的layout布局
		vkGetImageSubresourceLayout(device, image, &imageSubresource, &subresourceLayout);
		/*
		vkGetImageSubresourceLayout有效用法：
		1.image 必须以tiling为VK_IMAGE_TILING_LINEAR或 VK_IMAGE_TILING_DRM_FORMAT_MODIFIER_EXT创建
		2.pSubresource的aspectMask 必须只含有一个比特位
		3.pSubresource的mipLevel必须小于image创建指定的mipLevels，arrayLayer必须小于image创建指定的arrayLayers
		4.如果image的format是一个color format且不是一个multi-planar image format，且tiling 为VK_IMAGE_TILING_LINEAR 或 VK_IMAGE_TILING_OPTIMAL，则pSubresource的 aspectMask必须为 VK_IMAGE_ASPECT_COLOR_BIT
		5.如果image的format有一个depth component，则pSubresource的aspectMask 必须包含VK_IMAGE_ASPECT_DEPTH_BIT
		6.如果image的format有一个stencil component，则pSubresource的aspectMask 必须包含VK_IMAGE_ASPECT_STENCIL_BIT
		7.如果image的format不包含一个stencil 或 depth component，则pSubresource的aspectMask 不能包含VK_IMAGE_ASPECT_DEPTH_BIT 或VK_IMAGE_ASPECT_STENCIL_BIT
		8.如果image的tiling 为 VK_IMAGE_TILING_LINEAR且含有一个multi-planar 的 image format，则pSubresource的aspectMask 必须是一个单独有效的multi-planar mask比特位
		9.如果image 以VK_EXTERNAL_MEMORY_HANDLE_TYPE_ANDROID_HARDWARE_BUFFER_BIT_ANDROID 类型的external memory handle type创建，则该image必须已经绑定了memory
		10.如果image的tiling 为VK_IMAGE_TILING_DRM_FORMAT_MODIFIER_EXT，则pSubresource的aspectMask 必须为VK_IMAGE_ASPECT_MEMORY_PLANE_i_BIT_EXT且 i必须小于和 image的format以及 VkImageDrmFormatModifierPropertiesEXT::drmFormatModifier 相关联的 VkDrmFormatModifierPropertiesEXT::drmFormatModifierPlaneCount

		*/

		VkSubresourceLayout2KHR subresourceLayout2KHR{};
		subresourceLayout2KHR.sType = VK_STRUCTURE_TYPE_SUBRESOURCE_LAYOUT_2_KHR;
		subresourceLayout2KHR.pNext = nullptr;
		subresourceLayout2KHR.subresourceLayout = subresourceLayout; //是一个VkSubresourceLayout （vkGetImageSubresourceLayout的参数）

		VkImageSubresource2KHR imageSubresourceKHR{};
		imageSubresourceKHR.sType = VK_STRUCTURE_TYPE_IMAGE_SUBRESOURCE_2_KHR;
			//VkImageSubresource2KHR.pNext
			{
				//当image创建指定了VK_HOST_IMAGE_COPY_MEMCPY_EXT，然后要查询使用 vkCopyMemoryToImageEXT 或者 vkCopyImageToMemoryEXT 命令拷贝到image或从image拷贝的需要的内存大小
				//VkSubresourceHostMemcpySizeEXT链接到VkImageSubresource2KHR.pNext
				VkSubresourceHostMemcpySizeEXT subresourceHostMemcpySizeEXT{};
				subresourceHostMemcpySizeEXT.sType = VK_STRUCTURE_TYPE_SUBRESOURCE_HOST_MEMCPY_SIZE_EXT;
				subresourceHostMemcpySizeEXT.pNext = nullptr;
				subresourceHostMemcpySizeEXT.size = 0;//为image subresource的字节大小

				//VkImageCompressionPropertiesEXT链接到VkImageSubresource2KHR.pNext
				VkImageCompressionPropertiesEXT  imageCompressionPropertiesEXT{  };//前面已经说明过该结构体的作用这里边不再进行说明

				


			}
		imageSubresourceKHR.pNext = nullptr;//可以包含一个 VkImageCompressionPropertiesEXT 或 VkSubresourceHostMemcpySizeEXT
		imageSubresourceKHR.imageSubresource = imageSubresource;// 是一个 VkImageSubresource （vkGetImageSubresourceLayout的参数）.
		//查询image subresource 的layout布局,和vkGetImageSubresourceLayout相似，只是可以查询时可以附加一些额外信息，等效于vkGetImageSubresourceLayout2EXT,该接口可以查询VK_IMAGE_TILING_OPTIMAL的imagesubresource但是返回的值时未定义的
		vkGetImageSubresourceLayout2KHR(device, image, &imageSubresourceKHR, &subresourceLayout2KHR);
		/*
		vkGetImageSubresourceLayout2KHR或vkGetImageSubresourceLayout2EXT有效用法:
		1.pSubresource的aspectMask 必须只含有一个比特位
		2.pSubresource的mipLevel必须小于image创建指定的mipLevels，arrayLayer必须小于image创建指定的arrayLayers
		3.如果image的format是一个color format且不是一个multi-planar image format，且tiling 为VK_IMAGE_TILING_LINEAR 或 VK_IMAGE_TILING_OPTIMAL，则pSubresource的 aspectMask必须为 VK_IMAGE_ASPECT_COLOR_BIT
		4.如果image的format有一个depth component，则pSubresource的aspectMask 必须包含VK_IMAGE_ASPECT_DEPTH_BIT
		5.如果image的format有一个stencil component，则pSubresource的aspectMask 必须包含VK_IMAGE_ASPECT_STENCIL_BIT
		6.如果image的format不包含一个stencil 或 depth component，则pSubresource的aspectMask 不能包含VK_IMAGE_ASPECT_DEPTH_BIT 或VK_IMAGE_ASPECT_STENCIL_BIT
		7.如果image的tiling 为 VK_IMAGE_TILING_LINEAR且含有一个multi-planar 的 image format，则pSubresource的aspectMask 必须是一个单独有效的multi-planar mask比特位
		8.如果image 以VK_EXTERNAL_MEMORY_HANDLE_TYPE_ANDROID_HARDWARE_BUFFER_BIT_ANDROID 类型的external memory handle type创建，则该image必须已经绑定了memory
		9.如果image的tiling 为VK_IMAGE_TILING_DRM_FORMAT_MODIFIER_EXT，则pSubresource的aspectMask 必须为VK_IMAGE_ASPECT_MEMORY_PLANE_i_BIT_EXT且 i必须小于和 image的format以及 VkImageDrmFormatModifierPropertiesEXT::drmFormatModifier 相关联的 VkDrmFormatModifierPropertiesEXT::drmFormatModifierPlaneCount
		*/


	
		VkDeviceImageSubresourceInfoKHR deviceImageSubresourceInfoKHR{};
		deviceImageSubresourceInfoKHR.sType = VK_STRUCTURE_TYPE_DEVICE_IMAGE_SUBRESOURCE_INFO_KHR;
		deviceImageSubresourceInfoKHR.pNext = nullptr;
		deviceImageSubresourceInfoKHR.pCreateInfo = &imageCreateInfo;//是一个指向 VkImageCreateInfo 结构的指针，包含影响创建image的参数。
		deviceImageSubresourceInfoKHR.pSubresource = &imageSubresourceKHR;//是指向VkImageSubresource2KHR结构的指针，为查询选择特定的图像子资源
		/*
		VkDeviceImageSubresourceInfoKHR有效用法:
		1.pSubresource的aspectMask 必须只含有一个比特位
		2.pSubresource的mipLevel必须小于pCreateInfo指定的mipLevels，arrayLayer必须小于pCreateInfo指定的arrayLayers
		3.如果image的format是一个color format且不是一个multi-planar image format，且pCreateInfo的tiling 为VK_IMAGE_TILING_LINEAR 或 VK_IMAGE_TILING_OPTIMAL，则pSubresource的 aspectMask必须为 VK_IMAGE_ASPECT_COLOR_BIT
		4.如果pCreateInfo的format有一个depth component，则pSubresource的aspectMask 必须包含VK_IMAGE_ASPECT_DEPTH_BIT
		5.如果pCreateInfo的format有一个stencil component，则pSubresource的aspectMask 必须包含VK_IMAGE_ASPECT_STENCIL_BIT
		6.如果pCreateInfo的format不包含一个stencil 或 depth component，则pSubresource的aspectMask 不能包含VK_IMAGE_ASPECT_DEPTH_BIT 或VK_IMAGE_ASPECT_STENCIL
		7.如果pCreateInfo的tiling 为 VK_IMAGE_TILING_LINEAR且含有一个multi-planar 的 image format，则pSubresource的aspectMask 必须是一个单独有效的multi-planar mask比特位
		*/
		
		//查询一个image subresource的memory layout，不需要指定一个image,和 vkGetImageSubresourceLayout2KHR类似，但是是通过 VkImageCreateInfo来指定image
		vkGetDeviceImageSubresourceLayoutKHR(device, &deviceImageSubresourceInfoKHR, &subresourceLayout2KHR);




		VkImageDrmFormatModifierPropertiesEXT imageDrmFormatModifierPropertiesEXT{};
		imageDrmFormatModifierPropertiesEXT.sType = VK_STRUCTURE_TYPE_IMAGE_DRM_FORMAT_MODIFIER_PROPERTIES_EXT;
		imageDrmFormatModifierPropertiesEXT.pNext = nullptr;
		imageDrmFormatModifierPropertiesEXT.drmFormatModifier;//返回image的 DRM format modifier。


		//如果一个image是用VK_IMAGE_TILING_DRM_FORMAT_MODIFIER_EXT创建的,其他tiling不行，那么该图像就有一个Linux DRM format modifier。查询这个modifier
		vkGetImageDrmFormatModifierPropertiesEXT(device, image, &imageDrmFormatModifierPropertiesEXT);

	}

	vkDestroyImage(device, image, nullptr);



	//Image Format Features 参见p1076
	{
	//......
	}

	//Corner-Sampled Images
	{
	//corner-sampled image是一个非标准化的texel坐标以整数值而不是半整数值为中心的图像。参见p1077
	}

	//Image Mip Level Sizing
	{
		//complete mipmap chain是mipmap level的全集，从最大的level到最小的level，
		// 对传统的image，即mipmal level数为 ⌊log2(max (width0 , height0 , depth0))⌋ + 1,第n层和第n+1层的mipmap level的width，height，depth满足 Sn+1 = max(⌊S/2⌋, 1),最小的mipmap为1，1*1，1*1*1
		// 对corner-sampled images,即mipmal level数为 log2(max (width0 , height0 , depth0)),第n层和第n+1层的mipmap level的width，height，depth满足 Sn+1 = max(⌈Sn/2⌉, 2),最小的mipmap为1*1，1*1*1，不支持一维
	}

	//image layout
	{
		//每个image subresource 都有一个image layout，不同的subresource 的image layout可以不同




	}



}

struct ImageViewCreateInfoEXT {
	VkExportMetalObjectCreateInfoEXT exportMetalObjectCreateInfoEXT{};
	VkImageViewASTCDecodeModeEXT imageViewASTCDecodeModeEXT{};
	VkImageViewMinLodCreateInfoEXT imageViewMinLodCreateInfoEXT{};
	VkImageViewSampleWeightCreateInfoQCOM imageViewSampleWeightCreateInfoQCOM{};
	VkImageViewSlicedCreateInfoEXT imageViewSlicedCreateInfoEXT{};
	VkImageViewUsageCreateInfo imageViewUsageCreateInfo{};
	VkOpaqueCaptureDescriptorDataCreateInfoEXT OpaqueCaptureDescriptorDataCreateInfoEXT{};
	VkSamplerYcbcrConversionInfo samplerYcbcrConversionInfo{};
	ImageViewCreateInfoEXT() {
		Init();
	}
	void Init() {
		exportMetalObjectCreateInfoEXT.sType = VK_STRUCTURE_TYPE_EXPORT_METAL_OBJECT_CREATE_INFO_EXT;
		imageViewASTCDecodeModeEXT.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_ASTC_DECODE_MODE_EXT;
		imageViewMinLodCreateInfoEXT.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_MIN_LOD_CREATE_INFO_EXT;
		imageViewSampleWeightCreateInfoQCOM.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_SAMPLE_WEIGHT_CREATE_INFO_QCOM;
		imageViewSlicedCreateInfoEXT.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_SLICED_CREATE_INFO_EXT;
		imageViewUsageCreateInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_USAGE_CREATE_INFO;
		OpaqueCaptureDescriptorDataCreateInfoEXT.sType = VK_STRUCTURE_TYPE_OPAQUE_CAPTURE_DESCRIPTOR_DATA_CREATE_INFO_EXT;
		samplerYcbcrConversionInfo.sType = VK_STRUCTURE_TYPE_SAMPLER_YCBCR_CONVERSION_INFO_KHR;



	}
};


void ResourceCreationTest::ImageViewCreateTest()
{
	/*
	shaders不能直接访问image对象用于读取或写入图像数据。相反，将使用表示image subresource的连续范围并包含其他元数据的image view来进行访问image。image view必须在兼容类型的image上创建，并且必须表示image subresource的有效子集。
	*/


	
	
	VkImageView imageView{};
	VK_REMAINING_ARRAY_LAYERS;//VK_REMAINING_ARRAY_LAYERS  是一个特殊的常量值，用于图像视图，用来表示图像中基底层后的所有剩余数组层都应该包含在视图中。
	VK_REMAINING_MIP_LEVELS;//VK_REMAINING_MIP_LEVELS 是一个特殊的常量值，用于图像视图，用来表示在基础级别之后的图像中剩余的所有mipmap级别都应该包含在视图中

	//image view 的用法隐含（隐含规则见p1087）在image 创建时候usage指定的内存，但可以在VkImageViewCreateInfo的pNext中包含一个VkImageViewUsageCreateInfo进行显示指定，一些其他的规则见p1087
	{
		/*
		 Image type 和 image view type 兼容需求表

		Image View Type					|		 Compatible Image Types
		VK_IMAGE_VIEW_TYPE_1D			|	VK_IMAGE_TYPE_1D
		VK_IMAGE_VIEW_TYPE_1D_ARRAY		|	VK_IMAGE_TYPE_1D
		VK_IMAGE_VIEW_TYPE_2D			|	VK_IMAGE_TYPE_2D , VK_IMAGE_TYPE_3D
		VK_IMAGE_VIEW_TYPE_2D_ARRAY		|	VK_IMAGE_TYPE_2D , VK_IMAGE_TYPE_3D
		VK_IMAGE_VIEW_TYPE_CUBE			|	VK_IMAGE_TYPE_2D
		VK_IMAGE_VIEW_TYPE_CUBE_ARRAY	|	VK_IMAGE_TYPE_2D
		VK_IMAGE_VIEW_TYPE_3D			|	VK_IMAGE_TYPE_3D
		*/
	}
	VkImageViewCreateInfo imageViewCreateInfo{};
	imageViewCreateInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
		ImageViewCreateInfoEXT imageViewCreateInfoEXT{};
	imageViewCreateInfo.pNext = &imageViewCreateInfoEXT.exportMetalObjectCreateInfoEXT;
	imageViewCreateInfo.flags = 0;/*是指定image view的附加参数的 VkImageViewCreateFlagBits 组合值的位掩码。
	VkImageViewCreateFlagBits:
	VK_IMAGE_VIEW_CREATE_FRAGMENT_DENSITY_MAP_DYNAMIC_BIT_EXT: 指明device将在VK_PIPELINE_STAGE_FRAGMENT_DENSITY_PROCESS_BIT_EXT 阶段读取ragment density map
	VK_IMAGE_VIEW_CREATE_FRAGMENT_DENSITY_MAP_DEFERRED_BIT_EXT: 指明host将在render pass记录到的primary command buffer的vkEndCommandBuffer命令执行期间读取ragment density map
	VK_IMAGE_VIEW_CREATE_DESCRIPTOR_BUFFER_CAPTURE_REPLAY_BIT_EXT: 指明image view可以在capturing 和 replaying (e.g. for trace capture and replay)和descriptor buffers 一起使用，参见VkOpaqueCaptureDescriptorDataCreateInfoEXT（p1392）

	*/
	imageViewCreateInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;//是指定image view类型的 VkImageViewType值
	imageViewCreateInfo.format = VK_FORMAT_UNDEFINED;//指明用来解释image texel blocks的format和类型的一个 VkFormat值
		VkComponentMapping componentsMapping;
		componentsMapping.r = VK_COMPONENT_SWIZZLE_IDENTITY;//是一个 VkComponentSwizzle值，指定shader输出vec的R分量的分量值
		componentsMapping.g = VK_COMPONENT_SWIZZLE_IDENTITY;//是一个 VkComponentSwizzle值，指定shader输出vec的G分量的分量值
		componentsMapping.b = VK_COMPONENT_SWIZZLE_IDENTITY;//是一个 VkComponentSwizzle值，指定shader输出vec的B分量的分量值
		componentsMapping.a = VK_COMPONENT_SWIZZLE_IDENTITY;//是一个 VkComponentSwizzle值，指定shader输出vec的A分量的分量值
		/*
		
        VK_COMPONENT_SWIZZLE_IDENTITY:  指明这个分量component设置为 identity swizzle.
        VK_COMPONENT_SWIZZLE_ZERO:  指明这个分量component设置为 0.
		VK_COMPONENT_SWIZZLE_ONE:  指明这个分量component设置为1或1.0，取决于image view format是一个整数还是浮点型的format，参见p4027  Format Definition
		VK_COMPONENT_SWIZZLE_R:  指明这个分量component设置为image的 R 分量component
        VK_COMPONENT_SWIZZLE_G:  指明这个分量component设置为image的 G 分量component
        VK_COMPONENT_SWIZZLE_B:  指明这个分量component设置为image的 B 分量component
        VK_COMPONENT_SWIZZLE_A:  指明这个分量component设置为image的 A 分量component

		componeny设置为VK_COMPONENT_SWIZZLE_IDENTITY等价于：
		Component       |       Identity Mapping
		components.r	|	 VK_COMPONENT_SWIZZLE_R
		components.g	|	 VK_COMPONENT_SWIZZLE_G
		components.b	|	 VK_COMPONENT_SWIZZLE_B
		components.a	|	 VK_COMPONENT_SWIZZLE_A
		*/
	imageViewCreateInfo.components = componentsMapping;//是一种 VkComponentMapping 结构体，指定color component（或depth或stencil component转换为color component后）的重新映射规则。该规则主要是用于shaders代码中vec component是如何映射到image component的
	imageViewCreateInfo.image = VkImage{/*假设这是一个有效的VkImage*/ }; //指明从那个image上创建image view
		VkImageSubresourceRange imageSubresourceRange{};
		imageSubresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;/*是 VkImageAspectFlagBits组合值的位掩码，指定image view中包含image的哪个aspect。如果包含VK_IMAGE_ASPECT_COLOR_BIT,就不能再包含VK_IMAGE_ASPECT_PLANE_0_BIT, VK_IMAGE_ASPECT_PLANE_1_BIT,或者 VK_IMAGE_ASPECT_PLANE_2_BIT，且不能包含任何 VK_IMAGE_ASPECT_MEMORY_PLANE_i_BIT_EXT
		VkImageAspectFlagBits:
        VK_IMAGE_ASPECT_NONE:  指明没有image aspect, 或者 image aspect 不可应用.
        VK_IMAGE_ASPECT_COLOR_BIT:  指明 color aspect.
        VK_IMAGE_ASPECT_DEPTH_BIT:  指明 depth aspect.
        VK_IMAGE_ASPECT_STENCIL_BIT:  指明 stencil aspect.
        VK_IMAGE_ASPECT_METADATA_BIT:  指明用在sparse resource operations的 metadata aspect used 
        VK_IMAGE_ASPECT_PLANE_0_BIT:  指明multi-planar image format 的 plane 0 
        VK_IMAGE_ASPECT_PLANE_1_BIT:  指明multi-planar image format 的 plane 1
        VK_IMAGE_ASPECT_PLANE_2_BIT:  指明multi-planar image format 的 plane 2
        VK_IMAGE_ASPECT_MEMORY_PLANE_0_BIT_EXT:  指明 memory plane 0.
        VK_IMAGE_ASPECT_MEMORY_PLANE_1_BIT_EXT:  指明 memory plane 1.
        VK_IMAGE_ASPECT_MEMORY_PLANE_2_BIT_EXT:  指明 memory plane 2.
        VK_IMAGE_ASPECT_MEMORY_PLANE_3_BIT_EXT:  指明 memory plane 3
		
		*/
		imageSubresourceRange.baseArrayLayer = 0;//指明image view可访问的image的第一个array layer。对于cube map,从baseArrayLayer 开始依次表示+X,-X,+Y,-Y,+Z,-Z
		imageSubresourceRange.layerCount = 1;//指明image view从baseArrayLayer开始可访问的array layer的数量。如果为VK_REMAINING_ARRAY_LAYERS则表明使用baseArrayLayer开始所有的array layer，如果不为VK_REMAINING_ARRAY_LAYERS则必须大于0
		imageSubresourceRange.baseMipLevel = 0;//指明image view可访问的image的第一个mipmap level
		imageSubresourceRange.levelCount = 1;//指明image view从baseMipLevel开始可访问的mipmap level的数量。如果为VK_REMAINING_MIP_LEVELS则表明使用baseMipLevel开始所有的array layer，如果不为VK_REMAINING_MIP_LEVELS则必须大于0
	imageViewCreateInfo.subresourceRange = imageSubresourceRange;//是一个 VkImageSubresourceRange 结构，选择image view 可访问的mipmap level和array layer集合。
	/*
	VkImageViewCreateInfo有效用法：
	1.如果image不以VK_IMAGE_CREATE_CUBE_COMPATIBLE_BIT创建，则viewType 不能为VK_IMAGE_VIEW_TYPE_CUBE 或者 VK_IMAGE_VIEW_TYPE_CUBE_ARRAY
	2.如果imageCubeArray 特性没有开启，viewType 不能是VK_IMAGE_VIEW_TYPE_CUBE_ARRAY
	3.如果image以VK_IMAGE_TYPE_3D但是不以VK_IMAGE_CREATE_2D_ARRAY_COMPATIBLE_BIT 创建则viewType 不能为VK_IMAGE_VIEW_TYPE_2D_ARRAY
	4.如果image以VK_IMAGE_TYPE_3D但是不以VK_IMAGE_CREATE_2D_ARRAY_COMPATIBLE_BIT 或者VK_IMAGE_CREATE_2D_VIEW_COMPATIBLE_BIT_EXT 创建则viewType 不能为VK_IMAGE_VIEW_TYPE_2D
	5.如果image以VK_IMAGE_TYPE_3D创建且 viewType为VK_IMAGE_VIEW_TYPE_2D 或者VK_IMAGE_VIEW_TYPE_2D_ARRAY，则（1）subresourceRange.levelCount 必须为1
																									       （2）VkImageCreateInfo::flags不能包含任何VK_IMAGE_CREATE_SPARSE_BINDING_BIT, VK_IMAGE_CREATE_SPARSE_RESIDENCY_BIT, 和VK_IMAGE_CREATE_SPARSE_ALIASED_BIT中的一个
	6.如果image创建时的samples 不等于VK_SAMPLE_COUNT_1_BIT，则viewType 必须为VK_IMAGE_VIEW_TYPE_2D或 VK_IMAGE_VIEW_TYPE_2D_ARRAY
	7.image 必须以包含至少一个定义在有效对image view的image usage list中的usage 值创建
	8.最终image view的format features必须包含至少一个比特位
	9.如果image的usage包含VK_IMAGE_USAGE_SAMPLED_BIT，则最终image view的format features必须包含VK_FORMAT_FEATURE_SAMPLED_IMAGE_BIT
	10.如果image的usage包含VK_IMAGE_USAGE_STORAGE_BIT，则最终image view的format features必须包含VK_FORMAT_FEATURE_STORAGE_IMAGE_BIT
	11.如果image的usage包含VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT，则最终image view的format features必须包含VK_FORMAT_FEATURE_COLOR_ATTACHMENT_BIT 或VK_FORMAT_FEATURE_2_LINEAR_COLOR_ATTACHMENT_BIT_NV
	12.如果image的usage包含VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT，则最终image view的format features必须包含VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT
	13.如果image以VK_IMAGE_CREATE_VIDEO_PROFILE_INDEPENDENT_BIT_KHR创建则（1）如果usage包含VK_IMAGE_USAGE_VIDEO_DECODE_DST_BIT_KHR，则最终image view的format features必须包含VK_FORMAT_FEATURE_VIDEO_DECODE_OUTPUT_BIT_KHR
																		 （2）如果usage包含VK_IMAGE_USAGE_VIDEO_DECODE_DPB_BIT_KHR，则最终image view的format features必须包含VK_FORMAT_FEATURE_VIDEO_DECODE_DPB_BIT_KHR
																		 （3）image的usage不能包含VK_IMAGE_USAGE_VIDEO_DECODE_SRC_BIT_KHR 或者 VK_IMAGE_USAGE_VIDEO_ENCODE_DST_BIT_KHR
																		 （4）如果usage包含VK_IMAGE_USAGE_VIDEO_ENCODE_SRC_BIT_KHR，则最终image view的format features必须包含VK_FORMAT_FEATURE_VIDEO_ENCODE_INPUT_BIT_KHR
																		 （5）如果usage包含VK_IMAGE_USAGE_VIDEO_ENCODE_DPB_BIT_KHR，则最终image view的format features必须包含VK_FORMAT_FEATURE_VIDEO_ENCODE_DPB_BIT_KHR
	
	14.如果usage 包含VK_IMAGE_USAGE_INPUT_ATTACHMENT_BIT，且 externalFormatResolve特性没有开启，nullColorAttachmentWithExternalFormatResolve属性为VK_TRUE，或者image一个VkExternalFormatANDROID::externalFormat为0的值创建 三者只要任何一个成立，则
						image view的format features至少包含VK_FORMAT_FEATURE_COLOR_ATTACHMENT_BIT 或 VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT 或者 VK_FORMAT_FEATURE_2_LINEAR_COLOR_ATTACHMENT_BIT_NV 中的一个
	15.subresourceRange.baseMipLevel 必须小于image的VkImageCreateInfo中指定的mipLevels
	16.如果subresourceRange.levelCount 不为VK_REMAINING_MIP_LEVELS ，则subresourceRange.baseMipLevel + subresourceRange.levelCount 必须小于等于image的VkImageCreateInfo中指定的mipLevels
	17.如果image 以包含VK_IMAGE_USAGE_FRAGMENT_DENSITY_MAP_BIT_EXT的usage创建，则subresourceRange.levelCount 必须为1
	18.如果image不是一个以VK_IMAGE_CREATE_2D_ARRAY_COMPATIBLE_BIT 或VK_IMAGE_CREATE_2D_VIEW_COMPATIBLE_BIT_EXT创建的3D image，或者viewType不是VK_IMAGE_VIEW_TYPE_2D 或 VK_IMAGE_VIEW_TYPE_2D_ARRAY，则subresourceRange.baseArrayLayer 必须小于image的VkImageCreateInfo中指定的arrayLayers
	19.如果subresourceRange.layerCount 不是 VK_REMAINING_ARRAY_LAYERS，且image不是一个以VK_IMAGE_CREATE_2D_ARRAY_COMPATIBLE_BIT 或VK_IMAGE_CREATE_2D_VIEW_COMPATIBLE_BIT_EXT创建的，或者viewType不是VK_IMAGE_VIEW_TYPE_2D 或 VK_IMAGE_VIEW_TYPE_2D_ARRAY，则subresourceRange.baseArrayLayer 必须为非0值且subresourceRange.baseArrayLayer + subresourceRange.layerCount小于等于image的VkImageCreateInfo中指定的arrayLayers
	20.如果image是以VK_IMAGE_CREATE_2D_ARRAY_COMPATIBLE_BIT 创建的3D image，且viewType 为 VK_IMAGE_VIEW_TYPE_2D 或者 VK_IMAGE_VIEW_TYPE_2D_ARRAY，则subresourceRange.baseArrayLayer必须小于根据Image Mip Level Sizing 定义的规则由 VkImageCreateInfo的baseMipLevel以及 extent.depth计算出来的深度值
	21.如果subresourceRange.layerCount 不是 VK_REMAINING_ARRAY_LAYERS，且image是一个以VK_IMAGE_CREATE_2D_ARRAY_COMPATIBLE_BIT 创建的3D image，且viewType是VK_IMAGE_VIEW_TYPE_2D 或 VK_IMAGE_VIEW_TYPE_2D_ARRAY，则subresourceRange.layerCount 必须为非0值且subresourceRange.baseArrayLayer + subresourceRange.layerCount 必须小于等于根据Image Mip Level Sizing 定义的规则由 VkImageCreateInfo的baseMipLevel以及 extent.depth计算出来的深度值
	22.如果image以VK_IMAGE_CREATE_MUTABLE_FORMAT_BIT但不以VK_IMAGE_CREATE_BLOCK_TEXEL_VIEW_COMPATIBLE_BIT 标志创建，且其format是一个multi-planar format，则VkImageViewCreateInfo.format必须和创建image的format兼容，参见 Format Compatibility Classes p4067
	23.如果image以VK_IMAGE_CREATE_BLOCK_TEXEL_VIEW_COMPATIBLE_BIT 创建，则（1）当前format必须和创建image的format是兼容的，或者是大小兼容的非压缩的format。
																	   	  （2）如果format是一个非压缩format，则subresourceRange.levelCount必须为1
																	   	  （3）如果VkPhysicalDeviceMaintenance6PropertiesKHR::blockTexelViewCompatibleMultipleLayers不为VK_TRUE,且format是一个非压缩format，则subresourceRange.layerCount 必须为1

	24.如果创建image的VkImageCreateInfo.pNext中含有一个VkImageFormatListCreateInfo，且VkImageFormatListCreateInfo::viewFormatCount不为0，则format必须为VkImageFormatListCreateInfo::pViewFormats 中的一个
	25.如果image以VK_IMAGE_CREATE_MUTABLE_FORMAT_BIT创建，如果iamge的format是一个multi-planar format，且subresourceRange.aspectMask是multi-planar aspect mask中的一个，则format 必须和subresourceRange.aspectMask指明的plane的 image format兼容，参见Compatible Formats of Planes of Multi-Planar Formats p4057
	26.subresourceRange.aspectMask 必须只能含有至多一个有效的multi-planar aspect mask 比特位
	27.如果image不以VK_IMAGE_CREATE_MUTABLE_FORMAT_BIT 创建，如果如果image的 format是一个multi-planar format且 subresourceRange.aspectMask为VK_IMAGE_ASPECT_COLOR_BIT ，则format必须等于创建image的format
	28.如果image view需要一个sampler Y′CBCR conversion且image的 usage含有VK_IMAGE_USAGE_SAMPLED_BIT，则pNext中必须含有一个conversion不为VK_NULL_HANDLE 的VkSamplerYcbcrConversionInfo
	29.如果format 含有_422 或 _420 后缀，则image必须以width为2的倍数来创建
	30.如果format 含有_420 后缀，则image必须以height为2的倍数来创建
	31.如果pNext中必须含有一个conversion不为VK_NULL_HANDLE 的VkSamplerYcbcrConversionInfo，则（1）components中的所有成员必须为identity swizzle
																							 （2）则format 必须和VkSamplerYcbcrConversionCreateInfo::format相同
	32.如果image是non-sparse 则其必须绑定到一个完整连续的单个VkDeviceMemory对象上
	33.viewType 必须和image 的type兼容，见1045行中的注释
	34.如果image有一个Android external format，则（1）format必须为VK_FORMAT_UNDEFINED
												 （2）pNext中必须有一个以含有和image相同的external format创建的conversion的VkSamplerYcbcrConversionInfo
												 （3）components中的所有成员必须为identity swizzle
	35.如果image有一个QNX Screen external format，则（1）format必须为VK_FORMAT_UNDEFINED
												 （2）pNext中必须有一个以含有和image相同的external format创建的conversion的VkSamplerYcbcrConversionInfo
												 （3）components中的所有成员必须为identity swizzle
	36.如果image以usage含有VK_IMAGE_USAGE_FRAGMENT_SHADING_RATE_ATTACHMENT_BIT_KHR创建，则viewType必须为VK_IMAGE_VIEW_TYPE_2D 或者 VK_IMAGE_VIEW_TYPE_2D_ARRAY
	37.如果shadingRateImage 特性开启，且如果image以usage含有VK_IMAGE_USAGE_SHADING_RATE_IMAGE_BIT_NV创建，则format 必须为 VK_FORMAT_R8_UINTAY
	38.如果attachmentFragmentShadingRate 特性开启，且对image view如果usage含有VK_IMAGE_USAGE_FRAGMENT_SHADING_RATE_ATTACHMENT_BIT_KHR，则（1）image view的format features必须包含 VK_FORMAT_FEATURE_FRAGMENT_SHADING_RATE_ATTACHMENT_BIT_KHR
																																		 （2）如果layeredShadingRateAttachments为 VK_FALSE，则subresourceRange.layerCount 必须为1
	39.如果fragmentDensityMapDynamic 特性未开启，flags不能包含VK_IMAGE_VIEW_CREATE_FRAGMENT_DENSITY_MAP_DYNAMIC_BIT_EXT
	40.如果fragmentDensityMapDeferred 特性未开启，flags不能包含VK_IMAGE_VIEW_CREATE_FRAGMENT_DENSITY_MAP_DEFERRED_BIT_EXT
	41.如果flags包含VK_IMAGE_VIEW_CREATE_FRAGMENT_DENSITY_MAP_DEFERRED_BIT_EXT，则flags就不能包含VK_IMAGE_VIEW_CREATE_FRAGMENT_DENSITY_MAP_DYNAMIC_BIT_EXT
	42.如果image 以VK_IMAGE_CREATE_SUBSAMPLED_BIT_EXT创建且usage 包含VK_IMAGE_USAGE_SAMPLED_BIT，subresourceRange.layerCount 必须小于等于 VkPhysicalDeviceFragmentDensityMap2PropertiesEXT::maxSubsampledArrayLayers
	43.如果invocationMask 特性开启，且image以usage含VK_IMAGE_USAGE_INVOCATION_MASK_BIT_HUAWEI 创建，format 必须为VK_FORMAT_R8_UINT
	44.如果flags 不包含VK_IMAGE_VIEW_CREATE_FRAGMENT_DENSITY_MAP_DYNAMIC_BIT_EXT，且image创建是usage含有VK_IMAGE_USAGE_FRAGMENT_DENSITY_MAP_BIT_EXT，则image创建时的flags就不能含有VK_IMAGE_CREATE_PROTECTED_BIT,
						VK_IMAGE_CREATE_SPARSE_BINDING_BIT, VK_IMAGE_CREATE_SPARSE_RESIDENCY_BIT, 或者 VK_IMAGE_CREATE_SPARSE_ALIASED_BIT 中的任何一个
	45.如果pNext中包含一个VkImageViewUsageCreateInfo，但是image创建时候的VkImageCreateInfo.pNext中不包含VkImageViewUsageCreateInfo，则pNext中的VkImageViewUsageCreateInfo的usage就不能包含任何在VkImageCreateInfo.usage中没有的比特位
	46.如果pNext中包含一个VkImageViewUsageCreateInfo，但是image创建时候的VkImageCreateInfo.pNext中包含VkImageStencilUsageCreateInfo，则（1）如果 subresourceRange.aspectMask 包含VK_IMAGE_ASPECT_STENCIL_BIT， 则pNext中的VkImageViewUsageCreateInfo的usage就不能包含任何在VkImageCreateInfo.pNext中的VkImageStencilUsageCreateInfo.usage中没有的比特位
																																	   （2）如果 subresourceRange.aspectMask 不包含VK_IMAGE_ASPECT_STENCIL_BIT， 则pNext中的VkImageViewUsageCreateInfo的usage就不能包含任何在VkImageCreateInfo.ugsae中没有的比特位
	47.如果viewType为VK_IMAGE_VIEW_TYPE_1D, VK_IMAGE_VIEW_TYPE_2D, 或者 VK_IMAGE_VIEW_TYPE_3D，则（1）如果subresourceRange.layerCount不为VK_REMAINING_ARRAY_LAYERS则必须为1
																								 （2）如果subresourceRange.layerCount不为VK_REMAINING_ARRAY_LAYERS就必须为1
	48.如果viewType为VK_IMAGE_VIEW_TYPE_CUBE，则（1）如果subresourceRange.layerCount 不为VK_REMAINING_ARRAY_LAYERS就必须为6
												（2）如果subresourceRange.layerCount 为VK_REMAINING_ARRAY_LAYERS 则 remaining layers的个数就必须为6
	49.如果viewType为VK_IMAGE_VIEW_TYPE_CUBE_ARRAY，则（1）如果subresourceRange.layerCount 不为VK_REMAINING_ARRAY_LAYERS就必须为6的倍数
													  （2）如果subresourceRange.layerCount 为VK_REMAINING_ARRAY_LAYERS则 remaining layers的个数必须为6的倍数
	50.如果VK_KHR_portability_subset 拓展开启，则（1）如果VkPhysicalDevicePortabilitySubsetFeaturesKHR::imageViewFormatSwizzle 为VK_FALSE，则components中的所有成员必须为identity swizzle
												 （2）如果VkPhysicalDevicePortabilitySubsetFeaturesKHR::imageViewFormatReinterpretation 为VK_FALSE，image view的format相比image的format就不能包含不同数量的component，或者同一component含不同的比特数
	51.如果image以usage含有VK_IMAGE_USAGE_VIDEO_DECODE_DST_BIT_KHR，VK_IMAGE_USAGE_VIDEO_DECODE_SRC_BIT_KHR 或者 VK_IMAGE_USAGE_VIDEO_DECODE_DPB_BIT_KHR，
						   VK_IMAGE_USAGE_VIDEO_ENCODE_DST_BIT_KHR, VK_IMAGE_USAGE_VIDEO_ENCODE_SRC_BIT_KHR, 或者 VK_IMAGE_USAGE_VIDEO_ENCODE_DPB_BIT_KHR创建，则viewType 必须为VK_IMAGE_VIEW_TYPE_2D 或者 VK_IMAGE_VIEW_TYPE_2D_ARRAY
	52.如果flags包含VK_IMAGE_VIEW_CREATE_DESCRIPTOR_BUFFER_CAPTURE_REPLAY_BIT_EXT，descriptorBufferCaptureReplay特性必须开启
	53.如果pNext中包含一个VkOpaqueCaptureDescriptorDataCreateInfoEXT，则flags必须包含VK_IMAGE_VIEW_CREATE_DESCRIPTOR_BUFFER_CAPTURE_REPLAY_BIT_EXT
	54.如果pNext中包含一个VkExportMetalObjectCreateInfoEXT，则该结构体的exportObjectType 必须为VK_EXPORT_METAL_OBJECT_TYPE_METAL_TEXTURE_BIT_EXT
	55.如果pNext中包含一个VkImageViewSampleWeightCreateInfoQCOM，则（1）textureSampleWeighted 特性必须开启
																   （2）image必须以usage含有VK_IMAGE_USAGE_SAMPLE_WEIGHT_BIT_QCOM 创建
																   （3）components的所有成员必须为VK_COMPONENT_SWIZZLE_IDENTITY
																   （4）subresourceRange.aspectMask 必须为 VK_IMAGE_ASPECT_COLOR_BIT
																   （5）subresourceRange.levelCount 必须为 1
																   （6）viewType 必须为 VK_IMAGE_VIEW_TYPE_1D_ARRAY or VK_IMAGE_VIEW_TYPE_2D_ARRAY
																   （7）如果viewType 为 VK_IMAGE_VIEW_TYPE_1D_ARRAY,则 image 必须以 imageType 为 VK_IMAGE_TYPE_1D创建
																   （8）如果viewType 为 VK_IMAGE_VIEW_TYPE_1D_ARRAY,则 subresourceRange.layerCount 必须为2
																   （9）如果viewType 为 VK_IMAGE_VIEW_TYPE_1D_ARRAY,则 image必须以width 大于等于 （numPhases * max(align(filterSize.width,4),filterSize.height)）
																   （10）如果viewType 为 VK_IMAGE_VIEW_TYPE_2D_ARRAY,则 image 必须以 imageType 为 VK_IMAGE_TYPE_2D创建
																   （11）如果viewType 为 VK_IMAGE_VIEW_TYPE_2D_ARRAY,则 subresourceRange.layerCount 必须大于等于 numPhases
																   （12）如果viewType 为 VK_IMAGE_VIEW_TYPE_2D_ARRAY,则 image必须以width 大于等于 filterSize.width
																   （13）如果viewType 为 VK_IMAGE_VIEW_TYPE_2D_ARRAY,则 image必须以height 大于等于 filterSize.height
																   （14）则VkImageViewSampleWeightCreateInfoQCOM::filterSize.height必须小于等于VkPhysicalDeviceImageProcessingPropertiesQCOM::maxWeightFilterDimension.height
	56.subresourceRange.aspectMask 必须是对image 创建时的format有效的一个值

	*/


	// VkImageViewUsageCreateInfo
	//该结构体可以限定相对于image的usage使用在本image view上的usage
	VkImageViewUsageCreateInfo& imageViewUsageCreateInfo = imageViewCreateInfoEXT.imageViewUsageCreateInfo;
	imageViewUsageCreateInfo.usage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;//是指定image view允许使用的 VkImageUsageFlagBits组合值位掩码，不能为0


	VK_REMAINING_3D_SLICES_EXT;//VK_REMAINING_3D_SLICES_EXT是一个特殊的常量值，用于VkImageViewSlicedCreateInfoEXT的切片计数，表示指定的第一个切片偏移后图像中剩余的所有3D切片都应该包含在视图中。
	//VkImageViewSlicedCreateInfoEXT
	//该结构体用来限制image view所对应的3D slices的范围--对应到image的Z维度的范围，3D slices只有一个mipmap level且只能和 VK_DESCRIPTOR_TYPE_STORAGE_IMAGE结合使用
	VkImageViewSlicedCreateInfoEXT& imageViewSlicedCreateInfoEXT = imageViewCreateInfoEXT.imageViewSlicedCreateInfoEXT;
	imageViewSlicedCreateInfoEXT.sliceCount = 0;//是从sliceOffset开始image view可访问的3D slices数量
	imageViewSlicedCreateInfoEXT.sliceOffset = 0;//是image view可访问的第一个3D slices对image的Z-偏移量
	/*
	VkImageViewSlicedCreateInfoEXT有效用法:
	1.sliceOffset 必须小于 Image Mip Level Sizing中实际起作用的深度大小
	2.如果sliceCount 不为VK_REMAINING_3D_SLICES_EXT，则其必须为非0值 且sliceOffset + sliceCount必须小于等于 Image Mip Level Sizing中实际起作用的深度大小
	3.image 必须以imageType 为VK_IMAGE_TYPE_3D 创建
	4.viewType必须为VK_IMAGE_VIEW_TYPE_3D
	5.image view 必须只引用一个mipmap level
	6.imageSlicedViewOf3D 特性必须在device上启用


	*/


	//VkImageViewASTCDecodeModeEXT
	//这个结构体表示使用了ATSC format的image view的解码模式
	VkImageViewASTCDecodeModeEXT& imageViewASTCDecodeModeEXT = imageViewCreateInfoEXT.imageViewASTCDecodeModeEXT;
	imageViewASTCDecodeModeEXT.decodeMode = VK_FORMAT_R16G16B16A16_SFLOAT;//是用于解码ASTC压缩格式的中间格式。如果image view的format为sRGB格式，则该值无效
	/*
	VkImageViewASTCDecodeModeEXT有效用法:
	1.decodeMode 必须是VK_FORMAT_R16G16B16A16_SFLOAT, VK_FORMAT_R8G8B8A8_UNORM, 或 VK_FORMAT_E5B9G9R9_UFLOAT_PACK32中的一个
	2.如果 decodeModeSharedExponent 特性没有开启，decodeMode 就不能为VK_FORMAT_E5B9G9R9_UFLOAT_PACK32
	3.如果 decodeMode 为VK_FORMAT_R8G8B8A8_UNORM, 则image view 必须不包含任何使用ASTC HDR模式的块
	4.image view的format必须是ASTC Compressed Image Formats（p4307） 中的一个


	*/



	// VkImageViewSampleWeightCreateInfoQCOM
	//该结构体指明 weight image sampling的参数，见p1519
	VkImageViewSampleWeightCreateInfoQCOM& imageViewSampleWeightCreateInfoQCOM = imageViewCreateInfoEXT.imageViewSampleWeightCreateInfoQCOM;
	imageViewSampleWeightCreateInfoQCOM.numPhases = 1;//是 sub-pixel filter 阶段的数量
		VkExtent2D filterSize;
	imageViewSampleWeightCreateInfoQCOM.filterSize = filterSize;//是一个指定权重滤波维度的VkExtent2D。见p1521
		VkOffset2D filterCenter;
	imageViewSampleWeightCreateInfoQCOM.filterCenter = filterCenter;//是一个描述权重滤波原点位置的VkOffset2D。指定滤波核中心，见p1522
	/*
	VkImageViewSampleWeightCreateInfoQCOM有效用法:
	1.filterSize.width 必须小于或等于 VkPhysicalDeviceImageProcessingPropertiesQCOM::maxWeightFilterDimension.width
	2.filterSize.height 必须小于或等于 VkPhysicalDeviceImageProcessingPropertiesQCOM::maxWeightFilterDimension.height
	3.filterCenter.x 必须小于或等于(filterSize.width - 1)
	4.filterCenter.y 必须小于或等于(filterSize.height - 1)
	5.numPhases 必须是2的指数的平方(i.e., 1, 4, 16, 64, 256, etc.)
	6.numPhases 必须小于等于 VkPhysicalDeviceImageProcessingPropertiesQCOM::maxWeightFilterPhases

	*/

	//VkImageViewMinLodCreateInfoEXT
	//该结构体指定了image view的再 Image Level(s) Selection（p1506）, Texel Gathering（p1511） 以及 Integer Texel Coordinate Operations （p1510）中可访问的最小LOD值，见p1524
	VkImageViewMinLodCreateInfoEXT& imageViewMinLodCreateInfoEXT = imageViewCreateInfoEXT.imageViewMinLodCreateInfoEXT;
	imageViewMinLodCreateInfoEXT.minLod = 0.0f;//指定一个值限定最小的image view可访问的LOD 
	/*
	VkImageViewMinLodCreateInfoEXT有效用法：
	1.如果minLod 特性没有开启，则minLod 必须为0
	2.minLod 必须小于或等于 image view可访问的最后一个mipmap level的索引
	*/


	vkCreateImageView(device, &imageViewCreateInfo, nullptr, &imageView);


	vkDestroyImageView(device, imageView, nullptr);

	VkImageViewHandleInfoNVX imageViewHandleInfoNVX{};
	imageViewHandleInfoNVX.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_HANDLE_INFO_NVX;
	imageViewHandleInfoNVX.pNext = nullptr;
	imageViewHandleInfoNVX.descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;//指明从哪里查询句柄的描述符类型
	imageViewHandleInfoNVX.imageView = VkImageView{/*假设这是一个有效的VkImageView句柄*/ };//是要获取句柄的image view
	imageViewHandleInfoNVX.sampler = VkSampler{/*假设这是一个有效的VkSampler句柄*/ };//是当生成句柄时绑定到image view的sampler
	/*
	VkImageViewHandleInfoNVX有效用法：
	1.descriptorType 必须为VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE，VK_DESCRIPTOR_TYPE_STORAGE_IMAGE, 或者 VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER
	2.sampler 必须是有效的VkSampler句柄，如果descriptorType 为VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER
	3.如果descriptorType 为VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE 或者VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER，则image view对应的image必须以usage含有VK_IMAGE_USAGE_SAMPLED_BIT创建
	4.如果descriptorType 为VK_DESCRIPTOR_TYPE_STORAGE_IMAGE，则image view对应的image必须以usage含有VK_IMAGE_USAGE_STORAGE_BIT创建

	*/
	//获取image view的句柄
	uint32_t handle = vkGetImageViewHandleNVX(device, &imageViewHandleInfoNVX);





	VkImageViewAddressPropertiesNVX imageViewAddressPropertiesNVX{};
	imageViewAddressPropertiesNVX.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_ADDRESS_PROPERTIES_NVX;
	imageViewAddressPropertiesNVX.pNext = nullptr;
	imageViewAddressPropertiesNVX.deviceAddress;//返回image view的设备地址
	imageViewAddressPropertiesNVX.size = 0;//返回image view设备地址内存的字节大小


	//获取image view的设备地址
	vkGetImageViewAddressNVX(device, VkImageView{/*假设这是一个有效的VkImageView句柄*/ }, & imageViewAddressPropertiesNVX);
	

	// Image View Format Features 见p1111
	{
		//简单讲就是调用某些查询格式属性的函数来获取对应格式的属性
	}

}

void ResourceCreationTest::AccelerationStructureCreateTest()
{
	/*
	概述：
	加速结构是不透明的数据结构，以更有效地对提供的几何数据执行空间查询。对于这种扩展，加速度结构是包含一组底层加速度结构的顶层加速度结构，或者是包含一组自定义几何的轴对边框或一组三角形的底层加速度结构。
	顶层加速结构中的每个实例都包含对底层加速结构的引用，以及实例转换以及索引到着色器绑定所需的信息。顶层加速结构是绑定到加速描述符的结构，例如，要在光线跟踪管道中的着色器内部进行跟踪。

	*/


	VkAccelerationStructureNV accelerationStructureNV{};
	VkAccelerationStructureCreateInfoNV accelerationStructureCreateInfoNV{};
	accelerationStructureCreateInfoNV.sType = VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_CREATE_INFO_NV;
	accelerationStructureCreateInfoNV.pNext = nullptr;//可以包含一个VkOpaqueCaptureDescriptorDataCreateInfoEXT
	accelerationStructureCreateInfoNV.compactedSize = 0;//如果这个加速结构将是压缩拷贝的目标，则为vkCmdWriteAccelerationStructuresPropertiesNV返回结果的大小。如果 compactedSize 不为 0 则 info.geometryCount 和 info.instanceCount 必须为 0
	VkAccelerationStructureInfoNV accelerationStructureInfoNV{};
	{
		accelerationStructureInfoNV.sType = VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_INFO_NV;
		accelerationStructureInfoNV.pNext = nullptr;
		accelerationStructureInfoNV.flags = 0;/*是VkBuildAccelerationStructureFlagBitsNV(等同于VkBuildAccelerationStructureFlagBitsKHR)组合值的一个位掩码，指定了加速结构的附加参数。
		VkBuildAccelerationStructureFlagBitsKHR:
		VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_UPDATE_BIT_KHR:  指明这个加速结构可以在VK_BUILD_ACCELERATION_STRUCTURE_MODE_UPDATE_KHR模式下调用VkAccelerationStructureBuildGeometryInfoKHR 或者在vkCmdBuildAccelerationStructureNV 中设置为VK_TURE来进行更新 
		VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_COMPACTION_BIT_KHR:  指明这个加速可够可以在VK_COPY_ACCELERATION_STRUCTURE_MODE_COMPACT_KHR 模式下作为拷贝命令的source来产生一个compacted 加速结构
		VK_BUILD_ACCELERATION_STRUCTURE_PREFER_FAST_TRACE_BIT_KHR:  表示给定的加速结构构建应该优先考虑跟踪性能。
		VK_BUILD_ACCELERATION_STRUCTURE_PREFER_FAST_BUILD_BIT_KHR:  表示给定的加速结构构建应该优先考虑构建时间，而不是跟踪性能。 
		VK_BUILD_ACCELERATION_STRUCTURE_LOW_MEMORY_BIT_KHR: 表明这种加速结构应该最小化scratch memory和最终的加速结构，可能以牺牲构建时间或跟踪性能为代价。
		VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_OPACITY_MICROMAP_UPDATE_EXT: 表示与指定加速结构相关的opacity micromaps可能随着加速结构的更新而变化。
		VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_OPACITY_MICROMAP_DATA_UPDATE_EXT: 表示与指定加速度结构相关的opacity micromaps的数据可能随着加速度结构的更新而变化
		VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_DISABLE_OPACITY_MICROMAPS_EXT:  表示指定的加速结构可以引用具有VK_GEOMETRY_INSTANCE_DISABLE_OPACITY_MICROMAPS_EXT设置的实例
		VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_DATA_ACCESS_KHR:  表示可以使用指定的加速度结构获取命中三角形的顶点位置时。
		VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_DISPLACEMENT_MICROMAP_UPDATE_NV:  表示与指定加速度结构相关的displacement micromaps可能会随着加速度结构的更新而变化。 
		*/


		accelerationStructureInfoNV.type = VK_ACCELERATION_STRUCTURE_TYPE_TOP_LEVEL_KHR;/*是一个指定将要创建的加速度结构类型的VkAccelerationStructureTypeNV值。
		VkAccelerationStructureTypeNV:
		VK_ACCELERATION_STRUCTURE_TYPE_TOP_LEVEL_KHR: 是一个包含对bottom-level 加速结构的instance data引用的top-level 加速结构
		VK_ACCELERATION_STRUCTURE_TYPE_BOTTOM_LEVEL_KHR: 是一个包含用来求交的AABBs或者 geometry 的 bottom-level的加速结构
		VK_ACCELERATION_STRUCTURE_TYPE_GENERIC_KHR: 是一个在特殊情况下使用的且类型在构建时期确定的加速结构，在这种情况下，加速结构在创建的时候并不确定其类型，必须在构建的时候指定其是top-level的还是bottom-level的加速结构

		*/


		accelerationStructureInfoNV.geometryCount = 1;//指定新加速结构中的geometrys数量
		VkGeometryNV geometry{};
		{
			geometry.sType = VK_STRUCTURE_TYPE_GEOMETRY_NV;
			geometry.pNext = nullptr;
			geometry.flags = 0;/*包含描述geometry 选项的 VkGeometryFlagBitsKHR
			VkGeometryFlagBitsKHR
			VK_GEOMETRY_OPAQUE_BIT_KHR:  指出这个geometry 不会触发任何any-hit shaders即使它在一个hit group中
			VK_GEOMETRY_NO_DUPLICATE_ANY_HIT_INVOCATION_BIT_KHR: 指出实现必须为geometry的每个图元只调用一次 any-hit shader，如果没有该比特位，则实现可能会为每个图元调用多次 any-hit shader
			*/
			geometry.geometryType = VK_GEOMETRY_TYPE_TRIANGLES_KHR;/*一个指定geometry 类型的 VkGeometryTypeKHR，geometryType 必须为 VK_GEOMETRY_TYPE_TRIANGLES_NV 或者 VK_GEOMETRY_TYPE_AABBS_NV
			VkGeometryTypeKHR:
			VK_GEOMETRY_TYPE_TRIANGLES_KHR: 指明一个包含三角形的geometry 类型
			VK_GEOMETRY_TYPE_AABBS_KHR: 指明一个包含axis-aligned bounding boxes 的geometry 类型 
			VK_GEOMETRY_TYPE_INSTANCES_KHR: 指明一个包含加速结构的geometry 类型 
			*/
			
			VkGeometryDataNV geometryDataNV{};
			{
				VkGeometryAABBNV aabbs;//指定bottom-level加速结构的axis-aligned bounding box geometry信息,
				{
					aabbs.sType = VK_STRUCTURE_TYPE_GEOMETRY_AABB_NV;
					aabbs.pNext = nullptr;
					aabbs.stride = 0;//是aabbData中每一个AABB之间的字节大小，必须是8的倍数
					aabbs.numAABBs = 0;//是geometry中AABB的个数
					aabbs.offset = 0;//是aabbData中第一个AABB的字节偏移量,必须小于aabbData的大小且为8的倍数
					aabbs.aabbData = VkBuffer{/*假设这是一个有效的VkBuffer*/ };//是包含 axis-aligned bounding box数据 的VkBuffer
				}
				geometryDataNV.aabbs = aabbs;//如果 VkGeometryNV::geometryType 为 VK_GEOMETRY_TYPE_AABBS_NV，则这里包含axis-aligned bounding box 数据
				VkGeometryTrianglesNV triangles;//指定bottom-level加速结构的三角形geometry信息,如果indexType为VK_INDEX_TYPE_NONE_NV，则此结构描述了一组由vertexCount确定的三角形。否则，此结构描述了一组由indexCount确定的索引三角形。
				{
					triangles.sType = VK_STRUCTURE_TYPE_GEOMETRY_TRIANGLES_NV;
					triangles.pNext = nullptr;
					triangles.indexType = VK_INDEX_TYPE_UINT16;//描述每个顶点索引元素格式的 VkIndexType
					triangles.indexData = VkBuffer{/*假设这是一个有效的VkBuffer*/ };//是geometry的包含顶点索引数据的VkBuffer
					triangles.indexCount = 1;//有效的索引个数
					triangles.indexOffset = 0;//是geometry基于包含顶点索引数据的indexData的字节偏移量
					triangles.vertexFormat = VK_FORMAT_R32G32B32_SFLOAT;//描述每个顶点元素的一个 VkFormat 值
					triangles.vertexData = VkBuffer{/*假设这是一个有效的VkBuffer*/ };//是geometry的包含顶点数据的VkBuffer
					triangles.vertexCount = 1;//有效的顶点数
					triangles.vertexOffset = 0;//是geometry基于包含顶点数据的vertexData的字节偏移量
					triangles.vertexStride = 3;//每一个顶点的步长字节数
					triangles.transformOffset = 0;//基于transformData的字节偏移量
					triangles.transformData = VkBuffer{/*假设这是一个有效的VkBuffer*/ };//是一个可选的缓冲区，包含一个 VkTransformMatrixNV 结构，定义了一个应用于这个几何的转换矩阵数据
					/*
					VkGeometryTrianglesNV有效用法:
					1.vertexOffset 必须小于vertexData 的大小，且必须为vertexFormat 大小的倍数
					2.vertexFormat必须为VK_FORMAT_R32G32B32_SFLOAT, VK_FORMAT_R32G32_SFLOAT, VK_FORMAT_R16G16B16_SFLOAT, VK_FORMAT_R16G16_SFLOAT, VK_FORMAT_R16G16_SNORM, 或者 VK_FORMAT_R16G16B16_SNORM 中的一个
					3.vertexStride 必须小于等于2				
					4.indexOffset 必须小于indexData 的大小，且必须为indexType 大小的倍数
					5.indexType必须为VK_INDEX_TYPE_UINT16, VK_INDEX_TYPE_UINT32, 或者 VK_INDEX_TYPE_NONE_NV
					6.如果indexType为 VK_INDEX_TYPE_NONE_NV 则indexData 必须为VK_NULL_HANDLE
					7.如果indexType不为 VK_INDEX_TYPE_NONE_NV 则indexData 必须为一个有效的VkBuffer句柄
					8.如果indexType为 VK_INDEX_TYPE_NONE_NV 则indexCount 必须为VK_NULL_HANDLE
					9.transformOffset必须小于transformData 的大小，且必须为16的倍数

					*/
				
				}
				geometryDataNV.triangles = triangles;//如果 VkGeometryNV::geometryType 为 VK_GEOMETRY_TYPE_TRIANGLES_NV，则这里包含三角面片数据
			}
			geometry.geometry = geometryDataNV; //以 VkGeometryDataNV 描述的geometry 数据
		}
		accelerationStructureInfoNV.pGeometries = &geometry;//是一个指向 geometryCount个VkGeometryNV数组的指针，其中包含被传递到加速结构的场景数据。
		accelerationStructureInfoNV.instanceCount = 1;//指定将在新的加速结构中存在的instance数。
		/*
		VkAccelerationStructureInfoNV有效用法:
		1.geometryCount必须小于等于 VkPhysicalDeviceRayTracingPropertiesNV::maxGeometryCount
		2.instanceCount必须小于等于 VkPhysicalDeviceRayTracingPropertiesNV::maxInstanceCount
		3.所有geometries中的triangles 的总数必须小于等于VkPhysicalDeviceRayTracingPropertiesNV::maxTriangleCount
		4.如果type 为VK_ACCELERATION_STRUCTURE_TYPE_TOP_LEVEL_NV，则geometryCount 必须为0
		5.如果type 为VK_ACCELERATION_STRUCTURE_TYPE_BOTTOM_LEVEL_NV，则instanceCount 必须为0，pGeometries中的每个元素的 geometryType必须相同
		6.type不能为 VK_ACCELERATION_STRUCTURE_TYPE_GENERIC_KHR
		7.如果flags包含VK_BUILD_ACCELERATION_STRUCTURE_PREFER_FAST_TRACE_BIT_NV，则flags就不能包含VK_BUILD_ACCELERATION_STRUCTURE_PREFER_FAST_BUILD_BIT_NV
		8.scratch 必须以VK_BUFFER_USAGE_RAY_TRACING_BIT_NV 创建
		9.如果instanceData 不为VK_NULL_HANDLE，instanceData必须以VK_BUFFER_USAGE_RAY_TRACING_BIT_NV 创建

		*/
	}
	accelerationStructureCreateInfoNV.info = accelerationStructureInfoNV;//是指定所创建的加速结构的更多参数的VkAccelerationStructureInfoNV结构。


	vkCreateAccelerationStructureNV(device, &accelerationStructureCreateInfoNV, nullptr, &accelerationStructureNV);


	vkDestroyAccelerationStructureNV(device, accelerationStructureNV, nullptr);/*
	vkDestroyAccelerationStructureNV有效用法:
	1.引用到accelerationStructure的所有已经提交的命令必须完成执行
	2.如果创建accelerationStructure 提供了一个VkAllocationCallbacks，则这里也需要提供一个兼容的
	3.如果创建accelerationStructure 没有提供一个VkAllocationCallbacks，则这里设置为nullptr
	
	*/



	VkAccelerationStructureKHR accelerationStructureKHR{};
	VkAccelerationStructureCreateInfoKHR accelerationStructureCreateInfoKHR{};
	accelerationStructureCreateInfoKHR.sType = VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_CREATE_INFO_KHR;
	accelerationStructureCreateInfoKHR.pNext = nullptr;//可以包含一个 VkAccelerationStructureMotionInfoNV 或者 VkOpaqueCaptureDescriptorDataCreateInfoEXT
	accelerationStructureCreateInfoKHR.buffer = VkBuffer{/*假设这是一个有效的VkBuffer*/ };//是将存储加速度结构的buffer。其数据通过vkCmdBuildAccelerationStructuresKHR, vkBuildAccelerationStructuresKHR, vkCmdCopyAccelerationStructureKHR, 和 vkCopyAccelerationStructureKHR命令填充
	accelerationStructureCreateInfoKHR.offset = 0;//是与加速度结构将被存储的buffer的相对其基本地址的一个字节偏移量，并且必须是256的倍数。
	accelerationStructureCreateInfoKHR.size = 1;//是加速结构所需的字节大小。
	accelerationStructureCreateInfoKHR.type = VK_ACCELERATION_STRUCTURE_TYPE_BOTTOM_LEVEL_KHR;//是一个指定将要创建的加速度结构类型的VkAccelerationStructureTypeKHR值。
	accelerationStructureCreateInfoKHR.deviceAddress = 0;//是加速结构需要的device address，需要accelerationStructureCaptureReplay 特性开启，如果为0，则表示不需要特定的地址，常规使用尽量避免使用该项
	accelerationStructureCreateInfoKHR.createFlags = VK_ACCELERATION_STRUCTURE_CREATE_DEVICE_ADDRESS_CAPTURE_REPLAY_BIT_KHR;/*是VkAccelerationStructureCreateFlagBitsKHR组合值的位掩码，指定加速结构的附加创建参数。
	VkAccelerationStructureCreateFlagBitsKHR:
	VK_ACCELERATION_STRUCTURE_CREATE_DEVICE_ADDRESS_CAPTURE_REPLAY_BIT_KHR :  指明这个加速结构的地址可以在后续运行中被保存或者重用
	VK_ACCELERATION_STRUCTURE_CREATE_DESCRIPTOR_BUFFER_CAPTURE_REPLAY_BIT_EX :  指明这个加速结构可以在capturing 和 replaying时候用作 descriptor buffers，(e.g.见 trace capture and replay)，参见VkOpaqueCaptureDescriptorDataCreateInfoEXT p1392
	*/
	/*
	VkAccelerationStructureCreateInfoKHR有效用法:
	1.如果deviceAddress 不为0，则（1）createFlags 必须包含VK_ACCELERATION_STRUCTURE_CREATE_DEVICE_ADDRESS_CAPTURE_REPLAY_BIT_KHR
								 （2）deviceAddress必须从，则必须从相同创建的加速结构中获取，buffer和deviceAddress除外（这句不太明白）
								 （3）buffer必须是和用来创建加速结构的以及获取deviceAddress的 VkBuffer相同创建的，除了VkBufferOpaqueCaptureAddressCreateInfo::opaqueCaptureAddress
								 （4）buffer必须是通过vkGetBufferOpaqueCaptureAddress传入buffer后返回的 VkBufferOpaqueCaptureAddressCreateInfo::opaqueCaptureAddress创建的且该buffer是用来创建加速结构的以及获取deviceAddress的
	2.如果createFlags 包含VK_ACCELERATION_STRUCTURE_CREATE_DEVICE_ADDRESS_CAPTURE_REPLAY_BIT_KHR，VkPhysicalDeviceAccelerationStructureFeaturesKHR::accelerationStructureCaptureReplay必须为 VK_TRUE
	3.buffer 必须以usage含有VK_BUFFER_USAGE_ACCELERATION_STRUCTURE_STORAGE_BIT_KHR 创建
	4.buffer 不能以VK_BUFFER_CREATE_SPARSE_RESIDENCY_BIT 创建
	5.offset + size 必须小于等于buffer的大小
	6.offset必须为256的倍数
	7.如果createFlags 包含VK_ACCELERATION_STRUCTURE_CREATE_MOTION_BIT_NV，且type为VK_ACCELERATION_STRUCTURE_TYPE_TOP_LEVEL_KHR ，则pNext中必须包含一个有效的VkAccelerationStructureMotionInfoNV
	8.如果任何geometry 包含VkAccelerationStructureGeometryMotionTrianglesDataNV，则createFlags 必须包含VK_ACCELERATION_STRUCTURE_CREATE_MOTION_BIT_NV
	9.如果createFlags 包含VK_ACCELERATION_STRUCTURE_CREATE_DESCRIPTOR_BUFFER_CAPTURE_REPLAY_BIT_EXT，则descriptorBufferCaptureReplay 特性必须开启
	10.如果pNext中包含一个VkOpaqueCaptureDescriptorDataCreateInfoEXT，则createFlags 必须包含VK_ACCELERATION_STRUCTURE_CREATE_DESCRIPTOR_BUFFER_CAPTURE_REPLAY_BIT_EXT

	*/


	//VkAccelerationStructureMotionInfoNV
	//可包含在VkAccelerationStructureCreateInfoKHR.pNext中
	VkAccelerationStructureMotionInfoNV  accelerationStructureMotionInfoNV{};
	accelerationStructureMotionInfoNV.sType = VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_MOTION_INFO_NV;
	accelerationStructureMotionInfoNV.pNext = nullptr;
	accelerationStructureMotionInfoNV.flags = 0;//为0，保留未来使用
	accelerationStructureMotionInfoNV.maxInstances = 1;//是在运动top-level加速度结构中可能使用的最大的instance数。









	vkCreateAccelerationStructureKHR(device, &accelerationStructureCreateInfoKHR, nullptr, &accelerationStructureKHR);/*
	vkCreateAccelerationStructureKHR有效用法:
	1.VkPhysicalDeviceAccelerationStructureFeaturesKHR::accelerationStructure 特性必须启用
	2.如果VkAccelerationStructureCreateInfoKHR::deviceAddress 不为0，则accelerationStructureCaptureReplay 特性必须启用
	3.如果device 以多physical device创建，则bufferDeviceAddressMultiDevice 特性必须开启

	*/

	//详情见p1123
	VkAccelerationStructureBuildGeometryInfoKHR accelerationStructureBuildGeometryInfoKHR{};
	accelerationStructureBuildGeometryInfoKHR.sType = VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_BUILD_GEOMETRY_INFO_KHR;
	accelerationStructureBuildGeometryInfoKHR.pNext = nullptr;
	accelerationStructureBuildGeometryInfoKHR.type = VK_ACCELERATION_STRUCTURE_TYPE_BOTTOM_LEVEL_KHR;
		VkDeviceOrHostAddressKHR scratchData{};
		{
			scratchData.deviceAddress = 0;
			scratchData.hostAddress = 0;
		}
	accelerationStructureBuildGeometryInfoKHR.scratchData = scratchData;
	accelerationStructureBuildGeometryInfoKHR.srcAccelerationStructure = VkAccelerationStructureKHR{/*假设这是一个有效的VkAccelerationStructureKHR加速结构句柄*/ };
	accelerationStructureBuildGeometryInfoKHR.dstAccelerationStructure = VkAccelerationStructureKHR{/*假设这是一个有效的VkAccelerationStructureKHR加速结构句柄*/ };
	accelerationStructureBuildGeometryInfoKHR.geometryCount = 1;
		VkAccelerationStructureGeometryKHR geomerty{};
		{
			geomerty.sType = VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_KHR;
			geomerty.pNext = nullptr;
			VkAccelerationStructureGeometryDataKHR geometryData{};
			{
				VkAccelerationStructureGeometryAabbsDataKHR aabbs;
				{
				aabbs.sType = VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_AABBS_DATA_KHR;
				aabbs.pNext = nullptr;
				aabbs.stride = 0;
				aabbs.data = VkDeviceOrHostAddressConstKHR{  /*假设这是一个有效的VkDeviceOrHostAddressConstKHR句柄，其中含有有效地址*/ };
				}
			geometryData.aabbs = aabbs;
				VkAccelerationStructureGeometryInstancesDataKHR instancesData;
				{
				instancesData.sType = VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_INSTANCES_DATA_KHR;
				instancesData.pNext = nullptr;
				instancesData.arrayOfPointers = VK_FALSE;
				instancesData.data = VkDeviceOrHostAddressConstKHR{  /*假设这是一个有效的VkDeviceOrHostAddressConstKHR句柄，其中含有有效地址*/ };

				}
			geometryData.instances = instancesData;
				VkAccelerationStructureGeometryTrianglesDataKHR trianglesData;
				{
				trianglesData.sType = VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_TRIANGLES_DATA_KHR;
				trianglesData.pNext = nullptr;
				trianglesData.indexType = VK_INDEX_TYPE_UINT8_EXT;
				trianglesData.indexData = VkDeviceOrHostAddressConstKHR{  /*假设这是一个有效的VkDeviceOrHostAddressConstKHR句柄，其中含有有效地址*/ };
				trianglesData.maxVertex = 1;
				trianglesData.vertexFormat = VK_FORMAT_R32G32B32_SFLOAT;
				trianglesData.vertexStride = 3;
				trianglesData.vertexData = VkDeviceOrHostAddressConstKHR{  /*假设这是一个有效的VkDeviceOrHostAddressConstKHR句柄，其中含有有效地址*/ };
				trianglesData.transformData = VkDeviceOrHostAddressConstKHR{  /*假设这是一个有效的VkDeviceOrHostAddressConstKHR句柄，其中含有有效地址*/ };
				}
			geometryData.triangles = trianglesData;
		}
			geomerty.geometry = geometryData;
			geomerty.geometryType = VK_GEOMETRY_TYPE_INSTANCES_KHR;
			geomerty.flags = 0;
		
		}
	accelerationStructureBuildGeometryInfoKHR.pGeometries = &geomerty;
	accelerationStructureBuildGeometryInfoKHR.ppGeometries = &accelerationStructureBuildGeometryInfoKHR.pGeometries;
	accelerationStructureBuildGeometryInfoKHR.mode = VK_BUILD_ACCELERATION_STRUCTURE_MODE_BUILD_KHR;
	accelerationStructureBuildGeometryInfoKHR.flags = 0;
	
	VkAccelerationStructureBuildSizesInfoKHR buildSizeInfoKHR{};
	buildSizeInfoKHR.sType = VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_BUILD_SIZES_INFO_KHR;
	buildSizeInfoKHR.pNext = nullptr;
	buildSizeInfoKHR.updateScratchSize = 0;//是更新操作中scratch buffer所需要的字节数大小
	buildSizeInfoKHR.buildScratchSize = 0;//是构建操作中scratch buffer所需要的字节数大小
	buildSizeInfoKHR.accelerationStructureSize = 0;//是VkAccelerationStructureKHR加速结构中构建或更新操作所需的字节大小。
	uint32_t buildSizeInfoCount = 1;
	//获取加速结构的构建大小
	//
	vkGetAccelerationStructureBuildSizesKHR(device, VkAccelerationStructureBuildTypeKHR::VK_ACCELERATION_STRUCTURE_BUILD_TYPE_DEVICE_KHR,
		&accelerationStructureBuildGeometryInfoKHR, &buildSizeInfoCount, &buildSizeInfoKHR);/*
	vkGetAccelerationStructureBuildSizesKHR有效用法:
	1. VkPhysicalDeviceAccelerationStructureFeaturesKHR::accelerationStructure特性必须开启
	2. 如果pBuildInfo->geometryCount 不为0，则pMaxPrimitiveCounts 必须是一个有效的pBuildInfo->geometryCount个uint32_t 值的首地址指针
	3. 如果	pBuildInfo->pGeometries 或者 pBuildInfo->ppGeometries 由元素的geometryType 为VK_GEOMETRY_TYPE_INSTANCES_KHR，则每个pMaxPrimitiveCounts[i] 必须小于等于 VkPhysicalDeviceAccelerationStructurePropertiesKHR::maxInstanceCount

	---------------------------------------------------
	VkAccelerationStructureBuildTypeKHR:
	VK_ACCELERATION_STRUCTURE_BUILD_TYPE_HOST_KHR: 请求主机执行的操作的内存需求。
	VK_ACCELERATION_STRUCTURE_BUILD_TYPE_DEVICE_KHR: 请求该设备执行的操作的内存需求。
	VK_ACCELERATION_STRUCTURE_BUILD_TYPE_HOST_OR_DEVICE_KHR: 请求主机或设备执行的操作的内存需求

	*/



	//销毁
	vkDestroyAccelerationStructureKHR(device, accelerationStructureKHR, nullptr);/*
	vkDestroyAccelerationStructureKHR有效用法:
	1.VkPhysicalDeviceAccelerationStructureFeaturesKHR::accelerationStructure 特性必须开启
	2.引用到accelerationStructure的所有已经提交的命令必须完成执行
	3.如果创建accelerationStructure 提供了一个VkAllocationCallbacks，则这里也需要提供一个兼容的
	4.如果创建accelerationStructure 没有提供一个VkAllocationCallbacks，则这里设置为nullptr
	*/




	VkAccelerationStructureMemoryRequirementsInfoNV accelerationStructureMemoryRequirementsInfoNV{};
	accelerationStructureMemoryRequirementsInfoNV.sType = VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_MEMORY_REQUIREMENTS_INFO_NV;
	accelerationStructureMemoryRequirementsInfoNV.pNext = nullptr;
	accelerationStructureMemoryRequirementsInfoNV.type = VK_ACCELERATION_STRUCTURE_MEMORY_REQUIREMENTS_TYPE_BUILD_SCRATCH_NV;//选择要查询的内存需求的类型。VK_ACCELERATION_STRUCTURE_MEMORY_REQUIREMENTS_TYPE_OBJECT_NV返回对象本身的内存需求。VK_ACCELERATION_STRUCTURE_MEMORY_REQUIREMENTS_TYPE_BUILD_SCRATCH_NV在执行构建时返回scratch memory的内存需求。VK_ACCELERATION_STRUCTURE_MEMORY_REQUIREMENTS_TYPE_UPDATE_SCRATCH_NV在执行更新时返回scratch memory的内存要求。
	/*
	VkAccelerationStructureMemoryRequirementsTypeNV:
	VK_ACCELERATION_STRUCTURE_MEMORY_REQUIREMENTS_TYPE_OBJECT_NV: 查询VkAccelerationStructureNV 备份存储的内存需求
	VK_ACCELERATION_STRUCTURE_MEMORY_REQUIREMENTS_TYPE_BUILD_SCRATCH_NV:  查询在最初构建时scratch space 的内存需求
	VK_ACCELERATION_STRUCTURE_MEMORY_REQUIREMENTS_TYPE_UPDATE_SCRATCH_NV:  查询更新时scratch space 的内存需求
	*/
	accelerationStructureMemoryRequirementsInfoNV.accelerationStructure = VkAccelerationStructureNV{/*假设这是一个有效的VkAccelerationStructureNV句柄*/};//指明要查询内存属性的加速架构
	
	VkMemoryRequirements2KHR memoryRequirements2KHR{};
	memoryRequirements2KHR.sType = VK_STRUCTURE_TYPE_MEMORY_REQUIREMENTS_2_KHR;
	memoryRequirements2KHR.pNext = nullptr;
	memoryRequirements2KHR.memoryRequirements;//
	//加速结构具有结构对象本身的内存需求，构建scratch space和更新scratch space
	//查询内存属性
	vkGetAccelerationStructureMemoryRequirementsNV(device, &accelerationStructureMemoryRequirementsInfoNV, &memoryRequirements2KHR);





	VkBindAccelerationStructureMemoryInfoNV bindAccelerationStructureMemoryInfoNV{};
	bindAccelerationStructureMemoryInfoNV.sType = VK_STRUCTURE_TYPE_BIND_ACCELERATION_STRUCTURE_MEMORY_INFO_NV;
	bindAccelerationStructureMemoryInfoNV.pNext = nullptr;
	bindAccelerationStructureMemoryInfoNV.memory = VkDeviceMemory{/*假设这是一个有效的VkDeviceMemory*/ };//是一个 VkDeviceMemory指明要绑定到的memory
	bindAccelerationStructureMemoryInfoNV.memoryOffset = 0;//是要绑定到加速结构的memory区域的起始偏移量。从内存偏移字节开始的内存中的返回到VkMemoryRequirements：：size的字节数，将被绑定到指定的加速结构。
	bindAccelerationStructureMemoryInfoNV.deviceIndexCount = 0;//pDeviceIndices的元素个数
	bindAccelerationStructureMemoryInfoNV.pDeviceIndices = VK_NULL_HANDLE;//是device索引值的数组首地址
	bindAccelerationStructureMemoryInfoNV.accelerationStructure = VkAccelerationStructureNV{/*假设这是一个有效的VkAccelerationStructureNV句柄*/};//指明要绑定到memory上的加速结构
	/*
	1.accelerationStructure 不能已经被一个memory 对象备份了
	2.memoryOffset 必须小于memory的大小
	3.memory 必须已经使用调用vkGetAccelerationStructureMemoryRequirementsNV传入accelerationStructure 以及type为VK_ACCELERATION_STRUCTURE_MEMORY_REQUIREMENTS_TYPE_OBJECT_NV 返回的结构中的VkMemoryRequirements的memoryTypeBits 允许的类型创建
	4.memoryOffset 必须是调用vkGetAccelerationStructureMemoryRequirementsNV传入accelerationStructure 以及type为VK_ACCELERATION_STRUCTURE_MEMORY_REQUIREMENTS_TYPE_OBJECT_NV 返回的结构中的VkMemoryRequirements的alignment 的整数倍
	5.调用vkGetAccelerationStructureMemoryRequirementsNV传入accelerationStructure 以及type为VK_ACCELERATION_STRUCTURE_MEMORY_REQUIREMENTS_TYPE_OBJECT_NV 返回的结构中size 必须小于等于memory的大小减去memoryOffset

	
	*/
	
	
	//将一个memory绑定到一个或多个加速结构上
	vkBindAccelerationStructureMemoryNV(device, 1, &bindAccelerationStructureMemoryInfoNV);







	//如果需要，为了允许使用设备代码构造几何实例，我们需要能够查询加速结构的不透明句柄。这个句柄的值为8个字节
	//
	uint64_t handle;
	vkGetAccelerationStructureHandleNV(device, VkAccelerationStructureNV{/*假设这是一个有效的VkAccelerationStructureNV句柄*/ }, sizeof(uint64_t), & handle);/*
	vkGetAccelerationStructureHandleNV有效用法:
	1.dataSize 必须足够大以容纳8个字节的结果
	2.accelerationStructure 必须已经通过vkBindAccelerationStructureMemoryNV 绑定到一个完整的连续的单个VkDeviceMemory 对象上

	*/

	VkAccelerationStructureDeviceAddressInfoKHR accelerationStructureDeviceAddressInfoKHR{};
	accelerationStructureDeviceAddressInfoKHR.sType = VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_DEVICE_ADDRESS_INFO_KHR;
	accelerationStructureDeviceAddressInfoKHR.pNext = nullptr;
	accelerationStructureDeviceAddressInfoKHR.accelerationStructure = VkAccelerationStructureKHR{/*假设这是一个有效的VkAccelerationStructureKHR句柄*/ };//指明要查询设备地址的加速结构



	//查询加速结构的64位设备地址
	vkGetAccelerationStructureDeviceAddressKHR(device, &accelerationStructureDeviceAddressInfoKHR);/*
	vkGetAccelerationStructureDeviceAddressKHR有效用法:
	1.VkPhysicalDeviceAccelerationStructureFeaturesKHR::accelerationStructure 特性必须开启
	2.如果device 以多physical device创建，则bufferDeviceAddressMultiDevice 特性必须开启
	3.如果 pInfo->accelerationStructure 加速结构所在的buffer是non-sparse的则该buffer必须被完全和连续的绑定到一个VkDeviceMemory对象上
	4.pInfo->accelerationStructure 加速结构所在的buffer 必须以VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT 标志创建

	*/

}

void ResourceCreationTest::MicroMapsCreateTest()
{
	//Micromaps是一种不透明的数据结构，由实现构建，以编码包含在加速结构中的sub-triangle数据。
	VkMicromapEXT micromapEXT{};
	VkMicromapCreateInfoEXT micromapCreateInfoEXT{  };
	micromapCreateInfoEXT.sType = VK_STRUCTURE_TYPE_MICROMAP_CREATE_INFO_EXT;
	micromapCreateInfoEXT.pNext = nullptr;
	micromapCreateInfoEXT.type = VK_MICROMAP_TYPE_OPACITY_MICROMAP_EXT;/*是一个VkMicromapTypeEXT值，指定将创建的micromap的类型。
	VkMicromapTypeEXT:
	VK_MICROMAP_TYPE_OPACITY_MICROMAP_EXT: 是一个包含控制三角形不透明度信息的micromap 
	VK_MICROMAP_TYPE_DISPLACEMENT_MICROMAP_NV:  是一个包含控制三角形中的子三角形的位移信息
	*/
	micromapCreateInfoEXT.buffer = VkBuffer{/*假设这是一个有效的VkBuffer*/ };//是存储micromap的数据的VkBuffer，通过 vkCmdBuildMicromapsEXT, vkBuildMicromapsEXT, vkCmdCopyMicromapEXT,和vkCopyMicromapEXT 生成
	micromapCreateInfoEXT.offset = 0;//是micromap开始存储数据地址基于buffer基地址的字节偏移量，必须是256的倍数
	micromapCreateInfoEXT.size = 0;//是micromap需要的内存大小
	micromapCreateInfoEXT.deviceAddress = 0;//如果 micromapCaptureReplay 特性开启则为micromap需要的设备地址
	micromapCreateInfoEXT.createFlags = VK_MICROMAP_CREATE_DEVICE_ADDRESS_CAPTURE_REPLAY_BIT_EXT;//是VkMicromapCreateFlagBitsEXT组合值的一个位掩码，指定了micromap的额外创建参数。VK_MICROMAP_CREATE_DEVICE_ADDRESS_CAPTURE_REPLAY_BIT_EXT 指明micromap的地址可以在后续运行中捕获或重用
	/*
	VkMicromapCreateInfoEXT有效用法:
	1.如果deviceAddress 不为0，则createFlags 必须包含VK_MICROMAP_CREATE_DEVICE_ADDRESS_CAPTURE_REPLAY_BIT_EXT
	2.如果createFlags 包含VK_MICROMAP_CREATE_DEVICE_ADDRESS_CAPTURE_REPLAY_BIT_EXT,则 kPhysicalDeviceOpacityMicromapFeaturesEXT::micromapCaptureReplay 必须为VK_TRUE
	3.buffer必须以usage含有VK_BUFFER_USAGE_MICROMAP_STORAGE_BIT_EXT 创建
	4.buffer 不能以VK_BUFFER_CREATE_SPARSE_RESIDENCY_BIT 创建
	5.offset + size必须小于buffer的大小
	6.offset必须是256的倍数
	
	*/




	vkCreateMicromapEXT(device, &micromapCreateInfoEXT, nullptr, &micromapEXT);/*
	vkCreateMicromapEXT有效用法:
	1.micromap 特性必须开启
	2.如果VkMicromapCreateInfoEXT::deviceAddress 不为0，则micromapCaptureReplay 必须开启
	3.如果device以多physical device创建，则bufferDeviceAddressMultiDevice 特性必须开启
	
	*/


	VkMicromapBuildInfoEXT micromapBuildInfoEXT{};
	micromapBuildInfoEXT.sType = VK_STRUCTURE_TYPE_MICROMAP_BUILD_INFO_EXT;
	micromapBuildInfoEXT.pNext = nullptr;
	micromapBuildInfoEXT.flags = VK_BUILD_MICROMAP_PREFER_FAST_BUILD_BIT_EXT;/*
	VkBuildMicromapFlagBitsEXT:
	VK_BUILD_MICROMAP_PREFER_FAST_TRACE_BIT_EXT:  指明给定的micromap的构建相比构建时间优先考虑性能
	VK_BUILD_MICROMAP_PREFER_FAST_BUILD_BIT_EXT:  指明给定的micromap的构建相比性能优先考虑构建时间
	*/
	micromapBuildInfoEXT.mode = VK_BUILD_MICROMAP_MODE_BUILD_EXT;
	micromapBuildInfoEXT.dstMicromap = VkMicromapEXT{/*假设这是一个有效的VkMicromapEXT句柄*/ };
	micromapBuildInfoEXT.scratchData = VkDeviceOrHostAddressKHR{/*假设这是一个有效的VkDeviceOrHostAddressConstKHR句柄*/ };
	micromapBuildInfoEXT.type = VK_MICROMAP_TYPE_OPACITY_MICROMAP_EXT;
	micromapBuildInfoEXT.usageCountsCount = 1;
	VkMicromapUsageEXT usage{};
	usage.count = 0;
	usage.format = 0;
	usage.subdivisionLevel = 0;
	micromapBuildInfoEXT.pUsageCounts = &usage;
	micromapBuildInfoEXT.ppUsageCounts = &micromapBuildInfoEXT.pUsageCounts;
	micromapBuildInfoEXT.triangleArrayStride = 0;
	micromapBuildInfoEXT.triangleArray = VkDeviceOrHostAddressConstKHR{/*假设这是一个有效的VkDeviceOrHostAddressConstKHR句柄*/ };


	VkMicromapBuildSizesInfoEXT micromapBuildSizesInfoEXT{};
	micromapBuildSizesInfoEXT.sType = VK_STRUCTURE_TYPE_MICROMAP_BUILD_SIZES_INFO_EXT;
	micromapBuildSizesInfoEXT.pNext = nullptr;
	micromapBuildSizesInfoEXT.micromapSize = 0;//返回micromap构建或更新需要的字节大小
	micromapBuildSizesInfoEXT.buildScratchSize = 0;//返回构建过程中scratch buffer需要的字节大小
	micromapBuildSizesInfoEXT.discardable = VK_FALSE;//指示在加速结构构建或更新后是否可以销毁micromap对象。VK_FALSE意味着用该micromap构建的加速度结构可能包含对其中包含的数据的引用，并且在射线遍历结束之前，应用程序不能破坏该micromap。VK_TRUE表示micromap中的信息将被值复制到加速度结构中，在加速度结构构建结束后，micromap可能会被销毁。

	//获取micromap的构建大小
	vkGetMicromapBuildSizesEXT(device, VK_ACCELERATION_STRUCTURE_BUILD_TYPE_DEVICE_KHR, &micromapBuildInfoEXT, &micromapBuildSizesInfoEXT);/*
	vkGetMicromapBuildSizesEXT有效用法:
	1.pBuildInfo的dstMicromap 以及 mode 是被忽略的. pBuildInfo的所有VkDeviceOrHostAddressKHR 成员是被忽略的。
	2.VkMicromapBuildInfoEXT::dstMicromap 必须从device上创建
	3.micromap 特性必须开启
	4.如果device以多physical device创建，则bufferDeviceAddressMultiDevice 特性必须开启

	*/


	vkDestroyMicromapEXT(device, micromapEXT, nullptr);


}

void ResourceCreationTest::ResourceMemoryAssociationTest()
{
	/*
	概述
	资源最初是作为虚拟分配创建的，没有实际内存。设备内存被单独分配（请参见Device Memory p887），然后与资源关联。对于稀疏资源，这种关联对于非稀疏资源的做法不同。
	使用任何稀疏创建标志创建的资源都被认为是稀疏资源。没有这些标志创建的资源是非稀疏的。在Sparse Resources (p2981)中描述了关于稀疏资源的资源内存关联的详细信息。
	
	*/

	//查询资源的内存需求,返回的内存需求中的参数的更细致的描述见p1156
	{

		VkMemoryRequirements bufferMemoryRequirements{};
		bufferMemoryRequirements.size = 0;//为当前资源分配所需要的字节大小
		bufferMemoryRequirements.memoryTypeBits = 0;//是一个位掩码，对资源的每个支持的内存类型都包含一个比特位。当且仅当物理设备的VkPhysicalDeviceMemoryProperties结构中的内存类型i支持该资源时，才设置位i。
		bufferMemoryRequirements.alignment = 0;//是资源分配所需的offset的字节对齐数
		//查询buffer资源的内存需求
		vkGetBufferMemoryRequirements(device, VkBuffer{/*假设这是一个有效的VkBuffer*/ }, &bufferMemoryRequirements);


		VkMemoryRequirements imageMemoryRequirements{};
		imageMemoryRequirements.size = 0;//为当前资源分配所需要的字节大小
		imageMemoryRequirements.memoryTypeBits = 0;//是一个位掩码，对资源的每个支持的内存类型都包含一个比特位。当且仅当物理设备的VkPhysicalDeviceMemoryProperties结构中的内存类型i支持该资源时，才设置位i。
		imageMemoryRequirements.alignment = 0;//是资源分配所需的offset的字节对齐数
		//查询不以VK_IMAGE_CREATE_DISJOINT_BIT创建的image资源的内存需求
		vkGetImageMemoryRequirements(device, VkImage{/*假设这是一个有效的VkBuffer*/ }, &imageMemoryRequirements);/*
		1.image不能以VK_IMAGE_CREATE_DISJOINT_BIT 创建
		2.如果image以VK_EXTERNAL_MEMORY_HANDLE_TYPE_ANDROID_HARDWARE_BUFFER_BIT_ANDROID external memory handle type创建，且image必须绑定到memory
		3.如果image以VK_EXTERNAL_MEMORY_HANDLE_TYPE_SCREEN_BUFFER_BIT_QNX external memory handle type创建，且image必须绑定到memory
		*/




		VkBufferMemoryRequirementsInfo2 bufferMemoryRequirementsInfo2{};
		bufferMemoryRequirementsInfo2.sType = VK_STRUCTURE_TYPE_BUFFER_MEMORY_REQUIREMENTS_INFO_2;
		bufferMemoryRequirementsInfo2.pNext = nullptr;
		bufferMemoryRequirementsInfo2.buffer = VkBuffer{/*假设这是一个有效的VkBuffer*/ };//指要查询的buffer

		VkMemoryRequirements2 bufferMemoryRequirements2{};
		bufferMemoryRequirements2.sType = VK_STRUCTURE_TYPE_MEMORY_REQUIREMENTS_2;
		VkMemoryDedicatedRequirements bufferMemoryDedicatedRequirements{};//等价于VkMemoryDedicatedRequirementsKHR
		{
			//返回的参数的更多信息见p1168
			bufferMemoryDedicatedRequirements.sType = VK_STRUCTURE_TYPE_MEMORY_DEDICATED_REQUIREMENTS;
			bufferMemoryDedicatedRequirements.pNext = nullptr;
			bufferMemoryDedicatedRequirements.prefersDedicatedAllocation = VK_FALSE;//指定实现更希望对此资源进行专用分配。应用程序仍然可以自由进行次分配资源，但是如果使用专用分配，它可以获得更好的性能。
			bufferMemoryDedicatedRequirements.requiresDedicatedAllocation = VK_FALSE;//指定此资源需要进行专用分配。
		}
		bufferMemoryRequirements2.pNext = &bufferMemoryDedicatedRequirements;//可以添加一个VkMemoryDedicatedRequirements
		bufferMemoryRequirements2.memoryRequirements = bufferMemoryRequirements;//是一个描述资源的内存需求的VkMemoryRequirements。
		//查询buffer资源的内存需求，等同于vkGetBufferMemoryRequirements2KHR
		vkGetBufferMemoryRequirements2(device, &bufferMemoryRequirementsInfo2, &bufferMemoryRequirements2);



		VkDeviceBufferMemoryRequirements deviceBufferMemoryRequirements{};
		deviceBufferMemoryRequirements.sType = VK_STRUCTURE_TYPE_DEVICE_BUFFER_MEMORY_REQUIREMENTS;
		deviceBufferMemoryRequirements.pNext = nullptr;
			VkBufferCreateInfo bufferCreateInfo{}; {/*假设这是一个有效的VkBufferCreateInfo*/ }
		deviceBufferMemoryRequirements.pCreateInfo = &bufferCreateInfo; //是一个指向VkBufferCreateInfo结构的指针，其中包含影响要查询的buffer创建的参数
		//查询buffer资源的内存需求而不需要先有一个buffer对象,等同于vkGetDeviceBufferMemoryRequirementsKHR
		vkGetDeviceBufferMemoryRequirements(device, &deviceBufferMemoryRequirements, &bufferMemoryRequirements2);



		VkImageMemoryRequirementsInfo2 imageMemoryRequirementsInfo2{};//等价于VkImageMemoryRequirementsInfo2KHR
		imageMemoryRequirementsInfo2.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_REQUIREMENTS_INFO_2;
		VkImagePlaneMemoryRequirementsInfo imagePlaneMemoryRequirementsInfo{}; //等同于VkImagePlaneMemoryRequirementsInfoKHR
		{
			imagePlaneMemoryRequirementsInfo.sType = VK_STRUCTURE_TYPE_IMAGE_PLANE_MEMORY_REQUIREMENTS_INFO;
			imagePlaneMemoryRequirementsInfo.pNext = nullptr;
			imagePlaneMemoryRequirementsInfo.planeAspect = VK_IMAGE_ASPECT_COLOR_BIT;//是一个VkImageAspectFlagBits值，指定与要查询的image plane aspect
			/*
			VkImagePlaneMemoryRequirementsInfo有效用法:
			1.如果image的tiling 为VK_IMAGE_TILING_LINEAR 或者 VK_IMAGE_TILING_OPTIMAL，则planeAspect 必须是一个单独有效的multi-planar aspect mask比特位
			2.如果image的tiling 为VK_IMAGE_TILING_DRM_FORMAT_MODIFIER_EXT，则planeAspect 必须是一个单独的有效的image memory plane(即 aspectMask必须指明一个其索引小于和 image的format以及VkImageDrmFormatModifierPropertiesEXT::drmFormatModifier关联的 VkDrmFormatModifierPropertiesEXT::drmFormatModifierPlaneCount 的plane )

			*/
		}
		imageMemoryRequirementsInfo2.pNext = &imagePlaneMemoryRequirementsInfo;//可以包含一个 VkImagePlaneMemoryRequirementsInfo
		imageMemoryRequirementsInfo2.image = VkImage{/*假设这是一个有效的VkImage*/ };//指明要查询的image
		/*
		VkImageMemoryRequirementsInfo2有效用法：
		1.如果image以一个multi-planar format 和VK_IMAGE_CREATE_DISJOINT_BIT创建，则VkImageMemoryRequirementsInfo2的pNext中必须包含一个VkImagePlaneMemoryRequirementsInfo
		2.如果image以VK_IMAGE_CREATE_DISJOINT_BIT 和VK_IMAGE_TILING_DRM_FORMAT_MODIFIER_EXT创建，则VkImageMemoryRequirementsInfo2的pNext中必须包含一个VkImagePlaneMemoryRequirementsInfo
		3.如果image不以VK_IMAGE_CREATE_DISJOINT_BIT 创建，则VkImageMemoryRequirementsInfo2的pNext中不能包含一个VkImagePlaneMemoryRequirementsInfo
		4.如果image以一个single-plane format 且不包含VK_IMAGE_TILING_DRM_FORMAT_MODIFIER_EXT 创建，则VkImageMemoryRequirementsInfo2的pNext中不能包含一个VkImagePlaneMemoryRequirementsInfo
		5.如果image 以VK_EXTERNAL_MEMORY_HANDLE_TYPE_ANDROID_HARDWARE_BUFFER_BIT_ANDROID  external memory handle type创建，则image必须绑定到memory
		6.如果image 以VK_EXTERNAL_MEMORY_HANDLE_TYPE_SCREEN_BUFFER_BIT_QNX  external memory handle type创建，则image必须绑定到memory

		*/

		VkMemoryRequirements2 imageMemoryRequirements2{};
		imageMemoryRequirements2.sType = VK_STRUCTURE_TYPE_MEMORY_REQUIREMENTS_2;
		VkMemoryDedicatedRequirements imageMemoryDedicatedRequirements{};//等价于VkMemoryDedicatedRequirementsKHR
		{
			//返回的参数的更多信息见p1168
			imageMemoryDedicatedRequirements.sType = VK_STRUCTURE_TYPE_MEMORY_DEDICATED_REQUIREMENTS;
			imageMemoryDedicatedRequirements.pNext = nullptr;
			imageMemoryDedicatedRequirements.prefersDedicatedAllocation = VK_FALSE;//指定实现更希望对此资源进行专用分配。应用程序仍然可以自由进行次分配资源，但是如果使用专用分配，它可以获得更好的性能。
			imageMemoryDedicatedRequirements.requiresDedicatedAllocation = VK_FALSE;//指定此资源需要进行专用分配。
		}
		imageMemoryRequirements2.pNext = &imageMemoryDedicatedRequirements;//可以包含一个VkMemoryDedicatedRequirements
		imageMemoryRequirements2.memoryRequirements = imageMemoryRequirements;//是一个描述资源的内存需求的VkMemoryRequirements。

		//查询不以image资源的内存需求，等同于vkGetImageMemoryRequirements2KHR
		vkGetImageMemoryRequirements2(device, &imageMemoryRequirementsInfo2, &imageMemoryRequirements2);



		VkDeviceImageMemoryRequirements deviceImageMemoryRequirements{};
		deviceImageMemoryRequirements.sType = VK_STRUCTURE_TYPE_DEVICE_IMAGE_MEMORY_REQUIREMENTS;
		deviceImageMemoryRequirements.pNext = nullptr;
		deviceImageMemoryRequirements.planeAspect = VK_IMAGE_ASPECT_COLOR_BIT;// 是一个VkImageAspectFlagBits值，指定与要查询的image plane aspect。此参数将会被忽略，除非pCreateInfo->tiling是VK_IMAGE_TILING_DRM_FORMAT_MODIFIER_EXT，或pCreateInfo->flags已经设置了VK_IMAGE_CREATE_DISJOINT_BIT。
			VkImageCreateInfo imageCreateInfo{};//假设这是一个有效的VkImageCreateInfo
		deviceImageMemoryRequirements.pCreateInfo = &imageCreateInfo;//是一个指向VkImageCreateInfo结构的指针，其中包含影响要查询的image创建的参数
		/*
		VkDeviceImageMemoryRequirements有效用法:
		1.pCreateInfo->pNext 不能包含一个VkImageSwapchainCreateInfoKHR或者VkImageDrmFormatModifierExplicitCreateInfoEXT
		2.vkGetDeviceImageMemoryRequirements调用时，VkDeviceImageMemoryRequirements.pCreateInfo->pNext不能含有一个externalFormat 为非0值的VkExternalFormatANDROID 或者VkExternalFormatQNX
		3.如果pCreateInfo->format 指定一个multi-planar format 且pCreateInfo->flags含有VK_IMAGE_CREATE_DISJOINT_BIT，则planeAspect 不能为VK_IMAGE_ASPECT_NONE_KHR
		4.如果pCreateInfo->flags 有VK_IMAGE_CREATE_DISJOINT_BIT且如果pCreateInfo->tiling为VK_IMAGE_TILING_LINEAR 或者 VK_IMAGE_TILING_OPTIMAL，则planeAspect 必须是一个单独的有效的multi-planar aspect mask 比特位
		5.如果pCreateInfo->tiling 为VK_IMAGE_TILING_DRM_FORMAT_MODIFIER_EXT，则planeAspect 必须是一个单独的有效的image memory plane(即 aspectMask必须指明一个其索引小于和 image的format以及VkImageDrmFormatModifierPropertiesEXT::drmFormatModifier关联的 VkDrmFormatModifierPropertiesEXT::drmFormatModifierPlaneCount 的plane )

		*/


		//查询image资源的内存需求而不需要先有一个image对象,等同于vkGetDeviceImageMemoryRequirementsKHR
		vkGetDeviceImageMemoryRequirements(device, &deviceImageMemoryRequirements, &imageMemoryRequirements2);

	}


	//绑定memory到VkBuffer
	{
		vkBindBufferMemory(device, VkBuffer{/*假设这是一个有效的VkBuffer*/ }, VkDeviceMemory{/*假设这是一个有效的VkDeviceMemory*/ },0);
		/*
		vkBindBufferMemory参数:
		buffer:要附加到memory的VkBuffer
		memory:buffer需要附加到的VkDeviceMemory
		memoryOffset:指明从memory开始的字节偏移量开始的区域将绑定到buffer---从memory的memoryOffset开始 查询获取的VkMemoryRequirements::size大小的内存将绑定到buffer
		
		-------------------------------------
		vkBindBufferMemory有效用法:
		1.buffer 不能已经绑定到memory了
		2.buffer 不能以任何sparse memory binding标志创建
		3.memoryOffset 必须小于memory的大小
		4.memory 必须使用调用vkGetBufferMemoryRequirements传入buffer返回的VkMemoryRequirements.memoryTypeBits允许的一种内存类型创建
		5.memoryOffset必须是调用vkGetBufferMemoryRequirements传入buffer返回的VkMemoryRequirements.alignment的整数倍
		6.调用vkGetBufferMemoryRequirements传入buffer返回的VkMemoryRequirements.size必须小于等于 memory的大小减去memoryOffset
		7.如果buffer需要dedicated allocation（参见传入buffer调用vkGetBufferMemoryRequirements2返回的VkMemoryDedicatedRequirements::requiresDedicatedAllocation），则memory必须以其VkMemoryDedicatedAllocateInfo::buffer等于buffer创建
		8.如果memory创建时候的VkMemoryAllocateInfo.pNext中含有一个buffer不为VK_NULL_HANDLE的VkMemoryDedicatedAllocateInfo，则VkMemoryDedicatedAllocateInfo::buffer必须等于buffer，memoryOffset必须为0
		9.如果buffer 以VK_BUFFER_CREATE_PROTECTED_BIT创建，则buffer就必须绑定到其分配时memory type含有VK_MEMORY_PROPERTY_PROTECTED_BIT的memory对象
		10.如果buffer 不以VK_BUFFER_CREATE_PROTECTED_BIT创建，则buffer就不能绑定到其分配时memory type含有VK_MEMORY_PROPERTY_PROTECTED_BIT的memory对象
		11.如果buffer 以其VkDedicatedAllocationBufferCreateInfoNV::dedicatedAllocation为VK_TRUE 创建，则memory必须以其VkDedicatedAllocationBufferCreateInfoNV::buffer等于一个和buffer创建参数相同的VkBuffer句柄，且memoryOffset必须为0
		12.如果VK_KHR_dedicated_allocation 拓展没有开启，且VkPhysicalDeviceProperties::apiVersion小于Vulkan 1.1，且buffer 不以其VkDedicatedAllocationBufferCreateInfoNV::dedicatedAllocation为VK_TRUE 创建，对buffer或image则其memory就不能采用专有分配
		13.如果创建memory时的VkExportMemoryAllocateInfo::handleTypes 不为0则必须包含至少一个设置在VkExternalMemoryBufferCreateInfo::handleTypes 中的类型
		14.如果memory是通过一个导入操作创建的，且不是通过一个含有non-NULL 的buffer对象的VkImportAndroidHardwareBufferInfoANDROID创建的，则导入的memory的external handle type必须设置在buffer创建时候的VkExternalMemoryBufferCreateInfo::handleTypes 中
		15.如果memory 使用过一个含有non-NULL 的buffer对象的VkImportAndroidHardwareBufferInfoANDROID的导入操作创建的，则在buffer创建时候的VkExternalMemoryBufferCreateInfo::handleTypes 中必须包含VK_EXTERNAL_MEMORY_HANDLE_TYPE_ANDROID_HARDWARE_BUFFER_BIT_ANDROID
		16.如果VkPhysicalDeviceBufferDeviceAddressFeatures::bufferDeviceAddress 特性开启且如果buffer以VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT创建，则memory 必须以VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT创建
		17.如果VkPhysicalDeviceBufferDeviceAddressFeatures::bufferDeviceAddressCaptureReplay 特性开启且 如果buffer以VK_BUFFER_CREATE_DEVICE_ADDRESS_CAPTURE_REPLAY_BIT创建，则memory 必须以VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_CAPTURE_REPLAY_BIT创建
		17.如果buffer创建的时候VkBufferCreateInfo::pNext 含有一个VkBufferCollectionBufferCreateInfoFUCHSIA，则memory 创建时候的VkMemoryAllocateInfo::pNext 也必须含有VkBufferCollectionBufferCreateInfoFUCHSIA
		18.如果buffer以VK_BUFFER_CREATE_DESCRIPTOR_BUFFER_CAPTURE_REPLAY_BIT_EXT 创建，则memory必须以VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT 以及 VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_CAPTURE_REPLAY_BIT创建

		*/

		VkBindBufferMemoryInfo bindBufferMemoryInfo{};
		bindBufferMemoryInfo.sType = VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO;
		//VkBindBufferMemoryInfo.pNetx 
		VkBindBufferMemoryDeviceGroupInfo bindBufferMemoryDeviceGroupInfo{};//等价于VkBindBufferMemoryDeviceGroupInfoKHR
		//VkBindMemoryStatusKHR 
		{
			bindBufferMemoryDeviceGroupInfo.sType = VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_DEVICE_GROUP_INFO;
			bindBufferMemoryDeviceGroupInfo.pNext = nullptr;
			bindBufferMemoryDeviceGroupInfo.deviceIndexCount = 0;//pDeviceIndices中的元素个数，如果为0，且memory以VK_MEMORY_HEAP_MULTI_INSTANCE_BIT创建，则相当于pDeviceIndices中的元素是从0到device中的设备数减去1，如果为0且不以VK_MEMORY_HEAP_MULTI_INSTANCE_BIT创建，则相当于pDeviceIndices中的元素是0
			bindBufferMemoryDeviceGroupInfo.pDeviceIndices = VK_NULL_HANDLE;//指向一个uint32_t数组，包含要绑定的设备索引，其中元素指明buffer将绑定到device中第几个物理设备的memory 实例
			/*
			VkBindBufferMemoryDeviceGroupInfo有效用法：
			1.deviceIndexCount必须为0或者等于逻辑设备中的物理设备数
			2.pDeviceIndices 中的元素都必须是有效的设备索引值
			*/

			// Provided by VK_KHR_maintenance6
			typedef struct VkBindMemoryStatusKHR {
				VkStructureType sType;
				const void* pNext;
				VkResult* pResult;
			} VkBindMemoryStatusKHR; //这个没有定义这里先自己定义

			VkBindMemoryStatusKHR bindBufferStatusKHR{};
			bindBufferStatusKHR.sType = VK_STRUCTURE_TYPE_MAX_ENUM;//这里先设置为最大枚举值，实际上应该是VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_STATUS_KHR，但是该值没有定义
			bindBufferStatusKHR.pNext = nullptr;
			bindBufferStatusKHR.pResult = nullptr;//指向一个VkResult指针，用来描述绑定buffer到memory操作的结果


		}

		bindBufferMemoryInfo.pNext = &bindBufferMemoryDeviceGroupInfo;//可以包含一个 VkBindBufferMemoryDeviceGroupInfo 或者 VkBindMemoryStatusKHR
		bindBufferMemoryInfo.buffer = VkBuffer{/*假设这是一个有效的VkBuffer*/ };//要附加到memory的VkBuffer
		bindBufferMemoryInfo.memory = VkDeviceMemory{/*假设这是一个有效的VkDeviceMemory*/ };//buffer需要附加到的VkDeviceMemory
		bindBufferMemoryInfo.memoryOffset = 0;//指明从memory开始的字节偏移量开始的区域将绑定到buffer---从memory的memoryOffset开始 查询获取的VkMemoryRequirements::size大小的内存将绑定到buffer
		/*
		VkBindBufferMemoryInfo有效用法:
		1.buffer 不能已经绑定到memory了
		2.buffer 不能以任何sparse memory binding标志创建
		3.memoryOffset 必须小于memory的大小
		4.memory 必须使用调用vkGetBufferMemoryRequirements传入buffer返回的VkMemoryRequirements.memoryTypeBits允许的一种内存类型创建
		5.memoryOffset必须是调用vkGetBufferMemoryRequirements传入buffer返回的VkMemoryRequirements.alignment的整数倍
		6.调用vkGetBufferMemoryRequirements传入buffer返回的VkMemoryRequirements.size必须小于等于 memory的大小减去memoryOffset
		7.如果buffer需要dedicated allocation（参见传入buffer调用vkGetBufferMemoryRequirements2返回的VkMemoryDedicatedRequirements::requiresDedicatedAllocation），则memory必须以其VkMemoryDedicatedAllocateInfo::buffer等于buffer创建
		8.如果memory创建时候的VkMemoryAllocateInfo.pNext中含有一个buffer不为VK_NULL_HANDLE的VkMemoryDedicatedAllocateInfo，则VkMemoryDedicatedAllocateInfo::buffer必须等于buffer，memoryOffset必须为0
		9.如果buffer 以VK_BUFFER_CREATE_PROTECTED_BIT创建，则buffer就必须绑定到其分配时memory type含有VK_MEMORY_PROPERTY_PROTECTED_BIT的memory对象
		10.如果buffer 不以VK_BUFFER_CREATE_PROTECTED_BIT创建，则buffer就不能绑定到其分配时memory type含有VK_MEMORY_PROPERTY_PROTECTED_BIT的memory对象
		11.如果buffer 以其VkDedicatedAllocationBufferCreateInfoNV::dedicatedAllocation为VK_TRUE 创建，则memory必须以其VkDedicatedAllocationMemoryAllocateInfoNV::buffer等于一个和buffer创建参数相同的VkBuffer句柄，且memoryOffset必须为0
		12.如果VK_KHR_dedicated_allocation 拓展没有开启，且VkPhysicalDeviceProperties::apiVersion小于Vulkan 1.1，且buffer 不以其VkDedicatedAllocationBufferCreateInfoNV::dedicatedAllocation为VK_TRUE 创建，对buffer或image则其memory就不能采用专有分配
		13.如果创建memory时的VkExportMemoryAllocateInfo::handleTypes 不为0则必须包含至少一个设置在VkExternalMemoryBufferCreateInfo::handleTypes 中的类型
		14.如果memory是通过一个导入操作创建的，且不是通过一个含有non-NULL 的buffer对象的VkImportAndroidHardwareBufferInfoANDROID创建的，则导入的memory的external handle type必须设置在buffer创建时候的VkExternalMemoryBufferCreateInfo::handleTypes 中
		15.如果memory 使用过一个含有non-NULL 的buffer对象的VkImportAndroidHardwareBufferInfoANDROID的导入操作创建的，则在buffer创建时候的VkExternalMemoryBufferCreateInfo::handleTypes 中必须包含VK_EXTERNAL_MEMORY_HANDLE_TYPE_ANDROID_HARDWARE_BUFFER_BIT_ANDROID
		16.如果VkPhysicalDeviceBufferDeviceAddressFeatures::bufferDeviceAddress 特性开启则如果buffer以VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT创建，则memory 必须以VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT创建
		17.如果VkPhysicalDeviceBufferDeviceAddressFeatures::bufferDeviceAddressCaptureReplay 特性开启，且如果buffer以VK_BUFFER_CREATE_DEVICE_ADDRESS_CAPTURE_REPLAY_BIT创建，则memory 必须以VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_CAPTURE_REPLAY_BIT创建																		  
		18.如果buffer创建的时候VkBufferCreateInfo::pNext 含有一个VkBufferCollectionBufferCreateInfoFUCHSIA，则memory 创建时候的VkMemoryAllocateInfo::pNext 也必须含有VkBufferCollectionBufferCreateInfoFUCHSIA
		18.如果buffer以VK_BUFFER_CREATE_DESCRIPTOR_BUFFER_CAPTURE_REPLAY_BIT_EXT 创建，则memory必须以VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT 以及 VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_CAPTURE_REPLAY_BIT创建
		19.如果VkBindBufferMemoryInfo::pNext 含有一个VkBindBufferMemoryDeviceGroupInfo，则所有VkBindBufferMemoryDeviceGroupInfo::pDeviceIndices指定的 memory 实例必须已经创建

		*/
		
		
		//等价于vkBindBufferMemory2KHR，如果pBindInfos的元素的pNext中不含VkBindMemoryStatusKHR，且该命令失败，则pBindInfos中的元素引用的buffer会变成终止状态，后续不能继续使用，应该被销毁
		vkBindBufferMemory2(device, 1, &bindBufferMemoryInfo);


	}
	


	//绑定memory 到image
	{
		//绑定memory到 不以 VK_IMAGE_CREATE_DISJOINT_BIT创建的image
		vkBindImageMemory(device, VkImage{/*假设这是一个有效的VkImage*/ }, VkDeviceMemory{/*假设这是一个有效的VkDeviceMemory*/ }, 0);/*
		vkBindImageMemory参数：
		image:要附加到memory的VkImage
		memory:image需要附加到的VkDeviceMemory
		memoryOffset:指明从memory开始的字节偏移量开始的区域将绑定到image---从memory的memoryOffset开始 查询获取的VkMemoryRequirements::size大小的内存将绑定到image
		
		----------------------------------------------------
		vkBindImageMemory有效用法:
		1.image 不能已经绑定到memory了
		2.image 不能以任何sparse memory binding标志创建
		3.memoryOffset 必须小于memory的大小
		4.如果image需要dedicated allocation（参见传入image调用vkGetImageMemoryRequirements2返回的VkMemoryDedicatedRequirements::requiresDedicatedAllocation），则memory必须以其VkMemoryDedicatedAllocateInfo::image等于image创建
		5.如果dedicatedAllocationImageAliasing 特性没有开启，且memory创建时候的VkMemoryAllocateInfo.pNext中含有一个image不为VK_NULL_HANDLE的VkMemoryDedicatedAllocateInfo，则VkMemoryDedicatedAllocateInfo::image必须等于image，memoryOffset必须为0
		6.如果dedicatedAllocationImageAliasing 特性开启，且memory创建时候的VkMemoryAllocateInfo.pNext中含有一个image不为VK_NULL_HANDLE的VkMemoryDedicatedAllocateInfo，则memoryOffset必须为0，image必须等于VkMemoryDedicatedAllocateInfo::image或者在VkImageCreateInfo使用相同参数创建的image，除了
					 extent 和 arrayLayers可能不同，但其遵循以下限制：正要绑定memory的image的extent的每个维度必须是等于或小于原image的extent的对应维度，arrayLayers参数必须是等于或小于原image的arrayLayers。
		7.如果image 以VK_IMAGE_CREATE_PROTECTED_BIT创建，则image就必须绑定到其分配时memory type含有VK_MEMORY_PROPERTY_PROTECTED_BIT的memory对象
		8.如果image 不以VK_IMAGE_CREATE_PROTECTED_BIT创建，则buffer就不能绑定到其分配时memory type含有VK_MEMORY_PROPERTY_PROTECTED_BIT的memory对象
		9.如果image 以其VkDedicatedAllocationImageCreateInfoNV::dedicatedAllocation为VK_TRUE 创建，则memory必须以其VkDedicatedAllocationMemoryAllocateInfoNV::image等于一个和image创建参数相同的VkImage句柄，且memoryOffset必须为0
		10.如果VK_KHR_dedicated_allocation 拓展没有开启，且VkPhysicalDeviceProperties::apiVersion小于Vulkan 1.1，且image 不以其VkDedicatedAllocationImageCreateInfoNV::dedicatedAllocation为VK_TRUE 创建，对buffer或image则其memory就不能采用专有分配
		11.如果创建memory时的VkExportMemoryAllocateInfo::handleTypes 不为0则必须包含至少一个设置在image创建时 VkExternalMemoryImageCreateInfo::handleTypes 中的类型
		12.如果memory是通过一个导入操作创建的，且不是通过一个含有non-NULL 的buffer对象的VkImportAndroidHardwareBufferInfoANDROID创建的，则导入的memory的external handle type必须设置在image创建时候的VkExternalMemoryImageCreateInfo::handleTypes 中
		13.如果memory 使用过一个含有non-NULL 的buffer对象的VkImportAndroidHardwareBufferInfoANDROID的导入操作创建的，则在image创建时候的VkExternalMemoryImageCreateInfo::handleTypes 中必须包含VK_EXTERNAL_MEMORY_HANDLE_TYPE_ANDROID_HARDWARE_BUFFER_BIT_ANDROID
		14.如果image以VK_IMAGE_CREATE_DESCRIPTOR_BUFFER_CAPTURE_REPLAY_BIT_EXT 创建，则memory必须以VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT 以及 VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_CAPTURE_REPLAY_BIT创建
		15.image 不能以VK_IMAGE_CREATE_DISJOINT_BIT 创建
		16.memory 必须使用调用vkGetImageMemoryRequirements传入image返回的VkMemoryRequirements.memoryTypeBits允许的一种内存类型创建
		17.memoryOffset必须是调用vkGetImageMemoryRequirements传入image返回的VkMemoryRequirements.alignment的整数倍
		18.调用vkGetImageMemoryRequirements传入image返回的VkMemoryRequirements.size必须小于等于 memory的大小减去memoryOffset
		19.如果image创建的时候VkImageCreateInfo::pNext 含有一个VkBufferCollectionBufferCreateInfoFUCHSIA，则memory 创建时候的VkMemoryAllocateInfo::pNext 也必须含有VkBufferCollectionBufferCreateInfoFUCHSIA
		*/



		VkBindImageMemoryInfo bindImageMemoryInfo{};
		bindImageMemoryInfo.sType = VK_STRUCTURE_TYPE_BIND_IMAGE_MEMORY_INFO_KHR;
		//VkBindImageMemoryInfo.pNext
		VkBindImageMemoryDeviceGroupInfo bindImageMemoryDeviceGroupInfo{};
		VkBindImageMemorySwapchainInfoKHR bindImageMemorySwapchainInfoKHR{};//指明image将绑定到swapchain的某个image memory上，可以和VkBindImageMemoryDeviceGroupInfo连用
		VkBindImagePlaneMemoryInfo bindImagePlaneMemoryInfo{};//绑定一个 disjoint image的planes
		//VkBindMemoryStatusKHR
		{
			bindImageMemoryDeviceGroupInfo.sType = VK_STRUCTURE_TYPE_BIND_IMAGE_MEMORY_DEVICE_GROUP_INFO;
			bindImageMemoryDeviceGroupInfo.deviceIndexCount = 0;//pDeviceIndices中的元素个数，如果为0，且memory以VK_MEMORY_HEAP_MULTI_INSTANCE_BIT创建，则相当于pDeviceIndices中的元素是从0到device中的设备数减去1，如果为0且不以VK_MEMORY_HEAP_MULTI_INSTANCE_BIT创建，则相当于pDeviceIndices中的元素是0
			bindImageMemoryDeviceGroupInfo.pDeviceIndices = VK_NULL_HANDLE;//指向一个uint32_t数组，包含要绑定的设备索引，其中元素指明buffer将绑定到device中第几个物理设备的memory 实例
			bindImageMemoryDeviceGroupInfo.splitInstanceBindRegionCount = 0;//是pSplitInstanceBindRegions中的元素个数
			bindImageMemoryDeviceGroupInfo.pSplitInstanceBindRegions = VK_NULL_HANDLE;//VkRect2D数组，描述image的那个区域会被绑定到每一个设备的memory 实例上，设N为逻辑设备中的物理设备的数量。如果splitInstanceBindRegionCount大于0，那么pSplitInstanceBindRegions是一个指向N平方个矩形数组的指针，其中资源实例i中元素i*N+j处的矩形指定的图像区域被绑定到内存实例j。绑定到每个稀疏图像块区域的内存块使用内存中的偏移，相对于内存偏移，计算就好像整个图像被绑定到一个连续的内存范围。换句话说，水平相邻的图像块使用连续的内存块，垂直相邻的图像块用每个块的字节数乘以图像块的宽度，（0,0）对应于从内存偏移开始的存储器。
			/*
			VkBindImageMemoryDeviceGroupInfo有效用法:
			1.deviceIndexCount 和splitInstanceBindRegionCount 至少一个必须为0
			2.deviceIndexCount必须为0或者等于逻辑设备中的物理设备数
			3.pDeviceIndices 中的元素必须是有效的设备索引值	
			4.splitInstanceBindRegionCount必须为0或者等于逻辑设备中的物理设备数的平方
			5.pSplitInstanceBindRegions 中的对应到相同image的元素不能重叠
			6.pSplitInstanceBindRegions任何元素的offset.x 必须是image全部non-metadata aspects的sparse image block width（VkSparseImageFormatProperties::imageGranularity.width）的倍数
			7.pSplitInstanceBindRegions任何元素的offset.y 必须是image全部non-metadata aspects的sparse image block height（VkSparseImageFormatProperties::imageGranularity.height）的倍数
			8.pSplitInstanceBindRegions任何元素的extent.width 必须是 image全部non-metadata aspects的sparse image block width的倍数或者extent.width + offset.x 必须等于image subresource的width
			9.pSplitInstanceBindRegions任何元素的extent.height 必须是 image全部non-metadata aspects的sparse image block height的倍数或者extent.height + offset.y 必须等于image subresource的height

			*/
			bindImageMemorySwapchainInfoKHR.sType = VK_STRUCTURE_TYPE_BIND_IMAGE_MEMORY_SWAPCHAIN_INFO_KHR;
			bindImageMemorySwapchainInfoKHR.pNext = nullptr;
			bindImageMemorySwapchainInfoKHR.swapchain = VkSwapchainKHR{/*假设这是一个有效的VkSwapchainKHR*/ };//image将绑定到swapchain的某个image memory上
			bindImageMemorySwapchainInfoKHR.imageIndex = 0;//指明要绑定的swapchain 中的image 索引
			/*
			VkBindImageMemorySwapchainInfoKHR有效用法:
			1.imageIndex 必须小于swapchain中image的数量
			2.如果swapchain以VK_SWAPCHAIN_CREATE_DEFERRED_MEMORY_ALLOCATION_BIT_EXT 创建，则imageIndex 必须是vkAcquireNextImageKHR 或者 vkAcquireNextImage2KHR之前调用返回的索引值

			*/


			bindImagePlaneMemoryInfo.sType = VK_STRUCTURE_TYPE_BIND_IMAGE_PLANE_MEMORY_INFO;
			bindImagePlaneMemoryInfo.pNext = nullptr;
			bindImagePlaneMemoryInfo.planeAspect = VK_IMAGE_ASPECT_COLOR_BIT;//是一个 VkImageAspectFlagBits 指定要绑定的disjoint image plane的aspect
			/*
			VkBindImagePlaneMemoryInfo有效用法：
			1.如果image的tiling为VK_IMAGE_TILING_LINEAR 或者 VK_IMAGE_TILING_OPTIMAL，则planeAspect 必须是一个单独有效的 multi-planar aspect mask 比特
			2.如果image的tiling为VK_IMAGE_TILING_DRM_FORMAT_MODIFIER_EXT，则planeAspect 必须是一个单独有效的image的 memory plane （aspectMask 必须指定一个小于 和image的format以及VkImageDrmFormatModifierPropertiesEXT::drmFormatModifier 相关的VkDrmFormatModifierPropertiesEXT::drmFormatModifierPlaneCount的plane的索引值 ）
			*/

			//VkBindMemoryStatusKHR这里不再赘述，见VkBindBufferMemoryInfo.pNetx 

		
		}
		bindImageMemoryInfo.pNext = nullptr;//可以包含VkBindImageMemoryDeviceGroupInfo, VkBindImageMemorySwapchainInfoKHR, VkBindImagePlaneMemoryInfo, 或者 VkBindMemoryStatusKHR
		bindImageMemoryInfo.image = VkImage{/*假设这是一个有效的VkImage*/ };//是要绑定到memory的image
		bindImageMemoryInfo.memory = VkDeviceMemory{/*假设这是一个有效的VkDeviceMemory*/ };//image需要附加到的VkDeviceMemory
		bindImageMemoryInfo.memoryOffset = 0;//指明从memory开始的字节偏移量开始的区域将绑定到image---从memory的memoryOffset开始 查询获取的VkMemoryRequirements::size大小的内存将绑定到image
		/*
		VkBindImageMemoryInfo有效用法:
		1.image 不能已经绑定到memory了
		2.image 不能以任何sparse memory binding标志创建
		3.memoryOffset 必须小于memory的大小
		4.如果image需要dedicated allocation（参见传入image调用vkGetImageMemoryRequirements2返回的VkMemoryDedicatedRequirements::requiresDedicatedAllocation），则memory必须以其VkMemoryDedicatedAllocateInfo::image等于image创建
		5.如果dedicatedAllocationImageAliasing 特性没有开启，且memory创建时候的VkMemoryAllocateInfo.pNext中含有一个image不为VK_NULL_HANDLE的VkMemoryDedicatedAllocateInfo，则VkMemoryDedicatedAllocateInfo::image必须等于image，memoryOffset必须为0
		6.如果dedicatedAllocationImageAliasing 特性开启，且memory创建时候的VkMemoryAllocateInfo.pNext中含有一个image不为VK_NULL_HANDLE的VkMemoryDedicatedAllocateInfo，则memoryOffset必须为0，image必须等于VkMemoryDedicatedAllocateInfo::image或者在VkImageCreateInfo使用相同参数创建的image，除了
					 extent 和 arrayLayers可能不同，但其遵循以下限制：正要绑定memory的image的extent的每个维度必须是等于或小于原image的extent的对应维度，arrayLayers参数必须是等于或小于原image的arrayLayers。
		7.如果image 以VK_IMAGE_CREATE_PROTECTED_BIT创建，则image就必须绑定到其分配时memory type含有VK_MEMORY_PROPERTY_PROTECTED_BIT的memory对象
		8.如果image 不以VK_IMAGE_CREATE_PROTECTED_BIT创建，则buffer就不能绑定到其分配时memory type含有VK_MEMORY_PROPERTY_PROTECTED_BIT的memory对象
		9.如果image 以其VkDedicatedAllocationImageCreateInfoNV::dedicatedAllocation为VK_TRUE 创建，则memory必须以其VkDedicatedAllocationMemoryAllocateInfoNV::image等于一个和image创建参数相同的VkImage句柄，且memoryOffset必须为0
		10.如果VK_KHR_dedicated_allocation 拓展没有开启，且VkPhysicalDeviceProperties::apiVersion小于Vulkan 1.1，且image 不以其VkDedicatedAllocationImageCreateInfoNV::dedicatedAllocation为VK_TRUE 创建，对buffer或image则其memory就不能采用专有分配
		11.如果创建memory时的VkExportMemoryAllocateInfo::handleTypes 不为0则必须包含至少一个设置在image创建时 VkExternalMemoryImageCreateInfo::handleTypes 中的类型
		12.如果memory是通过一个导入操作创建的，且不是通过一个含有non-NULL 的buffer对象的VkImportAndroidHardwareBufferInfoANDROID创建的，则导入的memory的external handle type必须设置在image创建时候的VkExternalMemoryImageCreateInfo::handleTypes 中
		13.如果memory 使用过一个含有non-NULL 的buffer对象的VkImportAndroidHardwareBufferInfoANDROID的导入操作创建的，则在image创建时候的VkExternalMemoryImageCreateInfo::handleTypes 中必须包含VK_EXTERNAL_MEMORY_HANDLE_TYPE_ANDROID_HARDWARE_BUFFER_BIT_ANDROID
		14.如果image以VK_IMAGE_CREATE_DESCRIPTOR_BUFFER_CAPTURE_REPLAY_BIT_EXT 创建，则memory必须以VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT 以及 VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_CAPTURE_REPLAY_BIT创建
		15.如果pNext中不包含一个VkBindImagePlaneMemoryInfo结构，则（1）memory必须使用调用vkGetImageMemoryRequirements传入image返回的VkMemoryRequirements.memoryTypeBits允许的一种内存类型创建
																  （2）memoryOffset必须是调用vkGetImageMemoryRequirements传入image返回的VkMemoryRequirements.alignment的整数倍
																  （3）调用vkGetImageMemoryRequirements传入image返回的VkMemoryRequirements.size必须小于等于 memory的大小减去memoryOffset
		16.如果pNext中包含一个VkBindImagePlaneMemoryInfo结构，则（1）image必须以VK_IMAGE_CREATE_DISJOINT_BIT 创建
															    （2）memory必须使用调用vkGetImageMemoryRequirements传入image以及pNetx中的VkImagePlaneMemoryRequirementsInfo::planeAspect对应VkBindImagePlaneMemoryInfo::planeAspect的VkImageMemoryRequirementsInfo2参数 返回的VkMemoryRequirements.memoryTypeBits允许的一种内存类型创建
															    （3）memoryOffset必须是调用vkGetImageMemoryRequirements传入image以及pNetx中的VkImagePlaneMemoryRequirementsInfo::planeAspect对应VkBindImagePlaneMemoryInfo::planeAspect的VkImageMemoryRequirementsInfo2参数返回的VkMemoryRequirements.alignment的整数倍
															    （4）调用vkGetImageMemoryRequirements传入image以及pNetx中的VkImagePlaneMemoryRequirementsInfo::planeAspect对应VkBindImagePlaneMemoryInfo::planeAspect的VkImageMemoryRequirementsInfo2参数返回的VkMemoryRequirements.size必须小于等于 memory的大小减去memoryOffset
		17.如果pNext中包含一个VkBindImageMemoryDeviceGroupInfo，则（1）所有VkBindImageMemoryDeviceGroupInfo::pDeviceIndices中指定的memory 实例必须已经创建
																  （2）如果VkBindImageMemoryDeviceGroupInfo::splitInstanceBindRegionCount 不为0，则image 必须以VK_IMAGE_CREATE_SPLIT_INSTANCE_BIND_REGIONS_BIT创建
																  （3）所有VkBindImageMemoryDeviceGroupInfo::pSplitInstanceBindRegions中的元素必须有效的包含在在image维度中的值
																  （4）所有VkBindImageMemoryDeviceGroupInfo::pSplitInstanceBindRegions的元素的合集必须包含整个image的区域
		18.如果image以其VkImageSwapchainCreateInfoKHR::swapchain一个有效的值创建，则pNext中也必须包含一个含有相同swapchain句柄的VkBindImageMemorySwapchainInfoKHR
		19.如果pNext中含有一个VkBindImageMemorySwapchainInfoKHR，则memory必须为VK_NULL_HANDLE
		20.如果pNext不包含一个VkBindImageMemorySwapchainInfoKHR，则memory必须是一个有效的VkDeviceMemory 句柄

		*/



		//等价于vkBindImageMemory2KHR，如果pBindInfos的元素的pNext中不含VkBindMemoryStatusKHR，且该命令失败，则pBindInfos中的元素引用的image会变成终止状态，后续不能继续使用，应该被销毁
		vkBindImageMemory2(device, 1, &bindImageMemoryInfo);/*
		vkBindImageMemory2有效用法：
		1.如果任何 VkBindImageMemoryInfo::image 以VK_IMAGE_CREATE_DISJOINT_BIT创建，则VkBindImageMemoryInfo::image的所有plane必须单独在一个 VkBindImageMemoryInfo 结构中进行绑定
		2.pBindInfos不能多次引用相同的image

		*/


	
	}



	//Buffer-Image Granularity 见p1191
}

void ResourceCreationTest::OtherTest()
{
	// Resource Sharing Mode p1192
	//buffer和image对象通过共享模式来控制如何从队列访问它们
	{
		VkSharingMode sharingMode{};
		/*
		VK_SHARING_MODE_EXCLUSIVE : 指定对对象的任何范围或图像子资源的访问将由单个队列族独占。只能由创建该对象时指明的队列族访问，如果创建时没有指明哪个队列族，则该对象将属于第一次使用该对象的队列族，如果对象要给别的队列族使用，那么要进行所有权转换
		VK_SHARING_MODE_CONCURRENT : 指定支持多个队列族对对象任何范围或图像子资源的并发访问。
		
		*/
	


		//External Resource Sharing
		/*
		底层memory对象同一时候只能由一个vulkan instance访问，vulkan instance独占其自己分配的内存，
		当然vulkan instance可以从外部导入或导出底层memory对象以此来进行memory所有权的转换。只有当内存已从使用外部内存句柄导入或导出到另一个实例或外部API时，应用程序才能转移资源的底层内存的所有权。
		这种所有权转换操作也使用barrier操作来完成。
		*/



	}

	//Memory Aliasing
	{
	//如果一个memory对象的某个范围区域绑定到多个resource 上，则说这个memory是Aliasing的，更多细节见p1194
	
	
	}


	//Buffer Collections p1196
	{
	/*
	概述:
	Fuchsia’s FIDL-based( Fuchsia Interface Definition Language.以fidl作为文件后缀)的系统服务通过VK_FUCHSIA_buffer_collection 拓展和vulkan交互
	buffer collection指的是一组含一个或多个拥有相同属性的buffer，这些属性描述了这些buffer的内部解释，比如维度和布局信息。
	这确保了所有的buffer都可以被需要在多个buffer之间进行交换的任务互换使用，例如双缓冲区图形渲染。
	在Fuchsia 中，buffer collection是其核心设计思想
	
	*/
	
		VkBufferCollectionFUCHSIA bufferCollectionFUCHSIA{};
		
		VkBufferCollectionCreateInfoFUCHSIA bufferCollectionCreateInfoFUCHSIA{};
		bufferCollectionCreateInfoFUCHSIA.sType = VK_STRUCTURE_TYPE_BUFFER_COLLECTION_CREATE_INFO_FUCHSIA;
		bufferCollectionCreateInfoFUCHSIA.pNext = nullptr;
		bufferCollectionCreateInfoFUCHSIA.collectionToken = zx_handle_t{/*假设这是一个有效的zx_handle_t */ };//是一个包含Sysmem客户端的 buffer collection token 的zx_handle_t,collectionToken 必须是一个有效的System以ZX_DEFAULT_CHANNEL_RIGHTS权限分配的Zircon channel的 zx_handle_t (fuchsia.sysmem.Allocator / AllocateSharedCollection) 

		vkCreateBufferCollectionFUCHSIA(device, &bufferCollectionCreateInfoFUCHSIA, nullptr, &bufferCollectionFUCHSIA);





		//buffer collection可以为了VkImage或者VkBuffer的内存分配而构建，可以设置一些限制
		VkImageConstraintsInfoFUCHSIA imageConstraintsInfoFUCHSIA{};
		imageConstraintsInfoFUCHSIA.sType = VK_STRUCTURE_TYPE_IMAGE_CONSTRAINTS_INFO_FUCHSIA;
		imageConstraintsInfoFUCHSIA.pNext = nullptr;
		imageConstraintsInfoFUCHSIA.flags = 0;/*是一个VkImageConstraintsInfoFlagBitsFUCHSIA值，指定关于Sysmem应该为buffer collection分配的内存类型的提示。
		VkImageConstraintsInfoFlagBitsFUCHSIA:
		关于Sysmem应该根据缓冲区集合中的图像的预期使用情况所分配的内存类型的一般提示包括：
		VK_IMAGE_CONSTRAINTS_INFO_CPU_READ_RARELY_FUCHSIA 
		VK_IMAGE_CONSTRAINTS_INFO_CPU_READ_OFTEN_FUCHSIA 
		VK_IMAGE_CONSTRAINTS_INFO_CPU_WRITE_RARELY_FUCHSIA 
		VK_IMAGE_CONSTRAINTS_INFO_CPU_WRITE_OFTEN_FUCHSIA
		
		对于protected内存：
		VK_IMAGE_CONSTRAINTS_INFO_PROTECTED_OPTIONAL_FUCHSIA :  指定protected内存是可选的。
		*/
		imageConstraintsInfoFUCHSIA.formatConstraintsCount = 0;//是pFormatConstraints 中的个数
			VkImageFormatConstraintsInfoFUCHSIA imageFormatConstraintsInfoFUCHSIA{};
			{
			imageFormatConstraintsInfoFUCHSIA.sType = VK_STRUCTURE_TYPE_IMAGE_FORMAT_CONSTRAINTS_INFO_FUCHSIA;
			imageFormatConstraintsInfoFUCHSIA.pNext = nullptr;
			imageFormatConstraintsInfoFUCHSIA.flags = 0;//保留未来使用
			imageFormatConstraintsInfoFUCHSIA.sysmemPixelFormat = 0;//是一个来自fuchsia.sysmem/image_formats.fidl FIDL Interface的 PixelFormatType 值
			imageFormatConstraintsInfoFUCHSIA.requiredFormatFeatures = VK_FORMAT_FEATURE_COLOR_ATTACHMENT_BIT;//是VkFormatFeatureFlagBits组合值的位掩码，指明buffer collection中的buffer需要的format feature，不能为0
			imageFormatConstraintsInfoFUCHSIA.colorSpaceCount = 0;//pColorSpaces中的个数
				VkSysmemColorSpaceFUCHSIA colorSpace{};
				{
					colorSpace.sType = VK_STRUCTURE_TYPE_SYSMEM_COLOR_SPACE_FUCHSIA;
					colorSpace.pNext = nullptr;
					colorSpace.colorSpace = VK_COLORSPACE_SRGB_NONLINEAR_KHR;// Sysmem 的ColorSpaceType值，参见 fuchsia.sysmem/image_formats.fidl
				}
			imageFormatConstraintsInfoFUCHSIA.pColorSpaces = &colorSpace;//是colorSpaceCount 个VkSysmemColorSpaceFUCHSIA 数组的首地址
			imageFormatConstraintsInfoFUCHSIA.imageCreateInfo = VkImageCreateInfo{/*假设这是一个有效的VkImageCreateInfo*/ };//是一个VkImageCreateInfo ，用来创建一个使用 VkBufferCollectionFUCHSIA 的memory的VkImage
			}
		imageConstraintsInfoFUCHSIA.pFormatConstraints = &imageFormatConstraintsInfoFUCHSIA;//是一个指向 formatConstraintsCount个 VkImageFormatConstraintsInfoFUCHSIA 格式结构数组的指针，用于进一步限制基于image的buffer collection的buffer collection的format选择。
			VkBufferCollectionConstraintsInfoFUCHSIA bufferCollectionConstraintsInfoFUCHSIA{};//p1204
			{
				bufferCollectionConstraintsInfoFUCHSIA.sType = VK_STRUCTURE_TYPE_BUFFER_COLLECTION_CONSTRAINTS_INFO_FUCHSIA;
				bufferCollectionConstraintsInfoFUCHSIA.pNext = nullptr;
				bufferCollectionConstraintsInfoFUCHSIA.maxBufferCount = 1;//是buffer collection中可用的buffer的最大数量
				bufferCollectionConstraintsInfoFUCHSIA.minBufferCount = 0;//是buffer collection中可用的buffer的最小数量
				bufferCollectionConstraintsInfoFUCHSIA.minBufferCountForCamping = 0;//是camping 的 per-participant的最小的buffer数量
				bufferCollectionConstraintsInfoFUCHSIA.minBufferCountForDedicatedSlack = 0;//是dedicated slack 的 per-participant的最小的buffer数量
				bufferCollectionConstraintsInfoFUCHSIA.minBufferCountForSharedSlack = 0;//是 shared slack 的 per-participant的最小的buffer数量
			}
		imageConstraintsInfoFUCHSIA.bufferCollectionConstraints = bufferCollectionConstraintsInfoFUCHSIA;//是一个VkBufferCollectionConstraintsInfoFUCHSIA结构，用于为基于buffer的buffer collection的权衡和分配提供参数
		/*
		VkImageConstraintsInfoFUCHSIA有效用法:
		1.pFormatConstraints中的所有元素其VkImageFormatConstraintsInfoFUCHSIA::requiredFormatFeatures必须至少含有一个比特位
		2.如果pFormatConstraints->imageCreateInfo->usage 包含VK_IMAGE_USAGE_SAMPLED_BIT	，则pFormatConstraints->requiredFormatFeatures 必须包含VK_FORMAT_FEATURE_SAMPLED_IMAGE_BIT
		3.如果pFormatConstraints->imageCreateInfo->usage 包含VK_IMAGE_USAGE_STORAGE_BIT	，则pFormatConstraints->requiredFormatFeatures 必须包含VK_FORMAT_FEATURE_STORAGE_IMAGE_BIT
		4.如果pFormatConstraints->imageCreateInfo->usage 包含VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT ，则pFormatConstraints->requiredFormatFeatures 必须包含VK_FORMAT_FEATURE_COLOR_ATTACHMENT_BIT
		5.如果pFormatConstraints->imageCreateInfo->usage 包含VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT ，则pFormatConstraints->requiredFormatFeatures 必须包含VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT
		6.如果pFormatConstraints->imageCreateInfo->usage 包含VK_IMAGE_USAGE_INPUT_ATTACHMENT_BIT ，则pFormatConstraints->requiredFormatFeatures 必须包含VK_FORMAT_FEATURE_COLOR_ATTACHMENT_BIT，或VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT中的至少一个
		7.如果attachmentFragmentShadingRate 特性开启，且如果pFormatConstraints->imageCreateInfo->usage 包含VK_IMAGE_USAGE_FRAGMENT_SHADING_RATE_ATTACHMENT_BIT_KHR ，则pFormatConstraints->requiredFormatFeatures 必须包含VK_FORMAT_FEATURE_FRAGMENT_SHADING_RATE_ATTACHMENT_BIT_KHR
		*/
		
		//设置buffer collection 限制来进行VkImage 的 format的权衡以及buffer collection分配
		vkSetBufferCollectionImageConstraintsFUCHSIA(device, bufferCollectionFUCHSIA,&imageConstraintsInfoFUCHSIA);//如果pImageConstraintsInfo->formatConstraintsCount大于实现能支持的或者pImageConstraintsInfo中列举的format实现不支持则可能失败返回其错误信息，且该接口对于同一个bufferCollection只能调用一次




		VkBufferConstraintsInfoFUCHSIA bufferConstraintsInfoFUCHSIA{};
		bufferConstraintsInfoFUCHSIA.sType = VK_STRUCTURE_TYPE_BUFFER_CONSTRAINTS_INFO_FUCHSIA;
		bufferConstraintsInfoFUCHSIA.pNext = nullptr;
		bufferConstraintsInfoFUCHSIA.createInfo = VkBufferCreateInfo{/*假设这是一个有效的VkBufferCreateInfo*/ };//是一个 VkBufferCreateInfo 描述buffer collection中buffer的属性
		bufferConstraintsInfoFUCHSIA.requiredFormatFeatures = VK_FORMAT_FEATURE_VERTEX_BUFFER_BIT;//是VkFormatFeatureFlagBits组合值的位掩码，指明buffer collection中buffer需要的format feature，必须从 buffer compatible format features（p4085）中列举的值中选取
		VkBufferCollectionConstraintsInfoFUCHSIA bufferCollectionConstraintsInfoFUCHSIA{};//p1204
		{
			bufferCollectionConstraintsInfoFUCHSIA.sType = VK_STRUCTURE_TYPE_BUFFER_COLLECTION_CONSTRAINTS_INFO_FUCHSIA;
			bufferCollectionConstraintsInfoFUCHSIA.pNext = nullptr;
			bufferCollectionConstraintsInfoFUCHSIA.maxBufferCount = 1;//是buffer collection中可用的buffer的最大数量
			bufferCollectionConstraintsInfoFUCHSIA.minBufferCount = 0;//是buffer collection中可用的buffer的最小数量
			bufferCollectionConstraintsInfoFUCHSIA.minBufferCountForCamping = 0;//是camping 的 per-participant的最小的buffer数量
			bufferCollectionConstraintsInfoFUCHSIA.minBufferCountForDedicatedSlack = 0;//是dedicated slack 的 per-participant的最小的buffer数量
			bufferCollectionConstraintsInfoFUCHSIA.minBufferCountForSharedSlack = 0;//是 shared slack 的 per-participant的最小的buffer数量
		}
		bufferConstraintsInfoFUCHSIA.bufferCollectionConstraints = bufferCollectionConstraintsInfoFUCHSIA;//是一个VkBufferCollectionConstraintsInfoFUCHSIA结构，用于为基于buffer的buffer collection的权衡和分配提供参数

		//设置VkBuffer 的buffer collection 限制
		vkSetBufferCollectionBufferConstraintsFUCHSIA(device, bufferCollectionFUCHSIA, &bufferConstraintsInfoFUCHSIA);//如果实现不支持bufferCollectionConstraints中的限制则可能失败，对每个bufferCollection只能调用一次



		VkBufferCollectionPropertiesFUCHSIA bufferCollectionPropertiesFUCHSIA{};
		bufferCollectionPropertiesFUCHSIA.sType = VK_STRUCTURE_TYPE_BUFFER_COLLECTION_PROPERTIES_FUCHSIA;
		bufferCollectionPropertiesFUCHSIA.pNext = nullptr;
		bufferCollectionPropertiesFUCHSIA.bufferCount = 0;//是 buffer collection中buffer的数量
		bufferCollectionPropertiesFUCHSIA.createInfoIndex = 0;//返回之前调用vkSetBufferCollectionImageConstraintsFUCHSIA设置image buffer collection限制时选取的VkImageConstraintsInfoFUCHSIA::pImageCreateInfos中的一个元素的索引值，如果先前调用vkSetBufferCollectionBufferConstraintsFUCHSIA则返回0
		bufferCollectionPropertiesFUCHSIA.formatFeatures = 0;//是buffer collection共有的 VkFormatFeatureFlagBits的组合值的位掩码
		bufferCollectionPropertiesFUCHSIA.memoryTypeBits = 0;//是一个至少包含一个比特为的位掩码，用来指明buffer collection可以导入为什么memory type的buffer collection
		bufferCollectionPropertiesFUCHSIA.samplerYcbcrConversionComponents = VkComponentMapping{};//指明各个分量映射规则的VkComponentMapping
		bufferCollectionPropertiesFUCHSIA.suggestedYcbcrModel = VK_SAMPLER_YCBCR_MODEL_CONVERSION_RGB_IDENTITY;//指明建议的 Y′CbCr模式  的 VkSamplerYcbcrModelConversion值
		bufferCollectionPropertiesFUCHSIA.suggestedYcbcrRange = VK_SAMPLER_YCBCR_RANGE_ITU_FULL;//指明建议的 Y′CbCr范围的VkSamplerYcbcrRange 值
		bufferCollectionPropertiesFUCHSIA.suggestedXChromaOffset = VK_CHROMA_LOCATION_COSITED_EVEN;//指明建议的 X chroma 偏移的 VkChromaLocation 值
		bufferCollectionPropertiesFUCHSIA.suggestedYChromaOffset = VK_CHROMA_LOCATION_COSITED_EVEN;//指明建议的 Y chroma 偏移的 VkChromaLocation 值
		bufferCollectionPropertiesFUCHSIA.sysmemColorSpaceIndex = VkSysmemColorSpaceFUCHSIA{};//是一个指明color space的 VkSysmemColorSpaceFUCHSIA,只对image buffer collection有效，成功后将为kImageConstraintsInfoFUCHSIA::pFormatConstraints的第createInfoIndex个元素的pColorSpaces中的一个值
		bufferCollectionPropertiesFUCHSIA.sysmemPixelFormat = 0;//是定义在fuchsia.sysmem/image_formats.fidl中的System PixelFormatType值
		

		//获取buffer collection的属性
		// 在调用vkSetBufferCollectionImageConstraintsFUCHSIA 或者 vkSetBufferCollectionBufferConstraintsFUCHSIA设置了限制之后获取buffer collection最终的属性
		vkGetBufferCollectionPropertiesFUCHSIA(device, bufferCollectionFUCHSIA, &bufferCollectionPropertiesFUCHSIA);






		//buffer collection memory的导入
		//如果将buffer collection memory导入到image或者buffer，则在其memory创建时候的VkMemoryAllocateInfo的pNext中包含一个VkImportMemoryBufferCollectionFUCHSIA
		VkImportMemoryBufferCollectionFUCHSIA importMemoryBufferCollectionFUCHSIA{};
		importMemoryBufferCollectionFUCHSIA.sType = VK_STRUCTURE_TYPE_IMPORT_MEMORY_BUFFER_COLLECTION_FUCHSIA;
		importMemoryBufferCollectionFUCHSIA.pNext = nullptr;
		importMemoryBufferCollectionFUCHSIA.index = 0;//buffer collection中buffer的索引，必须小于buffer collection的buffer的数量，参见属性VkBufferCollectionPropertiesFUCHSIA:bufferCount
		importMemoryBufferCollectionFUCHSIA.collection = bufferCollectionFUCHSIA;//指明一个buffer collection的 VkBufferCollectionFUCHSIA

		
		
		
		//销毁buffer collection
		vkDestroyBufferCollectionFUCHSIA(device, bufferCollectionFUCHSIA, nullptr);//引用到该buffer collection的image或者buffer 可能会比这个buffer collection的生命周期长








	}


}



NS_TEST_END