
/*
by Joydeep Das,14116032
problem3: https://www.codechef.com/problems/D2/
*/



#include<bits/stdc++.h>
using namespace std;


// Binary search 
int CeilIndex(vector<int> &v, int l, int r, int key) {
    while (r-l > 1) {
    int m = l + (r-l)/2;
    if (v[m] >= key)
        r = m;
    else
        l = m;
    }
 
    return r;
}

int modified_LIS(int arr[], int n){
	vector<int> maxlen(10005);
	maxlen[0]=arr[0];
	int length=1;
	for(int i=0;i<n;i++){
		if(arr[i]<maxlen[0]){
			maxlen[0]=arr[i];
			
		}
		else if(arr[i]>maxlen[length-1]){
        	maxlen[length]=arr[i];
        	length++;
		}
        else{
        	maxlen[CeilIndex(maxlen,-1,length-1,arr[i])]=arr[i];
		}   
	}
	return  length;
}

int main(){
	int t;
	cin>>t;
	int arr[10005*2];
	while(t--){
		int n;
		cin>>n;
		for(int i=0;i<n;i++){
			cin>>arr[i];
			arr[n+i]=arr[i];
		}
		int ans=0;
		for(int i=0;i<n;i++){
			ans=max(ans,modified_LIS(arr+i,n));
		}
		cout<<ans<<endl;
	}
	
}

