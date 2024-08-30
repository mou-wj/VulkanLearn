#include "SparseResourcesAndWindowSystemIntergrationTest.h"
#include "vulkan/vulkan_android.h"
//wayland
struct wl_display {};//未定义这里自己定义
struct wl_surface {};//未定义这里自己定义
#include "vulkan/vulkan_wayland.h"
#include <Windows.h>
#include "vulkan/vulkan_win32.h"
//xcb
typedef uint32_t xcb_connection_t;//未定义这里自己定义
typedef uint32_t xcb_window_t;//未定义这里自己定义
#include "vulkan/vulkan_xcb.h"
//xlib
typedef uint32_t Display;//未定义这里自己定义
typedef uint32_t Window;//未定义这里自己定义
#include "vulkan/vulkan_xlib.h"
//direct fb
typedef uint32_t  IDirectFB;//未定义这里自己定义
typedef uint32_t  IDirectFBSurface;//未定义这里自己定义
#include "vulkan/vulkan_directfb.h"
//fuchsia
typedef uint32_t zx_handle_t;//未定义这里自己定义
#include "vulkan/vulkan_fuchsia.h"
//google game platform
typedef uint32_t GgpStreamDescriptor;//未定义这里自己定义
typedef uint32_t GgpFrameToken;//未定义这里自己定义
#include "vulkan/vulkan_ggp.h"

#include "vulkan/vulkan_ios.h"

#include "vulkan/vulkan_macos.h"

#include "vulkan/vulkan_vi.h"

#include "vulkan/vulkan_metal.h"
//screen qnx
struct _screen_context {};//未定义这里自己定义
struct _screen_window {};//未定义这里自己定义
#include "vulkan/vulkan_screen.h"

typedef uint32_t RROutput;
#include "vulkan/vulkan_xlib_xrandr.h"

NS_TEST_BEGIN
SparseResourcesAndWindowSystemIntergrationTest::SparseResourcesAndWindowSystemIntergrationTest()
{
}

void SparseResourcesAndWindowSystemIntergrationTest::run()
{
}

SparseResourcesAndWindowSystemIntergrationTest::~SparseResourcesAndWindowSystemIntergrationTest()
{
}

void SparseResourcesAndWindowSystemIntergrationTest::SparseResourcesTest()
{
	/*
	通常情况下，non-sparse的VkBuffer或者VkImage资源需要绑定到完整的连续的单独的内存上，凡是如果是sparse的，那么就可以有更松的内存限制; 资源可以绑定到多个内存上，资源可以重新绑定，可以具有生成并与内存绑定命令正交使用的描述符。
	
	*/

	//Sparse Resource Features  参见p2981
	{
		/*
		Sparse resources必须要开启几个特性，可以在创建资源的VkImageCreateInfo或者VkBufferCreateInfo标志中设置，这几个特性又和设备的一个或多个特性（VkPhysicalDeviceFeatures.）相关联。
		这几个特性包括： sparseBinding，基于sparseBinding的sparseResidency 相关特性， sparseResidencyAliased特性，这些特性的功能见p2981-p2982
		
		
		*/
	}


	//Sparse Buffers and Fully-Resident Images  参见p2983
	{
		/*
		以VK_IMAGE_CREATE_SPARSE_BINDING_BIT 或者 VK_BUFFER_CREATE_SPARSE_BINDING_BIT创建的VkImage或者VkBuffer,
		
		如果VkImage不以VK_IMAGE_CREATE_SPARSE_RESIDENCY_BIT创建，则其整个内存对应用是不可见的，

		如果同时使用了 VK_IMAGE_CREATE_SPARSE_RESIDENCY_BIT 或者 VK_BUFFER_CREATE_SPARSE_RESIDENCY_BIT，则必须在使用前将资源绑定到一个或多个内存对象
		
		*/

		//Sparse Buffer and Fully - Resident Image Block Size    和VkMemoryRequirements::alignment. alignment相关   见p2983
	}

	// Sparse Partially-Resident Buffers  以VK_BUFFER_CREATE_SPARSE_BINDING_BIT 和VK_BUFFER_CREATE_SPARSE_RESIDENCY_BIT 创建的VkBuffer,     参见p2983

	//Sparse Partially - Resident Images  参见p2983
	{
		//以VK_IMAGE_CREATE_SPARSE_BINDING_BIT 和VK_IMAGE_CREATE_SPARSE_RESIDENCY_BIT 创建的VkImage

		// Accessing Unbound Regions  参见p2983
		{
			/*
			访问未绑定的内存的行为可根据VkPhysicalDeviceSparseProperties.residencyNonResidentStrict 属性来定，具体参见p2984
			
			*/
		}

		//Mip Tail Regions  参见p2984
		{
			/*
			基于以VK_IMAGE_CREATE_SPARSE_BINDING_BIT 和VK_IMAGE_CREATE_SPARSE_RESIDENCY_BIT 创建的VkImage，

			在每个layer中节大小小于sparse block size的所有字mipmap level的区域会被组织到一起，称为mip tail region，
			
			如果对image的format的VkSparseImageFormatProperties的flags中如果包含VK_SPARSE_IMAGE_FORMAT_ALIGNED_MIP_SIZE_BIT，则layer中任何其维度不是sparse image block（VkPhysicalDeviceSparseProperties.residencyAlignedMipSize）对应维度大小的整数倍的mipmap level以及该mipmap level之后的mipmap level的区域都会被组织到 mip tail region中。

			如果VkSparseImageMemoryRequirements::flags中包含VK_SPARSE_IMAGE_FORMAT_SINGLE_MIPTAIL_BIT，则多个layer的mip tail region会被组织到一起，否则每个layer的mip tail region会单独分配。

			所以mip tail region的根据VK_SPARSE_IMAGE_FORMAT_ALIGNED_MIP_SIZE_BIT以及VK_SPARSE_IMAGE_FORMAT_SINGLE_MIPTAIL_BIT技能得到四种组合，每个组合的mip tail region的内存形式参见 p2985-p2987

			*/


		}

		// Standard Sparse Image Block Shapes  参见p2987
		{
			/*
			Standard sparse image block shapes对sparse image blocks基于image的format,定义了一组标准的维度。texel以及sparse image block中压缩texel的布局是基于实现的，当前定义的standard sparse image block shapes都是64KB大小的
			
			维度表格：
			//————————————————————————————————————————
			Standard Sparse Image Block Shapes (Single Sample)：
			TEXEL SIZE (bits)				Block Shape (2D)			Block Shape (3D)
			8-Bit						 256 × 256 × 1				64 × 32 × 32
			16-Bit						 256 × 128 × 1				32 × 32 × 32
			32-Bit						 128 × 128 × 1				32 × 32 × 16
			64-Bit						 128 × 64 × 1					32 × 16 × 16
			128-Bit						 64 × 64 × 1					16 × 16 × 16


			Standard Sparse Image Block Shapes (MSAA)
			TEXEL SIZE (bits)		Block Shape (2X)		Block Shape (4X)		Block Shape (8X)		Block Shape(16X)
			8-Bit					128 × 256 × 1			128 × 128 × 1			64 × 128 × 1			64 × 64 × 1
			16-Bit					128 × 128 × 1			128 × 64 × 1			64 × 64 × 1			64 × 32 × 1
			32-Bit					64 × 128 × 1			64 × 64 × 1			32 × 64 × 1			32 × 32 × 1
			64-Bit					64 × 64 × 1			64 × 32 × 1			32 × 32 × 1			32 × 16 × 1
			128-Bit					32 × 64 × 1			32 × 32 × 1			16 × 32 × 1			16 × 16 × 1
			//————————————————————————————————————————————————
			具体支持维度表格中列举的Sparse Image Block Shapes可根据VkPhysicalDeviceSparseProperties的residencyStandard2DBlockShape， residencyStandard2DMultisampleBlockShape 或者residencyStandard3DBlockShape 判断，这些特性并不意味这所有image 类型都支持sparse image,只是说明这些类型支持的sparse image没有Standard Sparse Image Block Shapes的将使用自定义的
			*/
		}


		//Custom Sparse Image Block Shapes  参见p2989
		{
			/*
			没有支持Standard Sparse Image Block Shapes的则可以使用自定义的Sparse Image Block Shapes，自定义的Sparse Image Block Shapes由vkGetPhysicalDeviceSparseImageFormatProperties 以及 vkGetImageSparseMemoryRequirements调用返回的VkSparseImageFormatProperties::imageGranularity以及VkMemoryRequirements::alignment决定.
			
			*/
		}

		// Multiple Aspects   参见p2990    Partially resident images允许不同的aspect又各自的sparse properties
	}

	// Sparse Memory Aliasing  参见p2991
	{
		
		/*
		默认情况下，sparse资源遵守non-sparse资源的别名规则，见 Memory Aliasing p1194
		
		如果VkDevice开启了 sparseResidencyAliased特性，则sparse资源可以使用VK_BUFFER_CREATE_SPARSE_ALIASED_BIT 以及 VK_IMAGE_CREATE_SPARSE_ALIASED_BIT 允许以数据一致的方式访问绑定到一个或多个sparse资源中的多个位置的物理内存
		
		访问该内存需要有memory dependencies，且需要遵守一些限制，见p2991
		*/


	}

	// Sparse Resource Implementation Guidelines (Informative)  参见p2992
	{
		/*
		sparseBinding 特性允许在resource创建的时候保存其设备虚拟地址范围，除此之外和non-sparse资源一样

		sparseResidency 特性允许不绑定内存就可以访问资源，residencyNonResidentStrict可以规定访问未绑定的内存的行为


		
		*/
	}


	//Sparse Resource API  参见p2994
	{

		/*
		Physical Device Features 参见p2994

		列举在 VkPhysicalDeviceFeatures中，为:
		> sparseBinding
		> sparseResidencyBuffer
		> sparseResidencyImage2D
		> sparseResidencyImage3D 
		> sparseResidency2Samples
		> sparseResidency4Samples
		> sparseResidency8Samples
		> sparseResidency16Samples
		> sparseResidencyAliased
		*/


		//Physical Device Sparse Properties   参见p2995
		{
			/*
			实现的有些特性是无法关闭的且根据这些特性可以允许应用改变sparse资源的用法，其列举在 VkPhysicalDeviceProperties::sparseProperties中，为一个VkPhysicalDeviceSparseProperties
			*/

			VkPhysicalDeviceSparseProperties physicalDeviceSparseProperties = VkPhysicalDeviceProperties{}.sparseProperties;
			physicalDeviceSparseProperties.residencyStandard2DBlockShape = VK_TRUE;//如果为VK_TRUE,则指明物理设备将使用standard sparse image block shapes访问所有的single-sample 2D sparse resources。如果不支持，则返回的VkSparseImageFormatProperties.imageGranularity就不必要和其 standard sparse image block dimensions匹配
			physicalDeviceSparseProperties.residencyStandard2DMultisampleBlockShape = VK_TRUE;//如果为VK_TRUE,则指明物理设备将使用standard sparse image block shapes访问所有的multisample 2D sparse resources。如果不支持，则返回的VkSparseImageFormatProperties.imageGranularity就不必要和其 standard sparse image block dimensions匹配
			physicalDeviceSparseProperties.residencyStandard3DBlockShape = VK_TRUE;//如果为VK_TRUE,则指明物理设备将使用standard sparse image block shapes访问所有的3D sparse resources。如果不支持，则返回的VkSparseImageFormatProperties.imageGranularity就不必要和其 standard sparse image block dimensions匹配
			physicalDeviceSparseProperties.residencyAlignedMipSize = VK_TRUE;//如果为VK_TRUE，则含有mipmap level的image的维度不为对应 sparse image block 维度的整数倍的level或许会放到mip tail中，如果不支持，则只有维度小于VkSparseImageFormatProperties.imageGranularity的level会放到mip tail中，如果支持，则应用允许返回的VkSparseImageFormatProperties.flags中包含VK_SPARSE_IMAGE_FORMAT_ALIGNED_MIP_SIZE_BIT，指明mipmap level的image的维度不为对应 sparse image block 维度的整数倍的level会放到mip tail中
			physicalDeviceSparseProperties.residencyNonResidentStrict = VK_TRUE;//指明物理设备是否可以一直访问资源的non-resident区域，如果为VK_TRUE，则访问该区域返回的值为0，写入该区域的值会被丢弃

		}


		//Sparse Image Format Properties 参见p2996
		{
			//在创建sparse资源前查询 sparse image format properties
			uint32_t sparseImageFormatPropertiesCount = 0;
			std::vector<VkSparseImageFormatProperties> sparseImageFormatProperties{};
			vkGetPhysicalDeviceSparseImageFormatProperties(physicalDevice, VK_FORMAT_R8G8B8_SRGB, VK_IMAGE_TYPE_2D, VK_SAMPLE_COUNT_1_BIT/*samples，必须是参入相同format, type, tiling, 以及 usage参数调用vkGetPhysicalDeviceImageFormatProperties返回的VkImageFormatProperties::sampleCounts中的有效值*/, VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT, VK_IMAGE_TILING_LINEAR,
				&sparseImageFormatPropertiesCount,nullptr);
			sparseImageFormatProperties.resize(sparseImageFormatPropertiesCount);
			vkGetPhysicalDeviceSparseImageFormatProperties(physicalDevice, VK_FORMAT_R8G8B8_SRGB, VK_IMAGE_TYPE_2D, VK_SAMPLE_COUNT_1_BIT, VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT, VK_IMAGE_TILING_LINEAR,
				&sparseImageFormatPropertiesCount, sparseImageFormatProperties.data());//假设返回成功了至少一个property
			VkSparseImageFormatProperties& sparseImageFormatPropertie = sparseImageFormatProperties[0];
			sparseImageFormatPropertie.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;//为 VkImageAspectFlagBits组合值位掩码，指明该property应用的aspect
			sparseImageFormatPropertie.flags = VK_SPARSE_IMAGE_FORMAT_ALIGNED_MIP_SIZE_BIT;/*VkSparseImageFormatFlagBits组合值位掩码指明sparse resource额外的属性
			VkSparseImageFormatFlagBits:
			VK_SPARSE_IMAGE_FORMAT_SINGLE_MIPTAIL_BIT: 指定image的所有array layers只有一个mip tail region，不是每个layer都有一个
			VK_SPARSE_IMAGE_FORMAT_ALIGNED_MIP_SIZE_BIT:  指定会被放到mipmap tail region维度不为对应sparse image block的维度整数倍的第一个mipmap level
			VK_SPARSE_IMAGE_FORMAT_NONSTANDARD_BLOCK_SIZE_BIT:  指定image不使用standard sparse image block dimensions，且imageGranularity不匹配对应format的standard sparse image block dimensions

			
			*/
			sparseImageFormatPropertie.imageGranularity = VkExtent3D{ .width = 1,.height = 1,.depth = 1 };//为sparse image block基于texel或者compressed texel blocks的 width, height, 以及 depth维度值


			//在创建sparse资源前查询 sparse image format properties 2   vkGetPhysicalDeviceSparseImageFormatProperties2等同于vkGetPhysicalDeviceSparseImageFormatProperties2KHR
			VkPhysicalDeviceSparseImageFormatInfo2 physicalDeviceSparseImageFormatInfo2{};
			physicalDeviceSparseImageFormatInfo2.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SPARSE_IMAGE_FORMAT_INFO_2;
			physicalDeviceSparseImageFormatInfo2.pNext = nullptr;
			physicalDeviceSparseImageFormatInfo2.format = VK_FORMAT_R8G8B8_SRGB;//image format
			physicalDeviceSparseImageFormatInfo2.samples = VK_SAMPLE_COUNT_1_BIT;//image samples,必须是参入相同format, type, tiling, 以及 usage参数调用vkGetPhysicalDeviceImageFormatProperties返回的VkImageFormatProperties::sampleCounts中的有效值
			physicalDeviceSparseImageFormatInfo2.tiling = VK_IMAGE_TILING_LINEAR;//image tiling
			physicalDeviceSparseImageFormatInfo2.type = VK_IMAGE_TYPE_2D;//image type
			physicalDeviceSparseImageFormatInfo2.usage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;//image usage
			
			uint32_t sparseImageFormatPropertiesCount2 = 0;
			std::vector<VkSparseImageFormatProperties2> sparseImageFormatProperties2s{};
			vkGetPhysicalDeviceSparseImageFormatProperties2(physicalDevice, &physicalDeviceSparseImageFormatInfo2, &sparseImageFormatPropertiesCount2, nullptr);
			sparseImageFormatProperties2s.resize(sparseImageFormatPropertiesCount2);
			vkGetPhysicalDeviceSparseImageFormatProperties2(physicalDevice, &physicalDeviceSparseImageFormatInfo2, &sparseImageFormatPropertiesCount2, sparseImageFormatProperties2s.data());//假设返回成功了一个
			VkSparseImageFormatProperties2& sparseImageFormatProperties2 = sparseImageFormatProperties2s[0];
			sparseImageFormatProperties2.sType = VK_STRUCTURE_TYPE_SPARSE_IMAGE_FORMAT_PROPERTIES_2;
			sparseImageFormatProperties2.pNext = nullptr;
			sparseImageFormatProperties2.properties = VkSparseImageFormatProperties{/*假设这是返回的有效VkSparseImageFormatProperties*/};//前面有说明，这里不再复述
		}


		//Sparse Resource Creation  参见p3002
		{
			/*
			Sparse resources需要在创建Device的是否开启相关sparse feature。
			
			以 *_SPARSE_BINDING_BIT创建的资源就可以使用sparse binding command (vkQueueBindSparse).
			*/
		}

		// Sparse Resource Memory Requirements 参见p3002
		{
			/*
			Sparse resources对绑定的内存有特定的需求
			*/

			/*
			Buffer and Fully-Resident Images

			buffer（fully 以及 partially resident）以及 fully-resident images可以绑定到满足 VkMemoryRequirements.中参数的内存上 ，VkMemoryRequirements::alignment 指明字节对齐
			*/


			/*
			Partially Resident Images 

			和Buffer and Fully-Resident Images有所不同，Partially Resident Images 需要满足调用vkGetImageSparseMemoryRequirements返回的VkSparseImageMemoryRequirements定义的参数
			*/


			//Sparse Image Memory Requirements
			{
				//查询Sparse Image Memory Requirements
				uint32_t sparseImageMemoryRequirementsCount = 0;
				std::vector<VkSparseImageMemoryRequirements> sparseImageMemoryRequirements{};
				vkGetImageSparseMemoryRequirements(device, VkImage{/*假设这是一个有效的VkImage*/ }, & sparseImageMemoryRequirementsCount, nullptr);
				sparseImageMemoryRequirements.resize(sparseImageMemoryRequirementsCount);
				vkGetImageSparseMemoryRequirements(device, VkImage{/*假设这是一个有效的VkImage*/ }, & sparseImageMemoryRequirementsCount, sparseImageMemoryRequirements.data());//假设成功返回了一个元素
				VkSparseImageMemoryRequirements& sparseImageMemoryRequirement = sparseImageMemoryRequirements[0];
				sparseImageMemoryRequirement.formatProperties = VkSparseImageFormatProperties{/*假设这是返回的有效VkSparseImageFormatProperties*/ };//指明format的属性,前面有说明，这里不再复述
				sparseImageMemoryRequirement.imageMipTailFirstLod = 0;//指明image subresources中第一个包含在mipmap tail中的mipmap level
				sparseImageMemoryRequirement.imageMipTailOffset = 0;//为用于绑定 mip tail region(s).的VkSparseImageOpaqueMemoryBindInfo的opaque memory offset
				sparseImageMemoryRequirement.imageMipTailSize = 0;//为 mip tail region的字节大小，如果 formatProperties.flags包含VK_SPARSE_IMAGE_FORMAT_SINGLE_MIPTAIL_BIT，则为整个mip tail的大小，否则为每个array layer的mip tail的大小，该值保证是sparse block size的整数倍
				sparseImageMemoryRequirement.imageMipTailStride = 1;//为每个array-layer的mip tail之间的内存步长，在formatProperties.flags不包含VK_SPARSE_IMAGE_FORMAT_SINGLE_MIPTAIL_BIT情况下有效
			
			
			
				//查询Sparse Image Memory Requirements2   vkGetImageSparseMemoryRequirements2 等同于 vkGetImageSparseMemoryRequirements2KHR
				uint32_t sparseImageMemoryRequirementsCount2 = 0;
				std::vector<VkSparseImageMemoryRequirements2> sparseImageMemoryRequirements2s{};
				VkImageSparseMemoryRequirementsInfo2 imageSparseMemoryRequirementsInfo2{};
				imageSparseMemoryRequirementsInfo2.sType = VK_STRUCTURE_TYPE_IMAGE_SPARSE_MEMORY_REQUIREMENTS_INFO_2;
				imageSparseMemoryRequirementsInfo2.pNext = nullptr;
				imageSparseMemoryRequirementsInfo2.image = VkImage{/*假设这是一个有效的VkImage*/ };//指明查询的image
				
				vkGetImageSparseMemoryRequirements2(device, &imageSparseMemoryRequirementsInfo2, &sparseImageMemoryRequirementsCount2, nullptr);
				sparseImageMemoryRequirements2s.resize(sparseImageMemoryRequirementsCount2);
				vkGetImageSparseMemoryRequirements2(device, &imageSparseMemoryRequirementsInfo2, &sparseImageMemoryRequirementsCount2, sparseImageMemoryRequirements2s.data());//假设成功返回了一个元素
				VkSparseImageMemoryRequirements2 sparseImageMemoryRequirements2 = sparseImageMemoryRequirements2s[0];
				sparseImageMemoryRequirements2.sType = VK_STRUCTURE_TYPE_SPARSE_IMAGE_MEMORY_REQUIREMENTS_2;
				sparseImageMemoryRequirements2.pNext = nullptr;
				sparseImageMemoryRequirements2.memoryRequirements = VkSparseImageMemoryRequirements{/*假设这是一个有效的VkSparseImageMemoryRequirements*/ };//前面有提及，这里不再复述

				//在不需要创建VkImage情况下查询Sparse Image Memory Requirements     vkGetDeviceImageSparseMemoryRequirements等同于vkGetDeviceImageSparseMemoryRequirementsKHR
				VkDeviceImageMemoryRequirements deviceImageMemoryRequirements{};
				deviceImageMemoryRequirements.sType = VK_STRUCTURE_TYPE_DEVICE_IMAGE_MEMORY_REQUIREMENTS;
				deviceImageMemoryRequirements.pNext = nullptr;
				deviceImageMemoryRequirements.planeAspect = VK_IMAGE_ASPECT_COLOR_BIT;
				VkImageCreateInfo imageCreareInfo{/*假设这是一个有效的VkImageCreateInfo*/ };
				deviceImageMemoryRequirements.pCreateInfo = &imageCreareInfo;
				
				vkGetDeviceImageSparseMemoryRequirements(device, &deviceImageMemoryRequirements, &sparseImageMemoryRequirementsCount2, nullptr);
				sparseImageMemoryRequirements2s.resize(sparseImageMemoryRequirementsCount2);
				vkGetDeviceImageSparseMemoryRequirements(device, &deviceImageMemoryRequirements, &sparseImageMemoryRequirementsCount2, sparseImageMemoryRequirements2s.data());


			}


			

		}

		//Binding Resource Memory
		{
			/*
			Non-sparse 资源通过vkBindImageMemory 或者 vkBindBufferMemory在使用前绑定其内存，且不能更改。

			sparse资源的绑定在包含VK_QUEUE_SPARSE_BINDING_BIT的queue中执行，绑定需要进行外部同步。
			
			如果绑定到 VK_IMAGE_ASPECT_METADATA_BIT，则 VkSparseMemoryBind::flags中必须包含VK_SPARSE_MEMORY_BIND_METADATA_BIT

			如果绑定到 mip tail,则VkSparseMemoryBind::flags中必须包含VK_SPARSE_MEMORY_BIND_METADATA_BIT，如果绑定到任何aspect的mip tail则使用VkSparseImageOpaqueMemoryBindInfo，
			如果formatProperties.flags包含VK_SPARSE_IMAGE_FORMAT_SINGLE_MIPTAIL_BIT，则只用一个VkSparseMemoryBind即可，其中resourceOffset = imageMipTailOffset，size = imageMipTailSize.
			如果formatProperties.flags不包含VK_SPARSE_IMAGE_FORMAT_SINGLE_MIPTAIL_BIT，则每个array layer要有一个VkSparseMemoryBind，其中 resourceOffset = arrayMipTailOffset = imageMipTailOffset + arrayLayer * imageMipTailStride， size = imageMipTailSize.
			*/

			//Sparse Memory Binding Functions

			/*
			VkSparseMemoryBind结构体，绑定资源的[resourceOffset, resourceOffset + size)范围

			如果flags 包含VK_SPARSE_MEMORY_BIND_METADATA_BIT，则resourceOffset =  imageMipTailOffset + imageMipTailStride × n，其中imageMipTailOffset, imageMipTailSize, 以及 imageMipTailStride为前面提及的对应该meta aspect的VkSparseImageMemoryRequirements中列举的，
			如果VkSparseImageMemoryRequirements::formatProperties.flags包含VK_SPARSE_IMAGE_FORMAT_SINGLE_MIPTAIL_BIT，则imageMipTailStride认为是0

			如果flags 不包含VK_SPARSE_MEMORY_BIND_METADATA_BIT，则绑定资源的范围在 [0,VkMemoryRequirements::size).内
			*/
			VkSparseMemoryBind sparseMemoryBind{};
			sparseMemoryBind.flags = VK_SPARSE_MEMORY_BIND_METADATA_BIT;//VkSparseMemoryBindFlagBits组合值位掩码，指明绑定操作的用法，VK_SPARSE_MEMORY_BIND_METADATA_BIT 指明只用于metadata aspect的内存绑定
			sparseMemoryBind.memory = VkDeviceMemory{/*假设这是一个有效的VkDeviceMemory*/ };//为该资源范围绑定的 VkDeviceMemory对象，如果为VK_NULL_HANDLE，则表示该资源范围为未绑定的
			sparseMemoryBind.memoryOffset = 0;//为该资源范围绑定的 VkDeviceMemory对象中的起始字节偏移量，如果memory为VK_NULL_HANDLE，则该值忽略
			sparseMemoryBind.resourceOffset = 0;//是在该资源中的字节偏移量
			sparseMemoryBind.size = 1;//为要绑定的内存区域大小
			/*
			VkSparseMemoryBind有效用法:
			1.如果memory 不为VK_NULL_HANDLE，则memory以及memoryOffset 必须匹配该资源的内存需求，参见Resource Memory Association p1153
			2.如果资源为VkBuffer,则resourceOffset，memoryOffset以及size必须是调用vkGetBufferMemoryRequirements传入该buffer 资源的参数返回的VkMemoryRequirements.alignment的整数倍
			3.如果资源为VkImage,则resourceOffset，memoryOffset必须是调用vkGetImageMemoryRequirements传入该image 资源的参数返回的VkMemoryRequirements.alignment的整数倍
			4.如果memory 不为VK_NULL_HANDLE，则memory 不能以VK_MEMORY_PROPERTY_LAZILY_ALLOCATED_BIT创建
			5.size 必须大于0，小于等于资源大小减去resourceOffset，小于等于memory大小减去memoryOffset
			6.resourceOffset 必须小于资源的大小
			7.memoryOffset 必须小于等于memory大小
			8.如果memory以VkExportMemoryAllocateInfo::handleTypes不为0创建，则创建资源时VkExternalMemoryBufferCreateInfo::handleTypes 或者 VkExternalMemoryImageCreateInfo::handleTypes至少包含一个handle type
			9.如果memory通过一个memory import operation创建，则创建资源时，导入memory的外部handle type必须设置在 VkExternalMemoryBufferCreateInfo::handleTypes 或者 VkExternalMemoryImageCreateInfo::handleTypes中

			*/


			//绑定以VK_BUFFER_CREATE_SPARSE_BINDING_BIT创建的buffer的内存使用VkSparseBufferMemoryBindInfo
			VkSparseBufferMemoryBindInfo sparseBufferMemoryBindInfo{};
			sparseBufferMemoryBindInfo.buffer = VkBuffer{/*假设这是一个有效的VkBuffer*/ };//指明要绑定的buffer
			sparseBufferMemoryBindInfo.bindCount = 1;// pBinds中元素个数
			sparseBufferMemoryBindInfo.pBinds = &sparseMemoryBind;//一组 VkSparseMemoryBind数组指针，指定其要绑定的范围

			//绑定以VK_IMAGE_CREATE_SPARSE_BINDING_BIT创建的image的opaque regions的内存使用VkSparseImageOpaqueMemoryBindInfo，主要用于绑定fully-resident sparse images，partially resident images的mip tail regions 或者entire binding range
			VkSparseImageOpaqueMemoryBindInfo sparseImageOpaqueMemoryBindInfo{};
			sparseImageOpaqueMemoryBindInfo.image = VkImage{/*假设这是一个有效的VkImage*/ };//指明要绑定的image
			sparseImageOpaqueMemoryBindInfo.bindCount = 1;// pBinds中元素个数
			sparseImageOpaqueMemoryBindInfo.pBinds = &sparseMemoryBind;//一组 VkSparseMemoryBind数组指针，指定其要绑定的范围,如果任何元素得flags包含VK_SPARSE_MEMORY_BIND_METADATA_BIT，则该元素定义的范围必须在该image的metadata aspect 的mip tail region中
		

			//绑定以VK_IMAGE_CREATE_SPARSE_RESIDENCY_BIT创建的image的sparse image blocks的内存使用VkSparseImageMemoryBindInfo，
			VkSparseImageMemoryBindInfo sparseImageMemoryBindInfo{};
			sparseImageMemoryBindInfo.image = VkImage{/*假设这是一个有效的VkImage*/ };//指明要绑定的image
			sparseImageMemoryBindInfo.bindCount = 1;// pBinds中元素个数
			VkSparseImageMemoryBind sparseImageMemoryBind{};
			{
				sparseImageMemoryBind.subresource = VkImageSubresource{ .aspectMask = VK_IMAGE_ASPECT_COLOR_BIT,.mipLevel = 0,.arrayLayer = 0 };//指定image的哪个resource
				sparseImageMemoryBind.flags = 0;//VkSparseMemoryBindFlagBits组合值位掩码，指明绑定操作的用法，VK_SPARSE_MEMORY_BIND_METADATA_BIT 指明只用于metadata aspect的内存绑定
				sparseImageMemoryBind.memory = VkDeviceMemory{/*假设这是一个有效的VkDeviceMemory*/ };//为该sparse image blocks资源范围绑定的 VkDeviceMemory对象，如果为VK_NULL_HANDLE，则表示该资源范围为未绑定的
				sparseImageMemoryBind.memoryOffset = 0;//为该sparse image blocks资源范围绑定的 VkDeviceMemory对象中的起始字节偏移量，如果memory为VK_NULL_HANDLE，则该值忽略
				sparseImageMemoryBind.offset = VkOffset3D{ .x = 0,.y = 0,.z = 0 };//为image subresource绑定的texel区域的第一个texel的坐标
				sparseImageMemoryBind.extent = VkExtent3D{ .width = 1,.height = 1,.depth = 1 };//为image subresource绑定的texel区域的大小，必须是sparse image block dimensions的整数倍，除非绑定的sparse image blocks在 image subresource的边界上时可以允许offset + extent等于 image subresource.的维度
				/*
				VkSparseImageMemoryBind有效用法:
				1.如果sparseResidencyAliased 特性没有开启，且如果任何其他的资源绑定到memory范围，则绑定memory的范围不能重叠
				2.memory以及memoryOffset 必须匹配该image资源的内存需求，参见Resource Memory Association p1153
				3.offset.x 必须是image的对应sparse image block width（(VkSparseImageFormatProperties::imageGranularity.width)）的倍数
				4.extent.width  必须大于0，且必须是image的对应sparse image block width的倍数或者(extent.width + offset.x)  必须等于image subresource的width
				5.offset.y 必须是image的对应sparse image block height（(VkSparseImageFormatProperties::imageGranularity.height)）的倍数
				6.extent.height  必须大于0，且必须是image的对应sparse image block height的倍数或者(extent.height + offset.y)  必须等于image subresource的height
				7.offset.z 必须是image的对应sparse image block depth（(VkSparseImageFormatProperties::imageGranularity.depth)）的倍数
				8.extent.depth  必须大于0，且必须是image的对应sparse image block depth的倍数或者(extent.depth + offset.z)  必须等于image subresource的depth
				9.如果memory以VkExportMemoryAllocateInfo::handleTypes不为0创建，则创建资源时VkExternalMemoryBufferCreateInfo::handleTypes 或者 VkExternalMemoryImageCreateInfo::handleTypes至少包含一个handle type
				10.如果memory通过一个memory import operation创建，则创建资源时，导入memory的外部handle type必须设置在 VkExternalMemoryBufferCreateInfo::handleTypes 或者 VkExternalMemoryImageCreateInfo::handleTypes中
				*/
			
			}
			sparseImageMemoryBindInfo.pBinds = &sparseImageMemoryBind;//一组 VkSparseMemoryBind数组指针，指定其要绑定的范围,如果任何元素得flags包含VK_SPARSE_MEMORY_BIND_METADATA_BIT，则该元素定义的范围必须在该image的metadata aspect 的mip tail region中
			/*
			VkSparseImageMemoryBindInfo有效用法:
			1.pBinds的每个元素的subresource.mipLevel必须小于创建image的VkImageCreateInfo的mipLevels
			2.pBinds的每个元素的subresource.arrayLayer必须小于创建image的VkImageCreateInfo的arrayLayers
			3.pBinds的每个元素的subresource.aspectMask 必须对创建image的VkImageCreateInfo的format是有效的
			4.image 必须以VK_IMAGE_CREATE_SPARSE_RESIDENCY_BIT 创建
			*/


			struct BindSparseInfoEXT {
				VkDeviceGroupBindSparseInfo deviceGroupBindSparseInfo{};
				VkFrameBoundaryEXT frameBoundaryEXT{};
				VkTimelineSemaphoreSubmitInfo timelineSemaphoreSubmitInfo{};
				BindSparseInfoEXT() {
					Init();

				}
				void Init() {

					deviceGroupBindSparseInfo.sType = VK_STRUCTURE_TYPE_DEVICE_GROUP_BIND_SPARSE_INFO;
					deviceGroupBindSparseInfo.pNext = nullptr;
					frameBoundaryEXT.sType = VK_STRUCTURE_TYPE_MAX_ENUM;//因为是自定义的所以定义为非法值
					frameBoundaryEXT.pNext = nullptr;
					timelineSemaphoreSubmitInfo.sType = VK_STRUCTURE_TYPE_TIMELINE_SEMAPHORE_SUBMIT_INFO;
					timelineSemaphoreSubmitInfo.pNext = nullptr;

				}
			};


			//提交一个绑定操作到queue
			VkBindSparseInfo bindSparseInfo{};
			bindSparseInfo.sType = VK_STRUCTURE_TYPE_BIND_SPARSE_INFO;
			BindSparseInfoEXT bindSparseInfoEXT{};
			bindSparseInfo.pNext = &bindSparseInfoEXT.deviceGroupBindSparseInfo;
			bindSparseInfo.waitSemaphoreCount = 1;//为执行这批sparse绑定操作前要等待的semaphore的数量
			VkSemaphore waitSemaphore{/*假设这是一个有效的VkSemaphore*/ };
			bindSparseInfo.pWaitSemaphores = &waitSemaphore;//为一组VkSemaphore 的数组指针指明这批sparse绑定操作前要等外的semaphore，这定义了一个 semaphore wait operation.p358
			bindSparseInfo.bufferBindCount = 1;//为这批要执行的sparse buffer bindings的数量
			bindSparseInfo.pBufferBinds = &sparseBufferMemoryBindInfo;//一组 VkSparseBufferMemoryBindInfo的数组指针，指明sparse buffer binding信息
			bindSparseInfo.imageOpaqueBindCount = 1;//为这批要执行的opaque sparse image bindings的数量
			bindSparseInfo.pImageOpaqueBinds = &sparseImageOpaqueMemoryBindInfo;//一组  VkSparseImageOpaqueMemoryBindInfo的数组指针，指明opaque sparse image bindings信息
			bindSparseInfo.imageBindCount = 1;//为这批要执行的sparse image bindings的数量
			bindSparseInfo.pImageBinds = &sparseImageMemoryBindInfo;//一组 VkSparseImageMemoryBindInfo的数组指针，指明sparse image bindings信息
			bindSparseInfo.signalSemaphoreCount = 1;//为这批sparse绑定操作执行完成后要触发的semaphore的数量
			VkSemaphore signalSemaphore{/*假设这是一个有效的VkSemaphore*/ }; //为一组VkSemaphore 的数组指针指明这批sparse绑定操作完成后要触发的semaphore，这定义了一个  semaphore signal operation.p357
			bindSparseInfo.pSignalSemaphores = &signalSemaphore; 
			/*
			VkBindSparseInfo有效用法:
			1.如果 pWaitSemaphores 或者 pSignalSemaphores的任何元素以VkSemaphoreType为VK_SEMAPHORE_TYPE_TIMELINE创建，则pNext中必须包含一个VkTimelineSemaphoreSubmitInfo
			2.如果pNext中包含一个VkTimelineSemaphoreSubmitInfo且pWaitSemaphores中任何元素以VkSemaphoreType为VK_SEMAPHORE_TYPE_TIMELINE创建，则该结构体的waitSemaphoreValueCount必须等于waitSemaphoreCount
			3.如果pNext中包含一个VkTimelineSemaphoreSubmitInfo且pSignalSemaphores中任何元素以VkSemaphoreType为VK_SEMAPHORE_TYPE_TIMELINE创建，则该结构体的waitSemaphoreValueCount必须等于signalSemaphoreCount
			4.对pSignalSemaphores中每个以VkSemaphoreType为VK_SEMAPHORE_TYPE_TIMELINE创建的semaphore，则其VkTimelineSemaphoreSubmitInfo::pSignalSemaphoreValues中的对应值必须大于该semaphore的semaphore signal operation执行时semaphore的当前值
			5.对pWaitSemaphores中每个以VkSemaphoreType为VK_SEMAPHORE_TYPE_TIMELINE创建的semaphore，则其VkTimelineSemaphoreSubmitInfo::pWaitSemaphoreValues中的对应值必须和该semaphore的当前值相同或者和该semaphore的任何外部wait 或者 signal operation的值的差异不超过maxTimelineSemaphoreValueDifference
			6.对pSignalSemaphores中每个以VkSemaphoreType为VK_SEMAPHORE_TYPE_TIMELINE创建的semaphore，则其VkTimelineSemaphoreSubmitInfo::pSignalSemaphoreValues中的对应值必须和该semaphore的当前值相同或者和该semaphore的任何外部wait 或者 signal operation的值的差异不超过maxTimelineSemaphoreValueDifference
			*/


			//指明绑定哪个实例的资源和内存的设备索引，这些索引会应用到这批绑定信息中的所有buffer以及image binding，semaphore的wait以及signal操作会在resourceDeviceIndex所指的设置上执行，   如果不包含该结构体，则可看成resourceDeviceIndex 以及memoryDeviceIndex 都为0
			VkDeviceGroupBindSparseInfo& deviceGroupBindSparseInfo = bindSparseInfoEXT.deviceGroupBindSparseInfo;
			deviceGroupBindSparseInfo.resourceDeviceIndex = 0;//指明绑定哪个实例的资源的设备索引
			deviceGroupBindSparseInfo.memoryDeviceIndex = 0;//指明资源要绑定哪个实例的内存的设备索引
			/*
			VkDeviceGroupBindSparseInfo有效用法:
			1.resourceDeviceIndex以及memoryDeviceIndex 必须同时是有效的设备索引
			2.这批绑定中每一个memory的分配必须在memoryDeviceIndex指定的设备上分配一个实例
			*/


			vkQueueBindSparse(VkQueue{/*假设这是一个有效的VkQueue*/ }, 1, & bindSparseInfo, VkFence{/*假设这是一个有效的VkFence*/ }/*判断这些绑定是否完成的fence*/);
			/*
			vkQueueBindSparse有效用法:
			1.如果fence不为VK_NULL_HANDLE，则fence不能已经触发，且fence不能关联到任何在其他的queue上还没有完成指明的queue命令
			2.pBindInfo的每个元素的pSignalSemaphores的每个元素必须是未触发的
			3.当pBindInfo的任何元素的pWaitSemaphores的任何元素定义一个引用到一个binary semaphore的执行在queue上的semaphore wait operation，则不能有其他queue等待该相同的semaphore
			4.pBindInfo的所有元素的pWaitSemaphores的所有元素引用到一个以VkSemaphoreType为VK_SEMAPHORE_TYPE_BINARY创建的semaphore，则该semaphore的 signal operation 必须已经提交执行且该semaphore依赖的semaphore的signal operations也必须提交执行
			*/
		}
	}
}

void SparseResourcesAndWindowSystemIntergrationTest::WindowSystemIntegration_WSI_Test()
{
	/*
	vulkan的渲染结果如果要显示则需要通过window system integration (WSI)的各平台的相关显示拓展进行显示
	*/


	//WSI Platform  参见p2022
	{
		/*
		平台是对窗口系统、操作系统等的抽象概念。一些例子包括MS Windows、安卓系统和Wayland系统。Vulkan API可以为每个平台以一种独特的方式进行集成。
		
		Vulkan API不定义任何类型的平台对象。vulkan 定义特定于平台的WSI扩展，每个扩展都包含特定于使用WSI的平台的功能。使用这些拓展根据 Window System-Specific Header Control p5304附录 中定义的预处理符号进行控制，简单将就是要在包含vulkan的相关头文件前定义一些符号来确定使用的平台
		*/


	}

	//WSI Surface  参见p3022
	{
		/*
		原生平台的surface或者window被抽象为surface 对象，即 VkSurfaceKHR 。

		 VK_KHR_surface拓展会声明VkSurfaceKHR，各个平台会提供其创建和相会VkSurfaceKHR对象的函数接口。
		
		*/

		VkSurfaceKHR surface{};

		//Android Platform  参见p3023
		{
			//为 Android native window创建一个 VkSurfaceKHR对象
			VkAndroidSurfaceCreateInfoKHR androidSurfaceCreateInfoKHR{};
			androidSurfaceCreateInfoKHR.sType = VK_STRUCTURE_TYPE_ANDROID_SURFACE_CREATE_INFO_KHR;
			androidSurfaceCreateInfoKHR.pNext = nullptr;
			androidSurfaceCreateInfoKHR.flags = 0;//保留未来使用
			ANativeWindow* nativeWindow{};//一个ANativeWindow只能对应一个VkSurfaceKHR，对ANativeWindow创建一个VkSurfaceKHR则ANativeWindow的引用计数会加一，销毁则减一，完整的 ANativeWindow定义在 Android NDK headers.
			androidSurfaceCreateInfoKHR.window = nativeWindow;//为该surface关联的ANativeWindow的指针，必须是一个有效的ANativeWindow的指针

			//创建
			vkCreateAndroidSurfaceKHR(instance, &androidSurfaceCreateInfoKHR, nullptr, &surface);



			//销毁
			vkDestroySurfaceKHR(instance, surface, nullptr);

			/*
			swapchain的image维度如果不匹配surface，则会在显示的时候进行缩放,到surface的currentExtent，surface的minImageExtent为(1,1),maxImageExtent取决于消费端
			
			*/
		}


		//Wayland Platform  参见3025
		{
			/*
			Wayland是linux系统的默认窗口系统x11的现代替代品，是一种通信协议，定义X window显示服务器和应用程序之间的消息传递。
			*/

			//为Wayland surface创建一个VkSurfaceKHR
			VkWaylandSurfaceCreateInfoKHR waylandSurfaceCreateInfoKHR{};
			waylandSurfaceCreateInfoKHR.sType = VK_STRUCTURE_TYPE_WAYLAND_SURFACE_CREATE_INFO_KHR;
			waylandSurfaceCreateInfoKHR.pNext = nullptr;
			waylandSurfaceCreateInfoKHR.flags = 0;//保留未来使用
			wl_display* wl_display{};
			waylandSurfaceCreateInfoKHR.display = wl_display;//为该surface关联的wl_display的指针，必须是一个有效的wl_display的指针
			wl_surface* wl_surf{};
			waylandSurfaceCreateInfoKHR.surface = wl_surf;//为该surface关联的wl_surface的指针，必须是一个有效的wl_surface的指针

			//创建
			vkCreateWaylandSurfaceKHR(instance, &waylandSurfaceCreateInfoKHR, nullptr, &surface);

			//销毁
			vkDestroySurfaceKHR(instance, surface, nullptr);
			
			
			/*
			currentExtent是一个特殊值 (0xFFFFFFFF, 0xFFFFFFFF),指明surface的维度取决于swapchain的维度，不论应用设置swapchian的维度为多少，当第一张图元被显示了，minImageExtent将为(1,1),maxImageExtent将为支持的surface的最大维度
			
			该surface支持VK_PRESENT_MODE_MAILBOX_KHR

			*/
		}


		//Win32 Platform  参见p3027
		{
			//为Win32 window创建一个 VkSurfaceKHR对象
			VkWin32SurfaceCreateInfoKHR win32SurfaceCreateInfoKHR{};
			win32SurfaceCreateInfoKHR.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
			win32SurfaceCreateInfoKHR.pNext = nullptr;
			win32SurfaceCreateInfoKHR.flags = 0;//保留未来使用
			HWND windowHandle{};//用来表示一个window窗口
			win32SurfaceCreateInfoKHR.hwnd = windowHandle;//为该surface关联的HWND窗口，必须是有效的HWND
			HINSTANCE hInstance{};//用于表示一个程序的实例
			win32SurfaceCreateInfoKHR.hinstance = hInstance;//为该surface关联的win32 HINSTANCE，必须是有效的win32 HINSTANCE
			
			//创建
			vkCreateWin32SurfaceKHR(instance, &win32SurfaceCreateInfoKHR, nullptr, &surface);



			//销毁
			vkDestroySurfaceKHR(instance, surface, nullptr);

			/*
			 minImageExtent, maxImageExtent, 以及 currentExtent永远等于窗口大小
			
			当swapchain和surface的当前维度大小不同后，如果没有VkSwapchainPresentScalingCreateInfoEXT指明如何处理这种不同，那么需要为surface重新创建新的swapchain
			*/
		}

		// XCB Platform  参见3030
		{
			/*
			X11 window是linux系统的默认窗口系统
			*/

			//使用 XCB 客户端库 为 X11 window创建一个VkSurfaceKHR
			VkXcbSurfaceCreateInfoKHR xcbSurfaceCreateInfoKHR{};
			xcbSurfaceCreateInfoKHR.sType = VK_STRUCTURE_TYPE_XCB_SURFACE_CREATE_INFO_KHR;
			xcbSurfaceCreateInfoKHR.pNext = nullptr;
			xcbSurfaceCreateInfoKHR.flags = 0;//保留未来使用
			xcb_connection_t* connection{};
			xcbSurfaceCreateInfoKHR.connection = connection;//为该surface关联 X 服务器的xcb_connection_t的指针，必须是一个有效的X11的xcb_connection_t的指针
			xcb_window_t window{};
			xcbSurfaceCreateInfoKHR.window = window;//为该surface关联 X11 window的xcb_window_t，必须是一个有效 X11 window的xcb_window_t

			//创建
			vkCreateXcbSurfaceKHR(instance, &xcbSurfaceCreateInfoKHR, nullptr, &surface);

			//销毁
			vkDestroySurfaceKHR(instance, surface, nullptr);
			/*
			 minImageExtent, maxImageExtent, 以及 currentExtent永远等于窗口大小
			
			当swapchain和surface的当前维度大小不同后，如果没有VkSwapchainPresentScalingCreateInfoEXT指明如何处理这种不同，那么需要为surface重新创建新的swapchain
			*/
		}


		//Xlib Platform  参见3032
		{
			/*
			X11 window是linux系统的默认窗口系统
			*/

			//使用Xlib客户端库 为 X11 window创建一个VkSurfaceKHR
			VkXlibSurfaceCreateInfoKHR xlibSurfaceCreateInfoKHR{};
			xlibSurfaceCreateInfoKHR.sType = VK_STRUCTURE_TYPE_XLIB_SURFACE_CREATE_INFO_KHR;
			xlibSurfaceCreateInfoKHR.pNext = nullptr;
			xlibSurfaceCreateInfoKHR.flags = 0;//保留未来使用
			Display* display{};
			xlibSurfaceCreateInfoKHR.dpy = display;//为该surface关联 X 服务器的Xlib Display connection的指针，必须是一个有效的Xlib Display的指针
			Window window{};
			xlibSurfaceCreateInfoKHR.window = window;//为该surface关联的 Xlib Window，必须是一个有效的 Xlib Window

			//创建
			vkCreateXlibSurfaceKHR(instance, &xlibSurfaceCreateInfoKHR, nullptr, &surface);

			//销毁
			vkDestroySurfaceKHR(instance, surface, nullptr);
			
			/*
			 minImageExtent, maxImageExtent, 以及 currentExtent永远等于窗口大小

			当swapchain和surface的当前维度大小不同后，如果没有VkSwapchainPresentScalingCreateInfoEXT指明如何处理这种不同，那么需要为surface重新创建新的swapchain
			*/
		}


		//DirectFB Platform  参见3035
		{
			/*
			DirectFB是嵌入式设备的图形显示库
			*/

			//为 DirectFB surface 创建一个VkSurfaceKHR
			VkDirectFBSurfaceCreateInfoEXT directFBSurfaceCreateInfoEXT{};
			directFBSurfaceCreateInfoEXT.sType = VK_STRUCTURE_TYPE_DIRECTFB_SURFACE_CREATE_INFO_EXT;
			directFBSurfaceCreateInfoEXT.pNext = nullptr;
			directFBSurfaceCreateInfoEXT.flags = 0;//保留未来使用
			IDirectFB* dfb{};
			directFBSurfaceCreateInfoEXT.dfb = dfb;//为DirectFB 的 IDirectFB main interface的指针，必须是一个有效的DirectFB IDirectFB的指针
			IDirectFBSurface* iSurface{};
			directFBSurfaceCreateInfoEXT.surface = iSurface;//为IDirectFBSurface surface interface的指针，必须是一个有效的 DirectFB IDirectFBSurface指针

			//创建
			vkCreateDirectFBSurfaceEXT(instance, &directFBSurfaceCreateInfoEXT, nullptr, &surface);

			//销毁
			vkDestroySurfaceKHR(instance, surface, nullptr);

			/*
			 minImageExtent, maxImageExtent, 以及 currentExtent永远等于窗口大小

			*/
		}


		// Fuchsia Platform 参见3037
		{
			/*
			Fuchsia是google的新型移动端操作系统
			*/

			//为  Fuchsia ImagePipe创建一个VkSurfaceKHR
			VkImagePipeSurfaceCreateInfoFUCHSIA imagePipeSurfaceCreateInfoFUCHSIA{};
			imagePipeSurfaceCreateInfoFUCHSIA.sType = VK_STRUCTURE_TYPE_IMAGEPIPE_SURFACE_CREATE_INFO_FUCHSIA;
			imagePipeSurfaceCreateInfoFUCHSIA.pNext = nullptr;
			imagePipeSurfaceCreateInfoFUCHSIA.flags = 0;//保留未来使用
			zx_handle_t imagePipeHandle{};
			imagePipeSurfaceCreateInfoFUCHSIA.imagePipeHandle = imagePipeHandle;//为surface关联的引用到ImagePipe的 zx_handle_t，必须是一个有效的 zx_handle_t

			//创建
			vkCreateImagePipeSurfaceFUCHSIA(instance, &imagePipeSurfaceCreateInfoFUCHSIA, nullptr, &surface);

			//销毁
			vkDestroySurfaceKHR(instance, surface, nullptr);

			/*
			 currentExtent特殊值 (0xFFFFFFFF, 0xFFFFFFFF)表示surface的大小取决于swapchian的大小

			*/
		}



		// Google Games Platform 参见3039
		{
			/*
			 Google Games Platform是google的游戏平台
			*/

			//为Google Games Platform stream descriptor创建一个VkSurfaceKHR
			VkStreamDescriptorSurfaceCreateInfoGGP streamDescriptorSurfaceCreateInfoGGP{};
			streamDescriptorSurfaceCreateInfoGGP.sType = VK_STRUCTURE_TYPE_STREAM_DESCRIPTOR_SURFACE_CREATE_INFO_GGP;
			streamDescriptorSurfaceCreateInfoGGP.pNext = nullptr;
			streamDescriptorSurfaceCreateInfoGGP.flags = 0;//保留未来使用
			GgpStreamDescriptor streamDescriptor{};
			streamDescriptorSurfaceCreateInfoGGP.streamDescriptor = streamDescriptor;//为surface关联的引用到 GGP stream descriptor的GgpStreamDescriptor，必须是一个有效的 GgpStreamDescriptor

			//创建
			vkCreateStreamDescriptorSurfaceGGP(instance, &streamDescriptorSurfaceCreateInfoGGP, nullptr, &surface);

			//销毁
			vkDestroySurfaceKHR(instance, surface, nullptr);

			/*
			在该平台，surface extent为动态的，minImageExtent不会大于1080p，maxImageExtent不会小于1080p,currentExtent反映当前可选择的分辨率

			swapchain的大小一般使用surface的当前大小，如果两者不再匹配则用swapchain的image显示可以缩放到surface的维度且返回VK_SUBOPTIMAL_KHR，或者显示失败返回VK_ERROR_OUT_OF_DATE_KHR
			*/
		}

		//iOS Platform 参见3039
		{


			//为iOS UIView 或者CAMetalLayer创建一个VkSurfaceKHR
			VkIOSSurfaceCreateInfoMVK iOSSurfaceCreateInfoMVK{};
			iOSSurfaceCreateInfoMVK.sType = VK_STRUCTURE_TYPE_IOS_SURFACE_CREATE_INFO_MVK;
			iOSSurfaceCreateInfoMVK.pNext = nullptr;
			iOSSurfaceCreateInfoMVK.flags = 0;//保留未来使用
			void*  view{};
			iOSSurfaceCreateInfoMVK.pView = view;//为 CAMetalLayer 或者UIView的引用
			/*
			VkIOSSurfaceCreateInfoMVK有效用法:
			1.如果pView为一个CAMetalLayer，则其必须是一个有效的CAMetalLayer
			2.如果pView为一个UIView，则其必须是一个有效的UIView，且其底层必须为一个CAMetalLayer类型的CALayer，且vkCreateIOSSurfaceMVK必须在主线程调用
			*/

			//创建
			vkCreateIOSSurfaceMVK(instance, &iOSSurfaceCreateInfoMVK, nullptr, &surface);

			//销毁
			vkDestroySurfaceKHR(instance, surface, nullptr);

		}

		// macOS Platform 参见3043
		{


			//为 macOS NSView 或者 CAMetalLayer创建一个VkSurfaceKHR
			VkMacOSSurfaceCreateInfoMVK macOSSurfaceCreateInfoMVK{};
			macOSSurfaceCreateInfoMVK.sType = VK_STRUCTURE_TYPE_IOS_SURFACE_CREATE_INFO_MVK;
			macOSSurfaceCreateInfoMVK.pNext = nullptr;
			macOSSurfaceCreateInfoMVK.flags = 0;//保留未来使用
			void* view{};
			macOSSurfaceCreateInfoMVK.pView = view;//为 CAMetalLayer 或者 NSView的引用
			/*
			VkMacOSSurfaceCreateInfoMVK有效用法:
			1.如果pView为一个CAMetalLayer，则其必须是一个有效的CAMetalLayer
			2.如果pView为一个 NSView，则其必须是一个有效的 NSView，且其底层必须为一个CAMetalLayer类型的CALayer，且 vkCreateMacOSSurfaceMVK必须在主线程调用
			*/

			//创建
			vkCreateMacOSSurfaceMVK(instance, &macOSSurfaceCreateInfoMVK, nullptr, &surface);

			//销毁
			vkDestroySurfaceKHR(instance, surface, nullptr);

		}


		//VI Platform 参见3045
		{
			/*
			VI Platform是 视觉识别系统
			*/

			//为nn::vi::Layer 创建一个VkSurfaceKHR,调用nn::vi::GetNativeWindow查询layer的 native handle,
			VkViSurfaceCreateInfoNN viSurfaceCreateInfoNN{};
			viSurfaceCreateInfoNN.sType = VK_STRUCTURE_TYPE_VI_SURFACE_CREATE_INFO_NN;
			viSurfaceCreateInfoNN.pNext = nullptr;
			viSurfaceCreateInfoNN.flags = 0;//保留未来使用
			void* window{};//每个window对应一个surface
			viSurfaceCreateInfoNN.window = window;//为surface关联的 nn::vi::Layer的 nn::vi::NativeWindowHandle，必须是一个有效的  nn::vi::NativeWindowHandle

			//创建
			vkCreateViSurfaceNN(instance, &viSurfaceCreateInfoNN, nullptr, &surface);

			//销毁
			vkDestroySurfaceKHR(instance, surface, nullptr);

			/*
			 如果window以一个特定的大小创建，则currentExtent表示这个大小，swapchain的大小应该为这个大小，否则currentExtent为特殊值 (0xFFFFFFFF, 0xFFFFFFFF)表示surface的大小取决于swapchian的大小
			*/
		}


		//Metal Platform 参见3047
		{
			/*
			Metal 是一个将图形和计算紧密集成的现代化 API，提供了强大的着色语言，专为 Apple 平台设计并进行了优化。
			*/

			//为 CAMetalLayer创建一个VkSurfaceKHR
			VkMetalSurfaceCreateInfoEXT metalSurfaceCreateInfoEXT{};
			metalSurfaceCreateInfoEXT.sType = VK_STRUCTURE_TYPE_METAL_SURFACE_CREATE_INFO_EXT;
			metalSurfaceCreateInfoEXT.pNext = nullptr;
			metalSurfaceCreateInfoEXT.flags = 0;//保留未来使用
			void* metalLayer{};
			metalSurfaceCreateInfoEXT.pLayer = metalLayer;//为 CAMetalLayer 的引用,表示一个可渲染的界面
	

			//创建
			vkCreateMetalSurfaceEXT(instance, &metalSurfaceCreateInfoEXT, nullptr, &surface);

			//销毁
			vkDestroySurfaceKHR(instance, surface, nullptr);

		}


		//QNX Screen Platform 参见3047
		{
			/*
			QNX Screen Platform 是一个基于客户机/服务器的屏幕图形子系统。
			*/

			//为QNX Screen surface 创建一个VkSurfaceKHR
			VkScreenSurfaceCreateInfoQNX screenSurfaceCreateInfoQNX{};
			screenSurfaceCreateInfoQNX.sType = VK_STRUCTURE_TYPE_SCREEN_SURFACE_CREATE_INFO_QNX;
			screenSurfaceCreateInfoQNX.pNext = nullptr;
			screenSurfaceCreateInfoQNX.flags = 0;//保留未来使用
			_screen_context* contex{};
			screenSurfaceCreateInfoQNX.context = contex;//为surface关联的QNX Screen context，必须是一个有效的  QNX Screen _screen_context指针
			_screen_window* window{};
			screenSurfaceCreateInfoQNX.window = window;//为surface关联的QNX Screen  window，必须是一个有效的  QNX Screen _screen_window指针



			//创建
			vkCreateScreenSurfaceQNX(instance, &screenSurfaceCreateInfoQNX, nullptr, &surface);

			//销毁
			vkDestroySurfaceKHR(instance, surface, nullptr);

		}

		// Platform-Independent Information  参见p3051
		{
			/*
			一旦创建完毕，VkSurfaceKHR对象就可以在这个扩展和其他扩展中使用，特别是VK_KHR_swapchain扩展。
			*/

			vkDestroySurfaceKHR(instance, VkSurfaceKHR{/*假设这是一个有效的VkSurfaceKHR*/}, nullptr);
			/*
			vkDestroySurfaceKHR有效用法:
			1.所有VkSwapchainKHR必须在其基于平台的native surface之前销毁
			2.如果创建该VkSurfaceKHR时提供了VkAllocationCallbacks，则这里的callbacks也需要提供一个兼容的
			3.如果创建该VkSurfaceKHR时没有提供VkAllocationCallbacks，则这里的pAllocator必须为NULL

			*/

		}

	}



	//Presenting Directly to Display Devices  参见p3052
	{
		/*
		在有些环境中，vulkan可以直接将渲染结果显示到显示设备上而不需要中间的windowing system介入。在比如嵌入式系统中很有用

		VK_KHR_display拓展就提供了相关的函数，创建显示设备相关的VkSurfaceKHR
		*/

		//Display Enumeration  参见p3052
		{
			//显示设备以 VkDisplayKHR表示
			VkDisplayKHR displayKHR{};

			//查询可用的显示设备display信息
			uint32_t displayPropertiesCount = 0;
			std::vector<VkDisplayPropertiesKHR> displayPropertiesKHRs{};
			vkGetPhysicalDeviceDisplayPropertiesKHR(physicalDevice, &displayPropertiesCount, nullptr);
			displayPropertiesKHRs.resize(displayPropertiesCount);
			vkGetPhysicalDeviceDisplayPropertiesKHR(physicalDevice, &displayPropertiesCount, displayPropertiesKHRs.data());//假设返回成功了一个元素
			VkDisplayPropertiesKHR& displayPropertiesKHR = displayPropertiesKHRs[0];
			displayPropertiesKHR.display = VkDisplayKHR{/*假设这是一个有效的VkDisplayKHR*/ };//是一个句柄，用来指代这里描述的显示器。此句柄将在Vulkan实例的生命周期内有效。
			displayPropertiesKHR.displayName = "name";//为NULL或者以空字符结尾的UTF-8字符串表明该显示设备的字符串，如果不为NULL则将在Vulkan实例的生命周期内有效。
			displayPropertiesKHR.persistentContent = VK_FALSE;//告知显示器是否支持 自刷新/内部 缓冲。如果为VK_TRUE，应用程序可以对针对此显示创建的交换链提交持久保留当前操作。
			displayPropertiesKHR.physicalDimensions = VkExtent2D{ .width = 1,.height = 1 };//描述显示器可见部分的物理宽度和高度，单位为毫米
			displayPropertiesKHR.physicalResolution = VkExtent2D{ .width = 1,.height = 1 };//描述显示器的物理、原生或首选分辨率
			displayPropertiesKHR.planeReorderPossible = VK_TRUE;//表示这个显示器上的平面是否可以改变它们的z顺序。如果这是VK_TRUE，应用程序可以以相对于彼此的任何顺序重新排列这个显示器上的平面
			displayPropertiesKHR.supportedTransforms = VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR;//为VkSurfaceTransformFlagBitsKHR组合值位掩码，指明显示器支持的变换操作


			//查询可用的显示设备display信息 2
			uint32_t displayPropertiesCount2 = 0;
			std::vector<VkDisplayProperties2KHR> displayProperties2KHRs{};
			vkGetPhysicalDeviceDisplayProperties2KHR(physicalDevice, &displayPropertiesCount2, nullptr);
			displayProperties2KHRs.resize(displayPropertiesCount);
			vkGetPhysicalDeviceDisplayProperties2KHR(physicalDevice, &displayPropertiesCount, displayProperties2KHRs.data());//假设返回成功了一个元素
			VkDisplayProperties2KHR& displayProperties2KHR = displayProperties2KHRs[0];
			displayProperties2KHR.sType = VK_STRUCTURE_TYPE_DISPLAY_PROPERTIES_2_KHR;
			displayProperties2KHR.pNext = nullptr;
			displayProperties2KHR.displayProperties = displayPropertiesKHRs[0];//VkDisplayPropertiesKHR类型，前面已经提及，这里不再复述

			
			//在有些平台上，如果display已经被某些窗口或者应用程序使用了，则其就不能在其他地方进行使用，所以在这种情况下就需要先获取到显示设备才能进行使用
			
				//查询X11 server上可直接访问的显示设备的许可权
				Display* dpy{};
				vkAcquireXlibDisplayEXT(physicalDevice, dpy/*dpy，为当前拥有显示设备VkDisplayKHR display的到 X11 server的连接*/, VkDisplayKHR{/*假设这是一个有效的VkDisplayKHR*/ }/*display,为vulkan中想要控制的显示设备*/);

				//当获取X11 server上的显示设备时，应用程序还可能希望使用本机句柄而不是VkDisplayKHR句柄来枚举和标识它们。则确定与X11 RandR输出对应的VkDisplayKHR句柄:
				vkGetRandROutputDisplayEXT(physicalDevice, dpy/*dpy，为 查询的rrOutput的到 X11 server的连接*/, 0/*rrOutput,一个 X11 RandR output ID.*/, &displayKHR/*pDisplay,为将返回的对应的 VkDisplayKHR handle.*/);


				//查询Windows 10上可直接访问的显示设备的许可权
				vkAcquireWinrtDisplayNV(physicalDevice, VkDisplayKHR{/*假设这是一个有效的VkDisplayKHR*/ }/*display,为vulkan中想要控制的显示设备*/);

				//当获取Windows 10上的显示设备时，应用程序还可能希望使用本机句柄而不是VkDisplayKHR句柄来枚举和标识它们。则确定与winrt::Windows::Devices::Display::Core::DisplayTarget对应的VkDisplayKHR句柄:
				vkGetWinrtDisplayNV(physicalDevice, 0/*deviceRelativeId,  "DisplayTarget" 的 "AdapterRelativeId" 属性值，由"Id"匹配physicalDevice的VkPhysicalDeviceIDProperties的deviceLUID的"DisplayAdapter"列举.*/, &displayKHR/*pDisplay,为将返回的对应的 VkDisplayKHR handle.*/);


				//查询Direct Rendering Manager (DRM) interface上可直接访问的显示设备的许可权
				vkAcquireDrmDisplayEXT(physicalDevice, 0/*drmFd，DRM primary file descriptor.*/, VkDisplayKHR{/*假设这是一个有效的VkDisplayKHR*/ }/*display,为vulkan中想要控制的显示设备*/);

				//在获取Direct Rendering Manager (DRM) interface上的显示设备前，可以通过一个VkDisplayKHR句柄来标识使用connectorId的显示设备
				vkGetDrmDisplayEXT(physicalDevice, 0/*drmFd，DRM primary file descriptor.*/, 0/*connectorId，特定DRM connector的标识.*/, &displayKHR/*pDisplay,为将返回的对应的 VkDisplayKHR handle.*/);

				//释放已经获取的显示设备
				vkReleaseDisplayEXT(physicalDevice, displayKHR/*display ,要释放控制的显示设备.*/);
			


			//图元在显示设备的plane上进行显示，一个显示设备至少支持一个plane，plane可以被堆叠和混合，以在一个显示器上合成多个图像
			
				//查询plane的属性
				uint32_t displayPlanePropertiesKHRCount = 0;
				std::vector<VkDisplayPlanePropertiesKHR> displayPlanePropertiesKHRs{};
				vkGetPhysicalDeviceDisplayPlanePropertiesKHR(physicalDevice, &displayPlanePropertiesKHRCount, nullptr);
				displayPlanePropertiesKHRs.resize(displayPlanePropertiesKHRCount);
				vkGetPhysicalDeviceDisplayPlanePropertiesKHR(physicalDevice, &displayPlanePropertiesKHRCount, displayPlanePropertiesKHRs.data());//假设成功返回了一个元素
				VkDisplayPlanePropertiesKHR &displayPlanePropertiesKHR = displayPlanePropertiesKHRs[0];
				displayPlanePropertiesKHR.currentDisplay = VkDisplayKHR{/*假设这是一个有效的VkDisplayKHR*/};//为该plane当前关联的display的VkDisplayKHR句柄，如果没有关联任何显示设备，则这里为VK_NULL_HANDLE
				displayPlanePropertiesKHR.currentStackIndex = 0;//为当前plane的z-order,该值在0到调用vkGetPhysicalDeviceDisplayPlanePropertiesKHR返回的pPropertyCount中的值之间


				//查询plane的属性 2
				uint32_t displayPlaneProperties2KHRCount = 0;
				std::vector<VkDisplayPlaneProperties2KHR> displayPlaneProperties2KHRs{};
				vkGetPhysicalDeviceDisplayPlaneProperties2KHR(physicalDevice, &displayPlaneProperties2KHRCount, nullptr);
				displayPlaneProperties2KHRs.resize(displayPlaneProperties2KHRCount);
				vkGetPhysicalDeviceDisplayPlaneProperties2KHR(physicalDevice, &displayPlaneProperties2KHRCount, displayPlaneProperties2KHRs.data());//假设成功返回了一个元素
				VkDisplayPlaneProperties2KHR& displayPlaneProperties2KHR = displayPlaneProperties2KHRs[0];
				displayPlaneProperties2KHR.sType = VK_STRUCTURE_TYPE_DISPLAY_PLANE_PROPERTIES_2_KHR;
				displayPlaneProperties2KHR.pNext = nullptr;
				displayPlaneProperties2KHR.displayPlaneProperties = displayPlanePropertiesKHRs[0];//VkDisplayPlanePropertiesKHR类型，前面已经描述过，这里不再复述


				//确定哪个plane是可用的
				uint32_t displayCount = 0;
				std::vector<VkDisplayKHR> surportDisplayKHRs{};
				vkGetDisplayPlaneSupportedDisplaysKHR(physicalDevice, 0/*planeIndex,为该应用想使用的plane的索引，从0开始，到physical的plane数减一，调用vkGetPhysicalDeviceDisplayPlanePropertiesKHR返回的计数值*/, &displayCount, nullptr);
				surportDisplayKHRs.resize(displayCount);
				vkGetDisplayPlaneSupportedDisplaysKHR(physicalDevice, 0/*planeIndex,为该应用想使用的plane的索引，从0开始，到physical的plane数减一，调用vkGetPhysicalDeviceDisplayPlanePropertiesKHR返回的计数值*/, &displayCount, surportDisplayKHRs.data());//假设成功返回一个元素





				//显示模式  参见p3066

					//显示模式以VkDisplayModeKHR 表示
				VkDisplayModeKHR displayModeKHR{};

				//一个显示设备支持一个或者多个显示模式
				// 查询显示器内置显示模式
				uint32_t displayModePropertiesKHRCount = 0;
				std::vector<VkDisplayModePropertiesKHR> displayModePropertiesKHRs{};
				vkGetDisplayModePropertiesKHR(physicalDevice, displayKHR, &displayModePropertiesKHRCount, nullptr);
				displayModePropertiesKHRs.resize(displayModePropertiesKHRCount);
				vkGetDisplayModePropertiesKHR(physicalDevice, displayKHR, &displayModePropertiesKHRCount, displayModePropertiesKHRs.data());//假设成功返回了一个元素
				VkDisplayModePropertiesKHR& displayModePropertiesKHR = displayModePropertiesKHRs[0];
				displayModePropertiesKHR.displayMode = VkDisplayModeKHR{/*假设这是一个有效的VkDisplayModeKHR*/ };//为display mode的句柄，此句柄将在Vulkan实例的生命周期内有效。
				displayModePropertiesKHR.parameters = VkDisplayModeParametersKHR{ .visibleRegion = VkExtent2D{.width = 1,.height = 1},/*为可视区域的2D范围，width和height必须大于0 */
																				  .refreshRate = 256000 /*为显示器每秒刷新的次数乘上1000，该值必须大于0*/ };//VkDisplayModeParametersKHR结构体，描述和display mode相关的参数


				// 查询显示器内置显示模式2
				uint32_t displayModeProperties2KHRCount = 0;
				std::vector<VkDisplayModeProperties2KHR> displayModeProperties2KHRs{};
				vkGetDisplayModeProperties2KHR(physicalDevice, displayKHR, &displayModeProperties2KHRCount, nullptr);
				displayModeProperties2KHRs.resize(displayModeProperties2KHRCount);
				vkGetDisplayModeProperties2KHR(physicalDevice, displayKHR, &displayModeProperties2KHRCount, displayModeProperties2KHRs.data());//假设成功返回了一个元素
				VkDisplayModeProperties2KHR& displayModeProperties2KHR = displayModeProperties2KHRs[0];
				displayModeProperties2KHR.sType = VK_STRUCTURE_TYPE_DISPLAY_MODE_PROPERTIES_2_KHR;
				displayModeProperties2KHR.pNext = nullptr;
				displayModeProperties2KHR.displayModeProperties = displayModePropertiesKHRs[0];//VkDisplayModePropertiesKHR类型，前面已经描述过了，这里不再复述


				//为显示器创建额外的显示模式
				VkDisplayModeCreateInfoKHR displayModeCreateInfoKHR{};
				displayModeCreateInfoKHR.sType = VK_STRUCTURE_TYPE_DISPLAY_MODE_CREATE_INFO_KHR;
				displayModeCreateInfoKHR.pNext = nullptr;
				displayModeCreateInfoKHR.flags = 0;//保留未来使用,必须为0
				displayModeCreateInfoKHR.parameters = VkDisplayModeParametersKHR{ .visibleRegion = VkExtent2D{.width = 1,.height = 1},/*为可视区域的2D范围，width和height必须大于0 */
																				  .refreshRate = 256000 /*为显示器每秒刷新的次数乘上1000，该值必须大于0*/ };//VkDisplayModeParametersKHR结构体，描述创建的新的display mode相关的参数，如果该参数和当前显示器不兼容，则创建的时候会返回VK_ERROR_INITIALIZATION_FAILED.
				vkCreateDisplayModeKHR(physicalDevice, displayKHR, &displayModeCreateInfoKHR, nullptr, &displayModeKHR);

				/*
				应用要将结果直接显示到显示器上需要选中一个显示模式以及一个plane作为显示的目标
				*/
				//查询一个显示模式和显示plane的组合的显示能力
				VkDisplayPlaneCapabilitiesKHR displayPlaneCapabilitiesKHR{};
				displayPlaneCapabilitiesKHR.supportedAlpha = VK_DISPLAY_PLANE_ALPHA_GLOBAL_BIT_KHR;//为VkDisplayPlaneAlphaFlagBitsKHR组合值位掩码，表明支持的alpha混合模式
				displayPlaneCapabilitiesKHR.minSrcPosition = VkOffset2D{ .x = 0,.y = 0 };//是此平面使用指定模式支持的显示图片中读取pxiel的最小矩形位置偏移量。
				displayPlaneCapabilitiesKHR.maxSrcPosition = VkOffset2D{ .x = 1,.y = 1 };//是此平面使用指定模式支持的显示图片中读取pxiel的最大矩形位置偏移量，x，y必须大于minSrcPosition中对应的。
				displayPlaneCapabilitiesKHR.minSrcExtent = VkExtent2D{ .width = 1,.height = 1 };//是此平面使用指定模式支持的显示图片中读取pxiel的最小矩形的大小。
				displayPlaneCapabilitiesKHR.maxSrcExtent = VkExtent2D{ .width = 2,.height = 2 };//是此平面使用指定模式支持的显示图片中读取pxiel的最大矩形的大小。
				displayPlaneCapabilitiesKHR.minDstPosition = VkOffset2D{ .x = 0,.y = 0 };//是此平面使用指定模式支持的显示图片的显示输出的最小矩形位置偏移量。可能含有负数。
				displayPlaneCapabilitiesKHR.maxDstPosition = VkOffset2D{ .x = 1,.y = 1 };//是此平面使用指定模式支持的显示图片的显示输出的最大矩形偏移量。x，y必须大于minDstPosition中对应的。可能含有负数。
				displayPlaneCapabilitiesKHR.minDstExtent = VkExtent2D{ .width = 1,.height = 1 };//是此平面使用指定模式支持的显示图片的显示输出的最小矩形的大小。
				displayPlaneCapabilitiesKHR.maxDstExtent = VkExtent2D{ .width = 2,.height = 2 };//是此平面使用指定模式支持的显示图片的显示输出的最大矩形的大小。

				vkGetDisplayPlaneCapabilitiesKHR(physicalDevice, displayModeKHR/*mode,指明显示模式的VkDisplayModeKHR句柄，隐含了显示器参数*/, 0/*planeIndex，为plane的索引*/, &displayPlaneCapabilitiesKHR);


				//查询一个显示模式和显示plane的组合的显示能力 2
				VkDisplayPlaneCapabilities2KHR displayPlaneCapabilities2KHR{};
				displayPlaneCapabilities2KHR.sType = VK_STRUCTURE_TYPE_DISPLAY_PLANE_CAPABILITIES_2_KHR;
				displayPlaneCapabilities2KHR.pNext = nullptr;
				displayPlaneCapabilities2KHR.capabilities = displayPlaneCapabilitiesKHR;//VkDisplayPlaneCapabilitiesKHR类型，前面已经描述过了，这里不再复述

				VkDisplayPlaneInfo2KHR displayPlaneInfo2KHR{};
				displayPlaneInfo2KHR.sType = VK_STRUCTURE_TYPE_DISPLAY_PLANE_INFO_2_KHR;
				displayPlaneInfo2KHR.pNext = nullptr;
				displayPlaneInfo2KHR.mode = displayModeKHR;//指明显示模式的VkDisplayModeKHR句柄，隐含了显示器参数
				displayPlaneInfo2KHR.planeIndex = 0;//为plane的索引

				vkGetDisplayPlaneCapabilities2KHR(physicalDevice, &displayPlaneInfo2KHR, &displayPlaneCapabilities2KHR);
		}


		//Display Control   参见p3077
		{
			//设置显示器的电源状态
			VkDisplayPowerInfoEXT displayPowerInfoEXT{};
			displayPowerInfoEXT.sType = VK_STRUCTURE_TYPE_DISPLAY_POWER_INFO_EXT;
			displayPowerInfoEXT.pNext = nullptr;
			displayPowerInfoEXT.powerState = VK_DISPLAY_POWER_STATE_ON_EXT;/*指明显示器的新电源状态的 VkDisplayPowerStateEXT值
			VkDisplayPowerStateEXT:
			VK_DISPLAY_POWER_STATE_OFF_EXT:  指明关闭显示器
			VK_DISPLAY_POWER_STATE_SUSPEND_EXT:  指明显示器处于低功耗模式，相比于VK_DISPLAY_POWER_STATE_OFF_EXT能够很快回到VK_DISPLAY_POWER_STATE_ON_EXT，该模式可能和VK_DISPLAY_POWER_STATE_OFF_EXT状态相同。
			VK_DISPLAY_POWER_STATE_ON_EXT:  指明开启显示器
			*/
			vkDisplayPowerControlEXT(device, VkDisplayKHR{/*假设这是一个有效的VkDisplayKHR*/ }, & displayPowerInfoEXT);



		}

		//Display Surfaces  参见p3078
		{
			/*

			一个完整的显示配置包括一个显示模式、一个或多个显示plane和描述其行为的任何参数，
			以及描述与这些平面相关联的图像的某些方面的参数。显示表面描述了带完整显示配置中的单个平面的配置。
			*/

			//为显示plane 创建一个VkSurfaceKHR
			VkDisplaySurfaceCreateInfoKHR displaySurfaceCreateInfoKHR{};
			displaySurfaceCreateInfoKHR.sType = VK_STRUCTURE_TYPE_DISPLAY_SURFACE_CREATE_INFO_KHR;
			displaySurfaceCreateInfoKHR.pNext = nullptr;
			displaySurfaceCreateInfoKHR.flags = 0;//保留未来使用，必须为0
			displaySurfaceCreateInfoKHR.displayMode = VkDisplayModeKHR{/*假设这是一个有效的VkDisplayModeKHR，见前面描述*/ };//为VkDisplayModeKHR句柄，指明该显示surface使用的显示模式
			displaySurfaceCreateInfoKHR.planeIndex = 0;//为该surface所对的显示plane索引
			displaySurfaceCreateInfoKHR.planeStackIndex = 0;//为该surface所对的显示plane的 z-order
			displaySurfaceCreateInfoKHR.transform = VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR;//为一个 VkSurfaceTransformFlagBitsKHR值，指明图像在扫描输出时应用的变换操作
			displaySurfaceCreateInfoKHR.globalAlpha = 1;//为全局的alpha值，如果alphaMode 不为VK_DISPLAY_PLANE_ALPHA_GLOBAL_BIT_KHR，则该值忽略
			displaySurfaceCreateInfoKHR.alphaMode = VK_DISPLAY_PLANE_ALPHA_OPAQUE_BIT_KHR;/*为 VkDisplayPlaneAlphaFlagBitsKHR值，指明使用的alpha混合类型
			VkDisplayPlaneAlphaFlagBitsKHR:

			VK_DISPLAY_PLANE_ALPHA_OPAQUE_BIT_KHR: 指明source image将被视为不透明的。
			VK_DISPLAY_PLANE_ALPHA_GLOBAL_BIT_KHR: 指明必须指定一个全局的alpha值，将应用到源图像的所有像素。
			VK_DISPLAY_PLANE_ALPHA_PER_PIXEL_BIT_KHR:  指明每个像素的alpha值将由源图像的像素的alpha值决定。如果源格式没有alpha值，则不会应用混合。源alpha值不会预乘到源图像的其他颜色组件中。
			VK_DISPLAY_PLANE_ALPHA_PER_PIXEL_PREMULTIPLIED_BIT_KHR: 等价于VK_DISPLAY_PLANE_ALPHA_PER_PIXEL_BIT_KHR，但源alpha值假设已经预乘到源图像的其他颜色组件中。
			*/
			displaySurfaceCreateInfoKHR.imageExtent = VkExtent2D{ .width = 1,.height = 1 };//指明该surface使用的image显示图像的大小
			/*
			VkDisplaySurfaceCreateInfoKHR有效用法:
			1.planeIndex 必须小于vkGetPhysicalDeviceDisplayPlanePropertiesKHR返回的设备支持的plane的数量
			2.如果调用vkGetPhysicalDeviceDisplayPropertiesKHR返回的VkDisplayPropertiesKHR元素的display对应的displayMode的planeReorderPossible为VK_TRUE,则planeStackIndex 必须小于vkGetPhysicalDeviceDisplayPlanePropertiesKHR返回的当前physical device支持的plane的数量，
							否则planeStackIndex 必须等于vkGetPhysicalDeviceDisplayPlanePropertiesKHR返回的对应到displayMode的plane的VkDisplayPlanePropertiesKHR的currentStackIndex
			3.如果alphaMode 为VK_DISPLAY_PLANE_ALPHA_GLOBAL_BIT_KHR，则globalAlpha必须在[0,1]之间
			4.alphaMode必须是对应到displayMode的plane的VkDisplayPlaneCapabilitiesKHR中的supportedAlpha支持的
			5.transform必须是对应到displayMode的plane的VkDisplayPropertiesKHR中的supportedTransforms支持的
			6.imageExtent的width以及height必须小于等于VkPhysicalDeviceLimits::maxImageDimension2D中对应的
			*/


			VkSurfaceKHR surfaceKHR{};
			vkCreateDisplayPlaneSurfaceKHR(instance, &displaySurfaceCreateInfoKHR, nullptr, &surfaceKHR);

			//销毁
			vkDestroySurfaceKHR(instance, surfaceKHR, nullptr);
		}

		//Presenting to Headless Surfaces 参见p3082
		{
			/*
			Vulkan渲染可以呈现到一个无头表面，其中表示操作是一个noop，不会产生外部可见的结果。

			方便测试一些vulkan的拓展或者特性等。
			*/


			//创建一个无头表面
			VkHeadlessSurfaceCreateInfoEXT headlessSurfaceCreateInfoEXT{};
			headlessSurfaceCreateInfoEXT.sType = VK_STRUCTURE_TYPE_HEADLESS_SURFACE_CREATE_INFO_EXT;
			headlessSurfaceCreateInfoEXT.pNext = nullptr;
			headlessSurfaceCreateInfoEXT.flags = 0;//保留未来使用，必须为0

			VkSurfaceKHR surfaceKHR{};
			vkCreateHeadlessSurfaceEXT(instance, &headlessSurfaceCreateInfoEXT, nullptr, &surfaceKHR);

			//销毁
			vkDestroySurfaceKHR(instance, surfaceKHR, nullptr);

			/*
			surface的 currentExtent为预留的值 (0xFFFFFFFF, 0xFFFFFFFF)，表明使用swapchain的大小。
			*/
		}

	}


	//Querying for WSI Support  参见p3084
	{
		/*
		并非所有的物理设备都将包括WSI支持。在物理设备中，并非所有的队列族都将支持表示。
		
		*/

		VkSurfaceKHR surfaceKHR{/*假设这是一个有效的VkSurfaceKHR*/};

		//查询physical device的队列组是否支持在surface上的显示
		VkBool32 supportsPresent;
		vkGetPhysicalDeviceSurfaceSupportKHR(physicalDevice, 0/*queueFamilyIndex,为队列索引，必须小于调用vkGetPhysicalDeviceQueueFamilyProperties返回的物理设备支持的队列组数量.*/, surfaceKHR/*surface ，为surface的VkSurfaceKHR句柄.*/, &supportsPresent/**/);


		//Android Platform 不需要查询，所有的队列都支持显示

		//Wayland Platform
		//查询physical device的队列组是否支持在 Wayland compositor上的显示，必须在创建surface前调用
		wl_display* wl_disp{/*假设这是一个有效的wl_display指针*/};
		VkBool32 waylandPrensentSupport = vkGetPhysicalDeviceWaylandPresentationSupportKHR(physicalDevice, 0/*queueFamilyIndex,为队列索引，必须小于调用vkGetPhysicalDeviceQueueFamilyProperties返回的物理设备支持的队列组数量.*/, wl_disp/*display,是Wayland compositor相关的wl_display指针.*/);
	

		//Win32 Platform
		//查询physical device的队列组是否支持在Microsoft Windows desktop上的显示，必须在创建surface前调用
		VkBool32 winPrensentSupport = vkGetPhysicalDeviceWin32PresentationSupportKHR(physicalDevice, 0/*queueFamilyIndex,为队列索引，必须小于调用vkGetPhysicalDeviceQueueFamilyProperties返回的物理设备支持的队列组数量.*/);


		//XCB Platform
		//查询physical device的队列组是否支持在X11 server上的显示，使用XCB 客户端库，必须在创建surface前调用
		xcb_connection_t* xcb_conn{/*假设这是一个有效的xcb_connection_t指针*/ };
		typedef uint32_t xcb_visualid_t;
		xcb_visualid_t xcb_visualid{/*假设这是一个有效的xcb_screen_t指针*/ };
		VkBool32 xcbPrensentSupport = vkGetPhysicalDeviceXcbPresentationSupportKHR(physicalDevice, 0/*queueFamilyIndex,为队列索引，必须小于调用vkGetPhysicalDeviceQueueFamilyProperties返回的物理设备支持的队列组数量.*/, xcb_conn/*connection,为 X11 Server连接的xcb_connection_t指针*/, xcb_visualid/*visual_id,为一个 X11 visual (xcb_visualid_t).*/);


		//Xlib Platform
		//查询physical device的队列组是否支持在X11 server上的显示，使用Xlib 客户端库，必须在创建surface前调用
		Display* disp{/*假设这是一个有效的Display指针*/};
		typedef uint32_t VisualID;
		VisualID visualid{/*假设这是一个有效的VisualID*/ };
		VkBool32 xlibPrensentSupport = vkGetPhysicalDeviceXlibPresentationSupportKHR(physicalDevice, 0/*queueFamilyIndex,为队列索引，必须小于调用vkGetPhysicalDeviceQueueFamilyProperties返回的物理设备支持的队列组数量.*/, disp/*dpy,为 X11 Server的Display连接指针*/, visualid/*visualId,为一个 X11 visual (VisualID).*/);


		//DirectFB Platform
		//查询physical device的队列组是否支持使用DirectFB library进行显示，必须在创建surface前调用
		IDirectFB* dfb{/*假设这是一个有效的IDirectFB指针*/ };
		VkBool32 directfbPrensentSupport = vkGetPhysicalDeviceDirectFBPresentationSupportEXT(physicalDevice, 0/*queueFamilyIndex,为队列索引，必须小于调用vkGetPhysicalDeviceQueueFamilyProperties返回的物理设备支持的队列组数量.*/, dfb/*dfb,为e IDirectFB main interface的IDirectFB指针.*/);


		//Fuchsia Platform  不需要查询，所有的队列都支持显示

		//Google Games Platform  不需要查询，所有的 VK_QUEUE_GRAPHICS_BIT 或者VK_QUEUE_COMPUTE_BIT队列都支持显示

		// iOS Platform  不需要查询，所有的队列都支持显示

		//macOS Platform  不需要查询，所有的队列都支持显示
		
		// VI Platform   不需要查询，所有的队列都支持显示

		//QNX Screen Platform
		//查询physical device的队列组是否支持在QNX Screen compositor上进行显示，必须在创建surface前调用
		_screen_window* qnxWindow{/*假设这是一个有效的_screen_window指针*/ };
		VkBool32 qnxPrensentSupport = vkGetPhysicalDeviceScreenPresentationSupportQNX(physicalDevice, 0/*queueFamilyIndex,为队列索引，必须小于调用vkGetPhysicalDeviceQueueFamilyProperties返回的物理设备支持的队列组数量.*/, qnxWindow/*window,为QNX Screen窗口指针.*/);

	}


	//Surface Queries  参见3091
	{
		/*
		wapchain将渲染结果通过surface显示的能力由WSI platform, the native window 或者 display, 以及 physical device相关的信息决定。
		*/
		VkSurfaceKHR surfaceKHR{/*假设这是一个有效的VkSurfaceKHR*/ };

		//Surface Capabilities  参见p3091
		{
			

			//查询创建swapchain时需要的surface的基本能力
			VkSurfaceCapabilitiesKHR surfaceCapabilitiesKHR{};
			vkGetPhysicalDeviceSurfaceCapabilitiesKHR(physicalDevice, surfaceKHR/*surface,为surface句柄，必须是有效的且被physicalDevice支持，见vkGetPhysicalDeviceSurfaceSupportKHR*/, &surfaceCapabilitiesKHR);//假设返回了正确结果
			surfaceCapabilitiesKHR.minImageCount = 1;//为设备支持的对surface创建的swapchian的最小的image的数量，至少为1
			surfaceCapabilitiesKHR.maxImageCount = 1;//为设备支持的对surface创建的swapchian的最大的image的数量，可以为0或者大于等于minImageCount，0意味着没有限制，只受限于内存
			surfaceCapabilitiesKHR.currentExtent = VkExtent2D{.width = 1,.height = 1};//为surface当前的宽高，如果是特殊值(0xFFFFFFFF, 0xFFFFFFFF)则指明该surface的宽高屈居于创建的swapchain的宽高
			surfaceCapabilitiesKHR.minImageExtent = VkExtent2D{ .width = 1,.height = 1 };//为设备支持的对surface创建的swapchian的最小宽高，小于等于currentExtent中对应的值，除非currentExtent为特殊值
			surfaceCapabilitiesKHR.maxImageExtent = VkExtent2D{ .width = 1,.height = 1 };//为设备支持的对surface创建的swapchian的最大宽高，大于等于minImageExtent中对应的值，大于等于currentExtent中对应的值，除非currentExtent为特殊值
			surfaceCapabilitiesKHR.maxImageArrayLayers = 1;//为设备支持的对surface创建的swapchian中的image所能含有的最大的arrayLayer数量，至少为1
			surfaceCapabilitiesKHR.supportedTransforms = VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR;/*VkSurfaceTransformFlagBitsKHR 组合值位掩码，指明设备支持的对surface能够支持的presentation transforms
			VkSurfaceTransformFlagBitsKHR:

			VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR: 指明图像内容的显示不会经过变换
			VK_SURFACE_TRANSFORM_ROTATE_90_BIT_KHR:  指明图像内容的显示会顺时针旋转90度
			VK_SURFACE_TRANSFORM_ROTATE_180_BIT_KHR:  指明图像内容的显示会顺时针旋转180度
			VK_SURFACE_TRANSFORM_ROTATE_270_BIT_KHR:  指明图像内容的显示会顺时针旋转270度
			VK_SURFACE_TRANSFORM_HORIZONTAL_MIRROR_BIT_KHR:  指明图像内容的显示会水平镜像反转
			VK_SURFACE_TRANSFORM_HORIZONTAL_MIRROR_ROTATE_90_BIT_KHR:  指明图像内容的显示会水平镜像反转，然后顺时针旋转90度
			VK_SURFACE_TRANSFORM_HORIZONTAL_MIRROR_ROTATE_180_BIT_KHR:  指明图像内容的显示会水平镜像反转，然后顺时针旋转180度
			VK_SURFACE_TRANSFORM_HORIZONTAL_MIRROR_ROTATE_270_BIT_KHR:  指明图像内容的显示会水平镜像反转，然后顺时针旋转270度
			VK_SURFACE_TRANSFORM_INHERIT_BIT_KHR:  指明图像内容的显示的不指明变换操作，其由vulkan外的特定平台决定
			*/
			surfaceCapabilitiesKHR.currentTransform = VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR;//为一个VkSurfaceTransformFlagBitsKHR值，指明surface当前的presentation transforms
			surfaceCapabilitiesKHR.supportedCompositeAlpha = VK_COMPOSITE_ALPHA_INHERIT_BIT_KHR;/* VkCompositeAlphaFlagBitsKHR 组合值位掩码，表示显示支持的alpha混合模式，至少将设置一个位。不透明混合可以通过使用任何没有alpha组件的图像格式，或者通过确保可呈现图像中的所有像素都有1.0的alpha值来实现。
			VkCompositeAlphaFlagBitsKHR:

			VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR: 图像中的alpha分量（如果存在）会在混合处理中会被忽略，就像是其alpha分量固定为一个常量1.0一样 
			VK_COMPOSITE_ALPHA_PRE_MULTIPLIED_BIT_KHR:  图像中的alpha分量（如果存在）会在混合处理中会被考虑，图像的非alpha分量会被认为是已经和alpha分量相乘后得到的结果。
			VK_COMPOSITE_ALPHA_POST_MULTIPLIED_BIT_KHR:  图像中的alpha分量（如果存在）会在混合处理中会被考虑，图像的非alpha分量不会被认为是已经和alpha分量相乘后得到的结果，反而会在混合的时候将非alpha分量乘上alpha分量。
			VK_COMPOSITE_ALPHA_INHERIT_BIT_KHR: 该方式认为图像中的alpha分量在vulkan是不可知的，需要由应用使用本地系统命令去设置alpha混合模式，如果没有使用本地系统命令去设置该模式，则使用该平台的默认模式。

			*/
			surfaceCapabilitiesKHR.supportedUsageFlags = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;//VkImageUsageFlagBits组合值位掩码，指明设备支持的对surface以  VkPresentModeKHR为 VK_PRESENT_MODE_IMMEDIATE_KHR, VK_PRESENT_MODE_MAILBOX_KHR, VK_PRESENT_MODE_FIFO_KHR 或者VK_PRESENT_MODE_FIFO_RELAXED_KHR创建的swapchian中的image的用法，必须包含VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT


			//通过内核或者拓展查询创建swapchain时需要的surface的基本能力
			{
				struct PhysicalDeviceSurfaceInfo2KHREXT
				{
					VkSurfaceFullScreenExclusiveInfoEXT surfaceFullScreenExclusiveInfoEXT{};
					VkSurfaceFullScreenExclusiveWin32InfoEXT surfaceFullScreenExclusiveWin32InfoEXT{};
					VkSurfacePresentModeEXT surfacePresentModeEXT{};
					PhysicalDeviceSurfaceInfo2KHREXT() {
						Init();
					}
					void Init() {
						surfaceFullScreenExclusiveInfoEXT.sType = VK_STRUCTURE_TYPE_SURFACE_FULL_SCREEN_EXCLUSIVE_INFO_EXT;
						surfaceFullScreenExclusiveInfoEXT.pNext = &surfaceFullScreenExclusiveWin32InfoEXT;
						surfaceFullScreenExclusiveWin32InfoEXT.sType = VK_STRUCTURE_TYPE_SURFACE_FULL_SCREEN_EXCLUSIVE_WIN32_INFO_EXT;
						surfaceFullScreenExclusiveWin32InfoEXT.pNext = nullptr;
						surfacePresentModeEXT.sType = VK_STRUCTURE_TYPE_SURFACE_PRESENT_MODE_EXT;
						surfacePresentModeEXT.pNext = nullptr;
					}
				};

				VkPhysicalDeviceSurfaceInfo2KHR physicalDeviceSurfaceInfo2KHR{};
				physicalDeviceSurfaceInfo2KHR.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SURFACE_INFO_2_KHR;
				PhysicalDeviceSurfaceInfo2KHREXT physicalDeviceSurfaceInfo2KHREXT{};
				//VkPhysicalDeviceSurfaceInfo2KHR.pNext
				{
					//VkSurfaceFullScreenExclusiveInfoEXT指明应用偏好使用全屏的行为，如果不含该结构体可以认为默认为VK_FULL_SCREEN_EXCLUSIVE_DEFAULT_EXT
					VkSurfaceFullScreenExclusiveInfoEXT& surfaceFullScreenExclusiveInfoEXT = physicalDeviceSurfaceInfo2KHREXT.surfaceFullScreenExclusiveInfoEXT;
					surfaceFullScreenExclusiveInfoEXT.fullScreenExclusive = VK_FULL_SCREEN_EXCLUSIVE_DEFAULT_EXT;/*为 VkFullScreenExclusiveEXT值，指明应用更偏好的全屏行为
					VkFullScreenExclusiveEXT:
					VK_FULL_SCREEN_EXCLUSIVE_DEFAULT_EXT:  指明实现应该确定适当的全屏方式而不管如何该方式是如何认定的
					VK_FULL_SCREEN_EXCLUSIVE_ALLOWED_EXT:  指定实现或许会使用可用的全屏独有机制，这个机制可能会导致更好的的性能以及/或者不能的显示能力，但可能在swapchain 初始化，第一次显示以及/或者销毁的时候需要更多的 disruptive transitions。
					VK_FULL_SCREEN_EXCLUSIVE_DISALLOWED_EXT:  指定实现应该避免使用依赖 disruptive transitions的全屏机制
					VK_FULL_SCREEN_EXCLUSIVE_APPLICATION_CONTROLLED_EXT:  指明应用应该通过使用vkAcquireFullScreenExclusiveModeEXT以及vkReleaseFullScreenExclusiveModeEXT命令来管理全屏独有模式

					*/

					VkSurfaceFullScreenExclusiveWin32InfoEXT surfaceFullScreenExclusiveWin32InfoEXT = physicalDeviceSurfaceInfo2KHREXT.surfaceFullScreenExclusiveWin32InfoEXT;
					HMONITOR hMonitor{/*假设这是一个有效的HMONITOR*/ };
					surfaceFullScreenExclusiveWin32InfoEXT.hmonitor = hMonitor;//为创建surface的显示其的Win32 HMONITOR句柄，必须是有效的


					//
					VkSurfacePresentModeEXT& surfacePresentModeEXT = physicalDeviceSurfaceInfo2KHREXT.surfacePresentModeEXT;
					surfacePresentModeEXT.presentMode = VK_PRESENT_MODE_FIFO_KHR;//为swapchain要使用的显示模式，必须是 vkGetPhysicalDeviceSurfacePresentModesKHR中返回的surface支持的

				}
				physicalDeviceSurfaceInfo2KHR.pNext = &physicalDeviceSurfaceInfo2KHREXT.surfaceFullScreenExclusiveInfoEXT;
				physicalDeviceSurfaceInfo2KHR.surface = surfaceKHR;
				/*
				VkPhysicalDeviceSurfaceInfo2KHR有效用法:
				1.如果pNext中包含一个fullScreenExclusive设为VK_FULL_SCREEN_EXCLUSIVE_APPLICATION_CONTROLLED_EXT的VkSurfaceFullScreenExclusiveInfoEXT，且surface使用vkCreateWin32SurfaceKHR创建，则pNext中必须包含一个VkSurfaceFullScreenExclusiveWin32InfoEXT
				2.如果surface 不为VK_NULL_HANDLE，且VK_GOOGLE_surfaceless_query 拓展未开启，则surface必须是有效的VkSurfaceKHR句柄
				*/


				struct SurfaceCapabilities2KHREXT {
					VkDisplayNativeHdrSurfaceCapabilitiesAMD displayNativeHdrSurfaceCapabilitiesAMD{};
					VkLatencySurfaceCapabilitiesNV  latencySurfaceCapabilitiesNV{};
					VkSharedPresentSurfaceCapabilitiesKHR sharedPresentSurfaceCapabilitiesKHR{};
					VkSurfaceCapabilitiesFullScreenExclusiveEXT surfaceCapabilitiesFullScreenExclusiveEXT{};
					VkSurfaceCapabilitiesPresentBarrierNV surfaceCapabilitiesPresentBarrierNV{};
					VkSurfacePresentModeCompatibilityEXT surfacePresentModeCompatibilityEXT{};
					VkSurfacePresentScalingCapabilitiesEXT surfacePresentScalingCapabilitiesEXT{};
					VkSurfaceProtectedCapabilitiesKHR surfaceProtectedCapabilitiesKHR{};
					SurfaceCapabilities2KHREXT() {
						Init();
					}
					void Init() {
						displayNativeHdrSurfaceCapabilitiesAMD.sType = VK_STRUCTURE_TYPE_DISPLAY_NATIVE_HDR_SURFACE_CAPABILITIES_AMD;
						displayNativeHdrSurfaceCapabilitiesAMD.pNext = nullptr;
						latencySurfaceCapabilitiesNV.sType = VK_STRUCTURE_TYPE_MAX_ENUM;//没有定义这里设置为非法值
						latencySurfaceCapabilitiesNV.pNext = nullptr;
						sharedPresentSurfaceCapabilitiesKHR.sType = VK_STRUCTURE_TYPE_SHARED_PRESENT_SURFACE_CAPABILITIES_KHR;
						sharedPresentSurfaceCapabilitiesKHR.pNext = nullptr;
						surfaceCapabilitiesFullScreenExclusiveEXT.sType = VK_STRUCTURE_TYPE_SURFACE_CAPABILITIES_FULL_SCREEN_EXCLUSIVE_EXT;
						surfaceCapabilitiesFullScreenExclusiveEXT.pNext = nullptr;
						surfaceCapabilitiesPresentBarrierNV.sType = VK_STRUCTURE_TYPE_SURFACE_CAPABILITIES_PRESENT_BARRIER_NV;
						surfaceCapabilitiesPresentBarrierNV.pNext = nullptr;
						surfacePresentModeCompatibilityEXT.sType = VK_STRUCTURE_TYPE_SURFACE_PRESENT_MODE_COMPATIBILITY_EXT;
						surfacePresentModeCompatibilityEXT.pNext = nullptr;
						surfacePresentScalingCapabilitiesEXT.sType = VK_STRUCTURE_TYPE_SURFACE_PRESENT_SCALING_CAPABILITIES_EXT;
						surfacePresentScalingCapabilitiesEXT.pNext = nullptr;
						surfaceProtectedCapabilitiesKHR.sType = VK_STRUCTURE_TYPE_SURFACE_PROTECTED_CAPABILITIES_KHR;
						surfaceProtectedCapabilitiesKHR.pNext = nullptr;


					}
				};


				VkSurfaceCapabilities2KHR surfaceCapabilities2KHR{};
				surfaceCapabilities2KHR.sType = VK_STRUCTURE_TYPE_SURFACE_CAPABILITIES_2_KHR;
				SurfaceCapabilities2KHREXT surfaceCapabilities2KHREXT{};
				//VkSurfaceCapabilities2KHR.pNext  这些值都是查询后返回的
				{
					//查询一个可显示的 protected VkSurfaceKHR
					VkSurfaceProtectedCapabilitiesKHR& surfaceProtectedCapabilitiesKHR = surfaceCapabilities2KHREXT.surfaceProtectedCapabilitiesKHR;
					surfaceProtectedCapabilitiesKHR.supportsProtected = VK_TRUE;//返回值，指定是否可以在屏幕上显示从VkPhysicalDeviceSurfaceInfo2KHR::surface为特定窗口系统创建的protected swapchain。如果为VK_TRUE，则必须支持创建带有VK_SWAPCHAIN_CREATE_PROTECTED_BIT_KHR标志的swapchain。


					//获取surface支持的缩放能力
					VkSurfacePresentScalingCapabilitiesEXT& surfacePresentScalingCapabilitiesEXT = surfaceCapabilities2KHREXT.surfacePresentScalingCapabilitiesEXT;
					surfacePresentScalingCapabilitiesEXT.minScaledImageExtent = VkExtent2D{ .width = 1,.height = 1 };//当使用支持的缩放方法之一时，该值包含指定设备上surface的最小有效 swapchain的缩放范围，或特殊值（0x FFFFFFFF，0x FFFFFFFF），表明surface大小将由swapchain的范围决定。该范围的width和height均应小于或等于VkSurfaceCapabilitiesKHR::minImageExtent对应的值
					surfacePresentScalingCapabilitiesEXT.maxScaledImageExtent = VkExtent2D{ .width = 1,.height = 1 };//当使用支持的缩放方法之一时，该值包含指定设备上surface的最大有效 swapchain的缩放范围，或特殊值（0x FFFFFFFF，0x FFFFFFFF），表明surface大小将由swapchain的范围决定。该范围的width和height均应大于或等于VkSurfaceCapabilitiesKHR::maxImageExtent对应的值
					surfacePresentScalingCapabilitiesEXT.supportedPresentGravityX = VK_PRESENT_GRAVITY_MIN_BIT_EXT;/* VkPresentGravityFlagBitsEXT组合值位掩码，指明surface支持的X轴的pixel gravity，为0表示X轴不支持pixel gravity
					VkPresentGravityFlagBitsEXT:
					VK_PRESENT_GRAVITY_MIN_BIT_EXT: 指明pixels将趋向于surface的顶部或左侧。
					VK_PRESENT_GRAVITY_MAX_BIT_EXT: 指明pixels将趋向于surface的底部或右侧。
					VK_PRESENT_GRAVITY_CENTERED_BIT_EXT: 指明pixels将处于surface的中心。

					*/
					surfacePresentScalingCapabilitiesEXT.supportedPresentGravityY = VK_PRESENT_GRAVITY_MIN_BIT_EXT;// VkPresentGravityFlagBitsEXT组合值位掩码，指明surface支持的Y轴的pixel gravity，为0表示Y轴不支持pixel gravity
					surfacePresentScalingCapabilitiesEXT.supportedPresentScaling = VK_PRESENT_SCALING_ONE_TO_ONE_BIT_EXT;/*为VkPresentScalingFlagBitsEXT组合值位掩码，指明surface支持的缩放操作,或者为0表示不支持缩放
					VkPresentScalingFlagBitsEXT:
					VK_PRESENT_SCALING_ONE_TO_ONE_BIT_EXT:   指明不进行缩放操作，所有swapchain中的所有像素会一一对应到surface中的所有像素，映射根据选定的presentation gravity进行
					VK_PRESENT_SCALING_ASPECT_RATIO_STRETCH_BIT_EXT:  指定swapchain图像将被缩小或放大，使产生的宽度或高度中至少一个等于相应的surface尺寸，并且另一个产生的尺寸小于或等于相应的surface尺寸，生成的图像与原始swapchain图像的长宽比相同
					VK_PRESENT_SCALING_STRETCH_BIT_EXT:  指定swapchain图像将被缩小或放大到surface的大小
					*/


					//VkSurfacePresentModeCompatibilityEXT    查询和给定present mode显示模式兼容的一组present mode
					VkSurfacePresentModeCompatibilityEXT& surfacePresentModeCompatibilityEXT = surfaceCapabilities2KHREXT.surfacePresentModeCompatibilityEXT;
					surfacePresentModeCompatibilityEXT.presentModeCount = 1;//为查询到的和给定present mode兼容的显示模式的数量
					VkPresentModeKHR presentMode = VK_PRESENT_MODE_FIFO_KHR;
					surfacePresentModeCompatibilityEXT.pPresentModes = &presentMode;//一组VkPresentModeKHR数组指针，指明个给定present mode兼容的一组present mode


					//VkSharedPresentSurfaceCapabilitiesKHR
					VkSharedPresentSurfaceCapabilitiesKHR& sharedPresentSurfaceCapabilitiesKHR = surfaceCapabilities2KHREXT.sharedPresentSurfaceCapabilitiesKHR;
					sharedPresentSurfaceCapabilitiesKHR.sharedPresentSupportedUsageFlags = VK_IMAGE_ASPECT_COLOR_BIT;// VkImageUsageFlagBits组合值位掩码，指明在设备支持surface的以VkPresentModeKHR为 VK_PRESENT_MODE_SHARED_DEMAND_REFRESH_KHR 或者 VK_PRESENT_MODE_SHARED_CONTINUOUS_REFRESH_KHR创建的swapchain之间的共享image的用法，至少包含VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT

					//VkDisplayNativeHdrSurfaceCapabilitiesAMD
					VkDisplayNativeHdrSurfaceCapabilitiesAMD& displayNativeHdrSurfaceCapabilitiesAMD = surfaceCapabilities2KHREXT.displayNativeHdrSurfaceCapabilitiesAMD;
					displayNativeHdrSurfaceCapabilitiesAMD.localDimmingSupport = VK_TRUE;//指明surface是否支持local dimming，如果为VK_TRUE，则创建swapchain的时候就可以指定一个VkSwapchainDisplayNativeHdrCreateInfoAMD显示开关local dimming，或者由 vkSetLocalDimmingAMD设置


					VkSurfaceCapabilitiesFullScreenExclusiveEXT& surfaceCapabilitiesFullScreenExclusiveEXT = surfaceCapabilities2KHREXT.surfaceCapabilitiesFullScreenExclusiveEXT;
					surfaceCapabilitiesFullScreenExclusiveEXT.fullScreenExclusiveSupported = VK_TRUE;//描述surface时候能够使用独有全屏访问，如果不支持则不能以VK_FULL_SCREEN_EXCLUSIVE_APPLICATION_CONTROLLED_EXT创建swapchain

					VkSurfaceCapabilitiesPresentBarrierNV& surfaceCapabilitiesPresentBarrierNV = surfaceCapabilities2KHREXT.surfaceCapabilitiesPresentBarrierNV;
					surfaceCapabilitiesPresentBarrierNV.presentBarrierSupported = VK_TRUE;//描述surface是否可以使用present barrier 特性

				}

				surfaceCapabilities2KHR.pNext = &surfaceCapabilities2KHREXT.displayNativeHdrSurfaceCapabilitiesAMD;

				vkGetPhysicalDeviceSurfaceCapabilities2KHR(physicalDevice, &physicalDeviceSurfaceInfo2KHR/*pSurfaceInfo*/, &surfaceCapabilities2KHR/*pSurfaceCapabilities*/);//假设返回了正确结果
				/*
				vkGetPhysicalDeviceSurfaceCapabilities2KHR有效用法:
				1.如果VK_GOOGLE_surfaceless_query 拓展没有开启，则pSurfaceInfo->surface 必须是有效的VkSurfaceKHR句柄
				2.如果pSurfaceInfo->surface不为VK_NULL_HANDLE，pSurfaceInfo->surface必须由physicalDevice支持，见vkGetPhysicalDeviceSurfaceSupportKHR
				3.如果pSurfaceCapabilities->pNext中不包含VkSurfaceCapabilitiesFullScreenExclusiveEXT，则pSurfaceInfo->pNext中必须包含VkSurfaceFullScreenExclusiveWin32InfoEXT
				4.如果pSurfaceCapabilities->pNext中包含VkSurfacePresentModeCompatibilityEXT，则（1）pSurfaceInfo->pNext中必须包含VkSurfacePresentModeEXT
																							   （2）pSurfaceInfo->surface 必须是有效的VkSurfaceKHR句柄
				5.如果pSurfaceCapabilities->pNext中包含VkSurfacePresentScalingCapabilitiesEXT，则（1）pSurfaceInfo->pNext中必须包含VkSurfacePresentModeEXT
																								 （2）pSurfaceInfo->surface 必须是有效的VkSurfaceKHR句柄


				*/

				surfaceCapabilities2KHR.surfaceCapabilities = surfaceCapabilitiesKHR;//VkSurfaceCapabilitiesKHR类型，前面已经描述过这里不再复述




			}


			//查询创建swapchain时需要的surface的基本能力
			VkSurfaceCapabilities2EXT surfaceCapabilities2EXT{};
			surfaceCapabilities2EXT.sType = VK_STRUCTURE_TYPE_SURFACE_CAPABILITIES_2_EXT;
			surfaceCapabilities2EXT.pNext = nullptr;
			vkGetPhysicalDeviceSurfaceCapabilities2EXT(physicalDevice, surfaceKHR, &surfaceCapabilities2EXT);//假设成功返回了结果
			surfaceCapabilities2EXT.minImageCount = 1;//为设备支持的对surface创建的swapchian的最小的image的数量，至少为1
			surfaceCapabilities2EXT.maxImageCount = 1;//为设备支持的对surface创建的swapchian的最大的image的数量，可以为0或者大于等于minImageCount，0意味着没有限制，只受限于内存
			surfaceCapabilities2EXT.currentExtent = VkExtent2D{ .width = 1,.height = 1 };//为surface当前的宽高，如果是特殊值(0xFFFFFFFF, 0xFFFFFFFF)则指明该surface的宽高屈居于创建的swapchain的宽高
			surfaceCapabilities2EXT.minImageExtent = VkExtent2D{ .width = 1,.height = 1 };//为设备支持的对surface创建的swapchian的最小宽高，小于等于currentExtent中对应的值，除非currentExtent为特殊值
			surfaceCapabilities2EXT.maxImageExtent = VkExtent2D{ .width = 1,.height = 1 };//为设备支持的对surface创建的swapchian的最大宽高，大于等于minImageExtent中对应的值，大于等于currentExtent中对应的值，除非currentExtent为特殊值
			surfaceCapabilities2EXT.maxImageArrayLayers = 1;//为设备支持的对surface创建的swapchian中的image所能含有的最大的arrayLayer数量，至少为1
			surfaceCapabilities2EXT.supportedTransforms = VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR;//VkSurfaceTransformFlagBitsKHR 组合值位掩码，指明设备支持的对surface能够支持的presentation transforms
			surfaceCapabilities2EXT.currentTransform = VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR;//为一个VkSurfaceTransformFlagBitsKHR值，指明surface当前的presentation transforms
			surfaceCapabilities2EXT.supportedCompositeAlpha = VK_COMPOSITE_ALPHA_INHERIT_BIT_KHR;// VkCompositeAlphaFlagBitsKHR 组合值位掩码，表示显示支持的alpha混合模式，至少将设置一个位。不透明混合可以通过使用任何没有alpha组件的图像格式，或者通过确保可呈现图像中的所有像素都有1.0的alpha值来实现。
			surfaceCapabilities2EXT.supportedUsageFlags = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;//VkImageUsageFlagBits组合值位掩码，指明设备支持的对surface以  VkPresentModeKHR为 VK_PRESENT_MODE_IMMEDIATE_KHR, VK_PRESENT_MODE_MAILBOX_KHR, VK_PRESENT_MODE_FIFO_KHR 或者VK_PRESENT_MODE_FIFO_RELAXED_KHR创建的swapchian中的image的用法，必须包含VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT
			surfaceCapabilities2EXT.supportedSurfaceCounters = 0;// VkSurfaceCounterFlagBitsEXT组合值位掩码指明支持的surface计数器类型，除非surface是一个display surface否则不能包含 VK_SURFACE_COUNTER_VBLANK_BIT_EXT,VK_SURFACE_COUNTER_VBLANK_BIT_EXT指明每次在与曲面相关联的显示器上出现垂直消隐周期时递增一次的计数器


		}


		// Surface Format Support  参见p3111
		{
			
			//查询surface的swapchain支持的format以及color space对
			uint32_t surfaceFormatCount = 0;
			std::vector<VkSurfaceFormatKHR> surfaceFormatKHRs{};
			vkGetPhysicalDeviceSurfaceFormatsKHR(physicalDevice, surfaceKHR, &surfaceFormatCount, nullptr);
			/*
			vkGetPhysicalDeviceSurfaceFormatsKHR有效用法:
			1.如果 VK_GOOGLE_surfaceless_query 拓展未开启，则surface必须是有效的VkSurfaceKHR句柄
			2.如果surface不为VK_NULL_HANDLE，则surface必须被physicalDevice支持，参见vkGetPhysicalDeviceSurfaceSupportKHR或者一个对等的平台机制来判断
			*/
			surfaceFormatKHRs.resize(surfaceFormatCount);
			vkGetPhysicalDeviceSurfaceFormatsKHR(physicalDevice, surfaceKHR, &surfaceFormatCount, surfaceFormatKHRs.data());//假设成功返回了一个元素,
			VkSurfaceFormatKHR& surfaceFormatKHR = surfaceFormatKHRs[0];
			surfaceFormatKHR.format = VK_FORMAT_R8G8B8_SRGB;//为指定surface兼容的format，指明pixel的编码方式
			surfaceFormatKHR.colorSpace = VK_COLORSPACE_SRGB_NONLINEAR_KHR;/*为指定surface兼容的 VkColorSpaceKHR，定义如何解释pixel的编码值
			VkColorSpaceKHR:

			VK_COLOR_SPACE_SRGB_NONLINEAR_KHR:  指明支持 sRGB color space
			VK_COLOR_SPACE_DISPLAY_P3_NONLINEAR_EXT:  指明支持 Display-P3 color space,使用sRGB-like EOTF进行显示
			VK_COLOR_SPACE_EXTENDED_SRGB_LINEAR_EXT:  指明支持 拓展 sRGB color space,使用linear EOTF进行显示
			VK_COLOR_SPACE_EXTENDED_SRGB_NONLINEAR_EXT:  指明支持 拓展 sRGB color space,使用sRGB EOTF进行显示
			VK_COLOR_SPACE_DISPLAY_P3_LINEAR_EXT:  指明支持 Display-P3 color space,使用linear EOTF进行显示
			VK_COLOR_SPACE_DCI_P3_NONLINEAR_EXT:  指明支持 DCI-P3 color space,使用DCI-P3 EOTF进行显示，该图像中的值会被解释为XYZ编码的颜色数据
			VK_COLOR_SPACE_BT709_LINEAR_EXT:  指明支持 BT709 color space,使用linear EOTF进行显示
			VK_COLOR_SPACE_BT709_NONLINEAR_EXT:  指明支持 BT709 color space,使用SMPTE 170M EOTF进行显示
			VK_COLOR_SPACE_BT2020_LINEAR_EXT:  指明支持 BT2020 color space,使用linear EOTF进行显示
			VK_COLOR_SPACE_HDR10_ST2084_EXT:  指明支持 HDR10 (BT2020 color) color space,使用SMPTE ST2084 Perceptual Quantizer (PQ) EOTF进行显示
			VK_COLOR_SPACE_DOLBYVISION_EXT:  指明支持 Dolby Vision (BT2020 color space) color space，proprietary encoding,使用SMPTE ST2084 EOTF进行显示
			VK_COLOR_SPACE_HDR10_HLG_EXT:  指明支持 HDR10 (BT2020 color space) color space,使用Hybrid Log Gamma (HLG) EOTF进行显示
			VK_COLOR_SPACE_ADOBERGB_LINEAR_EXT:  指明支持 AdobeRGB color space,使用linear EOTF进行显示
			VK_COLOR_SPACE_ADOBERGB_NONLINEAR_EXT:  指明支持 AdobeRGB color space,使用Gamma 2.2 EOTF进行显示
			VK_COLOR_SPACE_PASS_THROUGH_EXT:  指明颜色分量就按照“原来”那样使用，这允许应用不在此处进行解释颜色值，一般用在传统线性或者非gamma颜色转换函数中会使用这个
			VK_COLOR_SPACE_DISPLAY_NATIVE_AMD:  指明支持显示器本地的color space，这符合AMD的支持FreeSync2 standard的显示器的color space期望，
			*/



			//查询surface的swapchain支持的format元组
VkPhysicalDeviceSurfaceInfo2KHR physicalDeviceSurfaceInfo2KHR{};
physicalDeviceSurfaceInfo2KHR.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SURFACE_INFO_2_KHR;
physicalDeviceSurfaceInfo2KHR.pNext = nullptr;
physicalDeviceSurfaceInfo2KHR.surface = surfaceKHR;//

uint32_t surfaceFormat2Count = 0;
std::vector<VkSurfaceFormat2KHR> surfaceFormat2KHRs{};
vkGetPhysicalDeviceSurfaceFormats2KHR(physicalDevice, &physicalDeviceSurfaceInfo2KHR, &surfaceFormat2Count, nullptr);
/*
vkGetPhysicalDeviceSurfaceFormats2KHR有效用法:
1.如果 VK_GOOGLE_surfaceless_query 拓展未开启，则surface必须是有效的VkSurfaceKHR句柄
2.如果surface不为VK_NULL_HANDLE，则surface必须被physicalDevice支持，参见vkGetPhysicalDeviceSurfaceSupportKHR或者一个对等的平台机制来判断
*/
surfaceFormat2KHRs.resize(surfaceFormat2Count);
vkGetPhysicalDeviceSurfaceFormats2KHR(physicalDevice, &physicalDeviceSurfaceInfo2KHR, &surfaceFormat2Count, surfaceFormat2KHRs.data());//假设成功返回了一个元素
VkSurfaceFormat2KHR& surfaceFormat2KHR = surfaceFormat2KHRs[0];
surfaceFormat2KHR.sType = VK_STRUCTURE_TYPE_SURFACE_FORMAT_2_KHR;
VkImageCompressionPropertiesEXT imageCompressionPropertiesEXT{};
{
	imageCompressionPropertiesEXT.sType = VK_STRUCTURE_TYPE_IMAGE_COMPRESSION_PROPERTIES_EXT;
	imageCompressionPropertiesEXT.pNext = nullptr;
	imageCompressionPropertiesEXT.imageCompressionFlags = 0;
	imageCompressionPropertiesEXT.imageCompressionFixedRateFlags = 0;
}
surfaceFormat2KHR.pNext = &imageCompressionPropertiesEXT;//如果imageCompressionControlSwapchain 特性开启，可以包含一个VkImageCompressionPropertiesEXT，返回其压缩属性
surfaceFormat2KHR.surfaceFormat = surfaceFormatKHRs[0];//VkSurfaceFormatKHR类型，前面已经描述过这里不再复述


		}


		//Surface Presentation Mode Support 参见p3119
		{
			//查询surface支持的present mode
			uint32_t presentModeCount = 0;
			std::vector<VkPresentModeKHR> presentModeKHRs{};
			vkGetPhysicalDeviceSurfacePresentModesKHR(physicalDevice, surfaceKHR, &presentModeCount, nullptr);
			/*
			vkGetPhysicalDeviceSurfacePresentModesKHR有效用法:
			1.如果 VK_GOOGLE_surfaceless_query 拓展未开启，则surface必须是有效的VkSurfaceKHR句柄
			2.如果surface不为VK_NULL_HANDLE，则surface必须被physicalDevice支持，参见vkGetPhysicalDeviceSurfaceSupportKHR或者一个对等的平台机制来判断
			*/
			presentModeKHRs.resize(presentModeCount);
			vkGetPhysicalDeviceSurfacePresentModesKHR(physicalDevice, surfaceKHR, &presentModeCount, presentModeKHRs.data());//假设成功返回了一个元素
			VkPresentModeKHR& presentModeKHR = presentModeKHRs[0] = VK_PRESENT_MODE_FIFO_KHR;
			/*
			VkPresentModeKHR:
			VK_PRESENT_MODE_IMMEDIATE_KHR:  指定显示不等待垂直空白周期（vertical blanking period）来更新当前图像，这意味着此模式可能会导致可见的撕裂。显示图像不需要请求进行内部排队，因为请求会立即应用
			VK_PRESENT_MODE_MAILBOX_KHR:  指定显示等待下一个垂直空白周期（vertical blanking period）来更新当前图像。不会观察到撕裂。内部单条目队列用于保存挂起的图像显示请求。如果在收到新的表示请求时队列已满，则新请求将替换现有条目，并且与先前条目相关联的任何图像都可供应用程序重用。队列非空时，会在每个垂直空白周期（vertical blanking period）中删除一个请求并进行处理
			VK_PRESENT_MODE_FIFO_KHR:  指定显示等待下一个垂直空白周期（vertical blanking period）来更新当前图像。不会观察到撕裂。内部队列用于保存正在挂起的图像显示请求。新请求被附加到队列的末尾，在队列非空时，会在每个垂直空白周期（vertical blanking period）中删除一个请求并进行处理。这是presentMode中必须需要支持的唯一个模式。
			VK_PRESENT_MODE_FIFO_RELAXED_KHR:  指定显示通常会等待下一个垂直空白周期（vertical blanking period）以更新当前图像。如果自当前图像的上次更新以来，垂直空白周期（vertical blanking period）已经过去，那么显示不会等待另一个垂垂直空白周期（vertical blanking period），这意味着在这种情况下，这种模式可能导致可见的撕裂。这种模式对于减少 visual stutter很有用，该应用程序将在下一个垂垂直空白周期（vertical blanking period）之前呈现新图像，但偶尔可能会延迟，并在下一个垂垂直空白周期（vertical blanking period）之后呈现新图像。内部队列用于保存已挂起的图像显示请求。新请求被附加到队列的末尾，在队列非空时，会在每个垂直空白周期（vertical blanking period）中或者之后删除一个请求并进行处理
			VK_PRESENT_MODE_SHARED_DEMAND_REFRESH_KHR:  指定显示和应用程序可以并发访问单个图像，这被称为共享的可显示图像。显示只需要在收到新的图像显示请求后更新当前图像。因此，每当需要更新时，应用程序必须提出图像显示请求。然而，显示可以在任何点更新当前的图像，这意味着这种模式可能导致可见的撕裂
			VK_PRESENT_MODE_SHARED_CONTINUOUS_REFRESH_KHR:  指定显示和应用程序可以并发访问单个图像，这被称为共享的可显示图像。显示在循环中定期更新当前图像。应用程序只需要发出一个初始显示请求，之后显示更新而不需要任何后续的显示请求就能够定期更新图像。应用程序可以通过发出显示请求来指示图像内容已经更新，但这并不能保证何时会更新它的时间。如果没有正确定时渲染图像，这种模式可能会导致可见撕裂。
			*/

			//选择其他创建swapchain的固定参数来查询surface支持的present mode
			VkPhysicalDeviceSurfaceInfo2KHR physicalDeviceSurfaceInfo2KHR{};//该结构体前面已经描述过了，这里不再复述
			physicalDeviceSurfaceInfo2KHR.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SURFACE_INFO_2_KHR;
			physicalDeviceSurfaceInfo2KHR.pNext = nullptr;
			physicalDeviceSurfaceInfo2KHR.surface = surfaceKHR;//指明surface
			vkGetPhysicalDeviceSurfacePresentModes2EXT(physicalDevice, &physicalDeviceSurfaceInfo2KHR, &presentModeCount, nullptr);
			/*
			vkGetPhysicalDeviceSurfacePresentModes2EXT有效用法:
			1.如果 VK_GOOGLE_surfaceless_query 拓展未开启，则surface必须是有效的VkSurfaceKHR句柄
			2.如果surface不为VK_NULL_HANDLE，则surface必须被physicalDevice支持，参见vkGetPhysicalDeviceSurfaceSupportKHR或者一个对等的平台机制来判断
			*/
			presentModeKHRs.resize(presentModeCount);
			vkGetPhysicalDeviceSurfacePresentModes2EXT(physicalDevice, &physicalDeviceSurfaceInfo2KHR, &presentModeCount, presentModeKHRs.data());//假设成功返回了一个元素


			/*
			显示模式和显示图像的用法对应参考表:
			Presentation mode									Image usage flags
			VK_PRESENT_MODE_IMMEDIATE_KHR					VkSurfaceCapabilitiesKHR::supportedUsageFlags
			VK_PRESENT_MODE_MAILBOX_KHR						VkSurfaceCapabilitiesKHR::supportedUsageFlags
			VK_PRESENT_MODE_FIFO_KHR						VkSurfaceCapabilitiesKHR::supportedUsageFlags
			VK_PRESENT_MODE_FIFO_RELAXED_KHR				VkSurfaceCapabilitiesKHR::supportedUsageFlags
			VK_PRESENT_MODE_SHARED_DEMAND_REFRESH_KHR		VkSharedPresentSurfaceCapabilitiesKHR::sharedPresentSupportedUsageFlags
			VK_PRESENT_MODE_SHARED_CONTINUOUS_REFRESH_KHR   VkSharedPresentSurfaceCapabilitiesKHR::sharedPresentSupportedUsageFlags

			*/
		}

	}


	//Full Screen Exclusive Control  参见p3123
	{
		/*
		要显示以fullScreenExclusive 设置为VK_FULL_SCREEN_EXCLUSIVE_APPLICATION_CONTROLLED_EXT 创建的swapchain必须要获取或者释放全屏独家访问权exclusive full-screen access
		*/

		//获取exclusive full-screen access
		vkAcquireFullScreenExclusiveModeEXT(device, VkSwapchainKHR{/*假设这是一个有效的VkSwapchainKHR*/ }/*swapchain,要获取exclusive full-screen access的swapchain*/);
		/*
		vkAcquireFullScreenExclusiveModeEXT有效用法:
		1.swapchain 不能处于retired state
		2.swapchain 必须是以含有fullScreenExclusive设置为VK_FULL_SCREEN_EXCLUSIVE_APPLICATION_CONTROLLED_EXT的 VkSurfaceFullScreenExclusiveInfoEXT 创建的
		3.swapchain 当前不能拥有exclusive full-screen access
		*/

		//释放exclusive full-screen access
		vkReleaseFullScreenExclusiveModeEXT(device, VkSwapchainKHR{/*假设这是一个有效的VkSwapchainKHR*/ }/*swapchain,要释放exclusive full-screen access的swapchain*/);
		/*
		vkReleaseFullScreenExclusiveModeEXT有效用法:
		1.swapchain 不能处于retired state
		2.swapchain 必须是以含有fullScreenExclusive设置为VK_FULL_SCREEN_EXCLUSIVE_APPLICATION_CONTROLLED_EXT的 VkSurfaceFullScreenExclusiveInfoEXT 创建的
		*/
	}


	//Device Group Queries  参见p3126
	{
		/*
		一个表示多个物理设备的逻辑设备可以将image显示到多个物理设备上，或者是从多个物理设备上绑定显示image
		*/

		//查询多物理设备显示相关能力
		VkDeviceGroupPresentCapabilitiesKHR deviceGroupPresentCapabilitiesKHR{};
		deviceGroupPresentCapabilitiesKHR.sType = VK_STRUCTURE_TYPE_DEVICE_GROUP_PRESENT_CAPABILITIES_KHR;
		deviceGroupPresentCapabilitiesKHR.pNext = nullptr;

		vkGetDeviceGroupPresentCapabilitiesKHR(device, &deviceGroupPresentCapabilitiesKHR);//假设成功返回了属性

		deviceGroupPresentCapabilitiesKHR.presentMask;///presentMask为VK_MAX_DEVICE_GROUP_SIZE 个uint32_t值数组，如果元素值非0代表这个元素对应的物理设备可以显示--有显示引擎，如果这个元素的某个bit为1代表这个元素支持该bit对应的物理设备的图像的显示，该元素至少要设备对应本元素物理设备的bit为1
		for (uint32_t i = 0; i < VK_MAX_DEVICE_GROUP_SIZE; i++)
		{
			deviceGroupPresentCapabilitiesKHR.presentMask[i] = 0x00000001;
		}
		deviceGroupPresentCapabilitiesKHR.modes = VK_DEVICE_GROUP_PRESENT_MODE_LOCAL_BIT_KHR;//VkDeviceGroupPresentModeFlagBitsKHR 组合值位掩码，指明支持哪个设备组的显示模式，永远含有 VK_DEVICE_GROUP_PRESENT_MODE_LOCAL_BIT_KHR
		/*
		VkDeviceGroupPresentModeFlagBitsKHR:
		VK_DEVICE_GROUP_PRESENT_MODE_LOCAL_BIT_KHR:  指明任何含有显示引擎的物理设备能够显示其自有的swapchain images
		VK_DEVICE_GROUP_PRESENT_MODE_REMOTE_BIT_KHR:  指明任何含有显示引擎的物理设备能够显示来自其presentMask中指定的任何其他物理设备的swapchain images
		VK_DEVICE_GROUP_PRESENT_MODE_SUM_BIT_KHR:  指明任何含有显示引擎的物理设备能够显示来自其presentMask中指定的任何其他物理设备的swapchain images总和
		VK_DEVICE_GROUP_PRESENT_MODE_LOCAL_MULTI_DEVICE_BIT_KHR:  指明多个物理设备含有一个显示引擎的各个物理设备能够显示其自有的swapchain images
		*/

		VkSurfaceKHR surface{/*假设这是一个有效的VkSurfaceKHR*/ };

		//有些surface可能不支持所有的设备组显示模式，所以查询某个surface支持的设备组显示模式
		VkDeviceGroupPresentModeFlagsKHR surfaceDeviceGroupPresentModeFlagsKHR{};
		vkGetDeviceGroupSurfacePresentModesKHR(device, surface/*surface ,surface必须被device中的所有physical device支持，参见vkGetPhysicalDeviceSurfaceSupportKHR或者一个对等的平台机制来判断*/, & surfaceDeviceGroupPresentModeFlagsKHR);


		//有些surface可能不支持所有的设备组显示模式，所以指定一些创建swapchain需要的固有参数查询某个surface支持的设备组显示模式
		VkPhysicalDeviceSurfaceInfo2KHR physicalDeviceSurfaceInfo2KHR{};//该结构体前面已经描述过了，这里不再复述
		physicalDeviceSurfaceInfo2KHR.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SURFACE_INFO_2_KHR;
		physicalDeviceSurfaceInfo2KHR.pNext = nullptr;
		physicalDeviceSurfaceInfo2KHR.surface = surface;//surface必须被device中的所有physical device支持，参见vkGetPhysicalDeviceSurfaceSupportKHR或者一个对等的平台机制来判断

		vkGetDeviceGroupSurfacePresentModes2EXT(device, &physicalDeviceSurfaceInfo2KHR, & surfaceDeviceGroupPresentModeFlagsKHR);


		//当使用VK_DEVICE_GROUP_PRESENT_MODE_LOCAL_MULTI_DEVICE_BIT_KHR时，一个surface上有多个物理设备来进行显示，查询每个物理设备所对应的surface上的一组显示区域rectangle
		uint32_t physicalDeviceRenderRegionCount = 0;
		std::vector<VkRect2D> physicalDeviceRenderRegions{};
		vkGetPhysicalDevicePresentRectanglesKHR(physicalDevice, surface/*surface,必须是有效的句柄，必须被physical device支持，参见vkGetPhysicalDeviceSurfaceSupportKHR或者一个对等的平台机制来判断*/, &physicalDeviceRenderRegionCount, nullptr);
		physicalDeviceRenderRegions.resize(physicalDeviceRenderRegionCount);
		vkGetPhysicalDevicePresentRectanglesKHR(physicalDevice, surface/*surface,必须是有效的句柄，必须被physical device支持，参见vkGetPhysicalDeviceSurfaceSupportKHR或者一个对等的平台机制来判断*/, &physicalDeviceRenderRegionCount, physicalDeviceRenderRegions.data());



	}

	// Display Timing Queries 参见p3132
	{
		//和VK_GOOGLE_display_timing 拓展相关

		VkSwapchainKHR swapchain{/*假设这是一个有效的VkSwapchainKHR*/ };

		//查询显示引擎一个刷新循环（RC）的持续时间
		VkRefreshCycleDurationGOOGLE refreshCycleDurationGOOGLE{};
		vkGetRefreshCycleDurationGOOGLE(device, swapchain, & refreshCycleDurationGOOGLE);//假设正确返回了结果
		refreshCycleDurationGOOGLE.refreshDuration = 1;//为一个刷新循环的开始到下一个刷新循环的开始之间的纳秒时间间隔


		//异步查询显示引擎，以获取关于给定swapchain的之前最新的一次或多次显示的相关的耗时信息
		uint32_t swapchainPresentTimingInfoCount = 0;
		std::vector<VkPastPresentationTimingGOOGLE> pastPresentationTimingGOOGLEs{};
		
		vkGetPastPresentationTimingGOOGLE(device, swapchain, &swapchainPresentTimingInfoCount, nullptr);
		pastPresentationTimingGOOGLEs.resize(swapchainPresentTimingInfoCount);
		vkGetPastPresentationTimingGOOGLE(device, swapchain, &swapchainPresentTimingInfoCount, pastPresentationTimingGOOGLEs.data());//假设成功返回了至少一个元素
		
		//该结构体中的值具体要怎么解释根据显示模式 VK_PRESENT_MODE_*** 的不同有所区别，具体见3137
		VkPastPresentationTimingGOOGLE &pastPresentationTimingGOOGLE = pastPresentationTimingGOOGLEs[0];//时间单位为纳秒
		pastPresentationTimingGOOGLE.presentID  = 0;//为应用通过 VkPresentTimeGOOGLE::presentID为上一个 vkQueuePresentKHR命令提供的一个值，可以唯一确定一次 vkQueuePresentKHR命令
		pastPresentationTimingGOOGLE.desiredPresentTime = 1;//为应用通过 VkPresentTimeGOOGLE::desiredPresentTime为上一个 vkQueuePresentKHR命令提供的一个值，如果该值不为0，可以指明image不能在早于该值表示的时间之前进行显示
		pastPresentationTimingGOOGLE.actualPresentTime = 1;//为swapchain的image实际显示的时间
		pastPresentationTimingGOOGLE.earliestPresentTime = 1;//为swapchain中image可以显示的一个最早时间点，如果应用要求不早于 VkPresentTimeGOOGLE::desiredPresentTime进行image的显示的话该值可能和actualPresentTime不同
		pastPresentationTimingGOOGLE.presentMargin = 1;//指明了vkQueuePresentKHR要多早被处理和多快被处理的比较，在earliestPresentTime也有体现


	}


	// Present Wait  参见p3138   和 VK_KHR_present_wait 拓展相关，简单将就是传递 VkPresentIdKHR.presentId给vkQueuePresentKHR，让后续的vkWaitForPresentKHR进行阻塞
	

	// WSI Swapchain  参见p3138
	{
		/*
		swapchain是一组可以显示到surface上的images的抽象概念，这些images由显示引擎所有,可以在vulkan中共享访问。要在vulkan中使用这些图像，需要调用vkAcquireNextImageKHR获取该image，然后进行相关操作，布局转换，绘制等等，然后调用vkQueuePresentKHR将该图像显示并且释放该image，也可以通过vkReleaseSwapchainImagesEXT来释放image，这个操作会跳过显示步骤且需要image不在device上使用。
		
		如果swapchain创建的 presentMode为 VK_PRESENT_MODE_SHARED_DEMAND_REFRESH_KHR 或者 VK_PRESENT_MODE_SHARED_CONTINUOUS_REFRESH_KHR，则该swapchain中只有一个共享的image，vulkan 应用和显示引擎需要协同进行访问。具体见p3139


		*/

		VkSwapchainKHR swapchainKHR{/*假设这是一个有效的VkSwapchainKHR*/};
		

		//查询渲染时swapchain中的共享的显示image的状态   ，主要可以判断这个swapchain是否还可用，参见p3141 对接口结果的描述
		VkResult result = vkGetSwapchainStatusKHR(device, swapchainKHR);


		struct SwapchainCreateInfoKHREXT {
			VkDeviceGroupSwapchainCreateInfoKHR deviceGroupSwapchainCreateInfoKHR{};
			VkImageCompressionControlEXT imageCompressionControlEXT{};
			VkImageFormatListCreateInfo imageFormatListCreateInfo{};
			VkSurfaceFullScreenExclusiveInfoEXT surfaceFullScreenExclusiveInfoEXT{};
			VkSurfaceFullScreenExclusiveWin32InfoEXT surfaceFullScreenExclusiveWin32InfoEXT{};
			VkSwapchainCounterCreateInfoEXT swapchainCounterCreateInfoEXT{ };
			VkSwapchainDisplayNativeHdrCreateInfoAMD swapchainDisplayNativeHdrCreateInfoAMD{};
			VkSwapchainLatencyCreateInfoNV swapchainLatencyCreateInfoNV{};
			VkSwapchainPresentBarrierCreateInfoNV swapchainPresentBarrierCreateInfoNV{};
			VkSwapchainPresentModesCreateInfoEXT swapchainPresentModesCreateInfoEXT{};
			VkSwapchainPresentScalingCreateInfoEXT swapchainPresentScalingCreateInfoEXT{};
			SwapchainCreateInfoKHREXT() {
				Init();
			}
			void Init() {
				deviceGroupSwapchainCreateInfoKHR.sType = VK_STRUCTURE_TYPE_DEVICE_GROUP_SWAPCHAIN_CREATE_INFO_KHR;
				deviceGroupSwapchainCreateInfoKHR.pNext = nullptr;
				imageCompressionControlEXT.sType = VK_STRUCTURE_TYPE_IMAGE_COMPRESSION_CONTROL_EXT;
				imageCompressionControlEXT.pNext = nullptr;
				imageFormatListCreateInfo.sType = VK_STRUCTURE_TYPE_IMAGE_FORMAT_LIST_CREATE_INFO;
				imageFormatListCreateInfo.pNext = nullptr;
				surfaceFullScreenExclusiveInfoEXT.sType = VK_STRUCTURE_TYPE_SURFACE_FULL_SCREEN_EXCLUSIVE_INFO_EXT;
				surfaceFullScreenExclusiveInfoEXT.pNext = &surfaceFullScreenExclusiveWin32InfoEXT;
				surfaceFullScreenExclusiveWin32InfoEXT.sType = VK_STRUCTURE_TYPE_SURFACE_FULL_SCREEN_EXCLUSIVE_WIN32_INFO_EXT;
				surfaceFullScreenExclusiveWin32InfoEXT.pNext = nullptr;
				swapchainCounterCreateInfoEXT.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_COUNTER_CREATE_INFO_EXT;
				swapchainCounterCreateInfoEXT.pNext = nullptr;
				swapchainDisplayNativeHdrCreateInfoAMD.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_DISPLAY_NATIVE_HDR_CREATE_INFO_AMD;
				swapchainDisplayNativeHdrCreateInfoAMD.pNext = nullptr;
				swapchainLatencyCreateInfoNV.sType = VK_STRUCTURE_TYPE_MAX_ENUM;//没有定义所以设置为非法值
				swapchainLatencyCreateInfoNV.pNext = nullptr;
				swapchainPresentBarrierCreateInfoNV.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_PRESENT_BARRIER_CREATE_INFO_NV;
				swapchainPresentBarrierCreateInfoNV.pNext = nullptr;
				swapchainPresentModesCreateInfoEXT.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_PRESENT_MODES_CREATE_INFO_EXT;
				swapchainPresentModesCreateInfoEXT.pNext = nullptr;
				swapchainPresentScalingCreateInfoEXT.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_PRESENT_SCALING_CREATE_INFO_EXT;
				swapchainPresentScalingCreateInfoEXT.pNext = nullptr;

			}

		};


		VkSwapchainCreateInfoKHR swapchainCreateInfoKHR{};
		swapchainCreateInfoKHR.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
		SwapchainCreateInfoKHREXT swapchainCreateInfoKHREXT{};
		//VkSwapchainCreateInfoKHR.pNext
		{
			//VkDeviceGroupSwapchainCreateInfoKHR 指明swapchain可以使用的一组 device group present modes ，如果不包含该结构体，则默认mode为VK_DEVICE_GROUP_PRESENT_MODE_LOCAL_BIT_KHR
			VkDeviceGroupSwapchainCreateInfoKHR& deviceGroupSwapchainCreateInfoKHR = swapchainCreateInfoKHREXT.deviceGroupSwapchainCreateInfoKHR;
			deviceGroupSwapchainCreateInfoKHR.modes = VK_DEVICE_GROUP_PRESENT_MODE_LOCAL_BIT_KHR;//指明swapchain可以使用的一组 device group present modes，其bit位指明一种device group present mode

			//VkSwapchainDisplayNativeHdrCreateInfoAMD  指明创建swapchain时特定于显示的HDR支持的额外参数，如果不包含该结构体则默认localDimmingEnable为VK_TRUE
			VkSwapchainDisplayNativeHdrCreateInfoAMD& swapchainDisplayNativeHdrCreateInfoAMD = swapchainCreateInfoKHREXT.swapchainDisplayNativeHdrCreateInfoAMD;
			swapchainDisplayNativeHdrCreateInfoAMD.localDimmingEnable = VK_TRUE;//指明对swapchain是否开启local dimming，如果支持VkDisplayNativeHdrSurfaceCapabilitiesAMD::localDimmingSupport则该值必须为VK_TRUE
			{
				//在swapchain有效期间可以设置local dimming HDR设置
				vkSetLocalDimmingAMD(device, swapchainKHR, VK_TRUE);//VkDisplayNativeHdrSurfaceCapabilitiesAMD::localDimmingSupport必须要支持
			}


			// VkSurfaceFullScreenExclusiveInfoEXT  指明应用偏好的全屏显示行为，如果不包含该结构体，则 fullScreenExclusive认为是VK_FULL_SCREEN_EXCLUSIVE_DEFAULT_EXT
			VkSurfaceFullScreenExclusiveInfoEXT& surfaceFullScreenExclusiveInfoEXT = swapchainCreateInfoKHREXT.surfaceFullScreenExclusiveInfoEXT;
			surfaceFullScreenExclusiveInfoEXT.fullScreenExclusive = VK_FULL_SCREEN_EXCLUSIVE_DEFAULT_EXT;


			//VkSwapchainCounterCreateInfoEXT  指明开启 surface counters，
			VkSwapchainCounterCreateInfoEXT &swapchainCounterCreateInfoEXT = swapchainCreateInfoKHREXT.swapchainCounterCreateInfoEXT;
			swapchainCounterCreateInfoEXT.surfaceCounters = VK_SURFACE_COUNTER_VBLANK_EXT;// VkSurfaceCounterFlagBitsEXT组合值位掩码，指明swapchain启用的surface counters，该值中的bit设置必须由surface支持，见vkGetPhysicalDeviceSurfaceCapabilities2EXT
			{
				//当显示引擎处理swapchain的第一个显示请求的是否需要的surface counters就会激活，查询激活的counter的值
				uint64_t counterValue = 0;
				vkGetSwapchainCounterEXT(device, swapchainKHR, VK_SURFACE_COUNTER_VBLANK_EXT, &counterValue);//调用该命令必须保证swapchain的一个或者多个显示命令已经被处理了

			}

			//VkImageCompressionControlEXT  指定swapchain中的image的压缩属性
			VkImageCompressionControlEXT& imageCompressionControlEXT = swapchainCreateInfoKHREXT.imageCompressionControlEXT;
			imageCompressionControlEXT.flags = 0;
			imageCompressionControlEXT.compressionControlPlaneCount = 0;
			imageCompressionControlEXT.pFixedRateFlags = VK_NULL_HANDLE;


			//VkSwapchainPresentModesCreateInfoEXT  指定swapchain使用的多种present mode
			VkSwapchainPresentModesCreateInfoEXT &swapchainPresentModesCreateInfoEXT = swapchainCreateInfoKHREXT.swapchainPresentModesCreateInfoEXT;
			swapchainPresentModesCreateInfoEXT.presentModeCount = 1;//指明提供的present mode的数量
			VkPresentModeKHR presentModeKHR = VK_PRESENT_MODE_FIFO_KHR;
			swapchainPresentModesCreateInfoEXT.pPresentModes = &presentModeKHR;//presentModeCount个present mode的数组指针,其中元素必须属于由vkGetPhysicalDeviceSurfacePresentModesKHR传入surface返回的 VkPresentModeKHR集合，且这些元素集合必须是传入VkSwapchainCreateInfoKHR::presentMode给 VkSurfacePresentModeEXT，返回的VkSurfacePresentModeCompatibilityEXT::pPresentModes的present modes的子集，VkSwapchainCreateInfoKHR::presentMode必须包含在该数组元素中


			//VkSwapchainPresentScalingCreateInfoEXT   指定swapchain和对应surface的维度不同时候的缩放行为
			VkSwapchainPresentScalingCreateInfoEXT &swapchainPresentScalingCreateInfoEXT = swapchainCreateInfoKHREXT.swapchainPresentScalingCreateInfoEXT;
			swapchainPresentScalingCreateInfoEXT.presentGravityX = VK_PRESENT_GRAVITY_MIN_BIT_EXT;//为0或者当scalingBehavior为VK_PRESENT_SCALING_ONE_TO_ONE_BIT_EXT时和surface相关的x轴向的像素的趋向
			swapchainPresentScalingCreateInfoEXT.presentGravityY = VK_PRESENT_GRAVITY_MIN_BIT_EXT;//为0或者当scalingBehavior为VK_PRESENT_SCALING_ONE_TO_ONE_BIT_EXT时和surface相关的y轴向的像素的趋向
			swapchainPresentScalingCreateInfoEXT.scalingBehavior = VK_PRESENT_SCALING_ONE_TO_ONE_BIT_EXT;//为0或者swapchain和对应surface的维度不同时候的缩放方法
			/*
			VkSwapchainPresentScalingCreateInfoEXT有效用法:
			1.如果presentGravityX为0，则presentGravityY必须为0
			2.如果presentGravityX不为0，则presentGravityY必须不为0
			3.scalingBehavior，presentGravityX以及presentGravityY只能由一个bit设置
			4.scalingBehavior 必须是一个对surface有效的 scaling method，参见传入VkSwapchainCreateInfoKHR::presentMode给VkSurfacePresentModeEXT，返回的VkSurfacePresentScalingCapabilitiesEXT::supportedPresentScaling
			5.如果swapchain以含有一个VkSwapchainPresentModesCreateInfoEXT 创建，则scalingBehavior 必须是一个对surface有效的 scaling method，参见传入VkSwapchainPresentModesCreateInfoEXT::pPresentMode的每个元素给VkSurfacePresentModeEXT，返回的VkSurfacePresentScalingCapabilitiesEXT::supportedPresentScaling
			6.presentGravityX 必须是一个对surface有效的x-axis present gravity，参见传入VkSwapchainCreateInfoKHR::presentMode给VkSurfacePresentModeEXT，返回的VkSurfacePresentScalingCapabilitiesEXT::supportedPresentGravityX	
			7.如果swapchain以含有一个VkSwapchainPresentModesCreateInfoEXT 创建，则presentGravityX 必须是一个对surface有效的 x-axis present gravity，参见传入VkSwapchainPresentModesCreateInfoEXT::pPresentMode的每个元素给VkSurfacePresentModeEXT，返回的VkSurfacePresentScalingCapabilitiesEXT::supportedPresentGravityX
			8.presentGravityY 必须是一个对surface有效的y-axis present gravity，参见传入VkSwapchainCreateInfoKHR::presentMode给VkSurfacePresentModeEXT，返回的VkSurfacePresentScalingCapabilitiesEXT::supportedPresentGravityY
			9.如果swapchain以含有一个VkSwapchainPresentModesCreateInfoEXT 创建，则presentGravityY 必须是一个对surface有效的 y-axis present gravity，参见传入VkSwapchainPresentModesCreateInfoEXT::pPresentMode的每个元素给VkSurfacePresentModeEXT，返回的VkSurfacePresentScalingCapabilitiesEXT::supportedPresentGravityY

			*/

		}
		swapchainCreateInfoKHR.pNext = &swapchainCreateInfoKHREXT.deviceGroupSwapchainCreateInfoKHR;
		swapchainCreateInfoKHR.flags = VK_SWAPCHAIN_CREATE_MUTABLE_FORMAT_BIT_KHR;/* VkSwapchainCreateFlagBitsKHR组合值位掩码，指明swapchain创建时的参数
		VkSwapchainCreateFlagBitsKHR:

		VK_SWAPCHAIN_CREATE_SPLIT_INSTANCE_BIND_REGIONS_BIT_KHR:  指明swapchain中创建的image（就和创建image时带有一个swapchian设置为当前的句柄的VkImageSwapchainCreateInfoKHR ）必须使用VK_IMAGE_CREATE_SPLIT_INSTANCE_BIND_REGIONS_BIT
		VK_SWAPCHAIN_CREATE_PROTECTED_BIT_KHR:  指明swapchain中创建的image是protected images
		VK_SWAPCHAIN_CREATE_MUTABLE_FORMAT_BIT_KHR:  指明swapchain中创建的image可以用来创建和创建swapchain时指定的format不同format的VkImageView，允许使用的format列举在VkSwapchainCreateInfoKHR.pNext中的VkImageFormatListCreateInfo，该标志也指明该swapchain创建时的图像imageUsage可以不支持imageFormat，但至少要支持允许的image view的format中的一个
		VK_SWAPCHAIN_CREATE_DEFERRED_MEMORY_ALLOCATION_BIT_EXT:  指明或许或对swapchain中的image采取推迟分配内存的操作直到该iamge的索引通过vkAcquireNextImageKHR或者vkAcquireNextImage2KHR 第一次返回
		*/
		swapchainCreateInfoKHR.surface = VkSurfaceKHR{/*假设这是一个有效的VkSurfaceKHR*/};//指明创建的swapchain的image要在哪个surface上进行显示，一旦swapchain创建成功，则该swapchain就关联上该surface
		swapchainCreateInfoKHR.minImageCount = 1;//为应用需要的最少的可显示的image的数量，实现要么至少创建这么多的可显示的image，要么直接就创建失败
		swapchainCreateInfoKHR.imageFormat = VK_FORMAT_R8G8B8A8_UINT;// VkFormat值指明创建的swapchain中image的格式
		swapchainCreateInfoKHR.imageColorSpace = VK_COLORSPACE_SRGB_NONLINEAR_KHR;// VkColorSpaceKHR值指明swapchain如何解释image中的数据
		swapchainCreateInfoKHR.imageExtent = VkExtent2D{.width = 1,.height = 1};//为swapchain中image的像素级别的大小，如果和vkGetPhysicalDeviceSurfaceCapabilitiesKHR返回的surface的currentExtent不匹配则该值的处理行为是基于平台的
		swapchainCreateInfoKHR.imageArrayLayers = 1;//为multiview/stereo surface中的view视图的个数，如果为non-stereoscopic-3D 应用，则该值为1
		swapchainCreateInfoKHR.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;// VkImageUsageFlagBits组合值位掩码描述了应用获取了swapchian的image后可能的用法
		swapchainCreateInfoKHR.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;//swapchain中的image在队列族间的共享模式
		swapchainCreateInfoKHR.queueFamilyIndexCount = 1;//为imageSharingMode 为 VK_SHARING_MODE_CONCURRENT时，可以访问swapchain中的image的队列族的数量
		uint32_t imageQueue = 0;
		swapchainCreateInfoKHR.pQueueFamilyIndices = &imageQueue;//为imageSharingMode 为 VK_SHARING_MODE_CONCURRENT时，可以访问swapchain中的image的队列族的索引值的数组指针
		swapchainCreateInfoKHR.preTransform = VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR;//VkSurfaceTransformFlagBitsKHR值描述了在image显示之间，将其内容根据显示引擎的本地坐标进行的旋转变换操作，如果该值和vkGetPhysicalDeviceSurfaceCapabilitiesKHR返回的currentTransform 不匹配，则显示引擎将会把image的内容变换操作作为是图像显示操作的一部分
		swapchainCreateInfoKHR.compositeAlpha = VK_COMPOSITE_ALPHA_INHERIT_BIT_KHR;// VkCompositeAlphaFlagBitsKHR值指明在指定系统上和其他surface混合时的alpha 混合模式
		swapchainCreateInfoKHR.presentMode = VK_PRESENT_MODE_FIFO_KHR;//为swapchain使用的显示模式，swapchain的显示模式决定了如何处理传入的当前显示请求并在内部排队
		swapchainCreateInfoKHR.clipped = VK_TRUE;//指明是否允许vulkan实现丢弃关联到surface中不可见区域的渲染操作
		swapchainCreateInfoKHR.oldSwapchain = VK_NULL_HANDLE;//为VK_NULL_HANDLE或者一个关联到surface的未处于retired状态的swapchian，提供该参数主要有助于资源重用以及应用任然可以继续显示已经从oldSwapchian中获取到的image
		/*
		VkSwapchainCreateInfoKHR有效用法:
		1.surface 必须是设备支持的，由vkGetPhysicalDeviceSurfaceSupportKHR返回的结果决定
		2.minImageCount 必须小于等于调用vkGetPhysicalDeviceSurfaceCapabilitiesKHR传入surface返回的VkSurfaceCapabilitiesKHR的maxImageCount（如果该值不为0）
		3.如果presentMode 既不是VK_PRESENT_MODE_SHARED_DEMAND_REFRESH_KHR 也不是 VK_PRESENT_MODE_SHARED_CONTINUOUS_REFRESH_KHR，则minImageCount 必须小于等于调用vkGetPhysicalDeviceSurfaceCapabilitiesKHR传入surface返回的VkSurfaceCapabilitiesKHR的maxImageCount
		4.如果presentMode 为VK_PRESENT_MODE_SHARED_DEMAND_REFRESH_KHR或者VK_PRESENT_MODE_SHARED_CONTINUOUS_REFRESH_KHR中的一个，则minImageCount 必须为1
		5.imageFormat 和imageColorSpace 必须和调用vkGetPhysicalDeviceSurfaceFormatsKHR传入surface返回的VkSurfaceFormatKHR中的format以及colorSpace 一一对应匹配
		6.如果pNext中不包含VkSwapchainPresentScalingCreateInfoEXT，或者包含一个scalingBehavior为0的VkSwapchainPresentScalingCreateInfoEXT，则imageExtent的范围必须包含在[minImageExtent,maxImageExtent]之间，其中minImageExtent和maxImageExtent为调用vkGetPhysicalDeviceSurfaceCapabilitiesKHR传入surface返回的VkSurfaceCapabilitiesKHR中的成员
		7.如果pNext中包含VkSwapchainPresentScalingCreateInfoEXT且其scalingBehavior不为0，则imageExtent的范围必须包含在[minScaledImageExtent,maxScaledImageExtent]之间，其中minScaledImageExtent和maxScaledImageExtent为调用vkGetPhysicalDeviceSurfaceCapabilities2KHR传入surface以及presentMode返回的VkSurfacePresentScalingCapabilitiesEXT中的成员
		8.imageExtent的width以及height必须都是非0值
		9.imageArrayLayers 必须大于0且小于等于调用vkGetPhysicalDeviceSurfaceCapabilitiesKHR传入surface返回的VkSurfaceCapabilitiesKHR的maxImageArrayLayers
		10.如果presentMode为VK_PRESENT_MODE_IMMEDIATE_KHR, VK_PRESENT_MODE_MAILBOX_KHR, VK_PRESENT_MODE_FIFO_KHR 或者 VK_PRESENT_MODE_FIFO_RELAXED_KHR，imageUsage必须是一个调用vkGetPhysicalDeviceSurfaceCapabilitiesKHR传入surface返回的VkSurfaceCapabilitiesKHR的supportedUsageFlags中的子集
		11.如果presentMode为VK_PRESENT_MODE_SHARED_DEMAND_REFRESH_KHR 或者 VK_PRESENT_MODE_SHARED_CONTINUOUS_REFRESH_KHR，imageUsage必须是一个调用vkGetPhysicalDeviceSurfaceCapabilities2KHR传入surface返回的VkSharedPresentSurfaceCapabilitiesKHR的sharedPresentSupportedUsageFlags中的子集
		12.如果imageSharingMode 为VK_SHARING_MODE_CONCURRENT，则（1）pQueueFamilyIndices 必须是有效的queueFamilyIndexCount个uint32_t值的数组指针
																（2）queueFamilyIndexCount 必须大于1
																（3）pQueueFamilyIndices中的每个元素必须是唯一的，且必须小于调用vkGetPhysicalDeviceQueueFamilyProperties或者vkGetPhysicalDeviceQueueFamilyProperties2返回的pQueueFamilyPropertyCount（该值指明队列族的个数）
		13.preTransform 必须是调用vkGetPhysicalDeviceSurfaceCapabilitiesKHR传入surface返回的VkSurfaceCapabilitiesKHR中的supportedTransforms中的一个bit设置
		14.compositeAlpha 必须是调用vkGetPhysicalDeviceSurfaceCapabilitiesKHR传入surface返回的VkSurfaceCapabilitiesKHR中的supportedCompositeAlpha中的一个bit设置
		15.presentMode 必须是调用vkGetPhysicalDeviceSurfacePresentModesKHR传入surface返回的VkPresentModeKHR中的一个
		16.如果逻辑设备以VkDeviceGroupDeviceCreateInfo::physicalDeviceCount为1创建，则flags不能包含VK_SWAPCHAIN_CREATE_SPLIT_INSTANCE_BIND_REGIONS_BIT_KHR
		17.如果oldSwapchain不为VK_NULL_HANDLE，则oldSwapchain 必须是一个关联到surface所应用的native window的 non-retired swapchain
		18.swapchain的隐含的image创建参数必须被支持，见vkGetPhysicalDeviceImageFormatProperties返回的信息
		19.如果flags包含VK_SWAPCHAIN_CREATE_MUTABLE_FORMAT_BIT_KHR则pNext中必须包含一个viewFormatCount大于0且pViewFormats中必须有一个元素等于 imageFormat的VkImageFormatListCreateInfo
		20.如果pNext中包含VkImageFormatListCreateInfo，且其viewFormatCount 不为0，则其pViewFormats中所有的format必须和列举在compatibility table中描述的format兼容（参见p4067） 
		21.如果flags不包含VK_SWAPCHAIN_CREATE_MUTABLE_FORMAT_BIT_KHR则pNext中包含一个VkImageFormatListCreateInfo，则其viewFormatCount必须为0或者1
		22.如果flags包含VK_SWAPCHAIN_CREATE_PROTECTED_BIT_KHR，则调用vkGetPhysicalDeviceSurfaceCapabilities2KHR传入surface返回的VkSurfaceProtectedCapabilitiesKHR::supportsProtected 必须为VK_TRUE
		23.如果pNext中包含fullScreenExclusive设置为VK_FULL_SCREEN_EXCLUSIVE_APPLICATION_CONTROLLED_EXT的VkSurfaceFullScreenExclusiveInfoEXT且surface由vkCreateWin32SurfaceKHR创建，则pNext中也必须包含一个VkSurfaceFullScreenExclusiveWin32InfoEXT
		24.如果imageCompressionControlSwapchain 特性未开启，则pNext中不能包含VkImageCompressionControlEXT
		*/


		//创建swapchain
		vkCreateSwapchainKHR(device, &swapchainCreateInfoKHR/*pCreateInfo，指定创建swapchain的信息*/, nullptr, &swapchainKHR);
		/*
		vkCreateSwapchainKHR相关说明:

		创建的swapchain中的image等效于vulkan中以以下信息创建的image:
		VkImageCreateInfo Field										Value
					flags									如果创建swapchain包含VK_SWAPCHAIN_CREATE_SPLIT_INSTANCE_BIND_REGIONS_BIT_KHR，
																则等价于创建一个包含 VK_IMAGE_CREATE_SPLIT_INSTANCE_BIND_REGIONS_BIT的image；
															如果创建swapchain包含VK_SWAPCHAIN_CREATE_PROTECTED_BIT_KHR，
																则等价于创建一个包含 VK_IMAGE_CREATE_PROTECTED_BIT的image；
															如果创建swapchain包含VK_SWAPCHAIN_CREATE_MUTABLE_FORMAT_BIT_KHR，
																则等价于创建一个包含 VK_IMAGE_CREATE_PROTECTED_BIT和 VK_IMAGE_CREATE_EXTENDED_USAGE_BIT_KHR的image；
															不包含其他的image标志
					imageType								 VK_IMAGE_TYPE_2D
					format									pCreateInfo->imageFormat
					extent									{pCreateInfo->imageExtent.width, pCreateInfo->imageExtent.height, 1}
					mipLevels									1
					arrayLayers								pCreateInfo->imageArrayLayers
					samples									VK_SAMPLE_COUNT_1_BIT
					tiling									VK_IMAGE_TILING_OPTIMAL
					usage									pCreateInfo->imageUsage
					sharingMode								pCreateInfo->imageSharingMode
					queueFamilyIndexCount					pCreateInfo->queueFamilyIndexCount
					pQueueFamilyIndices						pCreateInfo->pQueueFamilyIndices
					initialLayout							VK_IMAGE_LAYOUT_UNDEFINED
		
		其他信息见p3143
		*/


		//销毁swapchain
		vkDestroySwapchainKHR(device, swapchainKHR, nullptr);
		/*
		vkDestroySwapchainKHR有效用法:
		1.所有从swapchain中获取的image必须已经完成了执行
		2.如果创建swapchain时提供了VkAllocationCallbacks，则这里必须提供一个兼容的callbakcs
		3.如果创建swapchain时未提供VkAllocationCallbacks，则这里pAllocator必须为NULL

		*/


		//当VK_KHR_display_swapchain 拓展开启，多个swapchain可以共享image
		vkCreateSharedSwapchainsKHR(device, 1, &swapchainCreateInfoKHR, nullptr, &swapchainKHR);


		//获取swapchain中的一组image，  还可以在创建VkImage的时候在其VkImageCreateInfo.pNext中加上一个VkImageSwapchainCreateInfoKHR来创建一个swapchain中的image，其使用vkBindImageMemory2 传入VkBindImageMemorySwapchainInfoKHR 绑定到一个swapchain中的内存，但这种情况下该VkImage需要手动销毁
		uint32_t imageCount = 0;
		std::vector<VkImage> presentImages;
		vkGetSwapchainImagesKHR(device, swapchainKHR, &imageCount, nullptr);
		presentImages.resize(imageCount);
		vkGetSwapchainImagesKHR(device, swapchainKHR, &imageCount, presentImages.data());


		//获取swapchain中一个可用的image，并返回其索引 
		uint32_t imageIndex = 0;
		VkResult acquireImageResult =  vkAcquireNextImageKHR(device, swapchainKHR, VK_TIMEOUT, VkSemaphore{/*假设这是一个有效的VkSemaphore*/ }/*为一个触发的semaphore*/, VkFence{/*假设这是一个有效的VkFence*/ }/*为一个触发的fence*/, & imageIndex/*返回下一个可用的image的索引*/);
		/*
		1.swapchain 不能处于retired state
		2.semaphore 如果不是VK_NULL_HANDLE则（1）必须是unsignaled状态
											（2）不能有任何未完成的信号或等待操作
		3.如果fence不是VK_NULL_HANDLE，则其必须是unsignaled状态，且不能关联到任何执行在其他队列上还未完成的命令
		4.semaphore 和fence 不能同时为VK_NULL_HANDLE
		5.如果对pAcquireInfo中创建swapchian的surface的不能保证前面的处理，则pAcquireInfo->timeout 必须为UINT64_MAX
		6.semaphore 的VkSemaphoreType 必须是VK_SEMAPHORE_TYPE_BINARY

		*/


		acquireImageResult;//vkAcquireNextImageKHR返回的结果说明
		/*
		VK_SUCCESS:  成功返回一个可用的image
		VK_ERROR_SURFACE_LOST_KHR:  指明surface不再可用
		VK_NOT_READY: 指明timeout为0且返回时没有可用的image
		VK_TIMEOUT: 指明在超过了timeout在[0,UINT64_MAX]指定的一个值时，仍没有可用的image
		VK_SUBOPTIMAL_KHR:  指明一个image可用，但此时swapchain已经不再匹配当前的surface了，但是仍然可以成功进行显示到surface上
		VK_ERROR_OUT_OF_DATE_KHR: 指明surface已经改变不再兼容swapchain，后续显示请求会直接失败，这种情况下如果需要继续显示则需要重新查询surface的属性并重新创建swapchain	
		*/


		//获取swapchain中一个可用的image，并返回其索引2 
		VkAcquireNextImageInfoKHR acquireNextImageInfoKHR{};
		acquireNextImageInfoKHR.sType = VK_STRUCTURE_TYPE_ACQUIRE_NEXT_IMAGE_INFO_KHR;
		acquireNextImageInfoKHR.pNext = nullptr;
		acquireNextImageInfoKHR.timeout = VK_TIMEOUT;//指定没有image可用时该函数需要等待多少纳秒
		acquireNextImageInfoKHR.swapchain = swapchainKHR;//指明从哪个swapchain中取image
		acquireNextImageInfoKHR.semaphore = VkSemaphore{/*假设这是一个有效的VkSemaphore*/ };//为一个触发的semaphore
		acquireNextImageInfoKHR.fence = VkFence{/*假设这是一个有效的VkFence*/ };//为一个触发的fence
		acquireNextImageInfoKHR.deviceMask = 0x00000001;//是一个设备掩码指明semaphore或者fence触发后哪个设备会使用该image
		/*
		VkAcquireNextImageInfoKHR有效用法:
		1.swapchain 不能处于retired state
		2.semaphore 如果不是VK_NULL_HANDLE则（1）必须是unsignaled状态
											（2）不能有任何未完成的信号或等待操作
		3.如果fence不是VK_NULL_HANDLE，则其必须是unsignaled状态，且不能关联到任何执行在其他队列上还未完成的命令
		4.semaphore 和fence 不能同时为VK_NULL_HANDLE
		5.deviceMask 必须是一个有效的设备掩码，且不能为0
		6.semaphore 的VkSemaphoreType 必须是VK_SEMAPHORE_TYPE_BINARY

		*/

		vkAcquireNextImage2KHR(device, &acquireNextImageInfoKHR, &imageIndex);//如果对pAcquireInfo中创建swapchian的surface的不能保证前面的处理，则pAcquireInfo->timeout 必须为UINT64_MAX


		//在进行了一系列绘制和图像layout转换后，可以将需要显示的image进行排队显示到surface上,   surface显示的本地坐标是基于平台的，一般默认左上角为像素原点（0，0），其他信息见p3172
		{
			struct PresentInfoKHREXT {
				VkDeviceGroupPresentInfoKHR deviceGroupPresentInfoKHR{};
				VkDisplayPresentInfoKHR displayPresentInfoKHR{};
				VkFrameBoundaryEXT frameBoundaryEXT{};
				VkPresentFrameTokenGGP presentFrameTokenGGP{};
				VkPresentIdKHR presentIdKHR{};
				VkPresentRegionsKHR presentRegionsKHR{};
				VkPresentTimesInfoGOOGLE presentTimesInfoGOOGLE{};
				VkSwapchainPresentFenceInfoEXT swapchainPresentFenceInfoEXT{};
				VkSwapchainPresentModeInfoEXT swapchainPresentModeInfoEXT{};
				PresentInfoKHREXT() {
					Init();
				}
				void Init() {
					deviceGroupPresentInfoKHR.sType = VK_STRUCTURE_TYPE_DEVICE_GROUP_PRESENT_INFO_KHR;
					deviceGroupPresentInfoKHR.pNext = nullptr;
					displayPresentInfoKHR.sType = VK_STRUCTURE_TYPE_DISPLAY_PRESENT_INFO_KHR;
					displayPresentInfoKHR.pNext = nullptr;
					frameBoundaryEXT.sType = VK_STRUCTURE_TYPE_MAX_ENUM;//未定义所以这里定义为非法值
					frameBoundaryEXT.pNext = nullptr;
					presentFrameTokenGGP.sType = VK_STRUCTURE_TYPE_PRESENT_FRAME_TOKEN_GGP;
					presentFrameTokenGGP.pNext = nullptr;
					presentIdKHR.sType = VK_STRUCTURE_TYPE_PRESENT_ID_KHR;
					presentIdKHR.pNext = nullptr;
					presentRegionsKHR.sType = VK_STRUCTURE_TYPE_PRESENT_REGIONS_KHR;
					presentRegionsKHR.pNext = nullptr;
					presentTimesInfoGOOGLE.sType = VK_STRUCTURE_TYPE_PRESENT_TIMES_INFO_GOOGLE;
					presentTimesInfoGOOGLE.pNext = nullptr;
					swapchainPresentFenceInfoEXT.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_PRESENT_FENCE_INFO_EXT;
					swapchainPresentFenceInfoEXT.pNext = nullptr;
					swapchainPresentModeInfoEXT.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_PRESENT_MODE_INFO_EXT;
					swapchainPresentModeInfoEXT.pNext = nullptr;


				}
			};


			VkPresentInfoKHR presentInfoKHR{};
			presentInfoKHR.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
			PresentInfoKHREXT presentInfoKHREXT{};
			//VkPresentInfoKHR.pNext
			{
				//当 VK_KHR_incremental_present拓展开启时，可以通过包含VkPresentRegionsKHR来给显示引擎一个提示，指明显示的image的只有某个特定的区域改变了，这可以让显示引擎只去更新这些改变了的区域
				VkPresentRegionsKHR& presentRegionsKHR = presentInfoKHREXT.presentRegionsKHR;
				presentRegionsKHR.swapchainCount = 1;//指明swapchain的数量,必须等于 VkPresentInfoKHR::swapchainCount
				VkPresentRegionKHR changedRegion{};
				{
					changedRegion.rectangleCount = 1;//pRectangles中元素个数，或者为0指明整个image都改变了需要更新
					VkRectLayerKHR rectLayer{};//该结构体指定的像素区域不会被缩放影响
					{
						rectLayer.layer = 0;//指定这个区域为image的哪个layer
						rectLayer.offset = VkOffset2D{ .x = 0,.y = 0 };//指明这个像素区域的原点
						rectLayer.extent = VkExtent2D{ .width = 1,.height = 1 };//指明这个像素区域的大小
						/*
						VkRectLayerKHR有效用法:
						1.offset + extent 的和在经过VkSwapchainCreateInfoKHR的preTransform变换后，不能大于创建swapchain时的VkSwapchainCreateInfoKHR的imageExtent
						2.layer 必须小于创建swapchain时的VkSwapchainCreateInfoKHR的imageArrayLayers
						*/
					}
					changedRegion.pRectangles = &rectLayer;//为NULL或者 一组 VkRectLayerKHR 的数组指针，VkRectLayerKHR指定改变了的区域所对的image的layer以及framebuffer coordinates，这些区域要关联到VkSurfaceCapabilitiesKHR::currentTransform,而不用管swapchain的 preTransform，显示引擎会为这些区域执行 preTransform 变换操作
				}
				presentRegionsKHR.pRegions = &changedRegion;//为NULL或者 swapchainCount个VkPresentRegionKHR 的数组指针，指明swapchain中自最后一次显示之后更新的image的区域

				
				//当开启 VK_KHR_display_swapchain时，可以指定显示器显示的额外信息 ,如果srcRect和dstRect的extent不同则会对应采取像素缩放
				VkDisplayPresentInfoKHR &displayPresentInfoKHR = presentInfoKHREXT.displayPresentInfoKHR;
				displayPresentInfoKHR.srcRect = VkRect2D{ .offset = VkOffset2D{.x = 0,.y = 0},.extent = VkExtent2D {.width = 1,.height = 1} };//为需要显示的像素矩形区域，该区域必须在显示igame的大小范围内，如果该结构体不指定则该值相当于默认该值为整个显示image
				displayPresentInfoKHR.dstRect = VkRect2D{ .offset = VkOffset2D{.x = 0,.y = 0},.extent = VkExtent2D {.width = 1,.height = 1} };//为swapchain的display mode下的可视矩形区域，，如果该结构体不指定则该值相当于默认该值为整个swapchain的可视区域，如果指定的区域为display mode的可视区域的一个子集，则如果swapchain的plane下的display play在指定区域外的内容是可见的，如果swapchain下没有plane，则display play在指定区域外的内容是不可见的，如果指定的区域有一部分在display plane的可视区域外，则映射到区域外这一部分的像素会被丢弃
				displayPresentInfoKHR.persistent = VK_TRUE;//如果这是VK_TRUE，则显示引擎将在支持它的显示器上启用缓冲模式，这允许显示引擎停止向显示器发送内容，直到呈现出新的图像。显示器将保留最后一个呈现的图像的副本。这允许使用更少的功率，但可能会增加表示延迟。如果没有指定该结构体，则将不会使用持久模式。
				/*
				VkDisplayPresentInfoKHR有效用法:
				VkDisplayPresentInfoKHR有效用法:
				1.srcRect 必须指定在显示igame的大小范围内的子集
				2.dstRect 必须指定swapchain使用的display mode的visibleRegion指定的可视范围内的子集
				3.如果调用vkGetPhysicalDeviceDisplayPropertiesKHR返回的对应该display的VkDisplayPropertiesKHR的persistentContent为VK_FALSE，则persistent 必须为VK_FALSE
				*/


				//VkDeviceGroupPresentInfoKHR 指明一组设备掩码和一个device group present mode  如果不包含该结构体或者swapchainCount为0，则可认为设备掩码为1，如果不含该结构体可认为mode为VK_DEVICE_GROUP_PRESENT_MODE_LOCAL_BIT_KHR
				VkDeviceGroupPresentInfoKHR& deviceGroupPresentInfoKHR = presentInfoKHREXT.deviceGroupPresentInfoKHR;
				deviceGroupPresentInfoKHR.swapchainCount = 1;//为0或者pDeviceMasks中元素个数
				uint32_t deviceMask = 0x00000001;
				deviceGroupPresentInfoKHR.pDeviceMasks = &deviceMask;//一组设备掩码uint32_t数组指针，一一对应VkPresentInfoKHR::pSwapchains
				deviceGroupPresentInfoKHR.mode = VK_DEVICE_GROUP_PRESENT_MODE_LOCAL_BIT_KHR;// VkDeviceGroupPresentModeFlagBitsKHR值，指明显示使用的 device group present mode，具体情况对应具体的操作见p3181
				/*
				VkDeviceGroupPresentInfoKHR有效用法:
				1.swapchainCount必须0或者VkPresentInfoKHR::swapchainCount
				2.如果mode为VK_DEVICE_GROUP_PRESENT_MODE_LOCAL_BIT_KHR，则pDeviceMasks中每个元素只能含有一个bit设置，则其VkDeviceGroupPresentCapabilitiesKHR::presentMask对应元素不能为非零值
				3.如果mode为VK_DEVICE_GROUP_PRESENT_MODE_REMOTE_BIT_KHR，则pDeviceMasks中每个元素只能含有一个bit设置，则逻辑设备中的一些物理设备必须在其VkDeviceGroupPresentCapabilitiesKHR::presentMask中包含该bit设置
				4.如果mode为VK_DEVICE_GROUP_PRESENT_MODE_SUM_BIT_KHR，则pDeviceMasks中每个元素必须有其所有bit设置设置在VkDeviceGroupPresentCapabilitiesKHR::presentMask 的一个元素中
				5.如果mode为VK_DEVICE_GROUP_PRESENT_MODE_LOCAL_MULTI_DEVICE_BIT_KHR，则pDeviceMasks中每个元素的每个bit设置，则其VkDeviceGroupPresentCapabilitiesKHR::presentMask对应元素不能为非零值
				6.pDeviceMasks中的每个元素的值必须等于swapchain中对应image的索引被最后获取时的VkAcquireNextImageInfoKHR::deviceMask的值
				7.mode 必须只有一个bit设置，且该bit设置必须包含在VkDeviceGroupSwapchainCreateInfoKHR::modes中
				*/


				//当 VK_GOOGLE_display_timing拓展开启，VkPresentTimesInfoGOOGLE 可以用来告诉显示引擎一个图片应该被显示的最早时间，可以用来避免stutter
				VkPresentTimesInfoGOOGLE &presentTimesInfoGOOGLE = presentInfoKHREXT.presentTimesInfoGOOGLE;
				presentTimesInfoGOOGLE.swapchainCount = 1;//指明处理的swapchian的数量，必须等于VkPresentInfoKHR::swapchainCount
				VkPresentTimeGOOGLE earliestDisplayTime{};
				{
					earliestDisplayTime.presentID = 0;//是应用程序提供的用于标识的值，可以与vkGetPastPresentationTimingGOOGLE返回的结果一起使用，以便唯一地识别一次显示present操作。为了对应用程序有用，它在一段时间内对应用程序有应该是唯一的
					earliestDisplayTime.desiredPresentTime = 0;//指定不应该将图像在该值指定的时间之前进行显示。该时间是一个以纳秒为单位，相对于一个单调递增的时钟（例如，在安卓和Linux上的CLOCK_MONOTONIC（见clock_gettime(2)））。值为零表示显示引擎可以在任何时候显示图像。当应用程序希望提供 presentID但不需要指定特定的显示时间的情况下使用。
				}
				presentTimesInfoGOOGLE.pTimes = &earliestDisplayTime;//为NULL或者 swapchainCount个VkPresentTimeGOOGLE的数组指针，指明 VkPresentInfoKHR::pImageIndices中指定的image的最早显示时间


				VkPresentIdKHR& presentIdKHR = presentInfoKHREXT.presentIdKHR;
				presentIdKHR.swapchainCount = 1;//指明处理的swapchian的数量
				uint64_t presentId = 0;
				presentIdKHR.pPresentIds = &presentId;//为NULL或者 swapchainCount个uint64_t的数组指针，指明给定给 VkPresentInfoKHR::pImageIndices中指定的image的显示操作的一个标识id
				/*
				VkPresentIdKHR有效用法:
				1.swapchainCount必须等于VkPresentInfoKHR::swapchainCount
				2.presentIds中每个元素的值必须大于传递给pSwapchains中对应swapchain的先前显示的presentId
				*/
				{
					//如果开启了 presentWait 特性，则可以等待某个presentId关联的swapchain中image的显示操作完成， 该等待操作主要是等待关联到swapchain的当前presentId的值大于这里给定的值，所以swapchain中当前的presentId至少要为这里的值
					vkWaitForPresentKHR(device, swapchainKHR/*swapchain,指定哪个显示image的 non-retired swapchain*/, 0/*presentId，指定要等待的显示操作关联的presentId*/, VK_TIMEOUT/*timeout, 指定以纳秒为单位的等待超时时间*/);
					/*
					vkWaitForPresentKHR有效用法:
					1.swapchain 不能处于retired state
					2.presentWait 特性必须开启
					*/
				}


				//当开启 VK_GGP_frame_token 拓展，则显示swapchian中的image时可以通过  VkPresentFrameTokenGGP指定Google Games Platform frame token
				VkPresentFrameTokenGGP& presentFrameTokenGGP = presentInfoKHREXT.presentFrameTokenGGP;
				GgpFrameToken frameToken{};
				presentFrameTokenGGP.frameToken = frameToken;//指定要显示的image的Google Games Platform frame token,必须是一个有效的GgpFrameToken


				//VkSwapchainPresentModeInfoEXT 指定了swapchain的用于当前以及后续显示操作的present mode，可以改变创建swapchain时指定的present mode，前后两个resent mode之间的切换遵循一定操作，两个mode的类型需要满足一定要求，具体情况见p3188
				VkSwapchainPresentModeInfoEXT& swapchainPresentModeInfoEXT = presentInfoKHREXT.swapchainPresentModeInfoEXT;
				swapchainPresentModeInfoEXT.swapchainCount = 1;//为swapchain的数量，必须等于VkPresentInfoKHR::swapchainCount
				VkPresentModeKHR presenMode = VK_PRESENT_MODE_FIFO_KHR;
				swapchainPresentModeInfoEXT.pPresentModes = &presenMode;//为NULL或者swapchainCount个VkPresentModeKHR的数组指针，指定swapchain的用于当前以及后续显示操作的present mode， 这些present mode必须列举在创建其对应swapchain的VkSwapchainPresentModesCreateInfoEXT::pPresentModes中


				VkSwapchainPresentFenceInfoEXT& swapchainPresentFenceInfoEXT = presentInfoKHREXT.swapchainPresentFenceInfoEXT;
				swapchainPresentFenceInfoEXT.swapchainCount = 1;//为swapchain的数量，必须等于VkPresentInfoKHR::swapchainCount，必须大于0
				VkFence presenFinishFence{/*假设这是一个有效的VkFence*/ };
				swapchainPresentFenceInfoEXT.pFences = &presenFinishFence;//是swapchainCount 个VkFence的数组指针，指定提交的显示请求完成时要触发的fence，这些fence如果不是VK_NULL_HANDLE则必须是未触发的，触发的顺序按照显示操作的顺序进行




			}
			presentInfoKHR.pNext = &presentInfoKHREXT.deviceGroupPresentInfoKHR;
			presentInfoKHR.swapchainCount = 1;//指明要处理的swapchain的数量
			presentInfoKHR.pSwapchains = &swapchainKHR;//swapchainCount个VkSwapchainKHR的数组指针， 指明要处理的swapchain
			presentInfoKHR.pImageIndices = &imageIndex;//swapchainCount个uint32_t的数组指针，指明对应pSwapchains中的swapchain要显示的image的索引，在显示前这些image的布局必须要转换为VK_IMAGE_LAYOUT_PRESENT_SRC_KHR或者VK_IMAGE_LAYOUT_SHARED_PRESENT_KHR
			VkResult presentResult{};
			presentInfoKHR.pResults = &presentResult;//swapchainCount个VkResult的数组指针,指明各个swapchain中的image的显示结果，如果不需要获取结果，则可以为NULL
			presentInfoKHR.waitSemaphoreCount = 1;//为发布显示请求之前需要等待的semaphore的数量，可能为0
			VkSemaphore waitSemaphroe{/*假设这是一个有效的VkSemaphore*/ };
			presentInfoKHR.pWaitSemaphores = &waitSemaphroe;//为NULL或者含waitSemaphoreCount个 VkSemaphore的数组指针，指定发布显示请求之前需要等待的semaphore
			/*
			VkPresentInfoKHR有效用法:
			1.pSwapchain的每个元素必须时唯一的
			2.pImageIndices中的每个元素必须是从pSwapchains对应swapchain中获取的image的索引值，且该image的subresource必须在执行该命令前已经转换到VK_IMAGE_LAYOUT_PRESENT_SRC_KHR 或者 VK_IMAGE_LAYOUT_SHARED_PRESENT_KHR layout
			3.如果pNext中包含VkPresentIdKHR，且presentId特性未开启，则VkPresentIdKHR中的presentIds中每个元素必须为NULL
			4.如果pSwapchains的任何元素的swapchain以含有VkSwapchainPresentModesCreateInfoEXT创建，则pSwapchains的所有元素的swapchain也必须以含有VkSwapchainPresentModesCreateInfoEXT创建
			*/



			vkQueuePresentKHR(VkQueue{/*假设这是一个有效的VkQueue*/ }/*queue*/, & presentInfoKHR);
			/*
			vkQueuePresentKHR有效用法:
			1.pPresentInfo的pSwapchains的每个swapchain必须是以在queue上支持显示的surface创建的，参见vkGetPhysicalDeviceSurfaceSupportKHR
			2.如果pPresentInfo的pSwapchains有超过1个的swapchain从display surface上创建，则所有引用到相同显示器desplay的display surface必须使用相同的display mode
			3.当pPresentInfo的pWaitSemaphores的元素定义了引用到一个binary semaphore执行在queue上的semaphore wait操作时，不能有其他的队列在等待该semaphore
			4.pPresentInfo的pWaitSemaphores的所有元素必须以VkSemaphoreType 为VK_SEMAPHORE_TYPE_BINARY 创建
			5.pPresentInfo的pWaitSemaphores的所有元素必须引用到一个signal 操作已经提交执行的且其依赖的semaphore signal 操作也提交执行的semaphore
			*/


			//释放之前通过vkAcquireNextImage2KHR 或者vkAcquireNextImageKHR 获取的swapchain中的image ,只有这些image不再被设备使用才可以释放，释放不改变这些image的内容的布局
			VkReleaseSwapchainImagesInfoEXT releaseSwapchainImagesInfoEXT{};
			releaseSwapchainImagesInfoEXT.sType = VK_STRUCTURE_TYPE_RELEASE_SWAPCHAIN_IMAGES_INFO_EXT;
			releaseSwapchainImagesInfoEXT.pNext = nullptr;
			releaseSwapchainImagesInfoEXT.swapchain = swapchainKHR;//指明要释放的image所在的swapchain
			releaseSwapchainImagesInfoEXT.imageIndexCount = 1;//是要释放的image的个数
			releaseSwapchainImagesInfoEXT.pImageIndices = &imageIndex;//是imageIndexCount 个swapchain中要释放的image的索引值的数组指针
			/*
			VkReleaseSwapchainImagesInfoEXT有效用法:
			1.pImageIndices 中的每个元素必须是从swapchain中获取的image的索引值
			2.对pImageIndices 中的每个元素引用的image的所有使用操作必须已经完成了执行
			*/

			vkReleaseSwapchainImagesEXT(device, &releaseSwapchainImagesInfoEXT);



		}


	}


	//Hdr Metadata  参见p3192
	{
		/*
		该节描述了如何改进内容的颜色再现，以更好地再现在显示器上看到的颜色。以下定义来自于相关的SMPTE 2086、CTA 861.3和CIE 15：2004规范
		*/

		VkSwapchainKHR swapchainKHR{/*假设这是一个有效的VkSwapchainKHR*/};

		//提供实现一个 Hdr metadata,这些metdata将会应用到swapchain的下一次显示操作中
		VkHdrMetadataEXT hdrMetadataEXT{};
		hdrMetadataEXT.sType = VK_STRUCTURE_TYPE_HDR_METADATA_EXT;
		hdrMetadataEXT.pNext = nullptr;
		hdrMetadataEXT.displayPrimaryRed = VkXYColorEXT{ .x = 0,.y = 0 };//为 VkXYColorEXT值指明显示器的红基色的色度坐标 chromaticity coordinates，指明 x 和 y chromaticity coordinate，Chromaticity coordinates参见 CIE 15:2004
		hdrMetadataEXT.displayPrimaryGreen = VkXYColorEXT{ .x = 0,.y = 0 };//为 VkXYColorEXT值指明显示器的绿基色的色度坐标 chromaticity coordinates，指明 x 和 y chromaticity coordinate，Chromaticity coordinates参见 CIE 15:2004
		hdrMetadataEXT.displayPrimaryBlue = VkXYColorEXT{ .x = 0,.y = 0 };//为 VkXYColorEXT值指明显示器的蓝基色的色度坐标 chromaticity coordinates，指明 x 和 y chromaticity coordinate，Chromaticity coordinates参见 CIE 15:2004
		hdrMetadataEXT.whitePoint = VkXYColorEXT{ .x = 0.3127f,.y = 0.329f };//为 VkXYColorEXT值指明显示器的白色的色度坐标 chromaticity coordinates，指明 x 和 y chromaticity coordinate，Chromaticity coordinates参见 CIE 15:2004
		hdrMetadataEXT.minLuminance = 0.0f;//为显示的最小的发光亮度值，以nits为单位
		hdrMetadataEXT.maxLuminance = 1.0f;//为显示的最大的发光亮度值，以nits为单位
		hdrMetadataEXT.maxContentLightLevel = 1;//为显示的最大的内容亮度值，以nits为单位
		hdrMetadataEXT.maxFrameAverageLightLevel = 1;//为显示的最大的帧平均亮度值，以nits为单位


		vkSetHdrMetadataEXT(device,1, &swapchainKHR, &hdrMetadataEXT);

	}


	//Present Barrier  参见p3194
	{
		/*
		 VK_NV_present_barrier 拓展可以允许应用使用 present barrier 去同步多个swapchain中的显示操作，这需要这些swapchain在创建swapchain的VkSwapchainCreateInfoKHR中包含一个presentBarrierEnable设为VK_TRUE的 VkSwapchainPresentBarrierCreateInfoNV
		
		
		*/

		//如果不包含该结构体则默认presentBarrierEnable 为VK_FALSE
		VkSwapchainPresentBarrierCreateInfoNV swapchainPresentBarrierCreateInfoNV{};
		swapchainPresentBarrierCreateInfoNV.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_PRESENT_BARRIER_CREATE_INFO_NV;
		swapchainPresentBarrierCreateInfoNV.pNext = nullptr;
		swapchainPresentBarrierCreateInfoNV.presentBarrierEnable = VK_TRUE;//指明显示请示是否使用present barrier
	}

}



NS_TEST_END