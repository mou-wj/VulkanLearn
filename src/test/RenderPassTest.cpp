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
	VkRect2D stripeArea;//stripeAreaָ����ǰrender passʵ����Ӱ�����Ⱦ������Ҫ��render pass��renderArea��һ���֣�����ϸ�ڣ�
	/*
	stripeArea.offset.x�Լ�stripeArea.extent.width������VkPhysicalDeviceRenderPassStripedPropertiesARM::renderPassStripeGranularity.width�ı�������stripeArea.offset.x + stripeArea.extent.widthҪ����render passʵ����renderArea.extent.width
	stripeArea.offset.y�Լ�stripeArea.extent.height������VkPhysicalDeviceRenderPassStripedPropertiesARM::renderPassStripeGranularity.width�ı�������stripeArea.offset.y + stripeArea.extent.heightҪ����render passʵ����renderArea.extent.height
	
	*/
} VkRenderPassStripeInfoARM;
typedef struct VkRenderPassStripeBeginInfoARM {
	VkStructureType sType;
	const void* pNext;
	uint32_t stripeInfoCount;//��ֵ����С�� VkPhysicalDeviceRenderPassStripedPropertiesARM::maxRenderPassStripes
	const VkRenderPassStripeInfoARM* pStripeInfos;
} VkRenderPassStripeBeginInfoARM;//������ν�render passʵ������Ϊstrips
struct RenderInfoExt
{
	VkDeviceGroupRenderPassBeginInfo deviceGroupRenderPassBeginInfo{};
	VkMultisampledRenderToSingleSampledInfoEXT multisampledRenderToSingleSampledInfoEXT{};
	VkMultiviewPerViewAttributesInfoNVX multiviewPerViewAttributesInfoNVX{};
	VkMultiviewPerViewRenderAreasRenderPassBeginInfoQCOM MultiviewPerViewRenderAreasRenderPassBeginInfoQCOM{};

	VkRenderPassStripeBeginInfoARM renderPassStripeBeginInfoARM{};//��ǰvulkan�汾û���ҵ��ýṹ��Ķ��壬�ȶ���һ����Ϊʾ�����Ҹýṹ�岻���ڳ�ʼ��Init�����н��г�ʼ����������
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
	�Ϸ��÷���
	1. dynamicRendering������Ҫ����
	2. nestedCommandBuffer����δ������pRenderingInfo->flags������VK_RENDERING_CONTENTS_SECONDARY_COMMAND_BUFFERS_BIT
	3. pRenderingInfo->pDepthAttachment����NULL��pRenderingInfo->pDepthAttachment->imageView�������VK_NULL_HANDLE���imageview�Ĳ���Ҫ�� pRenderingInfo->pDepthAttachment->imageLayout��ͬ
	4. pRenderingInfo->pDepthAttachment����NULL,pRenderingInfo->pDepthAttachment->imageView�������VK_NULL_HANDLE,�� pRenderingInfo->pDepthAttachment->imageResolveMode����VK_RESOLVE_MODE_NONE��
	��pRenderingInfo->pDepthAttachment->resolveImageView����VK_NULL_HANDLE����pRenderingInfo->pDepthAttachment->resolveImageView������Ҫ�� pRenderingInfo->pDepthAttachment->resolveImageLayout��ͬ
	5. pRenderingInfo->pStencilAttachment����NULL,��pRenderingInfo->pStencilAttachment->imageView����VK_NULL_HANDLE��pRenderingInfo->pStencilAttachment->imageView�����
	pRenderingInfo->pStencilAttachment->imageLayout������ͬ
	6. pRenderingInfo->pStencilAttachment����NULL,pRenderingInfo->pStencilAttachment->imageView�������VK_NULL_HANDLE,�� pRenderingInfo->pStencilAttachment->imageResolveMode����VK_RESOLVE_MODE_NONE��
	��pRenderingInfo->pStencilAttachment->resolveImageView����VK_NULL_HANDLE����pRenderingInfo->pStencilAttachment->resolveImageView������Ҫ�� pRenderingInfo->pStencilAttachment->resolveImageLayout��ͬ
	7. �κ�pRenderingInfo->pColorAttachments�е�imageView�������VK_NULL_HANDLE����imageView�Ĳ�����Ҫ��imageLayout��ͬ
	8. �κ�pRenderingInfo->pColorAttachments�е�imageView���imageResolveMode��VK_RESOLVE_MODE_EXTERNAL_FORMAT_DOWNSAMPLE_ANDROID,����imageView����VK_NULL_HANDLE��imageResolveMode���� VK_RESOLVE_MODE_NONE�Լ�
	resolveImageView����VK_NULL_HANDLE��resolveImageView�����resolveImageLayout������ͬ

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
	//����VkRenderingInfoKHR�Ŀ���չ�����ݽṹ
	RenderInfoExt renderInfoExt;
	refRenderInfo.pNext = &renderInfoExt.deviceGroupRenderPassBeginInfo;
	//refRenderInfo.pNext = nullptr;
	refRenderInfo.flags = VK_RENDERING_SUSPENDING_BIT;/*
		VK_RENDERING_CONTENTS_SECONDARY_COMMAND_BUFFERS_BIT: ָ��render passʵ�����ڸ�����������м�¼���Ƶ��õ������������� nestedCommandBuffer ���ԣ���μ������еĻ��Ƶ��ÿ��Ե��� vkCmdExecuteCommands��
		VK_RENDERING_RESUMING_BIT: ָ����ǰ��render pass ʵ����ʹ��֮ǰ�����render pass ʵ��
		VK_RENDERING_SUSPENDING_BIT: ָ������ǰ��render pass ����
		VK_RENDERING_ENABLE_LEGACY_DITHERING_BIT_EXT: ָ��Legacy Dithering�ڵ�ǰrender pass ʵ������
		VK_RENDERING_CONTENTS_INLINE_BIT_EXT: ָ����ǰrender pass�Ļ�������������Եļ�¼�ڵ�ǰ����������У���� nestedCommandBuffer���Կ�������Ժ�VK_RENDERING_CONTENTS_SECONDARY_COMMAND_BUFFERS_BIT����������
		�μ�������������Լ�¼��������

		note:resume render pass��suspend render pass��pRenderingInfo���ݳ���VK_RENDERING_RESUMING_BIT, VK_RENDERING_SUSPENDING_BIT, �Լ�VK_RENDERING_CONTENTS_SECONDARY_COMMAND_BUFFERS_BIT����Ҫƥ�䣬��������֮ǰ
		�����������Ķ�����ͬ���������render passʵ��
	*/


	/*
	VkRenderingInfoKHR�Ϸ��÷�����������˵�����º�VkRenderingInfoKHR��Աͬ���ı�����ΪVkRenderingInfoKHR�ĳ�Ա��
	1. ���viewMaskΪ0,��layerCount������0
	2. ���VK_AMD_mixed_attachment_samples��VK_NV_framebuffer_mixed_samples��չδ�������� multisampledRenderToSingleSampled����δ��������
	pDepthAttachment, pStencilAttachment, �Լ�pColorAttachments�еĲ�ΪVK_NULL_HANDLE��imageView��sampleCount������ͬ
	3. ���multisampledRenderToSingleSampled����δ��������pColorAttachments�еĲ�ΪVK_NULL_HANDLE��imageView��sampleCount������ͬ
	4. ���VkDeviceGroupRenderPassBeginInfo::deviceRenderAreaCount��0����renderArea.extent.width�Լ�renderArea.extent.height�������0
	5. ���multisampled-render-to-single-sampled��������pDepthAttachment, pStencilAttachment, �Լ�pColorAttachments�еĲ�ΪVK_NULL_HANDLE��imageView��sampleCount����
	��VK_SAMPLE_COUNT_1_BIT ���ߵ���VkMultisampledRenderToSingleSampledInfoEXT::rasterizationSamples�������VK_SAMPLE_COUNT_1_BIT���ڴ���imageʱ�������VK_IMAGE_CREATE_MULTISAMPLED_RENDER_TO_SINGLE_SAMPLED_BIT_EXT ��
	VkImageCreateInfo::flags��
	6. ���pNext�в���VkDeviceGroupRenderPassBeginInfo����deviceRenderAreaCountΪ0���� renderArea.offset.x�� renderArea.offset.y�������0��renderArea.offset.x + renderArea.extent.width ����С�� maxFramebufferWidth��
	renderArea.offset.y + renderArea.extent.height ����С�� maxFramebufferHeight����pDepthAttachment, pStencilAttachment, �Լ�pColorAttachments�еĲ�ΪVK_NULL_HANDLE��imageView�Ŀ�������renderArea.offset.x + renderArea.extent.width��
	�߱������renderArea.offset.y + renderArea.extent.height
	7. ���pNext�к�VkDeviceGroupRenderPassBeginInfo����pDepthAttachment, pStencilAttachment, �Լ�pColorAttachments�еĲ�ΪVK_NULL_HANDLE��imageView�Ŀ�������pDeviceRenderAreas�е�offset.x + extent.width��
	�߱������pDeviceRenderAreas�е�offset.y + extent.height
	8. ��� pDepthAttachment �� pStencilAttachment������NULL,�Ҷ�Ӧ��imageViewҲ����VK_NULL_HANDLE�������ߵ�imageView������ͬ����� ���ߵ�resolveModeҲ����VK_RESOLVE_MODE_NONE�������ߵ� resolveImageViewҲ������ͬ
	9. ���colorAttachmentCount����0����pColorAttachments�еĲ�ΪVK_NULL_HANDLE��imageView��Ӧ��image����ʱ�������VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT�����pColorAttachments��Ӧ�� resolveMode����ΪVK_RESOLVE_MODE_EXTERNAL_FORMAT_DOWNSAMPLE_ANDROID,
	����pColorAttachments�еĲ�ΪVK_NULL_HANDLE��imageView��resolveMode����VK_RESOLVE_MODE_NONE,���� pColorAttachments �е� resolveImageView��Ӧ��image����ʱҲ�������VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT
	10. ��� pDepthAttachment ���� NULL �� pDepthAttachment->imageView ���� VK_NULL_HANDLE,�� pDepthAttachment->imageView��Ӧ��image�����ǵ�format�б����������ݣ��ұ��뺬��VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT�����pDepthAttachment->resolveMode ����
	VK_RESOLVE_MODE_NONE,�� pDepthAttachment->resolveImageView��Ӧ��image����ʱҲ���뺬��VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT
	11. ��� pStencilAttachment ���� NULL �� pStencilAttachment->imageView ���� VK_NULL_HANDLE,�� pStencilAttachment->imageView��Ӧ��image�����ǵ�format�б�����ģ����ݣ��ұ��뺬��VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT�����pStencilAttachment->resolveMode ����
	VK_RESOLVE_MODE_NONE,�� pStencilAttachment->resolveImageView��Ӧ��image����ʱҲ���뺬��VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT
	12. ���colorAttachmentCount����0����pColorAttachments�еĲ�ΪVK_NULL_HANDLE��imageView�Լ������Ӧ�� resolveMode����VK_RESOLVE_MODE_NONE����imageView��Ӧ��imageLayout�Լ���Ӧ��
	 resolveImageLayoutҲ������ VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL
								����VK_IMAGE_LAYOUT_DEPTH_STENCIL_READ_ONLY_OPTIMAL��
								VK_IMAGE_LAYOUT_DEPTH_READ_ONLY_STENCIL_ATTACHMENT_OPTIMAL
								���� VK_IMAGE_LAYOUT_DEPTH_ATTACHMENT_STENCIL_READ_ONLY_OPTIMAL��
								VK_IMAGE_LAYOUT_DEPTH_ATTACHMENT_OPTIMAL,
								VK_IMAGE_LAYOUT_DEPTH_READ_ONLY_OPTIMAL,
								VK_IMAGE_LAYOUT_STENCIL_ATTACHMENT_OPTIMAL, ����
								VK_IMAGE_LAYOUT_STENCIL_READ_ONLY_OPTIMAL
	13. ���pDepthAttachment ���� NULL �� pDepthAttachment->imageView ���� VK_NULL_HANDLE�������Ӧ��resolveMode����VK_RESOLVE_MODE_NONE����pDepthAttachment->layout���� resolveImageLayout������
																		VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL��
																		VK_IMAGE_LAYOUT_STENCIL_ATTACHMENT_OPTIMAL ����
																		VK_IMAGE_LAYOUT_STENCIL_READ_ONLY_OPTIMAL

	ͬ�����pStencilAttachment ���� NULL �� pStencilAttachment->imageView ���� VK_NULL_HANDLE�������Ӧ��resolveMode����VK_RESOLVE_MODE_NONE����pStencilAttachment->layout ����resolveImageLayoutҲ������
																		VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL��
																		VK_IMAGE_LAYOUT_DEPTH_ATTACHMENT_OPTIMAL ����
																		VK_IMAGE_LAYOUT_DEPTH_READ_ONLY_OPTIMAL
	14. ���pDepthAttachment ���� NULL �� pDepthAttachment->imageView ���� VK_NULL_HANDLE,�Ҷ�Ӧ��resolveMode����VK_RESOLVE_MODE_NONE����resolveImageLayout������VK_IMAGE_LAYOUT_DEPTH_READ_ONLY_STENCIL_ATTACHMENT_OPTIMAL�����Ƶģ�������pStencilAttachment ���� NULL ��
	pStencilAttachment->imageView ���� VK_NULL_HANDLE,�Ҷ�Ӧ��resolveMode����VK_RESOLVE_MODE_NONE����resolveImageLayout������VK_IMAGE_LAYOUT_DEPTH_ATTACHMENT_STENCIL_READ_ONLY_OPTIMAL

	15. ���pDepthAttachment ���� NULL �� pDepthAttachment->imageView ���� VK_NULL_HANDLE,���Ӧ��resolveMode������VkPhysicalDeviceDepthStencilResolveProperties::supportedDepthResolveModes֧�ֵģ�ͬ�����pStencilAttachment ���� NULL �� pStencilAttachment->imageView
	���� VK_NULL_HANDLE,���Ӧ��resolveMode������VkPhysicalDeviceDepthStencilResolveProperties::supportedDepthResolveModes֧�ֵ�
	16. ���pDepthAttachment ��pStencilAttachment���� NULL �� pDepthAttachment->imageView ��pStencilAttachment->imageView ���� VK_NULL_HANDLE����VkPhysicalDeviceDepthStencilResolveProperties::independentResolve �� VK_FALSE�����������ߵ�resolveMode��������ͬ�������
	��VkPhysicalDeviceDepthStencilResolveProperties::independentResolve��VK_FALSE������£�ֻҪ��������һ����resolveMode����VK_RESOLVE_MODE_NONE�������ߵ� resolveMode������ͬ

	17.colorAttachmentCount����С��VkPhysicalDeviceLimits::maxColorAttachments
	18.�����pNext�к���VkRenderingFragmentDensityMapAttachmentInfoEXT,�����е�imageView����VK_NULL_HANDLE����
							��1�������fragmentDensityMapNonSubsampledImagesû�п�������Ϸ��� pDepthAttachment, pStencilAttachment, �Լ�pColorAttachments��resolveImageView�еĺϷ���imageView��Ӧ
									��image����ʱ���뺬��VK_IMAGE_CREATE_SUBSAMPLED_BIT_EXT
							��2�������viewMask����0����imageView�Ĵ���ʱ��layerCount������ڻ����viewMask�������������viewMask��0����imageView�Ĵ���ʱ��layerCount������1
	19.���pNext��û�к���VkDeviceGroupRenderPassBeginInfo����deviceRenderAreaCountΪ0������pNext�к���VkRenderingFragmentShadingRateAttachmentInfoKHR���Ҷ�Ӧ��imageView��ΪVK_NULL_HANDLE,��
					��1��imageView�ĵ�widthҪ���ڵ��� (renderArea.x + renderArea.width) / shadingRateAttachmentTexelSize.width
					��2��imageView�ĵ�heightҪ���ڵ��� (renderArea.y + renderArea.height) / shadingRateAttachmentTexelSize.height
	   ���pNext�к���VkDeviceGroupRenderPassBeginInfo��deviceRenderAreaCount��Ϊ0������pNext�к���VkRenderingFragmentShadingRateAttachmentInfoKHR���Ҷ�Ӧ��pDeviceRenderAreas��imageView��ΪVK_NULL_HANDLE,��
					��1��pDeviceRenderAreas��imageView�ĵ�widthҪ���ڵ��� (pDeviceRenderArea.x + pDeviceRenderArea.width) / shadingRateAttachmentTexelSize.width
					��2��pDeviceRenderAreas��imageView�ĵ�heightҪ���ڵ��� (pDeviceRenderArea.y + pDeviceRenderArea.height) / shadingRateAttachmentTexelSize.height
	20. �����pNext�к���VkRenderingFragmentShadingRateAttachmentInfoKHR���Ҷ�Ӧ��imageView��ΪVK_NULL_HANDLEʱ����
					��1�����viewMask �� 0,��imageView ���е� layer�����������1 ���ߴ��ڵ���refRenderInfo.layerCount
					��2�����viewMask����0����imageView�ĺ��е� layer��������1���ߴ��ڻ����viewMask��������
					��3��imageView����� pDepthAttachment, pStencilAttachment�����κ� pColorAttachments��resolveImageView�� imageView���
					��4��imageView�����pNext�е�VkRenderingFragmentDensityMapAttachmentInfoEXT��imageView���
	21.  viewMask����С�� maxMultiviewViewCount����� multiview����δ��������viewMask������0
	22.	���pNext�е�VkMultiviewPerViewRenderAreasRenderPassBeginInfoQCOM��perViewRenderAreaCount��Ϊ0���� multiviewPerViewRenderAreas���Ա��뿪���� refRenderInfo.renderArea������
		����ÿ��view��renderArea�Ĳ���
	23. ��Ч�ĸ������ڴ治�ܽ����ص�
	24. ���flags����VK_RENDERING_CONTENTS_INLINE_BIT_EXT����nestedCommandBuffer���Ա��뿪��
	25. pDepthAttachment->resolveMode�Լ�pStencilAttachment->resolveMode������VK_RESOLVE_MODE_EXTERNAL_FORMAT_DOWNSAMPLE_ANDROID
	26. ���colorAttachmentCount��Ϊ1����pColorAttachments��Ӧ��resolveMode������ VK_RESOLVE_MODE_EXTERNAL_FORMAT_DOWNSAMPLE_ANDROID�����pColorAttachments��Ӧ��resolveMode�� VK_RESOLVE_MODE_EXTERNAL_FORMAT_DOWNSAMPLE_ANDROID��
			��VkRenderingFragmentDensityMapAttachmentInfoEXT::imageView�Լ�VkRenderingFragmentShadingRateAttachmentInfoKHR::imageView������VK_NULL_HANDLE����û��ʹ�ã�
	27. ���pNext�к��� VkRenderPassStripeBeginInfoARM�������� VkRenderPassStripeInfoARM::pStripeInfos�е�strip area�Ĳ����������refRenderInfo.renderArea
	28. ���colorAttachmentCount����0����pColorAttachments�еĲ�ΪVK_NULL_HANDLE��imageView���������� identity swizzle�����pColorAttachments��Ӧ��resolveModeΪ VK_RESOLVE_MODE_EXTERNAL_FORMAT_DOWNSAMPLE_ANDROID������
	pColorAttachments�еĲ�ΪVK_NULL_HANDLE��imageView��Ӧ��resolveMode��ΪVK_RESOLVE_MODE_NONE����pColorAttachments��resolveImageView�Ĵ���������identity swizzle
	29.���pDepthAttachment��ΪNULL,��pDepthAttachment->imageView��ΪVK_NULL_HANDLE,���pDepthAttachment->resolveMode��ΪVK_RESOLVE_MODE_NONE����pDepthAttachment->imageView�Լ�pDepthAttachment->resolveImageView�Ĵ���������identity swizzle��
	ͬ����� pStencilAttachment��ΪNULL,�� pStencilAttachment->imageView��ΪVK_NULL_HANDLE,��� pStencilAttachment->resolveMode��ΪVK_RESOLVE_MODE_NONE���� pStencilAttachment->imageView�Լ� pStencilAttachment->resolveImageView�Ĵ���������identity swizzle��
	30. �����pNext��ֻҪ����VkRenderingFragmentShadingRateAttachmentInfoKHR����VkRenderingFragmentDensityMapAttachmentInfoEXT�������е�imageView��ΪVK_NULL_HANDLE,���imageView����������identity swizzle

	*/

	VkRenderingAttachmentInfoKHR colorAttachmentInfo{};
	colorAttachmentInfo.sType = VK_STRUCTURE_TYPE_RENDERING_ATTACHMENT_INFO_KHR;
	colorAttachmentInfo.imageView = VK_NULL_HANDLE;//���imageView��VK_NULL_HANDLE,��resolveMode����VK_RESOLVE_MODE_EXTERNAL_FORMAT_DOWNSAMPLE_ANDROID,�����������ᱻ���ԣ������û�ж���ø���
	colorAttachmentInfo.imageLayout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
	colorAttachmentInfo.clearValue = VkClearValue{ 0,0,0,1 };
	colorAttachmentInfo.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;//ֻ�ᷢ����û������VK_RENDERING_RESUMING_BIT_KHR��render passʵ����ʼ
	colorAttachmentInfo.storeOp = VK_ATTACHMENT_STORE_OP_STORE;//ֻ�ᷢ����û������VK_RENDERING_SUSPENDING_BIT_KHR��render passʵ������
	colorAttachmentInfo.pNext = nullptr;
	colorAttachmentInfo.resolveMode = VK_RESOLVE_MODE_NONE;//���resolveMode����VK_RESOLVE_MODE_NONE����resolveImageView����VK_NULL_HANDLE�����ᶨ��һ�����ز������������resolveModeΪVK_RESOLVE_MODE_EXTERNAL_FORMAT_DOWNSAMPLE_ANDROID,
	//��nullColorAttachmentWithExternalFormatResolveΪVK_TRUE,�ڼ��ز���������ֵ�����δ���壨���ﲻ���ʲô��˼��
	colorAttachmentInfo.resolveImageView = VK_NULL_HANDLE;
	colorAttachmentInfo.resolveImageLayout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

	/*
	VkRenderingAttachmentInfo�Ϸ��÷�����������˵�����º�VkRenderingAttachmentInfoKHR��Աͬ���ı�����ΪVkRenderingAttachmentInfoKHR�ĳ�Ա��
	1. ���imageView���� VK_NULL_HANDLE����һ����������color format����resolveMode����Ϊ VK_RESOLVE_MODE_NONE �� VK_RESOLVE_MODE_AVERAGE_BIT���������һ����������color format����resolveMode����Ϊ VK_RESOLVE_MODE_NONE ��  VK_RESOLVE_MODE_SAMPLE_ZERO_BIT
	2. ���imageView ���� VK_NULL_HANDLE����resolveMode��Ϊ VK_RESOLVE_MODE_NONE����multisampledRenderToSingleSampledEnable Ϊ VK_TRUE
					��1�����VkRenderingInfo��pNext�в���VkMultisampledRenderToSingleSampledInfoEXT ���� imageView���ܺ���VK_SAMPLE_COUNT_1_BIT����resolveImageView ����Ϊ VK_NULL_HANDLE
					��2�����VkRenderingInfo��pNext�к�VkMultisampledRenderToSingleSampledInfoEXT ���� imageView����VK_SAMPLE_COUNT_1_BIT����resolveImageView Ϊ VK_NULL_HANDLE
	3. ���imageView ���� VK_NULL_HANDLE�� resolveImageView���� VK_NULL_HANDLE,��resolveMode ���� VK_RESOLVE_MODE_NONE���� resolveImageView������VK_SAMPLE_COUNT_1_BIT��imageView �� resolveImageView��������ͬ��VkFormat
	4. ���imageView ���� VK_NULL_HANDLE����imageLayout������VK_IMAGE_LAYOUT_UNDEFINED,
															VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL, VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL,
															VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, �� VK_IMAGE_LAYOUT_PREINITIALIZED��
															VK_IMAGE_LAYOUT_SHADING_RATE_OPTIMAL_NV ��VK_IMAGE_LAYOUT_FRAGMENT_DENSITY_MAP_OPTIMAL_EXT��
															VK_IMAGE_LAYOUT_FRAGMENT_SHADING_RATE_ATTACHMENT_OPTIMAL_KHR ����VK_IMAGE_LAYOUT_PRESENT_SRC_KHR��

	4. ���imageView ���� VK_NULL_HANDLE����  resolveMode ����VK_RESOLVE_MODE_NONE����resolveImageLayout������
															VK_IMAGE_LAYOUT_UNDEFINED,
															VK_IMAGE_LAYOUT_DEPTH_STENCIL_READ_ONLY_OPTIMAL,
															VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL, VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL,
															VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,����VK_IMAGE_LAYOUT_PREINITIALIZED��
															VK_IMAGE_LAYOUT_DEPTH_READ_ONLY_OPTIMAL ���� VK_IMAGE_LAYOUT_STENCIL_READ_ONLY_OPTIMAL��
															VK_IMAGE_LAYOUT_SHADING_RATE_OPTIMAL_NV ��VK_IMAGE_LAYOUT_FRAGMENT_DENSITY_MAP_OPTIMAL_EXT��
															VK_IMAGE_LAYOUT_READ_ONLY_OPTIMAL_KHR ��VK_IMAGE_LAYOUT_FRAGMENT_SHADING_RATE_ATTACHMENT_OPTIMAL_KHR��
															 VK_IMAGE_LAYOUT_PRESENT_SRC_KHR
	5. ��� externalFormatResolveû�����ã���resolveMode������VK_RESOLVE_MODE_EXTERNAL_FORMAT_DOWNSAMPLE_ANDROID����resolveImageView��������Ч�ģ�
									resolveImageView������ VkExternalFormatANDROID������ subresourceRange.layerCount Ϊ1
	6. ��� nullColorAttachmentWithExternalFormatResolve������VK_TRUE,��resolveMode��VK_RESOLVE_MODE_EXTERNAL_FORMAT_DOWNSAMPLE_ANDROID��resolveImageView�Ĳ�����������VK_SAMPLE_COUNT_1_BIT��imageView����ΪVK_NULL_HANDLE
	7. ��� nullColorAttachmentWithExternalFormatResolve������VK_FALSE,��resolveMode��VK_RESOLVE_MODE_EXTERNAL_FORMAT_DOWNSAMPLE_ANDROID,imageView��������Ч�ģ��ұ����и���ʽ�Ͱ�׿�豸����vkGetAndroidHardwareBufferPropertiesANDROID���ص���������
	resolveImageView��VkAndroidHardwareBufferFormatResolvePropertiesANDROID::colorAttachmentFormat���
	*/




	VkRenderingFragmentShadingRateAttachmentInfoKHR& renderingFragmentShadingRateAttachmentInfoKHR = renderInfoExt.renderingFragmentShadingRateAttachmentInfoKHR;
	renderingFragmentShadingRateAttachmentInfoKHR.sType = VK_STRUCTURE_TYPE_RENDERING_FRAGMENT_SHADING_RATE_ATTACHMENT_INFO_KHR;
	renderingFragmentShadingRateAttachmentInfoKHR.imageLayout = VK_IMAGE_LAYOUT_GENERAL;
	renderingFragmentShadingRateAttachmentInfoKHR.imageView = VK_NULL_HANDLE;
	renderingFragmentShadingRateAttachmentInfoKHR.shadingRateAttachmentTexelSize = VkExtent2D{ 1,1 };//ָ��imageView��ÿ��texel��Ӧ����������һ��texelָ�ľ�����imegaView�д���ĳ��λ�ã�x,y������С��Ԫ
	//renderingFragmentShadingRateAttachmentInfoKHR.pNext = nullptr;//�Ѿ���������������㲻������

	/*
	VkRenderingFragmentShadingRateAttachmentInfoKHR�Ϸ��÷�����������˵�����º�VkRenderingFragmentShadingRateAttachmentInfoKHR��Աͬ���ı�����ΪVkRenderingFragmentShadingRateAttachmentInfoKHR�ĳ�Ա��
	1.���imageView����VK_NULL_HANDLE,��
						��1��layout������VK_IMAGE_LAYOUT_GENERAL ����VK_IMAGE_LAYOUT_FRAGMENT_SHADING_RATE_ATTACHMENT_OPTIMAL_KHR
						��2��imageView������VK_IMAGE_USAGE_FRAGMENT_SHADING_RATE_ATTACHMENT_BIT_KHR����
						��3�� minFragmentShadingRateAttachmentTexelSize.width <= shadingRateAttachmentTexelSize.width(2����������) <=maxFragmentShadingRateAttachmentTexelSize.width
						��4�� minFragmentShadingRateAttachmentTexelSize.height <= shadingRateAttachmentTexelSize.height(2����������) <=maxFragmentShadingRateAttachmentTexelSize.height
						��5����shadingRateAttachmentTexelSize.width /  shadingRateAttachmentTexelSize.height�� <= maxFragmentShadingRateAttachmentTexelSizeAspectRatio
						��6�� ��shadingRateAttachmentTexelSize.height /  shadingRateAttachmentTexelSize.width�� <= maxFragmentShadingRateAttachmentTexelSizeAspectRatio
						��7��imageView�����Ǹ���Ч�Ķ���
	*/

	VkRenderingFragmentDensityMapAttachmentInfoEXT& renderingFragmentDensityMapAttachmentInfoEXT = renderInfoExt.renderingFragmentDensityMapAttachmentInfoEXT;
	renderingFragmentDensityMapAttachmentInfoEXT.sType = VK_STRUCTURE_TYPE_RENDERING_FRAGMENT_DENSITY_MAP_ATTACHMENT_INFO_EXT;
	renderingFragmentDensityMapAttachmentInfoEXT.imageLayout = VK_IMAGE_LAYOUT_GENERAL;//���imageView����VK_NULL_HANDLE�������ΪVK_IMAGE_LAYOUT_GENERAL ����
	//VK_IMAGE_LAYOUT_FRAGMENT_DENSITY_MAP_OPTIMAL_EXT
	renderingFragmentDensityMapAttachmentInfoEXT.imageView = VK_NULL_HANDLE;//���imageView����VK_NULL_HANDLE���򴴽����뺬��VK_IMAGE_USAGE_FRAGMENT_DENSITY_MAP_BIT_EXT���Ҳ��ܺ���VK_IMAGE_CREATE_SUBSAMPLED_BIT_EXT��
	//��� multiviewδ������ VkPhysicalDeviceProperties::apiVersionС��vulkan1.1����imageView�� layerCountΪ1

	//renderingFragmentDensityMapAttachmentInfoEXT.pNext = nullptr;//�Ѿ���������������㲻������



	//��ȡrender pass��������Ⱦ����
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
	} VkRenderingAreaInfoKHR;//����ṹ�嵱ǰ��vulkanû�ж��壬��������������ʾ��
	auto vkGetRenderAreaGranularityKHR = [](VkDevice device,
		const VkRenderingAreaInfoKHR* pRenderingAreaInfo,
		VkExtent2D* pGranularity) {

	};//����ӿڵ�ǰ��vulkanû�ж��壬��������������ʾ������ǰvulkanzֻ������vkGetRenderAreaGranularity
	VkRenderingAreaInfoKHR renderAreaInfo{};
	renderAreaInfo.sType = VK_STRUCTURE_TYPE_MAX_ENUM;//��Ϊ��ǰ��vulkanû�ж���ýṹ�壬��������ֱ������Ϊһ���Ƿ���ֵ
	renderAreaInfo.colorAttachmentCount = 0;
	renderAreaInfo.pColorAttachmentFormats = VK_NULL_HANDLE;
	renderAreaInfo.depthAttachmentFormat = VK_FORMAT_UNDEFINED;
	renderAreaInfo.stencilAttachmentFormat = VK_FORMAT_UNDEFINED;
	renderAreaInfo.viewMask = 0;
	renderAreaInfo.pNext = nullptr;

	vkGetRenderAreaGranularityKHR(device, &renderAreaInfo, &renderAreaGranularity);
	/*
		��ѵ�refRenderInfo.renderArea��Ⱦ����Ӧ���ǣ�
			 refRenderInfo.renderArea.offset.xӦ����renderAreaGranularity.width�ı�����
			 refRenderInfo.renderArea.offset.yӦ����renderAreaGranularity.height�ı�����
			 refRenderInfo.renderArea.extent.widthӦ����renderAreaGranularity.width�ı�������refRenderInfo.renderArea.offset.x+refRenderInfo.renderArea.extent.widthҪ�����ڵ�ǰrender pass��ʹ�õĸ����Ŀ��
			 refRenderInfo.renderArea.extent.heightӦ����renderAreaGranularity.height�ı�������refRenderInfo.renderArea.offset.y+refRenderInfo.renderArea.extent.heightҪ�����ڵ�ǰrender pass��ʹ�õĸ����ĸ߶�
	*/


	VkRenderPassStripeBeginInfoARM renderPassStripeBeginInfoARM = renderInfoExt.renderPassStripeBeginInfoARM;//���ﲻ�ٽ�������
	renderPassStripeBeginInfoARM.sType = VK_STRUCTURE_TYPE_MAX_ENUM;//��Ϊvulkanû�ж�������ṹ�壬��������Ϊһ���Ƿ�ֵ
	renderPassStripeBeginInfoARM.pNext = nullptr;
	renderPassStripeBeginInfoARM.stripeInfoCount = 1;
	VkRenderPassStripeInfoARM stripInfo{};
	stripInfo.sType = VK_STRUCTURE_TYPE_MAX_ENUM;//��Ϊvulkanû�ж�������ṹ�壬��������Ϊһ���Ƿ�ֵ
	stripInfo.pNext = nullptr;
	stripInfo.stripeArea = renderInfo.renderArea;//ֱ�ӵ���VkRenderingInfoKHR��renderArea
	renderPassStripeBeginInfoARM.pStripeInfos = nullptr;



	//��BeginRendering ��EndRendering�п��Ե� vkCmdBeginQuery*�Լ�vkCmdEndQuery*���������ӿ����׳�����ͬһ��render pass��



	//framebuffer-local dependencies��subpass֮��






	vkCmdEndRenderingKHR(cmdbuf);//���pRenderingInfo->flagsΪVK_RENDERING_SUSPENDING_BIT������ø�����������render pass�ȴ���һ��render pass��ȡ

	VkTilePropertiesQCOM tilePropertiesQCOM{};
	tilePropertiesQCOM.sType = VK_STRUCTURE_TYPE_TILE_PROPERTIES_QCOM;

	//��ѯdynamic rendering��tile����
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
	renderPassCreateInfo.flags = 0;//VK_RENDER_PASS_CREATE_TRANSFORM_BIT_QCOM ָ����render pass����render pass transform���ԣ�����ı任ָ���Ƕ�����ɫ���вü�����ĵģ�x,y������������ԭ������ת�任������ת90��
	renderPassCreateInfo.attachmentCount = 0;
	renderPassCreateInfo.pAttachments = VK_NULL_HANDLE;
	renderPassCreateInfo.dependencyCount = 0;
	renderPassCreateInfo.pDependencies = VK_NULL_HANDLE;//�������subpass֮��������ݾ���������ĳ��subpass��Ҫ��ĳ��������д���ݣ���ô����Ҫһ��subpass dependence
	renderPassCreateInfo.subpassCount = 0;
	renderPassCreateInfo.pSubpasses = VK_NULL_HANDLE;
	RenderPassCreateInfoExt renderPassCreateInfoExt{};
	renderPassCreateInfo.pNext = &renderPassCreateInfoExt.renderPassFragmentDensityMapCreateInfoEXT;
	/*
	�Ϸ��÷���
	1. ���pSubpasser�е�pInputAttachments, pColorAttachments,pResolveAttachments ���� pDepthStencilAttachment,���� pPreserveAttachments���е�attachment����VK_ATTACHMENT_UNUSED����ôattachment��������С�ڵ���renderPassCreateInfo.attachmentCount
	2. ���pNext�к���VkRenderPassFragmentDensityMapCreateInfoEXT����fragmentDensityMapAttachment����VK_ATTACHMENT_UNUSED����attachment��������С�ڵ���renderPassCreateInfo.attachmentCount
	3. �����κ� pAttachments �� loadOp ���ز���Ϊ VK_ATTACHMENT_LOAD_OP_CLEAR�ĸ�����������������ĵ�һ��ʹ�õĲ��ֲ�����VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL ����VK_IMAGE_LAYOUT_DEPTH_STENCIL_READ_ONLY_OPTIMAL����VK_IMAGE_LAYOUT_DEPTH_READ_ONLY_STENCIL_ATTACHMENT_OPTIMAL
	4. �����κ� pAttachments ��stencilLoadOp���ز���Ϊ VK_ATTACHMENT_LOAD_OP_CLEAR�ĸ�����������������ĵ�һ��ʹ�õĲ��ֲ�����VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL ����VK_IMAGE_LAYOUT_DEPTH_STENCIL_READ_ONLY_OPTIMAL���� VK_IMAGE_LAYOUT_DEPTH_ATTACHMENT_STENCIL_READ_ONLY_OPTIMAL
	5. ���pNext�к���VkRenderPassInputAttachmentAspectCreateInfo����
						��1�� ��VkRenderPassInputAttachmentAspectCreateInfo.pAspectReferences��ÿ��Ԫ�ض�Ӧ��subpass��������С��renderPassCreateInfo.subpassCount
						��2�� ��VkRenderPassInputAttachmentAspectCreateInfo.pAspectReferences��ÿ��Ԫ�ص� inputAttachmentIndex����С��С�ڸ�Ԫ���ж�Ӧ��subpass����Ӧ��inputAttachmentCount
						��3�� ��VkRenderPassInputAttachmentAspectCreateInfo.pAspectReferences��ÿ��Ԫ������Ӧ��subpass�е� pInputAttachments�ĸ�������VK_ATTACHMENT_UNUSED,��ô��VkRenderPassInputAttachmentAspectCreateInfo.pAspectReferencesԪ���е�aspectMaskֵ������ֻ�ܰ�����ӦrenderPassCreateInfo.pAttachments�еĸ����е�aspectMask
	6. ���pNext�к���VkRenderPassMultiviewCreateInfo����
						��1�� ���VkRenderPassMultiviewCreateInfo.subpassCount��Ϊ0�������ΪrenderPassCreateInfo.subpassCount
						��2�� ���VkRenderPassMultiviewCreateInfo.dependencyCount��Ϊ0�������ΪrenderPassCreateInfo.dependencyCount
						��3�� ��ӦVkRenderPassMultiviewCreateInfo.pViewOffsets��ÿ������ֵ�� srcSubpass �� dstSubpass�������ͬ������renderPassCreateInfo.pDependencies����ͬ
						��4�� �����κ�renderPassCreateInfo.pDependencies��dependencyFlagsû�к���VK_DEPENDENCY_VIEW_LOCAL_BIT����ô��ͬ������VkRenderPassMultiviewCreateInfo.pViewOffsets��ֵ������0
						��5�� ��� VkRenderPassMultiviewCreateInfo.pViewMasks��ÿ��Ԫ�ض���0,�� VkRenderPassMultiviewCreateInfo.correlationMaskCountҲ��0�������κ�renderPassCreateInfo.pDependencies��dependencyFlags���ܺ���VK_DEPENDENCY_VIEW_LOCAL_BIT
	7. �����κ�pDependencies�е�Ԫ��,���srcSubpass/dstSubpass ���� VK_SUBPASS_EXTERNAL ����ôsrcSubpass/dstSubpass����С��subpassCount�� ����ô srcStageMask/dstStageMask������pipelineBindPoint�󶨵�pipeline��֧�ֵĹ���״̬					 

	8. ��� attachmentCount��subpassCount���Լ�dependencyCount����Ϊ0��pAttachments��pSubpasses�Լ�pDependencies����Ҫ��һ����Ч�ĺ��� VkAttachmentDescription��VkSubpassDescription�Լ� VkSubpassDependency��Ч���ݵ������ָ��
	9. subpassCount�������0


	*/


	//VkRenderPassCreateInfo�������ӵ���չ�ṹ��
	VkRenderPassMultiviewCreateInfo& renderPassMultiviewCreateInfo = renderPassCreateInfoExt.renderPassMultiviewCreateInfo;
	renderPassMultiviewCreateInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_MULTIVIEW_CREATE_INFO;
	renderPassMultiviewCreateInfo.subpassCount = 1;//Ϊ0����render pass��subpass����
	renderPassMultiviewCreateInfo.dependencyCount = 1;//Ϊ0����render pass��dependency����
	renderPassMultiviewCreateInfo.correlationMaskCount = 0;
	renderPassMultiviewCreateInfo.pCorrelationMasks = nullptr;// correlationMaskCount��view masksָ����Щviews���Ը���Ч��ͬʱ������Ⱦ
	renderPassMultiviewCreateInfo.pViewMasks = VK_NULL_HANDLE;//subpassCount��viewMask��ÿ��viewMask�Ǹ�view������λ�ֶ������ĸ�view����subpass�б���Ⱦ���� multiview����������� subpassCountΪ0��pViewMasks��ÿ������Ϊ��0
	renderPassMultiviewCreateInfo.pViewOffsets = VK_NULL_HANDLE;// dependencyCount��viewOffset��ÿ��dependenceһ�������dependencyCountΪ0��pViewOffsets��ÿ������Ϊ��0��ÿ��viewOffset����ÿ��dstSubpass����srcSubpass��view��ƫ����
	//��������multiView���������ĵ�p519
	/*
	�Ϸ��÷���
	1. ÿ��view index���ܱ�������pCorrelationMasks�Ķ������
	2.  multiview���û�п������� pViewMasks������ֵ����0
	3.  pViewMasks�е�ֵ��������Чλ���ܳ���maxMultiviewViewCount
	4. ���subpassCount��dependencyCount���Լ�correlationMaskCount����Ϊ0����pCorrelationMasks��pViewMasks�Լ�pViewOffsets����Ҫ��һ��uint32_t,int32_t,uint32_t����Ч�������ָ��
	*/


	//���Ӧ����subpass��չ�Ķ���ṹ��
	VkMultiviewPerViewAttributesInfoNVX multiviewPerViewAttributesInfoNVX{};//��������������subpass������Ϣ��pNext��
	multiviewPerViewAttributesInfoNVX.sType = VK_STRUCTURE_TYPE_MULTIVIEW_PER_VIEW_ATTRIBUTES_INFO_NVX;
	multiviewPerViewAttributesInfoNVX.pNext = nullptr;
	multiviewPerViewAttributesInfoNVX.perViewAttributes = VK_FALSE;//ָ��Ϊ�˹ܵ��������ɫ����ÿ�����㴦��׶εĵ���������Ϊ����view������ԣ���д per-view attributes �� *PerViewNV[]��ɫ����������� non-per-view (e.g. Position) ���.
	multiviewPerViewAttributesInfoNVX.perViewAttributesPositionXOnly = VK_FALSE;//ָ����ǰpipeline�������ɫ����ʹ��ֻ��x������ͬ��per-view positions�� Per-view viewport maskҲ���Ա�ʹ��
	//���ʹ��dynamic render passʵ����������Ⱦ��������subpass������Ϣ��ָ��VK_SUBPASS_DESCRIPTION_PER_VIEW_ATTRIBUTES_BIT_NVX ����VK_SUBPASS_DESCRIPTION_PER_VIEW_POSITION_X_ONLY_BIT_NVX��
	//����Ҫ��VkMultiviewPerViewAttributesInfoNVX�����ڴ���pipeline��fVkGraphicsPipelineCreateInfo�У��ڿ�ʼ��̬��Ⱦ�� VkRenderingInfo�У���ָ����̬��Ⱦ�Ĵμ�������������VkCommandBufferInheritanceInfo��




	//VkRenderPassCreateInfo�������ӵ���չ�ṹ��
	VkRenderPassFragmentDensityMapCreateInfoEXT &renderPassFragmentDensityMapCreateInfoEXT = renderPassCreateInfoExt.renderPassFragmentDensityMapCreateInfoEXT;
	renderPassFragmentDensityMapCreateInfoEXT.fragmentDensityMapAttachment = VkAttachmentReference{
	.attachment = 0,/*
		���attachment��Ӧ��imageView��VK_IMAGE_VIEW_CREATE_FRAGMENT_DENSITY_MAP_DYNAMIC_BIT_EXT��������ôfragment density map���� VK_PIPELINE_STAGE_FRAGMENT_DENSITY_PROCESS_BIT_EXT�׶α�device��ȡ��
		���attachment��Ӧ��imageView��VK_IMAGE_VIEW_CREATE_FRAGMENT_DENSITY_MAP_DEFERRED_BIT_EXT��������ôfragment density map������Ҫ��������� vkEndCommandBuffer�����б�host��ȡ
		�������������vkCmdBeginRenderPass��host��ȡ
	*/
	.layout = VK_IMAGE_LAYOUT_ATTACHMENT_OPTIMAL };
	/*
	�Ϸ��÷���
	1.���fragmentDensityMapAttachment����VK_ATTACHMENT_UNUSED��
							��1����fragmentDensityMapAttachment���������κ�subpass��VkSubpassDescription::pInputAttachments,VkSubpassDescription::pColorAttachments, VkSubpassDescription::pResolveAttachments,
								VkSubpassDescription::pDepthStencilAttachment, ���� VkSubpassDescription::pPreserveAttachments
	                        ��2����layout ����ΪVK_IMAGE_LAYOUT_FRAGMENT_DENSITY_MAP_OPTIMAL_EXT, ���� VK_IMAGE_LAYOUT_GENERAL
							��3�� fragmentDensityMapAttachment���õ�attachment�� loadOp ����Ϊ VK_ATTACHMENT_LOAD_OP_LOAD ���� VK_ATTACHMENT_LOAD_OP_DONT_CARE
							��3�� fragmentDensityMapAttachment���õ�attachment�� storeOp ����Ϊ VK_ATTACHMENT_STORE_OP_DONT_CARE 
	2. ���õ�attachment��������Ч��
	*/


	//VkAttachmentDescription ��������
	VkAttachmentDescription colorAttachment{};
	colorAttachment.format = VK_FORMAT_R8G8B8_SRGB;
	colorAttachment.flags = VK_ATTACHMENT_DESCRIPTION_MAY_ALIAS_BIT;//VK_ATTACHMENT_DESCRIPTION_MAY_ALIAS_BIT��������ָ�����������ͬһrender pass���������������ڴ棨���總����ʹ��ͬһ��imageView����ʹ�ò�ͬ��imageView�������õ���ͬ��image��subResource,�������õĲ�����ͬ��image��subResourceRange���ǰ󶨵���ͬ���ڴ��ص�����
	//���flags�а���VK_ATTACHMENT_DESCRIPTION_MAY_ALIAS_BIT���������subpass��������д��������ô����Ҫһ��memory dependence����֤д��˳��,��dependence������ VK_DEPENDENCY_BY_REGION_BIT����ǲ�ͬ��image��subResource���ǰ󶨵���ͬ���ڴ��ص������������������VK_ATTACHMENT_DESCRIPTION_MAY_ALIAS_BIT�ĸ���������ͬһ��subpass��ʹ�ã�
	//������������VK_ATTACHMENT_DESCRIPTION_MAY_ALIAS_BIT����ͬһ����ͻ�������render pass��һ����ʹ��attachment��initialLayout��������attachment��initialLayout��������VK_IMAGE_LAYOUT_UNDEFINED
	colorAttachment.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;//ָ��render pass��ʼʱ��ĸ�������
	colorAttachment.finalLayout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;//ָ��render pass����ʱ��ĸ�������
	colorAttachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;//����color attachment�ļ��ز������߸���depth���ݵļ��ز���
	colorAttachment.storeOp = VK_ATTACHMENT_STORE_OP_STORE;//����color attachment�Ĵ洢�������߸���depth���ݵĴ洢����
	colorAttachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_NONE_EXT;//���Ƹ���stencil���ݵļ��ز���
	colorAttachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_NONE;//���Ƹ���stencil���ݵĴ洢����
	colorAttachment.samples = VK_SAMPLE_COUNT_1_BIT;
	/*
	VkAttachmentDescription�Ϸ��÷���
	1. ���format����color�Լ�depth���ݣ���loadOpΪVK_ATTACHMENT_LOAD_OP_LOAD����initialLayout������VK_IMAGE_LAYOUT_UNDEFINED
	2. finalLayout ������ VK_IMAGE_LAYOUT_UNDEFINED ����VK_IMAGE_LAYOUT_PREINITIALIZED
	3. ���format��color��ʽ��initialLayout��finalLayout ������VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL ����VK_IMAGE_LAYOUT_DEPTH_STENCIL_READ_ONLY_OPTIMAL��
															 VK_IMAGE_LAYOUT_DEPTH_ATTACHMENT_STENCIL_READ_ONLY_OPTIMAL ����
															 VK_IMAGE_LAYOUT_DEPTH_READ_ONLY_STENCIL_ATTACHMENT_OPTIMAL��
															 VK_IMAGE_LAYOUT_DEPTH_ATTACHMENT_OPTIMAL, VK_IMAGE_LAYOUT_DEPTH_READ_ONLY_OPTIMAL,
															 VK_IMAGE_LAYOUT_STENCIL_ATTACHMENT_OPTIMAL, ����
															 VK_IMAGE_LAYOUT_STENCIL_READ_ONLY_OPTIMAL
	4. ���format��depth/stencil��ʽ��initialLayout��finalLayout������VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL
	5. ��� separateDepthStencilLayouts��depth��stencil�����Ƿ��ֿܷ�������û�п�������ô initialLayout�Լ�finalLayout������
																			VK_IMAGE_LAYOUT_DEPTH_ATTACHMENT_OPTIMAL, VK_IMAGE_LAYOUT_DEPTH_READ_ONLY_OPTIMAL,
																			VK_IMAGE_LAYOUT_STENCIL_ATTACHMENT_OPTIMAL,����
																			VK_IMAGE_LAYOUT_STENCIL_READ_ONLY_OPTIMAL,
	6. ���format��depth/stencil��ʽ���Һ���depth��stencil���ݻ���ֻ����stencil���ݣ���initialLayout��finalLayout������VK_IMAGE_LAYOUT_STENCIL_ATTACHMENT_OPTIMAL ����
																								  VK_IMAGE_LAYOUT_STENCIL_READ_ONLY_OPTIMAL��VK_IMAGE_LAYOUT_DEPTH_ATTACHMENT_OPTIMAL 
																								  ����VK_IMAGE_LAYOUT_DEPTH_READ_ONLY_OPTIMAL

	7. ���synchronization2����δ������initialLayout��finalLayout������VK_IMAGE_LAYOUT_ATTACHMENT_OPTIMAL_KHR ���� VK_IMAGE_LAYOUT_READ_ONLY_OPTIMAL_KHR
	8. ���attachmentFeedbackLoopLayout����δ������initialLayout��finalLayout������VK_IMAGE_LAYOUT_ATTACHMENT_FEEDBACK_LOOP_OPTIMAL_EXT
	9. samples�����Ǳ����image����ʱ���samples��ͬ
	10. ���dynamicRenderingLocalRead����δ������initialLayout��finalLayout������VK_IMAGE_LAYOUT_RENDERING_LOCAL_READ_KHR
	11. format����ΪVK_FORMAT_UNDEFINED
	12. ���format ��stencil ������ stencilLoadOp �� VK_ATTACHMENT_LOAD_OP_LOAD,�� initialLayout ����Ϊ VK_IMAGE_LAYOUT_UNDEFINED
	
	
	
	*/

	VkAttachmentReference colorAttachmentRef{};
	colorAttachmentRef.attachment = 0;//����VkRenderPassCreateInfo.pAttachments�еĵ�0��attachment
	colorAttachmentRef.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;//ָ��attachment�Ĳ���


	//VkRenderPassCreateInfo�������ӵ���չ�ṹ��
	VkRenderPassInputAttachmentAspectCreateInfo& renderPassInputAttachmentAspectCreateInfo = renderPassCreateInfoExt.renderPassInputAttachmentAspectCreateInfo;
	renderPassInputAttachmentAspectCreateInfo.aspectReferenceCount = 0;
	VkInputAttachmentAspectReference inputAttachmentAspectReference{};
	inputAttachmentAspectReference.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
	inputAttachmentAspectReference.subpass = 0;//aspectMask����ΪVK_IMAGE_ASPECT_METADATA_BIT�Լ������κ����� i������ΪVK_IMAGE_ASPECT_MEMORY_PLANE_i_BIT_EXT 
	inputAttachmentAspectReference.inputAttachmentIndex = 0;//pCreateInfo->pSubpasses[subpass].pInputAttachments[inputAttachmentIndex]
	renderPassInputAttachmentAspectCreateInfo.pAspectReferences = &inputAttachmentAspectReference;//��VkInputAttachmentAspectReference�ĳ���ΪaspectReferenceCount�����飬ÿ��Ԫ��������ĳ��subpass�����븽����aspectMask�Լ���Ӧ���븽��������
	//���pAspectReferencesû��ָ��ĳ��subpass�����븽����aspectMask���������Է��ʸø���������aspectMask������Ѿ�ָ����ֻ�ܷ���ָ����aspectMask




	//subpass����,��Ҫ���������Լ�subpass���ô�
	VkSubpassDescription subpassDescription{};
	subpassDescription.flags = 0;/*
	todo 20240617
	
	*/
	subpassDescription.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
	subpassDescription.colorAttachmentCount = 1;
	subpassDescription.pColorAttachments = VK_NULL_HANDLE;//pColorAttachments����ɫ���п���ͨ��ָ��������������ʶ���з��ʣ�����glsl��ʾ��layout (location = 0) out vec4 color;
	subpassDescription.pResolveAttachments = VK_NULL_HANDLE;//���flags������VK_SUBPASS_DESCRIPTION_SHADER_RESOLVE_BIT_QCOM,��pResolveAttachments����VK_NULL_HANDLE,��pResolveAttachments�е�ÿ��Ԫ�ض���Ϊһһ��Ӧ��color attachment����һ������������������resolve attachment��VK_ATTACHMENT_UNUSED.
	subpassDescription.inputAttachmentCount = 0;
	subpassDescription.pInputAttachments = VK_NULL_HANDLE;//pInputAttachments����ɫ���п���ͨ��ָ��������������ʶ���з��ʣ�����glsl��ʾ��layout (input_attachment_index = 0, set = 0, binding = 0) uniform subpassInput myInputAttachment;
	subpassDescription.preserveAttachmentCount = 0;
	subpassDescription.pPreserveAttachments = VK_NULL_HANDLE;//��p532
	subpassDescription.pDepthStencilAttachment = VK_NULL_HANDLE;//���flags������VK_SUBPASS_DESCRIPTION_SHADER_RESOLVE_BIT_QCOM����VkSubpassDescriptionDepthStencilResolve::pDepthStencilResolveAttachment��ΪNULL�Ҷ�Ӧ��attachment��ΪVK_ATTACHMENT_UNUSED����
	//��ΪpDepthStencilAttachment������VkSubpassDescriptionDepthStencilResolve::depthResolveMode�Լ�VkSubpassDescriptionDepthStencilResolve::stencilResolveMode�ĳ��������������VkSubpassDescriptionDepthStencilResolve::depthResolveMode��VK_RESOLVE_MODE_NONE��
	//����pDepthStencilResolveAttachmentû�� depth aspect,�򲻻�Ϊdepth���峬�������������VkSubpassDescriptionDepthStencilResolve::stencilResolveMode��VK_RESOLVE_MODE_NONE������pDepthStencilResolveAttachmentû�� stencil aspeck���򲻻�Ϊstencil���峬����������
	//���depth/stencil�ĸ������õ�image����ΪVK_IMAGE_CREATE_SAMPLE_LOCATIONS_COMPATIBLE_DEPTH_BIT_EXT�����Ӧ�ĳ�������������VkRenderPassSampleLocationsBeginInfoEXT::pPostSubpassSampleLocations�е� sampleLocationsInfo ������

	/*
	VkSubpassDescription�Ϸ��÷���
	1. ���pInputAttachments��attachment���� VK_ATTACHMENT_UNUSED����layout������VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL ���� VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL��
																															   VK_IMAGE_LAYOUT_DEPTH_ATTACHMENT_OPTIMAL ����VK_IMAGE_LAYOUT_STENCIL_ATTACHMENT_OPTIMAL��
																															   VK_IMAGE_LAYOUT_ATTACHMENT_OPTIMAL_KHR
	2. ��� pColorAttachments����pResolveAttachments��attachment���� VK_ATTACHMENT_UNUSED����layout������ VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL ����VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL��
																										  VK_IMAGE_LAYOUT_DEPTH_ATTACHMENT_STENCIL_READ_ONLY_OPTIMAL ����
																										  VK_IMAGE_LAYOUT_DEPTH_READ_ONLY_STENCIL_ATTACHMENT_OPTIMAL��
																										  VK_IMAGE_LAYOUT_DEPTH_ATTACHMENT_OPTIMAL,VK_IMAGE_LAYOUT_DEPTH_READ_ONLY_OPTIMAL,
																										  VK_IMAGE_LAYOUT_STENCIL_ATTACHMENT_OPTIMAL, ���� VK_IMAGE_LAYOUT_STENCIL_READ_ONLY_OPTIMAL��
																										  VK_IMAGE_LAYOUT_READ_ONLY_OPTIMAL_KHR
	3. ��� pDepthStencilAttachment��attachment���� VK_ATTACHMENT_UNUSED����layout������VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL ����VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL
	4. pipelineBindPoint������VK_PIPELINE_BIND_POINT_GRAPHICS ����VK_PIPELINE_BIND_POINT_SUBPASS_SHADING_HUAWEI
	5. colorAttachmentCount����С�ڵ���VkPhysicalDeviceLimits::maxColorAttachments
	6. ���һ��attachment��render pass�еĵ�һ��ʹ����Ϊinput attachment�������ڸ�subpass�в�����Ϊcolor ���� depth/stencil�����������loadOp������ VK_ATTACHMENT_LOAD_OP_CLEAR
	7. ���pResolveAttachments����NULL,�����е�Ԫ�ض�Ӧ��resolve attachmentҲ����VK_ATTACHMENT_UNUSED,��
										    ��1�����Ӧ��color attachmentҲ������VK_ATTACHMENT_UNUSED��
										    ��2�������Ӧ�ĵ�color attachment�Ĳ�����������VK_SAMPLE_COUNT_1_BIT
											��3�����е�Ԫ�ض�Ӧ��resolve attachment�Ĳ�����������VK_SAMPLE_COUNT_1_BIT
											��4�����е�Ԫ�ض�Ӧ��resolve attachment��formatҪ�Ͷ�Ӧ��color attachment��format��ͬ
	8. pColorAttachments�в��� VK_ATTACHMENT_UNUSED�����и����Ĳ�����������ͬ
	9.  pInputAttachments�в���VK_ATTACHMENT_UNUSED��attachment���뺬��ӵ��potential format features ����p4100������ΪVK_FORMAT_FEATURE_COLOR_ATTACHMENT_BIT ����VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT�� image format
	10. pColorAttachments����pResolveAttachments�в���VK_ATTACHMENT_UNUSED��attachment���뺬��ӵ��potential format features ����p4100��Ϊ VK_FORMAT_FEATURE_COLOR_ATTACHMENT_BIT�� image format
	11. pDepthStencilAttachment ���� NULL �� ��attachment ���� VK_ATTACHMENT_UNUSEDVK_ATTACHMENT_UNUSED�� ��attachment���뺬��ӵ��potential format features ����p4100��Ϊ VK_FORMAT_FEATURE_COLOR_ATTACHMENT_BIT�� image format
	12. ��� linearColorAttachment���Կ�����image����ΪVK_IMAGE_TILING_LINEAR,��
											��1��pInputAttachments�в���VK_ATTACHMENT_UNUSED��attachment���뺬��ӵ��potential format features ����p4100��ΪVK_FORMAT_FEATURE_2_LINEAR_COLOR_ATTACHMENT_BIT_NV�� image format
											��2��pColorAttachments����pResolveAttachments�в���VK_ATTACHMENT_UNUSED��attachment���뺬��ӵ��potential format features ����p4100��Ϊ  VK_FORMAT_FEATURE_2_LINEAR_COLOR_ATTACHMENT_BIT_NV�� image format
	13. ��� VK_AMD_mixed_attachment_samples���� VK_NV_framebuffer_mixed_samples���Կ�������pColorAttachments�в���VK_ATTACHMENT_UNUSED��attachment�Ĳ���������С��pDepthStencilAttachment�������ΪVK_ATTACHMENT_UNUSED����attachment�Ĳ�����
	14. ��� VK_AMD_mixed_attachment_samples���� VK_NV_framebuffer_mixed_samples���Զ�û�п��������pResolveAttachments����VK_ATTACHMENT_UNUSED����pColorAttachments�в���VK_ATTACHMENT_UNUSED��attachment�Ĳ�����������ͬ��
	15.  pPreserveAttachments�е�ÿ��Ԫ�ز�����VK_ATTACHMENT_UNUSED���Ҳ�����subpass description�е���������
	16. ���һ������attachment����� VkAttachmentReference���ã���ô��Щ���ñ�������ͬ��layout
	17. ���flags���� VK_SUBPASS_DESCRIPTION_PER_VIEW_POSITION_X_ONLY_BIT_NVX�����仹�������VK_SUBPASS_DESCRIPTION_PER_VIEW_ATTRIBUTES_BIT_NVX
	18.  ���flags����VK_SUBPASS_DESCRIPTION_SHADER_RESOLVE_BIT_QCOM����
												��1�����pResolveAttachments����NULL,��pResolveAttachments�е�ÿ��Ԫ�ص�attachment������VK_ATTACHMENT_UNUSED
												��2����ǰ��subpass������subpass dependence�е����һ��subpass
												��3��pInputAttachments�е�ÿ��Ԫ�ر����� VK_ATTACHMENT_UNUSED
	19. pDepthStencilAttachment �� pColorAttachments����ͬʱָ��ͬһ��attachment
	
	*/










}





























NS_TEST_END