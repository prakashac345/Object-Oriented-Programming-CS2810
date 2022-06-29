#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <string>

using namespace std;

class node{
    public:
    
    node(){
        isEnd = false;
        for(int i=0;i<26;i++){
            next.push_back(NULL);
        }
    }
    
    void send(){
        isEnd=true;
    }

    bool present(int k){
        if(next[k] == NULL){
            return false;
        }
        else return true;
    }

    node* get(int k){
        return next[k];
    }

    void put(int k,node* p){
        next[k] = p;
    }

    bool end(){
        return isEnd;
    }

    private:
    bool isEnd = false;
    vector<node*> next; 
};
class Trie{
    public:
    node *root;
    Trie(){
        root = new node();
    }

    void insert(string word){
        node *current = root;
        for(long unsigned int i=0;i<word.length();i++){
            int no = (word[i]-'a');
            if(!current->present(no)){
                node *p1 = new node();
                current->put(no,p1);
            }
            node *p2 = current->get(no);
            current = p2;
        }
        current->send();
    }

    string search(string word){
        node *current = root;
        string prefix2 = "\0";
        string prefix1 = "\0";
        int flag =0;
        for(long unsigned int i=0;i<word.length();i++){
            int no = (word[i]-'a');
           if(current->end()){
               flag = 1;
               prefix1 = prefix2; 
           }
           if(current->present(no)){
               prefix2+=word[i];
           }
           else break;

           node *p2 = current->get(no);
           current = p2;
        }
        
        if(flag == 1){
            return prefix1;
        }
        
        if(!current->end()){
            return word;
        }
        return prefix2;
    }
};

int main() {
    Trie t;
    int p;
    cin>>p;
    string prefix[p];
    for(int i=0;i<p;i++){
        cin>>prefix[i];
        t.insert(prefix[i]);
    }
    int n;
    cin>>n;
    string word[n];
    for(int i=0;i<n;i++){
        cin>>word[i];
    }

    for(int i=0;i<n;i++){
            string s = t.search(word[i]);
            word[i] = s;
    }
    for(int i=0;i<n;i++){
        cout<<word[i]<<" ";
    }
    return 0;
}
