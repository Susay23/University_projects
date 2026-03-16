package session_5;
import java.util.Scanner;

class Customer {
    public String name, id, address;
    
    public Customer() {
    name = "";
    id = "";
    address = "";
    }

    public Customer(String name, String id, String address){
        this.name = name;
        this.id = id;
        this.address = address;
    }

    // input customer information
    public void input(){
        Scanner sc = new Scanner(System.in);
        System.out.println("input name");
        this.name = sc.nextLine();
        System.out.println("input id");
        this.id = sc.nextLine();
        System.out.println("input address");
        this.address = sc.nextLine();
    }

    // display customer information
    public void display(){
        System.out.println("name:" + name);
        System.out.println("id:" + id);
        System.out.println("address:" + address);
    }
}