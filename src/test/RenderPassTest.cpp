#include "RenderPassTest.h"

NS_TEST_BEGIN


































RenderPassTest::RenderPassTest()
{

	PrepareContex();
}








































void RenderPassTest::run()
{

}

RenderPassTest::~RenderPassTest()
{
	ClearContex();
}
// Provided by VK_ARM_render_pass_striped
typedef struct VkRenderPassStripeInfoARM {
	VkStructureType sType;
	const void* pNext;
	VkRect2D stripeArea;//stripeArea指明当前render pass实例被影响的渲染区域，需要是render pass的renderArea的一部分，具体细节：
	/*
	stripeArea.offset.x以及stripeArea.extent.width必须是VkPhysicalDeviceRenderPassStripedPropertiesARM::renderPassStripeGranularity.width的倍数或者stripeArea.offset.x + stripeArea.extent.width要等于render pass实例的renderArea.extent.width
	stripeArea.offset.y以及stripeArea.extent.height必须是VkPhysicalDeviceRenderPassStripedPropertiesARM::renderPassStripeGranularity.width的倍数或者stripeArea.offset.y + stripeArea.extent.height要等于render pass实例的renderArea.extent.height
	
	*/
} VkRenderPassStripeInfoARM;
typedef struct VkRenderPassStripeBeginInfoARM {
	VkStructureType sType;
	const void* pNext;
	uint32_t stripeInfoCount;//该值必须小于 VkPhysicalDeviceRenderPassStripedPropertiesARM::maxRenderPassStripes
	const VkRenderPassStripeInfoARM* pStripeInfos;
} VkRenderPassStripeBeginInfoARM;//定义如何将render pass实例划分为strips
struct RenderInfoExt
{
	VkDeviceGroupRenderPassBeginInfo deviceGroupRenderPassBeginInfo{};
	VkMultisampledRenderToSingleSampledInfoEXT multisampledRenderToSingleSampledInfoEXT{};
	VkMultiviewPerViewAttributesInfoNVX multiviewPerViewAttributesInfoNVX{};
	VkMultiviewPerViewRenderAreasRenderPassBeginInfoQCOM MultiviewPerViewRenderAreasRenderPassBeginInfoQCOM{};

	VkRenderPassStripeBeginInfoARM renderPassStripeBeginInfoARM{};//当前vulkan版本没有找到该结构体的定义，先定义一个作为示例，且该结构体不会在初始话Init函数中进行初始化类型设置
	VkRenderingFragmentDensityMapAttachmentInfoEXT renderingFragmentDensityMapAttachmentInfoEXT{};

	VkRenderingFragmentShadingRateAttachmentInfoKHR renderingFragmentShadingRateAttachmentInfoKHR{};
	RenderInfoExt() {
		Init();
	}
	void Init() {
		deviceGroupRenderPassBeginInfo.sType = VK_STRUCTURE_TYPE_DEVICE_GROUP_RENDER_PASS_BEGIN_INFO_KHR;
		deviceGroupRenderPassBeginInfo.pNext = &multisampledRenderToSingleSampledInfoEXT;
		multisampledRenderToSingleSampledInfoEXT.sType = VK_STRUCTURE_TYPE_MULTISAMPLED_RENDER_TO_SINGLE_SAMPLED_INFO_EXT;
		multisampledRenderToSingleSampledInfoEXT.pNext = &multiviewPerViewAttributesInfoNVX;
		multiviewPerViewAttributesInfoNVX.sType = VK_STRUCTURE_TYPE_MULTIVIEW_PER_VIEW_ATTRIBUTES_INFO_NVX;
		multiviewPerViewAttributesInfoNVX.pNext = &MultiviewPerViewRenderAreasRenderPassBeginInfoQCOM;
		MultiviewPerViewRenderAreasRenderPassBeginInfoQCOM.sType = VK_STRUCTURE_TYPE_MULTIVIEW_PER_VIEW_RENDER_AREAS_RENDER_PASS_BEGIN_INFO_QCOM;
		MultiviewPerViewRenderAreasRenderPassBeginInfoQCOM.pNext = &renderingFragmentDensityMapAttachmentInfoEXT;
		renderingFragmentDensityMapAttachmentInfoEXT.sType = VK_STRUCTURE_TYPE_RENDERING_FRAGMENT_DENSITY_MAP_ATTACHMENT_INFO_EXT;
		renderingFragmentDensityMapAttachmentInfoEXT.pNext = &renderingFragmentShadingRateAttachmentInfoKHR;
		renderingFragmentShadingRateAttachmentInfoKHR.sType = VK_STRUCTURE_TYPE_RENDERING_FRAGMENT_SHADING_RATE_ATTACHMENT_INFO_KHR;
		renderingFragmentShadingRateAttachmentInfoKHR.pNext = nullptr;
	}

};

void RenderPassTest::RenderPassInstanceCommandTest()
{
	VkCommandBuffer cmdbuf;
	VkRenderingInfoKHR renderInfo;
	renderInfo.sType = VK_STRUCTURE_TYPE_RENDERING_INFO_KHR;

	vkCmdBeginRenderingKHR(cmdbuf, &renderInfo);
	/*
	合法用法：
	1. dynamicRendering特性需要开启
	2. nestedCommandBuffer特性未开启，pRenderingInfo->flags不能是VK_RENDERING_CONTENTS_SECONDARY_COMMAND_BUFFERS_BIT
	3. pRenderingInfo->pDepthAttachment不是NULL，pRenderingInfo->pDepthAttachment->imageView如果不是VK_NULL_HANDLE则该imageview的布局要和 pRenderingInfo->pDepthAttachment->imageLayout相同
	4. pRenderingInfo->pDepthAttachment不是NULL,pRenderingInfo->pDepthAttachment->imageView如果不是VK_NULL_HANDLE,且 pRenderingInfo->pDepthAttachment->imageResolveMode不是VK_RESOLVE_MODE_NONE，
	且pRenderingInfo->pDepthAttachment->resolveImageView不是VK_NULL_HANDLE，则pRenderingInfo->pDepthAttachment->resolveImageView布局需要和 pRenderingInfo->pDepthAttachment->resolveImageLayout相同
	5. pRenderingInfo->pStencilAttachment不是NULL,且pRenderingInfo->pStencilAttachment->imageView不是VK_NULL_HANDLE，pRenderingInfo->pStencilAttachment->imageView必须和
	pRenderingInfo->pStencilAttachment->imageLayout布局相同
	6. pRenderingInfo->pStencilAttachment不是NULL,pRenderingInfo->pStencilAttachment->imageView如果不是VK_NULL_HANDLE,且 pRenderingInfo->pStencilAttachment->imageResolveMode不是VK_RESOLVE_MODE_NONE，
	且pRenderingInfo->pStencilAttachment->resolveImageView不是VK_NULL_HANDLE，则pRenderingInfo->pStencilAttachment->resolveImageView布局需要和 pRenderingInfo->pStencilAttachment->resolveImageLayout相同
	7. 任何pRenderingInfo->pColorAttachments中的imageView如果不是VK_NULL_HANDLE，则imageView的布局需要和imageLayout相同
	8. 任何pRenderingInfo->pColorAttachments中的imageView如果imageResolveMode是VK_RESOLVE_MODE_EXTERNAL_FORMAT_DOWNSAMPLE_ANDROID,或者imageView不是VK_NULL_HANDLE且imageResolveMode不是 VK_RESOLVE_MODE_NONE以及
	resolveImageView不是VK_NULL_HANDLE，resolveImageView必须和resolveImageLayout布局相同

	*/


	VkRenderingInfoKHR& refRenderInfo = renderInfo;
	refRenderInfo.sType = VK_STRUCTURE_TYPE_RENDERING_INFO_KHR;
	refRenderInfo.viewMask = 0;
	refRenderInfo.layerCount = 1;
	refRenderInfo.colorAttachmentCount = 0;
	refRenderInfo.pColorAttachments = VK_NULL_HANDLE;
	refRenderInfo.pDepthAttachment = VK_NULL_HANDLE;
	refRenderInfo.pStencilAttachment = VK_NULL_HANDLE;
	refRenderInfo.renderArea = VkRect2D{};
	//加入VkRenderingInfoKHR的可拓展的数据结构
	RenderInfoExt renderInfoExt;
	refRenderInfo.pNext = &renderInfoExt.deviceGroupRenderPassBeginInfo;
	//refRenderInfo.pNext = nullptr;
	refRenderInfo.flags = VK_RENDERING_SUSPENDING_BIT;/*
		VK_RENDERING_CONTENTS_SECONDARY_COMMAND_BUFFERS_BIT: 指定render pass实例将在辅助命令缓冲区中记录绘制调用的命令。如果启用了 nestedCommandBuffer 特性，则次级命令中的绘制调用可以调用 vkCmdExecuteCommands。
		VK_RENDERING_RESUMING_BIT: 指明当前的render pass 实例将使用之前挂起的render pass 实例
		VK_RENDERING_SUSPENDING_BIT: 指明将当前的render pass 挂起
		VK_RENDERING_ENABLE_LEGACY_DITHERING_BIT_EXT: 指明Legacy Dithering在当前render pass 实例开启
		VK_RENDERING_CONTENTS_INLINE_BIT_EXT: 指明当前render pass的绘制命令可以线性的记录在当前的命令缓冲区中，如果 nestedCommandBuffer特性开启则可以和VK_RENDERING_CONTENTS_SECONDARY_COMMAND_BUFFERS_BIT连用用来在
		次级命令缓冲区中线性记录绘制命令

		note:resume render pass和suspend render pass的pRenderingInfo内容除了VK_RENDERING_RESUMING_BIT, VK_RENDERING_SUSPENDING_BIT, 以及VK_RENDERING_CONTENTS_SECONDARY_COMMAND_BUFFERS_BIT外需要匹配，且在两者之前
		不能有其他的动作，同步命令或者render pass实例
	*/


	/*
	VkRenderingInfoKHR合法用法：（无特殊说明以下和VkRenderingInfoKHR成员同名的变量即为VkRenderingInfoKHR的成员）
	1. 如果viewMask为0,则layerCount不能是0
	2. 如果VK_AMD_mixed_attachment_samples或VK_NV_framebuffer_mixed_samples拓展未开，或者 multisampledRenderToSingleSampled特性未开启，则
	pDepthAttachment, pStencilAttachment, 以及pColorAttachments中的不为VK_NULL_HANDLE的imageView的sampleCount必须相同
	3. 如果multisampledRenderToSingleSampled特性未开启，则pColorAttachments中的不为VK_NULL_HANDLE的imageView的sampleCount必须相同
	4. 如果VkDeviceGroupRenderPassBeginInfo::deviceRenderAreaCount是0，则renderArea.extent.width以及renderArea.extent.height必须大于0
	5. 如果multisampled-render-to-single-sampled开启，则pDepthAttachment, pStencilAttachment, 以及pColorAttachments中的不为VK_NULL_HANDLE的imageView的sampleCount必须
	是VK_SAMPLE_COUNT_1_BIT 或者等于VkMultisampledRenderToSingleSampledInfoEXT::rasterizationSamples且如果是VK_SAMPLE_COUNT_1_BIT则在创建image时必须包含VK_IMAGE_CREATE_MULTISAMPLED_RENDER_TO_SINGLE_SAMPLED_BIT_EXT 在
	VkImageCreateInfo::flags中
	6. 如果pNext中不含VkDeviceGroupRenderPassBeginInfo或者deviceRenderAreaCount为0，则 renderArea.offset.x， renderArea.offset.y必须大于0，renderArea.offset.x + renderArea.extent.width 必须小于 maxFramebufferWidth，
	renderArea.offset.y + renderArea.extent.height 必须小于 maxFramebufferHeight，且pDepthAttachment, pStencilAttachment, 以及pColorAttachments中的不为VK_NULL_HANDLE的imageView的宽必须大于renderArea.offset.x + renderArea.extent.width，
	高必须大于renderArea.offset.y + renderArea.extent.height
	7. 如果pNext中含VkDeviceGroupRenderPassBeginInfo，则pDepthAttachment, pStencilAttachment, 以及pColorAttachments中的不为VK_NULL_HANDLE的imageView的宽必须大于pDeviceRenderAreas中的offset.x + extent.width，
	高必须大于pDeviceRenderAreas中的offset.y + extent.height
	8. 如果 pDepthAttachment 和 pStencilAttachment都不是NULL,且对应的imageView也不是VK_NULL_HANDLE，则两者的imageView必须相同，如果 两者的resolveMode也不是VK_RESOLVE_MODE_NONE，则两者的 resolveImageView也必须相同
	9. 如果colorAttachmentCount不是0，则pColorAttachments中的不为VK_NULL_HANDLE的imageView对应的image创建时必须包含VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT，如果pColorAttachments对应的 resolveMode设置为VK_RESOLVE_MODE_EXTERNAL_FORMAT_DOWNSAMPLE_ANDROID,
	或者pColorAttachments中的不为VK_NULL_HANDLE的imageView的resolveMode不是VK_RESOLVE_MODE_NONE,，则 pColorAttachments 中的 resolveImageView对应的image创建时也必须包含VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT
	10. 如果 pDepthAttachment 不是 NULL 且 pDepthAttachment->imageView 不是 VK_NULL_HANDLE,则 pDepthAttachment->imageView对应的image创建是的format中必须有深度组份，且必须含有VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT，如果pDepthAttachment->resolveMode 不是
	VK_RESOLVE_MODE_NONE,则 pDepthAttachment->resolveImageView对应的image创建时也必须含有VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT
	11. 如果 pStencilAttachment 不是 NULL 且 pStencilAttachment->imageView 不是 VK_NULL_HANDLE,则 pStencilAttachment->imageView对应的image创建是的format中必须有模板组份，且必须含有VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT，如果pStencilAttachment->resolveMode 不是
	VK_RESOLVE_MODE_NONE,则 pStencilAttachment->resolveImageView对应的image创建时也必须含有VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT
	12. 如果colorAttachmentCount不是0，则pColorAttachments中的不为VK_NULL_HANDLE的imageView以及如果对应的 resolveMode不是VK_RESOLVE_MODE_NONE，则imageView对应的imageLayout以及对应的
	 resolveImageLayout也不能是 VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL
								或者VK_IMAGE_LAYOUT_DEPTH_STENCIL_READ_ONLY_OPTIMAL，
								VK_IMAGE_LAYOUT_DEPTH_READ_ONLY_STENCIL_ATTACHMENT_OPTIMAL
								或者 VK_IMAGE_LAYOUT_DEPTH_ATTACHMENT_STENCIL_READ_ONLY_OPTIMAL，
								VK_IMAGE_LAYOUT_DEPTH_ATTACHMENT_OPTIMAL,
								VK_IMAGE_LAYOUT_DEPTH_READ_ONLY_OPTIMAL,
								VK_IMAGE_LAYOUT_STENCIL_ATTACHMENT_OPTIMAL, 或者
								VK_IMAGE_LAYOUT_STENCIL_READ_ONLY_OPTIMAL
	13. 如果pDepthAttachment 不是 NULL 且 pDepthAttachment->imageView 不是 VK_NULL_HANDLE，如果对应的resolveMode不是VK_RESOLVE_MODE_NONE，则pDepthAttachment->layout或者 resolveImageLayout不能是
																		VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL，
																		VK_IMAGE_LAYOUT_STENCIL_ATTACHMENT_OPTIMAL 或者
																		VK_IMAGE_LAYOUT_STENCIL_READ_ONLY_OPTIMAL

	同理如果pStencilAttachment 不是 NULL 且 pStencilAttachment->imageView 不是 VK_NULL_HANDLE，如果对应的resolveMode不是VK_RESOLVE_MODE_NONE，则pStencilAttachment->layout 或者resolveImageLayout也不能是
																		VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL，
																		VK_IMAGE_LAYOUT_DEPTH_ATTACHMENT_OPTIMAL 或者
																		VK_IMAGE_LAYOUT_DEPTH_READ_ONLY_OPTIMAL
	14. 如果pDepthAttachment 不是 NULL 且 pDepthAttachment->imageView 不是 VK_NULL_HANDLE,且对应的resolveMode不是VK_RESOLVE_MODE_NONE，则resolveImageLayout不能是VK_IMAGE_LAYOUT_DEPTH_READ_ONLY_STENCIL_ATTACHMENT_OPTIMAL，相似的，如果如果pStencilAttachment 不是 NULL 且
	pStencilAttachment->imageView 不是 VK_NULL_HANDLE,且对应的resolveMode不是VK_RESOLVE_MODE_NONE，则resolveImageLayout不能是VK_IMAGE_LAYOUT_DEPTH_ATTACHMENT_STENCIL_READ_ONLY_OPTIMAL

	15. 如果pDepthAttachment 不是 NULL 且 pDepthAttachment->imageView 不是 VK_NULL_HANDLE,则对应的resolveMode必须是VkPhysicalDeviceDepthStencilResolveProperties::supportedDepthResolveModes支持的，同理如果pStencilAttachment 不是 NULL 且 pStencilAttachment->imageView
	不是 VK_NULL_HANDLE,则对应的resolveMode必须是VkPhysicalDeviceDepthStencilResolveProperties::supportedDepthResolveModes支持的
	16. 如果pDepthAttachment 和pStencilAttachment不是 NULL 且 pDepthAttachment->imageView 和pStencilAttachment->imageView 不是 VK_NULL_HANDLE，在VkPhysicalDeviceDepthStencilResolveProperties::independentResolve 是 VK_FALSE情况下如果两者的resolveMode都必须相同，如果是
	在VkPhysicalDeviceDepthStencilResolveProperties::independentResolve是VK_FALSE的情况下，只要两者中有一个的resolveMode不是VK_RESOLVE_MODE_NONE，则两者的 resolveMode必须相同

	17.colorAttachmentCount必须小于VkPhysicalDeviceLimits::maxColorAttachments
	18.如果在pNext中含有VkRenderingFragmentDensityMapAttachmentInfoEXT,且其中的imageView不是VK_NULL_HANDLE，则
							（1）：如果fragmentDensityMapNonSubsampledImages没有开启，则合法的 pDepthAttachment, pStencilAttachment, 以及pColorAttachments的resolveImageView中的合法的imageView对应
									的image创建时必须含有VK_IMAGE_CREATE_SUBSAMPLED_BIT_EXT
							（2）：如果viewMask不是0，则imageView的创建时的layerCount必须大于或等于viewMask最大的索引，如果viewMask是0，则imageView的创建时的layerCount必须是1
	19.如果pNext中没有含有VkDeviceGroupRenderPassBeginInfo或者deviceRenderAreaCount为0，且在pNext中含有VkRenderingFragmentShadingRateAttachmentInfoKHR，且对应的imageView不为VK_NULL_HANDLE,则
					（1）imageView的的width要大于等于 (renderArea.x + renderArea.width) / shadingRateAttachmentTexelSize.width
					（2）imageView的的height要大于等于 (renderArea.y + renderArea.height) / shadingRateAttachmentTexelSize.height
	   如果pNext中含有VkDeviceGroupRenderPassBeginInfo且deviceRenderAreaCount不为0，且在pNext中含有VkRenderingFragmentShadingRateAttachmentInfoKHR，且对应的pDeviceRenderAreas的imageView不为VK_NULL_HANDLE,则
					（1）pDeviceRenderAreas的imageView的的width要大于等于 (pDeviceRenderArea.x + pDeviceRenderArea.width) / shadingRateAttachmentTexelSize.width
					（2）pDeviceRenderAreas的imageView的的height要大于等于 (pDeviceRenderArea.y + pDeviceRenderArea.height) / shadingRateAttachmentTexelSize.height
	20. 如果在pNext中含有VkRenderingFragmentShadingRateAttachmentInfoKHR，且对应的imageView不为VK_NULL_HANDLE时，则
					（1）如果viewMask 是 0,则imageView 含有的 layer数量必须等于1 或者大于等于refRenderInfo.layerCount
					（2）如果viewMask不是0，则imageView的含有的 layer数量等于1或者大于或等于viewMask最大的索引
					（3）imageView必须和 pDepthAttachment, pStencilAttachment或者任何 pColorAttachments的resolveImageView的 imageView相等
					（4）imageView必须和pNext中的VkRenderingFragmentDensityMapAttachmentInfoEXT的imageView相等
	21.  viewMask必须小于 maxMultiviewViewCount且如果 multiview特性未开启，则viewMask必须是0
	22.	如果pNext中的VkMultiviewPerViewRenderAreasRenderPassBeginInfoQCOM的perViewRenderAreaCount不为0，则 multiviewPerViewRenderAreas特性必须开启且 refRenderInfo.renderArea必须是
		所有每个view的renderArea的并集
	23. 有效的附件的内存不能交叉重叠
	24. 如果flags包含VK_RENDERING_CONTENTS_INLINE_BIT_EXT，则nestedCommandBuffer特性必须开启
	25. pDepthAttachment->resolveMode以及pStencilAttachment->resolveMode不能是VK_RESOLVE_MODE_EXTERNAL_FORMAT_DOWNSAMPLE_ANDROID
	26. 如果colorAttachmentCount不为1，则pColorAttachments对应的resolveMode不能是 VK_RESOLVE_MODE_EXTERNAL_FORMAT_DOWNSAMPLE_ANDROID，如果pColorAttachments对应的resolveMode是 VK_RESOLVE_MODE_EXTERNAL_FORMAT_DOWNSAMPLE_ANDROID，
			则VkRenderingFragmentDensityMapAttachmentInfoEXT::imageView以及VkRenderingFragmentShadingRateAttachmentInfoKHR::imageView必须是VK_NULL_HANDLE（即没有使用）
	27. 如果pNext中含有 VkRenderPassStripeBeginInfoARM，则定义在 VkRenderPassStripeInfoARM::pStripeInfos中的strip area的并集必须包含refRenderInfo.renderArea
	28. 如果colorAttachmentCount不是0，则pColorAttachments中的不为VK_NULL_HANDLE的imageView创建必须是 identity swizzle，如果pColorAttachments对应的resolveMode为 VK_RESOLVE_MODE_EXTERNAL_FORMAT_DOWNSAMPLE_ANDROID或者是
	pColorAttachments中的不为VK_NULL_HANDLE的imageView对应的resolveMode不为VK_RESOLVE_MODE_NONE，则pColorAttachments的resolveImageView的创建必须是identity swizzle
	29.如果pDepthAttachment不为NULL,且pDepthAttachment->imageView不为VK_NULL_HANDLE,如果pDepthAttachment->resolveMode不为VK_RESOLVE_MODE_NONE，则pDepthAttachment->imageView以及pDepthAttachment->resolveImageView的创建必须是identity swizzle，
	同理如果 pStencilAttachment不为NULL,且 pStencilAttachment->imageView不为VK_NULL_HANDLE,如果 pStencilAttachment->resolveMode不为VK_RESOLVE_MODE_NONE，则 pStencilAttachment->imageView以及 pStencilAttachment->resolveImageView的创建必须是identity swizzle，
	30. 如果在pNext中只要含有VkRenderingFragmentShadingRateAttachmentInfoKHR或者VkRenderingFragmentDensityMapAttachmentInfoEXT，且其中的imageView不为VK_NULL_HANDLE,则该imageView创建必须是identity swizzle

	*/

	VkRenderingAttachmentInfoKHR colorAttachmentInfo{};
	colorAttachmentInfo.sType = VK_STRUCTURE_TYPE_RENDERING_ATTACHMENT_INFO_KHR;
	colorAttachmentInfo.imageView = VK_NULL_HANDLE;//如果imageView是VK_NULL_HANDLE,且resolveMode不是VK_RESOLVE_MODE_EXTERNAL_FORMAT_DOWNSAMPLE_ANDROID,其他参数都会被忽略，类比于没有定义该附件
	colorAttachmentInfo.imageLayout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
	colorAttachmentInfo.clearValue = VkClearValue{ 0,0,0,1 };
	colorAttachmentInfo.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;//只会发生在没有声明VK_RENDERING_RESUMING_BIT_KHR的render pass实例开始
	colorAttachmentInfo.storeOp = VK_ATTACHMENT_STORE_OP_STORE;//只会发生在没有声明VK_RENDERING_SUSPENDING_BIT_KHR的render pass实例结束
	colorAttachmentInfo.pNext = nullptr;
	colorAttachmentInfo.resolveMode = VK_RESOLVE_MODE_NONE;//如果resolveMode不是VK_RESOLVE_MODE_NONE，且resolveImageView不是VK_NULL_HANDLE，将会定义一个多重采样操作，如果resolveMode为VK_RESOLVE_MODE_EXTERNAL_FORMAT_DOWNSAMPLE_ANDROID,
	//且nullColorAttachmentWithExternalFormatResolve为VK_TRUE,在加载操作结束后值便会变得未定义（这里不清楚什么意思）
	colorAttachmentInfo.resolveImageView = VK_NULL_HANDLE;
	colorAttachmentInfo.resolveImageLayout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

	/*
	VkRenderingAttachmentInfo合法用法：（无特殊说明以下和VkRenderingAttachmentInfoKHR成员同名的变量即为VkRenderingAttachmentInfoKHR的成员）
	1. 如果imageView不是 VK_NULL_HANDLE且有一个非整数的color format，则resolveMode必须为 VK_RESOLVE_MODE_NONE 或 VK_RESOLVE_MODE_AVERAGE_BIT，如果是有一个非整数的color format，则resolveMode必须为 VK_RESOLVE_MODE_NONE 或  VK_RESOLVE_MODE_SAMPLE_ZERO_BIT
	2. 如果imageView 不是 VK_NULL_HANDLE，且resolveMode不为 VK_RESOLVE_MODE_NONE，且multisampledRenderToSingleSampledEnable 为 VK_TRUE
					（1）如果VkRenderingInfo的pNext中不含VkMultisampledRenderToSingleSampledInfoEXT ，则 imageView不能含有VK_SAMPLE_COUNT_1_BIT，且resolveImageView 不能为 VK_NULL_HANDLE
					（2）如果VkRenderingInfo的pNext中含VkMultisampledRenderToSingleSampledInfoEXT ，且 imageView不能VK_SAMPLE_COUNT_1_BIT，且resolveImageView 为 VK_NULL_HANDLE
	3. 如果imageView 不是 VK_NULL_HANDLE， resolveImageView不是 VK_NULL_HANDLE,且resolveMode 不是 VK_RESOLVE_MODE_NONE，则 resolveImageView必须是VK_SAMPLE_COUNT_1_BIT，imageView 和 resolveImageView必须有相同的VkFormat
	4. 如果imageView 不是 VK_NULL_HANDLE，则imageLayout不能是VK_IMAGE_LAYOUT_UNDEFINED,
															VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL, VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL,
															VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, 或 VK_IMAGE_LAYOUT_PREINITIALIZED，
															VK_IMAGE_LAYOUT_SHADING_RATE_OPTIMAL_NV 或VK_IMAGE_LAYOUT_FRAGMENT_DENSITY_MAP_OPTIMAL_EXT，
															VK_IMAGE_LAYOUT_FRAGMENT_SHADING_RATE_ATTACHMENT_OPTIMAL_KHR ，或VK_IMAGE_LAYOUT_PRESENT_SRC_KHR，

	4. 如果imageView 不是 VK_NULL_HANDLE，且  resolveMode 不是VK_RESOLVE_MODE_NONE，则resolveImageLayout不能是
															VK_IMAGE_LAYOUT_UNDEFINED,
															VK_IMAGE_LAYOUT_DEPTH_STENCIL_READ_ONLY_OPTIMAL,
															VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL, VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL,
															VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,或者VK_IMAGE_LAYOUT_PREINITIALIZED，
															VK_IMAGE_LAYOUT_DEPTH_READ_ONLY_OPTIMAL 或者 VK_IMAGE_LAYOUT_STENCIL_READ_ONLY_OPTIMAL，
															VK_IMAGE_LAYOUT_SHADING_RATE_OPTIMAL_NV 或VK_IMAGE_LAYOUT_FRAGMENT_DENSITY_MAP_OPTIMAL_EXT，
															VK_IMAGE_LAYOUT_READ_ONLY_OPTIMAL_KHR 或VK_IMAGE_LAYOUT_FRAGMENT_SHADING_RATE_ATTACHMENT_OPTIMAL_KHR，
															 VK_IMAGE_LAYOUT_PRESENT_SRC_KHR
	5. 如果 externalFormatResolve没有启用，则resolveMode必须是VK_RESOLVE_MODE_EXTERNAL_FORMAT_DOWNSAMPLE_ANDROID，且resolveImageView必须是有效的，
									resolveImageView必须以 VkExternalFormatANDROID创建且 subresourceRange.layerCount 为1
	6. 如果 nullColorAttachmentWithExternalFormatResolve属性是VK_TRUE,且resolveMode是VK_RESOLVE_MODE_EXTERNAL_FORMAT_DOWNSAMPLE_ANDROID，resolveImageView的采样数必须是VK_SAMPLE_COUNT_1_BIT，imageView必须为VK_NULL_HANDLE
	7. 如果 nullColorAttachmentWithExternalFormatResolve属性是VK_FALSE,且resolveMode是VK_RESOLVE_MODE_EXTERNAL_FORMAT_DOWNSAMPLE_ANDROID,imageView必须是有效的，且必须有个格式和安卓设备调用vkGetAndroidHardwareBufferPropertiesANDROID返回的用来创建
	resolveImageView的VkAndroidHardwareBufferFormatResolvePropertiesANDROID::colorAttachmentFormat相等
	*/




	VkRenderingFragmentShadingRateAttachmentInfoKHR& renderingFragmentShadingRateAttachmentInfoKHR = renderInfoExt.renderingFragmentShadingRateAttachmentInfoKHR;
	renderingFragmentShadingRateAttachmentInfoKHR.sType = VK_STRUCTURE_TYPE_RENDERING_FRAGMENT_SHADING_RATE_ATTACHMENT_INFO_KHR;
	renderingFragmentShadingRateAttachmentInfoKHR.imageLayout = VK_IMAGE_LAYOUT_GENERAL;
	renderingFragmentShadingRateAttachmentInfoKHR.imageView = VK_NULL_HANDLE;
	renderingFragmentShadingRateAttachmentInfoKHR.shadingRateAttachmentTexelSize = VkExtent2D{ 1,1 };//指定imageView中每个texel对应的像素数。一个texel指的就是在imegaView中处于某个位置（x,y）的最小单元
	//renderingFragmentShadingRateAttachmentInfoKHR.pNext = nullptr;//已经链接起来了这里便不再设置

	/*
	VkRenderingFragmentShadingRateAttachmentInfoKHR合法用法：（无特殊说明以下和VkRenderingFragmentShadingRateAttachmentInfoKHR成员同名的变量即为VkRenderingFragmentShadingRateAttachmentInfoKHR的成员）
	1.如果imageView不是VK_NULL_HANDLE,则
						（1）layout必须是VK_IMAGE_LAYOUT_GENERAL 或者VK_IMAGE_LAYOUT_FRAGMENT_SHADING_RATE_ATTACHMENT_OPTIMAL_KHR
						（2）imageView必须以VK_IMAGE_USAGE_FRAGMENT_SHADING_RATE_ATTACHMENT_BIT_KHR创建
						（3） minFragmentShadingRateAttachmentTexelSize.width <= shadingRateAttachmentTexelSize.width(2的整数次幂) <=maxFragmentShadingRateAttachmentTexelSize.width
						（4） minFragmentShadingRateAttachmentTexelSize.height <= shadingRateAttachmentTexelSize.height(2的整数次幂) <=maxFragmentShadingRateAttachmentTexelSize.height
						（5）（shadingRateAttachmentTexelSize.width /  shadingRateAttachmentTexelSize.height） <= maxFragmentShadingRateAttachmentTexelSizeAspectRatio
						（6） （shadingRateAttachmentTexelSize.height /  shadingRateAttachmentTexelSize.width） <= maxFragmentShadingRateAttachmentTexelSizeAspectRatio
						（7）imageView必须是个有效的对象
	*/

	VkRenderingFragmentDensityMapAttachmentInfoEXT& renderingFragmentDensityMapAttachmentInfoEXT = renderInfoExt.renderingFragmentDensityMapAttachmentInfoEXT;
	renderingFragmentDensityMapAttachmentInfoEXT.sType = VK_STRUCTURE_TYPE_RENDERING_FRAGMENT_DENSITY_MAP_ATTACHMENT_INFO_EXT;
	renderingFragmentDensityMapAttachmentInfoEXT.imageLayout = VK_IMAGE_LAYOUT_GENERAL;//如果imageView不是VK_NULL_HANDLE，则必须为VK_IMAGE_LAYOUT_GENERAL 或者
	//VK_IMAGE_LAYOUT_FRAGMENT_DENSITY_MAP_OPTIMAL_EXT
	renderingFragmentDensityMapAttachmentInfoEXT.imageView = VK_NULL_HANDLE;//如果imageView不是VK_NULL_HANDLE，则创建必须含有VK_IMAGE_USAGE_FRAGMENT_DENSITY_MAP_BIT_EXT，且不能含有VK_IMAGE_CREATE_SUBSAMPLED_BIT_EXT；
	//如果 multiview未开启且 VkPhysicalDeviceProperties::apiVersion小于vulkan1.1，则imageView的 layerCount为1

	//renderingFragmentDensityMapAttachmentInfoEXT.pNext = nullptr;//已经链接起来了这里便不再设置



	//获取render pass的区域渲染粒度
	VkRenderPass renderPass;
	VkExtent2D renderAreaGranularity;
	typedef struct VkRenderingAreaInfoKHR {
		VkStructureType sType;
		const void* pNext;
		uint32_t viewMask;
		uint32_t colorAttachmentCount;
		const VkFormat* pColorAttachmentFormats;
		VkFormat depthAttachmentFormat;
		VkFormat stencilAttachmentFormat;
	} VkRenderingAreaInfoKHR;//这个结构体当前的vulkan没有定义，这里用以用来做示例
	auto vkGetRenderAreaGranularityKHR = [](VkDevice device,
		const VkRenderingAreaInfoKHR* pRenderingAreaInfo,
		VkExtent2D* pGranularity) {

	};//这个接口当前的vulkan没有定义，这里用以用来做示例，当前vulkanz只定义了vkGetRenderAreaGranularity
	VkRenderingAreaInfoKHR renderAreaInfo{};
	renderAreaInfo.sType = VK_STRUCTURE_TYPE_MAX_ENUM;//因为当前的vulkan没有定义该结构体，所以这里直接设置为一个非法的值
	renderAreaInfo.colorAttachmentCount = 0;
	renderAreaInfo.pColorAttachmentFormats = VK_NULL_HANDLE;
	renderAreaInfo.depthAttachmentFormat = VK_FORMAT_UNDEFINED;
	renderAreaInfo.stencilAttachmentFormat = VK_FORMAT_UNDEFINED;
	renderAreaInfo.viewMask = 0;
	renderAreaInfo.pNext = nullptr;

	vkGetRenderAreaGranularityKHR(device, &renderAreaInfo, &renderAreaGranularity);
	/*
		最佳的refRenderInfo.renderArea渲染区域应该是：
			 refRenderInfo.renderArea.offset.x应该是renderAreaGranularity.width的倍数；
			 refRenderInfo.renderArea.offset.y应该是renderAreaGranularity.height的倍数；
			 refRenderInfo.renderArea.extent.width应该是renderAreaGranularity.width的倍数或者refRenderInfo.renderArea.offset.x+refRenderInfo.renderArea.extent.width要等于在当前render pass中使用的附件的宽度
			 refRenderInfo.renderArea.extent.height应该是renderAreaGranularity.height的倍数或者refRenderInfo.renderArea.offset.y+refRenderInfo.renderArea.extent.height要等于在当前render pass中使用的附件的高度
	*/


	VkRenderPassStripeBeginInfoARM renderPassStripeBeginInfoARM = renderInfoExt.renderPassStripeBeginInfoARM;//这里不再进行设置
	renderPassStripeBeginInfoARM.sType = VK_STRUCTURE_TYPE_MAX_ENUM;//因为vulkan没有定义这个结构体，所以设置为一个非法值
	renderPassStripeBeginInfoARM.pNext = nullptr;
	renderPassStripeBeginInfoARM.stripeInfoCount = 1;
	VkRenderPassStripeInfoARM stripInfo{};
	stripInfo.sType = VK_STRUCTURE_TYPE_MAX_ENUM;//因为vulkan没有定义这个结构体，所以设置为一个非法值
	stripInfo.pNext = nullptr;
	stripInfo.stripeArea = renderInfo.renderArea;//直接等于VkRenderingInfoKHR的renderArea
	renderPassStripeBeginInfoARM.pStripeInfos = nullptr;



	//在BeginRendering 到EndRendering中可以调 vkCmdBeginQuery*以及vkCmdEndQuery*，这两个接口配套出现在同一个render pass中



	//framebuffer-local dependencies在subpass之间






	vkCmdEndRenderingKHR(cmdbuf);//如果pRenderingInfo->flags为VK_RENDERING_SUSPENDING_BIT，则调用该命令后会挂起该render pass等待下一个render pass获取

	VkTilePropertiesQCOM tilePropertiesQCOM{};
	tilePropertiesQCOM.sType = VK_STRUCTURE_TYPE_TILE_PROPERTIES_QCOM;

	//查询dynamic rendering的tile属性
	vkGetDynamicRenderingTilePropertiesQCOM(device, &renderInfo, &tilePropertiesQCOM);

}

struct RenderPassCreateInfoExt
{

	VkRenderPassFragmentDensityMapCreateInfoEXT	renderPassFragmentDensityMapCreateInfoEXT{};
	VkRenderPassInputAttachmentAspectCreateInfo	 renderPassInputAttachmentAspectCreateInfo{};
	VkRenderPassMultiviewCreateInfo renderPassMultiviewCreateInfo{};
	RenderPassCreateInfoExt() {
		Init();
	}
	void Init() {
		renderPassFragmentDensityMapCreateInfoEXT.sType = VK_STRUCTURE_TYPE_RENDER_PASS_FRAGMENT_DENSITY_MAP_CREATE_INFO_EXT;
		renderPassFragmentDensityMapCreateInfoEXT.pNext = &renderPassInputAttachmentAspectCreateInfo;
		renderPassInputAttachmentAspectCreateInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_INPUT_ATTACHMENT_ASPECT_CREATE_INFO;
		renderPassInputAttachmentAspectCreateInfo.pNext = &renderPassMultiviewCreateInfo;
		renderPassMultiviewCreateInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_MULTIVIEW_CREATE_INFO;
		renderPassMultiviewCreateInfo.pNext = nullptr;
	}
};
struct RenderPassCreateInfo2Ext
{
	VkRenderPassCreationControlEXT	renderPassCreationControlEXT{};
	VkRenderPassCreationFeedbackCreateInfoEXT renderPassCreationFeedbackCreateInfoEXT{};
	VkRenderPassFragmentDensityMapCreateInfoEXT renderPassFragmentDensityMapCreateInfoEXT{};
	RenderPassCreateInfo2Ext() {
		Init();
	}
	void Init() {
		renderPassCreationControlEXT.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATION_CONTROL_EXT;
		renderPassCreationControlEXT.pNext = &renderPassCreationFeedbackCreateInfoEXT;
		renderPassCreationFeedbackCreateInfoEXT.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATION_FEEDBACK_CREATE_INFO_EXT;
		renderPassCreationFeedbackCreateInfoEXT.pNext = &renderPassFragmentDensityMapCreateInfoEXT;
		renderPassFragmentDensityMapCreateInfoEXT.sType = VK_STRUCTURE_TYPE_RENDER_PASS_FRAGMENT_DENSITY_MAP_CREATE_INFO_EXT;
		renderPassFragmentDensityMapCreateInfoEXT.pNext = nullptr;

	}
};


struct SubpassDesctiption2Ext {
	VkFragmentShadingRateAttachmentInfoKHR fragmentShadingRateAttachmentInfoKHR{};
	VkMultisampledRenderToSingleSampledInfoEXT  multisampledRenderToSingleSampledInfoEXT{};
	VkRenderPassCreationControlEXT renderPassCreationControlEXT{};
	VkRenderPassSubpassFeedbackCreateInfoEXT renderPassSubpassFeedbackCreateInfoEXT{};
	VkSubpassDescriptionDepthStencilResolve subpassDescriptionDepthStencilResolve{};
	SubpassDesctiption2Ext() {
		Init();
	}
	void Init() {
		fragmentShadingRateAttachmentInfoKHR.sType = VK_STRUCTURE_TYPE_FRAGMENT_SHADING_RATE_ATTACHMENT_INFO_KHR;
		fragmentShadingRateAttachmentInfoKHR.pNext = &multisampledRenderToSingleSampledInfoEXT;
		multisampledRenderToSingleSampledInfoEXT.sType = VK_STRUCTURE_TYPE_MULTISAMPLED_RENDER_TO_SINGLE_SAMPLED_INFO_EXT;
		multisampledRenderToSingleSampledInfoEXT.pNext = &renderPassCreationControlEXT;
		renderPassCreationControlEXT.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATION_CONTROL_EXT;
		renderPassCreationControlEXT.pNext = &renderPassSubpassFeedbackCreateInfoEXT;
		renderPassSubpassFeedbackCreateInfoEXT.sType = VK_STRUCTURE_TYPE_RENDER_PASS_SUBPASS_FEEDBACK_CREATE_INFO_EXT;
		renderPassSubpassFeedbackCreateInfoEXT.pNext = &subpassDescriptionDepthStencilResolve;
		subpassDescriptionDepthStencilResolve.sType = VK_STRUCTURE_TYPE_SUBPASS_DESCRIPTION_DEPTH_STENCIL_RESOLVE;
		subpassDescriptionDepthStencilResolve.pNext = nullptr;



	}

};


void RenderPassTest::RenderPassCreateTest()
{
	
	VkRenderPassCreateInfo renderPassCreateInfo{};
	renderPassCreateInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
	renderPassCreateInfo.flags = 0;//VK_RENDER_PASS_CREATE_TRANSFORM_BIT_QCOM 指明该render pass适配render pass transform特性，这里的变换指的是顶点着色器中裁剪坐标的的（x,y）会沿着坐标原点做旋转变换，如旋转90°
	renderPassCreateInfo.attachmentCount = 0;
	renderPassCreateInfo.pAttachments = VK_NULL_HANDLE;
	renderPassCreateInfo.dependencyCount = 0;
	renderPassCreateInfo.pDependencies = VK_NULL_HANDLE;//如果两个subpass之间存在数据竞争，比如某个subpass需要往某个附件中写数据，那么就需要一个subpass dependence
	renderPassCreateInfo.subpassCount = 0;
	renderPassCreateInfo.pSubpasses = VK_NULL_HANDLE;
	RenderPassCreateInfoExt renderPassCreateInfoExt{};
	renderPassCreateInfo.pNext = &renderPassCreateInfoExt.renderPassFragmentDensityMapCreateInfoEXT;
	/*
	合法用法：
	1. 如果pSubpasser中的pInputAttachments, pColorAttachments,pResolveAttachments 或者 pDepthStencilAttachment,或者 pPreserveAttachments中有的attachment不是VK_ATTACHMENT_UNUSED，那么attachment索引必须小于等于renderPassCreateInfo.attachmentCount
	2. 如果pNext中含有VkRenderPassFragmentDensityMapCreateInfoEXT，且fragmentDensityMapAttachment不是VK_ATTACHMENT_UNUSED，则attachment索引必须小于等于renderPassCreateInfo.attachmentCount
	3. 对于任何 pAttachments 的 loadOp 加载操作为 VK_ATTACHMENT_LOAD_OP_CLEAR的附件，对于这个附件的第一次使用的布局不能是VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL 或者VK_IMAGE_LAYOUT_DEPTH_STENCIL_READ_ONLY_OPTIMAL或者VK_IMAGE_LAYOUT_DEPTH_READ_ONLY_STENCIL_ATTACHMENT_OPTIMAL
	4. 对于任何 pAttachments 的stencilLoadOp加载操作为 VK_ATTACHMENT_LOAD_OP_CLEAR的附件，对于这个附件的第一次使用的布局不能是VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL 或者VK_IMAGE_LAYOUT_DEPTH_STENCIL_READ_ONLY_OPTIMAL或者 VK_IMAGE_LAYOUT_DEPTH_ATTACHMENT_STENCIL_READ_ONLY_OPTIMAL
	5. 如果pNext中含有VkRenderPassInputAttachmentAspectCreateInfo，则
						（1） 则VkRenderPassInputAttachmentAspectCreateInfo.pAspectReferences中每个元素对应的subpass索引必须小于renderPassCreateInfo.subpassCount
						（2） 则VkRenderPassInputAttachmentAspectCreateInfo.pAspectReferences中每个元素的 inputAttachmentIndex必须小于小于该元素中对应的subpass所对应的inputAttachmentCount
						（3） 则VkRenderPassInputAttachmentAspectCreateInfo.pAspectReferences中每个元素所对应的subpass中的 pInputAttachments的附件不是VK_ATTACHMENT_UNUSED,那么该VkRenderPassInputAttachmentAspectCreateInfo.pAspectReferences元素中的aspectMask值必须是只能包含对应renderPassCreateInfo.pAttachments中的附件有的aspectMask
	6. 如果pNext中含有VkRenderPassMultiviewCreateInfo，则
						（1） 如果VkRenderPassMultiviewCreateInfo.subpassCount不为0，则必须为renderPassCreateInfo.subpassCount
						（2） 如果VkRenderPassMultiviewCreateInfo.dependencyCount不为0，则必须为renderPassCreateInfo.dependencyCount
						（3） 对应VkRenderPassMultiviewCreateInfo.pViewOffsets的每个非零值， srcSubpass 和 dstSubpass必须和相同索引的renderPassCreateInfo.pDependencies的相同
						（4） 对于任何renderPassCreateInfo.pDependencies的dependencyFlags没有含有VK_DEPENDENCY_VIEW_LOCAL_BIT，那么相同索引的VkRenderPassMultiviewCreateInfo.pViewOffsets的值必须是0
						（5） 如果 VkRenderPassMultiviewCreateInfo.pViewMasks的每个元素都是0,则 VkRenderPassMultiviewCreateInfo.correlationMaskCount也是0，对于任何renderPassCreateInfo.pDependencies的dependencyFlags不能含有VK_DEPENDENCY_VIEW_LOCAL_BIT
	7. 对于任何pDependencies中的元素,如果srcSubpass/dstSubpass 不是 VK_SUBPASS_EXTERNAL ，那么srcSubpass/dstSubpass必须小于subpassCount， 且那么 srcStageMask/dstStageMask必须是pipelineBindPoint绑定的pipeline所支持的管线状态

	8. 如果 attachmentCount，subpassCount，以及dependencyCount都不为0，pAttachments，pSubpasses以及pDependencies都需要是一个有效的含有 VkAttachmentDescription，VkSubpassDescription以及 VkSubpassDependency有效数据的数组的指针
	9. subpassCount必须大于0


	*/


	//VkRenderPassCreateInfo可以链接的拓展结构体
	VkRenderPassMultiviewCreateInfo& renderPassMultiviewCreateInfo = renderPassCreateInfoExt.renderPassMultiviewCreateInfo;
	renderPassMultiviewCreateInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_MULTIVIEW_CREATE_INFO;
	renderPassMultiviewCreateInfo.subpassCount = 1;//为0或者render pass的subpass数量
	renderPassMultiviewCreateInfo.dependencyCount = 1;//为0或者render pass的dependency数量
	renderPassMultiviewCreateInfo.correlationMaskCount = 0;
	renderPassMultiviewCreateInfo.pCorrelationMasks = nullptr;// correlationMaskCount个view masks指明那些views可以更有效的同时进行渲染
	renderPassMultiviewCreateInfo.pViewMasks = VK_NULL_HANDLE;//subpassCount个viewMask，每个viewMask是个view索引的位字段描述哪个view会在subpass中被渲染（当 multiview开启），如果 subpassCount为0，pViewMasks中每个都认为是0
	renderPassMultiviewCreateInfo.pViewOffsets = VK_NULL_HANDLE;// dependencyCount个viewOffset，每个dependence一个，如果dependencyCount为0，pViewOffsets中每个都认为是0，每个viewOffset控制每个dstSubpass基于srcSubpass的view的偏移量
	//其他关于multiView的描述见文档p519
	/*
	合法用法：
	1. 每个view index不能被设置在pCorrelationMasks的多个项中
	2.  multiview如果没有开启，则 pViewMasks的所有值都是0
	3.  pViewMasks中的值的最大的有效位不能超过maxMultiviewViewCount
	4. 如果subpassCount，dependencyCount，以及correlationMaskCount都不为0，则pCorrelationMasks，pViewMasks以及pViewOffsets都需要是一个uint32_t,int32_t,uint32_t的有效的数组的指针
	*/


	//这个应该是subpass拓展的额外结构体
	VkMultiviewPerViewAttributesInfoNVX multiviewPerViewAttributesInfoNVX{};//可以用来包含在subpass创建信息的pNext中
	multiviewPerViewAttributesInfoNVX.sType = VK_STRUCTURE_TYPE_MULTIVIEW_PER_VIEW_ATTRIBUTES_INFO_NVX;
	multiviewPerViewAttributesInfoNVX.pNext = nullptr;
	multiviewPerViewAttributesInfoNVX.perViewAttributes = VK_FALSE;//指定为此管道编译的着色器在每个顶点处理阶段的单个调用中为所有view输出属性，将写 per-view attributes 到 *PerViewNV[]着色器输出而不是 non-per-view (e.g. Position) 输出.
	multiviewPerViewAttributesInfoNVX.perViewAttributesPositionXOnly = VK_FALSE;//指明当前pipeline编译的着色器将使用只有x分量不同的per-view positions， Per-view viewport mask也可以被使用
	//如果使用dynamic render pass实例来进行渲染，除了在subpass创建信息中指定VK_SUBPASS_DESCRIPTION_PER_VIEW_ATTRIBUTES_BIT_NVX 或者VK_SUBPASS_DESCRIPTION_PER_VIEW_POSITION_X_ONLY_BIT_NVX，
	//还需要将VkMultiviewPerViewAttributesInfoNVX包含在创建pipeline的fVkGraphicsPipelineCreateInfo中，在开始动态渲染的 VkRenderingInfo中，在指明动态渲染的次级缓冲区参数的VkCommandBufferInheritanceInfo中




	//VkRenderPassCreateInfo可以链接的拓展结构体
	VkRenderPassFragmentDensityMapCreateInfoEXT& renderPassFragmentDensityMapCreateInfoEXT = renderPassCreateInfoExt.renderPassFragmentDensityMapCreateInfoEXT;
	renderPassFragmentDensityMapCreateInfoEXT.fragmentDensityMapAttachment = VkAttachmentReference{
	.attachment = 0,/*
		如果attachment对应的imageView以VK_IMAGE_VIEW_CREATE_FRAGMENT_DENSITY_MAP_DYNAMIC_BIT_EXT创建，那么fragment density map将在 VK_PIPELINE_STAGE_FRAGMENT_DENSITY_PROCESS_BIT_EXT阶段被device读取；
		如果attachment对应的imageView以VK_IMAGE_VIEW_CREATE_FRAGMENT_DENSITY_MAP_DEFERRED_BIT_EXT创建，那么fragment density map将在主要命令缓冲区的 vkEndCommandBuffer命令中被host读取
		其他情况将会在vkCmdBeginRenderPass被host读取
	*/
	.layout = VK_IMAGE_LAYOUT_ATTACHMENT_OPTIMAL };
	/*
	合法用法：
	1.如果fragmentDensityMapAttachment不是VK_ATTACHMENT_UNUSED，
							（1）则fragmentDensityMapAttachment不能属于任何subpass的VkSubpassDescription::pInputAttachments,VkSubpassDescription::pColorAttachments, VkSubpassDescription::pResolveAttachments,
								VkSubpassDescription::pDepthStencilAttachment, 或者 VkSubpassDescription::pPreserveAttachments
							（2）则layout 必须为VK_IMAGE_LAYOUT_FRAGMENT_DENSITY_MAP_OPTIMAL_EXT, 或者 VK_IMAGE_LAYOUT_GENERAL
							（3） fragmentDensityMapAttachment引用的attachment的 loadOp 必须为 VK_ATTACHMENT_LOAD_OP_LOAD 或者 VK_ATTACHMENT_LOAD_OP_DONT_CARE
							（3） fragmentDensityMapAttachment引用的attachment的 storeOp 必须为 VK_ATTACHMENT_STORE_OP_DONT_CARE
	2. 引用的attachment必须是有效的
	*/


	//VkAttachmentDescription 附件描述
	VkAttachmentDescription colorAttachment{};
	colorAttachment.format = VK_FORMAT_R8G8B8_SRGB;
	colorAttachment.flags = VK_ATTACHMENT_DESCRIPTION_MAY_ALIAS_BIT;//VK_ATTACHMENT_DESCRIPTION_MAY_ALIAS_BIT（别名）指明这个附件和同一render pass的其他附件共享内存（例如附件都使用同一个imageView或者使用不同的imageView但是引用到相同的image的subResource,或者引用的不是相同的image的subResourceRange但是绑定到相同的内存重叠区域）
	//如果flags中包含VK_ATTACHMENT_DESCRIPTION_MAY_ALIAS_BIT，且如果有subpass会往其中写入数据那么就需要一个memory dependence来保证写入顺序,且dependence不能有 VK_DEPENDENCY_BY_REGION_BIT如果是不同的image的subResource但是绑定到相同的内存重叠区域这种情况，可能VK_ATTACHMENT_DESCRIPTION_MAY_ALIAS_BIT的附件不能在同一个subpass内使用，
	//如果多个附件有VK_ATTACHMENT_DESCRIPTION_MAY_ALIAS_BIT且在同一个冲突域，则除了render pass第一个被使用attachment的initialLayout外其他的attachment的initialLayout都必须是VK_IMAGE_LAYOUT_UNDEFINED
	colorAttachment.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;//指明render pass开始时候的附件布局
	colorAttachment.finalLayout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;//指明render pass结束时候的附件布局
	colorAttachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;//控制color attachment的加载操作或者附件depth数据的加载操作
	colorAttachment.storeOp = VK_ATTACHMENT_STORE_OP_STORE;//控制color attachment的存储操作或者附件depth数据的存储操作
	colorAttachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_NONE_EXT;//控制附件stencil数据的加载操作
	colorAttachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_NONE;//控制附件stencil数据的存储操作
	colorAttachment.samples = VK_SAMPLE_COUNT_1_BIT;
	/*
	VkAttachmentDescription合法用法：
	1. 如果format包含color以及depth内容，且loadOp为VK_ATTACHMENT_LOAD_OP_LOAD，则initialLayout不能是VK_IMAGE_LAYOUT_UNDEFINED
	2. finalLayout 不能是 VK_IMAGE_LAYOUT_UNDEFINED 或者VK_IMAGE_LAYOUT_PREINITIALIZED
	3. 如果format是color格式，initialLayout和finalLayout 不能是VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL 或者VK_IMAGE_LAYOUT_DEPTH_STENCIL_READ_ONLY_OPTIMAL，
															 VK_IMAGE_LAYOUT_DEPTH_ATTACHMENT_STENCIL_READ_ONLY_OPTIMAL 或者
															 VK_IMAGE_LAYOUT_DEPTH_READ_ONLY_STENCIL_ATTACHMENT_OPTIMAL，
															 VK_IMAGE_LAYOUT_DEPTH_ATTACHMENT_OPTIMAL, VK_IMAGE_LAYOUT_DEPTH_READ_ONLY_OPTIMAL,
															 VK_IMAGE_LAYOUT_STENCIL_ATTACHMENT_OPTIMAL, 或者
															 VK_IMAGE_LAYOUT_STENCIL_READ_ONLY_OPTIMAL
	4. 如果format是depth/stencil格式，initialLayout和finalLayout不能是VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL
	5. 如果 separateDepthStencilLayouts（depth和stencil布局是否能分开）特性没有开启，那么 initialLayout以及finalLayout不能是
																			VK_IMAGE_LAYOUT_DEPTH_ATTACHMENT_OPTIMAL, VK_IMAGE_LAYOUT_DEPTH_READ_ONLY_OPTIMAL,
																			VK_IMAGE_LAYOUT_STENCIL_ATTACHMENT_OPTIMAL,或者
																			VK_IMAGE_LAYOUT_STENCIL_READ_ONLY_OPTIMAL,
	6. 如果format是depth/stencil格式，且含有depth和stencil数据或者只含有depth数据，则initialLayout和finalLayout不能是VK_IMAGE_LAYOUT_STENCIL_ATTACHMENT_OPTIMAL 或者
																								  VK_IMAGE_LAYOUT_STENCIL_READ_ONLY_OPTIMAL，


	7. 如果synchronization2特性未开启，initialLayout和finalLayout不能是VK_IMAGE_LAYOUT_ATTACHMENT_OPTIMAL_KHR 或者 VK_IMAGE_LAYOUT_READ_ONLY_OPTIMAL_KHR
	8. 如果attachmentFeedbackLoopLayout特性未开启，initialLayout和finalLayout不能是VK_IMAGE_LAYOUT_ATTACHMENT_FEEDBACK_LOOP_OPTIMAL_EXT
	9. samples必须是必须和image创建时候的samples相同
	10. 如果dynamicRenderingLocalRead特性未开启，initialLayout和finalLayout不能是VK_IMAGE_LAYOUT_RENDERING_LOCAL_READ_KHR
	11. format不能为VK_FORMAT_UNDEFINED
	12. 如果format 有stencil 数据且 stencilLoadOp 是 VK_ATTACHMENT_LOAD_OP_LOAD,则 initialLayout 不能为 VK_IMAGE_LAYOUT_UNDEFINED
	13.如果format是depth/stencil格式，且只含有stencil数据，则initialLayout和finalLayout不能是VK_IMAGE_LAYOUT_DEPTH_ATTACHMENT_OPTIMAL
																								  或者VK_IMAGE_LAYOUT_DEPTH_READ_ONLY_OPTIMAL
	14. 如果format是depth/stencil格式，且含有depth和stencil数据，则initialLayout和finalLayout不能是VK_IMAGE_LAYOUT_DEPTH_ATTACHMENT_OPTIMAL 或者VK_IMAGE_LAYOUT_DEPTH_READ_ONLY_OPTIMAL

	*/

	VkAttachmentReference colorAttachmentRef{};
	colorAttachmentRef.attachment = 0;//引用VkRenderPassCreateInfo.pAttachments中的第0个attachment
	colorAttachmentRef.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;//指明attachment的布局


	//VkRenderPassCreateInfo可以链接的拓展结构体
	VkRenderPassInputAttachmentAspectCreateInfo& renderPassInputAttachmentAspectCreateInfo = renderPassCreateInfoExt.renderPassInputAttachmentAspectCreateInfo;
	renderPassInputAttachmentAspectCreateInfo.aspectReferenceCount = 0;
	VkInputAttachmentAspectReference inputAttachmentAspectReference{};
	inputAttachmentAspectReference.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
	inputAttachmentAspectReference.subpass = 0;//aspectMask不能为VK_IMAGE_ASPECT_METADATA_BIT以及对于任何索引 i，不能为VK_IMAGE_ASPECT_MEMORY_PLANE_i_BIT_EXT 
	inputAttachmentAspectReference.inputAttachmentIndex = 0;//pCreateInfo->pSubpasses[subpass].pInputAttachments[inputAttachmentIndex]
	renderPassInputAttachmentAspectCreateInfo.pAspectReferences = &inputAttachmentAspectReference;//是VkInputAttachmentAspectReference的长度为aspectReferenceCount的数组，每个元素描述了某个subpass的输入附件的aspectMask以及对应输入附件的索引
	//如果pAspectReferences没有指定某个subpass的输入附件的aspectMask，则程序可以访问该附件的任意aspectMask，如果已经指定则只能访问指定的aspectMask




	//subpass描述,主要描述附件以及subpass的用处
	VkSubpassDescription subpassDescription{};
	subpassDescription.flags = 0;/*
		VK_SUBPASS_DESCRIPTION_PER_VIEW_ATTRIBUTES_BIT_NVX: 指定当前subpass编译的着色器会在 pre-rasterization 着色器阶段的单个调用中为所有view输出属性，如果不含当前标志，则该subpass则不输出到 *PerViewNV[]，而是输出到non-per-view (e.g. Position) outputs.
		VK_SUBPASS_DESCRIPTION_PER_VIEW_POSITION_X_ONLY_BIT_NVX: 指定当前subpass编译的着色器使用per-view positions将只有x分量不同，Per-view viewport mask也将被使用
		VK_SUBPASS_DESCRIPTION_FRAGMENT_REGION_BIT_QCOM: 指定当前subpass的framebuffer region 是 fragment region，即最小的region dependence是基于pixel的，而不是基于sample的，任何fragment shader都可以访问当前fragment shader调用的的任何sample
		VK_SUBPASS_DESCRIPTION_SHADER_RESOLVE_BIT_QCOM: 指定当前subpass执行shader resolve操作（允许自定义resolve操作）
		VK_SUBPASS_DESCRIPTION_RASTERIZATION_ORDER_ATTACHMENT_COLOR_ACCESS_BIT_EXT: 指定当前subpass支持以VK_PIPELINE_COLOR_BLEND_STATE_CREATE_RASTERIZATION_ORDER_ATTACHMENT_ACCESS_BIT_EXT.创建的pipeline
		VK_SUBPASS_DESCRIPTION_RASTERIZATION_ORDER_ATTACHMENT_DEPTH_ACCESS_BIT_EXT: 指定当前subpass支持以VK_PIPELINE_DEPTH_STENCIL_STATE_CREATE_RASTERIZATION_ORDER_ATTACHMENT_DEPTH_ACCESS_BIT_EXT.创建的pipeline
		VK_SUBPASS_DESCRIPTION_RASTERIZATION_ORDER_ATTACHMENT_STENCIL_ACCESS_BIT_EXT: 指定当前subpass支持以VK_PIPELINE_DEPTH_STENCIL_STATE_CREATE_RASTERIZATION_ORDER_ATTACHMENT_STENCIL_ACCESS_BIT_EXT.创建的pipeline
		VK_SUBPASS_DESCRIPTION_ENABLE_LEGACY_DITHERING_BIT_EXT: 指明当前subpass启用legacy dithering

	*/
	subpassDescription.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
	subpassDescription.colorAttachmentCount = 1;
	subpassDescription.pColorAttachments = VK_NULL_HANDLE;//pColorAttachments在着色器中可以通过指定的描述符集标识进行访问，比如glsl中示例layout (location = 0) out vec4 color;
	subpassDescription.pResolveAttachments = VK_NULL_HANDLE;//如果flags不包含VK_SUBPASS_DESCRIPTION_SHADER_RESOLVE_BIT_QCOM,且pResolveAttachments不是VK_NULL_HANDLE,则pResolveAttachments中的每个元素都会为一一对应的color attachment定义一个超采样操作，除非resolve attachment是VK_ATTACHMENT_UNUSED.
	subpassDescription.inputAttachmentCount = 0;
	subpassDescription.pInputAttachments = VK_NULL_HANDLE;//pInputAttachments在着色器中可以通过指定的描述符集标识进行访问，比如glsl中示例layout (input_attachment_index = 0, set = 0, binding = 0) uniform subpassInput myInputAttachment;
	subpassDescription.preserveAttachmentCount = 0;
	subpassDescription.pPreserveAttachments = VK_NULL_HANDLE;//见p532
	subpassDescription.pDepthStencilAttachment = VK_NULL_HANDLE;//如果flags不包含VK_SUBPASS_DESCRIPTION_SHADER_RESOLVE_BIT_QCOM，且VkSubpassDescriptionDepthStencilResolve::pDepthStencilResolveAttachment不为NULL且对应的attachment不为VK_ATTACHMENT_UNUSED，则
	//则为pDepthStencilAttachment定义了VkSubpassDescriptionDepthStencilResolve::depthResolveMode以及VkSubpassDescriptionDepthStencilResolve::stencilResolveMode的超采样操作，如果VkSubpassDescriptionDepthStencilResolve::depthResolveMode是VK_RESOLVE_MODE_NONE，
	//或者pDepthStencilResolveAttachment没有 depth aspect,则不会为depth定义超采样操作，如果VkSubpassDescriptionDepthStencilResolve::stencilResolveMode是VK_RESOLVE_MODE_NONE。或者pDepthStencilResolveAttachment没有 stencil aspeck，则不会为stencil定义超采样操作。
	//如果depth/stencil的附件引用的image创建为VK_IMAGE_CREATE_SAMPLE_LOCATIONS_COMPATIBLE_DEPTH_BIT_EXT，则对应的超采样操作将用VkRenderPassSampleLocationsBeginInfoEXT::pPostSubpassSampleLocations中的 sampleLocationsInfo 来进行

	/*
	VkSubpassDescription合法用法：
	1. 如果pInputAttachments的attachment不是 VK_ATTACHMENT_UNUSED，则layout不能是VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL 或者 VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL，
																															   VK_IMAGE_LAYOUT_DEPTH_ATTACHMENT_OPTIMAL 或者VK_IMAGE_LAYOUT_STENCIL_ATTACHMENT_OPTIMAL，
																															   VK_IMAGE_LAYOUT_ATTACHMENT_OPTIMAL_KHR
	2. 如果 pColorAttachments或者pResolveAttachments的attachment不是 VK_ATTACHMENT_UNUSED，则layout不能是 VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL 或者VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL，
																										  VK_IMAGE_LAYOUT_DEPTH_ATTACHMENT_STENCIL_READ_ONLY_OPTIMAL 或者
																										  VK_IMAGE_LAYOUT_DEPTH_READ_ONLY_STENCIL_ATTACHMENT_OPTIMAL，
																										  VK_IMAGE_LAYOUT_DEPTH_ATTACHMENT_OPTIMAL,VK_IMAGE_LAYOUT_DEPTH_READ_ONLY_OPTIMAL,
																										  VK_IMAGE_LAYOUT_STENCIL_ATTACHMENT_OPTIMAL, 或者 VK_IMAGE_LAYOUT_STENCIL_READ_ONLY_OPTIMAL，
																										  VK_IMAGE_LAYOUT_READ_ONLY_OPTIMAL_KHR
	3. 如果 pDepthStencilAttachment的attachment不是 VK_ATTACHMENT_UNUSED，则layout不能是VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL 或者VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL
	4. pipelineBindPoint必须是VK_PIPELINE_BIND_POINT_GRAPHICS 或者VK_PIPELINE_BIND_POINT_SUBPASS_SHADING_HUAWEI
	5. colorAttachmentCount必须小于等于VkPhysicalDeviceLimits::maxColorAttachments
	6. 如果一个attachment在render pass中的第一次使用作为input attachment，而且在该subpass中不是作为color 或者 depth/stencil附件，则其的loadOp不能是 VK_ATTACHMENT_LOAD_OP_CLEAR
	7. 如果pResolveAttachments不是NULL,且其中的元素对应的resolve attachment也不是VK_ATTACHMENT_UNUSED,则：
											（1）其对应的color attachment也不能是VK_ATTACHMENT_UNUSED、
											（2）则其对应的的color attachment的采样数不能是VK_SAMPLE_COUNT_1_BIT
											（3）其中的元素对应的resolve attachment的采样数必须是VK_SAMPLE_COUNT_1_BIT
											（4）其中的元素对应的resolve attachment的format要和对应的color attachment的format相同
	8. pColorAttachments中不是 VK_ATTACHMENT_UNUSED的所有附件的采样数必须相同
	9.  pInputAttachments中不是VK_ATTACHMENT_UNUSED的attachment必须含有拥有potential format features （见p4100）至少为VK_FORMAT_FEATURE_COLOR_ATTACHMENT_BIT 或者VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT的 image format
	10. pColorAttachments或者pResolveAttachments中不是VK_ATTACHMENT_UNUSED的attachment必须含有拥有potential format features （见p4100）为 VK_FORMAT_FEATURE_COLOR_ATTACHMENT_BIT的 image format
	11. pDepthStencilAttachment 不是 NULL 且 其attachment 不是 VK_ATTACHMENT_UNUSED， 则attachment必须含有拥有potential format features （见p4100）为 VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT的 image format
	12. 如果 linearColorAttachment特性开启且image创建为VK_IMAGE_TILING_LINEAR,则
											（1）pInputAttachments中不是VK_ATTACHMENT_UNUSED的attachment必须含有拥有potential format features （见p4100）为VK_FORMAT_FEATURE_2_LINEAR_COLOR_ATTACHMENT_BIT_NV的 image format
											（2）pColorAttachments或者pResolveAttachments中不是VK_ATTACHMENT_UNUSED的attachment必须含有拥有potential format features （见p4100）为  VK_FORMAT_FEATURE_2_LINEAR_COLOR_ATTACHMENT_BIT_NV的 image format
	13. 如果 VK_AMD_mixed_attachment_samples或者 VK_NV_framebuffer_mixed_samples特性开启，则pColorAttachments中不是VK_ATTACHMENT_UNUSED的attachment的采样数必须小于pDepthStencilAttachment（如果不为VK_ATTACHMENT_UNUSED）中attachment的采样数
	14. 如果 VK_AMD_mixed_attachment_samples或者 VK_NV_framebuffer_mixed_samples特性都没有开启，如果pResolveAttachments不是VK_ATTACHMENT_UNUSED，则pColorAttachments中不是VK_ATTACHMENT_UNUSED的attachment的采样数必须相同，
	15.  pPreserveAttachments中的每个元素不能是VK_ATTACHMENT_UNUSED，且不能是subpass description中的其他附件
	16. 如果一个附件attachment被多个 VkAttachmentReference引用，那么这些引用必须有相同的layout
	17. 如果flags包含 VK_SUBPASS_DESCRIPTION_PER_VIEW_POSITION_X_ONLY_BIT_NVX，则其还必须包含VK_SUBPASS_DESCRIPTION_PER_VIEW_ATTRIBUTES_BIT_NVX
	18.  如果flags包含VK_SUBPASS_DESCRIPTION_SHADER_RESOLVE_BIT_QCOM，则
												（1）如果pResolveAttachments不是NULL,则pResolveAttachments中的每个元素的attachment必须是VK_ATTACHMENT_UNUSED
												（2）当前的subpass必须是subpass dependence中的最后一个subpass
												（3）pInputAttachments中的每个元素必须是 VK_ATTACHMENT_UNUSED
	19. pDepthStencilAttachment 和 pColorAttachments不能同时指向同一个attachment

	*/



	VkAttachmentReference unusedAttachmentRef;//定义一个空的VkAttachmentReference
	unusedAttachmentRef.attachment = VK_ATTACHMENT_UNUSED;//attachment设置为VK_ATTACHMENT_UNUSED,说明当前reference的attachment是空的
	unusedAttachmentRef.layout = VK_IMAGE_LAYOUT_UNDEFINED;
	/*
	1.如果attachment是VK_ATTACHMENT_UNUSED，则layout不能为 VK_IMAGE_LAYOUT_UNDEFINED,VK_IMAGE_LAYOUT_PREINITIALIZED, 或者 VK_IMAGE_LAYOUT_PRESENT_SRC_KHR
	2.如果attachment是VK_ATTACHMENT_UNUSED，且separateDepthStencilLayouts特性没有开启，则layout不能为VK_IMAGE_LAYOUT_DEPTH_ATTACHMENT_OPTIMAL,
				VK_IMAGE_LAYOUT_DEPTH_READ_ONLY_OPTIMAL, VK_IMAGE_LAYOUT_STENCIL_ATTACHMENT_OPTIMAL, 或VK_IMAGE_LAYOUT_STENCIL_READ_ONLY_OPTIMAL
	3.如果synchronization2特性没有开启，则layout不能为VK_IMAGE_LAYOUT_ATTACHMENT_OPTIMAL_KHR 或者 VK_IMAGE_LAYOUT_READ_ONLY_OPTIMAL_KHR
	4. 如果attachmentFeedbackLoopLayout特性没有开启，则layout不能为VK_IMAGE_LAYOUT_ATTACHMENT_FEEDBACK_LOOP_OPTIMAL_EXT
	5. 如果dynamicRenderingLocalRead特性没有开启，则layout不能为VK_IMAGE_LAYOUT_RENDERING_LOCAL_READ_KHR
	6. layout必须是合法的值

	*/


	VK_SUBPASS_EXTERNAL;//指明是一个外部的subpass
	VkSubpassDependency subpassDependency;//定义一个空的VkSubpassDependency,VkSubpassDependency作用：
	//当srcSubpass和dstSubpass一致时，VkSubpassDependency相当于定义了一个pipeline barriers，当不一致时才定义了提交到队列的subpass的依赖关系，如果srcSubpass为VK_SUBPASS_EXTERNAL，
	//则第一个同步域为 vkCmdBeginRenderPass提交顺序之前的所有命令，如果dstSubpass为 VK_SUBPASS_EXTERNAL,则第二个同步域为 vkCmdEndRenderPass提交顺序之后的所有命令，主要限制这些subpass对附件load，store以及resolve操作的管线状态
	subpassDependency.srcSubpass = VK_SUBPASS_EXTERNAL;
	subpassDependency.srcAccessMask = VK_ACCESS_NONE;
	subpassDependency.srcStageMask = VK_PIPELINE_STAGE_NONE;
	subpassDependency.dstSubpass = 0;
	subpassDependency.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
	subpassDependency.dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
	subpassDependency.dependencyFlags = 0;

	/*
	有效用法：
	1.特性和管线状态的匹配，见同步章节。
	2.如果 synchronization2特性没有开启，则srcStageMask和dstStageMask不能为0
	3.如果  VK_NV_ray_tracing拓展或者 rayTracingPipeline特性没有开启，则srcStageMask和dstStageMask不能包含 VK_PIPELINE_STAGE_RAY_TRACING_SHADER_BIT_KHR
	4.srcSubpass必须小于dstSubpass,除非其中有一个为VK_SUBPASS_EXTERNAL，不能两个都是VK_SUBPASS_EXTERNAL
	5.如果srcSubpass等于dstSubpass，如果srcStageMask包含 framebuffer-space stage,则dstStageMask也必须包含framebuffer-space stage
	6.访问控制和管线状态需要匹配，见同步章节
	7.如果srcSubpass等于dstSubpass，如果srcStageMask和dstStageMask都包含 framebuffer-space stage,则 dependencyFlags必须包含VK_DEPENDENCY_BY_REGION_BIT
	8.如果 dependencyFlags包含VK_DEPENDENCY_VIEW_LOCAL_BIT，则srcSubpass和dstSubpass不能是VK_SUBPASS_EXTERNAL
	9.如果srcSubpass等于dstSubpass，且该subpass的view mask有超过一个bit位设置，则dependencyFlags必须包含VK_DEPENDENCY_VIEW_LOCAL_BIT
	*/


	{
		VkCommandBuffer cmdbuf;
		//动态开启非附件（以loop标识创建的附件）写入，只在以含有VK_DYNAMIC_STATE_ATTACHMENT_FEEDBACK_LOOP_ENABLE_EXT动态状态创建的pipeline中使用
		vkCmdSetAttachmentFeedbackLoopEnableEXT(cmdbuf, VkImageAspectFlagBits::VK_IMAGE_ASPECT_COLOR_BIT);
		/*
		 1.attachmentFeedbackLoopDynamicState特性必须开启
		 2.aspectMask只能包含VK_IMAGE_ASPECT_NONE, VK_IMAGE_ASPECT_COLOR_BIT,VK_IMAGE_ASPECT_DEPTH_BIT, 以及 VK_IMAGE_ASPECT_STENCIL_BIT
		 2.如果attachmentFeedbackLoopLayout特性没有开启，则aspectMask只能为VK_IMAGE_ASPECT_NONE
		*/
	}

	//创建render pass
	vkCreateRenderPass(device, &renderPassCreateInfo, nullptr, &renderPass);

	vkDestroyRenderPass(device, renderPass, nullptr);











	//创建render pass 2

	VkRenderPassCreateInfo2 renderPassCreateInfo2{};
	renderPassCreateInfo2.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO_2;
	renderPassCreateInfo2.attachmentCount = 0;
	renderPassCreateInfo2.pAttachments = VK_NULL_HANDLE;
	renderPassCreateInfo2.dependencyCount = 0;
	renderPassCreateInfo2.pDependencies = VK_NULL_HANDLE;
	renderPassCreateInfo2.subpassCount = 0;
	renderPassCreateInfo2.pSubpasses = VK_NULL_HANDLE;
	renderPassCreateInfo2.correlatedViewMaskCount = 0;
	renderPassCreateInfo2.pCorrelatedViewMasks = VK_NULL_HANDLE;
	renderPassCreateInfo2.flags = 0;
	RenderPassCreateInfo2Ext renderPassCreateInfo2Ext{};
	renderPassCreateInfo2.pNext = &renderPassCreateInfo2Ext.renderPassCreationControlEXT;
	/*
	合法用法：
	1.只要两个subpass有访问相同附件的相同区域，且其中一个存在写操作，则必须定义一个依赖关系
	2.如果任何pInputAttachments, pColorAttachments,pResolveAttachments 或者 pDepthStencilAttachment, pPreserveAttachments的attachment的内存存在重叠，则该attachment对应的附件的flags必须包含VK_ATTACHMENT_DESCRIPTION_MAY_ALIAS_BIT
	3.如果任何pInputAttachments, pColorAttachments,pResolveAttachments 或者 pDepthStencilAttachment, pPreserveAttachments的attachment不是VK_ATTACHMENT_UNUSED,则attachment必须小于attachmentCount
	4.如果 VkRenderPassFragmentDensityMapCreateInfoEXT包含在pNext中且fragmentDensityMapAttachment且attachment对应的附件不是VK_ATTACHMENT_UNUSED，则该attachment必须小于attachmentCount
	5.如果VkSubpassDescriptionDepthStencilResolve包含在pNext中且pDepthStencilResolveAttachment不是NULL且其attachment对应的附件不是VK_ATTACHMENT_UNUSED，则该attachment必须小于attachmentCount
	6.对于任何 pAttachments 的 loadOp 加载操作为 VK_ATTACHMENT_LOAD_OP_CLEAR的附件，对于这个附件的第一次使用的布局不能是VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL 或者VK_IMAGE_LAYOUT_DEPTH_STENCIL_READ_ONLY_OPTIMAL或者VK_IMAGE_LAYOUT_DEPTH_READ_ONLY_STENCIL_ATTACHMENT_OPTIMAL
	7.对于任何 pAttachments 的stencilLoadOp加载操作为 VK_ATTACHMENT_LOAD_OP_CLEAR的附件，对于这个附件的第一次使用的布局不能是VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL 或者VK_IMAGE_LAYOUT_DEPTH_STENCIL_READ_ONLY_OPTIMAL或者 VK_IMAGE_LAYOUT_DEPTH_ATTACHMENT_STENCIL_READ_ONLY_OPTIMAL
	8.如果 pDependencies的srcSubpass以及dstSubpass不等于VK_SUBPASS_EXTERNAL，则srcStageMask以及dstStageMask必须被pipelineBindPoint绑定的pipeline支持
	9.pCorrelatedViewMasks中不能含有位重叠的两个view mask
	10.如果所有subpass的VkSubpassDescription2::viewMask为0，则correlatedViewMaskCount必须为0，任何subpass的VkSubpassDescription2::viewMask要么全为0，要么全不为0，如果全为0，则pDependencies的flags不能含有VK_DEPENDENCY_VIEW_LOCAL_BIT
	11.如果pDependencies的某个dependence的srcSubpass等于dstSubpass，且如果对应的subpass的 viewMask包含不止一个位，则该dependence需要包含VK_DEPENDENCY_VIEW_LOCAL_BIT
	12.如果 pSubpasses的 pInputAttachments的attachment对应的VkRenderPassCreateInfo2.pAttachments不是 VK_ATTACHMENT_UNUSED，则该subpass的pInputAttachments的aspectMask必须包含在VkRenderPassCreateInfo2.pAttachments所含有的aspectMask之中
	13.任何denpendence的srcSubpass和dstSubpass必须小于subpassCount
	14.如果pAttachments的任何附件在某subpass中用作 fragment shading rate attachment，则该附件就不能在该render pass中用作其他的附件，且它的loadOp也不能为VK_ATTACHMENT_LOAD_OP_CLEAR，且必须拥有potential format features包含VK_FORMAT_FEATURE_FRAGMENT_SHADING_RATE_ATTACHMENT_BIT_KHR的image format
	15.如果flags 包含 VK_RENDER_PASS_CREATE_TRANSFORM_BIT_QCOM，pSubpasses的某个subpass的pNext中含有VkFragmentShadingRateAttachmentInfoKHR，且该结构体的 pFragmentShadingRateAttachment不为NULL,则该参数对应的attachment必须是VK_ATTACHMENT_UNUSED
	16.如果一个管线以片段着色器阶段创建，且VK_QCOM_render_pass_shader_resolve拓展开启，如果subpass含有任何input attachments或者subpass description中含有VK_SUBPASS_DESCRIPTION_FRAGMENT_REGION_BIT_QCOM，则该input attachments的采样数等于rasterizationSamples
	17.如果一个管线以片段着色器阶段创建，且VK_QCOM_render_pass_shader_resolve拓展开启，如果subpass description中含有VK_SUBPASS_DESCRIPTION_FRAGMENT_REGION_BIT_QCOM，则sampleShadingEnable必须为VK_FALSE
	18.如果flags包含VK_SUBPASS_DESCRIPTION_SHADER_RESOLVE_BIT_QCOM，则
											（1）如果pResolveAttachments不是NULL,则每个 resolve attachment必须是VK_ATTACHMENT_UNUSED
											（2）如果pDepthStencilResolveAttachment不是NULL,则depth/stencil resolve attachment必须是VK_ATTACHMENT_UNUSED
											（3）subpass必须是subpass依赖链中的最后一个subpass
	19.如果pSubpasses的某个subpass的 pDepthStencilAttachment对应的attachment附件不是VK_ATTACHMENT_UNUSED,则
											（1）如果其 pDepthStencilAttachment对应的结构体中的layout是VK_IMAGE_LAYOUT_DEPTH_ATTACHMENT_OPTIMAL 或者 VK_IMAGE_LAYOUT_DEPTH_READ_ONLY_OPTIMAL,且在该结构体的pNext中没有VkAttachmentReferenceStencilLayout，则 attachment对应的pAttachments的format不能同时含有深度和模板两个成分
											（2）如果其 pDepthStencilAttachment对应的结构体中的layout是VK_IMAGE_LAYOUT_STENCIL_ATTACHMENT_OPTIMAL 或者VK_IMAGE_LAYOUT_STENCIL_READ_ONLY_OPTIMAL，则 attachment对应的pAttachments的format只能含有模板成分
											（3）如果其 pDepthStencilAttachment对应的结构体中的layout是VK_IMAGE_LAYOUT_DEPTH_ATTACHMENT_OPTIMAL或者VK_IMAGE_LAYOUT_DEPTH_READ_ONLY_OPTIMAL，则 attachment对应的pAttachments的format不能只能含有模板成分
	20.如果pSubpasses的某个subpass引用的 pResolveAttachment的format为VK_FORMAT_UNDEFINED,则VkRenderPassFragmentDensityMapCreateInfoEXT::fragmentDensityMapAttachment->attachment 必须为VK_ATTACHMENT_UNUSED
	21.如果 attachmentCount，subpassCount，correlatedViewMaskCount以及dependencyCount不为0，则其对应的数组指针必须是含有有效数据的数组指针
	*/





	VkAttachmentDescription2 attachmentDescription2{};
	attachmentDescription2.sType = VK_STRUCTURE_TYPE_ATTACHMENT_DESCRIPTION_2;
	attachmentDescription2.format = VK_FORMAT_R8G8B8A8_UNORM;
	attachmentDescription2.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
	attachmentDescription2.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;
	attachmentDescription2.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
	attachmentDescription2.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
	attachmentDescription2.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
	attachmentDescription2.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
	attachmentDescription2.flags = 0;
	attachmentDescription2.samples = VK_SAMPLE_COUNT_1_BIT;

	VkAttachmentDescriptionStencilLayout stencilLayout{};
	stencilLayout.pNext = nullptr;
	stencilLayout.sType = VK_STRUCTURE_TYPE_ATTACHMENT_DESCRIPTION_STENCIL_LAYOUT;
	stencilLayout.stencilInitialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
	stencilLayout.stencilFinalLayout = VK_IMAGE_LAYOUT_STENCIL_ATTACHMENT_OPTIMAL;
	/*
	1.stencilInitialLayout和stencilFinalLayout不能为VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL,
									VK_IMAGE_LAYOUT_DEPTH_ATTACHMENT_OPTIMAL, VK_IMAGE_LAYOUT_DEPTH_READ_ONLY_OPTIMAL,
									VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL,
									VK_IMAGE_LAYOUT_DEPTH_STENCIL_READ_ONLY_OPTIMAL,
									VK_IMAGE_LAYOUT_DEPTH_ATTACHMENT_STENCIL_READ_ONLY_OPTIMAL, 或者
									VK_IMAGE_LAYOUT_DEPTH_READ_ONLY_STENCIL_ATTACHMENT_OPTIMAL
	2.stencilFinalLayout不能为VK_IMAGE_LAYOUT_UNDEFINED 或者VK_IMAGE_LAYOUT_PREINITIALIZED

	*/
	attachmentDescription2.pNext = &stencilLayout;//pNext中可以包含VkExternalFormatANDROID和VkAttachmentDescriptionStencilLayout
	/*
	有效用法：
	1.类比VkAttachmentDescription的用法
	2.如果separateDepthStencilLayouts特性开启，且format是一个depth/stencil的format，则initialLayout和finalLayout能够只设置depth的layout也可以depth/stencil一起设置，stencil的layout可以在pNext中的VkAttachmentDescriptionStencilLayout
	中进行指定（如果有的话），如果format只是stencil的format，则initialLayout和finalLayout只能设置为stencil的layout，且在pNext中的VkAttachmentDescriptionStencilLayout中指定（如果有的话），如果没有则在initialLayout和finalLayout中指定

	3. 如果format包含color以及depth内容，且loadOp为VK_ATTACHMENT_LOAD_OP_LOAD，则initialLayout不能是VK_IMAGE_LAYOUT_UNDEFINED
	4. finalLayout 不能是 VK_IMAGE_LAYOUT_UNDEFINED 或者VK_IMAGE_LAYOUT_PREINITIALIZED
	5. 如果format是color格式，initialLayout和finalLayout 不能是VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL 或者VK_IMAGE_LAYOUT_DEPTH_STENCIL_READ_ONLY_OPTIMAL，
															 VK_IMAGE_LAYOUT_DEPTH_ATTACHMENT_STENCIL_READ_ONLY_OPTIMAL 或者
															 VK_IMAGE_LAYOUT_DEPTH_READ_ONLY_STENCIL_ATTACHMENT_OPTIMAL，
															 VK_IMAGE_LAYOUT_DEPTH_ATTACHMENT_OPTIMAL, VK_IMAGE_LAYOUT_DEPTH_READ_ONLY_OPTIMAL,
															 VK_IMAGE_LAYOUT_STENCIL_ATTACHMENT_OPTIMAL, 或者
															 VK_IMAGE_LAYOUT_STENCIL_READ_ONLY_OPTIMAL
	6. 如果format是depth/stencil格式，initialLayout和finalLayout不能是VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL
	7. 如果 separateDepthStencilLayouts（depth和stencil布局是否能分开）特性没有开启，那么 initialLayout以及finalLayout不能是
																			VK_IMAGE_LAYOUT_DEPTH_ATTACHMENT_OPTIMAL, VK_IMAGE_LAYOUT_DEPTH_READ_ONLY_OPTIMAL,
																			VK_IMAGE_LAYOUT_STENCIL_ATTACHMENT_OPTIMAL,或者
																			VK_IMAGE_LAYOUT_STENCIL_READ_ONLY_OPTIMAL,
	8. 如果format是depth/stencil格式，且含有depth和stencil数据或者只含有depth数据，则initialLayout和finalLayout不能是VK_IMAGE_LAYOUT_STENCIL_ATTACHMENT_OPTIMAL 或者
																								  VK_IMAGE_LAYOUT_STENCIL_READ_ONLY_OPTIMAL
	9. 如果synchronization2特性未开启，initialLayout和finalLayout不能是VK_IMAGE_LAYOUT_ATTACHMENT_OPTIMAL_KHR 或者 VK_IMAGE_LAYOUT_READ_ONLY_OPTIMAL_KHR
	10. 如果attachmentFeedbackLoopLayout特性未开启，initialLayout和finalLayout不能是VK_IMAGE_LAYOUT_ATTACHMENT_FEEDBACK_LOOP_OPTIMAL_EXT
	11. samples必须是必须和image创建时候的合法的samples值
	12.如果pNext中不含VkAttachmentDescriptionStencilLayout，则format含有stencil的部分，且stencilLoadOp 是 VK_ATTACHMENT_LOAD_OP_LOAD,则 initialLayout 不能为 VK_IMAGE_LAYOUT_UNDEFINED
	13.如果pNext中含VkAttachmentDescriptionStencilLayout，则format含有stencil的部分，且stencilLoadOp 是 VK_ATTACHMENT_LOAD_OP_LOAD,则 VkAttachmentDescriptionStencilLayout::stencilInitialLayout 不能是VK_IMAGE_LAYOUT_UNDEFINED
	14.如果format为 depth/stencil 的其含有depth和stencil部分，则initialLayout和finalLayout是initialLayout is VK_IMAGE_LAYOUT_DEPTH_ATTACHMENT_OPTIMAL 或者VK_IMAGE_LAYOUT_DEPTH_READ_ONLY_OPTIMAL，则pNext中必须含有VkAttachmentDescriptionStencilLayout
	15.如果pNext中不含VkAttachmentDescriptionStencilLayout，且format只含stencil部分，则initialLayout和finalLayout不能是VK_IMAGE_LAYOUT_DEPTH_ATTACHMENT_OPTIMAL 或 VK_IMAGE_LAYOUT_DEPTH_READ_ONLY_OPTIMAL
	16. 如果 externalFormatResolve 没有开启, format 不能为 VK_FORMAT_UNDEFINED
	17.如果format 是 VK_FORMAT_UNDEFINED, 就必须在pNext中包含一个externalFormat不为0的VkExternalFormatANDROID


	*/

	renderPassCreateInfo2.pAttachments = &attachmentDescription2;



	//subpass 描述2
	VkSubpassDescription2 subpassDescription2{};
	subpassDescription2.sType = VK_STRUCTURE_TYPE_SUBPASS_DESCRIPTION_2;
	subpassDescription2.viewMask = 0;
	subpassDescription2.flags = 0;
	subpassDescription2.inputAttachmentCount = 0;
	subpassDescription2.pInputAttachments = VK_NULL_HANDLE;
	subpassDescription2.colorAttachmentCount = 0;
	subpassDescription2.pColorAttachments = VK_NULL_HANDLE;
	subpassDescription2.pResolveAttachments = VK_NULL_HANDLE;
	subpassDescription2.pDepthStencilAttachment = VK_NULL_HANDLE;
	subpassDescription2.preserveAttachmentCount = 0;
	subpassDescription2.pPreserveAttachments = VK_NULL_HANDLE;
	subpassDescription2.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;//指明该subpass支持的pipeline类型
	SubpassDesctiption2Ext subpassDesctiption2Ext{};

	//指明subpass的depth和stencil的resolve信息
	VkSubpassDescriptionDepthStencilResolve& depthStencilResolve = subpassDesctiption2Ext.subpassDescriptionDepthStencilResolve;
	depthStencilResolve.depthResolveMode = VK_RESOLVE_MODE_NONE;//depth的resolve模式
	depthStencilResolve.stencilResolveMode = VK_RESOLVE_MODE_NONE;//stencil的resolve模式
	//depthStencilResolve.pNext = nullptr;//已经设置好了，这里便不再设置了
	depthStencilResolve.sType = VK_STRUCTURE_TYPE_SUBPASS_DESCRIPTION_DEPTH_STENCIL_RESOLVE;
	depthStencilResolve.pDepthStencilResolveAttachment = VK_NULL_HANDLE;//为空或者有效的VkAttachmentReference2指针，这里直接设为空
	/*
	VkSubpassDescriptionDepthStencilResolve合法用法：
	1.如果pDepthStencilResolveAttachment 不是NULL 且不为VK_ATTACHMENT_UNUSED, 则：
													（1）pDepthStencilAttachment 不能为 NULL或者为VK_ATTACHMENT_UNUSED
													（2）pDepthStencilAttachment的采样数不能为VK_SAMPLE_COUNT_1_BIT
													（3）pDepthStencilResolveAttachment的采样数必须为VK_SAMPLE_COUNT_1_BIT
													（4）其image format 的potential format features必须含有VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT
													（5）如果 pDepthStencilResolveAttachment的format有depth 成分, pDepthStencilAttachment的format必须有相同数字格式的depth成分
													（6）如果 pDepthStencilResolveAttachment的format有stencil 成分, pDepthStencilAttachment的format必须有相同数字格式的stencil成分
													（7）depthResolveMode 和 stencilResolveMode 不能同时VK_RESOLVE_MODE_NONE
													（8）如果pDepthStencilResolveAttachment的format有 depth成分,则depthResolveMode 必须为VkPhysicalDeviceDepthStencilResolveProperties::supportedDepthResolveModes中的一位或者VK_RESOLVE_MODE_NONE
													（9）如果pDepthStencilResolveAttachment的format有 stencil成分,则 stencilResolveMode 必须为VkPhysicalDeviceDepthStencilResolveProperties::supportedStencilResolveModes中的一位或者VK_RESOLVE_MODE_NONE
													(10) pDepthStencilResolveAttachment的foramt有depth和stencil成分, VkPhysicalDeviceDepthStencilResolveProperties::independentResolve为VK_FALSE, 且 VkPhysicalDeviceDepthStencilResolveProperties::independentResolveNone
																为 VK_FALSE, 则depthResolveMode 和 stencilResolveMode必须相同
													(11)pDepthStencilResolveAttachment的foramt有depth和stencil成分, VkPhysicalDeviceDepthStencilResolveProperties::independentResolve为VK_FALSE, 且 VkPhysicalDeviceDepthStencilResolveProperties::independentResolveNone
																为 VK_TRUE, 则depthResolveMode 和 stencilResolveMode必须相同或者其中一个必须为 VK_RESOLVE_MODE_NONE


	2.如果VkSubpassDescription2的pNext 中含有VkMultisampledRenderToSingleSampledInfoEXT 且该数据结构的multisampledRenderToSingleSampledEnable为VK_TRUE, 且pDepthStencilAttachment不是NULL且不是VK_ATTACHMENT_UNUSED，则
													（1）depthResolveMode 和stencilResolveMode不能同时为 VK_RESOLVE_MODE_NONE
													（2）如果pDepthStencilAttachment的format有depth成分, 则depthResolveMode必须为VkPhysicalDeviceDepthStencilResolveProperties::supportedDepthResolveModes 的其中一位或者VK_RESOLVE_MODE_NONE
													（3）如果pDepthStencilAttachment的format有stencil成分, 则stencilResolveMode必须为VkPhysicalDeviceDepthStencilResolveProperties::supportedStencilResolveModes 的其中一位或者VK_RESOLVE_MODE_NONE
													(10) pDepthStencilAttachment的foramt有depth和stencil成分, VkPhysicalDeviceDepthStencilResolveProperties::independentResolve为VK_FALSE, 且 VkPhysicalDeviceDepthStencilResolveProperties::independentResolveNone
																为 VK_FALSE, 则depthResolveMode 和 stencilResolveMode必须相同
													(11)pDepthStencilAttachment的foramt有depth和stencil成分, VkPhysicalDeviceDepthStencilResolveProperties::independentResolve为VK_FALSE, 且 VkPhysicalDeviceDepthStencilResolveProperties::independentResolveNone
																为 VK_TRUE, 则depthResolveMode 和 stencilResolveMode必须相同或者其中一个必须为 VK_RESOLVE_MODE_NONE

	3.常规合法性用法pDepthStencilResolveAttachment不是 NULL, 则pDepthStencilResolveAttachment必须为合法的VkAttachmentReference2指针

	*/



	//fragment shading rate attachment描述
	VkFragmentShadingRateAttachmentInfoKHR& fragmentShadingRateAttachmentInfoKHR = subpassDesctiption2Ext.fragmentShadingRateAttachmentInfoKHR;
	fragmentShadingRateAttachmentInfoKHR.sType = VK_STRUCTURE_TYPE_FRAGMENT_SHADING_RATE_ATTACHMENT_INFO_KHR;
	//fragmentShadingRateAttachmentInfoKHR.pNext = nullptr;//已经设置好了，这里便不再设置了
	fragmentShadingRateAttachmentInfoKHR.shadingRateAttachmentTexelSize = { 1,/*width*/   1/*height*/ };//指明每个texel对应的framebuffer对应位置区域大小
	fragmentShadingRateAttachmentInfoKHR.pFragmentShadingRateAttachment = VK_NULL_HANDLE;//为该subpass定义一个fragment shading rate attachment
	/*
	VkFragmentShadingRateAttachmentInfoKHR合法用法:
	1.如果pFragmentShadingRateAttachment 不是 NULL且对应的附件不是VK_ATTACHMENT_UNUSED,则
										（1）其layout必须为 VK_IMAGE_LAYOUT_GENERAL或者VK_IMAGE_LAYOUT_FRAGMENT_SHADING_RATE_ATTACHMENT_OPTIMAL_KHR
										（2） minFragmentShadingRateAttachmentTexelSize.width <= shadingRateAttachmentTexelSize.width (必须为2的指数幂) <= maxFragmentShadingRateAttachmentTexelSize.width
										（3）minFragmentShadingRateAttachmentTexelSize.height <= shadingRateAttachmentTexelSize.height (必须为2的指数幂) <= maxFragmentShadingRateAttachmentTexelSize.height
										（4）(shadingRateAttachmentTexelSize.width / shadingRateAttachmentTexelSize.height) <=maxFragmentShadingRateAttachmentTexelSizeAspectRatio
										（5）(shadingRateAttachmentTexelSize.height / shadingRateAttachmentTexelSize.width) <=maxFragmentShadingRateAttachmentTexelSizeAspectRatio

	*/


	// VkMultisampledRenderToSingleSampledInfoEXT
	VkMultisampledRenderToSingleSampledInfoEXT& multisampledRenderToSingleSampledInfoEXT = subpassDesctiption2Ext.multisampledRenderToSingleSampledInfoEXT;
	multisampledRenderToSingleSampledInfoEXT.sType = VK_STRUCTURE_TYPE_MULTISAMPLED_RENDER_TO_SINGLE_SAMPLED_INFO_EXT;
	//multisampledRenderToSingleSampledInfoEXT.pNext = nullptr;//已经设置好了，这里便不再设置了
	multisampledRenderToSingleSampledInfoEXT.rasterizationSamples = VK_SAMPLE_COUNT_4_BIT;//控制是否执行对单采样附件的多采样渲染。该值不能为 VK_SAMPLE_COUNT_1_BIT
	multisampledRenderToSingleSampledInfoEXT.multisampledRenderToSingleSampledEnable = VK_FALSE;//指明光栅化的采样数
	/*
	1.如果该结构体加到VkRenderingInfo的pNext中, 任何VkRenderingInfo::pColorAttachments, VkRenderingInfo::pDepthAttachment, 或者VkRenderingInfo::pStencilAttachment的不是VK_NULL_HANDLE的imageView 必须至此支持rasterizationSamples
	2.如果该结构体加到VkRenderingInfo或者VkSubpassDescription2的pNext中，且multisampledRenderToSingleSampledEnable为VK_TRUE,该subpass对应的pipeline管线创建时的VkGraphicsPipelineCreateInfo::rasterizationSamples必须等于VkMultisampledRenderToSingleSampledInfoEXT::rasterizationSamples，这样该subpass的附件的采样数就可以为 VK_SAMPLE_COUNT_1_BIT，
	这样对于这些采样数为1的附件，就可以执行多采样渲染，采用临时的image来进行多重采样，通过复制进行初始化，存储前完成resolve操作
	*/



	subpassDescription2.pNext = &subpassDesctiption2Ext.fragmentShadingRateAttachmentInfoKHR;

	/*
	有效用法：
	1.类比VkSubpassDescription的用法
	2.viewMask等价于 VkRenderPassMultiviewCreateInfo::pViewMasks对应该subpass的值
	3.如果pNext中含有VkFragmentShadingRateAttachmentInfoKHR，且其pFragmentShadingRateAttachment 不是 NULL, attachment对应附件不是 VK_ATTACHMENT_UNUSED,则该subpass定义一个fragment shading rate attachment
	4.如果 pResolveAttachments任何元素的附件在 VkExternalFormatANDROID中指明，则对应的color附件将以 VK_RESOLVE_MODE_EXTERNAL_FORMAT_DOWNSAMPLE_ANDROID.处理到resolve附件中
	5.如果 nullColorAttachmentWithExternalFormatResolve 限制是 VK_TRUE，则color附件中的值会在渲染开始前从resolve附件中加载（这个限制的作用不是很清楚）


	6. 如果pInputAttachments的attachment不是 VK_ATTACHMENT_UNUSED，则layout不能是VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL 或者 VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL，
																															   VK_IMAGE_LAYOUT_DEPTH_ATTACHMENT_OPTIMAL
																															   或者VK_IMAGE_LAYOUT_STENCIL_ATTACHMENT_OPTIMAL，
																															   VK_IMAGE_LAYOUT_ATTACHMENT_OPTIMAL_KHR


	7. 如果 pColorAttachments或者pResolveAttachments的attachment不是 VK_ATTACHMENT_UNUSED，则layout不能是 VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL 或者VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL，
																										  VK_IMAGE_LAYOUT_DEPTH_ATTACHMENT_STENCIL_READ_ONLY_OPTIMAL 或者
																										  VK_IMAGE_LAYOUT_DEPTH_READ_ONLY_STENCIL_ATTACHMENT_OPTIMAL，
																										  VK_IMAGE_LAYOUT_DEPTH_ATTACHMENT_OPTIMAL,VK_IMAGE_LAYOUT_DEPTH_READ_ONLY_OPTIMAL,
																										  VK_IMAGE_LAYOUT_STENCIL_ATTACHMENT_OPTIMAL, 或者 VK_IMAGE_LAYOUT_STENCIL_READ_ONLY_OPTIMAL，
																										  VK_IMAGE_LAYOUT_READ_ONLY_OPTIMAL_KHR

	8. 如果 pDepthStencilAttachment的attachment不是 VK_ATTACHMENT_UNUSED，则layout不能是VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL 或者VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL
	9.如果 pDepthStencilAttachment的attachment不是 VK_ATTACHMENT_UNUSED，且pNext中含有VkAttachmentReferenceStencilLayout，则该附件的layout不能是VK_IMAGE_LAYOUT_STENCIL_ATTACHMENT_OPTIMAL 或者VK_IMAGE_LAYOUT_STENCIL_READ_ONLY_OPTIMAL


	10. pipelineBindPoint必须是VK_PIPELINE_BIND_POINT_GRAPHICS 或者VK_PIPELINE_BIND_POINT_SUBPASS_SHADING_HUAWEI
	11. colorAttachmentCount必须小于等于VkPhysicalDeviceLimits::maxColorAttachments
	12. 如果一个attachment在render pass中的第一次使用作为input attachment，而且在该subpass中不是作为color 或者 depth/stencil附件，则其的loadOp不能是 VK_ATTACHMENT_LOAD_OP_CLEAR
	13. 如果pResolveAttachments不是NULL,且其中的元素对应的resolve attachment也不是VK_ATTACHMENT_UNUSED,则其中的元素对应的resolve attachment的采样数必须是VK_SAMPLE_COUNT_1_BIT
	14.如果 externalFormatResolve 没开启且pResolveAttachments 不是 NULL, 每个不是VK_ATTACHMENT_UNUSED的resolve attachment,对应的color attachment 不能是 VK_ATTACHMENT_UNUSED
	15.如果nullColorAttachmentWithExternalFormatResolve 是 VK_FALSE 且pResolveAttachments 不是NULL, 每个VK_FORMAT_UNDEFINED的resolve attachment 对应的 color attachment 不能是VK_ATTACHMENT_UNUSED
	16.如果nullColorAttachmentWithExternalFormatResolve 是VK_TRUE 且pResolveAttachments不是 NULL, 每个VK_FORMAT_UNDEFINED的resolve attachment 对应的 color attachment 必须是VK_ATTACHMENT_UNUSED
VK_ATTACHMENT_UNUSED

	17.如果 externalFormatResolve 没开启且 pResolveAttachments 不是 NULL, 每个不是VK_ATTACHMENT_UNUSED的resolve attachment对应的color attachment的采样数不能为 VK_SAMPLE_COUNT_1_BIT
	18.如果externalFormatResolve 没有开启， 每个pResolveAttachments的format必须和其对应的color attachment的format相同
	19.如果multisampledRenderToSingleSampled 特性未开启, 所有pColorAttachments 中不是 VK_ATTACHMENT_UNUSED 必须为相同的采样数

	20.  pInputAttachments中不是VK_ATTACHMENT_UNUSED的attachment且在 externalFormatResolve 特性没有开启，nullColorAttachmentWithExternalFormatResolve 为 VK_FALSE
			VkExternalFormatANDROID::externalFormat不含有非零值其中任意一个满足的情况下，必须含有拥有potential format features （见p4100）至少为VK_FORMAT_FEATURE_COLOR_ATTACHMENT_BIT 或者VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT的 image format
	21. pColorAttachments或者pResolveAttachments中不是VK_ATTACHMENT_UNUSED的attachment必须含有拥有potential format features （见p4100）为 VK_FORMAT_FEATURE_COLOR_ATTACHMENT_BIT的 image format
	22. pDepthStencilAttachment 不是 NULL 且 其attachment 不是 VK_ATTACHMENT_UNUSED， 则attachment必须含有拥有potential format features （见p4100）为 VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT的 image format

	23. 如果 linearColorAttachment特性开启且image创建为VK_IMAGE_TILING_LINEAR,则
											（1）pInputAttachments中不是VK_ATTACHMENT_UNUSED的attachment必须含有拥有potential format features （见p4100）为VK_FORMAT_FEATURE_2_LINEAR_COLOR_ATTACHMENT_BIT_NV的 image format
											（2）pColorAttachments或者pResolveAttachments中不是VK_ATTACHMENT_UNUSED的attachment必须含有拥有potential format features （见p4100）为  VK_FORMAT_FEATURE_2_LINEAR_COLOR_ATTACHMENT_BIT_NV的 image format
	24. 如果 VK_AMD_mixed_attachment_samples或者 VK_NV_framebuffer_mixed_samples特性开启，则pColorAttachments中不是VK_ATTACHMENT_UNUSED的attachment的采样数必须小于pDepthStencilAttachment（如果不为VK_ATTACHMENT_UNUSED）中attachment的采样数
	25.如果pNext中含有multisampledRenderToSingleSampledEnable为VK_TRUE的VkMultisampledRenderToSingleSampledInfoEXT，则
											（1） 所有 pColorAttachments 和 pDepthStencilAttachment 不是VK_ATTACHMENT_UNUSED 的采样数必须为 VK_SAMPLE_COUNT_1_BIT 或者等于VkMultisampledRenderToSingleSampledInfoEXT::rasterizationSamples
											（2）如果pDepthStencilAttachment不是 NULL, 且不是 VK_ATTACHMENT_UNUSED, 且采样数为VK_SAMPLE_COUNT_1_BIT, 则 pNext 中也必须包含pDepthStencilResolveAttachment为 NULL 或者 VK_ATTACHMENT_UNUSED的VkSubpassDescriptionDepthStencilResolve

	26. 如果 VK_AMD_mixed_attachment_samples拓展或者 VK_NV_framebuffer_mixed_samples拓展以及 multisampledRenderToSingleSampled都没有开启，如果pDepthStencilAttachment 或者 pColorAttachments不是VK_ATTACHMENT_UNUSED的attachment的采样数必须相同，


	27.  pPreserveAttachments中的每个元素不能是VK_ATTACHMENT_UNUSED，且不能是subpass description中的其他附件
	28. 如果一个附件attachment被多个 VkAttachmentReference2引用，那么这些引用必须有相同的layout
	29. 如果flags包含 VK_SUBPASS_DESCRIPTION_PER_VIEW_POSITION_X_ONLY_BIT_NVX，则其还必须包含VK_SUBPASS_DESCRIPTION_PER_VIEW_ATTRIBUTES_BIT_NVX
	30.如果pInputAttachments中的附件不是VK_ATTACHMENT_UNUSED,则
															（1）aspectMask 必须是合法的 VkImageAspectFlagBits组合
															（2） aspectMask 不能为 0
															（3）aspectMask 不能包含 VK_IMAGE_ASPECT_METADATA_BIT
															（4）aspectMask 不能含 VK_IMAGE_ASPECT_MEMORY_PLANE_i_BIT_EXT对于index i


	31. pDepthStencilAttachment 和 pColorAttachments不能同时指向同一个attachment
	32.viewMask值的最大有效位的 必须小于maxMultiviewViewCount，如果multiview 特性没有开启, 则viewMask 必须为 0
	33.如果externalFormatResolve 开启且 pResolveAttachments不是NULL, 则
															（1）如果colorAttachmentCount 不是 1,pResolveAttachments中不是VK_ATTACHMENT_UNUSED的format不能为 VK_FORMAT_UNDEFINED
															（2）任何pResolveAttachments 中不是 VK_ATTACHMENT_UNUSED 但format却是 VK_FORMAT_UNDEFINED,且其对应的pColorAttachments的color附件不是 VK_ATTACHMENT_UNUSED, 则该color附件的采样数必须为1
															（3）任何pResolveAttachments 中不是 VK_ATTACHMENT_UNUSED 但format却是 VK_FORMAT_UNDEFINED，viewMask必须为0
															（4）任何pResolveAttachments 中不是 VK_ATTACHMENT_UNUSED 但format却是 VK_FORMAT_UNDEFINED，VkFragmentShadingRateAttachmentInfoKHR::pFragmentShadingRateAttachment 必须是NULL 或者对应到一个VK_ATTACHMENT_UNUSED附件的 VkAttachmentReference2
															（5）任何pResolveAttachments 中不是 VK_ATTACHMENT_UNUSED 但format却是 VK_FORMAT_UNDEFINED，在该subpass中其pInputAttachments 引用到 color attachment 或者 resolve attachment 不能包含 VK_IMAGE_ASPECT_PLANE_i_BIT 对任何aspectMask的index i

	34.常规合法性用法如pColorAttachments是colorAttachmentCount个合法颜色附件引用的数组首地址指针等等






	*/



	VkAttachmentReference2 colorAttachmentRef2{};
	colorAttachmentRef2.sType = VK_STRUCTURE_TYPE_ATTACHMENT_REFERENCE_2;
	colorAttachmentRef2.attachment = 0;// 是VkRenderPassCreateInfo2::pAttachments的索引, 或者 VK_ATTACHMENT_UNUSED 表明该附件没有使用
	colorAttachmentRef2.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
	colorAttachmentRef2.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

	VkAttachmentReferenceStencilLayout referenceStencilLayout;
	referenceStencilLayout.sType = VK_STRUCTURE_TYPE_ATTACHMENT_REFERENCE_STENCIL_LAYOUT;
	referenceStencilLayout.pNext = nullptr;
	referenceStencilLayout.stencilLayout = VK_IMAGE_LAYOUT_UNDEFINED;/*
	1.stencilLayout 不能为 VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_PREINITIALIZED,
							VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL, VK_IMAGE_LAYOUT_DEPTH_ATTACHMENT_OPTIMAL,
							VK_IMAGE_LAYOUT_DEPTH_READ_ONLY_OPTIMAL,
							VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL,
							VK_IMAGE_LAYOUT_DEPTH_STENCIL_READ_ONLY_OPTIMAL,
							VK_IMAGE_LAYOUT_DEPTH_ATTACHMENT_STENCIL_READ_ONLY_OPTIMAL,
							VK_IMAGE_LAYOUT_DEPTH_READ_ONLY_STENCIL_ATTACHMENT_OPTIMAL, 或者
							VK_IMAGE_LAYOUT_PRESENT_SRC_KHR
	
	*/



	colorAttachmentRef2.pNext = &stencilLayout;//可以含有VkAttachmentReferenceStencilLayout
	/*
	VkAttachmentReference2有效用法
	1.如果attachment 不是VK_ATTACHMENT_UNUSED, layout不能是VK_IMAGE_LAYOUT_UNDEFINED,VK_IMAGE_LAYOUT_PREINITIALIZED, 或者 VK_IMAGE_LAYOUT_PRESENT_SRC_KHR
	2.如果separateDepthStencilLayouts 特性没有开启, 且 attachment 不是VK_ATTACHMENT_UNUSED, layout 不能是 VK_IMAGE_LAYOUT_DEPTH_ATTACHMENT_OPTIMAL,
						VK_IMAGE_LAYOUT_DEPTH_READ_ONLY_OPTIMAL, VK_IMAGE_LAYOUT_STENCIL_ATTACHMENT_OPTIMAL, 或者VK_IMAGE_LAYOUT_STENCIL_READ_ONLY_OPTIMAL,
	3.如果synchronization2 特性没有开启, layout 不能为VK_IMAGE_LAYOUT_ATTACHMENT_OPTIMAL_KHR 或者 VK_IMAGE_LAYOUT_READ_ONLY_OPTIMAL_KHR
	4.如果attachmentFeedbackLoopLayout 特性没有开启, layout 不能为VK_IMAGE_LAYOUT_ATTACHMENT_FEEDBACK_LOOP_OPTIMAL_EXT
	5.如果dynamicRenderingLocalRead 特性没有开启, layout 不能为VK_IMAGE_LAYOUT_RENDERING_LOCAL_READ_KHR
	

	*/




	//subpass dependence 2
	VkSubpassDependency2 subpassDependency2{};
	subpassDependency2.sType = VK_STRUCTURE_TYPE_SUBPASS_DEPENDENCY_2;
	subpassDependency2.pNext = nullptr;//可以含有 VkMemoryBarrier2
	subpassDependency2.srcSubpass = VK_SUBPASS_EXTERNAL;
	subpassDependency2.srcAccessMask = VK_ACCESS_NONE;
	subpassDependency2.srcStageMask = VK_PIPELINE_STAGE_NONE;
	subpassDependency2.dstSubpass = 0;
	subpassDependency2.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
	subpassDependency2.dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
	subpassDependency2.dependencyFlags = 0;
	subpassDependency2.viewOffset = 0;
	/*
	VkSubpassDependency2合法用法：
	1.用法类比VkSubpassDependency的用法
	2.viewOffset 等效于VkRenderPassMultiviewCreateInfo::pViewOffsets 中对应subpass dependency的值
	3.如果 VkMemoryBarrier2包含在pNext中，则srcStageMask, dstStageMask, srcAccessMask,以及dstAccessMask将被忽略
	4.着色器特性和管线阶段的合法对应（如果某些着色器特性没有开启就不能包含与之对应的管线阶段），见同步章节
	5.如果synchronization2 特性没有开启, srcStageMask必须为0
	6.如果VK_NV_ray_tracing 拓展或者 rayTracingPipeline 特性其中之一开启,srcStageMask 不能包含VK_PIPELINE_STAGE_RAY_TRACING_SHADER_BIT_KHR
	7.如果 fragmentDensityMap 特性没有开启, dstStageMask不能包含VK_PIPELINE_STAGE_FRAGMENT_DENSITY_PROCESS_BIT_EXT
	8.如果 transformFeedback 特性没有开启, dstStageMask不能包含VK_PIPELINE_STAGE_TRANSFORM_FEEDBACK_BIT_EXT
	9.如果 shadingRateImage即没有开启 attachmentFragmentShadingRate 特性也没有开启, dstStageMask不能包含VK_PIPELINE_STAGE_FRAGMENT_SHADING_RATE_ATTACHMENT_BIT_KHR
	10.如果  synchronization2 特性没有开启, dstStageMask不能为0
	11.如果VK_NV_ray_tracing 拓展既没有开启rayTracingPipeline 特性也没有开启,dstStageMask 不能包含 VK_PIPELINE_STAGE_RAY_TRACING_SHADER_BIT_KHR
	12.srcSubpass 必须小于等于 dstSubpass, 除非其中之一为VK_SUBPASS_EXTERNAL，但不能同时为VK_SUBPASS_EXTERNAL,为了保证不出现循环依赖和正确的执行顺序
	13.如果srcSubpass等于dstSubpass且srcStageMask 包含framebuffer-space stage,则dstStageMask 只能包含 framebuffer-space stages
	14. srcAccessMask和 srcStageMask，dstAccessMask和 dstStageMask必须是合法的对应关系，见同步章节
	15.如果 dependencyFlags 包含 VK_DEPENDENCY_VIEW_LOCAL_BIT, srcSubpass，dstSubpass 不能等于VK_SUBPASS_EXTERNAL
	16.如果srcSubpass等于dstSubpass且srcStageMask和dstStageMask 包含framebuffer-space stage,则 dependencyFlags必须包含  VK_DEPENDENCY_BY_REGION_BIT
	17.如果viewOffset 不为 0, srcSubpass 不能等于dstSubpass
	18.如果 dependencyFlags不包含 VK_DEPENDENCY_VIEW_LOCAL_BIT, viewOffset 必须为 0
	*/

	vkCreateRenderPass2(device, &renderPassCreateInfo2, nullptr, &renderPass);

	vkDestroyRenderPass(device, renderPass, nullptr);



}



//render pass兼容
/*
	1.附件引用兼容：format 和 sample count相同, 或者都是 VK_ATTACHMENT_UNUSED 或者附件引用指针为 NULL.
	2.附件引用数组兼容：两个附件数组，其对应的附件一一对应兼容，附件数量少的数组中没有表示出来的附件被看作是VK_ATTACHMENT_UNUSED
	3.render pass兼容：两个render pass对应的color, input, resolve, 以及 depth/stencil附件引用是兼容的以及是否这些是附件除了初始和结束的image layout ， Load 和 store 操作，附件引用的 Image layout 外全部相同的。
	4.frame buffer兼容：两个frame用同一个render pass创建或者兼容的render pass创建




*/



void RenderPassTest::FrameBufferCreateTest()
{
	//创建frame buffer
	VkFramebuffer frameBuffer;
	VkFramebufferCreateInfo frameBufferCreateInfo{};
	frameBufferCreateInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
	frameBufferCreateInfo.renderPass = renderPass;
	frameBufferCreateInfo.flags = VK_FRAMEBUFFER_CREATE_IMAGELESS_BIT;//	如果不包含 VK_FRAMEBUFFER_CREATE_IMAGELESS_BIT,且attachmentCount 不是 0, 则pCreateInfo->pAttachments的每一个必须在device上创建
	//VK_FRAMEBUFFER_CREATE_IMAGELESS_BIT指定不在pAttachments中指定图像视图，仅通过VkFramebufferAttachmentImageInfo结构提供附件视图兼容性信息
	frameBufferCreateInfo.attachmentCount = 0;
	frameBufferCreateInfo.pAttachments = VK_NULL_HANDLE;//imageView的句柄数组首地址
	frameBufferCreateInfo.width = 16;
	frameBufferCreateInfo.height = 16;
	frameBufferCreateInfo.layers = 1;//如果render pass用multiview，则layers必须是一个大于subpass的设置在viewMask中最大的位索引的一个数
	VkFramebufferAttachmentsCreateInfo frameBufferAttachmentsCreateInfo{};
	frameBufferAttachmentsCreateInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_ATTACHMENTS_CREATE_INFO;
	frameBufferAttachmentsCreateInfo.pNext = nullptr;
	frameBufferAttachmentsCreateInfo.attachmentImageInfoCount = 1;
	VkFramebufferAttachmentImageInfo attachmentImageInfo{};
	attachmentImageInfo.flags = 0;//与即将用于本framebuffer的image的flags匹配
	attachmentImageInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_ATTACHMENT_IMAGE_INFO;
	attachmentImageInfo.pNext = nullptr;
	attachmentImageInfo.usage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;//与即将用于本framebuffer的image的usage匹配
	attachmentImageInfo.width = 16;//渲染时的image view的width
	attachmentImageInfo.height = 16;//渲染时的image view的height
	attachmentImageInfo.layerCount = 1;//渲染时的image view的layers
	attachmentImageInfo.viewFormatCount = 0;//是pViewFomats数组中的元素个数，与用于创建与此框架缓冲区一起使用的图像的VkImageFormatListCreateInfo：：viewFormatCount的值相匹配
	attachmentImageInfo.pViewFormats = VK_NULL_HANDLE;//是一个指向VkFormat值数组的指针，指定在创建图像视图时可以使用的所有格式，与用于创建与此框架缓冲区一起使用的图像的VkImageFormatListCreateInfo：：pViewFormats的值相匹配


	frameBufferAttachmentsCreateInfo.pAttachmentImageInfos = &attachmentImageInfo;//描述每个attachment的image信息
	frameBufferCreateInfo.pNext = nullptr;//可以含有VkFramebufferAttachmentsCreateInfo

	/*
	合法用法：
	1.绑定到subpass的管线pipeline的状态信息VkPipelineMultisampleStateCreateInfo的rasterizationSamples必须相同，如果 VkPhysicalDeviceFeatures::variableMultisampleRate位VK_FALSE,且必须被VkPhysicalDeviceLimits::framebufferNoAttachmentsSampleCounts.支持 
	2.attachmentCount必须等于renderPass中指定的attachment count
	3.如果flags不包含VK_FRAMEBUFFER_CREATE_IMAGELESS_BIT，则
														（1） 若 attachmentCount不为0, pAttachments 需要是一个attachmentCount的有效的VkImageView数组首地址指针
														（2）pAttachments中任何被renderPass用作color attachment 或者 resolve attachment 创建时必须含有VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT
														（3）pAttachments中任何被renderPass用作 depth/stencil attachment或者 depth/stencil resolve attachment 创建时必须含有 VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT
														（4）如果renderpass不为 VK_NULL_HANDLE，pAttachments中任何被renderPass用作 input attachment创建时必须含有 VK_IMAGE_USAGE_INPUT_ATTACHMENT_BIT
														（5）pAttachments中任何元素创建时的format必须与renderPass中对应的VkAttachmentDescription指定的format匹配
														（6）pAttachments中任何元素创建时的samples必须与renderPass中对应的VkAttachmentDescription指定的samples匹配
														（7）pAttachments中任何被renderPass用作  input, color, resolve, 或者 depth/stencil attachment 创建时必须有  VkImageCreateInfo::extent.width大于等于width,
																VkImageCreateInfo::extent.height大于等于height,VkImageCreateInfo::subresourceRange.layerCount大于等于layers
														（8）pAttachments中任何 fragmentDensityMapAttachment引用的元素的width必须至少大于(VkFramebufferCreateInfo.width / maxFragmentDensityTexelSize.width),
																height必须至少大于(VkFramebufferCreateInfo.height / maxFragmentDensityTexelSize.height)
														（9)如果 renderPass 有非零的 view masks,pAttachments每一个被renderPass用作fragment shading rate attachment的layerCount 为 1,或者大于view masks中最大的有效位的索引，或者大于layers
														（10）pAttachments每一个被renderPass用作fragment shading rate attachment的with至少为 （VkFramebufferCreateInfo.width / texelWidth）,texelWidth是 VkFragmentShadingRateAttachmentInfoKHR的
																shadingRateAttachmentTexelSize.width的最大值，height至少为 (VkFramebufferCreateInfo.height / texelHeight）,texelHeight是 VkFragmentShadingRateAttachmentInfoKHR的
																shadingRateAttachmentTexelSize.height的最大值
														（11）pAttachments中任何元素只能有指定一个mipmap，且创建必须为identity swizzle
														（12）pAttachments中任何元素是3D image的2D 或者2D array image view的不能含有depth/stencil format
														（13）pAttachments中任何元素创建时 VkImageViewCreateInfo::viewType不能为VK_IMAGE_VIEW_TYPE_3D
														（14）pAttachments每一个被renderPass用作fragment shading rate attachment创建时必须含有VK_IMAGE_USAGE_FRAGMENT_SHADING_RATE_ATTACHMENT_BIT_KHR
														（15）如果nullColorAttachmentWithExternalFormatResolve 为 VK_FALSE，renderPass中的subpass中的color附件有包含一个外部的format作为resolve format的resolve附件,该附件的resolve format必须等于
																		通过vkGetAndroidHardwareBufferPropertiesANDROID返回的VkAndroidHardwareBufferFormatResolvePropertiesANDROID::colorAttachmentFormat
														（16）pAttachments中任何元素的format为VK_FORMAT_UNDEFINED,则其创建时的VkExternalFormatANDROID::externalFormat必须与对应的renderPass中的VkAttachmentDescription2提供的的VkExternalFormatANDROID::externalFormat相等
	4.pAttachments中任何被renderPass用作fragment density map attachment 创建时不能含有 VK_IMAGE_CREATE_SUBSAMPLED_BIT_EXT
	5.如果 renderPass 有 fragment density map attachment 且fragmentDensityMapNonSubsampledImages 特性没有开启, pAttachments中任何附件创建时必须含有 VK_IMAGE_CREATE_SUBSAMPLED_BIT_EXT，除非该附件被renderPass用作fragment density map attachment 
	6.如果renderPass创建时 fragment density map offsets不为(0,0), pAttachments的每个元素创建时flags必须含有VK_IMAGE_CREATE_FRAGMENT_DENSITY_MAP_OFFSET_BIT_QCOM
	7.如果renderPass的view masks是非零值, pAttachments中任何被renderPass用作  input, color, resolve, 或者 depth/stencil attachment的layerCount必须大于view masks中最大的有效位的索引
	8.每一个被fragmentDensityMapAttachment引用的pAttachments的元素的layerCount必须为1或者必须大于renderPass中view masks中最大的有效位的索引如果renderPass有非零的 view masks
	9.如果renderPass的view masks是非零值,pAttachments每一个被renderPass用作fragment shading rate attachment的layerCount 为 1,或者大于view masks中最大的有效位的索引
	10.0 <= with <=  maxFramebufferWidth, 0 <= height <= maxFramebufferHeight， 0 <= layers <= maxFramebufferLayers
	11.如果renderPass的view masks是非零值，layers必须为1
	12.如果imagelessFramebuffer特性没有开启, flags不能包含VK_FRAMEBUFFER_CREATE_IMAGELESS_BIT
	13.如果flags包含VK_FRAMEBUFFER_CREATE_IMAGELESS_BIT，则
														（1） pNext 中必须含有一个VkFramebufferAttachmentsCreateInfo
														（2） pNext 中VkFramebufferAttachmentsCreateInfo的attachmentImageInfoCount必须为0或者attachmentCount
														（3） pNext 中VkFramebufferAttachmentsCreateInfo的pAttachmentImageInfos中在renderPass中用作input, color, resolve 或者 depth/stencil attachment in renderPass的width 必须大于等于VkFramebufferCreateInfo.width
														（4） pNext 中VkFramebufferAttachmentsCreateInfo的pAttachmentImageInfos中在renderPass中用作input, color, resolve 或者 depth/stencil attachment in renderPass的height 必须大于等于VkFramebufferCreateInfo.height
														（5）pNext 中VkFramebufferAttachmentsCreateInfo的pAttachmentImageInfos在renderPass中被VkRenderPassFragmentDensityMapCreateInfoEXT::fragmentDensityMapAttachment引用的width必须大于等于(VkFramebufferCreateInfo.width / maxFragmentDensityTexelSize.width)，
																		height必须大于等于(VkFramebufferCreateInfo.height / maxFragmentDensityTexelSize.height)

														（6）pNext 中VkFramebufferAttachmentsCreateInfo的pAttachmentImageInfos在renderPass中被用作fragment shading rate attachment的with至少为 （VkFramebufferCreateInfo.width / texelWidth）,texelWidth是 VkFragmentShadingRateAttachmentInfoKHR的
																shadingRateAttachmentTexelSize.width的最大值，height至少为 (VkFramebufferCreateInfo.height / texelHeight）,texelHeight是 VkFragmentShadingRateAttachmentInfoKHR的
																shadingRateAttachmentTexelSize.height的最大值，layerCount必须为1或者大于等于VkFramebufferCreateInfo.layers
														（7）renderPass的view masks是非零值,pAttachments每一个被renderPass用作fragment shading rate attachment的layerCount 为 1
														（8）如果 multiview 开启，则pNext 中VkFramebufferAttachmentsCreateInfo的pAttachmentImageInfos中任何被renderPass用作  input, color, resolve, 或者 depth/stencil attachment 的layerCount 必须大于等于renderPass 中view masks中最大的有效位的索引
														（9）如果 multiview 没有开启，则pNext 中VkFramebufferAttachmentsCreateInfo的pAttachmentImageInfos中任何被renderPass用作  input, color, resolve, 或者 depth/stencil attachment 的layerCount 必须大于等于VkFramebufferCreateInfo.layers
														（10）则pNext 中VkFramebufferAttachmentsCreateInfo的pAttachmentImageInfos中任何被renderPass用作color attachment 或者 resolve attachment 创建时必须含有VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT
														（11）则pNext 中VkFramebufferAttachmentsCreateInfo的pAttachmentImageInfos中任何被renderPass用作depth/stencil attachment 或者depth/stencil resolve attachment 创建时必须含有 VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT
														（12）则pNext 中VkFramebufferAttachmentsCreateInfo的pAttachmentImageInfos中任何被renderPass用作input attachment  创建时必须含有 VK_IMAGE_USAGE_INPUT_ATTACHMENT_BIT
														（13）pNext 中VkFramebufferAttachmentsCreateInfo的pAttachmentImageInfos的pViewFormats中至少一个元素和renderPass中对应的VkAttachmentDescription的format匹配
														（14）则pNext 中VkFramebufferAttachmentsCreateInfo的pAttachmentImageInfos中任何被renderPass用作fragment shading rate attachment  创建时必须含有 VK_IMAGE_USAGE_FRAGMENT_SHADING_RATE_ATTACHMENT_BIT_KHR

	14.如果multisampled-render-to-single-sampled对任何subpass开启, subpass中所有的 color,depth/stencil 以及 input attachments的VkAttachmentDescription::samples 或者 VkAttachmentDescription2::samples 等于VK_SAMPLE_COUNT_1_BIT 的image创建时，则
														（1）VkImageCreateInfo::flags必须含有VK_IMAGE_CREATE_MULTISAMPLED_RENDER_TO_SINGLE_SAMPLED_BIT_EXT
														（2）其format必须支持在VkMultisampledRenderToSingleSampledInfoEXT::rasterizationSamples指定的sample count
	15.如果nullColorAttachmentWithExternalFormatResolve为 VK_FALSE, 且 flags does not
include VK_FRAMEBUFFER_CREATE_IMAGELESS_BIT, the format of the color attachment for each
subpass in renderPass that includes an external format image as a resolve attachment
must have a format equal to the value of
VkAndroidHardwareBufferFormatResolvePropertiesANDROID::colorAttachmentFormat as
returned by a call to vkGetAndroidHardwareBufferPropertiesANDROID for the Android
hardware buffer that was used to create the image view use as its resolve attachment
	*/


	vkCreateFramebuffer(device, &frameBufferCreateInfo, nullptr, &frameBuffer);

	vkDestroyFramebuffer(device, frameBuffer, nullptr);

}




//color附件的读取和写出在VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT阶段，depth/stencil附件的读取和写出在VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT阶段，超采样在VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT阶段
/*
读取：
VK_ATTACHMENT_LOAD_OP_LOAD：表示附件原来的内容将以原来的值保存
VK_ATTACHMENT_LOAD_OP_CLEAR：表示附件中的内容将在render pass渲染开始前被清空
VK_ATTACHMENT_LOAD_OP_DONT_CARE：表示附件的原来内容将被忽略，其值将是未定义的
VK_ATTACHMENT_LOAD_OP_NONE_KHR：表示附件的原来内容将是未定义的，将不会被访问

写出：
VK_ATTACHMENT_STORE_OP_STORE：表示在render pass期间生成的值将被保存到附件中
VK_ATTACHMENT_STORE_OP_DONT_CARE：表示在render pass期间生成的值将被忽略，不被需要，其值将是未定义的
VK_ATTACHMENT_STORE_OP_NONE：表示在render pass期间生成的值不会被写入到附件中


超采样：
VK_RESOLVE_MODE_NONE：没有超采样
VK_RESOLVE_MODE_SAMPLE_ZERO_BIT：超采样的像素值将被设置为sample 0的值
VK_RESOLVE_MODE_AVERAGE_BIT：超采样的像素值将被设置为所有sample的平均值
VK_RESOLVE_MODE_MIN_BIT：超采样的像素值将被设置为所有sample的最小值
VK_RESOLVE_MODE_MAX_BIT：超采样的像素值将被设置为所有sample的最大值
VK_RESOLVE_MODE_EXTERNAL_FORMAT_DOWNSAMPLE_ANDROID：表示将把单个采样的颜色附件降采样为由外部安卓格式指定的Y‘CBCR格式图像，而不是多样本解析。


*/


struct RenderPassBeginInfoExt {
	VkDeviceGroupRenderPassBeginInfo deviceGroupRenderPassBeginInfo{};
	VkMultiviewPerViewRenderAreasRenderPassBeginInfoQCOM multiviewPerViewRenderAreasRenderPassBeginInfoQCOM{};
	VkRenderPassAttachmentBeginInfo renderPassAttachmentBeginInfo{};
	VkRenderPassSampleLocationsBeginInfoEXT renderPassSampleLocationsBeginInfoEXT{};
	VkRenderPassStripeBeginInfoARM renderPassStripeBeginInfoARM{};
	VkRenderPassTransformBeginInfoQCOM renderPassTransformBeginInfoQCOM{};
	RenderPassBeginInfoExt() {
		Init();
	}
	void Init() {
		deviceGroupRenderPassBeginInfo.sType = VK_STRUCTURE_TYPE_DEVICE_GROUP_RENDER_PASS_BEGIN_INFO;
		deviceGroupRenderPassBeginInfo.pNext = &multiviewPerViewRenderAreasRenderPassBeginInfoQCOM;
		multiviewPerViewRenderAreasRenderPassBeginInfoQCOM.sType = VK_STRUCTURE_TYPE_MULTIVIEW_PER_VIEW_RENDER_AREAS_RENDER_PASS_BEGIN_INFO_QCOM;
		multiviewPerViewRenderAreasRenderPassBeginInfoQCOM.pNext = &renderPassAttachmentBeginInfo;

		renderPassAttachmentBeginInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_ATTACHMENT_BEGIN_INFO;
		renderPassAttachmentBeginInfo.pNext = &renderPassSampleLocationsBeginInfoEXT;
		renderPassSampleLocationsBeginInfoEXT.sType = VK_STRUCTURE_TYPE_RENDER_PASS_SAMPLE_LOCATIONS_BEGIN_INFO_EXT;
		renderPassSampleLocationsBeginInfoEXT.pNext = &renderPassStripeBeginInfoARM;
		renderPassStripeBeginInfoARM.sType = VK_STRUCTURE_TYPE_MAX_ENUM;//这个结构体的sType没有定义
		renderPassStripeBeginInfoARM.pNext = &renderPassTransformBeginInfoQCOM;
		renderPassTransformBeginInfoQCOM.sType = VK_STRUCTURE_TYPE_RENDER_PASS_TRANSFORM_BEGIN_INFO_QCOM;
		renderPassTransformBeginInfoQCOM.pNext = nullptr;
	}

};


void RenderPassTest::RenderPassCmdTest()
{

	VkCommandBuffer cmdbuf;

	RenderPassBeginInfoExt renderPassBeginInfoExt{};

	//参考使用VK_IMAGE_CREATE_SAMPLE_LOCATIONS_COMPATIBLE_DEPTH_BIT_EXT创建的图像的深度/模板附件的深度方面的图像布局取决于用于渲染到图像子资源的最后一个样本位置，以下结构体指明采样位置
	VkRenderPassSampleLocationsBeginInfoEXT& renderPassSampleLocationsBeginInfoEXT = renderPassBeginInfoExt.renderPassSampleLocationsBeginInfoEXT;
	renderPassSampleLocationsBeginInfoEXT.attachmentInitialSampleLocationsCount = 1;

	VkAttachmentSampleLocationsEXT attachmentSampleLocationsEXT{};
	attachmentSampleLocationsEXT.attachmentIndex = 0;//如果该索引所指的附件并不是以VK_IMAGE_CREATE_SAMPLE_LOCATIONS_COMPATIBLE_DEPTH_BIT_EXT创建的，则sampleLocationsInfo中的设置则会被忽略
	VkSampleLocationsInfoEXT locationsEXTs;
	locationsEXTs.sType = VK_STRUCTURE_TYPE_SAMPLE_LOCATIONS_INFO_EXT;
	locationsEXTs.pNext = nullptr;
	locationsEXTs.sampleLocationsCount = 1;
	VkSampleLocationEXT location;
	location.x = 0;
	location.y = 0;
	locationsEXTs.pSampleLocations = &location;
	locationsEXTs.sampleLocationsPerPixel = VK_SAMPLE_COUNT_4_BIT;
	VkExtent2D locationGridSize;
	locationGridSize.height = 1;
	locationGridSize.height = 1;
	locationsEXTs.sampleLocationGridSize = locationGridSize;


	attachmentSampleLocationsEXT.sampleLocationsInfo = locationsEXTs;//是用于将给定附件的布局从附件的初始布局转换到在使用它的第一个子传递中为附件指定的图像布局的sample位置状态。


	renderPassSampleLocationsBeginInfoEXT.pAttachmentInitialSampleLocations = &attachmentSampleLocationsEXT;//是attachmentInitialSampleLocationsCount个VkAttachmentSampleLocationsEXT的数组首地址指针，指明附件的索引以及采样位置，并且每个元素指明了depth/stencil附件在subpass中的第一次使用时的自动转换布局时使用的采样位置
	renderPassSampleLocationsBeginInfoEXT.postSubpassSampleLocationsCount = 1;
	VkSubpassSampleLocationsEXT subpassSampleLocationsEXT{};
	subpassSampleLocationsEXT.subpassIndex = 0;//如果subpass没有depth/stencil附件或者该附件不是以VK_IMAGE_CREATE_SAMPLE_LOCATIONS_COMPATIBLE_DEPTH_BIT_EXT创建，且VkPhysicalDeviceSampleLocationsPropertiesEXT::variableSampleLocations 为 VK_TRUE，则 sampleLocationsInfo中的参数会被忽略
	VkSampleLocationsInfoEXT slocationsEXTs;
	slocationsEXTs.sType = VK_STRUCTURE_TYPE_SAMPLE_LOCATIONS_INFO_EXT;
	slocationsEXTs.pNext = nullptr;
	slocationsEXTs.sampleLocationsCount = 1;
	VkSampleLocationEXT slocation;
	slocation.x = 0;
	slocation.y = 0;
	slocationsEXTs.pSampleLocations = &slocation;
	slocationsEXTs.sampleLocationsPerPixel = VK_SAMPLE_COUNT_4_BIT;
	VkExtent2D slocationGridSize;
	slocationGridSize.height = 1;
	slocationGridSize.height = 1;
	locationsEXTs.sampleLocationGridSize = slocationGridSize;
	subpassSampleLocationsEXT.sampleLocationsInfo = slocationsEXTs;

	renderPassSampleLocationsBeginInfoEXT.pPostSubpassSampleLocations = &subpassSampleLocationsEXT;//是postSubpassSampleLocationsCount个VkSubpassSampleLocationsEXT的数组首地址指针，指明subpass的索引以及采样位置，每个元素指明了depth/stencil附件在subpass中的最后一次使用时的自动转换布局时使用的采样位置，额外，如果
	//VkPhysicalDeviceSampleLocationsPropertiesEXT::variableSampleLocations 为 VK_FALSE,则其中的元素必须和绑定在该subpass对应的命令缓冲区中的pipeline的采样位置相匹配，如果variableSampleLocations 为 VK_TRUE，这里面的值将不会使用



	//VkRenderPassTransformBeginInfoQCOM
	//如果要启用render pass transform,则需要包含一个VkRenderPassTransformBeginInfoQCOM结构体
	VkRenderPassTransformBeginInfoQCOM& renderPassTransformBeginInfoQCOM = renderPassBeginInfoExt.renderPassTransformBeginInfoQCOM;
	renderPassTransformBeginInfoQCOM.transform = VK_SURFACE_TRANSFORM_ROTATE_180_BIT_KHR;//指明render pass的转换方式，这里指明为旋转180°作为参考，这里只能指定transform-02871
	//为VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR, VK_SURFACE_TRANSFORM_ROTATE_90_BIT_KHR, VK_SURFACE_TRANSFORM_ROTATE_180_BIT_KHR,或者VK_SURFACE_TRANSFORM_ROTATE_270_BIT_KHR，且renderPass创建时的flags必须包含VK_RENDER_PASS_CREATE_TRANSFORM_BIT_QCOM


	//VkDeviceGroupRenderPassBeginInfo
	//如果包含了该数据结构，则将设置一个devivce mask和该device上的render areas
	VkDeviceGroupRenderPassBeginInfo& deviceGroupRenderPassBeginInfo = renderPassBeginInfoExt.deviceGroupRenderPassBeginInfo;
	deviceGroupRenderPassBeginInfo.deviceMask = 1;
	deviceGroupRenderPassBeginInfo.deviceRenderAreaCount = 1;//如果非0，则pDeviceRenderAreas将复写VkRenderPassBeginInfo::renderArea，然后为每个物理设备提供渲染区域，如果没有该结构体，则render pass实例的device mask为VkDeviceGroupCommandBufferBeginInfo::deviceMask，如果没有提供该结构体或者该值为0，则, VkRenderPassBeginInfo::renderArea应用到所有物理设备
	VkRect2D renderArea{};
	renderArea.extent.width = 1;
	renderArea.extent.height = 1;
	renderArea.offset.x = 0;
	renderArea.offset.y = 0;

	deviceGroupRenderPassBeginInfo.pDeviceRenderAreas = &renderArea;//指明每个物理设备的渲染区域
	/*
	VkDeviceGroupRenderPassBeginInfo有效用法：
	1.deviceMask不能为0，且必须为一个合法的device mask，且必须时command buffer初始device mask中的子集
	2. pDeviceRenderAreas的 offset.x， offset.y必须大于等于0， extent.width， extent.height必须大于0
	3.offset.x + extent.width必须小于等于 maxFramebufferWidth，offset.y + extent.height必须小于等于 maxFramebufferHeight，

	*/


	//VkRenderPassAttachmentBeginInfo
	VkRenderPassAttachmentBeginInfo& renderPassAttachmentBeginInfo = renderPassBeginInfoExt.renderPassAttachmentBeginInfo;
	renderPassAttachmentBeginInfo.attachmentCount = 0;
	renderPassAttachmentBeginInfo.pAttachments = VK_NULL_HANDLE;//指明每个附件所对应的image view，和创建render pass的附件一一对应
	/*
	1. pAttachments的每个元素只能指定一个mipmap，且必须以identity swizzle创建，且创建时的 VkImageViewCreateInfo::viewType不等于 VK_IMAGE_VIEW_TYPE_3D
	2.如果 multisampled-render-to-single-sampled对任何subpass开启，pAttachments的每个元素的采样数为VK_SAMPLE_COUNT_1_BIT的必须有支持VkMultisampledRenderToSingleSampledInfoEXT::rasterizationSamples的format格式
	3.pAttachments应该是attachmentCount个有效的VkImageView的句柄的数组的首地址
	*/


	// VkMultiviewPerViewRenderAreasRenderPassBeginInfoQCOM
	//如果启用multiview,且multiviewPerViewRenderAreas特性开启，则可以包含一个VkMultiviewPerViewRenderAreasRenderPassBeginInfoQCOM结构体
	VkMultiviewPerViewRenderAreasRenderPassBeginInfoQCOM& multiviewPerViewRenderAreasRenderPassBeginInfoQCOM = renderPassBeginInfoExt.multiviewPerViewRenderAreasRenderPassBeginInfoQCOM;
	multiviewPerViewRenderAreasRenderPassBeginInfoQCOM.perViewRenderAreaCount = 1;//如果不为0将复写VkRenderPassBeginInfo::renderArea 或 VkRenderingInfo::renderArea，然后为每个视图提供渲染区域，VkRenderPassBeginInfo::renderArea 或 VkRenderingInfo::renderArea则为pPerViewRenderAreas的并集，
	//且perViewRenderAreaCount必须大于render pass中VkRenderPassMultiviewCreateInfo::pViewMasks. 或者 VkRenderingInfo::viewMask指定的最大有效位的索引，如果是0，VkRenderPassBeginInfo::renderArea or VkRenderingInfo::renderArea将应用到所有的render view
		VkRect2D viewRenderArea{};
		viewRenderArea.extent.width = 1;
		viewRenderArea.extent.height = 1;
		viewRenderArea.offset.x = 0;
		viewRenderArea.offset.y = 0;
	multiviewPerViewRenderAreasRenderPassBeginInfoQCOM.pPerViewRenderAreas = &viewRenderArea;
	/*
	VkMultiviewPerViewRenderAreasRenderPassBeginInfoQCOM有效用法：
	1. pPerViewRenderAreas的 offset.x， offset.y必须大于等于0， extent.width， extent.height必须大于0
	2.pPerViewRenderAreas的offset.x + extent.width必须小于等于 maxFramebufferWidth，offset.y + extent.height必须小于等于 maxFramebufferHeight，
	3.如果VkRenderPassBeginInfo或者VkRenderingInfo的pNext中含有该结构体且 VkRenderPassMultiviewCreateInfo::pViewMasks或者VkRenderingInfo::viewMask设置了第n位，则 perViewRenderAreaCount至少为n+1
	4.pPerViewRenderAreas为perViewRenderAreaCount个有效的VkRect2D的数组的首地址
	*/



	VkRenderPassBeginInfo renderPassBeginInfo{};
	renderPassBeginInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
	renderPassBeginInfo.pNext = &renderPassBeginInfoExt.deviceGroupRenderPassBeginInfo;
	renderPassBeginInfo.clearValueCount = 0;
	renderPassBeginInfo.pClearValues = VK_NULL_HANDLE;//是VkClearValue的数组首地址指针，按照attachment索引，不在索引内的元素将会被忽略
	renderPassBeginInfo.framebuffer = VK_NULL_HANDLE;
	renderPassBeginInfo.renderArea.extent = VkExtent2D{ .width = 1,
														.height = 1 };
	/*
	renderArea:指明渲染过程中会被影响的所有附件中x，y处于范围内的pixel值，且会作用于所有的layer，如果应用了VkRenderPassTransformBeginInfoQCOM::transform，则renderArea必须再framebuffer的维度内，
				如果 render pass transform启用，则renderArea必须为framebuffer 的转换前的维度，当renderArea被 VkRenderPassTransformBeginInfoQCOM::transform,转换后，将会为framebuffer转换后的维度，
				如果 multiviewPerViewRenderAreas 开启，则renderArea必须是VkMultiviewPerViewRenderAreasRenderPassBeginInfoQCOM::pPerViewRenderAreas的一个并集
				如果 subpassShading开启，则renderArea必须等于framebuffer的维度 
	*/
	renderPassBeginInfo.renderArea.offset = { .x = 0,.y = 0 };
	renderPassBeginInfo.renderPass = VK_NULL_HANDLE;
	
	/*
	合法用法：
	1.clearValueCount 必须大于renderPass最大的指明了loadOp（或者stencilLoadOp如果有depth/stencil format）为VK_ATTACHMENT_LOAD_OP_CLEAR的attachment索引
	2.如果clearValueCount 不为 0, pClearValues 必须是合法的clearValueCount个VkClearValue的数组首地址
	3.renderPass必须和创建framebuffer时的renderPass相兼容
	4.如果pNext 中不含VkDeviceGroupRenderPassBeginInfo 或者含但是其deviceRenderAreaCount 为 0,则
												（1）renderArea.extent.width，renderArea.extent.height必须大于0,renderArea.offset.x，renderArea.offset.y 必须大于等于0
												（2）renderArea.extent.width + renderArea.offset.x 必须小于等于framebuffer创建时的width，renderArea.extent.height + renderArea.offset.y 必须小于等于framebuffer创建时的height
	5.如果pNext 中含有VkDeviceGroupRenderPassBeginInfo，则 pDeviceRenderAreas中的每一个元素的offset.x + extent.width必须小于等于framebuffer创建时的width，offset.y + extent.height必须小于等于framebuffer创建时的height
	6.如果 framebuffer创建时的VkFramebufferCreateInfo::flags 不是 VK_FRAMEBUFFER_CREATE_IMAGELESS_BIT, 且 pNext 包含VkRenderPassAttachmentBeginInfo , 则 VkRenderPassAttachmentBeginInfo.attachmentCount必须为0
	7.如果 framebuffer 创建时的 VkFramebufferCreateInfo::flags 包含VK_FRAMEBUFFER_CREATE_IMAGELESS_BIT, 则
												（1）pNext中的VkRenderPassAttachmentBeginInfo.attachmentCount必须等于创建framebuffer时的 VkFramebufferAttachmentsCreateInfo::attachmentImageInfoCount
												（2） pNext中的VkRenderPassAttachmentBeginInfo.pAttachments中的每个附件必须再renderPass以及framebuffer所在的Device上创建
												（3）pNext中的VkRenderPassAttachmentBeginInfo.pAttachments中的每个附件的VkImageView 创建时的VkImageCreateInfo::flags 必须等于创建framebuffer的VkFramebufferAttachmentsCreateInfo::pAttachmentImageInfos中对应元素的flags参数
												（4）pNext中的VkRenderPassAttachmentBeginInfo.pAttachments中的每个附件的VkImageView 创建时的usage 必须源于创建framebuffer的VkFramebufferAttachmentsCreateInfo::pAttachmentImageInfos中对应元素的usage参数
												（5）pNext中的VkRenderPassAttachmentBeginInfo.pAttachments中的每个附件的VkImageView 创建时的width，height 必须等于创建framebuffer的VkFramebufferAttachmentsCreateInfo::pAttachmentImageInfos中对应元素的width，height参数
												（6）pNext中的VkRenderPassAttachmentBeginInfo.pAttachments中的每个附件的VkImageView 创建时的VkImageCreateInfo::subresourceRange.layerCount 必须等于创建framebuffer的VkFramebufferAttachmentsCreateInfo::pAttachmentImageInfos中对应元素的 layerCount参数
												（7）pNext中的VkRenderPassAttachmentBeginInfo.pAttachments中的每个附件的VkImageView 创建时的 VkImageFormatListCreateInfo::viewFormatCount必须等于创建framebuffer的VkFramebufferAttachmentsCreateInfo::pAttachmentImageInfos中对应元素的  viewFormatCount参数，
												（8）pNext中的VkRenderPassAttachmentBeginInfo.pAttachments中的每个附件的VkImageView 创建时的 VkImageFormatListCreateInfo::pViewFormats 中的元素必须等于创建framebuffer的VkFramebufferAttachmentsCreateInfo::pAttachmentImageInfos中对应元素的  pViewFormats中的元素
												（9）pNext中的VkRenderPassAttachmentBeginInfo.pAttachments中的每个附件的VkImageView 创建时的VkImageCreateInfo::format 必须等于renderPass的对应附件的 VkAttachmentDescription::format
												（10）如果nullColorAttachmentWithExternalFormatResolve 为 VK_FALSE,则subpass中所有使用一个通过 vkGetAndroidHardwareBufferPropertiesANDROID接口获取的VkAndroidHardwareBufferFormatResolvePropertiesANDROID::colorAttachmentFormat格式创建的image来作为resolve 附件的是color 附件的格式必须和该resolve附件相同
												（11）pNext中的VkRenderPassAttachmentBeginInfo.pAttachments中的每个附件的VkImageView 创建时的format以VkExternalFormatANDROID::externalFormat创建， 其format必须等于renderPass创建时对应的 VkAttachmentDescription2的pNext中的VkExternalFormatANDROID::externalFormat
												（12）pNext中的VkRenderPassAttachmentBeginInfo.pAttachments中的每个附件的VkImageView 创建时的VkImageCreateInfo::samples 必须等于renderPass的对应附件的VkAttachmentDescription::samples，或者等于VK_SAMPLE_COUNT_1_BIT如果创建renderPass时的pNext中含有VkMultisampledRenderToSingleSampledInfoEXT且multisampledRenderToSingleSampledEnable为VK_TRUE

	
	8.如果pNext中含有VkRenderPassTransformBeginInfoQCOM，则renderArea.offset必须为（0，0），被VkRenderPassTransformBeginInfoQCOM::transform转换的renderArea.extent必须等于framebuffer的维度
	9.如果pNext中含有VkMultiviewPerViewRenderAreasRenderPassBeginInfoQCOM且其perViewRenderAreaCount不为0，则 multiviewPerViewRenderAreas 特性必须开启，且renderArea必须是所有render view的render area的一个并集
	10.如果pNext 含有VkRenderPassStripeBeginInfoARM ,  VkRenderPassStripeInfoARM::pStripeInfos中定义的stripe areas的并集必须包含renderArea 
	11.renderPass和framebuffer所在的Device必须相同
	*/





	vkCmdBeginRenderPass(cmdbuf, &renderPassBeginInfo, VK_SUBPASS_CONTENTS_INLINE);//调用了该命令后即可开始第一个subpass的命令记录
	/*
	有效用法：
	1.如果pRenderPassBegin中的rendPass创建时的任何VkAttachmentDescription中的initialLayout或者 finalLayout，或者VkAttachmentReference中的layout为
			VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL，则 pRenderPassBegin中的framebuffer对应的附件的image view创建时必须含有VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT
	2.如果pRenderPassBegin中的rendPass创建时的任何VkAttachmentDescription中的initialLayout或者 finalLayout，或者VkAttachmentReference中的layout为
			VK_IMAGE_LAYOUT_DEPTH_READ_ONLY_STENCIL_ATTACHMENT_OPTIMAL,
			VK_IMAGE_LAYOUT_DEPTH_ATTACHMENT_STENCIL_READ_ONLY_OPTIMAL,
			VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL, 或者
			VK_IMAGE_LAYOUT_DEPTH_STENCIL_READ_ONLY_OPTIMAL，
			VK_IMAGE_LAYOUT_DEPTH_ATTACHMENT_OPTIMAL, 或者 VK_IMAGE_LAYOUT_DEPTH_READ_ONLY_OPTIMAL,
			VK_IMAGE_LAYOUT_STENCIL_ATTACHMENT_OPTIMAL, 或者
			VK_IMAGE_LAYOUT_STENCIL_READ_ONLY_OPTIMAL，则 pRenderPassBegin中的framebuffer对应的附件的image view创建时必须含有VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT
	3.如果pRenderPassBegin中的rendPass创建时的任何VkAttachmentDescriptionStencilLayout中的stencilInitialLayout或者 stencilFinalLayout，或者VkAttachmentReferenceStencilLayout中的stencilLayout为
			VK_IMAGE_LAYOUT_STENCIL_ATTACHMENT_OPTIMAL, 或者
			VK_IMAGE_LAYOUT_STENCIL_READ_ONLY_OPTIMAL，则 pRenderPassBegin中的framebuffer对应的附件的image view创建时必须含有VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT
	4.如果pRenderPassBegin中的rendPass创建时的任何VkAttachmentDescription中的initialLayout或者 finalLayout，或者VkAttachmentReference中的layout为
			VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL，则 pRenderPassBegin中的framebuffer对应的附件的image view创建时必须含有VK_IMAGE_USAGE_SAMPLED_BIT 或者 VK_IMAGE_USAGE_INPUT_ATTACHMENT_BIT
	5.如果pRenderPassBegin中的rendPass创建时的任何VkAttachmentDescription中的initialLayout或者 finalLayout，或者VkAttachmentReference中的layout为
			VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL，则 pRenderPassBegin中的framebuffer对应的附件的image view创建时必须含有VK_IMAGE_USAGE_TRANSFER_SRC_BIT
	6.如果pRenderPassBegin中的rendPass创建时的任何VkAttachmentDescription中的initialLayout或者 finalLayout，或者VkAttachmentReference中的layout为
			VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL，则 pRenderPassBegin中的framebuffer对应的附件的image view创建时必须含有VK_IMAGE_USAGE_TRANSFER_DST_BIT
	7.如果pRenderPassBegin中的rendPass创建时的任何VkAttachmentDescription中的initialLayout不为VK_IMAGE_LAYOUT_UNDEFINED，则其initialLayout必须为当前 pRenderPassBegin中的framebuffer对应的附件的image subresource的图像布局
	8.VkRenderPassCreateInfo中的pDependencies中的srcStageMask以及dstStageMask必须是能够被commmandBuffer所在的commmandPool创建时的queueFamilyIndex所对应的队列簇支持的。
	9.如果renderPass所用的framebuffer的任何附件和改renderPass所用的其他附件存在内存重叠，且至少有一个附件是需要写入的，则这些附件都需要包含VK_ATTACHMENT_DESCRIPTION_MAY_ALIAS_BIT，这些附件只能在subpass中用作color attachment, depth/stencil, 或者 resolve attachment
	10.如果pRenderPassBegin中的rendPass创建时的任何VkAttachmentDescription中的initialLayout或者 finalLayout，或者VkAttachmentReference中的layout为
			VK_IMAGE_LAYOUT_ATTACHMENT_FEEDBACK_LOOP_OPTIMAL_EXT，则 pRenderPassBegin中的framebuffer对应的附件的image view创建时必须含有VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT 或者 VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT 与上 VK_IMAGE_USAGE_INPUT_ATTACHMENT_BIT 或者 VK_IMAGE_USAGE_SAMPLED_BIT 
			再与上 VK_IMAGE_USAGE_ATTACHMENT_FEEDBACK_LOOP_BIT_EXT
	11.如果pRenderPassBegin中的rendPass创建时的任何VkAttachmentDescription中的initialLayout或者 finalLayout，或者VkAttachmentReference中的layout为
			VK_IMAGE_LAYOUT_RENDERING_LOCAL_READ_KHR，则 pRenderPassBegin中的framebuffer对应的附件的image view创建时必须含有VK_IMAGE_USAGE_STORAGE_BIT, 或者 VK_IMAGE_USAGE_INPUT_ATTACHMENT_BIT 与上 VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT ， VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT其中之一
	12.如果contents 为 VK_SUBPASS_CONTENTS_INLINE_AND_SECONDARY_COMMAND_BUFFERS_EXT, 则nestedCommandBuffer 必须开启
	13.commandBuffer 必须是recording 状态
	*/


	VkSubpassBeginInfo subpassBeginInfo{};
	subpassBeginInfo.sType = VK_STRUCTURE_TYPE_SUBPASS_BEGIN_INFO;
	subpassBeginInfo.pNext = nullptr;
	subpassBeginInfo.contents = VK_SUBPASS_CONTENTS_INLINE;/*如果contents 为 VK_SUBPASS_CONTENTS_INLINE_AND_SECONDARY_COMMAND_BUFFERS_EXT, 则nestedCommandBuffer 必须开启
	VK_SUBPASS_CONTENTS_INLINE：指明命令将被记录到一个primaryCommandBuffer中，且该subpass不能包含任何执行secondaryCommandBuffer的命令
	VK_SUBPASS_CONTENTS_SECONDARY_COMMAND_BUFFERS：指明命令将被记录到一个secondaryCommandBuffer中，该secondaryCommandBuffer中只能使用vkCmdExecuteCommands命令来执行其他secondaryCommandBuffer直到遇到vkCmdNextSubpass 或者 vkCmdEndRenderPass.
	VK_SUBPASS_CONTENTS_INLINE_AND_SECONDARY_COMMAND_BUFFERS_EXT：指明该subpass的命令可以记录到一个primaryCommandBuffer以及通过 vkCmdExecuteCommands执行的secondaryCommandBuffer中。
	*/


	vkCmdBeginRenderPass2(cmdbuf, &renderPassBeginInfo, &subpassBeginInfo);//调用了该命令后即可开始第一个subpass的命令记录
	/*
	合法用法：
	1.pRenderPassBegin中的framebuffer和renderPass必须创建在commandBuffer所在的Device上
	2.如果pRenderPassBegin中的rendPass创建时的任何VkAttachmentDescription中的initialLayout或者 finalLayout，或者VkAttachmentReference中的layout为
			VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL，则 pRenderPassBegin中的framebuffer对应的附件的image view创建时必须含有VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT
	3.如果pRenderPassBegin中的rendPass创建时的任何VkAttachmentDescription中的initialLayout或者 finalLayout，或者VkAttachmentReference中的layout为
			VK_IMAGE_LAYOUT_DEPTH_READ_ONLY_STENCIL_ATTACHMENT_OPTIMAL,
			VK_IMAGE_LAYOUT_DEPTH_ATTACHMENT_STENCIL_READ_ONLY_OPTIMAL,
			VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL, 或者
			VK_IMAGE_LAYOUT_DEPTH_STENCIL_READ_ONLY_OPTIMAL，
			VK_IMAGE_LAYOUT_DEPTH_ATTACHMENT_OPTIMAL, 或者 VK_IMAGE_LAYOUT_DEPTH_READ_ONLY_OPTIMAL,
			VK_IMAGE_LAYOUT_STENCIL_ATTACHMENT_OPTIMAL, 或者
			VK_IMAGE_LAYOUT_STENCIL_READ_ONLY_OPTIMAL，则 pRenderPassBegin中的framebuffer对应的附件的image view创建时必须含有VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT
	4.如果pRenderPassBegin中的rendPass创建时的任何VkAttachmentDescriptionStencilLayout中的stencilInitialLayout或者 stencilFinalLayout，或者VkAttachmentReferenceStencilLayout中的stencilLayout为
			VK_IMAGE_LAYOUT_STENCIL_ATTACHMENT_OPTIMAL, 或者
			VK_IMAGE_LAYOUT_STENCIL_READ_ONLY_OPTIMAL，则 pRenderPassBegin中的framebuffer对应的附件的image view创建时必须含有VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT
	
	
	
	
	5.如果pRenderPassBegin中的rendPass创建时的任何VkAttachmentDescription中的initialLayout或者 finalLayout，或者VkAttachmentReference中的layout为
			VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL，则 pRenderPassBegin中的framebuffer对应的附件的image view创建时必须含有VK_IMAGE_USAGE_SAMPLED_BIT 或者 VK_IMAGE_USAGE_INPUT_ATTACHMENT_BIT
	6.如果pRenderPassBegin中的rendPass创建时的任何VkAttachmentDescription中的initialLayout或者 finalLayout，或者VkAttachmentReference中的layout为
			VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL，则 pRenderPassBegin中的framebuffer对应的附件的image view创建时必须含有 VK_IMAGE_USAGE_TRANSFER_SRC_BIT
	7.如果pRenderPassBegin中的rendPass创建时的任何VkAttachmentDescription中的initialLayout或者 finalLayout，或者VkAttachmentReference中的layout为
			VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL，则 pRenderPassBegin中的framebuffer对应的附件的image view创建时必须含有VK_IMAGE_USAGE_TRANSFER_DST_BIT
	8.如果pRenderPassBegin中的rendPass创建时的任何VkAttachmentDescription中的initialLayout不为VK_IMAGE_LAYOUT_UNDEFINED，则其initialLayout必须为当前 pRenderPassBegin中的framebuffer对应的附件的image subresource的图像布局
	9.VkRenderPassCreateInfo中的pDependencies中的srcStageMask以及dstStageMask必须是能够被commmandBuffer所在的commmandPool创建时的queueFamilyIndex所对应的队列簇支持的。
	10.如果renderPass所用的framebuffer的任何附件和改renderPass所用的其他附件存在内存重叠，且至少有一个附件是需要写入的，则这些附件都需要包含VK_ATTACHMENT_DESCRIPTION_MAY_ALIAS_BIT，这些附件只能在subpass中用作color attachment, depth/stencil, 或者 resolve attachment
	11.如果pRenderPassBegin中的rendPass创建时的任何VkAttachmentDescription中的initialLayout或者 finalLayout，或者VkAttachmentReference中的layout为
			VK_IMAGE_LAYOUT_ATTACHMENT_FEEDBACK_LOOP_OPTIMAL_EXT，则 pRenderPassBegin中的framebuffer对应的附件的image view创建时必须含有VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT 或者 VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT 与上 VK_IMAGE_USAGE_INPUT_ATTACHMENT_BIT 或者 VK_IMAGE_USAGE_SAMPLED_BIT 
			再与上 VK_IMAGE_USAGE_ATTACHMENT_FEEDBACK_LOOP_BIT_EXT
	12.如果pRenderPassBegin中的rendPass创建时的任何VkAttachmentDescription中的initialLayout或者 finalLayout，或者VkAttachmentReference中的layout为
			VK_IMAGE_LAYOUT_RENDERING_LOCAL_READ_KHR，则 pRenderPassBegin中的framebuffer对应的附件的image view创建时必须含有VK_IMAGE_USAGE_STORAGE_BIT, 或者 VK_IMAGE_USAGE_INPUT_ATTACHMENT_BIT 与上 VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT ， VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT其中之一
	13.commandBuffer 必须是recording 状态

	
	
	
	*/




	//查询渲染粒度,用于辅助设置renderArea
	VkExtent2D renderAreaGranularity{};
	vkGetRenderAreaGranularity(device, renderPass, &renderAreaGranularity);
	/*
	理想情况：
	1.renderArea的width以及offset.x应该是renderAreaGranularity返回的width的整数倍,height以及offset.y应该是renderAreaGranularity返回的height的整数倍
	2.renderArea.width + renderArea.offset.x应该等于VkRenderPassBeginInfo中framebuffer的width,renderArea.height + renderArea.offset.y应该等于VkRenderPassBeginInfo中framebuffer的height
	*/



	//进入到下一个subpass
	vkCmdNextSubpass(cmdbuf, VK_SUBPASS_CONTENTS_SECONDARY_COMMAND_BUFFERS);//调用了该命令后即可开始下一个subpass的命令记录，subpass的索引随着该调用依次递增，该command buffer必须是recoding状态，且改命令不能在render pass实例外
	//调用，不能在video code外调用，command buffer 必须支持图形操作


	VkSubpassEndInfo subpassEndInfo{};
	subpassEndInfo.sType = VK_STRUCTURE_TYPE_SUBPASS_END_INFO;
		VkSubpassFragmentDensityMapOffsetEndInfoQCOM subpassFragmentDensityMapOffsetEndInfo{};
		subpassFragmentDensityMapOffsetEndInfo.sType = VK_STRUCTURE_TYPE_SUBPASS_FRAGMENT_DENSITY_MAP_OFFSET_END_INFO_QCOM;
		subpassFragmentDensityMapOffsetEndInfo.pNext = nullptr;
		subpassFragmentDensityMapOffsetEndInfo.fragmentDensityOffsetCount = 0;
			VkOffset2D fragmentDensityOffset{};
			fragmentDensityOffset.x = 0;
			fragmentDensityOffset.y = 0;
			subpassFragmentDensityMapOffsetEndInfo.pFragmentDensityOffsets = &fragmentDensityOffset;//包含fragment density map offsets 每个layer的offset,其中索引=层。每个（x，y）偏移量都是帧缓冲区像素，并将片段密度映射的获取移动到该量上。偏移量可以是正的或负的。如果该结构体没有包含在最后一个subpass的EndInfo的pNext中，则将忽略该结构体的参数，
			//如果最后一个subpass的VkSubpassEndInfo::pNext中或者是renderPass不含VkSubpassFragmentDensityMapOffsetEndInfoQCOM,或者fragmentDensityOffsetCount为0，则offset (0,0) 将会被 Fetch Density Value使用
		/*
		VkSubpassFragmentDensityMapOffsetEndInfoQCOM有效用法：
		1.
		
		
		
		
		
		*/
	subpassEndInfo.pNext = &subpassFragmentDensityMapOffsetEndInfo;//pNext中可以含有VkSubpassFragmentDensityMapOffsetEndInfoQCOM
	vkCmdNextSubpass2(cmdbuf, &subpassBeginInfo, &subpassEndInfo);//等用与vkCmdNextSubpass，只是可以扩展



	//结束render pass 渲染
	vkCmdEndRenderPass(cmdbuf);//调用该命令后，当前subpass必须是最后一个subpass，渲染结束。不能和vkCmdBeginRendering配套使用，vkCmdBeginQuery*以及vkCmdEndQuery*必须配套使用在同一个subpass中，该command buffer必须是recoding状态，且改命令不能在render pass实例外
	//调用，不能在video code外调用，command buffer 必须支持图形操作

	vkCmdEndRenderPass2(cmdbuf, &subpassEndInfo);//等用与vkCmdEndRenderPass，只是可以扩展，调用该命令后，当前subpass必须是最后一个subpass，渲染结束。不能和vkCmdBeginRendering配套使用，vkCmdBeginQuery*以及vkCmdEndQuery*必须配套使用在同一个subpass中，该command buffer必须是recoding状态，且改命令不能在render pass实例外
	//调用，不能在video code外调用，command buffer 必须支持图形操作

}


















NS_TEST_END