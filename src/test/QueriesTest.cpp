#include "QueriesTest.h"
#include "vulkan/vulkan_beta.h"
NS_TEST_BEGIN
/*
����:
query�ṩ��һ�ֿ��Դ�һϵ�е�vulkan commands��ִ���з���һЩִ����Ϣ�Ļ���

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
		queryPoolVideoEncodeFeedbackCreateInfoKHR.sType = VK_STRUCTURE_TYPE_MAX_ENUM;//û�ж��壬���ﶨ��Ϊ�Ƿ�ֵ
		queryPoolVideoEncodeFeedbackCreateInfoKHR.pNext = nullptr;
		videoDecodeAV1ProfileInfoKHR.sType = VK_STRUCTURE_TYPE_MAX_ENUM;//û�ж��壬���ﶨ��Ϊ�Ƿ�ֵ
		videoDecodeAV1ProfileInfoKHR.pNext = nullptr;
		videoDecodeH264ProfileInfoKHR.sType = VK_STRUCTURE_TYPE_VIDEO_DECODE_H264_PROFILE_INFO_KHR;
		videoDecodeH264ProfileInfoKHR.pNext = nullptr;
		videoDecodeH265ProfileInfoKHR.sType = VK_STRUCTURE_TYPE_VIDEO_DECODE_H265_PROFILE_INFO_KHR;
		videoDecodeH265ProfileInfoKHR.pNext = nullptr;
		videoDecodeUsageInfoKHR.sType = VK_STRUCTURE_TYPE_VIDEO_DECODE_USAGE_INFO_KHR;
		videoDecodeUsageInfoKHR.pNext = nullptr;
		videoEncodeH264ProfileInfoKHR.sType = VK_STRUCTURE_TYPE_MAX_ENUM;//û�ж��壬���ﶨ��Ϊ�Ƿ�ֵ
		videoEncodeH264ProfileInfoKHR.pNext = nullptr;
		videoEncodeH265ProfileInfoKHR.sType = VK_STRUCTURE_TYPE_MAX_ENUM;//û�ж��壬���ﶨ��Ϊ�Ƿ�ֵ
		videoEncodeH265ProfileInfoKHR.pNext = nullptr;
		videoEncodeUsageInfoKHR.sType = VK_STRUCTURE_TYPE_MAX_ENUM;//û�ж��壬���ﶨ��Ϊ�Ƿ�ֵ
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
	queryPoolCreateInfo.flags = 0;//����δ��ʹ��
	queryPoolCreateInfo.queryCount = 1;//�����pool�����query������
	queryPoolCreateInfo.queryType = VK_QUERY_TYPE_MICROMAP_SERIALIZATION_SIZE_EXT;//Ϊ VkQueryType ֵ��ָ�����pool����query������
	/*
	VkQueryType:
	
    VK_QUERY_TYPE_OCCLUSION:   ָ��һ��������ѯ.
    VK_QUERY_TYPE_PIPELINE_STATISTICS:   ָ��һ�� pipeline statistics ��ѯ.
    VK_QUERY_TYPE_TIMESTAMP:   ָ��һ�� timestamp ��ѯ.
    VK_QUERY_TYPE_PERFORMANCE_QUERY_KHR:   ָ��һ�����ܲ�ѯ.
    VK_QUERY_TYPE_TRANSFORM_FEEDBACK_STREAM_EXT:   ָ��һ��transform feedback ��ѯ.
    VK_QUERY_TYPE_PRIMITIVES_GENERATED_EXT:   ָ��һ��primitives generated��ѯ.
    VK_QUERY_TYPE_ACCELERATION_STRUCTURE_COMPACTED_SIZE_KHR:   ָ��ʹ��vkCmdWriteAccelerationStructuresPropertiesKHR ����vkWriteAccelerationStructuresPropertiesKHR�ļ��ٽṹ�Ĵ�С��ѯ
    VK_QUERY_TYPE_ACCELERATION_STRUCTURE_SERIALIZATION_SIZE_KHR:   ָ��һ�����ٽṹ���л��Ĵ�С��ѯ
    VK_QUERY_TYPE_ACCELERATION_STRUCTURE_SIZE_KHR:   ָ��ʹ��vkCmdWriteAccelerationStructuresPropertiesKHR ����vkWriteAccelerationStructuresPropertiesKHR�ļ��ٽṹ�Ĵ�С��ѯ
    VK_QUERY_TYPE_ACCELERATION_STRUCTURE_SERIALIZATION_BOTTOM_LEVEL_POINTERS_KHR:   ָ��һ�����ٽṹָ��������ѯ
    VK_QUERY_TYPE_ACCELERATION_STRUCTURE_COMPACTED_SIZE_NV:   ָ��ʹ��vkCmdWriteAccelerationStructuresPropertiesNV�ļ��ٽṹ�Ĵ�С��ѯ
    VK_QUERY_TYPE_PERFORMANCE_QUERY_INTEL:   ָ��һ�� Intel���ܲ�ѯ.
    VK_QUERY_TYPE_RESULT_STATUS_ONLY_KHR:   ָ��һ�����״̬��ѯ.
    VK_QUERY_TYPE_VIDEO_ENCODE_FEEDBACK_KHR:   ָ��һ��video encode feedback ��ѯ.
    VK_QUERY_TYPE_MESH_PRIMITIVES_GENERATED_EXT:   ָ��һ�� generated mesh primitives ��ѯ.
	*/
	queryPoolCreateInfo.pipelineStatistics = VK_QUERY_PIPELINE_STATISTIC_CLIPPING_INVOCATIONS_BIT;//�� VkQueryPipelineStatisticFlagBits ���ֵ��λ���룬ָ��query���ĸ��������᷵�ص�pool�У��μ� Pipeline Statistics Queries p1573,�� queryType ��Ϊ VK_QUERY_TYPE_PIPELINE_STATISTICS��ʱ����Ը�ֵ
	/*
	VkQueryPoolCreateInfo��Ч�÷�:
	1.���pipelineStatisticsQuery ����û�п�����queryType ������VK_QUERY_TYPE_PIPELINE_STATISTICS
	2.���meshShaderQueries ����û�п�������1��queryType ������VK_QUERY_TYPE_MESH_PRIMITIVES_GENERATED_EXT
											��2�����queryType ��VK_QUERY_TYPE_PIPELINE_STATISTICS����pipelineStatistics���ܰ���VK_QUERY_PIPELINE_STATISTIC_TASK_SHADER_INVOCATIONS_BIT_EXT ���� VK_QUERY_PIPELINE_STATISTIC_MESH_SHADER_INVOCATIONS_BIT_EXT
	3.���queryType��VK_QUERY_TYPE_PIPELINE_STATISTICS����pipelineStatistics ��������Ч��VkQueryPipelineStatisticFlagBits ���ֵ���Ҳ���Ϊ0
	4.���queryType��VK_QUERY_TYPE_PERFORMANCE_QUERY_KHR����pNext�б������һ��VkQueryPoolPerformanceCreateInfoKHR
	5.queryCount�������0
	6.���queryType��VK_QUERY_TYPE_VIDEO_ENCODE_FEEDBACK_KHR����1��pNext�б������һ��videoCodecOperationָ����encode operation ��VkVideoProfileInfoKHR
																��2��pNext�б������һ��VkQueryPoolVideoEncodeFeedbackCreateInfoKHR
																��3�����pNext�а���һ��VkVideoProfileInfoKHR �Լ�VkQueryPoolVideoEncodeFeedbackCreateInfoKHR����VkQueryPoolVideoEncodeFeedbackCreateInfoKHR::encodeFeedbackFlags ���ܰ����κ�û��������
																							����vkGetPhysicalDeviceVideoCapabilitiesKHR����VkVideoProfileInfoKHR���������pNext�з��ص� VkVideoEncodeCapabilitiesKHR::supportedEncodeFeedbackFlags�ı���ֵ
	
	*/


	//VkQueryPoolPerformanceCreateInfoKHR
	VkQueryPoolPerformanceCreateInfoKHR& queryPoolPerformanceCreateInfoKHR = queryPoolCreateInfoEXT.queryPoolPerformanceCreateInfoKHR;
	queryPoolPerformanceCreateInfoKHR.counterIndexCount = 1;//pCounterIndices��Ԫ�ظ���
	queryPoolPerformanceCreateInfoKHR.queueFamilyIndex = 0;//��ҪΪ�ĸ������崴����performance query pool
		uint32_t counterIndex = 0;
	queryPoolPerformanceCreateInfoKHR.pCounterIndices = &counterIndex;//��һ��������vkEnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersKHR::pCounters������ֵ��ָ��performance query poolҪ������Щcounter
	/*
	VkQueryPoolPerformanceCreateInfoKHR��Ч�÷�:
	1.queueFamilyIndex ������device����Ч�Ķ����������
	2.performanceCounterQueryPools ���Ա��뿪��
	3.pCounterIndices�е�ÿ��Ԫ�ر������ڵ���vkEnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersKHR��ָ��queueFamilyIndex���ص�counter�ķ�Χ��

	*/

	//��ѯperformance query pool��ѯ�����pass������
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
	��ѯͨ������������п���:  ����Ĺ���������p1544,�����̽����� ��ѯbegin --> ��ѯend  --> pool�洢��� -->  ���������ȡ���  
	vkCmdBeginQuery, vkCmdEndQuery,
	vkCmdBeginQueryIndexedEXT, vkCmdEndQueryIndexedEXT, vkCmdResetQueryPool,
	vkCmdCopyQueryPoolResults, vkCmdWriteTimestamp2, �Լ� vkCmdWriteTimestamp.


	begin��end����ͬʱ��subpass�ڻ��⣬����ͬʱ��video coding scope�ڻ���
	*/

	VkQueryPool validQueryPool{};//��������һ����Ч��VkQueryPool
	VkCommandBuffer commandBuffer{};//��������һ����Ч��VkCommandBuffer
	//����Query Pool�ϵ�queries
	vkCmdResetQueryPool(commandBuffer, validQueryPool, 0/*��һ��Ҫ���õ�query������*/, 1/*Ҫ���õ�query������*/);
	/*
	vkResetQueryPool��Ч�÷�:
	1.firstQuery����С��queryPool ��query������
	2.firstQuery + queryCount����С�ڵ���queryPool ��query������
	3.�������ʹ�õ�����query �����Ǽ����
	4.���queryPool ��VK_QUERY_TYPE_PERFORMANCE_QUERY_KHR���������������Ͳ��ܼ�¼���κ�command buffer�У�������primary ����second command buffer����������ʼ��ѯ [firstQuery,firstQuery + queryCount - 1]������
	*/

	//host������Query Pool�ϵ�queries  �ȼ���vkResetQueryPoolEXT
	vkResetQueryPool(device, validQueryPool, 0/*��һ��Ҫ���õ�query������*/, 1/*Ҫ���õ�query������*/);
	/*
	vkResetQueryPool��Ч�÷�:
	1.firstQuery����С��queryPool ��query������
	2.firstQuery + queryCount����С�ڵ���queryPool ��query������
	3.hostQueryReset ���Ա��뿪��
	4.�Ѿ��ύ�����õ�queryPool��[firstQuery,firstQuery + queryCount - 1]��queries ��commands�����Ѿ����ִ��
	5.queryPool��[firstQuery,firstQuery + queryCount - 1]��queries �����ڱ���߳��б�vkGetQueryPoolResults ����vkResetQueryPool ����

	
	*/

	//��ѯ    �μ�p1549
	{
		//��ʼ��ѯ   �����������������Ϊ���query�Ѿ�������
		vkCmdBeginQuery(commandBuffer, validQueryPool, 0/*ָ��queryPool��������Ž����query������*/, VK_QUERY_CONTROL_PRECISE_BIT/* VkQueryControlFlagBits ���ֵλ���룬ָ���ܱ�ִ�е�query����������     VK_QUERY_CONTROL_PRECISE_BIT:  ָ��������ѯ�ľ���*/);//
		/*
		vkCmdBeginQuery��Ч�÷�:
		1.�����������ʹ�õ�queries��������Ч��
		2.����queryPool�� queryType ����ΪVK_QUERY_TYPE_TIMESTAMP��VK_QUERY_TYPE_ACCELERATION_STRUCTURE_COMPACTED_SIZE_KHR��VK_QUERY_TYPE_ACCELERATION_STRUCTURE_SERIALIZATION_SIZE_KHR
					VK_QUERY_TYPE_ACCELERATION_STRUCTURE_SIZE_KHR��VK_QUERY_TYPE_ACCELERATION_STRUCTURE_SERIALIZATION_BOTTOM_LEVEL_POINTERS_KHR������VK_QUERY_TYPE_ACCELERATION_STRUCTURE_COMPACTED_SIZE_NV				
		3.���occlusionQueryPrecise ����û�п��������ߴ���queryPool�� queryType ��ΪVK_QUERY_TYPE_OCCLUSION����flags���ܰ���VK_QUERY_CONTROL_PRECISE_BIT	
		4.query����С��queryPool��queries������
		5.����queryPool�� queryType ΪVK_QUERY_TYPE_OCCLUSION����commandBuffer���ڵ�VkCommandPool����ʱ�Ķ��������֧��graphics operations
		6.����queryPool�� queryType ΪVK_QUERY_TYPE_PIPELINE_STATISTICS��pipelineStatistics ���κ�һ��ָ����graphics operations����commandBuffer���ڵ�VkCommandPool����ʱ�Ķ��������֧��graphics operations
		7.����queryPool�� queryType ΪVK_QUERY_TYPE_PIPELINE_STATISTICS��pipelineStatistics ���κ�һ��ָ����compute operations����commandBuffer���ڵ�VkCommandPool����ʱ�Ķ��������֧��compute operations
		8.commandBuffer ������һ��protected command buffer
		9.�����������һ��render pass instance�е��ã����ʼ��query�������Լ��ڵ�ǰsubpass��view mask�����õ�bits����������С�ڵ���queryPool��queries������
		10.�������queryPool�� queryType ΪVK_QUERY_TYPE_RESULT_STATUS_ONLY_KHR����commandBuffer���ڵ�VkCommandPool����ʱ�Ķ��������֧�� result status queries���μ�VkQueueFamilyQueryResultStatusPropertiesKHR::queryResultStatusSupport 
		11.���������������Ϊһ���󶨵�video session����1�������м����queries
													    ��2����video session������VK_VIDEO_SESSION_CREATE_INLINE_QUERIES_BIT_KHR ����
		12.�������queryPool�� queryType ΪVK_QUERY_TYPE_RESULT_STATUS_ONLY_KHR�ҵ�����������Ϊһ���󶨵�video session����queryPool�Ĵ�����������VkQueryPoolCreateInfo.pNext�а���һ���ʹ����ð󶨵�video session��VkVideoSessionCreateInfoKHR::pVideoProfile��ͬ��VkVideoProfileInfoKHR
		13.�������queryPool�� queryType ΪVK_QUERY_TYPE_VIDEO_ENCODE_FEEDBACK_KHR����1�����ø������λ�ñ�����һ���󶨵�video session
																					  ��2��������ø������λ����һ���󶨵�video session����queryPool�Ĵ�����������VkQueryPoolCreateInfo.pNext�а���һ���ʹ����ð󶨵�video session��VkVideoSessionCreateInfoKHR::pVideoProfile��ͬ��VkVideoProfileInfoKHR
		14.�������queryPool�� queryType ��ΪVK_QUERY_TYPE_RESULT_STATUS_ONLY_KHR ����VK_QUERY_TYPE_VIDEO_ENCODE_FEEDBACK_KHR������ø������λ�ò�����һ���󶨵�video session
		15.queryPool ������һ���͵�ǰcommandBuffer���Ѿ������queries���ڵ�VkQueryPool��ͬ��queryType ����
		16.�������queryPool�� queryType ΪVK_QUERY_TYPE_MESH_PRIMITIVES_GENERATED_EXT �� VK_QUERY_TYPE_TRANSFORM_FEEDBACK_STREAM_EXT ����VK_QUERY_TYPE_PRIMITIVES_GENERATED_EXT����commandBuffer���ڵ�VkCommandPool����ʱ�Ķ��������֧��graphics operations
		17.�������queryPool�� queryType ΪVK_QUERY_TYPE_TRANSFORM_FEEDBACK_STREAM_EXT�������֧��VkPhysicalDeviceTransformFeedbackPropertiesEXT::transformFeedbackQueries
		18.�������queryPool�� queryType ΪVK_QUERY_TYPE_PRIMITIVES_GENERATED_EXT����primitivesGeneratedQuery ��������
		19.�������queryPool�� queryType ΪVK_QUERY_TYPE_PERFORMANCE_QUERY_KHR����1������queryPool��VkQueryPoolCreateInfo.pNext�е�VkQueryPoolPerformanceCreateInfoKHR::queueFamilyIndex ������ڵ�ǰcommandBuffer���ڵ�VkCommandPool����ʱ��Ķ���������
																				  ��2��profiling lock ������commandBuffer��vkBeginCommandBuffer����ǰ����ȡ
																				  ��3��������ڴ���queryPool��counters�е�һ��ΪVK_PERFORMANCE_COUNTER_SCOPE_COMMAND_BUFFER_KHR��������������commandBuffer�м�¼�ĵ�һ������
																				  ��4��������ڴ���queryPool��counters�е�һ��ΪVK_PERFORMANCE_COUNTER_SCOPE_RENDER_PASS_KHR���������ܼ�¼��һ��render pass instance��
																				  ��5�����������queryType ΪVK_QUERY_TYPE_PERFORMANCE_QUERY_KHR������queryPoolҲ�ڸ�commandBuffer��ʹ�ã��丸primary command buffer ���� secondary command buffer��¼�ں�commandBuffer��ͬ��parent primary command buffer�У���performanceCounterMultipleQueryPools ���Ա��뿪��
																				  ��6���������Ͳ���ֱ�ӻ��Ӽ�¼��һ��Ӱ����ͬquery��ѯ�İ���vkCmdResetQueryPool �����command buffer��

		*/

		//vkCmd***  >>>....  ��������һ����Ҫ��ѯ��Ϣ������

		//��һϵ������������������ѯ   ��������������queryΪ��Ч״̬
		vkCmdEndQuery(commandBuffer, validQueryPool, 0/*ָ��queryPool��������Ž����query������*/);
		/*
		vkCmdEndQuery��Ч�÷�:
		1.�����������ʹ�õ�queries�����Ǽ����
		2.query����С��queryPool��queries������
		3.commandBuffer ������һ��protected command buffer
		4.���vkCmdEndQuery ��һ��render pass instance�е��ã������query�������Լ��ڵ�ǰsubpass��view mask�����õ�bits����������С�ڵ���queryPool��queries������
		5.�������queryPool�� queryType ΪVK_QUERY_TYPE_PERFORMANCE_QUERY_KHR����1��������ڴ���queryPool��counters�е�һ������ΪVK_PERFORMANCE_COUNTER_SCOPE_COMMAND_BUFFER_KHR��������������commandBuffer�м�¼�����һ������
																				 ��2��������ڴ���queryPool��counters�е�һ������ΪVK_PERFORMANCE_COUNTER_SCOPE_RENDER_PASS_KHR���������ܼ�¼��һ��render pass instance��
		6.�����render pass instance��һ��subpass�е��ø�������Ӧ��vkCmdBeginQuery* ��������ڸ�subpass�е�ǰ�汻����
		*/




		//��ʼһ�� indexed query
		vkCmdBeginQueryIndexedEXT(commandBuffer, validQueryPool, 0/*ָ��queryPool��������Ž����query������*/, VK_QUERY_CONTROL_PRECISE_BIT/* VkQueryControlFlagBits ���ֵλ���룬ָ���ܱ�ִ�е�query����������*/, 
																	1/*query type�ض������������query typeΪVK_QUERY_TYPE_TRANSFORM_FEEDBACK_STREAM_EXT ���� VK_QUERY_TYPE_PRIMITIVES_GENERATED_EXT�������������ʾvertex stream*/ );//
		/*
		vkCmdBeginQueryIndexedEXT��Ч�÷�:
		1.�����������ʹ�õ�queries��������Ч��
		2.����queryPool�� queryType ����ΪVK_QUERY_TYPE_TIMESTAMP��VK_QUERY_TYPE_ACCELERATION_STRUCTURE_COMPACTED_SIZE_KHR��VK_QUERY_TYPE_ACCELERATION_STRUCTURE_SERIALIZATION_SIZE_KHR
					VK_QUERY_TYPE_ACCELERATION_STRUCTURE_SIZE_KHR��VK_QUERY_TYPE_ACCELERATION_STRUCTURE_SERIALIZATION_BOTTOM_LEVEL_POINTERS_KHR������VK_QUERY_TYPE_ACCELERATION_STRUCTURE_COMPACTED_SIZE_NV
		3.���occlusionQueryPrecise ����û�п��������ߴ���queryPool�� queryType ��ΪVK_QUERY_TYPE_OCCLUSION����flags���ܰ���VK_QUERY_CONTROL_PRECISE_BIT
		4.query����С��queryPool��queries������
		5.����queryPool�� queryType ΪVK_QUERY_TYPE_OCCLUSION����commandBuffer���ڵ�VkCommandPool����ʱ�Ķ��������֧��graphics operations
		6.����queryPool�� queryType ΪVK_QUERY_TYPE_PIPELINE_STATISTICS��pipelineStatistics ���κ�һ��ָ����graphics operations����commandBuffer���ڵ�VkCommandPool����ʱ�Ķ��������֧��graphics operations
		7.����queryPool�� queryType ΪVK_QUERY_TYPE_PIPELINE_STATISTICS��pipelineStatistics ���κ�һ��ָ����compute operations����commandBuffer���ڵ�VkCommandPool����ʱ�Ķ��������֧��compute operations
		8.commandBuffer ������һ��protected command buffer
		9.�����������һ��render pass instance�е��ã����ʼ��query�������Լ��ڵ�ǰsubpass��view mask�����õ�bits����������С�ڵ���queryPool��queries������
		10.�������queryPool�� queryType ΪVK_QUERY_TYPE_RESULT_STATUS_ONLY_KHR����commandBuffer���ڵ�VkCommandPool����ʱ�Ķ��������֧�� result status queries���μ�VkQueueFamilyQueryResultStatusPropertiesKHR::queryResultStatusSupport
		11.���������������Ϊһ���󶨵�video session����1�������м����queries
														��2����video session������VK_VIDEO_SESSION_CREATE_INLINE_QUERIES_BIT_KHR ����
		12.�������queryPool�� queryType ΪVK_QUERY_TYPE_RESULT_STATUS_ONLY_KHR�ҵ�����������Ϊһ���󶨵�video session����queryPool�Ĵ�����������VkQueryPoolCreateInfo.pNext�а���һ���ʹ����ð󶨵�video session��VkVideoSessionCreateInfoKHR::pVideoProfile��ͬ��VkVideoProfileInfoKHR
		13.�������queryPool�� queryType ΪVK_QUERY_TYPE_VIDEO_ENCODE_FEEDBACK_KHR����1�����ø������λ�ñ�����һ���󶨵�video session
																					  ��2��������ø������λ����һ���󶨵�video session����queryPool�Ĵ�����������VkQueryPoolCreateInfo.pNext�а���һ���ʹ����ð󶨵�video session��VkVideoSessionCreateInfoKHR::pVideoProfile��ͬ��VkVideoProfileInfoKHR
		14.�������queryPool�� queryType ��ΪVK_QUERY_TYPE_RESULT_STATUS_ONLY_KHR ����VK_QUERY_TYPE_VIDEO_ENCODE_FEEDBACK_KHR������ø������λ�ò�����һ���󶨵�video session
		15.���queryPool ��һ���͵�ǰcommandBuffer���Ѿ������queries���ڵ�VkQueryPool��ͬ��queryType ��������index���ܺ��Ǹ������query��indexƥ��
		16.�������queryPool�� queryType ΪVK_QUERY_TYPE_TRANSFORM_FEEDBACK_STREAM_EXT����1��commandBuffer���ڵ�VkCommandPool����ʱ�Ķ��������֧��graphics operations
																						  ��2��index ����С��VkPhysicalDeviceTransformFeedbackPropertiesEXT::maxTransformFeedbackStreams
		17.�������queryPool��queryType ��ΪVK_QUERY_TYPE_TRANSFORM_FEEDBACK_STREAM_EXT �Ҳ�ΪVK_QUERY_TYPE_PRIMITIVES_GENERATED_EXT ����index ����Ϊ0
		18.�������queryPool�� queryType ΪVK_QUERY_TYPE_PRIMITIVES_GENERATED_EXT����1��commandBuffer���ڵ�VkCommandPool����ʱ�Ķ��������֧��graphics operations
																				     ��2��index ����С��VkPhysicalDeviceTransformFeedbackPropertiesEXT::maxTransformFeedbackStreams
																					 ��3�����primitivesGeneratedQueryWithNonZeroStreams ����û�п�������index ����Ϊ0
																					 ��4��primitivesGeneratedQuery ��������
		19.�������queryPool�� queryType ΪVK_QUERY_TYPE_TRANSFORM_FEEDBACK_STREAM_EXT�������֧��VkPhysicalDeviceTransformFeedbackPropertiesEXT::transformFeedbackQueries
		20.����queryPool�� queryType ����ΪVK_QUERY_TYPE_MESH_PRIMITIVES_GENERATED_EXT
		21.�������queryPool�� queryType ΪVK_QUERY_TYPE_PERFORMANCE_QUERY_KHR����1������queryPool��VkQueryPoolCreateInfo.pNext�е�VkQueryPoolPerformanceCreateInfoKHR::queueFamilyIndex ������ڵ�ǰcommandBuffer���ڵ�VkCommandPool����ʱ��Ķ���������
																				  ��2��profiling lock ������commandBuffer��vkBeginCommandBuffer����ǰ����ȡ
																				  ��3��������ڴ���queryPool��counters�е�һ��ΪVK_PERFORMANCE_COUNTER_SCOPE_COMMAND_BUFFER_KHR��������������commandBuffer�м�¼�ĵ�һ������
																				  ��4��������ڴ���queryPool��counters�е�һ��ΪVK_PERFORMANCE_COUNTER_SCOPE_RENDER_PASS_KHR���������ܼ�¼��һ��render pass instance��
																				  ��5�����������queryType ΪVK_QUERY_TYPE_PERFORMANCE_QUERY_KHR������queryPoolҲ�ڸ�commandBuffer��ʹ�ã��丸primary command buffer ���� secondary command buffer��¼�ں�commandBuffer��ͬ��parent primary command buffer�У���performanceCounterMultipleQueryPools ���Ա��뿪��
																				  ��6���������Ͳ���ֱ�ӻ��Ӽ�¼��һ��Ӱ����ͬquery��ѯ�İ���vkCmdResetQueryPool �����command buffer��

		*/


		//��һϵ���������������� indexed query   ��������������queryΪ��Ч״̬
		vkCmdEndQueryIndexedEXT(commandBuffer, validQueryPool, 0/*ָ��queryPool��������Ž����query������*/, 0/*query type�ض�������*/);
		/*
		vkCmdEndQueryIndexedEXT��Ч�÷�:
		1.�����������ʹ�õ�queries�����Ǽ����
		2.query����С��queryPool��queries������
		3.commandBuffer ������һ��protected command buffer
		4.���vkCmdEndQueryIndexedEXT ��һ��render pass instance�е��ã������query�������Լ��ڵ�ǰsubpass��view mask�����õ�bits����������С�ڵ���queryPool��queries������
		5.�������queryPool�� queryType ΪVK_QUERY_TYPE_TRANSFORM_FEEDBACK_STREAM_EXT ���� VK_QUERY_TYPE_PRIMITIVES_GENERATED_EXT����index ����С��VkPhysicalDeviceTransformFeedbackPropertiesEXT::maxTransformFeedbackStreams����index������� vkCmdBeginQueryIndexedEXT ��ָ����index
		6.�������queryPool��queryType ��ΪVK_QUERY_TYPE_TRANSFORM_FEEDBACK_STREAM_EXT �Ҳ�ΪVK_QUERY_TYPE_PRIMITIVES_GENERATED_EXT ����index ����Ϊ0
		7.�����render pass instance��һ��subpass�е��ø�������Ӧ��vkCmdBeginQuery* ��������ڸ�subpass�е�ǰ�汻����

		*/

	}



}






NS_TEST_END