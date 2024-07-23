#pragma once

#include "VKTestBase.h"


NS_TEST_BEGIN

MARK_TEST_SEQUENCE(1)
class ResourceDescriptorsTest : public VKTestBase {
public:
	ResourceDescriptorsTest();
	void run() override;
	~ResourceDescriptorsTest();

private:
	void DescriptorTypeTest();
	void DescriptorSetsTest();
	void PhysicalStorageBufferAccessTest();

private:


};
TEST_REGISTER(ResourceDescriptorsTest)



NS_TEST_END

