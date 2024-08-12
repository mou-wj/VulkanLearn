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
	// Vertex Attributes �μ�p2582 
	{
		/*
		������������
		�������Ժ�vertex shader��������������
		
		����input variable��vertex shader���ԴӰ󶨵�һ������buffer�л�ȡ�����������ݡ�

		�����������ԺͶ������������������ʽ��Ϣ������������δӻ������ڴ�����ȡ���ݲ�ת��Ϊ������ɫ���������ĸ�ʽ�����������Լ�������: VkPhysicalDeviceLimits::maxVertexInputAttributes, VkPhysicalDeviceLimits::maxVertexInputBindings
		
		���磬��GLSL��
		// Assign location M to variableName
		layout (location=M, component=2) in vec2 variableName;
		// Assign locations [N,N+L) to the array elements of variableNameArray
		layout (location=N) in vec4 variableNameArray[L];

		SPIR-Vʵ����p2582

		*/


		//Attribute Location �Լ� Component Assignment  �μ�p2582
		{
			/*
			Locationָ��shader �������ʹ����һ�� vertex input attribute����vertex input attribute�д��ĸ�������ʼ��ȡ������Componentָ��
			
			������ �����p2582��  ��Input attribute components accessed by 16-bit and 32-bit input variables
			
			����� �����p2584�� ��Input attributes accessed by 32-bit input matrix variables    ������ÿһ��ռ��һ��Location����Щ��֮���Location����
			
			�����������Ϊ64-bit��  �����p2585  ��Input attribute locations and components accessed by 64-bit input variables

			*/
		}



		//Vertex Input Description �μ�p2586
		{
			/*
			Ӧ��ָ������������Ϣ�Լ�����Ϣͨ�����õ�VkGraphicsPipelineCreateInfo::pVertexInputState��VkPipelineVertexInputStateCreateInfoָ����ָ�����������VK_DYNAMIC_STATE_VERTEX_INPUT_EXT����ͨ������ vkCmdSetVertexInputEXT��ָ̬��
			*/

			VkPipelineVertexInputStateCreateInfo pipelineVertexInputStateCreateInfo{};
			pipelineVertexInputStateCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
			//
			VkPipelineVertexInputDivisorStateCreateInfoKHR pipelineVertexInputDivisorStateCreateInfoKHR{};
			{
				pipelineVertexInputDivisorStateCreateInfoKHR.sType = VK_STRUCTURE_TYPE_MAX_ENUM;//û�ж������Զ���ɷǷ�ֵ
				pipelineVertexInputDivisorStateCreateInfoKHR.pNext = nullptr;
				pipelineVertexInputDivisorStateCreateInfoKHR.vertexBindingDivisorCount = 1;
				VkVertexInputBindingDivisorDescriptionKHR vertexInputBindingDivisorDescriptionKHR{};
				{
					vertexInputBindingDivisorDescriptionKHR.binding = 0;
					vertexInputBindingDivisorDescriptionKHR.divisor = 2;
				}
				pipelineVertexInputDivisorStateCreateInfoKHR.pVertexBindingDivisors = &vertexInputBindingDivisorDescriptionKHR;
			}
			pipelineVertexInputStateCreateInfo.pNext = nullptr;//���԰���һ��VkPipelineVertexInputDivisorStateCreateInfoKHR
			pipelineVertexInputStateCreateInfo.flags = 0;//����δ��ʹ��
			pipelineVertexInputStateCreateInfo.vertexAttributeDescriptionCount = 1;//pVertexAttributeDescriptions�� vertex binding descriptions������
			VkVertexInputAttributeDescription vertexInputAttributeDescription{};	
			{
				vertexInputAttributeDescription.format = VK_FORMAT_R32G32_SINT;// ��vertex attribute���ݵ������Լ���С����
				vertexInputAttributeDescription.location = 0;//��shader��input������Ӧ��attribute��location���
				vertexInputAttributeDescription.binding = 0;//ָ��binding�ı�ţ��ñ��ָ��ʹ�ð󶨵��ĸ�binding�ϵĶ��㻺��������
				vertexInputAttributeDescription.offset = 0;//�Ǹ�attribute����ڰ󶨵Ķ������������л���һ��Ԫ�صĿ�ͷ���ڲ��ֽ�ƫ������
				/*
				VkVertexInputAttributeDescription��Ч�÷�:
				1.location����С��VkPhysicalDeviceLimits::maxVertexInputAttributes
				2.binding����С��VkPhysicalDeviceLimits::maxVertexInputBindings
				3.offset����С�ڵ���VkPhysicalDeviceLimits::maxVertexInputAttributeOffset
				4.format��format features�������VK_FORMAT_FEATURE_VERTEX_BUFFER_BIT
				5.���VK_KHR_portability_subset ��չ��������VkPhysicalDevicePortabilitySubsetFeaturesKHR::vertexAttributeAccessBeyondStrideΪVK_FALSE����offset ����format������vertex attribute ���ݵĴ�С
							����С�ڵ���binding��Ӧ��VkVertexInputBindingDescription�е�stride		
				*/
			}
			pipelineVertexInputStateCreateInfo.pVertexAttributeDescriptions = &vertexInputAttributeDescription;//һ�� VkVertexInputBindingDescription����ָ��
			pipelineVertexInputStateCreateInfo.vertexBindingDescriptionCount = 1;//pVertexBindingDescriptions�� vertex binding description������
			VkVertexInputBindingDescription vertexInputBindingDescription{};
			{
				vertexInputBindingDescription.binding = 0;//ָ��binding�ı��
				vertexInputBindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;//��һ��VkVertexInputRateֵָ���Ƿ�vertex attribute��ַ�Ƕ�������������instance�����ĺ���
				/*
				VkVertexInputRate:
				VK_VERTEX_INPUT_RATE_VERTEX:  ָ��vertex arribute��ַ�Ƕ��������ĺ���
				VK_VERTEX_INPUT_RATE_INSTANCE:   ָ��vertex arribute��ַ��instance�����ĺ���				
				*/
				vertexInputBindingDescription.stride = 3;//ָ��buffer����������Ԫ��֮����ֽڲ���
				/*
				VkVertexInputBindingDescription��Ч�÷�:
				1.binding����С��VkPhysicalDeviceLimits::maxVertexInputBindings
				2.stride����С�ڵ���VkPhysicalDeviceLimits::maxVertexInputBindingStride
				3.���VK_KHR_portability_subset ��չ��������stride����������VkPhysicalDevicePortabilitySubsetPropertiesKHR::minVertexInputBindingStrideAlignment�ı���

				*/
			}
			pipelineVertexInputStateCreateInfo.pVertexBindingDescriptions = &vertexInputBindingDescription;//һ��VkVertexInputBindingDescription����ָ��
			/*
			VkPipelineVertexInputStateCreateInfo��Ч�÷�:
			1.vertexBindingDescriptionCount����С�ڵ���VkPhysicalDeviceLimits::maxVertexInputBindings
			2.vertexAttributeDescriptionCount����С�ڵ���VkPhysicalDeviceLimits::maxVertexInputAttributes
			3.��pVertexAttributeDescriptions��ÿ��binding��������pVertexBindingDescriptions����һ��VkVertexInputBindingDescription��bingding��֮��Ӧ
			4.pVertexBindingDescriptions������Ԫ�ر���������ͬ��binding
			5.pVertexAttributeDescriptions������Ԫ�ر���������ͬ�� attribute locations
			
			*/
		
		}
	}


}


NS_TEST_END