package practical_session_01.ex5;

import java.util.Scanner;

public class App {
    private static String splitter(String input){
        String[] words = input.split(" ");
        return words[0];
    }

    public static void main(String[] args) {
        String fullName;
        try (Scanner sc = new Scanner(System.in)) {
            fullName = sc.nextLine();
        }

        System.out.println("Your first name is: " + splitter(fullName));
    }
}
