#include<iostream>
#include<vector>
using namespace std;
int num;
double * creatarray(int n){
    double *x=new double [n+1];
    for(int i=1;i<=n;i++){
        x[i]=rand()%10;
        //cin>>x[i];
    }
    return x;
}
void print_LCS(char*** b , double *x ,int i,int j,int k){
    
    if(i==0||j==0||k==0)
        return;
    if(b[i][j][k]=='A'){
        print_LCS(b,x,i-1,j-1,k-1);
        num++;
        cout<<x[i]<<" ";
    }
    else if(b[i][j][k]=='B'){
        print_LCS(b,x,i-1,j,k);
    }
    else if(b[i][j][k]=='C'){
        print_LCS(b,x,i,j-1,k);
    }
    else{
        print_LCS(b,x,i,j,k-1);
    }
}
void LCS(double*x ,int m, double *y,int n,double*z , int q){
    char ***b=new char**[m+1];
    int max=-1;
    for(int i=0;i<=m;i++){
        b[i]=new char*[n+1];
        for(int j=0;j<=q;j++){
            b[i][j]=new char[q+1];
        }
    }
    int***C=new int**[m+1];
    for(int i=0;i<=m;i++){
        C[i]=new int*[n+1];
        for(int j=0;j<=q;j++)
            C[i][j]=new int[q+1];
    }
    for(int i=0;i<=m;i++)
        C[i][0][0]=0;
    for(int i=0;i<=n;i++)
        C[0][i][0]=0;
    for(int i=0;i<=n;i++)
        C[0][0][i]=0;

    for(int i=1;i<=m;i++){
        for(int j=1;j<=n;j++){
            for(int k=1;k<=q;k++){
                if(x[i]==y[j]&&y[j]==z[k]){
                    C[i][j][k]=C[i-1][j-1][k-1]+1;
                    b[i][j][k]='A';
                    if(C[i][j][k]>max){
                        max=C[i][j][k];
                    }
                }
                else if(C[i-1][j][k]>=C[i][j-1][k] && C[i-1][j][k]>=C[i][j][k-1]){
                    C[i][j][k]=C[i-1][j][k];
                    b[i][j][k]='B';
                }
                else if(C[i][j-1][k]>=C[i-1][j][k] && C[i][j-1][k]>=C[i][j][k-1]){
                    C[i][j][k]=C[i][j-1][k];
                    b[i][j][k]='C';
                }
                else{
                    C[i][j][k]=C[i][j][k-1];
                    b[i][j][k]='D';
                }
            }
        }
    }
    vector<double> v;
    
    //cout<<max<<endl;
    for(int i=1;i<=m;i++){
        for(int j=1;j<=n;j++){
            for(int k=1;k<=q;k++){
                bool flag=0;
        		if( C[i][j][k] == max && b[i][j][k]=='A' && x[i]!=x[m]){
                    for(int l=0;l<v.size();l++){
                        if(x[i]==v[l]){
                            flag = 1;
                            break;
                        }
                    }
                    if(flag==0){
                        v.push_back(x[i]);
                        num=0;
					    print_LCS(b, x, i, j, k);
        			    cout << endl ;
                    }
				}	
        	}
        }
	}
    
}
int main(){
    int n1,n2,n3;
    cout<<"Please input the length of three sequences (1~100) : \n";
    cin>>n1>>n2>>n3;
    double *x = creatarray(n1);
    double *y = creatarray(n2);
    double *z = creatarray(n3);
    cout<<"X : ";
    for(int i=1;i<=n1;i++){
        cout<<x[i]<<" ";
    }
    cout<<"\n";
    cout<<"Y : ";
    for(int i=1;i<=n2;i++){
        cout<<y[i]<<" ";
    }
    cout<<"\n";
    cout<<"Z : ";
    for(int i=1;i<=n3;i++){
        cout<<z[i]<<" ";
    }
    cout<<"\n";
    cout<<"Longest Common Subsequence W : \n";
    LCS(x,n1,y,n2,z,n3);
    cout<<"\n";
    cout<<"Length of W : "<<num<<"\n";
}
