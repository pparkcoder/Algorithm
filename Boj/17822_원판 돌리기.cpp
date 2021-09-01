// https://www.acmicpc.net/problem/17822

#include<iostream>
#include<vector>
#include<deque>
#define mp make_pair
using namespace std;
vector<pair<int, int> >v;
deque<int> dq;
int map[51][51];
int dx[4] = { 0,0,-1,1 };
int dy[4] = { -1,1,0,0 };
int n, m, t;
int result = 0;
void start(int x, int d, int k) {
	int temp, nx, ny, flag, sum, cnt,turn;
	float avg;
	for (int i = 1; i <= n; ++i) {
		if (i % x) continue;
		for (int j = 1; j <= m; ++j)
			dq.push_back(map[i][j]);
        turn = k % m;
		for (int j = 1; j <= turn; ++j) {
			if (!d) {
				temp = dq.back();
				dq.pop_back();
				dq.push_front(temp);
			}
			else {
				temp = dq.front();
				dq.pop_front();
				dq.push_back(temp);
			}
		}
		for (int j = 1; j <= m; ++j)
			map[i][j] = dq[j - 1];
		dq.clear();
	}
	flag = sum = cnt = 0;
	v.clear();
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) {
			if (!map[i][j]) continue;
			if ((j == 1 || j == m) && (map[i][1] == map[i][m])) {
				v.push_back(mp(i, 1));
				v.push_back(mp(i, m));
				flag = 1;
			}
			for (int l = 0; l < 4; ++l) {
				nx = i + dx[l];
				ny = j + dy[l];
				if (0 < nx && nx <= n && 0 < ny && ny <= m && map[nx][ny] == map[i][j]) {
					v.push_back(mp(nx, ny));
					flag = 1;
				}
			}
			sum += map[i][j];
			++cnt;
		}
	}
	if (flag) {
		for (int i = 0; i < v.size(); ++i)
			map[v[i].first][v[i].second] = 0;
	}
	else {
		avg = float(sum) / cnt;
		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= m; ++j) {
				if (!map[i][j] || map[i][j] == avg) continue;
				else if (map[i][j] > avg) --map[i][j];
				else if (map[i][j] < avg) ++map[i][j];
			}
		}
	}
}
int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int x, d, k;
	cin >> n >> m >> t;
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= m; ++j)
			cin >> map[i][j];
	for (int i = 1; i <= t; ++i) {
		cin >> x >> d >> k;
		start(x, d, k);
	}
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= m; ++j)
			result += map[i][j];
	cout << result;
}
