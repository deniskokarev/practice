package dk.foobar;

public class Solution_3_2 {
    static protected class R {
        long n, d;

        private static long gcd(long a, long b) {
            while (b != 0) {
                long temp = b;
                b = a % b;
                a = temp;
            }
            return a;
        }

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
            if (d < 0) {
                d *= -1;
                n *= -1;
            }
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
            return new R(n * o.d, d * o.n).simplify();
        }

        public Boolean equals(int i) {
            return n == i && d == 1 || (n == 0 && i == 0);
        }

        public String toString() {
            //return Long.toString(n) + "/" + Long.toString(d);
            return Double.toString(((double) n) / d);
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
    }
}