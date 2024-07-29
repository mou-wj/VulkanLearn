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
	��ѯͨ������������п���:  ����Ĺ���������p1544,�����̽����� ��ѯ--> pool�洢��� -->  ���������ȡ���  
	vkCmdBeginQuery, vkCmdEndQuery,
	vkCmdBeginQueryIndexedEXT, vkCmdEndQueryIndexedEXT, vkCmdResetQueryPool,
	vkCmdCopyQueryPoolResults, vkCmdWriteTimestamp2, �Լ� vkCmdWriteTimestamp.

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



}






NS_TEST_END