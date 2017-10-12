import java.io.*;
import java.util.*;

public class Reference {
    public static void main(String[] args) throws IOException {
        try (BufferedReader in = new BufferedReader(new FileReader("input.txt"));
             PrintWriter out = new PrintWriter("output.txt")) {
            StringTokenizer st = new StringTokenizer(in.readLine() + " " + in.readLine() + " " + in.readLine());
            int n = Integer.parseInt(st.nextToken());
            int a = Integer.parseInt(st.nextToken()),
                b = Integer.parseInt(st.nextToken()),
                c = Integer.parseInt(st.nextToken());
            int v0 = Integer.parseInt(st.nextToken()),
                v1 = Integer.parseInt(st.nextToken());
            out.print(v0);
            out.print(' ');
            out.print(v1);
            for (int i = 2; i < n; ++i) {
                int v2 = a * v0 + b * v1 + c;
                out.print(' ');
                out.print(v2);
                v0 = v1;
                v1 = v2;
            }
            out.println();
        }
    }
}
