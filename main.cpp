#include "AloneBowling.h"
#ifdef WIN32
#include <windows.h>
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
#else
int main()
#endif
{
  AloneBowling game;
  game.run();
  return 0;
}
