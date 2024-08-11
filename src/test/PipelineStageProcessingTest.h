#pragma once

#include "VKTestBase.h"


NS_TEST_BEGIN

MARK_TEST_SEQUENCE(1)
class PipelineStageProcessingTest : public VKTestBase {
public:
	PipelineStageProcessingTest();
	void run() override;
	~PipelineStageProcessingTest();

private:
	//chapter 22
	void VertexProcessingFixedFunctionTest();
private:


};
TEST_REGISTER(PipelineStageProcessingTest)



NS_TEST_END

