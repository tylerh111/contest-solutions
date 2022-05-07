
import java.util.*;


public class Solution {

    static int[] A;
    static int[] B;

    static int[][][][] memo;
    static boolean[][][][] solved;

    public static void main(String[] args){

        Scanner sc = new Scanner(System.in);

        int n = sc.nextInt();

        A = new int[n << 1];
        B = new int[n << 1];

        memo = new int[n<<1][n<<1][n+1][3];
        solved = new boolean[n<<1][n<<1][n+1][3];

        for (int i = 0; i < n << 1; i++) A[i] = sc.nextInt();
        for (int i = 0; i < n << 1; i++) B[i] = sc.nextInt();

        System.out.println(pandora(n));

    }


    static long pandora(int n){
        return T (0, 0, n, 0);
    }

    static int T(int i, int j, int n, int s){

        if (n == 0) return 0;
        if (solved[i][j][n][s]) return memo[i][j][n][s];

        if (s > 0){
            int ret =  Math.max(T(i+1, j, n-1, s-1) + A[i], T(i, j+1, n-1, s-1) + B[j]);
            memo[i][j][n][s] = ret;
            solved[i][j][n][s] = true;
            return ret;
        }

        int ret = Math.max(Math.max(T(i+1, j, n-1, 0) + A[i], T(i, j+1, n-1, 0) + B[j]),
                           Math.max(T(i+2, j, n-1, 2) + A[i+1], T(i, j+2, n-1, 2) + B[j+1]));
        memo[i][j][n][s] = ret;
        solved[i][j][n][s] = true;
        return ret;
    }

}

