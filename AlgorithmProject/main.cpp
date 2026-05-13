#include <iostream>
#include <string>
#include "Algorithms.h"

using namespace std;

int main() {
    string s;
    cin>>s;
    int NonRecursiveResult=NonRecursiveAlgorithm(s);
    int RecursiveResult=RecursiveAlgorithm(s);

    cout<<"\nNon-Recursive Result = "<<NonRecursiveResult<<endl;
    cout << "Recursive Result = "<<RecursiveResult<<endl;
    return 0;
}
