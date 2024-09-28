#pragma once

#include "VKTestBase.h"


NS_TEST_BEGIN

MARK_TEST_SEQUENCE(1)
class AdditionalCapacitiesAndDebuggingTest : public VKTestBase {
public:
	AdditionalCapacitiesAndDebuggingTest();
	void run() override;
	~AdditionalCapacitiesAndDebuggingTest();


private:
	void AdditionalCapacitiesTest();
	void DebuggingTest();
};
TEST_REGISTER(AdditionalCapacitiesAndDebuggingTest)



NS_TEST_END
