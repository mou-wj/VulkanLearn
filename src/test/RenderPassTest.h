#pragma once

#include "VKTestBase.h"


NS_TEST_BEGIN

MARK_TEST_SEQUENCE(1)
class RenderPassTest : public VKTestBase {
public:
	RenderPassTest();
	void run() override;
	~RenderPassTest();

private:
	void RenderPassInstanceCommandTest();
	void RenderPassCreateTest();
	void FrameBufferCreateTest();
	void RenderPassCmdTest();

private:

	VkRenderPass renderPass{ VK_NULL_HANDLE };
};
TEST_REGISTER(RenderPassTest)



NS_TEST_END

