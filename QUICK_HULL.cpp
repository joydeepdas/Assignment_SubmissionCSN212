#include<bits/stdc++.h>
using namespace std;

struct point
{
	int x;
	int y;
};
vector<point> answer;
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

int dot(int A[], int B[], int C[]){
        int AB[2];
        int BC[2];
        AB[0] = B[0]-A[0];
        AB[1] = B[1]-A[1];
        BC[0] = C[0]-B[0];
        BC[1] = C[1]-B[1];
        int dot = AB[0] * BC[0] + AB[1] * BC[1];
        return dot;
    }
    //Compute the cross product AB x AC
    int cross(int A[], int B[], int C[]){
        int AB[2];
        int AC[2];
        AB[0] = B[0]-A[0];
        AB[1] = B[1]-A[1];
        AC[0] = C[0]-A[0];
        AC[1] = C[1]-A[1];
        int cross = AB[0] * AC[1] - AB[1] * AC[0];
        return cross;
    }
    //Compute the distance from A to B
    double distance(int A[], int B[]){
        int d1 = A[0] - B[0];
        int d2 = A[1] - B[1];
        return sqrt(d1*d1+d2*d2);
    }
    //Compute the distance from AB to C
    //if isSegment is true, AB is a segment, not a line.
    double linePointDist(int A[], int B[], int C[]){
       
            int dot1 = dot(A,B,C);
            if(dot1 > 0)return distance(B,C);
            int dot2 = dot(B,A,C);
            if(dot2 > 0)return distance(A,C);
        
        
    }
double linePointDist1(point A, point B, point C){
        double dist = ((B.x-A.x)*(C.y-A.y)-(B.y-A.y)*(C.x-A.x)) / sqrt((B.x-A.x)*(B.x-A.x)+(B.y-A.y)*(B.y-A.y));
            int dot1 = (C.x-B.x)*(B.x-A.x)+(C.y-B.y)*(B.y-A.y);
            //cout<<dot1<<endl;
            if(dot1 > 0)return sqrt((B.x-C.x)*(B.x-C.x)+(B.y-C.y)*(B.y-C.y));
            int dot2 = (C.x-A.x)*(A.x-B.x)+(C.y-A.y)*(A.y-B.y);
            //cout<<dot2<<endl;
            if(dot2 > 0)return sqrt((A.x-C.x)*(A.x-C.x)+(A.y-C.y)*(A.y-C.y));
        return abs(dist);
    }
void QuickHull_helper(vector<point> Sk,point A,point B){
	
	if(Sk.size()==0)
	{
		return;
	}
	
	// find point to be included in convex hull in the right side of A->B
	// finding furthest point from line segment A->B

	int maxi=linePointDist1(A,B,Sk[0]);
	
	int C=0;
	for(int i=0;i<Sk.size();i++){
		//cout<<i<<"->"<<linePointDist1(A,B,Sk[i])<<endl;
		if(linePointDist1(A,B,Sk[i])>maxi){
			maxi=linePointDist1(A,B,Sk[i]);
			C=i;
		}
	}
	
	answer.push_back(Sk[C]);
	
	// divide in right of A->C and in right of C->B
	vector<point> S1,S2;
	for (int i=0;i<Sk.size();i++){
		// find points in right of A->C
		if( orientation(A,Sk[C],Sk[i])==1){
			S1.push_back(Sk[i]);
		}
		// find points in right of C->B
		if( orientation(Sk[C],B,Sk[i])==1){
			S2.push_back(Sk[i]);
		}
	}
	QuickHull_helper(S1,A,Sk[C]);
	QuickHull_helper(S2,Sk[C],B);
	
	
	
}


vector<point> QuickHull( point array[], int n){
	
	
	if (n<3){
		return answer;
	}
	
	// calculate two furthest horizontal points
	
	// leftmost x
	int leftpoint=array[0].x;
	int mini=0;
	for( int i=0;i<n;i++){
		if( array[i].x < leftpoint )
		{
			mini=i;
			leftpoint= array[i].x;
		}
	}
	
	point A = array[mini];
	
	// rightmost x
	int rightpoint=array[0].x;
	mini=0;
	for( int i=0;i<n;i++){
		if( array[i].x > rightpoint )
		{
			mini=i;
			rightpoint= array[i].x;
		}
	}	
	point B = array[mini];
	
	answer.push_back(A);
	answer.push_back(B);
	
	vector<point> S1,S2;
	for (int i=0;i<n;i++){
		// find points in right of A->B
		if( orientation(A,B,array[i])==1){
			S1.push_back(array[i]);
		}
		// find points in right of B->A
		if( orientation(B,A,array[i])==1){
			S2.push_back(array[i]);
		}
	}
	
	
	QuickHull_helper(S1,A,B);
	QuickHull_helper(S2,B,A);
	
	return answer;
	
}
int dist( point p, point q){
	
	int distance= (p.x-q.x)*(p.x-q.x)+(p.y-q.y)*(p.y-q.y);
	return distance;
}

// helper function to quicksort for sorting w.r.t reference elements
point p;
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
	
	clock_t t1,t2;
    t1=clock();

	vector<point> answer=QuickHull(array,n);
	
	
	// arrange the points in clockwise or anticlockwise with starting as a refernce
	// sort all other points with reference to this minm point
	p=answer[0];
	
	
	// quick-sort
	qsort(&answer[1], answer.size()-1, sizeof(point),my_sort);
	
	t2=clock();
	//display result
	cout<<" The Convex Hull points obtaines are: "<<endl;
	for ( int i=0;i<answer.size();i++){
		cout<<"( " << answer[i].x << " , " << answer[i].y<< " )"<<endl;
	}
	
	
	
	float diff=((float)t2-(float)t1);
	float seconds = diff / CLOCKS_PER_SEC;	
	cout<<"clocks_per_sec--> "<<CLOCKS_PER_SEC<<endl;
	cout<<"clock_ticks--> "<<diff<<endl;
    cout<<"RUNNNING TIME --> "<<seconds<<endl;
	// Time Complexity O(nlogn).
	// In average case better than GRAHAM_SCAN AND GIFT_WRAP
}
