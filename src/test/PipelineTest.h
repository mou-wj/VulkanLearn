#pragma once

#include "VKTestBase.h"


NS_TEST_BEGIN

MARK_TEST_SEQUENCE(1)
class PipelineTest : public VKTestBase {
public:
	PipelineTest();
	void run() override;
	~PipelineTest();

private:


private:

};
TEST_REGISTER(PipelineTest)



NS_TEST_END

