#include "DrawingCommandsTest.h"
NS_TEST_BEGIN
DrawingCommandsTest::DrawingCommandsTest()
{
}

void DrawingCommandsTest::run()
{
}

DrawingCommandsTest::~DrawingCommandsTest()
{
}

void DrawingCommandsTest::PrimitiveTest()
{
    /*
    ���� �μ�1741
    Drawing commandsΪ����draw��������ø������ִ�а󶨵�graphics pipeline�������ڸ�����ִ��֮ǰ�������Ȱ�graphics pipeline�Լ�pipeline�е�shader��
    
    ÿ��������0�����������0������ʵ����ɣ���Щʵ�����豸����������ͼԪ����װ��ͼԪ����װ����VkPipelineInputAssemblyStateCreateInfo����Ϣ���С�
    
    */

    VkPipelineInputAssemblyStateCreateInfo pipelineInputAssemblyStateCreateInfo{
        .sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO,
        .pNext = nullptr,
        .flags = 0,//����δ��ʹ��
        .topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST,// VkPrimitiveTopologyֵ������ͼԪ����������
        .primitiveRestartEnable = VK_TRUE/*
        �����Ƿ�һ������Ķ�������ֵ��Ϊ��������ͼԪ��װ�Ŀ���
        �� (vkCmdDrawIndexed, vkCmdDrawMultiIndexedEXT, �Լ� vkCmdDrawIndexedIndirect)��ʹ��
        ������������ֵΪ:
        0xFFFFFFFF >> ��vkCmdBindIndexBuffer2KHR����vkCmdBindIndexBuffer��indexType����ΪVK_INDEX_TYPE_UINT32ʱ
        0xFFFF >> ��vkCmdBindIndexBuffer2KHR����vkCmdBindIndexBuffer��indexType����Ϊ VK_INDEX_TYPE_UINT16ʱ

        ��������С�list�����˵�������װ������primitiveTopologyPatchListRestart ���� primitiveTopologyListRestart �е�һ�����Կ���
        */
    };
    /*
    VkPipelineInputAssemblyStateCreateInfo��Ч�÷�:
    1.���primitiveTopologyListRestart ����δ��������topology ΪVK_PRIMITIVE_TOPOLOGY_POINT_LIST, VK_PRIMITIVE_TOPOLOGY_LINE_LIST,
    VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST, VK_PRIMITIVE_TOPOLOGY_LINE_LIST_WITH_ADJACENCY, ����
    VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST_WITH_ADJACENCY����primitiveRestartEnable ����ΪVK_FALSE��
    2.���primitiveTopologyPatchListRestart ����δ��������topology ΪVK_PRIMITIVE_TOPOLOGY_PATCH_LIST����primitiveRestartEnable ����ΪVK_FALSE��
    3.���geometryShader ����δ��������topology ����ΪVK_PRIMITIVE_TOPOLOGY_LINE_LIST_WITH_ADJACENCY,
    VK_PRIMITIVE_TOPOLOGY_LINE_STRIP_WITH_ADJACENCY,
    VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST_WITH_ADJACENCY ����
    VK_PRIMITIVE_TOPOLOGY_TRIANGLE_STRIP_WITH_ADJACENCY
    4.���tessellationShader ����δ��������topology ����ΪVK_PRIMITIVE_TOPOLOGY_PATCH_LIST��
    5.���VK_KHR_portability_subset ��չ�����ã���VkPhysicalDevicePortabilitySubsetFeaturesKHR::triangleFans ����ΪVK_FALSE����topology ����ΪVK_PRIMITIVE_TOPOLOGY_TRIANGLE_FAN��
    */

    VkCommandBuffer commandBuffer{/*��������һ����Ч��VkCommandBuffer*/ };

    //��̬�����Ƿ�һ������Ķ�������ֵ��Ϊ��������ͼԪ��װ�Ŀ���  , ��ͬ��vkCmdSetPrimitiveRestartEnableEXT
    //���������ʹ��shader objects ���ƻ���pipeline�Զ�̬״̬��VK_DYNAMIC_STATE_PRIMITIVE_RESTART_ENABLE��������Ч
	vkCmdSetPrimitiveRestartEnable(commandBuffer, 
        VK_TRUE/*primitiveRestartEnable,�����Ƿ�һ������Ķ�������ֵ��Ϊ��������ͼԪ��װ�Ŀ���,�ȼ���VkPipelineInputAssemblyStateCreateInfo::primitiveRestartEnable */);
    /*
    vkCmdSetPrimitiveRestartEnable��Ч�÷�:
    1.����������Ҫ��һ������
           >  extendedDynamicState2 ���Կ���
           >  shaderObject ���Կ���
           >  ����commandBuffer���ڵ�VkInstance��VkApplicationInfo::apiVersion Ҫ���ڵ���Version 1.3

    */



    // Primitive Topologies  �μ�1744

}



NS_TEST_END