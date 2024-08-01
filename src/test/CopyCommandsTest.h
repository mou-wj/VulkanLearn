#pragma once

#include "VKTestBase.h"


NS_TEST_BEGIN

MARK_TEST_SEQUENCE(1)
class CopyCommandsTest : public VKTestBase {
public:
	CopyCommandsTest();
	void run() override;
	~CopyCommandsTest();

private:

	void CommandsTest();



};
TEST_REGISTER(CopyCommandsTest)



NS_TEST_END

