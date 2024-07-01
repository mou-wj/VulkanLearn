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
		computePipelineIndirectBufferInfoNV.sType = VK_STRUCTURE_TYPE_COMPUTE_PIPELINE_INDIRECT_BUFFER_INFO_NV;
		computePipelineIndirectBufferInfoNV.pNext = &computePipelineControlCreateInfoAMD;
		computePipelineControlCreateInfoAMD.sType = VK_STRUCTURE_TYPE_PIPELINE_COMPILER_CONTROL_CREATE_INFO_AMD;
		computePipelineControlCreateInfoAMD.pNext = &pipelineCreateFlags2CreateInfoKHR;
		pipelineCreateFlags2CreateInfoKHR.sType = VK_STRUCTURE_TYPE_PIPELINE_CREATE_FLAGS_2_CREATE_INFO_KHR;
		pipelineCreateFlags2CreateInfoKHR.pNext = &pipelineCreationFeedbackCreateInfo;
		pipelineCreationFeedbackCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_CREATION_FEEDBACK_CREATE_INFO;
		pipelineCreationFeedbackCreateInfo.pNext = &pipelineRobustnessCreateInfoEXT;
		pipelineRobustnessCreateInfoEXT.sType = VK_STRUCTURE_TYPE_PIPELINE_ROBUSTNESS_CREATE_INFO_EXT;
		pipelineRobustnessCreateInfoEXT.pNext = &subpassShadingPipelineCreateInfoHUAWEI;
		subpassShadingPipelineCreateInfoHUAWEI.sType = VK_STRUCTURE_TYPE_SUBPASS_SHADING_PIPELINE_CREATE_INFO_HUAWEI;
		subpassShadingPipelineCreateInfoHUAWEI.pNext = nullptr;
	}
};


struct PipelineShaderStageCreateInfoExt {
	VkDebugUtilsObjectNameInfoEXT debugUtilsObjectNameInfoEXT{};
	VkPipelineRobustnessCreateInfoEXT pipelineRobustnessCreateInfoEXT{};
	VkPipelineShaderStageModuleIdentifierCreateInfoEXT pipelineShaderStageModuleIdentifierCreateInfoEXT{};
	VkPipelineShaderStageNodeCreateInfoAMDX pipelineShaderStageNodeCreateInfoAMDX{};
	VkPipelineShaderStageRequiredSubgroupSizeCreateInfo pipelineShaderStageRequiredSubgroupSizeCreateInfo{};
	VkShaderModuleCreateInfo shaderModuleCreateInfo{};
	VkShaderModuleValidationCacheCreateInfoEXT shaderModuleValidationCacheCreateInfoEXT{};
	PipelineShaderStageCreateInfoExt() {
		Init();
	}
	void Init() {
		debugUtilsObjectNameInfoEXT.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT;
		debugUtilsObjectNameInfoEXT.pNext = &pipelineRobustnessCreateInfoEXT;
		pipelineRobustnessCreateInfoEXT.sType = VK_STRUCTURE_TYPE_PIPELINE_ROBUSTNESS_CREATE_INFO_EXT;
		pipelineRobustnessCreateInfoEXT.pNext = &pipelineShaderStageModuleIdentifierCreateInfoEXT;
		pipelineShaderStageModuleIdentifierCreateInfoEXT.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_MODULE_IDENTIFIER_CREATE_INFO_EXT;
		pipelineShaderStageModuleIdentifierCreateInfoEXT.pNext = &pipelineShaderStageNodeCreateInfoAMDX;
		pipelineShaderStageNodeCreateInfoAMDX.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_NODE_CREATE_INFO_AMDX;
		pipelineShaderStageNodeCreateInfoAMDX.pNext = &pipelineShaderStageRequiredSubgroupSizeCreateInfo;
		pipelineShaderStageRequiredSubgroupSizeCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_REQUIRED_SUBGROUP_SIZE_CREATE_INFO;
		pipelineShaderStageRequiredSubgroupSizeCreateInfo.pNext = &shaderModuleCreateInfo;
		shaderModuleCreateInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
		shaderModuleCreateInfo.pNext = &shaderModuleValidationCacheCreateInfoEXT;
		shaderModuleValidationCacheCreateInfoEXT.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_VALIDATION_CACHE_CREATE_INFO_EXT;
		shaderModuleValidationCacheCreateInfoEXT.pNext = nullptr;


	}


};


void PipelineTest::ComputePipelineCreateTest()
{
	VkPipeline computePipeline{ VK_NULL_HANDLE };

	VkPipelineLayout computeLayout{ VK_NULL_HANDLE };


		//stage
		VkPipelineShaderStageCreateInfo computeStageInfo{};
		computeStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;

			PipelineShaderStageCreateInfoExt pipelineShaderStageCreateInfoExt{};



		computeStageInfo.pNext = &pipelineShaderStageCreateInfoExt.debugUtilsObjectNameInfoEXT;//如果 shaderModuleIdentifier特性开启，则可以通过包含一个identifierSize不为0的VkPipelineShaderStageModuleIdentifierCreateInfoEXT来忽略当前stage的着色器代码，使用这种方式会以 VK_PIPELINE_COMPILE_REQUIRED 创建管线失败，可以用这种方式创建含VK_PIPELINE_CREATE_LIBRARY_BIT_KHR的pipeline
		computeStageInfo.flags = 0;/*
		VK_PIPELINE_SHADER_STAGE_CREATE_ALLOW_VARYING_SUBGROUP_SIZE_BIT:指定SubgroupSize在当前着色器阶段中可能会有所不同。
		VK_PIPELINE_SHADER_STAGE_CREATE_REQUIRE_FULL_SUBGROUPS_BIT:指定必须在任务、网格或计算阶段激活时启动子组大小。
		如果指定了VK_PIPELINE_SHADER_STAGE_CREATE_ALLOW_VARYING_SUBGROUP_SIZE_BIT_EXT和VK_PIPELINE_SHADER_STAGE_CREATE_REQUIRE_FULL_SUBGROUPS_BIT_EXT，并且minSubgroupSize不等于 maxSubgroupSize，并且没有指定必需的子组大小，那么保证本地工作组大小的“X”维是SubgroupSize的倍数的唯一方法是使其成为maxSubgroupSize的倍数。在这些条件下，是完整的子组，但没有任何特定的子组大小。
		*/
		computeStageInfo.module = VK_NULL_HANDLE;//如果不为VK_NULL_HANDLE，则为一个VkShaderModule对象, 指明入口点代码所在的module，如果为VK_NULL_HANDLE，则需要包含一个在VkPipelineShaderStageCreateInfo.pNext中包含VkShaderModuleCreateInfo，
		

		computeStageInfo.pName = "main";//入口函数
		computeStageInfo.stage = VK_SHADER_STAGE_COMPUTE_BIT;/*
			VK_SHADER_STAGE_VERTEX_BIT:  vertex stage.
			VK_SHADER_STAGE_TESSELLATION_CONTROL_BIT :  tessellation control stage.
			VK_SHADER_STAGE_TESSELLATION_EVALUATION_BIT :  tessellation evaluation stage.
			VK_SHADER_STAGE_GEOMETRY_BIT :  geometry stage.
			VK_SHADER_STAGE_FRAGMENT_BIT :  fragment stage.
			VK_SHADER_STAGE_COMPUTE_BIT :  compute stage.
			VK_SHADER_STAGE_ALL_GRAPHICS : 以上的的所有图形着色器阶段的并集
			VK_SHADER_STAGE_ALL :为device支持的所有着色器阶段的并集，包含拓展的着色器管线阶段
			VK_SHADER_STAGE_TASK_BIT_EXT :  task stage.
			VK_SHADER_STAGE_MESH_BIT_EXT :  mesh stage.
			VK_SHADER_STAGE_CLUSTER_CULLING_BIT_HUAWEI :  cluster culling stage.
			VK_SHADER_STAGE_RAYGEN_BIT_KHR :  ray generation stage.
			VK_SHADER_STAGE_ANY_HIT_BIT_KHR :  any-hit stage.
			VK_SHADER_STAGE_CLOSEST_HIT_BIT_KHR :  closest hit stage.
			VK_SHADER_STAGE_MISS_BIT_KHR :  miss stage.
			VK_SHADER_STAGE_INTERSECTION_BIT_KHR :  intersection stage.
			VK_SHADER_STAGE_CALLABLE_BIT_KHR :  callable stage.
		
			*/
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
		9.如果 stage 为 VK_SHADER_STAGE_GEOMETRY_BIT,  则 entry point 必须含有一个 OpExecutionMode 指令指明最大的顶点输出个数，该数必须大于0且小于等于VkPhysicalDeviceLimits::maxGeometryOutputVertices，且必须有一个OpExecutionMode 指令指明着色器调用个数，该数必须大于0且小于等于VkPhysicalDeviceLimits::maxGeometryShaderInvocations
		10.如果 stage 为  VK_SHADER_STAGE_VERTEX_BIT, VK_SHADER_STAGE_TESSELLATION_CONTROL_BIT,VK_SHADER_STAGE_TESSELLATION_EVALUATION_BIT, 或者 VK_SHADER_STAGE_GEOMETRY_BIT, 且 entry point 写到图元的 Layer 上的数据也必须将相同的值写到该图元的所有顶点的Layer上,写到图元的  ViewportIndex 上的数据也必须将相同的值写到该图元的所有顶点的 ViewportIndex上
		11.如果 stage 为 VK_SHADER_STAGE_FRAGMENT_BIT, 则 entry point在任何执行路径下写到 FragDepth，所有的执行路径含有helper invocations的就必须将FragDepth初始化或丢弃，entry point在任何执行路径下写到 FragStencilRefEXT，所有的执行路径含有helper invocations的就必须将FragStencilRefEXT初始化或丢弃
		12.如果 flags 含有 VK_PIPELINE_SHADER_STAGE_CREATE_ALLOW_VARYING_SUBGROUP_SIZE_BIT ，则 subgroupSizeControl 特性必须启用，computeFullSubgroups 特性必须启用
		13.如果 flags 包含 VK_PIPELINE_SHADER_STAGE_CREATE_REQUIRE_FULL_SUBGROUPS_BIT, stage 必须包含 VK_SHADER_STAGE_MESH_BIT_EXT, VK_SHADER_STAGE_TASK_BIT_EXT, 或者 VK_SHADER_STAGE_COMPUTE_BIT其中之一
		14.如果 pNext 中含有一个 VkPipelineShaderStageRequiredSubgroupSizeCreateInfo ， flags 不能含有 VK_PIPELINE_SHADER_STAGE_CREATE_ALLOW_VARYING_SUBGROUP_SIZE_BIT
		15.如果pNext中含有 VkPipelineShaderStageRequiredSubgroupSizeCreateInfo ,  subgroupSizeControl 特性必须开启,  stage 必须是在 requiredSubgroupSizeStages中指定的一个合法的值
		16.如果pNext中含有VkPipelineShaderStageRequiredSubgroupSizeCreateInfo  且 stage 为 VK_SHADER_STAGE_COMPUTE_BIT, VK_SHADER_STAGE_MESH_BIT_EXT, 或者VK_SHADER_STAGE_TASK_BIT_EXT, 则shader的 local workgroup size 必须小于等于  VkPipelineShaderStageRequiredSubgroupSizeCreateInfo::requiredSubgroupSize * maxComputeWorkgroupSubgroups
		17.如果pNext中含有 VkPipelineShaderStageRequiredSubgroupSizeCreateInfo , 且 flags 含有VK_PIPELINE_SHADER_STAGE_CREATE_REQUIRE_FULL_SUBGROUPS_BIT , 则pipeline的X维度的 local workgroup size  必须是VkPipelineShaderStageRequiredSubgroupSizeCreateInfo::requiredSubgroupSize的倍数
		18.如果 flags 同时含有 VK_PIPELINE_SHADER_STAGE_CREATE_REQUIRE_FULL_SUBGROUPS_BIT 以及 VK_PIPELINE_SHADER_STAGE_CREATE_ALLOW_VARYING_SUBGROUP_SIZE_BIT , 则pipeline的X维度的 local workgroup size  必须是maxSubgroupSize的倍数
		19.如果 flags 含有 VK_PIPELINE_SHADER_STAGE_CREATE_REQUIRE_FULL_SUBGROUPS_BIT 且不含 VK_PIPELINE_SHADER_STAGE_CREATE_ALLOW_VARYING_SUBGROUP_SIZE_BIT且pNext中不含 VkPipelineShaderStageRequiredSubgroupSizeCreateInfo , 则pipeline的X维度的 local workgroup size  必须是subgroupSize的倍数
		20.如果 module 使用 OpTypeCooperativeMatrixKHR 指令且 Scope 为 Subgroup 作用域,则pipeline的X维度的 local workgroup size  必须是subgroupSize的倍数
		21.如果 shader module identifier 没有为 stage 指定, 则（1）module 必须是有效的VkShaderModule 如果graphicsPipelineLibrary和maintenance5特性都没有开启
															  （2）module 必须是有效的VkShaderModule 或者 pNext中必须有一个VkShaderModuleCreateInfo
															  （3）pipeline使用的shader code必须是在应用了 pSpecializationInfo（如果有则将specialization常数转换为固定常数）后符合 Khronos SPIR-V Specification描述的合法代码，
		21.如果 为 stage 指定了 shader module identifier，则pNext中不能有VkShaderModuleCreateInfo，module就不能为VK_NULL_HANDLE
		*/



		//VkPipelineShaderStageRequiredSubgroupSizeCreateInfo
		VkPipelineShaderStageRequiredSubgroupSizeCreateInfo& pipelineShaderStageRequiredSubgroupSizeCreateInfo = pipelineShaderStageCreateInfoExt.pipelineShaderStageRequiredSubgroupSizeCreateInfo;
		pipelineShaderStageRequiredSubgroupSizeCreateInfo.requiredSubgroupSize = 1;//指明新创建的pipeline shader stage所需要的subgroup大小， minSubgroupSize <= requiredSubgroupSize(2的指数) <= maxSubgroupSize




	VkComputePipelineCreateInfo computePipelineCreateInfo{};
	computePipelineCreateInfo.sType = VK_STRUCTURE_TYPE_COMPUTE_PIPELINE_CREATE_INFO;
		ComputePipelineCreateInfoExt computePipelineCreateInfoExt{};
		

	computePipelineCreateInfo.pNext = &computePipelineCreateInfoExt.computePipelineIndirectBufferInfoNV;//可以包含VkPipelineCreateFlags2CreateInfoKHR
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
	VkPipelineCreateFlags2CreateInfoKHR& pipelineCreateFlags2CreateInfoKHR = computePipelineCreateInfoExt.pipelineCreateFlags2CreateInfoKHR;
	pipelineCreateFlags2CreateInfoKHR.sType = VK_STRUCTURE_TYPE_PIPELINE_CREATE_FLAGS_2_CREATE_INFO_KHR;
	//pipelineCreateFlags2CreateInfoKHR.pNext = nullptr;//已经链接好了这里不再设置
	pipelineCreateFlags2CreateInfoKHR.flags = VK_PIPELINE_CREATE_2_ALLOW_DERIVATIVES_BIT_KHR;

	//VkSubpassShadingPipelineCreateInfoHUAWEI
	// subpass shading pipeline是一个compute pipeline，只能在subpass的render area范围内调用，允许访问在调用subpass中指定的输入附件，创建一个subpass shading pipeline需要在创建compute pipeline的时候的vkCreateComputePipelines.pNext这个中包含这个结构体
	VkSubpassShadingPipelineCreateInfoHUAWEI& subpassShadingPipelineCreateInfoHUAWEI = computePipelineCreateInfoExt.subpassShadingPipelineCreateInfoHUAWEI;
	subpassShadingPipelineCreateInfoHUAWEI.renderPass = VK_NULL_HANDLE;//指明当前pipeline需要用到的render pass，只能使用和当前pipeline兼容的render pass
	subpassShadingPipelineCreateInfoHUAWEI.subpass = 0;//指明当前pipeline需要用到的subpass的索引

	//subpass shading pipeline的workgroup大小是一个二维向量，其宽度和高度的幂次数为2。宽度和高度的最大数量取决于实现，并且可能因渲染过程中不同的格式和附件的样本计数而有所不同，可以使用以下接口查询。
	VkExtent2D maxWorkGroupSize;
	vkGetDeviceSubpassShadingMaxWorkgroupSizeHUAWEI(device, VK_NULL_HANDLE, &maxWorkGroupSize);



	//VkPipelineRobustnessCreateInfoEXT
	//由于ComputePipelineCreateInfoExt以及PipelineShaderStageCreateInfoExt都含有该结构体，故这里同时设置,这个结构体如果包含在创建pipeline的信息结构体中其作用域就是整个管线对资源的访问（它只影响由创建信息指定的管道的子集），包含在shader stage的创建信息中则作用域只对当前shader stage对资源的访问，如果同时指定，shader stage对资源的访问优先
	VkPipelineRobustnessCreateInfoEXT& pipelineRobustnessCreateInfoEXTForPipeline = computePipelineCreateInfoExt.pipelineRobustnessCreateInfoEXT;
	VkPipelineRobustnessCreateInfoEXT& pipelineRobustnessCreateInfoEXTForShaderStage = pipelineShaderStageCreateInfoExt.pipelineRobustnessCreateInfoEXT;

	pipelineRobustnessCreateInfoEXTForPipeline.images = VK_PIPELINE_ROBUSTNESS_IMAGE_BEHAVIOR_DEVICE_DEFAULT_EXT;//为◦ VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE以及VK_DESCRIPTOR_TYPE_STORAGE_IMAGE所指的资源指明超出资源范围的访问行为
	pipelineRobustnessCreateInfoEXTForPipeline.vertexInputs = VK_PIPELINE_ROBUSTNESS_BUFFER_BEHAVIOR_DEVICE_DEFAULT_EXT;//为input vertex arributes所指的资源指明超出资源范围的访问行为
	pipelineRobustnessCreateInfoEXTForPipeline.storageBuffers = VK_PIPELINE_ROBUSTNESS_BUFFER_BEHAVIOR_DEVICE_DEFAULT_EXT;//为VK_DESCRIPTOR_TYPE_STORAGE_BUFFER，VK_DESCRIPTOR_TYPE_STORAGE_TEXEL_BUFFER以及VK_DESCRIPTOR_TYPE_STORAGE_BUFFER_DYNAMIC所指的资源指明超出资源范围的访问行为
	pipelineRobustnessCreateInfoEXTForPipeline.uniformBuffers = VK_PIPELINE_ROBUSTNESS_BUFFER_BEHAVIOR_DEVICE_DEFAULT_EXT;//为 VK_DESCRIPTOR_TYPE_UNIFORM_TEXEL_BUFFER，VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER，VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC以及VK_DESCRIPTOR_TYPE_INLINE_UNIFORM_BLOCK所指的资源指明超出资源范围的访问行为

	pipelineRobustnessCreateInfoEXTForShaderStage.images = VK_PIPELINE_ROBUSTNESS_IMAGE_BEHAVIOR_DEVICE_DEFAULT_EXT;/*
	 	VK_PIPELINE_ROBUSTNESS_IMAGE_BEHAVIOR_DEVICE_DEFAULT_EXT: 指定此管道阶段遵循在创建此管道的设备上启用的健壮性特性的行为
		VK_PIPELINE_ROBUSTNESS_IMAGE_BEHAVIOR_DISABLED_EXT: 指定此管道阶段对相关资源类型的image访问不能越界
 		VK_PIPELINE_ROBUSTNESS_IMAGE_BEHAVIOR_ROBUST_IMAGE_ACCESS_EXT: 指定此管道阶段对相关image资源类型的越界访问的行为，就好像启用了robustBufferAccess特性一样
 		VK_PIPELINE_ROBUSTNESS_IMAGE_BEHAVIOR_ROBUST_IMAGE_ACCESS_2_EXT: 指定此管道阶段对相关image资源类型的越界访问表现为启用了robustBufferAccess2特性一样
	
	*/
	pipelineRobustnessCreateInfoEXTForShaderStage.vertexInputs = VK_PIPELINE_ROBUSTNESS_BUFFER_BEHAVIOR_DEVICE_DEFAULT_EXT;/*
		VK_PIPELINE_ROBUSTNESS_BUFFER_BEHAVIOR_DEVICE_DEFAULT_EXT: 指定此管道阶段遵循在创建此管道的设备上启用的健壮性特性的行为
 		VK_PIPELINE_ROBUSTNESS_BUFFER_BEHAVIOR_DISABLED_EXTL: 指定此管道阶段对相关资源类型的buffer访问不能越界
 		VK_PIPELINE_ROBUSTNESS_BUFFER_BEHAVIOR_ROBUST_BUFFER_ACCESS_EXT: 指定此管道阶段对相关buffer资源类型的越界访问的行为，就好像启用了robustBufferAccess特性一样
 		VK_PIPELINE_ROBUSTNESS_BUFFER_BEHAVIOR_ROBUST_BUFFER_ACCESS_2_EXT: 指定此管道阶段对相关buffer资源类型的越界访问表现为启用了robustBufferAccess2特性一样
	
	*/
	pipelineRobustnessCreateInfoEXTForShaderStage.storageBuffers = VK_PIPELINE_ROBUSTNESS_BUFFER_BEHAVIOR_DEVICE_DEFAULT_EXT;
	pipelineRobustnessCreateInfoEXTForShaderStage.uniformBuffers = VK_PIPELINE_ROBUSTNESS_BUFFER_BEHAVIOR_DEVICE_DEFAULT_EXT;
	/*
	VkPipelineRobustnessCreateInfoEXT有效用法：
	1.如果 pipelineRobustness 特性 没有开启, 则（1） storageBuffers，uniformBuffers以及 vertexInputs不能是VK_PIPELINE_ROBUSTNESS_BUFFER_BEHAVIOR_DEVICE_DEFAULT_EXT
												  （2）images 不能是VK_PIPELINE_ROBUSTNESS_IMAGE_BEHAVIOR_DEVICE_DEFAULT_EXT
	2.如果 robustImageAccess 特性 没有开启, 则images不能是VK_PIPELINE_ROBUSTNESS_IMAGE_BEHAVIOR_ROBUST_IMAGE_ACCESS_EXT
	3.如果 robustBufferAccess2 特性 没有开启, 则（1） storageBuffers，uniformBuffers以及 vertexInputs不能是VK_PIPELINE_ROBUSTNESS_BUFFER_BEHAVIOR_ROBUST_BUFFER_ACCESS_2_EXT
												  （2）images 不能是VK_PIPELINE_ROBUSTNESS_IMAGE_BEHAVIOR_ROBUST_IMAGE_ACCESS_2_EXT
	
	*/


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