#pragma once

#include "VKTestBase.h"


NS_TEST_BEGIN

MARK_TEST_SEQUENCE(1)
class DispatchingAndDeviceGeneratedCommandsTest : public VKTestBase {
public:
	DispatchingAndDeviceGeneratedCommandsTest();
	void run() override;
	~DispatchingAndDeviceGeneratedCommandsTest();

private:

	void DispatchingCommandsTest();
	void DeviceGeneratedCommandsTest();



};
TEST_REGISTER(DispatchingAndDeviceGeneratedCommandsTest)



NS_TEST_END

