#include "DeviceAndQueueTest.h"
NS_TEST_BEGIN










DeviceAndQueueTest::DeviceAndQueueTest()
{
	PrepareContex();
}
DeviceAndQueueTest::~DeviceAndQueueTest()
{
	ClearContex();
}

std::vector<VkPhysicalDevice> GetPhysicalDevices(VkInstance instance)
{
	uint32_t count = 0;
	vkEnumeratePhysicalDevices(instance, &count, nullptr);
	std::vector<VkPhysicalDevice> devices(count);
	vkEnumeratePhysicalDevices(instance, &count, devices.data());
	return devices;
}
std::vector<VkPhysicalDeviceProperties> GetPhysicalDeviceProperties(const std::vector<VkPhysicalDevice>& physicalDevices)
{
	std::vector<VkPhysicalDeviceProperties> properties;
	properties.resize(physicalDevices.size());
	for (uint32_t i = 0; i < properties.size(); i++)
	{
		vkGetPhysicalDeviceProperties(physicalDevices[i], &properties[i]);
	}
	return properties;

}

std::vector<VkPhysicalDeviceProperties2> GetPhysicalDeviceProperties2(const std::vector<VkPhysicalDevice>& physicalDevices) {
	std::vector<VkPhysicalDeviceProperties2> properties2;
	properties2.resize(physicalDevices.size());
	for (uint32_t i = 0; i < properties2.size(); i++)
	{
		vkGetPhysicalDeviceProperties2(physicalDevices[i], &properties2[i]);
	}
	return properties2;


}



void DeviceAndQueueTest::run()
{


	//TODO: ±àÐ´²âÊÔÓÃÀý´úÂë
	auto physicalDevices = GetPhysicalDevices(instance);
	auto properties = GetPhysicalDeviceProperties(physicalDevices);

	for (uint32_t i = 0; i < properties.size(); i++)
	{
		auto& prop = properties[i];
		std::cout << "Device Name: " << prop.deviceName << std::endl;
		std::cout << "Device Type: " << prop.deviceType << std::endl;
		std::cout << "API Version: " << prop.apiVersion << std::endl;
		std::cout << "Driver Version: " << prop.driverVersion << std::endl;
		std::cout << "Vendor ID: " << prop.vendorID << std::endl;
		std::cout << "Device ID: " << prop.deviceID << std::endl;
		std::cout << "Device UUID: " << prop.pipelineCacheUUID << std::endl;
		std::cout << "Device Limits: " << std::endl;
		std::cout << "maxImageDimension1D: " << prop.limits.maxImageDimension1D << std::endl;
		std::cout << "maxImageDimension2D: " << prop.limits.maxImageDimension2D << std::endl;
		std::cout << "maxImageDimension3D: " << prop.limits.maxImageDimension3D << std::endl;
		std::cout << "maxImageDimensionCube: " << prop.limits.maxImageDimensionCube << std::endl;
		std::cout << "maxImageArrayLayers: " << prop.limits.maxImageArrayLayers << std::endl;
		std::cout << "maxTexelBufferElements: " << prop.limits.maxTexelBufferElements << std::endl;
		std::cout << "maxUniformBufferRange: " << prop.limits.maxUniformBufferRange << std::endl;
		std::cout << "maxStorageBufferRange: " << prop.limits.maxStorageBufferRange << std::endl;
		std::cout << "maxPushConstantsSize: " << prop.limits.maxPushConstantsSize << std::endl;
		std::cout << "maxMemoryAllocationCount: " << prop.limits.maxMemoryAllocationCount << std::endl;
		std::cout << "maxSamplerAllocationCount: " << prop.limits.maxSamplerAllocationCount << std::endl;
		std::cout << "bufferImageGranularity: " << prop.limits.bufferImageGranularity << std::endl;
		std::cout << "sparseAddressSpaceSize: " << prop.limits.sparseAddressSpaceSize << std::endl;
	}

	auto properties2 = GetPhysicalDeviceProperties2(physicalDevices);

	for (uint32_t i = 0; i < properties2.size(); i++)
	{
		auto& prop = properties2[i];
		std::cout << "Device Name: " << prop.properties.deviceName << std::endl;
		std::cout << "Device Type: " << prop.properties.deviceType << std::endl;
		std::cout << "API Version: " << prop.properties.apiVersion << std::endl;
		std::cout << "Driver Version: " << prop.properties.driverVersion << std::endl;
		std::cout << "Vendor ID: " << prop.properties.vendorID << std::endl;
		std::cout << "Device ID: " << prop.properties.deviceID << std::endl;
		std::cout << "Device UUID: " << prop.properties.pipelineCacheUUID << std::endl;
		std::cout << "Device Limits: " << std::endl;
		std::cout << "maxImageDimension1D: " << prop.properties.limits.maxImageDimension1D << std::endl;
		std::cout << "maxImageDimension2D: " << prop.properties.limits.maxImageDimension2D << std::endl;
		std::cout << "maxImageDimension3D: " << prop.properties.limits.maxImageDimension3D << std::endl;
		std::cout << "maxImageDimensionCube: " << prop.properties.limits.maxImageDimensionCube << std::endl;
		std::cout << "maxImageArrayLayers: " << prop.properties.limits.maxImageArrayLayers << std::endl;
		std::cout << "maxTexelBufferElements: " << prop.properties.limits.maxTexelBufferElements << std::endl;
		std::cout << "maxUniformBufferRange: " << prop.properties.limits.maxUniformBufferRange << std::endl;
		std::cout << "maxStorageBufferRange: " << prop.properties.limits.maxStorageBufferRange << std::endl;
		std::cout << "maxPushConstantsSize: " << prop.properties.limits.maxPushConstantsSize << std::endl;
		std::cout << "maxMemoryAllocationCount: " << prop.properties.limits.maxMemoryAllocationCount << std::endl;
		std::cout << "maxSamplerAllocationCount: " << prop.properties.limits.maxSamplerAllocationCount << std::endl;
		std::cout << "bufferImageGranularity: " << prop.properties.limits.bufferImageGranularity << std::endl;
	}





}


NS_TEST_END
