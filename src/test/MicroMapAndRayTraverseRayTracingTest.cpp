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

	displacement micromap存储移动sub-triangle 顶点的信息 （参见Displacement Micromap. p3324）

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
	/*
	ray traversal处理加速结构中geometry和ray的相交。
	
	ray traversal不通过vulkan API直接开始，而是需要一个shader执行OpRayQueryProceedKHR或者一个 pipeline trace ray 指令。

	当rayTracingPipeline 特性开启，则OpTraceRayKHR 可以用于ray tracing，当 rayQuery特性开启，则OpRayQueryProceedKHR可以在任何shader stage使用。
	*/


	//Ray Intersection Candidate Determination  参见p3327
	{
		/*
		ray tracing一旦开始，ray首先会判断是否可能和instance相交，然后再去判断是否可能和instance中的geometry相交。

		一旦判断可能和某个geometry相交，则会将该geometry中图元的顶点从加速结构的顶点空间变换以ray的方向作为-z轴的ray空间中，然后寻找相交备选点，
		这样图元与ray相交备选点必满足在ray空间中x，y为0，z为一个值的点
		
		一旦确定了该备选交点，便会依次进行以下操作:
		1. Ray Intersection Culling
		2. Ray Intersection Confirmation
		3. Ray Closest Hit Determination
		4. Ray Result Determination
		*/

	}


	// Watertightness  参见p3330   对一些含共享顶点或者共享边的图元，必须保证这些共享顶点或者共享边不能被ray击中多次


	//Ray Intersection Culling  参见p3330
	{
		/*
		确定了相交备选点后会经过一系列顺序不定的cull操作然后最终确定相交点。
		*/


		//Ray Primitive Culling  参见p3330
		{
			/*
			如果rayTraversalPrimitiveCulling 或者 rayQuery 特性开启，则可以在ray flags中指定SkipTrianglesKHR 或者SkipAABBsKHR(两者只能用一个)来指出当ray和三角形或者aabbs相交时，该次相交的交点处理终止，不会对该交点做后续操作。

			也可以在创建ray tracing pipeline的时候指定VK_PIPELINE_CREATE_RAY_TRACING_SKIP_TRIANGLES_BIT_KHR 或者 VK_PIPELINE_CREATE_RAY_TRACING_SKIP_AABBS_BIT_KHR来达到相同的效果。
			
			*/
		}

		//Ray Mask Culling  参见p3331
		{
			/*
			当用于ray tracing的Cull Mask和VkAccelerationStructureInstanceKHR::mask的操作结果mask & Cull Mask == 0 时指明该加速结构实例对ray不可见，此次相交终止，不再进行后续操作，
			*/
		}

		//Ray Face Culling  参见p3331
		{
			/*
			在击中三角形时，如果从ray的方向看去是图元正面（根据图元顶点在ray空间中根据rasterization章节定义的正反面计算公式计算出的值为负数），则 HitKindKHR 会设置为HitKindFrontFacingTriangleKHR，否则会设为HitKindBackFacingTriangleKHR，

			如果ray以OpRayQueryProceedKHR进行，则击中正面时OpRayQueryGetIntersectionFrontFaceKHR会返回true，反之为false。

			如果在ray flags中设置 CullBackFacingTrianglesKHR，则在击中背面的时候，或者如果设置了 CullFrontFacingTrianglesKHR（和前者只能使用一个），在击中正面的时候，此次击中操作终止，不再进行后续操作，如果VkAccelerationStructureInstanceKHR::flags中设置了VK_GEOMETRY_INSTANCE_TRIANGLE_FLIP_FACING_BIT_KHR，则可以反转操作结果，正面的击中判为反面的击中，反之一样。


			如果VkAccelerationStructureInstanceKHR::flags中设置了VK_GEOMETRY_INSTANCE_TRIANGLE_FACING_CULL_DISABLE_BIT_KHR，则可以关闭ray face culling
			*/
		}

		//Ray Opacity Culling  参见p3332
		{
			/*
			在ray taversal过程中，如果geometry为透明的（非Opaque的）则该geometry可能会被丢弃。

			geometry的Opeque属性最先由其 VkAccelerationStructureGeometryKHR::flags 是否包含VK_GEOMETRY_OPAQUE_BIT_KHR决定，
			如果geometry含有Opaque micromap，则进一步使用micromap中说明的属性，再然后由VkAccelerationStructureInstanceKHR::flags
			中是否包含VK_GEOMETRY_INSTANCE_FORCE_OPAQUE_BIT_KHR 或者VK_GEOMETRY_INSTANCE_FORCE_NO_OPAQUE_BIT_KHR 决定，Opaque属性
			还可以在ray flags中包含 OpaqueKHR 或者 NoOpaqueKHR 指定所有的geometry是否是不透明的。

			如果ray以 OpRayQueryProceedKHR进行trace，则 OpRayQueryGetIntersectionCandidateAABBOpaqueKHR可以用来判断是否相交与一个Opaque的AABB，如果是返回true，否则返回false。

			当判断了Opaque属性后，如果ray flags中包含CullOpaqueKHR，则和opaque geometry的相交将终止，不再进行后续操作，如果包含CullNoOpaqueKHR，则和non-opaque geometry的相交将终止，
			不再进行后续操作。ray flags中OpaqueKHR, NoOpaqueKHR, CullOpaqueKHR, 以及 CullNoOpaqueKHR 只能互斥使用。

			*/



		
		}


		//Ray Opacity Micromap  参见p3333
		{
			/*
			如果VkAccelerationStructureInstanceKHR::flags中不含VK_GEOMETRY_INSTANCE_DISABLE_OPACITY_MICROMAPS_EXT则可以使用micromap来对geometry的opaque属性进行细粒度的控制。

			详情见p3334
			
			*/
		}

	}



	//Ray Intersection Confirmation  参见p3334
	{
		//AABB Intersection Candidates  参见p3335

		//Triangle and Generated Intersection Candidates  参见p3335
		{
			/*
			基于相交的opaque属性（见前面ray opaque culling）需要额外的shader调用来确定是否继续处理此次相交的备选点，该操作可以对相同备选点执行多次除非指明VK_GEOMETRY_NO_DUPLICATE_ANY_HIT_INVOCATION_BIT_KHR。

			如果相交的opaque属性为opaque，则此次该确认该备选点，然后传入下一阶段进行后续处理。

			如果相交的opaque属性为non-opaque，则如果shader调用了OpIgnoreIntersectionKHR，则终止对该备选点的处理，如果 any-hit shader为 VK_SHADER_UNUSED_KHR，则确认该备选点，然后传入下一阶段进行后续处理。
			
			如果ray 以OpRayQueryProceedKHR 进行，则调用 OpRayQueryConfirmIntersectionKHR确认该备选点，然后对该ray trace继续进行OpRayQueryProceedKHR，如果调用OpRayQueryTerminateKHR则直接终止对该备选点的处理。
			*/
		}

	}

	//Ray Closest Hit Determination  参见p3336
	{
		/*
		除非ray flags中设置了TerminateOnFirstHitKHR，否则必须直到所有geometry都测试了且确定或终止了击中备选点找出最近的击中点（备选点都在延-z轴，所以最近点为z最大的点）为止。
		*/
	}

	//Ray Result Determination  参见p3336
	{
		//一旦相交备选点完成了上述阶段或者强制终止了ray trace，则最终的结果就确定了，对结果的具体描述见p3336
	}
}

void MicromapAndRayTraverseRayTracingTest::RayTracingTest()
{
	/*
	在ray tracing pipeline中，ray tracing的执行过程会触发各种shader stages，ray tracing pipeline 和在VkBuffer中传递给ray tracing命令用于遍历的加速结构的geometry之间的管线称为shader binding table。

	 OpExecuteCallableKHR 可以在ray tracing过程中用于触发一个 callable shader。

	 ray tracing涉及的shader stage为 single-ray programming model，一次只处理一条ray
	
	*/


	//Shader Call Instructions  参见p3339
	{
		/*
		shader call是一条指令，用于在任何地方触发一个不同的shader stage进行执行。
		这些指令为:
		OpTraceRayKHR :  可能触发 intersection, any-hit, closest hit, 或者 miss shaders,
		OpTraceRayMotionNV : 可能触发 invoke intersection, any-hit, closest hit, 或者 miss shaders,
		OpReportIntersectionKHR : 可能触发 any-hit shaders
		OpExecuteCallableKHR : 触发 callable shader.
		OpHitObjectTraceRayNV, OpHitObjectTraceRayMotionNV, 以及 OpHitObjectExecuteShaderNV :  可能触发intersection, any-hit, closest hit, miss, 或者 callable shaders.

		这些指令可以在递归调用，最大递归深度受 maxRecursionDepth 或者 maxRayRecursionDepth 限制
		

		invocation repack 指令为 ray tracing 指令，可能会更改执行的一组调用，变更其所属的subgroup或者原来同一subgroup的SubgroupLocalInvocationId，这些指令为OpTraceRayKHR, OpTraceRayMotionNV, OpReorderThreadWithHintNV, OpReorderThreadWithHitObjectNV, OpReportIntersectionKHR, 以及 OpExecuteCallableKHR
		当变更了subgroup后SubgroupSize, SubgroupLocalInvocationId, SMIDNV, WarpIDNV,以及SubgroupEqMask, SubgroupGeMask, SubgroupGtMask, SubgroupLeMask, SubgroupLtMask都必须要改变。所以在ray tracing过程中，这些变量需要用Volatile
		
		*/

	}

	//Ray Tracing Commands 参见p3340
	{
		/*
		ray tracing commands 记录在command buffer中，执行在queue中，触发绑定的ray tracing pipeline进行工作。
		
		*/

		VkCommandBuffer commandBuffer{/*假设这是一个有效的VkCommandBuffer*/ };
		VkBuffer raygenShaderBindingTableBuffer{/*假设这是一个有效的VkBuffer*/ };
		VkBuffer missShaderBindingTableBuffer{/*假设这是一个有效的VkBuffer*/ };
		VkBuffer hitShaderBindingTableBuffer{/*假设这是一个有效的VkBuffer*/ };
		VkBuffer callableShaderBindingTableBuffer{/*假设这是一个有效的VkBuffer*/ };


		//dispatch ray tracing,   执行该命令，则一个包含 width × height × depth 条ray的ray 产生组会被组装
		vkCmdTraceRaysNV(commandBuffer, 
			raygenShaderBindingTableBuffer/*raygenShaderBindingTableBuffer,包含用于ray generation shader stage的shader binding table data.*/, 0/*raygenShaderBindingOffset，raygenShaderBindingTableBuffer中数据的起始字节偏移量*/,
			missShaderBindingTableBuffer/*missShaderBindingTableBuffer,包含用于miss shader stage的shader binding table data.*/, 0/*missShaderBindingOffset， missShaderBindingTableBuffer中数据的起始字节偏移量*/,1/*missShaderBindingStride,为missShaderBindingTableBuffer 中每个shader binding table的字节数大小.*/,
			hitShaderBindingTableBuffer/*hitShaderBindingTableBuffer,包含用于hit shader stage的shader binding table data.*/, 0/*hitShaderBindingOffset，hitShaderBindingTableBuffer中数据的起始字节偏移量*/, 1/*hitShaderBindingStride,为hitShaderBindingTableBuffer 中每个shader binding table的字节数大小.*/,
			callableShaderBindingTableBuffer/*callableShaderBindingTableBuffer,包含用于callable shader stage的shader binding table data.*/, 0/*callableShaderBindingOffset， callableShaderBindingTableBuffer中数据的起始字节偏移量*/, 1/*callableShaderBindingStride,为callableShaderBindingTableBuffer 中每个shader binding table的字节数大小.*/,
			1/*width,为ray trace query dimensions的width.*/, 1/*height,为ray trace query dimensions的height.*/, 1/*depth,为ray trace query dimensions的depth.*/);
		/*
		vkCmdTraceRaysNV有效用法:
		1.如果一个VkSampler以其magFilter或者minFilter等于VK_FILTER_LINEAR创建，则（1）如果reductionMode为VK_SAMPLER_REDUCTION_MODE_WEIGHTED_AVERAGE，如果用于采样一个VkImageView作为该命令的结果的compareEnable为VK_FALSE，则该image view的format features必须包含VK_FORMAT_FEATURE_SAMPLED_IMAGE_FILTER_LINEAR_BIT
																				 （2）如果reductionMode为VK_SAMPLER_REDUCTION_MODE_MIN 或者VK_SAMPLER_REDUCTION_MODE_MAX之一 用于采样一个VkImageView作为该命令的结果，则该image view的format features必须包含VK_FORMAT_FEATURE_SAMPLED_IMAGE_FILTER_MINMAX_BIT
		2.如果一个VkSampler以其mipmapMode 等于VK_SAMPLER_MIPMAP_MODE_LINEAR创建，则（1）如果reductionMode为VK_SAMPLER_REDUCTION_MODE_WEIGHTED_AVERAGE，如果用于采样一个VkImageView作为该命令的结果的compareEnable为VK_FALSE，则该image view的format features必须包含VK_FORMAT_FEATURE_SAMPLED_IMAGE_FILTER_LINEAR_BIT
																				 （2）如果reductionMode为VK_SAMPLER_REDUCTION_MODE_MIN 或者VK_SAMPLER_REDUCTION_MODE_MAX之一 用于采样一个VkImageView作为该命令的结果，则该image view的format features必须包含VK_FORMAT_FEATURE_SAMPLED_IMAGE_FILTER_MINMAX_BIT
		3.如果一个VkSampler以其unnormalizedCoordinates等于VK_TRUE用于采样一个VkImageView作为该命令的结果创建，则（1）该image view的levelCount以及layerCount必须为1
																												（2）该image view的viewType必须为VK_IMAGE_VIEW_TYPE_1D 或者 VK_IMAGE_VIEW_TYPE_2D
		4.如果一个VkImageView的采样带depth comparison操作，则image view的format features必须包含VK_FORMAT_FEATURE_2_SAMPLED_IMAGE_DEPTH_COMPARISON_BIT
		5.如果一个VkImageView使用atomic operations作为该命令的结果进行访问，则image view的format features必须包含VK_FORMAT_FEATURE_STORAGE_IMAGE_ATOMIC_BIT
		6.如果一个VK_DESCRIPTOR_TYPE_STORAGE_TEXEL_BUFFER类型的 descriptor使用atomic operations作为该命令的结果进行访问，则storage texel buffer的format features必须包含VK_FORMAT_FEATURE_STORAGE_TEXEL_BUFFER_ATOMIC_BIT
		7.如果一个以VK_FILTER_CUBIC_EXT进行采样的VkImageView作为该命令的结果，则image view的format features必须包含VK_FORMAT_FEATURE_SAMPLED_IMAGE_FILTER_CUBIC_BIT_EXT
		8.如果VK_EXT_filter_cubic拓展没有开启，且有任何一个以VK_FILTER_CUBIC_EXT进行采样的VkImageView作为该命令的结果，则其VkImageViewType不能为VK_IMAGE_VIEW_TYPE_3D, VK_IMAGE_VIEW_TYPE_CUBE, 或者 VK_IMAGE_VIEW_TYPE_CUBE_ARRAY
		9.任何一个以VK_FILTER_CUBIC_EXT进行采样的作为该命令的结果的VkImageView，其VkImageViewType和format 必须支持cubic filtering，参见vkGetPhysicalDeviceImageFormatProperties2返回的VkFilterCubicImageViewImageFormatPropertiesEXT::filterCubic
		10.任何一个以VK_FILTER_CUBIC_EXT进行采样且reduction mode为VK_SAMPLER_REDUCTION_MODE_MIN 或者 VK_SAMPLER_REDUCTION_MODE_MAX之一的作为该命令的结果的VkImageView，其VkImageViewType和format 必须支持带minmax filtering的cubic filtering，参见vkGetPhysicalDeviceImageFormatProperties2返回的VkFilterCubicImageViewImageFormatPropertiesEXT::filterCubicMinmax
		11.如果cubicRangeClamp特性没有开启，则有任何一个以VK_FILTER_CUBIC_EXT进行采样VkImageView的作为该命令的结果，VkSamplerReductionModeCreateInfo::reductionMode不能为VK_SAMPLER_REDUCTION_MODE_WEIGHTED_AVERAGE_RANGECLAMP_QCOM
		12.任何一个以VkSamplerReductionModeCreateInfo::reductionMode为VK_SAMPLER_REDUCTION_MODE_WEIGHTED_AVERAGE_RANGECLAMP_QCOM进行采样的作为该命令的结果的VkImageView必须以VK_FILTER_CUBIC_EXT进行采样
		13.如果selectableCubicWeights特性没有开启，则有任何一个以VK_FILTER_CUBIC_EXT进行采样VkImageView的作为该命令的结果，VkSamplerCubicWeightsCreateInfoQCOM::cubicWeights必须为VK_CUBIC_FILTER_WEIGHTS_CATMULL_ROM_QCOM
		14.任何一个以VkImageCreateInfo::flags含VK_IMAGE_CREATE_CORNER_SAMPLED_BIT_NV创建的采样作为该命令结果的VkImage必须以VkSamplerAddressMode为VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE 进行采样
		15.对于任何作为storage image写入的VkImageView，且其OpTypeImage的format未知，则该image view的 format features必须包含VK_FORMAT_FEATURE_2_STORAGE_WRITE_WITHOUT_FORMAT_BIT
		16.对于任何作为storage image读取的VkImageView，且其OpTypeImage的format未知，则该image view的 format features必须包含VK_FORMAT_FEATURE_2_STORAGE_READ_WITHOUT_FORMAT_BIT
		17.对于任何作为storage storage texel buffer写入的VkBufferView，且其OpTypeImage的format未知，则该buffer view的 buffer features必须包含VK_FORMAT_FEATURE_2_STORAGE_WRITE_WITHOUT_FORMAT_BIT
		18.对于任何作为storage storage texel buffer读取的VkBufferView，且其OpTypeImage的format未知，则该buffer view的 buffer features必须包含VK_FORMAT_FEATURE_2_STORAGE_READ_WITHOUT_FORMAT_BIT
		19.对于每个在绑定的shader中静态使用的set n，一个descriptor set必须被绑定到相同pipeline bind point的set n处，该set n必须和创建当前VkPipeline的VkPipelineLayout或者和创建当前VkShaderEXT的VkDescriptorSetLayout 数组的set n处的布局兼容，参见Pipeline Layout Compatibility p1280
		20.对于每个在绑定的shader中静态使用的push constant，一个push constant值必须被绑定到相同pipeline bind point的对应处，该push constant必须和创建当前VkPipeline的VkPipelineLayout或者和创建当前VkShaderEXT的VkDescriptorSetLayout 数组中的对应处的布局兼容，参见Pipeline Layout Compatibility p1280
		21.如果maintenance4特性没有开启，则对于每个在绑定的shader中静态使用的push constant，一个push constant值必须被设置到相同pipeline bind point的对应处，该push constant必须和创建当前VkPipeline的VkPipelineLayout或者和创建当前VkShaderEXT的VkDescriptorSetLayout 数组中的对应处的布局兼容，参见Pipeline Layout Compatibility p1280
		22.每一个通过vkCmdBindDescriptorSets绑定的descriptor set的descriptors,如果是被不以VK_PIPELINE_CREATE_DESCRIPTOR_BUFFER_BIT_EXT创建的，且已经绑定到该命令使用的pipeline bind point的VkPipeline静态使用的，则这些descriptors必须是有效的，参见 descriptor validity p1328
		23.如果通过vkCmdBindDescriptorSets指定绑定到pipeline bind point的VkPipeline要使用的descriptors，则绑定的VkPipeline不能以VK_PIPELINE_CREATE_DESCRIPTOR_BUFFER_BIT_EXT创建
		24.在vkCmdSetDescriptorBufferOffsetsEXT中指定绑定的descriptor buffers的descriptors，则（1）如果绑定到pipeline bind point的该命令会使用的VkPipeline以VK_PIPELINE_CREATE_DESCRIPTOR_BUFFER_BIT_EXT创建，且这些descriptors是动态使用的，则这些descriptors必须是有效的
																							  （2）如果绑定到pipeline bind point的对应stage的该命令会使用的VkShaderEXT，且这些descriptors是动态使用的，则这些descriptors必须是有效的
		25.在vkCmdSetDescriptorBufferOffsetsEXT中指定的descriptors在绑定到pipeline bind point的VkPipeline中使用，则VkPipeline必须以VK_PIPELINE_CREATE_DESCRIPTOR_BUFFER_BIT_EXT创建
		26.如果一个descriptor在以VK_PIPELINE_CREATE_DESCRIPTOR_BUFFER_BIT_EXT创建的VkPipeline中动态使用，则descriptor memory必须是驻留内存
		27.如果一个descriptor在以其VkDescriptorSetLayout以VK_DESCRIPTOR_SET_LAYOUT_CREATE_DESCRIPTOR_BUFFER_BIT_EXT创建的VkShaderEXT中动态使用，则descriptor memory必须是驻留内存
		28.如果shaderObject 特性没有开启，一个有效的pipeline必须绑定到这个命令使用的绑定到pipeline bind point上
		29.如果一个pipeline绑定到该命令使用的pipeline bind point上，则不能有任何动态state 设置命令设置任何该VkPipeline 中没有指定的动态 state
		30.如果一个VkPipeline绑定到该命令使用的pipeline bind point上 或者任何一个会访问一个使用unnormalized coordinates的VkSampler的 VkShaderEXT绑定到该命令使用的pipeline bind point上的pipeline的对应stage，则
																					（1）在任何shader stage中，VkSampler不能用来采样任何类型为VK_IMAGE_VIEW_TYPE_3D, VK_IMAGE_VIEW_TYPE_CUBE, VK_IMAGE_VIEW_TYPE_1D_ARRAY, VK_IMAGE_VIEW_TYPE_2D_ARRAY 或者 VK_IMAGE_VIEW_TYPE_CUBE_ARRAY的VkImageView
																					（2）在任何shader stage中，该VkSampler不能和任何带有名字中带有ImplicitLod，Dref 或者 Proj 的SPIR-V OpImageSample* 或者 OpImageSparseSample*指令一起使用
																					（3）在任何shader stage中，该VkSampler不能和任何包含 LOD bias或者offset 值 的SPIR-V OpImageSample* or OpImageSparseSample*指令一起使用
		31.如果shaderObject开启，一个有效的pipeline必须绑定到该命令使用的pipeline bind point上或者一个有效的shader objects以及VK_NULL_HANDLE的组合必须绑定到该命令使用的pipeline bind point每一个支持的shader stage上
		32.如何绑定到该命令使用的pipeline bind point上的VkPipeline的任何stage会访问一个uniform buffer，且该stage对uniformBuffers不以启用VK_PIPELINE_ROBUSTNESS_BUFFER_BEHAVIOR_ROBUST_BUFFER_ACCESS_EXT或者VK_PIPELINE_ROBUSTNESS_BUFFER_BEHAVIOR_ROBUST_BUFFER_ACCESS_2_EXT 创建，且robustBufferAccess特性未开启，则该stage就不能访问绑定到相同pipeline bind point的descriptor set指定的buffer范围外的值
		33.如果robustBufferAccess特性未开启，且任何会访问uniform buffer的绑定到该命令使用的pipeline bind point上对应shader stage的VkShaderEXT，则其不能访问绑定到相同pipeline bind point的descriptor set指定的buffer范围外的值
		34.如何绑定到该命令使用的pipeline bind point上的VkPipeline的任何stage会访问一个storage buffer，且该stage对storageBuffers不以启用VK_PIPELINE_ROBUSTNESS_BUFFER_BEHAVIOR_ROBUST_BUFFER_ACCESS_EXT或者VK_PIPELINE_ROBUSTNESS_BUFFER_BEHAVIOR_ROBUST_BUFFER_ACCESS_2_EXT 创建，且robustBufferAccess特性未开启，则该stage就不能访问绑定到相同pipeline bind point的descriptor set指定的buffer范围外的值
		35.如果robustBufferAccess特性未开启，且任何会访问storage buffer的绑定到该命令使用的pipeline bind point上对应shader stage的VkShaderEXT，则其不能访问绑定到相同pipeline bind point的descriptor set指定的buffer范围外的值
		36.如果commandBuffer 是一个unprotected command buffer，且protectedNoFault 未支持，则任何绑定的shaders访问的资源不能是一个protected resource
		37.如果一个绑定的shader访问一个VkSampler 或者 VkImageView ，且启用了sampler Y′C BCR conversion，则只能使用OpImageSample* 或者 OpImageSparseSample*指令，不能使用ConstOffset 以及 Offset操作符
		38.如果一个VkImageView作为该命令的结果进行访问，则（1）image view 的viewType 必须匹配Instruction/Sampler/Image View Validation p1481中描述的OpTypeImage的Dim操作符
														  （2）image view 的foamrt的numeric type 必须匹配OpTypeImage的Sampled Type操作符
		39.如果一个VkImageView以一个不是VK_FORMAT_A8_UNORM_KHR的format创建且通过OpImageWrite作为该命令的结果进行访问，则该命令的Texel 操作符的Type必须至少包含和 image view的 format含有的components的个数相同的components个数
		40.如果一个VkImageView以VK_FORMAT_A8_UNORM_KHR的format创建且通过OpImageWrite作为该命令的结果进行访问，则该命令的Texel 操作符的Type必须包含4个components
		41.如果一个VkBufferView通过OpImageWrite作为该命令的结果进行访问，则该命令的Texel 操作符的Type必须至少包含和 buffer view的 format含有的components的个数相同的components个数
		42.如果一个带64-bit component的VkFormat的VkImageView作为该命令的结果进行访问，则该命令的OpTypeImage操作符的SampledType的宽度必须为64
		43.如果一个带少于64-bit component的VkFormat的VkImageView作为该命令的结果进行访问，则该命令的OpTypeImage操作符的SampledType的宽度必须为32
		44.如果一个带64-bit component的VkFormat的VkBufferView作为该命令的结果进行访问，则该命令的OpTypeImage操作符的SampledType的宽度必须为64位
		45.如果一个带少于64-bit component的VkFormat的VkBufferView作为该命令的结果进行访问，则该命令的OpTypeImage操作符的SampledType的宽度必须为32
		46.如果sparseImageInt64Atomics 特性未开启，则以VK_IMAGE_CREATE_SPARSE_RESIDENCY_BIT创建的VkImage对象不能被SampledType宽度为64位的OpTypeImage的atomic instructions访问
		47.如果sparseImageInt64Atomics 特性未开启，则以VK_BUFFER_CREATE_SPARSE_RESIDENCY_BIT创建的VkBuffer对象不能被SampledType宽度为64位的OpTypeImage的atomic instructions访问
		48.如果OpImageWeightedSampleQCOM用来采样一个作为该命令的结果的VkImageView，则该image view的format features必须包含VK_FORMAT_FEATURE_2_WEIGHT_SAMPLED_IMAGE_BIT_QCOM
		49.如果OpImageWeightedSampleQCOM用来采样一个作为该命令的结果的sample weight image的VkImageView，则该image view的format features必须包含VK_FORMAT_FEATURE_2_WEIGHT_IMAGE_BIT_QCOM
		50.如果OpImageBoxFilterQCOM用来采样一个作为该命令的结果的VkImageView，则该image view的format features必须包含VK_FORMAT_FEATURE_2_BOX_FILTER_SAMPLED_BIT_QCOM
		51.如果OpImageBlockMatchSSDQCOM，或者 OpImageBlockMatchSADQCOM用来读取一个作为该命令的结果的VkImageView，则（1）该image view的format features必须包含VK_FORMAT_FEATURE_2_BLOCK_MATCHING_BIT_QCOM
																												   （2）如果是读取的reference image，指定的reference coordinates不能在integer texel coordinate validation 时候失败
		52.如果OpImageWeightedSampleQCOM, OpImageBoxFilterQCOM, OpImageBlockMatchWindowSSDQCOM, OpImageBlockMatchWindowSADQCOM, OpImageBlockMatchGatherSSDQCOM,
													OpImageBlockMatchGatherSADQCOM, OpImageBlockMatchSSDQCOM, 或者 OpImageBlockMatchSADQCOM用来采样一个作为该命令的结果的VkImageView，则该VkSampler必须以VK_SAMPLER_CREATE_IMAGE_PROCESSING_BIT_QCOM创建
		53.如果任何除了OpImageWeightedSampleQCOM, OpImageBoxFilterQCOM, OpImageBlockMatchWindowSSDQCOM, OpImageBlockMatchWindowSADQCOM, OpImageBlockMatchGatherSSDQCOM, OpImageBlockMatchGatherSADQCOM, OpImageBlockMatchSSDQCOM, 或者 OpImageBlockMatchSADQCOM之外的指令使用VkSampler进行采样作为该命令的结果，则该sampler不能以VK_SAMPLER_CREATE_IMAGE_PROCESSING_BIT_QCOM 创建
		54.如果OpImageBlockMatchWindow*QCOM or OpImageBlockMatchGather*QCOM指令用来读取VkImageView作为该命令的结果，则（1）VkImageView的format features必须包含VK_FORMAT_FEATURE_2_BLOCK_MATCHING_BIT_QCOM
																													  （2）VkImageView的format必须只含有一个component
		55.如果OpImageBlockMatchWindow*QCOM or OpImageBlockMatchGather*QCOM指令用来读取一个引用的image作为该命令的结果，则指定的 reference coordinates不能在integer texel coordinate validation 时候失败
		56.任何该命令执行的shader invocation必须已经终止
		57.如果有一个类型为VK_DESCRIPTOR_TYPE_SAMPLE_WEIGHT_IMAGE_QCOM, VK_DESCRIPTOR_TYPE_BLOCK_MATCH_IMAGE_QCOM, VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE, VK_DESCRIPTOR_TYPE_STORAGE_IMAGE, 或者 VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT中任意一个的descriptor作为该命令的结果进行访问，则该descriptor所指的image subresource的layout必须和该descriptor被写入时的layout相同。
		58.任何该调用引用的shader group handle 必须已经在当前绑定的ray tracing pipeline中查询过。
		59.如果绑定的tracing pipeline 以VK_DYNAMIC_STATE_RAY_TRACING_PIPELINE_STACK_SIZE_KHR 动态状态创建，则该命令必须在当前命令缓冲区之前调用 vkCmdSetRayTracingPipelineStackSizeKHR。
		60.commandBuffer 必须不能是protected command buffer。
		61.该命令不能造成一个在shader invocation上执行的pipeline trace ray instruction的递归深度超过了创建该pipeline的maxRecursionDepth。
		62.如果raygenShaderBindingTableBuffer 是non-sparse的则其必须绑定到完整的连续的单独的VkDeviceMemory对象上。
		63.raygenShaderBindingOffset 必须小于等于raygenShaderBindingTableBuffer的大小，且必须是VkPhysicalDeviceRayTracingPropertiesNV::shaderGroupBaseAlignment的倍数。
		64.如果missShaderBindingTableBuffer 是non-sparse的则其必须绑定到完整的连续的单独的VkDeviceMemory对象上。
		65.missShaderBindingOffset 必须小于等于missShaderBindingTableBuffer的大小，且必须是VkPhysicalDeviceRayTracingPropertiesNV::shaderGroupBaseAlignment的倍数。
		66.如果hitShaderBindingTableBuffer 是non-sparse的则其必须绑定到完整的连续的单独的VkDeviceMemory对象上。
		67.hitShaderBindingOffset 必须小于等于hitShaderBindingTableBuffer的大小，且必须是VkPhysicalDeviceRayTracingPropertiesNV::shaderGroupBaseAlignment的倍数。
		68.如果callableShaderBindingTableBuffer 是non-sparse的则其必须绑定到完整的连续的单独的VkDeviceMemory对象上。
		69.callableShaderBindingOffset 必须小于等于callableShaderBindingTableBuffer的大小，且必须是VkPhysicalDeviceRayTracingPropertiesNV::shaderGroupBaseAlignment的倍数。
		70.missShaderBindingStride，hitShaderBindingStride以及callableShaderBindingStride 必须是VkPhysicalDeviceRayTracingPropertiesNV::shaderGroupHandleSize的倍数，且都必须小于等于VkPhysicalDeviceRayTracingPropertiesNV::maxShaderGroupStride。
		71.width，height以及depth必须对应小于等于VkPhysicalDeviceLimits::maxComputeWorkGroupCount[0], VkPhysicalDeviceLimits::maxComputeWorkGroupCount[1], VkPhysicalDeviceLimits::maxComputeWorkGroupCount[2]。
		*/


		VkStridedDeviceAddressRegionKHR raygenShaderBindingTable{};
		raygenShaderBindingTable.deviceAddress = VkDeviceAddress{/*假设这是一个有效的VkDeviceAddress*/ };
		raygenShaderBindingTable.stride = 3;
		raygenShaderBindingTable.size = 3;

		VkStridedDeviceAddressRegionKHR missShaderBindingTable{};
		missShaderBindingTable.deviceAddress = VkDeviceAddress{/*假设这是一个有效的VkDeviceAddress*/ };
		missShaderBindingTable.stride = 3;
		missShaderBindingTable.size = 3;

		VkStridedDeviceAddressRegionKHR hitShaderBindingTable{};
		hitShaderBindingTable.deviceAddress = VkDeviceAddress{/*假设这是一个有效的VkDeviceAddress*/ };
		hitShaderBindingTable.stride = 3;
		hitShaderBindingTable.size = 3;

		VkStridedDeviceAddressRegionKHR callableShaderBindingTable{};
		callableShaderBindingTable.deviceAddress = VkDeviceAddress{/*假设这是一个有效的VkDeviceAddress*/ };
		callableShaderBindingTable.stride = 3;
		callableShaderBindingTable.size = 3;


		//dispatch ray tracing,   执行该命令，则一个包含 width × height × depth 条ray的ray 产生组会被组装
		vkCmdTraceRaysKHR(commandBuffer,
			&raygenShaderBindingTable,
			&missShaderBindingTable,
			&hitShaderBindingTable,
			&callableShaderBindingTable,
			1/*width,为ray trace query dimensions的width.*/, 1/*height,为ray trace query dimensions的height.*/, 1/*depth,为ray trace query dimensions的depth.*/);
		/*
		vkCmdTraceRaysKHR有效用法:
		1.如果一个VkSampler以其magFilter或者minFilter等于VK_FILTER_LINEAR创建，则（1）如果reductionMode为VK_SAMPLER_REDUCTION_MODE_WEIGHTED_AVERAGE，如果用于采样一个VkImageView作为该命令的结果的compareEnable为VK_FALSE，则该image view的format features必须包含VK_FORMAT_FEATURE_SAMPLED_IMAGE_FILTER_LINEAR_BIT
																				 （2）如果reductionMode为VK_SAMPLER_REDUCTION_MODE_MIN 或者VK_SAMPLER_REDUCTION_MODE_MAX之一 用于采样一个VkImageView作为该命令的结果，则该image view的format features必须包含VK_FORMAT_FEATURE_SAMPLED_IMAGE_FILTER_MINMAX_BIT
		2.如果一个VkSampler以其mipmapMode 等于VK_SAMPLER_MIPMAP_MODE_LINEAR创建，则（1）如果reductionMode为VK_SAMPLER_REDUCTION_MODE_WEIGHTED_AVERAGE，如果用于采样一个VkImageView作为该命令的结果的compareEnable为VK_FALSE，则该image view的format features必须包含VK_FORMAT_FEATURE_SAMPLED_IMAGE_FILTER_LINEAR_BIT
																				 （2）如果reductionMode为VK_SAMPLER_REDUCTION_MODE_MIN 或者VK_SAMPLER_REDUCTION_MODE_MAX之一 用于采样一个VkImageView作为该命令的结果，则该image view的format features必须包含VK_FORMAT_FEATURE_SAMPLED_IMAGE_FILTER_MINMAX_BIT
		3.如果一个VkSampler以其unnormalizedCoordinates等于VK_TRUE用于采样一个VkImageView作为该命令的结果创建，则（1）该image view的levelCount以及layerCount必须为1
																												（2）该image view的viewType必须为VK_IMAGE_VIEW_TYPE_1D 或者 VK_IMAGE_VIEW_TYPE_2D
		4.如果一个VkImageView的采样带depth comparison操作，则image view的format features必须包含VK_FORMAT_FEATURE_2_SAMPLED_IMAGE_DEPTH_COMPARISON_BIT
		5.如果一个VkImageView使用atomic operations作为该命令的结果进行访问，则image view的format features必须包含VK_FORMAT_FEATURE_STORAGE_IMAGE_ATOMIC_BIT
		6.如果一个VK_DESCRIPTOR_TYPE_STORAGE_TEXEL_BUFFER类型的 descriptor使用atomic operations作为该命令的结果进行访问，则storage texel buffer的format features必须包含VK_FORMAT_FEATURE_STORAGE_TEXEL_BUFFER_ATOMIC_BIT
		7.如果一个以VK_FILTER_CUBIC_EXT进行采样的VkImageView作为该命令的结果，则image view的format features必须包含VK_FORMAT_FEATURE_SAMPLED_IMAGE_FILTER_CUBIC_BIT_EXT
		8.如果VK_EXT_filter_cubic拓展没有开启，且有任何一个以VK_FILTER_CUBIC_EXT进行采样的VkImageView作为该命令的结果，则其VkImageViewType不能为VK_IMAGE_VIEW_TYPE_3D, VK_IMAGE_VIEW_TYPE_CUBE, 或者 VK_IMAGE_VIEW_TYPE_CUBE_ARRAY
		9.任何一个以VK_FILTER_CUBIC_EXT进行采样的作为该命令的结果的VkImageView，其VkImageViewType和format 必须支持cubic filtering，参见vkGetPhysicalDeviceImageFormatProperties2返回的VkFilterCubicImageViewImageFormatPropertiesEXT::filterCubic
		10.任何一个以VK_FILTER_CUBIC_EXT进行采样且reduction mode为VK_SAMPLER_REDUCTION_MODE_MIN 或者 VK_SAMPLER_REDUCTION_MODE_MAX之一的作为该命令的结果的VkImageView，其VkImageViewType和format 必须支持带minmax filtering的cubic filtering，参见vkGetPhysicalDeviceImageFormatProperties2返回的VkFilterCubicImageViewImageFormatPropertiesEXT::filterCubicMinmax
		11.如果cubicRangeClamp特性没有开启，则有任何一个以VK_FILTER_CUBIC_EXT进行采样VkImageView的作为该命令的结果，VkSamplerReductionModeCreateInfo::reductionMode不能为VK_SAMPLER_REDUCTION_MODE_WEIGHTED_AVERAGE_RANGECLAMP_QCOM
		12.任何一个以VkSamplerReductionModeCreateInfo::reductionMode为VK_SAMPLER_REDUCTION_MODE_WEIGHTED_AVERAGE_RANGECLAMP_QCOM进行采样的作为该命令的结果的VkImageView必须以VK_FILTER_CUBIC_EXT进行采样
		13.如果selectableCubicWeights特性没有开启，则有任何一个以VK_FILTER_CUBIC_EXT进行采样VkImageView的作为该命令的结果，VkSamplerCubicWeightsCreateInfoQCOM::cubicWeights必须为VK_CUBIC_FILTER_WEIGHTS_CATMULL_ROM_QCOM
		14.任何一个以VkImageCreateInfo::flags含VK_IMAGE_CREATE_CORNER_SAMPLED_BIT_NV创建的采样作为该命令结果的VkImage必须以VkSamplerAddressMode为VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE 进行采样
		15.对于任何作为storage image写入的VkImageView，且其OpTypeImage的format未知，则该image view的 format features必须包含VK_FORMAT_FEATURE_2_STORAGE_WRITE_WITHOUT_FORMAT_BIT
		16.对于任何作为storage image读取的VkImageView，且其OpTypeImage的format未知，则该image view的 format features必须包含VK_FORMAT_FEATURE_2_STORAGE_READ_WITHOUT_FORMAT_BIT
		17.对于任何作为storage storage texel buffer写入的VkBufferView，且其OpTypeImage的format未知，则该buffer view的 buffer features必须包含VK_FORMAT_FEATURE_2_STORAGE_WRITE_WITHOUT_FORMAT_BIT
		18.对于任何作为storage storage texel buffer读取的VkBufferView，且其OpTypeImage的format未知，则该buffer view的 buffer features必须包含VK_FORMAT_FEATURE_2_STORAGE_READ_WITHOUT_FORMAT_BIT
		19.对于每个在绑定的shader中静态使用的set n，一个descriptor set必须被绑定到相同pipeline bind point的set n处，该set n必须和创建当前VkPipeline的VkPipelineLayout或者和创建当前VkShaderEXT的VkDescriptorSetLayout 数组的set n处的布局兼容，参见Pipeline Layout Compatibility p1280
		20.对于每个在绑定的shader中静态使用的push constant，一个push constant值必须被绑定到相同pipeline bind point的对应处，该push constant必须和创建当前VkPipeline的VkPipelineLayout或者和创建当前VkShaderEXT的VkDescriptorSetLayout 数组中的对应处的布局兼容，参见Pipeline Layout Compatibility p1280
		21.如果maintenance4特性没有开启，则对于每个在绑定的shader中静态使用的push constant，一个push constant值必须被设置到相同pipeline bind point的对应处，该push constant必须和创建当前VkPipeline的VkPipelineLayout或者和创建当前VkShaderEXT的VkDescriptorSetLayout 数组中的对应处的布局兼容，参见Pipeline Layout Compatibility p1280
		22.每一个通过vkCmdBindDescriptorSets绑定的descriptor set的descriptors,如果是被不以VK_PIPELINE_CREATE_DESCRIPTOR_BUFFER_BIT_EXT创建的，且已经绑定到该命令使用的pipeline bind point的VkPipeline静态使用的，则这些descriptors必须是有效的，参见 descriptor validity p1328
		23.如果通过vkCmdBindDescriptorSets指定绑定到pipeline bind point的VkPipeline要使用的descriptors，则绑定的VkPipeline不能以VK_PIPELINE_CREATE_DESCRIPTOR_BUFFER_BIT_EXT创建
		24.在vkCmdSetDescriptorBufferOffsetsEXT中指定绑定的descriptor buffers的descriptors，则（1）如果绑定到pipeline bind point的该命令会使用的VkPipeline以VK_PIPELINE_CREATE_DESCRIPTOR_BUFFER_BIT_EXT创建，且这些descriptors是动态使用的，则这些descriptors必须是有效的
																							  （2）如果绑定到pipeline bind point的对应stage的该命令会使用的VkShaderEXT，且这些descriptors是动态使用的，则这些descriptors必须是有效的
		25.在vkCmdSetDescriptorBufferOffsetsEXT中指定的descriptors在绑定到pipeline bind point的VkPipeline中使用，则VkPipeline必须以VK_PIPELINE_CREATE_DESCRIPTOR_BUFFER_BIT_EXT创建
		26.如果一个descriptor在以VK_PIPELINE_CREATE_DESCRIPTOR_BUFFER_BIT_EXT创建的VkPipeline中动态使用，则descriptor memory必须是驻留内存
		27.如果一个descriptor在以其VkDescriptorSetLayout以VK_DESCRIPTOR_SET_LAYOUT_CREATE_DESCRIPTOR_BUFFER_BIT_EXT创建的VkShaderEXT中动态使用，则descriptor memory必须是驻留内存
		28.如果shaderObject 特性没有开启，一个有效的pipeline必须绑定到这个命令使用的绑定到pipeline bind point上
		29.如果一个pipeline绑定到该命令使用的pipeline bind point上，则不能有任何动态state 设置命令设置任何该VkPipeline 中没有指定的动态 state
		30.如果一个VkPipeline绑定到该命令使用的pipeline bind point上 或者任何一个会访问一个使用unnormalized coordinates的VkSampler的 VkShaderEXT绑定到该命令使用的pipeline bind point上的pipeline的对应stage，则
																					（1）在任何shader stage中，VkSampler不能用来采样任何类型为VK_IMAGE_VIEW_TYPE_3D, VK_IMAGE_VIEW_TYPE_CUBE, VK_IMAGE_VIEW_TYPE_1D_ARRAY, VK_IMAGE_VIEW_TYPE_2D_ARRAY 或者 VK_IMAGE_VIEW_TYPE_CUBE_ARRAY的VkImageView
																					（2）在任何shader stage中，该VkSampler不能和任何带有名字中带有ImplicitLod，Dref 或者 Proj 的SPIR-V OpImageSample* 或者 OpImageSparseSample*指令一起使用
																					（3）在任何shader stage中，该VkSampler不能和任何包含 LOD bias或者offset 值 的SPIR-V OpImageSample* or OpImageSparseSample*指令一起使用
		31.如果shaderObject开启，一个有效的pipeline必须绑定到该命令使用的pipeline bind point上或者一个有效的shader objects以及VK_NULL_HANDLE的组合必须绑定到该命令使用的pipeline bind point每一个支持的shader stage上
		32.如何绑定到该命令使用的pipeline bind point上的VkPipeline的任何stage会访问一个uniform buffer，且该stage对uniformBuffers不以启用VK_PIPELINE_ROBUSTNESS_BUFFER_BEHAVIOR_ROBUST_BUFFER_ACCESS_EXT或者VK_PIPELINE_ROBUSTNESS_BUFFER_BEHAVIOR_ROBUST_BUFFER_ACCESS_2_EXT 创建，且robustBufferAccess特性未开启，则该stage就不能访问绑定到相同pipeline bind point的descriptor set指定的buffer范围外的值
		33.如果robustBufferAccess特性未开启，且任何会访问uniform buffer的绑定到该命令使用的pipeline bind point上对应shader stage的VkShaderEXT，则其不能访问绑定到相同pipeline bind point的descriptor set指定的buffer范围外的值
		34.如何绑定到该命令使用的pipeline bind point上的VkPipeline的任何stage会访问一个storage buffer，且该stage对storageBuffers不以启用VK_PIPELINE_ROBUSTNESS_BUFFER_BEHAVIOR_ROBUST_BUFFER_ACCESS_EXT或者VK_PIPELINE_ROBUSTNESS_BUFFER_BEHAVIOR_ROBUST_BUFFER_ACCESS_2_EXT 创建，且robustBufferAccess特性未开启，则该stage就不能访问绑定到相同pipeline bind point的descriptor set指定的buffer范围外的值
		35.如果robustBufferAccess特性未开启，且任何会访问storage buffer的绑定到该命令使用的pipeline bind point上对应shader stage的VkShaderEXT，则其不能访问绑定到相同pipeline bind point的descriptor set指定的buffer范围外的值
		36.如果commandBuffer 是一个unprotected command buffer，且protectedNoFault 未支持，则任何绑定的shaders访问的资源不能是一个protected resource
		37.如果一个绑定的shader访问一个VkSampler 或者 VkImageView ，且启用了sampler Y′C BCR conversion，则只能使用OpImageSample* 或者 OpImageSparseSample*指令，不能使用ConstOffset 以及 Offset操作符
		38.如果一个VkImageView作为该命令的结果进行访问，则（1）image view 的viewType 必须匹配Instruction/Sampler/Image View Validation p1481中描述的OpTypeImage的Dim操作符
														  （2）image view 的foamrt的numeric type 必须匹配OpTypeImage的Sampled Type操作符
		39.如果一个VkImageView以一个不是VK_FORMAT_A8_UNORM_KHR的format创建且通过OpImageWrite作为该命令的结果进行访问，则该命令的Texel 操作符的Type必须至少包含和 image view的 format含有的components的个数相同的components个数
		40.如果一个VkImageView以VK_FORMAT_A8_UNORM_KHR的format创建且通过OpImageWrite作为该命令的结果进行访问，则该命令的Texel 操作符的Type必须包含4个components
		41.如果一个VkBufferView通过OpImageWrite作为该命令的结果进行访问，则该命令的Texel 操作符的Type必须至少包含和 buffer view的 format含有的components的个数相同的components个数
		42.如果一个带64-bit component的VkFormat的VkImageView作为该命令的结果进行访问，则该命令的OpTypeImage操作符的SampledType的宽度必须为64
		43.如果一个带少于64-bit component的VkFormat的VkImageView作为该命令的结果进行访问，则该命令的OpTypeImage操作符的SampledType的宽度必须为32
		44.如果一个带64-bit component的VkFormat的VkBufferView作为该命令的结果进行访问，则该命令的OpTypeImage操作符的SampledType的宽度必须为64位
		45.如果一个带少于64-bit component的VkFormat的VkBufferView作为该命令的结果进行访问，则该命令的OpTypeImage操作符的SampledType的宽度必须为32
		46.如果sparseImageInt64Atomics 特性未开启，则以VK_IMAGE_CREATE_SPARSE_RESIDENCY_BIT创建的VkImage对象不能被SampledType宽度为64位的OpTypeImage的atomic instructions访问
		47.如果sparseImageInt64Atomics 特性未开启，则以VK_BUFFER_CREATE_SPARSE_RESIDENCY_BIT创建的VkBuffer对象不能被SampledType宽度为64位的OpTypeImage的atomic instructions访问
		48.如果OpImageWeightedSampleQCOM用来采样一个作为该命令的结果的VkImageView，则该image view的format features必须包含VK_FORMAT_FEATURE_2_WEIGHT_SAMPLED_IMAGE_BIT_QCOM
		49.如果OpImageWeightedSampleQCOM用来采样一个作为该命令的结果的sample weight image的VkImageView，则该image view的format features必须包含VK_FORMAT_FEATURE_2_WEIGHT_IMAGE_BIT_QCOM
		50.如果OpImageBoxFilterQCOM用来采样一个作为该命令的结果的VkImageView，则该image view的format features必须包含VK_FORMAT_FEATURE_2_BOX_FILTER_SAMPLED_BIT_QCOM
		51.如果OpImageBlockMatchSSDQCOM，或者 OpImageBlockMatchSADQCOM用来读取一个作为该命令的结果的VkImageView，则（1）该image view的format features必须包含VK_FORMAT_FEATURE_2_BLOCK_MATCHING_BIT_QCOM
																												   （2）如果是读取的reference image，指定的reference coordinates不能在integer texel coordinate validation 时候失败
		52.如果OpImageWeightedSampleQCOM, OpImageBoxFilterQCOM, OpImageBlockMatchWindowSSDQCOM, OpImageBlockMatchWindowSADQCOM, OpImageBlockMatchGatherSSDQCOM,
													OpImageBlockMatchGatherSADQCOM, OpImageBlockMatchSSDQCOM, 或者 OpImageBlockMatchSADQCOM用来采样一个作为该命令的结果的VkImageView，则该VkSampler必须以VK_SAMPLER_CREATE_IMAGE_PROCESSING_BIT_QCOM创建
		53.如果任何除了OpImageWeightedSampleQCOM, OpImageBoxFilterQCOM, OpImageBlockMatchWindowSSDQCOM, OpImageBlockMatchWindowSADQCOM, OpImageBlockMatchGatherSSDQCOM, OpImageBlockMatchGatherSADQCOM, OpImageBlockMatchSSDQCOM, 或者 OpImageBlockMatchSADQCOM之外的指令使用VkSampler进行采样作为该命令的结果，则该sampler不能以VK_SAMPLER_CREATE_IMAGE_PROCESSING_BIT_QCOM 创建
		54.如果OpImageBlockMatchWindow*QCOM or OpImageBlockMatchGather*QCOM指令用来读取VkImageView作为该命令的结果，则（1）VkImageView的format features必须包含VK_FORMAT_FEATURE_2_BLOCK_MATCHING_BIT_QCOM
																													  （2）VkImageView的format必须只含有一个component
		55.如果OpImageBlockMatchWindow*QCOM or OpImageBlockMatchGather*QCOM指令用来读取一个引用的image作为该命令的结果，则指定的 reference coordinates不能在integer texel coordinate validation 时候失败
		56.任何该命令执行的shader invocation必须已经终止
		57.如果有一个类型为VK_DESCRIPTOR_TYPE_SAMPLE_WEIGHT_IMAGE_QCOM, VK_DESCRIPTOR_TYPE_BLOCK_MATCH_IMAGE_QCOM, VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE, VK_DESCRIPTOR_TYPE_STORAGE_IMAGE, 或者 VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT中任意一个的descriptor作为该命令的结果进行访问，则该descriptor所指的image subresource的layout必须和该descriptor被写入时的layout相同。
		58.任何该调用引用的shader group handle 必须已经在当前绑定的ray tracing pipeline中查询过。
		59.如果绑定的tracing pipeline 以VK_DYNAMIC_STATE_RAY_TRACING_PIPELINE_STACK_SIZE_KHR 动态状态创建，则该命令必须在当前命令缓冲区之前调用 vkCmdSetRayTracingPipelineStackSizeKHR。
		60.该命令不能造成一个在shader invocation上执行的pipeline trace ray instruction的递归深度超过了创建该pipeline的maxPipelineRayRecursionDepth。
		61.commandBuffer 必须不能是protected command buffer。
		62.pRayGenShaderBindingTable的size 必须等于其stride
		63.如果pRayGenShaderBindingTable->deviceAddress 所对的buffer 是non-sparse的则其必须绑定到完整的连续的单独的VkDeviceMemory对象上。
		64.pRayGenShaderBindingTable->deviceAddress 所对的buffer 必须以VK_BUFFER_USAGE_SHADER_BINDING_TABLE_BIT_KHR 创建
		65.pRayGenShaderBindingTable->deviceAddress 必须是VkPhysicalDeviceRayTracingPropertiesNV::shaderGroupBaseAlignment的倍数
		66.如果pMissShaderBindingTable->deviceAddress 所对的buffer 是non-sparse的则其必须绑定到完整的连续的单独的VkDeviceMemory对象上。
		67.pMissShaderBindingTable->deviceAddress 所对的buffer 必须以VK_BUFFER_USAGE_SHADER_BINDING_TABLE_BIT_KHR 创建
		68.pMissShaderBindingTable->deviceAddress 必须是VkPhysicalDeviceRayTracingPropertiesNV::shaderGroupBaseAlignment的倍数
		69.pMissShaderBindingTable->stride 必须是VkPhysicalDeviceRayTracingPipelinePropertiesKHR::shaderGroupHandleAlignment的倍数，且小于等于VkPhysicalDeviceRayTracingPipelinePropertiesKHR::maxShaderGroupStride
		70.如果pHitShaderBindingTable->deviceAddress 所对的buffer 是non-sparse的则其必须绑定到完整的连续的单独的VkDeviceMemory对象上。
		71.pHitShaderBindingTable->deviceAddress 所对的buffer 必须以VK_BUFFER_USAGE_SHADER_BINDING_TABLE_BIT_KHR 创建
		72.pHitShaderBindingTable->deviceAddress 必须是VkPhysicalDeviceRayTracingPropertiesNV::shaderGroupBaseAlignment的倍数
		73.pHitShaderBindingTable->stride 必须是VkPhysicalDeviceRayTracingPipelinePropertiesKHR::shaderGroupHandleAlignment的倍数，且小于等于VkPhysicalDeviceRayTracingPipelinePropertiesKHR::maxShaderGroupStride
		74.如果pCallableShaderBindingTable->deviceAddress 所对的buffer 是non-sparse的则其必须绑定到完整的连续的单独的VkDeviceMemory对象上。
		75.pCallableShaderBindingTable->deviceAddress 所对的buffer 必须以VK_BUFFER_USAGE_SHADER_BINDING_TABLE_BIT_KHR 创建
		76.pCallableShaderBindingTable->deviceAddress 必须是VkPhysicalDeviceRayTracingPropertiesNV::shaderGroupBaseAlignment的倍数
		77.pCallableShaderBindingTable->stride 必须是VkPhysicalDeviceRayTracingPipelinePropertiesKHR::shaderGroupHandleAlignment的倍数，且小于等于VkPhysicalDeviceRayTracingPipelinePropertiesKHR::maxShaderGroupStride
		78.如果当前绑定的ray tracing pipeline 以包含VK_PIPELINE_CREATE_RAY_TRACING_NO_NULL_CLOSEST_HIT_SHADERS_BIT_KHR 或者VK_PIPELINE_CREATE_RAY_TRACING_NO_NULL_INTERSECTION_SHADERS_BIT_KHR 创建，则pHitShaderBindingTable->deviceAddress 不能为0
		79.如果当前绑定的ray tracing pipeline 以包含VK_PIPELINE_CREATE_RAY_TRACING_NO_NULL_MISS_SHADERS_BIT_KHR 创建，则pMissShaderBindingTable->deviceAddress 指定的shader group handle 不能为0
		80.如果当前绑定的ray tracing pipeline 以包含VK_PIPELINE_CREATE_RAY_TRACING_NO_NULL_ANY_HIT_SHADERS_BIT_KHR 或者VK_PIPELINE_CREATE_RAY_TRACING_NO_NULL_CLOSEST_HIT_SHADERS_BIT_KHR ，VK_PIPELINE_CREATE_RAY_TRACING_NO_NULL_CLOSEST_HIT_SHADERS_BIT_KHR 或者VK_PIPELINE_CREATE_RAY_TRACING_NO_NULL_INTERSECTION_SHADERS_BIT_KHR 创建， 则用于执行一个any-hit shader作为该命令结果进行访问的 pHitShaderBindingTable->deviceAddress 指定的table中的实体 不能设置为0
		81.任何被该命令在一个geometryType为VK_GEOMETRY_TYPE_TRIANGLES_KHR的geometry中进行访问的 pHitShaderBindingTable->deviceAddress 指定的table中的任何 非0 hit shader group 实体必须以VK_RAY_TRACING_SHADER_GROUP_TYPE_TRIANGLES_HIT_GROUP_KHR 创建
		82.任何被该命令在一个geometryType为VK_GEOMETRY_TYPE_AABBS_KHR的geometry中进行访问的 pHitShaderBindingTable->deviceAddress 指定的table中的任何 非0 hit shader group 实体必须以VK_RAY_TRACING_SHADER_GROUP_TYPE_PROCEDURAL_HIT_GROUP_KHR 创建
		83.width，height以及depth必须对应小于等于VkPhysicalDeviceLimits::maxComputeWorkGroupCount[0] × VkPhysicalDeviceLimits::maxComputeWorkGroupSize[0], VkPhysicalDeviceLimits::maxComputeWorkGroupCount[1]  × VkPhysicalDeviceLimits::maxComputeWorkGroupSize[1], VkPhysicalDeviceLimits::maxComputeWorkGroupCount[2] × VkPhysicalDeviceLimits::maxComputeWorkGroupSize[2]。
		84.width × height × depth 必须小于等于 VkPhysicalDeviceRayTracingPipelinePropertiesKHR::maxRayDispatchInvocationCount	

		*/


		//当在ray tracing pipeline上开启使用 invocation mask image（通过image的值控制shader invocation）时，指定 invocation mask image
		vkCmdBindInvocationMaskHUAWEI(commandBuffer, VkImageView{/*假设这是一个有效的VkImageView*/ }/*imageView，为 invocation mask image的image view，如果设置为VK_NULL_HANDLE，则相当于指定一个值以1填充的image*/, VK_IMAGE_LAYOUT_GENERAL/* imageLayout,指明该image作为invocation mask image访问时subresource的layout*/);
		/*
		vkCmdBindInvocationMaskHUAWEI有效用法:
		1.invocationMask 特性必须开启
		2.如果imageView 不为VK_NULL_HANDLE，则（1）其必须是一个有效的类型为VK_IMAGE_VIEW_TYPE_2D的VkImageView
											  （2）其format必须为VK_FORMAT_R8_UINT
											  （3）其必须以VK_IMAGE_USAGE_INVOCATION_MASK_BIT_HUAWEI 创建
											  （4）imageLayout必须为VK_IMAGE_LAYOUT_GENERAL
		3.mask image的分辨率必须匹配vkCmdTraceRaysKHR的width和height
		4.invocation mask image中的每个元素值必须为0或者1，1代表该invocation 激活。
		5.vkCmdTraceRaysKHR的depth 必须为1
		*/


		VkTraceRaysIndirectCommandKHR traceRaysIndirectCommandKHR{};
		traceRaysIndirectCommandKHR.width = 1;//为ray trace query dimensions的width
		traceRaysIndirectCommandKHR.height = 1;//为ray trace query dimensions的height
		traceRaysIndirectCommandKHR.depth = 1;//为ray trace query dimensions的depth
		/*
		VkTraceRaysIndirectCommandKHR有效用法:
		1.width，height以及depth必须对应小于等于VkPhysicalDeviceLimits::maxComputeWorkGroupCount[0] × VkPhysicalDeviceLimits::maxComputeWorkGroupSize[0], VkPhysicalDeviceLimits::maxComputeWorkGroupCount[1]  × VkPhysicalDeviceLimits::maxComputeWorkGroupSize[1], VkPhysicalDeviceLimits::maxComputeWorkGroupCount[2] × VkPhysicalDeviceLimits::maxComputeWorkGroupSize[2]。
		2.width × height × depth 必须小于等于 VkPhysicalDeviceRayTracingPipelinePropertiesKHR::maxRayDispatchInvocationCount

		*/

		VkDeviceAddress dimensionsXYZ{/*假设这是一个有效的VkDeviceAddress*/ };//包含VkTraceRaysIndirectCommandKHR数据，指明ray trace query dimensions的width，height以及depth

		//dispatch ray tracing,一些参数从device的内存地址中获取,   执行该命令，则一个包含 width × height × depth 条ray的ray 产生组会被组装
		vkCmdTraceRaysIndirectKHR(commandBuffer,
			&raygenShaderBindingTable,
			&missShaderBindingTable,
			&hitShaderBindingTable,
			&callableShaderBindingTable,
			dimensionsXYZ/*indirectDeviceAddress,为指向VkTraceRaysIndirectCommandKHR 的地址.*/);
		/*
		vkCmdTraceRaysKHR有效用法:
		1.如果一个VkSampler以其magFilter或者minFilter等于VK_FILTER_LINEAR创建，则（1）如果reductionMode为VK_SAMPLER_REDUCTION_MODE_WEIGHTED_AVERAGE，如果用于采样一个VkImageView作为该命令的结果的compareEnable为VK_FALSE，则该image view的format features必须包含VK_FORMAT_FEATURE_SAMPLED_IMAGE_FILTER_LINEAR_BIT
																				 （2）如果reductionMode为VK_SAMPLER_REDUCTION_MODE_MIN 或者VK_SAMPLER_REDUCTION_MODE_MAX之一 用于采样一个VkImageView作为该命令的结果，则该image view的format features必须包含VK_FORMAT_FEATURE_SAMPLED_IMAGE_FILTER_MINMAX_BIT
		2.如果一个VkSampler以其mipmapMode 等于VK_SAMPLER_MIPMAP_MODE_LINEAR创建，则（1）如果reductionMode为VK_SAMPLER_REDUCTION_MODE_WEIGHTED_AVERAGE，如果用于采样一个VkImageView作为该命令的结果的compareEnable为VK_FALSE，则该image view的format features必须包含VK_FORMAT_FEATURE_SAMPLED_IMAGE_FILTER_LINEAR_BIT
																				 （2）如果reductionMode为VK_SAMPLER_REDUCTION_MODE_MIN 或者VK_SAMPLER_REDUCTION_MODE_MAX之一 用于采样一个VkImageView作为该命令的结果，则该image view的format features必须包含VK_FORMAT_FEATURE_SAMPLED_IMAGE_FILTER_MINMAX_BIT
		3.如果一个VkSampler以其unnormalizedCoordinates等于VK_TRUE用于采样一个VkImageView作为该命令的结果创建，则（1）该image view的levelCount以及layerCount必须为1
																												（2）该image view的viewType必须为VK_IMAGE_VIEW_TYPE_1D 或者 VK_IMAGE_VIEW_TYPE_2D
		4.如果一个VkImageView的采样带depth comparison操作，则image view的format features必须包含VK_FORMAT_FEATURE_2_SAMPLED_IMAGE_DEPTH_COMPARISON_BIT
		5.如果一个VkImageView使用atomic operations作为该命令的结果进行访问，则image view的format features必须包含VK_FORMAT_FEATURE_STORAGE_IMAGE_ATOMIC_BIT
		6.如果一个VK_DESCRIPTOR_TYPE_STORAGE_TEXEL_BUFFER类型的 descriptor使用atomic operations作为该命令的结果进行访问，则storage texel buffer的format features必须包含VK_FORMAT_FEATURE_STORAGE_TEXEL_BUFFER_ATOMIC_BIT
		7.如果一个以VK_FILTER_CUBIC_EXT进行采样的VkImageView作为该命令的结果，则image view的format features必须包含VK_FORMAT_FEATURE_SAMPLED_IMAGE_FILTER_CUBIC_BIT_EXT
		8.如果VK_EXT_filter_cubic拓展没有开启，且有任何一个以VK_FILTER_CUBIC_EXT进行采样的VkImageView作为该命令的结果，则其VkImageViewType不能为VK_IMAGE_VIEW_TYPE_3D, VK_IMAGE_VIEW_TYPE_CUBE, 或者 VK_IMAGE_VIEW_TYPE_CUBE_ARRAY
		9.任何一个以VK_FILTER_CUBIC_EXT进行采样的作为该命令的结果的VkImageView，其VkImageViewType和format 必须支持cubic filtering，参见vkGetPhysicalDeviceImageFormatProperties2返回的VkFilterCubicImageViewImageFormatPropertiesEXT::filterCubic
		10.任何一个以VK_FILTER_CUBIC_EXT进行采样且reduction mode为VK_SAMPLER_REDUCTION_MODE_MIN 或者 VK_SAMPLER_REDUCTION_MODE_MAX之一的作为该命令的结果的VkImageView，其VkImageViewType和format 必须支持带minmax filtering的cubic filtering，参见vkGetPhysicalDeviceImageFormatProperties2返回的VkFilterCubicImageViewImageFormatPropertiesEXT::filterCubicMinmax
		11.如果cubicRangeClamp特性没有开启，则有任何一个以VK_FILTER_CUBIC_EXT进行采样VkImageView的作为该命令的结果，VkSamplerReductionModeCreateInfo::reductionMode不能为VK_SAMPLER_REDUCTION_MODE_WEIGHTED_AVERAGE_RANGECLAMP_QCOM
		12.任何一个以VkSamplerReductionModeCreateInfo::reductionMode为VK_SAMPLER_REDUCTION_MODE_WEIGHTED_AVERAGE_RANGECLAMP_QCOM进行采样的作为该命令的结果的VkImageView必须以VK_FILTER_CUBIC_EXT进行采样
		13.如果selectableCubicWeights特性没有开启，则有任何一个以VK_FILTER_CUBIC_EXT进行采样VkImageView的作为该命令的结果，VkSamplerCubicWeightsCreateInfoQCOM::cubicWeights必须为VK_CUBIC_FILTER_WEIGHTS_CATMULL_ROM_QCOM
		14.任何一个以VkImageCreateInfo::flags含VK_IMAGE_CREATE_CORNER_SAMPLED_BIT_NV创建的采样作为该命令结果的VkImage必须以VkSamplerAddressMode为VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE 进行采样
		15.对于任何作为storage image写入的VkImageView，且其OpTypeImage的format未知，则该image view的 format features必须包含VK_FORMAT_FEATURE_2_STORAGE_WRITE_WITHOUT_FORMAT_BIT
		16.对于任何作为storage image读取的VkImageView，且其OpTypeImage的format未知，则该image view的 format features必须包含VK_FORMAT_FEATURE_2_STORAGE_READ_WITHOUT_FORMAT_BIT
		17.对于任何作为storage storage texel buffer写入的VkBufferView，且其OpTypeImage的format未知，则该buffer view的 buffer features必须包含VK_FORMAT_FEATURE_2_STORAGE_WRITE_WITHOUT_FORMAT_BIT
		18.对于任何作为storage storage texel buffer读取的VkBufferView，且其OpTypeImage的format未知，则该buffer view的 buffer features必须包含VK_FORMAT_FEATURE_2_STORAGE_READ_WITHOUT_FORMAT_BIT
		19.对于每个在绑定的shader中静态使用的set n，一个descriptor set必须被绑定到相同pipeline bind point的set n处，该set n必须和创建当前VkPipeline的VkPipelineLayout或者和创建当前VkShaderEXT的VkDescriptorSetLayout 数组的set n处的布局兼容，参见Pipeline Layout Compatibility p1280
		20.对于每个在绑定的shader中静态使用的push constant，一个push constant值必须被绑定到相同pipeline bind point的对应处，该push constant必须和创建当前VkPipeline的VkPipelineLayout或者和创建当前VkShaderEXT的VkDescriptorSetLayout 数组中的对应处的布局兼容，参见Pipeline Layout Compatibility p1280
		21.如果maintenance4特性没有开启，则对于每个在绑定的shader中静态使用的push constant，一个push constant值必须被设置到相同pipeline bind point的对应处，该push constant必须和创建当前VkPipeline的VkPipelineLayout或者和创建当前VkShaderEXT的VkDescriptorSetLayout 数组中的对应处的布局兼容，参见Pipeline Layout Compatibility p1280
		22.每一个通过vkCmdBindDescriptorSets绑定的descriptor set的descriptors,如果是被不以VK_PIPELINE_CREATE_DESCRIPTOR_BUFFER_BIT_EXT创建的，且已经绑定到该命令使用的pipeline bind point的VkPipeline静态使用的，则这些descriptors必须是有效的，参见 descriptor validity p1328
		23.如果通过vkCmdBindDescriptorSets指定绑定到pipeline bind point的VkPipeline要使用的descriptors，则绑定的VkPipeline不能以VK_PIPELINE_CREATE_DESCRIPTOR_BUFFER_BIT_EXT创建
		24.在vkCmdSetDescriptorBufferOffsetsEXT中指定绑定的descriptor buffers的descriptors，则（1）如果绑定到pipeline bind point的该命令会使用的VkPipeline以VK_PIPELINE_CREATE_DESCRIPTOR_BUFFER_BIT_EXT创建，且这些descriptors是动态使用的，则这些descriptors必须是有效的
																							  （2）如果绑定到pipeline bind point的对应stage的该命令会使用的VkShaderEXT，且这些descriptors是动态使用的，则这些descriptors必须是有效的
		25.在vkCmdSetDescriptorBufferOffsetsEXT中指定的descriptors在绑定到pipeline bind point的VkPipeline中使用，则VkPipeline必须以VK_PIPELINE_CREATE_DESCRIPTOR_BUFFER_BIT_EXT创建
		26.如果一个descriptor在以VK_PIPELINE_CREATE_DESCRIPTOR_BUFFER_BIT_EXT创建的VkPipeline中动态使用，则descriptor memory必须是驻留内存
		27.如果一个descriptor在以其VkDescriptorSetLayout以VK_DESCRIPTOR_SET_LAYOUT_CREATE_DESCRIPTOR_BUFFER_BIT_EXT创建的VkShaderEXT中动态使用，则descriptor memory必须是驻留内存
		28.如果shaderObject 特性没有开启，一个有效的pipeline必须绑定到这个命令使用的绑定到pipeline bind point上
		29.如果一个pipeline绑定到该命令使用的pipeline bind point上，则不能有任何动态state 设置命令设置任何该VkPipeline 中没有指定的动态 state
		30.如果一个VkPipeline绑定到该命令使用的pipeline bind point上 或者任何一个会访问一个使用unnormalized coordinates的VkSampler的 VkShaderEXT绑定到该命令使用的pipeline bind point上的pipeline的对应stage，则
																					（1）在任何shader stage中，VkSampler不能用来采样任何类型为VK_IMAGE_VIEW_TYPE_3D, VK_IMAGE_VIEW_TYPE_CUBE, VK_IMAGE_VIEW_TYPE_1D_ARRAY, VK_IMAGE_VIEW_TYPE_2D_ARRAY 或者 VK_IMAGE_VIEW_TYPE_CUBE_ARRAY的VkImageView
																					（2）在任何shader stage中，该VkSampler不能和任何带有名字中带有ImplicitLod，Dref 或者 Proj 的SPIR-V OpImageSample* 或者 OpImageSparseSample*指令一起使用
																					（3）在任何shader stage中，该VkSampler不能和任何包含 LOD bias或者offset 值 的SPIR-V OpImageSample* or OpImageSparseSample*指令一起使用
		31.如果shaderObject开启，一个有效的pipeline必须绑定到该命令使用的pipeline bind point上或者一个有效的shader objects以及VK_NULL_HANDLE的组合必须绑定到该命令使用的pipeline bind point每一个支持的shader stage上
		32.如何绑定到该命令使用的pipeline bind point上的VkPipeline的任何stage会访问一个uniform buffer，且该stage对uniformBuffers不以启用VK_PIPELINE_ROBUSTNESS_BUFFER_BEHAVIOR_ROBUST_BUFFER_ACCESS_EXT或者VK_PIPELINE_ROBUSTNESS_BUFFER_BEHAVIOR_ROBUST_BUFFER_ACCESS_2_EXT 创建，且robustBufferAccess特性未开启，则该stage就不能访问绑定到相同pipeline bind point的descriptor set指定的buffer范围外的值
		33.如果robustBufferAccess特性未开启，且任何会访问uniform buffer的绑定到该命令使用的pipeline bind point上对应shader stage的VkShaderEXT，则其不能访问绑定到相同pipeline bind point的descriptor set指定的buffer范围外的值
		34.如何绑定到该命令使用的pipeline bind point上的VkPipeline的任何stage会访问一个storage buffer，且该stage对storageBuffers不以启用VK_PIPELINE_ROBUSTNESS_BUFFER_BEHAVIOR_ROBUST_BUFFER_ACCESS_EXT或者VK_PIPELINE_ROBUSTNESS_BUFFER_BEHAVIOR_ROBUST_BUFFER_ACCESS_2_EXT 创建，且robustBufferAccess特性未开启，则该stage就不能访问绑定到相同pipeline bind point的descriptor set指定的buffer范围外的值
		35.如果robustBufferAccess特性未开启，且任何会访问storage buffer的绑定到该命令使用的pipeline bind point上对应shader stage的VkShaderEXT，则其不能访问绑定到相同pipeline bind point的descriptor set指定的buffer范围外的值
		36.如果commandBuffer 是一个unprotected command buffer，且protectedNoFault 未支持，则任何绑定的shaders访问的资源不能是一个protected resource
		37.如果一个绑定的shader访问一个VkSampler 或者 VkImageView ，且启用了sampler Y′C BCR conversion，则只能使用OpImageSample* 或者 OpImageSparseSample*指令，不能使用ConstOffset 以及 Offset操作符
		38.如果一个VkImageView作为该命令的结果进行访问，则（1）image view 的viewType 必须匹配Instruction/Sampler/Image View Validation p1481中描述的OpTypeImage的Dim操作符
														  （2）image view 的foamrt的numeric type 必须匹配OpTypeImage的Sampled Type操作符
		39.如果一个VkImageView以一个不是VK_FORMAT_A8_UNORM_KHR的format创建且通过OpImageWrite作为该命令的结果进行访问，则该命令的Texel 操作符的Type必须至少包含和 image view的 format含有的components的个数相同的components个数
		40.如果一个VkImageView以VK_FORMAT_A8_UNORM_KHR的format创建且通过OpImageWrite作为该命令的结果进行访问，则该命令的Texel 操作符的Type必须包含4个components
		41.如果一个VkBufferView通过OpImageWrite作为该命令的结果进行访问，则该命令的Texel 操作符的Type必须至少包含和 buffer view的 format含有的components的个数相同的components个数
		42.如果一个带64-bit component的VkFormat的VkImageView作为该命令的结果进行访问，则该命令的OpTypeImage操作符的SampledType的宽度必须为64
		43.如果一个带少于64-bit component的VkFormat的VkImageView作为该命令的结果进行访问，则该命令的OpTypeImage操作符的SampledType的宽度必须为32
		44.如果一个带64-bit component的VkFormat的VkBufferView作为该命令的结果进行访问，则该命令的OpTypeImage操作符的SampledType的宽度必须为64位
		45.如果一个带少于64-bit component的VkFormat的VkBufferView作为该命令的结果进行访问，则该命令的OpTypeImage操作符的SampledType的宽度必须为32
		46.如果sparseImageInt64Atomics 特性未开启，则以VK_IMAGE_CREATE_SPARSE_RESIDENCY_BIT创建的VkImage对象不能被SampledType宽度为64位的OpTypeImage的atomic instructions访问
		47.如果sparseImageInt64Atomics 特性未开启，则以VK_BUFFER_CREATE_SPARSE_RESIDENCY_BIT创建的VkBuffer对象不能被SampledType宽度为64位的OpTypeImage的atomic instructions访问
		48.如果OpImageWeightedSampleQCOM用来采样一个作为该命令的结果的VkImageView，则该image view的format features必须包含VK_FORMAT_FEATURE_2_WEIGHT_SAMPLED_IMAGE_BIT_QCOM
		49.如果OpImageWeightedSampleQCOM用来采样一个作为该命令的结果的sample weight image的VkImageView，则该image view的format features必须包含VK_FORMAT_FEATURE_2_WEIGHT_IMAGE_BIT_QCOM
		50.如果OpImageBoxFilterQCOM用来采样一个作为该命令的结果的VkImageView，则该image view的format features必须包含VK_FORMAT_FEATURE_2_BOX_FILTER_SAMPLED_BIT_QCOM
		51.如果OpImageBlockMatchSSDQCOM，或者 OpImageBlockMatchSADQCOM用来读取一个作为该命令的结果的VkImageView，则（1）该image view的format features必须包含VK_FORMAT_FEATURE_2_BLOCK_MATCHING_BIT_QCOM
																												   （2）如果是读取的reference image，指定的reference coordinates不能在integer texel coordinate validation 时候失败
		52.如果OpImageWeightedSampleQCOM, OpImageBoxFilterQCOM, OpImageBlockMatchWindowSSDQCOM, OpImageBlockMatchWindowSADQCOM, OpImageBlockMatchGatherSSDQCOM,
													OpImageBlockMatchGatherSADQCOM, OpImageBlockMatchSSDQCOM, 或者 OpImageBlockMatchSADQCOM用来采样一个作为该命令的结果的VkImageView，则该VkSampler必须以VK_SAMPLER_CREATE_IMAGE_PROCESSING_BIT_QCOM创建
		53.如果任何除了OpImageWeightedSampleQCOM, OpImageBoxFilterQCOM, OpImageBlockMatchWindowSSDQCOM, OpImageBlockMatchWindowSADQCOM, OpImageBlockMatchGatherSSDQCOM, OpImageBlockMatchGatherSADQCOM, OpImageBlockMatchSSDQCOM, 或者 OpImageBlockMatchSADQCOM之外的指令使用VkSampler进行采样作为该命令的结果，则该sampler不能以VK_SAMPLER_CREATE_IMAGE_PROCESSING_BIT_QCOM 创建
		54.如果OpImageBlockMatchWindow*QCOM or OpImageBlockMatchGather*QCOM指令用来读取VkImageView作为该命令的结果，则（1）VkImageView的format features必须包含VK_FORMAT_FEATURE_2_BLOCK_MATCHING_BIT_QCOM
																													  （2）VkImageView的format必须只含有一个component
		55.如果OpImageBlockMatchWindow*QCOM or OpImageBlockMatchGather*QCOM指令用来读取一个引用的image作为该命令的结果，则指定的 reference coordinates不能在integer texel coordinate validation 时候失败
		56.任何该命令执行的shader invocation必须已经终止
		57.如果有一个类型为VK_DESCRIPTOR_TYPE_SAMPLE_WEIGHT_IMAGE_QCOM, VK_DESCRIPTOR_TYPE_BLOCK_MATCH_IMAGE_QCOM, VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE, VK_DESCRIPTOR_TYPE_STORAGE_IMAGE, 或者 VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT中任意一个的descriptor作为该命令的结果进行访问，则该descriptor所指的image subresource的layout必须和该descriptor被写入时的layout相同。
		58.任何该调用引用的shader group handle 必须已经在当前绑定的ray tracing pipeline中查询过。
		59.如果绑定的tracing pipeline 以VK_DYNAMIC_STATE_RAY_TRACING_PIPELINE_STACK_SIZE_KHR 动态状态创建，则该命令必须在当前命令缓冲区之前调用 vkCmdSetRayTracingPipelineStackSizeKHR。
		60.该命令不能造成一个在shader invocation上执行的pipeline trace ray instruction的递归深度超过了创建该pipeline的maxPipelineRayRecursionDepth。
		61.commandBuffer 必须不能是protected command buffer。
		62.pRayGenShaderBindingTable的size 必须等于其stride
		63.如果pRayGenShaderBindingTable->deviceAddress 所对的buffer 是non-sparse的则其必须绑定到完整的连续的单独的VkDeviceMemory对象上。
		64.pRayGenShaderBindingTable->deviceAddress 所对的buffer 必须以VK_BUFFER_USAGE_SHADER_BINDING_TABLE_BIT_KHR 创建
		65.pRayGenShaderBindingTable->deviceAddress 必须是VkPhysicalDeviceRayTracingPropertiesNV::shaderGroupBaseAlignment的倍数
		66.如果pMissShaderBindingTable->deviceAddress 所对的buffer 是non-sparse的则其必须绑定到完整的连续的单独的VkDeviceMemory对象上。
		67.pMissShaderBindingTable->deviceAddress 所对的buffer 必须以VK_BUFFER_USAGE_SHADER_BINDING_TABLE_BIT_KHR 创建
		68.pMissShaderBindingTable->deviceAddress 必须是VkPhysicalDeviceRayTracingPropertiesNV::shaderGroupBaseAlignment的倍数
		69.pMissShaderBindingTable->stride 必须是VkPhysicalDeviceRayTracingPipelinePropertiesKHR::shaderGroupHandleAlignment的倍数，且小于等于VkPhysicalDeviceRayTracingPipelinePropertiesKHR::maxShaderGroupStride
		70.如果pHitShaderBindingTable->deviceAddress 所对的buffer 是non-sparse的则其必须绑定到完整的连续的单独的VkDeviceMemory对象上。
		71.pHitShaderBindingTable->deviceAddress 所对的buffer 必须以VK_BUFFER_USAGE_SHADER_BINDING_TABLE_BIT_KHR 创建
		72.pHitShaderBindingTable->deviceAddress 必须是VkPhysicalDeviceRayTracingPropertiesNV::shaderGroupBaseAlignment的倍数
		73.pHitShaderBindingTable->stride 必须是VkPhysicalDeviceRayTracingPipelinePropertiesKHR::shaderGroupHandleAlignment的倍数，且小于等于VkPhysicalDeviceRayTracingPipelinePropertiesKHR::maxShaderGroupStride
		74.如果pCallableShaderBindingTable->deviceAddress 所对的buffer 是non-sparse的则其必须绑定到完整的连续的单独的VkDeviceMemory对象上。
		75.pCallableShaderBindingTable->deviceAddress 所对的buffer 必须以VK_BUFFER_USAGE_SHADER_BINDING_TABLE_BIT_KHR 创建
		76.pCallableShaderBindingTable->deviceAddress 必须是VkPhysicalDeviceRayTracingPropertiesNV::shaderGroupBaseAlignment的倍数
		77.pCallableShaderBindingTable->stride 必须是VkPhysicalDeviceRayTracingPipelinePropertiesKHR::shaderGroupHandleAlignment的倍数，且小于等于VkPhysicalDeviceRayTracingPipelinePropertiesKHR::maxShaderGroupStride
		78.如果当前绑定的ray tracing pipeline 以包含VK_PIPELINE_CREATE_RAY_TRACING_NO_NULL_CLOSEST_HIT_SHADERS_BIT_KHR 或者VK_PIPELINE_CREATE_RAY_TRACING_NO_NULL_INTERSECTION_SHADERS_BIT_KHR 创建，则pHitShaderBindingTable->deviceAddress 不能为0
		79.如果当前绑定的ray tracing pipeline 以包含VK_PIPELINE_CREATE_RAY_TRACING_NO_NULL_MISS_SHADERS_BIT_KHR 创建，则pMissShaderBindingTable->deviceAddress 指定的shader group handle 不能为0
		80.如果当前绑定的ray tracing pipeline 以包含VK_PIPELINE_CREATE_RAY_TRACING_NO_NULL_ANY_HIT_SHADERS_BIT_KHR 或者VK_PIPELINE_CREATE_RAY_TRACING_NO_NULL_CLOSEST_HIT_SHADERS_BIT_KHR ，VK_PIPELINE_CREATE_RAY_TRACING_NO_NULL_CLOSEST_HIT_SHADERS_BIT_KHR 或者VK_PIPELINE_CREATE_RAY_TRACING_NO_NULL_INTERSECTION_SHADERS_BIT_KHR 创建， 则用于执行一个any-hit shader作为该命令结果进行访问的 pHitShaderBindingTable->deviceAddress 指定的table中的实体 不能设置为0
		81.任何被该命令在一个geometryType为VK_GEOMETRY_TYPE_TRIANGLES_KHR的geometry中进行访问的 pHitShaderBindingTable->deviceAddress 指定的table中的任何 非0 hit shader group 实体必须以VK_RAY_TRACING_SHADER_GROUP_TYPE_TRIANGLES_HIT_GROUP_KHR 创建
		82.任何被该命令在一个geometryType为VK_GEOMETRY_TYPE_AABBS_KHR的geometry中进行访问的 pHitShaderBindingTable->deviceAddress 指定的table中的任何 非0 hit shader group 实体必须以VK_RAY_TRACING_SHADER_GROUP_TYPE_PROCEDURAL_HIT_GROUP_KHR 创建
		83.如果indirectDeviceAddress所指的buffer时non-sparse的则其必须绑定到完整的连续的单独的VkDeviceMemory上，且该buffer必须以VK_BUFFER_USAGE_INDIRECT_BUFFER_BIT 创建
		84.indirectDeviceAddress 必须是4的倍数
		85.所有在indirectDeviceAddress 到indirectDeviceAddress + sizeof (VkTraceRaysIndirectCommandKHR) - 1 之间的地址必须在同一个buffer的设备地址范围中
		86.rayTracingPipelineTraceRaysIndirect 特性必须开启
		87.如果绑定的ray tracing pipeline 以VK_PIPELINE_CREATE_RAY_TRACING_ALLOW_MOTION_BIT_NV 创建，则VkPhysicalDeviceRayTracingMotionBlurFeaturesNV::rayTracingMotionBlurPipelineTraceRaysIndirect 特性必须开启


		*/

	
		VkTraceRaysIndirectCommand2KHR traceRaysIndirectCommand2KHR{};
		traceRaysIndirectCommand2KHR.raygenShaderRecordAddress = VkDeviceAddress{/*假设这是一个有效的VkDeviceAddress*/};//为ray generation shader binding table 的VkDeviceAddress 地址
		traceRaysIndirectCommand2KHR.raygenShaderRecordSize = 1;//为 raygenShaderRecordAddress 中ray generation shader binding table的字节数数量大小
		traceRaysIndirectCommand2KHR.missShaderBindingTableAddress = VkDeviceAddress{/*假设这是一个有效的VkDeviceAddress*/ };//为第一个miss shader binding table 的VkDeviceAddress 地址
		traceRaysIndirectCommand2KHR.missShaderBindingTableSize = 1;//为 missShaderBindingTableAddress 中所有miss shader binding table的字节数数量大小
		traceRaysIndirectCommand2KHR.missShaderBindingTableStride = 1;//为 missShaderBindingTableAddress 中miss shader binding table之间的字节大小步长
		traceRaysIndirectCommand2KHR.hitShaderBindingTableAddress = VkDeviceAddress{/*假设这是一个有效的VkDeviceAddress*/ };//为第一个hit shader binding table 的VkDeviceAddress 地址
		traceRaysIndirectCommand2KHR.hitShaderBindingTableSize = 1;//为 hitShaderBindingTableAddress 中所有hit shader binding table的字节数数量大小
		traceRaysIndirectCommand2KHR.hitShaderBindingTableStride = 1;//为 hitShaderBindingTableAddress 中hit shader binding table之间的字节大小步长
		traceRaysIndirectCommand2KHR.callableShaderBindingTableAddress = VkDeviceAddress{/*假设这是一个有效的VkDeviceAddress*/ };//为第一个callable shader binding table 的VkDeviceAddress 地址
		traceRaysIndirectCommand2KHR.callableShaderBindingTableSize = 1;//为 callableShaderBindingTableAddress 中所有callable shader binding table的字节数数量大小
		traceRaysIndirectCommand2KHR.callableShaderBindingTableStride = 1;//为 callableShaderBindingTableAddress 中callable shader binding table之间的字节大小步长
		traceRaysIndirectCommand2KHR.width = 1;//为ray trace query dimensions的width
		traceRaysIndirectCommand2KHR.height = 1;//为ray trace query dimensions的height
		traceRaysIndirectCommand2KHR.depth = 1;//为ray trace query dimensions的depth
		/*
		VkTraceRaysIndirectCommand2KHR有效用法:

		1.如果raygenShaderRecordAddress 所对的buffer 是non-sparse的则其必须绑定到完整的连续的单独的VkDeviceMemory对象上。
		2.raygenShaderRecordAddress 所对的buffer 必须以VK_BUFFER_USAGE_SHADER_BINDING_TABLE_BIT_KHR 创建
		3.raygenShaderRecordAddress 必须是VkPhysicalDeviceRayTracingPipelinePropertiesKHR::shaderGroupBaseAlignment的倍数
		4.如果missShaderBindingTableAddress 所对的buffer 是non-sparse的则其必须绑定到完整的连续的单独的VkDeviceMemory对象上。
		5.missShaderBindingTableAddress 所对的buffer 必须以VK_BUFFER_USAGE_SHADER_BINDING_TABLE_BIT_KHR 创建
		6.missShaderBindingTableAddress 必须是VkPhysicalDeviceRayTracingPipelinePropertiesKHR::shaderGroupBaseAlignment的倍数
		7.missShaderBindingTableStride 必须是VkPhysicalDeviceRayTracingPipelinePropertiesKHR::shaderGroupHandleAlignment的倍数，且小于等于VkPhysicalDeviceRayTracingPipelinePropertiesKHR::maxShaderGroupStride
		
		8.如果hitShaderBindingTableAddress 所对的buffer 是non-sparse的则其必须绑定到完整的连续的单独的VkDeviceMemory对象上。
		9.hitShaderBindingTableAddress 所对的buffer 必须以VK_BUFFER_USAGE_SHADER_BINDING_TABLE_BIT_KHR 创建
		10.hitShaderBindingTableAddress 必须是VkPhysicalDeviceRayTracingPipelinePropertiesKHR::shaderGroupBaseAlignment的倍数
		11.hitShaderBindingTableStride 必须是VkPhysicalDeviceRayTracingPipelinePropertiesKHR::shaderGroupHandleAlignment的倍数，且小于等于VkPhysicalDeviceRayTracingPipelinePropertiesKHR::maxShaderGroupStride
		12.如果callableShaderBindingTableAddress 所对的buffer 是non-sparse的则其必须绑定到完整的连续的单独的VkDeviceMemory对象上。
		13.callableShaderBindingTableAddress 所对的buffer 必须以VK_BUFFER_USAGE_SHADER_BINDING_TABLE_BIT_KHR 创建
		14.callableShaderBindingTableAddress 必须是VkPhysicalDeviceRayTracingPipelinePropertiesKHR::shaderGroupBaseAlignment的倍数
		15.callableShaderBindingTableStride 必须是VkPhysicalDeviceRayTracingPipelinePropertiesKHR::shaderGroupHandleAlignment的倍数，且小于等于VkPhysicalDeviceRayTracingPipelinePropertiesKHR::maxShaderGroupStride
		16.如果当前绑定的ray tracing pipeline 以包含VK_PIPELINE_CREATE_RAY_TRACING_NO_NULL_CLOSEST_HIT_SHADERS_BIT_KHR 或者VK_PIPELINE_CREATE_RAY_TRACING_NO_NULL_INTERSECTION_SHADERS_BIT_KHR 创建，则hitShaderBindingTableAddress 不能为0
		17.如果当前绑定的ray tracing pipeline 以包含VK_PIPELINE_CREATE_RAY_TRACING_NO_NULL_MISS_SHADERS_BIT_KHR 创建，则missShaderBindingTableAddress 指定的shader group handle 不能为0
		18.如果当前绑定的ray tracing pipeline 以包含VK_PIPELINE_CREATE_RAY_TRACING_NO_NULL_ANY_HIT_SHADERS_BIT_KHR 或者VK_PIPELINE_CREATE_RAY_TRACING_NO_NULL_CLOSEST_HIT_SHADERS_BIT_KHR ，VK_PIPELINE_CREATE_RAY_TRACING_NO_NULL_CLOSEST_HIT_SHADERS_BIT_KHR 或者VK_PIPELINE_CREATE_RAY_TRACING_NO_NULL_INTERSECTION_SHADERS_BIT_KHR 创建， 则用于执行一个any-hit shader作为该命令结果进行访问的 hitShaderBindingTableAddress 指定的table中的实体 不能设置为0
		19.任何被该命令在一个geometryType为VK_GEOMETRY_TYPE_TRIANGLES_KHR的geometry中进行访问的 hitShaderBindingTableAddress 指定的table中的任何 非0 hit shader group 实体必须以VK_RAY_TRACING_SHADER_GROUP_TYPE_TRIANGLES_HIT_GROUP_KHR 创建
		20.任何被该命令在一个geometryType为VK_GEOMETRY_TYPE_AABBS_KHR的geometry中进行访问的 hitShaderBindingTableAddress 指定的table中的任何 非0 hit shader group 实体必须以VK_RAY_TRACING_SHADER_GROUP_TYPE_PROCEDURAL_HIT_GROUP_KHR 创建
		21.width，height以及depth必须对应小于等于VkPhysicalDeviceLimits::maxComputeWorkGroupCount[0] × VkPhysicalDeviceLimits::maxComputeWorkGroupSize[0], VkPhysicalDeviceLimits::maxComputeWorkGroupCount[1]  × VkPhysicalDeviceLimits::maxComputeWorkGroupSize[1], VkPhysicalDeviceLimits::maxComputeWorkGroupCount[2] × VkPhysicalDeviceLimits::maxComputeWorkGroupSize[2]。
		22.width × height × depth 必须小于等于 VkPhysicalDeviceRayTracingPipelinePropertiesKHR::maxRayDispatchInvocationCount
		*/



		VkDeviceAddress traceRaysIndirectRarams{/*假设这是一个有效的VkDeviceAddress*/ };//包含VkTraceRaysIndirectCommand2KHR数据，指明dispatch ray tracing 的参数

		//dispatch ray tracing,一些参数从device的内存地址中获取,   执行该命令，则一个包含 width × height × depth 条ray的ray 产生组会被组装
		vkCmdTraceRaysIndirect2KHR(commandBuffer,
			traceRaysIndirectRarams/*indirectDeviceAddress,为指向VkTraceRaysIndirectCommand2KHR 的地址.*/);
		/*
		vkCmdTraceRaysIndirect2KHR有效用法:
		1.如果一个VkSampler以其magFilter或者minFilter等于VK_FILTER_LINEAR创建，则（1）如果reductionMode为VK_SAMPLER_REDUCTION_MODE_WEIGHTED_AVERAGE，如果用于采样一个VkImageView作为该命令的结果的compareEnable为VK_FALSE，则该image view的format features必须包含VK_FORMAT_FEATURE_SAMPLED_IMAGE_FILTER_LINEAR_BIT
																				 （2）如果reductionMode为VK_SAMPLER_REDUCTION_MODE_MIN 或者VK_SAMPLER_REDUCTION_MODE_MAX之一 用于采样一个VkImageView作为该命令的结果，则该image view的format features必须包含VK_FORMAT_FEATURE_SAMPLED_IMAGE_FILTER_MINMAX_BIT
		2.如果一个VkSampler以其mipmapMode 等于VK_SAMPLER_MIPMAP_MODE_LINEAR创建，则（1）如果reductionMode为VK_SAMPLER_REDUCTION_MODE_WEIGHTED_AVERAGE，如果用于采样一个VkImageView作为该命令的结果的compareEnable为VK_FALSE，则该image view的format features必须包含VK_FORMAT_FEATURE_SAMPLED_IMAGE_FILTER_LINEAR_BIT
																				 （2）如果reductionMode为VK_SAMPLER_REDUCTION_MODE_MIN 或者VK_SAMPLER_REDUCTION_MODE_MAX之一 用于采样一个VkImageView作为该命令的结果，则该image view的format features必须包含VK_FORMAT_FEATURE_SAMPLED_IMAGE_FILTER_MINMAX_BIT
		3.如果一个VkSampler以其unnormalizedCoordinates等于VK_TRUE用于采样一个VkImageView作为该命令的结果创建，则（1）该image view的levelCount以及layerCount必须为1
																												（2）该image view的viewType必须为VK_IMAGE_VIEW_TYPE_1D 或者 VK_IMAGE_VIEW_TYPE_2D
		4.如果一个VkImageView的采样带depth comparison操作，则image view的format features必须包含VK_FORMAT_FEATURE_2_SAMPLED_IMAGE_DEPTH_COMPARISON_BIT
		5.如果一个VkImageView使用atomic operations作为该命令的结果进行访问，则image view的format features必须包含VK_FORMAT_FEATURE_STORAGE_IMAGE_ATOMIC_BIT
		6.如果一个VK_DESCRIPTOR_TYPE_STORAGE_TEXEL_BUFFER类型的 descriptor使用atomic operations作为该命令的结果进行访问，则storage texel buffer的format features必须包含VK_FORMAT_FEATURE_STORAGE_TEXEL_BUFFER_ATOMIC_BIT
		7.如果一个以VK_FILTER_CUBIC_EXT进行采样的VkImageView作为该命令的结果，则image view的format features必须包含VK_FORMAT_FEATURE_SAMPLED_IMAGE_FILTER_CUBIC_BIT_EXT
		8.如果VK_EXT_filter_cubic拓展没有开启，且有任何一个以VK_FILTER_CUBIC_EXT进行采样的VkImageView作为该命令的结果，则其VkImageViewType不能为VK_IMAGE_VIEW_TYPE_3D, VK_IMAGE_VIEW_TYPE_CUBE, 或者 VK_IMAGE_VIEW_TYPE_CUBE_ARRAY
		9.任何一个以VK_FILTER_CUBIC_EXT进行采样的作为该命令的结果的VkImageView，其VkImageViewType和format 必须支持cubic filtering，参见vkGetPhysicalDeviceImageFormatProperties2返回的VkFilterCubicImageViewImageFormatPropertiesEXT::filterCubic
		10.任何一个以VK_FILTER_CUBIC_EXT进行采样且reduction mode为VK_SAMPLER_REDUCTION_MODE_MIN 或者 VK_SAMPLER_REDUCTION_MODE_MAX之一的作为该命令的结果的VkImageView，其VkImageViewType和format 必须支持带minmax filtering的cubic filtering，参见vkGetPhysicalDeviceImageFormatProperties2返回的VkFilterCubicImageViewImageFormatPropertiesEXT::filterCubicMinmax
		11.如果cubicRangeClamp特性没有开启，则有任何一个以VK_FILTER_CUBIC_EXT进行采样VkImageView的作为该命令的结果，VkSamplerReductionModeCreateInfo::reductionMode不能为VK_SAMPLER_REDUCTION_MODE_WEIGHTED_AVERAGE_RANGECLAMP_QCOM
		12.任何一个以VkSamplerReductionModeCreateInfo::reductionMode为VK_SAMPLER_REDUCTION_MODE_WEIGHTED_AVERAGE_RANGECLAMP_QCOM进行采样的作为该命令的结果的VkImageView必须以VK_FILTER_CUBIC_EXT进行采样
		13.如果selectableCubicWeights特性没有开启，则有任何一个以VK_FILTER_CUBIC_EXT进行采样VkImageView的作为该命令的结果，VkSamplerCubicWeightsCreateInfoQCOM::cubicWeights必须为VK_CUBIC_FILTER_WEIGHTS_CATMULL_ROM_QCOM
		14.任何一个以VkImageCreateInfo::flags含VK_IMAGE_CREATE_CORNER_SAMPLED_BIT_NV创建的采样作为该命令结果的VkImage必须以VkSamplerAddressMode为VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE 进行采样
		15.对于任何作为storage image写入的VkImageView，且其OpTypeImage的format未知，则该image view的 format features必须包含VK_FORMAT_FEATURE_2_STORAGE_WRITE_WITHOUT_FORMAT_BIT
		16.对于任何作为storage image读取的VkImageView，且其OpTypeImage的format未知，则该image view的 format features必须包含VK_FORMAT_FEATURE_2_STORAGE_READ_WITHOUT_FORMAT_BIT
		17.对于任何作为storage storage texel buffer写入的VkBufferView，且其OpTypeImage的format未知，则该buffer view的 buffer features必须包含VK_FORMAT_FEATURE_2_STORAGE_WRITE_WITHOUT_FORMAT_BIT
		18.对于任何作为storage storage texel buffer读取的VkBufferView，且其OpTypeImage的format未知，则该buffer view的 buffer features必须包含VK_FORMAT_FEATURE_2_STORAGE_READ_WITHOUT_FORMAT_BIT
		19.对于每个在绑定的shader中静态使用的set n，一个descriptor set必须被绑定到相同pipeline bind point的set n处，该set n必须和创建当前VkPipeline的VkPipelineLayout或者和创建当前VkShaderEXT的VkDescriptorSetLayout 数组的set n处的布局兼容，参见Pipeline Layout Compatibility p1280
		20.对于每个在绑定的shader中静态使用的push constant，一个push constant值必须被绑定到相同pipeline bind point的对应处，该push constant必须和创建当前VkPipeline的VkPipelineLayout或者和创建当前VkShaderEXT的VkDescriptorSetLayout 数组中的对应处的布局兼容，参见Pipeline Layout Compatibility p1280
		21.如果maintenance4特性没有开启，则对于每个在绑定的shader中静态使用的push constant，一个push constant值必须被设置到相同pipeline bind point的对应处，该push constant必须和创建当前VkPipeline的VkPipelineLayout或者和创建当前VkShaderEXT的VkDescriptorSetLayout 数组中的对应处的布局兼容，参见Pipeline Layout Compatibility p1280
		22.每一个通过vkCmdBindDescriptorSets绑定的descriptor set的descriptors,如果是被不以VK_PIPELINE_CREATE_DESCRIPTOR_BUFFER_BIT_EXT创建的，且已经绑定到该命令使用的pipeline bind point的VkPipeline静态使用的，则这些descriptors必须是有效的，参见 descriptor validity p1328
		23.如果通过vkCmdBindDescriptorSets指定绑定到pipeline bind point的VkPipeline要使用的descriptors，则绑定的VkPipeline不能以VK_PIPELINE_CREATE_DESCRIPTOR_BUFFER_BIT_EXT创建
		24.在vkCmdSetDescriptorBufferOffsetsEXT中指定绑定的descriptor buffers的descriptors，则（1）如果绑定到pipeline bind point的该命令会使用的VkPipeline以VK_PIPELINE_CREATE_DESCRIPTOR_BUFFER_BIT_EXT创建，且这些descriptors是动态使用的，则这些descriptors必须是有效的
																							  （2）如果绑定到pipeline bind point的对应stage的该命令会使用的VkShaderEXT，且这些descriptors是动态使用的，则这些descriptors必须是有效的
		25.在vkCmdSetDescriptorBufferOffsetsEXT中指定的descriptors在绑定到pipeline bind point的VkPipeline中使用，则VkPipeline必须以VK_PIPELINE_CREATE_DESCRIPTOR_BUFFER_BIT_EXT创建
		26.如果一个descriptor在以VK_PIPELINE_CREATE_DESCRIPTOR_BUFFER_BIT_EXT创建的VkPipeline中动态使用，则descriptor memory必须是驻留内存
		27.如果一个descriptor在以其VkDescriptorSetLayout以VK_DESCRIPTOR_SET_LAYOUT_CREATE_DESCRIPTOR_BUFFER_BIT_EXT创建的VkShaderEXT中动态使用，则descriptor memory必须是驻留内存
		28.如果shaderObject 特性没有开启，一个有效的pipeline必须绑定到这个命令使用的绑定到pipeline bind point上
		29.如果一个pipeline绑定到该命令使用的pipeline bind point上，则不能有任何动态state 设置命令设置任何该VkPipeline 中没有指定的动态 state
		30.如果一个VkPipeline绑定到该命令使用的pipeline bind point上 或者任何一个会访问一个使用unnormalized coordinates的VkSampler的 VkShaderEXT绑定到该命令使用的pipeline bind point上的pipeline的对应stage，则
																					（1）在任何shader stage中，VkSampler不能用来采样任何类型为VK_IMAGE_VIEW_TYPE_3D, VK_IMAGE_VIEW_TYPE_CUBE, VK_IMAGE_VIEW_TYPE_1D_ARRAY, VK_IMAGE_VIEW_TYPE_2D_ARRAY 或者 VK_IMAGE_VIEW_TYPE_CUBE_ARRAY的VkImageView
																					（2）在任何shader stage中，该VkSampler不能和任何带有名字中带有ImplicitLod，Dref 或者 Proj 的SPIR-V OpImageSample* 或者 OpImageSparseSample*指令一起使用
																					（3）在任何shader stage中，该VkSampler不能和任何包含 LOD bias或者offset 值 的SPIR-V OpImageSample* or OpImageSparseSample*指令一起使用
		31.如果shaderObject开启，一个有效的pipeline必须绑定到该命令使用的pipeline bind point上或者一个有效的shader objects以及VK_NULL_HANDLE的组合必须绑定到该命令使用的pipeline bind point每一个支持的shader stage上
		32.如何绑定到该命令使用的pipeline bind point上的VkPipeline的任何stage会访问一个uniform buffer，且该stage对uniformBuffers不以启用VK_PIPELINE_ROBUSTNESS_BUFFER_BEHAVIOR_ROBUST_BUFFER_ACCESS_EXT或者VK_PIPELINE_ROBUSTNESS_BUFFER_BEHAVIOR_ROBUST_BUFFER_ACCESS_2_EXT 创建，且robustBufferAccess特性未开启，则该stage就不能访问绑定到相同pipeline bind point的descriptor set指定的buffer范围外的值
		33.如果robustBufferAccess特性未开启，且任何会访问uniform buffer的绑定到该命令使用的pipeline bind point上对应shader stage的VkShaderEXT，则其不能访问绑定到相同pipeline bind point的descriptor set指定的buffer范围外的值
		34.如何绑定到该命令使用的pipeline bind point上的VkPipeline的任何stage会访问一个storage buffer，且该stage对storageBuffers不以启用VK_PIPELINE_ROBUSTNESS_BUFFER_BEHAVIOR_ROBUST_BUFFER_ACCESS_EXT或者VK_PIPELINE_ROBUSTNESS_BUFFER_BEHAVIOR_ROBUST_BUFFER_ACCESS_2_EXT 创建，且robustBufferAccess特性未开启，则该stage就不能访问绑定到相同pipeline bind point的descriptor set指定的buffer范围外的值
		35.如果robustBufferAccess特性未开启，且任何会访问storage buffer的绑定到该命令使用的pipeline bind point上对应shader stage的VkShaderEXT，则其不能访问绑定到相同pipeline bind point的descriptor set指定的buffer范围外的值
		36.如果commandBuffer 是一个unprotected command buffer，且protectedNoFault 未支持，则任何绑定的shaders访问的资源不能是一个protected resource
		37.如果一个绑定的shader访问一个VkSampler 或者 VkImageView ，且启用了sampler Y′C BCR conversion，则只能使用OpImageSample* 或者 OpImageSparseSample*指令，不能使用ConstOffset 以及 Offset操作符
		38.如果一个VkImageView作为该命令的结果进行访问，则（1）image view 的viewType 必须匹配Instruction/Sampler/Image View Validation p1481中描述的OpTypeImage的Dim操作符
														  （2）image view 的foamrt的numeric type 必须匹配OpTypeImage的Sampled Type操作符
		39.如果一个VkImageView以一个不是VK_FORMAT_A8_UNORM_KHR的format创建且通过OpImageWrite作为该命令的结果进行访问，则该命令的Texel 操作符的Type必须至少包含和 image view的 format含有的components的个数相同的components个数
		40.如果一个VkImageView以VK_FORMAT_A8_UNORM_KHR的format创建且通过OpImageWrite作为该命令的结果进行访问，则该命令的Texel 操作符的Type必须包含4个components
		41.如果一个VkBufferView通过OpImageWrite作为该命令的结果进行访问，则该命令的Texel 操作符的Type必须至少包含和 buffer view的 format含有的components的个数相同的components个数
		42.如果一个带64-bit component的VkFormat的VkImageView作为该命令的结果进行访问，则该命令的OpTypeImage操作符的SampledType的宽度必须为64
		43.如果一个带少于64-bit component的VkFormat的VkImageView作为该命令的结果进行访问，则该命令的OpTypeImage操作符的SampledType的宽度必须为32
		44.如果一个带64-bit component的VkFormat的VkBufferView作为该命令的结果进行访问，则该命令的OpTypeImage操作符的SampledType的宽度必须为64位
		45.如果一个带少于64-bit component的VkFormat的VkBufferView作为该命令的结果进行访问，则该命令的OpTypeImage操作符的SampledType的宽度必须为32
		46.如果sparseImageInt64Atomics 特性未开启，则以VK_IMAGE_CREATE_SPARSE_RESIDENCY_BIT创建的VkImage对象不能被SampledType宽度为64位的OpTypeImage的atomic instructions访问
		47.如果sparseImageInt64Atomics 特性未开启，则以VK_BUFFER_CREATE_SPARSE_RESIDENCY_BIT创建的VkBuffer对象不能被SampledType宽度为64位的OpTypeImage的atomic instructions访问
		48.如果OpImageWeightedSampleQCOM用来采样一个作为该命令的结果的VkImageView，则该image view的format features必须包含VK_FORMAT_FEATURE_2_WEIGHT_SAMPLED_IMAGE_BIT_QCOM
		49.如果OpImageWeightedSampleQCOM用来采样一个作为该命令的结果的sample weight image的VkImageView，则该image view的format features必须包含VK_FORMAT_FEATURE_2_WEIGHT_IMAGE_BIT_QCOM
		50.如果OpImageBoxFilterQCOM用来采样一个作为该命令的结果的VkImageView，则该image view的format features必须包含VK_FORMAT_FEATURE_2_BOX_FILTER_SAMPLED_BIT_QCOM
		51.如果OpImageBlockMatchSSDQCOM，或者 OpImageBlockMatchSADQCOM用来读取一个作为该命令的结果的VkImageView，则（1）该image view的format features必须包含VK_FORMAT_FEATURE_2_BLOCK_MATCHING_BIT_QCOM
																												   （2）如果是读取的reference image，指定的reference coordinates不能在integer texel coordinate validation 时候失败
		52.如果OpImageWeightedSampleQCOM, OpImageBoxFilterQCOM, OpImageBlockMatchWindowSSDQCOM, OpImageBlockMatchWindowSADQCOM, OpImageBlockMatchGatherSSDQCOM,
													OpImageBlockMatchGatherSADQCOM, OpImageBlockMatchSSDQCOM, 或者 OpImageBlockMatchSADQCOM用来采样一个作为该命令的结果的VkImageView，则该VkSampler必须以VK_SAMPLER_CREATE_IMAGE_PROCESSING_BIT_QCOM创建
		53.如果任何除了OpImageWeightedSampleQCOM, OpImageBoxFilterQCOM, OpImageBlockMatchWindowSSDQCOM, OpImageBlockMatchWindowSADQCOM, OpImageBlockMatchGatherSSDQCOM, OpImageBlockMatchGatherSADQCOM, OpImageBlockMatchSSDQCOM, 或者 OpImageBlockMatchSADQCOM之外的指令使用VkSampler进行采样作为该命令的结果，则该sampler不能以VK_SAMPLER_CREATE_IMAGE_PROCESSING_BIT_QCOM 创建
		54.如果OpImageBlockMatchWindow*QCOM or OpImageBlockMatchGather*QCOM指令用来读取VkImageView作为该命令的结果，则（1）VkImageView的format features必须包含VK_FORMAT_FEATURE_2_BLOCK_MATCHING_BIT_QCOM
																													  （2）VkImageView的format必须只含有一个component
		55.如果OpImageBlockMatchWindow*QCOM or OpImageBlockMatchGather*QCOM指令用来读取一个引用的image作为该命令的结果，则指定的 reference coordinates不能在integer texel coordinate validation 时候失败
		56.任何该命令执行的shader invocation必须已经终止
		57.如果有一个类型为VK_DESCRIPTOR_TYPE_SAMPLE_WEIGHT_IMAGE_QCOM, VK_DESCRIPTOR_TYPE_BLOCK_MATCH_IMAGE_QCOM, VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE, VK_DESCRIPTOR_TYPE_STORAGE_IMAGE, 或者 VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT中任意一个的descriptor作为该命令的结果进行访问，则该descriptor所指的image subresource的layout必须和该descriptor被写入时的layout相同。
		58.任何该调用引用的shader group handle 必须已经在当前绑定的ray tracing pipeline中查询过。
		59.如果绑定的tracing pipeline 以VK_DYNAMIC_STATE_RAY_TRACING_PIPELINE_STACK_SIZE_KHR 动态状态创建，则该命令必须在当前命令缓冲区之前调用 vkCmdSetRayTracingPipelineStackSizeKHR。
		60.该命令不能造成一个在shader invocation上执行的pipeline trace ray instruction的递归深度超过了创建该pipeline的maxPipelineRayRecursionDepth。
		61.commandBuffer 必须不能是protected command buffer。
		62.如果indirectDeviceAddress所指的buffer时non-sparse的则其必须绑定到完整的连续的单独的VkDeviceMemory上，且该buffer必须以VK_BUFFER_USAGE_INDIRECT_BUFFER_BIT 创建
		63.indirectDeviceAddress 必须是4的倍数
		64.所有在indirectDeviceAddress 到indirectDeviceAddress + sizeof (VkTraceRaysIndirectCommand2KHR) - 1 之间的地址必须在同一个buffer的设备地址范围中
		65.rayTracingPipelineTraceRaysIndirect2 特性必须开启
		66.如果绑定的ray tracing pipeline 以VK_PIPELINE_CREATE_RAY_TRACING_ALLOW_MOTION_BIT_NV 创建，则VkPhysicalDeviceRayTracingMotionBlurFeaturesNV::rayTracingMotionBlurPipelineTraceRaysIndirect 特性必须开启

		
		*/
	}


	//Shader Binding Table  参见p3391
	{
		/*
		shader binding table是用来建立ray tracing pipeline 和acceleration structures之间联系的资源。指明操作加速结构中geometry的shader，也包含该shader可访问的纹理，设备地址以及常量资源。shader binding tables以一个VkBuffer进行管理。

		shader binding table中的每个实体包含 shaderGroupHandleSize个字节，其值可通过 vkGetRayTracingShaderGroupHandlesKHR 查询指明shader，或者0全为0指明所有shader为VK_SHADER_UNUSED_KHR。余下由stride指定的数据可以在shader中通过 ShaderRecordBufferKHR 进行访问

		shader binding table通过 vkCmdTraceRaysNV, vkCmdTraceRaysKHR, 或者 vkCmdTraceRaysIndirectKHR传递给ray tracing pipeline，以VK_PIPELINE_STAGE_RAY_TRACING_SHADER_BIT_KHR pipeline stage 同步，以VK_ACCESS_SHADER_READ_BIT 进行访问
		*/
		
		//Indexing Rules  参见p3392
		{
			/*
			为了在ray tracing过程中正确执行shader以及访问资源，实现需要正确计算索引用于访问shader binding table
			
			
			对Ray Generation Shaders:
				因为每个ray tracing dispatch只会执行一个ray generation shader，所以传递给vkCmdTraceRaysKHR 或者vkCmdTraceRaysNV的raygen shader binding table不要计算索引。
			
			-----------------------------------------------------
			对Hit Shaders:
				对 vkCmdTraceRaysKHR 命令,正确计算pHitShaderBindingTable的一个索引为:
					pHitShaderBindingTable->deviceAddress + pHitShaderBindingTable->stride × ( instanceShaderBindingTableRecordOffset + geometryIndex × sbtRecordStride + sbtRecordOffset ),
								
				对 vkCmdTraceRaysNV 命令，正确计算hitShaderBindingTableBuffer的一个索引为:
					hitShaderBindingOffset + hitShaderBindingStride × ( instanceShaderBindingTableRecordOffset + geometryIndex × sbtRecordStride + sbtRecordOffset )

				其中其中instanceShaderBindingTableRecordOffset 为相交的instance的VkAccelerationStructureInstanceKHR::instanceShaderBindingTableRecordOffset,geometryIndex 指明为加速结构中相交的geometry的索引，sbtRecordOffset 以及 sbtRecordStride 是传递给traceNV() 或者 traceRayEXT() shader指令的参数（GLSL），在SPIR-V中为传递给 pipeline trace ray指令的SBTOffset 以及 SBTStride
			
			-----------------------------------------------------
			对Miss Shaders:
				对 vkCmdTraceRaysKHR 命令,正确计算pMissShaderBindingTable的一个索引为:
					pMissShaderBindingTable->deviceAddress + pMissShaderBindingTable->stride × missIndex

				对 vkCmdTraceRaysNV 命令，正确计算missShaderBindingTableBuffer的一个索引为:
					missShaderBindingOffset + missShaderBindingStride × missIndex

				其中其中 missIndex  是传递给traceNV() 或者 traceRayEXT() shader指令的参数（GLSL），在SPIR-V中为传递给 pipeline trace ray指令的 MissIndex

			------------------------------------------------------
			对Callable Shaders:
				对 vkCmdTraceRaysKHR 命令,正确计算pCallableShaderBindingTable的一个索引为:
					pCallableShaderBindingTable->deviceAddress + pCallableShaderBindingTable->stride × sbtRecordIndex

				对 vkCmdTraceRaysNV 命令，正确计算callableShaderBindingTableBuffer的一个索引为:
					callableShaderBindingOffset + callableShaderBindingStride × sbtRecordIndex

				其中其中 sbtRecordIndex  是传递给traceNV() 或者 traceRayEXT() shader指令的参数（GLSL），在SPIR-V中为传递给 OpExecuteCallableNV 或者 OpExecuteCallableKHR的 SBTIndex

			
			*/

		}
	}


	//Ray Tracing Pipeline Stack  参见p3394

	//Ray Tracing Capture Replay  参见p3395  ,类似于bufferDeviceAddressCaptureReplay

	//Ray Tracing Validation  参见p3395， 开启 ray tracing validation 特性能够使警告和错误信息能够通过 messenger callback直接传递给实现，然后在应用程序端的debug或者Log系统中处理
}

NS_TEST_END