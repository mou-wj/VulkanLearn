#pragma once

#include "VKTestBase.h"


NS_TEST_BEGIN

MARK_TEST_SEQUENCE(1)
class ResourceCreationTest : public VKTestBase {
public:
	ResourceCreationTest();
	void run() override;
	~ResourceCreationTest();

private:

	void BufferCreateTest();
	void BufferViewCreateTest();
	void ImageCreateTest();
	void ImageViewCreateTest();
	void AccelerationStructureCreateTest();
	void MicroMapsCreateTest();

};
TEST_REGISTER(ResourceCreationTest)



NS_TEST_END

