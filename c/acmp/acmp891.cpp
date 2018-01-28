/* ACMP 891 */
#include <iostream>
#include <cassert>
#include <algorithm>
#include <queue>
#include <unordered_map>

using namespace std;

// rotation matrixes
const static int rot[3][3][3] = {
	{ // axis x counter-clockwies
		{ 1,  0,  0},
		{ 0,  0, -1},
		{ 0,  1,  0}
	},
	{ // axis y counter-clockwies
		{ 0,  0,  1},
		{ 0,  1,  0},
		{-1,  0,  0}
	},
	{ // axis z counter-clockwies
		{ 0, -1,  0},
		{ 1,  0,  0},
		{ 0,  0,  1}
	}
};

struct S {
	int face[3]; // x, y, z
	int x[3]; // x, y, z
	bool operator==(const S &b) const {
		for (int j=0; j<3; j++)
			if (x[j] != b.x[j] || face[j] != b.face[j])
				return false;
		return true;
	}
};

// coordinates and direction of all qube squares in our storage order, each side as UL, UR, BL, BR
const static S ss[6][4] = {
	{	// F
			{{ 1,  0,  0}, { 1, -1,  1}},
			{{ 1,  0,  0}, { 1,  1,  1}},
			{{ 1,  0,  0}, { 1, -1, -1}},
			{{ 1,  0,  0}, { 1,  1, -1}}
	},
	{	// L
			{{ 0, -1,  0}, {-1, -1,  1}},
			{{ 0, -1,  0}, { 1, -1,  1}},
			{{ 0, -1,  0}, {-1, -1, -1}},
			{{ 0, -1,  0}, { 1, -1, -1}}
	},
	{	// B
			{{-1,  0,  0}, {-1,  1,  1}},
			{{-1,  0,  0}, {-1, -1,  1}},
			{{-1,  0,  0}, {-1,  1, -1}},
			{{-1,  0,  0}, {-1, -1, -1}}
	},
	{	// R
			{{ 0,  1,  0}, { 1,  1,  1}},
			{{ 0,  1,  0}, {-1,  1,  1}},
			{{ 0,  1,  0}, { 1,  1, -1}},
			{{ 0,  1,  0}, {-1,  1, -1}}
	},
	{	// U
			{{ 0,  0,  1}, {-1, -1,  1}},
			{{ 0,  0,  1}, {-1,  1,  1}},
			{{ 0,  0,  1}, { 1, -1,  1}},
			{{ 0,  0,  1}, { 1,  1,  1}}
	},
	{	// D
			{{ 0,  0, -1}, { 1, -1, -1}},
			{{ 0,  0, -1}, { 1,  1, -1}},
			{{ 0,  0, -1}, {-1, -1, -1}},
			{{ 0,  0, -1}, {-1,  1, -1}}
	}
};

// we need to construct a move permutation of our cube represented by 24 chars string
// [axis:0-x,1-y,2-z][0:clock-wise, 1:conuter][front:0, back:1]
static int moves[3][2][2][6*4];

static string smoves[3][2][2] = {
	{{"F", "B"}, {"F'", "B'"}},
	{{"R", "L"}, {"R'", "L'"}},
	{{"U", "D"}, {"U'", "D'"}}
};

void rot3d(const int src[3], const int rot[3][3], int dst[3]) {
	int res[3];
	for (int c=0; c<3; c++) {
		int s = 0;
		for (int j=0; j<3; j++)
			s += src[j]*rot[j][c];
		res[c] = s;
	}
	copy(res, res+3, dst);
}

// build moves permutation matrix for each legal move
void bldmoves(int moves[3][2][2][6*4]) {
	int dir[] = {1, -1};
	int rot_cnt[2][2] = {{3, 1}, {1, 3}};
	for (int axis=0; axis<3; axis++) {
		for (int cw=0; cw<2; cw++) { // clock-wise?
			for (int fi=0; fi<2; fi++) { // front/back
				S ss0[6][4];
				for (int i=0; i<6; i++) {
					for (int j=0; j<4; j++) {
						ss0[i][j] = ss[i][j];
						if (ss[i][j].x[axis] == dir[fi]) {
							for (int k=0; k<rot_cnt[fi][cw]; k++) {
								rot3d(ss0[i][j].face, rot[axis], ss0[i][j].face);
								rot3d(ss0[i][j].x, rot[axis], ss0[i][j].x);
							}
						}
					}
				}
				const S *so = (S*)ss;
				const S *sn = (S*)ss0;
				for (int i=0; i<6*4; i++)
					for (int j=0; j<6*4; j++)
						if (so[i] == sn[j])
							moves[axis][cw][fi][i] = j;
				// basic validation of correctness - we must get a permutation
				int sum=0;
				for (int i=0; i<6*4; i++)
					sum += moves[axis][cw][fi][i];
				assert(sum == 23*12);
			}
		}
	}
}

void mkmove(const string &src, int axis, int cw, int fi, string &dst) {
	const auto &mv = moves[axis][cw][fi];
	for (int i=0; i<6*4; i++)
		dst[mv[i]] = src[i];
}

bool is_solved(const string &q) {
	for (int s=0; s<6; s++)
		for (int e=1; e<4; e++)
			if (q[s*4+e] != q[s*4])
				return false;
	return true;
}


//#define DEBUG

int main(int argc, char **argv) {
	// read input
	string start(24, ' ');
	for (int r=0; r<2; r++) {
		for (int s=0; s<6; s++) {
			string ln;
			cin >> ln;
			start[s*4+r*2] = ln[0];
			start[s*4+r*2+1] = ln[1];
		}
	}
	// construct qube permutation for each move
	bldmoves(moves);
#ifdef DEBUG
	// print permutation for each move
	for (int axis=0; axis<3; axis++) {
		for (int cw=0; cw<2; cw++) { // clock-wise?
			for (int fi=0; fi<2; fi++) {
				cerr << smoves[axis][cw][fi] << ": ";
				for (int i=0; i<6*4; i++)
					cerr << moves[axis][cw][fi][i] << ' ';
				cerr << endl;
			}
		}
	}
	// excercise the plan
	const string seq[] = {
		"L", "U", "L", "U'", "L", "B'", "D", "B", "R"
	};
	string m[2] = {start, string(24, ' ')};
	int src = 0, dst = 1;
	for (auto smv:seq) {
		for (int axis=0; axis<3; axis++) {
			for (int cw=0; cw<2; cw++) {
				for (int fi=0; fi<2; fi++) {
					if (smv == smoves[axis][cw][fi]) {
						mkmove(m[src], axis, cw, fi, m[dst]);
						cerr << smoves[axis][cw][fi] << ": " << m[dst] << " solved: " << is_solved(m[dst]) << endl;
					}
				}
			}
		}
		swap(src, dst);
	}
#endif
	if (is_solved(start)) {
		cout << "Solved" << endl;
		return 0;
	}
	unordered_map<string, pair<string, string>> seen; // position->(prev_position, move)
	queue<string> qq;
	qq.push(start);
	seen[start] = make_pair("", "");
	while (!qq.empty()) {
		const string &p = qq.front();
		if (is_solved(p))
			break;
		for (int axis=0; axis<3; axis++) {
			for (int cw=0; cw<2; cw++) {
				for (int fi=0; fi<2; fi++) {
					string np(24, ' ');
					mkmove(p, axis, cw, fi, np);
					if (seen.find(np) == seen.end()) {
						qq.push(np);
						seen[np] = make_pair(p, smoves[axis][cw][fi]);
					}
				}
			}
		}
		qq.pop();
	}
	assert(qq.empty() == false && "we must find the solution");
	vector<string> solution;
	for (string &p = qq.front(); seen.find(p) != seen.end(); p = seen[p].first)
		solution.push_back(seen[p].second);
	for (auto it=solution.rbegin(); it!=solution.rend(); ++it)
		cout << *it;
	cout << endl;
	return 0;
}
