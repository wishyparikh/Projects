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
  int ntrials = __NTRIALS;
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

  START("List::filter_leq COMPLTE test Suite (20/20 pts)"); 
  {
	int i;

	  PtsPer = 2.0;


	  lsts[0] = arr2list(arrs[0], 5);
	  lsts[1] = lsts[0]->filter_leq( 0);
	  TEST_RET(lsts[1]->is_empty(), 
			"test case with empty filtered list",
			1, PtsPer);

	  TEST_RET(eq2array(lsts[0], arrs[0], 5), 
			"empty filtered list: is given list intact?",
			1, PtsPer);


	 cleanup();
	  lsts[0] = arr2list(arrs[0], 5);
	  lsts[1] = lsts[0]->filter_leq( 9);
	
	  TEST_RET_MESSAGE(lsts[0]->is_empty(), 
			"test case where everything is LEQ: given list empty?", 
			true, PtsPer);

	  TEST_RET(eq2arrayP(lsts[1], arrs[0], 5), 
			"test case where everything is LEQ: returned list correct?", 
			1, PtsPer);

	cleanup();

	{
	 int a[] = {2, 0, 2, 2, 0, 0, 2, 0};
	 int leq[] = {0, 0, 0, 0};
	 int gt[] = {2, 2, 2, 2};

	 lsts[0] = arr2list(a, 8);
	 lsts[1] = lsts[0]->filter_leq( 1);

	  TEST_RET(eq2arrayP(lsts[1], leq, 4), 
			"test: 4 0's, 4 2's; cutoff=1 - is LEQ correct?",
			1, PtsPer);
	 
	  TEST_RET(eq2arrayP(lsts[0], gt, 4), 
			"test: 4 0's, 4 2's; cutoff=1 - is right-side correct?",
			1, PtsPer);

	}
	cleanup();
	{
	 int a[] = {10, 8, 6, 4, 2, 0};
	 int leq[] = {4, 2, 0};
	 int gt[] = {10, 8, 6};

	 lsts[0] = arr2list(a, 6);
	 lsts[1] = lsts[0]->filter_leq( 5);

	 lsts[2] = arr2list(leq, 3); // leq list
	 lsts[3] = arr2list(gt, 3); // greater-than list

	  TEST_RET(same_contents(lsts[1], lsts[2], 1),
			"test: [10 8 6 4 2 0]; cutoff=5 - is LEQ correct?",
			1, PtsPer);
	 
	  TEST_RET(same_contents(lsts[0], lsts[3], 1),
			"test: [10 8 6 4 2 0]; cutoff=5 - is RHS correct?",
			1, PtsPer);
	}
	cleanup();
	{
	 int i;

	 lsts[0] = new List<int>();
	 lsts[2] = new List<int>(); // zeros
	 lsts[3] = new List<int>(); // twos
	 for(i=0; i<1000; i++) {
		lsts[0]->push_front(2);
		lsts[0]->push_front(0);
		lsts[2]->push_front(0);
		lsts[3]->push_front(2);
	 }
	 lsts[1] = lsts[0]->filter_leq( 1);
	  TEST_RET(lsts_equal_destructive(lsts[1], lsts[2]),
			"test: 1000 0's, 1000 2's; cutoff=1 - is LEQ correct?",
			1, PtsPer);

	  TEST_RET(lsts_equal_destructive(lsts[0], lsts[3]),
			"test: 1000 0's, 1000 2's; cutoff=1 - is RHS correct?",
			1, PtsPer);
	 }	

  }
  END

  printf("\n\nPOST-MORTEM...\n");
  printf("YOU JUST RAN THIS AUTO-TEST WITH: \n");
  printf("    N (Big Problem Size) = %i\n", n);
  printf("    NUM_TRIALS       = %i\n\n", ntrials);
  printf("IF YOU RECEIVED A ");
  _red_txt();
  printf("WARNING ");
  _normal_txt();
  printf(" ABOUT UNRELIABLE RUNTIME MEASUREMENTS\n");
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
