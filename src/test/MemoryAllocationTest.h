#pragma once

#include "VKTestBase.h"


NS_TEST_BEGIN

MARK_TEST_SEQUENCE(1)
class MemoryAllocationTest : public VKTestBase {
public:
	MemoryAllocationTest();
	void run() override;
	~MemoryAllocationTest();


private:

};
TEST_REGISTER(MemoryAllocationTest)



NS_TEST_END
