#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;


int maxpower(vector<int> p,int n){
    int dp[n+1][n+1];

    for(int i=0;i<=n;i++){
      for(int j=0;j<=n;j++){
        dp[i][j] = 0;
      }
    }
    for(int size = 1;size<=n;size++){
        for(int i=1;i+size<=n+1;i++){
            int j = i+size;
            if(i == j) dp[i][j] = p[i-1]*p[i]*p[i+1];
            else if( j == i+1)dp[i][j] = max(p[i],p[j]) + p[i]*p[j];
            for(int k = i+1;k<j;k++){
                dp[i][j] = max(dp[i][j],dp[i][k]+dp[k][j] + p[i]*p[k]*p[j] + p[i]*p[j] + max(p[i],p[j]) - p[i]*p[k] - max(p[i],p[k]) - p[k]*p[j] -max(p[k],p[j]));
            }
        }
    }
    return dp[1][n];
}
int main() {
    int n;
    cin>>n;
    vector<int> stones;
    int t;
    stones.push_back(1);
    for(int i=0;i<n;i++){
        cin>>t;
        stones.push_back(t);
    }
    stones.push_back(1);
    int PT;
    cin>>PT;
    int ans = maxpower(stones,n);
    if(ans >= PT ) {
        cout<<ans<<endl;
        cout<<"YES";
    }
    else{
        cout<<ans<<endl;
        cout<<"NO";
    }
    return 0;
} 