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
		1/*query type�ض������������query typeΪVK_QUERY_TYPE_TRANSFORM_FEEDBACK_STREAM_EXT ���� VK_QUERY_TYPE_PRIMITIVES_GENERATED_EXT�������������ʾvertex stream*/);//
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


	//��ѯ���query����Ĵ洢�Ų���״̬����Լ�query��ֵ�������������Ϣ  ��p1563
	//��ȡ��ѯ���
	{
		VkQueryResultStatusKHR resultStatus{};
		/*
		VkQueryResultStatusKHR
        VK_QUERY_RESULT_STATUS_NOT_READY_KHR:  ָ��query�Ľ����������Ч��
        VK_QUERY_RESULT_STATUS_ERROR_KHR:  ָ��������û����ȫ�ɹ�
        VK_QUERY_RESULT_STATUS_COMPLETE_KHR:  ָ��������ȫ�ɹ���query�������Ч��
        VK_QUERY_RESULT_STATUS_INSUFFICIENT_BITSTREAM_BUFFER_RANGE_KHR:  ָ��video encode ����û����ȫ�ɹ���ԭ��Ϊdestination video bitstream buffer�����󣬲�������encoded bitstream data
		*/


		VkQueryResultFlagBits queryResultFlagBits = VkQueryResultFlagBits::VK_QUERY_RESULT_WAIT_BIT;
		/*
		VkQueryResultFlagBits:
		VK_QUERY_RESULT_64_BIT:  ָ���������64-bit �޷���������д�����û�����ã�����32-bit �޷���������д
        VK_QUERY_RESULT_WAIT_BIT:  ָ��vulkan���ȴ�ÿ��query�Ľ����Ч���ȥ��ȡ  
        VK_QUERY_RESULT_WITH_AVAILABILITY_BIT:  ָ��query�������availability status
        VK_QUERY_RESULT_PARTIAL_BIT:  ָ�������ز��ֽ��
        VK_QUERY_RESULT_WITH_STATUS_BIT_KHR:  ָ����󷵻صĽ��ֵΪVkQueryResultStatusKHR���ͣ��μ� result status query p1602
		*/

		std::vector<uint64_t> data{};//���صĽ���ڴ��Ų���p1564
		vkGetQueryPoolResults(device, validQueryPool, 0/*��ȡ�ĵ�һ��query������*/, 1/*��ȡ��query������*/, 
			sizeof(uint64_t) * data.size()/*pData���ֽڴ�С*/, data.data()/*pData �����Ҫд��Ľ������*/,
			sizeof(uint64_t) /*pData��ÿ������query������ֽڲ���*/, queryResultFlagBits/* VkQueryResultFlagBitsλ���룬ָ�������η���*/);
		/*
		vkGetQueryPoolResults��Ч�÷�:
		1.firstQuery ����С��queryPool��queries������
		2.firstQuery + queryCount����С�ڵ���queryPool��queries������
		3.���queryCount ����1��stride����Ϊ0
		4.�������queryPool�� queryType ΪVK_QUERY_TYPE_TIMESTAMP��flags���ܰ���VK_QUERY_RESULT_PARTIAL_BIT
		5.�������queryPool�� queryType ΪVK_QUERY_TYPE_PERFORMANCE_QUERY_KHR����1��flags���ܰ���VK_QUERY_RESULT_WITH_AVAILABILITY_BIT, VK_QUERY_RESULT_WITH_STATUS_BIT_KHR, VK_QUERY_RESULT_PARTIAL_BIT, ���� VK_QUERY_RESULT_64_BIT
																				 ��2��queryPool�����ͨ��vkGetPhysicalDeviceQueueFamilyPerformanceQueryPassesKHR���û�õ�ÿ��pass��¼һ��
		6.�������queryPool�� queryType ΪVK_QUERY_TYPE_RESULT_STATUS_ONLY_KHR��flags�������VK_QUERY_RESULT_WITH_STATUS_BIT_KHR
		7.���flags����VK_QUERY_RESULT_WITH_STATUS_BIT_KHR����flags���ܰ���VK_QUERY_RESULT_WITH_AVAILABILITY_BIT
		8.�������ʹ�õ�queries������δ��ʼ����
		9.���flags ��û������VK_QUERY_RESULT_64_BIT���Ҵ���queryPool�� queryType ΪVK_QUERY_TYPE_PERFORMANCE_QUERY_KHR����pData�Ĵ�С�Լ�stride������4�ı���
		10.���flags ��������VK_QUERY_RESULT_64_BIT����pData�Ĵ�С�Լ�stride������8�ı���
		11.���flags��û������VK_QUERY_RESULT_WITH_AVAILABILITY_BIT��stride�����㹻���������ܹ�����query�������ı�ʾavailability ���� status���޷���������
		12.�������queryPool�� queryType ΪVK_QUERY_TYPE_PERFORMANCE_QUERY_KHR����1��pData�Ĵ�С�Լ�stride������VkPerformanceCounterResultKHR.size�ı���
																				  ��2����stride�����㹻���������ܹ�����VkQueryPoolPerformanceCreateInfoKHR::counterIndexCount * VkPerformanceCounterResultKHR.size ���ֽڴ�С
		13.dataSize�����㹻��������ÿһ��query�Ľ�����μ�p1562 �Բ�ѯ������ڴ���������
		*/


		//����query�����VkBuffer    ͬ���� �����SyncronizationAncCacheControl�½ڣ�������transfer����
		vkCmdCopyQueryPoolResults(commandBuffer, validQueryPool, 0/*��ȡ�ĵ�һ��query������*/, 1/*��ȡ��query������*/, 
						VkBuffer{/*��������һ����Ч��VkBuffer*/ }/*���ɻ�ȡ��query���ֵ��VkBuffer*/, 0/*dstBuffer��ƫ��*/,
						sizeof(uint64_t)/*dstBuffer��ÿ������query������ֽڲ���*/, queryResultFlagBits/* VkQueryResultFlagBitsλ���룬ָ�������η���*/);
		/*
		vkCmdCopyQueryPoolResults��Ч�÷�:
		1.firstQuery ����С��queryPool��queries������
		2.firstQuery + queryCount����С�ڵ���queryPool��queries������
		3.���queryCount ����1��stride����Ϊ0
		4.�������queryPool�� queryType ΪVK_QUERY_TYPE_TIMESTAMP��flags���ܰ���VK_QUERY_RESULT_PARTIAL_BIT
		5.�������queryPool�� queryType ΪVK_QUERY_TYPE_PERFORMANCE_QUERY_KHR����1��flags���ܰ���VK_QUERY_RESULT_WITH_AVAILABILITY_BIT, VK_QUERY_RESULT_WITH_STATUS_BIT_KHR, VK_QUERY_RESULT_PARTIAL_BIT, ���� VK_QUERY_RESULT_64_BIT
																				 ��2��queryPool�����ͨ��vkGetPhysicalDeviceQueueFamilyPerformanceQueryPassesKHR���û�õ�ÿ��pass��¼һ��
		6.�������queryPool�� queryType ΪVK_QUERY_TYPE_RESULT_STATUS_ONLY_KHR��flags�������VK_QUERY_RESULT_WITH_STATUS_BIT_KHR
		7.���flags����VK_QUERY_RESULT_WITH_STATUS_BIT_KHR����flags���ܰ���VK_QUERY_RESULT_WITH_AVAILABILITY_BIT
		8.�������ִ��ʱʹ�õ�queries������δ��ʼ����
		9.dstOffset����С��dstBuffer�Ĵ�С
		10.���flags ��û������VK_QUERY_RESULT_64_BIT����dstOffset �Լ� stride������4�ı���
		11.���flags ��������VK_QUERY_RESULT_64_BIT����dstOffset �Լ�stride������8�ı���
		12.dstBuffer�������㹻��Ŀռ䣬��dstOffset��ʼ���ܹ�����ÿһ��query�Ľ��,�μ�p1562 �Բ�ѯ������ڴ���������
		13.dstBuffer������VK_BUFFER_USAGE_TRANSFER_DST_BIT ����
		14.���dstBuffer�� non-sparse�ģ���dstBuffer�����Ѿ��󶨵�һ�������������ĵ�����VkDeviceMemory��
		15.�������queryPool�� queryType ΪVK_QUERY_TYPE_PERFORMANCE_QUERY_KHR����VkPhysicalDevicePerformanceQueryPropertiesKHR::allowCommandBufferQueryCopies ����ΪVK_TRUE
		16.�������queryPool�� queryType ΪVK_QUERY_TYPE_PERFORMANCE_QUERY_INTEL������ʹ�ø������query���
		17.�������ʹ�õ�����queries�����Ǽ���ģ��ұ����ڸ�����ǰ�ĵ��ú��Ϊ��Ч��
	
		*/
	}



	//Occlusion Queries  
	/*
		������ѯһ�������������У�ͨ��per-fragment tests�Ĳ������������
		��������� VK_QUERY_CONTROL_PRECISE_BIT����һ������ֻ��Ҫ�ж���û�в�����ͨ�����Ե�����������Ҫ�����ж��ٸ�������ͨ�����ԣ�����Ҫ����
	*/ 


	// Pipeline Statistics Queries
	{
		//Pipeline statistics queries ����Ӧ�ò���ָ��VkPipeline��һ��contours��Ϣ���Ƿ��ܲ�ѯ�μ�VkPhysicalDeviceFeatures.pipelineStatisticsQuery ,VkQueryPoolCreateInfo::pipelineStatistics ���� VkCommandBufferInheritanceInfo::pipelineStatistics��ָ��Ҫ������ͳ����Ϣ


		VkQueryPipelineStatisticFlagBits queryPipelineStatisticFlagBits = VkQueryPipelineStatisticFlagBits::VK_QUERY_PIPELINE_STATISTIC_VERTEX_SHADER_INVOCATIONS_BIT;
		/*
		VkQueryPipelineStatisticFlagBits:

		
		VK_QUERY_PIPELINE_STATISTIC_INPUT_ASSEMBLY_VERTICES_BIT:   ָ��pool�����queries��ͳ������װ��׶δ���Ķ������������Ӧ�ڲ�������ͼԪ����Ҳ�ᱻͳ�ơ�
        VK_QUERY_PIPELINE_STATISTIC_INPUT_ASSEMBLY_PRIMITIVES_BIT:   ָ��pool�����queries��ͳ������װ��׶δ����ͼԪ�������primitive restart�������½���ͼԪ���˲������ͳ�ơ���������ͼԪ����Ҳ�ᱻͳ�ơ�
		VK_QUERY_PIPELINE_STATISTIC_VERTEX_SHADER_INVOCATIONS_BIT:    ָ��pool�����queries��ͳ��vertex shader invocations����������vertex shader�����õĴ�������������ֵ����ÿ�ε���vertex shader�����
        VK_QUERY_PIPELINE_STATISTIC_GEOMETRY_SHADER_INVOCATIONS_BIT:   ָ��pool�����queries��ͳ��geometry shader invocations����������geometry shader�����õĴ�������������ֵ����ÿ�ε���geometry shader�����������instanced geometry shader����������ֵ����ÿ������instanced geometry shader ���ú����
        VK_QUERY_PIPELINE_STATISTIC_GEOMETRY_SHADER_PRIMITIVES_BIT:    ָ��pool�����queries��ͳ��geometry shader ������ͼԪ����������������ֵ����ÿ��geometry shader����һ��ͼԪ�������ʹ��SPIR-V ָ�� OpEndPrimitive ���� OpEndStreamPrimitive���½���ͼԪ���˲���Ӱ���������ֵ
        VK_QUERY_PIPELINE_STATISTIC_CLIPPING_INVOCATIONS_BIT:  ָ��pool�����queries��ͳ��pipeline��Primitive Clipping�׶δ����ͼԪ����������������ֵ����ÿ��ͼԪ���� primitive clipping�׶ε�ʱ�����
        VK_QUERY_PIPELINE_STATISTIC_CLIPPING_PRIMITIVES_BIT:   ָ��pool�����queries��ͳ��pipeline��Primitive Clipping�׶������ͼԪ����������������ֵ����ÿ��ͼԪͨ�� primitive clipping�׶ε�ʱ�����
        VK_QUERY_PIPELINE_STATISTIC_FRAGMENT_SHADER_INVOCATIONS_BIT:   ָ��pool�����queries��ͳ��fragment shader invocations����������fragment shader�����õĴ�������������ֵ����ÿ�ε���fragment shader����� 
        VK_QUERY_PIPELINE_STATISTIC_TESSELLATION_CONTROL_SHADER_PATCHES_BIT:   ָ��pool�����queries��ͳ��tessellation control shader�����patches����������������ֵ����ÿ�ε���tessellation control shader����patch����� 
        VK_QUERY_PIPELINE_STATISTIC_TESSELLATION_EVALUATION_SHADER_INVOCATIONS_BIT:    ָ��pool�����queries��ͳ��tessellation evaluation shader invocations����������tessellation evaluation shader�����õĴ�������������ֵ����ÿ�ε���tessellation evaluation shader�����   
        VK_QUERY_PIPELINE_STATISTIC_COMPUTE_SHADER_INVOCATIONS_BIT:  ָ��pool�����queries��ͳ��compute shader invocations����������compute shader�����õĴ�������������ֵ����ÿ�ε���compute shader�����     
        VK_QUERY_PIPELINE_STATISTIC_TASK_SHADER_INVOCATIONS_BIT_EXT:   ָ��pool�����queries��ͳ��task shader invocations����������task shader�����õĴ�������������ֵ����ÿ�ε���task shader�����     
        VK_QUERY_PIPELINE_STATISTIC_MESH_SHADER_INVOCATIONS_BIT_EXT:   ָ��pool�����queries��ͳ��mesh shader invocations����������mesh shader�����õĴ�������������ֵ����ÿ�ε���mesh shader�����     
		*/


	}



	//Timestamp Queries  �μ�p1576
	{
		//Timestamps ����Ӧ�ü�ʱ����ִ�е�ʱ��  ��ʹ�� vkCmdBeginQuery ���� vkCmdEndQuery��ֱ��ͨ��vkGetQueryPoolResults ����vkCmdCopyQueryPoolResults ��ʱ�����ã�Ȼ��host�˼���Ƚϣ�������Ϊ��λ

		//��ʱ�����Ϣд��query pool   ��ͬ��vkCmdWriteTimestamp2KHR
		vkCmdWriteTimestamp2(commandBuffer, VK_PIPELINE_STAGE_2_VERTEX_INPUT_BIT/*ָ��pipeline�׶�*/, validQueryPool, 0/*ָ��д��ʱ�����query����*/);
		/*
		vkCmdWriteTimestamp2��Ч�÷�:
		1.���geometryShader ����û�п�����stage���ܰ���VK_PIPELINE_STAGE_2_GEOMETRY_SHADER_BIT
		2.���tessellationShader ����û�п�����stage���ܰ���VK_PIPELINE_STAGE_2_TESSELLATION_CONTROL_SHADER_BIT �� VK_PIPELINE_STAGE_2_TESSELLATION_EVALUATION_SHADER_BIT
		3.���conditionalRendering ����û�п�����stage���ܰ���VK_PIPELINE_STAGE_2_CONDITIONAL_RENDERING_BIT_EXT
		4.���fragmentDensityMap ����û�п�����stage���ܰ���VK_PIPELINE_STAGE_2_FRAGMENT_DENSITY_PROCESS_BIT_EXT
		5.���transformFeedback ����û�п�����stage���ܰ���VK_PIPELINE_STAGE_2_TRANSFORM_FEEDBACK_BIT_EXT
		6.���meshShader ����û�п�����stage���ܰ���VK_PIPELINE_STAGE_2_MESH_SHADER_BIT_EXT
		7.���taskShader ����û�п�����stage���ܰ���VK_PIPELINE_STAGE_2_TASK_SHADER_BIT_EXT
		8.���shadingRateImage ���� attachmentFragmentShadingRateû��һ����������stage���ܰ���VK_PIPELINE_STAGE_2_FRAGMENT_SHADING_RATE_ATTACHMENT_BIT_KHR
		9.���subpassShading ����û�п�����stage���ܰ���VK_PIPELINE_STAGE_2_SUBPASS_SHADER_BIT_HUAWEI
		10.���invocationMask ����û�п�����stage���ܰ���VK_PIPELINE_STAGE_2_INVOCATION_MASK_BIT_HUAWEI
		11.���VK_NV_ray_tracing ��չ ���� rayTracingPipeline ����û��һ����������stage���ܰ���VK_PIPELINE_STAGE_2_RAY_TRACING_SHADER_BIT_KHR
		12.synchronization2 ���Ա��뿪��
		13.stageֻ�ܰ���һ�������Ľ׶�
		14.stage�������һ��commandBuffer���ڵ�VkCommandPool����ʱ�Ķ�����֧�ֵĽ׶�
		15.queryPool ������queryType ΪVK_QUERY_TYPE_TIMESTAMP ����
		16.commandBuffer���ڵ�VkCommandPool����ʱ�Ķ��������֧��һ�������timestampValidBits
		17.query ����С��queryPool��queries������
		18.��ǰ����ʹ�õ�queris����ʱ��Ч��
		19.���������vkCmdWriteTimestamp2 ��һ�� render pass instance�е��ã���query�͵�ǰsubpass��view mask�����õ�λ���ܺͱ���С�ڻ����queryPool�е�queries����
		*/


		vkCmdWriteTimestamp(commandBuffer, VK_PIPELINE_STAGE_VERTEX_INPUT_BIT/*ָ��pipeline�׶�*/, validQueryPool, 0/*ָ��д��ʱ�����query����*/);
		/*
		vkCmdWriteTimestamp��Ч�÷�:
		1.pipelineStage����Ϊһ��commandBuffer���ڵ�VkCommandPool����ʱ�Ķ�����֧�ֵĽ׶�
		2.���geometryShader ����û�п�����pipelineStage���ܰ���VK_PIPELINE_STAGE_GEOMETRY_SHADER_BIT
		3.���tessellationShader ����û�п�����pipelineStage���ܰ���VK_PIPELINE_STAGE_TESSELLATION_CONTROL_SHADER_BIT �� VK_PIPELINE_STAGE_TESSELLATION_EVALUATION_SHADER_BIT
		4.���conditionalRendering ����û�п�����pipelineStage���ܰ���VK_PIPELINE_STAGE_CONDITIONAL_RENDERING_BIT_EXT
		5.���fragmentDensityMap ����û�п�����pipelineStage���ܰ���VK_PIPELINE_STAGE_FRAGMENT_DENSITY_PROCESS_BIT_EXT
		6.���transformFeedback ����û�п�����pipelineStage���ܰ���VK_PIPELINE_STAGE_TRANSFORM_FEEDBACK_BIT_EXT
		7.���meshShader ����û�п�����pipelineStage���ܰ���VK_PIPELINE_STAGE_MESH_SHADER_BIT_EXT
		8.���taskShader ����û�п�����pipelineStage���ܰ���VK_PIPELINE_STAGE_TASK_SHADER_BIT_EXT
		9.���shadingRateImage ���� attachmentFragmentShadingRateû��һ����������pipelineStage���ܰ���VK_PIPELINE_STAGE_FRAGMENT_SHADING_RATE_ATTACHMENT_BIT_KHR
		10.���synchronization2 δ��������pipelineStage���ܰ���VK_PIPELINE_STAGE_NONE
		11.���VK_NV_ray_tracing ��չ ���� rayTracingPipeline ����û��һ����������pipelineStage���ܰ���VK_PIPELINE_STAGE_RAY_TRACING_SHADER_BIT_KHR
		12.queryPool ������queryType ΪVK_QUERY_TYPE_TIMESTAMP ����
		13.commandBuffer���ڵ�VkCommandPool����ʱ�Ķ��������֧��һ�������timestampValidBits
		14.query ����С��queryPool��queries������
		15.��ǰ����ʹ�õ�queris����ʱ��Ч��
		16.���������vkCmdWriteTimestamp ��һ�� render pass instance�е��ã���query�͵�ǰsubpass��view mask�����õ�λ���ܺͱ���С�ڻ����queryPool�е�queries����



		*/
	}



	//Performance Queries �μ�p1584
	{
		//Performance queries�ṩ��Ӧ��һ�����ƻ�ȡ command buffers, render passes, �Լ� commandsִ�е����ܼ�����Ϣ
		//queue�ϵ����ܼ������� vkEnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersKHR.
		//��ѯʹ��vkCmdBeginQuery �Լ� vkCmdEndQuery
		//��ȡ��ѯ���vkGetQueryPoolResults.   ���ΪVkPerformanceCounterResultKHR��ʽ��������ʲô�μ�VkPerformanceCounterKHR::storage

		VkPerformanceCounterResultKHR performanceCounterResultKHR{};
		performanceCounterResultKHR.float32;
		performanceCounterResultKHR.float64;
		performanceCounterResultKHR.int32;
		performanceCounterResultKHR.int64;
		performanceCounterResultKHR.uint32;
		performanceCounterResultKHR.uint64;


		//Profiling Lock
		{
			//profiling lock �����ڽ������ܼ�����ѯ���� vkBeginCommandBufferǰ��ȡ


			VkAcquireProfilingLockInfoKHR acquireProfilingLockInfoKHR{};
			acquireProfilingLockInfoKHR.sType = VK_STRUCTURE_TYPE_ACQUIRE_PROFILING_LOCK_INFO_KHR;
			acquireProfilingLockInfoKHR.pNext = nullptr;
			acquireProfilingLockInfoKHR.flags = 0;//����δ��ʹ��
			acquireProfilingLockInfoKHR.timeout = 1000;//���profiling lock�������Ի�ȡ�Ļ���ָ����ȡ�����ȴ��ĺ����������Ϊ UINT64_MAX����һֱ�ȴ�����ȡΪֹ
			//��ȡprofiling lock
			vkAcquireProfilingLockKHR(device, &acquireProfilingLockInfoKHR);



			//�ͷ�profiling lock
			vkReleaseProfilingLockKHR(device);
		}

	}

	//Transform Feedback Queries �μ�p1587
	//Transform feedback queries ��ѯ����vertex streamʱҪд��ͼԪ�Լ�ʵ��д��ͼԪ������
	//ʹ�� vkCmdBeginQuery �Լ� vkCmdEndQuery,  vkCmdBeginQueryIndexedEXT �Լ� vkCmdEndQueryIndexedEXT

	
	//Primitives Generated Queries �μ�p1587
	//Primitives generated queries ��ѯÿһ�����͵�stream���� transform feedback stage�׶ε�ͼԪ������
	//ʹ�� vkCmdBeginQuery �Լ� vkCmdEndQuery,  vkCmdBeginQueryIndexedEXT �Լ� vkCmdEndQueryIndexedEXT
	//��ȡ vkCmdCopyQueryPoolResults �Լ� vkGetQueryPoolResults


	//Mesh Shader Queries  �μ�p1587
	/*
	Mesh shader queries ��ѯÿһ��mesh shader ������ͼԪ���� fragment shader stage�׶ε�ͼԪ������
	*/

	
	//Intel Performance Queries  �μ�p1588
	{
		//Intel Performance Queries������һ��commands���������ݣ������������ѯ�������ѯ����ֱ�Ӷ�ȡ��ѯ��������Ǵ�������ת��Ϊ�˿ɶ�����Ϣ


		VkInitializePerformanceApiInfoINTEL  initializePerformanceApiInfoINTEL{};
		initializePerformanceApiInfoINTEL.sType = VK_STRUCTURE_TYPE_INITIALIZE_PERFORMANCE_API_INFO_INTEL;
		initializePerformanceApiInfoINTEL.pNext = nullptr;
		initializePerformanceApiInfoINTEL.pUserData = nullptr;//ΪӦ�����ݵ�ָ��
		//����query poolǰ��ʼ��performance query
		vkInitializePerformanceApiINTEL(device, &initializePerformanceApiInfoINTEL);

		//performance query��ѯ������ȡ��performance query�ĳ�ʼ��
		vkUninitializePerformanceApiINTEL(device);

		VkPerformanceParameterTypeINTEL performanceParameterTypeINTEL{};
		performanceParameterTypeINTEL = VkPerformanceParameterTypeINTEL::VK_PERFORMANCE_PARAMETER_TYPE_HW_COUNTERS_SUPPORTED_INTEL;
		/*
		VkPerformanceParameterTypeINTEL
		VK_PERFORMANCE_PARAMETER_TYPE_HW_COUNTERS_SUPPORTED_INTEL:  ָ���������˵���Ƿ����ò���Ӳ��������booleanֵ
		VK_PERFORMANCE_PARAMETER_TYPE_STREAM_MARKER_VALID_BITS_INTEL:  ָ���������˵�����ٱ��ؿ���д��VkPerformanceValueINTEL��32-bits ����ֵ
		*/

		VkPerformanceValueINTEL performanceValueINTEL{};//��ȡ��ѯ����
		performanceValueINTEL.type = VK_PERFORMANCE_VALUE_TYPE_UINT32_INTEL;//ָ�����ص��������͵� VkPerformanceValueTypeINTEL
		/*
		VkPerformanceValueTypeINTEL:
		VK_PERFORMANCE_VALUE_TYPE_UINT32_INTEL:    ָ������ unsigned 32-bit integer���ݵ�data.value32.
		VK_PERFORMANCE_VALUE_TYPE_UINT64_INTEL:    ָ������ unsigned 64-bit integer���ݵ�data.value64.
		VK_PERFORMANCE_VALUE_TYPE_FLOAT_INTEL:    ָ������ floating-point���ݵ�data.valueFloat.
		VK_PERFORMANCE_VALUE_TYPE_BOOL_INTEL:    ָ������ VkBool32 ���ݵ�data.valueBool.
		VK_PERFORMANCE_VALUE_TYPE_STRING_INTEL:    ָ������һ�� null-terminated UTF-8�ַ������ݵ� in data.valueString.
		*/

		performanceValueINTEL.data.value32;//���uint32_t�ķ�������
		performanceValueINTEL.data.value64;//���uint64_t�ķ�������
		performanceValueINTEL.data.valueBool;//���VkBool32�ķ�������
		performanceValueINTEL.data.valueFloat;//���float�ķ�������
		performanceValueINTEL.data.valueString;//���c����ַ���null-terminated UTF-8�ķ�������
		//��ȡ performance query ��ѯ������
		vkGetPerformanceParameterINTEL(device, performanceParameterTypeINTEL, &performanceValueINTEL);



		//VkQueryPoolPerformanceQueryCreateInfoINTEL
		//����ܹ���ӵ� VkQueryPoolCreateInfo.pNext���������ø����͵�query
		VkQueryPoolPerformanceQueryCreateInfoINTEL queryPoolPerformanceQueryCreateInfoINTEL{};
		queryPoolPerformanceQueryCreateInfoINTEL.sType = VK_STRUCTURE_TYPE_QUERY_POOL_PERFORMANCE_QUERY_CREATE_INFO_INTEL;
		queryPoolPerformanceQueryCreateInfoINTEL.pNext = nullptr;
		queryPoolPerformanceQueryCreateInfoINTEL.performanceCountersSampling = VK_QUERY_POOL_SAMPLING_MODE_MANUAL_INTEL;//������β���performance queries��VK_QUERY_POOL_SAMPLING_MODE_MANUAL_INTELָ��Ӧ��ʹ��Ĭ��ģʽ����vkCmdBeginQuery �Լ� vkCmdEndQuery����¼performance����


		VkPerformanceMarkerInfoINTEL performanceMarkerInfoINTEL{};
		performanceMarkerInfoINTEL.sType = VK_STRUCTURE_TYPE_PERFORMANCE_MARKER_INFO_INTEL;
		performanceMarkerInfoINTEL.pNext = nullptr;
		performanceMarkerInfoINTEL.marker = 0;//��¼����ѯ�����һ����͸���ı��ֵ
		//Ϊ�˰�������ѯ�����Ӧ�ó��򷢳�������ض���������������Խ�������õ����������
		vkCmdSetPerformanceMarkerINTEL(commandBuffer, &performanceMarkerInfoINTEL);



		VkPerformanceStreamMarkerInfoINTEL performanceStreamMarkerInfoINTEL{};
		performanceStreamMarkerInfoINTEL.sType = VK_STRUCTURE_TYPE_PERFORMANCE_STREAM_MARKER_INFO_INTEL;
		performanceStreamMarkerInfoINTEL.pNext = nullptr;
		performanceStreamMarkerInfoINTEL.marker = 0;//�ǽ�����¼���ⲿӦ�ó���ʹ�õı����еı��ֵ�����ֵ����ʹ��vkGetPerformanceParameterINTEL����VK_PERFORMANCE_PARAMETER_TYPE_STREAM_MARKER_VALID_BITS_INTEL���ص�ֵ
		/*
		����������ϵͳ�����е�����Ӧ�ó������ɵ����ݼ��е�Ӧ�ó������Ϊʱ����Ǳ�ڵĴ�������������ʶ����Ƶ����Ǻ����õġ�Ϊ�ˣ�Ӧ�ó��������������ǣ���Щ����ǽ����ڸ��پ����ض�������������ض����Ƶ���
		*/
		vkCmdSetPerformanceStreamMarkerINTEL(commandBuffer, &performanceStreamMarkerInfoINTEL);


		VkPerformanceOverrideInfoINTEL performanceOverrideInfoINTEL{};
		performanceOverrideInfoINTEL.sType = VK_STRUCTURE_TYPE_PERFORMANCE_OVERRIDE_INFO_INTEL;
		performanceOverrideInfoINTEL.pNext = nullptr;
		performanceOverrideInfoINTEL.type = VK_PERFORMANCE_OVERRIDE_TYPE_FLUSH_GPU_CACHES_INTEL;/*ָ�����͵� VkPerformanceOverrideTypeINTELֵ
		VkPerformanceOverrideTypeINTEL:
		VK_PERFORMANCE_OVERRIDE_TYPE_NULL_HARDWARE_INTEL:  ��������Ⱦ������Ϊ�ղ���
		VK_PERFORMANCE_OVERRIDE_TYPE_FLUSH_GPU_CACHES_INTEL:  ֹͣ��������ֱ����ǰ���������������ɣ����л��涼��ˢ�²���Ч
		*/
		performanceOverrideInfoINTEL.enable = VK_TRUE;//�����Ƿ�������д���ò���
		performanceOverrideInfoINTEL.parameter = 0;//����д���ÿ�����Ҫ�Ĳ���

		//һЩӦ�ó������ϣ��ʹ�ò�ͬ������������һ�������Ч������д���õ���
		vkCmdSetPerformanceOverrideINTEL(commandBuffer, &performanceOverrideInfoINTEL);

		//�ڽ��������ܲ�ѯ�������������ύ���豸����֮ǰ��Ӧ�ó�������ȡ���������ܲ�ѯ���á�

		VkPerformanceConfigurationINTEL performanceConfigurationINTEL{};

		VkPerformanceConfigurationAcquireInfoINTEL performanceConfigurationAcquireInfoINTEL{};
		performanceConfigurationAcquireInfoINTEL.sType = VK_STRUCTURE_TYPE_PERFORMANCE_CONFIGURATION_ACQUIRE_INFO_INTEL;
		performanceConfigurationAcquireInfoINTEL.pNext = nullptr;
		performanceConfigurationAcquireInfoINTEL.type = VK_PERFORMANCE_CONFIGURATION_TYPE_COMMAND_QUEUE_METRICS_DISCOVERY_ACTIVATED_INTEL;//ָ������ȡ��performance configuration�� VkPerformanceConfigurationTypeINTEL����ֵ
		//��ȡ���ܲ�ѯ����performance configuration
		vkAcquirePerformanceConfigurationINTEL(device, &performanceConfigurationAcquireInfoINTEL, &performanceConfigurationINTEL);


		//����performance configuration
		vkQueueSetPerformanceConfigurationINTEL(VkQueue{/*��������һ����Ч��VkQueue*/ }, performanceConfigurationINTEL);

		//�ͷ�performance configuration
		vkReleasePerformanceConfigurationINTEL(device, performanceConfigurationINTEL);//configuration����������������configuration���Ѿ��ύ��command buffers����pending״̬ǰ�ͷ�

	}

	// Result Status Queries �μ�p1603
	/*
	Result status queries ����Ӧ��ȷ��һ�������Ƿ��Ѿ��ɹ�������ͨ��VkQueryResultStatusKHR ָ��

	�Ƿ�֧�ָò�ѯ�μ� vkGetPhysicalDeviceQueueFamilyProperties2���ص� VkQueueFamilyQueryResultStatusPropertiesKHR::queryResultStatusSupport
	*/

	//Video Encode Feedback Queries �μ�p1603
	{
		//Video encode feedback queries����Ӧ�û�ȡvideo encode operations������ feedback values
		//�Ƿ�֧�ָò�ѯ�μ�  vkGetPhysicalDeviceVideoCapabilitiesKHR���ص�  VkVideoEncodeCapabilitiesKHR::supportedEncodeFeedbackFlags


		//VkQueryPoolVideoEncodeFeedbackCreateInfoKHR
		//��VkQueryPoolCreateInfo.pNext����Ӹýṹ�����øò�ѯ
		VkQueryPoolVideoEncodeFeedbackCreateInfoKHR queryPoolVideoEncodeFeedbackCreateInfoKHR{};
		queryPoolVideoEncodeFeedbackCreateInfoKHR.sType = VK_STRUCTURE_TYPE_MAX_ENUM;//û�ж�����������Ϊ�Ƿ�ֵ
		queryPoolVideoEncodeFeedbackCreateInfoKHR.pNext = nullptr;
		queryPoolVideoEncodeFeedbackCreateInfoKHR.encodeFeedbackFlags = VK_VIDEO_ENCODE_FEEDBACK_BITSTREAM_BUFFER_OFFSET_BIT_KHR;/*�� VkVideoEncodeFeedbackFlagBitsKHR���ֵλ���룬ָ��������Щ video encode feedback values�Ĳ���
		VkVideoEncodeFeedbackFlagBitsKHR:

        VK_VIDEO_ENCODE_FEEDBACK_BITSTREAM_BUFFER_OFFSET_BIT_KHR: ָ���ɳع���Ĳ�ѯ����������Ƶ���������VkVideoEncodeInfoKHR::dstBuffer��ָ����λ��������д��λ�����ݵ������VkVideoEncodeInfoKHR::dstBufferOffset��ָ����ƫ�������ֽ�ƫ����,�������κ���Ƶ����������ĵ�һ����Ƶ�����������ֵ��ʼ��Ϊ�㣬����ζ��λ���������Ǵ�VkVideoEncodeInfoKHR::dstBufferOffset.��ָ����ƫ������ʼд��VkVideoEncodeInfoKHR::dstBuffer��ָ���Ļ�����
        VK_VIDEO_ENCODE_FEEDBACK_BITSTREAM_BYTES_WRITTEN_BIT_KHR: ָ���ɳع���Ĳ�ѯ����������Ƶ�������д�뵽��VkVideoEncodeInfoKHR::dstBuffer.��ָ����λ�����������ֽ���
        VK_VIDEO_ENCODE_FEEDBACK_BITSTREAM_HAS_OVERRIDES_BIT_KHR:  ָ���ɳع���Ĳ�ѯ������һ������ֵ�������д�뵽VkVideoEncodeInfoKHR::dstBuffer��ָ����λ�������������ݰ�������д�Ĳ�����
		*/
	}
}






NS_TEST_END