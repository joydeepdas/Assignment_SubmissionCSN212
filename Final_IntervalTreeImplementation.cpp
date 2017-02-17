#include <iostream>
using namespace std;
 
// Structure for an interval.
// "int" according to CLRS.
struct Interval
{
    int low, high;
};
 
// Structure for node in Interval Search Tree
// "x" according to CLRS
struct IntervalNode 
{
    Interval *interval;  // 'i' could also be a normal variable
    int max;
    IntervalNode *left, *right;
};
 
//  creation of a new Interval Search Tree Node
IntervalNode * newNode(Interval i)
{
    IntervalNode *temp = new IntervalNode;
    temp->interval = new Interval(i);
    temp->max = i.high;
    temp->left = NULL;
	temp->right = NULL;
};
 
// Interval-Insert according to CLRS
IntervalNode *Interval_Insert(IntervalNode *root, Interval i)
{

    if (root == NULL)
    {
		return newNode(i);
 	}
    
    // If root's low value is larger, then new interval goes to
    // left subtree
    if (i.low < root->interval->low)
        root->left = Interval_Insert(root->left, i);
 
    // Else
    else
        root->right = Interval_Insert(root->right, i);
 
    // Update the max value 
    if (root->max < i.high)
        root->max = i.high;
 
    return root;
}
 
//  function to check if given two intervals overlap
bool Interval_Overlap(Interval i1, Interval i2)
{
    if (i1.low <= i2.high && i2.low <= i1.high)
        return true;
    return false;
}
 
// interval search function according to CLRS
Interval *Interval_Search(IntervalNode *root, Interval i)
{
    
    if (root == NULL) return NULL;
 
    // If given interval overlaps with root
    if (Interval_Overlap(*(root->interval), i))
        return root->interval;
 
    // If left child of root is present and max of left child is greater than or equal to given interval, then i may
    // overlap with an interval is left subtree
    if (root->left != NULL && root->left->max >= i.low)
        return Interval_Search(root->left, i);
 
    // else 
    return Interval_Search(root->right, i);
}
 
// function required for delete operation
IntervalNode* minValue(IntervalNode *node)
{
    IntervalNode* current = node;
 
    // serach for leftmost leaf
    while (current->left != NULL)
        current = current->left;
 
    return current;
}

int maximum(int a,int b,int c){
	if(a>=b && a>=c){
		return a;
	}
	else if(b>=a && b>=a){
		return b;
	}
	else{
		return c;
	}
}

// delete operation on BST according to CLRS 
IntervalNode* Interval_delete(IntervalNode *root, Interval i)
{
    // base case
    if (root == NULL) return root;
 
    // If the interval's low is less than root's low ,then it lies in left subtree
    if (i.low < root->interval->low)
        root->left = Interval_delete(root->left, i);
 
    // else in right subtree
    else if (i.low > root->interval->low)
        root->right = Interval_delete(root->right, i);
 
    // if the root is the interval to be deleted
    else
    {
        // node with only one child or no child
        if (root->left == NULL)
        {
            IntervalNode *temp = root->right;
            //no update of int.max is required 
            return temp;
        }
        else if (root->right == NULL)
        {
            IntervalNode *temp = root->left;
            //no update of int.max is required 
            return temp;
        }
 
        // node with two children: Get the inorder successor acc. to BSt
        IntervalNode *temp = minValue(root->right);
 
        
        root->interval = temp->interval;
        //update max
 		root->max=maximum(root->max,root->left->max,root->right->max);
        // Delete the inorder successor
        root->right = Interval_delete(root->right, *temp->interval);
    }
    return root;
} 
 
 
 
 
 
 
 
 
 
 
 
 
void inorder(IntervalNode *root)
{
    if (root == NULL) return;
 
    inorder(root->left);
 
    cout << "{" << root->interval->low << ", " << root->interval->high << "}"<< endl;
 
    inorder(root->right);
}
 

int main()
{
    
    IntervalNode *root = NULL;	
 	root=Interval_Insert(root, {1,15});
    root=Interval_Insert(root, {7,23});
    root=Interval_Insert(root, {16,20});
    root=Interval_Insert(root, {22,35});
    root=Interval_Insert(root, {38,40});
 	
    cout <<"Inorder traversal of Interval Tree is"<<endl;
    inorder(root);
 	cout<<endl;
    Interval var = {25, 33};
 
    cout << "Search interval for {" << var.low << "," << var.high << "  is  ";
    Interval *res = Interval_Search(root, var);
    if (res == NULL)
    {
		cout << "No overlap interval in tree";
	}
    else{
        cout << "{" << res->low << ", " << res->high << "}"<< endl;
    }
    // deletetion operation
    cout<<"\nAfter deleteion of {38,40}, the inorder traversal is\n";
    root=Interval_delete(root,{38,40});
    inorder(root);
 	cout<<endl;
    
        
        
    return 0;
}
