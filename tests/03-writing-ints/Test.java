import mooc.*;

public class Test {
    public static void main(String[] args) {
        try (EdxIO io = EdxIO.create()) {
            int n = io.nextInt();
            int a = io.nextInt(), b = io.nextInt(), c = io.nextInt();
            int v0 = io.nextInt(), v1 = io.nextInt();
            io.print(v0).print(' ').print(v1);
            for (int i = 2; i < n; ++i) {
                int v2 = a * v0 + b * v1 + c;
                io.print(' ').print(v2);
                v0 = v1;
                v1 = v2;
            }
            io.println();
        }
    }
}
