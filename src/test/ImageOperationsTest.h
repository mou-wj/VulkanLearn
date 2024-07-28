#pragma once

#include "VKTestBase.h"


NS_TEST_BEGIN

MARK_TEST_SEQUENCE(1)
class ImageOperationsTest : public VKTestBase {
public:
	ImageOperationsTest();
	void run() override;
	~ImageOperationsTest();

private:

	void OperationsTest();



};
TEST_REGISTER(ImageOperationsTest)



NS_TEST_END

