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
	//chapter 35
	void DefferedHostOperationTest();
	//chapter 36
	void PrivateDataTest();
	//chapter 37
	void AccelerationStructureTest();

};
TEST_REGISTER(DefferedHostOperationPrivateDataAndAccelarationStructureTest)



NS_TEST_END

