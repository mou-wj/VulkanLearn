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
	VkRenderPassFragmentDensityMapCreateInfoEXT& renderPassFragmentDensityMapCreateInfoEXT = renderPassCreateInfoExt.renderPassFragmentDensityMapCreateInfoEXT;
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
	6. ���format��depth/stencil��ʽ���Һ���depth��stencil���ݻ���ֻ����depth���ݣ���initialLayout��finalLayout������VK_IMAGE_LAYOUT_STENCIL_ATTACHMENT_OPTIMAL ����
																								  VK_IMAGE_LAYOUT_STENCIL_READ_ONLY_OPTIMAL��


	7. ���synchronization2����δ������initialLayout��finalLayout������VK_IMAGE_LAYOUT_ATTACHMENT_OPTIMAL_KHR ���� VK_IMAGE_LAYOUT_READ_ONLY_OPTIMAL_KHR
	8. ���attachmentFeedbackLoopLayout����δ������initialLayout��finalLayout������VK_IMAGE_LAYOUT_ATTACHMENT_FEEDBACK_LOOP_OPTIMAL_EXT
	9. samples�����Ǳ����image����ʱ���samples��ͬ
	10. ���dynamicRenderingLocalRead����δ������initialLayout��finalLayout������VK_IMAGE_LAYOUT_RENDERING_LOCAL_READ_KHR
	11. format����ΪVK_FORMAT_UNDEFINED
	12. ���format ��stencil ������ stencilLoadOp �� VK_ATTACHMENT_LOAD_OP_LOAD,�� initialLayout ����Ϊ VK_IMAGE_LAYOUT_UNDEFINED
	13.���format��depth/stencil��ʽ����ֻ����stencil���ݣ���initialLayout��finalLayout������VK_IMAGE_LAYOUT_DEPTH_ATTACHMENT_OPTIMAL
																								  ����VK_IMAGE_LAYOUT_DEPTH_READ_ONLY_OPTIMAL
	14. ���format��depth/stencil��ʽ���Һ���depth��stencil���ݣ���initialLayout��finalLayout������VK_IMAGE_LAYOUT_DEPTH_ATTACHMENT_OPTIMAL ����VK_IMAGE_LAYOUT_DEPTH_READ_ONLY_OPTIMAL

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
		VK_SUBPASS_DESCRIPTION_PER_VIEW_ATTRIBUTES_BIT_NVX: ָ����ǰsubpass�������ɫ������ pre-rasterization ��ɫ���׶εĵ���������Ϊ����view������ԣ����������ǰ��־�����subpass������� *PerViewNV[]�����������non-per-view (e.g. Position) outputs.
		VK_SUBPASS_DESCRIPTION_PER_VIEW_POSITION_X_ONLY_BIT_NVX: ָ����ǰsubpass�������ɫ��ʹ��per-view positions��ֻ��x������ͬ��Per-view viewport maskҲ����ʹ��
		VK_SUBPASS_DESCRIPTION_FRAGMENT_REGION_BIT_QCOM: ָ����ǰsubpass��framebuffer region �� fragment region������С��region dependence�ǻ���pixel�ģ������ǻ���sample�ģ��κ�fragment shader�����Է��ʵ�ǰfragment shader���õĵ��κ�sample
		VK_SUBPASS_DESCRIPTION_SHADER_RESOLVE_BIT_QCOM: ָ����ǰsubpassִ��shader resolve�����������Զ���resolve������
		VK_SUBPASS_DESCRIPTION_RASTERIZATION_ORDER_ATTACHMENT_COLOR_ACCESS_BIT_EXT: ָ����ǰsubpass֧����VK_PIPELINE_COLOR_BLEND_STATE_CREATE_RASTERIZATION_ORDER_ATTACHMENT_ACCESS_BIT_EXT.������pipeline
		VK_SUBPASS_DESCRIPTION_RASTERIZATION_ORDER_ATTACHMENT_DEPTH_ACCESS_BIT_EXT: ָ����ǰsubpass֧����VK_PIPELINE_DEPTH_STENCIL_STATE_CREATE_RASTERIZATION_ORDER_ATTACHMENT_DEPTH_ACCESS_BIT_EXT.������pipeline
		VK_SUBPASS_DESCRIPTION_RASTERIZATION_ORDER_ATTACHMENT_STENCIL_ACCESS_BIT_EXT: ָ����ǰsubpass֧����VK_PIPELINE_DEPTH_STENCIL_STATE_CREATE_RASTERIZATION_ORDER_ATTACHMENT_STENCIL_ACCESS_BIT_EXT.������pipeline
		VK_SUBPASS_DESCRIPTION_ENABLE_LEGACY_DITHERING_BIT_EXT: ָ����ǰsubpass����legacy dithering

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
	11. pDepthStencilAttachment ���� NULL �� ��attachment ���� VK_ATTACHMENT_UNUSED�� ��attachment���뺬��ӵ��potential format features ����p4100��Ϊ VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT�� image format
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



	VkAttachmentReference unusedAttachmentRef;//����һ���յ�VkAttachmentReference
	unusedAttachmentRef.attachment = VK_ATTACHMENT_UNUSED;//attachment����ΪVK_ATTACHMENT_UNUSED,˵����ǰreference��attachment�ǿյ�
	unusedAttachmentRef.layout = VK_IMAGE_LAYOUT_UNDEFINED;
	/*
	1.���attachment��VK_ATTACHMENT_UNUSED����layout����Ϊ VK_IMAGE_LAYOUT_UNDEFINED,VK_IMAGE_LAYOUT_PREINITIALIZED, ���� VK_IMAGE_LAYOUT_PRESENT_SRC_KHR
	2.���attachment��VK_ATTACHMENT_UNUSED����separateDepthStencilLayouts����û�п�������layout����ΪVK_IMAGE_LAYOUT_DEPTH_ATTACHMENT_OPTIMAL,
				VK_IMAGE_LAYOUT_DEPTH_READ_ONLY_OPTIMAL, VK_IMAGE_LAYOUT_STENCIL_ATTACHMENT_OPTIMAL, ��VK_IMAGE_LAYOUT_STENCIL_READ_ONLY_OPTIMAL
	3.���synchronization2����û�п�������layout����ΪVK_IMAGE_LAYOUT_ATTACHMENT_OPTIMAL_KHR ���� VK_IMAGE_LAYOUT_READ_ONLY_OPTIMAL_KHR
	4. ���attachmentFeedbackLoopLayout����û�п�������layout����ΪVK_IMAGE_LAYOUT_ATTACHMENT_FEEDBACK_LOOP_OPTIMAL_EXT
	5. ���dynamicRenderingLocalRead����û�п�������layout����ΪVK_IMAGE_LAYOUT_RENDERING_LOCAL_READ_KHR
	6. layout�����ǺϷ���ֵ

	*/


	VK_SUBPASS_EXTERNAL;//ָ����һ���ⲿ��subpass
	VkSubpassDependency subpassDependency;//����һ���յ�VkSubpassDependency,VkSubpassDependency���ã�
	//��srcSubpass��dstSubpassһ��ʱ��VkSubpassDependency�൱�ڶ�����һ��pipeline barriers������һ��ʱ�Ŷ������ύ�����е�subpass��������ϵ�����srcSubpassΪVK_SUBPASS_EXTERNAL��
	//���һ��ͬ����Ϊ vkCmdBeginRenderPass�ύ˳��֮ǰ������������dstSubpassΪ VK_SUBPASS_EXTERNAL,��ڶ���ͬ����Ϊ vkCmdEndRenderPass�ύ˳��֮������������Ҫ������Щsubpass�Ը���load��store�Լ�resolve�����Ĺ���״̬
	subpassDependency.srcSubpass = VK_SUBPASS_EXTERNAL;
	subpassDependency.srcAccessMask = VK_ACCESS_NONE;
	subpassDependency.srcStageMask = VK_PIPELINE_STAGE_NONE;
	subpassDependency.dstSubpass = 0;
	subpassDependency.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
	subpassDependency.dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
	subpassDependency.dependencyFlags = 0;

	/*
	��Ч�÷���
	1.���Ժ͹���״̬��ƥ�䣬��ͬ���½ڡ�
	2.��� synchronization2����û�п�������srcStageMask��dstStageMask����Ϊ0
	3.���  VK_NV_ray_tracing��չ���� rayTracingPipeline����û�п�������srcStageMask��dstStageMask���ܰ��� VK_PIPELINE_STAGE_RAY_TRACING_SHADER_BIT_KHR
	4.srcSubpass����С��dstSubpass,����������һ��ΪVK_SUBPASS_EXTERNAL��������������VK_SUBPASS_EXTERNAL
	5.���srcSubpass����dstSubpass�����srcStageMask���� framebuffer-space stage,��dstStageMaskҲ�������framebuffer-space stage
	6.���ʿ��ƺ͹���״̬��Ҫƥ�䣬��ͬ���½�
	7.���srcSubpass����dstSubpass�����srcStageMask��dstStageMask������ framebuffer-space stage,�� dependencyFlags�������VK_DEPENDENCY_BY_REGION_BIT
	8.��� dependencyFlags����VK_DEPENDENCY_VIEW_LOCAL_BIT����srcSubpass��dstSubpass������VK_SUBPASS_EXTERNAL
	9.���srcSubpass����dstSubpass���Ҹ�subpass��view mask�г���һ��bitλ���ã���dependencyFlags�������VK_DEPENDENCY_VIEW_LOCAL_BIT
	*/


	{
		VkCommandBuffer cmdbuf;
		//��̬�����Ǹ�������loop��ʶ�����ĸ�����д�룬ֻ���Ժ���VK_DYNAMIC_STATE_ATTACHMENT_FEEDBACK_LOOP_ENABLE_EXT��̬״̬������pipeline��ʹ��
		vkCmdSetAttachmentFeedbackLoopEnableEXT(cmdbuf, VkImageAspectFlagBits::VK_IMAGE_ASPECT_COLOR_BIT);
		/*
		 1.attachmentFeedbackLoopDynamicState���Ա��뿪��
		 2.aspectMaskֻ�ܰ���VK_IMAGE_ASPECT_NONE, VK_IMAGE_ASPECT_COLOR_BIT,VK_IMAGE_ASPECT_DEPTH_BIT, �Լ� VK_IMAGE_ASPECT_STENCIL_BIT
		 2.���attachmentFeedbackLoopLayout����û�п�������aspectMaskֻ��ΪVK_IMAGE_ASPECT_NONE
		*/
	}

	//����render pass
	vkCreateRenderPass(device, &renderPassCreateInfo, nullptr, &renderPass);

	vkDestroyRenderPass(device, renderPass, nullptr);











	//����render pass 2

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
	�Ϸ��÷���
	1.ֻҪ����subpass�з�����ͬ��������ͬ����������һ������д����������붨��һ��������ϵ
	2.����κ�pInputAttachments, pColorAttachments,pResolveAttachments ���� pDepthStencilAttachment, pPreserveAttachments��attachment���ڴ�����ص������attachment��Ӧ�ĸ�����flags�������VK_ATTACHMENT_DESCRIPTION_MAY_ALIAS_BIT
	3.����κ�pInputAttachments, pColorAttachments,pResolveAttachments ���� pDepthStencilAttachment, pPreserveAttachments��attachment����VK_ATTACHMENT_UNUSED,��attachment����С��attachmentCount
	4.��� VkRenderPassFragmentDensityMapCreateInfoEXT������pNext����fragmentDensityMapAttachment��attachment��Ӧ�ĸ�������VK_ATTACHMENT_UNUSED�����attachment����С��attachmentCount
	5.���VkSubpassDescriptionDepthStencilResolve������pNext����pDepthStencilResolveAttachment����NULL����attachment��Ӧ�ĸ�������VK_ATTACHMENT_UNUSED�����attachment����С��attachmentCount
	6.�����κ� pAttachments �� loadOp ���ز���Ϊ VK_ATTACHMENT_LOAD_OP_CLEAR�ĸ�����������������ĵ�һ��ʹ�õĲ��ֲ�����VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL ����VK_IMAGE_LAYOUT_DEPTH_STENCIL_READ_ONLY_OPTIMAL����VK_IMAGE_LAYOUT_DEPTH_READ_ONLY_STENCIL_ATTACHMENT_OPTIMAL
	7.�����κ� pAttachments ��stencilLoadOp���ز���Ϊ VK_ATTACHMENT_LOAD_OP_CLEAR�ĸ�����������������ĵ�һ��ʹ�õĲ��ֲ�����VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL ����VK_IMAGE_LAYOUT_DEPTH_STENCIL_READ_ONLY_OPTIMAL���� VK_IMAGE_LAYOUT_DEPTH_ATTACHMENT_STENCIL_READ_ONLY_OPTIMAL
	8.��� pDependencies��srcSubpass�Լ�dstSubpass������VK_SUBPASS_EXTERNAL����srcStageMask�Լ�dstStageMask���뱻pipelineBindPoint�󶨵�pipeline֧��
	9.pCorrelatedViewMasks�в��ܺ���λ�ص�������view mask
	10.�������subpass��VkSubpassDescription2::viewMaskΪ0����correlatedViewMaskCount����Ϊ0���κ�subpass��VkSubpassDescription2::viewMaskҪôȫΪ0��Ҫôȫ��Ϊ0�����ȫΪ0����pDependencies��flags���ܺ���VK_DEPENDENCY_VIEW_LOCAL_BIT
	11.���pDependencies��ĳ��dependence��srcSubpass����dstSubpass���������Ӧ��subpass�� viewMask������ֹһ��λ�����dependence��Ҫ����VK_DEPENDENCY_VIEW_LOCAL_BIT
	12.��� pSubpasses�� pInputAttachments��attachment��Ӧ��VkRenderPassCreateInfo2.pAttachments���� VK_ATTACHMENT_UNUSED�����subpass��pInputAttachments��aspectMask���������VkRenderPassCreateInfo2.pAttachments�����е�aspectMask֮��
	13.�κ�denpendence��srcSubpass��dstSubpass����С��subpassCount
	14.���pAttachments���κθ�����ĳsubpass������ fragment shading rate attachment����ø����Ͳ����ڸ�render pass�����������ĸ�����������loadOpҲ����ΪVK_ATTACHMENT_LOAD_OP_CLEAR���ұ���ӵ��potential format features����VK_FORMAT_FEATURE_FRAGMENT_SHADING_RATE_ATTACHMENT_BIT_KHR��image format
	15.���flags ���� VK_RENDER_PASS_CREATE_TRANSFORM_BIT_QCOM��pSubpasses��ĳ��subpass��pNext�к���VkFragmentShadingRateAttachmentInfoKHR���Ҹýṹ��� pFragmentShadingRateAttachment��ΪNULL,��ò�����Ӧ��attachment������VK_ATTACHMENT_UNUSED
	16.���һ��������Ƭ����ɫ���׶δ�������VK_QCOM_render_pass_shader_resolve��չ���������subpass�����κ�input attachments����subpass description�к���VK_SUBPASS_DESCRIPTION_FRAGMENT_REGION_BIT_QCOM�����input attachments�Ĳ���������rasterizationSamples
	17.���һ��������Ƭ����ɫ���׶δ�������VK_QCOM_render_pass_shader_resolve��չ���������subpass description�к���VK_SUBPASS_DESCRIPTION_FRAGMENT_REGION_BIT_QCOM����sampleShadingEnable����ΪVK_FALSE
	18.���flags����VK_SUBPASS_DESCRIPTION_SHADER_RESOLVE_BIT_QCOM����
											��1�����pResolveAttachments����NULL,��ÿ�� resolve attachment������VK_ATTACHMENT_UNUSED
											��2�����pDepthStencilResolveAttachment����NULL,��depth/stencil resolve attachment������VK_ATTACHMENT_UNUSED
											��3��subpass������subpass�������е����һ��subpass
	19.���pSubpasses��ĳ��subpass�� pDepthStencilAttachment��Ӧ��attachment��������VK_ATTACHMENT_UNUSED,��
											��1������� pDepthStencilAttachment��Ӧ�Ľṹ���е�layout��VK_IMAGE_LAYOUT_DEPTH_ATTACHMENT_OPTIMAL ���� VK_IMAGE_LAYOUT_DEPTH_READ_ONLY_OPTIMAL,���ڸýṹ���pNext��û��VkAttachmentReferenceStencilLayout���� attachment��Ӧ��pAttachments��format����ͬʱ������Ⱥ�ģ�������ɷ�
											��2������� pDepthStencilAttachment��Ӧ�Ľṹ���е�layout��VK_IMAGE_LAYOUT_STENCIL_ATTACHMENT_OPTIMAL ����VK_IMAGE_LAYOUT_STENCIL_READ_ONLY_OPTIMAL���� attachment��Ӧ��pAttachments��formatֻ�ܺ���ģ��ɷ�
											��3������� pDepthStencilAttachment��Ӧ�Ľṹ���е�layout��VK_IMAGE_LAYOUT_DEPTH_ATTACHMENT_OPTIMAL����VK_IMAGE_LAYOUT_DEPTH_READ_ONLY_OPTIMAL���� attachment��Ӧ��pAttachments��format����ֻ�ܺ���ģ��ɷ�
	20.���pSubpasses��ĳ��subpass���õ� pResolveAttachment��formatΪVK_FORMAT_UNDEFINED,��VkRenderPassFragmentDensityMapCreateInfoEXT::fragmentDensityMapAttachment->attachment ����ΪVK_ATTACHMENT_UNUSED
	21.��� attachmentCount��subpassCount��correlatedViewMaskCount�Լ�dependencyCount��Ϊ0�������Ӧ������ָ������Ǻ�����Ч���ݵ�����ָ��
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
	1.stencilInitialLayout��stencilFinalLayout����ΪVK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL,
									VK_IMAGE_LAYOUT_DEPTH_ATTACHMENT_OPTIMAL, VK_IMAGE_LAYOUT_DEPTH_READ_ONLY_OPTIMAL,
									VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL,
									VK_IMAGE_LAYOUT_DEPTH_STENCIL_READ_ONLY_OPTIMAL,
									VK_IMAGE_LAYOUT_DEPTH_ATTACHMENT_STENCIL_READ_ONLY_OPTIMAL, ����
									VK_IMAGE_LAYOUT_DEPTH_READ_ONLY_STENCIL_ATTACHMENT_OPTIMAL
	2.stencilFinalLayout����ΪVK_IMAGE_LAYOUT_UNDEFINED ����VK_IMAGE_LAYOUT_PREINITIALIZED

	*/
	attachmentDescription2.pNext = &stencilLayout;//pNext�п��԰���VkExternalFormatANDROID��VkAttachmentDescriptionStencilLayout
	/*
	��Ч�÷���
	1.���VkAttachmentDescription���÷�
	2.���separateDepthStencilLayouts���Կ�������format��һ��depth/stencil��format����initialLayout��finalLayout�ܹ�ֻ����depth��layoutҲ����depth/stencilһ�����ã�stencil��layout������pNext�е�VkAttachmentDescriptionStencilLayout
	�н���ָ��������еĻ��������formatֻ��stencil��format����initialLayout��finalLayoutֻ������Ϊstencil��layout������pNext�е�VkAttachmentDescriptionStencilLayout��ָ��������еĻ��������û������initialLayout��finalLayout��ָ��

	3. ���format����color�Լ�depth���ݣ���loadOpΪVK_ATTACHMENT_LOAD_OP_LOAD����initialLayout������VK_IMAGE_LAYOUT_UNDEFINED
	4. finalLayout ������ VK_IMAGE_LAYOUT_UNDEFINED ����VK_IMAGE_LAYOUT_PREINITIALIZED
	5. ���format��color��ʽ��initialLayout��finalLayout ������VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL ����VK_IMAGE_LAYOUT_DEPTH_STENCIL_READ_ONLY_OPTIMAL��
															 VK_IMAGE_LAYOUT_DEPTH_ATTACHMENT_STENCIL_READ_ONLY_OPTIMAL ����
															 VK_IMAGE_LAYOUT_DEPTH_READ_ONLY_STENCIL_ATTACHMENT_OPTIMAL��
															 VK_IMAGE_LAYOUT_DEPTH_ATTACHMENT_OPTIMAL, VK_IMAGE_LAYOUT_DEPTH_READ_ONLY_OPTIMAL,
															 VK_IMAGE_LAYOUT_STENCIL_ATTACHMENT_OPTIMAL, ����
															 VK_IMAGE_LAYOUT_STENCIL_READ_ONLY_OPTIMAL
	6. ���format��depth/stencil��ʽ��initialLayout��finalLayout������VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL
	7. ��� separateDepthStencilLayouts��depth��stencil�����Ƿ��ֿܷ�������û�п�������ô initialLayout�Լ�finalLayout������
																			VK_IMAGE_LAYOUT_DEPTH_ATTACHMENT_OPTIMAL, VK_IMAGE_LAYOUT_DEPTH_READ_ONLY_OPTIMAL,
																			VK_IMAGE_LAYOUT_STENCIL_ATTACHMENT_OPTIMAL,����
																			VK_IMAGE_LAYOUT_STENCIL_READ_ONLY_OPTIMAL,
	8. ���format��depth/stencil��ʽ���Һ���depth��stencil���ݻ���ֻ����depth���ݣ���initialLayout��finalLayout������VK_IMAGE_LAYOUT_STENCIL_ATTACHMENT_OPTIMAL ����
																								  VK_IMAGE_LAYOUT_STENCIL_READ_ONLY_OPTIMAL
	9. ���synchronization2����δ������initialLayout��finalLayout������VK_IMAGE_LAYOUT_ATTACHMENT_OPTIMAL_KHR ���� VK_IMAGE_LAYOUT_READ_ONLY_OPTIMAL_KHR
	10. ���attachmentFeedbackLoopLayout����δ������initialLayout��finalLayout������VK_IMAGE_LAYOUT_ATTACHMENT_FEEDBACK_LOOP_OPTIMAL_EXT
	11. samples�����Ǳ����image����ʱ��ĺϷ���samplesֵ
	12.���pNext�в���VkAttachmentDescriptionStencilLayout����format����stencil�Ĳ��֣���stencilLoadOp �� VK_ATTACHMENT_LOAD_OP_LOAD,�� initialLayout ����Ϊ VK_IMAGE_LAYOUT_UNDEFINED
	13.���pNext�к�VkAttachmentDescriptionStencilLayout����format����stencil�Ĳ��֣���stencilLoadOp �� VK_ATTACHMENT_LOAD_OP_LOAD,�� VkAttachmentDescriptionStencilLayout::stencilInitialLayout ������VK_IMAGE_LAYOUT_UNDEFINED
	14.���formatΪ depth/stencil ���京��depth��stencil���֣���initialLayout��finalLayout��initialLayout is VK_IMAGE_LAYOUT_DEPTH_ATTACHMENT_OPTIMAL ����VK_IMAGE_LAYOUT_DEPTH_READ_ONLY_OPTIMAL����pNext�б��뺬��VkAttachmentDescriptionStencilLayout
	15.���pNext�в���VkAttachmentDescriptionStencilLayout����formatֻ��stencil���֣���initialLayout��finalLayout������VK_IMAGE_LAYOUT_DEPTH_ATTACHMENT_OPTIMAL �� VK_IMAGE_LAYOUT_DEPTH_READ_ONLY_OPTIMAL
	16. ��� externalFormatResolve û�п���, format ����Ϊ VK_FORMAT_UNDEFINED
	17.���format �� VK_FORMAT_UNDEFINED, �ͱ�����pNext�а���һ��externalFormat��Ϊ0��VkExternalFormatANDROID


	*/

	renderPassCreateInfo2.pAttachments = &attachmentDescription2;



	//subpass ����2
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
	subpassDescription2.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;//ָ����subpass֧�ֵ�pipeline����
	SubpassDesctiption2Ext subpassDesctiption2Ext{};

	//ָ��subpass��depth��stencil��resolve��Ϣ
	VkSubpassDescriptionDepthStencilResolve& depthStencilResolve = subpassDesctiption2Ext.subpassDescriptionDepthStencilResolve;
	depthStencilResolve.depthResolveMode = VK_RESOLVE_MODE_NONE;//depth��resolveģʽ
	depthStencilResolve.stencilResolveMode = VK_RESOLVE_MODE_NONE;//stencil��resolveģʽ
	//depthStencilResolve.pNext = nullptr;//�Ѿ����ú��ˣ�����㲻��������
	depthStencilResolve.sType = VK_STRUCTURE_TYPE_SUBPASS_DESCRIPTION_DEPTH_STENCIL_RESOLVE;
	depthStencilResolve.pDepthStencilResolveAttachment = VK_NULL_HANDLE;//Ϊ�ջ�����Ч��VkAttachmentReference2ָ�룬����ֱ����Ϊ��
	/*
	VkSubpassDescriptionDepthStencilResolve�Ϸ��÷���
	1.���pDepthStencilResolveAttachment ����NULL �Ҳ�ΪVK_ATTACHMENT_UNUSED, ��
													��1��pDepthStencilAttachment ����Ϊ NULL����ΪVK_ATTACHMENT_UNUSED
													��2��pDepthStencilAttachment�Ĳ���������ΪVK_SAMPLE_COUNT_1_BIT
													��3��pDepthStencilResolveAttachment�Ĳ���������ΪVK_SAMPLE_COUNT_1_BIT
													��4����image format ��potential format features���뺬��VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT
													��5����� pDepthStencilResolveAttachment��format��depth �ɷ�, pDepthStencilAttachment��format��������ͬ���ָ�ʽ��depth�ɷ�
													��6����� pDepthStencilResolveAttachment��format��stencil �ɷ�, pDepthStencilAttachment��format��������ͬ���ָ�ʽ��stencil�ɷ�
													��7��depthResolveMode �� stencilResolveMode ����ͬʱVK_RESOLVE_MODE_NONE
													��8�����pDepthStencilResolveAttachment��format�� depth�ɷ�,��depthResolveMode ����ΪVkPhysicalDeviceDepthStencilResolveProperties::supportedDepthResolveModes�е�һλ����VK_RESOLVE_MODE_NONE
													��9�����pDepthStencilResolveAttachment��format�� stencil�ɷ�,�� stencilResolveMode ����ΪVkPhysicalDeviceDepthStencilResolveProperties::supportedStencilResolveModes�е�һλ����VK_RESOLVE_MODE_NONE
													(10) pDepthStencilResolveAttachment��foramt��depth��stencil�ɷ�, VkPhysicalDeviceDepthStencilResolveProperties::independentResolveΪVK_FALSE, �� VkPhysicalDeviceDepthStencilResolveProperties::independentResolveNone
																Ϊ VK_FALSE, ��depthResolveMode �� stencilResolveMode������ͬ
													(11)pDepthStencilResolveAttachment��foramt��depth��stencil�ɷ�, VkPhysicalDeviceDepthStencilResolveProperties::independentResolveΪVK_FALSE, �� VkPhysicalDeviceDepthStencilResolveProperties::independentResolveNone
																Ϊ VK_TRUE, ��depthResolveMode �� stencilResolveMode������ͬ��������һ������Ϊ VK_RESOLVE_MODE_NONE


	2.���VkSubpassDescription2��pNext �к���VkMultisampledRenderToSingleSampledInfoEXT �Ҹ����ݽṹ��multisampledRenderToSingleSampledEnableΪVK_TRUE, ��pDepthStencilAttachment����NULL�Ҳ���VK_ATTACHMENT_UNUSED����
													��1��depthResolveMode ��stencilResolveMode����ͬʱΪ VK_RESOLVE_MODE_NONE
													��2�����pDepthStencilAttachment��format��depth�ɷ�, ��depthResolveMode����ΪVkPhysicalDeviceDepthStencilResolveProperties::supportedDepthResolveModes ������һλ����VK_RESOLVE_MODE_NONE
													��3�����pDepthStencilAttachment��format��stencil�ɷ�, ��stencilResolveMode����ΪVkPhysicalDeviceDepthStencilResolveProperties::supportedStencilResolveModes ������һλ����VK_RESOLVE_MODE_NONE
													(10) pDepthStencilAttachment��foramt��depth��stencil�ɷ�, VkPhysicalDeviceDepthStencilResolveProperties::independentResolveΪVK_FALSE, �� VkPhysicalDeviceDepthStencilResolveProperties::independentResolveNone
																Ϊ VK_FALSE, ��depthResolveMode �� stencilResolveMode������ͬ
													(11)pDepthStencilAttachment��foramt��depth��stencil�ɷ�, VkPhysicalDeviceDepthStencilResolveProperties::independentResolveΪVK_FALSE, �� VkPhysicalDeviceDepthStencilResolveProperties::independentResolveNone
																Ϊ VK_TRUE, ��depthResolveMode �� stencilResolveMode������ͬ��������һ������Ϊ VK_RESOLVE_MODE_NONE

	3.����Ϸ����÷�pDepthStencilResolveAttachment���� NULL, ��pDepthStencilResolveAttachment����Ϊ�Ϸ���VkAttachmentReference2ָ��

	*/



	//fragment shading rate attachment����
	VkFragmentShadingRateAttachmentInfoKHR& fragmentShadingRateAttachmentInfoKHR = subpassDesctiption2Ext.fragmentShadingRateAttachmentInfoKHR;
	fragmentShadingRateAttachmentInfoKHR.sType = VK_STRUCTURE_TYPE_FRAGMENT_SHADING_RATE_ATTACHMENT_INFO_KHR;
	//fragmentShadingRateAttachmentInfoKHR.pNext = nullptr;//�Ѿ����ú��ˣ�����㲻��������
	fragmentShadingRateAttachmentInfoKHR.shadingRateAttachmentTexelSize = { 1,/*width*/   1/*height*/ };//ָ��ÿ��texel��Ӧ��framebuffer��Ӧλ�������С
	fragmentShadingRateAttachmentInfoKHR.pFragmentShadingRateAttachment = VK_NULL_HANDLE;//Ϊ��subpass����һ��fragment shading rate attachment
	/*
	VkFragmentShadingRateAttachmentInfoKHR�Ϸ��÷�:
	1.���pFragmentShadingRateAttachment ���� NULL�Ҷ�Ӧ�ĸ�������VK_ATTACHMENT_UNUSED,��
										��1����layout����Ϊ VK_IMAGE_LAYOUT_GENERAL����VK_IMAGE_LAYOUT_FRAGMENT_SHADING_RATE_ATTACHMENT_OPTIMAL_KHR
										��2�� minFragmentShadingRateAttachmentTexelSize.width <= shadingRateAttachmentTexelSize.width (����Ϊ2��ָ����) <= maxFragmentShadingRateAttachmentTexelSize.width
										��3��minFragmentShadingRateAttachmentTexelSize.height <= shadingRateAttachmentTexelSize.height (����Ϊ2��ָ����) <= maxFragmentShadingRateAttachmentTexelSize.height
										��4��(shadingRateAttachmentTexelSize.width / shadingRateAttachmentTexelSize.height) <=maxFragmentShadingRateAttachmentTexelSizeAspectRatio
										��5��(shadingRateAttachmentTexelSize.height / shadingRateAttachmentTexelSize.width) <=maxFragmentShadingRateAttachmentTexelSizeAspectRatio

	*/


	// VkMultisampledRenderToSingleSampledInfoEXT
	VkMultisampledRenderToSingleSampledInfoEXT& multisampledRenderToSingleSampledInfoEXT = subpassDesctiption2Ext.multisampledRenderToSingleSampledInfoEXT;
	multisampledRenderToSingleSampledInfoEXT.sType = VK_STRUCTURE_TYPE_MULTISAMPLED_RENDER_TO_SINGLE_SAMPLED_INFO_EXT;
	//multisampledRenderToSingleSampledInfoEXT.pNext = nullptr;//�Ѿ����ú��ˣ�����㲻��������
	multisampledRenderToSingleSampledInfoEXT.rasterizationSamples = VK_SAMPLE_COUNT_4_BIT;//�����Ƿ�ִ�жԵ����������Ķ������Ⱦ����ֵ����Ϊ VK_SAMPLE_COUNT_1_BIT
	multisampledRenderToSingleSampledInfoEXT.multisampledRenderToSingleSampledEnable = VK_FALSE;//ָ����դ���Ĳ�����
	/*
	1.����ýṹ��ӵ�VkRenderingInfo��pNext��, �κ�VkRenderingInfo::pColorAttachments, VkRenderingInfo::pDepthAttachment, ����VkRenderingInfo::pStencilAttachment�Ĳ���VK_NULL_HANDLE��imageView ��������֧��rasterizationSamples
	2.����ýṹ��ӵ�VkRenderingInfo����VkSubpassDescription2��pNext�У���multisampledRenderToSingleSampledEnableΪVK_TRUE,��subpass��Ӧ��pipeline���ߴ���ʱ��VkGraphicsPipelineCreateInfo::rasterizationSamples�������VkMultisampledRenderToSingleSampledInfoEXT::rasterizationSamples��������subpass�ĸ����Ĳ������Ϳ���Ϊ VK_SAMPLE_COUNT_1_BIT��
	����������Щ������Ϊ1�ĸ������Ϳ���ִ�ж������Ⱦ��������ʱ��image�����ж��ز�����ͨ�����ƽ��г�ʼ�����洢ǰ���resolve����
	*/



	subpassDescription2.pNext = &subpassDesctiption2Ext.fragmentShadingRateAttachmentInfoKHR;

	/*
	��Ч�÷���
	1.���VkSubpassDescription���÷�
	2.viewMask�ȼ��� VkRenderPassMultiviewCreateInfo::pViewMasks��Ӧ��subpass��ֵ
	3.���pNext�к���VkFragmentShadingRateAttachmentInfoKHR������pFragmentShadingRateAttachment ���� NULL, attachment��Ӧ�������� VK_ATTACHMENT_UNUSED,���subpass����һ��fragment shading rate attachment
	4.��� pResolveAttachments�κ�Ԫ�صĸ����� VkExternalFormatANDROID��ָ�������Ӧ��color�������� VK_RESOLVE_MODE_EXTERNAL_FORMAT_DOWNSAMPLE_ANDROID.����resolve������
	5.��� nullColorAttachmentWithExternalFormatResolve ������ VK_TRUE����color�����е�ֵ������Ⱦ��ʼǰ��resolve�����м��أ�������Ƶ����ò��Ǻ������


	6. ���pInputAttachments��attachment���� VK_ATTACHMENT_UNUSED����layout������VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL ���� VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL��
																															   VK_IMAGE_LAYOUT_DEPTH_ATTACHMENT_OPTIMAL
																															   ����VK_IMAGE_LAYOUT_STENCIL_ATTACHMENT_OPTIMAL��
																															   VK_IMAGE_LAYOUT_ATTACHMENT_OPTIMAL_KHR


	7. ��� pColorAttachments����pResolveAttachments��attachment���� VK_ATTACHMENT_UNUSED����layout������ VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL ����VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL��
																										  VK_IMAGE_LAYOUT_DEPTH_ATTACHMENT_STENCIL_READ_ONLY_OPTIMAL ����
																										  VK_IMAGE_LAYOUT_DEPTH_READ_ONLY_STENCIL_ATTACHMENT_OPTIMAL��
																										  VK_IMAGE_LAYOUT_DEPTH_ATTACHMENT_OPTIMAL,VK_IMAGE_LAYOUT_DEPTH_READ_ONLY_OPTIMAL,
																										  VK_IMAGE_LAYOUT_STENCIL_ATTACHMENT_OPTIMAL, ���� VK_IMAGE_LAYOUT_STENCIL_READ_ONLY_OPTIMAL��
																										  VK_IMAGE_LAYOUT_READ_ONLY_OPTIMAL_KHR

	8. ��� pDepthStencilAttachment��attachment���� VK_ATTACHMENT_UNUSED����layout������VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL ����VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL
	9.��� pDepthStencilAttachment��attachment���� VK_ATTACHMENT_UNUSED����pNext�к���VkAttachmentReferenceStencilLayout����ø�����layout������VK_IMAGE_LAYOUT_STENCIL_ATTACHMENT_OPTIMAL ����VK_IMAGE_LAYOUT_STENCIL_READ_ONLY_OPTIMAL


	10. pipelineBindPoint������VK_PIPELINE_BIND_POINT_GRAPHICS ����VK_PIPELINE_BIND_POINT_SUBPASS_SHADING_HUAWEI
	11. colorAttachmentCount����С�ڵ���VkPhysicalDeviceLimits::maxColorAttachments
	12. ���һ��attachment��render pass�еĵ�һ��ʹ����Ϊinput attachment�������ڸ�subpass�в�����Ϊcolor ���� depth/stencil�����������loadOp������ VK_ATTACHMENT_LOAD_OP_CLEAR
	13. ���pResolveAttachments����NULL,�����е�Ԫ�ض�Ӧ��resolve attachmentҲ����VK_ATTACHMENT_UNUSED,�����е�Ԫ�ض�Ӧ��resolve attachment�Ĳ�����������VK_SAMPLE_COUNT_1_BIT
	14.��� externalFormatResolve û������pResolveAttachments ���� NULL, ÿ������VK_ATTACHMENT_UNUSED��resolve attachment,��Ӧ��color attachment ������ VK_ATTACHMENT_UNUSED
	15.���nullColorAttachmentWithExternalFormatResolve �� VK_FALSE ��pResolveAttachments ����NULL, ÿ��VK_FORMAT_UNDEFINED��resolve attachment ��Ӧ�� color attachment ������VK_ATTACHMENT_UNUSED
	16.���nullColorAttachmentWithExternalFormatResolve ��VK_TRUE ��pResolveAttachments���� NULL, ÿ��VK_FORMAT_UNDEFINED��resolve attachment ��Ӧ�� color attachment ������VK_ATTACHMENT_UNUSED
VK_ATTACHMENT_UNUSED

	17.��� externalFormatResolve û������ pResolveAttachments ���� NULL, ÿ������VK_ATTACHMENT_UNUSED��resolve attachment��Ӧ��color attachment�Ĳ���������Ϊ VK_SAMPLE_COUNT_1_BIT
	18.���externalFormatResolve û�п����� ÿ��pResolveAttachments��format��������Ӧ��color attachment��format��ͬ
	19.���multisampledRenderToSingleSampled ����δ����, ����pColorAttachments �в��� VK_ATTACHMENT_UNUSED ����Ϊ��ͬ�Ĳ�����

	20.  pInputAttachments�в���VK_ATTACHMENT_UNUSED��attachment���� externalFormatResolve ����û�п�����nullColorAttachmentWithExternalFormatResolve Ϊ VK_FALSE
			VkExternalFormatANDROID::externalFormat�����з���ֵ��������һ�����������£����뺬��ӵ��potential format features ����p4100������ΪVK_FORMAT_FEATURE_COLOR_ATTACHMENT_BIT ����VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT�� image format
	21. pColorAttachments����pResolveAttachments�в���VK_ATTACHMENT_UNUSED��attachment���뺬��ӵ��potential format features ����p4100��Ϊ VK_FORMAT_FEATURE_COLOR_ATTACHMENT_BIT�� image format
	22. pDepthStencilAttachment ���� NULL �� ��attachment ���� VK_ATTACHMENT_UNUSED�� ��attachment���뺬��ӵ��potential format features ����p4100��Ϊ VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT�� image format

	23. ��� linearColorAttachment���Կ�����image����ΪVK_IMAGE_TILING_LINEAR,��
											��1��pInputAttachments�в���VK_ATTACHMENT_UNUSED��attachment���뺬��ӵ��potential format features ����p4100��ΪVK_FORMAT_FEATURE_2_LINEAR_COLOR_ATTACHMENT_BIT_NV�� image format
											��2��pColorAttachments����pResolveAttachments�в���VK_ATTACHMENT_UNUSED��attachment���뺬��ӵ��potential format features ����p4100��Ϊ  VK_FORMAT_FEATURE_2_LINEAR_COLOR_ATTACHMENT_BIT_NV�� image format
	24. ��� VK_AMD_mixed_attachment_samples���� VK_NV_framebuffer_mixed_samples���Կ�������pColorAttachments�в���VK_ATTACHMENT_UNUSED��attachment�Ĳ���������С��pDepthStencilAttachment�������ΪVK_ATTACHMENT_UNUSED����attachment�Ĳ�����
	25.���pNext�к���multisampledRenderToSingleSampledEnableΪVK_TRUE��VkMultisampledRenderToSingleSampledInfoEXT����
											��1�� ���� pColorAttachments �� pDepthStencilAttachment ����VK_ATTACHMENT_UNUSED �Ĳ���������Ϊ VK_SAMPLE_COUNT_1_BIT ���ߵ���VkMultisampledRenderToSingleSampledInfoEXT::rasterizationSamples
											��2�����pDepthStencilAttachment���� NULL, �Ҳ��� VK_ATTACHMENT_UNUSED, �Ҳ�����ΪVK_SAMPLE_COUNT_1_BIT, �� pNext ��Ҳ�������pDepthStencilResolveAttachmentΪ NULL ���� VK_ATTACHMENT_UNUSED��VkSubpassDescriptionDepthStencilResolve

	26. ��� VK_AMD_mixed_attachment_samples��չ���� VK_NV_framebuffer_mixed_samples��չ�Լ� multisampledRenderToSingleSampled��û�п��������pDepthStencilAttachment ���� pColorAttachments����VK_ATTACHMENT_UNUSED��attachment�Ĳ�����������ͬ��


	27.  pPreserveAttachments�е�ÿ��Ԫ�ز�����VK_ATTACHMENT_UNUSED���Ҳ�����subpass description�е���������
	28. ���һ������attachment����� VkAttachmentReference2���ã���ô��Щ���ñ�������ͬ��layout
	29. ���flags���� VK_SUBPASS_DESCRIPTION_PER_VIEW_POSITION_X_ONLY_BIT_NVX�����仹�������VK_SUBPASS_DESCRIPTION_PER_VIEW_ATTRIBUTES_BIT_NVX
	30.���pInputAttachments�еĸ�������VK_ATTACHMENT_UNUSED,��
															��1��aspectMask �����ǺϷ��� VkImageAspectFlagBits���
															��2�� aspectMask ����Ϊ 0
															��3��aspectMask ���ܰ��� VK_IMAGE_ASPECT_METADATA_BIT
															��4��aspectMask ���ܺ� VK_IMAGE_ASPECT_MEMORY_PLANE_i_BIT_EXT����index i


	31. pDepthStencilAttachment �� pColorAttachments����ͬʱָ��ͬһ��attachment
	32.viewMaskֵ�������Чλ�� ����С��maxMultiviewViewCount�����multiview ����û�п���, ��viewMask ����Ϊ 0
	33.���externalFormatResolve ������ pResolveAttachments����NULL, ��
															��1�����colorAttachmentCount ���� 1,pResolveAttachments�в���VK_ATTACHMENT_UNUSED��format����Ϊ VK_FORMAT_UNDEFINED
															��2���κ�pResolveAttachments �в��� VK_ATTACHMENT_UNUSED ��formatȴ�� VK_FORMAT_UNDEFINED,�����Ӧ��pColorAttachments��color�������� VK_ATTACHMENT_UNUSED, ���color�����Ĳ���������Ϊ1
															��3���κ�pResolveAttachments �в��� VK_ATTACHMENT_UNUSED ��formatȴ�� VK_FORMAT_UNDEFINED��viewMask����Ϊ0
															��4���κ�pResolveAttachments �в��� VK_ATTACHMENT_UNUSED ��formatȴ�� VK_FORMAT_UNDEFINED��VkFragmentShadingRateAttachmentInfoKHR::pFragmentShadingRateAttachment ������NULL ���߶�Ӧ��һ��VK_ATTACHMENT_UNUSED������ VkAttachmentReference2
															��5���κ�pResolveAttachments �в��� VK_ATTACHMENT_UNUSED ��formatȴ�� VK_FORMAT_UNDEFINED���ڸ�subpass����pInputAttachments ���õ� color attachment ���� resolve attachment ���ܰ��� VK_IMAGE_ASPECT_PLANE_i_BIT ���κ�aspectMask��index i

	34.����Ϸ����÷���pColorAttachments��colorAttachmentCount���Ϸ���ɫ�������õ������׵�ַָ��ȵ�






	*/



	VkAttachmentReference2 colorAttachmentRef2{};
	colorAttachmentRef2.sType = VK_STRUCTURE_TYPE_ATTACHMENT_REFERENCE_2;
	colorAttachmentRef2.attachment = 0;// ��VkRenderPassCreateInfo2::pAttachments������, ���� VK_ATTACHMENT_UNUSED �����ø���û��ʹ��
	colorAttachmentRef2.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
	colorAttachmentRef2.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

	VkAttachmentReferenceStencilLayout referenceStencilLayout;
	referenceStencilLayout.sType = VK_STRUCTURE_TYPE_ATTACHMENT_REFERENCE_STENCIL_LAYOUT;
	referenceStencilLayout.pNext = nullptr;
	referenceStencilLayout.stencilLayout = VK_IMAGE_LAYOUT_UNDEFINED;/*
	1.stencilLayout ����Ϊ VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_PREINITIALIZED,
							VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL, VK_IMAGE_LAYOUT_DEPTH_ATTACHMENT_OPTIMAL,
							VK_IMAGE_LAYOUT_DEPTH_READ_ONLY_OPTIMAL,
							VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL,
							VK_IMAGE_LAYOUT_DEPTH_STENCIL_READ_ONLY_OPTIMAL,
							VK_IMAGE_LAYOUT_DEPTH_ATTACHMENT_STENCIL_READ_ONLY_OPTIMAL,
							VK_IMAGE_LAYOUT_DEPTH_READ_ONLY_STENCIL_ATTACHMENT_OPTIMAL, ����
							VK_IMAGE_LAYOUT_PRESENT_SRC_KHR
	
	*/



	colorAttachmentRef2.pNext = &stencilLayout;//���Ժ���VkAttachmentReferenceStencilLayout
	/*
	VkAttachmentReference2��Ч�÷�
	1.���attachment ����VK_ATTACHMENT_UNUSED, layout������VK_IMAGE_LAYOUT_UNDEFINED,VK_IMAGE_LAYOUT_PREINITIALIZED, ���� VK_IMAGE_LAYOUT_PRESENT_SRC_KHR
	2.���separateDepthStencilLayouts ����û�п���, �� attachment ����VK_ATTACHMENT_UNUSED, layout ������ VK_IMAGE_LAYOUT_DEPTH_ATTACHMENT_OPTIMAL,
						VK_IMAGE_LAYOUT_DEPTH_READ_ONLY_OPTIMAL, VK_IMAGE_LAYOUT_STENCIL_ATTACHMENT_OPTIMAL, ����VK_IMAGE_LAYOUT_STENCIL_READ_ONLY_OPTIMAL,
	3.���synchronization2 ����û�п���, layout ����ΪVK_IMAGE_LAYOUT_ATTACHMENT_OPTIMAL_KHR ���� VK_IMAGE_LAYOUT_READ_ONLY_OPTIMAL_KHR
	4.���attachmentFeedbackLoopLayout ����û�п���, layout ����ΪVK_IMAGE_LAYOUT_ATTACHMENT_FEEDBACK_LOOP_OPTIMAL_EXT
	5.���dynamicRenderingLocalRead ����û�п���, layout ����ΪVK_IMAGE_LAYOUT_RENDERING_LOCAL_READ_KHR
	

	*/




	//subpass dependence 2
	VkSubpassDependency2 subpassDependency2{};
	subpassDependency2.sType = VK_STRUCTURE_TYPE_SUBPASS_DEPENDENCY_2;
	subpassDependency2.pNext = nullptr;//���Ժ��� VkMemoryBarrier2
	subpassDependency2.srcSubpass = VK_SUBPASS_EXTERNAL;
	subpassDependency2.srcAccessMask = VK_ACCESS_NONE;
	subpassDependency2.srcStageMask = VK_PIPELINE_STAGE_NONE;
	subpassDependency2.dstSubpass = 0;
	subpassDependency2.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
	subpassDependency2.dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
	subpassDependency2.dependencyFlags = 0;
	subpassDependency2.viewOffset = 0;
	/*
	VkSubpassDependency2�Ϸ��÷���
	1.�÷����VkSubpassDependency���÷�
	2.viewOffset ��Ч��VkRenderPassMultiviewCreateInfo::pViewOffsets �ж�Ӧsubpass dependency��ֵ
	3.��� VkMemoryBarrier2������pNext�У���srcStageMask, dstStageMask, srcAccessMask,�Լ�dstAccessMask��������
	4.��ɫ�����Ժ͹��߽׶εĺϷ���Ӧ�����ĳЩ��ɫ������û�п����Ͳ��ܰ�����֮��Ӧ�Ĺ��߽׶Σ�����ͬ���½�
	5.���synchronization2 ����û�п���, srcStageMask����Ϊ0
	6.���VK_NV_ray_tracing ��չ���� rayTracingPipeline ��������֮һ����,srcStageMask ���ܰ���VK_PIPELINE_STAGE_RAY_TRACING_SHADER_BIT_KHR
	7.��� fragmentDensityMap ����û�п���, dstStageMask���ܰ���VK_PIPELINE_STAGE_FRAGMENT_DENSITY_PROCESS_BIT_EXT
	8.��� transformFeedback ����û�п���, dstStageMask���ܰ���VK_PIPELINE_STAGE_TRANSFORM_FEEDBACK_BIT_EXT
	9.��� shadingRateImage��û�п��� attachmentFragmentShadingRate ����Ҳû�п���, dstStageMask���ܰ���VK_PIPELINE_STAGE_FRAGMENT_SHADING_RATE_ATTACHMENT_BIT_KHR
	10.���  synchronization2 ����û�п���, dstStageMask����Ϊ0
	11.���VK_NV_ray_tracing ��չ��û�п���rayTracingPipeline ����Ҳû�п���,dstStageMask ���ܰ��� VK_PIPELINE_STAGE_RAY_TRACING_SHADER_BIT_KHR
	12.srcSubpass ����С�ڵ��� dstSubpass, ��������֮һΪVK_SUBPASS_EXTERNAL��������ͬʱΪVK_SUBPASS_EXTERNAL,Ϊ�˱�֤������ѭ����������ȷ��ִ��˳��
	13.���srcSubpass����dstSubpass��srcStageMask ����framebuffer-space stage,��dstStageMask ֻ�ܰ��� framebuffer-space stages
	14. srcAccessMask�� srcStageMask��dstAccessMask�� dstStageMask�����ǺϷ��Ķ�Ӧ��ϵ����ͬ���½�
	15.��� dependencyFlags ���� VK_DEPENDENCY_VIEW_LOCAL_BIT, srcSubpass��dstSubpass ���ܵ���VK_SUBPASS_EXTERNAL
	16.���srcSubpass����dstSubpass��srcStageMask��dstStageMask ����framebuffer-space stage,�� dependencyFlags�������  VK_DEPENDENCY_BY_REGION_BIT
	17.���viewOffset ��Ϊ 0, srcSubpass ���ܵ���dstSubpass
	18.��� dependencyFlags������ VK_DEPENDENCY_VIEW_LOCAL_BIT, viewOffset ����Ϊ 0
	*/

	vkCreateRenderPass2(device, &renderPassCreateInfo2, nullptr, &renderPass);

	vkDestroyRenderPass(device, renderPass, nullptr);



}



//render pass����
/*
	1.�������ü��ݣ�format �� sample count��ͬ, ���߶��� VK_ATTACHMENT_UNUSED ���߸�������ָ��Ϊ NULL.
	2.��������������ݣ������������飬���Ӧ�ĸ���һһ��Ӧ���ݣ����������ٵ�������û�б�ʾ�����ĸ�����������VK_ATTACHMENT_UNUSED
	3.render pass���ݣ�����render pass��Ӧ��color, input, resolve, �Լ� depth/stencil���������Ǽ��ݵ��Լ��Ƿ���Щ�Ǹ������˳�ʼ�ͽ�����image layout �� Load �� store �������������õ� Image layout ��ȫ����ͬ�ġ�
	4.frame buffer���ݣ�����frame��ͬһ��render pass�������߼��ݵ�render pass����




*/



void RenderPassTest::FrameBufferCreateTest()
{
	//����frame buffer
	VkFramebuffer frameBuffer;
	VkFramebufferCreateInfo frameBufferCreateInfo{};
	frameBufferCreateInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
	frameBufferCreateInfo.renderPass = renderPass;
	frameBufferCreateInfo.flags = VK_FRAMEBUFFER_CREATE_IMAGELESS_BIT;//	��������� VK_FRAMEBUFFER_CREATE_IMAGELESS_BIT,��attachmentCount ���� 0, ��pCreateInfo->pAttachments��ÿһ��������device�ϴ���
	//VK_FRAMEBUFFER_CREATE_IMAGELESS_BITָ������pAttachments��ָ��ͼ����ͼ����ͨ��VkFramebufferAttachmentImageInfo�ṹ�ṩ������ͼ��������Ϣ
	frameBufferCreateInfo.attachmentCount = 0;
	frameBufferCreateInfo.pAttachments = VK_NULL_HANDLE;//imageView�ľ�������׵�ַ
	frameBufferCreateInfo.width = 16;
	frameBufferCreateInfo.height = 16;
	frameBufferCreateInfo.layers = 1;//���render pass��multiview����layers������һ������subpass��������viewMask������λ������һ����
	VkFramebufferAttachmentsCreateInfo frameBufferAttachmentsCreateInfo{};
	frameBufferAttachmentsCreateInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_ATTACHMENTS_CREATE_INFO;
	frameBufferAttachmentsCreateInfo.pNext = nullptr;
	frameBufferAttachmentsCreateInfo.attachmentImageInfoCount = 1;
	VkFramebufferAttachmentImageInfo attachmentImageInfo{};
	attachmentImageInfo.flags = 0;//�뼴�����ڱ�framebuffer��image��flagsƥ��
	attachmentImageInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_ATTACHMENT_IMAGE_INFO;
	attachmentImageInfo.pNext = nullptr;
	attachmentImageInfo.usage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;//�뼴�����ڱ�framebuffer��image��usageƥ��
	attachmentImageInfo.width = 16;//��Ⱦʱ��image view��width
	attachmentImageInfo.height = 16;//��Ⱦʱ��image view��height
	attachmentImageInfo.layerCount = 1;//��Ⱦʱ��image view��layers
	attachmentImageInfo.viewFormatCount = 0;//��pViewFomats�����е�Ԫ�ظ����������ڴ�����˿�ܻ�����һ��ʹ�õ�ͼ���VkImageFormatListCreateInfo����viewFormatCount��ֵ��ƥ��
	attachmentImageInfo.pViewFormats = VK_NULL_HANDLE;//��һ��ָ��VkFormatֵ�����ָ�룬ָ���ڴ���ͼ����ͼʱ����ʹ�õ����и�ʽ�������ڴ�����˿�ܻ�����һ��ʹ�õ�ͼ���VkImageFormatListCreateInfo����pViewFormats��ֵ��ƥ��


	frameBufferAttachmentsCreateInfo.pAttachmentImageInfos = &attachmentImageInfo;//����ÿ��attachment��image��Ϣ
	frameBufferCreateInfo.pNext = nullptr;//���Ժ���VkFramebufferAttachmentsCreateInfo

	/*
	�Ϸ��÷���
	1.�󶨵�subpass�Ĺ���pipeline��״̬��ϢVkPipelineMultisampleStateCreateInfo��rasterizationSamples������ͬ����� VkPhysicalDeviceFeatures::variableMultisampleRateλVK_FALSE,�ұ��뱻VkPhysicalDeviceLimits::framebufferNoAttachmentsSampleCounts.֧�� 
	2.attachmentCount�������renderPass��ָ����attachment count
	3.���flags������VK_FRAMEBUFFER_CREATE_IMAGELESS_BIT����
														��1�� �� attachmentCount��Ϊ0, pAttachments ��Ҫ��һ��attachmentCount����Ч��VkImageView�����׵�ַָ��
														��2��pAttachments���κα�renderPass����color attachment ���� resolve attachment ����ʱ���뺬��VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT
														��3��pAttachments���κα�renderPass���� depth/stencil attachment���� depth/stencil resolve attachment ����ʱ���뺬�� VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT
														��4�����renderpass��Ϊ VK_NULL_HANDLE��pAttachments���κα�renderPass���� input attachment����ʱ���뺬�� VK_IMAGE_USAGE_INPUT_ATTACHMENT_BIT
														��5��pAttachments���κ�Ԫ�ش���ʱ��format������renderPass�ж�Ӧ��VkAttachmentDescriptionָ����formatƥ��
														��6��pAttachments���κ�Ԫ�ش���ʱ��samples������renderPass�ж�Ӧ��VkAttachmentDescriptionָ����samplesƥ��
														��7��pAttachments���κα�renderPass����  input, color, resolve, ���� depth/stencil attachment ����ʱ������  VkImageCreateInfo::extent.width���ڵ���width,
																VkImageCreateInfo::extent.height���ڵ���height,VkImageCreateInfo::subresourceRange.layerCount���ڵ���layers
														��8��pAttachments���κ� fragmentDensityMapAttachment���õ�Ԫ�ص�width�������ٴ���(VkFramebufferCreateInfo.width / maxFragmentDensityTexelSize.width),
																height�������ٴ���(VkFramebufferCreateInfo.height / maxFragmentDensityTexelSize.height)
														��9)��� renderPass �з���� view masks,pAttachmentsÿһ����renderPass����fragment shading rate attachment��layerCount Ϊ 1,���ߴ���view masks��������Чλ�����������ߴ���layers
														��10��pAttachmentsÿһ����renderPass����fragment shading rate attachment��with����Ϊ ��VkFramebufferCreateInfo.width / texelWidth��,texelWidth�� VkFragmentShadingRateAttachmentInfoKHR��
																shadingRateAttachmentTexelSize.width�����ֵ��height����Ϊ (VkFramebufferCreateInfo.height / texelHeight��,texelHeight�� VkFragmentShadingRateAttachmentInfoKHR��
																shadingRateAttachmentTexelSize.height�����ֵ
														��11��pAttachments���κ�Ԫ��ֻ����ָ��һ��mipmap���Ҵ�������Ϊidentity swizzle
														��12��pAttachments���κ�Ԫ����3D image��2D ����2D array image view�Ĳ��ܺ���depth/stencil format
														��13��pAttachments���κ�Ԫ�ش���ʱ VkImageViewCreateInfo::viewType����ΪVK_IMAGE_VIEW_TYPE_3D
														��14��pAttachmentsÿһ����renderPass����fragment shading rate attachment����ʱ���뺬��VK_IMAGE_USAGE_FRAGMENT_SHADING_RATE_ATTACHMENT_BIT_KHR
														��15�����nullColorAttachmentWithExternalFormatResolve Ϊ VK_FALSE��renderPass�е�subpass�е�color�����а���һ���ⲿ��format��Ϊresolve format��resolve����,�ø�����resolve format�������
																		ͨ��vkGetAndroidHardwareBufferPropertiesANDROID���ص�VkAndroidHardwareBufferFormatResolvePropertiesANDROID::colorAttachmentFormat
														��16��pAttachments���κ�Ԫ�ص�formatΪVK_FORMAT_UNDEFINED,���䴴��ʱ��VkExternalFormatANDROID::externalFormat�������Ӧ��renderPass�е�VkAttachmentDescription2�ṩ�ĵ�VkExternalFormatANDROID::externalFormat���
	4.pAttachments���κα�renderPass����fragment density map attachment ����ʱ���ܺ��� VK_IMAGE_CREATE_SUBSAMPLED_BIT_EXT
	5.��� renderPass �� fragment density map attachment ��fragmentDensityMapNonSubsampledImages ����û�п���, pAttachments���κθ�������ʱ���뺬�� VK_IMAGE_CREATE_SUBSAMPLED_BIT_EXT�����Ǹø�����renderPass����fragment density map attachment 
	6.���renderPass����ʱ fragment density map offsets��Ϊ(0,0), pAttachments��ÿ��Ԫ�ش���ʱflags���뺬��VK_IMAGE_CREATE_FRAGMENT_DENSITY_MAP_OFFSET_BIT_QCOM
	7.���renderPass��view masks�Ƿ���ֵ, pAttachments���κα�renderPass����  input, color, resolve, ���� depth/stencil attachment��layerCount�������view masks��������Чλ������
	8.ÿһ����fragmentDensityMapAttachment���õ�pAttachments��Ԫ�ص�layerCount����Ϊ1���߱������renderPass��view masks��������Чλ���������renderPass�з���� view masks
	9.���renderPass��view masks�Ƿ���ֵ,pAttachmentsÿһ����renderPass����fragment shading rate attachment��layerCount Ϊ 1,���ߴ���view masks��������Чλ������
	10.0 <= with <=  maxFramebufferWidth, 0 <= height <= maxFramebufferHeight�� 0 <= layers <= maxFramebufferLayers
	11.���renderPass��view masks�Ƿ���ֵ��layers����Ϊ1
	12.���imagelessFramebuffer����û�п���, flags���ܰ���VK_FRAMEBUFFER_CREATE_IMAGELESS_BIT
	13.���flags����VK_FRAMEBUFFER_CREATE_IMAGELESS_BIT����
														��1�� pNext �б��뺬��һ��VkFramebufferAttachmentsCreateInfo
														��2�� pNext ��VkFramebufferAttachmentsCreateInfo��attachmentImageInfoCount����Ϊ0����attachmentCount
														��3�� pNext ��VkFramebufferAttachmentsCreateInfo��pAttachmentImageInfos����renderPass������input, color, resolve ���� depth/stencil attachment in renderPass��width ������ڵ���VkFramebufferCreateInfo.width
														��4�� pNext ��VkFramebufferAttachmentsCreateInfo��pAttachmentImageInfos����renderPass������input, color, resolve ���� depth/stencil attachment in renderPass��height ������ڵ���VkFramebufferCreateInfo.height
														��5��pNext ��VkFramebufferAttachmentsCreateInfo��pAttachmentImageInfos��renderPass�б�VkRenderPassFragmentDensityMapCreateInfoEXT::fragmentDensityMapAttachment���õ�width������ڵ���(VkFramebufferCreateInfo.width / maxFragmentDensityTexelSize.width)��
																		height������ڵ���(VkFramebufferCreateInfo.height / maxFragmentDensityTexelSize.height)

														��6��pNext ��VkFramebufferAttachmentsCreateInfo��pAttachmentImageInfos��renderPass�б�����fragment shading rate attachment��with����Ϊ ��VkFramebufferCreateInfo.width / texelWidth��,texelWidth�� VkFragmentShadingRateAttachmentInfoKHR��
																shadingRateAttachmentTexelSize.width�����ֵ��height����Ϊ (VkFramebufferCreateInfo.height / texelHeight��,texelHeight�� VkFragmentShadingRateAttachmentInfoKHR��
																shadingRateAttachmentTexelSize.height�����ֵ��layerCount����Ϊ1���ߴ��ڵ���VkFramebufferCreateInfo.layers
														��7��renderPass��view masks�Ƿ���ֵ,pAttachmentsÿһ����renderPass����fragment shading rate attachment��layerCount Ϊ 1
														��8����� multiview ��������pNext ��VkFramebufferAttachmentsCreateInfo��pAttachmentImageInfos���κα�renderPass����  input, color, resolve, ���� depth/stencil attachment ��layerCount ������ڵ���renderPass ��view masks��������Чλ������
														��9����� multiview û�п�������pNext ��VkFramebufferAttachmentsCreateInfo��pAttachmentImageInfos���κα�renderPass����  input, color, resolve, ���� depth/stencil attachment ��layerCount ������ڵ���VkFramebufferCreateInfo.layers
														��10����pNext ��VkFramebufferAttachmentsCreateInfo��pAttachmentImageInfos���κα�renderPass����color attachment ���� resolve attachment ����ʱ���뺬��VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT
														��11����pNext ��VkFramebufferAttachmentsCreateInfo��pAttachmentImageInfos���κα�renderPass����depth/stencil attachment ����depth/stencil resolve attachment ����ʱ���뺬�� VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT
														��12����pNext ��VkFramebufferAttachmentsCreateInfo��pAttachmentImageInfos���κα�renderPass����input attachment  ����ʱ���뺬�� VK_IMAGE_USAGE_INPUT_ATTACHMENT_BIT
														��13��pNext ��VkFramebufferAttachmentsCreateInfo��pAttachmentImageInfos��pViewFormats������һ��Ԫ�غ�renderPass�ж�Ӧ��VkAttachmentDescription��formatƥ��
														��14����pNext ��VkFramebufferAttachmentsCreateInfo��pAttachmentImageInfos���κα�renderPass����fragment shading rate attachment  ����ʱ���뺬�� VK_IMAGE_USAGE_FRAGMENT_SHADING_RATE_ATTACHMENT_BIT_KHR

	14.���multisampled-render-to-single-sampled���κ�subpass����, subpass�����е� color,depth/stencil �Լ� input attachments��VkAttachmentDescription::samples ���� VkAttachmentDescription2::samples ����VK_SAMPLE_COUNT_1_BIT ��image����ʱ����
														��1��VkImageCreateInfo::flags���뺬��VK_IMAGE_CREATE_MULTISAMPLED_RENDER_TO_SINGLE_SAMPLED_BIT_EXT
														��2����format����֧����VkMultisampledRenderToSingleSampledInfoEXT::rasterizationSamplesָ����sample count
	15.���nullColorAttachmentWithExternalFormatResolveΪ VK_FALSE, �� flags does not
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




//color�����Ķ�ȡ��д����VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT�׶Σ�depth/stencil�����Ķ�ȡ��д����VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT�׶Σ���������VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT�׶�
/*
��ȡ��
VK_ATTACHMENT_LOAD_OP_LOAD����ʾ����ԭ�������ݽ���ԭ����ֵ����
VK_ATTACHMENT_LOAD_OP_CLEAR����ʾ�����е����ݽ���render pass��Ⱦ��ʼǰ�����
VK_ATTACHMENT_LOAD_OP_DONT_CARE����ʾ������ԭ�����ݽ������ԣ���ֵ����δ�����
VK_ATTACHMENT_LOAD_OP_NONE_KHR����ʾ������ԭ�����ݽ���δ����ģ������ᱻ����

д����
VK_ATTACHMENT_STORE_OP_STORE����ʾ��render pass�ڼ����ɵ�ֵ�������浽������
VK_ATTACHMENT_STORE_OP_DONT_CARE����ʾ��render pass�ڼ����ɵ�ֵ�������ԣ�������Ҫ����ֵ����δ�����
VK_ATTACHMENT_STORE_OP_NONE����ʾ��render pass�ڼ����ɵ�ֵ���ᱻд�뵽������


��������
VK_RESOLVE_MODE_NONE��û�г�����
VK_RESOLVE_MODE_SAMPLE_ZERO_BIT��������������ֵ��������Ϊsample 0��ֵ
VK_RESOLVE_MODE_AVERAGE_BIT��������������ֵ��������Ϊ����sample��ƽ��ֵ
VK_RESOLVE_MODE_MIN_BIT��������������ֵ��������Ϊ����sample����Сֵ
VK_RESOLVE_MODE_MAX_BIT��������������ֵ��������Ϊ����sample�����ֵ
VK_RESOLVE_MODE_EXTERNAL_FORMAT_DOWNSAMPLE_ANDROID����ʾ���ѵ�����������ɫ����������Ϊ���ⲿ��׿��ʽָ����Y��CBCR��ʽͼ�񣬶����Ƕ�����������


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
		renderPassStripeBeginInfoARM.sType = VK_STRUCTURE_TYPE_MAX_ENUM;//����ṹ���sTypeû�ж���
		renderPassStripeBeginInfoARM.pNext = &renderPassTransformBeginInfoQCOM;
		renderPassTransformBeginInfoQCOM.sType = VK_STRUCTURE_TYPE_RENDER_PASS_TRANSFORM_BEGIN_INFO_QCOM;
		renderPassTransformBeginInfoQCOM.pNext = nullptr;
	}

};


void RenderPassTest::RenderPassCmdTest()
{

	VkCommandBuffer cmdbuf;

	RenderPassBeginInfoExt renderPassBeginInfoExt{};

	//�ο�ʹ��VK_IMAGE_CREATE_SAMPLE_LOCATIONS_COMPATIBLE_DEPTH_BIT_EXT������ͼ������/ģ�帽������ȷ����ͼ�񲼾�ȡ����������Ⱦ��ͼ������Դ�����һ������λ�ã����½ṹ��ָ������λ��
	VkRenderPassSampleLocationsBeginInfoEXT& renderPassSampleLocationsBeginInfoEXT = renderPassBeginInfoExt.renderPassSampleLocationsBeginInfoEXT;
	renderPassSampleLocationsBeginInfoEXT.attachmentInitialSampleLocationsCount = 1;

	VkAttachmentSampleLocationsEXT attachmentSampleLocationsEXT{};
	attachmentSampleLocationsEXT.attachmentIndex = 0;//�����������ָ�ĸ�����������VK_IMAGE_CREATE_SAMPLE_LOCATIONS_COMPATIBLE_DEPTH_BIT_EXT�����ģ���sampleLocationsInfo�е�������ᱻ����
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


	attachmentSampleLocationsEXT.sampleLocationsInfo = locationsEXTs;//�����ڽ����������Ĳ��ִӸ����ĳ�ʼ����ת������ʹ�����ĵ�һ���Ӵ�����Ϊ����ָ����ͼ�񲼾ֵ�sampleλ��״̬��


	renderPassSampleLocationsBeginInfoEXT.pAttachmentInitialSampleLocations = &attachmentSampleLocationsEXT;//��attachmentInitialSampleLocationsCount��VkAttachmentSampleLocationsEXT�������׵�ַָ�룬ָ�������������Լ�����λ�ã�����ÿ��Ԫ��ָ����depth/stencil������subpass�еĵ�һ��ʹ��ʱ���Զ�ת������ʱʹ�õĲ���λ��
	renderPassSampleLocationsBeginInfoEXT.postSubpassSampleLocationsCount = 1;
	VkSubpassSampleLocationsEXT subpassSampleLocationsEXT{};
	subpassSampleLocationsEXT.subpassIndex = 0;//���subpassû��depth/stencil�������߸ø���������VK_IMAGE_CREATE_SAMPLE_LOCATIONS_COMPATIBLE_DEPTH_BIT_EXT��������VkPhysicalDeviceSampleLocationsPropertiesEXT::variableSampleLocations Ϊ VK_TRUE���� sampleLocationsInfo�еĲ����ᱻ����
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

	renderPassSampleLocationsBeginInfoEXT.pPostSubpassSampleLocations = &subpassSampleLocationsEXT;//��postSubpassSampleLocationsCount��VkSubpassSampleLocationsEXT�������׵�ַָ�룬ָ��subpass�������Լ�����λ�ã�ÿ��Ԫ��ָ����depth/stencil������subpass�е����һ��ʹ��ʱ���Զ�ת������ʱʹ�õĲ���λ�ã����⣬���
	//VkPhysicalDeviceSampleLocationsPropertiesEXT::variableSampleLocations Ϊ VK_FALSE,�����е�Ԫ�ر���Ͱ��ڸ�subpass��Ӧ����������е�pipeline�Ĳ���λ����ƥ�䣬���variableSampleLocations Ϊ VK_TRUE���������ֵ������ʹ��



	//VkRenderPassTransformBeginInfoQCOM
	//���Ҫ����render pass transform,����Ҫ����һ��VkRenderPassTransformBeginInfoQCOM�ṹ��
	VkRenderPassTransformBeginInfoQCOM& renderPassTransformBeginInfoQCOM = renderPassBeginInfoExt.renderPassTransformBeginInfoQCOM;
	renderPassTransformBeginInfoQCOM.transform = VK_SURFACE_TRANSFORM_ROTATE_180_BIT_KHR;//ָ��render pass��ת����ʽ������ָ��Ϊ��ת180����Ϊ�ο�������ֻ��ָ��transform-02871
	//ΪVK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR, VK_SURFACE_TRANSFORM_ROTATE_90_BIT_KHR, VK_SURFACE_TRANSFORM_ROTATE_180_BIT_KHR,����VK_SURFACE_TRANSFORM_ROTATE_270_BIT_KHR����renderPass����ʱ��flags�������VK_RENDER_PASS_CREATE_TRANSFORM_BIT_QCOM


	//VkDeviceGroupRenderPassBeginInfo
	//��������˸����ݽṹ��������һ��devivce mask�͸�device�ϵ�render areas
	VkDeviceGroupRenderPassBeginInfo& deviceGroupRenderPassBeginInfo = renderPassBeginInfoExt.deviceGroupRenderPassBeginInfo;
	deviceGroupRenderPassBeginInfo.deviceMask = 1;
	deviceGroupRenderPassBeginInfo.deviceRenderAreaCount = 1;//�����0����pDeviceRenderAreas����дVkRenderPassBeginInfo::renderArea��Ȼ��Ϊÿ�������豸�ṩ��Ⱦ�������û�иýṹ�壬��render passʵ����device maskΪVkDeviceGroupCommandBufferBeginInfo::deviceMask�����û���ṩ�ýṹ����߸�ֵΪ0����, VkRenderPassBeginInfo::renderAreaӦ�õ����������豸
	VkRect2D renderArea{};
	renderArea.extent.width = 1;
	renderArea.extent.height = 1;
	renderArea.offset.x = 0;
	renderArea.offset.y = 0;

	deviceGroupRenderPassBeginInfo.pDeviceRenderAreas = &renderArea;//ָ��ÿ�������豸����Ⱦ����
	/*
	VkDeviceGroupRenderPassBeginInfo��Ч�÷���
	1.deviceMask����Ϊ0���ұ���Ϊһ���Ϸ���device mask���ұ���ʱcommand buffer��ʼdevice mask�е��Ӽ�
	2. pDeviceRenderAreas�� offset.x�� offset.y������ڵ���0�� extent.width�� extent.height�������0
	3.offset.x + extent.width����С�ڵ��� maxFramebufferWidth��offset.y + extent.height����С�ڵ��� maxFramebufferHeight��

	*/


	//VkRenderPassAttachmentBeginInfo
	VkRenderPassAttachmentBeginInfo& renderPassAttachmentBeginInfo = renderPassBeginInfoExt.renderPassAttachmentBeginInfo;
	renderPassAttachmentBeginInfo.attachmentCount = 0;
	renderPassAttachmentBeginInfo.pAttachments = VK_NULL_HANDLE;//ָ��ÿ����������Ӧ��image view���ʹ���render pass�ĸ���һһ��Ӧ
	/*
	1. pAttachments��ÿ��Ԫ��ֻ��ָ��һ��mipmap���ұ�����identity swizzle�������Ҵ���ʱ�� VkImageViewCreateInfo::viewType������ VK_IMAGE_VIEW_TYPE_3D
	2.��� multisampled-render-to-single-sampled���κ�subpass������pAttachments��ÿ��Ԫ�صĲ�����ΪVK_SAMPLE_COUNT_1_BIT�ı�����֧��VkMultisampledRenderToSingleSampledInfoEXT::rasterizationSamples��format��ʽ
	3.pAttachmentsӦ����attachmentCount����Ч��VkImageView�ľ����������׵�ַ
	*/


	// VkMultiviewPerViewRenderAreasRenderPassBeginInfoQCOM
	//�������multiview,��multiviewPerViewRenderAreas���Կ���������԰���һ��VkMultiviewPerViewRenderAreasRenderPassBeginInfoQCOM�ṹ��
	VkMultiviewPerViewRenderAreasRenderPassBeginInfoQCOM& multiviewPerViewRenderAreasRenderPassBeginInfoQCOM = renderPassBeginInfoExt.multiviewPerViewRenderAreasRenderPassBeginInfoQCOM;
	multiviewPerViewRenderAreasRenderPassBeginInfoQCOM.perViewRenderAreaCount = 1;//�����Ϊ0����дVkRenderPassBeginInfo::renderArea �� VkRenderingInfo::renderArea��Ȼ��Ϊÿ����ͼ�ṩ��Ⱦ����VkRenderPassBeginInfo::renderArea �� VkRenderingInfo::renderArea��ΪpPerViewRenderAreas�Ĳ�����
	//��perViewRenderAreaCount�������render pass��VkRenderPassMultiviewCreateInfo::pViewMasks. ���� VkRenderingInfo::viewMaskָ���������Чλ�������������0��VkRenderPassBeginInfo::renderArea or VkRenderingInfo::renderArea��Ӧ�õ����е�render view
		VkRect2D viewRenderArea{};
		viewRenderArea.extent.width = 1;
		viewRenderArea.extent.height = 1;
		viewRenderArea.offset.x = 0;
		viewRenderArea.offset.y = 0;
	multiviewPerViewRenderAreasRenderPassBeginInfoQCOM.pPerViewRenderAreas = &viewRenderArea;
	/*
	VkMultiviewPerViewRenderAreasRenderPassBeginInfoQCOM��Ч�÷���
	1. pPerViewRenderAreas�� offset.x�� offset.y������ڵ���0�� extent.width�� extent.height�������0
	2.pPerViewRenderAreas��offset.x + extent.width����С�ڵ��� maxFramebufferWidth��offset.y + extent.height����С�ڵ��� maxFramebufferHeight��
	3.���VkRenderPassBeginInfo����VkRenderingInfo��pNext�к��иýṹ���� VkRenderPassMultiviewCreateInfo::pViewMasks����VkRenderingInfo::viewMask�����˵�nλ���� perViewRenderAreaCount����Ϊn+1
	4.pPerViewRenderAreasΪperViewRenderAreaCount����Ч��VkRect2D��������׵�ַ
	*/



	VkRenderPassBeginInfo renderPassBeginInfo{};
	renderPassBeginInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
	renderPassBeginInfo.pNext = &renderPassBeginInfoExt.deviceGroupRenderPassBeginInfo;
	renderPassBeginInfo.clearValueCount = 0;
	renderPassBeginInfo.pClearValues = VK_NULL_HANDLE;//��VkClearValue�������׵�ַָ�룬����attachment���������������ڵ�Ԫ�ؽ��ᱻ����
	renderPassBeginInfo.framebuffer = VK_NULL_HANDLE;
	renderPassBeginInfo.renderArea.extent = VkExtent2D{ .width = 1,
														.height = 1 };
	/*
	renderArea:ָ����Ⱦ�����лᱻӰ������и�����x��y���ڷ�Χ�ڵ�pixelֵ���һ����������е�layer�����Ӧ����VkRenderPassTransformBeginInfoQCOM::transform����renderArea������framebuffer��ά���ڣ�
				��� render pass transform���ã���renderArea����Ϊframebuffer ��ת��ǰ��ά�ȣ���renderArea�� VkRenderPassTransformBeginInfoQCOM::transform,ת���󣬽���Ϊframebufferת�����ά�ȣ�
				��� multiviewPerViewRenderAreas ��������renderArea������VkMultiviewPerViewRenderAreasRenderPassBeginInfoQCOM::pPerViewRenderAreas��һ������
				��� subpassShading��������renderArea�������framebuffer��ά�� 
	*/
	renderPassBeginInfo.renderArea.offset = { .x = 0,.y = 0 };
	renderPassBeginInfo.renderPass = VK_NULL_HANDLE;
	
	/*
	�Ϸ��÷���
	1.clearValueCount �������renderPass����ָ����loadOp������stencilLoadOp�����depth/stencil format��ΪVK_ATTACHMENT_LOAD_OP_CLEAR��attachment����
	2.���clearValueCount ��Ϊ 0, pClearValues �����ǺϷ���clearValueCount��VkClearValue�������׵�ַ
	3.renderPass����ʹ���framebufferʱ��renderPass�����
	4.���pNext �в���VkDeviceGroupRenderPassBeginInfo ���ߺ�������deviceRenderAreaCount Ϊ 0,��
												��1��renderArea.extent.width��renderArea.extent.height�������0,renderArea.offset.x��renderArea.offset.y ������ڵ���0
												��2��renderArea.extent.width + renderArea.offset.x ����С�ڵ���framebuffer����ʱ��width��renderArea.extent.height + renderArea.offset.y ����С�ڵ���framebuffer����ʱ��height
	5.���pNext �к���VkDeviceGroupRenderPassBeginInfo���� pDeviceRenderAreas�е�ÿһ��Ԫ�ص�offset.x + extent.width����С�ڵ���framebuffer����ʱ��width��offset.y + extent.height����С�ڵ���framebuffer����ʱ��height
	6.��� framebuffer����ʱ��VkFramebufferCreateInfo::flags ���� VK_FRAMEBUFFER_CREATE_IMAGELESS_BIT, �� pNext ����VkRenderPassAttachmentBeginInfo , �� VkRenderPassAttachmentBeginInfo.attachmentCount����Ϊ0
	7.��� framebuffer ����ʱ�� VkFramebufferCreateInfo::flags ����VK_FRAMEBUFFER_CREATE_IMAGELESS_BIT, ��
												��1��pNext�е�VkRenderPassAttachmentBeginInfo.attachmentCount������ڴ���framebufferʱ�� VkFramebufferAttachmentsCreateInfo::attachmentImageInfoCount
												��2�� pNext�е�VkRenderPassAttachmentBeginInfo.pAttachments�е�ÿ������������renderPass�Լ�framebuffer���ڵ�Device�ϴ���
												��3��pNext�е�VkRenderPassAttachmentBeginInfo.pAttachments�е�ÿ��������VkImageView ����ʱ��VkImageCreateInfo::flags ������ڴ���framebuffer��VkFramebufferAttachmentsCreateInfo::pAttachmentImageInfos�ж�ӦԪ�ص�flags����
												��4��pNext�е�VkRenderPassAttachmentBeginInfo.pAttachments�е�ÿ��������VkImageView ����ʱ��usage ����Դ�ڴ���framebuffer��VkFramebufferAttachmentsCreateInfo::pAttachmentImageInfos�ж�ӦԪ�ص�usage����
												��5��pNext�е�VkRenderPassAttachmentBeginInfo.pAttachments�е�ÿ��������VkImageView ����ʱ��width��height ������ڴ���framebuffer��VkFramebufferAttachmentsCreateInfo::pAttachmentImageInfos�ж�ӦԪ�ص�width��height����
												��6��pNext�е�VkRenderPassAttachmentBeginInfo.pAttachments�е�ÿ��������VkImageView ����ʱ��VkImageCreateInfo::subresourceRange.layerCount ������ڴ���framebuffer��VkFramebufferAttachmentsCreateInfo::pAttachmentImageInfos�ж�ӦԪ�ص� layerCount����
												��7��pNext�е�VkRenderPassAttachmentBeginInfo.pAttachments�е�ÿ��������VkImageView ����ʱ�� VkImageFormatListCreateInfo::viewFormatCount������ڴ���framebuffer��VkFramebufferAttachmentsCreateInfo::pAttachmentImageInfos�ж�ӦԪ�ص�  viewFormatCount������
												��8��pNext�е�VkRenderPassAttachmentBeginInfo.pAttachments�е�ÿ��������VkImageView ����ʱ�� VkImageFormatListCreateInfo::pViewFormats �е�Ԫ�ر�����ڴ���framebuffer��VkFramebufferAttachmentsCreateInfo::pAttachmentImageInfos�ж�ӦԪ�ص�  pViewFormats�е�Ԫ��
												��9��pNext�е�VkRenderPassAttachmentBeginInfo.pAttachments�е�ÿ��������VkImageView ����ʱ��VkImageCreateInfo::format �������renderPass�Ķ�Ӧ������ VkAttachmentDescription::format
												��10�����nullColorAttachmentWithExternalFormatResolve Ϊ VK_FALSE,��subpass������ʹ��һ��ͨ�� vkGetAndroidHardwareBufferPropertiesANDROID�ӿڻ�ȡ��VkAndroidHardwareBufferFormatResolvePropertiesANDROID::colorAttachmentFormat��ʽ������image����Ϊresolve ��������color �����ĸ�ʽ����͸�resolve������ͬ
												��11��pNext�е�VkRenderPassAttachmentBeginInfo.pAttachments�е�ÿ��������VkImageView ����ʱ��format��VkExternalFormatANDROID::externalFormat������ ��format�������renderPass����ʱ��Ӧ�� VkAttachmentDescription2��pNext�е�VkExternalFormatANDROID::externalFormat
												��12��pNext�е�VkRenderPassAttachmentBeginInfo.pAttachments�е�ÿ��������VkImageView ����ʱ��VkImageCreateInfo::samples �������renderPass�Ķ�Ӧ������VkAttachmentDescription::samples�����ߵ���VK_SAMPLE_COUNT_1_BIT�������renderPassʱ��pNext�к���VkMultisampledRenderToSingleSampledInfoEXT��multisampledRenderToSingleSampledEnableΪVK_TRUE

	
	8.���pNext�к���VkRenderPassTransformBeginInfoQCOM����renderArea.offset����Ϊ��0��0������VkRenderPassTransformBeginInfoQCOM::transformת����renderArea.extent�������framebuffer��ά��
	9.���pNext�к���VkMultiviewPerViewRenderAreasRenderPassBeginInfoQCOM����perViewRenderAreaCount��Ϊ0���� multiviewPerViewRenderAreas ���Ա��뿪������renderArea����������render view��render area��һ������
	10.���pNext ����VkRenderPassStripeBeginInfoARM ,  VkRenderPassStripeInfoARM::pStripeInfos�ж����stripe areas�Ĳ����������renderArea 
	11.renderPass��framebuffer���ڵ�Device������ͬ
	*/





	vkCmdBeginRenderPass(cmdbuf, &renderPassBeginInfo, VK_SUBPASS_CONTENTS_INLINE);//�����˸�����󼴿ɿ�ʼ��һ��subpass�������¼
	/*
	��Ч�÷���
	1.���pRenderPassBegin�е�rendPass����ʱ���κ�VkAttachmentDescription�е�initialLayout���� finalLayout������VkAttachmentReference�е�layoutΪ
			VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL���� pRenderPassBegin�е�framebuffer��Ӧ�ĸ�����image view����ʱ���뺬��VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT
	2.���pRenderPassBegin�е�rendPass����ʱ���κ�VkAttachmentDescription�е�initialLayout���� finalLayout������VkAttachmentReference�е�layoutΪ
			VK_IMAGE_LAYOUT_DEPTH_READ_ONLY_STENCIL_ATTACHMENT_OPTIMAL,
			VK_IMAGE_LAYOUT_DEPTH_ATTACHMENT_STENCIL_READ_ONLY_OPTIMAL,
			VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL, ����
			VK_IMAGE_LAYOUT_DEPTH_STENCIL_READ_ONLY_OPTIMAL��
			VK_IMAGE_LAYOUT_DEPTH_ATTACHMENT_OPTIMAL, ���� VK_IMAGE_LAYOUT_DEPTH_READ_ONLY_OPTIMAL,
			VK_IMAGE_LAYOUT_STENCIL_ATTACHMENT_OPTIMAL, ����
			VK_IMAGE_LAYOUT_STENCIL_READ_ONLY_OPTIMAL���� pRenderPassBegin�е�framebuffer��Ӧ�ĸ�����image view����ʱ���뺬��VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT
	3.���pRenderPassBegin�е�rendPass����ʱ���κ�VkAttachmentDescriptionStencilLayout�е�stencilInitialLayout���� stencilFinalLayout������VkAttachmentReferenceStencilLayout�е�stencilLayoutΪ
			VK_IMAGE_LAYOUT_STENCIL_ATTACHMENT_OPTIMAL, ����
			VK_IMAGE_LAYOUT_STENCIL_READ_ONLY_OPTIMAL���� pRenderPassBegin�е�framebuffer��Ӧ�ĸ�����image view����ʱ���뺬��VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT
	4.���pRenderPassBegin�е�rendPass����ʱ���κ�VkAttachmentDescription�е�initialLayout���� finalLayout������VkAttachmentReference�е�layoutΪ
			VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL���� pRenderPassBegin�е�framebuffer��Ӧ�ĸ�����image view����ʱ���뺬��VK_IMAGE_USAGE_SAMPLED_BIT ���� VK_IMAGE_USAGE_INPUT_ATTACHMENT_BIT
	5.���pRenderPassBegin�е�rendPass����ʱ���κ�VkAttachmentDescription�е�initialLayout���� finalLayout������VkAttachmentReference�е�layoutΪ
			VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL���� pRenderPassBegin�е�framebuffer��Ӧ�ĸ�����image view����ʱ���뺬��VK_IMAGE_USAGE_TRANSFER_SRC_BIT
	6.���pRenderPassBegin�е�rendPass����ʱ���κ�VkAttachmentDescription�е�initialLayout���� finalLayout������VkAttachmentReference�е�layoutΪ
			VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL���� pRenderPassBegin�е�framebuffer��Ӧ�ĸ�����image view����ʱ���뺬��VK_IMAGE_USAGE_TRANSFER_DST_BIT
	7.���pRenderPassBegin�е�rendPass����ʱ���κ�VkAttachmentDescription�е�initialLayout��ΪVK_IMAGE_LAYOUT_UNDEFINED������initialLayout����Ϊ��ǰ pRenderPassBegin�е�framebuffer��Ӧ�ĸ�����image subresource��ͼ�񲼾�
	8.VkRenderPassCreateInfo�е�pDependencies�е�srcStageMask�Լ�dstStageMask�������ܹ���commmandBuffer���ڵ�commmandPool����ʱ��queueFamilyIndex����Ӧ�Ķ��д�֧�ֵġ�
	9.���renderPass���õ�framebuffer���κθ����͸�renderPass���õ��������������ڴ��ص�����������һ����������Ҫд��ģ�����Щ��������Ҫ����VK_ATTACHMENT_DESCRIPTION_MAY_ALIAS_BIT����Щ����ֻ����subpass������color attachment, depth/stencil, ���� resolve attachment
	10.���pRenderPassBegin�е�rendPass����ʱ���κ�VkAttachmentDescription�е�initialLayout���� finalLayout������VkAttachmentReference�е�layoutΪ
			VK_IMAGE_LAYOUT_ATTACHMENT_FEEDBACK_LOOP_OPTIMAL_EXT���� pRenderPassBegin�е�framebuffer��Ӧ�ĸ�����image view����ʱ���뺬��VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT ���� VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT ���� VK_IMAGE_USAGE_INPUT_ATTACHMENT_BIT ���� VK_IMAGE_USAGE_SAMPLED_BIT 
			������ VK_IMAGE_USAGE_ATTACHMENT_FEEDBACK_LOOP_BIT_EXT
	11.���pRenderPassBegin�е�rendPass����ʱ���κ�VkAttachmentDescription�е�initialLayout���� finalLayout������VkAttachmentReference�е�layoutΪ
			VK_IMAGE_LAYOUT_RENDERING_LOCAL_READ_KHR���� pRenderPassBegin�е�framebuffer��Ӧ�ĸ�����image view����ʱ���뺬��VK_IMAGE_USAGE_STORAGE_BIT, ���� VK_IMAGE_USAGE_INPUT_ATTACHMENT_BIT ���� VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT �� VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT����֮һ
	12.���contents Ϊ VK_SUBPASS_CONTENTS_INLINE_AND_SECONDARY_COMMAND_BUFFERS_EXT, ��nestedCommandBuffer ���뿪��
	13.commandBuffer ������recording ״̬
	*/


	VkSubpassBeginInfo subpassBeginInfo{};
	subpassBeginInfo.sType = VK_STRUCTURE_TYPE_SUBPASS_BEGIN_INFO;
	subpassBeginInfo.pNext = nullptr;
	subpassBeginInfo.contents = VK_SUBPASS_CONTENTS_INLINE;/*���contents Ϊ VK_SUBPASS_CONTENTS_INLINE_AND_SECONDARY_COMMAND_BUFFERS_EXT, ��nestedCommandBuffer ���뿪��
	VK_SUBPASS_CONTENTS_INLINE��ָ���������¼��һ��primaryCommandBuffer�У��Ҹ�subpass���ܰ����κ�ִ��secondaryCommandBuffer������
	VK_SUBPASS_CONTENTS_SECONDARY_COMMAND_BUFFERS��ָ���������¼��һ��secondaryCommandBuffer�У���secondaryCommandBuffer��ֻ��ʹ��vkCmdExecuteCommands������ִ������secondaryCommandBufferֱ������vkCmdNextSubpass ���� vkCmdEndRenderPass.
	VK_SUBPASS_CONTENTS_INLINE_AND_SECONDARY_COMMAND_BUFFERS_EXT��ָ����subpass��������Լ�¼��һ��primaryCommandBuffer�Լ�ͨ�� vkCmdExecuteCommandsִ�е�secondaryCommandBuffer�С�
	*/


	vkCmdBeginRenderPass2(cmdbuf, &renderPassBeginInfo, &subpassBeginInfo);//�����˸�����󼴿ɿ�ʼ��һ��subpass�������¼
	/*
	�Ϸ��÷���
	1.pRenderPassBegin�е�framebuffer��renderPass���봴����commandBuffer���ڵ�Device��
	2.���pRenderPassBegin�е�rendPass����ʱ���κ�VkAttachmentDescription�е�initialLayout���� finalLayout������VkAttachmentReference�е�layoutΪ
			VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL���� pRenderPassBegin�е�framebuffer��Ӧ�ĸ�����image view����ʱ���뺬��VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT
	3.���pRenderPassBegin�е�rendPass����ʱ���κ�VkAttachmentDescription�е�initialLayout���� finalLayout������VkAttachmentReference�е�layoutΪ
			VK_IMAGE_LAYOUT_DEPTH_READ_ONLY_STENCIL_ATTACHMENT_OPTIMAL,
			VK_IMAGE_LAYOUT_DEPTH_ATTACHMENT_STENCIL_READ_ONLY_OPTIMAL,
			VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL, ����
			VK_IMAGE_LAYOUT_DEPTH_STENCIL_READ_ONLY_OPTIMAL��
			VK_IMAGE_LAYOUT_DEPTH_ATTACHMENT_OPTIMAL, ���� VK_IMAGE_LAYOUT_DEPTH_READ_ONLY_OPTIMAL,
			VK_IMAGE_LAYOUT_STENCIL_ATTACHMENT_OPTIMAL, ����
			VK_IMAGE_LAYOUT_STENCIL_READ_ONLY_OPTIMAL���� pRenderPassBegin�е�framebuffer��Ӧ�ĸ�����image view����ʱ���뺬��VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT
	4.���pRenderPassBegin�е�rendPass����ʱ���κ�VkAttachmentDescriptionStencilLayout�е�stencilInitialLayout���� stencilFinalLayout������VkAttachmentReferenceStencilLayout�е�stencilLayoutΪ
			VK_IMAGE_LAYOUT_STENCIL_ATTACHMENT_OPTIMAL, ����
			VK_IMAGE_LAYOUT_STENCIL_READ_ONLY_OPTIMAL���� pRenderPassBegin�е�framebuffer��Ӧ�ĸ�����image view����ʱ���뺬��VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT
	
	
	
	
	5.���pRenderPassBegin�е�rendPass����ʱ���κ�VkAttachmentDescription�е�initialLayout���� finalLayout������VkAttachmentReference�е�layoutΪ
			VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL���� pRenderPassBegin�е�framebuffer��Ӧ�ĸ�����image view����ʱ���뺬��VK_IMAGE_USAGE_SAMPLED_BIT ���� VK_IMAGE_USAGE_INPUT_ATTACHMENT_BIT
	6.���pRenderPassBegin�е�rendPass����ʱ���κ�VkAttachmentDescription�е�initialLayout���� finalLayout������VkAttachmentReference�е�layoutΪ
			VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL���� pRenderPassBegin�е�framebuffer��Ӧ�ĸ�����image view����ʱ���뺬�� VK_IMAGE_USAGE_TRANSFER_SRC_BIT
	7.���pRenderPassBegin�е�rendPass����ʱ���κ�VkAttachmentDescription�е�initialLayout���� finalLayout������VkAttachmentReference�е�layoutΪ
			VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL���� pRenderPassBegin�е�framebuffer��Ӧ�ĸ�����image view����ʱ���뺬��VK_IMAGE_USAGE_TRANSFER_DST_BIT
	8.���pRenderPassBegin�е�rendPass����ʱ���κ�VkAttachmentDescription�е�initialLayout��ΪVK_IMAGE_LAYOUT_UNDEFINED������initialLayout����Ϊ��ǰ pRenderPassBegin�е�framebuffer��Ӧ�ĸ�����image subresource��ͼ�񲼾�
	9.VkRenderPassCreateInfo�е�pDependencies�е�srcStageMask�Լ�dstStageMask�������ܹ���commmandBuffer���ڵ�commmandPool����ʱ��queueFamilyIndex����Ӧ�Ķ��д�֧�ֵġ�
	10.���renderPass���õ�framebuffer���κθ����͸�renderPass���õ��������������ڴ��ص�����������һ����������Ҫд��ģ�����Щ��������Ҫ����VK_ATTACHMENT_DESCRIPTION_MAY_ALIAS_BIT����Щ����ֻ����subpass������color attachment, depth/stencil, ���� resolve attachment
	11.���pRenderPassBegin�е�rendPass����ʱ���κ�VkAttachmentDescription�е�initialLayout���� finalLayout������VkAttachmentReference�е�layoutΪ
			VK_IMAGE_LAYOUT_ATTACHMENT_FEEDBACK_LOOP_OPTIMAL_EXT���� pRenderPassBegin�е�framebuffer��Ӧ�ĸ�����image view����ʱ���뺬��VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT ���� VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT ���� VK_IMAGE_USAGE_INPUT_ATTACHMENT_BIT ���� VK_IMAGE_USAGE_SAMPLED_BIT 
			������ VK_IMAGE_USAGE_ATTACHMENT_FEEDBACK_LOOP_BIT_EXT
	12.���pRenderPassBegin�е�rendPass����ʱ���κ�VkAttachmentDescription�е�initialLayout���� finalLayout������VkAttachmentReference�е�layoutΪ
			VK_IMAGE_LAYOUT_RENDERING_LOCAL_READ_KHR���� pRenderPassBegin�е�framebuffer��Ӧ�ĸ�����image view����ʱ���뺬��VK_IMAGE_USAGE_STORAGE_BIT, ���� VK_IMAGE_USAGE_INPUT_ATTACHMENT_BIT ���� VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT �� VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT����֮һ
	13.commandBuffer ������recording ״̬

	
	
	
	*/




	//��ѯ��Ⱦ����,���ڸ�������renderArea
	VkExtent2D renderAreaGranularity{};
	vkGetRenderAreaGranularity(device, renderPass, &renderAreaGranularity);
	/*
	���������
	1.renderArea��width�Լ�offset.xӦ����renderAreaGranularity���ص�width��������,height�Լ�offset.yӦ����renderAreaGranularity���ص�height��������
	2.renderArea.width + renderArea.offset.xӦ�õ���VkRenderPassBeginInfo��framebuffer��width,renderArea.height + renderArea.offset.yӦ�õ���VkRenderPassBeginInfo��framebuffer��height
	*/



	//���뵽��һ��subpass
	vkCmdNextSubpass(cmdbuf, VK_SUBPASS_CONTENTS_SECONDARY_COMMAND_BUFFERS);//�����˸�����󼴿ɿ�ʼ��һ��subpass�������¼��subpass���������Ÿõ������ε�������command buffer������recoding״̬���Ҹ��������render passʵ����
	//���ã�������video code����ã�command buffer ����֧��ͼ�β���


	VkSubpassEndInfo subpassEndInfo{};
	subpassEndInfo.sType = VK_STRUCTURE_TYPE_SUBPASS_END_INFO;
		VkSubpassFragmentDensityMapOffsetEndInfoQCOM subpassFragmentDensityMapOffsetEndInfo{};
		subpassFragmentDensityMapOffsetEndInfo.sType = VK_STRUCTURE_TYPE_SUBPASS_FRAGMENT_DENSITY_MAP_OFFSET_END_INFO_QCOM;
		subpassFragmentDensityMapOffsetEndInfo.pNext = nullptr;
		subpassFragmentDensityMapOffsetEndInfo.fragmentDensityOffsetCount = 0;
			VkOffset2D fragmentDensityOffset{};
			fragmentDensityOffset.x = 0;
			fragmentDensityOffset.y = 0;
			subpassFragmentDensityMapOffsetEndInfo.pFragmentDensityOffsets = &fragmentDensityOffset;//����fragment density map offsets ÿ��layer��offset,��������=�㡣ÿ����x��y��ƫ��������֡���������أ�����Ƭ���ܶ�ӳ��Ļ�ȡ�ƶ��������ϡ�ƫ�������������Ļ򸺵ġ�����ýṹ��û�а��������һ��subpass��EndInfo��pNext�У��򽫺��Ըýṹ��Ĳ�����
			//������һ��subpass��VkSubpassEndInfo::pNext�л�����renderPass����VkSubpassFragmentDensityMapOffsetEndInfoQCOM,����fragmentDensityOffsetCountΪ0����offset (0,0) ���ᱻ Fetch Density Valueʹ��
		/*
		VkSubpassFragmentDensityMapOffsetEndInfoQCOM��Ч�÷���
		1.
		
		
		
		
		
		*/
	subpassEndInfo.pNext = &subpassFragmentDensityMapOffsetEndInfo;//pNext�п��Ժ���VkSubpassFragmentDensityMapOffsetEndInfoQCOM
	vkCmdNextSubpass2(cmdbuf, &subpassBeginInfo, &subpassEndInfo);//������vkCmdNextSubpass��ֻ�ǿ�����չ



	//����render pass ��Ⱦ
	vkCmdEndRenderPass(cmdbuf);//���ø�����󣬵�ǰsubpass���������һ��subpass����Ⱦ���������ܺ�vkCmdBeginRendering����ʹ�ã�vkCmdBeginQuery*�Լ�vkCmdEndQuery*��������ʹ����ͬһ��subpass�У���command buffer������recoding״̬���Ҹ��������render passʵ����
	//���ã�������video code����ã�command buffer ����֧��ͼ�β���

	vkCmdEndRenderPass2(cmdbuf, &subpassEndInfo);//������vkCmdEndRenderPass��ֻ�ǿ�����չ�����ø�����󣬵�ǰsubpass���������һ��subpass����Ⱦ���������ܺ�vkCmdBeginRendering����ʹ�ã�vkCmdBeginQuery*�Լ�vkCmdEndQuery*��������ʹ����ͬһ��subpass�У���command buffer������recoding״̬���Ҹ��������render passʵ����
	//���ã�������video code����ã�command buffer ����֧��ͼ�β���

}


















NS_TEST_END