#include<bits\stdc++.h>
#include"node.h"
using namespace std;

list<Node*> consolidateBinomialHeap(list<Node*> bh){
    // 0 or 1
    if(bh.size() <= 1){
        return bh;
    }
    
    list<Node*>::iterator prev_tree, curr_tree, next_tree;
    prev_tree = curr_tree = next_tree = bh.begin();

    // 2
    if(bh.size() == 2){
        next_tree = bh.end();
        if((*curr_tree)->getDegree() != (*next_tree)->getDegree()){
            return bh;
        }
        *curr_tree = mergeBinomialTrees((*curr_tree), (*next_tree));
        bh.erase(next_tree);

        return bh;
    }

    // 3 or more trees
    // looping through the end
    next_tree++;
    while(prev_tree != bh.end()){
        // case 01 : degrees of curr and next
        // are not same; move ahead
        if((*curr_tree)->getDegree() != (*next_tree)->getDegree()){
            prev_tree++;
            curr_tree++;
            next_tree++;

            continue;
        }
        // case 02 : degrees are same 3 in a row
        // move ahead
        list<Node*>::iterator temp = next_tree;
        temp++;
        if((*curr_tree)->getDegree() == (*temp)->getDegree()){
            prev_tree++;
            curr_tree++;
            next_tree++;

            continue;
        }
        // case 03 : value of curr >= value of next
        // make next a child of curr
        if((*curr_tree)->getValue() >= (*next_tree)->getValue()){
            *prev_tree = mergeBinomialTrees((*curr_tree), (*next_tree));
            curr_tree = bh.erase(next_tree);
            if(next_tree != bh.end()){
                next_tree++;
            }
        }
        // case 04 : value of curr < value of next
        // make curr a child of next
        else{
            *prev_tree = mergeBinomialTrees((*next_tree), (*curr_tree));
            curr_tree = bh.erase(curr_tree);
            if(next_tree != bh.end()){
                next_tree++;
            }
        }
    }
    return bh;
}

list<Node*> unionBinomialHeap(list<Node*> bh1, list<Node*> bh2){
    list<Node*> merged;
    list<Node*>::iterator it1 = bh1.begin();
    list<Node*>::iterator it2 = bh2.begin();

    while(it1 != bh1.end() && it2 != bh2.end()){
        if((*it1)->getDegree() <= (*it2)->getDegree()){
            merged.push_back(*it1);
            it1++;
        } else {
            merged.push_back(*it2);
            it2++;
        }
    }

    while(it1 != bh1.end()){
        merged.push_back(*it1);
        it1++;
    }

    while(it2 != bh2.end()){
        merged.push_back(*it2);
        it2++;
    }

    return merged;
}

Node* findMax(list<Node*> bh){
    list<Node*>::iterator it = bh.begin();
    Node *maxRoot = *it;
    while(it != bh.end()){
        if ((*it)->getValue() > maxRoot->getValue()){
            maxRoot = *it;
        }
        it++;
    }
    return maxRoot;
}

list<Node*> extractMax(list<Node*> bh){
    // find max
    Node *maxRoot = findMax(bh);
    // erase that tree from primary heap
    list<Node*> newHeap1;
    list<Node*>::iterator it = bh.begin();
    while(it != bh.end()){
        if(*it != maxRoot){
            newHeap1.push_back(*it);
        }
        it++;
    }
    // make a heap with trees who are children of the root of the removed tree
    list<Node*> newHeap2;
    Node *temp1 = maxRoot->getChild();
    Node *temp2;
    while(temp1 != nullptr){
        temp2 = temp1;
        temp2->setSiblings(nullptr);
        newHeap2.push_front(temp2);
        temp1 = temp1->getSiblings();
    }
    // union and consolidate both heaps
    bh = unionBinomialHeap(newHeap1, newHeap2);
    bh = consolidateBinomialHeap(bh);

    return bh;
}

list<Node*> insertInto(list<Node*> &bh, int value){
    Node* newNode = createNode(value);
    bh.push_front(newNode);
    bh = consolidateBinomialHeap(bh);

    return bh;
}

list<Node*> increaseKey(list<Node*> bh, int find, int replace){
    bool found = false;
    Node* toBeIncreased;

    list<Node*>::iterator rootIterator = bh.begin();
    while(rootIterator != bh.end()){
        if((*rootIterator)->getValue() == find){
            toBeIncreased = *rootIterator;
            found = true;
            break;
        }

        Node* childIterator = (*rootIterator)->getChild();
        while(childIterator != nullptr){
            if(childIterator->getValue() == find){
                toBeIncreased = childIterator;
                found = true;
                break;
            }

            Node* siblingsIterator = childIterator->getSiblings();
            while(siblingsIterator != nullptr){
                if(siblingsIterator->getValue() == find){
                    toBeIncreased = siblingsIterator;
                    found = true;
                    break;
                }

                siblingsIterator = siblingsIterator->getSiblings();
            }

            if(found){
                break;
            }
            childIterator = childIterator->getChild();
        }

        if(found){
            break;
        }
        rootIterator++;
    }

    // increase
    toBeIncreased->setValue(replace);

    // now to bubble up
    Node *tempChild, *tempParent;
    tempChild = toBeIncreased;
    tempParent = toBeIncreased->getParent();
    while(tempParent != nullptr){
        if(tempChild->getValue() > tempParent->getValue()){
            int tempValue = tempChild->getValue();
            tempChild->setValue(tempParent->getValue());
            tempParent->setValue(tempValue);
        }
        tempChild = tempParent;
        tempParent = tempChild->getParent();
    }

    return bh;
}

void printHeap(list<Node*> bh){
    cout << "Printing Binomial Heap..." << endl;
    cout << "-------------------------------------" << endl;

    list<Node*>::iterator rootIterator = bh.begin();
    while(rootIterator != bh.end()){
        cout << "Binomial Tree, B" << (*rootIterator)->getDegree() << endl;

        cout << "Level 0 : " << (*rootIterator)->getValue() << endl;

        int i = 1;
        Node* childIterator = (*rootIterator)->getChild();
        while(childIterator != nullptr){
            cout << "Level " << i << " : " << childIterator->getValue() << " ";

            Node* siblingsIterator = childIterator->getSiblings();
            while(siblingsIterator != nullptr){
                cout << siblingsIterator->getValue() << " ";

                siblingsIterator = siblingsIterator->getSiblings();
            }

            cout << endl;

            i++;
            childIterator = childIterator->getChild();
        }

        rootIterator++;
    }

    cout << "-------------------------------------" << endl;
}
