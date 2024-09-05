#pragma once

#include "VKTestBase.h"
#include "TestFwd.h"

NS_TEST_BEGIN

MARK_TEST_SEQUENCE(4)
class MemoryDecompressionAndVideoCodingTest final : public  VKTestBase {
public:
	MemoryDecompressionAndVideoCodingTest();
	void run() override;
	virtual ~MemoryDecompressionAndVideoCodingTest();

private:
	//chater 41
	void MemoryDecompressionTest();

};
TEST_REGISTER(MemoryDecompressionAndVideoCodingTest)



NS_TEST_END
