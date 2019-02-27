#ifndef TASKS_H
#define TASKS_H

#include "utils.h"

typedef void F(SOCKET);

void default_Task(F fnc, uint16_t port);

#endif // TASKS_H
