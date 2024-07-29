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
	查询通过以下命令进行控制:  命令的功能描述见p1544,简单流程讲就是 查询begin --> 查询end  --> pool存储结果 -->  调用命令获取结果  
	vkCmdBeginQuery, vkCmdEndQuery,
	vkCmdBeginQueryIndexedEXT, vkCmdEndQueryIndexedEXT, vkCmdResetQueryPool,
	vkCmdCopyQueryPoolResults, vkCmdWriteTimestamp2, 以及 vkCmdWriteTimestamp.


	begin和end必须同时在subpass内或外，或者同时在video coding scope内或外
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

	//host端重置Query Pool上的queries  等价于vkResetQueryPoolEXT
	vkResetQueryPool(device, validQueryPool, 0/*第一个要重置的query的索引*/, 1/*要重置的query的数量*/);
	/*
	vkResetQueryPool有效用法:
	1.firstQuery必须小于queryPool 中query的数量
	2.firstQuery + queryCount必须小于等于queryPool 中query的数量
	3.hostQueryReset 特性必须开启
	4.已经提交的引用到queryPool的[firstQuery,firstQuery + queryCount - 1]的queries 的commands必须已经完成执行
	5.queryPool的[firstQuery,firstQuery + queryCount - 1]的queries 不能在别的线程中被vkGetQueryPoolResults 或者vkResetQueryPool 调用

	
	*/

	//查询    参见p1549
	{
		//开始查询   调用了这个命令后就认为这个query已经激活了
		vkCmdBeginQuery(commandBuffer, validQueryPool, 0/*指明queryPool中用来存放结果的query的索引*/, VK_QUERY_CONTROL_PRECISE_BIT/* VkQueryControlFlagBits 组合值位掩码，指明能被执行的query的类型限制     VK_QUERY_CONTROL_PRECISE_BIT:  指明阻塞查询的精度*/);//
		/*
		vkCmdBeginQuery有效用法:
		1.所有这个命令使用的queries必须是无效的
		2.创建queryPool的 queryType 不能为VK_QUERY_TYPE_TIMESTAMP，VK_QUERY_TYPE_ACCELERATION_STRUCTURE_COMPACTED_SIZE_KHR，VK_QUERY_TYPE_ACCELERATION_STRUCTURE_SERIALIZATION_SIZE_KHR
					VK_QUERY_TYPE_ACCELERATION_STRUCTURE_SIZE_KHR，VK_QUERY_TYPE_ACCELERATION_STRUCTURE_SERIALIZATION_BOTTOM_LEVEL_POINTERS_KHR，或者VK_QUERY_TYPE_ACCELERATION_STRUCTURE_COMPACTED_SIZE_NV				
		3.如果occlusionQueryPrecise 特性没有开启，或者创建queryPool的 queryType 不为VK_QUERY_TYPE_OCCLUSION，则flags不能包含VK_QUERY_CONTROL_PRECISE_BIT	
		4.query必须小于queryPool中queries的数量
		5.创建queryPool的 queryType 为VK_QUERY_TYPE_OCCLUSION，则commandBuffer所在的VkCommandPool创建时的队列族必须支持graphics operations
		6.创建queryPool的 queryType 为VK_QUERY_TYPE_PIPELINE_STATISTICS且pipelineStatistics 中任何一个指定了graphics operations，则commandBuffer所在的VkCommandPool创建时的队列族必须支持graphics operations
		7.创建queryPool的 queryType 为VK_QUERY_TYPE_PIPELINE_STATISTICS且pipelineStatistics 中任何一个指定了compute operations，则commandBuffer所在的VkCommandPool创建时的队列族必须支持compute operations
		8.commandBuffer 不能是一个protected command buffer
		9.如果该命令在一个render pass instance中调用，命令开始的query的数量以及在当前subpass的view mask中设置的bits的数量必须小于等于queryPool中queries的数量
		10.如果创建queryPool的 queryType 为VK_QUERY_TYPE_RESULT_STATUS_ONLY_KHR，则commandBuffer所在的VkCommandPool创建时的队列族必须支持 result status queries，参见VkQueueFamilyQueryResultStatusPropertiesKHR::queryResultStatusSupport 
		11.如果调用命令这里为一个绑定的video session，则（1）不能有激活的queries
													    （2）该video session不能以VK_VIDEO_SESSION_CREATE_INLINE_QUERIES_BIT_KHR 创建
		12.如果创建queryPool的 queryType 为VK_QUERY_TYPE_RESULT_STATUS_ONLY_KHR且调用命令这里为一个绑定的video session，则queryPool的创建必须在其VkQueryPoolCreateInfo.pNext中包含一个和创建该绑定的video session的VkVideoSessionCreateInfoKHR::pVideoProfile相同的VkVideoProfileInfoKHR
		13.如果创建queryPool的 queryType 为VK_QUERY_TYPE_VIDEO_ENCODE_FEEDBACK_KHR，则（1）调用该命令的位置必须有一个绑定的video session
																					  （2）如果调用该命令的位置有一个绑定的video session，则queryPool的创建必须在其VkQueryPoolCreateInfo.pNext中包含一个和创建该绑定的video session的VkVideoSessionCreateInfoKHR::pVideoProfile相同的VkVideoProfileInfoKHR
		14.如果创建queryPool的 queryType 不为VK_QUERY_TYPE_RESULT_STATUS_ONLY_KHR 或者VK_QUERY_TYPE_VIDEO_ENCODE_FEEDBACK_KHR，则调用该命令的位置不能有一个绑定的video session
		15.queryPool 必须以一个和当前commandBuffer中已经激活的queries所在的VkQueryPool不同的queryType 创建
		16.如果创建queryPool的 queryType 为VK_QUERY_TYPE_MESH_PRIMITIVES_GENERATED_EXT ， VK_QUERY_TYPE_TRANSFORM_FEEDBACK_STREAM_EXT 或者VK_QUERY_TYPE_PRIMITIVES_GENERATED_EXT，则commandBuffer所在的VkCommandPool创建时的队列族必须支持graphics operations
		17.如果创建queryPool的 queryType 为VK_QUERY_TYPE_TRANSFORM_FEEDBACK_STREAM_EXT，则必须支持VkPhysicalDeviceTransformFeedbackPropertiesEXT::transformFeedbackQueries
		18.如果创建queryPool的 queryType 为VK_QUERY_TYPE_PRIMITIVES_GENERATED_EXT，则primitivesGeneratedQuery 必须启用
		19.如果创建queryPool的 queryType 为VK_QUERY_TYPE_PERFORMANCE_QUERY_KHR，则（1）创建queryPool的VkQueryPoolCreateInfo.pNext中的VkQueryPoolPerformanceCreateInfoKHR::queueFamilyIndex 必须等于当前commandBuffer所在的VkCommandPool创建时候的队列族索引
																				  （2）profiling lock 必须在commandBuffer的vkBeginCommandBuffer调用前被获取
																				  （3）如果用于创建queryPool的counters中的一个为VK_PERFORMANCE_COUNTER_SCOPE_COMMAND_BUFFER_KHR，则该命令必须是commandBuffer中记录的第一个命令
																				  （4）如果用于创建queryPool的counters中的一个为VK_PERFORMANCE_COUNTER_SCOPE_RENDER_PASS_KHR，则该命令不能记录在一个render pass instance中
																				  （5）如果其他以queryType 为VK_QUERY_TYPE_PERFORMANCE_QUERY_KHR创建的queryPool也在该commandBuffer中使用，其父primary command buffer 或者 secondary command buffer记录在和commandBuffer相同的parent primary command buffer中，则performanceCounterMultipleQueryPools 特性必须开启
																				  （6）这个命令就不能直接或间接记录在一个影响相同query查询的包含vkCmdResetQueryPool 命令的command buffer中

		*/

		//vkCmd***  >>>....  假设这是一组想要查询信息的命令

		//在一系列期望的命令后结束查询   该命令结束后会标记query为有效状态
		vkCmdEndQuery(commandBuffer, validQueryPool, 0/*指明queryPool中用来存放结果的query的索引*/);
		/*
		vkCmdEndQuery有效用法:
		1.所有这个命令使用的queries必须是激活的
		2.query必须小于queryPool中queries的数量
		3.commandBuffer 不能是一个protected command buffer
		4.如果vkCmdEndQuery 在一个render pass instance中调用，则调用query的数量以及在当前subpass的view mask中设置的bits的数量必须小于等于queryPool中queries的数量
		5.如果创建queryPool的 queryType 为VK_QUERY_TYPE_PERFORMANCE_QUERY_KHR，则（1）如果用于创建queryPool的counters中的一个或多个为VK_PERFORMANCE_COUNTER_SCOPE_COMMAND_BUFFER_KHR，则该命令必须是commandBuffer中记录的最后一个命令
																				 （2）如果用于创建queryPool的counters中的一个或多个为VK_PERFORMANCE_COUNTER_SCOPE_RENDER_PASS_KHR，则该命令不能记录在一个render pass instance中
		6.如果在render pass instance的一个subpass中调用该命令，则对应的vkCmdBeginQuery* 命令必须在该subpass中的前面被调用
		*/




		//开始一个 indexed query
		vkCmdBeginQueryIndexedEXT(commandBuffer, validQueryPool, 0/*指明queryPool中用来存放结果的query的索引*/, VK_QUERY_CONTROL_PRECISE_BIT/* VkQueryControlFlagBits 组合值位掩码，指明能被执行的query的类型限制*/, 
																	1/*query type特定的索引，如果query type为VK_QUERY_TYPE_TRANSFORM_FEEDBACK_STREAM_EXT 或者 VK_QUERY_TYPE_PRIMITIVES_GENERATED_EXT，则这个参数表示vertex stream*/ );//
		/*
		vkCmdBeginQueryIndexedEXT有效用法:
		1.所有这个命令使用的queries必须是无效的
		2.创建queryPool的 queryType 不能为VK_QUERY_TYPE_TIMESTAMP，VK_QUERY_TYPE_ACCELERATION_STRUCTURE_COMPACTED_SIZE_KHR，VK_QUERY_TYPE_ACCELERATION_STRUCTURE_SERIALIZATION_SIZE_KHR
					VK_QUERY_TYPE_ACCELERATION_STRUCTURE_SIZE_KHR，VK_QUERY_TYPE_ACCELERATION_STRUCTURE_SERIALIZATION_BOTTOM_LEVEL_POINTERS_KHR，或者VK_QUERY_TYPE_ACCELERATION_STRUCTURE_COMPACTED_SIZE_NV
		3.如果occlusionQueryPrecise 特性没有开启，或者创建queryPool的 queryType 不为VK_QUERY_TYPE_OCCLUSION，则flags不能包含VK_QUERY_CONTROL_PRECISE_BIT
		4.query必须小于queryPool中queries的数量
		5.创建queryPool的 queryType 为VK_QUERY_TYPE_OCCLUSION，则commandBuffer所在的VkCommandPool创建时的队列族必须支持graphics operations
		6.创建queryPool的 queryType 为VK_QUERY_TYPE_PIPELINE_STATISTICS且pipelineStatistics 中任何一个指定了graphics operations，则commandBuffer所在的VkCommandPool创建时的队列族必须支持graphics operations
		7.创建queryPool的 queryType 为VK_QUERY_TYPE_PIPELINE_STATISTICS且pipelineStatistics 中任何一个指定了compute operations，则commandBuffer所在的VkCommandPool创建时的队列族必须支持compute operations
		8.commandBuffer 不能是一个protected command buffer
		9.如果该命令在一个render pass instance中调用，命令开始的query的数量以及在当前subpass的view mask中设置的bits的数量必须小于等于queryPool中queries的数量
		10.如果创建queryPool的 queryType 为VK_QUERY_TYPE_RESULT_STATUS_ONLY_KHR，则commandBuffer所在的VkCommandPool创建时的队列族必须支持 result status queries，参见VkQueueFamilyQueryResultStatusPropertiesKHR::queryResultStatusSupport
		11.如果调用命令这里为一个绑定的video session，则（1）不能有激活的queries
														（2）该video session不能以VK_VIDEO_SESSION_CREATE_INLINE_QUERIES_BIT_KHR 创建
		12.如果创建queryPool的 queryType 为VK_QUERY_TYPE_RESULT_STATUS_ONLY_KHR且调用命令这里为一个绑定的video session，则queryPool的创建必须在其VkQueryPoolCreateInfo.pNext中包含一个和创建该绑定的video session的VkVideoSessionCreateInfoKHR::pVideoProfile相同的VkVideoProfileInfoKHR
		13.如果创建queryPool的 queryType 为VK_QUERY_TYPE_VIDEO_ENCODE_FEEDBACK_KHR，则（1）调用该命令的位置必须有一个绑定的video session
																					  （2）如果调用该命令的位置有一个绑定的video session，则queryPool的创建必须在其VkQueryPoolCreateInfo.pNext中包含一个和创建该绑定的video session的VkVideoSessionCreateInfoKHR::pVideoProfile相同的VkVideoProfileInfoKHR
		14.如果创建queryPool的 queryType 不为VK_QUERY_TYPE_RESULT_STATUS_ONLY_KHR 或者VK_QUERY_TYPE_VIDEO_ENCODE_FEEDBACK_KHR，则调用该命令的位置不能有一个绑定的video session
		15.如果queryPool 以一个和当前commandBuffer中已经激活的queries所在的VkQueryPool相同的queryType 创建，则index不能和那个激活的query的index匹配
		16.如果创建queryPool的 queryType 为VK_QUERY_TYPE_TRANSFORM_FEEDBACK_STREAM_EXT，则（1）commandBuffer所在的VkCommandPool创建时的队列族必须支持graphics operations
																						  （2）index 必须小于VkPhysicalDeviceTransformFeedbackPropertiesEXT::maxTransformFeedbackStreams
		17.如果创建queryPool的queryType 不为VK_QUERY_TYPE_TRANSFORM_FEEDBACK_STREAM_EXT 且不为VK_QUERY_TYPE_PRIMITIVES_GENERATED_EXT ，则index 必须为0
		18.如果创建queryPool的 queryType 为VK_QUERY_TYPE_PRIMITIVES_GENERATED_EXT，则（1）commandBuffer所在的VkCommandPool创建时的队列族必须支持graphics operations
																				     （2）index 必须小于VkPhysicalDeviceTransformFeedbackPropertiesEXT::maxTransformFeedbackStreams
																					 （3）如果primitivesGeneratedQueryWithNonZeroStreams 特性没有开启，则index 必须为0
																					 （4）primitivesGeneratedQuery 必须启用
		19.如果创建queryPool的 queryType 为VK_QUERY_TYPE_TRANSFORM_FEEDBACK_STREAM_EXT，则必须支持VkPhysicalDeviceTransformFeedbackPropertiesEXT::transformFeedbackQueries
		20.创建queryPool的 queryType 不能为VK_QUERY_TYPE_MESH_PRIMITIVES_GENERATED_EXT
		21.如果创建queryPool的 queryType 为VK_QUERY_TYPE_PERFORMANCE_QUERY_KHR，则（1）创建queryPool的VkQueryPoolCreateInfo.pNext中的VkQueryPoolPerformanceCreateInfoKHR::queueFamilyIndex 必须等于当前commandBuffer所在的VkCommandPool创建时候的队列族索引
																				  （2）profiling lock 必须在commandBuffer的vkBeginCommandBuffer调用前被获取
																				  （3）如果用于创建queryPool的counters中的一个为VK_PERFORMANCE_COUNTER_SCOPE_COMMAND_BUFFER_KHR，则该命令必须是commandBuffer中记录的第一个命令
																				  （4）如果用于创建queryPool的counters中的一个为VK_PERFORMANCE_COUNTER_SCOPE_RENDER_PASS_KHR，则该命令不能记录在一个render pass instance中
																				  （5）如果其他以queryType 为VK_QUERY_TYPE_PERFORMANCE_QUERY_KHR创建的queryPool也在该commandBuffer中使用，其父primary command buffer 或者 secondary command buffer记录在和commandBuffer相同的parent primary command buffer中，则performanceCounterMultipleQueryPools 特性必须开启
																				  （6）这个命令就不能直接或间接记录在一个影响相同query查询的包含vkCmdResetQueryPool 命令的command buffer中

		*/


		//在一系列期望的命令后结束 indexed query   该命令结束后会标记query为有效状态
		vkCmdEndQueryIndexedEXT(commandBuffer, validQueryPool, 0/*指明queryPool中用来存放结果的query的索引*/, 0/*query type特定的索引*/);
		/*
		vkCmdEndQueryIndexedEXT有效用法:
		1.所有这个命令使用的queries必须是激活的
		2.query必须小于queryPool中queries的数量
		3.commandBuffer 不能是一个protected command buffer
		4.如果vkCmdEndQueryIndexedEXT 在一个render pass instance中调用，则调用query的数量以及在当前subpass的view mask中设置的bits的数量必须小于等于queryPool中queries的数量
		5.如果创建queryPool的 queryType 为VK_QUERY_TYPE_TRANSFORM_FEEDBACK_STREAM_EXT 或者 VK_QUERY_TYPE_PRIMITIVES_GENERATED_EXT，则index 必须小于VkPhysicalDeviceTransformFeedbackPropertiesEXT::maxTransformFeedbackStreams，且index必须等于 vkCmdBeginQueryIndexedEXT 中指定的index
		6.如果创建queryPool的queryType 不为VK_QUERY_TYPE_TRANSFORM_FEEDBACK_STREAM_EXT 且不为VK_QUERY_TYPE_PRIMITIVES_GENERATED_EXT ，则index 必须为0
		7.如果在render pass instance的一个subpass中调用该命令，则对应的vkCmdBeginQuery* 命令必须在该subpass中的前面被调用

		*/

	}



}






NS_TEST_END