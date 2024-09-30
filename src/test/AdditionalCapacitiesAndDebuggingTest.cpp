#include "AdditionalCapacitiesAndDebuggingTest.h"
NS_TEST_BEGIN
AdditionalCapacitiesAndDebuggingTest::AdditionalCapacitiesAndDebuggingTest()
{
}

void AdditionalCapacitiesAndDebuggingTest::run()
{
}

AdditionalCapacitiesAndDebuggingTest::~AdditionalCapacitiesAndDebuggingTest()
{
}

void AdditionalCapacitiesAndDebuggingTest::AdditionalCapacitiesTest()
{

	//Additional Image Capabilities  �μ�p4122
	{
		//�����image capabilities��Ϊ�����ָ��image type�ĸ����ά���Լ�����Ĳ���������������linear tiling format����Ķ����image capabilities

		//��ѯָ��image type�Ķ����image capabilities
		VkImageFormatProperties imageFormatProperties{};
		VkResult result/*�����������ϲ�֧����᷵��VK_ERROR_FORMAT_NOT_SUPPORTED*/ = vkGetPhysicalDeviceImageFormatProperties(physicalDevice, VK_FORMAT_R8G8B8_UINT/*format*/, VK_IMAGE_TYPE_2D/*type*/, VK_IMAGE_TILING_LINEAR/*tiling������ΪVK_IMAGE_TILING_DRM_FORMAT_MODIFIER_EXT*/,
			VK_IMAGE_USAGE_SAMPLED_BIT/*usage*/, VK_IMAGE_CREATE_2D_ARRAY_COMPATIBLE_BIT/*flags*/, &imageFormatProperties/*pImageFormatProperties,���ؽ��*/);//������ȷ���ؽ��
		imageFormatProperties.maxExtent = VkExtent3D{ .width = 1,.height = 1,.depth = 1 };//Ϊ֧�ֵ�����image��ά��
		imageFormatProperties.maxMipLevels = 10;//Ϊ֧�ֵ�mipmap levels���������������������p4124
		imageFormatProperties.maxArrayLayers = 10;//Ϊ֧�ֵ�array layers���������������������p4124
		imageFormatProperties.sampleCounts = VK_SAMPLE_COUNT_16_BIT;//VkSampleCountFlagBits ���ֵλ���룬ָ��image֧�ֵĲ�������Ŀ
		imageFormatProperties.maxResourceSize = 1000;//Ϊ����image ��Դ��ռ�ݵ��ֽ����������������������pow(2,32)-1



		//ȷ���� external memory handle type���ݵ� image capabilities
		VkExternalImageFormatPropertiesNV externalImageFormatPropertiesNV{};
		vkGetPhysicalDeviceExternalImageFormatPropertiesNV(physicalDevice, VK_FORMAT_R8G8B8_UINT/*format*/, VK_IMAGE_TYPE_2D/*type*/, VK_IMAGE_TILING_LINEAR/*tiling������ΪVK_IMAGE_TILING_DRM_FORMAT_MODIFIER_EXT*/,
			VK_IMAGE_USAGE_SAMPLED_BIT/*usage*/, VK_IMAGE_CREATE_2D_ARRAY_COMPATIBLE_BIT/*flags*/, VK_EXTERNAL_MEMORY_HANDLE_TYPE_D3D11_IMAGE_BIT_NV/*externalHandleType ��VkExternalMemoryHandleTypeFlagBitsNV*/, &externalImageFormatPropertiesNV/*pExternalImageFormatProperties�����ؽ��*/);//������ȷ���ؽ��
		externalImageFormatPropertiesNV.imageFormatProperties = imageFormatProperties;//VkImageFormatProperties����
		externalImageFormatPropertiesNV.externalMemoryFeatures;/*VkExternalMemoryFeatureFlagBitsNV ���ֵλ���룬ָ��externalHandleType������
		VkExternalMemoryFeatureFlagBitsNV:
		VK_EXTERNAL_MEMORY_FEATURE_DEDICATED_ONLY_BIT_NV : ָ��ָ��type���ⲿmemory�����Զ��з��䴴��
		VK_EXTERNAL_MEMORY_FEATURE_EXPORTABLE_BIT_NV : ָ��ʵ��֧�ֵ���ָ�����͵ľ��
		VK_EXTERNAL_MEMORY_FEATURE_IMPORTABLE_BIT_NV : ָ��ʵ��֧�ֵ���ָ�����͵ľ��
		*/
		externalImageFormatPropertiesNV.exportFromImportedHandleTypes;//VkExternalMemoryHandleTypeFlagBitsNV���ֵλ���룬ָ�����Դ�externalHandleType�ϵ��봴���ڴ��һ��external memory handle types
		externalImageFormatPropertiesNV.compatibleHandleTypes;//VkExternalMemoryHandleTypeFlagBitsNV���ֵλ���룬ָ������vkAllocateMemoryʱ���Ժ�externalHandleTypeһָͬ����һ��external memory handle types


		//��ѯָ��image type�Ķ����image capabilities 2
		{
			struct ImageFormatProperties2EXT {
				VkAndroidHardwareBufferUsageANDROID androidHardwareBufferUsageANDROID{};
				VkExternalImageFormatProperties externalImageFormatProperties{};
				VkFilterCubicImageViewImageFormatPropertiesEXT filterCubicImageViewImageFormatPropertiesEXT{};
				VkHostImageCopyDevicePerformanceQueryEXT hostImageCopyDevicePerformanceQueryEXT{};
				VkImageCompressionPropertiesEXT imageCompressionPropertiesEXT{};
				VkSamplerYcbcrConversionImageFormatProperties samplerYcbcrConversionImageFormatProperties{};
				VkTextureLODGatherFormatPropertiesAMD textureLODGatherFormatPropertiesAMD{};
				ImageFormatProperties2EXT() {
					androidHardwareBufferUsageANDROID.sType = VK_STRUCTURE_TYPE_MAX_ENUM;//û�ж������ﶨ��Ϊ�Ƿ�ֵ
					androidHardwareBufferUsageANDROID.pNext = nullptr;
					externalImageFormatProperties.sType = VK_STRUCTURE_TYPE_EXTERNAL_IMAGE_FORMAT_PROPERTIES;
					externalImageFormatProperties.pNext = nullptr;
					filterCubicImageViewImageFormatPropertiesEXT.sType = VK_STRUCTURE_TYPE_FILTER_CUBIC_IMAGE_VIEW_IMAGE_FORMAT_PROPERTIES_EXT;
					filterCubicImageViewImageFormatPropertiesEXT.pNext = nullptr;
					hostImageCopyDevicePerformanceQueryEXT.sType = VK_STRUCTURE_TYPE_HOST_IMAGE_COPY_DEVICE_PERFORMANCE_QUERY_EXT;
					hostImageCopyDevicePerformanceQueryEXT.pNext = nullptr;
					imageCompressionPropertiesEXT.sType = VK_STRUCTURE_TYPE_IMAGE_COMPRESSION_PROPERTIES_EXT;
					imageCompressionPropertiesEXT.pNext = nullptr;
					samplerYcbcrConversionImageFormatProperties.sType = VK_STRUCTURE_TYPE_SAMPLER_YCBCR_CONVERSION_IMAGE_FORMAT_PROPERTIES;
					samplerYcbcrConversionImageFormatProperties.pNext = nullptr;
					textureLODGatherFormatPropertiesAMD.sType = VK_STRUCTURE_TYPE_TEXTURE_LOD_GATHER_FORMAT_PROPERTIES_AMD;
					textureLODGatherFormatPropertiesAMD.pNext = nullptr;
				}
			};


			VkImageFormatProperties2 imageFormatProperties2{};//�ȼ���VkImageFormatProperties2KHR
			imageFormatProperties2.sType = VK_STRUCTURE_TYPE_IMAGE_FORMAT_PROPERTIES_2;
			ImageFormatProperties2EXT imageFormatProperties2EXT{};
			//VkImageFormatProperties2.pNext
			{
				//VkTextureLODGatherFormatPropertiesAMD,����ȷ��ʹ����ʽLOD �Լ�/���� bias ������texture gather functions �Ƿ��������ָ����image format
				VkTextureLODGatherFormatPropertiesAMD& textureLODGatherFormatPropertiesAMD = imageFormatProperties2EXT.textureLODGatherFormatPropertiesAMD;
				textureLODGatherFormatPropertiesAMD.supportsTextureGatherLODBiasAMD = VK_FALSE;//˵��ָ��image format�Ƿ��������texture gather bias/LOD functions

				//VkExternalImageFormatProperties�� �ȼ���VkExternalImageFormatPropertiesKHR������ȷ��ʹ����ʽLOD �Լ�/���� bias ������texture gather functions �Ƿ��������ָ����image format
				VkExternalImageFormatProperties& externalImageFormatProperties = imageFormatProperties2EXT.externalImageFormatProperties;
				VkExternalMemoryProperties externalMemoryProperties{}; //�ȼ���VkExternalMemoryPropertiesKH
				{
					externalMemoryProperties.externalMemoryFeatures = VK_EXTERNAL_MEMORY_FEATURE_DEDICATED_ONLY_BIT;/* VkExternalMemoryFeatureFlagBits���ֵλ���룬ָ��handleType������
					VkExternalMemoryFeatureFlagBits �ȼ���VkExternalMemoryFeatureFlagBitsKHR :
					VK_EXTERNAL_MEMORY_FEATURE_DEDICATED_ONLY_BIT : ˵����ָ���Ĳ�����handle type������images����buffers����ʹ��VkMemoryDedicatedRequirements �Լ� VkMemoryDedicatedAllocateInfo����Ļ������������ߵ���һ��image����buffer��dedicated allocation
					VK_EXTERNAL_MEMORY_FEATURE_EXPORTABLE_BIT : ָ��������͵�handles���Դ�vulkan memory�����е���
					VK_EXTERNAL_MEMORY_FEATURE_IMPORTABLE_BIT : ָ��������͵�handles���Ե�����Ϊvulkan memory����
					*/
					externalMemoryProperties.exportFromImportedHandleTypes = VK_EXTERNAL_MEMORY_HANDLE_TYPE_D3D11_TEXTURE_KMT_BIT;// VkExternalMemoryHandleTypeFlagBits���ֵλ���룬ָ����Щ���͵ĵ��������Ե���handleType
					externalMemoryProperties.compatibleHandleTypes = VK_EXTERNAL_MEMORY_HANDLE_TYPE_D3D11_TEXTURE_KMT_BIT;// VkExternalMemoryHandleTypeFlagBits���ֵλ���룬ָ������handleType����һ�����ⲿ�ڴ���ݵ�image��ͬʱ������ָ����Щhandle types
				}
				externalImageFormatProperties.externalMemoryProperties = externalMemoryProperties;//ָ��һ��external handle type ���ڴ�����ͬ������image��Ӧ�Ĳ�ͬ������


				//VkSamplerYcbcrConversionImageFormatProperties�� �ȼ���VkSamplerYcbcrConversionImageFormatPropertiesKHR������ȷ��֧��һ�� multi-planar format��Ҫ��combined image samplers������
				VkSamplerYcbcrConversionImageFormatProperties& samplerYcbcrConversionImageFormatProperties = imageFormatProperties2EXT.samplerYcbcrConversionImageFormatProperties;
				samplerYcbcrConversionImageFormatProperties.combinedImageSamplerDescriptorCount = 1;//ָ�����ڷ���format��combined image sampler descriptors������

				
				//VkAndroidHardwareBufferUsageANDROID������ȷ��֧��һ�� multi-planar format��Ҫ��combined image samplers������
				VkAndroidHardwareBufferUsageANDROID& androidHardwareBufferUsageANDROID = imageFormatProperties2EXT.androidHardwareBufferUsageANDROID;
				androidHardwareBufferUsageANDROID.androidHardwareBufferUsage = 0;//���� Android hardware buffer usage flags��ÿ��bit��Ӧ����AHARDWAREBUFFER_USAGE_GPU_*���÷����о��� AHardwareBuffer Usage Equivalence p989


				//VkHostImageCopyDevicePerformanceQueryEXT������ȷ��ʹ��VK_IMAGE_USAGE_HOST_TRANSFER_BIT_EXT �Ƿ�Է���image��device�����в���Ӱ��
				VkHostImageCopyDevicePerformanceQueryEXT& hostImageCopyDevicePerformanceQueryEXT = imageFormatProperties2EXT.hostImageCopyDevicePerformanceQueryEXT;
				hostImageCopyDevicePerformanceQueryEXT.optimalDeviceAccess = VK_FALSE;//ָ��������ȫ��ͬ���Ұ󶨵���ͬVkDeviceMemory������image����ֻ�ǽ�VK_IMAGE_USAGE_HOST_TRANSFER_BIT_EXT���滻ΪVK_IMAGE_USAGE_TRANSFER_SRC_BIT��VK_IMAGE_USAGE_TRANSFER_DST_BIT��host image copy �Ƿ�device��������û�в���Ӱ��
				hostImageCopyDevicePerformanceQueryEXT.identicalMemoryLayout = VK_FALSE;//ָ��������ȫ��ͬ���Ұ󶨵���ͬVkDeviceMemory������image����ֻ�ǽ�VK_IMAGE_USAGE_HOST_TRANSFER_BIT_EXT���滻ΪVK_IMAGE_USAGE_TRANSFER_SRC_BIT��VK_IMAGE_USAGE_TRANSFER_DST_BIT��host image copy �Ƿ����ڴ沼����û��Ӱ��


				//VkFilterCubicImageViewImageFormatPropertiesEXT������ȷ��ָ��image format�Լ�image view type�Ƿ�֧��cubic filtering
				VkFilterCubicImageViewImageFormatPropertiesEXT& filterCubicImageViewImageFormatPropertiesEXT = imageFormatProperties2EXT.filterCubicImageViewImageFormatPropertiesEXT;
				filterCubicImageViewImageFormatPropertiesEXT.filterCubic = VK_FALSE;//ָ���Ƿ�ָ����image format, image type �Լ� image view type���Ժ�cubic filteringһ��ʹ��
				filterCubicImageViewImageFormatPropertiesEXT.filterCubicMinmax = VK_FALSE;//ָ���Ƿ�ָ����image format, image type �Լ� image view type���Ժ�cubic filtering�Լ�minmax filteringһ��ʹ��


			}
			imageFormatProperties2.pNext = &imageFormatProperties2EXT.androidHardwareBufferUsageANDROID;
			imageFormatProperties2.imageFormatProperties;//VkImageFormatProperties ����


			struct PhysicalDeviceImageFormatInfo2EXT {
				VkImageCompressionControlEXT imageCompressionControlEXT{};
				VkImageFormatListCreateInfo imageFormatListCreateInfo{};
				VkImageStencilUsageCreateInfo imageStencilUsageCreateInfo{};
				VkOpticalFlowImageFormatInfoNV opticalFlowImageFormatInfoNV{};
				VkPhysicalDeviceExternalImageFormatInfo physicalDeviceExternalImageFormatInfo{};
				VkPhysicalDeviceImageDrmFormatModifierInfoEXT physicalDeviceImageDrmFormatModifierInfoEXT{};
				VkPhysicalDeviceImageViewImageFormatInfoEXT physicalDeviceImageViewImageFormatInfoEXT{};
				VkVideoProfileListInfoKHR videoProfileListInfoKHR{};
				PhysicalDeviceImageFormatInfo2EXT() {
					Init();
				}
				void Init() {
					imageCompressionControlEXT.sType = VK_STRUCTURE_TYPE_IMAGE_COMPRESSION_CONTROL_EXT;
					imageCompressionControlEXT.pNext = nullptr;
					imageFormatListCreateInfo.sType = VK_STRUCTURE_TYPE_IMAGE_FORMAT_LIST_CREATE_INFO;
					imageFormatListCreateInfo.pNext = nullptr;
					imageStencilUsageCreateInfo.sType = VK_STRUCTURE_TYPE_IMAGE_STENCIL_USAGE_CREATE_INFO;
					imageStencilUsageCreateInfo.pNext = nullptr;
					opticalFlowImageFormatInfoNV.sType = VK_STRUCTURE_TYPE_OPTICAL_FLOW_IMAGE_FORMAT_INFO_NV;
					opticalFlowImageFormatInfoNV.pNext = nullptr;
					physicalDeviceExternalImageFormatInfo.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_EXTERNAL_IMAGE_FORMAT_INFO;
					physicalDeviceExternalImageFormatInfo.pNext = nullptr;
					physicalDeviceImageDrmFormatModifierInfoEXT.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_IMAGE_DRM_FORMAT_MODIFIER_INFO_EXT;
					physicalDeviceImageDrmFormatModifierInfoEXT.pNext = nullptr;
					physicalDeviceImageViewImageFormatInfoEXT.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_IMAGE_VIEW_IMAGE_FORMAT_INFO_EXT;
					physicalDeviceImageViewImageFormatInfoEXT.pNext = nullptr;
					videoProfileListInfoKHR.sType = VK_STRUCTURE_TYPE_VIDEO_PROFILE_LIST_INFO_KHR;
					videoProfileListInfoKHR.pNext = nullptr;
				}
			};

			VkPhysicalDeviceImageFormatInfo2 physicalDeviceImageFormatInfo2{};//�ȼ���VkPhysicalDeviceImageFormatInfo2KHR
			physicalDeviceImageFormatInfo2.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_IMAGE_FORMAT_INFO_2;
			PhysicalDeviceImageFormatInfo2EXT physicalDeviceImageFormatInfo2EXT{};
			//VkPhysicalDeviceImageFormatInfo2.pNext
			{
				//VkPhysicalDeviceExternalImageFormatInfo���ȼ���VkPhysicalDeviceExternalImageFormatInfoKHR ,����ȷ����ָ��external memory handle type���ݵ�image capabilities
				VkPhysicalDeviceExternalImageFormatInfo& physicalDeviceExternalImageFormatInfo = physicalDeviceImageFormatInfo2EXT.physicalDeviceExternalImageFormatInfo;
				physicalDeviceExternalImageFormatInfo.handleType = VK_EXTERNAL_MEMORY_HANDLE_TYPE_D3D11_TEXTURE_BIT;/* VkExternalMemoryHandleTypeFlagBits ֵ��ָ��image������memory��memory handle type
				VkExternalMemoryHandleTypeFlagBits �ȼ���VkExternalMemoryHandleTypeFlagBitsKHR:
				VK_EXTERNAL_MEMORY_HANDLE_TYPE_OPAQUE_FD_BIT : ָ��һ����vulkan������������APIs��ֻ����������Ч�÷���POSIX file descriptor handle������������p4136
				VK_EXTERNAL_MEMORY_HANDLE_TYPE_OPAQUE_WIN32_BIT  : ָ��һ����vulkan������������APIs��ֻ����������Ч�÷���NT handle������������p4136
				VK_EXTERNAL_MEMORY_HANDLE_TYPE_OPAQUE_WIN32_KMT_BIT : ָ��һ����vulkan������������APIs��ֻ����������Ч�÷���global share handle������������p4136
				VK_EXTERNAL_MEMORY_HANDLE_TYPE_D3D11_TEXTURE_BIT : ָ��һ�����õ�Direct3D 10 ���� 11 texture resource��IDXGIResource1::CreateSharedHandle���ص�NT handle������������p4136
				VK_EXTERNAL_MEMORY_HANDLE_TYPE_D3D11_TEXTURE_KMT_BIT : ָ��һ�����õ�Direct3D 10 ���� 11 texture resource��IDXGIResource1::GetSharedHandle���ص�global share handle������������p4136
				VK_EXTERNAL_MEMORY_HANDLE_TYPE_D3D12_HEAP_BIT : ָ��һ�����õ�Direct3D 12 heap resource��ID3D12Device::CreateSharedHandle���ص�NT handle������������p4136
				VK_EXTERNAL_MEMORY_HANDLE_TYPE_D3D12_RESOURCE_BIT : ָ��һ�����õ�Direct3D 12 committed resource��ID3D12Device::CreateSharedHandle���ص�NT handle������������p4136
				VK_EXTERNAL_MEMORY_HANDLE_TYPE_HOST_ALLOCATION_BIT_EXT : ָ��һ��ͨ��host memory allocation command�����host pointer������������p4136
				VK_EXTERNAL_MEMORY_HANDLE_TYPE_HOST_MAPPED_FOREIGN_MEMORY_BIT_EXT: ָ��һ��ͨ��hostӳ���ȡ��host pointer������������p4136
				VK_EXTERNAL_MEMORY_HANDLE_TYPE_DMA_BUF_BIT_EXT : Ϊһ��Linux dma_buf��һ��file descriptor������������p4136
				VK_EXTERNAL_MEMORY_HANDLE_TYPE_ANDROID_HARDWARE_BUFFER_BIT_ANDROID : ָ��һ����Android NDK�����AHardwareBuffer��������������p4136
				VK_EXTERNAL_MEMORY_HANDLE_TYPE_ZIRCON_VMO_BIT_FUCHSIA : Ϊһ�������ڴ�����Zircon handle
				VK_EXTERNAL_MEMORY_HANDLE_TYPE_RDMA_ADDRESS_BIT_NV : Ϊ��remote devices���ʵ�һ���������ľ�����þ��ӵ��Vulkan memory�����ʾ�ĵײ��ڴ���Դ������
				VK_EXTERNAL_MEMORY_HANDLE_TYPE_SCREEN_BUFFER_BIT_QNX : ָ��һ����QNX SDP�����_screen_buffer��������������p4137

				һЩ external memory handle types��������ͬ�ĵײ�physical device�Լ�������ͬ��device�汾�й����������Ϣ��p4138 Table 91. External memory handle types compatibility
				*/



				//VkPhysicalDeviceImageDrmFormatModifierInfoEXT�����ڲ�ѯ�� Linux DRM format modifier���ݵ�image capabilities
				VkPhysicalDeviceImageDrmFormatModifierInfoEXT& physicalDeviceImageDrmFormatModifierInfoEXT = physicalDeviceImageFormatInfo2EXT.physicalDeviceImageDrmFormatModifierInfoEXT;
				physicalDeviceImageDrmFormatModifierInfoEXT.drmFormatModifier = 0;//Ϊimage��Linux DRM format modifier����Ӧ��VkImageDrmFormatModifierExplicitCreateInfoEXT::modifier ����VkImageDrmFormatModifierListCreateInfoEXT::pModifiers�е�Ԫ��
				physicalDeviceImageDrmFormatModifierInfoEXT.sharingMode = VK_SHARING_MODE_EXCLUSIVE;//ָ��image�Ĺ���ģʽ
				physicalDeviceImageDrmFormatModifierInfoEXT.queueFamilyIndexCount = 1;//ָ������image�Ķ����������
				uint32_t queueFamily = 0;
				physicalDeviceImageDrmFormatModifierInfoEXT.pQueueFamilyIndices = &queueFamily;//ָ������image�Ķ��������������� sharingMode ��Ϊ VK_SHARING_MODE_CONCURRENT�����
				/*
				VkPhysicalDeviceImageDrmFormatModifierInfoEXT��Ч�÷�:
				1.���sharingMode ΪVK_SHARING_MODE_CONCURRENT����1��pQueueFamilyIndices����Ϊ��Ч��queueFamilyIndexCount��uint32_tֵ�������ָ��
																  ��2��queueFamilyIndexCount �������1
																  ��3��pQueueFamilyIndices��ÿ��Ԫ�ر�����Ψһ���ұ���С��vkGetPhysicalDeviceQueueFamilyProperties2���ص����ڴ���device��pQueueFamilyPropertyCount��ֵָ���Ķ�����ĸ���
				*/


				//VkPhysicalDeviceImageViewImageFormatInfoEXT������ȷ���Ƿ�cubic filtering���Ժ�ָ����image format��image typeһ��ʹ��
				VkPhysicalDeviceImageViewImageFormatInfoEXT& physicalDeviceImageViewImageFormatInfoEXT = physicalDeviceImageFormatInfo2EXT.physicalDeviceImageViewImageFormatInfoEXT;
				physicalDeviceImageViewImageFormatInfoEXT.imageViewType = VK_IMAGE_VIEW_TYPE_2D;// VkImageViewType ֵָ��image view������


			}
			physicalDeviceImageFormatInfo2.pNext = nullptr;
			physicalDeviceImageFormatInfo2.format = VK_FORMAT_R8_UNORM;//VkFormat��ָ��image format
			physicalDeviceImageFormatInfo2.type = VK_IMAGE_TYPE_2D;//VkImageType��ָ��image type
			physicalDeviceImageFormatInfo2.tiling = VK_IMAGE_TILING_LINEAR;//VkImageTiling��ָ��image tiling
			physicalDeviceImageFormatInfo2.usage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;//VkImageUsageFlagBits���ֵλ���룬ָ��image usages
			physicalDeviceImageFormatInfo2.flags = VK_IMAGE_CREATE_2D_ARRAY_COMPATIBLE_BIT;//VkImageCreateFlagBits���ֵλ���룬ָ��image flags
			/*
			VkPhysicalDeviceImageFormatInfo2��Ч�÷�:
			1.���pNext�а��� VkPhysicalDeviceImageDrmFormatModifierInfoEXT ����tiling����ΪVK_IMAGE_TILING_DRM_FORMAT_MODIFIER_EXT
			2.���tiling ΪVK_IMAGE_TILING_DRM_FORMAT_MODIFIER_EXT��flags�а���VK_IMAGE_CREATE_MUTABLE_FORMAT_BIT ����pNext�б������  viewFormatCount��Ϊ0��VkImageFormatListCreateInfo
			*/


			vkGetPhysicalDeviceImageFormatProperties2(physicalDevice, &physicalDeviceImageFormatInfo2, &imageFormatProperties2);//������ȷ���ؽ��
			/*
			vkGetPhysicalDeviceImageFormatProperties2��Ч�÷�:
			1.���pImageFormatProperties->pNext�а���һ��VkAndroidHardwareBufferUsageANDROID����pImageFormatInfo->pNext�б������һ��handleTypeָ��ΪVK_EXTERNAL_MEMORY_HANDLE_TYPE_ANDROID_HARDWARE_BUFFER_BIT_ANDROID��VkPhysicalDeviceExternalImageFormatInfo
			2.���pImageFormatProperties->pNext�а���һ��VkHostImageCopyDevicePerformanceQueryEXT����pImageFormatInfo->usage �������VK_IMAGE_USAGE_HOST_TRANSFER_BIT_EXT
			*/
		}


		//Supported Sample Counts  ����һЩ�����vkGetPhysicalDeviceImageFormatProperties���÷��ص�sampleCounts������� ��ϸ����μ�p4148 

		//Allowed Extent Values Based on Image Type ��ʵ��֧����һЩ�����image�ķ�Χ����limit���оٵ�ָ��image���͵������Сֵ����Щ�������ϸ�����μ�p4149

	}


	//Additional Buffer Capabilities  �μ�p4149
	{

		//��ѯbuffers֧�ֵ� external handle types
		VkPhysicalDeviceExternalBufferInfo physicalDeviceExternalBufferInfo{};//�ȼ���VkPhysicalDeviceExternalBufferInfoKHR
		physicalDeviceExternalBufferInfo.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_EXTERNAL_BUFFER_INFO;
		physicalDeviceExternalBufferInfo.pNext = nullptr;//���԰���һ��VkBufferUsageFlags2CreateInfoKHR
		physicalDeviceExternalBufferInfo.flags = VK_BUFFER_CREATE_SPARSE_BINDING_BIT;// VkBufferCreateFlagBits ���ֵλ���룬ָ��buffer�Ķ����������Ӧ VkBufferCreateInfo::flags
		physicalDeviceExternalBufferInfo.usage = VK_BUFFER_USAGE_INDEX_BUFFER_BIT;// VkBufferUsageFlagBits ���ֵλ���룬ָ��buffer��Ԥ����;����Ӧ VkBufferCreateInfo::usage
		physicalDeviceExternalBufferInfo.handleType = VK_EXTERNAL_MEMORY_HANDLE_TYPE_D3D11_TEXTURE_BIT;// VkExternalMemoryHandleTypeFlagBitsֵ��ָ������buffer������memory�� memory handle type
		/*
		VkPhysicalDeviceExternalBufferInfo��Ч�÷�:
		1.���pNext�в�����һ�� VkBufferUsageFlags2CreateInfoKHR���� usage������һ����Ч�� VkBufferUsageFlagBits���ֵ������Ϊ0
		
		
		*/

		VkExternalBufferProperties externalBufferProperties{};//�ȼ���VkExternalBufferPropertiesKHR
		externalBufferProperties.sType = VK_STRUCTURE_TYPE_EXTERNAL_BUFFER_PROPERTIES;
		externalBufferProperties.pNext = nullptr;
		VkExternalMemoryProperties externalMemoryProperties{/*��������һ����Ч��VkExternalMemoryProperties*/};//ǰ���Ѿ������������ﲻ������
		externalBufferProperties.externalMemoryProperties = externalMemoryProperties;//ָ��һ��external handle type ���ڴ�����ͬ������buffer��Ӧ�Ĳ�ͬ������

		//�ȼ���vkGetPhysicalDeviceExternalBufferPropertiesKHR
		vkGetPhysicalDeviceExternalBufferProperties(physicalDevice, &physicalDeviceExternalBufferInfo, &externalBufferProperties);




	}


	//Optional Semaphore Capabilities  �μ�p4152
	{
		//semaphores ���ܻᵼ��򵼳���payload���ⲿ�ľ������ѯsemaphores֧�ֵ��ⲿ�������
		VkPhysicalDeviceExternalSemaphoreInfo physicalDeviceExternalSemaphoreInfo{};//�ȼ���VkPhysicalDeviceExternalSemaphoreInfoKHR
		physicalDeviceExternalSemaphoreInfo.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_EXTERNAL_SEMAPHORE_INFO;
		physicalDeviceExternalSemaphoreInfo.pNext = nullptr;
		physicalDeviceExternalSemaphoreInfo.handleType = VK_EXTERNAL_SEMAPHORE_HANDLE_TYPE_OPAQUE_WIN32_BIT;/*VkExternalSemaphoreHandleTypeFlagBits ֵ��ָ��Ҫ��ѯ���Ե�external semaphore handle type
		VkExternalSemaphoreHandleTypeFlagBits �ȼ���VkExternalSemaphoreHandleTypeFlagBitsKHR:
		VK_EXTERNAL_SEMAPHORE_HANDLE_TYPE_OPAQUE_FD_BIT : ָ��һ����vulkan�Լ��������ݵ�APIs֮�⺬��������Ч�÷���POSIX file descriptor handle��������ϸ������p4154
		VK_EXTERNAL_SEMAPHORE_HANDLE_TYPE_OPAQUE_WIN32_BIT : ָ��һ����vulkan�Լ��������ݵ�APIs֮�⺬��������Ч�÷���NT handle ��������ϸ������p4154
		VK_EXTERNAL_SEMAPHORE_HANDLE_TYPE_OPAQUE_WIN32_KMT_BIT : ָ��һ����vulkan�Լ��������ݵ�APIs֮�⺬��������Ч�÷��� global share handle��������ϸ������p4155
		VK_EXTERNAL_SEMAPHORE_HANDLE_TYPE_D3D12_FENCE_BIT : ָ��һ�����õ�һ��Direct3D 12 fence ��ID3D12Device::CreateSharedHandle���������õ�һ��Direct3D 11 fence��ID3D11Device5::CreateFence���ص�NT handle��������ϸ������p4155
		VK_EXTERNAL_SEMAPHORE_HANDLE_TYPE_D3D11_FENCE_BIT : ��VK_EXTERNAL_SEMAPHORE_HANDLE_TYPE_D3D12_FENCE_BIT��˼��ͬ
		VK_EXTERNAL_SEMAPHORE_HANDLE_TYPE_SYNC_FD_BIT : ָ��һ��Linux Sync File ���� Android Fence object��POSIX file descriptor handle��������ϸ������p4155
		VK_EXTERNAL_SEMAPHORE_HANDLE_TYPE_ZIRCON_EVENT_BIT_FUCHSIA : ָ��һ��Zircon event object�ľ����������ϸ������p4155
		
		һЩ external semaphore handle typesֻ��������ͬ�ײ�physical device �Լ�������ͬdevice�汾������²��ܹ�����صļ�����Ϣ�μ�p4156 Table 92. External semaphore handle types compatibility
		*/



		VkExternalSemaphoreProperties externalSemaphoreProperties{};//�ȼ���VkExternalSemaphorePropertiesKHR
		externalSemaphoreProperties.sType = VK_STRUCTURE_TYPE_EXTERNAL_SEMAPHORE_PROPERTIES;
		externalSemaphoreProperties.pNext = nullptr;
		externalSemaphoreProperties.exportFromImportedHandleTypes = VK_EXTERNAL_SEMAPHORE_HANDLE_TYPE_OPAQUE_WIN32_BIT;//VkExternalSemaphoreHandleTypeFlagBits ���ֵλ���룬ָ��handleType ���Դ���Щ���͵�imported handle�е���
		externalSemaphoreProperties.compatibleHandleTypes = VK_EXTERNAL_SEMAPHORE_HANDLE_TYPE_OPAQUE_WIN32_BIT;//VkExternalSemaphoreHandleTypeFlagBits ���ֵλ���룬ָ����handleType ����semaphore��ͬʱ������ָ����Щhandle types
		externalSemaphoreProperties.externalSemaphoreFeatures = VK_EXTERNAL_SEMAPHORE_FEATURE_EXPORTABLE_BIT;/*VkExternalSemaphoreFeatureFlagBits ���ֵλ���룬���� handleType������
		VkExternalSemaphoreFeatureFlagBits �ȼ���VkExternalSemaphoreFeatureFlagBitsKHR :
		VK_EXTERNAL_SEMAPHORE_FEATURE_EXPORTABLE_BIT : ָ�������͵ľ�����Դ�Vulkan semaphore �����е���
		VK_EXTERNAL_SEMAPHORE_FEATURE_IMPORTABLE_BIT : ָ�������͵ľ�����Ե���ΪVulkan semaphore ����
		*/


		//�ȼ���vkGetPhysicalDeviceExternalSemaphorePropertiesKHR
		vkGetPhysicalDeviceExternalSemaphoreProperties(physicalDevice, &physicalDeviceExternalSemaphoreInfo, &externalSemaphoreProperties/*pExternalSemaphoreProperties������ֵ*/);


	}



	//Optional Fence Capabilities  �μ�p4158
	{
		//fences ���ܻᵼ��򵼳���payload���ⲿ�ľ������ѯfences֧�ֵ��ⲿ�������
		VkPhysicalDeviceExternalFenceInfo physicalDeviceExternalFenceInfo{};//�ȼ���VkPhysicalDeviceExternalFenceInfoKHR
		physicalDeviceExternalFenceInfo.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_EXTERNAL_FENCE_INFO;
		physicalDeviceExternalFenceInfo.pNext = nullptr;
		physicalDeviceExternalFenceInfo.handleType = VK_EXTERNAL_FENCE_HANDLE_TYPE_OPAQUE_WIN32_BIT;/* VkExternalFenceHandleTypeFlagBits ֵ��ָ��Ҫ��ѯ���Ե�external fence handle type
		VkExternalFenceHandleTypeFlagBits �ȼ���VkExternalFenceHandleTypeFlagBitsKHR:
		VK_EXTERNAL_FENCE_HANDLE_TYPE_OPAQUE_FD_BIT : ָ��һ����vulkan�Լ��������ݵ�APIs֮�⺬��������Ч�÷���POSIX file descriptor handle��������ϸ������p4160
		VK_EXTERNAL_FENCE_HANDLE_TYPE_OPAQUE_WIN32_BIT : ָ��һ����vulkan�Լ��������ݵ�APIs֮�⺬��������Ч�÷���NT handle ��������ϸ������p4160
		VK_EXTERNAL_FENCE_HANDLE_TYPE_OPAQUE_WIN32_KMT_BIT : ָ��һ����vulkan�Լ��������ݵ�APIs֮�⺬��������Ч�÷��� global share handle��������ϸ������p4160
		VK_EXTERNAL_FENCE_HANDLE_TYPE_SYNC_FD_BIT : ָ��һ��Linux Sync File ���� Android Fence object��POSIX file descriptor handle��������ϸ������p4160


		һЩ external fence handle typesֻ��������ͬ�ײ�physical device �Լ�������ͬdevice�汾������²��ܹ�����صļ�����Ϣ�μ�p4162 Table 93. External fence handle types compatibility

		*/

		VkExternalFenceProperties externalFenceProperties{};//�ȼ���VkExternalFencePropertiesKHR
		externalFenceProperties.sType = VK_STRUCTURE_TYPE_EXTERNAL_FENCE_PROPERTIES;
		externalFenceProperties.pNext = nullptr;
		externalFenceProperties.exportFromImportedHandleTypes = VK_EXTERNAL_FENCE_HANDLE_TYPE_OPAQUE_WIN32_BIT;//VkExternalFenceHandleTypeFlagBits ���ֵλ���룬ָ��handleType ���Դ���Щ���͵�imported handle�е���
		externalFenceProperties.compatibleHandleTypes = VK_EXTERNAL_FENCE_HANDLE_TYPE_OPAQUE_WIN32_BIT;//VkExternalFenceHandleTypeFlagBits ���ֵλ���룬ָ����handleType ����fence��ͬʱ������ָ����Щhandle types
		externalFenceProperties.externalFenceFeatures = VK_EXTERNAL_FENCE_FEATURE_EXPORTABLE_BIT;/*VkExternalFenceFeatureFlagBits ���ֵλ���룬���� handleType������	
		VkExternalFenceFeatureFlagBits �ȼ���VkExternalFenceFeatureFlagBitsKHR :
		VK_EXTERNAL_FENCE_FEATURE_EXPORTABLE_BIT : ָ�������͵ľ�����Դ�Vulkan fence �����е���
		VK_EXTERNAL_FENCE_FEATURE_IMPORTABLE_BIT : ָ�������͵ľ�����Ե���ΪVulkan fence ����
		*/



		//�ȼ���vkGetPhysicalDeviceExternalFencePropertiesKHR
		vkGetPhysicalDeviceExternalFenceProperties(physicalDevice, &physicalDeviceExternalFenceInfo, &externalFenceProperties);


	}


	//Timestamp Calibration Capabilities  �μ�p4164
	{
		//��ѯphysical device֧�ֵ�timestamp calibration��һ�� time domains
		uint32_t timeDomainCount = 0;
		std::vector<VkTimeDomainKHR> timeDomainKHRs{};
		//�ȼ���vkGetPhysicalDeviceCalibrateableTimeDomainsEXT
		vkGetPhysicalDeviceCalibrateableTimeDomainsKHR(physicalDevice, &timeDomainCount, nullptr);
		timeDomainKHRs.resize(timeDomainCount);
		vkGetPhysicalDeviceCalibrateableTimeDomainsKHR(physicalDevice, &timeDomainCount, timeDomainKHRs.data());

	}

}

VkBool32 TestCallBack(
	VkDebugUtilsMessageSeverityFlagBitsEXT           messageSeverity,//ָ�������ûص��� VkDebugUtilsMessageSeverityFlagBitsEXT
	VkDebugUtilsMessageTypeFlagsEXT                  messageTypes,//ָ�������ûص��� VkDebugUtilsMessageTypeFlagBitsEXT
	const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,//Ϊ��������callback���ݵ�VkDebugUtilsMessengerCallbackDataEXT
	void* pUserData/*Ϊ���� VkDebugUtilsMessengerEXTʱ�ṩ���û����������*/) {//�ûص������ڲ����ܵ����κ�vulkan����
	
	VkDebugUtilsMessengerCallbackDataEXT debugUtilsMessengerCallbackDataEXT{};
	debugUtilsMessengerCallbackDataEXT = *pCallbackData;
	debugUtilsMessengerCallbackDataEXT.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CALLBACK_DATA_EXT;
	VkDeviceAddressBindingCallbackDataEXT deviceAddressBindingCallbackDataEXT{};
	{
		//����������p4189
		deviceAddressBindingCallbackDataEXT.sType = VK_STRUCTURE_TYPE_DEVICE_ADDRESS_BINDING_CALLBACK_DATA_EXT;
		deviceAddressBindingCallbackDataEXT.pNext = nullptr;
		deviceAddressBindingCallbackDataEXT.flags = VK_DEVICE_ADDRESS_BINDING_INTERNAL_OBJECT_BIT_EXT;/*VkDeviceAddressBindingFlagBitsEXT ���ֵλ���룬ָ�������ص��İ󶨵��¼��Ķ�����Ϣ
		VkDeviceAddressBindingFlagBitsEXT
		VK_DEVICE_ADDRESS_BINDING_INTERNAL_OBJECT_BIT_EXT : ָ��VkDeviceAddressBindingCallbackDataEXT����һ����û��ͨ��vulkan��������host�ɼ���vulkan����
		*/
		deviceAddressBindingCallbackDataEXT.baseAddress = 0;//ָ��vulkan �������ڵ������ַ�ռ�Ŀ�ʼ��GPU-accessible virtual address��Ҳ��VkDebugUtilsMessengerCallbackDataEXT.pObjects��ָ����
		deviceAddressBindingCallbackDataEXT.size = 1;//ΪGPU-accessible virtual address�ռ���ֽڴ�С
		deviceAddressBindingCallbackDataEXT.bindingType = VK_DEVICE_ADDRESS_BINDING_TYPE_BIND_EXT;/*VkDeviceAddressBindingTypeEXTֵ��ָ�������ص��İ󶨵��¼�������
		VkDeviceAddressBindingTypeEXT:
		VK_DEVICE_ADDRESS_BINDING_TYPE_BIND_EXT : ָ��һ���µ�GPU-accessible virtual address��Χ����
		VK_DEVICE_ADDRESS_BINDING_TYPE_UNBIND_EXT : ָ��һ��GPU-accessible virtual address��Χ�����
		*/
		

	}
	debugUtilsMessengerCallbackDataEXT.pNext = nullptr;//���ܰ���һ��VkDeviceAddressBindingCallbackDataEXT
	debugUtilsMessengerCallbackDataEXT.flags = 0;//Ϊ0����δ��ʹ��
	debugUtilsMessengerCallbackDataEXT.pMessageIdName;//ΪNULL���� null-terminated UTF-8 string��ָ������������message��message ID�ı�ʶ
	debugUtilsMessengerCallbackDataEXT.messageIdNumber;//Ϊ����message��ID
	debugUtilsMessengerCallbackDataEXT.pMessage;//ΪNULL ���messageTypesΪVK_DEBUG_UTILS_MESSAGE_TYPE_DEVICE_ADDRESS_BINDING_BIT_EXT,���ߴ���message����ϸ��Ϣ��null-terminated UTF-8 string
	debugUtilsMessengerCallbackDataEXT.queueLabelCount;// pQueueLabels ��Ԫ�ظ���
	debugUtilsMessengerCallbackDataEXT.pQueueLabels;//ΪNULL����һ���ڸûص�����ʱqueue�м����VkDebugUtilsLabelEXT������ָ��
	debugUtilsMessengerCallbackDataEXT.cmdBufLabelCount;//pCmdBufLabels��Ԫ�ظ���
	debugUtilsMessengerCallbackDataEXT.pCmdBufLabels;//ΪNULL����һ���ڸûص�����ʱcommand buffer�м����VkDebugUtilsLabelEXT������ָ��
	debugUtilsMessengerCallbackDataEXT.objectCount;//pObjects ��Ԫ�ظ���
	debugUtilsMessengerCallbackDataEXT.pObjects;//Ϊ��������⵽�������һ��VkDebugUtilsObjectNameInfoEXT��ָ��
	
	
	return VK_FALSE;
}

VkBool32 ReportCallBack(
	VkDebugReportFlagsEXT                       flags,//ָ�������ص��� VkDebugReportFlagBitsEXT
	VkDebugReportObjectTypeEXT                  objectType,// VkDebugReportObjectTypeEXTֵ��ָ���¼�����ʱʹ�õĻ��ߴ����Ķ��������
	uint64_t                                    object,//Ϊ��⵽�¼�����ʱʹ�û򴴽��Ķ�����objectType��ΪVK_DEBUG_REPORT_OBJECT_TYPE_UNKNOWN_EXTʱ��Ч
	size_t                                      location,//Ϊָ�������¼���(layer, driver, loader)λ�ã���ѡ����
	int32_t                                     messageCode,//��layer-defined��ֵ���ڲ��Իص�����
	const char* pLayerPrefix,//null-terminated UTF-8 string��Ϊ�ûص��ĵ����ߵ�������д
	const char* pMessage,//Ϊ����message����ϸ��Ϣ��null-terminated UTF-8 string
	void* pUserData/*Ϊ���� VkDebugReportCallbackEXTʱ�ṩ���û����������*/) {

	return VK_FALSE;
}

void AdditionalCapacitiesAndDebuggingTest::DebuggingTest()
{
	/*
	Ϊ�˰���������Ա����Ӧ�ó�����ʹ��Vulkanʱ���ֵĴ����ر������ⲿ����������������ʱ������ʹ��debugging��չ
	
	��debugging ��Ϣ�У� VkObjectType ö��ֵ����������ʶ�������ͣ�VkObjectType����Щֵ�Լ����Ӧ��ЩVulkan����������p4166 - p4169
	*/

	
	//Debug Utilities  �μ�p4169
	{
		//Object Debug Annotation  ������ν�ָ�������ֻ��߶�������Ϣ������ָ����vulkan���� �� �μ�p4169
		{
			//Object Naming �μ�p4170
			VkDebugUtilsObjectNameInfoEXT debugUtilsObjectNameInfoEXT{};
			debugUtilsObjectNameInfoEXT.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT;
			debugUtilsObjectNameInfoEXT.pNext = nullptr;
			debugUtilsObjectNameInfoEXT.objectType = VK_OBJECT_TYPE_IMAGE;// VkObjectTypeֵ��ָ��Ҫָ�����ֵĶ��������
			debugUtilsObjectNameInfoEXT.objectHandle = (uint64_t)VkImage{/*��������һ����Ч��VkImage*/};//Ϊ�ö���ľ��
			debugUtilsObjectNameInfoEXT.pObjectName = "my_image";//ΪNULL����null-terminated UTF-8 string��ָ��Ӧ�õ��ö��������
			/*
			VkDebugUtilsObjectNameInfoEXT��Ч�÷�:
			1.���objectType ΪVK_OBJECT_TYPE_UNKNOWN����objectHandle ����ΪVK_NULL_HANDLE
			2.���objectType ��ΪVK_OBJECT_TYPE_UNKNOWN����objectHandle ����ΪVK_NULL_HANDLE����һ��objectTypeָ�������͵�vulkan�����vulkan���

			*/


			//��һ�������ṩһ���û����������
			vkSetDebugUtilsObjectNameEXT(device, &debugUtilsObjectNameInfoEXT);
			/*
			vkSetDebugUtilsObjectNameEXT��Ч�÷�:
			1.pNameInfo->objectType ����ΪVK_OBJECT_TYPE_UNKNOWN
			2.pNameInfo->objectHandle ����ΪVK_NULL_HANDLE
			3.���pNameInfo->objectHandle ��һ����Ч��instance-level ����ľ����device��Ӧ��VkDevice�������Ժ�pNameInfo->objectHandle��ͬ��VkInstance
			4.���pNameInfo->objectHandle ��һ����Ч��physical-device-level ����ľ����device��Ӧ��VkDevice ����� pNameInfo->objectHandle��Ӧ��VkPhysicalDevice����������
			5.���pNameInfo->objectHandle ��һ����Ч��device-level ����ľ����pNameInfo->objectHandle ����������device��Ӧ��VkDevice
			*/


			//Object Data Association  �μ�p4172
			VkDebugUtilsObjectTagInfoEXT debugUtilsObjectTagInfoEXT{};
			debugUtilsObjectTagInfoEXT.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_TAG_INFO_EXT;
			debugUtilsObjectTagInfoEXT.pNext = nullptr;
			debugUtilsObjectTagInfoEXT.objectType = VK_OBJECT_TYPE_IMAGE;// VkObjectTypeֵ��ָ��Ҫָ�����ֵĶ��������
			debugUtilsObjectTagInfoEXT.objectHandle = (uint64_t)VkImage{/*��������һ����Ч��VkImage*/ };//Ϊ�ö���ľ��
			debugUtilsObjectTagInfoEXT.tagName =  0;//Ϊtag�����ֱ�ʶ��
			debugUtilsObjectTagInfoEXT.tagSize = 3;//Ϊ���ӵ�vulkan�����ϵ����ݵ��ֽ�����С
			debugUtilsObjectTagInfoEXT.pTag = "tag";//Ϊ���ӵ�vulkan�����ϵ�����
			/*
			VkDebugUtilsObjectTagInfoEXT��Ч�÷�:
			1.objectType ����ΪVK_OBJECT_TYPE_UNKNOWN
			2.objectHandle����Ϊһ����Ч��objectTypeָ�������͵�vulkan�����vulkan���
			*/

			//��һ�����󸽼Ӷ��������
			vkSetDebugUtilsObjectTagEXT(device, &debugUtilsObjectTagInfoEXT);
			/*
			vkSetDebugUtilsObjectTagEXT��Ч�÷�:
			1.���pTagInfo->objectHandle ��һ����Ч��instance-level ����ľ����device��Ӧ��VkDevice�������Ժ�pNameInfo->objectHandle��ͬ��VkInstance
			2.���pTagInfo->objectHandle ��һ����Ч��physical-device-level ����ľ����device��Ӧ��VkDevice ����� pNameInfo->objectHandle��Ӧ��VkPhysicalDevice����������
			3.���pTagInfo->objectHandle ��һ����Ч��device-level ����ľ����pNameInfo->objectHandle ����������device��Ӧ��VkDevice
			
			*/


		}


		//Queue Labels  �������ע�ͺͳ����ύ�����еĹ������μ�p4174
		{
			VkQueue queue{/*��������һ����Ч��VkQueue*/ };

			//queue debug label region������������ĸ�queue���ĸ�λ������ִ��


			VkDebugUtilsLabelEXT debugUtilsLabelEXT{};
			debugUtilsLabelEXT.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_LABEL_EXT;
			debugUtilsLabelEXT.pNext = nullptr;
			debugUtilsLabelEXT.pLabelName = "my_label";//null-terminated UTF-8 string��ָ��label������
			debugUtilsLabelEXT.color/*float[4]*/;//һ����ѡ�Ĺ�����label��RGBA��ɫֵ��ÿ��Ԫ�ط�ΧΪ0-1

			//����һ��queue debug label region
			vkQueueBeginDebugUtilsLabelEXT(queue, &debugUtilsLabelEXT);

			//����һ��queue debug label region
			vkQueueEndDebugUtilsLabelEXT(queue);//���������֮ǰ������һ����Ե�vkQueueBeginDebugUtilsLabelEXT


			//��һ��label����һ��queue
			vkQueueInsertDebugUtilsLabelEXT(queue, &debugUtilsLabelEXT);

		}

		//Command Buffer Labels  ������ι���VkCommandBuffer�еĳ����е��߼�Ԫ�� ,�μ�p4177
		{
			VkCommandBuffer commandBuffer{/*��������һ����Ч��VkCommandBuffer*/ };

			//command buffer debug label������������ĸ�command buffer���ĸ�λ������ִ��

			VkDebugUtilsLabelEXT debugUtilsLabelEXT{};
			debugUtilsLabelEXT.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_LABEL_EXT;
			debugUtilsLabelEXT.pNext = nullptr;
			debugUtilsLabelEXT.pLabelName = "my_label";//null-terminated UTF-8 string��ָ��label������
			debugUtilsLabelEXT.color/*float[4]*/;//һ����ѡ�Ĺ�����label��RGBA��ɫֵ��ÿ��Ԫ�ط�ΧΪ0-1

			//����һ��command buffer��debug label region�Ŀ�ʼ
			vkCmdBeginDebugUtilsLabelEXT(commandBuffer, &debugUtilsLabelEXT);

			//�ر�һ��command debug label region
			vkCmdEndDebugUtilsLabelEXT(commandBuffer);//commandBuffer��¼֮ǰ������һ����Ե�vkCmdBeginDebugUtilsLabelEXT

			//��command buffer�в���һ��debug label
			vkCmdInsertDebugUtilsLabelEXT(commandBuffer, &debugUtilsLabelEXT);

		}

		//Debug Messengers   ������δ���һ��������Ӧ�õ�ʹ�ûص���������vulkan��ͬ���ֵĵ�����Ϣ��debug messenger ,�μ�p4181
		{
			//vulkan����Ӧ��ע��ص���������ȡ������Ϣ��������Щ�ص���������Ҫ������Ϊ validation layers����debug messagers ������

			VkDebugUtilsMessengerEXT debugUtilsMessengerEXT{};

			//����һ������debug callback��debug messenger
			VkDebugUtilsMessengerCreateInfoEXT debugUtilsMessengerCreateInfoEXT{};
			debugUtilsMessengerCreateInfoEXT.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
			debugUtilsMessengerCreateInfoEXT.pNext = nullptr;
			debugUtilsMessengerCreateInfoEXT.flags = 0;//Ϊ0����δ��ʹ��
			debugUtilsMessengerCreateInfoEXT.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;/*VkDebugUtilsMessageSeverityFlagBitsEXT���ֵλ���룬ָ�����̶ֳȵ��¼��ᴥ���ص������ĵ���
			VkDebugUtilsMessageSeverityFlagBitsEXT:
			VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT : ָ��Ӧ�ò����ܹ�ָ��vulkan loaders��layers�Լ�drivers�����������Ϣ����ϸ���
			VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT : ָ����ʾ��Ϣ����Ϣ���統����Ӧ��ʱ���ܴ������Դϸ��
			VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT : ָ��vulkan��ʹ�ÿ��ܻᱩ¶һ��Ӧ��bug����Щ������ܲ��������𺦳���ִ�У�ֻ��һ�����档
			VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT : ָ��Ӧ������һ��Υ��vulkan����Ч�÷��Ĵ���

			*/
			debugUtilsMessengerCreateInfoEXT.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;/* VkDebugUtilsMessageTypeFlagBitsEXT ���ֵλ���룬ָ���������͵��¼��ᴥ���ص������ĵ���
			VkDebugUtilsMessageTypeFlagBitsEXT:
			VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT : ָ��һЩ�����¼���������non-specification, non-performance event
			VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT : ָ��һЩ������validation ��Υ��Vulkan specification�Ŀ���ָ��invalid behavior���¼�
			VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT : ָ��һ��Ǳ�ڵ�vulkan�ķ������÷������統VkAttachmentDescription::loadOp����ΪVK_ATTACHMENT_LOAD_OP_CLEARʱ����vkCmdClearColorImage
			VK_DEBUG_UTILS_MESSAGE_TYPE_DEVICE_ADDRESS_BINDING_BIT_EXT : ָ��ʵ���Ѿ��޸��˹�����vulkan�����GPU-visible virtual addresses
			*/
			debugUtilsMessengerCreateInfoEXT.pfnUserCallback = &TestCallBack;//�ص������ĺ�����ַ
			debugUtilsMessengerCreateInfoEXT.pUserData = "test_userdata";//һ���û�����Ĵ��ݸ��ص������Ķ�Ӧ����������



			//����Щ������û�ϣ��������ύһ��debug messager,����һ���ص�
			VkDebugUtilsMessengerCallbackDataEXT debugUtilsMessengerCallbackDataEXT{};//�ص��������Ѿ����������ﲻ�ٸ���
			vkSubmitDebugUtilsMessageEXT(instance, VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT, VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT, &debugUtilsMessengerCallbackDataEXT);// pCallbackData->pObjects��ÿ��Ԫ�ص�objectType ����ΪVK_OBJECT_TYPE_UNKNOWN


			//����һ��debug messager
			vkDestroyDebugUtilsMessengerEXT(instance, debugUtilsMessengerEXT, nullptr);
			/*
			vkDestroyDebugUtilsMessengerEXT��Ч�÷�:
			1.�������messagerʱ�ṩ��һ�� VkAllocationCallbacks������������ṩһ�����ݵ�
			2.�������messagerʱû���ṩVkAllocationCallbacks����pAllocator ����ΪNULL

			*/

		}

	}



	//Debug Markers  �μ�p4193
	{
		//Debug markersΪdebugging �Լ� validation layers�ṩ��һ�����ķ�ʽ����ȡע�ͺ͵�����Ϣ

		//Object Annotation   ������ν����ֺͶ��������ݹ�����vulkan���� �μ�p4193
		{

			
			VkDebugMarkerObjectNameInfoEXT debugMarkerObjectNameInfoEXT{};
			debugMarkerObjectNameInfoEXT.sType = VK_STRUCTURE_TYPE_DEBUG_MARKER_OBJECT_NAME_INFO_EXT;
			debugMarkerObjectNameInfoEXT.pNext = nullptr;
			debugMarkerObjectNameInfoEXT.objectType = VK_DEBUG_REPORT_OBJECT_TYPE_IMAGE_EXT;//  VkDebugReportObjectTypeEXTֵ��ָ��Ҫָ�����ֵĶ��������
			debugMarkerObjectNameInfoEXT.object = (uint64_t)VkImage{/*��������һ����Ч��VkImage*/ };//Ϊ�ö���ľ��
			debugMarkerObjectNameInfoEXT.pObjectName = "my_image";//ΪNULL����null-terminated UTF-8 string��ָ��Ӧ�õ��ö��������
			/*
			VkDebugMarkerObjectNameInfoEXT��Ч�÷�:
			1.objectType ����Ϊ VK_DEBUG_REPORT_OBJECT_TYPE_UNKNOWN_EXT
			2.object ����ΪVK_NULL_HANDLE
			3.object����Ϊһ��objectTypeָ�������͵�vulkan�����vulkan���
			*/


			//��һ�������ṩһ���û����������
			vkDebugMarkerSetObjectNameEXT(device, &debugMarkerObjectNameInfoEXT);


			VkDebugMarkerObjectTagInfoEXT debugMarkerObjectTagInfoEXT{};
			debugMarkerObjectTagInfoEXT.sType = VK_STRUCTURE_TYPE_DEBUG_MARKER_OBJECT_TAG_INFO_EXT;
			debugMarkerObjectTagInfoEXT.pNext = nullptr;
			debugMarkerObjectTagInfoEXT.objectType = VK_DEBUG_REPORT_OBJECT_TYPE_IMAGE_EXT;// VkDebugReportObjectTypeEXTֵ��ָ��Ҫָ�����ֵĶ��������,��������ö��ֵ�Ķ����Լ���Ӧ��vulkan��������ϸ��Ϣ��p4204 - p4207
			debugMarkerObjectTagInfoEXT.object = (uint64_t)VkImage{/*��������һ����Ч��VkImage*/ };//Ϊ�ö���ľ��
			debugMarkerObjectTagInfoEXT.tagName = 0;//Ϊtag�����ֱ�ʶ��
			debugMarkerObjectTagInfoEXT.tagSize = 3;//Ϊ���ӵ�vulkan�����ϵ����ݵ��ֽ�����С
			debugMarkerObjectTagInfoEXT.pTag = "tag";//Ϊ���ӵ�vulkan�����ϵ�����
			/*
			VkDebugMarkerObjectTagInfoEXT��Ч�÷�:
			1.objectType ����ΪVK_DEBUG_REPORT_OBJECT_TYPE_UNKNOWN_EXT
			2.object����ΪVK_NULL_HANDLE
			3.object����Ϊһ����Ч��objectTypeָ�������͵�vulkan�����vulkan���
			*/

			//��һ�����󸽼Ӷ��������
			vkDebugMarkerSetObjectTagEXT(device, &debugMarkerObjectTagInfoEXT);

		}


		//Command Buffer Markers   ������ι���VkCommandBuffer�еĳ����е��߼�Ԫ�أ� �μ�p4197
		{
			VkCommandBuffer commandBuffer{/*��������һ����Ч��VkCommandBuffer*/ };

			//marker region�����������command buffer�е�һ�����������

			VkDebugMarkerMarkerInfoEXT debugMarkerMarkerInfoEXT{};
			debugMarkerMarkerInfoEXT.sType = VK_STRUCTURE_TYPE_DEBUG_MARKER_MARKER_INFO_EXT;
			debugMarkerMarkerInfoEXT.pNext = nullptr;
			debugMarkerMarkerInfoEXT.pMarkerName = "my_marker";//null-terminated UTF-8 string��ָ��marker������
			debugMarkerMarkerInfoEXT.color/*float[4]*/;//һ����ѡ�Ĺ�����marker��RGBA��ɫֵ��ÿ��Ԫ�ط�ΧΪ0-1

			//����һ��marker region�Ŀ�ʼ
			vkCmdDebugMarkerBeginEXT(commandBuffer, &debugMarkerMarkerInfoEXT);

			//�ر�һ��marker region
			vkCmdDebugMarkerEndEXT(commandBuffer);//commandBuffer��¼֮ǰ������һ����Ե�vkCmdDebugMarkerBeginEXT

			//��command buffer�в���һ��marker
			vkCmdDebugMarkerInsertEXT(commandBuffer, &debugMarkerMarkerInfoEXT);

		}

	}


	//Debug Report Callbacks  �μ�p4201
	{
		//debug report callbacks�ܹ��ڸ���Ȥ���¼�����ʱ��������ķ�����Ϣ

		VkDebugReportCallbackEXT debugReportCallbackEXT{};

		
		VkDebugReportCallbackCreateInfoEXT debugReportCallbackCreateInfoEXT{};
		debugReportCallbackCreateInfoEXT.sType = VK_STRUCTURE_TYPE_DEBUG_REPORT_CALLBACK_CREATE_INFO_EXT;
		debugReportCallbackCreateInfoEXT.pNext = nullptr;
		debugReportCallbackCreateInfoEXT.flags = VK_DEBUG_REPORT_ERROR_BIT_EXT;/* VkDebugReportFlagBitsEXT ���ֵλ���룬ָ���ĸ��¼������ᴥ���ص�
		VkDebugReportFlagBitsEXT:
		VK_DEBUG_REPORT_ERROR_BIT_EXT : ָ��Ӧ��Υ����specification�й涨�ĺϷ�ʹ������
		VK_DEBUG_REPORT_WARNING_BIT_EXT : ָ��vulkan��ʹ�ÿ��ܻᱩ¶һ��Ӧ��bug����Щ������ܲ��������𺦳���ִ�У�ֻ��һ�����档
		VK_DEBUG_REPORT_PERFORMANCE_WARNING_BIT_EXT : ָ��һ��Ǳ�ڵ�vulkan�ķ������÷������統VkAttachmentDescription::loadOp����ΪVK_ATTACHMENT_LOAD_OP_CLEARʱ����vkCmdClearColorImage
		VK_DEBUG_REPORT_INFORMATION_BIT_EXT : ָ����ʾ��Ϣ����Ϣ���統����Ӧ��ʱ���ܴ������Դϸ��
		VK_DEBUG_REPORT_DEBUG_BIT_EXT : ָ������ʵ���Լ�layers�������Ϣ
		*/
		debugReportCallbackCreateInfoEXT.pfnCallback = &ReportCallBack;//ָ���ص�����
		debugReportCallbackCreateInfoEXT.pUserData = "my_userdata";//һ���û�����Ĵ��ݸ��ص������Ķ�Ӧ����������
		
		//ע��һ��debug report callback
		vkCreateDebugReportCallbackEXT(instance, &debugReportCallbackCreateInfoEXT, nullptr, &debugReportCallbackEXT);


		//��debug stream��ע����Ϣ
		vkDebugReportMessageEXT(instance, VK_DEBUG_REPORT_ERROR_BIT_EXT/*flags*/, VK_DEBUG_REPORT_OBJECT_TYPE_BUFFER_EXT/*objectType*/, (uint64_t)VkBuffer {/*��������һ����Ч��VkBuffer*/ }/*object*/,
			0/*location*/, 0/*messageCode*/, "my_layer"/*pLayerPrefix*/, "test_message"/*pMessage*/);//��������ɶ���ReportCallBack�ص�����
		/*
		vkDebugReportMessageEXT��Ч�÷�:
		1.object ����Ϊvulkan ����������VK_NULL_HANDLE
		2.���objectType ��ΪVK_DEBUG_REPORT_OBJECT_TYPE_UNKNOWN_EXT ��object��ΪVK_NULL_HANDLE����object������objectType��Ӧ����Ч��vulkan�����vulkan���

		*/

		
		//����debug report callbacks
		vkDestroyDebugReportCallbackEXT(instance, debugReportCallbackEXT, nullptr);
		/*
		vkDestroyDebugReportCallbackEXT��Ч�÷�:
		1.�������callbackʱ�ṩ��һ�� VkAllocationCallbacks������������ṩһ�����ݵ�
		2.�������callbackʱû���ṩVkAllocationCallbacks����pAllocator ����ΪNULL
		
		*/

	}


	//Device Loss Debugging �μ�p4209
	{
		//Device Diagnostic Checkpoints  �μ�p4209
		{
			//device�ĳ���ִ�п���ͨ�����û������device��ϼ���ע��ָ������������׷��������device loss

			VkCommandBuffer commandBuffer{};//��������һ����Ч��VkCommandBuffer

			//���������в���device diagnostic checkpoints
			uint32_t checkPoint = 0;
			vkCmdSetCheckpointNV(commandBuffer, &checkPoint);

			//����deviceִ������device loss����ʱ��ʵ�ֻ���hostִ�е�һЩ�㷵��VK_ERROR_DEVICE_LOST����ȡ������ʱ����� diagnostic checkpoints����Ϣ
			uint32_t checkPointDataCount2 = 0;
			std::vector<VkCheckpointData2NV> checkpointData2NVs{};
			vkGetQueueCheckpointData2NV(VkQueue{/*��������һ����Ч��VkQueue*/ }/*queue*/, & checkPointDataCount2, nullptr);//queue���봦��lost״̬
			checkpointData2NVs.resize(checkPointDataCount2);
			vkGetQueueCheckpointData2NV(VkQueue{/*��������һ����Ч��VkQueue*/ }, & checkPointDataCount2, checkpointData2NVs.data());//������ȷ����������
			VkCheckpointData2NV &checkpointData2NV = checkpointData2NVs[0];
			checkpointData2NV.sType = VK_STRUCTURE_TYPE_CHECKPOINT_DATA_2_NV;
			checkpointData2NV.pNext = nullptr;
			checkpointData2NV.stage = VK_PIPELINE_STAGE_2_RESOLVE_BIT;//ָ��һ��checkpoint marker �������õ���һ��pipeline stage
			uint32_t markerData2 = 0;
			checkpointData2NV.pCheckpointMarker = &markerData2;//������stage��ִ�е����һ��checkpoint marker��ֵ


			//����deviceִ������device loss����ʱ��ʵ�ֻ���hostִ�е�һЩ�㷵��VK_ERROR_DEVICE_LOST����ȡ������ʱ����� diagnostic checkpoints����Ϣ
			uint32_t checkPointDataCount = 0;
			std::vector<VkCheckpointDataNV> checkpointDataNVs{};
			vkGetQueueCheckpointDataNV(VkQueue{/*��������һ����Ч��VkQueue*/ }/*queue*/, & checkPointDataCount, nullptr);//queue���봦��lost״̬
			checkpointDataNVs.resize(checkPointDataCount);
			vkGetQueueCheckpointDataNV(VkQueue{/*��������һ����Ч��VkQueue*/ }, & checkPointDataCount, checkpointDataNVs.data());//������ȷ����������
			VkCheckpointDataNV& checkpointDataNV = checkpointDataNVs[0];
			checkpointDataNV.sType = VK_STRUCTURE_TYPE_CHECKPOINT_DATA_NV;
			checkpointDataNV.pNext = nullptr;
			checkpointDataNV.stage = VK_PIPELINE_STAGE_COMPUTE_SHADER_BIT;//ָ��һ��checkpoint marker �������õ���һ��pipeline stage
			uint32_t markerData = 0;
			checkpointDataNV.pCheckpointMarker = &markerData;//������stage��ִ�е����һ��checkpoint marker��ֵ


		}


		//Device Fault Diagnosis  �μ�p4214
		{
			//��ȡ�������device loss�Ĵ���������Ϣ
			VkDeviceFaultCountsEXT deviceFaultCountsEXT{};
			deviceFaultCountsEXT.sType = VK_STRUCTURE_TYPE_DEVICE_FAULT_COUNTS_EXT;
			deviceFaultCountsEXT.pNext = nullptr;
			deviceFaultCountsEXT.addressInfoCount = 0;// VkDeviceFaultAddressInfoEXT�������������������ҳ���ϵ��ڴ���ʻ����Ǹù��Ϸ����ǵ�activeָ��ĵ�ַ
			deviceFaultCountsEXT.vendorInfoCount = 0;// VkDeviceFaultVendorInfoEXT������������vendor-specific ������Ϣ
			deviceFaultCountsEXT.vendorBinarySize = 0;//Ϊ vendor-specific�����Ʊ���ת����Ϣ���ֽ�����С�������ڵ��뵽�ⲿ����ʱ�ṩ������Ϣ

			VkDeviceFaultInfoEXT deviceFaultInfoEXT{};
			deviceFaultInfoEXT.sType = VK_STRUCTURE_TYPE_DEVICE_FAULT_INFO_EXT;
			deviceFaultInfoEXT.pNext = nullptr;
			deviceFaultInfoEXT.description/*char[VK_MAX_DESCRIPTION_SIZE]*/;//null-terminated UTF-8 string��ָ���û��ɶ��Ĺ�������
			deviceFaultInfoEXT.pAddressInfos = nullptr;//ΪNULL������ VkDeviceFaultAddressInfoEXT����ָ�룬�����������ҳ���ϵ��ڴ���ʻ����Ǹù��Ϸ����ǵ�activeָ��ĵ�ַ�������ΪNULL��ÿ��Ԫ������һ�� GPU virtual address�ռ�İ����򣬸�����������ʵ�GPU virtual address����activeָ���ָ��
			deviceFaultInfoEXT.pVendorInfos = nullptr;//ΪNULL������ VkDeviceFaultVendorInfoEXT����ָ�룬����vendor-specific ������Ϣ
			deviceFaultInfoEXT.pVendorBinaryData = nullptr;//ΪNULL������vendorBinarySize���ֽڵ����ݵ�ָ�룬����vendor-specific�����Ʊ���ת����Ϣ��������p4220 Vendor Binary Crash Dumps


			std::vector<VkDeviceFaultAddressInfoEXT> deviceFaultAddressInfoEXTs{};
			std::vector<VkDeviceFaultVendorInfoEXT> deviceFaultVendorInfoEXTs{};
			std::vector<char> vendorBinaryData{};

			vkGetDeviceFaultInfoEXT(device, &deviceFaultCountsEXT, &deviceFaultInfoEXT);
			/*
			vkGetDeviceFaultInfoEXT��Ч�÷�:
			1.device ����Ϊlost state
			2.���pFaultCounts->addressInfoCount��ֵ��Ϊ0����pFaultInfo->pAddressInfos��ΪNULL����pFaultInfo->pAddressInfos ����һ����pFaultCounts->addressInfoCount��VkDeviceFaultAddressInfoEXTԪ�ص�����ָ��
			3.���pFaultCounts->vendorInfoCount��ֵ��Ϊ0����pFaultInfo->pVendorInfos��ΪNULL����pFaultInfo->pVendorInfos ����һ����pFaultCounts->vendorInfoCount��VkDeviceFaultVendorInfoEXTԪ�ص�����ָ��
			4.���pFaultCounts->vendorBinarySize��ֵ��Ϊ0����pFaultInfo->pVendorBinaryData��ΪNULL����pFaultInfo->pVendorBinaryData ����һ����pFaultCounts->vendorBinarySize���ֽ�Ԫ�ص�����ָ��
			*/

			deviceFaultAddressInfoEXTs.resize(deviceFaultCountsEXT.addressInfoCount);
			deviceFaultVendorInfoEXTs.resize(deviceFaultCountsEXT.vendorInfoCount);
			vendorBinaryData.resize(deviceFaultCountsEXT.vendorBinarySize);
			deviceFaultInfoEXT.pAddressInfos = deviceFaultAddressInfoEXTs.data();
			deviceFaultInfoEXT.pVendorInfos = deviceFaultVendorInfoEXTs.data();
			deviceFaultInfoEXT.pVendorBinaryData = vendorBinaryData.data();

			vkGetDeviceFaultInfoEXT(device, &deviceFaultCountsEXT, &deviceFaultInfoEXT);//������ȷ����������
			VkDeviceFaultAddressInfoEXT &deviceFaultAddressInfoEXT = deviceFaultAddressInfoEXTs[0];
			deviceFaultAddressInfoEXT.addressType = VK_DEVICE_FAULT_ADDRESS_TYPE_WRITE_INVALID_EXT;/*VkDeviceFaultAddressTypeEXTֵ��Ϊ���ҳ���ϵ��ڴ���ʵĲ������ͻ���activeָ��ʹ���֮�����ϵ����
			VkDeviceFaultAddressTypeEXT:
			VK_DEVICE_FAULT_ADDRESS_TYPE_NONE_EXT : ָ��VkDeviceFaultAddressInfoEXT������һ��ҳ���ϻ���һ��ָ���ַ
			VK_DEVICE_FAULT_ADDRESS_TYPE_READ_INVALID_EXT : ָ��VkDeviceFaultAddressInfoEXT����һ�����Ƿ�������������ҳ����
			VK_DEVICE_FAULT_ADDRESS_TYPE_WRITE_INVALID_EXT : ָ��VkDeviceFaultAddressInfoEXT����һ�����Ƿ�д����������ҳ����
			VK_DEVICE_FAULT_ADDRESS_TYPE_EXECUTE_INVALID_EXT : ����һ���г���ִ��non-executable memory������ҳ����
			VK_DEVICE_FAULT_ADDRESS_TYPE_INSTRUCTION_POINTER_UNKNOWN_EXT : �ڹ��Ϸ���ʱָ��һ��ָ��ָ�룬ָ����ָ����ܺ͹����й�
			VK_DEVICE_FAULT_ADDRESS_TYPE_INSTRUCTION_POINTER_INVALID_EXT : ָ��һ���зǷ�ָ������ָ��ָ��
			VK_DEVICE_FAULT_ADDRESS_TYPE_INSTRUCTION_POINTER_FAULT_EXT : ָ��һ���͹����йص�ָ��ָ��
			
			*/
			deviceFaultAddressInfoEXT.reportedAddress = 0;//Ϊdevice��¼��GPU virtual address
			deviceFaultAddressInfoEXT.addressPrecision = 0;//Ϊ2��ָ����ָ��device���Լ�¼�ĵ�ַ�ľ��ȣ���reportedAddress���Թ�ͬ����һ����Ч�ĵ�ַ��Χ


			VkDeviceFaultVendorInfoEXT& deviceFaultVendorInfoEXT = deviceFaultVendorInfoEXTs[0];
			deviceFaultVendorInfoEXT.description[VK_MAX_DESCRIPTION_SIZE];//����null-terminated UTF-8 string�������û��ɶ��Ĺ�����Ϣ
			deviceFaultVendorInfoEXT.vendorFaultCode;//Ϊ�ù��ϵ�vendor-specific ������
			deviceFaultVendorInfoEXT.vendorFaultData;//Ϊ�������ù��ϵ�vendor-specific ��������

			//vendor-specific binary crash dump���ݵĸ�ʽ�Ը���vendor���ܲ�����ͬ������Ϊ�����ֲ���ȷ������Щ���ݣ�д�뵽VkDeviceFaultInfoEXT::pVendorBinaryData���ʼ���ֽڱ������һ��ͷ��Ϣ����ʽΪ
			VkDeviceFaultVendorBinaryHeaderVersionOneEXT deviceFaultVendorBinaryHeaderVersionOneEXT{};
			deviceFaultVendorBinaryHeaderVersionOneEXT.headerSize = sizeof(VkDeviceFaultVendorBinaryHeaderVersionOneEXT);//Ϊcrash dump header���ֽ�����С
			deviceFaultVendorBinaryHeaderVersionOneEXT.headerVersion = VK_DEVICE_FAULT_VENDOR_BINARY_HEADER_VERSION_ONE_EXT;//һ�� VkDeviceFaultVendorBinaryHeaderVersionEXT ֵ��ָ��header�汾
			deviceFaultVendorBinaryHeaderVersionOneEXT.vendorID = 0;//Ϊʵ�ֵ�VkPhysicalDeviceProperties::vendorID
			deviceFaultVendorBinaryHeaderVersionOneEXT.deviceID = 0;//Ϊʵ�ֵ�VkPhysicalDeviceProperties::deviceID
			deviceFaultVendorBinaryHeaderVersionOneEXT.driverVersion = 0;//Ϊʵ�ֵ�VkPhysicalDeviceProperties::driverVersion
			deviceFaultVendorBinaryHeaderVersionOneEXT.pipelineCacheUUID[VK_UUID_SIZE];//����ƥ��VkPhysicalDeviceProperties::pipelineCacheUUID���Ե�ֵ
			deviceFaultVendorBinaryHeaderVersionOneEXT.applicationNameOffset = 0;//Ϊ0������Ϊ��crash dump header�Ļ���ַ��ʼ������Ӧ�õ����ֵ�null-terminated UTF-8 string������ƫ�����������Ϊ0�������ƥ�䴴��instanceʱָ����VkApplicationInfo::pApplicationName
			deviceFaultVendorBinaryHeaderVersionOneEXT.applicationVersion = 0;//����Ϊ0���ߴ���instanceʱָ����VkApplicationInfo::applicationVersion
			deviceFaultVendorBinaryHeaderVersionOneEXT.engineNameOffset = 0;//Ϊ0������Ϊ��crash dump header�Ļ���ַ��ʼ���������ڴ���Ӧ�õ�engine�����ֵ�null-terminated UTF-8 string������ƫ�����������Ϊ0�������ƥ�䴴��instanceʱָ���� VkApplicationInfo::pEngineName
			deviceFaultVendorBinaryHeaderVersionOneEXT.engineVersion = 0;//����Ϊ0���ߴ���instanceʱָ����VkApplicationInfo::engineVersion
			deviceFaultVendorBinaryHeaderVersionOneEXT.apiVersion = 0;//����Ϊ0���ߴ���instanceʱָ����VkApplicationInfo::apiVersion


		}


	}


}


NS_TEST_END