#include "ShadersInterfaceTest.h"
NS_TEST_BEGIN

/*
概述:
当pipeline创建了后，其指定的shaders将会隐式链接到一系列的接口:
>  Shader Input and Output Interface
>  Vertex Input Interface
>  Fragment Output Interface
>  Fragment Tile Image Interface
>  Fragment Input Attachment Interface
>  Ray Tracing Pipeline Interface
>  Shader Resource Interface
>  Geometry Shader Passthrough


*/


ShadersInterfaceTest::ShadersInterfaceTest()
{
}

void ShadersInterfaceTest::run()
{
}

ShadersInterfaceTest::~ShadersInterfaceTest()
{
}

void ShadersInterfaceTest::InterfaceTest()
{
	// Shader Input and Output Interfaces
	{
		//这种interface由一个shader，一个匹配到下一个shader 输入的输出以及一个匹配上一个shader stage的输出的输入构成
		//这种interface的变量作为OpEntryPoint 指令操作符列举出来，以 Input 或者 Output storage classes进行声明,这样的接口只存在于两个连续的shader stage之间
		//这种interface的变量分配built-in 变量以及 user-defined变量


		//Built-in Interface Block   参见p1395

		//User-defined Variable Interface   参见p1395

		// Interface Matching 参见p1396

	}







}


NS_TEST_END