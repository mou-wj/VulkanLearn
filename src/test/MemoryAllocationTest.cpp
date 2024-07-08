#include "MemoryAllocationTest.h"

NS_TEST_BEGIN


MemoryAllocationTest::MemoryAllocationTest()
{
}

void MemoryAllocationTest::run()
{
}

MemoryAllocationTest::~MemoryAllocationTest()
{
}
namespace CustomMemoryFunc {
	PFN_vkAllocationFunction;
	PFN_vkReallocationFunction;
	PFN_vkFreeFunction;
	PFN_vkInternalAllocationNotification;
	PFN_vkInternalFreeNotification;

	using VkSystemAllocationScopeWithNotation = VkSystemAllocationScope;/*
		
    VK_SYSTEM_ALLOCATION_SCOPE_COMMAND: 指明分配操作的作用域为vulkan command的持续期间
    VK_SYSTEM_ALLOCATION_SCOPE_OBJECT:  指明分配操作的作用域为正在被分配或者使用的vulkan objects的整个生命周期
    VK_SYSTEM_ALLOCATION_SCOPE_CACHE:   指明分配操作的作用域为VkPipelineCache 或者 VkValidationCacheEXT的生命周期
    VK_SYSTEM_ALLOCATION_SCOPE_DEVICE:   指明分配操作的作用域为Vulkan Device的生命周期
    VK_SYSTEM_ALLOCATION_SCOPE_INSTANCE:  指明分配操作的作用域为Vulkan Instance的生命周期

	*/


	using VkInternalAllocationTypeWithNotation = VkInternalAllocationType;/*
	VK_INTERNAL_ALLOCATION_TYPE_EXECUTABLE:   指定分配操作由host 来执行
	*/


	//一些可能用到这些内存操作函数的场景见p886

	void* CustomAlloc(
		void* pUserData,//调用时传入 VkAllocationCallbacks.pUserData
		size_t                                      size,//传入需要分配的内存大小
		size_t                                      alignment,//需要的内存对齐的字节数大小，必须是2的幂
		VkSystemAllocationScope                     allocationScope //是一个VkSystemAllocationScope值，指定分配生命周期的分配范围。
	) {
		//这里定义自定义的内存分配操作
		return nullptr;
	}

	void* CustomRealloc(
		void* pUserData,//调用时传入 VkAllocationCallbacks.pUserData
		void* pOriginal,//必须是NULL或之前由兼容分配器的 pfnReallocation 或者 pfnAllocation返回的内存指针。如果为NULL，等同于调用一个PFN_vkAllocationFunction
		size_t                                      size,//传入需要分配的内存大小，如果为0，等同于调用 PFN_vkFreeFunction
		size_t                                      alignment,//需要的内存对齐的字节数大小，必须是2的幂，且必须和 pOriginal分配时的alignment 相同
		VkSystemAllocationScope                     allocationScope //是一个VkSystemAllocationScope值，指定分配生命周期的分配范围。
	) {
		//这里定义自定义的内存重新分配操作
		return nullptr;
	}
	void CustomFree(
		void* pUserData,//调用时传入 VkAllocationCallbacks.pUserData
		void* pMemory//需要被释放的内存指针
	) {
		//这里定义自定义的内存释放操作
	}

	void CustomInternalAlloc(
		void* pUserData,//调用时传入 VkAllocationCallbacks.pUserData
		size_t                                      size,//传入需要分配的内存大小
		VkInternalAllocationType                    allocationType,//是VkInternalAllocationType 值，指定请求的分配类型。
		VkSystemAllocationScope                     allocationScope//是一个VkSystemAllocationScope值，指定分配生命周期的分配范围。
	) {
		//这里定义自定义的内部内存分配操作
	
	}

	void CustomInternalFree(
		void* pUserData,//调用时传入 VkAllocationCallbacks.pUserData
		size_t                                      size,//传入需要分配的内存大小
		VkInternalAllocationType                    allocationType,//是VkInternalAllocationType 值，指定请求的分配类型。
		VkSystemAllocationScope                     allocationScope//是一个VkSystemAllocationScope值，指定分配生命周期的分配范围。
	) {
		//这里定义自定义的内部内存释放操作

	}

}
void MemoryAllocationTest::HostAllocationCallbacksTest()
{


	VkAllocationCallbacks callbacks;
	callbacks.pUserData = nullptr;//是一个要通过回调的实现来解释的值。当调用VkAllocationCallbacks中的任何一个回调被调用时，Vulkan实现将把这个值作为第一个参数传递给该回调函数。每次将分配器传递到命令时，此值都会发生变化，即使当同一对象在多个命令中接受分配器时也是如此。
	callbacks.pfnAllocation = &CustomMemoryFunc::CustomAlloc;//是一个指向应用程序定义的内存分配函数的PFN_vkAllocationFunction指针。
	callbacks.pfnFree = &CustomMemoryFunc::CustomFree;//是一个指向应用程序定义的释放内存函数的PFN_vkFreeFunction指针。
	callbacks.pfnReallocation = &CustomMemoryFunc::CustomRealloc;//是一个指向应用程序定义的内存重新分配函数的PFN_vkReallocationFunction指针。
	callbacks.pfnInternalAllocation = VK_NULL_HANDLE;//是一个指向应用程序定义函数的PFN_vkInternalAllocationNotification指针，实现在进行内部分配时调用该函数。
	callbacks.pfnInternalFree = VK_NULL_HANDLE;//是一个指向应用程序定义函数的PFN_vkInternalFreeNotification指针，当实现释放内部分配时，实现会调用该函数。
	/*
	VkAllocationCallbacks有效用法：
	1.pfnAllocation必须是一个有效的用户定义的 PFN_vkAllocationFunction 指针
	2.pfnReallocation必须是一个有效的用户定义的 PFN_vkReallocationFunction 指针
	3.pfnFree必须是一个有效的用户定义的 PFN_vkFreeFunction 指针
	4.pfnInternalAllocation 以及 pfnInternalFree 必须同时为NULL 或者同时是有效的指针
	*/






}

void MemoryAllocationTest::DeviceMemoryTest()
{

	//物理设备的内存属性描述了内存堆和可用的内存类型。
	//查询内存属性
	VkPhysicalDeviceMemoryProperties deviceMemoryProps;
	deviceMemoryProps.memoryHeapCount; //memoryHeaps中的有效类型个数
	deviceMemoryProps.memoryHeaps;//是一个VK_MAX_MEMORY_HEAPS 个 VkMemoryHeap 结构的数组，描述可以分配内存的内存堆
	deviceMemoryProps.memoryTypeCount;//memoryTypes中的有效类型个数
	deviceMemoryProps.memoryTypes;//是一个VK_MAX_MEMORY_TYPES 个 VkMemoryType 结构的数组，描述了可用于访问从内存堆指定的堆中分配的内存类型的内存类型。其中VkMemoryPropertyFlags是子集有序的，即如果一个VkMemoryPropertyFlags为另一个VkMemoryPropertyFlags的子集，其索引小
	vkGetPhysicalDeviceMemoryProperties(physicalDevice, &deviceMemoryProps);

	//VkMemoryHeap
	VkMemoryHeap& tmpMemoryHeap = deviceMemoryProps.memoryHeaps[0];
	tmpMemoryHeap.size;//指明当前堆的大小
	tmpMemoryHeap.flags;/*指明堆的属性
	VK_MEMORY_HEAP_DEVICE_LOCAL_BIT: 指明该堆对应到device-local 的内存，device-local 内存相比于host-local内存由不同的性能特性，能够支持不同的内存属性
	VK_MEMORY_HEAP_MULTI_INSTANCE_BIT: 指明这个堆在一个逻辑device中且表示多个physical device的堆内存，每个physical device中都有这么一个堆，分配这么一个堆会导致每个physical device上都会分配这么一个堆

	*/

	//VkMemoryType
	VkMemoryType& tmpMemoryType = deviceMemoryProps.memoryTypes[0];
	tmpMemoryType.heapIndex;//指明这个内存类型在memoryHeaps中所对应的堆索引
	tmpMemoryType.propertyFlags;/*是VkMemoryPropertyFlagBits的组合值，指明内存属性：
		VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT: 指定分配给此类型的内存是最有效的设备访问内存。当且仅当内存类型属于具有VK_MEMORY_HEAP_DEVICE_LOCAL_BIT集的堆时，才将设置此属性。
		VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT: 指定可以使用vkMapMemory映射分配给此类型的内存以进行主机访问
		VK_MEMORY_PROPERTY_HOST_COHERENT_BIT: 指定不需要vkFlushMappedMemoryRanges和vkInvalidateMappedMemoryRanges主机端缓存管理命令来刷新主机的缓存写入到设备或使设备写入对主机可见。
		VK_MEMORY_PROPERTY_HOST_CACHED_BIT: 指定将分配给此类型的内存缓存在主机上。主机内存对未缓存内存的访问比缓存内存慢，但是未缓存的内存总是主机一致的。
		VK_MEMORY_PROPERTY_LAZILY_ALLOCATED_BIT: 指定该内存类型仅允许设备访问该内存。内存类型不能同时设置了VK_MEMORY_PROPERTY_LAZILY_ALLOCATED_BIT和VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT。此外，对象的支持内存可能由 Lazily Allocated Memory 中指定的实现延迟地提供。
		VK_MEMORY_PROPERTY_PROTECTED_BIT: 指定内存类型仅允许设备访问内存，并允许受保护的队列操作访问内存。内存类型不能为有VK_MEMORY_PROPERTY_PROTECTED_BIT和任何VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT、VK_MEMORY_PROPERTY_HOST_COHERENT_BIT或VK_MEMORY_PROPERTY_HOST_CACHED_BIT的组合。
		VK_MEMORY_PROPERTY_DEVICE_COHERENT_BIT_AMD: 指定设备对此内存类型分配的访问将自动提供可用和可见
		VK_MEMORY_PROPERTY_DEVICE_UNCACHED_BIT_AMD: 指定在设备上对此类型的内存分配不进行缓存。未缓存的设备内存总是与设备相一致的。
		VK_MEMORY_PROPERTY_RDMA_CAPABLE_BIT_NV: 指定外部设备可以直接访问此内存

	propertyFlags的有效组合值：
	- VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT
	- VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_CACHED_BIT
	- VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_CACHED_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT
	- VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT
	- VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT | VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT
	- VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT | VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_CACHED_BIT
	- VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT | VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_CACHED_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT
	- VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT | VK_MEMORY_PROPERTY_LAZILY_ALLOCATED_BIT
	- VK_MEMORY_PROPERTY_PROTECTED_BIT
	- VK_MEMORY_PROPERTY_PROTECTED_BIT | VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT
	- VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT | VK_MEMORY_PROPERTY_DEVICE_COHERENT_BIT_AMD
	- VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_CACHED_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT | VK_MEMORY_PROPERTY_DEVICE_COHERENT_BIT_AMD
	- VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT | VK_MEMORY_PROPERTY_DEVICE_COHERENT_BIT_AMD
    - VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT | VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT | VK_MEMORY_PROPERTY_DEVICE_COHERENT_BIT_AMD
    - VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT | VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_CACHED_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT | VK_MEMORY_PROPERTY_DEVICE_COHERENT_BIT_AMD
    - VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT | VK_MEMORY_PROPERTY_DEVICE_COHERENT_BIT_AMD | VK_MEMORY_PROPERTY_DEVICE_UNCACHED_BIT_AMD
    - VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_CACHED_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT | VK_MEMORY_PROPERTY_DEVICE_COHERENT_BIT_AMD | VK_MEMORY_PROPERTY_DEVICE_UNCACHED_BIT_AMD
    - VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT | VK_MEMORY_PROPERTY_DEVICE_COHERENT_BIT_AMD | VK_MEMORY_PROPERTY_DEVICE_UNCACHED_BIT_AMD
    - VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT | VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT | VK_MEMORY_PROPERTY_DEVICE_COHERENT_BIT_AMD | VK_MEMORY_PROPERTY_DEVICE_UNCACHED_BIT_AMD
    - VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT | VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_CACHED_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT | VK_MEMORY_PROPERTY_DEVICE_COHERENT_BIT_AMD | VK_MEMORY_PROPERTY_DEVICE_UNCACHED_BIT_AMD
    - VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT | VK_MEMORY_PROPERTY_RDMA_CAPABLE_BIT_NV
	*/

	//查询内存属性2，只是比VkPhysicalDeviceMemoryProperties多了些拓展信息
	VkPhysicalDeviceMemoryProperties2 deviceMemoryProps2;
	deviceMemoryProps2.memoryProperties;//是一个 VkPhysicalDeviceMemoryProperties 数据结构体
	deviceMemoryProps2.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MEMORY_PROPERTIES_2;
		VkPhysicalDeviceMemoryBudgetPropertiesEXT deviceMemoryBudgetPropsEXT;
		deviceMemoryBudgetPropsEXT.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MEMORY_BUDGET_PROPERTIES_EXT;
		deviceMemoryBudgetPropsEXT.pNext = nullptr;
		deviceMemoryBudgetPropsEXT.heapBudget;//是一个VK_MAX_MEMORY_HEAPS个 VkDeviceSize值的数组，其中返回内存预算，对应每一个堆。堆的预算是在分配可能失败或导致性能下降之前进程可以从堆分配多少内存的粗略估计。该预算包括当前分配的任何设备内存
		deviceMemoryBudgetPropsEXT.heapUsage;//是一个VK_MAX_MEMORY_HEAPS个 VkDeviceSize值的数组，其中返回内存的使用量，对应每一个堆。堆的使用量是对进程当前在该堆中使用的内存量的估计。
	deviceMemoryProps2.pNext = &deviceMemoryBudgetPropsEXT;//这里可以包含一个 VkPhysicalDeviceMemoryBudgetPropertiesEXT
	vkGetPhysicalDeviceMemoryProperties2(physicalDevice, &deviceMemoryProps2);
	


	//分配内存
	VkDeviceMemory deviceMemory{VK_NULL_HANDLE};
	VkMemoryAllocateInfo memoryAllocateInfo{};
	memoryAllocateInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
	memoryAllocateInfo.pNext = nullptr;
	memoryAllocateInfo.allocationSize = 1;//只需要分配的内存的字节数
	memoryAllocateInfo.memoryTypeIndex = 0;//是从vkGetPhysicalDeviceMemoryProperties获取的VkPhysicalDeviceMemoryProperties结构的memoryTypes数组中的内存类型的索引。
	vkAllocateMemory(device, &memoryAllocateInfo, nullptr, &deviceMemory);
	/*
	vkAllocateMemory有效用法:
	1.pAllocateInfo->allocationSize必须小于等于 VkPhysicalDeviceMemoryProperties::memoryHeaps[memindex].size，其中memindex 为通过vkGetPhysicalDeviceMemoryProperties接口查询的 VkPhysicalDeviceMemoryProperties::memoryTypes[pAllocateInfo->memoryTypeIndex].heapIndex，VkPhysicalDeviceMemoryProperties是
	2.pAllocateInfo->memoryTypeIndex必须小于通过vkGetPhysicalDeviceMemoryProperties接口查询的VkPhysicalDeviceMemoryProperties::memoryTypeCount，
	3.如果 deviceCoherentMemory 特性没有开启，pAllocateInfo->memoryTypeIndex就不能指定一个支持 VK_MEMORY_PROPERTY_DEVICE_COHERENT_BIT_AMD的内存类型
	4.当前在device上分配的内存大小必须小于VkPhysicalDeviceLimits::maxMemoryAllocationCount
	
	*/



}


NS_TEST_END