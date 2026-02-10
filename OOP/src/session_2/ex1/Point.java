package session_2.ex1;
import java.util.Scanner;

public class Point {
    public int x, y;

    public Point() {
        x = 0;
        y = 0;
    }

    public Point(int x, int y) {
        this.x = x;
        this.y = y;
    }

    public void input() { // input value
        Scanner sc = new Scanner(System.in);
        System.out.println("input x: ");
        this.x = sc.nextInt();
        System.out.println("input y: ");
        this.y = sc.nextInt();
    }

    public void display() { // display value
        System.out.println("(" + this.x + "," + this.y + ")");
    }

    public void move(int dx, int dy) { // move x,y with value dx, dy
        this.x += dx;
        this.y += dy;
    }

    public int getX(){ // get x value
        return this.x;
    }

    public int getY(){ // get y value
        return this.y;
    }

    public float distance(){ // use special case pythagoras d = sqrt x^2 + y^2;
        return (float) Math.sqrt(x*x + y*y);
    }

    public float distance(Point d){// use pythagoras d = sqrt (x2-x1)^2 + (y2-y1)^2;
        float dx = this.x - d.x;
        float dy = this.x - d.y;
        return (float) Math.sqrt(dx*dx + dy*dy);
    }
}
