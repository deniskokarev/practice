enum {END=0,MINUS,PLUS,DIV,MUL,INT,OP_SZ};

static const int PRIORITY[OP_SZ] = {0, 1, 1, 2, 2, 3};

struct OP {
    int op;
    int v;
};

class Solution {
    void eval(vector<OP> &stack, int &sp, int upto_op) {
        while (sp > 2 && PRIORITY[stack[sp-2].op] >= PRIORITY[upto_op]) {
            switch (stack[sp-2].op) {
                case MINUS:
                    stack[sp-3].v -= stack[sp-1].v;
                    break;
                case PLUS:
                    stack[sp-3].v += stack[sp-1].v;
                    break;
                case DIV:
                    stack[sp-3].v /= stack[sp-1].v;
                    break;
                case MUL:
                    stack[sp-3].v *= stack[sp-1].v;
                    break;
            }
            sp -= 2;
        }
    }
public:
    int calculate(string &s) {
        vector<OP> stack(2+2+1); // 2 kinds of ops means 5 elemets max
        int sp = 0;
        int v = 0;
        for (auto c:s) {
            int op = -1;
            switch (c) {
                case '*':
                    op = MUL;
                    break;
                case '/':
                    op = DIV;
                    break;
                case '+':
                    op = PLUS;
                    break;
                case '-':
                    op = MINUS;
                    break;
                default:
                    if (isdigit(c)) {
                        if (sp > 0 && stack[sp-1].op == INT)
                            stack[sp-1].v *= 10, stack[sp-1].v += c-'0';
                        else
                            stack[sp++] = OP {INT, c-'0'};
                    }
                    continue;
            }
            eval(stack, sp, op);
            stack[sp++] = OP {op, -1};
        }
        eval(stack, sp, END);
        return stack[0].v;
    }
};
