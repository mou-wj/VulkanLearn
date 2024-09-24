#pragma once

#include "VKTestBase.h"


NS_TEST_BEGIN

MARK_TEST_SEQUENCE(1)
class LimitsAndFormatsTest : public VKTestBase {
public:
	LimitsAndFormatsTest();
	void run() override;
	~LimitsAndFormatsTest();


private:
	void LimitsTest();
	void FormatsTest();
};
TEST_REGISTER(LimitsAndFormatsTest)



NS_TEST_END
