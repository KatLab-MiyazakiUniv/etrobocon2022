#include "app.h"
#include "EtRobocon2022.h"

void main_task(intptr_t unused)
{
  EtRobocon2022::start();
  ext_tsk();
}
// end::main_task_2[]