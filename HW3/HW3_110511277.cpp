#include<iostream>
#include<time.h>
#include<chrono>
using namespace std;
class Heap {
	int* data;
	int last;
	int size;
	void reheap_up();
	void reheap_down();   
public:
	Heap(int);
	Heap();
	void insert(int);
	int delete_root();
	int* print_heap();
};
void swap(int &a, int &b) {
	int temp = a;
	a = b;
	b = temp;
}
Heap::Heap() {
}
Heap::Heap(int n) {
	data = new int[n];
	last = -1;
	size = n;
}
void Heap::insert(int n) {
	last++;
	data[last] = n;
	reheap_up();
}
void Heap::reheap_up() {
	int k = last;
	if (last != 0) {
		while (data[k] < data[(k - 1) / 2] && k > 0) {
			swap(data[k], data[(k - 1) / 2]);
			k = (k - 1) / 2;
		}
	}
}
void Heap::reheap_down() {
	int k = 0;
	if (last != 0) {
		while (last > 2*k+2) {
			if (data[2 * k + 1] > data[k] && data[2 * k + 2] > data[k]) {
				return;
			}
			else if (data[2 * k + 1] < data[k] && data[2 * k + 1]< data[2 * k + 2]) {
				swap(data[k], data[2 * k + 1]);
				k = 2 * k + 1;
			}
			else if (data[2 * k + 2] < data[k]){
				swap(data[k], data[2 * k + 2]);
				k = 2 * k + 2;
			}
		}
		if (2* k <= last) {
			if (data[2 * k + 1] < data[k]) {
				swap(data[k], data[2 * k + 1]);
			}
		}
		return;
	}
}
int Heap::delete_root() {
	int temp = data[0];
	data[0] = data[last];
	last--;
	reheap_down();
	return temp;
}
int* Heap::print_heap() {
	int *a=new int[size];
	for (int i = 0; i < size;i++) {
		a[i] = delete_root() ;
	}
    return a;
}
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
        //double begin,finish;
        int *data2=new int[size];
        int *data3=new int[size];
        data=createarray(size);
        for(int i=0;i<size;i++){
            data2[i]=data[i];
            data3[i]=data[i];
        }
        //auto begin=clock();
        auto begin = chrono::high_resolution_clock::now(); 
        insertion_sort(data,size);
        //auto finish=clock();
        auto finish = chrono::high_resolution_clock::now(); 
        chrono::duration<double, ratio<1, 1>> dur = chrono::duration(finish - begin);
        //cout << dur.count() << "s\n";
        printf("insertion sort during time: %lfs\n", dur.count());
       // cout<<"data after insertion sort : ";
        /*for(int i=0;i<size;i++){
            cout<<data[i]<<" ";
        }
        cout<<"\n";
*/
        begin = chrono::high_resolution_clock::now(); //auto begin=clock();
        mergesort(data2,0,size-1);
        finish = chrono::high_resolution_clock::now(); //auto finish=clock();
        dur = chrono::duration(finish - begin);
        //cout << dur.count() << "s\n";
        printf("merge sort during time: %lfs\n", dur.count());
        /*cout<<"data after merge sort : ";
        for(int i=0;i<size;i++){
            cout<<data2[i]<<" ";
        }*/
        Heap h(size);
        begin = chrono::high_resolution_clock::now(); //begin=clock();
        for(int i=0;i<size;i++){
            h.insert(data3[i]);
        }
        h.print_heap();
        finish = chrono::high_resolution_clock::now(); //finish=clock();
        // h.print_heap();
        dur = chrono::duration(finish - begin);
        //cout << dur.count() << "s\n";
        printf("heap sort during time: %lfs\n",dur.count());


        cout<<"Please cin data size (cin negative number to quit) : ";
    }
}
