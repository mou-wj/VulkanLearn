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
	physicalDeviceVulkan13Features.robustImageAccess = VK_FALSE;//指明对image的访问会对image view的维度进行边界检查
	physicalDeviceVulkan13Features.inlineUniformBlock = VK_FALSE;//指明是否支持inline uniform block descriptor，如果不支持，则不能使用 VK_DESCRIPTOR_TYPE_INLINE_UNIFORM_BLOCK
	physicalDeviceVulkan13Features.descriptorBindingInlineUniformBlockUpdateAfterBind = VK_FALSE;//指定是否支持在绑定一个descriptor set之后更新inline uniform block descriptors，如果不支持，则VK_DESCRIPTOR_BINDING_UPDATE_AFTER_BIND_BIT不能和 VK_DESCRIPTOR_TYPE_INLINE_UNIFORM_BLOCK一起使用
	physicalDeviceVulkan13Features.pipelineCreationCacheControl = VK_FALSE;//指定Vk*PipelineCreateInfo::flags 中是否可以包含VK_PIPELINE_CREATE_FAIL_ON_PIPELINE_COMPILE_REQUIRED_BIT 或者 VK_PIPELINE_CREATE_EARLY_RETURN_ON_FAILURE_BIT，  VkPipelineCacheCreateInfo::flags 中是否可以包含 VK_PIPELINE_CACHE_CREATE_EXTERNALLY_SYNCHRONIZED_BIT
	physicalDeviceVulkan13Features.privateData = VK_FALSE;//指明是否支持 private data，见p3202
	physicalDeviceVulkan13Features.shaderDemoteToHelperInvocation = VK_FALSE;//指明是否支持SPIR-V DemoteToHelperInvocationEXT 能力
	physicalDeviceVulkan13Features.shaderTerminateInvocation = VK_FALSE;//指明是否支持SPIR-V modules 使用 SPV_KHR_terminate_invocation 拓展
	physicalDeviceVulkan13Features.subgroupSizeControl = VK_FALSE;//指明是否可以通过VK_PIPELINE_SHADER_STAGE_CREATE_ALLOW_VARYING_SUBGROUP_SIZE_BIT 以及  VkPipelineShaderStageRequiredSubgroupSizeCreateInfo 来指定subgroup size
	physicalDeviceVulkan13Features.computeFullSubgroups = VK_FALSE;//指明compute , mesh, 或者 task shaders是否可以通过VK_PIPELINE_SHADER_STAGE_CREATE_REQUIRE_FULL_SUBGROUPS_BIT 来要求使用完整的subgroup
	physicalDeviceVulkan13Features.synchronization2 = VK_FALSE;//指明是否支持 VK_KHR_synchronization2 拓展中说明的一组同步命令
	physicalDeviceVulkan13Features.textureCompressionASTC_HDR = VK_FALSE;//指明是否支持所有的ASTC HDR 压缩纹理格式，如果支持，则如VK_FORMAT_ASTC_*** 的optimalTilingFeatures 必须包含VK_FORMAT_FEATURE_SAMPLED_IMAGE_BIT, VK_FORMAT_FEATURE_BLIT_SRC_BIT 以及 VK_FORMAT_FEATURE_SAMPLED_IMAGE_FILTER_LINEAR_BIT
	physicalDeviceVulkan13Features.shaderZeroInitializeWorkgroupMemory = VK_FALSE;//指明是否支持初始化一个Workgroup storage class类型的变量
	physicalDeviceVulkan13Features.dynamicRendering = VK_FALSE;//指明是否可以通过使用 vkCmdBeginRendering 支持动态render pass instance
	physicalDeviceVulkan13Features.shaderIntegerDotProduct = VK_FALSE;//指明shader module是否可以声明DotProductInputAllKHR, DotProductInput4x8BitKHR, DotProductInput4x8BitPackedKHR 以及 DotProductKHR 能力
	physicalDeviceVulkan13Features.maintenance4 = VK_FALSE;//指明是否支持: 1.使用 VkPipelineLayout 创建一个对象后立即销毁该pipeline；2.LocalSizeId 可以替换 LocalSize;3.以相同参数创建的image的对齐要求相同;4.buffer以及image的大小内存要求不会大于另一个内存比该buffer或者image大的内存大小要求;5.在动态访问之前Push constants不必初始化;6.接口匹配规则允许大的output vec和小的input vec匹配，多的分量会被丢弃


	// VkPhysicalDeviceVariablePointersFeatures  ，等价于 VkPhysicalDeviceVariablePointersFeaturesKHR ,  可以包含在VkPhysicalDeviceFeatures2.pNext中 
	VkPhysicalDeviceVariablePointersFeatures  physicalDeviceVariablePointersFeatures{};
	physicalDeviceVariablePointersFeatures.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VARIABLE_POINTERS_FEATURES;
	physicalDeviceVariablePointersFeatures.pNext = nullptr;
	physicalDeviceVariablePointersFeatures.variablePointersStorageBuffer = VK_FALSE;//指明是否支持SPIR-V VariablePointersStorageBuffer 能力，如果支持，则可以在shader module中声明SPV_KHR_variable_pointers 拓展或者 VariablePointersStorageBuffer 能力
	physicalDeviceVariablePointersFeatures.variablePointers = VK_FALSE;//指明是否支持SPIR-V VariablePointers 能力，如果支持，则可以在shader module中声明 VariablePointers 能力，如果该能力支持，则variablePointersStorageBuffer 也必须支持


	// VkPhysicalDeviceMultiviewFeatures，等价于 VkPhysicalDeviceMultiviewFeaturesKHR ,  可以包含在VkPhysicalDeviceFeatures2.pNext中 
	VkPhysicalDeviceMultiviewFeatures physicalDeviceMultiviewFeatures{};
	physicalDeviceMultiviewFeatures.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MULTIVIEW_FEATURES;
	physicalDeviceMultiviewFeatures.pNext = nullptr;
	physicalDeviceMultiviewFeatures.multiview = VK_FALSE;//指明在一个render pass中是否支持multiview 渲染，如果不支持，则每个subpass的view mask必须为0
	physicalDeviceMultiviewFeatures.multiviewGeometryShader = VK_FALSE;//指明是否支持在一个含有geometry shaders的 render pass中进行multiview渲染，如果不支持，则含有view mask不为0的pipeline不能包含geometry shaders， 如果该特性支持，则multiview 必须支持
	physicalDeviceMultiviewFeatures.multiviewTessellationShader = VK_FALSE;//指明是否支持在一个含有 tessellation shaders的 render pass中进行multiview渲染，如果不支持，则含有view mask不为0的pipeline不能包含 tessellation shaders， 如果该特性支持，则multiview 必须支持


	//VkPhysicalDeviceShaderAtomicFloatFeaturesEXT ,   可以包含在VkPhysicalDeviceFeatures2.pNext中 
	VkPhysicalDeviceShaderAtomicFloatFeaturesEXT physicalDeviceShaderAtomicFloatFeaturesEXT{};
	physicalDeviceShaderAtomicFloatFeaturesEXT.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_ATOMIC_FLOAT_FEATURES_EXT;
	physicalDeviceShaderAtomicFloatFeaturesEXT.pNext = nullptr;
	physicalDeviceShaderAtomicFloatFeaturesEXT.shaderBufferFloat32Atomics = VK_FALSE;//指明shader是否可以在storage buffer上执行32-bit 浮点load, store 以及 exchange atomic operations
	physicalDeviceShaderAtomicFloatFeaturesEXT.shaderBufferFloat32AtomicAdd = VK_FALSE;//指明shader是否可以在storage buffer上执行32-bit 浮点add atomic operations
	physicalDeviceShaderAtomicFloatFeaturesEXT.shaderBufferFloat64Atomics = VK_FALSE;//指明shader是否可以在storage buffer上执行64-bit 浮点load, store 以及 exchange atomic operations
	physicalDeviceShaderAtomicFloatFeaturesEXT.shaderBufferFloat64AtomicAdd = VK_FALSE;//指明shader是否可以在storage buffer上执行64-bit 浮点add atomic operations
	physicalDeviceShaderAtomicFloatFeaturesEXT.shaderSharedFloat32Atomics = VK_FALSE;//指明shader是否可以在shared 以及 payload memory上执行32-bit 浮点load, store 以及 exchange atomic operations
	physicalDeviceShaderAtomicFloatFeaturesEXT.shaderSharedFloat32AtomicAdd = VK_FALSE;//指明shader是否可以在shared 以及 payload memory上执行32-bit 浮点add atomic operations
	physicalDeviceShaderAtomicFloatFeaturesEXT.shaderSharedFloat64Atomics = VK_FALSE;//指明shader是否可以在shared 以及 payload memory上执行64-bit 浮点load, store 以及 exchange atomic operations
	physicalDeviceShaderAtomicFloatFeaturesEXT.shaderSharedFloat64AtomicAdd = VK_FALSE;//指明shader是否可以在shared 以及 payload memory上执行64-bit 浮点add atomic operations
	physicalDeviceShaderAtomicFloatFeaturesEXT.shaderImageFloat32Atomics = VK_FALSE;//指明shader是否可以执行32-bit 浮点load, store 以及 exchange atomic image operations
	physicalDeviceShaderAtomicFloatFeaturesEXT.shaderImageFloat32AtomicAdd = VK_FALSE;//指明shader是否可以执行32-bit 浮点add atomic image operations
	physicalDeviceShaderAtomicFloatFeaturesEXT.sparseImageFloat32Atomics = VK_FALSE;//指明shader是否可以在 sparse images上执行64-bit 浮点load, store 以及 exchange atomic operations
	physicalDeviceShaderAtomicFloatFeaturesEXT.sparseImageFloat32AtomicAdd = VK_FALSE;//指明shader是否可以在 sparse images上执行64-bit 浮点add atomic operations


	//VkPhysicalDeviceShaderAtomicFloat2FeaturesEXT，  可以包含在VkPhysicalDeviceFeatures2.pNext中
	VkPhysicalDeviceShaderAtomicFloat2FeaturesEXT  physicalDeviceShaderAtomicFloat2FeaturesEXT{};
	physicalDeviceShaderAtomicFloat2FeaturesEXT.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_ATOMIC_FLOAT_2_FEATURES_EXT;
	physicalDeviceShaderAtomicFloat2FeaturesEXT.pNext = nullptr;
	physicalDeviceShaderAtomicFloat2FeaturesEXT.shaderBufferFloat16Atomics = VK_FALSE;//指明shader是否可以在storage buffer上执行16-bit 浮点load, store 以及 exchange atomic operations
	physicalDeviceShaderAtomicFloat2FeaturesEXT.shaderBufferFloat16AtomicAdd = VK_FALSE;//指明shader是否可以在storage buffer上执行16-bit 浮点add atomic operations
	physicalDeviceShaderAtomicFloat2FeaturesEXT.shaderBufferFloat16AtomicMinMax = VK_FALSE;//指明shader是否可以在storage buffer上执行16-bit 浮点min 以及max atomic operations
	physicalDeviceShaderAtomicFloat2FeaturesEXT.shaderBufferFloat32AtomicMinMax = VK_FALSE;//指明shader是否可以在storage buffer上执行32-bit 浮点min 以及max atomic operations
	physicalDeviceShaderAtomicFloat2FeaturesEXT.shaderBufferFloat64AtomicMinMax = VK_FALSE;//指明shader是否可以在storage buffer上执行64-bit 浮点min 以及max atomic operations
	physicalDeviceShaderAtomicFloat2FeaturesEXT.shaderSharedFloat16Atomics = VK_FALSE;//指明shader是否可以在shared 以及 payload memory上执行16-bit 浮点load, store 以及 exchange atomic operations
	physicalDeviceShaderAtomicFloat2FeaturesEXT.shaderSharedFloat16AtomicAdd = VK_FALSE;//指明shader是否可以在shared 以及 payload memory上执行16-bit 浮点add atomic operations
	physicalDeviceShaderAtomicFloat2FeaturesEXT.shaderSharedFloat16AtomicMinMax = VK_FALSE;//指明shader是否可以在shared 以及 payload memory上执行16-bit 浮点min 以及max atomic operations
	physicalDeviceShaderAtomicFloat2FeaturesEXT.shaderSharedFloat32AtomicMinMax = VK_FALSE;//指明shader是否可以在shared 以及 payload memory上执行32-bit 浮点min 以及max atomic operations
	physicalDeviceShaderAtomicFloat2FeaturesEXT.shaderSharedFloat64AtomicMinMax = VK_FALSE;//指明shader是否可以在shared 以及 payload memory上执行64-bit 浮点min 以及max atomic operations
	physicalDeviceShaderAtomicFloat2FeaturesEXT.shaderImageFloat32AtomicMinMax = VK_FALSE;//指明shader是否可以执行32-bit 浮点min 以及max atomic image operations
	physicalDeviceShaderAtomicFloat2FeaturesEXT.sparseImageFloat32AtomicMinMax = VK_FALSE;//指明shader是否可以执行64-bit 浮点min 以及max atomic image operations


	// VkPhysicalDeviceShaderAtomicInt64Features ，等价于 VkPhysicalDeviceShaderAtomicInt64FeaturesKHR ,  可以包含在VkPhysicalDeviceFeatures2.pNext中
	VkPhysicalDeviceShaderAtomicInt64Features  physicalDeviceShaderAtomicInt64Features{};
	physicalDeviceShaderAtomicInt64Features.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_ATOMIC_INT64_FEATURES;
	physicalDeviceShaderAtomicInt64Features.pNext = nullptr;
	physicalDeviceShaderAtomicInt64Features.shaderBufferInt64Atomics = VK_FALSE;//指明shader是否可以在buffer上执行64-bit 有符号以及无符号整数 atomic operations
	physicalDeviceShaderAtomicInt64Features.shaderSharedInt64Atomics = VK_FALSE;//指明shader是否可以在shared 以及 payload memory上执行64-bit 有符号以及无符号整数 atomic operations


	//VkPhysicalDeviceShaderImageAtomicInt64FeaturesEXT ，  可以包含在VkPhysicalDeviceFeatures2.pNext中
	VkPhysicalDeviceShaderImageAtomicInt64FeaturesEXT physicalDeviceShaderImageAtomicInt64FeaturesEXT{};
	physicalDeviceShaderImageAtomicInt64FeaturesEXT.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_IMAGE_ATOMIC_INT64_FEATURES_EXT;
	physicalDeviceShaderImageAtomicInt64FeaturesEXT.pNext = nullptr;
	physicalDeviceShaderImageAtomicInt64FeaturesEXT.shaderImageInt64Atomics = VK_FALSE;//指明shader是否可以在image上执行64-bit 有符号以及无符号整数 atomic operations
	physicalDeviceShaderImageAtomicInt64FeaturesEXT.sparseImageInt64Atomics = VK_FALSE;//指明shader是否可以在sparse images上执行64-bit 有符号以及无符号整数 atomic operations


	// VkPhysicalDevice8BitStorageFeatures ,等价于VkPhysicalDevice8BitStorageFeaturesKHR，  可以包含在VkPhysicalDeviceFeatures2.pNext中
	VkPhysicalDevice8BitStorageFeatures   physicalDevice8BitStorageFeatures{};
	physicalDevice8BitStorageFeatures.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_8BIT_STORAGE_FEATURES;
	physicalDevice8BitStorageFeatures.pNext = nullptr;
	physicalDevice8BitStorageFeatures.storageBuffer8BitAccess = VK_FALSE;//指明是否StorageBuffer, ShaderRecordBufferKHR, 或者 PhysicalStorageBuffer storage class中有Block声明的对象是否能够含有8-bit的整数成员
	physicalDevice8BitStorageFeatures.uniformAndStorageBuffer8BitAccess = VK_FALSE;//指明是否Uniform storage class中有Block声明的对象是否能够含有8-bit的整数成员
	physicalDevice8BitStorageFeatures.storagePushConstant8 = VK_FALSE;//指明是否PushConstant storage class能够含有8-bit的整数成员


	//VkPhysicalDevice16BitStorageFeatures ，等价于 VkPhysicalDevice16BitStorageFeaturesKHR ,  可以包含在VkPhysicalDeviceFeatures2.pNext中
	VkPhysicalDevice16BitStorageFeatures physicalDevice16BitStorageFeatures{};
	physicalDevice16BitStorageFeatures.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_16BIT_STORAGE_FEATURES;
	physicalDevice16BitStorageFeatures.pNext = nullptr;
	physicalDevice16BitStorageFeatures.storageBuffer16BitAccess = VK_FALSE;//指明是否StorageBuffer, ShaderRecordBufferKHR, 或者 PhysicalStorageBuffer storage class中有Block声明的对象是否能够含有16-bit的整数以及浮点数成员
	physicalDevice16BitStorageFeatures.uniformAndStorageBuffer16BitAccess = VK_FALSE;//指明是否Uniform storage class中有Block声明的对象是否能够含有16-bit的整数以及浮点数成员
	physicalDevice16BitStorageFeatures.storagePushConstant16 = VK_FALSE;//指明是否PushConstant storage class能够含有16-bit的整数以及浮点数成员
	physicalDevice16BitStorageFeatures.storageInputOutput16 = VK_FALSE;//指明是否 Input 以及 Output storage classes能够含有16-bit的整数以及浮点数成员



	//VkPhysicalDeviceShaderFloat16Int8Features ，等价于VkPhysicalDeviceShaderFloat16Int8FeaturesKHR,  可以包含在VkPhysicalDeviceFeatures2.pNext中
	VkPhysicalDeviceShaderFloat16Int8Features physicalDeviceShaderFloat16Int8Features{};
	physicalDeviceShaderFloat16Int8Features.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_FLOAT16_INT8_FEATURES;
	physicalDeviceShaderFloat16Int8Features.pNext = nullptr;
	physicalDeviceShaderFloat16Int8Features.shaderFloat16 = VK_FALSE;//指明shader code中是否支持16-bit浮点
	physicalDeviceShaderFloat16Int8Features.shaderInt8 = VK_FALSE;//指明shader code中是否支持8-bit有符号以及无符号整数



	//VkPhysicalDeviceShaderClockFeaturesKHR， 可以包含在VkPhysicalDeviceFeatures2.pNext中
	VkPhysicalDeviceShaderClockFeaturesKHR  physicalDeviceShaderClockFeaturesKHR{};
	physicalDeviceShaderClockFeaturesKHR.sType = VK_STRUCTURE_TYPE_MAX_ENUM;//没有定义所以这里定义为非法值
	physicalDeviceShaderClockFeaturesKHR.pNext = nullptr;
	physicalDeviceShaderClockFeaturesKHR.shaderSubgroupClock = VK_FALSE;//指明shaders可以进行Subgroup scoped clock reads
	physicalDeviceShaderClockFeaturesKHR.shaderDeviceClock = VK_FALSE;//指明shaders可以进行Device scoped clock reads.



	//VkPhysicalDeviceSamplerYcbcrConversionFeatures ，等价于 VkPhysicalDeviceSamplerYcbcrConversionFeaturesKHR ,  可以包含在VkPhysicalDeviceFeatures2.pNext中
	VkPhysicalDeviceSamplerYcbcrConversionFeatures  physicalDeviceSamplerYcbcrConversionFeatures{};
	physicalDeviceSamplerYcbcrConversionFeatures.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SAMPLER_YCBCR_CONVERSION_FEATURES;
	physicalDeviceSamplerYcbcrConversionFeatures.pNext = nullptr;
	physicalDeviceSamplerYcbcrConversionFeatures.samplerYcbcrConversion = VK_FALSE;//指明是否支持sampler YCbCr conversion,如果不支持的话就不能使用sampler Y′CBCR conversion


	//VkPhysicalDeviceProtectedMemoryFeatures ,  可以包含在VkPhysicalDeviceFeatures2.pNext中
	VkPhysicalDeviceProtectedMemoryFeatures physicalDeviceProtectedMemoryFeatures{};
	physicalDeviceProtectedMemoryFeatures.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PROTECTED_MEMORY_FEATURES;
	physicalDeviceProtectedMemoryFeatures.pNext = nullptr;
	physicalDeviceProtectedMemoryFeatures.protectedMemory = VK_FALSE;//指明是否支持protected memory


	//VkPhysicalDeviceBlendOperationAdvancedFeaturesEXT  ,  可以包含在VkPhysicalDeviceFeatures2.pNext中
	VkPhysicalDeviceBlendOperationAdvancedFeaturesEXT physicalDeviceBlendOperationAdvancedFeaturesEXT{};
	physicalDeviceBlendOperationAdvancedFeaturesEXT.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_BLEND_OPERATION_ADVANCED_FEATURES_EXT;
	physicalDeviceBlendOperationAdvancedFeaturesEXT.pNext = nullptr;
	physicalDeviceBlendOperationAdvancedFeaturesEXT.advancedBlendCoherentOperations = VK_FALSE;//指明是否使用 advanced blend operations的blending操作保证按照primitive order 原子性执行。如果支持，则认为VK_ACCESS_COLOR_ATTACHMENT_READ_NONCOHERENT_BIT_EXT 等同于VK_ACCESS_COLOR_ATTACHMENT_READ_BIT，不需要额外同步，如果不支持则需要memory dependencies


	//VkPhysicalDeviceConditionalRenderingFeaturesEXT ,  可以包含在VkPhysicalDeviceFeatures2.pNext中
	VkPhysicalDeviceConditionalRenderingFeaturesEXT physicalDeviceConditionalRenderingFeaturesEXT{};
	physicalDeviceConditionalRenderingFeaturesEXT.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_CONDITIONAL_RENDERING_FEATURES_EXT;
	physicalDeviceConditionalRenderingFeaturesEXT.pNext = nullptr;
	physicalDeviceConditionalRenderingFeaturesEXT.conditionalRendering = VK_FALSE;//指明是否支持conditional rendering
	physicalDeviceConditionalRenderingFeaturesEXT.inheritedConditionalRendering = VK_FALSE;//指明当在primary command buffer中激活conditional rendering时，是否可以执行secondary command buffer


	// VkPhysicalDeviceShaderDrawParametersFeatures ，等价于 VkPhysicalDeviceShaderDrawParameterFeatures ,  可以包含在VkPhysicalDeviceFeatures2.pNext中
	VkPhysicalDeviceShaderDrawParametersFeatures physicalDeviceShaderDrawParametersFeatures{};
	physicalDeviceShaderDrawParametersFeatures.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_DRAW_PARAMETERS_FEATURES;
	physicalDeviceShaderDrawParametersFeatures.pNext = nullptr;
	physicalDeviceShaderDrawParametersFeatures.shaderDrawParameters = VK_FALSE;//指明是否支持SPIR-V DrawParameters 能力，如果不支持，则shader module中不能声明SPV_KHR_shader_draw_parameters 扩展以及 DrawParameters 能力。


	//VkPhysicalDeviceMeshShaderFeaturesNV  ，  可以包含在VkPhysicalDeviceFeatures2.pNext中
	VkPhysicalDeviceMeshShaderFeaturesNV physicalDeviceMeshShaderFeaturesNV{};
	physicalDeviceMeshShaderFeaturesNV.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MESH_SHADER_FEATURES_EXT;
	physicalDeviceMeshShaderFeaturesNV.pNext = nullptr;
	physicalDeviceMeshShaderFeaturesNV.taskShader = VK_FALSE;//指明是否支持 task shaders，如果不支持，则不能使用VK_SHADER_STAGE_TASK_BIT_NV 以及 VK_PIPELINE_STAGE_TASK_SHADER_BIT_NV
	physicalDeviceMeshShaderFeaturesNV.meshShader = VK_FALSE;//指明是否支持 mesh shaders，如果不支持，则不能使用VK_SHADER_STAGE_MESH_BIT_NV 以及 VK_PIPELINE_STAGE_MESH_SHADER_BIT_NV


	//VkPhysicalDeviceMeshShaderFeaturesEXT ，  可以包含在VkPhysicalDeviceFeatures2.pNext中
	VkPhysicalDeviceMeshShaderFeaturesEXT physicalDeviceMeshShaderFeaturesEXT{};
	physicalDeviceMeshShaderFeaturesEXT.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MESH_SHADER_PROPERTIES_EXT;
	physicalDeviceMeshShaderFeaturesEXT.pNext = nullptr;
	physicalDeviceMeshShaderFeaturesEXT.taskShader;//指明是否支持 task shaders，如果不支持，则不能使用VK_SHADER_STAGE_TASK_BIT_EXT 以及 VK_PIPELINE_STAGE_TASK_SHADER_BIT_EXT
	physicalDeviceMeshShaderFeaturesEXT.meshShader;//指明是否支持 mesh shaders，如果不支持，则不能使用VK_SHADER_STAGE_MESH_BIT_EXT 以及 VK_PIPELINE_STAGE_MESH_SHADER_BIT_EXT
	physicalDeviceMeshShaderFeaturesEXT.multiviewMeshShader;//指明是否支持在一个含有mesh shaders的 render pass中进行multiview渲染，如果不支持，则含有view mask不为0的pipeline不能包含mesh shaders，如果开启则VkPhysicalDeviceMultiviewFeaturesKHR::multiview 必须开启
	physicalDeviceMeshShaderFeaturesEXT.primitiveFragmentShadingRateMeshShader;//指明mesh shaders中是否支持primitive fragment shading rate，如果开启则VkPhysicalDeviceFragmentShadingRateFeaturesKHR::primitiveFragmentShadingRate 必须开启
	physicalDeviceMeshShaderFeaturesEXT.meshShaderQueries;//指明是否支持使用VK_QUERY_TYPE_MESH_PRIMITIVES_GENERATED_EXT 创建VkQueryPool以及 支持statistic queries能够包含VK_QUERY_PIPELINE_STATISTIC_TASK_SHADER_INVOCATIONS_BIT_EXT 以及VK_QUERY_PIPELINE_STATISTIC_MESH_SHADER_INVOCATIONS_BIT_EXT


	//VkPhysicalDeviceMemoryDecompressionFeaturesNV ，  可以包含在VkPhysicalDeviceFeatures2.pNext中
	VkPhysicalDeviceMemoryDecompressionFeaturesNV physicalDeviceMemoryDecompressionFeaturesNV{};
	physicalDeviceMemoryDecompressionFeaturesNV.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MEMORY_DECOMPRESSION_PROPERTIES_NV;
	physicalDeviceMemoryDecompressionFeaturesNV.pNext = nullptr;
	physicalDeviceMemoryDecompressionFeaturesNV.memoryDecompression = VK_FALSE;//指明是否支持memory decompression


	//VkPhysicalDeviceDescriptorIndexingFeatures  ,  等价于VkPhysicalDeviceDescriptorIndexingFeaturesEXT , 可以包含在VkPhysicalDeviceFeatures2.pNext中
	VkPhysicalDeviceDescriptorIndexingFeatures physicalDeviceDescriptorIndexingFeatures{};
	physicalDeviceDescriptorIndexingFeatures.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DESCRIPTOR_INDEXING_FEATURES;
	physicalDeviceDescriptorIndexingFeatures.pNext = nullptr;
	physicalDeviceDescriptorIndexingFeatures.shaderInputAttachmentArrayDynamicIndexing = VK_FALSE;//指明input attachments 数组是否可以在shader code中通过一个dynamically uniform integer expressions进行访问，如果不支持，则VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT 类型的资源数组只能通过常量表达式进行访问
	physicalDeviceDescriptorIndexingFeatures.shaderUniformTexelBufferArrayDynamicIndexing = VK_FALSE;//指明uniform texel buffers 数组是否可以在shader code中通过一个dynamically uniform integer expressions进行访问，如果不支持，则VK_DESCRIPTOR_TYPE_UNIFORM_TEXEL_BUFFER 类型的资源数组只能通过常量表达式进行访问
	physicalDeviceDescriptorIndexingFeatures.shaderStorageTexelBufferArrayDynamicIndexing = VK_FALSE;//指明storage texel buffers 数组是否可以在shader code中通过一个dynamically uniform integer expressions进行访问，如果不支持，则VK_DESCRIPTOR_TYPE_STORAGE_TEXEL_BUFFER 类型的资源数组只能通过常量表达式进行访问
	physicalDeviceDescriptorIndexingFeatures.shaderUniformBufferArrayNonUniformIndexing = VK_FALSE;//指明 uniform buffers 数组是否可以在shader code中通过一个non-uniform integer expressions进行访问，如果不支持，则VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER 或者 VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC 类型的资源数组不能通过non-uniform integer expressions 进行访问
	physicalDeviceDescriptorIndexingFeatures.shaderSampledImageArrayNonUniformIndexing = VK_FALSE;//指明samplers 或者 sampled images 数组是否可以在shader code中通过一个non-uniform integer expressions进行访问，如果不支持，则VK_DESCRIPTOR_TYPE_SAMPLER, VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, 或者 VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE类型的资源数组不能通过non-uniform integer expressions 进行访问
	physicalDeviceDescriptorIndexingFeatures.shaderStorageBufferArrayNonUniformIndexing = VK_FALSE;//指明 storage buffers 数组是否可以在shader code中通过一个non-uniform integer expressions进行访问，如果不支持，则VK_DESCRIPTOR_TYPE_STORAGE_BUFFER 或者 VK_DESCRIPTOR_TYPE_STORAGE_BUFFER_DYNAMIC 类型的资源数组不能通过non-uniform integer expressions 进行访问
	physicalDeviceDescriptorIndexingFeatures.shaderStorageImageArrayNonUniformIndexing = VK_FALSE;//指明 storage images 数组是否可以在shader code中通过一个non-uniform integer expressions进行访问，如果不支持，则VK_DESCRIPTOR_TYPE_STORAGE_IMAGE 类型的资源数组不能通过non-uniform integer expressions 进行访问
	physicalDeviceDescriptorIndexingFeatures.shaderInputAttachmentArrayNonUniformIndexing = VK_FALSE;//指明 input attachments 数组是否可以在shader code中通过一个non-uniform integer expressions进行访问，如果不支持，则VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT 类型的资源数组不能通过non-uniform integer expressions 进行访问
	physicalDeviceDescriptorIndexingFeatures.shaderUniformTexelBufferArrayNonUniformIndexing = VK_FALSE;//指明 uniform texel buffers 数组是否可以在shader code中通过一个non-uniform integer expressions进行访问，如果不支持，则VK_DESCRIPTOR_TYPE_UNIFORM_TEXEL_BUFFER 类型的资源数组不能通过non-uniform integer expressions 进行访问
	physicalDeviceDescriptorIndexingFeatures.shaderStorageTexelBufferArrayNonUniformIndexing = VK_FALSE;//指明 storage texel buffers 数组是否可以在shader code中通过一个non-uniform integer expressions进行访问，如果不支持，则VK_DESCRIPTOR_TYPE_STORAGE_TEXEL_BUFFER 类型的资源数组不能通过non-uniform integer expressions 进行访问
	physicalDeviceDescriptorIndexingFeatures.descriptorBindingUniformBufferUpdateAfterBind = VK_FALSE;//指明是否支持在绑定一个descriptor set之后更新uniform buffer descriptors，如果不支持，则VK_DESCRIPTOR_BINDING_UPDATE_AFTER_BIND_BIT不能和 VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER一起使用
	physicalDeviceDescriptorIndexingFeatures.descriptorBindingSampledImageUpdateAfterBind = VK_FALSE;//指明是否支持在绑定一个descriptor set之后更新sampled image descriptors，如果不支持，则VK_DESCRIPTOR_BINDING_UPDATE_AFTER_BIND_BIT不能和 VK_DESCRIPTOR_TYPE_SAMPLER, VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, 或者VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE 一起使用
	physicalDeviceDescriptorIndexingFeatures.descriptorBindingStorageImageUpdateAfterBind = VK_FALSE;//指明是否支持在绑定一个descriptor set之后更新storage image descriptors，如果不支持，则VK_DESCRIPTOR_BINDING_UPDATE_AFTER_BIND_BIT不能和 VK_DESCRIPTOR_TYPE_STORAGE_IMAGE一起使用
	physicalDeviceDescriptorIndexingFeatures.descriptorBindingStorageBufferUpdateAfterBind = VK_FALSE;//指明是否支持在绑定一个descriptor set之后更新storage buffer descriptors，如果不支持，则VK_DESCRIPTOR_BINDING_UPDATE_AFTER_BIND_BIT不能和 VK_DESCRIPTOR_TYPE_STORAGE_BUFFER一起使用
	physicalDeviceDescriptorIndexingFeatures.descriptorBindingUniformTexelBufferUpdateAfterBind = VK_FALSE;//指明是否支持在绑定一个descriptor set之后更新uniform texel buffer descriptors，如果不支持，则VK_DESCRIPTOR_BINDING_UPDATE_AFTER_BIND_BIT不能和 VK_DESCRIPTOR_TYPE_UNIFORM_TEXEL_BUFFER一起使用
	physicalDeviceDescriptorIndexingFeatures.descriptorBindingStorageTexelBufferUpdateAfterBind = VK_FALSE;//指明是否支持在绑定一个descriptor set之后更新storage texel buffer descriptors，如果不支持，则VK_DESCRIPTOR_BINDING_UPDATE_AFTER_BIND_BIT不能和 VK_DESCRIPTOR_TYPE_STORAGE_TEXEL_BUFFER一起使用
	physicalDeviceDescriptorIndexingFeatures.descriptorBindingUpdateUnusedWhilePending = VK_FALSE;//指明是否支持在descriptor set正在使用的时候更新descriptors，如果不支持则不能使用VK_DESCRIPTOR_BINDING_UPDATE_UNUSED_WHILE_PENDING_BIT
	physicalDeviceDescriptorIndexingFeatures.descriptorBindingPartiallyBound = VK_FALSE;//指明是否支持静态使用一个存在descriptor无效的descriptor set binding，如果不支持则不能使用VK_DESCRIPTOR_BINDING_PARTIALLY_BOUND_BIT
	physicalDeviceDescriptorIndexingFeatures.descriptorBindingVariableDescriptorCount = VK_FALSE;//指明是否支持descriptor sets的最后一个binding是大小可变的，如果不支持则不能使用VK_DESCRIPTOR_BINDING_VARIABLE_DESCRIPTOR_COUNT_BIT
	physicalDeviceDescriptorIndexingFeatures.runtimeDescriptorArray = VK_FALSE;//指明是否支持 SPIR-V RuntimeDescriptorArray能力

	
	//VkPhysicalDeviceCopyMemoryIndirectFeaturesNV,   可以包含在VkPhysicalDeviceFeatures2.pNext中
	VkPhysicalDeviceCopyMemoryIndirectFeaturesNV  physicalDeviceCopyMemoryIndirectFeaturesNV{};
	physicalDeviceCopyMemoryIndirectFeaturesNV.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_COPY_MEMORY_INDIRECT_FEATURES_NV;
	physicalDeviceCopyMemoryIndirectFeaturesNV.pNext = nullptr;
	physicalDeviceCopyMemoryIndirectFeaturesNV.indirectCopy = VK_FALSE;//指明是否支持 indirect copies


	//VkPhysicalDeviceVertexAttributeDivisorFeaturesKHR  ,等价于 VkPhysicalDeviceVertexAttributeDivisorFeaturesEXT，    可以包含在VkPhysicalDeviceFeatures2.pNext中
	VkPhysicalDeviceVertexAttributeDivisorFeaturesKHR physicalDeviceVertexAttributeDivisorFeaturesKHR{};
	physicalDeviceVertexAttributeDivisorFeaturesKHR.sType = VK_STRUCTURE_TYPE_MAX_ENUM;//没有定义这里定义为非法值
	physicalDeviceVertexAttributeDivisorFeaturesKHR.pNext = nullptr;
	physicalDeviceVertexAttributeDivisorFeaturesKHR.vertexAttributeInstanceRateDivisor = VK_FALSE;//指明是否在instance rendering中 vertex attribute可能会被重复获取
	physicalDeviceVertexAttributeDivisorFeaturesKHR.vertexAttributeInstanceRateZeroDivisor = VK_FALSE;//指明是否支持VkVertexInputBindingDivisorDescriptionEXT::divisor为0


	// VkPhysicalDeviceASTCDecodeFeaturesEXT ，    可以包含在VkPhysicalDeviceFeatures2.pNext中 
	VkPhysicalDeviceASTCDecodeFeaturesEXT  physicalDeviceASTCDecodeFeaturesEXT{};
	physicalDeviceASTCDecodeFeaturesEXT.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_ASTC_DECODE_FEATURES_EXT;
	physicalDeviceASTCDecodeFeaturesEXT.pNext = nullptr;
	physicalDeviceASTCDecodeFeaturesEXT.decodeModeSharedExponent = VK_FALSE;//指明是否支持解压ASTC 压缩格式到VK_FORMAT_E5B9G9R9_UFLOAT_PACK32


	//VkPhysicalDeviceTransformFeedbackFeaturesEXT  ，    可以包含在VkPhysicalDeviceFeatures2.pNext中 
	VkPhysicalDeviceTransformFeedbackFeaturesEXT physicalDeviceTransformFeedbackFeaturesEXT{};
	physicalDeviceTransformFeedbackFeaturesEXT.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_TRANSFORM_FEEDBACK_FEATURES_EXT;
	physicalDeviceTransformFeedbackFeaturesEXT.pNext = nullptr;
	physicalDeviceTransformFeedbackFeaturesEXT.transformFeedback = VK_FALSE;//指明是否支持transform feedback且shader module中可以是否声明TransformFeedback 能力
	physicalDeviceTransformFeedbackFeaturesEXT.geometryStreams = VK_FALSE;//指明是否支持GeometryStreams SPIR-V 能力


	//VkPhysicalDeviceVulkanMemoryModelFeatures   ， 等价于VkPhysicalDeviceVulkanMemoryModelFeaturesKHR，可以包含在VkPhysicalDeviceFeatures2.pNext中 
	VkPhysicalDeviceVulkanMemoryModelFeatures physicalDeviceVulkanMemoryModelFeatures{};
	physicalDeviceVulkanMemoryModelFeatures.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_MEMORY_MODEL_FEATURES;
	physicalDeviceVulkanMemoryModelFeatures.pNext = nullptr;
	physicalDeviceVulkanMemoryModelFeatures.vulkanMemoryModel = VK_FALSE;//指明是否shader module可以声明 VulkanMemoryModel能力
	physicalDeviceVulkanMemoryModelFeatures.vulkanMemoryModelDeviceScope = VK_FALSE;//指明是否Vulkan Memory Mode可以使用 Device scope synchronization，也指明是否shader module可以声明VulkanMemoryModelDeviceScope 能力
	physicalDeviceVulkanMemoryModelFeatures.vulkanMemoryModelAvailabilityVisibilityChains = VK_FALSE;//指明是否 Vulkan Memory Model可以使用超过一个元素的 availability and visibility chains


	//VkPhysicalDeviceInlineUniformBlockFeatures  , 等价于VkPhysicalDeviceInlineUniformBlockFeaturesEXT，可以包含在VkPhysicalDeviceFeatures2.pNext中 
	VkPhysicalDeviceInlineUniformBlockFeatures physicalDeviceInlineUniformBlockFeatures{};
	physicalDeviceInlineUniformBlockFeatures.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_INLINE_UNIFORM_BLOCK_FEATURES_EXT;
	physicalDeviceInlineUniformBlockFeatures.pNext = nullptr;
	physicalDeviceInlineUniformBlockFeatures.inlineUniformBlock = VK_FALSE;//指明是否支持inline uniform block descriptor，如果不支持，则不能使用 VK_DESCRIPTOR_TYPE_INLINE_UNIFORM_BLOCK
	physicalDeviceInlineUniformBlockFeatures.descriptorBindingInlineUniformBlockUpdateAfterBind = VK_FALSE;//指定是否支持在绑定一个descriptor set之后更新inline uniform block descriptors，如果不支持，则VK_DESCRIPTOR_BINDING_UPDATE_AFTER_BIND_BIT不能和 VK_DESCRIPTOR_TYPE_INLINE_UNIFORM_BLOCK一起使用


	//VkPhysicalDeviceRepresentativeFragmentTestFeaturesNV ，可以包含在VkPhysicalDeviceFeatures2.pNext中 
	VkPhysicalDeviceRepresentativeFragmentTestFeaturesNV physicalDeviceRepresentativeFragmentTestFeaturesNV{};
	physicalDeviceRepresentativeFragmentTestFeaturesNV.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_REPRESENTATIVE_FRAGMENT_TEST_FEATURES_NV;
	physicalDeviceRepresentativeFragmentTestFeaturesNV.pNext = nullptr;
	physicalDeviceRepresentativeFragmentTestFeaturesNV.representativeFragmentTest = VK_FALSE;//指明是否支持representative fragment test， 见Representative Fragment Test. p2804


	//VkPhysicalDeviceExclusiveScissorFeaturesNV  ，可以包含在VkPhysicalDeviceFeatures2.pNext中 
	VkPhysicalDeviceExclusiveScissorFeaturesNV physicalDeviceExclusiveScissorFeaturesNV{};
	physicalDeviceExclusiveScissorFeaturesNV.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_EXCLUSIVE_SCISSOR_FEATURES_NV;
	physicalDeviceExclusiveScissorFeaturesNV.pNext = nullptr;
	physicalDeviceExclusiveScissorFeaturesNV.exclusiveScissor = VK_FALSE;//指明是否支持 exclusive scissor test


	//VkPhysicalDeviceCornerSampledImageFeaturesNV   ，可以包含在VkPhysicalDeviceFeatures2.pNext中 
	VkPhysicalDeviceCornerSampledImageFeaturesNV physicalDeviceCornerSampledImageFeaturesNV{};
	physicalDeviceCornerSampledImageFeaturesNV.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_CORNER_SAMPLED_IMAGE_FEATURES_NV;
	physicalDeviceCornerSampledImageFeaturesNV.pNext = nullptr;
	physicalDeviceCornerSampledImageFeaturesNV.cornerSampledImage = VK_FALSE;//指明image是否可以以 VkImageCreateInfo::flags包含 VK_IMAGE_CREATE_CORNER_SAMPLED_BIT_NV 创建，见p1077  Corner-Sampled Images.


	//VkPhysicalDeviceComputeShaderDerivativesFeaturesNV，可以包含在VkPhysicalDeviceFeatures2.pNext中 
	VkPhysicalDeviceComputeShaderDerivativesFeaturesNV  physicalDeviceComputeShaderDerivativesFeaturesNV{};
	physicalDeviceComputeShaderDerivativesFeaturesNV.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_COMPUTE_SHADER_DERIVATIVES_FEATURES_NV;
	physicalDeviceComputeShaderDerivativesFeaturesNV.pNext = nullptr;
	physicalDeviceComputeShaderDerivativesFeaturesNV.computeDerivativeGroupQuads = VK_FALSE;//指明是否支持ComputeDerivativeGroupQuadsNV SPIR-V 能力
	physicalDeviceComputeShaderDerivativesFeaturesNV.computeDerivativeGroupLinear = VK_FALSE;//指明是否支持ComputeDerivativeGroupLinearNV SPIR-V 能力



	//VkPhysicalDeviceFragmentShaderBarycentricFeaturesKHR， 等价于VkPhysicalDeviceFragmentShaderBarycentricFeaturesNV   , 可以包含在VkPhysicalDeviceFeatures2.pNext中 
	VkPhysicalDeviceFragmentShaderBarycentricFeaturesKHR  physicalDeviceFragmentShaderBarycentricFeaturesKHR{};
	physicalDeviceFragmentShaderBarycentricFeaturesKHR.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FRAGMENT_SHADER_BARYCENTRIC_FEATURES_KHR;
	physicalDeviceFragmentShaderBarycentricFeaturesKHR.pNext = nullptr;
	physicalDeviceFragmentShaderBarycentricFeaturesKHR.fragmentShaderBarycentric = VK_FALSE;//指明fragment shader中是否支持BaryCoordKHR 以及 BaryCoordNoPerspKHR 内置变量以及支持用 PerVertexKHR SPIR - V声明shader 输入变量


	//VkPhysicalDeviceShaderImageFootprintFeaturesNV , 可以包含在VkPhysicalDeviceFeatures2.pNext中 
	VkPhysicalDeviceShaderImageFootprintFeaturesNV  physicalDeviceShaderImageFootprintFeaturesNV{};
	physicalDeviceShaderImageFootprintFeaturesNV.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_IMAGE_FOOTPRINT_FEATURES_NV;
	physicalDeviceShaderImageFootprintFeaturesNV.pNext = nullptr;
	physicalDeviceShaderImageFootprintFeaturesNV.imageFootprint = VK_FALSE;//指明是否支持ImageFootprintNV SPIR-V 能力


	//VkPhysicalDeviceShadingRateImageFeaturesNV，可以包含在VkPhysicalDeviceFeatures2.pNext中 
	VkPhysicalDeviceShadingRateImageFeaturesNV  physicalDeviceShadingRateImageFeaturesNV{};
	physicalDeviceShadingRateImageFeaturesNV.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADING_RATE_IMAGE_FEATURES_NV;
	physicalDeviceShadingRateImageFeaturesNV.pNext = nullptr;
	physicalDeviceShadingRateImageFeaturesNV.shadingRateImage = VK_FALSE;//指明是否可以使用一个shading rate image来驱动fragment processing中一个高效的shading rate，也指明是否支持ShadingRateNV SPIR-V execution mode
	physicalDeviceShadingRateImageFeaturesNV.shadingRateCoarseSampleOrder = VK_FALSE;//指明在含有多个pixel的fragment中是否支持用户对coverage sample的顺序自定义


	//VkPhysicalDeviceFragmentDensityMapFeaturesEXT，可以包含在VkPhysicalDeviceFeatures2.pNext中 
	VkPhysicalDeviceFragmentDensityMapFeaturesEXT  physicalDeviceFragmentDensityMapFeaturesEXT{};
	physicalDeviceFragmentDensityMapFeaturesEXT.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FRAGMENT_DENSITY_MAP_FEATURES_EXT;
	physicalDeviceFragmentDensityMapFeaturesEXT.pNext = nullptr;
	physicalDeviceFragmentDensityMapFeaturesEXT.fragmentDensityMap = VK_FALSE;//指明是否支持render pass含有一个fragment density map attachment
	physicalDeviceFragmentDensityMapFeaturesEXT.fragmentDensityMapDynamic = VK_FALSE;//指明是否支持动态的fragment density map image views ，如果不支持，则VkImageViewCreateInfo::flags中不能包含VK_IMAGE_VIEW_CREATE_FRAGMENT_DENSITY_MAP_DYNAMIC_BIT_EXT
	physicalDeviceFragmentDensityMapFeaturesEXT.fragmentDensityMapNonSubsampledImages = VK_FALSE;//指明含一个fragment density map render pass中是否可以支持non-subsampled image attachments，如果不支持则含一个fragment density map attachment 的render pass必须绑定一个subsampled attachments



	// VkPhysicalDeviceFragmentDensityMap2FeaturesEXT , 可以包含在VkPhysicalDeviceFeatures2.pNext中 
	VkPhysicalDeviceFragmentDensityMap2FeaturesEXT   physicalDeviceFragmentDensityMap2FeaturesEXT{};
	physicalDeviceFragmentDensityMap2FeaturesEXT.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FRAGMENT_DENSITY_MAP_2_FEATURES_EXT;
	physicalDeviceFragmentDensityMap2FeaturesEXT.pNext = nullptr;
	physicalDeviceFragmentDensityMap2FeaturesEXT.fragmentDensityMapDeferred = VK_FALSE;//指明是否支持对fragment density map image views的延迟读取 ，如果不支持，则VkImageViewCreateInfo::flags中不能包含VK_IMAGE_VIEW_CREATE_FRAGMENT_DENSITY_MAP_DEFERRED_BIT_EXT


	// VkPhysicalDeviceFragmentDensityMapOffsetFeaturesQCOM , 可以包含在VkPhysicalDeviceFeatures2.pNext中 
	VkPhysicalDeviceFragmentDensityMapOffsetFeaturesQCOM   physicalDeviceFragmentDensityMapOffsetFeaturesQCOM{};
	physicalDeviceFragmentDensityMapOffsetFeaturesQCOM.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FRAGMENT_DENSITY_MAP_OFFSET_FEATURES_QCOM;
	physicalDeviceFragmentDensityMapOffsetFeaturesQCOM.pNext = nullptr;
	physicalDeviceFragmentDensityMapOffsetFeaturesQCOM.fragmentDensityMapOffset = VK_FALSE;//指明是否支持fragment density map offsets


	// VkPhysicalDeviceInvocationMaskFeaturesHUAWEI , 可以包含在VkPhysicalDeviceFeatures2.pNext中 
	VkPhysicalDeviceInvocationMaskFeaturesHUAWEI   physicalDeviceInvocationMaskFeaturesHUAWEI{};
	physicalDeviceInvocationMaskFeaturesHUAWEI.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_INVOCATION_MASK_FEATURES_HUAWEI;
	physicalDeviceInvocationMaskFeaturesHUAWEI.pNext = nullptr;
	physicalDeviceInvocationMaskFeaturesHUAWEI.invocationMask = VK_FALSE;//指明是否可以使用一个invocation mask image 来优化 ray dispatch.


	//VkPhysicalDeviceScalarBlockLayoutFeatures， 等价于VkPhysicalDeviceScalarBlockLayoutFeaturesEXT   , 可以包含在VkPhysicalDeviceFeatures2.pNext中 
	VkPhysicalDeviceScalarBlockLayoutFeatures  physicalDeviceScalarBlockLayoutFeatures{};
	physicalDeviceScalarBlockLayoutFeatures.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SCALAR_BLOCK_LAYOUT_FEATURES;
	physicalDeviceScalarBlockLayoutFeatures.pNext = nullptr;
	physicalDeviceScalarBlockLayoutFeatures.scalarBlockLayout = VK_FALSE;//指明是否shader中资源块的layout能否使用 scalar alignment


	//VkPhysicalDeviceUniformBufferStandardLayoutFeatures， 等价于VkPhysicalDeviceUniformBufferStandardLayoutFeaturesKHR   , 可以包含在VkPhysicalDeviceFeatures2.pNext中 
	VkPhysicalDeviceUniformBufferStandardLayoutFeatures  physicalDeviceUniformBufferStandardLayoutFeatures{};
	physicalDeviceUniformBufferStandardLayoutFeatures.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_UNIFORM_BUFFER_STANDARD_LAYOUT_FEATURES;
	physicalDeviceUniformBufferStandardLayoutFeatures.pNext = nullptr;
	physicalDeviceUniformBufferStandardLayoutFeatures.uniformBufferStandardLayout = VK_FALSE;//指明是否支持uniform buffers作为storage 或者其他类型的buffer的时候使用相同的layout


	// VkPhysicalDeviceDepthClipEnableFeaturesEXT , 可以包含在VkPhysicalDeviceFeatures2.pNext中 
	VkPhysicalDeviceDepthClipEnableFeaturesEXT   physicalDeviceDepthClipEnableFeaturesEXT{};
	physicalDeviceDepthClipEnableFeaturesEXT.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DEPTH_CLIP_ENABLE_FEATURES_EXT;
	physicalDeviceDepthClipEnableFeaturesEXT.pNext = nullptr;
	physicalDeviceDepthClipEnableFeaturesEXT.depthClipEnable = VK_FALSE;//指明是否支持使用 VkPipelineRasterizationDepthClipStateCreateInfoEXT 来显式设置 depth clipping operation，如果不支持则 VkPipelineRasterizationStateCreateInfo::depthClampEnable 必须为VK_FALSE


	// VkPhysicalDeviceMemoryPriorityFeaturesEXT , 可以包含在VkPhysicalDeviceFeatures2.pNext中 
	VkPhysicalDeviceMemoryPriorityFeaturesEXT   physicalDeviceMemoryPriorityFeaturesEXT{};
	physicalDeviceMemoryPriorityFeaturesEXT.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MEMORY_PRIORITY_FEATURES_EXT;
	physicalDeviceMemoryPriorityFeaturesEXT.pNext = nullptr;
	physicalDeviceMemoryPriorityFeaturesEXT.memoryPriority = VK_FALSE;//指明是否支持使用  VkMemoryPriorityAllocateInfoEXT 在分配memory的时候指定memory priorities



	//VkPhysicalDeviceBufferDeviceAddressFeatures  ， 等价于VkPhysicalDeviceBufferDeviceAddressFeaturesKHR，可以包含在VkPhysicalDeviceFeatures2.pNext中 
	VkPhysicalDeviceBufferDeviceAddressFeatures  physicalDeviceBufferDeviceAddressFeatures{};
	physicalDeviceBufferDeviceAddressFeatures.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_BUFFER_DEVICE_ADDRESS_FEATURES;
	physicalDeviceBufferDeviceAddressFeatures.pNext = nullptr;
	physicalDeviceBufferDeviceAddressFeatures.bufferDeviceAddress = VK_FALSE;//指明是否支持在shader中访问通过 vkGetBufferDeviceAddress获取的内存地址作为storage buffers进行访问
	physicalDeviceBufferDeviceAddressFeatures.bufferDeviceAddressCaptureReplay = VK_FALSE;//指明实现支持保存和重用buffer 以及 device addresses
	physicalDeviceBufferDeviceAddressFeatures.bufferDeviceAddressMultiDevice = VK_FALSE;//指明实现支持在以多物理设备创建的逻辑设备上支持bufferDeviceAddress , rayTracingPipeline 以及 rayQuery 特性

	
	//VkPhysicalDeviceBufferDeviceAddressFeaturesEXT  ， 等价于VkPhysicalDeviceBufferAddressFeaturesEXT，可以包含在VkPhysicalDeviceFeatures2.pNext中 
	VkPhysicalDeviceBufferDeviceAddressFeaturesEXT  physicalDeviceBufferDeviceAddressFeaturesEXT{};
	physicalDeviceBufferDeviceAddressFeaturesEXT.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_BUFFER_DEVICE_ADDRESS_FEATURES_EXT;
	physicalDeviceBufferDeviceAddressFeaturesEXT.pNext = nullptr;
	physicalDeviceBufferDeviceAddressFeaturesEXT.bufferDeviceAddress = VK_FALSE;//指明是否支持在shader中访问通过 vkGetBufferDeviceAddressEXT获取的内存地址作为storage buffers进行访问
	physicalDeviceBufferDeviceAddressFeaturesEXT.bufferDeviceAddressCaptureReplay = VK_FALSE;//指明实现支持保存和重用buffer 以及 device addresses
	physicalDeviceBufferDeviceAddressFeaturesEXT.bufferDeviceAddressMultiDevice = VK_FALSE;//指明实现支持在以多物理设备创建的逻辑设备上支持bufferDeviceAddress 特性,如果不支持，则不能在以多物理设备创建的逻辑设备上查询内存地址


	// VkPhysicalDeviceDedicatedAllocationImageAliasingFeaturesNV , 可以包含在VkPhysicalDeviceFeatures2.pNext中 
	VkPhysicalDeviceDedicatedAllocationImageAliasingFeaturesNV   physicalDeviceDedicatedAllocationImageAliasingFeaturesNV{};
	physicalDeviceDedicatedAllocationImageAliasingFeaturesNV.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DEDICATED_ALLOCATION_IMAGE_ALIASING_FEATURES_NV;
	physicalDeviceDedicatedAllocationImageAliasingFeaturesNV.pNext = nullptr;
	physicalDeviceDedicatedAllocationImageAliasingFeaturesNV.dedicatedAllocationImageAliasing = VK_FALSE;//指明是否可以对一个兼容的以专有分配 dedicated allocation的image对象取别名


	//VkPhysicalDeviceImagelessFramebufferFeatures， 等价于VkPhysicalDeviceImagelessFramebufferFeaturesKHR   , 可以包含在VkPhysicalDeviceFeatures2.pNext中 
	VkPhysicalDeviceImagelessFramebufferFeatures  physicalDeviceImagelessFramebufferFeatures{};
	physicalDeviceImagelessFramebufferFeatures.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_IMAGELESS_FRAMEBUFFER_FEATURES;
	physicalDeviceImagelessFramebufferFeatures.pNext = nullptr;
	physicalDeviceImagelessFramebufferFeatures.imagelessFramebuffer = VK_FALSE;//指明是否支持在render pass开始的时候通过 VkRenderPassAttachmentBeginInfo 指定附件的image view


	//VkPhysicalDeviceFragmentShaderInterlockFeaturesEXT ，可以包含在VkPhysicalDeviceFeatures2.pNext中 
	VkPhysicalDeviceFragmentShaderInterlockFeaturesEXT  physicalDeviceFragmentShaderInterlockFeaturesEXT{};
	physicalDeviceFragmentShaderInterlockFeaturesEXT.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FRAGMENT_SHADER_INTERLOCK_FEATURES_EXT;
	physicalDeviceFragmentShaderInterlockFeaturesEXT.pNext = nullptr;
	physicalDeviceFragmentShaderInterlockFeaturesEXT.fragmentShaderSampleInterlock = VK_FALSE;//指明是否支持FragmentShaderSampleInterlockEXT SPIR-V 能力
	physicalDeviceFragmentShaderInterlockFeaturesEXT.fragmentShaderPixelInterlock = VK_FALSE;//指明是否支持FragmentShaderPixelInterlockEXT SPIR-V 能力
	physicalDeviceFragmentShaderInterlockFeaturesEXT.fragmentShaderShadingRateInterlock = VK_FALSE;//指明是否支持FragmentShaderShadingRateInterlockEXT SPIR-V 能力



	//VkPhysicalDeviceCooperativeMatrixFeaturesNV ，可以包含在VkPhysicalDeviceFeatures2.pNext中 
	VkPhysicalDeviceCooperativeMatrixFeaturesNV  physicalDeviceCooperativeMatrixFeaturesNV{};
	physicalDeviceCooperativeMatrixFeaturesNV.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_COOPERATIVE_MATRIX_PROPERTIES_NV;
	physicalDeviceCooperativeMatrixFeaturesNV.pNext = nullptr;
	physicalDeviceCooperativeMatrixFeaturesNV.cooperativeMatrix = VK_FALSE;//指明是否支持 CooperativeMatrixNV SPIR-V 能力
	physicalDeviceCooperativeMatrixFeaturesNV.cooperativeMatrixRobustBufferAccess = VK_FALSE;//指明是否支持以SPIR-V OpCooperativeMatrixLoadNV 以及 OpCooperativeMatrixStoreNV指令访问robust buffer


	//VkPhysicalDeviceCooperativeMatrixFeaturesKHR ，可以包含在VkPhysicalDeviceFeatures2.pNext中 
	VkPhysicalDeviceCooperativeMatrixFeaturesKHR  physicalDeviceCooperativeMatrixFeaturesKHR{};
	physicalDeviceCooperativeMatrixFeaturesKHR.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_COOPERATIVE_MATRIX_PROPERTIES_KHR;
	physicalDeviceCooperativeMatrixFeaturesKHR.pNext = nullptr;
	physicalDeviceCooperativeMatrixFeaturesKHR.cooperativeMatrix = VK_FALSE;//指明是否支持 CooperativeMatrixKHR SPIR-V 能力
	physicalDeviceCooperativeMatrixFeaturesKHR.cooperativeMatrixRobustBufferAccess = VK_FALSE;//指明是否支持以SPIR-V OpCooperativeMatrixLoadKHR 以及 OpCooperativeMatrixStoreKHR指令访问robust buffer


	//VkPhysicalDeviceYcbcrImageArraysFeaturesEXT ，可以包含在VkPhysicalDeviceFeatures2.pNext中 
	VkPhysicalDeviceYcbcrImageArraysFeaturesEXT  physicalDeviceYcbcrImageArraysFeaturesEXT{};
	physicalDeviceYcbcrImageArraysFeaturesEXT.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_YCBCR_IMAGE_ARRAYS_FEATURES_EXT;
	physicalDeviceYcbcrImageArraysFeaturesEXT.pNext = nullptr;
	physicalDeviceYcbcrImageArraysFeaturesEXT.ycbcrImageArrays = VK_FALSE;//指明是否支持创建一个多array layer的image，该image的format需要Y′CBCR conversion


	//VkPhysicalDeviceShaderSubgroupExtendedTypesFeatures ，等价于VkPhysicalDeviceShaderSubgroupExtendedTypesFeaturesKHR ，可以包含在VkPhysicalDeviceFeatures2.pNext中 
	VkPhysicalDeviceShaderSubgroupExtendedTypesFeatures  physicalDeviceShaderSubgroupExtendedTypesFeatures{};
	physicalDeviceShaderSubgroupExtendedTypesFeatures.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_SUBGROUP_EXTENDED_TYPES_FEATURES;
	physicalDeviceShaderSubgroupExtendedTypesFeatures.pNext = nullptr;
	physicalDeviceShaderSubgroupExtendedTypesFeatures.shaderSubgroupExtendedTypes = VK_FALSE;//指明 subgroup operations 是否可以使用 8-bit integer, 16-bit integer, 64-bit integer, 16-bit floating point,以及这些类型的vec值，如果这些类型支持的话


	//VkPhysicalDeviceHostQueryResetFeatures ，等价于VkPhysicalDeviceHostQueryResetFeaturesEXT ，可以包含在VkPhysicalDeviceFeatures2.pNext中 
	VkPhysicalDeviceHostQueryResetFeatures  physicalDeviceHostQueryResetFeatures{};
	physicalDeviceHostQueryResetFeatures.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_SUBGROUP_EXTENDED_TYPES_FEATURES;
	physicalDeviceHostQueryResetFeatures.pNext = nullptr;
	physicalDeviceHostQueryResetFeatures.hostQueryReset = VK_FALSE;//指明是否可以在host端用vkResetQueryPool重置query


	//VkPhysicalDeviceShaderIntegerFunctions2FeaturesINTEL ，可以包含在VkPhysicalDeviceFeatures2.pNext中 
	VkPhysicalDeviceShaderIntegerFunctions2FeaturesINTEL  physicalDeviceShaderIntegerFunctions2FeaturesINTEL{};
	physicalDeviceShaderIntegerFunctions2FeaturesINTEL.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_INTEGER_FUNCTIONS_2_FEATURES_INTEL;
	physicalDeviceShaderIntegerFunctions2FeaturesINTEL.pNext = nullptr;
	physicalDeviceShaderIntegerFunctions2FeaturesINTEL.shaderIntegerFunctions2 = VK_FALSE;///指明是否支持  IntegerFunctions2INTEL SPIR-V 能力


	//VkPhysicalDeviceCoverageReductionModeFeaturesNV ，可以包含在VkPhysicalDeviceFeatures2.pNext中 
	VkPhysicalDeviceCoverageReductionModeFeaturesNV  physicalDeviceCoverageReductionModeFeaturesNV{};
	physicalDeviceCoverageReductionModeFeaturesNV.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_COVERAGE_REDUCTION_MODE_FEATURES_NV;
	physicalDeviceCoverageReductionModeFeaturesNV.pNext = nullptr;
	physicalDeviceCoverageReductionModeFeaturesNV.coverageReductionMode = VK_FALSE;//指明是否支持  coverage reduction modes. 见Coverage Reduction p2811


	//VkPhysicalDeviceTimelineSemaphoreFeatures ，等价于 VkPhysicalDeviceTimelineSemaphoreFeaturesKHR，可以包含在VkPhysicalDeviceFeatures2.pNext中 
	VkPhysicalDeviceTimelineSemaphoreFeatures  physicalDeviceTimelineSemaphoreFeatures{};
	physicalDeviceTimelineSemaphoreFeatures.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_TIMELINE_SEMAPHORE_FEATURES;
	physicalDeviceTimelineSemaphoreFeatures.pNext = nullptr;
	physicalDeviceTimelineSemaphoreFeatures.timelineSemaphore = VK_FALSE;//指明是否可以创建VkSemaphoreType为VK_SEMAPHORE_TYPE_TIMELINE的semaphore


	//VkPhysicalDeviceExternalMemoryScreenBufferFeaturesQNX ，可以包含在VkPhysicalDeviceFeatures2.pNext中 
	VkPhysicalDeviceExternalMemoryScreenBufferFeaturesQNX  physicalDeviceExternalMemoryScreenBufferFeaturesQNX{};
	physicalDeviceExternalMemoryScreenBufferFeaturesQNX.sType = VK_STRUCTURE_TYPE_MAX_ENUM;//没有定义这里定义为非法值
	physicalDeviceExternalMemoryScreenBufferFeaturesQNX.pNext = nullptr;
	physicalDeviceExternalMemoryScreenBufferFeaturesQNX.screenBufferImport = VK_FALSE;//指明是否支持 QNX Screen buffer 导入功能，如果支持，则VkDeviceMemory就支持导入_screen_buffer


	//VkPhysicalDeviceIndexTypeUint8FeaturesKHR ，等价于 VkPhysicalDeviceIndexTypeUint8FeaturesEXT，可以包含在VkPhysicalDeviceFeatures2.pNext中 
	VkPhysicalDeviceIndexTypeUint8FeaturesKHR  physicalDeviceIndexTypeUint8FeaturesKHR{};
	physicalDeviceIndexTypeUint8FeaturesKHR.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_INDEX_TYPE_UINT8_FEATURES_EXT;
	physicalDeviceIndexTypeUint8FeaturesKHR.pNext = nullptr;
	physicalDeviceIndexTypeUint8FeaturesKHR.indexTypeUint8 = VK_FALSE;//指明vkCmdBindIndexBuffer2KHR 以及 vkCmdBindIndexBuffer命令是否可以使用VK_INDEX_TYPE_UINT8_KHR


	//VkPhysicalDevicePrimitiveTopologyListRestartFeaturesEXT ，可以包含在VkPhysicalDeviceFeatures2.pNext中 
	VkPhysicalDevicePrimitiveTopologyListRestartFeaturesEXT  physicalDevicePrimitiveTopologyListRestartFeaturesEXT{};
	physicalDevicePrimitiveTopologyListRestartFeaturesEXT.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PRIMITIVE_TOPOLOGY_LIST_RESTART_FEATURES_EXT;
	physicalDevicePrimitiveTopologyListRestartFeaturesEXT.pNext = nullptr;
	physicalDevicePrimitiveTopologyListRestartFeaturesEXT.primitiveTopologyListRestart = VK_FALSE;//指明列表类型的图元: VK_PRIMITIVE_TOPOLOGY_POINT_LIST, VK_PRIMITIVE_TOPOLOGY_LINE_LIST, VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST, VK_PRIMITIVE_TOPOLOGY_LINE_LIST_WITH_ADJACENCY 以及 VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST_WITH_ADJACENCY, 是否可以使用index buffer中的restart index
	physicalDevicePrimitiveTopologyListRestartFeaturesEXT.primitiveTopologyPatchListRestart = VK_FALSE;//指明VK_PRIMITIVE_TOPOLOGY_PATCH_LIST 类型的图元是否可以使用index buffer中的restart index


	//VkPhysicalDeviceShaderSMBuiltinsFeaturesNV ，可以包含在VkPhysicalDeviceFeatures2.pNext中 
	VkPhysicalDeviceShaderSMBuiltinsFeaturesNV  physicalDeviceShaderSMBuiltinsFeaturesNV{};
	physicalDeviceShaderSMBuiltinsFeaturesNV.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_SM_BUILTINS_FEATURES_NV;
	physicalDeviceShaderSMBuiltinsFeaturesNV.pNext = nullptr;
	physicalDeviceShaderSMBuiltinsFeaturesNV.shaderSMBuiltins = VK_FALSE;//指明是否支持  ShaderSMBuiltinsNV SPIR-V 能力


	//VkPhysicalDeviceSeparateDepthStencilLayoutsFeatures ，等价于 VkPhysicalDeviceSeparateDepthStencilLayoutsFeaturesKHR ，可以包含在VkPhysicalDeviceFeatures2.pNext中 
	VkPhysicalDeviceSeparateDepthStencilLayoutsFeatures  physicalDeviceSeparateDepthStencilLayoutsFeatures{};
	physicalDeviceSeparateDepthStencilLayoutsFeatures.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SEPARATE_DEPTH_STENCIL_LAYOUTS_FEATURES;
	physicalDeviceSeparateDepthStencilLayoutsFeatures.pNext = nullptr;
	physicalDeviceSeparateDepthStencilLayoutsFeatures.separateDepthStencilLayouts = VK_FALSE;//指明是否支持对只设置了VK_IMAGE_ASPECT_DEPTH_BIT 或者 VK_IMAGE_ASPECT_STENCIL_BIT 的depth/stencil image使用VkImageMemoryBarrier，且是否VK_IMAGE_LAYOUT_DEPTH_ATTACHMENT_OPTIMAL, VK_IMAGE_LAYOUT_DEPTH_READ_ONLY_OPTIMAL, VK_IMAGE_LAYOUT_STENCIL_ATTACHMENT_OPTIMAL, 或者 VK_IMAGE_LAYOUT_STENCIL_READ_ONLY_OPTIMAL可以使用


	//VkPhysicalDevicePipelineExecutablePropertiesFeaturesKHR ，可以包含在VkPhysicalDeviceFeatures2.pNext中 
	VkPhysicalDevicePipelineExecutablePropertiesFeaturesKHR  physicalDevicePipelineExecutablePropertiesFeaturesKHR{};
	physicalDevicePipelineExecutablePropertiesFeaturesKHR.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PIPELINE_EXECUTABLE_PROPERTIES_FEATURES_KHR;
	physicalDevicePipelineExecutablePropertiesFeaturesKHR.pNext = nullptr;
	physicalDevicePipelineExecutablePropertiesFeaturesKHR.pipelineExecutableInfo = VK_FALSE;//表示实现支持报告与编译管道关联的管道可执行文件的属性和统计信息


	//VkPhysicalDeviceShaderDemoteToHelperInvocationFeatures ，等价于 VkPhysicalDeviceShaderDemoteToHelperInvocationFeaturesEXT ，可以包含在VkPhysicalDeviceFeatures2.pNext中 
	VkPhysicalDeviceShaderDemoteToHelperInvocationFeatures  physicalDeviceShaderDemoteToHelperInvocationFeatures{};
	physicalDeviceShaderDemoteToHelperInvocationFeatures.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_DEMOTE_TO_HELPER_INVOCATION_FEATURES;
	physicalDeviceShaderDemoteToHelperInvocationFeatures.pNext = nullptr;
	physicalDeviceShaderDemoteToHelperInvocationFeatures.shaderDemoteToHelperInvocation = VK_FALSE;//指明是否支持SPIR-V DemoteToHelperInvocationEXT 能力


	//VkPhysicalDeviceTexelBufferAlignmentFeaturesEXT ，可以包含在VkPhysicalDeviceFeatures2.pNext中 
	VkPhysicalDeviceTexelBufferAlignmentFeaturesEXT  physicalDeviceTexelBufferAlignmentFeaturesEXT{};
	physicalDeviceTexelBufferAlignmentFeaturesEXT.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_TEXEL_BUFFER_ALIGNMENT_FEATURES_EXT;
	physicalDeviceTexelBufferAlignmentFeaturesEXT.pNext = nullptr;
	physicalDeviceTexelBufferAlignmentFeaturesEXT.texelBufferAlignment = VK_FALSE;//表示是否可以使用 VkPhysicalDeviceTexelBufferAlignmentProperties中建议的更精细的对齐属性而不是VkPhysicalDeviceLimits::minTexelBufferOffsetAlignment


	//VkPhysicalDeviceAttachmentFeedbackLoopDynamicStateFeaturesEXT ，可以包含在VkPhysicalDeviceFeatures2.pNext中 
	VkPhysicalDeviceAttachmentFeedbackLoopDynamicStateFeaturesEXT  physicalDeviceAttachmentFeedbackLoopDynamicStateFeaturesEXT{};
	physicalDeviceAttachmentFeedbackLoopDynamicStateFeaturesEXT.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_ATTACHMENT_FEEDBACK_LOOP_DYNAMIC_STATE_FEATURES_EXT;
	physicalDeviceAttachmentFeedbackLoopDynamicStateFeaturesEXT.pNext = nullptr;
	physicalDeviceAttachmentFeedbackLoopDynamicStateFeaturesEXT.attachmentFeedbackLoopDynamicState = VK_FALSE;//表示是否支持 dynamic feedback loops


	//VkPhysicalDeviceLegacyVertexAttributesFeaturesEXT ，可以包含在VkPhysicalDeviceFeatures2.pNext中 
	VkPhysicalDeviceLegacyVertexAttributesFeaturesEXT  physicalDeviceLegacyVertexAttributesFeaturesEXT{};
	physicalDeviceLegacyVertexAttributesFeaturesEXT.sType = VK_STRUCTURE_TYPE_MAX_ENUM;//没有定义这里设置为非法值
	physicalDeviceLegacyVertexAttributesFeaturesEXT.pNext = nullptr;
	physicalDeviceLegacyVertexAttributesFeaturesEXT.legacyVertexAttributes = VK_FALSE;//指明使用 dynamic vertex input state的是否是否支持顶点属性的兼容性特性


	//VkPhysicalDeviceTextureCompressionASTCHDRFeatures ，等价于VkPhysicalDeviceTextureCompressionASTCHDRFeaturesEXT ，可以包含在VkPhysicalDeviceFeatures2.pNext中 
	VkPhysicalDeviceTextureCompressionASTCHDRFeatures  physicalDeviceTextureCompressionASTCHDRFeatures{};
	physicalDeviceTextureCompressionASTCHDRFeatures.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_TEXTURE_COMPRESSION_ASTC_HDR_FEATURES;
	physicalDeviceTextureCompressionASTCHDRFeatures.pNext = nullptr;
	physicalDeviceTextureCompressionASTCHDRFeatures.textureCompressionASTC_HDR = VK_FALSE;//指明是否支持所有的ASTC HDR 压缩纹理格式，如果支持，则如VK_FORMAT_ASTC_*** 的optimalTilingFeatures 必须包含VK_FORMAT_FEATURE_SAMPLED_IMAGE_BIT, VK_FORMAT_FEATURE_BLIT_SRC_BIT 以及 VK_FORMAT_FEATURE_SAMPLED_IMAGE_FILTER_LINEAR_BIT
	
	
	//VkPhysicalDeviceLineRasterizationFeaturesKHR ，等价于VkPhysicalDeviceLineRasterizationFeaturesEXT ，可以包含在VkPhysicalDeviceFeatures2.pNext中 
	VkPhysicalDeviceLineRasterizationFeaturesKHR  physicalDeviceLineRasterizationFeaturesKHR{};
	physicalDeviceLineRasterizationFeaturesKHR.sType = VK_STRUCTURE_TYPE_MAX_ENUM;//没有定义这里设置为非法值
	physicalDeviceLineRasterizationFeaturesKHR.pNext = nullptr;
	physicalDeviceLineRasterizationFeaturesKHR.rectangularLines = VK_FALSE;//指明是否支持 rectangular line rasterization 
	physicalDeviceLineRasterizationFeaturesKHR.bresenhamLines = VK_FALSE;//指明是否支持 Bresenham-style line rasterization 
	physicalDeviceLineRasterizationFeaturesKHR.smoothLines = VK_FALSE;//指明是否支持  smooth line rasterization 
	physicalDeviceLineRasterizationFeaturesKHR.stippledRectangularLines = VK_FALSE;//指明是否支持VK_LINE_RASTERIZATION_MODE_RECTANGULAR_KHR line的 stippled line rasterization 
	physicalDeviceLineRasterizationFeaturesKHR.stippledBresenhamLines = VK_FALSE;//指明是否支持VK_LINE_RASTERIZATION_MODE_BRESENHAM_KHR line的 stippled line rasterization 
	physicalDeviceLineRasterizationFeaturesKHR.stippledSmoothLines = VK_FALSE;//指明是否支持VK_LINE_RASTERIZATION_MODE_RECTANGULAR_SMOOTH_KHR line的 stippled line rasterization 


	//VkPhysicalDeviceSubgroupSizeControlFeatures ，等价于VkPhysicalDeviceSubgroupSizeControlFeaturesEXT ，可以包含在VkPhysicalDeviceFeatures2.pNext中 
	VkPhysicalDeviceSubgroupSizeControlFeatures  physicalDeviceSubgroupSizeControlFeatures{};
	physicalDeviceSubgroupSizeControlFeatures.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SUBGROUP_SIZE_CONTROL_FEATURES;
	physicalDeviceSubgroupSizeControlFeatures.pNext = nullptr;
	physicalDeviceSubgroupSizeControlFeatures.subgroupSizeControl = VK_FALSE;//指明是否可以通过VK_PIPELINE_SHADER_STAGE_CREATE_ALLOW_VARYING_SUBGROUP_SIZE_BIT 以及  VkPipelineShaderStageRequiredSubgroupSizeCreateInfo 来指定subgroup size
	physicalDeviceSubgroupSizeControlFeatures.computeFullSubgroups = VK_FALSE;//指明compute , mesh, 或者 task shaders是否可以通过VK_PIPELINE_SHADER_STAGE_CREATE_REQUIRE_FULL_SUBGROUPS_BIT 来要求使用完整的subgroup


	//VkPhysicalDeviceCoherentMemoryFeaturesAMD ，可以包含在VkPhysicalDeviceFeatures2.pNext中 
	VkPhysicalDeviceCoherentMemoryFeaturesAMD  physicalDeviceCoherentMemoryFeaturesAMD{};
	physicalDeviceCoherentMemoryFeaturesAMD.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_COHERENT_MEMORY_FEATURES_AMD;
	physicalDeviceCoherentMemoryFeaturesAMD.pNext = nullptr;
	physicalDeviceCoherentMemoryFeaturesAMD.deviceCoherentMemory = VK_FALSE;//指明是否可以支持 device coherent memory


	//VkPhysicalDeviceAccelerationStructureFeaturesKHR  ，可以包含在VkPhysicalDeviceFeatures2.pNext中 
	VkPhysicalDeviceAccelerationStructureFeaturesKHR  physicalDeviceAccelerationStructureFeaturesKHR{};
	physicalDeviceAccelerationStructureFeaturesKHR.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_ACCELERATION_STRUCTURE_FEATURES_KHR;
	physicalDeviceAccelerationStructureFeaturesKHR.pNext = nullptr;
	physicalDeviceAccelerationStructureFeaturesKHR.accelerationStructure = VK_FALSE;//指明是否支持acceleration structure 功能
	physicalDeviceAccelerationStructureFeaturesKHR.accelerationStructureCaptureReplay = VK_FALSE;//指明是否支持保存和重用acceleration structure 的device地址
	physicalDeviceAccelerationStructureFeaturesKHR.accelerationStructureIndirectBuild = VK_FALSE;//指明是否支持如 vkCmdBuildAccelerationStructuresIndirectKHR的间接acceleration structure 构建命令
	physicalDeviceAccelerationStructureFeaturesKHR.accelerationStructureHostCommands = VK_FALSE;//指明是否支持host端的acceleration structure 命令如:vkBuildAccelerationStructuresKHR, vkCopyAccelerationStructureKHR, vkCopyAccelerationStructureToMemoryKHR, vkCopyMemoryToAccelerationStructureKHR, vkWriteAccelerationStructuresPropertiesKHR.
	physicalDeviceAccelerationStructureFeaturesKHR.descriptorBindingAccelerationStructureUpdateAfterBind = VK_FALSE;//指明是否支持在绑定descriptor set后更新acceleration structure descriptors，如果不支持，则VK_DESCRIPTOR_BINDING_UPDATE_AFTER_BIND_BIT 不能和VK_DESCRIPTOR_TYPE_ACCELERATION_STRUCTURE_KHR 一起使用


	//VkPhysicalDeviceRayTracingPipelineFeaturesKHR  ，可以包含在VkPhysicalDeviceFeatures2.pNext中 
	VkPhysicalDeviceRayTracingPipelineFeaturesKHR  physicalDeviceRayTracingPipelineFeaturesKHR{};
	physicalDeviceRayTracingPipelineFeaturesKHR.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_RAY_TRACING_PIPELINE_FEATURES_KHR;
	physicalDeviceRayTracingPipelineFeaturesKHR.pNext = nullptr;
	physicalDeviceRayTracingPipelineFeaturesKHR.rayTracingPipeline = VK_FALSE;//指明是否支持ray tracing pipeline 功能
	physicalDeviceRayTracingPipelineFeaturesKHR.rayTracingPipelineShaderGroupHandleCaptureReplay = VK_FALSE;//指明是否支持保存和重用 shader group 句柄
	physicalDeviceRayTracingPipelineFeaturesKHR.rayTracingPipelineShaderGroupHandleCaptureReplayMixed = VK_FALSE;//指明是否支持重用的 shader group 句柄和非重用的 shader group 句柄任意混合使用，如果不支持则重用的 shader group 句柄必须在可能创建的非重用 shader group 句柄前指定，如果支持则rayTracingPipelineShaderGroupHandleCaptureReplay 也必须支持为VK_TRUE
	physicalDeviceRayTracingPipelineFeaturesKHR.rayTracingPipelineTraceRaysIndirect = VK_FALSE;//指明是否支持如 vkCmdTraceRaysIndirectKHR 的间接ray tracing 命令
	physicalDeviceRayTracingPipelineFeaturesKHR.rayTraversalPrimitiveCulling = VK_FALSE;//指明是否支持在 ray traversal过程中进行 primitive culling 


	//VkPhysicalDeviceRayQueryFeaturesKHR  ，可以包含在VkPhysicalDeviceFeatures2.pNext中 
	VkPhysicalDeviceRayQueryFeaturesKHR  physicalDeviceRayQueryFeaturesKHR{};
	physicalDeviceRayQueryFeaturesKHR.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_RAY_QUERY_FEATURES_KHR;
	physicalDeviceRayQueryFeaturesKHR.pNext = nullptr;
	physicalDeviceRayQueryFeaturesKHR.rayQuery = VK_FALSE;//指明是否支持ray query (OpRayQueryProceedKHR) 功能


	//VkPhysicalDeviceRayTracingMaintenance1FeaturesKHR  ，可以包含在VkPhysicalDeviceFeatures2.pNext中 
	VkPhysicalDeviceRayTracingMaintenance1FeaturesKHR  physicalDeviceRayTracingMaintenance1FeaturesKHR{};
	physicalDeviceRayTracingMaintenance1FeaturesKHR.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_RAY_TRACING_MAINTENANCE_1_FEATURES_KHR;
	physicalDeviceRayTracingMaintenance1FeaturesKHR.pNext = nullptr;
	physicalDeviceRayTracingMaintenance1FeaturesKHR.rayTracingMaintenance1 = VK_FALSE;//指明是否支持：1. CullMaskKHR SPIR-V 内嵌变量使用 SPV_KHR_ray_cull_mask SPIR-V 拓展；2.额外加速结构的属性查询VK_QUERY_TYPE_ACCELERATION_STRUCTURE_SERIALIZATION_BOTTOM_LEVEL_POINTERS_KHR 以及 VK_QUERY_TYPE_ACCELERATION_STRUCTURE_SIZE_KHR；3.新的访问标志 VK_ACCESS_2_SHADER_BINDING_TABLE_READ_BIT_KHR；4.新的pipeline stage标志 VK_PIPELINE_STAGE_2_ACCELERATION_STRUCTURE_COPY_BIT_KHR
	physicalDeviceRayTracingMaintenance1FeaturesKHR.rayTracingPipelineTraceRaysIndirect2 = VK_FALSE;//指明是否支持扩展的如 vkCmdTraceRaysIndirect2KHR 的间接ray tracing 命令


	//VkPhysicalDeviceVideoMaintenance1FeaturesKHR  ，可以包含在VkPhysicalDeviceFeatures2.pNext中 
	VkPhysicalDeviceVideoMaintenance1FeaturesKHR  physicalDeviceVideoMaintenance1FeaturesKHR{};
	physicalDeviceVideoMaintenance1FeaturesKHR.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_RAY_TRACING_MAINTENANCE_1_FEATURES_KHR;
	physicalDeviceVideoMaintenance1FeaturesKHR.pNext = nullptr;
	physicalDeviceVideoMaintenance1FeaturesKHR.videoMaintenance1 = VK_FALSE;//指明是否支持:1.新的buffer 创建标志VK_BUFFER_CREATE_VIDEO_PROFILE_INDEPENDENT_BIT_KHR；2.新的image创建标志 VK_IMAGE_CREATE_VIDEO_PROFILE_INDEPENDENT_BIT_KHR；3.新的video session创建标志 VK_VIDEO_SESSION_CREATE_INLINE_QUERIES_BIT_KHR


	//VkPhysicalDeviceExtendedDynamicStateFeaturesEXT  ，可以包含在VkPhysicalDeviceFeatures2.pNext中 
	VkPhysicalDeviceExtendedDynamicStateFeaturesEXT  physicalDeviceExtendedDynamicStateFeaturesEXT{};
	physicalDeviceExtendedDynamicStateFeaturesEXT.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_EXTENDED_DYNAMIC_STATE_FEATURES_EXT;
	physicalDeviceExtendedDynamicStateFeaturesEXT.pNext = nullptr;
	physicalDeviceExtendedDynamicStateFeaturesEXT.extendedDynamicState = VK_FALSE;/*
		指明是否支持如下动态states:
		> VK_DYNAMIC_STATE_CULL_MODE
		> VK_DYNAMIC_STATE_FRONT_FACE
		> VK_DYNAMIC_STATE_PRIMITIVE_TOPOLOGY
		> VK_DYNAMIC_STATE_VIEWPORT_WITH_COUNT
		> VK_DYNAMIC_STATE_SCISSOR_WITH_COUNT
		> VK_DYNAMIC_STATE_VERTEX_INPUT_BINDING_STRIDE
		> VK_DYNAMIC_STATE_DEPTH_TEST_ENABLE
		> VK_DYNAMIC_STATE_DEPTH_WRITE_ENABLE
		> VK_DYNAMIC_STATE_DEPTH_COMPARE_OP
		> VK_DYNAMIC_STATE_DEPTH_BOUNDS_TEST_ENABLE
		> VK_DYNAMIC_STATE_STENCIL_TEST_ENABLE
		> VK_DYNAMIC_STATE_STENCIL_OP
		*/


	//VkPhysicalDeviceExtendedDynamicState2FeaturesEXT  ，可以包含在VkPhysicalDeviceFeatures2.pNext中 
	VkPhysicalDeviceExtendedDynamicState2FeaturesEXT  physicalDeviceExtendedDynamicState2FeaturesEXT{};
	physicalDeviceExtendedDynamicState2FeaturesEXT.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_EXTENDED_DYNAMIC_STATE_2_FEATURES_EXT;
	physicalDeviceExtendedDynamicState2FeaturesEXT.pNext = nullptr;
	physicalDeviceExtendedDynamicState2FeaturesEXT.extendedDynamicState2 = VK_FALSE;//指明是否支持动态states: VK_DYNAMIC_STATE_DEPTH_BIAS_ENABLE,  VK_DYNAMIC_STATE_PRIMITIVE_RESTART_ENABLE , VK_DYNAMIC_STATE_RASTERIZER_DISCARD_ENABLE
	physicalDeviceExtendedDynamicState2FeaturesEXT.extendedDynamicState2LogicOp = VK_FALSE;//指明是否支持动态state: VK_DYNAMIC_STATE_LOGIC_OP_EXT
	physicalDeviceExtendedDynamicState2FeaturesEXT.extendedDynamicState2PatchControlPoints = VK_FALSE;//指明是否支持动态state: K_DYNAMIC_STATE_PATCH_CONTROL_POINTS_EXT


	//VkPhysicalDeviceExtendedDynamicState3FeaturesEXT  ，可以包含在VkPhysicalDeviceFeatures2.pNext中 
	VkPhysicalDeviceExtendedDynamicState3FeaturesEXT  physicalDeviceExtendedDynamicState3FeaturesEXT{};
	physicalDeviceExtendedDynamicState3FeaturesEXT.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_EXTENDED_DYNAMIC_STATE_3_FEATURES_EXT;
	physicalDeviceExtendedDynamicState3FeaturesEXT.pNext = nullptr;
	physicalDeviceExtendedDynamicState3FeaturesEXT.extendedDynamicState3TessellationDomainOrigin = VK_FALSE;
	physicalDeviceExtendedDynamicState3FeaturesEXT.extendedDynamicState3DepthClampEnable = VK_FALSE;
	physicalDeviceExtendedDynamicState3FeaturesEXT.extendedDynamicState3PolygonMode = VK_FALSE;
	physicalDeviceExtendedDynamicState3FeaturesEXT.extendedDynamicState3RasterizationSamples = VK_FALSE;
	physicalDeviceExtendedDynamicState3FeaturesEXT.extendedDynamicState3SampleMask = VK_FALSE;
	physicalDeviceExtendedDynamicState3FeaturesEXT.extendedDynamicState3AlphaToCoverageEnable = VK_FALSE;
	physicalDeviceExtendedDynamicState3FeaturesEXT.extendedDynamicState3AlphaToOneEnable = VK_FALSE;
	physicalDeviceExtendedDynamicState3FeaturesEXT.extendedDynamicState3LogicOpEnable = VK_FALSE;
	physicalDeviceExtendedDynamicState3FeaturesEXT.extendedDynamicState3ColorBlendEnable = VK_FALSE;
	physicalDeviceExtendedDynamicState3FeaturesEXT.extendedDynamicState3ColorBlendEquation = VK_FALSE;
	physicalDeviceExtendedDynamicState3FeaturesEXT.extendedDynamicState3ColorWriteMask = VK_FALSE;
	physicalDeviceExtendedDynamicState3FeaturesEXT.extendedDynamicState3RasterizationStream = VK_FALSE;
	physicalDeviceExtendedDynamicState3FeaturesEXT.extendedDynamicState3ConservativeRasterizationMode = VK_FALSE;
	physicalDeviceExtendedDynamicState3FeaturesEXT.extendedDynamicState3ExtraPrimitiveOverestimationSize = VK_FALSE;
	physicalDeviceExtendedDynamicState3FeaturesEXT.extendedDynamicState3DepthClipEnable = VK_FALSE;
	physicalDeviceExtendedDynamicState3FeaturesEXT.extendedDynamicState3SampleLocationsEnable = VK_FALSE;
	physicalDeviceExtendedDynamicState3FeaturesEXT.extendedDynamicState3ColorBlendAdvanced = VK_FALSE;
	physicalDeviceExtendedDynamicState3FeaturesEXT.extendedDynamicState3ProvokingVertexMode = VK_FALSE;
	physicalDeviceExtendedDynamicState3FeaturesEXT.extendedDynamicState3LineRasterizationMode = VK_FALSE;
	physicalDeviceExtendedDynamicState3FeaturesEXT.extendedDynamicState3LineStippleEnable = VK_FALSE;
	physicalDeviceExtendedDynamicState3FeaturesEXT.extendedDynamicState3DepthClipNegativeOneToOne = VK_FALSE;
	physicalDeviceExtendedDynamicState3FeaturesEXT.extendedDynamicState3ViewportWScalingEnable = VK_FALSE;
	physicalDeviceExtendedDynamicState3FeaturesEXT.extendedDynamicState3ViewportSwizzle = VK_FALSE;
	physicalDeviceExtendedDynamicState3FeaturesEXT.extendedDynamicState3CoverageToColorEnable = VK_FALSE;
	physicalDeviceExtendedDynamicState3FeaturesEXT.extendedDynamicState3CoverageToColorLocation = VK_FALSE;
	physicalDeviceExtendedDynamicState3FeaturesEXT.extendedDynamicState3CoverageModulationMode = VK_FALSE;
	physicalDeviceExtendedDynamicState3FeaturesEXT.extendedDynamicState3CoverageModulationTableEnable = VK_FALSE;
	physicalDeviceExtendedDynamicState3FeaturesEXT.extendedDynamicState3CoverageModulationTable = VK_FALSE;
	physicalDeviceExtendedDynamicState3FeaturesEXT.extendedDynamicState3CoverageReductionMode = VK_FALSE;
	physicalDeviceExtendedDynamicState3FeaturesEXT.extendedDynamicState3RepresentativeFragmentTestEnable = VK_FALSE;
	physicalDeviceExtendedDynamicState3FeaturesEXT.extendedDynamicState3ShadingRateImageEnable = VK_FALSE;














}












NS_TEST_END