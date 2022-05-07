import java.io.*;
import java.util.*;

public class Solution {
    
    public static class TreeUnbalancedException extends Exception {
        private static final long serialVersionUID = 1L;

        public TreeUnbalancedException(String message) {
            super(message);
        }
    }
    
    
    public static class Node {
        int id = -1, w = -1, id_l = -1, d_l = -1, id_r = -1, d_r = -1;
        int w_t = -1;
    }
    
    
    public static Node createNode(String input) {
        String[] arr = input.split(" ");
        
        Node n = new Node();
        n.id   = Integer.parseInt(arr[0]);
        n.w    = Integer.parseInt(arr[1]);
        n.id_l = Integer.parseInt(arr[2]);
        n.d_l  = Integer.parseInt(arr[3]);
        n.id_r = Integer.parseInt(arr[4]);
        n.d_r  = Integer.parseInt(arr[5]);
        
        return n;
    }
    
    
    public static int calcWeights(TreeMap<Integer, Node> nodes, Node n)
        throws TreeUnbalancedException
    {
        if (n.w_t == -1) {
            
            int w_lst = n.id_l == -1 ? 0 : calcWeights(nodes, nodes.get(n.id_l));
            int w_rst = n.id_r == -1 ? 0 : calcWeights(nodes, nodes.get(n.id_r));
            
            int t_lst = n.d_l * w_lst;
            int t_rst = n.d_r * w_rst;
            
            n.w_t = n.w + w_lst + w_rst;
            
            // System.out.println("id = " + n.id + ", w_t = " + n.w_t + "\n" + 
            //                    "\tid_l = " + n.id_l + ", id_r = " + n.id_r + "\n" + 
            //                    "\tw_lst = " + w_lst + ", w_rst = " + w_rst + "\n" + 
            //                    "\tt_lst = " + t_lst + ", t_rst = " + t_rst);
            
            
            // stop processing when an unbalanced tree is found
            if (t_lst != t_rst) throw new TreeUnbalancedException("Tree is not balanced at node " + n.id);
            
        }
        
        return n.w_t;
    }
    
    

    public static void main(String[] args) {
        
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        TreeMap<Integer, Node> nodes = new TreeMap<>();
        String input;
        Node n;
        
        boolean balanced = true;
        
        try {
            
            // read input
            while((input = reader.readLine()) != null) {
                n = createNode(input);
                nodes.put(n.id, n);
            }
            
            // calculate weights and check for balance
            for (Map.Entry<Integer, Node> entry : nodes.entrySet()) {
                calcWeights(nodes, entry.getValue());
            }
            
        } catch (IOException e) {
            e.printStackTrace();
        } catch (TreeUnbalancedException e) {
            e.printStackTrace();
            balanced = false;
        }
        
        if (balanced) System.out.println("Balanced");
        else System.out.println("Unbalanced");
        
    }
}

