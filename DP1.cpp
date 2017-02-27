/*
by Joydeep Das,14116032
problem1: https://community.topcoder.com/stat?c=problem_statement&pm=1259
*/

#include<bits/stdc++.h>
using namespace std;
int main(){
	int t;
	cin>>t;
	while(t--){
		int n;
		cin>>n;
		int arr[n];
		for(int i=0;i<n;i++){
			cin>>arr[i];
		}
		if(n==1){
			cout<<1<<endl;
		}
		vector<int> prev(n,-1);
		vector<int> maxlen(n,1);
		for(int i=0;i<n;i++){
			for(int j=0;j<i;j++){
				if( (arr[i] != arr[j]) && (prev[j] == -1 || (arr[i] - arr[j])*(arr[j] - arr[prev[j]]) <-1 )){
					if(maxlen[j]+1 > maxlen[i]){
					
						maxlen[i] = maxlen[j]+1;
						prev[i] = j;
					}
				}
			}
		}
		int ans=maxlen[0];
		for(int i=0;i<n;i++){
			if(maxlen[i]>ans){
				ans=maxlen[i];
			}
		}
		cout<<ans<<endl;
		
		
	}
}
