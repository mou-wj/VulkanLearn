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
typedef uint32_t GgpFrameToken;//δ���������Լ�����
#include "vulkan/vulkan_ggp.h"

#include "vulkan/vulkan_ios.h"

#include "vulkan/vulkan_macos.h"

#include "vulkan/vulkan_vi.h"

#include "vulkan/vulkan_metal.h"
//screen qnx
struct _screen_context {};//δ���������Լ�����
struct _screen_window {};//δ���������Լ�����
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



	//Presenting Directly to Display Devices  �μ�p3052
	{
		/*
		����Щ�����У�vulkan����ֱ�ӽ���Ⱦ�����ʾ����ʾ�豸�϶�����Ҫ�м��windowing system���롣�ڱ���Ƕ��ʽϵͳ�к�����

		VK_KHR_display��չ���ṩ����صĺ�����������ʾ�豸��ص�VkSurfaceKHR
		*/

		//Display Enumeration  �μ�p3052
		{
			//��ʾ�豸�� VkDisplayKHR��ʾ
			VkDisplayKHR displayKHR{};

			//��ѯ���õ���ʾ�豸display��Ϣ
			uint32_t displayPropertiesCount = 0;
			std::vector<VkDisplayPropertiesKHR> displayPropertiesKHRs{};
			vkGetPhysicalDeviceDisplayPropertiesKHR(physicalDevice, &displayPropertiesCount, nullptr);
			displayPropertiesKHRs.resize(displayPropertiesCount);
			vkGetPhysicalDeviceDisplayPropertiesKHR(physicalDevice, &displayPropertiesCount, displayPropertiesKHRs.data());//���践�سɹ���һ��Ԫ��
			VkDisplayPropertiesKHR& displayPropertiesKHR = displayPropertiesKHRs[0];
			displayPropertiesKHR.display = VkDisplayKHR{/*��������һ����Ч��VkDisplayKHR*/ };//��һ�����������ָ��������������ʾ�����˾������Vulkanʵ����������������Ч��
			displayPropertiesKHR.displayName = "name";//ΪNULL�����Կ��ַ���β��UTF-8�ַ�����������ʾ�豸���ַ����������ΪNULL����Vulkanʵ����������������Ч��
			displayPropertiesKHR.persistentContent = VK_FALSE;//��֪��ʾ���Ƿ�֧�� ��ˢ��/�ڲ� ���塣���ΪVK_TRUE��Ӧ�ó�����Զ���Դ���ʾ�����Ľ������ύ�־ñ�����ǰ������
			displayPropertiesKHR.physicalDimensions = VkExtent2D{ .width = 1,.height = 1 };//������ʾ���ɼ����ֵ������Ⱥ͸߶ȣ���λΪ����
			displayPropertiesKHR.physicalResolution = VkExtent2D{ .width = 1,.height = 1 };//������ʾ��������ԭ������ѡ�ֱ���
			displayPropertiesKHR.planeReorderPossible = VK_TRUE;//��ʾ�����ʾ���ϵ�ƽ���Ƿ���Ըı����ǵ�z˳���������VK_TRUE��Ӧ�ó������������ڱ˴˵��κ�˳���������������ʾ���ϵ�ƽ��
			displayPropertiesKHR.supportedTransforms = VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR;//ΪVkSurfaceTransformFlagBitsKHR���ֵλ���룬ָ����ʾ��֧�ֵı任����


			//��ѯ���õ���ʾ�豸display��Ϣ 2
			uint32_t displayPropertiesCount2 = 0;
			std::vector<VkDisplayProperties2KHR> displayProperties2KHRs{};
			vkGetPhysicalDeviceDisplayProperties2KHR(physicalDevice, &displayPropertiesCount2, nullptr);
			displayProperties2KHRs.resize(displayPropertiesCount);
			vkGetPhysicalDeviceDisplayProperties2KHR(physicalDevice, &displayPropertiesCount, displayProperties2KHRs.data());//���践�سɹ���һ��Ԫ��
			VkDisplayProperties2KHR& displayProperties2KHR = displayProperties2KHRs[0];
			displayProperties2KHR.sType = VK_STRUCTURE_TYPE_DISPLAY_PROPERTIES_2_KHR;
			displayProperties2KHR.pNext = nullptr;
			displayProperties2KHR.displayProperties = displayPropertiesKHRs[0];//VkDisplayPropertiesKHR���ͣ�ǰ���Ѿ��ἰ�����ﲻ�ٸ���

			
			//����Щƽ̨�ϣ����display�Ѿ���ĳЩ���ڻ���Ӧ�ó���ʹ���ˣ�����Ͳ����������ط�����ʹ�ã���������������¾���Ҫ�Ȼ�ȡ����ʾ�豸���ܽ���ʹ��
			
				//��ѯX11 server�Ͽ�ֱ�ӷ��ʵ���ʾ�豸�����Ȩ
				Display* dpy{};
				vkAcquireXlibDisplayEXT(physicalDevice, dpy/*dpy��Ϊ��ǰӵ����ʾ�豸VkDisplayKHR display�ĵ� X11 server������*/, VkDisplayKHR{/*��������һ����Ч��VkDisplayKHR*/ }/*display,Ϊvulkan����Ҫ���Ƶ���ʾ�豸*/);

				//����ȡX11 server�ϵ���ʾ�豸ʱ��Ӧ�ó��򻹿���ϣ��ʹ�ñ������������VkDisplayKHR�����ö�ٺͱ�ʶ���ǡ���ȷ����X11 RandR�����Ӧ��VkDisplayKHR���:
				vkGetRandROutputDisplayEXT(physicalDevice, dpy/*dpy��Ϊ ��ѯ��rrOutput�ĵ� X11 server������*/, 0/*rrOutput,һ�� X11 RandR output ID.*/, &displayKHR/*pDisplay,Ϊ�����صĶ�Ӧ�� VkDisplayKHR handle.*/);


				//��ѯWindows 10�Ͽ�ֱ�ӷ��ʵ���ʾ�豸�����Ȩ
				vkAcquireWinrtDisplayNV(physicalDevice, VkDisplayKHR{/*��������һ����Ч��VkDisplayKHR*/ }/*display,Ϊvulkan����Ҫ���Ƶ���ʾ�豸*/);

				//����ȡWindows 10�ϵ���ʾ�豸ʱ��Ӧ�ó��򻹿���ϣ��ʹ�ñ������������VkDisplayKHR�����ö�ٺͱ�ʶ���ǡ���ȷ����winrt::Windows::Devices::Display::Core::DisplayTarget��Ӧ��VkDisplayKHR���:
				vkGetWinrtDisplayNV(physicalDevice, 0/*deviceRelativeId,  "DisplayTarget" �� "AdapterRelativeId" ����ֵ����"Id"ƥ��physicalDevice��VkPhysicalDeviceIDProperties��deviceLUID��"DisplayAdapter"�о�.*/, &displayKHR/*pDisplay,Ϊ�����صĶ�Ӧ�� VkDisplayKHR handle.*/);


				//��ѯDirect Rendering Manager (DRM) interface�Ͽ�ֱ�ӷ��ʵ���ʾ�豸�����Ȩ
				vkAcquireDrmDisplayEXT(physicalDevice, 0/*drmFd��DRM primary file descriptor.*/, VkDisplayKHR{/*��������һ����Ч��VkDisplayKHR*/ }/*display,Ϊvulkan����Ҫ���Ƶ���ʾ�豸*/);

				//�ڻ�ȡDirect Rendering Manager (DRM) interface�ϵ���ʾ�豸ǰ������ͨ��һ��VkDisplayKHR�������ʶʹ��connectorId����ʾ�豸
				vkGetDrmDisplayEXT(physicalDevice, 0/*drmFd��DRM primary file descriptor.*/, 0/*connectorId���ض�DRM connector�ı�ʶ.*/, &displayKHR/*pDisplay,Ϊ�����صĶ�Ӧ�� VkDisplayKHR handle.*/);

				//�ͷ��Ѿ���ȡ����ʾ�豸
				vkReleaseDisplayEXT(physicalDevice, displayKHR/*display ,Ҫ�ͷſ��Ƶ���ʾ�豸.*/);
			


			//ͼԪ����ʾ�豸��plane�Ͻ�����ʾ��һ����ʾ�豸����֧��һ��plane��plane���Ա��ѵ��ͻ�ϣ�����һ����ʾ���Ϻϳɶ��ͼ��
			
				//��ѯplane������
				uint32_t displayPlanePropertiesKHRCount = 0;
				std::vector<VkDisplayPlanePropertiesKHR> displayPlanePropertiesKHRs{};
				vkGetPhysicalDeviceDisplayPlanePropertiesKHR(physicalDevice, &displayPlanePropertiesKHRCount, nullptr);
				displayPlanePropertiesKHRs.resize(displayPlanePropertiesKHRCount);
				vkGetPhysicalDeviceDisplayPlanePropertiesKHR(physicalDevice, &displayPlanePropertiesKHRCount, displayPlanePropertiesKHRs.data());//����ɹ�������һ��Ԫ��
				VkDisplayPlanePropertiesKHR &displayPlanePropertiesKHR = displayPlanePropertiesKHRs[0];
				displayPlanePropertiesKHR.currentDisplay = VkDisplayKHR{/*��������һ����Ч��VkDisplayKHR*/};//Ϊ��plane��ǰ������display��VkDisplayKHR��������û�й����κ���ʾ�豸��������ΪVK_NULL_HANDLE
				displayPlanePropertiesKHR.currentStackIndex = 0;//Ϊ��ǰplane��z-order,��ֵ��0������vkGetPhysicalDeviceDisplayPlanePropertiesKHR���ص�pPropertyCount�е�ֵ֮��


				//��ѯplane������ 2
				uint32_t displayPlaneProperties2KHRCount = 0;
				std::vector<VkDisplayPlaneProperties2KHR> displayPlaneProperties2KHRs{};
				vkGetPhysicalDeviceDisplayPlaneProperties2KHR(physicalDevice, &displayPlaneProperties2KHRCount, nullptr);
				displayPlaneProperties2KHRs.resize(displayPlaneProperties2KHRCount);
				vkGetPhysicalDeviceDisplayPlaneProperties2KHR(physicalDevice, &displayPlaneProperties2KHRCount, displayPlaneProperties2KHRs.data());//����ɹ�������һ��Ԫ��
				VkDisplayPlaneProperties2KHR& displayPlaneProperties2KHR = displayPlaneProperties2KHRs[0];
				displayPlaneProperties2KHR.sType = VK_STRUCTURE_TYPE_DISPLAY_PLANE_PROPERTIES_2_KHR;
				displayPlaneProperties2KHR.pNext = nullptr;
				displayPlaneProperties2KHR.displayPlaneProperties = displayPlanePropertiesKHRs[0];//VkDisplayPlanePropertiesKHR���ͣ�ǰ���Ѿ������������ﲻ�ٸ���


				//ȷ���ĸ�plane�ǿ��õ�
				uint32_t displayCount = 0;
				std::vector<VkDisplayKHR> surportDisplayKHRs{};
				vkGetDisplayPlaneSupportedDisplaysKHR(physicalDevice, 0/*planeIndex,Ϊ��Ӧ����ʹ�õ�plane����������0��ʼ����physical��plane����һ������vkGetPhysicalDeviceDisplayPlanePropertiesKHR���صļ���ֵ*/, &displayCount, nullptr);
				surportDisplayKHRs.resize(displayCount);
				vkGetDisplayPlaneSupportedDisplaysKHR(physicalDevice, 0/*planeIndex,Ϊ��Ӧ����ʹ�õ�plane����������0��ʼ����physical��plane����һ������vkGetPhysicalDeviceDisplayPlanePropertiesKHR���صļ���ֵ*/, &displayCount, surportDisplayKHRs.data());//����ɹ�����һ��Ԫ��





				//��ʾģʽ  �μ�p3066

					//��ʾģʽ��VkDisplayModeKHR ��ʾ
				VkDisplayModeKHR displayModeKHR{};

				//һ����ʾ�豸֧��һ�����߶����ʾģʽ
				// ��ѯ��ʾ��������ʾģʽ
				uint32_t displayModePropertiesKHRCount = 0;
				std::vector<VkDisplayModePropertiesKHR> displayModePropertiesKHRs{};
				vkGetDisplayModePropertiesKHR(physicalDevice, displayKHR, &displayModePropertiesKHRCount, nullptr);
				displayModePropertiesKHRs.resize(displayModePropertiesKHRCount);
				vkGetDisplayModePropertiesKHR(physicalDevice, displayKHR, &displayModePropertiesKHRCount, displayModePropertiesKHRs.data());//����ɹ�������һ��Ԫ��
				VkDisplayModePropertiesKHR& displayModePropertiesKHR = displayModePropertiesKHRs[0];
				displayModePropertiesKHR.displayMode = VkDisplayModeKHR{/*��������һ����Ч��VkDisplayModeKHR*/ };//Ϊdisplay mode�ľ�����˾������Vulkanʵ����������������Ч��
				displayModePropertiesKHR.parameters = VkDisplayModeParametersKHR{ .visibleRegion = VkExtent2D{.width = 1,.height = 1},/*Ϊ���������2D��Χ��width��height�������0 */
																				  .refreshRate = 256000 /*Ϊ��ʾ��ÿ��ˢ�µĴ�������1000����ֵ�������0*/ };//VkDisplayModeParametersKHR�ṹ�壬������display mode��صĲ���


				// ��ѯ��ʾ��������ʾģʽ2
				uint32_t displayModeProperties2KHRCount = 0;
				std::vector<VkDisplayModeProperties2KHR> displayModeProperties2KHRs{};
				vkGetDisplayModeProperties2KHR(physicalDevice, displayKHR, &displayModeProperties2KHRCount, nullptr);
				displayModeProperties2KHRs.resize(displayModeProperties2KHRCount);
				vkGetDisplayModeProperties2KHR(physicalDevice, displayKHR, &displayModeProperties2KHRCount, displayModeProperties2KHRs.data());//����ɹ�������һ��Ԫ��
				VkDisplayModeProperties2KHR& displayModeProperties2KHR = displayModeProperties2KHRs[0];
				displayModeProperties2KHR.sType = VK_STRUCTURE_TYPE_DISPLAY_MODE_PROPERTIES_2_KHR;
				displayModeProperties2KHR.pNext = nullptr;
				displayModeProperties2KHR.displayModeProperties = displayModePropertiesKHRs[0];//VkDisplayModePropertiesKHR���ͣ�ǰ���Ѿ��������ˣ����ﲻ�ٸ���


				//Ϊ��ʾ�������������ʾģʽ
				VkDisplayModeCreateInfoKHR displayModeCreateInfoKHR{};
				displayModeCreateInfoKHR.sType = VK_STRUCTURE_TYPE_DISPLAY_MODE_CREATE_INFO_KHR;
				displayModeCreateInfoKHR.pNext = nullptr;
				displayModeCreateInfoKHR.flags = 0;//����δ��ʹ��,����Ϊ0
				displayModeCreateInfoKHR.parameters = VkDisplayModeParametersKHR{ .visibleRegion = VkExtent2D{.width = 1,.height = 1},/*Ϊ���������2D��Χ��width��height�������0 */
																				  .refreshRate = 256000 /*Ϊ��ʾ��ÿ��ˢ�µĴ�������1000����ֵ�������0*/ };//VkDisplayModeParametersKHR�ṹ�壬�����������µ�display mode��صĲ���������ò����͵�ǰ��ʾ�������ݣ��򴴽���ʱ��᷵��VK_ERROR_INITIALIZATION_FAILED.
				vkCreateDisplayModeKHR(physicalDevice, displayKHR, &displayModeCreateInfoKHR, nullptr, &displayModeKHR);

				/*
				Ӧ��Ҫ�����ֱ����ʾ����ʾ������Ҫѡ��һ����ʾģʽ�Լ�һ��plane��Ϊ��ʾ��Ŀ��
				*/
				//��ѯһ����ʾģʽ����ʾplane����ϵ���ʾ����
				VkDisplayPlaneCapabilitiesKHR displayPlaneCapabilitiesKHR{};
				displayPlaneCapabilitiesKHR.supportedAlpha = VK_DISPLAY_PLANE_ALPHA_GLOBAL_BIT_KHR;//ΪVkDisplayPlaneAlphaFlagBitsKHR���ֵλ���룬����֧�ֵ�alpha���ģʽ
				displayPlaneCapabilitiesKHR.minSrcPosition = VkOffset2D{ .x = 0,.y = 0 };//�Ǵ�ƽ��ʹ��ָ��ģʽ֧�ֵ���ʾͼƬ�ж�ȡpxiel����С����λ��ƫ������
				displayPlaneCapabilitiesKHR.maxSrcPosition = VkOffset2D{ .x = 1,.y = 1 };//�Ǵ�ƽ��ʹ��ָ��ģʽ֧�ֵ���ʾͼƬ�ж�ȡpxiel��������λ��ƫ������x��y�������minSrcPosition�ж�Ӧ�ġ�
				displayPlaneCapabilitiesKHR.minSrcExtent = VkExtent2D{ .width = 1,.height = 1 };//�Ǵ�ƽ��ʹ��ָ��ģʽ֧�ֵ���ʾͼƬ�ж�ȡpxiel����С���εĴ�С��
				displayPlaneCapabilitiesKHR.maxSrcExtent = VkExtent2D{ .width = 2,.height = 2 };//�Ǵ�ƽ��ʹ��ָ��ģʽ֧�ֵ���ʾͼƬ�ж�ȡpxiel�������εĴ�С��
				displayPlaneCapabilitiesKHR.minDstPosition = VkOffset2D{ .x = 0,.y = 0 };//�Ǵ�ƽ��ʹ��ָ��ģʽ֧�ֵ���ʾͼƬ����ʾ�������С����λ��ƫ���������ܺ��и�����
				displayPlaneCapabilitiesKHR.maxDstPosition = VkOffset2D{ .x = 1,.y = 1 };//�Ǵ�ƽ��ʹ��ָ��ģʽ֧�ֵ���ʾͼƬ����ʾ�����������ƫ������x��y�������minDstPosition�ж�Ӧ�ġ����ܺ��и�����
				displayPlaneCapabilitiesKHR.minDstExtent = VkExtent2D{ .width = 1,.height = 1 };//�Ǵ�ƽ��ʹ��ָ��ģʽ֧�ֵ���ʾͼƬ����ʾ�������С���εĴ�С��
				displayPlaneCapabilitiesKHR.maxDstExtent = VkExtent2D{ .width = 2,.height = 2 };//�Ǵ�ƽ��ʹ��ָ��ģʽ֧�ֵ���ʾͼƬ����ʾ����������εĴ�С��

				vkGetDisplayPlaneCapabilitiesKHR(physicalDevice, displayModeKHR/*mode,ָ����ʾģʽ��VkDisplayModeKHR�������������ʾ������*/, 0/*planeIndex��Ϊplane������*/, &displayPlaneCapabilitiesKHR);


				//��ѯһ����ʾģʽ����ʾplane����ϵ���ʾ���� 2
				VkDisplayPlaneCapabilities2KHR displayPlaneCapabilities2KHR{};
				displayPlaneCapabilities2KHR.sType = VK_STRUCTURE_TYPE_DISPLAY_PLANE_CAPABILITIES_2_KHR;
				displayPlaneCapabilities2KHR.pNext = nullptr;
				displayPlaneCapabilities2KHR.capabilities = displayPlaneCapabilitiesKHR;//VkDisplayPlaneCapabilitiesKHR���ͣ�ǰ���Ѿ��������ˣ����ﲻ�ٸ���

				VkDisplayPlaneInfo2KHR displayPlaneInfo2KHR{};
				displayPlaneInfo2KHR.sType = VK_STRUCTURE_TYPE_DISPLAY_PLANE_INFO_2_KHR;
				displayPlaneInfo2KHR.pNext = nullptr;
				displayPlaneInfo2KHR.mode = displayModeKHR;//ָ����ʾģʽ��VkDisplayModeKHR�������������ʾ������
				displayPlaneInfo2KHR.planeIndex = 0;//Ϊplane������

				vkGetDisplayPlaneCapabilities2KHR(physicalDevice, &displayPlaneInfo2KHR, &displayPlaneCapabilities2KHR);
		}


		//Display Control   �μ�p3077
		{
			//������ʾ���ĵ�Դ״̬
			VkDisplayPowerInfoEXT displayPowerInfoEXT{};
			displayPowerInfoEXT.sType = VK_STRUCTURE_TYPE_DISPLAY_POWER_INFO_EXT;
			displayPowerInfoEXT.pNext = nullptr;
			displayPowerInfoEXT.powerState = VK_DISPLAY_POWER_STATE_ON_EXT;/*ָ����ʾ�����µ�Դ״̬�� VkDisplayPowerStateEXTֵ
			VkDisplayPowerStateEXT:
			VK_DISPLAY_POWER_STATE_OFF_EXT:  ָ���ر���ʾ��
			VK_DISPLAY_POWER_STATE_SUSPEND_EXT:  ָ����ʾ�����ڵ͹���ģʽ�������VK_DISPLAY_POWER_STATE_OFF_EXT�ܹ��ܿ�ص�VK_DISPLAY_POWER_STATE_ON_EXT����ģʽ���ܺ�VK_DISPLAY_POWER_STATE_OFF_EXT״̬��ͬ��
			VK_DISPLAY_POWER_STATE_ON_EXT:  ָ��������ʾ��
			*/
			vkDisplayPowerControlEXT(device, VkDisplayKHR{/*��������һ����Ч��VkDisplayKHR*/ }, & displayPowerInfoEXT);



		}

		//Display Surfaces  �μ�p3078
		{
			/*

			һ����������ʾ���ð���һ����ʾģʽ��һ��������ʾplane����������Ϊ���κβ�����
			�Լ���������Щƽ���������ͼ���ĳЩ����Ĳ�������ʾ���������˴�������ʾ�����еĵ���ƽ������á�
			*/

			//Ϊ��ʾplane ����һ��VkSurfaceKHR
			VkDisplaySurfaceCreateInfoKHR displaySurfaceCreateInfoKHR{};
			displaySurfaceCreateInfoKHR.sType = VK_STRUCTURE_TYPE_DISPLAY_SURFACE_CREATE_INFO_KHR;
			displaySurfaceCreateInfoKHR.pNext = nullptr;
			displaySurfaceCreateInfoKHR.flags = 0;//����δ��ʹ�ã�����Ϊ0
			displaySurfaceCreateInfoKHR.displayMode = VkDisplayModeKHR{/*��������һ����Ч��VkDisplayModeKHR����ǰ������*/ };//ΪVkDisplayModeKHR�����ָ������ʾsurfaceʹ�õ���ʾģʽ
			displaySurfaceCreateInfoKHR.planeIndex = 0;//Ϊ��surface���Ե���ʾplane����
			displaySurfaceCreateInfoKHR.planeStackIndex = 0;//Ϊ��surface���Ե���ʾplane�� z-order
			displaySurfaceCreateInfoKHR.transform = VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR;//Ϊһ�� VkSurfaceTransformFlagBitsKHRֵ��ָ��ͼ����ɨ�����ʱӦ�õı任����
			displaySurfaceCreateInfoKHR.globalAlpha = 1;//Ϊȫ�ֵ�alphaֵ�����alphaMode ��ΪVK_DISPLAY_PLANE_ALPHA_GLOBAL_BIT_KHR�����ֵ����
			displaySurfaceCreateInfoKHR.alphaMode = VK_DISPLAY_PLANE_ALPHA_OPAQUE_BIT_KHR;/*Ϊ VkDisplayPlaneAlphaFlagBitsKHRֵ��ָ��ʹ�õ�alpha�������
			VkDisplayPlaneAlphaFlagBitsKHR:

			VK_DISPLAY_PLANE_ALPHA_OPAQUE_BIT_KHR: ָ��source image������Ϊ��͸���ġ�
			VK_DISPLAY_PLANE_ALPHA_GLOBAL_BIT_KHR: ָ������ָ��һ��ȫ�ֵ�alphaֵ����Ӧ�õ�Դͼ����������ء�
			VK_DISPLAY_PLANE_ALPHA_PER_PIXEL_BIT_KHR:  ָ��ÿ�����ص�alphaֵ����Դͼ������ص�alphaֵ���������Դ��ʽû��alphaֵ���򲻻�Ӧ�û�ϡ�Դalphaֵ����Ԥ�˵�Դͼ���������ɫ����С�
			VK_DISPLAY_PLANE_ALPHA_PER_PIXEL_PREMULTIPLIED_BIT_KHR: �ȼ���VK_DISPLAY_PLANE_ALPHA_PER_PIXEL_BIT_KHR����Դalphaֵ�����Ѿ�Ԥ�˵�Դͼ���������ɫ����С�
			*/
			displaySurfaceCreateInfoKHR.imageExtent = VkExtent2D{ .width = 1,.height = 1 };//ָ����surfaceʹ�õ�image��ʾͼ��Ĵ�С
			/*
			VkDisplaySurfaceCreateInfoKHR��Ч�÷�:
			1.planeIndex ����С��vkGetPhysicalDeviceDisplayPlanePropertiesKHR���ص��豸֧�ֵ�plane������
			2.�������vkGetPhysicalDeviceDisplayPropertiesKHR���ص�VkDisplayPropertiesKHRԪ�ص�display��Ӧ��displayMode��planeReorderPossibleΪVK_TRUE,��planeStackIndex ����С��vkGetPhysicalDeviceDisplayPlanePropertiesKHR���صĵ�ǰphysical device֧�ֵ�plane��������
							����planeStackIndex �������vkGetPhysicalDeviceDisplayPlanePropertiesKHR���صĶ�Ӧ��displayMode��plane��VkDisplayPlanePropertiesKHR��currentStackIndex
			3.���alphaMode ΪVK_DISPLAY_PLANE_ALPHA_GLOBAL_BIT_KHR����globalAlpha������[0,1]֮��
			4.alphaMode�����Ƕ�Ӧ��displayMode��plane��VkDisplayPlaneCapabilitiesKHR�е�supportedAlpha֧�ֵ�
			5.transform�����Ƕ�Ӧ��displayMode��plane��VkDisplayPropertiesKHR�е�supportedTransforms֧�ֵ�
			6.imageExtent��width�Լ�height����С�ڵ���VkPhysicalDeviceLimits::maxImageDimension2D�ж�Ӧ��
			*/


			VkSurfaceKHR surfaceKHR{};
			vkCreateDisplayPlaneSurfaceKHR(instance, &displaySurfaceCreateInfoKHR, nullptr, &surfaceKHR);

			//����
			vkDestroySurfaceKHR(instance, surfaceKHR, nullptr);
		}

		//Presenting to Headless Surfaces �μ�p3082
		{
			/*
			Vulkan��Ⱦ���Գ��ֵ�һ����ͷ���棬���б�ʾ������һ��noop����������ⲿ�ɼ��Ľ����

			�������һЩvulkan����չ�������Եȡ�
			*/


			//����һ����ͷ����
			VkHeadlessSurfaceCreateInfoEXT headlessSurfaceCreateInfoEXT{};
			headlessSurfaceCreateInfoEXT.sType = VK_STRUCTURE_TYPE_HEADLESS_SURFACE_CREATE_INFO_EXT;
			headlessSurfaceCreateInfoEXT.pNext = nullptr;
			headlessSurfaceCreateInfoEXT.flags = 0;//����δ��ʹ�ã�����Ϊ0

			VkSurfaceKHR surfaceKHR{};
			vkCreateHeadlessSurfaceEXT(instance, &headlessSurfaceCreateInfoEXT, nullptr, &surfaceKHR);

			//����
			vkDestroySurfaceKHR(instance, surfaceKHR, nullptr);

			/*
			surface�� currentExtentΪԤ����ֵ (0xFFFFFFFF, 0xFFFFFFFF)������ʹ��swapchain�Ĵ�С��
			*/
		}

	}


	//Querying for WSI Support  �μ�p3084
	{
		/*
		�������е������豸��������WSI֧�֡��������豸�У��������еĶ����嶼��֧�ֱ�ʾ��
		
		*/

		VkSurfaceKHR surfaceKHR{/*��������һ����Ч��VkSurfaceKHR*/};

		//��ѯphysical device�Ķ������Ƿ�֧����surface�ϵ���ʾ
		VkBool32 supportsPresent;
		vkGetPhysicalDeviceSurfaceSupportKHR(physicalDevice, 0/*queueFamilyIndex,Ϊ��������������С�ڵ���vkGetPhysicalDeviceQueueFamilyProperties���ص������豸֧�ֵĶ���������.*/, surfaceKHR/*surface ��Ϊsurface��VkSurfaceKHR���.*/, &supportsPresent/**/);


		//Android Platform ����Ҫ��ѯ�����еĶ��ж�֧����ʾ

		//Wayland Platform
		//��ѯphysical device�Ķ������Ƿ�֧���� Wayland compositor�ϵ���ʾ�������ڴ���surfaceǰ����
		wl_display* wl_disp{/*��������һ����Ч��wl_displayָ��*/};
		VkBool32 waylandPrensentSupport = vkGetPhysicalDeviceWaylandPresentationSupportKHR(physicalDevice, 0/*queueFamilyIndex,Ϊ��������������С�ڵ���vkGetPhysicalDeviceQueueFamilyProperties���ص������豸֧�ֵĶ���������.*/, wl_disp/*display,��Wayland compositor��ص�wl_displayָ��.*/);
	

		//Win32 Platform
		//��ѯphysical device�Ķ������Ƿ�֧����Microsoft Windows desktop�ϵ���ʾ�������ڴ���surfaceǰ����
		VkBool32 winPrensentSupport = vkGetPhysicalDeviceWin32PresentationSupportKHR(physicalDevice, 0/*queueFamilyIndex,Ϊ��������������С�ڵ���vkGetPhysicalDeviceQueueFamilyProperties���ص������豸֧�ֵĶ���������.*/);


		//XCB Platform
		//��ѯphysical device�Ķ������Ƿ�֧����X11 server�ϵ���ʾ��ʹ��XCB �ͻ��˿⣬�����ڴ���surfaceǰ����
		xcb_connection_t* xcb_conn{/*��������һ����Ч��xcb_connection_tָ��*/ };
		typedef uint32_t xcb_visualid_t;
		xcb_visualid_t xcb_visualid{/*��������һ����Ч��xcb_screen_tָ��*/ };
		VkBool32 xcbPrensentSupport = vkGetPhysicalDeviceXcbPresentationSupportKHR(physicalDevice, 0/*queueFamilyIndex,Ϊ��������������С�ڵ���vkGetPhysicalDeviceQueueFamilyProperties���ص������豸֧�ֵĶ���������.*/, xcb_conn/*connection,Ϊ X11 Server���ӵ�xcb_connection_tָ��*/, xcb_visualid/*visual_id,Ϊһ�� X11 visual (xcb_visualid_t).*/);


		//Xlib Platform
		//��ѯphysical device�Ķ������Ƿ�֧����X11 server�ϵ���ʾ��ʹ��Xlib �ͻ��˿⣬�����ڴ���surfaceǰ����
		Display* disp{/*��������һ����Ч��Displayָ��*/};
		typedef uint32_t VisualID;
		VisualID visualid{/*��������һ����Ч��VisualID*/ };
		VkBool32 xlibPrensentSupport = vkGetPhysicalDeviceXlibPresentationSupportKHR(physicalDevice, 0/*queueFamilyIndex,Ϊ��������������С�ڵ���vkGetPhysicalDeviceQueueFamilyProperties���ص������豸֧�ֵĶ���������.*/, disp/*dpy,Ϊ X11 Server��Display����ָ��*/, visualid/*visualId,Ϊһ�� X11 visual (VisualID).*/);


		//DirectFB Platform
		//��ѯphysical device�Ķ������Ƿ�֧��ʹ��DirectFB library������ʾ�������ڴ���surfaceǰ����
		IDirectFB* dfb{/*��������һ����Ч��IDirectFBָ��*/ };
		VkBool32 directfbPrensentSupport = vkGetPhysicalDeviceDirectFBPresentationSupportEXT(physicalDevice, 0/*queueFamilyIndex,Ϊ��������������С�ڵ���vkGetPhysicalDeviceQueueFamilyProperties���ص������豸֧�ֵĶ���������.*/, dfb/*dfb,Ϊe IDirectFB main interface��IDirectFBָ��.*/);


		//Fuchsia Platform  ����Ҫ��ѯ�����еĶ��ж�֧����ʾ

		//Google Games Platform  ����Ҫ��ѯ�����е� VK_QUEUE_GRAPHICS_BIT ����VK_QUEUE_COMPUTE_BIT���ж�֧����ʾ

		// iOS Platform  ����Ҫ��ѯ�����еĶ��ж�֧����ʾ

		//macOS Platform  ����Ҫ��ѯ�����еĶ��ж�֧����ʾ
		
		// VI Platform   ����Ҫ��ѯ�����еĶ��ж�֧����ʾ

		//QNX Screen Platform
		//��ѯphysical device�Ķ������Ƿ�֧����QNX Screen compositor�Ͻ�����ʾ�������ڴ���surfaceǰ����
		_screen_window* qnxWindow{/*��������һ����Ч��_screen_windowָ��*/ };
		VkBool32 qnxPrensentSupport = vkGetPhysicalDeviceScreenPresentationSupportQNX(physicalDevice, 0/*queueFamilyIndex,Ϊ��������������С�ڵ���vkGetPhysicalDeviceQueueFamilyProperties���ص������豸֧�ֵĶ���������.*/, qnxWindow/*window,ΪQNX Screen����ָ��.*/);

	}


	//Surface Queries  �μ�3091
	{
		/*
		wapchain����Ⱦ���ͨ��surface��ʾ��������WSI platform, the native window ���� display, �Լ� physical device��ص���Ϣ������
		*/
		VkSurfaceKHR surfaceKHR{/*��������һ����Ч��VkSurfaceKHR*/ };

		//Surface Capabilities  �μ�p3091
		{
			

			//��ѯ����swapchainʱ��Ҫ��surface�Ļ�������
			VkSurfaceCapabilitiesKHR surfaceCapabilitiesKHR{};
			vkGetPhysicalDeviceSurfaceCapabilitiesKHR(physicalDevice, surfaceKHR/*surface,Ϊsurface�������������Ч���ұ�physicalDevice֧�֣���vkGetPhysicalDeviceSurfaceSupportKHR*/, &surfaceCapabilitiesKHR);//���践������ȷ���
			surfaceCapabilitiesKHR.minImageCount = 1;//Ϊ�豸֧�ֵĶ�surface������swapchian����С��image������������Ϊ1
			surfaceCapabilitiesKHR.maxImageCount = 1;//Ϊ�豸֧�ֵĶ�surface������swapchian������image������������Ϊ0���ߴ��ڵ���minImageCount��0��ζ��û�����ƣ�ֻ�������ڴ�
			surfaceCapabilitiesKHR.currentExtent = VkExtent2D{.width = 1,.height = 1};//Ϊsurface��ǰ�Ŀ�ߣ����������ֵ(0xFFFFFFFF, 0xFFFFFFFF)��ָ����surface�Ŀ�������ڴ�����swapchain�Ŀ��
			surfaceCapabilitiesKHR.minImageExtent = VkExtent2D{ .width = 1,.height = 1 };//Ϊ�豸֧�ֵĶ�surface������swapchian����С��ߣ�С�ڵ���currentExtent�ж�Ӧ��ֵ������currentExtentΪ����ֵ
			surfaceCapabilitiesKHR.maxImageExtent = VkExtent2D{ .width = 1,.height = 1 };//Ϊ�豸֧�ֵĶ�surface������swapchian������ߣ����ڵ���minImageExtent�ж�Ӧ��ֵ�����ڵ���currentExtent�ж�Ӧ��ֵ������currentExtentΪ����ֵ
			surfaceCapabilitiesKHR.maxImageArrayLayers = 1;//Ϊ�豸֧�ֵĶ�surface������swapchian�е�image���ܺ��е�����arrayLayer����������Ϊ1
			surfaceCapabilitiesKHR.supportedTransforms = VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR;/*VkSurfaceTransformFlagBitsKHR ���ֵλ���룬ָ���豸֧�ֵĶ�surface�ܹ�֧�ֵ�presentation transforms
			VkSurfaceTransformFlagBitsKHR:

			VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR: ָ��ͼ�����ݵ���ʾ���ᾭ���任
			VK_SURFACE_TRANSFORM_ROTATE_90_BIT_KHR:  ָ��ͼ�����ݵ���ʾ��˳ʱ����ת90��
			VK_SURFACE_TRANSFORM_ROTATE_180_BIT_KHR:  ָ��ͼ�����ݵ���ʾ��˳ʱ����ת180��
			VK_SURFACE_TRANSFORM_ROTATE_270_BIT_KHR:  ָ��ͼ�����ݵ���ʾ��˳ʱ����ת270��
			VK_SURFACE_TRANSFORM_HORIZONTAL_MIRROR_BIT_KHR:  ָ��ͼ�����ݵ���ʾ��ˮƽ����ת
			VK_SURFACE_TRANSFORM_HORIZONTAL_MIRROR_ROTATE_90_BIT_KHR:  ָ��ͼ�����ݵ���ʾ��ˮƽ����ת��Ȼ��˳ʱ����ת90��
			VK_SURFACE_TRANSFORM_HORIZONTAL_MIRROR_ROTATE_180_BIT_KHR:  ָ��ͼ�����ݵ���ʾ��ˮƽ����ת��Ȼ��˳ʱ����ת180��
			VK_SURFACE_TRANSFORM_HORIZONTAL_MIRROR_ROTATE_270_BIT_KHR:  ָ��ͼ�����ݵ���ʾ��ˮƽ����ת��Ȼ��˳ʱ����ת270��
			VK_SURFACE_TRANSFORM_INHERIT_BIT_KHR:  ָ��ͼ�����ݵ���ʾ�Ĳ�ָ���任����������vulkan����ض�ƽ̨����
			*/
			surfaceCapabilitiesKHR.currentTransform = VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR;//Ϊһ��VkSurfaceTransformFlagBitsKHRֵ��ָ��surface��ǰ��presentation transforms
			surfaceCapabilitiesKHR.supportedCompositeAlpha = VK_COMPOSITE_ALPHA_INHERIT_BIT_KHR;/* VkCompositeAlphaFlagBitsKHR ���ֵλ���룬��ʾ��ʾ֧�ֵ�alpha���ģʽ�����ٽ�����һ��λ����͸����Ͽ���ͨ��ʹ���κ�û��alpha�����ͼ���ʽ������ͨ��ȷ���ɳ���ͼ���е��������ض���1.0��alphaֵ��ʵ�֡�
			VkCompositeAlphaFlagBitsKHR:

			VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR: ͼ���е�alpha������������ڣ����ڻ�ϴ����лᱻ���ԣ���������alpha�����̶�Ϊһ������1.0һ�� 
			VK_COMPOSITE_ALPHA_PRE_MULTIPLIED_BIT_KHR:  ͼ���е�alpha������������ڣ����ڻ�ϴ����лᱻ���ǣ�ͼ��ķ�alpha�����ᱻ��Ϊ���Ѿ���alpha������˺�õ��Ľ����
			VK_COMPOSITE_ALPHA_POST_MULTIPLIED_BIT_KHR:  ͼ���е�alpha������������ڣ����ڻ�ϴ����лᱻ���ǣ�ͼ��ķ�alpha�������ᱻ��Ϊ���Ѿ���alpha������˺�õ��Ľ�����������ڻ�ϵ�ʱ�򽫷�alpha��������alpha������
			VK_COMPOSITE_ALPHA_INHERIT_BIT_KHR: �÷�ʽ��Ϊͼ���е�alpha������vulkan�ǲ���֪�ģ���Ҫ��Ӧ��ʹ�ñ���ϵͳ����ȥ����alpha���ģʽ�����û��ʹ�ñ���ϵͳ����ȥ���ø�ģʽ����ʹ�ø�ƽ̨��Ĭ��ģʽ��

			*/
			surfaceCapabilitiesKHR.supportedUsageFlags = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;//VkImageUsageFlagBits���ֵλ���룬ָ���豸֧�ֵĶ�surface��  VkPresentModeKHRΪ VK_PRESENT_MODE_IMMEDIATE_KHR, VK_PRESENT_MODE_MAILBOX_KHR, VK_PRESENT_MODE_FIFO_KHR ����VK_PRESENT_MODE_FIFO_RELAXED_KHR������swapchian�е�image���÷����������VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT


			//ͨ���ں˻�����չ��ѯ����swapchainʱ��Ҫ��surface�Ļ�������
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
					//VkSurfaceFullScreenExclusiveInfoEXTָ��Ӧ��ƫ��ʹ��ȫ������Ϊ����������ýṹ�������ΪĬ��ΪVK_FULL_SCREEN_EXCLUSIVE_DEFAULT_EXT
					VkSurfaceFullScreenExclusiveInfoEXT& surfaceFullScreenExclusiveInfoEXT = physicalDeviceSurfaceInfo2KHREXT.surfaceFullScreenExclusiveInfoEXT;
					surfaceFullScreenExclusiveInfoEXT.fullScreenExclusive = VK_FULL_SCREEN_EXCLUSIVE_DEFAULT_EXT;/*Ϊ VkFullScreenExclusiveEXTֵ��ָ��Ӧ�ø�ƫ�õ�ȫ����Ϊ
					VkFullScreenExclusiveEXT:
					VK_FULL_SCREEN_EXCLUSIVE_DEFAULT_EXT:  ָ��ʵ��Ӧ��ȷ���ʵ���ȫ����ʽ��������θ÷�ʽ������϶���
					VK_FULL_SCREEN_EXCLUSIVE_ALLOWED_EXT:  ָ��ʵ�ֻ����ʹ�ÿ��õ�ȫ�����л��ƣ�������ƿ��ܻᵼ�¸��õĵ������Լ�/���߲��ܵ���ʾ��������������swapchain ��ʼ������һ����ʾ�Լ�/�������ٵ�ʱ����Ҫ����� disruptive transitions��
					VK_FULL_SCREEN_EXCLUSIVE_DISALLOWED_EXT:  ָ��ʵ��Ӧ�ñ���ʹ������ disruptive transitions��ȫ������
					VK_FULL_SCREEN_EXCLUSIVE_APPLICATION_CONTROLLED_EXT:  ָ��Ӧ��Ӧ��ͨ��ʹ��vkAcquireFullScreenExclusiveModeEXT�Լ�vkReleaseFullScreenExclusiveModeEXT����������ȫ������ģʽ

					*/

					VkSurfaceFullScreenExclusiveWin32InfoEXT surfaceFullScreenExclusiveWin32InfoEXT = physicalDeviceSurfaceInfo2KHREXT.surfaceFullScreenExclusiveWin32InfoEXT;
					HMONITOR hMonitor{/*��������һ����Ч��HMONITOR*/ };
					surfaceFullScreenExclusiveWin32InfoEXT.hmonitor = hMonitor;//Ϊ����surface����ʾ���Win32 HMONITOR�������������Ч��


					//
					VkSurfacePresentModeEXT& surfacePresentModeEXT = physicalDeviceSurfaceInfo2KHREXT.surfacePresentModeEXT;
					surfacePresentModeEXT.presentMode = VK_PRESENT_MODE_FIFO_KHR;//ΪswapchainҪʹ�õ���ʾģʽ�������� vkGetPhysicalDeviceSurfacePresentModesKHR�з��ص�surface֧�ֵ�

				}
				physicalDeviceSurfaceInfo2KHR.pNext = &physicalDeviceSurfaceInfo2KHREXT.surfaceFullScreenExclusiveInfoEXT;
				physicalDeviceSurfaceInfo2KHR.surface = surfaceKHR;
				/*
				VkPhysicalDeviceSurfaceInfo2KHR��Ч�÷�:
				1.���pNext�а���һ��fullScreenExclusive��ΪVK_FULL_SCREEN_EXCLUSIVE_APPLICATION_CONTROLLED_EXT��VkSurfaceFullScreenExclusiveInfoEXT����surfaceʹ��vkCreateWin32SurfaceKHR��������pNext�б������һ��VkSurfaceFullScreenExclusiveWin32InfoEXT
				2.���surface ��ΪVK_NULL_HANDLE����VK_GOOGLE_surfaceless_query ��չδ��������surface��������Ч��VkSurfaceKHR���
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
						latencySurfaceCapabilitiesNV.sType = VK_STRUCTURE_TYPE_MAX_ENUM;//û�ж�����������Ϊ�Ƿ�ֵ
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
				//VkSurfaceCapabilities2KHR.pNext  ��Щֵ���ǲ�ѯ�󷵻ص�
				{
					//��ѯһ������ʾ�� protected VkSurfaceKHR
					VkSurfaceProtectedCapabilitiesKHR& surfaceProtectedCapabilitiesKHR = surfaceCapabilities2KHREXT.surfaceProtectedCapabilitiesKHR;
					surfaceProtectedCapabilitiesKHR.supportsProtected = VK_TRUE;//����ֵ��ָ���Ƿ��������Ļ����ʾ��VkPhysicalDeviceSurfaceInfo2KHR::surfaceΪ�ض�����ϵͳ������protected swapchain�����ΪVK_TRUE�������֧�ִ�������VK_SWAPCHAIN_CREATE_PROTECTED_BIT_KHR��־��swapchain��


					//��ȡsurface֧�ֵ���������
					VkSurfacePresentScalingCapabilitiesEXT& surfacePresentScalingCapabilitiesEXT = surfaceCapabilities2KHREXT.surfacePresentScalingCapabilitiesEXT;
					surfacePresentScalingCapabilitiesEXT.minScaledImageExtent = VkExtent2D{ .width = 1,.height = 1 };//��ʹ��֧�ֵ����ŷ���֮һʱ����ֵ����ָ���豸��surface����С��Ч swapchain�����ŷ�Χ��������ֵ��0x FFFFFFFF��0x FFFFFFFF��������surface��С����swapchain�ķ�Χ�������÷�Χ��width��height��ӦС�ڻ����VkSurfaceCapabilitiesKHR::minImageExtent��Ӧ��ֵ
					surfacePresentScalingCapabilitiesEXT.maxScaledImageExtent = VkExtent2D{ .width = 1,.height = 1 };//��ʹ��֧�ֵ����ŷ���֮һʱ����ֵ����ָ���豸��surface�������Ч swapchain�����ŷ�Χ��������ֵ��0x FFFFFFFF��0x FFFFFFFF��������surface��С����swapchain�ķ�Χ�������÷�Χ��width��height��Ӧ���ڻ����VkSurfaceCapabilitiesKHR::maxImageExtent��Ӧ��ֵ
					surfacePresentScalingCapabilitiesEXT.supportedPresentGravityX = VK_PRESENT_GRAVITY_MIN_BIT_EXT;/* VkPresentGravityFlagBitsEXT���ֵλ���룬ָ��surface֧�ֵ�X���pixel gravity��Ϊ0��ʾX�᲻֧��pixel gravity
					VkPresentGravityFlagBitsEXT:
					VK_PRESENT_GRAVITY_MIN_BIT_EXT: ָ��pixels��������surface�Ķ�������ࡣ
					VK_PRESENT_GRAVITY_MAX_BIT_EXT: ָ��pixels��������surface�ĵײ����Ҳࡣ
					VK_PRESENT_GRAVITY_CENTERED_BIT_EXT: ָ��pixels������surface�����ġ�

					*/
					surfacePresentScalingCapabilitiesEXT.supportedPresentGravityY = VK_PRESENT_GRAVITY_MIN_BIT_EXT;// VkPresentGravityFlagBitsEXT���ֵλ���룬ָ��surface֧�ֵ�Y���pixel gravity��Ϊ0��ʾY�᲻֧��pixel gravity
					surfacePresentScalingCapabilitiesEXT.supportedPresentScaling = VK_PRESENT_SCALING_ONE_TO_ONE_BIT_EXT;/*ΪVkPresentScalingFlagBitsEXT���ֵλ���룬ָ��surface֧�ֵ����Ų���,����Ϊ0��ʾ��֧������
					VkPresentScalingFlagBitsEXT:
					VK_PRESENT_SCALING_ONE_TO_ONE_BIT_EXT:   ָ�����������Ų���������swapchain�е��������ػ�һһ��Ӧ��surface�е��������أ�ӳ�����ѡ����presentation gravity����
					VK_PRESENT_SCALING_ASPECT_RATIO_STRETCH_BIT_EXT:  ָ��swapchainͼ�񽫱���С��Ŵ�ʹ�����Ŀ�Ȼ�߶�������һ��������Ӧ��surface�ߴ磬������һ�������ĳߴ�С�ڻ������Ӧ��surface�ߴ磬���ɵ�ͼ����ԭʼswapchainͼ��ĳ������ͬ
					VK_PRESENT_SCALING_STRETCH_BIT_EXT:  ָ��swapchainͼ�񽫱���С��Ŵ�surface�Ĵ�С
					*/


					//VkSurfacePresentModeCompatibilityEXT    ��ѯ�͸���present mode��ʾģʽ���ݵ�һ��present mode
					VkSurfacePresentModeCompatibilityEXT& surfacePresentModeCompatibilityEXT = surfaceCapabilities2KHREXT.surfacePresentModeCompatibilityEXT;
					surfacePresentModeCompatibilityEXT.presentModeCount = 1;//Ϊ��ѯ���ĺ͸���present mode���ݵ���ʾģʽ������
					VkPresentModeKHR presentMode = VK_PRESENT_MODE_FIFO_KHR;
					surfacePresentModeCompatibilityEXT.pPresentModes = &presentMode;//һ��VkPresentModeKHR����ָ�룬ָ��������present mode���ݵ�һ��present mode


					//VkSharedPresentSurfaceCapabilitiesKHR
					VkSharedPresentSurfaceCapabilitiesKHR& sharedPresentSurfaceCapabilitiesKHR = surfaceCapabilities2KHREXT.sharedPresentSurfaceCapabilitiesKHR;
					sharedPresentSurfaceCapabilitiesKHR.sharedPresentSupportedUsageFlags = VK_IMAGE_ASPECT_COLOR_BIT;// VkImageUsageFlagBits���ֵλ���룬ָ�����豸֧��surface����VkPresentModeKHRΪ VK_PRESENT_MODE_SHARED_DEMAND_REFRESH_KHR ���� VK_PRESENT_MODE_SHARED_CONTINUOUS_REFRESH_KHR������swapchain֮��Ĺ���image���÷������ٰ���VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT

					//VkDisplayNativeHdrSurfaceCapabilitiesAMD
					VkDisplayNativeHdrSurfaceCapabilitiesAMD& displayNativeHdrSurfaceCapabilitiesAMD = surfaceCapabilities2KHREXT.displayNativeHdrSurfaceCapabilitiesAMD;
					displayNativeHdrSurfaceCapabilitiesAMD.localDimmingSupport = VK_TRUE;//ָ��surface�Ƿ�֧��local dimming�����ΪVK_TRUE���򴴽�swapchain��ʱ��Ϳ���ָ��һ��VkSwapchainDisplayNativeHdrCreateInfoAMD��ʾ����local dimming�������� vkSetLocalDimmingAMD����


					VkSurfaceCapabilitiesFullScreenExclusiveEXT& surfaceCapabilitiesFullScreenExclusiveEXT = surfaceCapabilities2KHREXT.surfaceCapabilitiesFullScreenExclusiveEXT;
					surfaceCapabilitiesFullScreenExclusiveEXT.fullScreenExclusiveSupported = VK_TRUE;//����surfaceʱ���ܹ�ʹ�ö���ȫ�����ʣ������֧��������VK_FULL_SCREEN_EXCLUSIVE_APPLICATION_CONTROLLED_EXT����swapchain

					VkSurfaceCapabilitiesPresentBarrierNV& surfaceCapabilitiesPresentBarrierNV = surfaceCapabilities2KHREXT.surfaceCapabilitiesPresentBarrierNV;
					surfaceCapabilitiesPresentBarrierNV.presentBarrierSupported = VK_TRUE;//����surface�Ƿ����ʹ��present barrier ����

				}

				surfaceCapabilities2KHR.pNext = &surfaceCapabilities2KHREXT.displayNativeHdrSurfaceCapabilitiesAMD;

				vkGetPhysicalDeviceSurfaceCapabilities2KHR(physicalDevice, &physicalDeviceSurfaceInfo2KHR/*pSurfaceInfo*/, &surfaceCapabilities2KHR/*pSurfaceCapabilities*/);//���践������ȷ���
				/*
				vkGetPhysicalDeviceSurfaceCapabilities2KHR��Ч�÷�:
				1.���VK_GOOGLE_surfaceless_query ��չû�п�������pSurfaceInfo->surface ��������Ч��VkSurfaceKHR���
				2.���pSurfaceInfo->surface��ΪVK_NULL_HANDLE��pSurfaceInfo->surface������physicalDevice֧�֣���vkGetPhysicalDeviceSurfaceSupportKHR
				3.���pSurfaceCapabilities->pNext�в�����VkSurfaceCapabilitiesFullScreenExclusiveEXT����pSurfaceInfo->pNext�б������VkSurfaceFullScreenExclusiveWin32InfoEXT
				4.���pSurfaceCapabilities->pNext�а���VkSurfacePresentModeCompatibilityEXT����1��pSurfaceInfo->pNext�б������VkSurfacePresentModeEXT
																							   ��2��pSurfaceInfo->surface ��������Ч��VkSurfaceKHR���
				5.���pSurfaceCapabilities->pNext�а���VkSurfacePresentScalingCapabilitiesEXT����1��pSurfaceInfo->pNext�б������VkSurfacePresentModeEXT
																								 ��2��pSurfaceInfo->surface ��������Ч��VkSurfaceKHR���


				*/

				surfaceCapabilities2KHR.surfaceCapabilities = surfaceCapabilitiesKHR;//VkSurfaceCapabilitiesKHR���ͣ�ǰ���Ѿ����������ﲻ�ٸ���




			}


			//��ѯ����swapchainʱ��Ҫ��surface�Ļ�������
			VkSurfaceCapabilities2EXT surfaceCapabilities2EXT{};
			surfaceCapabilities2EXT.sType = VK_STRUCTURE_TYPE_SURFACE_CAPABILITIES_2_EXT;
			surfaceCapabilities2EXT.pNext = nullptr;
			vkGetPhysicalDeviceSurfaceCapabilities2EXT(physicalDevice, surfaceKHR, &surfaceCapabilities2EXT);//����ɹ������˽��
			surfaceCapabilities2EXT.minImageCount = 1;//Ϊ�豸֧�ֵĶ�surface������swapchian����С��image������������Ϊ1
			surfaceCapabilities2EXT.maxImageCount = 1;//Ϊ�豸֧�ֵĶ�surface������swapchian������image������������Ϊ0���ߴ��ڵ���minImageCount��0��ζ��û�����ƣ�ֻ�������ڴ�
			surfaceCapabilities2EXT.currentExtent = VkExtent2D{ .width = 1,.height = 1 };//Ϊsurface��ǰ�Ŀ�ߣ����������ֵ(0xFFFFFFFF, 0xFFFFFFFF)��ָ����surface�Ŀ�������ڴ�����swapchain�Ŀ��
			surfaceCapabilities2EXT.minImageExtent = VkExtent2D{ .width = 1,.height = 1 };//Ϊ�豸֧�ֵĶ�surface������swapchian����С��ߣ�С�ڵ���currentExtent�ж�Ӧ��ֵ������currentExtentΪ����ֵ
			surfaceCapabilities2EXT.maxImageExtent = VkExtent2D{ .width = 1,.height = 1 };//Ϊ�豸֧�ֵĶ�surface������swapchian������ߣ����ڵ���minImageExtent�ж�Ӧ��ֵ�����ڵ���currentExtent�ж�Ӧ��ֵ������currentExtentΪ����ֵ
			surfaceCapabilities2EXT.maxImageArrayLayers = 1;//Ϊ�豸֧�ֵĶ�surface������swapchian�е�image���ܺ��е�����arrayLayer����������Ϊ1
			surfaceCapabilities2EXT.supportedTransforms = VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR;//VkSurfaceTransformFlagBitsKHR ���ֵλ���룬ָ���豸֧�ֵĶ�surface�ܹ�֧�ֵ�presentation transforms
			surfaceCapabilities2EXT.currentTransform = VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR;//Ϊһ��VkSurfaceTransformFlagBitsKHRֵ��ָ��surface��ǰ��presentation transforms
			surfaceCapabilities2EXT.supportedCompositeAlpha = VK_COMPOSITE_ALPHA_INHERIT_BIT_KHR;// VkCompositeAlphaFlagBitsKHR ���ֵλ���룬��ʾ��ʾ֧�ֵ�alpha���ģʽ�����ٽ�����һ��λ����͸����Ͽ���ͨ��ʹ���κ�û��alpha�����ͼ���ʽ������ͨ��ȷ���ɳ���ͼ���е��������ض���1.0��alphaֵ��ʵ�֡�
			surfaceCapabilities2EXT.supportedUsageFlags = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;//VkImageUsageFlagBits���ֵλ���룬ָ���豸֧�ֵĶ�surface��  VkPresentModeKHRΪ VK_PRESENT_MODE_IMMEDIATE_KHR, VK_PRESENT_MODE_MAILBOX_KHR, VK_PRESENT_MODE_FIFO_KHR ����VK_PRESENT_MODE_FIFO_RELAXED_KHR������swapchian�е�image���÷����������VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT
			surfaceCapabilities2EXT.supportedSurfaceCounters = 0;// VkSurfaceCounterFlagBitsEXT���ֵλ����ָ��֧�ֵ�surface���������ͣ�����surface��һ��display surface�����ܰ��� VK_SURFACE_COUNTER_VBLANK_BIT_EXT,VK_SURFACE_COUNTER_VBLANK_BIT_EXTָ��ÿ�������������������ʾ���ϳ��ִ�ֱ��������ʱ����һ�εļ�����


		}


		// Surface Format Support  �μ�p3111
		{
			
			//��ѯsurface��swapchain֧�ֵ�format�Լ�color space��
			uint32_t surfaceFormatCount = 0;
			std::vector<VkSurfaceFormatKHR> surfaceFormatKHRs{};
			vkGetPhysicalDeviceSurfaceFormatsKHR(physicalDevice, surfaceKHR, &surfaceFormatCount, nullptr);
			/*
			vkGetPhysicalDeviceSurfaceFormatsKHR��Ч�÷�:
			1.��� VK_GOOGLE_surfaceless_query ��չδ��������surface��������Ч��VkSurfaceKHR���
			2.���surface��ΪVK_NULL_HANDLE����surface���뱻physicalDevice֧�֣��μ�vkGetPhysicalDeviceSurfaceSupportKHR����һ���Եȵ�ƽ̨�������ж�
			*/
			surfaceFormatKHRs.resize(surfaceFormatCount);
			vkGetPhysicalDeviceSurfaceFormatsKHR(physicalDevice, surfaceKHR, &surfaceFormatCount, surfaceFormatKHRs.data());//����ɹ�������һ��Ԫ��,
			VkSurfaceFormatKHR& surfaceFormatKHR = surfaceFormatKHRs[0];
			surfaceFormatKHR.format = VK_FORMAT_R8G8B8_SRGB;//Ϊָ��surface���ݵ�format��ָ��pixel�ı��뷽ʽ
			surfaceFormatKHR.colorSpace = VK_COLORSPACE_SRGB_NONLINEAR_KHR;/*Ϊָ��surface���ݵ� VkColorSpaceKHR��������ν���pixel�ı���ֵ
			VkColorSpaceKHR:

			VK_COLOR_SPACE_SRGB_NONLINEAR_KHR:  ָ��֧�� sRGB color space
			VK_COLOR_SPACE_DISPLAY_P3_NONLINEAR_EXT:  ָ��֧�� Display-P3 color space,ʹ��sRGB-like EOTF������ʾ
			VK_COLOR_SPACE_EXTENDED_SRGB_LINEAR_EXT:  ָ��֧�� ��չ sRGB color space,ʹ��linear EOTF������ʾ
			VK_COLOR_SPACE_EXTENDED_SRGB_NONLINEAR_EXT:  ָ��֧�� ��չ sRGB color space,ʹ��sRGB EOTF������ʾ
			VK_COLOR_SPACE_DISPLAY_P3_LINEAR_EXT:  ָ��֧�� Display-P3 color space,ʹ��linear EOTF������ʾ
			VK_COLOR_SPACE_DCI_P3_NONLINEAR_EXT:  ָ��֧�� DCI-P3 color space,ʹ��DCI-P3 EOTF������ʾ����ͼ���е�ֵ�ᱻ����ΪXYZ�������ɫ����
			VK_COLOR_SPACE_BT709_LINEAR_EXT:  ָ��֧�� BT709 color space,ʹ��linear EOTF������ʾ
			VK_COLOR_SPACE_BT709_NONLINEAR_EXT:  ָ��֧�� BT709 color space,ʹ��SMPTE 170M EOTF������ʾ
			VK_COLOR_SPACE_BT2020_LINEAR_EXT:  ָ��֧�� BT2020 color space,ʹ��linear EOTF������ʾ
			VK_COLOR_SPACE_HDR10_ST2084_EXT:  ָ��֧�� HDR10 (BT2020 color) color space,ʹ��SMPTE ST2084 Perceptual Quantizer (PQ) EOTF������ʾ
			VK_COLOR_SPACE_DOLBYVISION_EXT:  ָ��֧�� Dolby Vision (BT2020 color space) color space��proprietary encoding,ʹ��SMPTE ST2084 EOTF������ʾ
			VK_COLOR_SPACE_HDR10_HLG_EXT:  ָ��֧�� HDR10 (BT2020 color space) color space,ʹ��Hybrid Log Gamma (HLG) EOTF������ʾ
			VK_COLOR_SPACE_ADOBERGB_LINEAR_EXT:  ָ��֧�� AdobeRGB color space,ʹ��linear EOTF������ʾ
			VK_COLOR_SPACE_ADOBERGB_NONLINEAR_EXT:  ָ��֧�� AdobeRGB color space,ʹ��Gamma 2.2 EOTF������ʾ
			VK_COLOR_SPACE_PASS_THROUGH_EXT:  ָ����ɫ�����Ͱ��ա�ԭ��������ʹ�ã�������Ӧ�ò��ڴ˴����н�����ɫֵ��һ�����ڴ�ͳ���Ի��߷�gamma��ɫת�������л�ʹ�����
			VK_COLOR_SPACE_DISPLAY_NATIVE_AMD:  ָ��֧����ʾ�����ص�color space�������AMD��֧��FreeSync2 standard����ʾ����color space������
			*/



			//��ѯsurface��swapchain֧�ֵ�formatԪ��
VkPhysicalDeviceSurfaceInfo2KHR physicalDeviceSurfaceInfo2KHR{};
physicalDeviceSurfaceInfo2KHR.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SURFACE_INFO_2_KHR;
physicalDeviceSurfaceInfo2KHR.pNext = nullptr;
physicalDeviceSurfaceInfo2KHR.surface = surfaceKHR;//

uint32_t surfaceFormat2Count = 0;
std::vector<VkSurfaceFormat2KHR> surfaceFormat2KHRs{};
vkGetPhysicalDeviceSurfaceFormats2KHR(physicalDevice, &physicalDeviceSurfaceInfo2KHR, &surfaceFormat2Count, nullptr);
/*
vkGetPhysicalDeviceSurfaceFormats2KHR��Ч�÷�:
1.��� VK_GOOGLE_surfaceless_query ��չδ��������surface��������Ч��VkSurfaceKHR���
2.���surface��ΪVK_NULL_HANDLE����surface���뱻physicalDevice֧�֣��μ�vkGetPhysicalDeviceSurfaceSupportKHR����һ���Եȵ�ƽ̨�������ж�
*/
surfaceFormat2KHRs.resize(surfaceFormat2Count);
vkGetPhysicalDeviceSurfaceFormats2KHR(physicalDevice, &physicalDeviceSurfaceInfo2KHR, &surfaceFormat2Count, surfaceFormat2KHRs.data());//����ɹ�������һ��Ԫ��
VkSurfaceFormat2KHR& surfaceFormat2KHR = surfaceFormat2KHRs[0];
surfaceFormat2KHR.sType = VK_STRUCTURE_TYPE_SURFACE_FORMAT_2_KHR;
VkImageCompressionPropertiesEXT imageCompressionPropertiesEXT{};
{
	imageCompressionPropertiesEXT.sType = VK_STRUCTURE_TYPE_IMAGE_COMPRESSION_PROPERTIES_EXT;
	imageCompressionPropertiesEXT.pNext = nullptr;
	imageCompressionPropertiesEXT.imageCompressionFlags = 0;
	imageCompressionPropertiesEXT.imageCompressionFixedRateFlags = 0;
}
surfaceFormat2KHR.pNext = &imageCompressionPropertiesEXT;//���imageCompressionControlSwapchain ���Կ��������԰���һ��VkImageCompressionPropertiesEXT��������ѹ������
surfaceFormat2KHR.surfaceFormat = surfaceFormatKHRs[0];//VkSurfaceFormatKHR���ͣ�ǰ���Ѿ����������ﲻ�ٸ���


		}


		//Surface Presentation Mode Support �μ�p3119
		{
			//��ѯsurface֧�ֵ�present mode
			uint32_t presentModeCount = 0;
			std::vector<VkPresentModeKHR> presentModeKHRs{};
			vkGetPhysicalDeviceSurfacePresentModesKHR(physicalDevice, surfaceKHR, &presentModeCount, nullptr);
			/*
			vkGetPhysicalDeviceSurfacePresentModesKHR��Ч�÷�:
			1.��� VK_GOOGLE_surfaceless_query ��չδ��������surface��������Ч��VkSurfaceKHR���
			2.���surface��ΪVK_NULL_HANDLE����surface���뱻physicalDevice֧�֣��μ�vkGetPhysicalDeviceSurfaceSupportKHR����һ���Եȵ�ƽ̨�������ж�
			*/
			presentModeKHRs.resize(presentModeCount);
			vkGetPhysicalDeviceSurfacePresentModesKHR(physicalDevice, surfaceKHR, &presentModeCount, presentModeKHRs.data());//����ɹ�������һ��Ԫ��
			VkPresentModeKHR& presentModeKHR = presentModeKHRs[0] = VK_PRESENT_MODE_FIFO_KHR;
			/*
			VkPresentModeKHR:
			VK_PRESENT_MODE_IMMEDIATE_KHR:  ָ����ʾ���ȴ���ֱ�հ����ڣ�vertical blanking period�������µ�ǰͼ������ζ�Ŵ�ģʽ���ܻᵼ�¿ɼ���˺�ѡ���ʾͼ����Ҫ��������ڲ��Ŷӣ���Ϊ���������Ӧ��
			VK_PRESENT_MODE_MAILBOX_KHR:  ָ����ʾ�ȴ���һ����ֱ�հ����ڣ�vertical blanking period�������µ�ǰͼ�񡣲���۲쵽˺�ѡ��ڲ�����Ŀ�������ڱ�������ͼ����ʾ����������յ��µı�ʾ����ʱ�������������������滻������Ŀ����������ǰ��Ŀ��������κ�ͼ�񶼿ɹ�Ӧ�ó������á����зǿ�ʱ������ÿ����ֱ�հ����ڣ�vertical blanking period����ɾ��һ�����󲢽��д���
			VK_PRESENT_MODE_FIFO_KHR:  ָ����ʾ�ȴ���һ����ֱ�հ����ڣ�vertical blanking period�������µ�ǰͼ�񡣲���۲쵽˺�ѡ��ڲ��������ڱ������ڹ����ͼ����ʾ���������󱻸��ӵ����е�ĩβ���ڶ��зǿ�ʱ������ÿ����ֱ�հ����ڣ�vertical blanking period����ɾ��һ�����󲢽��д�������presentMode�б�����Ҫ֧�ֵ�Ψһ��ģʽ��
			VK_PRESENT_MODE_FIFO_RELAXED_KHR:  ָ����ʾͨ����ȴ���һ����ֱ�հ����ڣ�vertical blanking period���Ը��µ�ǰͼ������Ե�ǰͼ����ϴθ�����������ֱ�հ����ڣ�vertical blanking period���Ѿ���ȥ����ô��ʾ����ȴ���һ������ֱ�հ����ڣ�vertical blanking period��������ζ������������£�����ģʽ���ܵ��¿ɼ���˺�ѡ�����ģʽ���ڼ��� visual stutter�����ã���Ӧ�ó�������һ������ֱ�հ����ڣ�vertical blanking period��֮ǰ������ͼ�񣬵�ż�����ܻ��ӳ٣�������һ������ֱ�հ����ڣ�vertical blanking period��֮�������ͼ���ڲ��������ڱ����ѹ����ͼ����ʾ���������󱻸��ӵ����е�ĩβ���ڶ��зǿ�ʱ������ÿ����ֱ�հ����ڣ�vertical blanking period���л���֮��ɾ��һ�����󲢽��д���
			VK_PRESENT_MODE_SHARED_DEMAND_REFRESH_KHR:  ָ����ʾ��Ӧ�ó�����Բ������ʵ���ͼ���ⱻ��Ϊ����Ŀ���ʾͼ����ʾֻ��Ҫ���յ��µ�ͼ����ʾ�������µ�ǰͼ����ˣ�ÿ����Ҫ����ʱ��Ӧ�ó���������ͼ����ʾ����Ȼ������ʾ�������κε���µ�ǰ��ͼ������ζ������ģʽ���ܵ��¿ɼ���˺��
			VK_PRESENT_MODE_SHARED_CONTINUOUS_REFRESH_KHR:  ָ����ʾ��Ӧ�ó�����Բ������ʵ���ͼ���ⱻ��Ϊ����Ŀ���ʾͼ����ʾ��ѭ���ж��ڸ��µ�ǰͼ��Ӧ�ó���ֻ��Ҫ����һ����ʼ��ʾ����֮����ʾ���¶�����Ҫ�κκ�������ʾ������ܹ����ڸ���ͼ��Ӧ�ó������ͨ��������ʾ������ָʾͼ�������Ѿ����£����Ⲣ���ܱ�֤��ʱ���������ʱ�䡣���û����ȷ��ʱ��Ⱦͼ������ģʽ���ܻᵼ�¿ɼ�˺�ѡ�
			*/

			//ѡ����������swapchain�Ĺ̶���������ѯsurface֧�ֵ�present mode
			VkPhysicalDeviceSurfaceInfo2KHR physicalDeviceSurfaceInfo2KHR{};//�ýṹ��ǰ���Ѿ��������ˣ����ﲻ�ٸ���
			physicalDeviceSurfaceInfo2KHR.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SURFACE_INFO_2_KHR;
			physicalDeviceSurfaceInfo2KHR.pNext = nullptr;
			physicalDeviceSurfaceInfo2KHR.surface = surfaceKHR;//ָ��surface
			vkGetPhysicalDeviceSurfacePresentModes2EXT(physicalDevice, &physicalDeviceSurfaceInfo2KHR, &presentModeCount, nullptr);
			/*
			vkGetPhysicalDeviceSurfacePresentModes2EXT��Ч�÷�:
			1.��� VK_GOOGLE_surfaceless_query ��չδ��������surface��������Ч��VkSurfaceKHR���
			2.���surface��ΪVK_NULL_HANDLE����surface���뱻physicalDevice֧�֣��μ�vkGetPhysicalDeviceSurfaceSupportKHR����һ���Եȵ�ƽ̨�������ж�
			*/
			presentModeKHRs.resize(presentModeCount);
			vkGetPhysicalDeviceSurfacePresentModes2EXT(physicalDevice, &physicalDeviceSurfaceInfo2KHR, &presentModeCount, presentModeKHRs.data());//����ɹ�������һ��Ԫ��


			/*
			��ʾģʽ����ʾͼ����÷���Ӧ�ο���:
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


	//Full Screen Exclusive Control  �μ�p3123
	{
		/*
		Ҫ��ʾ��fullScreenExclusive ����ΪVK_FULL_SCREEN_EXCLUSIVE_APPLICATION_CONTROLLED_EXT ������swapchain����Ҫ��ȡ�����ͷ�ȫ�����ҷ���Ȩexclusive full-screen access
		*/

		//��ȡexclusive full-screen access
		vkAcquireFullScreenExclusiveModeEXT(device, VkSwapchainKHR{/*��������һ����Ч��VkSwapchainKHR*/ }/*swapchain,Ҫ��ȡexclusive full-screen access��swapchain*/);
		/*
		vkAcquireFullScreenExclusiveModeEXT��Ч�÷�:
		1.swapchain ���ܴ���retired state
		2.swapchain �������Ժ���fullScreenExclusive����ΪVK_FULL_SCREEN_EXCLUSIVE_APPLICATION_CONTROLLED_EXT�� VkSurfaceFullScreenExclusiveInfoEXT ������
		3.swapchain ��ǰ����ӵ��exclusive full-screen access
		*/

		//�ͷ�exclusive full-screen access
		vkReleaseFullScreenExclusiveModeEXT(device, VkSwapchainKHR{/*��������һ����Ч��VkSwapchainKHR*/ }/*swapchain,Ҫ�ͷ�exclusive full-screen access��swapchain*/);
		/*
		vkReleaseFullScreenExclusiveModeEXT��Ч�÷�:
		1.swapchain ���ܴ���retired state
		2.swapchain �������Ժ���fullScreenExclusive����ΪVK_FULL_SCREEN_EXCLUSIVE_APPLICATION_CONTROLLED_EXT�� VkSurfaceFullScreenExclusiveInfoEXT ������
		*/
	}


	//Device Group Queries  �μ�p3126
	{
		/*
		һ����ʾ��������豸���߼��豸���Խ�image��ʾ����������豸�ϣ������ǴӶ�������豸�ϰ���ʾimage
		*/

		//��ѯ�������豸��ʾ�������
		VkDeviceGroupPresentCapabilitiesKHR deviceGroupPresentCapabilitiesKHR{};
		deviceGroupPresentCapabilitiesKHR.sType = VK_STRUCTURE_TYPE_DEVICE_GROUP_PRESENT_CAPABILITIES_KHR;
		deviceGroupPresentCapabilitiesKHR.pNext = nullptr;

		vkGetDeviceGroupPresentCapabilitiesKHR(device, &deviceGroupPresentCapabilitiesKHR);//����ɹ�����������

		deviceGroupPresentCapabilitiesKHR.presentMask;///presentMaskΪVK_MAX_DEVICE_GROUP_SIZE ��uint32_tֵ���飬���Ԫ��ֵ��0�������Ԫ�ض�Ӧ�������豸������ʾ--����ʾ���棬������Ԫ�ص�ĳ��bitΪ1�������Ԫ��֧�ָ�bit��Ӧ�������豸��ͼ�����ʾ����Ԫ������Ҫ�豸��Ӧ��Ԫ�������豸��bitΪ1
		for (uint32_t i = 0; i < VK_MAX_DEVICE_GROUP_SIZE; i++)
		{
			deviceGroupPresentCapabilitiesKHR.presentMask[i] = 0x00000001;
		}
		deviceGroupPresentCapabilitiesKHR.modes = VK_DEVICE_GROUP_PRESENT_MODE_LOCAL_BIT_KHR;//VkDeviceGroupPresentModeFlagBitsKHR ���ֵλ���룬ָ��֧���ĸ��豸�����ʾģʽ����Զ���� VK_DEVICE_GROUP_PRESENT_MODE_LOCAL_BIT_KHR
		/*
		VkDeviceGroupPresentModeFlagBitsKHR:
		VK_DEVICE_GROUP_PRESENT_MODE_LOCAL_BIT_KHR:  ָ���κκ�����ʾ����������豸�ܹ���ʾ�����е�swapchain images
		VK_DEVICE_GROUP_PRESENT_MODE_REMOTE_BIT_KHR:  ָ���κκ�����ʾ����������豸�ܹ���ʾ������presentMask��ָ�����κ����������豸��swapchain images
		VK_DEVICE_GROUP_PRESENT_MODE_SUM_BIT_KHR:  ָ���κκ�����ʾ����������豸�ܹ���ʾ������presentMask��ָ�����κ����������豸��swapchain images�ܺ�
		VK_DEVICE_GROUP_PRESENT_MODE_LOCAL_MULTI_DEVICE_BIT_KHR:  ָ����������豸����һ����ʾ����ĸ��������豸�ܹ���ʾ�����е�swapchain images
		*/

		VkSurfaceKHR surface{/*��������һ����Ч��VkSurfaceKHR*/ };

		//��Щsurface���ܲ�֧�����е��豸����ʾģʽ�����Բ�ѯĳ��surface֧�ֵ��豸����ʾģʽ
		VkDeviceGroupPresentModeFlagsKHR surfaceDeviceGroupPresentModeFlagsKHR{};
		vkGetDeviceGroupSurfacePresentModesKHR(device, surface/*surface ,surface���뱻device�е�����physical device֧�֣��μ�vkGetPhysicalDeviceSurfaceSupportKHR����һ���Եȵ�ƽ̨�������ж�*/, & surfaceDeviceGroupPresentModeFlagsKHR);


		//��Щsurface���ܲ�֧�����е��豸����ʾģʽ������ָ��һЩ����swapchain��Ҫ�Ĺ��в�����ѯĳ��surface֧�ֵ��豸����ʾģʽ
		VkPhysicalDeviceSurfaceInfo2KHR physicalDeviceSurfaceInfo2KHR{};//�ýṹ��ǰ���Ѿ��������ˣ����ﲻ�ٸ���
		physicalDeviceSurfaceInfo2KHR.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SURFACE_INFO_2_KHR;
		physicalDeviceSurfaceInfo2KHR.pNext = nullptr;
		physicalDeviceSurfaceInfo2KHR.surface = surface;//surface���뱻device�е�����physical device֧�֣��μ�vkGetPhysicalDeviceSurfaceSupportKHR����һ���Եȵ�ƽ̨�������ж�

		vkGetDeviceGroupSurfacePresentModes2EXT(device, &physicalDeviceSurfaceInfo2KHR, & surfaceDeviceGroupPresentModeFlagsKHR);


		//��ʹ��VK_DEVICE_GROUP_PRESENT_MODE_LOCAL_MULTI_DEVICE_BIT_KHRʱ��һ��surface���ж�������豸��������ʾ����ѯÿ�������豸����Ӧ��surface�ϵ�һ����ʾ����rectangle
		uint32_t physicalDeviceRenderRegionCount = 0;
		std::vector<VkRect2D> physicalDeviceRenderRegions{};
		vkGetPhysicalDevicePresentRectanglesKHR(physicalDevice, surface/*surface,��������Ч�ľ�������뱻physical device֧�֣��μ�vkGetPhysicalDeviceSurfaceSupportKHR����һ���Եȵ�ƽ̨�������ж�*/, &physicalDeviceRenderRegionCount, nullptr);
		physicalDeviceRenderRegions.resize(physicalDeviceRenderRegionCount);
		vkGetPhysicalDevicePresentRectanglesKHR(physicalDevice, surface/*surface,��������Ч�ľ�������뱻physical device֧�֣��μ�vkGetPhysicalDeviceSurfaceSupportKHR����һ���Եȵ�ƽ̨�������ж�*/, &physicalDeviceRenderRegionCount, physicalDeviceRenderRegions.data());



	}

	// Display Timing Queries �μ�p3132
	{
		//��VK_GOOGLE_display_timing ��չ���

		VkSwapchainKHR swapchain{/*��������һ����Ч��VkSwapchainKHR*/ };

		//��ѯ��ʾ����һ��ˢ��ѭ����RC���ĳ���ʱ��
		VkRefreshCycleDurationGOOGLE refreshCycleDurationGOOGLE{};
		vkGetRefreshCycleDurationGOOGLE(device, swapchain, & refreshCycleDurationGOOGLE);//������ȷ�����˽��
		refreshCycleDurationGOOGLE.refreshDuration = 1;//Ϊһ��ˢ��ѭ���Ŀ�ʼ����һ��ˢ��ѭ���Ŀ�ʼ֮�������ʱ����


		//�첽��ѯ��ʾ���棬�Ի�ȡ���ڸ���swapchain��֮ǰ���µ�һ�λ�����ʾ����صĺ�ʱ��Ϣ
		uint32_t swapchainPresentTimingInfoCount = 0;
		std::vector<VkPastPresentationTimingGOOGLE> pastPresentationTimingGOOGLEs{};
		
		vkGetPastPresentationTimingGOOGLE(device, swapchain, &swapchainPresentTimingInfoCount, nullptr);
		pastPresentationTimingGOOGLEs.resize(swapchainPresentTimingInfoCount);
		vkGetPastPresentationTimingGOOGLE(device, swapchain, &swapchainPresentTimingInfoCount, pastPresentationTimingGOOGLEs.data());//����ɹ�����������һ��Ԫ��
		
		//�ýṹ���е�ֵ����Ҫ��ô���͸�����ʾģʽ VK_PRESENT_MODE_*** �Ĳ�ͬ�������𣬾����3137
		VkPastPresentationTimingGOOGLE &pastPresentationTimingGOOGLE = pastPresentationTimingGOOGLEs[0];//ʱ�䵥λΪ����
		pastPresentationTimingGOOGLE.presentID  = 0;//ΪӦ��ͨ�� VkPresentTimeGOOGLE::presentIDΪ��һ�� vkQueuePresentKHR�����ṩ��һ��ֵ������Ψһȷ��һ�� vkQueuePresentKHR����
		pastPresentationTimingGOOGLE.desiredPresentTime = 1;//ΪӦ��ͨ�� VkPresentTimeGOOGLE::desiredPresentTimeΪ��һ�� vkQueuePresentKHR�����ṩ��һ��ֵ�������ֵ��Ϊ0������ָ��image���������ڸ�ֵ��ʾ��ʱ��֮ǰ������ʾ
		pastPresentationTimingGOOGLE.actualPresentTime = 1;//Ϊswapchain��imageʵ����ʾ��ʱ��
		pastPresentationTimingGOOGLE.earliestPresentTime = 1;//Ϊswapchain��image������ʾ��һ������ʱ��㣬���Ӧ��Ҫ������ VkPresentTimeGOOGLE::desiredPresentTime����image����ʾ�Ļ���ֵ���ܺ�actualPresentTime��ͬ
		pastPresentationTimingGOOGLE.presentMargin = 1;//ָ����vkQueuePresentKHRҪ���类����Ͷ�챻����ıȽϣ���earliestPresentTimeҲ������


	}


	// Present Wait  �μ�p3138   �� VK_KHR_present_wait ��չ��أ��򵥽����Ǵ��� VkPresentIdKHR.presentId��vkQueuePresentKHR���ú�����vkWaitForPresentKHR��������
	

	// WSI Swapchain  �μ�p3138
	{
		/*
		swapchain��һ�������ʾ��surface�ϵ�images�ĳ�������Щimages����ʾ��������,������vulkan�й�����ʡ�Ҫ��vulkan��ʹ����Щͼ����Ҫ����vkAcquireNextImageKHR��ȡ��image��Ȼ�������ز���������ת�������Ƶȵȣ�Ȼ�����vkQueuePresentKHR����ͼ����ʾ�����ͷŸ�image��Ҳ����ͨ��vkReleaseSwapchainImagesEXT���ͷ�image�����������������ʾ��������Ҫimage����device��ʹ�á�
		
		���swapchain������ presentModeΪ VK_PRESENT_MODE_SHARED_DEMAND_REFRESH_KHR ���� VK_PRESENT_MODE_SHARED_CONTINUOUS_REFRESH_KHR�����swapchain��ֻ��һ�������image��vulkan Ӧ�ú���ʾ������ҪЭͬ���з��ʡ������p3139


		*/

		VkSwapchainKHR swapchainKHR{/*��������һ����Ч��VkSwapchainKHR*/};
		

		//��ѯ��Ⱦʱswapchain�еĹ������ʾimage��״̬   ����Ҫ�����ж����swapchain�Ƿ񻹿��ã��μ�p3141 �Խӿڽ��������
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
				swapchainLatencyCreateInfoNV.sType = VK_STRUCTURE_TYPE_MAX_ENUM;//û�ж�����������Ϊ�Ƿ�ֵ
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
			//VkDeviceGroupSwapchainCreateInfoKHR ָ��swapchain����ʹ�õ�һ�� device group present modes ������������ýṹ�壬��Ĭ��modeΪVK_DEVICE_GROUP_PRESENT_MODE_LOCAL_BIT_KHR
			VkDeviceGroupSwapchainCreateInfoKHR& deviceGroupSwapchainCreateInfoKHR = swapchainCreateInfoKHREXT.deviceGroupSwapchainCreateInfoKHR;
			deviceGroupSwapchainCreateInfoKHR.modes = VK_DEVICE_GROUP_PRESENT_MODE_LOCAL_BIT_KHR;//ָ��swapchain����ʹ�õ�һ�� device group present modes����bitλָ��һ��device group present mode

			//VkSwapchainDisplayNativeHdrCreateInfoAMD  ָ������swapchainʱ�ض�����ʾ��HDR֧�ֵĶ������������������ýṹ����Ĭ��localDimmingEnableΪVK_TRUE
			VkSwapchainDisplayNativeHdrCreateInfoAMD& swapchainDisplayNativeHdrCreateInfoAMD = swapchainCreateInfoKHREXT.swapchainDisplayNativeHdrCreateInfoAMD;
			swapchainDisplayNativeHdrCreateInfoAMD.localDimmingEnable = VK_TRUE;//ָ����swapchain�Ƿ���local dimming�����֧��VkDisplayNativeHdrSurfaceCapabilitiesAMD::localDimmingSupport���ֵ����ΪVK_TRUE
			{
				//��swapchain��Ч�ڼ��������local dimming HDR����
				vkSetLocalDimmingAMD(device, swapchainKHR, VK_TRUE);//VkDisplayNativeHdrSurfaceCapabilitiesAMD::localDimmingSupport����Ҫ֧��
			}


			// VkSurfaceFullScreenExclusiveInfoEXT  ָ��Ӧ��ƫ�õ�ȫ����ʾ��Ϊ������������ýṹ�壬�� fullScreenExclusive��Ϊ��VK_FULL_SCREEN_EXCLUSIVE_DEFAULT_EXT
			VkSurfaceFullScreenExclusiveInfoEXT& surfaceFullScreenExclusiveInfoEXT = swapchainCreateInfoKHREXT.surfaceFullScreenExclusiveInfoEXT;
			surfaceFullScreenExclusiveInfoEXT.fullScreenExclusive = VK_FULL_SCREEN_EXCLUSIVE_DEFAULT_EXT;


			//VkSwapchainCounterCreateInfoEXT  ָ������ surface counters��
			VkSwapchainCounterCreateInfoEXT &swapchainCounterCreateInfoEXT = swapchainCreateInfoKHREXT.swapchainCounterCreateInfoEXT;
			swapchainCounterCreateInfoEXT.surfaceCounters = VK_SURFACE_COUNTER_VBLANK_EXT;// VkSurfaceCounterFlagBitsEXT���ֵλ���룬ָ��swapchain���õ�surface counters����ֵ�е�bit���ñ�����surface֧�֣���vkGetPhysicalDeviceSurfaceCapabilities2EXT
			{
				//����ʾ���洦��swapchain�ĵ�һ����ʾ������Ƿ���Ҫ��surface counters�ͻἤ���ѯ�����counter��ֵ
				uint64_t counterValue = 0;
				vkGetSwapchainCounterEXT(device, swapchainKHR, VK_SURFACE_COUNTER_VBLANK_EXT, &counterValue);//���ø�������뱣֤swapchain��һ�����߶����ʾ�����Ѿ���������

			}

			//VkImageCompressionControlEXT  ָ��swapchain�е�image��ѹ������
			VkImageCompressionControlEXT& imageCompressionControlEXT = swapchainCreateInfoKHREXT.imageCompressionControlEXT;
			imageCompressionControlEXT.flags = 0;
			imageCompressionControlEXT.compressionControlPlaneCount = 0;
			imageCompressionControlEXT.pFixedRateFlags = VK_NULL_HANDLE;


			//VkSwapchainPresentModesCreateInfoEXT  ָ��swapchainʹ�õĶ���present mode
			VkSwapchainPresentModesCreateInfoEXT &swapchainPresentModesCreateInfoEXT = swapchainCreateInfoKHREXT.swapchainPresentModesCreateInfoEXT;
			swapchainPresentModesCreateInfoEXT.presentModeCount = 1;//ָ���ṩ��present mode������
			VkPresentModeKHR presentModeKHR = VK_PRESENT_MODE_FIFO_KHR;
			swapchainPresentModesCreateInfoEXT.pPresentModes = &presentModeKHR;//presentModeCount��present mode������ָ��,����Ԫ�ر���������vkGetPhysicalDeviceSurfacePresentModesKHR����surface���ص� VkPresentModeKHR���ϣ�����ЩԪ�ؼ��ϱ����Ǵ���VkSwapchainCreateInfoKHR::presentMode�� VkSurfacePresentModeEXT�����ص�VkSurfacePresentModeCompatibilityEXT::pPresentModes��present modes���Ӽ���VkSwapchainCreateInfoKHR::presentMode��������ڸ�����Ԫ����


			//VkSwapchainPresentScalingCreateInfoEXT   ָ��swapchain�Ͷ�Ӧsurface��ά�Ȳ�ͬʱ���������Ϊ
			VkSwapchainPresentScalingCreateInfoEXT &swapchainPresentScalingCreateInfoEXT = swapchainCreateInfoKHREXT.swapchainPresentScalingCreateInfoEXT;
			swapchainPresentScalingCreateInfoEXT.presentGravityX = VK_PRESENT_GRAVITY_MIN_BIT_EXT;//Ϊ0���ߵ�scalingBehaviorΪVK_PRESENT_SCALING_ONE_TO_ONE_BIT_EXTʱ��surface��ص�x��������ص�����
			swapchainPresentScalingCreateInfoEXT.presentGravityY = VK_PRESENT_GRAVITY_MIN_BIT_EXT;//Ϊ0���ߵ�scalingBehaviorΪVK_PRESENT_SCALING_ONE_TO_ONE_BIT_EXTʱ��surface��ص�y��������ص�����
			swapchainPresentScalingCreateInfoEXT.scalingBehavior = VK_PRESENT_SCALING_ONE_TO_ONE_BIT_EXT;//Ϊ0����swapchain�Ͷ�Ӧsurface��ά�Ȳ�ͬʱ������ŷ���
			/*
			VkSwapchainPresentScalingCreateInfoEXT��Ч�÷�:
			1.���presentGravityXΪ0����presentGravityY����Ϊ0
			2.���presentGravityX��Ϊ0����presentGravityY���벻Ϊ0
			3.scalingBehavior��presentGravityX�Լ�presentGravityYֻ����һ��bit����
			4.scalingBehavior ������һ����surface��Ч�� scaling method���μ�����VkSwapchainCreateInfoKHR::presentMode��VkSurfacePresentModeEXT�����ص�VkSurfacePresentScalingCapabilitiesEXT::supportedPresentScaling
			5.���swapchain�Ժ���һ��VkSwapchainPresentModesCreateInfoEXT ��������scalingBehavior ������һ����surface��Ч�� scaling method���μ�����VkSwapchainPresentModesCreateInfoEXT::pPresentMode��ÿ��Ԫ�ظ�VkSurfacePresentModeEXT�����ص�VkSurfacePresentScalingCapabilitiesEXT::supportedPresentScaling
			6.presentGravityX ������һ����surface��Ч��x-axis present gravity���μ�����VkSwapchainCreateInfoKHR::presentMode��VkSurfacePresentModeEXT�����ص�VkSurfacePresentScalingCapabilitiesEXT::supportedPresentGravityX	
			7.���swapchain�Ժ���һ��VkSwapchainPresentModesCreateInfoEXT ��������presentGravityX ������һ����surface��Ч�� x-axis present gravity���μ�����VkSwapchainPresentModesCreateInfoEXT::pPresentMode��ÿ��Ԫ�ظ�VkSurfacePresentModeEXT�����ص�VkSurfacePresentScalingCapabilitiesEXT::supportedPresentGravityX
			8.presentGravityY ������һ����surface��Ч��y-axis present gravity���μ�����VkSwapchainCreateInfoKHR::presentMode��VkSurfacePresentModeEXT�����ص�VkSurfacePresentScalingCapabilitiesEXT::supportedPresentGravityY
			9.���swapchain�Ժ���һ��VkSwapchainPresentModesCreateInfoEXT ��������presentGravityY ������һ����surface��Ч�� y-axis present gravity���μ�����VkSwapchainPresentModesCreateInfoEXT::pPresentMode��ÿ��Ԫ�ظ�VkSurfacePresentModeEXT�����ص�VkSurfacePresentScalingCapabilitiesEXT::supportedPresentGravityY

			*/

		}
		swapchainCreateInfoKHR.pNext = &swapchainCreateInfoKHREXT.deviceGroupSwapchainCreateInfoKHR;
		swapchainCreateInfoKHR.flags = VK_SWAPCHAIN_CREATE_MUTABLE_FORMAT_BIT_KHR;/* VkSwapchainCreateFlagBitsKHR���ֵλ���룬ָ��swapchain����ʱ�Ĳ���
		VkSwapchainCreateFlagBitsKHR:

		VK_SWAPCHAIN_CREATE_SPLIT_INSTANCE_BIND_REGIONS_BIT_KHR:  ָ��swapchain�д�����image���ͺʹ���imageʱ����һ��swapchian����Ϊ��ǰ�ľ����VkImageSwapchainCreateInfoKHR ������ʹ��VK_IMAGE_CREATE_SPLIT_INSTANCE_BIND_REGIONS_BIT
		VK_SWAPCHAIN_CREATE_PROTECTED_BIT_KHR:  ָ��swapchain�д�����image��protected images
		VK_SWAPCHAIN_CREATE_MUTABLE_FORMAT_BIT_KHR:  ָ��swapchain�д�����image�������������ʹ���swapchainʱָ����format��ͬformat��VkImageView������ʹ�õ�format�о���VkSwapchainCreateInfoKHR.pNext�е�VkImageFormatListCreateInfo���ñ�־Ҳָ����swapchain����ʱ��ͼ��imageUsage���Բ�֧��imageFormat��������Ҫ֧�������image view��format�е�һ��
		VK_SWAPCHAIN_CREATE_DEFERRED_MEMORY_ALLOCATION_BIT_EXT:  ָ��������swapchain�е�image��ȡ�Ƴٷ����ڴ�Ĳ���ֱ����iamge������ͨ��vkAcquireNextImageKHR����vkAcquireNextImage2KHR ��һ�η���
		*/
		swapchainCreateInfoKHR.surface = VkSurfaceKHR{/*��������һ����Ч��VkSurfaceKHR*/};//ָ��������swapchain��imageҪ���ĸ�surface�Ͻ�����ʾ��һ��swapchain�����ɹ������swapchain�͹����ϸ�surface
		swapchainCreateInfoKHR.minImageCount = 1;//ΪӦ����Ҫ�����ٵĿ���ʾ��image��������ʵ��Ҫô���ٴ�����ô��Ŀ���ʾ��image��Ҫôֱ�Ӿʹ���ʧ��
		swapchainCreateInfoKHR.imageFormat = VK_FORMAT_R8G8B8A8_UINT;// VkFormatֵָ��������swapchain��image�ĸ�ʽ
		swapchainCreateInfoKHR.imageColorSpace = VK_COLORSPACE_SRGB_NONLINEAR_KHR;// VkColorSpaceKHRֵָ��swapchain��ν���image�е�����
		swapchainCreateInfoKHR.imageExtent = VkExtent2D{.width = 1,.height = 1};//Ϊswapchain��image�����ؼ���Ĵ�С�������vkGetPhysicalDeviceSurfaceCapabilitiesKHR���ص�surface��currentExtent��ƥ�����ֵ�Ĵ�����Ϊ�ǻ���ƽ̨��
		swapchainCreateInfoKHR.imageArrayLayers = 1;//Ϊmultiview/stereo surface�е�view��ͼ�ĸ��������Ϊnon-stereoscopic-3D Ӧ�ã����ֵΪ1
		swapchainCreateInfoKHR.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;// VkImageUsageFlagBits���ֵλ����������Ӧ�û�ȡ��swapchian��image����ܵ��÷�
		swapchainCreateInfoKHR.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;//swapchain�е�image�ڶ������Ĺ���ģʽ
		swapchainCreateInfoKHR.queueFamilyIndexCount = 1;//ΪimageSharingMode Ϊ VK_SHARING_MODE_CONCURRENTʱ�����Է���swapchain�е�image�Ķ����������
		uint32_t imageQueue = 0;
		swapchainCreateInfoKHR.pQueueFamilyIndices = &imageQueue;//ΪimageSharingMode Ϊ VK_SHARING_MODE_CONCURRENTʱ�����Է���swapchain�е�image�Ķ����������ֵ������ָ��
		swapchainCreateInfoKHR.preTransform = VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR;//VkSurfaceTransformFlagBitsKHRֵ��������image��ʾ֮�䣬�������ݸ�����ʾ����ı���������е���ת�任�����������ֵ��vkGetPhysicalDeviceSurfaceCapabilitiesKHR���ص�currentTransform ��ƥ�䣬����ʾ���潫���image�����ݱ任������Ϊ��ͼ����ʾ������һ����
		swapchainCreateInfoKHR.compositeAlpha = VK_COMPOSITE_ALPHA_INHERIT_BIT_KHR;// VkCompositeAlphaFlagBitsKHRֵָ����ָ��ϵͳ�Ϻ�����surface���ʱ��alpha ���ģʽ
		swapchainCreateInfoKHR.presentMode = VK_PRESENT_MODE_FIFO_KHR;//Ϊswapchainʹ�õ���ʾģʽ��swapchain����ʾģʽ��������δ�����ĵ�ǰ��ʾ�������ڲ��Ŷ�
		swapchainCreateInfoKHR.clipped = VK_TRUE;//ָ���Ƿ�����vulkanʵ�ֶ���������surface�в��ɼ��������Ⱦ����
		swapchainCreateInfoKHR.oldSwapchain = VK_NULL_HANDLE;//ΪVK_NULL_HANDLE����һ��������surface��δ����retired״̬��swapchian���ṩ�ò�����Ҫ��������Դ�����Լ�Ӧ����Ȼ���Լ�����ʾ�Ѿ���oldSwapchian�л�ȡ����image
		/*
		VkSwapchainCreateInfoKHR��Ч�÷�:
		1.surface �������豸֧�ֵģ���vkGetPhysicalDeviceSurfaceSupportKHR���صĽ������
		2.minImageCount ����С�ڵ��ڵ���vkGetPhysicalDeviceSurfaceCapabilitiesKHR����surface���ص�VkSurfaceCapabilitiesKHR��maxImageCount�������ֵ��Ϊ0��
		3.���presentMode �Ȳ���VK_PRESENT_MODE_SHARED_DEMAND_REFRESH_KHR Ҳ���� VK_PRESENT_MODE_SHARED_CONTINUOUS_REFRESH_KHR����minImageCount ����С�ڵ��ڵ���vkGetPhysicalDeviceSurfaceCapabilitiesKHR����surface���ص�VkSurfaceCapabilitiesKHR��maxImageCount
		4.���presentMode ΪVK_PRESENT_MODE_SHARED_DEMAND_REFRESH_KHR����VK_PRESENT_MODE_SHARED_CONTINUOUS_REFRESH_KHR�е�һ������minImageCount ����Ϊ1
		5.imageFormat ��imageColorSpace ����͵���vkGetPhysicalDeviceSurfaceFormatsKHR����surface���ص�VkSurfaceFormatKHR�е�format�Լ�colorSpace һһ��Ӧƥ��
		6.���pNext�в�����VkSwapchainPresentScalingCreateInfoEXT�����߰���һ��scalingBehaviorΪ0��VkSwapchainPresentScalingCreateInfoEXT����imageExtent�ķ�Χ���������[minImageExtent,maxImageExtent]֮�䣬����minImageExtent��maxImageExtentΪ����vkGetPhysicalDeviceSurfaceCapabilitiesKHR����surface���ص�VkSurfaceCapabilitiesKHR�еĳ�Ա
		7.���pNext�а���VkSwapchainPresentScalingCreateInfoEXT����scalingBehavior��Ϊ0����imageExtent�ķ�Χ���������[minScaledImageExtent,maxScaledImageExtent]֮�䣬����minScaledImageExtent��maxScaledImageExtentΪ����vkGetPhysicalDeviceSurfaceCapabilities2KHR����surface�Լ�presentMode���ص�VkSurfacePresentScalingCapabilitiesEXT�еĳ�Ա
		8.imageExtent��width�Լ�height���붼�Ƿ�0ֵ
		9.imageArrayLayers �������0��С�ڵ��ڵ���vkGetPhysicalDeviceSurfaceCapabilitiesKHR����surface���ص�VkSurfaceCapabilitiesKHR��maxImageArrayLayers
		10.���presentModeΪVK_PRESENT_MODE_IMMEDIATE_KHR, VK_PRESENT_MODE_MAILBOX_KHR, VK_PRESENT_MODE_FIFO_KHR ���� VK_PRESENT_MODE_FIFO_RELAXED_KHR��imageUsage������һ������vkGetPhysicalDeviceSurfaceCapabilitiesKHR����surface���ص�VkSurfaceCapabilitiesKHR��supportedUsageFlags�е��Ӽ�
		11.���presentModeΪVK_PRESENT_MODE_SHARED_DEMAND_REFRESH_KHR ���� VK_PRESENT_MODE_SHARED_CONTINUOUS_REFRESH_KHR��imageUsage������һ������vkGetPhysicalDeviceSurfaceCapabilities2KHR����surface���ص�VkSharedPresentSurfaceCapabilitiesKHR��sharedPresentSupportedUsageFlags�е��Ӽ�
		12.���imageSharingMode ΪVK_SHARING_MODE_CONCURRENT����1��pQueueFamilyIndices ��������Ч��queueFamilyIndexCount��uint32_tֵ������ָ��
																��2��queueFamilyIndexCount �������1
																��3��pQueueFamilyIndices�е�ÿ��Ԫ�ر�����Ψһ�ģ��ұ���С�ڵ���vkGetPhysicalDeviceQueueFamilyProperties����vkGetPhysicalDeviceQueueFamilyProperties2���ص�pQueueFamilyPropertyCount����ֵָ��������ĸ�����
		13.preTransform �����ǵ���vkGetPhysicalDeviceSurfaceCapabilitiesKHR����surface���ص�VkSurfaceCapabilitiesKHR�е�supportedTransforms�е�һ��bit����
		14.compositeAlpha �����ǵ���vkGetPhysicalDeviceSurfaceCapabilitiesKHR����surface���ص�VkSurfaceCapabilitiesKHR�е�supportedCompositeAlpha�е�һ��bit����
		15.presentMode �����ǵ���vkGetPhysicalDeviceSurfacePresentModesKHR����surface���ص�VkPresentModeKHR�е�һ��
		16.����߼��豸��VkDeviceGroupDeviceCreateInfo::physicalDeviceCountΪ1��������flags���ܰ���VK_SWAPCHAIN_CREATE_SPLIT_INSTANCE_BIND_REGIONS_BIT_KHR
		17.���oldSwapchain��ΪVK_NULL_HANDLE����oldSwapchain ������һ��������surface��Ӧ�õ�native window�� non-retired swapchain
		18.swapchain��������image�����������뱻֧�֣���vkGetPhysicalDeviceImageFormatProperties���ص���Ϣ
		19.���flags����VK_SWAPCHAIN_CREATE_MUTABLE_FORMAT_BIT_KHR��pNext�б������һ��viewFormatCount����0��pViewFormats�б�����һ��Ԫ�ص��� imageFormat��VkImageFormatListCreateInfo
		20.���pNext�а���VkImageFormatListCreateInfo������viewFormatCount ��Ϊ0������pViewFormats�����е�format������о���compatibility table��������format���ݣ��μ�p4067�� 
		21.���flags������VK_SWAPCHAIN_CREATE_MUTABLE_FORMAT_BIT_KHR��pNext�а���һ��VkImageFormatListCreateInfo������viewFormatCount����Ϊ0����1
		22.���flags����VK_SWAPCHAIN_CREATE_PROTECTED_BIT_KHR�������vkGetPhysicalDeviceSurfaceCapabilities2KHR����surface���ص�VkSurfaceProtectedCapabilitiesKHR::supportsProtected ����ΪVK_TRUE
		23.���pNext�а���fullScreenExclusive����ΪVK_FULL_SCREEN_EXCLUSIVE_APPLICATION_CONTROLLED_EXT��VkSurfaceFullScreenExclusiveInfoEXT��surface��vkCreateWin32SurfaceKHR��������pNext��Ҳ�������һ��VkSurfaceFullScreenExclusiveWin32InfoEXT
		24.���imageCompressionControlSwapchain ����δ��������pNext�в��ܰ���VkImageCompressionControlEXT
		*/


		//����swapchain
		vkCreateSwapchainKHR(device, &swapchainCreateInfoKHR/*pCreateInfo��ָ������swapchain����Ϣ*/, nullptr, &swapchainKHR);
		/*
		vkCreateSwapchainKHR���˵��:

		������swapchain�е�image��Ч��vulkan����������Ϣ������image:
		VkImageCreateInfo Field										Value
					flags									�������swapchain����VK_SWAPCHAIN_CREATE_SPLIT_INSTANCE_BIND_REGIONS_BIT_KHR��
																��ȼ��ڴ���һ������ VK_IMAGE_CREATE_SPLIT_INSTANCE_BIND_REGIONS_BIT��image��
															�������swapchain����VK_SWAPCHAIN_CREATE_PROTECTED_BIT_KHR��
																��ȼ��ڴ���һ������ VK_IMAGE_CREATE_PROTECTED_BIT��image��
															�������swapchain����VK_SWAPCHAIN_CREATE_MUTABLE_FORMAT_BIT_KHR��
																��ȼ��ڴ���һ������ VK_IMAGE_CREATE_PROTECTED_BIT�� VK_IMAGE_CREATE_EXTENDED_USAGE_BIT_KHR��image��
															������������image��־
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
		
		������Ϣ��p3143
		*/


		//����swapchain
		vkDestroySwapchainKHR(device, swapchainKHR, nullptr);
		/*
		vkDestroySwapchainKHR��Ч�÷�:
		1.���д�swapchain�л�ȡ��image�����Ѿ������ִ��
		2.�������swapchainʱ�ṩ��VkAllocationCallbacks������������ṩһ�����ݵ�callbakcs
		3.�������swapchainʱδ�ṩVkAllocationCallbacks��������pAllocator����ΪNULL

		*/


		//��VK_KHR_display_swapchain ��չ���������swapchain���Թ���image
		vkCreateSharedSwapchainsKHR(device, 1, &swapchainCreateInfoKHR, nullptr, &swapchainKHR);


		//��ȡswapchain�е�һ��image��  �������ڴ���VkImage��ʱ������VkImageCreateInfo.pNext�м���һ��VkImageSwapchainCreateInfoKHR������һ��swapchain�е�image����ʹ��vkBindImageMemory2 ����VkBindImageMemorySwapchainInfoKHR �󶨵�һ��swapchain�е��ڴ棬����������¸�VkImage��Ҫ�ֶ�����
		uint32_t imageCount = 0;
		std::vector<VkImage> presentImages;
		vkGetSwapchainImagesKHR(device, swapchainKHR, &imageCount, nullptr);
		presentImages.resize(imageCount);
		vkGetSwapchainImagesKHR(device, swapchainKHR, &imageCount, presentImages.data());


		//��ȡswapchain��һ�����õ�image�������������� 
		uint32_t imageIndex = 0;
		VkResult acquireImageResult =  vkAcquireNextImageKHR(device, swapchainKHR, VK_TIMEOUT, VkSemaphore{/*��������һ����Ч��VkSemaphore*/ }/*Ϊһ��������semaphore*/, VkFence{/*��������һ����Ч��VkFence*/ }/*Ϊһ��������fence*/, & imageIndex/*������һ�����õ�image������*/);
		/*
		1.swapchain ���ܴ���retired state
		2.semaphore �������VK_NULL_HANDLE��1��������unsignaled״̬
											��2���������κ�δ��ɵ��źŻ�ȴ�����
		3.���fence����VK_NULL_HANDLE�����������unsignaled״̬���Ҳ��ܹ������κ�ִ�������������ϻ�δ��ɵ�����
		4.semaphore ��fence ����ͬʱΪVK_NULL_HANDLE
		5.�����pAcquireInfo�д���swapchian��surface�Ĳ��ܱ�֤ǰ��Ĵ�����pAcquireInfo->timeout ����ΪUINT64_MAX
		6.semaphore ��VkSemaphoreType ������VK_SEMAPHORE_TYPE_BINARY

		*/


		acquireImageResult;//vkAcquireNextImageKHR���صĽ��˵��
		/*
		VK_SUCCESS:  �ɹ�����һ�����õ�image
		VK_ERROR_SURFACE_LOST_KHR:  ָ��surface���ٿ���
		VK_NOT_READY: ָ��timeoutΪ0�ҷ���ʱû�п��õ�image
		VK_TIMEOUT: ָ���ڳ�����timeout��[0,UINT64_MAX]ָ����һ��ֵʱ����û�п��õ�image
		VK_SUBOPTIMAL_KHR:  ָ��һ��image���ã�����ʱswapchain�Ѿ�����ƥ�䵱ǰ��surface�ˣ�������Ȼ���Գɹ�������ʾ��surface��
		VK_ERROR_OUT_OF_DATE_KHR: ָ��surface�Ѿ��ı䲻�ټ���swapchain��������ʾ�����ֱ��ʧ�ܣ���������������Ҫ������ʾ����Ҫ���²�ѯsurface�����Բ����´���swapchain	
		*/


		//��ȡswapchain��һ�����õ�image��������������2 
		VkAcquireNextImageInfoKHR acquireNextImageInfoKHR{};
		acquireNextImageInfoKHR.sType = VK_STRUCTURE_TYPE_ACQUIRE_NEXT_IMAGE_INFO_KHR;
		acquireNextImageInfoKHR.pNext = nullptr;
		acquireNextImageInfoKHR.timeout = VK_TIMEOUT;//ָ��û��image����ʱ�ú�����Ҫ�ȴ���������
		acquireNextImageInfoKHR.swapchain = swapchainKHR;//ָ�����ĸ�swapchain��ȡimage
		acquireNextImageInfoKHR.semaphore = VkSemaphore{/*��������һ����Ч��VkSemaphore*/ };//Ϊһ��������semaphore
		acquireNextImageInfoKHR.fence = VkFence{/*��������һ����Ч��VkFence*/ };//Ϊһ��������fence
		acquireNextImageInfoKHR.deviceMask = 0x00000001;//��һ���豸����ָ��semaphore����fence�������ĸ��豸��ʹ�ø�image
		/*
		VkAcquireNextImageInfoKHR��Ч�÷�:
		1.swapchain ���ܴ���retired state
		2.semaphore �������VK_NULL_HANDLE��1��������unsignaled״̬
											��2���������κ�δ��ɵ��źŻ�ȴ�����
		3.���fence����VK_NULL_HANDLE�����������unsignaled״̬���Ҳ��ܹ������κ�ִ�������������ϻ�δ��ɵ�����
		4.semaphore ��fence ����ͬʱΪVK_NULL_HANDLE
		5.deviceMask ������һ����Ч���豸���룬�Ҳ���Ϊ0
		6.semaphore ��VkSemaphoreType ������VK_SEMAPHORE_TYPE_BINARY

		*/

		vkAcquireNextImage2KHR(device, &acquireNextImageInfoKHR, &imageIndex);//�����pAcquireInfo�д���swapchian��surface�Ĳ��ܱ�֤ǰ��Ĵ�����pAcquireInfo->timeout ����ΪUINT64_MAX


		//�ڽ�����һϵ�л��ƺ�ͼ��layoutת���󣬿��Խ���Ҫ��ʾ��image�����Ŷ���ʾ��surface��,   surface��ʾ�ı��������ǻ���ƽ̨�ģ�һ��Ĭ�����Ͻ�Ϊ����ԭ�㣨0��0����������Ϣ��p3172
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
					frameBoundaryEXT.sType = VK_STRUCTURE_TYPE_MAX_ENUM;//δ�����������ﶨ��Ϊ�Ƿ�ֵ
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
				//�� VK_KHR_incremental_present��չ����ʱ������ͨ������VkPresentRegionsKHR������ʾ����һ����ʾ��ָ����ʾ��image��ֻ��ĳ���ض�������ı��ˣ����������ʾ����ֻȥ������Щ�ı��˵�����
				VkPresentRegionsKHR& presentRegionsKHR = presentInfoKHREXT.presentRegionsKHR;
				presentRegionsKHR.swapchainCount = 1;//ָ��swapchain������,������� VkPresentInfoKHR::swapchainCount
				VkPresentRegionKHR changedRegion{};
				{
					changedRegion.rectangleCount = 1;//pRectangles��Ԫ�ظ���������Ϊ0ָ������image���ı�����Ҫ����
					VkRectLayerKHR rectLayer{};//�ýṹ��ָ�����������򲻻ᱻ����Ӱ��
					{
						rectLayer.layer = 0;//ָ���������Ϊimage���ĸ�layer
						rectLayer.offset = VkOffset2D{ .x = 0,.y = 0 };//ָ��������������ԭ��
						rectLayer.extent = VkExtent2D{ .width = 1,.height = 1 };//ָ�������������Ĵ�С
						/*
						VkRectLayerKHR��Ч�÷�:
						1.offset + extent �ĺ��ھ���VkSwapchainCreateInfoKHR��preTransform�任�󣬲��ܴ��ڴ���swapchainʱ��VkSwapchainCreateInfoKHR��imageExtent
						2.layer ����С�ڴ���swapchainʱ��VkSwapchainCreateInfoKHR��imageArrayLayers
						*/
					}
					changedRegion.pRectangles = &rectLayer;//ΪNULL���� һ�� VkRectLayerKHR ������ָ�룬VkRectLayerKHRָ���ı��˵��������Ե�image��layer�Լ�framebuffer coordinates����Щ����Ҫ������VkSurfaceCapabilitiesKHR::currentTransform,�����ù�swapchain�� preTransform����ʾ�����Ϊ��Щ����ִ�� preTransform �任����
				}
				presentRegionsKHR.pRegions = &changedRegion;//ΪNULL���� swapchainCount��VkPresentRegionKHR ������ָ�룬ָ��swapchain�������һ����ʾ֮����µ�image������

				
				//������ VK_KHR_display_swapchainʱ������ָ����ʾ����ʾ�Ķ�����Ϣ ,���srcRect��dstRect��extent��ͬ����Ӧ��ȡ��������
				VkDisplayPresentInfoKHR &displayPresentInfoKHR = presentInfoKHREXT.displayPresentInfoKHR;
				displayPresentInfoKHR.srcRect = VkRect2D{ .offset = VkOffset2D{.x = 0,.y = 0},.extent = VkExtent2D {.width = 1,.height = 1} };//Ϊ��Ҫ��ʾ�����ؾ������򣬸������������ʾigame�Ĵ�С��Χ�ڣ�����ýṹ�岻ָ�����ֵ�൱��Ĭ�ϸ�ֵΪ������ʾimage
				displayPresentInfoKHR.dstRect = VkRect2D{ .offset = VkOffset2D{.x = 0,.y = 0},.extent = VkExtent2D {.width = 1,.height = 1} };//Ϊswapchain��display mode�µĿ��Ӿ������򣬣�����ýṹ�岻ָ�����ֵ�൱��Ĭ�ϸ�ֵΪ����swapchain�Ŀ����������ָ��������Ϊdisplay mode�Ŀ��������һ���Ӽ��������swapchain��plane�µ�display play��ָ��������������ǿɼ��ģ����swapchain��û��plane����display play��ָ��������������ǲ��ɼ��ģ����ָ����������һ������display plane�Ŀ��������⣬��ӳ�䵽��������һ���ֵ����ػᱻ����
				displayPresentInfoKHR.persistent = VK_TRUE;//�������VK_TRUE������ʾ���潫��֧��������ʾ�������û���ģʽ����������ʾ����ֹͣ����ʾ���������ݣ�ֱ�����ֳ��µ�ͼ����ʾ�����������һ�����ֵ�ͼ��ĸ�����������ʹ�ø��ٵĹ��ʣ������ܻ����ӱ�ʾ�ӳ١����û��ָ���ýṹ�壬�򽫲���ʹ�ó־�ģʽ��
				/*
				VkDisplayPresentInfoKHR��Ч�÷�:
				VkDisplayPresentInfoKHR��Ч�÷�:
				1.srcRect ����ָ������ʾigame�Ĵ�С��Χ�ڵ��Ӽ�
				2.dstRect ����ָ��swapchainʹ�õ�display mode��visibleRegionָ���Ŀ��ӷ�Χ�ڵ��Ӽ�
				3.�������vkGetPhysicalDeviceDisplayPropertiesKHR���صĶ�Ӧ��display��VkDisplayPropertiesKHR��persistentContentΪVK_FALSE����persistent ����ΪVK_FALSE
				*/


				//VkDeviceGroupPresentInfoKHR ָ��һ���豸�����һ��device group present mode  ����������ýṹ�����swapchainCountΪ0�������Ϊ�豸����Ϊ1����������ýṹ�����ΪmodeΪVK_DEVICE_GROUP_PRESENT_MODE_LOCAL_BIT_KHR
				VkDeviceGroupPresentInfoKHR& deviceGroupPresentInfoKHR = presentInfoKHREXT.deviceGroupPresentInfoKHR;
				deviceGroupPresentInfoKHR.swapchainCount = 1;//Ϊ0����pDeviceMasks��Ԫ�ظ���
				uint32_t deviceMask = 0x00000001;
				deviceGroupPresentInfoKHR.pDeviceMasks = &deviceMask;//һ���豸����uint32_t����ָ�룬һһ��ӦVkPresentInfoKHR::pSwapchains
				deviceGroupPresentInfoKHR.mode = VK_DEVICE_GROUP_PRESENT_MODE_LOCAL_BIT_KHR;// VkDeviceGroupPresentModeFlagBitsKHRֵ��ָ����ʾʹ�õ� device group present mode�����������Ӧ����Ĳ�����p3181
				/*
				VkDeviceGroupPresentInfoKHR��Ч�÷�:
				1.swapchainCount����0����VkPresentInfoKHR::swapchainCount
				2.���modeΪVK_DEVICE_GROUP_PRESENT_MODE_LOCAL_BIT_KHR����pDeviceMasks��ÿ��Ԫ��ֻ�ܺ���һ��bit���ã�����VkDeviceGroupPresentCapabilitiesKHR::presentMask��ӦԪ�ز���Ϊ����ֵ
				3.���modeΪVK_DEVICE_GROUP_PRESENT_MODE_REMOTE_BIT_KHR����pDeviceMasks��ÿ��Ԫ��ֻ�ܺ���һ��bit���ã����߼��豸�е�һЩ�����豸��������VkDeviceGroupPresentCapabilitiesKHR::presentMask�а�����bit����
				4.���modeΪVK_DEVICE_GROUP_PRESENT_MODE_SUM_BIT_KHR����pDeviceMasks��ÿ��Ԫ�ر�����������bit����������VkDeviceGroupPresentCapabilitiesKHR::presentMask ��һ��Ԫ����
				5.���modeΪVK_DEVICE_GROUP_PRESENT_MODE_LOCAL_MULTI_DEVICE_BIT_KHR����pDeviceMasks��ÿ��Ԫ�ص�ÿ��bit���ã�����VkDeviceGroupPresentCapabilitiesKHR::presentMask��ӦԪ�ز���Ϊ����ֵ
				6.pDeviceMasks�е�ÿ��Ԫ�ص�ֵ�������swapchain�ж�Ӧimage������������ȡʱ��VkAcquireNextImageInfoKHR::deviceMask��ֵ
				7.mode ����ֻ��һ��bit���ã��Ҹ�bit���ñ��������VkDeviceGroupSwapchainCreateInfoKHR::modes��
				*/


				//�� VK_GOOGLE_display_timing��չ������VkPresentTimesInfoGOOGLE ��������������ʾ����һ��ͼƬӦ�ñ���ʾ������ʱ�䣬������������stutter
				VkPresentTimesInfoGOOGLE &presentTimesInfoGOOGLE = presentInfoKHREXT.presentTimesInfoGOOGLE;
				presentTimesInfoGOOGLE.swapchainCount = 1;//ָ�������swapchian���������������VkPresentInfoKHR::swapchainCount
				VkPresentTimeGOOGLE earliestDisplayTime{};
				{
					earliestDisplayTime.presentID = 0;//��Ӧ�ó����ṩ�����ڱ�ʶ��ֵ��������vkGetPastPresentationTimingGOOGLE���صĽ��һ��ʹ�ã��Ա�Ψһ��ʶ��һ����ʾpresent������Ϊ�˶�Ӧ�ó������ã�����һ��ʱ���ڶ�Ӧ�ó�����Ӧ����Ψһ��
					earliestDisplayTime.desiredPresentTime = 0;//ָ����Ӧ�ý�ͼ���ڸ�ֵָ����ʱ��֮ǰ������ʾ����ʱ����һ��������Ϊ��λ�������һ������������ʱ�ӣ����磬�ڰ�׿��Linux�ϵ�CLOCK_MONOTONIC����clock_gettime(2)������ֵΪ���ʾ��ʾ����������κ�ʱ����ʾͼ�񡣵�Ӧ�ó���ϣ���ṩ presentID������Ҫָ���ض�����ʾʱ��������ʹ�á�
				}
				presentTimesInfoGOOGLE.pTimes = &earliestDisplayTime;//ΪNULL���� swapchainCount��VkPresentTimeGOOGLE������ָ�룬ָ�� VkPresentInfoKHR::pImageIndices��ָ����image��������ʾʱ��


				VkPresentIdKHR& presentIdKHR = presentInfoKHREXT.presentIdKHR;
				presentIdKHR.swapchainCount = 1;//ָ�������swapchian������
				uint64_t presentId = 0;
				presentIdKHR.pPresentIds = &presentId;//ΪNULL���� swapchainCount��uint64_t������ָ�룬ָ�������� VkPresentInfoKHR::pImageIndices��ָ����image����ʾ������һ����ʶid
				/*
				VkPresentIdKHR��Ч�÷�:
				1.swapchainCount�������VkPresentInfoKHR::swapchainCount
				2.presentIds��ÿ��Ԫ�ص�ֵ������ڴ��ݸ�pSwapchains�ж�Ӧswapchain����ǰ��ʾ��presentId
				*/
				{
					//��������� presentWait ���ԣ�����Եȴ�ĳ��presentId������swapchain��image����ʾ������ɣ� �õȴ�������Ҫ�ǵȴ�������swapchain�ĵ�ǰpresentId��ֵ�������������ֵ������swapchain�е�ǰ��presentId����ҪΪ�����ֵ
					vkWaitForPresentKHR(device, swapchainKHR/*swapchain,ָ���ĸ���ʾimage�� non-retired swapchain*/, 0/*presentId��ָ��Ҫ�ȴ�����ʾ����������presentId*/, VK_TIMEOUT/*timeout, ָ��������Ϊ��λ�ĵȴ���ʱʱ��*/);
					/*
					vkWaitForPresentKHR��Ч�÷�:
					1.swapchain ���ܴ���retired state
					2.presentWait ���Ա��뿪��
					*/
				}


				//������ VK_GGP_frame_token ��չ������ʾswapchian�е�imageʱ����ͨ��  VkPresentFrameTokenGGPָ��Google Games Platform frame token
				VkPresentFrameTokenGGP& presentFrameTokenGGP = presentInfoKHREXT.presentFrameTokenGGP;
				GgpFrameToken frameToken{};
				presentFrameTokenGGP.frameToken = frameToken;//ָ��Ҫ��ʾ��image��Google Games Platform frame token,������һ����Ч��GgpFrameToken


				//VkSwapchainPresentModeInfoEXT ָ����swapchain�����ڵ�ǰ�Լ�������ʾ������present mode�����Ըı䴴��swapchainʱָ����present mode��ǰ������resent mode֮����л���ѭһ������������mode��������Ҫ����һ��Ҫ�󣬾��������p3188
				VkSwapchainPresentModeInfoEXT& swapchainPresentModeInfoEXT = presentInfoKHREXT.swapchainPresentModeInfoEXT;
				swapchainPresentModeInfoEXT.swapchainCount = 1;//Ϊswapchain���������������VkPresentInfoKHR::swapchainCount
				VkPresentModeKHR presenMode = VK_PRESENT_MODE_FIFO_KHR;
				swapchainPresentModeInfoEXT.pPresentModes = &presenMode;//ΪNULL����swapchainCount��VkPresentModeKHR������ָ�룬ָ��swapchain�����ڵ�ǰ�Լ�������ʾ������present mode�� ��Щpresent mode�����о��ڴ������Ӧswapchain��VkSwapchainPresentModesCreateInfoEXT::pPresentModes��


				VkSwapchainPresentFenceInfoEXT& swapchainPresentFenceInfoEXT = presentInfoKHREXT.swapchainPresentFenceInfoEXT;
				swapchainPresentFenceInfoEXT.swapchainCount = 1;//Ϊswapchain���������������VkPresentInfoKHR::swapchainCount���������0
				VkFence presenFinishFence{/*��������һ����Ч��VkFence*/ };
				swapchainPresentFenceInfoEXT.pFences = &presenFinishFence;//��swapchainCount ��VkFence������ָ�룬ָ���ύ����ʾ�������ʱҪ������fence����Щfence�������VK_NULL_HANDLE�������δ�����ģ�������˳������ʾ������˳�����




			}
			presentInfoKHR.pNext = &presentInfoKHREXT.deviceGroupPresentInfoKHR;
			presentInfoKHR.swapchainCount = 1;//ָ��Ҫ�����swapchain������
			presentInfoKHR.pSwapchains = &swapchainKHR;//swapchainCount��VkSwapchainKHR������ָ�룬 ָ��Ҫ�����swapchain
			presentInfoKHR.pImageIndices = &imageIndex;//swapchainCount��uint32_t������ָ�룬ָ����ӦpSwapchains�е�swapchainҪ��ʾ��image������������ʾǰ��Щimage�Ĳ��ֱ���Ҫת��ΪVK_IMAGE_LAYOUT_PRESENT_SRC_KHR����VK_IMAGE_LAYOUT_SHARED_PRESENT_KHR
			VkResult presentResult{};
			presentInfoKHR.pResults = &presentResult;//swapchainCount��VkResult������ָ��,ָ������swapchain�е�image����ʾ������������Ҫ��ȡ����������ΪNULL
			presentInfoKHR.waitSemaphoreCount = 1;//Ϊ������ʾ����֮ǰ��Ҫ�ȴ���semaphore������������Ϊ0
			VkSemaphore waitSemaphroe{/*��������һ����Ч��VkSemaphore*/ };
			presentInfoKHR.pWaitSemaphores = &waitSemaphroe;//ΪNULL���ߺ�waitSemaphoreCount�� VkSemaphore������ָ�룬ָ��������ʾ����֮ǰ��Ҫ�ȴ���semaphore
			/*
			VkPresentInfoKHR��Ч�÷�:
			1.pSwapchain��ÿ��Ԫ�ر���ʱΨһ��
			2.pImageIndices�е�ÿ��Ԫ�ر����Ǵ�pSwapchains��Ӧswapchain�л�ȡ��image������ֵ���Ҹ�image��subresource������ִ�и�����ǰ�Ѿ�ת����VK_IMAGE_LAYOUT_PRESENT_SRC_KHR ���� VK_IMAGE_LAYOUT_SHARED_PRESENT_KHR layout
			3.���pNext�а���VkPresentIdKHR����presentId����δ��������VkPresentIdKHR�е�presentIds��ÿ��Ԫ�ر���ΪNULL
			4.���pSwapchains���κ�Ԫ�ص�swapchain�Ժ���VkSwapchainPresentModesCreateInfoEXT��������pSwapchains������Ԫ�ص�swapchainҲ�����Ժ���VkSwapchainPresentModesCreateInfoEXT����
			*/



			vkQueuePresentKHR(VkQueue{/*��������һ����Ч��VkQueue*/ }/*queue*/, & presentInfoKHR);
			/*
			vkQueuePresentKHR��Ч�÷�:
			1.pPresentInfo��pSwapchains��ÿ��swapchain����������queue��֧����ʾ��surface�����ģ��μ�vkGetPhysicalDeviceSurfaceSupportKHR
			2.���pPresentInfo��pSwapchains�г���1����swapchain��display surface�ϴ��������������õ���ͬ��ʾ��desplay��display surface����ʹ����ͬ��display mode
			3.��pPresentInfo��pWaitSemaphores��Ԫ�ض��������õ�һ��binary semaphoreִ����queue�ϵ�semaphore wait����ʱ�������������Ķ����ڵȴ���semaphore
			4.pPresentInfo��pWaitSemaphores������Ԫ�ر�����VkSemaphoreType ΪVK_SEMAPHORE_TYPE_BINARY ����
			5.pPresentInfo��pWaitSemaphores������Ԫ�ر������õ�һ��signal �����Ѿ��ύִ�е�����������semaphore signal ����Ҳ�ύִ�е�semaphore
			*/


			//�ͷ�֮ǰͨ��vkAcquireNextImage2KHR ����vkAcquireNextImageKHR ��ȡ��swapchain�е�image ,ֻ����Щimage���ٱ��豸ʹ�òſ����ͷţ��ͷŲ��ı���Щimage�����ݵĲ���
			VkReleaseSwapchainImagesInfoEXT releaseSwapchainImagesInfoEXT{};
			releaseSwapchainImagesInfoEXT.sType = VK_STRUCTURE_TYPE_RELEASE_SWAPCHAIN_IMAGES_INFO_EXT;
			releaseSwapchainImagesInfoEXT.pNext = nullptr;
			releaseSwapchainImagesInfoEXT.swapchain = swapchainKHR;//ָ��Ҫ�ͷŵ�image���ڵ�swapchain
			releaseSwapchainImagesInfoEXT.imageIndexCount = 1;//��Ҫ�ͷŵ�image�ĸ���
			releaseSwapchainImagesInfoEXT.pImageIndices = &imageIndex;//��imageIndexCount ��swapchain��Ҫ�ͷŵ�image������ֵ������ָ��
			/*
			VkReleaseSwapchainImagesInfoEXT��Ч�÷�:
			1.pImageIndices �е�ÿ��Ԫ�ر����Ǵ�swapchain�л�ȡ��image������ֵ
			2.��pImageIndices �е�ÿ��Ԫ�����õ�image������ʹ�ò��������Ѿ������ִ��
			*/

			vkReleaseSwapchainImagesEXT(device, &releaseSwapchainImagesInfoEXT);



		}


	}


	//Hdr Metadata  �μ�p3192
	{
		/*
		�ý���������θĽ����ݵ���ɫ���֣��Ը��õ���������ʾ���Ͽ�������ɫ�����¶�����������ص�SMPTE 2086��CTA 861.3��CIE 15��2004�淶
		*/

		VkSwapchainKHR swapchainKHR{/*��������һ����Ч��VkSwapchainKHR*/};

		//�ṩʵ��һ�� Hdr metadata,��Щmetdata����Ӧ�õ�swapchain����һ����ʾ������
		VkHdrMetadataEXT hdrMetadataEXT{};
		hdrMetadataEXT.sType = VK_STRUCTURE_TYPE_HDR_METADATA_EXT;
		hdrMetadataEXT.pNext = nullptr;
		hdrMetadataEXT.displayPrimaryRed = VkXYColorEXT{ .x = 0,.y = 0 };//Ϊ VkXYColorEXTֵָ����ʾ���ĺ��ɫ��ɫ������ chromaticity coordinates��ָ�� x �� y chromaticity coordinate��Chromaticity coordinates�μ� CIE 15:2004
		hdrMetadataEXT.displayPrimaryGreen = VkXYColorEXT{ .x = 0,.y = 0 };//Ϊ VkXYColorEXTֵָ����ʾ�����̻�ɫ��ɫ������ chromaticity coordinates��ָ�� x �� y chromaticity coordinate��Chromaticity coordinates�μ� CIE 15:2004
		hdrMetadataEXT.displayPrimaryBlue = VkXYColorEXT{ .x = 0,.y = 0 };//Ϊ VkXYColorEXTֵָ����ʾ��������ɫ��ɫ������ chromaticity coordinates��ָ�� x �� y chromaticity coordinate��Chromaticity coordinates�μ� CIE 15:2004
		hdrMetadataEXT.whitePoint = VkXYColorEXT{ .x = 0.3127f,.y = 0.329f };//Ϊ VkXYColorEXTֵָ����ʾ���İ�ɫ��ɫ������ chromaticity coordinates��ָ�� x �� y chromaticity coordinate��Chromaticity coordinates�μ� CIE 15:2004
		hdrMetadataEXT.minLuminance = 0.0f;//Ϊ��ʾ����С�ķ�������ֵ����nitsΪ��λ
		hdrMetadataEXT.maxLuminance = 1.0f;//Ϊ��ʾ�����ķ�������ֵ����nitsΪ��λ
		hdrMetadataEXT.maxContentLightLevel = 1;//Ϊ��ʾ��������������ֵ����nitsΪ��λ
		hdrMetadataEXT.maxFrameAverageLightLevel = 1;//Ϊ��ʾ������֡ƽ������ֵ����nitsΪ��λ


		vkSetHdrMetadataEXT(device,1, &swapchainKHR, &hdrMetadataEXT);

	}


	//Present Barrier  �μ�p3194
	{
		/*
		 VK_NV_present_barrier ��չ��������Ӧ��ʹ�� present barrier ȥͬ�����swapchain�е���ʾ����������Ҫ��Щswapchain�ڴ���swapchain��VkSwapchainCreateInfoKHR�а���һ��presentBarrierEnable��ΪVK_TRUE�� VkSwapchainPresentBarrierCreateInfoNV
		
		
		*/

		//����������ýṹ����Ĭ��presentBarrierEnable ΪVK_FALSE
		VkSwapchainPresentBarrierCreateInfoNV swapchainPresentBarrierCreateInfoNV{};
		swapchainPresentBarrierCreateInfoNV.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_PRESENT_BARRIER_CREATE_INFO_NV;
		swapchainPresentBarrierCreateInfoNV.pNext = nullptr;
		swapchainPresentBarrierCreateInfoNV.presentBarrierEnable = VK_TRUE;//ָ����ʾ��ʾ�Ƿ�ʹ��present barrier
	}

}



NS_TEST_END