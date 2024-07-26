#include "ShadersInterfaceTest.h"
NS_TEST_BEGIN

/*
����:
��pipeline�����˺���ָ����shaders������ʽ���ӵ�һϵ�еĽӿ�:
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
		//����interface��һ��shader��һ��ƥ�䵽��һ��shader ���������Լ�һ��ƥ����һ��shader stage����������빹��
		//����interface�ı�����ΪOpEntryPoint ָ��������оٳ������� Input ���� Output storage classes��������,�����Ľӿ�ֻ����������������shader stage֮��
		//����interface�ı�������built-in �����Լ� user-defined����


		//Built-in Interface Block   �μ�p1395

		//User-defined Variable Interface   �μ�p1395

		// Interface Matching �μ�p1396

		//Location Assignment �μ�p1396
		{
		/*
		ÿ��shader interface���õ�location��������
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

		//Component Assignment �μ�p1398




	}


	//Vertex Input Interface �μ�p1398
	{
		// ����vertex input attributes�Ľӿڣ��ýӿ���ͨ��Location�Լ�Component�����ı�������  VkGraphicsPipelineCreateInfo.pVertexInputState�е���Ϣ��ƥ��
	}

	//Fragment Output Interface
	{
		//fragment shader�������������render pass�ж����color attachment�Ľӿڣ�ͨ��Location �Լ� Component��Indexƥ�䣬Location[i]��ӦVkRenderingInfo::pColorAttachments[i].
	
		//��� dynamicRenderingLocalRead ���Կ�����Location��VkRenderingInfo::pColorAttachments��ӳ����Զ�ָ̬��

		VkRenderingAttachmentLocationInfoKHR renderingAttachmentLocationInfoKHR{};//���԰�����VkGraphicsPipelineCreateInfo��ָ��ӳ����Ϣ,Ҳ���԰����� VkCommandBufferInheritanceInfo�����̳�primary command buffer��state
		renderingAttachmentLocationInfoKHR.sType = VK_STRUCTURE_TYPE_MAX_ENUM;//û�ж������Զ���Ϊ�Ƿ�ֵ
		renderingAttachmentLocationInfoKHR.pNext = nullptr;
		renderingAttachmentLocationInfoKHR.colorAttachmentCount = 1;//pColorAttachmentLocations��Ԫ�ظ���
		uint32_t colorAttachmentLocation = 2;
		renderingAttachmentLocationInfoKHR.pColorAttachmentLocations = &colorAttachmentLocation;//��colorAttachmentCount��uint32_t ֵ������ָ�룬ָ��color attachment������ӳ���Location�����ΪNULL����ȼ������е�ֵΪ[0,...colorAttachmentCount-1]
		/*
		VkRenderingAttachmentLocationInfoKHR��Ч�÷�:
		1.���dynamicRenderingLocalRead ����û�п�������pColorAttachmentLocations��ΪNULL����pColorAttachmentLocations�е�ֵ������Ϊ[0,...colorAttachmentCount-1]
		2.pColorAttachmentLocations�ж�Ӧ������VK_ATTACHMENT_UNUSED�ĸ�����Ԫ�صĸ�������ֵ������Ψһ��
		3.colorAttachmentCount ����С�ڵ���maxColorAttachments
		4.pColorAttachmentLocations�е�Ԫ��ֵ����С��maxColorAttachments
		*/


		//��̬����Location��VkRenderingInfo::pColorAttachments��ӳ��
		vkCmdSetRenderingAttachmentLocationsKHR(VkCommandBuffer{/*��������һ����Ч��VkCommandBuffer*/ }, &renderingAttachmentLocationInfoKHR);
		/*
		vkCmdSetRenderingAttachmentLocationsKHR��Ч�÷�:
		1.dynamicRenderingLocalRead ���Ա��뿪��
		2.pLocationInfo->colorAttachmentCount ������ڿ�ʼ��ǰrender passʵ����VkRenderingInfo::colorAttachmentCount
		3.��ǰ��render passʵ�������Ѿ�ͨ����commandBuffer��vkCmdBeginRendering���ÿ�ʼ����ʹ����

		*/


		//����ӿ��е���Component0��1��2��3�����������Ӧ��color blend��Ԫ�����R��G��B��A����    ��Index 0��1�����������Ӧ��color blend��Ԫ�ĵ�һ���ڶ�������

	}

	// Legacy Dithering �μ�p1403


	// Fragment Tile Image Interface �μ�p1403
	{
		//�ýӿڶ�����fragment shader �У���ȡ VkRenderingInfoKHR::pColorAttachments��ֻ����Location��TileImageEXT���幹�ɽӿڣ�����ʹ��Component
	}

	// Fragment Input Attachment Interface �μ�p1403
	{
		//�ýӿڶ�����fragment shader �У���ȡrender pass�е�VkRenderingInfoKHR::pInputAttachments,��InputAttachmentIndex�Լ� UniformConstant���幹�ɽӿڣ����õ����븽��������VkPhysicalDeviceLimits::maxPerStageDescriptorInputAttachments


		VkRenderingInputAttachmentIndexInfoKHR renderingInputAttachmentIndexInfoKHR{};//���԰�����VkGraphicsPipelineCreateInfo��ָ��ӳ����Ϣ,Ҳ���԰����� VkCommandBufferInheritanceInfo�����̳�primary command buffer��state
		renderingInputAttachmentIndexInfoKHR.sType = VK_STRUCTURE_TYPE_MAX_ENUM;
		renderingInputAttachmentIndexInfoKHR.pNext = nullptr;
		uint32_t colorAttachmentIndex = 2,depthAttachmentIndex = 3,stencilAttachmentIndex = 3;
		renderingInputAttachmentIndexInfoKHR.colorAttachmentCount = 1;//pColorAttachmentInputIndices �е�Ԫ�ظ���
		renderingInputAttachmentIndexInfoKHR.pColorAttachmentInputIndices = &colorAttachmentIndex;//��colorAttachmentCount��uint32_t ֵ������ָ�룬ָ������input attachment��color attachment������ӳ���InputAttachmentIndex�����ΪNULL����ȼ������е�ֵΪ[0,...colorAttachmentCount-1],������е�ֵΪ VK_ATTACHMENT_UNUSED,������color attachment����Ϊinput attachmentʹ��
		renderingInputAttachmentIndexInfoKHR.pDepthInputAttachmentIndex = &depthAttachmentIndex;//��NULL����1��uint32_t ֵ������ָ�룬ָ������input attachment��depth attachment������ӳ���InputAttachmentIndex ,�������ΪNULL������ӳ�䵽����  InputAttachmentIndex������input attachment,�����ֵ��Ӧһ��VK_ATTACHMENT_UNUSED��������depth attachment����Ϊinput attachmentʹ��
		renderingInputAttachmentIndexInfoKHR.pStencilInputAttachmentIndex = &stencilAttachmentIndex;//��NULL����1��uint32_t ֵ������ָ�룬ָ������input attachment��stencil attachment������ӳ���InputAttachmentIndex ,�������ΪNULL������ӳ�䵽����  InputAttachmentIndex������input attachment,�����ֵ��Ӧһ��VK_ATTACHMENT_UNUSED��������depth attachment����Ϊinput attachmentʹ�� 
		/*
		VkRenderingInputAttachmentIndexInfoKHR��Ч�÷�:
		1.���dynamicRenderingLocalRead ����û�п�������1�����pColorAttachmentInputIndices��ΪNULL��������ÿ��Ԫ�ز�������ΪVK_ATTACHMENT_UNUSED
													    ��2��pDepthInputAttachmentIndex��pStencilInputAttachmentIndex����Ϊһ��ֵΪVK_ATTACHMENT_UNUSED �ĵ�ַ
		2.pColorAttachmentInputIndices��ֵ��ΪVK_ATTACHMENT_UNUSED��Ԫ����ֵ������Ψһ�ģ��Ҳ��ܺ�pDepthInputAttachmentIndex�Լ�pStencilInputAttachmentIndex��ָ��ֵ��ͬ
		3.colorAttachmentCount ����С�ڵ���maxColorAttachments
		*/
		
		
		//��� dynamicRenderingLocalRead ���Կ�����InputAttachmentIndex��VkRenderingInfo::pInputAttachments��ӳ����Զ�ָ̬��
		vkCmdSetRenderingInputAttachmentIndicesKHR(VkCommandBuffer{/*��������һ����Ч��VkCommandBuffer*/ }, & renderingInputAttachmentIndexInfoKHR);
		/*
		vkCmdSetRenderingInputAttachmentIndicesKHR��Ч�÷�:
		1.dynamicRenderingLocalRead ���뿪��
		2.pInputAttachmentIndexInfo->colorAttachmentCount ������ڿ�ʼ��ǰrender passʵ����VkRenderingInfo::colorAttachmentCount
		3.��ǰ��render passʵ�������Ѿ�ͨ����commandBuffer��vkCmdBeginRendering���ÿ�ʼ����ʹ����

		*/

	}


	//Ray Tracing Pipeline Interface �μ�p1408


	//Shader Resource Interface �μ�p1409
	{
		//��shader�з��� buffer ���� image resourcesʱ,��shader�п��Է��ʵ���Uniform, UniformConstant,StorageBuffer, ���� PushConstant������shader �������shader resource interface����interface���ٷ�Ϊ push constant interface �Լ� descriptor set interface.����fragment shader������fragment input attachment interface
	
		// Push Constant Interface ��PushConstant���� �μ�p1409
	
		//Descriptor Set Interface
		{
			//��StorageBuffer, Uniform ���� UniformConstant�������� DescriptorSet �Լ� Binding���Σ���ӦVkDescriptorSetLayout�е����ݣ� �μ�p1410������fragment shader������fragment input attachment interface
			//��Щ������ʹ�����Ƽ�p1410 - p1414
		}

		// DescriptorSet and Binding Assignment  To do
	}


}


NS_TEST_END