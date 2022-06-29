#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

template<typename T>
class node{
    public:
    T val;
    node<T> *left,*right;
    
    node(){
        left = right = NULL;
    }
    
    node(T a){
        val = a;
        left = right = NULL;
    }
};
template<typename T>
class dll {
    public:
    dll(){
        front = back = NULL;
        s = 0;
    }
    
    void push_front(T a){
        node<T> *temp = new node<T>(a);
        if(front == NULL && back == NULL){
            back = front = temp;
            temp->left = temp->right = NULL;
            s++;
            return;
        }
        temp->right = front;
        front->left = temp;
        temp->left = NULL;
        front = temp;
        s++;
    }
    
    void push_end(T a){
        node<T> *temp = new node<T>(a);
        if(front == NULL && back == NULL){
            back = front = temp;
            temp->left = temp->right = NULL;
            s++;
            return;
        }
        temp->left = back;
        back->right = temp;
        temp->right = NULL;
        back = temp;
        s++;
    }
    
    T pop_front(){
        T del;
        node<T> *de;
        if(front == NULL && back == NULL){
            exit(0);
        }
        if(front == back){
            de = front;
            del = de->val;
            front = back = NULL;
            s--;
            delete de;
            return del;
        }
        de = front;
        front->right->left = NULL;
        front = front->right;
        del = de->val;
        delete de;
        s--;
        return del;
    }
    
    T pop_end(){
        node<T> *de;
        T del;
        if(front == NULL && back == NULL){
            exit(0);
        }
        if(front == back){
            de = front;
            del = de->val;
            front = back = NULL;
            s--;
            delete de;
            return del;
        }
        de = back;
        back->left->right = NULL;
        back = back->left;
        del = de->val;
        delete de;
        s--;
        return del;
    }
    
    int size(){
        return s;
    }
    
    private:
    node<T> *front ,*back ;
    int s;
};

template<typename T>
class stack{
    public:
    void push(T a){
        st.push_front(a);
    }
    
    T pop(){
        return st.pop_front();
    }
    
    T top(){
         T r = st.pop_front();
         st.push_front(r);
         return r;
    }
    
    int size(){
        int s = st.size();
        return s;
    }
    
    bool compare(T n){
        T t = st.pop_front();
        st.push_front(t);
        
        if(n > t) return true;
        else return false;
    }
    
    private:
    dll<T> st;
};
template<typename T>
void encrypt(stack<T> s,int n, T *a){
    int i=n;
    while(i--){
        
        T in;
        in = a[n-i-1];
        
        if(s.size() == 0){
            s.push(in);
        }
        
        else if(s.compare(in)){
            s.push(in);
            
        }
        
        else{
            while(s.size()!=0 && s.compare(in) == false){
                cout<<s.pop();
            }
            s.push(in);
        }
    }
    
    while(s.size()!=0){
        cout<<s.pop();
    }
}
int main(){
    int n;
    char op;
    cin>>n>>op;
    if(op == 'I'){
        int a[n];
        for(int i=0;i<n;i++) cin>>a[i];
        stack<int> st;
        encrypt(st,n,a);
    }
    if(op == 'C'){
        char a[n];
        for(int i=0;i<n;i++) cin>>a[i];
        stack<char> st;
        encrypt(st,n,a);
    }
    if(op == 'F'){
        float a[n];
        for(int i=0;i<n;i++) cin>>a[i];
        stack<float> st;
        encrypt(st,n,a);
    }        
    return 0;
}
