#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

int min(int x1, int x2, int x3) { return min(min(x1, x2), x3); }
 
int min_operations(string s1, string s2, int l1, int l2){
    int dp[l1 + 1][l2 + 1];

    for (int i = 0; i <= l1; i++) {
        for (int j = 0; j <= l2; j++) {
           
            if (i == 0)
                dp[i][j] = j; 
 
            else if (j == 0)
                dp[i][j] = i; 
 
            else if (s1[i - 1] == s2[j - 1])
                dp[i][j] = dp[i - 1][j - 1];
            else
                dp[i][j]
                    = 1 + min(dp[i][j - 1], dp[i - 1][j], dp[i - 1][j - 1]); 
        }
    }
    return dp[l1][l2];
}


string lcs( string t1, string t2, int l1, int l2 )
{
    if (l1 == 0 || l2 == 0)
        return "";
    if (t1[l1-1] == t2[l2-1])
        return  lcs(t1, t2, l1-1, l2-1) + t2[l2-1];
    else{
        string s1 = lcs(t1, t2, l1, l2-1);
        string s2 = lcs(t1, t2, l1-1, l2);
        if(s1.length() >= s2.length()) return s1;
        else return s2;
    }
}

vector<pair<string,string>> closestring(vector<string> t,string s){
    vector<pair<string,string>> temp1;
    int n = t.size();
    string lca = lcs(s,t[0],s.length(),t[0].length());
    int max_lca = lca.length(); 
    for(int i=1;i<n;i++){
        string lca = lcs(s,t[i],s.length(),t[i].length());
        int lcw = lca.length();
        if(max_lca < lcw){
            max_lca = lcw;
            continue;
        }
    }
    for(int i=0;i<n;i++){
        string lca = lcs(s,t[i],s.length(),t[i].length()); 
        int lcd = lca.length();
        if(max_lca == lcd){
            pair<string,string> A;
            A.first = t[i];
            A.second = lca;
            temp1.push_back(A);
        }       
    }
    return temp1;
}
int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    vector<string>S,D;
    int s;
    cin>>s;
    string t;
    while(s--){
        cin>>t;
        S.push_back(t);
    }   
    int d;
    cin>>d;
    while(d--){
        cin>>t;
        D.push_back(t);
    }
    int i,j,min_op;
    vector<string> temp;
    
    for(i=0;i<S.size();i++){
        min_op = min_operations(S[i],D[0],S[i].length(),D[0].length());
        for(j=1;j<D.size();j++){
            int op = min_operations(S[i],D[j],S[i].length(),D[j].length());
            if(min_op > op){
                min_op = op;
            }
        }
        for(j=0;j<D.size();j++){
            int op = min_operations(S[i],D[j],S[i].length(),D[j].length());
            if(min_op == op){
                temp.push_back(D[j]);
            }
        }
        if(temp.size() == 1){
            cout<<S[i]<<endl;
            cout<<temp[0]<<endl;
            string lca_string = lcs(S[i],temp[0],S[i].length(),temp[0].length());
            if(lca_string == ""){
                cout<<"EMPTY"<<endl;
            }
            else cout<<lca_string<<endl;
            cout<<min_op<<endl;
        }
        else if(temp.size() > 1){
            vector<pair<string,string>> tempclose = closestring(temp,S[i]);
            int n= tempclose.size();
            for(int k=0;k<n;k++){
                cout<<S[i]<<endl;
                cout<<tempclose[k].first<<endl;
                if(tempclose[k].second == ""){
                    cout<<"EMPTY"<<endl;
                }
                else cout<<tempclose[k].second<<endl;
                cout<<min_op<<endl;
            }
            tempclose.clear();
        }
        temp.clear();
    }
    return 0;
}
