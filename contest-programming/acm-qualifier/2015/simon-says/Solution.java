
import java.io.*;


public class Solution {
	
	public static void main(String[] args){
		
		BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
		
		try{
			int n = Integer.valueOf(reader.readLine());
			
			for (int i = 0; i < n; i++){
				String in = reader.readLine();
				
				if (0 == in.indexOf("Simon says")){
					System.out.println(in.substring(10));
				}
			}
		}
		catch(Exception e){
			System.out.println(e.toString());
		}
		
	}
	
	
	
	
}

