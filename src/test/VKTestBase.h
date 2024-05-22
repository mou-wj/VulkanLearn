#pragma once

#include "../common/TestBase.h"
#include "TestFwd.h"

NS_TEST_BEGIN


class VKTestBase : public TestBase {
public:
	VKTestBase();
	virtual void run()  = 0;
	virtual ~VKTestBase();
protected:
	VkInstance instance{ VK_NULL_HANDLE };
	//准备Vulkan上下文，供需要的测试类在构造函数体中调用
	void PrepareContex();

	//清理Vulkan上下文，供需要的测试类在析构函数体中调用
	void ClearContex();


	

};
TEST_REGISTER(InstanceTest)



NS_TEST_END

