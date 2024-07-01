#include "PipelineTest.h"

NS_TEST_BEGIN
/*

���ֹ��ߵĴ�����
	compute



*/







PipelineTest::PipelineTest()
{
}
















void PipelineTest::run()
{
}

PipelineTest::~PipelineTest()
{
}

struct ComputePipelineCreateInfoExt {
	VkComputePipelineIndirectBufferInfoNV computePipelineIndirectBufferInfoNV{};
	VkPipelineCompilerControlCreateInfoAMD computePipelineControlCreateInfoAMD{};
	VkPipelineCreateFlags2CreateInfoKHR pipelineCreateFlags2CreateInfoKHR{  };
	VkPipelineCreationFeedbackCreateInfo pipelineCreationFeedbackCreateInfo{};
	VkPipelineRobustnessCreateInfoEXT pipelineRobustnessCreateInfoEXT{};
	VkSubpassShadingPipelineCreateInfoHUAWEI subpassShadingPipelineCreateInfoHUAWEI{};

	ComputePipelineCreateInfoExt() {
		Init();
	}
	void Init() {

	}
};



void PipelineTest::ComputePipelineCreateTest()
{
	VkPipeline computePipeline{ VK_NULL_HANDLE };

	VkPipelineLayout computeLayout{ VK_NULL_HANDLE };


		//stage
		VkPipelineShaderStageCreateInfo computeStageInfo{};
		computeStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
		computeStageInfo.pNext = nullptr;//��� shaderModuleIdentifier���Կ����������ͨ������һ��identifierSize��Ϊ0��VkPipelineShaderStageModuleIdentifierCreateInfoEXT�����Ե�ǰstage����ɫ�����룬ʹ�����ַ�ʽ���� VK_PIPELINE_COMPILE_REQUIRED ��������ʧ�ܣ����������ַ�ʽ������VK_PIPELINE_CREATE_LIBRARY_BIT_KHR��pipeline
		computeStageInfo.flags = 0;
		computeStageInfo.module = VK_NULL_HANDLE;//�����ΪVK_NULL_HANDLE����Ϊһ��VkShaderModule����, ָ����ڵ�������ڵ�module�����ΪVK_NULL_HANDLE������Ҫ����һ����VkPipelineShaderStageCreateInfo.pNext�а���VkShaderModuleCreateInfo��
		

		computeStageInfo.pName = "main";//��ں���
		computeStageInfo.stage = VK_SHADER_STAGE_COMPUTE_BIT;
			VkSpecializationInfo specializationInfo{};
			specializationInfo.dataSize = 0;
			specializationInfo.mapEntryCount = 1;
			specializationInfo.pData = VK_NULL_HANDLE;
				VkSpecializationMapEntry mapEntry{};
				mapEntry.constantID = 0;
				mapEntry.offset = 0;
				mapEntry.size = 0;
			specializationInfo.pMapEntries = &mapEntry;
		computeStageInfo.pSpecializationInfo = &specializationInfo;
		/*
		VkPipelineShaderStageCreateInfo��Ч�÷���
		1.���ĳЩ��ɫ������û�п�������stage����Ϊ��Ӧ��ֵ����geometryShader����û������stage�Ͳ���ΪVK_SHADER_STAGE_GEOMETRY_BIT��
		2.stage ����Ϊ VK_SHADER_STAGE_ALL_GRAPHICS, �� VK_SHADER_STAGE_ALL
		3.pName ������ module ����ڵ��������ִ��ģ��Ҫ�� stage ƥ��
		4.��� entry point ����ӿڴ������κ���ClipDistance BuiltIn �����ı���, ����Щ������ɵ������С���ܴ���VkPhysicalDeviceLimits::maxClipDistances
		5.��� entry point ����ӿڴ������κ���CullDistance BuiltIn �����ı���, ����Щ������ɵ������С���ܴ���VkPhysicalDeviceLimits::maxCullDistances
		6.��� entry point ����ӿڴ������κ���ClipDistance BuiltIn �Լ�CullDistance BuiltIn �����ı���, ����Щ������ɵ������С���ܴ���VkPhysicalDeviceLimits::maxCombinedClipAndCullDistances
		7.��� entry point ����ӿڴ������κ���SampleMask BuiltIn �����ı���, ����Щ������ɵ������С���ܴ���VkPhysicalDeviceLimits::maxSampleMaskWords
		8.��� stage Ϊ VK_SHADER_STAGE_TESSELLATION_CONTROL_BIT ���� VK_SHADER_STAGE_TESSELLATION_EVALUATION_BIT, �� entry point ����һ�� OpExecutionMode ָ��ָ��OutputVertices�� patch size , ��  0 < patch size <=VkPhysicalDeviceLimits::maxTessellationPatchSize
		9.��� stage Ϊ VK_SHADER_STAGE_GEOMETRY_BIT,  �� entry point ���뺬��һ�� OpExecutionMode ָ��ָ�����Ķ�����������������������0��С�ڵ���VkPhysicalDeviceLimits::maxGeometryOutputVertices
		*/

	VkComputePipelineCreateInfo computePipelineCreateInfo{};
	computePipelineCreateInfo.sType = VK_STRUCTURE_TYPE_COMPUTE_PIPELINE_CREATE_INFO;
		ComputePipelineCreateInfoExt computePipelineCreateInfoExgt{};
		

	computePipelineCreateInfo.pNext = &computePipelineCreateInfoExgt.computePipelineIndirectBufferInfoNV;//���԰���VkPipelineCreateFlags2CreateInfoKHR
	computePipelineCreateInfo.layout = computeLayout;
	computePipelineCreateInfo.stage = computeStageInfo;
	computePipelineCreateInfo.flags = 0;//ָ��pipeline��α�����
	computePipelineCreateInfo.basePipelineIndex = 0;//ָ��Դ�ڵ�pipeline����pCreateInfos�е�����
	computePipelineCreateInfo.basePipelineHandle = VK_NULL_HANDLE;//ָ��Դ���ĸ�pipeline
	/*
	1.���pNext�в���VkPipelineCreateFlags2CreateInfoKHR����flags������һ���Ϸ��� VkPipelineCreateFlagBits�����ֵ
	2.��� flags ���� VK_PIPELINE_CREATE_DERIVATIVE_BIT ��:
													��1����� basePipelineIndex Ϊ -1,basePipelineHandle ������һ����Ч�� compute VkPipeline ���
													��2����� basePipelineHandle ΪVK_NULL_HANDLE, basePipelineIndex �����ǵ�ǰ��������vkCreateComputePipelines��pCreateInfos ������һ����Ч������ֵ
													��3��basePipelineIndex ����Ϊ -1���� basePipelineHandle ����Ϊ VK_NULL_HANDLE
	3.���push constant ����shader��������,��layout�е� push constant�� range �����shader�� stage �Լ� rangeƥ��
	4.��� resource variables ��shader��������,��  
													��1��layout�е� descriptor slot ����ƥ��shader stage
													��2�����layout�е� descriptor type����VK_DESCRIPTOR_TYPE_MUTABLE_EXT,�� descriptor slot����ƥ�� descriptor slot
	5.��� resource variables ��shader������Ϊarray����layout�е� descriptor slot����ƥ�� descriptor count
	6.flags ���ܰ��� VK_PIPELINE_CREATE_RAY_TRACING_NO_NULL_ANY_HIT_SHADERS_BIT_KHR��VK_PIPELINE_CREATE_RAY_TRACING_NO_NULL_CLOSEST_HIT_SHADERS_BIT_KHR��
													VK_PIPELINE_CREATE_RAY_TRACING_NO_NULL_MISS_SHADERS_BIT_KHR��VK_PIPELINE_CREATE_RAY_TRACING_NO_NULL_INTERSECTION_SHADERS_BIT_KHR��
													VK_PIPELINE_CREATE_RAY_TRACING_SKIP_TRIANGLES_BIT_KHR��VK_PIPELINE_CREATE_RAY_TRACING_SKIP_AABBS_BIT_KHR��
													VK_PIPELINE_CREATE_RAY_TRACING_SHADER_GROUP_HANDLE_CAPTURE_REPLAY_BIT_KHR���Լ�VK_PIPELINE_CREATE_RAY_TRACING_ALLOW_MOTION_BIT_NV��
													VK_PIPELINE_CREATE_RAY_TRACING_OPACITY_MICROMAP_BIT_EXT �Լ� VK_PIPELINE_CREATE_RAY_TRACING_DISPLACEMENT_MICROMAP_BIT_NV
	7.���VkPhysicalDeviceDeviceGeneratedCommandsComputeFeaturesNV::deviceGeneratedComputePipelinesû�п�����flags���ܰ���VK_PIPELINE_CREATE_INDIRECT_BINDABLE_BIT_NV
	8.��� flags ���� VK_PIPELINE_CREATE_INDIRECT_BINDABLE_BIT_NV, �� pNext �������һ����Ч�� VkComputePipelineIndirectBufferInfoNVָ�� pipeline��s metadata ��������ĵ�ַ
	9.��� pipelineCreationCacheControl ����û�п���, flags ���ܰ���VK_PIPELINE_CREATE_FAIL_ON_PIPELINE_COMPILE_REQUIRED_BIT ���� VK_PIPELINE_CREATE_EARLY_RETURN_ON_FAILURE_BIT
	10. stage�е�stage ����Ϊ VK_SHADER_STAGE_COMPUTE_BIT
	11.��stage��ʶ����ڵ���ɸýṹ��ʶ������״̬����ɫ�����������ѭ�� Shader Interfaces�½��������Ĺܵ����ӹ���
	12.compute shader �׶���layout�����Ŀ��Է��ʵ���Դ������С�ڻ����VkPhysicalDeviceLimits::maxPerStageResources
	13.��� shaderEnqueue û�п���, flags ���ܰ��� VK_PIPELINE_CREATE_LIBRARY_BIT_KHR
	14.��� flags û�а��� VK_PIPELINE_CREATE_LIBRARY_BIT_KHR, ��stage���Ե� shader�Ͳ������� ShaderEnqueueAMDX capability
	15.��� VkPipelineCreationFeedbackCreateInfo::pipelineStageCreationFeedbackCount ��Ϊ 0�ͱ���Ϊ1

	*/

	//VkPipelineCreateFlags2CreateInfoKHR
	VkPipelineCreateFlags2CreateInfoKHR& pipelineCreateFlags2CreateInfoKHR = computePipelineCreateInfoExgt.pipelineCreateFlags2CreateInfoKHR;
	pipelineCreateFlags2CreateInfoKHR.sType = VK_STRUCTURE_TYPE_PIPELINE_CREATE_FLAGS_2_CREATE_INFO_KHR;
	//pipelineCreateFlags2CreateInfoKHR.pNext = nullptr;//�Ѿ����Ӻ������ﲻ������
	pipelineCreateFlags2CreateInfoKHR.flags = VK_PIPELINE_CREATE_2_ALLOW_DERIVATIVES_BIT_KHR;



	vkCreateComputePipelines(device, VK_NULL_HANDLE, 1, &computePipelineCreateInfo, nullptr, &computePipeline);
	/*
	�Ϸ��÷���
	1.���pCreateInfos�е�ĳ��Ԫ�ص�flags����VK_PIPELINE_CREATE_DERIVATIVE_BIT����
													��1�������basePipelineIndex��Ϊ-1����basePipelineIndex����С�ڵ�ǰԪ����pCreateInfos�е�����ֵ
													��1��basePipelineHandle�Ĵ���flags���뺬�� VK_PIPELINE_CREATE_ALLOW_DERIVATIVES_BIT
	2.���pipelineCache �� VK_PIPELINE_CACHE_CREATE_EXTERNALLY_SYNCHRONIZED_BIT��־����,������ pipelineCache ����Ҫ�����ⲿͬ��--���ⲿ���߳�ͬ����
	
	*/

}


























NS_TEST_END