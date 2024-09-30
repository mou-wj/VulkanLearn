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
		//fences 可能会导入或导出其payload到外部的句柄，查询fences支持的外部句柄类型
		VkPhysicalDeviceExternalFenceInfo physicalDeviceExternalFenceInfo{};//等价于VkPhysicalDeviceExternalFenceInfoKHR
		physicalDeviceExternalFenceInfo.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_EXTERNAL_FENCE_INFO;
		physicalDeviceExternalFenceInfo.pNext = nullptr;
		physicalDeviceExternalFenceInfo.handleType = VK_EXTERNAL_FENCE_HANDLE_TYPE_OPAQUE_WIN32_BIT;/* VkExternalFenceHandleTypeFlagBits 值，指明要查询属性的external fence handle type
		VkExternalFenceHandleTypeFlagBits 等价于VkExternalFenceHandleTypeFlagBitsKHR:
		VK_EXTERNAL_FENCE_HANDLE_TYPE_OPAQUE_FD_BIT : 指明一个在vulkan以及其他兼容的APIs之外含有有限有效用法的POSIX file descriptor handle，其他详细描述见p4160
		VK_EXTERNAL_FENCE_HANDLE_TYPE_OPAQUE_WIN32_BIT : 指明一个在vulkan以及其他兼容的APIs之外含有有限有效用法的NT handle ，其他详细描述见p4160
		VK_EXTERNAL_FENCE_HANDLE_TYPE_OPAQUE_WIN32_KMT_BIT : 指明一个在vulkan以及其他兼容的APIs之外含有有限有效用法的 global share handle，其他详细描述见p4160
		VK_EXTERNAL_FENCE_HANDLE_TYPE_SYNC_FD_BIT : 指定一个Linux Sync File 或者 Android Fence object的POSIX file descriptor handle，其他详细描述见p4160


		一些 external fence handle types只能在有相同底层physical device 以及或者相同device版本的情况下才能共享，相关的兼容信息参见p4162 Table 93. External fence handle types compatibility

		*/

		VkExternalFenceProperties externalFenceProperties{};//等价于VkExternalFencePropertiesKHR
		externalFenceProperties.sType = VK_STRUCTURE_TYPE_EXTERNAL_FENCE_PROPERTIES;
		externalFenceProperties.pNext = nullptr;
		externalFenceProperties.exportFromImportedHandleTypes = VK_EXTERNAL_FENCE_HANDLE_TYPE_OPAQUE_WIN32_BIT;//VkExternalFenceHandleTypeFlagBits 组合值位掩码，指明handleType 可以从哪些类型的imported handle中导出
		externalFenceProperties.compatibleHandleTypes = VK_EXTERNAL_FENCE_HANDLE_TYPE_OPAQUE_WIN32_BIT;//VkExternalFenceHandleTypeFlagBits 组合值位掩码，指明以handleType 创建fence的同时还可以指定哪些handle types
		externalFenceProperties.externalFenceFeatures = VK_EXTERNAL_FENCE_FEATURE_EXPORTABLE_BIT;/*VkExternalFenceFeatureFlagBits 组合值位掩码，描述 handleType的特性	
		VkExternalFenceFeatureFlagBits 等价于VkExternalFenceFeatureFlagBitsKHR :
		VK_EXTERNAL_FENCE_FEATURE_EXPORTABLE_BIT : 指明该类型的句柄可以从Vulkan fence 对象中导出
		VK_EXTERNAL_FENCE_FEATURE_IMPORTABLE_BIT : 指明该类型的句柄可以导入为Vulkan fence 对象
		*/



		//等价于vkGetPhysicalDeviceExternalFencePropertiesKHR
		vkGetPhysicalDeviceExternalFenceProperties(physicalDevice, &physicalDeviceExternalFenceInfo, &externalFenceProperties);


	}


	//Timestamp Calibration Capabilities  参见p4164
	{
		//查询physical device支持的timestamp calibration的一组 time domains
		uint32_t timeDomainCount = 0;
		std::vector<VkTimeDomainKHR> timeDomainKHRs{};
		//等价于vkGetPhysicalDeviceCalibrateableTimeDomainsEXT
		vkGetPhysicalDeviceCalibrateableTimeDomainsKHR(physicalDevice, &timeDomainCount, nullptr);
		timeDomainKHRs.resize(timeDomainCount);
		vkGetPhysicalDeviceCalibrateableTimeDomainsKHR(physicalDevice, &timeDomainCount, timeDomainKHRs.data());

	}

}

VkBool32 TestCallBack(
	VkDebugUtilsMessageSeverityFlagBitsEXT           messageSeverity,//指明触发该回调的 VkDebugUtilsMessageSeverityFlagBitsEXT
	VkDebugUtilsMessageTypeFlagsEXT                  messageTypes,//指明触发该回调的 VkDebugUtilsMessageTypeFlagBitsEXT
	const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,//为包含所有callback数据的VkDebugUtilsMessengerCallbackDataEXT
	void* pUserData/*为创建 VkDebugUtilsMessengerEXT时提供的用户定义的数据*/) {//该回调函数内部不能调用任何vulkan函数
	
	VkDebugUtilsMessengerCallbackDataEXT debugUtilsMessengerCallbackDataEXT{};
	debugUtilsMessengerCallbackDataEXT = *pCallbackData;
	debugUtilsMessengerCallbackDataEXT.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CALLBACK_DATA_EXT;
	VkDeviceAddressBindingCallbackDataEXT deviceAddressBindingCallbackDataEXT{};
	{
		//其他描述见p4189
		deviceAddressBindingCallbackDataEXT.sType = VK_STRUCTURE_TYPE_DEVICE_ADDRESS_BINDING_CALLBACK_DATA_EXT;
		deviceAddressBindingCallbackDataEXT.pNext = nullptr;
		deviceAddressBindingCallbackDataEXT.flags = VK_DEVICE_ADDRESS_BINDING_INTERNAL_OBJECT_BIT_EXT;/*VkDeviceAddressBindingFlagBitsEXT 组合值位掩码，指明触发回调的绑定的事件的额外信息
		VkDeviceAddressBindingFlagBitsEXT
		VK_DEVICE_ADDRESS_BINDING_INTERNAL_OBJECT_BIT_EXT : 指明VkDeviceAddressBindingCallbackDataEXT描述一个还没用通过vulkan命令来对host可见的vulkan对象
		*/
		deviceAddressBindingCallbackDataEXT.baseAddress = 0;//指明vulkan 对象所在的虚拟地址空间的开始的GPU-accessible virtual address，也见VkDebugUtilsMessengerCallbackDataEXT.pObjects中指定的
		deviceAddressBindingCallbackDataEXT.size = 1;//为GPU-accessible virtual address空间的字节大小
		deviceAddressBindingCallbackDataEXT.bindingType = VK_DEVICE_ADDRESS_BINDING_TYPE_BIND_EXT;/*VkDeviceAddressBindingTypeEXT值，指明触发回调的绑定的事件的类型
		VkDeviceAddressBindingTypeEXT:
		VK_DEVICE_ADDRESS_BINDING_TYPE_BIND_EXT : 指定一个新的GPU-accessible virtual address范围被绑定
		VK_DEVICE_ADDRESS_BINDING_TYPE_UNBIND_EXT : 指定一个GPU-accessible virtual address范围被解绑
		*/
		

	}
	debugUtilsMessengerCallbackDataEXT.pNext = nullptr;//可能包含一个VkDeviceAddressBindingCallbackDataEXT
	debugUtilsMessengerCallbackDataEXT.flags = 0;//为0保留未来使用
	debugUtilsMessengerCallbackDataEXT.pMessageIdName;//为NULL或者 null-terminated UTF-8 string，指明关联到给定message的message ID的标识
	debugUtilsMessengerCallbackDataEXT.messageIdNumber;//为触发message的ID
	debugUtilsMessengerCallbackDataEXT.pMessage;//为NULL 如果messageTypes为VK_DEBUG_UTILS_MESSAGE_TYPE_DEVICE_ADDRESS_BINDING_BIT_EXT,或者触发message的详细信息的null-terminated UTF-8 string
	debugUtilsMessengerCallbackDataEXT.queueLabelCount;// pQueueLabels 中元素个数
	debugUtilsMessengerCallbackDataEXT.pQueueLabels;//为NULL或者一组在该回调调用时queue中激活的VkDebugUtilsLabelEXT的数组指针
	debugUtilsMessengerCallbackDataEXT.cmdBufLabelCount;//pCmdBufLabels中元素个数
	debugUtilsMessengerCallbackDataEXT.pCmdBufLabels;//为NULL或者一组在该回调调用时command buffer中激活的VkDebugUtilsLabelEXT的数组指针
	debugUtilsMessengerCallbackDataEXT.objectCount;//pObjects 中元素个数
	debugUtilsMessengerCallbackDataEXT.pObjects;//为关联到检测到的问题的一组VkDebugUtilsObjectNameInfoEXT的指针
	
	
	return VK_FALSE;
}

VkBool32 ReportCallBack(
	VkDebugReportFlagsEXT                       flags,//指明触发回调的 VkDebugReportFlagBitsEXT
	VkDebugReportObjectTypeEXT                  objectType,// VkDebugReportObjectTypeEXT值，指明事件触发时使用的或者创建的对象的类型
	uint64_t                                    object,//为检测到事件发生时使用或创建的对象，在objectType不为VK_DEBUG_REPORT_OBJECT_TYPE_UNKNOWN_EXT时有效
	size_t                                      location,//为指明触发事件的(layer, driver, loader)位置，可选参数
	int32_t                                     messageCode,//是layer-defined的值用于测试回调函数
	const char* pLayerPrefix,//null-terminated UTF-8 string，为该回调的调用者的名字缩写
	const char* pMessage,//为触发message的详细信息的null-terminated UTF-8 string
	void* pUserData/*为创建 VkDebugReportCallbackEXT时提供的用户定义的数据*/) {

	return VK_FALSE;
}

void AdditionalCapacitiesAndDebuggingTest::DebuggingTest()
{
	/*
	为了帮助开发人员跟踪应用程序在使用Vulkan时出现的错误，特别是与外部调试器或分析器结合时，可以使用debugging扩展
	
	在debugging 信息中， VkObjectType 枚举值可以用来标识对象类型，VkObjectType有那些值以及其对应那些Vulkan句柄的详情见p4166 - p4169
	*/

	
	//Debug Utilities  参见p4169
	{
		//Object Debug Annotation  描述如何将指定的名字或者二进制信息关联到指定的vulkan对象 ， 参见p4169
		{
			//Object Naming 参见p4170
			VkDebugUtilsObjectNameInfoEXT debugUtilsObjectNameInfoEXT{};
			debugUtilsObjectNameInfoEXT.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT;
			debugUtilsObjectNameInfoEXT.pNext = nullptr;
			debugUtilsObjectNameInfoEXT.objectType = VK_OBJECT_TYPE_IMAGE;// VkObjectType值，指明要指定名字的对象的类型
			debugUtilsObjectNameInfoEXT.objectHandle = (uint64_t)VkImage{/*假设这是一个有效的VkImage*/};//为该对象的句柄
			debugUtilsObjectNameInfoEXT.pObjectName = "my_image";//为NULL或者null-terminated UTF-8 string，指明应用到该对象的名字
			/*
			VkDebugUtilsObjectNameInfoEXT有效用法:
			1.如果objectType 为VK_OBJECT_TYPE_UNKNOWN，则objectHandle 不能为VK_NULL_HANDLE
			2.如果objectType 不为VK_OBJECT_TYPE_UNKNOWN，则objectHandle 必须为VK_NULL_HANDLE或者一个objectType指明的类型的vulkan对象的vulkan句柄

			*/


			//给一个对象提供一个用户定义的名字
			vkSetDebugUtilsObjectNameEXT(device, &debugUtilsObjectNameInfoEXT);
			/*
			vkSetDebugUtilsObjectNameEXT有效用法:
			1.pNameInfo->objectType 不能为VK_OBJECT_TYPE_UNKNOWN
			2.pNameInfo->objectHandle 不能为VK_NULL_HANDLE
			3.如果pNameInfo->objectHandle 是一个有效的instance-level 对象的句柄，device对应的VkDevice必须来自和pNameInfo->objectHandle相同的VkInstance
			4.如果pNameInfo->objectHandle 是一个有效的physical-device-level 对象的句柄，device对应的VkDevice 必须从 pNameInfo->objectHandle对应的VkPhysicalDevice上衍生出来
			5.如果pNameInfo->objectHandle 是一个有效的device-level 对象的句柄，pNameInfo->objectHandle 必须衍生自device对应的VkDevice
			*/


			//Object Data Association  参加p4172
			VkDebugUtilsObjectTagInfoEXT debugUtilsObjectTagInfoEXT{};
			debugUtilsObjectTagInfoEXT.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_TAG_INFO_EXT;
			debugUtilsObjectTagInfoEXT.pNext = nullptr;
			debugUtilsObjectTagInfoEXT.objectType = VK_OBJECT_TYPE_IMAGE;// VkObjectType值，指明要指定名字的对象的类型
			debugUtilsObjectTagInfoEXT.objectHandle = (uint64_t)VkImage{/*假设这是一个有效的VkImage*/ };//为该对象的句柄
			debugUtilsObjectTagInfoEXT.tagName =  0;//为tag的数字标识符
			debugUtilsObjectTagInfoEXT.tagSize = 3;//为附加到vulkan对象上的数据的字节数大小
			debugUtilsObjectTagInfoEXT.pTag = "tag";//为附加到vulkan对象上的数据
			/*
			VkDebugUtilsObjectTagInfoEXT有效用法:
			1.objectType 不能为VK_OBJECT_TYPE_UNKNOWN
			2.objectHandle必须为一个有效的objectType指明的类型的vulkan对象的vulkan句柄
			*/

			//给一个对象附加额外的数据
			vkSetDebugUtilsObjectTagEXT(device, &debugUtilsObjectTagInfoEXT);
			/*
			vkSetDebugUtilsObjectTagEXT有效用法:
			1.如果pTagInfo->objectHandle 是一个有效的instance-level 对象的句柄，device对应的VkDevice必须来自和pNameInfo->objectHandle相同的VkInstance
			2.如果pTagInfo->objectHandle 是一个有效的physical-device-level 对象的句柄，device对应的VkDevice 必须从 pNameInfo->objectHandle对应的VkPhysicalDevice上衍生出来
			3.如果pTagInfo->objectHandle 是一个有效的device-level 对象的句柄，pNameInfo->objectHandle 必须衍生自device对应的VkDevice
			
			*/


		}


		//Queue Labels  描述如何注释和成组提交到队列的工作，参见p4174
		{
			VkQueue queue{/*假设这是一个有效的VkQueue*/ };

			//queue debug label region可以用来标记哪个queue的哪个位置正在执行


			VkDebugUtilsLabelEXT debugUtilsLabelEXT{};
			debugUtilsLabelEXT.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_LABEL_EXT;
			debugUtilsLabelEXT.pNext = nullptr;
			debugUtilsLabelEXT.pLabelName = "my_label";//null-terminated UTF-8 string，指明label的名字
			debugUtilsLabelEXT.color/*float[4]*/;//一个可选的关联到label的RGBA颜色值，每个元素范围为0-1

			//开启一个queue debug label region
			vkQueueBeginDebugUtilsLabelEXT(queue, &debugUtilsLabelEXT);

			//结束一个queue debug label region
			vkQueueEndDebugUtilsLabelEXT(queue);//该命令调用之前必须有一个配对的vkQueueBeginDebugUtilsLabelEXT


			//将一个label插入一个queue
			vkQueueInsertDebugUtilsLabelEXT(queue, &debugUtilsLabelEXT);

		}

		//Command Buffer Labels  描述如何关联VkCommandBuffer中的场景中的逻辑元素 ,参加p4177
		{
			VkCommandBuffer commandBuffer{/*假设这是一个有效的VkCommandBuffer*/ };

			//command buffer debug label可以用来标记哪个command buffer的哪个位置正在执行

			VkDebugUtilsLabelEXT debugUtilsLabelEXT{};
			debugUtilsLabelEXT.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_LABEL_EXT;
			debugUtilsLabelEXT.pNext = nullptr;
			debugUtilsLabelEXT.pLabelName = "my_label";//null-terminated UTF-8 string，指明label的名字
			debugUtilsLabelEXT.color/*float[4]*/;//一个可选的关联到label的RGBA颜色值，每个元素范围为0-1

			//定义一个command buffer上debug label region的开始
			vkCmdBeginDebugUtilsLabelEXT(commandBuffer, &debugUtilsLabelEXT);

			//关闭一个command debug label region
			vkCmdEndDebugUtilsLabelEXT(commandBuffer);//commandBuffer记录之前必须有一个配对的vkCmdBeginDebugUtilsLabelEXT

			//往command buffer中插入一个debug label
			vkCmdInsertDebugUtilsLabelEXT(commandBuffer, &debugUtilsLabelEXT);

		}

		//Debug Messengers   描述如何创建一个关联到应用的使用回调函数捕获vulkan不同部分的调试信息的debug messenger ,参见p4181
		{
			//vulkan允许应用注册回调函数来获取调试信息，其中这些回调函数的主要调用者为 validation layers，被debug messagers 触发，

			VkDebugUtilsMessengerEXT debugUtilsMessengerEXT{};

			//创建一个触发debug callback的debug messenger
			VkDebugUtilsMessengerCreateInfoEXT debugUtilsMessengerCreateInfoEXT{};
			debugUtilsMessengerCreateInfoEXT.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
			debugUtilsMessengerCreateInfoEXT.pNext = nullptr;
			debugUtilsMessengerCreateInfoEXT.flags = 0;//为0保留未来使用
			debugUtilsMessengerCreateInfoEXT.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;/*VkDebugUtilsMessageSeverityFlagBitsEXT组合值位掩码，指明那种程度的事件会触发回调函数的调用
			VkDebugUtilsMessageSeverityFlagBitsEXT:
			VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT : 指明应该捕获能够指明vulkan loaders，layers以及drivers的所有诊断信息的详细输出
			VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT : 指明表示信息的消息比如当调试应用时可能处理的资源细节
			VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT : 指明vulkan的使用可能会暴露一个应用bug，这些情况可能不会立即损害程序执行，只是一个警告。
			VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT : 指明应用遇到一个违反vulkan的有效用法的错误

			*/
			debugUtilsMessengerCreateInfoEXT.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;/* VkDebugUtilsMessageTypeFlagBitsEXT 组合值位掩码，指明那种类型的事件会触发回调函数的调用
			VkDebugUtilsMessageTypeFlagBitsEXT:
			VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT : 指明一些常规事件发生，即non-specification, non-performance event
			VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT : 指明一些发生在validation 中违反Vulkan specification的可能指明invalid behavior的事件
			VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT : 指明一个潜在的vulkan的非最优用法，比如当VkAttachmentDescription::loadOp设置为VK_ATTACHMENT_LOAD_OP_CLEAR时调用vkCmdClearColorImage
			VK_DEBUG_UTILS_MESSAGE_TYPE_DEVICE_ADDRESS_BINDING_BIT_EXT : 指明实现已经修改了关联到vulkan对象的GPU-visible virtual addresses
			*/
			debugUtilsMessengerCreateInfoEXT.pfnUserCallback = &TestCallBack;//回调函数的函数地址
			debugUtilsMessengerCreateInfoEXT.pUserData = "test_userdata";//一个用户定义的传递给回调函数的对应参数的数据



			//在有些情况下用户希望有意的提交一个debug messager,触发一个回调
			VkDebugUtilsMessengerCallbackDataEXT debugUtilsMessengerCallbackDataEXT{};//回调函数中已经描述，这里不再复述
			vkSubmitDebugUtilsMessageEXT(instance, VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT, VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT, &debugUtilsMessengerCallbackDataEXT);// pCallbackData->pObjects中每个元素的objectType 不能为VK_OBJECT_TYPE_UNKNOWN


			//销毁一个debug messager
			vkDestroyDebugUtilsMessengerEXT(instance, debugUtilsMessengerEXT, nullptr);
			/*
			vkDestroyDebugUtilsMessengerEXT有效用法:
			1.如果创建messager时提供了一个 VkAllocationCallbacks，则这里必须提供一个兼容的
			2.如果创建messager时没有提供VkAllocationCallbacks，则pAllocator 必须为NULL

			*/

		}

	}



	//Debug Markers  参见p4193
	{
		//Debug markers为debugging 以及 validation layers提供了一种灵活的方式来获取注释和调试信息

		//Object Annotation   描述如何将名字和二进制数据关联到vulkan对象， 参见p4193
		{

			
			VkDebugMarkerObjectNameInfoEXT debugMarkerObjectNameInfoEXT{};
			debugMarkerObjectNameInfoEXT.sType = VK_STRUCTURE_TYPE_DEBUG_MARKER_OBJECT_NAME_INFO_EXT;
			debugMarkerObjectNameInfoEXT.pNext = nullptr;
			debugMarkerObjectNameInfoEXT.objectType = VK_DEBUG_REPORT_OBJECT_TYPE_IMAGE_EXT;//  VkDebugReportObjectTypeEXT值，指明要指定名字的对象的类型
			debugMarkerObjectNameInfoEXT.object = (uint64_t)VkImage{/*假设这是一个有效的VkImage*/ };//为该对象的句柄
			debugMarkerObjectNameInfoEXT.pObjectName = "my_image";//为NULL或者null-terminated UTF-8 string，指明应用到该对象的名字
			/*
			VkDebugMarkerObjectNameInfoEXT有效用法:
			1.objectType 不能为 VK_DEBUG_REPORT_OBJECT_TYPE_UNKNOWN_EXT
			2.object 不能为VK_NULL_HANDLE
			3.object必须为一个objectType指明的类型的vulkan对象的vulkan句柄
			*/


			//给一个对象提供一个用户定义的名字
			vkDebugMarkerSetObjectNameEXT(device, &debugMarkerObjectNameInfoEXT);


			VkDebugMarkerObjectTagInfoEXT debugMarkerObjectTagInfoEXT{};
			debugMarkerObjectTagInfoEXT.sType = VK_STRUCTURE_TYPE_DEBUG_MARKER_OBJECT_TAG_INFO_EXT;
			debugMarkerObjectTagInfoEXT.pNext = nullptr;
			debugMarkerObjectTagInfoEXT.objectType = VK_DEBUG_REPORT_OBJECT_TYPE_IMAGE_EXT;// VkDebugReportObjectTypeEXT值，指明要指定名字的对象的类型,这里类型枚举值的定义以及对应的vulkan对象句柄详细信息见p4204 - p4207
			debugMarkerObjectTagInfoEXT.object = (uint64_t)VkImage{/*假设这是一个有效的VkImage*/ };//为该对象的句柄
			debugMarkerObjectTagInfoEXT.tagName = 0;//为tag的数字标识符
			debugMarkerObjectTagInfoEXT.tagSize = 3;//为附加到vulkan对象上的数据的字节数大小
			debugMarkerObjectTagInfoEXT.pTag = "tag";//为附加到vulkan对象上的数据
			/*
			VkDebugMarkerObjectTagInfoEXT有效用法:
			1.objectType 不能为VK_DEBUG_REPORT_OBJECT_TYPE_UNKNOWN_EXT
			2.object不能为VK_NULL_HANDLE
			3.object必须为一个有效的objectType指明的类型的vulkan对象的vulkan句柄
			*/

			//给一个对象附加额外的数据
			vkDebugMarkerSetObjectTagEXT(device, &debugMarkerObjectTagInfoEXT);

		}


		//Command Buffer Markers   描述如何关联VkCommandBuffer中的场景中的逻辑元素， 参见p4197
		{
			VkCommandBuffer commandBuffer{/*假设这是一个有效的VkCommandBuffer*/ };

			//marker region可以用来标记command buffer中的一组命令的区域

			VkDebugMarkerMarkerInfoEXT debugMarkerMarkerInfoEXT{};
			debugMarkerMarkerInfoEXT.sType = VK_STRUCTURE_TYPE_DEBUG_MARKER_MARKER_INFO_EXT;
			debugMarkerMarkerInfoEXT.pNext = nullptr;
			debugMarkerMarkerInfoEXT.pMarkerName = "my_marker";//null-terminated UTF-8 string，指明marker的名字
			debugMarkerMarkerInfoEXT.color/*float[4]*/;//一个可选的关联到marker的RGBA颜色值，每个元素范围为0-1

			//定义一个marker region的开始
			vkCmdDebugMarkerBeginEXT(commandBuffer, &debugMarkerMarkerInfoEXT);

			//关闭一个marker region
			vkCmdDebugMarkerEndEXT(commandBuffer);//commandBuffer记录之前必须有一个配对的vkCmdDebugMarkerBeginEXT

			//往command buffer中插入一个marker
			vkCmdDebugMarkerInsertEXT(commandBuffer, &debugMarkerMarkerInfoEXT);

		}

	}


	//Debug Report Callbacks  参见p4201
	{
		//debug report callbacks能够在感兴趣的事件发生时给出更多的反馈信息

		VkDebugReportCallbackEXT debugReportCallbackEXT{};

		
		VkDebugReportCallbackCreateInfoEXT debugReportCallbackCreateInfoEXT{};
		debugReportCallbackCreateInfoEXT.sType = VK_STRUCTURE_TYPE_DEBUG_REPORT_CALLBACK_CREATE_INFO_EXT;
		debugReportCallbackCreateInfoEXT.pNext = nullptr;
		debugReportCallbackCreateInfoEXT.flags = VK_DEBUG_REPORT_ERROR_BIT_EXT;/* VkDebugReportFlagBitsEXT 组合值位掩码，指明哪个事件发生会触发回调
		VkDebugReportFlagBitsEXT:
		VK_DEBUG_REPORT_ERROR_BIT_EXT : 指明应用违反了specification中规定的合法使用条件
		VK_DEBUG_REPORT_WARNING_BIT_EXT : 指明vulkan的使用可能会暴露一个应用bug，这些情况可能不会立即损害程序执行，只是一个警告。
		VK_DEBUG_REPORT_PERFORMANCE_WARNING_BIT_EXT : 指明一个潜在的vulkan的非最优用法，比如当VkAttachmentDescription::loadOp设置为VK_ATTACHMENT_LOAD_OP_CLEAR时调用vkCmdClearColorImage
		VK_DEBUG_REPORT_INFORMATION_BIT_EXT : 指明表示信息的消息比如当调试应用时可能处理的资源细节
		VK_DEBUG_REPORT_DEBUG_BIT_EXT : 指明来自实现以及layers的诊断信息
		*/
		debugReportCallbackCreateInfoEXT.pfnCallback = &ReportCallBack;//指明回调函数
		debugReportCallbackCreateInfoEXT.pUserData = "my_userdata";//一个用户定义的传递给回调函数的对应参数的数据
		
		//注册一个debug report callback
		vkCreateDebugReportCallbackEXT(instance, &debugReportCallbackCreateInfoEXT, nullptr, &debugReportCallbackEXT);


		//往debug stream中注入消息
		vkDebugReportMessageEXT(instance, VK_DEBUG_REPORT_ERROR_BIT_EXT/*flags*/, VK_DEBUG_REPORT_OBJECT_TYPE_BUFFER_EXT/*objectType*/, (uint64_t)VkBuffer {/*假设这是一个有效的VkBuffer*/ }/*object*/,
			0/*location*/, 0/*messageCode*/, "my_layer"/*pLayerPrefix*/, "test_message"/*pMessage*/);//参数含义可对照ReportCallBack回调函数
		/*
		vkDebugReportMessageEXT有效用法:
		1.object 必须为vulkan 对象句柄或者VK_NULL_HANDLE
		2.如果objectType 不为VK_DEBUG_REPORT_OBJECT_TYPE_UNKNOWN_EXT 且object不为VK_NULL_HANDLE，则object必须是objectType对应的有效的vulkan对象的vulkan句柄

		*/

		
		//销毁debug report callbacks
		vkDestroyDebugReportCallbackEXT(instance, debugReportCallbackEXT, nullptr);
		/*
		vkDestroyDebugReportCallbackEXT有效用法:
		1.如果创建callback时提供了一个 VkAllocationCallbacks，则这里必须提供一个兼容的
		2.如果创建callback时没有提供VkAllocationCallbacks，则pAllocator 必须为NULL
		
		*/

	}


	//Device Loss Debugging 参见p4209
	{
		//Device Diagnostic Checkpoints  参见p4209
		{
			//device的程序执行可以通过以用户定义的device诊断检查点注释指定的命令流来追踪来调试device loss

			VkCommandBuffer commandBuffer{};//假设这是一个有效的VkCommandBuffer

			//在命令流中插入device diagnostic checkpoints
			uint32_t checkPoint = 0;
			vkCmdSetCheckpointNV(commandBuffer, &checkPoint);

			//当在device执行遇到device loss错误时，实现会在host执行的一些点返回VK_ERROR_DEVICE_LOST，获取错误发生时最近的 diagnostic checkpoints的信息
			uint32_t checkPointDataCount2 = 0;
			std::vector<VkCheckpointData2NV> checkpointData2NVs{};
			vkGetQueueCheckpointData2NV(VkQueue{/*假设这是一个有效的VkQueue*/ }/*queue*/, & checkPointDataCount2, nullptr);//queue必须处于lost状态
			checkpointData2NVs.resize(checkPointDataCount2);
			vkGetQueueCheckpointData2NV(VkQueue{/*假设这是一个有效的VkQueue*/ }, & checkPointDataCount2, checkpointData2NVs.data());//假设正确返回了数据
			VkCheckpointData2NV &checkpointData2NV = checkpointData2NVs[0];
			checkpointData2NV.sType = VK_STRUCTURE_TYPE_CHECKPOINT_DATA_2_NV;
			checkpointData2NV.pNext = nullptr;
			checkpointData2NV.stage = VK_PIPELINE_STAGE_2_RESOLVE_BIT;//指明一个checkpoint marker 数据引用到的一个pipeline stage
			uint32_t markerData2 = 0;
			checkpointData2NV.pCheckpointMarker = &markerData2;//包含在stage上执行的最后一个checkpoint marker的值


			//当在device执行遇到device loss错误时，实现会在host执行的一些点返回VK_ERROR_DEVICE_LOST，获取错误发生时最近的 diagnostic checkpoints的信息
			uint32_t checkPointDataCount = 0;
			std::vector<VkCheckpointDataNV> checkpointDataNVs{};
			vkGetQueueCheckpointDataNV(VkQueue{/*假设这是一个有效的VkQueue*/ }/*queue*/, & checkPointDataCount, nullptr);//queue必须处于lost状态
			checkpointDataNVs.resize(checkPointDataCount);
			vkGetQueueCheckpointDataNV(VkQueue{/*假设这是一个有效的VkQueue*/ }, & checkPointDataCount, checkpointDataNVs.data());//假设正确返回了数据
			VkCheckpointDataNV& checkpointDataNV = checkpointDataNVs[0];
			checkpointDataNV.sType = VK_STRUCTURE_TYPE_CHECKPOINT_DATA_NV;
			checkpointDataNV.pNext = nullptr;
			checkpointDataNV.stage = VK_PIPELINE_STAGE_COMPUTE_SHADER_BIT;//指明一个checkpoint marker 数据引用到的一个pipeline stage
			uint32_t markerData = 0;
			checkpointDataNV.pCheckpointMarker = &markerData;//包含在stage上执行的最后一个checkpoint marker的值


		}


		//Device Fault Diagnosis  参见p4214
		{
			//获取可能造成device loss的错误的诊断信息
			VkDeviceFaultCountsEXT deviceFaultCountsEXT{};
			deviceFaultCountsEXT.sType = VK_STRUCTURE_TYPE_DEVICE_FAULT_COUNTS_EXT;
			deviceFaultCountsEXT.pNext = nullptr;
			deviceFaultCountsEXT.addressInfoCount = 0;// VkDeviceFaultAddressInfoEXT的数量，描述可能造成页故障的内存访问或者是该故障发生是的active指令的地址
			deviceFaultCountsEXT.vendorInfoCount = 0;// VkDeviceFaultVendorInfoEXT的数量，描述vendor-specific 故障信息
			deviceFaultCountsEXT.vendorBinarySize = 0;//为 vendor-specific二进制崩溃转储信息的字节数大小，可能在导入到外部工具时提供额外信息

			VkDeviceFaultInfoEXT deviceFaultInfoEXT{};
			deviceFaultInfoEXT.sType = VK_STRUCTURE_TYPE_DEVICE_FAULT_INFO_EXT;
			deviceFaultInfoEXT.pNext = nullptr;
			deviceFaultInfoEXT.description/*char[VK_MAX_DESCRIPTION_SIZE]*/;//null-terminated UTF-8 string，指明用户可读的故障描述
			deviceFaultInfoEXT.pAddressInfos = nullptr;//为NULL，或者 VkDeviceFaultAddressInfoEXT数组指针，描述可能造成页故障的内存访问或者是该故障发生是的active指令的地址，如果不为NULL，每个元素描述一个 GPU virtual address空间的绑定区域，该区域包含访问的GPU virtual address或者active指令的指针
			deviceFaultInfoEXT.pVendorInfos = nullptr;//为NULL，或者 VkDeviceFaultVendorInfoEXT数组指针，描述vendor-specific 故障信息
			deviceFaultInfoEXT.pVendorBinaryData = nullptr;//为NULL，或者vendorBinarySize个字节的数据的指针，描述vendor-specific二进制崩溃转储信息，其他见p4220 Vendor Binary Crash Dumps


			std::vector<VkDeviceFaultAddressInfoEXT> deviceFaultAddressInfoEXTs{};
			std::vector<VkDeviceFaultVendorInfoEXT> deviceFaultVendorInfoEXTs{};
			std::vector<char> vendorBinaryData{};

			vkGetDeviceFaultInfoEXT(device, &deviceFaultCountsEXT, &deviceFaultInfoEXT);
			/*
			vkGetDeviceFaultInfoEXT有效用法:
			1.device 必须为lost state
			2.如果pFaultCounts->addressInfoCount的值不为0，且pFaultInfo->pAddressInfos不为NULL，则pFaultInfo->pAddressInfos 必须一个有pFaultCounts->addressInfoCount个VkDeviceFaultAddressInfoEXT元素的数组指针
			3.如果pFaultCounts->vendorInfoCount的值不为0，且pFaultInfo->pVendorInfos不为NULL，则pFaultInfo->pVendorInfos 必须一个有pFaultCounts->vendorInfoCount个VkDeviceFaultVendorInfoEXT元素的数组指针
			4.如果pFaultCounts->vendorBinarySize的值不为0，且pFaultInfo->pVendorBinaryData不为NULL，则pFaultInfo->pVendorBinaryData 必须一个有pFaultCounts->vendorBinarySize个字节元素的数组指针
			*/

			deviceFaultAddressInfoEXTs.resize(deviceFaultCountsEXT.addressInfoCount);
			deviceFaultVendorInfoEXTs.resize(deviceFaultCountsEXT.vendorInfoCount);
			vendorBinaryData.resize(deviceFaultCountsEXT.vendorBinarySize);
			deviceFaultInfoEXT.pAddressInfos = deviceFaultAddressInfoEXTs.data();
			deviceFaultInfoEXT.pVendorInfos = deviceFaultVendorInfoEXTs.data();
			deviceFaultInfoEXT.pVendorBinaryData = vendorBinaryData.data();

			vkGetDeviceFaultInfoEXT(device, &deviceFaultCountsEXT, &deviceFaultInfoEXT);//假设正确返回了数据
			VkDeviceFaultAddressInfoEXT &deviceFaultAddressInfoEXT = deviceFaultAddressInfoEXTs[0];
			deviceFaultAddressInfoEXT.addressType = VK_DEVICE_FAULT_ADDRESS_TYPE_WRITE_INVALID_EXT;/*VkDeviceFaultAddressTypeEXT值，为造成页故障的内存访问的操作类型或者active指令和错误之间的联系类型
			VkDeviceFaultAddressTypeEXT:
			VK_DEVICE_FAULT_ADDRESS_TYPE_NONE_EXT : 指明VkDeviceFaultAddressInfoEXT不描述一个页故障或者一个指令地址
			VK_DEVICE_FAULT_ADDRESS_TYPE_READ_INVALID_EXT : 指明VkDeviceFaultAddressInfoEXT描述一个被非法读操作触发的页故障
			VK_DEVICE_FAULT_ADDRESS_TYPE_WRITE_INVALID_EXT : 指明VkDeviceFaultAddressInfoEXT描述一个被非法写操作触发的页故障
			VK_DEVICE_FAULT_ADDRESS_TYPE_EXECUTE_INVALID_EXT : 描述一个有尝试执行non-executable memory触发的页故障
			VK_DEVICE_FAULT_ADDRESS_TYPE_INSTRUCTION_POINTER_UNKNOWN_EXT : 在故障发生时指定一个指令指针，指明该指令可能和故障有关
			VK_DEVICE_FAULT_ADDRESS_TYPE_INSTRUCTION_POINTER_INVALID_EXT : 指定一个有非法指令错误的指令指针
			VK_DEVICE_FAULT_ADDRESS_TYPE_INSTRUCTION_POINTER_FAULT_EXT : 指定一个和故障有关的指令指针
			
			*/
			deviceFaultAddressInfoEXT.reportedAddress = 0;//为device记录的GPU virtual address
			deviceFaultAddressInfoEXT.addressPrecision = 0;//为2的指数，指明device可以记录的地址的精度，和reportedAddress可以共同决定一个有效的地址范围


			VkDeviceFaultVendorInfoEXT& deviceFaultVendorInfoEXT = deviceFaultVendorInfoEXTs[0];
			deviceFaultVendorInfoEXT.description[VK_MAX_DESCRIPTION_SIZE];//包含null-terminated UTF-8 string，描述用户可读的故障信息
			deviceFaultVendorInfoEXT.vendorFaultCode;//为该故障的vendor-specific 故障码
			deviceFaultVendorInfoEXT.vendorFaultData;//为关联到该故障的vendor-specific 故障数据

			//vendor-specific binary crash dump数据的格式对各个vendor可能不尽相同，所以为了区分并正确处理这些数据，写入到VkDeviceFaultInfoEXT::pVendorBinaryData的最开始的字节必须包含一个头信息，格式为
			VkDeviceFaultVendorBinaryHeaderVersionOneEXT deviceFaultVendorBinaryHeaderVersionOneEXT{};
			deviceFaultVendorBinaryHeaderVersionOneEXT.headerSize = sizeof(VkDeviceFaultVendorBinaryHeaderVersionOneEXT);//为crash dump header的字节数大小
			deviceFaultVendorBinaryHeaderVersionOneEXT.headerVersion = VK_DEVICE_FAULT_VENDOR_BINARY_HEADER_VERSION_ONE_EXT;//一个 VkDeviceFaultVendorBinaryHeaderVersionEXT 值，指定header版本
			deviceFaultVendorBinaryHeaderVersionOneEXT.vendorID = 0;//为实现的VkPhysicalDeviceProperties::vendorID
			deviceFaultVendorBinaryHeaderVersionOneEXT.deviceID = 0;//为实现的VkPhysicalDeviceProperties::deviceID
			deviceFaultVendorBinaryHeaderVersionOneEXT.driverVersion = 0;//为实现的VkPhysicalDeviceProperties::driverVersion
			deviceFaultVendorBinaryHeaderVersionOneEXT.pipelineCacheUUID[VK_UUID_SIZE];//包含匹配VkPhysicalDeviceProperties::pipelineCacheUUID属性的值
			deviceFaultVendorBinaryHeaderVersionOneEXT.applicationNameOffset = 0;//为0，或者为从crash dump header的基地址开始到包含应用的名字的null-terminated UTF-8 string结束的偏移量，如果不为0，则必须匹配创建instance时指定的VkApplicationInfo::pApplicationName
			deviceFaultVendorBinaryHeaderVersionOneEXT.applicationVersion = 0;//必须为0或者创建instance时指定的VkApplicationInfo::applicationVersion
			deviceFaultVendorBinaryHeaderVersionOneEXT.engineNameOffset = 0;//为0，或者为从crash dump header的基地址开始到包含用于创建应用的engine的名字的null-terminated UTF-8 string结束的偏移量，如果不为0，则必须匹配创建instance时指定的 VkApplicationInfo::pEngineName
			deviceFaultVendorBinaryHeaderVersionOneEXT.engineVersion = 0;//必须为0或者创建instance时指定的VkApplicationInfo::engineVersion
			deviceFaultVendorBinaryHeaderVersionOneEXT.apiVersion = 0;//必须为0或者创建instance时指定的VkApplicationInfo::apiVersion


		}


	}


}


NS_TEST_END