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
					1/*vertexAttributeDescriptionCount，为pVertexAttributeDescriptions元素个数.*/, &vertexInputAttributeDescription2EXT/*• pVertexAttributeDescriptions，一组 VkVertexInputAttributeDescription2EXT 数组指针，指明属性信息.*/);
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
	}

}


NS_TEST_END