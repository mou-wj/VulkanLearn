#include "ResourceCreationTest.h"
#include <Windows.h>
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
	imageCreateInfo.tiling = VK_IMAGE_TILING_OPTIMAL;//指明image的 texel blocks的内存排布的一个 VkImageTiling
	imageCreateInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;//是一个 VkSharingMode 值，指定图像在它将被多个队列族访问时的共享模式。
	imageCreateInfo.queueFamilyIndexCount = 0;//pQueueFamilyIndices的元素个数
	imageCreateInfo.pQueueFamilyIndices = VK_NULL_HANDLE;//是指向将访问此图像的队列族索引数组的指针。如果共享模式不是VK_SHARING_MODE_CONCURRENT，则被忽略。
	imageCreateInfo.samples = VK_SAMPLE_COUNT_1_BIT;// 是一个指定samples per texel采样数的 VkSampleCountFlagBits
	imageCreateInfo.imageType = VK_IMAGE_TYPE_2D;//是一个指定image的基本维度的VkImageType值。从图像类型的目的上讲，array textures中的layers不计入维度
	imageCreateInfo.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED; //是一个VkImageLayout 值，指定图像的所有image subresources (mips 以及 layers)的初始VkAmageLayout 值。请参见Image Layout p1078
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



}



NS_TEST_END