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


		//Physical Device Sparse Properties


	}
}



NS_TEST_END