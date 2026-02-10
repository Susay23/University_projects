package Ex3;

import java.util.Arrays;
import java.util.Scanner;

public class Student {
    String id;
    String name;
    Date birthday;
    int num_course;
    String[] coursename;
    String[] coursegrade;

    public Student() {
        num_course = 0;
        coursegrade = new String[0];
        coursename = new String[0];
    }

    public Student(String id, String name, Date birthday) {
        this.id = id;
        this.name = name;
        this.birthday = birthday;
        this.num_course = 0;
        this.coursename = new String[0];
        this.coursegrade = new String[0];
    }

    // Copy Constructor
    public Student(Student other) {
        this.id = other.id;
        this.name = other.name;
        this.birthday = other.birthday;
        this.num_course = other.num_course;
        this.coursename = Arrays.copyOf(other.coursename, other.num_course);
        this.coursegrade = Arrays.copyOf(other.coursegrade, other.num_course);
    }

    public void input() {
        Scanner sc = new Scanner(System.in);
        System.out.print("Enter ID: ");
        id = sc.nextLine();
        System.out.print("Enter Name: ");
        name = sc.nextLine();
        birthday = new Date();
        birthday.input();
    }

    public void inputGrade() {
        Scanner sc = new Scanner(System.in);
        System.out.println("input numbers of course: ");
        num_course = sc.nextInt();
        sc.nextLine();
        coursename = new String[num_course];
        coursegrade = new String[num_course];
        for (int i = 0; i < num_course; i++) {
            System.out.println("Couse Number " + (i + 1) + " Name: ");
            coursename[i] = sc.nextLine();
            System.out.println("Grade: (A, B+, B, C+, C, D+, D, F)");
            coursegrade[i] = sc.nextLine().toUpperCase();
        }
    }

    public Float gradeToPoint(String grade) {
        switch (grade) {
            case "A":
                return 4.0f;
            case "B+":
                return 3.5f;
            case "B":
                return 3.0f;
            case "C+":
                return 2.5f;
            case "C":
                return 2.0f;
            case "D+":
                return 1.5f;
            case "D":
                return 1.0f;
            default:
                return 0.0f;

        }
    }

    public float avgGrade() {
        if (num_course == 0) {
            return 0;
        }
        float total = 0;
        for (String g : coursegrade) {
            total += gradeToPoint(g);
        }
        return total;
    }

    public void add(String name, String grade) {
        this.coursename = Arrays.copyOf(coursename, num_course + 1);
        this.coursegrade = Arrays.copyOf(coursegrade, num_course + 1);
        coursename[num_course] = name;
        coursegrade[num_course] = grade;
    }

    public void delete(String name) {
        int index = -1;
        for (int i = 0; i < num_course; i++) {
            if (coursename[i].equalsIgnoreCase(name)) {
                index = i;
            }
            if (index == -1) {
                System.out.println("ERROR!!!");
                break;
            }
        }
    }

    public void results() {
        System.out.println("Results of" + name + "(GPA: " + avgGrade() + ")");
        for (int i = 0; i < num_course; i++) {
            System.out.println(" - " + coursename[i] + " - " + coursegrade[i]);
        }
    }

    public String toString() {
        return "ID: " + id + " | Name: " + name + " | Courses: " + num_course + " | GPA: " + avgGrade();
    }

    public String getName() {
        return name;
    }

}
