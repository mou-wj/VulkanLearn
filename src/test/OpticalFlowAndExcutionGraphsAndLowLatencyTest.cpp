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
	//Optical Flow Queues  �μ�p3641
	{
		/*
		VK_NV_optical_flow ��չ�ṩ��optical flow queue���������� - ��һ����ͼ�δ�����ص����ԣ�ר�����ڴ���������㡣������һ�ּ�������֮֡�������˶��ķ�����ͨ��������Ƶ�������˶����Ƶ�Ӧ�á����������Vulkan����Ҫ�����Ż��ͼ����������صĲ�������
		*/
	}

	//Optical Flow Image Formats  �μ�p3641
	{

		//ö���ض� optical flow ��;��֧�ֵ�image formats
		uint32_t formatCount = 0;
		std::vector<VkOpticalFlowImageFormatPropertiesNV> opticalFlowImageFormatPropertiesNVs{};
		

		VkOpticalFlowImageFormatInfoNV opticalFlowImageFormatInfoNV{};
		opticalFlowImageFormatInfoNV.sType = VK_STRUCTURE_TYPE_OPTICAL_FLOW_IMAGE_FORMAT_INFO_NV;
		opticalFlowImageFormatInfoNV.pNext = nullptr;
		opticalFlowImageFormatInfoNV.usage = VK_OPTICAL_FLOW_USAGE_INPUT_BIT_NV;//Ϊ VkOpticalFlowUsageFlagBitsNV ���ֵλ���룬ָ��imageԤ�ڵ�optical flow ��;
		/*
		VkOpticalFlowUsageFlagBitsNV:
		VK_OPTICAL_FLOW_USAGE_INPUT_BIT_NV : ָ��image������Ϊ optical flow operation��input ���� reference frame
		VK_OPTICAL_FLOW_USAGE_OUTPUT_BIT_NV : ָ��image������Ϊ optical flow operation��output flow vector map
		VK_OPTICAL_FLOW_USAGE_HINT_BIT_NV : ָ��image������Ϊ optical flow operation��hint flow vector map
		VK_OPTICAL_FLOW_USAGE_COST_BIT_NV : ָ��image������Ϊ optical flow operation��output cost map
		VK_OPTICAL_FLOW_USAGE_GLOBAL_FLOW_BIT_NV : ָ��image������Ϊ optical flow operation��global flow vector
		*/


		vkGetPhysicalDeviceOpticalFlowImageFormatsNV(physicalDevice, &opticalFlowImageFormatInfoNV, &formatCount, nullptr);
		opticalFlowImageFormatPropertiesNVs.resize(formatCount);
		vkGetPhysicalDeviceOpticalFlowImageFormatsNV(physicalDevice, &opticalFlowImageFormatInfoNV, &formatCount, opticalFlowImageFormatPropertiesNVs.data());//������ȷ������һ��Ԫ��
		/*
		��ע:
		�ڴ���һ����Ϊ optical flow frame��image֮ǰ����ҪvkGetPhysicalDeviceFormatProperties2 �Լ�vkGetPhysicalDeviceImageFormatProperties2 ����������ѯ��õ�format�� VkPhysicalDeviceImageFormatInfo2.pNext�е�VkOpticalFlowImageFormatInfoNV������ѯimage����֧�ֵĲ���
		*/

		VkOpticalFlowImageFormatPropertiesNV& opticalFlowImageFormatPropertiesNV = opticalFlowImageFormatPropertiesNVs[0];
		opticalFlowImageFormatPropertiesNV.sType = VK_STRUCTURE_TYPE_OPTICAL_FLOW_IMAGE_FORMAT_PROPERTIES_NV;
		opticalFlowImageFormatPropertiesNV.pNext = nullptr;
		opticalFlowImageFormatPropertiesNV.format = VK_FORMAT_R8G8_UNORM;// VkFormat ֵ��ָ��������ָ��optical flow��;��image format


	}


	//Optical Flow Session  �μ�p3644
	{
		VkOpticalFlowSessionNV opticalFlowSessionNV{};

		//Optical Flow Session Object �μ�p3644
		{
			//����һ��optical flow session object
			VkOpticalFlowSessionCreateInfoNV opticalFlowSessionCreateInfoNV{};
			opticalFlowSessionCreateInfoNV.sType = VK_STRUCTURE_TYPE_OPTICAL_FLOW_SESSION_CREATE_INFO_NV;
			VkOpticalFlowSessionCreatePrivateDataInfoNV opticalFlowSessionCreatePrivateDataInfoNV{};//�����ڲ�ʹ�õ�����
			{
				opticalFlowSessionCreatePrivateDataInfoNV.sType = VK_STRUCTURE_TYPE_OPTICAL_FLOW_SESSION_CREATE_PRIVATE_DATA_INFO_NV;
				opticalFlowSessionCreatePrivateDataInfoNV.pNext = nullptr;
				opticalFlowSessionCreatePrivateDataInfoNV.id = 0;//ΪpPrivateData ����ָ�����ݵ�һ���ڲ��ı�ʶ
				opticalFlowSessionCreatePrivateDataInfoNV.size = 0;//pPrivateData �а������ֽ����ݴ�С
				opticalFlowSessionCreatePrivateDataInfoNV.pPrivateData = nullptr;//��һ��NV internal data ��ָ��
			}
			opticalFlowSessionCreateInfoNV.pNext = &opticalFlowSessionCreatePrivateDataInfoNV;//���԰���һ��VkOpticalFlowSessionCreatePrivateDataInfoNV
			opticalFlowSessionCreateInfoNV.width = 1;//Ϊ�󶨵�optical flow session��input ���� reference frame ����texel��width
			opticalFlowSessionCreateInfoNV.height = 1;//Ϊ�󶨵�optical flow session��input ���� reference frame ����texel��width
			opticalFlowSessionCreateInfoNV.outputGridSize = VK_OPTICAL_FLOW_GRID_SIZE_1X1_BIT_NV;/* VkOpticalFlowGridSizeFlagsNV ���͵�һ������ֵ��ָ���󶨵�optical flow session��output flow �Լ� cost maps��grid size��output flow �Լ� cost maps�Ĵ�С��width��height���Գ��Ըò�����Ӧֵ����
			Optical flow vectors�Ĳ����ǰ���block��Χ���ģ�ÿ��block��NxN pixel�ģ���Ϊgrid
			VkOpticalFlowGridSizeFlagsNV:
			VK_OPTICAL_FLOW_GRID_SIZE_1X1_BIT_NV : ָ����gridΪ 1x1 pixel.
			VK_OPTICAL_FLOW_GRID_SIZE_2X2_BIT_NV : ָ����gridΪ 2x2 pixel.
			VK_OPTICAL_FLOW_GRID_SIZE_4X4_BIT_NV : ָ����gridΪ 4x4 pixel.
			VK_OPTICAL_FLOW_GRID_SIZE_8X8_BIT_NV : ָ����gridΪ 8x8 pixel.
			
			
			*/
			opticalFlowSessionCreateInfoNV.hintGridSize = VK_OPTICAL_FLOW_GRID_SIZE_1X1_BIT_NV;// VkOpticalFlowGridSizeFlagsNV ���͵�һ������ֵ��ָ���󶨵�optical flow session��hint flow vector maps��grid size��hint flow vector maps�Ĵ�С��width��height���Գ��Ըò�����Ӧֵ����
			opticalFlowSessionCreateInfoNV.performanceLevel = VK_OPTICAL_FLOW_PERFORMANCE_LEVEL_SLOW_NV;/*Ϊ���ڸ�optical session object�� VkOpticalFlowPerformanceLevelNVֵ
			�������ܺ�������Ҫ��ʵ�ֱ�¶���û����Կ��Ƶ����ܼ���
			VkOpticalFlowPerformanceLevelNV:
			VK_OPTICAL_FLOW_PERFORMANCE_LEVEL_SLOW_NV : Ϊһ�������ܵ��������ļ���
			VK_OPTICAL_FLOW_PERFORMANCE_LEVEL_MEDIUM_NV : Ϊһ�����ܺ����������еļ���
			VK_OPTICAL_FLOW_PERFORMANCE_LEVEL_FAST_NV : Ϊһ�������ܵ��������ļ���			
			*/
			opticalFlowSessionCreateInfoNV.flags = VK_OPTICAL_FLOW_SESSION_CREATE_ENABLE_HINT_BIT_NV;/*Ϊ���ڸ�optical session object�� VkOpticalFlowSessionCreateFlagsNVֵ
			VkOpticalFlowSessionCreateFlagsNV:
			VK_OPTICAL_FLOW_SESSION_CREATE_ENABLE_HINT_BIT_NV : ָ�����ⲿflow vectors��VkImageView���ڽ���motion searchʱ������Ϊhints���ұ���󶨵�VK_OPTICAL_FLOW_SESSION_BINDING_POINT_HINT_NV
			VK_OPTICAL_FLOW_SESSION_CREATE_ENABLE_COST_BIT_NV : ָ��VkImageView ��forward flow��cost ����󶨵�VK_OPTICAL_FLOW_SESSION_BINDING_POINT_COST_NV�����⣬���Ҳ������VK_OPTICAL_FLOW_SESSION_CREATE_BOTH_DIRECTIONS_BIT_NV��
							��VkImageView ��backward flow��cost ����󶨵�VK_OPTICAL_FLOW_SESSION_BINDING_POINT_BACKWARD_COST_NV��frame��ÿ��grid��flow vector��cost ��һ��confidence level����ʾ��grid��flow vector��׼ȷ�ԡ�costֵԽ�ߣ���ʾflow vectorԽ��׼ȷ����֮��Ȼ��
			VK_OPTICAL_FLOW_SESSION_CREATE_ENABLE_GLOBAL_FLOW_BIT_NV : ָ��global flow vector �Ǵ�һ��������VkImageView�е�forward flow���Ƶõ��ģ���VkImageView����󶨵�VK_OPTICAL_FLOW_SESSION_BINDING_POINT_GLOBAL_FLOW_NV��
			VK_OPTICAL_FLOW_SESSION_CREATE_ALLOW_REGIONS_BIT_NV : ָ����VkOpticalFlowExecuteInfoNV �п���ָ��interest regions
			VK_OPTICAL_FLOW_SESSION_CREATE_BOTH_DIRECTIONS_BIT_NV : ָ������������forward flow�¶�������backward flow��
			
			*/
			opticalFlowSessionCreateInfoNV.imageFormat = VK_FORMAT_R8_SNORM;//Ϊ�󶨵�optical flow session��input ���� reference frame ��image VkFormat
			opticalFlowSessionCreateInfoNV.flowVectorFormat = VK_FORMAT_R8_SNORM;//Ϊ�󶨵�optical flow session��flow vector maps (output ���� hint) ��image VkFormat
			opticalFlowSessionCreateInfoNV.costFormat = VK_FORMAT_R8_SNORM;//Ϊ�󶨵�optical flow session��const maps ��image VkFormat
			/*
			VkOpticalFlowSessionCreateInfoNV��Ч�÷�:
			1.width ������ڵ���VkPhysicalDeviceOpticalFlowPropertiesNV::minWidth ��С�ڻ����VkPhysicalDeviceOpticalFlowPropertiesNV::maxWidth
			2.height ������ڵ���VkPhysicalDeviceOpticalFlowPropertiesNV::minHeight ��С�ڻ����VkPhysicalDeviceOpticalFlowPropertiesNV::maxHeight
			3.imageFormat ����ΪvkGetPhysicalDeviceOpticalFlowImageFormatsNV����VK_OPTICAL_FLOW_USAGE_INPUT_BIT_NV ���ص�֧�ֵ�image formats֮һ
			4.flowVectorFormat ����ΪvkGetPhysicalDeviceOpticalFlowImageFormatsNV����VK_OPTICAL_FLOW_USAGE_OUTPUT_BIT_NV ���ص�֧�ֵ�image formats֮һ
			5.���flags ��������VK_OPTICAL_FLOW_SESSION_CREATE_ENABLE_COST_BIT_NV ����costFormat ����ΪvkGetPhysicalDeviceOpticalFlowImageFormatsNV����VK_OPTICAL_FLOW_USAGE_COST_BIT_NV ���ص�֧�ֵ�image formats֮һ
			6.outputGridSize ������VkPhysicalDeviceOpticalFlowPropertiesNV::supportedOutputGridSizes �к��е�һ����������
			7.���flags ��������VK_OPTICAL_FLOW_SESSION_CREATE_ENABLE_HINT_BIT_NV ����hintGridSize ������VkPhysicalDeviceOpticalFlowPropertiesNV::supportedHintGridSizes �к��е�һ����������
			8.���VkPhysicalDeviceOpticalFlowPropertiesNV::hintSupported ��ΪVK_FALSE����flags �в�������VK_OPTICAL_FLOW_SESSION_CREATE_ENABLE_HINT_BIT_NV
			9.���VkPhysicalDeviceOpticalFlowPropertiesNV::costSupported ��ΪVK_FALSE����flags �в�������VK_OPTICAL_FLOW_SESSION_CREATE_ENABLE_COST_BIT_NV
			10.���VkPhysicalDeviceOpticalFlowPropertiesNV::globalFlowSupported ��ΪVK_FALSE����flags �в�������VK_OPTICAL_FLOW_SESSION_CREATE_ENABLE_GLOBAL_FLOW_BIT_NV
			11.���VkPhysicalDeviceOpticalFlowPropertiesNV::maxNumRegionsOfInterest Ϊ0������flags�������� VK_OPTICAL_FLOW_SESSION_CREATE_ALLOW_REGIONS_BIT_NV
			12.���VkPhysicalDeviceOpticalFlowPropertiesNV::bidirectionalFlowSupported ��ΪVK_FALSE����flags �в�������VK_OPTICAL_FLOW_SESSION_CREATE_BOTH_DIRECTIONS_BIT_NV
			*/


			vkCreateOpticalFlowSessionNV(device, &opticalFlowSessionCreateInfoNV, nullptr, &opticalFlowSessionNV);

			//����һ�� Optical Flow Session �μ�p3651
			vkDestroyOpticalFlowSessionNV(device, opticalFlowSessionNV, nullptr);
		}


		//Binding Vulkan Image Views to an Optical Flow Session  �μ�p3651
		{
			VkOpticalFlowSessionBindingPointNV opticalFlowSessionBindingPointNV = VK_OPTICAL_FLOW_SESSION_BINDING_POINT_INPUT_NV;// VkOpticalFlowSessionBindingPointNV ֵ��ָ����Ҫ�󶨵�image view����;
			/*
			VkOpticalFlowSessionBindingPointNV:
			VK_OPTICAL_FLOW_SESSION_BINDING_POINT_INPUT_NV : ָ��input frame�İ󶨵�
			VK_OPTICAL_FLOW_SESSION_BINDING_POINT_REFERENCE_NV : ָ��input reference frame �İ󶨵�.
			VK_OPTICAL_FLOW_SESSION_BINDING_POINT_HINT_NV : ָ����Ϊ optional external hint flow vectors.
			VK_OPTICAL_FLOW_SESSION_BINDING_POINT_FLOW_VECTOR_NV : ָ��Ĭ��forward flow�����output flow vectors�İ󶨵�.
			VK_OPTICAL_FLOW_SESSION_BINDING_POINT_BACKWARD_FLOW_VECTOR_NV : ָ��optional backward flow�����optional output flow vector map �İ󶨵�
			VK_OPTICAL_FLOW_SESSION_BINDING_POINT_COST_NV : ָ��Ĭ��forward flow�����optional output cost map �İ󶨵�.
			VK_OPTICAL_FLOW_SESSION_BINDING_POINT_BACKWARD_COST_NV : ָ��optional backward flow�����optional output cost map �İ󶨵�.
			VK_OPTICAL_FLOW_SESSION_BINDING_POINT_GLOBAL_FLOW_NV : ָ��Ĭ��forward flow�����optional global flow value �İ󶨵�.

			*/
			
			vkBindOpticalFlowSessionImageNV(device, opticalFlowSessionNV, opticalFlowSessionBindingPointNV, VkImageView{/*��������һ����Ч��VkImageView*/ }, VK_IMAGE_LAYOUT_GENERAL);
		}



		//Optical Flow Execution  �μ�p3653
		{
			/*
			flow���Ƶ�Ĭ�Ϸ���������ģ��������˴�����֡���ο�֡�Ĺ�������ѡ��������㷴��flow���ơ������������Vx��Vy����ָ�����ڲο�֡��λ�ã�x+Vx��y+Vy�����ҵ�����֡�ĵ�ǰ����(x��y����������������Vx��Vy����ʾ������֡��λ�ã�x+Vx��y+Vy�������ҵ��ο�֡�ĵ�ǰ���أ�x��y����
			�򵥽����Ǽ���ͬһ�����ڲ�֮ͬ֡�������λ���Լ�λ����������Ϣ��
			*/

			//��������input frame֮���optical flow vectors
			VkOpticalFlowExecuteInfoNV opticalFlowExecuteInfoNV{};
			opticalFlowExecuteInfoNV.sType = VK_STRUCTURE_TYPE_OPTICAL_FLOW_EXECUTE_INFO_NV;
			opticalFlowExecuteInfoNV.pNext = nullptr;
			opticalFlowExecuteInfoNV.flags = VK_OPTICAL_FLOW_EXECUTE_DISABLE_TEMPORAL_HINTS_BIT_NV;/*Ϊ������ʹ�õ� VkOpticalFlowExecuteFlagsNV 
			VkOpticalFlowExecuteFlagBitsNV:
			VK_OPTICAL_FLOW_EXECUTE_DISABLE_TEMPORAL_HINTS_BIT_NV : ָ��֮ǰflow vectors���ɵ�temporal hints ����ʹ�á����temporal hints ��������vkCmdOpticalFlowExecuteNV������Զ�ʹ��֮ǰ��optical flow vectors��Ϊhints����������Ƶ�����е�ʱ������ԡ����֮ǰ��flow vectorsû��ʱ������ԣ���temporal hintsӦ�ùرա�	
			*/
			opticalFlowExecuteInfoNV.regionCount = 1;// pRegions ��Ԫ�ظ��������VkOpticalFlowSessionNV ����ʱû��ָ�� VK_OPTICAL_FLOW_SESSION_CREATE_ALLOW_REGIONS_BIT_NV�������Ϊ0
			VkRect2D region{ .offset = VkOffset2D{.x = 0,.y = 0},.extent = VkExtent2D{.width = 1,.height = 1} };
			opticalFlowExecuteInfoNV.pRegions = &region;// pRegions ��һ�� VkRect2D ����ָ�룬����ָ������Ȥ����



			vkCmdOpticalFlowExecuteNV(VkCommandBuffer{/*��������һ����Ч��VkCommandBuffer*/ }, opticalFlowSessionNV, & opticalFlowExecuteInfoNV);



		}
	}

}

void OpticalFlowAndExcutionGraphsAndLowLatencyTest::ExecutionGraphsTest()
{
	/*
	execution graphs�ṩ��һ�ַ���������host�˵�һ�������Ϸ������������Ϊ��֧����һ��Ϊ��ʵ���ṩ��һ���µ�graph pipeline����pipeline�����pipeline ����sheder��������������ÿ��pipeline����shader ������һ��������������Щpipeline����shader��Ϊgraph execution node�����Ա�����shader��̬����ִ�С�
	
	*/

	VkPipeline graphPipeline{};

	//Pipeline Creation  �μ�p3657
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
		executionGraphPipelineCreateInfoAMDX.sType = VK_STRUCTURE_TYPE_MAX_ENUM;//û�ж�����������Ϊ�Ƿ�ֵ
		executionGraphPipelineCreateInfoAMDX.pNext = nullptr;
		executionGraphPipelineCreateInfoAMDX.flags = VK_PIPELINE_CREATE_DISABLE_OPTIMIZATION_BIT;// VkPipelineCreateFlagBits ���ֵλ���룬ָ��pipeline��β���
		executionGraphPipelineCreateInfoAMDX.stageCount = 1;//pStages ��Ԫ�ظ���

		VkPipelineShaderStageCreateInfo pipelineShaderStageCreateInfo{/*��������һ����Ч��VkPipelineShaderStageCreateInfo*/ };//pNext�п��԰���VkPipelineShaderStageNodeCreateInfoAMDX ָ����node�������Լ�����
		{
			pipelineShaderStageCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
			VkPipelineShaderStageNodeCreateInfoAMDX pipelineShaderStageNodeCreateInfoAMDX{};
			{
				pipelineShaderStageNodeCreateInfoAMDX.sType = VK_STRUCTURE_TYPE_MAX_ENUM;//û�ж������ﶨ��Ϊ�Ƿ�ֵ
				pipelineShaderStageNodeCreateInfoAMDX.pNext = nullptr;
				pipelineShaderStageNodeCreateInfoAMDX.index = 0;//Ϊ����execution graph ��nodeʱshader ʹ�õ����������ΪVK_SHADER_INDEX_UNUSED_AMDX ���shaderʹ��ԭʼ������ShaderIndexAMDX execution modeָ������Ϊ0��
				pipelineShaderStageNodeCreateInfoAMDX.pName = "name";//Ϊ����execution graph ��nodeʱshader ʹ�õ����֡����ΪNULL����ʹ�� SPIR-V��������ڵ�entry point����

			}
			pipelineShaderStageCreateInfo.pNext = &pipelineShaderStageNodeCreateInfoAMDX;

		}
		executionGraphPipelineCreateInfoAMDX.pStages = &pipelineShaderStageCreateInfo;//һ��VkPipelineShaderStageCreateInfo ����ָ�룬���������ڸ� execution graph pipeline�е�shader stage
		VkPipelineLibraryCreateInfoKHR pipelineLibraryCreateInfoKHR{/*��������һ����Ч��VkPipelineLibraryCreateInfoKHR*/ };//һ�� VkPipelineLibraryCreateInfoKHR ָ�������������pipeline libraries
		executionGraphPipelineCreateInfoAMDX.pLibraryInfo = &pipelineLibraryCreateInfoKHR;
		executionGraphPipelineCreateInfoAMDX.layout = VkPipelineLayout{/*��������һ����Ч��VkPipelineLayout*/ };//ΪVkPipelineLayout���������ͬʱ����pipeline�Լ�descriptor sets�İ󶨵���Ϣ
		executionGraphPipelineCreateInfoAMDX.basePipelineHandle = VkPipeline{/*��������һ����Ч��VkPipeline*/ };//VkPipeline �����ָ�����ĸ�pipeline������
		executionGraphPipelineCreateInfoAMDX.basePipelineIndex = 0;////һ�� pCreateInfos��Ԫ�ص�������ָ�����ĸ�pipeline������
		/*
		VkExecutionGraphPipelineCreateInfoAMDX��Ч�÷�:
		1.���pNext�в�����VkPipelineCreateFlags2CreateInfoKHR�ڣ���flags������һ����Ч��VkPipelineCreateFlagBits���ֵ
		2.���flags ����VK_PIPELINE_CREATE_DERIVATIVE_BIT����1�����basePipelineIndexΪ-1����basePipelineHandle ������һ����Ч��execution graph VkPipeline ���
														   ��2�����basePipelineHandleΪVK_NULL_HANDLE����basePipelineIndex ������һ����Ч��pCreateInfos ��Ԫ�ص�����
														   ��3��basePipelineIndex ����Ϊ-1 ����basePipelineHandle ����ΪVK_NULL_HANDLE����������һ��
		3.���shader��������push constant block����layout�е�push constant range ����ͬʱ����shader stage�Լ� range
		4.���shader��������resource variables����1��layout�е�descriptor slot ����ƥ��shader stage
												��2�������descriptor ���Ͳ�ΪVK_DESCRIPTOR_TYPE_MUTABLE_EXT����layout�е�descriptor slot ����ƥ��descriptor ����
		5.���shader��������resource variablesΪarray��layout�е�descriptor slot ����ƥ��descriptor count
		6.flags���ܰ���VK_PIPELINE_CREATE_RAY_TRACING_NO_NULL_ANY_HIT_SHADERS_BIT_KHR�� VK_PIPELINE_CREATE_RAY_TRACING_NO_NULL_CLOSEST_HIT_SHADERS_BIT_KHR��
								VK_PIPELINE_CREATE_RAY_TRACING_NO_NULL_MISS_SHADERS_BIT_KHR��VK_PIPELINE_CREATE_RAY_TRACING_NO_NULL_INTERSECTION_SHADERS_BIT_KHR��
								VK_PIPELINE_CREATE_RAY_TRACING_SKIP_TRIANGLES_BIT_KHR��VK_PIPELINE_CREATE_RAY_TRACING_SKIP_AABBS_BIT_KHR��
								VK_PIPELINE_CREATE_RAY_TRACING_SHADER_GROUP_HANDLE_CAPTURE_REPLAY_BIT_KHR �Լ�VK_PIPELINE_CREATE_RAY_TRACING_ALLOW_MOTION_BIT_NV
		7.���VkPhysicalDeviceDeviceGeneratedCommandsComputeFeaturesNV::deviceGeneratedComputePipelinesδ��������flags ���ܰ���VK_PIPELINE_CREATE_INDIRECT_BINDABLE_BIT_NV
		8.���flags����VK_PIPELINE_CREATE_INDIRECT_BINDABLE_BIT_NV����pNext�б������һ��VkComputePipelineIndirectBufferInfoNV��ָ����pipeline��metadata�������ڵ�ַ
		9.���pipelineCreationCacheControl ����δ��������flags���ܰ���VK_PIPELINE_CREATE_FAIL_ON_PIPELINE_COMPILE_REQUIRED_BIT ����VK_PIPELINE_CREATE_EARLY_RETURN_ON_FAILURE_BIT
		10.pStages �е��κ�Ԫ�ص�stage����ΪVK_SHADER_STAGE_COMPUTE_BIT
		11.pStages ��Ԫ�ض�Ӧ��shader code�������pipeline ���ӹ��򣬼�p1394 Shader Interfaces
		12.layout �����pStages ��shader��layoutһ��
		13.���pLibraryInfo ��ΪNULL����pLibraries�е�ÿ��Ԫ�ر�����һ���͸�pipeline��layout���ݵĲ��ִ���
		14.��pipeline��ÿ��shader stage�ɷ��ʵ�layout����Դ��������С�ڵ���VkPhysicalDeviceLimits::maxPerStageResources
		15.���pLibraryInfo ��ΪNULL��pLibraryInfo->libraries��ÿ��Ԫ�ر���Ϊcompute pipeline����execution graph pipeline
		16.pipeline�в���������shader������ͬ�������Լ���������VkPipelineShaderStageNodeCreateInfoAMDX��ָ���Ĳ���
		17.pipeline�в���������shader������ͬ�������Һ���ͬ��С��input payload����
		18.pipeline�в���������shader������ͬ�����Ƶ�����ͬ��execution models
		19.pipeline�в���������shader������ͬ������������һ������CoalescedInputCountAMDX������һ��������
		20.pipeline�в���������shader������ͬ������������һ������StaticNumWorkgroupsAMDX������һ��������
		21.���pipeline���κ�shader������ output payload ����һ��Node Name��graph pipeline������node��shader ����ƥ���PayloadNodeNameAMDX����output payload�Ĵ�С�������ƥ���Ǹ�ƥ��node��input payload�Ĵ�С
		*/



		//����execution graph pipelines
		vkCreateExecutionGraphPipelinesAMDX(device, VkPipelineCache{/*��������һ����Ч��VkPipelineCache*/ }, 1, & executionGraphPipelineCreateInfoAMDX, nullptr, & graphPipeline);
		/*
		vkCreateExecutionGraphPipelinesAMDX��Ч�÷�:
		1.shaderEnqueue ���Ա��뿪��
		2.���pCreateInfos��Ԫ�ص�flags ����VK_PIPELINE_CREATE_DERIVATIVE_BIT����1����Ԫ�ص�basePipelineIndex��Ϊ-1�����Ԫ�ص�basePipelineIndex����С�ڸ�Ԫ����pCreateInfos�е�����
																				 ��2�����Ԫ�ص�basePipelineHandle���Ե�base pipeline ������VK_PIPELINE_CREATE_ALLOW_DERIVATIVES_BIT ����
		3.���pipelineCache ��VK_PIPELINE_CACHE_CREATE_EXTERNALLY_SYNCHRONIZED_BIT ������host�˶�pipelineCache�ķ��ʱ������ⲿͬ����

		*/



		//һ��node�������ڴ���ʱ��͹̶��ˣ����������Ƕ�̬�ģ���execution graph��һ�����ֿ��Զ�Ӧ���������ֻ��Ҫ��֤��graph�����ֺ����������ԣ���Ӧһ���ڲ���������Ψһ�Ϳ���
		//��ѯgraph��ָ��node���ڲ�����
		uint32_t nodeIndex = 0;
		::VkPipelineShaderStageNodeCreateInfoAMDX pipelineShaderStageNodeCreateInfoAMDX{};
		pipelineShaderStageNodeCreateInfoAMDX.sType = VK_STRUCTURE_TYPE_MAX_ENUM;
		pipelineShaderStageNodeCreateInfoAMDX.pNext = nullptr;
		pipelineShaderStageNodeCreateInfoAMDX.pName = "queryName";
		pipelineShaderStageNodeCreateInfoAMDX.index = 0;

		vkGetExecutionGraphPipelineNodeIndexAMDX(device, graphPipeline, &pipelineShaderStageNodeCreateInfoAMDX, &nodeIndex/*pNodeIndex�����ز�ѯ������*/);
		/*
		vkGetExecutionGraphPipelineNodeIndexAMDX��Ч�÷�:
		1.pNodeInfo->pName ����ΪNULL
		2.pNodeInfo->index ����ΪVK_SHADER_INDEX_UNUSED_AMDX
		3.executionGraph �б�����һ������ƥ��pNodeInfo->pName������ƥ��pNodeInfo->index��node
		*/

	}

	VkCommandBuffer commandBuffer{/*��������һ����Ч��VkCommandBuffer*/ };

	//Initializing Scratch Memory  �μ�p3665
	{
		//ʵ����Ҫscratch memory ������ dispatch queues

		//��ѯ�ɷ�һ�� execution graph ��Ҫ�� scratch space
		VkExecutionGraphPipelineScratchSizeAMDX executionGraphPipelineScratchSizeAMDX{};
		executionGraphPipelineScratchSizeAMDX.size = VK_STRUCTURE_TYPE_MAX_ENUM;//û�ж�����������Ϊ�Ƿ�ֵ
		executionGraphPipelineScratchSizeAMDX.pNext = nullptr;
		executionGraphPipelineScratchSizeAMDX.size = 0;//ָ���ɷ�һ�� execution graph ��Ҫ�� scratch space��С

		vkGetExecutionGraphPipelineScratchSizeAMDX(device, graphPipeline, &executionGraphPipelineScratchSizeAMDX);



		//��ʼ��ָ�� execution graph��scratch memory ,scratch ������ vkCmdDispatchGraphAMDX, vkCmdDispatchGraphIndirectAMDX, vkCmdDispatchGraphIndirectCountAMDX,���� vkCmdInitializeGraphScratchMemoryAMDX ����ǰ���³�ʼ��
		vkCmdInitializeGraphScratchMemoryAMDX(commandBuffer, VkDeviceAddress{/*��������һ����Ч��VkDeviceAddress*/ }/*scratch, ָ��Ҫ��ʼ����scratch���ڴ��ַ*/);
		/*
		vkCmdInitializeGraphScratchMemoryAMDX��Ч�÷�:
		1.scratch ������һ����С����Ϊ����VkExecutionGraphPipelineScratchSizeAMDX����󶨵�execution graph���ص�VkExecutionGraphPipelineScratchSizeAMDX::size���ڴ��ַ
		2.scratch ������64�ı���
		*/
		

	}

	//Dispatching a Graph  �μ�p3668
	{
		VkDeviceAddress scratch{/*��������һ����Ч��VkDeviceAddress*/ };

		//��¼�ɷ�һ�� execution graph   ,scratch��VK_PIPELINE_STAGE_2_COMPUTE_SHADER_BIT pipeline stageͬ������VK_ACCESS_2_SHADER_STORAGE_READ_BIT �Լ� VK_ACCESS_2_SHADER_STORAGE_WRITE_BIT���з���
		VkDispatchGraphCountInfoAMDX dispatchGraphCountInfoAMDX{};
		dispatchGraphCountInfoAMDX.count = 1;//ָ��infos�� VkDispatchGraphInfoAMDX �ĸ���
		dispatchGraphCountInfoAMDX.stride = 64;//ָ��infos������ VkDispatchGraphInfoAMDX ֮ǰ���ֽڲ���
		VkDispatchGraphInfoAMDX dispatchGraphInfoAMDX{};
		{
			dispatchGraphInfoAMDX.nodeIndex = 0;//Ϊexecution graph���ɷ���node������
			dispatchGraphInfoAMDX.payloadCount = 1;//Ϊָ��node�ɷ���payloads������������С��maxExecutionGraphShaderPayloadCount
			dispatchGraphInfoAMDX.payloads = VkDeviceOrHostAddressConstAMDX{/* .deviceAddress = 0,Ϊ���� vkGetBufferDeviceAddressKHR���ص�һ����ַ */.hostAddress = 0 /*Ϊhost�˵ĵ�ַ*/ };//Ϊ��СΪpayloadCount * payloadStride��device����host�˵�ַ������payloads��������
			dispatchGraphInfoAMDX.payloadStride = 64;//Ϊ payloads������payload֮����ֽڲ���
		}
		dispatchGraphCountInfoAMDX.infos = VkDeviceOrHostAddressConstAMDX{/* .deviceAddress = 0,Ϊ���� vkGetBufferDeviceAddressKHR���ص�һ����ַ */.hostAddress = 0 /*Ϊhost�˵ĵ�ַ*/ };//Ϊ���� VkDispatchGraphInfoAMDX �����device����host�˵�ַ

		vkCmdDispatchGraphAMDX(commandBuffer, scratch, &dispatchGraphCountInfoAMDX);
		/*
		vkCmdDispatchGraphAMDX��Ч�÷�:
		1.���һ��VkSampler����magFilter����minFilter����VK_FILTER_LINEAR��������1�����reductionModeΪVK_SAMPLER_REDUCTION_MODE_WEIGHTED_AVERAGE��������ڲ���һ��VkImageView��Ϊ������Ľ����compareEnableΪVK_FALSE�����image view��format features�������VK_FORMAT_FEATURE_SAMPLED_IMAGE_FILTER_LINEAR_BIT
																				 ��2�����reductionModeΪVK_SAMPLER_REDUCTION_MODE_MIN ����VK_SAMPLER_REDUCTION_MODE_MAX֮һ ���ڲ���һ��VkImageView��Ϊ������Ľ�������image view��format features�������VK_FORMAT_FEATURE_SAMPLED_IMAGE_FILTER_MINMAX_BIT
		2.���һ��VkSampler����mipmapMode ����VK_SAMPLER_MIPMAP_MODE_LINEAR��������1�����reductionModeΪVK_SAMPLER_REDUCTION_MODE_WEIGHTED_AVERAGE��������ڲ���һ��VkImageView��Ϊ������Ľ����compareEnableΪVK_FALSE�����image view��format features�������VK_FORMAT_FEATURE_SAMPLED_IMAGE_FILTER_LINEAR_BIT
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
																												   ��2������Ƕ�ȡ��reference image��ָ����reference coordinates������integer texel coordinate validation ʱ��ʧ��
		52.���OpImageWeightedSampleQCOM, OpImageBoxFilterQCOM, OpImageBlockMatchWindowSSDQCOM, OpImageBlockMatchWindowSADQCOM, OpImageBlockMatchGatherSSDQCOM,
													OpImageBlockMatchGatherSADQCOM, OpImageBlockMatchSSDQCOM, ���� OpImageBlockMatchSADQCOM��������һ����Ϊ������Ľ����VkImageView�����VkSampler������VK_SAMPLER_CREATE_IMAGE_PROCESSING_BIT_QCOM����
		53.����κγ���OpImageWeightedSampleQCOM, OpImageBoxFilterQCOM, OpImageBlockMatchWindowSSDQCOM, OpImageBlockMatchWindowSADQCOM, OpImageBlockMatchGatherSSDQCOM, OpImageBlockMatchGatherSADQCOM, OpImageBlockMatchSSDQCOM, ���� OpImageBlockMatchSADQCOM֮���ָ��ʹ��VkSampler���в�����Ϊ������Ľ�������sampler������VK_SAMPLER_CREATE_IMAGE_PROCESSING_BIT_QCOM ����
		54.���OpImageBlockMatchWindow*QCOM or OpImageBlockMatchGather*QCOMָ��������ȡVkImageView��Ϊ������Ľ������1��VkImageView��format features�������VK_FORMAT_FEATURE_2_BLOCK_MATCHING_BIT_QCOM
																													  ��2��VkImageView��format����ֻ����һ��component
		55.���OpImageBlockMatchWindow*QCOM or OpImageBlockMatchGather*QCOMָ��������ȡһ�����õ�image��Ϊ������Ľ������ָ���� reference coordinates������integer texel coordinate validation ʱ��ʧ��
		56.�κθ�����ִ�е�shader invocation�����Ѿ���ֹ
		57.�����һ������λΪVK_DESCRIPTOR_TYPE_SAMPLE_WEIGHT_IMAGE_QCOM, VK_DESCRIPTOR_TYPE_BLOCK_MATCH_IMAGE_QCOM, VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE, VK_DESCRIPTOR_TYPE_STORAGE_IMAGE, ���� VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT������һ����descriptor��Ϊ������Ľ�����з��ʣ����descriptor��ָ��image subresource��layout����͸�descriptor��д��ʱ��layout��ͬ��
		
		58.commandBuffer ����Ϊһ��protected command buffer������Ϊһ��primary command buffer
		59.scratch �����Ǵ�С����Ϊ����VkExecutionGraphPipelineScratchSizeAMDX����󶨵� execution graph���ص�VkExecutionGraphPipelineScratchSizeAMDX::size���ڴ��ַ
		60.scratch ��������VK_BUFFER_USAGE_EXECUTION_GRAPH_SCRATCH_BIT_AMDX ����VK_BUFFER_USAGE_2_EXECUTION_GRAPH_SCRATCH_BIT_AMDX������VkBuffer���豸��ַ
		61.[scratch,scratch + VkExecutionGraphPipelineScratchSizeAMDX::size) �ڵ��ڴ�����Ѿ�ʹ�õ�ǰ�󶨵�execution graph����vkCmdInitializeGraphScratchMemoryAMDX���г�ʼ���ˣ��Ҳ��ܱ�����execution graph��dispatch command ����
		62.�������ִ�в��ܵ���һ��node��һ��workgroups�������������node�е�MaxNumWorkgroupsAMDX ����maxComputeWorkGroupCount ָ�������ɷ�
		63.�������ִ�в��ܵ����κ�shader��ʼ������maxExecutionGraphShaderPayloadCount�� output payloads
		64.�������ִ�в��ܵ����κ�������NodeMaxPayloadsAMDX�� shader��ʼ������������ָ����payloads������������������Ӧ�õ�ÿ��NodeMaxPayloadsAMDX ������
		65.pCountInfo->infos ������һ��hostָ�룬ָ��һ����С����Ϊcount * stride ���ڴ�
		66.[infos, infos + (count*stride)) �еĵ�ַ��strideΪ���ȣ�ÿ��������ǰ24�ֽڱ��������Ч��VkDispatchGraphInfoAMDX 
		67.��pCountInfo->infos�е�ÿ��VkDispatchGraphInfoAMDX����1����payloads������һ��host�˵�ָ�룬ָ���С����Ϊ payloadCount * payloadStride���ڴ��ַ
															   ��2����nodeIndex ������һ���ڵ�ǰ����vkGetExecutionGraphPipelineNodeIndexAMDX����󶨵�execution graph pipeline�з��ص���Ч��node ����
															   ��3����ָ���host��ַ��Χ[payloads, payloads + (payloadCount * payloadStride))����payloadStride Ϊ���ȣ����������ʼ���ֽڱ������һ��payload����payload�Ĵ�Сƥ��nodeIndex��ָ��node������input payload�Ĵ�С

		*/


		//��¼�ɷ�һ�� execution graph,����node�Լ�payload������device�ж�ȡ   ,scratch��VK_PIPELINE_STAGE_2_COMPUTE_SHADER_BIT pipeline stageͬ������VK_ACCESS_2_SHADER_STORAGE_READ_BIT �Լ� VK_ACCESS_2_SHADER_STORAGE_WRITE_BIT���з���
		vkCmdDispatchGraphIndirectAMDX(commandBuffer, scratch, &dispatchGraphCountInfoAMDX);
		/*
		vkCmdDispatchGraphIndirectAMDX��Ч�÷�:
		1.���һ��VkSampler����magFilter����minFilter����VK_FILTER_LINEAR��������1�����reductionModeΪVK_SAMPLER_REDUCTION_MODE_WEIGHTED_AVERAGE��������ڲ���һ��VkImageView��Ϊ������Ľ����compareEnableΪVK_FALSE�����image view��format features�������VK_FORMAT_FEATURE_SAMPLED_IMAGE_FILTER_LINEAR_BIT
																				 ��2�����reductionModeΪVK_SAMPLER_REDUCTION_MODE_MIN ����VK_SAMPLER_REDUCTION_MODE_MAX֮һ ���ڲ���һ��VkImageView��Ϊ������Ľ�������image view��format features�������VK_FORMAT_FEATURE_SAMPLED_IMAGE_FILTER_MINMAX_BIT
		2.���һ��VkSampler����mipmapMode ����VK_SAMPLER_MIPMAP_MODE_LINEAR��������1�����reductionModeΪVK_SAMPLER_REDUCTION_MODE_WEIGHTED_AVERAGE��������ڲ���һ��VkImageView��Ϊ������Ľ����compareEnableΪVK_FALSE�����image view��format features�������VK_FORMAT_FEATURE_SAMPLED_IMAGE_FILTER_LINEAR_BIT
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
																												   ��2������Ƕ�ȡ��reference image��ָ����reference coordinates������integer texel coordinate validation ʱ��ʧ��
		52.���OpImageWeightedSampleQCOM, OpImageBoxFilterQCOM, OpImageBlockMatchWindowSSDQCOM, OpImageBlockMatchWindowSADQCOM, OpImageBlockMatchGatherSSDQCOM,
													OpImageBlockMatchGatherSADQCOM, OpImageBlockMatchSSDQCOM, ���� OpImageBlockMatchSADQCOM��������һ����Ϊ������Ľ����VkImageView�����VkSampler������VK_SAMPLER_CREATE_IMAGE_PROCESSING_BIT_QCOM����
		53.����κγ���OpImageWeightedSampleQCOM, OpImageBoxFilterQCOM, OpImageBlockMatchWindowSSDQCOM, OpImageBlockMatchWindowSADQCOM, OpImageBlockMatchGatherSSDQCOM, OpImageBlockMatchGatherSADQCOM, OpImageBlockMatchSSDQCOM, ���� OpImageBlockMatchSADQCOM֮���ָ��ʹ��VkSampler���в�����Ϊ������Ľ�������sampler������VK_SAMPLER_CREATE_IMAGE_PROCESSING_BIT_QCOM ����
		54.���OpImageBlockMatchWindow*QCOM or OpImageBlockMatchGather*QCOMָ��������ȡVkImageView��Ϊ������Ľ������1��VkImageView��format features�������VK_FORMAT_FEATURE_2_BLOCK_MATCHING_BIT_QCOM
																													  ��2��VkImageView��format����ֻ����һ��component
		55.���OpImageBlockMatchWindow*QCOM or OpImageBlockMatchGather*QCOMָ��������ȡһ�����õ�image��Ϊ������Ľ������ָ���� reference coordinates������integer texel coordinate validation ʱ��ʧ��
		56.�κθ�����ִ�е�shader invocation�����Ѿ���ֹ
		57.�����һ������λΪVK_DESCRIPTOR_TYPE_SAMPLE_WEIGHT_IMAGE_QCOM, VK_DESCRIPTOR_TYPE_BLOCK_MATCH_IMAGE_QCOM, VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE, VK_DESCRIPTOR_TYPE_STORAGE_IMAGE, ���� VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT������һ����descriptor��Ϊ������Ľ�����з��ʣ����descriptor��ָ��image subresource��layout����͸�descriptor��д��ʱ��layout��ͬ��
		
		58.commandBuffer ����Ϊһ��protected command buffer������Ϊһ��primary command buffer
		59.scratch �����Ǵ�С����Ϊ����VkExecutionGraphPipelineScratchSizeAMDX����󶨵� execution graph���ص�VkExecutionGraphPipelineScratchSizeAMDX::size���ڴ��ַ
		60.scratch ��������VK_BUFFER_USAGE_EXECUTION_GRAPH_SCRATCH_BIT_AMDX ����VK_BUFFER_USAGE_2_EXECUTION_GRAPH_SCRATCH_BIT_AMDX������VkBuffer���豸��ַ
		61.[scratch,scratch + VkExecutionGraphPipelineScratchSizeAMDX::size) �ڵ��ڴ�����Ѿ�ʹ�õ�ǰ�󶨵�execution graph����vkCmdInitializeGraphScratchMemoryAMDX���г�ʼ���ˣ��Ҳ��ܱ�����execution graph��dispatch command ����
		62.�������ִ�в��ܵ���һ��node��һ��workgroups�������������node�е�MaxNumWorkgroupsAMDX ����maxComputeWorkGroupCount ָ�������ɷ�
		63.�������ִ�в��ܵ����κ�shader��ʼ������maxExecutionGraphShaderPayloadCount�� output payloads
		64.�������ִ�в��ܵ����κ�������NodeMaxPayloadsAMDX�� shader��ʼ������������ָ����payloads������������������Ӧ�õ�ÿ��NodeMaxPayloadsAMDX ������
		65.pCountInfo->infos ������һ��deviceָ�룬����������device��ִ�е�ʱ�����ָ��һ����С����Ϊcount * stride ���ڴ�
		66.pCountInfo->infos ������һ����VK_BUFFER_USAGE_INDIRECT_BUFFER_BIT������VkBuffer��device��ַ
		67.pCountInfo->infos ������executionGraphDispatchAddressAlignment�ı���
		68.[infos, infos + (count*stride)) �е�device��ַ��strideΪ���ȣ��ڸ�������device�����е�ʱ��ÿ��������ǰ24�ֽڱ��������Ч��VkDispatchGraphInfoAMDX
		69.��pCountInfo->infos�е�ÿ��VkDispatchGraphInfoAMDX����1����payloads������һ��device�˵�ָ�룬�ڸ�������device�����е�ʱ��ָ���С����Ϊ payloadCount * payloadStride���ڴ��ַ
															   ��2����payloads������һ��device�˵�ָ�룬�ڸ�������device�����е�ʱ��ָ��һ����VK_BUFFER_USAGE_INDIRECT_BUFFER_BIT ������VkBuffer���ڴ��ַ
															   ��3����payloads ������executionGraphDispatchAddressAlignment �ı���
															   ��4���ڸ�������device�����е�ʱ����nodeIndex ������һ���ڵ�ǰ����vkGetExecutionGraphPipelineNodeIndexAMDX����󶨵�execution graph pipeline�з��ص���Ч��node ����
															   ��5���ڸ�������device�����е�ʱ����ָ���device��ַ��Χ[payloads, payloads + (payloadCount * payloadStride))����payloadStride Ϊ���ȣ����������ʼ���ֽڱ������һ��payload����payload�Ĵ�Сƥ��nodeIndex��ָ��node������input payload�Ĵ�С


		*/


		//��¼�ɷ�һ�� execution graph,�������в�����device�ж�ȡ   ,scratch��VK_PIPELINE_STAGE_2_COMPUTE_SHADER_BIT pipeline stageͬ������VK_ACCESS_2_SHADER_STORAGE_READ_BIT �Լ� VK_ACCESS_2_SHADER_STORAGE_WRITE_BIT���з���
		vkCmdDispatchGraphIndirectCountAMDX(commandBuffer, scratch, VkDeviceAddress{/*��������һ����Ч��VkDeviceAddress*/ }/*countInfo, һ��VkDispatchGraphCountInfoAMDX�ṹ���device��ַ������Ҫ��ִ�е�nodes*/);
		/*
		vkCmdDispatchGraphIndirectCountAMDX��Ч�÷�:
		1.���һ��VkSampler����magFilter����minFilter����VK_FILTER_LINEAR��������1�����reductionModeΪVK_SAMPLER_REDUCTION_MODE_WEIGHTED_AVERAGE��������ڲ���һ��VkImageView��Ϊ������Ľ����compareEnableΪVK_FALSE�����image view��format features�������VK_FORMAT_FEATURE_SAMPLED_IMAGE_FILTER_LINEAR_BIT
																				 ��2�����reductionModeΪVK_SAMPLER_REDUCTION_MODE_MIN ����VK_SAMPLER_REDUCTION_MODE_MAX֮һ ���ڲ���һ��VkImageView��Ϊ������Ľ�������image view��format features�������VK_FORMAT_FEATURE_SAMPLED_IMAGE_FILTER_MINMAX_BIT
		2.���һ��VkSampler����mipmapMode ����VK_SAMPLER_MIPMAP_MODE_LINEAR��������1�����reductionModeΪVK_SAMPLER_REDUCTION_MODE_WEIGHTED_AVERAGE��������ڲ���һ��VkImageView��Ϊ������Ľ����compareEnableΪVK_FALSE�����image view��format features�������VK_FORMAT_FEATURE_SAMPLED_IMAGE_FILTER_LINEAR_BIT
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
																												   ��2������Ƕ�ȡ��reference image��ָ����reference coordinates������integer texel coordinate validation ʱ��ʧ��
		52.���OpImageWeightedSampleQCOM, OpImageBoxFilterQCOM, OpImageBlockMatchWindowSSDQCOM, OpImageBlockMatchWindowSADQCOM, OpImageBlockMatchGatherSSDQCOM,
													OpImageBlockMatchGatherSADQCOM, OpImageBlockMatchSSDQCOM, ���� OpImageBlockMatchSADQCOM��������һ����Ϊ������Ľ����VkImageView�����VkSampler������VK_SAMPLER_CREATE_IMAGE_PROCESSING_BIT_QCOM����
		53.����κγ���OpImageWeightedSampleQCOM, OpImageBoxFilterQCOM, OpImageBlockMatchWindowSSDQCOM, OpImageBlockMatchWindowSADQCOM, OpImageBlockMatchGatherSSDQCOM, OpImageBlockMatchGatherSADQCOM, OpImageBlockMatchSSDQCOM, ���� OpImageBlockMatchSADQCOM֮���ָ��ʹ��VkSampler���в�����Ϊ������Ľ�������sampler������VK_SAMPLER_CREATE_IMAGE_PROCESSING_BIT_QCOM ����
		54.���OpImageBlockMatchWindow*QCOM or OpImageBlockMatchGather*QCOMָ��������ȡVkImageView��Ϊ������Ľ������1��VkImageView��format features�������VK_FORMAT_FEATURE_2_BLOCK_MATCHING_BIT_QCOM
																													  ��2��VkImageView��format����ֻ����һ��component
		55.���OpImageBlockMatchWindow*QCOM or OpImageBlockMatchGather*QCOMָ��������ȡһ�����õ�image��Ϊ������Ľ������ָ���� reference coordinates������integer texel coordinate validation ʱ��ʧ��
		56.�κθ�����ִ�е�shader invocation�����Ѿ���ֹ
		57.�����һ������λΪVK_DESCRIPTOR_TYPE_SAMPLE_WEIGHT_IMAGE_QCOM, VK_DESCRIPTOR_TYPE_BLOCK_MATCH_IMAGE_QCOM, VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE, VK_DESCRIPTOR_TYPE_STORAGE_IMAGE, ���� VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT������һ����descriptor��Ϊ������Ľ�����з��ʣ����descriptor��ָ��image subresource��layout����͸�descriptor��д��ʱ��layout��ͬ��

		58.commandBuffer ����Ϊһ��protected command buffer������Ϊһ��primary command buffer
		59.scratch �����Ǵ�С����Ϊ����VkExecutionGraphPipelineScratchSizeAMDX����󶨵� execution graph���ص�VkExecutionGraphPipelineScratchSizeAMDX::size���ڴ��ַ
		60.scratch ��������VK_BUFFER_USAGE_EXECUTION_GRAPH_SCRATCH_BIT_AMDX ����VK_BUFFER_USAGE_2_EXECUTION_GRAPH_SCRATCH_BIT_AMDX������VkBuffer���豸��ַ
		61.[scratch,scratch + VkExecutionGraphPipelineScratchSizeAMDX::size) �ڵ��ڴ�����Ѿ�ʹ�õ�ǰ�󶨵�execution graph����vkCmdInitializeGraphScratchMemoryAMDX���г�ʼ���ˣ��Ҳ��ܱ�����execution graph��dispatch command ����
		62.�������ִ�в��ܵ���һ��node��һ��workgroups�������������node�е�MaxNumWorkgroupsAMDX ����maxComputeWorkGroupCount ָ�������ɷ�
		63.�������ִ�в��ܵ����κ�shader��ʼ������maxExecutionGraphShaderPayloadCount�� output payloads
		64.�������ִ�в��ܵ����κ�������NodeMaxPayloadsAMDX�� shader��ʼ������������ָ����payloads������������������Ӧ�õ�ÿ��NodeMaxPayloadsAMDX ������

		65.����������device��ִ��ʱ��countInfo ������һ���ڴ����һ��VkDispatchGraphCountInfoAMDX���ڴ��ַ
		66..countInfo ������һ����VK_BUFFER_USAGE_INDIRECT_BUFFER_BIT������VkBuffer��device��ַ
		67.countInfo ������executionGraphDispatchAddressAlignment�ı���
		68.countInfo->infos ������һ��deviceָ�룬����������device��ִ�е�ʱ�����ָ��һ����С����Ϊcount * stride ���ڴ�
		69.countInfo->infos ������һ����VK_BUFFER_USAGE_INDIRECT_BUFFER_BIT������VkBuffer��device��ַ
		70.countInfo->infos ������executionGraphDispatchAddressAlignment�ı���
		71.[infos, infos + (count*stride)) �е�device��ַ��strideΪ���ȣ��ڸ�������device�����е�ʱ��ÿ��������ǰ24�ֽڱ��������Ч��VkDispatchGraphInfoAMDX
		69.��countInfo->infos�е�ÿ��VkDispatchGraphInfoAMDX����1����payloads������һ��device�˵�ָ�룬�ڸ�������device�����е�ʱ��ָ���С����Ϊ payloadCount * payloadStride���ڴ��ַ
															   ��2����payloads������һ��device�˵�ָ�룬�ڸ�������device�����е�ʱ��ָ��һ����VK_BUFFER_USAGE_INDIRECT_BUFFER_BIT ������VkBuffer���ڴ��ַ
															   ��3����payloads ������executionGraphDispatchAddressAlignment �ı���
															   ��4���ڸ�������device�����е�ʱ����nodeIndex ������һ���ڵ�ǰ����vkGetExecutionGraphPipelineNodeIndexAMDX����󶨵�execution graph pipeline�з��ص���Ч��node ����
															   ��5���ڸ�������device�����е�ʱ����ָ���device��ַ��Χ[payloads, payloads + (payloadCount * payloadStride))����payloadStride Ϊ���ȣ����������ʼ���ֽڱ������һ��payload����payload�Ĵ�Сƥ��nodeIndex��ָ��node������input payload�Ĵ�С
		
		*/

	}


	//Shader Enqueue  �μ�p3669
	{
		//һ��shader����˶�payload��д���ʼ����node payload������Щpayload�ͻ������ӽ����ɷ���

		//Compute Nodes  �򵥽�������Ϊnode��compute shader����StaticNumWorkgroupsAMDX ���� CoalescingAMDX execution modes ���ֲ�ͬ��ִ�з�ʽ.  ����μ�p3699
	}

}


void OpticalFlowAndExcutionGraphsAndLowLatencyTest::LowLatency2Test()
{
	//Latency Reduction  �μ�p3701
	{
		VkSwapchainKHR swapchainKHR{/*��������һ����Ч��VkSwapChainKHR*/ };

		//����swapchain�ϵ� low latency mode
		VkLatencySleepModeInfoNV latencySleepModeInfoNV{};
		latencySleepModeInfoNV.sType = VK_STRUCTURE_TYPE_LATENCY_SLEEP_MODE_INFO_NV;
		latencySleepModeInfoNV.pNext = nullptr;
		latencySleepModeInfoNV.lowLatencyMode = VK_TRUE;//ָ���Ƿ���low latency mode
		latencySleepModeInfoNV.lowLatencyBoost = VK_TRUE;//����Ӧ����ʾGPU����������������ߵ��������������Ӷ�latency�Ľ�ʡ
		latencySleepModeInfoNV.minimumIntervalUs = 1;//�Ƕ����õ�swapchain��vkQueuePresentKHR����֮��ĺ�����

		vkSetLatencySleepModeNV(device, swapchainKHR, &latencySleepModeInfoNV);


		//�ṩͬ��ԭ�������ӳ� lower latency��host CPU work
		VkLatencySleepInfoNV latencySleepInfoNV{};
		latencySleepInfoNV.sType = VK_STRUCTURE_TYPE_LATENCY_SLEEP_INFO_NV;
		latencySleepInfoNV.pNext = nullptr;
		latencySleepInfoNV.signalSemaphore = VkSemaphore{/*��������һ����Ч��VkSemaphore*/ };//��һ��Ҫ������semaphoreָ��Ӧ��Ӧ������input sampling work������Ϊһ��timeline semaphore
		latencySleepInfoNV.value = 0;//ָ������sampling work �� signalSemaphore��ֵ

		vkLatencySleepNV(device, swapchainKHR, &latencySleepInfoNV);



		//Ӧ���ڲ���frame�Ĳ�ͬ�׶��ṩ��ʱ���
		VkSetLatencyMarkerInfoNV setLatencyMarkerInfoNV{};
		setLatencyMarkerInfoNV.sType = VK_STRUCTURE_TYPE_SET_LATENCY_MARKER_INFO_NV;
		setLatencyMarkerInfoNV.pNext = nullptr;
		setLatencyMarkerInfoNV.presentID = 0;//Ϊ�û��ṩ��һ��ֵ�����ڽ�ʱ���������һ��vkQueuePresentKHR �����ӦVkPresentIdKHR::pPresentIds�е�
		setLatencyMarkerInfoNV.marker = VK_LATENCY_MARKER_INPUT_SAMPLE_NV;//VkLatencyMarkerNVֵ��Ϊ��¼��ʱ���������
		/*
		VkLatencyMarkerNV:
		VK_LATENCY_MARKER_SIMULATION_START_NV : Ӧ����ÿ��frame��simulationִ�п�ʼ֮ǰ���ã��õ���֮��ΪvkLatencySleepNV
		VK_LATENCY_MARKER_SIMULATION_END_NV : Ӧ����ÿ��frame��simulationִ�н���ʱ����
		VK_LATENCY_MARKER_RENDERSUBMIT_START_NV : Ӧ����ÿ��frame����Ⱦ�ύִ�п�ʼʱ���ã����������첽��Ⱦ
		VK_LATENCY_MARKER_RENDERSUBMIT_END_NV : Ӧ����ÿ��frame����Ⱦ�ύִ�н���ʱ����
		VK_LATENCY_MARKER_PRESENT_START_NV : Ӧ����vkQueuePresentKHR ֮ǰ����
		VK_LATENCY_MARKER_PRESENT_END_NV : Ӧ����vkQueuePresentKHR ����ʱ����
		VK_LATENCY_MARKER_INPUT_SAMPLE_NV : Ӧ����Ӧ�û�ȡinput����֮ǰ����
		VK_LATENCY_MARKER_TRIGGER_FLASH_NV : Ӧ���ڵ�һ�������ʱ�䷢��ʱ��VK_LATENCY_MARKER_SIMULATION_START_NV �Լ� VK_LATENCY_MARKER_SIMULATION_END_NV֮����κ�ʱ�����

		*/

		vkSetLatencyMarkerNV(device, swapchainKHR, &setLatencyMarkerInfoNV);


		//��ȡһ���������µ� latency���ݵ�����
		std::vector<VkLatencyTimingsFrameReportNV> latencyTimingsFrameReportNVs{};

		VkGetLatencyMarkerInfoNV getLatencyMarkerInfoNV{};
		getLatencyMarkerInfoNV.sType = VK_STRUCTURE_TYPE_GET_LATENCY_MARKER_INFO_NV;
		getLatencyMarkerInfoNV.pNext = nullptr;
		getLatencyMarkerInfoNV.timingCount = 0;//Ϊ���õĻ����Ѿ���ѯ���� latency data��������ǰframe������
		getLatencyMarkerInfoNV.pTimings = nullptr;//ΪNULL���� VkLatencyTimingsFrameReportNV ����ָ��

		vkGetLatencyTimingsNV(device, swapchainKHR, &getLatencyMarkerInfoNV);
		latencyTimingsFrameReportNVs.resize(getLatencyMarkerInfoNV.timingCount);
		getLatencyMarkerInfoNV.pTimings = latencyTimingsFrameReportNVs.data();

		vkGetLatencyTimingsNV(device, swapchainKHR, &getLatencyMarkerInfoNV);//����ɹ�������һ�����

		VkLatencyTimingsFrameReportNV &latencyTimingsFrameReportNV = latencyTimingsFrameReportNVs[0];
		latencyTimingsFrameReportNV.sType = VK_STRUCTURE_TYPE_LATENCY_TIMINGS_FRAME_REPORT_NV;
		latencyTimingsFrameReportNV.pNext = nullptr;
		latencyTimingsFrameReportNV.presentID = 0;//Ϊ�û��ṩ��һ��ֵ�����ڽ�ʱ���������һ��vkQueuePresentKHR �����ӦVkPresentIdKHR::pPresentIds�е�
		latencyTimingsFrameReportNV.inputSampleTimeUs = 0;//Ϊ����vkSetLatencyMarkerNV����ΪVK_LATENCY_MARKER_INPUT_SAMPLE_NVʱ���ص�ʱ�����ֵ
		latencyTimingsFrameReportNV.simStartTimeUs = 0;//Ϊ����vkSetLatencyMarkerNV����Ϊ VK_LATENCY_MARKER_SIMULATION_START_NVʱ���ص�ʱ�����ֵ
		latencyTimingsFrameReportNV.simEndTimeUs = 0;//Ϊ����vkSetLatencyMarkerNV����Ϊ  VK_LATENCY_MARKER_SIMULATION_END_NVʱ���ص�ʱ�����ֵ
		latencyTimingsFrameReportNV.renderSubmitStartTimeUs = 0;//Ϊ����vkSetLatencyMarkerNV����Ϊ  VK_LATENCY_MARKER_RENDERSUBMIT_START_NVʱ���ص�ʱ�����ֵ
		latencyTimingsFrameReportNV.renderSubmitEndTimeUs = 0;//Ϊ����vkSetLatencyMarkerNV����Ϊ VK_LATENCY_MARKER_RENDERSUBMIT_END_NVʱ���ص�ʱ�����ֵ
		latencyTimingsFrameReportNV.presentStartTimeUs = 0;//Ϊ����vkSetLatencyMarkerNV����Ϊ VK_LATENCY_MARKER_PRESENT_START_NVʱ���ص�ʱ�����ֵ
		latencyTimingsFrameReportNV.presentEndTimeUs = 0;//Ϊ����vkSetLatencyMarkerNV����ΪVK_LATENCY_MARKER_PRESENT_END_NVʱ���ص�ʱ�����ֵ
		latencyTimingsFrameReportNV.driverStartTimeUs = 0;//Ϊ��frame�ĵ�һ��vkQueueSubmit����ʱ���ص�ʱ�����ֵ
		latencyTimingsFrameReportNV.driverEndTimeUs = 0;//ΪVulkan Driver�ϴ�������һ�� vkQueueSubmit������󷵻ص�ʱ�����ֵ
		latencyTimingsFrameReportNV.osRenderQueueStartTimeUs = 0;//ΪVulkan Driver�ϴ�������һ�� vkQueueSubmit������󷵻ص�ʱ�����ֵ
		latencyTimingsFrameReportNV.osRenderQueueEndTimeUs = 0;//Ϊ��һ���ύ�ִ�GPUʱ���ص�ʱ�����ֵ
		latencyTimingsFrameReportNV.gpuRenderStartTimeUs = 0;//Ϊ��һ���ύ�ִ�GPUʱ���ص�ʱ�����ֵ
		latencyTimingsFrameReportNV.gpuRenderEndTimeUs = 0;//Ϊ��frame��GPU�ϵ����һ���ύ���ʱ���ص�ʱ�����ֵ


		VkLatencySubmissionPresentIdNV latencySubmissionPresentIdNV{};//����vkQueueSubmit
		latencySubmissionPresentIdNV.sType = VK_STRUCTURE_TYPE_LATENCY_SUBMISSION_PRESENT_ID_NV;
		latencySubmissionPresentIdNV.pNext = nullptr;
		latencySubmissionPresentIdNV.presentID = 0;//���ڽ�vkQueueSubmit ������һ��֮ǰ��vkQueuePresentKHR ��ͨ����Ӧ��VkPresentIdKHR::pPresentIds�е�ֵ.


		//Ӧ�ÿ��Ա��һ��queue Ϊ Out of Band�ģ������� latency evaluationʱ���� �ڸö�����ִ�е�vkQueueSubmit�ᱻ����
		VkOutOfBandQueueTypeInfoNV outOfBandQueueTypeInfoNV{};
		outOfBandQueueTypeInfoNV.sType = VK_STRUCTURE_TYPE_OUT_OF_BAND_QUEUE_TYPE_INFO_NV;
		outOfBandQueueTypeInfoNV.pNext = nullptr;
		outOfBandQueueTypeInfoNV.queueType = VK_OUT_OF_BAND_QUEUE_TYPE_PRESENT_NV;//VkOutOfBandQueueTypeNVֵ��ָ�����ΪOut of Band��queue����;
		/*
		VkOutOfBandQueueTypeNV:
		VK_OUT_OF_BAND_QUEUE_TYPE_RENDER_NV : ָ����work�ᱻ�ύ����queue
		VK_OUT_OF_BAND_QUEUE_TYPE_PRESENT_NV : ָ����queue������present

		*/

		vkQueueNotifyOutOfBandNV(VkQueue{/*��������һ����Ч��VkQueue*/ }, &outOfBandQueueTypeInfoNV);



		//���� low latency mode ����swapchain����VkSwapchainCreateInfoKHR.pNext�а���һ��VkSwapchainLatencyCreateInfoNV
		VkSwapchainLatencyCreateInfoNV swapchainLatencyCreateInfoNV{};
		swapchainLatencyCreateInfoNV.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_LATENCY_CREATE_INFO_NV;
		swapchainLatencyCreateInfoNV.pNext = nullptr;
		swapchainLatencyCreateInfoNV.latencyModeEnable = VK_TRUE;//ָ��������swapchain�Ƿ�ʹ��low latency mode


		VkLatencySurfaceCapabilitiesNV  latencySurfaceCapabilitiesNV{};//�ýṹ�����ڷ����Ż�������low latency mode�� present mode
		latencySurfaceCapabilitiesNV.sType = VK_STRUCTURE_TYPE_LATENCY_SURFACE_CAPABILITIES_NV;
		latencySurfaceCapabilitiesNV.pNext = nullptr;
		latencySurfaceCapabilitiesNV.presentModeCount = 1;//ΪpPresentModes ��Ԫ�ظ���
		VkPresentModeKHR presenModeKHR = VK_PRESENT_MODE_MAILBOX_KHR;
		latencySurfaceCapabilitiesNV.pPresentModes = &presenModeKHR;//һ��VkPresentModeKHR ����ָ�룬ָ���ṩ������low latency mode���Ż���present mode
	}


}


NS_TEST_END