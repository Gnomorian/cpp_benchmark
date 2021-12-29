#include <iostream>
#include <string>
#include "common.h"
#include <BenchmarkRunner.h>
#include <BenchmarkTest.h>
#include <chrono>
#include <Logger.h>
#include <thread>

class SleepTestExample : public wiwyum::benchmark::BenchmarkTest
{
	const std::chrono::milliseconds SleepFor;
public:
	SleepTestExample(decltype(SleepFor) sleepFor, wiwyum::Logger* logger)
		: SleepFor{ sleepFor }
	{
		setLogger(*logger);
	}

	// Inherited via BenchmarkTest
	virtual void execute() override
	{
		logger.get().debugArgs(L"Sleeping for ", SleepFor);
		std::this_thread::sleep_for(SleepFor);
	}
};

void printResults(const auto& map)
{
	for (const auto& pair : map)
	{
		std::wcout << "TestId: " << pair.first << std::endl;
		std::wcout << L"\tMin: " << pair.second->min() << std::endl
			<< L"\tMax: " << pair.second->max() << std::endl
			<< L"\tAverage: " << pair.second->average() << std::endl;
	}
}

int wmain(int argc, wchar_t* args[])
{
	auto logger{ wiwyum::makeLogger() };
	SleepTestExample quickerTest{ std::chrono::milliseconds{5}, logger.get() };
	SleepTestExample slowerTest{ std::chrono::milliseconds{10}, logger.get() };
	auto benchmarkResults{ 
		wiwyum::benchmark::makeBenchmarkRunner(10, *logger.get())
			->addTest(quickerTest)
			.addTest(slowerTest).run()
	};
	printResults(benchmarkResults);
}