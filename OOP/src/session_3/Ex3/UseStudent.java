package Ex3;

import java.util.Scanner;

public class UseStudent {
    public static void main(String[] args) {
        // Create student a. Enter information for student a and Register student a for an additional course called "OOP". Display information for a.
        Student a = new Student();
        a.input();
        a.add("OOP", "A");
        System.out.println(a.toString());
        a.results();

        // Create a list of students. Enter and display information for the list of students.
        Scanner sc = new Scanner(System.in);
        System.out.println("number of student: ");
        int n = sc.nextInt();
        Student[] list = new Student[n];
        for(int i = 0; i < n; i ++){
            System.out.println("\nStudent #" + (i + 1));
            list[i] = new Student();
            list[i].input();
            list[i].inputGrade();
        }

        // Find students with academic warnings (average grade less than or equal to 1)
        System.out.println("\n--- Academic Warnings (GPA <= 1.0) ---");
        boolean foundwarning = false;
        for (Student s : list){
            if(s.avgGrade()<=1){
                System.out.println(s.toString());
                foundwarning = true;
            }
        }
        if(!foundwarning){
            System.out.println("None. ");
        }

        // Find students with the highest average grade in the class
        Student top = list[0];
        for(int i = 0; i < n; i++){
            if(list[i].avgGrade()>top.avgGrade()){
                top = list[i];
            }
        }
        System.out.println("Highest Student: ");
        System.out.println(top.toString());
        top.results();

        // Display the list of students in alphabetical order of Name (lambda expression)
        java.util.Arrays.sort(list, (s1, s2) -> s1.getName().compareToIgnoreCase(s2.getName()));
        for(int i = 0; i < n ; i++){
            System.out.println(list[i].toString());
        }
    }
}
