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

	//Additional Image Capabilities  参见p4122
	{
		//额外的image capabilities，为比如对指定image type的更大的维度以及额外的采样点数量，或者linear tiling format额外的额外的image capabilities

		//查询指定image type的额外的image capabilities
		VkImageFormatProperties imageFormatProperties{};
		VkResult result/*如果参数的组合不支持则会返回VK_ERROR_FORMAT_NOT_SUPPORTED*/ = vkGetPhysicalDeviceImageFormatProperties(physicalDevice, VK_FORMAT_R8G8B8_UINT/*format*/, VK_IMAGE_TYPE_2D/*type*/, VK_IMAGE_TILING_LINEAR/*tiling，不能为VK_IMAGE_TILING_DRM_FORMAT_MODIFIER_EXT*/,
			VK_IMAGE_USAGE_SAMPLED_BIT/*usage*/, VK_IMAGE_CREATE_2D_ARRAY_COMPATIBLE_BIT/*flags*/, &imageFormatProperties/*pImageFormatProperties,返回结果*/);//假设正确返回结果
		imageFormatProperties.maxExtent = VkExtent3D{ .width = 1,.height = 1,.depth = 1 };//为支持的最大的image的维度
		imageFormatProperties.maxMipLevels = 10;//为支持的mipmap levels的最大数量，其他描述见p4124
		imageFormatProperties.maxArrayLayers = 10;//为支持的array layers的最大数量，其他描述见p4124
		imageFormatProperties.sampleCounts = VK_SAMPLE_COUNT_16_BIT;//VkSampleCountFlagBits 组合值位掩码，指明image支持的采样点数目
		imageFormatProperties.maxResourceSize = 1000;//为所有image 资源所占据的字节总数的最大数量，至少是pow(2,32)-1



		//确定和 external memory handle type兼容的 image capabilities
		VkExternalImageFormatPropertiesNV externalImageFormatPropertiesNV{};
		vkGetPhysicalDeviceExternalImageFormatPropertiesNV(physicalDevice, VK_FORMAT_R8G8B8_UINT/*format*/, VK_IMAGE_TYPE_2D/*type*/, VK_IMAGE_TILING_LINEAR/*tiling，不能为VK_IMAGE_TILING_DRM_FORMAT_MODIFIER_EXT*/,
			VK_IMAGE_USAGE_SAMPLED_BIT/*usage*/, VK_IMAGE_CREATE_2D_ARRAY_COMPATIBLE_BIT/*flags*/, VK_EXTERNAL_MEMORY_HANDLE_TYPE_D3D11_IMAGE_BIT_NV/*externalHandleType ，VkExternalMemoryHandleTypeFlagBitsNV*/, &externalImageFormatPropertiesNV/*pExternalImageFormatProperties，返回结果*/);//假设正确返回结果
		externalImageFormatPropertiesNV.imageFormatProperties = imageFormatProperties;//VkImageFormatProperties类型
		externalImageFormatPropertiesNV.externalMemoryFeatures;/*VkExternalMemoryFeatureFlagBitsNV 组合值位掩码，指明externalHandleType的属性
		VkExternalMemoryFeatureFlagBitsNV:
		VK_EXTERNAL_MEMORY_FEATURE_DEDICATED_ONLY_BIT_NV : 指明指定type的外部memory可以以独有分配创建
		VK_EXTERNAL_MEMORY_FEATURE_EXPORTABLE_BIT_NV : 指定实现支持导出指定类型的句柄
		VK_EXTERNAL_MEMORY_FEATURE_IMPORTABLE_BIT_NV : 指定实现支持导入指定类型的句柄
		*/
		externalImageFormatPropertiesNV.exportFromImportedHandleTypes;//VkExternalMemoryHandleTypeFlagBitsNV组合值位掩码，指明可以从externalHandleType上导入创建内存的一组external memory handle types
		externalImageFormatPropertiesNV.compatibleHandleTypes;//VkExternalMemoryHandleTypeFlagBitsNV组合值位掩码，指明调用vkAllocateMemory时可以和externalHandleType一同指定的一组external memory handle types


		//查询指定image type的额外的image capabilities 2
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
					androidHardwareBufferUsageANDROID.sType = VK_STRUCTURE_TYPE_MAX_ENUM;//没有定义这里定义为非法值
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


			VkImageFormatProperties2 imageFormatProperties2{};//等价于VkImageFormatProperties2KHR
			imageFormatProperties2.sType = VK_STRUCTURE_TYPE_IMAGE_FORMAT_PROPERTIES_2;
			ImageFormatProperties2EXT imageFormatProperties2EXT{};
			//VkImageFormatProperties2.pNext
			{
				//VkTextureLODGatherFormatPropertiesAMD,用于确定使用显式LOD 以及/或者 bias 参数的texture gather functions 是否可以用于指定的image format
				VkTextureLODGatherFormatPropertiesAMD& textureLODGatherFormatPropertiesAMD = imageFormatProperties2EXT.textureLODGatherFormatPropertiesAMD;
				textureLODGatherFormatPropertiesAMD.supportsTextureGatherLODBiasAMD = VK_FALSE;//说明指定image format是否可以用于texture gather bias/LOD functions

				//VkExternalImageFormatProperties， 等价于VkExternalImageFormatPropertiesKHR，用于确定使用显式LOD 以及/或者 bias 参数的texture gather functions 是否可以用于指定的image format
				VkExternalImageFormatProperties& externalImageFormatProperties = imageFormatProperties2EXT.externalImageFormatProperties;
				VkExternalMemoryProperties externalMemoryProperties{}; //等价于VkExternalMemoryPropertiesKH
				{
					externalMemoryProperties.externalMemoryFeatures = VK_EXTERNAL_MEMORY_FEATURE_DEDICATED_ONLY_BIT;/* VkExternalMemoryFeatureFlagBits组合值位掩码，指明handleType的特性
					VkExternalMemoryFeatureFlagBits 等价于VkExternalMemoryFeatureFlagBitsKHR :
					VK_EXTERNAL_MEMORY_FEATURE_DEDICATED_ONLY_BIT : 说明以指定的参数和handle type创建的images或者buffers必须使用VkMemoryDedicatedRequirements 以及 VkMemoryDedicatedAllocateInfo定义的机制来创建或者导入一个image或者buffer的dedicated allocation
					VK_EXTERNAL_MEMORY_FEATURE_EXPORTABLE_BIT : 指定这个类型的handles可以从vulkan memory对象中导出
					VK_EXTERNAL_MEMORY_FEATURE_IMPORTABLE_BIT : 指定这个类型的handles可以导入作为vulkan memory对象
					*/
					externalMemoryProperties.exportFromImportedHandleTypes = VK_EXTERNAL_MEMORY_HANDLE_TYPE_D3D11_TEXTURE_KMT_BIT;// VkExternalMemoryHandleTypeFlagBits组合值位掩码，指明哪些类型的导入句柄可以导出handleType
					externalMemoryProperties.compatibleHandleTypes = VK_EXTERNAL_MEMORY_HANDLE_TYPE_D3D11_TEXTURE_KMT_BIT;// VkExternalMemoryHandleTypeFlagBits组合值位掩码，指明当以handleType创建一个和外部内存兼容的image的同时还可以指定哪些handle types
				}
				externalImageFormatProperties.externalMemoryProperties = externalMemoryProperties;//指明一个external handle type 用于创建不同参数的image对应的不同的属性


				//VkSamplerYcbcrConversionImageFormatProperties， 等价于VkSamplerYcbcrConversionImageFormatPropertiesKHR，用于确定支持一个 multi-planar format需要的combined image samplers的数量
				VkSamplerYcbcrConversionImageFormatProperties& samplerYcbcrConversionImageFormatProperties = imageFormatProperties2EXT.samplerYcbcrConversionImageFormatProperties;
				samplerYcbcrConversionImageFormatProperties.combinedImageSamplerDescriptorCount = 1;//指明用于访问format的combined image sampler descriptors的数量

				
				//VkAndroidHardwareBufferUsageANDROID，用于确定支持一个 multi-planar format需要的combined image samplers的数量
				VkAndroidHardwareBufferUsageANDROID& androidHardwareBufferUsageANDROID = imageFormatProperties2EXT.androidHardwareBufferUsageANDROID;
				androidHardwareBufferUsageANDROID.androidHardwareBufferUsage = 0;//返回 Android hardware buffer usage flags，每个bit对应形如AHARDWAREBUFFER_USAGE_GPU_*的用法，列举在 AHardwareBuffer Usage Equivalence p989


				//VkHostImageCopyDevicePerformanceQueryEXT，用于确定使用VK_IMAGE_USAGE_HOST_TRANSFER_BIT_EXT 是否对访问image的device性能有不利影响
				VkHostImageCopyDevicePerformanceQueryEXT& hostImageCopyDevicePerformanceQueryEXT = imageFormatProperties2EXT.hostImageCopyDevicePerformanceQueryEXT;
				hostImageCopyDevicePerformanceQueryEXT.optimalDeviceAccess = VK_FALSE;//指明参数完全相同，且绑定到相同VkDeviceMemory创建的image，在只是将VK_IMAGE_USAGE_HOST_TRANSFER_BIT_EXT被替换为VK_IMAGE_USAGE_TRANSFER_SRC_BIT和VK_IMAGE_USAGE_TRANSFER_DST_BIT的host image copy 是否device访问性能没有不利影响
				hostImageCopyDevicePerformanceQueryEXT.identicalMemoryLayout = VK_FALSE;//指明参数完全相同，且绑定到相同VkDeviceMemory创建的image，在只是将VK_IMAGE_USAGE_HOST_TRANSFER_BIT_EXT被替换为VK_IMAGE_USAGE_TRANSFER_SRC_BIT和VK_IMAGE_USAGE_TRANSFER_DST_BIT的host image copy 是否在内存布局上没有影响


				//VkFilterCubicImageViewImageFormatPropertiesEXT，用于确定指定image format以及image view type是否支持cubic filtering
				VkFilterCubicImageViewImageFormatPropertiesEXT& filterCubicImageViewImageFormatPropertiesEXT = imageFormatProperties2EXT.filterCubicImageViewImageFormatPropertiesEXT;
				filterCubicImageViewImageFormatPropertiesEXT.filterCubic = VK_FALSE;//指明是否指定的image format, image type 以及 image view type可以和cubic filtering一起使用
				filterCubicImageViewImageFormatPropertiesEXT.filterCubicMinmax = VK_FALSE;//指明是否指定的image format, image type 以及 image view type可以和cubic filtering以及minmax filtering一起使用


			}
			imageFormatProperties2.pNext = &imageFormatProperties2EXT.androidHardwareBufferUsageANDROID;
			imageFormatProperties2.imageFormatProperties;//VkImageFormatProperties 类型


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

			VkPhysicalDeviceImageFormatInfo2 physicalDeviceImageFormatInfo2{};//等价于VkPhysicalDeviceImageFormatInfo2KHR
			physicalDeviceImageFormatInfo2.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_IMAGE_FORMAT_INFO_2;
			PhysicalDeviceImageFormatInfo2EXT physicalDeviceImageFormatInfo2EXT{};
			//VkPhysicalDeviceImageFormatInfo2.pNext
			{
				//VkPhysicalDeviceExternalImageFormatInfo，等价于VkPhysicalDeviceExternalImageFormatInfoKHR ,用于确定和指定external memory handle type兼容的image capabilities
				VkPhysicalDeviceExternalImageFormatInfo& physicalDeviceExternalImageFormatInfo = physicalDeviceImageFormatInfo2EXT.physicalDeviceExternalImageFormatInfo;
				physicalDeviceExternalImageFormatInfo.handleType = VK_EXTERNAL_MEMORY_HANDLE_TYPE_D3D11_TEXTURE_BIT;/* VkExternalMemoryHandleTypeFlagBits 值，指明image关联的memory的memory handle type
				VkExternalMemoryHandleTypeFlagBits 等价于VkExternalMemoryHandleTypeFlagBitsKHR:
				VK_EXTERNAL_MEMORY_HANDLE_TYPE_OPAQUE_FD_BIT : 指明一个在vulkan或者其他兼容APIs外只含有有限有效用法的POSIX file descriptor handle，其他描述见p4136
				VK_EXTERNAL_MEMORY_HANDLE_TYPE_OPAQUE_WIN32_BIT  : 指明一个在vulkan或者其他兼容APIs外只含有有限有效用法的NT handle，其他描述见p4136
				VK_EXTERNAL_MEMORY_HANDLE_TYPE_OPAQUE_WIN32_KMT_BIT : 指明一个在vulkan或者其他兼容APIs外只含有有限有效用法的global share handle，其他描述见p4136
				VK_EXTERNAL_MEMORY_HANDLE_TYPE_D3D11_TEXTURE_BIT : 指定一个引用到Direct3D 10 或者 11 texture resource的IDXGIResource1::CreateSharedHandle返回的NT handle，其他描述见p4136
				VK_EXTERNAL_MEMORY_HANDLE_TYPE_D3D11_TEXTURE_KMT_BIT : 指定一个引用到Direct3D 10 或者 11 texture resource的IDXGIResource1::GetSharedHandle返回的global share handle，其他描述见p4136
				VK_EXTERNAL_MEMORY_HANDLE_TYPE_D3D12_HEAP_BIT : 指定一个引用到Direct3D 12 heap resource的ID3D12Device::CreateSharedHandle返回的NT handle，其他描述见p4136
				VK_EXTERNAL_MEMORY_HANDLE_TYPE_D3D12_RESOURCE_BIT : 指定一个引用到Direct3D 12 committed resource的ID3D12Device::CreateSharedHandle返回的NT handle，其他描述见p4136
				VK_EXTERNAL_MEMORY_HANDLE_TYPE_HOST_ALLOCATION_BIT_EXT : 指定一个通过host memory allocation command分配的host pointer，其他描述见p4136
				VK_EXTERNAL_MEMORY_HANDLE_TYPE_HOST_MAPPED_FOREIGN_MEMORY_BIT_EXT: 指定一个通过host映射获取的host pointer，其他描述见p4136
				VK_EXTERNAL_MEMORY_HANDLE_TYPE_DMA_BUF_BIT_EXT : 为一个Linux dma_buf的一个file descriptor，其他描述见p4136
				VK_EXTERNAL_MEMORY_HANDLE_TYPE_ANDROID_HARDWARE_BUFFER_BIT_ANDROID : 指定一个由Android NDK定义的AHardwareBuffer对象，其他描述见p4136
				VK_EXTERNAL_MEMORY_HANDLE_TYPE_ZIRCON_VMO_BIT_FUCHSIA : 为一个虚拟内存对象的Zircon handle
				VK_EXTERNAL_MEMORY_HANDLE_TYPE_RDMA_ADDRESS_BIT_NV : 为被remote devices访问的一个分配区的句柄，该句柄拥有Vulkan memory对象表示的底层内存资源的引用
				VK_EXTERNAL_MEMORY_HANDLE_TYPE_SCREEN_BUFFER_BIT_QNX : 指定一个由QNX SDP定义的_screen_buffer对象，其他描述见p4137

				一些 external memory handle types可以在相同的底层physical device以及或者相同的device版本中共享，其相关信息见p4138 Table 91. External memory handle types compatibility
				*/



				//VkPhysicalDeviceImageDrmFormatModifierInfoEXT，用于查询和 Linux DRM format modifier兼容的image capabilities
				VkPhysicalDeviceImageDrmFormatModifierInfoEXT& physicalDeviceImageDrmFormatModifierInfoEXT = physicalDeviceImageFormatInfo2EXT.physicalDeviceImageDrmFormatModifierInfoEXT;
				physicalDeviceImageDrmFormatModifierInfoEXT.drmFormatModifier = 0;//为image的Linux DRM format modifier，对应到VkImageDrmFormatModifierExplicitCreateInfoEXT::modifier 或者VkImageDrmFormatModifierListCreateInfoEXT::pModifiers中的元素
				physicalDeviceImageDrmFormatModifierInfoEXT.sharingMode = VK_SHARING_MODE_EXCLUSIVE;//指定image的共享模式
				physicalDeviceImageDrmFormatModifierInfoEXT.queueFamilyIndexCount = 1;//指定访问image的队列族的数量
				uint32_t queueFamily = 0;
				physicalDeviceImageDrmFormatModifierInfoEXT.pQueueFamilyIndices = &queueFamily;//指定访问image的队列族的索引，如果 sharingMode 不为 VK_SHARING_MODE_CONCURRENT则忽略
				/*
				VkPhysicalDeviceImageDrmFormatModifierInfoEXT有效用法:
				1.如果sharingMode 为VK_SHARING_MODE_CONCURRENT，则（1）pQueueFamilyIndices必须为有效的queueFamilyIndexCount个uint32_t值的数组的指针
																  （2）queueFamilyIndexCount 必须大于1
																  （3）pQueueFamilyIndices中每个元素必须是唯一的且必须小于vkGetPhysicalDeviceQueueFamilyProperties2返回的用于创建device的pQueueFamilyPropertyCount的值指明的队列族的个数
				*/


				//VkPhysicalDeviceImageViewImageFormatInfoEXT，用于确定是否cubic filtering可以和指定的image format和image type一起使用
				VkPhysicalDeviceImageViewImageFormatInfoEXT& physicalDeviceImageViewImageFormatInfoEXT = physicalDeviceImageFormatInfo2EXT.physicalDeviceImageViewImageFormatInfoEXT;
				physicalDeviceImageViewImageFormatInfoEXT.imageViewType = VK_IMAGE_VIEW_TYPE_2D;// VkImageViewType 值指明image view的类型


			}
			physicalDeviceImageFormatInfo2.pNext = nullptr;
			physicalDeviceImageFormatInfo2.format = VK_FORMAT_R8_UNORM;//VkFormat，指定image format
			physicalDeviceImageFormatInfo2.type = VK_IMAGE_TYPE_2D;//VkImageType，指定image type
			physicalDeviceImageFormatInfo2.tiling = VK_IMAGE_TILING_LINEAR;//VkImageTiling，指定image tiling
			physicalDeviceImageFormatInfo2.usage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;//VkImageUsageFlagBits组合值位掩码，指定image usages
			physicalDeviceImageFormatInfo2.flags = VK_IMAGE_CREATE_2D_ARRAY_COMPATIBLE_BIT;//VkImageCreateFlagBits组合值位掩码，指定image flags
			/*
			VkPhysicalDeviceImageFormatInfo2有效用法:
			1.如果pNext中包含 VkPhysicalDeviceImageDrmFormatModifierInfoEXT ，则tiling必须为VK_IMAGE_TILING_DRM_FORMAT_MODIFIER_EXT
			2.如果tiling 为VK_IMAGE_TILING_DRM_FORMAT_MODIFIER_EXT且flags中包含VK_IMAGE_CREATE_MUTABLE_FORMAT_BIT ，则pNext中必须包含  viewFormatCount不为0的VkImageFormatListCreateInfo
			*/


			vkGetPhysicalDeviceImageFormatProperties2(physicalDevice, &physicalDeviceImageFormatInfo2, &imageFormatProperties2);//假设正确返回结果
			/*
			vkGetPhysicalDeviceImageFormatProperties2有效用法:
			1.如果pImageFormatProperties->pNext中包含一个VkAndroidHardwareBufferUsageANDROID，则pImageFormatInfo->pNext中必须包含一个handleType指定为VK_EXTERNAL_MEMORY_HANDLE_TYPE_ANDROID_HARDWARE_BUFFER_BIT_ANDROID的VkPhysicalDeviceExternalImageFormatInfo
			2.如果pImageFormatProperties->pNext中包含一个VkHostImageCopyDevicePerformanceQueryEXT，则pImageFormatInfo->usage 必须包含VK_IMAGE_USAGE_HOST_TRANSFER_BIT_EXT
			*/
		}


		//Supported Sample Counts  描述一些情况下vkGetPhysicalDeviceImageFormatProperties调用返回的sampleCounts的情况， 详细情况参见p4148 

		//Allowed Extent Values Based on Image Type ，实现支持在一些情况下image的范围超过limit中列举的指定image类型的最大最小值，这些情况的详细描述参见p4149

	}


	//Additional Buffer Capabilities  参见p4149
	{

		//查询buffers支持的 external handle types
		VkPhysicalDeviceExternalBufferInfo physicalDeviceExternalBufferInfo{};//等价于VkPhysicalDeviceExternalBufferInfoKHR
		physicalDeviceExternalBufferInfo.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_EXTERNAL_BUFFER_INFO;
		physicalDeviceExternalBufferInfo.pNext = nullptr;//可以包含一个VkBufferUsageFlags2CreateInfoKHR
		physicalDeviceExternalBufferInfo.flags = VK_BUFFER_CREATE_SPARSE_BINDING_BIT;// VkBufferCreateFlagBits 组合值位掩码，指明buffer的额外参数，对应 VkBufferCreateInfo::flags
		physicalDeviceExternalBufferInfo.usage = VK_BUFFER_USAGE_INDEX_BUFFER_BIT;// VkBufferUsageFlagBits 组合值位掩码，指明buffer的预期用途，对应 VkBufferCreateInfo::usage
		physicalDeviceExternalBufferInfo.handleType = VK_EXTERNAL_MEMORY_HANDLE_TYPE_D3D11_TEXTURE_BIT;// VkExternalMemoryHandleTypeFlagBits值，指明用于buffer关联的memory的 memory handle type
		/*
		VkPhysicalDeviceExternalBufferInfo有效用法:
		1.如果pNext中不包含一个 VkBufferUsageFlags2CreateInfoKHR，则 usage必须是一个有效的 VkBufferUsageFlagBits组合值，不能为0
		
		
		*/

		VkExternalBufferProperties externalBufferProperties{};//等价于VkExternalBufferPropertiesKHR
		externalBufferProperties.sType = VK_STRUCTURE_TYPE_EXTERNAL_BUFFER_PROPERTIES;
		externalBufferProperties.pNext = nullptr;
		VkExternalMemoryProperties externalMemoryProperties{/*假设这是一个有效的VkExternalMemoryProperties*/};//前面已经描述过，这里不再描述
		externalBufferProperties.externalMemoryProperties = externalMemoryProperties;//指明一个external handle type 用于创建不同参数的buffer对应的不同的属性

		//等价于vkGetPhysicalDeviceExternalBufferPropertiesKHR
		vkGetPhysicalDeviceExternalBufferProperties(physicalDevice, &physicalDeviceExternalBufferInfo, &externalBufferProperties);




	}


	//Optional Semaphore Capabilities  参见p4152
	{
		//semaphores 可能会导入或导出其payload到外部的句柄，查询semaphores支持的外部句柄类型
		VkPhysicalDeviceExternalSemaphoreInfo physicalDeviceExternalSemaphoreInfo{};//等价于VkPhysicalDeviceExternalSemaphoreInfoKHR
		physicalDeviceExternalSemaphoreInfo.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_EXTERNAL_SEMAPHORE_INFO;
		physicalDeviceExternalSemaphoreInfo.pNext = nullptr;
		physicalDeviceExternalSemaphoreInfo.handleType = VK_EXTERNAL_SEMAPHORE_HANDLE_TYPE_OPAQUE_WIN32_BIT;/*VkExternalSemaphoreHandleTypeFlagBits 值，指明要查询属性的external semaphore handle type
		VkExternalSemaphoreHandleTypeFlagBits 等价于VkExternalSemaphoreHandleTypeFlagBitsKHR:
		VK_EXTERNAL_SEMAPHORE_HANDLE_TYPE_OPAQUE_FD_BIT : 指明一个在vulkan以及其他兼容的APIs之外含有有限有效用法的POSIX file descriptor handle，其他详细描述见p4154
		VK_EXTERNAL_SEMAPHORE_HANDLE_TYPE_OPAQUE_WIN32_BIT : 指明一个在vulkan以及其他兼容的APIs之外含有有限有效用法的NT handle ，其他详细描述见p4154
		VK_EXTERNAL_SEMAPHORE_HANDLE_TYPE_OPAQUE_WIN32_KMT_BIT : 指明一个在vulkan以及其他兼容的APIs之外含有有限有效用法的 global share handle，其他详细描述见p4155
		VK_EXTERNAL_SEMAPHORE_HANDLE_TYPE_D3D12_FENCE_BIT : 指明一个引用到一个Direct3D 12 fence 的ID3D12Device::CreateSharedHandle，或者引用到一个Direct3D 11 fence的ID3D11Device5::CreateFence返回的NT handle，其他详细描述见p4155
		VK_EXTERNAL_SEMAPHORE_HANDLE_TYPE_D3D11_FENCE_BIT : 和VK_EXTERNAL_SEMAPHORE_HANDLE_TYPE_D3D12_FENCE_BIT意思相同
		VK_EXTERNAL_SEMAPHORE_HANDLE_TYPE_SYNC_FD_BIT : 指定一个Linux Sync File 或者 Android Fence object的POSIX file descriptor handle，其他详细描述见p4155
		VK_EXTERNAL_SEMAPHORE_HANDLE_TYPE_ZIRCON_EVENT_BIT_FUCHSIA : 指定一个Zircon event object的句柄，其他详细描述见p4155
		
		一些 external semaphore handle types只能在有相同底层physical device 以及或者相同device版本的情况下才能共享，相关的兼容信息参见p4156 Table 92. External semaphore handle types compatibility
		*/



		VkExternalSemaphoreProperties externalSemaphoreProperties{};//等价于VkExternalSemaphorePropertiesKHR
		externalSemaphoreProperties.sType = VK_STRUCTURE_TYPE_EXTERNAL_SEMAPHORE_PROPERTIES;
		externalSemaphoreProperties.pNext = nullptr;
		externalSemaphoreProperties.exportFromImportedHandleTypes = VK_EXTERNAL_SEMAPHORE_HANDLE_TYPE_OPAQUE_WIN32_BIT;//VkExternalSemaphoreHandleTypeFlagBits 组合值位掩码，指明handleType 可以从哪些类型的imported handle中导出
		externalSemaphoreProperties.compatibleHandleTypes = VK_EXTERNAL_SEMAPHORE_HANDLE_TYPE_OPAQUE_WIN32_BIT;//VkExternalSemaphoreHandleTypeFlagBits 组合值位掩码，指明以handleType 创建semaphore的同时还可以指定哪些handle types
		externalSemaphoreProperties.externalSemaphoreFeatures = VK_EXTERNAL_SEMAPHORE_FEATURE_EXPORTABLE_BIT;/*VkExternalSemaphoreFeatureFlagBits 组合值位掩码，描述 handleType的特性
		VkExternalSemaphoreFeatureFlagBits 等价于VkExternalSemaphoreFeatureFlagBitsKHR :
		VK_EXTERNAL_SEMAPHORE_FEATURE_EXPORTABLE_BIT : 指明该类型的句柄可以从Vulkan semaphore 对象中导出
		VK_EXTERNAL_SEMAPHORE_FEATURE_IMPORTABLE_BIT : 指明该类型的句柄可以导入为Vulkan semaphore 对象
		*/


		//等价于vkGetPhysicalDeviceExternalSemaphorePropertiesKHR
		vkGetPhysicalDeviceExternalSemaphoreProperties(physicalDevice, &physicalDeviceExternalSemaphoreInfo, &externalSemaphoreProperties/*pExternalSemaphoreProperties，返回值*/);


	}



	//Optional Fence Capabilities  参见p4158
	{

	}




}

void AdditionalCapacitiesAndDebuggingTest::DebuggingTest()
{
}


NS_TEST_END