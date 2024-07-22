#include "ResourceDescriptorsTest.h"
NS_TEST_BEGIN



/*
һ�� descriptor ��һ��ָ��������һ��shader resource ���� buffer, buffer view, image view, sampler, ���� combined image sampler��ͨ�� descriptor sets����֯��
ÿ��descriptor set�п��԰�����descriptor �Ų��� descriptor set layout������descriptor set layout �ɱ�pipeline layout����ʹ�ã���� descriptorBuffer ���Կ�������֧��
��descriptor �ŵ� descriptor buffers�С�

shaderͨ��ʹ��descriptor set��binding �Ž������εı�����������Դ����Щ�������������ӵ�descriptor set�е�descriptor��ӳ�䵽descriptor set��shader �ӿ�������  Shader Resource Interface p1409

shader ����ֱ��ͨ��64λ�ĵ�ֱַ�ӷ���buffer������Ҫͨ��descriptor���� Physical Storage Buffer Access p1352

*/


ResourceDescriptorsTest::ResourceDescriptorsTest()
{
}

void ResourceDescriptorsTest::run()
{
}

ResourceDescriptorsTest::~ResourceDescriptorsTest()
{
}

void ResourceDescriptorsTest::DescriptorTypeTest()
{
	// Descriptor Types    
	//vulkan��֧�ֶ���descriptor ���ͣ���Ӧ��ͬ����Դʹ�÷�ʽ


	// Storage Image
	{
	/*
	
	 һ��storage image (VK_DESCRIPTOR_TYPE_STORAGE_IMAGE) ��һ��������image resourceͨ��image view���еļ��أ��洢���Լ�ԭ�Ӳ����� descriptor type

	 ֧������shader�׶Σ����������p1242

	
	*/
	
	}

	// Sampler
	{
	/*
	һ��sampler descriptor (VK_DESCRIPTOR_TYPE_SAMPLER) ��һ������ sampler �� descriptor type,�������� sampled image�Ĳ�����Ϊ��p1473��

	*/
	}


	//Sampled Image
	{
	/*
	һ��sampled image (VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE) ��һ��������image resourceͨ��image view���еĲ���������p1473���� descriptor type
	
	shader �󶨵�һ��sampled image�����Լ�sampler���������в���

	֧������shader��image view��format��  format features �躬��VK_FORMAT_FEATURE_SAMPLED_IMAGE_BIT

	�󶨵�image subresource��layoutӦΪ��������֮һ��
    VK_IMAGE_LAYOUT_DEPTH_STENCIL_READ_ONLY_OPTIMAL
    VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL
    VK_IMAGE_LAYOUT_GENERAL
    VK_IMAGE_LAYOUT_SHARED_PRESENT_KHR
    VK_IMAGE_LAYOUT_DEPTH_READ_ONLY_STENCIL_ATTACHMENT_OPTIMAL
    VK_IMAGE_LAYOUT_DEPTH_ATTACHMENT_STENCIL_READ_ONLY_OPTIMAL
    VK_IMAGE_LAYOUT_DEPTH_READ_ONLY_OPTIMAL
    VK_IMAGE_LAYOUT_STENCIL_READ_ONLY_OPTIMAL
    VK_IMAGE_LAYOUT_READ_ONLY_OPTIMAL_KHR
    VK_IMAGE_LAYOUT_ATTACHMENT_FEEDBACK_LOOP_OPTIMAL_EXT
	*/
	
	}

	// Combined Image Sampler
	{
	/*
	һ��combined image sampler (VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER) ��һ�������Ĺ�����sampler�� image subresource��  descriptor type������ һ��sampler �� sampled image descriptor�󶨵���һ���Ϊһ��������descriptor
	
	�����descriptor ���õ�һ�� ʹ���� Y��CBCR conversion ���߲���  subsampled image��sampler����samplerֻ�����ڶ�ͬһdescriptor�е�image���в���������sampler��descriptor��image �Ϳ������������

	�󶨵�image subresource��layoutӦΪ��������֮һ��
	VK_IMAGE_LAYOUT_DEPTH_STENCIL_READ_ONLY_OPTIMAL
	VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL
	VK_IMAGE_LAYOUT_GENERAL
	VK_IMAGE_LAYOUT_SHARED_PRESENT_KHR
	VK_IMAGE_LAYOUT_DEPTH_READ_ONLY_STENCIL_ATTACHMENT_OPTIMAL
	VK_IMAGE_LAYOUT_DEPTH_ATTACHMENT_STENCIL_READ_ONLY_OPTIMAL
	VK_IMAGE_LAYOUT_DEPTH_READ_ONLY_OPTIMAL
	VK_IMAGE_LAYOUT_STENCIL_READ_ONLY_OPTIMAL
	VK_IMAGE_LAYOUT_READ_ONLY_OPTIMAL_KHR
	VK_IMAGE_LAYOUT_ATTACHMENT_FEEDBACK_LOOP_OPTIMAL_EXT

	*/
	
	}

	// Uniform Texel Buffer
	{
	/*
	һ��uniform texel buffer (VK_DESCRIPTOR_TYPE_UNIFORM_TEXEL_BUFFER) ��һ��������buffer resourceͨ��buffer view����image ����������p1473���� descriptor type
	
	uniform texel buffer������һ���������е�һά����texel���飬����������ɫ���ж�ȡʱ�����������ͼ��һ���ķ�ʽ���и�ʽת����
	
	֧������shader��image view��format��  format features �躬��VK_FORMAT_FEATURE_UNIFORM_TEXEL_BUFFER_BIT
	*/
	
	}


	// Storage Texel Buffer
	{
	/*
	һ�� storage texel buffer (VK_DESCRIPTOR_TYPE_STORAGE_TEXEL_BUFFER) ��һ��������buffer resourceͨ��buffer view����image ���أ��洢���Լ�ԭ�Ӳ����� descriptor type
	
	storage texel buffer������һ���������е�һά����texel���飬����������ɫ���ж�ȡʱ�����������ͼ��һ���ķ�ʽ���и�ʽת������� uniform texel buffer��storage texel buffer��������ͬ�ķ�ʽд��  storage images��

	���������p1244
	*/
	
	}

	// Storage Buffer
	{
	/*
	һ�� storage buffer (VK_DESCRIPTOR_TYPE_STORAGE_BUFFER) ��һ��ֱ�ӹ�����buffer resource����shader��ͨ���ṹ�������Ա�����м��أ��洢���Լ�ԭ�Ӳ����� descriptor type
	
	*/
	}

	// Uniform Buffer
	{
	/*
	һ��  uniform buffer (VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER) ��һ��ֱ�ӹ�����buffer resource����shader��ͨ���ṹ�������Ա�����м��ز����� descriptor type
	*/
	}

	// Dynamic Uniform Buffer
	{
	/*
		һ�� dynamic uniform buffer(VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC) ������ͬ�� uniform buffer��ֻ�Ǹ�descriptor��ȥָ��buffer��offset���ڰ�descriptor set ʱ���һ�� VkDescriptorBufferInfo ��dynamic offset��p1239�����ʼ����descriptor set��ʱ����������offset
	*/
	
	}

	//Dynamic Storage Buffer
	{
	/*
		һ�� dynamic storage buffer (VK_DESCRIPTOR_TYPE_STORAGE_BUFFER_DYNAMIC) ������ͬ�� storage buffer��ֻ�Ǹ�descriptor��ȥָ��buffer��offset���ڰ�descriptor set ʱ���һ�� VkDescriptorBufferInfo ��dynamic offset��p1239�����ʼ����descriptor set��ʱ����������offset
	*/
	}

	// Inline Uniform Block
	{
	/*
	һ��inline uniform block (VK_DESCRIPTOR_TYPE_INLINE_UNIFORM_BLOCK) ����������uniform buffer��ֻ�Ǹ�descriptor ���Ե�����ֱ�Ӵ洢��descriptor set�У����ö����buffer memory����ʡ���ڴ棬��������ܡ�
	
	�����÷�ʱ���С���ֳ������ݣ������push constants ����������ɢ�Ļ����Լ�dispatching commandsʱ������ͬ�ĳ������ݡ�
	
	inline uniform block descriptors ������ϳ�һ�����飬��һ��inline uniform block descriptor binding �������Сʵ����ָ�������binding���ֽ�������
	*/
	}

	// Sample Weight Image
	{
	/*
	һ��sample weight image (VK_DESCRIPTOR_TYPE_SAMPLE_WEIGHT_IMAGE_QCOM) ��һ�������� image resource ͨ�� image view ����weight image ���������� descriptor type���� image view ����ʹ�� VkImageViewSampleWeightCreateInfoQCOM �ṹ������

	shader���԰�һ��sample weight image������һ��sampled image�������Լ�һ��sampler����������weight image������

	֧������shader��weight image view��format��  format features �躬��VK_FORMAT_FEATURE_2_WEIGHT_IMAGE_BIT_QCOM��sampled image view��format��  format features �躬��VK_FORMAT_FEATURE_2_WEIGHT_SAMPLED_IMAGE_BIT_QCOM
	

	weight image subresources�Ĳ���Ӧ��Ϊ VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL����  VK_IMAGE_LAYOUT_GENERAL 
	*/
	}


	//Block Matching Image
	{
	/*
	һ��block matching image (VK_DESCRIPTOR_TYPE_BLOCK_MATCHING_IMAGE_QCOM) ��һ�������� image resource ͨ�� image view ����block matching ������ descriptor type��

	shader���԰�һ��block matching image��target image��������һ��reference image�������Լ�һ��sampler����������block matching��

	֧������shader��block matching image view��reference view ��format��  format features �躬��VK_FORMAT_FEATURE_2_BLOCK_MATCHING_BIT_QCOM
	
	block matching��image subresources �Ĳ���Ӧ��ΪVK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL ���� VK_IMAGE_LAYOUT_GENERAL

	*/
	
	}

	//Input Attachment
	{
	/*
	һ��input attachment (VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT) ��һ�������� image resource ͨ�� image view ������fragment shaders��framebuffer local load ������ descriptor type��

	���ڸ���image��tiling����֧��color attachments��VK_FORMAT_FEATURE_COLOR_ATTACHMENT_BIT �� VK_FORMAT_FEATURE_2_LINEAR_COLOR_ATTACHMENT_BIT_NV �������� depth/stencil attachments (VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT) Ҳ��֧��input attachments
	
	input attachment���Ե�image view�Ĳ���Ӧ��Ϊ�����е�һ��:
    VK_IMAGE_LAYOUT_DEPTH_STENCIL_READ_ONLY_OPTIMAL
    VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL
    VK_IMAGE_LAYOUT_GENERAL
    VK_IMAGE_LAYOUT_SHARED_PRESENT_KHR
    VK_IMAGE_LAYOUT_DEPTH_READ_ONLY_STENCIL_ATTACHMENT_OPTIMAL
    VK_IMAGE_LAYOUT_DEPTH_ATTACHMENT_STENCIL_READ_ONLY_OPTIMAL
    VK_IMAGE_LAYOUT_READ_ONLY_OPTIMAL_KHR
    VK_IMAGE_LAYOUT_ATTACHMENT_FEEDBACK_LOOP_OPTIMAL_EXT
    VK_IMAGE_LAYOUT_RENDERING_LOCAL_READ_KHR
	*/
	
	}

	//Acceleration Structure
	{
	/*
	һ��acceleration structure (VK_DESCRIPTOR_TYPE_ACCELERATION_STRUCTURE_KHR ���� VK_DESCRIPTOR_TYPE_ACCELERATION_STRUCTURE_NV) ��һ����ȡshader����������ray tracing�ĳ����������ݣ�ֻ������ descriptor type��

	*/
	}

	//Mutable
	{
	/*
	һ�� mutable  descriptor (VK_DESCRIPTOR_TYPE_MUTABLE_EXT) ָ�����descriptor ���Ա��Ϊ�κ��������͵�descriptor�������������VkDescriptorSetLayoutCreateInfo.pNext�е�VkMutableDescriptorTypeListEXT::pDescriptorTypes�б��е�ǰbingding������descriptor type������
	
	����ͨ��ָ��VK_DESCRIPTOR_TYPE_MUTABLE_EXT binding�Լ� ��binding�� VkMutableDescriptorTypeCreateInfoEXT::pDescriptorTypes ���� vkGetDescriptorSetLayoutSupport����ȡ��descriptor֧�ֵ�descriptor type��
	*/
	
	
	}

}

struct DescriptorSetLayoutCreateInfoEXT {
	VkDescriptorSetLayoutBindingFlagsCreateInfo	descriptorSetLayoutBindingFlagsCreateInfo{};
	VkMutableDescriptorTypeCreateInfoEXT mutableDescriptorTypeCreateInfoEXT{};
	DescriptorSetLayoutCreateInfoEXT() {
		Init();
	}
	void Init() {
		descriptorSetLayoutBindingFlagsCreateInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_BINDING_FLAGS_CREATE_INFO;
		descriptorSetLayoutBindingFlagsCreateInfo.pNext = nullptr;
		mutableDescriptorTypeCreateInfoEXT.sType = VK_STRUCTURE_TYPE_MUTABLE_DESCRIPTOR_TYPE_CREATE_INFO_EXT;
		mutableDescriptorTypeCreateInfoEXT.pNext = nullptr;

	}


};

struct DescriptorPoolCreateInfoEXT {
	VkDescriptorPoolInlineUniformBlockCreateInfo descriptorPoolInlineUniformBlockCreateInfo{};
	VkMutableDescriptorTypeCreateInfoEXT mutableDescriptorTypeCreateInfoEXT{};
	DescriptorPoolCreateInfoEXT() {
		Init();
	}
	void Init() {
		descriptorPoolInlineUniformBlockCreateInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_INLINE_UNIFORM_BLOCK_CREATE_INFO;
		descriptorPoolInlineUniformBlockCreateInfo.pNext = nullptr;
		mutableDescriptorTypeCreateInfoEXT.sType = VK_STRUCTURE_TYPE_MUTABLE_DESCRIPTOR_TYPE_CREATE_INFO_EXT;
		mutableDescriptorTypeCreateInfoEXT.pNext = nullptr;


	}


};

struct WriteDescriptorSetEXT
{
	VkWriteDescriptorSetAccelerationStructureKHR writeDescriptorSetAccelerationStructureKHR{};
	VkWriteDescriptorSetAccelerationStructureNV writeDescriptorSetAccelerationStructureNV{};
	VkWriteDescriptorSetInlineUniformBlock writeDescriptorSetInlineUniformBlock{};
	WriteDescriptorSetEXT() {
		Init();
	}
	void Init() {
		writeDescriptorSetAccelerationStructureKHR.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET_ACCELERATION_STRUCTURE_KHR;
		writeDescriptorSetAccelerationStructureKHR.pNext = nullptr;
		writeDescriptorSetAccelerationStructureNV.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET_ACCELERATION_STRUCTURE_NV;
		writeDescriptorSetAccelerationStructureNV.pNext = nullptr;
		writeDescriptorSetInlineUniformBlock.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET_INLINE_UNIFORM_BLOCK;
		writeDescriptorSetInlineUniformBlock.pNext = nullptr;

	}

};

void ResourceDescriptorsTest::DescriptorSetsTest()
{
	/*
	����
	descriptor ��ϳ�descriptor set��Ȼ��ͨ�� descriptor set layout�������е�descriptor�����ͺ��������Լ����ǵ�binding �ţ�descriptor set layoutҲ��ȷ��descriptor setҪʹ�õ�resource�Լ� shader resources��shader stage֮��Ľӿڡ�
	
	*/

	//descriptor set layout
	VkDescriptorSetLayout descriptorSetLayout{};
	{
	/*
	descriptor set layout ͨ��һ��һ������ descriptor bindings �����壬ÿ��������descriptor binding ��һ�� descriptor type��һ��bingding�е� descriptor count���Լ�һ��ɷ��ʸ�binding�� shader stage ��ɣ����У����ʹ�� immutable samplers��һ�� sampler descriptors�����顣
	*/
	
		VkDescriptorSetLayoutCreateInfo descriptorSetLayoutCreateInfo{};
		descriptorSetLayoutCreateInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
			DescriptorSetLayoutCreateInfoEXT descriptorSetLayoutCreateInfoEXT{};
		descriptorSetLayoutCreateInfo.pNext = &descriptorSetLayoutCreateInfoEXT.descriptorSetLayoutBindingFlagsCreateInfo;//���Ժ���VkDescriptorSetLayoutBindingFlagsCreateInfo ���� VkMutableDescriptorTypeCreateInfoEXT
		descriptorSetLayoutCreateInfo.flags = 0;//��һ��  VkDescriptorSetLayoutCreateFlagBits ���ֵ��λ���룬ָ��descriptor set layout�����Ķ�������
		/*
		VkDescriptorSetLayoutCreateFlagBits:

		VK_DESCRIPTOR_SET_LAYOUT_CREATE_PUSH_DESCRIPTOR_BIT_KHR :  ָ��descriptor sets����ʹ�����layout���з��䣬���descriptors ��ͨ��vkCmdPushDescriptorSetKHR ���и��� 
		VK_DESCRIPTOR_SET_LAYOUT_CREATE_UPDATE_AFTER_BIND_POOL_BIT :  ָ��descriptor sets�����һ����������VK_DESCRIPTOR_POOL_CREATE_UPDATE_AFTER_BIND_BIT ��descriptor pool ��ȥ���䣬�������־������descriptor set layout��descriptors per-stage �Լ� per-pipeline layout���ɱ��������������ƣ���
																					non-UpdateAfterBind ����ֻ��ͳ�Ʋ��������־������descriptor set �е�descriptors������UpdateAfterBind ���ƻ�ͳ������descriptors�����������ܸ���non-UpdateAfterBind ����������
		
		VK_DESCRIPTOR_SET_LAYOUT_CREATE_INDIRECT_BINDABLE_BIT_NV:  ָ��ʹ�����layout��descriptor sets �ܹ��󶨵���VK_PIPELINE_CREATE_INDIRECT_BINDABLE_BIT_NV ������compute pipelines����Device-Generated Commands ��ʹ�á�
		VK_DESCRIPTOR_SET_LAYOUT_CREATE_DESCRIPTOR_BUFFER_BIT_EXT:  ָ�����layoutֻ���������� descriptor buffers.
		VK_DESCRIPTOR_SET_LAYOUT_CREATE_EMBEDDED_IMMUTABLE_SAMPLERS_BIT_EXT:  ָ�����layoutֻ�ܰ���vkCmdBindDescriptorBufferEmbeddedSamplersEXT ���԰󶨵� immutable samplers������ͨ����immutable samplers��embedded immutable samplers����ҪӦ���ṩһ�� descriptor buffer.

		VK_DESCRIPTOR_SET_LAYOUT_CREATE_HOST_ONLY_POOL_BIT_EXT :  ָ��descriptor sets�����һ����������VK_DESCRIPTOR_POOL_CREATE_HOST_ONLY_BIT_EXT ��descriptor pool ��ȥ���䣬�������־������descriptor set layout��descriptors per-stage  ��û�����Ե�������������ƣ�host descriptor sets ֻ�ܿ���host memory�����ƣ�����������һЩ�����ʵ�ֶ��յ��ر�����ƣ� ʵ��
																					���ܻ�����֧�ֵ�UpdateAfterBind ���� non-UpdateAfterBind descriptors������������һ������
		
		VK_DESCRIPTOR_SET_LAYOUT_CREATE_PER_STAGE_BIT_NV:  ָ��descriptor sets��ʹ�����layout��bingding ������ÿһ��stage�п��ܻ���ֲ�ͬ��Դ�һ�����Դ����
		*/
		descriptorSetLayoutCreateInfo.bindingCount = 1;// pBindings �еĸ���
			VkDescriptorSetLayoutBinding descriptorBinding{};
			{
				descriptorBinding.binding = 0;//ָ��binding�ţ���Ӧshader stage����ͬbinding�ŵ���Դ
				descriptorBinding.descriptorCount = 1;//��shader stage�����binding�Ϻ��е�descriptors����������shader��ͨ��������ʣ� ��� descriptorTypeΪ VK_DESCRIPTOR_TYPE_INLINE_UNIFORM_BLOCK�����ֵ��ʾ inline uniform block ���ֽڴ�С�������ֵΪ0���ʾshader�����ڰ������layout��pipeline��ʹ�����binding
				descriptorBinding.descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;//��һ�� VkDescriptorTypeֵ��ָ�����binding�ϵ�resource descriptors������
				descriptorBinding.pImmutableSamplers = (const VkSampler*)VkSampler{/*��������һ����Ч��VkSampler*/};//Ӱ�� samplers�ĳ�ʼ��,���descriptorTypeΪ VK_DESCRIPTOR_TYPE_SAMPLER Ϊ VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER���Ҹ�VkSampler��ΪVK_NULL_HANDL���ʾ��VkSampler���ڸ�binding��ʹ�����޷���̬���£����VkSamplerΪVK_NULL_HANDL���ʾ���Զ�̬���£����descriptorType��Ϊǰ��˵�����֣�����������ᱻ����
				descriptorBinding.stageFlags = VK_SHADER_STAGE_ALL;//�� VkShaderStageFlagBits ���ֵ��λ���룬ָ�����binding���Ա����ʵ�shader stage
				/*
				VkDescriptorSetLayoutBinding��Ч�÷���
				1.���descriptorType ΪVK_DESCRIPTOR_TYPE_SAMPLER ����VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER����descriptorCount��Ϊ0��pImmutableSamplers��ΪNULL������pImmutableSamplers����ָ��һ������descriptorCount����ЧVkSampler�����顣
				2.���inlineUniformBlock ����û�п�������descriptorType ����ΪVK_DESCRIPTOR_TYPE_INLINE_UNIFORM_BLOCK
				3.���descriptorType ΪVK_DESCRIPTOR_TYPE_INLINE_UNIFORM_BLOCK ��1��descriptorCount ����Ϊ4�ı���
																				 ��2�����VkDescriptorSetLayoutCreateInfo::flags ������VK_DESCRIPTOR_SET_LAYOUT_CREATE_DESCRIPTOR_BUFFER_BIT_EXT����descriptorCount ����С�ڵ���VkPhysicalDeviceInlineUniformBlockProperties::maxInlineUniformBlockSize
				4.���VkDescriptorSetLayoutCreateInfo::flags ����VK_DESCRIPTOR_SET_LAYOUT_CREATE_EMBEDDED_IMMUTABLE_SAMPLERS_BIT_EXT����1��descriptorType ����ΪVK_DESCRIPTOR_TYPE_SAMPLER��descriptorCount ����С�ڵ���1
																																		��2�����descriptorCount ����1��pImmutableSamplers ����ΪNULL
				5.���descriptorCount ��Ϊ0��stageFlags ����ΪVK_SHADER_STAGE_ALL ������Ч��VkShaderStageFlagBits ���ֵ
				6.���descriptorType ΪVK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT��descriptorCount ��Ϊ0����stageFlags ����Ϊ0���� VK_SHADER_STAGE_FRAGMENT_BIT
				7.pImmutableSamplers ָ����sampler�����borderColor ����VK_BORDER_COLOR_FLOAT_CUSTOM_EXT ��VK_BORDER_COLOR_INT_CUSTOM_EXT 
				8.���descriptorType ΪVK_DESCRIPTOR_TYPE_MUTABLE_EXT����pImmutableSamplers ����ΪNULL
				9.��� VkDescriptorSetLayoutCreateInfo::flags ����VK_DESCRIPTOR_SET_LAYOUT_CREATE_PER_STAGE_BIT_NV����descriptorCount ��Ϊ0����stageFlags ������ VK_SHADER_STAGE_VERTEX_BIT, VK_SHADER_STAGE_TESSELLATION_CONTROL_BIT, VK_SHADER_STAGE_TESSELLATION_EVALUATION_BIT,
													VK_SHADER_STAGE_GEOMETRY_BIT, VK_SHADER_STAGE_FRAGMENT_BIT �� VK_SHADER_STAGE_COMPUTE_BIT ����Ч�����ֵ

				*/
			
			}
		descriptorSetLayoutCreateInfo.pBindings = &descriptorBinding;//��һ�� VkDescriptorSetLayoutBinding�������ַ
		/*
		VkDescriptorSetLayoutCreateInfo��Ч�÷�:
		1.���perStageDescriptorSet ����û�п���������flagsû�а���VK_DESCRIPTOR_SET_LAYOUT_CREATE_PER_STAGE_BIT_NV����pBindings�е�ÿ��Ԫ�ص�VkDescriptorSetLayoutBinding::binding��Ա�����в�ͬ��ֵ
		2.���flags����	VK_DESCRIPTOR_SET_LAYOUT_CREATE_PUSH_DESCRIPTOR_BIT_KHR����pBindings ������Ԫ�ز����� descriptorType ���� VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC �� VK_DESCRIPTOR_TYPE_STORAGE_BUFFER_DYNAMIC
		3.���flags���� VK_DESCRIPTOR_SET_LAYOUT_CREATE_PUSH_DESCRIPTOR_BIT_KHR����1��pBindings ������Ԫ�ز����� descriptorType ���� VK_DESCRIPTOR_TYPE_INLINE_UNIFORM_BLOCK
																				   ��2��pBindings ������Ԫ����descriptor�����ܺͲ��ܳ��� VkPhysicalDevicePushDescriptorPropertiesKHR::maxPushDescriptors
																				   ��3��flags ���ܰ���VK_DESCRIPTOR_SET_LAYOUT_CREATE_HOST_ONLY_POOL_BIT_EXT
																				   ��4��pBindings�в��ܺ���descriptorType ΪVK_DESCRIPTOR_TYPE_MUTABLE_EXT ��Ԫ��
		4.����κ�binding����VK_DESCRIPTOR_BINDING_UPDATE_AFTER_BIND_BIT����1��flags ������� VK_DESCRIPTOR_SET_LAYOUT_CREATE_UPDATE_AFTER_BIND_POOL_BIT
																			��2������bindingԪ�ز����� descriptorType ���� VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC ����VK_DESCRIPTOR_TYPE_STORAGE_BUFFER_DYNAMIC
		5.���flags����VK_DESCRIPTOR_SET_LAYOUT_CREATE_UPDATE_AFTER_BIND_POOL_BIT����flags���ܰ���VK_DESCRIPTOR_SET_LAYOUT_CREATE_HOST_ONLY_POOL_BIT_EXT
		6.������pBindings[i]��descriptorType ���� VK_DESCRIPTOR_TYPE_MUTABLE_EXT����pNext�б��뺬��һ��mutableDescriptorTypeListCount ����i��VkMutableDescriptorTypeCreateInfoEXT
		7.���һ��binding��descriptorTypeΪVK_DESCRIPTOR_TYPE_MUTABLE_EXT����pImmutableSamplers ����ΪNULL
		8.���mutableDescriptorTypeFeaturesEXT::mutableDescriptorType ����û�п�������pBindings�в��ܺ���descriptorType ΪVK_DESCRIPTOR_TYPE_MUTABLE_EXT ��Ԫ��
		9.���flags����VK_DESCRIPTOR_SET_LAYOUT_CREATE_HOST_ONLY_POOL_BIT_EXT����VkPhysicalDeviceMutableDescriptorTypeFeaturesEXT::mutableDescriptorType ���뿪��
		10.���flags����VK_DESCRIPTOR_SET_LAYOUT_CREATE_DESCRIPTOR_BUFFER_BIT_EXT����pBindings ������Ԫ�ز����� descriptorType ���� VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC �� VK_DESCRIPTOR_TYPE_STORAGE_BUFFER_DYNAMIC
		11.���flags����VK_DESCRIPTOR_SET_LAYOUT_CREATE_EMBEDDED_IMMUTABLE_SAMPLERS_BIT_EXT����flags���ܰ���VK_DESCRIPTOR_SET_LAYOUT_CREATE_DESCRIPTOR_BUFFER_BIT_EXT
		12.���flags����VK_DESCRIPTOR_SET_LAYOUT_CREATE_DESCRIPTOR_BUFFER_BIT_EXT����flags���ܰ���VK_DESCRIPTOR_SET_LAYOUT_CREATE_UPDATE_AFTER_BIND_POOL_BIT��VK_DESCRIPTOR_SET_LAYOUT_CREATE_HOST_ONLY_POOL_BIT_VALVE
		13.���flags����VK_DESCRIPTOR_SET_LAYOUT_CREATE_PER_STAGE_BIT_NV����1��perStageDescriptorSet ���뿪��
																			��2��pBindings�в��ܺ���VkDescriptorSetLayoutBinding::binding��� �Լ�VkDescriptorSetLayoutBinding::stageFlags������ͬ����λ������Ԫ�� 

		*/


		//VkMutableDescriptorTypeCreateInfoEXT   �ȼ���VkMutableDescriptorTypeCreateInfoVALVE
		//ָ��mutable descriptor���ܵ�descriptor ����, VkDescriptorSetLayoutCreateInfo::pBindings[i] ʹ���о���VkMutableDescriptorTypeCreateInfoEXT::::pMutableDescriptorTypeLists[i]�е� descriptor����
		VkMutableDescriptorTypeCreateInfoEXT& mutableDescriptorTypeCreateInfoEXT = descriptorSetLayoutCreateInfoEXT.mutableDescriptorTypeCreateInfoEXT;
		mutableDescriptorTypeCreateInfoEXT.mutableDescriptorTypeListCount = 1;// pMutableDescriptorTypeLists��Ԫ��
			VkMutableDescriptorTypeListEXT mutableDescriptorTypeList{};//�ȼ���VkMutableDescriptorTypeListVALVE
			{
				mutableDescriptorTypeList.descriptorTypeCount = 0;//pDescriptorTypes��Ԫ�ظ���
				mutableDescriptorTypeList.pDescriptorTypes = VK_NULL_HANDLE;//��descriptorTypeCount�� VkDescriptorType�������ַ������һ�������İ�mutable descriptor���ܻ�ͻ��Ϊ��Щ���������͡�
				/*
				VkMutableDescriptorTypeListEXT��Ч�÷�:
				1.descriptorTypeCount ����Ϊ0�������Ӧ��binding ΪVK_DESCRIPTOR_TYPE_MUTABLE_EXT
				2.pDescriptorTypes ������һ����Ч��ָ�룬ָ��һ��descriptorTypeCount����Ч�ġ�Ψһ��VkDescriptorTypeֵ�����������binding��VK_DESCRIPTOR_TYPE_MUTABLE_EXT����
				3.descriptorTypeCount ����Ϊ0�������Ӧ��binding ��ΪVK_DESCRIPTOR_TYPE_MUTABLE_EXT
				4.pDescriptorTypes ���ܰ���VK_DESCRIPTOR_TYPE_MUTABLE_EXT��VK_DESCRIPTOR_TYPE_STORAGE_BUFFER_DYNAMIC��VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC ��VK_DESCRIPTOR_TYPE_INLINE_UNIFORM_BLOCK

				*/
			}
		mutableDescriptorTypeCreateInfoEXT.pMutableDescriptorTypeLists = &mutableDescriptorTypeList;//��һ�� VkMutableDescriptorTypeListEXT�������ַ


		//VkDescriptorSetLayoutBindingFlagsCreateInfo    ��ͬ��VkDescriptorSetLayoutBindingFlagsCreateInfoEXT
		//ָ������descriptor sets layout��ÿ��binding��flags   ���� VkDescriptorSetLayoutCreateInfo::pBindings[i] ʹ�� VkDescriptorSetLayoutBindingFlagsCreateInfo::pBindingFlags[i] �е�flags
		VkDescriptorSetLayoutBindingFlagsCreateInfo& bindingFlagsCreateInfo = descriptorSetLayoutCreateInfoEXT.descriptorSetLayoutBindingFlagsCreateInfo;
		bindingFlagsCreateInfo.pBindingFlags = (VkDescriptorBindingFlags*)VkDescriptorBindingFlagBits{ VK_DESCRIPTOR_BINDING_UPDATE_AFTER_BIND_BIT };/*��һ��VkDescriptorBindingFlagBits ���ֵ��λ�������飬����ָ��descriptor set layout��ÿ��binding��flags
		VkDescriptorBindingFlagBits ����ͬ��VkDescriptorBindingFlagBitsEXT��:

		VK_DESCRIPTOR_BINDING_UPDATE_AFTER_BIND_BIT:  ָ�����binding��descriptors �������descriptor set�󶨵�command buffer��command buffer�ύ������֮����и��¡�
		VK_DESCRIPTOR_BINDING_PARTIALLY_BOUND_BIT:  ָ�����binding��descriptors ���Ƕ�̬ʹ�õģ���ʹ��ʱ���binding���뺬����Ч��descriptors
		VK_DESCRIPTOR_BINDING_UPDATE_UNUSED_WHILE_PENDING_BIT:  ָ�����binding��descriptors ������command buffer�󶨸�descriptor set֮����£�������ʹ�ø�descriptor set��command buffer����pending execution�½��и��£������ڲ�ʹ�ø�descriptor set��command buffer����pending execution�½��и��¡�
		VK_DESCRIPTOR_BINDING_VARIABLE_DESCRIPTOR_COUNT_BIT:  ָ�����binding��descriptors ��һ���ɱ��С��descriptor binding�����С���ڷ���descriptor setʱָ����descriptorCount ����Ϊһ�����ޣ���ʵ�ʵ�descriptor��������С��������ޡ�

		������������������������ÿ��ö�����͵ĺ������������ֻ�о�����Ҫ����Ϣ��ʣ�µ���ϸ˵����p1261
		
		*/
		bindingFlagsCreateInfo.bindingCount = 1;//pBindingFlags �е�Ԫ�ظ���
		/*
		VkDescriptorSetLayoutBindingFlagsCreateInfo
		1.���bindingCount ����0��������VkDescriptorSetLayoutCreateInfo::bindingCount
		2.���VkDescriptorSetLayoutCreateInfo::flags ����VK_DESCRIPTOR_SET_LAYOUT_CREATE_PUSH_DESCRIPTOR_BIT_KHR����pBindingFlags �е�����Ԫ�ز��ܺ���VK_DESCRIPTOR_BINDING_UPDATE_AFTER_BIND_BIT��VK_DESCRIPTOR_BINDING_UPDATE_UNUSED_WHILE_PENDING_BIT��VK_DESCRIPTOR_BINDING_UPDATE_UNUSED_WHILE_PENDING_BIT ����VK_DESCRIPTOR_BINDING_VARIABLE_DESCRIPTOR_COUNT_BIT
		3.���pBindingFlags ��һ��Ԫ�ذ���VK_DESCRIPTOR_BINDING_VARIABLE_DESCRIPTOR_COUNT_BIT�������Ԫ�ص�binding �ű�����pBindings ��binding �ŵ����ֵ
		4.���VkPhysicalDeviceDescriptorIndexingFeatures::descriptorBindingUniformBufferUpdateAfterBind û�п�����������binding��descriptorTypeΪVK_DESCRIPTOR_TYPE_UNIFORM_BUFFER ����ʹ��VK_DESCRIPTOR_BINDING_UPDATE_AFTER_BIND_BIT
		5.���VkPhysicalDeviceDescriptorIndexingFeatures::descriptorBindingSampledImageUpdateAfterBind û�п�����������binding��descriptorTypeΪVK_DESCRIPTOR_TYPE_SAMPLER�� ����ΪVK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER ���� VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE
		6.���VkPhysicalDeviceDescriptorIndexingFeatures::descriptorBindingStorageImageUpdateAfterBind û�п�����������binding��descriptorTypeΪVK_DESCRIPTOR_TYPE_STORAGE_IMAGE �Ҳ���ʹ��VK_DESCRIPTOR_BINDING_UPDATE_AFTER_BIND_BIT
		7.���VkPhysicalDeviceDescriptorIndexingFeatures::descriptorBindingStorageBufferUpdateAfterBind û�п�����������binding��descriptorTypeΪVK_DESCRIPTOR_TYPE_STORAGE_BUFFER �Ҳ���ʹ��VK_DESCRIPTOR_BINDING_UPDATE_AFTER_BIND_BIT
		8.���VkPhysicalDeviceDescriptorIndexingFeatures::descriptorBindingUniformTexelBufferUpdateAfterBind û�п�����������binding��descriptorTypeΪVK_DESCRIPTOR_TYPE_UNIFORM_TEXEL_BUFFER �Ҳ���ʹ��VK_DESCRIPTOR_BINDING_UPDATE_AFTER_BIND_BIT
		9.���VkPhysicalDeviceDescriptorIndexingFeatures::descriptorBindingStorageTexelBufferUpdateAfterBind û�п�����������binding��descriptorTypeΪVK_DESCRIPTOR_TYPE_STORAGE_TEXEL_BUFFER �Ҳ���ʹ��VK_DESCRIPTOR_BINDING_UPDATE_AFTER_BIND_BIT
		10.���VkPhysicalDeviceInlineUniformBlockFeatures::descriptorBindingInlineUniformBlockUpdateAfterBind û�п�����������binding��descriptorTypeΪVK_DESCRIPTOR_TYPE_INLINE_UNIFORM_BLOCK �Ҳ���ʹ��VK_DESCRIPTOR_BINDING_UPDATE_AFTER_BIND_BIT
		11.���VkPhysicalDeviceAccelerationStructureFeaturesKHR::descriptorBindingAccelerationStructureUpdateAfterBind û�п�����������binding��descriptorTypeΪVK_DESCRIPTOR_TYPE_ACCELERATION_STRUCTURE_KHR ����VK_DESCRIPTOR_TYPE_ACCELERATION_STRUCTURE_NV  �Ҳ���ʹ��VK_DESCRIPTOR_BINDING_UPDATE_AFTER_BIND_BIT
		12.����ʹ��descriptor type ΪVK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT,VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC, ���� VK_DESCRIPTOR_TYPE_STORAGE_BUFFER_DYNAMIC��binding �Ҳ���ʹ��VK_DESCRIPTOR_BINDING_UPDATE_AFTER_BIND_BIT
		13.���VkPhysicalDeviceDescriptorIndexingFeatures::descriptorBindingUpdateUnusedWhilePending û�п�����������pBindingFlags��Ԫ�ز��ܺ���VK_DESCRIPTOR_BINDING_UPDATE_UNUSED_WHILE_PENDING_BIT
		14.���VkPhysicalDeviceDescriptorIndexingFeatures::descriptorBindingPartiallyBound û�п�����������pBindingFlags��Ԫ�ز��ܺ���VK_DESCRIPTOR_BINDING_PARTIALLY_BOUND_BIT
		15.���VkPhysicalDeviceDescriptorIndexingFeatures::descriptorBindingVariableDescriptorCount û�п�����������pBindingFlags��Ԫ�ز��ܺ���VK_DESCRIPTOR_BINDING_VARIABLE_DESCRIPTOR_COUNT_BIT
		16.���pBindingFlags ��һ��Ԫ�ذ���VK_DESCRIPTOR_BINDING_VARIABLE_DESCRIPTOR_COUNT_BIT�������Ԫ�ص�descriptorType ����ΪVK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC ����VK_DESCRIPTOR_TYPE_STORAGE_BUFFER_DYNAMIC

		*/



		//��ѯһ��descriptor set layout�Ƿ��ܹ�������,��Ҫ��ѯ��ԭ���p1263
		{
			VkDescriptorSetLayoutSupport support{};//��ͬ��VkDescriptorSetLayoutSupportKHR
			support.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_SUPPORT;
				VkDescriptorSetVariableDescriptorCountLayoutSupport variableSupport{};//��ͬ��VkDescriptorSetVariableDescriptorCountLayoutSupportEXT
				{
					variableSupport.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_VARIABLE_DESCRIPTOR_COUNT_LAYOUT_SUPPORT;
					variableSupport.pNext = nullptr;
					variableSupport.maxVariableDescriptorCount = 0;//ָʾ��layout����߱��binding��֧�ֵ����descriptor���������binding�ǿɱ��С�ġ����layout����߱��binding������������ΪVK_DESCRIPTOR_TYPE_INLINE_UNIFORM_BLOCK����ômaxVariableDescriptorCount��ʾbinding֧�ֵ�����ֽڴ�С�������binding��С�ɱ�ġ�
				}
			support.pNext = &variableSupport;//���԰���VkDescriptorSetVariableDescriptorCountLayoutSupport
			support.supported = VK_FALSE;//ָ�����descriptor set layout�Ƿ��ܹ��������ķ���ֵ

			//������vkGetDescriptorSetLayoutSupportKHR
			vkGetDescriptorSetLayoutSupport(device, & descriptorSetLayoutCreateInfo, & support);


		
		}


		//һЩbinding����ɫ��������������ʽ���£�  �����p1265
		/*
		//��������ɫ�����������µ�uniform������
		//
		// binding to a single sampled image descriptor in set 0
		//
		layout (set=0, binding=0) uniform texture2D mySampledImage;
		*/

		vkCreateDescriptorSetLayout(device, &descriptorSetLayoutCreateInfo, nullptr,&descriptorSetLayout);

		//����descriptor set layout
		vkDestroyDescriptorSetLayout(device, descriptorSetLayout, nullptr);//�������descriptor set layoutʱָ����VkAllocationCallbacks����������Ҫ�ṩһ�����ݵ�VkAllocationCallbacks�����������pAllocator��������ΪNULL��

	}


	//pipeline layout
	VkPipelineLayout pipelineLayout{};
	{
	/*
	��pipeline�з���descriptor setͨ��pipeline layout��descriptor set layout��push constant ranges���󶨵�һ���γ�һ�������ɹ�pipeline ���ʵ���������Դ����pipeline layout�����pipeline layout����ȷ��shader stage��shader resource֮��Ľӿ�
	*/
	
		VkDescriptorSetLayout validDescriptorSetLayout{};//����һ����Ч��VkDescriptorSetLayout
		VkPushConstantRange pushConstantRange{};//����һ����Ч��VkPushConstantRange
		pushConstantRange.offset = 0;//���ֽ�Ϊ��λ������Ϊ4�ı���������С�� VkPhysicalDeviceLimits::maxPushConstantsSize
		pushConstantRange.size = 1;//���ֽ�Ϊ��λ������Ϊ4�ı���
		pushConstantRange.stageFlags = VK_PIPELINE_STAGE_ALL_GRAPHICS_BIT;//��һ��stage��־���������˽�����һϵ��push constant����ɫ���׶Ρ����һ���ض��Ľ׶β������ڸ÷�Χ�У���ô����Ӧ����ɫ���׶η��ʸ����ͳ�����Χ�ĳ�Ա������δ�����ֵ��



		//һ��pipeline layout������ӵ�е�descriptor����������һЩ���ƣ������p1278  Pipeline Layout Resource Limits
		VkPipelineLayoutCreateInfo pipelineLayoutCreateInfo{};
		pipelineLayoutCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
		pipelineLayoutCreateInfo.pNext = nullptr;
		pipelineLayoutCreateInfo.flags = 0;/*�� VkPipelineLayoutCreateFlagBits ���ֵ��λ���룬ָ��pipeline layout������ѡ��
		VkPipelineLayoutCreateFlagBits:
		VK_PIPELINE_LAYOUT_CREATE_INDEPENDENT_SETS_BIT_EXT :  ָ��ʵ�ֱ��뱣֤���л���ȱʧ�ض�descriptor set�����Բ���Ӱ��pipeline layout���κ����ԡ������������pipeline librariesʱ���Բ��ô���һ����VK_PIPELINE_CREATE_LINK_TIME_OPTIMIZATION_BIT_EXT ���ܵ�descriptor set�е�һ���Ӽ�
		*/
		pipelineLayoutCreateInfo.setLayoutCount = 1;//pSetLayouts ��Ԫ�ظ���
		pipelineLayoutCreateInfo.pSetLayouts = &validDescriptorSetLayout;//��һ�� VkDescriptorSetLayout ���������ָ��
		pipelineLayoutCreateInfo.pushConstantRangeCount = 1;//pPushConstantRanges ��Ԫ�ظ���
		pipelineLayoutCreateInfo.pPushConstantRanges = &pushConstantRange;//��һ�� VkPushConstantRange ���������ָ�룬�������ڵ���pipeline layout�е�push constant range��pipeline layout ����������pipelineÿ��stage�ɷ��ʵ�push constant������
		/*
		VkPipelineLayoutCreateInfo��Ч�÷�:
		1.setLayoutCount ����С�ڵ���VkPhysicalDeviceLimits::maxBoundDescriptorSets
		2.������VK_DESCRIPTOR_SET_LAYOUT_CREATE_UPDATE_AFTER_BIND_POOL_BIT ������descriptor set layout ������descriptorType ΪVK_DESCRIPTOR_TYPE_SAMPLER ��VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER�Ŀɹ��κ�����shader stages����pSetLayouts��descriptor�����ܺͱ���С�ڵ��� VkPhysicalDeviceLimits::maxPerStageDescriptorSamplers
		3.������VK_DESCRIPTOR_SET_LAYOUT_CREATE_UPDATE_AFTER_BIND_POOL_BIT ������descriptor set layout ������descriptorType ΪVK_DESCRIPTOR_TYPE_UNIFORM_BUFFER ��VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC �Ŀɹ��κ�����shader stages����pSetLayouts��descriptor�����ܺͱ���С�ڵ��� VkPhysicalDeviceLimits::maxPerStageDescriptorUniformBuffers
		4.������VK_DESCRIPTOR_SET_LAYOUT_CREATE_UPDATE_AFTER_BIND_POOL_BIT ������descriptor set layout ������descriptorType ΪVK_DESCRIPTOR_TYPE_STORAGE_BUFFER ��VK_DESCRIPTOR_TYPE_STORAGE_BUFFER_DYNAMIC �Ŀɹ��κ�����shader stages����pSetLayouts��descriptor�����ܺͱ���С�ڵ��� VkPhysicalDeviceLimits::maxPerStageDescriptorStorageBuffers
		5.������VK_DESCRIPTOR_SET_LAYOUT_CREATE_UPDATE_AFTER_BIND_POOL_BIT ������descriptor set layout ������descriptorType ΪVK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE, VK_DESCRIPTOR_TYPE_SAMPLE_WEIGHT_IMAGE_QCOM, VK_DESCRIPTOR_TYPE_BLOCK_MATCH_IMAGE_QCOM, ��VK_DESCRIPTOR_TYPE_UNIFORM_TEXEL_BUFFER �Ŀɹ��κ�����shader stages����pSetLayouts��descriptor�����ܺͱ���С�ڵ��� VkPhysicalDeviceLimits::maxPerStageDescriptorSampledImages
		6.������VK_DESCRIPTOR_SET_LAYOUT_CREATE_UPDATE_AFTER_BIND_POOL_BIT ������descriptor set layout ������descriptorType ΪVK_DESCRIPTOR_TYPE_STORAGE_IMAGE ��VK_DESCRIPTOR_TYPE_STORAGE_TEXEL_BUFFER �Ŀɹ��κ�����shader stages����pSetLayouts��descriptor�����ܺͱ���С�ڵ��� VkPhysicalDeviceLimits::maxPerStageDescriptorStorageImages
		7.������VK_DESCRIPTOR_SET_LAYOUT_CREATE_UPDATE_AFTER_BIND_POOL_BIT ������descriptor set layout ������descriptorType ΪVK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT �Ŀɹ��κ�����shader stages����pSetLayouts��descriptor�����ܺͱ���С�ڵ��� VkPhysicalDeviceLimits::maxPerStageDescriptorInputAttachments
		8.������VK_DESCRIPTOR_SET_LAYOUT_CREATE_UPDATE_AFTER_BIND_POOL_BIT ������descriptor set layout ������descriptorType ΪVK_DESCRIPTOR_TYPE_INLINE_UNIFORM_BLOCK �Ŀɹ��κ�����shader stages����pSetLayouts��descriptor�����ܺͱ���С�ڵ��� VkPhysicalDeviceInlineUniformBlockProperties::maxPerStageDescriptorInlineUniformBlocks
		9.����descriptorType ΪVK_DESCRIPTOR_TYPE_SAMPLER �Լ�VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER �Ŀɹ��κ�����shader stages����pSetLayouts��descriptor�����ܺͱ���С�ڵ��� VkPhysicalDeviceDescriptorIndexingProperties::maxPerStageDescriptorUpdateAfterBindSamp
		10.����descriptorType ΪVK_DESCRIPTOR_TYPE_UNIFORM_BUFFER �Լ�VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC �Ŀɹ��κ�����shader stages����pSetLayouts��descriptor�����ܺͱ���С�ڵ��� VkPhysicalDeviceDescriptorIndexingProperties::maxPerStageDescriptorUpdateAfterBindUniformBuffers
		11.����descriptorType ΪVK_DESCRIPTOR_TYPE_STORAGE_BUFFER �Լ�VK_DESCRIPTOR_TYPE_STORAGE_BUFFER_DYNAMIC �Ŀɹ��κ�����shader stages����pSetLayouts��descriptor�����ܺͱ���С�ڵ��� VkPhysicalDeviceDescriptorIndexingProperties::maxPerStageDescriptorUpdateAfterBindStorageBuffers
		12.����descriptorType ΪVK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE, ��VK_DESCRIPTOR_TYPE_UNIFORM_TEXEL_BUFFER �Ŀɹ��κ�����shader stages����pSetLayouts��descriptor�����ܺͱ���С�ڵ��� VkPhysicalDeviceDescriptorIndexingProperties::maxPerStageDescriptorUpdateAfterBindSampledImages
		13.����descriptorType ΪVK_DESCRIPTOR_TYPE_STORAGE_IMAGE �Լ�VK_DESCRIPTOR_TYPE_STORAGE_TEXEL_BUFFER �Ŀɹ��κ�����shader stages����pSetLayouts��descriptor�����ܺͱ���С�ڵ��� VkPhysicalDeviceDescriptorIndexingProperties::maxPerStageDescriptorUpdateAfterBindStorageImages
		14.����descriptorType ΪVK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT �Ŀɹ��κ�����shader stages����pSetLayouts��descriptor�����ܺͱ���С�ڵ��� VkPhysicalDeviceDescriptorIndexingProperties::maxPerStageDescriptorUpdateAfterBindInputAttachments
		15.����descriptorType ΪVK_DESCRIPTOR_TYPE_INLINE_UNIFORM_BLOCK �Ŀɹ��κ�����shader stages����pSetLayouts��descriptor�����ܺͱ���С�ڵ��� VkPhysicalDeviceInlineUniformBlockProperties::maxPerStageDescriptorUpdateAfterBindInlineUniformBlocks
		16.������VK_DESCRIPTOR_SET_LAYOUT_CREATE_UPDATE_AFTER_BIND_POOL_BIT ������descriptor set layout ������descriptorType ΪVK_DESCRIPTOR_TYPE_SAMPLER �� VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER �Ŀɹ��κ�����shader stages����pSetLayouts��descriptor�����ܺͱ���С�ڵ���VkPhysicalDeviceLimits::maxDescriptorSetSamplers
		18.������VK_DESCRIPTOR_SET_LAYOUT_CREATE_UPDATE_AFTER_BIND_POOL_BIT ������descriptor set layout ������descriptorType ΪVK_DESCRIPTOR_TYPE_UNIFORM_BUFFER �Ŀɹ��κ�����shader stages����pSetLayouts��descriptor�����ܺͱ���С�ڵ��� VkPhysicalDeviceLimits::maxDescriptorSetUniformBuffers
		19.������VK_DESCRIPTOR_SET_LAYOUT_CREATE_UPDATE_AFTER_BIND_POOL_BIT ������descriptor set layout ������descriptorType ΪVK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC �Ŀɹ��κ�����shader stages����pSetLayouts��descriptor�����ܺͱ���С�ڵ��� VkPhysicalDeviceLimits::maxDescriptorSetUniformBuffersDynamic
		20.������VK_DESCRIPTOR_SET_LAYOUT_CREATE_UPDATE_AFTER_BIND_POOL_BIT ������descriptor set layout ������descriptorType ΪVK_DESCRIPTOR_TYPE_STORAGE_BUFFER �Ŀɹ��κ�����shader stages����pSetLayouts��descriptor�����ܺͱ���С�ڵ��� VkPhysicalDeviceLimits::maxDescriptorSetStorageBuffers
		21.������VK_DESCRIPTOR_SET_LAYOUT_CREATE_UPDATE_AFTER_BIND_POOL_BIT ������descriptor set layout ������descriptorType ΪVK_DESCRIPTOR_TYPE_STORAGE_BUFFER_DYNAMIC �Ŀɹ��κ�����shader stages����pSetLayouts��descriptor�����ܺͱ���С�ڵ��� VkPhysicalDeviceLimits::maxDescriptorSetStorageBuffersDynamic
		22.������VK_DESCRIPTOR_SET_LAYOUT_CREATE_UPDATE_AFTER_BIND_POOL_BIT ������descriptor set layout ������descriptorType ΪVK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER ��VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE ��VK_DESCRIPTOR_TYPE_UNIFORM_TEXEL_BUFFER  �Ŀɹ��κ�����shader stages����pSetLayouts��descriptor�����ܺͱ���С�ڵ��� VkPhysicalDeviceLimits::maxDescriptorSetSampledImages
		23.������VK_DESCRIPTOR_SET_LAYOUT_CREATE_UPDATE_AFTER_BIND_POOL_BIT ������descriptor set layout ������descriptorType ΪVK_DESCRIPTOR_TYPE_STORAGE_IMAGE ��VK_DESCRIPTOR_TYPE_STORAGE_TEXEL_BUFFER �Ŀɹ��κ�����shader stages����pSetLayouts��descriptor�����ܺͱ���С�ڵ��� VkPhysicalDeviceLimits::maxDescriptorSetStorageImages
		24.������VK_DESCRIPTOR_SET_LAYOUT_CREATE_UPDATE_AFTER_BIND_POOL_BIT ������descriptor set layout ������descriptorType ΪVK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT �Ŀɹ��κ�����shader stages����pSetLayouts��descriptor�����ܺͱ���С�ڵ��� VkPhysicalDeviceLimits::maxDescriptorSetInputAttachments
		25.������VK_DESCRIPTOR_SET_LAYOUT_CREATE_UPDATE_AFTER_BIND_POOL_BIT ������descriptor set layout ������descriptorType ΪVK_DESCRIPTOR_TYPE_INLINE_UNIFORM_BLOCK �Ŀɹ��κ�����shader stages����pSetLayouts��binding�����ܺͱ���С�ڵ��� VkPhysicalDeviceInlineUniformBlockProperties::maxDescriptorSetInlineUniformBlocks
		26.����descriptorType ΪVK_DESCRIPTOR_TYPE_SAMPLER ��VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER �Ŀɹ�����shader stages����pSetLayouts��descriptor�����ܺͱ���С�ڵ��� VkPhysicalDeviceDescriptorIndexingProperties::maxDescriptorSetUpdateAfterBindSamplers
		27.����descriptorType ΪVK_DESCRIPTOR_TYPE_UNIFORM_BUFFER �Ŀɹ�����shader stages����pSetLayouts��descriptor�����ܺͱ���С�ڵ��� VkPhysicalDeviceDescriptorIndexingProperties::maxDescriptorSetUpdateAfterBindUniformBuffers
		28.����descriptorType ΪVK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC �Ŀɹ�����shader stages����pSetLayouts��descriptor�����ܺͱ���С�ڵ��� VkPhysicalDeviceDescriptorIndexingProperties::maxDescriptorSetUpdateAfterBindUniformBuffersDynamic
		29.����descriptorType ΪVK_DESCRIPTOR_TYPE_STORAGE_BUFFER �Ŀɹ�����shader stages����pSetLayouts��descriptor�����ܺͱ���С�ڵ��� VkPhysicalDeviceDescriptorIndexingProperties::maxDescriptorSetUpdateAfterBindStorageBuffers
		30.����descriptorType ΪVK_DESCRIPTOR_TYPE_STORAGE_BUFFER_DYNAMIC �Ŀɹ�����shader stages����pSetLayouts��descriptor�����ܺͱ���С�ڵ��� VkPhysicalDeviceDescriptorIndexingProperties::maxDescriptorSetUpdateAfterBindStorageBuffersDynamic
		31.����descriptorType ΪVK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER��VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE ��VK_DESCRIPTOR_TYPE_UNIFORM_TEXEL_BUFFER �Ŀɹ�����shader stages����pSetLayouts��descriptor�����ܺͱ���С�ڵ��� VkPhysicalDeviceDescriptorIndexingProperties::maxDescriptorSetUpdateAfterBindSampledImages
		32.����descriptorType ΪVK_DESCRIPTOR_TYPE_STORAGE_IMAGE ��VK_DESCRIPTOR_TYPE_STORAGE_TEXEL_BUFFER �Ŀɹ�����shader stages����pSetLayouts��descriptor�����ܺͱ���С�ڵ��� VkPhysicalDeviceDescriptorIndexingProperties::maxDescriptorSetUpdateAfterBindStorageImages
		33.����descriptorType ΪVK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT �Ŀɹ�����shader stages����pSetLayouts��descriptor�����ܺͱ���С�ڵ��� VkPhysicalDeviceDescriptorIndexingProperties::maxDescriptorSetUpdateAfterBindInputAttachments
		34.����descriptorType ΪVK_DESCRIPTOR_TYPE_INLINE_UNIFORM_BLOCK �Ŀɹ�����shader stages����pSetLayouts��binding�����ܺͱ���С�ڵ��� VkPhysicalDeviceInlineUniformBlockProperties::maxDescriptorSetUpdateAfterBindInlineUniformBlocks
		35.����descriptorType ΪVK_DESCRIPTOR_TYPE_INLINE_UNIFORM_BLOCK �Ŀɹ�����shader stages����pSetLayouts��descriptors�����ܺͱ���С�ڵ��� VkPhysicalDeviceVulkan13Properties::maxInlineUniformTotalSize
		36.�κ�pPushConstantRanges �е�����Ԫ�ص�stageFlags���ܺ�����ͬ��stage
		37.pSetLayout���ܺ��г���һ��VK_DESCRIPTOR_SET_LAYOUT_CREATE_PUSH_DESCRIPTOR_BIT_KHR������descriptor set layout
		38.������VK_DESCRIPTOR_SET_LAYOUT_CREATE_UPDATE_AFTER_BIND_POOL_BIT ������descriptor set layout ������descriptorType ΪVK_DESCRIPTOR_TYPE_ACCELERATION_STRUCTURE_KHR �Ŀɹ��κ�����shader stages����pSetLayouts��binding�����ܺͱ���С�ڵ��� VkPhysicalDeviceAccelerationStructurePropertiesKHR::maxPerStageDescriptorAccelerationStructures
		39.����descriptorType ΪVK_DESCRIPTOR_TYPE_ACCELERATION_STRUCTURE_KHR �Ŀɹ��κ�����shader stages����pSetLayouts��binding�����ܺͱ���С�ڵ��� VkPhysicalDeviceAccelerationStructurePropertiesKHR::maxPerStageDescriptorUpdateAfterBindAccelerationStructures
		39.������VK_DESCRIPTOR_SET_LAYOUT_CREATE_UPDATE_AFTER_BIND_POOL_BIT ������descriptor set layout ������descriptorType ΪVK_DESCRIPTOR_TYPE_ACCELERATION_STRUCTURE_KHR �Ŀɹ�����shader stages����pSetLayouts��binding�����ܺͱ���С�ڵ��� VkPhysicalDeviceAccelerationStructurePropertiesKHR::maxDescriptorSetAccelerationStructures
		40.����descriptorType ΪVK_DESCRIPTOR_TYPE_ACCELERATION_STRUCTURE_KHR �Ŀɹ��κ�����shader stages����pSetLayouts��binding�����ܺͱ���С�ڵ��� VkPhysicalDeviceAccelerationStructurePropertiesKHR::maxDescriptorSetUpdateAfterBindA
		41.����descriptorType ΪVK_DESCRIPTOR_TYPE_ACCELERATION_STRUCTURE_NV �Ŀɹ�����shader stages����pSetLayouts��binding�����ܺͱ���С�ڵ��� VkPhysicalDeviceRayTracingPropertiesNV::maxDescriptorSetAccelerationStructures
		42.pImmutableSamplers ����VK_SAMPLER_CREATE_SUBSAMPLED_BIT_EXT ����VK_SAMPLER_CREATE_SUBSAMPLED_COARSE_RECONSTRUCTION_BIT_EXT ��������shader stages�Լ�����pSetLayouts�е�sampler �����ܺͱ���С�ڵ��� VkPhysicalDeviceFragmentDensityMap2PropertiesEXT::maxDescriptorSetSubsampledSamplers
		43.pSetLayouts �е��κ�Ԫ�ز�����VK_DESCRIPTOR_SET_LAYOUT_CREATE_HOST_ONLY_POOL_BIT_EXT ����
		44.���graphicsPipelineLibrary δ���ã�pSetLayouts �е�ÿ��Ԫ�ر�������Ч��VkDescriptorSetLayout����
		45.���pSetLayouts �е��κ�Ԫ����VK_DESCRIPTOR_SET_LAYOUT_CREATE_DESCRIPTOR_BUFFER_BIT_EXT ��������pSetLayouts �е�����Ԫ�ر�����VK_DESCRIPTOR_SET_LAYOUT_CREATE_DESCRIPTOR_BUFFER_BIT_EXT ����

		*/



		vkCreatePipelineLayout(device, &pipelineLayoutCreateInfo, nullptr, &pipelineLayout);
	

		vkDestroyPipelineLayout(device, pipelineLayout, nullptr);

	}


	//Pipeline Layout Compatibility ��p1280
	//��Ҫ��Ϊ���ڰ�pipelineʱ���Լ���ʹ���Ѿ��󶨵�pipelineLayout�����������´���pipelineLayout���Ӷ����Ч�ʡ��������°���pipeline���pipelineLayout�е�descriptor Set�Ƿ�Ե�ǰpipeline��Ч����Ҫ��pipelineLayout�ļ�����


	// Allocation of Descriptor Sets ����descriptor set
	{
		//descriptor pool����һ��descriptors��descriptor sets���Դ��н��з���
		//��ϸ��Ϣ��p1284
		VkDescriptorPool descriptorPool{};
		VkDescriptorPoolCreateInfo descriptorPoolCreateInfo{};
		descriptorPoolCreateInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
			DescriptorPoolCreateInfoEXT descriptorPoolCreateInfoEXT{};
		descriptorPoolCreateInfo.pNext = &descriptorPoolCreateInfoEXT.descriptorPoolInlineUniformBlockCreateInfo;//���Ժ��� VkDescriptorPoolInlineUniformBlockCreateInfo ���� VkMutableDescriptorTypeCreateInfoEXT
		descriptorPoolCreateInfo.flags = VK_DESCRIPTOR_POOL_CREATE_UPDATE_AFTER_BIND_BIT;//�� VkDescriptorPoolCreateFlagBits ���ֵ��λ���룬ָ��pool��֧�ֵ��ض���ѡ�� 
		/*
		VkDescriptorPoolCreateFlagBits:
		VK_DESCRIPTOR_POOL_CREATE_FREE_DESCRIPTOR_SET_BIT : ָ���ͷ�descriptor sets�ķ����Ƕ����ģ�������ʹ��vkAllocateDescriptorSets��vkFreeDescriptorSets��vkResetDescriptorPool������ֻ��ʹ��vkAllocateDescriptorSets�Լ�vkResetDescriptorPool
		VK_DESCRIPTOR_POOL_CREATE_UPDATE_AFTER_BIND_BIT:  ָ�����pool�Ϸ����descriptor set���Ժ��а���VK_DESCRIPTOR_BINDING_UPDATE_AFTER_BIND_BIT��binding���Ӻ���VK_DESCRIPTOR_POOL_CREATE_UPDATE_AFTER_BIND_BIT������pool�Ϸ���һ����binding����VK_DESCRIPTOR_BINDING_UPDATE_AFTER_BIND_BIT ��descriptor set����Ч��
		VK_DESCRIPTOR_POOL_CREATE_HOST_ONLY_BIT_EXT:  ָ�����pool�Ϸ����descriptor setֻ���������ڴ��з��䣬���Ҳ��ܱ��󶨡������ڲ����иñ�־�����descriptor sets��Ӧ�ó�����������pool�����descriptor sets����п��������������pool�з����descriptor sets���ֵ��������vkUpdateDescriptorSetWithTemplateKHR��vkUpdateDescriptorSets�е��ⲿͬ��Ҫ��descriptor sets����descriptor�����ڲ�ͬ���߳���ͬʱ���£�������ͬ��descriptor���ܱ������߳�ͬʱ���¡�
		VK_DESCRIPTOR_POOL_CREATE_ALLOW_OVERALLOCATION_SETS_BIT_NV:  ָ��ʵ��Ӧ������Ӧ�ôӸ�pool�з��䳬��VkDescriptorPoolCreateInfo::maxSets ��descriptor set��ʵ��Ӧ��ʹ��maxSets �������ʼ��descriptor set����maxSets ����ָ��Ϊ0
		VK_DESCRIPTOR_POOL_CREATE_ALLOW_OVERALLOCATION_POOLS_BIT_NV:  ָ��ʵ��Ӧ������pool���䳬���κ�VkDescriptorPoolCreateInfo::poolSizeCount�Լ�VkDescriptorPoolCreateInfo::pPoolSizesָ����Ԫ����VkDescriptorPoolSize::descriptorCount��descriptor,ʵ�ֽ���ÿ��descriptor type��descriptorCount �����ʼ��descriptor set����poolSizeCount ����ָ��Ϊ0��pPoolSizes��Ԫ�ص�descriptorCount ����ָ��Ϊ0

		*/
		descriptorPoolCreateInfo.poolSizeCount = 1;// pPoolSizes��Ԫ�ظ���
			VkDescriptorPoolSize descriptorPoolSize{};
			{
				descriptorPoolSize.descriptorCount = 1;//������Ϳ��Է����descriptor�������������0�����typeΪVK_DESCRIPTOR_TYPE_INLINE_UNIFORM_BLOCK����descriptorCountΪ������Ϳ��Է�����ֽ������ұ�����4�ı���
				descriptorPoolSize.type = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;//descriptor����
			}

		descriptorPoolCreateInfo.pPoolSizes = &descriptorPoolSize;//һ��VkDescriptorPoolSize ������ָ�룬ÿһ��Ԫ��������pool�п��Է����descriptor�����ͺ�����
		descriptorPoolCreateInfo.maxSets = 1;//�Ǵ����pool���ܹ������descriptor set���������
		/*
		VkDescriptorPoolCreateInfo��Ч�÷�:
		1.���descriptorPoolOverallocation ����û�п���������flags������VK_DESCRIPTOR_POOL_CREATE_ALLOW_OVERALLOCATION_SETS_BIT_NV����maxSets �������0
		2.���flags����VK_DESCRIPTOR_POOL_CREATE_ALLOW_OVERALLOCATION_SETS_BIT_NV����VK_DESCRIPTOR_POOL_CREATE_ALLOW_OVERALLOCATION_POOLS_BIT_NV ����descriptorPoolOverallocation ���Ա��뿪��
		3.���flags����VK_DESCRIPTOR_POOL_CREATE_HOST_ONLY_BIT_EXT����Ͳ��ܰ���VK_DESCRIPTOR_POOL_CREATE_UPDATE_AFTER_BIND_BIT
		4.���VkPhysicalDeviceMutableDescriptorTypeFeaturesEXT::mutableDescriptorType û�п�������pPoolSizes �в��ܰ���descriptorTypeΪ VK_DESCRIPTOR_TYPE_MUTABLE_EXT��Ԫ��
		5.���flags����VK_DESCRIPTOR_POOL_CREATE_HOST_ONLY_BIT_EXT����VkPhysicalDeviceMutableDescriptorTypeFeaturesEXT::mutableDescriptorType ���뿪��
		6.���pPoolSizes ����descriptorType ΪVK_DESCRIPTOR_TYPE_MUTABLE_EXT ��Ԫ�أ���pPoolSizes���κ���������VK_DESCRIPTOR_TYPE_MUTABLE_EXT��Ԫ����descriptor set֧�ֵ�descriptor ���Ͳ������Ԫ�ص�descriptor set֧�ֵ�descriptor ���Ͳ����ص�
		7.���pPoolSizes ����descriptorType ΪVK_DESCRIPTOR_TYPE_INLINE_UNIFORM_BLOCK ��Ԫ�أ���pNext�б������һ��maxInlineUniformBlockBindings ��Ϊ0��VkDescriptorPoolInlineUniformBlockCreateInfo�ṹ��

		*/


		//VkDescriptorPoolInlineUniformBlockCreateInfo    ��ͬ��VkDescriptorPoolInlineUniformBlockCreateInfoEXT
		//Ϊ�˴������� inline uniform block binding��descriptor set����Ҫ��VkDescriptorPoolCreateInfo��pNext�а���VkDescriptorPoolInlineUniformBlockCreateInfo�ṹ����ָ��descriptor pool��inline uniform block binding ����
		VkDescriptorPoolInlineUniformBlockCreateInfo& inlineUniformBlockCreateInfo = descriptorPoolCreateInfoEXT.descriptorPoolInlineUniformBlockCreateInfo;
		inlineUniformBlockCreateInfo.maxInlineUniformBlockBindings = 1;//inline uniform block binding���������



		vkCreateDescriptorPool(device, &descriptorPoolCreateInfo, nullptr, &descriptorPool);


		vkDestroyDescriptorPool(device, descriptorPool, nullptr);/*
		vkDestroyDescriptorPool��Ч�÷�:
		1.���õ���descriptorPool��ͨ���κη����descriptor sets�����Ѿ��ύ��command buffer�����Ѿ����ִ��
		2.�������descriptorPool �ṩ��VkAllocationCallbacks����������Ҫ�ṩһ�����ݵ�VkAllocationCallbacks����������ΪNULL

		*/

		VkDescriptorSetAllocateInfo descriptorSetAllocateInfo{};
		descriptorSetAllocateInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
		VkDescriptorSetVariableDescriptorCountAllocateInfo descriptorSetVariableDescriptorCountAllocateInfo{};//ָ�� variable-sized descriptor bindings�е�һ��descriptor count��ÿ���ṹ���Ӧһ��descriptor set���ȼ���VkDescriptorSetVariableDescriptorCountAllocateInfoEXT
		{
			descriptorSetVariableDescriptorCountAllocateInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_VARIABLE_DESCRIPTOR_COUNT_ALLOCATE_INFO;
			descriptorSetVariableDescriptorCountAllocateInfo.pNext = nullptr;
			descriptorSetVariableDescriptorCountAllocateInfo.descriptorSetCount = 1;//pDescriptorCounts �е�Ԫ�ظ����������Ϊ0��������VkDescriptorSetAllocateInfo::descriptorSetCount
				uint32_t descriptorCount = 10;//ÿһ��descriptor set��variable descriptor count
			descriptorSetVariableDescriptorCountAllocateInfo.pDescriptorCounts = &descriptorCount;//Ϊ����descriptor set��ÿ�� variable-sized descriptor binding �ϵ�descriptor ����������ָ��
		}

		descriptorSetAllocateInfo.pNext = &descriptorSetVariableDescriptorCountAllocateInfo;//���Ժ���һ��VkDescriptorSetVariableDescriptorCountAllocateInfo
		descriptorSetAllocateInfo.descriptorPool = VkDescriptorPool{/*��������һ����Ч��VkDescriptorPool*/ };//ָ��descriptor set���ĸ�pool�з���
		descriptorSetAllocateInfo.descriptorSetCount = 1;//Ҫ�����descriptor set������
		descriptorSetAllocateInfo.pSetLayouts = &descriptorSetLayout;//��һ��VkDescriptorSetLayout ������ָ�룬ÿһ��Ԫ��ָ��һ��descriptor set layout��������Ҫ����descriptor set�Ĳ���
		/*
		VkDescriptorSetAllocateInfo��Ч�÷�:
		1.���VK_KHR_maintenance1 ��չû�п�����VkPhysicalDeviceProperties::apiVersion С��Vulkan 1.1����1��descriptorSetCount ���ܴ���descriptorPool �пɷ����descriptor set����
																										 ��2��descriptorPool ��ʣ���descriptor capacity �����㹻����ָ��layout ��descriptor set��
		2.pSetLayouts��ÿ��Ԫ�ز�����VK_DESCRIPTOR_SET_LAYOUT_CREATE_PUSH_DESCRIPTOR_BIT_KHR ����
		3.���pSetLayouts ������Ԫ����VK_DESCRIPTOR_SET_LAYOUT_CREATE_UPDATE_AFTER_BIND_POOL_BIT ��������descriptorPool ������VK_DESCRIPTOR_POOL_CREATE_UPDATE_AFTER_BIND_BIT ����
		4.���pSetLayouts[i] ����pBindingFlags ����VK_DESCRIPTOR_BINDING_VARIABLE_DESCRIPTOR_COUNT_BIT������pNext�к���һ��descriptorSetCount ��Ϊ0��VkDescriptorSetVariableDescriptorCountAllocateInfo����VkDescriptorSetVariableDescriptorCountAllocateInfo::pDescriptorCounts[i]
																	��ֵ����С�ڻ����VkDescriptorSetLayoutBinding::descriptorCount ��Ӧ����pSetLayouts[i]��binding�ĵ�������
		5.���pSetLayouts ���κ�Ԫ����VK_DESCRIPTOR_SET_LAYOUT_CREATE_HOST_ONLY_POOL_BIT_EXT����descriptorPool ������VK_DESCRIPTOR_POOL_CREATE_HOST_ONLY_BIT_EXT ����
		6.pSetLayouts�е�ÿ��Ԫ�ز�����VK_DESCRIPTOR_SET_LAYOUT_CREATE_DESCRIPTOR_BUFFER_BIT_EXT ����

		*/


		VkDescriptorSet descriptorSet{};
		//����descriptor set
		vkAllocateDescriptorSets(device, &descriptorSetAllocateInfo, &descriptorSet);//�����p1290


		//�ͷ�descriptor set
		vkFreeDescriptorSets(device, descriptorPool, 1, &descriptorSet);/*
		vkFreeDescriptorSets��Ч�÷�:
		1.���õ�pDescriptorSets ���κ�Ԫ�ص��Ѿ��ύ��command buffer�����Ѿ����ִ��
		2.pDescriptorSets ������ descriptorSetCount ����Ч��VkDescriptorSet����VK_NULL_HANDLE
		3.descriptorPool ������VK_DESCRIPTOR_POOL_CREATE_FREE_DESCRIPTOR_SET_BIT����
		*/


		//��pool�Ϸ��������descriptor set���յ�pool�����ǵ����ͷ�һ��descriptor set
		vkResetDescriptorPool(device, descriptorPool, 0);/* �������õ�descriptorPool��ͨ���κη����descriptor sets���Ĳ��������Ѿ����   */

	}


	//Descriptor Set Updates ����descriptor set
	{

		//������descriptor set����ͨ��д����߿��������descriptor set�ĸ���

		//write  
		// VkWriteDescriptorSet�� pImageInfo, pBufferInfo, ���� pTexelBufferView������ֻʹ��һ�������߶���ʹ�ã��� VK_DESCRIPTOR_TYPE_INLINE_UNIFORM_BLOCK,VK_DESCRIPTOR_TYPE_ACCELERATION_STRUCTURE_KHR����VK_DESCRIPTOR_TYPE_ACCELERATION_STRUCTURE_NV�����
		//ʹ�� VkWriteDescriptorSetInlineUniformBlock�� VkWriteDescriptorSetAccelerationStructureKHR���� VkWriteDescriptorSetAccelerationStructureNV ��ָ����ز���
		VkWriteDescriptorSet writeDescriptorSet{};
		writeDescriptorSet.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
			WriteDescriptorSetEXT writeDescriptorSetEXT{};
		writeDescriptorSet.pNext = &writeDescriptorSetEXT.writeDescriptorSetAccelerationStructureKHR;
		writeDescriptorSet.descriptorCount = 1;//���binding�д�dstArrayElement��ʼҪ���µ�descriptor���������ͨ��dstSet��dstBinding ָ����binding��descriptorTypeΪ VK_DESCRIPTOR_TYPE_INLINE_UNIFORM_BLOCK�������ָ��Ϊ���binding��Ҫ���µ��ֽڴ�С������ΪpImageInfo�е�Ԫ�ظ����� pBufferInfo�е�Ԫ�ظ����� pTexelBufferView�е�Ԫ�ظ�����VkWriteDescriptorSetInlineUniformBlock.dataSize����VkWriteDescriptorSetAccelerationStructureKHR.accelerationStructureCount�е�һ��
		writeDescriptorSet.descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;/*��һ��VkDescriptorType ָ��pImageInfo, pBufferInfo, ���� pTexelBufferView�� descriptor�����ͣ����ͨ��dstSet��dstBinding ָ����binding��descriptorType��Ϊ VK_DESCRIPTOR_TYPE_MUTABLE_EXT����������ͱ��������ͬ
		VkDescriptorType:

        VK_DESCRIPTOR_TYPE_SAMPLER:  ָ��һ�� sampler descriptor.
        VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER:  ָ��һ�� combined image sampler descriptor.
        VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE:  ָ��һ�� sampled image descriptor.
        VK_DESCRIPTOR_TYPE_STORAGE_IMAGE:  ָ��һ�� storage image descriptor.
        VK_DESCRIPTOR_TYPE_UNIFORM_TEXEL_BUFFER:  ָ��һ�� uniform texel buffer descriptor.
        VK_DESCRIPTOR_TYPE_STORAGE_TEXEL_BUFFER:  ָ��һ�� storage texel buffer descriptor.
        VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER:  ָ��һ�� uniform buffer descriptor.
        VK_DESCRIPTOR_TYPE_STORAGE_BUFFER:  ָ��һ�� storage buffer descriptor.
        VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC:  ָ��һ�� dynamic uniform buffer descriptor.
        VK_DESCRIPTOR_TYPE_STORAGE_BUFFER_DYNAMIC:  ָ��һ�� dynamic storage buffer descriptor.
        VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT:  ָ��һ��n input attachment descriptor.
        VK_DESCRIPTOR_TYPE_INLINE_UNIFORM_BLOCK:  ָ��һ�� inline uniform block.
        VK_DESCRIPTOR_TYPE_MUTABLE_EXT:  ָ��һ�� descriptor of mutable type.
        VK_DESCRIPTOR_TYPE_SAMPLE_WEIGHT_IMAGE_QCOM:  ָ��һ�� sampled weight image descriptor.
        VK_DESCRIPTOR_TYPE_BLOCK_MATCH_IMAGE_QCOM:  ָ��һ�� block matching image descriptor.
		
		*/
		
		writeDescriptorSet.dstArrayElement = 0;//���binding��descriptor�����е���ʼԪ�أ����ͨ��dstSet��dstBinding ָ����binding��descriptorTypeΪ VK_DESCRIPTOR_TYPE_INLINE_UNIFORM_BLOCK�������ָ��Ϊ���binding�п�ʼ�ֽڵ�ƫ����
		writeDescriptorSet.dstBinding = 0;//Ҫ���µ�descriptor set�� descriptor binding
		writeDescriptorSet.dstSet = VkDescriptorSet{/*��������һ����Ч��VkDescriptorSet*/ };//Ҫ���µ�descriptor set
			VkDescriptorBufferInfo descriptorBufferInfo{};
			{
				descriptorBufferInfo.buffer = VkBuffer{/*��������һ����Ч��VkBuffer*/ };//ΪVK_NULL_HANDLE����ָ��buffer��Դ����� nullDescriptorû�п�������ΪVK_NULL_HANDLE�����ΪVK_NULL_HANDLE����offset����Ϊ0��range����ΪVK_WHOLE_SIZE
				descriptorBufferInfo.offset = 0;//ָ��buffer����ʼ�ֽ�ƫ������ͨ�����descriptor����buffer���������ƫ��������Ե�ַ���з��ʣ�����С��buffer�Ĵ�С
				descriptorBufferInfo.range = 1;//ָ�����descriptorҪ���µ�buffer���ֽ��������ΪVK_WHOLE_SIZE���ʾ��offset��ʼ��buffer�������������ΪVK_WHOLE_SIZE������Ч��Χ��offset�����������ܴ��� maxUniformBufferRange ���� maxStorageBufferRange����0 < range <= buffer��С - offset
			}
		writeDescriptorSet.pBufferInfo = &descriptorBufferInfo;//��һ��   VkDescriptorBufferInfo �������ַ
			VkDescriptorImageInfo descriptorImageInfo{};
			{
				descriptorImageInfo.sampler = VkSampler{/*��������һ����Ч��VkSampler*/ };//��һ��VkSampler�����ʹ����VK_DESCRIPTOR_TYPE_SAMPLER �Լ� VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER������û��ʹ��immutable samplers ��descriptor�ĸ�����
				descriptorImageInfo.imageView = VkImageView{/*��������һ����Ч��VkImageView*/ };//ΪVK_NULL_HANDLE����VkImageView�����ʹ����VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE, VK_DESCRIPTOR_TYPE_STORAGE_IMAGE, VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, �Լ� VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT ���͵�descriptor�ĸ�����
				descriptorImageInfo.imageLayout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;//����descriptor����ʱ��imageView���ʵ�image subresource��VkImageLayout���֣�����VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE, VK_DESCRIPTOR_TYPE_STORAGE_IMAGE, VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, �Լ� VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT���͵�descriptor�ĸ�����
				/*
				VkDescriptorImageInfo��Ч�÷�:
				1.imageView �����Ǵ�3D image�ϴ�����2D array image view
				2.���imageView �Ǵ�3D image�ϴ�����2D image view����1��descriptorType����Ϊ VK_DESCRIPTOR_TYPE_STORAGE_IMAGE, VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE, ���� VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER
																	 ��2��image������VK_IMAGE_CREATE_2D_VIEW_COMPATIBLE_BIT_EXT����
				3.���image2DViewOf3D ����û�п�������descriptorType ���� VK_DESCRIPTOR_TYPE_STORAGE_IMAGE��VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE ���� VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER����imageView �����Ǵ�3D image�ϴ�����2D image view
				
				4.���imageView��һ��depth/stencil image �ϴ���������������imageView��aspectMask �������VK_IMAGE_ASPECT_DEPTH_BIT ���� VK_IMAGE_ASPECT_STENCIL_BIT �е�һ��
				5.���imageLayout ΪVK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL������������imageView��aspectMask ���ܰ���VK_IMAGE_ASPECT_DEPTH_BIT ���� VK_IMAGE_ASPECT_STENCIL_BIT �е�һ��
				6.���imageLayout ΪVK_IMAGE_LAYOUT_DEPTH_READ_ONLY_STENCIL_ATTACHMENT_OPTIMAL,
									VK_IMAGE_LAYOUT_DEPTH_ATTACHMENT_STENCIL_READ_ONLY_OPTIMAL,
									VK_IMAGE_LAYOUT_DEPTH_READ_ONLY_OPTIMAL, VK_IMAGE_LAYOUT_DEPTH_ATTACHMENT_OPTIMAL,
									VK_IMAGE_LAYOUT_STENCIL_READ_ONLY_OPTIMAL, VK_IMAGE_LAYOUT_STENCIL_ATTACHMENT_OPTIMAL,
									VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL ����
									VK_IMAGE_LAYOUT_DEPTH_STENCIL_READ_ONLY_OPTIMAL������������imageView��aspectMask ���ܰ���VK_IMAGE_ASPECT_COLOR_BIT
				7.��descriptor���ʵ�ʱ�� imageLayout �����ʵ�ʵĴ�imageView�ɷ��ʵ�image subresource��VkImageLayout����ƥ�䣬�μ�ƥ����� image layout matching rules p1083
				8.���ʹ����sampler��image��VkFormat��һ��multi-planar format����image������VK_IMAGE_CREATE_MUTABLE_FORMAT_BIT��������imageView������aspectMask������һ����Ч��multi-planar aspect mask����λ
				9.���VK_KHR_portability_subset ��չ��������VkPhysicalDevicePortabilitySubsetFeaturesKHR::mutableComparisonSamplersΪ VK_FALSE����sampler������VkSamplerCreateInfo::compareEnable����ΪVK_FALSE����

				*/
			}
		writeDescriptorSet.pImageInfo = &descriptorImageInfo;//��һ�� VkDescriptorImageInfo �������ַ
			VkBufferView texelBufferView{};
		writeDescriptorSet.pTexelBufferView = &texelBufferView;//��һ��  VkBufferView �������ַ
		/*
		VkWriteDescriptorSet��Ч�÷�:
		1.dstBinding ����С�ڵ���dstSet�� descriptor set layout����ʱָ��������binding������
		2.dstBinding ������һ�����з�0descriptorCountֵ��binding
		3.����ͨ��������VkWriteDescriptorSet���µ�������binding��������ЩdescriptorCountΪ0��binding����Щbinding��������ͬ��descriptorType �Լ� stageFlags������ȫ��ʹ�û��߲�ʹ��immutable samplers
		4.descriptorType�����dstSet�е�dstBindingƥ��
		5.dstSet��������Ч�� VkDescriptorSet���
		6.dstArrayElement + descriptorCount����С�ڵ���dstBinding��ָ����descriptor������Ԫ�ص��������Լ�consecutive binding updates p1301������������binding�����п��õ�descriptor������
		7.���descriptorTypeΪVK_DESCRIPTOR_TYPE_INLINE_UNIFORM_BLOCK����dstArrayElement�Լ�descriptorCount ������4��������
		8.���descriptorTypeΪVK_DESCRIPTOR_TYPE_UNIFORM_TEXEL_BUFFER ����VK_DESCRIPTOR_TYPE_STORAGE_TEXEL_BUFFER����1��pTexelBufferView�е�Ԫ�ر�������Ч��VkBufferView�������VK_NULL_HANDLE
																													 ��2�����nullDescriptor ����û�п�������pTexelBufferView�е�ÿ��Ԫ�ؾͲ���ΪVK_NULL_HANDLE
		9.���descriptorTypeΪVK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, VK_DESCRIPTOR_TYPE_STORAGE_BUFFER, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC, ���� VK_DESCRIPTOR_TYPE_STORAGE_BUFFER_DYNAMIC��pBufferInfo ������descriptorCount����ЧVkDescriptorBufferInfo������ָ��
		10.���descriptorTypeΪVK_DESCRIPTOR_TYPE_SAMPLER ����VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER����dstSet����һ�� descriptorType���͵�dstBinding����immutable samplers��layout���䣬��pImageInfo�е�ÿ��Ԫ�ص�sampler������һ����Ч��VkSampler
		11.���descriptorTypeΪVK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER��VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE ����VK_DESCRIPTOR_TYPE_STORAGE_IMAGE����1��pImageInfo�е�Ԫ�ص�imageView ��������Ч��VkImageView����VK_NULL_HANDLE
																																				   ��2�����nullDescriptor����û�п�������pImageInfo�е�Ԫ�ص�imageView ����ΪVK_NULL_HANDLE
		12.���descriptorTypeΪVK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT����pImageInfo�е�Ԫ�ص�imageView ����ΪVK_NULL_HANDLE
		13.���descriptorTypeΪVK_DESCRIPTOR_TYPE_INLINE_UNIFORM_BLOCK����pNext�б������һ��dataSize ����descriptorCount��VkWriteDescriptorSetInlineUniformBlock
		14.���descriptorTypeΪVK_DESCRIPTOR_TYPE_ACCELERATION_STRUCTURE_KHR����pNext�б������һ��accelerationStructureCount ����descriptorCount��VkWriteDescriptorSetAccelerationStructureKHR
		15.���descriptorTypeΪVK_DESCRIPTOR_TYPE_ACCELERATION_STRUCTURE_NV����pNext�б������һ��accelerationStructureCount ����descriptorCount��VkWriteDescriptorSetAccelerationStructureNV
		16.���descriptorTypeΪVK_DESCRIPTOR_TYPE_SAMPLED_IMAGE����pImageInfo�е�Ԫ�ص�imageView ��������pNext����һ��VkSamplerYcbcrConversionInfo ���д���
		17.���descriptorTypeΪVK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER����1�����pImageInfo�е�Ԫ�ص�imageView ����pNext����һ��VkSamplerYcbcrConversionInfo ���д�������dstSet������dstBinding����immutable samplers��layout���д������Ҷ�Ӧ��immutable samplers �����VkSamplerYcbcrConversionInfo�ж������ͬ
																			��2�����dstSet����dstBinding����immutable samplers��layout���д�������pImageInfo �е�ÿ��Ԫ�صĶ�Ӧ��һ��������sampler Y��CBCR conversion��immutable sampler�� imageView �����Ժ���һ���Ͷ�Ӧimmutable sampler��ͬ�����VkSamplerYcbcrConversionInfo ���д���
																			��3�����dstSet��dstBinding����immutable samplers��layout���д���������Щsamplers������sampler Y��CBCR conversion����pImageInfo �е�ÿ��Ԫ�صĶ�Ӧ��һ��������sampler Y��CBCR conversion��immutable sampler�� imageView ���벻��ΪVK_NULL_HANDLE
		18.���descriptorTypeΪVK_DESCRIPTOR_TYPE_UNIFORM_BUFFER���� VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC����pBufferInfo��ÿ��Ԫ�ص� offset ����ΪVkPhysicalDeviceLimits::minUniformBufferOffsetAlignment�ı���
		19.���descriptorTypeΪVK_DESCRIPTOR_TYPE_STORAGE_BUFFER���� VK_DESCRIPTOR_TYPE_STORAGE_BUFFER_DYNAMIC����pBufferInfo��ÿ��Ԫ�ص� offset ����ΪVkPhysicalDeviceLimits::minStorageBufferOffsetAlignment�ı���
		20.���descriptorTypeΪVK_DESCRIPTOR_TYPE_UNIFORM_BUFFER��VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC��VK_DESCRIPTOR_TYPE_STORAGE_BUFFER���� VK_DESCRIPTOR_TYPE_STORAGE_BUFFER_DYNAMIC����pBufferInfo���κ�Ԫ�ص�bufferΪnon-sparse�ģ���buffer����󶨵�һ��������������������VkDeviceMemory��
		21.���descriptorTypeΪVK_DESCRIPTOR_TYPE_UNIFORM_BUFFER ���� VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC����pBufferInfo���κ�Ԫ�ص�buffer������VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT ����
		22.���descriptorTypeΪVK_DESCRIPTOR_TYPE_STORAGE_BUFFER ���� VK_DESCRIPTOR_TYPE_STORAGE_BUFFER_DYNAMIC����1��pBufferInfo���κ�Ԫ�ص�buffer������VK_BUFFER_USAGE_STORAGE_BUFFER_BIT ����
																												   ��2����pBufferInfo���κ�Ԫ�ص�range ����С�ڵ��� VkPhysicalDeviceLimits::maxUniformBufferRange������ΪVK_WHOLE_SIZE
		23.���descriptorTypeΪVK_DESCRIPTOR_TYPE_UNIFORM_BUFFER ���� VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC���ң�1��pBufferInfo���κ�Ԫ�ص�buffer������VK_BUFFER_USAGE_STORAGE_BUFFER_BIT ����
																												   ��2����pBufferInfo���κ�Ԫ�ص�range ����С�ڵ��� VkPhysicalDeviceLimits::maxStorageBufferRange������ΪVK_WHOLE_SIZE
		24.���descriptorTypeΪVK_DESCRIPTOR_TYPE_UNIFORM_TEXEL_BUFFER����pTexelBufferView ��Ԫ�ش������뺬��VK_BUFFER_USAGE_UNIFORM_TEXEL_BUFFER_BIT
		25.���descriptorTypeΪVK_DESCRIPTOR_TYPE_STORAGE_TEXEL_BUFFER����pTexelBufferView ��Ԫ�ش������뺬��VK_BUFFER_USAGE_STORAGE_TEXEL_BUFFER_BIT
		26.���descriptorTypeΪVK_DESCRIPTOR_TYPE_STORAGE_IMAGE ����VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT����pImageInfo��ÿ��Ԫ�ص�imageView ������identity swizzle ����
		27.���descriptorTypeΪVK_DESCRIPTOR_TYPE_SAMPLED_IMAGE ����VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER����pImageInfo��ÿ��Ԫ�ص�imageView ������VK_IMAGE_USAGE_SAMPLED_BIT ����
		28.���descriptorTypeΪVK_DESCRIPTOR_TYPE_SAMPLED_IMAGE����pImageInfo��ÿ��Ԫ�ص�imageLayout ������һ���о���Sampled Image p1243�е�Ԫ��
		29.���descriptorTypeΪVK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER����pImageInfo��ÿ��Ԫ�ص�imageLayout ������һ���о���Combined Image Sampler p1243�е�Ԫ��
		30.���descriptorTypeΪVK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT����1��pImageInfo��ÿ��Ԫ�ص�imageLayout ������һ���о���Input Attachment p1246�е�Ԫ��
																	  ��2��pImageInfo��ÿ��Ԫ�ص�imageView ������VK_IMAGE_USAGE_INPUT_ATTACHMENT_BIT����
		31.���descriptorTypeΪVK_DESCRIPTOR_TYPE_STORAGE_IMAGE����1��pImageInfo��ÿ��Ԫ�ص�imageLayout ������һ���о���Storage Image p1242�е�Ԫ��
																   ��2��pImageInfo��ÿ��Ԫ�ص�imageView ������VK_IMAGE_USAGE_STORAGE_BIT����
																   ��3��pImageInfo��ÿ��Ԫ�ص�imageView ��������pNext�в�����һ��VkImageViewMinLodCreateInfoEXT ���� ����һ��minLodΪ0��VkImageViewMinLodCreateInfoEXT ����
		32.���descriptorTypeΪVK_DESCRIPTOR_TYPE_SAMPLER����dstSet ������һ��dstBinding����immutable samplers ��layout����
		33.���dstSet��dstBinding���Ե�VkDescriptorSetLayoutBinding��VK_DESCRIPTOR_TYPE_MUTABLE_EXT���͵ģ����µļ����descriptorType �����о���dstBinding��Ӧ��pMutableDescriptorTypeLists��
		34.���descriptorTypeΪVK_DESCRIPTOR_TYPE_SAMPLE_WEIGHT_IMAGE_QCOM����1��pImageInfo��ÿ��Ԫ�ص�imageView ������VK_IMAGE_USAGE_SAMPLE_WEIGHT_BIT_QCOM ����
		35.���descriptorTypeΪVK_DESCRIPTOR_TYPE_BLOCK_MATCH_IMAGE_QCOM����1��pImageInfo��ÿ��Ԫ�ص�imageView ������VK_IMAGE_USAGE_SAMPLE_BLOCK_MATCH_BIT_QCOM ����

		*/


		//VkWriteDescriptorSetInlineUniformBlock
		//ָ��Ҫд�뵽descriptor set�����ݵ�descriptor����ΪVK_DESCRIPTOR_TYPE_INLINE_UNIFORM_BLOCK
		VkWriteDescriptorSetInlineUniformBlock& writeDescriptorSetInlineUniformBlock = writeDescriptorSetEXT.writeDescriptorSetInlineUniformBlock;
		writeDescriptorSetInlineUniformBlock.dataSize = 0;//ָ��pData��inline uniform block ���ݵ��ֽ���������Ϊ4�ı���
		writeDescriptorSetInlineUniformBlock.pData = nullptr;//Ҫд�뵽descriptor��inline uniform block ����


		//VkWriteDescriptorSetAccelerationStructureKHR
		VkWriteDescriptorSetAccelerationStructureKHR& writeDescriptorSetAccelerationStructureKHR = writeDescriptorSetEXT.writeDescriptorSetAccelerationStructureKHR;
		writeDescriptorSetAccelerationStructureKHR.accelerationStructureCount = 0;//��pAccelerationStructures�м��ٽṹԪ�ظ���
		writeDescriptorSetAccelerationStructureKHR.pAccelerationStructures = VK_NULL_HANDLE;//��һ��VkAccelerationStructureKHR ������ָ�룬ָ��Ҫ���µļ��ٽṹ
		/*
		VkWriteDescriptorSetAccelerationStructureKHR��Ч�÷�:
		1.accelerationStructureCount ������ڱ���չ��VkWriteDescriptorSet��descriptorCount
		2.pAccelerationStructures��ÿ�����ٽṹ������VK_ACCELERATION_STRUCTURE_TYPE_TOP_LEVEL_KHR ����VK_ACCELERATION_STRUCTURE_TYPE_GENERIC_KHR���ʹ���
		3.���nullDescriptor ����û�п�������pAccelerationStructures�е�ÿ��Ԫ�ز���ΪVK_NULL_HANDLE
		*/

		//VkWriteDescriptorSetAccelerationStructureNV
		VkWriteDescriptorSetAccelerationStructureNV& writeDescriptorSetAccelerationStructureNV = writeDescriptorSetEXT.writeDescriptorSetAccelerationStructureNV;
		writeDescriptorSetAccelerationStructureNV.accelerationStructureCount = 0;//��pAccelerationStructures�м��ٽṹԪ�ظ���
		writeDescriptorSetAccelerationStructureNV.pAccelerationStructures = VK_NULL_HANDLE;//��һ��VkAccelerationStructureKHR ������ָ�룬ָ��Ҫ���µļ��ٽṹ
		/*
		VkWriteDescriptorSetAccelerationStructureNV��Ч�÷�:
		1.accelerationStructureCount ������ڱ���չ��VkWriteDescriptorSet��descriptorCount
		2.pAccelerationStructures��ÿ�����ٽṹ������VK_ACCELERATION_STRUCTURE_TYPE_TOP_LEVEL_KHR ���ʹ���
		3.���nullDescriptor ����û�п�������pAccelerationStructures�е�ÿ��Ԫ�ز���ΪVK_NULL_HANDLE
		*/


		//copy
		VkCopyDescriptorSet copyDescriptorSet{};
		copyDescriptorSet.sType = VK_STRUCTURE_TYPE_COPY_DESCRIPTOR_SET;
		copyDescriptorSet.pNext = nullptr;
		copyDescriptorSet.descriptorCount = 1;//ָ��Ҫ������descriptor���������ͨ��srcSet��srcBinding ָ����binding��descriptorTypeΪ VK_DESCRIPTOR_TYPE_INLINE_UNIFORM_BLOCK�������ָ��Ҫ�������ֽڴ�С
		copyDescriptorSet.dstArrayElement = 0;//���dstBinding��descriptor�����е���ʼԪ�أ����ͨ��dstSet��dstBinding ָ����binding��descriptorTypeΪ VK_DESCRIPTOR_TYPE_INLINE_UNIFORM_BLOCK�������ָ��Ϊ���binding�п�ʼ�ֽڵ�ƫ����
		copyDescriptorSet.dstBinding = 0;////ָ��Ҫ��������destination descriptor set��binding
		copyDescriptorSet.dstSet = VkDescriptorSet{/*��������һ����Ч��VkDescriptorSet*/ }; //ָ��Ҫ��������destination descriptor set
		copyDescriptorSet.srcArrayElement = 0;//���srcBinding��descriptor�����е���ʼԪ�أ����ͨ��srcSet��srcBinding ָ����binding��descriptorTypeΪ VK_DESCRIPTOR_TYPE_INLINE_UNIFORM_BLOCK�������ָ��Ϊ���binding�п�ʼ�ֽڵ�ƫ����
		copyDescriptorSet.srcBinding = 0;//ָ��Ҫ������source descriptor set��binding
		copyDescriptorSet.srcSet = VkDescriptorSet{/*��������һ����Ч��VkDescriptorSet*/ };//ָ��Ҫ������source descriptor set
		/*
		VkCopyDescriptorSet��Ч�÷�:
		1.srcBinding ������srcSet����Ч��binding
		2.srcArrayElement + descriptorCount ����С�ڵ���srcSet��srcBinding��descriptor ���������Լ�consecutive binding updates p1301������������binding�����п��õ�descriptor������
		3.dstBinding ������dstSet����Ч��binding
		4.dstArrayElement + descriptorCount ����С�ڵ���srcSet��dstBinding��descriptor ���������Լ�consecutive binding updates p1301������������binding�����п��õ�descriptor������
		5.dstSet��dstBinding �����ͱ������srcSet��srcBinding ������
		6.���srcSet ����dstSet����source��destination��descriptors�ķ�Χ�����ص�����Щ��Χ�п��ܰ���consecutive binding updates p1301������������binding
		7.���srcBinding ָ����descriptor ����ΪVK_DESCRIPTOR_TYPE_INLINE_UNIFORM_BLOCK����srcArrayElement ������4��������
		8.���dstBinding ָ����descriptor ����ΪVK_DESCRIPTOR_TYPE_INLINE_UNIFORM_BLOCK����dstArrayElement ������4��������
		9.���srcBinding ���� dstBinding ָ����descriptor ����ΪVK_DESCRIPTOR_TYPE_INLINE_UNIFORM_BLOCK����descriptorCount ������4��������
		10.���srcSet ��layout��VK_DESCRIPTOR_SET_LAYOUT_CREATE_UPDATE_AFTER_BIND_POOL_BIT��������dstSet ��layout ������VK_DESCRIPTOR_SET_LAYOUT_CREATE_UPDATE_AFTER_BIND_POOL_BIT����
		11.���srcSet ��layout����VK_DESCRIPTOR_SET_LAYOUT_CREATE_HOST_ONLY_POOL_BIT_EXT ����VK_DESCRIPTOR_SET_LAYOUT_CREATE_UPDATE_AFTER_BIND_POOL_BIT ��������dstSet ��layout �Ͳ�����VK_DESCRIPTOR_SET_LAYOUT_CREATE_UPDATE_AFTER_BIND_POOL_BIT����
		12.�������srcSet ��descriptor pool ��VK_DESCRIPTOR_POOL_CREATE_UPDATE_AFTER_BIND_BIT�����������dstSet ��descriptor pool Ҳ������VK_DESCRIPTOR_POOL_CREATE_UPDATE_AFTER_BIND_BIT����
		13.�������srcSet ��descriptor pool ����VK_DESCRIPTOR_POOL_CREATE_HOST_ONLY_BIT_EXT ���� VK_DESCRIPTOR_POOL_CREATE_UPDATE_AFTER_BIND_BIT�����������dstSet ��descriptor pool ������VK_DESCRIPTOR_POOL_CREATE_UPDATE_AFTER_BIND_BIT����
		14.���dstBinding ָ����descriptor ����ΪVK_DESCRIPTOR_TYPE_SAMPLER����dstSet ������һ��dstBinding ����immutable samplers��layout���з���
		15.���dstSet��dstBinding������ΪVK_DESCRIPTOR_TYPE_MUTABLE_EXT��������µĸ�dstBinding��descriptor ���Ͳ�ΪVK_DESCRIPTOR_TYPE_MUTABLE_EXT��������о��ڸ�dstBinding��Ӧ��pMutableDescriptorTypeLists�б���
		16.���srcSet��srcBinding������ΪVK_DESCRIPTOR_TYPE_MUTABLE_EXT����dstSet��dstBinding�����Ͳ�ΪVK_DESCRIPTOR_TYPE_MUTABLE_EXT����source descriptor�����ͱ����dstBinding�ϵ�descriptor����ƥ��
		17.���dstSet��dstBinding������ΪVK_DESCRIPTOR_TYPE_MUTABLE_EXT��������µĸ�dstBinding��descriptor ����ΪVK_DESCRIPTOR_TYPE_MUTABLE_EXT�����ӦsrcBinding��dstBinding��pMutableDescriptorTypeLists�е�Ԫ�ر�����ȫƥ��

		*/


		vkUpdateDescriptorSets(device, 1, &writeDescriptorSet, 1, &copyDescriptorSet);
		/*
		vkUpdateDescriptorSets��Ч�÷�:
		1.����pDescriptorWrites��ÿ��descriptorTypeΪVK_DESCRIPTOR_TYPE_UNIFORM_TEXEL_BUFFER ���� VK_DESCRIPTOR_TYPE_STORAGE_TEXEL_BUFFER��Ԫ�أ����Ԫ�ص�pTexelBufferView �����Ѿ���device�ϴ���
		2.����pDescriptorWrites��ÿ��descriptorTypeΪVK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, VK_DESCRIPTOR_TYPE_STORAGE_BUFFER, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC, ���� VK_DESCRIPTOR_TYPE_STORAGE_BUFFER_DYNAMIC��Ԫ�أ����Ԫ�ص�pBufferInfo��buffer �����Ѿ���device�ϴ���
		3.����pDescriptorWrites��ÿ��descriptorTypeΪVK_DESCRIPTOR_TYPE_SAMPLER ���� VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER��Ԫ�أ������dstSet ����һ��descriptorType���͵�dstBinding ���� immutable samplers��layout���з��䣬�����Ԫ�ص�pImageInfo�� sampler�����Ѿ���device�ϴ���
		4.����pDescriptorWrites��ÿ��descriptorTypeΪVK_DESCRIPTOR_TYPE_SAMPLED_IMAGE��VK_DESCRIPTOR_TYPE_STORAGE_IMAGE��VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT ���� VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER��Ԫ�أ����Ԫ�ص�pImageInfo�� imageView �����Ѿ���device�ϴ���
		5.����pDescriptorWrites��ÿ��descriptorTypeΪVK_DESCRIPTOR_TYPE_ACCELERATION_STRUCTURE_KHR ��Ԫ�أ����Ԫ�ص�pNext�е�VkWriteDescriptorSetAccelerationStructureKHR.pAccelerationStructures �еļ��ٽṹ�����Ѿ���device�ϴ���
		6.����pDescriptorWrites��ÿ��descriptorTypeΪVK_DESCRIPTOR_TYPE_ACCELERATION_STRUCTURE_NV ��Ԫ�أ����Ԫ�ص�pNext�е�VkWriteDescriptorSetAccelerationStructureNV.pAccelerationStructures �еļ��ٽṹ�����Ѿ���device�ϴ���
		7.����pDescriptorWrites��ÿ��descriptorTypeΪVK_DESCRIPTOR_TYPE_SAMPLE_WEIGHT_IMAGE_QCOM ���� VK_DESCRIPTOR_TYPE_BLOCK_MATCH_IMAGE_QCOM ��Ԫ�أ����Ԫ�ص�pImageInfo�� imageView  �����Ѿ���device�ϴ���
		8.����pDescriptorWrites��ÿ��descriptorTypeΪVK_DESCRIPTOR_TYPE_SAMPLER, VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE, VK_DESCRIPTOR_TYPE_STORAGE_IMAGE, ����
                                     VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT ��Ԫ�أ����Ԫ�ص�pImageInfo�����Ǹ�Ԫ����ָdescriptorCount����ЧVkDescriptorImageInfo�����ָ��
		9.����pDescriptorWrites��ÿ��descriptorTypeΪVK_DESCRIPTOR_TYPE_SAMPLE_WEIGHT_IMAGE_QCOM ���� VK_DESCRIPTOR_TYPE_BLOCK_MATCH_IMAGE_QCOM ��Ԫ�أ����Ԫ�ص�pImageInfo�����Ǹ�Ԫ����ָdescriptorCount����ЧVkDescriptorImageInfo�����ָ��
		10.pDescriptorWrites ��ÿ��Ԫ�ص�dstSet���� pDescriptorCopies��binding����VK_DESCRIPTOR_BINDING_UPDATE_AFTER_BIND_BIT���� VK_DESCRIPTOR_BINDING_UPDATE_UNUSED_WHILE_PENDING_BIT������Ԫ�ز������κ�һ����¼��pending state ״̬��command buffer��command��ʹ��
		11.host����pDescriptorWrites�е�dstSet�Լ�pDescriptorCopies�е�dstSet �������ⲿͬ���ģ�����������ı�־���á�
	
		*/
	
	}




}


NS_TEST_END