//https://www.acmicpc.net/problem/12100

#include<iostream>
#include<vector>
#include<cstring>
#include<algorithm>
using namespace std;
vector<int> v;
int map[21][21];
int cmap[21][21];
int visit[21][21];
int dx[4] = { 0,0,-1,1 };
int dy[4] = { -1,1,0,0 };
int result = -987654321;
int n, dir;
void move(int now_x, int now_y) {
	int x = now_x;
	int y = now_y;
	while(1){
		int nx = x + dx[dir];
		int ny = y + dy[dir];
		if (1 > nx || nx > n || 1 > ny || ny > n) return;
		if (cmap[nx][ny] != cmap[x][y]) {
			if (cmap[nx][ny]) return;
			else {
				cmap[nx][ny] = cmap[x][y];
				cmap[x][y] = 0;
			}
		}
		else {
			if (!visit[nx][ny]) {
				cmap[nx][ny] *= 2;
				cmap[x][y] = 0;
				visit[nx][ny] = 1;
			}
			else {
				cmap[nx - dx[dir]][ny - dy[dir]] = cmap[x][y];
			}
			return;
		}
		x = nx;
		y = ny;
	}
}
void brute(int cnt) {
	if (cnt == 5) {
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= n; j++)
				cmap[i][j] = map[i][j];
		for (int i = 0; i < v.size(); i++) {
			memset(visit, 0, sizeof(visit));
			dir = v[i];
			if (dir == 0 || dir == 2) {
				for (int k = 1; k <= n; k++)
					for (int j = 1; j <= n; j++)
						if(cmap[k][j]) move(k, j);
			}
			else {
				for (int k = n; k > 0; k--)
					for (int j = n; j > 0; j--)
						if (cmap[k][j]) move(k, j);
			}
		}
		for (int k = 1; k <= n; k++)
			for (int j = 1; j <= n; j++)
				result = max(result, cmap[k][j]);
		return;
	}
	for (int i = 0; i < 4; i++) {
		v.push_back(i);
		brute(cnt + 1);
		v.pop_back();
	}
}
int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> n;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			cin >> map[i][j];
	brute(0);
	cout << result;
}
