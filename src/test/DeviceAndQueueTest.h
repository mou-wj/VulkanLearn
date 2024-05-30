#pragma once

#include "VKTestBase.h"
#include "TestFwd.h"

NS_TEST_BEGIN

MARK_TEST_SEQUENCE(2)
class DeviceAndQueueTest final: public  VKTestBase{
public:
	DeviceAndQueueTest();
	void run() override;
	virtual ~DeviceAndQueueTest();	



};
TEST_REGISTER(DeviceAndQueueTest)



NS_TEST_END
