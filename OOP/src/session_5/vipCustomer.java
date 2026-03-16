package session_5;

import java.util.Scanner;

public class vipCustomer extends Customer {
    int discount;

    public vipCustomer(){
        super();
        discount = 0;
    }

    public vipCustomer(String name, String id, String address, int discount){
        super(name,id,address);
        this.discount = discount;
    }

    // input 

    public void input(){
        Scanner sc = new Scanner(System.in);
        System.out.println("input name, id, address");
        super.input();
        System.out.println("input discount");
        this.discount = sc.nextInt();
        sc.nextLine();
    }

    // display

    public void display(){
        super.display();
        System.out.println("Discount: " + discount);
    }
    
}
