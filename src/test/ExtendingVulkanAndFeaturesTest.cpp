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
	//�µĺ�������ͨ���µ���չ�������µ��ں˰汾���Լ���չ���µİ汾��ӵ�vulkan

	//Instance and Device Functionality  �μ�p3713
	{
		/*
		ö��instance���Ի��߽���instanceΪ�����ĺ���Ϊinstance-level functionality.

		��device�������Ӷ����ɷ��ģ����߽���deviceΪ�����ĺ���Ϊdevice-level functionality.

		��VkPhysicalDevice�ɷ����߽���VkPhysicalDevice�ĺ�����instance-level����device-level functionality ȡ�����Ƿ�ָ��һ��instance extension����device extension�����⣬�о��豸���Ե���Ϊ��device-level functionality 
		
		*/


	}

	// Core Versions  �μ�p3713
	{
		// Version Numbers  �μ�p3714
		{
			/*
			vulkan �汾�����Ĳ��ֹ���: variant, major, minor �Լ� patch �汾
			
			variant �汾: ָ��ʵ��֧�ֵ�vulkan API�ı���汾����vulkan API��˵��ԶΪ0
			major �汾: ��ʾAPI�е�һ���ش�仯����������һ��ȫ�µĹ淶�汾
			minor �汾: ָ���ں��Ĺ淶�м������µĹ���
			patch �汾: ָ����ʾ�淶�а����˴����޸�����������ԸĽ�

			vulkan����İ汾���ܹ�32bit�����и�ʽΪ��ǰ���󣬴Ӹ�λ����λ: variant��3bit��, major��7bit��, minor��10bit�� �Լ� patch ��12bit��,��δӴ���İ汾������ȡ��Ӧ�İ汾��vulkan������һЩ��ȡ���� VK_VERSION_PATCH �������p3715
			
			vulkan������һЩָ���ض�vulkan �汾�ĺ��� VK_API_VERSION_1_0 ���μ�p3716
			*/



		}

		//Querying Version Support  �μ�p3717
		{
			// instance-level functionality�İ汾��ѯ
			uint32_t apiVersion = 0;
			vkEnumerateInstanceVersion(&apiVersion);


			// device-level functionality�İ汾��ѯ
			VkPhysicalDeviceProperties properties;
			vkGetPhysicalDeviceProperties(physicalDevice, &properties);
			properties.apiVersion;//���ز�ѯ֧�ֵ�api�汾
			
			VkPhysicalDeviceProperties2 properties2;
			vkGetPhysicalDeviceProperties2(physicalDevice, &properties2);
			properties2.properties.apiVersion;//���ز�ѯ֧�ֵ�api�汾
		}
	}


	//Layers  �μ�p3717
	{
		/*
		��һ��layer����ʱ����layer����Լ����뵽��Ӧ��vulkan��������ĵ������У�����չ���������Ϊ��������־��׷�٣�У���Լ��ṩ������չ�ȹ���
		*/
	
		//��ѯ���õ�layers
		uint32_t numLayer = 0;
		std::vector<VkLayerProperties> layerProperties;
		vkEnumerateInstanceLayerProperties(&numLayer, nullptr);
		layerProperties.resize(numLayer);
		vkEnumerateInstanceLayerProperties(&numLayer, layerProperties.data());//����ɹ�������һ��Ԫ��

		VkLayerProperties& layerProp = layerProperties[0];
		layerProp.layerName/*char [VK_MAX_EXTENSION_NAME_SIZE]���ͣ�VK_MAX_EXTENSION_NAME_SIZE = 256U*/;//Ϊ��layer�� null-terminated UTF-8���͵����ƣ��ɴ��� VkInstanceCreateInfo.ppEnabledLayerNames ��ָ��instanceҪ������layer����һЩlayer����ʽ�����ģ����ﲻ��Ҫָ��
		layerProp.specVersion = 0;//Ϊ��layerд���ĸ�vulkan�汾
		layerProp.implementationVersion = 0;//Ϊ��layer�Լ��İ汾������
		layerProp.description/*char [VK_MAX_DESCRIPTION_SIZE]���ͣ�VK_MAX_DESCRIPTION_SIZE = 256U*/;//Ϊ��layer�� null-terminated UTF-8���͵��������ṩ�������Ϣָ����layer


		// Device Layer Deprecation  �μ�p3719
		{
			/*
			���ڰ汾����layerΪinstance layer���� device layer����Щlayerֻ�ܺͶ�Ӧ�Ķ��󽻻������ڰ汾�������֡�
			*/

			//Ϊ�˼������ڵİ汾����ȡdevice��layer ����
			uint32_t numDeviceLayer = 0;
			std::vector<VkLayerProperties> deviceLayerProperties;
			vkEnumerateDeviceLayerProperties(physicalDevice, &numDeviceLayer, nullptr);
			deviceLayerProperties.resize(numDeviceLayer);
			vkEnumerateDeviceLayerProperties(physicalDevice, &numDeviceLayer, deviceLayerProperties.data());//���صĽ����vkEnumerateInstanceLayerProperties һ�������صĲ�������VkDeviceCreateInfo�е�ppEnabledLayerNames�Լ� enabledLayerCount��ʹ�ã�����������ʵ���Ϸ������ˣ�����Ч��
			


		}


	}


	// Extensions  �μ�p3721
	{
		/*
		extensions ���ܻᶨ���µ�vulkan��������ṹ�壬ö�ٵȡ�Ϊ�˱���Ŀ�ģ��Ѿ�ע���extensions�������Լ����ݽṹ�Ȼ��о���vulkan_core.h�У�extensions�ĵ��������ͨ����̬���ӣ���Ҫ��̬���ء�

		extension����չ���߸ı�Vulkan API����Ϊ��extensionӦ��Ҫ֧��vulkan��layers
		
		������VkInstanceCreateInfo.ppEnabledExtensionNames��ָ��extension����������instance extension�������� VkDeviceCreateInfo.ppEnabledExtensionNames��ָ��extension����������device extension
		
		����extensions���ı�����vulkan API����Ϊ��������extensions����Ϊ��ֻ���ø�extension��صĽӿڣ��ṹ�����Ч��
		*/


		// Instance Extensions  �μ�p3722
		{
			//Instance extensions ����µ� instance-level functionality��API��������ӵ�core��

			//��ѯ���õ�instance extensions
			uint32_t numExtension = 0;
			std::vector<VkExtensionProperties> extensionProperties{};

			//�о�Vulkanʵ�ֻ�����ʽ������layers�ṩ��extensions
			vkEnumerateInstanceExtensionProperties(nullptr, &numExtension, nullptr);
			extensionProperties.resize(numExtension);
			vkEnumerateInstanceExtensionProperties(nullptr, &numExtension, extensionProperties.data());//����ɹ�������һ��Ԫ��

			VkExtensionProperties &extensionProp = extensionProperties[0];
			extensionProp.specVersion = 0;//Ϊ��extension�Լ��İ汾������
			extensionProp.extensionName/*char [VK_MAX_EXTENSION_NAME_SIZE]���ͣ�VK_MAX_EXTENSION_NAME_SIZE = 256U*/;//Ϊ��extension�� null-terminated UTF-8���͵�����



			char layerName[5];//��������һ����Ч��layer name
			//�о�ָ��layer�ṩ��extensions
			vkEnumerateInstanceExtensionProperties(layerName, &numExtension, nullptr);
			extensionProperties.resize(numExtension);
			vkEnumerateInstanceExtensionProperties(layerName, &numExtension, extensionProperties.data());

		}

		//Device Extensions  �μ�p3723
		{
			//Device extensions ����µ� device-level functionality��API��������ӵ�core��

			//��ѯ���õ�device extensions

			uint32_t numDeviceExtension = 0;
			std::vector<VkExtensionProperties> deviceExtensionProperties{};

			//�о�Vulkanʵ�ֻ�����ʽ������layers�ṩ��extensions
			vkEnumerateDeviceExtensionProperties(physicalDevice,nullptr, &numDeviceExtension, nullptr);
			deviceExtensionProperties.resize(numDeviceExtension);
			vkEnumerateDeviceExtensionProperties(physicalDevice,nullptr, &numDeviceExtension, deviceExtensionProperties.data());

			char layerName[5];//��������һ����Ч��layer name
			//�о�ָ��layer�ṩ��extensions
			vkEnumerateDeviceExtensionProperties(physicalDevice,layerName, &numDeviceExtension, nullptr);
			deviceExtensionProperties.resize(numDeviceExtension);
			vkEnumerateDeviceExtensionProperties(physicalDevice,layerName, &numDeviceExtension, deviceExtensionProperties.data());

		}

	}



	//Extension Dependencies  �μ�p3726
	{
		/*
		һЩextensions���ڴӺ������������extension����ָ����vulkan�汾�������ڿ�����extensions֮ǰ����Ҫ������������extensions�Լ�ʹ�ö�Ӧ�汾��
		*/
	}


	//Compatibility Guarantees (Informative)  �μ�p3726
	{
		//Core Versions  ��Ҫ�����汾�ĸ������ְ���ʲô������е�����  �μ�p3726
		

		//Extensions    ��Ҫ�������뱣֤��Щextensions���Ժ���Щextensionsһ��ʹ���Լ�һЩ��ļ��ݹ���,  �μ�p3728  �� vk.xml ��������extensions��һЩ�����Ϣ


	}
}












NS_TEST_END