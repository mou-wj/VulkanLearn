#include "MemoryAllocationTest.h"
#include <Windows.h>
#include <vulkan/vulkan_win32.h>
#include <winnt.h>
#include <vulkan/vulkan_metal.h>
#include <vulkan/vulkan_android.h>
typedef uint32_t zx_handle_t;//��Ϊzx_handle_t ��google�Ŀ�Դ����ϵͳfuchsia�ľ�����ͣ��������ﶨ��һ��uint32_t���͵ľ������zx_handle_t������ʵ������ֻ��Ϊ��ͨ������
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
		
    VK_SYSTEM_ALLOCATION_SCOPE_COMMAND: ָ�����������������Ϊvulkan command�ĳ����ڼ�
    VK_SYSTEM_ALLOCATION_SCOPE_OBJECT:  ָ�����������������Ϊ���ڱ��������ʹ�õ�vulkan objects��������������
    VK_SYSTEM_ALLOCATION_SCOPE_CACHE:   ָ�����������������ΪVkPipelineCache ���� VkValidationCacheEXT����������
    VK_SYSTEM_ALLOCATION_SCOPE_DEVICE:   ָ�����������������ΪVulkan Device����������
    VK_SYSTEM_ALLOCATION_SCOPE_INSTANCE:  ָ�����������������ΪVulkan Instance����������

	*/


	using VkInternalAllocationTypeWithNotation = VkInternalAllocationType;/*
	VK_INTERNAL_ALLOCATION_TYPE_EXECUTABLE:   ָ�����������host ��ִ��
	*/


	//һЩ�����õ���Щ�ڴ���������ĳ�����p886

	void* CustomAlloc(
		void* pUserData,//����ʱ���� VkAllocationCallbacks.pUserData
		size_t                                      size,//������Ҫ������ڴ��С
		size_t                                      alignment,//��Ҫ���ڴ������ֽ�����С��������2����
		VkSystemAllocationScope                     allocationScope //��һ��VkSystemAllocationScopeֵ��ָ�������������ڵķ��䷶Χ��
	) {
		//���ﶨ���Զ�����ڴ�������
		return nullptr;
	}

	void* CustomRealloc(
		void* pUserData,//����ʱ���� VkAllocationCallbacks.pUserData
		void* pOriginal,//������NULL��֮ǰ�ɼ��ݷ������� pfnReallocation ���� pfnAllocation���ص��ڴ�ָ�롣���ΪNULL����ͬ�ڵ���һ��PFN_vkAllocationFunction
		size_t                                      size,//������Ҫ������ڴ��С�����Ϊ0����ͬ�ڵ��� PFN_vkFreeFunction
		size_t                                      alignment,//��Ҫ���ڴ������ֽ�����С��������2���ݣ��ұ���� pOriginal����ʱ��alignment ��ͬ
		VkSystemAllocationScope                     allocationScope //��һ��VkSystemAllocationScopeֵ��ָ�������������ڵķ��䷶Χ��
	) {
		//���ﶨ���Զ�����ڴ����·������
		return nullptr;
	}
	void CustomFree(
		void* pUserData,//����ʱ���� VkAllocationCallbacks.pUserData
		void* pMemory//��Ҫ���ͷŵ��ڴ�ָ��
	) {
		//���ﶨ���Զ�����ڴ��ͷŲ���
	}

	void CustomInternalAlloc(
		void* pUserData,//����ʱ���� VkAllocationCallbacks.pUserData
		size_t                                      size,//������Ҫ������ڴ��С
		VkInternalAllocationType                    allocationType,//��VkInternalAllocationType ֵ��ָ������ķ������͡�
		VkSystemAllocationScope                     allocationScope//��һ��VkSystemAllocationScopeֵ��ָ�������������ڵķ��䷶Χ��
	) {
		//���ﶨ���Զ�����ڲ��ڴ�������
	
	}

	void CustomInternalFree(
		void* pUserData,//����ʱ���� VkAllocationCallbacks.pUserData
		size_t                                      size,//������Ҫ������ڴ��С
		VkInternalAllocationType                    allocationType,//��VkInternalAllocationType ֵ��ָ������ķ������͡�
		VkSystemAllocationScope                     allocationScope//��һ��VkSystemAllocationScopeֵ��ָ�������������ڵķ��䷶Χ��
	) {
		//���ﶨ���Զ�����ڲ��ڴ��ͷŲ���

	}

}
void MemoryAllocationTest::HostAllocationCallbacksTest()
{


	VkAllocationCallbacks callbacks;
	callbacks.pUserData = nullptr;//��һ��Ҫͨ���ص���ʵ�������͵�ֵ��������VkAllocationCallbacks�е��κ�һ���ص�������ʱ��Vulkanʵ�ֽ������ֵ��Ϊ��һ���������ݸ��ûص�������ÿ�ν����������ݵ�����ʱ����ֵ���ᷢ���仯����ʹ��ͬһ�����ڶ�������н��ܷ�����ʱҲ����ˡ�
	callbacks.pfnAllocation = &CustomMemoryFunc::CustomAlloc;//��һ��ָ��Ӧ�ó�������ڴ���亯����PFN_vkAllocationFunctionָ�롣
	callbacks.pfnFree = &CustomMemoryFunc::CustomFree;//��һ��ָ��Ӧ�ó�������ͷ��ڴ溯����PFN_vkFreeFunctionָ�롣
	callbacks.pfnReallocation = &CustomMemoryFunc::CustomRealloc;//��һ��ָ��Ӧ�ó�������ڴ����·��亯����PFN_vkReallocationFunctionָ�롣
	callbacks.pfnInternalAllocation = VK_NULL_HANDLE;//��һ��ָ��Ӧ�ó����庯����PFN_vkInternalAllocationNotificationָ�룬ʵ���ڽ����ڲ�����ʱ���øú�����
	callbacks.pfnInternalFree = VK_NULL_HANDLE;//��һ��ָ��Ӧ�ó����庯����PFN_vkInternalFreeNotificationָ�룬��ʵ���ͷ��ڲ�����ʱ��ʵ�ֻ���øú�����
	/*
	VkAllocationCallbacks��Ч�÷���
	1.pfnAllocation������һ����Ч���û������ PFN_vkAllocationFunction ָ��
	2.pfnReallocation������һ����Ч���û������ PFN_vkReallocationFunction ָ��
	3.pfnFree������һ����Ч���û������ PFN_vkFreeFunction ָ��
	4.pfnInternalAllocation �Լ� pfnInternalFree ����ͬʱΪNULL ����ͬʱ����Ч��ָ��
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
		//����ֻ��ʾ������һЩ�ṹ���ǲ��ܹ�ͬʱ���ӵ�һ�����ӵ�VkMemoryAllocateInfo��pNext�е�
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

	//�����豸���ڴ������������ڴ�ѺͿ��õ��ڴ����͡�
	//��ѯ�ڴ�����
	VkPhysicalDeviceMemoryProperties deviceMemoryProps;
	deviceMemoryProps.memoryHeapCount; //memoryHeaps�е���Ч���͸���
	deviceMemoryProps.memoryHeaps;//��һ��VK_MAX_MEMORY_HEAPS �� VkMemoryHeap �ṹ�����飬�������Է����ڴ���ڴ��
	deviceMemoryProps.memoryTypeCount;//memoryTypes�е���Ч���͸���
	deviceMemoryProps.memoryTypes;//��һ��VK_MAX_MEMORY_TYPES �� VkMemoryType �ṹ�����飬�����˿����ڷ��ʴ��ڴ��ָ���Ķ��з�����ڴ����͵��ڴ����͡�����VkMemoryPropertyFlags���Ӽ�����ģ������һ��VkMemoryPropertyFlagsΪ��һ��VkMemoryPropertyFlags���Ӽ���������С
	vkGetPhysicalDeviceMemoryProperties(physicalDevice, &deviceMemoryProps);

	//VkMemoryHeap
	VkMemoryHeap& tmpMemoryHeap = deviceMemoryProps.memoryHeaps[0];
	tmpMemoryHeap.size;//ָ����ǰ�ѵĴ�С
	tmpMemoryHeap.flags;/*ָ���ѵ�����
	VK_MEMORY_HEAP_DEVICE_LOCAL_BIT: ָ���öѶ�Ӧ��device-local ���ڴ棬device-local �ڴ������host-local�ڴ��ɲ�ͬ���������ԣ��ܹ�֧�ֲ�ͬ���ڴ�����
	VK_MEMORY_HEAP_MULTI_INSTANCE_BIT: ָ���������һ���߼�device���ұ�ʾ���physical device�Ķ��ڴ棬ÿ��physical device�ж�����ôһ���ѣ�������ôһ���ѻᵼ��ÿ��physical device�϶��������ôһ����

	*/

	//VkMemoryType
	VkMemoryType& tmpMemoryType = deviceMemoryProps.memoryTypes[0];
	tmpMemoryType.heapIndex;//ָ������ڴ�������memoryHeaps������Ӧ�Ķ�����
	tmpMemoryType.propertyFlags;/*��VkMemoryPropertyFlagBits�����ֵ��ָ���ڴ����ԣ�
		VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT: ָ������������͵��ڴ�������Ч���豸�����ڴ档���ҽ����ڴ��������ھ���VK_MEMORY_HEAP_DEVICE_LOCAL_BIT���Ķ�ʱ���Ž����ô����ԡ�
		VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT: ָ������ʹ��vkMapMemoryӳ�����������͵��ڴ��Խ�����������
		VK_MEMORY_PROPERTY_HOST_COHERENT_BIT: ָ������ҪvkFlushMappedMemoryRanges��vkInvalidateMappedMemoryRanges�����˻������������ˢ�������Ļ���д�뵽�豸��ʹ�豸д��������ɼ���
		VK_MEMORY_PROPERTY_HOST_CACHED_BIT: ָ��������������͵��ڴ滺���������ϡ������ڴ��δ�����ڴ�ķ��ʱȻ����ڴ���������δ������ڴ���������һ�µġ�
		VK_MEMORY_PROPERTY_LAZILY_ALLOCATED_BIT: ָ�����ڴ����ͽ������豸���ʸ��ڴ档�ڴ����Ͳ���ͬʱ������VK_MEMORY_PROPERTY_LAZILY_ALLOCATED_BIT��VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT�����⣬�����֧���ڴ������ Lazily Allocated Memory ��ָ����ʵ���ӳٵ��ṩ��
		VK_MEMORY_PROPERTY_PROTECTED_BIT: ָ���ڴ����ͽ������豸�����ڴ棬�������ܱ����Ķ��в��������ڴ档�ڴ����Ͳ���Ϊ��VK_MEMORY_PROPERTY_PROTECTED_BIT���κ�VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT��VK_MEMORY_PROPERTY_HOST_COHERENT_BIT��VK_MEMORY_PROPERTY_HOST_CACHED_BIT����ϡ�
		VK_MEMORY_PROPERTY_DEVICE_COHERENT_BIT_AMD: ָ���豸�Դ��ڴ����ͷ���ķ��ʽ��Զ��ṩ���úͿɼ�
		VK_MEMORY_PROPERTY_DEVICE_UNCACHED_BIT_AMD: ָ�����豸�϶Դ����͵��ڴ���䲻���л��档δ������豸�ڴ��������豸��һ�µġ�
		VK_MEMORY_PROPERTY_RDMA_CAPABLE_BIT_NV: ָ���ⲿ�豸����ֱ�ӷ��ʴ��ڴ�

	propertyFlags����Ч���ֵ��
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

	//��ѯ�ڴ�����2��ֻ�Ǳ�VkPhysicalDeviceMemoryProperties����Щ��չ��Ϣ
	VkPhysicalDeviceMemoryProperties2 deviceMemoryProps2;
	deviceMemoryProps2.memoryProperties;//��һ�� VkPhysicalDeviceMemoryProperties ���ݽṹ��
	deviceMemoryProps2.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MEMORY_PROPERTIES_2;
		VkPhysicalDeviceMemoryBudgetPropertiesEXT deviceMemoryBudgetPropsEXT;
		deviceMemoryBudgetPropsEXT.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MEMORY_BUDGET_PROPERTIES_EXT;
		deviceMemoryBudgetPropsEXT.pNext = nullptr;
		deviceMemoryBudgetPropsEXT.heapBudget;//��һ��VK_MAX_MEMORY_HEAPS�� VkDeviceSizeֵ�����飬���з����ڴ�Ԥ�㣬��Ӧÿһ���ѡ��ѵ�Ԥ�����ڷ������ʧ�ܻ��������½�֮ǰ���̿��ԴӶѷ�������ڴ�Ĵ��Թ��ơ���Ԥ�������ǰ������κ��豸�ڴ�
		deviceMemoryBudgetPropsEXT.heapUsage;//��һ��VK_MAX_MEMORY_HEAPS�� VkDeviceSizeֵ�����飬���з����ڴ��ʹ��������Ӧÿһ���ѡ��ѵ�ʹ�����ǶԽ��̵�ǰ�ڸö���ʹ�õ��ڴ����Ĺ��ơ�
	deviceMemoryProps2.pNext = &deviceMemoryBudgetPropsEXT;//������԰���һ�� VkPhysicalDeviceMemoryBudgetPropertiesEXT
	vkGetPhysicalDeviceMemoryProperties2(physicalDevice, &deviceMemoryProps2);
	


	//�����ڴ�
	VkDeviceMemory deviceMemory{VK_NULL_HANDLE};
	VkMemoryAllocateInfo memoryAllocateInfo{};
	memoryAllocateInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
		MemoryAllocateInfoEXT memoryAllocateInfoEXT{};
	memoryAllocateInfo.pNext = &memoryAllocateInfoEXT.dedicatedAllocationMemoryAllocateInfoNV;
	memoryAllocateInfo.allocationSize = 1;//ֻ��Ҫ������ڴ���ֽ���
	memoryAllocateInfo.memoryTypeIndex = 0;//�Ǵ�vkGetPhysicalDeviceMemoryProperties��ȡ��VkPhysicalDeviceMemoryProperties�ṹ��memoryTypes�����е��ڴ����͵�������
	/*
	VkMemoryAllocateInfo��Ч�÷���
	1.�������û��ָ��һ��import ��export operation����allocationSize �������0
	2.��������ָ�����import ����
	3.�������������һ��export operation,��handleType����VK_EXTERNAL_MEMORY_HANDLE_TYPE_ANDROID_HARDWARE_BUFFER_BIT_ANDROID����allocationSize�������0
	4.�������������һ������VkBufferCollectionFUCHSIA��import operation,��1�����VkMemoryDedicatedAllocateInfo::bufferδ��NULL��ֵ��VkImportMemoryBufferCollectionFUCHSIA::collection �Լ�VkImportMemoryBufferCollectionFUCHSIA::index �������ƥ��ʹ���VkMemoryDedicatedAllocateInfo::buffer��VkBufferCollectionBufferCreateInfoFUCHSIA�ṹ���е� VkBufferCollectionBufferCreateInfoFUCHSIA::collection ��VkBufferCollectionBufferCreateInfoFUCHSIA::index
																		  ��2�����VkMemoryDedicatedAllocateInfo::imageδ��NULL��ֵ��VkImportMemoryBufferCollectionFUCHSIA::collection �Լ�VkImportMemoryBufferCollectionFUCHSIA::index �������ƥ��ʹ���VkMemoryDedicatedAllocateInfo::image��VkBufferCollectionBufferCreateInfoFUCHSIA�ṹ���е� VkBufferCollectionBufferCreateInfoFUCHSIA::collection ��VkBufferCollectionBufferCreateInfoFUCHSIA::index
																		  ��3����allocationSize�����vkGetImageMemoryRequirements����vkGetBufferMemoryRequirements���û�ȡ��image-based ��buffer-based collections��VkMemoryRequirements::size��ƥ�䡣
																		  ��4����pNext�б������һ����image ���� buffer ����ΪVK_NULL_HANDLE��VkMemoryDedicatedAllocateInfo�ṹ��
																		  ��5�����pNext�а���VkMemoryDedicatedAllocateInfo�ṹ�壬��VkMemoryDedicatedAllocateInfo::image����ʱ������VkImageCreateInfo::pNext�а���һ��VkBufferCollectionImageCreateInfoFUCHSIA�ṹ�壬
																		  ��6�����pNext�а���VkMemoryDedicatedAllocateInfo�ṹ�壬��VkMemoryDedicatedAllocateInfo::buffer����ʱ������VkBufferCreateInfo::pNext�а���һ��VkBufferCollectionImageCreateInfoFUCHSIA�ṹ�壬
																		  ��7����memoryTypeIndex �����Ǵ�vkGetBufferCollectionPropertiesFUCHSIA ���û�ȡ��VkBufferCollectionPropertiesFUCHSIA�Ķ�Ӧ�ڴ�����������
	5.���pNext �а�����һ��VkExportMemoryAllocateInfo����1�������image���� buffer��ΪVK_NULL_HANDLE �����κ�VkExportMemoryAllocateInfo::handleTypes ָ����handle type ��Ҫ��ռ���䣬�Ƿ��ռ�����image����ͨ��vkGetPhysicalDeviceImageFormatProperties2���÷��ص�VkExternalImageFormatProperties::externalMemoryProperties.externalMemoryFeatures ���߶���buffer��ͨ������vkGetPhysicalDeviceExternalBufferProperties��ȡ�� VkExternalBufferProperties::externalMemoryProperties.externalMemoryFeatures �н��г��֣���pNext�б������һ��VkMemoryDedicatedAllocateInfo ����VkDedicatedAllocationMemoryAllocateInfoNV
														  ��2��pNext�оͲ����ٰ���һ�� VkExportMemoryAllocateInfoNV ���� VkExportMemoryWin32HandleInfoNV
	6.���pNext �а�����һ��VkImportMemoryWin32HandleInfoKHR�� ��pNext�Ͳ��ܰ��� VkImportMemoryWin32HandleInfoNV

	7.�������������һ��import operation,��external handle ��ͨ��Vulkan API�����ģ���1�������external handle������ΪVK_EXTERNAL_MEMORY_HANDLE_TYPE_OPAQUE_FD_BIT����allocationSize ��memoryTypeIndex �ͱ���ͱ������payload����ʱָ���Ĳ�����ƥ�䡣
																					 ��2��VkMemoryAllocateFlagsInfoָ���� device mask����ͱ������payload����ʱָ���Ĳ�����ƥ�䡣
																					 ��3���򴫸�vkAllocateMemory�� �߼��豸�� physical devices�б����ͱ������payload����ʱ�����physical devices�б���ƥ�䡣
																					 ��4�����external handle������ΪVK_EXTERNAL_MEMORY_HANDLE_TYPE_OPAQUE_WIN32_BIT ����VK_EXTERNAL_MEMORY_HANDLE_TYPE_OPAQUE_WIN32_KMT_BIT�� ��allocationSize ��memoryTypeIndex �ͱ���ͱ������payload����ʱָ���Ĳ�����ƥ�䡣
	8.�������������һ��import operation����external handle ΪVulkan API�ⲿ���� NT handle ����һ����global share handle����memoryTypeIndex ������vkGetMemoryWin32HandlePropertiesKHR ������Ϣ�ж�Ӧ�����е�һ��������																
	9.�������������һ��import operation����external handle ����ΪVK_EXTERNAL_MEMORY_HANDLE_TYPE_D3D12_HEAP_BIT����allocationSize ����ʹӱ���ȡ����payload�д���Direct3D 12 heap payloadʱָ���Ĳ�����ƥ�䡣
	10.�������������һ��import operation����external handle ��һ��Vulkan API�ⴴ����POSIX file descriptor����memoryTypeIndex ������vkGetMemoryFdPropertiesKHR ������Ϣ�ж�Ӧ�����е�һ��������
	11.���protectedMemory ����û�п�������VkMemoryAllocateInfo::memoryTypeIndex ����ָ��һ����VK_MEMORY_PROPERTY_PROTECTED_BIT ���͵��ڴ�����
	12.�������������һ��import operation����external handle Ϊһ��host pointer�� ��1��memoryTypeIndex ������vkGetMemoryHostPointerPropertiesEXT ������Ϣ�ж�Ӧ�����е�һ��������
																					��2��allocationSize ������һ����������VkPhysicalDeviceExternalMemoryHostPropertiesEXT::minImportedHostPointerAlignment
																					��3��pNext�в��ܰ���һ����image ���� buffer ����ΪVK_NULL_HANDLE��VkDedicatedAllocationMemoryAllocateInfoNV�ṹ��
																					��4��pNext�в��ܰ���һ����image ���� buffer ����ΪVK_NULL_HANDLE��VkMemoryDedicatedAllocateInfo�ṹ��
	13.�������������һ�� import operation����external handle ����ΪVK_EXTERNAL_MEMORY_HANDLE_TYPE_ANDROID_HARDWARE_BUFFER_BIT_ANDROID	����1������Android hardware buffer��allocationSize�����Ǵ�vkGetAndroidHardwareBufferPropertiesANDROID �з��ص�ֵ																	
																																			��2�����pNext�в�����һ��VkMemoryDedicatedAllocateInfo ����VkMemoryDedicatedAllocateInfo::imageΪVK_NULL_HANDLE��Android hardware buffer �ͱ�����AHardwareBuffer_Desc::formatΪAHARDWAREBUFFER_FORMAT_BLOB �Լ�AHardwareBuffer_Desc::usage ����AHARDWAREBUFFER_USAGE_GPU_DATA_BUFFER
																																			��3������Android hardware buffer�� memoryTypeIndex �����Ǵ�vkGetAndroidHardwareBufferPropertiesANDROID ���صĲ���������Ӧ�����ĵ�����
	14.�������û��ָ��һ��import operation����pNext �а���һ��handleTypes����VK_EXTERNAL_MEMORY_HANDLE_TYPE_ANDROID_HARDWARE_BUFFER_BIT_ANDROID�� VkExportMemoryAllocateInfo����pNext�а���һ��image ��ΪVK_NULL_HANDLE��VkMemoryDedicatedAllocateInfo����allocationSize ������0
	15.�������������һ��export operation����handle����ΪVK_EXTERNAL_MEMORY_HANDLE_TYPE_ANDROID_HARDWARE_BUFFER_BIT_ANDROID����1�����pNext�в���VkMemoryDedicatedAllocateInfo����allocationSize ������� 0
																															   ��2�����pNext�а���һ��bufferΪ��Чֵ��VkMemoryDedicatedAllocateInfo����allocationSize �������0

	16.�������������һ��import operation����external handle ��һ��Android hardware buffer����pNext�а���һ��image ��ΪVK_NULL_HANDLE��VkMemoryDedicatedAllocateInfo����1��Android hardware buffer��AHardwareBuffer::usage ����Ҫ����AHARDWAREBUFFER_USAGE_GPU_FRAMEBUFFER, AHARDWAREBUFFER_USAGE_GPU_SAMPLED_IMAGE ���� AHARDWAREBUFFER_USAGE_GPU_DATA_BUFFER ����һ��
																																									    ��2������Android hardware buffer�� image��format����ΪVK_FORMAT_UNDEFINED ����ͨ��vkGetAndroidHardwareBufferPropertiesANDROID���ص�VkAndroidHardwareBufferFormatPropertiesANDROID::format
																																									    ��3��image��width, height, �Լ� array layer ά������� Android hardware buffer��s AHardwareBuffer_Desc�еĶ�Ӧ������ͬ
																																									    ��4�����Android hardware buffer�� AHardwareBuffer::usage ����AHARDWAREBUFFER_USAGE_GPU_MIPMAP_COMPLETE ����image������һ����ɵ�mipmap������mipmapһֱ��width��height��Ϊ1 ����
																																									    ��5�����Android hardware buffe�� AHardwareBuffer::usage������AHARDWAREBUFFER_USAGE_GPU_MIPMAP_COMPLETE����iamge����ֻ��һ��mipmap����
																																									    ��6��ÿһ������Ϊimage ��usage�ı���λ����������AHardwareBuffer Usage Equivalence �У����û���ڸ��б��У���ñ���λ���������Android hardware buffer�� AHardwareBuffer_Desc::usage ��

	17.�������������һ��import operation����external handle ����ΪVK_EXTERNAL_MEMORY_HANDLE_TYPE_SCREEN_BUFFER_BIT_QNX����1�� VkPhysicalDeviceExternalMemoryScreenBufferFeaturesQNX::screenBufferImport���뿪��
																														   ��2��allocationSize ������ΪQNX Screen buffer���� vkGetScreenBufferPropertiesQNX ���صĴ�С
																														   ��3��memoryTypeIndex ������ΪQNX Screen buffer���� vkGetScreenBufferPropertiesQNX ���صĲ���������Ӧ�����ĵ�һ������
	18.�������������һ��import operation����external handle Ϊһ��QNX Screen buffer����pNext�а���һ��image ��ΪVK_NULL_HANDLE��VkMemoryDedicatedAllocateInfo����1��QNX Screen��s buffer������һ����Ч��QNX Screen buffer
																																								  ��2��image��format����ΪVK_FORMAT_UNDEFINED ����Ϊ QNX Screen buffer ͨ��vkGetScreenBufferPropertiesQNX���ص�VkScreenBufferFormatPropertiesQNX::format
																																								  ��3��image��width, height, �Լ� array layer ά������� QNX Screen buffer�� _screen_buffer�еĶ�Ӧ������ͬ
	19.���VkMemoryOpaqueCaptureAddressAllocateInfo::opaqueCaptureAddress ��Ϊ 0��VkMemoryAllocateFlagsInfo::flags�������VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_CAPTURE_REPLAY_BIT
	20.���VkMemoryAllocateFlagsInfo::flags����VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_CAPTURE_REPLAY_BIT����bufferDeviceAddressCaptureReplay ���Ա��뿪��
	21.���VkMemoryAllocateFlagsInfo::flags����VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT����bufferDeviceAddress ���Ա��뿪��
	22.���pNext�а���VkImportMemoryHostPointerInfoEXT����VkMemoryOpaqueCaptureAddressAllocateInfo::opaqueCaptureAddress ����Ϊ 0
	23.�������������һ��import operation��VkMemoryOpaqueCaptureAddressAllocateInfo::opaqueCaptureAddress ����Ϊ 0
	24.�������������һ��import operation����external handle ����ΪVK_EXTERNAL_MEMORY_HANDLE_TYPE_ZIRCON_VMO_BIT_FUCHSIA����1��memoryTypeIndex ������vkGetMemoryZirconHandlePropertiesFUCHSIA ������ϢVkMemoryZirconHandlePropertiesFUCHSIA �ж�Ӧ����memoryTypeBits �е�һ��������
																															��2��allocationSize ������� 0 ��С�ڵ���ͨ��zx_vmo_get_size(handle)��ȡ��VMO��С������handleΪ�����ⲿ�ڴ��VMO handle
	25.���pNext�а���һ��VkExportMetalObjectCreateInfoEXT�� ��ýṹ���exportObjectType����ΪVK_EXPORT_METAL_OBJECT_TYPE_METAL_BUFFER_BIT_EXT



	*/
	
	



	//VkMemoryDedicatedAllocateInfo  
	//�����VkMemoryAllocateInfo��pNext�а�������ýṹ����뺬��һ���������ڴ����󶨵�buffer����image ����ָ��
	VkMemoryDedicatedAllocateInfo& memoryDedicatedAllocateInfo = memoryAllocateInfoEXT.memoryDedicatedAllocateInfo;
	memoryDedicatedAllocateInfo.buffer = VK_NULL_HANDLE; //��VK_NULL_HANDLE����ڴ潫���󶨵���VkBuffer�ľ����
	memoryDedicatedAllocateInfo.image = VK_NULL_HANDLE;//��VK_NULL_HANDLE����ڴ潫���󶨵���VkImage�ľ����
	/*
	VkMemoryDedicatedAllocateInfo��Ч�÷�:
	1.image ��buffer ����һ��ΪVK_NULL_HANDLE
	2.��� image ��ΪVK_NULL_HANDLE ��1�����memory ����һ������� Android Hardware Buffer����QNX Screen buffer ,��VkMemoryAllocateInfo::allocationSize ������� image�� VkMemoryRequirements::size
						              ��2��image����ʱ���VkImageCreateInfo::flags ���ܺ��� VK_IMAGE_CREATE_SPARSE_BINDING_BIT��VK_IMAGE_CREATE_DISJOINT_BIT
									  ��3�����VkMemoryAllocateInfo������һ��memory import operation������handle����Ϊ VK_EXTERNAL_MEMORY_HANDLE_TYPE_OPAQUE_WIN32_BIT, VK_EXTERNAL_MEMORY_HANDLE_TYPE_OPAQUE_WIN32_KMT_BIT, VK_EXTERNAL_MEMORY_HANDLE_TYPE_D3D11_TEXTURE_BIT, VK_EXTERNAL_MEMORY_HANDLE_TYPE_D3D11_TEXTURE_KMT_BIT, VK_EXTERNAL_MEMORY_HANDLE_TYPE_D3D12_HEAP_BIT, 
									  		    ���� VK_EXTERNAL_MEMORY_HANDLE_TYPE_D3D12_RESOURCE_BIT���Ҹ��ⲿhandle����Vulkan API�����ģ�������� memory������һ�� dedicated image����ģ������ڴ�ֻ��image��ӵ�У�����imageҪ�͸�memory ��������VkImage��ͬ
									  ��4�����VkMemoryAllocateInfo������һ��memory import operation������handle����Ϊ VK_EXTERNAL_MEMORY_HANDLE_TYPE_OPAQUE_FD_BIT ��VK_EXTERNAL_MEMORY_HANDLE_TYPE_ZIRCON_VMO_BIT_FUCHSIA��������� memory������һ�� dedicated image����ģ������ڴ�ֻ��image��ӵ�У�����imageҪ�͸�memory ��������VkImage��ͬ

	3.��� buffer ��ΪVK_NULL_HANDLE ��1�����memory ����һ������� Android Hardware Buffer����QNX Screen buffer ,��VkMemoryAllocateInfo::allocationSize ������� buffer �� VkMemoryRequirements::size
									   ��2��buffer ����ʱ���VkBufferCreateInfo::flags ���ܺ��� VK_BUFFER_CREATE_SPARSE_BINDING_BIT
									   ��3�����VkMemoryAllocateInfo������һ��memory import operation������handle����Ϊ VK_EXTERNAL_MEMORY_HANDLE_TYPE_OPAQUE_WIN32_BIT, VK_EXTERNAL_MEMORY_HANDLE_TYPE_OPAQUE_WIN32_KMT_BIT, VK_EXTERNAL_MEMORY_HANDLE_TYPE_D3D11_TEXTURE_BIT, VK_EXTERNAL_MEMORY_HANDLE_TYPE_D3D11_TEXTURE_KMT_BIT, VK_EXTERNAL_MEMORY_HANDLE_TYPE_D3D12_HEAP_BIT,
												���� VK_EXTERNAL_MEMORY_HANDLE_TYPE_D3D12_RESOURCE_BIT���Ҹ��ⲿhandle����Vulkan API�����ģ�������� memory������һ�� dedicated buffer����ģ������ڴ�ֻ��buffer ��ӵ�У�����bufferҪ�͸�memory ��������VkBuffer��ͬ
									   ��4�����VkMemoryAllocateInfo������һ��memory import operation������handle����Ϊ VK_EXTERNAL_MEMORY_HANDLE_TYPE_OPAQUE_FD_BIT ��VK_EXTERNAL_MEMORY_HANDLE_TYPE_ZIRCON_VMO_BIT_FUCHSIA��������� memory������һ�� dedicated buffer����ģ������ڴ�ֻ��buffer ��ӵ�У�����bufferҪ�͸�memory ��������VkBuffer��ͬ

	*/


	// VkDedicatedAllocationMemoryAllocateInfoNV,���ܺ�VkMemoryDedicatedAllocateInfo ����
	//�����VkMemoryAllocateInfo��pNext�а�������ýṹ����뺬��һ���������ڴ����󶨵�buffer����image ����ָ��
	VkDedicatedAllocationMemoryAllocateInfoNV& memoryDedicatedAllocateInfoNV = memoryAllocateInfoEXT.dedicatedAllocationMemoryAllocateInfoNV;
	memoryDedicatedAllocateInfo.buffer = VK_NULL_HANDLE; //��VK_NULL_HANDLE����ڴ潫���󶨵���VkBuffer�ľ����
	memoryDedicatedAllocateInfo.image = VK_NULL_HANDLE;//��VK_NULL_HANDLE����ڴ潫���󶨵���VkImage�ľ����
	/*
	VkDedicatedAllocationMemoryAllocateInfoNV��Ч�÷���
	1.image ��buffer ����һ��ΪVK_NULL_HANDLE
	2.��� image ��ΪVK_NULL_HANDLE ��1��image������ VkDedicatedAllocationImageCreateInfoNV::dedicatedAllocationΪVK_TRUE����
									  ��2��VkMemoryAllocateInfo::allocationSize ������� image�� VkMemoryRequirements::size
									  ��3�����VkMemoryAllocateInfo������һ��memory import operation��������� memory������һ�� dedicated image����ģ������ڴ�ֻ��image��ӵ�У�����imageҪ�͸�memory ��������VkImage��ͬ
									  

	3.��� buffer ��ΪVK_NULL_HANDLE ��1��buffer������ VkDedicatedAllocationImageCreateInfoNV::dedicatedAllocationΪVK_TRUE����
									   ��2��VkMemoryAllocateInfo::allocationSize ������� buffer �� VkMemoryRequirements::size
									   ��3�����VkMemoryAllocateInfo������һ��memory import operation��������� memory������һ�� dedicated buffer����ģ������ڴ�ֻ��buffer ��ӵ�У�����bufferҪ�͸�memory ��������VkBuffer��ͬ
									   
	
	*/

	// VkMemoryPriorityAllocateInfoEXT
	//�����VkMemoryAllocateInfo��pNext�а���,��ýṹ���ʾ���ڴ�����ȼ�

	VkMemoryPriorityAllocateInfoEXT& memoryPriorityAllocateInfoEXT = memoryAllocateInfoEXT.memoryPriorityAllocateInfoEXT;
	memoryPriorityAllocateInfoEXT.priority = 0;//�ǽ���0��1֮��ĸ���ֵ��ָʾ��������������ڴ��������ȼ���ֵԽ�����ȼ���Խ�ߡ����ȼ�������������ʵ�֡�
		{
		//�ı�����memory�����ȼ�
		vkSetDeviceMemoryPriorityEXT(device, deviceMemory, 0);
		}
	
	//VkExportMemoryAllocateInfo
	//�����VkMemoryAllocateInfo��pNext�а���һ��,��ýṹ���ʾ���ڴ��payload���Ե��뵽�������� ����Vulkan Instanceʹ��
	VkExportMemoryAllocateInfo& exportMemoryAllocateInfo = memoryAllocateInfoEXT.exportMemoryAllocateInfo;
	exportMemoryAllocateInfo.handleTypes = VK_EXTERNAL_MEMORY_HANDLE_TYPE_OPAQUE_FD_BIT;//�� 0 ��һ������VkExternalMemoryHandleTypeFlagBits��λ������ϣ�ָ��Ӧ�ó�����Դӽ�������е�����һ�������ڴ������͡���Ӧ�ó������Ϊ��ͬ�ķ���������������͡�������ͱ����Ǳ�֧�ֵģ��μ�VkExternalImageFormatProperties ���� VkExternalBufferProperties
	
	
	//VkExportMemoryAllocateInfoNV,���ܺ�VkExportMemoryAllocateInfo����
	//�����VkMemoryAllocateInfo��pNext�а���һ��,��ýṹ���ʾ���ڴ��payload���Ե��뵽�������� ����Vulkan Instanceʹ��
	VkExportMemoryAllocateInfoNV& exportMemoryAllocateInfoNV = memoryAllocateInfoEXT.exportMemoryAllocateInfoNV;
	exportMemoryAllocateInfoNV.handleTypes = VK_EXTERNAL_MEMORY_HANDLE_TYPE_OPAQUE_FD_BIT;//��VkExternalMemoryHandleTypeFlagBitsNV��һ�����߶��λ������ϣ�ָ��һ���������Ե������ڴ������͡�ͬһ��������Ķ��handle type�����Ǽ��ݵģ��μ�vkGetPhysicalDeviceExternalImageFormatPropertiesNV �л�ȡ�Ĳ���


	VkDeviceMemory allocatedMemory;
	//win32 handle ��������memory����
	HANDLE handle;
	{
		//VkExportMemoryWin32HandleInfoKHR
		//�����VkMemoryAllocateInfo��pNext�а���һ��(��ҪVkMemoryAllocateInfo��pNext�к���һ�� handleTypes����VK_EXTERNAL_MEMORY_HANDLE_TYPE_OPAQUE_WIN32_BIT��VkExportMemoryAllocateInfo ����Ч,�����������Ҳ���ܰ����ýṹ�� ),
		// ��ýṹ���ʾָ����memory �����е�����NT handle�Ķ������������
		VkExportMemoryWin32HandleInfoKHR& exportMemoryWin32HandleInfoKHR = memoryAllocateInfoEXT.exportMemoryWin32HandleInfoKHR;
		exportMemoryWin32HandleInfoKHR.name = L"name";//��һ���Կս�β��UTF-16�ַ�����Ҫ��Ӵ������ڴ浼����NT handle���õ���Ч���ع�����
		exportMemoryWin32HandleInfoKHR.dwAccess;//��һ��ָ���Ըþ���ķ���Ȩ�޵�DWORD��
		exportMemoryWin32HandleInfoKHR.pAttributes = nullptr;//��ָ��ָ�������ȫ���Ե�Windows SECURITY_ATTRIBUTES�ṹ��ָ�롣


		//VkImportMemoryWin32HandleInfoKHR
		//�����VkMemoryAllocateInfo��pNext�а���,���ʾ����һ��windows handle�� �ڴ�
		//����Windows handles�е�payload ���Ὣpayload������Ȩת�Ƹ�vulkan��ֻ�����ò���ת�ƣ��������������Ҫ����Ҫ����ϵͳ����CloaseHandle���ر�
		VkImportMemoryWin32HandleInfoKHR& importMemoryWin32HandleInfoKHR = memoryAllocateInfoEXT.importMemoryWin32HandleInfoKHR;
		importMemoryWin32HandleInfoKHR.handle = nullptr;//ΪNULL��Ҫ������ⲿ�����
		importMemoryWin32HandleInfoKHR.handleType = VK_EXTERNAL_MEMORY_HANDLE_TYPE_OPAQUE_WIN32_BIT;//��һ��ָ��handle ��name�����͵�VkExternalMemoryHandleTypeFlagBitsֵ
		importMemoryWin32HandleInfoKHR.name = L"name";//ΪNULL��ΪҪ������Կ��ַ�����β��UTF-16 payload�����֡�
		/*
		VkImportMemoryWin32HandleInfoKHR��Ч�÷�:
		1.���handleType ��Ϊ0�� ��1��������֧������ģ��μ�VkExternalImageFormatProperties ���� VkExternalBufferProperties
								   ��2������붨��Ϊ NT handle������global shader handle
								   ��3�����handleΪNULL����name ������һ��ָ����handleType����Ч��memory ��Դ
								   ��4�����handleΪNULL����handle ������һ��ָ����handleType����Ч��handle
		2.��handle�е����Ļ�������name ������memory ����͵�ǰdevice����ͬһ���ײ�physical device�ϴ�����
		3.���handleType ��ΪVK_EXTERNAL_MEMORY_HANDLE_TYPE_OPAQUE_WIN32_BIT, VK_EXTERNAL_MEMORY_HANDLE_TYPE_D3D11_TEXTURE_BIT, VK_EXTERNAL_MEMORY_HANDLE_TYPE_D3D12_HEAP_BIT, ���� VK_EXTERNAL_MEMORY_HANDLE_TYPE_D3D12_RESOURCE_BIT���� name����ΪNULL
		4.���handle ��Ϊ0����1��name����ΪNULL
							  ��2�����������������external memory handle types compatibility�е�Ҫ��

		5.���name ��ΪNULL�������������������external memory handle types compatibility�е�Ҫ��
		*/


		//����handle
		{
			//��һ��vulkan device memory �����е���һ����ʾpayload�� window handle������

			VkMemoryGetWin32HandleInfoKHR memoryGetWin32HandleInfoKHR;
			memoryGetWin32HandleInfoKHR.sType = VK_STRUCTURE_TYPE_MEMORY_GET_WIN32_HANDLE_INFO_KHR;
			memoryGetWin32HandleInfoKHR.pNext = nullptr;
			memoryGetWin32HandleInfoKHR.handleType = VK_EXTERNAL_MEMORY_HANDLE_TYPE_OPAQUE_WIN32_BIT;//��һ��ָ��������ľ�����͵�VkExternalMemoryHandleTypeFlagBitsֵ��
			memoryGetWin32HandleInfoKHR.memory = allocatedMemory;//�Ǽ������е��������memory ����
			/*
			VkMemoryGetWin32HandleInfoKHR��Ч�÷�:
			1.handleType ���������memory ����ʱ��VkExportMemoryAllocateInfo::handleTypes��
			2.���handleType ����Ϊһ�� NT handle����vkGetMemoryWin32HandleKHR ����ÿһ��������memory�� handleType�����ֻ�ܵ���һ��
			3.handleType ���붨��Ϊһ�� NT handle ���� global share handle

			*/

			vkGetMemoryWin32HandleKHR(device, &memoryGetWin32HandleInfoKHR, &handle);
			//�ýṹ��ȡ��NT handle����Ȩ���� application�� ���������ҪҲ��Ҫ����CloseHandle�����ڽӿ���VkMemoryGetWin32HandleInfoKHR.memory����������ܵ���


			VkMemoryWin32HandlePropertiesKHR memoryWin32HandlePropertiesKHR{};
			memoryWin32HandlePropertiesKHR.sType = VK_STRUCTURE_TYPE_MEMORY_WIN32_HANDLE_PROPERTIES_KHR;
			memoryWin32HandlePropertiesKHR.pNext = nullptr;
			memoryWin32HandlePropertiesKHR.memoryTypeBits;//��һ���������룬��Ӧÿһ��memory type ����VkPhysicalDeviceMemoryProperties.memoryTypes ??����ָ�� window handle���Ա�����Ϊ������ .
			//��vulkan���ݵ�window handle�������ɷ�vulkan api�����ģ�Ϊ����ȷʹ����Щhandle���Բ�ѯ�����ԣ�
			vkGetMemoryWin32HandlePropertiesKHR(device, VK_EXTERNAL_MEMORY_HANDLE_TYPE_D3D11_TEXTURE_BIT, handle, &memoryWin32HandlePropertiesKHR);//handleType �����Ƕ���Ϊopaque�� handle types



		}

		//VkExportMemoryWin32HandleInfoNV
		//�����VkMemoryAllocateInfoNV��pNext�а���һ��(��ҪVkMemoryAllocateInfoNV��pNext�к���һ�� handleTypes����VK_EXTERNAL_MEMORY_HANDLE_TYPE_OPAQUE_WIN32_BIT_NV��VkExportMemoryAllocateInfoNV ����Ч,�����������Ҳ���ܰ����ýṹ�� ),
		// ��ýṹ���ʾΪmemory�����external handleָ����ȫ���Ժͷ���Ȩ��
		VkExportMemoryWin32HandleInfoNV& exportMemoryWin32HandleInfoNV = memoryAllocateInfoEXT.exportMemoryWin32HandleInfoNV;
		exportMemoryWin32HandleInfoNV.dwAccess;//��һ��ָ���Ըþ���ķ���Ȩ�޵�DWORD��
		exportMemoryWin32HandleInfoNV.pAttributes;//��ָ��ָ�������ȫ���Ե�Windows SECURITY_ATTRIBUTES�ṹ��ָ�롣


		//VkImportMemoryWin32HandleInfoNV
		//�����VkMemoryAllocateInfoNV��pNext�а���һ��,��ʾ����ǵ�ǰVulkan Instance���ǵײ��physical device����ͬ��instance������mmemory 
		VkImportMemoryWin32HandleInfoNV& importMemoryWin32HandleInfoNV = memoryAllocateInfoEXT.importMemoryWin32HandleInfoNV;
		importMemoryWin32HandleInfoNV.handle = handle;//��һ��ָ�ڴ��Windows�����������vkGetMemoryWin32HandleNV ָ����ͬhandleType��ȡ����
		importMemoryWin32HandleInfoNV.handleType = VK_EXTERNAL_MEMORY_HANDLE_TYPE_OPAQUE_WIN32_BIT;/*��0��һ��ָ������е��ڴ������͵�VkExternalMemoryHandleTypeFlagBitsNVֵ��ֻ������һ��λ
		VkExternalMemoryHandleTypeFlagBitsNV��
		VK_EXTERNAL_MEMORY_HANDLE_TYPE_OPAQUE_WIN32_KMT_BIT_NV: ָ�����memory�� handle���� vkGetMemoryWin32HandleNV ���ص�
		VK_EXTERNAL_MEMORY_HANDLE_TYPE_OPAQUE_WIN32_BIT_NV: ָ�����memory�� handle���� vkGetMemoryWin32HandleNV ���ص� �������� DuplicateHandle() ���Ƶ�һ��vkGetMemoryWin32HandleNV���ص� handle
		VK_EXTERNAL_MEMORY_HANDLE_TYPE_D3D11_IMAGE_BIT_NV:  ָ�����memory����Ч��NT handle���� IDXGIResource1::CreateSharedHandle ���صģ� �������� DuplicateHandle() ���Ƶ�һ��IDXGIResource1::CreateSharedHandle ���ص� handle
		VK_EXTERNAL_MEMORY_HANDLE_TYPE_D3D11_IMAGE_KMT_BIT_NV: ָ�����memory�� handle���� IDXGIResource::GetSharedHandle() ���ص�

		*/


		//��ȡhandle NV
		{

			vkGetMemoryWin32HandleNV(device, allocatedMemory, VK_EXTERNAL_MEMORY_HANDLE_TYPE_OPAQUE_WIN32_KMT_BIT_NV, &handle);
			//�ڷ����ڴ�ʱ��handleType��������VkExportMemoryAllocateInfoNV����handleTypes��ָ���ı�־�����ڽӿ���memory����������ܵ���
		}
	
	
	
	
	
	}

	int fd;
	//POSIX file descriptor handle��������memory����
	{
		//VkImportMemoryFdInfoKHR
		//�����VkMemoryAllocateInfo��pNext�а���һ������ʾ��һ��POSIX file descriptor handle�е���memory
		//��file descriptor ����memory�Ὣfile descriptor ����Ȩ��Ӧ��ת�Ƶ�vulkan���ڳɹ������Ӧ�ó����ܶ�file descriptorִ���κβ����������memory ����ӵ����payload�����ã�Ӧ�ó�����Խ���ͬ��payload��ε��뵽Vulkan Instance��
		VkImportMemoryFdInfoKHR& importMemoryFdInfoKHR = memoryAllocateInfoEXT.importMemoryFdInfoKHR;
		importMemoryFdInfoKHR.fd = 0;//��Ҫ������ⲿ�����
		importMemoryFdInfoKHR.handleType = VK_EXTERNAL_MEMORY_HANDLE_TYPE_OPAQUE_FD_BIT;//��һ��ָ��fd�ľ�����͵�VkExternalMemoryHandleTypeFlagBitsֵ��
		/*
		VkImportMemoryFdInfoKHR��Ч�÷���
		1.���handleType ��Ϊ0�� ��1���������֧������ģ��μ�VkExternalImageFormatProperties ���� VkExternalBufferProperties
								   ��2���������ΪVK_EXTERNAL_MEMORY_HANDLE_TYPE_OPAQUE_FD_BIT ��VK_EXTERNAL_MEMORY_HANDLE_TYPE_DMA_BUF_BIT_EXT
								   ��3��fd������handleType ָ������Ч�� handle

		2.��fd �е����ĵ�memory ����͵�ǰdevice����ͬһ���ײ�physical device�ϴ�����
		3.fd ��ʾ��memory �����ں͵�ǰdevice�Լ� handleType���ݵ���ͬ�ײ�physical device���������ϴ����ģ��μ�external memory handle types compatibility�е�Ҫ��
		4.fd ��������������external memory handle types compatibility�е�Ҫ��
		*/
	

		VkMemoryGetFdInfoKHR getMemoryFdInfoKHR{};
		getMemoryFdInfoKHR.sType = VK_STRUCTURE_TYPE_MEMORY_GET_FD_INFO_KHR;
		getMemoryFdInfoKHR.pNext = nullptr;
		getMemoryFdInfoKHR.handleType = VK_EXTERNAL_MEMORY_HANDLE_TYPE_OPAQUE_FD_BIT;//��һ��ָ��������ľ�����͵�VkExternalMemoryHandleTypeFlagBitsֵ��
		getMemoryFdInfoKHR.memory = allocatedMemory;// �ǽ����е���������ڴ����
		/*
		VkMemoryGetFdInfoKHR��Ч�÷���
		1.handleType ��������ڴ���memory�� VkExportMemoryAllocateInfo::handleTypes��
		2.handleType ����ΪVK_EXTERNAL_MEMORY_HANDLE_TYPE_OPAQUE_FD_BIT �� VK_EXTERNAL_MEMORY_HANDLE_TYPE_DMA_BUF_BIT_EXT
		*/


		//����һ�� ���õ�vulkan��memory �����payload�� POSIX file descriptor
		vkGetMemoryFdKHR(device, &getMemoryFdInfoKHR, &fd);
		//ÿ�ε���vkGetMemoryFdKHR���ᴴ��һ���µ����õ���memory��payload��file descriptor�ҽ�����Ȩ����Ӧ�ó��򣬲�����Ҫ�õ�ʱ����Ҫ����close��fd��,���������ڴ��С���ܻᳬ��VkMemoryAllocateInfo::allocationSize.�����handleTypeΪ VK_EXTERNAL_MEMORY_HANDLE_TYPE_DMA_BUF_BIT_EXT,���Ե���lseek��ѯ�ⲿ�ļ���С
	


		VkMemoryFdPropertiesKHR memoryFdPropertiesKHR{};
		memoryFdPropertiesKHR.sType = VK_STRUCTURE_TYPE_MEMORY_FD_PROPERTIES_KHR;
		memoryFdPropertiesKHR.pNext = nullptr;
		memoryFdPropertiesKHR.memoryTypeBits;//��һ���������룬��Ӧÿһ��memory type ����VkPhysicalDeviceMemoryProperties.memoryTypes ??����ָ�� POSIX file descriptor���Ա�����Ϊ������ .
		//��vulkan���ݵ�POSIX file descriptor�������ɷ�vulkan api�����ģ�Ϊ����ȷʹ����Щhandle���Բ�ѯ�����ԣ�
		vkGetMemoryFdPropertiesKHR(device, VK_EXTERNAL_MEMORY_HANDLE_TYPE_DMA_BUF_BIT_EXT, fd, &memoryFdPropertiesKHR);//handleType �����Ƕ���Ϊopaque�� handle types
		//handleType����ΪVK_EXTERNAL_MEMORY_HANDLE_TYPE_OPAQUE_FD_BIT






	}



	void* hostPointer;
	//host memory
	{
		//VkImportMemoryHostPointerInfoEXT
		//�����VkMemoryAllocateInfo��pNext�а���һ������ʾ��һ��host pointer�е���memory
		//����host pointer����host��vulkanʵ�ּ乲��memory ������Ȩ��Ӧ�ó�����Ȼ����ͨ��host pointer���ʸ��ڴ棬ֻ����ҪӦ�ó������device�� non-device���ڴ����ͬ��
		//host pointer���Զ�ε��뵽vulkan instance����������Ϊƽ̨�����ƶ����µ���ʧ��
		VkImportMemoryHostPointerInfoEXT& importMemoryHostPointerInfoEXT = memoryAllocateInfoEXT.importMemoryHostPointerInfoEXT;
		importMemoryHostPointerInfoEXT.handleType = VK_EXTERNAL_MEMORY_HANDLE_TYPE_HOST_ALLOCATION_BIT_EXT;//��һ��ָ��������͵�VkExternalMemoryHandleTypeFlagBitsֵ��
		importMemoryHostPointerInfoEXT.pHostPointer = nullptr;//��Ҫ���е���memory ��host pointer
		/*
		VkImportMemoryHostPointerInfoEXT��Ч�÷���
		1.���handleType ��Ϊ0����1�������֧�ֵ��룬�μ�VkExternalMemoryProperties
								  ��2�������ΪVK_EXTERNAL_MEMORY_HANDLE_TYPE_HOST_ALLOCATION_BIT_EXT ���� VK_EXTERNAL_MEMORY_HANDLE_TYPE_HOST_MAPPED_FOREIGN_MEMORY_BIT_EXT
		
		2.pHostPointer ��ָ������뵽�������� VkPhysicalDeviceExternalMemoryHostPropertiesEXT::minImportedHostPointerAlignment
		3.���handleType Ϊ VK_EXTERNAL_MEMORY_HANDLE_TYPE_HOST_ALLOCATION_BIT_EXT��pHostPointer������һ����СΪVkMemoryAllocateInfo.allocationSize ��host memory��ָ��
		4.���handleTypeΪ VK_EXTERNAL_MEMORY_HANDLE_TYPE_HOST_MAPPED_FOREIGN_MEMORY_BIT_EXT��pHostPointer������һ����СΪVkMemoryAllocateInfo.allocationSize ��host mapped foreign memory��ָ��

		*/



		VkMemoryHostPointerPropertiesEXT memoryHostPointerPropertiesEXT{};
		memoryHostPointerPropertiesEXT.sType = VK_STRUCTURE_TYPE_MEMORY_HOST_POINTER_PROPERTIES_EXT;
		memoryHostPointerPropertiesEXT.pNext = nullptr;
		memoryHostPointerPropertiesEXT.memoryTypeBits;//��һ���������룬��Ӧÿһ��memory type ����VkPhysicalDeviceMemoryProperties.memoryTypes ??����ָ�� host pointer���Ա�����Ϊ������ .ֻ����host �ɼ���memory type
		
		//Ϊ�˵���host pointerʱ�������Ƿ���ȷ�����Ե��ú�����ѯ����
		vkGetMemoryHostPointerPropertiesEXT(device, VK_EXTERNAL_MEMORY_HANDLE_TYPE_HOST_MAPPED_FOREIGN_MEMORY_BIT_EXT, hostPointer, &memoryHostPointerPropertiesEXT);
		/*
		vkGetMemoryHostPointerPropertiesEXT��Ч�÷�:
		1.handleType ����ΪVK_EXTERNAL_MEMORY_HANDLE_TYPE_HOST_ALLOCATION_BIT_EXT ���� VK_EXTERNAL_MEMORY_HANDLE_TYPE_HOST_MAPPED_FOREIGN_MEMORY_BIT_EXT
		2.pHostPointer����ʱ��Ч�Ķ��뵽������VkPhysicalDeviceExternalMemoryHostPropertiesEXT::minImportedHostPointerAlignment��ָ��
		3.���handleType ΪVK_EXTERNAL_MEMORY_HANDLE_TYPE_HOST_ALLOCATION_BIT_EXT��pHostPointer ������host memory��ָ��
		4.���handleType ΪVK_EXTERNAL_MEMORY_HANDLE_TYPE_HOST_MAPPED_FOREIGN_MEMORY_BIT_EXT��pHostPointer ������host mapped foreign memory��ָ��
		*/


	}
	
	AHardwareBuffer* androidBuffer;
	// android hardware buffer external memory
	{
		// VkImportAndroidHardwareBufferInfoANDROID
		//�����VkMemoryAllocateInfo��pNext�а���һ������ʾ��һ��vulkan instalce �ⲿ�� android hardware buffer�е���memory
		VkImportAndroidHardwareBufferInfoANDROID& importAndroidHardwareBufferInfoANDROID = memoryAllocateInfoEXT.importAndroidHardwareBufferInfoANDROID;
		importAndroidHardwareBufferInfoANDROID.buffer = androidBuffer;//��Ҫ�����android hardware buffer
		/*
		VkImportAndroidHardwareBufferInfoANDROID��Ч�÷���
		1.��� buffer��Ϊ NULL����1�� android hardware buffer����֧�ֵ��룬�μ�VkExternalImageFormatProperties ���� VkExternalBufferProperties
								  ��2��buffer����Ϊһ����Android Hardware Buffers�������� AHardwareBuffer_Desc::usage ��vulkan ���ݵĶ���

		*/
	

		VkMemoryGetAndroidHardwareBufferInfoANDROID memoryGetAndroidHardwareBufferInfoANDROID{};
		memoryGetAndroidHardwareBufferInfoANDROID.sType = VK_STRUCTURE_TYPE_MEMORY_GET_ANDROID_HARDWARE_BUFFER_INFO_ANDROID;
		memoryGetAndroidHardwareBufferInfoANDROID.pNext = nullptr;
		memoryGetAndroidHardwareBufferInfoANDROID.memory = allocatedMemory;//�ǽ����е���android hardware buffer��VkDeviceMemory����
		/*
		VkMemoryGetAndroidHardwareBufferInfoANDROID��Ч�÷���
		1.������memory ��ʱ��VkExportMemoryAllocateInfo::handleTypes �б������VK_EXTERNAL_MEMORY_HANDLE_TYPE_ANDROID_HARDWARE_BUFFER_BIT_ANDROID 
		2.�������memory��ʱ��VkMemoryAllocateInfo ��pNext�к���һ��image��ΪNULL�� VkMemoryDedicatedAllocateInfo�����image �����Ѿ��󶨵���memory��

		*/




		//��vulkan object�е���һ��������payload�� android hardware buffer���ã�
		vkGetMemoryAndroidHardwareBufferANDROID(device, &memoryGetAndroidHardwareBufferInfoANDROID, &androidBuffer);
		//����vkGetMemoryAndroidHardwareBufferANDROID������һ���µ�android hardware buffer ���õ� VkDeviceMemory.������ͬ��VkMemoryGetAndroidHardwareBufferInfoANDROID.memory��������ͬ������

		VkAndroidHardwareBufferPropertiesANDROID androidHardwareBufferPropertiesANDROID{};
		androidHardwareBufferPropertiesANDROID.sType = VK_STRUCTURE_TYPE_ANDROID_HARDWARE_BUFFER_PROPERTIES_ANDROID;
			//VkAndroidHardwareBufferPropertiesANDROID.pNext
			{
			VkAndroidHardwareBufferFormatProperties2ANDROID androidHardwareBufferFormatProperties2ANDROID{};
			androidHardwareBufferFormatProperties2ANDROID.sType = VK_STRUCTURE_TYPE_ANDROID_HARDWARE_BUFFER_FORMAT_PROPERTIES_2_ANDROID;
			androidHardwareBufferFormatProperties2ANDROID.pNext = nullptr;
			androidHardwareBufferFormatProperties2ANDROID.format;//����android hardware buffer format��Ӧ��Vulkan format�����û�е�Ч��Vulkan format����ΪVK_FORMAT_UNDEFINED�����android hardware buffer ��һ��format�о��� Format Equivalence table �У����ֵ��Ϊ���Ӧformat������ΪVK_FORMAT_UNDEFINED
			androidHardwareBufferFormatProperties2ANDROID.externalFormat;//��һ��ʵ�ֶ�����ⲿ��ʽ��ʶ��������VkExternalFormatANDROID������Ϊ�㡣
			androidHardwareBufferFormatProperties2ANDROID.formatFeatures;//������һ��image �󶨵���buffer �е����memoryʱ ���ⲿ��ʽ���������������VK_FORMAT_FEATURE_SAMPLED_IMAGE_BIT�Լ����ٰ��� VK_FORMAT_FEATURE_MIDPOINT_CHROMA_SAMPLES_BIT �� VK_FORMAT_FEATURE_COSITED_CHROMA_SAMPLES_BIT�е�һ����Ӧ�ð���VK_FORMAT_FEATURE_SAMPLED_IMAGE_FILTER_LINEAR_BIT �� VK_FORMAT_FEATURE_SAMPLED_IMAGE_YCBCR_CONVERSION_LINEAR_FILTER_BIT.
			//�ò���ֻ������ֻ��ʹ�� android hardware buffer ������һ�� �ⲿ���ǵ�imageʱ��� ��Ч����
			androidHardwareBufferFormatProperties2ANDROID.samplerYcbcrConversionComponents;//Ӧ������VkSamplerYcbcrConversionCreateInfo�е�component swizzle����
			androidHardwareBufferFormatProperties2ANDROID.suggestedYcbcrModel;//����VkSamplerYcbcrConversionCreateInfo�е�һ�������color model
			androidHardwareBufferFormatProperties2ANDROID.suggestedYcbcrRange;//����VkSamplerYcbcrConversionCreateInfo.��ʹ�õ�һ��������ֵ��Χ
			androidHardwareBufferFormatProperties2ANDROID.suggestedXChromaOffset;//����VkSamplerYcbcrConversionCreateInfo.��ʹ�õ�һ������� X chroma offset
			androidHardwareBufferFormatProperties2ANDROID.suggestedYChromaOffset;//����VkSamplerYcbcrConversionCreateInfo.��ʹ�õ�һ������� Y chroma offset
			
			}
		androidHardwareBufferPropertiesANDROID.pNext = nullptr;//����ΪNULL���߰���һ�� ��Ч��VkAndroidHardwareBufferFormatProperties2ANDROID, VkAndroidHardwareBufferFormatPropertiesANDROID, ����VkAndroidHardwareBufferFormatResolvePropertiesANDROID
		androidHardwareBufferPropertiesANDROID.allocationSize;//Ϊ�ⲿmemory�Ĵ�С
		androidHardwareBufferPropertiesANDROID.memoryTypeBits;//��һ���������룬��Ӧÿһ��memory type ����VkPhysicalDeviceMemoryProperties.memoryTypes ??����ָ�� android hardware buffer���Ա�����Ϊ������ .
		//Ϊ�˵���android hardware bufferʱ�������Ƿ���ȷ�����Ե��ú�����ѯ����
		vkGetAndroidHardwareBufferPropertiesANDROID(device, androidBuffer, &androidHardwareBufferPropertiesANDROID);
		//buffer ������һ������AHardwareBuffer_Desc::usage���ٰ���һ��AHARDWAREBUFFER_USAGE_GPU_* flags����Ч�� android hardware buffer




	}






	vkAllocateMemory(device, &memoryAllocateInfo, nullptr, &deviceMemory);
	/*
	vkAllocateMemory��Ч�÷�:
	1.pAllocateInfo->allocationSize����С�ڵ��� VkPhysicalDeviceMemoryProperties::memoryHeaps[memindex].size������memindex Ϊͨ��vkGetPhysicalDeviceMemoryProperties�ӿڲ�ѯ�� VkPhysicalDeviceMemoryProperties::memoryTypes[pAllocateInfo->memoryTypeIndex].heapIndex��VkPhysicalDeviceMemoryProperties��
	2.pAllocateInfo->memoryTypeIndex����С��ͨ��vkGetPhysicalDeviceMemoryProperties�ӿڲ�ѯ��VkPhysicalDeviceMemoryProperties::memoryTypeCount��
	3.��� deviceCoherentMemory ����û�п�����pAllocateInfo->memoryTypeIndex�Ͳ���ָ��һ��֧�� VK_MEMORY_PROPERTY_DEVICE_COHERENT_BIT_AMD���ڴ�����
	4.��ǰ��device�Ϸ�����ڴ��С����С��VkPhysicalDeviceLimits::maxMemoryAllocationCount
	
	*/



}


NS_TEST_END