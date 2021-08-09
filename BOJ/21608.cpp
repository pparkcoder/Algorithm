#include<iostream>
#include<vector>
#include<cmath>
#include<algorithm>
using namespace std;
typedef struct {
	int like_cnt, empty_cnt, x, y;
}info;
info I;
vector<info> v;
vector<int> order;
vector<int> connect[401];
int map[21][21];
int dx[4] = { 0,0,-1,1 };
int dy[4] = { -1,1,0,0 };
int n, s, e;
int result = 0;

bool cmp(info first, info second) {
	if (first.like_cnt == second.like_cnt) {
		if (first.empty_cnt == second.empty_cnt) {
			if (first.x == second.x) {
				return first.y > second.y;
			}
			return first.x > second.x;
		}
		return first.empty_cnt < second.empty_cnt;
	}
	return first.like_cnt < second.like_cnt;
}

void find(int num, int x, int y, int flag) {
	int nx, ny;
	int like_cnt = 0, empty_cnt = 0;
	vector<int> temp;
	for (int i = 0; i < 4; ++i) {
		nx = x + dx[i];
		ny = y + dy[i];
		if (0 < nx && nx <= n && 0 < ny && ny <= n) {
			if (!map[nx][ny]) ++empty_cnt;
			else temp.push_back(map[nx][ny]);
		}
	}
	for (int i = 0; i < temp.size(); ++i) {
		for (int j = 0; j < connect[num].size(); ++j) {
			if (temp[i] == connect[num][j]) {
				++like_cnt;
				break;
			}
		}
	}
	if (!flag) {
		I = { like_cnt,empty_cnt,x,y };
		v.push_back(I);
	}
	else {
		if (like_cnt)
			result += pow(10, like_cnt - 1);
	}
}

void start() {
	int len;
	for (int i = 0; i < order.size(); ++i) {
		for (int j = 1; j <= n; ++j)
			for (int k = 1; k <= n; ++k)
				if (!map[j][k])
					find(order[i], j, k, 0);
		sort(v.begin(), v.end(), cmp);
		len = v.size() - 1;
		map[v[len].x][v[len].y] = order[i];
		v.clear();
	}
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= n; ++j)
			find(map[i][j], i, j, 1);
	cout << result;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> n;
	for (int i = 0; i < n*n; ++i) {
		cin >> s;
		for (int j = 0; j < 4; ++j) {
			cin >> e;
			connect[s].push_back(e);
		}
		order.push_back(s);
	}
	start();
}