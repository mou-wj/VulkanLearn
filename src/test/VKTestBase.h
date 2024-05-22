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
	//׼��Vulkan�����ģ�����Ҫ�Ĳ������ڹ��캯�����е���
	void PrepareContex();

	//����Vulkan�����ģ�����Ҫ�Ĳ������������������е���
	void ClearContex();


	

};
TEST_REGISTER(InstanceTest)



NS_TEST_END

