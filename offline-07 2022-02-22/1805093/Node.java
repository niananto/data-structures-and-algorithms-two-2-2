public class Node {
    private Node left;
    private Node right;
    private int value;
    private int height;

    public Node(int value) {
        left = null;
        right = null;
        this.value = value;
        this.height = 0;
    }

    public int getValue() {
        return value;
    }

    public Node getLeft() {
        return left;
    }

    public Node getRight() {
        return right;
    }

    public void setLeft(Node left) {
        this.left = left;
    }

    public void setRight(Node right) {
        this.right = right;
    }

    public void setValue(int value) {
        this.value = value;
    }

    public int getHeight() {
        return height;
    }

    public void setHeight(int height) {
        this.height = height;
    }

    public boolean isLeaf() {
        return (left == null && right == null);
    }
}
