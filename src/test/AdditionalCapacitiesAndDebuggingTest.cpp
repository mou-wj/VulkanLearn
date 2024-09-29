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

	}




}

void AdditionalCapacitiesAndDebuggingTest::DebuggingTest()
{
}


NS_TEST_END