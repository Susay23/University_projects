package session_2.ex2;

import java.util.Scanner;

public class useDate {
    public static void main(String[] args) {
        // Test default constructor
        System.out.println("Testing default constructor:");
        Date a = new Date();
        a.display();

        // Test parameterized constructor
        System.out.println("\nTesting parameterized constructor:");
        Date b = new Date(15, 3, 2024);
        b.display();

        // Test isValid method
        System.out.println("\nTesting isValid method:");
        Date validDate = new Date(29, 2, 2024); // Leap year
        System.out.println("Feb 29, 2024 (leap year): " + validDate.hople());

        Date invalidDate = new Date(29, 2, 2023); // Not leap year
        System.out.println("Feb 29, 2023 (not leap year): " + invalidDate.hople());

        Date invalidMonth = new Date(15, 13, 2024);
        System.out.println("Month 13: " + invalidMonth.hople());

        // Test nextDate method
        System.out.println("\nTesting nextDate method:");
        Date testNext = new Date(28, 2, 2024); // Feb 28, 2024 (leap year)
        System.out.print("Original: ");
        testNext.display();
        Date next = testNext.nextDate();
        System.out.print("Next day: ");
        next.display();

        Date testEndMonth = new Date(31, 1, 2024);
        System.out.print("Jan 31, 2024: ");
        testEndMonth.display();
        Date nextMonth = testEndMonth.nextDate();
        System.out.print("Next day: ");
        nextMonth.display();

        // Test add method
        System.out.println("\nTesting add method:");
        Date start = new Date(1, 1, 2024);
        System.out.print("Start date: ");
        start.display();
        Date added = start.add(365); // Add 365 days
        System.out.print("After adding 365 days: ");
        added.display();

        // Test leap year
        System.out.println("\nTesting leap year logic:");
        Date leapTest = new Date(1, 1, 2024);
        System.out.println("2024 is leap year: " + leapTest.isleapyear(2024));
        System.out.println("2023 is leap year: " + leapTest.isleapyear(2023));
        System.out.println("2000 is leap year: " + leapTest.isleapyear(2000));
        System.out.println("1900 is leap year: " + leapTest.isleapyear(1900));

        // test add
        System.out.println("\n input value");
        Scanner sc = new Scanner(System.in);
        int n = sc.nextInt();
        Date addTest = new Date(26, 1, 2026);
        Date Result = addTest.add(n);
        System.out.println("the date is: ");
        Result.display();
    }
}
