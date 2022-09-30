
#include <thread>
#include <mutex>

//container used to store elements
#include <queue>
//std::function, used in the constructor.
#include <functional>
//sleep
#include <chrono> 
//IO
#include <iostream>

#include "Logger.h"

void LoggerThread::MainLoop()
{
	//Loop until we exit.
	while (Quit == false)
	{
		//While we have logs, log them.
		while(!LogQueue.empty())
		{
			//Request the lock.
			std::lock_guard Mutex(LogMutex);

			//gets the first element from the queue.
			const log_data & Log = LogQueue.front();
			
			std::cout << "Log id: " << Log.id << " Player Name: " << Log.Name << '\n';

			//done with the element ? remove it from the queue.
			LogQueue.pop();

		}
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}

}

int main()
{
	// Both LoggerThread and LoggerInterface need to live through the entire life of the program.
	LoggerThread LoggerThread;

	//Creates the main interface class
	const LoggerInterface logger(&LoggerThread, [&]{LoggerThread.MainLoop(); });

	unsigned int counter = 0;

	while(true)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(100)); 

		counter++;

		log_data log = { counter, "new log added" };

		logger.LogItem(log);
	}

	LoggerThread.Exit();

}

