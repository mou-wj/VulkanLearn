#include "PipelineTest.h"

NS_TEST_BEGIN
/*

多种管线的创建：
	compute
	graphic


*/


// Provided by VK_NV_device_generated_commands_compute
typedef struct VkComputePipelineIndirectBufferInfoNV {
	VkStructureType sType;
	const void* pNext;
	VkDeviceAddress deviceAddress;
	VkDeviceSize size;
	VkDeviceAddress pipelineDeviceAddressCaptureReplay;
} VkComputePipelineIndirectBufferInfoNV;

// Provided by VK_ANDROID_external_memory_android_hardware_buffer
typedef struct VkExternalFormatANDROID {
	VkStructureType    sType;
	void* pNext;
	uint64_t           externalFormat;
} VkExternalFormatANDROID;
typedef VkFlags VkPipelineCreateFlags2KHR;
// Provided by VK_KHR_maintenance5
typedef struct VkPipelineCreateFlags2CreateInfoKHR {
	VkStructureType              sType;
	const void* pNext;
	VkPipelineCreateFlags2KHR    flags;
} VkPipelineCreateFlags2CreateInfoKHR;
// Provided by VK_AMDX_shader_enqueue
typedef struct VkPipelineShaderStageNodeCreateInfoAMDX {
	VkStructureType    sType;
	const void* pNext;
	const char* pName;
	uint32_t             index;
} VkPipelineShaderStageNodeCreateInfoAMDX;

// Provided by VK_KHR_dynamic_rendering_local_read
typedef struct VkRenderingAttachmentLocationInfoKHR {
	VkStructureType    sType;
	const void* pNext;
	uint32_t           colorAttachmentCount;
	const uint32_t* pColorAttachmentLocations;
} VkRenderingAttachmentLocationInfoKHR;

// Provided by VK_KHR_dynamic_rendering_local_read
typedef struct VkRenderingInputAttachmentIndexInfoKHR {
	VkStructureType    sType;
	const void* pNext;
	uint32_t           colorAttachmentCount;
	const uint32_t* pColorAttachmentInputIndices;
	const uint32_t* pDepthInputAttachmentIndex;
	const uint32_t* pStencilInputAttachmentIndex;
} VkRenderingInputAttachmentIndexInfoKHR;

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
		computePipelineIndirectBufferInfoNV.sType = VK_STRUCTURE_TYPE_MAX_ENUM;//没有定义VK_STRUCTURE_TYPE_COMPUTE_PIPELINE_INDIRECT_BUFFER_INFO_NV
		computePipelineIndirectBufferInfoNV.pNext = &computePipelineControlCreateInfoAMD;
		computePipelineControlCreateInfoAMD.sType = VK_STRUCTURE_TYPE_PIPELINE_COMPILER_CONTROL_CREATE_INFO_AMD;
		computePipelineControlCreateInfoAMD.pNext = &pipelineCreateFlags2CreateInfoKHR;
		pipelineCreateFlags2CreateInfoKHR.sType = VK_STRUCTURE_TYPE_MAX_ENUM;//没有定义VK_STRUCTURE_TYPE_PIPELINE_CREATE_FLAGS_2_CREATE_INFO_KHR
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
		pipelineShaderStageNodeCreateInfoAMDX.sType = VK_STRUCTURE_TYPE_MAX_ENUM;//没有定义VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_NODE_CREATE_INFO_AMDX
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

		VkPipelineShaderStageModuleIdentifierCreateInfoEXT& pipelineShaderStageModuleIdentifierCreateInfoEXT = pipelineShaderStageCreateInfoExt.pipelineShaderStageModuleIdentifierCreateInfoEXT;
		pipelineShaderStageModuleIdentifierCreateInfoEXT.identifierSize = 0;//指定pIdentifier中数据的字节长度
		pipelineShaderStageModuleIdentifierCreateInfoEXT.pIdentifier = nullptr;// 是一个指向一个指定标识符的不透明数据缓冲区的指针，这个可以通过VkShaderModuleIdentifierEXT获得，见ShadersTest章节
		/*
		有效用法：
		1.如果该结构体包含在VkPipelineShaderStageCreateInfo的pNext中，且identifierSize不为0，则shaderModuleIdentifier特性必须开启，对应要创建的pipeline创建是必须包含VK_PIPELINE_CREATE_FAIL_ON_PIPELINE_COMPILE_REQUIRED_BIT，
		2.identifierSize 必须小于等于 VK_MAX_SHADER_MODULE_IDENTIFIER_SIZE_EXT
		
		*/



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
		pipelineCreateFlags2CreateInfoKHR.sType = VK_STRUCTURE_TYPE_MAX_ENUM;//没有定义VK_STRUCTURE_TYPE_PIPELINE_CREATE_FLAGS_2_CREATE_INFO_KHR
		//pipelineCreateFlags2CreateInfoKHR.pNext = nullptr;//已经链接好了这里不再设置
		pipelineCreateFlags2CreateInfoKHR.flags = 0;//没有定义VK_PIPELINE_CREATE_2_ALLOW_DERIVATIVES_BIT_KHR

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

		//VkComputePipelineIndirectBufferInfoNV
		//如果一个计算管道将在设备生成的命令中使用，通过指定其管道令牌与VkBindPipelineIndirectCommandNV，则其的metadata将被保存到一个缓冲区中，通过VkComputePipelineIndirectBufferInfoNV指定这个缓冲区的地址
		VkComputePipelineIndirectBufferInfoNV& computePipelineIndirectBufferInfoNV = computePipelineCreateInfoExt.computePipelineIndirectBufferInfoNV;
		computePipelineIndirectBufferInfoNV.deviceAddress = 0;//指向metadata将会被保存的缓冲区的设备地址
		computePipelineIndirectBufferInfoNV.size = 0;//metadata将会被保存的缓冲区的大小
		computePipelineIndirectBufferInfoNV.pipelineDeviceAddressCaptureReplay = 0;//指明metadata最开始被存放的地址且可以用来重新填充deviceAddress，目前这个参数的应用场景还不是很明确
		/*
		VkComputePipelineIndirectBufferInfoNV有效用法
		1.VkPhysicalDeviceDeviceGeneratedCommandsComputeFeaturesNV::deviceGeneratedComputePipelines特性必须开启
		2.管线创建的VkComputePipelineCreateInfo::flags中必须含有VK_PIPELINE_CREATE_INDIRECT_BINDABLE_BIT_NV
		3.deviceAddress 必须和通过vkGetPipelineIndirectMemoryRequirementsNV返回的 VkMemoryRequirements2::alignment对齐
		4.deviceAddress 必须从含有VK_BUFFER_USAGE_TRANSFER_DST_BIT 和 VK_BUFFER_USAGE_INDIRECT_BUFFER_BIT 用法位创建的 buffer 中分配
		5.size必须大于等于vkGetPipelineIndirectMemoryRequirementsNV中返回的 VkMemoryRequirements2::size
		6.如果 pipelineDeviceAddressCaptureReplay 不为0 则 （1） VkPhysicalDeviceDeviceGeneratedCommandsComputeFeaturesNV::deviceGeneratedComputeCaptureReplay 特性必须开启
                                                           （2）address 必须以 VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_CAPTURE_REPLAY_BIT 进行分配
	    												   （3） pipeline 必须已经为了replay重新创建了
		7.pipelineDeviceAddressCaptureReplay 必须满足和 deviceAddress 相似的对齐和大小限制

		*/
		{
					// Provided by VK_NV_device_generated_commands_compute
			auto vkCmdUpdatePipelineIndirectBufferNV = [](
				VkCommandBuffer commandBuffer,
				VkPipelineBindPoint pipelineBindPoint,
				VkPipeline pipeline) {

			};//这个接口没有定义，这里定义将pipeline的metadata保存到一个缓冲区中
			VkCommandBuffer cmdBuf;
			vkCmdUpdatePipelineIndirectBufferNV(cmdBuf, VK_PIPELINE_BIND_POINT_COMPUTE, computePipeline);//将pipeline的metadata保存到一个缓冲区中
			/*
			vkCmdUpdatePipelineIndirectBufferNV有效用法：
			1.必须在render pass实例以及video coding域外调用
			2.pipelineBindPoint 必须为 VK_PIPELINE_BIND_POINT_COMPUTE
			3.pipeline 创建必须含有 VK_PIPELINE_CREATE_INDIRECT_BINDABLE_BIT_NV 
			4.pipeline创建是必须有一个 VkComputePipelineIndirectBufferInfoNV指定数据保存的地址
			5.VkPhysicalDeviceDeviceGeneratedCommandsComputeFeaturesNV::deviceGeneratedComputePipelines特性必须开启
			6.cmdBuf所在的pool对应的queue必须支持图形，转换或者计算操作
			*/
		
		}


	vkCreateComputePipelines(device, VK_NULL_HANDLE, 1, &computePipelineCreateInfo, nullptr, &computePipeline);
	/*
	合法用法：
	1.如果pCreateInfos中的某个元素的flags包含VK_PIPELINE_CREATE_DERIVATIVE_BIT，则
													（1）如果其basePipelineIndex不为-1，则basePipelineIndex必须小于当前元素在pCreateInfos中的索引值
													（1）basePipelineHandle的创建flags必须含有 VK_PIPELINE_CREATE_ALLOW_DERIVATIVES_BIT
	2.如果pipelineCache 以 VK_PIPELINE_CACHE_CREATE_EXTERNALLY_SYNCHRONIZED_BIT标志创建,主机对 pipelineCache 必须要进行外部同步--如外部多线程同步等
	
	*/

	//销毁pipeline
	vkDestroyPipeline(device, computePipeline, nullptr);
}


struct GraphicsPipelineCreateInfoExt {
	VkAttachmentSampleCountInfoAMD attachmentSampleCountInfoAMD{};
	VkExternalFormatANDROID  externalFormatANDROID{};
	VkGraphicsPipelineLibraryCreateInfoEXT pipelineLibraryCreateInfoEXT{};
	VkGraphicsPipelineShaderGroupsCreateInfoNV pipelineShaderGroupsCreateInfoNV{};
	VkMultiviewPerViewAttributesInfoNVX multiviewPerViewAttributesInfoNVX{};
	VkPipelineCompilerControlCreateInfoAMD pipelineCompilerControlCreateInfoAMD{};
	VkPipelineCreateFlags2CreateInfoKHR  pipelineCreateFlags2CreateInfoKHR{};
	VkPipelineCreationFeedbackCreateInfo pipelineCreationFeedbackCreateInfo{};
	VkPipelineDiscardRectangleStateCreateInfoEXT pipelineDiscardRectangleStateCreateInfoEXT{};
	VkPipelineFragmentShadingRateEnumStateCreateInfoNV pipelineFragmentShadingRateEnumStateCreateInfoNV{};
	VkPipelineFragmentShadingRateStateCreateInfoKHR pipelineFragmentShadingRateStateCreateInfoKHR{};
	VkPipelineLibraryCreateInfoKHR pipelineLibraryCreateInfoKHR{};
	VkPipelineRenderingCreateInfo pipelineRenderingCreateInfo{};
	VkPipelineRepresentativeFragmentTestStateCreateInfoNV pipelineRepresentativeFragmentTestStateCreateInfoNV{};
	VkPipelineRobustnessCreateInfoEXT pipelineRobustnessCreateInfoEXT{};
	VkRenderingAttachmentLocationInfoKHR	renderingAttachmentLocationInfoKHR{};
	VkRenderingInputAttachmentIndexInfoKHR renderingInputAttachmentIndexInfoKHR{};
	GraphicsPipelineCreateInfoExt() {
		Init();
	}
	void Init() {
		attachmentSampleCountInfoAMD.sType = VK_STRUCTURE_TYPE_ATTACHMENT_SAMPLE_COUNT_INFO_AMD;
		attachmentSampleCountInfoAMD.pNext = &externalFormatANDROID;
		externalFormatANDROID.sType = VK_STRUCTURE_TYPE_EXTERNAL_FORMAT_ANDROID;
		externalFormatANDROID.pNext = &pipelineLibraryCreateInfoEXT;
		pipelineLibraryCreateInfoEXT.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_LIBRARY_CREATE_INFO_EXT;
		pipelineLibraryCreateInfoEXT.pNext = &pipelineShaderGroupsCreateInfoNV;
		pipelineShaderGroupsCreateInfoNV.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_SHADER_GROUPS_CREATE_INFO_NV;
		pipelineShaderGroupsCreateInfoNV.pNext = &multiviewPerViewAttributesInfoNVX;
		multiviewPerViewAttributesInfoNVX.sType = VK_STRUCTURE_TYPE_MULTIVIEW_PER_VIEW_ATTRIBUTES_INFO_NVX;
		multiviewPerViewAttributesInfoNVX.pNext = &pipelineCompilerControlCreateInfoAMD;
		pipelineCompilerControlCreateInfoAMD.sType = VK_STRUCTURE_TYPE_PIPELINE_COMPILER_CONTROL_CREATE_INFO_AMD;
		pipelineCompilerControlCreateInfoAMD.pNext = &pipelineCreateFlags2CreateInfoKHR;
		pipelineCreateFlags2CreateInfoKHR.sType = VK_STRUCTURE_TYPE_MAX_ENUM;//VK_STRUCTURE_TYPE_PIPELINE_CREATE_FLAGS_2_CREATE_INFO_KHR未定义
		pipelineCreateFlags2CreateInfoKHR.pNext = &pipelineCreationFeedbackCreateInfo;
		pipelineCreationFeedbackCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_CREATION_FEEDBACK_CREATE_INFO;
		pipelineCreationFeedbackCreateInfo.pNext = &pipelineDiscardRectangleStateCreateInfoEXT;
		pipelineDiscardRectangleStateCreateInfoEXT.sType = VK_STRUCTURE_TYPE_PIPELINE_DISCARD_RECTANGLE_STATE_CREATE_INFO_EXT;
		pipelineDiscardRectangleStateCreateInfoEXT.pNext = &pipelineFragmentShadingRateEnumStateCreateInfoNV;
		pipelineFragmentShadingRateEnumStateCreateInfoNV.sType = VK_STRUCTURE_TYPE_PIPELINE_FRAGMENT_SHADING_RATE_ENUM_STATE_CREATE_INFO_NV;
		pipelineFragmentShadingRateEnumStateCreateInfoNV.pNext = &pipelineFragmentShadingRateStateCreateInfoKHR;
		pipelineFragmentShadingRateStateCreateInfoKHR.sType = VK_STRUCTURE_TYPE_PIPELINE_FRAGMENT_SHADING_RATE_STATE_CREATE_INFO_KHR;
		pipelineFragmentShadingRateStateCreateInfoKHR.pNext = &pipelineLibraryCreateInfoKHR;
		pipelineLibraryCreateInfoKHR.sType = VK_STRUCTURE_TYPE_PIPELINE_LIBRARY_CREATE_INFO_KHR;
		pipelineLibraryCreateInfoKHR.pNext = &pipelineRenderingCreateInfo;
		pipelineRenderingCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_RENDERING_CREATE_INFO;
		pipelineRenderingCreateInfo.pNext = &pipelineRepresentativeFragmentTestStateCreateInfoNV;
		pipelineRepresentativeFragmentTestStateCreateInfoNV.sType = VK_STRUCTURE_TYPE_PIPELINE_REPRESENTATIVE_FRAGMENT_TEST_STATE_CREATE_INFO_NV;
		pipelineRepresentativeFragmentTestStateCreateInfoNV.pNext = &pipelineRobustnessCreateInfoEXT;
		pipelineRobustnessCreateInfoEXT.sType = VK_STRUCTURE_TYPE_PIPELINE_ROBUSTNESS_CREATE_INFO_EXT;
		pipelineRobustnessCreateInfoEXT.pNext = &renderingAttachmentLocationInfoKHR;
		renderingAttachmentLocationInfoKHR.sType = VK_STRUCTURE_TYPE_MAX_ENUM;//VK_STRUCTURE_TYPE_RENDERING_ATTACHMENT_LOCATION_INFO_KHR未定义
		renderingAttachmentLocationInfoKHR.pNext = &renderingInputAttachmentIndexInfoKHR;
		renderingInputAttachmentIndexInfoKHR.sType = VK_STRUCTURE_TYPE_MAX_ENUM;//VK_STRUCTURE_TYPE_RENDERING_INPUT_ATTACHMENT_INDEX_INFO_KHR未定义
		renderingInputAttachmentIndexInfoKHR.pNext = nullptr;

	
	
	
	}

};


void PipelineTest::GraphicPipelineCreateTest()
{


	VkPipeline graphicPipeline;

	//创建管线所需要的状态被分为4个部分 vertex input state, pre-rasterization shader state, fragment shader state, 以及 fragment output state.
	/*
	vertex input state：
			VkPipelineVertexInputStateCreateInfo
			VkPipelineInputAssemblyStateCreateInfo
			一些其他细节见p743
	pre-rasterization shader state：
			VkPipelineShaderStageCreateInfo 包含:
				Vertex shaders
				Tessellation control shaders
				Tessellation evaluation shaders
				Geometry shaders
				Task shaders
				Mesh shaders
			VkPipelineViewportStateCreateInfo
			VkPipelineRasterizationStateCreateInfo
			VkPipelineTessellationStateCreateInfo
			VkRenderPass and subpass parameter
			The viewMask parameter of VkPipelineRenderingCreateInfo (formats are ignored)
			VkPipelineDiscardRectangleStateCreateInfoEXT
			VkPipelineFragmentShadingRateStateCreateInfoKHR
			一些其他细节见p743
	fragment shader state：
		VkPipelineShaderStageCreateInfo 
			fragment shader
		VkPipelineLayout
		VkPipelineMultisampleStateCreateInfo 
		VkPipelineDepthStencilStateCreateInfo
		VkRenderPass and subpass parameter
		The viewMask parameter of VkPipelineRenderingCreateInfo (formats are ignored)
		VkPipelineFragmentShadingRateStateCreateInfoKHR
		VkPipelineFragmentShadingRateEnumStateCreateInfoNV
		VkPipelineRepresentativeFragmentTestStateCreateInfoNV
		Inclusion/omission： 对于  VK_PIPELINE_RASTERIZATION_STATE_CREATE_FRAGMENT_SHADING_RATE_ATTACHMENT_BIT_KHR  以及VK_PIPELINE_RASTERIZATION_STATE_CREATE_FRAGMENT_DENSITY_MAP_ATTACHMENT_BIT_EXT
		VkRenderingInputAttachmentIndexInfoKHR
	fragment output state：
		VkPipelineColorBlendStateCreateInfo
		VkRenderPass and subpass parameter
		VkPipelineMultisampleStateCreateInfo
		VkPipelineRenderingCreateInfo
		VkAttachmentSampleCountInfoAMD
		VkAttachmentSampleCountInfoNV
		VkExternalFormatANDROID
		Inclusion/omission：对于  VK_PIPELINE_CREATE_COLOR_ATTACHMENT_FEEDBACK_LOOP_BIT_EXT 以及 VK_PIPELINE_CREATE_DEPTH_STENCIL_ATTACHMENT_FEEDBACK_LOOP_BIT_EXT ， VK_PIPELINE_CREATE_2_ENABLE_LEGACY_DITHERING_BIT_EXT 
		VkRenderingAttachmentLocationInfoKHR

	动态状态中如果有已经设置的静态状态，则该动态状态会被忽略
	一个完整的pipeline总是包含pre-rasterization shader state

	*/
	VkGraphicsPipelineCreateInfo graphicPipelineCreateInfo{};



	VkPipelineShaderStageCreateInfo shaderStages{};
	VkPipelineVertexInputStateCreateInfo vertexInputState{};
	VkPipelineInputAssemblyStateCreateInfo inputAssemblyState{};
	VkPipelineTessellationStateCreateInfo tessellationState{};
	VkPipelineViewportStateCreateInfo viewportState{};
	VkPipelineRasterizationStateCreateInfo rasterizationState{};
	VkPipelineMultisampleStateCreateInfo multisampleState{};
	VkPipelineDepthStencilStateCreateInfo depthStencilState{};
	VkPipelineColorBlendStateCreateInfo colorBlendState{};
	VkPipelineDynamicStateCreateInfo dynamicState{};
	dynamicState.dynamicStateCount = 0;//pDynamicStates中元素个数
	dynamicState.pDynamicStates = VK_NULL_HANDLE;//是一个指向VkDynamicState值数组的指针，它指定哪些管道状态片段将使用来自dynamic state命令而不是来自管道创建时state信息的值。
	dynamicState.flags = 0;//保留未来使用
	//to do




		GraphicsPipelineCreateInfoExt pipelineCreateInfoExt{};


	graphicPipelineCreateInfo.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
	graphicPipelineCreateInfo.pNext = &pipelineCreateInfoExt.attachmentSampleCountInfoAMD;
	graphicPipelineCreateInfo.stageCount = 1;
	graphicPipelineCreateInfo.pStages = &shaderStages;/*指明管线所涉及的着色器状态

	VK_PIPELINE_CREATE_DISABLE_OPTIMIZATION_BIT :    指明管线创建不会优化，这会加快管道创建
    VK_PIPELINE_CREATE_ALLOW_DERIVATIVES_BIT :    指定要创建的管道允许是将在后续的管道创建调用中创建的管道的父管道
    VK_PIPELINE_CREATE_DERIVATIVE_BIT :    指定要创建的管道将是以前创建的父管道的子管道
    VK_PIPELINE_CREATE_VIEW_INDEX_FROM_DEVICE_INDEX_BIT :   指定任何以 ViewIndex修饰的着色器输入变量将被分配值，就像它们被修饰为DeviceIndex.一样。
	VK_PIPELINE_CREATE_DISPATCH_BASE :   指定计算管道可以与非零基工作组的vkCmdDispatchBase一起使用
    VK_PIPELINE_CREATE_DEFER_COMPILE_BIT_NV :    指定创建所有着色器处于延迟状态的的管道。在使用管道之前，应用程序必须在使用管道之前对管道中的每个着色器只调用vkCompileDeferredNV一次。 
    VK_PIPELINE_CREATE_CAPTURE_STATISTICS_BIT_KHR :    指定着色器编译器应该捕获由编译过程产生的管道可执行文件的统计信息，稍后可以通过调用vkGetPipelineExecutableStatisticsKHR.来检索这些信息，启用此标志不能影响最终编译的管道，但可能会禁用管道缓存或以其他方式影响管道创建时间。
    VK_PIPELINE_CREATE_CAPTURE_INTERNAL_REPRESENTATIONS_BIT_KHR :    指定着色器编译器应该捕获由编译过程产生的管道可执行文件的内部表示，稍后可以通过调用 vkGetPipelineExecutableInternalRepresentationsKHR.来检索启用此标志不能影响最终编译的管道，但可能会禁用管道缓存或以其他方式影响管道创建时间。当从使用管道库创建的管道中捕获IR时，并不能保证可以从链接的管道中检索到库中的IR。应用程序应该分别从每个库和任何链接的管道中检索IR
    VK_PIPELINE_CREATE_LIBRARY_BIT_KHR :    指定不能直接使用管道，而是定义了一个可以使用VkPipelineLibraryCreateInfoKHR结构与其他管道组合的 pipeline library 。这可以在光线追踪和图形管道中使用。
    VK_PIPELINE_CREATE_RAY_TRACING_NO_NULL_ANY_HIT_SHADERS_BIT_KHR :    指定在执行any-hit着色器时，将始终存在any-hit着色器。一个NULL any-hit的着色器是一个有效的是VK_SHADER_UNUSED_KHR的 any-hit 的着色器，例如来自一个完全由零组成的着色器组。 
    VK_PIPELINE_CREATE_RAY_TRACING_NO_NULL_CLOSEST_HIT_SHADERS_BIT_KHR :   指定在执行closest hit着色器时，将始终存在closest hit着色器。一个NULL closest hit 着色器是一个有效的VK_SHADER_UNUSED_KHR的closest hit 着色器，例如从一个完全由零组成的着色器组 
    VK_PIPELINE_CREATE_RAY_TRACING_NO_NULL_MISS_SHADERS_BIT_KHR :    指定在执行miss shader 时，将始终存在miss shader。一个NULL miss shader是一个有效的VK_SHADER_UNUSED_KHR miss shader，例如从一个完全由零组成的着色器组。
    VK_PIPELINE_CREATE_RAY_TRACING_NO_NULL_INTERSECTION_SHADERS_BIT_KHR :   指定在执行intersection shader 时，将始终存在intersection shader。一个NULL intersection shader是一个有效的VK_SHADER_UNUSED_KHR intersection shader，例如从一个完全由零组成的着色器组。  
    VK_PIPELINE_CREATE_RAY_TRACING_SKIP_TRIANGLES_BIT_KHR :    指定在使用管道跟踪射线指令遍历期间将跳过三角形图元。
    VK_PIPELINE_CREATE_RAY_TRACING_SKIP_AABBS_BIT_KHR :    指定在使用管道跟踪射线指令遍历期间将跳过AABB primitives。
    VK_PIPELINE_CREATE_RAY_TRACING_SHADER_GROUP_HANDLE_CAPTURE_REPLAY_BIT_KHR :     指定着色器组句柄可以在后续的运行中被保存和重用（例如，用于跟踪捕获和重播）。
    VK_PIPELINE_CREATE_INDIRECT_BINDABLE_BIT_NV :    指定管道可以与Device-Generated的命令结合使用  
	VK_PIPELINE_CREATE_FAIL_ON_PIPELINE_COMPILE_REQUIRED_BIT :    指定如果需要编译来创建一个有效的VkPipeline，则管道创建将失败；管道创建将返回VK_PIPELINE_COMPILE_REQUIRED，并且VkPipeline将被设置为VK_NULL_HANDLE。 
	VK_PIPELINE_CREATE_EARLY_RETURN_ON_FAILURE_BIT: 指定如果任何单个管道返回一个不是VK_SUCCESS的结果，则不再继续创建额外的管道，而是将控制权返回给应用程序。
    VK_PIPELINE_CREATE_RAY_TRACING_ALLOW_MOTION_BIT_NV :    指定管道可以使用 OpTraceRayMotionNV.
	VK_PIPELINE_CREATE_RENDERING_FRAGMENT_SHADING_RATE_ATTACHMENT_BIT_KHR :     指定管道将与一个 fragment shading rate attachment 一起使用。
    VK_PIPELINE_CREATE_RENDERING_FRAGMENT_DENSITY_MAP_ATTACHMENT_BIT_EXT :   指定管道将与一个 fragment density map attachment 一起使用
    VK_PIPELINE_CREATE_LINK_TIME_OPTIMIZATION_BIT_EXT :   指定要链接到此库中的管道库应该已应用了链接时间优化。如果省略了这个位，那么实现应该尽可能快地执行链接。
    VK_PIPELINE_CREATE_RETAIN_LINK_TIME_OPTIMIZATION_INFO_BIT_EXT :  指定管道库应该保留以后与VK_PIPELINE_CREATE_LINK_TIME_OPTIMIZATION_BIT_EXT.执行最佳链接所需的任何信息
    VK_PIPELINE_CREATE_DESCRIPTOR_BUFFER_BIT_EXT :    指定管道将与descriptor buffers一起使用，而不是使用descriptor sets。
	VK_PIPELINE_CREATE_COLOR_ATTACHMENT_FEEDBACK_LOOP_BIT_EXT :  指定管道可以与feedback loop color attachment一起使用。如果pDynamicStates设置了VK_DYNAMIC_STATE_ATTACHMENT_FEEDBACK_LOOP_ENABLE_EXT，则该位会被忽略  
	VK_PIPELINE_CREATE_DEPTH_STENCIL_ATTACHMENT_FEEDBACK_LOOP_BIT_EXT :   指定管道可以与feedback loop depth-stencil attachment一起使用。如果pDynamicStates设置了VK_DYNAMIC_STATE_ATTACHMENT_FEEDBACK_LOOP_ENABLE_EXT，则该位会被忽略      
	VK_PIPELINE_CREATE_RAY_TRACING_OPACITY_MICROMAP_BIT_EXT :   指定光线跟踪管道可与引用不透明度微映射阵列的加速结构一起使用。
    VK_PIPELINE_CREATE_RAY_TRACING_DISPLACEMENT_MICROMAP_BIT_NV :    指定光线追踪管道可以与参考位移微映射阵列的加速结构一起使用
    VK_PIPELINE_CREATE_NO_PROTECTED_ACCESS_BIT_EXT :    指定管道不能绑定到受保护的命令缓冲区。
    VK_PIPELINE_CREATE_PROTECTED_ACCESS_ONLY_BIT_EXT :    指定管道不能绑定到未受保护的命令缓冲区
	
	
	
	*/
	graphicPipelineCreateInfo.pVertexInputState = &vertexInputState;//指明顶点输入，如果管线包含mesh shader则可以被忽略，如果管线以VK_DYNAMIC_STATE_VERTEX_INPUT_EXT动态状态创建则该可以为NULL
	graphicPipelineCreateInfo.pInputAssemblyState = &inputAssemblyState;//是一个指向VkPipelineInputAssemblyStateCreateInfo结构的指针，它决定了顶点着色的输入装配行为，如图形命令中所述。如果启用了VK_EXT_extended_dynamic_state3扩展，如果管道是使用VK_DYNAMIC_STATE_PRIMITIVE_RESTART_ENABLE创建的，并且VK_DYNAMIC_STATE_PRIMITIVE_TOPOLOGY动态状态集，动态原始拓扑不受限制为VK_TRUE，则可以为NULL。如果管道包含一个网格着色器阶段，则会忽略它。
	graphicPipelineCreateInfo.pTessellationState = &tessellationState;//是一个指向VkPipelineTessellationStateCreateInfo结构的指针，定义tessellation shader的tessellation stage使用。如果管道是使用VK_DYNAMIC_STATE_PATCH_CONTROL_POINTS_EXT动态状态集创建的，则可以为NULL。
	graphicPipelineCreateInfo.pViewportState = &viewportState;//是指向VkPipelineViewportStateCreateInfo结构的指针，定义在启用光栅化时使用的视口状态。如果启用了VK_EXT_extended_dynamic_state3扩展，那么如果在创建管道时同时设置了VK_DYNAMIC_STATE_VIEWPORT_WITH_COUNT和VK_DYNAMIC_STATE_SCISSOR_WITH_COUNT动态状态，则它可以为NULL。
	graphicPipelineCreateInfo.pRasterizationState = &rasterizationState;//是一个指向定义光栅化状态的VkPipelineRasterizationStateCreateInfo结构的指针。如果启用了VK_EXT_extended_dynamic_state3扩展，则如果在管道中创建了所有VK_DYNAMIC_STATE_DEPTH_CLAMP_ENABLE_EXT、VK_DYNAMIC_STATE_RASTERIZER_DISCARD_ENABLE、VK_DYNAMIC_STATE_POLYGON_MODE_EXT、VK_DYNAMIC_STATE_CULL_MODE、VK_DYNAMIC_STATE_FRONT_FACE、
	//VK_DYNAMIC_STATE_DEPTH_BIAS_ENABLE、VK_DYNAMIC_STATE_DEPTH_BIAS和VK_DYNAMIC_STATE_LINE_WIDTH动态状态，则可以为NULL。
	graphicPipelineCreateInfo.pMultisampleState = &multisampleState;//是一个指向VkPipelineMultisampleStateCreateInfo结构的指针，它定义了在启用栅格化时使用的多样本状态。如果启用了VK_EXT_extended_dynamic_state3扩展，如果创建管道时设置了所有VK_DYNAMIC_STATE_RASTERIZATION_SAMPLES_EXT、VK_DYNAMIC_STATE_SAMPLE_MASK_EXT和VK_DYNAMIC_STATE_ALPHA_TO_COVERAGE_ENABLE_EXT动态状态，
	//并且在设备上禁用了Toone或设置了VK_DYNAMIC_STATE_ALPHA_TO_ONE_ENABLE_EXT，则可以为空，在这种情况下，假定VkPipelineMultisampleStateCreateInfo：：sampleShadingEnable为VK_FALSE。
	graphicPipelineCreateInfo.pDepthStencilState = &depthStencilState;//是一个指向VkPipelineDepthStencilStateCreateInfo结构的指针，定义在渲染过程中为访问深度或模板附件时的光栅化的深度/模板状态。如果启用了VK_EXT_extended_dynamic_state3扩展，则如果在管道中创建了所有VK_DYNAMIC_STATE_DEPTH_TEST_ENABLE、VK_DYNAMIC_STATE_DEPTH_WRITE_ENABLE、VK_DYNAMIC_STATE_DEPTH_COMPARE_OP、
	//VK_DYNAMIC_STATE_DEPTH_BOUNDS_TEST_ENABLE、VK_DYNAMIC_STATE_STENCIL_TEST_ENABLE、VK_DYNAMIC_STATE_STENCIL_OP和VK_DYNAMIC_STATE_DEPTH_BOUNDS动态状态，则可以为NULL。
	graphicPipelineCreateInfo.pColorBlendState = &colorBlendState;//是一个指向VkPipelineColorBlendStateCreateInfo结构的指针，它定义了在渲染期间启用了光栅化的颜色附件的颜色混合状态。如果启用了VK_EXT_extended_dynamic_state3扩展，则如果创建管道时设置了所有VK_DYNAMIC_STATE_LOGIC_OP_ENABLE_EXT、VK_DYNAMIC_STATE_LOGIC_OP_EXT、VK_DYNAMIC_STATE_COLOR_BLEND_ENABLE_EXT、
	//VK_DYNAMIC_STATE_COLOR_BLEND_EQUATION_EXT、VK_DYNAMIC_STATE_COLOR_WRITE_MASK_EXT和VK_DYNAMIC_STATE_BLEND_CONSTANTS动态状态，则可以为NULL。
	graphicPipelineCreateInfo.pDynamicState = &dynamicState;//是指向VkPipelineDynamicStateCreateInfo结构的指针，定义管道状态对象的哪些属性是动态的，可以独立于管道状态进行更改。这可以是NULL，这意味着管道中没有任何状态被认为是动态状态。

	VkPipelineLayout pipelineLayout;
	graphicPipelineCreateInfo.layout = pipelineLayout;//指定pipeline的绑定布局以及描述符布局
	graphicPipelineCreateInfo.renderPass = VK_NULL_HANDLE;//指明当前 pipeline 所对应的render pass环境，但是pipeline可以在和render pass兼容的其他render pass中使用
	graphicPipelineCreateInfo.subpass = 0;//指明当前pipeline对应render pass中的subpass 索引
	graphicPipelineCreateInfo.basePipelineHandle = VK_NULL_HANDLE;//指明pipeline的可以从哪个pipeline派生
	graphicPipelineCreateInfo.basePipelineIndex = 0;//指明pipeline的可以从哪个pipeline派生的在 pCreateInfos中索引值
	/*
	VkGraphicsPipelineCreateInfo有效用法：
	1.如果pNext中不包含VkPipelineCreateFlags2CreateInfoKHR则 flags 必须是合法的 VkPipelineCreateFlagBits 的组合值
	2.如果 flags 包含 VK_PIPELINE_CREATE_DERIVATIVE_BIT 则:
													（1）如果 basePipelineIndex 为 -1,basePipelineHandle 必须是一个有效的 graphics VkPipeline 句柄
													（2）如果 basePipelineHandle 为VK_NULL_HANDLE, basePipelineIndex 必须是当前创建命令vkCreateComputePipelines中pCreateInfos 参数的一个有效的索引值
													（3）basePipelineIndex 必须为 -1或者 basePipelineHandle 必须为 VK_NULL_HANDLE
	3.如果push constant 块在shader中声明了,则layout中的 push constant的 range 必须和shader的 stage 以及 range匹配
	4.如果 resource variables 在shader中声明了,则  
													（1）layout中的 descriptor slot 必须匹配shader stage
													（2）如果layout中的 descriptor type不是VK_DESCRIPTOR_TYPE_MUTABLE_EXT,则 descriptor slot必须匹配 descriptor slot
	5.如果 resource variables 在shader中声明为array，则layout中的 descriptor slot必须匹配 descriptor count
	6.如果 pipeline 需要 pre-rasterization shader state 则 pStages 其中一个必须为 VK_SHADER_STAGE_VERTEX_BIT 或者 VK_SHADER_STAGE_MESH_BIT_EXT
	7.如果 pipeline 需要 pre-rasterization shader state 则pStages中的 geometric shader stages 必须来自于 mesh shading pipeline (stage isVK_SHADER_STAGE_TASK_BIT_EXT or VK_SHADER_STAGE_MESH_BIT_EXT) 或者来自于 primitive shading pipeline (stage is VK_SHADER_STAGE_VERTEX_BIT,
										VK_SHADER_STAGE_TESSELLATION_CONTROL_BIT, VK_SHADER_STAGE_TESSELLATION_EVALUATION_BIT, 或者 VK_SHADER_STAGE_GEOMETRY_BIT)
	8.如果 pipeline 需要 pre-rasterization shader state 且 pStages 同时含有VK_SHADER_STAGE_TASK_BIT_EXT and VK_SHADER_STAGE_MESH_BIT_EXT, 则 mesh shader 的入口点不能声明DrawIndex BuiltIn描述的变量
	9.VK_SHADER_STAGE_TASK_BIT_EXT或VK_SHADER_STAGE_MESH_BIT_EXT的shader stage必须使用TaskNV和MeshNV执行模型或TaskEXT和MeshEXT执行模型，但不能同时使用
	10.如果 pipeline 需要 pre-rasterization shader state 则tessellation control shader stage以及tessellation evaluation shader stage如果pStages中有则需要同时包含在内
	11.如果 pipeline 需要 pre-rasterization shader state 且 pStages 包含 tessellation control shader stage, 且 VK_EXT_extended_dynamic_state3 拓展没有开启或者  VK_DYNAMIC_STATE_PATCH_CONTROL_POINTS_EXT dynamic state 没有设置, pTessellationState必须是一个有效的 VkPipelineTessellationStateCreateInfo 指针
	12.如果 pTessellationState 不为NULL则必须是有效的 VkPipelineTessellationStateCreateInfo 指针
	13.如果 pipeline 需要 pre-rasterization shader state 且 pStages 包含 tessellation shader stages, 则（1）则至少一个shader stage的 shader code 必须包含 OpExecutionMode 指令指明管线细分类型
																									   （2）如果两个stages的 shader code 都包含 OpExecutionMode 指令指明管线细分类型，则两者指明的细分类型必须是相同的
																									   （3）则至少一个shader stage的 shader code 必须包含 OpExecutionMode 指令指明管线的output patch size
																									   （4）如果两个stages的 shader code 都包含 OpExecutionMode 指令指明管线的output patch size，则两者指明的output patch size必须是相同的
	14.如果 pipeline 以 pre-rasterization shader state 和 vertex input state创建且 pStages 包含 tessellation shader stages, 且 如果 VK_DYNAMIC_STATE_PRIMITIVE_TOPOLOGY dynamic state 没有开启设置 或者dynamicPrimitiveTopologyUnrestricted 为 VK_FALSE, 则pInputAssembly中的 topology 必须为 VK_PRIMITIVE_TOPOLOGY_PATCH_LIST
	15.如果 pipeline 以 pre-rasterization shader state 和 vertex input state创建且pInputAssembly中的 topology 为 VK_PRIMITIVE_TOPOLOGY_PATCH_LIST, 且 VK_DYNAMIC_STATE_PRIMITIVE_TOPOLOGY dynamic state 没有开启设置 或者dynamicPrimitiveTopologyUnrestricted 为 VK_FALSE , 则 pStages 必须包含 tessellation shader stages
	16.如果 pipeline 以 TessellationEvaluation Execution Model创建,且没有 Geometry Execution Model, 使用 PointMode Execution Mode, 且 shaderTessellationAndGeometryPointSize 开启, 如果maintenance5没有开启则以 PointSize 修饰的变量必须被赋值
	17.如果 pipeline 以 Vertex Execution Model 创建且没有 TessellationEvaluation 或者 Geometry Execution Model, 且pInputAssembly中的 topology为 VK_PRIMITIVE_TOPOLOGY_POINT_LIST, 而且VK_DYNAMIC_STATE_PRIMITIVE_TOPOLOGY dynamic state 没有开启或者 dynamicPrimitiveTopologyUnrestricted 为 VK_FALSE,如果maintenance5没有开启则以 PointSize 修饰的变量必须被写入
	18.如果 maintenance5 开启且以PointSize描述的变量被写入了，所有的执行路径都必须写入到PointSize修饰的变量中
	19.如果 pipeline 以 TessellationEvaluation Execution Model创建, 没有 Geometry Execution Model, 使用 PointMode Execution Mode, 且 shaderTessellationAndGeometryPointSize 没有开启,  PointSize 修饰的变量就不能被写入
	20.如果 pipeline 以 Geometry Execution Model创建, 使用 OutputPoints Execution Mode, 则（1）如果 shaderTessellationAndGeometryPointSize 开启,如果maintenance5没有开启则PointSize修饰的变量必须为写入到每个发射的点中
																						  （2）如果 shaderTessellationAndGeometryPointSize 没有开启,则PointSize修饰的变量就不能被写入
	
	21.如果 pipeline 需要 pre-rasterization shader state 且 pStages 包含一个 geometry shader stage, 则（1）如果不包含任何 tessellation shader stages, 则其geometry shader code必须包含一个 OpExecutionMode 指令指明一个和pInputAssembly的topology兼容的输入图元类型
																									  （2） 如果包含  tessellation shader stages,则其geometry shader code必须包含一个 OpExecutionMode 指令指明一个和essellation stages输出的图元类型兼容的输入图元类型

	22.如果 pipeline 需要 pre-rasterization shader state 以及 fragment shader state, 且其同时包含 fragment shader 以及 geometry shader, 则在所有执行路径下， fragment shader code 需要从PrimitiveId修饰的输入变量中读取数据则 geometry shader code 必须写入到对应的PrimitiveId修饰的变量中

	23.如果 pipeline 需要 pre-rasterization shader state, 其包含一个 mesh shader 则在所有执行路径下，fragment shader code需要从PrimitiveId修饰的变量中读取输入变量，则 mesh shader code 必须写入到对应的以PrimitiveId修饰的变量中
	24.如果  renderPass 不为 VK_NULL_HANDLE 且 pipeline 以 fragment shader state 创建， the fragment shader 不能从subpass中任何定义为VK_ATTACHMENT_UNUSED的 input attachment 中读取数据
	25.如果 pipeline 需要 pre-rasterization shader state 且在pStages中包含 multiple pre-rasterization , 则pStages中的入口点的shader code以及VkGraphicsPipelineCreateInfo的其他状态入口点的shader code必须符合 Shader Interfaces 章节描述的链接规则
	25.如果 pipeline 需要 pre-rasterization shader state 和 fragment shader state,  fragment shader 和最后的 pre-rasterization shader stage 以及相关的 state 必须符合 Shader Interfaces 章节描述的链接规则
	26.如果 renderPass 不为 VK_NULL_HANDLE, 且 pipeline 以 fragment output interface state创建, 则（1）对于subpass中的任何 color attachment , 如果其对应的attachment description中的format的 potential format features 不包含 VK_FORMAT_FEATURE_COLOR_ATTACHMENT_BLEND_BIT, 则其对应的pColorBlendState中的pAttachments中的 blendEnable必须为VK_FALSE
																								  （2）若pColorBlendState 不为 NULL, pColorBlendState的 attachmentCount member 没有被忽略, subpass使用 color attachments, the pColorBlendState中的attachmentCount 必须等于创建subpass的 colorAttachmentCount

	27.如果 pipeline 需要 pre-rasterization shader state, 且 pViewportState->pViewports 不是动态的, 则（1）pViewportState->pViewports 必须是pViewportState->viewportCount个 有效 VkViewport 的数组首地址
																									  （2）pViewportState->pScissors 必须是pViewportState->scissorCount个 有效 VkRect2D 的数组首地址
	
	28.如果 pipeline 需要 pre-rasterization shader state, 且 wideLines 特性没有开启, 且pDynamicState中的pDynamicStates中没有 VK_DYNAMIC_STATE_LINE_WIDTH, 则pRasterizationStatethe的 lineWidth 必须为 1.0
	29.如果 pipeline 需要 pre-rasterization shader state, 且 VK_DYNAMIC_STATE_RASTERIZER_DISCARD_ENABLE dynamic state开启 或者pRasterizationState的 rasterizerDiscardEnable 为 VK_FALSE, 以及  VK_EXT_extended_dynamic_state3 拓展没有开启或者  VK_DYNAMIC_STATE_VIEWPORT_WITH_COUNT 或 VK_DYNAMIC_STATE_SCISSOR_WITH_COUNT dynamic states 没有设置, 则pViewportState 必须是一个有效的 VkPipelineViewportStateCreateInfo 指针
	30.如果pViewportState 不为 NULL 则其必须为一个合法的 VkPipelineViewportStateCreateInfo 指针
	31.如果 pipeline 需要 fragment output interface state, 且 VK_EXT_extended_dynamic_state3拓展没有开启或者 VK_DYNAMIC_STATE_RASTERIZATION_SAMPLES_EXT, VK_DYNAMIC_STATE_SAMPLE_MASK_EXT, 或 VK_DYNAMIC_STATE_ALPHA_TO_COVERAGE_ENABLE_EXT dynamic states 任何之一没有开启, 或者 alphaToOne 在Device上支持但 VK_DYNAMIC_STATE_ALPHA_TO_ONE_ENABLE_EXT 没有设置, pMultisampleState 必须是一个有效的 VkPipelineMultisampleStateCreateInfo 指针
	32.如果 pMultisampleState 不为 NULL 就必须是一个有效的 VkPipelineMultisampleStateCreateInfo 指针
	33.如果 pipeline 以 fragment shader state创建, VkPipelineMultisampleStateCreateInfo::alphaToCoverageEnable 为VK_TRUE且没有被忽略, 则 Fragment Output Interface 必须在Index 0 的Location 0 处含有一个拥有  alphaComponent 的变量
	34.如果 renderPass 不为 VK_NULL_HANDLE,  pipeline  以 fragment shader state创建, 且 subpass 使用一个 depth/stencil attachment, 且VK_EXT_extended_dynamic_state3 拓展没有开启或者VK_DYNAMIC_STATE_DEPTH_TEST_ENABLE, VK_DYNAMIC_STATE_DEPTH_WRITE_ENABLE,
					VK_DYNAMIC_STATE_DEPTH_COMPARE_OP, VK_DYNAMIC_STATE_DEPTH_BOUNDS_TEST_ENABLE,VK_DYNAMIC_STATE_STENCIL_TEST_ENABLE, VK_DYNAMIC_STATE_STENCIL_OP,或VK_DYNAMIC_STATE_DEPTH_BOUNDS dynamic states 任何之一没有设置, pDepthStencilState必须是一个有效的 VkPipelineDepthStencilStateCreateInfo 指针
	35.如果 pDepthStencilState 不为 NULL 则必须为有效的VkPipelineDepthStencilStateCreateInfo 指针
	36.如果 renderPass 不为 VK_NULL_HANDLE,  pipeline 以 fragment output interface state创建,  subpass 使用 color attachments, 且 VK_EXT_extended_dynamic_state3 拓展没有开启, 或者 VK_DYNAMIC_STATE_LOGIC_OP_ENABLE_EXT,VK_DYNAMIC_STATE_LOGIC_OP_EXT, VK_DYNAMIC_STATE_COLOR_BLEND_ENABLE_EXT,
					VK_DYNAMIC_STATE_COLOR_BLEND_EQUATION_EXT, VK_DYNAMIC_STATE_COLOR_WRITE_MASK_EXT,或者 VK_DYNAMIC_STATE_BLEND_CONSTANTS dynamic states 任何之一没有设置, pColorBlendState 必须是合法的 VkPipelineColorBlendStateCreateInfo 指针
	37.如果 pipeline 需要 pre-rasterization shader state,  depthBiasClamp 特性没有开启,  pDynamicState的pDynamicStates 中的元素没有 VK_DYNAMIC_STATE_DEPTH_BIAS,且pRasterizationState的depthBiasEnable 为 VK_TRUE, 则pRasterizationState的 depthBiasClamp必须为 0.0
	38.如果 pipeline 需要 fragment shader state,  VK_EXT_depth_range_unrestricted 拓展没有启用且pDynamicState的 pDynamicStates 没有 VK_DYNAMIC_STATE_DEPTH_BOUNDS, 且pDepthStencilState的depthBoundsTestEnable 为 VK_TRUE, 则pDepthStencilState的 minDepthBounds 以及 maxDepthBounds必须在 0.0 and 1.0
	39.如果 pipeline 需要 fragment shader state 或者 fragment output interface state,且rasterizationSamples 以及 sampleLocationsInfo 不是动态的,则
																			（1）如果pMultisampleState的pNext中的VkPipelineSampleLocationsStateCreateInfoEXT::sampleLocationsEnable 为 VK_TRUE，则sampleLocationsInfo.sampleLocationGridSize.width 必须均等的划分成从传入参数的samples为rasterizationSamples的vkGetPhysicalDeviceMultisamplePropertiesEXT接口返回的VkMultisamplePropertiesEXT::sampleLocationGridSize.width
																			（2）如果pMultisampleState的pNext中的VkPipelineSampleLocationsStateCreateInfoEXT::sampleLocationsEnable 为 VK_TRUE或者使用 VK_DYNAMIC_STATE_SAMPLE_LOCATIONS_ENABLE_EXT ，sampleLocationsInfo.sampleLocationGridSize.height 必须均等的划分成从传入参数的samples为rasterizationSamples的vkGetPhysicalDeviceMultisamplePropertiesEXT接口返回的VkMultisamplePropertiesEXT::sampleLocationGridSize.height
																			（3）如果pMultisampleState的pNext中的VkPipelineSampleLocationsStateCreateInfoEXT::sampleLocationsEnable 为 VK_TRUE或者使用 VK_DYNAMIC_STATE_SAMPLE_LOCATIONS_ENABLE_EXT ，sampleLocationsInfo.sampleLocationsPerPixel 必须等于 rasterizationSamples
	40.如果 pipeline 需要 fragment shader state, 且pMultisampleState的pNext中的VkPipelineSampleLocationsStateCreateInfoEXT的 sampleLocationsEnable  为 VK_TRUE, 则 fragment shader code 不能静态使用拓展的InterpolateAtSample指令
	41.如果 pipeline 需要 fragment output interface state, 且VK_AMD_mixed_attachment_samples 拓展, the VK_NV_framebuffer_mixed_samples 拓展, or the multisampledRenderToSingleSampled 特性没有一个开启, rasterizationSamples 不是动态的, 且如果 subpass 使用 color 以及或者 depth/stencil attachments,则pMultisampleState的 rasterizationSamples必须等于那些subpass的附件的采样数
	42.如果 pipeline 需要 fragment output interface state, 且VK_AMD_mixed_attachment_samples 特性开启, rasterizationSamples 不是动态的, 且如果 subpass 使用 color 以及或者 depth/stencil attachments,则pMultisampleState的 rasterizationSamples必须等于那些subpass的附件的最大的采样数
	43.如果 renderPass 不为 VK_NULL_HANDLE,  VK_EXT_multisampled_render_to_single_sampled 拓展没有开启, rasterizationSamples 不是动态的, 且 subpass的VkSubpassDescription2::pNext中含有一个VkMultisampledRenderToSingleSampledInfoEXT ，这个结构体的multisampledRenderToSingleSampledEnable为VK_TRUE, 则 pMultisampleState的rasterizationSamples 必须等于VkMultisampledRenderToSingleSampledInfoEXT::rasterizationSamples
	44.如果 pipeline 需要 fragment output interface state, 且VK_NV_framebuffer_mixed_samples 拓展没有开启, rasterizationSamples 不是动态的, 且如果 subpass 有一个 depth/stencil attachment 以及 depth test, stencil test, 或者 depth bounds test 是开启的, 则 pMultisampleState的 rasterizationSamples必须等于 depth/stencil attachment的采样数
	45.如果 pipeline 需要 fragment output interface state, 且 VK_NV_framebuffer_mixed_samples 拓展开启了, rasterizationSamples 不是动态的, 且如果 subpass 有任何 color attachments,则pMultisampleState的 rasterizationSamples 必须大于等于那些 subpass attachments 的采样数
	46.如果 pipeline 需要 fragment output interface state, 且 VK_NV_coverage_reduction_mode 拓展开启了, 且 rasterizationSamples 不是动态的, 则通过VkPipelineCoverageReductionStateCreateInfoNV::coverageReductionMode指定 coverage reduction mode ,  pMultisampleState的rasterizationSamples  以及 depth/stencil attachments (如果subpass 有的话)的采样数 必须是 vkGetPhysicalDeviceSupportedFramebufferMixedSamplesCombinationsNV返回的值的合法的组合值
	47.如果 pipeline 需要 fragment output interface state, rasterizationSamples 不是动态的, 且 subpass 没有使用任何 color 以及或者 depth/stencil attachments, 则pMultisampleState的 rasterizationSamples必须符合 无附件 subpass的规则
	48.如果renderPass 不是 VK_NULL_HANDLE, 则（1）subpass 必须有效的renderPass的 subpass 
											 （2）如果 pipeline 以 pre-rasterization shader state创建, 且subpass viewMask 不为 0, 以及 multiviewTessellationShader 没有开启, 则 pStages 不能包含 tessellation shaders
										     （3）如果 pipeline 以 pre-rasterization shader state创建, 且subpass viewMask 不为 0, 以及 multiviewGeometryShader 没有开启, 则 pStages 不能包含一个 geometry shader
											 （4）如果 pipeline 以 pre-rasterization shader state创建, 且subpass viewMask 不为 0,则pipeline的所有 shaders 在接口处不能包含以Layer built-in描述的变量
											 （5）如果 pipeline 以 pre-rasterization shader state创建, 且subpass viewMask 不为 0, 以及 multiviewMeshShader 没有开启, 则 pStages 不能包含一个 mesh shader

	49.flags 不能包含 VK_PIPELINE_CREATE_DISPATCH_BASE 
	50.如果 pipeline 需要 fragment shader state 以及一个 input attachment在renderPass创建的时候通过aspectMask 引用,则 the fragment shader 只能从该input attachment的aspects中读取数据
	51.每个shader stage中的 layout中能够访问的资源数必须小于或等于VkPhysicalDeviceLimits::maxPerStageResources
	52.如果 pipeline 需要 pre-rasterization shader state,且pDynamicState的pDynamicStates 没有 VK_DYNAMIC_STATE_VIEWPORT_W_SCALING_NV, 以及pViewportState的pNext中的VkPipelineViewportWScalingStateCreateInfoNV的viewportWScalingEnable为 VK_TRUE, 则VkPipelineViewportWScalingStateCreateInfoNV的 pViewportWScalings必须是 VkPipelineViewportWScalingStateCreateInfoNV::viewportCount 个有效的VkViewportWScalingNV 的数组首地址
	53.如果 pipeline 需要 pre-rasterization shader state,且pDynamicState的pDynamicStates 没有 VK_DYNAMIC_STATE_EXCLUSIVE_SCISSOR_NV , 且如果 pViewportState->pNext 包含一个exclusiveScissorCount不为0的VkPipelineViewportExclusiveScissorStateCreateInfoNV, 则其 pExclusiveScissors 必须是 exclusiveScissorCount 个有效的 VkRect2D 数组首地址
	54.如果pDynamicStates中包含VK_DYNAMIC_STATE_EXCLUSIVE_SCISSOR_ENABLE_NV 则实现至少支持版本为specVersion 2 版本的VK_NV_scissor_exclusive拓展 
	55.如果 pipeline 需要 pre-rasterization shader state, 且pDynamicState的pDynamicStates 没有 VK_DYNAMIC_STATE_VIEWPORT_SHADING_RATE_PALETTE_NV, 且如果 pViewportState->pNext 中包含一个 VkPipelineViewportShadingRateImageStateCreateInfoNV , 则其 pShadingRatePalettes 必须是 viewportCount个有效的 VkShadingRatePaletteNV 的数组首地址
	56.如果 pipeline 需要 pre-rasterization shader state, 且pDynamicState的pDynamicStates 没有 VK_DYNAMIC_STATE_DISCARD_RECTANGLE_EXT, 且如果 pNext 中包含一个 discardRectangleCount不为0的VkPipelineDiscardRectangleStateCreateInfoEXT ,则其 pDiscardRectangles 必须是discardRectangleCount 个有效的VkRect2D 数组首地址
	57.如果pDynamicStates中不含VK_DYNAMIC_STATE_DISCARD_RECTANGLE_ENABLE_EXT或者VK_DYNAMIC_STATE_DISCARD_RECTANGLE_MODE_EXT，则实现必须至少支持版本为specVersion 2的VK_EXT_discard_rectangles拓展
	58.如果 pipeline 需要 vertex input state, 且 pVertexInputState 不是动态的, 则pVertexInputState 必须是一个有效的VkPipelineVertexInputStateCreateInfo指针
	59.如果 pipeline 以 vertex input state创建且 pVertexInputState 不是动态的, 则 （1）所有在Vertex Execution Model OpEntryPoint以Location修饰的Input storage class变量的位置必须包含在VkVertexInputAttributeDescription::location中
																				  （2）所有在Vertex Execution Model OpEntryPoint中对应位置的Input variables的数字类型必须等于VkVertexInputAttributeDescription::format
																				  （3）如果 VkVertexInputAttributeDescription::format 有一个 64-bit component, 则所有Vertex Execution Model OpEntryPoint对应位置的Input variables的 scalar width必须为 64-bit
																				  （4） 如果所有Vertex Execution Model OpEntryPoint对应位置的Input variables的 scalar width为 64-bit, 则其对应的VkVertexInputAttributeDescription::format 必须含有一个 64-bit component
																				  （5）如果 VkVertexInputAttributeDescription::format 含有一个 64-bit component,  则所有Vertex Execution Model OpEntryPoint对应位置的Input variables不能使用在format中没有的component 

	60.如果 pipeline 需要 vertex input state, 且 VK_EXT_extended_dynamic_state3 拓展开启, 或者是 VK_DYNAMIC_STATE_PRIMITIVE_RESTART_ENABLE, 或VK_DYNAMIC_STATE_PRIMITIVE_TOPOLOGY dynamic states其中之一没有被设置, 或者 dynamicPrimitiveTopologyUnrestricted 为 VK_FALSE, pInputAssemblyState 必须是有效的 VkPipelineInputAssemblyStateCreateInfo 指针
	61.如果pInputAssemblyState 不为 NULL则必须是有效的VkPipelineInputAssemblyStateCreateInfo 指针
	62.如果 pipeline 需要 pre-rasterization shader state,  Xfb execution mode 可以在pStages的一个或多个stage中指定 , 且pStages中任何指明了specifies Xfb execution mode的 shader stage必须是 pre-rasterization shader stage中的最后一个
	63.如果 pipeline 需要 pre-rasterization shader state, 且VkPipelineRasterizationStateStreamCreateInfoEXT::rasterizationStream 指定一个不为0的值,所有入口点的输出接口的被编译描述为Position, PointSize, ClipDistance, 或者 CullDistance的变量必须以匹配rasterizationStream的单独的Stream values来描述 

	64.如果 pipeline 需要 pre-rasterization shader state, 且VkPipelineRasterizationStateStreamCreateInfoEXT::rasterizationStream 为0或者没有指定，所有入口点的输出接口的被编译描述为Position, PointSize, ClipDistance, 或者 CullDistance的变量必须以Stream values为0来描述，或者不必指明Stream描述

	65.如果 pipeline 需要 pre-rasterization shader state, 且最后的 pre-rasterizationshader stage是一个 geometry shader, 且该 geometry shader 使用 GeometryStreams capability, 则 VkPhysicalDeviceTransformFeedbackFeaturesEXT::geometryStreams 特性就必须开启
	66.如果 pipeline 需要 pre-rasterization shader state, pipeline中存在 mesh shader则pipeline中的shader stage就不能含有 Xfb execution mode
	67.如果 the pipeline 需要 pre-rasterization shader state 以及至少一个 fragment output interface state 或者 fragment shader state, 且 pMultisampleState 不为 NULL,  则pRasterizationState的pNext中的VkPipelineRasterizationLineStateCreateInfoKHR的lineRasterizationMode
							为VK_LINE_RASTERIZATION_MODE_BRESENHAM_KHR 或者VK_LINE_RASTERIZATION_MODE_RECTANGULAR_SMOOTH_KHR, 则pMultisampleState的 alphaToCoverageEnable,alphaToOneEnable, 以及 sampleShadingEnable必须全部为VK_FALSE
	68.如果 pipeline 需要 pre-rasterization shader state, VkPipelineRasterizationLineStateCreateInfoKHR的 stippledLineEnable 为VK_TRUE,  pDynamicState的pDynamicStates 没有 VK_DYNAMIC_STATE_LINE_STIPPLE_EXT, 则VkPipelineRasterizationLineStateCreateInfoKHR的lineStippleFactor必须在 [1,256]范围中
	69.flags不能包含 VK_PIPELINE_CREATE_RAY_TRACING_NO_NULL_ANY_HIT_SHADERS_BIT_KHR，VK_PIPELINE_CREATE_RAY_TRACING_NO_NULL_CLOSEST_HIT_SHADERS_BIT_KHR以及 VK_PIPELINE_CREATE_RAY_TRACING_NO_NULL_MISS_SHADERS_BIT_KHR，
							VK_PIPELINE_CREATE_RAY_TRACING_NO_NULL_INTERSECTION_SHADERS_BIT_KHR，VK_PIPELINE_CREATE_RAY_TRACING_SKIP_TRIANGLES_BIT_KHR， VK_PIPELINE_CREATE_RAY_TRACING_SKIP_AABBS_BIT_KHR，
							VK_PIPELINE_CREATE_RAY_TRACING_SHADER_GROUP_HANDLE_CAPTURE_REPLAY_BIT_KHR 以及 VK_PIPELINE_CREATE_RAY_TRACING_ALLOW_MOTION_BIT_NV
	70.如果 extendedDynamicState 特性没有开启, 且创建VkInstance的VkApplicationInfo::apiVersion 小于 Version 1.3 则pDynamicState的pDynamicStates就不能有 VK_DYNAMIC_STATE_CULL_MODE,
																								VK_DYNAMIC_STATE_FRONT_FACE, VK_DYNAMIC_STATE_PRIMITIVE_TOPOLOGY,
																								VK_DYNAMIC_STATE_VIEWPORT_WITH_COUNT, VK_DYNAMIC_STATE_SCISSOR_WITH_COUNT,
																								VK_DYNAMIC_STATE_VERTEX_INPUT_BINDING_STRIDE, VK_DYNAMIC_STATE_DEPTH_TEST_ENABLE,
																								VK_DYNAMIC_STATE_DEPTH_WRITE_ENABLE, VK_DYNAMIC_STATE_DEPTH_COMPARE_OP,
																								VK_DYNAMIC_STATE_DEPTH_BOUNDS_TEST_ENABLE, VK_DYNAMIC_STATE_STENCIL_TEST_ENABLE, 或者
																								VK_DYNAMIC_STATE_STENCIL_OP 设置
	71.如果 pipeline 需要 pre-rasterization shader state, 且pDynamicStates中包含VK_DYNAMIC_STATE_VIEWPORT_WITH_COUNT，则（1）viewportCount 必须为0
																														（2）VK_DYNAMIC_STATE_VIEWPORT就不能包含在pDynamicStates中
																												 
	72.如果 pipeline 需要 pre-rasterization shader state, 且pDynamicStates中包含VK_DYNAMIC_STATE_SCISSOR_WITH_COUNT，则（1）scissorCount 必须为0
																													   （2）VK_DYNAMIC_STATE_SCISSOR就不能包含在pDynamicStates中


	73.如果 pipeline 需要 pre-rasterization shader state, 且包含一个 a mesh shader,pDynamicState的pDynamicStates中就不能有 VK_DYNAMIC_STATE_PRIMITIVE_TOPOLOGY, 或者 VK_DYNAMIC_STATE_VERTEX_INPUT_BINDING_STRIDE
	74.如果 extendedDynamicState2 特性没有开启, 用来创建VkInstance的VkApplicationInfo::apiVersion 小于 Version 1.3 则pDynamicState的pDynamicStates就不能有VK_DYNAMIC_STATE_DEPTH_BIAS_ENABLE, VK_DYNAMIC_STATE_PRIMITIVE_RESTART_ENABLE, 或者VK_DYNAMIC_STATE_RASTERIZER_DISCARD_ENABLE
	75.如果 extendedDynamicState2LogicOp 特性没有开启,  则pDynamicState的pDynamicStates就不能有 VK_DYNAMIC_STATE_LOGIC_OP_EXT
	76.如果 extendedDynamicState2PatchControlPoints 特性没有开启,  则pDynamicState的pDynamicStates就不能有 VK_DYNAMIC_STATE_PATCH_CONTROL_POINTS_EXT
	77.如果 pipeline 需要 pre-rasterization shader state, 且包含一个 a mesh shader,  则pDynamicState的pDynamicStates就不能有VK_DYNAMIC_STATE_PRIMITIVE_RESTART_ENABLE, or VK_DYNAMIC_STATE_PATCH_CONTROL_POINTS_EXT
	78.如果 flags 包含 VK_PIPELINE_CREATE_INDIRECT_BINDABLE_BIT_NV, 则deviceGeneratedCommands 特性必须开启
	79.如果 pipeline 需要 pre-rasterization shader state 且 flags 包含 VK_PIPELINE_CREATE_INDIRECT_BINDABLE_BIT_NV, 则所有的stages不能指定 Xfb execution mode
	80.如果 pipeline 不是以完整的state集创建的, 或者VkPipelineLibraryCreateInfoKHR::libraryCount 不为 0,则 VkGraphicsPipelineShaderGroupsCreateInfoNV::groupCount 以及 VkGraphicsPipelineShaderGroupsCreateInfoNV::pipelineCount 必须为 0
	81.如果 pipeline 是以完整的state集创建的, 且VkPipelineLibraryCreateInfoKHR::libraryCount 为 0, 且pNext中包含一个 VkGraphicsPipelineShaderGroupsCreateInfoNV,则 VkGraphicsPipelineShaderGroupsCreateInfoNV::groupCount 必须大于 0
	82.如果 pipelineCreationCacheControl 特性没有开启, flags 不能包含 VK_PIPELINE_CREATE_FAIL_ON_PIPELINE_COMPILE_REQUIRED_BIT 或者 VK_PIPELINE_CREATE_EARLY_RETURN_ON_FAILURE_BIT
	83.如果 pipelineProtectedAccess 特性没有开启, flags 不能包含VK_PIPELINE_CREATE_NO_PROTECTED_ACCESS_BIT_EXT 或者 VK_PIPELINE_CREATE_PROTECTED_ACCESS_ONLY_BIT_EXT
	84.flags 不能同时包含 VK_PIPELINE_CREATE_NO_PROTECTED_ACCESS_BIT_EXT 和 VK_PIPELINE_CREATE_PROTECTED_ACCESS_ONLY_BIT_EXT
	85.如果 pipeline 需要 pre-rasterization shader state 或者 fragment shader state 且pDynamicState->pDynamicState中不含VK_DYNAMIC_STATE_FRAGMENT_SHADING_RATE_KHR , 则
											（1）VkPipelineFragmentShadingRateStateCreateInfoKHR::fragmentSize.width必须大于或等于1，VkPipelineFragmentShadingRateStateCreateInfoKHR::fragmentSize.height必须大于或等于1，且两者都为2的指数，且都必须小于或者等于4，
											（2）如果pipelineFragmentShadingRate特性没有开启，则VkPipelineFragmentShadingRateStateCreateInfoKHR::fragmentSize.width以及VkPipelineFragmentShadingRateStateCreateInfoKHR::fragmentSize.height必须同时为1
											（3）则VkPipelineFragmentShadingRateStateCreateInfoKHR::combinerOps[0]，combinerOps[1]必须是一个有效的VkFragmentShadingRateCombinerOpKHR值
											（4）如果primitiveFragmentShadingRate特性没有开启，则VkPipelineFragmentShadingRateStateCreateInfoKHR::combinerOps[0]，combinerOps[1]必须为VK_FRAGMENT_SHADING_RATE_COMBINER_OP_KEEP_KHR

	86.如果 pipeline 需要 pre-rasterization shader state 且 primitiveFragmentShadingRateWithMultipleViewports 限制不支持,则（1）如果pDynamicState->pDynamicStates中不包含VK_DYNAMIC_STATE_VIEWPORT_WITH_COUNT ,且 VkPipelineViewportStateCreateInfo::viewportCount 大于 1,则pStages的入口点不能写 PrimitiveShadingRateKHR built-in
																														   （2）则pStages的入口点写入到ViewportIndex built-in，但不能写 PrimitiveShadingRateKHR built-in
																														   （3）则pStages的入口点写入到ViewportMaskNV built-in，但不能写 PrimitiveShadingRateKHR built-in


	87.如果 pipeline 需要 pre-rasterization shader state 或者 fragment shader state,  fragmentShadingRateNonTrivialCombinerOps 限制不支持, 且pDynamicState->pDynamicStates中不含 VK_DYNAMIC_STATE_FRAGMENT_SHADING_RATE_KHR ,  VkPipelineFragmentShadingRateStateCreateInfoKHR::combinerOps 的元素必须为 VK_FRAGMENT_SHADING_RATE_COMBINER_OP_KEEP_KHR 或者 VK_FRAGMENT_SHADING_RATE_COMBINER_OP_REPLACE_KHR
	88.如果 pipeline 需要 fragment shader state 且pDynamicState->pDynamicStates中不含 VK_DYNAMIC_STATE_FRAGMENT_SHADING_RATE_KHR ,则（1） VkPipelineFragmentShadingRateEnumStateCreateInfoNV::shadingRateType 必须是一个有效的VkFragmentShadingRateTypeNV值
																																	（2）则 VkPipelineFragmentShadingRateEnumStateCreateInfoNV::shadingRate必须是一个有效的 VkFragmentShadingRateNV 值
																																	（3）则VkPipelineFragmentShadingRateEnumStateCreateInfoNV::combinerOps[0]，combinerOps[1] 必须是一个有效的 VkFragmentShadingRateCombinerOpKHR 值
																																	（4）如果 fragmentShadingRateEnums 特性没有开启,VkPipelineFragmentShadingRateEnumStateCreateInfoNV::shadingRateType 必须为 VK_FRAGMENT_SHADING_RATE_TYPE_FRAGMENT_SIZE_NV
																																	（5） 如果pipelineFragmentShadingRate 特性没有开启 ,则VkPipelineFragmentShadingRateEnumStateCreateInfoNV::shadingRate 必须等于 VK_FRAGMENT_SHADING_RATE_1_INVOCATION_PER_PIXEL_NV
																																	（6）如果 primitiveFragmentShadingRate 特性没有开启，则VkPipelineFragmentShadingRateEnumStateCreateInfoNV::combinerOps[0] 必须为VK_FRAGMENT_SHADING_RATE_COMBINER_OP_KEEP_KHR
																																	（7）如果 attachmentFragmentShadingRate 特性没有开启,则VkPipelineFragmentShadingRateEnumStateCreateInfoNV::combinerOps[1] 必须为VK_FRAGMENT_SHADING_RATE_COMBINER_OP_KEEP_KHR
	89.如果 pipeline 需要 fragment shader state, 且 fragmentShadingRateNonTrivialCombinerOps 限制不支持且pDynamicState->pDynamicStates中不包含VK_DYNAMIC_STATE_FRAGMENT_SHADING_RATE_KHR  , VkPipelineFragmentShadingRateEnumStateCreateInfoNV::combinerOps中的元素必须为 VK_FRAGMENT_SHADING_RATE_COMBINER_OP_KEEP_KHR 或者VK_FRAGMENT_SHADING_RATE_COMBINER_OP_REPLACE_KHR
	90.如果 pipeline 需要 fragment shader state, 且 supersampleFragmentShadingRates特性没有开启, VkPipelineFragmentShadingRateEnumStateCreateInfoNV::shadingRate不能等于 VK_FRAGMENT_SHADING_RATE_2_INVOCATIONS_PER_PIXEL_NV,VK_FRAGMENT_SHADING_RATE_4_INVOCATIONS_PER_PIXEL_NV,VK_FRAGMENT_SHADING_RATE_8_INVOCATIONS_PER_PIXEL_NV, 或者VK_FRAGMENT_SHADING_RATE_16_INVOCATIONS_PER_PIXEL_NV
	91.如果 pipeline 需要 fragment shader state, 且 noInvocationFragmentShadingRates特性没有开启, VkPipelineFragmentShadingRateEnumStateCreateInfoNV::shadingRate 不能等于 VK_FRAGMENT_SHADING_RATE_NO_INVOCATIONS_NV
	92.pDynamicState的pDynamicStates的所有元素不能为VK_DYNAMIC_STATE_RAY_TRACING_PIPELINE_STACK_SIZE_KHR
	93.如果 pipeline 需要 pre-rasterization shader state 且 vertexInputDynamicState特性没有开启, pDynamicState的pDynamicStates中不能有VK_DYNAMIC_STATE_VERTEX_INPUT_EXT
	94.如果 pipeline 需要 pre-rasterization shader state, 且包含一个 mesh shader, 则pDynamicState的pDynamicStates中不能有VK_DYNAMIC_STATE_VERTEX_INPUT_EXT
	95.如果 colorWriteEnable 特性没有开启, 则pDynamicState的pDynamicStates中不能有 VK_DYNAMIC_STATE_COLOR_WRITE_ENABLE_EXT
	96.如果pipeline 需要 fragment shader state, 且VK_QCOM_render_pass_shader_resolve 拓展开启,则（1） rasterizationSamples 不是动态的, 且如果 subpass 有任何 input attachments, 以及如果  subpass description 包含 VK_SUBPASS_DESCRIPTION_FRAGMENT_REGION_BIT_QCOM, 则 input attachments的采样数必须等于 rasterizationSamples
																								（2）如果 the subpass description包含 VK_SUBPASS_DESCRIPTION_FRAGMENT_REGION_BIT_QCOM, 则 sampleShadingEnable必须为 false
	97.如果 flags 包含 VK_SUBPASS_DESCRIPTION_SHADER_RESOLVE_BIT_QCOM, 则（1） subpass 必须是subpass 依赖链中的最后一个subpass
																		 （2）且如果pResolveAttachments 为 NULL, 则每一个 resolve attachment 必须为VK_ATTACHMENT_UNUSED
	
	98.如果 dynamicRendering 特性没有开启且 pipeline 需要 pre-rasterization shader state, fragment shader state, 或者 fragment output interface state, 则renderPass 不能为 VK_NULL_HANDLE
	99.如果multiview 特性没有开启,  pipeline 需要 pre-rasterization shader state, fragment shader state, 或者 fragment output interface state, 且 renderPass 为VK_NULL_HANDLE, 则VkPipelineRenderingCreateInfo::viewMask 必须是 0
	100.如果 pipeline 需要 pre-rasterization shader state, fragment shader state, 或者 fragmentoutput interface state, 且 renderPass 为 VK_NULL_HANDLE, 则VkPipelineRenderingCreateInfo::viewMask有效位的索引必须小于maxMultiviewViewCount
	101.如果 pipeline 需要 fragment output interface state, 且 renderPass 为 VK_NULL_HANDLE, 则（1）如果 VkPipelineRenderingCreateInfo::colorAttachmentCount 不为 0,则VkPipelineRenderingCreateInfo::pColorAttachmentFormats 必须是 colorAttachmentCount个有效的 VkFormat值的数组首地址
																							   （2）则 VkPipelineRenderingCreateInfo::pColorAttachmentFormats 中的每个元素必须是有效的 VkFormat 值
																							   （3）VkPipelineRenderingCreateInfo::pColorAttachmentFormats中任何不是VK_FORMAT_UNDEFINED的值必须是一个potential format features VK_FORMAT_FEATURE_COLOR_ATTACHMENT_BIT 或者 VK_FORMAT_FEATURE_2_LINEAR_COLOR_ATTACHMENT_BIT_NV的format
																							   （4）则VkPipelineRenderingCreateInfo::depthAttachmentFormat必须为一个有效的VkFormat值
																							   （5） VkPipelineRenderingCreateInfo::stencilAttachmentFormat必须为一个有效的VkFormat值
																							   （6）如果 VkPipelineRenderingCreateInfo::depthAttachmentFormat 不是 VK_FORMAT_UNDEFINED,则其必须是一个potential format features含有VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT的format值
																							   （7）如果 VkPipelineRenderingCreateInfo::stencilAttachmentFormat 不是 VK_FORMAT_UNDEFINED,则其必须是一个potential format features含有VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT的format值
																							   （8）如果 VkPipelineRenderingCreateInfo::depthAttachmentFormat 不为 VK_FORMAT_UNDEFINED, 其 format 必须包含 depth component
																							   （9）如果 VkPipelineRenderingCreateInfo::stencilAttachmentFormat 不为 VK_FORMAT_UNDEFINED,其 format 必须包含一个 stencil component
																							   （10）如果VkPipelineRenderingCreateInfo::depthAttachmentFormat 不为 VK_FORMAT_UNDEFINED, 且VkPipelineRenderingCreateInfo::stencilAttachmentFormat 不为 VK_FORMAT_UNDEFINED,depthAttachmentFormat 必须等于 stencilAttachmentFormat
	102.如果 renderPass 为 VK_NULL_HANDLE,  pipeline 以 fragment shader state和 fragment output interface state创建, 且  VkPipelineRenderingCreateInfo::depthAttachmentFormat 或者 VkPipelineRenderingCreateInfo::stencilAttachmentFormat 两者其一不为 VK_FORMAT_UNDEFINED, 且 VK_EXT_extended_dynamic_state3 拓展没有开启 或者 VK_DYNAMIC_STATE_DEPTH_TEST_ENABLE, VK_DYNAMIC_STATE_DEPTH_WRITE_ENABLE,
																								VK_DYNAMIC_STATE_DEPTH_COMPARE_OP, VK_DYNAMIC_STATE_DEPTH_BOUNDS_TEST_ENABLE, VK_DYNAMIC_STATE_STENCIL_TEST_ENABLE, VK_DYNAMIC_STATE_STENCIL_OP,或VK_DYNAMIC_STATE_DEPTH_BOUNDS dynamic states 任何之一没有设置, pDepthStencilState必须是一个有效的 VkPipelineDepthStencilStateCreateInfo 指针
	103.如果 pDepthStencilState 不为 NULL就必须为一个有效的 VkPipelineDepthStencilStateCreateInfo 指针
	104.如果 renderPass 为 VK_NULL_HANDLE,  pipeline 以 fragment shader state但不以 fragment output interface state创建, 且 VK_EXT_extended_dynamic_state3拓展没有开启, 或者 VK_DYNAMIC_STATE_DEPTH_TEST_ENABLE,VK_DYNAMIC_STATE_DEPTH_WRITE_ENABLE, VK_DYNAMIC_STATE_DEPTH_COMPARE_OP,VK_DYNAMIC_STATE_DEPTH_BOUNDS_TEST_ENABLE, VK_DYNAMIC_STATE_STENCIL_TEST_ENABLE,VK_DYNAMIC_STATE_STENCIL_OP, 
																								或者 VK_DYNAMIC_STATE_DEPTH_BOUNDS dynamic states 任何之一没有设置, pDepthStencilState 必须是一个有效的 VkPipelineDepthStencilStateCreateInfo 指针
	105.如果 pDepthStencilState 不为 NULL就必须为一个有效的 VkPipelineDepthStencilStateCreateInfo 指针
	106.如果 renderPass 为 VK_NULL_HANDLE,  pipeline 以 fragment output interface state创建, 且VkPipelineRenderingCreateInfo::pColorAttachmentFormats的任何元素不是 VK_FORMAT_UNDEFINED, 且 VK_EXT_extended_dynamic_state3 拓展没有开启,或者是 VK_DYNAMIC_STATE_LOGIC_OP_ENABLE_EXT, VK_DYNAMIC_STATE_LOGIC_OP_EXT, VK_DYNAMIC_STATE_COLOR_BLEND_ENABLE_EXT, VK_DYNAMIC_STATE_COLOR_BLEND_EQUATION_EXT,
																								VK_DYNAMIC_STATE_COLOR_WRITE_MASK_EXT, 或 VK_DYNAMIC_STATE_BLEND_CONSTANTS dynamic states 任何之一没有设置, pColorBlendState必须是一个有效的 VkPipelineColorBlendStateCreateInfo 指针
	
	
	107.如果 pColorBlendState 不为 NULL 就必须为一个有效的VkPipelineColorBlendStateCreateInfo 指针
	108.如果 renderPass 为 VK_NULL_HANDLE, pColorBlendState 不是动态的, 且 pipeline 以 fragment output interface state创建, 则pColorBlendState->attachmentCount 必须等于 VkPipelineRenderingCreateInfo::colorAttachmentCount
	109.如果 renderPass 为 VK_NULL_HANDLE,  pipeline 以 pre-rasterization shader state创建, VkPipelineRenderingCreateInfo::viewMask 不为 0, 则（1）如果 multiviewTessellationShader 特性没有开启, 则 pStages不能包含 tessellation shaders
																																			  （2）如果multiviewGeometryShader 特性没有开启, 则 pStages 不能包含一个 geometry shader
																																			  （3）管线中所有shaders的interfaces不能含有以Layer built-in decoration修饰的变量
																																			  （4）如果 multiviewMeshShader 没有开启, 则 pStages 不能包含一个 mesh shader
	110.如果 dynamicRenderingLocalRead 特性没有开启,  pipeline 需要 fragmentshader state, 且 renderPass 为 VK_NULL_HANDLE, pStages的fragment shaders不能包含 InputAttachment capability
	111.如果 pipeline 需要 fragment shader state 且 renderPass 不是 VK_NULL_HANDLE, pStages的fragment shaders 不能包含任何 TileImageColorReadAccessEXT, TileImageDepthReadAccessEXT, 或者 TileImageStencilReadAccessEXT capabilities
	112.如果 pipeline 需要 fragment output interface state 且 renderPass 为VK_NULL_HANDLE, 则（1）VkPipelineRenderingCreateInfo的pColorAttachmentFormats定义的每一个 color attachment format 如果其  potentialformat features 不包含 VK_FORMAT_FEATURE_COLOR_ATTACHMENT_BLEND_BIT, 则对应到pAttachments的pColorBlendState的 blendEnable 必须为 VK_FALSE
																							 （2）如果 pNext 中包含 VkAttachmentSampleCountInfoAMD 或者 VkAttachmentSampleCountInfoNV, 则其 colorAttachmentCount 必须等于 VkPipelineRenderingCreateInfo::colorAttachmentCount
	113.如果 pStages 包含一个 fragment shader stage, 且 fragment shader 声明了 EarlyFragmentTests execution mode, 则 VkPipelineDepthStencilStateCreateInfo的flags 不能包含 VK_PIPELINE_DEPTH_STENCIL_STATE_CREATE_RASTERIZATION_ORDER_ATTACHMENT_DEPTH_ACCESS_BIT_EXT 或者 VK_PIPELINE_DEPTH_STENCIL_STATE_CREATE_RASTERIZATION_ORDER_ATTACHMENT_STENCIL_ACCESS_BIT_EXT
	114.如果 dynamicRenderingLocalRead 特性没有开启,  pipeline 需要 fragment output interface state, 则（1）如果VkPipelineColorBlendStateCreateInfo的  flags包含 VK_PIPELINE_COLOR_BLEND_STATE_CREATE_RASTERIZATION_ORDER_ATTACHMENT_ACCESS_BIT_EXT, 则renderPass 不能为 VK_NULL_HANDLE
																									   （2）如果VkPipelineDepthStencilStateCreateInfo的 flags包含VK_PIPELINE_DEPTH_STENCIL_STATE_CREATE_RASTERIZATION_ORDER_ATTACHMENT_DEPTH_ACCESS_BIT_EXT 或者VK_PIPELINE_DEPTH_STENCIL_STATE_CREATE_RASTERIZATION_ORDER_ATTACHMENT_STENCIL_ACCESS_BIT_EXT, renderPass 不能为 VK_NULL_HANDLE
	115.如果 pipeline 需要 fragment output interface state,则（1） VkAttachmentSampleCountInfoAMD 或者 VkAttachmentSampleCountInfoNV的pColorAttachmentSamples的元素必须是有效的 VkSampleCountFlagBits 值
															 （2）如果VkAttachmentSampleCountInfoAMD 或者 VkAttachmentSampleCountInfoNV的 depthStencilAttachmentSamples 不为 0, 则其必须是一个有效的 VkSampleCountFlagBits 值
															 （3）如果 renderPass 不为 VK_NULL_HANDLE, VkPipelineColorBlendStateCreateInfo的 flags 包含 VK_PIPELINE_COLOR_BLEND_STATE_CREATE_RASTERIZATION_ORDER_ATTACHMENT_ACCESS_BIT_EXT 则subpass 必须以 VK_SUBPASS_DESCRIPTION_RASTERIZATION_ORDER_ATTACHMENT_COLOR_ACCESS_BIT_EXT创建
	
	
	
	116.如果 pipeline 需要 fragment shader state, renderPass 不为 VK_NULL_HANDLE, 则（1）如果VkPipelineDepthStencilStateCreateInfo的 flags 包含 VK_PIPELINE_DEPTH_STENCIL_STATE_CREATE_RASTERIZATION_ORDER_ATTACHMENT_DEPTH_ACCESS_BIT_EXT, subpass 必须以 VK_SUBPASS_DESCRIPTION_RASTERIZATION_ORDER_ATTACHMENT_DEPTH_ACCESS_BIT_EXT创建
																					（2）如果VkPipelineDepthStencilStateCreateInfo的 flags包含VK_PIPELINE_DEPTH_STENCIL_STATE_CREATE_RASTERIZATION_ORDER_ATTACHMENT_STENCIL_ACCESS_BIT_EXT, subpass 必须以 VK_SUBPASS_DESCRIPTION_RASTERIZATION_ORDER_ATTACHMENT_STENCIL_ACCESS_BIT_EXT创建
	117.如果 VkPipelineCreationFeedbackCreateInfo::pipelineStageCreationFeedbackCount不为 0, 则必须等于stageCount
	118.如果 renderPass 为 VK_NULL_HANDLE,  pipeline 以 pre-rasterization shader state 或者 fragment shader state创建, 且 VkMultiviewPerViewAttributesInfoNVX::perViewAttributesPositionXOnly 为 VK_TRUE 则 VkMultiviewPerViewAttributesInfoNVX::perViewAttributes 也要 VK_TRUE
	119.如果 VkGraphicsPipelineLibraryCreateInfoEXT::flags 只包含 VK_GRAPHICS_PIPELINE_LIBRARY_PRE_RASTERIZATION_SHADERS_BIT_EXT 或者 VK_GRAPHICS_PIPELINE_LIBRARY_FRAGMENT_SHADER_BIT_EXT其中一个,且  VkPipelineLibraryCreateInfoKHR::pLibraries的一个元素包含另外一个,则（1）在pipeline以及library中指定的 VkMultiviewPerViewAttributesInfoNVX::perViewAttributes 必须相同
						（2）																																																											  （2）在pipeline以及library中指定的 VkMultiviewPerViewAttributesInfoNVX::perViewAttributesPositionXOnly 必须相同								
	120. 如果 VkPipelineLibraryCreateInfoKHR::pLibraries的一个元素 包含 VK_GRAPHICS_PIPELINE_LIBRARY_PRE_RASTERIZATION_SHADERS_BIT_EXT 且其他的元素包含  VK_GRAPHICS_PIPELINE_LIBRARY_FRAGMENT_SHADER_BIT_EXT, 则（1）这些libraries中指定的 VkMultiviewPerViewAttributesInfoNVX::perViewAttributes必须相同
																																																				 （2）这些libraries中指定的 VkMultiviewPerViewAttributesInfoNVX::perViewAttributesPositionXOnly必须相同
	
	121.如果 pipeline 需要 pre-rasterization shader state 或者 fragment shader state,则 pStages 必须是 stageCount个有效的 VkPipelineShaderStageCreateInfo 的数组首地址

	122.如果 pipeline 不需要 pre-rasterization shader state 或者 fragment shader state, 则stageCount 必须为 zero
	123.如果 VkGraphicsPipelineLibraryCreateInfoEXT::flags 包含 VK_GRAPHICS_PIPELINE_LIBRARY_PRE_RASTERIZATION_SHADERS_BIT_EXT, 且 VK_EXT_extended_dynamic_state3 拓展没有开启, 或者 VK_DYNAMIC_STATE_RASTERIZATION_SAMPLES_EXT, VK_DYNAMIC_STATE_SAMPLE_MASK_EXT, 或 VK_DYNAMIC_STATE_ALPHA_TO_COVERAGE_ENABLE_EXT dynamic states 
														任何之一没有设置, 或者 alphaToOne 在 device 上启用但 VK_DYNAMIC_STATE_ALPHA_TO_ONE_ENABLE_EXT 没有设置, 则 pMultisampleState 必须是有效的 VkPipelineMultisampleStateCreateInfo 指针
	124.如果 pRasterizationState 不为 NULL 就必须是有效的 VkPipelineRasterizationStateCreateInfo 指针
	125.如果 pipeline 需要 fragment shader state 或者 pre-rasterization shader state, layout必须是有效的 VkPipelineLayout 句柄
	126.如果 pipeline 需要 pre-rasterization shader state, fragment shader state, 或者 fragment output state, 且 renderPass 不为 VK_NULL_HANDLE, renderPass 必须是有效的 VkRenderPass 句柄
	127.如果  pipeline 需要 pre-rasterization shader state, stageCount 必须大于 0 
	128.如果 graphicsPipelineLibrary 特性未开启, flags 不能包含 VK_PIPELINE_CREATE_LIBRARY_BIT_KHR
	129.如果 pipeline 定义, 或者以 libraries包含, 所有的完整的pipeline所需的 state subsets required, flags 不能包含 VK_PIPELINE_CREATE_LIBRARY_BIT_KHR
	130.如果 flags 包含 VK_PIPELINE_CREATE_LINK_TIME_OPTIMIZATION_BIT_EXT, 通过 VkPipelineLibraryCreateInfoKHR 包含的pipeline libraries 必须以 VK_PIPELINE_CREATE_RETAIN_LINK_TIME_OPTIMIZATION_INFO_BIT_EXT创建
	131.如果 flags 包含 VK_PIPELINE_CREATE_RETAIN_LINK_TIME_OPTIMIZATION_INFO_BIT_EXT, 则（1）flags就不能包含 VK_PIPELINE_CREATE_LIBRARY_BIT_KHR
																						 （2） 通过 VkPipelineLibraryCreateInfoKHR 包含的 pipeline libraries 必须以 VK_PIPELINE_CREATE_RETAIN_LINK_TIME_OPTIMIZATION_INFO_BIT_EXT创建
		
	132.任何通过 VkPipelineLibraryCreateInfoKHR::pLibraries 包含的 pipeline libraries 不能包含任何已经被VkGraphicsPipelineCreateInfo定义的或者在其他的VkPipelineLibraryCreateInfoKHR::pLibraries的 pipeline library的state subset 
	
	133.如果 VkGraphicsPipelineLibraryCreateInfoEXT::flags 只包含VK_GRAPHICS_PIPELINE_LIBRARY_PRE_RASTERIZATION_SHADERS_BIT_EXT 或者VK_GRAPHICS_PIPELINE_LIBRARY_FRAGMENT_SHADER_BIT_EXT其中一个, VkPipelineLibraryCreateInfoKHR::pLibraries 的一个元素包含另外一个, 则（1）如果 layout 不以 VK_PIPELINE_LAYOUT_CREATE_INDEPENDENT_SETS_BIT_EXT创建, 则pipeline 和 library 用的 layout必须是相同定义的
																																																																	   （2）如果 layout 以 VK_PIPELINE_LAYOUT_CREATE_INDEPENDENT_SETS_BIT_EXT创建的 ，则被library使用的layout也需要以VK_PIPELINE_LAYOUT_CREATE_INDEPENDENT_SETS_BIT_EXT创建
																																																																	   （3）如果 layout 以VK_PIPELINE_LAYOUT_CREATE_INDEPENDENT_SETS_BIT_EXT创建, pSetLayouts中的不是VK_NULL_HANDLE的创建的元素必须是和创建library的pSetLayouts相同索引的元素相同定义的 
																																																																	   （4） 任何在pipeline以及library中包含每一个shader stage对bindings访问的layout中指定的 descriptor set layout N 必须是相同定义的
																																																																	   （5）在pipeline和library中可以被每一个shader stages访问的layout中的 push constants必须是相同定义的
																																																																	   （6）任何用pSetLayouts 中创建的layout以及用来创建library的layout的pSetLayouts中的对应元素都不能同时为 VK_NULL_HANDLE
																																																																	   （7） 如果pSetLayouts的任何元素创建为VK_NULL_HANDLE，则用来创建其他library的layout的pSetLayouts中的对应元素在其他的subset中的shaders中不能有shader bindings
																																																																	   （8）如果用来创建library的layout的pSetLayouts的任何元素为VK_NULL_HANDLE，则用来创建pipeline的layout的pSetLayouts中的对应元素在其他的subset中的shaders中不能有shader bindings
	134.如果VkPipelineLibraryCreateInfoKHR::pLibraries的一个元素 包含 VK_GRAPHICS_PIPELINE_LIBRARY_PRE_RASTERIZATION_SHADERS_BIT_EXT且其他的元素包含  VK_GRAPHICS_PIPELINE_LIBRARY_FRAGMENT_SHADER_BIT_EXT, 则（1）如果 任意一个 library 指定的 layout 不以 VK_PIPELINE_LAYOUT_CREATE_INDEPENDENT_SETS_BIT_EXT创建, 则每个library使用的 layout必须是相同定义的
																																																			  （2）如果 任意一个 library 指定的 layout 以 VK_PIPELINE_LAYOUT_CREATE_INDEPENDENT_SETS_BIT_EXT创建, 则这些 library使用的 layout也需要以VK_PIPELINE_LAYOUT_CREATE_INDEPENDENT_SETS_BIT_EXT创建
																																																			  （3）如果 任意一个 library 指定的 layout 以 VK_PIPELINE_LAYOUT_CREATE_INDEPENDENT_SETS_BIT_EXT创建，则pSetLayouts中的不是VK_NULL_HANDLE的创建的元素必须是和创建library的pSetLayouts相同索引的元素相同定义的
																																																			  （4） 任何在这些library中包含每一个shader stage对bindings访问的layout中指定的 descriptor set layout N 必须是相同定义的 
																																																			  （5）在pipeline和library中可以被每一个shader stages访问的layout中的 push constants必须是相同定义的
																																																			  （6）任何pSetLayouts 中用来创建每个library的layout不为VK_NULL_HANDLE，则用来创建其他library的pSetLayouts中的对应元素也不能为 VK_NULL_HANDLE
																																																			  （7）如果用来创建每个library的layout的pSetLayouts的任何元素为VK_NULL_HANDLE，则用来创建其他library的layout的pSetLayouts中的对应元素在其他的subset中的shaders中不能有shader bindings


	135.如果 VkGraphicsPipelineLibraryCreateInfoEXT::flags 同时包含VK_GRAPHICS_PIPELINE_LIBRARY_PRE_RASTERIZATION_SHADERS_BIT_EXT 以及VK_GRAPHICS_PIPELINE_LIBRARY_FRAGMENT_SHADER_BIT_EXT, layout 创建时的 pSetLayouts 中没有元素为 VK_NULL_HANDLE
	136.如果VkGraphicsPipelineLibraryCreateInfoEXT::flags 包含 VK_GRAPHICS_PIPELINE_LIBRARY_PRE_RASTERIZATION_SHADERS_BIT_EXT 且 pRasterizationState->rasterizerDiscardEnable 为 VK_TRUE,  layout 创建时的 pSetLayouts 中没有元素为 VK_NULL_HANDLE
	137.如果 VkGraphicsPipelineLibraryCreateInfoEXT::flags 包含至少一个且不超过两个的 VK_GRAPHICS_PIPELINE_LIBRARY_PRE_RASTERIZATION_SHADERS_BIT_EXT, VK_GRAPHICS_PIPELINE_LIBRARY_FRAGMENT_SHADER_BIT_EXT, 或者 VK_GRAPHICS_PIPELINE_LIBRARY_FRAGMENT_OUTPUT_INTERFACE_BIT_EXT, VkPipelineLibraryCreateInfoKHR::pLibraries的一个元素包含另外的flags中的一个, 则 （1）subpass 必须等于用来创建 library的值
																																																																																								 （2）如果renderpass不为VK_NULL_HANDLE，renderPass就必须和用来创建library的renderpass兼容
																																																																																								 （3）如果renderpass为VK_NULL_HANDLE，则用来创建library的renderpass也必须为VK_NULL_HANDLE
																																																																																								 （4）如果renderpass为VK_NULL_HANDLE，则pipeline使用的VkPipelineRenderingCreateInfo::viewMask值必须等于 library 中指定的该值
	138.如果  VkPipelineLibraryCreateInfoKHR::pLibraries 的一个元素包含至少一个且不超过两个的VK_GRAPHICS_PIPELINE_LIBRARY_PRE_RASTERIZATION_SHADERS_BIT_EXT,VK_GRAPHICS_PIPELINE_LIBRARY_FRAGMENT_SHADER_BIT_EXT, 或者 VK_GRAPHICS_PIPELINE_LIBRARY_FRAGMENT_OUTPUT_INTERFACE_BIT_EXT, 且VkPipelineLibraryCreateInfoKHR::pLibraries的另外一个元素包含这些flags中的另外一个 ,  则：
																																																																																							（1） 用来创建每一个library的 subpass 必须相等
																																																																																							（2）如果这些libraries的renderpass为VK_NULL_HANDLE，则每一个library的VkPipelineRenderingCreateInfo::viewMask必须是相同的
																																																																																							（3）则同来创建每一个library的renderPass必须是兼容的或者全部为VK_NULL_HANDLE
	139.如果 renderPass 不为 VK_NULL_HANDLE,  pipeline 需要 fragment shader state, 且the VK_EXT_extended_dynamic_state3 拓展没有开启或者是VK_DYNAMIC_STATE_RASTERIZATION_SAMPLES_EXT, VK_DYNAMIC_STATE_SAMPLE_MASK_EXT, 或 VK_DYNAMIC_STATE_ALPHA_TO_COVERAGE_ENABLE_EXT dynamic states 任意一个没有设置, 或者 alphaToOne 在 device  上启用而 VK_DYNAMIC_STATE_ALPHA_TO_ONE_ENABLE_EXT 没有设置, 则 pMultisampleState 必须是一个有效的 VkPipelineMultisampleStateCreateInfo 指针
	140.如果  pipeline 需要 fragment shader state 且其 fragment shader 要么支持  sample shading 要么支持任何以Sample修饰Input storage class中的任何变量 ,  且the VK_EXT_extended_dynamic_state3 拓展没有开启或者是VK_DYNAMIC_STATE_RASTERIZATION_SAMPLES_EXT, VK_DYNAMIC_STATE_SAMPLE_MASK_EXT, 或 VK_DYNAMIC_STATE_ALPHA_TO_COVERAGE_ENABLE_EXT dynamic states 任意一个没有设置, 或者 alphaToOne 在 device  上启用而 VK_DYNAMIC_STATE_ALPHA_TO_ONE_ENABLE_EXT 没有设置, 则 pMultisampleState 必须是一个有效的 VkPipelineMultisampleStateCreateInfo 
	141.如果 VkGraphicsPipelineLibraryCreateInfoEXT::flags 包含 VK_GRAPHICS_PIPELINE_LIBRARY_FRAGMENT_SHADER_BIT_EXT 且pMultisampleState不为 NULL, 且 VkPipelineLibraryCreateInfoKHR::pLibraries的一个元素以  VK_GRAPHICS_PIPELINE_LIBRARY_FRAGMENT_OUTPUT_INTERFACE_BIT_EXT创建, 则pMultisampleState 必须是和创建library的相同定义的
	142.如果  VkPipelineLibraryCreateInfoKHR::pLibraries 的一个元素以 VK_GRAPHICS_PIPELINE_LIBRARY_FRAGMENT_SHADER_BIT_EXT 创建且 pMultisampleState 不为 NULL, 则:（1）如果 VkGraphicsPipelineLibraryCreateInfoEXT::flags 包含 VK_GRAPHICS_PIPELINE_LIBRARY_FRAGMENT_OUTPUT_INTERFACE_BIT_EXT,  则pMultisampleState 必须是和创建library的相同定义的
																																								  （2）如果 VkPipelineLibraryCreateInfoKHR::pLibraries不同的一个元素以  VK_GRAPHICS_PIPELINE_LIBRARY_FRAGMENT_OUTPUT_INTERFACE_BIT_EXT创建, 则创建每个library的 pMultisampleState 必须是相同定义的
	143.如果VkPipelineLibraryCreateInfoKHR::pLibraries 的一个元素以VK_GRAPHICS_PIPELINE_LIBRARY_FRAGMENT_OUTPUT_INTERFACE_BIT_EXT 创建 且pMultisampleState->sampleShadingEnable的一个值为 VK_TRUE, 则（1）如果VkPipelineLibraryCreateInfoKHR::pLibraries的一个不同元素以VK_GRAPHICS_PIPELINE_LIBRARY_FRAGMENT_SHADER_BIT_EXT创建, 则 则创建每个library的 pMultisampleState 必须是相同定义的
																																																	 （2）如果VkGraphicsPipelineLibraryCreateInfoEXT::flags 包含 VK_GRAPHICS_PIPELINE_LIBRARY_FRAGMENT_SHADER_BIT_EXT, pMultisampleState 必须和创建library的是相同定义的
	144.如果VkGraphicsPipelineLibraryCreateInfoEXT::flags 包含VK_GRAPHICS_PIPELINE_LIBRARY_FRAGMENT_OUTPUT_INTERFACE_BIT_EXT, pMultisampleState->sampleShadingEnable 为 VK_TRUE, and an element of VkPipelineLibraryCreateInfoKHR ::pLibraries的一个元素以 VK_GRAPHICS_PIPELINE_LIBRARY_FRAGMENT_SHADER_BIT_EXT创建,pMultisampleState 必须和创建library的是相同定义的
	
	145.如果 VkGraphicsPipelineLibraryCreateInfoEXT::flags 只包含VK_GRAPHICS_PIPELINE_LIBRARY_PRE_RASTERIZATION_SHADERS_BIT_EXT 或者VK_GRAPHICS_PIPELINE_LIBRARY_FRAGMENT_SHADER_BIT_EXT其中一个, VkPipelineLibraryCreateInfoKHR::pLibraries 的一个元素包含另外一个 ,则在pipeline以及library的VkPipelineFragmentShadingRateStateCreateInfoKHR中指定的值必须是相同的 
	
	146.如果VkPipelineLibraryCreateInfoKHR::pLibraries的一个元素包含VK_GRAPHICS_PIPELINE_LIBRARY_PRE_RASTERIZATION_SHADERS_BIT_EXT 且另外一个元素包含VK_GRAPHICS_PIPELINE_LIBRARY_FRAGMENT_SHADER_BIT_EXT，则在pipeline以及library的VkPipelineFragmentShadingRateStateCreateInfoKHR中指定的值必须是相同的 
	
	147.如果VkGraphicsPipelineLibraryCreateInfoEXT::flags包含VK_GRAPHICS_PIPELINE_LIBRARY_PRE_RASTERIZATION_SHADERS_BIT_EXT或者VK_GRAPHICS_PIPELINE_LIBRARY_FRAGMENT_SHADER_BIT_EXT，则（1）pStages必须是stageCount个有效的VkPipelineShaderStageCreateInfo数组首地址
																																													   （2）layout必须是有效的VkPipelineLayout句柄
																																													   （3）如果VkGraphicsPipelineLibraryCreateInfoEXT::flags或者还包含VK_GRAPHICS_PIPELINE_LIBRARY_FRAGMENT_OUTPUT_INTERFACE_BIT_EXT，则renderPass不为VK_NULL_HANDLE就必须为一个有效的VkRenderPass句柄
																																													   （4）stageCount必须大于0
	150.如果 VkGraphicsPipelineLibraryCreateInfoEXT::flags	不为0，如果flags包含 VK_PIPELINE_CREATE_CAPTURE_INTERNAL_REPRESENTATIONS_BIT_KHR	，任何libraries都必须也以VK_PIPELINE_CREATE_CAPTURE_INTERNAL_REPRESENTATIONS_BIT_KHR创建
	151.如果 VkPipelineLibraryCreateInfoKHR::pLibraries包含不止一个library，则（1）任何一个是以VK_PIPELINE_CREATE_CAPTURE_INTERNAL_REPRESENTATIONS_BIT_KHR创建的，则所有的libraries都需要也以VK_PIPELINE_CREATE_CAPTURE_INTERNAL_REPRESENTATIONS_BIT_KHR创建
																			  （2）如果VkGraphicsPipelineLibraryCreateInfoEXT::flags 为非零值, 则任何一个librariy以VK_PIPELINE_CREATE_CAPTURE_INTERNAL_REPRESENTATIONS_BIT_KHR创建,则flags必须包含 VK_PIPELINE_CREATE_CAPTURE_INTERNAL_REPRESENTATIONS_BIT_KHR
	152.如果 pipeline 包含完整的stage集，且VkPipelineLibraryCreateInfoKHR::pLibraries中不包含别的libraries,则 VkPipelineLayout必须是一个有效的pipeline layout
	153.如果 pipeline 包含的完整的stage集是通过libraries指定的，每一个library不以VK_PIPELINE_LAYOUT_CREATE_INDEPENDENT_SETS_BIT_EXT的layout创建，则 layout 必须和这些libraries的layout 兼容
	
	154.如果flags包含 VK_PIPELINE_CREATE_LINK_TIME_OPTIMIZATION_BIT_EXT,  pipeline 包含的完整的stage集是通过libraries指定的，每一个library以VK_PIPELINE_LAYOUT_CREATE_INDEPENDENT_SETS_BIT_EXT的layout创建，则 layout 必须和这些libraries的layout的并集 兼容而不是和包含或者不包含VK_PIPELINE_LAYOUT_CREATE_INDEPENDENT_SETS_BIT_EXT的libraries的layout的并集兼容
	
	155.如果 flags 不包含 VK_PIPELINE_CREATE_LINK_TIME_OPTIMIZATION_BIT_EXT, pipeline 包含的完整的stage集是通过libraries指定的，每一个library以VK_PIPELINE_LAYOUT_CREATE_INDEPENDENT_SETS_BIT_EXT的layout创建，则 layout 必须和这些libraries的layout的并集 兼容
	
	156.如果 conservativePointAndLineRasterization 不支持;  pipeline 以 vertex input state 以及 pre-rasterization shader state创建;  pipeline不包含geometry shader; 且 VkPipelineInputAssemblyStateCreateInfo::topology 为 VK_PRIMITIVE_TOPOLOGY_POINT_LIST, VK_PRIMITIVE_TOPOLOGY_LINE_LIST, 或者 VK_PRIMITIVE_TOPOLOGY_LINE_STRIP, 且 两者其一 VK_DYNAMIC_STATE_PRIMITIVE_TOPOLOGY dynamic state 没有设置或者  dynamicPrimitiveTopologyUnrestricted 为 VK_FALSE , 则 VkPipelineRasterizationConservativeStateCreateInfoEXT::conservativeRasterizationMode  必须为 VK_CONSERVATIVE_RASTERIZATION_MODE_DISABLED_EXT



	157.如果 conservativePointAndLineRasterization 不支持,  pipeline 需要 pre-rasterization shader state,则（1） 如果 pipeline 需要一个OutputPoints 或者 OutputLineStrip execution modes 其中之一的 geometry shader 则VkPipelineRasterizationConservativeStateCreateInfoEXT::conservativeRasterizationMode必须为 VK_CONSERVATIVE_RASTERIZATION_MODE_DISABLED_EXT
																										   （2）如果 pipeline 需要一个OutputPoints 或者 OutputLinesNV execution modes 其中之一的 mesh shader 则VkPipelineRasterizationConservativeStateCreateInfoEXT::conservativeRasterizationMode必须为 VK_CONSERVATIVE_RASTERIZATION_MODE_DISABLED_EXT
	158.如果 pipeline 需要 pre-rasterization shader state 但不需要 fragment shader state, 则pStages的元素不能含有stage设置为 VK_SHADER_STAGE_FRAGMENT_BIT
	159.如果 pipeline 需要 fragment shader state 但不需要 pre-rasterization shader state，则pStages的元素不能含有stage包含在 pre-rasterization状态范围中
	
	160.如果 pipeline 需要 pre-rasterization shader state, 则pStages的所有元素的必须有一个stage设置为fragment shader state或者pre-rasterization shader state中的shader stage
	
	161.如果 pipeline 需要 fragment shader state 以及/或者 pre-rasterization shader state，任何一个stage值不能在pStages中设置多次
	162.如果 extendedDynamicState3TessellationDomainOrigin 特性没有开启，pDynamicState的pDynamicStates就不能有元素为VK_DYNAMIC_STATE_TESSELLATION_DOMAIN_ORIGIN_EXT
	
	163.如果 extendedDynamicState3DepthClampEnable 特性没有开启，pDynamicState的pDynamicStates就不能有元素为VK_DYNAMIC_STATE_DEPTH_CLAMP_ENABLE_EXT
	
	164.如果 extendedDynamicState3PolygonMode 特性没有开启，pDynamicState的pDynamicStates就不能有元素为VK_DYNAMIC_STATE_POLYGON_MODE_EXT
	
	165.如果 extendedDynamicState3RasterizationSamples 特性没有开启，pDynamicState的pDynamicStates就不能有元素为VK_DYNAMIC_STATE_RASTERIZATION_SAMPLES_EXT
	
	166.如果 extendedDynamicState3SampleMask 特性没有开启，pDynamicState的pDynamicStates就不能有元素为VK_DYNAMIC_STATE_SAMPLE_MASK_EXT
	
	167.如果 extendedDynamicState3AlphaToCoverageEnable 特性没有开启，pDynamicState的pDynamicStates就不能有元素为VK_DYNAMIC_STATE_ALPHA_TO_COVERAGE_ENABLE_EXT
	
	168.如果 extendedDynamicState3AlphaToOneEnable 特性没有开启，pDynamicState的pDynamicStates就不能有元素为VK_DYNAMIC_STATE_ALPHA_TO_ONE_ENABLE_EXT
	
	169.如果 extendedDynamicState3LogicOpEnable 特性没有开启，pDynamicState的pDynamicStates就不能有元素为VK_DYNAMIC_STATE_LOGIC_OP_ENABLE_EXT
	
	
	170.如果 extendedDynamicState3ColorBlendEnable 特性没有开启，pDynamicState的pDynamicStates就不能有元素为VK_DYNAMIC_STATE_COLOR_BLEND_ENABLE_EXT
	
	171.如果 extendedDynamicState3ColorBlendEquation 特性没有开启，pDynamicState的pDynamicStates就不能有元素为VK_DYNAMIC_STATE_COLOR_BLEND_EQUATION_EXT
	
	172.如果 extendedDynamicState3ColorWriteMask 特性没有开启，pDynamicState的pDynamicStates就不能有元素为VK_DYNAMIC_STATE_COLOR_WRITE_MASK_EXT
	
	173.如果 extendedDynamicState3RasterizationStream 特性没有开启，pDynamicState的pDynamicStates就不能有元素为VK_DYNAMIC_STATE_RASTERIZATION_STREAM_EXT
	
	174.如果 extendedDynamicState3ConservativeRasterizationMode 特性没有开启，pDynamicState的pDynamicStates就不能有元素为VK_DYNAMIC_STATE_CONSERVATIVE_RASTERIZATION_MODE_EXT
	
	175.如果 extendedDynamicState3ExtraPrimitiveOverestimationSize 特性没有开启，pDynamicState的pDynamicStates就不能有元素为VK_DYNAMIC_STATE_EXTRA_PRIMITIVE_OVERESTIMATION_SIZE_EXT
	
	176.如果pipeline需要pre-rasterization shader state，pDynamicState包含VK_DYNAMIC_STATE_CONSERVATIVE_RASTERIZATION_MODE_EXT但不包含VK_DYNAMIC_STATE_EXTRA_PRIMITIVE_OVERESTIMATION_SIZE_EXT，则pRasterizationState的pNext中必须包含一个VkPipelineRasterizationConservativeStateCreateInfoEXT

	177.如果 extendedDynamicState3DepthClipEnable 特性没有开启，pDynamicState的pDynamicStates就不能有元素为VK_DYNAMIC_STATE_DEPTH_CLIP_ENABLE_EXT
	
	178.如果 extendedDynamicState3SampleLocationsEnable 特性没有开启，pDynamicState的pDynamicStates就不能有元素为VK_DYNAMIC_STATE_SAMPLE_LOCATIONS_ENABLE_EXT
	
	179.如果 extendedDynamicState3ColorBlendAdvanced 特性没有开启，pDynamicState的pDynamicStates就不能有元素为VK_DYNAMIC_STATE_COLOR_BLEND_ADVANCED_EXT
	
	180.如果 extendedDynamicState3ProvokingVertexMode 特性没有开启，pDynamicState的pDynamicStates就不能有元素为VK_DYNAMIC_STATE_PROVOKING_VERTEX_MODE_EXT
	
	181.如果 extendedDynamicState3LineRasterizationMode 特性没有开启，pDynamicState的pDynamicStates就不能有元素为VK_DYNAMIC_STATE_LINE_RASTERIZATION_MODE_EXT
	
	182.如果 extendedDynamicState3LineStippleEnable 特性没有开启，pDynamicState的pDynamicStates就不能有元素为VK_DYNAMIC_STATE_LINE_STIPPLE_ENABLE_EXT
	
	183.如果 extendedDynamicState3DepthClipNegativeOneToOne 特性没有开启，pDynamicState的pDynamicStates就不能有元素为VK_DYNAMIC_STATE_DEPTH_CLIP_NEGATIVE_ONE_TO_ONE_EXT
	
	184.如果 extendedDynamicState3ViewportWScalingEnable 特性没有开启，pDynamicState的pDynamicStates就不能有元素为VK_DYNAMIC_STATE_VIEWPORT_W_SCALING_ENABLE_NV
	
	185.如果 extendedDynamicState3ViewportSwizzle 特性没有开启，pDynamicState的pDynamicStates就不能有元素为VK_DYNAMIC_STATE_VIEWPORT_SWIZZLE_NV
	
	186.如果 extendedDynamicState3CoverageToColorEnable 特性没有开启，pDynamicState的pDynamicStates就不能有元素为VK_DYNAMIC_STATE_COVERAGE_TO_COLOR_ENABLE_NV

	187.如果 extendedDynamicState3CoverageToColorLocation 特性没有开启，pDynamicState的pDynamicStates就不能有元素为VK_DYNAMIC_STATE_COVERAGE_TO_COLOR_LOCATION_NV
	
	188.如果 extendedDynamicState3CoverageModulationMode 特性没有开启，pDynamicState的pDynamicStates就不能有元素为VK_DYNAMIC_STATE_COVERAGE_MODULATION_MODE_NV
	
	189.如果 extendedDynamicState3CoverageModulationTableEnable 特性没有开启，pDynamicState的pDynamicStates就不能有元素为VK_DYNAMIC_STATE_COVERAGE_MODULATION_TABLE_ENABLE_NV
	
	190.如果 extendedDynamicState3CoverageModulationTable 特性没有开启，pDynamicState的pDynamicStates就不能有元素为VK_DYNAMIC_STATE_COVERAGE_MODULATION_TABLE_NV
	
	191.如果 extendedDynamicState3CoverageReductionMode 特性没有开启，pDynamicState的pDynamicStates就不能有元素为VK_DYNAMIC_STATE_COVERAGE_REDUCTION_MODE_NV
	
	192.如果 extendedDynamicState3RepresentativeFragmentTestEnable 特性没有开启，pDynamicState的pDynamicStates就不能有元素为VK_DYNAMIC_STATE_REPRESENTATIVE_FRAGMENT_TEST_ENABLE_NV
	
	193.如果 extendedDynamicState3ShadingRateImageEnable 特性没有开启，pDynamicState的pDynamicStates就不能有元素为VK_DYNAMIC_STATE_SHADING_RATE_IMAGE_ENABLE_NV
	
	194.flags 不能包含 VK_PIPELINE_CREATE_RAY_TRACING_OPACITY_MICROMAP_BIT_EXT，VK_PIPELINE_CREATE_RAY_TRACING_DISPLACEMENT_MICROMAP_BIT_NV
	
	195.如果pipeline需要pre-rasterization shader state，且pDynamicState的pDynamicStates不含VK_DYNAMIC_STATE_VIEWPORT或者VK_DYNAMIC_STATE_VIEWPORT_WITH_COUNT，如果multiviewPerViewViewports开启，则VkRenderPassMultiviewCreateInfo::pViewMasks的有效位的索引必须小于pViewportState->viewportCount

	195.如果pipeline需要pre-rasterization shader state，且pDynamicState的pDynamicStates不含VK_DYNAMIC_STATE_SCISSOR或者VK_DYNAMIC_STATE_SCISSOR_WITH_COUNT，如果multiviewPerViewViewports开启，则VkRenderPassMultiviewCreateInfo::pViewMasks的有效位的索引必须小于pViewportState->scissorCount
	
	196.如果pStages包含一个fragment shader stage，VkPipelineDynamicStateCreateInfo::pDynamicStates中没有VK_DYNAMIC_STATE_DEPTH_WRITE_ENABLE，且fragment shader声明EarlyFragmentTests execution mode且使用OpDepthAttachmentReadEXT，则VkPipelineDepthStencilStateCreateInfo的depthWriteEnable必须VK_FALSE
	197.如果pStages包含一个fragment shader stage，VkPipelineDynamicStateCreateInfo::pDynamicStates中没有VK_DYNAMIC_STATE_STENCIL_WRITE_MASK，且fragment shader声明EarlyFragmentTests execution mode且 如果使用OpStencilAttachmentReadEXT，则VkPipelineDepthStencilStateCreateInfo的前后的VkStencilOpState::writeMask必须为0
	
	198.如果renderPass为VK_NULL_HANDLE，pipeline需要fragment output state或者fragment shader state， pipeline启用sample shading，rasterizationSamples不是动态的，pNext中包含一个VkPipelineRenderingCreateInfo， rasterizationSamples必须是一个对于每一个depthAttachmentFormat，stencilAttachmentFormat以及pColorAttachmentFormats中不为VK_NULL_HANDLE元素的的设置在imageCreateSampleCounts（或者在Image Creation Limits中定义的）有效的VkSampleCountFlagBits值
	
	199.如果VkGraphicsPipelineLibraryCreateInfoEXT::flags包含VK_GRAPHICS_PIPELINE_LIBRARY_VERTEX_INPUT_INTERFACE_BIT_EXT，pre-rasterization shader state指定在一个library或者通过包含VK_GRAPHICS_PIPELINE_LIBRARY_PRE_RASTERIZATION_SHADERS_BIT_EXT，且其pStages中包含一个 vertex shader stage ，则pipeline 必须定义一个vertex input state （VUID-VkGraphicsPipelineCreateInfo-flags-08897）
	
	200.如果VkGraphicsPipelineLibraryCreateInfoEXT::flagsVK_GRAPHICS_PIPELINE_LIBRARY_VERTEX_INPUT_INTERFACE_BIT_EXT，且没有指定pre-rasterization shader state，则pipeline 必须定义一个vertex input state
	
	201.如果flags不包含VK_PIPELINE_CREATE_LIBRARY_BIT_KHR，pre-rasterization shader state指定在一个library或者通过包含VK_GRAPHICS_PIPELINE_LIBRARY_PRE_RASTERIZATION_SHADERS_BIT_EXT，且其pStages中包含一个 vertex shader stage ，则pipeline 必须定义一个vertex input state 或者在linked pipeline library中包含该stage

	202.如果VkGraphicsPipelineLibraryCreateInfoEXT::flags包含VK_GRAPHICS_PIPELINE_LIBRARY_PRE_RASTERIZATION_SHADERS_BIT_EXT，则pipeline必须定义pre-rasterization shader state
	
	203.如果flags不包含VK_PIPELINE_CREATE_LIBRARY_BIT_KHR，则pipeline必须定义pre-rasterization shader state或者是在linked pipeline library中包含该state
	
	204.如果VkGraphicsPipelineLibraryCreateInfoEXT::flags 包含 VK_GRAPHICS_PIPELINE_LIBRARY_FRAGMENT_SHADER_BIT_EXT，pre-rasterization shader state是在一个library中指定或者是通过包含VK_GRAPHICS_PIPELINE_LIBRARY_FRAGMENT_SHADER_BIT_EXT指定，且这个stage包含VK_DYNAMIC_STATE_RASTERIZER_DISCARD_ENABLE或者其pRasterizationState->rasterizerDiscardEnable 设置为VK_FALSE，则pipeline必须定义fragment shader state
	
	205.如果VkGraphicsPipelineLibraryCreateInfoEXT::flags 包含 VK_GRAPHICS_PIPELINE_LIBRARY_FRAGMENT_SHADER_BIT_EXT，pre-rasterization shader state没有指定，则（1）pipeline必须定义fragment shader state
																																							   （2）pipeline必须定义 fragment output interface state
	206.如果VkGraphicsPipelineLibraryCreateInfoEXT::flags 包含 VK_GRAPHICS_PIPELINE_LIBRARY_FRAGMENT_SHADER_BIT_EXT，pre-rasterization shader state是在一个library中指定或者是通过包含VK_GRAPHICS_PIPELINE_LIBRARY_FRAGMENT_OUTPUT_INTERFACE_BIT_EXT指定，且这个stage包含VK_DYNAMIC_STATE_RASTERIZER_DISCARD_ENABLE或者其pRasterizationState->rasterizerDiscardEnable 设置为VK_FALSE，则pipeline必须定义fragment output interface state
	
	207.如果flags不包含VK_PIPELINE_CREATE_LIBRARY_BIT_KHR，pre-rasterization shader state指定在一个library或者通过包含VK_GRAPHICS_PIPELINE_LIBRARY_PRE_RASTERIZATION_SHADERS_BIT_EXT指定，且其state包含VK_DYNAMIC_STATE_RASTERIZER_DISCARD_ENABLE 或者其pRasterizationState->rasterizerDiscardEnable 为 VK_FALSE，则pipeline必须定义fragment output interface state 以及 fragment shader state 或者是在linked pipeline libraries中包含
	208.如果pDynamicState->pDynamicStates不包含VK_DYNAMIC_STATE_COLOR_WRITE_MASK_EXT，且color attachment的 format为VK_FORMAT_E5B9G9R9_UFLOAT_PACK32，则对应pColorBlendState->pAttachments元素的colorWriteMask必须是包含所有的VK_COLOR_COMPONENT_R_BIT, VK_COLOR_COMPONENT_G_BIT, 以及 VK_COLOR_COMPONENT_B_BIT或者是所有都不包含

	209.如果externalFormatResolve开启，pipeline需要fragment output interface state，且renderPass为VK_NULL_HANDLE,且VkExternalFormatANDROID::externalFormat不为0，则:（1）VkPipelineRenderingCreateInfo::viewMask 必须为 0
																																									（2）如果rasterizationSamples不是动态的，则VkPipelineMultisampleStateCreateInfo::rasterizationSamples必须为 1
																																									（3）如果blendEnable不是动态的，则pColorBlendState->pAttachments每个元素的blendEnable必须为VK_FALSE
																																									（4）如果pDynamicState->pDynamicStates 不包含VK_DYNAMIC_STATE_FRAGMENT_SHADING_RATE_KHR，则VkPipelineFragmentShadingRateStateCreateInfoKHR::width 必须为 1，VkPipelineFragmentShadingRateStateCreateInfoKHR::height必须为 1
																																									（5）则VkPipelineRenderingCreateInfo::colorAttachmentCount 必须为 1
	
	210.如果externalFormatResolve开启，pipeline需要pre-rasterization shader state 以及 fragment output interface state，renderPass 为 VK_NULL_HANDLE,且VkExternalFormatANDROID::externalFormat不为0,则 最后一个 pre-rasterization shader stage不能静态的使用以PrimitiveShadingRateKHR built-in修饰的变量
	
	211.如果externalFormatResolve开启，pipeline需要fragment shader state 以及 fragment output interface state，renderPass 为 VK_NULL_HANDLE,且VkExternalFormatANDROID::externalFormat不为0,则 fragment shader不能声明为DepthReplacing 或者 StencilRefReplacingEXT execution modes
	
	
	212.如果externalFormatResolve开启，pipeline需要fragment shader state 以及 fragment output interface state，renderPass 不为 VK_NULL_HANDLE, subpass 包含外部format的resolve attachment，则（1）如果rasterizationSamples不是动态的，则VkPipelineMultisampleStateCreateInfo::rasterizationSamples就必须为VK_SAMPLE_COUNT_1_BIT
																																															 （2）如果blendEnable不是动态的，每个pColorBlendState->pAttachments的 blendEnable 必须为 VK_FALSE
																																															 （3）如果pDynamicState->pDynamicStates不包含VK_DYNAMIC_STATE_FRAGMENT_SHADING_RATE_KHR，则VkPipelineFragmentShadingRateStateCreateInfoKHR::width必须为 1，VkPipelineFragmentShadingRateStateCreateInfoKHR::height必须为 1
	
	213.如果 externalFormatResolve 开启，pipeline 需要pre-rasterization shader state 以及 fragment output interface state，renderPass 不为 VK_NULL_HANDLE，subpass 包含外部format的resolve attachment，则最后一个 pre-rasterization shader stage 不能静态的使用以PrimitiveShadingRateKHR built-in修饰的变量
	
	214.如果 pipeline 以fragment shader state 和 fragment output state创建，且renderPass 为 VK_NULL_HANDLE，则（1）如果包含了VkRenderingInputAttachmentIndexInfoKHR，则VkRenderingInputAttachmentIndexInfoKHR::colorAttachmentCount 必须等于 VkPipelineRenderingCreateInfo::colorAttachmentCount
																											  （2）如果不包含VkRenderingInputAttachmentIndexInfoKHR，则fragment shader不能包含任何InputAttachmentIndex大于或等于VkPipelineRenderingCreateInfo::colorAttachmentCount的 input attachments
	215.如果pipeline 以 fragment output state创建，且renderPass为VK_NULL_HANDLE，则 VkRenderingAttachmentLocationInfoKHR::colorAttachmentCount 必须等于 VkPipelineRenderingCreateInfo::colorAttachmentCount
	



	*/



	/*
	VkPipelineRenderingCreateInfo这个包含在VkGraphicsPipelineCreateInfo的pNext中，如果pipeline创建没有renderPass,则 该结构体用于描述渲染相关的状态，如viewMask、colorAttachmentCount、pColorAttachmentFormats、depthAttachmentFormat、stencilAttachmentFormat等。如果pipeline创建有renderPass，则该结构体会被忽略
	如果format为VK_FORMAT_UNDEFINED则指明该附件在渲染中没有被使用
	*/
	VkPipelineRenderingCreateInfo& renderingCreateInfo = pipelineCreateInfoExt.pipelineRenderingCreateInfo;
	renderingCreateInfo.viewMask = 0;
	renderingCreateInfo.colorAttachmentCount = 0;
	renderingCreateInfo.pColorAttachmentFormats = VK_NULL_HANDLE;//指明pipeline中color attachment的格式
	renderingCreateInfo.depthAttachmentFormat = VK_FORMAT_UNDEFINED;//指明pipeline中depth attachment的格式
	renderingCreateInfo.stencilAttachmentFormat = VK_FORMAT_UNDEFINED;//指明pipeline中stencil attachment的格式


	/*VkPipelineCreateFlags2CreateInfoKHR*/
	VkPipelineCreateFlags2CreateInfoKHR& flags2CreateInfo = pipelineCreateInfoExt.pipelineCreateFlags2CreateInfoKHR;
	flags2CreateInfo.flags = 0;/*指明管线如何被创建
    VK_PIPELINE_CREATE_2_DISABLE_OPTIMIZATION_BIT_KHR :   指明管线创建不会优化，这会加快管道创建
    VK_PIPELINE_CREATE_2_ALLOW_DERIVATIVES_BIT_KHR :   指定要创建的管道允许是将在后续的管道创建调用中创建的管道的父管道
    VK_PIPELINE_CREATE_2_DERIVATIVE_BIT_KHR :    指定要创建的管道将是以前创建的父管道的子管道
    VK_PIPELINE_CREATE_2_VIEW_INDEX_FROM_DEVICE_INDEX_BIT_KHR :  指定任何以 ViewIndex修饰的着色器输入变量将被分配值，就像它们被修饰为DeviceIndex.一样。
    VK_PIPELINE_CREATE_2_DISPATCH_BASE_BIT_KHR :    指定计算管道可以与非零基工作组的vkCmdDispatchBase一起使用
    VK_PIPELINE_CREATE_2_DEFER_COMPILE_BIT_NV :   指定创建所有着色器处于延迟状态的的管道。在使用管道之前，应用程序必须在使用管道之前对管道中的每个着色器只调用vkCompileDeferredNV一次。 
    VK_PIPELINE_CREATE_2_CAPTURE_STATISTICS_BIT_KHR :    指定着色器编译器应该捕获由编译过程产生的管道可执行文件的统计信息，稍后可以通过调用vkGetPipelineExecutableStatisticsKHR.来检索这些信息，启用此标志不能影响最终编译的管道，但可能会禁用管道缓存或以其他方式影响管道创建时间。
    VK_PIPELINE_CREATE_2_CAPTURE_INTERNAL_REPRESENTATIONS_BIT_KHR :   指定着色器编译器应该捕获由编译过程产生的管道可执行文件的内部表示，稍后可以通过调用 vkGetPipelineExecutableInternalRepresentationsKHR.来检索启用此标志不能影响最终编译的管道，但可能会禁用管道缓存或以其他方式影响管道创建时间。当从使用管道库创建的管道中捕获IR时，并不能保证可以从链接的管道中检索到库中的IR。应用程序应该分别从每个库和任何链接的管道中检索IR
    VK_PIPELINE_CREATE_2_LIBRARY_BIT_KHR :    指定不能直接使用管道，而是定义了一个可以使用VkPipelineLibraryCreateInfoKHR结构与其他管道组合的 pipeline library 。这可以在光线追踪和图形管道中使用。
    VK_PIPELINE_CREATE_2_RAY_TRACING_NO_NULL_ANY_HIT_SHADERS_BIT_KHR :   指定在执行any-hit着色器时，将始终存在any-hit着色器。一个NULL any-hit的着色器是一个有效的是VK_SHADER_UNUSED_KHR的 any-hit 的着色器，例如来自一个完全由零组成的着色器组。 
    VK_PIPELINE_CREATE_2_RAY_TRACING_NO_NULL_CLOSEST_HIT_SHADERS_BIT_KHR : 指定在执行closest hit着色器时，将始终存在closest hit着色器。一个NULL closest hit 着色器是一个有效的VK_SHADER_UNUSED_KHR的closest hit 着色器，例如从一个完全由零组成的着色器组 
    VK_PIPELINE_CREATE_2_RAY_TRACING_NO_NULL_MISS_SHADERS_BIT_KHR :  指定在执行miss shader 时，将始终存在miss shader。一个NULL miss shader是一个有效的VK_SHADER_UNUSED_KHR miss shader，例如从一个完全由零组成的着色器组。
    VK_PIPELINE_CREATE_2_RAY_TRACING_NO_NULL_INTERSECTION_SHADERS_BIT_KHR :  指定在执行intersection shader 时，将始终存在intersection shader。一个NULL intersection shader是一个有效的VK_SHADER_UNUSED_KHR intersection shader，例如从一个完全由零组成的着色器组。  
    VK_PIPELINE_CREATE_2_RAY_TRACING_SKIP_TRIANGLES_BIT_KHR :    指定在使用管道跟踪射线指令遍历期间将跳过三角形图元。
    VK_PIPELINE_CREATE_2_RAY_TRACING_SKIP_AABBS_BIT_KHR :    指定在使用管道跟踪射线指令遍历期间将跳过AABB primitives。
    VK_PIPELINE_CREATE_2_RAY_TRACING_SHADER_GROUP_HANDLE_CAPTURE_REPLAY_BIT_KHR :    指定着色器组句柄可以在后续的运行中被保存和重用（例如，用于跟踪捕获和重播）。
    VK_PIPELINE_CREATE_2_INDIRECT_BINDABLE_BIT_NV :  指定管道可以与Device-Generated的命令结合使用  
	VK_PIPELINE_CREATE_2_FAIL_ON_PIPELINE_COMPILE_REQUIRED_BIT_KHR :   指定如果需要编译来创建一个有效的VkPipeline，则管道创建将失败；管道创建将返回VK_PIPELINE_COMPILE_REQUIRED，并且VkPipeline将被设置为VK_NULL_HANDLE。 
    VK_PIPELINE_CREATE_2_EARLY_RETURN_ON_FAILURE_BIT_KHR:   指定如果任何单个管道返回一个不是VK_SUCCESS的结果，则不再继续创建额外的管道，而是将控制权返回给应用程序。
	VK_PIPELINE_CREATE_2_RAY_TRACING_ALLOW_MOTION_BIT_NV :   指定管道可以使用 OpTraceRayMotionNV.
    VK_PIPELINE_CREATE_2_RENDERING_FRAGMENT_SHADING_RATE_ATTACHMENT_BIT_KHR :   指定管道将与一个 fragment shading rate attachment 一起使用。
    VK_PIPELINE_CREATE_2_RENDERING_FRAGMENT_DENSITY_MAP_ATTACHMENT_BIT_EXT :     指定管道将与一个 fragment density map attachment 一起使用
    VK_PIPELINE_CREATE_2_LINK_TIME_OPTIMIZATION_BIT_EXT :    指定要链接到此库中的管道库应该已应用了链接时间优化。如果省略了这个位，那么实现应该尽可能快地执行链接。
    VK_PIPELINE_CREATE_2_RETAIN_LINK_TIME_OPTIMIZATION_INFO_BIT_EXT :    指定管道库应该保留以后与VK_PIPELINE_CREATE_2_LINK_TIME_OPTIMIZATION_BIT_EXT.执行最佳链接所需的任何信息
	VK_PIPELINE_CREATE_2_DESCRIPTOR_BUFFER_BIT_EXT :   指定管道将与descriptor buffers一起使用，而不是使用descriptor sets。
	VK_PIPELINE_CREATE_2_COLOR_ATTACHMENT_FEEDBACK_LOOP_BIT_EXT :  指定管道可以与feedback loop color attachment一起使用。 
    VK_PIPELINE_CREATE_2_DEPTH_STENCIL_ATTACHMENT_FEEDBACK_LOOP_BIT_EXT :    指定管道可以与feedback loop depth-stencil attachment一起使用。
    VK_PIPELINE_CREATE_2_RAY_TRACING_OPACITY_MICROMAP_BIT_EXT :    指定光线跟踪管道可与引用不透明度微映射阵列的加速结构一起使用。
    VK_PIPELINE_CREATE_2_RAY_TRACING_DISPLACEMENT_MICROMAP_BIT_NV :    指定光线追踪管道可以与参考位移微映射阵列的加速结构一起使用
    VK_PIPELINE_CREATE_2_NO_PROTECTED_ACCESS_BIT_EXT :    指定管道不能绑定到受保护的命令缓冲区。
    VK_PIPELINE_CREATE_2_PROTECTED_ACCESS_ONLY_BIT_EXT :    指定管道不能绑定到未受保护的命令缓冲区
    VK_PIPELINE_CREATE_2_ENABLE_LEGACY_DITHERING_BIT_EXT :    指定将在以VK_RENDERING_ENABLE_LEGACY_DITHERING_BIT_EXT开始的render pass中使用该管道。
	
	*/


	/*
	如果一个VkGraphicsPipelineLibraryCreateInfoEXT结构包含在VkGraphicsPipelineCreateInfo的pNext链中，则它将指定正在被创建的图形管道的子集，排除开任何linked pipeline libraries中的子集。如果管道是用管道库创建的，那么从这些库中获得的state将与所述子集进行聚合。
	如果省略此结构，并且VkGraphicsPipelineCreateInfo：：flags包含VK_PIPELINE_CREATE_LIBRARY_BIT_KHR或VkGraphicsPipelineCreateInfo：：pNext链包含一个库计数大于0的VkPipelineLibraryCreateInfoKHR结构，则表示标志为0。否则，如果省略此结构，就好像标志包含了图形管道的所有可能的子集（即一个完整的图形管道）
	*/
	VkGraphicsPipelineLibraryCreateInfoEXT& pipelineLibraryCreateInfo = pipelineCreateInfoExt.pipelineLibraryCreateInfoEXT;
	pipelineLibraryCreateInfo.flags = VK_GRAPHICS_PIPELINE_LIBRARY_VERTEX_INPUT_INTERFACE_BIT_EXT;/*指定正在被编译的图形管道的子集。
	VK_GRAPHICS_PIPELINE_LIBRARY_VERTEX_INPUT_INTERFACE_BIT_EXT:  指明一个 pipeline 将包含 vertex input interface state. 
	VK_GRAPHICS_PIPELINE_LIBRARY_PRE_RASTERIZATION_SHADERS_BIT_EXT:  指明一个 pipeline 将包含  pre-rasterization shader state.
	VK_GRAPHICS_PIPELINE_LIBRARY_FRAGMENT_SHADER_BIT_EXT:  指明一个 pipeline 将包含  fragment shader state.
	VK_GRAPHICS_PIPELINE_LIBRARY_FRAGMENT_OUTPUT_INTERFACE_BIT_EXT:   指明一个 pipeline 将包含 fragment output interface state
	*/


	vkCreateGraphicsPipelines(device, VK_NULL_HANDLE, 1, &graphicPipelineCreateInfo, nullptr, &graphicPipeline);
	/*
	vkCreateGraphicsPipelines有效用法：
	1.如果pCreateInfos中的某个元素的flags包含VK_PIPELINE_CREATE_DERIVATIVE_BIT，则
													（1）如果其basePipelineIndex不为-1，则basePipelineIndex必须小于当前元素在pCreateInfos中的索引值
													（1）basePipelineHandle的创建flags必须含有 VK_PIPELINE_CREATE_ALLOW_DERIVATIVES_BIT
	2.如果pipelineCache 以 VK_PIPELINE_CACHE_CREATE_EXTERNALLY_SYNCHRONIZED_BIT标志创建,主机对 pipelineCache 必须要进行外部同步--如外部多线程同步等
	
	*/






}


























NS_TEST_END