#pragma once

#include "VKTestBase.h"


NS_TEST_BEGIN

MARK_TEST_SEQUENCE(1)
class InstanceTest : public VKTestBase {
public:
	InstanceTest();
	void run() override;




};
TEST_REGISTER(InstanceTest)



NS_TEST_END

