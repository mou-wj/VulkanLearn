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
	void FixedFunctionVertexProcessingTest();
	//chapter 23
	void TessellationTest();
	//chater 24
	void GeometryShadingTest();
	//chapter 25
	void MeshShaingTest();
	//chapter 26
	void ClusterCullingShadingTest();
	//chapter 27
	void FixedFunctionVertexPostProcessingTest();
	//chapter 28
	void RasterizationTest();
private:


};
TEST_REGISTER(PipelineStageProcessingTest)



NS_TEST_END

