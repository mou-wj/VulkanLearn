#include "ResourceCreationTest.h"

NS_TEST_BEGIN


ResourceCreationTest::ResourceCreationTest()
{
}

void ResourceCreationTest::run()
{
}

ResourceCreationTest::~ResourceCreationTest()
{
}

void ResourceCreationTest::BufferCreateTest()
{
	VkBuffer buffer{ VK_NULL_HANDLE };
	VkBufferCreateInfo bufferCreateInfo{};
	bufferCreateInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
	bufferCreateInfo.pNext = nullptr;
	bufferCreateInfo.flags = 0;//是 VkBufferCreateFlagBits组合值的一个位掩码，指定缓冲区的附加参数。
	bufferCreateInfo.queueFamilyIndexCount = 0;//是pQueueFamilyIndices中的队列族索引索引个数
	bufferCreateInfo.pQueueFamilyIndices = VK_NULL_HANDLE;//是指向将访问此buffer的队列族索引数组的指针。如果共享模式不是VK_SHARING_MODE_CONCURRENT，则被忽略
	bufferCreateInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;//是一个 VkSharingMode 值，指定buffer被多个队列族访问时的共享模式。
	bufferCreateInfo.size = 1;//是要创建的缓冲区的字节大小
	bufferCreateInfo.usage = VK_BUFFER_USAGE_VERTEX_BUFFER_BIT;//是 VkBufferUsageFlagBits组合值的位掩码，指定buffer的用途

	vkCreateBuffer(device, &bufferCreateInfo, nullptr, &buffer);/*
	vkCreateBuffer有效用法:
	1.如果pCreateInfo 中的flags包含VK_BUFFER_CREATE_SPARSE_BINDING_BIT，且extendedSparseAddressSpace 特性没有开启，则（1）创建这个VkBuffer 需要的sparse memory数量不能导致在device上 的所有有效的sparse resources memory的总和超过 VkPhysicalDeviceLimits::sparseAddressSpaceSize
																													 （2）如果pCreateInfo的usage包含VkPhysicalDeviceExtendedSparseAddressSpacePropertiesNV::extendedSparseBufferUsageFlags 中不含有的比特位，则在去除了pCreateInfo的flags中包含VkPhysicalDeviceExtendedSparseAddressSpacePropertiesNV::extendedSparseBufferUsageFlags比特位创建的VkBuffer和VkImage后，
																															创建这个VkBuffer 需要的sparse memory数量不能导致在device上 的所有有效的sparse resources memory的总和超过 VkPhysicalDeviceLimits::sparseAddressSpaceSize
	2.如果pCreateInfo 中的flags包含VK_BUFFER_CREATE_SPARSE_BINDING_BIT，且extendedSparseAddressSpace 特性开启，创建这个VkBuffer 需要的sparse resources数量不能导致在device上 的所有有效的sparse resources的总和超过 VkPhysicalDeviceExtendedSparseAddressSpacePropertiesNV::extendedSparseAddressSpaceSize

	3.如果为了在pCreateInfo的pNext中加入一个VkBufferCollectionBufferCreateInfoFUCHSIA导入一个VkBufferCollectionFUCHSIA 而使用这个VkBuffer，则 pCreateInfo必须匹配 调用vkSetBufferCollectionBufferConstraintsFUCHSIA设置buffer collection的限制的时候的 VkBufferConstraintsInfoFUCHSIA::createInfo

	*/










}



NS_TEST_END