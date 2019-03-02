#ifndef TASKS_H
#define TASKS_H

#include "utils.h"

typedef void F(SOCKET, int);

void default_Task(F fnc, uint16_t port, int logID);

#endif // TASKS_H
