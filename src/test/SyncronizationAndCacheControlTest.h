#pragma once

#include "VKTestBase.h"
#include "TestFwd.h"

NS_TEST_BEGIN

MARK_TEST_SEQUENCE(4)
class SyncronizationAndCacheControlTest final : public  VKTestBase {
public:
	SyncronizationAndCacheControlTest();
	void run() override;
	virtual ~SyncronizationAndCacheControlTest();

private:
	void FenceTest();
	void SemaphoreTest();
	void EventTest();
	void MemoryBarrierTest();
	void BufferMemoryBarrierTest();
	void ImageMemoryBarrierTest();
};
TEST_REGISTER(SyncronizationAndCacheControlTest)



NS_TEST_END
