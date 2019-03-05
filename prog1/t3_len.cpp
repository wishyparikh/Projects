#include "List.h"

#include <stdlib.h>
#include <iostream>
#include <string>

#include "_test.h"
#include "_util.h"

int arrs[][5] = {
		{ 1, 2, 3, 4, 5} ,
		{ 5, 4, 3, 2, 1},
		{ 0, 2, 3, 4, 5} ,
		{ 1, 2, 3, 4, 0} ,
		{ 0, 0, 0, 0, 0} ,   //IDX-4
		{ 1, 0, 0, 0, 0} ,   //IDX-5
		{ 0, 0, 0, 0, 1},    //IDX-6
		{ 0, 1, 0, 1, 0}     //IDX-7
	     };

using namespace std;


int main(int argc, char *argv[]){
  int n = __N;
  int ntrials = __NTRIALS*100;
  int i, dummy;

  if(argc > 1)
    n = atoi(argv[1]);
  if(argc > 2)
    ntrials = atoi(argv[2]);

  set_ntrials(ntrials);

  printf("STARTING AUTO-TEST WITH: \n");
  printf("    N (Big Problem Size) = %i\n", n);
  printf("    NUM_TRIALS       = %i\n", ntrials);
  printf("USAGE TO OVER-RIDE DEFAULT N and NUM_TRIALS:\n");
  printf("    %s <N> <NUM_TRIALS>\n\n", argv[0]);
  printf("EXAMPLE WITH N=9999; NUM_TRIALS=100000:\n");
  printf("    %s 9999 100000\n\n", argv[0]);

  printf("here we go...\n\n");

  START("List::length COMPLETE test Suite"); 

	  lsts[0] = one_to_n_lst(n);
	  lsts[1] = one_to_n_lst(2*n);

    PtsPer = 3;

    TIME_RATIO2(lsts[0]->length(), lsts[1]->length(), 
        "runtime test (O(1)): push_font only",
        n, 2*n, 1.25, PtsPer);


	  for(i=0; i<n/2; i++) 
		  lsts[0]->pop_front(dummy);

	  for(i=0; i<(2*n)/2; i++) 
		  lsts[1]->pop_front(dummy);

    TIME_RATIO2(lsts[0]->length(), lsts[1]->length(), 
        "runtime test (O(1)): n push_fronts + n/2 pop_fronts",
        n-n/2, (2*n)-((2*n)/2), 1.25, PtsPer);

	  for(i=0; i<n/2; i++) 
		  lsts[0]->push_back(0);

	  for(i=0; i<(2*n)/2; i++) 
		  lsts[1]->push_back(0);

    TIME_RATIO2(lsts[0]->length(), lsts[1]->length(), 
        "runtime test (O(1)): n push_fronts + n/2 pop_fronts + n/2 push_backs",
        n, 2*n, 1.25, PtsPer);

    lsts[2] = new List<int>();

    lsts[2]->push_front(1);
    lsts[2]->push_back(2);
    lsts[2]->pop_front(dummy);
    lsts[2]->pop_front(dummy);
	  TEST_RET(lsts[2]->length(), "after emptying list", 0, PtsPer);

    lsts[2]->pop_front(dummy);
	  TEST_RET(lsts[2]->length(), 
        "after failing pop on empty list", 0, PtsPer);


  END





  printf("\n\nPOST-MORTEM...\n");
  printf("YOU JUST RAN THIS AUTO-TEST WITH: \n");
  printf("    N (Big Problem Size) = %i\n", n);
  printf("    NUM_TRIALS       = %i\n\n", ntrials);
  printf("IF YOU RECEIVED A ");
  _red_txt();
  printf("WARNING ");
  _normal_txt();
  printf(" ABOUT UNRELIABLE RUNTIEM MEASUREMENTS\n");
  printf("AND INCREASING NUMBER OF TRIALS / PROBLEM SIZE\n");
  printf("HERE IS HOW YOU DO IT:\n\n");
  printf("  USAGE TO OVER-RIDE DEFAULT N and NUM_TRIALS:\n");


  _cyan_txt();
  printf("    %s <N> <NUM_TRIALS>\n\n", argv[0]);
  _normal_txt();
  printf("  EXAMPLE WITH N=9999; NUM_TRIALS=100000:\n");
  _cyan_txt();
  printf("    %s 9999 100000\n\n", argv[0]);
  _normal_txt();

  cleanup();

  return 0;
}
