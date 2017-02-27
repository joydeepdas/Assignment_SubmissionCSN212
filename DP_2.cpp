/*
by Joydeep Das,14116032
problem2: https://community.topcoder.com/stat?c=problem_statement&pm=1889
*/


#include<bits/stdc++.h>
using namespace std;

bool BadRoad(int x1, int y1, int x2, int y2, vector<string>bad){
	string comb = " ";
	stringstream ssx1,ssy1,ssx2,ssy2;
	ssx1 << x1;
	ssy1 << y1;
	ssx2 << x2;
	ssy2 << y2;
	string strx1 = ssx1.str();
	string stry1 = ssy1.str();
	string strx2 = ssx2.str();
	string stry2 = ssy2.str();
	string x = strx1 + comb + stry1 + comb + strx2 + comb + stry2 ; 
	string y = strx2 + comb + stry2 +comb + strx1 + comb + stry1 ; 		
	bool isBadRoad = false ; 
	for(int i=0;i<bad.size();i++){
		if( bad[i].compare(x)==0 || bad[i].compare(y)==0 ){
			isBadRoad = true ; 
			break ; 
		}
	}
	return isBadRoad ; 
}


long long numWays(int width, int height,vector< string> bad){
	long ans[width+1][height+1]; 
		for(int i=1;  i<=width;  i++){
			if( !BadRoad(i,0, i-1, 0, bad) ){ 
				ans[i][0] = 1;  
			}
			else{
				break ; 
			}
		}
				
		for(int j=1;  j<=height; j++){
			if( !BadRoad(0, j, 0, j-1, bad) ){ 
				ans[0][j] = 1; 
			}
			else{ 
				break; 
			}
		}

		for(int i=1;  i<=width;  i++)
		{
			for(int j=1;  j<=height;  j++)
			{
				if( !BadRoad(i, j, i-1, j, bad) )
					ans[i][j] += ans[i-1][j];
				
				if( !BadRoad(i, j, i, j-1, bad) )
					ans[i][j] += ans[i][j-1];				
			}
		}
		return ans[width][height] ; 
}

	
	
	
	
	
int main(){
	int t;
	cin>>t;
	while(t--){
		/*
		int width  = 6;
		int length = 6;
		vector<string> bad;
		bad.push_back("0 0 0 16");
		bad.push_back("6 6 5 6");
		*/
		int width,length;
		cin>>width>>length;
		vector<string> bad;
		int n;
		cin>>n;
		
		for(int i=0;i<n;i++){
			string s;
			cin>>s;
			bad.push_back(s);
		}
		cout<<numWays(width,length,bad)<<endl;
	}
	
}
