#include "Daemon.h"
#include <daemon-lite/logger.h>
#include <chrono>
#include <thread>

#include "tasks.h"
#include <string.h>
#include <string.h>
#include <iostream>

Daemon::Daemon()
{
	mLoggerId = createNewLogger(daemonName());
}

const char * Daemon::daemonName()const
{
    return "web-s";
}

const char * Daemon::pidFileName() const
{
    return "/var/run/web-s.pid";
}

int Daemon::loggerID() const 
{
	return mLoggerId;
}

int Daemon::fdLimitMax() const 
{
    return 0xFFFF;
}

bool Daemon::isThisStopCommand(const char * cfgFileName) 
{
    return strcmp(cfgFileName, "stop") == 0;
}

bool Daemon::isThisReloadCommand(const char * cfgFileName) 
{
    return strcmp(cfgFileName, "reload") == 0;
}

bool Daemon::loadConfig(const char * cfgFileName) 
{
	return true;
}

bool Daemon::reloadConfig() 
{
	return true;
}

int Daemon::run() 
{
    std::thread t1(default_Task, processClient, PORT_NO);
    std::thread t2(default_Task, processClientSSL, PORT_SSL_NO);
    t1.join();
    t2.join();
	return IDaemon::EXIT;
}

void Daemon::stop() 
{
    std::terminate();
}
