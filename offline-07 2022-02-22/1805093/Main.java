import java.io.*;
import java.util.Objects;

public class Main {

    public static void main(String[] args) {
        AVLTree tree = new AVLTree();
        try {
            BufferedReader br = new BufferedReader(new FileReader("avl.txt"));

            String str;
            while ((str = br.readLine()) != null) {
                System.out.print(str + '\t');
                String[] currentInput = str.split(" ");

                if (Objects.equals(currentInput[0], "I")) {
                    tree.insertItem(new Node(Integer.parseInt(currentInput[1])));
                    tree.printNestedParenthesis();
                } else if (Objects.equals(currentInput[0], "F")) {
                    System.out.println(tree.searchItem(new Node(Integer.parseInt(currentInput[1]))));
                } else if (Objects.equals(currentInput[0], "D")) {
                    tree.deleteItem(new Node(Integer.parseInt(currentInput[1])));
                    tree.printNestedParenthesis();
                }
            }
        } catch (Exception e) {
            e.printStackTrace();
        }

        System.out.println("Finally the tree is now -");
        tree.printNestedParenthesis();
    }
}
