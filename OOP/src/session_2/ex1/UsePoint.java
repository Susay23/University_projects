package session_2.ex1;
public class UsePoint {
    public static void main(String[] args) {
    
    Point a = new Point(3, 4); // Point a
    a.display();

    Point b = new Point(); // Point b
    b.input();
    b.display();

    Point c = new Point(-b.getX(), -b.getY());
    c.display();

    // b = (5,12);
    System.out.println("distance from point B to center O is: " + b.distance());

    System.out.println("distance from point A to point B is " + a.distance(b));

    }
}
