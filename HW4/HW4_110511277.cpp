#include<iostream>
#include<time.h>
#include<chrono>
using namespace std;
int *createarray(int size){
    int *data=new int [size];
    srand(time(NULL));
    for(int i=0;i<size;i++){
        data[i]=rand()%1000;
    }
    return data;
}
void swap(int &a,int &b){
    int temp=a;
    a=b;
    b=temp;
}
int partition(int *data,int p,int r){
    int x=data[r];
    int i=p-1;
    for(int j=p;j<=r-1;j++){
        if(data[j]<x){
            i++;
            swap(data[i],data[j]);
        }
    }
    swap(data[i+1],data[r]);
    return i+1;
}
int rm_partition(int* data,int p,int q){
    int i=(rand()%(p-q))+p;
    swap(data[i],data[q]);
    return partition(data,p,q);
}
void randomized_quicksort(int* data,int p,int r){
    if(p < r){
        int q = rm_partition(data,p,r);
        randomized_quicksort(data,p,q-1);
        randomized_quicksort(data,q+1,r);
    }
    else 
        return;

}
int main(){
    int size ;
    int *data;
    cout<<"Please cin data size(cin negative number to quit) : ";
    while(cin>>size){
        if(size<0)
            break;
        data=createarray(size);
        auto begin = chrono::high_resolution_clock::now(); 
        randomized_quicksort(data,0,size-1);
       
        auto finish = chrono::high_resolution_clock::now(); 
        chrono::duration<double, ratio<1, 1>> dur = chrono::duration(finish - begin);
        
        printf("randomized_quicksort sort sort during time: %lfs\n", dur.count());
        /*cout<<"data after randomized_quicksort sort : ";
        for(int i=0;i<size;i++){
            cout<<data[i]<<"\n";
        }
        cout<<"\n";*/
        cout<<"Please cin data size(cin negative number to quit) : ";
    }
}