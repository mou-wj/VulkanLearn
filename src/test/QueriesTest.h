#pragma once

#include "VKTestBase.h"


NS_TEST_BEGIN

MARK_TEST_SEQUENCE(1)
class QueriesTest : public VKTestBase {
public:
	QueriesTest();
	void run() override;
	~QueriesTest();

private:
	void QueryPoolTest();
	void QueryOperationsTest();



};
TEST_REGISTER(QueriesTest)



NS_TEST_END

