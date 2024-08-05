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
    {
        //Primitive topology��������ν������Ķ�����֯��ͼԪ������������ͼ�ιܵ���ʼʱʹ�õ�ͼԪ������,����������tessellation ���� geometry �׶��иı�ͼԪ���ͣ���mesh shading����Ч��ͼԪ��mesh shader�ж��塣
        VkPrimitiveTopology primitiveTopology = VkPrimitiveTopology::VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
        /*
        VkPrimitiveTopology:

        VK_PRIMITIVE_TOPOLOGY_POINT_LIST:   ָ��һϵ����ɢ�ĵ�ͼԪ.
        VK_PRIMITIVE_TOPOLOGY_LINE_LIST:   ָ��һϵ����ɢ����ͼԪ.
        VK_PRIMITIVE_TOPOLOGY_LINE_STRIP:   ָ��һϵ�������Ĺ���һ���������ͼԪ
        VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST:   ָ��һϵ����ɢ��������ͼԪ.
        VK_PRIMITIVE_TOPOLOGY_TRIANGLE_STRIP:   ָ��һϵ�������Ĺ���һ���ߵ�������ͼԪ.
        VK_PRIMITIVE_TOPOLOGY_TRIANGLE_FAN:   ָ��һϵ�������Ĺ���һ����ͬ�����������ͼԪ�����VK_KHR_portability_subset��չ��������VkPhysicalDevicePortabilitySubsetFeaturesKHR::triangleFansΪVK_FALSE��
                ��֧�ָ�ͼԪ���ͣ���VK_PRIMITIVE_TOPOLOGY_TRIANGLE_FAN ����ʹ��
        VK_PRIMITIVE_TOPOLOGY_LINE_LIST_WITH_ADJACENCY:   ָ��һϵ����ɢ�Ĵ��ڽӹ�ϵ����ͼԪ
        VK_PRIMITIVE_TOPOLOGY_LINE_STRIP_WITH_ADJACENCY:   ָ��һϵ�������Ĵ��ڽӹ�ϵ����ͼԪ������������ͼԪ�乲����������
        VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST_WITH_ADJACENCY:   ָ��һϵ����ɢ�Ĵ��ڽӹ�ϵ��������ͼԪ
        VK_PRIMITIVE_TOPOLOGY_TRIANGLE_STRIP_WITH_ADJACENCY:   ָ�������Ĵ��ڽӹ�ϵ��������ͼԪ����������������ͼԪ�乲��һ����
        VK_PRIMITIVE_TOPOLOGY_PATCH_LIST:   ָ����ɢ�� patch ͼԪ.

        
        �ڽӹ�ϵ����Ӱ��ͼԪ���ͣ�ֻ����Щ�ڽӹ�ϵ���ݻ���geometry shader��ʹ��
        */


        //��̬����ͼԪ����   �ȼ���vkCmdSetPrimitiveTopologyEXT��������ֻ����VkPipelineDynamicStateCreateInfo::pDynamicStates�ж�̬����VK_DYNAMIC_STATE_PRIMITIVE_TOPOLOGY�˲���Ч������ʹ��VkPipelineInputAssemblyStateCreateInfo::topology
        vkCmdSetPrimitiveTopology(commandBuffer, VK_PRIMITIVE_TOPOLOGY_LINE_LIST);
        /*
        vkCmdSetPrimitiveTopology��Ч�÷�:
        1.����������Ҫ��һ������
               >  extendedDynamicState ���Կ���
               >  shaderObject ���Կ���
               >  ����commandBuffer���ڵ�VkInstance��VkApplicationInfo::apiVersion Ҫ���ڵ���Version 1.3
        
        */




        //Topology Class �������ͱ�   �μ�p1747 

        // Point Lists ���б�����VK_PRIMITIVE_TOPOLOGY_POINT_LIST ��ÿ�������ĵ㶨��һ�����㣬�ܹ�ͼԪ��vertexCount  �μ�p1747 

        //  Line Lists ���б����� VK_PRIMITIVE_TOPOLOGY_LINE_LIST ��ÿһ�������ĵ㶨��һ���ߣ��ܹ�ͼԪ��vertexCount / 2 . �μ�p1748    �漰provokingVertexMode

        //Line Strips ���б����� VK_PRIMITIVE_TOPOLOGY_LINE_STRIP ��ÿһ����������һ���㶨��һ���ߣ��ܹ�ͼԪ��(0,vertexCount-1). �μ�p1748
    
        //Triangle Lists �������б����� VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST ��ÿ������һ�������������һ�������Σ��ܹ�ͼԪ��vertexCount / 3. �μ�p1749   �漰provokingVertexMode
        
        //Triangle Strips �������б����� VK_PRIMITIVE_TOPOLOGY_TRIANGLE_STRIP ��ÿ����ͺ��������������һ�������Σ��ܹ�ͼԪ��vertexCount - 2 . �μ�p1750   �漰provokingVertexMode
    
        // Triangle Fans �������б����� VK_PRIMITIVE_TOPOLOGY_TRIANGLE_FAN ������������Χ��һ���������㣬��������ΪV0���ܹ�ͼԪ��vertexCount - 2 . �μ�p1751   �漰provokingVertexMode

        // Line Lists With Adjacency���б�����  VK_PRIMITIVE_TOPOLOGY_LINE_LIST_WITH_ADJACENCY ��ÿ������һ���ĸ��������һ�����Լ����ڽ����ݣ��м�������Ϊ��ͼԪ����β������Ϊ�ڽ����ݣ��ܹ�ͼԪ��vertexCount / 4. �μ�p1751   �漰provokingVertexMode
    
        //Line Strips With Adjacency���б�����  VK_PRIMITIVE_TOPOLOGY_LINE_STRIP_WITH_ADJACENCY �����е���м�ÿһ����������һ���㶨��һ���ߣ����ж������β������Ϊ��ͼԪ���ܹ�ͼԪ��vertexCount - 3. �μ�p1752   �漰provokingVertexMode
    
        //Triangle Lists With Adjacency �������б�����  VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST_WITH_ADJACENCY ��ÿ������һ�������������һ���������Լ����ڽ����ݣ���һ���������������������������Σ�����������Ϊ�ڽ����ݣ��ܹ�ͼԪ��vertexCount / 6. �μ�p1752   �漰provokingVertexMode
    
        //Triangle Strips With Adjacency �������б�����  VK_PRIMITIVE_TOPOLOGY_TRIANGLE_STRIP_WITH_ADJACENCY ��ÿһ��������������㶨��һ�������Σ���һ���������������������������Σ�����������Ϊ�ڽ����ݣ��ܹ�ͼԪ��(vertexCount - 4) / 2. �μ�p1752   �漰provokingVertexMode
    
        //Patch Lists patch�б�����  VK_PRIMITIVE_TOPOLOGY_PATCH_LIST ��ÿ������һ�� m ���������һ��patch��m �� VkPipelineTessellationStateCreateInfo::patchControlPointsָ�����ܹ�ͼԪ��vertexCount / m. �μ�p1755 
    }



    //Primitive Order  ͼԪ��˳��  �μ�p1756


    // Programmable Primitive Shading �ɱ��ͼԪ����  �μ�p1756
    {
        //һ�����ͼԪ��װ��pipeline�����vertex shader�׶Σ��������Ϊmultiple instances,�����ÿ��instance����ЩͼԪ���ظ����͵�vertex shader�׶Σ��ý׶λ��������ͼԪװ��׶ε�ÿ�����㶼���е������������vertexIndex �Լ� instanceIndex
        /*
        ��������������:vkCmdDraw �� vkCmdDrawIndirect�� vkCmdDrawIndirectCount ��vkCmdDrawIndirectCountKHR�� vkCmdDrawIndirectCountAMD��vkCmdDrawMultiEXT
        ������������: vkCmdDrawIndexed, vkCmdDrawIndexedIndirect, vkCmdDrawIndexedIndirectCount, vkCmdDrawIndexedIndirectCountKHR, vkCmdDrawIndexedIndirectCountAMD, vkCmdDrawMultiIndexedEXT
        */


        VkIndexType indexType = VK_INDEX_TYPE_UINT16;//ָ�������������Լ��ֽڴ�С
        /*
        VkIndexType:
        VK_INDEX_TYPE_UINT16:    ָ������Ϊ16-bit unsigned integerֵ.
        VK_INDEX_TYPE_UINT32:    ָ������Ϊ32-bit unsigned integerֵ.
        VK_INDEX_TYPE_NONE_KHR:    ָ��û���ṩ��������.
        VK_INDEX_TYPE_UINT8_KHR:    ָ������Ϊ8-bit unsigned integerֵ.

        
        */

        //������������
        vkCmdBindIndexBuffer(commandBuffer, VkBuffer{/*��������һ����Ч��VkBuffer����ʾ��������������*/ }/*buffer,ָ��Ҫ�󶨵�buffer*/,
            0/*offset,��������������������ַ�������ʼ�ֽ�ƫ����*/, indexType/*indexType��ָ�����������ͺʹ�С*/);
        /*
        vkCmdBindIndexBuffer��Ч�÷�:
        1.offset����С��buffer�Ĵ�С
        2.offset + buffer�ڲ�VkDeviceMemory�Ļ���ַ��������indexTypeָ�����ֽڴ�С��������
        3.buffer������VK_BUFFER_USAGE_INDEX_BUFFER_BIT ����
        4.���buffer��non-sparse�ģ���������Ѿ��󶨵���������������VkDeviceMemory����
        5.indexType����ΪVK_INDEX_TYPE_NONE_KHR
        6.���indexTypeΪVK_INDEX_TYPE_UINT8_KHR����indexTypeUint8 ���Ա��뿪��
        7.���maintenance6 û�п�������buffer����ΪVK_NULL_HANDLE
        8.���bufferΪVK_NULL_HANDLE����offset����Ϊ0
        */


        //�������������Լ����С
        vkCmdBindIndexBuffer2KHR(commandBuffer, VkBuffer{/*��������һ����Ч��VkBuffer����ʾ��������������*/ }/*buffer,ָ��Ҫ�󶨵�buffer*/,
            0/*offset,��������������������ַ�������ʼ�ֽ�ƫ����*/,1/*size,Ϊbuffer��Ҫ�󶨵��ڴ��С*/, indexType/*indexType��ָ�����������ͺʹ�С*/);
        /*
        vkCmdBindIndexBuffer2KHR��Ч�÷�:
        1.offset����С��buffer�Ĵ�С
        2.offset + buffer�ڲ�VkDeviceMemory�Ļ���ַ��������indexTypeָ�����ֽڴ�С��������
        3.buffer������VK_BUFFER_USAGE_INDEX_BUFFER_BIT ����
        4.���buffer��non-sparse�ģ���������Ѿ��󶨵���������������VkDeviceMemory����
        5.indexType����ΪVK_INDEX_TYPE_NONE_KHR
        6.���indexTypeΪVK_INDEX_TYPE_UINT8_KHR����indexTypeUint8 ���Ա��뿪��
        7.���maintenance6 û�п�������buffer����ΪVK_NULL_HANDLE
        8.���bufferΪVK_NULL_HANDLE����offset����Ϊ0
        9.���size��ΪVK_WHOLE_SIZE,��1��size����ΪindexTypeָ�����ֽڴ�С��������
                                      ��2��offset + size����С��buffer�Ĵ�С
        */



        //��¼һ���������������  ��ִ��������pipeline���Զ�������ΪfirstVertex��ʼ��װvertexCount�����㣬��firstInstance��ʼ����instanceCount��instance
        vkCmdDraw(commandBuffer, 1/*vertexCount,ָ��Ҫ���ƵĶ������*/, 1/*instanceCount,ָ��Ҫ���Ƶ�instances����*/,
            0/*firstVertex,ָ��Ҫ���Ƶĵ�һ�����������*/, 0/*firstInstance,ָ��Ҫ���Ƶĵ�һ��instance��ID*/);
        /*
        vkCmdDraw��Ч�÷�:
        1.���һ��VkSampler����magFilter����minFilter����VK_FILTER_LINEAR��������1�����reductionModeΪVK_SAMPLER_REDUCTION_MODE_WEIGHTED_AVERAGE��������ڲ���һ��VkImageView��Ϊ������Ľ����compareEnableΪVK_FALSE�����image view��format features�������VK_FORMAT_FEATURE_SAMPLED_IMAGE_FILTER_LINEAR_BIT
                                                                                 ��2�����reductionModeΪVK_SAMPLER_REDUCTION_MODE_MIN ����VK_SAMPLER_REDUCTION_MODE_MAX֮һ ���ڲ���һ��VkImageView��Ϊ������Ľ�������image view��format features�������VK_FORMAT_FEATURE_SAMPLED_IMAGE_FILTER_MINMAX_BIT
        2.���һ��VkSampler����magFilter����minFilter����VK_SAMPLER_MIPMAP_MODE_LINEAR��������1�����reductionModeΪVK_SAMPLER_REDUCTION_MODE_WEIGHTED_AVERAGE��������ڲ���һ��VkImageView��Ϊ������Ľ����compareEnableΪVK_FALSE�����image view��format features�������VK_FORMAT_FEATURE_SAMPLED_IMAGE_FILTER_LINEAR_BIT
                                                                                 ��2�����reductionModeΪVK_SAMPLER_REDUCTION_MODE_MIN ����VK_SAMPLER_REDUCTION_MODE_MAX֮һ ���ڲ���һ��VkImageView��Ϊ������Ľ�������image view��format features�������VK_FORMAT_FEATURE_SAMPLED_IMAGE_FILTER_MINMAX_BIT
        3.���һ��VkSampler����unnormalizedCoordinates����VK_TRUE���ڲ���һ��VkImageView��Ϊ������Ľ����������1����image view��levelCount�Լ�layerCount����Ϊ1
                                                                                                                ��2����image view��viewType����ΪVK_IMAGE_VIEW_TYPE_1D ���� VK_IMAGE_VIEW_TYPE_2D
        4.���һ��VkImageView�Ĳ�����depth comparison��������image view��format features�������VK_FORMAT_FEATURE_2_SAMPLED_IMAGE_DEPTH_COMPARISON_BIT
        5.���һ��VkImageViewʹ��atomic operations��Ϊ������Ľ�����з��ʣ���image view��format features�������VK_FORMAT_FEATURE_STORAGE_IMAGE_ATOMIC_BIT
        6.���һ��VK_DESCRIPTOR_TYPE_STORAGE_TEXEL_BUFFER���͵� descriptorʹ��atomic operations��Ϊ������Ľ�����з��ʣ���storage texel buffer��format features�������VK_FORMAT_FEATURE_STORAGE_TEXEL_BUFFER_ATOMIC_BIT
        7.���һ����VK_FILTER_CUBIC_EXT���в�����VkImageView��Ϊ������Ľ������image view��format features�������VK_FORMAT_FEATURE_SAMPLED_IMAGE_FILTER_CUBIC_BIT_EXT
        8.���VK_EXT_filter_cubic��չû�п����������κ�һ����VK_FILTER_CUBIC_EXT���в�����VkImageView��Ϊ������Ľ��������VkImageViewType����ΪVK_IMAGE_VIEW_TYPE_3D, VK_IMAGE_VIEW_TYPE_CUBE, ���� VK_IMAGE_VIEW_TYPE_CUBE_ARRAY
        9.�κ�һ����VK_FILTER_CUBIC_EXT���в�������Ϊ������Ľ����VkImageView����VkImageViewType��format ����֧��cubic filtering���μ�vkGetPhysicalDeviceImageFormatProperties2���ص�VkFilterCubicImageViewImageFormatPropertiesEXT::filterCubic
        10.�κ�һ����VK_FILTER_CUBIC_EXT���в�����reduction modeΪVK_SAMPLER_REDUCTION_MODE_MIN ���� VK_SAMPLER_REDUCTION_MODE_MAX֮һ����Ϊ������Ľ����VkImageView����VkImageViewType��format ����֧�ִ�minmax filtering��cubic filtering���μ�vkGetPhysicalDeviceImageFormatProperties2���ص�VkFilterCubicImageViewImageFormatPropertiesEXT::filterCubicMinmax
        11.���cubicRangeClamp����û�п����������κ�һ����VK_FILTER_CUBIC_EXT���в���VkImageView����Ϊ������Ľ����VkSamplerReductionModeCreateInfo::reductionMode����ΪVK_SAMPLER_REDUCTION_MODE_WEIGHTED_AVERAGE_RANGECLAMP_QCOM
        12.�κ�һ����VkSamplerReductionModeCreateInfo::reductionModeΪVK_SAMPLER_REDUCTION_MODE_WEIGHTED_AVERAGE_RANGECLAMP_QCOM���в�������Ϊ������Ľ����VkImageView������VK_FILTER_CUBIC_EXT���в���
        13.���selectableCubicWeights����û�п����������κ�һ����VK_FILTER_CUBIC_EXT���в���VkImageView����Ϊ������Ľ����VkSamplerCubicWeightsCreateInfoQCOM::cubicWeights����ΪVK_CUBIC_FILTER_WEIGHTS_CATMULL_ROM_QCOM
        14.�κ�һ����VkImageCreateInfo::flags��VK_IMAGE_CREATE_CORNER_SAMPLED_BIT_NV�����Ĳ�����Ϊ����������VkImage������VkSamplerAddressModeΪVK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE ���в���
        15.�����κ���Ϊstorage imageд���VkImageView������OpTypeImage��formatδ֪�����image view�� format features�������VK_FORMAT_FEATURE_2_STORAGE_WRITE_WITHOUT_FORMAT_BIT
        16.�����κ���Ϊstorage image��ȡ��VkImageView������OpTypeImage��formatδ֪�����image view�� format features�������VK_FORMAT_FEATURE_2_STORAGE_READ_WITHOUT_FORMAT_BIT
        17.�����κ���Ϊstorage storage texel bufferд���VkBufferView������OpTypeImage��formatδ֪�����buffer view�� buffer features�������VK_FORMAT_FEATURE_2_STORAGE_WRITE_WITHOUT_FORMAT_BIT
        18.�����κ���Ϊstorage storage texel buffer��ȡ��VkBufferView������OpTypeImage��formatδ֪�����buffer view�� buffer features�������VK_FORMAT_FEATURE_2_STORAGE_READ_WITHOUT_FORMAT_BIT
        19.����ÿ���ڰ󶨵�shader�о�̬ʹ�õ�set n��һ��descriptor set���뱻�󶨵���ͬpipeline bind point��set n������set n����ʹ�����ǰVkPipeline��VkPipelineLayout���ߺʹ�����ǰVkShaderEXT��VkDescriptorSetLayout �����set n���Ĳ��ּ��ݣ��μ�Pipeline Layout Compatibility p1280
        20.����ÿ���ڰ󶨵�shader�о�̬ʹ�õ�push constant��һ��push constantֵ���뱻�󶨵���ͬpipeline bind point�Ķ�Ӧ������push constant����ʹ�����ǰVkPipeline��VkPipelineLayout���ߺʹ�����ǰVkShaderEXT��VkDescriptorSetLayout �����еĶ�Ӧ���Ĳ��ּ��ݣ��μ�Pipeline Layout Compatibility p1280
        21.���maintenance4����û�п����������ÿ���ڰ󶨵�shader�о�̬ʹ�õ�push constant��һ��push constantֵ���뱻���õ���ͬpipeline bind point�Ķ�Ӧ������push constant����ʹ�����ǰVkPipeline��VkPipelineLayout���ߺʹ�����ǰVkShaderEXT��VkDescriptorSetLayout �����еĶ�Ӧ���Ĳ��ּ��ݣ��μ�Pipeline Layout Compatibility p1280
        22.ÿһ��ͨ��vkCmdBindDescriptorSets�󶨵�descriptor set��descriptors,����Ǳ�����VK_PIPELINE_CREATE_DESCRIPTOR_BUFFER_BIT_EXT�����ģ����Ѿ��󶨵�������ʹ�õ�pipeline bind point��VkPipeline��̬ʹ�õģ�����Щdescriptors��������Ч�ģ��μ� descriptor validity p1328
        23.���ͨ��vkCmdBindDescriptorSetsָ���󶨵�pipeline bind point��VkPipelineҪʹ�õ�descriptors����󶨵�VkPipeline������VK_PIPELINE_CREATE_DESCRIPTOR_BUFFER_BIT_EXT����
		24.��vkCmdSetDescriptorBufferOffsetsEXT��ָ���󶨵�descriptor buffers��descriptors����1������󶨵�pipeline bind point�ĸ������ʹ�õ�VkPipeline��VK_PIPELINE_CREATE_DESCRIPTOR_BUFFER_BIT_EXT����������Щdescriptors�Ƕ�̬ʹ�õģ�����Щdescriptors��������Ч��
                                                                                              ��2������󶨵�pipeline bind point�Ķ�Ӧstage�ĸ������ʹ�õ�VkShaderEXT������Щdescriptors�Ƕ�̬ʹ�õģ�����Щdescriptors��������Ч��
        25.��vkCmdSetDescriptorBufferOffsetsEXT��ָ����descriptors�ڰ󶨵�pipeline bind point��VkPipeline��ʹ�ã���VkPipeline������VK_PIPELINE_CREATE_DESCRIPTOR_BUFFER_BIT_EXT����
        26.���һ��descriptor����VK_PIPELINE_CREATE_DESCRIPTOR_BUFFER_BIT_EXT������VkPipeline�ж�̬ʹ�ã���descriptor memory������פ���ڴ�
		27.���һ��descriptor������VkDescriptorSetLayout��VK_DESCRIPTOR_SET_LAYOUT_CREATE_DESCRIPTOR_BUFFER_BIT_EXT������VkShaderEXT�ж�̬ʹ�ã���descriptor memory������פ���ڴ�
        28.���shaderObject ����û�п�����һ����Ч��pipeline����󶨵��������ʹ�õİ󶨵�pipeline bind point��
		29.���һ��pipeline�󶨵�������ʹ�õ�pipeline bind point�ϣ��������κζ�̬state �������������κθ�VkPipeline ��û��ָ���Ķ�̬ state
		30.���һ��VkPipeline�󶨵�������ʹ�õ�pipeline bind point�� �����κ�һ�������һ��ʹ��unnormalized coordinates��VkSampler�� VkShaderEXT�󶨵�������ʹ�õ�pipeline bind point�ϵ�pipeline�Ķ�Ӧstage����
                                                                                    ��1�����κ�shader stage�У�VkSampler�������������κ�����ΪVK_IMAGE_VIEW_TYPE_3D, VK_IMAGE_VIEW_TYPE_CUBE, VK_IMAGE_VIEW_TYPE_1D_ARRAY, VK_IMAGE_VIEW_TYPE_2D_ARRAY ���� VK_IMAGE_VIEW_TYPE_CUBE_ARRAY��VkImageView
                                                                                    ��2�����κ�shader stage�У���VkSampler���ܺ��κδ��������д���ImplicitLod��Dref ���� Proj ��SPIR-V OpImageSample* ���� OpImageSparseSample*ָ��һ��ʹ��
                                                                                    ��3�����κ�shader stage�У���VkSampler���ܺ��κΰ��� LOD bias����offset ֵ ��SPIR-V OpImageSample* or OpImageSparseSample*ָ��һ��ʹ��
		31.���shaderObject������һ����Ч��pipeline����󶨵�������ʹ�õ�pipeline bind point�ϻ���һ����Ч��shader objects�Լ�VK_NULL_HANDLE����ϱ���󶨵�������ʹ�õ�pipeline bind pointÿһ��֧�ֵ�shader stage��
        32.��ΰ󶨵�������ʹ�õ�pipeline bind point�ϵ�VkPipeline���κ�stage�����һ��uniform buffer���Ҹ�stage��uniformBuffers��������VK_PIPELINE_ROBUSTNESS_BUFFER_BEHAVIOR_ROBUST_BUFFER_ACCESS_EXT����VK_PIPELINE_ROBUSTNESS_BUFFER_BEHAVIOR_ROBUST_BUFFER_ACCESS_2_EXT ��������robustBufferAccess����δ���������stage�Ͳ��ܷ��ʰ󶨵���ͬpipeline bind point��descriptor setָ����buffer��Χ���ֵ
		33.���robustBufferAccess����δ���������κλ����uniform buffer�İ󶨵�������ʹ�õ�pipeline bind point�϶�Ӧshader stage��VkShaderEXT�����䲻�ܷ��ʰ󶨵���ͬpipeline bind point��descriptor setָ����buffer��Χ���ֵ
        34.��ΰ󶨵�������ʹ�õ�pipeline bind point�ϵ�VkPipeline���κ�stage�����һ��storage buffer���Ҹ�stage��storageBuffers��������VK_PIPELINE_ROBUSTNESS_BUFFER_BEHAVIOR_ROBUST_BUFFER_ACCESS_EXT����VK_PIPELINE_ROBUSTNESS_BUFFER_BEHAVIOR_ROBUST_BUFFER_ACCESS_2_EXT ��������robustBufferAccess����δ���������stage�Ͳ��ܷ��ʰ󶨵���ͬpipeline bind point��descriptor setָ����buffer��Χ���ֵ
		35.���robustBufferAccess����δ���������κλ����storage buffer�İ󶨵�������ʹ�õ�pipeline bind point�϶�Ӧshader stage��VkShaderEXT�����䲻�ܷ��ʰ󶨵���ͬpipeline bind point��descriptor setָ����buffer��Χ���ֵ
        36.���commandBuffer ��һ��unprotected command buffer����protectedNoFault δ֧�֣����κΰ󶨵�shaders���ʵ���Դ������һ��protected resource
        37.���һ���󶨵�shader����һ��VkSampler ���� VkImageView ����������sampler Y��C BCR conversion����ֻ��ʹ��OpImageSample* ���� OpImageSparseSample*ָ�����ʹ��ConstOffset �Լ� Offset������
        38.���һ��VkImageView��Ϊ������Ľ�����з��ʣ���1��image view ��viewType ����ƥ��Instruction/Sampler/Image View Validation p1481��������OpTypeImage��Dim������
                                                          ��2��image view ��foamrt��numeric type ����ƥ��OpTypeImage��Sampled Type������
        39.���һ��VkImageView��һ������VK_FORMAT_A8_UNORM_KHR��format������ͨ��OpImageWrite��Ϊ������Ľ�����з��ʣ���������Texel ��������Type�������ٰ����� image view�� format���е�components�ĸ�����ͬ��components����
		40.���һ��VkImageView��VK_FORMAT_A8_UNORM_KHR��format������ͨ��OpImageWrite��Ϊ������Ľ�����з��ʣ���������Texel ��������Type�������4��components
		41.���һ��VkBufferViewͨ��OpImageWrite��Ϊ������Ľ�����з��ʣ���������Texel ��������Type�������ٰ����� buffer view�� format���е�components�ĸ�����ͬ��components����
		42.���һ����64-bit component��VkFormat��VkImageView��Ϊ������Ľ�����з��ʣ���������OpTypeImage��������SampledType�Ŀ�ȱ���Ϊ64
		43.���һ��������64-bit component��VkFormat��VkImageView��Ϊ������Ľ�����з��ʣ���������OpTypeImage��������SampledType�Ŀ�ȱ���Ϊ32
		44.���һ����64-bit component��VkFormat��VkBufferView��Ϊ������Ľ�����з��ʣ���������OpTypeImage��������SampledType�Ŀ�ȱ���Ϊ64λ
		45.���һ��������64-bit component��VkFormat��VkBufferView��Ϊ������Ľ�����з��ʣ���������OpTypeImage��������SampledType�Ŀ�ȱ���Ϊ32
		46.���sparseImageInt64Atomics ����δ����������VK_IMAGE_CREATE_SPARSE_RESIDENCY_BIT������VkImage�����ܱ�SampledType���Ϊ64λ��OpTypeImage��atomic instructions����
		47.���sparseImageInt64Atomics ����δ����������VK_BUFFER_CREATE_SPARSE_RESIDENCY_BIT������VkBuffer�����ܱ�SampledType���Ϊ64λ��OpTypeImage��atomic instructions����
		48.���OpImageWeightedSampleQCOM��������һ����Ϊ������Ľ����VkImageView�����image view��format features�������VK_FORMAT_FEATURE_2_WEIGHT_SAMPLED_IMAGE_BIT_QCOM
        49.���OpImageWeightedSampleQCOM��������һ����Ϊ������Ľ����sample weight image��VkImageView�����image view��format features�������VK_FORMAT_FEATURE_2_WEIGHT_IMAGE_BIT_QCOM
		50.���OpImageBoxFilterQCOM��������һ����Ϊ������Ľ����VkImageView�����image view��format features�������VK_FORMAT_FEATURE_2_BOX_FILTER_SAMPLED_BIT_QCOM
        51.���OpImageBlockMatchSSDQCOM������ OpImageBlockMatchSADQCOM������ȡһ����Ϊ������Ľ����VkImageView����1����image view��format features�������VK_FORMAT_FEATURE_2_BLOCK_MATCHING_BIT_QCOM
                                                                                                                   ��2��ָ����reference coordinates������integer texel coordinate validation ʱ��ʧ��
        52.���OpImageWeightedSampleQCOM, OpImageBoxFilterQCOM, OpImageBlockMatchWindowSSDQCOM, OpImageBlockMatchWindowSADQCOM, OpImageBlockMatchGatherSSDQCOM,
                                                    OpImageBlockMatchGatherSADQCOM, OpImageBlockMatchSSDQCOM, ���� OpImageBlockMatchSADQCOM��������һ����Ϊ������Ľ����VkImageView�����VkSampler������VK_SAMPLER_CREATE_IMAGE_PROCESSING_BIT_QCOM����
        53.����κγ���OpImageWeightedSampleQCOM, OpImageBoxFilterQCOM, OpImageBlockMatchWindowSSDQCOM, OpImageBlockMatchWindowSADQCOM, OpImageBlockMatchGatherSSDQCOM, OpImageBlockMatchGatherSADQCOM, OpImageBlockMatchSSDQCOM, ���� OpImageBlockMatchSADQCOM֮���ָ��ʹ��VkSampler���в�����Ϊ������Ľ�������sampler������VK_SAMPLER_CREATE_IMAGE_PROCESSING_BIT_QCOM ����
		54.���OpImageBlockMatchWindow*QCOM or OpImageBlockMatchGather*QCOMָ��������ȡVkImageView��Ϊ������Ľ������1��VkImageView��format features�������VK_FORMAT_FEATURE_2_BLOCK_MATCHING_BIT_QCOM
                                                                                                                      ��2��VkImageView��format����ֻ����һ��component
        55.���OpImageBlockMatchWindow*QCOM or OpImageBlockMatchGather*QCOMָ��������ȡһ�����õ�image��Ϊ������Ľ������ָ���� reference coordinates������integer texel coordinate validation ʱ��ʧ��
        56.�κθ�����ִ�е�shader invocation�����Ѿ���ֹ
        57.�����һ������λΪVK_DESCRIPTOR_TYPE_SAMPLE_WEIGHT_IMAGE_QCOM, VK_DESCRIPTOR_TYPE_BLOCK_MATCH_IMAGE_QCOM, VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE, VK_DESCRIPTOR_TYPE_STORAGE_IMAGE, ���� VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT������һ����descriptor��Ϊ������Ľ�����з��ʣ����descriptor��ָ��image subresource��layout����͸�descriptor��д��ʱ��layout��ͬ��
        58.��ǰ�� render pass  ����Ͱ󶨵�VK_PIPELINE_BIND_POINT_GRAPHICS�ϵ�VkPipeline ����ʱ���VkGraphicsPipelineCreateInfo��ָ����renderPass����
        59.��ǰ�� render pass  ��subpass index����Ͱ󶨵�VK_PIPELINE_BIND_POINT_GRAPHICS�ϵ�VkPipeline ����ʱ���VkGraphicsPipelineCreateInfo��ָ����subpass��ͬ
		60.����κ�shader��̬����һ��input attachment������Ч��descriptor����ͨ��VkDescriptorSet���󶨵���pipeline��
		61.����κθ�pipelineִ��shader��SubpassData��Dim����������һ��OpTypeImage��������ñ������뱻һ����Ӧ��ǰsubpass��input attachment��InputAttachmentIndex����
		62.��subpass�з��ʵ�Input attachment views�����Ժ͸�subpass��ͬ�����VkFormat�������ұ�����һ���͵�ǰ�󶨵�VkFramebuffer�ĸø������õ�subpass��pInputAttachments[InputAttachmentIndex]�������ݵ�VkImageView�������μ�Fragment Input Attachment Compatibility p1408
        63.�ڶ�̬render pass�з�����VkRenderingInputAttachmentIndexInfoKHR��InputAttachmentIndex������VkRenderingInputAttachmentIndexInfoKHR:pDepthInputAttachmentIndex ���� VkRenderingInputAttachmentIndexInfoKHR:pStencilInputAttachmentIndexΪNULL����²�ָ��InputAttachmentIndex�����õ�Input attachment views�������Ժ�VkRenderingInfo�ж�Ӧcolor, depth, ���� stencil attachment���ݵ�VkImageView����
        64.���VkRenderingInputAttachmentIndexInfoKHR::pDepthInputAttachmentIndex �Լ� VkRenderingInputAttachmentIndexInfoKHR::pStencilInputAttachmentIndex��ΪNULL�����ڶ�̬render pass��ͨ��shader object����Input attachment views����ָ��InputAttachmentIndex
        65.����ڶ�̬render pass��ͨ��shader object����Input attachment viewsָ����InputAttachmentIndex����InputAttachmentIndex����ƥ��VkRenderingInputAttachmentIndexInfoKHR�е�index
        66.��ǰrender pass���õĸ�����Ӧ��image subresource�ײ��ڴ��д��ֻ����Ϊ�������һ������д��
        67.���һ��color attachment��֮ǰ�ĸ�subpass����������load, store, ���� resolve operations������д�룬����layout��ΪVK_IMAGE_LAYOUT_ATTACHMENT_FEEDBACK_LOOP_OPTIMAL_EXT�����е�ǰ�󶨵�pipeline����VK_PIPELINE_CREATE_COLOR_ATTACHMENT_FEEDBACK_LOOP_BIT_EXT������
                                        ����vkCmdSetAttachmentFeedbackLoopEnableEXT���ð���VK_IMAGE_ASPECT_COLOR_BIT�Լ� û�а󶨵�pipeline ���߰󶨵�pipeline��VK_DYNAMIC_STATE_ATTACHMENT_FEEDBACK_LOOP_ENABLE_EXT��������ø���ֻ���Ը������з��ʵģ������������֮һ
        68.���һ��depth attachment��֮ǰ�ĸ�subpass����������load, store, ���� resolve operations������д�룬����layout��ΪVK_IMAGE_LAYOUT_ATTACHMENT_FEEDBACK_LOOP_OPTIMAL_EXT�����е�ǰ�󶨵�pipeline����VK_PIPELINE_CREATE_DEPTH_STENCIL_ATTACHMENT_FEEDBACK_LOOP_BIT_EXT������
                                        ����vkCmdSetAttachmentFeedbackLoopEnableEXT���ð���VK_IMAGE_ASPECT_DEPTH_BIT�Լ� û�а󶨵�pipeline ���߰󶨵�pipeline��VK_DYNAMIC_STATE_ATTACHMENT_FEEDBACK_LOOP_ENABLE_EXT��������ø���ֻ���Ը������з��ʵģ������������֮һ

        */


    }

}



NS_TEST_END