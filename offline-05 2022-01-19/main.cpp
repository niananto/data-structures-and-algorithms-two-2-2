#include<bits\stdc++.h>
using namespace std;

#include"separateChaining.h"
// #include"doubleHashing.h"
// #include"customProbing.h"

// random word generator
string genRandom(int stringLength)
{
    // static const char alphanum[] =
    //     "0123456789"
    //     "!@#$%^&*"
    //     "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    //     "abcdefghijklmnopqrstuvwxyz";

    static const char alphanum[] = 
        "abcdefghijklmnopqrstuvwxyz";

    string randString;

    for(int i=0; i<stringLength; i++){
        randString += alphanum[rand() % sizeof(alphanum) - 1];
    }

    return randString;
}

int main()
{
    unsigned long N;
    cin >> N;

    int stringLength = 7;
    vector<string> randStrings(10000);
    srand(time(NULL));
    for(int i=0; i<10000; i++){
        randStrings[i] = genRandom(stringLength);
        
        // generating unique words
        
        // vector<string> :: iterator itr;
        // for(itr = randStrings.begin(); itr != randStrings.end(); itr++){
        //     if((*itr) == randStrings[i]){
        //         i--;
        //         break;
        //     }
        // }

        // for(const auto &itr : randStrings){
        //     if(itr == randStrings[i]){
        //         i--;
        //         break;
        //     }
        // }
    }

    auto table = createHashTable(randStrings, N);
    // for(auto t : table){
    //     cout << t.first << ", " << t.second << endl;
    // }
    // cout << searchItem(table, randStrings[9000], N);

    int i;
    unsigned long* probing = new unsigned long(0);
    for(i=0; i<10000; i+=10){
        searchItem(table, randStrings[i], N, probing);
    }
    cout << "Average probing " << (*probing)/1000.0 << endl;

    return 0;
}