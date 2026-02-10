package Ex2;

public class LineSegment {
    Point d1, d2;

    public LineSegment() {
        this.d1 = new Point();
        this.d2 = new Point();
    }

    public LineSegment(Point x, Point y) {
        this.d1 = x;
        this.d2 = y;
    }

    public LineSegment(int d1x, int d1y, int d2x, int d2y) {
        this.d1 = new Point(d1x, d1y);
        this.d2 = new Point(d2x, d2y);
    }

    public void input() {
        System.out.println("d1: ");
        d1.input();
        System.out.println("d2: ");
        d2.input();
    }

    public void display() {
        System.out.println("Line Segment from ");
        d1.display();
        System.out.println("to ");
        d2.display();
    }

    public void move(int dx, int dy) {
        d1.move(dx, dy);
        d2.move(dx, dy);
    }

    public float length() { // Distance formula: sqrt((x2-x1)^2 + (y2-y1)^2)
        return (float) Math.sqrt(Math.pow(d2.x - d1.x, 2) + Math.pow(d2.y - d1.y, 2));
    }
}
