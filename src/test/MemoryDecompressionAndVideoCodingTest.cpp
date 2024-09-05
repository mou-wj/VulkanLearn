#include "MemoryDecompressionAndVideoCodingTest.h"
NS_TEST_BEGIN
MemoryDecompressionAndVideoCodingTest::MemoryDecompressionAndVideoCodingTest()
{
}

void MemoryDecompressionAndVideoCodingTest::run()
{
}

MemoryDecompressionAndVideoCodingTest::~MemoryDecompressionAndVideoCodingTest()
{
}

void MemoryDecompressionAndVideoCodingTest::MemoryDecompressionTest()
{
	VkCommandBuffer commandBuffer{/*��������һ����Ч��VkCommandBuffer*/ };


	//��ѹ��һ�����߶���ڴ������е�����
	VkDecompressMemoryRegionNV decompressMemoryRegionNV{};
	decompressMemoryRegionNV.srcAddress = VkDeviceAddress{/*��������һ����Ч��VkDeviceAddress*/ };//Ϊѹ�������ݵĴ洢��ַ
	decompressMemoryRegionNV.dstAddress = VkDeviceAddress{/*��������һ����Ч��VkDeviceAddress*/ };//ΪҪ��Ž�ѹ�������ݵ�Ŀ�ĵ�ַ
	decompressMemoryRegionNV.compressedSize = 1;//Ϊѹ�������ݵ��ֽ�����С
	decompressMemoryRegionNV.decompressedSize = 2; //Ϊ��ѹ�������ݵ��ֽ�����С
	decompressMemoryRegionNV.decompressionMethod = VK_MEMORY_DECOMPRESSION_METHOD_GDEFLATE_1_0_BIT_NV;//һ��ֻ����һ��bit���õ� VkMemoryDecompressionMethodFlagBitsNV���֮λ���룬ָ����ѹ���ķ����� VK_MEMORY_DECOMPRESSION_METHOD_GDEFLATE_1_0_BIT_NV : ָ�� GDeflate 1.0 �㷨���ڽ�ѹ����.
	/*
	VkDecompressMemoryRegionNV��Ч�÷�:
	1.srcAddress ������뵽4�ֽ�
	2.srcAddress �� srcAddress + compressedSize��ַ��Χ�е��ڴ��������Ч���Ұ󶨵�һ��VkDeviceMemory ��
	3.dstAddress ������뵽4�ֽ�
	4.���decompressionMethod ΪVK_MEMORY_DECOMPRESSION_METHOD_GDEFLATE_1_0_BIT_NV����decompressedSize����С�ڵ���65536 �ֽ�
	5.dstAddress �� dstAddress + compressedSize��ַ��Χ�е��ڴ��������Ч���Ұ󶨵�һ��VkDeviceMemory ��
	6.decompressedSize �����㹻�������ɻ���decompressionMethod������ѹ���������
	7.decompressionMethod ����ֻ��һ��bit����
	8.srcAddress �� srcAddress + compressedSize��ַ��Χ�е��ڴ治�ܺ�dstAddress �� dstAddress + compressedSize��ַ��Χ�е��ڴ����ص�
	*/

	vkCmdDecompressMemoryNV(commandBuffer, 1, &decompressMemoryRegionNV);// memoryDecompression ���Ա��뿪��



	//��ѹ��һ�����߶���ڴ������е�����,������ز���������buffer��
	vkCmdDecompressMemoryIndirectCountNV(commandBuffer,
		VkDeviceAddress{/*��������һ����Ч��VkDeviceAddress*/ }/*indirectCommandsAddress,Ϊ����VkDecompressMemoryRegionNV �ṹ��������豸��ַ��ָ����ؽ�ѹ������.*/,
		VkDeviceAddress{/*��������һ����Ч��VkDeviceAddress*/ }/*indirectCommandsCountAddress,Ϊ��Ž�ѹ�������������豸��ַ.*/,
		sizeof(VkDecompressMemoryRegionNV)/*stride,ΪindirectCommandsAddress ������������֮����ֽڲ���.*/);
	/*
	vkCmdDecompressMemoryIndirectCountNV��Ч�÷�:
	1.memoryDecompression ���Ա��뿪��
	2.indirectCommandsAddress ��ָ��buffer�����non-sparse�ģ����buffer����󶨵������������ĵ�����VkDeviceMemory�ϣ��Ҹ�buffer������VK_BUFFER_USAGE_INDIRECT_BUFFER_BIT����
	3.indirectCommandsCountAddress ��ָ��buffer�����non-sparse�ģ����buffer����󶨵������������ĵ�����VkDeviceMemory�ϣ��Ҹ�buffer������VK_BUFFER_USAGE_INDIRECT_BUFFER_BIT����
	4.indirectCommandsCountAddress ������4�ı���
	5.�����indirectCommandsCountAddress�еļ���ֵ����С�ڵ���VkPhysicalDeviceMemoryDecompressionPropertiesNV::maxDecompressionIndirectCount
	6.stride ������4�ı����Ҵ��ڵ���sizeof(VkDecompressMemoryRegionNV) 
	7.��������indirectCommandsCountAddress�еļ���ֵΪ1����(offset + sizeof(VkDecompressMemoryRegionNV)) ����С�ڵ���indirectCommandsAddress ��ָ��buffer�Ĵ�С
	8.��������indirectCommandsCountAddress�еļ���ֵ����1����indirectCommandsAddress + sizeof(VkDecompressMemoryRegionNV) + (stride �� (indirectCommandsCountAddress�еļ���ֵ - 1)) ����С�ڵ���indirectCommandsAddress ��ָ��buffer�����һ����Ч�ĵ�ַ
	*/

}



NS_TEST_END