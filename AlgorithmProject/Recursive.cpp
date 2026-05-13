#include <iostream>
#include <string>
#include <algorithm>
#include "Algorithms.h"

using namespace std;

void solve(const string& s,int start,int index,int freq[26],int diff,int& maxLen){
    if(index==s.size()){
        return;
    }
    int c=s[index]-'a';
    if(freq[c]==0){
        diff++;
    }
    freq[c]++;
    if(diff>2){
        return;
    }
    if(diff==2){
        int first=0,second=0;
        for (int i=0;i<26;i++){
            if(freq[i]>0){
                if (first==0)
                    first=freq[i];
                else
                    second=freq[i];
            }
        }
        if(first==second){
            maxLen=max(maxLen,index-start+1);
        }
    }
    solve(s,start,index+1,freq,diff,maxLen);
}
int RecursiveAlgorithm(const string& s){
    int maxLen=0;
    for (int i=0;i<s.size();i++){
        int freq[26]={0};
        solve(s,i,i,freq,0,maxLen);
    }
    return maxLen;
}