#include "ShadersTest.h"
NS_TEST_BEGIN


/*
�½�����������
shaders����
������shaders����
��shaders
����shader״̬
shaders����
shaderģ��
shaderģ���ʶ��
shaderִ��
shader����˳��
shader��������
task shader
mesh shader
cluster culling shader
vertex shader
tessellation control shader
tessellation evaluation shader
geometry shader
fragment shader
compute shader
ray generation shader
intersection shader
any-hit shader
close-hit shader
miss shader
callable shader
��ֵװ��
scope
�����
�ı��������
��������
Эͬ����
��֤����
cuda ģ��




*/












ShadersTest::ShadersTest()
{
}

void ShadersTest::run()
{
}

ShadersTest::~ShadersTest()
{
}

void ShadersTest::ShaderCreateTest()
{
	VkShaderEXT shaderExt{VK_NULL_HANDLE};
	VkShaderCreateInfoEXT shaderCreateInfo{};
	shaderCreateInfo.sType = VK_STRUCTURE_TYPE_SHADER_CREATE_INFO_EXT;
	shaderCreateInfo.pNext = nullptr;//���Ժ���VkPipelineShaderStageRequiredSubgroupSizeCreateInfo

	shaderCreateInfo.flags = VK_SHADER_CREATE_LINK_STAGE_BIT_EXT;
	/*
	
	VK_SHADER_CREATE_LINK_STAGE_BIT_EXT��ָ����vkCreateShadersEXT������shader�ᱻ������һ��
	VK_SHADER_CREATE_ALLOW_VARYING_SUBGROUP_SIZE_BIT_EXT��ָ��task, mesh, ���� compute shader�� SubgroupSize���Բ�ͬ
	VK_SHADER_CREATE_REQUIRE_FULL_SUBGROUPS_BIT_EXT��ָ��subgroup��С���Ա����ڼ���task, mesh, ���� compute shaderʱ����
	VK_SHADER_CREATE_NO_TASK_SHADER_BIT_EXT��ָ��mesh shader������û��task shader�����ʹ��
	VK_SHADER_CREATE_DISPATCH_BASE_BIT_EXT��ָ��compute shader������vkCmdDispatchBase���Է���������������ʹ��
	VK_SHADER_CREATE_FRAGMENT_SHADING_RATE_ATTACHMENT_BIT_EXT��ָ��fragment shader����ʹ��fragment shading rate attachment
	VK_SHADER_CREATE_FRAGMENT_DENSITY_MAP_ATTACHMENT_BIT_EXT��ָ��fragment shader����ʹ��fragment density map attachment.
	*/
	shaderCreateInfo.stage = VK_SHADER_STAGE_VERTEX_BIT;//ָ��������shader����
	shaderCreateInfo.nextStage = VK_SHADER_STAGE_VERTEX_BIT;//��Ϊ0����ָ����һ������ɫ���󶨺���ƿ��ܻ�ʹ�õ���ɫ��״̬
	shaderCreateInfo.codeType = VK_SHADER_CODE_TYPE_SPIRV_EXT;//ָ��shader��������
	/*
	VK_SHADER_CODE_TYPE_BINARY_EXT��ָ��shader����Ϊ��͸���ģ��ض��������豸��ʵ�ֶ���Ķ����Ƹ�ʽ
	VK_SHADER_CODE_TYPE_SPIRV_EX��ָ��shader����ΪSPIR-V��ʽ
	*/
	shaderCreateInfo.codeSize = 1;//ָ�����볤��
	shaderCreateInfo.pCode = VK_NULL_HANDLE;//ָ��shader�����ָ��
	shaderCreateInfo.pName = "main";//ָ����ǰ��ɫ������ں�����
	shaderCreateInfo.pushConstantRangeCount = 1;
		VkPushConstantRange constantRange{};
		constantRange.offset = 0;
		constantRange.size = 1;
		constantRange.stageFlags = VK_SHADER_STAGE_VERTEX_BIT;
	shaderCreateInfo.pPushConstantRanges = &constantRange;//pushConstantRangeCount�� VkPushConstantRange�������׵�ַ
	shaderCreateInfo.setLayoutCount = 0;
	shaderCreateInfo.pSetLayouts = VK_NULL_HANDLE;//ָ������ɫ��ʹ�õ���Դ����
		VkSpecializationInfo specializationInfo{};
		specializationInfo.dataSize = 1;
		specializationInfo.pData = VK_NULL_HANDLE;
		specializationInfo.mapEntryCount = 1;
			VkSpecializationMapEntry mapEntry;
			mapEntry.constantID = 1;
			mapEntry.offset = 0;
			mapEntry.size = 1;
			specializationInfo.pMapEntries = &mapEntry;
	shaderCreateInfo.pSpecializationInfo = &specializationInfo;
	/*
	��Ч�÷���
	1.��� codeType Ϊ VK_SHADER_CODE_TYPE_SPIRV_EXT����1��codeSize����Ϊ4�ı���
                                                        ��2��pCode�����ǺϷ���spirv����
	                                                    ��3��pCode���븽�ӵ� SPIR-V Environment��¼�� Validation Rules within a Module������������֤������
														��4��pCode��������shader��spirv����capability
														��6��pCode��������API��֧�ֵ�capability�� ��SPIR-V Environment��¼�е� Capabilities�н�������
														��7��pCode�������о���SPIR-V Environment��¼��capability����������������Ӧ������
														��8��pCode��������API��֧�ֵ���չ����SPIR-V Environment��¼�е�  Extension �н�������
														��9��pName������pCode�� OpEntryPointƥ��stage��ִ��ģ�͵�����
														��10��pCode������뵽4�ֽ�
														��11���������ڵ�Ľӿڴ������� ClipDistance BuiltIn�����ı�������ñ�������Ĵ�С���ܴ��� VkPhysicalDeviceLimits::maxClipDistances
														��12���������ڵ�Ľӿڴ������� CullDistance BuiltIn�����ı�������ñ�������Ĵ�С���ܴ��� VkPhysicalDeviceLimits::maxCullDistances
														��13���������ڵ�Ľӿڴ������� ClipDistance BuiltIn����CullDistance BuiltIn�����ı�������ñ�������Ĵ�С���ܴ���  VkPhysicalDeviceLimits::maxCombinedClipAndCullDistances
														��14���������ڵ�Ľӿڴ������� SampleMask BuiltIn�����ı�������ñ�������Ĵ�С���ܴ��� VkPhysicalDeviceLimits::maxSampleMaskWords
														��15�����stageΪVK_SHADER_STAGE_VERTEX_BIT,��������ڵ�Ľӿڴ��Ͳ��ܴ��ڴ����� CullDistance�������������
														��16�����stageΪVK_SHADER_STAGE_TESSELLATION_CONTROL_BIT ���� VK_SHADER_STAGE_TESSELLATION_EVALUATION_BIT,��������ڵ���OpExecutionModeָ���� OutputVertices,��patch size ��
																		��patch size�ͱ������0��С��VkPhysicalDeviceLimits::maxTessellationPatchSize
														��17�����stageΪVK_SHADER_STAGE_GEOMETRY_BIT,��������ڵ���뺬��OpExecutionModeָ�������Ķ�����Ŀ������Ŀ����0��С�ڵ���VkPhysicalDeviceLimits::maxGeometryOutputVertices 
														��18�����stageΪVK_SHADER_STAGE_GEOMETRY_BIT,��������ڵ���뺬��OpExecutionModeָ���˵�����Ŀ������Ŀ����0��С�ڵ���VkPhysicalDeviceLimits:::maxGeometryShaderInvocations 
														��19�����stageΪһ�� pre-rasterization shader stage ������ڵ��ƬԪ���κ�layerд��������뽫��ͬ��ֵд��ƬԪ�����ж����layer��
														��20�����stageΪһ�� pre-rasterization shader stage ������ڵ��ƬԪ���κ�ViewportIndexд��������뽫��ͬ��ֵд��ƬԪ�����ж����ViewportIndex��
														��21�����stageΪ VK_SHADER_STAGE_FRAGMENT_BIT��������ڵ㲻�ܺ����κ���  CullDistance �������������
														��22�����stageΪ VK_SHADER_STAGE_FRAGMENT_BIT��������ڵ㲻�����κ�ִ��·����д�� FragDepth �����в�ר����helper���õ�ִ��·�������붪��Ƭ�Σ�����д����ʼ���� FragDepthֵ
														��23��pCode�е�ֵ��������Ӧ���� pSpecializationInfo������У������ Khronos SPIR-V Specification�����ĺϷ���ֵ���һὫ����ר�Ż�����ת��Ϊ�̶�����
														��24�����stageΪVK_SHADER_STAGE_TESSELLATION_EVALUATION_BIT��pCode�������һ��OpExecutionModeָ��ϸ������
														��25�����stageΪVK_SHADER_STAGE_TESSELLATION_EVALUATION_BIT��pCode�������һ��OpExecutionModeָ��ϸ�ֿ�����������orientation of triangles
														��26�����stageΪVK_SHADER_STAGE_TESSELLATION_EVALUATION_BIT��pCode�������һ��OpExecutionModeָ��ϸ��ͼԪ�ı��ϵ�spacing of segments
														��27�����stageΪVK_SHADER_STAGE_TESSELLATION_EVALUATION_BIT��pCode�������һ��OpExecutionModeָ�� output patch ��С
	2.���stage����VK_SHADER_STAGE_TASK_BIT_EXT, VK_SHADER_STAGE_MESH_BIT_EXT,
													VK_SHADER_STAGE_VERTEX_BIT, VK_SHADER_STAGE_TESSELLATION_CONTROL_BIT,
													VK_SHADER_STAGE_TESSELLATION_EVALUATION_BIT, VK_SHADER_STAGE_GEOMETRY_BIT, ����
													VK_SHADER_STAGE_FRAGMENT_BIT��flags���ܰ���VK_SHADER_CREATE_LINK_STAGE_BIT_EXT
	3.���stage����VK_SHADER_STAGE_FRAGMENT_BIT,��flags���ܰ���VK_SHADER_CREATE_FRAGMENT_SHADING_RATE_ATTACHMENT_BIT_EXT��VK_SHADER_CREATE_FRAGMENT_DENSITY_MAP_ATTACHMENT_BIT_EXT��											
	4.��� attachmentFragmentShadingRate����û�п�����flags���ܰ���VK_SHADER_CREATE_FRAGMENT_SHADING_RATE_ATTACHMENT_BIT_EXT
	5.���  fragmentDensityMap����û�п�����flags���ܰ���VK_SHADER_CREATE_FRAGMENT_DENSITY_MAP_ATTACHMENT_BIT_EXT
	6.���flags����VK_SHADER_CREATE_ALLOW_VARYING_SUBGROUP_SIZE_BIT_EXT,�� subgroupSizeControl ���Ա��뿪��
	7.���flags����VK_SHADER_CREATE_REQUIRE_FULL_SUBGROUPS_BIT_EXT,�� computeFullSubgroups ���Ա��뿪��
	8.���flags����VK_SHADER_CREATE_REQUIRE_FULL_SUBGROUPS_BIT_EXT����stage������VK_SHADER_STAGE_MESH_BIT_EXT, VK_SHADER_STAGE_TASK_BIT_EXT, ����VK_SHADER_STAGE_COMPUTE_BIT����֮һ
	9.���stage��ΪVK_SHADER_STAGE_COMPUTE_BIT����flags���ܰ���VK_SHADER_CREATE_DISPATCH_BASE_BIT_EXT
	10.���stage��ΪVK_SHADER_STAGE_MESH_BIT_EXT����flags���ܰ���VK_SHADER_CREATE_NO_TASK_SHADER_BIT_EXT
	11.���flags����VK_SHADER_CREATE_ALLOW_VARYING_SUBGROUP_SIZE_BIT_EXT �� VK_SHADER_CREATE_REQUIRE_FULL_SUBGROUPS_BIT_EXT������ɫ���ı��ع������С��Xά�ȱ���Ϊ maxSubgroupSize ����
	12.���flags����VK_SHADER_CREATE_REQUIRE_FULL_SUBGROUPS_BIT_EXT���ǲ�����VK_SHADER_CREATE_ALLOW_VARYING_SUBGROUP_SIZE_BIT_EXT����pNext��û�� VkShaderRequiredSubgroupSizeCreateInfoEXT ��
													����ɫ���ı��ع������С��Xά�ȱ���Ϊ subgroupSize ����
	13.stage����Ϊ VK_SHADER_STAGE_ALL_GRAPHICS ���� VK_SHADER_STAGE_ALL��VK_SHADER_STAGE_SUBPASS_SHADING_BIT_HUAWEI����VK_SHADER_STAGE_CLUSTER_CULLING_BIT_HUAWEI
	14.���tessellationShader����û�п�������stage��nextStage����ΪVK_SHADER_STAGE_TESSELLATION_CONTROL_BIT ���� VK_SHADER_STAGE_TESSELLATION_EVALUATION_BIT
	15.���geometryShader����û�п�������stage��nextStage����ΪVK_SHADER_STAGE_GEOMETRY_BIT
	16.��� taskShader ����û�п�������stage����ΪVK_SHADER_STAGE_TASK_BIT_EXT
	17.��� meshShader ����û�п�������stage����ΪVK_SHADER_STAGE_MESH_BIT_EXT
	18.���stageΪVK_SHADER_STAGE_VERTEX_BIT��nextStage���ܰ����κγ���VK_SHADER_STAGE_TESSELLATION_CONTROL_BIT, VK_SHADER_STAGE_GEOMETRY_BIT, �Լ�VK_SHADER_STAGE_FRAGMENT_BIT֮���stage
	19.���stageΪVK_SHADER_STAGE_TESSELLATION_CONTROL_BIT��nextStage���ܰ�������VK_SHADER_STAGE_TESSELLATION_EVALUATION_BIT֮���stage
	20.���stageΪVK_SHADER_STAGE_TESSELLATION_EVALUATION_BIT��nextStage���ܰ������� VK_SHADER_STAGE_GEOMETRY_BIT�� VK_SHADER_STAGE_FRAGMENT_BIT֮���stage
	21.���stageΪ VK_SHADER_STAGE_GEOMETRY_BIT��nextStage���ܰ������� VK_SHADER_STAGE_FRAGMENT_BIT֮���stage
	22.���stageΪ  VK_SHADER_STAGE_FRAGMENT_BIT����VK_SHADER_STAGE_COMPUTE_BIT��nextStage����Ϊ0
	23.���stageΪ VK_SHADER_STAGE_TASK_BIT_EXT��nextStage���ܰ������� VK_SHADER_STAGE_MESH_BIT_EXT֮���stage
	24.���stageΪ VK_SHADER_STAGE_MESH_BIT_EXT��nextStage���ܰ������� VK_SHADER_STAGE_FRAGMENT_BIT֮���stage
	25.���codeTypeΪ VK_SHADER_CODE_TYPE_BINARY_EXT��pCode������뵽16�ֽ�

	
	
	
	*/


	vkCreateShadersEXT(device, 1, &shaderCreateInfo, nullptr, &shaderExt);//���ĳ��shaderģ�鴴��ʧ�ܣ���Ӧ��shaderExt��᷵��VK_NULL_HANDLE
	/*
	��Ч�÷���
	1. shaderObject���Ա��뿪��
	2.ֻҪpCreateInfos���κ�Ԫ�ص�flags����VK_SHADER_CREATE_LINK_STAGE_BIT_EXT������������Ԫ�ص�stageΪVK_SHADER_STAGE_VERTEX_BIT,
									VK_SHADER_STAGE_TESSELLATION_CONTROL_BIT, VK_SHADER_STAGE_TESSELLATION_EVALUATION_BIT,
									VK_SHADER_STAGE_GEOMETRY_BIT, ���� VK_SHADER_STAGE_FRAGMENT_BIT��
									VK_SHADER_STAGE_TASK_BIT_EXT ���� VK_SHADER_STAGE_MESH_BIT_EXT��flagsҲ�������VK_SHADER_CREATE_LINK_STAGE_BIT_EXT
	3.���pCreateInfos���κ�Ԫ�ص�stage��VK_SHADER_STAGE_TASK_BIT_EXT ���� VK_SHADER_STAGE_MESH_BIT_EXT��flags�а���VK_SHADER_CREATE_LINK_STAGE_BIT_EXT����
									pCreateInfos�н�û��stageΪVK_SHADER_STAGE_VERTEX_BIT��flags����VK_SHADER_CREATE_LINK_STAGE_BIT_EXT
	4.���pCreateInfos���д���stageΪ VK_SHADER_STAGE_MESH_BIT_EXT��flags����VK_SHADER_CREATE_LINK_STAGE_BIT_EXT ��VK_SHADER_CREATE_NO_TASK_SHADER_BIT_EXT��Ԫ�أ���
									pCreateInfos�н�û��stageΪVK_SHADER_STAGE_TASK_BIT_EXT��flags����VK_SHADER_CREATE_LINK_STAGE_BIT_EXT
	5.���pCreateInfos��ÿ��Ԫ�ص�flags����VK_SHADER_CREATE_LINK_STAGE_BIT_EXT�������������Ԫ�ص�stage�߼��ϳ���ǰ�����flagsҲ����VK_SHADER_CREATE_LINK_STAGE_BIT_EXT����
									ǰ���nextStage������ڱ�ǰ���flags����VK_SHADER_CREATE_LINK_STAGE_BIT_EXT�� stage���߼���ǰ���һ��Ԫ�ص�stage �����벻׼��
	6.pCreateInfos��ÿ��Ԫ�ص�flags����VK_SHADER_CREATE_LINK_STAGE_BIT_EXT��stage�����ǲ�ͬ�ģ�codeType������ͬ
	7.pCreateInfos��Ԫ�������Ԫ�ص�stage����VK_SHADER_STAGE_TESSELLATION_CONTROL_BIT�� VK_SHADER_STAGE_TESSELLATION_EVALUATION_BIT,flags����VK_SHADER_CREATE_LINK_STAGE_BIT_EXT��codeTypeΪVK_SHADER_CODE_TYPE_SPIRV_EXT��
									���� VK_SHADER_STAGE_TESSELLATION_CONTROL_BIT״̬��pCode���� OpExecutionModeָ��ָ��ϸ�ֵ����ͣ����������VK_SHADER_STAGE_TESSELLATION_EVALUATION_BIT��ϸ������ƥ�䣬ͬ��orientation of triangles,Ҳ����ƥ�䣬
									 ��ϸ��ͼԪ�߽��ϵ�spacing of segments Ҳ����ƥ�䣬output patch sizeҲ����ƥ��
	8.pCreateInfos��Ԫ�������Ԫ�ص�stage����VK_SHADER_STAGE_TESSELLATION_CONTROL_BIT�� VK_SHADER_STAGE_TESSELLATION_EVALUATION_BIT,flags����VK_SHADER_CREATE_LINK_STAGE_BIT_EXT��codeTypeΪVK_SHADER_CODE_TYPE_SPIRV_EXT,��
									���� VK_SHADER_STAGE_TESSELLATION_CONTROL_BIT״̬��pCode���� OpExecutionModeָ��ָ�� PointMode����VK_SHADER_STAGE_TESSELLATION_EVALUATION_BITҲ����ָ�� PointMode
	
	9.���pCreateInfos����һ��stageΪVK_SHADER_STAGE_MESH_BIT_EXT��codeTypeΪVK_SHADER_CODE_TYPE_SPIRV_EXT��û������VK_SHADER_CREATE_NO_TASK_SHADER_BIT_EXT����mesh shader�Ͳ�������һ���� DrawIndex BuiltIn�����ı���
	
	
	
	*/





}























NS_TEST_END