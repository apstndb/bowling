#include "bowlingScore.h"
#include <iostream>

using namespace std;
int main()
{
  int a;
  bowling::Game game;
  while(!game.isOver()) {
    cin >> a;
    game.put(a);
  }
  cout << game << endl;
  return 0;
}
