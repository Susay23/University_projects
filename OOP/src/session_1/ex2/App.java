package practical_session_01.ex2;

import java.util.Scanner;

public class App {
    private static int readUserInput(Scanner sc, String message) {
        System.out.print(message);

        while (true) {
            String userInput = sc.nextLine();

            try {
                return Integer.parseInt(userInput);
            } catch (NumberFormatException e) {
                System.out.print("The input is not integer! Please retype: ");
            }
        }
    }

    public static void main(String[] args) {
        int a, b;
        try (Scanner sc = new Scanner(System.in)) {
            a = readUserInput(sc, "Please type in number a: ");
            b = readUserInput(sc, "Please type in number b: ");
        }

        int sum = a + b;
        System.out.println("Sum of two numbers is: " + sum);
    }
}
