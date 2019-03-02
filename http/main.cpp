#include <iostream>
#include <daemon-lite/daemonApp.h>
#include "Daemon.h"

int main(int argc, char * argv[]) 
{
	Daemon d;
	return DaemonApp::instance(&d)->exec(argc, argv);
}