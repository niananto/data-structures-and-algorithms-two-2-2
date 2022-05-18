#include"binomialheap.h"

int main()
{
    list<Node*> * binomialHeap = new list<Node*>;

    freopen("input.txt", "r", stdin);

    string command;
    while(cin >> command){
        // cout << command << endl;
        if(command == "FIN"){
            cout << "FindMax returned " << findMax(binomialHeap)->getValue() << endl;

        } else if(command == "EXT"){
            int temp = findMax(binomialHeap)->getValue();
            extractMax(binomialHeap);
            cout << "ExtractMax returned " << temp << endl;

        } else if(command == "INS"){
            int value;
            cin >> value;

            insertInto(binomialHeap, value);
            // printHeap(binomialHeap);
            cout << "Inserted " << value << endl;
            
        } else if(command == "INC"){
            int find, replace;
            cin >> find >> replace;

            increaseKey(binomialHeap, find, replace);
            cout << "Increased " << find << ". The updated value is " << replace << "." << endl;

        } else if(command == "PRI"){
            printHeap(binomialHeap);
        }
    }
    
    return 0;
}