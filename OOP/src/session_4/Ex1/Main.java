package session_4.Ex1;
import java.security.PublicKey;
import java.util.Scanner;
import Session_3_new.Ex2.Course;

public class Main extends Course{

public static void main(String[] args) {
    Scanner sc = new Scanner(System.in);
    System.out.println("enter numbers of university course: ");
    int n = sc.nextInt();
    sc.nextLine();
    UniversityCourse[] ds = new UniversityCourse[n];
    for(int i = 0; i < n; i++){
        System.out.println("course: " + (i + 1));
        ds[i] = new UniversityCourse();
        ds[i].input();
    }

    for(int i = 0; i<n;i++){
        System.out.println("\n---Refister students for " + ds[i].getCourseName() + " ---");
        System.out.println("Number of students : ");
        int numberStudent = sc.nextInt();
        sc.nextLine();
            for(int j = 0; j < numberStudent; j ++){
                System.out.print("Student name " + (j + 1) + ": ");
                String studentName = sc.nextLine();
                ds[i].registerStudent(studentName);
            }
    }

    for(int i = 0; i < n; i ++){
        ds[i].display();
    }

    UniversityCourse maxSV = ds[0];
    for(int i = 1; i<n;i++){
        if(ds[i].getNumberStudent()>maxSV.getNumberStudent()){
            maxSV = ds[i];
        }
    }

    System.out.println("--- Course with the most registrations ---");
    maxSV.display();

    for(int i = 0; i < n - 1; i++){
        for(int j = 0; j < n - i - 1; j++){
            if(ds[j].getNumberStudent() < ds[j+1].getNumberStudent()){
                UniversityCourse temp = ds[j];
                ds[j] = ds[j + 1];
                ds[j + 1] = temp; 
            }
        }
    }

    }
    
}