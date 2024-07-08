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
	memoryAllocateInfo.pNext = nullptr;
	memoryAllocateInfo.allocationSize = 1;//ֻ��Ҫ������ڴ���ֽ���
	memoryAllocateInfo.memoryTypeIndex = 0;//�Ǵ�vkGetPhysicalDeviceMemoryProperties��ȡ��VkPhysicalDeviceMemoryProperties�ṹ��memoryTypes�����е��ڴ����͵�������
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