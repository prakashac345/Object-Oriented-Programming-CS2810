#include <bits/stdc++.h>
#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

class book{
    public:
    string title,author;
    int year,price;
    book *link;
};

//function overriding is used
class bookshelf{
    public:
    book *front,*back;
    bookshelf(){
        front = NULL;
        back = front;
    }
     void addbook(book );
     void removebook();
    bool checkempty(){
        if(front == NULL){
            return true;
        }
        return false ;
    }
     void list();
     void findcheap();
     void reverseunique();
};

//simialr to how stack ADT is implemented 
class verticalbookshelf : public bookshelf{
    public:
    verticalbookshelf() {front = NULL; back = front;}
    void addbook(book b){
        book *nbook = new book();
        nbook->author = b.author;
        nbook->title = b.title;
        nbook->price = b.price;
        nbook->year = b.year;
        nbook->link = front;
        front = nbook;
    }

    void removebook(){
        book *temp;
        if(front == NULL){
            cout<<"e"<<endl; 
        }
        else{
            temp = front;
            front = front->link;
            free(temp);
        }
    }

    void list(){
        book *temp;
        if(front == NULL){
            cout<<"e"<<endl;
            return;
        }
        else {
            temp = front;
            while(temp != NULL){
                cout << temp->title <<","<< temp->author <<","<<temp->year<<","<<temp->price<<endl;
                temp = temp->link;
            }
        }
    }

    void findcheap(){
        if(front == NULL)
        {
            cout<<"e"<<endl;
            return;
        }
        int min;
        book *temp = front;
        min = temp->price;
        while(temp != NULL){
            if(min < temp->price) cout<<min;
            else {
                cout<<-1;
                min = temp->price;
            }
            if(temp->link != NULL) cout<<",";
            temp = temp->link;
        }
        cout<<endl;
    }

    void reverseunique(){
        book b;
        verticalbookshelf v1;     
        book *temp = front, *temp1;
        while(temp!=NULL && temp->link!=NULL){
            temp1 = temp;
            while(temp1->link!=NULL){
                if(temp->author == temp1->link->author && temp->title == temp1->link->title
                 && temp->price == temp1->link->price && temp->year == temp1->link->year ){
                     book * duplicate = temp1->link;
                     temp1->link = temp1->link->link;
                     free(duplicate);
                }
                else temp1 = temp1->link;
            }
            temp = temp->link;
        }
        book *rev = front;
        while(rev!=NULL){
            b.author = rev->author;
            b.title = rev->title;
            b.price = rev->price;
            b.year = rev->year;
            rev = rev->link;
            v1.addbook(b);
            removebook();
        }
        front = v1.front;
        back = v1.back;
    }
};

//similar to how queue ADT is implemented 
class horizontalbookshelf : public bookshelf{
    public:
    horizontalbookshelf(){ front = NULL; back = NULL;}
    void addbook(book b){
        book *nbook = new book();
        nbook->author = b.author;
        nbook->title = b.title;
        nbook->price = b.price;
        nbook->year = b.year;
        if(back == NULL){
            front = back = nbook;
            return;
        }     
        back->link = nbook;
        back = nbook;
    }

    void removebook(){
        book *temp;
        if(front == NULL){
            cout <<"e"<<endl;
        }
        else {
            temp = front ;
            front = front->link;
            if(front == NULL) back = NULL;
            delete temp;
        }
    }

    void list(){
        book *temp;
        if(front == NULL){
            cout <<"e"<<endl;
            return;
        }
        else {
            temp = front;
            while(temp != NULL){
                cout << temp->title <<","<< temp->author <<","<<temp->year<<","<<temp->price<<endl;
                temp = temp->link;                
            }
        }
    }

    void findcheap(){
        if(front == NULL)
        {
            cout<<"e"<<endl;
            return;
        }
        int min;
        book *temp = front;
        min = temp->price;
        while(temp != NULL){
            if(min < temp->price) cout<<min;
            else {
                cout<<-1;
                min = temp->price;
            }
            if(temp->link != NULL) cout<<",";
            temp = temp->link;
        }
        cout<<endl;
    }
    
    void reverseunique(){
        book b;
        horizontalbookshelf h1;  
        verticalbookshelf v2;   
        book *temp = front, *temp1;
        while(temp!=NULL && temp->link!=NULL){
            temp1 = temp;
            while(temp1->link!=NULL){
                if(temp->author == temp1->link->author && temp->title == temp1->link->title
                 && temp->price == temp1->link->price && temp->year == temp1->link->year ){
                     book * duplicate = temp1->link;
                     temp1->link = temp1->link->link;
                     free(duplicate);
                }
                else temp1 = temp1->link;
            }
            temp = temp->link;
        }
        book *rev = front;
        while(rev!=NULL){
            b.author = rev->author;
            b.title = rev->title;
            b.price = rev->price;
            b.year = rev->year;
            rev = rev->link;
            v2.addbook(b);
            removebook();
        }
        book *rev2 = v2.front;
        while(rev2 != NULL){
            b.author = rev2->author;
            b.title = rev2->title;
            b.price = rev2->price;
            b.year = rev2->year;
            rev2 = rev2->link;
            h1.addbook(b);
            v2.removebook();
        }
        front = h1.front;
        back = h1.back;        
    }
};

int main() {  
    int q;
    book b;
    verticalbookshelf v;
    horizontalbookshelf h;
    cin>>q;
    while(q--){
        string s;
        cin>>s;
        if(s == "ADD"){
            char op;
            cin>>op;
            cin>>b.title>>b.author>>b.year>>b.price;
            if(op == 'v') v.addbook(b);
            else h.addbook(b);
        }
        
        else if(s == "REMOVE"){
            int n;
            cin>>n;
            char op;
            cin>>op;
            if(op == 'v'){
                while(n--){
                    v.removebook();
                }
            }
            else {
                while(n--){
                    h.removebook();
                }
            }
        }

        else if(s == "LIST"){
            char op;
            cin>>op;
            if(op == 'v'){
                v.list();
            }
            else h.list();
        }

        else if(s == "FINDC"){
            char op;
            cin>>op;
            if(op =='v'){
                v.findcheap();
            }
            else h.findcheap();
        }
        else if(s == "REVUNI"){
            char op;
            cin>>op;
            if(op == 'v'){
                v.reverseunique();
            }
            else h.reverseunique();
        }
    }
    return 0;
}