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

		// DescriptorSet and Binding Assignment  To do
	}


}


NS_TEST_END