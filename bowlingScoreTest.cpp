#include "bowlingScore.h"
#include <iostream>

using namespace std;
int main()
{
  int a;
  bowling::Game game(3);
  while(!game.isOver()) {
    cin >> a;
    game.put(a);
  }
  wcout << game << endl;
  return 0;
}
