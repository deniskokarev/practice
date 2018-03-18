/* ACMP 1010 */
#include <cstdio>

using namespace std;

int main(int argc, char **argv) {
	int n;
	scanf("%d", &n);
	for (int j=0; j<n; j++) {
		for (int k=0; k<n; k++)
			printf("%c", k+'A');
		printf(" ");
	}
	printf("\n");
	for (int i=1; i<n; i++) {
		for (int j=0; j<n; j++) {
			for (int k=0; k<n; k++)
				printf("%c", j+'A');
			printf(" ");
		}
		printf("\n");
	}
}
