#include <iostream>
#include "Engine.h"

int main(int argv, char **args)
{
  Engine *engine = new Engine();

  if (engine->Setup() == false)
  {
    engine->Quit();
    return 0;
  }

  int status = engine->Run();
  engine->Quit();

  return status;
}