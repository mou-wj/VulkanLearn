#include "ShadersInterfaceTest.h"
NS_TEST_BEGIN

/*
概述:
当pipeline创建了后，其指定的shaders将会隐式链接到一系列的接口:
>  Shader Input and Output Interface
>  Vertex Input Interface
>  Fragment Output Interface
>  Fragment Tile Image Interface
>  Fragment Input Attachment Interface
>  Ray Tracing Pipeline Interface
>  Shader Resource Interface
>  Geometry Shader Passthrough


*/


ShadersInterfaceTest::ShadersInterfaceTest()
{
}

void ShadersInterfaceTest::run()
{
}

ShadersInterfaceTest::~ShadersInterfaceTest()
{
}

void ShadersInterfaceTest::InterfaceTest()
{
	// Shader Input and Output Interfaces
	{
		//这种interface由一个shader，一个匹配到下一个shader 输入的输出以及一个匹配上一个shader stage的输出的输入构成
		//这种interface的变量作为OpEntryPoint 指令操作符列举出来，以 Input 或者 Output storage classes进行声明,这样的接口只存在于两个连续的shader stage之间
		//这种interface的变量分配built-in 变量以及 user-defined变量


		//Built-in Interface Block   参见p1395

		//User-defined Variable Interface   参见p1395

		// Interface Matching 参见p1396

		//Location Assignment 参见p1396
		{
		/*
		每个shader interface可用的location数量限制
		Shader Input and Output Locations

		Shader Interface                |        Locations Available
		vertex input					|	 maxVertexInputAttributes
		vertex output					|	 maxVertexOutputComponents / 4
		tessellation control input		|	 maxTessellationControlPerVertexInputComponents / 4
		tessellation control output		|	 maxTessellationControlPerVertexOutputComponents / 4
		tessellation evaluation input   |     maxTessellationEvaluationInputComponents / 4
		tessellation evaluation output  |     maxTessellationEvaluationOutputComponents / 4
		geometry input					|	 maxGeometryInputComponents / 4
		geometry output					|	 maxGeometryOutputComponents / 4
		fragment input					|	 maxFragmentInputComponents / 4
		fragment output                 |     maxFragmentOutputAttachments
		mesh output                     |     maxMeshOutputComponents / 4
		cluster culling output          |     maxOutputClusterCount
		*/
		}

		//Component Assignment 参见p1398




	}


	//Vertex Input Interface 参见p1398
	{
		// 含有vertex input attributes的接口，该接口中通过Location以及Component声明的变量将和  VkGraphicsPipelineCreateInfo.pVertexInputState中的信息相匹配
	}

	//Fragment Output Interface
	{
		//fragment shader的输出将构成在render pass中定义的color attachment的接口，通过Location 以及 Component，Index匹配，Location[i]对应VkRenderingInfo::pColorAttachments[i].
	
		//如果 dynamicRenderingLocalRead 特性开启，Location到VkRenderingInfo::pColorAttachments的映射可以动态指定

		VkRenderingAttachmentLocationInfoKHR renderingAttachmentLocationInfoKHR{};//可以包含在VkGraphicsPipelineCreateInfo来指定映射信息,也可以包含在 VkCommandBufferInheritanceInfo中来继承primary command buffer的state
		renderingAttachmentLocationInfoKHR.sType = VK_STRUCTURE_TYPE_MAX_ENUM;//没有定义所以定义为非法值
		renderingAttachmentLocationInfoKHR.pNext = nullptr;
		renderingAttachmentLocationInfoKHR.colorAttachmentCount = 1;//pColorAttachmentLocations中元素个数
		uint32_t colorAttachmentLocation = 2;
		renderingAttachmentLocationInfoKHR.pColorAttachmentLocations = &colorAttachmentLocation;//是colorAttachmentCount个uint32_t 值的数组指针，指明color attachment的重新映射的Location，如果为NULL，则等价于其中的值为[0,...colorAttachmentCount-1]
		/*
		VkRenderingAttachmentLocationInfoKHR有效用法:
		1.如果dynamicRenderingLocalRead 特性没有开启，且pColorAttachmentLocations不为NULL，则pColorAttachmentLocations中的值必须是为[0,...colorAttachmentCount-1]
		2.pColorAttachmentLocations中对应到不是VK_ATTACHMENT_UNUSED的附件的元素的附件索引值必须是唯一的
		3.colorAttachmentCount 必须小于等于maxColorAttachments
		4.pColorAttachmentLocations中的元素值必须小于maxColorAttachments
		*/


		//动态设置Location到VkRenderingInfo::pColorAttachments的映射
		vkCmdSetRenderingAttachmentLocationsKHR(VkCommandBuffer{/*假设这是一个有效的VkCommandBuffer*/ }, &renderingAttachmentLocationInfoKHR);
		/*
		vkCmdSetRenderingAttachmentLocationsKHR有效用法:
		1.dynamicRenderingLocalRead 特性必须开启
		2.pLocationInfo->colorAttachmentCount 必须等于开始当前render pass实例的VkRenderingInfo::colorAttachmentCount
		3.当前的render pass实例必须已经通过该commandBuffer的vkCmdBeginRendering调用开始或者使用了

		*/


		//这个接口中的以Component0，1，2，3声明的输出对应到color blend单元输入的R，G，B，A分量    以Index 0，1声明的输出对应到color blend单元的第一个第二个输入

	}

	// Legacy Dithering 参见p1403


	// Fragment Tile Image Interface 参见p1403
	{
		//该接口定义在fragment shader 中，读取 VkRenderingInfoKHR::pColorAttachments，只是由Location，TileImageEXT定义构成接口，不再使用Component
	}

	// Fragment Input Attachment Interface 参见p1403
	{
		//该接口定义在fragment shader 中，读取render pass中的VkRenderingInfoKHR::pInputAttachments,由InputAttachmentIndex以及 UniformConstant定义构成接口，可用的输入附件索引见VkPhysicalDeviceLimits::maxPerStageDescriptorInputAttachments


		VkRenderingInputAttachmentIndexInfoKHR renderingInputAttachmentIndexInfoKHR{};//可以包含在VkGraphicsPipelineCreateInfo来指定映射信息,也可以包含在 VkCommandBufferInheritanceInfo中来继承primary command buffer的state
		renderingInputAttachmentIndexInfoKHR.sType = VK_STRUCTURE_TYPE_MAX_ENUM;
		renderingInputAttachmentIndexInfoKHR.pNext = nullptr;
		uint32_t colorAttachmentIndex = 2,depthAttachmentIndex = 3,stencilAttachmentIndex = 3;
		renderingInputAttachmentIndexInfoKHR.colorAttachmentCount = 1;//pColorAttachmentInputIndices 中的元素个数
		renderingInputAttachmentIndexInfoKHR.pColorAttachmentInputIndices = &colorAttachmentIndex;//是colorAttachmentCount个uint32_t 值的数组指针，指明用作input attachment的color attachment的重新映射的InputAttachmentIndex，如果为NULL，则等价于其中的值为[0,...colorAttachmentCount-1],如果其中的值为 VK_ATTACHMENT_UNUSED,表明该color attachment不做为input attachment使用
		renderingInputAttachmentIndexInfoKHR.pDepthInputAttachmentIndex = &depthAttachmentIndex;//是NULL或者1个uint32_t 值的数组指针，指明用作input attachment的depth attachment的重新映射的InputAttachmentIndex ,如果设置为NULL，表明映射到不以  InputAttachmentIndex声明的input attachment,如果其值对应一个VK_ATTACHMENT_UNUSED，表明该depth attachment不做为input attachment使用
		renderingInputAttachmentIndexInfoKHR.pStencilInputAttachmentIndex = &stencilAttachmentIndex;//是NULL或者1个uint32_t 值的数组指针，指明用作input attachment的stencil attachment的重新映射的InputAttachmentIndex ,如果设置为NULL，表明映射到不以  InputAttachmentIndex声明的input attachment,如果其值对应一个VK_ATTACHMENT_UNUSED，表明该depth attachment不做为input attachment使用 
		/*
		VkRenderingInputAttachmentIndexInfoKHR有效用法:
		1.如果dynamicRenderingLocalRead 特性没有开启，则（1）如果pColorAttachmentInputIndices不为NULL，则其中每个元素不能设置为VK_ATTACHMENT_UNUSED
													    （2）pDepthInputAttachmentIndex，pStencilInputAttachmentIndex必须为一个值为VK_ATTACHMENT_UNUSED 的地址
		2.pColorAttachmentInputIndices中值不为VK_ATTACHMENT_UNUSED的元素其值必须是唯一的，且不能和pDepthInputAttachmentIndex以及pStencilInputAttachmentIndex所指的值相同
		3.colorAttachmentCount 必须小于等于maxColorAttachments
		*/
		
		
		//如果 dynamicRenderingLocalRead 特性开启，InputAttachmentIndex到VkRenderingInfo::pInputAttachments的映射可以动态指定
		vkCmdSetRenderingInputAttachmentIndicesKHR(VkCommandBuffer{/*假设这是一个有效的VkCommandBuffer*/ }, & renderingInputAttachmentIndexInfoKHR);
		/*
		vkCmdSetRenderingInputAttachmentIndicesKHR有效用法:
		1.dynamicRenderingLocalRead 必须开启
		2.pInputAttachmentIndexInfo->colorAttachmentCount 必须等于开始当前render pass实例的VkRenderingInfo::colorAttachmentCount
		3.当前的render pass实例必须已经通过该commandBuffer的vkCmdBeginRendering调用开始或者使用了

		*/

	}


	//Ray Tracing Pipeline Interface 参见p1408


	//Shader Resource Interface 参见p1409
	{
		//在shader中访问 buffer 或者 image resources时,在shader中可以访问的以Uniform, UniformConstant,StorageBuffer, 或者 PushConstant声明的shader 变量组成shader resource interface，该interface可再分为 push constant interface 以及 descriptor set interface.对于fragment shader，包含fragment input attachment interface
	
		// Push Constant Interface 以PushConstant声明 参见p1409
	
		//Descriptor Set Interface
		{
			//以StorageBuffer, Uniform 或者 UniformConstant声明，以 DescriptorSet 以及 Binding修饰（对应VkDescriptorSetLayout中的内容） 参见p1410，对于fragment shader，包含fragment input attachment interface
			//这些变量的使用限制见p1410 - p1414
		}

		// DescriptorSet and Binding Assignment  
		{
			//以DescriptorSet 和 Binding 描述的变量对应一个 VkDescriptorSetLayoutBinding，详情参见p1414- p1416
			/*
				 Shader Resource Limits表格见p1416
			*/

		}


		// Offset and Stride Assignment 参见p1416
		{
			// 以Offset, ArrayStride, 以及 MatrixStride 进行描述

		}
	}


}

void ShadersInterfaceTest::BuildInVariableTest()
{
	//Built-In Variables p1419
	//在shader中访问的以 BuiltIn 声明的变量

	//xxx
	/*
	概述:

	xxxY有效用法:

	
	*/

	//BaryCoordKHR
	/*
	概述:
	BaryCoordKHR 用于修饰 fragment shader input variable，为三分量浮点带权重的变量指明相对于屏幕空间中其图元顶点位置的重心坐标，使用透视插值得到

	BaryCoordKHR有效用法:
	1.BaryCoordKHR 必须在 Fragment Execution Model 中使用
	2.BaryCoordKHR修饰的变量必须以Input Storage Class 声明
	3.BaryCoordKHR修饰的变量 必须以三分量32-bit浮点类型声明
	*/


	//BaryCoordNoPerspAMD
	/*
	概述:

	BaryCoordNoPerspAMD 用于修饰 fragment shader input variable，该变量包含基于片段中心利用线性插值的到的重心坐标中的（I,J）对，其中K分量通过I + J + K = 1得到

	BaryCoordNoPerspAMD有效用法:
	1.BaryCoordNoPerspAMD 必须在 Fragment Execution Model 中使用
	2.BaryCoordNoPerspAMD修饰的变量必须以Input Storage Class 声明
	3.BaryCoordNoPerspAMD修饰的变量 必须以二分量32-bit浮点类型声明
	*/
	
	//BaryCoordNoPerspKHR
	/*
	概述:
	BaryCoordNoPerspKHR 用于修饰 fragment shader input variable，为三分量浮点带权重的变量指明相对于屏幕空间中其图元顶点位置的重心坐标，使用线性插值得到
	
	BaryCoordNoPerspKHR有效用法:
	1.BaryCoordNoPerspKHR 必须在 Fragment Execution Model 中使用
	2.BaryCoordNoPerspKHR修饰的变量必须以Input Storage Class 声明
	3.BaryCoordNoPerspKHR修饰的变量 必须以三分量32-bit浮点类型声明
	*/


	//BaryCoordNoPerspCentroidAMD
	/*
	概述:
	
	BaryCoordNoPerspCentroidAMD 用于修饰 fragment shader input variable，该变量包含基于质心利用线性插值的到的重心坐标中的（I,J）对，其中K分量通过I + J + K = 1得到
	
	BaryCoordNoPerspCentroidAMD有效用法:
	1.BaryCoordNoPerspCentroidAMD 必须在 Fragment Execution Model 中使用
	2.BaryCoordNoPerspCentroidAMD修饰的变量必须以Input Storage Class 声明
	3.BaryCoordNoPerspCentroidAMD修饰的变量 必须以三分量32-bit浮点类型声明
	*/


	//BaryCoordNoPerspSampleAMD
	/*
	概述:
	
	BaryCoordNoPerspSampleAMD 用于修饰 fragment shader input variable，该变量包含基于每个包含的采样点利用线性插值的到的重心坐标中的（I,J）对，其中K分量通过I + J + K = 1得到
	
	BaryCoordNoPerspSampleAMD有效用法:
	1.BaryCoordNoPerspSampleAMD 必须在 Fragment Execution Model 中使用
	2.BaryCoordNoPerspSampleAMD修饰的变量必须以Input Storage Class 声明
	3.BaryCoordNoPerspSampleAMD修饰的变量 必须以二分量32-bit浮点类型声明
	*/


	//BaryCoordPullModelAMD
	/*
	概述:
	
	BaryCoordPullModelAMD 用于修饰 fragment shader input variable，该变量包含基于片段中心计算所得的 (1/W, 1/I, 1/J)，可以用于计算梯度以及插值任何采样点的I,J,K值
	
	BaryCoordPullModelAMD有效用法:
	1.BaryCoordPullModelAMD 必须在 Fragment Execution Model 中使用
	2.BaryCoordPullModelAMD修饰的变量必须以Input Storage Class 声明
	3.BaryCoordPullModelAMD修饰的变量 必须以三分量32-bit浮点类型声明
	*/


	//BaryCoordSmoothAMD
	/*
	概述:
	
	BaryCoordSmoothAMD 用于修饰 fragment shader input variable，该变量包含基于片段中心使用透视插值计算所得的（I,J）重心坐标，其中K分量通过I + J + K = 1得到
	
	BaryCoordSmoothAMD有效用法:
	1.BaryCoordSmoothAMD 必须在 Fragment Execution Model 中使用
	2.BaryCoordSmoothAMD修饰的变量必须以Input Storage Class 声明
	3.BaryCoordSmoothAMD修饰的变量 必须以二分量32-bit浮点类型声明
	*/


	//BaryCoordSmoothCentroidAMD
	/*
	概述:
	
	BaryCoordSmoothCentroidAMD 用于修饰 fragment shader input variable，该变量包含基于质心使用透视插值计算所得的（I,J）重心坐标，其中K分量通过I + J + K = 1得到
	
	BaryCoordSmoothCentroidAMD有效用法:
	1.BaryCoordSmoothCentroidAMD 必须在 Fragment Execution Model 中使用
	2.BaryCoordSmoothCentroidAMD修饰的变量必须以Input Storage Class 声明
	3.BaryCoordSmoothCentroidAMD修饰的变量 必须以二分量32-bit浮点类型声明
	*/

	
	//BaryCoordSmoothSampleAMD
	/*
	概述:
	
	BaryCoordSmoothSampleAMD 用于修饰 fragment shader input variable，该变量包含基于包含的每个采样点使用透视插值计算所得的（I,J）重心坐标，其中K分量通过I + J + K = 1得到
	
	BaryCoordSmoothSampleAMD有效用法:
	1.BaryCoordSmoothSampleAMD 必须在 Fragment Execution Model 中使用
	2.BaryCoordSmoothSampleAMD修饰的变量必须以Input Storage Class 声明
	3.BaryCoordSmoothSampleAMD修饰的变量 必须以二分量32-bit浮点类型声明
	*/


	//BaseInstance
	/*
	概述:
	
	BaseInstance 修饰的变量包含一个 传递给触发当前顶点着色器调用的命令的first instance参数的整数索引，为绘制命令的firstInstance参数
	
	BaseInstance有效用法:
	1.BaseInstance 必须在 Vertex Execution Model 中使用
	2.BaseInstance修饰的变量必须以Input Storage Class 声明
	3.BaseInstance修饰的变量 必须以标量32-bit整型类型声明
	*/
	

	//BaseVertex
	/*
	概述:
	
	BaseVertex 修饰的变量包含一个 传递给触发当前顶点着色器调用的命令的first vertex或者vertex offset参数的整数索引，对于非索引绘制命令，为参数为firstVertex，在索引绘制命令中为参数为vertexOffset
	
	BaseVertex有效用法:
	1.BaseVertex 必须在 Vertex Execution Model 中使用
	2.BaseVertex修饰的变量必须以Input Storage Class 声明
	3.BaseVertex修饰的变量 必须以标量32-bit整型类型声明
	*/

	
	//ClipDistance
	/*
	概述:
	
	ClipDistance 修饰的变量指明用户控制裁剪，其中ClipDistance 中第i个元素对应第i个剪裁平面的裁剪距离，一个裁剪距离为0表示该点在裁剪平面上，大于0表示在裁剪平面内，小于0表示在裁剪平面外
	
	ClipDistance有效用法:
	1.ClipDistance 必须在 MeshEXT, MeshNV, Vertex,Fragment, TessellationControl, TessellationEvaluation, 或者 Geometry Execution Model 中使用
	2.ClipDistance修饰的变量在MeshEXT, MeshNV, 或者 Vertex Execution Model中 以Output Storage Class 声明
	3.ClipDistance修饰的变量在Fragment Execution Model中 以Input Storage Class 声明
	4.ClipDistance修饰的变量在TessellationControl，TessellationEvaluation, 或者 Geometry  Execution Model中不能以Input 或者Output Storage Class 声明
	5.ClipDistance修饰的变量 必须以32-bit浮点类型的数组声明
	*/

	
	//ClipDistancePerViewNV
	/*
	概述:

	ClipDistancePerViewNV 修饰的变量指明用户控制per-view的裁剪，类比于ClipDistance

	ClipDistancePerViewNV有效用法:
	1.ClipDistancePerViewNV 必须在 MeshNV Execution Model 中使用
	2.ClipDistance修饰的变量以Output Storage Class 声明
	3.ClipDistance修饰的变量必须也以PerViewNV 修饰
	4.ClipDistance修饰的变量 必须以二维32-bit浮点类型的数组声明
	*/


	//ClusterIDHUAWEI
	/*
	概述:
	
	ClusterIDHUAWEI 修饰用于修饰一个cluster culling shader output variable，该变量包含当前绘制的cluster的ID整数值，如果启用Cluster Culling Shader，则获取cluster-related 信息时 ClusterIDHUAWEI将替换gl_DrawID
	
	ClusterIDHUAWEI有效用法:
	1.ClusterIDHUAWEI 必须在 ClusterCullingHUAWEI Execution Model 中使用
	2.ClusterIDHUAWEI修饰的变量 必须以32-bit整型类型声明
	*/

	
	//ClusterShadingRateHUAWEI
	/*
	概述:
	
	ClusterShadingRateHUAWEI 修饰用于修饰一个cluster culling shader output variable，该变量包含当前绘制的cluster的 shading rate
	
	ClusterShadingRateHUAWEI有效用法:
	1.ClusterShadingRateHUAWEI 必须在 ClusterCullingHUAWEI Execution Model 中使用
	2.ClusterShadingRateHUAWEI修饰的变量 必须以32-bit整型类型声明
	*/


	//CullDistance
	/*
	概述:
	
	CullDistance 修饰的变量指明用户控制剔除，如果图元所有顶点的CullDistance都小于0，则表明这个图元会在光栅化前被剔除
	
	CullDistance有效用法:
	1.CullDistance 必须在 MeshEXT, MeshNV, Vertex,Fragment, TessellationControl, TessellationEvaluation, 或者 Geometry Execution Model 中使用
	2.CullDistance修饰的变量在MeshEXT, MeshNV, 或者 Vertex Execution Model中 以Output Storage Class 声明
	3.CullDistance修饰的变量在Fragment Execution Model中 以Input Storage Class 声明
	4.CullDistance修饰的变量在TessellationControl，TessellationEvaluation, 或者 Geometry  Execution Model中不能以Input 或者Output Storage Class 声明
	5.CullDistance修饰的变量 必须以32-bit浮点类型的数组声明
	*/

	
	//CullDistancePerViewNV
	/*
	概述:
	
	CullDistancePerViewNV 修饰的变量指明用户控制per-view的剔除，类比于CullDistance
	
	CullDistancePerViewNV有效用法:
	1.CullDistancePerViewNV 必须在 MeshNV Execution Model 中使用
	2.CullDistancePerViewNV修饰的变量以Output Storage Class 声明
	3.CullDistancePerViewNV修饰的变量必须也以PerViewNV 修饰
	4.CullDistancePerViewNV修饰的变量 必须以二维32-bit浮点类型的数组声明
	*/


	//CullPrimitiveEXT
	/*
	概述:
	
	CullPrimitiveEXT 修饰的变量包含图元的剔除状态，如果per-primitive 的boolean为true，则表明图元不被剔除，否则图元被剔除
	
	CullPrimitiveEXT有效用法:
	1.CullPrimitiveEXT 必须在  MeshEXT Execution Model 中使用
	2.CullPrimitiveEXT修饰的变量以Output Storage Class 声明
	3.CullPrimitiveEXT修饰的变量必须修饰为boolean值的数组
	4.CullPrimitiveEXT修饰的数组大小必须和OutputPrimitivesEXT 的值匹配
	5.CullPrimitiveEXT修饰的变量 必须也以 PerPrimitiveEXT 修饰
	*/

	//CullMaskKHR
	/*
	概述:
	
	CullMaskKHR 修饰的变量指明处理ray时候的cull mask
	
	CullMaskKHR有效用法:
	1.CullMaskKHR 必须在  IntersectionKHR, AnyHitKHR,ClosestHitKHR, 或者 MissKHR Execution Model 中使用
	2.CullMaskKHR修饰的变量以Input Storage Class 声明
	3.CullMaskKHR修饰的变量必须修饰为32-bit整数值

	*/

	
	//CurrentRayTimeNV
	/*
	概述:
	
	CurrentRayTimeNV 修饰的变量包含传递给调用当前shader的OpTraceRayMotionNV 的时间值
	
	CurrentRayTimeNV有效用法:
	1.CurrentRayTimeNV 必须在  IntersectionKHR, AnyHitKHR,ClosestHitKHR, 或者 MissKHR Execution Model 中使用
	2.CurrentRayTimeNV修饰的变量以Input Storage Class 声明
	3.CurrentRayTimeNV修饰的变量必须修饰为32-bit浮点值
	*/


	//DeviceIndex
	/*
	概述:
	
	DeviceIndex 会用来填充当前shader调用用组shader input的physical device的设备索引，范围为[0,max(1,physicalDeviceCount)],physicalDeviceCount为 VkDeviceGroupDeviceCreateInfo:: physicalDeviceCount
	
	DeviceIndex有效用法:
	1.DeviceIndex修饰的变量以Input Storage Class 声明
	2.DeviceIndex修饰的变量必须修饰为32-bit整数值
	*/

	//DrawIndex
	/*
	概述:

	DrawIndex 包含指明调用当前task, mesh, 或者 vertex shader的draw call的索引，见p1428

	DrawIndex有效用法:
	1.DrawIndex 必须在 Vertex, MeshEXT, TaskEXT, MeshNV 或者 TaskNV Execution Model 中使用
	1.DrawIndex修饰的变量以Input Storage Class 声明
	2.DrawIndex修饰的变量必须修饰为32-bit整数值
	*/

	//FirstIndexHUAWEI
	/*
	概述:

	FirstIndexHUAWEI 用来修饰cluster culling shader output variable，这个变量包含一个cluster的索引数组中的一个base 索引

	FirstIndexHUAWEI有效用法:
	1.FirstIndexHUAWEI 必须在 ClusterCullingHUAWEI Execution Model 中使用
	2.FirstIndexHUAWEI修饰的变量必须修饰为32-bit整数值
	*/
	
	//FragCoord
	/*
	概述:
	
	FragCoord 包含处理后的片段的 framebuffer坐标（x,y,z,1/w）,(0,0)位于 framebuffer左上角，(1,1)位于 framebuffer右下角，如果开启了采样，则x，y为采样点的坐标，否则为片段中心的坐标，z坐标通过插值获取，w重新计算为1/w
	
	FragCoord有效用法:
	1.FragCoord 必须在  Fragment Execution Model 中使用
	2.FragCoord 修饰的变量必须以Input Storage Class 声明
	3.FragCoord修饰的变量必须修饰为四分量 32-bit浮点vec值
	*/


	//FragDepth
	/*
	概述:
	
	FragDepth 用于后续深度测试以及写入到depth attachment
	
	FragDepth有效用法:
	1.FragDepth 必须在  Fragment Execution Model 中使用
	2.FragDepth 修饰的变量必须以Output Storage Class 声明
	3.FragDepth修饰的变量必须修饰为标量 32-bit浮点值
	4.如果着色器动态写入FragDepth修饰的变量，则必须也要声明DepthReplacing Execution Mode
	*/

	//FirstInstanceHUAWEI
	/*
	概述:
	
	FirstInstanceHUAWEI 用于描述cluster culling shader output variable，修饰的变量包含一个指向绘制的第一个instance的instance的索引值
	
	FirstInstanceHUAWEI有效用法:
	1.FirstInstanceHUAWEI 必须在  ClusterCullingHUAWEI Execution Model 中使用
	2.FirstInstanceHUAWEI 修饰的变量必须修饰为标量 32-bit整型值

	*/
	

	//FirstVertexHUAWEI
	/*
	概述:

	FirstVertexHUAWEI 用于描述cluster culling shader output variable，在非索引绘制模式中，该修饰的变量包含一个指向cluster绘制的第一个vertex的vertex的索引值

	FirstVertexHUAWEI有效用法:
	1.FirstVertexHUAWEI 必须在  FirstVertexHUAWEI Execution Model 中使用
	2.FirstVertexHUAWEI 修饰的变量必须修饰为标量 32-bit整型值
	*/

	
	//FragInvocationCountEXT
	/*
	概述:
	
	FragInvocationCountEXT 修饰的变量包含fragment shader invocation的最大数量，如果Sample Shading没有启用，则默认为1
	
	FragInvocationCountEXT有效用法:
	1.FragInvocationCountEXT 必须在  Fragment Execution Model 中使用
	2.FragInvocationCountEXT 修饰的变量必须以Input Storage Class 声明
	3.FragInvocationCountEXT 修饰的变量必须修饰为标量 32-bit整型值
	*/


	//FragSizeEXT
	/*
	概述:
	
	FragSizeEXT 修饰的变量包含片段包含的区域的像素维度，如果fragment density map 没有开启则默认为（1，1）
	
	FragSizeEXT有效用法:
	1.FragSizeEXT 必须在  Fragment Execution Model 中使用
	2.FragSizeEXT 修饰的变量必须以Input Storage Class 声明
	3.FragSizeEXT 修饰的变量必须修饰为二分量 32-bit整型vec值
	*/

	//FragStencilRefEXT
	/*
	概述:
	
	FragStencilRefEXT 修饰的变量包含片段包含的所有采样点所引用的stencil值，这个值用于stencil测试，如果要写入FragStencilRefEXT，则shader还需要声明  StencilRefReplacingEXT，
	
	FragStencilRefEXT有效用法:
	1.FragStencilRefEXT 必须在  Fragment Execution Model 中使用
	2.FragStencilRefEXT 修饰的变量必须以Output Storage Class 声明
	3.FragStencilRefEXT 修饰的变量必须修饰为标量整型值
	*/



	//FragmentSizeNV
	/*
	概述:

	FragmentSizeNV 修饰的变量包含片段的width以及height

	FragmentSizeNV有效用法:
	1.FragmentSizeNV 必须在  Fragment Execution Model 中使用
	2.FragmentSizeNV 修饰的变量必须以Output Storage Class 声明
	3.FragmentSizeNV 修饰的变量必须修饰为二分量 32-bit整型vec值
	*/

	
	//FrontFacing
	/*
	概述:

	FrontFacing 修饰的变量表明片段是否是处于正面或者背面，如果大于0则为正面，否则为背面

	FrontFacing有效用法:
	1.FrontFacing 必须在  Fragment Execution Model 中使用
	2.FrontFacing 修饰的变量必须以Input Storage Class 声明
	3.FrontFacing 修饰的变量必须修饰为boolean值
	*/

	//FullyCoveredEXT
	/*
	概述:
	
	FullyCoveredEXT 修饰的变量表明生成的图元是否完全包含片段区域，如果开启conservative rasterization 下完全包含则该值大于0，否则在没有开启conservative rasterization或者不完全包含下为0
	
	FullyCoveredEXT有效用法:
	1.FullyCoveredEXT 必须在  Fragment Execution Model 中使用
	2.FullyCoveredEXT 修饰的变量必须以Input Storage Class 声明
	3.FullyCoveredEXT 修饰的变量必须修饰为boolean值
	4.当声明了一个FullyCoveredEXT 修饰的变量， 如果VkPhysicalDeviceConservativeRasterizationPropertiesEXT::conservativeRasterizationPostDepthCoverage 不支持，则PostDepthCoverage Execution Mode 不能声明
	*/

	
	//GlobalInvocationId
	/*
	概述:
	
	GlobalInvocationId 修饰的变量包含global workgroup中当前调用的位置，每个分量的值为 当前local workgroup中的索引加上 LocalInvocationId 乘以 local workgroup 的大小
	
	GlobalInvocationId有效用法:
	1.GlobalInvocationId 必须在   GLCompute, MeshEXT, TaskEXT, MeshNV, 或者 TaskNV  Execution Model 中使用
	2.GlobalInvocationId 修饰的变量必须以Input Storage Class 声明
	3.GlobalInvocationId 修饰的变量必须修饰为三分量 32-bit整型vec值
	*/

	//HelperInvocation
	/*
	概述:

	HelperInvocation 修饰的变量指明当前的调用是否为helper invocation，如果大于0则是，否则不是，helper invocation表示用于类似生成衍生物等内部需求的shader的调用

	HelperInvocation有效用法:
	1.HelperInvocation 必须在  Fragment  Execution Model 中使用
	2.HelperInvocation 修饰的变量必须以Input Storage Class 声明
	3.HelperInvocation 修饰的变量必须修饰为boolean值
	*/

	//HitKindKHR
	/*
	概述:
	
	HitKindKHR 修饰的变量描述触发当前shader invocation的相交，值由 intersection shader 决定，对于用户定义的 intersection shader，为传递给 “Hit Kind”运算符的OpReportIntersectionKHR值，对三角形相交，则为HitKindFrontFacingTriangleKHR 或者 HitKindBackFacingTriangleKHR
	
	HitKindKHR有效用法:
	1.HitKindKHR 必须在  AnyHitKHR 或者 ClosestHitKHR  Execution Model 中使用
	2.HitKindKHR 修饰的变量必须以Input Storage Class 声明
	3.HitKindKHR 修饰的变量必须修饰为32-bit整型值
	*/

	//HitTNV
	/*
	概述:

	HitTNV 修饰的变量等同于以RayTmaxKHR修饰的变量

	HitTNV有效用法:
	1.HitTNV 必须在  AnyHitKHR 或者 ClosestHitKHR  Execution Model 中使用
	2.HitTNV 修饰的变量必须以Input Storage Class 声明
	3.HitTNV 修饰的变量必须修饰为32-bit浮点值
	*/

	//HitTriangleVertexPositionsKHR
	/*
	概述:

	HitTriangleVertexPositionsKHR 修饰的变量指明应用提供的顺序中当前相加的三角形的顶点的对象空间坐标，这个位置进行 geometry transform后返回获得

	HitTriangleVertexPositionsKHR有效用法:
	1.HitTriangleVertexPositionsKHR 必须在  AnyHitKHR 或者 ClosestHitKHR  Execution Model 中使用
	2.HitTriangleVertexPositionsKHR 修饰的变量必须以Input Storage Class 声明
	3.HitTriangleVertexPositionsKHR 修饰的变量必须修饰为含有3个32-bit浮点值的向量的以三个向量为元素的三向量数组
	4.以HitTriangleVertexPositionsKHR 修饰的变量必须是 HitKindKHR 为 HitKindFrontFacingTriangleKHR 或者 HitKindBackFacingTriangleKHR的
	5.对应当前相交的加速结构必须以VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_DATA_ACCESS_KHR 构建
	*/

	//IncomingRayFlagsKHR
	/*
	概述:
	
	IncomingRayFlagsKHR 修饰的变量包含传递给触发这个特殊shader的trace call的ray flags，
	
	IncomingRayFlagsKHR有效用法:
	1.IncomingRayFlagsKHR 必须在  IntersectionKHR, AnyHitKHR, ClosestHitKHR, 或者 MissKHR  Execution Model 中使用
	2.IncomingRayFlagsKHR 修饰的变量必须以Input Storage Class 声明
	3.IncomingRayFlagsKHR 修饰的变量必须修饰为标量32-bit整型值
	*/

	//IndexCountHUAWEI
	/*
	概述:
	
	IndexCountHUAWEI 修饰cluster culling shader output variable，描述绘制的cluster中包含的索引顶点的数量
	
	IndexCountHUAWEI有效用法:
	1.IndexCountHUAWEI 必须在 ClusterCullingHUAWEI  Execution Model 中使用
	3.IndexCountHUAWEI 修饰的变量必须修饰为标量32-bit整型值
	*/
	
	//InstanceCountHUAWEI
	/*
	概述:

	InstanceCountHUAWEI 修饰cluster culling shader output variable，描述绘制的cluster中包含的instance的数量

	InstanceCountHUAWEI有效用法:
	1.InstanceCountHUAWEI 必须在 ClusterCullingHUAWEI  Execution Model 中使用
	2.InstanceCountHUAWEI 修饰的变量必须修饰为标量32-bit整型值
	*/

	//InstanceCustomIndexKHR
	/*
	概述:

	InstanceCustomIndexKHR 修饰的变量包含应用设置的当前ray相交的instance的自定义索引值，在当前加速结构的VkAccelerationStructureInstanceKHR::instanceCustomIndex中指定，其中使用低24bit，高8bit为0

	InstanceCustomIndexKHR有效用法:
	1.InstanceCustomIndexKHR 必须在 IntersectionKHR, AnyHitKHR, 或者 ClosestHitKHR  Execution Model 中使用
	2.InstanceCustomIndexKHR 修饰的变量必须以Input Storage Class 声明
	3.InstanceCustomIndexKHR 修饰的变量必须修饰为标量32-bit整型值
	*/

	//InstanceId
	/*
	概述:

	InstanceId 修饰的变量包含当前ray相交的instance的索引值

	InstanceId有效用法:
	1.InstanceId 必须在 IntersectionKHR, AnyHitKHR, 或者 ClosestHitKHR  Execution Model 中使用
	2.InstanceId 修饰的变量必须以Input Storage Class 声明
	3.InstanceId 修饰的变量必须修饰为标量32-bit整型值
	*/

	//InvocationId
	/*
	概述:
	
	InvocationId 修饰的变量包含当前geometry shader中shader invocation的索引值，或者是 tessellation control shader中output patch vertex的索引值
	
	InvocationId有效用法:
	1.InvocationId 必须在 TessellationControl 或者 Geometry Execution Model 中使用
	2.InvocationId 修饰的变量必须以Input Storage Class 声明
	3.InvocationId 修饰的变量必须修饰为标量32-bit整型值
	*/

	//InvocationsPerPixelNV
	/*
	概述:
	
	InvocationsPerPixelNV 修饰的变量包含fragment shader中每个像素对应的最大shader invocation的数量，如果shading rate 指明为一个片段包含多个像素，则该值1
	
	InvocationsPerPixelNV有效用法:
	1.InvocationsPerPixelNV 必须在 Fragment Execution Model 中使用
	2.InvocationsPerPixelNV 修饰的变量必须以Input Storage Class 声明
	3.InvocationsPerPixelNV 修饰的变量必须修饰为标量32-bit整型值
	*/


	//InstanceIndex
	/*
	概述:
	
	InstanceIndex 修饰的变量包含当前vertex shader invocation处理的instance的索引值， InstanceIndex 以传递给vkCmdDraw 或者 vkCmdDrawIndexed，vkCmdDrawIndirect 或者 vkCmdDrawIndexedIndirect的firstInstance参数开始
	
	InstanceIndex有效用法:
	1.InstanceIndex 必须在  Vertex Execution Model 中使用
	2.InstanceIndex 修饰的变量必须以Input Storage Class 声明
	3.InstanceIndex 修饰的变量必须修饰为标量32-bit整型值
	*/

	
	//LaunchIdKHR
	/*
	概述:
	
	LaunchIdKHR 修饰的变量指明当前work item的索引，一个work item由 vkCmdTraceRaysKHR中的width × height × depth 个items打包产生，所有shader 访问相同的LaunchIdKHR修饰的变量
	
	LaunchIdKHR有效用法:
	1.LaunchIdKHR 必须在RayGenerationKHR, IntersectionKHR, AnyHitKHR, ClosestHitKHR, MissKHR, 或者 CallableKHR Execution Model 中使用
	2.LaunchIdKHR 修饰的变量必须以Input Storage Class 声明
	3.LaunchIdKHR 修饰的变量必须修饰为三分量32-bit整型vec值
	*/

	//LaunchSizeKHR
	/*
	概述:

	LaunchSizeKHR 修饰的变量包含传递给vkCmdTraceRaysKHR初始化shader执行 的width，height以及depth维度值，第一个分量为width，第二个分量为height，第三个分量为depth

	LaunchSizeKHR有效用法:
	1.LaunchSizeKHR 必须在RayGenerationKHR, IntersectionKHR, AnyHitKHR, ClosestHitKHR, MissKHR, 或者 CallableKHR Execution Model 中使用
	2.LaunchSizeKHR 修饰的变量必须以Input Storage Class 声明
	3.LaunchSizeKHR 修饰的变量必须修饰为三分量32-bit整型vec值
	*/



	//Layer
	/*
	概述:

	Layer 修饰的变量包含选择的multi-layer framebuffer attachment的layer值，其它信息见p1440,如果还以ViewportRelativeNV声明，则ViewportIndex 将加入到渲染Leyer中且在fragment shader中可用
	如果shader写入到ViewportIndex声明的变量，则选择的layer对于每个渲染的 viewport都有不同的值，

	Layer有效用法:
	1.Layer 必须在MeshEXT, MeshNV, Vertex, TessellationEvaluation, Geometry, 或者 Fragment Execution Model 中使用
	2.如果 shaderOutputLayer 特性没有开启，则Layer 修饰的变量只能用在 Geometry 或者 Fragment Execution Model中
	3.Layer修饰的变量在MeshEXT, MeshNV, Vertex, TessellationEvaluation, 或者 Geometry Execution Model 中必须以  Output Storage Class 声明
	4.Layer修饰的变量在Fragment Execution Model 中必须以 Input Storage Class 声明
	5.Layer 修饰的变量必须修饰为标量32-bit整型值
	6.Layer修饰的变量在 MeshEXT Execution Model 中必须也以  PerPrimitiveEXT声明
	*/


	//LayerPerViewNV
	/*
	概述:

	LayerPerViewNV 修饰的变量包含 per-view layer信息，对每个view来说，其per-view layer和Layer规则相同

	LayerPerViewNV有效用法:
	1.LayerPerViewNV 必须在  MeshNV Execution Model 中使用
	2.LayerPerViewNV 修饰的变量必须以 Output Storage Class 声明
	3.LayerPerViewNV 修饰的变量也必须以 PerViewNV声明
	4.LayerPerViewNV 修饰的变量必须修饰为标量32-bit整型值
	*/
	

	//LocalInvocationId
	/*
	概述:

	LocalInvocationId 修饰的变量包含local workgroup中当前调用的位置，每个分量的值为 当前local workgroup中的索引

	LocalInvocationId有效用法:
	1.LocalInvocationId 必须在GLCompute, MeshEXT, TaskEXT, MeshNV, 或者 TaskNV Execution Model 中使用
	2.LocalInvocationId 修饰的变量必须以 Input Storage Class 声明
	3.LocalInvocationId 修饰的变量必须修饰为三分量32-bit整型vec值
	*/


	//LocalInvocationIndex
	/*
	概述:

	LocalInvocationIndex 修饰的变量是LocalInvocationId 的一维表示，即LocalInvocationIndex = LocalInvocationId.z * WorkgroupSize.x * WorkgroupSize.y +
 																						 LocalInvocationId.y * WorkgroupSize.x +
 																						 LocalInvocationId.x;

	LocalInvocationIndex有效用法:
	1.LocalInvocationIndex 必须在GLCompute, MeshEXT, TaskEXT, MeshNV, 或者 TaskNV Execution Model 中使用
	2.LocalInvocationIndex 修饰的变量必须以 Input Storage Class 声明
	3.LocalInvocationIndex 修饰的变量必须修饰为标量32-bit整型值
	*/

	
	//MeshViewCountNV
	/*
	概述:

	MeshViewCountNV 修饰的变量包含当前mesh 或者 task shader invocations处理的view的数量.

	MeshViewCountNV有效用法:
	1.MeshViewCountNV 必须在MeshNV or TaskNV Execution Model 中使用
	2.MeshViewCountNV 修饰的变量必须以 Input Storage Class 声明
	3.MeshViewCountNV 修饰的变量必须修饰为标量32-bit整型值
	*/
	
	//MeshViewIndicesNV
	/*
	概述:

	MeshViewIndicesNV 修饰的变量包含mesh views 的索引，是一组当前mesh or task shader invocations正在处理的一组views中的view的索引号，如果MeshViewIndicesNV[i]为j ，然后，在处理view索引j的原语时，任何装饰有PerViewNV 的输出都将承担数组元素i的值。

	MeshViewIndicesNV有效用法:
	1.MeshViewIndicesNV 必须在MeshNV or TaskNV Execution Model 中使用
	2.MeshViewIndicesNV 修饰的变量必须以 Input Storage Class 声明
	3.MeshViewIndicesNV 修饰的变量必须修饰为标量32-bit整型值的数组
	*/
	
	
	//NumSubgroups
	/*
	概述:

	NumSubgroups 修饰的变量包含local workgroup中包含的subgroup的数量

	NumSubgroups有效用法:
	1.NumSubgroups 必须在GLCompute, MeshEXT, TaskEXT, MeshNV, 或者 TaskNV Execution Model 中使用
	2.NumSubgroups 修饰的变量必须以 Input Storage Class 声明
	3.NumSubgroups 修饰的变量必须修饰为标量32-bit整型值
	*/
	

	// NumWorkgroups
	/*
	概述:

	 NumWorkgroups 修饰的变量包含一次invocations 所属的dispatch中 workgroup的数量，每个分量的值为传递给dispatch命令的值

	NumWorkgroups有效用法:
	1.NumWorkgroups 必须在GLCompute, MeshEXT, TaskEXT Execution Model 中使用
	2.NumWorkgroups 修饰的变量必须以 Input Storage Class 声明
	3.NumWorkgroups 修饰的变量必须修饰为三分量32-bit整型vec值
	*/

	// ObjectRayDirectionKHR
	/*
	概述:

	 ObjectRayDirectionKHR 修饰的变量包含要处理的ray的方向

	ObjectRayDirectionKHR有效用法:
	1.ObjectRayDirectionKHR 必须在 IntersectionKHR, AnyHitKHR, 或者 ClosestHitKHR Execution Model 中使用
	2.ObjectRayDirectionKHR 修饰的变量必须以 Input Storage Class 声明
	3.ObjectRayDirectionKHR 修饰的变量必须修饰为三分量32-bit浮点型vec值
	*/
	

	// ObjectRayOriginKHR
	/*
	概述:

	 ObjectRayOriginKHR 修饰的变量包含要处理的ray的原点

	ObjectRayOriginKHR有效用法:
	1.ObjectRayOriginKHR 必须在 IntersectionKHR, AnyHitKHR, 或者 ClosestHitKHR Execution Model 中使用
	2.ObjectRayOriginKHR 修饰的变量必须以 Input Storage Class 声明
	3.ObjectRayOriginKHR 修饰的变量必须修饰为三分量32-bit浮点型vec值
	*/


	// ObjectToWorldKHR
	/*
	概述:

	 ObjectToWorldKHR 修饰的变量包含object-to-world的变换矩阵，取决于当前intersection所在的instance

	ObjectToWorldKHR有效用法:
	1.ObjectToWorldKHR 必须在 IntersectionKHR, AnyHitKHR, 或者 ClosestHitKHR Execution Model 中使用
	2.ObjectToWorldKHR 修饰的变量必须以 Input Storage Class 声明
	3.ObjectToWorldKHR 修饰的变量必须修饰为含4个列，每列为三份量32-bit浮点型vec值的4x3矩阵
	*/

	// PatchVertices
	/*
	概述:

	PatchVertices 修饰的变量包含当前shader处理的input patch的顶点数量，对于tessellation control shader，该值等于VkPipelineTessellationStateCreateInfo中的name:patchControlPoints，对于tessellation evaluation shader，该值等于tessellation control output patch vertex的数量

	PatchVertices有效用法:
	1.PatchVertices 必须在TessellationControl 或者 TessellationEvaluation Execution Model 中使用
	2.PatchVertices 修饰的变量必须以 Input Storage Class 声明
	3.PatchVertices 修饰的变量必须修饰标量32-bit浮点型整型值
	*/

	// PointCoord
	/*
	概述:

	PointCoord 修饰的变量包含当前当前片段光栅化的点坐标，归一化为左上角为原点坐标(0,0)，参见p2722 Basic Point Rasterization,

	PointCoord有效用法:
	1.PointCoord 必须在Fragment Execution Model 中使用
	2.PointCoord 修饰的变量必须以 Input Storage Class 声明
	3.PointCoord 修饰的变量必须修饰二分量32-bit浮点型vec值
	*/

	// PointCoord
	/*
	概述:

	PointCoord 修饰的变量包含当前当前片段光栅化的点坐标，归一化为左上角为原点坐标(0,0)，参见p2722 Basic Point Rasterization,

	PointCoord有效用法:
	1.PointCoord 必须在Fragment Execution Model 中使用
	2.PointCoord 修饰的变量必须以 Input Storage Class 声明
	3.PointCoord 修饰的变量必须修饰二分量32-bit浮点型vec值
	*/


	// PointSize
	/*
	概述:

	PointSize 修饰的变量包含点图元光栅化的大小或者VkPhysicalDeviceMaintenance5PropertiesKHR::polygonModePointSize为VK_TRUE时，polygon mode为VK_POLYGON_MODE_POINT时的点图元的光栅化大小，该大小为光栅化点在framebuffer-space 中的大小，如果 maintenance5没开启或者该值没有写入则默认为1

	PointSize有效用法:
	1.PointSize 必须在MeshEXT, MeshNV, Vertex, TessellationControl, TessellationEvaluation, 或者 Geometry Execution Model 中使用
	2.PointSize 修饰的变量在  MeshEXT, MeshNV, 或者 Vertex Execution Model中必须以Output Storage Class 声明
	3.PointSize 修饰的变量在TessellationControl,TessellationEvaluation, 或者 Geometry Execution Model中不能以Input 或者 Output Storage Class 声明
	4.PointSize 修饰的变量必须修饰标量32-bit浮点型值
	*/



	// Position
	/*
	概述:

	Position 修饰的变量包含当前处理的顶点的位置，这个值会用在后续图元装配，裁剪以及光栅化中

	Position有效用法:
	1.Position 必须在MeshEXT, MeshNV, Vertex, TessellationControl, TessellationEvaluation, 或者 Geometry Execution Model 中使用
	2.Position 修饰的变量在  MeshEXT, MeshNV, 或者 Vertex Execution Model中必须以Output Storage Class 声明
	3.Position 修饰的变量在TessellationControl,TessellationEvaluation, 或者 Geometry Execution Model中不能以Input 或者 Output Storage Class 声明
	4.Position 修饰的变量必须修饰四分量32-bit浮点型vec值
	*/


	// PositionPerViewNV
	/*
	概述:

	PositionPerViewNV 修饰的变量包含每个view当前处理的顶点的位置，这个值会用在后续图元装配，裁剪以及光栅化中，如果shader的subpass含有VK_SUBPASS_DESCRIPTION_PER_VIEW_POSITION_X_ONLY_BIT_NVX，则每个view的位置只能允许x分量上值不同

	PositionPerViewNV有效用法:
	1.PositionPerViewNV 必须在 MeshNV, Vertex, TessellationControl, TessellationEvaluation, 或者 Geometry Execution Model 中使用
	2.PositionPerViewNV 修饰的变量在 MeshNV, 或者 Vertex Execution Model中必须以Output Storage Class 声明
	3.PositionPerViewNV 修饰的变量在TessellationControl,TessellationEvaluation, 或者 Geometry Execution Model中不能以Input 或者 Output Storage Class 声明
	4.PositionPerViewNV 修饰的变量必须修饰四分量32-bit浮点型vec值的数组，数组大小为subpass中最大的view mask + 1
	5.PositionPerViewNV 修饰的变量必须以常量索引或者特殊的常量索引
	*/

	// PrimitiveCountNV
	/*
	概述:
	
	PrimitiveCountNV 修饰的变量包含图元的个数，图元个数为mesh shader 产生的用于后续阶段的图元数量
	
	PrimitiveCountNV有效用法:
	1.PrimitiveCountNV 必须在 MeshNV Execution Model 中使用
	2.PrimitiveCountNV 修饰的变量必须以Output Storage Class 声明
	4.PrimitiveCountNV 修饰的变量必须修饰标量32-bit整型值
	*/

	// PrimitiveId
	/*
	概述:
	
	PrimitiveId 修饰的变量包含当前图元的索引，参见p1448
	
	PrimitiveId有效用法:
	1.PrimitiveId 必须在MeshEXT, MeshNV, IntersectionKHR, AnyHitKHR, ClosestHitKHR, TessellationControl, TessellationEvaluation, Geometry, 或者 Fragment Execution Model 中使用
	2.如果pipeline同时包含 Fragment 和 Geometry Execution Model以及一个被修饰为 PrimitiveId变量在Fragment shader中读取，那么 Geometry shader 必须在所有路径上将 PrimitiveId 修饰的输出变量写入
	3.如果pipeline同时包含 Fragment 和 MeshEXT 或者 MeshNV Execution Model以及一个被修饰为 PrimitiveId变量在Fragment shader中读取，那么 MeshEXT 或者 MeshNV shader 必须在所有路径上将 PrimitiveId 修饰的输出变量写入
	4.如果Fragment Execution Model包含一个被修饰为 PrimitiveId的变量，则MeshShadingEXT, MeshShadingNV, Geometry 或者 Tessellation其中之一的capability 需要也被声明
	5.PrimitiveCountNV 修饰的变量在TessellationControl,TessellationEvaluation, Fragment, IntersectionKHR, AnyHitKHR, 或者 ClosestHitKHR Execution Model中必须以 Input Storage Class修饰
	6.PrimitiveCountNV 修饰的变量在Geometry Execution Model中必须以 Input 或者 Output Storage Class修饰
	7.PrimitiveCountNV 修饰的变量在MeshEXT 或者MeshNV Execution Model中必须以 Output Storage Class修饰
	8.PrimitiveId 修饰的变量必须修饰为标量32-bit整型值
	9.在MeshEXT Execution Model 修饰的PrimitiveId 变量必须也被修饰为PerPrimitiveEXT
	*/

	
	// PrimitiveIndicesNV
	/*
	概述:
	
	PrimitiveIndicesNV 修饰的变量为包含顶点索引的输出数组 ，参见p1450
	
	PrimitiveIndicesNV有效用法:
	1.PrimitiveIndicesNV 必须在 MeshNV Execution Model 中使用
	2.PrimitiveIndicesNV 修饰的变量必须以 Output Storage Class修饰
	3.PrimitiveIndicesNV 修饰的变量必须修饰为标量32-bit整型值的数组
	4.PrimitiveIndicesNV 修饰的变量数组的元素值范围为[0-N],N在OutputVertices Execution Mode 中指明
	5.如果Execution Mode 为 OutputPoints，则以PrimitiveIndicesNV 修饰的变量数组的大小在 OutputPrimitivesNV 中指定
	6.如果Execution Mode 为 OutputLinesNV，则以PrimitiveIndicesNV 修饰的变量数组的大小在 OutputPrimitivesNV 中指定的两倍
	7.如果Execution Mode 为 OutputTrianglesNV，则以PrimitiveIndicesNV 修饰的变量数组的大小在 OutputPrimitivesNV 中指定的三倍
	*/

	// PrimitivePointIndicesEXT
	/*
	概述:

	PrimitivePointIndicesEXT 修饰的变量为包含顶点图元顶点索引的输出数组 ，参见p1451

	PrimitivePointIndicesEXT有效用法:
	1.PrimitivePointIndicesEXT 必须在 MeshNV Execution Model 中使用
	2.PrimitivePointIndicesEXT 必须和 OutputPoints Execution Mode同时使用
	3.PrimitivePointIndicesEXT 修饰的变量必须以 Output Storage Class修饰
	4.PrimitivePointIndicesEXT 修饰的变量必须修饰为标量32-bit整型值的数组
	5.PrimitivePointIndicesEXT 修饰的变量数组的元素值范围为[0-N],N在OutputVertices Execution Mode 中指明
	6.PrimitivePointIndicesEXT 修饰的变量数组的大小匹配在 OutputPrimitivesNV 中指定的值
	*/
	

	// PrimitiveLineIndicesEXT
	/*
	概述:

	PrimitivePointIndicesEXT 修饰的变量为包含线图元顶点索引的输出数组 ，参见p1451

	PrimitiveLineIndicesEXT有效用法:
	1.PrimitiveLineIndicesEXT 必须在 MeshNV Execution Model 中使用
	2.PrimitiveLineIndicesEXT 必须和 OutputLinesEXT Execution Mode同时使用
	3.PrimitiveLineIndicesEXT 修饰的变量必须以 Output Storage Class修饰
	4.PrimitiveLineIndicesEXT 修饰的变量必须修饰为标量32-bit整型值的数组
	5.PrimitiveLineIndicesEXT 修饰的变量数组的元素值范围为[0-N],N在OutputVertices Execution Mode 中指明
	6.PrimitiveLineIndicesEXT 修饰的变量数组的大小匹配在 OutputPrimitivesNV 中指定的值
	*/


	// PrimitiveTriangleIndicesEXT
	/*
	概述:

	PrimitiveTriangleIndicesEXT 修饰的变量为包含三角形图元顶点索引的输出数组 ，参见p1451

	PrimitiveTriangleIndicesEXT有效用法:
	1.PrimitiveTriangleIndicesEXT 必须在 MeshNV Execution Model 中使用
	2.PrimitiveTriangleIndicesEXT 必须和 OutputTrianglesEXT Execution Mode同时使用
	3.PrimitiveTriangleIndicesEXT 修饰的变量必须以 Output Storage Class修饰
	4.PrimitiveTriangleIndicesEXT 修饰的变量必须修饰为标量32-bit整型值的数组
	5.PrimitiveTriangleIndicesEXT 修饰的变量数组的元素值范围为[0-N],N在OutputVertices Execution Mode 中指明
	6.PrimitiveTriangleIndicesEXT 修饰的变量数组的大小匹配在 OutputPrimitivesNV 中指定的值
	*/

	// PrimitiveShadingRateKHR
	/*
	概述:
	
	PrimitiveShadingRateKHR 修饰的变量包含 primitive fragment shading rate，参见p1452
	
	PrimitiveShadingRateKHR有效用法:
	1.PrimitiveShadingRateKHR 必须在MeshEXT, MeshNV, Vertex, 或者 Geometry Execution Model 中使用
	2.PrimitiveShadingRateKHR 修饰的变量必须以 Output Storage Class修饰
	3.PrimitiveShadingRateKHR 修饰的变量必须修饰为标量32-bit整型值
	4.写入到PrimitiveShadingRateKHR 修饰变量的值至多是Vertical2Pixels 以及 Vertical4Pixels，Horizontal2Pixels 以及 Horizontal4Pixels中的一个值
	5.写入到PrimitiveShadingRateKHR 修饰变量的值不能有flags比特设置是没有定义在Fragment Shading Rate Flags 中的值
	6.PrimitiveShadingRateKHR 修饰变量的值在MeshEXT Execution Model中，也必须以PerPrimitiveEXT修饰
	
	*/


	// RayGeometryIndexKHR
	/*
	概述:
	
	RayGeometryIndexKHR 修饰的变量当前被shaded的加速结构中geometry的索引
	
	RayGeometryIndexKHR有效用法:
	1.RayGeometryIndexKHR 必须在 IntersectionKHR, AnyHitKHR, 或者 ClosestHitKHR Execution Model 中使用
	2.RayGeometryIndexKHR 修饰的变量必须以Input Storage Class 声明
	3.RayGeometryIndexKHR 修饰的变量必须修饰标量32-bit整型值
	*/


	// RayTmaxKHR
	/*
	概述:

	RayTmaxKHR 修饰的变量包含当前处理的ray的参数tmax的值，这个参数是传递给 pipeline trace ray指令的值，参见p1454

	RayTmaxKHR有效用法:
	1.RayTmaxKHR 必须在 IntersectionKHR, AnyHitKHR, ClosestHitKHR或者MissKHR  Execution Model 中使用
	2.RayTmaxKHR 修饰的变量必须以Input Storage Class 声明
	3.RayTmaxKHR 修饰的变量必须修饰标量32-bit浮点值
	*/

	
	// RayTminKHR
	/*
	概述:

	RayTminKHR 修饰的变量包含当前处理的ray的参数tmin的值，这个参数是传递给 pipeline trace ray指令的值，参见p1454

	RayTminKHR有效用法:
	1.RayTminKHR 必须在 IntersectionKHR, AnyHitKHR, ClosestHitKHR或者MissKHR  Execution Model 中使用
	2.RayTminKHR 修饰的变量必须以Input Storage Class 声明
	3.RayTminKHR 修饰的变量必须修饰标量32-bit浮点值
	*/


	// SampleId
	/*
	概述:
	
	SampleId 修饰的变量包含当前fragment shader调用的coverage index， SampleId的范围从0到fragment中的采样数减去1，如果fragment shader中包含这个修饰的变量则认为以 minSampleShading 为1开启了sample shading
	
	SampleId有效用法:
	1.SampleId 必须在Fragment  Execution Model 中使用
	2.SampleId 修饰的变量必须以Input Storage Class 声明
	3.SampleId 修饰的变量必须修饰为标量32-bit整型值
	*/

	// SampleMask
	/*
	概述:

	SampleMask 修饰的变量包含当前fragment shader调用的sample mask， 参见p1455

	SampleMask有效用法:
	1.SampleMask 必须在Fragment  Execution Model 中使用
	2.SampleMask 修饰的变量必须以Input 或者Output Storage Class 声明
	3.SampleMask 修饰的变量必须修饰为32-bit整型值的数组
	*/
	

	// SamplePosition
	/*
	概述:
	
	SamplePosition 修饰的变量包含当前着色的采样点的sub-pixel位置，左上角为（0，0），右下角为（1，1），如果开启subpass含有 fragment density map attachment，则该变量包含当前fragment的采样点的sub-fragment坐标
	
	SamplePosition有效用法:
	1.SamplePosition 必须在Fragment  Execution Model 中使用
	2.SamplePosition 修饰的变量必须以Input Storage Class 声明
	3.SamplePosition 修饰的变量必须修饰为二分量32-bit浮点vec值
	*/


	// ShadingRateKHR
	/*
	概述:

	ShadingRateKHR 修饰的变量包含当前片段调用的 fragment shading rate，参见p1456

	ShadingRateKHR有效用法:
	1.ShadingRateKHR 必须在Fragment  Execution Model 中使用
	2.ShadingRateKHR 修饰的变量必须以Input Storage Class 声明
	3.ShadingRateKHR 修饰的变量必须修饰为标量32-bit整型值
	*/

	// SMCountNV
	/*
	概述:
	
	SMCountNV 修饰的变量包含设备上的SMs的数量
	
	SMCountNV有效用法:
	1.SMCountNV 修饰的变量必须以Input Storage Class 声明
	2.SMCountNV 修饰的变量必须修饰为标量32-bit整型值
	*/


	// SMIDNV
	/*
	概述:
	
	SMIDNV 修饰的变量包含当前shader invocation的SM的索引，范围在[0,..,SMCountNV]中
	
	SMIDNV有效用法:
	1.SMIDNV 修饰的变量必须以Input Storage Class 声明
	2.SMIDNV 修饰的变量必须修饰为标量32-bit整型值
	*/

	// SubgroupId
	/*
	概述:
	
	SubgroupId 修饰的变量包含local workgroup中subgroup的索引，范围在[0,..., NumSubgroups-1]中
	
	SubgroupId有效用法:
	1.SubgroupId 必须在 GLCompute, MeshEXT, TaskEXT, MeshNV, 或者 TaskNV  Execution Model 中使用
	2.SubgroupId 修饰的变量必须以Input Storage Class 声明
	3.SubgroupId 修饰的变量必须修饰为标量32-bit整型值
	*/


	// SubgroupEqMask
	/*
	概述:
	
	SubgroupEqMask 修饰的变量包含当前subgroup invocation的subgroup mask，对应SubgroupLocalInvocationId的这个比特设置在SubgroupEqMask修饰的变量中，SubgroupEqMaskKHR 为SubgroupEqMask别名
	
	SubgroupEqMask有效用法:
	1.SubgroupEqMask 修饰的变量必须以Input Storage Class 声明
	2.SubgroupEqMask 修饰的变量必须修饰为四分量32-bit整型vec值
	*/
	
	
	// SubgroupGeMask
	/*
	概述:

	SubgroupGeMask 修饰的变量包含当前subgroup invocation的subgroup mask，对应invocations大于等于设置在 SubgroupGeMask的 SubgroupSize-1个对应到SubgroupLocalInvocationId的值，SubgroupGeMaskKHR 为SubgroupGeMask别名

	SubgroupGeMask有效用法:
	1.SubgroupGeMask 修饰的变量必须以Input Storage Class 声明
	2.SubgroupGeMask 修饰的变量必须修饰为四分量32-bit整型vec值
	*/

	// SubgroupGtMask
	/*
	概述:

	SubgroupGtMask 修饰的变量包含当前subgroup invocation的subgroup mask，对应invocations大于设置在 SubgroupGeMask的 SubgroupSize-1个对应到SubgroupLocalInvocationId的值，SubgroupGtMaskKHR 为SubgroupGtMask别名

	SubgroupGtMask有效用法:
	1.SubgroupGtMask 修饰的变量必须以Input Storage Class 声明
	2.SubgroupGtMask 修饰的变量必须修饰为四分量32-bit整型vec值
	*/


	// SubgroupLeMask
	/*
	概述:

	SubgroupLeMask 修饰的变量包含当前subgroup invocation的subgroup mask，对应invocations小于等于设置在 SubgroupGeMask的 SubgroupLocalInvocationId，SubgroupLeMaskKHR 为SubgroupLeMask别名

	SubgroupLeMask有效用法:
	1.SubgroupLeMask 修饰的变量必须以Input Storage Class 声明
	2.SubgroupLeMask 修饰的变量必须修饰为四分量32-bit整型vec值
	*/


	// SubgroupLtMask
	/*
	概述:

	SubgroupLtMask 修饰的变量包含当前subgroup invocation的subgroup mask，对应invocations小于设置在 SubgroupGeMask的 SubgroupLocalInvocationId，SubgroupLtMaskKHR 为SubgroupLtMask别名

	SubgroupLtMask有效用法:
	1.SubgroupLtMask 修饰的变量必须以Input Storage Class 声明
	2.SubgroupLtMask 修饰的变量必须修饰为四分量32-bit整型vec值
	*/



	// SubgroupLocalInvocationId
	/*
	概述:

	SubgroupLocalInvocationId 修饰的变量包含subgroup 中invocation的索引，范围[0,SubgroupSize-1].其他信息参见p1459

	SubgroupLocalInvocationId有效用法:
	1.SubgroupLocalInvocationId 修饰的变量必须以Input Storage Class 声明
	2.SubgroupLocalInvocationId 修饰的变量必须修饰为标量32-bit整型值
	*/

	// SubgroupSize
	/*
	概述:

	SubgroupSize 修饰的变量包含subgroup中invocation的数量，基于实现，必须是2的指数，其他信息参见p1460

	SubgroupSize有效用法:
	1.SubgroupSize 修饰的变量必须以Input Storage Class 声明
	2.SubgroupSize 修饰的变量必须修饰为标量32-bit整型值
	*/
	

	// TaskCountNV
	/*
	概述:
	
	TaskCountNV 修饰的变量包含task的数量，指明task shader结束后产生的后续mesh shader可以使用的task的数量
	
	TaskCountNV有效用法:
	1.TaskCountNV 必须在 TaskNV  Execution Model 中使用
	2.TaskCountNV 修饰的变量必须以 Output Storage Class 声明
	3.TaskCountNV 修饰的变量必须修饰为标量32-bit整型值
	*/


	// TessCoord
	/*
	概述:
	
	TessCoord 修饰的变量包含patch中 tessellated顶点的三维度（u,v,w）重心坐标，范围在[0,1]中，参见p1462
	
	TessCoord有效用法:
	1.TessCoord 必须在 TessellationEvaluation  Execution Model 中使用
	2.TessCoord 修饰的变量必须以 Input Storage Class 声明
	3.TessCoord 修饰的变量必须修饰为三分量32-bit浮点vec值
	*/


	
	// TessLevelOuter
	/*
	概述:

	TessLevelOuter 修饰的变量包含patch的outer tessellation levels，用于控制 图元的tessellation，由tessellation control shaders 写，tessellation evaluation shaders读

	TessLevelOuter有效用法:
	1.TessLevelOuter 必须在 TessellationControl 或者 TessellationEvaluation  Execution Model 中使用
	2.TessLevelOuter 修饰的变量必须在 TessellationControl  Execution Model 中 以 Output Storage Class 声明
	3.TessLevelOuter 修饰的变量必须在 TessellationEvaluation  Execution Model 中 以 Input Storage Class 声明
	3.TessLevelOuter 修饰的变量必须修饰为包含32-bit浮点值的大小为4的数组
	*/

	// TessLevelInner
	/*
	概述:

	TessLevelInner 修饰的变量包含patch的inner tessellation levels，用于控制 图元的tessellation，由tessellation control shaders 写，tessellation evaluation shaders读

	TessLevelInner有效用法:
	1.TessLevelInner 必须在 TessellationControl 或者 TessellationEvaluation  Execution Model 中使用
	2.TessLevelInner 修饰的变量必须在 TessellationControl  Execution Model 中 以 Output Storage Class 声明
	3.TessLevelInner 修饰的变量必须在 TessellationEvaluation  Execution Model 中 以 Input Storage Class 声明
	3.TessLevelInner 修饰的变量必须修饰为包含32-bit浮点值的大小为2的数组
	*/

	// VertexCountHUAWEI
	/*
	概述:

	VertexCountHUAWEI 用来修饰cluster culling shader output variable ，非索引模式指定的变量将指明cluster绘制中的点的数量

	VertexCountHUAWEI有效用法:
	1.VertexCountHUAWEI 必须在ClusterCullingHUAWEI  Execution Model 中使用
	2.VertexCountHUAWEI 修饰的变量必须修饰为标量32-bit整型值
	*/
	
	// VertexIndex
	/*
	概述:

	VertexIndex 修饰的变量包含当前vertex shader处理的顶点的索引，对于非索引绘制，VertexIndex开始于vkCmdDraw或者 vkCmdDrawIndirect的firstVertex 参数，在索引绘制中，其值为当前顶点的索引缓冲区中的索引值加上 vkCmdDraw或者 vkCmdDrawIndirect的 vertexOffset

	VertexIndex有效用法:
	1.VertexIndex 必须在 Vertex  Execution Model 中使用
	2.VertexIndex 修饰的变量必须以Input Storage Class 声明
	3.VertexIndex 修饰的变量必须修饰为标量32-bit整型值
	*/


	// VertexOffsetHUAWEI
	/*
	概述:

	VertexOffsetHUAWEI 用来修饰cluster culling shader output variable，索引模式修饰的变量将指明cluster绘制时索引顶点缓冲区索引顶点要加上的偏移值

	VertexOffsetHUAWEI有效用法:
	1.VertexOffsetHUAWEI 必须在 ClusterCullingHUAWEI  Execution Model 中使用
	2.VertexOffsetHUAWEI 修饰的变量必须修饰为标量32-bit整型值
	*/


	// ViewIndex
	/*
	概述:

	ViewIndex 修饰的变量用于shader input，填充当前invocation处理的 view的索引值，

	ViewIndex有效用法:
	1.ViewIndex 必须在MeshEXT, Vertex, Geometry, TessellationControl, TessellationEvaluation 或者 Fragment  Execution Model 中使用
	2.ViewIndex 修饰的变量必须以Input Storage Class 声明
	3.ViewIndex 修饰的变量必须修饰为标量32-bit整型值
	*/


	// ViewportIndex
	/*
	概述:

	ViewportIndex 修饰的变量包含viewport的索引值，参见p1465

	ViewportIndex有效用法:
	1.ViewportIndex 必须在MeshEXT, MeshNV, Vertex, TessellationEvaluation, Geometry, 或者 Fragment Execution Model 中使用
	2.如果 shaderOutputViewportIndex 特性没有开启，则 ViewportIndex 只能用于 Geometry, 或者 Fragment Execution Model
	3.ViewportIndex 修饰的变量在MeshEXT, MeshNV, Vertex, TessellationEvaluation, 或者 Geometry Execution Model 必须以Output Storage Class 声明
	4.ViewportIndex 修饰的变量在Fragment Execution Model 必须以Input Storage Class 声明
	5.ViewportIndex 修饰的变量必须修饰为标量32-bit整型值
	6..ViewportIndex 修饰的变量在 MeshEXT Execution Model 必须也以 PerPrimitiveEXT 声明
	*/


	// ViewportMaskNV
	/*
	概述:

	ViewportMaskNV 修饰的变量包含viewport mask，参见p1466

	ViewportMaskNV有效用法:
	1.ViewportMaskNV 必须在Vertex, MeshNV, TessellationEvaluation, 或者 Geometry  Execution Model 中使用
	2.ViewportMaskNV 修饰的变量必须以 Output Storage Class 声明
	3.ViewportMaskNV 修饰的变量必须修饰为32-bit整型值的数组
	*/


	// ViewportMaskPerViewNV
	/*
	概述:

	ViewportMaskPerViewNV 修饰的变量包含每个view的图元要广播到的viewport mask，参见p1466

	ViewportMaskPerViewNV有效用法:
	1.ViewportMaskPerViewNV 必须在Vertex, MeshNV, TessellationControl, TessellationEvaluation, 或者 Geometry  Execution Model 中使用
	2.ViewportMaskPerViewNV 修饰的变量必须以 Output Storage Class 声明
	3.ViewportMaskPerViewNV 修饰的变量必须修饰为32-bit整型值的数组
	4.ViewportMaskPerViewNV 修饰的数组大小必须小于等于32且必须大于subpass view mask中最大的view对应的值
	5.ViewportMaskPerViewNV 修饰的数组必须以常量索引或者特殊常量索引
	*/

	// WarpsPerSMNV
	/*
	概述:

	WarpsPerSMNV 修饰的变量包含执行在SM 上的warps的最大数量

	ViewportMaskPerViewNV有效用法:
	1.ViewportMaskPerViewNV 修饰的变量必须以 Input Storage Class 声明
	2.ViewportMaskPerViewNV 修饰的变量必须修饰为标量32-bit整型值

	*/
	
	// WarpIDNV
	/*
	概述:
	
	WarpIDNV 修饰的变量包含在SM 上当前shader invocation 执行的warps的ID，范围在[0,WarpsPerSMNV-1]中
	
	WarpIDNV有效用法:
	1.WarpIDNV 修饰的变量必须以 Input Storage Class 声明
	2.WarpIDNV 修饰的变量必须修饰为标量32-bit整型值
	
	*/

	// WorkgroupId
	/*
	概述:

	WorkgroupId 修饰的变量包含当前shader invocation调用所属的global workgroup的ID，参见p1468

	WorkgroupId有效用法:
	1.WorkgroupId 必须在GLCompute, MeshEXT, TaskEXT, MeshNV, 或者 TaskNV  Execution Model 中使用
	2.WorkgroupId 修饰的变量必须以 Input Storage Class 声明
	3.WorkgroupId 修饰的变量必须修饰为三分量32-bit整型vec值
	*/
	

	// WorkgroupSize
	/*
	概述:
	
	WorkgroupSize 修饰的变量包含local workgroup的大小维度，参见p1468
	
	WorkgroupSize有效用法:
	1.WorkgroupSize 必须在GLCompute, MeshEXT, TaskEXT, MeshNV, 或者 TaskNV  Execution Model 中使用
	2.WorkgroupSize 修饰的变量必须是一个specification 常数或者常数
	3.WorkgroupSize 修饰的变量必须修饰为三分量32-bit整型vec值
	*/

	// WorldRayDirectionKHR
	/*
	概述:

	WorldRayDirectionKHR 修饰的变量包含当前处理的ray的世界空间的方向，该值通过参数传给 pipeline trace ray指令

	WorldRayDirectionKHR有效用法:
	1.WorldRayDirectionKHR 必须在IntersectionKHR, AnyHitKHR, ClosestHitKHR, 或者 MissKHR  Execution Model 中使用
	2.WorldRayDirectionKHR 修饰的变量必须以 Input Storage Class 声明
	3.WorldRayDirectionKHR 修饰的变量必须修饰为三分量32-bit浮点vec值
	*/
	

	// WorldRayOriginKHR
	/*
	概述:

	WorldRayOriginKHR 修饰的变量包含当前处理的ray的世界空间的原点，该值通过参数传给 pipeline trace ray指令

	WorldRayOriginKHR有效用法:
	1.WorldRayOriginKHR 必须在IntersectionKHR, AnyHitKHR, ClosestHitKHR, 或者 MissKHR  Execution Model 中使用
	2.WorldRayOriginKHR 修饰的变量必须以 Input Storage Class 声明
	3.WorldRayOriginKHR 修饰的变量必须修饰为三分量32-bit浮点vec值
	*/


	// WorldToObjectKHR
	/*
	概述:
	
	WorldToObjectKHR 修饰的变量包含world-to-object 转换矩阵，取决于当前相交的instance
	
	WorldToObjectKHR有效用法:
	1.WorldToObjectKHR 必须在IntersectionKHR, AnyHitKHR, 或者 ClosestHitKHR  Execution Model 中使用
	2.WorldToObjectKHR 修饰的变量必须以 Input Storage Class 声明
	3.WorldToObjectKHR 修饰的变量必须修饰为四个列的，每列为三分量32-bit浮点vec值的矩阵
	*/


	// CoreCountARM
	/*
	概述:
	
	CoreCountARM 修饰的变量包含设备上core的数量
	
	CoreCountARM有效用法:
	1.CoreCountARM 修饰的变量必须以 Input Storage Class 声明
	2.CoreCountARM 修饰的变量必须修饰为标量32-bit整型值
	*/

	// CoreMaxIDARM
	/*
	概述:

	CoreMaxIDARM 修饰的变量包含设备上当前运行的shader invocation的最大的shader core的ID

	CoreMaxIDARM有效用法:
	1.CoreMaxIDARM 修饰的变量必须以 Input Storage Class 声明
	2.CoreMaxIDARM 修饰的变量必须修饰为标量32-bit整型值
	*/
	

	// CoreIDARM
	/*
	概述:

	CoreIDARM 修饰的变量包含当前运行的shader invocation的的shader core的ID,范围[0,CoreMaxIDARM]

	CoreIDARM有效用法:
	1.CoreIDARM 修饰的变量必须以 Input Storage Class 声明
	2.CoreIDARM 修饰的变量必须修饰为标量32-bit整型值
	*/

	// WarpMaxIDARM
	/*
	概述:

	WarpMaxIDARM 修饰的变量包含当前运行的shader invocation的shader core的最大的warp的ID

	WarpMaxIDARM有效用法:
	1.WarpMaxIDARM 修饰的变量必须以 Input Storage Class 声明
	2.WarpMaxIDARM 修饰的变量必须修饰为标量32-bit整型值
	*/
	

	// WarpIDARM
	/*
	概述:

	WarpIDARM 修饰的变量包含当前运行的shader invocation的shader core的warp的ID,范围[0,WarpMaxIDARM]

	WarpIDARM有效用法:
	1.WarpIDARM 修饰的变量必须以 Input Storage Class 声明
	2.WarpIDARM 修饰的变量必须修饰为标量32-bit整型值
	*/


	// CoalescedInputCountAMDX
	/*
	概述:

	CoalescedInputCountAMDX 修饰的变量包含实现合并到当前shader input的despatch node的数量，范围[1,arraySize],arraySize为shader最大的input payload数组大小

	CoalescedInputCountAMDX有效用法:
	1.CoalescedInputCountAMDX 修饰的变量必须以 Input Storage Class 声明
	2.如果CoalescedInputCountAMDX 修饰了一个变量，则必须声明CoalescingAMDX execution mode
	2.CoalescedInputCountAMDX 修饰的变量必须修饰为标量32-bit整型值
	*/


	// ShaderIndexAMDX
	/*
	概述:

	ShaderIndexAMDX 修饰的变量包含编译时指定的当前shader的索引，或者是在 ShaderIndexAMDX execution mode 中VkPipelineShaderStageNodeCreateInfoAMDX::index指定的shader的索引

	ShaderIndexAMDX有效用法:
	1.ShaderIndexAMDX 修饰的变量必须以 Input Storage Class 声明
	2.ShaderIndexAMDX 修饰的变量必须修饰为标量32-bit整型值
	*/
}


NS_TEST_END