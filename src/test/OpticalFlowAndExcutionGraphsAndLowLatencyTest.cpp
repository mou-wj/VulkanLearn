#include "OpticalFlowAndExcutionGraphsAndLowLatencyTest.h"
#include "vulkan/vulkan_beta.h"
NS_TEST_BEGIN


OpticalFlowAndExcutionGraphsAndLowLatencyTest::OpticalFlowAndExcutionGraphsAndLowLatencyTest()
{
}

void OpticalFlowAndExcutionGraphsAndLowLatencyTest::run()
{
}

OpticalFlowAndExcutionGraphsAndLowLatencyTest::~OpticalFlowAndExcutionGraphsAndLowLatencyTest()
{
}

void OpticalFlowAndExcutionGraphsAndLowLatencyTest::OpticalFlowTest()
{
	//Optical Flow Queues  参见p3641
	{
		/*
		VK_NV_optical_flow 拓展提供了optical flow queue（光流队列 - 是一个与图形处理相关的特性，专门用于处理光流计算。光流是一种计算相邻帧之间像素运动的方法，通常用于视频分析、运动估计等应用。这个特性在Vulkan中主要用于优化和加速与光流相关的操作。）
		*/
	}

	//Optical Flow Image Formats  参见p3641
	{

		//枚举特定 optical flow 用途的支持的image formats
		uint32_t formatCount = 0;
		std::vector<VkOpticalFlowImageFormatPropertiesNV> opticalFlowImageFormatPropertiesNVs{};
		

		VkOpticalFlowImageFormatInfoNV opticalFlowImageFormatInfoNV{};
		opticalFlowImageFormatInfoNV.sType = VK_STRUCTURE_TYPE_OPTICAL_FLOW_IMAGE_FORMAT_INFO_NV;
		opticalFlowImageFormatInfoNV.pNext = nullptr;
		opticalFlowImageFormatInfoNV.usage = VK_OPTICAL_FLOW_USAGE_INPUT_BIT_NV;//为 VkOpticalFlowUsageFlagBitsNV 组合值位掩码，指明image预期的optical flow 用途
		/*
		VkOpticalFlowUsageFlagBitsNV:
		VK_OPTICAL_FLOW_USAGE_INPUT_BIT_NV : 指明image可以作为 optical flow operation的input 或者 reference frame
		VK_OPTICAL_FLOW_USAGE_OUTPUT_BIT_NV : 指明image可以作为 optical flow operation的output flow vector map
		VK_OPTICAL_FLOW_USAGE_HINT_BIT_NV : 指明image可以作为 optical flow operation的hint flow vector map
		VK_OPTICAL_FLOW_USAGE_COST_BIT_NV : 指明image可以作为 optical flow operation的output cost map
		VK_OPTICAL_FLOW_USAGE_GLOBAL_FLOW_BIT_NV : 指明image可以作为 optical flow operation的global flow vector
		*/


		vkGetPhysicalDeviceOpticalFlowImageFormatsNV(physicalDevice, &opticalFlowImageFormatInfoNV, &formatCount, nullptr);
		opticalFlowImageFormatPropertiesNVs.resize(formatCount);
		vkGetPhysicalDeviceOpticalFlowImageFormatsNV(physicalDevice, &opticalFlowImageFormatInfoNV, &formatCount, opticalFlowImageFormatPropertiesNVs.data());//假设正确返回了一个元素
		/*
		备注:
		在创建一个作为 optical flow frame的image之前，需要vkGetPhysicalDeviceFormatProperties2 以及vkGetPhysicalDeviceImageFormatProperties2 传入上述查询获得的format到 VkPhysicalDeviceImageFormatInfo2.pNext中的VkOpticalFlowImageFormatInfoNV用来查询image创建支持的参数
		*/

		VkOpticalFlowImageFormatPropertiesNV& opticalFlowImageFormatPropertiesNV = opticalFlowImageFormatPropertiesNVs[0];
		opticalFlowImageFormatPropertiesNV.sType = VK_STRUCTURE_TYPE_OPTICAL_FLOW_IMAGE_FORMAT_PROPERTIES_NV;
		opticalFlowImageFormatPropertiesNV.pNext = nullptr;
		opticalFlowImageFormatPropertiesNV.format = VK_FORMAT_R8G8_UNORM;// VkFormat 值，指明可用于指定optical flow用途的image format


	}


	//Optical Flow Session  参见p3644
	{
		VkOpticalFlowSessionNV opticalFlowSessionNV{};

		//Optical Flow Session Object 参见p3644
		{
			//创建一个optical flow session object
			VkOpticalFlowSessionCreateInfoNV opticalFlowSessionCreateInfoNV{};
			opticalFlowSessionCreateInfoNV.sType = VK_STRUCTURE_TYPE_OPTICAL_FLOW_SESSION_CREATE_INFO_NV;
			VkOpticalFlowSessionCreatePrivateDataInfoNV opticalFlowSessionCreatePrivateDataInfoNV{};//定义内部使用的数据
			{
				opticalFlowSessionCreatePrivateDataInfoNV.sType = VK_STRUCTURE_TYPE_OPTICAL_FLOW_SESSION_CREATE_PRIVATE_DATA_INFO_NV;
				opticalFlowSessionCreatePrivateDataInfoNV.pNext = nullptr;
				opticalFlowSessionCreatePrivateDataInfoNV.id = 0;//为pPrivateData 中所指的数据的一个内部的标识
				opticalFlowSessionCreatePrivateDataInfoNV.size = 0;//pPrivateData 中包含的字节数据大小
				opticalFlowSessionCreatePrivateDataInfoNV.pPrivateData = nullptr;//是一个NV internal data 的指针
			}
			opticalFlowSessionCreateInfoNV.pNext = &opticalFlowSessionCreatePrivateDataInfoNV;//可以包含一个VkOpticalFlowSessionCreatePrivateDataInfoNV
			opticalFlowSessionCreateInfoNV.width = 1;//为绑定到optical flow session的input 或者 reference frame 基于texel的width
			opticalFlowSessionCreateInfoNV.height = 1;//为绑定到optical flow session的input 或者 reference frame 基于texel的width
			opticalFlowSessionCreateInfoNV.outputGridSize = VK_OPTICAL_FLOW_GRID_SIZE_1X1_BIT_NV;/* VkOpticalFlowGridSizeFlagsNV 类型的一个比特值，指明绑定到optical flow session的output flow 以及 cost maps的grid size。output flow 以及 cost maps的大小由width，height各自除以该参数对应值决定
			Optical flow vectors的产生是按照block范围来的，每个block是NxN pixel的，称为grid
			VkOpticalFlowGridSizeFlagsNV:
			VK_OPTICAL_FLOW_GRID_SIZE_1X1_BIT_NV : 指明该grid为 1x1 pixel.
			VK_OPTICAL_FLOW_GRID_SIZE_2X2_BIT_NV : 指明该grid为 2x2 pixel.
			VK_OPTICAL_FLOW_GRID_SIZE_4X4_BIT_NV : 指明该grid为 4x4 pixel.
			VK_OPTICAL_FLOW_GRID_SIZE_8X8_BIT_NV : 指明该grid为 8x8 pixel.
			
			
			*/
			opticalFlowSessionCreateInfoNV.hintGridSize = VK_OPTICAL_FLOW_GRID_SIZE_1X1_BIT_NV;// VkOpticalFlowGridSizeFlagsNV 类型的一个比特值，指明绑定到optical flow session的hint flow vector maps的grid size。hint flow vector maps的大小由width，height各自除以该参数对应值决定
			opticalFlowSessionCreateInfoNV.performanceLevel = VK_OPTICAL_FLOW_PERFORMANCE_LEVEL_SLOW_NV;/*为用于该optical session object的 VkOpticalFlowPerformanceLevelNV值
			基于性能和质量的要求，实现暴露了用户可以控制的性能级别。
			VkOpticalFlowPerformanceLevelNV:
			VK_OPTICAL_FLOW_PERFORMANCE_LEVEL_SLOW_NV : 为一个低性能但高质量的级别。
			VK_OPTICAL_FLOW_PERFORMANCE_LEVEL_MEDIUM_NV : 为一个性能和质量都适中的级别。
			VK_OPTICAL_FLOW_PERFORMANCE_LEVEL_FAST_NV : 为一个高性能但低质量的级别。			
			*/
			opticalFlowSessionCreateInfoNV.flags = VK_OPTICAL_FLOW_SESSION_CREATE_ENABLE_HINT_BIT_NV;/*为用于该optical session object的 VkOpticalFlowSessionCreateFlagsNV值
			VkOpticalFlowSessionCreateFlagsNV:
			VK_OPTICAL_FLOW_SESSION_CREATE_ENABLE_HINT_BIT_NV : 指明带外部flow vectors的VkImageView将在进行motion search时用于作为hints，且必须绑定到VK_OPTICAL_FLOW_SESSION_BINDING_POINT_HINT_NV
			VK_OPTICAL_FLOW_SESSION_CREATE_ENABLE_COST_BIT_NV : 指明VkImageView 中forward flow的cost 必须绑定到VK_OPTICAL_FLOW_SESSION_BINDING_POINT_COST_NV，另外，如果也设置了VK_OPTICAL_FLOW_SESSION_CREATE_BOTH_DIRECTIONS_BIT_NV，
							则VkImageView 中backward flow的cost 必须绑定到VK_OPTICAL_FLOW_SESSION_BINDING_POINT_BACKWARD_COST_NV。frame的每个grid的flow vector的cost 是一个confidence level，表示该grid的flow vector的准确性。cost值越高，表示flow vector越不准确，反之亦然。
			VK_OPTICAL_FLOW_SESSION_CREATE_ENABLE_GLOBAL_FLOW_BIT_NV : 指明global flow vector 是从一个单像素VkImageView中的forward flow估计得到的，该VkImageView必须绑定到VK_OPTICAL_FLOW_SESSION_BINDING_POINT_GLOBAL_FLOW_NV。
			VK_OPTICAL_FLOW_SESSION_CREATE_ALLOW_REGIONS_BIT_NV : 指定了VkOpticalFlowExecuteInfoNV 中可以指明interest regions
			VK_OPTICAL_FLOW_SESSION_CREATE_BOTH_DIRECTIONS_BIT_NV : 指明在总是生成forward flow下额外生成backward flow。
			
			*/
			opticalFlowSessionCreateInfoNV.imageFormat = VK_FORMAT_R8_SNORM;//为绑定到optical flow session的input 或者 reference frame 的image VkFormat
			opticalFlowSessionCreateInfoNV.flowVectorFormat = VK_FORMAT_R8_SNORM;//为绑定到optical flow session的flow vector maps (output 或者 hint) 的image VkFormat
			opticalFlowSessionCreateInfoNV.costFormat = VK_FORMAT_R8_SNORM;//为绑定到optical flow session的const maps 的image VkFormat
			/*
			VkOpticalFlowSessionCreateInfoNV有效用法:
			1.width 必须大于等于VkPhysicalDeviceOpticalFlowPropertiesNV::minWidth 且小于或等于VkPhysicalDeviceOpticalFlowPropertiesNV::maxWidth
			2.height 必须大于等于VkPhysicalDeviceOpticalFlowPropertiesNV::minHeight 且小于或等于VkPhysicalDeviceOpticalFlowPropertiesNV::maxHeight
			3.imageFormat 必须为vkGetPhysicalDeviceOpticalFlowImageFormatsNV传入VK_OPTICAL_FLOW_USAGE_INPUT_BIT_NV 返回的支持的image formats之一
			4.flowVectorFormat 必须为vkGetPhysicalDeviceOpticalFlowImageFormatsNV传入VK_OPTICAL_FLOW_USAGE_OUTPUT_BIT_NV 返回的支持的image formats之一
			5.如果flags 中设置了VK_OPTICAL_FLOW_SESSION_CREATE_ENABLE_COST_BIT_NV ，则costFormat 必须为vkGetPhysicalDeviceOpticalFlowImageFormatsNV传入VK_OPTICAL_FLOW_USAGE_COST_BIT_NV 返回的支持的image formats之一
			6.outputGridSize 必须是VkPhysicalDeviceOpticalFlowPropertiesNV::supportedOutputGridSizes 中含有的一个比特设置
			7.如果flags 中设置了VK_OPTICAL_FLOW_SESSION_CREATE_ENABLE_HINT_BIT_NV ，则hintGridSize 必须是VkPhysicalDeviceOpticalFlowPropertiesNV::supportedHintGridSizes 中含有的一个比特设置
			8.如果VkPhysicalDeviceOpticalFlowPropertiesNV::hintSupported 中为VK_FALSE，则flags 中不能设置VK_OPTICAL_FLOW_SESSION_CREATE_ENABLE_HINT_BIT_NV
			9.如果VkPhysicalDeviceOpticalFlowPropertiesNV::costSupported 中为VK_FALSE，则flags 中不能设置VK_OPTICAL_FLOW_SESSION_CREATE_ENABLE_COST_BIT_NV
			10.如果VkPhysicalDeviceOpticalFlowPropertiesNV::globalFlowSupported 中为VK_FALSE，则flags 中不能设置VK_OPTICAL_FLOW_SESSION_CREATE_ENABLE_GLOBAL_FLOW_BIT_NV
			11.如果VkPhysicalDeviceOpticalFlowPropertiesNV::maxNumRegionsOfInterest 为0，则，则flags不能设置 VK_OPTICAL_FLOW_SESSION_CREATE_ALLOW_REGIONS_BIT_NV
			12.如果VkPhysicalDeviceOpticalFlowPropertiesNV::bidirectionalFlowSupported 中为VK_FALSE，则flags 中不能设置VK_OPTICAL_FLOW_SESSION_CREATE_BOTH_DIRECTIONS_BIT_NV
			*/


			vkCreateOpticalFlowSessionNV(device, &opticalFlowSessionCreateInfoNV, nullptr, &opticalFlowSessionNV);

			//销毁一个 Optical Flow Session 参见p3651
			vkDestroyOpticalFlowSessionNV(device, opticalFlowSessionNV, nullptr);
		}


		//Binding Vulkan Image Views to an Optical Flow Session  参见p3651
		{
			VkOpticalFlowSessionBindingPointNV opticalFlowSessionBindingPointNV = VK_OPTICAL_FLOW_SESSION_BINDING_POINT_INPUT_NV;// VkOpticalFlowSessionBindingPointNV 值，指明将要绑定的image view的用途
			/*
			VkOpticalFlowSessionBindingPointNV:
			VK_OPTICAL_FLOW_SESSION_BINDING_POINT_INPUT_NV : 指定input frame的绑定点
			VK_OPTICAL_FLOW_SESSION_BINDING_POINT_REFERENCE_NV : 指定input reference frame 的绑定点.
			VK_OPTICAL_FLOW_SESSION_BINDING_POINT_HINT_NV : 指定作为 optional external hint flow vectors.
			VK_OPTICAL_FLOW_SESSION_BINDING_POINT_FLOW_VECTOR_NV : 指定默认forward flow计算的output flow vectors的绑定点.
			VK_OPTICAL_FLOW_SESSION_BINDING_POINT_BACKWARD_FLOW_VECTOR_NV : 指定optional backward flow计算的optional output flow vector map 的绑定点
			VK_OPTICAL_FLOW_SESSION_BINDING_POINT_COST_NV : 指定默认forward flow计算的optional output cost map 的绑定点.
			VK_OPTICAL_FLOW_SESSION_BINDING_POINT_BACKWARD_COST_NV : 指定optional backward flow计算的optional output cost map 的绑定点.
			VK_OPTICAL_FLOW_SESSION_BINDING_POINT_GLOBAL_FLOW_NV : 指定默认forward flow计算的optional global flow value 的绑定点.

			*/
			
			vkBindOpticalFlowSessionImageNV(device, opticalFlowSessionNV, opticalFlowSessionBindingPointNV, VkImageView{/*假设这是一个有效的VkImageView*/ }, VK_IMAGE_LAYOUT_GENERAL);
		}



		//Optical Flow Execution  参见p3653
		{
			/*
			flow估计的默认方向是正向的，它计算了从输入帧到参考帧的光流。可选择另外计算反向flow估计。输出流向量（Vx、Vy）是指可以在参考帧的位置（x+Vx、y+Vy）处找到输入帧的当前像素(x、y）。后向流向量（Vx、Vy）表示在输入帧的位置（x+Vx，y+Vy）可以找到参考帧的当前像素（x，y）。
			简单将就是计算同一像素在不同帧之间的像素位置以及位移向量等信息。
			*/

			//计算两个input frame之间的optical flow vectors
			VkOpticalFlowExecuteInfoNV opticalFlowExecuteInfoNV{};
			opticalFlowExecuteInfoNV.sType = VK_STRUCTURE_TYPE_OPTICAL_FLOW_EXECUTE_INFO_NV;
			opticalFlowExecuteInfoNV.pNext = nullptr;
			opticalFlowExecuteInfoNV.flags = VK_OPTICAL_FLOW_EXECUTE_DISABLE_TEMPORAL_HINTS_BIT_NV;/*为该命令使用的 VkOpticalFlowExecuteFlagsNV 
			VkOpticalFlowExecuteFlagBitsNV:
			VK_OPTICAL_FLOW_EXECUTE_DISABLE_TEMPORAL_HINTS_BIT_NV : 指明之前flow vectors生成的temporal hints 不再使用。如果temporal hints 开启，则vkCmdOpticalFlowExecuteNV命令会自动使用之前的optical flow vectors作为hints，以利用视频序列中的时序相关性。如果之前的flow vectors没有时序相关性，则temporal hints应该关闭。	
			*/
			opticalFlowExecuteInfoNV.regionCount = 1;// pRegions 中元素个数，如果VkOpticalFlowSessionNV 创建时没有指定 VK_OPTICAL_FLOW_SESSION_CREATE_ALLOW_REGIONS_BIT_NV，则必须为0
			VkRect2D region{ .offset = VkOffset2D{.x = 0,.y = 0},.extent = VkExtent2D{.width = 1,.height = 1} };
			opticalFlowExecuteInfoNV.pRegions = &region;// pRegions 是一个 VkRect2D 数组指针，用于指定感兴趣区域



			vkCmdOpticalFlowExecuteNV(VkCommandBuffer{/*假设这是一个有效的VkCommandBuffer*/ }, opticalFlowSessionNV, & opticalFlowExecuteInfoNV);



		}
	}

}

void OpticalFlowAndExcutionGraphsAndLowLatencyTest::ExecutionGraphsTest()
{
	/*
	execution graphs提供了一种方法可以在host端的一个命令上发射多条操作。为了支持这一行为，实现提供了一种新的graph pipeline，该pipeline将多个pipeline 或者sheder链接起来，其中每个pipeline或者shader 描述了一个或多个操作。这些pipeline或者shader称为graph execution node，可以被其他shader动态调用执行。
	
	*/

	VkPipeline graphPipeline{};

	//Pipeline Creation  参见p3657
	{
		struct ExecutionGraphPipelineCreateInfoAMDXEXT {
			VkPipelineCompilerControlCreateInfoAMD pipelineCompilerControlCreateInfoAMD{};
			VkPipelineCreationFeedbackCreateInfo pipelineCreationFeedbackCreateInfo{};
			ExecutionGraphPipelineCreateInfoAMDXEXT() {
				Init();
			}
			void Init() {
				pipelineCompilerControlCreateInfoAMD.sType = VK_STRUCTURE_TYPE_PIPELINE_COMPILER_CONTROL_CREATE_INFO_AMD;
				pipelineCompilerControlCreateInfoAMD.pNext = nullptr;
				pipelineCreationFeedbackCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_CREATION_FEEDBACK_CREATE_INFO;
				pipelineCreationFeedbackCreateInfo.pNext = nullptr;

			}
		};


		VkExecutionGraphPipelineCreateInfoAMDX executionGraphPipelineCreateInfoAMDX{};
		executionGraphPipelineCreateInfoAMDX.sType = VK_STRUCTURE_TYPE_MAX_ENUM;//没有定义这里设置为非法值
		executionGraphPipelineCreateInfoAMDX.pNext = nullptr;
		executionGraphPipelineCreateInfoAMDX.flags = VK_PIPELINE_CREATE_DISABLE_OPTIMIZATION_BIT;// VkPipelineCreateFlagBits 组合值位掩码，指明pipeline如何产生
		executionGraphPipelineCreateInfoAMDX.stageCount = 1;//pStages 中元素个数

		VkPipelineShaderStageCreateInfo pipelineShaderStageCreateInfo{/*假设这是一个有效的VkPipelineShaderStageCreateInfo*/ };//pNext中可以包含VkPipelineShaderStageNodeCreateInfoAMDX 指明该node的索引以及名称
		{
			pipelineShaderStageCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
			VkPipelineShaderStageNodeCreateInfoAMDX pipelineShaderStageNodeCreateInfoAMDX{};
			{
				pipelineShaderStageNodeCreateInfoAMDX.sType = VK_STRUCTURE_TYPE_MAX_ENUM;//没有定义这里定义为非法值
				pipelineShaderStageNodeCreateInfoAMDX.pNext = nullptr;
				pipelineShaderStageNodeCreateInfoAMDX.index = 0;//为创建execution graph 的node时shader 使用的索引，如果为VK_SHADER_INDEX_UNUSED_AMDX 则该shader使用原始索引（ShaderIndexAMDX execution mode指定或者为0）
				pipelineShaderStageNodeCreateInfoAMDX.pName = "name";//为创建execution graph 的node时shader 使用的名字。如果为NULL，则使用 SPIR-V声明的入口点entry point名称

			}
			pipelineShaderStageCreateInfo.pNext = &pipelineShaderStageNodeCreateInfoAMDX;

		}
		executionGraphPipelineCreateInfoAMDX.pStages = &pipelineShaderStageCreateInfo;//一个VkPipelineShaderStageCreateInfo 数组指针，描述包含在该 execution graph pipeline中的shader stage
		VkPipelineLibraryCreateInfoKHR pipelineLibraryCreateInfoKHR{/*假设这是一个有效的VkPipelineLibraryCreateInfoKHR*/ };//一个 VkPipelineLibraryCreateInfoKHR 指定，定义包含的pipeline libraries
		executionGraphPipelineCreateInfoAMDX.pLibraryInfo = &pipelineLibraryCreateInfoKHR;
		executionGraphPipelineCreateInfoAMDX.layout = VkPipelineLayout{/*假设这是一个有效的VkPipelineLayout*/ };//为VkPipelineLayout句柄，描述同时用于pipeline以及descriptor sets的绑定点信息
		executionGraphPipelineCreateInfoAMDX.basePipelineHandle = VkPipeline{/*假设这是一个有效的VkPipeline*/ };//VkPipeline 句柄，指明从哪个pipeline上派生
		executionGraphPipelineCreateInfoAMDX.basePipelineIndex = 0;////一个 pCreateInfos中元素的索引，指明从哪个pipeline上派生
		/*
		VkExecutionGraphPipelineCreateInfoAMDX有效用法:
		1.如果pNext中不包含VkPipelineCreateFlags2CreateInfoKHR在，则flags必须是一个有效的VkPipelineCreateFlagBits组合值
		2.如果flags 包含VK_PIPELINE_CREATE_DERIVATIVE_BIT，（1）如果basePipelineIndex为-1，则basePipelineHandle 必须是一个有效的execution graph VkPipeline 句柄
														   （2）如果basePipelineHandle为VK_NULL_HANDLE，则basePipelineIndex 必须是一个有效的pCreateInfos 中元素的索引
														   （3）basePipelineIndex 必须为-1 或者basePipelineHandle 必须为VK_NULL_HANDLE，必须满足一个
		3.如果shader中声明了push constant block，则layout中的push constant range 必须同时满足shader stage以及 range
		4.如果shader中声明了resource variables，（1）layout中的descriptor slot 必须匹配shader stage
												（2）如果该descriptor 类型不为VK_DESCRIPTOR_TYPE_MUTABLE_EXT，则layout中的descriptor slot 必须匹配descriptor 类型
		5.如果shader中声明了resource variables为array，layout中的descriptor slot 必须匹配descriptor count
		6.flags不能包含VK_PIPELINE_CREATE_RAY_TRACING_NO_NULL_ANY_HIT_SHADERS_BIT_KHR， VK_PIPELINE_CREATE_RAY_TRACING_NO_NULL_CLOSEST_HIT_SHADERS_BIT_KHR，
								VK_PIPELINE_CREATE_RAY_TRACING_NO_NULL_MISS_SHADERS_BIT_KHR，VK_PIPELINE_CREATE_RAY_TRACING_NO_NULL_INTERSECTION_SHADERS_BIT_KHR，
								VK_PIPELINE_CREATE_RAY_TRACING_SKIP_TRIANGLES_BIT_KHR，VK_PIPELINE_CREATE_RAY_TRACING_SKIP_AABBS_BIT_KHR，
								VK_PIPELINE_CREATE_RAY_TRACING_SHADER_GROUP_HANDLE_CAPTURE_REPLAY_BIT_KHR 以及VK_PIPELINE_CREATE_RAY_TRACING_ALLOW_MOTION_BIT_NV
		7.如果VkPhysicalDeviceDeviceGeneratedCommandsComputeFeaturesNV::deviceGeneratedComputePipelines未开启，则flags 不能包含VK_PIPELINE_CREATE_INDIRECT_BINDABLE_BIT_NV
		8.如果flags包含VK_PIPELINE_CREATE_INDIRECT_BINDABLE_BIT_NV，则pNext中必须包含一个VkComputePipelineIndirectBufferInfoNV，指明该pipeline的metadata保存所在地址
		9.如果pipelineCreationCacheControl 特性未开启，则flags不能包含VK_PIPELINE_CREATE_FAIL_ON_PIPELINE_COMPILE_REQUIRED_BIT 或者VK_PIPELINE_CREATE_EARLY_RETURN_ON_FAILURE_BIT
		10.pStages 中的任何元素的stage必须为VK_SHADER_STAGE_COMPUTE_BIT
		11.pStages 中元素对应的shader code必须符合pipeline 链接规则，见p1394 Shader Interfaces
		12.layout 必须和pStages 中shader的layout一致
		13.如果pLibraryInfo 不为NULL，则pLibraries中的每个元素必须以一个和该pipeline的layout兼容的布局创建
		14.该pipeline中每个shader stage可访问的layout的资源数量必须小于等于VkPhysicalDeviceLimits::maxPerStageResources
		15.如果pLibraryInfo 不为NULL，pLibraryInfo->libraries中每个元素必须为compute pipeline或者execution graph pipeline
		16.pipeline中不能有两个shader共享相同的名称以及索引，见VkPipelineShaderStageNodeCreateInfoAMDX中指定的参数
		17.pipeline中不能有两个shader共享相同的名称且含不同大小的input payload声明
		18.pipeline中不能有两个shader共享相同的名称但含不同的execution models
		19.pipeline中不能有两个shader共享相同的名称且其中一个包含CoalescedInputCountAMDX但另外一个不包含
		20.pipeline中不能有两个shader共享相同的名称且其中一个包含StaticNumWorkgroupsAMDX但另外一个不包含
		21.如果pipeline中任何shader声明的 output payload 含有一个Node Name和graph pipeline中其他node的shader 名字匹配的PayloadNodeNameAMDX，则output payload的大小必须必须匹配那个匹配node的input payload的大小
		*/



		//创建execution graph pipelines
		vkCreateExecutionGraphPipelinesAMDX(device, VkPipelineCache{/*假设这是一个有效的VkPipelineCache*/ }, 1, & executionGraphPipelineCreateInfoAMDX, nullptr, & graphPipeline);
		/*
		vkCreateExecutionGraphPipelinesAMDX有效用法:
		1.shaderEnqueue 特性必须开启
		2.如果pCreateInfos中元素的flags 包含VK_PIPELINE_CREATE_DERIVATIVE_BIT，则（1）该元素的basePipelineIndex不为-1，则该元素的basePipelineIndex必须小于该元素在pCreateInfos中的索引
																				 （2）则该元素的basePipelineHandle所对的base pipeline 必须以VK_PIPELINE_CREATE_ALLOW_DERIVATIVES_BIT 创建
		3.如果pipelineCache 以VK_PIPELINE_CACHE_CREATE_EXTERNALLY_SYNCHRONIZED_BIT 创建，host端对pipelineCache的访问必须是外部同步的

		*/



		//一个node的名字在创建时候就固定了，但其索引是动态的，且execution graph中一个名字可以对应多个索引，只需要保证在graph中名字和索引参数对（对应一个内部索引）是唯一就可以
		//查询graph中指定node的内部索引
		uint32_t nodeIndex = 0;
		::VkPipelineShaderStageNodeCreateInfoAMDX pipelineShaderStageNodeCreateInfoAMDX{};
		pipelineShaderStageNodeCreateInfoAMDX.sType = VK_STRUCTURE_TYPE_MAX_ENUM;
		pipelineShaderStageNodeCreateInfoAMDX.pNext = nullptr;
		pipelineShaderStageNodeCreateInfoAMDX.pName = "queryName";
		pipelineShaderStageNodeCreateInfoAMDX.index = 0;

		vkGetExecutionGraphPipelineNodeIndexAMDX(device, graphPipeline, &pipelineShaderStageNodeCreateInfoAMDX, &nodeIndex/*pNodeIndex，返回查询的索引*/);
		/*
		vkGetExecutionGraphPipelineNodeIndexAMDX有效用法:
		1.pNodeInfo->pName 不能为NULL
		2.pNodeInfo->index 不能为VK_SHADER_INDEX_UNUSED_AMDX
		3.executionGraph 中必须有一个名字匹配pNodeInfo->pName，索引匹配pNodeInfo->index的node
		*/

	}

	VkCommandBuffer commandBuffer{/*假设这是一个有效的VkCommandBuffer*/ };

	//Initializing Scratch Memory  参见p3665
	{
		//实现需要scratch memory 来管理 dispatch queues

		//查询派发一个 execution graph 需要的 scratch space
		VkExecutionGraphPipelineScratchSizeAMDX executionGraphPipelineScratchSizeAMDX{};
		executionGraphPipelineScratchSizeAMDX.size = VK_STRUCTURE_TYPE_MAX_ENUM;//没有定义这里设置为非法值
		executionGraphPipelineScratchSizeAMDX.pNext = nullptr;
		executionGraphPipelineScratchSizeAMDX.size = 0;//指明派发一个 execution graph 需要的 scratch space大小

		vkGetExecutionGraphPipelineScratchSizeAMDX(device, graphPipeline, &executionGraphPipelineScratchSizeAMDX);



		//初始化指定 execution graph的scratch memory ,scratch 必须在 vkCmdDispatchGraphAMDX, vkCmdDispatchGraphIndirectAMDX, vkCmdDispatchGraphIndirectCountAMDX,或者 vkCmdInitializeGraphScratchMemoryAMDX 调用前重新初始化
		vkCmdInitializeGraphScratchMemoryAMDX(commandBuffer, VkDeviceAddress{/*假设这是一个有效的VkDeviceAddress*/ }/*scratch, 指明要初始化的scratch的内存地址*/);
		/*
		vkCmdInitializeGraphScratchMemoryAMDX有效用法:
		1.scratch 必须是一个大小至少为调用VkExecutionGraphPipelineScratchSizeAMDX传入绑定的execution graph返回的VkExecutionGraphPipelineScratchSizeAMDX::size的内存地址
		2.scratch 必须是64的倍数
		*/
		

	}

	//Dispatching a Graph  参见p3668
	{
		VkDeviceAddress scratch{/*假设这是一个有效的VkDeviceAddress*/ };

		//记录派发一个 execution graph   ,scratch在VK_PIPELINE_STAGE_2_COMPUTE_SHADER_BIT pipeline stage同步，以VK_ACCESS_2_SHADER_STORAGE_READ_BIT 以及 VK_ACCESS_2_SHADER_STORAGE_WRITE_BIT进行访问
		VkDispatchGraphCountInfoAMDX dispatchGraphCountInfoAMDX{};
		dispatchGraphCountInfoAMDX.count = 1;//指明infos中 VkDispatchGraphInfoAMDX 的个数
		dispatchGraphCountInfoAMDX.stride = 64;//指明infos中连续 VkDispatchGraphInfoAMDX 之前的字节步长
		VkDispatchGraphInfoAMDX dispatchGraphInfoAMDX{};
		{
			dispatchGraphInfoAMDX.nodeIndex = 0;//为execution graph中派发的node的索引
			dispatchGraphInfoAMDX.payloadCount = 1;//为指定node派发的payloads的数量，必须小于maxExecutionGraphShaderPayloadCount
			dispatchGraphInfoAMDX.payloads = VkDeviceOrHostAddressConstAMDX{/* .deviceAddress = 0,为调用 vkGetBufferDeviceAddressKHR返回的一个地址 */.hostAddress = 0 /*为host端的地址*/ };//为大小为payloadCount * payloadStride的device或者host端地址，包含payloads数组数据
			dispatchGraphInfoAMDX.payloadStride = 64;//为 payloads中连续payload之间的字节步长
		}
		dispatchGraphCountInfoAMDX.infos = VkDeviceOrHostAddressConstAMDX{/* .deviceAddress = 0,为调用 vkGetBufferDeviceAddressKHR返回的一个地址 */.hostAddress = 0 /*为host端的地址*/ };//为包含 VkDispatchGraphInfoAMDX 数组的device或者host端地址

		vkCmdDispatchGraphAMDX(commandBuffer, scratch, &dispatchGraphCountInfoAMDX);
		/*
		vkCmdDispatchGraphAMDX有效用法:
		1.如果一个VkSampler以其magFilter或者minFilter等于VK_FILTER_LINEAR创建，则（1）如果reductionMode为VK_SAMPLER_REDUCTION_MODE_WEIGHTED_AVERAGE，如果用于采样一个VkImageView作为该命令的结果的compareEnable为VK_FALSE，则该image view的format features必须包含VK_FORMAT_FEATURE_SAMPLED_IMAGE_FILTER_LINEAR_BIT
																				 （2）如果reductionMode为VK_SAMPLER_REDUCTION_MODE_MIN 或者VK_SAMPLER_REDUCTION_MODE_MAX之一 用于采样一个VkImageView作为该命令的结果，则该image view的format features必须包含VK_FORMAT_FEATURE_SAMPLED_IMAGE_FILTER_MINMAX_BIT
		2.如果一个VkSampler以其mipmapMode 等于VK_SAMPLER_MIPMAP_MODE_LINEAR创建，则（1）如果reductionMode为VK_SAMPLER_REDUCTION_MODE_WEIGHTED_AVERAGE，如果用于采样一个VkImageView作为该命令的结果的compareEnable为VK_FALSE，则该image view的format features必须包含VK_FORMAT_FEATURE_SAMPLED_IMAGE_FILTER_LINEAR_BIT
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
		23.如果通过vkCmdBindDescriptorSets指定绑定到pipeline bind point的VkPipeline要使用的descriptors，则绑定的VkPipeline不能以VK_PIPELINE_CREATE_DESCRIPTOR_BUFFER_BIT_EXT创建
		24.在vkCmdSetDescriptorBufferOffsetsEXT中指定绑定的descriptor buffers的descriptors，则（1）如果绑定到pipeline bind point的该命令会使用的VkPipeline以VK_PIPELINE_CREATE_DESCRIPTOR_BUFFER_BIT_EXT创建，且这些descriptors是动态使用的，则这些descriptors必须是有效的
																							  （2）如果绑定到pipeline bind point的对应stage的该命令会使用的VkShaderEXT，且这些descriptors是动态使用的，则这些descriptors必须是有效的
		25.在vkCmdSetDescriptorBufferOffsetsEXT中指定的descriptors在绑定到pipeline bind point的VkPipeline中使用，则VkPipeline必须以VK_PIPELINE_CREATE_DESCRIPTOR_BUFFER_BIT_EXT创建
		26.如果一个descriptor在以VK_PIPELINE_CREATE_DESCRIPTOR_BUFFER_BIT_EXT创建的VkPipeline中动态使用，则descriptor memory必须是驻留内存
		27.如果一个descriptor在以其VkDescriptorSetLayout以VK_DESCRIPTOR_SET_LAYOUT_CREATE_DESCRIPTOR_BUFFER_BIT_EXT创建的VkShaderEXT中动态使用，则descriptor memory必须是驻留内存
		28.如果shaderObject 特性没有开启，一个有效的pipeline必须绑定到这个命令使用的绑定到pipeline bind point上
		29.如果一个pipeline绑定到该命令使用的pipeline bind point上，则不能有任何动态state 设置命令设置任何该VkPipeline 中没有指定的动态 state
		30.如果一个VkPipeline绑定到该命令使用的pipeline bind point上 或者任何一个会访问一个使用unnormalized coordinates的VkSampler的 VkShaderEXT绑定到该命令使用的pipeline bind point上的pipeline的对应stage，则
																					（1）在任何shader stage中，VkSampler不能用来采样任何类型为VK_IMAGE_VIEW_TYPE_3D, VK_IMAGE_VIEW_TYPE_CUBE, VK_IMAGE_VIEW_TYPE_1D_ARRAY, VK_IMAGE_VIEW_TYPE_2D_ARRAY 或者 VK_IMAGE_VIEW_TYPE_CUBE_ARRAY的VkImageView
																					（2）在任何shader stage中，该VkSampler不能和任何带有名字中带有ImplicitLod，Dref 或者 Proj 的SPIR-V OpImageSample* 或者 OpImageSparseSample*指令一起使用
																					（3）在任何shader stage中，该VkSampler不能和任何包含 LOD bias或者offset 值 的SPIR-V OpImageSample* or OpImageSparseSample*指令一起使用
		31.如果shaderObject开启，一个有效的pipeline必须绑定到该命令使用的pipeline bind point上或者一个有效的shader objects以及VK_NULL_HANDLE的组合必须绑定到该命令使用的pipeline bind point每一个支持的shader stage上
		32.如何绑定到该命令使用的pipeline bind point上的VkPipeline的任何stage会访问一个uniform buffer，且该stage对uniformBuffers不以启用VK_PIPELINE_ROBUSTNESS_BUFFER_BEHAVIOR_ROBUST_BUFFER_ACCESS_EXT或者VK_PIPELINE_ROBUSTNESS_BUFFER_BEHAVIOR_ROBUST_BUFFER_ACCESS_2_EXT 创建，且robustBufferAccess特性未开启，则该stage就不能访问绑定到相同pipeline bind point的descriptor set指定的buffer范围外的值
		33.如果robustBufferAccess特性未开启，且任何会访问uniform buffer的绑定到该命令使用的pipeline bind point上对应shader stage的VkShaderEXT，则其不能访问绑定到相同pipeline bind point的descriptor set指定的buffer范围外的值
		34.如何绑定到该命令使用的pipeline bind point上的VkPipeline的任何stage会访问一个storage buffer，且该stage对storageBuffers不以启用VK_PIPELINE_ROBUSTNESS_BUFFER_BEHAVIOR_ROBUST_BUFFER_ACCESS_EXT或者VK_PIPELINE_ROBUSTNESS_BUFFER_BEHAVIOR_ROBUST_BUFFER_ACCESS_2_EXT 创建，且robustBufferAccess特性未开启，则该stage就不能访问绑定到相同pipeline bind point的descriptor set指定的buffer范围外的值
		35.如果robustBufferAccess特性未开启，且任何会访问storage buffer的绑定到该命令使用的pipeline bind point上对应shader stage的VkShaderEXT，则其不能访问绑定到相同pipeline bind point的descriptor set指定的buffer范围外的值
		36.如果commandBuffer 是一个unprotected command buffer，且protectedNoFault 未支持，则任何绑定的shaders访问的资源不能是一个protected resource
		37.如果一个绑定的shader访问一个VkSampler 或者 VkImageView ，且启用了sampler Y′C BCR conversion，则只能使用OpImageSample* 或者 OpImageSparseSample*指令，不能使用ConstOffset 以及 Offset操作符
		38.如果一个VkImageView作为该命令的结果进行访问，则（1）image view 的viewType 必须匹配Instruction/Sampler/Image View Validation p1481中描述的OpTypeImage的Dim操作符
														  （2）image view 的foamrt的numeric type 必须匹配OpTypeImage的Sampled Type操作符
		39.如果一个VkImageView以一个不是VK_FORMAT_A8_UNORM_KHR的format创建且通过OpImageWrite作为该命令的结果进行访问，则该命令的Texel 操作符的Type必须至少包含和 image view的 format含有的components的个数相同的components个数
		40.如果一个VkImageView以VK_FORMAT_A8_UNORM_KHR的format创建且通过OpImageWrite作为该命令的结果进行访问，则该命令的Texel 操作符的Type必须包含4个components
		41.如果一个VkBufferView通过OpImageWrite作为该命令的结果进行访问，则该命令的Texel 操作符的Type必须至少包含和 buffer view的 format含有的components的个数相同的components个数
		42.如果一个带64-bit component的VkFormat的VkImageView作为该命令的结果进行访问，则该命令的OpTypeImage操作符的SampledType的宽度必须为64
		43.如果一个带少于64-bit component的VkFormat的VkImageView作为该命令的结果进行访问，则该命令的OpTypeImage操作符的SampledType的宽度必须为32
		44.如果一个带64-bit component的VkFormat的VkBufferView作为该命令的结果进行访问，则该命令的OpTypeImage操作符的SampledType的宽度必须为64位
		45.如果一个带少于64-bit component的VkFormat的VkBufferView作为该命令的结果进行访问，则该命令的OpTypeImage操作符的SampledType的宽度必须为32
		46.如果sparseImageInt64Atomics 特性未开启，则以VK_IMAGE_CREATE_SPARSE_RESIDENCY_BIT创建的VkImage对象不能被SampledType宽度为64位的OpTypeImage的atomic instructions访问
		47.如果sparseImageInt64Atomics 特性未开启，则以VK_BUFFER_CREATE_SPARSE_RESIDENCY_BIT创建的VkBuffer对象不能被SampledType宽度为64位的OpTypeImage的atomic instructions访问
		48.如果OpImageWeightedSampleQCOM用来采样一个作为该命令的结果的VkImageView，则该image view的format features必须包含VK_FORMAT_FEATURE_2_WEIGHT_SAMPLED_IMAGE_BIT_QCOM
		49.如果OpImageWeightedSampleQCOM用来采样一个作为该命令的结果的sample weight image的VkImageView，则该image view的format features必须包含VK_FORMAT_FEATURE_2_WEIGHT_IMAGE_BIT_QCOM
		50.如果OpImageBoxFilterQCOM用来采样一个作为该命令的结果的VkImageView，则该image view的format features必须包含VK_FORMAT_FEATURE_2_BOX_FILTER_SAMPLED_BIT_QCOM
		51.如果OpImageBlockMatchSSDQCOM，或者 OpImageBlockMatchSADQCOM用来读取一个作为该命令的结果的VkImageView，则（1）该image view的format features必须包含VK_FORMAT_FEATURE_2_BLOCK_MATCHING_BIT_QCOM
																												   （2）如果是读取的reference image，指定的reference coordinates不能在integer texel coordinate validation 时候失败
		52.如果OpImageWeightedSampleQCOM, OpImageBoxFilterQCOM, OpImageBlockMatchWindowSSDQCOM, OpImageBlockMatchWindowSADQCOM, OpImageBlockMatchGatherSSDQCOM,
													OpImageBlockMatchGatherSADQCOM, OpImageBlockMatchSSDQCOM, 或者 OpImageBlockMatchSADQCOM用来采样一个作为该命令的结果的VkImageView，则该VkSampler必须以VK_SAMPLER_CREATE_IMAGE_PROCESSING_BIT_QCOM创建
		53.如果任何除了OpImageWeightedSampleQCOM, OpImageBoxFilterQCOM, OpImageBlockMatchWindowSSDQCOM, OpImageBlockMatchWindowSADQCOM, OpImageBlockMatchGatherSSDQCOM, OpImageBlockMatchGatherSADQCOM, OpImageBlockMatchSSDQCOM, 或者 OpImageBlockMatchSADQCOM之外的指令使用VkSampler进行采样作为该命令的结果，则该sampler不能以VK_SAMPLER_CREATE_IMAGE_PROCESSING_BIT_QCOM 创建
		54.如果OpImageBlockMatchWindow*QCOM or OpImageBlockMatchGather*QCOM指令用来读取VkImageView作为该命令的结果，则（1）VkImageView的format features必须包含VK_FORMAT_FEATURE_2_BLOCK_MATCHING_BIT_QCOM
																													  （2）VkImageView的format必须只含有一个component
		55.如果OpImageBlockMatchWindow*QCOM or OpImageBlockMatchGather*QCOM指令用来读取一个引用的image作为该命令的结果，则指定的 reference coordinates不能在integer texel coordinate validation 时候失败
		56.任何该命令执行的shader invocation必须已经终止
		57.如果有一个类型位为VK_DESCRIPTOR_TYPE_SAMPLE_WEIGHT_IMAGE_QCOM, VK_DESCRIPTOR_TYPE_BLOCK_MATCH_IMAGE_QCOM, VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE, VK_DESCRIPTOR_TYPE_STORAGE_IMAGE, 或者 VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT中任意一个的descriptor作为该命令的结果进行访问，则该descriptor所指的image subresource的layout必须和该descriptor被写入时的layout相同。
		
		58.commandBuffer 不能为一个protected command buffer，必须为一个primary command buffer
		59.scratch 必须是大小至少为调用VkExecutionGraphPipelineScratchSizeAMDX传入绑定的 execution graph返回的VkExecutionGraphPipelineScratchSizeAMDX::size的内存地址
		60.scratch 必须是以VK_BUFFER_USAGE_EXECUTION_GRAPH_SCRATCH_BIT_AMDX 或者VK_BUFFER_USAGE_2_EXECUTION_GRAPH_SCRATCH_BIT_AMDX创建的VkBuffer的设备地址
		61.[scratch,scratch + VkExecutionGraphPipelineScratchSizeAMDX::size) 内的内存必须已经使用当前绑定的execution graph调用vkCmdInitializeGraphScratchMemoryAMDX进行初始化了，且不能被其他execution graph的dispatch command 更改
		62.该命令的执行不能导致一个node以一个workgroups的最大数量（由node中的MaxNumWorkgroupsAMDX 或者maxComputeWorkGroupCount 指定）被派发
		63.该命令的执行不能导致任何shader初始化超过maxExecutionGraphShaderPayloadCount个 output payloads
		64.该命令的执行不能导致任何声明了NodeMaxPayloadsAMDX的 shader初始化超过该声明指定的payloads的最大数量。该需求会应用到每个NodeMaxPayloadsAMDX 声明。
		65.pCountInfo->infos 必须是一个host指针，指向一个大小至少为count * stride 的内存
		66.[infos, infos + (count*stride)) 中的地址以stride为粒度，每个粒度中前24字节必须包含有效的VkDispatchGraphInfoAMDX 
		67.对pCountInfo->infos中的每个VkDispatchGraphInfoAMDX，（1）其payloads必须是一个host端的指针，指向大小至少为 payloadCount * payloadStride的内存地址
															   （2）其nodeIndex 必须是一个在当前调用vkGetExecutionGraphPipelineNodeIndexAMDX传入绑定的execution graph pipeline中返回的有效的node 索引
															   （3）其指向的host地址范围[payloads, payloads + (payloadCount * payloadStride))，以payloadStride 为粒度，该粒度中最开始的字节必须包含一个payload，该payload的大小匹配nodeIndex所指的node期望的input payload的大小

		*/


		//记录派发一个 execution graph,其中node以及payload参数从device中读取   ,scratch在VK_PIPELINE_STAGE_2_COMPUTE_SHADER_BIT pipeline stage同步，以VK_ACCESS_2_SHADER_STORAGE_READ_BIT 以及 VK_ACCESS_2_SHADER_STORAGE_WRITE_BIT进行访问
		vkCmdDispatchGraphIndirectAMDX(commandBuffer, scratch, &dispatchGraphCountInfoAMDX);
		/*
		vkCmdDispatchGraphIndirectAMDX有效用法:
		1.如果一个VkSampler以其magFilter或者minFilter等于VK_FILTER_LINEAR创建，则（1）如果reductionMode为VK_SAMPLER_REDUCTION_MODE_WEIGHTED_AVERAGE，如果用于采样一个VkImageView作为该命令的结果的compareEnable为VK_FALSE，则该image view的format features必须包含VK_FORMAT_FEATURE_SAMPLED_IMAGE_FILTER_LINEAR_BIT
																				 （2）如果reductionMode为VK_SAMPLER_REDUCTION_MODE_MIN 或者VK_SAMPLER_REDUCTION_MODE_MAX之一 用于采样一个VkImageView作为该命令的结果，则该image view的format features必须包含VK_FORMAT_FEATURE_SAMPLED_IMAGE_FILTER_MINMAX_BIT
		2.如果一个VkSampler以其mipmapMode 等于VK_SAMPLER_MIPMAP_MODE_LINEAR创建，则（1）如果reductionMode为VK_SAMPLER_REDUCTION_MODE_WEIGHTED_AVERAGE，如果用于采样一个VkImageView作为该命令的结果的compareEnable为VK_FALSE，则该image view的format features必须包含VK_FORMAT_FEATURE_SAMPLED_IMAGE_FILTER_LINEAR_BIT
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
		23.如果通过vkCmdBindDescriptorSets指定绑定到pipeline bind point的VkPipeline要使用的descriptors，则绑定的VkPipeline不能以VK_PIPELINE_CREATE_DESCRIPTOR_BUFFER_BIT_EXT创建
		24.在vkCmdSetDescriptorBufferOffsetsEXT中指定绑定的descriptor buffers的descriptors，则（1）如果绑定到pipeline bind point的该命令会使用的VkPipeline以VK_PIPELINE_CREATE_DESCRIPTOR_BUFFER_BIT_EXT创建，且这些descriptors是动态使用的，则这些descriptors必须是有效的
																							  （2）如果绑定到pipeline bind point的对应stage的该命令会使用的VkShaderEXT，且这些descriptors是动态使用的，则这些descriptors必须是有效的
		25.在vkCmdSetDescriptorBufferOffsetsEXT中指定的descriptors在绑定到pipeline bind point的VkPipeline中使用，则VkPipeline必须以VK_PIPELINE_CREATE_DESCRIPTOR_BUFFER_BIT_EXT创建
		26.如果一个descriptor在以VK_PIPELINE_CREATE_DESCRIPTOR_BUFFER_BIT_EXT创建的VkPipeline中动态使用，则descriptor memory必须是驻留内存
		27.如果一个descriptor在以其VkDescriptorSetLayout以VK_DESCRIPTOR_SET_LAYOUT_CREATE_DESCRIPTOR_BUFFER_BIT_EXT创建的VkShaderEXT中动态使用，则descriptor memory必须是驻留内存
		28.如果shaderObject 特性没有开启，一个有效的pipeline必须绑定到这个命令使用的绑定到pipeline bind point上
		29.如果一个pipeline绑定到该命令使用的pipeline bind point上，则不能有任何动态state 设置命令设置任何该VkPipeline 中没有指定的动态 state
		30.如果一个VkPipeline绑定到该命令使用的pipeline bind point上 或者任何一个会访问一个使用unnormalized coordinates的VkSampler的 VkShaderEXT绑定到该命令使用的pipeline bind point上的pipeline的对应stage，则
																					（1）在任何shader stage中，VkSampler不能用来采样任何类型为VK_IMAGE_VIEW_TYPE_3D, VK_IMAGE_VIEW_TYPE_CUBE, VK_IMAGE_VIEW_TYPE_1D_ARRAY, VK_IMAGE_VIEW_TYPE_2D_ARRAY 或者 VK_IMAGE_VIEW_TYPE_CUBE_ARRAY的VkImageView
																					（2）在任何shader stage中，该VkSampler不能和任何带有名字中带有ImplicitLod，Dref 或者 Proj 的SPIR-V OpImageSample* 或者 OpImageSparseSample*指令一起使用
																					（3）在任何shader stage中，该VkSampler不能和任何包含 LOD bias或者offset 值 的SPIR-V OpImageSample* or OpImageSparseSample*指令一起使用
		31.如果shaderObject开启，一个有效的pipeline必须绑定到该命令使用的pipeline bind point上或者一个有效的shader objects以及VK_NULL_HANDLE的组合必须绑定到该命令使用的pipeline bind point每一个支持的shader stage上
		32.如何绑定到该命令使用的pipeline bind point上的VkPipeline的任何stage会访问一个uniform buffer，且该stage对uniformBuffers不以启用VK_PIPELINE_ROBUSTNESS_BUFFER_BEHAVIOR_ROBUST_BUFFER_ACCESS_EXT或者VK_PIPELINE_ROBUSTNESS_BUFFER_BEHAVIOR_ROBUST_BUFFER_ACCESS_2_EXT 创建，且robustBufferAccess特性未开启，则该stage就不能访问绑定到相同pipeline bind point的descriptor set指定的buffer范围外的值
		33.如果robustBufferAccess特性未开启，且任何会访问uniform buffer的绑定到该命令使用的pipeline bind point上对应shader stage的VkShaderEXT，则其不能访问绑定到相同pipeline bind point的descriptor set指定的buffer范围外的值
		34.如何绑定到该命令使用的pipeline bind point上的VkPipeline的任何stage会访问一个storage buffer，且该stage对storageBuffers不以启用VK_PIPELINE_ROBUSTNESS_BUFFER_BEHAVIOR_ROBUST_BUFFER_ACCESS_EXT或者VK_PIPELINE_ROBUSTNESS_BUFFER_BEHAVIOR_ROBUST_BUFFER_ACCESS_2_EXT 创建，且robustBufferAccess特性未开启，则该stage就不能访问绑定到相同pipeline bind point的descriptor set指定的buffer范围外的值
		35.如果robustBufferAccess特性未开启，且任何会访问storage buffer的绑定到该命令使用的pipeline bind point上对应shader stage的VkShaderEXT，则其不能访问绑定到相同pipeline bind point的descriptor set指定的buffer范围外的值
		36.如果commandBuffer 是一个unprotected command buffer，且protectedNoFault 未支持，则任何绑定的shaders访问的资源不能是一个protected resource
		37.如果一个绑定的shader访问一个VkSampler 或者 VkImageView ，且启用了sampler Y′C BCR conversion，则只能使用OpImageSample* 或者 OpImageSparseSample*指令，不能使用ConstOffset 以及 Offset操作符
		38.如果一个VkImageView作为该命令的结果进行访问，则（1）image view 的viewType 必须匹配Instruction/Sampler/Image View Validation p1481中描述的OpTypeImage的Dim操作符
														  （2）image view 的foamrt的numeric type 必须匹配OpTypeImage的Sampled Type操作符
		39.如果一个VkImageView以一个不是VK_FORMAT_A8_UNORM_KHR的format创建且通过OpImageWrite作为该命令的结果进行访问，则该命令的Texel 操作符的Type必须至少包含和 image view的 format含有的components的个数相同的components个数
		40.如果一个VkImageView以VK_FORMAT_A8_UNORM_KHR的format创建且通过OpImageWrite作为该命令的结果进行访问，则该命令的Texel 操作符的Type必须包含4个components
		41.如果一个VkBufferView通过OpImageWrite作为该命令的结果进行访问，则该命令的Texel 操作符的Type必须至少包含和 buffer view的 format含有的components的个数相同的components个数
		42.如果一个带64-bit component的VkFormat的VkImageView作为该命令的结果进行访问，则该命令的OpTypeImage操作符的SampledType的宽度必须为64
		43.如果一个带少于64-bit component的VkFormat的VkImageView作为该命令的结果进行访问，则该命令的OpTypeImage操作符的SampledType的宽度必须为32
		44.如果一个带64-bit component的VkFormat的VkBufferView作为该命令的结果进行访问，则该命令的OpTypeImage操作符的SampledType的宽度必须为64位
		45.如果一个带少于64-bit component的VkFormat的VkBufferView作为该命令的结果进行访问，则该命令的OpTypeImage操作符的SampledType的宽度必须为32
		46.如果sparseImageInt64Atomics 特性未开启，则以VK_IMAGE_CREATE_SPARSE_RESIDENCY_BIT创建的VkImage对象不能被SampledType宽度为64位的OpTypeImage的atomic instructions访问
		47.如果sparseImageInt64Atomics 特性未开启，则以VK_BUFFER_CREATE_SPARSE_RESIDENCY_BIT创建的VkBuffer对象不能被SampledType宽度为64位的OpTypeImage的atomic instructions访问
		48.如果OpImageWeightedSampleQCOM用来采样一个作为该命令的结果的VkImageView，则该image view的format features必须包含VK_FORMAT_FEATURE_2_WEIGHT_SAMPLED_IMAGE_BIT_QCOM
		49.如果OpImageWeightedSampleQCOM用来采样一个作为该命令的结果的sample weight image的VkImageView，则该image view的format features必须包含VK_FORMAT_FEATURE_2_WEIGHT_IMAGE_BIT_QCOM
		50.如果OpImageBoxFilterQCOM用来采样一个作为该命令的结果的VkImageView，则该image view的format features必须包含VK_FORMAT_FEATURE_2_BOX_FILTER_SAMPLED_BIT_QCOM
		51.如果OpImageBlockMatchSSDQCOM，或者 OpImageBlockMatchSADQCOM用来读取一个作为该命令的结果的VkImageView，则（1）该image view的format features必须包含VK_FORMAT_FEATURE_2_BLOCK_MATCHING_BIT_QCOM
																												   （2）如果是读取的reference image，指定的reference coordinates不能在integer texel coordinate validation 时候失败
		52.如果OpImageWeightedSampleQCOM, OpImageBoxFilterQCOM, OpImageBlockMatchWindowSSDQCOM, OpImageBlockMatchWindowSADQCOM, OpImageBlockMatchGatherSSDQCOM,
													OpImageBlockMatchGatherSADQCOM, OpImageBlockMatchSSDQCOM, 或者 OpImageBlockMatchSADQCOM用来采样一个作为该命令的结果的VkImageView，则该VkSampler必须以VK_SAMPLER_CREATE_IMAGE_PROCESSING_BIT_QCOM创建
		53.如果任何除了OpImageWeightedSampleQCOM, OpImageBoxFilterQCOM, OpImageBlockMatchWindowSSDQCOM, OpImageBlockMatchWindowSADQCOM, OpImageBlockMatchGatherSSDQCOM, OpImageBlockMatchGatherSADQCOM, OpImageBlockMatchSSDQCOM, 或者 OpImageBlockMatchSADQCOM之外的指令使用VkSampler进行采样作为该命令的结果，则该sampler不能以VK_SAMPLER_CREATE_IMAGE_PROCESSING_BIT_QCOM 创建
		54.如果OpImageBlockMatchWindow*QCOM or OpImageBlockMatchGather*QCOM指令用来读取VkImageView作为该命令的结果，则（1）VkImageView的format features必须包含VK_FORMAT_FEATURE_2_BLOCK_MATCHING_BIT_QCOM
																													  （2）VkImageView的format必须只含有一个component
		55.如果OpImageBlockMatchWindow*QCOM or OpImageBlockMatchGather*QCOM指令用来读取一个引用的image作为该命令的结果，则指定的 reference coordinates不能在integer texel coordinate validation 时候失败
		56.任何该命令执行的shader invocation必须已经终止
		57.如果有一个类型位为VK_DESCRIPTOR_TYPE_SAMPLE_WEIGHT_IMAGE_QCOM, VK_DESCRIPTOR_TYPE_BLOCK_MATCH_IMAGE_QCOM, VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE, VK_DESCRIPTOR_TYPE_STORAGE_IMAGE, 或者 VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT中任意一个的descriptor作为该命令的结果进行访问，则该descriptor所指的image subresource的layout必须和该descriptor被写入时的layout相同。
		
		58.commandBuffer 不能为一个protected command buffer，必须为一个primary command buffer
		59.scratch 必须是大小至少为调用VkExecutionGraphPipelineScratchSizeAMDX传入绑定的 execution graph返回的VkExecutionGraphPipelineScratchSizeAMDX::size的内存地址
		60.scratch 必须是以VK_BUFFER_USAGE_EXECUTION_GRAPH_SCRATCH_BIT_AMDX 或者VK_BUFFER_USAGE_2_EXECUTION_GRAPH_SCRATCH_BIT_AMDX创建的VkBuffer的设备地址
		61.[scratch,scratch + VkExecutionGraphPipelineScratchSizeAMDX::size) 内的内存必须已经使用当前绑定的execution graph调用vkCmdInitializeGraphScratchMemoryAMDX进行初始化了，且不能被其他execution graph的dispatch command 更改
		62.该命令的执行不能导致一个node以一个workgroups的最大数量（由node中的MaxNumWorkgroupsAMDX 或者maxComputeWorkGroupCount 指定）被派发
		63.该命令的执行不能导致任何shader初始化超过maxExecutionGraphShaderPayloadCount个 output payloads
		64.该命令的执行不能导致任何声明了NodeMaxPayloadsAMDX的 shader初始化超过该声明指定的payloads的最大数量。该需求会应用到每个NodeMaxPayloadsAMDX 声明。
		65.pCountInfo->infos 必须是一个device指针，当该命令在device上执行的时候必须指向一个大小至少为count * stride 的内存
		66.pCountInfo->infos 必须是一个以VK_BUFFER_USAGE_INDIRECT_BUFFER_BIT创建的VkBuffer的device地址
		67.pCountInfo->infos 必须是executionGraphDispatchAddressAlignment的倍数
		68.[infos, infos + (count*stride)) 中的device地址以stride为粒度，在该命令在device上运行的时候，每个粒度中前24字节必须包含有效的VkDispatchGraphInfoAMDX
		69.对pCountInfo->infos中的每个VkDispatchGraphInfoAMDX，（1）其payloads必须是一个device端的指针，在该命令在device上运行的时候，指向大小至少为 payloadCount * payloadStride的内存地址
															   （2）其payloads必须是一个device端的指针，在该命令在device上运行的时候，指向一个以VK_BUFFER_USAGE_INDIRECT_BUFFER_BIT 创建的VkBuffer的内存地址
															   （3）其payloads 必须是executionGraphDispatchAddressAlignment 的倍数
															   （4）在该命令在device上运行的时候，其nodeIndex 必须是一个在当前调用vkGetExecutionGraphPipelineNodeIndexAMDX传入绑定的execution graph pipeline中返回的有效的node 索引
															   （5）在该命令在device上运行的时候，其指向的device地址范围[payloads, payloads + (payloadCount * payloadStride))，以payloadStride 为粒度，该粒度中最开始的字节必须包含一个payload，该payload的大小匹配nodeIndex所指的node期望的input payload的大小


		*/


		//记录派发一个 execution graph,其中所有参数从device中读取   ,scratch在VK_PIPELINE_STAGE_2_COMPUTE_SHADER_BIT pipeline stage同步，以VK_ACCESS_2_SHADER_STORAGE_READ_BIT 以及 VK_ACCESS_2_SHADER_STORAGE_WRITE_BIT进行访问
		vkCmdDispatchGraphIndirectCountAMDX(commandBuffer, scratch, VkDeviceAddress{/*假设这是一个有效的VkDeviceAddress*/ }/*countInfo, 一个VkDispatchGraphCountInfoAMDX结构体的device地址，定义要被执行的nodes*/);
		/*
		vkCmdDispatchGraphIndirectCountAMDX有效用法:
		1.如果一个VkSampler以其magFilter或者minFilter等于VK_FILTER_LINEAR创建，则（1）如果reductionMode为VK_SAMPLER_REDUCTION_MODE_WEIGHTED_AVERAGE，如果用于采样一个VkImageView作为该命令的结果的compareEnable为VK_FALSE，则该image view的format features必须包含VK_FORMAT_FEATURE_SAMPLED_IMAGE_FILTER_LINEAR_BIT
																				 （2）如果reductionMode为VK_SAMPLER_REDUCTION_MODE_MIN 或者VK_SAMPLER_REDUCTION_MODE_MAX之一 用于采样一个VkImageView作为该命令的结果，则该image view的format features必须包含VK_FORMAT_FEATURE_SAMPLED_IMAGE_FILTER_MINMAX_BIT
		2.如果一个VkSampler以其mipmapMode 等于VK_SAMPLER_MIPMAP_MODE_LINEAR创建，则（1）如果reductionMode为VK_SAMPLER_REDUCTION_MODE_WEIGHTED_AVERAGE，如果用于采样一个VkImageView作为该命令的结果的compareEnable为VK_FALSE，则该image view的format features必须包含VK_FORMAT_FEATURE_SAMPLED_IMAGE_FILTER_LINEAR_BIT
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
		23.如果通过vkCmdBindDescriptorSets指定绑定到pipeline bind point的VkPipeline要使用的descriptors，则绑定的VkPipeline不能以VK_PIPELINE_CREATE_DESCRIPTOR_BUFFER_BIT_EXT创建
		24.在vkCmdSetDescriptorBufferOffsetsEXT中指定绑定的descriptor buffers的descriptors，则（1）如果绑定到pipeline bind point的该命令会使用的VkPipeline以VK_PIPELINE_CREATE_DESCRIPTOR_BUFFER_BIT_EXT创建，且这些descriptors是动态使用的，则这些descriptors必须是有效的
																							  （2）如果绑定到pipeline bind point的对应stage的该命令会使用的VkShaderEXT，且这些descriptors是动态使用的，则这些descriptors必须是有效的
		25.在vkCmdSetDescriptorBufferOffsetsEXT中指定的descriptors在绑定到pipeline bind point的VkPipeline中使用，则VkPipeline必须以VK_PIPELINE_CREATE_DESCRIPTOR_BUFFER_BIT_EXT创建
		26.如果一个descriptor在以VK_PIPELINE_CREATE_DESCRIPTOR_BUFFER_BIT_EXT创建的VkPipeline中动态使用，则descriptor memory必须是驻留内存
		27.如果一个descriptor在以其VkDescriptorSetLayout以VK_DESCRIPTOR_SET_LAYOUT_CREATE_DESCRIPTOR_BUFFER_BIT_EXT创建的VkShaderEXT中动态使用，则descriptor memory必须是驻留内存
		28.如果shaderObject 特性没有开启，一个有效的pipeline必须绑定到这个命令使用的绑定到pipeline bind point上
		29.如果一个pipeline绑定到该命令使用的pipeline bind point上，则不能有任何动态state 设置命令设置任何该VkPipeline 中没有指定的动态 state
		30.如果一个VkPipeline绑定到该命令使用的pipeline bind point上 或者任何一个会访问一个使用unnormalized coordinates的VkSampler的 VkShaderEXT绑定到该命令使用的pipeline bind point上的pipeline的对应stage，则
																					（1）在任何shader stage中，VkSampler不能用来采样任何类型为VK_IMAGE_VIEW_TYPE_3D, VK_IMAGE_VIEW_TYPE_CUBE, VK_IMAGE_VIEW_TYPE_1D_ARRAY, VK_IMAGE_VIEW_TYPE_2D_ARRAY 或者 VK_IMAGE_VIEW_TYPE_CUBE_ARRAY的VkImageView
																					（2）在任何shader stage中，该VkSampler不能和任何带有名字中带有ImplicitLod，Dref 或者 Proj 的SPIR-V OpImageSample* 或者 OpImageSparseSample*指令一起使用
																					（3）在任何shader stage中，该VkSampler不能和任何包含 LOD bias或者offset 值 的SPIR-V OpImageSample* or OpImageSparseSample*指令一起使用
		31.如果shaderObject开启，一个有效的pipeline必须绑定到该命令使用的pipeline bind point上或者一个有效的shader objects以及VK_NULL_HANDLE的组合必须绑定到该命令使用的pipeline bind point每一个支持的shader stage上
		32.如何绑定到该命令使用的pipeline bind point上的VkPipeline的任何stage会访问一个uniform buffer，且该stage对uniformBuffers不以启用VK_PIPELINE_ROBUSTNESS_BUFFER_BEHAVIOR_ROBUST_BUFFER_ACCESS_EXT或者VK_PIPELINE_ROBUSTNESS_BUFFER_BEHAVIOR_ROBUST_BUFFER_ACCESS_2_EXT 创建，且robustBufferAccess特性未开启，则该stage就不能访问绑定到相同pipeline bind point的descriptor set指定的buffer范围外的值
		33.如果robustBufferAccess特性未开启，且任何会访问uniform buffer的绑定到该命令使用的pipeline bind point上对应shader stage的VkShaderEXT，则其不能访问绑定到相同pipeline bind point的descriptor set指定的buffer范围外的值
		34.如何绑定到该命令使用的pipeline bind point上的VkPipeline的任何stage会访问一个storage buffer，且该stage对storageBuffers不以启用VK_PIPELINE_ROBUSTNESS_BUFFER_BEHAVIOR_ROBUST_BUFFER_ACCESS_EXT或者VK_PIPELINE_ROBUSTNESS_BUFFER_BEHAVIOR_ROBUST_BUFFER_ACCESS_2_EXT 创建，且robustBufferAccess特性未开启，则该stage就不能访问绑定到相同pipeline bind point的descriptor set指定的buffer范围外的值
		35.如果robustBufferAccess特性未开启，且任何会访问storage buffer的绑定到该命令使用的pipeline bind point上对应shader stage的VkShaderEXT，则其不能访问绑定到相同pipeline bind point的descriptor set指定的buffer范围外的值
		36.如果commandBuffer 是一个unprotected command buffer，且protectedNoFault 未支持，则任何绑定的shaders访问的资源不能是一个protected resource
		37.如果一个绑定的shader访问一个VkSampler 或者 VkImageView ，且启用了sampler Y′C BCR conversion，则只能使用OpImageSample* 或者 OpImageSparseSample*指令，不能使用ConstOffset 以及 Offset操作符
		38.如果一个VkImageView作为该命令的结果进行访问，则（1）image view 的viewType 必须匹配Instruction/Sampler/Image View Validation p1481中描述的OpTypeImage的Dim操作符
														  （2）image view 的foamrt的numeric type 必须匹配OpTypeImage的Sampled Type操作符
		39.如果一个VkImageView以一个不是VK_FORMAT_A8_UNORM_KHR的format创建且通过OpImageWrite作为该命令的结果进行访问，则该命令的Texel 操作符的Type必须至少包含和 image view的 format含有的components的个数相同的components个数
		40.如果一个VkImageView以VK_FORMAT_A8_UNORM_KHR的format创建且通过OpImageWrite作为该命令的结果进行访问，则该命令的Texel 操作符的Type必须包含4个components
		41.如果一个VkBufferView通过OpImageWrite作为该命令的结果进行访问，则该命令的Texel 操作符的Type必须至少包含和 buffer view的 format含有的components的个数相同的components个数
		42.如果一个带64-bit component的VkFormat的VkImageView作为该命令的结果进行访问，则该命令的OpTypeImage操作符的SampledType的宽度必须为64
		43.如果一个带少于64-bit component的VkFormat的VkImageView作为该命令的结果进行访问，则该命令的OpTypeImage操作符的SampledType的宽度必须为32
		44.如果一个带64-bit component的VkFormat的VkBufferView作为该命令的结果进行访问，则该命令的OpTypeImage操作符的SampledType的宽度必须为64位
		45.如果一个带少于64-bit component的VkFormat的VkBufferView作为该命令的结果进行访问，则该命令的OpTypeImage操作符的SampledType的宽度必须为32
		46.如果sparseImageInt64Atomics 特性未开启，则以VK_IMAGE_CREATE_SPARSE_RESIDENCY_BIT创建的VkImage对象不能被SampledType宽度为64位的OpTypeImage的atomic instructions访问
		47.如果sparseImageInt64Atomics 特性未开启，则以VK_BUFFER_CREATE_SPARSE_RESIDENCY_BIT创建的VkBuffer对象不能被SampledType宽度为64位的OpTypeImage的atomic instructions访问
		48.如果OpImageWeightedSampleQCOM用来采样一个作为该命令的结果的VkImageView，则该image view的format features必须包含VK_FORMAT_FEATURE_2_WEIGHT_SAMPLED_IMAGE_BIT_QCOM
		49.如果OpImageWeightedSampleQCOM用来采样一个作为该命令的结果的sample weight image的VkImageView，则该image view的format features必须包含VK_FORMAT_FEATURE_2_WEIGHT_IMAGE_BIT_QCOM
		50.如果OpImageBoxFilterQCOM用来采样一个作为该命令的结果的VkImageView，则该image view的format features必须包含VK_FORMAT_FEATURE_2_BOX_FILTER_SAMPLED_BIT_QCOM
		51.如果OpImageBlockMatchSSDQCOM，或者 OpImageBlockMatchSADQCOM用来读取一个作为该命令的结果的VkImageView，则（1）该image view的format features必须包含VK_FORMAT_FEATURE_2_BLOCK_MATCHING_BIT_QCOM
																												   （2）如果是读取的reference image，指定的reference coordinates不能在integer texel coordinate validation 时候失败
		52.如果OpImageWeightedSampleQCOM, OpImageBoxFilterQCOM, OpImageBlockMatchWindowSSDQCOM, OpImageBlockMatchWindowSADQCOM, OpImageBlockMatchGatherSSDQCOM,
													OpImageBlockMatchGatherSADQCOM, OpImageBlockMatchSSDQCOM, 或者 OpImageBlockMatchSADQCOM用来采样一个作为该命令的结果的VkImageView，则该VkSampler必须以VK_SAMPLER_CREATE_IMAGE_PROCESSING_BIT_QCOM创建
		53.如果任何除了OpImageWeightedSampleQCOM, OpImageBoxFilterQCOM, OpImageBlockMatchWindowSSDQCOM, OpImageBlockMatchWindowSADQCOM, OpImageBlockMatchGatherSSDQCOM, OpImageBlockMatchGatherSADQCOM, OpImageBlockMatchSSDQCOM, 或者 OpImageBlockMatchSADQCOM之外的指令使用VkSampler进行采样作为该命令的结果，则该sampler不能以VK_SAMPLER_CREATE_IMAGE_PROCESSING_BIT_QCOM 创建
		54.如果OpImageBlockMatchWindow*QCOM or OpImageBlockMatchGather*QCOM指令用来读取VkImageView作为该命令的结果，则（1）VkImageView的format features必须包含VK_FORMAT_FEATURE_2_BLOCK_MATCHING_BIT_QCOM
																													  （2）VkImageView的format必须只含有一个component
		55.如果OpImageBlockMatchWindow*QCOM or OpImageBlockMatchGather*QCOM指令用来读取一个引用的image作为该命令的结果，则指定的 reference coordinates不能在integer texel coordinate validation 时候失败
		56.任何该命令执行的shader invocation必须已经终止
		57.如果有一个类型位为VK_DESCRIPTOR_TYPE_SAMPLE_WEIGHT_IMAGE_QCOM, VK_DESCRIPTOR_TYPE_BLOCK_MATCH_IMAGE_QCOM, VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE, VK_DESCRIPTOR_TYPE_STORAGE_IMAGE, 或者 VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT中任意一个的descriptor作为该命令的结果进行访问，则该descriptor所指的image subresource的layout必须和该descriptor被写入时的layout相同。

		58.commandBuffer 不能为一个protected command buffer，必须为一个primary command buffer
		59.scratch 必须是大小至少为调用VkExecutionGraphPipelineScratchSizeAMDX传入绑定的 execution graph返回的VkExecutionGraphPipelineScratchSizeAMDX::size的内存地址
		60.scratch 必须是以VK_BUFFER_USAGE_EXECUTION_GRAPH_SCRATCH_BIT_AMDX 或者VK_BUFFER_USAGE_2_EXECUTION_GRAPH_SCRATCH_BIT_AMDX创建的VkBuffer的设备地址
		61.[scratch,scratch + VkExecutionGraphPipelineScratchSizeAMDX::size) 内的内存必须已经使用当前绑定的execution graph调用vkCmdInitializeGraphScratchMemoryAMDX进行初始化了，且不能被其他execution graph的dispatch command 更改
		62.该命令的执行不能导致一个node以一个workgroups的最大数量（由node中的MaxNumWorkgroupsAMDX 或者maxComputeWorkGroupCount 指定）被派发
		63.该命令的执行不能导致任何shader初始化超过maxExecutionGraphShaderPayloadCount个 output payloads
		64.该命令的执行不能导致任何声明了NodeMaxPayloadsAMDX的 shader初始化超过该声明指定的payloads的最大数量。该需求会应用到每个NodeMaxPayloadsAMDX 声明。

		65.当该命令在device上执行时，countInfo 必须是一个内存包含一个VkDispatchGraphCountInfoAMDX的内存地址
		66..countInfo 必须是一个以VK_BUFFER_USAGE_INDIRECT_BUFFER_BIT创建的VkBuffer的device地址
		67.countInfo 必须是executionGraphDispatchAddressAlignment的倍数
		68.countInfo->infos 必须是一个device指针，当该命令在device上执行的时候必须指向一个大小至少为count * stride 的内存
		69.countInfo->infos 必须是一个以VK_BUFFER_USAGE_INDIRECT_BUFFER_BIT创建的VkBuffer的device地址
		70.countInfo->infos 必须是executionGraphDispatchAddressAlignment的倍数
		71.[infos, infos + (count*stride)) 中的device地址以stride为粒度，在该命令在device上运行的时候，每个粒度中前24字节必须包含有效的VkDispatchGraphInfoAMDX
		69.对countInfo->infos中的每个VkDispatchGraphInfoAMDX，（1）其payloads必须是一个device端的指针，在该命令在device上运行的时候，指向大小至少为 payloadCount * payloadStride的内存地址
															   （2）其payloads必须是一个device端的指针，在该命令在device上运行的时候，指向一个以VK_BUFFER_USAGE_INDIRECT_BUFFER_BIT 创建的VkBuffer的内存地址
															   （3）其payloads 必须是executionGraphDispatchAddressAlignment 的倍数
															   （4）在该命令在device上运行的时候，其nodeIndex 必须是一个在当前调用vkGetExecutionGraphPipelineNodeIndexAMDX传入绑定的execution graph pipeline中返回的有效的node 索引
															   （5）在该命令在device上运行的时候，其指向的device地址范围[payloads, payloads + (payloadCount * payloadStride))，以payloadStride 为粒度，该粒度中最开始的字节必须包含一个payload，该payload的大小匹配nodeIndex所指的node期望的input payload的大小
		
		*/

	}


	//Shader Enqueue  参见p3669
	{
		//一旦shader完成了对payload的写入初始化好node payload，则这些payload就会进行入队进行派发。

		//Compute Nodes  简单讲就是作为node的compute shader根据StaticNumWorkgroupsAMDX 或者 CoalescingAMDX execution modes 呈现不同的执行方式.  详情参见p3699
	}

}


void OpticalFlowAndExcutionGraphsAndLowLatencyTest::LowLatency2Test()
{
	//Latency Reduction  参见p3701
	{
		VkSwapchainKHR swapchainKHR{/*假设这是一个有效的VkSwapChainKHR*/ };

		//开启swapchain上的 low latency mode
		VkLatencySleepModeInfoNV latencySleepModeInfoNV{};
		latencySleepModeInfoNV.sType = VK_STRUCTURE_TYPE_LATENCY_SLEEP_MODE_INFO_NV;
		latencySleepModeInfoNV.pNext = nullptr;
		latencySleepModeInfoNV.lowLatencyMode = VK_TRUE;//指明是否开启low latency mode
		latencySleepModeInfoNV.lowLatencyBoost = VK_TRUE;//允许应用提示GPU提升性能以在逐渐提高的能量消耗中增加对latency的节省
		latencySleepModeInfoNV.minimumIntervalUs = 1;//是对设置的swapchain的vkQueuePresentKHR调用之间的毫秒间隔

		vkSetLatencySleepModeNV(device, swapchainKHR, &latencySleepModeInfoNV);


		//提供同步原语用于延迟 lower latency的host CPU work
		VkLatencySleepInfoNV latencySleepInfoNV{};
		latencySleepInfoNV.sType = VK_STRUCTURE_TYPE_LATENCY_SLEEP_INFO_NV;
		latencySleepInfoNV.pNext = nullptr;
		latencySleepInfoNV.signalSemaphore = VkSemaphore{/*假设这是一个有效的VkSemaphore*/ };//是一个要触发的semaphore指明应用应该消耗input sampling work，必须为一个timeline semaphore
		latencySleepInfoNV.value = 0;//指明消耗sampling work 的 signalSemaphore的值

		vkLatencySleepNV(device, swapchainKHR, &latencySleepInfoNV);



		//应用在产生frame的不同阶段提供了时间戳
		VkSetLatencyMarkerInfoNV setLatencyMarkerInfoNV{};
		setLatencyMarkerInfoNV.sType = VK_STRUCTURE_TYPE_SET_LATENCY_MARKER_INFO_NV;
		setLatencyMarkerInfoNV.pNext = nullptr;
		setLatencyMarkerInfoNV.presentID = 0;//为用户提供的一个值，用于将时间戳关联到一个vkQueuePresentKHR 命令，对应VkPresentIdKHR::pPresentIds中的
		setLatencyMarkerInfoNV.marker = VK_LATENCY_MARKER_INPUT_SAMPLE_NV;//VkLatencyMarkerNV值，为记录的时间戳的类型
		/*
		VkLatencyMarkerNV:
		VK_LATENCY_MARKER_SIMULATION_START_NV : 应该在每个frame的simulation执行开始之前调用，该调用之后为vkLatencySleepNV
		VK_LATENCY_MARKER_SIMULATION_END_NV : 应该在每个frame的simulation执行结束时调用
		VK_LATENCY_MARKER_RENDERSUBMIT_START_NV : 应该在每个frame的渲染提交执行开始时调用，不能用与异步渲染
		VK_LATENCY_MARKER_RENDERSUBMIT_END_NV : 应该在每个frame的渲染提交执行结束时调用
		VK_LATENCY_MARKER_PRESENT_START_NV : 应该在vkQueuePresentKHR 之前调用
		VK_LATENCY_MARKER_PRESENT_END_NV : 应该在vkQueuePresentKHR 返回时调用
		VK_LATENCY_MARKER_INPUT_SAMPLE_NV : 应该在应用获取input数据之前调用
		VK_LATENCY_MARKER_TRIGGER_FLASH_NV : 应该在当一个鼠标点击时间发生时的VK_LATENCY_MARKER_SIMULATION_START_NV 以及 VK_LATENCY_MARKER_SIMULATION_END_NV之间的任何时候调用

		*/

		vkSetLatencyMarkerNV(device, swapchainKHR, &setLatencyMarkerInfoNV);


		//获取一个包含最新的 latency数据的数组
		std::vector<VkLatencyTimingsFrameReportNV> latencyTimingsFrameReportNVs{};

		VkGetLatencyMarkerInfoNV getLatencyMarkerInfoNV{};
		getLatencyMarkerInfoNV.sType = VK_STRUCTURE_TYPE_GET_LATENCY_MARKER_INFO_NV;
		getLatencyMarkerInfoNV.pNext = nullptr;
		getLatencyMarkerInfoNV.timingCount = 0;//为可用的或者已经查询过的 latency data关联的先前frame的数量
		getLatencyMarkerInfoNV.pTimings = nullptr;//为NULL或者 VkLatencyTimingsFrameReportNV 数组指针

		vkGetLatencyTimingsNV(device, swapchainKHR, &getLatencyMarkerInfoNV);
		latencyTimingsFrameReportNVs.resize(getLatencyMarkerInfoNV.timingCount);
		getLatencyMarkerInfoNV.pTimings = latencyTimingsFrameReportNVs.data();

		vkGetLatencyTimingsNV(device, swapchainKHR, &getLatencyMarkerInfoNV);//假设成功返回了一个结果

		VkLatencyTimingsFrameReportNV &latencyTimingsFrameReportNV = latencyTimingsFrameReportNVs[0];
		latencyTimingsFrameReportNV.sType = VK_STRUCTURE_TYPE_LATENCY_TIMINGS_FRAME_REPORT_NV;
		latencyTimingsFrameReportNV.pNext = nullptr;
		latencyTimingsFrameReportNV.presentID = 0;//为用户提供的一个值，用于将时间戳关联到一个vkQueuePresentKHR 命令，对应VkPresentIdKHR::pPresentIds中的
		latencyTimingsFrameReportNV.inputSampleTimeUs = 0;//为调用vkSetLatencyMarkerNV设置为VK_LATENCY_MARKER_INPUT_SAMPLE_NV时返回的时间戳的值
		latencyTimingsFrameReportNV.simStartTimeUs = 0;//为调用vkSetLatencyMarkerNV设置为 VK_LATENCY_MARKER_SIMULATION_START_NV时返回的时间戳的值
		latencyTimingsFrameReportNV.simEndTimeUs = 0;//为调用vkSetLatencyMarkerNV设置为  VK_LATENCY_MARKER_SIMULATION_END_NV时返回的时间戳的值
		latencyTimingsFrameReportNV.renderSubmitStartTimeUs = 0;//为调用vkSetLatencyMarkerNV设置为  VK_LATENCY_MARKER_RENDERSUBMIT_START_NV时返回的时间戳的值
		latencyTimingsFrameReportNV.renderSubmitEndTimeUs = 0;//为调用vkSetLatencyMarkerNV设置为 VK_LATENCY_MARKER_RENDERSUBMIT_END_NV时返回的时间戳的值
		latencyTimingsFrameReportNV.presentStartTimeUs = 0;//为调用vkSetLatencyMarkerNV设置为 VK_LATENCY_MARKER_PRESENT_START_NV时返回的时间戳的值
		latencyTimingsFrameReportNV.presentEndTimeUs = 0;//为调用vkSetLatencyMarkerNV设置为VK_LATENCY_MARKER_PRESENT_END_NV时返回的时间戳的值
		latencyTimingsFrameReportNV.driverStartTimeUs = 0;//为该frame的第一个vkQueueSubmit调用时返回的时间戳的值
		latencyTimingsFrameReportNV.driverEndTimeUs = 0;//为Vulkan Driver上处理的最后一个 vkQueueSubmit处理完后返回的时间戳的值
		latencyTimingsFrameReportNV.osRenderQueueStartTimeUs = 0;//为Vulkan Driver上处理的最后一个 vkQueueSubmit处理完后返回的时间戳的值
		latencyTimingsFrameReportNV.osRenderQueueEndTimeUs = 0;//为第一个提交抵达GPU时返回的时间戳的值
		latencyTimingsFrameReportNV.gpuRenderStartTimeUs = 0;//为第一个提交抵达GPU时返回的时间戳的值
		latencyTimingsFrameReportNV.gpuRenderEndTimeUs = 0;//为该frame在GPU上的最后一个提交完成时返回的时间戳的值


		VkLatencySubmissionPresentIdNV latencySubmissionPresentIdNV{};//用于vkQueueSubmit
		latencySubmissionPresentIdNV.sType = VK_STRUCTURE_TYPE_LATENCY_SUBMISSION_PRESENT_ID_NV;
		latencySubmissionPresentIdNV.pNext = nullptr;
		latencySubmissionPresentIdNV.presentID = 0;//用于将vkQueueSubmit 关联到一个之前的vkQueuePresentKHR ，通过对应到VkPresentIdKHR::pPresentIds中的值.


		//应用可以标记一个queue 为 Out of Band的，即当对 latency evaluation时所有 在该队列上执行的vkQueueSubmit会被忽略
		VkOutOfBandQueueTypeInfoNV outOfBandQueueTypeInfoNV{};
		outOfBandQueueTypeInfoNV.sType = VK_STRUCTURE_TYPE_OUT_OF_BAND_QUEUE_TYPE_INFO_NV;
		outOfBandQueueTypeInfoNV.pNext = nullptr;
		outOfBandQueueTypeInfoNV.queueType = VK_OUT_OF_BAND_QUEUE_TYPE_PRESENT_NV;//VkOutOfBandQueueTypeNV值，指明标记为Out of Band的queue的用途
		/*
		VkOutOfBandQueueTypeNV:
		VK_OUT_OF_BAND_QUEUE_TYPE_RENDER_NV : 指明该work会被提交到该queue
		VK_OUT_OF_BAND_QUEUE_TYPE_PRESENT_NV : 指明该queue将用于present

		*/

		vkQueueNotifyOutOfBandNV(VkQueue{/*假设这是一个有效的VkQueue*/ }, &outOfBandQueueTypeInfoNV);



		//允许 low latency mode 用于swapchain，在VkSwapchainCreateInfoKHR.pNext中包含一个VkSwapchainLatencyCreateInfoNV
		VkSwapchainLatencyCreateInfoNV swapchainLatencyCreateInfoNV{};
		swapchainLatencyCreateInfoNV.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_LATENCY_CREATE_INFO_NV;
		swapchainLatencyCreateInfoNV.pNext = nullptr;
		swapchainLatencyCreateInfoNV.latencyModeEnable = VK_TRUE;//指明创建的swapchain是否使用low latency mode


		VkLatencySurfaceCapabilitiesNV  latencySurfaceCapabilitiesNV{};//该结构提用于返回优化的用于low latency mode的 present mode
		latencySurfaceCapabilitiesNV.sType = VK_STRUCTURE_TYPE_LATENCY_SURFACE_CAPABILITIES_NV;
		latencySurfaceCapabilitiesNV.pNext = nullptr;
		latencySurfaceCapabilitiesNV.presentModeCount = 1;//为pPresentModes 中元素个数
		VkPresentModeKHR presenModeKHR = VK_PRESENT_MODE_MAILBOX_KHR;
		latencySurfaceCapabilitiesNV.pPresentModes = &presenModeKHR;//一组VkPresentModeKHR 数组指针，指明提供的用于low latency mode的优化的present mode
	}


}


NS_TEST_END