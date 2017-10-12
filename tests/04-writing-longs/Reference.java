import java.io.*;
import java.util.*;

public class Reference {
    public static void main(String[] args) throws IOException {
        try (BufferedReader in = new BufferedReader(new FileReader("input.txt"));
             PrintWriter out = new PrintWriter("output.txt")) {
            StringTokenizer st = new StringTokenizer(in.readLine() + " " + in.readLine() + " " + in.readLine());
            int n = Integer.parseInt(st.nextToken());
            long a = Long.parseLong(st.nextToken()),
                 b = Long.parseLong(st.nextToken()),
                 c = Long.parseLong(st.nextToken());
            long v0 = Long.parseLong(st.nextToken()),
                 v1 = Long.parseLong(st.nextToken());
            out.print(v0);
            out.print(' ');
            out.print(v1);
            for (int i = 2; i < n; ++i) {
                long v2 = a * v0 + b * v1 + c;
                out.print(' ');
                out.print(v2);
                v0 = v1;
                v1 = v2;
            }
            out.println();
        }
    }
}
