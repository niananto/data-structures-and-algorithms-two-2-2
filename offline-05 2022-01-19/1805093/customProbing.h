#include"hashFunctions.h"
using namespace std;

bool insertItem(vector< pair<string, unsigned long> > &table, string key, int N, unsigned long* collision){
    int index = hashFunction(&key[0]) % N;
    static unsigned long value = 1;

    if(table[index].first == ""){
        table[index] = make_pair(key, value);
        value++;
        return true;
    }
    else if(table[index].first == key){
        (*collision)++;
        return false;
    }
    else{
        // collision
        int i = 1;
        int oldIndex = index;
        while(true){
            //------------------------------------------------
            index = (index + 37 * i * auxHashFunction(&key[0]) + 53 * i * i) % N;
            //-------------------------------------------------
            if(table[index].first == key){
                return false;
            }
            else if(table[index].first == ""){
                table[index] = make_pair(key, value);
                value++;
                return true;
            }
            else if(index == oldIndex){
                // full
                return false;
            }
            i++;
            (*collision)++;
        }
    }
}

unsigned long searchItem(vector<pair<string, unsigned long>> &table, string key, int N, unsigned long* probing){
    int index = hashFunction(&key[0]) % N;

    if(table[index].first == ""){
        (*probing)++;
        return 0;
    }
    else if(table[index].first == key){
        (*probing)++;
        return table[index].second;
    }
    else{
        int i = 1;
        int oldIndex = index;
        while(true){
            //-------------------------------------------------
            index = (index + 37 * i * auxHashFunction(&key[0]) + 53 * i * i) % N;
            //-----------------------------------------------            
            if(table[index].first == key){
                return table[index].second;
            }
            if(index == oldIndex){
                // not found
                return 0;
            }
            i++;
            (*probing)++;
        }
    }
}

bool deleteItem(vector<pair<string, unsigned long>> &table, string key, int N){
    int index = hashFunction(&key[0]) % N;

    if(table[index].first == ""){
        return false;
    }
    else if(table[index].first == key){
        table[index] = make_pair("", 0);
        return true;
    }
    else{
        int i = 1;
        int oldIndex = index;
        while(true){
            //-------------------------------------------------
            index = (index + 37 * i * auxHashFunction(&key[0]) + 53 * i * i) % N;
            //-----------------------------------------------
            if(table[index].first == key){
                table[index] = make_pair("", 0);
                return true;
            }
            if(index == oldIndex){
                // not found
                return false;
            }
            i++;
        }
    }
}

vector<pair<string, unsigned long>> createHashTable(vector<string> &randStrings, int N){
    vector<pair<string, unsigned long>> table(N, make_pair("", 0));
    unsigned long collision = 0;
    for(int i=0; i<10000; i++){
        insertItem(table, randStrings[i], N, &collision);
    }

    cout << collision << endl;

    return table;
}