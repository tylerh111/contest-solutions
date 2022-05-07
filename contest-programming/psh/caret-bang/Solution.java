import java.util.*;

public class Solution {

    public static void main(String[] args) {

        Scanner sc = new Scanner(System.in);

        int start = 0;
        int bit = 0;
        String[] board = new String[4];
        for (int i = 0; i < 4; i++) {
            board[i] = sc.next();

            do {
                if (board[i].charAt(bit % 5) == 't')
                    start += (1 << bit);
                bit++;
            } while(bit % 5 != 0);
        }

        int target = 0;
        bit = 0;
        for (int i = 0; i < 4; i++) {
            board[i] = sc.next();

            do {
                if (board[i].charAt(bit % 5) == 't')
                    target += (1 << bit);
                bit++;
            } while(bit % 5 != 0);
        }

        int[] end = solve(start, target);

        if (end == null) System.out.println("Impossible");
        else {
            int endSize = end.length;

            System.out.println(endSize);
            System.out.println();

            for (int i = endSize - 1; i >= 0; i--) {
                System.out.println(outputBoardForm(end[i]));
            }

        }


    }

    private static int[] solve (int start, int target){

        //map
        int[] m = new int [1048576];
        //visited
        boolean[] b = new boolean[1048576];
        m[start] = start;
        b[start] =true;

        //queue
        int[] q = new int [10000000];
        q[0] = start;
        int f = 0;
        int e = 0;
        int size = 1;

        //used for how many times needed to iterate through queue
        int depth = 0;
        int branches = 1;
        int branchesNext = 0;

        //breadth first search
        //only time f == e is  when array is empty
        while (size != 0) {

            //int curr = queue.removeLast();
            int curr = q[f];
            size--;
            if (size != 0) f++;

            //recalculates depth while iterating through the queue
            if (branches == 0){
                depth++;
                branches = branchesNext;
                branchesNext = 0;
            }

            //if curr is the goooooaaal, then return curr
            if (curr == target){

                int[] ret = new int[depth];
                int nextToVisit = curr;

                for (int i = 0; i < depth; i++) {
                    ret[i] = nextToVisit;
                    //nextToVisit = map.get(nextToVisit);
                    nextToVisit = m[nextToVisit];
                }

                return ret;

            }

            //finds all one step extensions of curr
            for (int child : moveList(curr)){
                //if child x,y != T,F and child does not exist in the map
                if (child != -1 && !b[child]){
                    m[child] = curr;
                    b[child] = true;
                    q[e] = child;
                    e++;
                    size++;
                    if (e == q.length)
                        q = adjustSize(q);
                    branchesNext++;
                }
            }
            branches--;
        }
        return null;
    }


    private static int[] adjustSize(int[] oldA){
        int[] newA = new int[oldA.length * 10];

        for (int i = 0; i < oldA.length; i++){

            newA[i] = oldA[i];

        }
        return newA;
    }


    private static int[] moveList(int node){

        int[] ret = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};

        for (int i = 0; i < 31; i++){

            boolean x, y;
            int xBit, yBit;

            //finds bits and values for x and y
            if (i < 16) {
                xBit = 1 << ((i % 4) + ((i / 4) * 5));
                yBit = 1 << (((i % 4) + ((i / 4) * 5)) + 1);

                x = (node & xBit) == xBit;
                y = (node & yBit) == yBit;
            }
            else {
                xBit = 1 << (i % 16);
                yBit = 1 << ((i % 16) + 5);

                x = (node & xBit) == xBit;
                y = (node & yBit) == yBit;
            }

            ret[i] = node;

            //sets new x and y (x' = x ^ y and y' = !x)
            if (x && y) // TT -> FF
                ret[i] &= ~(xBit | yBit);
            else if (!x && !y) // FF -> FT
                ret[i] |= yBit;
            else if (!x) // FT -> TT
                ret[i] |= xBit;
            else
                ret[i] = -1;
        }

        return ret;
    }


    private static String outputBoardForm(int node){

        StringBuffer ret = new StringBuffer();

        for (int i = 0; i < 20; i++){
            ret.append(((node & (1 << i)) == (1 << i)) ? 't' : 'f');

            if (i % 5 == 4)
                ret.append("\n");
        }

        return ret.toString();
    }


}
