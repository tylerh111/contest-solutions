
import java.util.Scanner;


public class Solution {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) 
    {
        int row = 8;
        int col = 8;
        
        int queenCount = 0;
        
        char[][] array = new char[row][col];
        
        Scanner sc = new Scanner(System.in);
        
        String line;
        
        for (int i = 0; i < row; i++)
        {
            line = sc.next();
            for (int j = 0; j < col; j++)
            {    
                array[i][j] = line.charAt(j);
                if (array[i][j] == '*')
                    queenCount++;
            }
        }
        
        if (queenCount != 8)
            System.out.println("invalid");
        else
        {
            for (int i = 0; i < row; i++)
            {
                for (int j = 0; j < col; j++)
                {    
                    if(array[i][j] == '*')
                    {
                        for(int x = i + 1; x < 8; x++)
                        {
                            if (array[x][j] == '*')
                            {
                                System.out.println("invalid");
                                System.exit(0);
                            }
                        }
                        
                        for(int x = i - 1; x >= 0; x--)
                        {
                            if (array[x][j] == '*')
                            {
                                System.out.println("invalid");
                                System.exit(0);
                            }
                        }
                        
                        for(int x = j + 1; x < 8; x++)
                        {
                            if (array[i][x] == '*')
                            {
                                System.out.println("invalid");
                                System.exit(0);
                            }
                        }
                        
                        for(int x = j - 1; x >= 0; x--)
                        {
                            if (array[i][x] == '*')
                            {
                                System.out.println("invalid");
                                System.exit(0);
                            }
                        }
                        
                        for(int x = i - 1, y = j - 1; x >= 0 && y >= 0; x--, y--)
                        {
                            if (array[x][y] == '*')
                            {
                                System.out.println("invalid");
                                System.exit(0);
                            }
                        }
                        
                        for(int x = i - 1, y = j + 1; x >= 0 && y < 8; x--, y++)
                        {
                            if (array[x][y] == '*')
                            {
                                System.out.println("invalid");
                                System.exit(0);
                            }
                        }
                        
                        for(int x = i + 1, y = j - 1; x < 8 && y >= 0; x++, y--)
                        {
                            if (array[x][y] == '*')
                            {
                                System.out.println("invalid");
                                System.exit(0);
                            }
                        }
                        
                        for(int x = i + 1, y = j + 1; x < 8 && y < 8; x++, y++)
                        {
                            if (array[x][y] == '*')
                            {
                                System.out.println("invalid");
                                System.exit(0);
                            }
                        }
                    }
                }
            }
            System.out.println("valid");
        }
    }
    
}
