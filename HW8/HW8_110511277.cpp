#include<iostream>
#include<fstream>
#include<queue>
using namespace std;
struct node{
    int color;
    int d;  //distance
    int data;
    int x;
    int y;
    node *parent;
};

void printpath(node**map , node ini, node final ,ofstream&out){
    if(ini.x==final.x && ini.y==final.y){   //if the node is start(base case)
        for(int i=0;i<ini.data;i++){       //if it is trap, print two times
            out<<"("<<ini.y<<","<<ini.x<<")\n";
        }
    }
    else if(final.parent==NULL)      //if there is no parent, return
        return;
    else {
        printpath(map,ini,*(final.parent),out);  //recursive
        for(int i=0;i<final.data;i++){       //if it is trap, print two times
            out<<"("<<final.y<<","<<final.x<<")\n";
        }
    }
}
struct cmp
{
    bool operator()(node a,node b){
        return a.data>b.data;       //let the queue sort according to data
    }
};

int main(){
    ifstream in;
    ofstream out;
    int x ,N=20;                             //N is the number of times(20)
    int n1=N;
    node**map=new node*[18];

    node temp,temp2;
    for(int i=0;i<18;i++){
        map[i]=new node[18];
    }
    in.open("input.txt");
    out.open("110511277_output.txt");
    priority_queue<node,vector<node>,cmp>BFS;
    while(N--){                               //run 20 times
        for(int i=1;i<=17;i++){
            for(int j=1;j<=17;j++){
                in>>x;                        //read map
                map[i][j].x=j;                //store x 
                map[i][j].y=i;                //store y                          
                map[i][j].data=x;             //store map(wall or road or trap)
                map[i][j].color=0;            //let all color be white                  
                map[i][j].d=INT16_MAX;        //let all distance be infinite
                map[i][j].parent=NULL;        //let all parent be nullptr
            }
        }
        
        map[1][1].d=0;                         //let start's distance be zero
        map[1][1].color=1;                     //let start's color be gray
        temp=map[1][1];
        BFS.push(temp);                        //push into queue
        while(!BFS.empty()){
            temp=BFS.top();
            BFS.pop();
            if(temp.x-1>=1){                    //if next is not out of boundary
                if(map[temp.y][temp.x-1].color==0 && map[temp.y][temp.x-1].data>0){      //if next node is no visited and is not wall 
                    map[temp.y][temp.x-1].color=1;     //let color to be gray
                    map[temp.y][temp.x-1].d=map[temp.y][temp.x].d+map[temp.y][temp.x-1].data;   //set the distance
                    map[temp.y][temp.x-1].parent=&(map[temp.y][temp.x]);    //set its parent
                    temp2=map[temp.y][temp.x-1];
                    BFS.push(temp2);                       //push to the queue
                }
            }
            if(temp.y-1>=1 ){                    //if next is not out of boundary
                if(map[temp.y-1][temp.x].color==0 && map[temp.y-1][temp.x].data>0){       //if next node is no visited and is not wall
                    map[temp.y-1][temp.x].color=1;     //let color to be gray
                    map[temp.y-1][temp.x].d=map[temp.y][temp.x].d+map[temp.y-1][temp.x].data;  //set the distance
                    map[temp.y-1][temp.x].parent=&(map[temp.y][temp.x]);    //set its parent
                    temp2=map[temp.y-1][temp.x];                           
                    BFS.push(temp2);                    //push to the queue
                }
            }
            if(temp.x+1<=17 ){                   //if next is not out of boundary
                if(map[temp.y][temp.x+1].color==0 && map[temp.y][temp.x+1].data>0){       //if next node is no visited and is not wall
                    map[temp.y][temp.x+1].color=1;       //let color to be gray
                    map[temp.y][temp.x+1].d=map[temp.y][temp.x].d+map[temp.y][temp.x+1].data;   //set the distance
                    map[temp.y][temp.x+1].parent=&(map[temp.y][temp.x]);         //set its parent
                    temp2=map[temp.y][temp.x+1];
                    BFS.push(temp2);                    //push to the queue
                }
            }
            if(temp.y+1<=17 ){                   //if next is not out of boundary
                if(map[temp.y+1][temp.x].color==0 && map[temp.y+1][temp.x].data>0){        //if next node is no visited and is not wall
                    map[temp.y+1][temp.x].color=1;       //let color to be gray
                    map[temp.y+1][temp.x].d=map[temp.y][temp.x].d+map[temp.y+1][temp.x].data;  //set the distance
                    map[temp.y+1][temp.x].parent=&(map[temp.y][temp.x]);        //set its parent
                    
                    temp2=map[temp.y+1][temp.x];        
                    BFS.push(temp2);                    //push to the queue
                }
            }
            
            map[temp.y][temp.x].color=2;          //let the color to be black
        }
        //print the outcome
        out<<"pattern "<<n1-N<<"\nstep="<<map[17][17].d<<"\n";
        printpath(map,map[1][1],map[17][17],out);
        out<<"\n";
    }
    

        
}