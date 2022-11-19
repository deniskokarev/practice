package dk.foobar;

// Java program to find Determinant of a matrix
class GFG
{

    // Dimension of input square matrix
    static final int N = 4;

    // Function to get determinant of matrix
    static int determinantOfMatrix(int mat[][], int n)
    {
        int num1, num2, det = 1, index,
                total = 1; // Initialize result

        // temporary array for storing row
        int[] temp = new int[n + 1];

        // loop for traversing the diagonal elements
        for (int i = 0; i < n; i++)
        {
            index = i; // initialize the index

            // finding the index which has non zero value
            while (index < n && mat[index][i] == 0)
            {
                index++;
            }
            if (index == n) // if there is non zero element
            {
                // the determinant of matrix as zero
                continue;
            }
            if (index != i)
            {
                // loop for swapping the diagonal element row
                // and index row
                for (int j = 0; j < n; j++)
                {
                    swap(mat, index, j, i, j);
                }
                // determinant sign changes when we shift
                // rows go through determinant properties
                det = (int)(det * Math.pow(-1, index - i));
            }

            // storing the values of diagonal row elements
            for (int j = 0; j < n; j++)
            {
                temp[j] = mat[i][j];
            }

            // traversing every row below the diagonal
            // element
            for (int j = i + 1; j < n; j++)
            {
                num1 = temp[i]; // value of diagonal element
                num2 = mat[j]
                        [i]; // value of next row element

                // traversing every column of row
                // and multiplying to every row
                for (int k = 0; k < n; k++)
                {
                    // multiplying to make the diagonal
                    // element and next row element equal
                    mat[j][k] = (num1 * mat[j][k])
                            - (num2 * temp[k]);
                }
                total = total * num1; // Det(kA)=kDet(A);
            }
        }

        // multiplying the diagonal elements to get
        // determinant
        for (int i = 0; i < n; i++)
        {
            det = det * mat[i][i];
        }
        return (det / total); // Det(kA)/k=Det(A);
    }

    static int[][] swap(int[][] arr, int i1, int j1, int i2,
                        int j2)
    {
        int temp = arr[i1][j1];
        arr[i1][j1] = arr[i2][j2];
        arr[i2][j2] = temp;
        return arr;
    }

    // Driver code
    public static void main(String[] args)
    {
		/*int mat[N][N] = {{6, 1, 1},
						{4, -2, 5},
						{2, 8, 7}}; */

        int mat[][] = { { 1, 0, 2, -1 },
                { 3, 0, 0, 5 },
                { 2, 1, 4, -3 },
                { 1, 0, 5, 0 } };

        // Function call
        System.out.printf(
                "Determinant of the matrix is : %d",
                determinantOfMatrix(mat, N));
    }
}

// This code is contributed by Rajput-Ji

public class Solution_3_2 {
    static protected class R {
        long n, d;
        private long gcd(long a, long b) {
            while (b > 0) {
                long temp = b;
                b = a % b;
                a = temp;
            }
            return a;
        }
        private long lcm(long a, long b) {
            long g = gcd(a, b);
            return a / g * b;
        }
        public R(long n, long d) {
            this.n = n;
            this.d = d;
        }
        public R(long n) {
            this(n, 1);
        }
        public R() {
            this(0, 1);
        }
        R simplify() {
            long g = gcd(n, d);
            n /= g;
            d /= g;
            return this;
        }
        public R plus(R o) {
            long nd = lcm(d, o.d);
            return new R(n * (nd/d) + o.n * (nd/o.d), nd);
        }
        public R minus(R o) {
            long nd = lcm(d, o.d);
            return new R(n * (nd/d) - o.n * (nd/o.d), nd);
        }
        public R mul(R o) {
            return new R(n * o.n, d * o.d).simplify();
        }
        public R div(R o) {
            return new R(n * o.d, d * o.n).simplify();
        }
        public Boolean equals(int i) {
            return n == i && d == 1 || (n == 0 && i == 0);
        }
        public String toString() {
            return Long.toString(n) + " / " + Long.toString(d);
        }
    }
    static R r(int i) {
        return new R(i);
    }
    static R r(int n, int d) {
        return new R(n, d);
    }
    static class Mat {
        R mm[][];
        int sz;
        public Mat(R[][]mm) {
            this.mm = mm;
        }
        public R det() {
            R mat[][] = new R[mm.length][mm[0].length];
            for (int i=0; i<sz; i++) {
                System.arraycopy(mm[i], 0, mat[i], 0, sz);
            }
            R num1, num2;
            R total = new R(0);
            R det = new R(1);

            // temporary array for storing row
            R[] temp = new R[sz + 1];

            // loop for traversing the diagonal elements
            for (int i = 0; i < sz; i++) {
                int index = i; // initialize the index

                // finding the index which has non zero value
                while (index < sz && mat[index][i].equals(0)) {
                    index++;
                }
                if (index == sz) {// if there is non zero element
                    // the determinant of matrix as zero
                    continue;
                }
                if (index != i) {
                    // loop for swapping the diagonal element row
                    // and index row
                    System.arraycopy(mat[index], 0, temp, 0, sz);
                    System.arraycopy(mat[i], 0, mat[index], 0, sz);
                    System.arraycopy(temp, 0, mat[i], 0, sz);
                    // determinant sign changes when we shift
                    // rows go through determinant properties
                    det = det.mul(new R((long)(Math.pow(-1, index - i))));
                } else {
                    // storing the values of diagonal row elements
                    System.arraycopy(mat[i], 0, temp, 0, sz);
                }
                // traversing every row below the diagonal
                // element
                for (int j = i + 1; j < sz; j++) {
                    num1 = temp[i]; // value of diagonal element
                    num2 = mat[j][i]; // value of next row element

                    // traversing every column of row
                    // and multiplying to every row
                    for (int k = 0; k < sz; k++) {
                        // multiplying to make the diagonal
                        // element and next row element equal
                        mat[j][k] = num1.mul(mat[j][k]).minus((num2.mul(temp[k])));
                    }
                    total = total.mul(num1); // Det(kA)=kDet(A);
                }
            }

            // multiplying the diagonal elements to get
            // determinant
            for (int i = 0; i < sz; i++) {
                det = det.div(mat[i][i]);
            }
            return det.div(total); // Det(kA)/k=Det(A);
        }
    }
//    public static int[] solution(int[][] m) {
//    }

    public static void main(String args[]) {
        R [][] mat = new R[][]{
            {r(1), r(-1)},
            {r(-1), r(1)},
        };
        Mat mm = new Mat(mat);
//        int [] ans = Solution_3_2.solution(mat);
//        for (int i=0; i<ans.length; i++)
//            System.out.print(ans[i], ' ');
        System.out.println(mm.det());
        int mat2[][] = { { 1, 0, 2, -1 },
                { 3, 0, 0, 5 },
                { 2, 1, 4, -3 },
                { 1, 0, 5, 0 } };
        int mat3[][] = { { 1 }};
        int mat4[][] = { { 1, -1 },
                {1, 1}};

        // Function call
        System.out.printf(
                "Determinant of the matrix is : %d\n",
                GFG.determinantOfMatrix(mat4, 2));
    }
}