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


	vkCreateShadersEXT(device, 1, &shaderCreateInfo, nullptr, &shaderExt);//如果某个shader模块创建失败，对应的shaderExt则会返回VK_NULL_HANDLE
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





}























NS_TEST_END