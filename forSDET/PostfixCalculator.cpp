#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include <sstream>
#include <bits/stdc++.h>
using namespace std;

float str2float(string strNum){
    // cout<<"in str2float()"<<endl;
    for(int i=0;i<strNum.size();i++){
        if(strNum[i]=='.' && (strNum.size()==1)){
            return INT_MIN;
        }
        if((strNum[i]<'0'||strNum[i]>'9') && strNum[i]!='.' ){
            // cout<<strNum[i]<<":  str2float() fail"<<endl;
            return INT_MIN;
        }
    }
    float res;
    stringstream stream(strNum);
    stream>>res;
    // cout<<"got float Num"<<res<<"  ";
    return res;
}

void cutString(vector<string> &vecSer, string strSource){
    string res;
    vecSer.clear();
    stringstream input(strSource);
    while(input>>res){
        vecSer.push_back(res);
    }
// /////////////////////////////////////
//     cout<<"data from vecSer:";
//     for(int i=0;i<vecSer.size();i++){    
//         cout<<vecSer[i]<<'\t';
//     }
//     cout<<endl;/////////////////////
}

bool calPostFix(vector<string> const & vecSer, float & res){
    vector<float> vecAssist;
    int size=vecSer.size();
    // cout<<"In calPostFix():  ";
    for(int i=0;i<size;i++){
        if(vecSer[i].size()==1 && (vecSer[i][0]=='+' || vecSer[i][0]=='-' || vecSer[i][0]=='*' || vecSer[i][0]=='/')){
            // cout<<"Got operators"<<endl;
            if(vecAssist.size()<2)
                return false;
            float second=vecAssist.back();
            vecAssist.pop_back();
            float first=vecAssist.back();
            vecAssist.pop_back();
            switch(vecSer[i][0]){
            case '+':
                vecAssist.push_back(first+second);
                break;
            case '-':
                vecAssist.push_back(first-second);
                break;
            case '*':
                vecAssist.push_back(first*second);
                break;
            case '/':
                if((second-0.0<0.00001) && (second-0.0 >-0.00001))
                    return false;
                vecAssist.push_back(first/second);
                break;
            default:
            // cout<<"In switch failed, vecSer[i][0]=="<<vecSer[i][0]<<endl;
                return false;
            }
        }else{
            float fNum=str2float(vecSer[i]);
            if(fNum==INT_MIN)
                return false;
            vecAssist.push_back(fNum);
        }
    }
    if(vecAssist.size()!=1){
        return false;
    }
    res = vecAssist[0];
    return true;
}

int main(){
    string strSource, strExit("exit");
    std::getline(std::cin,strSource);
    vector<string> vecSer;
    
    while(1){
        cutString(vecSer,strSource);
        if(vecSer[0]==strExit)
            break;
        //for
        float res=0;
        if(!calPostFix(vecSer,res)){
            cout<<"Input Error!"<<endl;
        }else{
            cout<<res<<endl;
        }
        std::getline(std::cin,strSource);
    }
    // cout<<strSource;
}