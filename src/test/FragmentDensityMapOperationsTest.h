#pragma once

#include "VKTestBase.h"


NS_TEST_BEGIN

MARK_TEST_SEQUENCE(1)
class FragmentDensityMapOperationsTest : public VKTestBase {
public:
	FragmentDensityMapOperationsTest();
	void run() override;
	~FragmentDensityMapOperationsTest();

private:

	void OperationsTest();



};
TEST_REGISTER(FragmentDensityMapOperationsTest)



NS_TEST_END

