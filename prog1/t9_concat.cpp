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


int testA(List<int> *lst1, List<int> *lst2, int n) {
  int success = 1;


  // two concats for good measure!
   lst1->concat(*lst2);
   lst2->concat(*lst1);

   if(lst1->length() != 0) 
     success = 0;
   if(lst2->length() != 2*n)
     success = 0;

   return success;
}


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

  START("List::concat test Suite (15 pts)"); 
  {
	int i;

	  PtsPer = 1.0;

	  int a[] = {1, 2, 3};
	  int b[] = {6, 7, 8};
	  int ab[] = {1, 2, 3, 6, 7, 8};

	  lsts[0] = arr2list(a, 3);
	  lsts[1] = arr2list(b, 3);
	  lsts[2] = arr2list(ab, 6);

	  lsts[0]->concat(*lsts[1]);
	  TEST_RET(lsts[1]->is_empty(), 
			"test: 2nd lst empty after concat? ", 
			1, PtsPer);

	  TEST_RET(lsts_equal_destructive(lsts[0], lsts[2]),
			"test concat([1,2,3],[6,7,8]) ", 
			1, PtsPer);

	  cleanup();
	  
	  lsts[0] = arr2list(a, 3);
	  lsts[1] = new List<int>();
	  lsts[2] = arr2list(a, 3);
	  lsts[0]->concat(*lsts[1]);
	  TEST_RET(lsts_equal_destructive(lsts[0], lsts[2]),
			"empty 2nd list test: concat([1,2,3], []) ", 
			1, PtsPer);
	  
	  cleanup();


	  lsts[0] = new List<int>();
	  lsts[1] = arr2list(a, 3);
	  lsts[2] = arr2list(a, 3);
	  lsts[0]->concat( *lsts[1]);
	  TEST_RET(lsts_equal_destructive(lsts[0], lsts[2]),
			"test with calling list given as empty ", 
			1, PtsPer);

	  cleanup();
	  lsts[0] = arr2list(a, 3);
	  lsts[1] = new List<int>();
	  lsts[2] = arr2list(a, 3);
	  lsts[0]->concat( *lsts[1]);
	  lsts[0]->push_back( 99);
	  lsts[2]->push_back( 99);
	  TEST_RET(lsts_equal_destructive(lsts[0], lsts[2]),
			"concat w/ empty list + push_back",
			1, PtsPer);

	  cleanup();
	  lsts[0] = arr2list(a, 3);
	  lsts[0]->concat( *lsts[0]);
	  TEST_RET(eq2array(lsts[0], a, 3),
			"test concatination with self (no-op)",
			1, PtsPer);

	  cleanup();

    // timed tests
    lsts[0] = lst_of_n_ones(n);
    lsts[1] = lst_of_n_ones(n);

    lsts[2] = lst_of_n_ones(2*n);
    lsts[3] = lst_of_n_ones(2*n);

    TIME_RATIO2(testA(lsts[0], lsts[1], n), 
        testA(lsts[2], lsts[3], 2*n),
        "runtime test concat two lists; with total of n elems",
        1, 1, 1.25, 8.0);



    cleanup();

    lsts[0] = lst_of_n_ones(10);
    lsts[1] = lst_of_n_ones(10);
    lsts[2] = lst_of_n_ones(10);
    lsts[3] =  lst_of_n_ones(10);
    lsts[4] =  lst_of_n_ones(40);

    lsts[0]->concat(*lsts[1]);
    lsts[0]->concat(*lsts[2]);
    lsts[0]->concat(*lsts[3]);

	  TEST_RET(lsts_equal_destructive(lsts[0], lsts[4]),
			"test sequence of concat ops",
			1, 1.0);


    cleanup();






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
