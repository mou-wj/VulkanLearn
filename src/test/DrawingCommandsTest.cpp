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
    {
        //Primitive topology决定了如何将连续的顶点组织成图元，并决定了在图形管道开始时使用的图元的类型,后续可能在tessellation 或者 geometry 阶段中改变图元类型，在mesh shading中有效的图元在mesh shader中定义。
        VkPrimitiveTopology primitiveTopology = VkPrimitiveTopology::VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
        /*
        VkPrimitiveTopology:

        VK_PRIMITIVE_TOPOLOGY_POINT_LIST:   指明一系列离散的点图元.
        VK_PRIMITIVE_TOPOLOGY_LINE_LIST:   指明一系列离散的线图元.
        VK_PRIMITIVE_TOPOLOGY_LINE_STRIP:   指明一系列相连的共享一个顶点的线图元
        VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST:   指明一系列离散的三角形图元.
        VK_PRIMITIVE_TOPOLOGY_TRIANGLE_STRIP:   指明一系列相连的共享一条边的三角形图元.
        VK_PRIMITIVE_TOPOLOGY_TRIANGLE_FAN:   指明一系列相连的共享一个共同顶点的三角形图元，如果VK_KHR_portability_subset拓展开启，且VkPhysicalDevicePortabilitySubsetFeaturesKHR::triangleFans为VK_FALSE，
                则不支持改图元类型，即VK_PRIMITIVE_TOPOLOGY_TRIANGLE_FAN 不能使用
        VK_PRIMITIVE_TOPOLOGY_LINE_LIST_WITH_ADJACENCY:   指明一系列离散的带邻接关系的线图元
        VK_PRIMITIVE_TOPOLOGY_LINE_STRIP_WITH_ADJACENCY:   指明一系列相连的带邻接关系的线图元，即连续的线图元间共享三个顶点
        VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST_WITH_ADJACENCY:   指明一系列离散的带邻接关系的三角形图元
        VK_PRIMITIVE_TOPOLOGY_TRIANGLE_STRIP_WITH_ADJACENCY:   指明相连的带邻接关系的三角形图元，即连续的三角形图元间共享一条边
        VK_PRIMITIVE_TOPOLOGY_PATCH_LIST:   指明离散的 patch 图元.

        
        邻接关系不会影响图元类型，只是这些邻接关系数据会在geometry shader中使用
        */


        //动态设置图元类型   等价于vkCmdSetPrimitiveTopologyEXT，该命令只有在VkPipelineDynamicStateCreateInfo::pDynamicStates中动态开启VK_DYNAMIC_STATE_PRIMITIVE_TOPOLOGY了才有效，否则将使用VkPipelineInputAssemblyStateCreateInfo::topology
        vkCmdSetPrimitiveTopology(commandBuffer, VK_PRIMITIVE_TOPOLOGY_LINE_LIST);
        /*
        vkCmdSetPrimitiveTopology有效用法:
        1.以下至少需要有一个开启
               >  extendedDynamicState 特性开启
               >  shaderObject 特性开启
               >  创建commandBuffer所在的VkInstance的VkApplicationInfo::apiVersion 要大于等于Version 1.3
        
        */




        //Topology Class 拓扑类型表   参见p1747 

        // Point Lists 点列表，类型VK_PRIMITIVE_TOPOLOGY_POINT_LIST ，每个连续的点定义一个顶点，总共图元数vertexCount  参见p1747 

        //  Line Lists 线列表，类型 VK_PRIMITIVE_TOPOLOGY_LINE_LIST ，每一对连续的点定义一条线，总共图元数vertexCount / 2 . 参见p1748    涉及provokingVertexMode

        //Line Strips 线列表，类型 VK_PRIMITIVE_TOPOLOGY_LINE_STRIP ，每一个点和其后续一个点定义一条线，总共图元数(0,vertexCount-1). 参见p1748
    
        //Triangle Lists 三角形列表，类型 VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST ，每连续的一组三个顶点组成一个三角形，总共图元数vertexCount / 3. 参见p1749   涉及provokingVertexMode
        
        //Triangle Strips 三角形列表，类型 VK_PRIMITIVE_TOPOLOGY_TRIANGLE_STRIP ，每个点和后续两个顶点组成一个三角形，总共图元数vertexCount - 2 . 参见p1750   涉及provokingVertexMode
    
        // Triangle Fans 三角形列表，类型 VK_PRIMITIVE_TOPOLOGY_TRIANGLE_FAN ，所有三角形围绕一个公共顶点，公共顶点为V0，总共图元数vertexCount - 2 . 参见p1751   涉及provokingVertexMode

        // Line Lists With Adjacency线列表，类型  VK_PRIMITIVE_TOPOLOGY_LINE_LIST_WITH_ADJACENCY ，每连续的一组四个顶点组成一条线以及其邻接数据，中间两个点为线图元，首尾两个点为邻接数据，总共图元数vertexCount / 4. 参见p1751   涉及provokingVertexMode
    
        //Line Strips With Adjacency线列表，类型  VK_PRIMITIVE_TOPOLOGY_LINE_STRIP_WITH_ADJACENCY ，所有点的中间每一个点和其后续一个点定义一条线，所有顶点的首尾两个点为线图元，总共图元数vertexCount - 3. 参见p1752   涉及provokingVertexMode
    
        //Triangle Lists With Adjacency 三角形列表，类型  VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST_WITH_ADJACENCY ，每连续的一组六个顶点组成一个三角形以及其邻接数据，第一个，第三个，第五个点组成三角形，其余三个点为邻接数据，总共图元数vertexCount / 6. 参见p1752   涉及provokingVertexMode
    
        //Triangle Strips With Adjacency 三角形列表，类型  VK_PRIMITIVE_TOPOLOGY_TRIANGLE_STRIP_WITH_ADJACENCY ，每一个点和其后续五个点定义一个三角形，第一个，第三个，第五个点组成三角形，其余三个点为邻接数据，总共图元数(vertexCount - 4) / 2. 参见p1752   涉及provokingVertexMode
    
        //Patch Lists patch列表，类型  VK_PRIMITIVE_TOPOLOGY_PATCH_LIST ，每连续的一组 m 个顶点组成一个patch，m 由 VkPipelineTessellationStateCreateInfo::patchControlPoints指定，总共图元数vertexCount / m. 参见p1755 
    }



    //Primitive Order  图元的顺序  参见p1756


    // Programmable Primitive Shading 可编程图元绘制  参见p1756
    {
        //一旦完成图元组装，pipeline便进入vertex shader阶段，如果绘制为multiple instances,则对于每个instance，这些图元会重复发送到vertex shader阶段，该阶段会接受来自图元装配阶段的每个顶点都含有的两个输入参数vertexIndex 以及 instanceIndex
        /*
        非索引绘制命令:vkCmdDraw ， vkCmdDrawIndirect， vkCmdDrawIndirectCount ，vkCmdDrawIndirectCountKHR， vkCmdDrawIndirectCountAMD，vkCmdDrawMultiEXT
        索引绘制命令: vkCmdDrawIndexed, vkCmdDrawIndexedIndirect, vkCmdDrawIndexedIndirectCount, vkCmdDrawIndexedIndirectCountKHR, vkCmdDrawIndexedIndirectCountAMD, vkCmdDrawMultiIndexedEXT
        */


        VkIndexType indexType = VK_INDEX_TYPE_UINT16;//指定索引的类型以及字节大小
        /*
        VkIndexType:
        VK_INDEX_TYPE_UINT16:    指明索引为16-bit unsigned integer值.
        VK_INDEX_TYPE_UINT32:    指明索引为32-bit unsigned integer值.
        VK_INDEX_TYPE_NONE_KHR:    指明没有提供索引数据.
        VK_INDEX_TYPE_UINT8_KHR:    指明索引为8-bit unsigned integer值.

        
        */

        //绑定索引缓冲区
        vkCmdBindIndexBuffer(commandBuffer, VkBuffer{/*假设这是一个有效的VkBuffer，表示顶点索引缓存区*/ }/*buffer,指定要绑定的buffer*/,
            0/*offset,用于索引缓冲区索引地址计算的起始字节偏移量*/, indexType/*indexType，指明索引的类型和大小*/);
        /*
        vkCmdBindIndexBuffer有效用法:
        1.offset必须小于buffer的大小
        2.offset + buffer内部VkDeviceMemory的基地址，必须是indexType指明的字节大小的整数倍
        3.buffer必须以VK_BUFFER_USAGE_INDEX_BUFFER_BIT 创建
        4.如果buffer是non-sparse的，则其必须已经绑定到完整连续单独的VkDeviceMemory上了
        5.indexType不能为VK_INDEX_TYPE_NONE_KHR
        6.如果indexType为VK_INDEX_TYPE_UINT8_KHR，则indexTypeUint8 特性必须开启
        7.如果maintenance6 没有开启，则buffer不能为VK_NULL_HANDLE
        8.如果buffer为VK_NULL_HANDLE，则offset必须为0
        */


        //绑定索引缓冲区以及其大小
        vkCmdBindIndexBuffer2KHR(commandBuffer, VkBuffer{/*假设这是一个有效的VkBuffer，表示顶点索引缓存区*/ }/*buffer,指定要绑定的buffer*/,
            0/*offset,用于索引缓冲区索引地址计算的起始字节偏移量*/,1/*size,为buffer中要绑定的内存大小*/, indexType/*indexType，指明索引的类型和大小*/);
        /*
        vkCmdBindIndexBuffer2KHR有效用法:
        1.offset必须小于buffer的大小
        2.offset + buffer内部VkDeviceMemory的基地址，必须是indexType指明的字节大小的整数倍
        3.buffer必须以VK_BUFFER_USAGE_INDEX_BUFFER_BIT 创建
        4.如果buffer是non-sparse的，则其必须已经绑定到完整连续单独的VkDeviceMemory上了
        5.indexType不能为VK_INDEX_TYPE_NONE_KHR
        6.如果indexType为VK_INDEX_TYPE_UINT8_KHR，则indexTypeUint8 特性必须开启
        7.如果maintenance6 没有开启，则buffer不能为VK_NULL_HANDLE
        8.如果buffer为VK_NULL_HANDLE，则offset必须为0
        9.如果size不为VK_WHOLE_SIZE,则（1）size必须为indexType指定的字节大小的整数倍
                                      （2）offset + size必须小于buffer的大小
        */



        //记录一个非索引绘制命令，  当执行这个命令，pipeline将以顶点索引为firstVertex开始组装vertexCount个顶点，以firstInstance开始绘制instanceCount个instance
        vkCmdDraw(commandBuffer, 1/*vertexCount,指明要绘制的顶点个数*/, 1/*instanceCount,指明要绘制的instances个数*/,
            0/*firstVertex,指明要绘制的第一个顶点的索引*/, 0/*firstInstance,指明要绘制的第一个instance的ID*/);
        /*
        vkCmdDraw有效用法:
        1.如果一个VkSampler以其magFilter或者minFilter等于VK_FILTER_LINEAR创建，则（1）如果reductionMode为VK_SAMPLER_REDUCTION_MODE_WEIGHTED_AVERAGE，如果用于采样一个VkImageView作为该命令的结果的compareEnable为VK_FALSE，则该image view的format features必须包含VK_FORMAT_FEATURE_SAMPLED_IMAGE_FILTER_LINEAR_BIT
                                                                                 （2）如果reductionMode为VK_SAMPLER_REDUCTION_MODE_MIN 或者VK_SAMPLER_REDUCTION_MODE_MAX之一 用于采样一个VkImageView作为该命令的结果，则该image view的format features必须包含VK_FORMAT_FEATURE_SAMPLED_IMAGE_FILTER_MINMAX_BIT
        2.如果一个VkSampler以其magFilter或者minFilter等于VK_SAMPLER_MIPMAP_MODE_LINEAR创建，则（1）如果reductionMode为VK_SAMPLER_REDUCTION_MODE_WEIGHTED_AVERAGE，如果用于采样一个VkImageView作为该命令的结果的compareEnable为VK_FALSE，则该image view的format features必须包含VK_FORMAT_FEATURE_SAMPLED_IMAGE_FILTER_LINEAR_BIT
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

        */


    }

}



NS_TEST_END