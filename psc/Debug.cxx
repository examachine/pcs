/*
**
** Implementation file for Debug module
**
**
**
** exa
**
*/

#include "Debug.hxx"

int check_point_ctr = 0;

void check_point()
{
  cout << "check point: " << check_point_ctr++ << endl;
}
