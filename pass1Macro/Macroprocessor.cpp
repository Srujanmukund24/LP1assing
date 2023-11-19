#include<iostream>
#include<bits/stdc++.h>
#define long long ll
using namespace std;

int main()
{   ifstream fin;
    fin.open("input.txt" , ios::in);
    ofstream mntout,kpdtout,pntout,mdtout,fout;
    mntout.open("MNT2.txt"); //name-positional-kp-mdptr-kptr
    mdtout.open("MDT2.txt");// body of the macro with (p, index of parameter)
    kpdtout.open("KPDTAB2.txt"); // paramenter -value
    pntout.open("PNTAB2.txt");  //parameter-index
    fout.open("output2.txt");// only start to end matrerial direct sent to the output file
	vector<array<string,5>>mnt;
	vector<pair<string,string>>kpd;
	map<string,int>pnt;
	string line,word;
	bool macro=false,start=false;
	int mdptr=1;
	while(getline(fin,line)){
		stringstream ss(line);
		ss>>word; // only taken out 1st word;
		if(word=="MACRO"){
			macro=true;
			continue;//direct jump to next line;
		}
		if(macro){
			// for the very next line only :
			array<string,5>tempmnt={""};
			tempmnt[0]=word; // word will the fst word ie name of macro
            tempmnt[3]=to_string(mdptr);
			int pp=0;int kp=0 ; // no of parameters sathi lagnar aahe;
			while(ss>>word){
				// other words in line 
				word=word.substr(1); //& removed;
				if(word[word.size()-1]==','){
					word.pop_back();// removed ,
				}
				int kpind=-1;
				for(int i=0;i<word.size();i++){
					if(word[i]=='='){
						kpind=i;
						break;
					}
				}
				if(kpind!=-1){
					kp++;
					pair<string,string>pr({word.substr(0,kpind),word.substr(kpind+1)});
					kpd.push_back(pr);// insert int kptab;

					//insert only value in pntab;
					pnt[pr.first]=pnt.size()+1;
                    pntout<<pr.first<<" "<<pnt[pr.first]<<endl; 
				}
				else{
					pp++;
					pnt[word]=pnt.size()+1;
					pntout<<word<<" "<<pnt[word]<<endl;
				}
			} 
			tempmnt[1]=to_string(pp);
            tempmnt[2]=to_string(kp);
			if(kp>0){
				// then only kpdptr;
				tempmnt[4]=to_string(kpd.size()-kp+1); // formula
			}
			mnt.push_back(tempmnt);
            macro=false;
			continue;// jump to next;
		}
		if(word=="START"){
			start=true;
			continue;
		}

		if(start){
			// next line of start;
			if(word!="END"){
				fout<<word<<" ";
				while(ss>>word){
					fout<<word<<" ";
				}fout<<endl;
			}
			continue; // if end line come nothinf will be done ;
		}
		if(word=="MEND"){
              mdtout<<word<<endl;
			  pnt.clear();// fill the pnt again;
		}

		else{
			// all the other lines handled here mean the defination lines:
			mdtout<<word;

			while(ss>>word){

				if(word[0]=='&'){
					word=word.substr(1);// removed &;
					if(word[word.size()-1]==','){
						word.pop_back();
					}
					mdtout<< "(P,"<<pnt[word]<<")";
				}
			}mdtout<<endl;
		}
		mdptr++;
	}
    for(int i=0;i<mnt.size();i++){
		for(int j=0;j<5;j++){
			mntout<<mnt[i][j]<<" ";
		}mntout<<endl;
	}
	for(int i=0;i<kpd.size();i++){
		kpdtout<<kpd[i].first<<" "<<kpd[i].second<<endl;
	}
	return 0;
}