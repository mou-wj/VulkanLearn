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


void RenderPassTest::RenderPassCreateTest()
{
	VkRenderPass renderPass{ VK_NULL_HANDLE };
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
	VkRenderPassFragmentDensityMapCreateInfoEXT &renderPassFragmentDensityMapCreateInfoEXT = renderPassCreateInfoExt.renderPassFragmentDensityMapCreateInfoEXT;
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
	6. 如果format是depth/stencil格式，且含有depth和stencil数据或者只含有stencil数据，则initialLayout和finalLayout不能是VK_IMAGE_LAYOUT_STENCIL_ATTACHMENT_OPTIMAL 或者
																								  VK_IMAGE_LAYOUT_STENCIL_READ_ONLY_OPTIMAL，VK_IMAGE_LAYOUT_DEPTH_ATTACHMENT_OPTIMAL 
																								  或者VK_IMAGE_LAYOUT_DEPTH_READ_ONLY_OPTIMAL

	7. 如果synchronization2特性未开启，initialLayout和finalLayout不能是VK_IMAGE_LAYOUT_ATTACHMENT_OPTIMAL_KHR 或者 VK_IMAGE_LAYOUT_READ_ONLY_OPTIMAL_KHR
	8. 如果attachmentFeedbackLoopLayout特性未开启，initialLayout和finalLayout不能是VK_IMAGE_LAYOUT_ATTACHMENT_FEEDBACK_LOOP_OPTIMAL_EXT
	9. samples必须是必须和image创建时候的samples相同
	10. 如果dynamicRenderingLocalRead特性未开启，initialLayout和finalLayout不能是VK_IMAGE_LAYOUT_RENDERING_LOCAL_READ_KHR
	11. format不能为VK_FORMAT_UNDEFINED
	12. 如果format 有stencil 数据且 stencilLoadOp 是 VK_ATTACHMENT_LOAD_OP_LOAD,则 initialLayout 不能为 VK_IMAGE_LAYOUT_UNDEFINED
	
	
	
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
	todo 20240617
	
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
	11. pDepthStencilAttachment 不是 NULL 且 其attachment 不是 VK_ATTACHMENT_UNUSEDVK_ATTACHMENT_UNUSED， 则attachment必须含有拥有potential format features （见p4100）为 VK_FORMAT_FEATURE_COLOR_ATTACHMENT_BIT的 image format
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










}





























NS_TEST_END