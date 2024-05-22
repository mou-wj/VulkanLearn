#pragma once

#include "../common/TestBase.h"
#include "TestFwd.h"

NS_TEST_BEGIN


class DeviceAndQueueTest : public TestBase {
public:
	DeviceAndQueueTest() = default;
	void run() override;




};
TEST_REGISTER(DeviceAndQueueTest)



NS_TEST_END
