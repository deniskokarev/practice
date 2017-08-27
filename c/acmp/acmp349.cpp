#include <iostream>
#include <vector>
using namespace std;
int main() {
  int m,n;
  cin >> m >> n;
  n++;
  vector<bool> prime(n, true);
  prime[0] = prime[1] = false;
  for (int p=2; p<n; p++)
    if (prime[p])
	  for (int i=p+p; i<n; i+=p)
        prime[i] = false;
  int ans=0;
  for (int i=m; i<n; i++) {
    if (prime[i]) {
    	ans++;
        cout << i << endl;
    }
  }
  if (ans < 1)
    cout << "Absent" << endl;
  return 0;
}
