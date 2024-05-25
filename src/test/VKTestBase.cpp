#include "VKTestBase.h"
#include <vector>

NS_TEST_BEGIN

VKTestBase::VKTestBase()
{
	//PrepareContex();
}


VKTestBase::~VKTestBase()
{
	//ClearContex();
}

extern std::vector<VkLayerProperties> GetSurportLayers();
extern std::vector<VkExtensionProperties> GetSurportExtensions();
extern bool CheckExtensionSurport(const char* name, const std::vector<VkExtensionProperties>& exts);

void VKTestBase::PrepareContex()
{
	VkInstanceCreateInfo info{};
	info.sType = VkStructureType::VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	auto layers = GetSurportLayers();
	auto extenstions = GetSurportExtensions();
	std::vector<const char*> wantLayerNames;
	std::vector<const char*> wantExtensionNames;

	void** next = const_cast<void**>(&info.pNext);

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
	uint32_t apiVersion = 0;
	vkEnumerateInstanceVersion(&apiVersion);
	VkApplicationInfo appInfo{};
	appInfo.apiVersion = apiVersion;

	appInfo.applicationVersion = VK_MAKE_VERSION(0, 1, 0);
	appInfo.engineVersion = VK_MAKE_VERSION(0, 0, 0);
	appInfo.pApplicationName = "my_app";
	appInfo.pEngineName = "my_engine";
	appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	info.pApplicationInfo = &appInfo;








	auto res = vkCreateInstance(&info, nullptr, &instance);
	if (res != VK_SUCCESS)
	{
		_ASSERT(0);


	}


	//获取接口创建VkDebugUtilsMessengerEXT实例
	auto PvkCreateDebugUtilsMessengerEXT = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT");
	
	if (PvkCreateDebugUtilsMessengerEXT && suportDebugMessager)
	{

		auto res = PvkCreateDebugUtilsMessengerEXT(instance, &debugMessagerCreateInfo, nullptr, &messager);
		if (res != VK_SUCCESS)
		{
			_ASSERT(0);
		}


	}




}

void VKTestBase::ClearContex()
{
	auto PvkDestroyDebugUtilsMessengerEXT = (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT");
	if (PvkDestroyDebugUtilsMessengerEXT)
	{
		PvkDestroyDebugUtilsMessengerEXT(instance, messager, nullptr);
	}

	vkDestroyInstance(instance,nullptr);
}














NS_TEST_END