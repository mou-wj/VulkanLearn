#include "ResourceDescriptorsTest.h"
NS_TEST_BEGIN



/*
一个 descriptor 是一个指明了用作一个shader resource 的如 buffer, buffer view, image view, sampler, 或者 combined image sampler，通过 descriptor sets来组织，
每个descriptor set中可以包含的descriptor 排布由 descriptor set layout决定。descriptor set layout 可被pipeline layout进行使用，如果 descriptorBuffer 特性开启，则支持
将descriptor 放到 descriptor buffers中。

shader通过使用descriptor set和binding 号进行修饰的变量来访问资源，这些变量将它们链接到descriptor set中的descriptor，映射到descriptor set的shader 接口描述见  Shader Resource Interface p1409

shader 可以直接通过64位的地址直接访问buffer而不需要通过descriptor，见 Physical Storage Buffer Access p1352

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
	//vulkan中支持多找descriptor 类型，对应不同的资源使用方式


	// Storage Image
	{
	/*
	
	 一个storage image (VK_DESCRIPTOR_TYPE_STORAGE_IMAGE) 是一个关联到image resource通过image view进行的加载，存储，以及原子操作的 descriptor type

	 支持所有shader阶段，其他详情见p1242

	
	*/
	
	}

	// Sampler
	{
	/*
	一个sampler descriptor (VK_DESCRIPTOR_TYPE_SAMPLER) 是一个关联 sampler 的 descriptor type,用来控制 sampled image的采样行为（p1473）

	*/
	}


	//Sampled Image
	{
	/*
	一个sampled image (VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE) 是一个关联到image resource通过image view进行的采样操作（p1473）的 descriptor type
	
	shader 绑定到一个sampled image变量以及sampler变量来进行采样

	支持所有shader，image view的format的  format features 需含有VK_FORMAT_FEATURE_SAMPLED_IMAGE_BIT

	绑定的image subresource的layout应为以下类型之一：
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
	一个combined image sampler (VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER) 是一个单独的关联到sampler和 image subresource的  descriptor type，即将 一个sampler 和 sampled image descriptor绑定到了一起成为一个单独的descriptor
	
	如果该descriptor 引用到一个 使用了 Y′CBCR conversion 或者采样  subsampled image的sampler，则sampler只能用于对同一descriptor中的image进行采样。否则sampler和descriptor的image 就看可以任意组合

	绑定的image subresource的layout应为以下类型之一：
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
	一个uniform texel buffer (VK_DESCRIPTOR_TYPE_UNIFORM_TEXEL_BUFFER) 是一个关联到buffer resource通过buffer view进行image 采样操作（p1473）的 descriptor type
	
	uniform texel buffer定义了一个紧密排列的一维线性texel数组，当纹理在着色器中读取时，纹理会以与图像一样的方式进行格式转换。
	
	支持所有shader，image view的format的  format features 需含有VK_FORMAT_FEATURE_UNIFORM_TEXEL_BUFFER_BIT
	*/
	
	}


	// Storage Texel Buffer
	{
	/*
	一个 storage texel buffer (VK_DESCRIPTOR_TYPE_STORAGE_TEXEL_BUFFER) 是一个关联到buffer resource通过buffer view进行image 加载，存储，以及原子操作的 descriptor type
	
	storage texel buffer定义了一个紧密排列的一维线性texel数组，当纹理在着色器中读取时，纹理会以与图像一样的方式进行格式转换。相比 uniform texel buffer，storage texel buffer可以用相同的方式写入  storage images。

	其他详情见p1244
	*/
	
	}

	// Storage Buffer
	{
	/*
	一个 storage buffer (VK_DESCRIPTOR_TYPE_STORAGE_BUFFER) 是一个直接关联到buffer resource，在shader中通过结构体变量成员来进行加载，存储，以及原子操作的 descriptor type
	
	*/
	}

	// Uniform Buffer
	{
	/*
	一个  uniform buffer (VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER) 是一个直接关联到buffer resource，在shader中通过结构体变量成员来进行加载操作的 descriptor type
	*/
	}

	// Dynamic Uniform Buffer
	{
	/*
		一个 dynamic uniform buffer(VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC) 几乎等同于 uniform buffer，只是该descriptor会去指定buffer的offset，在绑定descriptor set 时添加一个 VkDescriptorBufferInfo 到dynamic offset（p1239）的最开始更新descriptor set的时候计算基本的offset
	*/
	
	}

	//Dynamic Storage Buffer
	{
	/*
		一个 dynamic storage buffer (VK_DESCRIPTOR_TYPE_STORAGE_BUFFER_DYNAMIC) 几乎等同于 storage buffer，只是该descriptor会去指定buffer的offset，在绑定descriptor set 时添加一个 VkDescriptorBufferInfo 到dynamic offset（p1239）的最开始更新descriptor set的时候计算基本的offset
	*/
	}

	// Inline Uniform Block
	{
	/*
	一个inline uniform block (VK_DESCRIPTOR_TYPE_INLINE_UNIFORM_BLOCK) 几乎等用于uniform buffer，只是该descriptor 所对的数据直接存储在descriptor set中，不用额外的buffer memory，节省了内存，提高了性能。
	
	典型用法时存放小部分常量数据，相比于push constants ，可以在离散的绘制以及dispatching commands时重用相同的常量数据。
	
	inline uniform block descriptors 不能组合成一个数组，而一个inline uniform block descriptor binding 的数组大小实际是指明了这个binding的字节容量。
	*/
	}

	// Sample Weight Image
	{
	/*
	一个sample weight image (VK_DESCRIPTOR_TYPE_SAMPLE_WEIGHT_IMAGE_QCOM) 是一个关联到 image resource 通过 image view 进行weight image 采样操作的 descriptor type，该 image view 必须使用 VkImageViewSampleWeightCreateInfoQCOM 结构创建。

	shader可以绑定一个sample weight image变量，一个sampled image变量，以及一个sampler变量来进行weight image采样。

	支持所有shader，weight image view的format的  format features 需含有VK_FORMAT_FEATURE_2_WEIGHT_IMAGE_BIT_QCOM，sampled image view的format的  format features 需含有VK_FORMAT_FEATURE_2_WEIGHT_SAMPLED_IMAGE_BIT_QCOM
	

	weight image subresources的布局应该为 VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL或者  VK_IMAGE_LAYOUT_GENERAL 
	*/
	}


	//Block Matching Image
	{
	/*
	一个block matching image (VK_DESCRIPTOR_TYPE_BLOCK_MATCHING_IMAGE_QCOM) 是一个关联到 image resource 通过 image view 进行block matching 操作的 descriptor type。

	shader可以绑定一个block matching image（target image）变量，一个reference image变量，以及一个sampler变量来进行block matching。

	支持所有shader，block matching image view和reference view 的format的  format features 需含有VK_FORMAT_FEATURE_2_BLOCK_MATCHING_BIT_QCOM
	
	block matching的image subresources 的布局应该为VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL 或者 VK_IMAGE_LAYOUT_GENERAL

	*/
	
	}

	//Input Attachment
	{
	/*
	一个input attachment (VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT) 是一个关联到 image resource 通过 image view 进行在fragment shaders中framebuffer local load 操作的 descriptor type。

	对于给定image的tiling所有支持color attachments（VK_FORMAT_FEATURE_COLOR_ATTACHMENT_BIT 或 VK_FORMAT_FEATURE_2_LINEAR_COLOR_ATTACHMENT_BIT_NV ），或者 depth/stencil attachments (VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT) 也将支持input attachments
	
	input attachment所对的image view的布局应该为以下中的一个:
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
	一个acceleration structure (VK_DESCRIPTOR_TYPE_ACCELERATION_STRUCTURE_KHR 或者 VK_DESCRIPTOR_TYPE_ACCELERATION_STRUCTURE_NV) 是一个获取shader中用来进行ray tracing的场景集合数据（只读）的 descriptor type。

	*/
	}

	//Mutable
	{
	/*
	一个 mutable  descriptor (VK_DESCRIPTOR_TYPE_MUTABLE_EXT) 指明这个descriptor 可以变更为任何其他类型的descriptor，具体的类型由VkDescriptorSetLayoutCreateInfo.pNext中的VkMutableDescriptorTypeListEXT::pDescriptorTypes列表中当前bingding给出的descriptor type决定。
	
	可以通过指定VK_DESCRIPTOR_TYPE_MUTABLE_EXT binding以及 该binding的 VkMutableDescriptorTypeCreateInfoEXT::pDescriptorTypes 调用 vkGetDescriptorSetLayoutSupport来获取该descriptor支持的descriptor type。
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
	概述
	descriptor 组合成descriptor set，然后通过 descriptor set layout描述其中的descriptor的类型和数量，以及它们的binding 号，descriptor set layout也会确定descriptor set要使用的resource以及 shader resources和shader stage之间的接口。
	
	*/

	//descriptor set layout
	VkDescriptorSetLayout descriptorSetLayout{};
	{
	/*
	descriptor set layout 通过一组一个或多个 descriptor bindings 来定义，每个单独的descriptor binding 由一个 descriptor type，一个bingding中的 descriptor count，以及一组可访问该binding的 shader stage 组成，还有（如果使用 immutable samplers）一个 sampler descriptors的数组。
	*/
	
		VkDescriptorSetLayoutCreateInfo descriptorSetLayoutCreateInfo{};
		descriptorSetLayoutCreateInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
			DescriptorSetLayoutCreateInfoEXT descriptorSetLayoutCreateInfoEXT{};
		descriptorSetLayoutCreateInfo.pNext = &descriptorSetLayoutCreateInfoEXT.descriptorSetLayoutBindingFlagsCreateInfo;//可以含有VkDescriptorSetLayoutBindingFlagsCreateInfo 或者 VkMutableDescriptorTypeCreateInfoEXT
		descriptorSetLayoutCreateInfo.flags = 0;//是一个  VkDescriptorSetLayoutCreateFlagBits 组合值的位掩码，指明descriptor set layout创建的额外属性
		/*
		VkDescriptorSetLayoutCreateFlagBits:

		VK_DESCRIPTOR_SET_LAYOUT_CREATE_PUSH_DESCRIPTOR_BIT_KHR :  指定descriptor sets不能使用这个layout进行分配，这个descriptors 会通过vkCmdPushDescriptorSetKHR 进行更新 
		VK_DESCRIPTOR_SET_LAYOUT_CREATE_UPDATE_AFTER_BIND_POOL_BIT :  指定descriptor sets必须从一个创建含有VK_DESCRIPTOR_POOL_CREATE_UPDATE_AFTER_BIND_BIT 的descriptor pool 上去分配，以这个标志创建的descriptor set layout在descriptors per-stage 以及 per-pipeline layout上由别的最大数量的限制，、
																					non-UpdateAfterBind 限制只会统计不以这个标志创建的descriptor set 中的descriptors数量。UpdateAfterBind 限制会统计所有descriptors数量，但可能高于non-UpdateAfterBind 限制数量。
		
		VK_DESCRIPTOR_SET_LAYOUT_CREATE_INDIRECT_BINDABLE_BIT_NV:  指定使用这个layout的descriptor sets 能够绑定到以VK_PIPELINE_CREATE_INDIRECT_BINDABLE_BIT_NV 创建的compute pipelines，在Device-Generated Commands 中使用。
		VK_DESCRIPTOR_SET_LAYOUT_CREATE_DESCRIPTOR_BUFFER_BIT_EXT:  指定这个layout只能用于描述 descriptor buffers.
		VK_DESCRIPTOR_SET_LAYOUT_CREATE_EMBEDDED_IMMUTABLE_SAMPLERS_BIT_EXT:  指定这个layout只能包含vkCmdBindDescriptorBufferEmbeddedSamplersEXT 可以绑定的 immutable samplers，不像通常的immutable samplers，embedded immutable samplers不需要应用提供一个 descriptor buffer.

		VK_DESCRIPTOR_SET_LAYOUT_CREATE_HOST_ONLY_POOL_BIT_EXT :  指定descriptor sets必须从一个创建含有VK_DESCRIPTOR_POOL_CREATE_HOST_ONLY_BIT_EXT 的descriptor pool 上去分配，以这个标志创建的descriptor set layout在descriptors per-stage  上没有明显的最大数量的限制，host descriptor sets 只受可用host memory的限制，但可能由于一些具体的实现而收到特别的限制， 实现
																					可能会限制支持的UpdateAfterBind 或者 non-UpdateAfterBind descriptors数量，不管哪一个更大。
		
		VK_DESCRIPTOR_SET_LAYOUT_CREATE_PER_STAGE_BIT_NV:  指定descriptor sets中使用这个layout的bingding 数量在每一个stage中可能会呈现不同资源且或者资源类型
		*/
		descriptorSetLayoutCreateInfo.bindingCount = 1;// pBindings 中的个数
			VkDescriptorSetLayoutBinding descriptorBinding{};
			{
				descriptorBinding.binding = 0;//指定binding号，对应shader stage中相同binding号的资源
				descriptorBinding.descriptorCount = 1;//是shader stage中这个binding上含有的descriptors的数量，在shader中通过数组访问， 如果 descriptorType为 VK_DESCRIPTOR_TYPE_INLINE_UNIFORM_BLOCK，则该值表示 inline uniform block 的字节大小，如果该值为0则表示shader不能在绑定了这个layout的pipeline中使用这个binding
				descriptorBinding.descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;//是一个 VkDescriptorType值，指定这个binding上的resource descriptors的类型
				descriptorBinding.pImmutableSamplers = (const VkSampler*)VkSampler{/*假设这是一个有效的VkSampler*/};//影响 samplers的初始化,如果descriptorType为 VK_DESCRIPTOR_TYPE_SAMPLER 为 VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER，且该VkSampler不为VK_NULL_HANDL则表示该VkSampler会在该binding上使用且无法动态更新，如果VkSampler为VK_NULL_HANDL则表示可以动态更新，如果descriptorType不为前面说的两种，则这个参数会被忽略
				descriptorBinding.stageFlags = VK_SHADER_STAGE_ALL;//是 VkShaderStageFlagBits 组合值的位掩码，指定这个binding可以被访问的shader stage
				/*
				VkDescriptorSetLayoutBinding有效用法：
				1.如果descriptorType 为VK_DESCRIPTOR_TYPE_SAMPLER 或者VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER，且descriptorCount不为0，pImmutableSamplers不为NULL，否则pImmutableSamplers必须指向一个包含descriptorCount个有效VkSampler的数组。
				2.如果inlineUniformBlock 特性没有开启，则descriptorType 不能为VK_DESCRIPTOR_TYPE_INLINE_UNIFORM_BLOCK
				3.如果descriptorType 为VK_DESCRIPTOR_TYPE_INLINE_UNIFORM_BLOCK 则（1）descriptorCount 必须为4的倍数
																				 （2）如果VkDescriptorSetLayoutCreateInfo::flags 不包含VK_DESCRIPTOR_SET_LAYOUT_CREATE_DESCRIPTOR_BUFFER_BIT_EXT，则descriptorCount 必须小于等于VkPhysicalDeviceInlineUniformBlockProperties::maxInlineUniformBlockSize
				4.如果VkDescriptorSetLayoutCreateInfo::flags 包含VK_DESCRIPTOR_SET_LAYOUT_CREATE_EMBEDDED_IMMUTABLE_SAMPLERS_BIT_EXT，则（1）descriptorType 必须为VK_DESCRIPTOR_TYPE_SAMPLER，descriptorCount 必须小于等于1
																																		（2）如果descriptorCount 等于1，pImmutableSamplers 不能为NULL
				5.如果descriptorCount 不为0，stageFlags 必须为VK_SHADER_STAGE_ALL 或者有效的VkShaderStageFlagBits 组合值
				6.如果descriptorType 为VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT且descriptorCount 不为0，则stageFlags 必须为0或者 VK_SHADER_STAGE_FRAGMENT_BIT
				7.pImmutableSamplers 指定的sampler对象的borderColor 等于VK_BORDER_COLOR_FLOAT_CUSTOM_EXT 或VK_BORDER_COLOR_INT_CUSTOM_EXT 
				8.如果descriptorType 为VK_DESCRIPTOR_TYPE_MUTABLE_EXT，则pImmutableSamplers 必须为NULL
				9.如果 VkDescriptorSetLayoutCreateInfo::flags 包含VK_DESCRIPTOR_SET_LAYOUT_CREATE_PER_STAGE_BIT_NV，且descriptorCount 不为0，则stageFlags 必须是 VK_SHADER_STAGE_VERTEX_BIT, VK_SHADER_STAGE_TESSELLATION_CONTROL_BIT, VK_SHADER_STAGE_TESSELLATION_EVALUATION_BIT,
													VK_SHADER_STAGE_GEOMETRY_BIT, VK_SHADER_STAGE_FRAGMENT_BIT 和 VK_SHADER_STAGE_COMPUTE_BIT 的有效的组合值

				*/
			
			}
		descriptorSetLayoutCreateInfo.pBindings = &descriptorBinding;//是一组 VkDescriptorSetLayoutBinding的数组地址
		/*
		VkDescriptorSetLayoutCreateInfo有效用法:
		1.如果perStageDescriptorSet 特性没有开启，或者flags没有包含VK_DESCRIPTOR_SET_LAYOUT_CREATE_PER_STAGE_BIT_NV，则pBindings中的每个元素的VkDescriptorSetLayoutBinding::binding成员必须有不同的值
		2.如果flags包含	VK_DESCRIPTOR_SET_LAYOUT_CREATE_PUSH_DESCRIPTOR_BIT_KHR，则pBindings 的所有元素不能有 descriptorType 等于 VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC 或 VK_DESCRIPTOR_TYPE_STORAGE_BUFFER_DYNAMIC
		3.如果flags包含 VK_DESCRIPTOR_SET_LAYOUT_CREATE_PUSH_DESCRIPTOR_BIT_KHR，则（1）pBindings 的所有元素不能有 descriptorType 等于 VK_DESCRIPTOR_TYPE_INLINE_UNIFORM_BLOCK
																				   （2）pBindings 的所有元素中descriptor数量总和不能超过 VkPhysicalDevicePushDescriptorPropertiesKHR::maxPushDescriptors
																				   （3）flags 不能包含VK_DESCRIPTOR_SET_LAYOUT_CREATE_HOST_ONLY_POOL_BIT_EXT
																				   （4）pBindings中不能含有descriptorType 为VK_DESCRIPTOR_TYPE_MUTABLE_EXT 的元素
		4.如果任何binding含有VK_DESCRIPTOR_BINDING_UPDATE_AFTER_BIND_BIT，则（1）flags 必须包含 VK_DESCRIPTOR_SET_LAYOUT_CREATE_UPDATE_AFTER_BIND_POOL_BIT
																			（2）所有binding元素不能有 descriptorType 等于 VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC 或者VK_DESCRIPTOR_TYPE_STORAGE_BUFFER_DYNAMIC
		5.如果flags包含VK_DESCRIPTOR_SET_LAYOUT_CREATE_UPDATE_AFTER_BIND_POOL_BIT，则flags不能包含VK_DESCRIPTOR_SET_LAYOUT_CREATE_HOST_ONLY_POOL_BIT_EXT
		6.如果如果pBindings[i]的descriptorType 等于 VK_DESCRIPTOR_TYPE_MUTABLE_EXT，则pNext中必须含有一个mutableDescriptorTypeListCount 大于i的VkMutableDescriptorTypeCreateInfoEXT
		7.如果一个binding的descriptorType为VK_DESCRIPTOR_TYPE_MUTABLE_EXT，则pImmutableSamplers 必须为NULL
		8.如果mutableDescriptorTypeFeaturesEXT::mutableDescriptorType 特性没有开启，则pBindings中不能含有descriptorType 为VK_DESCRIPTOR_TYPE_MUTABLE_EXT 的元素
		9.如果flags包含VK_DESCRIPTOR_SET_LAYOUT_CREATE_HOST_ONLY_POOL_BIT_EXT，则VkPhysicalDeviceMutableDescriptorTypeFeaturesEXT::mutableDescriptorType 必须开启
		10.如果flags包含VK_DESCRIPTOR_SET_LAYOUT_CREATE_DESCRIPTOR_BUFFER_BIT_EXT，则pBindings 的所有元素不能有 descriptorType 等于 VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC 或 VK_DESCRIPTOR_TYPE_STORAGE_BUFFER_DYNAMIC
		11.如果flags包含VK_DESCRIPTOR_SET_LAYOUT_CREATE_EMBEDDED_IMMUTABLE_SAMPLERS_BIT_EXT，则flags不能包含VK_DESCRIPTOR_SET_LAYOUT_CREATE_DESCRIPTOR_BUFFER_BIT_EXT
		12.如果flags包含VK_DESCRIPTOR_SET_LAYOUT_CREATE_DESCRIPTOR_BUFFER_BIT_EXT，则flags不能包含VK_DESCRIPTOR_SET_LAYOUT_CREATE_UPDATE_AFTER_BIND_POOL_BIT，VK_DESCRIPTOR_SET_LAYOUT_CREATE_HOST_ONLY_POOL_BIT_VALVE
		13.如果flags包含VK_DESCRIPTOR_SET_LAYOUT_CREATE_PER_STAGE_BIT_NV，则（1）perStageDescriptorSet 必须开启
																			（2）pBindings中不能含有VkDescriptorSetLayoutBinding::binding相等 以及VkDescriptorSetLayoutBinding::stageFlags含有相同比特位的两个元素 

		*/


		//VkMutableDescriptorTypeCreateInfoEXT   等价于VkMutableDescriptorTypeCreateInfoVALVE
		//指明mutable descriptor可能的descriptor 类型, VkDescriptorSetLayoutCreateInfo::pBindings[i] 使用列举在VkMutableDescriptorTypeCreateInfoEXT::::pMutableDescriptorTypeLists[i]中的 descriptor类型
		VkMutableDescriptorTypeCreateInfoEXT& mutableDescriptorTypeCreateInfoEXT = descriptorSetLayoutCreateInfoEXT.mutableDescriptorTypeCreateInfoEXT;
		mutableDescriptorTypeCreateInfoEXT.mutableDescriptorTypeListCount = 1;// pMutableDescriptorTypeLists的元素
			VkMutableDescriptorTypeListEXT mutableDescriptorTypeList{};//等价于VkMutableDescriptorTypeListVALVE
			{
				mutableDescriptorTypeList.descriptorTypeCount = 0;//pDescriptorTypes中元素个数
				mutableDescriptorTypeList.pDescriptorTypes = VK_NULL_HANDLE;//是descriptorTypeCount个 VkDescriptorType的数组地址，定义一个给定的绑定mutable descriptor可能会突变为哪些描述符类型。
				/*
				VkMutableDescriptorTypeListEXT有效用法:
				1.descriptorTypeCount 不能为0，如果对应的binding 为VK_DESCRIPTOR_TYPE_MUTABLE_EXT
				2.pDescriptorTypes 必须是一个有效的指针，指向一个descriptorTypeCount个有效的、唯一的VkDescriptorType值，如果给定的binding是VK_DESCRIPTOR_TYPE_MUTABLE_EXT类型
				3.descriptorTypeCount 必须为0，如果对应的binding 不为VK_DESCRIPTOR_TYPE_MUTABLE_EXT
				4.pDescriptorTypes 不能包含VK_DESCRIPTOR_TYPE_MUTABLE_EXT，VK_DESCRIPTOR_TYPE_STORAGE_BUFFER_DYNAMIC，VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC ，VK_DESCRIPTOR_TYPE_INLINE_UNIFORM_BLOCK

				*/
			}
		mutableDescriptorTypeCreateInfoEXT.pMutableDescriptorTypeLists = &mutableDescriptorTypeList;//是一组 VkMutableDescriptorTypeListEXT的数组地址


		//VkDescriptorSetLayoutBindingFlagsCreateInfo    等同于VkDescriptorSetLayoutBindingFlagsCreateInfoEXT
		//指明用于descriptor sets layout的每个binding的flags   ，即 VkDescriptorSetLayoutCreateInfo::pBindings[i] 使用 VkDescriptorSetLayoutBindingFlagsCreateInfo::pBindingFlags[i] 中的flags
		VkDescriptorSetLayoutBindingFlagsCreateInfo& bindingFlagsCreateInfo = descriptorSetLayoutCreateInfoEXT.descriptorSetLayoutBindingFlagsCreateInfo;
		bindingFlagsCreateInfo.pBindingFlags = (VkDescriptorBindingFlags*)VkDescriptorBindingFlagBits{ VK_DESCRIPTOR_BINDING_UPDATE_AFTER_BIND_BIT };/*是一个VkDescriptorBindingFlagBits 组合值的位掩码数组，用于指定descriptor set layout的每个binding的flags
		VkDescriptorBindingFlagBits （等同于VkDescriptorBindingFlagBitsEXT）:

		VK_DESCRIPTOR_BINDING_UPDATE_AFTER_BIND_BIT:  指明这个binding的descriptors 将在这个descriptor set绑定到command buffer和command buffer提交到队列之间进行更新。
		VK_DESCRIPTOR_BINDING_PARTIALLY_BOUND_BIT:  指明这个binding的descriptors 不是动态使用的，在使用时这个binding必须含有有效的descriptors
		VK_DESCRIPTOR_BINDING_UPDATE_UNUSED_WHILE_PENDING_BIT:  指明这个binding的descriptors 可以在command buffer绑定该descriptor set之后更新，或者在使用该descriptor set的command buffer处于pending execution下进行更新，或者在不使用该descriptor set的command buffer处于pending execution下进行更新。
		VK_DESCRIPTOR_BINDING_VARIABLE_DESCRIPTOR_COUNT_BIT:  指明这个binding的descriptors 是一个可变大小的descriptor binding，其大小将在分配descriptor set时指定。descriptorCount 将作为一个上限，但实际的descriptor数量可能小于这个上限。

		》》》》》》》》》》这里每个枚举类型的含义过长，这里只列举最重要的信息，剩下的详细说明见p1261
		
		*/
		bindingFlagsCreateInfo.bindingCount = 1;//pBindingFlags 中的元素个数
		/*
		VkDescriptorSetLayoutBindingFlagsCreateInfo
		1.如果bindingCount 不能0则必须等于VkDescriptorSetLayoutCreateInfo::bindingCount
		2.如果VkDescriptorSetLayoutCreateInfo::flags 包含VK_DESCRIPTOR_SET_LAYOUT_CREATE_PUSH_DESCRIPTOR_BIT_KHR，则pBindingFlags 中的所有元素不能含有VK_DESCRIPTOR_BINDING_UPDATE_AFTER_BIND_BIT，VK_DESCRIPTOR_BINDING_UPDATE_UNUSED_WHILE_PENDING_BIT，VK_DESCRIPTOR_BINDING_UPDATE_UNUSED_WHILE_PENDING_BIT 或者VK_DESCRIPTOR_BINDING_VARIABLE_DESCRIPTOR_COUNT_BIT
		3.如果pBindingFlags 的一个元素包含VK_DESCRIPTOR_BINDING_VARIABLE_DESCRIPTOR_COUNT_BIT，则这个元素的binding 号必须是pBindings 中binding 号的最大值
		4.如果VkPhysicalDeviceDescriptorIndexingFeatures::descriptorBindingUniformBufferUpdateAfterBind 没有开启，则所有binding的descriptorType为VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER 不能使用VK_DESCRIPTOR_BINDING_UPDATE_AFTER_BIND_BIT
		5.如果VkPhysicalDeviceDescriptorIndexingFeatures::descriptorBindingSampledImageUpdateAfterBind 没有开启，则所有binding的descriptorType为VK_DESCRIPTOR_TYPE_SAMPLER而 不能为VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER 或者 VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE
		6.如果VkPhysicalDeviceDescriptorIndexingFeatures::descriptorBindingStorageImageUpdateAfterBind 没有开启，则所有binding的descriptorType为VK_DESCRIPTOR_TYPE_STORAGE_IMAGE 且不能使用VK_DESCRIPTOR_BINDING_UPDATE_AFTER_BIND_BIT
		7.如果VkPhysicalDeviceDescriptorIndexingFeatures::descriptorBindingStorageBufferUpdateAfterBind 没有开启，则所有binding的descriptorType为VK_DESCRIPTOR_TYPE_STORAGE_BUFFER 且不能使用VK_DESCRIPTOR_BINDING_UPDATE_AFTER_BIND_BIT
		8.如果VkPhysicalDeviceDescriptorIndexingFeatures::descriptorBindingUniformTexelBufferUpdateAfterBind 没有开启，则所有binding的descriptorType为VK_DESCRIPTOR_TYPE_UNIFORM_TEXEL_BUFFER 且不能使用VK_DESCRIPTOR_BINDING_UPDATE_AFTER_BIND_BIT
		9.如果VkPhysicalDeviceDescriptorIndexingFeatures::descriptorBindingStorageTexelBufferUpdateAfterBind 没有开启，则所有binding的descriptorType为VK_DESCRIPTOR_TYPE_STORAGE_TEXEL_BUFFER 且不能使用VK_DESCRIPTOR_BINDING_UPDATE_AFTER_BIND_BIT
		10.如果VkPhysicalDeviceInlineUniformBlockFeatures::descriptorBindingInlineUniformBlockUpdateAfterBind 没有开启，则所有binding的descriptorType为VK_DESCRIPTOR_TYPE_INLINE_UNIFORM_BLOCK 且不能使用VK_DESCRIPTOR_BINDING_UPDATE_AFTER_BIND_BIT
		11.如果VkPhysicalDeviceAccelerationStructureFeaturesKHR::descriptorBindingAccelerationStructureUpdateAfterBind 没有开启，则所有binding的descriptorType为VK_DESCRIPTOR_TYPE_ACCELERATION_STRUCTURE_KHR 或者VK_DESCRIPTOR_TYPE_ACCELERATION_STRUCTURE_NV  且不能使用VK_DESCRIPTOR_BINDING_UPDATE_AFTER_BIND_BIT
		12.所有使用descriptor type 为VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT,VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC, 或者 VK_DESCRIPTOR_TYPE_STORAGE_BUFFER_DYNAMIC的binding 且不能使用VK_DESCRIPTOR_BINDING_UPDATE_AFTER_BIND_BIT
		13.如果VkPhysicalDeviceDescriptorIndexingFeatures::descriptorBindingUpdateUnusedWhilePending 没有开启，则所有pBindingFlags的元素不能含有VK_DESCRIPTOR_BINDING_UPDATE_UNUSED_WHILE_PENDING_BIT
		14.如果VkPhysicalDeviceDescriptorIndexingFeatures::descriptorBindingPartiallyBound 没有开启，则所有pBindingFlags的元素不能含有VK_DESCRIPTOR_BINDING_PARTIALLY_BOUND_BIT
		15.如果VkPhysicalDeviceDescriptorIndexingFeatures::descriptorBindingVariableDescriptorCount 没有开启，则所有pBindingFlags的元素不能含有VK_DESCRIPTOR_BINDING_VARIABLE_DESCRIPTOR_COUNT_BIT
		16.如果pBindingFlags 的一个元素包含VK_DESCRIPTOR_BINDING_VARIABLE_DESCRIPTOR_COUNT_BIT，则这个元素的descriptorType 不能为VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC 或者VK_DESCRIPTOR_TYPE_STORAGE_BUFFER_DYNAMIC

		*/



		//查询一个descriptor set layout是否能够被创建,需要查询的原因见p1263
		{
			VkDescriptorSetLayoutSupport support{};//等同于VkDescriptorSetLayoutSupportKHR
			support.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_SUPPORT;
				VkDescriptorSetVariableDescriptorCountLayoutSupport variableSupport{};//等同于VkDescriptorSetVariableDescriptorCountLayoutSupportEXT
				{
					variableSupport.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_VARIABLE_DESCRIPTOR_COUNT_LAYOUT_SUPPORT;
					variableSupport.pNext = nullptr;
					variableSupport.maxVariableDescriptorCount = 0;//指示在layout的最高编号binding中支持的最大descriptor数，如果该binding是可变大小的。如果layout的最高编号binding的描述符类型为VK_DESCRIPTOR_TYPE_INLINE_UNIFORM_BLOCK，那么maxVariableDescriptorCount表示binding支持的最大字节大小，如果该binding大小可变的。
				}
			support.pNext = &variableSupport;//可以包含VkDescriptorSetVariableDescriptorCountLayoutSupport
			support.supported = VK_FALSE;//指明这个descriptor set layout是否能够被创建的返回值

			//等用于vkGetDescriptorSetLayoutSupportKHR
			vkGetDescriptorSetLayoutSupport(device, & descriptorSetLayoutCreateInfo, & support);


		
		}


		//一些binding在着色器代码中声明形式如下：  详情见p1265
		/*
		//例如在着色器中声明如下的uniform变量：
		//
		// binding to a single sampled image descriptor in set 0
		//
		layout (set=0, binding=0) uniform texture2D mySampledImage;
		*/

		vkCreateDescriptorSetLayout(device, &descriptorSetLayoutCreateInfo, nullptr,&descriptorSetLayout);

		//销毁descriptor set layout
		vkDestroyDescriptorSetLayout(device, descriptorSetLayout, nullptr);//如果创建descriptor set layout时指定了VkAllocationCallbacks，则这里需要提供一个兼容的VkAllocationCallbacks，否则这里的pAllocator可以设置为NULL。

	}


	//pipeline layout
	VkPipelineLayout pipelineLayout{};
	{
	/*
	在pipeline中访问descriptor set通过pipeline layout，descriptor set layout和push constant ranges将绑定到一起形成一个描述可供pipeline 访问的完整的资源集的pipeline layout，这个pipeline layout用于确定shader stage和shader resource之间的接口
	*/
	
		VkDescriptorSetLayout validDescriptorSetLayout{};//假设一个有效的VkDescriptorSetLayout
		VkPushConstantRange pushConstantRange{};//假设一个有效的VkPushConstantRange
		pushConstantRange.offset = 0;//以字节为单位，必须为4的倍数，必须小于 VkPhysicalDeviceLimits::maxPushConstantsSize
		pushConstantRange.size = 1;//以字节为单位，必须为4的倍数
		pushConstantRange.stageFlags = VK_PIPELINE_STAGE_ALL_GRAPHICS_BIT;//是一组stage标志，它描述了将访问一系列push constant的着色器阶段。如果一个特定的阶段不包括在该范围中，那么从相应的着色器阶段访问该推送常数范围的成员将返回未定义的值。



		//一个pipeline layout中所能拥有的descriptor的数量存在一些限制，详情见p1278  Pipeline Layout Resource Limits
		VkPipelineLayoutCreateInfo pipelineLayoutCreateInfo{};
		pipelineLayoutCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
		pipelineLayoutCreateInfo.pNext = nullptr;
		pipelineLayoutCreateInfo.flags = 0;/*是 VkPipelineLayoutCreateFlagBits 组合值的位掩码，指明pipeline layout创建的选项
		VkPipelineLayoutCreateFlagBits:
		VK_PIPELINE_LAYOUT_CREATE_INDEPENDENT_SETS_BIT_EXT :  指明实现必须保证含有或者缺失特定descriptor set的属性不能影响pipeline layout的任何属性。这个允许链接pipeline libraries时可以不用创建一个含VK_PIPELINE_CREATE_LINK_TIME_OPTIMIZATION_BIT_EXT 的总的descriptor set中的一个子集
		*/
		pipelineLayoutCreateInfo.setLayoutCount = 1;//pSetLayouts 中元素个数
		pipelineLayoutCreateInfo.pSetLayouts = &validDescriptorSetLayout;//是一组 VkDescriptorSetLayout 对象数组的指针
		pipelineLayoutCreateInfo.pushConstantRangeCount = 1;//pPushConstantRanges 中元素个数
		pipelineLayoutCreateInfo.pPushConstantRanges = &pushConstantRange;//是一组 VkPushConstantRange 对象数组的指针，定义用在单个pipeline layout中的push constant range，pipeline layout 额外描述了pipeline每个stage可访问的push constant的数量
		/*
		VkPipelineLayoutCreateInfo有效用法:
		1.setLayoutCount 必须小于等于VkPhysicalDeviceLimits::maxBoundDescriptorSets
		2.所有以VK_DESCRIPTOR_SET_LAYOUT_CREATE_UPDATE_AFTER_BIND_POOL_BIT 创建的descriptor set layout 的其中descriptorType 为VK_DESCRIPTOR_TYPE_SAMPLER 和VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER的可供任何所给shader stages访问pSetLayouts的descriptor数量总和必须小于等于 VkPhysicalDeviceLimits::maxPerStageDescriptorSamplers
		3.所有以VK_DESCRIPTOR_SET_LAYOUT_CREATE_UPDATE_AFTER_BIND_POOL_BIT 创建的descriptor set layout 的其中descriptorType 为VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER 和VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC 的可供任何所给shader stages访问pSetLayouts的descriptor数量总和必须小于等于 VkPhysicalDeviceLimits::maxPerStageDescriptorUniformBuffers
		4.所有以VK_DESCRIPTOR_SET_LAYOUT_CREATE_UPDATE_AFTER_BIND_POOL_BIT 创建的descriptor set layout 的其中descriptorType 为VK_DESCRIPTOR_TYPE_STORAGE_BUFFER 和VK_DESCRIPTOR_TYPE_STORAGE_BUFFER_DYNAMIC 的可供任何所给shader stages访问pSetLayouts的descriptor数量总和必须小于等于 VkPhysicalDeviceLimits::maxPerStageDescriptorStorageBuffers
		5.所有以VK_DESCRIPTOR_SET_LAYOUT_CREATE_UPDATE_AFTER_BIND_POOL_BIT 创建的descriptor set layout 的其中descriptorType 为VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE, VK_DESCRIPTOR_TYPE_SAMPLE_WEIGHT_IMAGE_QCOM, VK_DESCRIPTOR_TYPE_BLOCK_MATCH_IMAGE_QCOM, 和VK_DESCRIPTOR_TYPE_UNIFORM_TEXEL_BUFFER 的可供任何所给shader stages访问pSetLayouts的descriptor数量总和必须小于等于 VkPhysicalDeviceLimits::maxPerStageDescriptorSampledImages
		6.所有以VK_DESCRIPTOR_SET_LAYOUT_CREATE_UPDATE_AFTER_BIND_POOL_BIT 创建的descriptor set layout 的其中descriptorType 为VK_DESCRIPTOR_TYPE_STORAGE_IMAGE 和VK_DESCRIPTOR_TYPE_STORAGE_TEXEL_BUFFER 的可供任何所给shader stages访问pSetLayouts的descriptor数量总和必须小于等于 VkPhysicalDeviceLimits::maxPerStageDescriptorStorageImages
		7.所有以VK_DESCRIPTOR_SET_LAYOUT_CREATE_UPDATE_AFTER_BIND_POOL_BIT 创建的descriptor set layout 的其中descriptorType 为VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT 的可供任何所给shader stages访问pSetLayouts的descriptor数量总和必须小于等于 VkPhysicalDeviceLimits::maxPerStageDescriptorInputAttachments
		8.所有以VK_DESCRIPTOR_SET_LAYOUT_CREATE_UPDATE_AFTER_BIND_POOL_BIT 创建的descriptor set layout 的其中descriptorType 为VK_DESCRIPTOR_TYPE_INLINE_UNIFORM_BLOCK 的可供任何所给shader stages访问pSetLayouts的descriptor数量总和必须小于等于 VkPhysicalDeviceInlineUniformBlockProperties::maxPerStageDescriptorInlineUniformBlocks
		9.所有descriptorType 为VK_DESCRIPTOR_TYPE_SAMPLER 以及VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER 的可供任何所给shader stages访问pSetLayouts的descriptor数量总和必须小于等于 VkPhysicalDeviceDescriptorIndexingProperties::maxPerStageDescriptorUpdateAfterBindSamp
		10.所有descriptorType 为VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER 以及VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC 的可供任何所给shader stages访问pSetLayouts的descriptor数量总和必须小于等于 VkPhysicalDeviceDescriptorIndexingProperties::maxPerStageDescriptorUpdateAfterBindUniformBuffers
		11.所有descriptorType 为VK_DESCRIPTOR_TYPE_STORAGE_BUFFER 以及VK_DESCRIPTOR_TYPE_STORAGE_BUFFER_DYNAMIC 的可供任何所给shader stages访问pSetLayouts的descriptor数量总和必须小于等于 VkPhysicalDeviceDescriptorIndexingProperties::maxPerStageDescriptorUpdateAfterBindStorageBuffers
		12.所有descriptorType 为VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE, 和VK_DESCRIPTOR_TYPE_UNIFORM_TEXEL_BUFFER 的可供任何所给shader stages访问pSetLayouts的descriptor数量总和必须小于等于 VkPhysicalDeviceDescriptorIndexingProperties::maxPerStageDescriptorUpdateAfterBindSampledImages
		13.所有descriptorType 为VK_DESCRIPTOR_TYPE_STORAGE_IMAGE 以及VK_DESCRIPTOR_TYPE_STORAGE_TEXEL_BUFFER 的可供任何所给shader stages访问pSetLayouts的descriptor数量总和必须小于等于 VkPhysicalDeviceDescriptorIndexingProperties::maxPerStageDescriptorUpdateAfterBindStorageImages
		14.所有descriptorType 为VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT 的可供任何所给shader stages访问pSetLayouts的descriptor数量总和必须小于等于 VkPhysicalDeviceDescriptorIndexingProperties::maxPerStageDescriptorUpdateAfterBindInputAttachments
		15.所有descriptorType 为VK_DESCRIPTOR_TYPE_INLINE_UNIFORM_BLOCK 的可供任何所给shader stages访问pSetLayouts的descriptor数量总和必须小于等于 VkPhysicalDeviceInlineUniformBlockProperties::maxPerStageDescriptorUpdateAfterBindInlineUniformBlocks
		16.所有以VK_DESCRIPTOR_SET_LAYOUT_CREATE_UPDATE_AFTER_BIND_POOL_BIT 创建的descriptor set layout 的其中descriptorType 为VK_DESCRIPTOR_TYPE_SAMPLER 和 VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER 的可供任何所给shader stages访问pSetLayouts的descriptor数量总和必须小于等于VkPhysicalDeviceLimits::maxDescriptorSetSamplers
		18.所有以VK_DESCRIPTOR_SET_LAYOUT_CREATE_UPDATE_AFTER_BIND_POOL_BIT 创建的descriptor set layout 的其中descriptorType 为VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER 的可供任何所给shader stages访问pSetLayouts的descriptor数量总和必须小于等于 VkPhysicalDeviceLimits::maxDescriptorSetUniformBuffers
		19.所有以VK_DESCRIPTOR_SET_LAYOUT_CREATE_UPDATE_AFTER_BIND_POOL_BIT 创建的descriptor set layout 的其中descriptorType 为VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC 的可供任何所给shader stages访问pSetLayouts的descriptor数量总和必须小于等于 VkPhysicalDeviceLimits::maxDescriptorSetUniformBuffersDynamic
		20.所有以VK_DESCRIPTOR_SET_LAYOUT_CREATE_UPDATE_AFTER_BIND_POOL_BIT 创建的descriptor set layout 的其中descriptorType 为VK_DESCRIPTOR_TYPE_STORAGE_BUFFER 的可供任何所给shader stages访问pSetLayouts的descriptor数量总和必须小于等于 VkPhysicalDeviceLimits::maxDescriptorSetStorageBuffers
		21.所有以VK_DESCRIPTOR_SET_LAYOUT_CREATE_UPDATE_AFTER_BIND_POOL_BIT 创建的descriptor set layout 的其中descriptorType 为VK_DESCRIPTOR_TYPE_STORAGE_BUFFER_DYNAMIC 的可供任何所给shader stages访问pSetLayouts的descriptor数量总和必须小于等于 VkPhysicalDeviceLimits::maxDescriptorSetStorageBuffersDynamic
		22.所有以VK_DESCRIPTOR_SET_LAYOUT_CREATE_UPDATE_AFTER_BIND_POOL_BIT 创建的descriptor set layout 的其中descriptorType 为VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER ，VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE 和VK_DESCRIPTOR_TYPE_UNIFORM_TEXEL_BUFFER  的可供任何所给shader stages访问pSetLayouts的descriptor数量总和必须小于等于 VkPhysicalDeviceLimits::maxDescriptorSetSampledImages
		23.所有以VK_DESCRIPTOR_SET_LAYOUT_CREATE_UPDATE_AFTER_BIND_POOL_BIT 创建的descriptor set layout 的其中descriptorType 为VK_DESCRIPTOR_TYPE_STORAGE_IMAGE 和VK_DESCRIPTOR_TYPE_STORAGE_TEXEL_BUFFER 的可供任何所给shader stages访问pSetLayouts的descriptor数量总和必须小于等于 VkPhysicalDeviceLimits::maxDescriptorSetStorageImages
		24.所有以VK_DESCRIPTOR_SET_LAYOUT_CREATE_UPDATE_AFTER_BIND_POOL_BIT 创建的descriptor set layout 的其中descriptorType 为VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT 的可供任何所给shader stages访问pSetLayouts的descriptor数量总和必须小于等于 VkPhysicalDeviceLimits::maxDescriptorSetInputAttachments
		25.所有以VK_DESCRIPTOR_SET_LAYOUT_CREATE_UPDATE_AFTER_BIND_POOL_BIT 创建的descriptor set layout 的其中descriptorType 为VK_DESCRIPTOR_TYPE_INLINE_UNIFORM_BLOCK 的可供任何所给shader stages访问pSetLayouts的binding数量总和必须小于等于 VkPhysicalDeviceInlineUniformBlockProperties::maxDescriptorSetInlineUniformBlocks
		26.所有descriptorType 为VK_DESCRIPTOR_TYPE_SAMPLER 和VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER 的可供所有shader stages访问pSetLayouts的descriptor数量总和必须小于等于 VkPhysicalDeviceDescriptorIndexingProperties::maxDescriptorSetUpdateAfterBindSamplers
		27.所有descriptorType 为VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER 的可供所有shader stages访问pSetLayouts的descriptor数量总和必须小于等于 VkPhysicalDeviceDescriptorIndexingProperties::maxDescriptorSetUpdateAfterBindUniformBuffers
		28.所有descriptorType 为VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC 的可供所有shader stages访问pSetLayouts的descriptor数量总和必须小于等于 VkPhysicalDeviceDescriptorIndexingProperties::maxDescriptorSetUpdateAfterBindUniformBuffersDynamic
		29.所有descriptorType 为VK_DESCRIPTOR_TYPE_STORAGE_BUFFER 的可供所有shader stages访问pSetLayouts的descriptor数量总和必须小于等于 VkPhysicalDeviceDescriptorIndexingProperties::maxDescriptorSetUpdateAfterBindStorageBuffers
		30.所有descriptorType 为VK_DESCRIPTOR_TYPE_STORAGE_BUFFER_DYNAMIC 的可供所有shader stages访问pSetLayouts的descriptor数量总和必须小于等于 VkPhysicalDeviceDescriptorIndexingProperties::maxDescriptorSetUpdateAfterBindStorageBuffersDynamic
		31.所有descriptorType 为VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER，VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE 和VK_DESCRIPTOR_TYPE_UNIFORM_TEXEL_BUFFER 的可供所有shader stages访问pSetLayouts的descriptor数量总和必须小于等于 VkPhysicalDeviceDescriptorIndexingProperties::maxDescriptorSetUpdateAfterBindSampledImages
		32.所有descriptorType 为VK_DESCRIPTOR_TYPE_STORAGE_IMAGE 和VK_DESCRIPTOR_TYPE_STORAGE_TEXEL_BUFFER 的可供所有shader stages访问pSetLayouts的descriptor数量总和必须小于等于 VkPhysicalDeviceDescriptorIndexingProperties::maxDescriptorSetUpdateAfterBindStorageImages
		33.所有descriptorType 为VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT 的可供所有shader stages访问pSetLayouts的descriptor数量总和必须小于等于 VkPhysicalDeviceDescriptorIndexingProperties::maxDescriptorSetUpdateAfterBindInputAttachments
		34.所有descriptorType 为VK_DESCRIPTOR_TYPE_INLINE_UNIFORM_BLOCK 的可供所有shader stages访问pSetLayouts的binding数量总和必须小于等于 VkPhysicalDeviceInlineUniformBlockProperties::maxDescriptorSetUpdateAfterBindInlineUniformBlocks
		35.所有descriptorType 为VK_DESCRIPTOR_TYPE_INLINE_UNIFORM_BLOCK 的可供所有shader stages访问pSetLayouts的descriptors数量总和必须小于等于 VkPhysicalDeviceVulkan13Properties::maxInlineUniformTotalSize
		36.任何pPushConstantRanges 中的两个元素的stageFlags不能含有相同的stage
		37.pSetLayout不能含有超过一个VK_DESCRIPTOR_SET_LAYOUT_CREATE_PUSH_DESCRIPTOR_BIT_KHR创建的descriptor set layout
		38.所有以VK_DESCRIPTOR_SET_LAYOUT_CREATE_UPDATE_AFTER_BIND_POOL_BIT 创建的descriptor set layout 的其中descriptorType 为VK_DESCRIPTOR_TYPE_ACCELERATION_STRUCTURE_KHR 的可供任何所给shader stages访问pSetLayouts的binding数量总和必须小于等于 VkPhysicalDeviceAccelerationStructurePropertiesKHR::maxPerStageDescriptorAccelerationStructures
		39.所有descriptorType 为VK_DESCRIPTOR_TYPE_ACCELERATION_STRUCTURE_KHR 的可供任何所给shader stages访问pSetLayouts的binding数量总和必须小于等于 VkPhysicalDeviceAccelerationStructurePropertiesKHR::maxPerStageDescriptorUpdateAfterBindAccelerationStructures
		39.所有以VK_DESCRIPTOR_SET_LAYOUT_CREATE_UPDATE_AFTER_BIND_POOL_BIT 创建的descriptor set layout 的其中descriptorType 为VK_DESCRIPTOR_TYPE_ACCELERATION_STRUCTURE_KHR 的可供所有shader stages访问pSetLayouts的binding数量总和必须小于等于 VkPhysicalDeviceAccelerationStructurePropertiesKHR::maxDescriptorSetAccelerationStructures
		40.所有descriptorType 为VK_DESCRIPTOR_TYPE_ACCELERATION_STRUCTURE_KHR 的可供任何所给shader stages访问pSetLayouts的binding数量总和必须小于等于 VkPhysicalDeviceAccelerationStructurePropertiesKHR::maxDescriptorSetUpdateAfterBindA
		41.所有descriptorType 为VK_DESCRIPTOR_TYPE_ACCELERATION_STRUCTURE_NV 的可供所有shader stages访问pSetLayouts的binding数量总和必须小于等于 VkPhysicalDeviceRayTracingPropertiesNV::maxDescriptorSetAccelerationStructures
		42.pImmutableSamplers 中以VK_SAMPLER_CREATE_SUBSAMPLED_BIT_EXT 或者VK_SAMPLER_CREATE_SUBSAMPLED_COARSE_RECONSTRUCTION_BIT_EXT 创建所有shader stages以及所有pSetLayouts中的sampler 数量总和必须小于等于 VkPhysicalDeviceFragmentDensityMap2PropertiesEXT::maxDescriptorSetSubsampledSamplers
		43.pSetLayouts 中的任何元素不能以VK_DESCRIPTOR_SET_LAYOUT_CREATE_HOST_ONLY_POOL_BIT_EXT 创建
		44.如果graphicsPipelineLibrary 未启用，pSetLayouts 中的每个元素必须是有效的VkDescriptorSetLayout对象
		45.如果pSetLayouts 中的任何元素以VK_DESCRIPTOR_SET_LAYOUT_CREATE_DESCRIPTOR_BUFFER_BIT_EXT 创建，则pSetLayouts 中的所有元素必须以VK_DESCRIPTOR_SET_LAYOUT_CREATE_DESCRIPTOR_BUFFER_BIT_EXT 创建

		*/



		vkCreatePipelineLayout(device, &pipelineLayoutCreateInfo, nullptr, &pipelineLayout);
	

		vkDestroyPipelineLayout(device, pipelineLayout, nullptr);

	}


	//Pipeline Layout Compatibility 见p1280
	//主要是为了在绑定pipeline时可以继续使用已经绑定的pipelineLayout，而不用重新创建pipelineLayout，从而提高效率。但是重新绑定了pipeline后该pipelineLayout中的descriptor Set是否对当前pipeline有效还需要看pipelineLayout的兼容性


	// Allocation of Descriptor Sets 分配descriptor set
	{
		//descriptor pool容纳一批descriptors，descriptor sets可以从中进行分配
		//详细信息见p1284
		VkDescriptorPool descriptorPool{};
		VkDescriptorPoolCreateInfo descriptorPoolCreateInfo{};
		descriptorPoolCreateInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
			DescriptorPoolCreateInfoEXT descriptorPoolCreateInfoEXT{};
		descriptorPoolCreateInfo.pNext = &descriptorPoolCreateInfoEXT.descriptorPoolInlineUniformBlockCreateInfo;//可以含有 VkDescriptorPoolInlineUniformBlockCreateInfo 或者 VkMutableDescriptorTypeCreateInfoEXT
		descriptorPoolCreateInfo.flags = VK_DESCRIPTOR_POOL_CREATE_UPDATE_AFTER_BIND_BIT;//是 VkDescriptorPoolCreateFlagBits 组合值的位掩码，指定pool上支持的特定的选项 
		/*
		VkDescriptorPoolCreateFlagBits:
		VK_DESCRIPTOR_POOL_CREATE_FREE_DESCRIPTOR_SET_BIT : 指明释放descriptor sets的分配是独立的，即可以使用vkAllocateDescriptorSets，vkFreeDescriptorSets，vkResetDescriptorPool，否则只能使用vkAllocateDescriptorSets以及vkResetDescriptorPool
		VK_DESCRIPTOR_POOL_CREATE_UPDATE_AFTER_BIND_BIT:  指明这个pool上分配的descriptor set可以含有包含VK_DESCRIPTOR_BINDING_UPDATE_AFTER_BIND_BIT的binding，从含有VK_DESCRIPTOR_POOL_CREATE_UPDATE_AFTER_BIND_BIT创建的pool上分配一个其binding不含VK_DESCRIPTOR_BINDING_UPDATE_AFTER_BIND_BIT 的descriptor set是有效的
		VK_DESCRIPTOR_POOL_CREATE_HOST_ONLY_BIT_EXT:  指明这个pool上分配的descriptor set只能在主机内存中分配，并且不能被绑定。类似于不含有该标志分配的descriptor sets，应用程序可以在这个pool分配的descriptor sets间进行拷贝操作。从这个pool中分配的descriptor sets部分地免除了在vkUpdateDescriptorSetWithTemplateKHR和vkUpdateDescriptorSets中的外部同步要求。descriptor sets及其descriptor可以在不同的线程中同时更新，尽管相同的descriptor不能被两个线程同时更新。
		VK_DESCRIPTOR_POOL_CREATE_ALLOW_OVERALLOCATION_SETS_BIT_NV:  指定实现应该允许应用从该pool中分配超过VkDescriptorPoolCreateInfo::maxSets 的descriptor set，实现应该使用maxSets 来分配初始的descriptor set，且maxSets 可以指定为0
		VK_DESCRIPTOR_POOL_CREATE_ALLOW_OVERALLOCATION_POOLS_BIT_NV:  指定实现应该允许pool分配超过任何VkDescriptorPoolCreateInfo::poolSizeCount以及VkDescriptorPoolCreateInfo::pPoolSizes指定的元素中VkDescriptorPoolSize::descriptorCount的descriptor,实现将用每个descriptor type的descriptorCount 分配初始的descriptor set，且poolSizeCount 可以指定为0，pPoolSizes中元素的descriptorCount 可以指定为0

		*/
		descriptorPoolCreateInfo.poolSizeCount = 1;// pPoolSizes的元素个数
			VkDescriptorPoolSize descriptorPoolSize{};
			{
				descriptorPoolSize.descriptorCount = 1;//这个类型可以分配的descriptor数量，必须大于0，如果type为VK_DESCRIPTOR_TYPE_INLINE_UNIFORM_BLOCK，则descriptorCount为这个类型可以分配的字节数量且必须是4的倍数
				descriptorPoolSize.type = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;//descriptor类型
			}

		descriptorPoolCreateInfo.pPoolSizes = &descriptorPoolSize;//一组VkDescriptorPoolSize 的数组指针，每一个元素描述了pool中可以分配的descriptor的类型和数量
		descriptorPoolCreateInfo.maxSets = 1;//是从这个pool上能够分配的descriptor set的最大数量
		/*
		VkDescriptorPoolCreateInfo有效用法:
		1.如果descriptorPoolOverallocation 特性没有开启，或者flags不包含VK_DESCRIPTOR_POOL_CREATE_ALLOW_OVERALLOCATION_SETS_BIT_NV，则maxSets 必须大于0
		2.如果flags包含VK_DESCRIPTOR_POOL_CREATE_ALLOW_OVERALLOCATION_SETS_BIT_NV或者VK_DESCRIPTOR_POOL_CREATE_ALLOW_OVERALLOCATION_POOLS_BIT_NV ，则descriptorPoolOverallocation 特性必须开启
		3.如果flags包含VK_DESCRIPTOR_POOL_CREATE_HOST_ONLY_BIT_EXT，则就不能包含VK_DESCRIPTOR_POOL_CREATE_UPDATE_AFTER_BIND_BIT
		4.如果VkPhysicalDeviceMutableDescriptorTypeFeaturesEXT::mutableDescriptorType 没有开启，则pPoolSizes 中不能包含descriptorType为 VK_DESCRIPTOR_TYPE_MUTABLE_EXT的元素
		5.如果flags含有VK_DESCRIPTOR_POOL_CREATE_HOST_ONLY_BIT_EXT，则VkPhysicalDeviceMutableDescriptorTypeFeaturesEXT::mutableDescriptorType 必须开启
		6.如果pPoolSizes 包含descriptorType 为VK_DESCRIPTOR_TYPE_MUTABLE_EXT 的元素，则pPoolSizes中任何其他含有VK_DESCRIPTOR_TYPE_MUTABLE_EXT的元素其descriptor set支持的descriptor 类型不能与该元素的descriptor set支持的descriptor 类型部分重叠
		7.如果pPoolSizes 包含descriptorType 为VK_DESCRIPTOR_TYPE_INLINE_UNIFORM_BLOCK 的元素，则pNext中必须包含一个maxInlineUniformBlockBindings 不为0的VkDescriptorPoolInlineUniformBlockCreateInfo结构体

		*/


		//VkDescriptorPoolInlineUniformBlockCreateInfo    等同于VkDescriptorPoolInlineUniformBlockCreateInfoEXT
		//为了创建含有 inline uniform block binding的descriptor set，需要在VkDescriptorPoolCreateInfo的pNext中包含VkDescriptorPoolInlineUniformBlockCreateInfo结构体来指明descriptor pool的inline uniform block binding 容量
		VkDescriptorPoolInlineUniformBlockCreateInfo& inlineUniformBlockCreateInfo = descriptorPoolCreateInfoEXT.descriptorPoolInlineUniformBlockCreateInfo;
		inlineUniformBlockCreateInfo.maxInlineUniformBlockBindings = 1;//inline uniform block binding的最大数量



		vkCreateDescriptorPool(device, &descriptorPoolCreateInfo, nullptr, &descriptorPool);


		vkDestroyDescriptorPool(device, descriptorPool, nullptr);/*
		vkDestroyDescriptorPool有效用法:
		1.引用到该descriptorPool（通过任何分配的descriptor sets）的已经提交的command buffer必须已经完成执行
		2.如果创建descriptorPool 提供了VkAllocationCallbacks，则这里需要提供一个兼容的VkAllocationCallbacks，否则设置为NULL

		*/

		VkDescriptorSetAllocateInfo descriptorSetAllocateInfo{};
		descriptorSetAllocateInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
		VkDescriptorSetVariableDescriptorCountAllocateInfo descriptorSetVariableDescriptorCountAllocateInfo{};//指定 variable-sized descriptor bindings中的一组descriptor count，每个结构体对应一个descriptor set，等价于VkDescriptorSetVariableDescriptorCountAllocateInfoEXT
		{
			descriptorSetVariableDescriptorCountAllocateInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_VARIABLE_DESCRIPTOR_COUNT_ALLOCATE_INFO;
			descriptorSetVariableDescriptorCountAllocateInfo.pNext = nullptr;
			descriptorSetVariableDescriptorCountAllocateInfo.descriptorSetCount = 1;//pDescriptorCounts 中的元素个数，如果不为0则必须等于VkDescriptorSetAllocateInfo::descriptorSetCount
				uint32_t descriptorCount = 10;//每一个descriptor set的variable descriptor count
			descriptorSetVariableDescriptorCountAllocateInfo.pDescriptorCounts = &descriptorCount;//为给定descriptor set上每个 variable-sized descriptor binding 上的descriptor 数量的数组指针
		}

		descriptorSetAllocateInfo.pNext = &descriptorSetVariableDescriptorCountAllocateInfo;//可以含有一个VkDescriptorSetVariableDescriptorCountAllocateInfo
		descriptorSetAllocateInfo.descriptorPool = VkDescriptorPool{/*假设这是一个有效的VkDescriptorPool*/ };//指明descriptor set从哪个pool中分配
		descriptorSetAllocateInfo.descriptorSetCount = 1;//要分配的descriptor set的数量
		descriptorSetAllocateInfo.pSetLayouts = &descriptorSetLayout;//是一组VkDescriptorSetLayout 的数组指针，每一个元素指向一个descriptor set layout，描述了要分配descriptor set的布局
		/*
		VkDescriptorSetAllocateInfo有效用法:
		1.如果VK_KHR_maintenance1 拓展没有开启且VkPhysicalDeviceProperties::apiVersion 小于Vulkan 1.1，则（1）descriptorSetCount 不能大于descriptorPool 中可分配的descriptor set数量
																										 （2）descriptorPool 中剩余的descriptor capacity 必须足够分配指定layout 的descriptor set。
		2.pSetLayouts的每个元素不能以VK_DESCRIPTOR_SET_LAYOUT_CREATE_PUSH_DESCRIPTOR_BIT_KHR 创建
		3.如果pSetLayouts 的任意元素以VK_DESCRIPTOR_SET_LAYOUT_CREATE_UPDATE_AFTER_BIND_POOL_BIT 创建，则descriptorPool 必须以VK_DESCRIPTOR_POOL_CREATE_UPDATE_AFTER_BIND_BIT 创建
		4.如果pSetLayouts[i] 以其pBindingFlags 含有VK_DESCRIPTOR_BINDING_VARIABLE_DESCRIPTOR_COUNT_BIT，且其pNext中含有一个descriptorSetCount 不为0的VkDescriptorSetVariableDescriptorCountAllocateInfo，则VkDescriptorSetVariableDescriptorCountAllocateInfo::pDescriptorCounts[i]
																	的值必须小于或等于VkDescriptorSetLayoutBinding::descriptorCount 对应创建pSetLayouts[i]的binding的的数量。
		5.如果pSetLayouts 的任何元素以VK_DESCRIPTOR_SET_LAYOUT_CREATE_HOST_ONLY_POOL_BIT_EXT，则descriptorPool 必须以VK_DESCRIPTOR_POOL_CREATE_HOST_ONLY_BIT_EXT 创建
		6.pSetLayouts中的每个元素不能以VK_DESCRIPTOR_SET_LAYOUT_CREATE_DESCRIPTOR_BUFFER_BIT_EXT 创建

		*/


		VkDescriptorSet descriptorSet{};
		//分配descriptor set
		vkAllocateDescriptorSets(device, &descriptorSetAllocateInfo, &descriptorSet);//详情见p1290


		//释放descriptor set
		vkFreeDescriptorSets(device, descriptorPool, 1, &descriptorSet);/*
		vkFreeDescriptorSets有效用法:
		1.引用到pDescriptorSets 的任何元素的已经提交的command buffer必须已经完成执行
		2.pDescriptorSets 必须是 descriptorSetCount 个有效的VkDescriptorSet或者VK_NULL_HANDLE
		3.descriptorPool 必须以VK_DESCRIPTOR_POOL_CREATE_FREE_DESCRIPTOR_SET_BIT创建
		*/


		//将pool上分配的所有descriptor set回收到pool而不是单独释放一个descriptor set
		vkResetDescriptorPool(device, descriptorPool, 0);/* 所有引用到descriptorPool（通过任何分配的descriptor sets）的操作必须已经完成   */

	}


	//Descriptor Set Updates 更新descriptor set
	{

		//分配了descriptor set后便可通过写入或者拷贝来完成descriptor set的更新

		//write  
		// VkWriteDescriptorSet的 pImageInfo, pBufferInfo, 或者 pTexelBufferView三个中只使用一个，或者都不使用，在 VK_DESCRIPTOR_TYPE_INLINE_UNIFORM_BLOCK,VK_DESCRIPTOR_TYPE_ACCELERATION_STRUCTURE_KHR或者VK_DESCRIPTOR_TYPE_ACCELERATION_STRUCTURE_NV情况下
		//使用 VkWriteDescriptorSetInlineUniformBlock， VkWriteDescriptorSetAccelerationStructureKHR或者 VkWriteDescriptorSetAccelerationStructureNV 来指定相关参数
		VkWriteDescriptorSet writeDescriptorSet{};
		writeDescriptorSet.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
			WriteDescriptorSetEXT writeDescriptorSetEXT{};
		writeDescriptorSet.pNext = &writeDescriptorSetEXT.writeDescriptorSetAccelerationStructureKHR;
		writeDescriptorSet.descriptorCount = 1;//这个binding中从dstArrayElement开始要更新的descriptor数量，如果通过dstSet和dstBinding 指定的binding的descriptorType为 VK_DESCRIPTOR_TYPE_INLINE_UNIFORM_BLOCK，则这个指明为这个binding中要更新的字节大小，否则为pImageInfo中的元素个数， pBufferInfo中的元素个数， pTexelBufferView中的元素个数，VkWriteDescriptorSetInlineUniformBlock.dataSize或者VkWriteDescriptorSetAccelerationStructureKHR.accelerationStructureCount中的一个
		writeDescriptorSet.descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;/*是一个VkDescriptorType 指明pImageInfo, pBufferInfo, 或者 pTexelBufferView中 descriptor的类型，如果通过dstSet和dstBinding 指定的binding的descriptorType不为 VK_DESCRIPTOR_TYPE_MUTABLE_EXT，则这个类型必须和其相同
		VkDescriptorType:

        VK_DESCRIPTOR_TYPE_SAMPLER:  指明一个 sampler descriptor.
        VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER:  指明一个 combined image sampler descriptor.
        VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE:  指明一个 sampled image descriptor.
        VK_DESCRIPTOR_TYPE_STORAGE_IMAGE:  指明一个 storage image descriptor.
        VK_DESCRIPTOR_TYPE_UNIFORM_TEXEL_BUFFER:  指明一个 uniform texel buffer descriptor.
        VK_DESCRIPTOR_TYPE_STORAGE_TEXEL_BUFFER:  指明一个 storage texel buffer descriptor.
        VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER:  指明一个 uniform buffer descriptor.
        VK_DESCRIPTOR_TYPE_STORAGE_BUFFER:  指明一个 storage buffer descriptor.
        VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC:  指明一个 dynamic uniform buffer descriptor.
        VK_DESCRIPTOR_TYPE_STORAGE_BUFFER_DYNAMIC:  指明一个 dynamic storage buffer descriptor.
        VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT:  指明一个n input attachment descriptor.
        VK_DESCRIPTOR_TYPE_INLINE_UNIFORM_BLOCK:  指明一个 inline uniform block.
        VK_DESCRIPTOR_TYPE_MUTABLE_EXT:  指明一个 descriptor of mutable type.
        VK_DESCRIPTOR_TYPE_SAMPLE_WEIGHT_IMAGE_QCOM:  指明一个 sampled weight image descriptor.
        VK_DESCRIPTOR_TYPE_BLOCK_MATCH_IMAGE_QCOM:  指明一个 block matching image descriptor.
		
		*/
		
		writeDescriptorSet.dstArrayElement = 0;//这个binding中descriptor数组中的起始元素，如果通过dstSet和dstBinding 指定的binding的descriptorType为 VK_DESCRIPTOR_TYPE_INLINE_UNIFORM_BLOCK，则这个指明为这个binding中开始字节的偏移量
		writeDescriptorSet.dstBinding = 0;//要更新的descriptor set的 descriptor binding
		writeDescriptorSet.dstSet = VkDescriptorSet{/*假设这是一个有效的VkDescriptorSet*/ };//要更新的descriptor set
			VkDescriptorBufferInfo descriptorBufferInfo{};
			{
				descriptorBufferInfo.buffer = VkBuffer{/*假设这是一个有效的VkBuffer*/ };//为VK_NULL_HANDLE或者指定buffer资源，如果 nullDescriptor没有开启则不能为VK_NULL_HANDLE，如果为VK_NULL_HANDLE，则offset必须为0，range必须为VK_WHOLE_SIZE
				descriptorBufferInfo.offset = 0;//指明buffer的起始字节偏移量，通过这个descriptor访问buffer将基于这个偏移量的相对地址进行访问，必须小于buffer的大小
				descriptorBufferInfo.range = 1;//指明这个descriptor要更新的buffer的字节数，如果为VK_WHOLE_SIZE则表示从offset开始到buffer结束，如果设置为VK_WHOLE_SIZE，则有效范围（offset到结束）不能大于 maxUniformBufferRange 或者 maxStorageBufferRange，且0 < range <= buffer大小 - offset
			}
		writeDescriptorSet.pBufferInfo = &descriptorBufferInfo;//是一组   VkDescriptorBufferInfo 的数组地址
			VkDescriptorImageInfo descriptorImageInfo{};
			{
				descriptorImageInfo.sampler = VkSampler{/*假设这是一个有效的VkSampler*/ };//是一个VkSampler句柄，使用在VK_DESCRIPTOR_TYPE_SAMPLER 以及 VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER类型且没有使用immutable samplers 的descriptor的更新中
				descriptorImageInfo.imageView = VkImageView{/*假设这是一个有效的VkImageView*/ };//为VK_NULL_HANDLE或者VkImageView句柄，使用在VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE, VK_DESCRIPTOR_TYPE_STORAGE_IMAGE, VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, 以及 VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT 类型的descriptor的更新中
				descriptorImageInfo.imageLayout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;//是在descriptor访问时从imageView访问的image subresource的VkImageLayout布局，用在VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE, VK_DESCRIPTOR_TYPE_STORAGE_IMAGE, VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, 以及 VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT类型的descriptor的更新中
				/*
				VkDescriptorImageInfo有效用法:
				1.imageView 不能是从3D image上创建的2D array image view
				2.如果imageView 是从3D image上创建的2D image view，则（1）descriptorType必须为 VK_DESCRIPTOR_TYPE_STORAGE_IMAGE, VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE, 或者 VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER
																	 （2）image必须以VK_IMAGE_CREATE_2D_VIEW_COMPATIBLE_BIT_EXT创建
				3.如果image2DViewOf3D 特性没有开启或者descriptorType 不是 VK_DESCRIPTOR_TYPE_STORAGE_IMAGE，VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE 或者 VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER，则imageView 不能是从3D image上创建的2D image view
				
				4.如果imageView从一个depth/stencil image 上创建，则用来创建imageView的aspectMask 必须包含VK_IMAGE_ASPECT_DEPTH_BIT 或者 VK_IMAGE_ASPECT_STENCIL_BIT 中的一个
				5.如果imageLayout 为VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL，则用来创建imageView的aspectMask 不能包含VK_IMAGE_ASPECT_DEPTH_BIT 或者 VK_IMAGE_ASPECT_STENCIL_BIT 中的一个
				6.如果imageLayout 为VK_IMAGE_LAYOUT_DEPTH_READ_ONLY_STENCIL_ATTACHMENT_OPTIMAL,
									VK_IMAGE_LAYOUT_DEPTH_ATTACHMENT_STENCIL_READ_ONLY_OPTIMAL,
									VK_IMAGE_LAYOUT_DEPTH_READ_ONLY_OPTIMAL, VK_IMAGE_LAYOUT_DEPTH_ATTACHMENT_OPTIMAL,
									VK_IMAGE_LAYOUT_STENCIL_READ_ONLY_OPTIMAL, VK_IMAGE_LAYOUT_STENCIL_ATTACHMENT_OPTIMAL,
									VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL 或者
									VK_IMAGE_LAYOUT_DEPTH_STENCIL_READ_ONLY_OPTIMAL，则用来创建imageView的aspectMask 不能包含VK_IMAGE_ASPECT_COLOR_BIT
				7.在descriptor访问的时候 imageLayout 必须和实际的从imageView可访问的image subresource的VkImageLayout布局匹配，参见匹配规则 image layout matching rules p1083
				8.如果使用了sampler且image的VkFormat是一个multi-planar format，则image必须以VK_IMAGE_CREATE_MUTABLE_FORMAT_BIT创建，且imageView创建的aspectMask必须是一个有效的multi-planar aspect mask比特位
				9.如果VK_KHR_portability_subset 拓展开启，且VkPhysicalDevicePortabilitySubsetFeaturesKHR::mutableComparisonSamplers为 VK_FALSE，则sampler必须以VkSamplerCreateInfo::compareEnable设置为VK_FALSE创建

				*/
			}
		writeDescriptorSet.pImageInfo = &descriptorImageInfo;//是一组 VkDescriptorImageInfo 的数组地址
			VkBufferView texelBufferView{};
		writeDescriptorSet.pTexelBufferView = &texelBufferView;//是一组  VkBufferView 的数组地址
		/*
		VkWriteDescriptorSet有效用法:
		1.dstBinding 必须小于等于dstSet的 descriptor set layout创建时指明的最大的binding的数量
		2.dstBinding 必须是一个含有非0descriptorCount值的binding
		3.所有通过单独的VkWriteDescriptorSet更新的连续的binding，除了那些descriptorCount为0的binding，这些binding必须有相同的descriptorType 以及 stageFlags，必须全部使用或者不使用immutable samplers
		4.descriptorType必须和dstSet中的dstBinding匹配
		5.dstSet必须是有效的 VkDescriptorSet句柄
		6.dstArrayElement + descriptorCount必须小于等于dstBinding中指定的descriptor数组中元素的数量，以及consecutive binding updates p1301中描述的连续binding中所有可用的descriptor的总数
		7.如果descriptorType为VK_DESCRIPTOR_TYPE_INLINE_UNIFORM_BLOCK，则dstArrayElement以及descriptorCount 必须是4的整数倍
		8.如果descriptorType为VK_DESCRIPTOR_TYPE_UNIFORM_TEXEL_BUFFER 或者VK_DESCRIPTOR_TYPE_STORAGE_TEXEL_BUFFER，则（1）pTexelBufferView中的元素必须是有效的VkBufferView句柄或者VK_NULL_HANDLE
																													 （2）如果nullDescriptor 特性没有开启，则pTexelBufferView中的每个元素就不能为VK_NULL_HANDLE
		9.如果descriptorType为VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, VK_DESCRIPTOR_TYPE_STORAGE_BUFFER, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC, 或者 VK_DESCRIPTOR_TYPE_STORAGE_BUFFER_DYNAMIC，pBufferInfo 必须是descriptorCount个有效VkDescriptorBufferInfo的数组指针
		10.如果descriptorType为VK_DESCRIPTOR_TYPE_SAMPLER 或者VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER，且dstSet不以一个 descriptorType类型的dstBinding含有immutable samplers的layout分配，则pImageInfo中的每个元素的sampler必须是一个有效的VkSampler
		11.如果descriptorType为VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER，VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE 或者VK_DESCRIPTOR_TYPE_STORAGE_IMAGE，则（1）pImageInfo中的元素的imageView 必须是有效的VkImageView或者VK_NULL_HANDLE
																																				   （2）如果nullDescriptor特性没有开启，则pImageInfo中的元素的imageView 不能为VK_NULL_HANDLE
		12.如果descriptorType为VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT，则pImageInfo中的元素的imageView 不能为VK_NULL_HANDLE
		13.如果descriptorType为VK_DESCRIPTOR_TYPE_INLINE_UNIFORM_BLOCK，则pNext中必须包含一个dataSize 等于descriptorCount的VkWriteDescriptorSetInlineUniformBlock
		14.如果descriptorType为VK_DESCRIPTOR_TYPE_ACCELERATION_STRUCTURE_KHR，则pNext中必须包含一个accelerationStructureCount 等于descriptorCount的VkWriteDescriptorSetAccelerationStructureKHR
		15.如果descriptorType为VK_DESCRIPTOR_TYPE_ACCELERATION_STRUCTURE_NV，则pNext中必须包含一个accelerationStructureCount 等于descriptorCount的VkWriteDescriptorSetAccelerationStructureNV
		16.如果descriptorType为VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE，则pImageInfo中的元素的imageView 不能以其pNext含有一个VkSamplerYcbcrConversionInfo 进行创建
		17.如果descriptorType为VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER，则（1）如果pImageInfo中的元素的imageView 以其pNext含有一个VkSamplerYcbcrConversionInfo 进行创建，则dstSet必须以dstBinding含有immutable samplers的layout进行创建，且对应的immutable samplers 必须和VkSamplerYcbcrConversionInfo中定义的相同
																			（2）如果dstSet不以dstBinding含有immutable samplers的layout进行创建，则pImageInfo 中的每个元素的对应到一个启用了sampler Y′CBCR conversion的immutable sampler的 imageView 必须以含有一个和对应immutable sampler相同定义的VkSamplerYcbcrConversionInfo 进行创建
																			（3）如果dstSet以dstBinding含有immutable samplers的layout进行创建，且这些samplers启用了sampler Y′CBCR conversion，则pImageInfo 中的每个元素的对应到一个启用了sampler Y′CBCR conversion的immutable sampler的 imageView 必须不能为VK_NULL_HANDLE
		18.如果descriptorType为VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER或者 VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC，则pBufferInfo中每个元素的 offset 必须为VkPhysicalDeviceLimits::minUniformBufferOffsetAlignment的倍数
		19.如果descriptorType为VK_DESCRIPTOR_TYPE_STORAGE_BUFFER或者 VK_DESCRIPTOR_TYPE_STORAGE_BUFFER_DYNAMIC，则pBufferInfo中每个元素的 offset 必须为VkPhysicalDeviceLimits::minStorageBufferOffsetAlignment的倍数
		20.如果descriptorType为VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER，VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC，VK_DESCRIPTOR_TYPE_STORAGE_BUFFER或者 VK_DESCRIPTOR_TYPE_STORAGE_BUFFER_DYNAMIC，且pBufferInfo中任何元素的buffer为non-sparse的，则buffer必须绑定到一个单独的完整的连续的VkDeviceMemory上
		21.如果descriptorType为VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER 或者 VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC，则pBufferInfo中任何元素的buffer必须以VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT 创建
		22.如果descriptorType为VK_DESCRIPTOR_TYPE_STORAGE_BUFFER 或者 VK_DESCRIPTOR_TYPE_STORAGE_BUFFER_DYNAMIC，则（1）pBufferInfo中任何元素的buffer必须以VK_BUFFER_USAGE_STORAGE_BUFFER_BIT 创建
																												   （2）则pBufferInfo中任何元素的range 必须小于等于 VkPhysicalDeviceLimits::maxUniformBufferRange，或者为VK_WHOLE_SIZE
		23.如果descriptorType为VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER 或者 VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC，且（1）pBufferInfo中任何元素的buffer必须以VK_BUFFER_USAGE_STORAGE_BUFFER_BIT 创建
																												   （2）则pBufferInfo中任何元素的range 必须小于等于 VkPhysicalDeviceLimits::maxStorageBufferRange，或者为VK_WHOLE_SIZE
		24.如果descriptorType为VK_DESCRIPTOR_TYPE_UNIFORM_TEXEL_BUFFER，则pTexelBufferView 的元素创建必须含有VK_BUFFER_USAGE_UNIFORM_TEXEL_BUFFER_BIT
		25.如果descriptorType为VK_DESCRIPTOR_TYPE_STORAGE_TEXEL_BUFFER，则pTexelBufferView 的元素创建必须含有VK_BUFFER_USAGE_STORAGE_TEXEL_BUFFER_BIT
		26.如果descriptorType为VK_DESCRIPTOR_TYPE_STORAGE_IMAGE 或者VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT，则pImageInfo中每个元素的imageView 必须以identity swizzle 创建
		27.如果descriptorType为VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE 或者VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER，则pImageInfo中每个元素的imageView 必须以VK_IMAGE_USAGE_SAMPLED_BIT 创建
		28.如果descriptorType为VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE，则pImageInfo中每个元素的imageLayout 必须是一个列举在Sampled Image p1243中的元素
		29.如果descriptorType为VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER，则pImageInfo中每个元素的imageLayout 必须是一个列举在Combined Image Sampler p1243中的元素
		30.如果descriptorType为VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT，则（1）pImageInfo中每个元素的imageLayout 必须是一个列举在Input Attachment p1246中的元素
																	  （2）pImageInfo中每个元素的imageView 必须以VK_IMAGE_USAGE_INPUT_ATTACHMENT_BIT创建
		31.如果descriptorType为VK_DESCRIPTOR_TYPE_STORAGE_IMAGE，则（1）pImageInfo中每个元素的imageLayout 必须是一个列举在Storage Image p1242中的元素
																   （2）pImageInfo中每个元素的imageView 必须以VK_IMAGE_USAGE_STORAGE_BIT创建
																   （3）pImageInfo中每个元素的imageView 必须以其pNext中不含有一个VkImageViewMinLodCreateInfoEXT 或者 含有一个minLod为0的VkImageViewMinLodCreateInfoEXT 创建
		32.如果descriptorType为VK_DESCRIPTOR_TYPE_SAMPLER，则dstSet 不能以一个dstBinding含有immutable samplers 的layout分配
		33.如果dstSet的dstBinding所对的VkDescriptorSetLayoutBinding是VK_DESCRIPTOR_TYPE_MUTABLE_EXT类型的，则新的激活的descriptorType 必须列举在dstBinding对应的pMutableDescriptorTypeLists中
		34.如果descriptorType为VK_DESCRIPTOR_TYPE_SAMPLE_WEIGHT_IMAGE_QCOM，则（1）pImageInfo中每个元素的imageView 必须以VK_IMAGE_USAGE_SAMPLE_WEIGHT_BIT_QCOM 创建
		35.如果descriptorType为VK_DESCRIPTOR_TYPE_BLOCK_MATCH_IMAGE_QCOM，则（1）pImageInfo中每个元素的imageView 必须以VK_IMAGE_USAGE_SAMPLE_BLOCK_MATCH_BIT_QCOM 创建

		*/


		//VkWriteDescriptorSetInlineUniformBlock
		//指定要写入到descriptor set的数据当descriptor类型为VK_DESCRIPTOR_TYPE_INLINE_UNIFORM_BLOCK
		VkWriteDescriptorSetInlineUniformBlock& writeDescriptorSetInlineUniformBlock = writeDescriptorSetEXT.writeDescriptorSetInlineUniformBlock;
		writeDescriptorSetInlineUniformBlock.dataSize = 0;//指明pData中inline uniform block 数据的字节数，必须为4的倍数
		writeDescriptorSetInlineUniformBlock.pData = nullptr;//要写入到descriptor的inline uniform block 数据


		//VkWriteDescriptorSetAccelerationStructureKHR
		VkWriteDescriptorSetAccelerationStructureKHR& writeDescriptorSetAccelerationStructureKHR = writeDescriptorSetEXT.writeDescriptorSetAccelerationStructureKHR;
		writeDescriptorSetAccelerationStructureKHR.accelerationStructureCount = 0;//是pAccelerationStructures中加速结构元素个数
		writeDescriptorSetAccelerationStructureKHR.pAccelerationStructures = VK_NULL_HANDLE;//是一组VkAccelerationStructureKHR 的数组指针，指明要更新的加速结构
		/*
		VkWriteDescriptorSetAccelerationStructureKHR有效用法:
		1.accelerationStructureCount 必须等于被拓展的VkWriteDescriptorSet的descriptorCount
		2.pAccelerationStructures的每个加速结构必须以VK_ACCELERATION_STRUCTURE_TYPE_TOP_LEVEL_KHR 或者VK_ACCELERATION_STRUCTURE_TYPE_GENERIC_KHR类型创建
		3.如果nullDescriptor 特性没有开启，则pAccelerationStructures中的每个元素不能为VK_NULL_HANDLE
		*/

		//VkWriteDescriptorSetAccelerationStructureNV
		VkWriteDescriptorSetAccelerationStructureNV& writeDescriptorSetAccelerationStructureNV = writeDescriptorSetEXT.writeDescriptorSetAccelerationStructureNV;
		writeDescriptorSetAccelerationStructureNV.accelerationStructureCount = 0;//是pAccelerationStructures中加速结构元素个数
		writeDescriptorSetAccelerationStructureNV.pAccelerationStructures = VK_NULL_HANDLE;//是一组VkAccelerationStructureKHR 的数组指针，指明要更新的加速结构
		/*
		VkWriteDescriptorSetAccelerationStructureNV有效用法:
		1.accelerationStructureCount 必须等于被拓展的VkWriteDescriptorSet的descriptorCount
		2.pAccelerationStructures的每个加速结构必须以VK_ACCELERATION_STRUCTURE_TYPE_TOP_LEVEL_KHR 类型创建
		3.如果nullDescriptor 特性没有开启，则pAccelerationStructures中的每个元素不能为VK_NULL_HANDLE
		*/


		//copy
		VkCopyDescriptorSet copyDescriptorSet{};
		copyDescriptorSet.sType = VK_STRUCTURE_TYPE_COPY_DESCRIPTOR_SET;
		copyDescriptorSet.pNext = nullptr;
		copyDescriptorSet.descriptorCount = 1;//指明要拷贝的descriptor个数，如果通过srcSet和srcBinding 指定的binding的descriptorType为 VK_DESCRIPTOR_TYPE_INLINE_UNIFORM_BLOCK，则这个指明要拷贝的字节大小
		copyDescriptorSet.dstArrayElement = 0;//这个dstBinding中descriptor数组中的起始元素，如果通过dstSet和dstBinding 指定的binding的descriptorType为 VK_DESCRIPTOR_TYPE_INLINE_UNIFORM_BLOCK，则这个指明为这个binding中开始字节的偏移量
		copyDescriptorSet.dstBinding = 0;////指定要拷贝到的destination descriptor set的binding
		copyDescriptorSet.dstSet = VkDescriptorSet{/*假设这是一个有效的VkDescriptorSet*/ }; //指明要拷贝到的destination descriptor set
		copyDescriptorSet.srcArrayElement = 0;//这个srcBinding中descriptor数组中的起始元素，如果通过srcSet和srcBinding 指定的binding的descriptorType为 VK_DESCRIPTOR_TYPE_INLINE_UNIFORM_BLOCK，则这个指明为这个binding中开始字节的偏移量
		copyDescriptorSet.srcBinding = 0;//指定要拷贝的source descriptor set的binding
		copyDescriptorSet.srcSet = VkDescriptorSet{/*假设这是一个有效的VkDescriptorSet*/ };//指明要拷贝的source descriptor set
		/*
		VkCopyDescriptorSet有效用法:
		1.srcBinding 必须是srcSet中有效的binding
		2.srcArrayElement + descriptorCount 必须小于等于srcSet中srcBinding的descriptor 的数量，以及consecutive binding updates p1301中描述的连续binding中所有可用的descriptor的总数
		3.dstBinding 必须是dstSet中有效的binding
		4.dstArrayElement + descriptorCount 必须小于等于srcSet中dstBinding的descriptor 的数量，以及consecutive binding updates p1301中描述的连续binding中所有可用的descriptor的总数
		5.dstSet中dstBinding 的类型必须等于srcSet中srcBinding 的类型
		6.如果srcSet 等于dstSet，则source和destination中descriptors的范围不能重叠，这些范围中可能包含consecutive binding updates p1301中描述的连续binding
		7.如果srcBinding 指明的descriptor 类型为VK_DESCRIPTOR_TYPE_INLINE_UNIFORM_BLOCK，则srcArrayElement 必须是4的整数倍
		8.如果dstBinding 指明的descriptor 类型为VK_DESCRIPTOR_TYPE_INLINE_UNIFORM_BLOCK，则dstArrayElement 必须是4的整数倍
		9.如果srcBinding 或者 dstBinding 指明的descriptor 类型为VK_DESCRIPTOR_TYPE_INLINE_UNIFORM_BLOCK，则descriptorCount 必须是4的整数倍
		10.如果srcSet 的layout以VK_DESCRIPTOR_SET_LAYOUT_CREATE_UPDATE_AFTER_BIND_POOL_BIT创建，则dstSet 的layout 必须以VK_DESCRIPTOR_SET_LAYOUT_CREATE_UPDATE_AFTER_BIND_POOL_BIT创建
		11.如果srcSet 的layout不以VK_DESCRIPTOR_SET_LAYOUT_CREATE_HOST_ONLY_POOL_BIT_EXT 或者VK_DESCRIPTOR_SET_LAYOUT_CREATE_UPDATE_AFTER_BIND_POOL_BIT 创建，则dstSet 的layout 就不能以VK_DESCRIPTOR_SET_LAYOUT_CREATE_UPDATE_AFTER_BIND_POOL_BIT创建
		12.如果分配srcSet 的descriptor pool 以VK_DESCRIPTOR_POOL_CREATE_UPDATE_AFTER_BIND_BIT创建，则分配dstSet 的descriptor pool 也必须以VK_DESCRIPTOR_POOL_CREATE_UPDATE_AFTER_BIND_BIT创建
		13.如果分配srcSet 的descriptor pool 不以VK_DESCRIPTOR_POOL_CREATE_HOST_ONLY_BIT_EXT 或者 VK_DESCRIPTOR_POOL_CREATE_UPDATE_AFTER_BIND_BIT创建，则分配dstSet 的descriptor pool 不能以VK_DESCRIPTOR_POOL_CREATE_UPDATE_AFTER_BIND_BIT创建
		14.如果dstBinding 指明的descriptor 类型为VK_DESCRIPTOR_TYPE_SAMPLER，则dstSet 不能以一个dstBinding 含有immutable samplers的layout进行分配
		15.如果dstSet的dstBinding的类型为VK_DESCRIPTOR_TYPE_MUTABLE_EXT，则如果新的该dstBinding的descriptor 类型不为VK_DESCRIPTOR_TYPE_MUTABLE_EXT，则必须列举在该dstBinding对应的pMutableDescriptorTypeLists列表中
		16.如果srcSet的srcBinding的类型为VK_DESCRIPTOR_TYPE_MUTABLE_EXT，且dstSet的dstBinding的类型不为VK_DESCRIPTOR_TYPE_MUTABLE_EXT，则source descriptor的类型必须和dstBinding上的descriptor类型匹配
		17.如果dstSet的dstBinding的类型为VK_DESCRIPTOR_TYPE_MUTABLE_EXT，且如果新的该dstBinding的descriptor 类型为VK_DESCRIPTOR_TYPE_MUTABLE_EXT，则对应srcBinding和dstBinding的pMutableDescriptorTypeLists中的元素必须完全匹配

		*/


		vkUpdateDescriptorSets(device, 1, &writeDescriptorSet, 1, &copyDescriptorSet);
		/*
		vkUpdateDescriptorSets有效用法:
		1.对于pDescriptorWrites中每个descriptorType为VK_DESCRIPTOR_TYPE_UNIFORM_TEXEL_BUFFER 或者 VK_DESCRIPTOR_TYPE_STORAGE_TEXEL_BUFFER的元素，则该元素的pTexelBufferView 必须已经在device上创建
		2.对于pDescriptorWrites中每个descriptorType为VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, VK_DESCRIPTOR_TYPE_STORAGE_BUFFER, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC, 或者 VK_DESCRIPTOR_TYPE_STORAGE_BUFFER_DYNAMIC的元素，则该元素的pBufferInfo的buffer 必须已经在device上创建
		3.对于pDescriptorWrites中每个descriptorType为VK_DESCRIPTOR_TYPE_SAMPLER 或者 VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER的元素，如果其dstSet 不以一个descriptorType类型的dstBinding 包含 immutable samplers的layout进行分配，则则该元素的pImageInfo的 sampler必须已经在device上创建
		4.对于pDescriptorWrites中每个descriptorType为VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE，VK_DESCRIPTOR_TYPE_STORAGE_IMAGE，VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT 或者 VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER的元素，则该元素的pImageInfo的 imageView 必须已经在device上创建
		5.对于pDescriptorWrites中每个descriptorType为VK_DESCRIPTOR_TYPE_ACCELERATION_STRUCTURE_KHR 的元素，则该元素的pNext中的VkWriteDescriptorSetAccelerationStructureKHR.pAccelerationStructures 中的加速结构必须已经在device上创建
		6.对于pDescriptorWrites中每个descriptorType为VK_DESCRIPTOR_TYPE_ACCELERATION_STRUCTURE_NV 的元素，则该元素的pNext中的VkWriteDescriptorSetAccelerationStructureNV.pAccelerationStructures 中的加速结构必须已经在device上创建
		7.对于pDescriptorWrites中每个descriptorType为VK_DESCRIPTOR_TYPE_SAMPLE_WEIGHT_IMAGE_QCOM 或者 VK_DESCRIPTOR_TYPE_BLOCK_MATCH_IMAGE_QCOM 的元素，则该元素的pImageInfo的 imageView  必须已经在device上创建
		8.对于pDescriptorWrites中每个descriptorType为VK_DESCRIPTOR_TYPE_SAMPLER, VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE, VK_DESCRIPTOR_TYPE_STORAGE_IMAGE, 或者
                                     VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT 的元素，则该元素的pImageInfo必须是该元素所指descriptorCount个有效VkDescriptorImageInfo数组的指针
		9.对于pDescriptorWrites中每个descriptorType为VK_DESCRIPTOR_TYPE_SAMPLE_WEIGHT_IMAGE_QCOM 或者 VK_DESCRIPTOR_TYPE_BLOCK_MATCH_IMAGE_QCOM 的元素，则该元素的pImageInfo必须是该元素所指descriptorCount个有效VkDescriptorImageInfo数组的指针
		10.pDescriptorWrites 中每个元素的dstSet或者 pDescriptorCopies中binding不以VK_DESCRIPTOR_BINDING_UPDATE_AFTER_BIND_BIT或者 VK_DESCRIPTOR_BINDING_UPDATE_UNUSED_WHILE_PENDING_BIT创建的元素不能在任何一个记录到pending state 状态的command buffer的command中使用
		11.host访问pDescriptorWrites中的dstSet以及pDescriptorCopies中的dstSet 必须是外部同步的，除非有特殊的标志设置。
	
		*/
	
	}



	//Descriptor Update Templates
	{
		//一个descriptor update template指的是一个descriptor更新信息到descriptor的映射，这个的设计是为了避免在过于频繁地更新descriptor sets中的同一descriptor set中 host端向驱动传递冗余的更新信息,即当希望更新多个使用相同 VkDescriptorSetLayout分配的descriptor sets中的一组相同的descriptors的时候，就可以使用 vkUpdateDescriptorSetWithTemplate 来替换 vkUpdateDescriptorSets
		//VkDescriptorUpdateTemplate 功能详细说明见p1318
		VkDescriptorUpdateTemplate descriptorUpdateTemplate{};//等同于VkDescriptorUpdateTemplateKHR


		VkDescriptorUpdateTemplateCreateInfo descriptorUpdateTemplateCreateInfo{};//等同于VkDescriptorUpdateTemplateCreateInfoKHR
		descriptorUpdateTemplateCreateInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_UPDATE_TEMPLATE_CREATE_INFO;
		descriptorUpdateTemplateCreateInfo.pNext = nullptr;
		descriptorUpdateTemplateCreateInfo.flags = 0;//保留未来使用
		descriptorUpdateTemplateCreateInfo.descriptorSetLayout = VkDescriptorSetLayout{/*假设这是一个有效的VkDescriptorSetLayout*/ };//用来构建descriptor update template的  descriptor set layout，通过descriptor update template 更新的descriptor sets必须以和该layout相匹配的布局创建，且该参数只在templateType为VK_DESCRIPTOR_UPDATE_TEMPLATE_TYPE_DESCRIPTOR_SET才有效
		descriptorUpdateTemplateCreateInfo.descriptorUpdateEntryCount = 1;//pDescriptorUpdateEntries中元素个数
			VkDescriptorUpdateTemplateEntry descriptorUpdateTemplateEntry{};//等价于VkDescriptorUpdateTemplateEntryKHR
			{
			descriptorUpdateTemplateEntry.stride = 1;//是原始数据结构中两个descriptor 更新信息数组元素之间的字节步长，更新实体i的更新信息j的实际地址：  const char *ptr = (const char *)pData + pDescriptorUpdateEntries[i].offset + j *pDescriptorUpdateEntries[i].stride
			descriptorUpdateTemplateEntry.offset = 0;//是原始数据结构中第一个binding的起始字节偏移量
			descriptorUpdateTemplateEntry.dstBinding = 0;//指明使用 descriptor update template要更新的binding
			descriptorUpdateTemplateEntry.dstArrayElement = 0;//dstBinding上的要更新的起始元素，如果dstBinding的类型为VK_DESCRIPTOR_TYPE_INLINE_UNIFORM_BLOCK，则表示要更新的起始字节偏移量
			descriptorUpdateTemplateEntry.descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;//是一个 VkDescriptorType值 指明descriptor的类型
			descriptorUpdateTemplateEntry.descriptorCount = 1;//要更新的descriptor的数量，如果dstBinding的类型为VK_DESCRIPTOR_TYPE_INLINE_UNIFORM_BLOCK，则表示要更新的字节数量
			/*
			VkDescriptorUpdateTemplateEntry有效用法:
			1.dstBinding必须是使用descriptor update template更新descriptors时descriptor set layout隐式指定的有效的binding
			2.dstArrayElement + descriptorCount必须小于等于使用descriptor update template更新descriptors是descriptor set layout隐式指定的有效的binding中元素的个数，以及所有可用连续binding中的descriptors的数量，见consecutive binding updates p1301 描述
			3.如果descriptor为VK_DESCRIPTOR_TYPE_INLINE_UNIFORM_BLOCK，dstArrayElement和descriptorCount 必须是4的整数倍
			*/
		}

		descriptorUpdateTemplateCreateInfo.pDescriptorUpdateEntries = &descriptorUpdateTemplateEntry;//一组VkDescriptorUpdateTemplateEntry的数组地址，描述一组通过descriptor update template更新的descriptors
		descriptorUpdateTemplateCreateInfo.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;//是一个VkPipelineBindPoint 指明哪一个类型的pipeline将使用这些descriptors，且该参数只在templateType为VK_DESCRIPTOR_UPDATE_TEMPLATE_TYPE_PUSH_DESCRIPTORS_KHR才有效
		descriptorUpdateTemplateCreateInfo.pipelineLayout = VkPipelineLayout{/*假设这是一个有效的VkPipelineLayout*/ };//是一个 VkPipelineLayout 对象管理这些bindings，且该参数只在templateType为VK_DESCRIPTOR_UPDATE_TEMPLATE_TYPE_PUSH_DESCRIPTORS_KHR才有效
		descriptorUpdateTemplateCreateInfo.set = 0;//是pipeline layout中要更新的descriptor set的编号，且该参数只在templateType为VK_DESCRIPTOR_UPDATE_TEMPLATE_TYPE_PUSH_DESCRIPTORS_KHR才有效
		descriptorUpdateTemplateCreateInfo.templateType = VK_DESCRIPTOR_UPDATE_TEMPLATE_TYPE_DESCRIPTOR_SET;/*指定descriptor update template 的类型，
			如果为VK_DESCRIPTOR_UPDATE_TEMPLATE_TYPE_DESCRIPTOR_SET 则只能用来更新使用descriptorSetLayout的descriptor sets，
			如果为VK_DESCRIPTOR_UPDATE_TEMPLATE_TYPE_PUSH_DESCRIPTORS_KHR，则可以用来推送pipelineBindPoint, pipelineLayout, 以及 set指明的descriptor sets
		*/


		/*
		VkDescriptorUpdateTemplateCreateInfo有效用法:
		1.如果templateType 是VK_DESCRIPTOR_UPDATE_TEMPLATE_TYPE_DESCRIPTOR_SET，则descriptorSetLayout必须是有效的VkDescriptorSetLayout 句柄，且descriptorSetLayout不能包含VK_DESCRIPTOR_TYPE_MUTABLE_EXT类型的binding
		2.如果templateType 是VK_DESCRIPTOR_UPDATE_TEMPLATE_TYPE_PUSH_DESCRIPTORS_KHR，则pipelineBindPoint必须是有效的VkPipelineBindPoint 值，pipelineLayout必须是有效的VkPipelineLayout句柄，set必须是使用VK_DESCRIPTOR_SET_LAYOUT_CREATE_PUSH_DESCRIPTOR_BIT_KHR 创建的pipeline layout中的单独的descriptor set编号

		*/


		//创建VkDescriptorUpdateTemplate   等同于vkCreateDescriptorUpdateTemplateKHR
		vkCreateDescriptorUpdateTemplate(device, &descriptorUpdateTemplateCreateInfo, nullptr, &descriptorUpdateTemplate);

		//销毁VkDescriptorUpdateTemplate   等同于vkDestroyDescriptorUpdateTemplateKHR
		vkDestroyDescriptorUpdateTemplate(device, descriptorUpdateTemplate, nullptr);


		void* rawData;
		//一旦创建以一个VkDescriptorUpdateTemplate，便可进行descriptor更新    等同于vkUpdateDescriptorSetWithTemplateKHR
		vkUpdateDescriptorSetWithTemplate(device, VkDescriptorSet{/*假设这是一个有效的VkDescriptorSet*/ }, descriptorUpdateTemplate, rawData);/*
		vkUpdateDescriptorSetWithTemplate关键参数:
		descriptorSet : 为要更新的 descriptor set 
		descriptorUpdateTemplate : 是一个VkDescriptorUpdateTemplate 句柄，指明一个pData到要更新的descriptor set之间的更新映射
		pData  :  是一个包含一个或多个kDescriptorImageInfo, VkDescriptorBufferInfo, 或者 VkBufferView  或者 VkAccelerationStructureKHR 或者 VkAccelerationStructureNV句柄的用于写入descriptor的地址指针
		
		---------------------------------------------------
		vkUpdateDescriptorSetWithTemplate有效用法:
		1.pData 必须是一个有效的包含一个或多个以创建descriptorUpdateTemplate时指定的layout布局创建的 VkDescriptorImageInfo, VkDescriptorBufferInfo, 或者 VkBufferView 句柄的用于写入descriptor的地址指针
		2.除非有特殊的标志说明，则host对descriptorSet 的访问必须时外部同步的
		
		
		*/

		//使用VkDescriptorUpdateTemplate 更新descriptor set的代码示例见p1326
	}



	//Descriptor Set Binding  绑定descriptor set
	{
		//绑定一个或者多个descriptor set到command buffer
		VkDescriptorSet descriptorSet{/*假设这是一个有效的VkDescriptorSet*/ };
		VkCommandBuffer commandBuffer{/*假设这是一个有效的VkCommandBuffer*/ };
		vkCmdBindDescriptorSets(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS,
			VkPipelineLayout{/*假设这是一个有效的VkPipelineLayout*/ }, 0, 1, & descriptorSet, 0, nullptr);
		/*
		vkCmdBindDescriptorSets重要参数:
		commandBuffer: 为descriptor set要绑定到的command buffer 
		pipelineBindPoint:  是一个VkPipelineBindPoint 指定使用descriptors的pipeline类型，不同pipeline类型的绑定不会互相干扰，见descriptor 绑定干扰Pipeline Layout Compatibility p1280
		layout: 是一个VkPipelineLayout， 用来组织 bindings.
		firstSet: 是第一个要绑定的descriptor set的set编号
		descriptorSetCount: pDescriptorSets中元素个数
		pDescriptorSets:  是一组描述要绑定的descriptor sets的VkDescriptorSet 句柄的数组指针
		dynamicOffsetCount:  pDynamicOffsets中元素个数
		pDynamicOffsets: 一组指明dynamic offsets的uint32_t值的数组指针

		绑定pDescriptorSets[0..descriptorSetCount-1] 到 [firstSet..firstSet+descriptorSetCount-1]

		dynamicOffsetCount以及pDynamicOffsets 用在要绑定的descriptor sets中含有dynamic uniform 或者 storage buffers类型的descriptor的时候，具体功能描述见p1329

		-------------------------------------
		vkCmdBindDescriptorSets有效用法:
		1.pDescriptorSets中每个元素分配时的VkDescriptorSetLayout必须匹配layout（VkPipelineLayout）中firstSet + pDescriptorSets中该元素索引 对应的 VkDescriptorSetLayout
		2.dynamicOffsetCount 必须等于pDescriptorSets中dynamic descriptors的总数
		3.firstSet + descriptorSetCount必须小于等于layout 创建时的VkPipelineLayoutCreateInfo::setLayoutCount
		4.pDynamicOffsets中的每个对应到descriptor binding为VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC类型的元素值必须是VkPhysicalDeviceLimits::minUniformBufferOffsetAlignment的倍数
		5.pDynamicOffsets中的每个对应到descriptor binding为VK_DESCRIPTOR_TYPE_STORAGE_BUFFER_DYNAMIC类型的元素值必须是VkPhysicalDeviceLimits::minStorageBufferOffsetAlignment的倍数
		6.对于pDescriptorSets中每个dynamic uniform 或者 storage buffer binding，则（1）其有效的offset + range必须小于buffer的大小
																				  （2）如果其range为range，则pDynamicOffsets 对应到该binding的元素必须为0
		7.pDescriptorSets中的每个元素不能从一个以VK_DESCRIPTOR_POOL_CREATE_HOST_ONLY_BIT_EXT创建的VkDescriptorPool 中分配
		8.如果graphicsPipelineLibrary 没有启用，则pDescriptorSets的每个元素必须是一个有效的VkDescriptorSet
		9.pDescriptorSets中的每个元素不能从一个以VK_DESCRIPTOR_SET_LAYOUT_CREATE_DESCRIPTOR_BUFFER_BIT_EXT创建的VkDescriptorSetLayout 来进行分配
		10.pipelineBindPoint 必须由commandBuffer所在的VkCommandPool对应的队列族所支持

		*/



		//使用vkCmdBindDescriptorSets2KHR 
		{
			// Provided by VK_KHR_maintenance6
			typedef struct VkBindDescriptorSetsInfoKHR {
				VkStructureType sType;
				const void* pNext;//可以包含一个 VkPipelineLayoutCreateInfo，只在layout为VK_NULL_HANDLE的情况下才包含
				VkShaderStageFlags stageFlags;//是VkShaderStageFlagBits组合值位掩码，指明descriptor要绑定的shader stages
				VkPipelineLayout layout;//是一个VkPipelineLayout， 用来组织 bindings，如果 dynamicPipelineLayout特性开启，这个参数可以为VK_NULL_HANDLE但必须在pNext中添加一个VkPipelineLayoutCreateInfo进行指定
				uint32_t firstSet;//是第一个要绑定的descriptor set的set编号
				uint32_t descriptorSetCount;//pDescriptorSets中元素个数
				const VkDescriptorSet* pDescriptorSets;//是一组描述要绑定的descriptor sets的VkDescriptorSet 句柄的数组指针
				uint32_t dynamicOffsetCount;//pDynamicOffsets中元素个数
				const uint32_t* pDynamicOffsets;//一组指明dynamic offsets的uint32_t值的数组指针
			} VkBindDescriptorSetsInfoKHR;
			/*
			VkBindDescriptorSetsInfoKHR有效用法:
			1.pDescriptorSets中每个元素分配时的VkDescriptorSetLayout必须匹配layout（VkPipelineLayout）中firstSet + pDescriptorSets中该元素索引 对应的 VkDescriptorSetLayout
			2.dynamicOffsetCount 必须等于pDescriptorSets中dynamic descriptors的总数
			3.firstSet + descriptorSetCount必须小于等于layout 创建时的VkPipelineLayoutCreateInfo::setLayoutCount
			4.pDynamicOffsets中的每个对应到descriptor binding为VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC类型的元素值必须是VkPhysicalDeviceLimits::minUniformBufferOffsetAlignment的倍数
			5.pDynamicOffsets中的每个对应到descriptor binding为VK_DESCRIPTOR_TYPE_STORAGE_BUFFER_DYNAMIC类型的元素值必须是VkPhysicalDeviceLimits::minStorageBufferOffsetAlignment的倍数
			6.对于pDescriptorSets中每个dynamic uniform 或者 storage buffer binding，则（1）其有效的offset + range必须小于buffer的大小
																				      （2）如果其range为range，则pDynamicOffsets 对应到该binding的元素必须为0
			7.pDescriptorSets中的每个元素不能从一个以VK_DESCRIPTOR_POOL_CREATE_HOST_ONLY_BIT_EXT创建的VkDescriptorPool 中分配
			8.如果graphicsPipelineLibrary 没有启用，则pDescriptorSets的每个元素必须是一个有效的VkDescriptorSet
			9.pDescriptorSets中的每个元素不能从一个以VK_DESCRIPTOR_SET_LAYOUT_CREATE_DESCRIPTOR_BUFFER_BIT_EXT创建的VkDescriptorSetLayout 来进行分配
			10.如果dynamicPipelineLayout 特性没有开启，则layout 必须是一个有效的VkPipelineLayout 句柄
			11.如果layout 为VK_NULL_HANDLE，则pNext中必须包含一个有效的VkPipelineLayoutCreateInfo

			*/



			// Provided by VK_KHR_maintenance6
			auto vkCmdBindDescriptorSets2KHR = [](
				VkCommandBuffer commandBuffer,
				const VkBindDescriptorSetsInfoKHR* pBindDescriptorSetsInfo/* pBindDescriptorSetsInfo->stageFlags中的每个比特位都必须由commandBuffer所在的VkCommandPool对应的队列族所支持*/
				) {

				};//由于vkCmdBindDescriptorSets2KHR这个接口没有定义，这里就直接定义成lambda形式
		
			VkBindDescriptorSetsInfoKHR bindDescriptorSetsInfoKHR{/*假设这是一个有效的VkBindDescriptorSetsInfoKHR*/ };
			vkCmdBindDescriptorSets2KHR(commandBuffer, &bindDescriptorSetsInfoKHR);
		}




	
	}



	// Push Descriptor Updates
	{
	//除了将descriptor sets绑定到command buffer外，还可以通过将descriptor 的更新信息记录到command buffer,这些push descriptors由command buffer进行内存管理则便不需要管理descriptor sets的生命周期
		VkCommandBuffer commandBuffer{/*假设这是一个有效的VkCommandBuffer*/ };
		VkWriteDescriptorSet writeDescriptorSet{/*假设这是一个有效的VkWriteDescriptorSet*/ };
		
		vkCmdPushDescriptorSetKHR(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, VkPipelineLayout{/*假设这是一个有效的VkPipelineLayout*/ },
			0, 1, & writeDescriptorSet);
		/*
		vkCmdPushDescriptorSetKHR参数:

		commandBuffer: 是descriptors将被记录到的command buffer
		pipelineBindPoint:  是一个VkPipelineBindPoint 指定使用descriptors的pipeline类型，不同pipeline类型的绑定不会互相干扰，见descriptor 绑定干扰Pipeline Layout Compatibility p1280
		layout:  是一个VkPipelineLayout， 用来组织 bindings.
		set:  是pipeline layout中要更新的descriptor set的set编号
		descriptorWriteCount:  pDescriptorWrites中元素个数
		pDescriptorWrites:  是一组描述要更新的descriptors的VkWriteDescriptorSet 数组指针

		具体的功能描述见p1336
		------------------------------------
		vkCmdPushDescriptorSetKHR有效用法:
		1.set必须小于等于layout 创建时的VkPipelineLayoutCreateInfo::setLayoutCount
		2.set必须是pipeline layout中使用VK_DESCRIPTOR_SET_LAYOUT_CREATE_PUSH_DESCRIPTOR_BIT_KHR创建的单独有效的set编号
		3.对于每个pDescriptorWrites中descriptorType为VK_DESCRIPTOR_TYPE_SAMPLER, VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE, VK_DESCRIPTOR_TYPE_STORAGE_IMAGE, 或者
								VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT 的元素，该元素的pImageInfo 必须是一个有效的该元素的descriptorCount个VkDescriptorImageInfo的数组指针
		4.pipelineBindPoint必须由commandBuffer所在的VkCommandPool对应的队列族所支持
		
		*/

	

		//使用vkCmdPushDescriptorSet2KHR
		{
			
			// Provided by VK_KHR_maintenance6 with VK_KHR_push_descriptor
			typedef struct VkPushDescriptorSetInfoKHR {
				VkStructureType sType;
				const void* pNext;//可以包含一个 VkPipelineLayoutCreateInfo，只在layout为VK_NULL_HANDLE的情况下才包含
				VkShaderStageFlags stageFlags;//是VkShaderStageFlagBits组合值位掩码，指明要使用descriptors的shader stages
				VkPipelineLayout layout;//是一个VkPipelineLayout， 用来组织 bindings，如果 dynamicPipelineLayout特性开启，这个参数可以为VK_NULL_HANDLE但必须在pNext中添加一个VkPipelineLayoutCreateInfo进行指定
				uint32_t set;//是要更新pipeline layout中的descriptor set的set编号
				uint32_t descriptorWriteCount;// pDescriptorWrites中元素个数
				const VkWriteDescriptorSet* pDescriptorWrites;//是一组描述要更新的descriptors的  VkWriteDescriptorSet数组指针
			} VkPushDescriptorSetInfoKHR;//没有定义所以这里定义一个临时VkPushDescriptorSetInfoKHR的用作示例
			/*
			VkPushDescriptorSetInfoKHR有效用法:
			1.set必须小于等于layout 创建时的VkPipelineLayoutCreateInfo::setLayoutCount
			2.set必须是pipeline layout中使用VK_DESCRIPTOR_SET_LAYOUT_CREATE_PUSH_DESCRIPTOR_BIT_KHR创建的单独有效的set编号
			3.对于每个pDescriptorWrites中descriptorType为VK_DESCRIPTOR_TYPE_SAMPLER, VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE, VK_DESCRIPTOR_TYPE_STORAGE_IMAGE, 或者
									VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT 的元素，该元素的pImageInfo 必须是一个有效的该元素的descriptorCount个VkDescriptorImageInfo的数组指针
			4.如果dynamicPipelineLayout 特性没有开启，则layout必须是一个有效的VkPipelineLayout 句柄
			5.如果layout为VK_NULL_HANDLE，则pNext中必须包含一个有效的VkPipelineLayoutCreateInfo 
			
			
			*/



			// Provided by VK_KHR_maintenance6 with VK_KHR_push_descriptor
			auto vkCmdPushDescriptorSet2KHR = [](
				VkCommandBuffer commandBuffer,
				const VkPushDescriptorSetInfoKHR* pPushDescriptorSetInfo/* pPushDescriptorSetInfo->stageFlags中的每个比特位都必须由commandBuffer所在的VkCommandPool对应的队列族所支持*/
				) {

				};//没有定义所以这里直接定义为lambda形式的
		
			VkPushDescriptorSetInfoKHR pushDescriptorSetInfoKHR{/*假设这是一个有效的VkPushDescriptorSetInfoKHR*/ };
			vkCmdPushDescriptorSet2KHR(commandBuffer, &pushDescriptorSetInfoKHR);
		}
	
	}


	// Push Descriptor Updates With Descriptor Update Templates  使用descriptor update template来更新push descriptor
	{
		VkCommandBuffer commandBuffer{/*假设这是一个有效的VkCommandBuffer*/};

		void* rawData;
		vkCmdPushDescriptorSetWithTemplateKHR(commandBuffer, VkDescriptorUpdateTemplate{/*假设这是一个有效的VkDescriptorUpdateTemplate*/ },
			VkPipelineLayout{/*假设这是一个有效的VkPipelineLayout*/ }, 0, rawData);
		/*
		vkCmdPushDescriptorSetWithTemplateKHR参数:
		commandBuffer: 是descriptors要被记录到的command buffer
		descriptorUpdateTemplate:  是一个定义如何解释pData中的descriptor信息的VkDescriptorUpdateTemplate句柄
		layout:  是一个组织bindings 的VkPipelineLayout句柄，必须和创建descriptorUpdateTemplate的pipeline layout兼容
		set:  是pipeline layout中要更新的descriptor set的编号，必须和创建descriptorUpdateTemplate的set相同
		pData:  是包含descriptors相关句柄的指针

		---------------------------------------------
		vkCmdPushDescriptorSetWithTemplateKHR有效用法:
		1.创建descriptorUpdateTemplate 时指定的pipelineBindPoint必须由 commandBuffer所在的VkCommandPool对应的队列族所支持
		2.pData 必须是一个包含一个或多个在创建descriptorUpdateTemplate的时候layout中定义的一个或多个VkDescriptorImageInfo, VkDescriptorBufferInfo, 或者 VkBufferView 有效实例的句柄的数组指针
		3.layout必须和创建descriptorUpdateTemplate的pipeline layout匹配
		4.descriptorUpdateTemplate 必须以VK_DESCRIPTOR_UPDATE_TEMPLATE_TYPE_PUSH_DESCRIPTORS_KHR类型创建
		5.set必须和创建descriptorUpdateTemplate的set相同，且set必须小于创建layout时VkPipelineLayoutCreateInfo::setLayoutCount指定的值，
				且set必须是使用以VK_DESCRIPTOR_SET_LAYOUT_CREATE_PUSH_DESCRIPTOR_BIT_KHR创建descriptor set layout的pipeline layout中一个单独的编号
		
		*/
	


		//使用vkCmdPushDescriptorSetWithTemplate2KHR
		{
		
			// Provided by VK_KHR_maintenance6 with VK_KHR_push_descriptor
			typedef struct VkPushDescriptorSetWithTemplateInfoKHR {
				VkStructureType sType;
				const void* pNext;//可以包含一个VkPipelineLayoutCreateInfo，只在layout为VK_NULL_HANDLE的情况下才包含
				VkDescriptorUpdateTemplate descriptorUpdateTemplate;//是一个定义如何解释pData中的descriptor信息的VkDescriptorUpdateTemplate句柄
				VkPipelineLayout layout;//是一个组织bindings 的VkPipelineLayout句柄，必须和创建descriptorUpdateTemplate的pipeline layout兼容,如果 dynamicPipelineLayout 特性开启，则可以为VK_NULL_HANDLE，但必须在pNext中添加一个VkPipelineLayoutCreateInfo
				uint32_t set;//是pipeline layout中要更新的descriptor set的编号，必须和创建descriptorUpdateTemplate的set相同
				const void* pData;//是包含descriptors相关句柄的指针
			} VkPushDescriptorSetWithTemplateInfoKHR;//这个数据结构没有定义所以定义一个示例的VkPushDescriptorSetWithTemplateInfoKHR
			/*
			VkPushDescriptorSetWithTemplateInfoKHR有效用法:
			
			1.创建descriptorUpdateTemplate 时指定的pipelineBindPoint必须由 commandBuffer所在的VkCommandPool对应的队列族所支持
			2.pData 必须是一个包含一个或多个在创建descriptorUpdateTemplate的时候layout中定义的一个或多个VkDescriptorImageInfo, VkDescriptorBufferInfo, 或者 VkBufferView 有效实例的句柄的数组指针
			3.layout必须和创建descriptorUpdateTemplate的pipeline layout匹配
			4.descriptorUpdateTemplate 必须以VK_DESCRIPTOR_UPDATE_TEMPLATE_TYPE_PUSH_DESCRIPTORS_KHR类型创建
			5.set必须和创建descriptorUpdateTemplate的set相同，且set必须小于创建layout时VkPipelineLayoutCreateInfo::setLayoutCount指定的值，
				 且set必须是使用以VK_DESCRIPTOR_SET_LAYOUT_CREATE_PUSH_DESCRIPTOR_BIT_KHR创建descriptor set layout的pipeline layout中一个单独的编号
			6.如果dynamicPipelineLayout 特性没有开启，则layout必须是一个有效的VkPipelineLayout 句柄
			7.如果layout为VK_NULL_HANDLE，则pNext中必须包含一个有效的VkPipelineLayoutCreateInfo 
			*/


			// Provided by VK_KHR_maintenance6 with VK_KHR_push_descriptor
			auto vkCmdPushDescriptorSetWithTemplate2KHR = [=](
				VkCommandBuffer commandBuffer,
				const VkPushDescriptorSetWithTemplateInfoKHR* pPushDescriptorSetWithTemplateInfo) {};//这个接口没有定义所以这里手动定义一个lambda形式的

			VkPushDescriptorSetWithTemplateInfoKHR pushDescriptorSetWithTemplateInfoKHR{/*假设这是一个有效的VkPushDescriptorSetWithTemplateInfoKHR*/ };
			vkCmdPushDescriptorSetWithTemplate2KHR(commandBuffer, &pushDescriptorSetWithTemplateInfoKHR);

		}



	}


}


NS_TEST_END