#pragma once

#include "VKTestBase.h"


NS_TEST_BEGIN

MARK_TEST_SEQUENCE(1)
class ShadersTest : public VKTestBase {
public:
	ShadersTest();
	void run() override;
	~ShadersTest();

private:
	void ShaderCreateTest();

private:

	
};
TEST_REGISTER(ShadersTest)



NS_TEST_END

