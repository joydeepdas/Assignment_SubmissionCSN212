/*
	Joydeep Das
	14116032,3rd Year ECE
	Tutorial 3: Implementation of Interval Tree (insertion, search) using BST.
	
*/

#include<bits/stdc++.h>
using namespace std;

struct Interval
{
	int start;
	int end;
};

struct Node
{
	struct Interval data;
	int max;
	struct Node* left; // pointer to left Node
	struct Node* right; //pointer to right Node
};


// funtion to make a new Node 
struct Node* createNode(Interval data)
{
	struct Node* temp = new Node; //if new is not used then temp will get deallocated 
	temp->data=data;
	temp->max=data.end;
	temp->left=NULL;
	temp->right=NULL;
	return temp;	
}

// function insert
struct Node* insert(struct Node* root,Interval data)
{
	struct Node* temp=root;
	// if root is empty
	if(temp==NULL)	return createNode(data);
	
	// updating max value
	if(temp->max<data.end)	temp->max=data.end;
	
	// if the start value of interval is larger than root's start then the new interval goes to right sub-tree
	if(data.start>=(temp->data).start)
		temp->right=insert(temp->right,data);				
	// else go to left	
	else{
		temp->left=insert(temp->left,data);
	}
	
	return root;
}

//search function
struct Node* searchInterval(struct Node* root,Interval data)
{
	struct Node* temp=root;
	while(temp!=NULL && (data.start>temp->data.end || data.end<temp->data.start))
	{
		// If left of root is present and max of left child is >= to given interval, solution is in left subtree
		if(temp->left!=NULL && data.start < temp->left->max)
		{
				temp=temp->left;
		}
		// Or  interval may overlap with right subtree	
		else temp=temp->right;
	}
	return temp;
}



void Inorder(struct Node* root)
{
	if(root==NULL)	return;
	Inorder(root->left);
	cout << "[" << root->data.start << ", " << root->data.end << "]"<< endl;
	Inorder(root->right);
}



int main()
{	
	// Initialize root with null
	struct Node* root=NULL;
	// given random interval values
    root=insert(root, {1,15});
    root=insert(root, {7,23});
    root=insert(root, {16,20});
    root=insert(root, {22,35});
    root=insert(root, {38,40});
    
    // printing the inoder traversal of tree
	Inorder(root);
   	// search for an interval
   	struct Node* temp;
   	Interval data={25,33};
    temp=searchInterval(root,data);
    // print the found start and end of interval
    cout<< "Found interval matching with provided data : "<<data.start<<" " <<data.end<< "  is  "<<temp->data.start<< " "<<temp->data.end<<endl;
    
    
   
}
