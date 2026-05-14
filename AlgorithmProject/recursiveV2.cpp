#include <iostream>
#include <string>
#include <algorithm>
#include "Algorithms.h"

using namespace std;

void solve(const string& s,int start,int index,int freq[26],int diff,int& maxLen){
    if(index==(int)s.size()){
        return;
    }
    int c=s[index]-'a';
    if(freq[c]==0){
        diff++;
    }
    freq[c]++;
    if(diff<=2){
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
    freq[c]--;
    if(freq[c]==0){
        diff--;
    }
}
int RecursiveAlgorithm(const string& s){
    int maxLen=0;
    for (int i=0;i<(int)s.size();i++){
        int freq[26]={0};
        int diff=0;
        solve(s,i,i,freq,diff,maxLen);
    }
    return maxLen;
}
#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include <string>
using namespace std;

int NonRecursiveAlgorithm(const string& s);
int RecursiveAlgorithm(const string& s);

#endif
