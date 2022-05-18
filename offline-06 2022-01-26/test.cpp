#include<bits\stdc++.h>
using namespace std;

void hello(list<int> *temp){
    (*temp).push_back(66);
}

int main(){
    list<int> temp;
    temp.push_back(55);

    hello(&temp);

    for(auto t : temp){
        cout << t << endl;
    }

}