import java.util.Iterator;
import java.util.LinkedList;
import java.util.Scanner;

public class Graph2 {

    private static int V;
    private static LinkedList<Integer> adjacency[];

    Graph2(int v) {
        V = v;
        adjacency = new LinkedList[v];

        for (int i = 0; i < v; ++i) {
            adjacency[i] = new LinkedList();
        }
    }

    void addEdge(int v1, int v2) {
        adjacency[v1].add(v2);
    }


    public static boolean BFS(int v) {
        boolean visit[] = new boolean[V];
        LinkedList<Integer> queue = new LinkedList<>();

        visit[v] = true;
        queue.add(v);

        while (queue.size() != 0) {
            v = queue.poll();


            Iterator<Integer> iterator = adjacency[v].listIterator();
            while (iterator.hasNext()) {
                int n = iterator.next();
                if(visit[n]) return false;
                if(!visit[n]) {
                    visit[n] = true;
                    queue.add(n);
                }
            }
        }
        return true;
    }



    public static void main(String[] args) {

        Scanner scanner=new Scanner(System.in);
        int n = scanner.nextInt();
        int m = scanner.nextInt();
        Graph2 g = new Graph2(n);

        for(int i=0;i<m;i++){
            int u=scanner.nextInt();
            int v=scanner.nextInt();
            g.addEdge(u,v);
        }

        boolean yesno = true;

        for(int i=0;i<n;i++){

            yesno = BFS(i);
            if(yesno == false){
                System.out.println(i);
                break;
            }
        }

        if(yesno == true) System.out.println("YES");
        else System.out.println("NO");
    }
}
