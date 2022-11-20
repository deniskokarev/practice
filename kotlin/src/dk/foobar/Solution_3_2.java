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
    static void assertMe(Boolean c, String err) throws IllegalStateException {
        if (!c)
            throw new IllegalStateException(err);
    }
    static protected class R {
        long n, d;

        // b must be pos
        private static long gcd(long a, long b) {
            a = Math.abs(a); // make a pos
            while (b != 0) {
                long temp = b;
                b = a % b;
                a = temp;
            }
            return a;
        }

        // b must be pos
        private static long lcm(long a, long b) {
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
            return new R(n * (nd / d) + o.n * (nd / o.d), nd);
        }

        public R minus(R o) {
            long nd = lcm(d, o.d);
            return new R(n * (nd / d) - o.n * (nd / o.d), nd);
        }

        public R mul(R o) {
            return new R(n * o.n, d * o.d).simplify();
        }

        public R div(R o) {
            int sign = Long.signum(n) * Long.signum(o.n);
            n = Math.abs(n);
            long on = Math.abs(o.n);
            return new R(n * o.d * sign, d * on).simplify();
        }

        public Boolean equals(int i) {
            return n == i && d == 1 || (n == 0 && i == 0);
        }

        public Boolean equals(R o) {
            return n == o.n && d == o.d;
        }

        public String toString() {
            return Long.toString(n) + "/" + Long.toString(d);
            //return Double.toString(((double) n) / d);
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
        int rows, cols;

        public Mat(R[][] mm) {
            this.mm = mm;
            rows = mm.length;
            cols = mm[0].length;
        }

        R[][] cloneMat() {
            R clMat[][] = new R[rows][cols];
            for (int i = 0; i < rows; i++)
                System.arraycopy(mm[i], 0, clMat[i], 0, cols);
            return clMat;
        }

        public R det() {
            int sz = rows; // rows == cols
            // diagonal matrix
            R dmat[][] = cloneMat();
            R total = new R(1);
            R det = new R(1);

            // temporary array for storing row
            R[] temp = new R[sz];

            // loop for traversing the diagonal elements
            for (int i = 0; i < sz; i++) {
                int index = i; // initialize the index
                int sign = 1;

                // finding the index which has non zero value
                while (index < sz && dmat[index][i].equals(0)) {
                    index++;
                    sign *= -1;
                }
                if (index == sz) {// if there is non zero element
                    // the determinant of matrix as zero
                    continue;
                } else if (index != i) {
                    // loop for swapping the diagonal element row and index row
                    System.arraycopy(dmat[index], 0, temp, 0, sz);
                    System.arraycopy(dmat[i], 0, dmat[index], 0, sz);
                    System.arraycopy(temp, 0, dmat[i], 0, sz);
                    // determinant sign changes when we shift
                    // rows go through determinant properties
                    //det = det.mul(r((int)Math.pow(-1, index - i)));
                    det = det.mul(new R(sign));
                } else {
                    // storing the values of diagonal row elements
                    System.arraycopy(dmat[i], 0, temp, 0, sz);
                }
                // traversing every row below the diagonal element
                for (int j = i + 1; j < sz; j++) {
                    R num1 = temp[i]; // value of diagonal element
                    R num2 = dmat[j][i]; // value of next row element
                    // traversing every column of row
                    // and multiplying to every row
                    for (int k = 0; k < sz; k++) {
                        // multiplying to make the diagonal
                        // element and next row element equal
                        dmat[j][k] = num1.mul(dmat[j][k]).minus((num2.mul(temp[k])));
                    }
                    total = total.mul(num1); // Det(kA)=kDet(A);
                }
            }
            // multiplying the diagonal elements to get
            // determinant
            for (int i = 0; i < sz; i++) {
                det = det.mul(dmat[i][i]);
            }
            return det.div(total); // Det(kA)/k=Det(A);
        }

        Mat mat_minor(int r, int c) {
            R[][] res = new R[rows - 1][cols - 1];
            for (int di = 0, si = 0; si < rows; si++) {
                if (si == r)
                    continue;
                for (int dj = 0, sj = 0; sj < cols; sj++) {
                    if (sj == c)
                        continue;
                    res[di][dj] = mm[si][sj];
                    dj++;
                }
                di++;
            }
            return new Mat(res);
        }

        Mat adj() {
            R a[][] = new R[rows][rows];
            for (int r = 0; r < rows; r++) {
                int sign = ((r & 1) == 0) ? 1 : -1;
                for (int c = 0; c < rows; c++) {
                    Mat mr = mat_minor(r, c);
                    if (c == 0 && r == 3) {
                        System.out.println("Mat minor [3][0]");
                        for (int i=0; i<3; i++) {
                            for (int j=0; j<3; j++)
                                System.out.print(mr.mm[i][j] + " ");
                            System.out.println("\n");
                        }
                        System.out.println("sign=" + sign);
                        System.out.println("det=" + mr.det());
                        System.out.println("out=" + mr.det().mul(r(sign)));
                    }
                    a[c][r] = mr.det().mul(r(sign));
                    sign *= -1;
                }
            }
            return new Mat(a);
        }

        Mat div(R o) {
            R clMat[][] = new R[rows][cols];
            for (int i = 0; i < rows; i++)
                for (int j = 0; j < cols; j++)
                    clMat[i][j] = mm[i][j].div(o);
            return new Mat(clMat);
        }

        Mat mul(Mat o) {
            R res[][] = new R[rows][o.cols];
            for (int r = 0; r < rows; r++) {
                for (int c = 0; c < o.cols; c++) {
                    R s = new R(0);
                    for (int j = 0; j < cols; j++)
                        s = s.plus(mm[r][j].mul(o.mm[j][c]));
                    res[r][c] = s;
                }
            }
            return new Mat(res);
        }

        Mat inv() {
            R d = det();
            Mat res = adj();
            return res.div(d);
        }

        public String toString() {
            String o = "";
            for (int i = 0; i < rows; i++) {
                for (int j = 0; j < cols; j++)
                    o += mm[i][j] + " ";
                o += "\n";
            }
            return o;
        }
    }
//    public static int[] solution(int[][] m) {
//    }

    public static void main(String args[]) {
        R r1 = new R(-180, 1);
        R r2 = new R(-6, 1);
        R q = r1.div(r2);
        System.out.println("result=" + q);
        R[][] mat0 = new R[][]{
                {r(3)},
        };
        R[][] mat1 = new R[][]{
                {r(2), r(-2)},
                {r(3), r(5)},
        };
        int mat2[][] = {
                {1, 0, 2, -3},
                {3, 0, 0, 5},
                {2, 1, 4, -3},
                {1, 0, 5, 0}
        };
        int mat5[][] = {
                {5, -2, 2, 7},
                {1, 0, 0, 3},
                {-3, 1, 5, 0},
                {3, -1, -9, 4}
        };
        int mat6[][] = {
                {0, 2, -3},
                {0, 0, 5},
                {1, 4, -3},
        };
        R mat2r[][] = new R[4][4];
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++)
                mat2r[i][j] = r(mat2[i][j]);
        }
        R mat5r[][] = new R[4][4];
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++)
                mat5r[i][j] = r(mat5[i][j]);
        }
        R mat6r[][] = new R[3][3];
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++)
                mat6r[i][j] = r(mat6[i][j]);
        }
        Mat mm5 = new Mat(mat5r);
        System.out.println(mm5);
        System.out.println(mm5.adj());
        System.out.println(mm5.inv());
        System.out.println(mm5.mul(mm5.inv()));

        Mat mm0 = new Mat(mat0);
        System.out.println(mm0.det());
        Mat mm1 = new Mat(mat1);
        System.out.println(mm1.det());

        Mat mm2 = new Mat(mat2r);
        System.out.println(mm2);
        System.out.println(mm2.inv());
        System.out.println(mm2.mul(mm2.inv()));
        System.out.println(mm2.adj());
        R d2 = mm2.det();
        R expD2 = r(60);
        System.out.println("d2=" + d2);
        assertMe(d2.equals(expD2), "wrong det for matrix 2");


        int rd6 = GFG.determinantOfMatrix(mat6, 3);
        System.out.println("rd6="+rd6);

        Mat mm3 = new Mat(mat6r);
        System.out.println(mm3);
        R d3 = mm3.det();
        R expD3 = r(10);
        System.out.println("d3=" + d3);
        assertMe(d3.equals(expD3), "wrong det for matrix 3");
    }
}