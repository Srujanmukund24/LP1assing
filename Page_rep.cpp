#include<iostream>
#include<bits/stdc++.h>
#define long long ll
using namespace std;

class PageRepalcement{
  vector<int> input;
  int pages;
  public:

  PageRepalcement(){
    // cout<<"Enter the no of pagees";
    // cin>>pages;
    // cout<<"Enter The Page Reference String ";
    // for(int i=0;i<pages;i++){
    //   int pg;cin>>pg;
    //   input.push_back(pg);
    // }
  }
  bool present(vector<int> vec,int key){
     for(int i=0;i<vec.size();i++){
      if(key==vec[i]) return true;
     }
     return false;
  }
  int found(int key,vector<int>vec){
    for(int i=0;i<vec.size();i++){
      if(key==vec[i]) return i;
     }
     return 0;
  }
  void FIFO(vector<int> pageref,int pages,int frames){
    // vector<int> pageref=this->input;
    // int frame;
    // cout<<"enter The frameber of frames to be used";
    // cin>>frame;
    vector<int> arrframe;
    queue<int>q;
    int hit=0;
    for(int i=0;i<pages;i++){
      if(present(arrframe,pageref[i])){
        hit++; // hit condition 
      }
      else if(arrframe.size()<frames){
         arrframe.push_back(pageref[i]); // page fault but sapce available
         q.push(pageref[i]);
      }
      else{
        int replace=q.front();
        q.pop();
        arrframe[found(replace,arrframe)]=pageref[i];
        q.push(pageref[i]);
      }       

       for(int i=0;i<arrframe.size();i++){
        cout<<arrframe[i]<<" "; // printing the frames buffer
      }cout<<endl;
    }
          cout<<"hit"<<hit<<" "<<pages-hit<<" ."<<endl;
  } 


  int predictOptimal(vector<int> pageref,vector<int> fr,int pages,int frames,int index){
    int res=-1;int farthest=index;//search in front for the place to be exchanged in buffer;

    for(int i=0;i<frames;i++){
      int j;
      for(j=index;j<pages;j++){
        if(pageref[j]==fr[i]){
          if(j>farthest){     // we wnat the farthest number present in the buffer or either not coming in future.
            farthest=j;
            res=i;
          }
          break;// for first occuresnce of the page 
        }
      }
    if(j==pages){
      return i; // means not found in the rest part .
    }
    }
    if(res==-1){
      res=0;
    }
    return res;
  }

  void Optimal(vector<int> pageref,int pages,int frames){
    vector<int> arrframe;
    int hit=0;
    for(int i=0;i<pages;i++){

      if(present(arrframe,pageref[i])){
        hit++; // hit condition 
      }
      else if(arrframe.size()<frames){
         arrframe.push_back(pageref[i]); // page fault but sapce available
      }
      else{ 
        // no space so repalce from the least frecuently used .
        int replace=predictOptimal(pageref,arrframe,pages,frames,i+1);
        arrframe[replace]=pageref[i];
      }

      for(int i=0;i<arrframe.size();i++){
        cout<<arrframe[i]<<" "; // printing the frames buffer
      }cout<<endl;

    }
      cout<<"hit"<<hit<<" "<<pages-hit<<" ."<<endl;
  } 

  int predictLru(vector<int> pageref,vector<int> fr,int pages,int frames,int index){
    int res=-1;int leastused=index+1;//search in front for the place to be exchanged in buffer;

    for(int i=0;i<frames;i++){
      int j;
      for(j=index;j>=0;j--){
        if(pageref[j]==fr[i]){
          if(j<leastused){     // we wnat the farthest number present in the buffer or either not coming in future.
            leastused=j;
            res=i;
          }
          break;// for first occuresnce of the page 
        }
      }
    if(j==0){
      return i; // means not found in the rest part .
    }
    }
    if(res==-1){
      res=0;
    }
    return res;
  }

  void LRU(vector<int> pageref,int pages,int frames){
    vector<int> arrframe;
    int hit=0;
    for(int i=0;i<pages;i++){

      if(present(arrframe,pageref[i])){
        hit++; // hit condition 
      }
      else if(arrframe.size()<frames){
         arrframe.push_back(pageref[i]); // page fault but sapce available
      }
      else{ 
        // no space so repalce from the least frecuently used .
        int replace=predictLru(pageref,arrframe,pages,frames,i-1);
        arrframe[replace]=pageref[i];
      }

      for(int i=0;i<arrframe.size();i++){
        cout<<arrframe[i]<<" "; // printing the frames buffer
      }cout<<endl;

    }
      cout<<"hit"<<hit<<" "<<pages-hit<<" ."<<endl;
  }
    
};

int main()
{ 
     PageRepalcement P1;
     vector<int> vec= {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2, 1, 2, 0, 1, 7, 0, 1};
     int pages=20;
     int frame=4;
     P1.FIFO(vec,pages,frame);
    // P1.Optimal(vec,pages,frame); 
    // P1.LRU(vec,pages,frame);    

    return 0;
}