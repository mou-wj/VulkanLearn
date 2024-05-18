#include "TestBase.h"

#include <assert.h>
NS_TEST_BEGIN

TestManager* TestManager::m_instance = nullptr;


TestManager* TestManager::Instance()
{
	if (!m_instance)
	{
		m_instance = new TestManager();
	}
	return m_instance;
}

void TestManager::RunTest(const std::string& symbol_TestName)
{
	
	if (!m_tests.contains(symbol_TestName)) {
		assert(false, "Test not found");
	}
	m_tests[symbol_TestName]->run();
}

TestManager::~TestManager()
{	
	for (auto& test : m_tests)
	{
		delete test.second;
	}
}





NS_TEST_END