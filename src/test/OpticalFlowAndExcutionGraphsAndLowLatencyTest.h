#pragma once

#include "VKTestBase.h"
#include "TestFwd.h"

NS_TEST_BEGIN

MARK_TEST_SEQUENCE(4)
class OpticalFlowAndExcutionGraphsAndLowLatencyTest final : public  VKTestBase {
public:
	OpticalFlowAndExcutionGraphsAndLowLatencyTest();
	void run() override;
	virtual ~OpticalFlowAndExcutionGraphsAndLowLatencyTest();

private:
	//chater 43
	void OpticalFlowTest();
	//chater 44
	void ExecutionGraphsTest();


};
TEST_REGISTER(OpticalFlowAndExcutionGraphsAndLowLatencyTest)



NS_TEST_END
