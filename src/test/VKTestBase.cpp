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

extern std::vector<VkLayerProperties> GetInstanceSurportLayers();
extern std::vector<VkExtensionProperties> GetInstanceSurportExtensions();
extern bool CheckExtensionSurport(const char* name, const std::vector<VkExtensionProperties>& exts);

void VKTestBase::PrepareContex()
{
	VkInstanceCreateInfo info{};
	info.sType = VkStructureType::VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	auto layers = GetInstanceSurportLayers();
	auto extenstions = GetInstanceSurportExtensions();
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

	//create device

	extern std::vector<VkPhysicalDevice> GetPhysicalDevices(VkInstance instance);
	extern std::vector<VkPhysicalDeviceProperties> GetPhysicalDeviceProperties(const std::vector<VkPhysicalDevice>&physicalDevices);
	extern std::vector<std::vector<VkQueueFamilyProperties>> GetPhysicalDeviceQueueFamilyPeoperties(const std::vector<VkPhysicalDevice>&physicalDevices);



	auto physicalDevices = GetPhysicalDevices(instance);
	auto physicalDeviceProperties = GetPhysicalDeviceProperties(physicalDevices);
	auto queueFamilyProperties = GetPhysicalDeviceQueueFamilyPeoperties(physicalDevices);
	int wantQueueFamilyIndex = -1, wantPhysicalDeviceIndex = -1;
	for (size_t i = 0; i < queueFamilyProperties.size(); i++)
	{
		for (size_t j = 0; j < queueFamilyProperties[i].size(); j++) {
			const auto& queueFamily = queueFamilyProperties[i][j];
			if (queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT && queueFamily.queueCount > 0 && queueFamily.queueFlags & VK_QUEUE_TRANSFER_BIT)
			{
				wantPhysicalDeviceIndex = i;
				wantQueueFamilyIndex = j;
				goto out;
			}

		}
	}
out:
	if (wantPhysicalDeviceIndex == -1 || wantQueueFamilyIndex == -1)
	{
		throw std::runtime_error("no surport device or queue family index");
	}

	physicalDevice = physicalDevices[wantPhysicalDeviceIndex];
	VkDeviceQueueCreateInfo queueCreateInfo{};
	queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
	queueCreateInfo.queueFamilyIndex = wantQueueFamilyIndex;
	queueCreateInfo.queueCount = queueFamilyProperties[wantPhysicalDeviceIndex][wantQueueFamilyIndex].queueCount;
	queueCreateInfo.flags = 0;
	std::vector<float> queueProperties(queueCreateInfo.queueCount, 1.0f);
	queueCreateInfo.pQueuePriorities = queueProperties.data();
	queueCreateInfo.pNext = nullptr;

	extern std::vector<VkExtensionProperties> GetPhysicalDeviceExtension(const VkPhysicalDevice physicalDevice);
	auto extensions = GetPhysicalDeviceExtension(physicalDevice);
	bool swapChainEXTSurport = CheckExtensionSurport(VK_KHR_SWAPCHAIN_EXTENSION_NAME, extensions);
	std::vector<const char*> wantExtensions;
	if (swapChainEXTSurport)
	{
		wantExtensions.push_back(VK_KHR_SWAPCHAIN_EXTENSION_NAME);
	}

	VkDeviceCreateInfo deviceCreateInfo{};
	deviceCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
	deviceCreateInfo.queueCreateInfoCount = 1;
	deviceCreateInfo.pQueueCreateInfos = &queueCreateInfo;
	deviceCreateInfo.pNext = nullptr;
	deviceCreateInfo.enabledExtensionCount = wantExtensions.size();
	deviceCreateInfo.ppEnabledExtensionNames = wantExtensions.data();
	deviceCreateInfo.pEnabledFeatures = nullptr;
	deviceCreateInfo.pEnabledFeatures = nullptr;
	deviceCreateInfo.enabledLayerCount = 0;
	deviceCreateInfo.ppEnabledLayerNames = nullptr;

	auto res = vkCreateDevice(physicalDevice, &deviceCreateInfo, nullptr, &device);
	if (res != VK_SUCCESS)
	{
		throw std::runtime_error("Create device failed");
	}
	queueFamilyIndex = wantQueueFamilyIndex;
	//获取队列
	queues.resize(queueCreateInfo.queueCount);
	for (uint32_t i = 0; i < queues.size(); i++)
	{
		vkGetDeviceQueue(device, queueFamilyIndex, i, &queues[i]);
	}












}

void VKTestBase::ClearContex()
{

	vkDestroyDevice(device, nullptr);

	auto PvkDestroyDebugUtilsMessengerEXT = (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT");
	if (PvkDestroyDebugUtilsMessengerEXT)
	{
		PvkDestroyDebugUtilsMessengerEXT(instance, messager, nullptr);
	}

	vkDestroyInstance(instance,nullptr);
}














NS_TEST_END