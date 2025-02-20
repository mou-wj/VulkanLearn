#include "ExtendingVulkanAndFeaturesTest.h"
#include "vulkan/vulkan_beta.h"

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
	physicalDeviceExtendedDynamicState3FeaturesEXT.extendedDynamicState3TessellationDomainOrigin = VK_FALSE;//指明支持动态state: VK_DYNAMIC_STATE_TESSELLATION_DOMAIN_ORIGIN_KHR
	physicalDeviceExtendedDynamicState3FeaturesEXT.extendedDynamicState3DepthClampEnable = VK_FALSE;//指明支持动态state: VK_DYNAMIC_STATE_DEPTH_CLAMP_ENABLE_EXT
	physicalDeviceExtendedDynamicState3FeaturesEXT.extendedDynamicState3PolygonMode = VK_FALSE;//指明支持动态state: VK_DYNAMIC_STATE_POLYGON_MODE_EXT
	physicalDeviceExtendedDynamicState3FeaturesEXT.extendedDynamicState3RasterizationSamples = VK_FALSE;//指明支持动态state: VK_DYNAMIC_STATE_RASTERIZATION_SAMPLES_EXT
	physicalDeviceExtendedDynamicState3FeaturesEXT.extendedDynamicState3SampleMask = VK_FALSE;//指明支持动态state: VK_DYNAMIC_STATE_SAMPLE_MASK_EXT
	physicalDeviceExtendedDynamicState3FeaturesEXT.extendedDynamicState3AlphaToCoverageEnable = VK_FALSE;//指明支持动态state: VK_DYNAMIC_STATE_ALPHA_TO_COVERAGE_ENABLE_EXT
	physicalDeviceExtendedDynamicState3FeaturesEXT.extendedDynamicState3AlphaToOneEnable = VK_FALSE;//指明支持动态state: VK_DYNAMIC_STATE_ALPHA_TO_ONE_ENABLE_EXT
	physicalDeviceExtendedDynamicState3FeaturesEXT.extendedDynamicState3LogicOpEnable = VK_FALSE;//指明支持动态state: VK_DYNAMIC_STATE_LOGIC_OP_ENABLE_EXT
	physicalDeviceExtendedDynamicState3FeaturesEXT.extendedDynamicState3ColorBlendEnable = VK_FALSE;//指明支持动态state: VK_DYNAMIC_STATE_COLOR_BLEND_ENABLE_EXT
	physicalDeviceExtendedDynamicState3FeaturesEXT.extendedDynamicState3ColorBlendEquation = VK_FALSE;//指明支持动态state: VK_DYNAMIC_STATE_COLOR_BLEND_EQUATION_EXT
	physicalDeviceExtendedDynamicState3FeaturesEXT.extendedDynamicState3ColorWriteMask = VK_FALSE;//指明支持动态state: VK_DYNAMIC_STATE_COLOR_WRITE_MASK_EXT
	physicalDeviceExtendedDynamicState3FeaturesEXT.extendedDynamicState3RasterizationStream = VK_FALSE;//指明支持动态state: VK_DYNAMIC_STATE_RASTERIZATION_STREAM_EXT
	physicalDeviceExtendedDynamicState3FeaturesEXT.extendedDynamicState3ConservativeRasterizationMode = VK_FALSE;//指明支持动态state: VK_DYNAMIC_STATE_CONSERVATIVE_RASTERIZATION_MODE_EXT
	physicalDeviceExtendedDynamicState3FeaturesEXT.extendedDynamicState3ExtraPrimitiveOverestimationSize = VK_FALSE;//指明支持动态state: VK_DYNAMIC_STATE_EXTRA_PRIMITIVE_OVERESTIMATION_SIZE_EXT
	physicalDeviceExtendedDynamicState3FeaturesEXT.extendedDynamicState3DepthClipEnable = VK_FALSE;//指明支持动态state: VK_DYNAMIC_STATE_DEPTH_CLIP_ENABLE_EXT
	physicalDeviceExtendedDynamicState3FeaturesEXT.extendedDynamicState3SampleLocationsEnable = VK_FALSE;//指明支持动态state: VK_DYNAMIC_STATE_SAMPLE_LOCATIONS_ENABLE_EXT
	physicalDeviceExtendedDynamicState3FeaturesEXT.extendedDynamicState3ColorBlendAdvanced = VK_FALSE;//指明支持动态state: VK_DYNAMIC_STATE_COLOR_BLEND_ADVANCED_EXT
	physicalDeviceExtendedDynamicState3FeaturesEXT.extendedDynamicState3ProvokingVertexMode = VK_FALSE;//指明支持动态state: VK_DYNAMIC_STATE_PROVOKING_VERTEX_MODE_EXT
	physicalDeviceExtendedDynamicState3FeaturesEXT.extendedDynamicState3LineRasterizationMode = VK_FALSE;//指明支持动态state: VK_DYNAMIC_STATE_LINE_RASTERIZATION_MODE_EXT
	physicalDeviceExtendedDynamicState3FeaturesEXT.extendedDynamicState3LineStippleEnable = VK_FALSE;//指明支持动态state: VK_DYNAMIC_STATE_LINE_STIPPLE_ENABLE_EXT
	physicalDeviceExtendedDynamicState3FeaturesEXT.extendedDynamicState3DepthClipNegativeOneToOne = VK_FALSE;//指明支持动态state: VK_DYNAMIC_STATE_DEPTH_CLIP_NEGATIVE_ONE_TO_ONE_EXT
	physicalDeviceExtendedDynamicState3FeaturesEXT.extendedDynamicState3ViewportWScalingEnable = VK_FALSE;//指明支持动态state: VK_DYNAMIC_STATE_VIEWPORT_W_SCALING_ENABLE_NV
	physicalDeviceExtendedDynamicState3FeaturesEXT.extendedDynamicState3ViewportSwizzle = VK_FALSE;//指明支持动态state: VK_DYNAMIC_STATE_VIEWPORT_SWIZZLE_NV
	physicalDeviceExtendedDynamicState3FeaturesEXT.extendedDynamicState3CoverageToColorEnable = VK_FALSE;//指明支持动态state: VK_DYNAMIC_STATE_COVERAGE_TO_COLOR_ENABLE_NV
	physicalDeviceExtendedDynamicState3FeaturesEXT.extendedDynamicState3CoverageToColorLocation = VK_FALSE;//指明支持动态state: VK_DYNAMIC_STATE_COVERAGE_TO_COLOR_LOCATION_NV
	physicalDeviceExtendedDynamicState3FeaturesEXT.extendedDynamicState3CoverageModulationMode = VK_FALSE;//指明支持动态state: VK_DYNAMIC_STATE_COVERAGE_MODULATION_MODE_NV
	physicalDeviceExtendedDynamicState3FeaturesEXT.extendedDynamicState3CoverageModulationTableEnable = VK_FALSE;//指明支持动态state: VK_DYNAMIC_STATE_COVERAGE_MODULATION_TABLE_ENABLE_NV
	physicalDeviceExtendedDynamicState3FeaturesEXT.extendedDynamicState3CoverageModulationTable = VK_FALSE;//指明支持动态state: VK_DYNAMIC_STATE_COVERAGE_MODULATION_TABLE_NV
	physicalDeviceExtendedDynamicState3FeaturesEXT.extendedDynamicState3CoverageReductionMode = VK_FALSE;//指明支持动态state: VK_DYNAMIC_STATE_COVERAGE_REDUCTION_MODE_NV
	physicalDeviceExtendedDynamicState3FeaturesEXT.extendedDynamicState3RepresentativeFragmentTestEnable = VK_FALSE;//指明支持动态state: VK_DYNAMIC_STATE_REPRESENTATIVE_FRAGMENT_TEST_ENABLE_NV
	physicalDeviceExtendedDynamicState3FeaturesEXT.extendedDynamicState3ShadingRateImageEnable = VK_FALSE;//指明支持动态state: VK_DYNAMIC_STATE_SHADING_RATE_IMAGE_ENABLE_NV


	//VkPhysicalDeviceDeviceGeneratedCommandsFeaturesNV  ，可以包含在VkPhysicalDeviceFeatures2.pNext中 
	VkPhysicalDeviceDeviceGeneratedCommandsFeaturesNV  physicalDeviceDeviceGeneratedCommandsFeaturesNV{};
	physicalDeviceDeviceGeneratedCommandsFeaturesNV.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DEVICE_GENERATED_COMMANDS_FEATURES_NV;
	physicalDeviceDeviceGeneratedCommandsFeaturesNV.pNext = nullptr;
	physicalDeviceDeviceGeneratedCommandsFeaturesNV.deviceGeneratedCommands = VK_FALSE;//指明是否支持在device上生成命令的功能。见 Device-Generated Commands p2905


	//VkPhysicalDeviceDeviceGeneratedCommandsComputeFeaturesNV  ，可以包含在VkPhysicalDeviceFeatures2.pNext中 
	VkPhysicalDeviceDeviceGeneratedCommandsComputeFeaturesNV  physicalDeviceDeviceGeneratedCommandsComputeFeaturesNV{};
	physicalDeviceDeviceGeneratedCommandsComputeFeaturesNV.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DEVICE_GENERATED_COMMANDS_FEATURES_NV;
	physicalDeviceDeviceGeneratedCommandsComputeFeaturesNV.pNext = nullptr;
	physicalDeviceDeviceGeneratedCommandsComputeFeaturesNV.deviceGeneratedCompute = VK_FALSE;//指明是否支持在device上生成用于compute pipeline的dispatch命令 以及push constants的功能。见 Device-Generated Commands p2905
	physicalDeviceDeviceGeneratedCommandsComputeFeaturesNV.deviceGeneratedComputePipelines = VK_FALSE;//指明是否支持在device上生成绑定compute pipeline 的命令的功能。见 Device-Generated Commands p2905
	physicalDeviceDeviceGeneratedCommandsComputeFeaturesNV.deviceGeneratedComputeCaptureReplay = VK_FALSE;//指明是否支持在捕获compute pipeline 地址用于后续回放的功能。见 Device-Generated Commands p2905


	//VkPhysicalDeviceDiagnosticsConfigFeaturesNV  ，可以包含在VkPhysicalDeviceFeatures2.pNext中 
	VkPhysicalDeviceDiagnosticsConfigFeaturesNV  physicalDeviceDiagnosticsConfigFeaturesNV{};
	physicalDeviceDiagnosticsConfigFeaturesNV.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DIAGNOSTICS_CONFIG_FEATURES_NV;
	physicalDeviceDiagnosticsConfigFeaturesNV.pNext = nullptr;
	physicalDeviceDiagnosticsConfigFeaturesNV.diagnosticsConfig = VK_FALSE;//指明是否支持configure diagnostic tools


	//VkPhysicalDeviceDeviceMemoryReportFeaturesEXT  ，可以包含在VkPhysicalDeviceFeatures2.pNext中 
	VkPhysicalDeviceDeviceMemoryReportFeaturesEXT  physicalDeviceDeviceMemoryReportFeaturesEXT{};
	physicalDeviceDeviceMemoryReportFeaturesEXT.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DEVICE_MEMORY_REPORT_FEATURES_EXT;
	physicalDeviceDeviceMemoryReportFeaturesEXT.pNext = nullptr;
	physicalDeviceDeviceMemoryReportFeaturesEXT.deviceMemoryReport = VK_FALSE;//指明是否支持注册device memory report callbacks


	//VkPhysicalDeviceGlobalPriorityQueryFeaturesKHR  ，等价于VkPhysicalDeviceGlobalPriorityQueryFeaturesEXT ，可以包含在VkPhysicalDeviceFeatures2.pNext中 
	VkPhysicalDeviceGlobalPriorityQueryFeaturesKHR  physicalDeviceGlobalPriorityQueryFeaturesKHR{};
	physicalDeviceGlobalPriorityQueryFeaturesKHR.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_GLOBAL_PRIORITY_QUERY_FEATURES_KHR;
	physicalDeviceGlobalPriorityQueryFeaturesKHR.pNext = nullptr;
	physicalDeviceGlobalPriorityQueryFeaturesKHR.globalPriorityQuery = VK_FALSE;//指明是否支持查询global queue priorities


	//VkPhysicalDevicePipelineCreationCacheControlFeatures  ，等价于VkPhysicalDevicePipelineCreationCacheControlFeaturesEXT ，可以包含在VkPhysicalDeviceFeatures2.pNext中 
	VkPhysicalDevicePipelineCreationCacheControlFeatures  physicalDevicePipelineCreationCacheControlFeatures{};
	physicalDevicePipelineCreationCacheControlFeatures.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PIPELINE_CREATION_CACHE_CONTROL_FEATURES;
	physicalDevicePipelineCreationCacheControlFeatures.pNext = nullptr;
	physicalDevicePipelineCreationCacheControlFeatures.pipelineCreationCacheControl = VK_FALSE;//指明是否支持:1. Vk*PipelineCreateInfo::flags 中使用VK_PIPELINE_CREATE_FAIL_ON_PIPELINE_COMPILE_REQUIRED_BIT ， VK_PIPELINE_CREATE_EARLY_RETURN_ON_FAILURE_BIT；2. VkPipelineCacheCreateInfo::flags 中使用VK_PIPELINE_CACHE_CREATE_EXTERNALLY_SYNCHRONIZED_BIT


	//VkPhysicalDeviceZeroInitializeWorkgroupMemoryFeatures  ，等价于VkPhysicalDeviceZeroInitializeWorkgroupMemoryFeaturesKHR ，可以包含在VkPhysicalDeviceFeatures2.pNext中 
	VkPhysicalDeviceZeroInitializeWorkgroupMemoryFeatures  physicalDeviceZeroInitializeWorkgroupMemoryFeatures{};
	physicalDeviceZeroInitializeWorkgroupMemoryFeatures.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_ZERO_INITIALIZE_WORKGROUP_MEMORY_FEATURES;
	physicalDeviceZeroInitializeWorkgroupMemoryFeatures.pNext = nullptr;
	physicalDeviceZeroInitializeWorkgroupMemoryFeatures.shaderZeroInitializeWorkgroupMemory = VK_FALSE;//指明是否支持初始化一个Workgroup storage class类型的变量


	//VkPhysicalDevicePrivateDataFeatures  ，等价于VkPhysicalDevicePrivateDataFeaturesEXT ，可以包含在VkPhysicalDeviceFeatures2.pNext中 
	VkPhysicalDevicePrivateDataFeatures  physicalDevicePrivateDataFeatures{};
	physicalDevicePrivateDataFeatures.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PRIVATE_DATA_FEATURES;
	physicalDevicePrivateDataFeatures.pNext = nullptr;
	physicalDevicePrivateDataFeatures.privateData = VK_FALSE;//指明是否支持 private data，见p3202


	//VkPhysicalDeviceShaderSubgroupUniformControlFlowFeaturesKHR  ,可以包含在VkPhysicalDeviceFeatures2.pNext中 
	VkPhysicalDeviceShaderSubgroupUniformControlFlowFeaturesKHR  physicalDeviceShaderSubgroupUniformControlFlowFeaturesKHR{};
	physicalDeviceShaderSubgroupUniformControlFlowFeaturesKHR.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_SUBGROUP_UNIFORM_CONTROL_FLOW_FEATURES_KHR;
	physicalDeviceShaderSubgroupUniformControlFlowFeaturesKHR.pNext = nullptr;
	physicalDeviceShaderSubgroupUniformControlFlowFeaturesKHR.shaderSubgroupUniformControlFlow = VK_FALSE;//指明是否支持shader execution mode SubgroupUniformControlFlowKHR


	//VkPhysicalDeviceRobustness2FeaturesEXT  ,可以包含在VkPhysicalDeviceFeatures2.pNext中 
	VkPhysicalDeviceRobustness2FeaturesEXT   physicalDeviceRobustness2FeaturesEXT{};
	physicalDeviceRobustness2FeaturesEXT.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_ROBUSTNESS_2_FEATURES_EXT;
	physicalDeviceRobustness2FeaturesEXT.pNext = nullptr;
	physicalDeviceRobustness2FeaturesEXT.robustBufferAccess2 = VK_FALSE;//指明buffer的访问是否会根据descriptor的范围进行边界检查，Uniform buffers 以及 Storage buffers 要进行边界检查，如果开启则 robustBufferAccess 必须开启，其他信息见p3829
	physicalDeviceRobustness2FeaturesEXT.robustImageAccess2 = VK_FALSE;//指明对image的访问会对image view的维度进行边界检查
	physicalDeviceRobustness2FeaturesEXT.nullDescriptor = VK_FALSE;//指明是否descriptor可以写入到VK_NULL_HANDLE的资源或者image view


	//VkPhysicalDeviceImageRobustnessFeatures ，等价于VkPhysicalDeviceImageRobustnessFeaturesEXT  ,可以包含在VkPhysicalDeviceFeatures2.pNext中 
	VkPhysicalDeviceImageRobustnessFeatures   physicalDeviceImageRobustnessFeatures{};
	physicalDeviceImageRobustnessFeatures.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_IMAGE_ROBUSTNESS_FEATURES;
	physicalDeviceImageRobustnessFeatures.pNext = nullptr;
	physicalDeviceImageRobustnessFeatures.robustImageAccess = VK_FALSE;//指明对image的访问会对image view的维度进行边界检查


	//VkPhysicalDeviceShaderTerminateInvocationFeatures ，等价于VkPhysicalDeviceShaderTerminateInvocationFeaturesKHR  ,可以包含在VkPhysicalDeviceFeatures2.pNext中 
	VkPhysicalDeviceShaderTerminateInvocationFeatures   physicalDeviceShaderTerminateInvocationFeatures{};
	physicalDeviceShaderTerminateInvocationFeatures.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_TERMINATE_INVOCATION_FEATURES;
	physicalDeviceShaderTerminateInvocationFeatures.pNext = nullptr;
	physicalDeviceShaderTerminateInvocationFeatures.shaderTerminateInvocation = VK_FALSE;//指明是否支持SPIR-V modules 使用 SPV_KHR_terminate_invocation 拓展


	//VkPhysicalDeviceCustomBorderColorFeaturesEXT ，  可以包含在VkPhysicalDeviceFeatures2.pNext中 
	VkPhysicalDeviceCustomBorderColorFeaturesEXT   physicalDeviceCustomBorderColorFeaturesEXT{};
	physicalDeviceCustomBorderColorFeaturesEXT.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_CUSTOM_BORDER_COLOR_FEATURES_EXT;
	physicalDeviceCustomBorderColorFeaturesEXT.pNext = nullptr;
	physicalDeviceCustomBorderColorFeaturesEXT.customBorderColors = VK_FALSE;//指明是否支持在创建一个sampler是指定  borderColor为 VK_BORDER_COLOR_FLOAT_CUSTOM_EXT 或者 VK_BORDER_COLOR_INT_CUSTOM_EXT
	physicalDeviceCustomBorderColorFeaturesEXT.customBorderColorWithoutFormat = VK_FALSE;//指定是否custom border color 扩展不需要显式指定format，即VkSamplerCustomBorderColorCreateInfoEXT.format 可以为VK_FORMAT_UNDEFINED,如果不支持则必须提供一个有效的format给VkSamplerCustomBorderColorCreateInfoEXT.format



	//VkPhysicalDeviceBorderColorSwizzleFeaturesEXT ，  可以包含在VkPhysicalDeviceFeatures2.pNext中 
	VkPhysicalDeviceBorderColorSwizzleFeaturesEXT   physicalDeviceBorderColorSwizzleFeaturesEXT{};
	physicalDeviceBorderColorSwizzleFeaturesEXT.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_BORDER_COLOR_SWIZZLE_FEATURES_EXT;
	physicalDeviceBorderColorSwizzleFeaturesEXT.pNext = nullptr;
	physicalDeviceBorderColorSwizzleFeaturesEXT.borderColorSwizzle = VK_FALSE;//指明当一个sampler使用 VK_BORDER_COLOR_FLOAT_OPAQUE_BLACK, VK_BORDER_COLOR_INT_OPAQUE_BLACK, VK_BORDER_COLOR_FLOAT_CUSTOM_EXT, 或者 VK_BORDER_COLOR_INT_CUSTOM_EXT borderColor 且image view 使用 non-identity component mapping，且当borderColorSwizzleFromImage 开启或者指定了VkSamplerBorderColorComponentMappingCreateInfoEXT 时sampled image operations 返回定义的值，
	physicalDeviceBorderColorSwizzleFeaturesEXT.borderColorSwizzleFromImage = VK_FALSE;//指定在上一个条件下的sampled image operations 是否返回边界的值，且不需要再创建sampler的时候定义color component mapping


	//VkPhysicalDevicePortabilitySubsetFeaturesKHR ，  可以包含在VkPhysicalDeviceFeatures2.pNext中 
	VkPhysicalDevicePortabilitySubsetFeaturesKHR   physicalDevicePortabilitySubsetFeaturesKHR{};
	physicalDevicePortabilitySubsetFeaturesKHR.sType = VK_STRUCTURE_TYPE_MAX_ENUM;//没有定义这里定义为非法值
	physicalDevicePortabilitySubsetFeaturesKHR.pNext = nullptr;
	physicalDevicePortabilitySubsetFeaturesKHR.constantAlphaColorBlendFactors = VK_FALSE;//指明是否支持用于source 或者 destination color Blending的constant alpha Blend Factors
	physicalDevicePortabilitySubsetFeaturesKHR.events = VK_FALSE;//指明是否支持使用 VkEvent 进行同步
	physicalDevicePortabilitySubsetFeaturesKHR.imageViewFormatReinterpretation = VK_FALSE;//指明相对于VkImage的 texel format，是否支持VkImageView 以包含不同数量分量的texel format 或者每个分量不同bit创建
	physicalDevicePortabilitySubsetFeaturesKHR.imageViewFormatSwizzle = VK_FALSE;//指明是否支持通过 VkImageViewCreateInfo::components 重新映射format分量
	physicalDevicePortabilitySubsetFeaturesKHR.imageView2DOn3DImage = VK_FALSE;//指明是否支持VkImage以 VK_IMAGE_CREATE_2D_ARRAY_COMPATIBLE_BIT 创建，允许在3D image上创建2D 或者 2D array image view
	physicalDevicePortabilitySubsetFeaturesKHR.multisampleArrayImage = VK_FALSE;//指明是否支持创建每个texel含多个采样点sample的 2D array image
	physicalDevicePortabilitySubsetFeaturesKHR.mutableComparisonSamplers = VK_FALSE;//指明是否支持更新带比较sampler的descriptors
	physicalDevicePortabilitySubsetFeaturesKHR.pointPolygons = VK_FALSE;//指明是否支持使用point Polygon Mode 进行Rasterization
	physicalDevicePortabilitySubsetFeaturesKHR.samplerMipLodBias = VK_FALSE;//指明是否支持在创建sampler时指定 mipmap LOD bias 值
	physicalDevicePortabilitySubsetFeaturesKHR.separateStencilMaskRef = VK_FALSE;//指明是否支持分量front 以及 back的Stencil Test reference value
	physicalDevicePortabilitySubsetFeaturesKHR.shaderSampleRateInterpolationFunctions = VK_FALSE;//指明是否支持fragment shaders 使用 InterpolationFunction 能力以及来自 GLSL.std.450 拓展集的的InterpolateAtCentroid, InterpolateAtOffset, 以及 InterpolateAtSample指令，该特性只在 sampleRateShading 开启时有效
	physicalDevicePortabilitySubsetFeaturesKHR.tessellationIsolines = VK_FALSE;//指明是否支持在graphics pipeline的Tessellation stage输出isoline output， 只在 tessellationShader 特性开启时有效
	physicalDevicePortabilitySubsetFeaturesKHR.tessellationPointMode = VK_FALSE;//指明是否支持在graphics pipeline的Tessellation stage输出point output， 只在 tessellationShader 特性开启时有效
	physicalDevicePortabilitySubsetFeaturesKHR.triangleFans = VK_FALSE;//指明是否支持 Triangle Fans 图元拓扑
	physicalDevicePortabilitySubsetFeaturesKHR.vertexAttributeAccessBeyondStride = VK_FALSE;//指明是否支持超过对应vertex input binding 的stride步长访问vertex input attribute
	

	//VkPhysicalDevicePerformanceQueryFeaturesKHR ，  可以包含在VkPhysicalDeviceFeatures2.pNext中 
	VkPhysicalDevicePerformanceQueryFeaturesKHR   physicalDevicePerformanceQueryFeaturesKHR{};
	physicalDevicePerformanceQueryFeaturesKHR.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PERFORMANCE_QUERY_FEATURES_KHR;
	physicalDevicePerformanceQueryFeaturesKHR.pNext = nullptr;
	physicalDevicePerformanceQueryFeaturesKHR.performanceCounterQueryPools = VK_FALSE;//指明是否支持 performance counter query pools
	physicalDevicePerformanceQueryFeaturesKHR.performanceCounterMultipleQueryPools = VK_FALSE;//指明是否支持在一个primary command buffer和在其中执行的secondary command buffer中使用多个performance query pools


	//VkPhysicalDevice4444FormatsFeaturesEXT ，  可以包含在VkPhysicalDeviceFeatures2.pNext中 
	VkPhysicalDevice4444FormatsFeaturesEXT   physicalDevice4444FormatsFeaturesEXT{};
	physicalDevice4444FormatsFeaturesEXT.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_4444_FORMATS_FEATURES_EXT;
	physicalDevice4444FormatsFeaturesEXT.pNext = nullptr;
	physicalDevice4444FormatsFeaturesEXT.formatA4R4G4B4 = VK_FALSE;//指明是否必须支持format features至少含有VK_FORMAT_FEATURE_SAMPLED_IMAGE_BIT , VK_FORMAT_FEATURE_BLIT_SRC_BIT 以及VK_FORMAT_FEATURE_SAMPLED_IMAGE_FILTER_LINEAR_BIT 的VK_FORMAT_A4R4G4B4_UNORM_PACK16_EXT
	physicalDevice4444FormatsFeaturesEXT.formatA4B4G4R4 = VK_FALSE;//指明是否必须支持format features至少含有VK_FORMAT_FEATURE_SAMPLED_IMAGE_BIT , VK_FORMAT_FEATURE_BLIT_SRC_BIT 以及VK_FORMAT_FEATURE_SAMPLED_IMAGE_FILTER_LINEAR_BIT 的VK_FORMAT_A4B4G4R4_UNORM_PACK16_EXT



	//VkPhysicalDeviceMutableDescriptorTypeFeaturesEXT ，等价于 VkPhysicalDeviceMutableDescriptorTypeFeaturesVALVE，  可以包含在VkPhysicalDeviceFeatures2.pNext中 
	VkPhysicalDeviceMutableDescriptorTypeFeaturesEXT  physicalDeviceMutableDescriptorTypeFeaturesEXT{};
	physicalDeviceMutableDescriptorTypeFeaturesEXT.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MUTABLE_DESCRIPTOR_TYPE_FEATURES_EXT;
	physicalDeviceMutableDescriptorTypeFeaturesEXT.pNext = nullptr;
	physicalDeviceMutableDescriptorTypeFeaturesEXT.mutableDescriptorType = VK_FALSE;//指明是否支持VkDescriptorType为 VK_DESCRIPTOR_TYPE_MUTABLE_EXT ，且VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE， VK_DESCRIPTOR_TYPE_STORAGE_IMAGE， VK_DESCRIPTOR_TYPE_UNIFORM_TEXEL_BUFFER， VK_DESCRIPTOR_TYPE_STORAGE_TEXEL_BUFFER， VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER，VK_DESCRIPTOR_TYPE_STORAGE_BUFFER的任意组合都支持



	//VkPhysicalDeviceDepthClipControlFeaturesEXT ，  可以包含在VkPhysicalDeviceFeatures2.pNext中 
	VkPhysicalDeviceDepthClipControlFeaturesEXT  physicalDeviceDepthClipControlFeaturesEXT{};
	physicalDeviceDepthClipControlFeaturesEXT.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DEPTH_CLIP_CONTROL_FEATURES_EXT;
	physicalDeviceDepthClipControlFeaturesEXT.pNext = nullptr;
	physicalDeviceDepthClipControlFeaturesEXT.depthClipControl = VK_FALSE;//指明是否支持设置VkPipelineViewportDepthClipControlCreateInfoEXT::negativeOneToOne 为VK_TRUE



	//VkPhysicalDeviceWorkgroupMemoryExplicitLayoutFeaturesKHR ，  可以包含在VkPhysicalDeviceFeatures2.pNext中 
	VkPhysicalDeviceWorkgroupMemoryExplicitLayoutFeaturesKHR  physicalDeviceWorkgroupMemoryExplicitLayoutFeaturesKHR{};
	physicalDeviceWorkgroupMemoryExplicitLayoutFeaturesKHR.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_WORKGROUP_MEMORY_EXPLICIT_LAYOUT_FEATURES_KHR;
	physicalDeviceWorkgroupMemoryExplicitLayoutFeaturesKHR.pNext = nullptr;
	physicalDeviceWorkgroupMemoryExplicitLayoutFeaturesKHR.workgroupMemoryExplicitLayout = VK_FALSE;//指明是否支持SPIR-V WorkgroupMemoryExplicitLayoutKHR 能力
	physicalDeviceWorkgroupMemoryExplicitLayoutFeaturesKHR.workgroupMemoryExplicitLayoutScalarBlockLayout = VK_FALSE;//指明是否Workgroup Blocks布局支持 scalar alignment
	physicalDeviceWorkgroupMemoryExplicitLayoutFeaturesKHR.workgroupMemoryExplicitLayout8BitAccess = VK_FALSE;//指明是否 Workgroup storage class中以 Block声明的对象可以含有8-bit整数对象。也说明shader module中是否声明有WorkgroupMemoryExplicitLayout8BitAccessKHR 能力
	physicalDeviceWorkgroupMemoryExplicitLayoutFeaturesKHR.workgroupMemoryExplicitLayout16BitAccess = VK_FALSE;//指明是否 Workgroup storage class中以 Block声明的对象可以含有16-bit整数以及浮点数对象。也说明shader module中是否声明有WorkgroupMemoryExplicitLayout16BitAccessKHR 能力



	//VkPhysicalDeviceSynchronization2Features ，等同于VkPhysicalDeviceSynchronization2FeaturesKHR，  可以包含在VkPhysicalDeviceFeatures2.pNext中 
	VkPhysicalDeviceSynchronization2Features  physicalDeviceSynchronization2Features{};
	physicalDeviceSynchronization2Features.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SYNCHRONIZATION_2_FEATURES;
	physicalDeviceSynchronization2Features.pNext = nullptr;
	physicalDeviceSynchronization2Features.synchronization2 = VK_FALSE;//指明是否支持 VK_KHR_synchronization2. 拓展中的新的同步命令集



	//VkPhysicalDeviceVertexInputDynamicStateFeaturesEXT ，  可以包含在VkPhysicalDeviceFeatures2.pNext中 
	VkPhysicalDeviceVertexInputDynamicStateFeaturesEXT  physicalDeviceVertexInputDynamicStateFeaturesEXT{};
	physicalDeviceVertexInputDynamicStateFeaturesEXT.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VERTEX_INPUT_DYNAMIC_STATE_FEATURES_EXT;
	physicalDeviceVertexInputDynamicStateFeaturesEXT.pNext = nullptr;
	physicalDeviceVertexInputDynamicStateFeaturesEXT.vertexInputDynamicState = VK_FALSE;//指明是否支持动态 state:VK_DYNAMIC_STATE_VERTEX_INPUT_EXT


	//VkPhysicalDevicePrimitivesGeneratedQueryFeaturesEXT ，  可以包含在VkPhysicalDeviceFeatures2.pNext中 
	VkPhysicalDevicePrimitivesGeneratedQueryFeaturesEXT  physicalDevicePrimitivesGeneratedQueryFeaturesEXT{};
	physicalDevicePrimitivesGeneratedQueryFeaturesEXT.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PRIMITIVES_GENERATED_QUERY_FEATURES_EXT;
	physicalDevicePrimitivesGeneratedQueryFeaturesEXT.pNext = nullptr;
	physicalDevicePrimitivesGeneratedQueryFeaturesEXT.primitivesGeneratedQuery = VK_FALSE;//指明是否支持VK_QUERY_TYPE_PRIMITIVES_GENERATED_EXT query type.
	physicalDevicePrimitivesGeneratedQueryFeaturesEXT.primitivesGeneratedQueryWithRasterizerDiscard = VK_FALSE;//指明是否支持在 rasterization discard开启时进行query
	physicalDevicePrimitivesGeneratedQueryFeaturesEXT.primitivesGeneratedQueryWithNonZeroStreams = VK_FALSE;//指明是否支持在 vkCmdBeginQueryIndexedEXT中以非0索引开始query


	//VkPhysicalDeviceFragmentShadingRateFeaturesKHR ，  可以包含在VkPhysicalDeviceFeatures2.pNext中 
	VkPhysicalDeviceFragmentShadingRateFeaturesKHR  physicalDeviceFragmentShadingRateFeaturesKHR{};
	physicalDeviceFragmentShadingRateFeaturesKHR.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FRAGMENT_SHADING_RATE_FEATURES_KHR;
	physicalDeviceFragmentShadingRateFeaturesKHR.pNext = nullptr;
	physicalDeviceFragmentShadingRateFeaturesKHR.pipelineFragmentShadingRate = VK_FALSE;//指明是否支持pipeline fragment shading rate
	physicalDeviceFragmentShadingRateFeaturesKHR.primitiveFragmentShadingRate = VK_FALSE;//指明是否支持 primitive fragment shading rate
	physicalDeviceFragmentShadingRateFeaturesKHR.attachmentFragmentShadingRate = VK_FALSE;//指明是否支持attachment fragment shading rate


	//VkPhysicalDeviceLegacyDitheringFeaturesEXT ，  可以包含在VkPhysicalDeviceFeatures2.pNext中 
	VkPhysicalDeviceLegacyDitheringFeaturesEXT  physicalDeviceLegacyDitheringFeaturesEXT{};
	physicalDeviceLegacyDitheringFeaturesEXT.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_LEGACY_DITHERING_FEATURES_EXT;
	physicalDeviceLegacyDitheringFeaturesEXT.pNext = nullptr;
	physicalDeviceLegacyDitheringFeaturesEXT.legacyDithering = VK_FALSE;//指明是否支持 Legacy Dithering（遗留问题）.


	//VkPhysicalDeviceFragmentShadingRateEnumsFeaturesNV ，  可以包含在VkPhysicalDeviceFeatures2.pNext中 
	VkPhysicalDeviceFragmentShadingRateEnumsFeaturesNV  physicalDeviceFragmentShadingRateEnumsFeaturesNV{};
	physicalDeviceFragmentShadingRateEnumsFeaturesNV.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FRAGMENT_SHADING_RATE_ENUMS_FEATURES_NV;
	physicalDeviceFragmentShadingRateEnumsFeaturesNV.pNext = nullptr;
	physicalDeviceFragmentShadingRateEnumsFeaturesNV.fragmentShadingRateEnums = VK_FALSE;//指明是否支持fragment shading rate 使用VkFragmentShadingRateNV 枚举类型
	physicalDeviceFragmentShadingRateEnumsFeaturesNV.supersampleFragmentShadingRates = VK_FALSE;//指明是否支持fragment shading rate 枚举值指明每个fragment可以触发多次shader调用
	physicalDeviceFragmentShadingRateEnumsFeaturesNV.noInvocationFragmentShadingRates = VK_FALSE;//指明是否支持fragment shading rate 枚举值指明当使用shading rate 时不会使用额外的fragment shader调用 


	//VkPhysicalDeviceInheritedViewportScissorFeaturesNV ，  可以包含在VkPhysicalDeviceFeatures2.pNext中 
	VkPhysicalDeviceInheritedViewportScissorFeaturesNV  physicalDeviceInheritedViewportScissorFeaturesNV{};
	physicalDeviceInheritedViewportScissorFeaturesNV.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_INHERITED_VIEWPORT_SCISSOR_FEATURES_NV;
	physicalDeviceInheritedViewportScissorFeaturesNV.pNext = nullptr;
	physicalDeviceInheritedViewportScissorFeaturesNV.inheritedViewportScissor2D = VK_FALSE;//指明secondary command buffer是否可以从primary command buffer中继承大部分动态 state: VK_DYNAMIC_STATE_VIEWPORT_WITH_COUNT, VK_DYNAMIC_STATE_SCISSOR_WITH_COUNT, VK_DYNAMIC_STATE_DISCARD_RECTANGLE_EXT, VK_DYNAMIC_STATE_DISCARD_RECTANGLE_ENABLE_EXT, VK_DYNAMIC_STATE_DISCARD_RECTANGLE_MODE_EXT, VK_DYNAMIC_STATE_VIEWPORT 或者 VK_DYNAMIC_STATE_SCISSOR


	//VkPhysicalDevicePipelineProtectedAccessFeaturesEXT ，  可以包含在VkPhysicalDeviceFeatures2.pNext中 
	VkPhysicalDevicePipelineProtectedAccessFeaturesEXT  physicalDevicePipelineProtectedAccessFeaturesEXT{};
	physicalDevicePipelineProtectedAccessFeaturesEXT.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PIPELINE_PROTECTED_ACCESS_FEATURES_EXT;
	physicalDevicePipelineProtectedAccessFeaturesEXT.pNext = nullptr;
	physicalDevicePipelineProtectedAccessFeaturesEXT.pipelineProtectedAccess = VK_FALSE;//指明是否支持对独立的pipeline进行protected访问


	//VkPhysicalDeviceYcbcr2Plane444FormatsFeaturesEXT ，  可以包含在VkPhysicalDeviceFeatures2.pNext中 
	VkPhysicalDeviceYcbcr2Plane444FormatsFeaturesEXT  physicalDeviceYcbcr2Plane444FormatsFeaturesEXT{};
	physicalDeviceYcbcr2Plane444FormatsFeaturesEXT.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_YCBCR_2_PLANE_444_FORMATS_FEATURES_EXT;
	physicalDeviceYcbcr2Plane444FormatsFeaturesEXT.pNext = nullptr;
	physicalDeviceYcbcr2Plane444FormatsFeaturesEXT.ycbcr2plane444Formats = VK_FALSE;//指明是否支持2-plane 444 Y′CBCR formats: VK_FORMAT_G8_B8R8_2PLANE_444_UNORM, VK_FORMAT_G10X6_B10X6R10X6_2PLANE_444_UNORM_3PACK16, VK_FORMAT_G12X4_B12X4R12X4_2PLANE_444_UNORM_3PACK16 ,VK_FORMAT_G16_B16R16_2PLANE_444_UNORM


	//VkPhysicalDeviceColorWriteEnableFeaturesEXT ，  可以包含在VkPhysicalDeviceFeatures2.pNext中 
	VkPhysicalDeviceColorWriteEnableFeaturesEXT  physicalDeviceColorWriteEnableFeaturesEXT{};
	physicalDeviceColorWriteEnableFeaturesEXT.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_COLOR_WRITE_ENABLE_FEATURES_EXT;
	physicalDeviceColorWriteEnableFeaturesEXT.pNext = nullptr;
	physicalDeviceColorWriteEnableFeaturesEXT.colorWriteEnable = VK_FALSE;//指明是否支持动态state: VK_DYNAMIC_STATE_COLOR_WRITE_ENABLE_EXT


	//VkPhysicalDevicePipelinePropertiesFeaturesEXT ，  可以包含在VkPhysicalDeviceFeatures2.pNext中 
	VkPhysicalDevicePipelinePropertiesFeaturesEXT  physicalDevicePipelinePropertiesFeaturesEXT{};
	physicalDevicePipelinePropertiesFeaturesEXT.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PIPELINE_PROPERTIES_FEATURES_EXT;
	physicalDevicePipelinePropertiesFeaturesEXT.pNext = nullptr;
	physicalDevicePipelinePropertiesFeaturesEXT.pipelinePropertiesIdentifier = VK_FALSE;//指明是否支持查询一个唯一的pipeline identifier



	//VkPhysicalDeviceProvokingVertexFeaturesEXT ，  可以包含在VkPhysicalDeviceFeatures2.pNext中 
	VkPhysicalDeviceProvokingVertexFeaturesEXT  physicalDeviceProvokingVertexFeaturesEXT{};
	physicalDeviceProvokingVertexFeaturesEXT.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PROVOKING_VERTEX_FEATURES_EXT;
	physicalDeviceProvokingVertexFeaturesEXT.pNext = nullptr;
	physicalDeviceProvokingVertexFeaturesEXT.provokingVertexLast = VK_FALSE;//指明是否支持flat shading的VK_PROVOKING_VERTEX_MODE_LAST_VERTEX_EXT provoking vertex mode
	physicalDeviceProvokingVertexFeaturesEXT.transformFeedbackPreservesProvokingVertex = VK_FALSE;//指明写到transform feedback的图元中的顶点顺序中是否保存provoking vertex，当transformFeedbackPreservesTriangleFanProvokingVertex 为VK_FALSE的是否不会应用到triangle fan 图元中，当不支持VK_EXT_transform_feedback拓展时这里必须为VK_FALSE


	//VkPhysicalDeviceDescriptorBufferFeaturesEXT ，  可以包含在VkPhysicalDeviceFeatures2.pNext中 
	VkPhysicalDeviceDescriptorBufferFeaturesEXT  physicalDeviceDescriptorBufferFeaturesEXT{};
	physicalDeviceDescriptorBufferFeaturesEXT.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PROVOKING_VERTEX_FEATURES_EXT;
	physicalDeviceDescriptorBufferFeaturesEXT.pNext = nullptr;
	physicalDeviceDescriptorBufferFeaturesEXT.descriptorBuffer = VK_FALSE;//指明是否支持讲shader可访问的descriptor直接放到内存中
	physicalDeviceDescriptorBufferFeaturesEXT.descriptorBufferCaptureReplay = VK_FALSE;//指明是否支持使用descriptor buffer进行捕获和回放。如果支持，则所有含标志VK_BUFFER_CREATE_DESCRIPTOR_BUFFER_CAPTURE_REPLAY_BIT_EXT, VK_IMAGE_CREATE_DESCRIPTOR_BUFFER_CAPTURE_REPLAY_BIT_EXT,VK_IMAGE_VIEW_CREATE_DESCRIPTOR_BUFFER_CAPTURE_REPLAY_BIT_EXT,VK_SAMPLER_CREATE_DESCRIPTOR_BUFFER_CAPTURE_REPLAY_BIT_EXT, 或者VK_ACCELERATION_STRUCTURE_CREATE_DESCRIPTOR_BUFFER_CAPTURE_REPLAY_BIT_EXT的资源要比不含该标志的资源先行创建
	physicalDeviceDescriptorBufferFeaturesEXT.descriptorBufferImageLayoutIgnored = VK_FALSE;//指明是否忽略调用 vkGetDescriptorEXT中的 VkDescriptorImageInfo.layout
	physicalDeviceDescriptorBufferFeaturesEXT.descriptorBufferPushDescriptors = VK_FALSE;//指明是否支持push descriptors和descriptor buffers一起使用


	//VkPhysicalDevicePageableDeviceLocalMemoryFeaturesEXT ，  可以包含在VkPhysicalDeviceFeatures2.pNext中 
	VkPhysicalDevicePageableDeviceLocalMemoryFeaturesEXT  physicalDevicePageableDeviceLocalMemoryFeaturesEXT{};
	physicalDevicePageableDeviceLocalMemoryFeaturesEXT.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PAGEABLE_DEVICE_LOCAL_MEMORY_FEATURES_EXT;
	physicalDevicePageableDeviceLocalMemoryFeaturesEXT.pNext = nullptr;
	physicalDevicePageableDeviceLocalMemoryFeaturesEXT.pageableDeviceLocalMemory = VK_FALSE;//指明是否支持可分页的 device-local 内存以及将device-local的内存分配移到host-local内存中以便更好的在应用之间共享device-local内存


	//VkPhysicalDeviceMultiDrawFeaturesEXT ，  可以包含在VkPhysicalDeviceFeatures2.pNext中 
	VkPhysicalDeviceMultiDrawFeaturesEXT  physicalDeviceMultiDrawFeaturesEXT{};
	physicalDeviceMultiDrawFeaturesEXT.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MULTI_DRAW_FEATURES_EXT;
	physicalDeviceMultiDrawFeaturesEXT.pNext = nullptr;
	physicalDeviceMultiDrawFeaturesEXT.multiDraw = VK_FALSE;//指明是否支持vkCmdDrawMultiEXT 以及 vkCmdDrawMultiIndexedEXT 命令


	//VkPhysicalDeviceRayTracingMotionBlurFeaturesNV ，  可以包含在VkPhysicalDeviceFeatures2.pNext中 
	VkPhysicalDeviceRayTracingMotionBlurFeaturesNV  physicalDeviceRayTracingMotionBlurFeaturesNV{};
	physicalDeviceRayTracingMotionBlurFeaturesNV.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_RAY_TRACING_MOTION_BLUR_FEATURES_NV;
	physicalDeviceRayTracingMotionBlurFeaturesNV.pNext = nullptr;
	physicalDeviceRayTracingMotionBlurFeaturesNV.rayTracingMotionBlur = VK_FALSE;//指明是否支持motion blur运动模糊特性
	physicalDeviceRayTracingMotionBlurFeaturesNV.rayTracingMotionBlurPipelineTraceRaysIndirect = VK_FALSE;//指明是否支持在开启motion blur运动模糊特性下，使用间接ray tracing 命令


	//VkPhysicalDeviceOpacityMicromapFeaturesEXT ，  可以包含在VkPhysicalDeviceFeatures2.pNext中 
	VkPhysicalDeviceOpacityMicromapFeaturesEXT  physicalDeviceOpacityMicromapFeaturesEXT{};
	physicalDeviceOpacityMicromapFeaturesEXT.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_RAY_TRACING_MOTION_BLUR_FEATURES_NV;
	physicalDeviceOpacityMicromapFeaturesEXT.pNext = nullptr;
	physicalDeviceOpacityMicromapFeaturesEXT.micromap = VK_FALSE;//指明是否支持micromap array 特性
	physicalDeviceOpacityMicromapFeaturesEXT.micromapCaptureReplay = VK_FALSE;//指明是否支持micromap arrays的地址的捕获和回放
	physicalDeviceOpacityMicromapFeaturesEXT.micromapHostCommands = VK_FALSE;//指明是否支持 host 端的micromap array 命令


	//VkPhysicalDeviceDisplacementMicromapFeaturesNV ，  可以包含在VkPhysicalDeviceFeatures2.pNext中 
	VkPhysicalDeviceDisplacementMicromapFeaturesNV  physicalDeviceDisplacementMicromapFeaturesNV{};
	physicalDeviceDisplacementMicromapFeaturesNV.sType = VK_STRUCTURE_TYPE_MAX_ENUM;//没有定义这里定义为非法值
	physicalDeviceDisplacementMicromapFeaturesNV.pNext = nullptr;
	physicalDeviceDisplacementMicromapFeaturesNV.displacementMicromap = VK_FALSE;//指明是否支持displacement micromap特性



	//VkPhysicalDeviceRayTracingValidationFeaturesNV ，  可以包含在VkPhysicalDeviceFeatures2.pNext中 
	VkPhysicalDeviceRayTracingValidationFeaturesNV  physicalDeviceRayTracingValidationFeaturesNV{};
	physicalDeviceRayTracingValidationFeaturesNV.sType = VK_STRUCTURE_TYPE_MAX_ENUM;//没有定义这里定义为非法值
	physicalDeviceRayTracingValidationFeaturesNV.pNext = nullptr;
	physicalDeviceRayTracingValidationFeaturesNV.rayTracingValidation = VK_FALSE;//指明是否支持ray tracing validation 特性


	//VkPhysicalDeviceSubpassShadingFeaturesHUAWEI ，  可以包含在VkPhysicalDeviceFeatures2.pNext中 
	VkPhysicalDeviceSubpassShadingFeaturesHUAWEI  physicalDeviceSubpassShadingFeaturesHUAWEI{};
	physicalDeviceSubpassShadingFeaturesHUAWEI.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SUBPASS_SHADING_FEATURES_HUAWEI;
	physicalDeviceSubpassShadingFeaturesHUAWEI.pNext = nullptr;
	physicalDeviceSubpassShadingFeaturesHUAWEI.subpassShading = VK_FALSE;//指明是否支持 subpass shading


	//VkPhysicalDeviceExternalMemoryRDMAFeaturesNV ，  可以包含在VkPhysicalDeviceFeatures2.pNext中 
	VkPhysicalDeviceExternalMemoryRDMAFeaturesNV  physicalDeviceExternalMemoryRDMAFeaturesNV{};
	physicalDeviceExternalMemoryRDMAFeaturesNV.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_EXTERNAL_MEMORY_RDMA_FEATURES_NV;
	physicalDeviceExternalMemoryRDMAFeaturesNV.pNext = nullptr;
	physicalDeviceExternalMemoryRDMAFeaturesNV.externalMemoryRDMA = VK_FALSE;//指明是否支持VK_MEMORY_PROPERTY_RDMA_CAPABLE_BIT_NV 内存属性以及VK_EXTERNAL_MEMORY_HANDLE_TYPE_RDMA_ADDRESS_BIT_NV 外部内存句柄类型


	//VkPhysicalDevicePresentIdFeaturesKHR ，  可以包含在VkPhysicalDeviceFeatures2.pNext中 
	VkPhysicalDevicePresentIdFeaturesKHR  physicalDevicePresentIdFeaturesKHR{};
	physicalDevicePresentIdFeaturesKHR.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PRESENT_ID_FEATURES_KHR;
	physicalDevicePresentIdFeaturesKHR.pNext = nullptr;
	physicalDevicePresentIdFeaturesKHR.presentId = VK_FALSE;//指明是否支持在VkPresentInfoKHR.pNext中的VkPresentIdKHR中指定present id值


	//VkPhysicalDevicePresentWaitFeaturesKHR ，  可以包含在VkPhysicalDeviceFeatures2.pNext中 
	VkPhysicalDevicePresentWaitFeaturesKHR  physicalDevicePresentWaitFeaturesKHR{};
	physicalDevicePresentWaitFeaturesKHR.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PRESENT_WAIT_FEATURES_KHR;
	physicalDevicePresentWaitFeaturesKHR.pNext = nullptr;
	physicalDevicePresentWaitFeaturesKHR.presentWait = VK_FALSE;//指明是否支持 vkWaitForPresentKHR


	//VkPhysicalDeviceHostImageCopyFeaturesEXT ，  可以包含在VkPhysicalDeviceFeatures2.pNext中 
	VkPhysicalDeviceHostImageCopyFeaturesEXT  physicalDeviceHostImageCopyFeaturesEXT{};
	physicalDeviceHostImageCopyFeaturesEXT.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_HOST_IMAGE_COPY_FEATURES_EXT;
	physicalDeviceHostImageCopyFeaturesEXT.pNext = nullptr;
	physicalDeviceHostImageCopyFeaturesEXT.hostImageCopy = VK_FALSE;//指明是否支持使用 vkCopyMemoryToImageEXT拷贝host memory到image，使用 vkCopyImageToMemoryEXT拷贝image 到host memory，在host端使用vkCopyImageToImageEXT在image间进行拷贝


	//VkPhysicalDevicePresentBarrierFeaturesNV ，  可以包含在VkPhysicalDeviceFeatures2.pNext中 
	VkPhysicalDevicePresentBarrierFeaturesNV  physicalDevicePresentBarrierFeaturesNV{};
	physicalDevicePresentBarrierFeaturesNV.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PRESENT_BARRIER_FEATURES_NV;
	physicalDevicePresentBarrierFeaturesNV.pNext = nullptr;
	physicalDevicePresentBarrierFeaturesNV.presentBarrier = VK_FALSE;//指明是否支持present barrier 特性


	//VkPhysicalDeviceShaderIntegerDotProductFeatures ，等价于VkPhysicalDeviceShaderIntegerDotProductFeaturesKHR，  可以包含在VkPhysicalDeviceFeatures2.pNext中 
	VkPhysicalDeviceShaderIntegerDotProductFeatures  physicalDeviceShaderIntegerDotProductFeatures{};
	physicalDeviceShaderIntegerDotProductFeatures.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_INTEGER_DOT_PRODUCT_FEATURES;
	physicalDeviceShaderIntegerDotProductFeatures.pNext = nullptr;
	physicalDeviceShaderIntegerDotProductFeatures.shaderIntegerDotProduct = VK_FALSE;//指明shader module是否可以声明DotProductInputAllKHR, DotProductInput4x8BitKHR, DotProductInput4x8BitPackedKHR 以及 DotProductKHR 能力


	//VkPhysicalDeviceMaintenance4Features ，等价于VkPhysicalDeviceMaintenance4FeaturesKHR，  可以包含在VkPhysicalDeviceFeatures2.pNext中 
	VkPhysicalDeviceMaintenance4Features  physicalDeviceMaintenance4Features{};
	physicalDeviceMaintenance4Features.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MAINTENANCE_4_FEATURES;
	physicalDeviceMaintenance4Features.pNext = nullptr;
	physicalDeviceMaintenance4Features.maintenance4 = VK_FALSE;//指明是否支持: 1.使用 VkPipelineLayout 创建一个对象后立即销毁该pipeline；2.LocalSizeId 可以替换 LocalSize;3.以相同参数创建的image的对齐要求相同;4.buffer以及image的大小内存要求不会大于另一个内存比该buffer或者image大的内存大小要求;5.在动态访问之前Push constants不必初始化;6.接口匹配规则允许大的output vec和小的input vec匹配，多的分量会被丢弃



	//VkPhysicalDeviceMaintenance5FeaturesKHR ，  可以包含在VkPhysicalDeviceFeatures2.pNext中 
	VkPhysicalDeviceMaintenance5FeaturesKHR  physicalDeviceMaintenance5FeaturesKHR{};
	physicalDeviceMaintenance5FeaturesKHR.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MAINTENANCE_5_FEATURES_KHR;
	physicalDeviceMaintenance5FeaturesKHR.pNext = nullptr;
	physicalDeviceMaintenance5FeaturesKHR.maintenance5 = VK_FALSE;//具体支持什么参见p3859 ***


	//VkPhysicalDeviceMaintenance6FeaturesKHR ，  可以包含在VkPhysicalDeviceFeatures2.pNext中 
	VkPhysicalDeviceMaintenance6FeaturesKHR  physicalDeviceMaintenance6FeaturesKHR{};
	physicalDeviceMaintenance6FeaturesKHR.sType = VK_STRUCTURE_TYPE_MAX_ENUM;//没有定义这里定义为非法值
	physicalDeviceMaintenance6FeaturesKHR.pNext = nullptr;
	physicalDeviceMaintenance6FeaturesKHR.maintenance6 = VK_FALSE;//具体支持什么参见p3860 ***


	//VkPhysicalDeviceDynamicRenderingFeatures ， 等价于VkPhysicalDeviceDynamicRenderingFeaturesKHR， 可以包含在VkPhysicalDeviceFeatures2.pNext中 
	VkPhysicalDeviceDynamicRenderingFeatures  physicalDeviceDynamicRenderingFeatures{};
	physicalDeviceDynamicRenderingFeatures.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DYNAMIC_RENDERING_FEATURES;
	physicalDeviceDynamicRenderingFeatures.pNext = nullptr;
	physicalDeviceDynamicRenderingFeatures.dynamicRendering = VK_FALSE;//指明是否可以使用 vkCmdBeginRendering 命令支持动态render pass 实例


	//VkPhysicalDeviceRGBA10X6FormatsFeaturesEXT ， 可以包含在VkPhysicalDeviceFeatures2.pNext中 
	VkPhysicalDeviceRGBA10X6FormatsFeaturesEXT  physicalDeviceRGBA10X6FormatsFeaturesEXT{};
	physicalDeviceRGBA10X6FormatsFeaturesEXT.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_RGBA10X6_FORMATS_FEATURES_EXT;
	physicalDeviceRGBA10X6FormatsFeaturesEXT.pNext = nullptr;
	physicalDeviceRGBA10X6FormatsFeaturesEXT.formatRgba10x6WithoutYCbCrSampler = VK_FALSE;//指明在不开启 sampler Y′CBCR conversion下VK_FORMAT_R10X6G10X6B10X6A10X6_UNORM_4PACK16 可用于一个subresourceRange.aspectMask 为VK_IMAGE_ASPECT_COLOR_BIT的VkImageView


	//VkPhysicalDevicePipelineRobustnessFeaturesEXT ， 可以包含在VkPhysicalDeviceFeatures2.pNext中 
	VkPhysicalDevicePipelineRobustnessFeaturesEXT  physicalDevicePipelineRobustnessFeaturesEXT{};
	physicalDevicePipelineRobustnessFeaturesEXT.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PIPELINE_ROBUSTNESS_FEATURES_EXT;
	physicalDevicePipelineRobustnessFeaturesEXT.pNext = nullptr;
	physicalDevicePipelineRobustnessFeaturesEXT.pipelineRobustness = VK_FALSE;//指明可以请求per-pipeline-stage粒度的robustness鲁棒性


	//VkPhysicalDeviceImageViewMinLodFeaturesEXT ， 可以包含在VkPhysicalDeviceFeatures2.pNext中 
	VkPhysicalDeviceImageViewMinLodFeaturesEXT  physicalDeviceImageViewMinLodFeaturesEXT{};
	physicalDeviceImageViewMinLodFeaturesEXT.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_IMAGE_VIEW_MIN_LOD_FEATURES_EXT;
	physicalDeviceImageViewMinLodFeaturesEXT.pNext = nullptr;
	physicalDeviceImageViewMinLodFeaturesEXT.minLod = VK_FALSE;//指明是否支持通过 VkImageViewMinLodCreateInfoEXT::minLod 限制LOD的最小值


	//VkPhysicalDeviceRasterizationOrderAttachmentAccessFeaturesEXT ，等价于VkPhysicalDeviceRasterizationOrderAttachmentAccessFeaturesARM， 可以包含在VkPhysicalDeviceFeatures2.pNext中 
	VkPhysicalDeviceRasterizationOrderAttachmentAccessFeaturesEXT  physicalDeviceRasterizationOrderAttachmentAccessFeaturesEXT{};
	physicalDeviceRasterizationOrderAttachmentAccessFeaturesEXT.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_RASTERIZATION_ORDER_ATTACHMENT_ACCESS_FEATURES_EXT;
	physicalDeviceRasterizationOrderAttachmentAccessFeaturesEXT.pNext = nullptr;
	physicalDeviceRasterizationOrderAttachmentAccessFeaturesEXT.rasterizationOrderColorAttachmentAccess = VK_FALSE;//指明是否支持通过  rasterization order 访问color以及input attachments
	physicalDeviceRasterizationOrderAttachmentAccessFeaturesEXT.rasterizationOrderDepthAttachmentAccess = VK_FALSE;//指明是否支持通过  rasterization order 访问depth/stencil attachment的depth aspect以及input attachments
	physicalDeviceRasterizationOrderAttachmentAccessFeaturesEXT.rasterizationOrderStencilAttachmentAccess = VK_FALSE;//指明是否支持通过  rasterization order 访问depth/stencil attachment的stencil aspect以及input attachments


	//VkPhysicalDeviceSubpassMergeFeedbackFeaturesEXT ， 可以包含在VkPhysicalDeviceFeatures2.pNext中 
	VkPhysicalDeviceSubpassMergeFeedbackFeaturesEXT  physicalDeviceSubpassMergeFeedbackFeaturesEXT{};
	physicalDeviceSubpassMergeFeedbackFeaturesEXT.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SUBPASS_MERGE_FEEDBACK_FEATURES_EXT;
	physicalDeviceSubpassMergeFeedbackFeaturesEXT.pNext = nullptr;
	physicalDeviceSubpassMergeFeedbackFeaturesEXT.subpassMergeFeedback = VK_FALSE;//指明是否支持subpass merge的feedback


	//VkPhysicalDeviceLinearColorAttachmentFeaturesNV ， 可以包含在VkPhysicalDeviceFeatures2.pNext中 
	VkPhysicalDeviceLinearColorAttachmentFeaturesNV  physicalDeviceLinearColorAttachmentFeaturesNV{};
	physicalDeviceLinearColorAttachmentFeaturesNV.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_LINEAR_COLOR_ATTACHMENT_FEATURES_NV;
	physicalDeviceLinearColorAttachmentFeaturesNV.pNext = nullptr;
	physicalDeviceLinearColorAttachmentFeaturesNV.linearColorAttachment = VK_FALSE;//指明是否支持 renderable Linear Color Attachment


	//VkPhysicalDeviceAttachmentFeedbackLoopLayoutFeaturesEXT ， 可以包含在VkPhysicalDeviceFeatures2.pNext中 
	VkPhysicalDeviceAttachmentFeedbackLoopLayoutFeaturesEXT  physicalDeviceAttachmentFeedbackLoopLayoutFeaturesEXT{};
	physicalDeviceAttachmentFeedbackLoopLayoutFeaturesEXT.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_ATTACHMENT_FEEDBACK_LOOP_LAYOUT_FEATURES_EXT;
	physicalDeviceAttachmentFeedbackLoopLayoutFeaturesEXT.pNext = nullptr;
	physicalDeviceAttachmentFeedbackLoopLayoutFeaturesEXT.attachmentFeedbackLoopLayout = VK_FALSE;//指明以VK_IMAGE_USAGE_ATTACHMENT_FEEDBACK_LOOP_BIT_EXT 创建的image是否可以使用VK_IMAGE_LAYOUT_ATTACHMENT_FEEDBACK_LOOP_OPTIMAL_EXT


	//VkPhysicalDeviceNestedCommandBufferFeaturesEXT ， 可以包含在VkPhysicalDeviceFeatures2.pNext中 
	VkPhysicalDeviceNestedCommandBufferFeaturesEXT  physicalDeviceNestedCommandBufferFeaturesEXT{};
	physicalDeviceNestedCommandBufferFeaturesEXT.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_ATTACHMENT_FEEDBACK_LOOP_LAYOUT_FEATURES_EXT;
	physicalDeviceNestedCommandBufferFeaturesEXT.pNext = nullptr;
	physicalDeviceNestedCommandBufferFeaturesEXT.nestedCommandBuffer = VK_FALSE;//指明是否支持nested command buffers，该特性能够允许secondary command buffer在secondary command buffer中执行
	physicalDeviceNestedCommandBufferFeaturesEXT.nestedCommandBufferRendering = VK_FALSE;//指明是否能够在一个以 VK_COMMAND_BUFFER_USAGE_RENDER_PASS_CONTINUE_BIT记录的secondary command buffer中调用 vkCmdExecuteCommands
	physicalDeviceNestedCommandBufferFeaturesEXT.nestedCommandBufferSimultaneousUse = VK_FALSE;//指明是否支持nested command buffers 和以VK_COMMAND_BUFFER_USAGE_SIMULTANEOUS_USE_BIT. 记录的command buffers一起使用


	//VkPhysicalDeviceGraphicsPipelineLibraryFeaturesEXT ， 可以包含在VkPhysicalDeviceFeatures2.pNext中 
	VkPhysicalDeviceGraphicsPipelineLibraryFeaturesEXT  physicalDeviceGraphicsPipelineLibraryFeaturesEXT{};
	physicalDeviceGraphicsPipelineLibraryFeaturesEXT.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_GRAPHICS_PIPELINE_LIBRARY_FEATURES_EXT;
	physicalDeviceGraphicsPipelineLibraryFeaturesEXT.pNext = nullptr;
	physicalDeviceGraphicsPipelineLibraryFeaturesEXT.graphicsPipelineLibrary = VK_FALSE;//指明是否支持 graphics pipeline libraries


	//VkPhysicalDeviceMultisampledRenderToSingleSampledFeaturesEXT ， 可以包含在VkPhysicalDeviceFeatures2.pNext中 
	VkPhysicalDeviceMultisampledRenderToSingleSampledFeaturesEXT  physicalDeviceMultisampledRenderToSingleSampledFeaturesEXT{};
	physicalDeviceMultisampledRenderToSingleSampledFeaturesEXT.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MULTISAMPLED_RENDER_TO_SINGLE_SAMPLED_FEATURES_EXT;
	physicalDeviceMultisampledRenderToSingleSampledFeaturesEXT.pNext = nullptr;
	physicalDeviceMultisampledRenderToSingleSampledFeaturesEXT.multisampledRenderToSingleSampled = VK_FALSE;//指明是否支持multisampled rendering 到 single-sampled render pass attachments


	//VkPhysicalDeviceImage2DViewOf3DFeaturesEXT ， 可以包含在VkPhysicalDeviceFeatures2.pNext中 
	VkPhysicalDeviceImage2DViewOf3DFeaturesEXT  physicalDeviceImage2DViewOf3DFeaturesEXT{};
	physicalDeviceImage2DViewOf3DFeaturesEXT.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_IMAGE_2D_VIEW_OF_3D_FEATURES_EXT;
	physicalDeviceImage2DViewOf3DFeaturesEXT.pNext = nullptr;
	physicalDeviceImage2DViewOf3DFeaturesEXT.image2DViewOf3D = VK_FALSE;//指明如果image以VK_IMAGE_CREATE_2D_VIEW_COMPATIBLE_BIT_EXT创建，则是否支持一个VK_DESCRIPTOR_TYPE_STORAGE_IMAGE类型的descriptor可以使用3D image的一个2D image view
	physicalDeviceImage2DViewOf3DFeaturesEXT.sampler2DViewOf3D = VK_FALSE;//指明如果image以VK_IMAGE_CREATE_2D_VIEW_COMPATIBLE_BIT_EXT创建，则是否支持一个VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE 或者 VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER类型的descriptor可以使用3D image的一个2D image view


	//VkPhysicalDeviceImageSlicedViewOf3DFeaturesEXT ， 可以包含在VkPhysicalDeviceFeatures2.pNext中 
	VkPhysicalDeviceImageSlicedViewOf3DFeaturesEXT  physicalDeviceImageSlicedViewOf3DFeaturesEXT{};
	physicalDeviceImageSlicedViewOf3DFeaturesEXT.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_IMAGE_SLICED_VIEW_OF_3D_FEATURES_EXT;
	physicalDeviceImageSlicedViewOf3DFeaturesEXT.pNext = nullptr;
	physicalDeviceImageSlicedViewOf3DFeaturesEXT.imageSlicedViewOf3D = VK_FALSE;//指明是否支持一个VK_DESCRIPTOR_TYPE_STORAGE_IMAGE类型的descriptor可以使用以VkImageViewSlicedCreateInfoEXT 创建的一个3D image的sliced image view


	//VkPhysicalDeviceImageCompressionControlFeaturesEXT ， 可以包含在VkPhysicalDeviceFeatures2.pNext中 
	VkPhysicalDeviceImageCompressionControlFeaturesEXT  physicalDeviceImageCompressionControlFeaturesEXT{};
	physicalDeviceImageCompressionControlFeaturesEXT.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_IMAGE_COMPRESSION_CONTROL_FEATURES_EXT;
	physicalDeviceImageCompressionControlFeaturesEXT.pNext = nullptr;
	physicalDeviceImageCompressionControlFeaturesEXT.imageCompressionControl = VK_FALSE;//指明是否支持在image创建的时候提供对image压缩的控制


	//VkPhysicalDeviceImageCompressionControlSwapchainFeaturesEXT ， 可以包含在VkPhysicalDeviceFeatures2.pNext中 
	VkPhysicalDeviceImageCompressionControlSwapchainFeaturesEXT  physicalDeviceImageCompressionControlSwapchainFeaturesEXT{};
	physicalDeviceImageCompressionControlSwapchainFeaturesEXT.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_IMAGE_COMPRESSION_CONTROL_SWAPCHAIN_FEATURES_EXT;
	physicalDeviceImageCompressionControlSwapchainFeaturesEXT.pNext = nullptr;
	physicalDeviceImageCompressionControlSwapchainFeaturesEXT.imageCompressionControlSwapchain = VK_FALSE;//指明是否支持控制每个swapchain的image控制以及每个surface的image压缩格式属性查询


	//VkPhysicalDeviceRayTracingPositionFetchFeaturesKHR ， 可以包含在VkPhysicalDeviceFeatures2.pNext中 
	VkPhysicalDeviceRayTracingPositionFetchFeaturesKHR  physicalDeviceRayTracingPositionFetchFeaturesKHR{};
	physicalDeviceRayTracingPositionFetchFeaturesKHR.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_RAY_TRACING_POSITION_FETCH_FEATURES_KHR;
	physicalDeviceRayTracingPositionFetchFeaturesKHR.pNext = nullptr;
	physicalDeviceRayTracingPositionFetchFeaturesKHR.rayTracingPositionFetch = VK_FALSE;//指明是否支持获取击中的三角行的物体空间顶点坐标


	//VkPhysicalDeviceShaderFloatControls2FeaturesKHR ， 可以包含在VkPhysicalDeviceFeatures2.pNext中 
	VkPhysicalDeviceShaderFloatControls2FeaturesKHR  physicalDeviceShaderFloatControls2FeaturesKHR{};
	physicalDeviceShaderFloatControls2FeaturesKHR.sType = VK_STRUCTURE_TYPE_MAX_ENUM;//没有定义这里定义为非法值
	physicalDeviceShaderFloatControls2FeaturesKHR.pNext = nullptr;
	physicalDeviceShaderFloatControls2FeaturesKHR.shaderFloatControls2 = VK_FALSE;//指明shader module是否可以声明FloatControls2 能力


	//VkPhysicalDeviceShaderEarlyAndLateFragmentTestsFeaturesAMD ， 可以包含在VkPhysicalDeviceFeatures2.pNext中 
	VkPhysicalDeviceShaderEarlyAndLateFragmentTestsFeaturesAMD  physicalDeviceShaderEarlyAndLateFragmentTestsFeaturesAMD{};
	physicalDeviceShaderEarlyAndLateFragmentTestsFeaturesAMD.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_EARLY_AND_LATE_FRAGMENT_TESTS_FEATURES_AMD;
	physicalDeviceShaderEarlyAndLateFragmentTestsFeaturesAMD.pNext = nullptr;
	physicalDeviceShaderEarlyAndLateFragmentTestsFeaturesAMD.shaderEarlyAndLateFragmentTests = VK_FALSE;//指明是否支持EarlyAndLateFragmentTestsAMD Execution Mode



	//VkPhysicalDeviceNonSeamlessCubeMapFeaturesEXT ， 可以包含在VkPhysicalDeviceFeatures2.pNext中 
	VkPhysicalDeviceNonSeamlessCubeMapFeaturesEXT  physicalDeviceNonSeamlessCubeMapFeaturesEXT{};
	physicalDeviceNonSeamlessCubeMapFeaturesEXT.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_NON_SEAMLESS_CUBE_MAP_FEATURES_EXT;
	physicalDeviceNonSeamlessCubeMapFeaturesEXT.pNext = nullptr;
	physicalDeviceNonSeamlessCubeMapFeaturesEXT.nonSeamlessCubeMap = VK_FALSE;//指明是否支持 VK_SAMPLER_CREATE_NON_SEAMLESS_CUBE_MAP_BIT_EXT


	//VkPhysicalDeviceShaderModuleIdentifierFeaturesEXT ， 可以包含在VkPhysicalDeviceFeatures2.pNext中 
	VkPhysicalDeviceShaderModuleIdentifierFeaturesEXT  physicalDeviceShaderModuleIdentifierFeaturesEXT{};
	physicalDeviceShaderModuleIdentifierFeaturesEXT.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_MODULE_IDENTIFIER_FEATURES_EXT;
	physicalDeviceShaderModuleIdentifierFeaturesEXT.pNext = nullptr;
	physicalDeviceShaderModuleIdentifierFeaturesEXT.shaderModuleIdentifier = VK_FALSE;//指明是否支持查询一个 VkShaderModule 或者 VkShaderModuleCreateInfo的标识符，然后根据该标识符创建pipeline


	//VkPhysicalDeviceTilePropertiesFeaturesQCOM ， 可以包含在VkPhysicalDeviceFeatures2.pNext中 
	VkPhysicalDeviceTilePropertiesFeaturesQCOM  physicalDeviceTilePropertiesFeaturesQCOM{};
	physicalDeviceTilePropertiesFeaturesQCOM.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_TILE_PROPERTIES_FEATURES_QCOM;
	physicalDeviceTilePropertiesFeaturesQCOM.pNext = nullptr;
	physicalDeviceTilePropertiesFeaturesQCOM.tileProperties = VK_FALSE;//指明支持返回tile properties的查询


	//VkPhysicalDeviceImageProcessingFeaturesQCOM ， 可以包含在VkPhysicalDeviceFeatures2.pNext中 
	VkPhysicalDeviceImageProcessingFeaturesQCOM  physicalDeviceImageProcessingFeaturesQCOM{};
	physicalDeviceImageProcessingFeaturesQCOM.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_IMAGE_PROCESSING_FEATURES_QCOM;
	physicalDeviceImageProcessingFeaturesQCOM.pNext = nullptr;
	physicalDeviceImageProcessingFeaturesQCOM.textureSampleWeighted = VK_FALSE;//指明shader module是否可以声明TextureSampleWeightedQCOM capability
	physicalDeviceImageProcessingFeaturesQCOM.textureBoxFilter = VK_FALSE;//指明shader module是否可以声明TextureBoxFilterQCOM capability
	physicalDeviceImageProcessingFeaturesQCOM.textureBlockMatch = VK_FALSE;//指明shader module是否可以声明TextureBlockMatchQCOM capability


	//VkPhysicalDeviceImageProcessing2FeaturesQCOM ， 可以包含在VkPhysicalDeviceFeatures2.pNext中 
	VkPhysicalDeviceImageProcessing2FeaturesQCOM  physicalDeviceImageProcessing2FeaturesQCOM{};
	physicalDeviceImageProcessing2FeaturesQCOM.sType = VK_STRUCTURE_TYPE_MAX_ENUM;//没有定义这里定义为非法值
	physicalDeviceImageProcessing2FeaturesQCOM.pNext = nullptr;
	physicalDeviceImageProcessing2FeaturesQCOM.textureBlockMatch2 = VK_FALSE;//指明shader module是否可以声明TextureBlockMatch2QCOM capability


	//VkPhysicalDeviceDepthClampZeroOneFeaturesEXT ， 可以包含在VkPhysicalDeviceFeatures2.pNext中 
	VkPhysicalDeviceDepthClampZeroOneFeaturesEXT  physicalDeviceDepthClampZeroOneFeaturesEXT{};
	physicalDeviceDepthClampZeroOneFeaturesEXT.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DEPTH_CLAMP_ZERO_ONE_FEATURES_EXT;
	physicalDeviceDepthClampZeroOneFeaturesEXT.pNext = nullptr;
	physicalDeviceDepthClampZeroOneFeaturesEXT.depthClampZeroOne = VK_FALSE;//指明支持将深度值限定到范围 0.0 - 1.0


	//VkPhysicalDeviceShaderTileImageFeaturesEXT ， 可以包含在VkPhysicalDeviceFeatures2.pNext中 
	VkPhysicalDeviceShaderTileImageFeaturesEXT  physicalDeviceShaderTileImageFeaturesEXT{};
	physicalDeviceShaderTileImageFeaturesEXT.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_TILE_IMAGE_FEATURES_EXT;
	physicalDeviceShaderTileImageFeaturesEXT.pNext = nullptr;
	physicalDeviceShaderTileImageFeaturesEXT.shaderTileImageColorReadAccess = VK_FALSE;//指明是否支持TileImageColorReadAccessEXT SPIR-V capability.
	physicalDeviceShaderTileImageFeaturesEXT.shaderTileImageDepthReadAccess = VK_FALSE;//指明是否支持TileImageDepthReadAccessEXT SPIR-V capability.
	physicalDeviceShaderTileImageFeaturesEXT.shaderTileImageStencilReadAccess = VK_FALSE;//指明是否支持TileImageStencilReadAccessEXT SPIR-V capability.


	//VkPhysicalDeviceDepthBiasControlFeaturesEXT ， 可以包含在VkPhysicalDeviceFeatures2.pNext中 
	VkPhysicalDeviceDepthBiasControlFeaturesEXT  physicalDeviceDepthBiasControlFeaturesEXT{};
	physicalDeviceDepthBiasControlFeaturesEXT.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DEPTH_BIAS_CONTROL_FEATURES_EXT;
	physicalDeviceDepthBiasControlFeaturesEXT.pNext = nullptr;
	physicalDeviceDepthBiasControlFeaturesEXT.depthBiasControl = VK_FALSE;//指明是否支持vkCmdSetDepthBias2EXT 命令以及 VkDepthBiasRepresentationInfoEXT 结构体
	physicalDeviceDepthBiasControlFeaturesEXT.leastRepresentableValueForceUnormRepresentation = VK_FALSE;//指明是否支持 VK_DEPTH_BIAS_REPRESENTATION_LEAST_REPRESENTABLE_VALUE_FORCE_UNORM_EXT depth bias representation
	physicalDeviceDepthBiasControlFeaturesEXT.floatRepresentation = VK_FALSE;//指明是否支持VK_DEPTH_BIAS_REPRESENTATION_FLOAT_EXT depth bias representation
	physicalDeviceDepthBiasControlFeaturesEXT.depthBiasExact = VK_FALSE;//指明是否支持使用VkDepthBiasRepresentationInfoEXT::depthBiasExact 强制不让depth bias不被缩放来保证最小的resolvable difference


	//VkPhysicalDeviceAddressBindingReportFeaturesEXT ， 可以包含在VkPhysicalDeviceFeatures2.pNext中 
	VkPhysicalDeviceAddressBindingReportFeaturesEXT  physicalDeviceAddressBindingReportFeaturesEXT{};
	physicalDeviceAddressBindingReportFeaturesEXT.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_ADDRESS_BINDING_REPORT_FEATURES_EXT;
	physicalDeviceAddressBindingReportFeaturesEXT.pNext = nullptr;
	physicalDeviceAddressBindingReportFeaturesEXT.reportAddressBinding = VK_FALSE;//指明是否支持报告Vulkan对象绑定的GPU虚拟地址范围


	//VkPhysicalDeviceOpticalFlowFeaturesNV ， 可以包含在VkPhysicalDeviceFeatures2.pNext中 
	VkPhysicalDeviceOpticalFlowFeaturesNV  physicalDeviceOpticalFlowFeaturesNV{};
	physicalDeviceOpticalFlowFeaturesNV.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_OPTICAL_FLOW_FEATURES_NV;
	physicalDeviceOpticalFlowFeaturesNV.pNext = nullptr;
	physicalDeviceOpticalFlowFeaturesNV.opticalFlow = VK_FALSE;//指明是否支持optical flow


	//VkPhysicalDeviceFaultFeaturesEXT ， 可以包含在VkPhysicalDeviceFeatures2.pNext中 
	VkPhysicalDeviceFaultFeaturesEXT  physicalDeviceFaultFeaturesEXT{};
	physicalDeviceFaultFeaturesEXT.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FAULT_FEATURES_EXT;
	physicalDeviceFaultFeaturesEXT.pNext = nullptr;
	physicalDeviceFaultFeaturesEXT.deviceFault = VK_FALSE;//指明是否支持报告device故障信息
	physicalDeviceFaultFeaturesEXT.deviceFaultVendorBinary = VK_FALSE;//指明是否支持生成vendor-specific binary crash dumps文件，该文件可以为vendor-specific外部工具提供额外信息


	//VkPhysicalDevicePipelineLibraryGroupHandlesFeaturesEXT ， 可以包含在VkPhysicalDeviceFeatures2.pNext中 
	VkPhysicalDevicePipelineLibraryGroupHandlesFeaturesEXT  physicalDevicePipelineLibraryGroupHandlesFeaturesEXT{};
	physicalDevicePipelineLibraryGroupHandlesFeaturesEXT.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PIPELINE_LIBRARY_GROUP_HANDLES_FEATURES_EXT;
	physicalDevicePipelineLibraryGroupHandlesFeaturesEXT.pNext = nullptr;
	physicalDevicePipelineLibraryGroupHandlesFeaturesEXT.pipelineLibraryGroupHandles = VK_FALSE;//指明是否支持直接从一个 ray tracing pipeline library 中查询group handels


	//VkPhysicalDeviceShaderObjectFeaturesEXT ， 可以包含在VkPhysicalDeviceFeatures2.pNext中 
	VkPhysicalDeviceShaderObjectFeaturesEXT  physicalDeviceShaderObjectFeaturesEXT{};
	physicalDeviceShaderObjectFeaturesEXT.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_OBJECT_FEATURES_EXT;
	physicalDeviceShaderObjectFeaturesEXT.pNext = nullptr;
	physicalDeviceShaderObjectFeaturesEXT.shaderObject = VK_FALSE;//指明是否支持 shader objects


	//VkPhysicalDeviceShaderCoreBuiltinsFeaturesARM ， 可以包含在VkPhysicalDeviceFeatures2.pNext中 
	VkPhysicalDeviceShaderCoreBuiltinsFeaturesARM  physicalDeviceShaderCoreBuiltinsFeaturesARM{};
	physicalDeviceShaderCoreBuiltinsFeaturesARM.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_CORE_BUILTINS_FEATURES_ARM;
	physicalDeviceShaderCoreBuiltinsFeaturesARM.pNext = nullptr;
	physicalDeviceShaderCoreBuiltinsFeaturesARM.shaderCoreBuiltins = VK_FALSE;//指明是否支持 SPIR-V CoreBuiltinsARM capability


	//VkPhysicalDeviceFrameBoundaryFeaturesEXT ， 可以包含在VkPhysicalDeviceFeatures2.pNext中 
	VkPhysicalDeviceFrameBoundaryFeaturesEXT  physicalDeviceFrameBoundaryFeaturesEXT{};
	physicalDeviceFrameBoundaryFeaturesEXT.sType = VK_STRUCTURE_TYPE_MAX_ENUM;//没有定义这里设置为非法值
	physicalDeviceFrameBoundaryFeaturesEXT.pNext = nullptr;
	physicalDeviceFrameBoundaryFeaturesEXT.frameBoundary = VK_FALSE;//指明是否支持帧边界信息


	//VkPhysicalDeviceSwapchainMaintenance1FeaturesEXT ， 可以包含在VkPhysicalDeviceFeatures2.pNext中 
	VkPhysicalDeviceSwapchainMaintenance1FeaturesEXT  physicalDeviceSwapchainMaintenance1FeaturesEXT{};
	physicalDeviceSwapchainMaintenance1FeaturesEXT.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SWAPCHAIN_MAINTENANCE_1_FEATURES_EXT;
	physicalDeviceSwapchainMaintenance1FeaturesEXT.pNext = nullptr;
	physicalDeviceSwapchainMaintenance1FeaturesEXT.swapchainMaintenance1 = VK_FALSE;//具体支持什么参见p3883


	//VkPhysicalDeviceDynamicRenderingUnusedAttachmentsFeaturesEXT ， 可以包含在VkPhysicalDeviceFeatures2.pNext中 
	VkPhysicalDeviceDynamicRenderingUnusedAttachmentsFeaturesEXT  physicalDeviceDynamicRenderingUnusedAttachmentsFeaturesEXT{};
	physicalDeviceDynamicRenderingUnusedAttachmentsFeaturesEXT.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DYNAMIC_RENDERING_UNUSED_ATTACHMENTS_FEATURES_EXT;
	physicalDeviceDynamicRenderingUnusedAttachmentsFeaturesEXT.pNext = nullptr;
	physicalDeviceDynamicRenderingUnusedAttachmentsFeaturesEXT.dynamicRenderingUnusedAttachments = VK_FALSE;//简单将就是指明是否支持绑定的pipeline的format不为VK_FORMAT_UNDEFIED的 color ，depth 以及stencile attachment指定一个VK_NULL_HANDLE的imae view或者为format为VK_FORMAT_UNDEFINED 指定一个不为VK_NULL_HANDLE的image view


	//VkPhysicalDeviceRayTracingInvocationReorderFeaturesNV ， 可以包含在VkPhysicalDeviceFeatures2.pNext中 
	VkPhysicalDeviceRayTracingInvocationReorderFeaturesNV  physicalDeviceRayTracingInvocationReorderFeaturesNV{};
	physicalDeviceRayTracingInvocationReorderFeaturesNV.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_RAY_TRACING_INVOCATION_REORDER_FEATURES_NV;
	physicalDeviceRayTracingInvocationReorderFeaturesNV.pNext = nullptr;
	physicalDeviceRayTracingInvocationReorderFeaturesNV.rayTracingInvocationReorder = VK_FALSE;//指定是否支持SPV_NV_shader_invocation_reorder 拓展


	//VkPhysicalDeviceExtendedSparseAddressSpaceFeaturesNV ， 可以包含在VkPhysicalDeviceFeatures2.pNext中 
	VkPhysicalDeviceExtendedSparseAddressSpaceFeaturesNV  physicalDeviceExtendedSparseAddressSpaceFeaturesNV{};
	physicalDeviceExtendedSparseAddressSpaceFeaturesNV.sType = VK_STRUCTURE_TYPE_MAX_ENUM;//没有定义这里定义为非法值
	physicalDeviceExtendedSparseAddressSpaceFeaturesNV.pNext = nullptr;
	physicalDeviceExtendedSparseAddressSpaceFeaturesNV.extendedSparseAddressSpace = VK_FALSE;//指定是否支持特定用法的sparse memory resources大小超过VkPhysicalDeviceLimits::sparseAddressSpaceSize，见VkPhysicalDeviceExtendedSparseAddressSpacePropertiesNV p3994


	//VkPhysicalDeviceMultiviewPerViewViewportsFeaturesQCOM ， 可以包含在VkPhysicalDeviceFeatures2.pNext中 
	VkPhysicalDeviceMultiviewPerViewViewportsFeaturesQCOM  physicalDeviceMultiviewPerViewViewportsFeaturesQCOM{};
	physicalDeviceMultiviewPerViewViewportsFeaturesQCOM.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MULTIVIEW_PER_VIEW_VIEWPORTS_FEATURES_QCOM;
	physicalDeviceMultiviewPerViewViewportsFeaturesQCOM.pNext = nullptr;
	physicalDeviceMultiviewPerViewViewportsFeaturesQCOM.multiviewPerViewViewports = VK_FALSE;//指明是否支持multiview per-view viewports


	//VkPhysicalDeviceMultiviewPerViewRenderAreasFeaturesQCOM ， 可以包含在VkPhysicalDeviceFeatures2.pNext中 
	VkPhysicalDeviceMultiviewPerViewRenderAreasFeaturesQCOM  physicalDeviceMultiviewPerViewRenderAreasFeaturesQCOM{};
	physicalDeviceMultiviewPerViewRenderAreasFeaturesQCOM.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MULTIVIEW_PER_VIEW_RENDER_AREAS_FEATURES_QCOM;
	physicalDeviceMultiviewPerViewRenderAreasFeaturesQCOM.pNext = nullptr;
	physicalDeviceMultiviewPerViewRenderAreasFeaturesQCOM.multiviewPerViewRenderAreas = VK_FALSE;//指明是否支持multiview per-view render areas


	//VkPhysicalDeviceClusterCullingShaderFeaturesHUAWEI ， 可以包含在VkPhysicalDeviceFeatures2.pNext中 
	VkPhysicalDeviceClusterCullingShaderFeaturesHUAWEI  physicalDeviceClusterCullingShaderFeaturesHUAWEI{};
	physicalDeviceClusterCullingShaderFeaturesHUAWEI.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_CLUSTER_CULLING_SHADER_FEATURES_HUAWEI;
	physicalDeviceClusterCullingShaderFeaturesHUAWEI.pNext = nullptr;
	physicalDeviceClusterCullingShaderFeaturesHUAWEI.clustercullingShader = VK_FALSE;//指明是否支持 cluster culling shader
	physicalDeviceClusterCullingShaderFeaturesHUAWEI.multiviewClusterCullingShader = VK_FALSE;//指明是否支持 multiview


	//VkPhysicalDeviceClusterCullingShaderVrsFeaturesHUAWEI ， 可以包含在VkPhysicalDeviceClusterCullingShaderFeaturesHUAWEI.pNext中 
	VkPhysicalDeviceClusterCullingShaderVrsFeaturesHUAWEI  physicalDeviceClusterCullingShaderVrsFeaturesHUAWEI{};
	physicalDeviceClusterCullingShaderVrsFeaturesHUAWEI.sType = VK_STRUCTURE_TYPE_MAX_ENUM;//没有定义这里定义为非法值
	physicalDeviceClusterCullingShaderVrsFeaturesHUAWEI.pNext = nullptr;
	physicalDeviceClusterCullingShaderVrsFeaturesHUAWEI.clusterShadingRate = VK_FALSE;//指明是否支持 per-cluster shading rates
	

	//VkPhysicalDeviceShaderEnqueueFeaturesAMDX ， 可以包含在VkPhysicalDeviceFeatures2.pNext中 
	VkPhysicalDeviceShaderEnqueueFeaturesAMDX  physicalDeviceShaderEnqueueFeaturesAMDX{};
	physicalDeviceShaderEnqueueFeaturesAMDX.sType = VK_STRUCTURE_TYPE_MAX_ENUM;//没有定义这里定义为非法值
	physicalDeviceShaderEnqueueFeaturesAMDX.pNext = nullptr;
	physicalDeviceShaderEnqueueFeaturesAMDX.shaderEnqueue = VK_FALSE;//指明是否支持execution graphs


	//VkPhysicalDeviceCubicClampFeaturesQCOM ， 可以包含在VkPhysicalDeviceFeatures2.pNext中 
	VkPhysicalDeviceCubicClampFeaturesQCOM  physicalDeviceCubicClampFeaturesQCOM{};
	physicalDeviceCubicClampFeaturesQCOM.sType = VK_STRUCTURE_TYPE_MAX_ENUM;//没有定义这里定义为非法值
	physicalDeviceCubicClampFeaturesQCOM.pNext = nullptr;
	physicalDeviceCubicClampFeaturesQCOM.cubicRangeClamp = VK_FALSE;//指定是否支持和一个 texel range clamp组合的cubic filtering


	//VkPhysicalDeviceYcbcrDegammaFeaturesQCOM ， 可以包含在VkPhysicalDeviceFeatures2.pNext中 
	VkPhysicalDeviceYcbcrDegammaFeaturesQCOM  physicalDeviceYcbcrDegammaFeaturesQCOM{};
	physicalDeviceYcbcrDegammaFeaturesQCOM.sType = VK_STRUCTURE_TYPE_MAX_ENUM;//没有定义这里定义为非法值
	physicalDeviceYcbcrDegammaFeaturesQCOM.pNext = nullptr;
	physicalDeviceYcbcrDegammaFeaturesQCOM.ycbcrDegamma = VK_FALSE;//指明是否支持 Y′CBCR degamma p1486


	//VkPhysicalDeviceCubicWeightsFeaturesQCOM ， 可以包含在VkPhysicalDeviceFeatures2.pNext中 
	VkPhysicalDeviceCubicWeightsFeaturesQCOM  physicalDeviceCubicWeightsFeaturesQCOM{};
	physicalDeviceCubicWeightsFeaturesQCOM.sType = VK_STRUCTURE_TYPE_MAX_ENUM;//没有定义这里定义为非法值
	physicalDeviceCubicWeightsFeaturesQCOM.pNext = nullptr;
	physicalDeviceCubicWeightsFeaturesQCOM.selectableCubicWeights = VK_FALSE;//指明是否支持filter cubic weights的选取


	//VkPhysicalDeviceDescriptorPoolOverallocationFeaturesNV ， 可以包含在VkPhysicalDeviceFeatures2.pNext中 
	VkPhysicalDeviceDescriptorPoolOverallocationFeaturesNV  physicalDeviceDescriptorPoolOverallocationFeaturesNV{};
	physicalDeviceDescriptorPoolOverallocationFeaturesNV.sType = VK_STRUCTURE_TYPE_MAX_ENUM;//没有定义这里定义为非法值
	physicalDeviceDescriptorPoolOverallocationFeaturesNV.pNext = nullptr;
	physicalDeviceDescriptorPoolOverallocationFeaturesNV.descriptorPoolOverallocation = VK_FALSE;//指明是否允许应用选择设置VK_DESCRIPTOR_POOL_CREATE_ALLOW_OVERALLOCATION_SETS_BIT_NV 以及/或者 VK_DESCRIPTOR_POOL_CREATE_ALLOW_OVERALLOCATION_POOLS_BIT_NV对descriptor pool进行过分配


	//VkPhysicalDevicePerStageDescriptorSetFeaturesNV ， 可以包含在VkPhysicalDeviceFeatures2.pNext中 
	VkPhysicalDevicePerStageDescriptorSetFeaturesNV  physicalDevicePerStageDescriptorSetFeaturesNV{};
	physicalDevicePerStageDescriptorSetFeaturesNV.sType = VK_STRUCTURE_TYPE_MAX_ENUM;//没有定义这里定义为非法值
	physicalDevicePerStageDescriptorSetFeaturesNV.pNext = nullptr;
	physicalDevicePerStageDescriptorSetFeaturesNV.perStageDescriptorSet = VK_FALSE;//指明是否允许使用VK_DESCRIPTOR_SET_LAYOUT_CREATE_PER_STAGE_BIT_NV 标志创建descriptor set layout，这也指明descriptor set layout的绑定是per-stage的而不是对所有stages的
	physicalDevicePerStageDescriptorSetFeaturesNV.dynamicPipelineLayout = VK_FALSE;//指明是否允许VkBindDescriptorSetsInfoKHR, VkPushConstantsInfoKHR, VkPushDescriptorSetInfoKHR, VkPushDescriptorSetWithTemplateInfoKHR, VkSetDescriptorBufferOffsetsInfoEXT 以及VkBindDescriptorBufferEmbeddedSamplersInfoEXT的layout为VK_NULL_HANDLE，而这些结构体的pNext中包含VkPipelineLayoutCreateInfo来指定layout信息


	//VkPhysicalDeviceCudaKernelLaunchFeaturesNV ， 可以包含在VkPhysicalDeviceFeatures2.pNext中 
	VkPhysicalDeviceCudaKernelLaunchFeaturesNV  physicalDeviceCudaKernelLaunchFeaturesNV{};
	physicalDeviceCudaKernelLaunchFeaturesNV.sType = VK_STRUCTURE_TYPE_MAX_ENUM;//没有定义这里定义为非法值
	physicalDeviceCudaKernelLaunchFeaturesNV.pNext = nullptr;
	physicalDeviceCudaKernelLaunchFeaturesNV.cudaKernelLaunchFeatures = VK_FALSE;//指明是否支持cuda kernel launch


	//VkPhysicalDeviceShaderMaximalReconvergenceFeaturesKHR ， 可以包含在VkPhysicalDeviceFeatures2.pNext中 
	VkPhysicalDeviceShaderMaximalReconvergenceFeaturesKHR  physicalDeviceShaderMaximalReconvergenceFeaturesKHR{};
	physicalDeviceShaderMaximalReconvergenceFeaturesKHR.sType = VK_STRUCTURE_TYPE_MAX_ENUM;//没有定义这里定义为非法值
	physicalDeviceShaderMaximalReconvergenceFeaturesKHR.pNext = nullptr;
	physicalDeviceShaderMaximalReconvergenceFeaturesKHR.shaderMaximalReconvergence = VK_FALSE;//指明是否支持shader execution mode MaximallyReconvergesKHR


	//VkPhysicalDeviceExternalFormatResolveFeaturesANDROID ， 可以包含在VkPhysicalDeviceFeatures2.pNext中 
	VkPhysicalDeviceExternalFormatResolveFeaturesANDROID  physicalDeviceExternalFormatResolveFeaturesANDROID{};
	physicalDeviceExternalFormatResolveFeaturesANDROID.sType = VK_STRUCTURE_TYPE_MAX_ENUM;//没有定义这里定义为非法值
	physicalDeviceExternalFormatResolveFeaturesANDROID.pNext = nullptr;
	physicalDeviceExternalFormatResolveFeaturesANDROID.externalFormatResolve = VK_FALSE;//指明是否支持 external format resolves


	//VkPhysicalDeviceSchedulingControlsFeaturesARM ， 可以包含在VkPhysicalDeviceFeatures2.pNext中 
	VkPhysicalDeviceSchedulingControlsFeaturesARM  physicalDeviceSchedulingControlsFeaturesARM{};
	physicalDeviceSchedulingControlsFeaturesARM.sType = VK_STRUCTURE_TYPE_MAX_ENUM;//没有定义这里定义为非法值
	physicalDeviceSchedulingControlsFeaturesARM.pNext = nullptr;
	physicalDeviceSchedulingControlsFeaturesARM.schedulingControls = VK_FALSE;//指明是否支持scheduling controls


	//VkPhysicalDeviceRelaxedLineRasterizationFeaturesIMG ， 可以包含在VkPhysicalDeviceFeatures2.pNext中 
	VkPhysicalDeviceRelaxedLineRasterizationFeaturesIMG  physicalDeviceRelaxedLineRasterizationFeaturesIMG{};
	physicalDeviceRelaxedLineRasterizationFeaturesIMG.sType = VK_STRUCTURE_TYPE_MAX_ENUM;//没有定义这里定义为非法值
	physicalDeviceRelaxedLineRasterizationFeaturesIMG.pNext = nullptr;
	physicalDeviceRelaxedLineRasterizationFeaturesIMG.relaxedLineRasterization = VK_FALSE;//指明是否支持relaxed line rasterization control


	//VkPhysicalDeviceRenderPassStripedFeaturesARM ， 可以包含在VkPhysicalDeviceFeatures2.pNext中 
	VkPhysicalDeviceRenderPassStripedFeaturesARM  physicalDeviceRenderPassStripedFeaturesARM{};
	physicalDeviceRenderPassStripedFeaturesARM.sType = VK_STRUCTURE_TYPE_MAX_ENUM;//没有定义这里定义为非法值
	physicalDeviceRenderPassStripedFeaturesARM.pNext = nullptr;
	physicalDeviceRenderPassStripedFeaturesARM.renderPassStriped = VK_FALSE;//指明是否支持striped rendering


	//VkPhysicalDeviceShaderSubgroupRotateFeaturesKHR ， 可以包含在VkPhysicalDeviceFeatures2.pNext中 
	VkPhysicalDeviceShaderSubgroupRotateFeaturesKHR  physicalDeviceShaderSubgroupRotateFeaturesKHR{};
	physicalDeviceShaderSubgroupRotateFeaturesKHR.sType = VK_STRUCTURE_TYPE_MAX_ENUM;//没有定义这里定义为非法值
	physicalDeviceShaderSubgroupRotateFeaturesKHR.pNext = nullptr;
	physicalDeviceShaderSubgroupRotateFeaturesKHR.shaderSubgroupRotate = VK_FALSE;//指明是否shader module可以声明GroupNonUniformRotateKHR capability
	physicalDeviceShaderSubgroupRotateFeaturesKHR.shaderSubgroupRotateClustered = VK_FALSE;//指明是否shader module可以使用GroupNonUniformRotateKHR的操作符ClusterSize


	//VkPhysicalDeviceShaderExpectAssumeFeaturesKHR ， 可以包含在VkPhysicalDeviceFeatures2.pNext中 
	VkPhysicalDeviceShaderExpectAssumeFeaturesKHR  physicalDeviceShaderExpectAssumeFeaturesKHR{};
	physicalDeviceShaderExpectAssumeFeaturesKHR.sType = VK_STRUCTURE_TYPE_MAX_ENUM;//没有定义这里定义为非法值
	physicalDeviceShaderExpectAssumeFeaturesKHR.pNext = nullptr;
	physicalDeviceShaderExpectAssumeFeaturesKHR.shaderExpectAssume = VK_FALSE;//指明是否shader module可以声明ExpectAssumeKHR capability


	//VkPhysicalDeviceDynamicRenderingLocalReadFeaturesKHR ， 可以包含在VkPhysicalDeviceFeatures2.pNext中 
	VkPhysicalDeviceDynamicRenderingLocalReadFeaturesKHR  physicalDeviceDynamicRenderingLocalReadFeaturesKHR{};
	physicalDeviceDynamicRenderingLocalReadFeaturesKHR.sType = VK_STRUCTURE_TYPE_MAX_ENUM;//没有定义这里定义为非法值
	physicalDeviceDynamicRenderingLocalReadFeaturesKHR.pNext = nullptr;
	physicalDeviceDynamicRenderingLocalReadFeaturesKHR.dynamicRenderingLocalRead = VK_FALSE;//指明是否在使用 vkCmdBeginRendering开始的动态render pass 实例中支持local reads 


	//VkPhysicalDeviceShaderQuadControlFeaturesKHR ， 可以包含在VkPhysicalDeviceFeatures2.pNext中 
	VkPhysicalDeviceShaderQuadControlFeaturesKHR  physicalDeviceShaderQuadControlFeaturesKHR{};
	physicalDeviceShaderQuadControlFeaturesKHR.sType = VK_STRUCTURE_TYPE_MAX_ENUM;//没有定义这里定义为非法值
	physicalDeviceShaderQuadControlFeaturesKHR.pNext = nullptr;
	physicalDeviceShaderQuadControlFeaturesKHR.shaderQuadControl = VK_FALSE;//指明是否支持shader能有QuadControlKHR capability



	//VkPhysicalDeviceMapMemoryPlacedFeaturesEXT ， 可以包含在VkPhysicalDeviceFeatures2.pNext中 
	VkPhysicalDeviceMapMemoryPlacedFeaturesEXT  physicalDeviceMapMemoryPlacedFeaturesEXT{};
	physicalDeviceMapMemoryPlacedFeaturesEXT.sType = VK_STRUCTURE_TYPE_MAX_ENUM;//没有定义这里定义为非法值
	physicalDeviceMapMemoryPlacedFeaturesEXT.pNext = nullptr;
	physicalDeviceMapMemoryPlacedFeaturesEXT.memoryMapPlaced = VK_FALSE;//指明是否支持将内存映射放置在host端的指定的虚拟内存上
	physicalDeviceMapMemoryPlacedFeaturesEXT.memoryMapRangePlaced = VK_FALSE;//指明是否支持将一个对象的子内存范围的内存映射放置在host端的指定的虚拟内存上
	physicalDeviceMapMemoryPlacedFeaturesEXT.memoryUnmapReserve = VK_FALSE;//指明是否支持当unmapping一个对象的时候保留其内存范围


	//VkPhysicalDeviceShaderAtomicFloat16VectorFeaturesNV ， 可以包含在VkPhysicalDeviceFeatures2.pNext中 
	VkPhysicalDeviceShaderAtomicFloat16VectorFeaturesNV  physicalDeviceShaderAtomicFloat16VectorFeaturesNV{};
	physicalDeviceShaderAtomicFloat16VectorFeaturesNV.sType = VK_STRUCTURE_TYPE_MAX_ENUM;//没有定义这里定义为非法值
	physicalDeviceShaderAtomicFloat16VectorFeaturesNV.pNext = nullptr;
	physicalDeviceShaderAtomicFloat16VectorFeaturesNV.shaderFloat16VectorAtomics = VK_FALSE;//指明是否支持16-bit浮点数以及2个到4个分量vector的原子操作


	//VkPhysicalDeviceRawAccessChainsFeaturesNV ， 可以包含在VkPhysicalDeviceFeatures2.pNext中 
	VkPhysicalDeviceRawAccessChainsFeaturesNV  physicalDeviceRawAccessChainsFeaturesNV{};
	physicalDeviceRawAccessChainsFeaturesNV.sType = VK_STRUCTURE_TYPE_MAX_ENUM;//没有定义这里定义为非法值
	physicalDeviceRawAccessChainsFeaturesNV.pNext = nullptr;
	physicalDeviceRawAccessChainsFeaturesNV.shaderRawAccessChains = VK_FALSE;//指明是否shader module可以声明RawAccessChainsNV capability


	//VkPhysicalDeviceImageAlignmentControlFeaturesMESA ， 可以包含在VkPhysicalDeviceFeatures2.pNext中 
	VkPhysicalDeviceImageAlignmentControlFeaturesMESA  physicalDeviceImageAlignmentControlFeaturesMESA{};
	physicalDeviceImageAlignmentControlFeaturesMESA.sType = VK_STRUCTURE_TYPE_MAX_ENUM;//没有定义这里定义为非法值
	physicalDeviceImageAlignmentControlFeaturesMESA.pNext = nullptr;
	physicalDeviceImageAlignmentControlFeaturesMESA.imageAlignmentControl = VK_FALSE;//指明是否支持 VkImageCreateInfo.pNext中包含 VkImageAlignmentControlCreateInfoMESA




	//----------------------------------------------------------------------------


	//Feature Requirements   在满足一定条件下，所有vulkan实现都必须要支持的特性详情  参见p3899 - p3907 ***


	//Profile Features  支持 Roadmap 2022 profile的vulkan实现必须支持的特性详情   参见 p3907 - p3908 ;支持 Roadmap 2024 profile的vulkan实现必须支持的特性详情   参见 p3908





}












NS_TEST_END