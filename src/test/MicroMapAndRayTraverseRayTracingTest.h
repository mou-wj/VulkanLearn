#pragma once

#include "VKTestBase.h"
#include "TestFwd.h"

NS_TEST_BEGIN

MARK_TEST_SEQUENCE(4)
class MicromapAndRayTraverseRayTracingTest final : public  VKTestBase {
public:
	MicromapAndRayTraverseRayTracingTest();
	void run() override;
	virtual ~MicromapAndRayTraverseRayTracingTest();

private:
	//chapter 38
	void MicromapTest();
	//chapter 39
	void RayTraverseTest();
	//chapter 40
	void RayTracingTest();
};
TEST_REGISTER(SparseResourcesAndWindowSystemIntergrationTest)



NS_TEST_END
