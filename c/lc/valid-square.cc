class Solution {
    struct P {
        int x,y;
        bool operator<(const P &o) const {
            return x<o.x || (x==o.x && y<o.y);
        }
        int d2() {
            return x*x + y*y;
        }
        P operator-(const P &o) const {
            return {x-o.x, y-o.y};
        }
    };
public:
    bool validSquare(vector<int>& p1, vector<int>& p2, vector<int>& p3, vector<int>& p4) {
        P pp[4] {{p1[0],p1[1]},{p2[0],p2[1]},{p3[0],p3[1]},{p4[0],p4[1]}};
        sort(pp, pp+4);
        swap(pp[2], pp[3]); // Z -> П
        int g1 = (pp[0]-pp[2]).d2();
        int g2 = (pp[1]-pp[3]).d2();
        int s1 = (pp[1]-pp[0]).d2();
        int s2 = (pp[2]-pp[1]).d2();
        int s3 = (pp[2]-pp[1]).d2();
        int s4 = (pp[3]-pp[2]).d2();
        return s1 && s1==s2 && s2==s3 && s3==s4 && g1 == g2;
    }
};
