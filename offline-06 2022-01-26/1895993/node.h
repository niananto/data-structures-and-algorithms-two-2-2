class Node
{
    int value, degree;
    Node *child, *siblings, *parent;
    // Node *next;

public:
    Node(){
        value = 0;
        degree = 0;
        child = nullptr;
        siblings = nullptr;
        parent = nullptr;
    }

    // Node(int val){
    //     value = val;
    //     degree = 0;
    //     child = nullptr;
    //     siblings = nullptr;
    //     parent = nullptr;
    // }

    ~Node(){
        delete [] child;
        delete [] siblings;
        delete [] parent;
    }

    friend Node* createNode(int val);
    friend Node* mergeBinomialTrees(Node* head1, Node* head2);
    // friend;

    void setValue(int value){
        this->value = value;
    }

    // void setDegree(int degree){
    //     this->degree = degree;
    // }

    // void setChild(Node* child){
    //     this->child= child;
    // }

    // void setParent(Node* parent){
    //     this->parent = parent;
    // }

    void setSiblings(Node* siblings){
        this->siblings = siblings;
    }

    int getValue(){
        return value;
    }

    int getDegree(){
        return degree;
    }

    Node* getChild(){
        return child;
    }

    Node* getParent(){
        return parent;
    }

    Node* getSiblings(){
        return siblings;
    }
};

Node* createNode(int val){
    Node* newNode = new Node;
    newNode->value = val;
    newNode->degree = 0;
    newNode->child = nullptr;
    newNode->siblings = nullptr;
    newNode->parent = nullptr;

    return newNode;
}

Node* mergeBinomialTrees(Node* big, Node* small){
    small->parent = big;
    small->siblings = big->child;
    big->child = small;
    big->degree++;
    
    return big;
}