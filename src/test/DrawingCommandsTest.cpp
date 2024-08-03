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
    概述 参见1741
    Drawing commands为带有draw的命令，调用该命令会执行绑定的graphics pipeline，所以在该命令执行之前，必须先绑定graphics pipeline以及pipeline中的shader。
    
    每个绘制由0个或多个顶点和0个或多个实例组成，这些实例由设备处理，并进行图元的组装，图元的组装根据VkPipelineInputAssemblyStateCreateInfo的信息进行。
    
    */

    VkPipelineInputAssemblyStateCreateInfo pipelineInputAssemblyStateCreateInfo{
        .sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO,
        .pNext = nullptr,
        .flags = 0,//保留未来使用
        .topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST,// VkPrimitiveTopology值，定义图元的拓扑类型
        .primitiveRestartEnable = VK_TRUE/*
        控制是否将一个特殊的顶点索引值视为重新启动图元组装的开关
        在 (vkCmdDrawIndexed, vkCmdDrawMultiIndexedEXT, 以及 vkCmdDrawIndexedIndirect)中使用
        这个特殊的索引值为:
        0xFFFFFFFF >> 当vkCmdBindIndexBuffer2KHR或者vkCmdBindIndexBuffer的indexType参数为VK_INDEX_TYPE_UINT32时
        0xFFFF >> 当vkCmdBindIndexBuffer2KHR或者vkCmdBindIndexBuffer的indexType参数为 VK_INDEX_TYPE_UINT16时

        不允许进行“list”拓扑的重新组装，除非primitiveTopologyPatchListRestart 或者 primitiveTopologyListRestart 中的一个特性开启
        */
    };
    /*
    VkPipelineInputAssemblyStateCreateInfo有效用法:
    1.如果primitiveTopologyListRestart 特性未开启，且topology 为VK_PRIMITIVE_TOPOLOGY_POINT_LIST, VK_PRIMITIVE_TOPOLOGY_LINE_LIST,
    VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST, VK_PRIMITIVE_TOPOLOGY_LINE_LIST_WITH_ADJACENCY, 或者
    VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST_WITH_ADJACENCY，则primitiveRestartEnable 必须为VK_FALSE。
    2.如果primitiveTopologyPatchListRestart 特性未开启，且topology 为VK_PRIMITIVE_TOPOLOGY_PATCH_LIST，则primitiveRestartEnable 必须为VK_FALSE。
    3.如果geometryShader 特性未开启，则topology 不能为VK_PRIMITIVE_TOPOLOGY_LINE_LIST_WITH_ADJACENCY,
    VK_PRIMITIVE_TOPOLOGY_LINE_STRIP_WITH_ADJACENCY,
    VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST_WITH_ADJACENCY 或者
    VK_PRIMITIVE_TOPOLOGY_TRIANGLE_STRIP_WITH_ADJACENCY
    4.如果tessellationShader 特性未开启，则topology 不能为VK_PRIMITIVE_TOPOLOGY_PATCH_LIST。
    5.如果VK_KHR_portability_subset 扩展被启用，且VkPhysicalDevicePortabilitySubsetFeaturesKHR::triangleFans 特性为VK_FALSE，则topology 不能为VK_PRIMITIVE_TOPOLOGY_TRIANGLE_FAN。
    */

    VkCommandBuffer commandBuffer{/*假设这是一个有效的VkCommandBuffer*/ };

    //动态控制是否将一个特殊的顶点索引值视为重新启动图元组装的开关  , 等同于vkCmdSetPrimitiveRestartEnableEXT
    //这个命令在使用shader objects 绘制或者pipeline以动态状态含VK_DYNAMIC_STATE_PRIMITIVE_RESTART_ENABLE创建下有效
	vkCmdSetPrimitiveRestartEnable(commandBuffer, 
        VK_TRUE/*primitiveRestartEnable,控制是否将一个特殊的顶点索引值视为重新启动图元组装的开关,等价于VkPipelineInputAssemblyStateCreateInfo::primitiveRestartEnable */);
    /*
    vkCmdSetPrimitiveRestartEnable有效用法:
    1.以下至少需要有一个开启
           >  extendedDynamicState2 特性开启
           >  shaderObject 特性开启
           >  创建commandBuffer所在的VkInstance的VkApplicationInfo::apiVersion 要大于等于Version 1.3

    */



    // Primitive Topologies  参见1744

}



NS_TEST_END