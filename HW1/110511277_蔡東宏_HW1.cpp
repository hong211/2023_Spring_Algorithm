#include<iostream>
#include<time.h>
using namespace std;
int *createarray(int size){
    int *data=new int [size];
    srand(time(NULL));
    for(int i=0;i<size;i++){
        data[i]=rand();
    }
    return data;
}
void merge(int *a, int start , int middle ,int end){
    int n1=middle-start+1;
    int n2=end-middle;
    int *a1=new int[n1];
    int *a2=new int[n2];
    for(int i=0;i<n1;i++){
        a1[i]=a[i+start];
    }
    for(int i=0;i<n2;i++){
        a2[i]=a[i+middle+1];
    }
    int i=0,j=0,k=start;
    while(i<n1||j<n2){
        if(i==n1){
            a[k]=a2[j];
            j++;
            k++;
        }
        else if(j==n2){
            a[k]=a1[i];
            i++;
            k++;
        }
        else if(a1[i]<a2[j]){
            a[k]=a1[i];
            i++;
            k++;
        }
        else{
            a[k]=a2[j];
            j++;
            k++;
        }
    }

}
void mergesort(int *a , int start , int end){
    int middle=(start+end)/2;
    if(start<end){
        mergesort(a,start,middle);
        mergesort(a,middle+1,end);
        merge(a,start,middle,end);
    }
}
void insertion_sort(int *a , int size){
    int temp , k;
    for(int i=1;i<size;i++){
        k=i;
        for(int j=i-1;j>=0;j--){
            if(a[j]>a[k]){
                temp=a[k];
                a[k]=a[j];
                a[j]=temp;
                k--;
            }
        }
    }
}
int main(){
    int size ;
    int *data;
    cout<<"Please cin data size(cin negative number to quit) : ";
    while(cin>>size){
        if(size<0)
            break;
        double begin,finish;
        int *data2=new int[size];
        data=createarray(size);
        /*cout<<"original data : ";
        for(int i=0;i<size;i++){
            cout<<data[i]<<" ";
            data2[i]=data[i];
        }
        cout<<"\n";*/
        begin=(double)clock();
        insertion_sort(data,size);
        finish=(double)clock();
        printf("insertion sort during time: %lfs\n", double(finish-begin)/CLOCKS_PER_SEC);
        /*cout<<"data after insertion sort : ";
        for(int i=0;i<size;i++){
            cout<<data[i]<<" ";
        }
        cout<<"\n";*/

        begin=(double)clock();
        mergesort(data2,0,size-1);
        finish=(double)clock();
        printf("merge sort during time: %lfs\n", double(finish-begin)/CLOCKS_PER_SEC);
        /*cout<<"data after merge sort : ";
        for(int i=0;i<size;i++){
            cout<<data2[i]<<" ";
        }
        cout<<"\n";*/
        cout<<"Please cin data size (cin negative number to quit) : ";
    }
}
