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
	bufferCreateInfo.flags = 0;//�� VkBufferCreateFlagBits���ֵ��һ��λ���룬ָ���������ĸ��Ӳ�����
	bufferCreateInfo.queueFamilyIndexCount = 0;//��pQueueFamilyIndices�еĶ�����������������
	bufferCreateInfo.pQueueFamilyIndices = VK_NULL_HANDLE;//��ָ�򽫷��ʴ�buffer�Ķ��������������ָ�롣�������ģʽ����VK_SHARING_MODE_CONCURRENT���򱻺���
	bufferCreateInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;//��һ�� VkSharingMode ֵ��ָ��buffer��������������ʱ�Ĺ���ģʽ��
	bufferCreateInfo.size = 1;//��Ҫ�����Ļ��������ֽڴ�С
	bufferCreateInfo.usage = VK_BUFFER_USAGE_VERTEX_BUFFER_BIT;//�� VkBufferUsageFlagBits���ֵ��λ���룬ָ��buffer����;

	vkCreateBuffer(device, &bufferCreateInfo, nullptr, &buffer);/*
	vkCreateBuffer��Ч�÷�:
	1.���pCreateInfo �е�flags����VK_BUFFER_CREATE_SPARSE_BINDING_BIT����extendedSparseAddressSpace ����û�п�������1���������VkBuffer ��Ҫ��sparse memory�������ܵ�����device�� ��������Ч��sparse resources memory���ܺͳ��� VkPhysicalDeviceLimits::sparseAddressSpaceSize
																													 ��2�����pCreateInfo��usage����VkPhysicalDeviceExtendedSparseAddressSpacePropertiesNV::extendedSparseBufferUsageFlags �в����еı���λ������ȥ����pCreateInfo��flags�а���VkPhysicalDeviceExtendedSparseAddressSpacePropertiesNV::extendedSparseBufferUsageFlags����λ������VkBuffer��VkImage��
																															�������VkBuffer ��Ҫ��sparse memory�������ܵ�����device�� ��������Ч��sparse resources memory���ܺͳ��� VkPhysicalDeviceLimits::sparseAddressSpaceSize
	2.���pCreateInfo �е�flags����VK_BUFFER_CREATE_SPARSE_BINDING_BIT����extendedSparseAddressSpace ���Կ������������VkBuffer ��Ҫ��sparse resources�������ܵ�����device�� ��������Ч��sparse resources���ܺͳ��� VkPhysicalDeviceExtendedSparseAddressSpacePropertiesNV::extendedSparseAddressSpaceSize

	3.���Ϊ����pCreateInfo��pNext�м���һ��VkBufferCollectionBufferCreateInfoFUCHSIA����һ��VkBufferCollectionFUCHSIA ��ʹ�����VkBuffer���� pCreateInfo����ƥ�� ����vkSetBufferCollectionBufferConstraintsFUCHSIA����buffer collection�����Ƶ�ʱ��� VkBufferConstraintsInfoFUCHSIA::createInfo

	*/










}



NS_TEST_END