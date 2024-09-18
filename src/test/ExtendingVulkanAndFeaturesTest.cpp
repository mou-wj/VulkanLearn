#include "ExtendingVulkanAndFeaturesTest.h"
NS_TEST_BEGIN
ExtendingVulkanAndFeatuesTest::ExtendingVulkanAndFeatuesTest()
{
}

void ExtendingVulkanAndFeatuesTest::run()
{
}

ExtendingVulkanAndFeatuesTest::~ExtendingVulkanAndFeatuesTest()
{
}

void ExtendingVulkanAndFeatuesTest::ExtendingVulkanTest()
{
	//新的函数可以通过新的拓展，或者新的内核版本，以及拓展的新的版本添加到vulkan

	//Instance and Device Functionality  参见p3713
	{
		/*
		枚举instance属性或者接受instance为参数的函数为instance-level functionality.

		从device或者其子对象派发的，或者接受device为参数的函数为device-level functionality.

		从VkPhysicalDevice派发或者接受VkPhysicalDevice的函数是instance-level还是device-level functionality 取决与是否指定一个instance extension还是device extension，另外，列举设备属性的认为是device-level functionality 
		
		*/


	}

	// Core Versions  参见p3713
	{
		// Version Numbers  参见p3714
		{
			/*
			vulkan 版本号由四部分构成: variant, major, minor 以及 patch 版本
			
			variant 版本: 指明实现支持的vulkan API的变体版本，对vulkan API来说永远为0
			major 版本: 表示API中的一个重大变化，它将包含一个全新的规范版本
			minor 版本: 指明在核心规范中加入了新的功能
			patch 版本: 指明表示规范中包含了错误修复、澄清和语言改进

			vulkan打包的版本号总共32bit，其中格式为从前往后，从高位到低位: variant（3bit）, major（7bit）, minor（10bit） 以及 patch （12bit）,如何从打包的版本号中提取对应的版本，vulkan定义了一些提取宏如 VK_VERSION_PATCH ，具体见p3715
			
			vulkan定义了一些指定特定vulkan 版本的宏如 VK_API_VERSION_1_0 ，参见p3716
			*/



		}

		//Querying Version Support  参见p3717
		{
			// instance-level functionality的版本查询
			uint32_t apiVersion = 0;
			vkEnumerateInstanceVersion(&apiVersion);


			// device-level functionality的版本查询
			VkPhysicalDeviceProperties properties;
			vkGetPhysicalDeviceProperties(physicalDevice, &properties);
			properties.apiVersion;//返回查询支持的api版本
			
			VkPhysicalDeviceProperties2 properties2;
			vkGetPhysicalDeviceProperties2(physicalDevice, &properties2);
			properties2.properties.apiVersion;//返回查询支持的api版本
		}
	}


	//Layers  参见p3717
	{
		/*
		当一个layer启用时，该layer会把自己插入到对应的vulkan函数命令的调用链中，以扩展该命令的行为，用于日志，追踪，校验以及提供额外拓展等功能
		*/
	
		//查询可用的layers
		uint32_t numLayer = 0;
		std::vector<VkLayerProperties> layerProperties;
		vkEnumerateInstanceLayerProperties(&numLayer, nullptr);
		layerProperties.resize(numLayer);
		vkEnumerateInstanceLayerProperties(&numLayer, layerProperties.data());//假设成功返回了一个元素

		VkLayerProperties& layerProp = layerProperties[0];
		layerProp.layerName/*char [VK_MAX_EXTENSION_NAME_SIZE]类型，VK_MAX_EXTENSION_NAME_SIZE = 256U*/;//为该layer的 null-terminated UTF-8类型的名称，可传入 VkInstanceCreateInfo.ppEnabledLayerNames 中指明instance要开启的layer，有一些layer是隐式开启的，这里不需要指定
		layerProp.specVersion = 0;//为该layer写入哪个vulkan版本
		layerProp.implementationVersion = 0;//为该layer自己的版本，递增
		layerProp.description/*char [VK_MAX_DESCRIPTION_SIZE]类型，VK_MAX_DESCRIPTION_SIZE = 256U*/;//为该layer的 null-terminated UTF-8类型的描述，提供额外的信息指定该layer


		// Device Layer Deprecation  参见p3719
		{
			/*
			早期版本区分layer为instance layer还是 device layer，这些layer只能和对应的对象交互，后期版本不再区分。
			*/

			//为了兼容早期的版本，获取device的layer 属性
			uint32_t numDeviceLayer = 0;
			std::vector<VkLayerProperties> deviceLayerProperties;
			vkEnumerateDeviceLayerProperties(physicalDevice, &numDeviceLayer, nullptr);
			deviceLayerProperties.resize(numDeviceLayer);
			vkEnumerateDeviceLayerProperties(physicalDevice, &numDeviceLayer, deviceLayerProperties.data());//返回的结果和vkEnumerateInstanceLayerProperties 一样，返回的参数可在VkDeviceCreateInfo中的ppEnabledLayerNames以及 enabledLayerCount中使用，但两个参数实际上废弃掉了，是无效的
			


		}


	}


	// Extensions  参见p3721
	{
		/*
		extensions 可能会定义新的vulkan调用命令，结构体，枚举等。为了编译目的，已经注册的extensions的命令以及数据结构等会列举在vulkan_core.h中，extensions的调用命令不能通过静态链接，需要动态加载。

		extension会拓展或者改变Vulkan API的行为，extension应该要支持vulkan的layers
		
		可以在VkInstanceCreateInfo.ppEnabledExtensionNames中指定extension名字来开启instance extension，可以在 VkDeviceCreateInfo.ppEnabledExtensionNames中指定extension名字来开启device extension
		
		开启extensions不改变现有vulkan API的行为或者其他extensions的行为，只是让该extension相关的接口，结构体等有效。
		*/


		// Instance Extensions  参见p3722
		{
			//Instance extensions 添加新的 instance-level functionality到API，不是添加到core中

			//查询可用的instance extensions
			uint32_t numExtension = 0;
			std::vector<VkExtensionProperties> extensionProperties{};

			//列举Vulkan实现或者隐式开启的layers提供的extensions
			vkEnumerateInstanceExtensionProperties(nullptr, &numExtension, nullptr);
			extensionProperties.resize(numExtension);
			vkEnumerateInstanceExtensionProperties(nullptr, &numExtension, extensionProperties.data());//假设成功返回了一个元素

			VkExtensionProperties &extensionProp = extensionProperties[0];
			extensionProp.specVersion = 0;//为该extension自己的版本，递增
			extensionProp.extensionName/*char [VK_MAX_EXTENSION_NAME_SIZE]类型，VK_MAX_EXTENSION_NAME_SIZE = 256U*/;//为该extension的 null-terminated UTF-8类型的名称



			char layerName[5];//假设这是一个有效的layer name
			//列举指定layer提供的extensions
			vkEnumerateInstanceExtensionProperties(layerName, &numExtension, nullptr);
			extensionProperties.resize(numExtension);
			vkEnumerateInstanceExtensionProperties(layerName, &numExtension, extensionProperties.data());

		}

		//Device Extensions  参见p3723
		{
			//Device extensions 添加新的 device-level functionality到API，不是添加到core中

			//查询可用的device extensions

			uint32_t numDeviceExtension = 0;
			std::vector<VkExtensionProperties> deviceExtensionProperties{};

			//列举Vulkan实现或者隐式开启的layers提供的extensions
			vkEnumerateDeviceExtensionProperties(physicalDevice,nullptr, &numDeviceExtension, nullptr);
			deviceExtensionProperties.resize(numDeviceExtension);
			vkEnumerateDeviceExtensionProperties(physicalDevice,nullptr, &numDeviceExtension, deviceExtensionProperties.data());

			char layerName[5];//假设这是一个有效的layer name
			//列举指定layer提供的extensions
			vkEnumerateDeviceExtensionProperties(physicalDevice,layerName, &numDeviceExtension, nullptr);
			deviceExtensionProperties.resize(numDeviceExtension);
			vkEnumerateDeviceExtensionProperties(physicalDevice,layerName, &numDeviceExtension, deviceExtensionProperties.data());

		}

	}



	//Extension Dependencies  参见p3726
	{
		/*
		一些extensions会在从函数上以来别的extension或者指定的vulkan版本，所以在开启该extensions之前，需要开启其以来的extensions以及使用对应版本。
		*/
	}


	//Compatibility Guarantees (Informative)  参见p3726
	{
		//Core Versions  主要描述版本的各个部分按照什么规则进行递增，  参见p3726
		

		//Extensions    主要描述必须保证哪些extensions可以和哪些extensions一起使用以及一些别的兼容规则,  参见p3728  ， vk.xml 中描述了extensions的一些别的信息


	}
}

void ExtendingVulkanAndFeatuesTest::FeaturesTest()
{
	/*
	Features描述了不是所有实现都支持的功能。是物理设备的特性，且是可选的，使用前必须显式开启。
	*/

	


	//查询支持的features  参见p3731
	VkPhysicalDeviceFeatures physicalDeviceFeatures{};
	vkGetPhysicalDeviceFeatures(physicalDevice, &physicalDeviceFeatures);//假设成功返回了结果
	physicalDeviceFeatures.robustBufferAccess = VK_FALSE;//指明是否对buffer descriptor的buffer的访问要进行边界检测，保证超出边界的返回不会导致运行终止，超出边界的访问的具体处理措施见p3735 - p3737
	physicalDeviceFeatures.fullDrawIndexUint32 = VK_FALSE;//指明当进行索引绘制时使用 VkIndexType 为VK_INDEX_TYPE_UINT32是否支持全部32-bit的都来进行索引，这样，索引最大值maxDrawIndexedIndexValue 就为pow(2,32)-1
	physicalDeviceFeatures.imageCubeArray = VK_FALSE;//指明是否可以创建VK_IMAGE_VIEW_TYPE_CUBE_ARRAY类型的image view以及其对应的SampledCubeArray 以及 ImageCubeArray 是否可以在着色器代码中使用
	physicalDeviceFeatures.independentBlend = VK_FALSE;//指明每个附件的VkPipelineColorBlendAttachmentState 是否可以单独设置
	physicalDeviceFeatures.geometryShader = VK_FALSE;//指明是否支持geometry shaders，即是否可以使用 VK_SHADER_STAGE_GEOMETRY_BIT 以及 VK_PIPELINE_STAGE_GEOMETRY_SHADER_BIT
	physicalDeviceFeatures.tessellationShader = VK_FALSE;//指明是否支持tessellation control 以及 evaluation shaders，即是否可以使用VK_SHADER_STAGE_TESSELLATION_CONTROL_BIT, VK_SHADER_STAGE_TESSELLATION_EVALUATION_BIT, VK_PIPELINE_STAGE_TESSELLATION_CONTROL_SHADER_BIT, VK_PIPELINE_STAGE_TESSELLATION_EVALUATION_SHADER_BIT, 以及 VK_STRUCTURE_TYPE_PIPELINE_TESSELLATION_STATE_CREATE_INFO
	physicalDeviceFeatures.sampleRateShading = VK_FALSE;//指明是否支持Sample Shading 以及multisample 插值，如果不支持则VkPipelineMultisampleStateCreateInfo的sampleShadingEnable必须为VK_FALSE，忽略其minSampleShading
	physicalDeviceFeatures.dualSrcBlend = VK_FALSE;//指明是否支持blend operations使用两个source，即是否可以使用e VK_BLEND_FACTOR_SRC1_COLOR, VK_BLEND_FACTOR_ONE_MINUS_SRC1_COLOR, VK_BLEND_FACTOR_SRC1_ALPHA, 以及 VK_BLEND_FACTOR_ONE_MINUS_SRC1_ALPHA
	physicalDeviceFeatures.logicOp = VK_FALSE;;//指明是否支持logic operations，如果不支持则 VkPipelineColorBlendStateCreateInfo的logicOpEnable必须为VK_FALSE，忽略其 logicOp
	physicalDeviceFeatures.multiDrawIndirect = VK_FALSE;//指明是否支持multiple draw indirect，如果不支持 则vkCmdDrawIndirect 以及 vkCmdDrawIndexedIndirect的 drawCount参数只能为0或者1
	physicalDeviceFeatures.drawIndirectFirstInstance = VK_FALSE;//指明是否indirect drawing调用支持firstInstance 参数，如果不支持，则传入其调用的firstInstance必须为0
	physicalDeviceFeatures.depthClamp = VK_FALSE;//指明是否支持depth clamping，如果支持，则可以在 VkPipelineRasterizationStateCreateInfo.depthClampEnable设置为VK_TRUE开启depth clamping
	physicalDeviceFeatures.depthBiasClamp = VK_FALSE;//指明是否支持depth bias clamping，如果不支持则VkPipelineRasterizationStateCreateInfo的 或者 vkCmdSetDepthBias设置的depthBiasClamp必须为0
	physicalDeviceFeatures.fillModeNonSolid = VK_FALSE;//指明是否支持point 以及 wireframe fill modes,即是否可以使用VK_POLYGON_MODE_POINT 以及 VK_POLYGON_MODE_LINE
	physicalDeviceFeatures.depthBounds = VK_FALSE;//指明是否支持depth bounds tests，如果不支持，则VkPipelineDepthStencilStateCreateInfo的depthBoundsTestEnable 必须为VK_FALSE，忽略其minDepthBounds以及maxDepthBounds
	physicalDeviceFeatures.wideLines = VK_FALSE;//指明是否支持线宽不为1.0，如果不支持，则 VkPipelineRasterizationStateCreateInfo的或者 vkCmdSetLineWidth设置的 lineWidth必须为1.0，如果支持，则支持的线宽范围以及粒度见VkPhysicalDeviceLimits的lineWidthRange以及 lineWidthGranularity
	physicalDeviceFeatures.largePoints = VK_FALSE;//指明点大小是否支持大于1.0，如果支持则支持的点大小范围以及粒度见VkPhysicalDeviceLimits的pointSizeRange以及 pointSizeGranularity
	physicalDeviceFeatures.alphaToOne = VK_FALSE;//指明在 Multisample Coverage fragment operation中是否支持替换fragment shader color output的alpha值，如果支持则可以在 VkPipelineRasterizationStateCreateInfo.alphaToOneEnable设置为VK_TRUE开启alpha-to-one行为
	physicalDeviceFeatures.multiViewport = VK_FALSE;//指明是否支持多个viewport，如果不支持，则VkPipelineViewportStateCreateInfo的viewportCount 以及 scissorCount 必须设置为1，vkCmdSetViewport的firstViewport 以及 viewportCount分别设为0和1，vkCmdSetScissor的firstScissor 以及 scissorCount分别设为0和1，VkPipelineViewportExclusiveScissorStateCreateInfoNV的exclusiveScissorCount 必须为0或者1，vkCmdSetExclusiveScissorNV的firstExclusiveScissor 以及 exclusiveScissorCount分别设为0和1
	physicalDeviceFeatures.samplerAnisotropy = VK_FALSE;//指明是否支持anisotropic filtering，如果不支持，则 VkSamplerCreateInfo的anisotropyEnable 必须设置为VK_FALSE
	physicalDeviceFeatures.textureCompressionETC2 = VK_FALSE;//指明是否支持ETC2 以及 EAC 纹理压缩格式，如果支持，则如VK_FORMAT_ETC2_***以及 VK_FORMAT_EAC_*** 的optimalTilingFeatures 必须包含VK_FORMAT_FEATURE_SAMPLED_IMAGE_BIT, VK_FORMAT_FEATURE_BLIT_SRC_BIT 以及 VK_FORMAT_FEATURE_SAMPLED_IMAGE_FILTER_LINEAR_BIT
	physicalDeviceFeatures.textureCompressionASTC_LDR = VK_FALSE;//指明是否支持ASTC LDR 纹理压缩格式，如果支持，则如VK_FORMAT_ASTC_*** 的optimalTilingFeatures 必须包含VK_FORMAT_FEATURE_SAMPLED_IMAGE_BIT, VK_FORMAT_FEATURE_BLIT_SRC_BIT 以及 VK_FORMAT_FEATURE_SAMPLED_IMAGE_FILTER_LINEAR_BIT
	physicalDeviceFeatures.textureCompressionBC = VK_FALSE;//指明是否支持BC 纹理压缩格式，如果支持，则如VK_FORMAT_BC*** 的optimalTilingFeatures 必须包含VK_FORMAT_FEATURE_SAMPLED_IMAGE_BIT, VK_FORMAT_FEATURE_BLIT_SRC_BIT 以及 VK_FORMAT_FEATURE_SAMPLED_IMAGE_FILTER_LINEAR_BIT
	physicalDeviceFeatures.occlusionQueryPrecise = VK_FALSE;//指明是否支持occlusion queries返回实际的采样数，即是否可以在VK_QUERY_TYPE_OCCLUSION 类型的query中使用VK_QUERY_CONTROL_PRECISE_BIT， 详情见p3741
	physicalDeviceFeatures.pipelineStatisticsQuery = VK_FALSE;//指明是否支持pipeline statistics queries，如果不支持则不能创建VK_QUERY_TYPE_PIPELINE_STATISTICS类型的query且  VkQueryPoolCreateInfo.pipelineStatistics必须为0
	physicalDeviceFeatures.vertexPipelineStoresAndAtomics = VK_FALSE;//指明在vertex, tessellation, 以及 geometry shader stages 中 storage buffer以及image是否支持 storage以及atomic操作，如果不支持，则shader中对应资源必须声明为 NonWritable
	physicalDeviceFeatures.fragmentStoresAndAtomics = VK_FALSE;////指明在fragment shader stages 中 storage buffer以及image是否支持 storage以及atomic操作，如果不支持，则shader中对应资源必须声明为 NonWritable
	physicalDeviceFeatures.shaderTessellationAndGeometryPointSize = VK_FALSE;//指明在 tessellation control, tessellation evaluation, 以及 geometry shader stages中是否可以访问PointSize内嵌变量，如果支持，则对应shader stage中可访问的PointSize对应变量为  TessellationPointSize， GeometryPointSize
	physicalDeviceFeatures.shaderImageGatherExtended = VK_FALSE;//指明是否在shader code中可访问image gather instructions的拓展，如果不支持，则OpImage*Gather指明则不能有 Offset 以及 ConstOffsets 操作符
	physicalDeviceFeatures.shaderStorageImageExtendedFormats = VK_FALSE;//指明是否支持所有的storage image extended formats，如果支持，则这些formats的 optimalTilingFeatures 中必须含有 VK_FORMAT_FEATURE_STORAGE_IMAGE_BIT，  storage image extended formats见p3742
	physicalDeviceFeatures.shaderStorageImageMultisample = VK_FALSE;//指明是否支持 multisampled storage images，如果不支持，则以VK_IMAGE_USAGE_STORAGE_BIT创建的image的samples必须为VK_SAMPLE_COUNT_1_BIT
	physicalDeviceFeatures.shaderStorageImageReadWithoutFormat = VK_FALSE;//指明当读取 storage images 以及 storage texel buffers的时候是否需要指定format
	physicalDeviceFeatures.shaderStorageImageWriteWithoutFormat = VK_FALSE;//指明当写入 storage images 以及 storage texel buffers的时候是否需要指定format
	physicalDeviceFeatures.shaderUniformBufferArrayDynamicIndexing = VK_FALSE;//指明 uniform buffers 数组是否可以在shader code中通过一个dynamically uniform integer expressions进行访问，如果不支持，则VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER 或者 VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC 类型的资源数组只能通过常量表达式进行访问
	physicalDeviceFeatures.shaderSampledImageArrayDynamicIndexing = VK_FALSE;//指明samplers 或者 sampled images 数组是否可以在shader code中通过一个dynamically uniform integer expressions进行访问，如果不支持，则VK_DESCRIPTOR_TYPE_SAMPLER, VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, 或者 VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE 类型的资源数组只能通过常量表达式进行访问
	physicalDeviceFeatures.shaderStorageBufferArrayDynamicIndexing = VK_FALSE;//指明 storage buffers 数组是否可以在shader code中通过一个dynamically uniform integer expressions进行访问，如果不支持，则VK_DESCRIPTOR_TYPE_STORAGE_BUFFER 或者 VK_DESCRIPTOR_TYPE_STORAGE_BUFFER_DYNAMIC 类型的资源数组只能通过常量表达式进行访问
	physicalDeviceFeatures.shaderStorageImageArrayDynamicIndexing = VK_FALSE;//指明 storage images 数组是否可以在shader code中通过一个dynamically uniform integer expressions进行访问，如果不支持，则 VK_DESCRIPTOR_TYPE_STORAGE_IMAGE 类型的资源数组只能通过常量表达式进行访问
	physicalDeviceFeatures.shaderClipDistance = VK_FALSE;//指明shader code中是否支持 clip distances，如果不支持，则shader module中不能读取或写入以 ClipDistance 声明的变量
	physicalDeviceFeatures.shaderCullDistance = VK_FALSE;//指明shader code中是否支持 cull distances，如果不支持，则shader module中不能读取或写入以 CullDistance 声明的变量
	physicalDeviceFeatures.shaderFloat64 = VK_FALSE;//指明shade code中是否支持64-bit 浮点数
	physicalDeviceFeatures.shaderInt64 = VK_FALSE;//指明shade code中是否支持64-bit 无符号以及有符号整数
	physicalDeviceFeatures.shaderInt16 = VK_FALSE;//指明shade code中是否支持16-bit 无符号以及有符号整数
	physicalDeviceFeatures.shaderResourceResidency = VK_FALSE;//指明返回resource residency信息的image operations是否在shader code中支持，如果不支持则shader code中不能使用OpImageSparse* 指令
	physicalDeviceFeatures.shaderResourceMinLod = VK_FALSE;//指明指定最小资源LOD信息的image operations是否在shader code中支持，如果不支持则shader code中不能使用 MinLod 操作符
	physicalDeviceFeatures.sparseBinding = VK_FALSE;//指明是否资源内存可以以离散块而不是一个对象来进行管理，如果不支持，则每个资源都要调用一次 vkBindBufferMemory 或者 vkBindImageMemory绑定内存，且资源不能以包含 VK_BUFFER_CREATE_SPARSE_BINDING_BIT或者  VK_IMAGE_CREATE_SPARSE_BINDING_BIT 创建
	physicalDeviceFeatures.sparseResidencyBuffer = VK_FALSE;//指明是否device可以访问partially resident buffers，如果不支持，则buffer不能以 VkBufferCreateInfo.flags包含VK_BUFFER_CREATE_SPARSE_RESIDENCY_BIT 创建
	physicalDeviceFeatures.sparseResidencyImage2D = VK_FALSE;//指明是否device可以以每个pixel一个采样点 访问partially resident 2D images，如果不支持，则以VkImageCreateInfo中imageType设置为 VK_IMAGE_TYPE_2D，samples 设置为VK_SAMPLE_COUNT_1_BIT的创建的image不能以 VkImageCreateInfo.flags包含VK_IMAGE_CREATE_SPARSE_RESIDENCY_BIT 创建
	physicalDeviceFeatures.sparseResidencyImage3D = VK_FALSE;//指明是否device可以访问partially resident 3D images，如果不支持，则以VkImageCreateInfo中imageType设置为  VK_IMAGE_TYPE_3D创建的image不能以 VkImageCreateInfo.flags包含VK_IMAGE_CREATE_SPARSE_RESIDENCY_BIT 创建
	physicalDeviceFeatures.sparseResidency2Samples = VK_FALSE;//指明是否device可以以每个pixel两个采样点 访问partially resident 2D images，如果不支持，则以VkImageCreateInfo中imageType设置为 VK_IMAGE_TYPE_2D，samples 设置为VK_SAMPLE_COUNT_2_BIT的创建的image不能以 VkImageCreateInfo.flags包含VK_IMAGE_CREATE_SPARSE_RESIDENCY_BIT 创建
	physicalDeviceFeatures.sparseResidency4Samples = VK_FALSE;//指明是否device可以以每个pixel四个采样点 访问partially resident 2D images，如果不支持，则以VkImageCreateInfo中imageType设置为 VK_IMAGE_TYPE_2D，samples 设置为VK_SAMPLE_COUNT_4_BIT的创建的image不能以 VkImageCreateInfo.flags包含VK_IMAGE_CREATE_SPARSE_RESIDENCY_BIT 创建
	physicalDeviceFeatures.sparseResidency8Samples = VK_FALSE;//指明是否device可以以每个pixel八个采样点 访问partially resident 2D images，如果不支持，则以VkImageCreateInfo中imageType设置为 VK_IMAGE_TYPE_2D，samples 设置为VK_SAMPLE_COUNT_8_BIT的创建的image不能以 VkImageCreateInfo.flags包含VK_IMAGE_CREATE_SPARSE_RESIDENCY_BIT 创建
	physicalDeviceFeatures.sparseResidency16Samples = VK_FALSE;//指明是否device可以以每个pixel十六个采样点 访问partially resident 2D images，如果不支持，则以VkImageCreateInfo中imageType设置为 VK_IMAGE_TYPE_2D，samples 设置为VK_SAMPLE_COUNT_16_BIT的创建的image不能以 VkImageCreateInfo.flags包含VK_IMAGE_CREATE_SPARSE_RESIDENCY_BIT 创建
	physicalDeviceFeatures.sparseResidencyAliased = VK_FALSE;//指明是否物理设备可以访问多个位置存在别名的数据，如果不支持，则VkBufferCreateInfo 以及 VkImageCreateInfo的flags中不能对应包含VK_BUFFER_CREATE_SPARSE_ALIASED_BIT 以及 VK_IMAGE_CREATE_SPARSE_ALIASED_BIT
	physicalDeviceFeatures.variableMultisampleRate = VK_FALSE;//指明在不使用附件的subpass中绑定到同一个command buffer的所有pipeline的VkPipelineMultisampleStateCreateInfo::rasterizationSamples是否必须相同，如果不支持，则在不使用附件的subpass中所有pipeline的multisample rate 必须相同
	physicalDeviceFeatures.inheritedQueries = VK_FALSE;//指明当激活query时是否可以执行一个secondary command buffer


	//查询core或者拓展支持的features
	VkPhysicalDeviceFeatures2 physicalDeviceFeatures2{};//等价于VkPhysicalDeviceFeaturesKHR
	physicalDeviceFeatures2.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FEATURES_2;
	physicalDeviceFeatures2.pNext = nullptr;

	//等价于vkGetPhysicalDeviceFeaturesKHR
	vkGetPhysicalDeviceFeatures2(physicalDevice, &physicalDeviceFeatures2);//假设正确返回了结果
	physicalDeviceFeatures2.features = physicalDeviceFeatures;//为一个VkPhysicalDeviceFeatures
	


	//VkPhysicalDeviceVulkan11Features ,  可以包含在VkPhysicalDeviceFeatures2.pNext中
	VkPhysicalDeviceVulkan11Features physicalDeviceVulkan11Features{};
	physicalDeviceVulkan11Features.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_1_FEATURES;
	physicalDeviceVulkan11Features.pNext = nullptr;
	physicalDeviceVulkan11Features.storageBuffer16BitAccess = VK_FALSE;//指明是否StorageBuffer, ShaderRecordBufferKHR, 或者 PhysicalStorageBuffer storage class中有Block声明的对象是否能够含有16-bit的整数或者浮点数成员
	physicalDeviceVulkan11Features.uniformAndStorageBuffer16BitAccess = VK_FALSE;//指明是否Uniform storage class中有Block声明的对象是否能够含有16-bit的整数或者浮点数成员
	physicalDeviceVulkan11Features.storagePushConstant16 = VK_FALSE;//指明是否PushConstant storage class能够含有16-bit的整数或者浮点数成员
	physicalDeviceVulkan11Features.storageInputOutput16 = VK_FALSE;//指明是否 Input 以及 Output storage classes能够含有16-bit的整数或者浮点数成员
	physicalDeviceVulkan11Features.multiview = VK_FALSE;//指明是否支持在一个render pass中进行multiview渲染，如果不支持，则每个subpass的view mask必须为0
	physicalDeviceVulkan11Features.multiviewGeometryShader = VK_FALSE;//指明是否支持在一个含有geometry shaders的 render pass中进行multiview渲染，如果不支持，则含有view mask不为0的pipeline不能包含geometry shaders
	physicalDeviceVulkan11Features.multiviewTessellationShader = VK_FALSE;//指明是否支持在一个含有 tessellation shaders的 render pass中进行multiview渲染，如果不支持，则含有view mask不为0的pipeline不能包含 tessellation shaders
	physicalDeviceVulkan11Features.variablePointersStorageBuffer = VK_FALSE;//指明实现是否支持SPIR-V VariablePointersStorageBuffer 能力
	physicalDeviceVulkan11Features.variablePointers = VK_FALSE;//指明实现是否支持SPIR-V VariablePointers 能力
	physicalDeviceVulkan11Features.protectedMemory = VK_FALSE;//指明是否支持 protected memory
	physicalDeviceVulkan11Features.samplerYcbcrConversion = VK_FALSE;//指明实现是否支持sampler Y′CBCR conversion
	physicalDeviceVulkan11Features.shaderDrawParameters = VK_FALSE;//指明实现是否支持SPIR-V DrawParameters 能力


	// VkPhysicalDeviceVulkan12Features ,  可以包含在VkPhysicalDeviceFeatures2.pNext中
	VkPhysicalDeviceVulkan12Features  physicalDeviceVulkan12Features{};
	physicalDeviceVulkan12Features.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_2_FEATURES;
	physicalDeviceVulkan12Features.pNext = nullptr;
	physicalDeviceVulkan12Features.samplerMirrorClampToEdge = VK_FALSE;//指明是否支持VK_SAMPLER_ADDRESS_MODE_MIRROR_CLAMP_TO_EDGE sampler address mode
	physicalDeviceVulkan12Features.drawIndirectCount = VK_FALSE;//指明是否支持vkCmdDrawIndirectCount 以及 vkCmdDrawIndexedIndirectCount 函数的使用
	physicalDeviceVulkan12Features.storageBuffer8BitAccess = VK_FALSE;//指明是否StorageBuffer, ShaderRecordBufferKHR, 或者 PhysicalStorageBuffer storage class中有Block声明的对象是否能够含有8-bit的整数成员
	physicalDeviceVulkan12Features.uniformAndStorageBuffer8BitAccess = VK_FALSE;//指明是否Uniform storage class中有Block声明的对象是否能够含有8-bit的整数成员
	physicalDeviceVulkan12Features.storagePushConstant8 = VK_FALSE;//指明是否PushConstant storage class能够含有8-bit的整数成员
	physicalDeviceVulkan12Features.shaderBufferInt64Atomics = VK_FALSE;//指明是否shader code可以进行buffer上的64-bit的有符号以及无符号的整数atomic operations
	physicalDeviceVulkan12Features.shaderSharedInt64Atomics = VK_FALSE;//指明是否shader code可以进行shared 以及 payload memory上的64-bit的有符号以及无符号的整数atomic operations
	physicalDeviceVulkan12Features.shaderFloat16 = VK_FALSE;//指明shader code是否支持16-bit浮点数
	physicalDeviceVulkan12Features.shaderInt8 = VK_FALSE; // 指明shader code是否支持8-bit无符号以及有符号整数
	physicalDeviceVulkan12Features.descriptorIndexing = VK_FALSE;//指明实现是否支持 Feature Requirements p3899描述的描述符索引的最小集
	physicalDeviceVulkan12Features.shaderInputAttachmentArrayDynamicIndexing = VK_FALSE;//指明input attachments 数组是否可以在shader code中通过一个dynamically uniform integer expressions进行访问，如果不支持，则VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT 类型的资源数组只能通过常量表达式进行访问
	physicalDeviceVulkan12Features.shaderUniformTexelBufferArrayDynamicIndexing = VK_FALSE;//指明uniform texel buffers 数组是否可以在shader code中通过一个dynamically uniform integer expressions进行访问，如果不支持，则VK_DESCRIPTOR_TYPE_UNIFORM_TEXEL_BUFFER 类型的资源数组只能通过常量表达式进行访问
	physicalDeviceVulkan12Features.shaderStorageTexelBufferArrayDynamicIndexing = VK_FALSE;//指明storage texel buffers 数组是否可以在shader code中通过一个dynamically uniform integer expressions进行访问，如果不支持，则VK_DESCRIPTOR_TYPE_STORAGE_TEXEL_BUFFER 类型的资源数组只能通过常量表达式进行访问
	physicalDeviceVulkan12Features.shaderUniformBufferArrayNonUniformIndexing = VK_FALSE;//指明 uniform buffers 数组是否可以在shader code中通过一个non-uniform integer expressions进行访问，如果不支持，则VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER 或者 VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC 类型的资源数组不能通过non-uniform integer expressions 进行访问
	physicalDeviceVulkan12Features.shaderSampledImageArrayNonUniformIndexing = VK_FALSE;//指明samplers 或者 sampled images 数组是否可以在shader code中通过一个non-uniform integer expressions进行访问，如果不支持，则VK_DESCRIPTOR_TYPE_SAMPLER, VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, 或者 VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE类型的资源数组不能通过non-uniform integer expressions 进行访问
	physicalDeviceVulkan12Features.shaderStorageBufferArrayNonUniformIndexing = VK_FALSE;//指明 storage buffers 数组是否可以在shader code中通过一个non-uniform integer expressions进行访问，如果不支持，则VK_DESCRIPTOR_TYPE_STORAGE_BUFFER 或者 VK_DESCRIPTOR_TYPE_STORAGE_BUFFER_DYNAMIC 类型的资源数组不能通过non-uniform integer expressions 进行访问
	physicalDeviceVulkan12Features.shaderStorageImageArrayNonUniformIndexing = VK_FALSE;//指明 storage images 数组是否可以在shader code中通过一个non-uniform integer expressions进行访问，如果不支持，则VK_DESCRIPTOR_TYPE_STORAGE_IMAGE 类型的资源数组不能通过non-uniform integer expressions 进行访问
	physicalDeviceVulkan12Features.shaderInputAttachmentArrayNonUniformIndexing = VK_FALSE;//指明 input attachments 数组是否可以在shader code中通过一个non-uniform integer expressions进行访问，如果不支持，则VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT 类型的资源数组不能通过non-uniform integer expressions 进行访问
	physicalDeviceVulkan12Features.shaderUniformTexelBufferArrayNonUniformIndexing = VK_FALSE;//指明 uniform texel buffers 数组是否可以在shader code中通过一个non-uniform integer expressions进行访问，如果不支持，则VK_DESCRIPTOR_TYPE_UNIFORM_TEXEL_BUFFER 类型的资源数组不能通过non-uniform integer expressions 进行访问
	physicalDeviceVulkan12Features.shaderStorageTexelBufferArrayNonUniformIndexing = VK_FALSE;//指明 storage texel buffers 数组是否可以在shader code中通过一个non-uniform integer expressions进行访问，如果不支持，则VK_DESCRIPTOR_TYPE_STORAGE_TEXEL_BUFFER 类型的资源数组不能通过non-uniform integer expressions 进行访问
	physicalDeviceVulkan12Features.descriptorBindingUniformBufferUpdateAfterBind = VK_FALSE;//指明是否支持在绑定一个descriptor set之后更新uniform buffer descriptors，如果不支持，则VK_DESCRIPTOR_BINDING_UPDATE_AFTER_BIND_BIT不能和 VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER一起使用
	physicalDeviceVulkan12Features.descriptorBindingSampledImageUpdateAfterBind = VK_FALSE;//指明是否支持在绑定一个descriptor set之后更新sampled image descriptors，如果不支持，则VK_DESCRIPTOR_BINDING_UPDATE_AFTER_BIND_BIT不能和 VK_DESCRIPTOR_TYPE_SAMPLER, VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, 或者VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE 一起使用
	physicalDeviceVulkan12Features.descriptorBindingStorageImageUpdateAfterBind = VK_FALSE;//指明是否支持在绑定一个descriptor set之后更新storage image descriptors，如果不支持，则VK_DESCRIPTOR_BINDING_UPDATE_AFTER_BIND_BIT不能和 VK_DESCRIPTOR_TYPE_STORAGE_IMAGE一起使用
	physicalDeviceVulkan12Features.descriptorBindingStorageBufferUpdateAfterBind = VK_FALSE;//指明是否支持在绑定一个descriptor set之后更新storage buffer descriptors，如果不支持，则VK_DESCRIPTOR_BINDING_UPDATE_AFTER_BIND_BIT不能和 VK_DESCRIPTOR_TYPE_STORAGE_BUFFER一起使用
	physicalDeviceVulkan12Features.descriptorBindingUniformTexelBufferUpdateAfterBind = VK_FALSE;//指明是否支持在绑定一个descriptor set之后更新uniform texel buffer descriptors，如果不支持，则VK_DESCRIPTOR_BINDING_UPDATE_AFTER_BIND_BIT不能和 VK_DESCRIPTOR_TYPE_UNIFORM_TEXEL_BUFFER一起使用
	physicalDeviceVulkan12Features.descriptorBindingStorageTexelBufferUpdateAfterBind = VK_FALSE;//指明是否支持在绑定一个descriptor set之后更新storage texel buffer descriptors，如果不支持，则VK_DESCRIPTOR_BINDING_UPDATE_AFTER_BIND_BIT不能和 VK_DESCRIPTOR_TYPE_STORAGE_TEXEL_BUFFER一起使用
	physicalDeviceVulkan12Features.descriptorBindingUpdateUnusedWhilePending = VK_FALSE;//指明是否支持在descriptor set正在使用的时候更新descriptors，如果不支持则不能使用VK_DESCRIPTOR_BINDING_UPDATE_UNUSED_WHILE_PENDING_BIT
	physicalDeviceVulkan12Features.descriptorBindingPartiallyBound = VK_FALSE;//指明是否支持静态使用一个存在descriptor无效的descriptor set binding，如果不支持则不能使用VK_DESCRIPTOR_BINDING_PARTIALLY_BOUND_BIT
	physicalDeviceVulkan12Features.descriptorBindingVariableDescriptorCount = VK_FALSE;//指明是否支持descriptor sets的最后一个binding是大小可变的，如果不支持则不能使用VK_DESCRIPTOR_BINDING_VARIABLE_DESCRIPTOR_COUNT_BIT
	physicalDeviceVulkan12Features.runtimeDescriptorArray = VK_FALSE;//指明是否支持 SPIR-V RuntimeDescriptorArray能力
	physicalDeviceVulkan12Features.samplerFilterMinmax = VK_FALSE;//指明需要的formats的最小集是否支持min/max filtering，如果不支持，则VkSamplerReductionModeCreateInfo中只能使用VK_SAMPLER_REDUCTION_MODE_WEIGHTED_AVERAGE
	physicalDeviceVulkan12Features.scalarBlockLayout = VK_FALSE;//指明是否shader中资源块的layout能否使用 scalar alignment
	physicalDeviceVulkan12Features.imagelessFramebuffer = VK_FALSE;//指明是否支持在render pass开始的时候通过 VkRenderPassAttachmentBeginInfo 指定附件的image view
	physicalDeviceVulkan12Features.uniformBufferStandardLayout = VK_FALSE;//指明是否支持uniform buffers作为storage 或者其他类型的buffer的时候使用相同的layout
	physicalDeviceVulkan12Features.shaderSubgroupExtendedTypes = VK_FALSE;//指明 subgroup operations 是否可以使用 8-bit integer, 16-bit integer, 64-bit integer, 16-bit floating point,以及这些类型的vec值，如果这些类型支持的话
	physicalDeviceVulkan12Features.separateDepthStencilLayouts = VK_FALSE;//指明是否支持对只设置了VK_IMAGE_ASPECT_DEPTH_BIT 或者 VK_IMAGE_ASPECT_STENCIL_BIT 的depth/stencil image使用VkImageMemoryBarrier，且是否VK_IMAGE_LAYOUT_DEPTH_ATTACHMENT_OPTIMAL, VK_IMAGE_LAYOUT_DEPTH_READ_ONLY_OPTIMAL, VK_IMAGE_LAYOUT_STENCIL_ATTACHMENT_OPTIMAL, 或者 VK_IMAGE_LAYOUT_STENCIL_READ_ONLY_OPTIMAL可以使用
	physicalDeviceVulkan12Features.hostQueryReset = VK_FALSE;//指明是否可以在host端用vkResetQueryPool重置query
	physicalDeviceVulkan12Features.timelineSemaphore = VK_FALSE;//指明是否可以创建VkSemaphoreType为VK_SEMAPHORE_TYPE_TIMELINE的semaphore
	physicalDeviceVulkan12Features.bufferDeviceAddress = VK_FALSE;//指明是否支持在shader中访问通过 vkGetBufferDeviceAddress获取的内存地址作为storage buffers进行访问
	physicalDeviceVulkan12Features.bufferDeviceAddressCaptureReplay = VK_FALSE;//指明实现支持保存和重用buffer 以及 device addresses
	physicalDeviceVulkan12Features.bufferDeviceAddressMultiDevice = VK_FALSE;//指明实现支持在以多物理设备创建的逻辑设备上支持bufferDeviceAddress , rayTracingPipeline 以及 rayQuery 特性
	physicalDeviceVulkan12Features.vulkanMemoryModel = VK_FALSE;//指明是否shader modules能够声明VulkanMemoryModel 能力
	physicalDeviceVulkan12Features.vulkanMemoryModelDeviceScope = VK_FALSE;//指明Vulkan Memory Model可以使用 Device scope synchronization.
	physicalDeviceVulkan12Features.vulkanMemoryModelAvailabilityVisibilityChains = VK_FALSE;//指明Vulkan Memory Model可以使用超过一个元素的 availability 以及 visibility chains
	physicalDeviceVulkan12Features.shaderOutputViewportIndex = VK_FALSE;//指明实现支持ShaderViewportIndex SPIR-V 能力，即可以在mesh, vertex 或者 tessellation evaluation shaders以ViewportIndex 内嵌变量声明输出变量
	physicalDeviceVulkan12Features.shaderOutputLayer = VK_FALSE;//指明实现支持 ShaderLayer SPIR-V能力，即可以在mesh, vertex 或者 tessellation evaluation shaders以Layer 内嵌变量声明输出变量
	physicalDeviceVulkan12Features.subgroupBroadcastDynamicId = VK_FALSE;//指明 OpGroupNonUniformBroadcast的Id 操作符以及OpGroupNonUniformQuadBroadcast的 Index 操作符是否可以是动态的uniform值



	//VkPhysicalDeviceVulkan13Features  ,  可以包含在VkPhysicalDeviceFeatures2.pNext中
	VkPhysicalDeviceVulkan13Features physicalDeviceVulkan13Features{};
	physicalDeviceVulkan13Features.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_3_FEATURES;
	physicalDeviceVulkan13Features.pNext = nullptr;
	physicalDeviceVulkan13Features.robustImageAccess = VK_FALSE;
	physicalDeviceVulkan13Features.inlineUniformBlock = VK_FALSE;
	physicalDeviceVulkan13Features.descriptorBindingInlineUniformBlockUpdateAfterBind = VK_FALSE;
	physicalDeviceVulkan13Features.pipelineCreationCacheControl = VK_FALSE;
	physicalDeviceVulkan13Features.privateData = VK_FALSE;
	physicalDeviceVulkan13Features.shaderDemoteToHelperInvocation = VK_FALSE;
	physicalDeviceVulkan13Features.shaderTerminateInvocation = VK_FALSE;
	physicalDeviceVulkan13Features.subgroupSizeControl = VK_FALSE;
	physicalDeviceVulkan13Features.computeFullSubgroups = VK_FALSE;
	physicalDeviceVulkan13Features.synchronization2 = VK_FALSE;
	physicalDeviceVulkan13Features.textureCompressionASTC_HDR = VK_FALSE;
	physicalDeviceVulkan13Features.shaderZeroInitializeWorkgroupMemory = VK_FALSE;
	physicalDeviceVulkan13Features.dynamicRendering = VK_FALSE;
	physicalDeviceVulkan13Features.shaderIntegerDotProduct = VK_FALSE;
	physicalDeviceVulkan13Features.maintenance4 = VK_FALSE;

}












NS_TEST_END