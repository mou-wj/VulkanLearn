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






	//��������ɫ������
	//��ȡshader�Ķ�������ɫ�����룬���Դ��ݸ�shaderCreateInfo����ȡ����������ڼ��ݵĲ�ͬ�߼��豸���������豸�ϴ�����ɫ����
	//���������л��ƣ�VkPhysicalDeviceShaderObjectPropertiesEXT�е�shaderBinaryUUID����ͬ����shaderBinaryVersion���汾����--�߼��ݵͣ�����
	size_t bcodeSize = 0;
	VK_DEVICE_FUNCTION_GET_AND_CALL(device, vkGetShaderBinaryDataEXT, device, shaderExt, &bcodeSize, nullptr);
	std::vector<char> bcode;
	bcode.resize(bcodeSize);
	VK_DEVICE_FUNCTION_GET_AND_CALL(device, vkGetShaderBinaryDataEXT, device, shaderExt, &bcodeSize, bcode.data());







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


	VK_DEVICE_FUNCTION_GET_AND_CALL(device, vkCreateShadersEXT, device, 1, &shaderCreateInfo, nullptr, &shaderExt);//���ĳ��shaderģ�鴴��ʧ�ܣ���Ӧ��shaderExt��᷵��VK_NULL_HANDLE
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



	//��shader
	{
		VkCommandBuffer cmdbuf;
		VkShaderStageFlagBits stage;
		VK_DEVICE_FUNCTION_GET_AND_CALL(device, vkCmdBindShadersEXT, cmdbuf, 1, &stage, &shaderExt);//��shader�Լ�ָ����stage,�൱�����°�pupeline�϶�Ӧstage����ɫ��
		/*
		�Ϸ��÷�
		1.������ĳ��shaderֻ��Ҫ��pShaders�ж�Ӧ��λ������ΪVK_NULL_HANDLE����,���pShadersΪNULL����ͬ������shader�����
		2.shaderObject���Ա��뿪��
		3.pShaders��ÿ��Ԫ�ص�stage�����ǲ�ͬ��
		4.pStages���ܰ���VK_SHADER_STAGE_ALL_GRAPHICS ���� VK_SHADER_STAGE_ALL��VK_SHADER_STAGE_RAYGEN_BIT_KHR,
														   VK_SHADER_STAGE_ANY_HIT_BIT_KHR, VK_SHADER_STAGE_CLOSEST_HIT_BIT_KHR,
														   VK_SHADER_STAGE_MISS_BIT_KHR, VK_SHADER_STAGE_INTERSECTION_BIT_KHR, ����
														   VK_SHADER_STAGE_CALLABLE_BIT_KHR��VK_SHADER_STAGE_SUBPASS_SHADING_BIT_HUAWEI��
														   VK_SHADER_STAGE_CLUSTER_CULLING_BIT_HUAWEI
		5.���pShaders��Ϊ�������еĲ�ΪVK_NULL_HANDLE��Ԫ�صĴ���ʱ���stage�����pStages�еĶ�Ӧλ�õ�stage��ͬ
		6.���pStages����VK_SHADER_STAGE_TASK_BIT_EXT �� VK_SHADER_STAGE_VERTEX_BIT����pShaders��ΪNULL,����pShaders��VK_SHADER_STAGE_TASK_BIT_EXT��ͬλ�õ�Ԫ�ز�ΪVK_NULL_HANDLE,
				��VK_SHADER_STAGE_VERTEX_BIT��ͬλ�õ�pShaderԪ�ر���ΪVK_NULL_HANDLE
		7.���pStages����VK_SHADER_STAGE_MESH_BIT_EXT �� VK_SHADER_STAGE_VERTEX_BIT,����pShaders��ΪNULL,����pShaders��VK_SHADER_STAGE_MESH_BIT_EXT��ͬλ�õ�Ԫ�ز�ΪVK_NULL_HANDLE,
				��VK_SHADER_STAGE_VERTEX_BIT��ͬλ�õ�pShaderԪ�ر���ΪVK_NULL_HANDLE
		8.���tessellationShader����û�п�������pStages����VK_SHADER_STAGE_TESSELLATION_CONTROL_BIT ���� VK_SHADER_STAGE_TESSELLATION_EVALUATION_BIT����pShaders��ΪNULL,��stage��Ӧ��pShaderԪ�ر���ΪVK_NULL_HANDLE
		9.���geometryShader����û�п�������pStages����VK_SHADER_STAGE_GEOMETRY_BIT����pShaders��ΪNULL,��stage��Ӧ��pShaderԪ�ر���ΪVK_NULL_HANDLE
		10.��� taskShader ����û�п�������pStages����VK_SHADER_STAGE_TASK_BIT_EXT����pShaders��ΪNULL,��stage��Ӧ��pShaderԪ�ر���ΪVK_NULL_HANDLE
		11.��� meshShader ����û�п�������pStages����VK_SHADER_STAGE_MESH_BIT_EXT����pShaders��ΪNULL,��stage��Ӧ��pShaderԪ�ر���ΪVK_NULL_HANDLE
		12.���pStages���� VK_SHADER_STAGE_COMPUTE_BIT,��cmdbuf���ڵ�VkCommandPool��queueFamilyIndex����֧�ּ������
		13.��� pStages ���� VK_SHADER_STAGE_VERTEX_BIT, VK_SHADER_STAGE_TESSELLATION_CONTROL_BIT,
				VK_SHADER_STAGE_TESSELLATION_EVALUATION_BIT, VK_SHADER_STAGE_GEOMETRY_BIT, ����
				VK_SHADER_STAGE_FRAGMENT_BIT��VK_SHADER_STAGE_MESH_BIT_EXT ���� VK_SHADER_STAGE_TASK_BIT_EXT,
				��cmdbuf���ڵ�VkCommandPool��queueFamilyIndex����֧��ͼ�β���
		*/
	


		//����״̬����Ҫ�����ö�̬����״̬

		//����������Ҫ�ڻ�������֮ǰ����
		vkCmdSetViewportWithCount(cmdbuf, 0, VK_NULL_HANDLE);
		vkCmdSetScissorWithCount(cmdbuf, 0, VK_NULL_HANDLE);
		vkCmdSetRasterizerDiscardEnable(cmdbuf, VK_FALSE);

		//���shader��VK_SHADER_STAGE_VERTEX_BIT��������������Ҫ�ڻ�������ǰ����
		VK_DEVICE_FUNCTION_GET_AND_CALL(device, vkCmdSetVertexInputEXT, cmdbuf, 0, VK_NULL_HANDLE, 0, VK_NULL_HANDLE);
		vkCmdSetPrimitiveTopology(cmdbuf, VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST);
		VK_DEVICE_FUNCTION_GET_AND_CALL(device, vkCmdSetPatchControlPointsEXT, cmdbuf, 0); //if primitiveTopology is VK_PRIMITIVE_TOPOLOGY_PATCH_LIST
		vkCmdSetPrimitiveRestartEnable(cmdbuf, VK_FALSE);

		//���shader��VK_SHADER_STAGE_TESSELLATION_EVALUATION_BIT��������������Ҫ�ڻ�������ǰ����
		VK_DEVICE_FUNCTION_GET_AND_CALL(device, vkCmdSetTessellationDomainOriginEXT, cmdbuf, VK_TESSELLATION_DOMAIN_ORIGIN_UPPER_LEFT);

		//��� rasterizerDiscardEnable Ϊ VK_FALSE,��������������Ҫ�ڻ�������ǰ����
		VK_DEVICE_FUNCTION_GET_AND_CALL(device, vkCmdSetRasterizationSamplesEXT, cmdbuf, VK_SAMPLE_COUNT_1_BIT);
		VK_DEVICE_FUNCTION_GET_AND_CALL(device, vkCmdSetSampleMaskEXT, cmdbuf, VK_SAMPLE_COUNT_1_BIT, VK_NULL_HANDLE);
		VK_DEVICE_FUNCTION_GET_AND_CALL(device, vkCmdSetAlphaToCoverageEnableEXT, cmdbuf, VK_FALSE);
		VK_DEVICE_FUNCTION_GET_AND_CALL(device, vkCmdSetAlphaToOneEnableEXT, cmdbuf, VK_FALSE);// if the alphaToOne feature is enabled on the device
		VK_DEVICE_FUNCTION_GET_AND_CALL(device, vkCmdSetPolygonModeEXT, cmdbuf, VK_POLYGON_MODE_FILL);
		vkCmdSetLineWidth(cmdbuf, 1);//  ���polygonMode Ϊ VK_POLYGON_MODE_LINE, ���� ��� shader �󶨵�
			//VK_SHADER_STAGE_VERTEX_BIT stage �� primitiveTopology Ϊ line topology, ������� shader ��� line primitives�Ұ󶨵� VK_SHADER_STAGE_TESSELLATION_EVALUATION_BIT ����
			//VK_SHADER_STAGE_GEOMETRY_BIT stage
		vkCmdSetCullMode(cmdbuf, VK_CULL_MODE_NONE);
		vkCmdSetFrontFace(cmdbuf, VK_FRONT_FACE_COUNTER_CLOCKWISE);
		vkCmdSetDepthTestEnable(cmdbuf, VK_TRUE);
		vkCmdSetDepthWriteEnable(cmdbuf, VK_TRUE);
		vkCmdSetDepthCompareOp(cmdbuf, VK_COMPARE_OP_ALWAYS);//, if depthTestEnable is VK_TRUE
		vkCmdSetDepthBoundsTestEnable(cmdbuf, VK_TRUE);//, if the depthBounds feature is enabled on the device
		vkCmdSetDepthBounds(cmdbuf, 0, 1);//if depthBoundsTestEnable is VK_TRUE
		vkCmdSetDepthBiasEnable(cmdbuf, VK_FALSE);
		vkCmdSetDepthBias(cmdbuf, 1, 1, 1);// if depthBiasEnable is VK_TRUE
		//vkCmdSetDepthBias2EXT  // if depthBiasEnable is VK_TRUE
		VK_DEVICE_FUNCTION_GET_AND_CALL(device, vkCmdSetDepthClampEnableEXT, cmdbuf, VK_TRUE);//if the depthClamp feature is enabled on the device
		vkCmdSetStencilTestEnable(cmdbuf, VK_TRUE);
		vkCmdSetStencilOp(cmdbuf, VK_STENCIL_FRONT_AND_BACK, VK_STENCIL_OP_DECREMENT_AND_CLAMP, VK_STENCIL_OP_DECREMENT_AND_CLAMP, VK_STENCIL_OP_DECREMENT_AND_CLAMP, VK_COMPARE_OP_ALWAYS);// if stencilTestEnable is VK_TRUE
		vkCmdSetStencilCompareMask(cmdbuf, VK_STENCIL_FACE_BACK_BIT, 1); //if stencilTestEnable is VK_TRUE
		vkCmdSetStencilWriteMask(cmdbuf, VK_STENCIL_FACE_BACK_BIT, 1); //if stencilTestEnable is VK_TRUE
		//vkCmdSetStencilReference(cmdbuf,) //if stencilTestEnable is VK_TRUE



		//��� rasterizerDiscardEnable Ϊ VK_FALSE,��shader�󶨵� VK_SHADER_STAGE_FRAGMENT_BIT��������������Ҫ�ڻ�������ǰ����
		VK_DEVICE_FUNCTION_GET_AND_CALL(device, vkCmdSetLogicOpEnableEXT, cmdbuf, VK_FALSE); //if the logicOp feature is enabled on the device
		VK_DEVICE_FUNCTION_GET_AND_CALL(device, vkCmdSetLogicOpEXT, cmdbuf, VK_LOGIC_OP_AND);// if logicOpEnable is VK_TRUE
		VK_DEVICE_FUNCTION_GET_AND_CALL(device, vkCmdSetColorBlendEnableEXT,cmdbuf, 0, 0, VK_NULL_HANDLE);// ���������ɫ��������������render pass�ĸ�������ʱ��Ӧ��ֵ
		VK_DEVICE_FUNCTION_GET_AND_CALL(device, vkCmdSetColorWriteMaskEXT, cmdbuf, 0, 0, VK_NULL_HANDLE);// ���������ɫ��������������render pass�ĸ�������ʱ��Ӧ��ֵ

		VK_DEVICE_FUNCTION_GET_AND_CALL(device, vkCmdSetColorBlendEquationEXT, cmdbuf, 0, 0, VK_NULL_HANDLE);// ���������ɫ����,����ÿһ��������pColorBlendEnables����һ��VK_TRUE��ָ��
		VK_DEVICE_FUNCTION_GET_AND_CALL(device, vkCmdSetColorBlendAdvancedEXT, cmdbuf, 0, 0, VK_NULL_HANDLE);// ���������ɫ����,����ÿһ��������pColorBlendEnables����һ��VK_TRUE��ָ��
		vkCmdSetBlendConstants(cmdbuf, nullptr);/* ��� pColorBlendEnables ��ֵ VK_TRUE,��
			pColorBlendEquations����ͬ�����µ�Ԫ����һ���κ�VkBlendFactor��ԱΪVK_BLEND_FACTOR_CONSTANT_COLOR, VK_BLEND_FACTOR_ONE_MINUS_CONSTANT_COLOR,
			VK_BLEND_FACTOR_CONSTANT_ALPHA, ���� VK_BLEND_FACTOR_ONE_MINUS_CONSTANT_ALPHA�� VkColorBlendEquationEXT
			*/



		//��� rasterizerDiscardEnable Ϊ VK_FALSE,��shader�󶨵� VK_SHADER_STAGE_FRAGMENT_BIT ���� pipelineFragmentShadingRate���Կ�����������������Ҫ�ڻ�������ǰ����
		VK_DEVICE_FUNCTION_GET_AND_CALL(device, vkCmdSetFragmentShadingRateKHR,cmdbuf, nullptr, nullptr);


		//���  geometryStreams ����,��shader�󶨵� VK_SHADER_STAGE_GEOMETRY_BIT��������������Ҫ�ڻ�������ǰ����
		VK_DEVICE_FUNCTION_GET_AND_CALL(device, vkCmdSetRasterizationStreamEXT, cmdbuf, 0);


		//��� rasterizerDiscardEnable Ϊ VK_FALSE,�� VK_EXT_discard_rectangles��չ������������������Ҫ�ڻ�������ǰ����
		VK_DEVICE_FUNCTION_GET_AND_CALL(device, vkCmdSetDiscardRectangleEnableEXT,cmdbuf,VK_FALSE);
		VK_DEVICE_FUNCTION_GET_AND_CALL(device, vkCmdSetDiscardRectangleModeEXT, cmdbuf, VK_DISCARD_RECTANGLE_MODE_EXCLUSIVE_EXT); //if discardRectangleEnable is VK_TRUE
		VK_DEVICE_FUNCTION_GET_AND_CALL(device, vkCmdSetDiscardRectangleEXT, cmdbuf, 0, 0, nullptr); //if discardRectangleEnable is VK_TRUE


		//��� rasterizerDiscardEnable Ϊ VK_FALSE,�� VK_EXT_conservative_rasterization��չ������������������Ҫ�ڻ�������ǰ����
		VK_DEVICE_FUNCTION_GET_AND_CALL(device, vkCmdSetConservativeRasterizationModeEXT, cmdbuf, VK_CONSERVATIVE_RASTERIZATION_MODE_DISABLED_EXT);
		VK_DEVICE_FUNCTION_GET_AND_CALL(device, vkCmdSetExtraPrimitiveOverestimationSizeEXT,cmdbuf, 1); //if conservativeRasterizationMode is VK_CONSERVATIVE_RASTERIZATION_MODE_OVERESTIMATE_EXT


		//���  depthClipEnable ���Կ�����������������Ҫ�ڻ�������ǰ����
		VK_DEVICE_FUNCTION_GET_AND_CALL(device, vkCmdSetDepthClipEnableEXT, cmdbuf, VK_TRUE);


		//��� rasterizerDiscardEnable Ϊ VK_FALSE,�� VK_EXT_sample_locations��չ������������������Ҫ�ڻ�������ǰ����
		VK_DEVICE_FUNCTION_GET_AND_CALL(device, vkCmdSetSampleLocationsEnableEXT, cmdbuf, VK_FALSE);
		VK_DEVICE_FUNCTION_GET_AND_CALL(device, vkCmdSetSampleLocationsEXT, cmdbuf, nullptr); //if sampleLocationsEnable is VK_TRUE


		//��� rasterizerDiscardEnable Ϊ VK_FALSE,�� VK_EXT_provoking_vertex��չ����,��shader�󶨵�VK_SHADER_STAGE_VERTEX_BIT��������������Ҫ�ڻ�������ǰ����
		VK_DEVICE_FUNCTION_GET_AND_CALL(device, vkCmdSetProvokingVertexModeEXT, cmdbuf, VK_PROVOKING_VERTEX_MODE_FIRST_VERTEX_EXT);

		//��� VK_KHR_line_rasterization ���� VK_EXT_line_rasterization ��չ��������rasterizerDiscardEnable Ϊ VK_FALSE����� polygonMode Ϊ VK_POLYGON_MODE_LINE����
		//shader�󶨵�  VK_SHADER_STAGE_VERTEX_BIT��primitiveTopologyΪline topology����shader���line topology �Ұ󶨵�VK_SHADER_STAGE_TESSELLATION_EVALUATION_BIT ���� VK_SHADER_STAGE_GEOMETRY_BIT,������������Ҫ�ڻ�������ǰ����
		VK_DEVICE_FUNCTION_GET_AND_CALL(device, vkCmdSetLineRasterizationModeEXT, cmdbuf, VK_LINE_RASTERIZATION_MODE_BRESENHAM_EXT);
		VK_DEVICE_FUNCTION_GET_AND_CALL(device, vkCmdSetLineStippleEnableEXT, cmdbuf, VK_FALSE);
		//vkCmdSetLineStippleKHR  //if stippledLineEnable is VK_TRUE


		//��� depthClipControl ���Կ�����������������Ҫ�ڻ�������ǰ����
		VK_DEVICE_FUNCTION_GET_AND_CALL(device, vkCmdSetDepthClipNegativeOneToOneEXT, cmdbuf, VK_FALSE);




		//��� rasterizerDiscardEnable Ϊ VK_FALSE,�� colorWriteEnable ���Կ���,��shader�󶨵�VK_SHADER_STAGE_FRAGMENT_BIT��������������Ҫ�ڻ�������ǰ����
		VK_DEVICE_FUNCTION_GET_AND_CALL(device, vkCmdSetColorWriteEnableEXT, cmdbuf, 0, nullptr); //with values set for every color attachment in the render pass instance active at draw time

		//��� rasterizerDiscardEnable Ϊ VK_FALSE,��  attachmentFeedbackLoopDynamicState ���Կ���,��shader�󶨵�VK_SHADER_STAGE_FRAGMENT_BIT��������������Ҫ�ڻ�������ǰ����
		VK_DEVICE_FUNCTION_GET_AND_CALL(device, vkCmdSetAttachmentFeedbackLoopEnableEXT, cmdbuf, VK_IMAGE_ASPECT_COLOR_BIT);


		//���  VK_NV_clip_space_w_scaling ���Կ���,������������Ҫ�ڻ�������ǰ����
		VK_DEVICE_FUNCTION_GET_AND_CALL(device, vkCmdSetViewportWScalingEnableNV,cmdbuf, VK_FALSE);
		VK_DEVICE_FUNCTION_GET_AND_CALL(device, vkCmdSetViewportWScalingNV,cmdbuf, 0, 0, nullptr); //if viewportWScalingEnable is VK_TRUE


		//���  VK_NV_clip_space_w_scaling ���Կ���,������������Ҫ�ڻ�������ǰ����
		VK_DEVICE_FUNCTION_GET_AND_CALL(device, vkCmdSetViewportSwizzleNV, cmdbuf, 0, 0, nullptr);


		//��� rasterizerDiscardEnable Ϊ VK_FALSE,��   VK_NV_fragment_coverage_to_color ��չ����,��shader�󶨵�VK_SHADER_STAGE_FRAGMENT_BIT��������������Ҫ�ڻ�������ǰ����
		VK_DEVICE_FUNCTION_GET_AND_CALL(device, vkCmdSetCoverageToColorEnableNV, cmdbuf, VK_FALSE);
		VK_DEVICE_FUNCTION_GET_AND_CALL(device, vkCmdSetCoverageToColorLocationNV, cmdbuf, 0); //if coverageToColorEnable is VK_TRUE


		//��� rasterizerDiscardEnable Ϊ VK_FALSE,��   VK_NV_framebuffer_mixed_samples ��չ������������������Ҫ�ڻ�������ǰ����
		VK_DEVICE_FUNCTION_GET_AND_CALL(device, vkCmdSetCoverageModulationModeNV, cmdbuf, VK_COVERAGE_MODULATION_MODE_ALPHA_NV);
		VK_DEVICE_FUNCTION_GET_AND_CALL(device, vkCmdSetCoverageModulationTableEnableNV, cmdbuf, VK_FALSE); //if coverageModulationMode is not VK_COVERAGE_MODULATION_MODE_NONE_NV
		VK_DEVICE_FUNCTION_GET_AND_CALL(device, vkCmdSetCoverageModulationTableNV, cmdbuf, 0, nullptr); //if coverageModulationTableEnable is VK_TRUE


		//��� rasterizerDiscardEnable Ϊ VK_FALSE,��    coverageReductionMode ���Կ�����������������Ҫ�ڻ�������ǰ����
		VK_DEVICE_FUNCTION_GET_AND_CALL(device, vkCmdSetCoverageReductionModeNV, cmdbuf, VK_COVERAGE_REDUCTION_MODE_MERGE_NV);

		//��� rasterizerDiscardEnable Ϊ VK_FALSE,��     representativeFragmentTest ���Կ�����������������Ҫ�ڻ�������ǰ����
		VK_DEVICE_FUNCTION_GET_AND_CALL(device, vkCmdSetRepresentativeFragmentTestEnableNV, cmdbuf, VK_FALSE);

		//��� rasterizerDiscardEnable Ϊ VK_FALSE,��      shadingRateImage ���Կ�����������������Ҫ�ڻ�������ǰ����
		VK_DEVICE_FUNCTION_GET_AND_CALL(device, vkCmdSetCoarseSampleOrderNV, cmdbuf, VK_COARSE_SAMPLE_ORDER_TYPE_CUSTOM_NV, 0, nullptr);
		VK_DEVICE_FUNCTION_GET_AND_CALL(device, vkCmdSetShadingRateImageEnableNV, cmdbuf, VK_FALSE);
		VK_DEVICE_FUNCTION_GET_AND_CALL(device, vkCmdSetViewportShadingRatePaletteNV, cmdbuf, 0, 0, nullptr); // if shadingRateImageEnable is VK_TRUE


		//���   exclusiveScissor ���Կ�����������������Ҫ�ڻ�������ǰ����
		VK_DEVICE_FUNCTION_GET_AND_CALL(device, vkCmdSetExclusiveScissorEnableNV, cmdbuf, 0, 0, nullptr);
		VK_DEVICE_FUNCTION_GET_AND_CALL(device, vkCmdSetExclusiveScissorNV, cmdbuf,0,0,nullptr); // if any value in pExclusiveScissorEnables is VK_TRUE


	}


	VK_DEVICE_FUNCTION_GET_AND_CALL(device, vkDestroyShaderEXT, device, shaderExt, nullptr);

}

void ShadersTest::ShaderModuleCreateTest()
{
	//shader module����һ��������ڵ㣬�ұ�����SPIR-V shader���봴����
	VkShaderModule shaderModule;


	VkShaderModuleCreateInfo shaderModuleCreateInfo{};
	shaderModuleCreateInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
		
		//��VkValidationCacheEXT�Ķ����л�ȡ��data
		VkValidationCacheEXT otherValidationCache{ VK_NULL_HANDLE };
		size_t validationDataSize = 0;
		std::vector<char> validationData;
		VK_DEVICE_FUNCTION_GET_AND_CALL(device, vkGetValidationCacheDataEXT, device, otherValidationCache, &validationDataSize, nullptr);
		validationData.resize(validationDataSize);
		VK_DEVICE_FUNCTION_GET_AND_CALL(device, vkGetValidationCacheDataEXT, device, otherValidationCache, &validationDataSize, validationData.data());/*
			��vkGetValidationCacheDataEXT��ȡ��pDataΪ������Ӧ��ʶ���Ƿ�͵�ǰdeviceƥ�䣬pData�Ŀ�ͷ�����ͷ����Ϣ��ͷ����Ϣ����Ҫ��ʽΪ��
				ǰ��ƫ��λ��0��4�ֽڱ�ʾ����ͷ����Ϣ���ֽڳ��ȣ����ֽ���д�룻
				ǰ��ƫ��λ��4��4�ֽڱ�ʾvalidation cache�İ汾��ϢVkValidationCacheHeaderVersionEXT�����ܵİ汾��ϢΪVK_VALIDATION_CACHE_HEADER_VERSION_ONE_EXT = 1ָ���汾Ϊ1�����ֽ���д�룻
				ǰ��ƫ��λ��8��VK_UUID_SIZE(16)�ֽڱ�ʾ��ʾΪUUID�Ĳ��ύID����Ψһ�ر�ʶ����������Щ��֤�������֤��İ汾
		*/

		//����һ��VkValidationCacheEXT,validationCache���������ڵ���Ӧ�ó��������к��ڶ������֮�������ڲ���֤�Ľ����
		VkValidationCacheEXT validationCache{VK_NULL_HANDLE};
		VkValidationCacheCreateInfoEXT validationCacheCreateInfo{};
		validationCacheCreateInfo.sType = VK_STRUCTURE_TYPE_VALIDATION_CACHE_CREATE_INFO_EXT;
		validationCacheCreateInfo.flags = 0;//����
		validationCacheCreateInfo.pNext = nullptr;
		validationCacheCreateInfo.initialDataSize = validationDataSize;//pInitialData���ֽ���Ŀ�����Ϊ0����pInitialData��ʼΪ��
		validationCacheCreateInfo.pInitialData = validationData.data();//��һ��ָ��֮ǰ��ȡ��validation cache�����ݣ�������ݺ͵�ǰdevice��ƥ�䣬��validation cache����ᱻ��ʼ��Ϊ�գ����initialDataSizeΪ0����pInitialData�е����ݱ�����,�����Ϊ0��������pInitialData��Сƥ���ұ�������vkGetValidationCacheDataEXT��õ�����



		VK_DEVICE_FUNCTION_GET_AND_CALL(device, vkCreateValidationCacheEXT, device, &validationCacheCreateInfo, nullptr, &validationCache);
		

		//�ϲ�VkValidationCacheEXT
		VK_DEVICE_FUNCTION_GET_AND_CALL(device, vkMergeValidationCachesEXT, device, validationCache, 1, &otherValidationCache);

		//����VkValidationCacheEXT
		VK_DEVICE_FUNCTION_GET_AND_CALL(device, vkDestroyValidationCacheEXT, device, otherValidationCache, nullptr);
		
		VkShaderModuleValidationCacheCreateInfoEXT shaderModuleValidationCacheCreateInfo{};
		shaderModuleValidationCacheCreateInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_VALIDATION_CACHE_CREATE_INFO_EXT;
		shaderModuleValidationCacheCreateInfo.pNext = nullptr;
		shaderModuleValidationCacheCreateInfo.validationCache  = validationCache;//

	shaderModuleCreateInfo.pNext = &shaderModuleValidationCacheCreateInfo;//���԰���VkShaderModuleValidationCacheCreateInfoEXT��������shader��У������VkValidationCacheEXT��
	shaderModuleCreateInfo.codeSize = 0;
	shaderModuleCreateInfo.pCode = nullptr;
	shaderModuleCreateInfo.flags = 0;//Ŀǰû��ʹ��
	/*
	�Ϸ��÷���
	1.pCodeָ��һ��SPIR-V��ʽ������
	2.���pCode��SPIR-V��ʽ�����ݣ��򣺣�1��codeSize������4�ı���
									   ��2��pCodeָ��ı����ǺϷ���SPIR-V��ʽ�����ݣ���Khronos SPIR-V Specification �ж���ĸ�ʽ����
									   ��3��pCode���븽�ӵ� SPIR-V Environment��¼�� Validation Rules within a Module������������֤������
	                                                    
									   ��4��pCode��������shader��spirv����capability
									   ��6��pCode��������API��֧�ֵ�capability�� ��SPIR-V Environment��¼�е� Capabilities�н�������
									   ��7��pCode�������о���SPIR-V Environment��¼��capability����������������Ӧ������
									   ��8��pCode��������API��֧�ֵ���չ����SPIR-V Environment��¼�е�  Extension �н�������
									   ��9����� VK_NV_glsl_shader ��չû�п�������pCode����ΪSPIR-V��ʽ������
									   ��10�����pCode��glsl���룬����glsl���������� GL_KHR_vulkan_glsl ����������Ҫ��
									   ��11��codeSize�������0
									   ��12��pCode������ codeSize / 4  ��uint32_t������
	
	*/


	vkCreateShaderModule(device, &shaderModuleCreateInfo, nullptr, &shaderModule);//shaderModule�����ú����������ڵ�Ϳ��Ա�ʹ�ã���� maintenance5�������򴴽�shaderModule��ᱻ���ԣ�ֻ��Ҫ
			//�ڴ���pipeline��ʱ���ڴ�����Ϣ�е�pNext�����VkPipelineShaderStageCreateInfo����

	//shader module ��ʶ��
	//shader module ���Լ��ı�ʶ��
	VkShaderModuleIdentifierEXT shaderModuleIdentifier{};
	shaderModuleIdentifier.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_IDENTIFIER_EXT;
	shaderModuleIdentifier.pNext = nullptr;
	shaderModuleIdentifier.identifierSize;//���ص�identifier�Ĵ�С�� 0 < identifierSize <=  VK_MAX_SHADER_MODULE_IDENTIFIER_SIZE_EXT
	shaderModuleIdentifier.identifier;//���صı�ʶ��

	VK_DEVICE_FUNCTION_GET_AND_CALL(device, vkGetShaderModuleCreateInfoIdentifierEXT, device, &shaderModuleCreateInfo, &shaderModuleIdentifier);//�����ʶ��ֻ��������ͬ��device�Һ�����ͬ��shaderModuleIdentifierAlgorithmUUID������²������壬
	//��ͬ��shaderModuleCreateInfo���ܻ᷵����ͬ��VkShaderModuleIdentifierEXT����ΪVkShaderModuleIdentifierEXT�ķ���ȡ����shaderModuleCreateInfo�Լ�shaderModuleIdentifierAlgorithmUUID,�ҷ��ص�ֵ�����
	//vkGetShaderModuleIdentifierEXT���ص�ֵ��ͬ���� VkShaderModuleCreateInfo��pNext�н���ָ����



	


	vkDestroyShaderModule(device, shaderModule, nullptr);



}



//shader ��
/*
���� vkCmdBindPipelineΪ VkPipelineBindPoint.�󶨹���״̬������vkCmdBindShadersEXTΪ����״̬��shader


*/


//shader ִ��
/*
shader�ĵ���˳�������δ֪�ģ�Ƭ����ɫ���ĵ���˳���ǹ�դ����˳��
shader stage�Ľ��������е�ǰ״̬����ɫ��ִ�н���֮��

*/


//shader �ڴ����˳��
/*
shader���ڴ����˳���������
*/

//shader �������
/*
ͨ��location��input�Լ�output��ص���Ƕ���������������
*/



//task shader
/*
task shader���ӵ�mesh shader����Ϊ��������ͼ�ι��߽׶���Ҫ��ͼԪ����,��Ҫ��Ϊmesh shader��������
��vkCmdDrawMeshTasksNV�׶�ִ��
�����p672
*/

//mesh shader
/*
mesh shader����Ϊ��������ͼ�ι��߽׶���Ҫ��ͼԪ����,���ͼԪ�����Ķ��������Լ������ϵ���������
��vkCmdDrawMeshTasksNV�׶�ִ��
�����p673
*/


//cluster culling shader
/*
cluster culling shader����ִ��cluster-based culling �Ҳ�������ͼ�ι��߽׶���Ҫ��cluster ��������
��vkCmdDrawClusterHUAWEI�׶�ִ��
�����p673
*/


//vertex shader
/*
vertex shader���������������Լ����������ݲ�������������ص����ݡ�ʹ��ͼԪ��ɫ����ͼ�ιܵ��������һ��������ɫ�������Ҷ�����ɫ���׶�ʼ����ͼ�ιܵ��еĵ�һ����ɫ���׶�
�����p674
*/

//tessellation control shader
/*
tessellation control shader������ȡinput patch�����output patch����input patch�ϵ��ò����һ�����Ƶ��Լ�output patch��������ݡ�
���Ƶ���Ŀ����ͨ��VkPipelineTessellationStateCreateInfo. patchControlPoints�����û���ͨ������vkCmdSetPatchControlPointsEXT��̬���ã��迪��VK_DYNAMIC_STATE_PATCH_CONTROL_POINTS_EXT������Ҫ extendedDynamicState2PatchControlPoints ���Ի��߸���ɫ�����ã��� 0 < patchControlPoints <= VkPhysicalDeviceLimits::maxTessellationPatchSize����
ִ�д������Զ�����ɫ������������
�����p675
*/


//tessellation evaluation shader
/*
tessellation evaluation shader�����������Ƶ㼰��������ݵ�input patch���Լ����������������ָ꣬ʾ�����ڱ�ϸ�ֵ�patch�е����λ�ã�������������㼰��������ݡ�
ִ�д���ÿһ����tessellator�����Ķ����Լ�����
�����p676
*/

//geometry shader
/*
geometry shader��������һ������ͼԪ�Ķ��������Լ�����ص����ݣ�Ȼ������µ�ͼԪ������صĶ��������Լ������������
ִ�д�������tessellation�׶������ͼԪ������п����ý׶Σ������ڶ�����ɫ��ǰ�Ķ���װ��׶�װ���ͼԪ
�����p677
*/

//fragment shader
/*
fragment shader�����������ߵĵ���fragment�Լ�����ص����ݡ�
�����p677
*/


//compute shader
/*
compute shaderͨ��vkCmdDispatch ���� vkCmdDispatchIndirect���ã�������Դ�ķ�ʽ��ͼ�ι��߷�����Դ����
�����p677
*/


//ray generation shader
/*
ray generation shader������compute shader����Ҫ��ʹ�� pipeline trace ray��p5331�� ���������������
ray generation shaderΪÿһ��ray tracing dispatch����һ��
�����p678
*/

//intersection shader
/*
intersection shaderΪÿ��ray ����ÿ��ͼԪ�����ཻ�����ұ�������ͨ��Ϊany-hit �� closest shaders�ṩ����Զ�ȡ����������������ͨ��,�����޸�ray payload��

�����p678
*/

// any-hit shader
/*
 any-hit shader������ intersection shader�����������ڵ�ǰ [tmin,tmax]�е��ཻray֮��Ȼ���ж��Ƿ������Щ�ཻ������һ�㶼����ܳ���shader������OpIgnoreIntersectionKHR��
 ֻ�ܶ�ȡintersection shader���ɵ����������ҿ��Զ�ȡ���޸�ray payload
�����p678
*/

// closet hit shader
/*
closet hit shader���Ե��� pipeline trace ray �������ݹ�Ľ���ray tracing
ֻ�ܶ�ȡintersection shader���ɵ����������ҿ��Զ�ȡ���޸�ray payload
�����p678
*/


// miss shader
/*
miss shader���Կ��Զ�ȡ���޸�ray payload�ҿ��Ե��� pipeline trace ray �����������µ�ray tracing�������ܷ���intersection shader��������������
miss shader��closet hit shaderû��ray tracing���ཻû���ҵ�ʱִ��
�����p679
*/


// callable shader
/*
callable shader ���Է���callable payload�������ray payload������subroutine ����
�����p679
*/



/*
p679-691���ﲻ���������ĵ�



*/


void ShadersTest::CooperateMatrixsTest()
{
	// Provided by VK_KHR_cooperative_matrix
	typedef enum VkComponentTypeKHR {
		VK_COMPONENT_TYPE_FLOAT16_KHR = 0,//��Ӧ SPIR-V OpTypeFloat 16.
		VK_COMPONENT_TYPE_FLOAT32_KHR = 1,//��Ӧ SPIR-V OpTypeFloat 32.
		VK_COMPONENT_TYPE_FLOAT64_KHR = 2,//��Ӧ SPIR-V OpTypeFloat 64.
		VK_COMPONENT_TYPE_SINT8_KHR = 3,//��Ӧ SPIR-V  OpTypeInt 8 1.
		VK_COMPONENT_TYPE_SINT16_KHR = 4,//��Ӧ SPIR-V  OpTypeInt 16 1.
		VK_COMPONENT_TYPE_SINT32_KHR = 5,//��Ӧ SPIR-V OpTypeInt 32 1.
		VK_COMPONENT_TYPE_SINT64_KHR = 6,//��Ӧ SPIR-V OpTypeInt 64 1.
		VK_COMPONENT_TYPE_UINT8_KHR = 7,//��Ӧ SPIR-V  OpTypeInt 8 0.
		VK_COMPONENT_TYPE_UINT16_KHR = 8,//��Ӧ SPIR-V  OpTypeInt 16 0.
		VK_COMPONENT_TYPE_UINT32_KHR = 9,//��Ӧ SPIR-V  OpTypeInt 32 0.
		VK_COMPONENT_TYPE_UINT64_KHR = 10,//��Ӧ SPIR-V  OpTypeInt 64 0.
		// Provided by VK_NV_cooperative_matrix
		VK_COMPONENT_TYPE_FLOAT16_NV = VK_COMPONENT_TYPE_FLOAT16_KHR,
		// Provided by VK_NV_cooperative_matrix
		VK_COMPONENT_TYPE_FLOAT32_NV = VK_COMPONENT_TYPE_FLOAT32_KHR,
		// Provided by VK_NV_cooperative_matrix
		VK_COMPONENT_TYPE_FLOAT64_NV = VK_COMPONENT_TYPE_FLOAT64_KHR,
		// Provided by VK_NV_cooperative_matrix
		VK_COMPONENT_TYPE_SINT8_NV = VK_COMPONENT_TYPE_SINT8_KHR,
		// Provided by VK_NV_cooperative_matrix
		VK_COMPONENT_TYPE_SINT16_NV = VK_COMPONENT_TYPE_SINT16_KHR,
		// Provided by VK_NV_cooperative_matrix
		VK_COMPONENT_TYPE_SINT32_NV = VK_COMPONENT_TYPE_SINT32_KHR,
		// Provided by VK_NV_cooperative_matrix
		VK_COMPONENT_TYPE_SINT64_NV = VK_COMPONENT_TYPE_SINT64_KHR,
		// Provided by VK_NV_cooperative_matrix
		VK_COMPONENT_TYPE_UINT8_NV = VK_COMPONENT_TYPE_UINT8_KHR,
		// Provided by VK_NV_cooperative_matrix
		VK_COMPONENT_TYPE_UINT16_NV = VK_COMPONENT_TYPE_UINT16_KHR,
		// Provided by VK_NV_cooperative_matrix
		VK_COMPONENT_TYPE_UINT32_NV = VK_COMPONENT_TYPE_UINT32_KHR,
		// Provided by VK_NV_cooperative_matrix
		VK_COMPONENT_TYPE_UINT64_NV = VK_COMPONENT_TYPE_UINT64_KHR,
	} VkComponentTypeKHR;//���ö������û�ж��壬�����ȶ�����Ϊʾ��
	
	// Provided by VK_KHR_cooperative_matrix
	typedef enum VkScopeKHR {
		VK_SCOPE_DEVICE_KHR = 1,//��Ӧ SPIR-V Device scope.
		VK_SCOPE_WORKGROUP_KHR = 2,//��Ӧ SPIR-V  Workgroup scope.
		VK_SCOPE_SUBGROUP_KHR = 3,//��Ӧ SPIR-V  Subgroup scope.
		VK_SCOPE_QUEUE_FAMILY_KHR = 5,//��Ӧ SPIR-V QueueFamily scope.
		// Provided by VK_NV_cooperative_matrix
		VK_SCOPE_DEVICE_NV = VK_SCOPE_DEVICE_KHR,
		// Provided by VK_NV_cooperative_matrix
		VK_SCOPE_WORKGROUP_NV = VK_SCOPE_WORKGROUP_KHR,
		// Provided by VK_NV_cooperative_matrix
		VK_SCOPE_SUBGROUP_NV = VK_SCOPE_SUBGROUP_KHR,
		// Provided by VK_NV_cooperative_matrix
		VK_SCOPE_QUEUE_FAMILY_NV = VK_SCOPE_QUEUE_FAMILY_KHR,
	} VkScopeKHR;//���ö������û�ж��壬�����ȶ�����Ϊʾ��
	
	// cooperative matrix type��һ�� SPIR-V���ͣ���洢�ͼ��������ھ����ϣ�����������ʵ���п�Խ���ý��д���
	struct VkCooperativeMatrixPropertiesKHR {
		VkStructureType sType;
		void* pNext;
		uint32_t MSize;
		uint32_t NSize;
		uint32_t KSize;
		VkComponentTypeKHR AType;
		VkComponentTypeKHR BType;
		VkComponentTypeKHR CType;
		VkComponentTypeKHR ResultType;
		VkBool32 saturatingAccumulation;//ָʾ����OpCooperativeMatrixMulAddKHR��SaturatingAccumulation�Ƿ���ڡ�
		VkScopeKHR scope;
	};//������ݽṹû�ж��壬�����ȶ�����Ϊʾ��
	auto vkGetPhysicalDeviceCooperativeMatrixPropertiesKHR = [](
		VkPhysicalDevice physicalDevice,
		uint32_t* pPropertyCount,
		VkCooperativeMatrixPropertiesKHR* pProperties) {
			return VK_SUCCESS;
	}; //����ӿ�û�ж��壬�����ȶ�����Ϊʾ��


	//�÷�
	uint32_t propertyCount = 0;
	std::vector<VkCooperativeMatrixPropertiesKHR> properties;
	vkGetPhysicalDeviceCooperativeMatrixPropertiesKHR(physicalDevice, &propertyCount, nullptr);
	properties.resize(propertyCount);
	vkGetPhysicalDeviceCooperativeMatrixPropertiesKHR(physicalDevice, &propertyCount, properties.data());


	// Provided by VK_NV_cooperative_matrix
	typedef struct VkCooperativeMatrixPropertiesNV {
		VkStructureType sType;
		void* pNext;
		uint32_t MSize;
		uint32_t NSize;
		uint32_t KSize;
		VkComponentTypeNV AType;
		VkComponentTypeNV BType;
		VkComponentTypeNV CType;
		VkComponentTypeNV DType;
		VkScopeNV scope;
	} VkCooperativeMatrixPropertiesNV;//������ݽṹû�ж��壬�����ȶ�����Ϊʾ��
	auto vkGetPhysicalDeviceCooperativeMatrixPropertiesNV = [](
		VkPhysicalDevice physicalDevice,
		uint32_t* pPropertyCount,
		VkCooperativeMatrixPropertiesKHR* pProperties) {
			return VK_SUCCESS;
	}; //����ӿ�û�ж��壬�����ȶ�����Ϊʾ��

	//�÷�
	uint32_t propertyCountNV = 0;
	std::vector<VkCooperativeMatrixPropertiesKHR> propertiesNV;
	vkGetPhysicalDeviceCooperativeMatrixPropertiesKHR(physicalDevice, &propertyCountNV, nullptr);
	propertiesNV.resize(propertyCountNV);
	vkGetPhysicalDeviceCooperativeMatrixPropertiesKHR(physicalDevice, &propertyCountNV, propertiesNV.data());
}

void ShadersTest::CUDAModuleTest()
{
	//CUDAģ��������һЩ�ں˴��룬���ұ��빫������һ��������ڵ�
	struct VkCudaModuleNV_T {};//û�ж��壬���ﶨ����Ϊʾ��
	VK_DEFINE_NON_DISPATCHABLE_HANDLE(VkCudaModuleNV)
		// Provided by VK_NV_cuda_kernel_launch
	typedef struct VkCudaModuleCreateInfoNV {
		VkStructureType sType;
		const void* pNext;
		size_t dataSize;//pData�ĳ���
		const void* pData;//ָ��CUDA code��ָ�� PTX
	} VkCudaModuleCreateInfoNV;//û�ж��壬���ﶨ����Ϊʾ��
	
	// Provided by VK_NV_cuda_kernel_launch
	auto vkCreateCudaModuleNV = [](
			VkDevice device,
			const VkCudaModuleCreateInfoNV* pCreateInfo,
			const VkAllocationCallbacks* pAllocator,
			VkCudaModuleNV* pModule) -> VkResult {
	
		return VK_SUCCESS;
	};//û�ж��壬���ﶨ����Ϊʾ��
	

	VkCudaModuleNV cudaModule{};
	VkCudaModuleCreateInfoNV cudaModuleCreateInfo{};
	cudaModuleCreateInfo.sType = VK_STRUCTURE_TYPE_MAX_ENUM;//û�иýṹ������Ͷ�������������Ϊ�Ƿ�ֵ
	cudaModuleCreateInfo.pNext = nullptr;
	cudaModuleCreateInfo.dataSize = 0;
	cudaModuleCreateInfo.pData = nullptr;

	vkCreateCudaModuleNV(device, &cudaModuleCreateInfo, nullptr, &cudaModule);



	//cuda ������VkCudaFunctionNV��ʾ��

	struct VkCudaFunctionNV_T {};//û�ж��壬���ﶨ����Ϊʾ��

	// Provided by VK_NV_cuda_kernel_launch
	VK_DEFINE_NON_DISPATCHABLE_HANDLE(VkCudaFunctionNV)


	//����cuda function
	// Provided by VK_NV_cuda_kernel_launch
	typedef struct VkCudaFunctionCreateInfoNV {
		VkStructureType sType;
		const void* pNext;
		VkCudaModuleNV module;//ָ����ǰfunction���ڵ�cuda ģ��
		const char* pName;//��һ���Կս�β��UTF-8�ַ��������а����˽׶ε���ɫ����ڵ�����ơ�
	} VkCudaFunctionCreateInfoNV;
	// Provided by VK_NV_cuda_kernel_launch
	auto vkCreateCudaFunctionNV = [](
			VkDevice device,
			const VkCudaFunctionCreateInfoNV* pCreateInfo,
			const VkAllocationCallbacks* pAllocator,
			VkCudaFunctionNV* pFunction) ->VkResult {

		return VK_SUCCESS;
	};

	VkCudaFunctionNV cudaFunc{};
	VkCudaFunctionCreateInfoNV cudaFuncCreateInfo{};
	cudaFuncCreateInfo.sType = VK_STRUCTURE_TYPE_MAX_ENUM;
	cudaFuncCreateInfo.pNext = nullptr;
	cudaFuncCreateInfo.module = cudaModule;
	cudaFuncCreateInfo.pName = "main";
	vkCreateCudaFunctionNV(device, &cudaFuncCreateInfo, nullptr, &cudaFunc);


	//��ȡcuda�������ݣ������������ٺ���CUDA�ĳ�ʼ��
	// Provided by VK_NV_cuda_kernel_launch
	auto vkGetCudaModuleCacheNV = [](
		VkDevice device,
		VkCudaModuleNV module,
		size_t* pCacheSize,
		void* pCacheData) ->VkResult {

			return VK_SUCCESS;
	};

	size_t cudaDataSize = 0;
	std::vector<char> cudaCacheData;
	vkGetCudaModuleCacheNV(device, cudaModule, &cudaDataSize, nullptr);
	cudaCacheData.resize(cudaDataSize);
	vkGetCudaModuleCacheNV(device, cudaModule, &cudaDataSize, cudaCacheData.data());//���صĻ�������Ժ����ڽ�һ����ʼ��CUDAģ�飬ͨ����ʹ�� vkCreateCudaModuleNV ʱ����������������PTX���롣




	//����cuda module
	// Provided by VK_NV_cuda_kernel_launch
	auto vkDestroyCudaFunctionNV = [](
		VkDevice device,
		VkCudaFunctionNV function,
		const VkAllocationCallbacks* pAllocator) {
	};
	vkDestroyCudaFunctionNV(device, cudaFunc, nullptr);


	//cuda��vulkan��ʹ�õ����Ʋ鿴�ĵ�p711�����ﲻ������



}






NS_TEST_END