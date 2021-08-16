// https://www.acmicpc.net/problem/17142
// Solving -> '활성 바이러스가 비활성 바이러스가 있는 칸으로 가면 비활성 바이러스가 활성으로 변한다' 는 다음점이 비활성 바이러스라면 현재 visit값을 그대로 넣기
// Tip -> max값 계산 시, 바이러스를 놓을 수 있는 자리(2) 면 continue + 초기의 ans 값을 0으로 놓기 -> 예제 7번보고 hint

#include<iostream>
#include<queue>
#include<vector>
#include<algorithm>
#include<cstring>
#define mp make_pair
using namespace std;
queue<pair<int, int> > q;
vector<pair<int, int> > v, v2;
int map[51][51];
int cmap[51][51];
int visit[51][51];
int dx[4] = { 0,0,-1,1 };
int dy[4] = { -1,1,0,0 };
int n, m;
int result = 987654321;
void calc() {
	memset(visit, -1, sizeof(visit));
	for (int i = 1; i <= n; ++i) 
		for (int j = 1; j <= n; ++j) 
			cmap[i][j] = map[i][j];
	for (int i = 0; i < v2.size(); ++i) {
		int x = v2[i].first;
		int y = v2[i].second;
		q.push(mp(x,y));
		visit[x][y] = 0;
	}
	while (!q.empty()) {
		int x = q.front().first;
		int y = q.front().second; q.pop();
		for (int i = 0; i < 4; ++i) {
			int nx = x + dx[i];
			int ny = y + dy[i];
			if (0 < nx && nx <= n && 0 < ny && ny <= n && visit[nx][ny] == -1 && cmap[nx][ny] != 1) {
				q.push(mp(nx, ny));
				visit[nx][ny] = visit[x][y] + 1;
			}
		}
	}
	int ans = 0;
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j) {
			if (visit[i][j] == -1 && !cmap[i][j]) return;
			if (cmap[i][j]) continue;
			ans = max(ans, visit[i][j]);
		}
	}
	result = min(result, ans);
}
void brute(int cnt, int index) {
	if (cnt == m) {
		calc();
		return;
	}
	for (int i = index; i < v.size(); ++i) {
		v2.push_back(mp(v[i].first, v[i].second));
		brute(cnt + 1, i + 1);
		v2.pop_back();
	}
}
int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> n >> m;
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j) {
			cin >> map[i][j];
			if (map[i][j] == 2) v.push_back(mp(i, j));
		}
	}
	brute(0, 0);
	cout << (result == 987654321 ? -1 : result);
}
