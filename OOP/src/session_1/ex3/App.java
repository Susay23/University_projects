package practical_session_01.ex3;

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

    private static void quadraticSolver(int a, int b, int c) {
        double delta = Math.pow(b, 2) - (4 * a * c);

        if (delta >= 0) {
            double x1 = (-b + Math.sqrt(delta)) / (2 * a);
            double x2 = (-b - Math.sqrt(delta)) / (2 * a);

            System.out.print("x1 = " + x1 + " | ");
            if (delta != 0)
                System.out.println("x2 = " + x2);
        } else {
            System.out.println("N/A");
        }
    }

    public static void main(String[] args) {
        int a, b, c;

        try (Scanner sc = new Scanner(System.in)) {
            a = readUserInput(sc, "Please type in the value for a: ");
            b = readUserInput(sc, "Please type in the value for b: ");
            c = readUserInput(sc, "Please type in the value for c: ");
        }

        System.out.print("The result of the quadratic equation is: ");
        quadraticSolver(a, b, c);
    }
}
