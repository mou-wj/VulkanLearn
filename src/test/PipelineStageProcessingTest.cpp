#include "PipelineStageProcessingTest.h"
NS_TEST_BEGIN
PipelineStageProcessingTest::PipelineStageProcessingTest()
{
}

void PipelineStageProcessingTest::run()
{
}

PipelineStageProcessingTest::~PipelineStageProcessingTest()
{
}

void PipelineStageProcessingTest::VertexProcessingFixedFunctionTest()
{
	// Vertex Attributes 参见p2582 
	{
		/*
		描述顶点属性
		顶点属性和vertex shader的输入变量相关联
		
		定义input variable的vertex shader可以从绑定的一个或多个buffer中获取顶点属性数据。

		顶点输入属性和顶点输入绑定描述包含格式信息，它控制了如何从缓冲区内存中提取数据并转换为顶点着色器所期望的格式。顶点属性以及绑定限制: VkPhysicalDeviceLimits::maxVertexInputAttributes, VkPhysicalDeviceLimits::maxVertexInputBindings
		
		例如，在GLSL中
		// Assign location M to variableName
		layout (location=M, component=2) in vec2 variableName;
		// Assign locations [N,N+L) to the array elements of variableNameArray
		layout (location=N) in vec4 variableNameArray[L];

		SPIR-V实例见p2582

		*/


		//Attribute Location 以及 Component Assignment  参见p2582
		{
			/*
			Location指明shader 输入变量使用哪一个 vertex input attribute，在vertex input attribute中从哪个分量开始获取数据由Component指定
			
			向量的 具体见p2582的  表Input attribute components accessed by 16-bit and 32-bit input variables
			
			矩阵的 具体见p2584的 表Input attributes accessed by 32-bit input matrix variables    ，矩阵每一列占据一个Location，这些行之间的Location连续
			
			如果向量类型为64-bit的  具体见p2585  表Input attribute locations and components accessed by 64-bit input variables

			*/
		}



		//Vertex Input Description 参见p2586
		{
			/*
			应用指定顶点属性信息以及绑定信息通过设置到VkGraphicsPipelineCreateInfo::pVertexInputState的VkPipelineVertexInputStateCreateInfo指针来指定。如果开启VK_DYNAMIC_STATE_VERTEX_INPUT_EXT，则通过命令 vkCmdSetVertexInputEXT动态指定
			*/

			VkPipelineVertexInputStateCreateInfo pipelineVertexInputStateCreateInfo{};
			pipelineVertexInputStateCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
			//
			VkPipelineVertexInputDivisorStateCreateInfoKHR pipelineVertexInputDivisorStateCreateInfoKHR{};
			{
				pipelineVertexInputDivisorStateCreateInfoKHR.sType = VK_STRUCTURE_TYPE_MAX_ENUM;//没有定义所以定义成非法值
				pipelineVertexInputDivisorStateCreateInfoKHR.pNext = nullptr;
				pipelineVertexInputDivisorStateCreateInfoKHR.vertexBindingDivisorCount = 1;
				VkVertexInputBindingDivisorDescriptionKHR vertexInputBindingDivisorDescriptionKHR{};
				{
					vertexInputBindingDivisorDescriptionKHR.binding = 0;
					vertexInputBindingDivisorDescriptionKHR.divisor = 2;
				}
				pipelineVertexInputDivisorStateCreateInfoKHR.pVertexBindingDivisors = &vertexInputBindingDivisorDescriptionKHR;
			}
			pipelineVertexInputStateCreateInfo.pNext = nullptr;//可以包含一个VkPipelineVertexInputDivisorStateCreateInfoKHR
			pipelineVertexInputStateCreateInfo.flags = 0;//保留未来使用
			pipelineVertexInputStateCreateInfo.vertexAttributeDescriptionCount = 1;//pVertexAttributeDescriptions中 vertex binding descriptions的数量
			VkVertexInputAttributeDescription vertexInputAttributeDescription{};	
			{
				vertexInputAttributeDescription.format = VK_FORMAT_R32G32_SINT;// 是vertex attribute数据的类型以及大小描述
				vertexInputAttributeDescription.location = 0;//是shader中input变量对应该attribute的location编号
				vertexInputAttributeDescription.binding = 0;//指定binding的编号，该编号指定使用绑定到哪个binding上的顶点缓冲区数据
				vertexInputAttributeDescription.offset = 0;//是该attribute相对于绑定的顶点数据输入中基于一个元素的开头的内部字节偏移量。
				/*
				VkVertexInputAttributeDescription有效用法:
				1.location必须小于VkPhysicalDeviceLimits::maxVertexInputAttributes
				2.binding必须小于VkPhysicalDeviceLimits::maxVertexInputBindings
				3.offset必须小于等于VkPhysicalDeviceLimits::maxVertexInputAttributeOffset
				4.format的format features必须包含VK_FORMAT_FEATURE_VERTEX_BUFFER_BIT
				5.如果VK_KHR_portability_subset 拓展开启，且VkPhysicalDevicePortabilitySubsetFeaturesKHR::vertexAttributeAccessBeyondStride为VK_FALSE，则offset 加上format描述的vertex attribute 数据的大小
							必须小于等于binding对应的VkVertexInputBindingDescription中的stride		
				*/
			}
			pipelineVertexInputStateCreateInfo.pVertexAttributeDescriptions = &vertexInputAttributeDescription;//一组 VkVertexInputBindingDescription数组指针
			pipelineVertexInputStateCreateInfo.vertexBindingDescriptionCount = 1;//pVertexBindingDescriptions中 vertex binding description的数量
			VkVertexInputBindingDescription vertexInputBindingDescription{};
			{
				vertexInputBindingDescription.binding = 0;//指定binding的编号
				vertexInputBindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;//是一个VkVertexInputRate值指明是否vertex attribute地址是顶点索引或者是instance索引的函数
				/*
				VkVertexInputRate:
				VK_VERTEX_INPUT_RATE_VERTEX:  指明vertex arribute地址是顶点索引的函数
				VK_VERTEX_INPUT_RATE_INSTANCE:   指明vertex arribute地址是instance索引的函数				
				*/
				vertexInputBindingDescription.stride = 3;//指明buffer中两个连续元素之间的字节步长
				/*
				VkVertexInputBindingDescription有效用法:
				1.binding必须小于VkPhysicalDeviceLimits::maxVertexInputBindings
				2.stride必须小于等于VkPhysicalDeviceLimits::maxVertexInputBindingStride
				3.如果VK_KHR_portability_subset 拓展开启，则stride必须至少是VkPhysicalDevicePortabilitySubsetPropertiesKHR::minVertexInputBindingStrideAlignment的倍数

				*/
			}
			pipelineVertexInputStateCreateInfo.pVertexBindingDescriptions = &vertexInputBindingDescription;//一组VkVertexInputBindingDescription数组指针
			/*
			VkPipelineVertexInputStateCreateInfo有效用法:
			1.vertexBindingDescriptionCount必须小于等于VkPhysicalDeviceLimits::maxVertexInputBindings
			2.vertexAttributeDescriptionCount必须小于等于VkPhysicalDeviceLimits::maxVertexInputAttributes
			3.对pVertexAttributeDescriptions中每个binding，必须在pVertexBindingDescriptions中有一个VkVertexInputBindingDescription的bingding与之对应
			4.pVertexBindingDescriptions中所有元素必须描述不同的binding
			5.pVertexAttributeDescriptions中所有元素必须描述不同的 attribute locations
			
			*/
		
		}
	}


}


NS_TEST_END