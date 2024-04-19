#include<iostream>
using namespace std;
void Optimal_BST(double** e, double **w, int **root, double *p, double *q, int n){
    for(int i=1;i<=n+1;i++){
        e[i][i-1]=q[i-1];
        w[i][i-1]=q[i-1];
    }
    for(int l=1;l<=n;l++){
        for(int i=1;i<=n-l+1;i++){
            int j = i+l-1;
            e[i][j]=INT16_MAX;
            w[i][j]=w[i][j-1]+p[j]+q[j];
            for(int r=i;r<=j;r++){
                double t = e[i][r-1]+e[r+1][j]+w[i][j];
                if(t<=e[i][j]){
                    e[i][j]=t;
                    root[i][j]=r;
                }
            }
        }
    }
}

void print_Optimal_BST(int **root ,int ini , int final ,int r, int n){
    if(ini>final)
        return;
    if(root[ini][final] == r){
        cout<<"Root of Tree is "<<root[ini][final]<<"\n";
    }
    else if( root[ini][final]<r){
        cout<<r<<"'s leftsubtree is  "<<root[ini][final]<<"\n";
    }
    else if(r <root[ini][final] ){
        cout<<r<<"'s rightsubtree is  "<<root[ini][final]<<"\n";
    }
    print_Optimal_BST(root ,ini , root[ini][final]-1 ,root[ini][final], n);
    print_Optimal_BST(root ,root[ini][final]+1 , final ,root[ini][final], n);
}
int main(){
    int n=9;
    double p[10]={0,0.05,0.04,0.02,0.07,0.08,0.09,0.04,0.08,0.03};
    double q[10]={0.08,0.06,0.04,0.04,0.03,0.06,0.07,0.06,0.04,0.02};
    /*int n=5;
    double p[6]={0,0.05,0.15,0.15,0.1,0.1};
    double q[6]={0.05,0.1,0.05,0.1,0.05,0.1};*/
    double**e = new double *[n+2];
    double**w = new double *[n+2];
    int**root = new int *[n+1];
    for(int i=1;i<=n+2;i++){
        e[i] = new double [n+1];
        w[i] = new double [n+1];
    }
    for(int i=1;i<=n+1;i++){
        root[i] = new int[n+1];
    }
    Optimal_BST(e,w,root,p,q,n);
    cout<<"Smallest serch cost : "<<e[1][n]<<"\n";
    cout<<"Root : "<<root[1][n]<<"\n\n";


    print_Optimal_BST(root ,1 ,n,root[1][n], n);
}