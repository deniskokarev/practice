#include <iostream>
#include <vector>
using namespace std;
int main() {
  int n;
  cin >> n;
  vector<bool> prime(2*n, true);
  prime[0] = prime[1] = false;
  for (int p=2; p<2*n; p++)
    if (prime[p])
	  for (int i=p+p; i<2*n; i+=p)
        prime[i] = false;
  int ans=0;
  for (int i=n+1; i<2*n; i++)
    if (prime[i])
    	ans++;
  cout << ans << endl;
  return 0;
}
