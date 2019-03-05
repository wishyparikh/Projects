#ifndef _BST_H
#define _BST_H

#include <iostream>
using namespace std;
#include <vector>

template <typename T>
class bst {

private:
	struct bst_node 
	{
		T      val;
		bst_node *left;
		bst_node *right;
		//Booking keeping information.
		int count_left = 0;
		int count_right = 0;
		bst_node(const T & _val = T{}, bst_node * l = nullptr, bst_node *r = nullptr)
			: val{ _val }, left{ l }, right{ r }
		{ }
	};

public:
	// constructor:  initializes an empty tree
	bst() 
	{
		root = nullptr;
	}

private:
	// helper function which recursively deallocates nodes
	//   in a tree.
	static void delete_nodes(bst_node *r) 
	{
		if (r == nullptr) return;
		delete_nodes(r->left);
		delete_nodes(r->right);
		delete r;
	}
public:
	// destructor
	~bst() {
		delete_nodes(root);
	}

private:
	/**
	* function:  insert()
	* desc:      recursive helper function inserting x into
	*            binary search tree rooted  at r.
	*
	* returns:   pointer to root of tree after insertion.
	*
	* notes:     if x is already in tree, no modifications are made.
	*/
	static bst_node * _insert(bst_node *r, T & x, bool &success)
	{
		if (r == nullptr)
		{
     		success = true;
			return new bst_node(x, nullptr, nullptr);
		}
		if (r->val == x)
		{
			success = false;
			return r;
		}
		// If x is less than root->val.
		if (x < r->val)
		{
			int max;
			int min;
			// insert
			r->left = _insert(r->left, x, success);
			// Updating the book keeping information.
			if (success == true)
			{
				r->count_left = 1 + r->count_left;     // Update booking keeping. 
				if (r->count_left > r->count_right)
				{
					max = r->count_left;
					min = r->count_right;
				}
				else
				{
					max = r->count_right;
					min = r->count_left;
				}
				if (max > (2 * min + 1))           // Rebalance condition.
				{
					// rebalance
					std::vector<T>* vv = get_vector(r);	   // Get the vector array in sorted from the closest point of violation.         
					bst_node*temp = r;
					int total = r->count_left + r->count_right;
					r = _from_vec(*vv, 0, total);
					delete temp;      // Deleting memory leaks.
					delete vv;        // Deleting memory leaks.
				}
			}
			//cout << r->val << "  root node contains [ " << r->count_left << "  " << r->count_right << " ]" << endl << endl;
			return r;
		}
		// If x is greater than root->val.
		else
		{
			int max;
			int min;
			// insert
			r->right = _insert(r->right, x, success);
			// Updating the book keeping information.
			if (success == true)
			{
				r->count_right = 1 + r->count_right;
				if (r->count_left > r->count_right)
				{
					max = r->count_left;
					min = r->count_right;
				}
				else
				{
					max = r->count_right;
					min = r->count_left;
				}
				if (max > 2 * min + 1)
				{
					// rebalance
					std::vector<T>* vv = get_vector(r);
					bst_node*temp = r;
					int total = r->count_left + r->count_right;
					r = _from_vec(*vv, 0, total);
					delete temp;
					delete vv;
				}
			}
		//	cout << r->val << "  root node contains [ " << r->count_left << "  " << r->count_right << " ]" << endl << endl;
			return r;
		}
	}
	
public:
	/**
	* function:  insert
	* desc:      inserts x into BST given by t.  Note that
	*            a BST stores a SET -- no duplicates.  Thus,
	*            if x is already in t when call made, no
	*            modifications to tree result.
	*
	* note:      helper function does most of the work.
	*
	*/
	bool insert(T & x) 
	{
		bool success;
		root = _insert(root, x, success);
		return success;
	}

	/**
	* function:  contains()
	* desc:      returns true or false depending on whether x is an
	*            element of BST (calling object)
	*
	*/
	bool contains(const T & x) 
	{
		bst_node *p = root;

		while (p != nullptr) 
		{
			if (p->val == x)
				return true;
			if (x < p->val) {
				p = p->left;
			}
			else
				p = p->right;
		}
		return false;
	}

private:
	// returns pointer to node containing
	//   smallest value in tree rooted at r
	static bst_node * _min_node(bst_node *r) 
	{
		if (r == nullptr)
			return nullptr; // should never happen!
		while (r->left != nullptr)
			r = r->left;
		return r;
	}

	// returns pointer to node containing
	//   smallest value in tree rooted at r
	static bst_node * _max_node(bst_node *r) 
	{
		if (r == nullptr)
			return nullptr; // should never happen!
		while (r->right != nullptr)
			r = r->right;
		return r;
	}

	// recursive helper function for node removal
	//   returns root of resulting tree after removal.
	static bst_node * _remove(bst_node *r, T & x, bool &success)
	{
		bst_node *tmp;
		bool sanity;
		if (r == nullptr) {
			success = false;
			return nullptr;
		}
		if (r->val == x)
		{
			success = true;
			if (r->left == nullptr)
			{
				tmp = r->right;
				delete r;
				return tmp;
			}
			if (r->right == nullptr)
			{
				tmp = r->left;
				delete r;
				return tmp;
			}
			// if we get here, r has two children
			r->val = _min_node(r->right)->val;
			r->right = _remove(r->right, r->val, sanity);       // Might need to update information here.
			if (sanity)
			{
				r->count_right = r->count_right - 1;
			}
			//--------------------------------------------------------------------------------------------
			                        //


			//--------------------------------------------------------------------------------------------
			if (!sanity)
				std::cerr << "ERROR:  remove() failed to delete promoted value?\n";
			return r;
		}
		if (x < r->val)
		{
			int max;
			int min;
			r->left = _remove(r->left, x, success);

			// if success, then 1) update book-keeping. 2) min and max and 3) populate vector. 4) rebalance.
			// Updating the book keeping information.-------------------------1
			if (success == true)
			{
				r->count_left = r->count_left - 1;                         // Updating the book keeping information--1
				// Assign min and max.--------------------2
				if (r->count_left > r->count_right)
				{
					max = r->count_left;
					min = r->count_right;
				}
				else
				{
					max = r->count_right;
					min = r->count_left;
				}
				// Rebalance condition.
				if (max > (2 * min + 1))
				{
					// Populate vector. ---------------------------------------3
					std::vector<T>* vv = get_vector(r);
					// Print the populate vector elements.
					
					bst_node*temp = r;
					int total = r->count_left + r->count_right;
					r = _from_vec(*vv, 0, total);                // Function call to rebalance. Rebalance the root.---------4
					delete temp;
					delete vv;
				}
			}
			
			return r;
		}
		else
		{
			int max;
			int min;

			// if success, then 1) update book-keeping. 2) min and max and 3) populate vector. 4) rebalance.
			r->right = _remove(r->right, x, success);

			// if success, then 1) update book-keeping. 2) min and max and 3) populate vector. 4) rebalance.

			// Updating the book keeping information.-------------------------1
			if (success == true)
			{
				r->count_right = r->count_right - 1;                         // Updating the book keeping information--1
																		   // Assign min and max.--------------------2
				if (r->count_left > r->count_right)
				{
					max = r->count_left;
					min = r->count_right;
				}
				else
				{
					max = r->count_right;
					min = r->count_left;
				}
				// Rebalance condition.
				if (max > (2 * min + 1))
				{
					// Populate vector. ---------------------------------------3
					std::vector<T>* vv = get_vector(r);
					// Print the populate vector elements.
					
					
					
					bst_node*temp = r;
					int total = r->count_left + r->count_right;
					r = _from_vec(*vv, 0, total);                // Function call to rebalance. Rebalance the root.---------4
					delete temp;
					delete vv;
				}
			}
			
			return r;
		}
	}

public:

	bool remove(T & x) 
	{
		bool success;
		root = _remove(root, x, success);
		return success;
	}


private:
	// recursive helper function to compute size of
	//   tree rooted at r
	static int _size(bst_node *r) 
	{
		if (r == nullptr) return 0;
		return _size(r->left) + _size(r->right) + 1;
	}

public:
	int size() 
	{
		return _size(root);
	}

private:

	static int _height(bst_node *r) 
	{
		int l_h, r_h;

		if (r == nullptr) return -1;
		l_h = _height(r->left);
		r_h = _height(r->right);
		return 1 + (l_h > r_h ? l_h : r_h);
	}

public:

	int height() 
	{
		return _height(root);
	}

	bool min(T & answer) 
	{
		if (root == nullptr) 
		{
			return false;
		}
		answer = _min_node(root)->val;
		return true;
	}

	T max() {
		return _max_node(root)->val;
	}

	/******************************************
	*
	* "stubs" for assigned TODO functions below
	*
	*****************************************/

	// TODO----------------------------------------------1   Done
	std::vector<T> * to_vector() 
	{
		// Create a new vector. pointer that points to new vector.------1
		std::vector<T>* v = new std::vector<T>();  
		// Helper function for pushback.
		v_addNodes(&v, root);
		return v;
	}
	static void v_addNodes(std::vector<T>** v, bst_node* rt)
	{
		if (rt == nullptr)
		{
			return;
		}
		v_addNodes(v, rt->left);
		(*v)->push_back(rt->val);
		v_addNodes(v, rt->right);
	}

	// Hepler function for populating the array for rebalancing.
	static std::vector<T> * get_vector( bst_node*r )
	{
		// Create a new vector. pointer that points to new vector.------1
		std::vector<T>* v = new std::vector<T>();
		// Helper function for pushback.
		v_addNodes(&v, r);
		return v;
	}

	


	/* TODO-------------------------------------------2 Done.
	* Function:  get_ith
	* Description:  determines the ith smallest element in t and
	*    "passes it back" to the caller via the reference parameter x.
	*    i ranges from 1..n where n is the number of elements in the
	*    tree.
	*
	*    If i is outside this range, false is returned.
	*    Otherwise, true is returned (indicating "success").
	*
	* Runtime:  O(h) where h is the tree height
	*/
	bool get_ith(int i, T &x) 
	{
		int position = 0;
		if (root == nullptr)         // Empty tree.   range checking.
		{
			return false;
		}
    	bst_node *p = root;
		while (p!= nullptr)
		{	
			if (i == p->count_left + 1 + position)
			{
				x = p->val;
				return true;
			}
			if (i > p->count_left + 1  + position)
			{			
				position = position + p->count_left +1;    // Update position when going to right.
				p = p->right;
			}
			else
			{
				p = p->left;
			}
	    }
		return false;   //  i is outside range---------------------------error checking.
	}

	bool get_ith_SLOW(int i, T &x) 
	{
		int n = size();
		int sofar = 0;

		if (i < 1 || i > n)
			return false;

		_get_ith_SLOW(root, i, x, sofar);
		return true;
	}

	/* TODO------------------------------------------------------3 Done
	* Function:  num_geq
	* Description:  returns the number of elements in tree which are
	*       greater than or equal to x.
	*
	* Runtime:  O(h) where h is the tree height
	*/
	int num_geq(const T & x) 
	{
		bst_node *p = root;
		int sum = 0;
		if (p == nullptr)
		{
			return 0;
		}
		while (p != nullptr)
		{
			if (x <= p->val) 
			{
				sum = sum + (p->count_right +1) ;
				p = p->left;
			}
			else
			{
				p = p->right;
			}			
		}
		return sum;
	}

	/*
	* function:     num_geq_SLOW
	* description:  same functionality as num_geq but sloooow (linear time)
	*
	*/
	int num_geq_SLOW(const T & x) 
	{
		return _num_geq_SLOW(root, x);
	}

	/* TODO----------------------------------------------------------4 Done
	* Function:  num_leq
	* Description:  returns the number of elements in tree which are less
	*      than or equal to x.
	*
	* Runtime:  O(h) where h is the tree height
	*
	**/
	int num_leq(const T &x) 
	{
		bst_node *p = root;
		int sum = 0;
		if (p == nullptr)                          // Empty tree.
		{
			return 0;
		}
		while (p != nullptr)
		{
			if (x >= p->val)
			{
				sum = sum + (p->count_left + 1);
				
				p = p->right;
			}
			else
			{
				p = p->left;
    		}
		}
		return sum;  // placeholder
	}

	/*
	* function:     num_leq_SLOW
	* description:  same functionality as num_leq but sloooow (linear time)
	*
	*/
	int num_leq_SLOW(const T & x) 
	{
		return _num_leq_SLOW(root, x);
	}

	/* TODO--------------------------------------------------------------5 Done
	* Function:  num_range
	* Description:  returns the number of elements in tree which are
	*       between min and max (inclusive).
	*
	* Runtime:  O(h) where h is the tree height
	*
	**/
	int num_range(const T & min, const T & max) 
	{
		if (root == nullptr)           // Empty tree.---------- error checking.
		{
			return 0;
		}
		if (max < min)                 // Invalid input range.........error checking.
		{
			return 0;
		}	
		int less;
		int greater;
		int range = 0;
     	less = num_leq(min);
		greater = num_geq(max);
		int total = this->root->count_left + this->root->count_right + 1;
		// 4 possible casses.
		if (contains(min) && contains(max))             // Both Range contains keys
		{	
			range = (total - (less + greater)) +2;
			cout << range;
			return range;
		}
		if (contains(min) || contains(max))         // Either Range contain keys.
		{
			range = (total - (less + greater))  +1 ;
			return range;
		}
		if (!contains(min) && !contains(max))      // None of range contain keys.
		{
			range = total - (less + greater);
			return range;
		}
		return 0;
	}
	/*
	* function:     num_range_SLOW
	* description:  same functionality as num_range but sloooow (linear time)
	*
	*/
	int num_range_SLOW(const T & min, const T & max) {
		return _num_range_SLOW(root, min, max);
	}

private:

	static void _get_ith_SLOW(bst_node *t, int i, T &x, int &sofar) {
		if (t == nullptr)
			return;
		_get_ith_SLOW(t->left, i, x, sofar);

		if (sofar == i)
			return;
		sofar++;
		if (sofar == i) {
			x = t->val;
			return;
		}
		_get_ith_SLOW(t->right, i, x, sofar);
	}

	static int _num_geq_SLOW(bst_node * t, const T & x) {
		int total;

		if (t == nullptr) return 0;
		total = _num_geq_SLOW(t->left, x) + _num_geq_SLOW(t->right, x);

		if (t->val >= x)
			total++;
		return total;
	}

	static int _num_leq_SLOW(bst_node *t, const T &x) {
		int total;

		if (t == nullptr) return 0;
		total = _num_leq_SLOW(t->left, x) + _num_leq_SLOW(t->right, x);

		if (t->val <= x)
			total++;
		return total;
	}

	static int _num_range_SLOW(bst_node *t, const T &min, const T &max)
	{
		int total;
		if (t == nullptr) return 0;
		total = _num_range_SLOW(t->left, min, max) +
			_num_range_SLOW(t->right, min, max);
		if (t->val >= min && t->val <= max)
			total++;
		return total;
	}





private:
	static void indent(int m) {
		int i;
		for (i = 0; i<m; i++)
			std::cout << "-";
	}

	static void _inorder(bst_node *r) 
	{
		if (r == nullptr) return;
		_inorder(r->left);
		std::cout << "[ " << r->val << " ]\n";
		_inorder(r->right);
	}

	static void _preorder(bst_node *r, int margin) {
		if (r == nullptr) {
			indent(margin);
			std::cout << " nullptr \n";
		}
		else {
			indent(margin);
			std::cout << "[ " << r->val << " ]\n";
			_preorder(r->left, margin + 3);
			_preorder(r->right, margin + 3);
		}

	}

	/*
	* TODO:
	* Complete the (recursive) helper function for the post-order traversal.
	* Remember: the indentation needs to be proportional to the height of the node!
	*/
	static void _postorder(bst_node *r, int margin) {

		std::cout << "\n   WARNING:  POSTORDER UNIMPLEMENTED...\n";
	}

public:
	void inorder() {
		std::cout << "\n======== BEGIN INORDER ============\n";
		_inorder(root);
		std::cout << "\n========  END INORDER  ============\n";
	}


	void preorder() {

		std::cout << "\n======== BEGIN PREORDER ============\n";
		_preorder(root, 0);
		std::cout << "\n========  END PREORDER  ============\n";

	}

	// indentation is proportional to depth of node being printed
	//   depth is #hops from root.
	void postorder() {

		std::cout << "\n======== BEGIN POSTORDER ============\n";
		_postorder(root, 0);
		std::cout << "\n========  END POSTORDER  ============\n";

	}

private:
	/*
	* Recursive  helper function _from_vec, used by
	* bst_from_sorted_arr(...). The function must return a sub-tree that is
	* perfectly balanced, given a sorted array of elements a.
	*/
	static bst_node * _from_vec(const std::vector<T> &a, int low, int hi) 
	{
		int m;
		bst_node *root;
		if (hi < low) return nullptr;
		m = (low + hi) / 2;
		root = new bst_node(a[m]);
		root->left = _from_vec(a, low, m - 1);
		if (root->left != nullptr)
		{
			root->count_left = root->left->count_left + root->left->count_right + 1;  // Adding all nodes from its left subtree to root.
		}
		root->right = _from_vec(a, m + 1, hi);
		if (root->right != nullptr)
		{
			root->count_right = root->right->count_left + root->right->count_right + 1;  // Adding all nodes from its right subtree to root.
		}
		return root;
	}

public:
	static bst* from_sorted_vec(const std::vector<T> &a, int n)
		//	 static void from_sorted_vec(int j, int n)
	{

		bst * t = new bst();
		t->root = _from_vec(a, 0, n - 1);
		return t;
	}       

	// TODO:  num_leaves
	//   Hint:  feel free to write a helper function!!
	int num_leaves() 
	{

		std::cout << "\n     WARNING:  bst::num_leaves UNIMPLEMENTED...\n";
		return 0;
	}

	// TODO:  num_at_level
	// description:  returns the number of nodes at specified level
	//   in tree.
	// note:  the root is at level 0.
	// Hint:  recursive helper function?
	int num_at_level(int level) 
	{

		std::cout << "\n     WARNING:  bst::num_leaves UNIMPLEMENTED...\n";
		return 0;
	}


private:
	bst_node * root;            // Main head of the tree. Top root of the tree.


}; // end class bst

#endif
#pragma once
