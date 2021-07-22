// https://www.acmicpc.net/problem/21610

#include<iostream>
#include<vector>
#include<cstring>
#define mp make_pair
using namespace std;
vector<pair<int, int> > v, cloud;
int map[51][51];
bool visit[51][51];
int dx[9] = { 0, 0,-1,-1,-1,0,1,1,1 };
int dy[9] = { 0,-1,-1,0,1,1,1,0,-1 };
int n, m, d, s;
int result = 0;
void start() {
	for (int i = 0; i < 2; ++i) {
		cloud.push_back(mp(n - i, 1));
		cloud.push_back(mp(n - i, 2));
	}
	int x, y, nx, ny, ns;
	for (int i = 0; i < v.size(); ++i) {
		d = v[i].first;
		s = v[i].second;
		for (int j = 0; j < cloud.size(); ++j) {
			x = cloud[j].first;
			y = cloud[j].second;
			ns = s % n;
			x += dx[d] * ns;
			y += dy[d] * ns;
			if (x < 1) x += n;
			else if (x > n) x -= n;
			if (y < 1) y += n;
			else if (y > n) y -= n;
			cloud[j].first = x;
			cloud[j].second = y;
			++map[x][y];
			visit[x][y] = 1;
		}
		for (int j = 0; j < cloud.size(); ++j) {
			x = cloud[j].first;
			y = cloud[j].second;
			for (int k = 2; k < 9; k += 2) {
				nx = x + dx[k];
				ny = y + dy[k];
				if (0 < nx && nx <= n && 0 < ny && ny <= n && map[nx][ny])
					++map[x][y];
			}
		}
		cloud.clear();
		for (int j = 1; j <= n; ++j) {
			for (int k = 1; k <= n; ++k) {
				if (map[j][k] > 1 && !visit[j][k]) {
					cloud.push_back(mp(j, k));
					map[j][k] -= 2;
				}
			}
		}
		memset(visit, 0, sizeof(visit));
	}
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= n; ++j)
			result += map[i][j];
	cout << result;
}
int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> n >> m;
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= n; ++j)
			cin >> map[i][j];
	while (m--) {
		cin >> d >> s;
		v.push_back(mp(d, s));
	}
	start();
}
