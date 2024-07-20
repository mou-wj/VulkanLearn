#pragma once

#include "VKTestBase.h"


NS_TEST_BEGIN

MARK_TEST_SEQUENCE(1)
class SamplerTest : public VKTestBase {
public:
	SamplerTest();
	void run() override;
	~SamplerTest();

private:
	void SamplerCreateTest();
private:


};
TEST_REGISTER(SamplerTest)



NS_TEST_END

