#include "QueriesTest.h"
#include "vulkan/vulkan_beta.h"
NS_TEST_BEGIN
/*
概述:
query提供了一种可以从一系列的vulkan commands的执行中返回一些执行信息的机制

*/
QueriesTest::QueriesTest()
{
}

void QueriesTest::run()
{
}

QueriesTest::~QueriesTest()
{
}

struct QueryPoolCreateInfoEXT {
	VkQueryPoolPerformanceCreateInfoKHR queryPoolPerformanceCreateInfoKHR{};
	VkQueryPoolPerformanceQueryCreateInfoINTEL queryPoolPerformanceQueryCreateInfoINTEL{};
	VkQueryPoolVideoEncodeFeedbackCreateInfoKHR queryPoolVideoEncodeFeedbackCreateInfoKHR{};
	VkVideoDecodeAV1ProfileInfoKHR videoDecodeAV1ProfileInfoKHR{};
	VkVideoDecodeH264ProfileInfoKHR videoDecodeH264ProfileInfoKHR{};
	VkVideoDecodeH265ProfileInfoKHR videoDecodeH265ProfileInfoKHR{};
	VkVideoDecodeUsageInfoKHR videoDecodeUsageInfoKHR{};
	VkVideoEncodeH264ProfileInfoKHR videoEncodeH264ProfileInfoKHR{};
	VkVideoEncodeH265ProfileInfoKHR videoEncodeH265ProfileInfoKHR{};
	VkVideoEncodeUsageInfoKHR videoEncodeUsageInfoKHR{};
	VkVideoProfileInfoKHR videoProfileInfoKHR{};
	QueryPoolCreateInfoEXT() {
		Init();
	}
	void Init() {
		queryPoolPerformanceCreateInfoKHR.sType = VK_STRUCTURE_TYPE_QUERY_POOL_PERFORMANCE_CREATE_INFO_KHR;
		queryPoolPerformanceCreateInfoKHR.pNext = nullptr;
		queryPoolPerformanceQueryCreateInfoINTEL.sType = VK_STRUCTURE_TYPE_QUERY_POOL_PERFORMANCE_QUERY_CREATE_INFO_INTEL;
		queryPoolPerformanceQueryCreateInfoINTEL.pNext = nullptr;
		queryPoolVideoEncodeFeedbackCreateInfoKHR.sType = VK_STRUCTURE_TYPE_MAX_ENUM;//没有定义，这里定义为非法值
		queryPoolVideoEncodeFeedbackCreateInfoKHR.pNext = nullptr;
		videoDecodeAV1ProfileInfoKHR.sType = VK_STRUCTURE_TYPE_MAX_ENUM;//没有定义，这里定义为非法值
		videoDecodeAV1ProfileInfoKHR.pNext = nullptr;
		videoDecodeH264ProfileInfoKHR.sType = VK_STRUCTURE_TYPE_VIDEO_DECODE_H264_PROFILE_INFO_KHR;
		videoDecodeH264ProfileInfoKHR.pNext = nullptr;
		videoDecodeH265ProfileInfoKHR.sType = VK_STRUCTURE_TYPE_VIDEO_DECODE_H265_PROFILE_INFO_KHR;
		videoDecodeH265ProfileInfoKHR.pNext = nullptr;
		videoDecodeUsageInfoKHR.sType = VK_STRUCTURE_TYPE_VIDEO_DECODE_USAGE_INFO_KHR;
		videoDecodeUsageInfoKHR.pNext = nullptr;
		videoEncodeH264ProfileInfoKHR.sType = VK_STRUCTURE_TYPE_MAX_ENUM;//没有定义，这里定义为非法值
		videoEncodeH264ProfileInfoKHR.pNext = nullptr;
		videoEncodeH265ProfileInfoKHR.sType = VK_STRUCTURE_TYPE_MAX_ENUM;//没有定义，这里定义为非法值
		videoEncodeH265ProfileInfoKHR.pNext = nullptr;
		videoEncodeUsageInfoKHR.sType = VK_STRUCTURE_TYPE_MAX_ENUM;//没有定义，这里定义为非法值
		videoEncodeUsageInfoKHR.pNext = nullptr;
		videoProfileInfoKHR.sType = VK_STRUCTURE_TYPE_VIDEO_PROFILE_INFO_KHR;
		videoProfileInfoKHR.pNext = nullptr;
	}
		
};

void QueriesTest::QueryPoolTest()
{
	VkQueryPool queryPool{};
	VkQueryPoolCreateInfo queryPoolCreateInfo{};
	queryPoolCreateInfo.sType = VK_STRUCTURE_TYPE_QUERY_POOL_CREATE_INFO;
		QueryPoolCreateInfoEXT queryPoolCreateInfoEXT{  };
	
	queryPoolCreateInfo.pNext = &queryPoolCreateInfoEXT.queryPoolPerformanceCreateInfoKHR;
	queryPoolCreateInfo.flags = 0;//保留未来使用
	queryPoolCreateInfo.queryCount = 1;//是这个pool管理的query的数量
	queryPoolCreateInfo.queryType = VK_QUERY_TYPE_MICROMAP_SERIALIZATION_SIZE_EXT;//为 VkQueryType 值，指明这个pool管理query的类型
	/*
	VkQueryType:
	
    VK_QUERY_TYPE_OCCLUSION:   指明一个阻塞查询.
    VK_QUERY_TYPE_PIPELINE_STATISTICS:   指明一个 pipeline statistics 查询.
    VK_QUERY_TYPE_TIMESTAMP:   指明一个 timestamp 查询.
    VK_QUERY_TYPE_PERFORMANCE_QUERY_KHR:   指明一个性能查询.
    VK_QUERY_TYPE_TRANSFORM_FEEDBACK_STREAM_EXT:   指明一个transform feedback 查询.
    VK_QUERY_TYPE_PRIMITIVES_GENERATED_EXT:   指明一个primitives generated查询.
    VK_QUERY_TYPE_ACCELERATION_STRUCTURE_COMPACTED_SIZE_KHR:   指明使用vkCmdWriteAccelerationStructuresPropertiesKHR 或者vkWriteAccelerationStructuresPropertiesKHR的加速结构的大小查询
    VK_QUERY_TYPE_ACCELERATION_STRUCTURE_SERIALIZATION_SIZE_KHR:   指明一个加速结构序列化的大小查询
    VK_QUERY_TYPE_ACCELERATION_STRUCTURE_SIZE_KHR:   指明使用vkCmdWriteAccelerationStructuresPropertiesKHR 或者vkWriteAccelerationStructuresPropertiesKHR的加速结构的大小查询
    VK_QUERY_TYPE_ACCELERATION_STRUCTURE_SERIALIZATION_BOTTOM_LEVEL_POINTERS_KHR:   指明一个加速结构指针数量查询
    VK_QUERY_TYPE_ACCELERATION_STRUCTURE_COMPACTED_SIZE_NV:   指明使用vkCmdWriteAccelerationStructuresPropertiesNV的加速结构的大小查询
    VK_QUERY_TYPE_PERFORMANCE_QUERY_INTEL:   指明一个 Intel性能查询.
    VK_QUERY_TYPE_RESULT_STATUS_ONLY_KHR:   指明一个结果状态查询.
    VK_QUERY_TYPE_VIDEO_ENCODE_FEEDBACK_KHR:   指明一个video encode feedback 查询.
    VK_QUERY_TYPE_MESH_PRIMITIVES_GENERATED_EXT:   指明一个 generated mesh primitives 查询.
	*/
	queryPoolCreateInfo.pipelineStatistics = VK_QUERY_PIPELINE_STATISTIC_CLIPPING_INVOCATIONS_BIT;//是 VkQueryPipelineStatisticFlagBits 组合值的位掩码，指明query中哪个计数器会返回到pool中，参见 Pipeline Statistics Queries p1573,在 queryType 不为 VK_QUERY_TYPE_PIPELINE_STATISTICS的时候忽略该值
	/*
	VkQueryPoolCreateInfo有效用法:
	1.如果pipelineStatisticsQuery 特性没有开启，queryType 不能是VK_QUERY_TYPE_PIPELINE_STATISTICS
	2.如果meshShaderQueries 特性没有开启，则（1）queryType 不能是VK_QUERY_TYPE_MESH_PRIMITIVES_GENERATED_EXT
											（2）如果queryType 是VK_QUERY_TYPE_PIPELINE_STATISTICS，则pipelineStatistics不能包含VK_QUERY_PIPELINE_STATISTIC_TASK_SHADER_INVOCATIONS_BIT_EXT 或者 VK_QUERY_PIPELINE_STATISTIC_MESH_SHADER_INVOCATIONS_BIT_EXT
	3.如果queryType是VK_QUERY_TYPE_PIPELINE_STATISTICS，则pipelineStatistics 必须是有效的VkQueryPipelineStatisticFlagBits 组合值，且不能为0
	4.如果queryType是VK_QUERY_TYPE_PERFORMANCE_QUERY_KHR，则pNext中必须包含一个VkQueryPoolPerformanceCreateInfoKHR
	5.queryCount必须大于0
	6.如果queryType是VK_QUERY_TYPE_VIDEO_ENCODE_FEEDBACK_KHR，则（1）pNext中必须包含一个videoCodecOperation指明了encode operation 的VkVideoProfileInfoKHR
																（2）pNext中必须包含一个VkQueryPoolVideoEncodeFeedbackCreateInfoKHR
																（3）如果pNext中包含一个VkVideoProfileInfoKHR 以及VkQueryPoolVideoEncodeFeedbackCreateInfoKHR，则VkQueryPoolVideoEncodeFeedbackCreateInfoKHR::encodeFeedbackFlags 不能包含任何没有设置在
																							调用vkGetPhysicalDeviceVideoCapabilitiesKHR传入VkVideoProfileInfoKHR到其参数的pNext中返回的 VkVideoEncodeCapabilitiesKHR::supportedEncodeFeedbackFlags的比特值
	
	*/


	//VkQueryPoolPerformanceCreateInfoKHR
	VkQueryPoolPerformanceCreateInfoKHR& queryPoolPerformanceCreateInfoKHR = queryPoolCreateInfoEXT.queryPoolPerformanceCreateInfoKHR;
	queryPoolPerformanceCreateInfoKHR.counterIndexCount = 1;//pCounterIndices中元素个数
	queryPoolPerformanceCreateInfoKHR.queueFamilyIndex = 0;//是要为哪个队列族创建该performance query pool
		uint32_t counterIndex = 0;
	queryPoolPerformanceCreateInfoKHR.pCounterIndices = &counterIndex;//是一组索引到vkEnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersKHR::pCounters的索引值，指明performance query pool要启用那些counter
	/*
	VkQueryPoolPerformanceCreateInfoKHR有效用法:
	1.queueFamilyIndex 必须是device中有效的队列族的索引
	2.performanceCounterQueryPools 特性必须开启
	3.pCounterIndices中的每个元素必须是在调用vkEnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersKHR，指定queueFamilyIndex返回的counter的范围内

	*/

	//查询performance query pool查询所需的pass的数量
	{
		uint32_t numPass;
		vkGetPhysicalDeviceQueueFamilyPerformanceQueryPassesKHR(physicalDevice, &queryPoolPerformanceCreateInfoKHR, &numPass);
	}

	vkCreateQueryPool(device, &queryPoolCreateInfo, nullptr, &queryPool);


	vkDestroyQueryPool(device, queryPool, nullptr);

}

void QueriesTest::QueryOperationsTest()
{
	/*
	查询通过以下命令进行控制:  命令的功能描述见p1544,简单流程讲就是 查询--> pool存储结果 -->  调用命令获取结果  
	vkCmdBeginQuery, vkCmdEndQuery,
	vkCmdBeginQueryIndexedEXT, vkCmdEndQueryIndexedEXT, vkCmdResetQueryPool,
	vkCmdCopyQueryPoolResults, vkCmdWriteTimestamp2, 以及 vkCmdWriteTimestamp.

	*/

	VkQueryPool validQueryPool{};//假设这是一个有效的VkQueryPool
	VkCommandBuffer commandBuffer{};//假设这是一个有效的VkCommandBuffer
	//重置Query Pool上的queries
	vkCmdResetQueryPool(commandBuffer, validQueryPool, 0/*第一个要重置的query的索引*/, 1/*要重置的query的数量*/);
	/*
	vkResetQueryPool有效用法:
	1.firstQuery必须小于queryPool 中query的数量
	2.firstQuery + queryCount必须小于等于queryPool 中query的数量
	3.这个命令使用的所有query 不能是激活的
	4.如果queryPool 以VK_QUERY_TYPE_PERFORMANCE_QUERY_KHR创建，则这个命令就不能记录在任何command buffer中，不管是primary 还是second command buffer，还包含开始查询 [firstQuery,firstQuery + queryCount - 1]的命令
	*/



}






NS_TEST_END