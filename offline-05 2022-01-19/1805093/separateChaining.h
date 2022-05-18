#include"hashFunctions.h"
using namespace std;

bool insertItem(vector<list< pair<string, unsigned long> >> &table, string key, int N, unsigned long* collision){
    int index = hashFunction(&key[0]) % N;
    static unsigned long value = 1;
    
    list< pair<string, unsigned long> > :: iterator itr;
    for(itr=table[index].begin(); itr!=table[index].end(); itr++){
        if((*itr).first == key){
            // is this a collision?
            return false;
        }
    }

    if(!table[index].empty()){
        (*collision)++;
    }
    table[index].push_back(make_pair(key, value));
    value++;
    return true;
}

unsigned long searchItem(vector<list< pair<string, unsigned long> >> &table, string key, int N, unsigned long* probing){
    int index = hashFunction(&key[0]) % N;

    list< pair<string, unsigned long> > :: iterator itr;
    for(itr=table[index].begin(); itr!=table[index].end(); itr++){
        (*probing)++;
        if((*itr).first == key){
            return (*itr).second;
        }
    }

    return 0;
}

bool deleteItem(vector<list< pair<string, unsigned long> >> &table, string key, int N){
    int index = hashFunction(&key[0]) % N;

    list< pair<string, unsigned long> > :: iterator itr;
    for(itr=table[index].begin(); itr!=table[index].end(); itr++){
        if((*itr).first == key){
            break;
        }
    }

    if (itr != table[index].end()){
        table[index].erase(itr);
        return true;
    }

    return false;
}

vector<list< pair<string, unsigned long> >> createHashTable(vector<string> &randStrings, int N){
    vector<list< pair<string, unsigned long> >> table(N);
    unsigned long* collision = new unsigned long(0);
    for(int i=0; i<10000; i++){
        insertItem(table, randStrings[i], N, collision);
        // cout << collision;
    }

    cout << *collision << endl;

    return table;
}