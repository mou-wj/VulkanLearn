#include "CommandBufferTest.h"

NS_TEST_BEGIN
#define NV 1
namespace EnableFeature {
	static bool inheritedConditionalRendering;
	static bool multiview;
};


struct SecondCommandBufferInheritanceEXT//次级命令的VkCommandBufferInheritanceInfo的pnext中可以有的结构体
{
#ifdef AMD
	VkAttachmentSampleCountInfoAMD attachmentSampleCountAMD{};
#endif // !AMD


	VkCommandBufferInheritanceConditionalRenderingInfoEXT conditionalRenderingInfo;//如何使用条件渲染
	VkCommandBufferInheritanceRenderPassTransformInfoQCOM renderPassTransformInfoQCOM;
	VkCommandBufferInheritanceRenderingInfo renderingInfo;
#ifdef NV
	VkCommandBufferInheritanceViewportScissorInfoNV viewportScissorInfoNV{};
	VkAttachmentSampleCountInfoNV attachmentSampleCountNV{};//用来指定附件多重采样的采样点数量
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



struct Submit2Ext {//VkSubmitInfo2的pnext中可以有的结构体
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


struct SubmitExt//VkSubmitInfo的pnext中可以有的结构体
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


//commandbuffer有四种状态，invalid，recording，executable，pending，开始时状态为invalid，开始记录命令后状态变为recording，结束后变为executable，提交到queue后变为pending，记录
//完后可以重置commandbuffer，将状态变为recording，也可以将commandbuffer的内存还给pool，将状态变为invalid，提交到queue后变为pending

void CommandBufferTest::run()
{
	VkCommandPoolCreateInfo poolInfo{};
	poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
	poolInfo.queueFamilyIndex = queueFamilyIndex;
	poolInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;//每次执行后的commandbuffer都会回到invalid初始状态
	poolInfo.pNext = nullptr;
	auto res = vkCreateCommandPool(device, &poolInfo, nullptr, &commandPool);
	if (res != VK_SUCCESS) {
		THROW_ERROR
	}

	//回收commandBufferPool中没有用到的内存
	vkTrimCommandPool(device, commandPool, 0);

	//重置commandPool，将所有分配的commandbuffer的资源回收到pool， VK_COMMAND_POOL_RESET_RELEASE_RESOURCES_BIT指将内存还给系统
	vkResetCommandPool(device, commandPool, VkCommandPoolResetFlagBits::VK_COMMAND_POOL_RESET_RELEASE_RESOURCES_BIT);


	//分配2个commandBuffer，一个主要的一个次要的
	VkCommandBufferAllocateInfo allocInfo{};
	allocInfo.pNext = nullptr;
	allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
	allocInfo.commandBufferCount = 1;
	allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;//分配一个主要的commandBuffer
	allocInfo.commandPool = commandPool;

	commandBuffers.resize(2,nullptr);
	vkAllocateCommandBuffers(device, &allocInfo, &commandBuffers[0]);

	allocInfo.level = VK_COMMAND_BUFFER_LEVEL_SECONDARY;//分配一个次要的commandBuffer
	vkAllocateCommandBuffers(device, &allocInfo, &commandBuffers[1]);

	vkResetCommandBuffer(commandBuffers[0], VkCommandBufferResetFlagBits::VK_COMMAND_BUFFER_RESET_RELEASE_RESOURCES_BIT);//重置commandBuffer，将内存还给commandPool,并让状态
	//回到invalid状态,如果flags为0，则comamndbuffer继续持有资源

	vkFreeCommandBuffers(device, commandPool, commandBuffers.size(), commandBuffers.data());//将commandBuffer的内存还给commandPool

	//重新分配commandbuffer----------------------
	vkAllocateCommandBuffers(device, &allocInfo, &commandBuffers[0]);
	allocInfo.level = VK_COMMAND_BUFFER_LEVEL_SECONDARY;//分配一个次要的commandBuffer
	vkAllocateCommandBuffers(device, &allocInfo, &commandBuffers[1]);
	//-----------------------------------------------



	//命令记录
	{
		//记录主要的commandbuffer
		VkCommandBufferBeginInfo beginInfo{};
		beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
		beginInfo.pInheritanceInfo = nullptr;//这个结构体只有在commandbuffer是次级的commandbuffer的时候才有效
		beginInfo.pNext = nullptr;
		beginInfo.flags = VkCommandBufferUsageFlagBits::VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;



		VK_API_WRAPPER(vkBeginCommandBuffer(commandBuffers[0], &beginInfo));
	
		VK_API_WRAPPER(vkEndCommandBuffer(commandBuffers[0]));
	}

	{
		VkCommandBufferBeginInfo beginInfo{};
		beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
		beginInfo.flags = VkCommandBufferUsageFlagBits::VK_COMMAND_BUFFER_USAGE_RENDER_PASS_CONTINUE_BIT;//VK_COMMAND_BUFFER_USAGE_RENDER_PASS_CONTINUE_BIT这个标志位次级commandbuffer使用时只能在nestedCommandBufferRendering特性开启才能使用，
		//且VK_COMMAND_BUFFER_USAGE_RENDER_PASS_CONTINUE_BIT指的是该command buffer应该在以vkCmdBeginRenderPass开始的render pass中执行，否则会报错，VK_COMMAND_BUFFER_USAGE_SIMULTANEOUS_USE_BIT次级commandbuffer
		//使用时只能在nestedCommandBufferSimultaneousUse特性开启时才能使用 -------  （这段描述需要后续再确认一下）
		{
			//可选项
			VkDeviceGroupCommandBufferBeginInfo deviceGroupCommandBufferBeginInfo{};//可添加在VkCommandBufferBeginInfo结构体的pNext字段中
			deviceGroupCommandBufferBeginInfo.sType = VK_STRUCTURE_TYPE_DEVICE_GROUP_COMMAND_BUFFER_BEGIN_INFO;
			deviceGroupCommandBufferBeginInfo.pNext = nullptr;
			deviceGroupCommandBufferBeginInfo.deviceMask = 0;
		
		}


		VkCommandBufferInheritanceInfo inheritanceInfo{};
		beginInfo.pInheritanceInfo = &inheritanceInfo;


		inheritanceInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_INHERITANCE_INFO;

		//如果该次级commandbuffer没有在一个renderpass里面，或者在vkCmdBeginRendering里，那么这个次级commandbuffer的beginInfo里面的renderPass，subpass和framebuffer都会被忽略，
		//否则都应该是有效的句柄
		inheritanceInfo.renderPass = nullptr;//和VkCommandBufferUsageFlagBits::VK_COMMAND_BUFFER_USAGE_RENDER_PASS_CONTINUE_BIT一起使用，表示继承一个renderpass,如果dynamicRendering没有开启，这个renderPass就不能为nullptr，如果为空需要如下操作
		
		inheritanceInfo.subpass = 0;//如果renderpass不是nullptr，这个需要是有效的subpassID
		inheritanceInfo.framebuffer = nullptr;////nullptr或者一个具体的framebuffer句柄
		
		inheritanceInfo.occlusionQueryEnable = VK_FALSE;//是否开启遮挡查询，目前不清楚具体作用，待定
		inheritanceInfo.queryFlags = 0;//和遮挡查询相关的标志位,如果设置 VK_QUERY_CONTROL_PRECISE_BIT则查询会返回精确的采样值（待定）
		inheritanceInfo.pipelineStatistics = 0;//和遮挡查询相关的管线标志信息，用来指明该次级commandbuffer所在的
		//primary commandbuffer的某个管线的采样信息从哪个管线阶段进行查询
		inheritanceInfo.pNext = nullptr;//预留参数，目前不清楚具体作用，待定

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
		// transform 和 renderArea 必须和render pass instance中的 transform and renderArea 保持一致
		renderPassTransformInfoQCOM.transform = VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR;//屏幕变换，比如旋转90度
		renderPassTransformInfoQCOM.renderArea = VkRect2D{ 0,0,512,512 };//测试的renderArea

		//renderingInfo

		if (beginInfo.flags & VkCommandBufferUsageFlagBits::VK_COMMAND_BUFFER_USAGE_RENDER_PASS_CONTINUE_BIT && inheritanceInfo.renderPass == nullptr)
		{

			//如果是nullptr需要在inheritance的pnext中加上这个结构体

			auto& inheritanceRenderingInfo = secondInheritanceInfo.renderingInfo;
			//VkCommandBufferInheritanceRenderingInfo inheritanceRenderingInfo{};
			inheritanceRenderingInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_INHERITANCE_RENDERING_INFO;
			inheritanceRenderingInfo.colorAttachmentCount = 1;//如果inheritanceInfo的pnext里面有如VkAttachmentSampleCountInfoNV
			//则这里的colorAttachmentCount和VkAttachmentSampleCountInfoNV的colorAttachmentCount要一致
			inheritanceRenderingInfo.depthAttachmentFormat = VK_FORMAT_D32_SFLOAT;//深度附件的格式,如果是VK_FORMAT_UNDIFIED说明这个附件没有被使用，任何
			//写操作都会被丢弃
			inheritanceRenderingInfo.stencilAttachmentFormat = VK_FORMAT_UNDEFINED;//模板附件的格式,,如果是VK_FORMAT_UNDIFIED说明这个附件没有被使用，任何
			//写操作都会被丢弃,如果stencilAttachmentFormat和depthAttachmentFormat都不是VK_FORMAT_UNDIFIED,则这两个参数必须是相同的
			std::vector<VkFormat> colorFormats;
			//填充colorFormats
			inheritanceRenderingInfo.pColorAttachmentFormats = colorFormats.data();//颜色附件的格式,如果是VK_FORMAT_UNDIFIED说明这个附件没有被使用，任何
			//写操作都会被丢弃
			inheritanceRenderingInfo.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;//如果colorAttachmentCount不为0，则rasterizationSamples必须是一个合法的参数
			if (!EnableFeature::multiview)
			{
				inheritanceRenderingInfo.viewMask = 0;//如果没有开启multiview，这个参数必须为0
			}
			else {
				inheritanceRenderingInfo.viewMask = 1;//如果开启multiview，这个参数必须为小于 maxMultiviewViewCount，这里设为1作为测试
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
		{//在此条件下会开启，否则会忽略这个结构体中的参数，这个结构体也可以包含在VkGraphicsPipelineCreateInfo的pNext中，这里不再
			//描述，具体看文档p249
			auto& attachmentSampleCountNV = secondInheritanceInfo.attachmentSampleCountNV;

			attachmentSampleCountNV.depthStencilAttachmentSamples = VK_SAMPLE_COUNT_1_BIT;
			std::vector<VkSampleCountFlagBits> colorSamples;//填充colorSamples
			attachmentSampleCountNV.colorAttachmentCount = colorSamples.size();
			attachmentSampleCountNV.pColorAttachmentSamples = colorSamples.data();
		}




		VK_STRCUTURE_LINK(inheritanceInfo, secondInheritanceInfo.conditionalRenderingInfo);
		VK_API_WRAPPER(vkBeginCommandBuffer(commandBuffers[1], &beginInfo));



		VK_API_WRAPPER(vkEndCommandBuffer(commandBuffers[1]));
	}


	//提交 
	VkFence submitFence;

	//VkSubmitInfo2以及vkQueueSubmit2
	VkSubmitInfo2 submitInfo2{};
	submitInfo2.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO_2;
	submitInfo2.flags = 0;//如果提交的全是protected的comamndbuffer，这里需要设置,且提交的queue必须是protected的queue，如果含VK_SUBMIT_PROTECTED_BIT，那么本次提交的所有comamndbuffer都是protected的
	//反之如果没有设置，那么本次提交的所有comamndbuffer则不一定都是unprotected的
	//wait semaphore
	VkSemaphore waitSemaphores;//waitSemaphore
	VkSemaphoreSubmitInfoKHR waitSemaphoreSubmitInfo{};//VkSemaphoreSubmitInfoKHR也是VkSemaphoreSubmitInfo
	waitSemaphoreSubmitInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_SUBMIT_INFO_KHR;
	waitSemaphoreSubmitInfo.deviceIndex = 0;//指的是在device group中执行等待信号量的device的index
	waitSemaphoreSubmitInfo.semaphore = waitSemaphores;
	waitSemaphoreSubmitInfo.stageMask = VK_PIPELINE_STAGE_2_ALL_COMMANDS_BIT_KHR;//等待的管线阶段，有些阶段是否支持要看是否开启了对应的特性feature
	waitSemaphoreSubmitInfo.pNext = nullptr;//必须为nullptr
	waitSemaphoreSubmitInfo.value = 1000;//如果是timeline的semaphore，这里指明等待时间
	//这个值和其他这个信号量的等待或者触发操作value值之差也不能大于maxTimelineSemaphoreValueDifference

	submitInfo2.waitSemaphoreInfoCount = 1;
	submitInfo2.pWaitSemaphoreInfos = &waitSemaphoreSubmitInfo;

	//signal semaphore
	VkSemaphore sigSemaphore;//填充sigSemaphores
	VkSemaphoreSubmitInfo sigSemaphoreSubmitInfo{};
	sigSemaphoreSubmitInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_SUBMIT_INFO_KHR;
	sigSemaphoreSubmitInfo.deviceIndex = 0;//指的是在device group中执行触发信号量的device的index
	sigSemaphoreSubmitInfo.semaphore = waitSemaphores;
	sigSemaphoreSubmitInfo.stageMask = VK_PIPELINE_STAGE_2_ALL_COMMANDS_BIT_KHR;//触发信号量的管线阶段，有些阶段是否支持要看是否开启了对应的特性feature
	sigSemaphoreSubmitInfo.pNext = nullptr;//必须为nullptr
	sigSemaphoreSubmitInfo.value = 1000;//如果是timeline的semaphore，这里指明触发时的值，如果这个semaphore也在waitSemaphoreInfo中指定，那value的值必须大于waitSemaphoreInfo中指定的值，两者的差不能大于maxTimelineSemaphoreValueDifference
	//同样这个值和其他这个信号量的等待或者触发操作value值之差也不能大于maxTimelineSemaphoreValueDifference

	submitInfo2.signalSemaphoreInfoCount = 1;
	submitInfo2.pSignalSemaphoreInfos = &sigSemaphoreSubmitInfo;

	//command info
	VkCommandBufferSubmitInfoKHR commandBufferInfo2{};
	commandBufferInfo2.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_SUBMIT_INFO_KHR;
	commandBufferInfo2.deviceMask = 0;//是一个位掩码，指示设备组中的哪些设备执行该命令缓冲区。设备掩码为0，相当于将组中有效设备对应的所有位设置为1。
	commandBufferInfo2.pNext = nullptr;//pnext可以包含一个指向VkRenderPassStripeSubmitInfoARM结构的指针，该结构用于指定渲染通道条带的信息,暂时忽略。
	commandBufferInfo2.commandBuffer = commandBuffers[0];



	submitInfo2.commandBufferInfoCount = 1;
	submitInfo2.pCommandBufferInfos = &commandBufferInfo2;

	
	Submit2Ext submit2Ext{};
	submit2Ext.performanceQuerySubmitInfoKHR.counterPassIndex = 0;
	submitInfo2.pNext = &submit2Ext.performanceQuerySubmitInfoKHR;//将Submit2Ext中的结构体的链接到submit2Ext中

	vkQueueSubmit2(queues[0], 1, &submitInfo2, submitFence);

	//VkSubmitInfo和vkQueueSubmit
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
	VkPipelineStageFlags waitDstStageMask = VK_PIPELINE_STAGE_ALL_COMMANDS_BIT;// 如果synchronization2特性没有开启，则不能为0 ，且不能包含VK_PIPELINE_STAGE_HOST_BIT
	submitInfo.pWaitDstStageMask = &waitDstStageMask;

	SubmitExt submitExt{};
	submitInfo.pNext = nullptr;//如果pSignalSemaphores或者pWaitSemaphores中包含timeline semaphore,那么pNext中需要包含VkTimelineSemaphoreSubmitInfo
	submitInfo.pNext = &submitExt.amigoProfilingSubmitInfoSEC;//将SubmitExt中的结构体链接到sumitinfo中
	


	{//VkTimelineSemaphoreSubmitInfo示例代码
		auto& timelineSemaphoreSubmitInfo = submitExt.timelineSemaphoreSubmitInfo;
		timelineSemaphoreSubmitInfo.pNext = nullptr;
		timelineSemaphoreSubmitInfo.sType = VK_STRUCTURE_TYPE_TIMELINE_SEMAPHORE_SUBMIT_INFO;
		timelineSemaphoreSubmitInfo.waitSemaphoreValueCount = 1;//必须和submitInfo.waitSemaphoreCount相等
		uint64_t waitValue,sigValue;
		timelineSemaphoreSubmitInfo.pWaitSemaphoreValues = &waitValue;
		timelineSemaphoreSubmitInfo.signalSemaphoreValueCount = 1;//必须和submitInfo.signalSemaphoreCount相等
		timelineSemaphoreSubmitInfo.pSignalSemaphoreValues = &sigValue;//value值的限制和之前的信号量提交信息中的value值限制相同，该value和在该信号量上的等待和触发操作的value差值不能超过maxTimelineSemaphoreValueDifference
		//submitInfo.pNext = &timelineSemaphoreSubmitInfo;
		
	}

	{
	
		auto& protectedSubmitInfo = submitExt.protectedSubmitInfo;
		protectedSubmitInfo.sType = VK_STRUCTURE_TYPE_PROTECTED_SUBMIT_INFO;
		protectedSubmitInfo.pNext = nullptr;
		protectedSubmitInfo.protectedSubmit = true;//如果该值为true，则提交的comamndbuffer必须是protected的，否则提交的comamndbuffer是unprotected的
		
	
	}


	{
		auto& deviceGroupSubmitInfo = submitExt.deviceGroupSubmitInfo;
		deviceGroupSubmitInfo.commandBufferCount = 1;//需要和submitInfo的commandBufferCount相等
		uint32_t deviceMask = 1;
		deviceGroupSubmitInfo.pCommandBufferDeviceMasks = &deviceMask;//物理设备掩码，指明哪个物理设备执行该command buffer

		uint32_t sigDeviceIndex = 1;
		deviceGroupSubmitInfo.signalSemaphoreCount = 1;//需要和submitInfo的signalSemaphoreCount相等
		deviceGroupSubmitInfo.pSignalSemaphoreDeviceIndices = &sigDeviceIndex;//物理设备在设备组中的索引，指明由设备组哪个物理设备执行触发信号量操作

		uint32_t waitDeviceIndex = 1;
		deviceGroupSubmitInfo.waitSemaphoreCount = 1;//需要和submitInfo的waitSemaphoreCount相等
		deviceGroupSubmitInfo.pWaitSemaphoreDeviceIndices = &waitDeviceIndex;//物理设备在设备组中的索引，指明由设备组哪个物理设备执行等待信号量操作

	
	}


	{
		auto& performanceQuerySubmitInfoKHR = submit2Ext.performanceQuerySubmitInfoKHR;
		performanceQuerySubmitInfoKHR.counterPassIndex = 0;//counter的缩影，指明哪个counter pass（计数器）需要被执行
		//需要小于counter pass的数量，counter pass的数量可以通过vkGetPhysicalDeviceQueueFamilyPerformanceQueryPassesKHR获取
	}

	
	
	
	//执行一个次级命令
	//具体的限制查看vulkanspecification文档p279，简单说大部分合法的使用在强调上下文参数的匹配和兼容
	//xxxxx
	
	//commandBuffers[0]为主命令缓冲区，commandBuffers[1]为次级命令缓冲区，次级缓冲区的不能在其他处于excutable以及pending状态的缓冲区中使用，否则该主缓冲区的状态会变为invalid
	//如果 nestedCommandBuffer特性开启，可以在次级缓冲区中调用vkCmdExecuteCommands，否则不能调用
	vkCmdExecuteCommands(commandBuffers[0], 1, &commandBuffers[1]);

	//xxxxx


	//设备掩码devicemask
	//如果 VkCommandBufferBeginInfo 中包含 VkDeviceGroupCommandBufferBeginInfo，则这个结构体里面就包含一个初始的设备掩码
	//调用vkCmdSetDeviceMask可以修改当前commandbuffer的设备掩码
	vkCmdSetDeviceMask(commandBuffers[1], 1);//比如修改设备掩码为1




	vkQueueSubmit(queues[0], 1, &submitInfo, submitFence);


	vkDestroyCommandPool(device, commandPool, nullptr);

}

CommandBufferTest::~CommandBufferTest()
{
	ClearContex();

}



NS_TEST_END