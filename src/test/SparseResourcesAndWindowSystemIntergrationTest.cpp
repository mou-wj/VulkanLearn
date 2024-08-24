#include "SparseResourcesAndWindowSystemIntergrationTest.h"
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


		//Physical Device Sparse Properties


	}
}



NS_TEST_END