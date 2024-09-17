#include "ExtendingVulkanAndFeaturesTest.h"
NS_TEST_BEGIN
ExtendingVulkanAndFeatuesTest::ExtendingVulkanAndFeatuesTest()
{
}

void ExtendingVulkanAndFeatuesTest::run()
{
}

ExtendingVulkanAndFeatuesTest::~ExtendingVulkanAndFeatuesTest()
{
}

void ExtendingVulkanAndFeatuesTest::ExtendingVulkanTest()
{
	//新的函数可以通过新的拓展，或者新的内核版本，以及拓展的新的版本添加到vulkan

	//Instance and Device Functionality  参见p3713
	{
		/*
		枚举instance属性或者接受instance为参数的函数为instance-level functionality.

		从device或者其子对象派发的，或者接受device为参数的函数为device-level functionality.

		从VkPhysicalDevice派发或者接受VkPhysicalDevice的函数是instance-level还是device-level functionality 取决与是否指定一个instance extension还是device extension，另外，列举设备属性的认为是device-level functionality 
		
		*/


	}

	// Core Versions  参见p3713
	{
		// Version Numbers  参见p3714
		{
			/*
			vulkan 版本号由四部分构成: variant, major, minor 以及 patch 版本
			
			variant 版本: 指明实现支持的vulkan API的变体版本，对vulkan API来说永远为0
			major 版本: 表示API中的一个重大变化，它将包含一个全新的规范版本
			minor 版本: 指明在核心规范中加入了新的功能
			patch 版本: 指明表示规范中包含了错误修复、澄清和语言改进

			vulkan打包的版本号总共32bit，其中格式为从前往后，从高位到低位: variant（3bit）, major（7bit）, minor（10bit） 以及 patch （12bit）,如何从打包的版本号中提取对应的版本，vulkan定义了一些提取宏如 VK_VERSION_PATCH ，具体见p3715
			
			vulkan定义了一些指定特定vulkan 版本的宏如 VK_API_VERSION_1_0 ，参见p3716
			*/



		}

		//Querying Version Support  参见p3717
		{
			// instance-level functionality的版本查询
			uint32_t apiVersion = 0;
			vkEnumerateInstanceVersion(&apiVersion);


			// device-level functionality的版本查询
			VkPhysicalDeviceProperties properties;
			vkGetPhysicalDeviceProperties(physicalDevice, &properties);
			properties.apiVersion;//返回查询支持的api版本
			
			VkPhysicalDeviceProperties2 properties2;
			vkGetPhysicalDeviceProperties2(physicalDevice, &properties2);
			properties2.properties.apiVersion;//返回查询支持的api版本
		}
	}


	//Layers  参见p3717
	{
		/*
		当一个layer启用时，该layer会把自己插入到对应的vulkan函数命令的调用链中，以扩展该命令的行为，用于日志，追踪，校验以及提供额外拓展等功能
		*/
	
		//查询可用的layers
		uint32_t numLayer = 0;
		std::vector<VkLayerProperties> layerProperties;
		vkEnumerateInstanceLayerProperties(&numLayer, nullptr);
		layerProperties.resize(numLayer);
		vkEnumerateInstanceLayerProperties(&numLayer, layerProperties.data());//假设成功返回了一个元素

		VkLayerProperties& layerProp = layerProperties[0];
		layerProp.layerName/*char [VK_MAX_EXTENSION_NAME_SIZE]类型，VK_MAX_EXTENSION_NAME_SIZE = 256U*/;//为该layer的 null-terminated UTF-8类型的名称，可传入 VkInstanceCreateInfo.ppEnabledLayerNames 中指明instance要开启的layer，有一些layer是隐式开启的，这里不需要指定
		layerProp.specVersion = 0;//为该layer写入哪个vulkan版本
		layerProp.implementationVersion = 0;//为该layer自己的版本，递增
		layerProp.description/*char [VK_MAX_DESCRIPTION_SIZE]类型，VK_MAX_DESCRIPTION_SIZE = 256U*/;//为该layer的 null-terminated UTF-8类型的描述，提供额外的信息指定该layer


		// Device Layer Deprecation  参见p3719
		{
			/*
			早期版本区分layer为instance layer还是 device layer，这些layer只能和对应的对象交互，后期版本不再区分。
			*/

			//为了兼容早期的版本，获取device的layer 属性
			uint32_t numDeviceLayer = 0;
			std::vector<VkLayerProperties> deviceLayerProperties;
			vkEnumerateDeviceLayerProperties(physicalDevice, &numDeviceLayer, nullptr);
			deviceLayerProperties.resize(numDeviceLayer);
			vkEnumerateDeviceLayerProperties(physicalDevice, &numDeviceLayer, deviceLayerProperties.data());//返回的结果和vkEnumerateInstanceLayerProperties 一样，返回的参数可在VkDeviceCreateInfo中的ppEnabledLayerNames以及 enabledLayerCount中使用，但两个参数实际上废弃掉了，是无效的
			


		}


	}


	// Extensions  参见p3721
	{
		/*
		extensions 可能会定义新的vulkan调用命令，结构体，枚举等。为了编译目的，已经注册的extensions的命令以及数据结构等会列举在vulkan_core.h中，extensions的调用命令不能通过静态链接，需要动态加载。

		extension会拓展或者改变Vulkan API的行为，extension应该要支持vulkan的layers
		
		可以在VkInstanceCreateInfo.ppEnabledExtensionNames中指定extension名字来开启instance extension，可以在 VkDeviceCreateInfo.ppEnabledExtensionNames中指定extension名字来开启device extension
		
		开启extensions不改变现有vulkan API的行为或者其他extensions的行为，只是让该extension相关的接口，结构体等有效。
		*/


		// Instance Extensions  参见p3722
		{
			//Instance extensions 添加新的 instance-level functionality到API，不是添加到core中

			//查询可用的instance extensions
			uint32_t numExtension = 0;
			std::vector<VkExtensionProperties> extensionProperties{};

			//列举Vulkan实现或者隐式开启的layers提供的extensions
			vkEnumerateInstanceExtensionProperties(nullptr, &numExtension, nullptr);
			extensionProperties.resize(numExtension);
			vkEnumerateInstanceExtensionProperties(nullptr, &numExtension, extensionProperties.data());//假设成功返回了一个元素

			VkExtensionProperties &extensionProp = extensionProperties[0];
			extensionProp.specVersion = 0;//为该extension自己的版本，递增
			extensionProp.extensionName/*char [VK_MAX_EXTENSION_NAME_SIZE]类型，VK_MAX_EXTENSION_NAME_SIZE = 256U*/;//为该extension的 null-terminated UTF-8类型的名称



			char layerName[5];//假设这是一个有效的layer name
			//列举指定layer提供的extensions
			vkEnumerateInstanceExtensionProperties(layerName, &numExtension, nullptr);
			extensionProperties.resize(numExtension);
			vkEnumerateInstanceExtensionProperties(layerName, &numExtension, extensionProperties.data());

		}

		//Device Extensions  参见p3723
		{
			//Device extensions 添加新的 device-level functionality到API，不是添加到core中

			//查询可用的device extensions

			uint32_t numDeviceExtension = 0;
			std::vector<VkExtensionProperties> deviceExtensionProperties{};

			//列举Vulkan实现或者隐式开启的layers提供的extensions
			vkEnumerateDeviceExtensionProperties(physicalDevice,nullptr, &numDeviceExtension, nullptr);
			deviceExtensionProperties.resize(numDeviceExtension);
			vkEnumerateDeviceExtensionProperties(physicalDevice,nullptr, &numDeviceExtension, deviceExtensionProperties.data());

			char layerName[5];//假设这是一个有效的layer name
			//列举指定layer提供的extensions
			vkEnumerateDeviceExtensionProperties(physicalDevice,layerName, &numDeviceExtension, nullptr);
			deviceExtensionProperties.resize(numDeviceExtension);
			vkEnumerateDeviceExtensionProperties(physicalDevice,layerName, &numDeviceExtension, deviceExtensionProperties.data());

		}

	}



	//Extension Dependencies  参见p3726
	{
		/*
		一些extensions会在从函数上以来别的extension或者指定的vulkan版本，所以在开启该extensions之前，需要开启其以来的extensions以及使用对应版本。
		*/
	}


	//Compatibility Guarantees (Informative)  参见p3726
	{
		//Core Versions  主要描述版本的各个部分按照什么规则进行递增，  参见p3726
		

		//Extensions    主要描述必须保证哪些extensions可以和哪些extensions一起使用以及一些别的兼容规则,  参见p3728  ， vk.xml 中描述了extensions的一些别的信息


	}
}












NS_TEST_END