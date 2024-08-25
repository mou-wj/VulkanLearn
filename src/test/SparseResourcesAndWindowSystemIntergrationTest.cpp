#include "SparseResourcesAndWindowSystemIntergrationTest.h"
#include "vulkan/vulkan_android.h"
//wayland
struct wl_display {};//δ���������Լ�����
struct wl_surface {};//δ���������Լ�����
#include "vulkan/vulkan_wayland.h"
#include <Windows.h>
#include "vulkan/vulkan_win32.h"
//xcb
typedef uint32_t xcb_connection_t;//δ���������Լ�����
typedef uint32_t xcb_window_t;//δ���������Լ�����
#include "vulkan/vulkan_xcb.h"
//xlib
typedef uint32_t Display;//δ���������Լ�����
typedef uint32_t Window;//δ���������Լ�����
#include "vulkan/vulkan_xlib.h"
//direct fb
typedef uint32_t  IDirectFB;//δ���������Լ�����
typedef uint32_t  IDirectFBSurface;//δ���������Լ�����
#include "vulkan/vulkan_directfb.h"
//fuchsia
typedef uint32_t zx_handle_t;//δ���������Լ�����
#include "vulkan/vulkan_fuchsia.h"
//google game platform
typedef uint32_t GgpStreamDescriptor;//δ���������Լ�����
#include "vulkan/vulkan_ggp.h"

#include "vulkan/vulkan_ios.h"

#include "vulkan/vulkan_macos.h"

#include "vulkan/vulkan_vi.h"

#include "vulkan/vulkan_metal.h"
//screen qnx
struct _screen_context {};//δ���������Լ�����
struct _screen_window {};//δ���������Լ�����
#include "vulkan/vulkan_screen.h"
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
	ͨ������£�non-sparse��VkBuffer����VkImage��Դ��Ҫ�󶨵������������ĵ������ڴ��ϣ����������sparse�ģ���ô�Ϳ����и��ɵ��ڴ�����; ��Դ���԰󶨵�����ڴ��ϣ���Դ�������°󶨣����Ծ������ɲ����ڴ����������ʹ�õ���������
	
	*/

	//Sparse Resource Features  �μ�p2981
	{
		/*
		Sparse resources����Ҫ�����������ԣ������ڴ�����Դ��VkImageCreateInfo����VkBufferCreateInfo��־�����ã��⼸�������ֺ��豸��һ���������ԣ�VkPhysicalDeviceFeatures.���������
		�⼸�����԰����� sparseBinding������sparseBinding��sparseResidency ������ԣ� sparseResidencyAliased���ԣ���Щ���ԵĹ��ܼ�p2981-p2982
		
		
		*/
	}


	//Sparse Buffers and Fully-Resident Images  �μ�p2983
	{
		/*
		��VK_IMAGE_CREATE_SPARSE_BINDING_BIT ���� VK_BUFFER_CREATE_SPARSE_BINDING_BIT������VkImage����VkBuffer,
		
		���VkImage����VK_IMAGE_CREATE_SPARSE_RESIDENCY_BIT���������������ڴ��Ӧ���ǲ��ɼ��ģ�

		���ͬʱʹ���� VK_IMAGE_CREATE_SPARSE_RESIDENCY_BIT ���� VK_BUFFER_CREATE_SPARSE_RESIDENCY_BIT���������ʹ��ǰ����Դ�󶨵�һ�������ڴ����
		
		*/

		//Sparse Buffer and Fully - Resident Image Block Size    ��VkMemoryRequirements::alignment. alignment���   ��p2983
	}

	// Sparse Partially-Resident Buffers  ��VK_BUFFER_CREATE_SPARSE_BINDING_BIT ��VK_BUFFER_CREATE_SPARSE_RESIDENCY_BIT ������VkBuffer,     �μ�p2983

	//Sparse Partially - Resident Images  �μ�p2983
	{
		//��VK_IMAGE_CREATE_SPARSE_BINDING_BIT ��VK_IMAGE_CREATE_SPARSE_RESIDENCY_BIT ������VkImage

		// Accessing Unbound Regions  �μ�p2983
		{
			/*
			����δ�󶨵��ڴ����Ϊ�ɸ���VkPhysicalDeviceSparseProperties.residencyNonResidentStrict ��������������μ�p2984
			
			*/
		}

		//Mip Tail Regions  �μ�p2984
		{
			/*
			������VK_IMAGE_CREATE_SPARSE_BINDING_BIT ��VK_IMAGE_CREATE_SPARSE_RESIDENCY_BIT ������VkImage��

			��ÿ��layer�нڴ�СС��sparse block size��������mipmap level������ᱻ��֯��һ�𣬳�Ϊmip tail region��
			
			�����image��format��VkSparseImageFormatProperties��flags���������VK_SPARSE_IMAGE_FORMAT_ALIGNED_MIP_SIZE_BIT����layer���κ���ά�Ȳ���sparse image block��VkPhysicalDeviceSparseProperties.residencyAlignedMipSize����Ӧά�ȴ�С����������mipmap level�Լ���mipmap level֮���mipmap level�����򶼻ᱻ��֯�� mip tail region�С�

			���VkSparseImageMemoryRequirements::flags�а���VK_SPARSE_IMAGE_FORMAT_SINGLE_MIPTAIL_BIT������layer��mip tail region�ᱻ��֯��һ�𣬷���ÿ��layer��mip tail region�ᵥ�����䡣

			����mip tail region�ĸ���VK_SPARSE_IMAGE_FORMAT_ALIGNED_MIP_SIZE_BIT�Լ�VK_SPARSE_IMAGE_FORMAT_SINGLE_MIPTAIL_BIT���ܵõ�������ϣ�ÿ����ϵ�mip tail region���ڴ���ʽ�μ� p2985-p2987

			*/


		}

		// Standard Sparse Image Block Shapes  �μ�p2987
		{
			/*
			Standard sparse image block shapes��sparse image blocks����image��format,������һ���׼��ά�ȡ�texel�Լ�sparse image block��ѹ��texel�Ĳ����ǻ���ʵ�ֵģ���ǰ�����standard sparse image block shapes����64KB��С��
			
			ά�ȱ��
			//��������������������������������������������������������������������������������
			Standard Sparse Image Block Shapes (Single Sample)��
			TEXEL SIZE (bits)				Block Shape (2D)			Block Shape (3D)
			8-Bit						 256 �� 256 �� 1				64 �� 32 �� 32
			16-Bit						 256 �� 128 �� 1				32 �� 32 �� 32
			32-Bit						 128 �� 128 �� 1				32 �� 32 �� 16
			64-Bit						 128 �� 64 �� 1					32 �� 16 �� 16
			128-Bit						 64 �� 64 �� 1					16 �� 16 �� 16


			Standard Sparse Image Block Shapes (MSAA)
			TEXEL SIZE (bits)		Block Shape (2X)		Block Shape (4X)		Block Shape (8X)		Block Shape(16X)
			8-Bit					128 �� 256 �� 1			128 �� 128 �� 1			64 �� 128 �� 1			64 �� 64 �� 1
			16-Bit					128 �� 128 �� 1			128 �� 64 �� 1			64 �� 64 �� 1			64 �� 32 �� 1
			32-Bit					64 �� 128 �� 1			64 �� 64 �� 1			32 �� 64 �� 1			32 �� 32 �� 1
			64-Bit					64 �� 64 �� 1			64 �� 32 �� 1			32 �� 32 �� 1			32 �� 16 �� 1
			128-Bit					32 �� 64 �� 1			32 �� 32 �� 1			16 �� 32 �� 1			16 �� 16 �� 1
			//������������������������������������������������������������������������������������������������
			����֧��ά�ȱ�����оٵ�Sparse Image Block Shapes�ɸ���VkPhysicalDeviceSparseProperties��residencyStandard2DBlockShape�� residencyStandard2DMultisampleBlockShape ����residencyStandard3DBlockShape �жϣ���Щ���Բ�����ζ������image ���Ͷ�֧��sparse image,ֻ��˵����Щ����֧�ֵ�sparse imageû��Standard Sparse Image Block Shapes�Ľ�ʹ���Զ����
			*/
		}


		//Custom Sparse Image Block Shapes  �μ�p2989
		{
			/*
			û��֧��Standard Sparse Image Block Shapes�������ʹ���Զ����Sparse Image Block Shapes���Զ����Sparse Image Block Shapes��vkGetPhysicalDeviceSparseImageFormatProperties �Լ� vkGetImageSparseMemoryRequirements���÷��ص�VkSparseImageFormatProperties::imageGranularity�Լ�VkMemoryRequirements::alignment����.
			
			*/
		}

		// Multiple Aspects   �μ�p2990    Partially resident images����ͬ��aspect�ָ��Ե�sparse properties
	}

	// Sparse Memory Aliasing  �μ�p2991
	{
		
		/*
		Ĭ������£�sparse��Դ����non-sparse��Դ�ı������򣬼� Memory Aliasing p1194
		
		���VkDevice������ sparseResidencyAliased���ԣ���sparse��Դ����ʹ��VK_BUFFER_CREATE_SPARSE_ALIASED_BIT �Լ� VK_IMAGE_CREATE_SPARSE_ALIASED_BIT ����������һ�µķ�ʽ���ʰ󶨵�һ������sparse��Դ�еĶ��λ�õ������ڴ�
		
		���ʸ��ڴ���Ҫ��memory dependencies������Ҫ����һЩ���ƣ���p2991
		*/


	}

	// Sparse Resource Implementation Guidelines (Informative)  �μ�p2992
	{
		/*
		sparseBinding ����������resource������ʱ�򱣴����豸�����ַ��Χ������֮���non-sparse��Դһ��

		sparseResidency �����������ڴ�Ϳ��Է�����Դ��residencyNonResidentStrict���Թ涨����δ�󶨵��ڴ����Ϊ


		
		*/
	}


	//Sparse Resource API  �μ�p2994
	{

		/*
		Physical Device Features �μ�p2994

		�о��� VkPhysicalDeviceFeatures�У�Ϊ:
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


		//Physical Device Sparse Properties   �μ�p2995
		{
			/*
			ʵ�ֵ���Щ�������޷��رյ��Ҹ�����Щ���Կ�������Ӧ�øı�sparse��Դ���÷������о��� VkPhysicalDeviceProperties::sparseProperties�У�Ϊһ��VkPhysicalDeviceSparseProperties
			*/

			VkPhysicalDeviceSparseProperties physicalDeviceSparseProperties = VkPhysicalDeviceProperties{}.sparseProperties;
			physicalDeviceSparseProperties.residencyStandard2DBlockShape = VK_TRUE;//���ΪVK_TRUE,��ָ�������豸��ʹ��standard sparse image block shapes�������е�single-sample 2D sparse resources�������֧�֣��򷵻ص�VkSparseImageFormatProperties.imageGranularity�Ͳ���Ҫ���� standard sparse image block dimensionsƥ��
			physicalDeviceSparseProperties.residencyStandard2DMultisampleBlockShape = VK_TRUE;//���ΪVK_TRUE,��ָ�������豸��ʹ��standard sparse image block shapes�������е�multisample 2D sparse resources�������֧�֣��򷵻ص�VkSparseImageFormatProperties.imageGranularity�Ͳ���Ҫ���� standard sparse image block dimensionsƥ��
			physicalDeviceSparseProperties.residencyStandard3DBlockShape = VK_TRUE;//���ΪVK_TRUE,��ָ�������豸��ʹ��standard sparse image block shapes�������е�3D sparse resources�������֧�֣��򷵻ص�VkSparseImageFormatProperties.imageGranularity�Ͳ���Ҫ���� standard sparse image block dimensionsƥ��
			physicalDeviceSparseProperties.residencyAlignedMipSize = VK_TRUE;//���ΪVK_TRUE������mipmap level��image��ά�Ȳ�Ϊ��Ӧ sparse image block ά�ȵ���������level�����ŵ�mip tail�У������֧�֣���ֻ��ά��С��VkSparseImageFormatProperties.imageGranularity��level��ŵ�mip tail�У����֧�֣���Ӧ�������ص�VkSparseImageFormatProperties.flags�а���VK_SPARSE_IMAGE_FORMAT_ALIGNED_MIP_SIZE_BIT��ָ��mipmap level��image��ά�Ȳ�Ϊ��Ӧ sparse image block ά�ȵ���������level��ŵ�mip tail��
			physicalDeviceSparseProperties.residencyNonResidentStrict = VK_TRUE;//ָ�������豸�Ƿ����һֱ������Դ��non-resident�������ΪVK_TRUE������ʸ����򷵻ص�ֵΪ0��д��������ֵ�ᱻ����

		}


		//Sparse Image Format Properties �μ�p2996
		{
			//�ڴ���sparse��Դǰ��ѯ sparse image format properties
			uint32_t sparseImageFormatPropertiesCount = 0;
			std::vector<VkSparseImageFormatProperties> sparseImageFormatProperties{};
			vkGetPhysicalDeviceSparseImageFormatProperties(physicalDevice, VK_FORMAT_R8G8B8_SRGB, VK_IMAGE_TYPE_2D, VK_SAMPLE_COUNT_1_BIT/*samples�������ǲ�����ͬformat, type, tiling, �Լ� usage��������vkGetPhysicalDeviceImageFormatProperties���ص�VkImageFormatProperties::sampleCounts�е���Чֵ*/, VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT, VK_IMAGE_TILING_LINEAR,
				&sparseImageFormatPropertiesCount,nullptr);
			sparseImageFormatProperties.resize(sparseImageFormatPropertiesCount);
			vkGetPhysicalDeviceSparseImageFormatProperties(physicalDevice, VK_FORMAT_R8G8B8_SRGB, VK_IMAGE_TYPE_2D, VK_SAMPLE_COUNT_1_BIT, VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT, VK_IMAGE_TILING_LINEAR,
				&sparseImageFormatPropertiesCount, sparseImageFormatProperties.data());//���践�سɹ�������һ��property
			VkSparseImageFormatProperties& sparseImageFormatPropertie = sparseImageFormatProperties[0];
			sparseImageFormatPropertie.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;//Ϊ VkImageAspectFlagBits���ֵλ���룬ָ����propertyӦ�õ�aspect
			sparseImageFormatPropertie.flags = VK_SPARSE_IMAGE_FORMAT_ALIGNED_MIP_SIZE_BIT;/*VkSparseImageFormatFlagBits���ֵλ����ָ��sparse resource���������
			VkSparseImageFormatFlagBits:
			VK_SPARSE_IMAGE_FORMAT_SINGLE_MIPTAIL_BIT: ָ��image������array layersֻ��һ��mip tail region������ÿ��layer����һ��
			VK_SPARSE_IMAGE_FORMAT_ALIGNED_MIP_SIZE_BIT:  ָ���ᱻ�ŵ�mipmap tail regionά�Ȳ�Ϊ��Ӧsparse image block��ά���������ĵ�һ��mipmap level
			VK_SPARSE_IMAGE_FORMAT_NONSTANDARD_BLOCK_SIZE_BIT:  ָ��image��ʹ��standard sparse image block dimensions����imageGranularity��ƥ���Ӧformat��standard sparse image block dimensions

			
			*/
			sparseImageFormatPropertie.imageGranularity = VkExtent3D{ .width = 1,.height = 1,.depth = 1 };//Ϊsparse image block����texel����compressed texel blocks�� width, height, �Լ� depthά��ֵ


			//�ڴ���sparse��Դǰ��ѯ sparse image format properties 2   vkGetPhysicalDeviceSparseImageFormatProperties2��ͬ��vkGetPhysicalDeviceSparseImageFormatProperties2KHR
			VkPhysicalDeviceSparseImageFormatInfo2 physicalDeviceSparseImageFormatInfo2{};
			physicalDeviceSparseImageFormatInfo2.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SPARSE_IMAGE_FORMAT_INFO_2;
			physicalDeviceSparseImageFormatInfo2.pNext = nullptr;
			physicalDeviceSparseImageFormatInfo2.format = VK_FORMAT_R8G8B8_SRGB;//image format
			physicalDeviceSparseImageFormatInfo2.samples = VK_SAMPLE_COUNT_1_BIT;//image samples,�����ǲ�����ͬformat, type, tiling, �Լ� usage��������vkGetPhysicalDeviceImageFormatProperties���ص�VkImageFormatProperties::sampleCounts�е���Чֵ
			physicalDeviceSparseImageFormatInfo2.tiling = VK_IMAGE_TILING_LINEAR;//image tiling
			physicalDeviceSparseImageFormatInfo2.type = VK_IMAGE_TYPE_2D;//image type
			physicalDeviceSparseImageFormatInfo2.usage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;//image usage
			
			uint32_t sparseImageFormatPropertiesCount2 = 0;
			std::vector<VkSparseImageFormatProperties2> sparseImageFormatProperties2s{};
			vkGetPhysicalDeviceSparseImageFormatProperties2(physicalDevice, &physicalDeviceSparseImageFormatInfo2, &sparseImageFormatPropertiesCount2, nullptr);
			sparseImageFormatProperties2s.resize(sparseImageFormatPropertiesCount2);
			vkGetPhysicalDeviceSparseImageFormatProperties2(physicalDevice, &physicalDeviceSparseImageFormatInfo2, &sparseImageFormatPropertiesCount2, sparseImageFormatProperties2s.data());//���践�سɹ���һ��
			VkSparseImageFormatProperties2& sparseImageFormatProperties2 = sparseImageFormatProperties2s[0];
			sparseImageFormatProperties2.sType = VK_STRUCTURE_TYPE_SPARSE_IMAGE_FORMAT_PROPERTIES_2;
			sparseImageFormatProperties2.pNext = nullptr;
			sparseImageFormatProperties2.properties = VkSparseImageFormatProperties{/*�������Ƿ��ص���ЧVkSparseImageFormatProperties*/};//ǰ����˵�������ﲻ�ٸ���
		}


		//Sparse Resource Creation  �μ�p3002
		{
			/*
			Sparse resources��Ҫ�ڴ���Device���Ƿ������sparse feature��
			
			�� *_SPARSE_BINDING_BIT��������Դ�Ϳ���ʹ��sparse binding command (vkQueueBindSparse).
			*/
		}

		// Sparse Resource Memory Requirements �μ�p3002
		{
			/*
			Sparse resources�԰󶨵��ڴ����ض�������
			*/

			/*
			Buffer and Fully-Resident Images

			buffer��fully �Լ� partially resident���Լ� fully-resident images���԰󶨵����� VkMemoryRequirements.�в������ڴ��� ��VkMemoryRequirements::alignment ָ���ֽڶ���
			*/


			/*
			Partially Resident Images 

			��Buffer and Fully-Resident Images������ͬ��Partially Resident Images ��Ҫ�������vkGetImageSparseMemoryRequirements���ص�VkSparseImageMemoryRequirements����Ĳ���
			*/


			//Sparse Image Memory Requirements
			{
				//��ѯSparse Image Memory Requirements
				uint32_t sparseImageMemoryRequirementsCount = 0;
				std::vector<VkSparseImageMemoryRequirements> sparseImageMemoryRequirements{};
				vkGetImageSparseMemoryRequirements(device, VkImage{/*��������һ����Ч��VkImage*/ }, & sparseImageMemoryRequirementsCount, nullptr);
				sparseImageMemoryRequirements.resize(sparseImageMemoryRequirementsCount);
				vkGetImageSparseMemoryRequirements(device, VkImage{/*��������һ����Ч��VkImage*/ }, & sparseImageMemoryRequirementsCount, sparseImageMemoryRequirements.data());//����ɹ�������һ��Ԫ��
				VkSparseImageMemoryRequirements& sparseImageMemoryRequirement = sparseImageMemoryRequirements[0];
				sparseImageMemoryRequirement.formatProperties = VkSparseImageFormatProperties{/*�������Ƿ��ص���ЧVkSparseImageFormatProperties*/ };//ָ��format������,ǰ����˵�������ﲻ�ٸ���
				sparseImageMemoryRequirement.imageMipTailFirstLod = 0;//ָ��image subresources�е�һ��������mipmap tail�е�mipmap level
				sparseImageMemoryRequirement.imageMipTailOffset = 0;//Ϊ���ڰ� mip tail region(s).��VkSparseImageOpaqueMemoryBindInfo��opaque memory offset
				sparseImageMemoryRequirement.imageMipTailSize = 0;//Ϊ mip tail region���ֽڴ�С����� formatProperties.flags����VK_SPARSE_IMAGE_FORMAT_SINGLE_MIPTAIL_BIT����Ϊ����mip tail�Ĵ�С������Ϊÿ��array layer��mip tail�Ĵ�С����ֵ��֤��sparse block size��������
				sparseImageMemoryRequirement.imageMipTailStride = 1;//Ϊÿ��array-layer��mip tail֮����ڴ沽������formatProperties.flags������VK_SPARSE_IMAGE_FORMAT_SINGLE_MIPTAIL_BIT�������Ч
			
			
			
				//��ѯSparse Image Memory Requirements2   vkGetImageSparseMemoryRequirements2 ��ͬ�� vkGetImageSparseMemoryRequirements2KHR
				uint32_t sparseImageMemoryRequirementsCount2 = 0;
				std::vector<VkSparseImageMemoryRequirements2> sparseImageMemoryRequirements2s{};
				VkImageSparseMemoryRequirementsInfo2 imageSparseMemoryRequirementsInfo2{};
				imageSparseMemoryRequirementsInfo2.sType = VK_STRUCTURE_TYPE_IMAGE_SPARSE_MEMORY_REQUIREMENTS_INFO_2;
				imageSparseMemoryRequirementsInfo2.pNext = nullptr;
				imageSparseMemoryRequirementsInfo2.image = VkImage{/*��������һ����Ч��VkImage*/ };//ָ����ѯ��image
				
				vkGetImageSparseMemoryRequirements2(device, &imageSparseMemoryRequirementsInfo2, &sparseImageMemoryRequirementsCount2, nullptr);
				sparseImageMemoryRequirements2s.resize(sparseImageMemoryRequirementsCount2);
				vkGetImageSparseMemoryRequirements2(device, &imageSparseMemoryRequirementsInfo2, &sparseImageMemoryRequirementsCount2, sparseImageMemoryRequirements2s.data());//����ɹ�������һ��Ԫ��
				VkSparseImageMemoryRequirements2 sparseImageMemoryRequirements2 = sparseImageMemoryRequirements2s[0];
				sparseImageMemoryRequirements2.sType = VK_STRUCTURE_TYPE_SPARSE_IMAGE_MEMORY_REQUIREMENTS_2;
				sparseImageMemoryRequirements2.pNext = nullptr;
				sparseImageMemoryRequirements2.memoryRequirements = VkSparseImageMemoryRequirements{/*��������һ����Ч��VkSparseImageMemoryRequirements*/ };//ǰ�����ἰ�����ﲻ�ٸ���

				//�ڲ���Ҫ����VkImage����²�ѯSparse Image Memory Requirements     vkGetDeviceImageSparseMemoryRequirements��ͬ��vkGetDeviceImageSparseMemoryRequirementsKHR
				VkDeviceImageMemoryRequirements deviceImageMemoryRequirements{};
				deviceImageMemoryRequirements.sType = VK_STRUCTURE_TYPE_DEVICE_IMAGE_MEMORY_REQUIREMENTS;
				deviceImageMemoryRequirements.pNext = nullptr;
				deviceImageMemoryRequirements.planeAspect = VK_IMAGE_ASPECT_COLOR_BIT;
				VkImageCreateInfo imageCreareInfo{/*��������һ����Ч��VkImageCreateInfo*/ };
				deviceImageMemoryRequirements.pCreateInfo = &imageCreareInfo;
				
				vkGetDeviceImageSparseMemoryRequirements(device, &deviceImageMemoryRequirements, &sparseImageMemoryRequirementsCount2, nullptr);
				sparseImageMemoryRequirements2s.resize(sparseImageMemoryRequirementsCount2);
				vkGetDeviceImageSparseMemoryRequirements(device, &deviceImageMemoryRequirements, &sparseImageMemoryRequirementsCount2, sparseImageMemoryRequirements2s.data());


			}


			

		}

		//Binding Resource Memory
		{
			/*
			Non-sparse ��Դͨ��vkBindImageMemory ���� vkBindBufferMemory��ʹ��ǰ�����ڴ棬�Ҳ��ܸ��ġ�

			sparse��Դ�İ��ڰ���VK_QUEUE_SPARSE_BINDING_BIT��queue��ִ�У�����Ҫ�����ⲿͬ����
			
			����󶨵� VK_IMAGE_ASPECT_METADATA_BIT���� VkSparseMemoryBind::flags�б������VK_SPARSE_MEMORY_BIND_METADATA_BIT

			����󶨵� mip tail,��VkSparseMemoryBind::flags�б������VK_SPARSE_MEMORY_BIND_METADATA_BIT������󶨵��κ�aspect��mip tail��ʹ��VkSparseImageOpaqueMemoryBindInfo��
			���formatProperties.flags����VK_SPARSE_IMAGE_FORMAT_SINGLE_MIPTAIL_BIT����ֻ��һ��VkSparseMemoryBind���ɣ�����resourceOffset = imageMipTailOffset��size = imageMipTailSize.
			���formatProperties.flags������VK_SPARSE_IMAGE_FORMAT_SINGLE_MIPTAIL_BIT����ÿ��array layerҪ��һ��VkSparseMemoryBind������ resourceOffset = arrayMipTailOffset = imageMipTailOffset + arrayLayer * imageMipTailStride�� size = imageMipTailSize.
			*/

			//Sparse Memory Binding Functions

			/*
			VkSparseMemoryBind�ṹ�壬����Դ��[resourceOffset, resourceOffset + size)��Χ

			���flags ����VK_SPARSE_MEMORY_BIND_METADATA_BIT����resourceOffset =  imageMipTailOffset + imageMipTailStride �� n������imageMipTailOffset, imageMipTailSize, �Լ� imageMipTailStrideΪǰ���ἰ�Ķ�Ӧ��meta aspect��VkSparseImageMemoryRequirements���оٵģ�
			���VkSparseImageMemoryRequirements::formatProperties.flags����VK_SPARSE_IMAGE_FORMAT_SINGLE_MIPTAIL_BIT����imageMipTailStride��Ϊ��0

			���flags ������VK_SPARSE_MEMORY_BIND_METADATA_BIT�������Դ�ķ�Χ�� [0,VkMemoryRequirements::size).��
			*/
			VkSparseMemoryBind sparseMemoryBind{};
			sparseMemoryBind.flags = VK_SPARSE_MEMORY_BIND_METADATA_BIT;//VkSparseMemoryBindFlagBits���ֵλ���룬ָ���󶨲������÷���VK_SPARSE_MEMORY_BIND_METADATA_BIT ָ��ֻ����metadata aspect���ڴ��
			sparseMemoryBind.memory = VkDeviceMemory{/*��������һ����Ч��VkDeviceMemory*/ };//Ϊ����Դ��Χ�󶨵� VkDeviceMemory�������ΪVK_NULL_HANDLE�����ʾ����Դ��ΧΪδ�󶨵�
			sparseMemoryBind.memoryOffset = 0;//Ϊ����Դ��Χ�󶨵� VkDeviceMemory�����е���ʼ�ֽ�ƫ���������memoryΪVK_NULL_HANDLE�����ֵ����
			sparseMemoryBind.resourceOffset = 0;//���ڸ���Դ�е��ֽ�ƫ����
			sparseMemoryBind.size = 1;//ΪҪ�󶨵��ڴ������С
			/*
			VkSparseMemoryBind��Ч�÷�:
			1.���memory ��ΪVK_NULL_HANDLE����memory�Լ�memoryOffset ����ƥ�����Դ���ڴ����󣬲μ�Resource Memory Association p1153
			2.�����ԴΪVkBuffer,��resourceOffset��memoryOffset�Լ�size�����ǵ���vkGetBufferMemoryRequirements�����buffer ��Դ�Ĳ������ص�VkMemoryRequirements.alignment��������
			3.�����ԴΪVkImage,��resourceOffset��memoryOffset�����ǵ���vkGetImageMemoryRequirements�����image ��Դ�Ĳ������ص�VkMemoryRequirements.alignment��������
			4.���memory ��ΪVK_NULL_HANDLE����memory ������VK_MEMORY_PROPERTY_LAZILY_ALLOCATED_BIT����
			5.size �������0��С�ڵ�����Դ��С��ȥresourceOffset��С�ڵ���memory��С��ȥmemoryOffset
			6.resourceOffset ����С����Դ�Ĵ�С
			7.memoryOffset ����С�ڵ���memory��С
			8.���memory��VkExportMemoryAllocateInfo::handleTypes��Ϊ0�������򴴽���ԴʱVkExternalMemoryBufferCreateInfo::handleTypes ���� VkExternalMemoryImageCreateInfo::handleTypes���ٰ���һ��handle type
			9.���memoryͨ��һ��memory import operation�������򴴽���Դʱ������memory���ⲿhandle type���������� VkExternalMemoryBufferCreateInfo::handleTypes ���� VkExternalMemoryImageCreateInfo::handleTypes��

			*/


			//����VK_BUFFER_CREATE_SPARSE_BINDING_BIT������buffer���ڴ�ʹ��VkSparseBufferMemoryBindInfo
			VkSparseBufferMemoryBindInfo sparseBufferMemoryBindInfo{};
			sparseBufferMemoryBindInfo.buffer = VkBuffer{/*��������һ����Ч��VkBuffer*/ };//ָ��Ҫ�󶨵�buffer
			sparseBufferMemoryBindInfo.bindCount = 1;// pBinds��Ԫ�ظ���
			sparseBufferMemoryBindInfo.pBinds = &sparseMemoryBind;//һ�� VkSparseMemoryBind����ָ�룬ָ����Ҫ�󶨵ķ�Χ

			//����VK_IMAGE_CREATE_SPARSE_BINDING_BIT������image��opaque regions���ڴ�ʹ��VkSparseImageOpaqueMemoryBindInfo����Ҫ���ڰ�fully-resident sparse images��partially resident images��mip tail regions ����entire binding range
			VkSparseImageOpaqueMemoryBindInfo sparseImageOpaqueMemoryBindInfo{};
			sparseImageOpaqueMemoryBindInfo.image = VkImage{/*��������һ����Ч��VkImage*/ };//ָ��Ҫ�󶨵�image
			sparseImageOpaqueMemoryBindInfo.bindCount = 1;// pBinds��Ԫ�ظ���
			sparseImageOpaqueMemoryBindInfo.pBinds = &sparseMemoryBind;//һ�� VkSparseMemoryBind����ָ�룬ָ����Ҫ�󶨵ķ�Χ,����κ�Ԫ�ص�flags����VK_SPARSE_MEMORY_BIND_METADATA_BIT�����Ԫ�ض���ķ�Χ�����ڸ�image��metadata aspect ��mip tail region��
		

			//����VK_IMAGE_CREATE_SPARSE_RESIDENCY_BIT������image��sparse image blocks���ڴ�ʹ��VkSparseImageMemoryBindInfo��
			VkSparseImageMemoryBindInfo sparseImageMemoryBindInfo{};
			sparseImageMemoryBindInfo.image = VkImage{/*��������һ����Ч��VkImage*/ };//ָ��Ҫ�󶨵�image
			sparseImageMemoryBindInfo.bindCount = 1;// pBinds��Ԫ�ظ���
			VkSparseImageMemoryBind sparseImageMemoryBind{};
			{
				sparseImageMemoryBind.subresource = VkImageSubresource{ .aspectMask = VK_IMAGE_ASPECT_COLOR_BIT,.mipLevel = 0,.arrayLayer = 0 };//ָ��image���ĸ�resource
				sparseImageMemoryBind.flags = 0;//VkSparseMemoryBindFlagBits���ֵλ���룬ָ���󶨲������÷���VK_SPARSE_MEMORY_BIND_METADATA_BIT ָ��ֻ����metadata aspect���ڴ��
				sparseImageMemoryBind.memory = VkDeviceMemory{/*��������һ����Ч��VkDeviceMemory*/ };//Ϊ��sparse image blocks��Դ��Χ�󶨵� VkDeviceMemory�������ΪVK_NULL_HANDLE�����ʾ����Դ��ΧΪδ�󶨵�
				sparseImageMemoryBind.memoryOffset = 0;//Ϊ��sparse image blocks��Դ��Χ�󶨵� VkDeviceMemory�����е���ʼ�ֽ�ƫ���������memoryΪVK_NULL_HANDLE�����ֵ����
				sparseImageMemoryBind.offset = VkOffset3D{ .x = 0,.y = 0,.z = 0 };//Ϊimage subresource�󶨵�texel����ĵ�һ��texel������
				sparseImageMemoryBind.extent = VkExtent3D{ .width = 1,.height = 1,.depth = 1 };//Ϊimage subresource�󶨵�texel����Ĵ�С��������sparse image block dimensions�������������ǰ󶨵�sparse image blocks�� image subresource�ı߽���ʱ��������offset + extent���� image subresource.��ά��
				/*
				VkSparseImageMemoryBind��Ч�÷�:
				1.���sparseResidencyAliased ����û�п�����������κ���������Դ�󶨵�memory��Χ�����memory�ķ�Χ�����ص�
				2.memory�Լ�memoryOffset ����ƥ���image��Դ���ڴ����󣬲μ�Resource Memory Association p1153
				3.offset.x ������image�Ķ�Ӧsparse image block width��(VkSparseImageFormatProperties::imageGranularity.width)���ı���
				4.extent.width  �������0���ұ�����image�Ķ�Ӧsparse image block width�ı�������(extent.width + offset.x)  �������image subresource��width
				5.offset.y ������image�Ķ�Ӧsparse image block height��(VkSparseImageFormatProperties::imageGranularity.height)���ı���
				6.extent.height  �������0���ұ�����image�Ķ�Ӧsparse image block height�ı�������(extent.height + offset.y)  �������image subresource��height
				7.offset.z ������image�Ķ�Ӧsparse image block depth��(VkSparseImageFormatProperties::imageGranularity.depth)���ı���
				8.extent.depth  �������0���ұ�����image�Ķ�Ӧsparse image block depth�ı�������(extent.depth + offset.z)  �������image subresource��depth
				9.���memory��VkExportMemoryAllocateInfo::handleTypes��Ϊ0�������򴴽���ԴʱVkExternalMemoryBufferCreateInfo::handleTypes ���� VkExternalMemoryImageCreateInfo::handleTypes���ٰ���һ��handle type
				10.���memoryͨ��һ��memory import operation�������򴴽���Դʱ������memory���ⲿhandle type���������� VkExternalMemoryBufferCreateInfo::handleTypes ���� VkExternalMemoryImageCreateInfo::handleTypes��
				*/
			
			}
			sparseImageMemoryBindInfo.pBinds = &sparseImageMemoryBind;//һ�� VkSparseMemoryBind����ָ�룬ָ����Ҫ�󶨵ķ�Χ,����κ�Ԫ�ص�flags����VK_SPARSE_MEMORY_BIND_METADATA_BIT�����Ԫ�ض���ķ�Χ�����ڸ�image��metadata aspect ��mip tail region��
			/*
			VkSparseImageMemoryBindInfo��Ч�÷�:
			1.pBinds��ÿ��Ԫ�ص�subresource.mipLevel����С�ڴ���image��VkImageCreateInfo��mipLevels
			2.pBinds��ÿ��Ԫ�ص�subresource.arrayLayer����С�ڴ���image��VkImageCreateInfo��arrayLayers
			3.pBinds��ÿ��Ԫ�ص�subresource.aspectMask ����Դ���image��VkImageCreateInfo��format����Ч��
			4.image ������VK_IMAGE_CREATE_SPARSE_RESIDENCY_BIT ����
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
					frameBoundaryEXT.sType = VK_STRUCTURE_TYPE_MAX_ENUM;//��Ϊ���Զ�������Զ���Ϊ�Ƿ�ֵ
					frameBoundaryEXT.pNext = nullptr;
					timelineSemaphoreSubmitInfo.sType = VK_STRUCTURE_TYPE_TIMELINE_SEMAPHORE_SUBMIT_INFO;
					timelineSemaphoreSubmitInfo.pNext = nullptr;

				}
			};


			//�ύһ���󶨲�����queue
			VkBindSparseInfo bindSparseInfo{};
			bindSparseInfo.sType = VK_STRUCTURE_TYPE_BIND_SPARSE_INFO;
			BindSparseInfoEXT bindSparseInfoEXT{};
			bindSparseInfo.pNext = &bindSparseInfoEXT.deviceGroupBindSparseInfo;
			bindSparseInfo.waitSemaphoreCount = 1;//Ϊִ������sparse�󶨲���ǰҪ�ȴ���semaphore������
			VkSemaphore waitSemaphore{/*��������һ����Ч��VkSemaphore*/ };
			bindSparseInfo.pWaitSemaphores = &waitSemaphore;//Ϊһ��VkSemaphore ������ָ��ָ������sparse�󶨲���ǰҪ�����semaphore���ⶨ����һ�� semaphore wait operation.p358
			bindSparseInfo.bufferBindCount = 1;//Ϊ����Ҫִ�е�sparse buffer bindings������
			bindSparseInfo.pBufferBinds = &sparseBufferMemoryBindInfo;//һ�� VkSparseBufferMemoryBindInfo������ָ�룬ָ��sparse buffer binding��Ϣ
			bindSparseInfo.imageOpaqueBindCount = 1;//Ϊ����Ҫִ�е�opaque sparse image bindings������
			bindSparseInfo.pImageOpaqueBinds = &sparseImageOpaqueMemoryBindInfo;//һ��  VkSparseImageOpaqueMemoryBindInfo������ָ�룬ָ��opaque sparse image bindings��Ϣ
			bindSparseInfo.imageBindCount = 1;//Ϊ����Ҫִ�е�sparse image bindings������
			bindSparseInfo.pImageBinds = &sparseImageMemoryBindInfo;//һ�� VkSparseImageMemoryBindInfo������ָ�룬ָ��sparse image bindings��Ϣ
			bindSparseInfo.signalSemaphoreCount = 1;//Ϊ����sparse�󶨲���ִ����ɺ�Ҫ������semaphore������
			VkSemaphore signalSemaphore{/*��������һ����Ч��VkSemaphore*/ }; //Ϊһ��VkSemaphore ������ָ��ָ������sparse�󶨲�����ɺ�Ҫ������semaphore���ⶨ����һ��  semaphore signal operation.p357
			bindSparseInfo.pSignalSemaphores = &signalSemaphore; 
			/*
			VkBindSparseInfo��Ч�÷�:
			1.��� pWaitSemaphores ���� pSignalSemaphores���κ�Ԫ����VkSemaphoreTypeΪVK_SEMAPHORE_TYPE_TIMELINE��������pNext�б������һ��VkTimelineSemaphoreSubmitInfo
			2.���pNext�а���һ��VkTimelineSemaphoreSubmitInfo��pWaitSemaphores���κ�Ԫ����VkSemaphoreTypeΪVK_SEMAPHORE_TYPE_TIMELINE��������ýṹ���waitSemaphoreValueCount�������waitSemaphoreCount
			3.���pNext�а���һ��VkTimelineSemaphoreSubmitInfo��pSignalSemaphores���κ�Ԫ����VkSemaphoreTypeΪVK_SEMAPHORE_TYPE_TIMELINE��������ýṹ���waitSemaphoreValueCount�������signalSemaphoreCount
			4.��pSignalSemaphores��ÿ����VkSemaphoreTypeΪVK_SEMAPHORE_TYPE_TIMELINE������semaphore������VkTimelineSemaphoreSubmitInfo::pSignalSemaphoreValues�еĶ�Ӧֵ������ڸ�semaphore��semaphore signal operationִ��ʱsemaphore�ĵ�ǰֵ
			5.��pWaitSemaphores��ÿ����VkSemaphoreTypeΪVK_SEMAPHORE_TYPE_TIMELINE������semaphore������VkTimelineSemaphoreSubmitInfo::pWaitSemaphoreValues�еĶ�Ӧֵ����͸�semaphore�ĵ�ǰֵ��ͬ���ߺ͸�semaphore���κ��ⲿwait ���� signal operation��ֵ�Ĳ��첻����maxTimelineSemaphoreValueDifference
			6.��pSignalSemaphores��ÿ����VkSemaphoreTypeΪVK_SEMAPHORE_TYPE_TIMELINE������semaphore������VkTimelineSemaphoreSubmitInfo::pSignalSemaphoreValues�еĶ�Ӧֵ����͸�semaphore�ĵ�ǰֵ��ͬ���ߺ͸�semaphore���κ��ⲿwait ���� signal operation��ֵ�Ĳ��첻����maxTimelineSemaphoreValueDifference
			*/


			//ָ�����ĸ�ʵ������Դ���ڴ���豸��������Щ������Ӧ�õ���������Ϣ�е�����buffer�Լ�image binding��semaphore��wait�Լ�signal��������resourceDeviceIndex��ָ��������ִ�У�   ����������ýṹ�壬��ɿ���resourceDeviceIndex �Լ�memoryDeviceIndex ��Ϊ0
			VkDeviceGroupBindSparseInfo& deviceGroupBindSparseInfo = bindSparseInfoEXT.deviceGroupBindSparseInfo;
			deviceGroupBindSparseInfo.resourceDeviceIndex = 0;//ָ�����ĸ�ʵ������Դ���豸����
			deviceGroupBindSparseInfo.memoryDeviceIndex = 0;//ָ����ԴҪ���ĸ�ʵ�����ڴ���豸����
			/*
			VkDeviceGroupBindSparseInfo��Ч�÷�:
			1.resourceDeviceIndex�Լ�memoryDeviceIndex ����ͬʱ����Ч���豸����
			2.��������ÿһ��memory�ķ��������memoryDeviceIndexָ�����豸�Ϸ���һ��ʵ��
			*/


			vkQueueBindSparse(VkQueue{/*��������һ����Ч��VkQueue*/ }, 1, & bindSparseInfo, VkFence{/*��������һ����Ч��VkFence*/ }/*�ж���Щ���Ƿ���ɵ�fence*/);
			/*
			vkQueueBindSparse��Ч�÷�:
			1.���fence��ΪVK_NULL_HANDLE����fence�����Ѿ���������fence���ܹ������κ���������queue�ϻ�û�����ָ����queue����
			2.pBindInfo��ÿ��Ԫ�ص�pSignalSemaphores��ÿ��Ԫ�ر�����δ������
			3.��pBindInfo���κ�Ԫ�ص�pWaitSemaphores���κ�Ԫ�ض���һ�����õ�һ��binary semaphore��ִ����queue�ϵ�semaphore wait operation������������queue�ȴ�����ͬ��semaphore
			4.pBindInfo������Ԫ�ص�pWaitSemaphores������Ԫ�����õ�һ����VkSemaphoreTypeΪVK_SEMAPHORE_TYPE_BINARY������semaphore�����semaphore�� signal operation �����Ѿ��ύִ���Ҹ�semaphore������semaphore��signal operationsҲ�����ύִ��
			*/
		}
	}
}

void SparseResourcesAndWindowSystemIntergrationTest::WindowSystemIntegration_WSI_Test()
{
	/*
	vulkan����Ⱦ������Ҫ��ʾ����Ҫͨ��window system integration (WSI)�ĸ�ƽ̨�������ʾ��չ������ʾ
	*/


	//WSI Platform  �μ�p2022
	{
		/*
		ƽ̨�ǶԴ���ϵͳ������ϵͳ�ȵĳ�����һЩ���Ӱ���MS Windows����׿ϵͳ��Waylandϵͳ��Vulkan API����Ϊÿ��ƽ̨��һ�ֶ��صķ�ʽ���м��ɡ�
		
		Vulkan API�������κ����͵�ƽ̨����vulkan �����ض���ƽ̨��WSI��չ��ÿ����չ�������ض���ʹ��WSI��ƽ̨�Ĺ��ܡ�ʹ����Щ��չ���� Window System-Specific Header Control p5304��¼ �ж����Ԥ������Ž��п��ƣ��򵥽�����Ҫ�ڰ���vulkan�����ͷ�ļ�ǰ����һЩ������ȷ��ʹ�õ�ƽ̨
		*/


	}

	//WSI Surface  �μ�p3022
	{
		/*
		ԭ��ƽ̨��surface����window������Ϊsurface ���󣬼� VkSurfaceKHR ��

		 VK_KHR_surface��չ������VkSurfaceKHR������ƽ̨���ṩ�䴴�������VkSurfaceKHR����ĺ����ӿڡ�
		
		*/

		VkSurfaceKHR surface{};

		//Android Platform  �μ�p3023
		{
			//Ϊ Android native window����һ�� VkSurfaceKHR����
			VkAndroidSurfaceCreateInfoKHR androidSurfaceCreateInfoKHR{};
			androidSurfaceCreateInfoKHR.sType = VK_STRUCTURE_TYPE_ANDROID_SURFACE_CREATE_INFO_KHR;
			androidSurfaceCreateInfoKHR.pNext = nullptr;
			androidSurfaceCreateInfoKHR.flags = 0;//����δ��ʹ��
			ANativeWindow* nativeWindow{};//һ��ANativeWindowֻ�ܶ�Ӧһ��VkSurfaceKHR����ANativeWindow����һ��VkSurfaceKHR��ANativeWindow�����ü������һ���������һ�������� ANativeWindow������ Android NDK headers.
			androidSurfaceCreateInfoKHR.window = nativeWindow;//Ϊ��surface������ANativeWindow��ָ�룬������һ����Ч��ANativeWindow��ָ��

			//����
			vkCreateAndroidSurfaceKHR(instance, &androidSurfaceCreateInfoKHR, nullptr, &surface);



			//����
			vkDestroySurfaceKHR(instance, surface, nullptr);

			/*
			swapchain��imageά�������ƥ��surface���������ʾ��ʱ���������,��surface��currentExtent��surface��minImageExtentΪ(1,1),maxImageExtentȡ�������Ѷ�
			
			*/
		}


		//Wayland Platform  �μ�3025
		{
			/*
			Wayland��linuxϵͳ��Ĭ�ϴ���ϵͳx11���ִ����Ʒ����һ��ͨ��Э�飬����X window��ʾ��������Ӧ�ó���֮�����Ϣ���ݡ�
			*/

			//ΪWayland surface����һ��VkSurfaceKHR
			VkWaylandSurfaceCreateInfoKHR waylandSurfaceCreateInfoKHR{};
			waylandSurfaceCreateInfoKHR.sType = VK_STRUCTURE_TYPE_WAYLAND_SURFACE_CREATE_INFO_KHR;
			waylandSurfaceCreateInfoKHR.pNext = nullptr;
			waylandSurfaceCreateInfoKHR.flags = 0;//����δ��ʹ��
			wl_display* wl_display{};
			waylandSurfaceCreateInfoKHR.display = wl_display;//Ϊ��surface������wl_display��ָ�룬������һ����Ч��wl_display��ָ��
			wl_surface* wl_surf{};
			waylandSurfaceCreateInfoKHR.surface = wl_surf;//Ϊ��surface������wl_surface��ָ�룬������һ����Ч��wl_surface��ָ��

			//����
			vkCreateWaylandSurfaceKHR(instance, &waylandSurfaceCreateInfoKHR, nullptr, &surface);

			//����
			vkDestroySurfaceKHR(instance, surface, nullptr);
			
			
			/*
			currentExtent��һ������ֵ (0xFFFFFFFF, 0xFFFFFFFF),ָ��surface��ά��ȡ����swapchain��ά�ȣ�����Ӧ������swapchian��ά��Ϊ���٣�����һ��ͼԪ����ʾ�ˣ�minImageExtent��Ϊ(1,1),maxImageExtent��Ϊ֧�ֵ�surface�����ά��
			
			��surface֧��VK_PRESENT_MODE_MAILBOX_KHR

			*/
		}


		//Win32 Platform  �μ�p3027
		{
			//ΪWin32 window����һ�� VkSurfaceKHR����
			VkWin32SurfaceCreateInfoKHR win32SurfaceCreateInfoKHR{};
			win32SurfaceCreateInfoKHR.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
			win32SurfaceCreateInfoKHR.pNext = nullptr;
			win32SurfaceCreateInfoKHR.flags = 0;//����δ��ʹ��
			HWND windowHandle{};//������ʾһ��window����
			win32SurfaceCreateInfoKHR.hwnd = windowHandle;//Ϊ��surface������HWND���ڣ���������Ч��HWND
			HINSTANCE hInstance{};//���ڱ�ʾһ�������ʵ��
			win32SurfaceCreateInfoKHR.hinstance = hInstance;//Ϊ��surface������win32 HINSTANCE����������Ч��win32 HINSTANCE
			
			//����
			vkCreateWin32SurfaceKHR(instance, &win32SurfaceCreateInfoKHR, nullptr, &surface);



			//����
			vkDestroySurfaceKHR(instance, surface, nullptr);

			/*
			 minImageExtent, maxImageExtent, �Լ� currentExtent��Զ���ڴ��ڴ�С
			
			��swapchain��surface�ĵ�ǰά�ȴ�С��ͬ�����û��VkSwapchainPresentScalingCreateInfoEXTָ����δ������ֲ�ͬ����ô��ҪΪsurface���´����µ�swapchain
			*/
		}

		// XCB Platform  �μ�3030
		{
			/*
			X11 window��linuxϵͳ��Ĭ�ϴ���ϵͳ
			*/

			//ʹ�� XCB �ͻ��˿� Ϊ X11 window����һ��VkSurfaceKHR
			VkXcbSurfaceCreateInfoKHR xcbSurfaceCreateInfoKHR{};
			xcbSurfaceCreateInfoKHR.sType = VK_STRUCTURE_TYPE_XCB_SURFACE_CREATE_INFO_KHR;
			xcbSurfaceCreateInfoKHR.pNext = nullptr;
			xcbSurfaceCreateInfoKHR.flags = 0;//����δ��ʹ��
			xcb_connection_t* connection{};
			xcbSurfaceCreateInfoKHR.connection = connection;//Ϊ��surface���� X ��������xcb_connection_t��ָ�룬������һ����Ч��X11��xcb_connection_t��ָ��
			xcb_window_t window{};
			xcbSurfaceCreateInfoKHR.window = window;//Ϊ��surface���� X11 window��xcb_window_t��������һ����Ч X11 window��xcb_window_t

			//����
			vkCreateXcbSurfaceKHR(instance, &xcbSurfaceCreateInfoKHR, nullptr, &surface);

			//����
			vkDestroySurfaceKHR(instance, surface, nullptr);
			/*
			 minImageExtent, maxImageExtent, �Լ� currentExtent��Զ���ڴ��ڴ�С
			
			��swapchain��surface�ĵ�ǰά�ȴ�С��ͬ�����û��VkSwapchainPresentScalingCreateInfoEXTָ����δ������ֲ�ͬ����ô��ҪΪsurface���´����µ�swapchain
			*/
		}


		//Xlib Platform  �μ�3032
		{
			/*
			X11 window��linuxϵͳ��Ĭ�ϴ���ϵͳ
			*/

			//ʹ��Xlib�ͻ��˿� Ϊ X11 window����һ��VkSurfaceKHR
			VkXlibSurfaceCreateInfoKHR xlibSurfaceCreateInfoKHR{};
			xlibSurfaceCreateInfoKHR.sType = VK_STRUCTURE_TYPE_XLIB_SURFACE_CREATE_INFO_KHR;
			xlibSurfaceCreateInfoKHR.pNext = nullptr;
			xlibSurfaceCreateInfoKHR.flags = 0;//����δ��ʹ��
			Display* display{};
			xlibSurfaceCreateInfoKHR.dpy = display;//Ϊ��surface���� X ��������Xlib Display connection��ָ�룬������һ����Ч��Xlib Display��ָ��
			Window window{};
			xlibSurfaceCreateInfoKHR.window = window;//Ϊ��surface������ Xlib Window��������һ����Ч�� Xlib Window

			//����
			vkCreateXlibSurfaceKHR(instance, &xlibSurfaceCreateInfoKHR, nullptr, &surface);

			//����
			vkDestroySurfaceKHR(instance, surface, nullptr);
			
			/*
			 minImageExtent, maxImageExtent, �Լ� currentExtent��Զ���ڴ��ڴ�С

			��swapchain��surface�ĵ�ǰά�ȴ�С��ͬ�����û��VkSwapchainPresentScalingCreateInfoEXTָ����δ������ֲ�ͬ����ô��ҪΪsurface���´����µ�swapchain
			*/
		}


		//DirectFB Platform  �μ�3035
		{
			/*
			DirectFB��Ƕ��ʽ�豸��ͼ����ʾ��
			*/

			//Ϊ DirectFB surface ����һ��VkSurfaceKHR
			VkDirectFBSurfaceCreateInfoEXT directFBSurfaceCreateInfoEXT{};
			directFBSurfaceCreateInfoEXT.sType = VK_STRUCTURE_TYPE_DIRECTFB_SURFACE_CREATE_INFO_EXT;
			directFBSurfaceCreateInfoEXT.pNext = nullptr;
			directFBSurfaceCreateInfoEXT.flags = 0;//����δ��ʹ��
			IDirectFB* dfb{};
			directFBSurfaceCreateInfoEXT.dfb = dfb;//ΪDirectFB �� IDirectFB main interface��ָ�룬������һ����Ч��DirectFB IDirectFB��ָ��
			IDirectFBSurface* iSurface{};
			directFBSurfaceCreateInfoEXT.surface = iSurface;//ΪIDirectFBSurface surface interface��ָ�룬������һ����Ч�� DirectFB IDirectFBSurfaceָ��

			//����
			vkCreateDirectFBSurfaceEXT(instance, &directFBSurfaceCreateInfoEXT, nullptr, &surface);

			//����
			vkDestroySurfaceKHR(instance, surface, nullptr);

			/*
			 minImageExtent, maxImageExtent, �Լ� currentExtent��Զ���ڴ��ڴ�С

			*/
		}


		// Fuchsia Platform �μ�3037
		{
			/*
			Fuchsia��google�������ƶ��˲���ϵͳ
			*/

			//Ϊ  Fuchsia ImagePipe����һ��VkSurfaceKHR
			VkImagePipeSurfaceCreateInfoFUCHSIA imagePipeSurfaceCreateInfoFUCHSIA{};
			imagePipeSurfaceCreateInfoFUCHSIA.sType = VK_STRUCTURE_TYPE_IMAGEPIPE_SURFACE_CREATE_INFO_FUCHSIA;
			imagePipeSurfaceCreateInfoFUCHSIA.pNext = nullptr;
			imagePipeSurfaceCreateInfoFUCHSIA.flags = 0;//����δ��ʹ��
			zx_handle_t imagePipeHandle{};
			imagePipeSurfaceCreateInfoFUCHSIA.imagePipeHandle = imagePipeHandle;//Ϊsurface���������õ�ImagePipe�� zx_handle_t��������һ����Ч�� zx_handle_t

			//����
			vkCreateImagePipeSurfaceFUCHSIA(instance, &imagePipeSurfaceCreateInfoFUCHSIA, nullptr, &surface);

			//����
			vkDestroySurfaceKHR(instance, surface, nullptr);

			/*
			 currentExtent����ֵ (0xFFFFFFFF, 0xFFFFFFFF)��ʾsurface�Ĵ�Сȡ����swapchian�Ĵ�С

			*/
		}



		// Google Games Platform �μ�3039
		{
			/*
			 Google Games Platform��google����Ϸƽ̨
			*/

			//ΪGoogle Games Platform stream descriptor����һ��VkSurfaceKHR
			VkStreamDescriptorSurfaceCreateInfoGGP streamDescriptorSurfaceCreateInfoGGP{};
			streamDescriptorSurfaceCreateInfoGGP.sType = VK_STRUCTURE_TYPE_STREAM_DESCRIPTOR_SURFACE_CREATE_INFO_GGP;
			streamDescriptorSurfaceCreateInfoGGP.pNext = nullptr;
			streamDescriptorSurfaceCreateInfoGGP.flags = 0;//����δ��ʹ��
			GgpStreamDescriptor streamDescriptor{};
			streamDescriptorSurfaceCreateInfoGGP.streamDescriptor = streamDescriptor;//Ϊsurface���������õ� GGP stream descriptor��GgpStreamDescriptor��������һ����Ч�� GgpStreamDescriptor

			//����
			vkCreateStreamDescriptorSurfaceGGP(instance, &streamDescriptorSurfaceCreateInfoGGP, nullptr, &surface);

			//����
			vkDestroySurfaceKHR(instance, surface, nullptr);

			/*
			�ڸ�ƽ̨��surface extentΪ��̬�ģ�minImageExtent�������1080p��maxImageExtent����С��1080p,currentExtent��ӳ��ǰ��ѡ��ķֱ���

			swapchain�Ĵ�Сһ��ʹ��surface�ĵ�ǰ��С��������߲���ƥ������swapchain��image��ʾ�������ŵ�surface��ά���ҷ���VK_SUBOPTIMAL_KHR��������ʾʧ�ܷ���VK_ERROR_OUT_OF_DATE_KHR
			*/
		}

		//iOS Platform �μ�3039
		{


			//ΪiOS UIView ����CAMetalLayer����һ��VkSurfaceKHR
			VkIOSSurfaceCreateInfoMVK iOSSurfaceCreateInfoMVK{};
			iOSSurfaceCreateInfoMVK.sType = VK_STRUCTURE_TYPE_IOS_SURFACE_CREATE_INFO_MVK;
			iOSSurfaceCreateInfoMVK.pNext = nullptr;
			iOSSurfaceCreateInfoMVK.flags = 0;//����δ��ʹ��
			void*  view{};
			iOSSurfaceCreateInfoMVK.pView = view;//Ϊ CAMetalLayer ����UIView������
			/*
			VkIOSSurfaceCreateInfoMVK��Ч�÷�:
			1.���pViewΪһ��CAMetalLayer�����������һ����Ч��CAMetalLayer
			2.���pViewΪһ��UIView�����������һ����Ч��UIView������ײ����Ϊһ��CAMetalLayer���͵�CALayer����vkCreateIOSSurfaceMVK���������̵߳���
			*/

			//����
			vkCreateIOSSurfaceMVK(instance, &iOSSurfaceCreateInfoMVK, nullptr, &surface);

			//����
			vkDestroySurfaceKHR(instance, surface, nullptr);

		}

		// macOS Platform �μ�3043
		{


			//Ϊ macOS NSView ���� CAMetalLayer����һ��VkSurfaceKHR
			VkMacOSSurfaceCreateInfoMVK macOSSurfaceCreateInfoMVK{};
			macOSSurfaceCreateInfoMVK.sType = VK_STRUCTURE_TYPE_IOS_SURFACE_CREATE_INFO_MVK;
			macOSSurfaceCreateInfoMVK.pNext = nullptr;
			macOSSurfaceCreateInfoMVK.flags = 0;//����δ��ʹ��
			void* view{};
			macOSSurfaceCreateInfoMVK.pView = view;//Ϊ CAMetalLayer ���� NSView������
			/*
			VkMacOSSurfaceCreateInfoMVK��Ч�÷�:
			1.���pViewΪһ��CAMetalLayer�����������һ����Ч��CAMetalLayer
			2.���pViewΪһ�� NSView�����������һ����Ч�� NSView������ײ����Ϊһ��CAMetalLayer���͵�CALayer���� vkCreateMacOSSurfaceMVK���������̵߳���
			*/

			//����
			vkCreateMacOSSurfaceMVK(instance, &macOSSurfaceCreateInfoMVK, nullptr, &surface);

			//����
			vkDestroySurfaceKHR(instance, surface, nullptr);

		}


		//VI Platform �μ�3045
		{
			/*
			VI Platform�� �Ӿ�ʶ��ϵͳ
			*/

			//Ϊnn::vi::Layer ����һ��VkSurfaceKHR,����nn::vi::GetNativeWindow��ѯlayer�� native handle,
			VkViSurfaceCreateInfoNN viSurfaceCreateInfoNN{};
			viSurfaceCreateInfoNN.sType = VK_STRUCTURE_TYPE_VI_SURFACE_CREATE_INFO_NN;
			viSurfaceCreateInfoNN.pNext = nullptr;
			viSurfaceCreateInfoNN.flags = 0;//����δ��ʹ��
			void* window{};//ÿ��window��Ӧһ��surface
			viSurfaceCreateInfoNN.window = window;//Ϊsurface������ nn::vi::Layer�� nn::vi::NativeWindowHandle��������һ����Ч��  nn::vi::NativeWindowHandle

			//����
			vkCreateViSurfaceNN(instance, &viSurfaceCreateInfoNN, nullptr, &surface);

			//����
			vkDestroySurfaceKHR(instance, surface, nullptr);

			/*
			 ���window��һ���ض��Ĵ�С��������currentExtent��ʾ�����С��swapchain�Ĵ�СӦ��Ϊ�����С������currentExtentΪ����ֵ (0xFFFFFFFF, 0xFFFFFFFF)��ʾsurface�Ĵ�Сȡ����swapchian�Ĵ�С
			*/
		}


		//Metal Platform �μ�3047
		{
			/*
			Metal ��һ����ͼ�κͼ�����ܼ��ɵ��ִ��� API���ṩ��ǿ�����ɫ���ԣ�רΪ Apple ƽ̨��Ʋ��������Ż���
			*/

			//Ϊ CAMetalLayer����һ��VkSurfaceKHR
			VkMetalSurfaceCreateInfoEXT metalSurfaceCreateInfoEXT{};
			metalSurfaceCreateInfoEXT.sType = VK_STRUCTURE_TYPE_METAL_SURFACE_CREATE_INFO_EXT;
			metalSurfaceCreateInfoEXT.pNext = nullptr;
			metalSurfaceCreateInfoEXT.flags = 0;//����δ��ʹ��
			void* metalLayer{};
			metalSurfaceCreateInfoEXT.pLayer = metalLayer;//Ϊ CAMetalLayer ������,��ʾһ������Ⱦ�Ľ���
	

			//����
			vkCreateMetalSurfaceEXT(instance, &metalSurfaceCreateInfoEXT, nullptr, &surface);

			//����
			vkDestroySurfaceKHR(instance, surface, nullptr);

		}


		//QNX Screen Platform �μ�3047
		{
			/*
			QNX Screen Platform ��һ�����ڿͻ���/����������Ļͼ����ϵͳ��
			*/

			//ΪQNX Screen surface ����һ��VkSurfaceKHR
			VkScreenSurfaceCreateInfoQNX screenSurfaceCreateInfoQNX{};
			screenSurfaceCreateInfoQNX.sType = VK_STRUCTURE_TYPE_SCREEN_SURFACE_CREATE_INFO_QNX;
			screenSurfaceCreateInfoQNX.pNext = nullptr;
			screenSurfaceCreateInfoQNX.flags = 0;//����δ��ʹ��
			_screen_context* contex{};
			screenSurfaceCreateInfoQNX.context = contex;//Ϊsurface������QNX Screen context��������һ����Ч��  QNX Screen _screen_contextָ��
			_screen_window* window{};
			screenSurfaceCreateInfoQNX.window = window;//Ϊsurface������QNX Screen  window��������һ����Ч��  QNX Screen _screen_windowָ��



			//����
			vkCreateScreenSurfaceQNX(instance, &screenSurfaceCreateInfoQNX, nullptr, &surface);

			//����
			vkDestroySurfaceKHR(instance, surface, nullptr);

		}

		// Platform-Independent Information  �μ�p3051
		{
			/*
			һ��������ϣ�VkSurfaceKHR����Ϳ����������չ��������չ��ʹ�ã��ر���VK_KHR_swapchain��չ��
			*/

			vkDestroySurfaceKHR(instance, VkSurfaceKHR{/*��������һ����Ч��VkSurfaceKHR*/}, nullptr);
			/*
			vkDestroySurfaceKHR��Ч�÷�:
			1.����VkSwapchainKHR�����������ƽ̨��native surface֮ǰ����
			2.���������VkSurfaceKHRʱ�ṩ��VkAllocationCallbacks���������callbacksҲ��Ҫ�ṩһ�����ݵ�
			3.���������VkSurfaceKHRʱû���ṩVkAllocationCallbacks���������pAllocator����ΪNULL

			*/

		}

	}


}



NS_TEST_END