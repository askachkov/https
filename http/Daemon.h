#ifndef DAEMON_H
#define DAEMON_H

#include <daemon-lite/daemonApp.h>

class Daemon: public IDaemon
{
public:
	Daemon();
	virtual const char * daemonName()const;
	virtual const char * pidFileName() const;
	virtual int loggerID() const;
	virtual int fdLimitMax() const;
	virtual bool loadConfig(const char * cfgFileName);
	virtual bool reloadConfig();
	virtual int run();
	virtual void stop();
	virtual bool isThisStopCommand(const char * cfgFileName);
	virtual bool isThisReloadCommand(const char * cfgFileName);

private:
	int mLoggerId;
};

#endif
