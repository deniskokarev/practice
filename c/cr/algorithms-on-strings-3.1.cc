#include <iostream>
#include <vector>
using namespace std;

vector<int> SortCharacters(const string &s) {
	vector<int> order(s.size());
	vector<int> count(256);
	for (auto c:s)
		count[c]++;
	for (int i=1; i<256; i++)
		count[i] += count[i-1];
	for (int i=s.size()-1; i>=0; i--) {
		char ch = s[i];
		count[ch]--;
		order[count[ch]] = i;
	}
	return order;
}


vector<int> ComputeCharClasses(const string &s, const vector<int> &order) {
	vector<int> classs(s.size());
	classs[order[0]] = 0;
	for (int i=1; i<s.size(); i++) {
		if (s[order[i]] != s[order[i-1]])
			classs[order[i]] = classs[order[i-1]] + 1;
		else
			classs[order[i]] = classs[order[i-1]];
	}
	return classs;
}
			
vector<int> SortDoubled(const string &s, int l, const vector<int> &order, const vector<int> &classs) {
	vector<int> count(s.size());
	vector<int> newOrder(s.size());
	for (int i=0; i<s.size(); i++)
		count[classs[i]]++;
	for (int j=1; j<s.size(); j++)
		count[j] += count[j-1];
	for (int i=s.size()-1; i>=0; i--) {
		int start = (order[i]-l+s.size()) % s.size();
		int cl = classs[start];
		count[cl]--;
		newOrder[count[cl]] = start;
	}
	return newOrder;
}

vector<int> UpdateClasses(const vector<int> &newOrder, const vector<int> &classs, int l) {
	int n = newOrder.size();
	vector<int> newClass(n);
	newClass[newOrder[0]] = 0;
	for (int i=1; i<n; i++) {
		int cur = newOrder[i], prev = newOrder [i-1];
		int mid = cur + l, midPrev = (prev + l) % n;
		if (classs[cur] != classs[prev] || classs[mid] != classs[midPrev])
			newClass[cur] = newClass[prev] + 1;
		else
			newClass[cur] = newClass[prev];
	}
	return newClass;
}

vector<int> BuildSuffixArray(const string &s) {
	auto order = SortCharacters(s);
	cerr << "SortCharacters(s): ";
	for (int i:order)
		cerr << i << ' ';
	cerr << endl;
	auto classs = ComputeCharClasses(s, order);
	cerr << "ComputeCharClasses(s, order): ";
	for (int i:classs)
		cerr << i << ' ';
	cerr << endl;
	int l = 1;
	while (l < s.size()) {
		order = SortDoubled(s, l, order, classs);
		cerr << "SortDoubled(s, " << l << ", order, classs): ";
		for (int i:order)
			cerr << i << ' ';
		cerr << endl;
		classs = UpdateClasses(order, classs, l);
		cerr << "UpdateClasses(order, classs, " << l << "): ";
		for (int i:classs)
			cerr << i << ' ';
		cerr << endl;
		l *= 2;
	}
	return order;
}

int main(int argc, char **argv) {
	string s;
	cin >> s;
	auto suffa = BuildSuffixArray(s);
	for (int i:suffa)
		cout << i << ' ';
	cout << endl;
	return 0;
}
