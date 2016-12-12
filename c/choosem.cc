#include <iostream>
#include <vector>

using namespace std;

typedef void (*F)(const vector<string> &kinds, const vector<int> &selection);

void choosem_r(const vector<string> &kinds, vector<int> &selection, int k, int p, const F &f) {
	if (p >= selection.size()) {
		f(kinds, selection);
	} else {
		for (int ki=k; ki<kinds.size(); ki++) {
			selection[p] = ki;
			choosem_r(kinds, selection, ki, p+1, f);
		}
	}
}

int main(int argc, char **argv) {
	vector<string> kinds = {"1", "2", "3"};
	vector<int> selection(3);
	choosem_r(kinds, selection, 0, 0, [](const vector<string> &kinds, const vector<int> &selection) -> void {
			for (auto i=selection.begin(); i!=selection.end(); ++i) {
				cout << kinds[*i] << " ";
			}
			cout << endl;
		});
	return 0;
}
