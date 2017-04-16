#include<bits/stdc++.h>
using namespace std;

struct point
{
	int x;
	int y;
};

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

// main function that returns the set of points included in convex hull

vector<point> ConvexHull( point array[], int n){
	
	vector<point> result;
	
	//  n<3 can't occur
	if (n<3){
		return result;
	}
	
	
	
	// start from leftmost element. 
	int left=0;
	for(int i=0;i<n;i++){
		if(array[i].x<array[left].x){
			left=i;
		}
	}
	
	// start from this leftmost element and move through the points till starting 
	// element is reached.
	int start=left;
	int next;
	int dummy=1; // dummy is set to zero after fisrt execution; to initiate the loop
	while(start!=left || dummy==1){
		dummy=0;
		result.push_back(array[start]);
		next=(start+1)%n;
		for(int i=0;i<n;i++){
			if( orientation(array[start],array[i],array[next])==2){
				next=i;
			}
		}
		
		start=next;
	}
	return result;
	
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
	
	 int n=10000;
	 
	 // generate hundred random numbers 
	 int arr1[n],arr2[n];
	 for(int i=0;i<n;i++){
	 	arr1[i]=rand()%1000000000; // range 0-99
	 }
	 for(int i=0;i<n;i++){
	 	arr2[i]=rand()%1000000000; // range 0-99
	 }
	 
	 point array[n];
	 for(int i=0;i<n;i++){
	 	array[i].x=arr1[i];
	 	array[i].y=arr2[i];
	 }
	 
	 int nn=sizeof(array)/sizeof(array[0]);

	clock_t t1,t2;
    t1=clock();

	vector<point> answer=ConvexHull(array,nn);
	
	t2=clock();
    
	//display result
	for ( int i=0;i<answer.size();i++){
		cout<<"( " << answer[i].x << " , " << answer[i].y<< " )"<<endl;
	}
	
	float diff=((float)t2-(float)t1);
	float seconds = diff / CLOCKS_PER_SEC;	
	cout<<"clocks_per_sec--> "<<CLOCKS_PER_SEC<<endl;
	cout<<"clock_ticks--> "<<diff<<endl;
    cout<<"RUNNNING TIME --> "<<seconds<<endl;
	
	// Time Complexity is O(n^2)
	
}
