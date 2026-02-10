package practical_session_01.ex6;

import java.util.Scanner;
import java.util.TreeMap;

public class App {
    @SuppressWarnings("ConvertToTryWithResources")
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        TreeMap<Integer, Integer> frequencyMap = new TreeMap<>();
        System.out.print("Please specify how long the list is: ");
        int n = sc.nextInt();
        System.out.print("Please type in the list, separate by spaces: ");
        for (int i = 0; i < n; ++i) {
            int userInput = sc.nextInt();
            frequencyMap.merge(userInput, 1, Integer::sum);
        }

        System.out.print("Please type in the number x: ");
        int x = sc.nextInt();
        if (frequencyMap.containsKey(x)) {
            System.out.println("The list has " + frequencyMap.get(x) + " of " + x);
        } else {
            System.out.println(x + " is not available!");
        }

        System.out.print("The sorted list: ");
        frequencyMap.forEach((number, frequency) -> {
            for (int i = 0; i < frequency; ++i) {
                System.out.print(number + " ");
            }
        });
        System.out.println();

        frequencyMap.merge(x, 1, Integer::sum);
        System.out.print("The sorted list after insert " + x + ": ");
        frequencyMap.forEach((number, frequency) -> {
            for (int i = 0; i < frequency; ++i) {
                System.out.print(number + " ");
            }
        });
        System.out.println();

        frequencyMap.headMap(x).clear();
        System.out.print("The sorted list after delete anything smaller than " + x + ": ");
        frequencyMap.forEach((number, frequency) -> {
            for (int i = 0; i < frequency; ++i) {
                System.out.print(number + " ");
            }
        });
        System.out.println();

        sc.close();
    }
}
