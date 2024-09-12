#include "OpticalFlowAndExcutionGraphsAndLowLatencyTest.h"
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


NS_TEST_END