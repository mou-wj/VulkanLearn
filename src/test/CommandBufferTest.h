#pragma once
#include "VKTestBase.h"

NS_TEST_BEGIN

MARK_TEST_SEQUENCE(3)
class CommandBufferTest : public VKTestBase {
public:
	CommandBufferTest();
	void run() override;
	virtual ~CommandBufferTest();


};
TEST_REGISTER(CommandBufferTest)


NS_TEST_END

