
import java.util.Scanner;
import java.util.TreeSet;

public class Solution {

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int n = sc.nextInt();
        for (String s: genParens(n)) {
            System.out.println(s);
        }
    }

    private static TreeSet<String> genParens(int n) {
        TreeSet<String> retVal = new TreeSet<>();

        if (n == 0)
            retVal.add("");
        else{

            for(String s: genParens(n - 1)) {

                String temp = "(" + s;

                for (int i = 1; i <= temp.length(); i++) {

                    String newString = temp.substring(0, i) + ")" + temp.substring(i);

                    if (!retVal.add(newString))
                        break;
                }
            }
        }
        return retVal;
    }
}

/*
{
        TreeSet<String> retVal=new..
        if(n==0){
            retVal.add("");
            return retVal;
        }
        for(int i=0;i<n; i++){
            for(String left:getParens(i)){
                for(String right:getParens(i){
                    retVal.add("("+left+")"+right);
                }


        }
            return retVal;
        }
}

*/








