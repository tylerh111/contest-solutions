import java.io.*;
import java.util.*;
import java.text.*;
import java.math.*;
import java.util.regex.*;

public class Solution {
    
    public static Set<String> validChoices;
    
    static {
        validChoices = new HashSet<String>();
        validChoices.add("Rock");
        validChoices.add("Paper");
        validChoices.add("Scissors");
        validChoices.add("Lizard");
        validChoices.add("Spock");
    }
    
    
    public static boolean isChoiceValid(String c) {
        return validChoices.contains(c);
    }
    
    /**
     * solve figures out who the winner is.
     *
     * @return is the winner, 1 for player 1 and 2 for player 2
     **/
    public static int solve(String p1, String c1, String p2, String c2) {
        
        boolean c1_valid = isChoiceValid(c1);
        boolean c2_valid = isChoiceValid(c2);
        
        if (c1_valid && !c2_valid) return 1;
        if (!c1_valid && c2_valid) return 2;
        if (!c1_valid && !c2_valid) // both invalid
            return (p1.compareToIgnoreCase(p2) < 0) ? 2 : 1;
        if (c1_valid && c2_valid && c1.equals(c2)) //tie
            return (p1.compareToIgnoreCase(p2) < 0) ? 1 : 2;
        
        switch(c1) {
            case "Rock":
                switch(c2) {
                    case "Paper": return 2;
                    case "Scissors": return 1;
                    case "Lizard": return 1;
                    case "Spock": return 2;
                }
            case "Paper":
                switch(c2) {
                    case "Rock": return 1;
                    case "Scissors": return 2;
                    case "Lizard": return 2;
                    case "Spock": return 1;
                }
            case "Scissors":
                switch(c2) {
                    case "Rock": return 2;
                    case "Paper": return 1;
                    case "Lizard": return 1;
                    case "Spock": return 2;
                }
            case "Lizard":
                switch(c2) {
                    case "Rock": return 2;
                    case "Paper": return 1;
                    case "Scissors": return 2;
                    case "Spock": return 1;
                }
            case "Spock":
                switch(c2) {
                    case "Rock": return 1;
                    case "Paper": return 2;
                    case "Scissors": return 1;
                    case "Lizard": return 2;
                }
        }
        
        return 0;
    }
    

    public static void main(String[] args) {
        
        String p1, c1, p2, c2;
        
        Scanner scanner = new Scanner(System.in);
        
        while(scanner.hasNext()) {
            p1 = scanner.next();
            c1 = scanner.next();
            p2 = scanner.next();
            c2 = scanner.next();
            
            int winner = solve(p1, c1, p2, c2);
            if (winner == 1) System.out.print(p1);
            if (winner == 2) System.out.print(p2);
            System.out.println(" wins!");
            
        }
        
        
    }
    
    
}