#pragma once

#include "../common/TestBase.h"
#include "TestFwd.h"


#include <vector>

#define THROW_ERROR throw std::runtime_error("error");
#define MARK_TEST_SEQUENCE(x) 

#define VK_API_WRAPPER(VK_API) auto res = VK_API;if(res != VK_SUCCESS) THROW_ERROR

#define VK_STRCUTURE_LINK(NodeHead,NodeToInsert) {\
const void* tmp = NodeHead.pNext;\
NodeToInsert.pNext = tmp;\
NodeHead.pNext = &NodeToInsert;\
}

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
	std::vector<VkQueue> queues;
	int queueFamilyIndex{ -1 };
};




NS_TEST_END

