#pragma once

#include "../common/TestBase.h"
#include "TestFwd.h"


#include <vector>

NS_TEST_BEGIN


class VKTestBase : public TestBase {
public:
	VKTestBase();
	virtual void run()  = 0;
	virtual ~VKTestBase();
protected:

	//准备Vulkan上下文，供需要的测试类在构造函数体中调用
	void PrepareContex();

	//清理Vulkan上下文，供需要的测试类在析构函数体中调用
	void ClearContex();

	VkInstance instance{ VK_NULL_HANDLE };
	VkPhysicalDevice physicalDevice{ VK_NULL_HANDLE };
	VkDevice device{ VK_NULL_HANDLE };
	VkDebugUtilsMessengerEXT messager{ VK_NULL_HANDLE };

};




NS_TEST_END

