import mooc.*;

public class Test {
    public static void main(String[] args) {
        try (EdxIO io = EdxIO.create()) {
            int n = io.nextInt();
            long xor = 0;
            for (int i = 0; i < n; ++i) {
                xor ^= io.nextLong();
            }
            io.println(xor);
        }
    }
}
