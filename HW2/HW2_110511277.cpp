#include<iostream>
#include<climits>
#include<vector>
#include<fstream>
using namespace std;
struct subarray{
    float value=0;
    int begin;
    int end;
    int length;
};
vector<subarray>v;
subarray max_midarray(vector<float>& a, int s, int m, int e){
    subarray temp;
    float sum=0;
    float tempsum=INT_MIN;
    for(int i=m;i>=s;i--){
        sum+=a[i];
        if(sum>tempsum){
            tempsum = sum;
            temp.begin = i;
        }
    }
    temp.value+=tempsum;//find the maximum subarray on the left of middle
    tempsum=INT_MIN;
    sum=0;
    for(int i=m+1;i<=e;i++){
        sum+=a[i];
        if(sum>tempsum){
            tempsum = sum;
            temp.end = i;
        }
    }
    temp.value+=tempsum;//find the maximum subarray on the right of middle
    temp.length=temp.end-temp.begin+1;
    return temp;
}
subarray max(subarray a, subarray b, subarray c){
    //push three subarray and return the subarray which have maximum value
    if(a.value>=b.value&&a.value>=c.value)
        return a;
    else if(b.value>a.value&&b.value>=c.value)
        return b;
    else
        return c;
    
}
subarray max_subarray(vector<float>& a,int s,int e){
    subarray ans;
    if(s==e){
        ans.begin=s;
        ans.end=e;
        ans.value=a[s];
        ans.length=1;
        v.push_back(ans);
        return ans;
    }//base case
    else{
        subarray sub_left = max_subarray(a,s,(s+e)/2);  //call recursion function(divide)，split vector into two subvector 
        subarray sub_right = max_subarray(a,(s+e)/2+1,e); //call recursion function(divide)，split vector into two subvector
        subarray sub_mid = max_midarray(a,s,(s+e)/2,e); //call max_midarray function，find max subarray which contain middle term
        subarray temp = max(sub_left,sub_mid,sub_right); //(conquer)find the maximum subarray in sub_left sub_right sub_mid
        v.push_back(temp);
        return temp;
    }
}
vector<subarray> process(){
    vector<subarray>v2;
    for(int i=0;i<v.size();i++){
        if(v[v.size()-1].value==v[i].value){
            v2.push_back(v[i]);
        }
    }//push subarray which have the same value as maximum value into another vector

    for(int i=0;i<v2.size();i++){
        for(int j=i+1;j<v2.size();j++){
            if(v2[j].length>v2[i].length){
                swap(v2[j],v2[i]);
            }
            else if(v2[j].length==v2[i].length){
                if(v2[j].begin>v2[i].begin){
                    swap(v2[j],v2[i]);
                }
            }
        }
    }//sort this vector by their length，if their length are the same，sort by their begin
    return v2;
}
int main(){
    vector<float>a;
    int num;
    float temp;
    ifstream input;
    input.open("data.txt"); //open input data
    while(input>>num>>temp){
        a.push_back(temp);    //read data and store in a vector a
    }
    subarray sub=max_subarray(a,0,a.size()-1); //call max_subarray function
    
    vector<subarray>v2;
    v2=process();         //push subarray which has the same maximum value into v2 and sort by their length

    cout<<"subarray begin : "<<v2[v2.size()-1].begin+1<<"\nsubarray end : "<<v2[v2.size()-1].end+1<<"\nsubarray value : "<<v2[v2.size()-1].value<<endl; //print the maximum subarray
    for(int i=v2.size()-2;i>=0;i--){
        if(v2[i].length==v2[i+1].length){//if their length are same，cout more than one
            if(v2[i].begin!=v2[i+1].begin||v2[i].end!=v2[i+1].end)//avoid cout the same subarray
                cout<<"\nsubarray begin : "<<v2[i].begin+1<<"\nsubarray end : "<<v2[i].end+1<<"\nsubarray value : "<<v2[i].value<<endl;
        }
        else
            break;
    }


}