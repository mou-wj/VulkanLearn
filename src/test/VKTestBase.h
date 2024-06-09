#pragma once

#include "../common/TestBase.h"
#include "TestFwd.h"


#include <vector>

#define THROW_ERROR throw std::runtime_error("error");
#define MARK_TEST_SEQUENCE(x) 

#define VK_API_WRAPPER(VK_API) {auto res = VK_API;if(res != VK_SUCCESS) THROW_ERROR}
#define VK_RESULT_CHECK_CALL(VK_API) VK_API_WRAPPER(VK_API)

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

	//准备Vulkan上下文，供需要的测试类在构造函数体中调用
	void PrepareContex();

	//清理Vulkan上下文，供需要的测试类在析构函数体中调用
	void ClearContex();

	VkInstance instance{ VK_NULL_HANDLE };
	VkPhysicalDevice physicalDevice{ VK_NULL_HANDLE };
	VkDevice device{ VK_NULL_HANDLE };
	VkDebugUtilsMessengerEXT messager{ VK_NULL_HANDLE };
	std::vector<VkQueue> queues;
	int queueFamilyIndex{ -1 };
};

inline void* ImportVKInstanceFunction(VkInstance instance,const char* funcName) {
	PFN_vkGetDeviceProcAddr pfnGetInstanceProcAddr = (PFN_vkGetDeviceProcAddr)vkGetInstanceProcAddr(instance, "vkGetDeviceProcAddr");
	return pfnGetInstanceProcAddr;
}
inline void* ImportVKDeviceFunction(VkDevice device, const char* funcName) {
	PFN_vkGetDeviceProcAddr pfnGetDeviceProcAddr = (PFN_vkGetDeviceProcAddr)vkGetDeviceProcAddr(device, "vkGetDeviceProcAddr");
	return pfnGetDeviceProcAddr;
}
#define VK_INSTANCE_FUNCTION_GET_AND_CALL(Instance,FuncName,...) ((PFN_##FuncName)ImportVKInstanceFunction(instance,#FuncName))(__VA_ARGS__);
#define VK_DEVICE_FUNCTION_GET_AND_CALL(Device,FuncName,...) ((PFN_##FuncName)ImportVKDeviceFunction(Device,#FuncName))(__VA_ARGS__);
NS_TEST_END

