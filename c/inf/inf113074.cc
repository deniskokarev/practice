#include <cstdio>
#include <cstring>
/* INF 113074 */

int main(int argc, char **argv) {
	int capacity, n;
	scanf("%d%d", &capacity, &n);
	int objects[n];
	for (auto &o:objects)
		scanf("%d", &o);
	int solution[capacity+1][n+1];
	memset(solution, 0, sizeof(solution));
	for (int t=1; t<=capacity; t++) {
		for (int i=0; i<n; i++)
			if (objects[i]<=t && solution[t-objects[i]][i]+1 > solution[t][i])
				solution[t][i+1] = solution[t-objects[i]][i]+1;
			else
				solution[t][i+1] = solution[t][i];
	}
	printf("%d\n", solution[capacity][n]);
	return 0;
}
