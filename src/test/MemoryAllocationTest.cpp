#include "MemoryAllocationTest.h"
#include <Windows.h>
#include <vulkan/vulkan_win32.h>
#include <winnt.h>
#include <vulkan/vulkan_metal.h>
#include <vulkan/vulkan_android.h>
typedef uint32_t zx_handle_t;//因为zx_handle_t 是google的开源操作系统fuchsia的句柄类型，所以这里定义一个uint32_t类型的句柄类型zx_handle_t，不起实际作用只是为了通过编译
#include <vulkan/vulkan_fuchsia.h>
#include <vulkan/vulkan_screen.h>
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
		MemoryAllocateInfoEXT memoryAllocateInfoEXT{};
	memoryAllocateInfo.pNext = &memoryAllocateInfoEXT.dedicatedAllocationMemoryAllocateInfoNV;
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
	
	



	//VkMemoryDedicatedAllocateInfo  
	//如果在VkMemoryAllocateInfo的pNext中包含，则该结构体必须含有一个单独的内存所绑定的buffer或者image 对象指针
	VkMemoryDedicatedAllocateInfo& memoryDedicatedAllocateInfo = memoryAllocateInfoEXT.memoryDedicatedAllocateInfo;
	memoryDedicatedAllocateInfo.buffer = VK_NULL_HANDLE; //是VK_NULL_HANDLE或此内存将被绑定到的VkBuffer的句柄。
	memoryDedicatedAllocateInfo.image = VK_NULL_HANDLE;//是VK_NULL_HANDLE或此内存将被绑定到的VkImage的句柄。
	/*
	VkMemoryDedicatedAllocateInfo有效用法:
	1.image 和buffer 至少一个为VK_NULL_HANDLE
	2.如果 image 不为VK_NULL_HANDLE 则（1）如果memory 不是一个引入的 Android Hardware Buffer或者QNX Screen buffer ,则VkMemoryAllocateInfo::allocationSize 必须等于 image的 VkMemoryRequirements::size
						              （2）image创建时候的VkImageCreateInfo::flags 不能含有 VK_IMAGE_CREATE_SPARSE_BINDING_BIT，VK_IMAGE_CREATE_DISJOINT_BIT
									  （3）如果VkMemoryAllocateInfo定义了一个memory import operation，且其handle类型为 VK_EXTERNAL_MEMORY_HANDLE_TYPE_OPAQUE_WIN32_BIT, VK_EXTERNAL_MEMORY_HANDLE_TYPE_OPAQUE_WIN32_KMT_BIT, VK_EXTERNAL_MEMORY_HANDLE_TYPE_D3D11_TEXTURE_BIT, VK_EXTERNAL_MEMORY_HANDLE_TYPE_D3D11_TEXTURE_KMT_BIT, VK_EXTERNAL_MEMORY_HANDLE_TYPE_D3D12_HEAP_BIT, 
									  		    或者 VK_EXTERNAL_MEMORY_HANDLE_TYPE_D3D12_RESOURCE_BIT，且该外部handle是由Vulkan API创建的，则被引入的 memory必须是一个 dedicated image分配的（即该内存只被image所拥有），且image要和该memory 所关联的VkImage相同
									  （4）如果VkMemoryAllocateInfo定义了一个memory import operation，且其handle类型为 VK_EXTERNAL_MEMORY_HANDLE_TYPE_OPAQUE_FD_BIT ，VK_EXTERNAL_MEMORY_HANDLE_TYPE_ZIRCON_VMO_BIT_FUCHSIA，则被引入的 memory必须是一个 dedicated image分配的（即该内存只被image所拥有），且image要和该memory 所关联的VkImage相同

	3.如果 buffer 不为VK_NULL_HANDLE 则（1）如果memory 不是一个引入的 Android Hardware Buffer或者QNX Screen buffer ,则VkMemoryAllocateInfo::allocationSize 必须等于 buffer 的 VkMemoryRequirements::size
									   （2）buffer 创建时候的VkBufferCreateInfo::flags 不能含有 VK_BUFFER_CREATE_SPARSE_BINDING_BIT
									   （3）如果VkMemoryAllocateInfo定义了一个memory import operation，且其handle类型为 VK_EXTERNAL_MEMORY_HANDLE_TYPE_OPAQUE_WIN32_BIT, VK_EXTERNAL_MEMORY_HANDLE_TYPE_OPAQUE_WIN32_KMT_BIT, VK_EXTERNAL_MEMORY_HANDLE_TYPE_D3D11_TEXTURE_BIT, VK_EXTERNAL_MEMORY_HANDLE_TYPE_D3D11_TEXTURE_KMT_BIT, VK_EXTERNAL_MEMORY_HANDLE_TYPE_D3D12_HEAP_BIT,
												或者 VK_EXTERNAL_MEMORY_HANDLE_TYPE_D3D12_RESOURCE_BIT，且该外部handle是由Vulkan API创建的，则被引入的 memory必须是一个 dedicated buffer分配的（即该内存只被buffer 所拥有），且buffer要和该memory 所关联的VkBuffer相同
									   （4）如果VkMemoryAllocateInfo定义了一个memory import operation，且其handle类型为 VK_EXTERNAL_MEMORY_HANDLE_TYPE_OPAQUE_FD_BIT ，VK_EXTERNAL_MEMORY_HANDLE_TYPE_ZIRCON_VMO_BIT_FUCHSIA，则被引入的 memory必须是一个 dedicated buffer分配的（即该内存只被buffer 所拥有），且buffer要和该memory 所关联的VkBuffer相同

	*/


	// VkDedicatedAllocationMemoryAllocateInfoNV,功能和VkMemoryDedicatedAllocateInfo 相似
	//如果在VkMemoryAllocateInfo的pNext中包含，则该结构体必须含有一个单独的内存所绑定的buffer或者image 对象指针
	VkDedicatedAllocationMemoryAllocateInfoNV& memoryDedicatedAllocateInfoNV = memoryAllocateInfoEXT.dedicatedAllocationMemoryAllocateInfoNV;
	memoryDedicatedAllocateInfo.buffer = VK_NULL_HANDLE; //是VK_NULL_HANDLE或此内存将被绑定到的VkBuffer的句柄。
	memoryDedicatedAllocateInfo.image = VK_NULL_HANDLE;//是VK_NULL_HANDLE或此内存将被绑定到的VkImage的句柄。
	/*
	VkDedicatedAllocationMemoryAllocateInfoNV有效用法：
	1.image 和buffer 至少一个为VK_NULL_HANDLE
	2.如果 image 不为VK_NULL_HANDLE 则（1）image必须以 VkDedicatedAllocationImageCreateInfoNV::dedicatedAllocation为VK_TRUE创建
									  （2）VkMemoryAllocateInfo::allocationSize 必须等于 image的 VkMemoryRequirements::size
									  （3）如果VkMemoryAllocateInfo定义了一个memory import operation，则被引入的 memory必须是一个 dedicated image分配的（即该内存只被image所拥有），且image要和该memory 所关联的VkImage相同
									  

	3.如果 buffer 不为VK_NULL_HANDLE 则（1）buffer必须以 VkDedicatedAllocationImageCreateInfoNV::dedicatedAllocation为VK_TRUE创建
									   （2）VkMemoryAllocateInfo::allocationSize 必须等于 buffer 的 VkMemoryRequirements::size
									   （3）如果VkMemoryAllocateInfo定义了一个memory import operation，则被引入的 memory必须是一个 dedicated buffer分配的（即该内存只被buffer 所拥有），且buffer要和该memory 所关联的VkBuffer相同
									   
	
	*/

	// VkMemoryPriorityAllocateInfoEXT
	//如果在VkMemoryAllocateInfo的pNext中包含,则该结构体表示该内存的优先级

	VkMemoryPriorityAllocateInfoEXT& memoryPriorityAllocateInfoEXT = memoryAllocateInfoEXT.memoryPriorityAllocateInfoEXT;
	memoryPriorityAllocateInfoEXT.priority = 0;//是介于0到1之间的浮点值，指示分配相对于其他内存分配的优先级。值越大，优先级就越高。优先级的粒度依赖于实现。
		{
		//改变现有memory的优先级
		vkSetDeviceMemoryPriorityEXT(device, deviceMemory, 0);
		}
	
	//VkExportMemoryAllocateInfo
	//如果在VkMemoryAllocateInfo的pNext中包含一个,则该结构体表示该内存的payload可以导入到其他程序 或者Vulkan Instance使用
	VkExportMemoryAllocateInfo& exportMemoryAllocateInfo = memoryAllocateInfoEXT.exportMemoryAllocateInfo;
	exportMemoryAllocateInfo.handleTypes = VK_EXTERNAL_MEMORY_HANDLE_TYPE_OPAQUE_FD_BIT;//是 0 或一个或多个VkExternalMemoryHandleTypeFlagBits的位掩码组合，指定应用程序可以从结果分配中导出的一个或多个内存句柄类型。该应用程序可以为相同的分配请求多个句柄类型。句柄类型必须是被支持的，参见VkExternalImageFormatProperties 或者 VkExternalBufferProperties
	
	
	//VkExportMemoryAllocateInfoNV,功能和VkExportMemoryAllocateInfo类似
	//如果在VkMemoryAllocateInfo的pNext中包含一个,则该结构体表示该内存的payload可以导入到其他程序 或者Vulkan Instance使用
	VkExportMemoryAllocateInfoNV& exportMemoryAllocateInfoNV = memoryAllocateInfoEXT.exportMemoryAllocateInfoNV;
	exportMemoryAllocateInfoNV.handleTypes = VK_EXTERNAL_MEMORY_HANDLE_TYPE_OPAQUE_FD_BIT;//是VkExternalMemoryHandleTypeFlagBitsNV的一个或者多个位掩码组合，指定一个或多个可以导出的内存句柄类型。同一分配所需的多个handle type必须是兼容的，参见vkGetPhysicalDeviceExternalImageFormatPropertiesNV 中获取的参数


	VkDeviceMemory allocatedMemory;
	//win32 handle 导出导入memory操作
	HANDLE handle;
	{
		//VkExportMemoryWin32HandleInfoKHR
		//如果在VkMemoryAllocateInfo的pNext中包含一个(需要VkMemoryAllocateInfo的pNext中含有一个 handleTypes包含VK_EXTERNAL_MEMORY_HANDLE_TYPE_OPAQUE_WIN32_BIT的VkExportMemoryAllocateInfo 才有效,如果不包含则也不能包含该结构体 ),
		// 则该结构体表示指明从memory 对象中导出的NT handle的额外的其他属性
		VkExportMemoryWin32HandleInfoKHR& exportMemoryWin32HandleInfoKHR = memoryAllocateInfoEXT.exportMemoryWin32HandleInfoKHR;
		exportMemoryWin32HandleInfoKHR.name = L"name";//是一个以空结尾的UTF-16字符串，要与从创建的内存导出的NT handle引用的有效负载关联。
		exportMemoryWin32HandleInfoKHR.dwAccess;//是一个指定对该句柄的访问权限的DWORD。
		exportMemoryWin32HandleInfoKHR.pAttributes = nullptr;//是指向指定句柄安全属性的Windows SECURITY_ATTRIBUTES结构的指针。


		//VkImportMemoryWin32HandleInfoKHR
		//如果在VkMemoryAllocateInfo的pNext中包含,则表示引入一个windows handle的 内存
		//引入Windows handles中的payload 不会将payload的所有权转移给vulkan（只是引用并非转移），所以如果不需要了需要调用系统命令CloaseHandle来关闭
		VkImportMemoryWin32HandleInfoKHR& importMemoryWin32HandleInfoKHR = memoryAllocateInfoEXT.importMemoryWin32HandleInfoKHR;
		importMemoryWin32HandleInfoKHR.handle = nullptr;//为NULL或要导入的外部句柄。
		importMemoryWin32HandleInfoKHR.handleType = VK_EXTERNAL_MEMORY_HANDLE_TYPE_OPAQUE_WIN32_BIT;//是一个指定handle 或name的类型的VkExternalMemoryHandleTypeFlagBits值
		importMemoryWin32HandleInfoKHR.name = L"name";//为NULL或为要导入的以空字符串结尾的UTF-16 payload的名字。
		/*
		VkImportMemoryWin32HandleInfoKHR有效用法:
		1.如果handleType 不为0， 则（1）必须是支持引入的，参见VkExternalImageFormatProperties 或者 VkExternalBufferProperties
								   （2）其必须定义为 NT handle或者是global shader handle
								   （3）如果handle为NULL，则name 必须是一个指定的handleType的有效的memory 资源
								   （4）如果handle为NULL，则handle 必须是一个指定的handleType的有效的handle
		2.从handle中导出的或者是以name 命名的memory 必须和当前device是在同一个底层physical device上创建的
		3.如果handleType 不为VK_EXTERNAL_MEMORY_HANDLE_TYPE_OPAQUE_WIN32_BIT, VK_EXTERNAL_MEMORY_HANDLE_TYPE_D3D11_TEXTURE_BIT, VK_EXTERNAL_MEMORY_HANDLE_TYPE_D3D12_HEAP_BIT, 或者 VK_EXTERNAL_MEMORY_HANDLE_TYPE_D3D12_RESOURCE_BIT，则 name必须为NULL
		4.如果handle 不为0，则（1）name必须为NULL
							  （2）其必须遵守罗列在external memory handle types compatibility中的要求

		5.如果name 不为NULL，则其必须遵守罗列在external memory handle types compatibility中的要求
		*/


		//导出handle
		{
			//从一个vulkan device memory 对象中导出一个表示payload的 window handle，调用

			VkMemoryGetWin32HandleInfoKHR memoryGetWin32HandleInfoKHR;
			memoryGetWin32HandleInfoKHR.sType = VK_STRUCTURE_TYPE_MEMORY_GET_WIN32_HANDLE_INFO_KHR;
			memoryGetWin32HandleInfoKHR.pNext = nullptr;
			memoryGetWin32HandleInfoKHR.handleType = VK_EXTERNAL_MEMORY_HANDLE_TYPE_OPAQUE_WIN32_BIT;//是一个指定所请求的句柄类型的VkExternalMemoryHandleTypeFlagBits值。
			memoryGetWin32HandleInfoKHR.memory = allocatedMemory;//是即将从中导出句柄的memory 对象。
			/*
			VkMemoryGetWin32HandleInfoKHR有效用法:
			1.handleType 必须包含在memory 创建时的VkExportMemoryAllocateInfo::handleTypes中
			2.如果handleType 定义为一个 NT handle，则vkGetMemoryWin32HandleKHR 对于每一个单独的memory和 handleType的组合只能调用一次
			3.handleType 必须定义为一个 NT handle 或者 global share handle

			*/

			vkGetMemoryWin32HandleKHR(device, &memoryGetWin32HandleInfoKHR, &handle);
			//该结构获取的NT handle归属权属于 application， 如果不在需要也需要调用CloseHandle，得在接口中VkMemoryGetWin32HandleInfoKHR.memory对象分配后才能调用


			VkMemoryWin32HandlePropertiesKHR memoryWin32HandlePropertiesKHR{};
			memoryWin32HandlePropertiesKHR.sType = VK_STRUCTURE_TYPE_MEMORY_WIN32_HANDLE_PROPERTIES_KHR;
			memoryWin32HandlePropertiesKHR.pNext = nullptr;
			memoryWin32HandlePropertiesKHR.memoryTypeBits;//是一个比特掩码，对应每一个memory type （见VkPhysicalDeviceMemoryProperties.memoryTypes ??），指明 window handle可以被引入为的类型 .
			//和vulkan兼容的window handle可能是由非vulkan api创建的，为了正确使用这些handle可以查询其属性：
			vkGetMemoryWin32HandlePropertiesKHR(device, VK_EXTERNAL_MEMORY_HANDLE_TYPE_D3D11_TEXTURE_BIT, handle, &memoryWin32HandlePropertiesKHR);//handleType 不能是定义为opaque的 handle types



		}

		//VkExportMemoryWin32HandleInfoNV
		//如果在VkMemoryAllocateInfoNV的pNext中包含一个(需要VkMemoryAllocateInfoNV的pNext中含有一个 handleTypes包含VK_EXTERNAL_MEMORY_HANDLE_TYPE_OPAQUE_WIN32_BIT_NV的VkExportMemoryAllocateInfoNV 才有效,如果不包含则也不能包含该结构体 ),
		// 则该结构体表示为memory对象的external handle指定安全属性和访问权限
		VkExportMemoryWin32HandleInfoNV& exportMemoryWin32HandleInfoNV = memoryAllocateInfoEXT.exportMemoryWin32HandleInfoNV;
		exportMemoryWin32HandleInfoNV.dwAccess;//是一个指定对该句柄的访问权限的DWORD。
		exportMemoryWin32HandleInfoNV.pAttributes;//是指向指定句柄安全属性的Windows SECURITY_ATTRIBUTES结构的指针。


		//VkImportMemoryWin32HandleInfoNV
		//如果在VkMemoryAllocateInfoNV的pNext中包含一个,表示引入非当前Vulkan Instance但是底层的physical device是相同的instance创建的mmemory 
		VkImportMemoryWin32HandleInfoNV& importMemoryWin32HandleInfoNV = memoryAllocateInfoEXT.importMemoryWin32HandleInfoNV;
		importMemoryWin32HandleInfoNV.handle = handle;//是一个指内存的Windows句柄。必须是vkGetMemoryWin32HandleNV 指定相同handleType获取来的
		importMemoryWin32HandleInfoNV.handleType = VK_EXTERNAL_MEMORY_HANDLE_TYPE_OPAQUE_WIN32_BIT;/*是0或一个指定句柄中的内存句柄类型的VkExternalMemoryHandleTypeFlagBitsNV值。只能设置一个位
		VkExternalMemoryHandleTypeFlagBitsNV：
		VK_EXTERNAL_MEMORY_HANDLE_TYPE_OPAQUE_WIN32_KMT_BIT_NV: 指定这个memory的 handle是由 vkGetMemoryWin32HandleNV 返回的
		VK_EXTERNAL_MEMORY_HANDLE_TYPE_OPAQUE_WIN32_BIT_NV: 指定这个memory的 handle是由 vkGetMemoryWin32HandleNV 返回的 或者是用 DuplicateHandle() 复制的一个vkGetMemoryWin32HandleNV返回的 handle
		VK_EXTERNAL_MEMORY_HANDLE_TYPE_D3D11_IMAGE_BIT_NV:  指定这个memory的有效的NT handle是由 IDXGIResource1::CreateSharedHandle 返回的， 或者是用 DuplicateHandle() 复制的一个IDXGIResource1::CreateSharedHandle 返回的 handle
		VK_EXTERNAL_MEMORY_HANDLE_TYPE_D3D11_IMAGE_KMT_BIT_NV: 指定这个memory的 handle是由 IDXGIResource::GetSharedHandle() 返回的

		*/


		//获取handle NV
		{

			vkGetMemoryWin32HandleNV(device, allocatedMemory, VK_EXTERNAL_MEMORY_HANDLE_TYPE_OPAQUE_WIN32_KMT_BIT_NV, &handle);
			//在分配内存时，handleType必须是在VkExportMemoryAllocateInfoNV：：handleTypes中指定的标志，得在接口中memory对象分配后才能调用
		}
	
	
	
	
	
	}

	int fd;
	//POSIX file descriptor handle导出导入memory操作
	{
		//VkImportMemoryFdInfoKHR
		//如果在VkMemoryAllocateInfo的pNext中包含一个，表示从一个POSIX file descriptor handle中导入memory
		//从file descriptor 导入memory会将file descriptor 所有权从应用转移到vulkan，在成功导入后，应用程序不能对file descriptor执行任何操作，导入的memory 对象拥有其payload的引用，应用程序可以将相同的payload多次导入到Vulkan Instance中
		VkImportMemoryFdInfoKHR& importMemoryFdInfoKHR = memoryAllocateInfoEXT.importMemoryFdInfoKHR;
		importMemoryFdInfoKHR.fd = 0;//是要导入的外部句柄。
		importMemoryFdInfoKHR.handleType = VK_EXTERNAL_MEMORY_HANDLE_TYPE_OPAQUE_FD_BIT;//是一个指定fd的句柄类型的VkExternalMemoryHandleTypeFlagBits值。
		/*
		VkImportMemoryFdInfoKHR有效用法：
		1.如果handleType 不为0， 则（1）其必须是支持引入的，参见VkExternalImageFormatProperties 或者 VkExternalBufferProperties
								   （2）则其必须为VK_EXTERNAL_MEMORY_HANDLE_TYPE_OPAQUE_FD_BIT 或VK_EXTERNAL_MEMORY_HANDLE_TYPE_DMA_BUF_BIT_EXT
								   （3）fd必须是handleType 指定的有效的 handle

		2.从fd 中导出的的memory 必须和当前device是在同一个底层physical device上创建的
		3.fd 表示的memory 必须在和当前device以及 handleType兼容的相同底层physical device或者驱动上创建的，参见external memory handle types compatibility中的要求
		4.fd 必须遵守罗列在external memory handle types compatibility中的要求
		*/
	

		VkMemoryGetFdInfoKHR getMemoryFdInfoKHR{};
		getMemoryFdInfoKHR.sType = VK_STRUCTURE_TYPE_MEMORY_GET_FD_INFO_KHR;
		getMemoryFdInfoKHR.pNext = nullptr;
		getMemoryFdInfoKHR.handleType = VK_EXTERNAL_MEMORY_HANDLE_TYPE_OPAQUE_FD_BIT;//是一个指定所请求的句柄类型的VkExternalMemoryHandleTypeFlagBits值。
		getMemoryFdInfoKHR.memory = allocatedMemory;// 是将从中导出句柄的内存对象。
		/*
		VkMemoryGetFdInfoKHR有效用法：
		1.handleType 必须包含在创建memory的 VkExportMemoryAllocateInfo::handleTypes中
		2.handleType 必须为VK_EXTERNAL_MEMORY_HANDLE_TYPE_OPAQUE_FD_BIT 或 VK_EXTERNAL_MEMORY_HANDLE_TYPE_DMA_BUF_BIT_EXT
		*/


		//导出一个 引用到vulkan的memory 对象的payload的 POSIX file descriptor
		vkGetMemoryFdKHR(device, &getMemoryFdInfoKHR, &fd);
		//每次调用vkGetMemoryFdKHR都会创建一个新的引用到该memory的payload的file descriptor且将所有权交给应用程序，不再需要用的时候需要调用close（fd）,这个导入的内存大小可能会超过VkMemoryAllocateInfo::allocationSize.，如果handleType为 VK_EXTERNAL_MEMORY_HANDLE_TYPE_DMA_BUF_BIT_EXT,可以调用lseek查询外部文件大小
	


		VkMemoryFdPropertiesKHR memoryFdPropertiesKHR{};
		memoryFdPropertiesKHR.sType = VK_STRUCTURE_TYPE_MEMORY_FD_PROPERTIES_KHR;
		memoryFdPropertiesKHR.pNext = nullptr;
		memoryFdPropertiesKHR.memoryTypeBits;//是一个比特掩码，对应每一个memory type （见VkPhysicalDeviceMemoryProperties.memoryTypes ??），指明 POSIX file descriptor可以被引入为的类型 .
		//和vulkan兼容的POSIX file descriptor可能是由非vulkan api创建的，为了正确使用这些handle可以查询其属性：
		vkGetMemoryFdPropertiesKHR(device, VK_EXTERNAL_MEMORY_HANDLE_TYPE_DMA_BUF_BIT_EXT, fd, &memoryFdPropertiesKHR);//handleType 不能是定义为opaque的 handle types
		//handleType不能为VK_EXTERNAL_MEMORY_HANDLE_TYPE_OPAQUE_FD_BIT






	}



	void* hostPointer;
	//host memory
	{
		//VkImportMemoryHostPointerInfoEXT
		//如果在VkMemoryAllocateInfo的pNext中包含一个，表示从一个host pointer中导入memory
		//引入host pointer将在host和vulkan实现间共享memory 的所有权，应用程序任然可以通过host pointer访问该内存，只是需要应用程序进行device和 non-device的内存访问同步
		//host pointer可以多次导入到vulkan instance，但可能因为平台的限制而导致导入失败
		VkImportMemoryHostPointerInfoEXT& importMemoryHostPointerInfoEXT = memoryAllocateInfoEXT.importMemoryHostPointerInfoEXT;
		importMemoryHostPointerInfoEXT.handleType = VK_EXTERNAL_MEMORY_HANDLE_TYPE_HOST_ALLOCATION_BIT_EXT;//是一个指定句柄类型的VkExternalMemoryHandleTypeFlagBits值。
		importMemoryHostPointerInfoEXT.pHostPointer = nullptr;//是要从中导入memory 的host pointer
		/*
		VkImportMemoryHostPointerInfoEXT有效用法：
		1.如果handleType 不为0，则（1）其必须支持导入，参见VkExternalMemoryProperties
								  （2）其必须为VK_EXTERNAL_MEMORY_HANDLE_TYPE_HOST_ALLOCATION_BIT_EXT 或者 VK_EXTERNAL_MEMORY_HANDLE_TYPE_HOST_MAPPED_FOREIGN_MEMORY_BIT_EXT
		
		2.pHostPointer 所指必须对齐到整数倍的 VkPhysicalDeviceExternalMemoryHostPropertiesEXT::minImportedHostPointerAlignment
		3.如果handleType 为 VK_EXTERNAL_MEMORY_HANDLE_TYPE_HOST_ALLOCATION_BIT_EXT，pHostPointer必须是一个大小为VkMemoryAllocateInfo.allocationSize 的host memory的指针
		4.如果handleType为 VK_EXTERNAL_MEMORY_HANDLE_TYPE_HOST_MAPPED_FOREIGN_MEMORY_BIT_EXT，pHostPointer必须是一个大小为VkMemoryAllocateInfo.allocationSize 的host mapped foreign memory的指针

		*/



		VkMemoryHostPointerPropertiesEXT memoryHostPointerPropertiesEXT{};
		memoryHostPointerPropertiesEXT.sType = VK_STRUCTURE_TYPE_MEMORY_HOST_POINTER_PROPERTIES_EXT;
		memoryHostPointerPropertiesEXT.pNext = nullptr;
		memoryHostPointerPropertiesEXT.memoryTypeBits;//是一个比特掩码，对应每一个memory type （见VkPhysicalDeviceMemoryProperties.memoryTypes ??），指明 host pointer可以被引入为的类型 .只包含host 可见的memory type
		
		//为了导入host pointer时检查参数是否正确，可以调用函数查询属性
		vkGetMemoryHostPointerPropertiesEXT(device, VK_EXTERNAL_MEMORY_HANDLE_TYPE_HOST_MAPPED_FOREIGN_MEMORY_BIT_EXT, hostPointer, &memoryHostPointerPropertiesEXT);
		/*
		vkGetMemoryHostPointerPropertiesEXT有效用法:
		1.handleType 必须为VK_EXTERNAL_MEMORY_HANDLE_TYPE_HOST_ALLOCATION_BIT_EXT 或者 VK_EXTERNAL_MEMORY_HANDLE_TYPE_HOST_MAPPED_FOREIGN_MEMORY_BIT_EXT
		2.pHostPointer必须时有效的对齐到整数倍VkPhysicalDeviceExternalMemoryHostPropertiesEXT::minImportedHostPointerAlignment的指针
		3.如果handleType 为VK_EXTERNAL_MEMORY_HANDLE_TYPE_HOST_ALLOCATION_BIT_EXT，pHostPointer 必须是host memory的指针
		4.如果handleType 为VK_EXTERNAL_MEMORY_HANDLE_TYPE_HOST_MAPPED_FOREIGN_MEMORY_BIT_EXT，pHostPointer 必须是host mapped foreign memory的指针
		*/


	}
	
	AHardwareBuffer* androidBuffer;
	// android hardware buffer external memory
	{
		// VkImportAndroidHardwareBufferInfoANDROID
		//如果在VkMemoryAllocateInfo的pNext中包含一个，表示从一个vulkan instalce 外部的 android hardware buffer中导入memory
		VkImportAndroidHardwareBufferInfoANDROID& importAndroidHardwareBufferInfoANDROID = memoryAllocateInfoEXT.importAndroidHardwareBufferInfoANDROID;
		importAndroidHardwareBufferInfoANDROID.buffer = androidBuffer;//是要导入的android hardware buffer
		/*
		VkImportAndroidHardwareBufferInfoANDROID有效用法：
		1.如果 buffer不为 NULL，则（1） android hardware buffer必须支持导入，参见VkExternalImageFormatProperties 或者 VkExternalBufferProperties
								  （2）buffer必须为一个在Android Hardware Buffers中描述的 AHardwareBuffer_Desc::usage 和vulkan 兼容的对象

		*/
	

		VkMemoryGetAndroidHardwareBufferInfoANDROID memoryGetAndroidHardwareBufferInfoANDROID{};
		memoryGetAndroidHardwareBufferInfoANDROID.sType = VK_STRUCTURE_TYPE_MEMORY_GET_ANDROID_HARDWARE_BUFFER_INFO_ANDROID;
		memoryGetAndroidHardwareBufferInfoANDROID.pNext = nullptr;
		memoryGetAndroidHardwareBufferInfoANDROID.memory = allocatedMemory;//是将从中导出android hardware buffer的VkDeviceMemory对象。
		/*
		VkMemoryGetAndroidHardwareBufferInfoANDROID有效用法：
		1.当创建memory 的时候VkExportMemoryAllocateInfo::handleTypes 中必须包含VK_EXTERNAL_MEMORY_HANDLE_TYPE_ANDROID_HARDWARE_BUFFER_BIT_ANDROID 
		2.如果创建memory的时候VkMemoryAllocateInfo 的pNext中含有一个image不为NULL的 VkMemoryDedicatedAllocateInfo，则该image 必须已经绑定到该memory了

		*/




		//从vulkan object中导出一个引用其payload的 android hardware buffer调用：
		vkGetMemoryAndroidHardwareBufferANDROID(device, &memoryGetAndroidHardwareBufferInfoANDROID, &androidBuffer);
		//调用vkGetMemoryAndroidHardwareBufferANDROID将返回一个新的android hardware buffer 引用到 VkDeviceMemory.传入相同的VkMemoryGetAndroidHardwareBufferInfoANDROID.memory将返回相同的引用

		VkAndroidHardwareBufferPropertiesANDROID androidHardwareBufferPropertiesANDROID{};
		androidHardwareBufferPropertiesANDROID.sType = VK_STRUCTURE_TYPE_ANDROID_HARDWARE_BUFFER_PROPERTIES_ANDROID;
			//VkAndroidHardwareBufferPropertiesANDROID.pNext
			{
			VkAndroidHardwareBufferFormatProperties2ANDROID androidHardwareBufferFormatProperties2ANDROID{};
			androidHardwareBufferFormatProperties2ANDROID.sType = VK_STRUCTURE_TYPE_ANDROID_HARDWARE_BUFFER_FORMAT_PROPERTIES_2_ANDROID;
			androidHardwareBufferFormatProperties2ANDROID.pNext = nullptr;
			androidHardwareBufferFormatProperties2ANDROID.format;//是与android hardware buffer format对应的Vulkan format，如果没有等效的Vulkan format，则为VK_FORMAT_UNDEFINED。如果android hardware buffer 有一个format列举在 Format Equivalence table 中，则该值就为其对应format，否则为VK_FORMAT_UNDEFINED
			androidHardwareBufferFormatProperties2ANDROID.externalFormat;//是一个实现定义的外部格式标识符，用于VkExternalFormatANDROID。不能为零。
			androidHardwareBufferFormatProperties2ANDROID.formatFeatures;//描述了一个image 绑定到从buffer 中导入的memory时 该外部格式的能力。必须包含VK_FORMAT_FEATURE_SAMPLED_IMAGE_BIT以及至少包含 VK_FORMAT_FEATURE_MIDPOINT_CHROMA_SAMPLES_BIT 或 VK_FORMAT_FEATURE_COSITED_CHROMA_SAMPLES_BIT中的一个，应该包含VK_FORMAT_FEATURE_SAMPLED_IMAGE_FILTER_LINEAR_BIT 和 VK_FORMAT_FEATURE_SAMPLED_IMAGE_YCBCR_CONVERSION_LINEAR_FILTER_BIT.
			//该参数只是用来只是使用 android hardware buffer 来创建一个 外部给是的image时候的 有效特性
			androidHardwareBufferFormatProperties2ANDROID.samplerYcbcrConversionComponents;//应该用在VkSamplerYcbcrConversionCreateInfo中的component swizzle参数
			androidHardwareBufferFormatProperties2ANDROID.suggestedYcbcrModel;//用在VkSamplerYcbcrConversionCreateInfo中的一个建议的color model
			androidHardwareBufferFormatProperties2ANDROID.suggestedYcbcrRange;//是在VkSamplerYcbcrConversionCreateInfo.中使用的一个建议数值范围
			androidHardwareBufferFormatProperties2ANDROID.suggestedXChromaOffset;//是在VkSamplerYcbcrConversionCreateInfo.中使用的一个建议的 X chroma offset
			androidHardwareBufferFormatProperties2ANDROID.suggestedYChromaOffset;//是在VkSamplerYcbcrConversionCreateInfo.中使用的一个建议的 Y chroma offset
			
			}
		androidHardwareBufferPropertiesANDROID.pNext = nullptr;//可以为NULL或者包含一个 有效的VkAndroidHardwareBufferFormatProperties2ANDROID, VkAndroidHardwareBufferFormatPropertiesANDROID, 或者VkAndroidHardwareBufferFormatResolvePropertiesANDROID
		androidHardwareBufferPropertiesANDROID.allocationSize;//为外部memory的大小
		androidHardwareBufferPropertiesANDROID.memoryTypeBits;//是一个比特掩码，对应每一个memory type （见VkPhysicalDeviceMemoryProperties.memoryTypes ??），指明 android hardware buffer可以被引入为的类型 .
		//为了导入android hardware buffer时检查参数是否正确，可以调用函数查询属性
		vkGetAndroidHardwareBufferPropertiesANDROID(device, androidBuffer, &androidHardwareBufferPropertiesANDROID);
		//buffer 必须是一个在其AHardwareBuffer_Desc::usage至少包含一个AHARDWAREBUFFER_USAGE_GPU_* flags的有效的 android hardware buffer




	}






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