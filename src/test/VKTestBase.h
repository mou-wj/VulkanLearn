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

	//׼��Vulkan�����ģ�����Ҫ�Ĳ������ڹ��캯�����е���
	void PrepareContex();

	//����Vulkan�����ģ�����Ҫ�Ĳ������������������е���
	void ClearContex();

	VkInstance instance{ VK_NULL_HANDLE };
	VkPhysicalDevice physicalDevice{ VK_NULL_HANDLE };
	VkDevice device{ VK_NULL_HANDLE };
	VkDebugUtilsMessengerEXT messager{ VK_NULL_HANDLE };

};




NS_TEST_END

