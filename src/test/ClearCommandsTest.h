#pragma once

#include "VKTestBase.h"


NS_TEST_BEGIN

MARK_TEST_SEQUENCE(1)
class ClearCommandsTest : public VKTestBase {
public:
	ClearCommandsTest();
	void run() override;
	~ClearCommandsTest();

private:
	
	void CommandsTest();



};
TEST_REGISTER(ClearCommandsTest)



NS_TEST_END

