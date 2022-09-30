# Thread-safe-logger

Any bugs or suggestions, feel free to contact me.

My discord : Rovug#1023

Thanks for your attention!

//---------------------------

This is a thread safe logger designed by me. It was used in conjuction with another code to log data to SQL.
This code is made to be implemented in your project, not to be used as DLL, LIB or EXE.

The code is very well commented, but below there is some details about it's usage: 

You need to define the data you are going to log inside this struct:



``` c++
struct log_data
{
	unsigned int id;
	char Name[16];
};

//In your code, create a new log file and add data to it.
log_data log = { counter, "new log added" };

//adds the item to the log queue..
logger.LogItem(log);
```
Inside the function void LoggerThread::MainLoop(), you are going to define what it's going to do with the log, either print to CLI, add to a SQL database or your needs.

