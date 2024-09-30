#pragma once

#include "VKTestBase.h"


NS_TEST_BEGIN

MARK_TEST_SEQUENCE(1)
class Appendix_A_2_J_Test : public VKTestBase {
public:
	Appendix_A_2_J_Test();
	void run() override;
	~Appendix_A_2_J_Test();

private:
	void Appendix_A_Test();//Vulkan Environment for SPIR-V


};
TEST_REGISTER(Appendix_A_2_J_Test)



NS_TEST_END

