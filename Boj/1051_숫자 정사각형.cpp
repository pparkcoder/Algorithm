// https://www.acmicpc.net/problem/1051
// 가장 최솟값을 0으로 두면 x -> 셀 하나가 길이가 1 인 정사각형 이므로

#include<iostream>
#include<algorithm>
using namespace std;
char map[51][51];
int dx[4] = { 0,1,0,-1 };
int dy[4] = { 1,0,-1,0 };
int n, m;
//int result = 0;
int result = 1;
void dfs(int x, int y, int dir, int len) {
	if (dir == 4) {
		result = max(result, (len + 1)*(len + 1));
		return;
	}
	int nx = x + dx[dir] * len;
	int ny = y + dy[dir] * len;
	if (0 < nx && nx <= n && 0 < ny && ny <= m && map[x][y] == map[nx][ny])
		dfs(nx, ny, dir + 1, len);
	return;
}
int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> n >> m;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			cin >> map[i][j];
	int len = min(n, m);
	for (int i = 1; i <= n; i++) 
		for (int j = 1; j <= m; j++) 
			for (int k = 1; k < len; k++) 
				dfs(i, j, 0, k);
	cout << result;
}
