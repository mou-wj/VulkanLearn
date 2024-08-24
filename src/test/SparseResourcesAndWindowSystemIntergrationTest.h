#pragma once

#include "VKTestBase.h"
#include "TestFwd.h"

NS_TEST_BEGIN

MARK_TEST_SEQUENCE(4)
class SparseResourcesAndWindowSystemIntergrationTest final : public  VKTestBase {
public:
	SparseResourcesAndWindowSystemIntergrationTest();
	void run() override;
	virtual ~SparseResourcesAndWindowSystemIntergrationTest();

private:
	void SparseResourcesTest();
};
TEST_REGISTER(SparseResourcesAndWindowSystemIntergrationTest)



NS_TEST_END
