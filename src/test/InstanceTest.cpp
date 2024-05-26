#include "InstanceTest.h"
#include <vector>

NS_TEST_BEGIN


//获得instance的api版本
uint32_t GetApiVersion()
{

	uint32_t instanceApiVersion = 0;
	vkEnumerateInstanceVersion(&instanceApiVersion);
	std::cout << "Instance API Version: " << std::endl;
	std::cout <<  " varient : " << VK_API_VERSION_VARIANT(instanceApiVersion) 
		      <<  " major : " << VK_VERSION_MAJOR(instanceApiVersion) 
			  <<  " minor : " << VK_VERSION_MINOR(instanceApiVersion) 
		      << " patch : " << VK_VERSION_PATCH(instanceApiVersion) << std::endl;
	return instanceApiVersion;


}
std::vector<VkLayerProperties> GetInstanceSurportLayers() {
	std::vector<VkLayerProperties> layerProps;
	uint32_t numLayer = 0;
	vkEnumerateInstanceLayerProperties(&numLayer, nullptr);
	layerProps.resize(numLayer);
	vkEnumerateInstanceLayerProperties(&numLayer, layerProps.data());
	for (auto layer : layerProps)
	{
		std::cout << "Layer Name: " << layer.layerName << std::endl;
		std::cout << "Layer Description: " << layer.description << std::endl;
		std::cout << "Layer Spec Version: " << layer.specVersion << std::endl;
		std::cout << "Layer Impl Version: " << layer.implementationVersion << std::endl;
		std::cout << "-----------------------------------" << std::endl;

	}
	return layerProps;
}
std::vector<VkExtensionProperties> GetInstanceSurportExtensions() {
	//获取核心层的拓展
	std::vector<VkExtensionProperties> extensionProps;
	uint32_t numExtension = 0;
	vkEnumerateInstanceExtensionProperties(nullptr, &numExtension, nullptr);
	extensionProps.resize(numExtension);
	vkEnumerateInstanceExtensionProperties(nullptr, &numExtension, extensionProps.data());
	for (auto extension : extensionProps)
	{
		std::cout << "Extension Name: " << extension.extensionName << std::endl;
		std::cout << "Extension Spec Version: " << extension.specVersion << std::endl;
		std::cout << "-----------------------------------" << std::endl;
	}
	//获取单个层的拓展
	//auto layers = GetSurportLayers();

	//for (auto layer : layers)
	//{
	//	std::cout << "Layer Extension Name: "  << std::endl;
	//	uint32_t numExtension = 0;
	//	vkEnumerateInstanceExtensionProperties(layer.layerName, &numExtension, nullptr);
	//	extensionProps.resize(numExtension);
	//	vkEnumerateInstanceExtensionProperties(layer.layerName, &numExtension, extensionProps.data());
	//	for (auto extension : extensionProps)
	//	{
	//		std::cout << "Extension Name: " << extension.extensionName << std::endl;
	//		std::cout << "Extension Spec Version: " << extension.specVersion << std::endl;
	//		std::cout << "-----------------------------------" << std::endl;
	//	}

	//}
	return extensionProps;

}

bool CheckExtensionSurport(const char* extensionName,const  std::vector<VkExtensionProperties>& extensions)
{


	for (auto extension : extensions)
	{
		if (strcmp(extension.extensionName, extensionName) == 0)
		{
			return true;
		}
	}
	return false;
}

bool CheckLayerSurport(const char* layerName,const std::vector<VkLayerProperties>& layers)
{
	for (auto layer : layers)
	{
		if (strcmp(layer.layerName, layerName) == 0)
		{
			return true;
		}
	}
	return false;
}
class Allocator {
public:

	void* Alloc(size_t size, size_t alignment, VkSystemAllocationScope allocationScope)
	{
		return malloc(size);
	}
	void Free(void* pMemory)
	{
		free(pMemory);
	}
	void* Realloc(void* pOriginal, size_t size, size_t alignment, VkSystemAllocationScope allocationScope)
	{
		return realloc(pOriginal, size);
	}
	void* InternalAlloc(size_t size, VkSystemAllocationScope allocationScope)
	{
		return malloc(size);
	}
	void InternalFree(void* pMemory)
	{
		free(pMemory);
	}



};

static VkInstance CreateInstanceTest() {
	VkInstanceCreateInfo info{};
	info.sType = VkStructureType::VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	auto layers = GetInstanceSurportLayers();
	auto extenstions = GetInstanceSurportExtensions();
	std::vector<const char*> wantLayerNames;
	std::vector<const char*> wantExtensionNames;
	//debug report ext
	auto surportDebugReport = CheckExtensionSurport(VK_EXT_DEBUG_REPORT_EXTENSION_NAME, extenstions);
	VkDebugReportCallbackCreateInfoEXT debugCreateInfo{};
	void** next = const_cast<void**>(&info.pNext);
	if (surportDebugReport)
	{
		wantExtensionNames.push_back(VK_EXT_DEBUG_REPORT_EXTENSION_NAME);
		
		debugCreateInfo.sType = VK_STRUCTURE_TYPE_DEBUG_REPORT_CALLBACK_CREATE_INFO_EXT;
		debugCreateInfo.flags = VK_DEBUG_REPORT_INFORMATION_BIT_EXT | VK_DEBUG_REPORT_ERROR_BIT_EXT | VK_DEBUG_REPORT_WARNING_BIT_EXT;
		debugCreateInfo.pUserData = nullptr;
		debugCreateInfo.pfnCallback = [](VkDebugReportFlagsEXT flags, VkDebugReportObjectTypeEXT objectType, uint64_t object, size_t location, int32_t messageCode, const char* pLayerPrefix, const char* pMessage, void* pUserData) {
			std::cout << "Debug Report: " << pMessage << std::endl;
			return VK_FALSE;
		};
		*next = &debugCreateInfo;
		next = const_cast<void**>(&debugCreateInfo.pNext);
		//info.pNext = &debugCreateInfo;
	}

	//debug message ext     debug report ext 的升级版
	auto suportDebugMessager = CheckExtensionSurport(VK_EXT_DEBUG_UTILS_EXTENSION_NAME, extenstions);
	VkDebugUtilsMessengerCreateInfoEXT	debugMessagerCreateInfo{};
	debugMessagerCreateInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
	if (suportDebugMessager)
	{
		wantExtensionNames.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
		debugMessagerCreateInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT;
		debugMessagerCreateInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT;
		debugMessagerCreateInfo.pfnUserCallback = [](VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageTypes, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData) {
			std::cout << "Debug Messager: " << pCallbackData->pMessage << std::endl;
			return VK_FALSE;
		};
		*next = &debugMessagerCreateInfo;
		next = const_cast<void**>(&debugMessagerCreateInfo.pNext);
	}

	info.enabledExtensionCount = wantExtensionNames.size();
	info.ppEnabledExtensionNames = wantExtensionNames.data();
	info.ppEnabledLayerNames = wantExtensionNames.data();
	info.enabledLayerCount = wantLayerNames.size();
	info.flags = VK_INSTANCE_CREATE_ENUMERATE_PORTABILITY_BIT_KHR;
	VkApplicationInfo appInfo{};
	appInfo.apiVersion = GetApiVersion();
		
	appInfo.applicationVersion = VK_MAKE_VERSION(0, 1, 0);
	appInfo.engineVersion = VK_MAKE_VERSION(0, 0, 0);
	appInfo.pApplicationName = "my_app";
	appInfo.pEngineName = "my_engine";
	appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	info.pApplicationInfo = &appInfo;
	VkInstance instance{VK_NULL_HANDLE};

	//验证层控制
	VkValidationFlagsEXT validationFlags{};
	validationFlags.sType = VK_STRUCTURE_TYPE_VALIDATION_FLAGS_EXT;
	validationFlags.disabledValidationCheckCount = 1;
	std::vector<VkValidationCheckEXT> checks;
	checks.push_back(VkValidationCheckEXT::VK_VALIDATION_CHECK_SHADERS_EXT);
	validationFlags.pDisabledValidationChecks = checks.data();
	*next = &validationFlags;
	next = const_cast<void**>(&validationFlags.pNext);


	//验证特性控制 通过验证特性控制来控制验证层的行为
	VkValidationFeaturesEXT validationFeatures{};
	validationFeatures.sType = VK_STRUCTURE_TYPE_VALIDATION_FEATURES_EXT;
	std::vector<VkValidationFeatureDisableEXT> validationFeatureDisables;
	std::vector<VkValidationFeatureEnableEXT> validationFeatureEnables;
	validationFeatureEnables.push_back(VkValidationFeatureEnableEXT::VK_VALIDATION_FEATURE_ENABLE_GPU_ASSISTED_EXT);
	validationFeatureEnables.push_back(VkValidationFeatureEnableEXT::VK_VALIDATION_FEATURE_ENABLE_GPU_ASSISTED_RESERVE_BINDING_SLOT_EXT);
	validationFeatureEnables.push_back(VkValidationFeatureEnableEXT::VK_VALIDATION_FEATURE_ENABLE_DEBUG_PRINTF_EXT);
	validationFeatureDisables.push_back(VkValidationFeatureDisableEXT::VK_VALIDATION_FEATURE_DISABLE_SHADER_VALIDATION_CACHE_EXT);
	validationFeatures.disabledValidationFeatureCount = validationFeatureDisables.size();
	validationFeatures.enabledValidationFeatureCount = validationFeatureEnables.size();
	validationFeatures.pEnabledValidationFeatures = validationFeatureEnables.data();
	validationFeatures.pDisabledValidationFeatures = validationFeatureDisables.data();
	*next = &validationFeatures;
	next = const_cast<void**>(&validationFeatures.pNext);

	//驱动加载列表 暂不测试
	VkDirectDriverLoadingListLUNARG directDriverLoadingList{};
	directDriverLoadingList.sType = VK_STRUCTURE_TYPE_DIRECT_DRIVER_LOADING_LIST_LUNARG;

	//VkExportMetalObjectCreateInfoEXT 暂不测试


	//VkLayerSettingsCreateInfoEXT 暂不测试


	//自定义分配器测试
	Allocator m_allocator;
	//VkAllocationCallbacks 的pfnAllocation pfnFree pfnReallocation 不能为空，pfnInternalAllocation pfnInternalFree要么同时为空，要么同时不为空
	VkAllocationCallbacks allocationCallbacks{};
	allocationCallbacks.pfnAllocation = [](void* pUserData, size_t size, size_t alignment, VkSystemAllocationScope allocationScope) {
		//return reinterpret_cast<Allocator*>(pUserData)->Alloc(size,alignment,allocationScope);
		return malloc(size);
	};
	allocationCallbacks.pfnFree = [](void* pUserData, void* pMemory) {
		free(pMemory);
	};
	allocationCallbacks.pfnInternalAllocation = nullptr;
	allocationCallbacks.pfnInternalFree = nullptr;
	allocationCallbacks.pfnReallocation = [](
		void* pUserData,
		void* pOriginal,
		size_t                                      size,
		size_t                                      alignment,
		VkSystemAllocationScope                     allocationScope) {
			return realloc(pOriginal, size);
	};
	allocationCallbacks.pUserData = &m_allocator;


	auto res = vkCreateInstance(&info, &allocationCallbacks, &instance);
	if (res != VK_SUCCESS)
	{
		_ASSERT(0);


	}
	

	//获取接口创建VkDebugUtilsMessengerEXT实例
	auto PvkCreateDebugUtilsMessengerEXT = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT");
	VkDebugUtilsMessengerEXT messager{ VK_NULL_HANDLE };
	if (PvkCreateDebugUtilsMessengerEXT && suportDebugMessager)
	{

		auto res = PvkCreateDebugUtilsMessengerEXT(instance, &debugMessagerCreateInfo, nullptr, &messager);
		if (res != VK_SUCCESS)
		{
			_ASSERT(0);
		}
		auto PvkDestroyDebugUtilsMessengerEXT = (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT");
		if (PvkDestroyDebugUtilsMessengerEXT)
		{
			PvkDestroyDebugUtilsMessengerEXT(instance, messager, &allocationCallbacks);
		}

	}


	//获取接口创建VkDebugReportCallbackEXT实例
	auto PvkCreateDebugReportCallbackEXT = (PFN_vkCreateDebugReportCallbackEXT)vkGetInstanceProcAddr(instance, "vkCreateDebugReportCallbackEXT");
	VkDebugReportCallbackEXT callback{ VK_NULL_HANDLE };
	if (PvkCreateDebugReportCallbackEXT && surportDebugReport)
	{

		auto res = PvkCreateDebugReportCallbackEXT(instance, &debugCreateInfo, nullptr, &callback);
		if (res != VK_SUCCESS)
		{
			_ASSERT(0);
		}

		auto PvkDestroyDebugReportCallbackEXT = (PFN_vkDestroyDebugReportCallbackEXT)vkGetInstanceProcAddr(instance, "vkDestroyDebugReportCallbackEXT");
		if (PvkDestroyDebugReportCallbackEXT)
		{
			PvkDestroyDebugReportCallbackEXT(instance, callback, &allocationCallbacks);
		}
	}
	//vkCreateDebugUtilsMessengerEXT(instance, &debugMessagerCreateInfo, nullptr, nullptr);
	



	vkDestroyInstance(instance, &allocationCallbacks);

	//VkExportMetalObjectCreateInfoEXT exportMetalObjectCreateInfo{};

	return nullptr;
}


InstanceTest::InstanceTest() :VKTestBase()
{
}

void InstanceTest::run()
{
	//auto apiVEersion = GetApiVersion();
	CreateInstanceTest();
}





NS_TEST_END