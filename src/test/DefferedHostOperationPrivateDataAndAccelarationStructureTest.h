#pragma once

#include "VKTestBase.h"


NS_TEST_BEGIN

MARK_TEST_SEQUENCE(1)
class DefferedHostOperationPrivateDataAndAccelarationStructureTest : public VKTestBase {
public:
	DefferedHostOperationPrivateDataAndAccelarationStructureTest();
	void run() override;
	~DefferedHostOperationPrivateDataAndAccelarationStructureTest();

private:
	void DefferedHostOperationTest();
	void PrivateDataTest();
	void AccelerationStructureTest();

};
TEST_REGISTER(DefferedHostOperationPrivateDataAndAccelarationStructureTest)



NS_TEST_END

