// https://www.acmicpc.net/problem/17135
// '같은 적이 여러 궁수에게 공격당할 수 있다' -> 반복문 한번마다 적을 죽이지 말고 한꺼번에 죽이기

#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
vector<pair<int, int> > v, v2;
vector<pair<int, pair<int, int> > >enemy; //거리 y x
int map[17][16], cmap[17][16];
int n, m, d, r1, c1, flag, kill, len;
int result = 0;
bool check() {
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			if (map[i][j]) return false;
	return true;
}
void start() {
	kill = 0;
	while (1) {
		if (check()) break;
		v2.clear();
		for (int i = 0; i < 3; i++) {
			r1 = v[i].first;
			c1 = v[i].second;
			flag = 0;
			enemy.clear();
			for (int r2 = n; r2 > 0; r2--) {
				for (int c2 = 1; c2 <= m; c2++) {
					len = abs(r1 - r2) + abs(c1 - c2);
					if (map[r2][c2] && len <= d) {
						enemy.push_back(make_pair(len, make_pair(c2, r2)));
						flag = 1;
					}
				}
			}
			if (flag) {
				sort(enemy.begin(), enemy.end());
				v2.push_back(make_pair(enemy[0].second.second, enemy[0].second.first));
			}
		}
		v2.erase(unique(v2.begin(), v2.end()), v2.end());
		for (int i = 0; i < v2.size(); i++) {
			map[v2[i].first][v2[i].second] = 0;
			++kill;
		
		for (int i = n; i > 0; i--) {
			for (int j = 1; j <= m; j++) {
				map[i + 1][j] = map[i][j];
				map[i][j] = 0;
			}
		}
	}
	result = max(result, kill);
	return;
}
void brute(int index, int cnt) {
	if (cnt == 3) {
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= m; j++)
				map[i][j] = cmap[i][j];
		start();
		return;
	}
	for (int i = index; i <= m; i++) {
		v.push_back(make_pair(n + 1, i));
		brute(i + 1, cnt + 1);
		v.pop_back();
	}
}
int main() {
	ios::sync_with_stdio(false); cin.tie(0);
	cin >> n >> m >> d;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			cin >> cmap[i][j];
	brute(1, 0);
	cout << result;
}
