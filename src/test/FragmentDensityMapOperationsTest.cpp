#include "FragmentDensityMapOperationsTest.h"
NS_TEST_BEGIN

FragmentDensityMapOperationsTest::FragmentDensityMapOperationsTest()
{
}

void FragmentDensityMapOperationsTest::run()
{
}

FragmentDensityMapOperationsTest::~FragmentDensityMapOperationsTest()
{
}

void FragmentDensityMapOperationsTest::OperationsTest()
{
	// Fragment Density Map Operations Overview
	{
		/*
		当在具有fragment density map附件的render pass中生成片段时，其区域由片段所占据的本地帧缓冲区区域的属性决定。帧缓冲区被划分为这些局部区域组成的均匀网格,这些局部区域就为density map
		*/
		/*fragment 区域属性由density map的一下操作推导出来的
		-> Fetch density value
		    ->> Component swizzle
		    ->> Component mapping
		-> Fragment area conversion
		    ->> Fragment area filter
		    ->> Fragment area clamp
		*/
	}

	//Fetch Density Value  参见p1533
	{
		//Component Swizzle

		//Component Mapping
	}



	//Fragment Area Conversion  参见p1534
	{
		//Fragment Area Filter

		// Fragment Area Clamp
	}

}


NS_TEST_END