#include<bits/stdc++.h>
using namespace std;

struct point
{
	int x;
	int y;
};

point p; // for referene point during sorting it is used.

int swap( point &x, point&y){
	point temp=x;
	x=y;
	y=temp;
}

int dist( point p, point q){
	
	int distance= (p.x-q.x)*(p.x-q.x)+(p.y-q.y)*(p.y-q.y);
	return distance;
}

// for finding point below top for repeated 
// deletion of elements from stack based on
// hether (nexttoTOP,TOP,newPoint) form an anticlockwise rotation

point BelowTop( stack<point> &s){
	
	point temp1=s.top();
	s.pop();
	point temp2=s.top();
	s.push(temp1);
	
	return temp2;
}

int orientation( point p, point q, point r ){
	// actually the underlying value to be found out 
	// is the slope of two different line segments and then comparing their slopes.
	
	int value= (q.y-p.y) * (r.x-q.x) - (q.x-p.x)*(r.y-q.y);
	
	if (value==0)
	{
		// colinear points
		return 0;
	}
	
	if (value >0 ){
		//clockwise
		return 1;
	}
	else{
		//anticlockwise
		return 2;
	}
}

// helper function to quicksort for sorting w.r.t reference elements

int my_sort( const void *p1, const void *p2){
	point *x= (point *)p1;
	point *y= (point *)p2;
	
	int ans= orientation(p,*x,*y);
	
	if ( ans ==0){
		if ( dist(p,*y)>= dist(p,*x)){
			return -1;
		}
		else return 1;
	}
	
	else if( ans==2){
		return -1;
	}
	
	else
	{
		return 1;
	}
	
	
}


// function for conver hull finding


vector<point> ConvexHull( point array[], int n){
	
	// find lowest y and in case of tie choose the point 
	// with leftest x
	int minpoint=array[0].y;
	int mini=0;
	for( int i=0;i<n;i++){
		if( array[i].y < minpoint || (array[i].y == minpoint &&
		 array[i].x<array[mini].x))
		 {
		 	mini=i;
		 	minpoint= array[i].y;
		 }
	}
	
	// start by placing this point to array[0]
	swap( array[0],array[mini]);
	
	// sort all other points with reference to this minm point
	p=array[0];
	
	// quick-sort
	qsort(&array[1], n-1, sizeof(point),my_sort);
	
	// now to reduce the sorted array further by removing points making 
	// same angle with the one that is farthest from reference array[0]
	
	int si=1; //size
	for(int i=0;i<n;i++){
		while( i<n-1 && orientation(p,array[i],array[i+1])==0){
			i++;
		}
		array[si]=array[i];
		si++;
	}
	
	vector<point> answer;
	
	if (si<3){
		return answer;
	}
	
	// process for retaining m-3 points by
	// taking triplets of three
	
	stack <point> s;
	s.push(array[0]);
	s.push(array[1]);
	s.push(array[2]);
	
	for (int i=3;i<si;i++){
		while( orientation(BelowTop(s),s.top(),array[i])!=2){
			s.pop();
		}
		s.push(array[i]);
	}
	
	while(s.empty()==false){
		point temp=s.top();
		answer.push_back(temp);
		s.pop();
	}
}

int main(){
	// reading input from user
	/*
	int n;
	cin>>n;
	
	point array[n];
	
	for(int i=0;i<n;i++){
		int xx,yy;
		cin>>xx>>yy;
		array[i].x=xx;
		array[i].y=yy;
	}
	*/
	// Uncomment user input to try that
	
	 point  array[] = {{0, 3}, {2, 2}, {1, 1}, {5, 1}, {3, 0}, {1, 0}, {3, 6}};
	 int n=sizeof(array)/sizeof(array[0]);


	vector<point> answer=ConvexHull(array,n);
	
	//display result
	for ( int i=0;i<answer.size();i++){
		cout<<"( " << answer[i].x << " , " << answer[i].y<< " )"<<endl;
	}
	
	// Time Complexity is O(n*logn)
	
}
