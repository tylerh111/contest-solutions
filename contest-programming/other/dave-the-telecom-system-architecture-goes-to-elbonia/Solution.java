import java.util.HashMap;
import java.util.HashSet;
import java.util.Map;
import java.util.Set;
import java.util.TreeSet;

import java.util.Scanner;

class Graph{
    public Set<String> vertexSet = new TreeSet<>();
    public Set<String> backbone = new TreeSet<>();
    public Set<String> notbackbone = new TreeSet<>();
    public Map<String, HashSet<String>> neighborMap = new HashMap<>();
    //private Map<String, HashSet<String>> backbone = new HashMap<>();

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

    public void addEdge(String fromVertex, String toVertex, boolean bidirectional, boolean bb) {
        vertexSet.add(fromVertex);
        vertexSet.add(toVertex);

        if (!neighborMap.containsKey(fromVertex)) {
            neighborMap.put(fromVertex, new HashSet<String> ());
        }
        neighborMap.get(fromVertex).add(toVertex);

        if (bb) backbone.add(fromVertex);
        else notbackbone.add(fromVertex);
        if (bidirectional) addEdge(toVertex, fromVertex, false, bb);
    }


    public boolean isAdjacent(String vertex, String potentialNeighbor) {
        return neighborMap.containsKey(vertex) && neighborMap.get(vertex).contains(potentialNeighbor);
    }



    public boolean isBackBoneConnected(){

        Set<String> visited = new HashSet<>();
        
        String start = backbone.iterator().next();

        traversal(start, visited);

        return visited.size() == backbone.size();
    }

    private void traversal(String v, Set<String> visited){
        
        visited.add(v);

        for (String w : neighborMap.get(v)){
            if (!visited.contains(w)){
                traversal(w, visited);
            }
        }
    }





}




public class Solution {

    public static void main(String[] args){

        Scanner sc = new Scanner(System.in);


        int k = sc.nextInt();
        int n = sc.nextInt();

        Graph g = new Graph();

        //create graph
        for (int i = 0; i < k; i++) g.addEdge(sc.next(), sc.next(), true, true);

        if (g.isBackBoneConnected()) {
            for (int i = 0; i < n; i++) g.addEdge(sc.next(), sc.next(), true, false);

            if (telecom(g)) System.out.println("valid");
            else System.out.println("invalid");
        }
        else System.out.println("invalid");
        
    }



    static boolean telecom(Graph g) {

        for (String s : g.notbackbone) {
            boolean tmp = false;

            for (String t : g.neighborMap.get(s)) {
                if (g.backbone.contains(t)) tmp = true;
            }

            if (!tmp) return false;
        }

        return true;
    }





}

