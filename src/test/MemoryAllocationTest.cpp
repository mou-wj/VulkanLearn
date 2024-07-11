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




// Provided by VK_ANDROID_external_format_resolve
typedef struct VkAndroidHardwareBufferFormatResolvePropertiesANDROID {
	VkStructureType sType;
	void* pNext;
	VkFormat colorAttachmentFormat;
} VkAndroidHardwareBufferFormatResolvePropertiesANDROID;





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
	VkDeviceMemory deviceMemory{ VK_NULL_HANDLE };
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
			//VkAndroidHardwareBufferFormatPropertiesANDROID
			VkAndroidHardwareBufferFormatPropertiesANDROID androidHardwareBufferFormatPropertiesANDROID{};
			androidHardwareBufferFormatPropertiesANDROID.sType = VK_STRUCTURE_TYPE_ANDROID_HARDWARE_BUFFER_FORMAT_PROPERTIES_ANDROID;
			androidHardwareBufferFormatPropertiesANDROID.pNext = nullptr;
			androidHardwareBufferFormatPropertiesANDROID.format;//����android hardware buffer format��Ӧ��Vulkan format�����û�е�Ч��Vulkan format����ΪVK_FORMAT_UNDEFINED�����android hardware buffer ��һ��format�о��� Format Equivalence table �У����ֵ��Ϊ���Ӧformat������ΪVK_FORMAT_UNDEFINED
			androidHardwareBufferFormatPropertiesANDROID.externalFormat;//��һ��ʵ�ֶ�����ⲿ��ʽ��ʶ��������VkExternalFormatANDROID������Ϊ�㡣
			androidHardwareBufferFormatPropertiesANDROID.formatFeatures;//������һ��image �󶨵���buffer �е����memoryʱ ���ⲿ��ʽ���������������VK_FORMAT_FEATURE_SAMPLED_IMAGE_BIT�Լ����ٰ��� VK_FORMAT_FEATURE_MIDPOINT_CHROMA_SAMPLES_BIT �� VK_FORMAT_FEATURE_COSITED_CHROMA_SAMPLES_BIT�е�һ����Ӧ�ð���VK_FORMAT_FEATURE_SAMPLED_IMAGE_FILTER_LINEAR_BIT �� VK_FORMAT_FEATURE_SAMPLED_IMAGE_YCBCR_CONVERSION_LINEAR_FILTER_BIT.
			//�ò���ֻ������ֻ��ʹ�� android hardware buffer ������һ�� �ⲿ���ǵ�imageʱ��� ��Ч����
			androidHardwareBufferFormatPropertiesANDROID.samplerYcbcrConversionComponents;//Ӧ������VkSamplerYcbcrConversionCreateInfo�е�component swizzle����
			androidHardwareBufferFormatPropertiesANDROID.suggestedYcbcrModel;//����VkSamplerYcbcrConversionCreateInfo�е�һ�������color model
			androidHardwareBufferFormatPropertiesANDROID.suggestedYcbcrRange;//����VkSamplerYcbcrConversionCreateInfo.��ʹ�õ�һ��������ֵ��Χ
			androidHardwareBufferFormatPropertiesANDROID.suggestedXChromaOffset;//����VkSamplerYcbcrConversionCreateInfo.��ʹ�õ�һ������� X chroma offset
			androidHardwareBufferFormatPropertiesANDROID.suggestedYChromaOffset;//����VkSamplerYcbcrConversionCreateInfo.��ʹ�õ�һ������� Y chroma offset


			//VkAndroidHardwareBufferFormatProperties2ANDROID
			VkAndroidHardwareBufferFormatProperties2ANDROID androidHardwareBufferFormatProperties2ANDROID{};
			androidHardwareBufferFormatProperties2ANDROID.pNext = nullptr;
			androidHardwareBufferFormatProperties2ANDROID.sType = VK_STRUCTURE_TYPE_ANDROID_HARDWARE_BUFFER_FORMAT_PROPERTIES_2_ANDROID;
			androidHardwareBufferFormatProperties2ANDROID.format;//����android hardware buffer format��Ӧ��Vulkan format�����û�е�Ч��Vulkan format����ΪVK_FORMAT_UNDEFINED��
			androidHardwareBufferFormatProperties2ANDROID.externalFormat;//��һ��ʵ�ֶ�����ⲿ��ʽ��ʶ��������VkExternalFormatANDROID������Ϊ�㡣
			androidHardwareBufferFormatProperties2ANDROID.formatFeatures;//������һ��image �󶨵���buffer �е����memoryʱ ���ⲿ��ʽ���������������VkAndroidHardwareBufferFormatPropertiesANDROID::formatFeatures�����õ�bit
			androidHardwareBufferFormatProperties2ANDROID.samplerYcbcrConversionComponents;//Ӧ������VkSamplerYcbcrConversionCreateInfo�е�component swizzle����
			androidHardwareBufferFormatProperties2ANDROID.suggestedYcbcrModel;//����VkSamplerYcbcrConversionCreateInfo�е�һ�������color model
			androidHardwareBufferFormatProperties2ANDROID.suggestedYcbcrRange;//����VkSamplerYcbcrConversionCreateInfo.��ʹ�õ�һ��������ֵ��Χ
			androidHardwareBufferFormatProperties2ANDROID.suggestedXChromaOffset;//����VkSamplerYcbcrConversionCreateInfo.��ʹ�õ�һ������� X chroma offset
			androidHardwareBufferFormatProperties2ANDROID.suggestedYChromaOffset;//����VkSamplerYcbcrConversionCreateInfo.��ʹ�õ�һ������� Y chroma offset

			VkAndroidHardwareBufferFormatResolvePropertiesANDROID androidHardwareBufferFormatResolvePropertiesANDROID{};
			androidHardwareBufferFormatResolvePropertiesANDROID.sType = VK_STRUCTURE_TYPE_MAX_ENUM;//û�ж�����������Ϊ�Ƿ�ֵ
			androidHardwareBufferFormatResolvePropertiesANDROID.pNext = nullptr;
			androidHardwareBufferFormatResolvePropertiesANDROID.colorAttachmentFormat = VK_FORMAT_UNDEFINED;//ָ����Ϊʹ����external format�� color attachment image ��resolve ������ color VkFormat�����֧��external format��resolve��������Ϊ�ø�ʽ����vkGetPhysicalDeviceFormatProperties ���ص�VkFormatProperties::optimalTilingFeatures ��Ҫ֧�� VK_FORMAT_FEATURE_COLOR_ATTACHMENT_BIT�������֧�ָ�format�ͱ�������Ϊ VK_FORMAT_UNDIFIED
		}
		androidHardwareBufferPropertiesANDROID.pNext = nullptr;//����ΪNULL���߰���һ�� ��Ч��VkAndroidHardwareBufferFormatProperties2ANDROID, VkAndroidHardwareBufferFormatPropertiesANDROID, ����VkAndroidHardwareBufferFormatResolvePropertiesANDROID
		androidHardwareBufferPropertiesANDROID.allocationSize;//Ϊ�ⲿmemory�Ĵ�С
		androidHardwareBufferPropertiesANDROID.memoryTypeBits;//��һ���������룬��Ӧÿһ��memory type ����VkPhysicalDeviceMemoryProperties.memoryTypes ??����ָ�� android hardware buffer���Ա�����Ϊ������ .
		//Ϊ�˵���android hardware bufferʱ�������Ƿ���ȷ�����Ե��ú�����ѯ����
		vkGetAndroidHardwareBufferPropertiesANDROID(device, androidBuffer, &androidHardwareBufferPropertiesANDROID);
		//buffer ������һ������AHardwareBuffer_Desc::usage���ٰ���һ��AHARDWAREBUFFER_USAGE_GPU_* flags����Ч�� android hardware buffer




	}



	VkRemoteAddressNV remoteAddressNV{ VK_NULL_HANDLE };
	//����һ���ɹ�remote device ���ʵ�vulkan device �����payload ��ַ
	{
		VkMemoryGetRemoteAddressInfoNV memoryGetRemoteAddressInfoNV{};
		memoryGetRemoteAddressInfoNV.sType = VK_STRUCTURE_TYPE_MEMORY_GET_REMOTE_ADDRESS_INFO_NV;
		memoryGetRemoteAddressInfoNV.pNext = nullptr;
		memoryGetRemoteAddressInfoNV.handleType = VK_EXTERNAL_MEMORY_HANDLE_TYPE_OPAQUE_WIN32_BIT_KHR;//ָ����Ҫ��hanle type�����������memory����ʱ���  VkExportMemoryAllocateInfo::handleTypes��
		memoryGetRemoteAddressInfoNV.memory = allocatedMemory;//�ǽ����е���Զ�̿ɷ��ʵ�ַ���ڴ����

		vkGetMemoryRemoteAddressNV(device, &memoryGetRemoteAddressInfoNV, &remoteAddressNV);


	}

	zx_handle_t zxHandle;
	//FUCHSIA external memory
	{

		// Fuchsia�ϵ��ⲿ�ڴ潫ʹ��zx_handle_t���͵�VMO������е���͵������ⲿ�ڴ��VMO���ͨ���Ǵ� Fuchsia��Sysmem������ϵͳ������zx_vmo_create�����л�õġ����ڵ����VMO���Ҳ����ͨ������һ��Vulkanʵ��������������ã����ڵ��� exporting fuchsia device memory������
		//����VMO handles ��������Ȩ��Ӧ��ת�Ƹ�Instance���ҵ���ɹ���Ӧ�þͲ����ڶԸ�handle ���κβ��������Խ�handle ��ε���vulkan instance��
		VkImportMemoryZirconHandleInfoFUCHSIA  importMemoryZirconHandleInfoFUCHSIA = memoryAllocateInfoEXT.importMemoryZirconHandleInfoFUCHSIA;
		importMemoryZirconHandleInfoFUCHSIA.handleType = VK_EXTERNAL_MEMORY_HANDLE_TYPE_ZIRCON_VMO_BIT_FUCHSIA;//��һ��ָ��������͵�VkExternalMemoryHandleTypeFlagBitsֵ��
		importMemoryZirconHandleInfoFUCHSIA.handle = zxHandle;//��ָ���ⲿ�ڴ��zx_handle_t��Zircon�������

		VkMemoryZirconHandlePropertiesFUCHSIA memoryZirconHandlePropertiesFUCHSIA{};
		memoryZirconHandlePropertiesFUCHSIA.sType = VK_STRUCTURE_TYPE_MEMORY_ZIRCON_HANDLE_PROPERTIES_FUCHSIA;
		memoryZirconHandlePropertiesFUCHSIA.pNext = nullptr;
		memoryZirconHandlePropertiesFUCHSIA.memoryTypeBits;//��һ���������룬��Ӧÿһ��memory type ����VkPhysicalDeviceMemoryProperties.memoryTypes ??����ָ���� handle���Ա�����Ϊ������ .
		//��ȡ���õ�������Ϣ
		vkGetMemoryZirconHandlePropertiesFUCHSIA(device, VK_EXTERNAL_MEMORY_HANDLE_TYPE_ZIRCON_VMO_BIT_FUCHSIA, zxHandle, &memoryZirconHandlePropertiesFUCHSIA);
		//handleType ����Ϊ VK_EXTERNAL_MEMORY_HANDLE_TYPE_ZIRCON_VMO_BIT_FUCHSIA


		VkMemoryGetZirconHandleInfoFUCHSIA memoryGetZirconHandleInfoFUCHSIA{};
		memoryGetZirconHandleInfoFUCHSIA.sType = VK_STRUCTURE_TYPE_MEMORY_GET_ZIRCON_HANDLE_INFO_FUCHSIA;
		memoryGetZirconHandleInfoFUCHSIA.pNext = nullptr;
		memoryGetZirconHandleInfoFUCHSIA.handleType = VK_EXTERNAL_MEMORY_HANDLE_TYPE_ZIRCON_VMO_BIT_FUCHSIA;//��һ��ָ����vkGetMemoryZirconHandleFUCHSIA����pZirconHandle.��ָ��ľ�������͵�VkExternalMemoryHandleTypeFlagBitsֵ
		memoryGetZirconHandleInfoFUCHSIA.memory = allocatedMemory;//��������VkDeviceMemory����
		/*
		1.handleType ����Ϊ VK_EXTERNAL_MEMORY_HANDLE_TYPE_ZIRCON_VMO_BIT_FUCHSIA
		2.handleType ��������ڴ���memory�� VkExportMemoryAllocateInfo�� handleTypes��
		*/


		//�뵼�����ƣ���Vulkan����һ��VMO����Ὣ�þ��������Ȩ��Vulkan Instanceת�Ƶ�Ӧ�ó��򡣵�����ʹ��ʱ��Ӧ�ó�����ʹ��zx_handle_close�����رոþ����
		vkGetMemoryZirconHandleFUCHSIA(device, &memoryGetZirconHandleInfoFUCHSIA, &zxHandle);

	}

	//metal object
	{
		//������
		//Vulkanʵ�ִ���Apple ƽ̨��Metal �ϲ㣬���ʵ����VK_EXT_metal_objects��չ����֧�ֵ���͵������ض�Vulkan����������ĵײ�Metal �����������
		//��ĳЩVulkan�����е����ײ�Metal �������ʹ��vkExportMetalObjectsEXT�����VkExportMetalObjectsInfoEXT������pNext����
		//һ�� VkDeviceMemory ���Ի���һ���Ѿ����ڵ�  MTLBuffer������ֻ���ڴ������ڴ�ʱ�� VkMemoryAllocateInfo��pNext ����һ�� VkImportMetalBufferInfoEXT 
		//һ���µ� VkImage ���Ի����Ѿ����ڵ� IOSurface����һ������  Metal MTLTexture �ϴ�����ֻ���ڴ�����image ʱ��  VkImageCreateInfo��pNext ����һ��  VkImportMetalIOSurfaceInfoEXT ���� VkImportMetalTextureInfoEXT 
		//���Ҫ����ĳ��VkDeviceMemory�� Metal��������Ҫ�ڶ�Ӧ��������Ĳ����ṹ���pNext�м���һ������ VkExportMetalObjectCreateInfoEXT����VkInstanceCreateInfo,
		//       VkMemoryAllocateInfo, VkImageCreateInfo, VkImageViewCreateInfo, VkBufferViewCreateInfo, VkSemaphoreCreateInfo, ���� VkEventCreateInfo,

		VkExportMetalObjectCreateInfoEXT exportMetalObjectCreateInfoEXT = memoryAllocateInfoEXT.exportMetalObjectCreateInfoEXT;
		exportMetalObjectCreateInfoEXT.sType = VK_STRUCTURE_TYPE_EXPORT_METAL_OBJECT_CREATE_INFO_EXT;
		exportMetalObjectCreateInfoEXT.pNext = nullptr;
		exportMetalObjectCreateInfoEXT.exportObjectType = VK_EXPORT_METAL_OBJECT_TYPE_METAL_DEVICE_BIT_EXT;/*��һ���Ϸ���VkExportMetalObjectTypeFlagBitsEXTֵ�������Ϊ0����ָʾӦ�ó�����������Vulkan���󵼳���Metal ��������͡�
		VkExportMetalObjectTypeFlagBitsEXT��
		VK_EXPORT_METAL_OBJECT_TYPE_METAL_DEVICE_BIT_EXT : ָһ�� Metal MTLDevice ���ܱ�����.
		VK_EXPORT_METAL_OBJECT_TYPE_METAL_COMMAND_QUEUE_BIT_EXT :  ָһ�� Metal MTLCommandQueue ���ܱ�����.
		VK_EXPORT_METAL_OBJECT_TYPE_METAL_BUFFER_BIT_EXT :  ָһ�� Metal MTLBuffer ���ܱ�����.
		VK_EXPORT_METAL_OBJECT_TYPE_METAL_TEXTURE_BIT_EXT :  ָһ�� Metal MTLTexture ���ܱ�����.
		VK_EXPORT_METAL_OBJECT_TYPE_METAL_IOSURFACE_BIT_EXT :  ָһ�� Metal IOSurface ���ܱ�����.
		VK_EXPORT_METAL_OBJECT_TYPE_METAL_SHARED_EVENT_BIT_EXT :  ָһ�� Metal MTLSharedEvent ���ܱ�����.

		*/


		//����vulkan ����ײ��Metal ����
		VkExportMetalObjectsInfoEXT exportMetalObjectsInfoEXT{};
		exportMetalObjectsInfoEXT.sType = VK_STRUCTURE_TYPE_EXPORT_METAL_OBJECTS_INFO_EXT;
		//VkExportMetalObjectsInfoEXT.pNext
		{
			//���԰�����VkExportMetalObjectsInfoEXT.pNext��ָ��Ҫ������Metal ��������
			struct ExportMetalObjectsInfoEXT {
				VkExportMetalBufferInfoEXT exportMetalBufferInfoEXT{};
				VkExportMetalCommandQueueInfoEXT exportMetalCommandQueueInfoEXT{};
				VkExportMetalDeviceInfoEXT exportMetalDeviceInfoEXT{};
				VkExportMetalIOSurfaceInfoEXT exportMetalIOSurfaceInfoEXT{};
				VkExportMetalSharedEventInfoEXT	exportMetalSharedEventInfoEXT{};
				VkExportMetalTextureInfoEXT  exportMetalTextureInfoEXT{};
				ExportMetalObjectsInfoEXT() {
					Init();
				}
				void Init() {
					exportMetalBufferInfoEXT.sType = VK_STRUCTURE_TYPE_EXPORT_METAL_BUFFER_INFO_EXT;
					exportMetalBufferInfoEXT.pNext = nullptr;
					exportMetalCommandQueueInfoEXT.sType = VK_STRUCTURE_TYPE_EXPORT_METAL_COMMAND_QUEUE_INFO_EXT;
					exportMetalCommandQueueInfoEXT.pNext = nullptr;
					exportMetalDeviceInfoEXT.sType = VK_STRUCTURE_TYPE_EXPORT_METAL_DEVICE_INFO_EXT;
					exportMetalDeviceInfoEXT.pNext = nullptr;
					exportMetalIOSurfaceInfoEXT.sType = VK_STRUCTURE_TYPE_EXPORT_METAL_IO_SURFACE_INFO_EXT;
					exportMetalIOSurfaceInfoEXT.pNext = nullptr;
					exportMetalSharedEventInfoEXT.sType = VK_STRUCTURE_TYPE_EXPORT_METAL_SHARED_EVENT_INFO_EXT;
					exportMetalSharedEventInfoEXT.pNext = nullptr;
					exportMetalTextureInfoEXT.sType = VK_STRUCTURE_TYPE_EXPORT_METAL_TEXTURE_INFO_EXT;
					exportMetalTextureInfoEXT.pNext = nullptr;


				}

			};



			ExportMetalObjectsInfoEXT exportMetalObjectsInfoEXT{};

			//����������VkDevice��  VkPhysicalDevice ����ײ�� Metal MTLDevice object ����
			VkExportMetalDeviceInfoEXT& exportMetalDeviceInfoEXT = exportMetalObjectsInfoEXT.exportMetalDeviceInfoEXT;
			exportMetalDeviceInfoEXT.mtlDevice;//��������б�ʶ��VkDevice���������VkPhysicalDevice �ײ��Metal id<MTLDevice>���󡣸�ʵ�ֽ����ص��˳�Ա�е�MTLDevice�����������vkPhysicaDevice ������û���ҵ�MTLDevice������������NULL


			//����Vulkan Queue����ײ��Metal MTLCommandQueue����
			VkExportMetalCommandQueueInfoEXT exportMetalCommandQueueInfoEXT = exportMetalObjectsInfoEXT.exportMetalCommandQueueInfoEXT;
			exportMetalCommandQueueInfoEXT.queue = VkQueue{/*����������һ����Ч��VkQueue����*/ };
			exportMetalCommandQueueInfoEXT.mtlCommandQueue;//��������б�ʶ��VkQueue���������VkPhysicalDevice �ײ��Metal id<MTLCommandQueue>���󡣸�ʵ�ֽ����ص��˳�Ա�е�MTLCommandQueue����������� VkQueue ������û���ҵ�MTLCommandQueue������������NULL


			//���� VkDeviceMemory ����ײ��Metal MTLBuffer����
			VkExportMetalBufferInfoEXT& exportMetalBufferInfoEXT = exportMetalObjectsInfoEXT.exportMetalBufferInfoEXT;
			exportMetalBufferInfoEXT.memory;
			exportMetalBufferInfoEXT.mtlBuffer;//��������б�ʶ��VkDeviceMemory����memory ������VkPhysicalDevice �ײ��Metal id<MTLBuffer>���󡣸�ʵ�ֽ����ص��˳�Ա�е�MTLBuffer�����������VkDeviceMemory ������û���ҵ�MTLBuffer������������NULL

			//����Metal MTLBuffer ����Vulkan VkDeviceMemory ������Ҫ��VkMemoryAllocateInfo��pNext�м���VkImportMetalBufferInfoEXT
			VkImportMetalBufferInfoEXT importMetalBufferInfoEXT{};
			importMetalBufferInfoEXT.sType = VK_STRUCTURE_TYPE_IMPORT_METAL_BUFFER_INFO_EXT;
			importMetalBufferInfoEXT.pNext = nullptr;
			importMetalBufferInfoEXT.mtlBuffer = MTLBuffer_id{/*��������һ����Ч��MTLBuffer_id*/ }; //��һ��Ҫ���뵽VkDeviceMemory�ײ�� Metal id<MTLBuffer> object 


			//����  VkImage, VkImageView, �� VkBufferView����ײ��Metal MTLTexture ����
			VkExportMetalTextureInfoEXT& exportMetalTextureInfoEXT = exportMetalObjectsInfoEXT.exportMetalTextureInfoEXT;
			exportMetalTextureInfoEXT.image = VkImage{/*��������һ����Ч��VkImage���*/ };
			exportMetalTextureInfoEXT.imageView = VK_NULL_HANDLE;
			exportMetalTextureInfoEXT.bufferView = VK_NULL_HANDLE;
			exportMetalTextureInfoEXT.mtlTexture;//���������image��imageView �� bufferView ��ʶ��VkImage, VkImageView, �� VkBufferView��������ĵײ��Metal id<MTLTexture>����plane ָ��aspectMask����ʵ�ֽ����ص��˳�Ա�е�MTLTexture�����������VkImage, VkImageView, �� VkBufferView ������û���ҵ�MTLTexture������������NULL
			exportMetalTextureInfoEXT.plane = VK_IMAGE_ASPECT_PLANE_0_BIT; //ָ��  multi-planar��image �� imageView��plane ����



			//����һ������Metal MTLTexture ����Vulkan VkImage ������Ҫ��VkImageCreateInfo��pNext�м���VkImportMetalTextureInfoEXT��ÿһ��plane��Ҫ��Ӧ����һ��VkImportMetalTextureInfoEXT
			VkImportMetalTextureInfoEXT importMetalTextureInfoEXT{};
			importMetalTextureInfoEXT.sType = VK_STRUCTURE_TYPE_IMPORT_METAL_TEXTURE_INFO_EXT;
			importMetalTextureInfoEXT.pNext = nullptr;
			importMetalTextureInfoEXT.mtlTexture = MTLTexture_id{/*��������һ����Ч��MTLTexture_id*/ }; //��һ��Ҫ���뵽 VkImage�ײ�� Metal id<MTLTexture> object
			importMetalTextureInfoEXT.plane = VK_IMAGE_ASPECT_PLANE_0_BIT; //ָ�� ���Metal id<MTLTexture> object Ҫ������ plane��


			//����  VkImage ����ײ��Metal IOSurfaceRef ����
			VkExportMetalIOSurfaceInfoEXT& exportMetalIOSurfaceInfoEXT = exportMetalObjectsInfoEXT.exportMetalIOSurfaceInfoEXT;
			exportMetalIOSurfaceInfoEXT.image = VkImage{/*��������һ����Ч��VkImage���*/ };
			exportMetalIOSurfaceInfoEXT.ioSurface;//���������image ��ʶ��VkImage��������ĵײ��Metal IOSurfaceRef���󡣸�ʵ�ֽ����ص��˳�Ա�е�IOSurfaceRef�����������VkImage ������û���ҵ�IOSurfaceRef������������NULL


			//����Metal IOSurfaceRef ����Vulkan VkImage ������Ҫ��VkImageCreateInfo��pNext�м���VkImportMetalIOSurfaceInfoEXT
			VkImportMetalIOSurfaceInfoEXT importMetalIOSurfaceInfoEXT{};
			importMetalIOSurfaceInfoEXT.sType = VK_STRUCTURE_TYPE_IMPORT_METAL_IO_SURFACE_INFO_EXT;
			importMetalIOSurfaceInfoEXT.pNext = nullptr;
			importMetalIOSurfaceInfoEXT.ioSurface = IOSurfaceRef{/*��������һ����Ч��IOSurfaceRef*/ }; //��һ��Ҫ���뵽 VkImage�ײ�� Metal IOSurfaceRef object


			//����  VkSemaphore �� VkEvent ����ײ��Metal MTLSharedEvent ����
			VkExportMetalSharedEventInfoEXT& exportMetalSharedEventInfoEXT = exportMetalObjectsInfoEXT.exportMetalSharedEventInfoEXT;
			exportMetalSharedEventInfoEXT.semaphore = VkSemaphore{/*��������һ����Ч��VkSemaphore���*/ };
			exportMetalSharedEventInfoEXT.event = VK_NULL_HANDLE;
			exportMetalSharedEventInfoEXT.mtlSharedEvent;//���������semaphore �� event ��ʶ��VkSemaphore �� VkEvent��������ĵײ��Metal  id<MTLSharedEvent>���󡣸�ʵ�ֽ����ص��˳�Ա�е�MTLSharedEvent�����������VkSemaphore �� VkEvent ������û���ҵ�MTLSharedEvent������������NULL

			//����Metal MTLSharedEvent ����Vulkan VkSemaphore �� VkEvent ������Ҫ��VkSemaphoreCreateInfo �� VkEventCreateInfo��pNext�м���VkImportMetalSharedEventInfoEXT
			VkImportMetalSharedEventInfoEXT importMetalSharedEventInfoEXT{};
			importMetalSharedEventInfoEXT.sType = VK_STRUCTURE_TYPE_IMPORT_METAL_SHARED_EVENT_INFO_EXT;
			importMetalSharedEventInfoEXT.pNext = nullptr;
			importMetalSharedEventInfoEXT.mtlSharedEvent = MTLSharedEvent_id{/*��������һ����Ч��MTLSharedEvent_id*/ }; //��һ��Ҫ���뵽 VkSemaphore �� VkEvent�ײ�� Metal MTLSharedEvent object
			//���VkImportMetalSharedEventInfoEXT������Ϣ�ṹ��pNextͬʱ����VkImportMetalSharedEventInfoEXT��VkSemaphoreTypeCreateInfo��������� id<MTLSharedEvent> ����� signaledValue ��������ΪVkSemaphoreTypeCreateInfo������Ϣ�� initialValue��



		}
		exportMetalObjectsInfoEXT.pNext = nullptr;//�������һЩ��Ϣָ��Ҫ������Metal ��������
		/*
		VkExportMetalObjectsInfoEXT��Ч�÷�
		1.���pNext����һ��VkExportMetalDeviceInfoEXT����VkInstance�����ڴ�������vkCreateInstance��ʱ����VkInstanceCreateInfo��pNext�а���һ�� exportObjectTypeΪ VK_EXPORT_METAL_OBJECT_TYPE_METAL_DEVICE_BIT_EXT�� VkExportMetalObjectCreateInfoEXT
		2.���pNext����һ��VkExportMetalCommandQueueInfoEXT����VkInstance�����ڴ�������vkCreateInstance��ʱ����VkInstanceCreateInfo��pNext�а���һ�� exportObjectTypeΪ VK_EXPORT_METAL_OBJECT_TYPE_METAL_COMMAND_QUEUE_BIT_EXT�� VkExportMetalObjectCreateInfoEXT
		3.���pNext����һ��VkExportMetalBufferInfoEXT��������ݽṹ��memory�� VkDeviceMemory�����ڴ�������vkAllocateMemory��ʱ����VkMemoryAllocateInfo��pNext�а���һ�� exportObjectTypeΪ VK_EXPORT_METAL_OBJECT_TYPE_METAL_BUFFER_BIT_EXT�� VkExportMetalObjectCreateInfoEXT
		4.���pNext����һ��VkExportMetalTextureInfoEXT��������ݽṹ��image��imageView ��bufferView��һ������ΪVK_NULL_HANDLE
		5.���pNext����һ��VkExportMetalTextureInfoEXT����1�������image��ΪVK_NULL_HANDLE�����image ��������vkCreateImage ��VkImageCreateInfo��pNext�б������һ��VkExportMetalObjectCreateInfoEXT������exportObjectTypeΪVK_EXPORT_METAL_OBJECT_TYPE_METAL_TEXTURE_BIT_EXT
														  ��2�������imageView��bufferView��ΪVK_NULL_HANDLE�����imageView��bufferView ��������vkCreateImageView ��vkCreateBufferView ��VkImageCreateInfo��VkBufferViewCreateInfo ��pNext�б������һ��VkExportMetalObjectCreateInfoEXT������exportObjectTypeΪVK_EXPORT_METAL_OBJECT_TYPE_METAL_TEXTURE_BIT_EXT
		6.���pNext����һ��VkExportMetalTextureInfoEXT��������ýṹ�ĵ�image ��imageView ��ΪVK_NULL_HANDLE,��ýṹ�� plane��������ΪVK_IMAGE_ASPECT_PLANE_0_BIT, VK_IMAGE_ASPECT_PLANE_1_BIT, �� VK_IMAGE_ASPECT_PLANE_2_BIT
		7.���pNext����һ��VkExportMetalTextureInfoEXT������ýṹ���image��VkImage ������һ��multi-planar format����ýṹ�� plane��������ΪVK_IMAGE_ASPECT_PLANE_0_BIT
		8.���pNext����һ��VkExportMetalTextureInfoEXT������ýṹ���image��VkImage ����һ��ֻ������plane�� multi-planar format����ýṹ�� plane��������Ϊ VK_IMAGE_ASPECT_PLANE_2_BIT
		9.���pNext����һ��VkExportMetalTextureInfoEXT������ýṹ���imageView ��VkImageView ������һ��multi-planar format����ýṹ�� plane��������ΪVK_IMAGE_ASPECT_PLANE_0_BIT
		10.���pNext����һ��VkExportMetalTextureInfoEXT������ýṹ���imageView��VkImageView ����һ��ֻ������plane�� multi-planar format����ýṹ�� plane��������Ϊ VK_IMAGE_ASPECT_PLANE_2_BIT
		11.���pNext����һ��VkExportMetalIOSurfaceInfoEXT����ýṹ���image��VkImage ��������vkCreateImage ��VkImageCreateInfo��pNext�б������һ��VkExportMetalObjectCreateInfoEXT������exportObjectTypeΪVK_EXPORT_METAL_OBJECT_TYPE_METAL_IOSURFACE_BIT_EXT
		12.���pNext����һ��VkExportMetalSharedEventInfoEXT����ýṹ���semaphore�� event ��һ����ΪVK_NULL_HANDLE
		13.���pNext����һ��VkExportMetalSharedEventInfoEXT����1������ýṹ���semaphore��ΪVK_NULL_HANDLE���� �ýṹ���semaphore��VkSemaphore ��������VkSemaphoreCreateInfo ��VkSemaphoreCreateInfo��pNext�б������һ��VkExportMetalObjectCreateInfoEXT������exportObjectTypeΪVK_EXPORT_METAL_OBJECT_TYPE_METAL_SHARED_EVENT_BIT_EXT
															   ��2������ýṹ���event��ΪVK_NULL_HANDLE���� �ýṹ���event��VkEvent ��������vkCreateEvent ��VkEventCreateInfo��pNext�б������һ��VkExportMetalObjectCreateInfoEXT������exportObjectTypeΪVK_EXPORT_METAL_OBJECT_TYPE_METAL_SHARED_EVENT_BIT_EXT

		14.pNext�е�sType������Ψһ�ģ�����  VkExportMetalBufferInfoEXT, VkExportMetalCommandQueueInfoEXT, VkExportMetalIOSurfaceInfoEXT, VkExportMetalSharedEventInfoEXT, ��VkExportMetalTextureInfoEXT
		*/



		vkExportMetalObjectsEXT(device, &exportMetalObjectsInfoEXT);






	}


	_screen_buffer* screenBuffer;
	// QNX Screen buffer
	{
		//���� QNX Screen buffer��memory�� vulkan instance
		VkImportScreenBufferInfoQNX& importScreenBufferInfoQNX = memoryAllocateInfoEXT.importScreenBufferInfoQNX;
		importScreenBufferInfoQNX.buffer = screenBuffer;//��һ��ָ�� struct _screen_buffer ��ָ�룬��Ҫ����� QNX Screen buffer
		/*
		VkImportScreenBufferInfoQNX��Ч�÷�:
		1.��� buffer��Ϊ NULL����1�� QNX Screen Buffers����֧�ֵ��룬�μ�VkExternalImageFormatProperties ���� VkExternalBufferProperties
								  ��2��buffer����Ϊһ����Ч�� QNX Screen Buffers ָ��

		*/

		VkScreenBufferPropertiesQNX screenBufferPropertiesQNX{};
		screenBufferPropertiesQNX.sType = VK_STRUCTURE_TYPE_SCREEN_BUFFER_PROPERTIES_QNX;
		//VkScreenBufferPropertiesQNX.pNext
		VkScreenBufferFormatPropertiesQNX screenBufferFormatPropertiesQNX{};
		screenBufferFormatPropertiesQNX.sType = VK_STRUCTURE_TYPE_SCREEN_BUFFER_FORMAT_PROPERTIES_QNX;
		screenBufferFormatPropertiesQNX.pNext = nullptr;
		screenBufferFormatPropertiesQNX.format;//����Screen buffer format��Ӧ��Vulkan format�����û�е�Ч��Vulkan��ʽ��ΪVK_FORMAT_UNDIFIED����Чָ������� QNX Screen buffer ��һ���о���  QNX Screen Format Equivalence table��format����format����Ϊ���ж�Ӧ��format
		screenBufferFormatPropertiesQNX.externalFormat;//��һ��ʵ�ֶ�����ⲿ��ʽ��ʶ��������VkExternalFormatQNX������Ϊ�㡣
		screenBufferFormatPropertiesQNX.formatFeatures;//�����󶨵�vkGetScreenBufferPropertiesQNX��buffer������ʹ����external format��image�� format��������������� VK_FORMAT_FEATURE_SAMPLED_IMAGE_BIT��Ӧ�ð���VK_FORMAT_FEATURE_SAMPLED_IMAGE_FILTER_LINEAR_BIT ��VK_FORMAT_FEATURE_SAMPLED_IMAGE_YCBCR_CONVERSION_LINEAR_FILTER_BIT.
		screenBufferFormatPropertiesQNX.samplerYcbcrConversionComponents;//Ӧ������VkSamplerYcbcrConversionCreateInfo�е�component swizzle����
		screenBufferFormatPropertiesQNX.screenUsage;//��һ��ʵ�ֶ����QNX Screen Buffers���ⲿʹ�ñ�ʶ��
		screenBufferFormatPropertiesQNX.suggestedXChromaOffset;//����VkSamplerYcbcrConversionCreateInfo.��ʹ�õ�һ������� X chroma offset
		screenBufferFormatPropertiesQNX.suggestedYChromaOffset;//����VkSamplerYcbcrConversionCreateInfo.��ʹ�õ�һ������� Y chroma offset
		screenBufferFormatPropertiesQNX.suggestedYcbcrModel;//����VkSamplerYcbcrConversionCreateInfo�е�һ�������color model
		screenBufferFormatPropertiesQNX.suggestedYcbcrRange;//����VkSamplerYcbcrConversionCreateInfo.��ʹ�õ�һ��������ֵ��Χ

		screenBufferPropertiesQNX.pNext = &screenBufferFormatPropertiesQNX;//���԰���һ��VkScreenBufferFormatPropertiesQNX��ȡformat ����
		screenBufferPropertiesQNX.allocationSize;//�ⲿmemory �Ĵ�С
		screenBufferPropertiesQNX.memoryTypeBits;////��һ���������룬��Ӧÿһ��memory type ����VkPhysicalDeviceMemoryProperties.memoryTypes ??����ָ�� QNX Screen Buffers���Ա�����Ϊ������ .

		//��ȡ�����QNX Screen Buffers��memory ����
		vkGetScreenBufferPropertiesQNX(device, screenBuffer, &screenBufferPropertiesQNX);


	}



	//Device Group Memory Allocations
	//��� VkMemoryAllocateInfo ��pNext�к���һ��VkMemoryAllocateFlagsInfo��ָ�����ٸ�memory��ʵ���ᱻ���䣬��������flags��deviceMask
	VkMemoryAllocateFlagsInfo& memoryAllocateFlagsInfo = memoryAllocateInfoEXT.memoryAllocateFlagsInfo;
	memoryAllocateFlagsInfo.flags = VK_MEMORY_ALLOCATE_DEVICE_MASK_BIT;//�ǿ��Ʒ����VkMemoryAllocateFlagBits���ֵ��һ��λ���롣
	memoryAllocateFlagsInfo.deviceMask = 0;/*���߼��豸�е������豸�����룬ָʾ����ڱ�־��������VK_MEMORY_ALLOCATE_DEVICE_MASK_BIT��������������е�ÿ���豸�Ϸ����ڴ档���û������VK_MEMORY_ALLOCATE_DEVICE_MASK_BIT��VK_MEMORY_HEAP_MULTI_INSTANCE_BIT�Ƿ����ã�����������Ի���ÿ�������豸�����ڴ����ֻ����һ���ڴ棬�����Ǹ�ֵ����Ϊ1
	VkMemoryAllocateFlagBits��
	VK_MEMORY_ALLOCATE_DEVICE_MASK_BIT:  ָ��VkMemoryAllocateInfo����Ӧ�� memory ����VkMemoryAllocateFlagsInfo::deviceMask ָ����device�Ϸ���
	VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT:  ָ��VkMemoryAllocateInfo����Ӧ��memory ���Ը���һ����VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT������buffer �����У�������ڴ�������ͨ��vkGetDeviceMemoryOpaqueCaptureAddress������ȡһ��Opaque Address
	VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_CAPTURE_REPLAY_BIT:  ָ��VkMemoryAllocateInfo�������memory�ĵ�ַ�����ں��������б����û��߱�������trace capture �� replay��,��ϸ��Ϣ��VkBufferOpaqueCaptureAddressCreateInfo
	*/



	//Opaque Capture Address Allocation
	//��� VkMemoryAllocateInfo ��pNext�к���һ��VkMemoryOpaqueCaptureAddressAllocateInfo����ָ��
	// ��Ҫһ��������豸��ַ����VkMemoryAllocateInfo����Ӧ��memory ���䣬

	VkMemoryOpaqueCaptureAddressAllocateInfo& memoryOpaqueCaptureAddressAllocateInfo = memoryAllocateInfoEXT.memoryOpaqueCaptureAddressAllocateInfo;
	memoryOpaqueCaptureAddressAllocateInfo.opaqueCaptureAddress = NULL;//ΪΪ�ڴ���������paque capture address������ͨ��vkGetDeviceMemoryOpaqueCaptureAddress ��ȡ










	vkAllocateMemory(device, &memoryAllocateInfo, nullptr, &deviceMemory);
	/*
	vkAllocateMemory��Ч�÷�:
	1.pAllocateInfo->allocationSize����С�ڵ��� VkPhysicalDeviceMemoryProperties::memoryHeaps[memindex].size������memindex Ϊͨ��vkGetPhysicalDeviceMemoryProperties�ӿڲ�ѯ�� VkPhysicalDeviceMemoryProperties::memoryTypes[pAllocateInfo->memoryTypeIndex].heapIndex��VkPhysicalDeviceMemoryProperties��
	2.pAllocateInfo->memoryTypeIndex����С��ͨ��vkGetPhysicalDeviceMemoryProperties�ӿڲ�ѯ��VkPhysicalDeviceMemoryProperties::memoryTypeCount��
	3.��� deviceCoherentMemory ����û�п�����pAllocateInfo->memoryTypeIndex�Ͳ���ָ��һ��֧�� VK_MEMORY_PROPERTY_DEVICE_COHERENT_BIT_AMD���ڴ�����
	4.��ǰ��device�Ϸ�����ڴ��С����С��VkPhysicalDeviceLimits::maxMemoryAllocationCount

	*/

	vkFreeMemory(device, deviceMemory, nullptr);


	//host�˷���device�˷�����ڴ�
	//��VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT ������device �˵�memory ���ܱ�host�˷��ʣ�ӳ��ķ�ʽ��
	//����vkMapMemory��device�˵�memoryӳ�䵽host�˺���Ҫ��Ӧ��������host��device�Ը��ڴ��ͬ������
	void* mappedMemoryPointer;
	vkMapMemory(device, allocatedMemory, 0, 1, 0, &mappedMemoryPointer);/*
	vkMapMemory��Ч�÷�:
		1.offset: Ϊ����0��ʼ��memory ������ֽ�ƫ��ֵ������С��memory�Ĵ�С
		2.size: ��offset ƫ��ֵ��ʼ��ӳ���ڴ��ֽڴ�С,���ΪVK_WHOLE_SIZE��ʾ��offse��ʼ��memory�Ľ�β�������ΪVK_WHOLE_SIZE,�������� 0��С�ڵ��� memory�Ĵ�С��ȥ offset
		3.flags: ΪVkMemoryMapFlagBits���ֵ��λ����ָ��ӳ������Ķ��������������������VK_MEMORY_MAP_PLACED_BIT_EXT��VK_MEMORY_MAP_PLACED_BIT_EXTָ������ʵ�ֽ��ڴ�ӳ������ڿͻ���ָ���������ַ�ϣ�
							ͨ��VkMemoryMapPlacedInfoEXT::pPlacedAddress���滻�õ�ַ�ϵ��κ�����ӳ�䡣�˱�־������vkMapMemoryһ��ʹ�ã���Ϊû�а취ָ�����õ�ַ��
		4.ppData: ��һ��ָ��void*������ָ�룬���з���һ��ָ��ӳ�䷶Χ��ͷ�������ɷ��ʵ�ָ�롣���ָ���ȥoffset�������ٶ��뵽VkPhysicalDeviceLimits����minMemoryMapAlignment
		5.memory�������Ѿ���ӳ����ģ��Ҳ��ܴ���Ϊmultiple instance�ģ��ұ�����VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT����
	*/

	VkMemoryMapInfoKHR memoryMapInfoKHR{};
	memoryMapInfoKHR.sType = VK_STRUCTURE_TYPE_MEMORY_MAP_INFO_KHR;
		//VkMemoryMapInfoKHR.pNext
		{
			// Provided by VK_EXT_map_memory_placed
			typedef struct VkMemoryMapPlacedInfoEXT {
				VkStructureType sType;
				const void* pNext;
				void* pPlacedAddress;//ָ���ڴ�ӳ���ӳ�䵽����ָ���������ַ,����ΪNULL���VkMemoryMapInfoKHR.flags���� VK_MEMORY_MAP_PLACED_BIT_EXT,��ָ�ڴ������뵽������VkPhysicalDeviceMapMemoryPlacedPropertiesEXT::minPlacedMemoryMapAlignment����VkMemoryMapInfoKHR::size���޶����ڴ淶Χ���ܺ��κ����е�����ӳ���ص�
			} VkMemoryMapPlacedInfoEXT;//����ṹ��û�ж��壬�����ֶ�����

			VkMemoryMapPlacedInfoEXT memoryMapPlacedInfoEXT{};
			memoryMapPlacedInfoEXT.sType = VK_STRUCTURE_TYPE_MAX_ENUM;
			memoryMapPlacedInfoEXT.pNext = nullptr;
			memoryMapPlacedInfoEXT.pNext = nullptr;
		}
	memoryMapInfoKHR.pNext = nullptr;//���flags ����VK_MEMORY_MAP_PLACED_BIT_EXT������԰���һ��VkMemoryMapPlacedInfoEXT
	memoryMapInfoKHR.offset = 0;//Ϊ����0��ʼ��memory ������ֽ�ƫ��ֵ������С��memory�Ĵ�С
	memoryMapInfoKHR.size = 1;//��offset ƫ��ֵ��ʼ��ӳ���ڴ��ֽڴ�С,���ΪVK_WHOLE_SIZE��ʾ��offse��ʼ��memory�Ľ�β�������ΪVK_WHOLE_SIZE,�������� 0��С�ڵ��� memory�Ĵ�С��ȥ offset
	memoryMapInfoKHR.memory = VkDeviceMemory{/*��������һ����Ч��VkDeviceMemory*/}; //ָ����Ҫ��ӳ���VkDeviceMemory
	memoryMapInfoKHR.flags = 0;/*ΪVkMemoryMapFlagBits���ֵ��λ����ָ��ӳ������Ķ������������
			���������VK_MEMORY_MAP_PLACED_BIT_EXT����1��memoryMapPlaced���Ա��뿪��
													  ��2��pNext�б������һ��VkMemoryMapPlacedInfoEXT::pPlacedAddress ��ΪNULL��VkMemoryMapPlacedInfoEXT
													  ��3�����memoryMapRangePlaced û�п�������offset����Ϊ0��size ����Ϊ VK_WHOLE_SIZE �� VkMemoryAllocateInfo::allocationSize
													  ��4�����memoryMapRangePlaced ��������offset������뵽��������VkPhysicalDeviceMapMemoryPlacedPropertiesEXT::minPlacedMemoryMapAlignment
													  ��5�����size ��ΪVK_WHOLE_SIZE��size������뵽��������VkPhysicalDeviceMapMemoryPlacedPropertiesEXT::minPlacedMemoryMapAlignment
													  ��6�����size ΪVK_WHOLE_SIZE��VkMemoryAllocateInfo::allocationSize������뵽�������� VkPhysicalDeviceMapMemoryPlacedPropertiesEXT::minPlacedMemoryMapAlignment
													  ��7��memory �����Ǵ�handle ����ΪVK_EXTERNAL_MEMORY_HANDLE_TYPE_HOST_ALLOCATION_BIT_EXT ����VK_EXTERNAL_MEMORY_HANDLE_TYPE_HOST_MAPPED_FOREIGN_MEMORY_BIT_EXT �����

	*/
	vkMapMemory2KHR(device, &memoryMapInfoKHR, &mappedMemoryPointer);/*
	vkMapMemory2KHR��Ч�÷�:

		ppData: ��һ��ָ��void*������ָ�룬���з���һ��ָ��ӳ�䷶Χ��ͷ�������ɷ��ʵ�ָ�롣���ָ���ȥVkMemoryMapInfoKHR.offset�������ٶ��뵽VkPhysicalDeviceLimits����minMemoryMapAlignment
	*/



	
	VkMappedMemoryRange mappedMemoryRange{};
	mappedMemoryRange.sType = VK_STRUCTURE_TYPE_MAPPED_MEMORY_RANGE;
	mappedMemoryRange.pNext = nullptr;
	mappedMemoryRange.offset = 0;//Ϊ����0��ʼ��memory ������ֽ�ƫ��ֵ��
	mappedMemoryRange.size = 1;//��offset ƫ��ֵ��ʼ��ӳ���ڴ��ֽڴ�С,
	mappedMemoryRange.memory = VkDeviceMemory{/*��������һ����Ч��VkDeviceMemory*/ };//ָ�����������buffer
	/*
	VkMappedMemoryRange��Ч�÷�:
	1.memory �����Ѿ�ӳ�䵽host����
	2.���size ��ΪVK_WHOLE_SIZE��offset �� size ����ָ����ǰӳ���memory ��Χ�е�һ���ӷ�Χ
	3.���size ΪVK_WHOLE_SIZE��offset �����ڵ�ǰӳ���memory ��Χ��
	4.offset������VkPhysicalDeviceLimits::nonCoherentAtomSize�ı���
	5.���size ΪVK_WHOLE_SIZE��memory�ĵ�ǰӳ��Ľ�β����ΪVkPhysicalDeviceLimits::nonCoherentAtomSize������������Ϊmemory�Ľ�β
	6.���size ��ΪVK_WHOLE_SIZE��size������VkPhysicalDeviceLimits::nonCoherentAtomSize�ı�������offset����size�������memory�Ĵ�С

	*/



	//һ������ vkMapMemory ���� vkMapMemory2KHR�ɹ�ӳ����device memory,host��д�����ݵ�ӳ��ص�ָ��������ˢ��host�˵�cache��non-coherent device memory�ɵ���
	vkFlushMappedMemoryRanges(device, 1, &mappedMemoryRange);
	//һ������ vkMapMemory ���� vkMapMemory2KHR�ɹ�ӳ����device memory,host��д�����ݵ�ӳ��ص�ָ�������host�˵�cache��������Ч���ɵ���
	vkInvalidateMappedMemoryRanges(device, 1, &mappedMemoryRange);


	//���host�˲�����Ҫ����device�˵�memory������Ҫ����vkUnmapMemory���ӳ���ϵ
	vkUnmapMemory(device, deviceMemory);


	VkMemoryUnmapInfoKHR memoryUnmapInfoKHR{};
	memoryUnmapInfoKHR.sType = VK_STRUCTURE_TYPE_MEMORY_UNMAP_INFO_KHR;
	memoryUnmapInfoKHR.pNext = nullptr;
	memoryUnmapInfoKHR.flags = 0;/*��VkMemoryUnmapFlagBitsKHR���ֵ��λ���룬ָ���ڴ�ȡ��ӳ������ĸ��Ӳ�����VK_MEMORY_UNMAP_RESERVE_BIT_EXT ��ʾ ������ vkUnmapMemory2KHR ������ɺ��ڴ�ӳ�䵱ǰռ�õ������ַ��Χ���ֱ�����
									δ��ϵͳ�ڴ�ӳ����������vkMapMemory�� vkMapMemory2KHR���᷵�����跶Χ�ĵ�ַ�����ǵ�ַ��Χ���� �ͻ�����ʾ���ú�VK_MEMORY_MAP_PLACED_BIT_EXT��vkMapMemory2KHR �������ȼ۵� �ڴ�ӳ�� ��û�б������ˡ�  
									��������VK_MEMORY_UNMAP_RESERVE_BIT_EXTʱ���ڴ�ȡ��ӳ��������ܻ�ʧ�ܣ�����������£��ڴ���󽫱�������ӳ�䣬��vkUnmap�ڴ�2KHR������VK_ERROR_MEMORY_MAP_FAILED*/
	memoryUnmapInfoKHR.memory = VkDeviceMemory{/*��������һ����Ч��VkDeviceMemory*/ };//ָ�����������buffer
	/*
	VkMemoryUnmapInfoKHR��Ч�÷�:
	1.memory �����Ѿ�ӳ�䵽host����
	2.���flags������VK_MEMORY_UNMAP_RESERVE_BIT_EXT�� ��1��memoryUnmapReserve ���뿪��
													     ��2��memory �����Ǵ�handle ����ΪVK_EXTERNAL_MEMORY_HANDLE_TYPE_HOST_ALLOCATION_BIT_EXT ����VK_EXTERNAL_MEMORY_HANDLE_TYPE_HOST_MAPPED_FOREIGN_MEMORY_BIT_EXT �����

	*/


	vkUnmapMemory2KHR(device, &memoryUnmapInfoKHR);/*
	
	*/




	//Lazily Allocated Memory
	{
		//����ڴ�����ǴӴ���VK_MEMORY_PROPERTY_LAZILY_ALLOCATED_BITλ���Ķ��з���ģ���ô�ö����֧���ڴ������ʵ���ӳٵ��ṩ��ʵ���ύ���ڴ��С�������С���㣨��������Ĵ�Сһ���󣩣�����������Ҫ������ڴ�����������ӡ�
		//�����˴˱�־���ڴ�����ֻ����󶨵���ʹ�ñ�־����VK_IMAGE_USAGE_TRANSIENT_ATTACHMENT_BIT��VkImage

		VkDeviceSize lazySize;
		//Ҫȷ����ǰΪ�ڴ�����ύ���ӳٷ�����ڴ���
		vkGetDeviceMemoryCommitment(device, allocatedMemory, &lazySize);//��ָ��VkDeviceSizeֵ��ָ�룬���ص�ǰ�ڴ�����ӳٷ�����ڴ�����memory������VK_MEMORY_PROPERTY_LAZILY_ALLOCATED_BIT�� �ڴ����ʹ���
	
	}


	//Protected Memory ��p985


	//External Memory Handle Types
	{
	//Android Hardware Buffer ��p986
	
		//AHardwareBuffer Format Equivalence
		/*
				AHardwareBuffer  Format                  |             Vulkan Format
			AHARDWAREBUFFER_FORMAT_R8G8B8A8_UNORM        |      VK_FORMAT_R8G8B8A8_UNORM
			AHARDWAREBUFFER_FORMAT_R8G8B8X8_UNORM 1      |      VK_FORMAT_R8G8B8A8_UNORM
			AHARDWAREBUFFER_FORMAT_R8G8B8_UNORM          |      VK_FORMAT_R8G8B8_UNORM
			AHARDWAREBUFFER_FORMAT_R5G6B5_UNORM          |      VK_FORMAT_R5G6B5_UNORM_PACK16
			AHARDWAREBUFFER_FORMAT_R16G16B16A16_FLOAT    |      VK_FORMAT_R16G16B16A16_SFLOAT
			AHARDWAREBUFFER_FORMAT_R10G10B10A2_UNORM     |      VK_FORMAT_A2B10G10R10_UNORM_PACK32
			AHARDWAREBUFFER_FORMAT_D16_UNORM             |      VK_FORMAT_D16_UNORM
			AHARDWAREBUFFER_FORMAT_D24_UNORM             |      VK_FORMAT_X8_D24_UNORM_PACK32
			AHARDWAREBUFFER_FORMAT_D24_UNORM_S8_UINT     |      VK_FORMAT_D24_UNORM_S8_UINT
			AHARDWAREBUFFER_FORMAT_D32_FLOAT             |      VK_FORMAT_D32_SFLOAT
			AHARDWAREBUFFER_FORMAT_D32_FLOAT_S8_UINT     |      VK_FORMAT_D32_SFLOAT_S8_UINT
			AHARDWAREBUFFER_FORMAT_S8_UINT               |      VK_FORMAT_S8_UINT
		
		1���ּ�p989
		*/

	
		//AHardwareBuffer Usage Equivalence
		/*
		
		AHardwareBuffer Usage						|	Vulkan Usage ���� Creation Flag
		None										|	VK_IMAGE_USAGE_TRANSFER_SRC_BIT
		None										|	VK_IMAGE_USAGE_TRANSFER_DST_BIT
		AHARDWAREBUFFER_USAGE_GPU_SAMPLED_IMAGE		|	VK_IMAGE_USAGE_SAMPLED_BIT
		AHARDWAREBUFFER_USAGE_GPU_SAMPLED_IMAGE		|	VK_IMAGE_USAGE_INPUT_ATTACHMENT_BIT
		AHARDWAREBUFFER_USAGE_GPU_FRAMEBUFFER 3		|	VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT
		AHARDWAREBUFFER_USAGE_GPU_FRAMEBUFFER 3		|	VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT
		AHARDWAREBUFFER_USAGE_GPU_CUBE_MAP			|	VK_IMAGE_CREATE_CUBE_COMPATIBLE_BIT
		AHARDWAREBUFFER_USAGE_GPU_MIPMAP_COMPLETE	|	None 2
		AHARDWAREBUFFER_USAGE_PROTECTED_CONTENT		|	VK_IMAGE_CREATE_PROTECTED_BIT
		None										|	VK_IMAGE_CREATE_MUTABLE_FORMAT_BIT
		None										|	VK_IMAGE_CREATE_EXTENDED_USAGE_BIT
		AHARDWAREBUFFER_USAGE_GPU_DATA_BUFFER 4		|	VK_IMAGE_USAGE_STORAGE_BIT
		
		2,3,4���ּ�p990
		*/



	//QNX Screen Buffer
		
		// QNX Screen Buffer Format Equivalence
		/*
		
		QNX Screen Format				|	     Vulkan Format
		SCREEN_FORMAT_RGBA8888			|	 VK_FORMAT_B8G8R8A8_UNORM
		SCREEN_FORMAT_RGBX8888 1		|	 VK_FORMAT_B8G8R8A8_UNORM
		SCREEN_FORMAT_BGRA8888			|	 VK_FORMAT_R8G8B8A8_UNORM
		SCREEN_FORMAT_BGRX8888 1		|	 VK_FORMAT_R8G8B8A8_UNORM
		SCREEN_FORMAT_RGBA1010102		|	 VK_FORMAT_A2R10G10B10_UNORM_PACK32
		SCREEN_FORMAT_RGBX1010102 1		|	 VK_FORMAT_A2R10G10B10_UNORM_PACK32
		SCREEN_FORMAT_BGRA1010102		|	 VK_FORMAT_A2B10G10R10_UNORM_PACK32
		SCREEN_FORMAT_BGRX1010102 1		|	 VK_FORMAT_A2B10G10R10_UNORM_PACK32
		SCREEN_FORMAT_RGBA5551			|	 VK_FORMAT_A1R5G5B5_UNORM_PACK16
		SCREEN_FORMAT_RGBX5551 1		|	 VK_FORMAT_A1R5G5B5_UNORM_PACK16
		SCREEN_FORMAT_RGB565			|	 VK_FORMAT_R5G6B5_UNORM_PACK16
		SCREEN_FORMAT_RGB888			|	 VK_FORMAT_R8G8B8_UNORM
		
		1���ּ�p992
		
		*/



	}


	//Peer Memory Features
	{
		//peer memory�����߼��豸��һ�������豸�Ϸ�����ڴ棬Ȼ���һ�����߼��豸�Ĳ�ͬ�������豸����Դ���������з��ʡ�
		
		VkPeerMemoryFeatureFlags peerMemoryFeatureFlags;
		//��ȡpeer memory��α����ʵ�����,�����ӿڵȼ�
		vkGetDeviceGroupPeerMemoryFeatures(device, 0, 0, 1, &peerMemoryFeatureFlags);
		vkGetDeviceGroupPeerMemoryFeaturesKHR(device, 0, 0, 1, &peerMemoryFeatureFlags);/*
		vkGetDeviceGroupPeerMemoryFeatures��vkGetDeviceGroupPeerMemoryFeaturesKHR ��������
			heapIndex �Ǵ��з����ڴ���ڴ�ѵ�������
			localDeviceIndex ��ִ���ڴ���ʵ������豸���豸����
			remoteDeviceIndex ����Ҫ�����ڴ�������豸���豸������
			pPeerMemoryFeatures ��һ��ָ�� VkPeerMemoryFeatureFlags ��ָ�룬ָʾ�ѡ����غ�Զ���豸�����֧����Щ���͵��ڴ���ʡ�

		*/

		VkPeerMemoryFeatureFlagBits peerMemoryFeatureFlagBits;
		/*
		VK_PEER_MEMORY_FEATURE_COPY_SRC_BIT:  ָ��memory����ͨ����ΪvkCmdCopy* �����source ������
		VK_PEER_MEMORY_FEATURE_COPY_DST_BIT:  ָ��memory����ͨ����ΪvkCmdCopy* �����destination ������
		VK_PEER_MEMORY_FEATURE_GENERIC_SRC_BIT:  ָ��memory������Ϊ�κ�memory access type ����ȡ
		VK_PEER_MEMORY_FEATURE_GENERIC_DST_BIT:  ָ��memory������Ϊ�κ�memory access type ��д�룬��ΪShader atomics ��д
		*/
	}



	//Opaque Capture Address Query
	{
		VkDeviceMemoryOpaqueCaptureAddressInfo memoryOpaqueCaptureAddressInfo{};
		memoryOpaqueCaptureAddressInfo.sType = VK_STRUCTURE_TYPE_DEVICE_MEMORY_OPAQUE_CAPTURE_ADDRESS_INFO;
		memoryOpaqueCaptureAddressInfo.pNext = nullptr;
		memoryOpaqueCaptureAddressAllocateInfo.opaqueCaptureAddress;//����һ��64λ���豸�ڴ��opaque capture address�������ֵ��Ϊ0������ýӿڷ��ص�ֵӦ�ú͸�ֵ��ͬ

		//��ѯһ��64λ���豸�ڴ��opaque capture address�������ӿڵ�Ч
		vkGetDeviceMemoryOpaqueCaptureAddress(device, &memoryOpaqueCaptureAddressInfo);
		vkGetDeviceMemoryOpaqueCaptureAddressKHR(device, &memoryOpaqueCaptureAddressInfo);/*
		vkGetDeviceMemoryOpaqueCaptureAddress��vkGetDeviceMemoryOpaqueCaptureAddressKHR ��Ч�÷���
		1. bufferDeviceAddress���Ա��뿪��
		2. ���device �������ж�������豸���� bufferDeviceAddressMultiDevice ���Ա��뿪��
		
		*/
	}



}


NS_TEST_END