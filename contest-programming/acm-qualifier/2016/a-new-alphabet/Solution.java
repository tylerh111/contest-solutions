import java.io.*;
import java.util.*;

public class Solution {
	
	public static void main(String[] args)
	{
		HashMap<Character, String> hmap = new HashMap<>();
		hmap.put('a',"@");
		hmap.put('b', "8");
		hmap.put('c',"(");
		hmap.put('d', "|)");
		hmap.put('e',"3");
		hmap.put('f', "#");
		hmap.put('g',"6");
		hmap.put('h', "[-]");
		hmap.put('i',"|");
		hmap.put('j', "_|");
		hmap.put('k',"|<");
		hmap.put('l', "1");
		hmap.put('m',"[]\\/[]");
		hmap.put('n', "[]\\[]");
		hmap.put('o',"0");
		hmap.put('p', "|D");
		hmap.put('q',"(,)");
		hmap.put('r', "|Z");
		hmap.put('s',"$");
		hmap.put('t', "']['");
		hmap.put('u',"|_|");
		hmap.put('v', "\\/");
		hmap.put('w',"\\/\\/");
		hmap.put('x', "}{");
		hmap.put('y',"`/");
		hmap.put('z', "2");
		
		BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
		String info = null;
		
		try{
			info = reader.readLine();
		} catch (Exception e){
			System.out.println(e.toString());
		}
		
		StringBuffer sb = new StringBuffer();
		
		for (char c : info.toCharArray()){
			if (65 <= c && c <= 90){
				sb.append(hmap.get((char) (c + 32)));
			}
			else if (97 <= c && c <= 122){
				sb.append(hmap.get(c));
			}
			else{
				sb.append(c);
			}
		}
		
		
		System.out.println(sb.toString());
		
	}
}
