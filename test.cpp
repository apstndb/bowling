#include <irrlicht/irrlicht.h>
#include <iostream>
using namespace irr;
using namespace core;
using namespace std;
int main()
{
  quaternion q;//(3.14, 3.14, 3.14);
  q.fromAngleAxis(3.14, vector3df(0, 0, 1));
  cout << q.X << ' ' << q.Y << ' ' << q.Z << endl;

  return 0;
}
