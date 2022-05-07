
import java.util.*;
import java.io.*;

public class Solution {


    public static void main(String[] args){


        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));

        int col;
        int row;

        int characters;

        char input;
        String[] ascii;


        Map<Character, String[]> map = new HashMap<>();



        try{

            col = Integer.valueOf(reader.readLine());
            row = Integer.valueOf(reader.readLine());

            characters = Integer.valueOf(reader.readLine());

            for (int i = 0; i < characters; i++){

                input = (char) reader.read();

                ascii = new String[row];

                reader.readLine();


                for (int j = 0; j < row; j++){
                    ascii[j] = reader.readLine();
                }

                map.put(input, ascii);
            }

            int l = Integer.valueOf(reader.readLine());

            for (int i = 0; i < l; i++){
                String toBePrinted = reader.readLine();
                int charAmount = toBePrinted.length();

                //for each row
                for (int j = 0; j < row; j++) {
                    for (int k = 0; k < charAmount; k++) {
                        System.out.print(map.get(toBePrinted.charAt(k))[j]);
                    }
                    System.out.println();
                }
            }

        }
        catch(Exception e){
            e.toString();
        }


    }

}

