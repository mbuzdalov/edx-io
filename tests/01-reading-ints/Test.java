import mooc.*;

public class Test {
    public static void main(String[] args) {
        try (EdxIO io = EdxIO.create()) {
            int n = io.nextInt();
            long sum = 0;
            for (int i = 0; i < n; ++i) {
                sum += io.nextInt();
            }
            io.println(sum);
        }
    }
}
