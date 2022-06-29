#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

class node{
    public:
    int val;
    node *next;
    
    node(){
        next = NULL;
    }
    
    node(int a){
        val = a;
        next = NULL;
    }
};

class stack{
    public:
    stack(){
        top = NULL;
    }
    void push(int x){
        node *newnode = new node(x);
        newnode->next = top;
        top = newnode;
    }
    int pop(){
        node *del;
        if(top == NULL){
            return -1;
        }
        del = top;
        int r = del->val;
        top = top->next;
        free(del);
        return r;
    }
    int Top(){
        if(top == NULL){
            return -1;
        }
        else {
            int r = top->val;
            return r;
        }
    }
    int isempty(){
        if(top == NULL) return 1;
        else return 0;
    }
    node *top;
};

class graph{
    public:
    graph(int n){
        this->n = n;
        a = new int*[n];
        for(int i=0;i<n;i++){
            a[i] = new int[n];
        }
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                a[i][j] = 0;
            }
        }
    }
    
    void operator +=( pair<int,int> A){
        a[A.first][A.second] = 1;
        a[A.second][A.first] = 1;
    }

    void operator -=(pair<int,int> A){
        a[A.first][A.second] = 0;
        a[A.second][A.first] = 0;
    }  

    friend ostream& operator <<(ostream &s,graph g);

    int dfsbe(int u,int*visited,int p){
        visited[u] = 1;
        for(int v=0;v<n;v++){
            if(a[u][v] == 1){
                if(visited[v] != 1){
                    if(dfsbe(v,visited,u) == 1){
                        return 1;
                    }
                }
                else if(v != p) return 1;
            }
        }
        return 0;
    }
    int detectcycle(){
        int visited[n];
        for(int i=0;i<n;i++) visited[i] = 0;
        for(int u=0;u<n;u++){
            if(visited[u]!=1){
                if(dfsbe(u,visited,-1) == 1){
                    return 1;
                }
            }
        }
        return 0;
    }
    int reach(int u,int v){
        int visited[n];
        for(int i=0;i<n;i++) visited[i] = 0;
        stack st;
        st.push(u);
        while(!st.isempty()){
            int x = st.pop();
            if(x == v) return 1;
            visited[x] = 1;
            for(int j=0;j<n;j++){
                if(a[x][j] == 1){
                    if(visited[j]==0){
                        st.push(j);
                    }
                }
            }
        }
        return 0;
    }
    private:
    int **a;
    int n;
};
ostream& operator <<(ostream&s,graph g){
    for(int i=0;i<g.n;i++){
        for(int j=0;j<g.n;j++){
            s <<g.a[i][j]<<" ";
        }
        s<<endl;
    }
    return s;
}

int main() {
    int q;
    cin>>q;
    stack s;
    while(q--){
        string str;
        cin>>str;
        if(str == "push"){
            int in;
            cin>>in;
            s.push(in);
        }
        else if(str == "pop"){
            int r = s.pop();
            cout<<r<<endl;
        }
        else if(str == "top"){
            int r = s.Top();
            cout<<r<<endl;
        }
        else if(str == "empty"){
            int r = s.isempty();
            cout<<r<<endl;
        }
    }  
    int n,m;
    cin>>n;
    graph g(n);
    cin>>m;
    while(m--){
        string str;
        cin>>str;
        if(str == "add"){
            int u,v;
            cin>>u>>v;
            pair<int,int>A(u,v);
            g+=A;
        }
        else if(str == "del"){
            int u,v;
            cin>>u>>v;
            pair<int,int>A(u,v);
            g-=A;
        }
        else if(str == "cycle"){
            int r = g.detectcycle();
            cout <<r<<endl;
        }
        else if(str == "print"){
            cout<<g;
        }
        else if(str == "reach"){
            int u,v;
            cin>>u>>v;
            int r = g.reach(u,v);
            cout<<r<<endl;
        }
    }
    return 0;
}
