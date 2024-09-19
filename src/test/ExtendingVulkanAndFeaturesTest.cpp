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
	//�µĺ�������ͨ���µ���չ�������µ��ں˰汾���Լ���չ���µİ汾��ӵ�vulkan

	//Instance and Device Functionality  �μ�p3713
	{
		/*
		ö��instance���Ի��߽���instanceΪ�����ĺ���Ϊinstance-level functionality.

		��device�������Ӷ����ɷ��ģ����߽���deviceΪ�����ĺ���Ϊdevice-level functionality.

		��VkPhysicalDevice�ɷ����߽���VkPhysicalDevice�ĺ�����instance-level����device-level functionality ȡ�����Ƿ�ָ��һ��instance extension����device extension�����⣬�о��豸���Ե���Ϊ��device-level functionality 
		
		*/


	}

	// Core Versions  �μ�p3713
	{
		// Version Numbers  �μ�p3714
		{
			/*
			vulkan �汾�����Ĳ��ֹ���: variant, major, minor �Լ� patch �汾
			
			variant �汾: ָ��ʵ��֧�ֵ�vulkan API�ı���汾����vulkan API��˵��ԶΪ0
			major �汾: ��ʾAPI�е�һ���ش�仯����������һ��ȫ�µĹ淶�汾
			minor �汾: ָ���ں��Ĺ淶�м������µĹ���
			patch �汾: ָ����ʾ�淶�а����˴����޸�����������ԸĽ�

			vulkan����İ汾���ܹ�32bit�����и�ʽΪ��ǰ���󣬴Ӹ�λ����λ: variant��3bit��, major��7bit��, minor��10bit�� �Լ� patch ��12bit��,��δӴ���İ汾������ȡ��Ӧ�İ汾��vulkan������һЩ��ȡ���� VK_VERSION_PATCH �������p3715
			
			vulkan������һЩָ���ض�vulkan �汾�ĺ��� VK_API_VERSION_1_0 ���μ�p3716
			*/



		}

		//Querying Version Support  �μ�p3717
		{
			// instance-level functionality�İ汾��ѯ
			uint32_t apiVersion = 0;
			vkEnumerateInstanceVersion(&apiVersion);


			// device-level functionality�İ汾��ѯ
			VkPhysicalDeviceProperties properties;
			vkGetPhysicalDeviceProperties(physicalDevice, &properties);
			properties.apiVersion;//���ز�ѯ֧�ֵ�api�汾
			
			VkPhysicalDeviceProperties2 properties2;
			vkGetPhysicalDeviceProperties2(physicalDevice, &properties2);
			properties2.properties.apiVersion;//���ز�ѯ֧�ֵ�api�汾
		}
	}


	//Layers  �μ�p3717
	{
		/*
		��һ��layer����ʱ����layer����Լ����뵽��Ӧ��vulkan��������ĵ������У�����չ���������Ϊ��������־��׷�٣�У���Լ��ṩ������չ�ȹ���
		*/
	
		//��ѯ���õ�layers
		uint32_t numLayer = 0;
		std::vector<VkLayerProperties> layerProperties;
		vkEnumerateInstanceLayerProperties(&numLayer, nullptr);
		layerProperties.resize(numLayer);
		vkEnumerateInstanceLayerProperties(&numLayer, layerProperties.data());//����ɹ�������һ��Ԫ��

		VkLayerProperties& layerProp = layerProperties[0];
		layerProp.layerName/*char [VK_MAX_EXTENSION_NAME_SIZE]���ͣ�VK_MAX_EXTENSION_NAME_SIZE = 256U*/;//Ϊ��layer�� null-terminated UTF-8���͵����ƣ��ɴ��� VkInstanceCreateInfo.ppEnabledLayerNames ��ָ��instanceҪ������layer����һЩlayer����ʽ�����ģ����ﲻ��Ҫָ��
		layerProp.specVersion = 0;//Ϊ��layerд���ĸ�vulkan�汾
		layerProp.implementationVersion = 0;//Ϊ��layer�Լ��İ汾������
		layerProp.description/*char [VK_MAX_DESCRIPTION_SIZE]���ͣ�VK_MAX_DESCRIPTION_SIZE = 256U*/;//Ϊ��layer�� null-terminated UTF-8���͵��������ṩ�������Ϣָ����layer


		// Device Layer Deprecation  �μ�p3719
		{
			/*
			���ڰ汾����layerΪinstance layer���� device layer����Щlayerֻ�ܺͶ�Ӧ�Ķ��󽻻������ڰ汾�������֡�
			*/

			//Ϊ�˼������ڵİ汾����ȡdevice��layer ����
			uint32_t numDeviceLayer = 0;
			std::vector<VkLayerProperties> deviceLayerProperties;
			vkEnumerateDeviceLayerProperties(physicalDevice, &numDeviceLayer, nullptr);
			deviceLayerProperties.resize(numDeviceLayer);
			vkEnumerateDeviceLayerProperties(physicalDevice, &numDeviceLayer, deviceLayerProperties.data());//���صĽ����vkEnumerateInstanceLayerProperties һ�������صĲ�������VkDeviceCreateInfo�е�ppEnabledLayerNames�Լ� enabledLayerCount��ʹ�ã�����������ʵ���Ϸ������ˣ�����Ч��
			


		}


	}


	// Extensions  �μ�p3721
	{
		/*
		extensions ���ܻᶨ���µ�vulkan��������ṹ�壬ö�ٵȡ�Ϊ�˱���Ŀ�ģ��Ѿ�ע���extensions�������Լ����ݽṹ�Ȼ��о���vulkan_core.h�У�extensions�ĵ��������ͨ����̬���ӣ���Ҫ��̬���ء�

		extension����չ���߸ı�Vulkan API����Ϊ��extensionӦ��Ҫ֧��vulkan��layers
		
		������VkInstanceCreateInfo.ppEnabledExtensionNames��ָ��extension����������instance extension�������� VkDeviceCreateInfo.ppEnabledExtensionNames��ָ��extension����������device extension
		
		����extensions���ı�����vulkan API����Ϊ��������extensions����Ϊ��ֻ���ø�extension��صĽӿڣ��ṹ�����Ч��
		*/


		// Instance Extensions  �μ�p3722
		{
			//Instance extensions ����µ� instance-level functionality��API��������ӵ�core��

			//��ѯ���õ�instance extensions
			uint32_t numExtension = 0;
			std::vector<VkExtensionProperties> extensionProperties{};

			//�о�Vulkanʵ�ֻ�����ʽ������layers�ṩ��extensions
			vkEnumerateInstanceExtensionProperties(nullptr, &numExtension, nullptr);
			extensionProperties.resize(numExtension);
			vkEnumerateInstanceExtensionProperties(nullptr, &numExtension, extensionProperties.data());//����ɹ�������һ��Ԫ��

			VkExtensionProperties &extensionProp = extensionProperties[0];
			extensionProp.specVersion = 0;//Ϊ��extension�Լ��İ汾������
			extensionProp.extensionName/*char [VK_MAX_EXTENSION_NAME_SIZE]���ͣ�VK_MAX_EXTENSION_NAME_SIZE = 256U*/;//Ϊ��extension�� null-terminated UTF-8���͵�����



			char layerName[5];//��������һ����Ч��layer name
			//�о�ָ��layer�ṩ��extensions
			vkEnumerateInstanceExtensionProperties(layerName, &numExtension, nullptr);
			extensionProperties.resize(numExtension);
			vkEnumerateInstanceExtensionProperties(layerName, &numExtension, extensionProperties.data());

		}

		//Device Extensions  �μ�p3723
		{
			//Device extensions ����µ� device-level functionality��API��������ӵ�core��

			//��ѯ���õ�device extensions

			uint32_t numDeviceExtension = 0;
			std::vector<VkExtensionProperties> deviceExtensionProperties{};

			//�о�Vulkanʵ�ֻ�����ʽ������layers�ṩ��extensions
			vkEnumerateDeviceExtensionProperties(physicalDevice,nullptr, &numDeviceExtension, nullptr);
			deviceExtensionProperties.resize(numDeviceExtension);
			vkEnumerateDeviceExtensionProperties(physicalDevice,nullptr, &numDeviceExtension, deviceExtensionProperties.data());

			char layerName[5];//��������һ����Ч��layer name
			//�о�ָ��layer�ṩ��extensions
			vkEnumerateDeviceExtensionProperties(physicalDevice,layerName, &numDeviceExtension, nullptr);
			deviceExtensionProperties.resize(numDeviceExtension);
			vkEnumerateDeviceExtensionProperties(physicalDevice,layerName, &numDeviceExtension, deviceExtensionProperties.data());

		}

	}



	//Extension Dependencies  �μ�p3726
	{
		/*
		һЩextensions���ڴӺ������������extension����ָ����vulkan�汾�������ڿ�����extensions֮ǰ����Ҫ������������extensions�Լ�ʹ�ö�Ӧ�汾��
		*/
	}


	//Compatibility Guarantees (Informative)  �μ�p3726
	{
		//Core Versions  ��Ҫ�����汾�ĸ������ְ���ʲô������е�����  �μ�p3726
		

		//Extensions    ��Ҫ�������뱣֤��Щextensions���Ժ���Щextensionsһ��ʹ���Լ�һЩ��ļ��ݹ���,  �μ�p3728  �� vk.xml ��������extensions��һЩ�����Ϣ


	}
}

void ExtendingVulkanAndFeatuesTest::FeaturesTest()
{
	/*
	Features�����˲�������ʵ�ֶ�֧�ֵĹ��ܡ��������豸�����ԣ����ǿ�ѡ�ģ�ʹ��ǰ������ʽ������
	*/




	//��ѯ֧�ֵ�features  �μ�p3731
	VkPhysicalDeviceFeatures physicalDeviceFeatures{};
	vkGetPhysicalDeviceFeatures(physicalDevice, &physicalDeviceFeatures);//����ɹ������˽��
	physicalDeviceFeatures.robustBufferAccess = VK_FALSE;//ָ���Ƿ��buffer descriptor��buffer�ķ���Ҫ���б߽��⣬��֤�����߽�ķ��ز��ᵼ��������ֹ�������߽�ķ��ʵľ��崦���ʩ��p3735 - p3737
	physicalDeviceFeatures.fullDrawIndexUint32 = VK_FALSE;//ָ����������������ʱʹ�� VkIndexType ΪVK_INDEX_TYPE_UINT32�Ƿ�֧��ȫ��32-bit�Ķ��������������������������ֵmaxDrawIndexedIndexValue ��Ϊpow(2,32)-1
	physicalDeviceFeatures.imageCubeArray = VK_FALSE;//ָ���Ƿ���Դ���VK_IMAGE_VIEW_TYPE_CUBE_ARRAY���͵�image view�Լ����Ӧ��SampledCubeArray �Լ� ImageCubeArray �Ƿ��������ɫ��������ʹ��
	physicalDeviceFeatures.independentBlend = VK_FALSE;//ָ��ÿ��������VkPipelineColorBlendAttachmentState �Ƿ���Ե�������
	physicalDeviceFeatures.geometryShader = VK_FALSE;//ָ���Ƿ�֧��geometry shaders�����Ƿ����ʹ�� VK_SHADER_STAGE_GEOMETRY_BIT �Լ� VK_PIPELINE_STAGE_GEOMETRY_SHADER_BIT
	physicalDeviceFeatures.tessellationShader = VK_FALSE;//ָ���Ƿ�֧��tessellation control �Լ� evaluation shaders�����Ƿ����ʹ��VK_SHADER_STAGE_TESSELLATION_CONTROL_BIT, VK_SHADER_STAGE_TESSELLATION_EVALUATION_BIT, VK_PIPELINE_STAGE_TESSELLATION_CONTROL_SHADER_BIT, VK_PIPELINE_STAGE_TESSELLATION_EVALUATION_SHADER_BIT, �Լ� VK_STRUCTURE_TYPE_PIPELINE_TESSELLATION_STATE_CREATE_INFO
	physicalDeviceFeatures.sampleRateShading = VK_FALSE;//ָ���Ƿ�֧��Sample Shading �Լ�multisample ��ֵ�������֧����VkPipelineMultisampleStateCreateInfo��sampleShadingEnable����ΪVK_FALSE��������minSampleShading
	physicalDeviceFeatures.dualSrcBlend = VK_FALSE;//ָ���Ƿ�֧��blend operationsʹ������source�����Ƿ����ʹ��e VK_BLEND_FACTOR_SRC1_COLOR, VK_BLEND_FACTOR_ONE_MINUS_SRC1_COLOR, VK_BLEND_FACTOR_SRC1_ALPHA, �Լ� VK_BLEND_FACTOR_ONE_MINUS_SRC1_ALPHA
	physicalDeviceFeatures.logicOp = VK_FALSE;;//ָ���Ƿ�֧��logic operations�������֧���� VkPipelineColorBlendStateCreateInfo��logicOpEnable����ΪVK_FALSE�������� logicOp
	physicalDeviceFeatures.multiDrawIndirect = VK_FALSE;//ָ���Ƿ�֧��multiple draw indirect�������֧�� ��vkCmdDrawIndirect �Լ� vkCmdDrawIndexedIndirect�� drawCount����ֻ��Ϊ0����1
	physicalDeviceFeatures.drawIndirectFirstInstance = VK_FALSE;//ָ���Ƿ�indirect drawing����֧��firstInstance �����������֧�֣���������õ�firstInstance����Ϊ0
	physicalDeviceFeatures.depthClamp = VK_FALSE;//ָ���Ƿ�֧��depth clamping�����֧�֣�������� VkPipelineRasterizationStateCreateInfo.depthClampEnable����ΪVK_TRUE����depth clamping
	physicalDeviceFeatures.depthBiasClamp = VK_FALSE;//ָ���Ƿ�֧��depth bias clamping�������֧����VkPipelineRasterizationStateCreateInfo�� ���� vkCmdSetDepthBias���õ�depthBiasClamp����Ϊ0
	physicalDeviceFeatures.fillModeNonSolid = VK_FALSE;//ָ���Ƿ�֧��point �Լ� wireframe fill modes,���Ƿ����ʹ��VK_POLYGON_MODE_POINT �Լ� VK_POLYGON_MODE_LINE
	physicalDeviceFeatures.depthBounds = VK_FALSE;//ָ���Ƿ�֧��depth bounds tests�������֧�֣���VkPipelineDepthStencilStateCreateInfo��depthBoundsTestEnable ����ΪVK_FALSE��������minDepthBounds�Լ�maxDepthBounds
	physicalDeviceFeatures.wideLines = VK_FALSE;//ָ���Ƿ�֧���߿�Ϊ1.0�������֧�֣��� VkPipelineRasterizationStateCreateInfo�Ļ��� vkCmdSetLineWidth���õ� lineWidth����Ϊ1.0�����֧�֣���֧�ֵ��߿�Χ�Լ����ȼ�VkPhysicalDeviceLimits��lineWidthRange�Լ� lineWidthGranularity
	physicalDeviceFeatures.largePoints = VK_FALSE;//ָ�����С�Ƿ�֧�ִ���1.0�����֧����֧�ֵĵ��С��Χ�Լ����ȼ�VkPhysicalDeviceLimits��pointSizeRange�Լ� pointSizeGranularity
	physicalDeviceFeatures.alphaToOne = VK_FALSE;//ָ���� Multisample Coverage fragment operation���Ƿ�֧���滻fragment shader color output��alphaֵ�����֧��������� VkPipelineRasterizationStateCreateInfo.alphaToOneEnable����ΪVK_TRUE����alpha-to-one��Ϊ
	physicalDeviceFeatures.multiViewport = VK_FALSE;//ָ���Ƿ�֧�ֶ��viewport�������֧�֣���VkPipelineViewportStateCreateInfo��viewportCount �Լ� scissorCount ��������Ϊ1��vkCmdSetViewport��firstViewport �Լ� viewportCount�ֱ���Ϊ0��1��vkCmdSetScissor��firstScissor �Լ� scissorCount�ֱ���Ϊ0��1��VkPipelineViewportExclusiveScissorStateCreateInfoNV��exclusiveScissorCount ����Ϊ0����1��vkCmdSetExclusiveScissorNV��firstExclusiveScissor �Լ� exclusiveScissorCount�ֱ���Ϊ0��1
	physicalDeviceFeatures.samplerAnisotropy = VK_FALSE;//ָ���Ƿ�֧��anisotropic filtering�������֧�֣��� VkSamplerCreateInfo��anisotropyEnable ��������ΪVK_FALSE
	physicalDeviceFeatures.textureCompressionETC2 = VK_FALSE;//ָ���Ƿ�֧��ETC2 �Լ� EAC ����ѹ����ʽ�����֧�֣�����VK_FORMAT_ETC2_***�Լ� VK_FORMAT_EAC_*** ��optimalTilingFeatures �������VK_FORMAT_FEATURE_SAMPLED_IMAGE_BIT, VK_FORMAT_FEATURE_BLIT_SRC_BIT �Լ� VK_FORMAT_FEATURE_SAMPLED_IMAGE_FILTER_LINEAR_BIT
	physicalDeviceFeatures.textureCompressionASTC_LDR = VK_FALSE;//ָ���Ƿ�֧��ASTC LDR ����ѹ����ʽ�����֧�֣�����VK_FORMAT_ASTC_*** ��optimalTilingFeatures �������VK_FORMAT_FEATURE_SAMPLED_IMAGE_BIT, VK_FORMAT_FEATURE_BLIT_SRC_BIT �Լ� VK_FORMAT_FEATURE_SAMPLED_IMAGE_FILTER_LINEAR_BIT
	physicalDeviceFeatures.textureCompressionBC = VK_FALSE;//ָ���Ƿ�֧��BC ����ѹ����ʽ�����֧�֣�����VK_FORMAT_BC*** ��optimalTilingFeatures �������VK_FORMAT_FEATURE_SAMPLED_IMAGE_BIT, VK_FORMAT_FEATURE_BLIT_SRC_BIT �Լ� VK_FORMAT_FEATURE_SAMPLED_IMAGE_FILTER_LINEAR_BIT
	physicalDeviceFeatures.occlusionQueryPrecise = VK_FALSE;//ָ���Ƿ�֧��occlusion queries����ʵ�ʵĲ����������Ƿ������VK_QUERY_TYPE_OCCLUSION ���͵�query��ʹ��VK_QUERY_CONTROL_PRECISE_BIT�� �����p3741
	physicalDeviceFeatures.pipelineStatisticsQuery = VK_FALSE;//ָ���Ƿ�֧��pipeline statistics queries�������֧�����ܴ���VK_QUERY_TYPE_PIPELINE_STATISTICS���͵�query��  VkQueryPoolCreateInfo.pipelineStatistics����Ϊ0
	physicalDeviceFeatures.vertexPipelineStoresAndAtomics = VK_FALSE;//ָ����vertex, tessellation, �Լ� geometry shader stages �� storage buffer�Լ�image�Ƿ�֧�� storage�Լ�atomic�����������֧�֣���shader�ж�Ӧ��Դ��������Ϊ NonWritable
	physicalDeviceFeatures.fragmentStoresAndAtomics = VK_FALSE;////ָ����fragment shader stages �� storage buffer�Լ�image�Ƿ�֧�� storage�Լ�atomic�����������֧�֣���shader�ж�Ӧ��Դ��������Ϊ NonWritable
	physicalDeviceFeatures.shaderTessellationAndGeometryPointSize = VK_FALSE;//ָ���� tessellation control, tessellation evaluation, �Լ� geometry shader stages���Ƿ���Է���PointSize��Ƕ���������֧�֣����Ӧshader stage�пɷ��ʵ�PointSize��Ӧ����Ϊ  TessellationPointSize�� GeometryPointSize
	physicalDeviceFeatures.shaderImageGatherExtended = VK_FALSE;//ָ���Ƿ���shader code�пɷ���image gather instructions����չ�������֧�֣���OpImage*Gatherָ�������� Offset �Լ� ConstOffsets ������
	physicalDeviceFeatures.shaderStorageImageExtendedFormats = VK_FALSE;//ָ���Ƿ�֧�����е�storage image extended formats�����֧�֣�����Щformats�� optimalTilingFeatures �б��뺬�� VK_FORMAT_FEATURE_STORAGE_IMAGE_BIT��  storage image extended formats��p3742
	physicalDeviceFeatures.shaderStorageImageMultisample = VK_FALSE;//ָ���Ƿ�֧�� multisampled storage images�������֧�֣�����VK_IMAGE_USAGE_STORAGE_BIT������image��samples����ΪVK_SAMPLE_COUNT_1_BIT
	physicalDeviceFeatures.shaderStorageImageReadWithoutFormat = VK_FALSE;//ָ������ȡ storage images �Լ� storage texel buffers��ʱ���Ƿ���Ҫָ��format
	physicalDeviceFeatures.shaderStorageImageWriteWithoutFormat = VK_FALSE;//ָ����д�� storage images �Լ� storage texel buffers��ʱ���Ƿ���Ҫָ��format
	physicalDeviceFeatures.shaderUniformBufferArrayDynamicIndexing = VK_FALSE;//ָ�� uniform buffers �����Ƿ������shader code��ͨ��һ��dynamically uniform integer expressions���з��ʣ������֧�֣���VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER ���� VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC ���͵���Դ����ֻ��ͨ���������ʽ���з���
	physicalDeviceFeatures.shaderSampledImageArrayDynamicIndexing = VK_FALSE;//ָ��samplers ���� sampled images �����Ƿ������shader code��ͨ��һ��dynamically uniform integer expressions���з��ʣ������֧�֣���VK_DESCRIPTOR_TYPE_SAMPLER, VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, ���� VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE ���͵���Դ����ֻ��ͨ���������ʽ���з���
	physicalDeviceFeatures.shaderStorageBufferArrayDynamicIndexing = VK_FALSE;//ָ�� storage buffers �����Ƿ������shader code��ͨ��һ��dynamically uniform integer expressions���з��ʣ������֧�֣���VK_DESCRIPTOR_TYPE_STORAGE_BUFFER ���� VK_DESCRIPTOR_TYPE_STORAGE_BUFFER_DYNAMIC ���͵���Դ����ֻ��ͨ���������ʽ���з���
	physicalDeviceFeatures.shaderStorageImageArrayDynamicIndexing = VK_FALSE;//ָ�� storage images �����Ƿ������shader code��ͨ��һ��dynamically uniform integer expressions���з��ʣ������֧�֣��� VK_DESCRIPTOR_TYPE_STORAGE_IMAGE ���͵���Դ����ֻ��ͨ���������ʽ���з���
	physicalDeviceFeatures.shaderClipDistance = VK_FALSE;//ָ��shader code���Ƿ�֧�� clip distances�������֧�֣���shader module�в��ܶ�ȡ��д���� ClipDistance �����ı���
	physicalDeviceFeatures.shaderCullDistance = VK_FALSE;//ָ��shader code���Ƿ�֧�� cull distances�������֧�֣���shader module�в��ܶ�ȡ��д���� CullDistance �����ı���
	physicalDeviceFeatures.shaderFloat64 = VK_FALSE;//ָ��shade code���Ƿ�֧��64-bit ������
	physicalDeviceFeatures.shaderInt64 = VK_FALSE;//ָ��shade code���Ƿ�֧��64-bit �޷����Լ��з�������
	physicalDeviceFeatures.shaderInt16 = VK_FALSE;//ָ��shade code���Ƿ�֧��16-bit �޷����Լ��з�������
	physicalDeviceFeatures.shaderResourceResidency = VK_FALSE;//ָ������resource residency��Ϣ��image operations�Ƿ���shader code��֧�֣������֧����shader code�в���ʹ��OpImageSparse* ָ��
	physicalDeviceFeatures.shaderResourceMinLod = VK_FALSE;//ָ��ָ����С��ԴLOD��Ϣ��image operations�Ƿ���shader code��֧�֣������֧����shader code�в���ʹ�� MinLod ������
	physicalDeviceFeatures.sparseBinding = VK_FALSE;//ָ���Ƿ���Դ�ڴ��������ɢ�������һ�����������й��������֧�֣���ÿ����Դ��Ҫ����һ�� vkBindBufferMemory ���� vkBindImageMemory���ڴ棬����Դ�����԰��� VK_BUFFER_CREATE_SPARSE_BINDING_BIT����  VK_IMAGE_CREATE_SPARSE_BINDING_BIT ����
	physicalDeviceFeatures.sparseResidencyBuffer = VK_FALSE;//ָ���Ƿ�device���Է���partially resident buffers�������֧�֣���buffer������ VkBufferCreateInfo.flags����VK_BUFFER_CREATE_SPARSE_RESIDENCY_BIT ����
	physicalDeviceFeatures.sparseResidencyImage2D = VK_FALSE;//ָ���Ƿ�device������ÿ��pixelһ�������� ����partially resident 2D images�������֧�֣�����VkImageCreateInfo��imageType����Ϊ VK_IMAGE_TYPE_2D��samples ����ΪVK_SAMPLE_COUNT_1_BIT�Ĵ�����image������ VkImageCreateInfo.flags����VK_IMAGE_CREATE_SPARSE_RESIDENCY_BIT ����
	physicalDeviceFeatures.sparseResidencyImage3D = VK_FALSE;//ָ���Ƿ�device���Է���partially resident 3D images�������֧�֣�����VkImageCreateInfo��imageType����Ϊ  VK_IMAGE_TYPE_3D������image������ VkImageCreateInfo.flags����VK_IMAGE_CREATE_SPARSE_RESIDENCY_BIT ����
	physicalDeviceFeatures.sparseResidency2Samples = VK_FALSE;//ָ���Ƿ�device������ÿ��pixel���������� ����partially resident 2D images�������֧�֣�����VkImageCreateInfo��imageType����Ϊ VK_IMAGE_TYPE_2D��samples ����ΪVK_SAMPLE_COUNT_2_BIT�Ĵ�����image������ VkImageCreateInfo.flags����VK_IMAGE_CREATE_SPARSE_RESIDENCY_BIT ����
	physicalDeviceFeatures.sparseResidency4Samples = VK_FALSE;//ָ���Ƿ�device������ÿ��pixel�ĸ������� ����partially resident 2D images�������֧�֣�����VkImageCreateInfo��imageType����Ϊ VK_IMAGE_TYPE_2D��samples ����ΪVK_SAMPLE_COUNT_4_BIT�Ĵ�����image������ VkImageCreateInfo.flags����VK_IMAGE_CREATE_SPARSE_RESIDENCY_BIT ����
	physicalDeviceFeatures.sparseResidency8Samples = VK_FALSE;//ָ���Ƿ�device������ÿ��pixel�˸������� ����partially resident 2D images�������֧�֣�����VkImageCreateInfo��imageType����Ϊ VK_IMAGE_TYPE_2D��samples ����ΪVK_SAMPLE_COUNT_8_BIT�Ĵ�����image������ VkImageCreateInfo.flags����VK_IMAGE_CREATE_SPARSE_RESIDENCY_BIT ����
	physicalDeviceFeatures.sparseResidency16Samples = VK_FALSE;//ָ���Ƿ�device������ÿ��pixelʮ���������� ����partially resident 2D images�������֧�֣�����VkImageCreateInfo��imageType����Ϊ VK_IMAGE_TYPE_2D��samples ����ΪVK_SAMPLE_COUNT_16_BIT�Ĵ�����image������ VkImageCreateInfo.flags����VK_IMAGE_CREATE_SPARSE_RESIDENCY_BIT ����
	physicalDeviceFeatures.sparseResidencyAliased = VK_FALSE;//ָ���Ƿ������豸���Է��ʶ��λ�ô��ڱ��������ݣ������֧�֣���VkBufferCreateInfo �Լ� VkImageCreateInfo��flags�в��ܶ�Ӧ����VK_BUFFER_CREATE_SPARSE_ALIASED_BIT �Լ� VK_IMAGE_CREATE_SPARSE_ALIASED_BIT
	physicalDeviceFeatures.variableMultisampleRate = VK_FALSE;//ָ���ڲ�ʹ�ø�����subpass�а󶨵�ͬһ��command buffer������pipeline��VkPipelineMultisampleStateCreateInfo::rasterizationSamples�Ƿ������ͬ�������֧�֣����ڲ�ʹ�ø�����subpass������pipeline��multisample rate ������ͬ
	physicalDeviceFeatures.inheritedQueries = VK_FALSE;//ָ��������queryʱ�Ƿ����ִ��һ��secondary command buffer


	//��ѯcore������չ֧�ֵ�features
	VkPhysicalDeviceFeatures2 physicalDeviceFeatures2{};//�ȼ���VkPhysicalDeviceFeaturesKHR
	physicalDeviceFeatures2.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FEATURES_2;
	physicalDeviceFeatures2.pNext = nullptr;

	//�ȼ���vkGetPhysicalDeviceFeaturesKHR
	vkGetPhysicalDeviceFeatures2(physicalDevice, &physicalDeviceFeatures2);//������ȷ�����˽��
	physicalDeviceFeatures2.features = physicalDeviceFeatures;//Ϊһ��VkPhysicalDeviceFeatures



	//VkPhysicalDeviceVulkan11Features ,  ���԰�����VkPhysicalDeviceFeatures2.pNext��
	VkPhysicalDeviceVulkan11Features physicalDeviceVulkan11Features{};
	physicalDeviceVulkan11Features.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_1_FEATURES;
	physicalDeviceVulkan11Features.pNext = nullptr;
	physicalDeviceVulkan11Features.storageBuffer16BitAccess = VK_FALSE;//ָ���Ƿ�StorageBuffer, ShaderRecordBufferKHR, ���� PhysicalStorageBuffer storage class����Block�����Ķ����Ƿ��ܹ�����16-bit���������߸�������Ա
	physicalDeviceVulkan11Features.uniformAndStorageBuffer16BitAccess = VK_FALSE;//ָ���Ƿ�Uniform storage class����Block�����Ķ����Ƿ��ܹ�����16-bit���������߸�������Ա
	physicalDeviceVulkan11Features.storagePushConstant16 = VK_FALSE;//ָ���Ƿ�PushConstant storage class�ܹ�����16-bit���������߸�������Ա
	physicalDeviceVulkan11Features.storageInputOutput16 = VK_FALSE;//ָ���Ƿ� Input �Լ� Output storage classes�ܹ�����16-bit���������߸�������Ա
	physicalDeviceVulkan11Features.multiview = VK_FALSE;//ָ���Ƿ�֧����һ��render pass�н���multiview��Ⱦ�������֧�֣���ÿ��subpass��view mask����Ϊ0
	physicalDeviceVulkan11Features.multiviewGeometryShader = VK_FALSE;//ָ���Ƿ�֧����һ������geometry shaders�� render pass�н���multiview��Ⱦ�������֧�֣�����view mask��Ϊ0��pipeline���ܰ���geometry shaders
	physicalDeviceVulkan11Features.multiviewTessellationShader = VK_FALSE;//ָ���Ƿ�֧����һ������ tessellation shaders�� render pass�н���multiview��Ⱦ�������֧�֣�����view mask��Ϊ0��pipeline���ܰ��� tessellation shaders
	physicalDeviceVulkan11Features.variablePointersStorageBuffer = VK_FALSE;//ָ��ʵ���Ƿ�֧��SPIR-V VariablePointersStorageBuffer ����
	physicalDeviceVulkan11Features.variablePointers = VK_FALSE;//ָ��ʵ���Ƿ�֧��SPIR-V VariablePointers ����
	physicalDeviceVulkan11Features.protectedMemory = VK_FALSE;//ָ���Ƿ�֧�� protected memory
	physicalDeviceVulkan11Features.samplerYcbcrConversion = VK_FALSE;//ָ��ʵ���Ƿ�֧��sampler Y��CBCR conversion
	physicalDeviceVulkan11Features.shaderDrawParameters = VK_FALSE;//ָ��ʵ���Ƿ�֧��SPIR-V DrawParameters ����


	// VkPhysicalDeviceVulkan12Features ,  ���԰�����VkPhysicalDeviceFeatures2.pNext��
	VkPhysicalDeviceVulkan12Features  physicalDeviceVulkan12Features{};
	physicalDeviceVulkan12Features.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_2_FEATURES;
	physicalDeviceVulkan12Features.pNext = nullptr;
	physicalDeviceVulkan12Features.samplerMirrorClampToEdge = VK_FALSE;//ָ���Ƿ�֧��VK_SAMPLER_ADDRESS_MODE_MIRROR_CLAMP_TO_EDGE sampler address mode
	physicalDeviceVulkan12Features.drawIndirectCount = VK_FALSE;//ָ���Ƿ�֧��vkCmdDrawIndirectCount �Լ� vkCmdDrawIndexedIndirectCount ������ʹ��
	physicalDeviceVulkan12Features.storageBuffer8BitAccess = VK_FALSE;//ָ���Ƿ�StorageBuffer, ShaderRecordBufferKHR, ���� PhysicalStorageBuffer storage class����Block�����Ķ����Ƿ��ܹ�����8-bit��������Ա
	physicalDeviceVulkan12Features.uniformAndStorageBuffer8BitAccess = VK_FALSE;//ָ���Ƿ�Uniform storage class����Block�����Ķ����Ƿ��ܹ�����8-bit��������Ա
	physicalDeviceVulkan12Features.storagePushConstant8 = VK_FALSE;//ָ���Ƿ�PushConstant storage class�ܹ�����8-bit��������Ա
	physicalDeviceVulkan12Features.shaderBufferInt64Atomics = VK_FALSE;//ָ���Ƿ�shader code���Խ���buffer�ϵ�64-bit���з����Լ��޷��ŵ�����atomic operations
	physicalDeviceVulkan12Features.shaderSharedInt64Atomics = VK_FALSE;//ָ���Ƿ�shader code���Խ���shared �Լ� payload memory�ϵ�64-bit���з����Լ��޷��ŵ�����atomic operations
	physicalDeviceVulkan12Features.shaderFloat16 = VK_FALSE;//ָ��shader code�Ƿ�֧��16-bit������
	physicalDeviceVulkan12Features.shaderInt8 = VK_FALSE; // ָ��shader code�Ƿ�֧��8-bit�޷����Լ��з�������
	physicalDeviceVulkan12Features.descriptorIndexing = VK_FALSE;//ָ��ʵ���Ƿ�֧�� Feature Requirements p3899��������������������С��
	physicalDeviceVulkan12Features.shaderInputAttachmentArrayDynamicIndexing = VK_FALSE;//ָ��input attachments �����Ƿ������shader code��ͨ��һ��dynamically uniform integer expressions���з��ʣ������֧�֣���VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT ���͵���Դ����ֻ��ͨ���������ʽ���з���
	physicalDeviceVulkan12Features.shaderUniformTexelBufferArrayDynamicIndexing = VK_FALSE;//ָ��uniform texel buffers �����Ƿ������shader code��ͨ��һ��dynamically uniform integer expressions���з��ʣ������֧�֣���VK_DESCRIPTOR_TYPE_UNIFORM_TEXEL_BUFFER ���͵���Դ����ֻ��ͨ���������ʽ���з���
	physicalDeviceVulkan12Features.shaderStorageTexelBufferArrayDynamicIndexing = VK_FALSE;//ָ��storage texel buffers �����Ƿ������shader code��ͨ��һ��dynamically uniform integer expressions���з��ʣ������֧�֣���VK_DESCRIPTOR_TYPE_STORAGE_TEXEL_BUFFER ���͵���Դ����ֻ��ͨ���������ʽ���з���
	physicalDeviceVulkan12Features.shaderUniformBufferArrayNonUniformIndexing = VK_FALSE;//ָ�� uniform buffers �����Ƿ������shader code��ͨ��һ��non-uniform integer expressions���з��ʣ������֧�֣���VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER ���� VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC ���͵���Դ���鲻��ͨ��non-uniform integer expressions ���з���
	physicalDeviceVulkan12Features.shaderSampledImageArrayNonUniformIndexing = VK_FALSE;//ָ��samplers ���� sampled images �����Ƿ������shader code��ͨ��һ��non-uniform integer expressions���з��ʣ������֧�֣���VK_DESCRIPTOR_TYPE_SAMPLER, VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, ���� VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE���͵���Դ���鲻��ͨ��non-uniform integer expressions ���з���
	physicalDeviceVulkan12Features.shaderStorageBufferArrayNonUniformIndexing = VK_FALSE;//ָ�� storage buffers �����Ƿ������shader code��ͨ��һ��non-uniform integer expressions���з��ʣ������֧�֣���VK_DESCRIPTOR_TYPE_STORAGE_BUFFER ���� VK_DESCRIPTOR_TYPE_STORAGE_BUFFER_DYNAMIC ���͵���Դ���鲻��ͨ��non-uniform integer expressions ���з���
	physicalDeviceVulkan12Features.shaderStorageImageArrayNonUniformIndexing = VK_FALSE;//ָ�� storage images �����Ƿ������shader code��ͨ��һ��non-uniform integer expressions���з��ʣ������֧�֣���VK_DESCRIPTOR_TYPE_STORAGE_IMAGE ���͵���Դ���鲻��ͨ��non-uniform integer expressions ���з���
	physicalDeviceVulkan12Features.shaderInputAttachmentArrayNonUniformIndexing = VK_FALSE;//ָ�� input attachments �����Ƿ������shader code��ͨ��һ��non-uniform integer expressions���з��ʣ������֧�֣���VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT ���͵���Դ���鲻��ͨ��non-uniform integer expressions ���з���
	physicalDeviceVulkan12Features.shaderUniformTexelBufferArrayNonUniformIndexing = VK_FALSE;//ָ�� uniform texel buffers �����Ƿ������shader code��ͨ��һ��non-uniform integer expressions���з��ʣ������֧�֣���VK_DESCRIPTOR_TYPE_UNIFORM_TEXEL_BUFFER ���͵���Դ���鲻��ͨ��non-uniform integer expressions ���з���
	physicalDeviceVulkan12Features.shaderStorageTexelBufferArrayNonUniformIndexing = VK_FALSE;//ָ�� storage texel buffers �����Ƿ������shader code��ͨ��һ��non-uniform integer expressions���з��ʣ������֧�֣���VK_DESCRIPTOR_TYPE_STORAGE_TEXEL_BUFFER ���͵���Դ���鲻��ͨ��non-uniform integer expressions ���з���
	physicalDeviceVulkan12Features.descriptorBindingUniformBufferUpdateAfterBind = VK_FALSE;//ָ���Ƿ�֧���ڰ�һ��descriptor set֮�����uniform buffer descriptors�������֧�֣���VK_DESCRIPTOR_BINDING_UPDATE_AFTER_BIND_BIT���ܺ� VK_DESCRIPTOR_TYPE_UNIFORM_BUFFERһ��ʹ��
	physicalDeviceVulkan12Features.descriptorBindingSampledImageUpdateAfterBind = VK_FALSE;//ָ���Ƿ�֧���ڰ�һ��descriptor set֮�����sampled image descriptors�������֧�֣���VK_DESCRIPTOR_BINDING_UPDATE_AFTER_BIND_BIT���ܺ� VK_DESCRIPTOR_TYPE_SAMPLER, VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, ����VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE һ��ʹ��
	physicalDeviceVulkan12Features.descriptorBindingStorageImageUpdateAfterBind = VK_FALSE;//ָ���Ƿ�֧���ڰ�һ��descriptor set֮�����storage image descriptors�������֧�֣���VK_DESCRIPTOR_BINDING_UPDATE_AFTER_BIND_BIT���ܺ� VK_DESCRIPTOR_TYPE_STORAGE_IMAGEһ��ʹ��
	physicalDeviceVulkan12Features.descriptorBindingStorageBufferUpdateAfterBind = VK_FALSE;//ָ���Ƿ�֧���ڰ�һ��descriptor set֮�����storage buffer descriptors�������֧�֣���VK_DESCRIPTOR_BINDING_UPDATE_AFTER_BIND_BIT���ܺ� VK_DESCRIPTOR_TYPE_STORAGE_BUFFERһ��ʹ��
	physicalDeviceVulkan12Features.descriptorBindingUniformTexelBufferUpdateAfterBind = VK_FALSE;//ָ���Ƿ�֧���ڰ�һ��descriptor set֮�����uniform texel buffer descriptors�������֧�֣���VK_DESCRIPTOR_BINDING_UPDATE_AFTER_BIND_BIT���ܺ� VK_DESCRIPTOR_TYPE_UNIFORM_TEXEL_BUFFERһ��ʹ��
	physicalDeviceVulkan12Features.descriptorBindingStorageTexelBufferUpdateAfterBind = VK_FALSE;//ָ���Ƿ�֧���ڰ�һ��descriptor set֮�����storage texel buffer descriptors�������֧�֣���VK_DESCRIPTOR_BINDING_UPDATE_AFTER_BIND_BIT���ܺ� VK_DESCRIPTOR_TYPE_STORAGE_TEXEL_BUFFERһ��ʹ��
	physicalDeviceVulkan12Features.descriptorBindingUpdateUnusedWhilePending = VK_FALSE;//ָ���Ƿ�֧����descriptor set����ʹ�õ�ʱ�����descriptors�������֧������ʹ��VK_DESCRIPTOR_BINDING_UPDATE_UNUSED_WHILE_PENDING_BIT
	physicalDeviceVulkan12Features.descriptorBindingPartiallyBound = VK_FALSE;//ָ���Ƿ�֧�־�̬ʹ��һ������descriptor��Ч��descriptor set binding�������֧������ʹ��VK_DESCRIPTOR_BINDING_PARTIALLY_BOUND_BIT
	physicalDeviceVulkan12Features.descriptorBindingVariableDescriptorCount = VK_FALSE;//ָ���Ƿ�֧��descriptor sets�����һ��binding�Ǵ�С�ɱ�ģ������֧������ʹ��VK_DESCRIPTOR_BINDING_VARIABLE_DESCRIPTOR_COUNT_BIT
	physicalDeviceVulkan12Features.runtimeDescriptorArray = VK_FALSE;//ָ���Ƿ�֧�� SPIR-V RuntimeDescriptorArray����
	physicalDeviceVulkan12Features.samplerFilterMinmax = VK_FALSE;//ָ����Ҫ��formats����С���Ƿ�֧��min/max filtering�������֧�֣���VkSamplerReductionModeCreateInfo��ֻ��ʹ��VK_SAMPLER_REDUCTION_MODE_WEIGHTED_AVERAGE
	physicalDeviceVulkan12Features.scalarBlockLayout = VK_FALSE;//ָ���Ƿ�shader����Դ���layout�ܷ�ʹ�� scalar alignment
	physicalDeviceVulkan12Features.imagelessFramebuffer = VK_FALSE;//ָ���Ƿ�֧����render pass��ʼ��ʱ��ͨ�� VkRenderPassAttachmentBeginInfo ָ��������image view
	physicalDeviceVulkan12Features.uniformBufferStandardLayout = VK_FALSE;//ָ���Ƿ�֧��uniform buffers��Ϊstorage �����������͵�buffer��ʱ��ʹ����ͬ��layout
	physicalDeviceVulkan12Features.shaderSubgroupExtendedTypes = VK_FALSE;//ָ�� subgroup operations �Ƿ����ʹ�� 8-bit integer, 16-bit integer, 64-bit integer, 16-bit floating point,�Լ���Щ���͵�vecֵ�������Щ����֧�ֵĻ�
	physicalDeviceVulkan12Features.separateDepthStencilLayouts = VK_FALSE;//ָ���Ƿ�֧�ֶ�ֻ������VK_IMAGE_ASPECT_DEPTH_BIT ���� VK_IMAGE_ASPECT_STENCIL_BIT ��depth/stencil imageʹ��VkImageMemoryBarrier�����Ƿ�VK_IMAGE_LAYOUT_DEPTH_ATTACHMENT_OPTIMAL, VK_IMAGE_LAYOUT_DEPTH_READ_ONLY_OPTIMAL, VK_IMAGE_LAYOUT_STENCIL_ATTACHMENT_OPTIMAL, ���� VK_IMAGE_LAYOUT_STENCIL_READ_ONLY_OPTIMAL����ʹ��
	physicalDeviceVulkan12Features.hostQueryReset = VK_FALSE;//ָ���Ƿ������host����vkResetQueryPool����query
	physicalDeviceVulkan12Features.timelineSemaphore = VK_FALSE;//ָ���Ƿ���Դ���VkSemaphoreTypeΪVK_SEMAPHORE_TYPE_TIMELINE��semaphore
	physicalDeviceVulkan12Features.bufferDeviceAddress = VK_FALSE;//ָ���Ƿ�֧����shader�з���ͨ�� vkGetBufferDeviceAddress��ȡ���ڴ��ַ��Ϊstorage buffers���з���
	physicalDeviceVulkan12Features.bufferDeviceAddressCaptureReplay = VK_FALSE;//ָ��ʵ��֧�ֱ��������buffer �Լ� device addresses
	physicalDeviceVulkan12Features.bufferDeviceAddressMultiDevice = VK_FALSE;//ָ��ʵ��֧�����Զ������豸�������߼��豸��֧��bufferDeviceAddress , rayTracingPipeline �Լ� rayQuery ����
	physicalDeviceVulkan12Features.vulkanMemoryModel = VK_FALSE;//ָ���Ƿ�shader modules�ܹ�����VulkanMemoryModel ����
	physicalDeviceVulkan12Features.vulkanMemoryModelDeviceScope = VK_FALSE;//ָ��Vulkan Memory Model����ʹ�� Device scope synchronization.
	physicalDeviceVulkan12Features.vulkanMemoryModelAvailabilityVisibilityChains = VK_FALSE;//ָ��Vulkan Memory Model����ʹ�ó���һ��Ԫ�ص� availability �Լ� visibility chains
	physicalDeviceVulkan12Features.shaderOutputViewportIndex = VK_FALSE;//ָ��ʵ��֧��ShaderViewportIndex SPIR-V ��������������mesh, vertex ���� tessellation evaluation shaders��ViewportIndex ��Ƕ���������������
	physicalDeviceVulkan12Features.shaderOutputLayer = VK_FALSE;//ָ��ʵ��֧�� ShaderLayer SPIR-V��������������mesh, vertex ���� tessellation evaluation shaders��Layer ��Ƕ���������������
	physicalDeviceVulkan12Features.subgroupBroadcastDynamicId = VK_FALSE;//ָ�� OpGroupNonUniformBroadcast��Id �������Լ�OpGroupNonUniformQuadBroadcast�� Index �������Ƿ�����Ƕ�̬��uniformֵ



	//VkPhysicalDeviceVulkan13Features  ,  ���԰�����VkPhysicalDeviceFeatures2.pNext��
	VkPhysicalDeviceVulkan13Features physicalDeviceVulkan13Features{};
	physicalDeviceVulkan13Features.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_3_FEATURES;
	physicalDeviceVulkan13Features.pNext = nullptr;
	physicalDeviceVulkan13Features.robustImageAccess = VK_FALSE;//ָ����image�ķ��ʻ��image view��ά�Ƚ��б߽���
	physicalDeviceVulkan13Features.inlineUniformBlock = VK_FALSE;//ָ���Ƿ�֧��inline uniform block descriptor�������֧�֣�����ʹ�� VK_DESCRIPTOR_TYPE_INLINE_UNIFORM_BLOCK
	physicalDeviceVulkan13Features.descriptorBindingInlineUniformBlockUpdateAfterBind = VK_FALSE;//ָ���Ƿ�֧���ڰ�һ��descriptor set֮�����inline uniform block descriptors�������֧�֣���VK_DESCRIPTOR_BINDING_UPDATE_AFTER_BIND_BIT���ܺ� VK_DESCRIPTOR_TYPE_INLINE_UNIFORM_BLOCKһ��ʹ��
	physicalDeviceVulkan13Features.pipelineCreationCacheControl = VK_FALSE;//ָ��Vk*PipelineCreateInfo::flags ���Ƿ���԰���VK_PIPELINE_CREATE_FAIL_ON_PIPELINE_COMPILE_REQUIRED_BIT ���� VK_PIPELINE_CREATE_EARLY_RETURN_ON_FAILURE_BIT��  VkPipelineCacheCreateInfo::flags ���Ƿ���԰��� VK_PIPELINE_CACHE_CREATE_EXTERNALLY_SYNCHRONIZED_BIT
	physicalDeviceVulkan13Features.privateData = VK_FALSE;//ָ���Ƿ�֧�� private data����p3202
	physicalDeviceVulkan13Features.shaderDemoteToHelperInvocation = VK_FALSE;//ָ���Ƿ�֧��SPIR-V DemoteToHelperInvocationEXT ����
	physicalDeviceVulkan13Features.shaderTerminateInvocation = VK_FALSE;//ָ���Ƿ�֧��SPIR-V modules ʹ�� SPV_KHR_terminate_invocation ��չ
	physicalDeviceVulkan13Features.subgroupSizeControl = VK_FALSE;//ָ���Ƿ����ͨ��VK_PIPELINE_SHADER_STAGE_CREATE_ALLOW_VARYING_SUBGROUP_SIZE_BIT �Լ�  VkPipelineShaderStageRequiredSubgroupSizeCreateInfo ��ָ��subgroup size
	physicalDeviceVulkan13Features.computeFullSubgroups = VK_FALSE;//ָ��compute , mesh, ���� task shaders�Ƿ����ͨ��VK_PIPELINE_SHADER_STAGE_CREATE_REQUIRE_FULL_SUBGROUPS_BIT ��Ҫ��ʹ��������subgroup
	physicalDeviceVulkan13Features.synchronization2 = VK_FALSE;//ָ���Ƿ�֧�� VK_KHR_synchronization2 ��չ��˵����һ��ͬ������
	physicalDeviceVulkan13Features.textureCompressionASTC_HDR = VK_FALSE;//ָ���Ƿ�֧�����е�ASTC HDR ѹ�������ʽ�����֧�֣�����VK_FORMAT_ASTC_*** ��optimalTilingFeatures �������VK_FORMAT_FEATURE_SAMPLED_IMAGE_BIT, VK_FORMAT_FEATURE_BLIT_SRC_BIT �Լ� VK_FORMAT_FEATURE_SAMPLED_IMAGE_FILTER_LINEAR_BIT
	physicalDeviceVulkan13Features.shaderZeroInitializeWorkgroupMemory = VK_FALSE;//ָ���Ƿ�֧�ֳ�ʼ��һ��Workgroup storage class���͵ı���
	physicalDeviceVulkan13Features.dynamicRendering = VK_FALSE;//ָ���Ƿ����ͨ��ʹ�� vkCmdBeginRendering ֧�ֶ�̬render pass instance
	physicalDeviceVulkan13Features.shaderIntegerDotProduct = VK_FALSE;//ָ��shader module�Ƿ��������DotProductInputAllKHR, DotProductInput4x8BitKHR, DotProductInput4x8BitPackedKHR �Լ� DotProductKHR ����
	physicalDeviceVulkan13Features.maintenance4 = VK_FALSE;//ָ���Ƿ�֧��: 1.ʹ�� VkPipelineLayout ����һ��������������ٸ�pipeline��2.LocalSizeId �����滻 LocalSize;3.����ͬ����������image�Ķ���Ҫ����ͬ;4.buffer�Լ�image�Ĵ�С�ڴ�Ҫ�󲻻������һ���ڴ�ȸ�buffer����image����ڴ��СҪ��;5.�ڶ�̬����֮ǰPush constants���س�ʼ��;6.�ӿ�ƥ�����������output vec��С��input vecƥ�䣬��ķ����ᱻ����


	// VkPhysicalDeviceVariablePointersFeatures  ���ȼ��� VkPhysicalDeviceVariablePointersFeaturesKHR ,  ���԰�����VkPhysicalDeviceFeatures2.pNext�� 
	VkPhysicalDeviceVariablePointersFeatures  physicalDeviceVariablePointersFeatures{};
	physicalDeviceVariablePointersFeatures.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VARIABLE_POINTERS_FEATURES;
	physicalDeviceVariablePointersFeatures.pNext = nullptr;
	physicalDeviceVariablePointersFeatures.variablePointersStorageBuffer = VK_FALSE;//ָ���Ƿ�֧��SPIR-V VariablePointersStorageBuffer ���������֧�֣��������shader module������SPV_KHR_variable_pointers ��չ���� VariablePointersStorageBuffer ����
	physicalDeviceVariablePointersFeatures.variablePointers = VK_FALSE;//ָ���Ƿ�֧��SPIR-V VariablePointers ���������֧�֣��������shader module������ VariablePointers ���������������֧�֣���variablePointersStorageBuffer Ҳ����֧��


	// VkPhysicalDeviceMultiviewFeatures���ȼ��� VkPhysicalDeviceMultiviewFeaturesKHR ,  ���԰�����VkPhysicalDeviceFeatures2.pNext�� 
	VkPhysicalDeviceMultiviewFeatures physicalDeviceMultiviewFeatures{};
	physicalDeviceMultiviewFeatures.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MULTIVIEW_FEATURES;
	physicalDeviceMultiviewFeatures.pNext = nullptr;
	physicalDeviceMultiviewFeatures.multiview = VK_FALSE;//ָ����һ��render pass���Ƿ�֧��multiview ��Ⱦ�������֧�֣���ÿ��subpass��view mask����Ϊ0
	physicalDeviceMultiviewFeatures.multiviewGeometryShader = VK_FALSE;//ָ���Ƿ�֧����һ������geometry shaders�� render pass�н���multiview��Ⱦ�������֧�֣�����view mask��Ϊ0��pipeline���ܰ���geometry shaders�� ���������֧�֣���multiview ����֧��
	physicalDeviceMultiviewFeatures.multiviewTessellationShader = VK_FALSE;//ָ���Ƿ�֧����һ������ tessellation shaders�� render pass�н���multiview��Ⱦ�������֧�֣�����view mask��Ϊ0��pipeline���ܰ��� tessellation shaders�� ���������֧�֣���multiview ����֧��


	//VkPhysicalDeviceShaderAtomicFloatFeaturesEXT ,   ���԰�����VkPhysicalDeviceFeatures2.pNext�� 
	VkPhysicalDeviceShaderAtomicFloatFeaturesEXT physicalDeviceShaderAtomicFloatFeaturesEXT{};
	physicalDeviceShaderAtomicFloatFeaturesEXT.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_ATOMIC_FLOAT_FEATURES_EXT;
	physicalDeviceShaderAtomicFloatFeaturesEXT.pNext = nullptr;
	physicalDeviceShaderAtomicFloatFeaturesEXT.shaderBufferFloat32Atomics = VK_FALSE;//ָ��shader�Ƿ������storage buffer��ִ��32-bit ����load, store �Լ� exchange atomic operations
	physicalDeviceShaderAtomicFloatFeaturesEXT.shaderBufferFloat32AtomicAdd = VK_FALSE;//ָ��shader�Ƿ������storage buffer��ִ��32-bit ����add atomic operations
	physicalDeviceShaderAtomicFloatFeaturesEXT.shaderBufferFloat64Atomics = VK_FALSE;//ָ��shader�Ƿ������storage buffer��ִ��64-bit ����load, store �Լ� exchange atomic operations
	physicalDeviceShaderAtomicFloatFeaturesEXT.shaderBufferFloat64AtomicAdd = VK_FALSE;//ָ��shader�Ƿ������storage buffer��ִ��64-bit ����add atomic operations
	physicalDeviceShaderAtomicFloatFeaturesEXT.shaderSharedFloat32Atomics = VK_FALSE;//ָ��shader�Ƿ������shared �Լ� payload memory��ִ��32-bit ����load, store �Լ� exchange atomic operations
	physicalDeviceShaderAtomicFloatFeaturesEXT.shaderSharedFloat32AtomicAdd = VK_FALSE;//ָ��shader�Ƿ������shared �Լ� payload memory��ִ��32-bit ����add atomic operations
	physicalDeviceShaderAtomicFloatFeaturesEXT.shaderSharedFloat64Atomics = VK_FALSE;//ָ��shader�Ƿ������shared �Լ� payload memory��ִ��64-bit ����load, store �Լ� exchange atomic operations
	physicalDeviceShaderAtomicFloatFeaturesEXT.shaderSharedFloat64AtomicAdd = VK_FALSE;//ָ��shader�Ƿ������shared �Լ� payload memory��ִ��64-bit ����add atomic operations
	physicalDeviceShaderAtomicFloatFeaturesEXT.shaderImageFloat32Atomics = VK_FALSE;//ָ��shader�Ƿ����ִ��32-bit ����load, store �Լ� exchange atomic image operations
	physicalDeviceShaderAtomicFloatFeaturesEXT.shaderImageFloat32AtomicAdd = VK_FALSE;//ָ��shader�Ƿ����ִ��32-bit ����add atomic image operations
	physicalDeviceShaderAtomicFloatFeaturesEXT.sparseImageFloat32Atomics = VK_FALSE;//ָ��shader�Ƿ������ sparse images��ִ��64-bit ����load, store �Լ� exchange atomic operations
	physicalDeviceShaderAtomicFloatFeaturesEXT.sparseImageFloat32AtomicAdd = VK_FALSE;//ָ��shader�Ƿ������ sparse images��ִ��64-bit ����add atomic operations


	//VkPhysicalDeviceShaderAtomicFloat2FeaturesEXT��  ���԰�����VkPhysicalDeviceFeatures2.pNext��
	VkPhysicalDeviceShaderAtomicFloat2FeaturesEXT  physicalDeviceShaderAtomicFloat2FeaturesEXT{};
	physicalDeviceShaderAtomicFloat2FeaturesEXT.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_ATOMIC_FLOAT_2_FEATURES_EXT;
	physicalDeviceShaderAtomicFloat2FeaturesEXT.pNext = nullptr;
	physicalDeviceShaderAtomicFloat2FeaturesEXT.shaderBufferFloat16Atomics = VK_FALSE;//ָ��shader�Ƿ������storage buffer��ִ��16-bit ����load, store �Լ� exchange atomic operations
	physicalDeviceShaderAtomicFloat2FeaturesEXT.shaderBufferFloat16AtomicAdd = VK_FALSE;//ָ��shader�Ƿ������storage buffer��ִ��16-bit ����add atomic operations
	physicalDeviceShaderAtomicFloat2FeaturesEXT.shaderBufferFloat16AtomicMinMax = VK_FALSE;//ָ��shader�Ƿ������storage buffer��ִ��16-bit ����min �Լ�max atomic operations
	physicalDeviceShaderAtomicFloat2FeaturesEXT.shaderBufferFloat32AtomicMinMax = VK_FALSE;//ָ��shader�Ƿ������storage buffer��ִ��32-bit ����min �Լ�max atomic operations
	physicalDeviceShaderAtomicFloat2FeaturesEXT.shaderBufferFloat64AtomicMinMax = VK_FALSE;//ָ��shader�Ƿ������storage buffer��ִ��64-bit ����min �Լ�max atomic operations
	physicalDeviceShaderAtomicFloat2FeaturesEXT.shaderSharedFloat16Atomics = VK_FALSE;//ָ��shader�Ƿ������shared �Լ� payload memory��ִ��16-bit ����load, store �Լ� exchange atomic operations
	physicalDeviceShaderAtomicFloat2FeaturesEXT.shaderSharedFloat16AtomicAdd = VK_FALSE;//ָ��shader�Ƿ������shared �Լ� payload memory��ִ��16-bit ����add atomic operations
	physicalDeviceShaderAtomicFloat2FeaturesEXT.shaderSharedFloat16AtomicMinMax = VK_FALSE;//ָ��shader�Ƿ������shared �Լ� payload memory��ִ��16-bit ����min �Լ�max atomic operations
	physicalDeviceShaderAtomicFloat2FeaturesEXT.shaderSharedFloat32AtomicMinMax = VK_FALSE;//ָ��shader�Ƿ������shared �Լ� payload memory��ִ��32-bit ����min �Լ�max atomic operations
	physicalDeviceShaderAtomicFloat2FeaturesEXT.shaderSharedFloat64AtomicMinMax = VK_FALSE;//ָ��shader�Ƿ������shared �Լ� payload memory��ִ��64-bit ����min �Լ�max atomic operations
	physicalDeviceShaderAtomicFloat2FeaturesEXT.shaderImageFloat32AtomicMinMax = VK_FALSE;//ָ��shader�Ƿ����ִ��32-bit ����min �Լ�max atomic image operations
	physicalDeviceShaderAtomicFloat2FeaturesEXT.sparseImageFloat32AtomicMinMax = VK_FALSE;//ָ��shader�Ƿ����ִ��64-bit ����min �Լ�max atomic image operations


	// VkPhysicalDeviceShaderAtomicInt64Features ���ȼ��� VkPhysicalDeviceShaderAtomicInt64FeaturesKHR ,  ���԰�����VkPhysicalDeviceFeatures2.pNext��
	VkPhysicalDeviceShaderAtomicInt64Features  physicalDeviceShaderAtomicInt64Features{};
	physicalDeviceShaderAtomicInt64Features.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_ATOMIC_INT64_FEATURES;
	physicalDeviceShaderAtomicInt64Features.pNext = nullptr;
	physicalDeviceShaderAtomicInt64Features.shaderBufferInt64Atomics = VK_FALSE;//ָ��shader�Ƿ������buffer��ִ��64-bit �з����Լ��޷������� atomic operations
	physicalDeviceShaderAtomicInt64Features.shaderSharedInt64Atomics = VK_FALSE;//ָ��shader�Ƿ������shared �Լ� payload memory��ִ��64-bit �з����Լ��޷������� atomic operations


	//VkPhysicalDeviceShaderImageAtomicInt64FeaturesEXT ��  ���԰�����VkPhysicalDeviceFeatures2.pNext��
	VkPhysicalDeviceShaderImageAtomicInt64FeaturesEXT physicalDeviceShaderImageAtomicInt64FeaturesEXT{};
	physicalDeviceShaderImageAtomicInt64FeaturesEXT.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_IMAGE_ATOMIC_INT64_FEATURES_EXT;
	physicalDeviceShaderImageAtomicInt64FeaturesEXT.pNext = nullptr;
	physicalDeviceShaderImageAtomicInt64FeaturesEXT.shaderImageInt64Atomics = VK_FALSE;//ָ��shader�Ƿ������image��ִ��64-bit �з����Լ��޷������� atomic operations
	physicalDeviceShaderImageAtomicInt64FeaturesEXT.sparseImageInt64Atomics = VK_FALSE;//ָ��shader�Ƿ������sparse images��ִ��64-bit �з����Լ��޷������� atomic operations


	// VkPhysicalDevice8BitStorageFeatures ,�ȼ���VkPhysicalDevice8BitStorageFeaturesKHR��  ���԰�����VkPhysicalDeviceFeatures2.pNext��
	VkPhysicalDevice8BitStorageFeatures   physicalDevice8BitStorageFeatures{};
	physicalDevice8BitStorageFeatures.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_8BIT_STORAGE_FEATURES;
	physicalDevice8BitStorageFeatures.pNext = nullptr;
	physicalDevice8BitStorageFeatures.storageBuffer8BitAccess = VK_FALSE;//ָ���Ƿ�StorageBuffer, ShaderRecordBufferKHR, ���� PhysicalStorageBuffer storage class����Block�����Ķ����Ƿ��ܹ�����8-bit��������Ա
	physicalDevice8BitStorageFeatures.uniformAndStorageBuffer8BitAccess = VK_FALSE;//ָ���Ƿ�Uniform storage class����Block�����Ķ����Ƿ��ܹ�����8-bit��������Ա
	physicalDevice8BitStorageFeatures.storagePushConstant8 = VK_FALSE;//ָ���Ƿ�PushConstant storage class�ܹ�����8-bit��������Ա


	//VkPhysicalDevice16BitStorageFeatures ���ȼ��� VkPhysicalDevice16BitStorageFeaturesKHR ,  ���԰�����VkPhysicalDeviceFeatures2.pNext��
	VkPhysicalDevice16BitStorageFeatures physicalDevice16BitStorageFeatures{};
	physicalDevice16BitStorageFeatures.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_16BIT_STORAGE_FEATURES;
	physicalDevice16BitStorageFeatures.pNext = nullptr;
	physicalDevice16BitStorageFeatures.storageBuffer16BitAccess = VK_FALSE;//ָ���Ƿ�StorageBuffer, ShaderRecordBufferKHR, ���� PhysicalStorageBuffer storage class����Block�����Ķ����Ƿ��ܹ�����16-bit�������Լ���������Ա
	physicalDevice16BitStorageFeatures.uniformAndStorageBuffer16BitAccess = VK_FALSE;//ָ���Ƿ�Uniform storage class����Block�����Ķ����Ƿ��ܹ�����16-bit�������Լ���������Ա
	physicalDevice16BitStorageFeatures.storagePushConstant16 = VK_FALSE;//ָ���Ƿ�PushConstant storage class�ܹ�����16-bit�������Լ���������Ա
	physicalDevice16BitStorageFeatures.storageInputOutput16 = VK_FALSE;//ָ���Ƿ� Input �Լ� Output storage classes�ܹ�����16-bit�������Լ���������Ա



	//VkPhysicalDeviceShaderFloat16Int8Features ���ȼ���VkPhysicalDeviceShaderFloat16Int8FeaturesKHR,  ���԰�����VkPhysicalDeviceFeatures2.pNext��
	VkPhysicalDeviceShaderFloat16Int8Features physicalDeviceShaderFloat16Int8Features{};
	physicalDeviceShaderFloat16Int8Features.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_FLOAT16_INT8_FEATURES;
	physicalDeviceShaderFloat16Int8Features.pNext = nullptr;
	physicalDeviceShaderFloat16Int8Features.shaderFloat16 = VK_FALSE;//ָ��shader code���Ƿ�֧��16-bit����
	physicalDeviceShaderFloat16Int8Features.shaderInt8 = VK_FALSE;//ָ��shader code���Ƿ�֧��8-bit�з����Լ��޷�������



	//VkPhysicalDeviceShaderClockFeaturesKHR�� ���԰�����VkPhysicalDeviceFeatures2.pNext��
	VkPhysicalDeviceShaderClockFeaturesKHR  physicalDeviceShaderClockFeaturesKHR{};
	physicalDeviceShaderClockFeaturesKHR.sType = VK_STRUCTURE_TYPE_MAX_ENUM;//û�ж����������ﶨ��Ϊ�Ƿ�ֵ
	physicalDeviceShaderClockFeaturesKHR.pNext = nullptr;
	physicalDeviceShaderClockFeaturesKHR.shaderSubgroupClock = VK_FALSE;//ָ��shaders���Խ���Subgroup scoped clock reads
	physicalDeviceShaderClockFeaturesKHR.shaderDeviceClock = VK_FALSE;//ָ��shaders���Խ���Device scoped clock reads.



	//VkPhysicalDeviceSamplerYcbcrConversionFeatures ���ȼ��� VkPhysicalDeviceSamplerYcbcrConversionFeaturesKHR ,  ���԰�����VkPhysicalDeviceFeatures2.pNext��
	VkPhysicalDeviceSamplerYcbcrConversionFeatures  physicalDeviceSamplerYcbcrConversionFeatures{};
	physicalDeviceSamplerYcbcrConversionFeatures.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SAMPLER_YCBCR_CONVERSION_FEATURES;
	physicalDeviceSamplerYcbcrConversionFeatures.pNext = nullptr;
	physicalDeviceSamplerYcbcrConversionFeatures.samplerYcbcrConversion = VK_FALSE;//ָ���Ƿ�֧��sampler YCbCr conversion,�����֧�ֵĻ��Ͳ���ʹ��sampler Y��CBCR conversion


	//VkPhysicalDeviceProtectedMemoryFeatures ,  ���԰�����VkPhysicalDeviceFeatures2.pNext��
	VkPhysicalDeviceProtectedMemoryFeatures physicalDeviceProtectedMemoryFeatures{};
	physicalDeviceProtectedMemoryFeatures.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PROTECTED_MEMORY_FEATURES;
	physicalDeviceProtectedMemoryFeatures.pNext = nullptr;
	physicalDeviceProtectedMemoryFeatures.protectedMemory = VK_FALSE;//ָ���Ƿ�֧��protected memory


	//VkPhysicalDeviceBlendOperationAdvancedFeaturesEXT  ,  ���԰�����VkPhysicalDeviceFeatures2.pNext��
	VkPhysicalDeviceBlendOperationAdvancedFeaturesEXT physicalDeviceBlendOperationAdvancedFeaturesEXT{};
	physicalDeviceBlendOperationAdvancedFeaturesEXT.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_BLEND_OPERATION_ADVANCED_FEATURES_EXT;
	physicalDeviceBlendOperationAdvancedFeaturesEXT.pNext = nullptr;
	physicalDeviceBlendOperationAdvancedFeaturesEXT.advancedBlendCoherentOperations = VK_FALSE;//ָ���Ƿ�ʹ�� advanced blend operations��blending������֤����primitive order ԭ����ִ�С����֧�֣�����ΪVK_ACCESS_COLOR_ATTACHMENT_READ_NONCOHERENT_BIT_EXT ��ͬ��VK_ACCESS_COLOR_ATTACHMENT_READ_BIT������Ҫ����ͬ���������֧������Ҫmemory dependencies


	//VkPhysicalDeviceConditionalRenderingFeaturesEXT ,  ���԰�����VkPhysicalDeviceFeatures2.pNext��
	VkPhysicalDeviceConditionalRenderingFeaturesEXT physicalDeviceConditionalRenderingFeaturesEXT{};
	physicalDeviceConditionalRenderingFeaturesEXT.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_CONDITIONAL_RENDERING_FEATURES_EXT;
	physicalDeviceConditionalRenderingFeaturesEXT.pNext = nullptr;
	physicalDeviceConditionalRenderingFeaturesEXT.conditionalRendering = VK_FALSE;//ָ���Ƿ�֧��conditional rendering
	physicalDeviceConditionalRenderingFeaturesEXT.inheritedConditionalRendering = VK_FALSE;//ָ������primary command buffer�м���conditional renderingʱ���Ƿ����ִ��secondary command buffer


	// VkPhysicalDeviceShaderDrawParametersFeatures ���ȼ��� VkPhysicalDeviceShaderDrawParameterFeatures ,  ���԰�����VkPhysicalDeviceFeatures2.pNext��
	VkPhysicalDeviceShaderDrawParametersFeatures physicalDeviceShaderDrawParametersFeatures{};
	physicalDeviceShaderDrawParametersFeatures.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_DRAW_PARAMETERS_FEATURES;
	physicalDeviceShaderDrawParametersFeatures.pNext = nullptr;
	physicalDeviceShaderDrawParametersFeatures.shaderDrawParameters = VK_FALSE;//ָ���Ƿ�֧��SPIR-V DrawParameters �����������֧�֣���shader module�в�������SPV_KHR_shader_draw_parameters ��չ�Լ� DrawParameters ������


	//VkPhysicalDeviceMeshShaderFeaturesNV  ��  ���԰�����VkPhysicalDeviceFeatures2.pNext��
	VkPhysicalDeviceMeshShaderFeaturesNV physicalDeviceMeshShaderFeaturesNV{};
	physicalDeviceMeshShaderFeaturesNV.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MESH_SHADER_FEATURES_EXT;
	physicalDeviceMeshShaderFeaturesNV.pNext = nullptr;
	physicalDeviceMeshShaderFeaturesNV.taskShader = VK_FALSE;//ָ���Ƿ�֧�� task shaders�������֧�֣�����ʹ��VK_SHADER_STAGE_TASK_BIT_NV �Լ� VK_PIPELINE_STAGE_TASK_SHADER_BIT_NV
	physicalDeviceMeshShaderFeaturesNV.meshShader = VK_FALSE;//ָ���Ƿ�֧�� mesh shaders�������֧�֣�����ʹ��VK_SHADER_STAGE_MESH_BIT_NV �Լ� VK_PIPELINE_STAGE_MESH_SHADER_BIT_NV


	//VkPhysicalDeviceMeshShaderFeaturesEXT ��  ���԰�����VkPhysicalDeviceFeatures2.pNext��
	VkPhysicalDeviceMeshShaderFeaturesEXT physicalDeviceMeshShaderFeaturesEXT{};
	physicalDeviceMeshShaderFeaturesEXT.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MESH_SHADER_PROPERTIES_EXT;
	physicalDeviceMeshShaderFeaturesEXT.pNext = nullptr;
	physicalDeviceMeshShaderFeaturesEXT.taskShader;//ָ���Ƿ�֧�� task shaders�������֧�֣�����ʹ��VK_SHADER_STAGE_TASK_BIT_EXT �Լ� VK_PIPELINE_STAGE_TASK_SHADER_BIT_EXT
	physicalDeviceMeshShaderFeaturesEXT.meshShader;//ָ���Ƿ�֧�� mesh shaders�������֧�֣�����ʹ��VK_SHADER_STAGE_MESH_BIT_EXT �Լ� VK_PIPELINE_STAGE_MESH_SHADER_BIT_EXT
	physicalDeviceMeshShaderFeaturesEXT.multiviewMeshShader;//ָ���Ƿ�֧����һ������mesh shaders�� render pass�н���multiview��Ⱦ�������֧�֣�����view mask��Ϊ0��pipeline���ܰ���mesh shaders�����������VkPhysicalDeviceMultiviewFeaturesKHR::multiview ���뿪��
	physicalDeviceMeshShaderFeaturesEXT.primitiveFragmentShadingRateMeshShader;//ָ��mesh shaders���Ƿ�֧��primitive fragment shading rate�����������VkPhysicalDeviceFragmentShadingRateFeaturesKHR::primitiveFragmentShadingRate ���뿪��
	physicalDeviceMeshShaderFeaturesEXT.meshShaderQueries;//ָ���Ƿ�֧��ʹ��VK_QUERY_TYPE_MESH_PRIMITIVES_GENERATED_EXT ����VkQueryPool�Լ� ֧��statistic queries�ܹ�����VK_QUERY_PIPELINE_STATISTIC_TASK_SHADER_INVOCATIONS_BIT_EXT �Լ�VK_QUERY_PIPELINE_STATISTIC_MESH_SHADER_INVOCATIONS_BIT_EXT


	//VkPhysicalDeviceMemoryDecompressionFeaturesNV ��  ���԰�����VkPhysicalDeviceFeatures2.pNext��
	VkPhysicalDeviceMemoryDecompressionFeaturesNV physicalDeviceMemoryDecompressionFeaturesNV{};
	physicalDeviceMemoryDecompressionFeaturesNV.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MEMORY_DECOMPRESSION_PROPERTIES_NV;
	physicalDeviceMemoryDecompressionFeaturesNV.pNext = nullptr;
	physicalDeviceMemoryDecompressionFeaturesNV.memoryDecompression = VK_FALSE;//ָ���Ƿ�֧��memory decompression


	//VkPhysicalDeviceDescriptorIndexingFeatures  ,  �ȼ���VkPhysicalDeviceDescriptorIndexingFeaturesEXT , ���԰�����VkPhysicalDeviceFeatures2.pNext��
	VkPhysicalDeviceDescriptorIndexingFeatures physicalDeviceDescriptorIndexingFeatures{};
	physicalDeviceDescriptorIndexingFeatures.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DESCRIPTOR_INDEXING_FEATURES;
	physicalDeviceDescriptorIndexingFeatures.pNext = nullptr;
	physicalDeviceDescriptorIndexingFeatures.shaderInputAttachmentArrayDynamicIndexing = VK_FALSE;//ָ��input attachments �����Ƿ������shader code��ͨ��һ��dynamically uniform integer expressions���з��ʣ������֧�֣���VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT ���͵���Դ����ֻ��ͨ���������ʽ���з���
	physicalDeviceDescriptorIndexingFeatures.shaderUniformTexelBufferArrayDynamicIndexing = VK_FALSE;//ָ��uniform texel buffers �����Ƿ������shader code��ͨ��һ��dynamically uniform integer expressions���з��ʣ������֧�֣���VK_DESCRIPTOR_TYPE_UNIFORM_TEXEL_BUFFER ���͵���Դ����ֻ��ͨ���������ʽ���з���
	physicalDeviceDescriptorIndexingFeatures.shaderStorageTexelBufferArrayDynamicIndexing = VK_FALSE;//ָ��storage texel buffers �����Ƿ������shader code��ͨ��һ��dynamically uniform integer expressions���з��ʣ������֧�֣���VK_DESCRIPTOR_TYPE_STORAGE_TEXEL_BUFFER ���͵���Դ����ֻ��ͨ���������ʽ���з���
	physicalDeviceDescriptorIndexingFeatures.shaderUniformBufferArrayNonUniformIndexing = VK_FALSE;//ָ�� uniform buffers �����Ƿ������shader code��ͨ��һ��non-uniform integer expressions���з��ʣ������֧�֣���VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER ���� VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC ���͵���Դ���鲻��ͨ��non-uniform integer expressions ���з���
	physicalDeviceDescriptorIndexingFeatures.shaderSampledImageArrayNonUniformIndexing = VK_FALSE;//ָ��samplers ���� sampled images �����Ƿ������shader code��ͨ��һ��non-uniform integer expressions���з��ʣ������֧�֣���VK_DESCRIPTOR_TYPE_SAMPLER, VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, ���� VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE���͵���Դ���鲻��ͨ��non-uniform integer expressions ���з���
	physicalDeviceDescriptorIndexingFeatures.shaderStorageBufferArrayNonUniformIndexing = VK_FALSE;//ָ�� storage buffers �����Ƿ������shader code��ͨ��һ��non-uniform integer expressions���з��ʣ������֧�֣���VK_DESCRIPTOR_TYPE_STORAGE_BUFFER ���� VK_DESCRIPTOR_TYPE_STORAGE_BUFFER_DYNAMIC ���͵���Դ���鲻��ͨ��non-uniform integer expressions ���з���
	physicalDeviceDescriptorIndexingFeatures.shaderStorageImageArrayNonUniformIndexing = VK_FALSE;//ָ�� storage images �����Ƿ������shader code��ͨ��һ��non-uniform integer expressions���з��ʣ������֧�֣���VK_DESCRIPTOR_TYPE_STORAGE_IMAGE ���͵���Դ���鲻��ͨ��non-uniform integer expressions ���з���
	physicalDeviceDescriptorIndexingFeatures.shaderInputAttachmentArrayNonUniformIndexing = VK_FALSE;//ָ�� input attachments �����Ƿ������shader code��ͨ��һ��non-uniform integer expressions���з��ʣ������֧�֣���VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT ���͵���Դ���鲻��ͨ��non-uniform integer expressions ���з���
	physicalDeviceDescriptorIndexingFeatures.shaderUniformTexelBufferArrayNonUniformIndexing = VK_FALSE;//ָ�� uniform texel buffers �����Ƿ������shader code��ͨ��һ��non-uniform integer expressions���з��ʣ������֧�֣���VK_DESCRIPTOR_TYPE_UNIFORM_TEXEL_BUFFER ���͵���Դ���鲻��ͨ��non-uniform integer expressions ���з���
	physicalDeviceDescriptorIndexingFeatures.shaderStorageTexelBufferArrayNonUniformIndexing = VK_FALSE;//ָ�� storage texel buffers �����Ƿ������shader code��ͨ��һ��non-uniform integer expressions���з��ʣ������֧�֣���VK_DESCRIPTOR_TYPE_STORAGE_TEXEL_BUFFER ���͵���Դ���鲻��ͨ��non-uniform integer expressions ���з���
	physicalDeviceDescriptorIndexingFeatures.descriptorBindingUniformBufferUpdateAfterBind = VK_FALSE;//ָ���Ƿ�֧���ڰ�һ��descriptor set֮�����uniform buffer descriptors�������֧�֣���VK_DESCRIPTOR_BINDING_UPDATE_AFTER_BIND_BIT���ܺ� VK_DESCRIPTOR_TYPE_UNIFORM_BUFFERһ��ʹ��
	physicalDeviceDescriptorIndexingFeatures.descriptorBindingSampledImageUpdateAfterBind = VK_FALSE;//ָ���Ƿ�֧���ڰ�һ��descriptor set֮�����sampled image descriptors�������֧�֣���VK_DESCRIPTOR_BINDING_UPDATE_AFTER_BIND_BIT���ܺ� VK_DESCRIPTOR_TYPE_SAMPLER, VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, ����VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE һ��ʹ��
	physicalDeviceDescriptorIndexingFeatures.descriptorBindingStorageImageUpdateAfterBind = VK_FALSE;//ָ���Ƿ�֧���ڰ�һ��descriptor set֮�����storage image descriptors�������֧�֣���VK_DESCRIPTOR_BINDING_UPDATE_AFTER_BIND_BIT���ܺ� VK_DESCRIPTOR_TYPE_STORAGE_IMAGEһ��ʹ��
	physicalDeviceDescriptorIndexingFeatures.descriptorBindingStorageBufferUpdateAfterBind = VK_FALSE;//ָ���Ƿ�֧���ڰ�һ��descriptor set֮�����storage buffer descriptors�������֧�֣���VK_DESCRIPTOR_BINDING_UPDATE_AFTER_BIND_BIT���ܺ� VK_DESCRIPTOR_TYPE_STORAGE_BUFFERһ��ʹ��
	physicalDeviceDescriptorIndexingFeatures.descriptorBindingUniformTexelBufferUpdateAfterBind = VK_FALSE;//ָ���Ƿ�֧���ڰ�һ��descriptor set֮�����uniform texel buffer descriptors�������֧�֣���VK_DESCRIPTOR_BINDING_UPDATE_AFTER_BIND_BIT���ܺ� VK_DESCRIPTOR_TYPE_UNIFORM_TEXEL_BUFFERһ��ʹ��
	physicalDeviceDescriptorIndexingFeatures.descriptorBindingStorageTexelBufferUpdateAfterBind = VK_FALSE;//ָ���Ƿ�֧���ڰ�һ��descriptor set֮�����storage texel buffer descriptors�������֧�֣���VK_DESCRIPTOR_BINDING_UPDATE_AFTER_BIND_BIT���ܺ� VK_DESCRIPTOR_TYPE_STORAGE_TEXEL_BUFFERһ��ʹ��
	physicalDeviceDescriptorIndexingFeatures.descriptorBindingUpdateUnusedWhilePending = VK_FALSE;//ָ���Ƿ�֧����descriptor set����ʹ�õ�ʱ�����descriptors�������֧������ʹ��VK_DESCRIPTOR_BINDING_UPDATE_UNUSED_WHILE_PENDING_BIT
	physicalDeviceDescriptorIndexingFeatures.descriptorBindingPartiallyBound = VK_FALSE;//ָ���Ƿ�֧�־�̬ʹ��һ������descriptor��Ч��descriptor set binding�������֧������ʹ��VK_DESCRIPTOR_BINDING_PARTIALLY_BOUND_BIT
	physicalDeviceDescriptorIndexingFeatures.descriptorBindingVariableDescriptorCount = VK_FALSE;//ָ���Ƿ�֧��descriptor sets�����һ��binding�Ǵ�С�ɱ�ģ������֧������ʹ��VK_DESCRIPTOR_BINDING_VARIABLE_DESCRIPTOR_COUNT_BIT
	physicalDeviceDescriptorIndexingFeatures.runtimeDescriptorArray = VK_FALSE;//ָ���Ƿ�֧�� SPIR-V RuntimeDescriptorArray����

	
	//VkPhysicalDeviceCopyMemoryIndirectFeaturesNV,   ���԰�����VkPhysicalDeviceFeatures2.pNext��
	VkPhysicalDeviceCopyMemoryIndirectFeaturesNV  physicalDeviceCopyMemoryIndirectFeaturesNV{};
	physicalDeviceCopyMemoryIndirectFeaturesNV.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_COPY_MEMORY_INDIRECT_FEATURES_NV;
	physicalDeviceCopyMemoryIndirectFeaturesNV.pNext = nullptr;
	physicalDeviceCopyMemoryIndirectFeaturesNV.indirectCopy = VK_FALSE;//ָ���Ƿ�֧�� indirect copies


	//VkPhysicalDeviceVertexAttributeDivisorFeaturesKHR  ,�ȼ��� VkPhysicalDeviceVertexAttributeDivisorFeaturesEXT��    ���԰�����VkPhysicalDeviceFeatures2.pNext��
	VkPhysicalDeviceVertexAttributeDivisorFeaturesKHR physicalDeviceVertexAttributeDivisorFeaturesKHR{};
	physicalDeviceVertexAttributeDivisorFeaturesKHR.sType = VK_STRUCTURE_TYPE_MAX_ENUM;//û�ж������ﶨ��Ϊ�Ƿ�ֵ
	physicalDeviceVertexAttributeDivisorFeaturesKHR.pNext = nullptr;
	physicalDeviceVertexAttributeDivisorFeaturesKHR.vertexAttributeInstanceRateDivisor = VK_FALSE;//ָ���Ƿ���instance rendering�� vertex attribute���ܻᱻ�ظ���ȡ
	physicalDeviceVertexAttributeDivisorFeaturesKHR.vertexAttributeInstanceRateZeroDivisor = VK_FALSE;//ָ���Ƿ�֧��VkVertexInputBindingDivisorDescriptionEXT::divisorΪ0


	// VkPhysicalDeviceASTCDecodeFeaturesEXT ��    ���԰�����VkPhysicalDeviceFeatures2.pNext�� 
	VkPhysicalDeviceASTCDecodeFeaturesEXT  physicalDeviceASTCDecodeFeaturesEXT{};
	physicalDeviceASTCDecodeFeaturesEXT.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_ASTC_DECODE_FEATURES_EXT;
	physicalDeviceASTCDecodeFeaturesEXT.pNext = nullptr;
	physicalDeviceASTCDecodeFeaturesEXT.decodeModeSharedExponent = VK_FALSE;//ָ���Ƿ�֧�ֽ�ѹASTC ѹ����ʽ��VK_FORMAT_E5B9G9R9_UFLOAT_PACK32


	//VkPhysicalDeviceTransformFeedbackFeaturesEXT  ��    ���԰�����VkPhysicalDeviceFeatures2.pNext�� 
	VkPhysicalDeviceTransformFeedbackFeaturesEXT physicalDeviceTransformFeedbackFeaturesEXT{};
	physicalDeviceTransformFeedbackFeaturesEXT.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_TRANSFORM_FEEDBACK_FEATURES_EXT;
	physicalDeviceTransformFeedbackFeaturesEXT.pNext = nullptr;
	physicalDeviceTransformFeedbackFeaturesEXT.transformFeedback = VK_FALSE;//ָ���Ƿ�֧��transform feedback��shader module�п����Ƿ�����TransformFeedback ����
	physicalDeviceTransformFeedbackFeaturesEXT.geometryStreams = VK_FALSE;//ָ���Ƿ�֧��GeometryStreams SPIR-V ����


	//VkPhysicalDeviceVulkanMemoryModelFeatures   �� �ȼ���VkPhysicalDeviceVulkanMemoryModelFeaturesKHR�����԰�����VkPhysicalDeviceFeatures2.pNext�� 
	VkPhysicalDeviceVulkanMemoryModelFeatures physicalDeviceVulkanMemoryModelFeatures{};
	physicalDeviceVulkanMemoryModelFeatures.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_MEMORY_MODEL_FEATURES;
	physicalDeviceVulkanMemoryModelFeatures.pNext = nullptr;
	physicalDeviceVulkanMemoryModelFeatures.vulkanMemoryModel = VK_FALSE;//ָ���Ƿ�shader module�������� VulkanMemoryModel����
	physicalDeviceVulkanMemoryModelFeatures.vulkanMemoryModelDeviceScope = VK_FALSE;//ָ���Ƿ�Vulkan Memory Mode����ʹ�� Device scope synchronization��Ҳָ���Ƿ�shader module��������VulkanMemoryModelDeviceScope ����
	physicalDeviceVulkanMemoryModelFeatures.vulkanMemoryModelAvailabilityVisibilityChains = VK_FALSE;//ָ���Ƿ� Vulkan Memory Model����ʹ�ó���һ��Ԫ�ص� availability and visibility chains


	//VkPhysicalDeviceInlineUniformBlockFeatures  , �ȼ���VkPhysicalDeviceInlineUniformBlockFeaturesEXT�����԰�����VkPhysicalDeviceFeatures2.pNext�� 
	VkPhysicalDeviceInlineUniformBlockFeatures physicalDeviceInlineUniformBlockFeatures{};
	physicalDeviceInlineUniformBlockFeatures.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_INLINE_UNIFORM_BLOCK_FEATURES_EXT;
	physicalDeviceInlineUniformBlockFeatures.pNext = nullptr;
	physicalDeviceInlineUniformBlockFeatures.inlineUniformBlock = VK_FALSE;//ָ���Ƿ�֧��inline uniform block descriptor�������֧�֣�����ʹ�� VK_DESCRIPTOR_TYPE_INLINE_UNIFORM_BLOCK
	physicalDeviceInlineUniformBlockFeatures.descriptorBindingInlineUniformBlockUpdateAfterBind = VK_FALSE;//ָ���Ƿ�֧���ڰ�һ��descriptor set֮�����inline uniform block descriptors�������֧�֣���VK_DESCRIPTOR_BINDING_UPDATE_AFTER_BIND_BIT���ܺ� VK_DESCRIPTOR_TYPE_INLINE_UNIFORM_BLOCKһ��ʹ��


	//VkPhysicalDeviceRepresentativeFragmentTestFeaturesNV �����԰�����VkPhysicalDeviceFeatures2.pNext�� 
	VkPhysicalDeviceRepresentativeFragmentTestFeaturesNV physicalDeviceRepresentativeFragmentTestFeaturesNV{};
	physicalDeviceRepresentativeFragmentTestFeaturesNV.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_REPRESENTATIVE_FRAGMENT_TEST_FEATURES_NV;
	physicalDeviceRepresentativeFragmentTestFeaturesNV.pNext = nullptr;
	physicalDeviceRepresentativeFragmentTestFeaturesNV.representativeFragmentTest = VK_FALSE;//ָ���Ƿ�֧��representative fragment test�� ��Representative Fragment Test. p2804


	//VkPhysicalDeviceExclusiveScissorFeaturesNV  �����԰�����VkPhysicalDeviceFeatures2.pNext�� 
	VkPhysicalDeviceExclusiveScissorFeaturesNV physicalDeviceExclusiveScissorFeaturesNV{};
	physicalDeviceExclusiveScissorFeaturesNV.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_EXCLUSIVE_SCISSOR_FEATURES_NV;
	physicalDeviceExclusiveScissorFeaturesNV.pNext = nullptr;
	physicalDeviceExclusiveScissorFeaturesNV.exclusiveScissor = VK_FALSE;//ָ���Ƿ�֧�� exclusive scissor test


	//VkPhysicalDeviceCornerSampledImageFeaturesNV   �����԰�����VkPhysicalDeviceFeatures2.pNext�� 
	VkPhysicalDeviceCornerSampledImageFeaturesNV physicalDeviceCornerSampledImageFeaturesNV{};
	physicalDeviceCornerSampledImageFeaturesNV.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_CORNER_SAMPLED_IMAGE_FEATURES_NV;
	physicalDeviceCornerSampledImageFeaturesNV.pNext = nullptr;
	physicalDeviceCornerSampledImageFeaturesNV.cornerSampledImage = VK_FALSE;//ָ��image�Ƿ������ VkImageCreateInfo::flags���� VK_IMAGE_CREATE_CORNER_SAMPLED_BIT_NV ��������p1077  Corner-Sampled Images.


	//VkPhysicalDeviceComputeShaderDerivativesFeaturesNV�����԰�����VkPhysicalDeviceFeatures2.pNext�� 
	VkPhysicalDeviceComputeShaderDerivativesFeaturesNV  physicalDeviceComputeShaderDerivativesFeaturesNV{};
	physicalDeviceComputeShaderDerivativesFeaturesNV.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_COMPUTE_SHADER_DERIVATIVES_FEATURES_NV;
	physicalDeviceComputeShaderDerivativesFeaturesNV.pNext = nullptr;
	physicalDeviceComputeShaderDerivativesFeaturesNV.computeDerivativeGroupQuads = VK_FALSE;//ָ���Ƿ�֧��ComputeDerivativeGroupQuadsNV SPIR-V ����
	physicalDeviceComputeShaderDerivativesFeaturesNV.computeDerivativeGroupLinear = VK_FALSE;//ָ���Ƿ�֧��ComputeDerivativeGroupLinearNV SPIR-V ����



	//VkPhysicalDeviceFragmentShaderBarycentricFeaturesKHR�� �ȼ���VkPhysicalDeviceFragmentShaderBarycentricFeaturesNV   , ���԰�����VkPhysicalDeviceFeatures2.pNext�� 
	VkPhysicalDeviceFragmentShaderBarycentricFeaturesKHR  physicalDeviceFragmentShaderBarycentricFeaturesKHR{};
	physicalDeviceFragmentShaderBarycentricFeaturesKHR.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FRAGMENT_SHADER_BARYCENTRIC_FEATURES_KHR;
	physicalDeviceFragmentShaderBarycentricFeaturesKHR.pNext = nullptr;
	physicalDeviceFragmentShaderBarycentricFeaturesKHR.fragmentShaderBarycentric = VK_FALSE;//ָ��fragment shader���Ƿ�֧��BaryCoordKHR �Լ� BaryCoordNoPerspKHR ���ñ����Լ�֧���� PerVertexKHR SPIR - V����shader �������


	//VkPhysicalDeviceShaderImageFootprintFeaturesNV , ���԰�����VkPhysicalDeviceFeatures2.pNext�� 
	VkPhysicalDeviceShaderImageFootprintFeaturesNV  physicalDeviceShaderImageFootprintFeaturesNV{};
	physicalDeviceShaderImageFootprintFeaturesNV.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_IMAGE_FOOTPRINT_FEATURES_NV;
	physicalDeviceShaderImageFootprintFeaturesNV.pNext = nullptr;
	physicalDeviceShaderImageFootprintFeaturesNV.imageFootprint = VK_FALSE;//ָ���Ƿ�֧��ImageFootprintNV SPIR-V ����


	//VkPhysicalDeviceShadingRateImageFeaturesNV�����԰�����VkPhysicalDeviceFeatures2.pNext�� 
	VkPhysicalDeviceShadingRateImageFeaturesNV  physicalDeviceShadingRateImageFeaturesNV{};
	physicalDeviceShadingRateImageFeaturesNV.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADING_RATE_IMAGE_FEATURES_NV;
	physicalDeviceShadingRateImageFeaturesNV.pNext = nullptr;
	physicalDeviceShadingRateImageFeaturesNV.shadingRateImage = VK_FALSE;//ָ���Ƿ����ʹ��һ��shading rate image������fragment processing��һ����Ч��shading rate��Ҳָ���Ƿ�֧��ShadingRateNV SPIR-V execution mode
	physicalDeviceShadingRateImageFeaturesNV.shadingRateCoarseSampleOrder = VK_FALSE;//ָ���ں��ж��pixel��fragment���Ƿ�֧���û���coverage sample��˳���Զ���


	//VkPhysicalDeviceFragmentDensityMapFeaturesEXT�����԰�����VkPhysicalDeviceFeatures2.pNext�� 
	VkPhysicalDeviceFragmentDensityMapFeaturesEXT  physicalDeviceFragmentDensityMapFeaturesEXT{};
	physicalDeviceFragmentDensityMapFeaturesEXT.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FRAGMENT_DENSITY_MAP_FEATURES_EXT;
	physicalDeviceFragmentDensityMapFeaturesEXT.pNext = nullptr;
	physicalDeviceFragmentDensityMapFeaturesEXT.fragmentDensityMap = VK_FALSE;//ָ���Ƿ�֧��render pass����һ��fragment density map attachment
	physicalDeviceFragmentDensityMapFeaturesEXT.fragmentDensityMapDynamic = VK_FALSE;//ָ���Ƿ�֧�ֶ�̬��fragment density map image views �������֧�֣���VkImageViewCreateInfo::flags�в��ܰ���VK_IMAGE_VIEW_CREATE_FRAGMENT_DENSITY_MAP_DYNAMIC_BIT_EXT
	physicalDeviceFragmentDensityMapFeaturesEXT.fragmentDensityMapNonSubsampledImages = VK_FALSE;//ָ����һ��fragment density map render pass���Ƿ����֧��non-subsampled image attachments�������֧����һ��fragment density map attachment ��render pass�����һ��subsampled attachments



	// VkPhysicalDeviceFragmentDensityMap2FeaturesEXT , ���԰�����VkPhysicalDeviceFeatures2.pNext�� 
	VkPhysicalDeviceFragmentDensityMap2FeaturesEXT   physicalDeviceFragmentDensityMap2FeaturesEXT{};
	physicalDeviceFragmentDensityMap2FeaturesEXT.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FRAGMENT_DENSITY_MAP_2_FEATURES_EXT;
	physicalDeviceFragmentDensityMap2FeaturesEXT.pNext = nullptr;
	physicalDeviceFragmentDensityMap2FeaturesEXT.fragmentDensityMapDeferred = VK_FALSE;//ָ���Ƿ�֧�ֶ�fragment density map image views���ӳٶ�ȡ �������֧�֣���VkImageViewCreateInfo::flags�в��ܰ���VK_IMAGE_VIEW_CREATE_FRAGMENT_DENSITY_MAP_DEFERRED_BIT_EXT


	// VkPhysicalDeviceFragmentDensityMapOffsetFeaturesQCOM , ���԰�����VkPhysicalDeviceFeatures2.pNext�� 
	VkPhysicalDeviceFragmentDensityMapOffsetFeaturesQCOM   physicalDeviceFragmentDensityMapOffsetFeaturesQCOM{};
	physicalDeviceFragmentDensityMapOffsetFeaturesQCOM.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FRAGMENT_DENSITY_MAP_OFFSET_FEATURES_QCOM;
	physicalDeviceFragmentDensityMapOffsetFeaturesQCOM.pNext = nullptr;
	physicalDeviceFragmentDensityMapOffsetFeaturesQCOM.fragmentDensityMapOffset = VK_FALSE;//ָ���Ƿ�֧��fragment density map offsets


	// VkPhysicalDeviceInvocationMaskFeaturesHUAWEI , ���԰�����VkPhysicalDeviceFeatures2.pNext�� 
	VkPhysicalDeviceInvocationMaskFeaturesHUAWEI   physicalDeviceInvocationMaskFeaturesHUAWEI{};
	physicalDeviceInvocationMaskFeaturesHUAWEI.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_INVOCATION_MASK_FEATURES_HUAWEI;
	physicalDeviceInvocationMaskFeaturesHUAWEI.pNext = nullptr;
	physicalDeviceInvocationMaskFeaturesHUAWEI.invocationMask = VK_FALSE;//ָ���Ƿ����ʹ��һ��invocation mask image ���Ż� ray dispatch.


	//VkPhysicalDeviceScalarBlockLayoutFeatures�� �ȼ���VkPhysicalDeviceScalarBlockLayoutFeaturesEXT   , ���԰�����VkPhysicalDeviceFeatures2.pNext�� 
	VkPhysicalDeviceScalarBlockLayoutFeatures  physicalDeviceScalarBlockLayoutFeatures{};
	physicalDeviceScalarBlockLayoutFeatures.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SCALAR_BLOCK_LAYOUT_FEATURES;
	physicalDeviceScalarBlockLayoutFeatures.pNext = nullptr;
	physicalDeviceScalarBlockLayoutFeatures.scalarBlockLayout = VK_FALSE;//ָ���Ƿ�shader����Դ���layout�ܷ�ʹ�� scalar alignment


	//VkPhysicalDeviceUniformBufferStandardLayoutFeatures�� �ȼ���VkPhysicalDeviceUniformBufferStandardLayoutFeaturesKHR   , ���԰�����VkPhysicalDeviceFeatures2.pNext�� 
	VkPhysicalDeviceUniformBufferStandardLayoutFeatures  physicalDeviceUniformBufferStandardLayoutFeatures{};
	physicalDeviceUniformBufferStandardLayoutFeatures.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_UNIFORM_BUFFER_STANDARD_LAYOUT_FEATURES;
	physicalDeviceUniformBufferStandardLayoutFeatures.pNext = nullptr;
	physicalDeviceUniformBufferStandardLayoutFeatures.uniformBufferStandardLayout = VK_FALSE;//ָ���Ƿ�֧��uniform buffers��Ϊstorage �����������͵�buffer��ʱ��ʹ����ͬ��layout


	// VkPhysicalDeviceDepthClipEnableFeaturesEXT , ���԰�����VkPhysicalDeviceFeatures2.pNext�� 
	VkPhysicalDeviceDepthClipEnableFeaturesEXT   physicalDeviceDepthClipEnableFeaturesEXT{};
	physicalDeviceDepthClipEnableFeaturesEXT.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DEPTH_CLIP_ENABLE_FEATURES_EXT;
	physicalDeviceDepthClipEnableFeaturesEXT.pNext = nullptr;
	physicalDeviceDepthClipEnableFeaturesEXT.depthClipEnable = VK_FALSE;//ָ���Ƿ�֧��ʹ�� VkPipelineRasterizationDepthClipStateCreateInfoEXT ����ʽ���� depth clipping operation�������֧���� VkPipelineRasterizationStateCreateInfo::depthClampEnable ����ΪVK_FALSE


	// VkPhysicalDeviceMemoryPriorityFeaturesEXT , ���԰�����VkPhysicalDeviceFeatures2.pNext�� 
	VkPhysicalDeviceMemoryPriorityFeaturesEXT   physicalDeviceMemoryPriorityFeaturesEXT{};
	physicalDeviceMemoryPriorityFeaturesEXT.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MEMORY_PRIORITY_FEATURES_EXT;
	physicalDeviceMemoryPriorityFeaturesEXT.pNext = nullptr;
	physicalDeviceMemoryPriorityFeaturesEXT.memoryPriority = VK_FALSE;//ָ���Ƿ�֧��ʹ��  VkMemoryPriorityAllocateInfoEXT �ڷ���memory��ʱ��ָ��memory priorities



	//VkPhysicalDeviceBufferDeviceAddressFeatures  �� �ȼ���VkPhysicalDeviceBufferDeviceAddressFeaturesKHR�����԰�����VkPhysicalDeviceFeatures2.pNext�� 
	VkPhysicalDeviceBufferDeviceAddressFeatures  physicalDeviceBufferDeviceAddressFeatures{};
	physicalDeviceBufferDeviceAddressFeatures.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_BUFFER_DEVICE_ADDRESS_FEATURES;
	physicalDeviceBufferDeviceAddressFeatures.pNext = nullptr;
	physicalDeviceBufferDeviceAddressFeatures.bufferDeviceAddress = VK_FALSE;//ָ���Ƿ�֧����shader�з���ͨ�� vkGetBufferDeviceAddress��ȡ���ڴ��ַ��Ϊstorage buffers���з���
	physicalDeviceBufferDeviceAddressFeatures.bufferDeviceAddressCaptureReplay = VK_FALSE;//ָ��ʵ��֧�ֱ��������buffer �Լ� device addresses
	physicalDeviceBufferDeviceAddressFeatures.bufferDeviceAddressMultiDevice = VK_FALSE;//ָ��ʵ��֧�����Զ������豸�������߼��豸��֧��bufferDeviceAddress , rayTracingPipeline �Լ� rayQuery ����

	
	//VkPhysicalDeviceBufferDeviceAddressFeaturesEXT  �� �ȼ���VkPhysicalDeviceBufferAddressFeaturesEXT�����԰�����VkPhysicalDeviceFeatures2.pNext�� 
	VkPhysicalDeviceBufferDeviceAddressFeaturesEXT  physicalDeviceBufferDeviceAddressFeaturesEXT{};
	physicalDeviceBufferDeviceAddressFeaturesEXT.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_BUFFER_DEVICE_ADDRESS_FEATURES_EXT;
	physicalDeviceBufferDeviceAddressFeaturesEXT.pNext = nullptr;
	physicalDeviceBufferDeviceAddressFeaturesEXT.bufferDeviceAddress = VK_FALSE;//ָ���Ƿ�֧����shader�з���ͨ�� vkGetBufferDeviceAddressEXT��ȡ���ڴ��ַ��Ϊstorage buffers���з���
	physicalDeviceBufferDeviceAddressFeaturesEXT.bufferDeviceAddressCaptureReplay = VK_FALSE;//ָ��ʵ��֧�ֱ��������buffer �Լ� device addresses
	physicalDeviceBufferDeviceAddressFeaturesEXT.bufferDeviceAddressMultiDevice = VK_FALSE;//ָ��ʵ��֧�����Զ������豸�������߼��豸��֧��bufferDeviceAddress ����,�����֧�֣��������Զ������豸�������߼��豸�ϲ�ѯ�ڴ��ַ


	// VkPhysicalDeviceDedicatedAllocationImageAliasingFeaturesNV , ���԰�����VkPhysicalDeviceFeatures2.pNext�� 
	VkPhysicalDeviceDedicatedAllocationImageAliasingFeaturesNV   physicalDeviceDedicatedAllocationImageAliasingFeaturesNV{};
	physicalDeviceDedicatedAllocationImageAliasingFeaturesNV.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DEDICATED_ALLOCATION_IMAGE_ALIASING_FEATURES_NV;
	physicalDeviceDedicatedAllocationImageAliasingFeaturesNV.pNext = nullptr;
	physicalDeviceDedicatedAllocationImageAliasingFeaturesNV.dedicatedAllocationImageAliasing = VK_FALSE;//ָ���Ƿ���Զ�һ�����ݵ���ר�з��� dedicated allocation��image����ȡ����


	//VkPhysicalDeviceImagelessFramebufferFeatures�� �ȼ���VkPhysicalDeviceImagelessFramebufferFeaturesKHR   , ���԰�����VkPhysicalDeviceFeatures2.pNext�� 
	VkPhysicalDeviceImagelessFramebufferFeatures  physicalDeviceImagelessFramebufferFeatures{};
	physicalDeviceImagelessFramebufferFeatures.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_IMAGELESS_FRAMEBUFFER_FEATURES;
	physicalDeviceImagelessFramebufferFeatures.pNext = nullptr;
	physicalDeviceImagelessFramebufferFeatures.imagelessFramebuffer = VK_FALSE;//ָ���Ƿ�֧����render pass��ʼ��ʱ��ͨ�� VkRenderPassAttachmentBeginInfo ָ��������image view


	//VkPhysicalDeviceFragmentShaderInterlockFeaturesEXT �����԰�����VkPhysicalDeviceFeatures2.pNext�� 
	VkPhysicalDeviceFragmentShaderInterlockFeaturesEXT  physicalDeviceFragmentShaderInterlockFeaturesEXT{};
	physicalDeviceFragmentShaderInterlockFeaturesEXT.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FRAGMENT_SHADER_INTERLOCK_FEATURES_EXT;
	physicalDeviceFragmentShaderInterlockFeaturesEXT.pNext = nullptr;
	physicalDeviceFragmentShaderInterlockFeaturesEXT.fragmentShaderSampleInterlock = VK_FALSE;//ָ���Ƿ�֧��FragmentShaderSampleInterlockEXT SPIR-V ����
	physicalDeviceFragmentShaderInterlockFeaturesEXT.fragmentShaderPixelInterlock = VK_FALSE;//ָ���Ƿ�֧��FragmentShaderPixelInterlockEXT SPIR-V ����
	physicalDeviceFragmentShaderInterlockFeaturesEXT.fragmentShaderShadingRateInterlock = VK_FALSE;//ָ���Ƿ�֧��FragmentShaderShadingRateInterlockEXT SPIR-V ����



	//VkPhysicalDeviceCooperativeMatrixFeaturesNV �����԰�����VkPhysicalDeviceFeatures2.pNext�� 
	VkPhysicalDeviceCooperativeMatrixFeaturesNV  physicalDeviceCooperativeMatrixFeaturesNV{};
	physicalDeviceCooperativeMatrixFeaturesNV.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_COOPERATIVE_MATRIX_PROPERTIES_NV;
	physicalDeviceCooperativeMatrixFeaturesNV.pNext = nullptr;
	physicalDeviceCooperativeMatrixFeaturesNV.cooperativeMatrix = VK_FALSE;//ָ���Ƿ�֧�� CooperativeMatrixNV SPIR-V ����
	physicalDeviceCooperativeMatrixFeaturesNV.cooperativeMatrixRobustBufferAccess = VK_FALSE;//ָ���Ƿ�֧����SPIR-V OpCooperativeMatrixLoadNV �Լ� OpCooperativeMatrixStoreNVָ�����robust buffer


	//VkPhysicalDeviceCooperativeMatrixFeaturesKHR �����԰�����VkPhysicalDeviceFeatures2.pNext�� 
	VkPhysicalDeviceCooperativeMatrixFeaturesKHR  physicalDeviceCooperativeMatrixFeaturesKHR{};
	physicalDeviceCooperativeMatrixFeaturesKHR.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_COOPERATIVE_MATRIX_PROPERTIES_KHR;
	physicalDeviceCooperativeMatrixFeaturesKHR.pNext = nullptr;
	physicalDeviceCooperativeMatrixFeaturesKHR.cooperativeMatrix = VK_FALSE;//ָ���Ƿ�֧�� CooperativeMatrixKHR SPIR-V ����
	physicalDeviceCooperativeMatrixFeaturesKHR.cooperativeMatrixRobustBufferAccess = VK_FALSE;//ָ���Ƿ�֧����SPIR-V OpCooperativeMatrixLoadKHR �Լ� OpCooperativeMatrixStoreKHRָ�����robust buffer


	//VkPhysicalDeviceYcbcrImageArraysFeaturesEXT �����԰�����VkPhysicalDeviceFeatures2.pNext�� 
	VkPhysicalDeviceYcbcrImageArraysFeaturesEXT  physicalDeviceYcbcrImageArraysFeaturesEXT{};
	physicalDeviceYcbcrImageArraysFeaturesEXT.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_YCBCR_IMAGE_ARRAYS_FEATURES_EXT;
	physicalDeviceYcbcrImageArraysFeaturesEXT.pNext = nullptr;
	physicalDeviceYcbcrImageArraysFeaturesEXT.ycbcrImageArrays = VK_FALSE;//ָ���Ƿ�֧�ִ���һ����array layer��image����image��format��ҪY��CBCR conversion


	//VkPhysicalDeviceShaderSubgroupExtendedTypesFeatures ���ȼ���VkPhysicalDeviceShaderSubgroupExtendedTypesFeaturesKHR �����԰�����VkPhysicalDeviceFeatures2.pNext�� 
	VkPhysicalDeviceShaderSubgroupExtendedTypesFeatures  physicalDeviceShaderSubgroupExtendedTypesFeatures{};
	physicalDeviceShaderSubgroupExtendedTypesFeatures.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_SUBGROUP_EXTENDED_TYPES_FEATURES;
	physicalDeviceShaderSubgroupExtendedTypesFeatures.pNext = nullptr;
	physicalDeviceShaderSubgroupExtendedTypesFeatures.shaderSubgroupExtendedTypes = VK_FALSE;//ָ�� subgroup operations �Ƿ����ʹ�� 8-bit integer, 16-bit integer, 64-bit integer, 16-bit floating point,�Լ���Щ���͵�vecֵ�������Щ����֧�ֵĻ�


	//VkPhysicalDeviceHostQueryResetFeatures ���ȼ���VkPhysicalDeviceHostQueryResetFeaturesEXT �����԰�����VkPhysicalDeviceFeatures2.pNext�� 
	VkPhysicalDeviceHostQueryResetFeatures  physicalDeviceHostQueryResetFeatures{};
	physicalDeviceHostQueryResetFeatures.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_SUBGROUP_EXTENDED_TYPES_FEATURES;
	physicalDeviceHostQueryResetFeatures.pNext = nullptr;
	physicalDeviceHostQueryResetFeatures.hostQueryReset = VK_FALSE;//ָ���Ƿ������host����vkResetQueryPool����query


	//VkPhysicalDeviceShaderIntegerFunctions2FeaturesINTEL �����԰�����VkPhysicalDeviceFeatures2.pNext�� 
	VkPhysicalDeviceShaderIntegerFunctions2FeaturesINTEL  physicalDeviceShaderIntegerFunctions2FeaturesINTEL{};
	physicalDeviceShaderIntegerFunctions2FeaturesINTEL.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_INTEGER_FUNCTIONS_2_FEATURES_INTEL;
	physicalDeviceShaderIntegerFunctions2FeaturesINTEL.pNext = nullptr;
	physicalDeviceShaderIntegerFunctions2FeaturesINTEL.shaderIntegerFunctions2 = VK_FALSE;///ָ���Ƿ�֧��  IntegerFunctions2INTEL SPIR-V ����


	//VkPhysicalDeviceCoverageReductionModeFeaturesNV �����԰�����VkPhysicalDeviceFeatures2.pNext�� 
	VkPhysicalDeviceCoverageReductionModeFeaturesNV  physicalDeviceCoverageReductionModeFeaturesNV{};
	physicalDeviceCoverageReductionModeFeaturesNV.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_COVERAGE_REDUCTION_MODE_FEATURES_NV;
	physicalDeviceCoverageReductionModeFeaturesNV.pNext = nullptr;
	physicalDeviceCoverageReductionModeFeaturesNV.coverageReductionMode = VK_FALSE;//ָ���Ƿ�֧��  coverage reduction modes. ��Coverage Reduction p2811


	//VkPhysicalDeviceTimelineSemaphoreFeatures ���ȼ��� VkPhysicalDeviceTimelineSemaphoreFeaturesKHR�����԰�����VkPhysicalDeviceFeatures2.pNext�� 
	VkPhysicalDeviceTimelineSemaphoreFeatures  physicalDeviceTimelineSemaphoreFeatures{};
	physicalDeviceTimelineSemaphoreFeatures.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_TIMELINE_SEMAPHORE_FEATURES;
	physicalDeviceTimelineSemaphoreFeatures.pNext = nullptr;
	physicalDeviceTimelineSemaphoreFeatures.timelineSemaphore = VK_FALSE;//ָ���Ƿ���Դ���VkSemaphoreTypeΪVK_SEMAPHORE_TYPE_TIMELINE��semaphore


	//VkPhysicalDeviceExternalMemoryScreenBufferFeaturesQNX �����԰�����VkPhysicalDeviceFeatures2.pNext�� 
	VkPhysicalDeviceExternalMemoryScreenBufferFeaturesQNX  physicalDeviceExternalMemoryScreenBufferFeaturesQNX{};
	physicalDeviceExternalMemoryScreenBufferFeaturesQNX.sType = VK_STRUCTURE_TYPE_MAX_ENUM;//û�ж������ﶨ��Ϊ�Ƿ�ֵ
	physicalDeviceExternalMemoryScreenBufferFeaturesQNX.pNext = nullptr;
	physicalDeviceExternalMemoryScreenBufferFeaturesQNX.screenBufferImport = VK_FALSE;//ָ���Ƿ�֧�� QNX Screen buffer ���빦�ܣ����֧�֣���VkDeviceMemory��֧�ֵ���_screen_buffer


	//VkPhysicalDeviceIndexTypeUint8FeaturesKHR ���ȼ��� VkPhysicalDeviceIndexTypeUint8FeaturesEXT�����԰�����VkPhysicalDeviceFeatures2.pNext�� 
	VkPhysicalDeviceIndexTypeUint8FeaturesKHR  physicalDeviceIndexTypeUint8FeaturesKHR{};
	physicalDeviceIndexTypeUint8FeaturesKHR.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_INDEX_TYPE_UINT8_FEATURES_EXT;
	physicalDeviceIndexTypeUint8FeaturesKHR.pNext = nullptr;
	physicalDeviceIndexTypeUint8FeaturesKHR.indexTypeUint8 = VK_FALSE;//ָ��vkCmdBindIndexBuffer2KHR �Լ� vkCmdBindIndexBuffer�����Ƿ����ʹ��VK_INDEX_TYPE_UINT8_KHR


	//VkPhysicalDevicePrimitiveTopologyListRestartFeaturesEXT �����԰�����VkPhysicalDeviceFeatures2.pNext�� 
	VkPhysicalDevicePrimitiveTopologyListRestartFeaturesEXT  physicalDevicePrimitiveTopologyListRestartFeaturesEXT{};
	physicalDevicePrimitiveTopologyListRestartFeaturesEXT.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PRIMITIVE_TOPOLOGY_LIST_RESTART_FEATURES_EXT;
	physicalDevicePrimitiveTopologyListRestartFeaturesEXT.pNext = nullptr;
	physicalDevicePrimitiveTopologyListRestartFeaturesEXT.primitiveTopologyListRestart = VK_FALSE;//ָ���б����͵�ͼԪ: VK_PRIMITIVE_TOPOLOGY_POINT_LIST, VK_PRIMITIVE_TOPOLOGY_LINE_LIST, VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST, VK_PRIMITIVE_TOPOLOGY_LINE_LIST_WITH_ADJACENCY �Լ� VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST_WITH_ADJACENCY, �Ƿ����ʹ��index buffer�е�restart index
	physicalDevicePrimitiveTopologyListRestartFeaturesEXT.primitiveTopologyPatchListRestart = VK_FALSE;//ָ��VK_PRIMITIVE_TOPOLOGY_PATCH_LIST ���͵�ͼԪ�Ƿ����ʹ��index buffer�е�restart index


	//VkPhysicalDeviceShaderSMBuiltinsFeaturesNV �����԰�����VkPhysicalDeviceFeatures2.pNext�� 
	VkPhysicalDeviceShaderSMBuiltinsFeaturesNV  physicalDeviceShaderSMBuiltinsFeaturesNV{};
	physicalDeviceShaderSMBuiltinsFeaturesNV.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_SM_BUILTINS_FEATURES_NV;
	physicalDeviceShaderSMBuiltinsFeaturesNV.pNext = nullptr;
	physicalDeviceShaderSMBuiltinsFeaturesNV.shaderSMBuiltins = VK_FALSE;//ָ���Ƿ�֧��  ShaderSMBuiltinsNV SPIR-V ����


	//VkPhysicalDeviceSeparateDepthStencilLayoutsFeatures ���ȼ��� VkPhysicalDeviceSeparateDepthStencilLayoutsFeaturesKHR �����԰�����VkPhysicalDeviceFeatures2.pNext�� 
	VkPhysicalDeviceSeparateDepthStencilLayoutsFeatures  physicalDeviceSeparateDepthStencilLayoutsFeatures{};
	physicalDeviceSeparateDepthStencilLayoutsFeatures.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SEPARATE_DEPTH_STENCIL_LAYOUTS_FEATURES;
	physicalDeviceSeparateDepthStencilLayoutsFeatures.pNext = nullptr;
	physicalDeviceSeparateDepthStencilLayoutsFeatures.separateDepthStencilLayouts = VK_FALSE;//ָ���Ƿ�֧�ֶ�ֻ������VK_IMAGE_ASPECT_DEPTH_BIT ���� VK_IMAGE_ASPECT_STENCIL_BIT ��depth/stencil imageʹ��VkImageMemoryBarrier�����Ƿ�VK_IMAGE_LAYOUT_DEPTH_ATTACHMENT_OPTIMAL, VK_IMAGE_LAYOUT_DEPTH_READ_ONLY_OPTIMAL, VK_IMAGE_LAYOUT_STENCIL_ATTACHMENT_OPTIMAL, ���� VK_IMAGE_LAYOUT_STENCIL_READ_ONLY_OPTIMAL����ʹ��


	//VkPhysicalDevicePipelineExecutablePropertiesFeaturesKHR �����԰�����VkPhysicalDeviceFeatures2.pNext�� 
	VkPhysicalDevicePipelineExecutablePropertiesFeaturesKHR  physicalDevicePipelineExecutablePropertiesFeaturesKHR{};
	physicalDevicePipelineExecutablePropertiesFeaturesKHR.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PIPELINE_EXECUTABLE_PROPERTIES_FEATURES_KHR;
	physicalDevicePipelineExecutablePropertiesFeaturesKHR.pNext = nullptr;
	physicalDevicePipelineExecutablePropertiesFeaturesKHR.pipelineExecutableInfo = VK_FALSE;//��ʾʵ��֧�ֱ��������ܵ������Ĺܵ���ִ���ļ������Ժ�ͳ����Ϣ


	//VkPhysicalDeviceShaderDemoteToHelperInvocationFeatures ���ȼ��� VkPhysicalDeviceShaderDemoteToHelperInvocationFeaturesEXT �����԰�����VkPhysicalDeviceFeatures2.pNext�� 
	VkPhysicalDeviceShaderDemoteToHelperInvocationFeatures  physicalDeviceShaderDemoteToHelperInvocationFeatures{};
	physicalDeviceShaderDemoteToHelperInvocationFeatures.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_DEMOTE_TO_HELPER_INVOCATION_FEATURES;
	physicalDeviceShaderDemoteToHelperInvocationFeatures.pNext = nullptr;
	physicalDeviceShaderDemoteToHelperInvocationFeatures.shaderDemoteToHelperInvocation = VK_FALSE;//ָ���Ƿ�֧��SPIR-V DemoteToHelperInvocationEXT ����


	//VkPhysicalDeviceTexelBufferAlignmentFeaturesEXT �����԰�����VkPhysicalDeviceFeatures2.pNext�� 
	VkPhysicalDeviceTexelBufferAlignmentFeaturesEXT  physicalDeviceTexelBufferAlignmentFeaturesEXT{};
	physicalDeviceTexelBufferAlignmentFeaturesEXT.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_TEXEL_BUFFER_ALIGNMENT_FEATURES_EXT;
	physicalDeviceTexelBufferAlignmentFeaturesEXT.pNext = nullptr;
	physicalDeviceTexelBufferAlignmentFeaturesEXT.texelBufferAlignment = VK_FALSE;//��ʾ�Ƿ����ʹ�� VkPhysicalDeviceTexelBufferAlignmentProperties�н���ĸ���ϸ�Ķ������Զ�����VkPhysicalDeviceLimits::minTexelBufferOffsetAlignment


	//VkPhysicalDeviceAttachmentFeedbackLoopDynamicStateFeaturesEXT �����԰�����VkPhysicalDeviceFeatures2.pNext�� 
	VkPhysicalDeviceAttachmentFeedbackLoopDynamicStateFeaturesEXT  physicalDeviceAttachmentFeedbackLoopDynamicStateFeaturesEXT{};
	physicalDeviceAttachmentFeedbackLoopDynamicStateFeaturesEXT.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_ATTACHMENT_FEEDBACK_LOOP_DYNAMIC_STATE_FEATURES_EXT;
	physicalDeviceAttachmentFeedbackLoopDynamicStateFeaturesEXT.pNext = nullptr;
	physicalDeviceAttachmentFeedbackLoopDynamicStateFeaturesEXT.attachmentFeedbackLoopDynamicState = VK_FALSE;//��ʾ�Ƿ�֧�� dynamic feedback loops


	//VkPhysicalDeviceLegacyVertexAttributesFeaturesEXT �����԰�����VkPhysicalDeviceFeatures2.pNext�� 
	VkPhysicalDeviceLegacyVertexAttributesFeaturesEXT  physicalDeviceLegacyVertexAttributesFeaturesEXT{};
	physicalDeviceLegacyVertexAttributesFeaturesEXT.sType = VK_STRUCTURE_TYPE_MAX_ENUM;//û�ж�����������Ϊ�Ƿ�ֵ
	physicalDeviceLegacyVertexAttributesFeaturesEXT.pNext = nullptr;
	physicalDeviceLegacyVertexAttributesFeaturesEXT.legacyVertexAttributes = VK_FALSE;//ָ��ʹ�� dynamic vertex input state���Ƿ��Ƿ�֧�ֶ������Եļ���������


	//VkPhysicalDeviceTextureCompressionASTCHDRFeatures ���ȼ���VkPhysicalDeviceTextureCompressionASTCHDRFeaturesEXT �����԰�����VkPhysicalDeviceFeatures2.pNext�� 
	VkPhysicalDeviceTextureCompressionASTCHDRFeatures  physicalDeviceTextureCompressionASTCHDRFeatures{};
	physicalDeviceTextureCompressionASTCHDRFeatures.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_TEXTURE_COMPRESSION_ASTC_HDR_FEATURES;
	physicalDeviceTextureCompressionASTCHDRFeatures.pNext = nullptr;
	physicalDeviceTextureCompressionASTCHDRFeatures.textureCompressionASTC_HDR = VK_FALSE;//ָ���Ƿ�֧�����е�ASTC HDR ѹ�������ʽ�����֧�֣�����VK_FORMAT_ASTC_*** ��optimalTilingFeatures �������VK_FORMAT_FEATURE_SAMPLED_IMAGE_BIT, VK_FORMAT_FEATURE_BLIT_SRC_BIT �Լ� VK_FORMAT_FEATURE_SAMPLED_IMAGE_FILTER_LINEAR_BIT
	
	
	//VkPhysicalDeviceLineRasterizationFeaturesKHR ���ȼ���VkPhysicalDeviceLineRasterizationFeaturesEXT �����԰�����VkPhysicalDeviceFeatures2.pNext�� 
	VkPhysicalDeviceLineRasterizationFeaturesKHR  physicalDeviceLineRasterizationFeaturesKHR{};
	physicalDeviceLineRasterizationFeaturesKHR.sType = VK_STRUCTURE_TYPE_MAX_ENUM;//û�ж�����������Ϊ�Ƿ�ֵ
	physicalDeviceLineRasterizationFeaturesKHR.pNext = nullptr;
	physicalDeviceLineRasterizationFeaturesKHR.rectangularLines = VK_FALSE;//ָ���Ƿ�֧�� rectangular line rasterization 
	physicalDeviceLineRasterizationFeaturesKHR.bresenhamLines = VK_FALSE;//ָ���Ƿ�֧�� Bresenham-style line rasterization 
	physicalDeviceLineRasterizationFeaturesKHR.smoothLines = VK_FALSE;//ָ���Ƿ�֧��  smooth line rasterization 
	physicalDeviceLineRasterizationFeaturesKHR.stippledRectangularLines = VK_FALSE;//ָ���Ƿ�֧��VK_LINE_RASTERIZATION_MODE_RECTANGULAR_KHR line�� stippled line rasterization 
	physicalDeviceLineRasterizationFeaturesKHR.stippledBresenhamLines = VK_FALSE;//ָ���Ƿ�֧��VK_LINE_RASTERIZATION_MODE_BRESENHAM_KHR line�� stippled line rasterization 
	physicalDeviceLineRasterizationFeaturesKHR.stippledSmoothLines = VK_FALSE;//ָ���Ƿ�֧��VK_LINE_RASTERIZATION_MODE_RECTANGULAR_SMOOTH_KHR line�� stippled line rasterization 


	//VkPhysicalDeviceSubgroupSizeControlFeatures ���ȼ���VkPhysicalDeviceSubgroupSizeControlFeaturesEXT �����԰�����VkPhysicalDeviceFeatures2.pNext�� 
	VkPhysicalDeviceSubgroupSizeControlFeatures  physicalDeviceSubgroupSizeControlFeatures{};
	physicalDeviceSubgroupSizeControlFeatures.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SUBGROUP_SIZE_CONTROL_FEATURES;
	physicalDeviceSubgroupSizeControlFeatures.pNext = nullptr;
	physicalDeviceSubgroupSizeControlFeatures.subgroupSizeControl = VK_FALSE;//ָ���Ƿ����ͨ��VK_PIPELINE_SHADER_STAGE_CREATE_ALLOW_VARYING_SUBGROUP_SIZE_BIT �Լ�  VkPipelineShaderStageRequiredSubgroupSizeCreateInfo ��ָ��subgroup size
	physicalDeviceSubgroupSizeControlFeatures.computeFullSubgroups = VK_FALSE;//ָ��compute , mesh, ���� task shaders�Ƿ����ͨ��VK_PIPELINE_SHADER_STAGE_CREATE_REQUIRE_FULL_SUBGROUPS_BIT ��Ҫ��ʹ��������subgroup


	//VkPhysicalDeviceCoherentMemoryFeaturesAMD �����԰�����VkPhysicalDeviceFeatures2.pNext�� 
	VkPhysicalDeviceCoherentMemoryFeaturesAMD  physicalDeviceCoherentMemoryFeaturesAMD{};
	physicalDeviceCoherentMemoryFeaturesAMD.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_COHERENT_MEMORY_FEATURES_AMD;
	physicalDeviceCoherentMemoryFeaturesAMD.pNext = nullptr;
	physicalDeviceCoherentMemoryFeaturesAMD.deviceCoherentMemory = VK_FALSE;//ָ���Ƿ����֧�� device coherent memory


	//VkPhysicalDeviceAccelerationStructureFeaturesKHR  �����԰�����VkPhysicalDeviceFeatures2.pNext�� 
	VkPhysicalDeviceAccelerationStructureFeaturesKHR  physicalDeviceAccelerationStructureFeaturesKHR{};
	physicalDeviceAccelerationStructureFeaturesKHR.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_ACCELERATION_STRUCTURE_FEATURES_KHR;
	physicalDeviceAccelerationStructureFeaturesKHR.pNext = nullptr;
	physicalDeviceAccelerationStructureFeaturesKHR.accelerationStructure = VK_FALSE;//ָ���Ƿ�֧��acceleration structure ����
	physicalDeviceAccelerationStructureFeaturesKHR.accelerationStructureCaptureReplay = VK_FALSE;//ָ���Ƿ�֧�ֱ��������acceleration structure ��device��ַ
	physicalDeviceAccelerationStructureFeaturesKHR.accelerationStructureIndirectBuild = VK_FALSE;//ָ���Ƿ�֧���� vkCmdBuildAccelerationStructuresIndirectKHR�ļ��acceleration structure ��������
	physicalDeviceAccelerationStructureFeaturesKHR.accelerationStructureHostCommands = VK_FALSE;//ָ���Ƿ�֧��host�˵�acceleration structure ������:vkBuildAccelerationStructuresKHR, vkCopyAccelerationStructureKHR, vkCopyAccelerationStructureToMemoryKHR, vkCopyMemoryToAccelerationStructureKHR, vkWriteAccelerationStructuresPropertiesKHR.
	physicalDeviceAccelerationStructureFeaturesKHR.descriptorBindingAccelerationStructureUpdateAfterBind = VK_FALSE;//ָ���Ƿ�֧���ڰ�descriptor set�����acceleration structure descriptors�������֧�֣���VK_DESCRIPTOR_BINDING_UPDATE_AFTER_BIND_BIT ���ܺ�VK_DESCRIPTOR_TYPE_ACCELERATION_STRUCTURE_KHR һ��ʹ��


	//VkPhysicalDeviceRayTracingPipelineFeaturesKHR  �����԰�����VkPhysicalDeviceFeatures2.pNext�� 
	VkPhysicalDeviceRayTracingPipelineFeaturesKHR  physicalDeviceRayTracingPipelineFeaturesKHR{};
	physicalDeviceRayTracingPipelineFeaturesKHR.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_RAY_TRACING_PIPELINE_FEATURES_KHR;
	physicalDeviceRayTracingPipelineFeaturesKHR.pNext = nullptr;
	physicalDeviceRayTracingPipelineFeaturesKHR.rayTracingPipeline = VK_FALSE;//ָ���Ƿ�֧��ray tracing pipeline ����
	physicalDeviceRayTracingPipelineFeaturesKHR.rayTracingPipelineShaderGroupHandleCaptureReplay = VK_FALSE;//ָ���Ƿ�֧�ֱ�������� shader group ���
	physicalDeviceRayTracingPipelineFeaturesKHR.rayTracingPipelineShaderGroupHandleCaptureReplayMixed = VK_FALSE;//ָ���Ƿ�֧�����õ� shader group ����ͷ����õ� shader group ���������ʹ�ã������֧�������õ� shader group ��������ڿ��ܴ����ķ����� shader group ���ǰָ�������֧����rayTracingPipelineShaderGroupHandleCaptureReplay Ҳ����֧��ΪVK_TRUE
	physicalDeviceRayTracingPipelineFeaturesKHR.rayTracingPipelineTraceRaysIndirect = VK_FALSE;//ָ���Ƿ�֧���� vkCmdTraceRaysIndirectKHR �ļ��ray tracing ����
	physicalDeviceRayTracingPipelineFeaturesKHR.rayTraversalPrimitiveCulling = VK_FALSE;//ָ���Ƿ�֧���� ray traversal�����н��� primitive culling 


	//VkPhysicalDeviceRayQueryFeaturesKHR  �����԰�����VkPhysicalDeviceFeatures2.pNext�� 
	VkPhysicalDeviceRayQueryFeaturesKHR  physicalDeviceRayQueryFeaturesKHR{};
	physicalDeviceRayQueryFeaturesKHR.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_RAY_QUERY_FEATURES_KHR;
	physicalDeviceRayQueryFeaturesKHR.pNext = nullptr;
	physicalDeviceRayQueryFeaturesKHR.rayQuery = VK_FALSE;//ָ���Ƿ�֧��ray query (OpRayQueryProceedKHR) ����


	//VkPhysicalDeviceRayTracingMaintenance1FeaturesKHR  �����԰�����VkPhysicalDeviceFeatures2.pNext�� 
	VkPhysicalDeviceRayTracingMaintenance1FeaturesKHR  physicalDeviceRayTracingMaintenance1FeaturesKHR{};
	physicalDeviceRayTracingMaintenance1FeaturesKHR.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_RAY_TRACING_MAINTENANCE_1_FEATURES_KHR;
	physicalDeviceRayTracingMaintenance1FeaturesKHR.pNext = nullptr;
	physicalDeviceRayTracingMaintenance1FeaturesKHR.rayTracingMaintenance1 = VK_FALSE;//ָ���Ƿ�֧�֣�1. CullMaskKHR SPIR-V ��Ƕ����ʹ�� SPV_KHR_ray_cull_mask SPIR-V ��չ��2.������ٽṹ�����Բ�ѯVK_QUERY_TYPE_ACCELERATION_STRUCTURE_SERIALIZATION_BOTTOM_LEVEL_POINTERS_KHR �Լ� VK_QUERY_TYPE_ACCELERATION_STRUCTURE_SIZE_KHR��3.�µķ��ʱ�־ VK_ACCESS_2_SHADER_BINDING_TABLE_READ_BIT_KHR��4.�µ�pipeline stage��־ VK_PIPELINE_STAGE_2_ACCELERATION_STRUCTURE_COPY_BIT_KHR
	physicalDeviceRayTracingMaintenance1FeaturesKHR.rayTracingPipelineTraceRaysIndirect2 = VK_FALSE;//ָ���Ƿ�֧����չ���� vkCmdTraceRaysIndirect2KHR �ļ��ray tracing ����


	//VkPhysicalDeviceVideoMaintenance1FeaturesKHR  �����԰�����VkPhysicalDeviceFeatures2.pNext�� 
	VkPhysicalDeviceVideoMaintenance1FeaturesKHR  physicalDeviceVideoMaintenance1FeaturesKHR{};
	physicalDeviceVideoMaintenance1FeaturesKHR.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_RAY_TRACING_MAINTENANCE_1_FEATURES_KHR;
	physicalDeviceVideoMaintenance1FeaturesKHR.pNext = nullptr;
	physicalDeviceVideoMaintenance1FeaturesKHR.videoMaintenance1 = VK_FALSE;//ָ���Ƿ�֧��:1.�µ�buffer ������־VK_BUFFER_CREATE_VIDEO_PROFILE_INDEPENDENT_BIT_KHR��2.�µ�image������־ VK_IMAGE_CREATE_VIDEO_PROFILE_INDEPENDENT_BIT_KHR��3.�µ�video session������־ VK_VIDEO_SESSION_CREATE_INLINE_QUERIES_BIT_KHR


	//VkPhysicalDeviceExtendedDynamicStateFeaturesEXT  �����԰�����VkPhysicalDeviceFeatures2.pNext�� 
	VkPhysicalDeviceExtendedDynamicStateFeaturesEXT  physicalDeviceExtendedDynamicStateFeaturesEXT{};
	physicalDeviceExtendedDynamicStateFeaturesEXT.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_EXTENDED_DYNAMIC_STATE_FEATURES_EXT;
	physicalDeviceExtendedDynamicStateFeaturesEXT.pNext = nullptr;
	physicalDeviceExtendedDynamicStateFeaturesEXT.extendedDynamicState = VK_FALSE;/*
		ָ���Ƿ�֧�����¶�̬states:
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


	//VkPhysicalDeviceExtendedDynamicState2FeaturesEXT  �����԰�����VkPhysicalDeviceFeatures2.pNext�� 
	VkPhysicalDeviceExtendedDynamicState2FeaturesEXT  physicalDeviceExtendedDynamicState2FeaturesEXT{};
	physicalDeviceExtendedDynamicState2FeaturesEXT.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_EXTENDED_DYNAMIC_STATE_2_FEATURES_EXT;
	physicalDeviceExtendedDynamicState2FeaturesEXT.pNext = nullptr;
	physicalDeviceExtendedDynamicState2FeaturesEXT.extendedDynamicState2 = VK_FALSE;//ָ���Ƿ�֧�ֶ�̬states: VK_DYNAMIC_STATE_DEPTH_BIAS_ENABLE,  VK_DYNAMIC_STATE_PRIMITIVE_RESTART_ENABLE , VK_DYNAMIC_STATE_RASTERIZER_DISCARD_ENABLE
	physicalDeviceExtendedDynamicState2FeaturesEXT.extendedDynamicState2LogicOp = VK_FALSE;//ָ���Ƿ�֧�ֶ�̬state: VK_DYNAMIC_STATE_LOGIC_OP_EXT
	physicalDeviceExtendedDynamicState2FeaturesEXT.extendedDynamicState2PatchControlPoints = VK_FALSE;//ָ���Ƿ�֧�ֶ�̬state: K_DYNAMIC_STATE_PATCH_CONTROL_POINTS_EXT


	//VkPhysicalDeviceExtendedDynamicState3FeaturesEXT  �����԰�����VkPhysicalDeviceFeatures2.pNext�� 
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