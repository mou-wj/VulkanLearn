#include "ShadersTest.h"
NS_TEST_BEGIN


/*
章节内容线索：
shaders创建
二进制shaders代码
绑定shaders
设置shader状态
shaders销毁
shader模块
shader模块标识符
shader执行
shader访问顺序
shader输入和输出
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
插值装饰
scope
组操作
四边形组操作
衍生操作
协同矩阵
验证缓存
cuda 模块




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






	//二进制着色器代码
	//获取shader的二进制着色器代码，可以传递个shaderCreateInfo，获取后可以用来在兼容的不同逻辑设备或者物理设备上创建着色器，
	//兼容满足有机制：VkPhysicalDeviceShaderObjectPropertiesEXT中的shaderBinaryUUID（相同）和shaderBinaryVersion（版本兼容--高兼容低）兼容
	size_t bcodeSize = 0;
	VK_DEVICE_FUNCTION_GET_AND_CALL(device, vkGetShaderBinaryDataEXT, device, shaderExt, &bcodeSize, nullptr);
	std::vector<char> bcode;
	bcode.resize(bcodeSize);
	VK_DEVICE_FUNCTION_GET_AND_CALL(device, vkGetShaderBinaryDataEXT, device, shaderExt, &bcodeSize, bcode.data());







	VkShaderCreateInfoEXT shaderCreateInfo{};
	shaderCreateInfo.sType = VK_STRUCTURE_TYPE_SHADER_CREATE_INFO_EXT;
	shaderCreateInfo.pNext = nullptr;//可以含有VkPipelineShaderStageRequiredSubgroupSizeCreateInfo

	shaderCreateInfo.flags = VK_SHADER_CREATE_LINK_STAGE_BIT_EXT;
	/*
	
	VK_SHADER_CREATE_LINK_STAGE_BIT_EXT：指明用vkCreateShadersEXT创建的shader会被链接在一起
	VK_SHADER_CREATE_ALLOW_VARYING_SUBGROUP_SIZE_BIT_EXT：指明task, mesh, 或者 compute shader的 SubgroupSize可以不同
	VK_SHADER_CREATE_REQUIRE_FULL_SUBGROUPS_BIT_EXT：指明subgroup大小可以必须在激活task, mesh, 或者 compute shader时启用
	VK_SHADER_CREATE_NO_TASK_SHADER_BIT_EXT：指明mesh shader不能在没有task shader情况下使用
	VK_SHADER_CREATE_DISPATCH_BASE_BIT_EXT：指明compute shader可以在vkCmdDispatchBase中以非零基础工作组进行使用
	VK_SHADER_CREATE_FRAGMENT_SHADING_RATE_ATTACHMENT_BIT_EXT：指明fragment shader可以使用fragment shading rate attachment
	VK_SHADER_CREATE_FRAGMENT_DENSITY_MAP_ATTACHMENT_BIT_EXT：指明fragment shader可以使用fragment density map attachment.
	*/
	shaderCreateInfo.stage = VK_SHADER_STAGE_VERTEX_BIT;//指明单独的shader类型
	shaderCreateInfo.nextStage = VK_SHADER_STAGE_VERTEX_BIT;//设为0或者指明下一个该着色器绑定后绘制可能会使用的着色器状态
	shaderCreateInfo.codeType = VK_SHADER_CODE_TYPE_SPIRV_EXT;//指明shader代码类型
	/*
	VK_SHADER_CODE_TYPE_BINARY_EXT：指明shader代码为不透明的，特定于物理设备的实现定义的二进制格式
	VK_SHADER_CODE_TYPE_SPIRV_EX：指明shader代码为SPIR-V格式
	*/
	shaderCreateInfo.codeSize = 1;//指明代码长度
	shaderCreateInfo.pCode = VK_NULL_HANDLE;//指向shader代码的指针
	shaderCreateInfo.pName = "main";//指明当前着色器的入口函数名
	shaderCreateInfo.pushConstantRangeCount = 1;
		VkPushConstantRange constantRange{};
		constantRange.offset = 0;
		constantRange.size = 1;
		constantRange.stageFlags = VK_SHADER_STAGE_VERTEX_BIT;
	shaderCreateInfo.pPushConstantRanges = &constantRange;//pushConstantRangeCount个 VkPushConstantRange的数组首地址
	shaderCreateInfo.setLayoutCount = 0;
	shaderCreateInfo.pSetLayouts = VK_NULL_HANDLE;//指明该着色器使用的资源布局
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
	有效用法：
	1.如果 codeType 为 VK_SHADER_CODE_TYPE_SPIRV_EXT，则（1）codeSize必须为4的倍数
                                                        （2）pCode必须是合法的spirv代码
	                                                    （3）pCode必须附加到 SPIR-V Environment附录的 Validation Rules within a Module部分描述的验证规则中
														（4）pCode必须声明shader的spirv代码capability
														（6）pCode不能声明API不支持的capability， 在SPIR-V Environment附录中的 Capabilities中进行描述
														（7）pCode声明的列举在SPIR-V Environment附录的capability，必须满足其他对应的条件
														（8）pCode不能声明API不支持的扩展，在SPIR-V Environment附录中的  Extension 中进行描述
														（9）pName必须是pCode的 OpEntryPoint匹配stage的执行模型的名字
														（10）pCode必须对齐到4字节
														（11）如果其入口点的接口处存在以 ClipDistance BuiltIn声明的变量，则该变量数组的大小不能大于 VkPhysicalDeviceLimits::maxClipDistances
														（12）如果其入口点的接口处存在以 CullDistance BuiltIn声明的变量，则该变量数组的大小不能大于 VkPhysicalDeviceLimits::maxCullDistances
														（13）如果其入口点的接口处存在以 ClipDistance BuiltIn且以CullDistance BuiltIn声明的变量，则该变量数组的大小不能大于  VkPhysicalDeviceLimits::maxCombinedClipAndCullDistances
														（14）如果其入口点的接口处存在以 SampleMask BuiltIn声明的变量，则该变量数组的大小不能大于 VkPhysicalDeviceLimits::maxSampleMaskWords
														（15）如果stage为VK_SHADER_STAGE_VERTEX_BIT,，则其入口点的接口处就不能存在存在以 CullDistance声明的输入变量
														（16）如果stage为VK_SHADER_STAGE_TESSELLATION_CONTROL_BIT 或者 VK_SHADER_STAGE_TESSELLATION_EVALUATION_BIT,，则其入口点有OpExecutionMode指明了 OutputVertices,的patch size ，
																		则patch size就必须大于0且小于VkPhysicalDeviceLimits::maxTessellationPatchSize
														（17）如果stage为VK_SHADER_STAGE_GEOMETRY_BIT,，则其入口点必须含有OpExecutionMode指明了最大的顶点数目，该数目大于0且小于等于VkPhysicalDeviceLimits::maxGeometryOutputVertices 
														（18）如果stage为VK_SHADER_STAGE_GEOMETRY_BIT,，则其入口点必须含有OpExecutionMode指明了调用数目，该数目大于0且小于等于VkPhysicalDeviceLimits:::maxGeometryShaderInvocations 
														（19）如果stage为一个 pre-rasterization shader stage 且其入口点对片元的任何layer写，则其必须将相同的值写到片元的所有顶点的layer中
														（20）如果stage为一个 pre-rasterization shader stage 且其入口点对片元的任何ViewportIndex写，则其必须将相同的值写到片元的所有顶点的ViewportIndex中
														（21）如果stage为 VK_SHADER_STAGE_FRAGMENT_BIT，则其入口点不能含有任何以  CullDistance 声明的输出变量
														（22）如果stage为 VK_SHADER_STAGE_FRAGMENT_BIT，则其入口点不能在任何执行路径上写到 FragDepth ，所有不专属于helper调用的执行路径都必须丢弃片段，或者写入或初始化的 FragDepth值
														（23）pCode中的值必须是在应用了 pSpecializationInfo（如果有）后符合 Khronos SPIR-V Specification描述的合法的值，且会将所有专门化常数转换为固定常数
														（24）如果stage为VK_SHADER_STAGE_TESSELLATION_EVALUATION_BIT，pCode必须包含一个OpExecutionMode指明细分类型
														（25）如果stage为VK_SHADER_STAGE_TESSELLATION_EVALUATION_BIT，pCode必须包含一个OpExecutionMode指明细分控制器产生的orientation of triangles
														（26）如果stage为VK_SHADER_STAGE_TESSELLATION_EVALUATION_BIT，pCode必须包含一个OpExecutionMode指明细分图元的边上的spacing of segments
														（27）如果stage为VK_SHADER_STAGE_TESSELLATION_EVALUATION_BIT，pCode必须包含一个OpExecutionMode指明 output patch 大小
	2.如果stage不是VK_SHADER_STAGE_TASK_BIT_EXT, VK_SHADER_STAGE_MESH_BIT_EXT,
													VK_SHADER_STAGE_VERTEX_BIT, VK_SHADER_STAGE_TESSELLATION_CONTROL_BIT,
													VK_SHADER_STAGE_TESSELLATION_EVALUATION_BIT, VK_SHADER_STAGE_GEOMETRY_BIT, 或者
													VK_SHADER_STAGE_FRAGMENT_BIT，flags不能包含VK_SHADER_CREATE_LINK_STAGE_BIT_EXT
	3.如果stage不是VK_SHADER_STAGE_FRAGMENT_BIT,，flags不能包含VK_SHADER_CREATE_FRAGMENT_SHADING_RATE_ATTACHMENT_BIT_EXT，VK_SHADER_CREATE_FRAGMENT_DENSITY_MAP_ATTACHMENT_BIT_EXT，											
	4.如果 attachmentFragmentShadingRate特性没有开启，flags不能包含VK_SHADER_CREATE_FRAGMENT_SHADING_RATE_ATTACHMENT_BIT_EXT
	5.如果  fragmentDensityMap特性没有开启，flags不能包含VK_SHADER_CREATE_FRAGMENT_DENSITY_MAP_ATTACHMENT_BIT_EXT
	6.如果flags包含VK_SHADER_CREATE_ALLOW_VARYING_SUBGROUP_SIZE_BIT_EXT,则 subgroupSizeControl 特性必须开启
	7.如果flags包含VK_SHADER_CREATE_REQUIRE_FULL_SUBGROUPS_BIT_EXT,则 computeFullSubgroups 特性必须开启
	8.如果flags包含VK_SHADER_CREATE_REQUIRE_FULL_SUBGROUPS_BIT_EXT，则stage必须是VK_SHADER_STAGE_MESH_BIT_EXT, VK_SHADER_STAGE_TASK_BIT_EXT, 或者VK_SHADER_STAGE_COMPUTE_BIT其中之一
	9.如果stage不为VK_SHADER_STAGE_COMPUTE_BIT，则flags不能包含VK_SHADER_CREATE_DISPATCH_BASE_BIT_EXT
	10.如果stage不为VK_SHADER_STAGE_MESH_BIT_EXT，则flags不能包含VK_SHADER_CREATE_NO_TASK_SHADER_BIT_EXT
	11.如果flags包含VK_SHADER_CREATE_ALLOW_VARYING_SUBGROUP_SIZE_BIT_EXT 和 VK_SHADER_CREATE_REQUIRE_FULL_SUBGROUPS_BIT_EXT，则着色器的本地工作组大小的X维度必须为 maxSubgroupSize 倍数
	12.如果flags包含VK_SHADER_CREATE_REQUIRE_FULL_SUBGROUPS_BIT_EXT但是不包含VK_SHADER_CREATE_ALLOW_VARYING_SUBGROUP_SIZE_BIT_EXT，且pNext中没有 VkShaderRequiredSubgroupSizeCreateInfoEXT 则
													则着色器的本地工作组大小的X维度必须为 subgroupSize 倍数
	13.stage不能为 VK_SHADER_STAGE_ALL_GRAPHICS 或者 VK_SHADER_STAGE_ALL，VK_SHADER_STAGE_SUBPASS_SHADING_BIT_HUAWEI或者VK_SHADER_STAGE_CLUSTER_CULLING_BIT_HUAWEI
	14.如果tessellationShader特性没有开启，则stage，nextStage不能为VK_SHADER_STAGE_TESSELLATION_CONTROL_BIT 或者 VK_SHADER_STAGE_TESSELLATION_EVALUATION_BIT
	15.如果geometryShader特性没有开启，则stage，nextStage不能为VK_SHADER_STAGE_GEOMETRY_BIT
	16.如果 taskShader 特性没有开启，则stage不能为VK_SHADER_STAGE_TASK_BIT_EXT
	17.如果 meshShader 特性没有开启，则stage不能为VK_SHADER_STAGE_MESH_BIT_EXT
	18.如果stage为VK_SHADER_STAGE_VERTEX_BIT，nextStage不能包含任何除了VK_SHADER_STAGE_TESSELLATION_CONTROL_BIT, VK_SHADER_STAGE_GEOMETRY_BIT, 以及VK_SHADER_STAGE_FRAGMENT_BIT之外的stage
	19.如果stage为VK_SHADER_STAGE_TESSELLATION_CONTROL_BIT，nextStage不能包含除了VK_SHADER_STAGE_TESSELLATION_EVALUATION_BIT之外的stage
	20.如果stage为VK_SHADER_STAGE_TESSELLATION_EVALUATION_BIT，nextStage不能包含除了 VK_SHADER_STAGE_GEOMETRY_BIT和 VK_SHADER_STAGE_FRAGMENT_BIT之外的stage
	21.如果stage为 VK_SHADER_STAGE_GEOMETRY_BIT，nextStage不能包含除了 VK_SHADER_STAGE_FRAGMENT_BIT之外的stage
	22.如果stage为  VK_SHADER_STAGE_FRAGMENT_BIT或者VK_SHADER_STAGE_COMPUTE_BIT，nextStage必须为0
	23.如果stage为 VK_SHADER_STAGE_TASK_BIT_EXT，nextStage不能包含除了 VK_SHADER_STAGE_MESH_BIT_EXT之外的stage
	24.如果stage为 VK_SHADER_STAGE_MESH_BIT_EXT，nextStage不能包含除了 VK_SHADER_STAGE_FRAGMENT_BIT之外的stage
	25.如果codeType为 VK_SHADER_CODE_TYPE_BINARY_EXT，pCode必须对齐到16字节

	
	
	
	*/


	VK_DEVICE_FUNCTION_GET_AND_CALL(device, vkCreateShadersEXT, device, 1, &shaderCreateInfo, nullptr, &shaderExt);//如果某个shader模块创建失败，对应的shaderExt则会返回VK_NULL_HANDLE
	/*
	有效用法：
	1. shaderObject特性必须开启
	2.只要pCreateInfos中任何元素的flags包含VK_SHADER_CREATE_LINK_STAGE_BIT_EXT，则所有其他元素的stage为VK_SHADER_STAGE_VERTEX_BIT,
									VK_SHADER_STAGE_TESSELLATION_CONTROL_BIT, VK_SHADER_STAGE_TESSELLATION_EVALUATION_BIT,
									VK_SHADER_STAGE_GEOMETRY_BIT, 或者 VK_SHADER_STAGE_FRAGMENT_BIT，
									VK_SHADER_STAGE_TASK_BIT_EXT 或这 VK_SHADER_STAGE_MESH_BIT_EXT的flags也必须包含VK_SHADER_CREATE_LINK_STAGE_BIT_EXT
	3.如果pCreateInfos中任何元素的stage是VK_SHADER_STAGE_TASK_BIT_EXT 或者 VK_SHADER_STAGE_MESH_BIT_EXT的flags中包含VK_SHADER_CREATE_LINK_STAGE_BIT_EXT，则
									pCreateInfos中将没有stage为VK_SHADER_STAGE_VERTEX_BIT的flags包含VK_SHADER_CREATE_LINK_STAGE_BIT_EXT
	4.如果pCreateInfos中有存在stage为 VK_SHADER_STAGE_MESH_BIT_EXT且flags包含VK_SHADER_CREATE_LINK_STAGE_BIT_EXT 和VK_SHADER_CREATE_NO_TASK_SHADER_BIT_EXT的元素，则
									pCreateInfos中将没有stage为VK_SHADER_STAGE_TASK_BIT_EXT的flags包含VK_SHADER_CREATE_LINK_STAGE_BIT_EXT
	5.如果pCreateInfos的每个元素的flags包含VK_SHADER_CREATE_LINK_STAGE_BIT_EXT，如果存在其他元素的stage逻辑上迟于前面的且flags也包含VK_SHADER_CREATE_LINK_STAGE_BIT_EXT，则
									前面的nextStage必须等于比前面的flags含有VK_SHADER_CREATE_LINK_STAGE_BIT_EXT的 stage的逻辑更前面的一个元素的stage （翻译不准）
	6.pCreateInfos的每个元素的flags包含VK_SHADER_CREATE_LINK_STAGE_BIT_EXT的stage必须是不同的，codeType必须相同
	7.pCreateInfos的元素如果有元素的stage包含VK_SHADER_STAGE_TESSELLATION_CONTROL_BIT和 VK_SHADER_STAGE_TESSELLATION_EVALUATION_BIT,flags包含VK_SHADER_CREATE_LINK_STAGE_BIT_EXT，codeType为VK_SHADER_CODE_TYPE_SPIRV_EXT，
									而且 VK_SHADER_STAGE_TESSELLATION_CONTROL_BIT状态的pCode包含 OpExecutionMode指令指明细分的类型，则它必须和VK_SHADER_STAGE_TESSELLATION_EVALUATION_BIT的细分类型匹配，同样orientation of triangles,也必须匹配，
									 在细分图元边界上的spacing of segments 也必须匹配，output patch size也必须匹配
	8.pCreateInfos的元素如果有元素的stage包含VK_SHADER_STAGE_TESSELLATION_CONTROL_BIT和 VK_SHADER_STAGE_TESSELLATION_EVALUATION_BIT,flags包含VK_SHADER_CREATE_LINK_STAGE_BIT_EXT，codeType为VK_SHADER_CODE_TYPE_SPIRV_EXT,，
									而且 VK_SHADER_STAGE_TESSELLATION_CONTROL_BIT状态的pCode包含 OpExecutionMode指令指明 PointMode，则VK_SHADER_STAGE_TESSELLATION_EVALUATION_BIT也必须指明 PointMode
	
	9.如果pCreateInfos包含一个stage为VK_SHADER_STAGE_MESH_BIT_EXT且codeType为VK_SHADER_CODE_TYPE_SPIRV_EXT且没有设置VK_SHADER_CREATE_NO_TASK_SHADER_BIT_EXT，则mesh shader就不能声明一个以 DrawIndex BuiltIn描述的变量
	
	
	
	*/



	//绑定shader
	{
		VkCommandBuffer cmdbuf;
		VkShaderStageFlagBits stage;
		VK_DEVICE_FUNCTION_GET_AND_CALL(device, vkCmdBindShadersEXT, cmdbuf, 1, &stage, &shaderExt);//绑定shader以及指定的stage,相当于重新绑定pupeline上对应stage的着色器
		/*
		合法用法
		1.如果解绑某个shader只需要将pShaders中对应的位置设置为VK_NULL_HANDLE即可,如果pShaders为NULL，等同于所有shader都解绑
		2.shaderObject特性必须开启
		3.pShaders的每个元素的stage必须是不同的
		4.pStages不能包含VK_SHADER_STAGE_ALL_GRAPHICS 或者 VK_SHADER_STAGE_ALL，VK_SHADER_STAGE_RAYGEN_BIT_KHR,
														   VK_SHADER_STAGE_ANY_HIT_BIT_KHR, VK_SHADER_STAGE_CLOSEST_HIT_BIT_KHR,
														   VK_SHADER_STAGE_MISS_BIT_KHR, VK_SHADER_STAGE_INTERSECTION_BIT_KHR, 或者
														   VK_SHADER_STAGE_CALLABLE_BIT_KHR，VK_SHADER_STAGE_SUBPASS_SHADING_BIT_HUAWEI，
														   VK_SHADER_STAGE_CLUSTER_CULLING_BIT_HUAWEI
		5.如果pShaders不为空且其中的不为VK_NULL_HANDLE的元素的创建时候的stage必须和pStages中的对应位置的stage相同
		6.如果pStages包含VK_SHADER_STAGE_TASK_BIT_EXT 和 VK_SHADER_STAGE_VERTEX_BIT，且pShaders不为NULL,且在pShaders中VK_SHADER_STAGE_TASK_BIT_EXT相同位置的元素不为VK_NULL_HANDLE,
				则VK_SHADER_STAGE_VERTEX_BIT相同位置的pShader元素必须为VK_NULL_HANDLE
		7.如果pStages包含VK_SHADER_STAGE_MESH_BIT_EXT 和 VK_SHADER_STAGE_VERTEX_BIT,，且pShaders不为NULL,且在pShaders中VK_SHADER_STAGE_MESH_BIT_EXT相同位置的元素不为VK_NULL_HANDLE,
				则VK_SHADER_STAGE_VERTEX_BIT相同位置的pShader元素必须为VK_NULL_HANDLE
		8.如果tessellationShader特性没有开启，且pStages包含VK_SHADER_STAGE_TESSELLATION_CONTROL_BIT 或者 VK_SHADER_STAGE_TESSELLATION_EVALUATION_BIT，且pShaders不为NULL,则stage对应的pShader元素必须为VK_NULL_HANDLE
		9.如果geometryShader特性没有开启，且pStages包含VK_SHADER_STAGE_GEOMETRY_BIT，且pShaders不为NULL,则stage对应的pShader元素必须为VK_NULL_HANDLE
		10.如果 taskShader 特性没有开启，且pStages包含VK_SHADER_STAGE_TASK_BIT_EXT，且pShaders不为NULL,则stage对应的pShader元素必须为VK_NULL_HANDLE
		11.如果 meshShader 特性没有开启，且pStages包含VK_SHADER_STAGE_MESH_BIT_EXT，且pShaders不为NULL,则stage对应的pShader元素必须为VK_NULL_HANDLE
		12.如果pStages包含 VK_SHADER_STAGE_COMPUTE_BIT,则cmdbuf所在的VkCommandPool的queueFamilyIndex必须支持计算操作
		13.如果 pStages 包含 VK_SHADER_STAGE_VERTEX_BIT, VK_SHADER_STAGE_TESSELLATION_CONTROL_BIT,
				VK_SHADER_STAGE_TESSELLATION_EVALUATION_BIT, VK_SHADER_STAGE_GEOMETRY_BIT, 或者
				VK_SHADER_STAGE_FRAGMENT_BIT，VK_SHADER_STAGE_MESH_BIT_EXT 或者 VK_SHADER_STAGE_TASK_BIT_EXT,
				则cmdbuf所在的VkCommandPool的queueFamilyIndex必须支持图形操作
		*/
	


		//设置状态，主要是设置动态管线状态

		//以下命令需要在绘制命令之前设置
		vkCmdSetViewportWithCount(cmdbuf, 0, VK_NULL_HANDLE);
		vkCmdSetScissorWithCount(cmdbuf, 0, VK_NULL_HANDLE);
		vkCmdSetRasterizerDiscardEnable(cmdbuf, VK_FALSE);

		//如果shader绑定VK_SHADER_STAGE_VERTEX_BIT，则以下命令需要在绘制命令前设置
		VK_DEVICE_FUNCTION_GET_AND_CALL(device, vkCmdSetVertexInputEXT, cmdbuf, 0, VK_NULL_HANDLE, 0, VK_NULL_HANDLE);
		vkCmdSetPrimitiveTopology(cmdbuf, VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST);
		VK_DEVICE_FUNCTION_GET_AND_CALL(device, vkCmdSetPatchControlPointsEXT, cmdbuf, 0); //if primitiveTopology is VK_PRIMITIVE_TOPOLOGY_PATCH_LIST
		vkCmdSetPrimitiveRestartEnable(cmdbuf, VK_FALSE);

		//如果shader绑定VK_SHADER_STAGE_TESSELLATION_EVALUATION_BIT，则以下命令需要在绘制命令前设置
		VK_DEVICE_FUNCTION_GET_AND_CALL(device, vkCmdSetTessellationDomainOriginEXT, cmdbuf, VK_TESSELLATION_DOMAIN_ORIGIN_UPPER_LEFT);

		//如果 rasterizerDiscardEnable 为 VK_FALSE,，则以下命令需要在绘制命令前设置
		VK_DEVICE_FUNCTION_GET_AND_CALL(device, vkCmdSetRasterizationSamplesEXT, cmdbuf, VK_SAMPLE_COUNT_1_BIT);
		VK_DEVICE_FUNCTION_GET_AND_CALL(device, vkCmdSetSampleMaskEXT, cmdbuf, VK_SAMPLE_COUNT_1_BIT, VK_NULL_HANDLE);
		VK_DEVICE_FUNCTION_GET_AND_CALL(device, vkCmdSetAlphaToCoverageEnableEXT, cmdbuf, VK_FALSE);
		VK_DEVICE_FUNCTION_GET_AND_CALL(device, vkCmdSetAlphaToOneEnableEXT, cmdbuf, VK_FALSE);// if the alphaToOne feature is enabled on the device
		VK_DEVICE_FUNCTION_GET_AND_CALL(device, vkCmdSetPolygonModeEXT, cmdbuf, VK_POLYGON_MODE_FILL);
		vkCmdSetLineWidth(cmdbuf, 1);//  如果polygonMode 为 VK_POLYGON_MODE_LINE, 或者 如果 shader 绑定到
			//VK_SHADER_STAGE_VERTEX_BIT stage 且 primitiveTopology 为 line topology, 或者如果 shader 输出 line primitives且绑定到 VK_SHADER_STAGE_TESSELLATION_EVALUATION_BIT 或者
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



		//如果 rasterizerDiscardEnable 为 VK_FALSE,且shader绑定到 VK_SHADER_STAGE_FRAGMENT_BIT，则以下命令需要在绘制命令前设置
		VK_DEVICE_FUNCTION_GET_AND_CALL(device, vkCmdSetLogicOpEnableEXT, cmdbuf, VK_FALSE); //if the logicOp feature is enabled on the device
		VK_DEVICE_FUNCTION_GET_AND_CALL(device, vkCmdSetLogicOpEXT, cmdbuf, VK_LOGIC_OP_AND);// if logicOpEnable is VK_TRUE
		VK_DEVICE_FUNCTION_GET_AND_CALL(device, vkCmdSetColorBlendEnableEXT,cmdbuf, 0, 0, VK_NULL_HANDLE);// 如果绑定了颜色附件，将会设置render pass的附件绘制时对应的值
		VK_DEVICE_FUNCTION_GET_AND_CALL(device, vkCmdSetColorWriteMaskEXT, cmdbuf, 0, 0, VK_NULL_HANDLE);// 如果绑定了颜色附件，将会设置render pass的附件绘制时对应的值

		VK_DEVICE_FUNCTION_GET_AND_CALL(device, vkCmdSetColorBlendEquationEXT, cmdbuf, 0, 0, VK_NULL_HANDLE);// 如果绑定了颜色附件,对于每一个附件其pColorBlendEnables的是一个VK_TRUE的指针
		VK_DEVICE_FUNCTION_GET_AND_CALL(device, vkCmdSetColorBlendAdvancedEXT, cmdbuf, 0, 0, VK_NULL_HANDLE);// 如果绑定了颜色附件,对于每一个附件其pColorBlendEnables的是一个VK_TRUE的指针
		vkCmdSetBlendConstants(cmdbuf, nullptr);/* 如果 pColorBlendEnables 的值 VK_TRUE,则
			pColorBlendEquations中相同索引下的元素是一个任何VkBlendFactor成员为VK_BLEND_FACTOR_CONSTANT_COLOR, VK_BLEND_FACTOR_ONE_MINUS_CONSTANT_COLOR,
			VK_BLEND_FACTOR_CONSTANT_ALPHA, 或者 VK_BLEND_FACTOR_ONE_MINUS_CONSTANT_ALPHA的 VkColorBlendEquationEXT
			*/



		//如果 rasterizerDiscardEnable 为 VK_FALSE,且shader绑定到 VK_SHADER_STAGE_FRAGMENT_BIT ，且 pipelineFragmentShadingRate特性开启，则以下命令需要在绘制命令前设置
		VK_DEVICE_FUNCTION_GET_AND_CALL(device, vkCmdSetFragmentShadingRateKHR,cmdbuf, nullptr, nullptr);


		//如果  geometryStreams 开启,且shader绑定到 VK_SHADER_STAGE_GEOMETRY_BIT，则以下命令需要在绘制命令前设置
		VK_DEVICE_FUNCTION_GET_AND_CALL(device, vkCmdSetRasterizationStreamEXT, cmdbuf, 0);


		//如果 rasterizerDiscardEnable 为 VK_FALSE,且 VK_EXT_discard_rectangles拓展开启，则以下命令需要在绘制命令前设置
		VK_DEVICE_FUNCTION_GET_AND_CALL(device, vkCmdSetDiscardRectangleEnableEXT,cmdbuf,VK_FALSE);
		VK_DEVICE_FUNCTION_GET_AND_CALL(device, vkCmdSetDiscardRectangleModeEXT, cmdbuf, VK_DISCARD_RECTANGLE_MODE_EXCLUSIVE_EXT); //if discardRectangleEnable is VK_TRUE
		VK_DEVICE_FUNCTION_GET_AND_CALL(device, vkCmdSetDiscardRectangleEXT, cmdbuf, 0, 0, nullptr); //if discardRectangleEnable is VK_TRUE


		//如果 rasterizerDiscardEnable 为 VK_FALSE,且 VK_EXT_conservative_rasterization拓展开启，则以下命令需要在绘制命令前设置
		VK_DEVICE_FUNCTION_GET_AND_CALL(device, vkCmdSetConservativeRasterizationModeEXT, cmdbuf, VK_CONSERVATIVE_RASTERIZATION_MODE_DISABLED_EXT);
		VK_DEVICE_FUNCTION_GET_AND_CALL(device, vkCmdSetExtraPrimitiveOverestimationSizeEXT,cmdbuf, 1); //if conservativeRasterizationMode is VK_CONSERVATIVE_RASTERIZATION_MODE_OVERESTIMATE_EXT


		//如果  depthClipEnable 特性开启，则以下命令需要在绘制命令前设置
		VK_DEVICE_FUNCTION_GET_AND_CALL(device, vkCmdSetDepthClipEnableEXT, cmdbuf, VK_TRUE);


		//如果 rasterizerDiscardEnable 为 VK_FALSE,且 VK_EXT_sample_locations拓展开启，则以下命令需要在绘制命令前设置
		VK_DEVICE_FUNCTION_GET_AND_CALL(device, vkCmdSetSampleLocationsEnableEXT, cmdbuf, VK_FALSE);
		VK_DEVICE_FUNCTION_GET_AND_CALL(device, vkCmdSetSampleLocationsEXT, cmdbuf, nullptr); //if sampleLocationsEnable is VK_TRUE


		//如果 rasterizerDiscardEnable 为 VK_FALSE,且 VK_EXT_provoking_vertex拓展开启,且shader绑定到VK_SHADER_STAGE_VERTEX_BIT，则以下命令需要在绘制命令前设置
		VK_DEVICE_FUNCTION_GET_AND_CALL(device, vkCmdSetProvokingVertexModeEXT, cmdbuf, VK_PROVOKING_VERTEX_MODE_FIRST_VERTEX_EXT);

		//如果 VK_KHR_line_rasterization 或者 VK_EXT_line_rasterization 拓展开启，且rasterizerDiscardEnable 为 VK_FALSE，如果 polygonMode 为 VK_POLYGON_MODE_LINE或者
		//shader绑定到  VK_SHADER_STAGE_VERTEX_BIT且primitiveTopology为line topology或者shader输出line topology 且绑定到VK_SHADER_STAGE_TESSELLATION_EVALUATION_BIT 或者 VK_SHADER_STAGE_GEOMETRY_BIT,则以下命令需要在绘制命令前设置
		VK_DEVICE_FUNCTION_GET_AND_CALL(device, vkCmdSetLineRasterizationModeEXT, cmdbuf, VK_LINE_RASTERIZATION_MODE_BRESENHAM_EXT);
		VK_DEVICE_FUNCTION_GET_AND_CALL(device, vkCmdSetLineStippleEnableEXT, cmdbuf, VK_FALSE);
		//vkCmdSetLineStippleKHR  //if stippledLineEnable is VK_TRUE


		//如果 depthClipControl 特性开启，则以下命令需要在绘制命令前设置
		VK_DEVICE_FUNCTION_GET_AND_CALL(device, vkCmdSetDepthClipNegativeOneToOneEXT, cmdbuf, VK_FALSE);




		//如果 rasterizerDiscardEnable 为 VK_FALSE,且 colorWriteEnable 特性开启,且shader绑定到VK_SHADER_STAGE_FRAGMENT_BIT，则以下命令需要在绘制命令前设置
		VK_DEVICE_FUNCTION_GET_AND_CALL(device, vkCmdSetColorWriteEnableEXT, cmdbuf, 0, nullptr); //with values set for every color attachment in the render pass instance active at draw time

		//如果 rasterizerDiscardEnable 为 VK_FALSE,且  attachmentFeedbackLoopDynamicState 特性开启,且shader绑定到VK_SHADER_STAGE_FRAGMENT_BIT，则以下命令需要在绘制命令前设置
		VK_DEVICE_FUNCTION_GET_AND_CALL(device, vkCmdSetAttachmentFeedbackLoopEnableEXT, cmdbuf, VK_IMAGE_ASPECT_COLOR_BIT);


		//如果  VK_NV_clip_space_w_scaling 特性开启,则以下命令需要在绘制命令前设置
		VK_DEVICE_FUNCTION_GET_AND_CALL(device, vkCmdSetViewportWScalingEnableNV,cmdbuf, VK_FALSE);
		VK_DEVICE_FUNCTION_GET_AND_CALL(device, vkCmdSetViewportWScalingNV,cmdbuf, 0, 0, nullptr); //if viewportWScalingEnable is VK_TRUE


		//如果  VK_NV_clip_space_w_scaling 特性开启,则以下命令需要在绘制命令前设置
		VK_DEVICE_FUNCTION_GET_AND_CALL(device, vkCmdSetViewportSwizzleNV, cmdbuf, 0, 0, nullptr);


		//如果 rasterizerDiscardEnable 为 VK_FALSE,且   VK_NV_fragment_coverage_to_color 拓展开启,且shader绑定到VK_SHADER_STAGE_FRAGMENT_BIT，则以下命令需要在绘制命令前设置
		VK_DEVICE_FUNCTION_GET_AND_CALL(device, vkCmdSetCoverageToColorEnableNV, cmdbuf, VK_FALSE);
		VK_DEVICE_FUNCTION_GET_AND_CALL(device, vkCmdSetCoverageToColorLocationNV, cmdbuf, 0); //if coverageToColorEnable is VK_TRUE


		//如果 rasterizerDiscardEnable 为 VK_FALSE,且   VK_NV_framebuffer_mixed_samples 拓展开启，则以下命令需要在绘制命令前设置
		VK_DEVICE_FUNCTION_GET_AND_CALL(device, vkCmdSetCoverageModulationModeNV, cmdbuf, VK_COVERAGE_MODULATION_MODE_ALPHA_NV);
		VK_DEVICE_FUNCTION_GET_AND_CALL(device, vkCmdSetCoverageModulationTableEnableNV, cmdbuf, VK_FALSE); //if coverageModulationMode is not VK_COVERAGE_MODULATION_MODE_NONE_NV
		VK_DEVICE_FUNCTION_GET_AND_CALL(device, vkCmdSetCoverageModulationTableNV, cmdbuf, 0, nullptr); //if coverageModulationTableEnable is VK_TRUE


		//如果 rasterizerDiscardEnable 为 VK_FALSE,且    coverageReductionMode 特性开启，则以下命令需要在绘制命令前设置
		VK_DEVICE_FUNCTION_GET_AND_CALL(device, vkCmdSetCoverageReductionModeNV, cmdbuf, VK_COVERAGE_REDUCTION_MODE_MERGE_NV);

		//如果 rasterizerDiscardEnable 为 VK_FALSE,且     representativeFragmentTest 特性开启，则以下命令需要在绘制命令前设置
		VK_DEVICE_FUNCTION_GET_AND_CALL(device, vkCmdSetRepresentativeFragmentTestEnableNV, cmdbuf, VK_FALSE);

		//如果 rasterizerDiscardEnable 为 VK_FALSE,且      shadingRateImage 特性开启，则以下命令需要在绘制命令前设置
		VK_DEVICE_FUNCTION_GET_AND_CALL(device, vkCmdSetCoarseSampleOrderNV, cmdbuf, VK_COARSE_SAMPLE_ORDER_TYPE_CUSTOM_NV, 0, nullptr);
		VK_DEVICE_FUNCTION_GET_AND_CALL(device, vkCmdSetShadingRateImageEnableNV, cmdbuf, VK_FALSE);
		VK_DEVICE_FUNCTION_GET_AND_CALL(device, vkCmdSetViewportShadingRatePaletteNV, cmdbuf, 0, 0, nullptr); // if shadingRateImageEnable is VK_TRUE


		//如果   exclusiveScissor 特性开启，则以下命令需要在绘制命令前设置
		VK_DEVICE_FUNCTION_GET_AND_CALL(device, vkCmdSetExclusiveScissorEnableNV, cmdbuf, 0, 0, nullptr);
		VK_DEVICE_FUNCTION_GET_AND_CALL(device, vkCmdSetExclusiveScissorNV, cmdbuf,0,0,nullptr); // if any value in pExclusiveScissorEnables is VK_TRUE


	}


	VK_DEVICE_FUNCTION_GET_AND_CALL(device, vkDestroyShaderEXT, device, shaderExt, nullptr);

}

void ShadersTest::ShaderModuleCreateTest()
{
	//shader module含有一个或多个入口点，且必须以SPIR-V shader代码创建。
	VkShaderModule shaderModule;


	VkShaderModuleCreateInfo shaderModuleCreateInfo{};
	shaderModuleCreateInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
		
		//从VkValidationCacheEXT的对象中获取的data
		VkValidationCacheEXT otherValidationCache{ VK_NULL_HANDLE };
		size_t validationDataSize = 0;
		std::vector<char> validationData;
		VK_DEVICE_FUNCTION_GET_AND_CALL(device, vkGetValidationCacheDataEXT, device, otherValidationCache, &validationDataSize, nullptr);
		validationData.resize(validationDataSize);
		VK_DEVICE_FUNCTION_GET_AND_CALL(device, vkGetValidationCacheDataEXT, device, otherValidationCache, &validationDataSize, validationData.data());/*
			从vkGetValidationCacheDataEXT获取的pData为了能让应用识别是否和当前device匹配，pData的开头会包含头部信息，头部信息的主要格式为：
				前从偏移位置0后4字节表示整个头部信息的字节长度，以字节流写入；
				前从偏移位置4后4字节表示validation cache的版本信息VkValidationCacheHeaderVersionEXT，可能的版本信息为VK_VALIDATION_CACHE_HEADER_VERSION_ONE_EXT = 1指明版本为1，以字节流写入；
				前从偏移位置8后VK_UUID_SIZE(16)字节表示表示为UUID的层提交ID，它唯一地标识用于生成这些验证结果的验证层的版本
		*/

		//创建一个VkValidationCacheEXT,validationCache可以允许在单个应用程序运行中和在多个运行之间重用内部验证的结果。
		VkValidationCacheEXT validationCache{VK_NULL_HANDLE};
		VkValidationCacheCreateInfoEXT validationCacheCreateInfo{};
		validationCacheCreateInfo.sType = VK_STRUCTURE_TYPE_VALIDATION_CACHE_CREATE_INFO_EXT;
		validationCacheCreateInfo.flags = 0;//保留
		validationCacheCreateInfo.pNext = nullptr;
		validationCacheCreateInfo.initialDataSize = validationDataSize;//pInitialData的字节数目，如果为0，则pInitialData初始为空
		validationCacheCreateInfo.pInitialData = validationData.data();//是一个指向之前获取的validation cache的数据，如果数据和当前device不匹配，则validation cache的则会被初始化为空，如果initialDataSize为0，则pInitialData中的数据被忽略,如果不为0，则必须和pInitialData大小匹配且必须是由vkGetValidationCacheDataEXT获得的数据



		VK_DEVICE_FUNCTION_GET_AND_CALL(device, vkCreateValidationCacheEXT, device, &validationCacheCreateInfo, nullptr, &validationCache);
		

		//合并VkValidationCacheEXT
		VK_DEVICE_FUNCTION_GET_AND_CALL(device, vkMergeValidationCachesEXT, device, validationCache, 1, &otherValidationCache);

		//销毁VkValidationCacheEXT
		VK_DEVICE_FUNCTION_GET_AND_CALL(device, vkDestroyValidationCacheEXT, device, otherValidationCache, nullptr);
		
		VkShaderModuleValidationCacheCreateInfoEXT shaderModuleValidationCacheCreateInfo{};
		shaderModuleValidationCacheCreateInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_VALIDATION_CACHE_CREATE_INFO_EXT;
		shaderModuleValidationCacheCreateInfo.pNext = nullptr;
		shaderModuleValidationCacheCreateInfo.validationCache  = validationCache;//

	shaderModuleCreateInfo.pNext = &shaderModuleValidationCacheCreateInfo;//可以包含VkShaderModuleValidationCacheCreateInfoEXT用来缓存shader的校验结果到VkValidationCacheEXT中
	shaderModuleCreateInfo.codeSize = 0;
	shaderModuleCreateInfo.pCode = nullptr;
	shaderModuleCreateInfo.flags = 0;//目前没有使用
	/*
	合法用法：
	1.pCode指向一个SPIR-V格式的数据
	2.如果pCode是SPIR-V格式的数据，则：（1）codeSize必须是4的倍数
									   （2）pCode指向的必须是合法的SPIR-V格式的数据，以Khronos SPIR-V Specification 中定义的格式编码
									   （3）pCode必须附加到 SPIR-V Environment附录的 Validation Rules within a Module部分描述的验证规则中
	                                                    
									   （4）pCode必须声明shader的spirv代码capability
									   （6）pCode不能声明API不支持的capability， 在SPIR-V Environment附录中的 Capabilities中进行描述
									   （7）pCode声明的列举在SPIR-V Environment附录的capability，必须满足其他对应的条件
									   （8）pCode不能声明API不支持的扩展，在SPIR-V Environment附录中的  Extension 中进行描述
									   （9）如果 VK_NV_glsl_shader 拓展没有开启，则pCode必须为SPIR-V格式的数据
									   （10）如果pCode是glsl代码，则其glsl代码必须符合 GL_KHR_vulkan_glsl 特性描述的要求
									   （11）codeSize必须大于0
									   （12）pCode必须是 codeSize / 4  个uint32_t的数组
	
	*/


	vkCreateShaderModule(device, &shaderModuleCreateInfo, nullptr, &shaderModule);//shaderModule创建好后，其包含的入口点就可以被使用，如果 maintenance5开启，则创建shaderModule则会被忽略，只需要
			//在创建pipeline的时候在创建信息中的pNext中添加VkPipelineShaderStageCreateInfo即可

	//shader module 标识符
	//shader module 有自己的标识符
	VkShaderModuleIdentifierEXT shaderModuleIdentifier{};
	shaderModuleIdentifier.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_IDENTIFIER_EXT;
	shaderModuleIdentifier.pNext = nullptr;
	shaderModuleIdentifier.identifierSize;//返回的identifier的大小， 0 < identifierSize <=  VK_MAX_SHADER_MODULE_IDENTIFIER_SIZE_EXT
	shaderModuleIdentifier.identifier;//返回的标识符

	VK_DEVICE_FUNCTION_GET_AND_CALL(device, vkGetShaderModuleCreateInfoIdentifierEXT, device, &shaderModuleCreateInfo, &shaderModuleIdentifier);//这个标识符只在两个不同的device且含有相同的shaderModuleIdentifierAlgorithmUUID的情况下才有意义，
	//不同的shaderModuleCreateInfo可能会返回相同的VkShaderModuleIdentifierEXT，因为VkShaderModuleIdentifierEXT的返回取决于shaderModuleCreateInfo以及shaderModuleIdentifierAlgorithmUUID,且返回的值必须和
	//vkGetShaderModuleIdentifierEXT返回的值相同（在 VkShaderModuleCreateInfo的pNext中进行指定）



	


	vkDestroyShaderModule(device, shaderModule, nullptr);



}



//shader 绑定
/*
调用 vkCmdBindPipeline为 VkPipelineBindPoint.绑定管线状态，调用vkCmdBindShadersEXT为管线状态绑定shader


*/


//shader 执行
/*
shader的调用顺序基本是未知的，片段着色器的调用顺序是光栅化的顺序
shader stage的结束在所有当前状态的着色器执行结束之后

*/


//shader 内存访问顺序
/*
shader的内存访问顺序是无序的
*/

//shader 输入输出
/*
通过location和input以及output相关的内嵌变量描述输入输出
*/



//task shader
/*
task shader链接到mesh shader用来为产生后续图形管线阶段需要的图元数据,主要是为mesh shader产生变量
在vkCmdDrawMeshTasksNV阶段执行
详情见p672
*/

//mesh shader
/*
mesh shader用来为产生后续图形管线阶段需要的图元数据,输出图元关联的顶点数据以及顶点上的属性数据
在vkCmdDrawMeshTasksNV阶段执行
详情见p673
*/


//cluster culling shader
/*
cluster culling shader用来执行cluster-based culling 且产生后续图形管线阶段需要的cluster 绘制命令
在vkCmdDrawClusterHUAWEI阶段执行
详情见p673
*/


//vertex shader
/*
vertex shader用来处理顶点数据以及其属性数据并输出顶点和其相关的数据。使用图元着色器的图形管道必须包含一个顶点着色器，并且顶点着色器阶段始终是图形管道中的第一个着色器阶段
详情见p674
*/

//tessellation control shader
/*
tessellation control shader用来读取input patch并输出output patch，在input patch上调用并输出一个控制点以及output patch的相关数据。
控制点数目可以通过VkPipelineTessellationStateCreateInfo. patchControlPoints来设置或者通过命令vkCmdSetPatchControlPointsEXT动态设置（需开启VK_DYNAMIC_STATE_PATCH_CONTROL_POINTS_EXT，且需要 extendedDynamicState2PatchControlPoints 特性或者该着色器启用，且 0 < patchControlPoints <= VkPhysicalDeviceLimits::maxTessellationPatchSize）。
执行处理来自顶点着色器的数据输入
详情见p675
*/


//tessellation evaluation shader
/*
tessellation evaluation shader用来操作控制点及其关联数据的input patch，以及单个输入重心坐标，指示调用在被细分的patch中的相对位置，并输出单个顶点及其关联数据。
执行处理每一个有tessellator产生的顶点以及数据
详情见p676
*/

//geometry shader
/*
geometry shader用来处理一批输入图元的顶点数据以及其相关的数据，然后产生新的图元数据相关的顶点数据以及顶点相关数据
执行处理来自tessellation阶段输入的图元（如果有开启该阶段）或者在顶点着色器前的顶点装配阶段装配的图元
详情见p677
*/

//fragment shader
/*
fragment shader用来操作管线的单个fragment以及其相关的数据。
详情见p677
*/


//compute shader
/*
compute shader通过vkCmdDispatch 或者 vkCmdDispatchIndirect调用，访问资源的方式和图形管线访问资源类似
详情见p677
*/


//ray generation shader
/*
ray generation shader类似于compute shader，主要是使用 pipeline trace ray（p5331） 命令来产生结果。
ray generation shader为每一个ray tracing dispatch调用一次
详情见p678
*/

//intersection shader
/*
intersection shader为每条ray 或者每个图元计算相交，并且报告结果，通过为any-hit 和 closest shaders提供其可以读取的属性数据来进行通信,不能修改ray payload。

详情见p678
*/

// any-hit shader
/*
 any-hit shader调用在 intersection shader报告了罗列在当前 [tmin,tmax]中的相交ray之后，然后判断是否接受这些相交操作，一般都会接受除非shader调用了OpIgnoreIntersectionKHR。
 只能读取intersection shader生成的属性数据且可以读取和修改ray payload
详情见p678
*/

// closet hit shader
/*
closet hit shader可以调用 pipeline trace ray 命令来递归的进行ray tracing
只能读取intersection shader生成的属性数据且可以读取和修改ray payload
详情见p678
*/


// miss shader
/*
miss shader可以可以读取和修改ray payload且可以调用 pipeline trace ray 命令来进行新的ray tracing，但不能访问intersection shader产生的属性数据
miss shader在closet hit shader没有ray tracing的相交没有找到时执行
详情见p679
*/


// callable shader
/*
callable shader 可以访问callable payload（类比于ray payload）来做subroutine 操作
详情见p679
*/



/*
p679-691这里不再描述见文档



*/


void ShadersTest::CooperateMatrixsTest()
{
	// Provided by VK_KHR_cooperative_matrix
	typedef enum VkComponentTypeKHR {
		VK_COMPONENT_TYPE_FLOAT16_KHR = 0,//对应 SPIR-V OpTypeFloat 16.
		VK_COMPONENT_TYPE_FLOAT32_KHR = 1,//对应 SPIR-V OpTypeFloat 32.
		VK_COMPONENT_TYPE_FLOAT64_KHR = 2,//对应 SPIR-V OpTypeFloat 64.
		VK_COMPONENT_TYPE_SINT8_KHR = 3,//对应 SPIR-V  OpTypeInt 8 1.
		VK_COMPONENT_TYPE_SINT16_KHR = 4,//对应 SPIR-V  OpTypeInt 16 1.
		VK_COMPONENT_TYPE_SINT32_KHR = 5,//对应 SPIR-V OpTypeInt 32 1.
		VK_COMPONENT_TYPE_SINT64_KHR = 6,//对应 SPIR-V OpTypeInt 64 1.
		VK_COMPONENT_TYPE_UINT8_KHR = 7,//对应 SPIR-V  OpTypeInt 8 0.
		VK_COMPONENT_TYPE_UINT16_KHR = 8,//对应 SPIR-V  OpTypeInt 16 0.
		VK_COMPONENT_TYPE_UINT32_KHR = 9,//对应 SPIR-V  OpTypeInt 32 0.
		VK_COMPONENT_TYPE_UINT64_KHR = 10,//对应 SPIR-V  OpTypeInt 64 0.
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
	} VkComponentTypeKHR;//这个枚举类型没有定义，这里先定义作为示例
	
	// Provided by VK_KHR_cooperative_matrix
	typedef enum VkScopeKHR {
		VK_SCOPE_DEVICE_KHR = 1,//对应 SPIR-V Device scope.
		VK_SCOPE_WORKGROUP_KHR = 2,//对应 SPIR-V  Workgroup scope.
		VK_SCOPE_SUBGROUP_KHR = 3,//对应 SPIR-V  Subgroup scope.
		VK_SCOPE_QUEUE_FAMILY_KHR = 5,//对应 SPIR-V QueueFamily scope.
		// Provided by VK_NV_cooperative_matrix
		VK_SCOPE_DEVICE_NV = VK_SCOPE_DEVICE_KHR,
		// Provided by VK_NV_cooperative_matrix
		VK_SCOPE_WORKGROUP_NV = VK_SCOPE_WORKGROUP_KHR,
		// Provided by VK_NV_cooperative_matrix
		VK_SCOPE_SUBGROUP_NV = VK_SCOPE_SUBGROUP_KHR,
		// Provided by VK_NV_cooperative_matrix
		VK_SCOPE_QUEUE_FAMILY_NV = VK_SCOPE_QUEUE_FAMILY_KHR,
	} VkScopeKHR;//这个枚举类型没有定义，这里先定义作为示例
	
	// cooperative matrix type是一种 SPIR-V类型，其存储和计算作用在矩阵上，且在作用域实例中跨越调用进行传播
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
		VkBool32 saturatingAccumulation;//指示含有OpCooperativeMatrixMulAddKHR的SaturatingAccumulation是否存在。
		VkScopeKHR scope;
	};//这个数据结构没有定义，这里先定义作为示例
	auto vkGetPhysicalDeviceCooperativeMatrixPropertiesKHR = [](
		VkPhysicalDevice physicalDevice,
		uint32_t* pPropertyCount,
		VkCooperativeMatrixPropertiesKHR* pProperties) {
			return VK_SUCCESS;
	}; //这个接口没有定义，这里先定义作为示例


	//用法
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
	} VkCooperativeMatrixPropertiesNV;//这个数据结构没有定义，这里先定义作为示例
	auto vkGetPhysicalDeviceCooperativeMatrixPropertiesNV = [](
		VkPhysicalDevice physicalDevice,
		uint32_t* pPropertyCount,
		VkCooperativeMatrixPropertiesKHR* pProperties) {
			return VK_SUCCESS;
	}; //这个接口没有定义，这里先定义作为示例

	//用法
	uint32_t propertyCountNV = 0;
	std::vector<VkCooperativeMatrixPropertiesKHR> propertiesNV;
	vkGetPhysicalDeviceCooperativeMatrixPropertiesKHR(physicalDevice, &propertyCountNV, nullptr);
	propertiesNV.resize(propertyCountNV);
	vkGetPhysicalDeviceCooperativeMatrixPropertiesKHR(physicalDevice, &propertyCountNV, propertiesNV.data());
}

void ShadersTest::CUDAModuleTest()
{
	//CUDA模块必须包含一些内核代码，并且必须公开至少一个函数入口点
	struct VkCudaModuleNV_T {};//没有定义，这里定义作为示例
	VK_DEFINE_NON_DISPATCHABLE_HANDLE(VkCudaModuleNV)
		// Provided by VK_NV_cuda_kernel_launch
	typedef struct VkCudaModuleCreateInfoNV {
		VkStructureType sType;
		const void* pNext;
		size_t dataSize;//pData的长度
		const void* pData;//指向CUDA code的指针 PTX
	} VkCudaModuleCreateInfoNV;//没有定义，这里定义作为示例
	
	// Provided by VK_NV_cuda_kernel_launch
	auto vkCreateCudaModuleNV = [](
			VkDevice device,
			const VkCudaModuleCreateInfoNV* pCreateInfo,
			const VkAllocationCallbacks* pAllocator,
			VkCudaModuleNV* pModule) -> VkResult {
	
		return VK_SUCCESS;
	};//没有定义，这里定义作为示例
	

	VkCudaModuleNV cudaModule{};
	VkCudaModuleCreateInfoNV cudaModuleCreateInfo{};
	cudaModuleCreateInfo.sType = VK_STRUCTURE_TYPE_MAX_ENUM;//没有该结构体的类型定义所以先设置为非法值
	cudaModuleCreateInfo.pNext = nullptr;
	cudaModuleCreateInfo.dataSize = 0;
	cudaModuleCreateInfo.pData = nullptr;

	vkCreateCudaModuleNV(device, &cudaModuleCreateInfo, nullptr, &cudaModule);



	//cuda 函数由VkCudaFunctionNV表示，

	struct VkCudaFunctionNV_T {};//没有定义，这里定义作为示例

	// Provided by VK_NV_cuda_kernel_launch
	VK_DEFINE_NON_DISPATCHABLE_HANDLE(VkCudaFunctionNV)


	//创建cuda function
	// Provided by VK_NV_cuda_kernel_launch
	typedef struct VkCudaFunctionCreateInfoNV {
		VkStructureType sType;
		const void* pNext;
		VkCudaModuleNV module;//指明当前function所在的cuda 模块
		const char* pName;//是一个以空结尾的UTF-8字符串，其中包含此阶段的着色器入口点的名称。
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


	//获取cuda缓存数据，可以用来加速后续CUDA的初始化
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
	vkGetCudaModuleCacheNV(device, cudaModule, &cudaDataSize, cudaCacheData.data());//返回的缓存可以稍后用于进一步初始化CUDA模块，通过在使用 vkCreateCudaModuleNV 时发送这个缓存而不是PTX代码。




	//销毁cuda module
	// Provided by VK_NV_cuda_kernel_launch
	auto vkDestroyCudaFunctionNV = [](
		VkDevice device,
		VkCudaFunctionNV function,
		const VkAllocationCallbacks* pAllocator) {
	};
	vkDestroyCudaFunctionNV(device, cudaFunc, nullptr);


	//cuda在vulkan中使用的限制查看文档p711，这里不再描述



}






NS_TEST_END