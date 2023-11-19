#include<iostream>
#include<bits/stdc++.h>
#define long long ll
using namespace std;

class Election{
 int npros,coordinator;
 vector<int> processSt;
 public:
   Election(){
    cout<<"Enter THe No of Process"<<endl;
    cin>>npros;
    processSt=vector<int>(npros+1,0);
    for(int i=1;i<npros+1;i++){
        cout<<"Enter the process "<<i<<"is alive or not 0/1 ";
        cin>>processSt[i];
        if(processSt[i]){
            coordinator=i;// the highest will be made as coordinator by defualt .
        }
    }
   }
   void display(){
    cout<<"Process \t Alive"<<endl;
    for(int i=1;i<=npros;i++){
        cout<<i<<"\t"<<processSt[i]<<endl;
    }

    cout<<"cordenator::::"<<coordinator<<endl;
   }

   void bully(){
      int choice,crash,activate,gid,subcordinator,flag;
      do{
        cout<<"1.crash 2.activate 3.disp 4.exit"<<endl;
        cin>>choice;
        switch(choice){
            case 1:
            //crash one of the alive only :
            cout<<"enter the process to be crash ";
            cin>>crash;
            if(processSt[crash]==0){
                cout<<"already dead"<<endl;
            }else{
                processSt[crash]=0;
            }
            do{
                cout<<"Enter generator id";
                cin>>gid;
                if(gid==coordinator || processSt[gid]==0){
                    cout<<"enter valid"<<endl;
                }
            }while(processSt[gid]==0 || gid==coordinator);
            flag=0;
             // sent msg to only the higer process an if aliv e make them subordinator
              for(int i=gid+1;i<=npros;i++){
                   cout<<"msg sent from "<<gid<<"to "<< i<<endl;

                   if(processSt[i]==1){
                    subcordinator=i;
                    cout<<"Response sent from "<<i<<endl;
                    flag=1;
                   }
              }
              if(flag){
                coordinator=subcordinator;  // change the codinator ;
              }
              else coordinator=gid;  // no highre remainign

              display();
            break;
            case 2:
            // activate any dead one ;
            cout<<"Enter the proces to bve activate ";
            cin>>activate;
            if(processSt[activate]){
                cout<<"already active;"<<endl;
                break;
            }else processSt[activate]=1;
            
            if(activate==npros){
                coordinator=npros;
                break;
            }
            flag=0;
             for(int i=activate+1;i<=npros;i++){
                   cout<<"msg sent from "<<activate<<"to "<< i<<endl;

                   if(processSt[i]==1){
                    subcordinator=i;
                    cout<<"Response sent from "<<i<<endl;
                    flag=1;
                   }
              }
              if(flag){
                coordinator=subcordinator;  // change the codinator ;
              }
              else coordinator=activate; 

              display();
            break;
            case 3:
            display();
            break;
            case 4:
            break;
        }
      }while(choice!=4);
   }
   void ring(){
       int choice,crash,activate,gid,subcordinator,flag,j;
       vector<int> activelist;
      do{
        cout<<"1.crash 2.activate 3.disp 4.exit"<<endl;
        cin>>choice;
        switch(choice){
            case 1:
            //crash one of the alive only :
            cout<<"enter the process to be crash ";
            cin>>crash;
            if(processSt[crash]==0){
                cout<<"already dead"<<endl;
            }else{
                processSt[crash]=0;
            }
            do{
                cout<<"Enter generator id";
                cin>>gid;
                if(gid==coordinator){
                    cout<<"enter valid"<<endl;
                }
            }while(gid==coordinator);
            flag=0;
             // sent msg to all circularly and wait for the msg to come again ;
            
              if(crash==coordinator){
                 j=gid+1;
                 activelist.push_back(gid);
                while(j!=gid){
                        
                        if(processSt[j]==1){
                            activelist.push_back(j);
                            cout<<j<<"is added to active list\n";
                            flag=1;
                        }
                        j=(j+1)%(npros+1);
                }

                sort(activelist.begin(), activelist.end());
                subcordinator=activelist.back();
                if(flag){
                    coordinator=subcordinator;
                }else coordinator=gid;
              }     
              cout<<" winner :"<<coordinator;   
              activelist.clear();
              display();
            break;

            case 2:
            // activate any dead one ;
            cout<<"Enter the proces to bve activate ";
            cin>>activate;
            if(processSt[activate]==1){
                cout<<"already active;"<<endl;
                break;
            }else processSt[activate]=1;

        
                j=activate+1;
                activelist.push_back(activate);
                while(j!=activate && j<=npros){
                        
                        if(processSt[j]==1){
                            activelist.push_back(j);
                            cout<<j<<"is added to active list";
                            flag=1;
                        }
                        j=(j+1)%(npros+1);
                }

                if(flag){
                    sort(activelist.begin(), activelist.end());
                    subcordinator=activelist.back();
                    coordinator=subcordinator;
                    activelist.clear();
                }
                else coordinator=activate;
             
               cout<<" winner :"<<coordinator;
              display();
            break;
            case 3:
            display();
            break;
            case 4:
            break;
        }
      }while(choice!=4);
   }

};

int main()
{ 
Election e1;
e1.display();
// e1.bully();
e1.ring();
    return 0;
}