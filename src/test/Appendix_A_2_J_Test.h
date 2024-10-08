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
	void Appendix_B_Test();//Memory Model
	void Appendix_C_Test();//Compressed Image Formats
	void Appendix_D_Test();//Core Revisions (Informative)
	void Appendix_E_Test();//Layers & Extensions (Informative)
	void Appendix_F_Test();//Vulkan Roadmap Milestones
	void Appendix_G_Test();//API Boilerplate
	void Appendix_H_Test();//Invariance
	void Appendix_I_Test();//Lexicon
	void Appendix_J_Test();//Credits (Informative)
};
TEST_REGISTER(Appendix_A_2_J_Test)



NS_TEST_END

