#pragma once

#include "VKTestBase.h"


NS_TEST_BEGIN

MARK_TEST_SEQUENCE(1)
class DrawingCommandsTest : public VKTestBase {
public:
	DrawingCommandsTest();
	void run() override;
	~DrawingCommandsTest();

private:
	void PrimitiveTest();
	void ConditinalRenderingTest();

};
TEST_REGISTER(DrawingCommandsTest)



NS_TEST_END

