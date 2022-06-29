#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

class base{
    public:
    int n;
    int opvalue;
    virtual void dpfunction(int W, int n,int r[], int wt[]) {return;}
};
class dpi : public base {
    public:
    void dpfunction(int W, int n,int r[], int wt[]){
        int dp[W+1];
        memset(dp, 0, sizeof dp);
        for (int i=1; i<=W; i++){
            for (int j=0; j<n; j++){
                if (wt[j] <= i) dp[i] = max(dp[i], dp[i-wt[j]] + r[j]);
            }
        }
        opvalue = dp[W];     
    }
};
int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */  
    int w;
    base b;
    cin>>w>>b.n;
    int r[b.n],wt[b.n];
    for(int i=0;i<b.n;i++){
        cin>>r[i];
    } 
    for(int i=0;i<b.n;i++){
        cin>>wt[i];
    }     
    dpi d;
    d.dpfunction(w,b.n,r,wt);
    cout<<d.opvalue<<endl;
    return 0;
}
