#pragma once

#include "VKTestBase.h"


NS_TEST_BEGIN

MARK_TEST_SEQUENCE(1)
class ExtendingVulkanAndFeatuesTest : public VKTestBase {
public:
	ExtendingVulkanAndFeatuesTest();
	void run() override;
	~ExtendingVulkanAndFeatuesTest();

private:

	//chater 46
	void ExtendingVulkanTest();
	//chater 47
	void FeaturesTest();


};
TEST_REGISTER(ExtendingVulkanAndFeatuesTest)



NS_TEST_END
