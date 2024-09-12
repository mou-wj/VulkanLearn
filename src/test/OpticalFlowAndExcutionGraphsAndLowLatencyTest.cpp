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


NS_TEST_END