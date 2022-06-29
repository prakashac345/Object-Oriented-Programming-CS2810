#include <iostream>

using namespace std;

template<typename T>
class node{
    public:
    T val;
    node<T> *next;
    
    node(){
        next = NULL;
    }
    
    node(T a){
        val = a;
        next = NULL;
    }
};

template<typename T>
class queue{
    public:
    queue(){
        front = back = NULL;
        s=0;
    }
    void enqueue(T a){
        node<T> *temp = new node<T>(a);
        if(back == NULL){
            front = back = temp;
            s++;
            return;
        }
        back->next = temp;
        back = temp;
        s++;
    }
    
    T dequeue(){
        T del;
        node<T> *de;
        if(front == NULL){
            exit(0);  
        }
        de = front;
        front = front->next;
        s--;
        if(front == NULL) back = NULL;
        del = de->val;
        delete(de);
        return del;
    }
    
    int size(){
        return s;
    }

    bool isempty(){
        if(front == NULL || back == NULL) return true;
        else return false ;
    }
    private:
    node<T> *front,*back;
    int s;
};

template<typename T>
class printer{
    public:
    class insufficientink{
        public:
        insufficientink(string st){
            cout<<st<<endl;
        }
    };
    class printbusy{
        public:
        printbusy(string st){
            cout<<st<<endl;
        }
    };
    class nodocument{
        public:
        nodocument(string st){
            cout<<st<<endl;
        }        
    };
    printer(int c, int i){
        capacity = c;
        ink = i;
    }
    void adddocument(T d){
        if(q.size() == capacity){
            throw printbusy("PRINTER_BUSY");
        }
        q.enqueue(d);
    }
    T printdocument(){
        if(q.isempty()){
            throw nodocument("NO_DOCUMENT");
        }
        if(ink==0){
            throw insufficientink("INSUFFICIENT_INK");
        }        
        T temp = q.dequeue();
        ink--;
        return temp;
    }
    void fillink(int ink){
        this->ink = ink;
    }
    private:
    queue<T> q;
    int capacity;
    int ink;
};

int main(){
    int m,n,Q;
    char op;
    cin>>m>>n>>op;
    if(op == 'I'){
        printer<int>p(m,n);
        cin>>Q;
        int i=Q;
        while(i--){
            int oc;
            cin>>oc;
            if(oc == 1){
                int in;
                cin>>in;
                try{
                    p.adddocument(in);
                }
                catch(printer<int>::printbusy){
                   
                }
            }
        
            else if(oc == 2){
                try{
                    int t=p.printdocument();
                    cout<<t<<endl;
                }
                catch(printer<int>::nodocument){
                    
                }
                catch(printer<int>::insufficientink){
                    
                }
            }
        
            else{
                int ik;
                cin>>ik;
                p.fillink(ik);
            }
        }  
         
    }
    if(op == 'C'){
        printer<char> p(m,n);
        cin>>Q;
        int i=Q;
        while(i--){
            int oc;
            cin>>oc;
            if(oc == 1){
                char in;
                cin>>in;
                try{
                    p.adddocument(in);
                }
                catch(printer<char>::printbusy){
                
                }
            }
        
            else if(oc == 2){
                try{
                    char t = p.printdocument();
                    cout<<t<<endl;
                }
                catch(printer<char>::nodocument){
                
                }
                catch(printer<char>::insufficientink){
               
                }
            }
        
            else{
                int ik;
                cin>>ik;
                p.fillink(ik);
            }
        }
    }
    if(op == 'F'){
        printer<float> p(m,n);
        cin>>Q;
        int i=Q;
        while(i--){
            int oc;
            cin>>oc;
            if(oc == 1){
                float in;
                cin>>in;
                try{
                    p.adddocument(in);
                }
                catch(printer<float>::printbusy){
                
                }
            }
        
            else if(oc == 2){
                try{
                    float t = p.printdocument();
                    cout<<t<<endl;
                }
                catch(printer<float>::nodocument){
                
                }
                catch(printer<float>::insufficientink){
               
                }
            }
        
            else{
                int ik;
                cin>>ik;
                p.fillink(ik);
            }
        }
    }        
    return 0;
}
