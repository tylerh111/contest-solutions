import java.io.*;
import java.util.*;
import java.lang.*;

public class Solution {
    
    public static class NumDig implements Comparable<NumDig> {
        public static int n;
        public static int[] mod;
        
        public Integer num;
        public Integer[] dig;
        
        public NumDig(Integer num) {
            this.num = num;
            this.dig = getDigits(num);
        }
        
        public NumDig(Integer[] dig) {
            this.num = getNumber(dig);
            this.dig = new Integer[n];
            for (int i = 0; i < n; ++i)
                this.dig[i] = dig[i];
        }
        
        
        public static int getNumber(Integer[] digits) {
            int x = 0;
            for (int i = 0; i < n; ++i) {
                x += digits[i] * mod[i+1];
            }
            return x;
        }
        
        public static Integer[] getDigits(Integer number) {
            Integer[] digits = new Integer[n];
            for (int i = 0; i < n; ++i) {
                digits[i] = (number / mod[i+1]) % 10;
            }
            return digits;
        }
        
        
        public void print() {
            System.out.print(num + ", ");
            for (int i = 0; i < n; ++i)
                System.out.print(dig[i]);
            System.out.println();
        }

        
        @Override 
        public boolean equals(Object other) {
            if (!(other instanceof NumDig))
                return false;
            
            return num == ((NumDig) other).num;
        }

        @Override 
        public int hashCode() {
            return num;
        }

        @Override 
        public int compareTo(NumDig other) {
            if (num < other.num) return -1;
            if (num == other.num) return 0;
            return 1;
        }
        
    }
    
    
    public static NumDig getNumDig(NumDig[] numbers, Integer num) {
        if (numbers[num] != null) return numbers[num];
        numbers[num] = new NumDig(num);
        return numbers[num];
    }
    
    public static NumDig getNumDig(NumDig[] numbers, Integer[] dig) {
        NumDig s = new NumDig(dig);
        numbers[s.num] = s;
        return s;
    }
    
    
    public static boolean findTarget(int n, int start, int target, Integer[][] memo, 
                                     NumDig[] numbers, TreeSet<Integer> forbidden) 
    {
        NumDig s = new NumDig(start);
        
        Queue<NumDig> queue = new LinkedList();
        queue.add(s);
        
        if (forbidden.contains(s.num)) return false;
        if (s.num == target) return true;
        
        while(!queue.isEmpty()) {
            s = queue.remove();
            // s.print();
            if (s.num == target) return true;
            
            for (int i = 0; i < 2*n; ++i) {
                int m = i%n;
                if (i < n) s.dig[m] = (s.dig[m] + 1) % 10;
                else s.dig[m] = (s.dig[m] + 9) % 10;
                
                NumDig x = getNumDig(numbers, s.dig);
                
                if (memo[x.num][0] == null && !forbidden.contains(x.num)) {
                    memo[s.num][0] = x.num;
                    memo[s.num][1] = 0;
                    memo[s.num][2] = (m)+1;
                    queue.add(x);
                }
                
                if (i < n) s.dig[m] = (s.dig[m] + 9) % 10;
                else s.dig[m] = (s.dig[m] + 1) % 10;
            }
            
        }
        
        return false;
    }
    
    
    public static void printSolution(int start, int target, Integer[][] memo) 
        throws IOException 
    {
        BufferedWriter writer = new BufferedWriter(new OutputStreamWriter(System.out));
        
        int count = 0;
        int s = start;
        while (s != target) {
            System.out.println(memo[s][0]);
            // direction
            if (memo[s][1] == 0) writer.write('D');
            else writer.write('U');
            
            // digit
            writer.write(memo[s][2]);
            writer.write(' ');
            
            // number
            writer.write(memo[s][0]);
            writer.write('\n');
            
            s = memo[s][0];
            count++;
        }
        
        System.out.println(count);
        writer.flush();
    }
    
    
    public static void main(String[] args) {
        
        try (BufferedReader reader = new BufferedReader(
                new InputStreamReader(System.in))) {
            
            int n = Integer.parseInt(reader.readLine());
            NumDig.n = n;
            NumDig.mod = new int[n+1];
            for (int i = 0; i <= n; ++i)
                NumDig.mod[i] = (int) Math.pow(10, n-i);
            
            int start = Integer.parseInt(reader.readLine());
            int target = Integer.parseInt(reader.readLine());
            
            NumDig[] numbers = new NumDig[(int) Math.pow(10,n)];
            numbers[start] = new NumDig(start);
            numbers[target] = new NumDig(target);

            int f = Integer.parseInt(reader.readLine());
            TreeSet<Integer> forbidden = new TreeSet();
            for (; f > 0; --f) {
                int num = Integer.parseInt(reader.readLine());
                numbers[num] = new NumDig(num);
                forbidden.add(num);
            }
            
            if (forbidden.contains(start) || forbidden.contains(target))
                System.out.println(-1);
            
            // memo[i] := next, direction, digit
            // direction := 0 is down, 1 is up
            Integer[][] memo = new Integer[(int) Math.pow(10,n)][3];
            boolean pathFound = findTarget(n, start, target, memo, numbers, forbidden);
            
            if (pathFound)
                printSolution(start, target, memo);
            else
                System.out.println(-1);
        }
        catch (IOException e) {
            e.printStackTrace();
        }
        
    }
}