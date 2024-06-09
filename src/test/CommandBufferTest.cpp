#include "CommandBufferTest.h"

NS_TEST_BEGIN
#define NV 1
namespace EnableFeature {
	static bool inheritedConditionalRendering;
	static bool multiview;
};


struct SecondCommandBufferInheritanceEXT//�μ������VkCommandBufferInheritanceInfo��pnext�п����еĽṹ��
{
#ifdef AMD
	VkAttachmentSampleCountInfoAMD attachmentSampleCountAMD{};
#endif // !AMD


	VkCommandBufferInheritanceConditionalRenderingInfoEXT conditionalRenderingInfo;//���ʹ��������Ⱦ
	VkCommandBufferInheritanceRenderPassTransformInfoQCOM renderPassTransformInfoQCOM;
	VkCommandBufferInheritanceRenderingInfo renderingInfo;
#ifdef NV
	VkCommandBufferInheritanceViewportScissorInfoNV viewportScissorInfoNV{};
	VkAttachmentSampleCountInfoNV attachmentSampleCountNV{};//����ָ���������ز����Ĳ���������
#endif // NV


	//VkExternalFormatANDROID externalFormatANDROID;
	VkMultiviewPerViewAttributesInfoNVX multiviewPerViewAttributesInfoNVX;
	//VkRenderingAttachmentLocationInfoKHR renderingAttachmentLocationInfoKHR;
	//VkRenderingInputAttachmentIndexInfoKHR renderingInputAttachmentIndexInfoKHR;

	SecondCommandBufferInheritanceEXT() {
		Init();
	}
	void Init() {
		conditionalRenderingInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_INHERITANCE_CONDITIONAL_RENDERING_INFO_EXT;
		conditionalRenderingInfo.pNext = &renderPassTransformInfoQCOM;		

		renderPassTransformInfoQCOM.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_INHERITANCE_RENDER_PASS_TRANSFORM_INFO_QCOM;;
		renderPassTransformInfoQCOM.pNext = &renderingInfo;



		renderingInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_INHERITANCE_RENDERING_INFO;
		renderingInfo.pNext = &viewportScissorInfoNV;
		
		viewportScissorInfoNV.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_INHERITANCE_VIEWPORT_SCISSOR_INFO_NV;
		

#ifdef NV
		viewportScissorInfoNV.pNext = &attachmentSampleCountNV;
		attachmentSampleCountNV.sType = VK_STRUCTURE_TYPE_ATTACHMENT_SAMPLE_COUNT_INFO_NV;
		attachmentSampleCountNV.pNext = &multiviewPerViewAttributesInfoNVX;
#else 
		viewportScissorInfoNV.pNext = &multiviewPerViewAttributesInfoNVX;
#endif // NV



		multiviewPerViewAttributesInfoNVX.sType = VK_STRUCTURE_TYPE_MULTIVIEW_PER_VIEW_ATTRIBUTES_INFO_NVX;;
		multiviewPerViewAttributesInfoNVX.pNext = nullptr;
	}

};



struct Submit2Ext {//VkSubmitInfo2��pnext�п����еĽṹ��
	//VkFrameBoundaryEXT frameBoundary{};
	//VkLatencySubmissionPresentIdNV latencySubmissionPresentIdNV{};
	VkPerformanceQuerySubmitInfoKHR performanceQuerySubmitInfoKHR{};
	//VkWin32KeyedMutexAcquireReleaseInfoKHR win32KeyedMutexAcquireReleaseInfoKHR{};
	//VkWin32KeyedMutexAcquireReleaseInfoNV win32KeyedMutexAcquireReleaseInfoNV{};

	Submit2Ext() {
		Init();
	}
	void Init() {
		performanceQuerySubmitInfoKHR.sType = VK_STRUCTURE_TYPE_PERFORMANCE_QUERY_SUBMIT_INFO_KHR;
		performanceQuerySubmitInfoKHR.pNext = nullptr;
	}
};


struct SubmitExt//VkSubmitInfo��pnext�п����еĽṹ��
{
	VkAmigoProfilingSubmitInfoSEC	amigoProfilingSubmitInfoSEC{};
	//VkD3D12FenceSubmitInfoKHR 
	VkDeviceGroupSubmitInfo deviceGroupSubmitInfo{};
	//VkFrameBoundaryEXT frameBoundary{};
	//VkLatencySubmissionPresentIdNV latencySubmissionPresentIdNV{};
	VkPerformanceQuerySubmitInfoKHR	performanceQuerySubmitInfoKHR{};
	VkProtectedSubmitInfo protectedSubmitInfo{};
	VkTimelineSemaphoreSubmitInfo timelineSemaphoreSubmitInfo{};
	//VkWin32KeyedMutexAcquireReleaseInfoKHR win32KeyedMutexAcquireReleaseInfoKHR{};
	//VkWin32KeyedMutexAcquireReleaseInfoNV	win32KeyedMutexAcquireReleaseInfoNV{};

	SubmitExt() {
		Init();
	}
	void Init() {
		amigoProfilingSubmitInfoSEC.sType = VK_STRUCTURE_TYPE_AMIGO_PROFILING_SUBMIT_INFO_SEC;
		amigoProfilingSubmitInfoSEC.pNext = &deviceGroupSubmitInfo;

		deviceGroupSubmitInfo.sType = VK_STRUCTURE_TYPE_DEVICE_GROUP_SUBMIT_INFO;
		deviceGroupSubmitInfo.pNext = &performanceQuerySubmitInfoKHR;

		performanceQuerySubmitInfoKHR.sType = VK_STRUCTURE_TYPE_PERFORMANCE_QUERY_SUBMIT_INFO_KHR;
		performanceQuerySubmitInfoKHR.pNext = &protectedSubmitInfo;

		protectedSubmitInfo.sType = VK_STRUCTURE_TYPE_PROTECTED_SUBMIT_INFO;
		protectedSubmitInfo.pNext = &timelineSemaphoreSubmitInfo;

		timelineSemaphoreSubmitInfo.sType = VK_STRUCTURE_TYPE_TIMELINE_SEMAPHORE_SUBMIT_INFO;
		timelineSemaphoreSubmitInfo.pNext = nullptr;

	}
};







CommandBufferTest::CommandBufferTest()
{
	PrepareContex();
}


//commandbuffer������״̬��invalid��recording��executable��pending����ʼʱ״̬Ϊinvalid����ʼ��¼�����״̬��Ϊrecording���������Ϊexecutable���ύ��queue���Ϊpending����¼
//����������commandbuffer����״̬��Ϊrecording��Ҳ���Խ�commandbuffer���ڴ滹��pool����״̬��Ϊinvalid���ύ��queue���Ϊpending

void CommandBufferTest::run()
{
	VkCommandPoolCreateInfo poolInfo{};
	poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
	poolInfo.queueFamilyIndex = queueFamilyIndex;
	poolInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;//ÿ��ִ�к��commandbuffer����ص�invalid��ʼ״̬
	poolInfo.pNext = nullptr;
	auto res = vkCreateCommandPool(device, &poolInfo, nullptr, &commandPool);
	if (res != VK_SUCCESS) {
		THROW_ERROR
	}

	//����commandBufferPool��û���õ����ڴ�
	vkTrimCommandPool(device, commandPool, 0);

	//����commandPool�������з����commandbuffer����Դ���յ�pool�� VK_COMMAND_POOL_RESET_RELEASE_RESOURCES_BITָ���ڴ滹��ϵͳ
	vkResetCommandPool(device, commandPool, VkCommandPoolResetFlagBits::VK_COMMAND_POOL_RESET_RELEASE_RESOURCES_BIT);


	//����2��commandBuffer��һ����Ҫ��һ����Ҫ��
	VkCommandBufferAllocateInfo allocInfo{};
	allocInfo.pNext = nullptr;
	allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
	allocInfo.commandBufferCount = 1;
	allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;//����һ����Ҫ��commandBuffer
	allocInfo.commandPool = commandPool;

	commandBuffers.resize(2,nullptr);
	vkAllocateCommandBuffers(device, &allocInfo, &commandBuffers[0]);

	allocInfo.level = VK_COMMAND_BUFFER_LEVEL_SECONDARY;//����һ����Ҫ��commandBuffer
	vkAllocateCommandBuffers(device, &allocInfo, &commandBuffers[1]);

	vkResetCommandBuffer(commandBuffers[0], VkCommandBufferResetFlagBits::VK_COMMAND_BUFFER_RESET_RELEASE_RESOURCES_BIT);//����commandBuffer�����ڴ滹��commandPool,����״̬
	//�ص�invalid״̬,���flagsΪ0����comamndbuffer����������Դ

	vkFreeCommandBuffers(device, commandPool, commandBuffers.size(), commandBuffers.data());//��commandBuffer���ڴ滹��commandPool

	//���·���commandbuffer----------------------
	vkAllocateCommandBuffers(device, &allocInfo, &commandBuffers[0]);
	allocInfo.level = VK_COMMAND_BUFFER_LEVEL_SECONDARY;//����һ����Ҫ��commandBuffer
	vkAllocateCommandBuffers(device, &allocInfo, &commandBuffers[1]);
	//-----------------------------------------------



	//�����¼
	{
		//��¼��Ҫ��commandbuffer
		VkCommandBufferBeginInfo beginInfo{};
		beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
		beginInfo.pInheritanceInfo = nullptr;//����ṹ��ֻ����commandbuffer�Ǵμ���commandbuffer��ʱ�����Ч
		beginInfo.pNext = nullptr;
		beginInfo.flags = VkCommandBufferUsageFlagBits::VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;



		VK_API_WRAPPER(vkBeginCommandBuffer(commandBuffers[0], &beginInfo));
	
		VK_API_WRAPPER(vkEndCommandBuffer(commandBuffers[0]));
	}

	{
		VkCommandBufferBeginInfo beginInfo{};
		beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
		beginInfo.flags = VkCommandBufferUsageFlagBits::VK_COMMAND_BUFFER_USAGE_RENDER_PASS_CONTINUE_BIT;//VK_COMMAND_BUFFER_USAGE_RENDER_PASS_CONTINUE_BIT�����־λ�μ�commandbufferʹ��ʱֻ����nestedCommandBufferRendering���Կ�������ʹ�ã�
		//��VK_COMMAND_BUFFER_USAGE_RENDER_PASS_CONTINUE_BITָ���Ǹ�command bufferӦ������vkCmdBeginRenderPass��ʼ��render pass��ִ�У�����ᱨ��VK_COMMAND_BUFFER_USAGE_SIMULTANEOUS_USE_BIT�μ�commandbuffer
		//ʹ��ʱֻ����nestedCommandBufferSimultaneousUse���Կ���ʱ����ʹ�� -------  �����������Ҫ������ȷ��һ�£�
		{
			//��ѡ��
			VkDeviceGroupCommandBufferBeginInfo deviceGroupCommandBufferBeginInfo{};//�������VkCommandBufferBeginInfo�ṹ���pNext�ֶ���
			deviceGroupCommandBufferBeginInfo.sType = VK_STRUCTURE_TYPE_DEVICE_GROUP_COMMAND_BUFFER_BEGIN_INFO;
			deviceGroupCommandBufferBeginInfo.pNext = nullptr;
			deviceGroupCommandBufferBeginInfo.deviceMask = 0;
		
		}


		VkCommandBufferInheritanceInfo inheritanceInfo{};
		beginInfo.pInheritanceInfo = &inheritanceInfo;


		inheritanceInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_INHERITANCE_INFO;

		//����ôμ�commandbufferû����һ��renderpass���棬������vkCmdBeginRendering���ô����μ�commandbuffer��beginInfo�����renderPass��subpass��framebuffer���ᱻ���ԣ�
		//����Ӧ������Ч�ľ��
		inheritanceInfo.renderPass = nullptr;//��VkCommandBufferUsageFlagBits::VK_COMMAND_BUFFER_USAGE_RENDER_PASS_CONTINUE_BITһ��ʹ�ã���ʾ�̳�һ��renderpass,���dynamicRenderingû�п��������renderPass�Ͳ���Ϊnullptr�����Ϊ����Ҫ���²���
		
		inheritanceInfo.subpass = 0;//���renderpass����nullptr�������Ҫ����Ч��subpassID
		inheritanceInfo.framebuffer = nullptr;////nullptr����һ�������framebuffer���
		
		inheritanceInfo.occlusionQueryEnable = VK_FALSE;//�Ƿ����ڵ���ѯ��Ŀǰ������������ã�����
		inheritanceInfo.queryFlags = 0;//���ڵ���ѯ��صı�־λ,������� VK_QUERY_CONTROL_PRECISE_BIT���ѯ�᷵�ؾ�ȷ�Ĳ���ֵ��������
		inheritanceInfo.pipelineStatistics = 0;//���ڵ���ѯ��صĹ��߱�־��Ϣ������ָ���ôμ�commandbuffer���ڵ�
		//primary commandbuffer��ĳ�����ߵĲ�����Ϣ���ĸ����߽׶ν��в�ѯ
		inheritanceInfo.pNext = nullptr;//Ԥ��������Ŀǰ������������ã�����

		SecondCommandBufferInheritanceEXT secondInheritanceInfo;
		inheritanceInfo.pNext = &secondInheritanceInfo.conditionalRenderingInfo;

		//conditionalRendering
		auto& conditionalRenderingInfo = secondInheritanceInfo.conditionalRenderingInfo;
		if (!EnableFeature::inheritedConditionalRendering)
		{
			conditionalRenderingInfo.conditionalRenderingEnable = VK_FALSE;
		}
		else {
			conditionalRenderingInfo.conditionalRenderingEnable = EnableFeature::inheritedConditionalRendering;
		}

		//renderPassTransformInfoQCOM
		auto& renderPassTransformInfoQCOM = secondInheritanceInfo.renderPassTransformInfoQCOM;
		// transform �� renderArea �����render pass instance�е� transform and renderArea ����һ��
		renderPassTransformInfoQCOM.transform = VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR;//��Ļ�任��������ת90��
		renderPassTransformInfoQCOM.renderArea = VkRect2D{ 0,0,512,512 };//���Ե�renderArea

		//renderingInfo

		if (beginInfo.flags & VkCommandBufferUsageFlagBits::VK_COMMAND_BUFFER_USAGE_RENDER_PASS_CONTINUE_BIT && inheritanceInfo.renderPass == nullptr)
		{

			//�����nullptr��Ҫ��inheritance��pnext�м�������ṹ��

			auto& inheritanceRenderingInfo = secondInheritanceInfo.renderingInfo;
			//VkCommandBufferInheritanceRenderingInfo inheritanceRenderingInfo{};
			inheritanceRenderingInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_INHERITANCE_RENDERING_INFO;
			inheritanceRenderingInfo.colorAttachmentCount = 1;//���inheritanceInfo��pnext��������VkAttachmentSampleCountInfoNV
			//�������colorAttachmentCount��VkAttachmentSampleCountInfoNV��colorAttachmentCountҪһ��
			inheritanceRenderingInfo.depthAttachmentFormat = VK_FORMAT_D32_SFLOAT;//��ȸ����ĸ�ʽ,�����VK_FORMAT_UNDIFIED˵���������û�б�ʹ�ã��κ�
			//д�������ᱻ����
			inheritanceRenderingInfo.stencilAttachmentFormat = VK_FORMAT_UNDEFINED;//ģ�帽���ĸ�ʽ,,�����VK_FORMAT_UNDIFIED˵���������û�б�ʹ�ã��κ�
			//д�������ᱻ����,���stencilAttachmentFormat��depthAttachmentFormat������VK_FORMAT_UNDIFIED,��������������������ͬ��
			std::vector<VkFormat> colorFormats;
			//���colorFormats
			inheritanceRenderingInfo.pColorAttachmentFormats = colorFormats.data();//��ɫ�����ĸ�ʽ,�����VK_FORMAT_UNDIFIED˵���������û�б�ʹ�ã��κ�
			//д�������ᱻ����
			inheritanceRenderingInfo.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;//���colorAttachmentCount��Ϊ0����rasterizationSamples������һ���Ϸ��Ĳ���
			if (!EnableFeature::multiview)
			{
				inheritanceRenderingInfo.viewMask = 0;//���û�п���multiview�������������Ϊ0
			}
			else {
				inheritanceRenderingInfo.viewMask = 1;//�������multiview�������������ΪС�� maxMultiviewViewCount��������Ϊ1��Ϊ����
			}
			//inheritanceInfo.pNext = &inheritanceRenderingInfo;

		}
		
		//viewportScissorInfoNV
		auto& viewportScissorInfoNV = secondInheritanceInfo.viewportScissorInfoNV;
		viewportScissorInfoNV.viewportScissor2D = VK_TRUE;
		std::vector<VkViewport> viewports;
		viewportScissorInfoNV.viewportDepthCount = viewports.size();
		viewportScissorInfoNV.pViewportDepths = viewports.data();

		//attachmentSampleCountNV
		if (beginInfo.flags & VkCommandBufferUsageFlagBits::VK_COMMAND_BUFFER_USAGE_RENDER_PASS_CONTINUE_BIT
			&& inheritanceInfo.renderPass == nullptr)
		{//�ڴ������»Ὺ����������������ṹ���еĲ���������ṹ��Ҳ���԰�����VkGraphicsPipelineCreateInfo��pNext�У����ﲻ��
			//���������忴�ĵ�p249
			auto& attachmentSampleCountNV = secondInheritanceInfo.attachmentSampleCountNV;

			attachmentSampleCountNV.depthStencilAttachmentSamples = VK_SAMPLE_COUNT_1_BIT;
			std::vector<VkSampleCountFlagBits> colorSamples;//���colorSamples
			attachmentSampleCountNV.colorAttachmentCount = colorSamples.size();
			attachmentSampleCountNV.pColorAttachmentSamples = colorSamples.data();
		}




		VK_STRCUTURE_LINK(inheritanceInfo, secondInheritanceInfo.conditionalRenderingInfo);
		VK_API_WRAPPER(vkBeginCommandBuffer(commandBuffers[1], &beginInfo));



		VK_API_WRAPPER(vkEndCommandBuffer(commandBuffers[1]));
	}


	//�ύ 
	VkFence submitFence;

	//VkSubmitInfo2�Լ�vkQueueSubmit2
	VkSubmitInfo2 submitInfo2{};
	submitInfo2.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO_2;
	submitInfo2.flags = 0;//����ύ��ȫ��protected��comamndbuffer��������Ҫ����,���ύ��queue������protected��queue�������VK_SUBMIT_PROTECTED_BIT����ô�����ύ������comamndbuffer����protected��
	//��֮���û�����ã���ô�����ύ������comamndbuffer��һ������unprotected��
	//wait semaphore
	VkSemaphore waitSemaphores;//waitSemaphore
	VkSemaphoreSubmitInfoKHR waitSemaphoreSubmitInfo{};//VkSemaphoreSubmitInfoKHRҲ��VkSemaphoreSubmitInfo
	waitSemaphoreSubmitInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_SUBMIT_INFO_KHR;
	waitSemaphoreSubmitInfo.deviceIndex = 0;//ָ������device group��ִ�еȴ��ź�����device��index
	waitSemaphoreSubmitInfo.semaphore = waitSemaphores;
	waitSemaphoreSubmitInfo.stageMask = VK_PIPELINE_STAGE_2_ALL_COMMANDS_BIT_KHR;//�ȴ��Ĺ��߽׶Σ���Щ�׶��Ƿ�֧��Ҫ���Ƿ����˶�Ӧ������feature
	waitSemaphoreSubmitInfo.pNext = nullptr;//����Ϊnullptr
	waitSemaphoreSubmitInfo.value = 1000;//�����timeline��semaphore������ָ���ȴ�ʱ��
	//���ֵ����������ź����ĵȴ����ߴ�������valueֵ֮��Ҳ���ܴ���maxTimelineSemaphoreValueDifference

	submitInfo2.waitSemaphoreInfoCount = 1;
	submitInfo2.pWaitSemaphoreInfos = &waitSemaphoreSubmitInfo;

	//signal semaphore
	VkSemaphore sigSemaphore;//���sigSemaphores
	VkSemaphoreSubmitInfo sigSemaphoreSubmitInfo{};
	sigSemaphoreSubmitInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_SUBMIT_INFO_KHR;
	sigSemaphoreSubmitInfo.deviceIndex = 0;//ָ������device group��ִ�д����ź�����device��index
	sigSemaphoreSubmitInfo.semaphore = waitSemaphores;
	sigSemaphoreSubmitInfo.stageMask = VK_PIPELINE_STAGE_2_ALL_COMMANDS_BIT_KHR;//�����ź����Ĺ��߽׶Σ���Щ�׶��Ƿ�֧��Ҫ���Ƿ����˶�Ӧ������feature
	sigSemaphoreSubmitInfo.pNext = nullptr;//����Ϊnullptr
	sigSemaphoreSubmitInfo.value = 1000;//�����timeline��semaphore������ָ������ʱ��ֵ��������semaphoreҲ��waitSemaphoreInfo��ָ������value��ֵ�������waitSemaphoreInfo��ָ����ֵ�����ߵĲ�ܴ���maxTimelineSemaphoreValueDifference
	//ͬ�����ֵ����������ź����ĵȴ����ߴ�������valueֵ֮��Ҳ���ܴ���maxTimelineSemaphoreValueDifference

	submitInfo2.signalSemaphoreInfoCount = 1;
	submitInfo2.pSignalSemaphoreInfos = &sigSemaphoreSubmitInfo;

	//command info
	VkCommandBufferSubmitInfoKHR commandBufferInfo2{};
	commandBufferInfo2.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_SUBMIT_INFO_KHR;
	commandBufferInfo2.deviceMask = 0;//��һ��λ���룬ָʾ�豸���е���Щ�豸ִ�и�����������豸����Ϊ0���൱�ڽ�������Ч�豸��Ӧ������λ����Ϊ1��
	commandBufferInfo2.pNext = nullptr;//pnext���԰���һ��ָ��VkRenderPassStripeSubmitInfoARM�ṹ��ָ�룬�ýṹ����ָ����Ⱦͨ����������Ϣ,��ʱ���ԡ�
	commandBufferInfo2.commandBuffer = commandBuffers[0];



	submitInfo2.commandBufferInfoCount = 1;
	submitInfo2.pCommandBufferInfos = &commandBufferInfo2;

	
	Submit2Ext submit2Ext{};
	submit2Ext.performanceQuerySubmitInfoKHR.counterPassIndex = 0;
	submitInfo2.pNext = &submit2Ext.performanceQuerySubmitInfoKHR;//��Submit2Ext�еĽṹ������ӵ�submit2Ext��

	vkQueueSubmit2(queues[0], 1, &submitInfo2, submitFence);

	//VkSubmitInfo��vkQueueSubmit
	VkSubmitInfo submitInfo{};
	submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;

	//command info
	submitInfo.commandBufferCount = 1;
	submitInfo.pCommandBuffers = &commandBuffers[0];
	//signal semaphore
	submitInfo.signalSemaphoreCount = 1;
	submitInfo.pSignalSemaphores = &sigSemaphore;
	//wait semaphore
	submitInfo.waitSemaphoreCount = 1;
	submitInfo.pWaitSemaphores = &waitSemaphores;
	VkPipelineStageFlags waitDstStageMask = VK_PIPELINE_STAGE_ALL_COMMANDS_BIT;// ���synchronization2����û�п���������Ϊ0 ���Ҳ��ܰ���VK_PIPELINE_STAGE_HOST_BIT
	submitInfo.pWaitDstStageMask = &waitDstStageMask;

	SubmitExt submitExt{};
	submitInfo.pNext = nullptr;//���pSignalSemaphores����pWaitSemaphores�а���timeline semaphore,��ôpNext����Ҫ����VkTimelineSemaphoreSubmitInfo
	submitInfo.pNext = &submitExt.amigoProfilingSubmitInfoSEC;//��SubmitExt�еĽṹ�����ӵ�sumitinfo��
	


	{//VkTimelineSemaphoreSubmitInfoʾ������
		auto& timelineSemaphoreSubmitInfo = submitExt.timelineSemaphoreSubmitInfo;
		timelineSemaphoreSubmitInfo.pNext = nullptr;
		timelineSemaphoreSubmitInfo.sType = VK_STRUCTURE_TYPE_TIMELINE_SEMAPHORE_SUBMIT_INFO;
		timelineSemaphoreSubmitInfo.waitSemaphoreValueCount = 1;//�����submitInfo.waitSemaphoreCount���
		uint64_t waitValue,sigValue;
		timelineSemaphoreSubmitInfo.pWaitSemaphoreValues = &waitValue;
		timelineSemaphoreSubmitInfo.signalSemaphoreValueCount = 1;//�����submitInfo.signalSemaphoreCount���
		timelineSemaphoreSubmitInfo.pSignalSemaphoreValues = &sigValue;//valueֵ�����ƺ�֮ǰ���ź����ύ��Ϣ�е�valueֵ������ͬ����value���ڸ��ź����ϵĵȴ��ʹ���������value��ֵ���ܳ���maxTimelineSemaphoreValueDifference
		//submitInfo.pNext = &timelineSemaphoreSubmitInfo;
		
	}

	{
	
		auto& protectedSubmitInfo = submitExt.protectedSubmitInfo;
		protectedSubmitInfo.sType = VK_STRUCTURE_TYPE_PROTECTED_SUBMIT_INFO;
		protectedSubmitInfo.pNext = nullptr;
		protectedSubmitInfo.protectedSubmit = true;//�����ֵΪtrue�����ύ��comamndbuffer������protected�ģ������ύ��comamndbuffer��unprotected��
		
	
	}


	{
		auto& deviceGroupSubmitInfo = submitExt.deviceGroupSubmitInfo;
		deviceGroupSubmitInfo.commandBufferCount = 1;//��Ҫ��submitInfo��commandBufferCount���
		uint32_t deviceMask = 1;
		deviceGroupSubmitInfo.pCommandBufferDeviceMasks = &deviceMask;//�����豸���룬ָ���ĸ������豸ִ�и�command buffer

		uint32_t sigDeviceIndex = 1;
		deviceGroupSubmitInfo.signalSemaphoreCount = 1;//��Ҫ��submitInfo��signalSemaphoreCount���
		deviceGroupSubmitInfo.pSignalSemaphoreDeviceIndices = &sigDeviceIndex;//�����豸���豸���е�������ָ�����豸���ĸ������豸ִ�д����ź�������

		uint32_t waitDeviceIndex = 1;
		deviceGroupSubmitInfo.waitSemaphoreCount = 1;//��Ҫ��submitInfo��waitSemaphoreCount���
		deviceGroupSubmitInfo.pWaitSemaphoreDeviceIndices = &waitDeviceIndex;//�����豸���豸���е�������ָ�����豸���ĸ������豸ִ�еȴ��ź�������

	
	}


	{
		auto& performanceQuerySubmitInfoKHR = submit2Ext.performanceQuerySubmitInfoKHR;
		performanceQuerySubmitInfoKHR.counterPassIndex = 0;//counter����Ӱ��ָ���ĸ�counter pass������������Ҫ��ִ��
		//��ҪС��counter pass��������counter pass����������ͨ��vkGetPhysicalDeviceQueueFamilyPerformanceQueryPassesKHR��ȡ
	}

	
	
	
	//ִ��һ���μ�����
	//��������Ʋ鿴vulkanspecification�ĵ�p279����˵�󲿷ֺϷ���ʹ����ǿ�������Ĳ�����ƥ��ͼ���
	//xxxxx
	
	//commandBuffers[0]Ϊ�����������commandBuffers[1]Ϊ�μ�����������μ��������Ĳ�������������excutable�Լ�pending״̬�Ļ�������ʹ�ã����������������״̬���Ϊinvalid
	//��� nestedCommandBuffer���Կ����������ڴμ��������е���vkCmdExecuteCommands�������ܵ���
	vkCmdExecuteCommands(commandBuffers[0], 1, &commandBuffers[1]);

	//xxxxx


	//�豸����devicemask
	//��� VkCommandBufferBeginInfo �а��� VkDeviceGroupCommandBufferBeginInfo��������ṹ������Ͱ���һ����ʼ���豸����
	//����vkCmdSetDeviceMask�����޸ĵ�ǰcommandbuffer���豸����
	vkCmdSetDeviceMask(commandBuffers[1], 1);//�����޸��豸����Ϊ1




	vkQueueSubmit(queues[0], 1, &submitInfo, submitFence);


	vkDestroyCommandPool(device, commandPool, nullptr);

}

CommandBufferTest::~CommandBufferTest()
{
	ClearContex();

}



NS_TEST_END