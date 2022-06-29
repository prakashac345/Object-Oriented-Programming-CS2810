#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

template<typename T> 
class node{
    public:
    T key,val;
    node<T> *next = NULL,*prev = NULL,*up = NULL,*down = NULL;
    node<T>(T k , T v){
        val = v;
        key = k;
    }
};

template<typename T> 
class skiplist{
    private:
    node<T> *bottom = NULL ,*top = NULL;
    int MAXLEVEL = 10;
    int nkeys = 0;
    public:

    void imskiplist(T maxo,T mino){
        
        int loop = MAXLEVEL - 1;
        node<T> *lbptr = new node<T>(mino, mino);
        node<T> *rbptr = new node<T>(maxo, maxo);
        lbptr->next = rbptr;
        rbptr->prev = lbptr;
        bottom = lbptr;
        while(loop--){
            node<T> *ltemp = new node<T>(mino, mino);
            node<T> *rtemp = new node<T>(maxo, maxo);
            lbptr->up = ltemp;
            rbptr->up = rtemp;
            ltemp->down = lbptr;
            rtemp->down = rbptr;
            ltemp->next = rtemp;
            rtemp->prev = ltemp;
            lbptr = ltemp;
            rbptr = rtemp;
        }
        top = lbptr;
    }
    int nokeys(){
        return nkeys;
    }
    
    node<T>* search(T k)
    {
        node<T> *current=top;
        while(current->down!=NULL){
            current=current->down;
        }
            if(current->next->next!=NULL){
                while(current->next->key <= k)
                {
                    if(current->next->next!=NULL)
                       current=current->next;

                    else break;  
                }
            

        }
        return current;
    }
    
        
    node<T> *searchbefore(T k,node<T> *ptr){
        node<T> *current = ptr;
        while(current->next->key<=k){
            if(current->next->next != NULL){
                current = current->next;
            }
            else break;
        }
        return current;            
    }
    
    void insert(T k, T v){
        nkeys++;
        node<T> *current = search(k);
        int n = MAXLEVEL-1;
        node<T> *level = bottom->up;
            
        if(current->key == k){
                return ;
            }
            
            else {
                node<T> *addnode = new node<T>(k,v);
                node<T> *addr = current->next;
                current->next = addnode;
                addnode->next = addr;
                addnode->prev = current;
                addr->prev = addnode;
                node<T> *utop = addnode;
                while(rand()%2!=1 && n!=0){
                    node<T> *temp = new node<T>(k,v);
                    temp->down = utop;
                    utop->up = temp;
                    node<T> *extemp = searchbefore(k,level);
                    node<T> *cl = extemp;
                    node<T> *cr = extemp->next;
                    temp->next = cr;
                    cr->prev = temp;
                    cl->next = temp;
                    temp->prev = cl;
                    level = level->up;
                    utop = temp;
                    n--;
                }
            }
        }



        void deletes(T k){
           
            node<T> *current = search(k);
            node<T> *cr,*cl;
            if(current != NULL){
                if(current->key == k){
                    nkeys--;
                    while(current != NULL){
                        node<T> *del = current;
                        cr = current->next;
                        cl = current->prev;
                        cr->prev = cl;
                        cl->next = cr;
                        current->prev = current->next = NULL;
                        current = current->up;
                        delete del;
                        }
                }
            }
        }
};

template<typename T>
class dictionary{
    public:
    skiplist<T> s;
    dictionary<T>(T a,T b){
        s.imskiplist(a,b);
    }
    void insert(T k,T v){
        s.insert(k,v);
    }
    void deleted(T k){
        s.deletes(k);
    }
    void find(T k){
        node<T>* ptr=s.search(k);
        if(ptr->next==NULL||ptr->prev==NULL) 
        {
            cout<<"NOT FOUND"<<endl;
            return;
        } 
        else if(ptr->key==k) cout<<ptr->val<<endl;
        else cout<<"NOT FOUND"<<endl;
        return;
    }
    bool empty(){
        if(s.nokeys() == 0){
            return true;
        }
        else return false;
    }

    void nofkeys(){
        cout<<s.nokeys()<<endl;
    }
};


int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    string s;
    cin>>s;
    int p;
    cin>>p;
    string op;
    int a = INT32_MIN, b = INT32_MAX;
    if(s == "INTEGERDICT"){
        dictionary<int> dt(a,b);
        while(p--){
            cin>>op;
            if(op == "ISEMPTY"){
                if(dt.empty()==true){
                    cout<<"True"<<endl;
                }
                else {
                    cout<<"False"<<endl;
                }
            }
            else if(op == "INSERT"){
                int k,v;
                cin>>k>>v;
                dt.insert(k,v);
            }
            else if(op == "SIZE"){
                dt.nofkeys();
            }
            else if(op == "DELETE"){
                int k;
                cin>>k;
                dt.deleted(k);
            }
            else if(op == "FIND"){
                int k;
                cin>>k;
                dt.find(k);
            }
        }        
    }

    if(s == "STRINGDICT"){
        dictionary<string> ds("@","}");
        while(p--){
            cin>>op;
            if(op == "ISEMPTY"){
                if(ds.empty()==true){
                    cout<<"True"<<endl;
                }
                else {
                    cout<<"False"<<endl;
                }
            }
            else if(op == "INSERT"){
                string k,v;
                cin>>k>>v;
                ds.insert(k,v);
            }
            else if(op == "SIZE"){
                ds.nofkeys();
            }
            else if(op == "DELETE"){
                string k;
                cin>>k;
                ds.deleted(k);
            }
            else if(op == "FIND"){
                string k;
                cin>>k;
                ds.find(k);
            }
        }        
    }    
    return 0;
}


