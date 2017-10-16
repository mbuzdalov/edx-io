import mooc.*;

public class Test {
    public static void main(String[] args) {
        try (EdxIO io = EdxIO.create()) {
            int n = io.nextInt();
            long a = io.nextLong(), b = io.nextLong(), c = io.nextLong();
            long v0 = io.nextLong(), v1 = io.nextLong();
            io.print(v0).print(' ').print(v1);
            for (int i = 2; i < n; ++i) {
                long v2 = a * v0 + b * v1 + c;
                io.print(' ').print(v2 < 0 ? -Math.sqrt(-v2) : Math.sqrt(v2));
                v0 = v1;
                v1 = v2;
            }
            io.println();
        }
    }
}
