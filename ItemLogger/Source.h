#pragma once

struct log_data
{
	unsigned int id;
	char Name[16];
};

class LoggerThread
{
private:
	std::mutex LogMutex;
	bool Quit = false;
public:
	//Main loop to log elements
	void MainLoop();

	//Request the logger to stop
	void Exit() { Quit = true; };

	//Used to lock the mutex and insert el.
	std::mutex & GetMutex() { return LogMutex; };

	//Where ours logs will be stored till dispatch.
	std::queue<log_data> LogQueue;
};

class LoggerInterface
{

private:
	LoggerThread * ThreadClass;

	std::thread thread;

public:

	//This class is a singleton, delete some constructors and copiers.
	LoggerInterface() = delete;
	LoggerInterface(const LoggerInterface&) = delete;

	//Main constructor / destructor
	LoggerInterface(LoggerThread* Logger, const std::function<void()>& func) : ThreadClass(Logger), thread(func) {};
	~LoggerInterface() = default;

	//Request the end of the execution.
	void Exit()
	{
		ThreadClass->Exit();
		if (thread.joinable()) thread.join();
	}

	//adds an element to be logged.
	void LogItem(const log_data & log) const
	{
		//ensure we are thread safe.
		ThreadClass->GetMutex().lock();

		//adds the element to the Logger.
		ThreadClass->LogQueue.emplace(log);

		//Unlocks the mutex 
		ThreadClass->GetMutex().unlock();
	};

};

