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




struct MemoryAllocateInfoEXT {
	VkDedicatedAllocationMemoryAllocateInfoNV dedicatedAllocationMemoryAllocateInfoNV{};
	VkExportMemoryAllocateInfo exportMemoryAllocateInfo{};
	VkExportMemoryAllocateInfoNV exportMemoryAllocateInfoNV{};
	VkExportMemoryWin32HandleInfoKHR exportMemoryWin32HandleInfoKHR{};
	VkExportMemoryWin32HandleInfoNV exportMemoryWin32HandleInfoNV{};
	VkExportMetalObjectCreateInfoEXT exportMetalObjectCreateInfoEXT{};
	VkImportAndroidHardwareBufferInfoANDROID importAndroidHardwareBufferInfoANDROID{};
	VkImportMemoryBufferCollectionFUCHSIA importMemoryBufferCollectionFUCHSIA{};
	VkImportMemoryFdInfoKHR importMemoryFdInfoKHR{};
	VkImportMemoryHostPointerInfoEXT importMemoryHostPointerInfoEXT{};
	VkImportMemoryWin32HandleInfoKHR importMemoryWin32HandleInfoKHR{};
	VkImportMemoryWin32HandleInfoNV importMemoryWin32HandleInfoNV{};
	VkImportMemoryZirconHandleInfoFUCHSIA importMemoryZirconHandleInfoFUCHSIA{};
	VkImportMetalBufferInfoEXT importMetalBufferInfoEXT{};
	VkImportScreenBufferInfoQNX importScreenBufferInfoQNX{};
	VkMemoryAllocateFlagsInfo memoryAllocateFlagsInfo{};
	VkMemoryDedicatedAllocateInfo memoryDedicatedAllocateInfo{};
	VkMemoryOpaqueCaptureAddressAllocateInfo memoryOpaqueCaptureAddressAllocateInfo{};
	VkMemoryPriorityAllocateInfoEXT memoryPriorityAllocateInfoEXT{};
	MemoryAllocateInfoEXT() {
		Init();
	}
	void Init() {
		//这里只是示例，有一些结构体是不能够同时链接到一起链接到VkMemoryAllocateInfo的pNext中的
		dedicatedAllocationMemoryAllocateInfoNV.sType = VK_STRUCTURE_TYPE_DEDICATED_ALLOCATION_MEMORY_ALLOCATE_INFO_NV;
		dedicatedAllocationMemoryAllocateInfoNV.pNext = &exportMemoryAllocateInfo;
		exportMemoryAllocateInfo.sType = VK_STRUCTURE_TYPE_EXPORT_MEMORY_ALLOCATE_INFO;
		exportMemoryAllocateInfo.pNext = &exportMemoryAllocateInfoNV;
		exportMemoryAllocateInfoNV.sType = VK_STRUCTURE_TYPE_EXPORT_MEMORY_ALLOCATE_INFO_NV;
		exportMemoryAllocateInfoNV.pNext = &exportMemoryWin32HandleInfoKHR;
		exportMemoryWin32HandleInfoKHR.sType = VK_STRUCTURE_TYPE_EXPORT_MEMORY_WIN32_HANDLE_INFO_KHR;
		exportMemoryWin32HandleInfoKHR.pNext = &exportMemoryWin32HandleInfoNV;
		exportMemoryWin32HandleInfoNV.sType = VK_STRUCTURE_TYPE_EXPORT_MEMORY_WIN32_HANDLE_INFO_NV;
		exportMemoryWin32HandleInfoNV.pNext = &exportMetalObjectCreateInfoEXT;
		exportMetalObjectCreateInfoEXT.sType = VK_STRUCTURE_TYPE_EXPORT_METAL_OBJECT_CREATE_INFO_EXT;
		exportMetalObjectCreateInfoEXT.pNext = &importAndroidHardwareBufferInfoANDROID;
		importAndroidHardwareBufferInfoANDROID.sType = VK_STRUCTURE_TYPE_IMPORT_ANDROID_HARDWARE_BUFFER_INFO_ANDROID;
		importAndroidHardwareBufferInfoANDROID.pNext = &importMemoryBufferCollectionFUCHSIA;
		importMemoryBufferCollectionFUCHSIA.sType = VK_STRUCTURE_TYPE_IMPORT_MEMORY_BUFFER_COLLECTION_FUCHSIA;
		importMemoryBufferCollectionFUCHSIA.pNext = &importMemoryFdInfoKHR;
		importMemoryFdInfoKHR.sType = VK_STRUCTURE_TYPE_IMPORT_MEMORY_FD_INFO_KHR;
		importMemoryFdInfoKHR.pNext = &importMemoryHostPointerInfoEXT;
		importMemoryHostPointerInfoEXT.sType = VK_STRUCTURE_TYPE_IMPORT_MEMORY_HOST_POINTER_INFO_EXT;
		importMemoryHostPointerInfoEXT.pNext = &importMemoryWin32HandleInfoKHR;
		importMemoryWin32HandleInfoKHR.sType = VK_STRUCTURE_TYPE_IMPORT_MEMORY_WIN32_HANDLE_INFO_KHR;
		importMemoryWin32HandleInfoKHR.pNext = &importMemoryWin32HandleInfoNV;
		importMemoryWin32HandleInfoNV.sType = VK_STRUCTURE_TYPE_IMPORT_MEMORY_WIN32_HANDLE_INFO_NV;
		importMemoryWin32HandleInfoNV.pNext = &importMemoryZirconHandleInfoFUCHSIA;
		importMemoryZirconHandleInfoFUCHSIA.sType = VK_STRUCTURE_TYPE_IMPORT_MEMORY_ZIRCON_HANDLE_INFO_FUCHSIA;
		importMemoryZirconHandleInfoFUCHSIA.pNext = &importMetalBufferInfoEXT;
		importMetalBufferInfoEXT.sType = VK_STRUCTURE_TYPE_IMPORT_METAL_BUFFER_INFO_EXT;
		importMetalBufferInfoEXT.pNext = &importScreenBufferInfoQNX;
		importScreenBufferInfoQNX.sType = VK_STRUCTURE_TYPE_IMPORT_SCREEN_BUFFER_INFO_QNX;
		importScreenBufferInfoQNX.pNext = &memoryAllocateFlagsInfo;
		memoryAllocateFlagsInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO;
		memoryAllocateFlagsInfo.pNext = &memoryDedicatedAllocateInfo;
		memoryDedicatedAllocateInfo.sType = VK_STRUCTURE_TYPE_MEMORY_DEDICATED_ALLOCATE_INFO;
		memoryDedicatedAllocateInfo.pNext = &memoryOpaqueCaptureAddressAllocateInfo;
		memoryOpaqueCaptureAddressAllocateInfo.sType = VK_STRUCTURE_TYPE_MEMORY_OPAQUE_CAPTURE_ADDRESS_ALLOCATE_INFO;
		memoryOpaqueCaptureAddressAllocateInfo.pNext = &memoryPriorityAllocateInfoEXT;
		memoryPriorityAllocateInfoEXT.sType = VK_STRUCTURE_TYPE_MEMORY_PRIORITY_ALLOCATE_INFO_EXT;
		memoryPriorityAllocateInfoEXT.pNext = nullptr;

	}

};




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
	/*
	VkMemoryAllocateInfo有效用法：
	1.如果参数没有指定一个import 或export operation，则allocationSize 必须大于0
	2.参数不能指定多个import 操作
	3.如果参数定义了一个export operation,且handleType不是VK_EXTERNAL_MEMORY_HANDLE_TYPE_ANDROID_HARDWARE_BUFFER_BIT_ANDROID，则allocationSize必须大于0
	4.如果参数定义了一个导入VkBufferCollectionFUCHSIA的import operation,则（1）如果VkMemoryDedicatedAllocateInfo::buffer未非NULL的值，VkImportMemoryBufferCollectionFUCHSIA::collection 以及VkImportMemoryBufferCollectionFUCHSIA::index 必须各自匹配和创建VkMemoryDedicatedAllocateInfo::buffer的VkBufferCollectionBufferCreateInfoFUCHSIA结构体中的 VkBufferCollectionBufferCreateInfoFUCHSIA::collection 和VkBufferCollectionBufferCreateInfoFUCHSIA::index
																		  （2）如果VkMemoryDedicatedAllocateInfo::image未非NULL的值，VkImportMemoryBufferCollectionFUCHSIA::collection 以及VkImportMemoryBufferCollectionFUCHSIA::index 必须各自匹配和创建VkMemoryDedicatedAllocateInfo::image的VkBufferCollectionBufferCreateInfoFUCHSIA结构体中的 VkBufferCollectionBufferCreateInfoFUCHSIA::collection 和VkBufferCollectionBufferCreateInfoFUCHSIA::index
																		  （3）则allocationSize必须和vkGetImageMemoryRequirements或者vkGetBufferMemoryRequirements调用获取的image-based 或buffer-based collections的VkMemoryRequirements::size相匹配。
																		  （4）则pNext中必须包含一个其image 或者 buffer 对象不为VK_NULL_HANDLE的VkMemoryDedicatedAllocateInfo结构体
																		  （5）如果pNext中包含VkMemoryDedicatedAllocateInfo结构体，则VkMemoryDedicatedAllocateInfo::image创建时必须在VkImageCreateInfo::pNext中包含一个VkBufferCollectionImageCreateInfoFUCHSIA结构体，
																		  （6）如果pNext中包含VkMemoryDedicatedAllocateInfo结构体，则VkMemoryDedicatedAllocateInfo::buffer创建时必须在VkBufferCreateInfo::pNext中包含一个VkBufferCollectionImageCreateInfoFUCHSIA结构体，
																		  （7）则memoryTypeIndex 必须是从vkGetBufferCollectionPropertiesFUCHSIA 调用获取的VkBufferCollectionPropertiesFUCHSIA的对应内存类型索引。
	5.如果pNext 中包含了一个VkExportMemoryAllocateInfo，则（1）如果其image或者 buffer不为VK_NULL_HANDLE ，且任何VkExportMemoryAllocateInfo::handleTypes 指定的handle type 需要独占分配，是否独占分配对image可以通过vkGetPhysicalDeviceImageFormatProperties2调用返回的VkExternalImageFormatProperties::externalMemoryProperties.externalMemoryFeatures 或者对于buffer，通过调用vkGetPhysicalDeviceExternalBufferProperties获取的 VkExternalBufferProperties::externalMemoryProperties.externalMemoryFeatures 中进行呈现，则pNext中必须包含一个VkMemoryDedicatedAllocateInfo 或者VkDedicatedAllocationMemoryAllocateInfoNV
														  （2）pNext中就不能再包含一个 VkExportMemoryAllocateInfoNV 或者 VkExportMemoryWin32HandleInfoNV
	6.如果pNext 中包含了一个VkImportMemoryWin32HandleInfoKHR， 则pNext就不能包含 VkImportMemoryWin32HandleInfoNV

	7.如果参数定义了一个import operation,且external handle 是通过Vulkan API创建的，则（1）且这个external handle的类型为VK_EXTERNAL_MEMORY_HANDLE_TYPE_OPAQUE_FD_BIT，则allocationSize 和memoryTypeIndex 就必须和被引入的payload创建时指定的参数相匹配。
																					 （2）VkMemoryAllocateFlagsInfo指定的 device mask必须和被引入的payload创建时指定的参数相匹配。
																					 （3）则传给vkAllocateMemory的 逻辑设备的 physical devices列表必须和被引入的payload分配时传入的physical devices列表相匹配。
																					 （4）如果external handle的类型为VK_EXTERNAL_MEMORY_HANDLE_TYPE_OPAQUE_WIN32_BIT 或者VK_EXTERNAL_MEMORY_HANDLE_TYPE_OPAQUE_WIN32_KMT_BIT， 则allocationSize 和memoryTypeIndex 就必须和被引入的payload创建时指定的参数相匹配。
	8.如果参数定义了一个import operation，且external handle 为Vulkan API外部创建 NT handle 或者一个的global share handle，则memoryTypeIndex 必须是vkGetMemoryWin32HandlePropertiesKHR 返回信息中对应参数中的一个的索引																
	9.如果参数定义了一个import operation，且external handle 类型为VK_EXTERNAL_MEMORY_HANDLE_TYPE_D3D12_HEAP_BIT，则allocationSize 必须和从被提取出的payload中创建Direct3D 12 heap payload时指定的参数相匹配。
	10.如果参数定义了一个import operation，且external handle 是一个Vulkan API外创建的POSIX file descriptor，则memoryTypeIndex 必须是vkGetMemoryFdPropertiesKHR 返回信息中对应参数中的一个的索引
	11.如果protectedMemory 特性没有开启，则VkMemoryAllocateInfo::memoryTypeIndex 不能指向一个含VK_MEMORY_PROPERTY_PROTECTED_BIT 类型的内存类型
	12.如果参数定义了一个import operation，且external handle 为一个host pointer， 则（1）memoryTypeIndex 必须是vkGetMemoryHostPointerPropertiesEXT 返回信息中对应参数中的一个的索引
																					（2）allocationSize 必须是一个整数倍的VkPhysicalDeviceExternalMemoryHostPropertiesEXT::minImportedHostPointerAlignment
																					（3）pNext中不能包含一个其image 或者 buffer 对象不为VK_NULL_HANDLE的VkDedicatedAllocationMemoryAllocateInfoNV结构体
																					（4）pNext中不能包含一个其image 或者 buffer 对象不为VK_NULL_HANDLE的VkMemoryDedicatedAllocateInfo结构体
	13.如果参数定义了一个 import operation，且external handle 类型为VK_EXTERNAL_MEMORY_HANDLE_TYPE_ANDROID_HARDWARE_BUFFER_BIT_ANDROID	，则（1）对于Android hardware buffer，allocationSize必须是从vkGetAndroidHardwareBufferPropertiesANDROID 中返回的值																	
																																			（2）如果pNext中不包含一个VkMemoryDedicatedAllocateInfo 或者VkMemoryDedicatedAllocateInfo::image为VK_NULL_HANDLE，Android hardware buffer 就必须有AHardwareBuffer_Desc::format为AHARDWAREBUFFER_FORMAT_BLOB 以及AHardwareBuffer_Desc::usage 包含AHARDWAREBUFFER_USAGE_GPU_DATA_BUFFER
																																			（3）对于Android hardware buffer， memoryTypeIndex 必须是从vkGetAndroidHardwareBufferPropertiesANDROID 返回的参数中所对应参数的的索引
	14.如果参数没有指定一个import operation，且pNext 中包含一个handleTypes包含VK_EXTERNAL_MEMORY_HANDLE_TYPE_ANDROID_HARDWARE_BUFFER_BIT_ANDROID的 VkExportMemoryAllocateInfo，且pNext中包含一个image 不为VK_NULL_HANDLE的VkMemoryDedicatedAllocateInfo，则allocationSize 必须是0
	15.如果参数定义了一个export operation，且handle类型为VK_EXTERNAL_MEMORY_HANDLE_TYPE_ANDROID_HARDWARE_BUFFER_BIT_ANDROID，则（1）如果pNext中不含VkMemoryDedicatedAllocateInfo，则allocationSize 必须大于 0
																															   （2）如果pNext中包含一个buffer为有效值的VkMemoryDedicatedAllocateInfo，则allocationSize 必须大于0

	16.如果参数定义了一个import operation，且external handle 是一个Android hardware buffer，且pNext中包含一个image 不为VK_NULL_HANDLE的VkMemoryDedicatedAllocateInfo，则（1）Android hardware buffer的AHardwareBuffer::usage 至少要包含AHARDWAREBUFFER_USAGE_GPU_FRAMEBUFFER, AHARDWAREBUFFER_USAGE_GPU_SAMPLED_IMAGE 或者 AHARDWAREBUFFER_USAGE_GPU_DATA_BUFFER 其中一个
																																									    （2）对于Android hardware buffer， image的format必须为VK_FORMAT_UNDEFINED 或者通过vkGetAndroidHardwareBufferPropertiesANDROID返回的VkAndroidHardwareBufferFormatPropertiesANDROID::format
																																									    （3）image的width, height, 以及 array layer 维数必须和 Android hardware buffer’s AHardwareBuffer_Desc中的对应参数相同
																																									    （4）如果Android hardware buffer的 AHardwareBuffer::usage 包含AHARDWAREBUFFER_USAGE_GPU_MIPMAP_COMPLETE ，则image必须有一个完成的mipmap链（即mipmap一直到width和height都为1 ？）
																																									    （5）如果Android hardware buffe的 AHardwareBuffer::usage不包含AHARDWAREBUFFER_USAGE_GPU_MIPMAP_COMPLETE，则iamge必须只有一个mipmap级别
																																									    （6）每一个设置为image 的usage的比特位必须罗列在AHardwareBuffer Usage Equivalence 中，如果没有在该列表中，则该比特位必须包含在Android hardware buffer的 AHardwareBuffer_Desc::usage 中

	17.如果参数定义了一个import operation，且external handle 类型为VK_EXTERNAL_MEMORY_HANDLE_TYPE_SCREEN_BUFFER_BIT_QNX，则（1） VkPhysicalDeviceExternalMemoryScreenBufferFeaturesQNX::screenBufferImport必须开启
																														   （2）allocationSize 必须是为QNX Screen buffer调用 vkGetScreenBufferPropertiesQNX 返回的大小
																														   （3）memoryTypeIndex 必须是为QNX Screen buffer调用 vkGetScreenBufferPropertiesQNX 返回的参数中所对应参数的的一个索引
	18.如果参数定义了一个import operation，且external handle 为一个QNX Screen buffer，且pNext中包含一个image 不为VK_NULL_HANDLE的VkMemoryDedicatedAllocateInfo，则（1）QNX Screen’s buffer必须是一个有效的QNX Screen buffer
																																								  （2）image的format必须为VK_FORMAT_UNDEFINED 或者为 QNX Screen buffer 通过vkGetScreenBufferPropertiesQNX返回的VkScreenBufferFormatPropertiesQNX::format
																																								  （3）image的width, height, 以及 array layer 维数必须和 QNX Screen buffer的 _screen_buffer中的对应参数相同
	19.如果VkMemoryOpaqueCaptureAddressAllocateInfo::opaqueCaptureAddress 不为 0，VkMemoryAllocateFlagsInfo::flags必须包含VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_CAPTURE_REPLAY_BIT
	20.如果VkMemoryAllocateFlagsInfo::flags包含VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_CAPTURE_REPLAY_BIT，则bufferDeviceAddressCaptureReplay 特性必须开启
	21.如果VkMemoryAllocateFlagsInfo::flags包含VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT，则bufferDeviceAddress 特性必须开启
	22.如果pNext中包含VkImportMemoryHostPointerInfoEXT，则VkMemoryOpaqueCaptureAddressAllocateInfo::opaqueCaptureAddress 必须为 0
	23.如果参数定义了一个import operation，VkMemoryOpaqueCaptureAddressAllocateInfo::opaqueCaptureAddress 必须为 0
	24.如果参数定义了一个import operation，且external handle 类型为VK_EXTERNAL_MEMORY_HANDLE_TYPE_ZIRCON_VMO_BIT_FUCHSIA，则（1）memoryTypeIndex 必须是vkGetMemoryZirconHandlePropertiesFUCHSIA 返回信息VkMemoryZirconHandlePropertiesFUCHSIA 中对应参数memoryTypeBits 中的一个的索引
																															（2）allocationSize 必须大于 0 且小于等于通过zx_vmo_get_size(handle)获取的VMO大小，其中handle为引入外部内存的VMO handle
	25.如果pNext中包含一个VkExportMetalObjectCreateInfoEXT， 则该结构体的exportObjectType必须为VK_EXPORT_METAL_OBJECT_TYPE_METAL_BUFFER_BIT_EXT



	*/
	
	
	
	
	
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