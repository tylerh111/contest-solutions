
import java.util.*;

class Graph{
    private Set<String> vertexSet = new TreeSet<>();
    private Map<String, HashSet<String>> neighborMap = new HashMap<>();

    public Set<String> vertexSet() {
        return vertexSet;
    }

    public Set<String> neighborsOf(String vertex) {
        if (!neighborMap.containsKey(vertex)) {
            neighborMap.put(vertex, new HashSet<String> ());
        }
        return neighborMap.get(vertex);
    }

    public void addVertex(String vertex) {
        vertexSet.add(vertex);
    }

    public void addEdge(String fromVertex, String toVertex, boolean bidirectional) {
        vertexSet.add(fromVertex);
        vertexSet.add(toVertex);

        if (!neighborMap.containsKey(fromVertex)) {
            neighborMap.put(fromVertex, new HashSet<String> ());
        }
        neighborMap.get(fromVertex).add(toVertex);

        if (bidirectional) addEdge(toVertex, fromVertex, false);
    }

    public boolean isAdjacent(String vertex, String potentialNeighbor) {
        return neighborMap.containsKey(vertex) && neighborMap.get(vertex).contains(potentialNeighbor);
    }


    public boolean BreadthFirstSearch(String search){

        Queue<String> q = new ArrayDeque<>();
        Set<String> v = new HashSet<>();

        q.add(search);
        v.add(search);

        if (search.equals("San_Jose")) return true;

        while (!q.isEmpty()){

            String curr = q.remove();

            for (String s : neighborsOf(curr)){
                if (s.equals("San_Jose")) return true;

                if (!v.contains(s)){
                    q.add(s);
                    v.add(s);
                }
            }
        }

        return false;
    }




}




public class Solution {


    public static void main(String[] args){

        Scanner sc = new Scanner(System.in);
        Graph graph = new Graph();

        int n = sc.nextInt();

        for(int i = 0; i < n; i++){
            String from = sc.next();
            String to = sc.next();

            graph.addEdge(from, to, true);
        }

        int t = sc.nextInt();

        for (int i = 0; i < t; i++){
            String search = sc.next();
            if(graph.BreadthFirstSearch(search)) System.out.println("Yes");
            else System.out.println("No");

        }



    }
    

}

