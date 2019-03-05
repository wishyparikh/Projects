


Name:
Wishy Parikh
-----------------------------------------------

Please confirm that you compiled your solution with test cases exercising ALL
functions using g++ -std=c++11.  Confirm this statement by typing YES below.
(If you did not do this, compilation errors may result in an overall grade of
zero!)

Yes, i compliled it with the syntax above.




Describe what augmentations to the bst data structures you made to complete the 
project -- i.e., what types / data members did you change and why?

I changed the stucture and added height. so that i can keep the track of height at each node.
Added some variables like count leaf nodes and height at the ith node.





-----------------------------------------------
Which functions did you need to modify as a result of the augmentations from the previous
question?  

Insert so that we can insert values in AVL form.
Delete function so that we can delete and arrange the values in avl form.







-----------------------------------------------
For each function from the previous question, how did you ensure that the (assymptotic) runtime 
remained the same?



Yes, i ensured that the changes that i made doesnt alter the runtime.




-----------------------------------------------
For each of the assigned functions, tell us how far you got using the choices 0-5 and
answer the given questions.  


0:  didn't get started
1:  started, but far from working
2:  have implementation but only works for simple cases
3:  finished and I think it works most of the time but not sure the runtime req is met. 
4:  finished and I think it works most of the time and I'm sure my design leads to 
       the correct runtime (even if I still have a few bugs).
5:  finished and confident on correctness and runtime requirements
 




to_vector level of completion:  __4_________  


-----------------------------------------------
get_ith level of completion:  _5__________  

    How did you ensure O(h) runtime?

    ANSWER: code checks the values in every level of tree so it depends on the height of the tree.

-----------------------------------------------
num_geq level of completion:  ___5________  

    How did you ensure O(h) runtime?

    ANSWER: Code checks the values in every level of the tree so it depends on the height of the tree.

-----------------------------------------------
num_leq level of completion:  ___5_________

    How did you ensure O(h) runtime?

    ANSWER: Code checks the values in every level of the tree so it depends on the height of the tree.


-----------------------------------------------
num_range level of completion:  __5__________

    How did you ensure O(h) runtime?

    ANSWER: Code checks the values in every level of the tree so it depends on the height of the tree.


-----------------------------------------------
Implementation of size-balanced criteria according to 
the given guidelines (including bst_sb_work):

    Level of completion: ___4________


Write a few sentences describing how you tested your solutions.  Are there
any tests that in retrospect you wish you'd done?


i added 100 values in the tree by using for loop and ran the functions by calling them individually.








