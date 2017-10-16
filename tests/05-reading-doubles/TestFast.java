import mooc.*;

public class TestFast {
    public static void main(String[] args) {
        try (EdxIO io = EdxIO.create()) {
            int n = io.nextInt();
            double sum = 0;
            for (int i = 0; i < n; ++i) {
                sum += io.nextDoubleFast();
            }
            io.println(sum);
        }
    }
}
