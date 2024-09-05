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
	VkCommandBuffer commandBuffer{/*假设这是一个有效的VkCommandBuffer*/ };


	//解压缩一个或者多个内存区域中的数据
	VkDecompressMemoryRegionNV decompressMemoryRegionNV{};
	decompressMemoryRegionNV.srcAddress = VkDeviceAddress{/*假设这是一个有效的VkDeviceAddress*/ };//为压缩的数据的存储地址
	decompressMemoryRegionNV.dstAddress = VkDeviceAddress{/*假设这是一个有效的VkDeviceAddress*/ };//为要存放解压缩的数据的目的地址
	decompressMemoryRegionNV.compressedSize = 1;//为压缩的数据的字节数大小
	decompressMemoryRegionNV.decompressedSize = 2; //为解压缩的数据的字节数大小
	decompressMemoryRegionNV.decompressionMethod = VK_MEMORY_DECOMPRESSION_METHOD_GDEFLATE_1_0_BIT_NV;//一个只含有一个bit设置的 VkMemoryDecompressionMethodFlagBitsNV组合之位掩码，指明解压缩的方法。 VK_MEMORY_DECOMPRESSION_METHOD_GDEFLATE_1_0_BIT_NV : 指明 GDeflate 1.0 算法用于解压数据.
	/*
	VkDecompressMemoryRegionNV有效用法:
	1.srcAddress 必须对齐到4字节
	2.srcAddress 到 srcAddress + compressedSize地址范围中的内存必须是有效的且绑定到一个VkDeviceMemory 上
	3.dstAddress 必须对齐到4字节
	4.如果decompressionMethod 为VK_MEMORY_DECOMPRESSION_METHOD_GDEFLATE_1_0_BIT_NV，则decompressedSize必须小于等于65536 字节
	5.dstAddress 到 dstAddress + compressedSize地址范围中的内存必须是有效的且绑定到一个VkDeviceMemory 上
	6.decompressedSize 必须足够大以容纳基于decompressionMethod方法解压缩后的数据
	7.decompressionMethod 必须只有一个bit设置
	8.srcAddress 到 srcAddress + compressedSize地址范围中的内存不能和dstAddress 到 dstAddress + compressedSize地址范围中的内存有重叠
	*/

	vkCmdDecompressMemoryNV(commandBuffer, 1, &decompressMemoryRegionNV);// memoryDecompression 特性必须开启



	//解压缩一个或者多个内存区域中的数据,其中相关参数包含在buffer中
	vkCmdDecompressMemoryIndirectCountNV(commandBuffer,
		VkDeviceAddress{/*假设这是一个有效的VkDeviceAddress*/ }/*indirectCommandsAddress,为包含VkDecompressMemoryRegionNV 结构体数组的设备地址，指明相关解压缩参数.*/,
		VkDeviceAddress{/*假设这是一个有效的VkDeviceAddress*/ }/*indirectCommandsCountAddress,为存放解压缩操作次数的设备地址.*/,
		sizeof(VkDecompressMemoryRegionNV)/*stride,为indirectCommandsAddress 中连续参数组之间的字节步长.*/);
	/*
	vkCmdDecompressMemoryIndirectCountNV有效用法:
	1.memoryDecompression 特性必须开启
	2.indirectCommandsAddress 所指的buffer如果是non-sparse的，则该buffer必须绑定到完整的连续的单独的VkDeviceMemory上，且该buffer必须以VK_BUFFER_USAGE_INDIRECT_BUFFER_BIT创建
	3.indirectCommandsCountAddress 所指的buffer如果是non-sparse的，则该buffer必须绑定到完整的连续的单独的VkDeviceMemory上，且该buffer必须以VK_BUFFER_USAGE_INDIRECT_BUFFER_BIT创建
	4.indirectCommandsCountAddress 必须是4的倍数
	5.存放在indirectCommandsCountAddress中的计数值必须小于等于VkPhysicalDeviceMemoryDecompressionPropertiesNV::maxDecompressionIndirectCount
	6.stride 必须是4的倍数且大于等于sizeof(VkDecompressMemoryRegionNV) 
	7.如果存放在indirectCommandsCountAddress中的计数值为1，则(offset + sizeof(VkDecompressMemoryRegionNV)) 必须小于等于indirectCommandsAddress 所指的buffer的大小
	8.如果存放在indirectCommandsCountAddress中的计数值大于1，则indirectCommandsAddress + sizeof(VkDecompressMemoryRegionNV) + (stride × (indirectCommandsCountAddress中的计数值 - 1)) 必须小于等于indirectCommandsAddress 所指的buffer中最后一个有效的地址
	*/

}



NS_TEST_END