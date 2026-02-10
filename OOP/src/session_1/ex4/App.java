package practical_session_01.ex4;

import java.util.Scanner;

public class App {
    private static boolean isPrime(int num) {
        if (num <= 1) {
            return false;
        } else {
            for (int i = (int)Math.sqrt(num); i > 1; --i){
                if (num % i == 0)
                    return false;
            }
        }

        return true;
    }

    private static String convertToBinary(int num){
        return Integer.toBinaryString(num);
    }

    private static int digitSum(int num){
        int sum = 0;

        while(num > 0){
            sum += num % 10;
            num = num / 10;
        }

        return sum;
    }

    private static void divisors(int num){
        while (num != 1){
            for (int i = num; i > 1; --i){
                if (num % i == 0 && isPrime(i)){
                    System.out.print(" " + i + " ");
                    num = num / i;
                    break;
                }
            }
        }
    }

    public static void main(String[] args) {
        int n;
        try (Scanner sc = new Scanner(System.in)) {
            n = sc.nextInt();
        }

        if (isPrime(n))
            System.out.println(n + " is a prime!");
        System.out.println(n + " in binary is: " + convertToBinary(n));
        System.out.println("Sum of all digits in " + n + " is: " + digitSum(n));
        System.out.print("The prime divisors of " + n + " is: ");
        divisors(n);
    }
}
