package session_4.Ex1;
import java.security.PublicKey;
import java.util.Scanner;
import Session_3_new.Ex2.Course;


public class UniversityCourse extends Course{
    public String teacherName, classRoom;
    public String[] listStudent;
    public int numOfstudent; 

    public UniversityCourse(){
        super();
        this.teacherName = "";
        this.classRoom = "";
        this.numOfstudent = 0;
        this.listStudent = new String[0];
    }

    public UniversityCourse(String courseID, String coursename, int numCredits, String teacherName, String classRoom){
        super(courseID,coursename,numCredits,0);
        this.teacherName = teacherName;
        this.classRoom = classRoom;
        this.numOfstudent = 0;
        this.listStudent = new String[0];
    }

    public void display(){
        super.display();
        System.out.println(" Teacher Name: " + teacherName);
        System.out.println(" Class Room: " + classRoom);
        System.out.println(" Number Of Students: " + numOfstudent);
        if(numOfstudent>0){
            System.out.println(" List Of Students ");
            for(int i = 0; i < numOfstudent; i ++){
                System.out.println(listStudent[i]);
                if(i<numOfstudent-1){
                    System.out.println(", ");
                }
            }
            System.out.println();
        }
    }
    
    public void input(){
        super.input();
        Scanner sc = new Scanner(System.in);
        System.out.println(" Teacher Name: ");
        teacherName =  sc.nextLine();
        System.out.println(" Class Room ");
        classRoom = sc.nextLine();
    }

    boolean alreadyRegistered(String studentName){
        for(int i = 0; i < numOfstudent; i ++){
            if(listStudent[i].equals(studentName)){
                return true;
            }
        }
        return false;
    }

    public void registerStudent(String studentName){
        if(alreadyRegistered(studentName)){
            System.out.println(studentName + " already registered!");
            return;
        }

        String[] newList = new String[numOfstudent + 1];
        for(int i = 0; i < numOfstudent; i ++){
            newList[i] = listStudent[i];
        }
        newList[numOfstudent] = studentName;
        listStudent = newList;
        numOfstudent++;
        System.out.println(" Resgister Success! ");
    }

    public void removeStudent(String studentName){
        int pos = -1;
        for(int i = 0; i<numOfstudent; i++){
            if(listStudent[i].equals(studentName)){
                pos = i;
                break;
            }
        }
        if(pos == -1){
            System.out.println("ERROR!");
            return;
        }

        String[] newList = new String[numOfstudent - 1];
        for(int i = 0; i < pos; i++){
            newList[i] = listStudent[i];
        }
        for(int i = pos + 1; i < numOfstudent; i ++ ){
            newList[i-1] = listStudent[i];
        }
        listStudent = newList;
        numOfstudent --;
        System.out.println(" Remove Success!!! ");

    }

    public int getNumberStudent(){
        return numOfstudent;
    }

    public String getCourseName(){
        return tenHP;
    }

}
