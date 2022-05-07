
import java.util.*;
import java.io.*;
import java.lang.*;

class DisjointSet{
	
	int[] sets;
	
	public DisjointSet(int n){
		sets = new int[n+1];
	}
	
	public void checkIndex(int x){
		if (x < 1 || x >= sets.length) throw new IndexOutOfBoundsException();
	}
	
	public void makeSet (int x){
		//checkIndex(x);
		if (sets[x] != 0) return;
		sets[x] = -1;
	}
	
	public int find (int x){
		//checkIndex(x);
		if (x < 1 || x >= sets.length || sets[x] == 0) return 0;
		
		//implement function recursively
		if (sets[x] < 0) return x;
		int root = find(sets[x]);
		sets[x] = root;
		return root;
	}
	
	public void union(int x, int y){
		//checkIndex(x);
		//checkIndex(y);
		if (x < 1 || x >= sets.length || y < 1 || y >= sets.length || sets[x] >= 0 || sets[y] >= 0 || x == y)
			return;
		if (x > y){ // y becomes parent
			sets[y] += sets[find(x)];
			sets[x] = y;
		}
		else{ //x becomes parent
			sets[x] += sets[find(y)];
			sets[y] = x;
		}
	}
}



public class Solution {
	
	public static void main(String[] args){
		System.out.println(mysteriousMaze());
	}
	
	
	static int mysteriousMaze (){
		
		//Scanner sc = new Scanner(System.in);
		BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
		
		DisjointSet ds;
		Set<Integer> ends;
		
		try {
			int n = Integer.valueOf(reader.readLine());
			int counter = 0;
			
			int row, col, input;
			
			ds = new DisjointSet(n * n);
			ends = new HashSet<>(n);
			
			int lastRowBeg = ((n - 1) * n) + 1;
			int lastRowEnd = n * n;
			
			while (true) {
				
				String[] in = reader.readLine().split(" ");
				//row = sc.nextInt();
				//if (row == -1) break; //finished reading input
				//col = sc.nextInt();
				
				row = Integer.parseInt(in[0]);
				if (row == -1) break; //finished reading input
				col = Integer.parseInt(in[1]);
				
				
				//mapping (row, col) -> input
				input = n * (row - 1) + col;
				
				ds.makeSet(input);
				
				if (lastRowBeg <= input && input <= lastRowEnd) ends.add(input);
				
				
				//union neighbors if possible (if not at any edges)
				if (row != n) ds.union(ds.find(input), ds.find(input + n));
				if (col != n) ds.union(ds.find(input), ds.find(input + 1));
				if (col != 1) ds.union(ds.find(input), ds.find(input - 1));
				if (row != 1) ds.union(ds.find(input), ds.find(input - n));
				
				//check to see if there is any way to get to any end from any beginning
				for (int e : ends) {
					int find = ds.find(e);
					
					if (1 <= find && find <= n) return counter + 1;
				}
				
				counter++;
				
			}
		}
		catch(Exception e)
		{
			System.out.println(e.toString());
		}
		
		return -1;
	}
	
	
}

