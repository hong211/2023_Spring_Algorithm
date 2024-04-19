#include<iostream>
using namespace std;
bool choice=0;
int memoized_cut_rod_aux(int *price,int n,int* r,int *s){
    if(!choice && r[n]>=0)
        return r[n];
    else if(choice && r[n]!=INT32_MAX)
        return r[n];
    else{
        int q=choice?INT32_MAX:-INT32_MAX;
        for(int i=n;i>=1;i--){
            if(i<=10){
                if(choice==0 && price[i]+memoized_cut_rod_aux(price,n-i,r,s)>q){
                    q=price[i]+memoized_cut_rod_aux(price,n-i,r,s);
                    s[n]=i;
                }
                else if(choice==1 && price[i]+memoized_cut_rod_aux(price,n-i,r,s)<q){
                    q=price[i]+memoized_cut_rod_aux(price,n-i,r,s);
                    s[n]=i;
                }
            }
        }
        r[n]=q;
        return q;
    }
}
int memoized_cut_rod(int* price,int n,int*s){
    int *r=new int [n+1];
    r[0]=0;
    for(int i=1;i<=n;i++){
        r[i]=choice?INT32_MAX:-INT32_MAX;
    }
    return memoized_cut_rod_aux(price,n,r,s);
}
int extended_bottom_up_cut_rod(int* price,int n,int *s){
    int *r=new int[n+1];
    r[0]=0;
    for(int i=1;i<=n;i++){
        int q=choice?INT32_MAX:-INT32_MAX;
        for(int j=i;j>=1;j--){
            if(j<=10){
                if(choice==0 && q<price[j]+r[i-j]){
                    q=price[j]+r[i-j];
                    s[i]=j;
                }
                else if(choice==1 && q>price[j]+r[i-j]){
                    q=price[j]+r[i-j];
                    s[i]=j;
                }
            }
           
        }
        r[i]=q;
        
    }
    return r[n];
}
int main(){
    int n;
    cout<<"please input total length: ";
    cin>>n;
    cout<<"please input the price corresponding to length 1~10 : "<<endl;
    int price[11];
    int *s=new int[n+1];
    for(int i= 1 ;i<=10;i++){
        cin>>price[i];
    }
    int k=memoized_cut_rod(price,n,s);
    int num=0;
    cout<<"-----Top Down:-----\n";
    cout<<"total length:"<<n<<"\n";
    cout<<"maximum price:"<<k<<"\n";
    int n1=n;
    while(n1>0){
        cout<<s[n1]<<" ";
        n1-=s[n1];
        num++;
    }
    cout<<"\nnumber of pieces: "<<num<<"\n\n";

    choice=1;
    k=memoized_cut_rod(price,n,s);
    num=0;
    cout<<"mininum price:"<<k<<"\n";
    n1=n;
    while(n1>0){
        cout<<s[n1]<<" ";
        n1-=s[n1];
        num++;
    }
    cout<<"\nnumber of pieces: "<<num<<"\n\n";

    choice=0;
    k=extended_bottom_up_cut_rod(price,n,s);
    num=0;
    cout<<"-----Bottom up:-----\n";
    cout<<"total length:"<<n<<"\n";
    cout<<"maxinum price:"<<k<<"\n";
    n1=n;
    while(n1>0){
        cout<<s[n1]<<" ";
        n1-=s[n1];
        num++;
    }
    cout<<"\nnumber of pieces: "<<num<<"\n\n";

    choice=1;
    k=extended_bottom_up_cut_rod(price,n,s);
    num=0;
    cout<<"mininum price:"<<k<<"\n";
    n1=n;
    while(n1>0){
        cout<<s[n1]<<" ";
        n1-=s[n1];
        num++;
    }
    cout<<"\nnumber of pieces: "<<num<<"\n\n";
}
