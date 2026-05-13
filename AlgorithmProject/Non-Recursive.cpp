#include <iostream>
#include <string>
#include <algorithm>
#include "Algorithms.h"

using namespace std;

int NonRecursiveAlgorithm(string s) {

    int n=s.length();
    int maxLen=0;
    for (int i=0;i<n;i++){
        int freq[26]={0};
        int diff=0;
        for(int j=i;j<n;j++){
            int index=s[j]-'a';
            if(freq[index]==0){
                diff++;
            }
            freq[index]++;
            if(diff>2){
                break;
            }
            if(diff==2){
                int first=0;
                int second=0;
                for(int k=0;k<26;k++){
                    if(freq[k]>0){
                        if(first==0)
                            first=freq[k];
                        else
                            second=freq[k];
                    }
                }
                if(first==second){
                    int len=j-i+1;
                    if (len>maxLen)
                        maxLen=len;
                }
            }
        }
    }
    return maxLen;
}
