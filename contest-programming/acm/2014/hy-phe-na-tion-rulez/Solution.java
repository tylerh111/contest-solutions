import java.util.Scanner;


public class Solution {

  public static void main(String[] args) {
    Scanner sc = new Scanner(System.in);
    String word;
    while (!(word = sc.next()).equals("===")) {
      int state = 1;
      Token pending = null;
      while (word.length() > 0) {
        Token token = new Token(word);
        word = word.substring(token.value.length());
        switch (state) {
        case 1:
          System.out.print(token.value);
          if (token.vowel) state = 2;
          break;
        case 2:
          if (token.other) {
            System.out.print(token.value);
            state = 1;
          }
          else if (token.vowel) {
            System.out.print(token.value);
          }
          else {
            pending = token;
            state = 3;
          }
          break;
        case 3:
          if (token.other || token.terminatingE) {
            System.out.print(pending.value + token.value);
            state = 1;
            pending = null;
          }
          else if (token.vowel) {
            System.out.print("-" + pending.value + token.value);
            pending = null;
            state = 2;
          }
          else {
            System.out.print(pending.value);
            pending = token;
            state = 4;
          }
          break;
        case 4:
          if (token.vowel) {
            System.out.print("-" + pending.value + token.value);
            pending = null;
            state = 2;
          }
          else {
            System.out.print(pending.value + token.value);
            pending = null;
            state = 1;
          }
          break;
        default:
          throw new RuntimeException("oops");
        }
      }
      
      if (pending != null) System.out.print(pending.value);
      pending = null;
      System.out.println();
    }
    
  }
}

class Token {
  static String[] ngrams = {
    "str", "qu", "tr", "br", "st", "sl", "bl", "cr", "ph", "ch"
  };
  boolean consonant, vowel, other, terminatingE;
  String value;
  
  // Extract next token from input
  Token(String input) {
    String lcase = input.toLowerCase();
    
    for (int i = 0; i < ngrams.length; i++) {
      if (input.length() >= ngrams[i].length() &&
          lcase.substring(0,ngrams[i].length()).equals(ngrams[i])) {
        consonant = true;
        value = input.substring(0,ngrams[i].length());
        return;
      }
    }
    
    value = input.substring(0,1);
    // Handle vowels
    switch (lcase.charAt(0)) {
    case 'a': case 'i': case 'o': case 'u': case 'y':
      vowel = true;
      return;
    case 'e':
      vowel = true;
      if (input.length() == 1) 
        terminatingE = true;
      return;
    }
    if (lcase.charAt(0) >= 'b' && lcase.charAt(0) <= 'z') {
      consonant = true;
    }
    else {
      other = true;
    }
    
  }
}

