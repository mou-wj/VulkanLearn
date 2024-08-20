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

void PipelineStageProcessingTest::RasterizationTest()
{
	/*
	Rasterization将图元转换为二维图像，图像中每个离散位置包含相关的数据如深度值，颜色等属性，Rasterization首先会计算图元在interger 坐标系中包含的面积，interger 坐标可以划分为方格网，每个方格称为fragment，有其framebuffer 坐标（x，y，z）以及相关的深度或者颜色值等属性
	
	Rasterization也会引用fragment的 sample locations，这些locations 一般会偏移fragment的左上角取值
	*/

	VkCommandBuffer commandBuffer{/*假设这是一个有效的VkCommandBuffer*/ };


	// VkPipelineRasterizationStateCreateInfo以及VkPipelineMultisampleStateCreateInfo. 中的参数可以控制Rasterization
	
	struct PipelineRasterizationStateCreateInfoEXT
	{
		VkDepthBiasRepresentationInfoEXT depthBiasRepresentationInfoEXT{};
		VkPipelineRasterizationConservativeStateCreateInfoEXT pipelineRasterizationConservativeStateCreateInfoEXT{};
		VkPipelineRasterizationDepthClipStateCreateInfoEXT pipelineRasterizationDepthClipStateCreateInfoEXT{};
		VkPipelineRasterizationLineStateCreateInfoKHR pipelineRasterizationLineStateCreateInfoKHR{};
		VkPipelineRasterizationProvokingVertexStateCreateInfoEXT pipelineRasterizationProvokingVertexStateCreateInfoEXT{};
		VkPipelineRasterizationStateRasterizationOrderAMD pipelineRasterizationStateRasterizationOrderAMD{};
		VkPipelineRasterizationStateStreamCreateInfoEXT pipelineRasterizationStateStreamCreateInfoEXT{};
		PipelineRasterizationStateCreateInfoEXT() {
			Init();
		}
		void Init() {
			depthBiasRepresentationInfoEXT.sType = VK_STRUCTURE_TYPE_MAX_ENUM;//未定义，所以这里定义为非法值
			depthBiasRepresentationInfoEXT.pNext = nullptr;
			pipelineRasterizationConservativeStateCreateInfoEXT.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_CONSERVATIVE_STATE_CREATE_INFO_EXT;
			pipelineRasterizationConservativeStateCreateInfoEXT.pNext = nullptr;
			pipelineRasterizationDepthClipStateCreateInfoEXT.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_DEPTH_CLIP_STATE_CREATE_INFO_EXT;
			pipelineRasterizationDepthClipStateCreateInfoEXT.pNext = nullptr;
			pipelineRasterizationLineStateCreateInfoKHR.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_LINE_STATE_CREATE_INFO_EXT;
			pipelineRasterizationLineStateCreateInfoKHR.pNext = nullptr;
			pipelineRasterizationProvokingVertexStateCreateInfoEXT.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_PROVOKING_VERTEX_STATE_CREATE_INFO_EXT;
			pipelineRasterizationProvokingVertexStateCreateInfoEXT.pNext = nullptr;
			pipelineRasterizationStateRasterizationOrderAMD.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_RASTERIZATION_ORDER_AMD;
			pipelineRasterizationStateRasterizationOrderAMD.pNext = nullptr;
			pipelineRasterizationStateStreamCreateInfoEXT.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_STREAM_CREATE_INFO_EXT;
			pipelineRasterizationStateStreamCreateInfoEXT.pNext = nullptr;
		}
	};

	//VkPipelineRasterizationStateCreateInfo
	VkPipelineRasterizationStateCreateInfo pipelineRasterizationStateCreateInfo{};
	pipelineRasterizationStateCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
	PipelineRasterizationStateCreateInfoEXT pipelineRasterizationStateCreateInfoEXT{};
	pipelineRasterizationStateCreateInfo.pNext = &pipelineRasterizationStateCreateInfoEXT.depthBiasRepresentationInfoEXT;
	pipelineRasterizationStateCreateInfo.flags = 0;//保留未来使用
	pipelineRasterizationStateCreateInfo.cullMode = VK_CULL_MODE_BACK_BIT;//是用于图元culling的三角形面的方向，见 VkCullModeFlagBits
	pipelineRasterizationStateCreateInfo.depthBiasClamp = VK_FALSE;//是fragment的深度值偏移量的最大或者最小值
	pipelineRasterizationStateCreateInfo.depthBiasConstantFactor = 0;//是一个标量因子用于控制添加到每个fragment深度值的常量值
	pipelineRasterizationStateCreateInfo.depthBiasEnable = VK_FALSE;//控制是否要偏移fragment的深度值
	pipelineRasterizationStateCreateInfo.depthBiasSlopeFactor = 0;//是一个标量因子用于fragment的深度值偏移计算的slope参数
	pipelineRasterizationStateCreateInfo.depthClampEnable = VK_FALSE;//控制是否进行 fragment深度值的clamp操作，如果pipeline不以含有 VkPipelineRasterizationDepthClipStateCreateInfoEXT创建，则启用depth clamp将关闭将深度值clip到视体z平面，否则depth cliping将由 VkPipelineRasterizationDepthClipStateCreateInfoEXT控制
	pipelineRasterizationStateCreateInfo.frontFace = VK_FRONT_FACE_CLOCKWISE;//一个 VkFrontFace 值指明用于culling的三角形的前面的面的方向
	pipelineRasterizationStateCreateInfo.lineWidth = 1;//为Rasterization后的线的宽度，像素级
	pipelineRasterizationStateCreateInfo.polygonMode = VK_POLYGON_MODE_FILL;//为三角形的渲染模式，为一个VkPolygonMode.值
	pipelineRasterizationStateCreateInfo.rasterizerDiscardEnable = VK_FALSE;//控制是否在rasterization stage前丢弃图元
	/*
	VkPipelineRasterizationStateCreateInfo有效用法:
	1.如果depthClamp 特性未开启，则depthClampEnable 必须为VK_FALSE
	2.如果fillModeNonSolid 特性未开启，则polygonMode 必须为VK_POLYGON_MODE_FILL或者 VK_POLYGON_MODE_FILL_RECTANGLE_NV
	3.如果VK_NV_fill_rectangle 拓展未开启，则polygonMode 必须为 VK_POLYGON_MODE_FILL_RECTANGLE_NV
	4.如果VK_KHR_portability_subset 拓展开启，且VkPhysicalDevicePortabilitySubsetFeaturesKHR::pointPolygons 为VK_FALSE，且rasterizerDiscardEnable为VK_FALSE，则polygonMode 不能为 VK_POLYGON_MODE_POINT
	*/


	//VkPipelineRasterizationStateCreateInfo.pNext中包含VkPipelineRasterizationDepthClipStateCreateInfoEXT用于控制是否开启depth clipping
	VkPipelineRasterizationDepthClipStateCreateInfoEXT& pipelineRasterizationDepthClipStateCreateInfoEXT = pipelineRasterizationStateCreateInfoEXT.pipelineRasterizationDepthClipStateCreateInfoEXT;
	pipelineRasterizationDepthClipStateCreateInfoEXT.flags = 0;//保留未来使用
	pipelineRasterizationDepthClipStateCreateInfoEXT.depthClipEnable = VK_FALSE;//控制是否开启 depth clipping




	struct PipelineMultisampleStateCreateInfoEXT {
		VkPipelineCoverageModulationStateCreateInfoNV pipelineCoverageModulationStateCreateInfoNV{};
		VkPipelineCoverageReductionStateCreateInfoNV pipelineCoverageReductionStateCreateInfoNV{};
		VkPipelineCoverageToColorStateCreateInfoNV pipelineCoverageToColorStateCreateInfoNV{};
		VkPipelineSampleLocationsStateCreateInfoEXT pipelineSampleLocationsStateCreateInfoEXT{};
		PipelineMultisampleStateCreateInfoEXT() {
			Init();
		}
		void Init() {
			pipelineCoverageModulationStateCreateInfoNV.sType = VK_STRUCTURE_TYPE_PIPELINE_COVERAGE_MODULATION_STATE_CREATE_INFO_NV;
			pipelineCoverageModulationStateCreateInfoNV.pNext = nullptr;
			pipelineCoverageReductionStateCreateInfoNV.sType = VK_STRUCTURE_TYPE_PIPELINE_COVERAGE_REDUCTION_STATE_CREATE_INFO_NV;
			pipelineCoverageReductionStateCreateInfoNV.pNext = nullptr;
			pipelineCoverageToColorStateCreateInfoNV.sType = VK_STRUCTURE_TYPE_PIPELINE_COVERAGE_TO_COLOR_STATE_CREATE_INFO_NV;
			pipelineCoverageToColorStateCreateInfoNV.pNext = nullptr;
			pipelineSampleLocationsStateCreateInfoEXT.sType = VK_STRUCTURE_TYPE_PIPELINE_SAMPLE_LOCATIONS_STATE_CREATE_INFO_EXT;
			pipelineSampleLocationsStateCreateInfoEXT.pNext = nullptr;


		}
	};




	//VkPipelineMultisampleStateCreateInfo
	VkPipelineMultisampleStateCreateInfo pipelineMultisampleStateCreateInfo{};
	pipelineMultisampleStateCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
	PipelineMultisampleStateCreateInfoEXT pipelineMultisampleStateCreateInfoEXT{};
	pipelineMultisampleStateCreateInfo.pNext = &pipelineMultisampleStateCreateInfoEXT.pipelineCoverageModulationStateCreateInfoNV;
	pipelineMultisampleStateCreateInfo.flags = 0;//保留未来使用
	pipelineMultisampleStateCreateInfo.alphaToCoverageEnable = VK_FALSE;//控制是否由基于fragment的第一个颜色输出的alpha分量生成一个暂时的coverage 值，参见Multisample Coverage p2779
	pipelineMultisampleStateCreateInfo.alphaToOneEnable = VK_FALSE;//控制是否替换fragment的第一个颜色输出的alpha分量为1，参见Multisample Coverage p2779
	pipelineMultisampleStateCreateInfo.minSampleShading = 0;//如果sampleShadingEnable为VK_TRUE，则该值指明Sample Shading最小的比例
	pipelineMultisampleStateCreateInfo.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;// 是一个VkSampleCountFlagBits值指明rasterization中的采样点数量，如果pipeline以VK_DYNAMIC_STATE_RASTERIZATION_SAMPLES_EXT但不以VK_DYNAMIC_STATE_SAMPLE_MASK_EXT动态设置开启创建，则该参数忽略，该参数同时用来定义pSampleMask中的元素个数
	pipelineMultisampleStateCreateInfo.sampleShadingEnable = VK_FALSE;//用来指定是否开启Sample Shading.见p2718
	VkSampleMask sampleMask{};//sampleMask中每个bit都会对应一个采样点
	pipelineMultisampleStateCreateInfo.pSampleMask = &sampleMask;//是一个VkSampleMask数组指针，指明在 sample mask test中的sample mask，长度为 ⌈ rasterizationSamples / 32 ⌉，如果为NULL，则相当于所有sample mask对应比特位为1
	/*
	VkPipelineMultisampleStateCreateInfo有效用法:
	1.如果sampleRateShading特性未开启，则sampleShadingEnable必须为VK_FALSE
	2.如果alphaToOne 特性未开启，则alphaToOneEnable 必须为VK_FALSE
	3.minSampleShading必须在[0,1]中
	4.如果VK_NV_framebuffer_mixed_samples 拓展开启，且如果subpass有任何color attachments的color samples小于rasterizationSamples，则sampleShadingEnable必须为VK_FALSE
	*/







	//Discarding Primitives Before Rasterization  参见p2702
	{
		/*
		如果VkPipelineRasterizationStateCreateInfo::rasterizerDiscardEnable为VK_TRUE，则图元会在 rasterization前 被最后一个激活的shader stage处理后被丢弃
		
		*/

		//动态设置是否启用图元丢弃    等价于vkCmdSetRasterizerDiscardEnableEXT    只有在后续绘制使用shader object或者绑定的graphics pipeline以VK_DYNAMIC_STATE_RASTERIZER_DISCARD_ENABLE创建才能使用，否则会只用 VkPipelineRasterizationStateCreateInfo::rasterizerDiscardEnable中设置的
		vkCmdSetRasterizerDiscardEnable(commandBuffer, VK_FALSE/* rasterizerDiscardEnable，控制是否在rasterization stage前丢弃图元.*/);
		/*
		vkCmdSetRasterizerDiscardEnable有效用法:
		1.extendedDynamicState2特性开启，shaderObject特性开启以及创建该commandBuffer所在的VkInstance的VkApplicationInfo::apiVersion大于等于Version 1.3 这三个条件中至少需要满足一个
		*/

	}


	// Controlling the Vertex Stream Used for Rasterization 参见p2674
	{
		/*
		默认情况下，最后的 pre-rasterization shader stage将把顶点数据定向到0号vertex stream

		Geometry shaders可以发送顶点数据到多个vertex stream，vertex stream收到数据后会根据geometry shader指定的图元类型进行图元组装，通过OpEndPrimitive 以及OpEndStreamPrimitive可以用来结束图元以及vertex stream中的图元组装

		实现可支持最大到VkPhysicalDeviceTransformFeedbackPropertiesEXT::maxTransformFeedbackStreams个流，至少为1，从索引0开始，每个vertex stream是独立的，受限于VkPhysicalDeviceTransformFeedbackPropertiesEXT::maxTransformFeedbackStreamDataSize 以及VkPhysicalDeviceTransformFeedbackPropertiesEXT::maxTransformFeedbackBufferDataSize

		vertex stream组装图元完成后便会通过transform feedback stage根据最后 pre-rasterization shader stage 定义的以XfbBuffer, XfbStride, 以及 Offsets修饰的输出变量行为来捕获顶点数据，
		
		默认情况下，0号vertex stream组装的数据会进行Rasterization 操作，如果支持VkPhysicalDeviceTransformFeedbackPropertiesEXT::transformFeedbackRasterizationStreamSelect，则可以选择别的vertex stream进行Rasterization

		默认情况下，如果Geometry shaders发送顶点到多个vertex stream话，只支持OutputPoints图元类型，如果支持VkPhysicalDeviceTransformFeedbackPropertiesEXT::transformFeedbackStreamsLinesTriangles，则也可以发送 OutputLineStrip 或者 OutputTriangleStrip类型的图元顶点
		*/

		//VkPipelineRasterizationStateCreateInfo.pNext中含VkPipelineRasterizationStateStreamCreateInfoEXT可以控制用于rasterization的vertex stream
		VkPipelineRasterizationStateStreamCreateInfoEXT& pipelineRasterizationStateStreamCreateInfoEXT = pipelineRasterizationStateCreateInfoEXT.pipelineRasterizationStateStreamCreateInfoEXT;
		pipelineRasterizationStateStreamCreateInfoEXT.flags = 0;//保留未来使用
		pipelineRasterizationStateStreamCreateInfoEXT.rasterizationStream = 0;//为选取的用于rasterization的vertex stream的索引
		/*
		VkPhysicalDeviceTransformFeedbackFeaturesEXT有效用法:
		1.VkPhysicalDeviceTransformFeedbackFeaturesEXT::geometryStreams 必须开启
		2.rasterizationStream必须小于VkPhysicalDeviceTransformFeedbackPropertiesEXT::maxTransformFeedbackStreams
		3.如果VkPhysicalDeviceTransformFeedbackPropertiesEXT::transformFeedbackRasterizationStreamSelect为VK_FALSE，rasterizationStream必须为0

		*/

		//动态设置选取用于rasterization的vertex stream的索引    只有在后续绘制使用shader object或者绑定的graphics pipeline以VK_DYNAMIC_STATE_RASTERIZATION_STREAM_EXT创建才能使用，否则会只用 VkPipelineRasterizationStateStreamCreateInfoEXT::rasterizationStream中设置的
		vkCmdSetRasterizationStreamEXT(commandBuffer, 0);
		/*
		vkCmdSetRasterizationStreamEXT有效用法:
		vkCmdSetRasterizationStreamEXT有效用法:
		1.extendedDynamicState3RasterizationStream 或者shaderObject 特性至少有一个要开启
		2.transformFeedback 特性必须开启
		3.rasterizationStream必须小于VkPhysicalDeviceTransformFeedbackPropertiesEXT::maxTransformFeedbackStreams
		4.如果VkPhysicalDeviceTransformFeedbackPropertiesEXT::transformFeedbackRasterizationStreamSelect为VK_FALSE，rasterizationStream必须为0
		*/

	}

	//Rasterization Order  参见p2677
	{

		//VkPipelineRasterizationStateCreateInfo.pNext中可以包含VkPipelineRasterizationStateRasterizationOrderAMD来指明Rasterization的顺序    ，如果 VK_AMD_rasterization_order拓展未开启或者Rasterization没有指定该结构体则默认使用 VK_RASTERIZATION_ORDER_STRICT_AMD
		VkPipelineRasterizationStateRasterizationOrderAMD& pipelineRasterizationStateRasterizationOrderAMD = pipelineRasterizationStateCreateInfoEXT.pipelineRasterizationStateRasterizationOrderAMD;
		pipelineRasterizationStateRasterizationOrderAMD.rasterizationOrder = VK_RASTERIZATION_ORDER_RELAXED_AMD;/*为一个 VkRasterizationOrderAMD值指明Rasterization使用的顺序
		VkRasterizationOrderAMD:
		VK_RASTERIZATION_ORDER_STRICT_AMD :  指明subpass中每个图元的Rasterization的顺序根据其原本图元顺序进行
		VK_RASTERIZATION_ORDER_RELAXED_AMD :  指明subpass中每个图元的Rasterization的顺序不根据其原本图元顺序进行 
		*/

	}


	//Multisampling  参见p2678
	{
		/*
		Multisampling是一种反走样技术，即对每个像素进行多次采样，并对这些采样结果进行一些操作以获得更该像素高质量的像素数据，如颜色，深度值等。
		
		vulkan中定义一个rasterization的single-sample modes等价于将multisample mode的结果给fragment中心的单个像素

		每个 fragment含有一个 coverage mask，其中每个bit对应一个sample，值取决于该fragment的该sample是否在图元中，如果没有则该bit为0，否则为1

		每个像素含有其相关的rasterizationSamples 个采样位置，这些采样点在该像素的为中心的单位面积内

		如果render pass含有一个fragment density map attachment，则不管该fragment中有多少像素，每个fragment中含rasterizationSamples 个采样位置，即用于存储每个像素的multiple samples结果的附件将定位到这些个采样位置
		
		在fragment shader的input interface中以 Sample 以及 Input修饰的变量可以从对应采样点中获取数据，如位置，深度值，颜色等

		定义为 fragment density map的Single pixel fragments 以及 multi-pixel fragments会含有一组采样点，由shading rate image定义或者设置了 fragment shading rate 的multi-pixel fragments的每个像素都有一组采样点，采样点数量由VkPipelineMultisampleStateCreateInfo::rasterizationSamples决定，采样点索引从0开始
		*/

		//动态设置rasterizationSamples    只有在后续绘制使用shader object或者绑定的graphics pipeline以VK_DYNAMIC_STATE_RASTERIZATION_SAMPLES_EXT创建才能使用，否则会只用 VkPipelineMultisampleStateCreateInfo::rasterizationSamples中设置的
		vkCmdSetRasterizationSamplesEXT(commandBuffer, VK_SAMPLE_COUNT_1_BIT/*rasterizationSamples ,指明 rasterizationSamples*/);
		/*
		vkCmdSetRasterizationSamplesEXT有效用法:
		1. extendedDynamicState3RasterizationSamples 特性开启或者shaderObject 特性至少一个特性开启
		
		*/


		/*
		每个采样点含有一个 coverage index 假设为 j（即该fragment的采样点位置包含在图元中的在整个frambuffer的位置索引），j范围[0, n * rasterizationSamples]，其中n为该fragment有多少组采样点
		如果n为1，则coverage index就为采样点索引
		如果使用shading rate image，则每个fragment包含多个像素，则coverage index就由VkPipelineViewportCoarseSampleOrderStateCreateInfoNV 或者 vkCmdSetCoarseSampleOrderNV定义决定
		如果设置fragment shading rate ，则coverage index计算:j = i + r × ((fw × fh) - 1 - p)  ,其中r为每个fragment的采样点数量，i为该采样点的的索引，fw为framebuffer的宽度，fh为framebuffer的高度，p为该像素所在frambuffer坐标在frambuffer中的索引，计算: p = px + (py × fw)，px  = x % f，py  = y % fh，x，y为该像素的frambuffer坐标
		
		 multi-pixel fragments中每个pixel的索引见p2681的表  Pixel indices 
		
		每个coverage mask包含B个采样点，且打包到W字中，则有B = n × rasterizationSamples，W = ⌈B/32⌉

		如果 VkPhysicalDeviceLimits::standardSampleLocations  为VK_TRUE，则 采样点VK_SAMPLE_COUNT_1_BIT, VK_SAMPLE_COUNT_2_BIT, VK_SAMPLE_COUNT_4_BIT, VK_SAMPLE_COUNT_8_BIT, VK_SAMPLE_COUNT_16_BIT的对应采样点位置参见p2683的表 Standard sample locations ，VK_SAMPLE_COUNT_32_BIT 以及 VK_SAMPLE_COUNT_64_BIT没有固定的位置
		
		以multiple samples per pixel创建的color image使用一种压缩技术，包含两个数组，第一个数组对应每个采样点，其中元素为第二数组的元素索引，第二个数组包含颜色值
		*/
	}


	//Custom Sample Locations  参见p2684
	{
		//可以 VkPipelineMultisampleStateCreateInfo.pNext中包含一个 VkPipelineSampleLocationsStateCreateInfoEXT控制rasterization的采样点位置
		VkPipelineSampleLocationsStateCreateInfoEXT& pipelineSampleLocationsStateCreateInfoEXT = pipelineMultisampleStateCreateInfoEXT.pipelineSampleLocationsStateCreateInfoEXT;
		pipelineSampleLocationsStateCreateInfoEXT.sampleLocationsEnable = VK_TRUE;//控制是否使用自定义的采样位置，如果为VK_FALSE，则使用默认的采样位置，在sampleLocationsInfo指定的位置信息会被忽略
		VkSampleLocationsInfoEXT sampleLocationsInfoEXT{};
		{
			/*
			VkSampleLocationsInfoEXT该结构体可以渲染的sample locations或者是指明用于以VK_IMAGE_CREATE_SAMPLE_LOCATIONS_COMPATIBLE_DEPTH_BIT_EXT. 创建的depth/stencil的subresource的layout transitions的最后渲染的采样位置信息
			
			pSampleLocations中指明在 sampleLocationGridSize 网格大小中每个像素的sampleLocationsPerPixel个采样位置，采样点i的位置为pSampleLocations[(x + y × sampleLocationGridSize.width) × sampleLocationsPerPixel + i]，其中(x,y)为采样点的像素所在的frambuffer坐标
			*/
			sampleLocationsInfoEXT.sType = VK_STRUCTURE_TYPE_SAMPLE_LOCATIONS_INFO_EXT;
			sampleLocationsInfoEXT.pNext = nullptr;
			sampleLocationsInfoEXT.sampleLocationGridSize = VkExtent2D{ .width = 1,.height = 1 };//选择自定义样本位置的采样位置网格大小
			sampleLocationsInfoEXT.sampleLocationsCount = 1;//pSampleLocations中元素个数，必须等于 sampleLocationsPerPixel × sampleLocationGridSize.width × sampleLocationGridSize.height
			VkSampleLocationEXT sampleLocationEXT{ .x = 0,.y = 0 };//指明采样位置的x，y坐标，这些坐标会被clamp到[sampleLocationCoordinateRange[0] , sampleLocationCoordinateRange[1]]，参见VkPhysicalDeviceSampleLocationsPropertiesEXT.
			sampleLocationsInfoEXT.pSampleLocations = &sampleLocationEXT;//是一个VkSampleLocationEXT数组指针，表示采样点的位置
			sampleLocationsInfoEXT.sampleLocationsPerPixel = VK_SAMPLE_COUNT_1_BIT;//一个VkSampleCountFlagBits 值，指明每个像素有多少个采样点，必须是一个有效的设置在VkPhysicalDeviceSampleLocationsPropertiesEXT::sampleLocationSampleCounts中的值
		}
		pipelineSampleLocationsStateCreateInfoEXT.sampleLocationsInfo = sampleLocationsInfoEXT;//是 rasterization 使用的采样位置信息，在sampleLocationsEnable为VK_TRUE且graphics pipeline不以 VK_DYNAMIC_STATE_SAMPLE_LOCATIONS_EXT创建下有效


		//动态设置 sampleLocationsEnable  只有在后续绘制使用shader object或者绑定的graphics pipeline以VK_DYNAMIC_STATE_SAMPLE_LOCATIONS_ENABLE_EXT创建才能使用，否则会只用VkPipelineSampleLocationsStateCreateInfoEXT::sampleLocationsEnable中设置的
		vkCmdSetSampleLocationsEnableEXT(commandBuffer, VK_TRUE/*sampleLocationsEnable,指明 sampleLocationsEnable state.*/);
		/*
		vkCmdSetSampleLocationsEnableEXT有效用法:
		1. extendedDynamicState3SampleLocationsEnable 或者shaderObject 特性至少有一个特性开启
		
		*/


		//动态设置 sampleLocationsInfo  只有在后续绘制使用shader object或者绑定的graphics pipeline以VK_DYNAMIC_STATE_SAMPLE_LOCATIONS_EXT创建且VkPipelineSampleLocationsStateCreateInfoEXT::sampleLocationsEnable 为VK_TRUE才能使用，否则会只用VkPipelineSampleLocationsStateCreateInfoEXT::sampleLocationsInfo中设置的
		vkCmdSetSampleLocationsEXT(commandBuffer, &sampleLocationsInfoEXT/*pSampleLocationsInfo,指明 采样位置信息.*/);
		/*
		vkCmdSetSampleLocationsEXT有效用法:
		1.如果VkPhysicalDeviceSampleLocationsPropertiesEXT::variableSampleLocations 为VK_FALSE，则当前的render pass必须以指定pPostSubpassSampleLocations中含有subpassIndex匹配当前subpass以及sampleLocationsInfo匹配pSampleLocationsInfo元素的VkRenderPassSampleLocationsBeginInfoEXT开始
		*/
	}



	//Fragment Shading Rates  参见p2689
	{
		/*
		VkPhysicalDeviceFragmentShadingRateFeaturesKHR建议的特性允许控制 fragment shader invocation的 shading rate

		shading rate和 Multisampling 强相关，则实现的可用rates集可能受到sample rate的限制
		
		*/

		//查询可用的 shading rates,
		uint32_t fragmentShadingRateCount;
		std::vector<VkPhysicalDeviceFragmentShadingRateKHR> physicalDeviceFragmentShadingRateKHRs;
		vkGetPhysicalDeviceFragmentShadingRatesKHR(physicalDevice, &fragmentShadingRateCount, nullptr);
		physicalDeviceFragmentShadingRateKHRs.resize(fragmentShadingRateCount);
		vkGetPhysicalDeviceFragmentShadingRatesKHR(physicalDevice, &fragmentShadingRateCount, physicalDeviceFragmentShadingRateKHRs.data());
		//假设返回了至少一个有效的shading rate
		/*
		返回的physicalDeviceFragmentShadingRateKHRs列表按主序fragmentSize.width由大到小排列，如果两个shading rate的fragmentSize.width相同，则按fragmentSize.height由大到小排列，且不能有两元素含相同 fragmentSize

		其中元素满足:
		1.fragmentSize.width为2的幂，fragmentSize.height为2的幂，且分别对应范围[1, maxFragmentSize.width],[1, maxFragmentSize.height]
		2.sampleCounts 小于等于maxFragmentShadingRateRasterizationSamples
		3.fragmentSize.width * fragmentSize.height * sampleCounts（最大的）必须小于等于 maxFragmentShadingRateCoverageSamples

		sampleCounts 以及 fragmentSize的支持详情见p2690,fragment size的支持可能还影响render pass transform

		*/
		physicalDeviceFragmentShadingRateKHRs[0].sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FRAGMENT_SHADING_RATE_KHR;
		physicalDeviceFragmentShadingRateKHRs[0].pNext = nullptr;
		physicalDeviceFragmentShadingRateKHRs[0].sampleCounts = VK_SAMPLE_COUNT_1_BIT;//为fragmentSize描述的 shading rate 支持的采样数
		physicalDeviceFragmentShadingRateKHRs[0].fragmentSize = { .width = 1,.height = 1 };//是一个 VkExtent2D 值，描述了支持的shading rate的宽高



		//Pipeline Fragment Shading Rate  参见p2692
		{
			//fragment shading rate 可以在pipeline的创建中或者vkCmdSetFragmentShadingRateKHR.中设置

			//在pipeline的创建中设置，VkGraphicsPipelineCreateInfo.pNext中包含 VkPipelineFragmentShadingRateStateCreateInfoKHR，如果没有包含，则默认fragmentSize为(1,1),combinerOps都设置为 VK_FRAGMENT_SHADING_RATE_COMBINER_OP_KEEP_KHR
			VkPipelineFragmentShadingRateStateCreateInfoKHR  pipelineFragmentShadingRateStateCreateInfoKHR{};
			pipelineFragmentShadingRateStateCreateInfoKHR.sType = VK_STRUCTURE_TYPE_PIPELINE_FRAGMENT_SHADING_RATE_STATE_CREATE_INFO_KHR;
			pipelineFragmentShadingRateStateCreateInfoKHR.pNext = nullptr;
			pipelineFragmentShadingRateStateCreateInfoKHR.combinerOps[0] = VK_FRAGMENT_SHADING_RATE_COMBINER_OP_KEEP_KHR;//指定一个VkFragmentShadingRateCombinerOpKHR 值指定pipeline, primitive, 以及 attachment shading rates如何绑定的，用于绘制命令如何使用该pipeline来产生fragments
			pipelineFragmentShadingRateStateCreateInfoKHR.combinerOps[1] = VK_FRAGMENT_SHADING_RATE_COMBINER_OP_KEEP_KHR;//指定一个VkFragmentShadingRateCombinerOpKHR 值指定pipeline, primitive, 以及 attachment shading rates如何绑定的，用于绘制命令如何使用该pipeline来产生fragments
			pipelineFragmentShadingRateStateCreateInfoKHR.fragmentSize = { .width = 1,.height = 1 };//为一个 VkExtent2D 结构体，定义pipeline fragment shading rate的fragment size，用于使用该pipeline的绘制命令
		


			//动态设置fragment shading rate以及 combiner operation      只有在后续绘制使用shader object或者绑定的graphics pipeline以VK_DYNAMIC_STATE_FRAGMENT_SHADING_RATE_KHR创建才能使用，否则会只用 VkPipelineFragmentShadingRateStateCreateInfoKHR::fragmentSize,combinerOps中设置的
			vkCmdSetFragmentShadingRateKHR(commandBuffer, &pipelineFragmentShadingRateStateCreateInfoKHR.fragmentSize/*pFragmentSize, 定义pipeline fragment shading rate的fragment size，用于使用该pipeline的后续绘制命令*/, pipelineFragmentShadingRateStateCreateInfoKHR.combinerOps/*指定一个VkFragmentShadingRateCombinerOpKHR 值指定pipeline, primitive, 以及 attachment shading rates如何绑定的，用于后续绘制命令如何使用该pipeline来产生fragments*/);
			/*
			vkCmdSetFragmentShadingRateKHR有效用法:
			1.如果pipelineFragmentShadingRate 没有开启，则pFragmentSize->width，pFragmentSize->height必须为1
			2.pipelineFragmentShadingRate，primitiveFragmentShadingRate或者attachmentFragmentShadingRate 至少有一个要开启
			3.如果primitiveFragmentShadingRate没有开启，则combinerOps[0]必须为VK_FRAGMENT_SHADING_RATE_COMBINER_OP_KEEP_KHR
			4.如果attachmentFragmentShadingRate没有开启，则combinerOps[1]必须为VK_FRAGMENT_SHADING_RATE_COMBINER_OP_KEEP_KHR
			5.如果fragmentSizeNonTrivialCombinerOps 限制不支持，则combinerOps中的元素必须为VK_FRAGMENT_SHADING_RATE_COMBINER_OP_KEEP_KHR或者VK_FRAGMENT_SHADING_RATE_COMBINER_OP_REPLACE_KHR
			6.pFragmentSize->width，pFragmentSize->height必须大于等于1小于等于4，pFragmentSize->width，pFragmentSize->height必须为2的幂

			*/
		
		}


		// Primitive Fragment Shading Rate      primitive fragment shading rate可以在最后的 pre-rasterization shader stage中通过 PrimitiveShadingRateKHR进行访问   参见p2695


		//Attachment Fragment Shading Rate  参见p2695
		{
			/*
			 可以在subpass中包含一个 VkFragmentShadingRateAttachmentInfoKHR来定义 fragment shading rate attachment，即每个frambuffer中的像素对应fragment shading rate attachment中的texel的attachment fragment shading rate

			计算:
			x' = floor(x / regionx)  y' = floor(y / regiony)  其中(x,y)为fragment的像素坐标，regionx，regiony为像素对应texel对应的区域的宽高，x'，y'为该像素对应texel的attachment fragment shading rate的坐标

			VkFragmentShadingRateAttachmentInfoKHR:: shadingRateAttachmentTexelSize指定regionx，regiony，该值会被编码到texel的第一个分量中，编码规则见p2696
			*/


		}


		//Combining the Fragment Shading Rates  参见p2696
		{
			/*
			最终的fragment shading rate (Cxy')必须是vkGetPhysicalDeviceFragmentShadingRatesKHR中返回的一个值

			在满足一定情况下， (Cxy')必须为（1，1），具体参见p2696,  否则每个指定的shading rate将绑定用来生成 Cxy'，有三种指定shading rates的方式，pipeline 以及 primitive shading rates之间，结果以及 attachment shading rate 有两种combiner operations

			combiner operations以VkFragmentShadingRateCombinerOpKHR定义:
				> VK_FRAGMENT_SHADING_RATE_COMBINER_OP_KEEP_KHR:  指定一个 combine(Axy,Bxy) = Axy的 combiner operation
				> VK_FRAGMENT_SHADING_RATE_COMBINER_OP_REPLACE_KHR:  指定一个 combine(Axy,Bxy) = Bxy的 combiner operation
				> VK_FRAGMENT_SHADING_RATE_COMBINER_OP_MIN_KHR:  指定一个 combine(Axy,Bxy) = min(Axy,Bxy)的 combiner operation
				> VK_FRAGMENT_SHADING_RATE_COMBINER_OP_MAX_KHR:  指定一个 combine(Axy,Bxy) = max(Axy,Bxy)的 combiner operation
				> VK_FRAGMENT_SHADING_RATE_COMBINER_OP_MUL_KHR:  指定一个 combine(Axy,Bxy) = Axy * Bxy的 combiner operation

			用于产生combined fragment area :  Cxy = combine(Axy,Bxy)   ，其中Axy 以及 Bxy 为fragment shading rates绑定的fragment areas， Cxy为combined fragment area result

			绑定两次:第一次的Axy 以及 Bxy分别为 pipeline fragment shading rate以及 primitive fragment shading rate，combine()由VkPipelineFragmentShadingRateStateCreateInfoKHR::combinerOps[0]定义，
					 第二次的Axy 以及 Bxy分别为第一次操作的结果 以及 attachment fragment shading rate，combine()由VkPipelineFragmentShadingRateStateCreateInfoKHR::combinerOps[1]定义， 第二次操作的结果为最终的fragment shading rate，由 ShadingRateKHR 表明


			实现应该限制 Axy 以及 Bxy,如果VkPhysicalDeviceMaintenance6PropertiesKHR::fragmentShadingRateClampCombinerInputs为VK_TRUE，则必须对Axy 以及 Bxy进行clamp操作，clamp范围为[0,1]，clamp操作由VkPhysicalDeviceFragmentShadingRatePropertiesKHR::minFragmentShadingRate和VkPhysicalDeviceFragmentShadingRatePropertiesKHR::maxFragmentShadingRate定义

			如果 Axy, Bxy 或者 Cxy 不在 vkGetPhysicalDeviceFragmentShadingRatesKHR返回的列表内，则应该遵循一些规则从其中选择一个，筛选规则 见p2697
			*/


		}


		//Extended Fragment Shading Rates 参见p2697
		{
			/*
			VkPhysicalDeviceFragmentShadingRateEnumsFeaturesNV建议的特性提供了额外的fragment shading rate支持

			如果 fragmentShadingRateEnums 特性开启，则fragment shading rates可以 VkFragmentShadingRateNV枚举来定义
				> VK_FRAGMENT_SHADING_RATE_1_INVOCATION_PER_PIXEL_NV: 指明 fragment 大小为 1x1 pixels.
				> VK_FRAGMENT_SHADING_RATE_1_INVOCATION_PER_1X2_PIXELS_NV: 指明 fragment 大小为 1x2 pixels.
				> VK_FRAGMENT_SHADING_RATE_1_INVOCATION_PER_2X1_PIXELS_NV: 指明 fragment 大小为 2x1 pixels.
				> VK_FRAGMENT_SHADING_RATE_1_INVOCATION_PER_2X2_PIXELS_NV: 指明 fragment 大小为 2x2 pixels.
				> VK_FRAGMENT_SHADING_RATE_1_INVOCATION_PER_2X4_PIXELS_NV: 指明 fragment 大小为 2x4 pixels.
				> VK_FRAGMENT_SHADING_RATE_1_INVOCATION_PER_4X2_PIXELS_NV: 指明 fragment 大小为 4x2 pixels.
				> VK_FRAGMENT_SHADING_RATE_1_INVOCATION_PER_4X4_PIXELS_NV: 指明 fragment 大小为 4x4 pixels.
				> VK_FRAGMENT_SHADING_RATE_2_INVOCATIONS_PER_PIXEL_NV: 指明 fragment 大小为 1x1 pixels, 且每个fragment有两次 fragment shader invocations
				> VK_FRAGMENT_SHADING_RATE_4_INVOCATIONS_PER_PIXEL_NV: 指明 fragment 大小为 1x1 pixels, 且每个fragment有四次 fragment shader invocations
				> VK_FRAGMENT_SHADING_RATE_8_INVOCATIONS_PER_PIXEL_NV: 指明 fragment 大小为 1x1 pixels, 且每个fragment有八次 fragment shader invocations
				> VK_FRAGMENT_SHADING_RATE_16_INVOCATIONS_PER_PIXEL_NV: 指明 fragment 大小为 1x1 pixels,  且每个fragment有十六次 fragment shader invocations
				> VK_FRAGMENT_SHADING_RATE_NO_INVOCATIONS_NV:  指明图元任何使用shading rate的部分都应该直接丢弃且不调用任何fragment shader

			当使用 fragment shading rate enums时,pipeline fragment shading rate可以在创建pipeline的时候设置或者调用vkCmdSetFragmentShadingRateEnumNV 动态设置
			*/

			//在pipeline的创建中设置pipeline fragment shading rate 以及 combiner operation，VkGraphicsPipelineCreateInfo.pNext中包含VkPipelineFragmentShadingRateEnumStateCreateInfoNV， 如果不包含该结构体，则shadingRateType 默认为VK_FRAGMENT_SHADING_RATE_TYPE_FRAGMENT_SIZE_NV，shadingRate 默认为VK_FRAGMENT_SHADING_RATE_1_INVOCATION_PER_PIXEL_NV，combinerOps的默认值都为VK_FRAGMENT_SHADING_RATE_COMBINER_OP_KEEP_KHR
			VkPipelineFragmentShadingRateEnumStateCreateInfoNV  pipelineFragmentShadingRateEnumStateCreateInfoNV{};
			pipelineFragmentShadingRateEnumStateCreateInfoNV.sType = VK_STRUCTURE_TYPE_PIPELINE_FRAGMENT_SHADING_RATE_ENUM_STATE_CREATE_INFO_NV;
			pipelineFragmentShadingRateEnumStateCreateInfoNV.pNext = nullptr;
			pipelineFragmentShadingRateEnumStateCreateInfoNV.combinerOps[0] = VK_FRAGMENT_SHADING_RATE_COMBINER_OP_KEEP_KHR;//指定一个VkFragmentShadingRateCombinerOpKHR 值指定pipeline, primitive, 以及 attachment shading rates如何绑定的，用于绘制命令如何使用该pipeline来产生fragments
			pipelineFragmentShadingRateEnumStateCreateInfoNV.combinerOps[1] = VK_FRAGMENT_SHADING_RATE_COMBINER_OP_KEEP_KHR;//指定一个VkFragmentShadingRateCombinerOpKHR 值指定pipeline, primitive, 以及 attachment shading rates如何绑定的，用于绘制命令如何使用该pipeline来产生fragments
			pipelineFragmentShadingRateEnumStateCreateInfoNV.shadingRate = VK_FRAGMENT_SHADING_RATE_1_INVOCATION_PER_PIXEL_NV;//指定一个VkFragmentShadingRateNV 值指定pipeline fragment shading rate
			pipelineFragmentShadingRateEnumStateCreateInfoNV.shadingRateType = VK_FRAGMENT_SHADING_RATE_TYPE_ENUMS_NV;/* 指定一个VkFragmentShadingRateTypeNV 值指定fragment shading rate是否由fragment sizes 或者VkFragmentShadingRateNV 枚举定义
			VkFragmentShadingRateTypeNV:
			VK_FRAGMENT_SHADING_RATE_TYPE_FRAGMENT_SIZE_NV:  指明pipeline fragment shading rate以及combiner state 从VkPipelineFragmentShadingRateStateCreateInfoKHR中指定，VkPipelineFragmentShadingRateEnumStateCreateInfoNV指定的会被忽略
			VK_FRAGMENT_SHADING_RATE_TYPE_ENUMS_NV:   指定pipeline fragment shading rate以及combiner state 从VkPipelineFragmentShadingRateEnumStateCreateInfoNV中指定，VkPipelineFragmentShadingRateStateCreateInfoKHR指定的会被忽略
			*/



			//动态设置pipeline fragment shading rate 以及 combiner operation     只有在后续绘制使用shader object或者绑定的graphics pipeline以VK_DYNAMIC_STATE_FRAGMENT_SHADING_RATE_KHR创建才能使用，否则会只用VkPipelineFragmentShadingRateEnumStateCreateInfoNV 中设置的
			vkCmdSetFragmentShadingRateEnumNV(commandBuffer, VK_FRAGMENT_SHADING_RATE_1_INVOCATION_PER_1X2_PIXELS_NV/*shadingRate,指定一个VkFragmentShadingRateNV枚举指明后续绘制命令使用的 pipeline fragment shading rate.*/, pipelineFragmentShadingRateEnumStateCreateInfoNV.combinerOps/*combinerOps， 指定VkFragmentShadingRateCombinerOpKHR 值指定pipeline, primitive, 以及 attachment shading rates如何绑定的，用于绘制命令如何使用该pipeline来产生fragments*/);
			/*
			vkCmdSetFragmentShadingRateEnumNV有效用法:
			1.如果pipelineFragmentShadingRate 未开启，则shadingRate必须为VK_FRAGMENT_SHADING_RATE_1_INVOCATION_PER_PIXEL_NV
			2.如果supersampleFragmentShadingRates 未开启，则shadingRate不能为VK_FRAGMENT_SHADING_RATE_2_INVOCATIONS_PER_PIXEL_NV,
																			 VK_FRAGMENT_SHADING_RATE_4_INVOCATIONS_PER_PIXEL_NV,
																			 VK_FRAGMENT_SHADING_RATE_8_INVOCATIONS_PER_PIXEL_NV,或者
																			 VK_FRAGMENT_SHADING_RATE_16_INVOCATIONS_PER_PIXEL_NV
			3.如果noInvocationFragmentShadingRates 未开启，则shadingRate不能为VK_FRAGMENT_SHADING_RATE_NO_INVOCATIONS_NV
			4.fragmentShadingRateEnums 特性必须开启
			5.pipelineFragmentShadingRate，primitiveFragmentShadingRate或者attachmentFragmentShadingRate 至少有一个要开启
			6.如果primitiveFragmentShadingRate没有开启，则combinerOps[0]必须为VK_FRAGMENT_SHADING_RATE_COMBINER_OP_KEEP_KHR
			7.如果attachmentFragmentShadingRate没有开启，则combinerOps[1]必须为VK_FRAGMENT_SHADING_RATE_COMBINER_OP_KEEP_KHR
			8.如果fragmentSizeNonTrivialCombinerOps 限制不支持，则combinerOps中的元素必须为VK_FRAGMENT_SHADING_RATE_COMBINER_OP_KEEP_KHR或者VK_FRAGMENT_SHADING_RATE_COMBINER_OP_REPLACE_KHR
			*/

		}
	}



	//Shading Rate Image  参见2703
	{
		/*
		 shadingRateImage特性允许使用 shading rate image来控制fragment area以及每个fragment最小的fragment shader invocations的数量。如果开启，则 rasterizer 会从shading rate image中读取一个图元覆盖的区域的一个值通过 per-viewport shading rate palette转换为基本的 shading rate，最终转换为final shading rate
		
		*/


		//在VkPipelineViewportStateCreateInfo.pNext中包含 VkPipelineViewportShadingRateImageStateCreateInfoNV用于控制shading rate
		VkPipelineViewportShadingRateImageStateCreateInfoNV  pipelineViewportShadingRateImageStateCreateInfoNV{};
		pipelineViewportShadingRateImageStateCreateInfoNV.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_SHADING_RATE_IMAGE_STATE_CREATE_INFO_NV;
		pipelineViewportShadingRateImageStateCreateInfoNV.pNext = nullptr;
		pipelineViewportShadingRateImageStateCreateInfoNV.shadingRateImageEnable = VK_TRUE;//指明是否在rasterization中使用shading rate image 以及 palettes
		pipelineViewportShadingRateImageStateCreateInfoNV.viewportCount = 1;//指定用于转换存储在shading rate image中值的per-viewport palettes的数量  ,pShadingRatePalettes中元素个数
		VkShadingRatePaletteNV shadingRatePaletteNV{};//该结构体定义单个shading rate image palette
		{
			shadingRatePaletteNV.shadingRatePaletteEntryCount = 1;//指明shading rate image palette.中的实体数量，必须在[1,VkPhysicalDeviceShadingRateImagePropertiesNV::shadingRatePaletteSize]之间
			VkShadingRatePaletteEntryNV shadingRatePaletteEntryNV = VK_SHADING_RATE_PALETTE_ENTRY_16_INVOCATIONS_PER_PIXEL_NV;
			{
				/*
				VkShadingRatePaletteEntryNV 值如何映射到基本的 shading rate，包括每个fragment的pixel的宽高以及fragment shader invocations的数量:

				Shading Rate                                                        |   Width       |       Height      |     Invocations
				VK_SHADING_RATE_PALETTE_ENTRY_NO_INVOCATIONS_NV						|	 0          |         0         |          0
				VK_SHADING_RATE_PALETTE_ENTRY_16_INVOCATIONS_PER_PIXEL_NV			|	 1          |         1         |          16
				VK_SHADING_RATE_PALETTE_ENTRY_8_INVOCATIONS_PER_PIXEL_NV			|	 1			|		  1			|		   8
				VK_SHADING_RATE_PALETTE_ENTRY_4_INVOCATIONS_PER_PIXEL_NV			|	 1			|		  1			|		   4
				VK_SHADING_RATE_PALETTE_ENTRY_2_INVOCATIONS_PER_PIXEL_NV			|	 1			|		  1			|		   2
				VK_SHADING_RATE_PALETTE_ENTRY_1_INVOCATION_PER_PIXEL_NV				|	 1			|		  1			|		   1
				VK_SHADING_RATE_PALETTE_ENTRY_1_INVOCATION_PER_2X1_PIXELS_NV		|	 2			|		  1			|		   1
				VK_SHADING_RATE_PALETTE_ENTRY_1_INVOCATION_PER_1X2_PIXELS_NV		|	 1			|		  2			|		   1
				VK_SHADING_RATE_PALETTE_ENTRY_1_INVOCATION_PER_2X2_PIXELS_NV		|	 2			|		  2			|		   1
				VK_SHADING_RATE_PALETTE_ENTRY_1_INVOCATION_PER_4X2_PIXELS_NV		|	 4			|		  2			|		   1
				VK_SHADING_RATE_PALETTE_ENTRY_1_INVOCATION_PER_2X4_PIXELS_NV		|	 2			|		  4			|		   1
				VK_SHADING_RATE_PALETTE_ENTRY_1_INVOCATION_PER_4X4_PIXELS_NV		|	 4			|		  4			|		   1
				
				
				*/



			}
			shadingRatePaletteNV.pShadingRatePaletteEntries = &shadingRatePaletteEntryNV;//一个VkShadingRatePaletteEntryNV 数组指针，指明shading rate image palette中的实体， shading rate index i会映射这里面的第i 元素以获取一个基本的 shading rate，如果i大于shadingRatePaletteEntryCount，则该基本的shading rate是未定义的，如果pipeline不使用shading rate image，则默认使用VK_SHADING_RATE_PALETTE_ENTRY_1_INVOCATION_PER_PIXEL_NV
		}
		pipelineViewportShadingRateImageStateCreateInfoNV.pShadingRatePalettes = &shadingRatePaletteNV;//一组VkShadingRatePaletteNV 数组指针，指明每个viewport的palette，如果 shading rate palette state是动态的，则该参数忽略
		/*
		VkPipelineViewportShadingRateImageStateCreateInfoNV有效用法:
		1.如果multiViewport 特性未开启，则viewportCount必须为0或者1
		2.viewportCount 必须小于或等于 VkPhysicalDeviceLimits::maxViewports
		3.如果shadingRateImageEnable 为 VK_TRUE，则viewportCount 必须大于或等于 VkPipelineViewportStateCreateInfo.viewportCount

		*/


		//当绑定的pipeline使用了 shading rate image，则可以通过命令指定
		vkCmdBindShadingRateImageNV(commandBuffer, VkImageView{/*假设这是一个有效的VkImageView*/ }/*imageView,为VkImageView指明 shading rate image. 可以设置为VK_NULL_HANDLE，等同于指定一个值全为0的image.*/, VK_IMAGE_LAYOUT_SHADING_RATE_OPTIMAL_NV/* imageLayout，指定 shading rate image被访问的subresource的layout布局*/);
		/*
		vkCmdBindShadingRateImageNV有效用法:
		1.shadingRateImage 特性必须开启
		2.如果imageView不为VK_NULL_HANDLE，则（1）必须是有效的VkImageView，且类型必须为VK_IMAGE_VIEW_TYPE_2D 或者 VK_IMAGE_VIEW_TYPE_2D_ARRAY
											 （2）格式必须为VK_FORMAT_R8_UINT
											 （3）必须以VK_IMAGE_USAGE_SHADING_RATE_IMAGE_BIT_NV创建
											 （4）imageLayout 必须比配实际上访问的subresource的layout布局，必须是VK_IMAGE_LAYOUT_SHADING_RATE_OPTIMAL_NV 或者 VK_IMAGE_LAYOUT_GENERAL
		*/

		//如果绑定的pipeline启用了 shading rate image，则可以获取其（u,v）坐标返回的值的unsigned integer component值来获取一个 shading rate index 并通过一个shading rate image palette映射到一个基本的 shading rate，每个viewport都有独立的shading rate image palette。（具体如何取(u，v)值参见p2706）

		//动态设置shadingRateImageEnable      只有在后续绘制使用shader object或者绑定的graphics pipeline以VK_DYNAMIC_STATE_SHADING_RATE_IMAGE_ENABLE_NV创建才能使用，否则会只用VkPipelineViewportShadingRateImageStateCreateInfoNV::shadingRateImageEnable中设置的
		vkCmdSetShadingRateImageEnableNV(commandBuffer, VK_TRUE/*shadingRateImageEnable，指明 shadingRateImageEnable state.*/);
		/*
		vkCmdSetShadingRateImageEnableNV有效用法:
		1.extendedDynamicState3ShadingRateImageEnable 或者shaderObject 特性至少有一个特性开启
		
		*/


		//动态设置per-viewport的shading rate image palettes   只有在后续绘制使用shader object或者绑定的graphics pipeline以VK_DYNAMIC_STATE_VIEWPORT_SHADING_RATE_PALETTE_NV创建才能使用，否则会只用VkPipelineViewportShadingRateImageStateCreateInfoNV::pShadingRatePalettes中设置的
		vkCmdSetViewportShadingRatePaletteNV(commandBuffer, 0/*firstViewport， 为该命令要更新shading rate image palette的第一个viewport的索引*/, 1/*viewportCount， 为该命令要更新shading rate image palette的viewport的数量*/,
					&shadingRatePaletteNV/* pShadingRatePalettes，一组VkShadingRatePaletteNV 数组指针，指明每个viewport的palette*/);
		/*
		vkCmdSetViewportShadingRatePaletteNV有效用法:
		1.shadingRateImage 特性必须开启
		2.firstViewport + viewportCount 必须在[1, VkPhysicalDeviceLimits::maxViewports]之间
		3.如果multiViewport特性未开启，则firstViewport必须为0，viewportCount必须为1

		*/


		//选择一个基本的 shading rate 后如何将其映射到最终的 shading rate  参见2711

		/*
		VkPipelineViewportStateCreateInfo.pNext中包含 VkPipelineViewportCoarseSampleOrderStateCreateInfoNV用于控制包含多个pixel的fragment的采样点的顺序，如果不含该结构体，则默认使用sampleOrderType为VK_COARSE_SAMPLE_ORDER_TYPE_DEFAULT_NV，
		如果 sampleOrderType为VK_COARSE_SAMPLE_ORDER_TYPE_CUSTOM_NV，则每个绑定的fragment的区域以及采样点数量的采样点排序规则没有在pCustomSampleOrders中指定，则将默认使用 VK_COARSE_SAMPLE_ORDER_TYPE_DEFAULT_NV.
		如果pipeline以 VK_DYNAMIC_STATE_VIEWPORT_COARSE_SAMPLE_ORDER_NV创建，则该结构体中的参数会被忽略
		
		*/
		VkPipelineViewportCoarseSampleOrderStateCreateInfoNV pipelineViewportCoarseSampleOrderStateCreateInfoNV{};
		pipelineViewportCoarseSampleOrderStateCreateInfoNV.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_COARSE_SAMPLE_ORDER_STATE_CREATE_INFO_NV;
		pipelineViewportCoarseSampleOrderStateCreateInfoNV.pNext = nullptr;
		pipelineViewportCoarseSampleOrderStateCreateInfoNV.sampleOrderType = VK_COARSE_SAMPLE_ORDER_TYPE_CUSTOM_NV;/*指定包含多个pixel的fragment的采样点的排序机制
		VkCoarseSampleOrderTypeNV:
		VK_COARSE_SAMPLE_ORDER_TYPE_DEFAULT_NV:  指定包含的采样点将按照实现定义的顺序排序。
		VK_COARSE_SAMPLE_ORDER_TYPE_CUSTOM_NV:   指定包含的采样点将按照VkPipelineViewportCoarseSampleOrderStateCreateInfoNV或者vkCmdSetCoarseSampleOrderNV中设置pCustomSampleOrders中指定的顺序排序。
		VK_COARSE_SAMPLE_ORDER_TYPE_PIXEL_MAJOR_NV:  指定包含的采样点将按照像素的行优先顺序排序，然后按照采样点的索引顺序排序。
		VK_COARSE_SAMPLE_ORDER_TYPE_SAMPLE_MAJOR_NV:  指定包含的采样点将按照采样点的索引优先顺序排序，然后按照像素的行优先顺序排序。
		*/
		pipelineViewportCoarseSampleOrderStateCreateInfoNV.customSampleOrderCount = 1;//指定当排序采样点的顺序时，需要使用的自定义排序规则的数量，为pCustomSampleOrders元素个数
		VkCoarseSampleOrderCustomNV coarseSampleOrderCustomNV{};
		{
			coarseSampleOrderCustomNV.shadingRate = VK_SHADING_RATE_PALETTE_ENTRY_16_INVOCATIONS_PER_PIXEL_NV;//是一个VkShadingRatePaletteEntryNV值，指定了该fragment绑定的fragment区域以及包含控制的per-pixel的采样点数量组合的fragment区域的宽高
			coarseSampleOrderCustomNV.sampleCount = 1;//指定了该fragment绑定的fragment区域的宽高以及包含控制的per-pixel的采样点数量组合的采样点数量
			coarseSampleOrderCustomNV.sampleLocationCount = 1;//指定自定义排序规则中的采样点的数量
			VkCoarseSampleLocationNV coarseSampleLocationNV{};//该结构体定义一个特定的像素位置，以及包含多个pixel的fragment中的一个采样点的索引
			{
				coarseSampleLocationNV.sample = 0;//是由pixelX和pixelY定义的像素中的包含的一个采样点的索引
				coarseSampleLocationNV.pixelX = 0;//添加到每个fragment左上角pixel的x坐标上用来定义包含采样点的pixel
				coarseSampleLocationNV.pixelY = 0;//添加到每个fragment左上角pixel的y坐标上用来定义包含采样点的pixel
				/*
				VkCoarseSampleLocationNV有效用法:
				1.pixelX 必须小于fragment的width，pixelY 必须小于fragment的height (基于pixel)
				2.sample 必须小于fragment的每个pixel包含的coverage samples的数量 
				*/
			}
			coarseSampleOrderCustomNV.pSampleLocations = &coarseSampleLocationNV;//一组VkCoarseSampleLocationNV数组指针，指明自定义排序规则中的采样点的位置,j号元素对应指定在 multi-pixel fragment中一个特定的像素x，y位置以及 coverage index j对应的采样点的索引
			/*
			VkCoarseSampleOrderCustomNV有效用法:
			1.shadingRate 必须是一个生成的fragment包含多个pixel的有效VkShadingRatePaletteEntryNV值
			2.sampleCount必须对应到列举在image的VkSampleCountFlags中的值，其对应bit值设置在VkPhysicalDeviceLimits::framebufferNoAttachmentsSampleCounts中
			3.sampleLocationCount 必须等于sampleCount * shadingRate.width * shadingRate.height，且必须小于或等于 VkPhysicalDeviceShadingRateImagePropertiesNV::shadingRateMaxCoarseSamples
			4.pSampleLocations中必须对每一个有效的pixelX, pixelY, 以及 sample的组合包含有一个实体
			*/
		
		}
		pipelineViewportCoarseSampleOrderStateCreateInfoNV.pCustomSampleOrders = &coarseSampleOrderCustomNV;//一个VkCoarseSampleOrderCustomNV 数组指针，指定每个绑定的fragment的区域以及采样点数量的组合的采样点排序规则，如果sampleOrderType不是VK_COARSE_SAMPLE_ORDER_TYPE_CUSTOM_NV，则该参数忽略
		/*
		VkPipelineViewportCoarseSampleOrderStateCreateInfoNV有效用法:
		1.如果sampleOrderType 不为VK_COARSE_SAMPLE_ORDER_TYPE_CUSTOM_NV，则customSamplerOrderCount 必须为0
		2.pCustomSampleOrders中不能包含两个shadingRate以及sampleCount相同的元素
		*/


		//动态设置包含多个pixel的fragment的每个pixel的采样点顺序      只有在后续绘制使用shader object或者绑定的graphics pipeline以VK_DYNAMIC_STATE_VIEWPORT_COARSE_SAMPLE_ORDER_NV创建才能使用，否则会只用VkPipelineViewportCoarseSampleOrderStateCreateInfoNV::pCustomSampleOrders中设置的， 如果 sampleOrderType为VK_COARSE_SAMPLE_ORDER_TYPE_CUSTOM_NV，则每个绑定的fragment的区域以及采样点数量的采样点排序规则没有在pCustomSampleOrders中指定，则将默认使用 VK_COARSE_SAMPLE_ORDER_TYPE_DEFAULT_NV.
		vkCmdSetCoarseSampleOrderNV(commandBuffer, VK_COARSE_SAMPLE_ORDER_TYPE_CUSTOM_NV/*sampleOrderType,指定包含多个pixel的fragment的采样点的排序机制 */, 1/*customSampleOrderCount，指定当排序采样点的顺序时，需要使用的自定义排序规则的数量 */, &coarseSampleOrderCustomNV/*pCustomSampleOrders，一个VkCoarseSampleOrderCustomNV 数组指针，指定每个绑定的fragment的区域以及采样点数量的组合的采样点排序规则*/);
		/*
		vkCmdSetCoarseSampleOrderNV有效用法:
		1.如果sampleOrderType 不为VK_COARSE_SAMPLE_ORDER_TYPE_CUSTOM_NV，则customSamplerOrderCount 必须为0
		2.pCustomSampleOrders中不能包含两个shadingRate以及sampleCount相同的元素

		*/


		//如果对包含 (x,y) pixel的图元的final shading rate导致每个pixel会调用多次fragment shader，则每个pixel的采样点会根据实现的顺序对应到一次 fragment sahder 调用，如果导致fragment包含多个pixel，则会生成一组fragment shader调用，每个pixel对应一个调用
	}


	//Sample Shading 参见p2719
	{
		/*
		Sample shading用来指定每个fragment的最小的不同采样点的数量，如果开启，则每个fragment至少要调用max(⌈ VkPipelineMultisampleStateCreateInfo::minSampleShading × VkPipelineMultisampleStateCreateInfo::rasterizationSamples ⌉, 1)次

		VkPipelineMultisampleStateCreateInfo::sampleShadingEnable为VK_TRUE即表示开启sample shading
		
		如果一个 fragment shader entry point静态使用了 SampleId 或者 SamplePosition修饰的变量，则表示sample shading开启，将使用1.0而不是minSampleShading，如果是使用了以Sample 修饰的变量，则表示sample shading可能开启，将使用minSampleShading如果该值为1.0
		*/
	}

	//Barycentric Interpolation   重心坐标插值 参见2719
	{
		/*
		当 fragmentShaderBarycentric 特性开启，且fragment shader inputs 中会为以PerVertexKHR 修饰的但还没有相关属性值的输入变量进行插值操作
		
		其他信息见p2720

		在fragment shader inputs 中以 BaryCoordKHR 或者 BaryCoordNoPerspKHR 修饰的变量将将会容纳相对于该该图元的三个顶点的屏幕空间坐标的三分量的权重值坐标，对于 BaryCoordKHR 使用透视插值，对于BaryCoordNoPerspKHR 使用线性插值
		*/
	}

	//Points   参见p2721
	{
		/*
		绘制一个点会产生一组以该点为重心的方形区域的fragments，边大小取决于 PointSize，该值在[pointSizeRange[0],pointSizeRange[1]]中，在该范围内可用的值是等间隔划分的，取决于 pointSizeGranularity，即例如范围为[1.0,2.0]，granularity为0.1，则可取值为1.0,1.1,1.2,1.3,1.4,1.5,1.6,1.7,1.8,1.9,2.0
		
		*/

		//Basic Point Rasterization  参见p2722
	}


	//Line Segments  参见p2722
	{
		//Line segment的rasterization options 受控于VkPipelineRasterizationLineStateCreateInfoKHR
		VkPipelineRasterizationLineStateCreateInfoKHR pipelineRasterizationLineStateCreateInfoKHR{};   //等同于VkPipelineRasterizationLineStateCreateInfoEXT
		pipelineRasterizationLineStateCreateInfoKHR.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_LINE_STATE_CREATE_INFO_EXT;
		pipelineRasterizationLineStateCreateInfoKHR.pNext = nullptr;
		pipelineRasterizationLineStateCreateInfoKHR.lineRasterizationMode = VK_LINE_RASTERIZATION_MODE_BRESENHAM_EXT;/*一个VkLineRasterizationModeKHR 值，指定了线段的rasterization模式
		VkLineRasterizationModeKHR:
		VK_LINE_RASTERIZATION_MODE_DEFAULT_KHR:  如果VkPhysicalDeviceLimits::strictLines 为VK_TRUE则等同于VK_LINE_RASTERIZATION_MODE_RECTANGULAR_KHR，否则线段将按照non-strictLines的平行四边形进行绘制，这些模式都定义在Basic Line Segment Rasterization 见p2729
		VK_LINE_RASTERIZATION_MODE_RECTANGULAR_KHR:  指定线段按照仿佛是从线中挤出的矩形进行绘制
		VK_LINE_RASTERIZATION_MODE_BRESENHAM_KHR:  指定线段按照和线段相交的像素菱形进行绘制，参考 Bresenham Line Segment Rasterization p2731
		VK_LINE_RASTERIZATION_MODE_RECTANGULAR_SMOOTH_KHR :  指定线段按照仿佛是从线中挤出的矩形进行绘制，但是线段的边缘会被模糊化，参考 Smooth Lines p2735
		*/
		pipelineRasterizationLineStateCreateInfoKHR.stippledLineEnable = VK_FALSE;//是否启用stippled line rasterization.参见p2733
		pipelineRasterizationLineStateCreateInfoKHR.lineStipplePattern = 0;//为用于stippled line rasterization的比特模板，如果stippledLineEnable为VK_TRUE，则该值忽略
		pipelineRasterizationLineStateCreateInfoKHR.lineStippleFactor = 0;//为用于stippled line rasterization的重复因子，如果stippledLineEnable为VK_TRUE，则该值忽略
		/*
		VkPipelineRasterizationLineStateCreateInfoKHR有效用法:
		1.如果lineRasterizationMode 为 VK_LINE_RASTERIZATION_MODE_RECTANGULAR_KHR，则rectangularLines 特性必须开启
		2.如果lineRasterizationMode 为 VK_LINE_RASTERIZATION_MODE_BRESENHAM_KHR，则bresenhamLines 特性必须开启
		3.如果lineRasterizationMode 为 VK_LINE_RASTERIZATION_MODE_RECTANGULAR_SMOOTH_KHR，则smoothLines 特性必须开启
		4.如果stippledLineEnable 为 VK_TRUE，则（1）如果lineRasterizationMode 为 VK_LINE_RASTERIZATION_MODE_RECTANGULAR_KHR，则stippledRectangularLines 特性必须开启
											   （2）如果lineRasterizationMode 为 VK_LINE_RASTERIZATION_MODE_BRESENHAM_KHR，则stippledBresenhamLines 特性必须开启
											   （3）如果lineRasterizationMode 为 VK_LINE_RASTERIZATION_MODE_RECTANGULAR_SMOOTH_KHR，则stippledSmoothLines 特性必须开启
											   （4）如果lineRasterizationMode 为 VK_LINE_RASTERIZATION_MODE_DEFAULT_KHR，则stippledRectangularLines 特性必须开启且VkPhysicalDeviceLimits::strictLines 必须为VK_TRUE

		*/




		//动态设置线段的rasterization options mode     只有在后续绘制使用shader object或者绑定的graphics pipeline以VK_DYNAMIC_STATE_LINE_RASTERIZATION_MODE_EXT创建才能使用，否则会只用VkPipelineRasterizationLineStateCreateInfoKHR::lineRasterizationMode中设置的， 
		vkCmdSetLineRasterizationModeEXT(commandBuffer, (VkLineRasterizationModeEXT)VK_LINE_RASTERIZATION_MODE_BRESENHAM_EXT/*lineRasterizationMode,指定lineRasterizationMode*/);
		/*
		vkCmdSetLineRasterizationModeEXT有效用法:
		1.extendedDynamicState3LineRasterizationMode 或者 shaderObject 特性至少有一个必须开启
		2.如果lineRasterizationMode 为 VK_LINE_RASTERIZATION_MODE_RECTANGULAR_KHR，则rectangularLines 特性必须开启
		3.如果lineRasterizationMode 为 VK_LINE_RASTERIZATION_MODE_BRESENHAM_KHR，则bresenhamLines 特性必须开启
		4.如果lineRasterizationMode 为 VK_LINE_RASTERIZATION_MODE_RECTANGULAR_SMOOTH_KHR，则smoothLines 特性必须开启
		*/

		//动态设置 stippledLineEnable      只有在后续绘制使用shader object或者绑定的graphics pipeline以VK_DYNAMIC_STATE_LINE_STIPPLE_ENABLE_EXT创建才能使用，否则会只用VkPipelineRasterizationLineStateCreateInfoKHR::stippledLineEnable中设置的， 
		vkCmdSetLineStippleEnableEXT(commandBuffer,VK_TRUE/*stippledLineEnable ，指定stippledLineEnable state*/);
		/*
		vkCmdSetLineStippleEnableEXT有效用法:
		1.extendedDynamicState3LineRasterizationMode 或者 shaderObject 特性至少有一个必须开启
		*/

		//动态设置 line width         只有在后续绘制使用shader object或者绑定的graphics pipeline以VK_DYNAMIC_STATE_LINE_WIDTH创建才能使用，否则会只用VkPipelineRasterizationStateCreateInfo::lineWidth中设置的， 
		vkCmdSetLineWidth(commandBuffer, 1/*lineWidth,为线段的rasterization操作的width.*/);
		/*
		vkCmdSetLineWidth有效用法:
		1.如果 wideLines 特性未开启，则lineWidth 必须为1.0
		*/




		// Basic Line Segment Rasterization  参见p2729
		{
			//对应 VK_LINE_RASTERIZATION_MODE_RECTANGULAR_KHR 或者 VK_LINE_RASTERIZATION_MODE_DEFAULT_KHR
		}

		//Bresenham Line Segment Rasterization  参见p2731
		{
			//对应  VK_LINE_RASTERIZATION_MODE_BRESENHAM_KHR
		}

		// Line Stipple 点线 参见p2733
		{
			/*
			如果 VkPipelineRasterizationLineStateCreateInfoKHR.stippledLineEnable 为 VK_TRUE，则会按照 VkPipelineRasterizationLineStateCreateInfoKHR.lineStipplePattern 和 VkPipelineRasterizationLineStateCreateInfoKHR.lineStippleFactor 进行点线的stipple rasterization，
			
			其中lineStipplePattern 是一个16bit模板确定在光栅化过程中哪个fragment保留哪个丢弃，lineStippleFactor 是一个计数值，让lineStipplePattern 中设置的有效的line striple 比特重复一定次数，
			
			判断是否丢弃根据   b  = |_  s / r _|  mod 16,其中b对应pattern中一个bit值，如果该比特值为1则保留，否则丢弃，s为生成的当前的fragment的计数值，r为lineStippleFactor，
			*/


			//动态设置line stipple state   ，等同于vkCmdSetLineStippleKHR，  只有在后续绘制使用shader object或者绑定的graphics pipeline以VK_DYNAMIC_STATE_LINE_STIPPLE_EXT 创建才能使用，否则会只用VkPipelineRasterizationLineStateCreateInfoKHR中设置的lineStippleFactor以及 lineStipplePattern
			vkCmdSetLineStippleEXT(commandBuffer, 0xAAAA/*lineStipplePattern，用于stippled line rasterization的比特模板*/, 1/*lineStippleFactor，用于stippled line rasterization的重复因子，必须在[1,256]之间*/);

		}


		// Smooth Lines  线平滑  参见p2735
		{
			//对应 VK_LINE_RASTERIZATION_MODE_RECTANGULAR_SMOOTH_KHR
		}
	}


	//Polygons  参见p2735
	{
		/*
		polygon来自于 triangle strip, triangle fan 或者一系列独立的triangles的分解，其光栅化操作受控于 VkPipelineRasterizationStateCreateInfo中的几个参数
		
		*/

		// Basic Polygon Rasterization   参见p2735
		{
			/*polygon的Rasterization操作首先要确定正反面，有由 VkPipelineRasterizationStateCreateInfo::frontFace规定
			VkFrontFace:
			VK_FRONT_FACE_COUNTER_CLOCKWISE :  指定一个通过计算正反面的公式计算得到的计算结果为正数的三角形为正面，计算公式见p2736
			VK_FRONT_FACE_CLOCKWISE :  指定一个通过计算正反面的公式计算得到的计算结果为负数的三角形为正面，计算公式见p2736
			*/

			//动态设置三角面的方向    ，等同于vkCmdSetFrontFaceEXT   ，  只有在后续绘制使用shader object或者绑定的graphics pipeline以VK_DYNAMIC_STATE_FRONT_FACE_EXT创建才能使用，否则会只用VkPipelineRasterizationStateCreateInfo中设置的frontFace
			vkCmdSetFrontFace(commandBuffer, VK_FRONT_FACE_COUNTER_CLOCKWISE/*frontFace，一个 VkFrontFace 值指明front-facing 三角形的方向*/);
			/*
			vkCmdSetFrontFace有效用法:
			1. extendedDynamicState特性开启，shaderObject特性开启以及创建该commandBuffer所在的VkInstance的VkApplicationInfo::apiVersion大于等于Version 1.3 这三个条件中至少需要满足一个

			*/
		

			/*
			一旦确定了正反面，polygon的Rasterization操作根据VkPipelineRasterizationStateCreateInfo::cullMode 进行剔除
			VkCullModeFlagBits:
			VK_CULL_MODE_NONE :  不进行剔除
			VK_CULL_MODE_FRONT_BIT :  剔除丢弃正面三角形				
			VK_CULL_MODE_BACK_BIT :  剔除丢弃反面三角形
			VK_CULL_MODE_FRONT_AND_BACKT :  剔除丢弃所有三角形 
			*/


			//动态设置三角面的剔除模式    ，等同于vkCmdSetCullModeEXT   ，  只有在后续绘制使用shader object或者绑定的graphics pipeline以VK_DYNAMIC_STATE_CULL_MODE_EXT创建才能使用，否则会只用VkPipelineRasterizationStateCreateInfo中设置的cullMode
			vkCmdSetCullMode(commandBuffer, VK_CULL_MODE_BACK_BIT/*cullMode，一个 VkCullModeFlagBits 组合值指明三角形的剔除模式*/);
			/*
			vkCmdSetCullMode有效用法:
			1. extendedDynamicState特性开启，shaderObject特性开启以及创建该commandBuffer所在的VkInstance的VkApplicationInfo::apiVersion大于等于Version 1.3 这三个条件中至少需要满足一个
			
			*/

		}

		//Polygon Mode   参见p2741
		{
			/*
			VkPipelineRasterizationStateCreateInfo::polygonMode指明了多边形的填充模式
			VkPolygonMode:
			VK_POLYGON_MODE_POINT:  指定polygon的顶点按点进行绘制
			VK_POLYGON_MODE_LINE:  指定polygon的边按照线段进行绘制
			VK_POLYGON_MODE_FILL:  指定polygon的内部区域按照多边形rasterization规则进行绘制
			VK_POLYGON_MODE_FILL_RECTANGLE_NV:  指定polygon的内部区域按照多边形rasterization规则进行绘制，但当在投影后采样点位置在图元三角形所在的轴向的边界盒中时会将该采样点考虑在内并且修改其渲染结果。其他信息见p2741

			如果polygon mode为VK_POLYGON_MODE_POINT，且如果 VkPhysicalDeviceMaintenance5PropertiesKHR::polygonModePointSize 为VK_TRUE，则使用 PointSize来控制点的大小，否则点的大小为1.0。
			*/ 

			//动态设置polygon mode    ，  只有在后续绘制使用shader object或者绑定的graphics pipeline以VK_DYNAMIC_STATE_POLYGON_MODE_EXT创建才能使用，否则会只用VkPipelineRasterizationStateCreateInfo中设置的polygonMode
			vkCmdSetPolygonModeEXT(commandBuffer, VK_POLYGON_MODE_FILL/*polygonMode，一个 VkPolygonMode 值指明多边形的填充模式*/);
			/*
			vkCmdSetPolygonModeEXT有效用法:
			1. extendedDynamicState3PolygonMode 或者 shaderObject 特性至少有一个必须开启
			2.如果fillModeNonSolid 特性没有开启，则polygonMode必须为VK_POLYGON_MODE_FILL或VK_POLYGON_MODE_FILL_RECTANGLE_NV
			3.如果VK_NV_fill_rectangle 扩展没有开启，则polygonMode不能为VK_POLYGON_MODE_FILL_RECTANGLE_NV
			*/
		
		
		}

		//Depth Bias  参见p2743
		{
			/*
			光栅化polygon得到的 fragments 深度值都可以加上以及计算得到的偏移值
			*/

			//开启depth bias可以通过调用 vkCmdSetDepthBiasEnable或者  vkCmdSetDepthBiasEnableEXT设置，又或者使用VkPipelineRasterizationStateCreateInfo::depthBiasEnable 进行设置


			//动态开启depth bias    ，等价于vkCmdSetDepthBiasEnableEXT ,  只有在后续绘制使用shader object或者绑定的graphics pipeline以VK_DYNAMIC_STATE_DEPTH_BIAS_ENABLE_EXT创建才能使用，否则会只用VkPipelineRasterizationStateCreateInfo中设置的depthBiasEnable
			vkCmdSetDepthBiasEnable(commandBuffer, VK_TRUE/*depthBiasEnable,控制是否要对fragments的深度值进行偏移 */);
			/*
			vkCmdSetDepthBiasEnable有效用法:
			1. extendedDynamicState2特性开启，shaderObject特性开启以及创建该commandBuffer所在的VkInstance的VkApplicationInfo::apiVersion大于等于Version 1.3 这三个条件中至少需要满足一个
			*/

			//Depth Bias Computation  参见p2744
			{
				/*
				Depth Bias的计算依赖参数
				depthBiasSlopeFactor:  对polygon的最大深度斜率进行缩放
				depthBiasConstantFactor:  对 depth attachment的参数r进行缩放
				缩放后的项的值要满足depthBiasClamp指明的范围

				> > Depth bias的计算公式以及这些参数的具体情况参见p2745
				*/

				//动态设置这些参数	， 等同于调用一个VkDepthBiasInfoEXT参数不含VkDepthBiasRepresentationInfoEXT的vkCmdSetDepthBias2EXT， 只有在后续绘制使用shader object或者绑定的graphics pipeline以VK_DYNAMIC_STATE_DEPTH_BIAS_EXT创建才能使用，否则会只用VkPipelineRasterizationStateCreateInfo中设置的depthBiasSlopeFactor,depthBiasConstantFactor,depthBiasClamp
				vkCmdSetDepthBias(commandBuffer, 1/*depthBiasConstantFactor，是一个标量因子控制一个添加到每个fragment的深度值*/, 
												0/*depthBiasClamp ，为fragment的最大或者最小的深度偏移，如果 depthBiasClamp 特性未开启，则该值必须为0 */,
												1/*depthBiasSlopeFactor,是一个标量因子，应用到fragment深度偏移计算的斜率上.*/);
			
				
				VkDepthBiasRepresentationInfoEXT depthBiasRepresentationInfoEXT{};//该结构体在深度偏移计算中的作用见 p2745
				depthBiasRepresentationInfoEXT.sType = VK_STRUCTURE_TYPE_MAX_ENUM;//该结构体时自己定义的，所以设置为非法值
				depthBiasRepresentationInfoEXT.pNext = nullptr;
				depthBiasRepresentationInfoEXT.depthBiasRepresentation = VK_DEPTH_BIAS_REPRESENTATION_FLOAT_EXT;/*是一个 VkDepthBiasRepresentationEXT 值，表示深度偏移值是如何表示的
				VkDepthBiasRepresentationEXT:
				VK_DEPTH_BIAS_REPRESENTATION_LEAST_REPRESENTABLE_VALUE_FORMAT_EXT:  指定深度偏移的表示为format的r分量的一个因子，参见Depth Bias Computation p2744
				VK_DEPTH_BIAS_REPRESENTATION_LEAST_REPRESENTABLE_VALUE_FORCE_UNORM_EXT:  指定深度偏移的表示为format的bit大小或者尾数的一个常量因子r，参见Depth Bias Computation p2744
				VK_DEPTH_BIAS_REPRESENTATION_FLOAT_EXT:  指定深度偏移的表示一个值为1的常量因子r.
				*/
				depthBiasRepresentationInfoEXT.depthBiasExact = VK_FALSE;//指定不允许实现缩放深度偏差值，以确保一个最小的可分辨距离
				/*
				VkDepthBiasRepresentationInfoEXT有效用法:
				1.如果leastRepresentableValueForceUnormRepresentation 特性未开启，则depthBiasRepresentation 不能为VK_DEPTH_BIAS_REPRESENTATION_LEAST_REPRESENTABLE_VALUE_FORCE_UNORM_EXT
				2.如果floatRepresentation 特性未开启，则depthBiasRepresentation 不能为VK_DEPTH_BIAS_REPRESENTATION_FLOAT_EXT
				3.如果depthBiasExact 特性未开启，则depthBiasExact 必须为VK_FALSE
				*/




				VkDepthBiasInfoEXT  depthBiasInfoEXT{};
				depthBiasInfoEXT.sType = VK_STRUCTURE_TYPE_MAX_ENUM;//自己定义的所以设置为非法值
				depthBiasInfoEXT.pNext = &depthBiasRepresentationInfoEXT;//如果pNext中不含VkDepthBiasRepresentationInfoEXT，则相当于含一个 depthBiasExact为VK_FALSE，depthBiasRepresentation为VK_DEPTH_BIAS_REPRESENTATION_LEAST_REPRESENTABLE_VALUE_FORMAT_EXT的VkDepthBiasRepresentationInfoEXT
				depthBiasInfoEXT.depthBiasClamp = 0.0f;//为fragment的最大或者最小的深度偏移，如果 depthBiasClamp 特性未开启，则该值必须为0 
				depthBiasInfoEXT.depthBiasSlopeFactor = 1.0f;//是一个标量因子，应用到fragment深度偏移计算的斜率上
				depthBiasInfoEXT.depthBiasConstantFactor = 0.0f;//是一个标量因子控制一个添加到每个fragment的深度值

				//动态设置深度偏移信息    ，  只有在后续绘制使用shader object或者绑定的graphics pipeline以VK_DYNAMIC_STATE_DEPTH_BIAS_EXT创建才能使用，否则会只用VkPipelineRasterizationStateCreateInfo中设置的depthBiasClamp,depthBiasSlopeFactor,depthBiasConstantFactor
				vkCmdSetDepthBias2EXT(commandBuffer, &depthBiasInfoEXT);
			
			}


			// Conservative Rasterization  参见p2751
			{
				/*
				如果VkPipelineRasterizationStateCreateInfo.pNext中含有一个VkPipelineRasterizationConservativeStateCreateInfoEXT，则其有参数可以控制 conservative rasterization
				如果不含该结构体，则相当于含一个 conservativeRasterizationMode为VK_CONSERVATIVE_RASTERIZATION_MODE_DISABLED_EXT的VkPipelineRasterizationConservativeStateCreateInfoEXT
				polygon可以设置VkPipelineRasterizationConservativeStateCreateInfoEXT.conservativeRasterizationMode 为VK_CONSERVATIVE_RASTERIZATION_MODE_OVERESTIMATE_EXT 或者 VK_CONSERVATIVE_RASTERIZATION_MODE_UNDERESTIMATE_EXT 来让开启 polygon conservative rasterization
				如果一个fragment的所有pixel都包含在图元内，则必须将 FullyCoveredEXT 设置为 VK_TRUE
				*/
				VkPipelineRasterizationConservativeStateCreateInfoEXT& pipelineRasterizationConservativeStateCreateInfoEXT = pipelineRasterizationStateCreateInfoEXT.pipelineRasterizationConservativeStateCreateInfoEXT;
				pipelineRasterizationConservativeStateCreateInfoEXT.flags = 0;//保留未来使用
				pipelineRasterizationConservativeStateCreateInfoEXT.conservativeRasterizationMode = VK_CONSERVATIVE_RASTERIZATION_MODE_UNDERESTIMATE_EXT;//指定conservative rasterization的模式
				/*
				VkConservativeRasterizationModeEXT
				VK_CONSERVATIVE_RASTERIZATION_MODE_DISABLED_EXT:  指定关闭conservative rasterization，使用常规的rasterization操作。
				VK_CONSERVATIVE_RASTERIZATION_MODE_OVERESTIMATE_EXT:  指定conservative rasterization的模式为overestimation 模式，即会产生fragment，只要该fragment的任何pixel的任何部分在图元中即可
				VK_CONSERVATIVE_RASTERIZATION_MODE_UNDERESTIMATE_EXT:  指定conservative rasterization的模式为underestimation 模式，即会产生fragment，只要该fragment的任何pixel的所有部分都在图元中即可
				*/
				pipelineRasterizationConservativeStateCreateInfoEXT.extraPrimitiveOverestimationSize = 1.0f;//指定在conservative rasterization过程中，超过VkPhysicalDeviceConservativeRasterizationPropertiesEXT::primitiveOverestimationSize中指定的产生图元在屏幕空间中X和Y方向上的额外大小，以像素为单位。如果conservativeRasterizationMode不是VK_CONSERVATIVE_RASTERIZATION_MODE_OVERESTIMATE_EXT，则该值被忽略。该值的范围为[0, VkPhysicalDeviceConservativeRasterizationPropertiesEXT::maxExtraPrimitiveOverestimationSize]
				


				//动态设置conservative rasterization mode    ，  只有在后续绘制使用shader object或者绑定的graphics pipeline以VK_DYNAMIC_STATE_CONSERVATIVE_RASTERIZATION_MODE_EXT创建才能使用，否则会只用VkPipelineRasterizationConservativeStateCreateInfoEXT中设置的conservativeRasterizationMode
				vkCmdSetConservativeRasterizationModeEXT(commandBuffer, VK_CONSERVATIVE_RASTERIZATION_MODE_OVERESTIMATE_EXT/*conservativeRasterizationMode，指定conservative rasterization的模式*/);
				/*
				vkCmdSetConservativeRasterizationModeEXT有效用法:
				1. extendedDynamicState3ConservativeRasterizationMode 或者 shaderObject 特性至少有一个必须开启
				
				*/


				//动态设置 extraPrimitiveOverestimationSize   ，  只有在后续绘制使用shader object或者绑定的graphics pipeline以VK_DYNAMIC_STATE_EXTRA_PRIMITIVE_OVERESTIMATION_SIZE_EXT创建才能使用，否则会只用VkPipelineRasterizationConservativeStateCreateInfoEXT中设置的extraPrimitiveOverestimationSize
				vkCmdSetExtraPrimitiveOverestimationSizeEXT(commandBuffer, 1.0f/*extraPrimitiveOverestimationSize，指定 extraPrimitiveOverestimationSize*/);
				/*
				vkCmdSetExtraPrimitiveOverestimationSizeEXT有效用法:
				1.  extendedDynamicState3ExtraPrimitiveOverestimationSize 或者 shaderObject 特性至少有一个必须开启
				2. extendedDynamicState3ExtraPrimitiveOverestimationSize的范围为[0, VkPhysicalDeviceConservativeRasterizationPropertiesEXT::maxExtraPrimitiveOverestimationSize]
				*/

				
			}
		}
	}
}

void PipelineStageProcessingTest::FragmentOperationsTest()
{
	/*
	rasterization产生的fragments会经过一系列操作来决定fragment shader产生的值如何写到framebuffer
	这些操作为(顺序依次):
	1. Discard rectangles test
	2. Scissor test
	3. Exclusive scissor test
	4. Sample mask test
	5. Certain Fragment shading operations:
				>  Sample Mask Accesses
				>  Tile Image Reads
				>  Depth Replacement
				>  Stencil Reference Replacement
				>  Interlocked Operations
	6. Multisample coverage
	7. Depth bounds test
	8. Stencil test
	9. Depth test
	10. Representative fragment test
	11. Sample counting
	12. Coverage to color
	13. Coverage reduction
	14. Coverage modulation
	

	以上的操作在满足一定条件的情况下顺序会有所不同，具体情况参见p2759

	在pipeline满足一些条件的时候可能会有一些额外的操作，具体情况参见p2759
	
	*/

	VkCommandBuffer commandBuffer{/*假设这是一个有效的VkCommandBuffer*/ };

	//Discard Rectangles Test  参见p2760
	{
		/*
		discard rectangle test会比较fragment中的采样点的framebuffer坐标 (xf,yf)是否在一个discard rectangle内，并进行相关操作
		
		discard rectangles可以在创建pipeline的VkPipelineDiscardRectangleStateCreateInfoEXT中设置，也可以在运行时通过vkCmdSetDiscardRectangleEXT设置

		如果一个fragment的采样点的framebuffer坐标 (xf,yf)在任何一个discard rectangle内即其坐标满足xf,yf对应在范围 [VkRect2D::offset.x, VkRect2D::offset.x + VkRect2D::extent.x),[VkRect2D::offset.y, VkRect2D::offset.y + VkRect2D::extent.y)内，则如果该test使用inclusive模式，则不在任何rectangle内的采样点的coverage比特位会被设为0，如果使用exclusive,则在任何rectangle内的采样点的coverage比特位会被设为0，如果不指明discard rectangle，则不会改变采样点的coverage比特位
		*/


		//在VkGraphicsPipelineCreateInfo.pNext中包含一个 VkPipelineDiscardRectangleStateCreateInfoEXT 结构体，来设置discard rectangle test的相关参数
		VkPipelineDiscardRectangleStateCreateInfoEXT  pipelineDiscardRectangleStateCreateInfoEXT{};
		pipelineDiscardRectangleStateCreateInfoEXT.sType = VK_STRUCTURE_TYPE_PIPELINE_DISCARD_RECTANGLE_STATE_CREATE_INFO_EXT;
		pipelineDiscardRectangleStateCreateInfoEXT.pNext = 0;
		pipelineDiscardRectangleStateCreateInfoEXT.flags = 0;
		pipelineDiscardRectangleStateCreateInfoEXT.discardRectangleMode = VK_DISCARD_RECTANGLE_MODE_INCLUSIVE_EXT;//一个 VkDiscardRectangleModeEXT值，指明discard rectangle test是inclusive还是 exclusive的，如果pipeline以VK_DYNAMIC_STATE_DISCARD_RECTANGLE_MODE_EXT创建，则该参数忽略
		/*
		VkDiscardRectangleModeEXT:
		VK_DISCARD_RECTANGLE_MODE_INCLUSIVE_EXT:  指明 discard rectangle test 是 inclusive的.
		VK_DISCARD_RECTANGLE_MODE_EXCLUSIVE_EXT:  指明 discard rectangle test 是 exclusive的
		*/
		pipelineDiscardRectangleStateCreateInfoEXT.discardRectangleCount = 1;//为使用的 discard rectangles 的数量，必须小于等于VkPhysicalDeviceDiscardRectanglePropertiesEXT::maxDiscardRectangles
		VkRect2D discardRectangle;
		discardRectangle.extent = VkExtent2D{ .width = 1,.height = 1 };
		discardRectangle.offset = VkOffset2D{ .x = 0,.y = 2 };
		pipelineDiscardRectangleStateCreateInfoEXT.pDiscardRectangles = &discardRectangle;//指向一个 VkRect2D 数组，每个数组元素对应一个 discard rectangle，如果pipeline以VK_DYNAMIC_STATE_DISCARD_RECTANGLE_EXT创建，则该参数忽略



		//动态设置discard rectangles    ，更新索引为[ firstDiscardRectangle, firstDiscardRectangle + discardRectangleCount)的discard rectangle，  只有在后续绘制使用shader object或者绑定的graphics pipeline以VK_DYNAMIC_STATE_DISCARD_RECTANGLE_EXT创建才能使用，否则会只用VkPipelineDiscardRectangleStateCreateInfoEXT中设置的pDiscardRectangles
		vkCmdSetDiscardRectangleEXT(commandBuffer, 0/*firstDiscardRectangle，是该命令更新的第一个discard rectangle的索引*/, 1/*discardRectangleCount，是该命令更新的discard rectangle的数量*/,
										&discardRectangle/*pDiscardRectangles，指向一个 VkRect2D 数组，每个数组元素对应一个 discard rectangle */);
		/*
		vkCmdSetDiscardRectangleEXT有效用法:
		1.firstDiscardRectangle + discardRectangleCount 必须小于等于VkPhysicalDeviceDiscardRectanglePropertiesEXT::maxDiscardRectangles
		2.pDiscardRectangles中每个元素的offset的x以及y必须大于0
		3.pDiscardRectangles中每个元素的(offset.x + extent.width)， (offset.y + extent.height) 不能导致符号整数加法溢出
		4.如果该命令记录在开启了VkCommandBufferInheritanceViewportScissorInfoNV::viewportScissor2D的 secondary command buffer中，则该函数不能被调用
		*/



		//动态设置是否启用discard rectangles    ，  只有在后续绘制使用shader object或者绑定的graphics pipeline以VK_DYNAMIC_STATE_DISCARD_RECTANGLE_ENABLE_EXT创建才能使用，否则会只用VkPipelineDiscardRectangleStateCreateInfoEXT中设置的discardRectangleCount来隐式指出，即大于0的值便是启用discard rectangles
		vkCmdSetDiscardRectangleEnableEXT(commandBuffer, VK_TRUE/*discardRectangleEnable,指明是否启用 discard rectangles*/);
		/*
		vkCmdSetDiscardRectangleEnableEXT有效用法:
		1. VK_EXT_discard_rectangles拓展必须开启，且必须支持该拓展的至少 specVersion 2版本
		
		*/

		//动态设置discard rectangle mode    ，  只有在后续绘制使用shader object或者绑定的graphics pipeline以VK_DYNAMIC_STATE_DISCARD_RECTANGLE_MODE_EXT创建才能使用，否则会只用VkPipelineDiscardRectangleStateCreateInfoEXT中设置的discardRectangleMode
		vkCmdSetDiscardRectangleModeEXT(commandBuffer, VK_DISCARD_RECTANGLE_MODE_INCLUSIVE_EXT/*discardRectangleMode, 指定所有discard rectangles的discard rectangle mode, 为 inclusive 或者 exclusive.*/);
		/*
		vkCmdSetDiscardRectangleModeEXT有效用法:
		1. VK_EXT_discard_rectangles拓展必须开启，且必须支持该拓展的至少 specVersion 2版本
		*/



	}


	//Scissor Test  参见p2766
	{
		/*
		 scissor test会比较fragment中的采样点的framebuffer坐标 (xf,yf)是否在一个该fragment的 ViewportIndex对应的 scissor rectangle 外，并进行相关操作
		
		每个scissor rectangle可以在创建pipeline的VkPipelineViewportStateCreateInfo中设置，也可以在运行时通过vkCmdSetScissor设置
		
		如果一个fragment的采样点的framebuffer坐标 (xf,yf)在任何一个scissor rectangle外即其坐标满足xf,yf对应在范围 [VkRect2D::offset.x, VkRect2D::offset.x + VkRect2D::extent.x),[VkRect2D::offset.y, VkRect2D::offset.y + VkRect2D::extent.y)外，则任何在 ViewportIndex对应的scissor rectangle外的采样点的coverage比特位会被设为0
		
		如果render pass transform 开启，则会先进行viewport transform，然后再进行scissor test
		*/

		VkRect2D scissor{};
		scissor.extent = VkExtent2D{ .width = 1,.height = 1 };
		scissor.offset = VkOffset2D{ .x = 0,.y = 0 };


		//动态设置scissor    ，更新索引为[ firstScissor, firstScissor + scissorCount)的scissor，  只有在后续绘制使用shader object或者绑定的graphics pipeline以VK_DYNAMIC_STATE_SCISSOR_EXT创建才能使用，否则会只用VkPipelineViewportStateCreateInfo中设置的pScissors
		vkCmdSetScissor(commandBuffer, 0/*firstScissor，是该命令更新的第一个scissor rectangle的索引*/, 1/*scissorCount，是该命令更新的scissor rectangle的数量*/,
								&scissor/* pScissors,指向一个 VkRect2D 数组，每个数组元素对应一个 scissor rectangle*/);
		/*
		vkCmdSetScissor有效用法:
		1.firstScissor + scissorCount 必须在[1,VkPhysicalDeviceLimits::maxViewports]中
		2.如果multiViewport 特性未开启，则firstScissor必须为0，scissorCount必须为1
		3.pScissors中每个元素的offset的x以及y必须大于等于0
		4.pScissors中每个元素的(offset.x + extent.width)， (offset.y + extent.height) 不能导致符号整数加法溢出
		5.如果该命令记录在开启了VkCommandBufferInheritanceViewportScissorInfoNV::viewportScissor2D的 secondary command buffer中，则该函数不能被调用

		*/
	}

	//Exclusive Scissor Test   参见p2768
	{
		/*
		 exclusive scissor test会比较fragment中的采样点的framebuffer坐标 (xf,yf)是否在一个该fragment的 ViewportIndex对应的exclusive scissor rectangle 外，并进行相关操作

		每个exclusive scissor rectangle可以在创建pipeline的VkPipelineViewportExclusiveScissorStateCreateInfoNV中设置，也可以在运行时通过 vkCmdSetExclusiveScissorNV 设置

		如果一个fragment的采样点的framebuffer坐标 (xf,yf)在任何一个exclusive scissor rectangle内即其坐标满足xf,yf对应在范围 [VkRect2D::offset.x, VkRect2D::offset.x + VkRect2D::extent.x),[VkRect2D::offset.y, VkRect2D::offset.y + VkRect2D::extent.y)内，则任何在 ViewportIndex对应的exclusive scissor rectangle内的采样点的coverage比特位会被设为0，如果不指明exclusive scissor rectangle，则不会改变采样点的coverage比特位

		*/


		//在VkGraphicsPipelineCreateInfo.pNext中包含VkPipelineViewportExclusiveScissorStateCreateInfoNV指明exclusive scissor rectagles，  如果不包含该结构体，则相当于包含一个exclusiveScissorCount为0的该结构体，  如果pipeline以VK_DYNAMIC_STATE_EXCLUSIVE_SCISSOR_NV创建，则该结构体中的pExclusiveScissors参数忽略
		VkPipelineViewportExclusiveScissorStateCreateInfoNV pipelineViewportExclusiveScissorStateCreateInfoNV{};
		pipelineViewportExclusiveScissorStateCreateInfoNV.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_EXCLUSIVE_SCISSOR_STATE_CREATE_INFO_NV;
		pipelineViewportExclusiveScissorStateCreateInfoNV.pNext = nullptr;
		pipelineViewportExclusiveScissorStateCreateInfoNV.exclusiveScissorCount = 1;//为exclusive scissor rectangles.的数量
		VkRect2D exclusiveScissor{};
		exclusiveScissor.extent = VkExtent2D{ .width = 1,.height = 1 };
		exclusiveScissor.offset = VkOffset2D{ .x = 0,.y = 0 };
		pipelineViewportExclusiveScissorStateCreateInfoNV.pExclusiveScissors = &exclusiveScissor;//指向一个 VkRect2D 数组，每个数组元素对应一个 exclusive scissor rectangle
		/*
		VkPipelineViewportExclusiveScissorStateCreateInfoNV有效用法:
		1.如果multiViewport 特性未开启，则exclusiveScissorCount必须为0或1
		2.exclusiveScissorCount 必须小于等于VkPhysicalDeviceLimits::maxViewports
		3.exclusiveScissorCount必须为0或者大于等于VkPipelineViewportStateCreateInfo::viewportCount
		*/



		//动态设置 exclusive scissor rectangles    ，更新索引为[ firstExclusiveScissor, firstExclusiveScissor + exclusiveScissorCount)的exclusive scissor rectangle，  只有在后续绘制使用shader object或者绑定的graphics pipeline以VK_DYNAMIC_STATE_EXCLUSIVE_SCISSOR_NV创建才能使用，否则会只用 VkPipelineViewportExclusiveScissorStateCreateInfoNV中设置的pExclusiveScissors
		vkCmdSetExclusiveScissorNV(commandBuffer, 0/*firstExclusiveScissor，是该命令更新的第一个exclusive scissor rectangle的索引*/, 1/*exclusiveScissorCount，是该命令更新的exclusive scissor rectangle的数量*/,
			&exclusiveScissor/* pExclusiveScissors,指向一个 VkRect2D 数组，每个数组元素对应一个exclusive scissor rectangle*/);
		/*
		vkCmdSetExclusiveScissorNV有效用法:
		1.exclusiveScissor 特性必须开启
		2.firstExclusiveScissor + exclusiveScissorCount 必须在[1,VkPhysicalDeviceLimits::maxViewports]中
		3.如果multiViewport 特性未开启，则firstExclusiveScissor必须为0，exclusiveScissorCount必须为1
		4.pExclusiveScissors中每个元素的offset的x以及y必须大于等于0
		5.pExclusiveScissors中每个元素的(offset.x + extent.width)， (offset.y + extent.height) 不能导致符号整数加法溢出

		*/


		VkBool32 enableExclusiveScissorRectagle = VK_TRUE;
		//动态设置一个exclusive scissor rectangle是否启用    ，更新索引为[ firstExclusiveScissor, firstExclusiveScissor + exclusiveScissorCount)的exclusive scissor rectangle的是否启用信息 ，  只有在后续绘制使用shader object或者绑定的graphics pipeline以VK_DYNAMIC_STATE_EXCLUSIVE_SCISSOR_ENABLE_NV创建才能使用，否则会只用 VkPipelineViewportExclusiveScissorStateCreateInfoNV中设置的exclusiveScissorCount来隐式指出，即从0到exclusiveScissorCount-1的索引的exclusive scissor rectangle启用，剩余到 VkPhysicalDeviceLimits::maxViewports的不启用
		vkCmdSetExclusiveScissorEnableNV(commandBuffer, 0/*firstExclusiveScissor，是该命令更新的第一个exclusive scissor rectangle的索引*/, 1/*exclusiveScissorCount，是该命令更新的exclusive scissor rectangle的数量*/,
														&enableExclusiveScissorRectagle/*pExclusiveScissorEnables，是一组VkBool32数组指针，指明exclusive scissor 是否开启*/);
		/*
		vkCmdSetExclusiveScissorEnableNV有效用法:
		1. exclusiveScissor 特性必须开启，实现必须支持 VK_NV_scissor_exclusive拓展的至少 specVersion 2版本
		
		*/


	}


	//Sample Mask Test  参见p2773
	{
		/*
		 sample mask test比较fragment的 coverage mask以及VkPipelineMultisampleStateCreateInfo::pSampleMask定义的mask，如果pSampleMask中的设置为0，则对应的采样点的coverage比特位会被设为0

		
		*/

		VkSampleMask sampleMask = 0x00000001;
		//动态设置sample mask    ， 只有在后续绘制使用shader object或者绑定的graphics pipeline以VK_DYNAMIC_STATE_SAMPLE_MASK_EXT创建才能使用，否则会只用VkPipelineMultisampleStateCreateInfo中设置的pSampleMask
		vkCmdSetSampleMaskEXT(commandBuffer,VK_SAMPLE_COUNT_1_BIT/*samples,指定pSampleMask中元素数量.*/ , &sampleMask/*pSampleMask，指向一个 VkSampleMask 数组，每个数组元素对应一个 sample mask,数组大小由samples参数决定*/);
		/*
		vkCmdSetSampleMaskEXT有效用法:
		1. extendedDynamicState3SampleMask 或者shaderObject特性必须有一个开启


		*/

	}


	//Fragment Shading  参见p2775
	{
		/*
		Fragment shaders会对每个fragment调用处理，或者是以 helper invocations处理
		
		Fragment shaders会对每个fragment是否执行，执行多少次条件详情参见p2755
		*/


		//Sample Mask  参见p2776


		//Fragment Shader Tile Image Reads   参见p2776
		{
			/*
			如果 VK_EXT_shader_tile_image 拓展开启，则会将framebuffer划分为一个个小的tile，一个tile image为 framebuffer attachment中fragment在tile区域内的一个视图
			
			*/


			//Depth Replacement  参见p2778

			//Stencil Reference Replacement 参见p2778

			// Interlocked Operations  参见p2778
			{
				/*
				OpBeginInvocationInterlockEXT 以及 OpEndInvocationInterlockEXT 定义片段着色器的一部分，它对在其中执行的操作施加额外的排序约束，
				具体的顺序约束取决于执行模式 execution mode，参见 ShadingRateInterlockOrderedEXT， ShadingRateInterlockUnorderedEXT，  PixelInterlockOrderedEXT，
												PixelInterlockUnorderedEXT，SampleInterlockOrderedEXT，SampleInterlockUnorderedEXT，具体情况见p2778
				*/
			}



		}



	}


	//Multisample Coverage  参见p2779
	{
		/*
		如果一个 fragment shader激活或者其entry point interface包含以 SampleMask 但不以 OverrideCoverageNV修饰的输出变量，则coverage mask将会根据以 SampleMask修饰的输出变量输出的值通过操作 ANDed产生一个新的coverage mask，

		如果以SampleMask 以及 OverrideCoverageNV修饰输出变量，则会直接替换为shader输出的coverage mask

		如果不含以SampleMask修饰的输出变量则不会更改coverage mask

		然后fragment的alpha值以及 coverage mask 会根据 line coverage factor（如果VkPipelineRasterizationStateCreateInfo::lineRasterizationMode为 VK_LINE_RASTERIZATION_MODE_RECTANGULAR_SMOOTH_KHR ）以及且VkPipelineMultisampleStateCreateInfo的alphaToCoverageEnable以及alphaToOneEnable 参数进行修改
		
		*/


		//动态设置 alphaToCoverageEnable      只有在后续绘制使用shader object或者绑定的graphics pipeline以VK_DYNAMIC_STATE_ALPHA_TO_COVERAGE_ENABLE_EXT创建才能使用，否则会只用 VkPipelineMultisampleStateCreateInfo::alphaToCoverageEnable设置的
		vkCmdSetAlphaToCoverageEnableEXT(commandBuffer, VK_TRUE/*alphaToCoverageEnable,指定 alphaToCoverageEnable state*/);
		/*
		vkCmdSetAlphaToCoverageEnableEXT有效用法:
		1.extendedDynamicState3AlphaToCoverageEnable 或者shaderObject特性必须有一个要开启
		*/

		//动态设置  alphaToOneEnable      只有在后续绘制使用shader object或者绑定的graphics pipeline以VK_DYNAMIC_STATE_ALPHA_TO_ONE_ENABLE_EXT创建才能使用，否则会只用 VkPipelineMultisampleStateCreateInfo::alphaToOneEnable设置的
		vkCmdSetAlphaToOneEnableEXT(commandBuffer, VK_TRUE/*alphaToOneEnable,指定 alphaToOneEnable state*/);
		/*
		vkCmdSetAlphaToOneEnableEXT有效用法:
		1.extendedDynamicState3AlphaToOneEnable 或者shaderObject特性必须有一个要开启
		2.如果alphaToOne 特性未开启，则alphaToOneEnable 必须为 VK_FALSE
		*/


		//该章节引用的alpha值来源于以 Location 和 Index修饰为0的输出变量，其他对该alpha的操作详细信息见p2782
	}



	//Depth and Stencil Operations   参见p2782
	{
		//pipeline的 depth bounds tests, stencil test, 以及 depth test由VkPipelineDepthStencilStateCreateInfo 控制
		VkPipelineDepthStencilStateCreateInfo pipelineDepthStencilStateCreateInfo{};
		pipelineDepthStencilStateCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
		pipelineDepthStencilStateCreateInfo.pNext = nullptr;
		pipelineDepthStencilStateCreateInfo.flags = VK_PIPELINE_DEPTH_STENCIL_STATE_CREATE_RASTERIZATION_ORDER_ATTACHMENT_DEPTH_ACCESS_BIT_EXT;//是一个VkPipelineDepthStencilStateCreateFlagBits组合值位掩码，指定额外的depth/stencil state 信息
		/*
		VkPipelineDepthStencilStateCreateFlagBits:
		VK_PIPELINE_DEPTH_STENCIL_STATE_CREATE_RASTERIZATION_ORDER_ATTACHMENT_DEPTH_ACCESS_BIT_EXT:  指明访问depth/stencil 以及 input attachments的depth aspect将有隐式的framebuffer-local memory dependencies.对该场景下memory dependencies的描述见p2785
		VK_PIPELINE_DEPTH_STENCIL_STATE_CREATE_RASTERIZATION_ORDER_ATTACHMENT_STENCIL_ACCESS_BIT_EXT:  指明访问depth/stencil 以及 input attachments的stencil aspect将有隐式的framebuffer-local memory dependencies.对该场景下memory dependencies的描述见p2786

		*/
		pipelineDepthStencilStateCreateInfo.depthTestEnable = VK_TRUE;//控制 depth testing 是否开启
		pipelineDepthStencilStateCreateInfo.depthCompareOp = VK_COMPARE_OP_LESS;//是一个VkCompareOp 值指明在depth testing步骤中depth comparison操作的比较操作符
		pipelineDepthStencilStateCreateInfo.depthWriteEnable = VK_TRUE;//控制当depthTestEnable 为 VK_TRUE的时候depth  writes是否开启，如果depthTestEnable 为 VK_FALSE，则永不会开启depth  writes
		pipelineDepthStencilStateCreateInfo.stencilTestEnable = VK_TRUE;//控制是否开启 stencil testing
		VkStencilOpState back{};
		{
			back.failOp = VK_STENCIL_OP_INVERT;
			back.passOp = VK_STENCIL_OP_ZERO;
			back.depthFailOp = VK_STENCIL_OP_KEEP;
			back.compareOp = VK_COMPARE_OP_LESS;
			back.compareMask = 0;
			back.writeMask = 0;
			back.reference = 0;
		}
		pipelineDepthStencilStateCreateInfo.back = back;//为VkStencilOpState 值控制对应的stencil test的相关参数
		VkStencilOpState front{};
		{
			front.failOp = VK_STENCIL_OP_INVERT;
			front.passOp = VK_STENCIL_OP_ZERO;
			front.depthFailOp = VK_STENCIL_OP_KEEP;
			front.compareOp = VK_COMPARE_OP_LESS;
			front.compareMask = 0;
			front.writeMask = 0;
			front.reference = 0;
		}
		pipelineDepthStencilStateCreateInfo.front = front;//为VkStencilOpState 值控制对应的stencil test的相关参数
		pipelineDepthStencilStateCreateInfo.depthBoundsTestEnable = VK_TRUE;//控制是否开启depth bounds testing
		pipelineDepthStencilStateCreateInfo.minDepthBounds = 0;//指明depth bounds testing中的深度边界的最小值
		pipelineDepthStencilStateCreateInfo.maxDepthBounds = 1;//指明depth bounds testing中的深度边界的最大值
		/*
		VkPipelineDepthStencilStateCreateInfo有效用法:
		1.如果depthBounds 特性未开启，则depthBoundsTestEnable必须为VK_FALSE
		2.如果VK_KHR_portability_subset 拓展开启，且VkPhysicalDevicePortabilitySubsetFeaturesKHR::separateStencilMaskRef为VK_FALSE，且VkPipelineDepthStencilStateCreateInfo::stencilTestEnable为VK_TRUE，且VkPipelineRasterizationStateCreateInfo::cullMode为VK_CULL_MODE_NONE，
						则front和back中的reference必须相同
		3.如果rasterizationOrderDepthAttachmentAccess 未开启，则flags不能包含VK_PIPELINE_DEPTH_STENCIL_STATE_CREATE_RASTERIZATION_ORDER_ATTACHMENT_DEPTH_ACCESS_BIT_EXT
		4.如果rasterizationOrderStencilAttachmentAccess 特性未开启，则flags不能包含VK_PIPELINE_DEPTH_STENCIL_STATE_CREATE_RASTERIZATION_ORDER_ATTACHMENT_STENCIL_ACCESS_BIT_EXT

		*/


	}


	// Depth Bounds Test  参见p2786
	{
		/*
		 depth bounds test将比较每个采样点的深度值z是否在[minDepthBounds ,maxDepthBounds]给定的范围中，如果不在，则该采样的点coverage mask会被设为0
	
		如果未开启depth bounds test或者不含depth attachment,则不会修改采样点的coverage mask

		该相关参数可以通过VkPipelineDepthStencilStateCreateInfo 指定或者vkCmdSetDepthBoundsTestEnable 以及 vkCmdSetDepthBounds动态指定

		*/



		//动态设置是否开启depth bounds test       ，等同于vkCmdSetDepthBoundsTestEnableEXT，  只有在后续绘制使用shader object或者绑定的graphics pipeline以VK_DYNAMIC_STATE_DEPTH_BOUNDS_TEST_ENABLE创建才能使用，否则会只用  VkPipelineDepthStencilStateCreateInfo::depthBoundsTestEnable设置的
		vkCmdSetDepthBoundsTestEnable(commandBuffer, VK_TRUE/*depthBoundsTestEnable,指明是否开启 depth bounds test .*/);
		/*
		vkCmdSetDepthBoundsTestEnable有效用法:
		1.extendedDynamicState特性开启，shaderObject特性开启以及创建该commandBuffer所在的VkInstance的VkApplicationInfo::apiVersion大于等于Version 1.3 这三个条件中至少需要满足一个
			
		*/

		//动态设置是否开启depth bounds test的范围       ，  只有在后续绘制使用shader object或者绑定的graphics pipeline以VK_DYNAMIC_STATE_DEPTH_BOUNDS_TEST_ENABLE创建才能使用，否则会只用  VkPipelineDepthStencilStateCreateInfo::depthBoundsTestEnable设置的
		vkCmdSetDepthBounds(commandBuffer, 0.0f/*minDepthBounds,指明depth bounds test的最小值 .*/,1.0f /*maxDepthBounds,指明depth bounds test的最大值  .*/);
		/*
		vkCmdSetDepthBounds有效用法:
		1.如果VK_EXT_depth_range_unrestricted 拓展未开启，minDepthBounds 以及maxDepthBounds 必须在[0.0,1.0]之间
		*/
	}



	// Stencil Test  参见p2789
	{
		/*
		stencil test将比较每个采样点的在 stencil attachment 中的值Sa 和一个引用的值reference，然后会根据测试的结果更新其在stencil attachment中的值以及coverage mask

		如果未开启stencil test，无论是通过VkPipelineDepthStencilStateCreateInfo::stencilTestEnable还是vkCmdSetStencilTestEnable 设置，或者不含stencil attachment，则采样点的coverage mask不会改变
		
		stencil test将由back 或者 front stencil state两个中的一个控制，如果当前的fragment所在的图元为  back-facing polygons的则由back决定，如果当前的fragment所在的图元为  front-facing polygons的或者其他图元的则由front决定

		比较操作通过指定一个vkCmdSetStencilOp::compareOp,或者 VkStencilOpState::compareOp的 VkCompareOp值决定

		back 或者 front stencil state中的compare mask Sc 以及 stencil reference 值 Sr由VkPipelineDepthStencilStateCreateInfo中的值或者 vkCmdSetStencilCompareMask以及vkCmdSetStencilReference.设置，
		Sr 以及 Sa会分别和Sc 进行与（AND）操作得到一个新的compare mask以及 stencil reference值，这两个新的值将会根据VkCompareOp指定的值进行比较操作的到一个值Sg，如果比较失败，则该采样点的coverage mask会被设置为0
		VkCompareOp指定的值可以由 vkCmdSetStencilOp 或者 VkPipelineDepthStencilStateCreateInfo指定，如果比较失败，将使用failOp 来处理Sg，如果比较通过，则将使用 VkPipelineDepthStencilStateCreateInfo::passOp（depth test通过）或者 VkPipelineDepthStencilStateCreateInfo::depthFailOp（depth test失败）
		比较成功，Sg将会更新到Sa，根据back 或者 front stencil state中定义的writeMask(Sw)，根据公式Sa =  (Sa & ¬Sw) | (Sg & Sw)


		*/

		//动态设置是否开启stencil test       ，等同于vkCmdSetStencilTestEnableEXT，  只有在后续绘制使用shader object或者绑定的graphics pipeline以VK_DYNAMIC_STATE_STENCIL_TEST_ENABLE创建才能使用，否则会只用VkPipelineDepthStencilStateCreateInfo::stencilTestEnable 设置的
		vkCmdSetStencilTestEnable(commandBuffer, VK_TRUE/*stencilTestEnable,指明是否开启stencil test .*/);
		/*
		vkCmdSetStencilTestEnable有效用法:
		1.extendedDynamicState特性开启，shaderObject特性开启以及创建该commandBuffer所在的VkInstance的VkApplicationInfo::apiVersion大于等于Version 1.3 这三个条件中至少需要满足一个

		*/

		VkStencilFaceFlagBits stencilFaceFlagBits = VK_STENCIL_FACE_FRONT_BIT;
		/*
		VkStencilFaceFlagBits:
		VK_STENCIL_FACE_FRONT_BIT: 指定只更新front stencil state 
		VK_STENCIL_FACE_BACK_BIT: 指定只更新back stencil state  specifies that only the back set of stencil state is updated.
		VK_STENCIL_FACE_FRONT_AND_BACK:  指定更新front 以及 stencil state ，为VK_STENCIL_FACE_FRONT_BIT以及VK_STENCIL_FACE_BACK_BIT组合值
		*/


		//动态设置stencil test  的参数     ，等同于vkCmdSetStencilOpEXT，  只有在后续绘制使用shader object或者绑定的graphics pipeline以 VK_DYNAMIC_STATE_STENCIL_OP创建才能使用，否则会只用VkPipelineDepthStencilStateCreateInfo::failOp, passOp, depthFailOp, 以及 compareOp设置的
		vkCmdSetStencilOp(commandBuffer, stencilFaceFlagBits/*faceMask,是VkStencilFaceFlagBits 组合值位掩码指明更新哪组stencil state.*/, VK_STENCIL_OP_INVERT/*failOp,是一个VkStencilOp值指明采样点在stencil test失败后的操作.*/,
					VK_STENCIL_OP_KEEP/*passOp, 是一个VkStencilOp 值指明采样点在同时通过depth以及 stencil test后的操作.*/, VK_STENCIL_OP_KEEP/*depthFailOp,一个VkStencilOp  值指明采样点通过stencil test但没有通过depth test的操作.*/, 
					VK_COMPARE_OP_LESS/*compareOp,是一个 VkCompareOp 值指明用于stencil test的比较操作符.*/);
		/*
		vkCmdSetStencilOp有效用法:
		1.extendedDynamicState特性开启，shaderObject特性开启以及创建该commandBuffer所在的VkInstance的VkApplicationInfo::apiVersion大于等于Version 1.3 这三个条件中至少需要满足一个
		
		*/


		//假设这个结构体设置为VkPipelineDepthStencilStateCreateInfo::back
		VkStencilOpState back{};
		{
			back.failOp = VK_STENCIL_OP_INVERT;//是一个VkStencilOp值指明采样点在stencil test失败后的操作
			back.passOp = VK_STENCIL_OP_ZERO;//是一个VkStencilOp 值指明采样点在同时通过depth以及 stencil test后的操作
			back.depthFailOp = VK_STENCIL_OP_KEEP;//一个VkStencilOp  值指明采样点通过stencil test但没有通过depth test的操作
			back.compareOp = VK_COMPARE_OP_LESS;//compareOp,是一个 VkCompareOp 值指明用于stencil test的比较操作符.
			back.compareMask = 0;//选择unsigned integer stencil值哪个比特参与stencil test.
			back.writeMask = 0;// 选择stencil test更新stencil attachment中 unsigned integer stencil值的哪个比特
			back.reference = 0;//是一个integer stencil reference值用于 unsigned stencil comparison
		}


		//动态设置 stencil compare mask     ， 只有在后续绘制使用shader object或者绑定的graphics pipeline以VK_DYNAMIC_STATE_STENCIL_COMPARE_MASK创建才能使用，否则会只用选择的back 或者 front stencil state 的 VkStencilOpState::compareMask设置的
		vkCmdSetStencilCompareMask(commandBuffer, stencilFaceFlagBits/*faceMask,是VkStencilFaceFlagBits 组合值位掩码指明更新哪组stencil state.*/, 0x00000001/*compareMask,是更新的stencil compare mask新值*/);


		//动态设置 stencil write mask     ， 只有在后续绘制使用shader object或者绑定的graphics pipeline以 VK_DYNAMIC_STATE_STENCIL_WRITE_MASK创建才能使用，否则会只用选择的back 或者 front stencil state 的 VkStencilOpState::writeMask设置的
		vkCmdSetStencilWriteMask(commandBuffer, stencilFaceFlagBits/*faceMask,是VkStencilFaceFlagBits 组合值位掩码指明更新哪组stencil state.*/, 0x00000001/*writeMask,是更新的stencil write mask新值*/);

		//动态设置 stencil reference值     ， 只有在后续绘制使用shader object或者绑定的graphics pipeline以 VK_DYNAMIC_STATE_STENCIL_REFERENCE创建才能使用，否则会只用选择的back 或者 front stencil state 的 VkStencilOpState::reference设置的
		vkCmdSetStencilReference(commandBuffer, stencilFaceFlagBits/*faceMask,是VkStencilFaceFlagBits 组合值位掩码指明更新哪组stencil state.*/, 1/*reference,是更新的 stencil reference新值*/);


		//VkStencilOpState(对应 back 或者 front stencil state)的 failOp, passOp, 以及 depthFailOp 可能的值 ，对应对stencil test后对 stencil attachment中该采样点stencil值的操作
		VkStencilOp stencilOp = VK_STENCIL_OP_DECREMENT_AND_CLAMP;
		/*
		VkStencilOp:
		VK_STENCIL_OP_KEEP:  保持当前值.
		VK_STENCIL_OP_ZERO:  设置为0.
		VK_STENCIL_OP_REPLACE:  设置值为reference值
		VK_STENCIL_OP_INCREMENT_AND_CLAMP: 递增当前的值且限制到最大可表示的无符号值
		VK_STENCIL_OP_DECREMENT_AND_CLAMP: 递减当前的值且限制到0
		VK_STENCIL_OP_INVERT:  将当前值的每个bit为翻转.
		VK_STENCIL_OP_INCREMENT_AND_WRAP: 递增当前的值且超出最大的值时设为0
		VK_STENCIL_OP_DECREMENT_AND_WRAP:  递减当前的值且当低于0时设置为最大的值
		
		*/

	}


	//Depth Test   参见p2799
	{
		/*
		depth test将比较每个采样点的在 depth attachment 中的值以及采样点的在framebuffer中的深度值，如果没有深度附件该操作会跳过

		depth test操作分为三部分:
				Depth Clamping and Range Adjustment
				Depth Comparison
				Depth Attachment Writes
		*/
		
		//Depth Clamping and Range Adjustment  见p2800
		{
			/*
			如果 VkPipelineRasterizationStateCreateInfo::depthClampEnable 开启，则采样点的深度值会被限制到[min( minDepth,maxDepth),max( minDepth,maxDepth)],其中minDepth和maxDepth为当前viewport的设置的 
			
			如果VkPhysicalDeviceDepthClampZeroOneFeaturesEXT::depthClampZeroOne开启，则如果depth attachment为浮点格式且 VK_EXT_depth_range_unrestricted开启，则深度值不变，否则限定到[0,1]
			如果VkPhysicalDeviceDepthClampZeroOneFeaturesEXT::depthClampZeroOne未开启，如果深度值不在[min( minDepth,maxDepth),max( minDepth,maxDepth)]范围内则会变为未定义，如果depth attachment的格式为定点数，则不在[0，1]内的深度值会变为未定义
			*/


		}


		//Depth Comparison   参见p2800
		{
			/*
			如果depth test未开启，通过vkCmdSetDepthTestEnable 或者 VkPipelineDepthStencilStateCreateInfo::depthTestEnable指定，则该步骤跳过

			比较将根据vkCmdSetDepthCompareOp, 或者 VkPipelineDepthStencilStateCreateInfo::depthCompareOp设置的VkCompareOp值来进行，比较当前采样点的值和其在depth attachment中的值，如果比较结果为失败，则该采样点的coverage mask会被设为0	
			*/
		}


		// Depth Attachment Writes  参见p2800
		{
			/*
			如果开启depth test，且depth test比较结果为true，则该采样点的深度值就会写入到depth attachment中，如果没有depth attachment，则不会写入任何值
			
			*/


			//动态开启depth test   ，等同于vkCmdSetDepthTestEnableEXT，  只有在后续绘制使用shader object或者绑定的graphics pipeline以 VK_DYNAMIC_STATE_DEPTH_TEST_ENABLE创建才能使用，否则会只用VkPipelineDepthStencilStateCreateInfo::depthTestEnable 设置的
			vkCmdSetDepthTestEnable(commandBuffer, VK_TRUE/*depthTestEnable,指明是否开启 depth test */);
			/*
			vkCmdSetDepthTestEnable有效用法:
			1.extendedDynamicState特性开启，shaderObject特性开启以及创建该commandBuffer所在的VkInstance的VkApplicationInfo::apiVersion大于等于Version 1.3 这三个条件中至少需要满足一个
			*/



			//动态设置depth test比较运算符   ，等同于vkCmdSetDepthCompareOpEXT，  只有在后续绘制使用shader object或者绑定的graphics pipeline以 VK_DYNAMIC_STATE_DEPTH_COMPARE_OP创建才能使用，否则会只用 VkPipelineDepthStencilStateCreateInfo::depthCompareOp 设置的
			vkCmdSetDepthCompareOp(commandBuffer, VK_COMPARE_OP_LESS/*depthCompareOp,是一个VkCompareOp 值指明在depth test中使用的比较运算符.*/);
			/*
			vkCmdSetDepthTestEnable有效用法:
			1.extendedDynamicState特性开启，shaderObject特性开启以及创建该commandBuffer所在的VkInstance的VkApplicationInfo::apiVersion大于等于Version 1.3 这三个条件中至少需要满足一个
			*/

			
			//动态开启depth write    ，等同于vkCmdSetDepthWriteEnableEXT，  只有在后续绘制使用shader object或者绑定的graphics pipeline以 VK_DYNAMIC_STATE_DEPTH_WRITE_ENABLE 创建才能使用，否则会只用VkPipelineDepthStencilStateCreateInfo::depthWriteEnable 设置的
			vkCmdSetDepthWriteEnable(commandBuffer, VK_TRUE/*depthWriteEnable,指明是否开启 depth write */);
			/*
			vkCmdSetDepthWriteEnable有效用法:
			1.extendedDynamicState特性开启，shaderObject特性开启以及创建该commandBuffer所在的VkInstance的VkApplicationInfo::apiVersion大于等于Version 1.3 这三个条件中至少需要满足一个
			*/

		}

	}



	//Representative Fragment Test  参见p2805
	{
		/*
		representative fragment test允许实现减少图元的rasterization以及fragment处理的工作量，对于所有传递到prior early fragment tests阶段的图元 实现会选中处理一些具有“代表性”的图元进行处理，或者丢弃所有图元，这是依赖具体实现的
		
		如果激活的fragment shader没有指定 EarlyFragmentTests execution mode,则representative fragment test 不起作用
		*/


		//在VkGraphicsPipelineCreateInfo.pNext中包含VkPipelineRepresentativeFragmentTestStateCreateInfoNV来控制representative fragment test
		VkPipelineRepresentativeFragmentTestStateCreateInfoNV pipelineRepresentativeFragmentTestStateCreateInfoNV{};
		pipelineRepresentativeFragmentTestStateCreateInfoNV.sType = VK_STRUCTURE_TYPE_PIPELINE_REPRESENTATIVE_FRAGMENT_TEST_STATE_CREATE_INFO_NV;
		pipelineRepresentativeFragmentTestStateCreateInfoNV.pNext = nullptr;
		pipelineRepresentativeFragmentTestStateCreateInfoNV.representativeFragmentTestEnable = VK_TRUE;//控制是否开启representative fragment test


		
		//动态设置 representativeFragmentTestEnable state   ，  只有在后续绘制使用shader object或者绑定的graphics pipeline以 VK_DYNAMIC_STATE_REPRESENTATIVE_FRAGMENT_TEST_ENABLE_NV 创建才能使用，否则会只用VkPipelineRepresentativeFragmentTestStateCreateInfoNV::representativeFragmentTestEnable 设置的
		vkCmdSetRepresentativeFragmentTestEnableNV(commandBuffer, VK_TRUE/*representativeFragmentTestEnable,指明是否开启representative fragment test */);
		/*
		vkCmdSetRepresentativeFragmentTestEnableNV有效用法:
		1. extendedDynamicState3RepresentativeFragmentTestEnable或者shaderObject特性开启至少一个开启
		*/

	}


	// Sample Counting 参见p2807    Occlusion queries可以查询所有通过了上述描述的各种per-fragment测试后coverage mask还为1的采样点的数量


	//Fragment Coverage to Color   参见p2807
	{

		/*
		如果VkPipelineMultisampleStateCreateInfo.pNext中包含一个VkPipelineCoverageToColorStateCreateInfoNV，则该结构体控制将fragment coverage mask替换该fragment的颜色值输出
		
		如果该结构体的coverageToColorEnable为VK_TRUE，则 coverage mask会替换fragment shader中Location等于coverageToColorLocation，且Index 为0的颜色输出值的第一个分量，否则会跳过该步骤
		*/
		VkPipelineCoverageToColorStateCreateInfoNV pipelineCoverageToColorStateCreateInfoNV{};
		pipelineCoverageToColorStateCreateInfoNV.sType = VK_STRUCTURE_TYPE_PIPELINE_COVERAGE_TO_COLOR_STATE_CREATE_INFO_NV;
		pipelineCoverageToColorStateCreateInfoNV.pNext = nullptr;
		pipelineCoverageToColorStateCreateInfoNV.flags = 0;
		pipelineCoverageToColorStateCreateInfoNV.coverageToColorEnable = VK_TRUE;
		pipelineCoverageToColorStateCreateInfoNV.coverageToColorLocation = 0;
		/*
		VkPipelineCoverageToColorStateCreateInfoNV有效用法:
		1.如果coverageToColorEnable 为VK_TRUE，则VkGraphicsPipelineCreateInfo::renderPass以及VkGraphicsPipelineCreateInfo::subpass 所指的render pass subpass必须在索引为coverageToColorLocation处含有一个格式为VK_FORMAT_R8_UINT, VK_FORMAT_R8_SINT, VK_FORMAT_R16_UINT,
						VK_FORMAT_R16_SINT, VK_FORMAT_R32_UINT, 或者 VK_FORMAT_R32_SINT的color attachment
		*/


		//动态设置 coverageToColorEnable state   ，  只有在后续绘制使用shader object或者绑定的graphics pipeline以 VK_DYNAMIC_STATE_COVERAGE_TO_COLOR_ENABLE_NV 创建才能使用，否则会只用VkPipelineCoverageToColorStateCreateInfoNV::coverageToColorEnable 设置的
		vkCmdSetCoverageToColorEnableNV(commandBuffer, VK_TRUE/*coverageToColorEnable,指明coverageToColorEnable state*/);
		/*
		vkCmdSetCoverageToColorEnableNV有效用法:
		1.  extendedDynamicState3CoverageToColorEnable或者shaderObject特性开启至少一个开启
		*/


		//动态设置 coverageToColorLocation state  ，  只有在后续绘制使用shader object或者绑定的graphics pipeline以 VK_DYNAMIC_STATE_COVERAGE_TO_COLOR_LOCATION_NV 创建才能使用，否则会只用VkPipelineCoverageToColorStateCreateInfoNV::coverageToColorLocation 设置的
		vkCmdSetCoverageToColorLocationNV(commandBuffer, VK_TRUE/*coverageToColorLocation,指明coverageToColorLocation state*/);
		/*
		vkCmdSetCoverageToColorLocationNV有效用法:
		1.  extendedDynamicState3CoverageToColorLocation或者shaderObject特性开启至少一个开启
		*/

	}



	//Coverage Reduction  参见p2811
	{
		/*
		coverage reduction将获取每个fragment中每个pixel包含的采样点的coverage mask信息，然后转换为一个boolean值
		
		*/


		//Pixel Coverage  参见p2811
		{
			/*
			每个pixel的coverage mask从总的fragment的coverage mask中提取。其包含rasterizationSamples个unique coverage sample
			*/
		}

		//Color Sample Coverage   参见2811
		{
			//一旦确定了Pixel Coverage，那Color Sample Coverage也就确定了，具体的提取计算规则见p2811

			/*
			如果开启了 VK_NV_coverage_reduction_mode  拓展，则coverage reduction由VkPipelineGraphicsPipelineCreateInfo.pNext的 VkPipelineCoverageReductionStateCreateInfoNV中的参数控制
			
			如果不包含该结构体或者VK_NV_coverage_reduction_mode 拓展没开启，则默认情况根据:
				如果 VK_NV_framebuffer_mixed_samples开启，则像是coverageReductionMode默认为VK_COVERAGE_REDUCTION_MODE_MERGE_NV.
				如果 VK_AMD_mixed_attachment_samples开启，则像是coverageReductionMode默认为VK_COVERAGE_REDUCTION_MODE_TRUNCATE_NV.
				如果 VK_NV_framebuffer_mixed_samples 以及VK_AMD_mixed_attachment_samples都开启，则默认coverageReductionMode依赖实现 
			*/
			
			VkPipelineCoverageReductionStateCreateInfoNV pipelineCoverageReductionStateCreateInfoNV{};
			pipelineCoverageReductionStateCreateInfoNV.sType = VK_STRUCTURE_TYPE_PIPELINE_COVERAGE_REDUCTION_STATE_CREATE_INFO_NV;
			pipelineCoverageReductionStateCreateInfoNV.pNext = nullptr;
			pipelineCoverageReductionStateCreateInfoNV.flags = 0;//保留未来使用
			pipelineCoverageReductionStateCreateInfoNV.coverageReductionMode = VK_COVERAGE_REDUCTION_MODE_MERGE_NV;/*一个 VkCoverageReductionModeNV 值指明color sample coverage如何从pixel coverage中产生
			VkCoverageReductionModeNV:
			VK_COVERAGE_REDUCTION_MODE_MERGE_NV:  指明每个color sample将根据实现关联到pixel coverage的samples的一个sample子集中，如果该子集中任何的sample被包含，则该color sample就被包含
			VK_COVERAGE_REDUCTION_MODE_TRUNCATE_NV:  指明对于在color attachment中呈现的color samples，如果pixel coverage 中相同sample index的sample被包含，则该color sample就被包含，其余未被包含的就会被丢弃
			*/


			//动态设置  coverageReductionMode state  ，  只有在后续绘制使用shader object或者绑定的graphics pipeline以 VK_DYNAMIC_STATE_COVERAGE_REDUCTION_MODE_NV 创建才能使用，否则会只用VkPipelineCoverageReductionStateCreateInfoNV::coverageReductionMode 设置的
			vkCmdSetCoverageReductionModeNV(commandBuffer, VK_COVERAGE_REDUCTION_MODE_MERGE_NV/*coverageReductionMode,指明 coverageReductionMode state*/);
			/*
			vkCmdSetCoverageReductionModeNV有效用法:
			1.  extendedDynamicState3CoverageReductionMode 或者shaderObject特性开启至少一个开启
			*/




		}

	}

}


NS_TEST_END