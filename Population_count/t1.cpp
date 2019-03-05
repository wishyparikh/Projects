
#include "GridWorld.h"
#include <string>
#include <iostream>
#include <sstream>
#include <vector>

using std::cout;
using std::cin;
using std::string;



bool t1(int n) {
  GridWorld *gw = new GridWorld(5, 5);
  int i, id;
  vector<int> ref;
  vector<int> *m;

  for(i=0; i<n; i++) {
    gw->birth(0, 0, id);
    if(id != i) {
      std::cout << "FAILURE type-1:  id mismatch on birth\n";
      return false;
    }
    ref.push_back(i);
  }

  m = gw->members(0, 0);
  if(*m != ref) {
    std::cout << "FAILURE type-2:  members wrong?\n";
    return false;
  }

  ref.clear();

  for(i=n/2; i<n; i++) {
    if(!gw->move(i, 1, 1) ) {
      std::cout << "FAILURE type-3:  attempted move failed?\n";
      return false;
    }
    ref.push_back(i);
  }
  m = gw->members(1, 1);
  if(*m != ref) {
    std::cout << "FAILURE type-4:  members wrong?\n";
    return false;
  }

  if(gw->population() != n) {
    std::cout << "FAILURE type-5:  world pop wrong?\n";
    std::cout << "  expected:  " << n << "\n";
    std::cout << "  reported:  " << gw->population() << "\n";
    return false;
  }
  if(gw->population(1, 1) != n-(n/2)) {
    std::cout << "FAILURE type-6:  (1,1) pop wrong?\n";
    std::cout << "  expected:  " << n-(n/2) << "\n";
    std::cout << "  reported:  " << gw->population(1,1) << "\n";
    return false;
  }
  if(gw->population(0, 0) != (n/2)) {
    std::cout << "FAILURE type-7:  (0,0) pop wrong?\n";
    std::cout << "  expected:  " << (n/2) << "\n";
    std::cout << "  reported:  " << gw->population(0,0) << "\n";
    return false;
  }
  int r, c;
  r=-1; c=-1;
  for(i=0; i<n/2; i++) {
    if(!gw->whereis(i, r, c)) {
      std::cout << "FAILURE type-8:  whereis failed?\n";
      return false;
    }
    if(r != 0 || c != 0) {
      std::cout << "FAILURE type-9:  whereis " << i << " wrong?\n";
      std::cout << "  expected:  (0, 0)\n";
      std::cout << "  reported:  (" << r << ", " << c << ")\n";
      return false;
    }
  }
  for(i=n/2; i<n; i++) {
    if(!gw->whereis(i, r, c)) {
      std::cout << "FAILURE type-10:  whereis failed?\n";
      return false;
    }
    if(r != 1 || c != 1) {
      std::cout << "FAILURE type-11:  whereis " << i << " wrong?\n";
      std::cout << "  expected:  (1, 1)\n";
      std::cout << "  reported:  (" << r << ", " << c << ")\n";
      return false;
    }
  }
  delete m;
  delete gw;
  return true;
}




/*
 * test case operates on a 5x5 grid.
 *
 * Optional cmd-line arg is "n" which is used to determine
 *   number of operations (births, etc.) performed.
 *
 * This test case focuses on birth, move and whereis
 */
int main(int argc, char *argv[]){
  int n=100;

  if(argc==2) {
    n = atoi(argv[1]);
  }

  cout << "Functional test t1 with n=" << n << "\n\n";

  if(t1(n)) 
    cout << "PASSED\n";
  else
    cout << "FAILED\n";

  return 0;
}
