#include "MicroMapAndRayTraverseRayTracingTest.h"
NS_TEST_BEGIN

MicromapAndRayTraverseRayTracingTest::MicromapAndRayTraverseRayTracingTest()
{
}

void MicromapAndRayTraverseRayTracingTest::run()
{
}

MicromapAndRayTraverseRayTracingTest::~MicromapAndRayTraverseRayTracingTest()
{
}

void MicromapAndRayTraverseRayTracingTest::MicromapTest()
{
	/*
	加速结构组织ray tracing需要的geometry，然而在一些情况下，存储和组织一些和geometry相关（尤其是三角形的geometry）的信息是有益处的，micromap就是组织了一些对应到细分的微三角形的信息，可以创建 bottom level acceleration structure添加到三角形geometry的时候

	opacity micromap存储控制 intersection opacity （参见p3333）的信息

	displacement micromap存储替换sub-triangle 顶点的信息 （参见Displacement Micromap. p3324）

	可以使用micromap的构建以及拷贝命令来构造一个micromap
	*/

	VkMicromapEXT micromapEXT{};
	VkCommandBuffer commandBuffer{/*假设这是一个有效的VkCommandBuffer*/ };


	// Micromaps 参见p3294
	{
		//构建micromap
		VkMicromapBuildInfoEXT micromapBuildInfoEXT{};//该结构体的一些别的信息见p3299
		micromapBuildInfoEXT.sType = VK_STRUCTURE_TYPE_MICROMAP_BUILD_INFO_EXT;
		micromapBuildInfoEXT.pNext = nullptr;
		micromapBuildInfoEXT.type = VK_MICROMAP_TYPE_OPACITY_MICROMAP_EXT;// VkMicromapTypeEXT值指定要构建的micromap类型
		micromapBuildInfoEXT.flags = VK_BUILD_MICROMAP_PREFER_FAST_TRACE_BIT_EXT;//VkBuildMicromapFlagBitsEXT组合值位掩码指明额外的参数
		micromapBuildInfoEXT.mode = VK_BUILD_MICROMAP_MODE_BUILD_EXT;// VkBuildMicromapModeEXT值指明要执行的操作,VK_BUILD_MICROMAP_MODE_BUILD_EXT 指明使用指定的数据构建micromap
		micromapBuildInfoEXT.dstMicromap = micromapEXT;//指明要构建的micromap的句柄
		micromapBuildInfoEXT.usageCountsCount = 1;//指明用来定义micromap大小的VkMicromapUsageEXT的数量
		VkMicromapUsageEXT micromapUsageEXT{};
		{
			micromapUsageEXT.count = 1;//为micromap由subdivisionLevel 以及 format 定义的使用格式下三角形的数量
			micromapUsageEXT.format = 0;//为使用格式的format
			/*
			VkOpacityMicromapFormatEXT：
			VK_OPACITY_MICROMAP_FORMAT_2_STATE_EXT:  指明所给micromap format对每个subtriangle对应有一个bit指明其完全不透明或者完全透明
			VK_OPACITY_MICROMAP_FORMAT_4_STATE_EXT:  指明所给micromap format对每个subtriangle对应有两个bit，具体解释见p3333 ray traversal


			VkDisplacementMicromapFormatNV:
			VK_DISPLACEMENT_MICROMAP_FORMAT_64_TRIANGLES_64_BYTES_NV: 指明所给micromap format将64个值得替换的64个micro-triangles编码为64个字节，参见Displacement Micromap Encoding p3324
			VK_DISPLACEMENT_MICROMAP_FORMAT_256_TRIANGLES_128_BYTES_NV:  指明所给micromap format将128个值得替换的128个micro-triangles编码为64个字节，参见Displacement Micromap Encoding p3324
			VK_DISPLACEMENT_MICROMAP_FORMAT_1024_TRIANGLES_128_BYTES_NV:  指明所给micromap format将1024个值得替换的128个micro-triangles编码为64个字节，参见Displacement Micromap Encoding p3324
			*/
			micromapUsageEXT.subdivisionLevel = 0;//为使用格式的 subdivision level
			/*
			VkMicromapUsageEXT有效用法:
			1.如果micromap的VkMicromapTypeEXT 为VK_MICROMAP_TYPE_OPACITY_MICROMAP_EXT，则（1）format必须为VK_OPACITY_MICROMAP_FORMAT_2_STATE_EXT或者 VK_OPACITY_MICROMAP_FORMAT_4_STATE_EXT
																						 （2）如果format为VK_OPACITY_MICROMAP_FORMAT_2_STATE_EXT，则subdivisionLevel 必须小于等于VkPhysicalDeviceOpacityMicromapPropertiesEXT::maxOpacity2StateSubdivisionLevel
																						 （3）如果format为VK_OPACITY_MICROMAP_FORMAT_4_STATE_EXT，则subdivisionLevel 必须小于等于VkPhysicalDeviceOpacityMicromapPropertiesEXT::maxOpacity4StateSubdivisionLevel
			2.如果micromap的VkMicromapTypeEXT 为VK_MICROMAP_TYPE_DISPLACEMENT_MICROMAP_NV，则（1）format必须为VK_DISPLACEMENT_MICROMAP_FORMAT_64_TRIANGLES_64_BYTES_NV, VK_DISPLACEMENT_MICROMAP_FORMAT_256_TRIANGLES_128_BYTES_NV 或者 VK_DISPLACEMENT_MICROMAP_FORMAT_1024_TRIANGLES_128_BYTES_NV
																							 （2）subdivisionLevel 必须小于等于VkPhysicalDeviceDisplacementMicromapPropertiesNV::maxDisplacementMicromapSubdivisionLevel

			*/
		}
		micromapBuildInfoEXT.pUsageCounts = &micromapUsageEXT;//一组VkMicromapUsageEXT 的数组指针
		micromapBuildInfoEXT.ppUsageCounts = VK_NULL_HANDLE;//一组VkMicromapUsageEXT 的数组指针的数组指针，和pUsageCounts只能有一个不为VK_NULL_HANDLE
		micromapBuildInfoEXT.data = VkDeviceOrHostAddressConstKHR{ .deviceAddress/*通过vkGetBufferDeviceAddressKHR返回*/ = 0/*.hostAddress host端地址*/ /*假设这是一个有效的VkDeviceOrHostAddressConstKHR*/ };//包含micromap数据的 device 或者 host端的const内存地址
		micromapBuildInfoEXT.scratchData = VkDeviceOrHostAddressKHR{ .deviceAddress/*通过vkGetBufferDeviceAddressKHR返回*/ = 0/*.hostAddress host端地址*/ /*假设这是一个有效的VkDeviceOrHostAddressKHR*/ };//为用于构建的 scratch memory 的 device 或者 host端的内存地址
		//triangleArray中的数据
		{
			VkMicromapTriangleEXT micromapTriangleEXT{};
			micromapTriangleEXT.dataOffset = 0;//为该三角形数据的起始字节偏移量
			micromapTriangleEXT.format = 0;//为该三角形的subdivision level
			micromapTriangleEXT.subdivisionLevel = 0;//为该三角形的format

			/*
			VkMicromapTriangleEXT有效用法:
			1.如果micromap的VkMicromapTypeEXT 为VK_MICROMAP_TYPE_OPACITY_MICROMAP_EXT，则（1）format必须为VK_OPACITY_MICROMAP_FORMAT_2_STATE_EXT或者 VK_OPACITY_MICROMAP_FORMAT_4_STATE_EXT
																						 （2）如果format为VK_OPACITY_MICROMAP_FORMAT_2_STATE_EXT，则subdivisionLevel 必须小于等于VkPhysicalDeviceOpacityMicromapPropertiesEXT::maxOpacity2StateSubdivisionLevel
																						 （3）如果format为VK_OPACITY_MICROMAP_FORMAT_4_STATE_EXT，则subdivisionLevel 必须小于等于VkPhysicalDeviceOpacityMicromapPropertiesEXT::maxOpacity4StateSubdivisionLevel
			2.如果micromap的VkMicromapTypeEXT 为VK_MICROMAP_TYPE_DISPLACEMENT_MICROMAP_NV，则（1）format必须为VK_DISPLACEMENT_MICROMAP_FORMAT_64_TRIANGLES_64_BYTES_NV, VK_DISPLACEMENT_MICROMAP_FORMAT_256_TRIANGLES_128_BYTES_NV 或者 VK_DISPLACEMENT_MICROMAP_FORMAT_1024_TRIANGLES_128_BYTES_NV
																							 （2）subdivisionLevel 必须小于等于VkPhysicalDeviceDisplacementMicromapPropertiesNV::maxDisplacementMicromapSubdivisionLevel

			*/

		}
		micromapBuildInfoEXT.triangleArray = VkDeviceOrHostAddressConstKHR{ .deviceAddress/*通过vkGetBufferDeviceAddressKHR返回*/ = 0/*.hostAddress host端地址*/ /*假设这是一个有效的VkDeviceOrHostAddressConstKHR*/ };//为包含VkMicromapTriangleEXT 数据的 device 或者 host端的const内存地址
		micromapBuildInfoEXT.triangleArrayStride = 12;//指定triangleArray 中连续元素之间的字节步长
		/*
		VkMicromapBuildInfoEXT有效用法:
		1.pUsageCounts和ppUsageCounts中只有一个为有效的指针，另外一个必须为VK_NULL_HANDLE
		2.如果type为VK_MICROMAP_TYPE_OPACITY_MICROMAP_EXT，则VkMicromapUsageEXT::format，VkMicromapTriangleEXT::format 必须是有效的VkOpacityMicromapFormatEXT值
		3.如果type为VK_MICROMAP_TYPE_DISPLACEMENT_MICROMAP_NV，则VkMicromapUsageEXT::format，VkMicromapTriangleEXT::format 必须是有效的VkDisplacementMicromapFormatNV值

		*/




		/*
		其中对 VkMicromapBuildInfoEXT::scratchData,VkMicromapBuildInfoEXT::dstMicromap, VkMicromapBuildInfoEXT::data以及VkMicromapBuildInfoEXT::triangleArray以VK_PIPELINE_STAGE_2_MICROMAP_BUILD_BIT_EXT pipeline stage同步，
		VkMicromapBuildInfoEXT::scratchData 以(VK_ACCESS_2_MICROMAP_READ_BIT_EXT | VK_ACCESS_2_MICROMAP_WRITE_BIT_EXT)进行访问
		VkMicromapBuildInfoEXT::dstMicromap 以VK_ACCESS_2_MICROMAP_WRITE_BIT_EXT 进行访问
		VkMicromapBuildInfoEXT::data以及VkMicromapBuildInfoEXT::triangleArray 以VK_ACCESS_2_MICROMAP_READ_BIT_EXT 进行访问
		*/
		vkCmdBuildMicromapsEXT(commandBuffer, 1, &micromapBuildInfoEXT);
		/*
		vkCmdBuildMicromapsEXT有效用法:
		1.对任何pInfos[i]，dstMicromap 必须以VkMicromapCreateInfoEXT::size大于等于调用vkGetMicromapBuildSizesEXT传入pBuildInfo = pInfos[i]查询返回的内存大小进行创建
		2.pInfos中每个元素的mode必须是一个有效的VkBuildMicromapModeEXT
		3.pInfos中每个元素的dstMicromap必须是一个有效的VkMicromapEXT 句柄
		4.pInfos中每个元素的type 必须匹配创建dstMicromap 时的VkMicromapCreateInfoEXT::type
		5.该命令访问的pInfos中任何元素的dstMicromap的底层内存的范围之间不能有重叠
		6.该命令访问的pInfos中任何元素的dstMicromap不能和任何元素(包含相同元素)的scratchData的底层内存的范围之间有重叠
		7.该命令访问的pInfos中任何元素的scratchData的底层内存的范围之间不能有重叠
		8.对pInfos的每个元素，用于创建其dstMicromap的buffer必须已经绑定到device memory
		9.如果pInfos[i].mode 为VK_BUILD_MICROMAP_MODE_BUILD_EXT，则在 pInfos[i].scratchData.deviceAddress 以及 pInfos[i].scratchData.deviceAddress + N - 1 之间的所有地址必须在相同buffer的地址范围内，其中N为调用vkGetMicromapBuildSizesEXT，传入相同VkMicromapBuildInfoEXT和primitive count返回的VkMicromapBuildSizesInfoEXT::buildScratchSize
		10. pInfos[i]中data以及triangleArray 涉及到的buffer必须以VK_BUFFER_USAGE_MICROMAP_BUILD_INPUT_READ_ONLY_BIT_EXT创建
		11.pInfos[i]中每个pInfos[i].scratchData.deviceAddress 涉及到的buffer必须以VK_BUFFER_USAGE_STORAGE_BUFFER_BIT 创建
		12.对pInfos的每个元素，其scratchData.deviceAddress, data.deviceAddress以及triangleArray.deviceAddress 必须是有效的通过vkGetBufferDeviceAddress 获取的地址
		13.对pInfos的每个元素，如果scratchData.deviceAddress, data.deviceAddress以及triangleArray.deviceAddress 涉及到non-sparse的buffer，则该buffer必须已经绑定到完整的连续的单独的VkDeviceMemory上了
		14.对pInfos的每个元素，其scratchData.deviceAddress 必须是VkPhysicalDeviceAccelerationStructurePropertiesKHR::minAccelerationStructureScratchOffsetAlignment的整数倍
		15.对pInfos的每个元素，其triangleArray.deviceAddress 以及 data.deviceAddress必须是256 的整数倍

		*/


		//------------------------------------

		/*
		存在一个命令不需要更新micromap的内容就可以对齐进行拷贝，但在拷贝前需要查询dst micromap的内存大小需求
		*/

		//查询micromap大小参数 ，对pMicromaps的元素以VK_PIPELINE_STAGE_2_MICROMAP_BUILD_BIT_EXT pipeline stage同步，以VK_ACCESS_2_MICROMAP_READ_BIT_EXT访问
		vkCmdWriteMicromapsPropertiesEXT(commandBuffer, 1, &micromapEXT,
			VK_QUERY_TYPE_ACCELERATION_STRUCTURE_COMPACTED_SIZE_KHR/*queryType,指定查询类型*/, VkQueryPool{/*假设这是一个有效的VkQueryPool*/ }/*queryPool，指定管理查询结果的VkQueryPool*/, 0/*firstQuery,指定存放查询结果的第一个query的索引*/);
		/*
		vkCmdWriteMicromapsPropertiesEXT有效用法:
		1.queryPool 必须以匹配queryType创建
		2.由queryPool 以及firstQuery 指定的queries 必须是unavailable 的
		3.用于创建pMicrmaps中每个micromap的buffer必须已经绑定到device memory
		4.firstQuery + micromapCount 必须小于等于queryPool中queries的数量
		5.pMicromaps中的所有micromaps 必须在改名执行前被构建
		6.如果queryType为VK_QUERY_TYPE_MICROMAP_COMPACTED_SIZE_EXT则 pMicromaps中的所有micromaps 必须以VK_BUILD_MICROMAP_ALLOW_COMPACTION_BIT_EXT 构建
		7.queryType 必须为VK_QUERY_TYPE_MICROMAP_COMPACTED_SIZE_EXT 或者VK_QUERY_TYPE_MICROMAP_SERIALIZATION_SIZE_EXT
		*/




		VkCopyMicromapInfoEXT copyMicromapInfoEXT{};
		copyMicromapInfoEXT.sType = VK_STRUCTURE_TYPE_COPY_MICROMAP_INFO_EXT;
		copyMicromapInfoEXT.pNext = nullptr;
		copyMicromapInfoEXT.mode = VK_COPY_MICROMAP_MODE_CLONE_EXT;/* VkCopyMicromapModeEXT值指明拷贝期间执行的额外操作
		VkCopyMicromapModeEXT:
		VK_COPY_MICROMAP_MODE_CLONE_EXT:  创建一个从src到dst的micromap的直接拷贝，dst micromap必须和src以相同的参数创建
		VK_COPY_MICROMAP_MODE_SERIALIZE_EXT: 以semi-opaque format序列化micromap（序列化的头部格式信息见p3308），可以被兼容的实现重新加载
		VK_COPY_MICROMAP_MODE_DESERIALIZE_EXT:  以semi-opaque format反序列化到一个micromap
		VK_COPY_MICROMAP_MODE_COMPACT_EXT:  创建一个从src到dst的压缩版本信息，dst 必须以大小至少为创建src后对其调用vkCmdWriteMicromapsPropertiesEXT返回的值创建
		*/
		copyMicromapInfoEXT.src = VkMicromapEXT{/*假设这是一个有效的VkMicromapEXT*/ };//指明拷贝的source micromap
		copyMicromapInfoEXT.dst = micromapEXT;//指明拷贝的destination micromap
		/*
		VkCopyMicromapInfoEXT有效用法:
		1.mode 必须为VK_COPY_MICROMAP_MODE_COMPACT_EXT 或者 VK_COPY_MICROMAP_MODE_CLONE_EXT
		2.src micromap必须在该命令执行前被构建
		3.如果mode 为VK_COPY_MICROMAP_MODE_COMPACT_EXT，则src必须以VK_BUILD_MICROMAP_ALLOW_COMPACTION_BIT_EXT构建
		4.用于创建src以及dst的buffer必须绑定到device memory上
		*/


		//拷贝micromap ,   对pInfo->src 以及 pInfo->dst以VK_PIPELINE_STAGE_2_MICROMAP_BUILD_BIT_EXT pipeline stage同步，以VK_ACCESS_2_MICROMAP_READ_BIT_EXT 或者 VK_ACCESS_2_MICROMAP_WRITE_BIT_EXT访问
		vkCmdCopyMicromapEXT(commandBuffer, &copyMicromapInfoEXT); //用于创建pInfo->src 以及 pInfo->dst的buffer必须已经绑定的device memory上




		VkCopyMicromapToMemoryInfoEXT copyMicromapToMemoryInfoEXT{};
		copyMicromapToMemoryInfoEXT.sType = VK_STRUCTURE_TYPE_COPY_MICROMAP_TO_MEMORY_INFO_EXT;
		copyMicromapToMemoryInfoEXT.pNext = nullptr;
		copyMicromapToMemoryInfoEXT.mode = VK_COPY_MICROMAP_MODE_SERIALIZE_EXT;//VkCopyMicromapModeEXT值指明拷贝期间执行的额外操作
		copyMicromapToMemoryInfoEXT.src = micromapEXT;//指明拷贝的source micromap
		copyMicromapToMemoryInfoEXT.dst = VkDeviceOrHostAddressKHR{ .deviceAddress/*通过vkGetBufferDeviceAddressKHR返回*/ = 0/*.hostAddress host端地址*/ /*假设这是一个有效的VkDeviceOrHostAddressKHR*/ };//为拷贝micromap的dstination memory的 device 或者 host端的内存地址
		/*
		VkCopyMicromapToMemoryInfoEXT有效用法:
		1.src micromap必须在该命令执行前构建
		2.dst绑定的memory的大小至少是src序列化的大小，见 vkWriteMicromapsPropertiesEXT 或者 vkCmdWriteMicromapsPropertiesEXT 传入query type为 VK_QUERY_TYPE_MICROMAP_SERIALIZATION_SIZE_EXT返回的值
		3.mode 必须为VK_COPY_MICROMAP_MODE_SERIALIZE_EXT
		*/

		/*
		拷贝一个micromap序列化到device memory ，和 vkCopyMicromapToMemoryEXT产生相同结果，只不过该命令会将结果写到device memory中，其输出可以被vkCmdCopyMemoryToMicromapEXT 或者 vkCopyMemoryToMicromapEXT使用
		对pInfo->src 或者pInfo->dst 以 VK_PIPELINE_STAGE_2_MICROMAP_BUILD_BIT_EXT pipeline stage 同步

		对pInfo->src以VK_ACCESS_2_MICROMAP_READ_BIT_EXT访问，对pInfo->dst.deviceAddress以 VK_ACCESS_TRANSFER_WRITE_BIT访问
		*/
		vkCmdCopyMicromapToMemoryEXT(commandBuffer, &copyMicromapToMemoryInfoEXT);
		/*
		vkCmdCopyMicromapToMemoryEXT有效用法:
		1.pInfo->dst.deviceAddress 必须是一个绑定到device memory的有效的device address，其必须对齐到256字节
		2.如果pInfo->dst.deviceAddress 所指的buffer是non-sparse的则该buffer必须绑定到完整的连续的单独的VkDeviceMemory对象
		3.用于创建pInfo->src 的buffer必须绑定到device memory
		*/




		VkCopyMemoryToMicromapInfoEXT copyMemoryToMicromapInfoEXT{};
		copyMemoryToMicromapInfoEXT.sType = VK_STRUCTURE_TYPE_COPY_MEMORY_TO_MICROMAP_INFO_EXT;
		copyMemoryToMicromapInfoEXT.pNext = nullptr;
		copyMemoryToMicromapInfoEXT.mode = VK_COPY_MICROMAP_MODE_DESERIALIZE_EXT;//VkCopyMicromapModeEXT值指明拷贝期间执行的额外操作
		copyMemoryToMicromapInfoEXT.src = VkDeviceOrHostAddressConstKHR{ .deviceAddress/*通过vkGetBufferDeviceAddressKHR返回*/ = 0/*.hostAddress host端地址*/ /*假设这是一个有效的VkDeviceOrHostAddressConstKHR*/ };//为拷贝micromap的source memory的 device 或者 host端的const内存地址
		copyMemoryToMicromapInfoEXT.dst = micromapEXT;//指明拷贝的destination micromap
		/*
		VkCopyMemoryToMicromapInfoEXT有效用法:
		1.src所指的source memory中必须包含之前通过vkCmdCopyMicromapToMemoryEXT序列化的数据
		2.mode 必须为VK_COPY_MICROMAP_MODE_DESERIALIZE_EXT
		3.src中的数据的必须有一个和destination physical device兼容的format ，见vkGetDeviceMicromapCompatibilityEXT返回的信息
		4.dst 数据大小必须以大于等于src中的序列化数据大小创建

		*/


		/*
		拷贝device memory反序列化到一个micromap，和vkCopyAccelerationStructureToMemoryKHR产生相同结果
		对pInfo->src 或者pInfo->dst 以  VK_PIPELINE_STAGE_2_MICROMAP_BUILD_BIT_EXT pipeline stage同步

		对pInfo->src.deviceAddress以VK_ACCESS_TRANSFER_READ_BIT访问，对pInfo->dst以 VK_ACCESS_2_MICROMAP_READ_BIT_EXT访问

		该命令可以接受来自vkCmdCopyMicromapToMemoryEXT 或者 vkCopyMicromapToMemoryEXT.产生的micromap
		*/
		vkCmdCopyMemoryToMicromapEXT(commandBuffer, &copyMemoryToMicromapInfoEXT);
		/*
		vkCmdCopyMemoryToMicromapEXT有效用法:
		1.pInfo->src.deviceAddress 必须是一个有效的绑定的device memory的device address，且必须对齐到256字节
		2.如果pInfo->src.deviceAddress 所指的buffer是non-sparse的则该buffer必须绑定到完整的连续的单独的VkDeviceMemory对象
		3.用于创建pInfo->dst 的buffer必须绑定到device memory
		*/


		VkMicromapVersionInfoEXT micromapVersionInfoEXT{};
		micromapVersionInfoEXT.sType = VK_STRUCTURE_TYPE_MICROMAP_VERSION_INFO_EXT;
		micromapVersionInfoEXT.pNext = nullptr;
		uint8_t version = 0;
		micromapVersionInfoEXT.pVersionData = &version;//必须是vkCmdCopyMicromapToMemoryEXT或者 vkCopyMicromapToMemoryEXT 执行是定义的版本头信息的数据指针，指向2×VK_UUID_SIZE 个uint8_t值

		VkAccelerationStructureCompatibilityKHR cccelerationStructureCompatibilityKHR{};
		//检查一些序列化的micromap是否兼容device
		vkGetDeviceMicromapCompatibilityEXT(device, &micromapVersionInfoEXT, &cccelerationStructureCompatibilityKHR);// micromap 特性必须开启
	}


	//Host Micromap Operations  参见p3314
	{
		/*
		如果 micromapHostCommands特性开启，则实现也提供了在host端对micromap的操作:
		
		host端							   对应             device端
		vkBuildMicromapsEXT				    ->				vkCmdBuildMicromapsEXT
		vkCopyMicromapEXT					->				vkCmdCopyMicromapEXT
		vkCopyMicromapToMemoryEXT			->				vkCmdCopyMicromapToMemoryEXT
		vkCopyMemoryToMicromapEXT			->				vkCmdCopyMemoryToMicromapEXT
		vkWriteMicromapsPropertiesEXT		->				vkCmdWriteMicromapsPropertiesEXT
		

		host端操作micromap的命令访问的micromap必须绑定到host-visible的内存，且所有micromap构建的所有输入数据必须引用host端的地址而不是device端
		*/

		VkMicromapBuildInfoEXT micromapBuildInfoEXT{/*假设这是一个有效的VkMicromapBuildInfoEXT*/};//前面已经描述过了，这里不再复述

		//在host端构建micromap  ,等效于vkCmdBuildMicromapsEXT，参数详解见前面的描述，这里不再复述，该命令不会进行任何内存访问控制
		vkBuildMicromapsEXT(device, VkDeferredOperationKHR{/*假设这是一个有效的VkDeferredOperationKHR*/ }, 1, & micromapBuildInfoEXT);
		/*
		vkBuildMicromapsEXT有效用法:
		1.对任何pInfos[i]，dstMicromap 必须以VkMicromapCreateInfoEXT::size大于等于调用vkGetMicromapBuildSizesEXT传入pBuildInfo = pInfos[i]查询返回的内存大小进行创建
		2.pInfos中每个元素的mode必须是一个有效的VkBuildMicromapModeEXT
		3.pInfos中每个元素的dstMicromap必须是一个有效的VkMicromapEXT 句柄
		4.pInfos中每个元素的type 必须匹配创建dstMicromap 时的VkMicromapCreateInfoEXT::type
		5.该命令访问的pInfos中任何元素的dstMicromap的底层内存的范围之间不能有重叠
		6.该命令访问的pInfos中任何元素的dstMicromap不能和任何元素(包含相同元素)的scratchData的底层内存的范围之间有重叠
		7.该命令访问的pInfos中任何元素的scratchData的底层内存的范围之间不能有重叠
		8.对pInfos的每个元素，用于创建其dstMicromap的buffer必须已经绑定到host-visible device memory
		9.pInfos中的每个元素，所有元素的data.hostAddress引用的必须是有效的host memory
		10.pInfos中的每个元素，所有元素的triangleArray.hostAddress引用的必须是有效的host memory
		11.VkPhysicalDeviceOpacityMicromapFeaturesEXT::micromapHostCommands 特性必须开启
		12.如果pInfos[i].mode 为VK_BUILD_MICROMAP_MODE_BUILD_EXT，则在 pInfos[i].scratchData.hostAddress 以及 pInfos[i].scratchData.hostAddress + N - 1 之间的所有地址必须有效的host memory，其中N为调用vkGetMicromapBuildSizesEXT，传入相同VkMicromapBuildInfoEXT和primitive count返回的VkMicromapBuildSizesInfoEXT::buildScratchSize
		13.pInfos中的每个元素，用于创建其dstMicromap的buffer必须绑定到memory，企鹅该memory不能在multiple instances 上分配
		*/



		VkCopyMicromapInfoEXT copyMicromapInfoEXT{/*假设这是一个有效的VkCopyMicromapInfoEXT*/ };//前面已经描述过这里不再复述
		//在host端拷贝或者压缩一个micromap  ,等效于vkCmdCopyMicromapEXT
		vkCopyMicromapEXT(device, VkDeferredOperationKHR{/*假设这是一个有效的VkDeferredOperationKHR*/ }, & copyMicromapInfoEXT);
		/*
		vkCopyMicromapEXT有效用法:
		1.  VkPhysicalDeviceOpacityMicromapFeaturesEXT::micromapHostCommands 特性必须开启
		2.任何deferredOperation关联的之前的deferred operation 必须已经完成
		3.用于创建pInfo->src，pInfo->dst micromap的buffer必须已经绑定到host-visible device memory上，且该memory没有在multiple instances上分配
		*/


		VkCopyMemoryToMicromapInfoEXT copyMemoryToMicromapInfoEXT{/*假设这是一个有效的VkCopyMemoryToMicromapInfoEXT*/ };//前面已经描述过这里不再复述
		//host端拷贝 host accessible memory 到一个micromap，等效于vkCmdCopyMemoryToMicromapEXT，可以接受由 vkCmdCopyMicromapToMemoryEXT 或者vkCopyMicromapToMemoryEXT产生的micromap
		vkCopyMemoryToMicromapEXT(device, VkDeferredOperationKHR{/*假设这是一个有效的VkDeferredOperationKHR*/ }, & copyMemoryToMicromapInfoEXT);
		/*
		vkCopyMemoryToMicromapEXT有效用法:
		1. VkPhysicalDeviceOpacityMicromapFeaturesEXT::micromapHostCommands 特性必须开启
		2.任何deferredOperation关联的之前的deferred operation 必须已经完成
		3.pInfo->src.hostAddress必须是有效的 host pointer，且其必须对齐到16字节
		4.用于创建pInfo->dst micromap的buffer必须已经绑定到host-visible device memory上，且该memory没有在multiple instances上分配

		*/


		VkCopyMicromapToMemoryInfoEXT copyMicromapToMemoryInfoEXT{/*假设这是一个有效的VkCopyMicromapToMemoryInfoEXT*/ };//前面已经描述过这里不再复述
		//host端拷贝一个micromap到host accessible memory，等效于vkCmdCopyMicromapToMemoryEXT，该接口输出可以被vkCmdCopyMemoryToMicromapEXT 或者 vkCopyMemoryToMicromapEXT使用
		vkCopyMicromapToMemoryEXT(device, VkDeferredOperationKHR{/*假设这是一个有效的VkDeferredOperationKHR*/ }, & copyMicromapToMemoryInfoEXT);
		/*
		vkCopyMicromapToMemoryEXT有效用法:
		1.VkPhysicalDeviceOpacityMicromapFeaturesEXT::micromapHostCommands特性必须开启
		2.任何deferredOperation关联的之前的deferred operation 必须已经完成
		3.pInfo->dst.hostAddress必须是有效的 host pointer，且其必须对齐到16字节
		4.用于创建pInfo->src micromap的buffer必须已经绑定到host-visible device memory上，且该memory没有在multiple instances上分配
		*/



		uint32_t needSize = 0;
		//host端查询micromap的大小参数
		VkMicromapEXT micromapEXT{/*假设这是一个有效的VkMicromapEXT*/ };
		//等效于 vkCmdWriteMicromapsPropertiesEXT
		vkWriteMicromapsPropertiesEXT(device, 1, &micromapEXT,
			VK_QUERY_TYPE_ACCELERATION_STRUCTURE_COMPACTED_SIZE_KHR/*queryType，指明查询类型*/, sizeof(needSize)/*dataSize，pData中的字节大小*/, &needSize/*pData,为用户分配的用于存放查询结果的内存指针*/, sizeof(needSize)/*stride,为pData中单独的查询结果之间的字节步长*/);
		/*
		vkWriteMicromapsPropertiesEXT有效用法:
		1.VkPhysicalDeviceOpacityMicromapFeaturesEXT::micromapHostCommands 特性必须开启
		2.pMicromaps中的所有micromap必须已经在该命令的执行前构建
		3.pMicromaps中的所有micromap如果queryType为VK_QUERY_TYPE_MICROMAP_COMPACTED_SIZE_EXT则必须以VK_BUILD_MICROMAP_ALLOW_COMPACTION_BIT_EXT创建
		4.queryType必须为VK_QUERY_TYPE_MICROMAP_COMPACTED_SIZE_EXT 或者 VK_QUERY_TYPE_MICROMAP_SERIALIZATION_SIZE_EXT
		5.如果queryType为VK_QUERY_TYPE_MICROMAP_SERIALIZATION_SIZE_EXT，则（1）stride 必须为VkDeviceSize类型字节大小的整数倍
																		  （2）pData必须是一个指向VkDeviceSize的数组
		6.dataSize 必须大于或等于micromapCount*stride
		7.用来创建pMicromaps中每个micromap的buffer必须已经绑定到host-visible device memory上，且该memory没有在multiple instances上分配
		*/



		//Displacement Micromap 参见p3324
		{
			//详情见 p3324 - p3327
		}

	}
}

void MicromapAndRayTraverseRayTracingTest::RayTraverseTest()
{
}

void MicromapAndRayTraverseRayTracingTest::RayTracingTest()
{
}

NS_TEST_END