#include <stdio.h>
#include <stdlib.h>

static int
find4key(int code)
{
    int this;
    int nl;
    int next;
    int i;
	int cnt = 0;

    static int tried[10000];
    for (i = 0; i < 10000; i++)
        tried[i] = 0;

    this = 0;
    nl = 4;
    for (cnt=0;;cnt++) {
        if (this == code)
            break;
        tried[this] = 1;

        for (next = (this*10)%10000, i = 10; i; next++, i--)
            if (tried[next] == 0)
                break;
        if (i) {
            this = next;
            nl += 1;
            continue;
        }
        for (next = (this*100)%10000, i = 100; i; next++, i--)
            if (tried[next] == 0)
                break;
        if (i) {
            this = next;
            nl += 2;
            continue;
        }
        for (next = (this*1000)%10000, i = 1000; i; next++, i--)
            if (tried[next] == 0)
                break;
        if (i) {
            this = next;
            nl += 3;
            continue;
        }
        for (next = 0, i = 10000; i; next++, i--)
            if (tried[next] == 0)
                break;
        if (i) {
            this = next;
            nl += 4;
            continue;
        }
    }
	printf("cnt: %d\n", cnt);
	
    return nl;
}

int main(int argc, char *argv[])
{
    int code;
    int begin;
    int end;
    int nl;
    int nall;

    if (argc > 1) {
        begin = atoi(argv[1]);
        end = begin;
    } else {
        begin = 0;
        end = 9999;
    }

    nall = 0;
    for (code = begin; code <= end; code++) {
        nl = find4key(code);
        printf("%04d %d\n", code, nl);
        nall += nl;
    }
    if (begin == 0)
        printf("average = %.f\n", (double)nall/10000);

    return 0;
}
