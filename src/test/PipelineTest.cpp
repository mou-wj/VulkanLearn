#include "PipelineTest.h"

NS_TEST_BEGIN
/*

多种管线的创建：
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
		computeStageInfo.pNext = nullptr;//如果 shaderModuleIdentifier特性开启，则可以通过包含一个identifierSize不为0的VkPipelineShaderStageModuleIdentifierCreateInfoEXT来忽略当前stage的着色器代码，使用这种方式会以 VK_PIPELINE_COMPILE_REQUIRED 创建管线失败，可以用这种方式创建含VK_PIPELINE_CREATE_LIBRARY_BIT_KHR的pipeline
		computeStageInfo.flags = 0;
		computeStageInfo.module = VK_NULL_HANDLE;//如果不为VK_NULL_HANDLE，则为一个VkShaderModule对象, 指明入口点代码所在的module，如果为VK_NULL_HANDLE，则需要包含一个在VkPipelineShaderStageCreateInfo.pNext中包含VkShaderModuleCreateInfo，
		

		computeStageInfo.pName = "main";//入口函数
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
		VkPipelineShaderStageCreateInfo有效用法：
		1.如果某些着色器特性没有开启，则stage不能为对应的值，如geometryShader特性没开启，stage就不能为VK_SHADER_STAGE_GEOMETRY_BIT等
		2.stage 不能为 VK_SHADER_STAGE_ALL_GRAPHICS, 或 VK_SHADER_STAGE_ALL
		3.pName 必须是 module 中入口点的名字且执行模型要和 stage 匹配
		4.如果 entry point 在其接口处包含任何以ClipDistance BuiltIn 描述的变量, 则这些变量组成的数组大小不能大于VkPhysicalDeviceLimits::maxClipDistances
		5.如果 entry point 在其接口处包含任何以CullDistance BuiltIn 描述的变量, 则这些变量组成的数组大小不能大于VkPhysicalDeviceLimits::maxCullDistances
		6.如果 entry point 在其接口处包含任何以ClipDistance BuiltIn 以及CullDistance BuiltIn 描述的变量, 则这些变量组成的数组大小不能大于VkPhysicalDeviceLimits::maxCombinedClipAndCullDistances
		7.如果 entry point 在其接口处包含任何以SampleMask BuiltIn 描述的变量, 则这些变量组成的数组大小不能大于VkPhysicalDeviceLimits::maxSampleMaskWords
		8.如果 stage 为 VK_SHADER_STAGE_TESSELLATION_CONTROL_BIT 或者 VK_SHADER_STAGE_TESSELLATION_EVALUATION_BIT, 且 entry point 含有一个 OpExecutionMode 指令指明OutputVertices的 patch size , 则  0 < patch size <=VkPhysicalDeviceLimits::maxTessellationPatchSize
		9.如果 stage 为 VK_SHADER_STAGE_GEOMETRY_BIT,  则 entry point 必须含有一个 OpExecutionMode 指令指明最大的顶点输出个数，该数必须大于0且小于等于VkPhysicalDeviceLimits::maxGeometryOutputVertices
		*/

	VkComputePipelineCreateInfo computePipelineCreateInfo{};
	computePipelineCreateInfo.sType = VK_STRUCTURE_TYPE_COMPUTE_PIPELINE_CREATE_INFO;
		ComputePipelineCreateInfoExt computePipelineCreateInfoExgt{};
		

	computePipelineCreateInfo.pNext = &computePipelineCreateInfoExgt.computePipelineIndirectBufferInfoNV;//可以包含VkPipelineCreateFlags2CreateInfoKHR
	computePipelineCreateInfo.layout = computeLayout;
	computePipelineCreateInfo.stage = computeStageInfo;
	computePipelineCreateInfo.flags = 0;//指明pipeline如何被创建
	computePipelineCreateInfo.basePipelineIndex = 0;//指明源于的pipeline的在pCreateInfos中的索引
	computePipelineCreateInfo.basePipelineHandle = VK_NULL_HANDLE;//指明源于哪个pipeline
	/*
	1.如果pNext中不含VkPipelineCreateFlags2CreateInfoKHR，则flags必须是一个合法的 VkPipelineCreateFlagBits的组合值
	2.如果 flags 包含 VK_PIPELINE_CREATE_DERIVATIVE_BIT 则:
													（1）如果 basePipelineIndex 为 -1,basePipelineHandle 必须是一个有效的 compute VkPipeline 句柄
													（2）如果 basePipelineHandle 为VK_NULL_HANDLE, basePipelineIndex 必须是当前创建命令vkCreateComputePipelines中pCreateInfos 参数的一个有效的索引值
													（3）basePipelineIndex 必须为 -1或者 basePipelineHandle 必须为 VK_NULL_HANDLE
	3.如果push constant 块在shader中声明了,则layout中的 push constant的 range 必须和shader的 stage 以及 range匹配
	4.如果 resource variables 在shader中声明了,则  
													（1）layout中的 descriptor slot 必须匹配shader stage
													（2）如果layout中的 descriptor type不是VK_DESCRIPTOR_TYPE_MUTABLE_EXT,则 descriptor slot必须匹配 descriptor slot
	5.如果 resource variables 在shader中声明为array，则layout中的 descriptor slot必须匹配 descriptor count
	6.flags 不能包含 VK_PIPELINE_CREATE_RAY_TRACING_NO_NULL_ANY_HIT_SHADERS_BIT_KHR，VK_PIPELINE_CREATE_RAY_TRACING_NO_NULL_CLOSEST_HIT_SHADERS_BIT_KHR，
													VK_PIPELINE_CREATE_RAY_TRACING_NO_NULL_MISS_SHADERS_BIT_KHR，VK_PIPELINE_CREATE_RAY_TRACING_NO_NULL_INTERSECTION_SHADERS_BIT_KHR，
													VK_PIPELINE_CREATE_RAY_TRACING_SKIP_TRIANGLES_BIT_KHR，VK_PIPELINE_CREATE_RAY_TRACING_SKIP_AABBS_BIT_KHR，
													VK_PIPELINE_CREATE_RAY_TRACING_SHADER_GROUP_HANDLE_CAPTURE_REPLAY_BIT_KHR，以及VK_PIPELINE_CREATE_RAY_TRACING_ALLOW_MOTION_BIT_NV，
													VK_PIPELINE_CREATE_RAY_TRACING_OPACITY_MICROMAP_BIT_EXT 以及 VK_PIPELINE_CREATE_RAY_TRACING_DISPLACEMENT_MICROMAP_BIT_NV
	7.如果VkPhysicalDeviceDeviceGeneratedCommandsComputeFeaturesNV::deviceGeneratedComputePipelines没有开启，flags不能包含VK_PIPELINE_CREATE_INDIRECT_BINDABLE_BIT_NV
	8.如果 flags 包含 VK_PIPELINE_CREATE_INDIRECT_BINDABLE_BIT_NV, 则 pNext 必须包含一个有效的 VkComputePipelineIndirectBufferInfoNV指明 pipeline’s metadata 将被保存的地址
	9.如果 pipelineCreationCacheControl 特性没有开启, flags 不能包含VK_PIPELINE_CREATE_FAIL_ON_PIPELINE_COMPILE_REQUIRED_BIT 或者 VK_PIPELINE_CREATE_EARLY_RETURN_ON_FAILURE_BIT
	10. stage中的stage 必须为 VK_SHADER_STAGE_COMPUTE_BIT
	11.由stage标识的入口点和由该结构标识的其他状态的着色器代码必须遵循在 Shader Interfaces章节中描述的管道链接规则
	12.compute shader 阶段在layout声明的可以访问的资源数必须小于或等于VkPhysicalDeviceLimits::maxPerStageResources
	13.如果 shaderEnqueue 没有开启, flags 不能包含 VK_PIPELINE_CREATE_LIBRARY_BIT_KHR
	14.如果 flags 没有包含 VK_PIPELINE_CREATE_LIBRARY_BIT_KHR, 则stage所对的 shader就不能声明 ShaderEnqueueAMDX capability
	15.如果 VkPipelineCreationFeedbackCreateInfo::pipelineStageCreationFeedbackCount 不为 0就必须为1

	*/

	//VkPipelineCreateFlags2CreateInfoKHR
	VkPipelineCreateFlags2CreateInfoKHR& pipelineCreateFlags2CreateInfoKHR = computePipelineCreateInfoExgt.pipelineCreateFlags2CreateInfoKHR;
	pipelineCreateFlags2CreateInfoKHR.sType = VK_STRUCTURE_TYPE_PIPELINE_CREATE_FLAGS_2_CREATE_INFO_KHR;
	//pipelineCreateFlags2CreateInfoKHR.pNext = nullptr;//已经链接好了这里不再设置
	pipelineCreateFlags2CreateInfoKHR.flags = VK_PIPELINE_CREATE_2_ALLOW_DERIVATIVES_BIT_KHR;



	vkCreateComputePipelines(device, VK_NULL_HANDLE, 1, &computePipelineCreateInfo, nullptr, &computePipeline);
	/*
	合法用法：
	1.如果pCreateInfos中的某个元素的flags包含VK_PIPELINE_CREATE_DERIVATIVE_BIT，则
													（1）如果其basePipelineIndex不为-1，则basePipelineIndex必须小于当前元素在pCreateInfos中的索引值
													（1）basePipelineHandle的创建flags必须含有 VK_PIPELINE_CREATE_ALLOW_DERIVATIVES_BIT
	2.如果pipelineCache 以 VK_PIPELINE_CACHE_CREATE_EXTERNALLY_SYNCHRONIZED_BIT标志创建,主机对 pipelineCache 必须要进行外部同步--如外部多线程同步等
	
	*/

}


























NS_TEST_END