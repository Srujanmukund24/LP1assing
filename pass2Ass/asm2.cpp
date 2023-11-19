#include<iostream>
#include<bits/stdc++.h>
#define long long ll
using namespace std;
int main()
{ 
    vector<pair<string,string>> symtab;
    vector<pair<string,string>> littab;
    ifstream sym;
    sym.open("symTable.txt", ios::in);
    ifstream lit;
    lit.open("litTable.txt", ios::in);
    string  line,word1,word2; 
    while(getline(sym,line)){
         stringstream ss(line);
         ss>>word1;ss>>word2;
         symtab.push_back({word1,word2});
    }
    
    while(getline(lit,line)){
         stringstream ss(line);
         ss>>word1;ss>>word2;
         littab.push_back({word1,word2});
    }
    
    for (auto it : symtab)
    {
        cout << it.first << " " << it.second << endl;
    }

    for (auto it : littab)
    {
        cout << it.first << " " << it.second << endl;
    }
    
    ifstream fin;
    fin.open("intermidiate.txt", ios::in);

    ofstream fout;
    fout.open("mac.txt", ios::out);
    string line1;
    while(getline(fin,line1)){
    string word;
    vector<string>words;
        stringstream ss(line1);
        while(ss>>word){
            words.push_back(word);
        }

        if(words[1][1]=='I' && words[1][2]=='S'){
             //memonoics opcode
             fout<<words[0]<<" ";
            if(words[2][0]=='0'){
                fout<<"0 0"<<endl;
            }
            else fout<<words[2][0];

            if(words[2][1]!=')'){
                fout<<words[2][1]<<" ";
            }else fout<<" ";


            if(words.size()==6){
                fout<<words[3][1]<<" ";
                if(words[4][1]=='S'){
                    int index=words[5][0]-'0';
                    fout<< symtab[index-1].second<<" \n";
                }
                if(words[4][1]=='L'){
                    int index=words[5][0]-'0';
                    fout<< littab[index-1].second<<" \n";
                }
            }

            if(words.size()==5){
                if(words[3][1]=='S'){
                    int index=words[4][0]-'0';
                    fout<< symtab[index-1].second<<" \n";
                }
                else if(words[3][1]=='L'){
                    int index=words[4][0]-'0';
                    fout<< littab[index-1].second<<" \n";
                }
                else{
                    fout<<words[3][1]<<" "<<words[4][1]<<endl;
                }
            }   
        }
        else if(words[1][1]=='D' && words[1][2]=='L') {
            if(words[2][0]=='2'){
                fout<<endl;
            }
            else{
                fout<<words[0]<<" 0 0 "<<words[4][0]<<endl;
            }
        }
         
    }
    return 0;
}