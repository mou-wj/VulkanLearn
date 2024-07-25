#pragma once

#include "VKTestBase.h"


NS_TEST_BEGIN

MARK_TEST_SEQUENCE(1)
class ShadersInterfaceTest : public VKTestBase {
public:
	ShadersInterfaceTest();
	void run() override;
	~ShadersInterfaceTest();

private:
	void InterfaceTest();
private:


};
TEST_REGISTER(ShadersInterfaceTest)



NS_TEST_END

