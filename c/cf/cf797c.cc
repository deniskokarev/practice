#include <iostream>
#include <vector>
/* CodeForces CF797C problem */
using namespace std;

void output_t(string &t, char upto_c) {
	while (t.size() > 0 && t.back() <= upto_c) {
		cout << t.back();
		t.pop_back();
	}
}

int main(int argc, char **argv) {
	string s;
	cin >> s;
	int sl = s.size();
	string smn = s; // keep min ch till the end
	for (int i=sl-2; i>=0; i--)
		if (s[i] <= smn[i+1])
			smn[i] = s[i];
		else
			smn[i] = smn[i+1];
	string t = "";
	int i = 0;
	while (i<sl) {
		output_t(t, smn[i]);
		for (; i<sl && (t.size() == 0 || t.back() > smn[i]); i++)
			t += s[i];
	}
	output_t(t, 127);
	cout << endl;
	return 0;
}
