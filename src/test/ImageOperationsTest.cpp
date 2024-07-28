#include "ImageOperationsTest.h"
NS_TEST_BEGIN

ImageOperationsTest::ImageOperationsTest()
{
}

void ImageOperationsTest::run()
{
}

ImageOperationsTest::~ImageOperationsTest()
{
}

void ImageOperationsTest::OperationsTest()
{
	//Image Operations Overview 概述
	{
		/*
		Vulkan Image Operations 是在SPIR-V 中的对image的操作，,例如由OpTypeImage, OpTypeSampledImage 等表示的操作，详情见p1473
		*/

		//Texel Coordinate Systems 参见p1474 - p1478


	}


	// Conversion Formulas 转换规则
	{
		// RGB to Shared Exponent Conversion
		{
			//(red,green,blue) -->  (redshared, greenshared,blueshared, expshared) 转换详情参见p1478-p1479
		}

		//  Shared Exponent to RGB
		{
			//(redshared, greenshared,blueshared, expshared) --> (red,green,blue)  转换详情参见p1479-p1480
		}
	}


	//Texel Input Operations
	{
		//Texel input instructions 指的是SPIR-V中读取image的指令，Texel input operations 为一系列处理texel input instruction 时作用在state, coordinates, 以 texel values 上的步骤
		{
			/*
			步骤列表,步骤顺序按照表中列举的顺序:
			-> Validation operations
				->> Instruction/Sampler/Image validation
				->> Coordinate validation
				->> Sparse validation
				->> Layout validation
			-> Format conversion
			-> Texel replacement
			-> Depth comparison
			-> Conversion to RGBA
			-> Component swizzle
			-> Chroma reconstruction
			-> Y′CBCR conversion

			如果Chroma reconstruction 隐含，则转而执行 Texel Filtering
			 block matching 以及 weight image sampling 中的操作需要在Conversion to RGBA 以及 Component swizzle前执行.
			*/


		}


		//Texel Input Validation Operations 参见p1481
		{
			//Texel input validation operations 检查 instruction/image/sampler state 后者 coordinates, 在特定情况下替换texel value 或使其未定义

			//Instruction/Sampler/Image View Validation  参见p1481 - p1483

			//Integer Texel Coordinate Validation   验证image的大小，layer数，采样数，基于integer texel coordinates  参见p1483 - p1485

			//Sparse Validation

			//Layout Validation
		}


		//Format Conversion   从VkFormat转换到包含浮点，符号整数，无符号整数分量的vec值   参见p1485


		//Texel Replacement 参见p1486 - p1487

		//Depth Compare Operation 对 OpImage*Dref* 指令，比较结果成功为1，值替换为depth的值，失败为0，  参见p1487 - p1488

		//Conversion to RGBA  参见p1488


		//Component Swizzle  参见p1489

		//Sparse Residency 参见p1489

		//Chroma Reconstruction  这一小节内容较多  >>>>>   详情参见p1490-p1496
		{}

		//Sampler Y′CBCR Conversion
		{
			/*
			主要操作:
			> Sampler Y′CBCR Range Expansion
			> Sampler Y′CBCR Model Conversion
			*/
		}
	}


	//Texel Output Operations  参见p1499-p1500
	{
		//Texel output instructions 指的是SPIR-V中写入image的指令，Texel output operations 为一系列处理texel output instruction 时作用在state, coordinates, 以 texel values 上的步骤
		{
			/*
			步骤列表,步骤顺序按照表中列举的顺序:
			-> Validation operations
				->> Format validation
				->> Type validation
				->> Coordinate validation
				->> Sparse validation
			-> Texel output format conversion
			*/
		}


		//Texel Output Validation Operations 
		{
			//Texel output validation operations 检查 instruction/image state 或者 coordinates, 且在特定情况下的写不起作用

			//Texel Format Validation

			//Texel Type Validation
		}

		// Integer Texel Coordinate Validation

		// Sparse Texel Operation

		// Texel Output Format Conversion  从VkFormat转换到包含浮点，符号整数，无符号整数分量的vec值  参见p1500
	}


	//Normalized Texel Coordinate Operations *** 详情参见p1500
	{
		//Projection Operation  

		//Derivative Image Operations
		{
			//Derivative 用于LOD选择
		}

		//Cube Map Face Selection and Transformations

		// Cube Map Face Selection

		//Cube Map Coordinate Transformation

		// Cube Map Derivative Transformation

		// Scale Factor Operation, LOD Operation and Image Level(s) Selection  参见p1053- p1507

		// (s,t,r,q,a) to (u,v,w,a) Transformation
	}


	//Unnormalized Texel Coordinate Operations  参见p1508
	{
		// (u,v,w,a) to (i,j,k,l,n) Transformation and Array Layer Selection
	}


	//Integer Texel Coordinate Operations  参见p1510


	//Image Sample Operations 见p1510
	{
		// Wrapping Operation 参见p1510

		//Texel Gathering  返回四个像素值，参见p1511

		// Texel Filtering  参见p1512
		{
			//Texel Nearest Filtering

			//Texel Linear Filtering 3D 8个，2D 4个，1D 2个采样点的加权操作，平均，最大，最小等

			//Texel Cubic Filtering 3D 64个，2D 16个，1D 4个采样点的加权操作，平均，最大，最小等，参见p1512

			//Texel Range Clamp

			//Texel Mipmap Filtering

			//Texel Anisotropic Filtering
		}


	}

	//Texel Footprint Evaluation 参见p1516 - p1519
	{
		// OpImageSampleFootprintNV 从单个mipmap level中计算一组texel的值用于filter，以Granularity控制采样点的数量，Corse用于在两个mipmap level中选择 参见p1516-p1517
	}


	//Weight Image Sampling p1519
	{
		// OpImageWeightedSampleQCOM 指明一个包含两个纹理的采样，wight指定一个采样权重image，该image定义滤波核，大小为(0,0) 到 (filterSize.x-1, filterSize.y-1)，numPhases 用于描述提供给sub-pixel filter的phase数

		// Weight Image Layout
		{
			//2D Non-Separable Weight Filters

			//1D Separable Weight Filters >>  2D filter的两个1D filter的表示
		}

		//Weight Sampling Phases p1521

		//Weight Sampler Parameters


		//Weight Sampling Operation 简单讲从采样纹理中采样，从权重纹理中获取权重，得到的值加权操作，平均，最小，最大值。  参见p1522-p1524
	}

	// Block Matching p1524
	{
		//opImageBlockMatchSAD and opImageBlockMatchSSD 指明目标image和引用image的相同大小的texel块的比较

		//Block Matching Sampler Parameters

		// Block Matching Operation  简单讲将目标image和引用image的差异值做操作，累加，最小，最大  参见p1525
	
		//Block Matching Window Operation  opImageBlockMatchWindowSAD 和 opImageBlockMatchWindowSSD，window中重复Block Matching Operation 参见p1526

		//Block Matching Gather Operation opImageBlockMatchGatherSAD 和 opImageBlockMatchGatherSSD，重复Block Matching Operation4次， 参见p1527
	}

	//Box Filter Sampling
	{
		// OpImageBoxFilterQCOM 指明一个区域的texel的加权平均    参见p1528

		//Box Filter Sampler Parameters 

		//Box Filter Operation  简单讲采样点附近完全覆盖boxSize的texel区域中每个texel进行加权操作,平均，最大，最小，权重为每个texel的范围在boxSize的比例  参见p1529
	}


	//Image Operation Steps  总结本届的Image Operations  参见p1531


	//Image Query Instructions  参见p1531
	{
		//Image Property Queries   >> OpImageQuerySize, OpImageQuerySizeLod, OpImageQueryLevels, 以及 OpImageQuerySamples

		//Lod Query
	}
}



NS_TEST_END