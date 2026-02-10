package Ex2;

import java.util.Scanner;

public class Point {
    int x,y;
    public Point(){
        this.x = 0;
        this.y = 0;
    }
    public Point(int x, int y){
        this.x = x;
        this.y = y;
    }
    public void input(){
        Scanner sc = new Scanner(System.in);
        System.out.println("input x = ");
        this.x = sc.nextInt();
        System.out.println("input y = ");
        this.y = sc.nextInt();
    }
    public void display(){
        System.out.println("(" + this.x + "," + this.y + ")");
    }
    public void move(int x, int y){
        this.x += x;
        this.y += y;
    }
}
