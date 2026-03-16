package session_5;

import java.util.Scanner;

public class product {
    String name, id;
    Date manuDate;
    public product() {
        super();
        name = "";
        id = "";
        manuDate = new Date();
    }
    public product(String name, String id, Date manuDate){
        this.name = name;
        this.id = id;
        this.manuDate = manuDate;
    }

    // input product information
    public void input(){
        Scanner sc = new Scanner(System.in);
        System.out.println("input name");
        this.name = sc.nextLine();
        System.out.println("input id");
        this.id = sc.nextLine();
        this.manuDate.input();
        sc.nextLine();
    }
    // display product information
    public void display(){
        System.out.println("name:" + name);
        System.out.println("id:" + id);
        System.out.println("manuDate:");
        this.manuDate.display();
    }
}
