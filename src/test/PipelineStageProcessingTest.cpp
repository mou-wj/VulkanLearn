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

void PipelineStageProcessingTest::FixedFunctionVertexProcessingTest()
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
			//VkPipelineVertexInputStateCreateInfo.pNext
			VkPipelineVertexInputDivisorStateCreateInfoKHR pipelineVertexInputDivisorStateCreateInfoKHR{};//等价于VkPipelineVertexInputDivisorStateCreateInfoEXT
			{
				pipelineVertexInputDivisorStateCreateInfoKHR.sType = VK_STRUCTURE_TYPE_MAX_ENUM;//没有定义所以定义成非法值
				pipelineVertexInputDivisorStateCreateInfoKHR.pNext = nullptr;
				pipelineVertexInputDivisorStateCreateInfoKHR.vertexBindingDivisorCount = 1;// pVertexBindingDivisors中元素个数
				VkVertexInputBindingDivisorDescriptionKHR vertexInputBindingDivisorDescriptionKHR{};//等价于VkVertexInputBindingDivisorDescriptionEXT
				{
					vertexInputBindingDivisorDescriptionKHR.binding = 0;//指定binding的编号
					vertexInputBindingDivisorDescriptionKHR.divisor = 2;//指定一组使用相同vertex attribute数据的连续instances，要求instanced rendering开启，除非vertexAttributeInstanceRateDivisor特性开启，否则该值必须设置为1，例如如果设置为N，则在移动到下一个vertex attribute数据之前，该vertex attribute数据将应用到N个连续的instances,如果 vertexAttributeInstanceRateZeroDivisor 特性开启，则可以设置为0，表示该vertex attribute数据将应用到所有instances，该值的最大值限制参考 VkPhysicalDeviceVertexAttributeDivisorPropertiesEXT::maxVertexAttribDivisor
					/*
					VkVertexInputBindingDivisorDescriptionKHR有效用法:
					1.binding必须小于VkPhysicalDeviceLimits::maxVertexInputBindings
					2.如果vertexAttributeInstanceRateZeroDivisor 特性没开启，则divisor不能为0
					3.如果vertexAttributeInstanceRateDivisor 特性没开启，则divisor必须为1
					4.divisor必须在0到VkPhysicalDeviceVertexAttributeDivisorPropertiesEXT::maxVertexAttribDivisor之间
					5.如果divisor 不为1，则inputRate必须是VK_VERTEX_INPUT_RATE_INSTANCE
					*/
				}
				pipelineVertexInputDivisorStateCreateInfoKHR.pVertexBindingDivisors = &vertexInputBindingDivisorDescriptionKHR;//一组VkVertexInputBindingDivisorDescriptionKHR数组指针，指明每个binding的divisor值
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
		


			//动态设置 vertex input attribute 以及 vertex input binding descriptions
			{

				VkCommandBuffer commandBuffer{/*假设这是一个有效的VkCommandBuffer*/ };

				VkVertexInputBindingDescription2EXT vertexInputBindingDescription2EXT{};
				vertexInputBindingDescription2EXT.sType = VK_STRUCTURE_TYPE_VERTEX_INPUT_BINDING_DESCRIPTION_2_EXT;
				vertexInputBindingDescription2EXT.pNext = nullptr;
				vertexInputBindingDescription2EXT.binding = 0;//指定binding的编号
				vertexInputBindingDescription2EXT.stride = 3;//指明buffer中两个连续元素之间的字节步长
				vertexInputBindingDescription2EXT.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;//是一个VkVertexInputRate值指明是否vertex attribute地址是顶点索引或者是instance索引的函数
				vertexInputBindingDescription2EXT.divisor = 1;//指定一组使用相同vertex attribute数据的连续instances，要求instanced rendering开启，除非vertexAttributeInstanceRateDivisor特性开启，否则该值必须设置为1，例如如果设置为N，则在移动到下一个vertex attribute数据之前，该vertex attribute数据将应用到N个连续的instances,如果 vertexAttributeInstanceRateZeroDivisor 特性开启，则可以设置为0，表示该vertex attribute数据将应用到所有instances，该值的最大值限制参考 VkPhysicalDeviceVertexAttributeDivisorPropertiesEXT::maxVertexAttribDivisor
				/*
				VkVertexInputBindingDescription2EXT有效用法:
				1.binding必须小于VkPhysicalDeviceLimits::maxVertexInputBindings
				2.stride必须小于等于VkPhysicalDeviceLimits::maxVertexInputBindingStride
				3.如果vertexAttributeInstanceRateZeroDivisor 特性没开启，则divisor不能为0
				4.如果vertexAttributeInstanceRateDivisor 特性没开启，则divisor必须为1
				5.divisor必须在0到VkPhysicalDeviceVertexAttributeDivisorPropertiesEXT::maxVertexAttribDivisor之间
				6.如果divisor 不为1，则inputRate必须是VK_VERTEX_INPUT_RATE_INSTANCE

				*/

				VkVertexInputAttributeDescription2EXT vertexInputAttributeDescription2EXT{};
				vertexInputAttributeDescription2EXT.sType = VK_STRUCTURE_TYPE_VERTEX_INPUT_ATTRIBUTE_DESCRIPTION_2_EXT;
				vertexInputAttributeDescription2EXT.pNext = nullptr;
				vertexInputAttributeDescription2EXT.location = 0;//是shader中input变量对应该attribute的location编号
				vertexInputAttributeDescription2EXT.binding = 0;//指定binding的编号，该编号指定使用绑定到哪个binding上的顶点缓冲区数据
				vertexInputAttributeDescription2EXT.format = VK_FORMAT_R32G32_SINT;// 是vertex attribute数据的类型以及大小描述
				vertexInputAttributeDescription2EXT.offset = 0;//是该attribute相对于绑定的顶点数据输入中基于一个元素的开头的内部字节偏移量。
				/*
				VkVertexInputAttributeDescription2EXT有效用法:
				1.location必须小于VkPhysicalDeviceLimits::maxVertexInputAttributes
				2.binding必须小于VkPhysicalDeviceLimits::maxVertexInputBindings
				3.offset必须小于等于VkPhysicalDeviceLimits::maxVertexInputAttributeOffset
				4.format的format features必须包含VK_FORMAT_FEATURE_VERTEX_BUFFER_BIT
				5.如果VK_KHR_portability_subset 拓展开启，且VkPhysicalDevicePortabilitySubsetFeaturesKHR::vertexAttributeAccessBeyondStride为VK_FALSE，则offset 加上format描述的vertex attribute 数据的大小
							必须小于等于binding对应的VkVertexInputBindingDescriptionEXT中的stride



				*/

				//设置vertex input attribute 以及 vertex input binding descriptions，只在开启了VK_DYNAMIC_STATE_VERTEX_INPUT_EXT的情况下有效，如果绘制使用 shader objects，且绑定的pipeline state object以VK_DYNAMIC_STATE_VERTEX_INPUT_BINDING_STRIDE创建，则vkCmdBindVertexBuffers2 可以用来动态设置stride
				vkCmdSetVertexInputEXT(commandBuffer, 1/*vertexBindingDescriptionCount ，为pVertexBindingDescriptions中元素个数.*/, &vertexInputBindingDescription2EXT/*pVertexBindingDescriptions，一组VkVertexInputBindingDescription2EXT 数组指针，指明绑定信息.*/,
					1/*vertexAttributeDescriptionCount，为pVertexAttributeDescriptions元素个数.*/, &vertexInputAttributeDescription2EXT/*    > pVertexAttributeDescriptions，一组 VkVertexInputAttributeDescription2EXT 数组指针，指明属性信息.*/);
				/*
				vkCmdSetVertexInputEXT有效用法:
				1.vertexInputDynamicState 或者 shaderObject 特性至少有一个必须开启
				2.vertexBindingDescriptionCount 必须小于等于VkPhysicalDeviceLimits::maxVertexInputBindings
				3.vertexAttributeDescriptionCount 必须小于等于VkPhysicalDeviceLimits::maxVertexInputAttributes
				4.对pVertexAttributeDescriptions中每个binding，必须在pVertexBindingDescriptions中有一个VkVertexInputBindingDescription2EXT的bingding与之对应
				5.pVertexBindingDescriptions中所有元素必须描述不同的binding
				6.pVertexAttributeDescriptions中所有元素必须描述不同的 attribute locations

				*/

				VkBuffer vertexBuffer{/*假设这是一个有效的VkBuffer*/ };//假设这个buffer中存放顶点属性数据
				VkDeviceSize vertexBufferOffset = 0;//顶点属性数据在buffer中的偏移量

				//绑定顶点缓冲区到command buffer用于后续绘制命令使用    该命令将pBuffers对应pOffsets中偏移的数据绑定到[firstBinding,firstBinding + bindingCount]  ,如果 nullDescriptor 特性开启，则pBuffer中可以有元素为VK_NULL_HANDLE的情况，表示该binding的数据为[0,0,0,1]
				vkCmdBindVertexBuffers(commandBuffer, 0/*firstBinding,为该command更新的第一个顶点输入binding的索引号，和前面属性以及绑定描述中的binding等价*/, 1/*bindingCount，为该命令要更新的顶点输入binding的数量.*/,
					&vertexBuffer/*pBuffers，是VkBuffer句柄数组指针，指明绑定的顶点缓冲区.*/, &vertexBufferOffset/* pOffsets，为pBuffer中对应buffer的起始字节偏移.*/);
				/*
				vkCmdBindVertexBuffers有效用法:
				1.firstBinding 必须小于VkPhysicalDeviceLimits::maxVertexInputBindings
				2.firstBinding + bindingCount必须小于等于VkPhysicalDeviceLimits::maxVertexInputBindings
				3.pOffsets中所有元素必须小于对应pBuffers中的buffer元素大小
				4.pBuffers中的所有元素必须以VK_BUFFER_USAGE_VERTEX_BUFFER_BIT创建
				5.如果pBuffers的元素是non-sparse的，则该buffer必须已经绑定到完整的连续的单独的VkDeviceMemory对象上
				6.如果nullDescriptor特性未开启，则pBuffers所有元素不能为VK_NULL_HANDLE
				7.如果pBuffers中有元素为VK_NULL_HANDLE，则对应pOffsets中的值必须为0
				*/

				VkDeviceSize vertexBufferSize = 0;
				VkDeviceSize vertexBufferStride = 3;

				//绑定顶点缓冲区到command buffer，并且指定buffer大小的步长，用于后续绘制命令使用,等价于vkCmdBindVertexBuffers2EXT     该命令将pBuffers对应pOffsets中偏移的数据绑定到[firstBinding,firstBinding + bindingCount]，pSizes如果不为NULL则指定pBuffers中对应buffer的大小  ,如果 nullDescriptor 特性开启，则pBuffer中可以有元素为VK_NULL_HANDLE的情况，表示该binding的数据为[0,0,0,1]，如果使用shader objects绘制，或者绑定的pipeline以VK_DYNAMIC_STATE_VERTEX_INPUT_BINDING_STRIDE创建，则pStride如果不为NULL则指定pBuffers中对应buffer的步长
				vkCmdBindVertexBuffers2(commandBuffer, 0/*firstBinding,为该command更新的第一个顶点输入binding的索引号，和前面属性以及绑定描述中的binding等价*/, 1/*bindingCount，为该命令要更新的顶点输入binding的数量.*/,
					&vertexBuffer/*pBuffers，是VkBuffer句柄数组指针，指明绑定的顶点缓冲区.*/, &vertexBufferOffset/* pOffsets，为pBuffer中对应buffer的起始字节偏移.*/,
					&vertexBufferSize/*pSizes, 为NULL一组指定 pBuffers中绑定的顶点缓冲区buffer大小的值的数组指针.*/, &vertexBufferStride/*pStrides,为NULL 或者指定pBuffers中步长的值的数组指针.*/);
				/*
				vkCmdBindVertexBuffers2有效用法:
				1.firstBinding 必须小于VkPhysicalDeviceLimits::maxVertexInputBindings
				2.firstBinding + bindingCount必须小于等于VkPhysicalDeviceLimits::maxVertexInputBindings
				3.如果pSizes不为NULL，则（1）pOffsets中的所有元素必须小于对应pBuffers中的buffer大小
										（2）所有pOffsets 加上pSizes 中的对应元素，如果pSizes对应元素不为VK_WHOLE_SIZE，则该和必须小于等于对应pBuffers中的buffer大小
				4.pBuffers中的所有元素必须以VK_BUFFER_USAGE_VERTEX_BUFFER_BIT创建
				5.如果pBuffers的元素是non-sparse的，则该buffer必须已经绑定到完整的连续的单独的VkDeviceMemory对象上
				6.如果nullDescriptor特性未开启，则pBuffers所有元素不能为VK_NULL_HANDLE
				7.如果pBuffers中有元素为VK_NULL_HANDLE，则对应pOffsets中的值必须为0
				8.如果pStrides不为NULL，则（1）pStrides中的所有元素必须小于等于VkPhysicalDeviceLimits::maxVertexInputBindingStride
										  （2）pStrides中的元素必须是0或大于或等于对应binding中所有vertex input attribute的最大范围值，该最大范围为VkVertexInputAttributeDescription::offset + VkVertexInputAttributeDescription::format对应的大小

				*/

			}
		}



		//Vertex Attribute Divisor in Instanced Rendering  参见p2600
		/*
		如果vertexAttributeInstanceRateDivisor 特性开启，且VkPipelineVertexInputStateCreateInfo的pNext中包含一个 VkPipelineVertexInputDivisorStateCreateInfoKHR将控制vertex attribute数据如何分配到instanced rendering的instance中。

		相关的结构体直接见前面描述。
		*/



		//Vertex Input Address Calculation  参见p2601
		{
			/*
			bufferBindingAddress = buffer[binding].baseAddress + offset[binding];
			if (bindingDesc.inputRate == VK_VERTEX_INPUT_RATE_VERTEX)
			  effectiveVertexOffset = vertexIndex * stride;
			else
			  if (divisor == 0)
			 		effectiveVertexOffset = firstInstance * stride;
			  else
			 		effectiveVertexOffset = (firstInstance + ((instanceIndex - firstInstance) / divisor)) * stride;
			attribAddress = bufferBindingAddress + effectiveVertexOffset + attribDesc.offset;

			*/


			// Vertex Input Extraction 
			//vertex attribute的原始数据从attribAddress提取出来并按照VkVertexInputAttributeDescription.format转换成shader中的input变量,转换一些注意点参见p2602 
		}



	}


}

void PipelineStageProcessingTest::TessellationTest()
{
	/*
	Tessellation包含3个阶段: 
	1.tessellation control shader用patch中的点来产生per-patch数据
	2.fixed-function tessellator根据patch中参数空间（见p2602）中的(u,v) 或者 (u,v,w)坐标产生许多图元
	3.tessellation evaluation shader转换生成的图元中的点，例如计算相关的三维空间的点坐标以及属性数据等 

	tessallator需要pipeline同时包含tessellation control shader和tessellation evaluation shader情况下才启用
	*/


	//Tessellator 参见p2604
	{
		/*
		tessellator消耗一批输入，然后产生一组新的图元，产生的方式是通过tessellation control shader写出的 outer 以及 inner tessellation levels参数控制几何图元的图元细分操作完成的，如果没有tessallation shader，则该tessellator则不启用，即不对图元做任何操作
		
		细分的类型由 OpExecutionMode指令控制，指定一个 Triangles（将三角形图元细分成更小的三角图元）, Quads（将四边形图元细分成更小的三角图元）, 或者 IsoLines（将四边形图元细分成TessCoord在u维度上相同的线段的集合） execution modes等，如果使用shader objects，则必须在tessellation evaluation shader中指定该指令，如果使用pipeline，则可以在tessellation control shader或者tessellation evaluation shader之一中指定该指令,如果两个shader中都设置有该指令则必须相等

		Tessellation execution modes分类:
		Triangles, Quads, 以及 IsoLines:控制细分类型以及输出的图元拓扑，如果VK_KHR_portability_subset拓展未开启，且VkPhysicalDevicePortabilitySubsetFeaturesKHR::tessellationIsolines为VK_FALSE，则不能使用IsoLines

		VertexOrderCw 以及 VertexOrderCcw:控制tessallator产生的三角形的顶点顺序

		PointMode: 控制点图元的生成，如果VK_KHR_portability_subset拓展未开启，且VkPhysicalDevicePortabilitySubsetFeaturesKHR::tessellationPointMode为VK_FALSE，则不能使用 PointMode

		SpacingEqual, SpacingFractionalEven, 以及 SpacingFractionalOdd: 控制细分的图元的边上线段的间距

		OutputVertices: 控制tessellation control shader产生的 output patch的大小
		*/


	}


	//Tessellator Patch Discard 参见p2607


	//Tessellator Spacing 参见p2607
	{
		/*
		指定细分图元边上的段间距通过 SpacingEqual, SpacingFractionalEven, 或者 SpacingFractionalOdd指定
		SpacingEqual: 如果浮点tessellation level限制到[1,VkPhysicalDeviceLimits::maxTessellationGenerationLevel]中最近的整数为n，则该边在（u，v）参数空间中等分为n份
		SpacingFractionalEven以及 SpacingFractionalOdd，前者浮点tessellation level限制到[2,VkPhysicalDeviceLimits::maxTessellationGenerationLevel]中最近的整数为n，后者限制到[1,VkPhysicalDeviceLimits::maxTessellationGenerationLevel-1]中最近的整数n，将细分的边划分为n-2个等长的段和2个等长的段，其中2个等长的段（在细分边两端）和n-2个等长的段的长度存在关系，随着n-f单调减小，f为浮点tessellation level限定到范围内值
		*/
	}

	//Tessellation Primitive Ordering 参见p2608

	//Tessellator Vertex Winding Order 参见p2608
	{
		/*
		细分产生的三角图元的顶点顺序由VertexOrderCw 或者 VertexOrderCcw指定:
		VertexOrderCw: 指定在 (u,v) 或者 (u,v,w) 空间中顶点顺序为顺时针
		VertexOrderCcw: 指定在 (u,v) 或者 (u,v,w) 空间中顶点顺序为逆时针
		*/
	}


	//Triangle Tessellation    >>  三角形图元的三角形细分规则见p2609    简单讲就是每个边上的细分段数由三个outer tessellation levels（左边，底边，右边）指定，三角形顶点最近的两个边上的最近细分点基于边的垂线的延长线交点得到内三角形的顶点，其他细分点基于边的垂线交内三角的边得到内三角的细分点，然后选取三角的相邻的两个细分点作为三角形两个点和另外一个三角的对应顶点组装成三角形，不断重复该操作，直到内三角的细分段个数为1或2


	//Quad Tessellation    >>   四边形图元的三角形细分规则见p2611    简单讲就是根据第一个以及第二个inner tessellation level的限制值将四边形图元先划分为对应m * n个小矩形，然后将内部不和外部矩形相接的小矩形细分成三角对，内部的小矩形的全集看作是一个含有细分点的内矩形，然后在按照四个 outer tessellation levels的限定值将矩阵四条边（l,b,r,t）细分，然后选取一条边的相邻的两个细分点作为三角形两个点和另外一个矩形的对应顶点组装成三角形


	//Isoline Tessellation  >>   四边形图元的线细分规则p2613    简单讲就是画平行四边形图元底边的线段，画多少条由第一个outer tessellation level决定（等间隔画），每条上面多少的细分点由第一个outer tessellation level

	

	//Tessellation Point Mode  参见p2613


	//Tessellation Pipeline State  参见p2614
	{
		//VkGraphicsPipelineCreateInfo.pTessellationState指向的VkPipelineTessellationStateCreateInfo控制tessellation

		VkPipelineTessellationStateCreateInfo pipelineTessellationStateCreateInfo{};
		pipelineTessellationStateCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_TESSELLATION_STATE_CREATE_INFO;
		VkPipelineTessellationDomainOriginStateCreateInfo pipelineTessellationDomainOriginStateCreateInfo{};//等价于VkPipelineTessellationDomainOriginStateCreateInfoKHR，如果没有使用该结构体，则默认的原点为 VK_TESSELLATION_DOMAIN_ORIGIN_UPPER_LEFT,主要影响如何解释VertexOrderCw 以及 VertexOrderCcw的顶点顺序
		{
			pipelineTessellationDomainOriginStateCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_TESSELLATION_DOMAIN_ORIGIN_STATE_CREATE_INFO;
			pipelineTessellationDomainOriginStateCreateInfo.pNext = nullptr;
			pipelineTessellationDomainOriginStateCreateInfo.domainOrigin = VK_TESSELLATION_DOMAIN_ORIGIN_LOWER_LEFT;/*一个VkTessellationDomainOrigin值指明tessellation domain space的原点位置
			VkTessellationDomainOrigin:
			VK_TESSELLATION_DOMAIN_ORIGIN_UPPER_LEFT:  指明tessellation domain space的原点位置在左上角
			VK_TESSELLATION_DOMAIN_ORIGIN_LOWER_LEFT:  指明tessellation domain space的原点位置在左下角
			*/
		}
		pipelineTessellationStateCreateInfo.pNext = &pipelineTessellationDomainOriginStateCreateInfo;//可以包含一个VkPipelineTessellationDomainOriginStateCreateInfo
		pipelineTessellationStateCreateInfo.flags = 0;//保留未来使用
		pipelineTessellationStateCreateInfo.patchControlPoints = 1;//是每个patch的控制点个数，必须大于0小于等于VkPhysicalDeviceLimits::maxTessellationPatchSize
	
	
		//动态设置tessellation domain space的原点位置     该命令只有在pipeline开启了VK_DYNAMIC_STATE_TESSELLATION_DOMAIN_ORIGIN_EXT才有效，否则使用VkPipelineTessellationDomainOriginStateCreateInfo::domainOrigin
		vkCmdSetTessellationDomainOriginEXT(VkCommandBuffer{/*假设这是一个有效的VkCommandBuffer*/ }, VK_TESSELLATION_DOMAIN_ORIGIN_UPPER_LEFT/*domainOrigin ,指明tessellation domain space的原点位置*/);
	
	}

}

void PipelineStageProcessingTest::GeometryShadingTest()
{
	/*
	geomrtry shader操作一个图元上的顶点以及属性数据，然后发送零个或多个图元以及其顶点数据，只在pipeline中包含geometry shader才有效
	
	*/


	//Geometry Shader Input Primitives 参见p2618
	{
		/*
		geometry shader访问图元的顶点数据，该顶点数据以数组的方式组织

		输入图元的类型通过geometry shader中的OpExecutionMode指定,且图元必须和pipeline的图元拓扑（如何tessellation未启用）或者tessellation shader输出的图元拓扑匹配（如果tessellation启用）:

		如果输入类型为 InputPoints，则图元拓扑必须是VK_PRIMITIVE_TOPOLOGY_POINT_LIST
		
		如果输入类型为 InputLines，则图元拓扑必须是VK_PRIMITIVE_TOPOLOGY_LINE_LIST 或者 VK_PRIMITIVE_TOPOLOGY_LINE_STRIP
		
		如果输入类型为 InputLinesAdjacency，则图元拓扑必须是VK_PRIMITIVE_TOPOLOGY_LINE_LIST_WITH_ADJACENCY 或者 VK_PRIMITIVE_TOPOLOGY_LINE_STRIP_WITH_ADJACENCY.
		
		如果输入类型为 Triangles，则图元拓扑必须是VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST, VK_PRIMITIVE_TOPOLOGY_TRIANGLE_STRIP, 或者 VK_PRIMITIVE_TOPOLOGY_TRIANGLE_FAN

		如果输入类型为 InputTrianglesAdjacency，则图元拓扑必须是VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST_WITH_ADJACENCY 或者 VK_PRIMITIVE_TOPOLOGY_TRIANGLE_STRIP_WITH_ADJACENCY
		*/
	}


	// Geometry Shader Output Primitives  参见p2619
	{
		//geometry shader输出的图元类型为points, line strips, 或者 triangle strips，通过 OpExecutionMode指令来指明OutputPoints, OutputLineStrip 或者 OutputTriangleStrip,最大的顶点输出数量由OpExecutionMode设置 OutputVertices来指定
	}


	// Multiple Invocations of Geometry Shaders  参见p2619     对一个输入图元可以调用多次geometry shader


	// Geometry Shader Primitive Ordering  参见p2619


	// Geometry Shader Passthrough   参见p2619
	{
		//geometry shader的输入变量如果有以 PassthroughNV修饰的，则该geometry shader为一个直通的geometry shader，即输入的图元的拓扑类型不会改变且不会产生新的顶点
	
	
		//PassthroughNV Decoration  参见p2620
		{
			//以PassthroughNV修饰的输入变量将直接将对应顶点数据拷贝到输出图元中，如果不以PassthroughNV修饰的输入变量或者块则会被geometry shader消耗且不会传递到下一个管线阶段
		}

		// Passthrough Interface Matching  参见p2620
	}

}

void PipelineStageProcessingTest::MeshShaingTest()
{
	/*
	Task 以及 mesh shaders工作在workgroups中用于产生后续管线阶段可以处理的图元，如果开启task shader则每个task shader会创建一组新的mesh shader的workgroup来完成任务，每个mesh shader的workgroup根据该workgroup中的顶点数据产生零个或者多个图元以及顶点数据
	
	*/


	//Task Shader Input  参见p2622   输入只有builtin workgroup identifiers


	//Task Shader Output  参见p2622   
	{
		/*
		Task Shader输出零个或多个mesh workgroups，
		
		如果使用TaskNV Execution Model模型，则通过内置变量 TaskCountNV 来指定输出的mesh workgroup数量，且不能超过 VkPhysicalDeviceMeshShaderPropertiesNV::maxTaskOutputCount，mesh shader中可以访问以PerTaskNV 声明的task shader写出的变量
		
		如果使用TaskEXT Execution Model，则通过传递给 OpEmitMeshTasksEXT指令的 groupCountX, groupCountY以及groupCountZ 三者的乘积来指定输出的mesh workgroup数量，每个分量不能超过 VkPhysicalDeviceMeshShaderPropertiesEXT::maxMeshWorkGroupCount，乘积不能超过 VkPhysicalDeviceMeshShaderPropertiesEXT::maxMeshWorkGroupTotalCount.，mesh shader中可以访问传递给  OpEmitMeshTasksEXT指令的以 TaskPayloadWorkgroupEXT 声明的task shader写出的变量
		

		*/
	}

	// Mesh Generation  参见p2622  


	// Mesh Shader Input  参见p2622 

	// Mesh Shader Output  参见p2622 
	{
		/*
		mesh shader产生的图元类型为points, lines,或者 triangles

		如果使用MeshNV Execution Model模型，则图元类型通过带OutputPoints, OutputLinesNV, 或者 OutputTrianglesNV 的OpExecutionMode指令 ,最大顶点数通过带OutputVertices 的OpExecutionMode指令指定，且不能超过 VkPhysicalDeviceMeshShaderPropertiesNV::maxMeshOutputVertices，
						最大图元数通过带 OutputPrimitivesNV 的OpExecutionMode指令指定写入到PrimitiveCountNV中，且不能超过 VkPhysicalDeviceMeshShaderPropertiesNV::maxMeshOutputPrimitives
		
		如果使用MeshEXT Execution Model模型，则通过带OutputPoints, OutputLinesEXT, 或者 OutputTrianglesEXT 的OpExecutionMode指令  ,最大顶点数通过带OutputVertices 的OpExecutionMode指令指定，且不能超过 VkPhysicalDeviceMeshShaderPropertiesEXT::maxMeshOutputVertices，
						最大图元数通过带 OutputPrimitivesEXT 的OpExecutionMode指令指定调用 OpSetMeshOutputsEXT进行设置，且不能超过 VkPhysicalDeviceMeshShaderPropertiesEXT::maxMeshOutputPrimitives.
		*/
	}

	// Mesh Shader Per-View Outputs  参见p2624
	{
		/*
		mesh shader中以PositionPerViewNV, ClipDistancePerViewNV, CullDistancePerViewNV, LayerPerViewNV, 以及 ViewportMaskPerViewNV修饰的变量是 Position, ClipDistance, CullDistance, Layer, 以及 ViewportMaskNV的per-view的版本,这些变量可以看着是对应每个view的数组
		
		*/
	}

	//Mesh Shader Primitive Ordering  参见p2624
}

void PipelineStageProcessingTest::ClusterCullingShadingTest()
{
	/*
	cluster culling shader的运行环境类似于compute shader，其workgroup中的一组shader调用用于进行原始的等级几何剔除以及LOD的选取，该shader通过内置函数发送内置的输出变量
	*/

	//Cluster Culling Shader Input  参见p2625    唯一的输入是那些能够指定workgroup 以及 invocation的变量

	//Cluster Culling Shader Output  参见p2625 
	{
		/*
		如果一个cluster在cluster culling shader的处理下任然保留，则该shader会发送一个绘制命令绘制该cluster，而使用内置输出参数的类似与VkDrawIndexedIndirectCommand 与 VkDrawIndirectCommand的绘制命令用来进行绘制

		cluster culling shader的内置输出参数类型:
        IndexCountHUAWEI: 为绘制的顶点数
        VertexCountHUAWEI: 为绘制的顶点数
        InstanceCountHUAWEI: 为绘制的实例数
        FirstIndexHUAWEI: 为index buffer中的起始索引
        FirstVertexHUAWEI: 为第一个要绘制的顶点的索引
        VertexOffsetHUAWEI:  为一个在索引到顶点缓冲区之前加到顶点索引的值
        FirstInstanceHUAWEI:  为要绘制的第一个instance的ID 
        ClusterIDHUAWEI:  为该绘制命令绘制的cluster的索引，当cluster culling shader开启，该值将替换传递给顶点着色器的gl_DrawID 
        ClusterShadingRate:  为该绘制命令绘制的cluster的shading rate
		*/

	}

	// Cluster Culling Shader Cluster Ordering    输出的cluster通过调用DispatchClusterHUAWEI()发送个下一管线阶段，发送顺序参见p2625 

	// Cluster Culling Shader Primitive Ordering  参见p2626
}

void PipelineStageProcessingTest::FixedFunctionVertexPostProcessingTest()
{
	/*
	当所有pre-rasterization shader stages结束后会依次进行以下操作处理最终图元上的顶点:
    > Transform feedback 
    > Viewport swizzle 
    > Flat shading 
    > Primitive clipping, including client-defined half-spaces
    > Shader output attribute clipping
    > Clip space W scaling 
    > Perspective division on clip coordinates
    > Viewport mapping, including depth range scaling 
    > Front face determination for polygon primitives
	
	*/

	VkCommandBuffer commandBuffer{/*假设这是一个有效的VkCommandBuffer*/ };

	// Transform feedback  参见p2627
	{
		/*
		如果要捕获pre-rasterization shader stage中最后一个shader stage输出的顶点，则必须在该shader stage中声明Xfb execution mode，则以XfbBuffer声明的输出变量则会写入数据到对应的绑定的transform feedback buffers中,XfbStride会记录对应的顶点字节步长

		绑定transform feedback buffers通过vkCmdBindTransformFeedbackBuffersEXT 进行

		激活捕获通过vkCmdBeginTransformFeedbackEXT命令，关闭捕获通过vkCmdEndTransformFeedbackEXT.

		捕获数据后便可调用vkCmdDrawIndirectByteCountEXT来绘制顶点，其中vertexCount由之前捕获到的字节数来确定

		捕获的顶点数据的图元类型根据实际情况确定，参见p2628

		*/


		VkBuffer transformFeedbackBuffer{/*假设这是一个有效的VkBuffer*/ };
		VkDeviceSize transformFeedbackBufferSize;
		VkDeviceSize transformFeedbackBufferOffset;
		//绑定transform feedback buffers， 更新[firstBinding,firstBinding + bindingCount)绑定点上的buffer，以及对应offset和size
		vkCmdBindTransformFeedbackBuffersEXT(commandBuffer, 0/*firstBinding,为该命令更新的第一个transform feedback binding的索引*/, 1/*bindingCount,为该命令更新的transform feedback bindings 的数量*/,
			&transformFeedbackBuffer/*pBuffers，一组buffer句柄数组指针.*/,
			&transformFeedbackBufferOffset/*pOffsets,一组buffer起始字节偏移值的数组指针*/, &transformFeedbackBufferSize/*pSizes,为NULL或者一组buffer大小的数组指针，指明该transform feedback buffer可以捕获的最大的字节数量，如果为NULL，或这其中值为VK_WHOLE_SIZE,则指明最大值为对应buffer的大小减去pOffsets中对应的偏移值*/);
		/*
		vkCmdBindTransformFeedbackBuffersEXT有效用法:
		1.VkPhysicalDeviceTransformFeedbackFeaturesEXT::transformFeedback 必须开启
		2.firstBinding必须小于VkPhysicalDeviceTransformFeedbackPropertiesEXT::maxTransformFeedbackBuffers
		3.firstBinding + bindingCount必须小于等于VkPhysicalDeviceTransformFeedbackPropertiesEXT::maxTransformFeedbackBuffers
		4.pOffsets中的所有元素必须小于pBuffers对应buffer的大小，且必须为4的倍数
		5.pBuffers中的所有元素必须以VK_BUFFER_USAGE_TRANSFORM_FEEDBACK_BUFFER_BIT_EXT创建
		6.如果指定了可选的pSize，则pSize中的每个元素必须为VK_WHOLE_SIZE或者一个小于等于VkPhysicalDeviceTransformFeedbackPropertiesEXT::maxTransformFeedbackBufferSize的值，且小于等于pBuffer中对应buffer的大小
		7.对pOffsets以及pSizes所有对应元素相加的和，如果pSizes中某元素不为VK_WHOLE_SIZE，则该和必须小于等于对应pBuffers中buffer的大小
		8.如果pBuffers中每个元素是non-sparse的，则其必须绑定到完整的连续的单独的VkDeviceMemory上
		9.该命令记录时不能激活Transform feedback
		*/


		VkBuffer counterBuffer{/*假设这是一个有效的VkBuffer*/ };
		VkDeviceSize counterBufferOffset;
		//激活某个transform feedback buffer的transform feedback    该命令将激活某个transform feedback buffer对应到XfbBuffer的顶点数据捕获以及字节计数
		vkCmdBeginTransformFeedbackEXT(commandBuffer, 0/*firstCounterBuffer, 是对应到pCounterBuffers[0]以及pCounterBufferOffsets[0]的第一个transform feedback buffer的索引*/, 1/*counterBufferCount，为pCounterBuffers 以及 pCounterBufferOffsets 中的元素个数.*/,
			&counterBuffer/*pCounterBuffers，为NULL或者一组VkBuffer数组指针，每个buffer包含4字节整数指明从transform feedback buffer捕获的顶点数据结尾基于起始字节的字节偏移量，如果该值为NULL，则相当于所有transform feedback buffers捕获的顶点数据的数据字节偏移为0，如果不为VK_NULL_HANDLE的元素则指明其对应transform feedback buffer将从从字节0开始捕获到该transform feedback buffer中*/,
			&counterBufferOffset/*pCounterBufferOffsets,为NULL或者一组VkDeviceSize数组指针指明pCounterBuffers对应counter buffer的起始字节偏移，counter buffer中从该字节偏移开始的内存必须大于4个字节，从该字节开始的4个字节表示之前捕获到该transform feedback buffer的字节数，如果该值为NULL，则相当于每个counter buffer的offset都为0.*/);
		/*
		vkCmdBeginTransformFeedbackEXT有效用法:
		1.VkPhysicalDeviceTransformFeedbackFeaturesEXT::transformFeedback 必须开启
		2.Transform feedback不能激活
		3.firstCounterBuffer必须小于VkPhysicalDeviceTransformFeedbackPropertiesEXT::maxTransformFeedbackBuffers
		4.firstCounterBuffer + 	counterBufferCount必须小于等于VkPhysicalDeviceTransformFeedbackPropertiesEXT::maxTransformFeedbackBuffers
		5.如果counterBufferCount不为0，且pCounterBuffers不为NULL，则pCounterBuffers必须是一个有效的含counterBufferCount个为VK_NULL_HANDLE或者有效句柄的VkBuffer的数组指针
		6.对于pCounterBuffers中每个buffer，如果不为VK_NULL_HANDLE，则必须引用到一个足够容纳从pCounterBufferOffsets对应字节偏移开始4个字节的VkBuffer
		7.如果pCounterBuffer为NULL，则pCounterBufferOffsets必须为NULL
		8.pCounterBuffers中每个不为VK_NULL_HANDLE的buffer必须以VK_BUFFER_USAGE_TRANSFORM_FEEDBACK_COUNTER_BUFFER_BIT_EXT创建
		9.firstCounterBuffer + counterBufferCount必须小于等于当前vkCmdBindTransformFeedbackBuffersEXT绑定的transform feedback buffers的数量
		10.如果shaderObject 特性没有开启，一个有效的graphics pipeline必须绑定到VK_PIPELINE_BIND_POINT_GRAPHICS
		11.绑定的graphics pipeline的最后一个pre-rasterization shader stage必须声明为Xfb execution mode
		12.Transform feedback不能在开启multiview的render pass instance中激活
		*/
	
	
		//关闭某个激活的transform feedback buffer的transform feedback 
		vkCmdEndTransformFeedbackEXT(commandBuffer, 0/*firstCounterBuffer, 是对应到pCounterBuffers[0]以及pCounterBufferOffsets[0]的第一个transform feedback buffer的索引*/, 1/*counterBufferCount，为pCounterBuffers 以及 pCounterBufferOffsets 中的元素个数.*/,
			&counterBuffer/*pCounterBuffers，为NULL或者一组VkBuffer数组指针，counter buffer中将记录当前transform feedback buffer中的字节位置，该位置用于下一个顶点的捕获，这个值可以被下一个vkCmdBeginTransformFeedbackEXT使用用于下一个顶点的捕获，或者被vkCmdDrawIndirectByteCountEXT使用来确定绘制的顶点数量*/,
			&counterBufferOffset/*pCounterBufferOffsets,为NULL或者一组VkDeviceSize数组指针指明pCounterBuffers对应counter buffer的起始字节偏移，counter buffer中从该字节偏移开始的内存必须大于4个字节，从该字节开始的4个字节表示之前捕获到该transform feedback buffer的字节数，如果该值为NULL，则相当于每个counter buffer的offset都为0.*/);
		/*
		vkCmdEndTransformFeedbackEXT
		1.VkPhysicalDeviceTransformFeedbackFeaturesEXT::transformFeedback 必须开启
		2.Transform feedback必须激活
		3.firstCounterBuffer必须小于VkPhysicalDeviceTransformFeedbackPropertiesEXT::maxTransformFeedbackBuffers
		4.firstCounterBuffer + 	counterBufferCount必须小于等于VkPhysicalDeviceTransformFeedbackPropertiesEXT::maxTransformFeedbackBuffers
		5.如果counterBufferCount不为0，且pCounterBuffers不为NULL，则pCounterBuffers必须是一个有效的含counterBufferCount个为VK_NULL_HANDLE或者有效句柄的VkBuffer的数组指针
		6.对于pCounterBuffers中每个buffer，如果不为VK_NULL_HANDLE，则必须引用到一个足够容纳从pCounterBufferOffsets对应字节偏移开始4个字节的VkBuffer
		7.如果pCounterBuffer为NULL，则pCounterBufferOffsets必须为NULL
		8.pCounterBuffers中每个不为VK_NULL_HANDLE的buffer必须以VK_BUFFER_USAGE_TRANSFORM_FEEDBACK_COUNTER_BUFFER_BIT_EXT创建
		*/
	
	
	}


	//Viewport Swizzle  参见p2636
	{
		/*
		每个发送的给定viewport的图元含有一个swizzle（坐标映射关系，在发送到viewport的图元的顶点会重新映射x,y,z,w分量）和一个可选的应用到裁剪坐标的negation
		*/

		//swizzle取决于viewport的索引，由VkPipelineViewportSwizzleStateCreateInfoNV控制
		VkPipelineViewportSwizzleStateCreateInfoNV pipelineViewportSwizzleStateCreateInfoNV{};
		pipelineViewportSwizzleStateCreateInfoNV.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_SWIZZLE_STATE_CREATE_INFO_NV;
		pipelineViewportSwizzleStateCreateInfoNV.pNext = nullptr;
		pipelineViewportSwizzleStateCreateInfoNV.flags = 0;//保留未来使用
		pipelineViewportSwizzleStateCreateInfoNV.viewportCount = 1;//是pipeline使用的viewport swizzles 的数量.必须大于等于VkPipelineViewportStateCreateInfo中设置的viewportCount
		VkViewportSwizzleNV viewportSwizzleNV{};
		{
			viewportSwizzleNV.w = VK_VIEWPORT_COORDINATE_SWIZZLE_POSITIVE_W_NV;//指明应用到w分量的swizzle操作
			viewportSwizzleNV.x = VK_VIEWPORT_COORDINATE_SWIZZLE_POSITIVE_X_NV;//指明应用到x分量的swizzle操作
			viewportSwizzleNV.y = VK_VIEWPORT_COORDINATE_SWIZZLE_POSITIVE_Y_NV;//指明应用到y分量的swizzle操作
			viewportSwizzleNV.z = VK_VIEWPORT_COORDINATE_SWIZZLE_POSITIVE_Z_NV;//指明应用到z分量的swizzle操作
			/*
			VkViewportCoordinateSwizzleNV：
			VK_VIEWPORT_COORDINATE_SWIZZLE_POSITIVE_X_NV = 将该分量映射到正x
 			VK_VIEWPORT_COORDINATE_SWIZZLE_NEGATIVE_X_NV = 将该分量映射到负x
 			VK_VIEWPORT_COORDINATE_SWIZZLE_POSITIVE_Y_NV = 将该分量映射到正y
 			VK_VIEWPORT_COORDINATE_SWIZZLE_NEGATIVE_Y_NV = 将该分量映射到负y
 			VK_VIEWPORT_COORDINATE_SWIZZLE_POSITIVE_Z_NV = 将该分量映射到正z
 			VK_VIEWPORT_COORDINATE_SWIZZLE_NEGATIVE_Z_NV = 将该分量映射到负z
 			VK_VIEWPORT_COORDINATE_SWIZZLE_POSITIVE_W_NV = 将该分量映射到正w
 			VK_VIEWPORT_COORDINATE_SWIZZLE_NEGATIVE_W_NV = 将该分量映射到负w
			
			*/
		}
		pipelineViewportSwizzleStateCreateInfoNV.pViewportSwizzles = &viewportSwizzleNV;//一组VkViewportSwizzleNV数组指针，指明viewport swizzle


		//动态设置viewport swizzle state    当后续绘制使用shader object或者一个开启了VK_DYNAMIC_STATE_VIEWPORT_SWIZZLE_NV的graphics pipeline的时候，改名令用来设置viewport swizzle，否则将使用VkPipelineViewportSwizzleStateCreateInfoNV中的viewportCount以及pViewportSwizzles
		vkCmdSetViewportSwizzleNV(commandBuffer, 0/*firstViewport,为该命令更新参数的第一个viewport的索引*/, 1/* viewportCount，为该命令更新参数的viewport的数量.*/, &viewportSwizzleNV/* pViewportSwizzles ,一组VkViewportSwizzleNV数组指针，指明viewport swizzle*/);//extendedDynamicState3ViewportSwizzle 或者shaderObject 特性至少有一个要开启
	}


	//Flat Shading  参见p2640
	{
		/*
		Flat Shading会将一个图元的所有顶点的输出顶点属性全部设置成相同的值，该值来源于provoking vertex的输出属性值，Flat Shading会应用到和 fragment input attributes中以Flat声明的变量相匹配的输出顶点属性上

		provoking vertex顶点的选取由具体情况决定:
		1. 如果mesh, geometry 或者 tessellation shading都不开启，则由VkPipelineInputAssemblyStateCreateInfo:topology定义的图元拓扑决定
		2. 如果使用MeshNV Execution Model，则由 OutputPoints, OutputLinesNV, 或者 OutputTrianglesNV execution mode指定的拓扑类型决定
		3. 如果使用MeshEXT Execution Model，则由 OutputPoints, OutputLinesEXT, 或者 OutputTrianglesEXT execution mode指定的拓扑类型决定
		4. 如果激活了geometry shading，则由 OutputPoints,  OutputLineStrip, 或者 OutputTriangleStrip execution mode指定的拓扑类型决定
		5. 如果激活tessellation shading 但不激活geometry shading，则provoking vertex顶点可能为图元中任何一个顶点
		*/


		//可以包含在VkPipelineRasterizationStateCreateInfo::pNext中的VkPipelineRasterizationProvokingVertexStateCreateInfoEXT用来指定 provoking vertex mode，如果不含则默认为VK_PROVOKING_VERTEX_MODE_FIRST_VERTEX_EXT，如果 provokingVertexModePerPipeline限制为VK_FALSE，则所有pipeline的provoking vertex mode都相同
		VkPipelineRasterizationProvokingVertexStateCreateInfoEXT pipelineRasterizationProvokingVertexStateCreateInfoEXT{};
		pipelineRasterizationProvokingVertexStateCreateInfoEXT.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_PROVOKING_VERTEX_STATE_CREATE_INFO_EXT;
		pipelineRasterizationProvokingVertexStateCreateInfoEXT.pNext = nullptr;
		pipelineRasterizationProvokingVertexStateCreateInfoEXT.provokingVertexMode = VK_PROVOKING_VERTEX_MODE_FIRST_VERTEX_EXT;/*一个 VkProvokingVertexModeEXT 值指定provoking vertex mode，如果为VK_PROVOKING_VERTEX_MODE_LAST_VERTEX_EXT,则provokingVertexLast 特性必须开启
        VK_PROVOKING_VERTEX_MODE_FIRST_VERTEX_EXT:  指定provoking vertex 为图元的顶点列表中第一个non-adjacency vertex
        VK_PROVOKING_VERTEX_MODE_LAST_VERTEX_EXT:  指定provoking vertex 为图元的顶点列表中最后一个non-adjacency vertex
		*/


		//动态设置provoking vertex mode    该命令只有在后续绘制使用shader object或者绑定的graphics pipeline以VK_DYNAMIC_STATE_PROVOKING_VERTEX_MODE_EXT创建才能使用，否则会只用VkPipelineRasterizationProvokingVertexStateCreateInfoEXT::provokingVertexMode中设置的
		vkCmdSetProvokingVertexModeEXT(commandBuffer, VK_PROVOKING_VERTEX_MODE_FIRST_VERTEX_EXT/*provokingVertexMode, 一个VkProvokingVertexModeEXT 值指定provoking vertex mode.*/);
		/*
		vkCmdSetProvokingVertexModeEXT有效用法:
		1.extendedDynamicState3ProvokingVertexMode 或者shaderObject 特性至少有一个必须开启
		2.如果provokingVertexMode为VK_PROVOKING_VERTEX_MODE_LAST_VERTEX_EXT，则provokingVertexLast 特性必须开启
		*/
	}

	//Primitive Clipping  参见p2643
	{
		/*
		在剔除体外的图元会被剔除，图元在剔除后只保留在剔除体内的部分，剔除体空间定义为-Wc <= Xc <= Wc,-Wc <= Yc <= Wc,-Zm <= Zc <= Wc,如果 VkPipelineViewportDepthClipControlCreateInfoEXT::negativeOneToOne为VK_TRUE，则 Zm = -Wc,否则Zm = 0

		剔除体也叫视体，视体的范围可以进一步被 VkPhysicalDeviceLimits::maxClipDistances进行限制，详细信息参见p2644
		
		*/


		//如果graphics pipeline的state中含有 VkPipelineRasterizationDepthClipStateCreateInfoEXT，但其depthClipEnable为VK_FALSE,则depth clipping是禁用的，如果graphics pipeline中不含该结构体，则当 VkPipelineRasterizationStateCreateInfo::depthClampEnable为VK_TRUE时，depth clipping是关闭的
	
		//动态设置depth clamping     该命令只有在后续绘制使用shader object或者绑定的graphics pipeline以VK_DYNAMIC_STATE_DEPTH_CLAMP_ENABLE_EXT创建才能使用，否则会只用VkPipelineRasterizationStateCreateInfo::depthClampEnable中设置的
		vkCmdSetDepthClampEnableEXT(commandBuffer, VK_TRUE/*depthClampEnable,指定是否开启depth clamping*/);
		/*
		vkCmdSetDepthClampEnableEXT有效用法:
		1.extendedDynamicState3DepthClampEnable 或者shaderObject 特性至少有一个必须开启
		2.如果depthClamp 特性未开启，则 depthClampEnable 必须为VK_TRUE
		*/


		//动态设置depth clipping    该命令只有在后续绘制使用shader object或者绑定的graphics pipeline以VK_DYNAMIC_STATE_DEPTH_CLIP_ENABLE_EXT创建才能使用，否则会只用VkPipelineRasterizationDepthClipStateCreateInfoEXT::depthClipEnable中设置的，或者是使用VkPipelineRasterizationStateCreateInfo::depthClampEnable的相反值如果VkPipelineRasterizationDepthClipStateCreateInfoEXT该结构体没有设置
		vkCmdSetDepthClipEnableEXT(commandBuffer, VK_TRUE/*depthClipEnable,指定是否开启depth clipping*/);
		/*
		vkCmdSetDepthClipEnableEXT有效用法:
		1.extendedDynamicState3DepthClipEnable 或者shaderObject 特性至少有一个必须开启
		2.depthClipEnable 特性必须开启
		*/


		/*
		当depth cliping开始，depth值会满足Zm ≤ Zc ≤ Wc
		
		VkPhysicalDevicePointClippingProperties::pointClippingBehavior的值为VkPointClippingBehavior（等同于VkPointClippingBehaviorKHR）类型，指明可能的clip行为
		VkPointClippingBehavior:
        VK_POINT_CLIPPING_BEHAVIOR_ALL_CLIP_PLANES:  指明图元在顶点处于任何clip plane外或者上的时候会被丢弃，
		VK_POINT_CLIPPING_BEHAVIOR_USER_CLIP_PLANES_ONLY:  指明图元在顶点处于任何user clip plane外的时候会被丢弃


		对于线，clip会剔除视体外的点，计算一个新的点
		对于多边形，会在视体边界上计算新边，剔除视体外的部分，如果多边形和视体的边重合，则会剔除后保留的部分会包含该边上的一个点
		*/


		VkPipelineViewportDepthClipControlCreateInfoEXT pipelineViewportDepthClipControlCreateInfoEXT{};
		pipelineViewportDepthClipControlCreateInfoEXT.sType = VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_BUILD_GEOMETRY_INFO_KHR;
		pipelineViewportDepthClipControlCreateInfoEXT.pNext = nullptr;
		pipelineViewportDepthClipControlCreateInfoEXT.negativeOneToOne = VK_TRUE;// 设置视体中的Zm 为 -Wc    ,如果depthClipControl 没有开启，则该值必须为VK_FALSE
	
	
		//动态设置视体中的Zm 为 -Wc    该命令只有在后续绘制使用shader object或者绑定的graphics pipeline以VK_DYNAMIC_STATE_DEPTH_CLIP_NEGATIVE_ONE_TO_ONE_EXT创建才能使用，否则会只用VkPipelineViewportDepthClipControlCreateInfoEXT::negativeOneToOne中设置的
		vkCmdSetDepthClipNegativeOneToOneEXT(commandBuffer, VK_TRUE/*negativeOneToOne,指定视体中的Zm 为 -Wc*/);
		/*
		vkCmdSetDepthClipNegativeOneToOneEXT有效用法:
		1.extendedDynamicState3DepthClipNegativeOneToOne 或者shaderObject 特性至少有一个必须开启
		2.depthClipControl 特性必须开启
		
		*/
	
	}

	//Clipping Shader Outputs   参见p2650


	//Controlling Viewport W Scaling  参见p2651
	{
		/*
		如果开启了viewport的 W scaling ，则裁剪坐标的 W 分量将会被更改，根据公式 Wc' = Xcoeff * Xc + Ycoeff * Yc + Wc
		
		*/


		//可以在VkPipelineViewportStateCreateInfo的pNext中加入VkPipelineViewportWScalingStateCreateInfoNV来指定W scaling参数
		VkPipelineViewportWScalingStateCreateInfoNV pipelineViewportWScalingStateCreateInfoNV{};
		pipelineViewportWScalingStateCreateInfoNV.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_W_SCALING_STATE_CREATE_INFO_NV;
		pipelineViewportWScalingStateCreateInfoNV.pNext = nullptr;
		pipelineViewportWScalingStateCreateInfoNV.viewportCount = 1;//使用 W scaling的viewport的数量，必须匹配pipeline的viewport的数量
		pipelineViewportWScalingStateCreateInfoNV.viewportWScalingEnable = VK_TRUE;//控制是否开启viewport W scaling
		VkViewportWScalingNV viewportWScalingNV{};
		{
			viewportWScalingNV.xcoeff = 0;//是viewport的对应X的 W scaling 因子
			viewportWScalingNV.ycoeff = 0;//是viewport的对应Y的 W scaling 因子
		}
		pipelineViewportWScalingStateCreateInfoNV.pViewportWScalings = &viewportWScalingNV;//一组 VkViewportWScalingNV数组指针，指明对应viewport的W scaling的参数，如果W scaling是动态状态，则值会被忽略


		//动态设置是否启用W scaling     该命令只有在后续绘制使用shader object或者绑定的graphics pipeline以VK_DYNAMIC_STATE_VIEWPORT_W_SCALING_ENABLE_NV创建才能使用，否则会只用VkPipelineViewportWScalingStateCreateInfoNV::viewportWScalingEnable中设置的
		vkCmdSetViewportWScalingEnableNV(commandBuffer, VK_TRUE/*viewportWScalingEnable,指明是否启用 W scaling*/);
		/*
		vkCmdSetViewportWScalingEnableNV有效用法:
		1. extendedDynamicState3ViewportWScalingEnable 或者shaderObject 特性至少有一个必须开启
		*/

		//动态设置W scaling参数     该命令更新索引为[firstViewport,firstViewport + viewportCount)的viewport的参数， 只有在后续绘制使用shader object或者绑定的graphics pipeline以VK_DYNAMIC_STATE_VIEWPORT_W_SCALING_NV创建才能使用，否则会只用VkPipelineViewportWScalingStateCreateInfoNV::pViewportWScalings中设置的
		vkCmdSetViewportWScalingNV(commandBuffer, 0/*firstViewport,为该命令更新参数的第一个viewport的索引.*/,1/*viewportCount,为该命令更新参数的viewport的数量*/,&viewportWScalingNV/*pViewportWScalings,一组 VkViewportWScalingNV数组指针，指明对应viewport的W scaling的参数*/);
		/*
		vkCmdSetViewportWScalingEnableNV有效用法:
		1. firstViewport + viewportCount 必须在[1,VkPhysicalDeviceLimits::maxViewports]中
		*/
	}


	// Coordinate Transformations  参见p2655    裁剪坐标除以w得到归一化的设备坐标，设备坐标的分量范围为[-1,1]

	//Render Pass Transform    render pass instance可以开启render pass transform，如果开启就表示其裁剪坐标会沿着XY平面基于原点旋转一定度数，取决于 VK_SURFACE_TRANSFORM_***,其他信息见2655  

	//Controlling the Viewport   参见p2656
	{
		/*
		viewport transformation （视图变换）将取决于viewport的在pixel上的长宽（pX,pY）以及pixel上的原点位置（oX,oY），以及缩放深度值因子pZ以及深度值偏移oZ，如framebuffer坐标的变换（由设备坐标转换而来）
		Xf = (pX / 2) × Xd + oX
		Yf = (pY / 2) × Yd + oY
		Zf = pZ × Zd + oZ

		oX,oY,oZ,pX,pY,pZ由VkViewport定义的参数决定:

		oX = x + width / 2
		oY = y + height / 2
		oZ = minDepth (或者 (maxDepth + minDepth) / 2 如果 VkPipelineViewportDepthClipControlCreateInfoEXT::negativeOneToOne 为 VK_TRUE)
		pX = width
		pY = height
		pZ = maxDepth - minDepth (或者 (maxDepth - minDepth) / 2 如果 VkPipelineViewportDepthClipControlCreateInfoEXT::negativeOneToOne 为 VK_TRUE)


		即设备坐标根据VkViewport的参数转换到framebuffer的坐标，Xd的范围[-1,1],Yd的范围[-1,1]，如果VkPipelineViewportDepthClipControlCreateInfoEXT::negativeOneToOne开启，则Zd的范围[-1,1],否则为[0,1]
		Xf = width / 2 × (Xd + 1 )  + x 
		Yf = height / 2 × (Yd + 1 )  + y
		Zf = (maxDepth - minDepth) × Zd + minDepth   （或者 (maxDepth - minDepth) / 2 × Zd  +  (maxDepth + minDepth) / 2  如果 VkPipelineViewportDepthClipControlCreateInfoEXT::negativeOneToOne 为 VK_TRUE ）

		*/
		struct PipelineViewportStateCreateInfoEXT
		{
			VkPipelineViewportCoarseSampleOrderStateCreateInfoNV pipelineViewportCoarseSampleOrderStateCreateInfoNV{};
			VkPipelineViewportDepthClipControlCreateInfoEXT pipelineViewportDepthClipControlCreateInfoEXT{};
			VkPipelineViewportExclusiveScissorStateCreateInfoNV pipelineViewportExclusiveScissorStateCreateInfoNV{};
			VkPipelineViewportShadingRateImageStateCreateInfoNV pipelineViewportShadingRateImageStateCreateInfoNV{};
			VkPipelineViewportSwizzleStateCreateInfoNV pipelineViewportSwizzleStateCreateInfoNV{  };
			VkPipelineViewportWScalingStateCreateInfoNV pipelineViewportWScalingStateCreateInfoNV{};
			PipelineViewportStateCreateInfoEXT() {
				Init();
			}
			void Init() {
				pipelineViewportCoarseSampleOrderStateCreateInfoNV.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_COARSE_SAMPLE_ORDER_STATE_CREATE_INFO_NV;
				pipelineViewportCoarseSampleOrderStateCreateInfoNV.pNext = nullptr;
				pipelineViewportDepthClipControlCreateInfoEXT.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_DEPTH_CLIP_CONTROL_CREATE_INFO_EXT;
				pipelineViewportDepthClipControlCreateInfoEXT.pNext = nullptr;
				pipelineViewportExclusiveScissorStateCreateInfoNV.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_EXCLUSIVE_SCISSOR_STATE_CREATE_INFO_NV;
				pipelineViewportExclusiveScissorStateCreateInfoNV.pNext = nullptr;
				pipelineViewportShadingRateImageStateCreateInfoNV.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_SHADING_RATE_IMAGE_STATE_CREATE_INFO_NV;
				pipelineViewportShadingRateImageStateCreateInfoNV.pNext = nullptr;
				pipelineViewportSwizzleStateCreateInfoNV.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_SWIZZLE_STATE_CREATE_INFO_NV;
				pipelineViewportSwizzleStateCreateInfoNV.pNext = nullptr;
				pipelineViewportWScalingStateCreateInfoNV.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_W_SCALING_STATE_CREATE_INFO_NV;
				pipelineViewportWScalingStateCreateInfoNV.pNext = nullptr;

			}
		};


		VkPipelineViewportStateCreateInfo  pipelineViewportStateCreateInfo{};
		pipelineViewportStateCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
		PipelineViewportStateCreateInfoEXT pipelineViewportStateCreateInfoEXT{};
		pipelineViewportStateCreateInfo.pNext = &pipelineViewportStateCreateInfoEXT.pipelineViewportCoarseSampleOrderStateCreateInfoNV;
		pipelineViewportStateCreateInfo.flags = 0;//保留未来使用
		pipelineViewportStateCreateInfo.viewportCount = 1;//pipeline使用的viewport数量
		VkViewport viewport{};
		{
			viewport.x = 0;//为viewport的左上角的x坐标
			viewport.y = 0;//为viewport的左上角的y坐标
			viewport.width = 1;//为viewport的宽度
			viewport.height = 1;//为viewport的长度
			viewport.minDepth = 0;//为viewport深度值范围的最小值
			viewport.maxDepth = 1;//为viewport深度值范围的最大值
			/*
			VkViewport有效用法:
			1.width必须大于0小于等于VkPhysicalDeviceLimits::maxViewportDimensions[0]
			2.如果VK_KHR_maintenance1 拓展没有开启，VK_AMD_negative_viewport_height拓展没有开启，且VkPhysicalDeviceProperties::apiVersion小于Vulkan 1.1，则height必须大于0
			3.height的绝对值必须小于等于VkPhysicalDeviceLimits::maxViewportDimensions[1]
			4.x必须大于等于VkPhysicalDeviceLimits::viewportBoundsRange[0]
			5.(x + width)必须小于等于VkPhysicalDeviceLimits::viewportBoundsRange[1]
			6.y必须大于等于VkPhysicalDeviceLimits::viewportBoundsRange[0]小于等于VkPhysicalDeviceLimits::viewportBoundsRange[1]
			7.(y + height)必须大于等于VkPhysicalDeviceLimits::viewportBoundsRange[0]小于等于VkPhysicalDeviceLimits::viewportBoundsRange[1]
			8.如果VK_EXT_depth_range_unrestricted 拓展没有开启，则minDepth以及maxDepth 必须在[0,1]范围内，
			*/
		}
		pipelineViewportStateCreateInfo.pViewports = &viewport;//一组VkViewport数组指针，指明 viewport transforms.如果viewport state是动态的，则该值忽略
		pipelineViewportStateCreateInfo.scissorCount = 1;//pipeline使用的 scissors数量，必须匹配viewport的数量
		VkRect2D scissor{};
		{
			scissor.extent = VkExtent2D{ .width = 1,.height = 1 };
			scissor.offset = VkOffset2D{ .x = 0,.y = 0 };
		}
		pipelineViewportStateCreateInfo.pScissors = &scissor;//一组 VkRect2D数组指针，指明对应viewport的scissor的矩形边界，如果scissor state是动态的，则该值忽略
		/*
		VkPipelineViewportStateCreateInfo有效用法:
		1.如果multiViewport 特性未开启，则viewportCount以及scissorCount 不能大于1
		2.viewportCount以及scissorCount 必须小于等于VkPhysicalDeviceLimits::maxViewports
		3.pScissors中任何元素的offset的x以及y必须大于等于0
		4.pScissors中任何元素的 (offset.x + extent.width)以及(offset.y + extent.height)计算不能导致符号整数的溢出
		5.如果scissorCount以及viewportCount 都不是动态的，则scissorCount以及viewportCount必须相同
		6.如果graphics pipeline以VK_DYNAMIC_STATE_VIEWPORT_WITH_COUNT创建，则viewportCount必须为0，否则viewportCount必须大于0
		7.如果graphics pipeline以VK_DYNAMIC_STATE_SCISSOR_WITH_COUNT创建，则scissorCount必须为0，否则scissorCount必须大于0
		8.如果pNext中包含一个viewportWScalingEnable为VK_TRUE的VkPipelineViewportWScalingStateCreateInfoNV，则VkPipelineViewportWScalingStateCreateInfoNV的viewportCount必须大于等于VkPipelineViewportStateCreateInfo::viewportCount
		*/


		//动态设置viewport   等价于vkCmdSetViewportWithCountEXT   只有在后续绘制使用shader object或者绑定的graphics pipeline以VK_DYNAMIC_STATE_VIEWPORT_WITH_COUNT创建才能使用，否则会只用VkPipelineViewportStateCreateInfo::viewportCount 以及 pViewports中设置的
		vkCmdSetViewportWithCount(commandBuffer, 1/*viewportCount, 指明viewport的数量.*/, &viewport/*pViewports,一组VkViewport数组指针，指定绘制使用的viewports.*/);
		/*
		vkCmdSetViewportWithCount有效用法:
		1.extendedDynamicState特性开启，shaderObject特性开启以及创建该commandBuffer所在的VkInstance的VkApplicationInfo::apiVersion大于等于Version 1.3 这三个条件中至少需要满足一个
		2.viewportCount 必须在[1, VkPhysicalDeviceLimits::maxViewports]之间
		3.如果multiViewport 特性未开启，则viewportCount必须为1
		4.commandBuffer不能有VkCommandBufferInheritanceViewportScissorInfoNV::viewportScissor2D开启

		*/

		//动态设置scissors   等价于vkCmdSetScissorWithCountEXT   只有在后续绘制使用shader object或者绑定的graphics pipeline以VK_DYNAMIC_STATE_SCISSOR_WITH_COUNT创建才能使用，否则会只用VkPipelineViewportStateCreateInfo::scissorCount 以及 pScissors中设置的
		vkCmdSetScissorWithCount(commandBuffer, 1/*scissorCount, 指明scissors的数量.*/, &scissor/*pScissors,一组VkRect2D数组指针，指定绘制使用的scissors.*/);
		/*
		vkCmdSetScissorWithCount有效用法:
		1.extendedDynamicState特性开启，shaderObject特性开启以及创建该commandBuffer所在的VkInstance的VkApplicationInfo::apiVersion大于等于Version 1.3 这三个条件中至少需要满足一个
		2.scissorCount 必须在[1, VkPhysicalDeviceLimits::maxViewports]之间
		3.如果multiViewport 特性未开启，则scissorCount必须为1
		4.pScissors中任何元素的offset的x以及y必须大于等于0
		5.pScissors中任何元素的 (offset.x + extent.width)以及(offset.y + extent.height)计算不能导致符号整数的溢出
		6.commandBuffer不能有VkCommandBufferInheritanceViewportScissorInfoNV::viewportScissor2D开启

		*/


		//图元中的顶点可以由激活的最后一个pre-rasterization shader stage发送到由 ViewportIndex或者ViewportMaskNV选择的一个或多个viewport并进行viewport tranform

		//动态viewport参数   更新索引为[firstViewport,firstViewport + viewportCount)的viewport参数     只有在后续绘制使用shader object或者绑定的graphics pipeline以VK_DYNAMIC_STATE_VIEWPORT创建才能使用，否则会只用 VkPipelineViewportStateCreateInfo::pViewports中设置的
		vkCmdSetViewport(commandBuffer, 0/*firstViewport,为该命令要更新参数的第一个viewport的索引.*/, 1/*viewportCount, 为该命令要更新参数的viewport的数量.*/, &viewport/*pViewports,一组VkViewport数组指针，指定绘制使用的viewports..*/);
		/*
		vkCmdSetViewport有效用法:
		1.firstViewport + viewportCount必须在[1, VkPhysicalDeviceLimits::maxViewports]之间
		2.如果multiViewport 特性未开启，则firstViewport必须为0，viewportCount必须为1
		3.commandBuffer不能有VkCommandBufferInheritanceViewportScissorInfoNV::viewportScissor2D开启
		
		*/


	}
}


NS_TEST_END