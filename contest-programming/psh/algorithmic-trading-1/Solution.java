import java.io.*;
import java.util.*;
import java.text.*;
import java.math.*;
import java.util.regex.*;

public class Solution {
    
    public static int searchElement(int arr[], int low, int high, int key)
    {
        if (high < low)
            return -1;
        int mid = (low + high) / 2;
        if (key == arr[mid])
            return mid;
        if (key > arr[mid])
            return searchElement(arr, (mid + 1), high, key);
        return searchElement(arr, low, (mid - 1), key);
    }
    
    public static int insertElement(int arr[], int n, int key)
    {
        int i;
        for (i = n - 1; (i >= 0 && arr[i] > key); i--)
            arr[i + 1] = arr[i];
        
        arr[i + 1] = key;
        
        return n + 1;
    }
    
    public static int deleteElement(int arr[], int n, int key)
    {
        // Find position of element to be deleted
        int pos = searchElement(arr, 0, n - 1, key);
        
        if (pos == -1) {
            System.out.println("Element not found");
            return n;
        }
        
        // Deleting element
        int i;
        for (i = pos; i < n - 1; i++)
            arr[i] = arr[i + 1];
        
        return n - 1;
    }
    
    
    public static double getMedian(int arr[]) {
        double median;
        if (arr.length % 2 == 0)
            median = ((double)arr[arr.length/2] + (double)arr[arr.length/2 - 1])/2;
        else
            median = (double) arr[arr.length/2];
        return median;
    }
    
    
    public static void printArray(int arr[]) {
        System.out.print("[");
        for (int i = 0; i < arr.length; ++i)
            System.out.print(arr[i] + ", ");
        System.out.println("]");
    }
    
    
    
    public static void main(String[] args) throws IOException {
        // input reader
    	BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
    	
    	String[] tokens = reader.readLine().split(" ");
    	int n = Integer.valueOf(tokens[0]);
    	int m = Integer.valueOf(tokens[1]);

		// output writer
 		StringBuffer sbOut = new StringBuffer();
        
        int[] prices = new int[n+1];
        int[] latestPrices = new int[m];
        int latestPricesLen = 1;
        int oldestPriceNdx = 0;
        int oldestPrice;
        int latestPrice;
        
        for (int i = 1; i < m; ++i) {
            latestPrice = Integer.valueOf(reader.readLine());
            prices[i] = latestPrice;
            latestPricesLen = insertElement(latestPrices, latestPricesLen, latestPrice);
        }
        
        double median;
    	for (int i = m; i < n+1; ++i) {
            // update oldest price
            oldestPrice = prices[oldestPriceNdx++];
            
            // update latest price
            latestPricesLen = deleteElement(latestPrices, latestPricesLen, oldestPrice);
    		latestPrice = Integer.valueOf(reader.readLine());
            prices[i] = latestPrice;
            latestPricesLen = insertElement(latestPrices, latestPricesLen, latestPrice);
            
            // get solution
            median = getMedian(latestPrices);
            if      (median == latestPrice) sbOut.append("hold\n");
            else if (median < latestPrice) sbOut.append("buy\n");
            else if (median > latestPrice) sbOut.append("sell\n");
            
    	}
        
		// print output
        System.out.print(sbOut.toString());
    }
    
}
