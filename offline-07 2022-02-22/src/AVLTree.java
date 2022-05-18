import static java.lang.Math.max;

public class AVLTree {
    private Node root;

    public AVLTree() {
        this.root = null;
    }

    public Node getRoot() {
        return root;
    }

    public Node getMinItem() {
        return getMinItem(root);
    }

    private Node getMinItem(Node currentNode) {
        while(currentNode.getLeft() != null) {
            currentNode = currentNode.getLeft();
        }
        return currentNode;
    }

    public Node getMaxItem() {
        return getMaxItem(root);
    }

    private Node getMaxItem(Node currentNode) {
        while(currentNode.getRight() != null) {
            currentNode = currentNode.getRight();
        }
        return currentNode;
    }

    int calculateHeight(Node node) {
        if (node == null)
            return -1;
        else
            return node.getHeight();
    }

    private int getBalance(Node node) {
        if (node == null)
            return 0;
        else
            return calculateHeight(node.getLeft()) - calculateHeight(node.getRight());
    }

    private Node rightRotate(Node y) {
        Node x = y.getLeft();
        Node temp = x.getRight();

        x.setRight(y);
        y.setLeft(temp);

        y.setHeight(1 + max(calculateHeight(y.getLeft()), calculateHeight(y.getRight())));
        x.setHeight(1 + max(calculateHeight(x.getLeft()), calculateHeight(x.getRight())));

        return x;
    }

    private Node leftRotate(Node x) {
        Node y = x.getRight();
        Node temp = y.getLeft();

        y.setLeft(x);
        x.setRight(temp);

        x.setHeight(1 + max(calculateHeight(x.getLeft()), calculateHeight(x.getRight())));
        y.setHeight(1 + max(calculateHeight(y.getLeft()), calculateHeight(y.getRight())));

        return y;
    }

    public void insertItem(Node newNode) {
        root = insertItem(root, newNode);
    }

    private Node insertItem(Node currentNode, Node newNode){
        if(currentNode == null) {
            return newNode;
        }
        if(newNode.getValue() < currentNode.getValue()) {
            currentNode.setLeft(insertItem(currentNode.getLeft(), newNode));
        } else if(newNode.getValue() > currentNode.getValue()) {
            currentNode.setRight(insertItem(currentNode.getRight(), newNode));
        } else {
            return currentNode;
        }

        currentNode.setHeight(1 + max(calculateHeight((currentNode.getLeft())), calculateHeight(currentNode.getRight())));

        int balance = getBalance(currentNode);

        if (balance > 1 && newNode.getValue() < currentNode.getLeft().getValue()) {
            System.out.print("Height invariant violated.\n" + "After rebalancing: ");
            return rightRotate(currentNode);
        }

        if (balance < -1 && newNode.getValue() > currentNode.getRight().getValue()) {
            System.out.print("Height invariant violated.\n" + "After rebalancing: ");
            return leftRotate(currentNode);
        }

        if (balance > 1 && newNode.getValue() > currentNode.getLeft().getValue()) {
            System.out.print("Height invariant violated.\n" + "After rebalancing: ");
            currentNode.setLeft(leftRotate(currentNode.getLeft()));
            return rightRotate(currentNode);
        }

        if (balance < -1 && newNode.getValue() < currentNode.getRight().getValue()) {
            System.out.print("Height invariant violated.\n" + "After rebalancing: ");
            currentNode.setRight(rightRotate(currentNode.getRight()));
            return leftRotate(currentNode);
        }

        return currentNode;
    }

    public boolean searchItem(Node findNode) {
        return searchItem(findNode, root);
    }

    private boolean searchItem(Node findNode, Node currentNode) {
        if(currentNode == null) {
            return false;
        } else if(findNode.getValue() < currentNode.getValue()) {
            return searchItem(findNode, currentNode.getLeft());
        } else if(findNode.getValue() > currentNode.getValue()) {
            return searchItem(findNode, currentNode.getRight());
        } else {
            return true;
        }
    }

    public int getItemDepth(Node findNode) {
        return getItemDepth(findNode, root, 0);
    }

    private int getItemDepth(Node findNode, Node currentNode, int currentDepth) {
        if (currentNode == null) {
            return -1;
        } else if (findNode.getValue() < currentNode.getValue()) {
            return getItemDepth(findNode, currentNode.getLeft(), currentDepth + 1);
        } else if (findNode.getValue() > currentNode.getValue()) {
            return getItemDepth(findNode, currentNode.getRight(), currentDepth + 1);
        } else {
            return currentDepth;
        }
    }

    public int getHeight() {
        return getHeight(root);
    }

    private int getHeight(Node currentNode) {
        if(currentNode == null || currentNode.isLeaf()) {
            return 0;
        } else {
            return 1 + max(getHeight(currentNode.getLeft()), getHeight(currentNode.getRight()));
        }
    }

    public int getSize() {
        return getSize(root);
    }

    private int getSize(Node currentNode) {
        if(currentNode == null) {
            return 0;
        } else {
            return 1 + getSize(currentNode.getLeft()) + getSize(currentNode.getRight());
        }
    }

    public void printNestedParenthesis() {
        printNestedParenthesis(root);
        System.out.println();
    }

    private void printNestedParenthesis(Node currentNode) {
        if(currentNode == null) {
            return;
        }
        System.out.print(currentNode.getValue());
        if (currentNode.isLeaf()) return;
        System.out.print("(");
        printNestedParenthesis(currentNode.getLeft());
        System.out.print(")(");
        printNestedParenthesis(currentNode.getRight());
        System.out.print(")");
    }

    public void printInOrder() {
        printInOrder(root);
    }

    private void printInOrder(Node currentNode) {
        if(currentNode == null) {
            return;
        }
        printInOrder(currentNode.getLeft());
        System.out.print(currentNode.getValue() + " ");
        printInOrder(currentNode.getRight());
    }

    public void printPreOrder() {
        printPreOrder(root);
    }

    private void printPreOrder(Node currentNode) {
        if(currentNode == null) {
            return;
        }
        System.out.print(currentNode.getValue() + " ");
        printPreOrder(currentNode.getLeft());
        printPreOrder(currentNode.getRight());
    }

    public void printPostOrder() {
        printPostOrder(root);
    }

    private void printPostOrder(Node currentNode) {
        if(currentNode == null) {
            return;
        }
        printPostOrder(currentNode.getLeft());
        printPostOrder(currentNode.getRight());
        System.out.print(currentNode.getValue() + " ");
    }

    public Node getInOrderSuccessor(Node node) {
        Node currentNode = root;
        Node lastLeftTurn = null;
        while(currentNode != null) {
            if(node.getValue() < currentNode.getValue()) {
                lastLeftTurn = currentNode;
                currentNode = currentNode.getLeft();
            } else if(node.getValue() > currentNode.getValue()) {
                currentNode = currentNode.getRight();
            } else { //matched
                if(currentNode.getRight() != null) {
                    return getMinItem(currentNode.getRight());
                } else {
                    return lastLeftTurn;
                }
            }
        }
        return null; // no successor
    }

    public Node getInOrderPredecessor(Node node) {
        Node currentNode = root;
        Node lastRightTurn = null;
        while(currentNode != null) {
            if(node.getValue() < currentNode.getValue()) {
                currentNode = currentNode.getLeft();
            } else if(node.getValue() > currentNode.getValue()) {
                lastRightTurn = currentNode;
                currentNode = currentNode.getRight();
            } else {
                if(currentNode.getLeft() != null) {
                    return getMaxItem(currentNode.getLeft());
                } else {
                    return lastRightTurn;
                }
            }
        }
        return null;
    }

    public void deleteItem(Node deleteNode) {
        root = deleteItem(root, deleteNode);
    }

    private Node deleteItem(Node currentNode, Node deleteNode) {
        if (currentNode == null)
            return currentNode;

        if (deleteNode.getValue() < currentNode.getValue())
            currentNode.setLeft(deleteItem(currentNode.getLeft(), deleteNode));

        else if (deleteNode.getValue() > currentNode.getValue())
            currentNode.setRight(deleteItem(currentNode.getRight(), deleteNode));

        else
        {

            if ((currentNode.getLeft() == null) || (currentNode.getRight() == null))
            {
                Node temp = null;
                if (temp == currentNode.getLeft())
                    temp = currentNode.getRight();
                else
                    temp = currentNode.getLeft();

                if (temp == null)
                {
                    currentNode = null;
                }
                else
                    currentNode = temp;
            }
            else
            {

                Node temp = getMinItem(currentNode.getRight());
                currentNode.setValue(temp.getValue());
                currentNode.setRight(deleteItem(currentNode.getRight(), temp));
            }
        }

        if (currentNode == null)
            return currentNode;

        currentNode.setHeight(1 + max(calculateHeight(currentNode.getLeft()), calculateHeight(currentNode.getRight())));

        int balance = getBalance(currentNode);

        if (balance > 1 && getBalance(currentNode.getLeft()) >= 0) {
            System.out.print("Height invariant violated.\n" + "After rebalancing: ");
            return rightRotate(currentNode);
        }

        if (balance > 1 && getBalance(currentNode.getLeft()) < 0) {
            System.out.print("Height invariant violated.\n" + "After rebalancing: ");
            currentNode.setLeft(leftRotate(currentNode.getLeft()));
            return rightRotate(currentNode);
        }

        if (balance < -1 && getBalance(currentNode.getRight()) <= 0) {
            System.out.print("Height invariant violated.\n" + "After rebalancing: ");
            return leftRotate(currentNode);
        }

        if (balance < -1 && getBalance(currentNode.getRight()) > 0) {
            System.out.print("Height invariant violated.\n" + "After rebalancing: ");
            currentNode.setRight(rightRotate(currentNode.getRight()));
            return leftRotate(currentNode);
        }

        return currentNode;
    }
}
