#include<iostream>
#include<algorithm> 
#include<vector>
#include<bits/stdc++.h>

using namespace std;


int main(){

vector<vector<int>> vect{{3,6},{17,15},{13,15},{16,12},{9,1},{2,7},{10,19}};

 int n=vect.size();

cout<< " Original matrix "<<endl;

for(int i=0;i<n;i++){
	for(int j=0;j<2;j++)
		cout<< vect[i][j] << " ";
	cout<<endl;

}

sort(vect.begin(),vect.end());

cout<< "Sort by x axis  "<<endl;

for(int i=0; i<n;i++){
	for(int j=0; j<2;j++)
		cout<< vect[i][j]<<" ";
	cout<<endl;
	}

// " swap" 

for(int i=0; i<n;i++)
	swap(vect[i][0],vect[i][1]);


cout<< " sort by y axis" << endl;

sort(vect.begin(),vect.end());

for(int i=0;i<n;i++)
	swap(vect[i][0],vect[i][1]);

 /// Display the sorted version by y axis 
for(int i=0; i<n; i++){
	for(int j=0;j<2; j++)
		cout<<vect[i][j] << " "; 
	cout<<endl;
	}

return 0;

}
