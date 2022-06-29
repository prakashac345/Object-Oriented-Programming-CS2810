#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include<map>
#include<set>
using namespace std;

class dictionary{
    private:
    map<int,set<string>>m;
    public:
    void builtdict(vector<string>words){
        for(auto it:words){
            int k=it.length();
            m[k].insert(it);
        }
    }
    void addwordtodict(string word){
        int k = word.length();
        m[k].insert(word);
    }
    bool search(string target){
        int k=target.length();
        if(m[k].find(target)!=m[k].end()) return true;
        else return false;
    }
    set<string> getwordsafterreplace(string target){
        int k = target.length();
        set<string>::iterator it;
        set<string> r;
        for(it=m[k].begin();it!=m[k].end();it++){
            int cnt=0;
            string s = *it;
            for(int i=0;i<k;i++){
                if(s[i]!=target[i]){
                    cnt++;
                }
            }
            if(cnt==1 || cnt==0) r.insert(s);
        }
        return r;
    }
    set<string> getwordsafterswap(string target){
        int k = target.length();
        set<string>::iterator it;
        set<string> r;
        for(it=m[k].begin();it!=m[k].end();it++){
            string s = *it;
            for(int i=0;i<k-1;i++){
                string b = target;
                swap(b[i],b[i+1]);
                if(s==b) r.insert(b);
            }
        }
        return r;
    }
    int maxchangeableword(){
        long unsigned int max=0;
        for(auto it=m.begin();it!=m.end();it++){
            set<string> s = it->second;
            for(auto itr=s.begin();itr!=s.end();itr++){
                set<string> t = getwordsafterreplace(*itr);
                if(t.size()>max){
                    max = t.size();
                }
            }
        }
        return max-1;
    }

    int maxswappableword(){
        long unsigned int max=0;
        for(auto it=m.begin();it!=m.end();it++){
            set<string> s = it->second;
            for(auto itr=s.begin();itr!=s.end();itr++){
                set<string> t = getwordsafterswap(*itr);
                if(t.size()>max){
                    max = t.size();
                }
            }
        }
        return max;
    }    
    
};

int main() {
    dictionary d;
    vector<string> s;
    int n;
    cin>>n;
    for(int i=0;i<n;i++){
        string str;
        cin>>str;
        s.push_back(str);
    }
    d.builtdict(s);
    int q;
    cin>>q;
    while(q--){
        int op;
        cin>>op;
        if(op==1){
            string s;
            cin>>s;
            d.addwordtodict(s);
        }
        else if(op==2){
            string s;
            cin>>s;
            bool b = d.search(s);
            if(b == true) cout<<"true"<<endl;
            else cout<<"false"<<endl;
        }
        else if(op==3){
            string s;
            cin>>s;
            set<string> r = d.getwordsafterreplace(s);
            if(r.size()==0) cout<<-1<<endl;
            else {
                for(auto it = r.begin();it!=r.end();it++){
                    cout<<*it<<" ";
                }
                cout<<endl;
            } 
        }
        else if(op==4){
            string s;
            cin>>s;
            set<string> r = d.getwordsafterswap(s);
            if(r.size()==0) cout<<-1<<endl;
            else {
                for(auto it = r.begin();it!=r.end();it++){
                    cout<<*it<<" ";
                }
                cout<<endl;
            }             
        }
        else if(op==5){
            int k = d.maxchangeableword();
            cout<<k<<endl;
        }
        else if(op==6){
            int k = d.maxswappableword();
            cout<<k<<endl;
        }
    }
    return 0;
}