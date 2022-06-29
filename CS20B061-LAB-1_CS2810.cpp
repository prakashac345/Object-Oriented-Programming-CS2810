#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

class Matrix{
    
    public:
    
    void setValue(int row,int col, int val);
    int getValue(int row,int col);
    int getNoRows();
    int getNoColumns();
    Matrix();
    Matrix(int row,int col);
    Matrix(int row,int col,int **matrix);
    int trace();
    void printSpiral();
    bool checkTriangular(); 
    bool isSpecialMatrix();
    
    private:
    
    int rows;
    int columns;
    int mat[1000][1000];
};

Matrix::Matrix(){
    rows = 0;
    columns = 0;
}

Matrix::Matrix(int row, int col){
    rows = row;
    columns = col;
    
    for (int i=0; i <rows; i++)
    {
        for (int j=0; j < columns; j++)
        {
            mat[i][j] = 0;
        }
    }
}


Matrix::Matrix(int row, int col, int **matrix){
   rows = row;
   columns = col;

    for (int i=0; i <rows; i++)
    {
        for (int j=0; j < columns; j++)
        {
            mat[i][j] = *(*(matrix+i)+j);
        }
    }
}

void Matrix::setValue(int row, int col, int val){
    mat[row-1][col-1] = val;
}

int Matrix::getValue(int row,int col){
    int val = mat[row-1][col-1];
    return val;
}

int Matrix::getNoRows(){
    return rows;
}

int Matrix::getNoColumns(){
    return columns;
}

int Matrix::trace(){
    int sum=0;
    if(rows != columns) return -1;
    
    else {
        for(int i=0;i<rows;i++){
            
            sum = sum + mat[i][i];
        }
        return sum;
    }
}

void Matrix::printSpiral(){

    int i;
    int k=0;
    int l=0;
    int m=rows, n= columns;
    while(k<m && l<n)

    {
        for(i=l;i<n;i++)  cout<<mat[k][i]<<" ";
        k++;

        for(i=k;i<m;i++)  cout<<mat[i][n-1]<<" ";
        n--;

        if(k<m){
            for(i=n-1;i>=l;--i)  cout<<mat[m-1][i]<<" ";
            m--;
        }

        if(l<n){
            for(i=m-1;i>=k;i--)  cout<<mat[i][l]<<" ";
            l++;
        }

    }

    cout<<endl;
}

bool Matrix::checkTriangular(){
    
    if(rows != columns) return false;
    
        bool l1= true, l2 =true;
        for(int i=1;i<rows;i++){
            for(int j=0;j<i;j++){
                if(mat[i][j] !=0 ) {
                    l1=false;
                    break;
                }
            }
        }
        
        for(int i=0;i<rows;i++){
            for(int j=1+i;j<columns;j++){
                if(mat[i][j]!=0){
                    l2=false;
                    break;
                }
            }
        }
        
        return (l1 || l2);
        
}

bool Matrix::isSpecialMatrix(){

        int i,j;
        bool check = true;
        long long  prevrowsum =0,prevcolsum=0;
        for(i=0;i<rows;i++) {
            prevrowsum += mat[0][i];
            prevcolsum += mat[i][0];
        }
        if(prevrowsum == prevcolsum ){
            
          for(i=0;i<rows;i++){
            long long  rowsum=0,colsum=0;
            for(j=0;j<columns;j++){
                rowsum += mat[i][j];
                colsum += mat[j][i];
            }
            if(rowsum  == colsum && rowsum == prevrowsum ){
                continue;
            }
            else{
                check = false ;
                break;
            }
          }
        }
        else check = false ;
        
        return check;
}



int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */  
    int N,M;
    int **matrix;
    
    cin>>N>>M;

    
    matrix = new int*[N];
    for(int i=0;i<N;i++){
        matrix[i] = new int[M];
    }
    
    for(int i=0;i<N;i++){
        for(int j=0;j<M;j++){
            cin>> *(*(matrix+i)+j);
        }
    }
    
    Matrix m(N,M,matrix);
    
    int q;
    cin>>q;
    
    while(q--)
    {
        int op;
        cin>>op;
        
        if(op == 2){
            int t = m.trace();
            cout<<t<<endl;
        }
        
        else if(op == 1){
            m.printSpiral();
        }
        
        else if(op == 3){
            bool c = m.checkTriangular();
            if(c) cout<<"true"<<endl;
            else cout<<"false"<<endl;
        }
        
        else if(op == 4){
            bool ch = m.isSpecialMatrix();
            if(ch) cout<<"true"<<endl;
            else cout<<"false"<<endl;
        }
        
    }
    
    //clearing memory stored in **matrix 
    for( int i = 0 ; i < m.getNoRows() ; i++ )
        delete [] *(matrix + i) ;
    delete [] matrix;
    
    return 0;
}