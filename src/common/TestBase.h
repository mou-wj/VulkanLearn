#pragma once
#include "Global.h"


#include <map>
#include <string>
NS_TEST_BEGIN

class TestBase {
public:
	TestBase() = default;
	virtual void run() = 0;

private:


};

class TestManager {
public:
	static TestManager* Instance();
	void RunTest(const std::string& symbol_TestName);

	template<class BaseClass>
	class TestRegister {
	public:
		TestRegister(const std::string& symbol_TestName) {
			if (!Instance()->m_tests.contains(symbol_TestName))
			{
				Instance()->m_tests[symbol_TestName] = new BaseClass();
			}

		}

	};
	~TestManager();
private:
	TestManager() {}
	TestManager(const TestManager&) = delete;
	TestManager& operator=(const TestManager&) = delete;
	static TestManager* m_instance;
	std::map<std::string, TestBase*> m_tests;
};
#define TEST_REGISTER(TestName) static TestManager::TestRegister<TestName> testRegister(#TestName)
#define TEST_RUN(TestName) TestManager::Instance()->RunTest(#TestName)


NS_TEST_END