// https://www.acmicpc.net/problem/17837
// '턴이 진행되던 중에 말이 4개 이상 쌓이는 순간 게임이 종료' - 모든 말을 한번 씩 움직이고 검사X 
// 다음 칸이 파란색이거나 범위를 벗어난 경우 방향 바꿔주고 그 다음칸도 파란색이거나 범위를 벗어난 경우 바로 continue
// 그렇지 않으면 현재칸이 흰색이거나 빨간색인 경우 다시한번 게임규칙이 작용하여 오답

#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;
typedef struct {
	int num, x, y, dir;
}info;
info I;
vector<info> v;
vector<int> temp;
vector<int> map[13][13];
int color[13][13];
int dx[5] = { 0,0,0,-1,1 };
int dy[5] = { 0,1,-1,0,0 };
int n, k, num, x, y, dir;
bool check() {
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j) {
			if (map[i][j].size() && map[i][j].size() > 3) return true;
		}
	}
	return false;
}
int start() {
	int st, nx, ny, ndir;
	for (int l = 1; l < 1001; ++l) {
		for (int i = 0; i < v.size(); ++i) {
			num = v[i].num;
			x = v[i].x;
			y = v[i].y;
			dir = v[i].dir;
			nx = x + dx[dir];
			ny = y + dy[dir];
			temp.clear();
			if (1 > nx || nx > n || 1 > ny || ny > n || color[nx][ny] == 2) {
				if (dir == 1 || dir == 3) ++dir;
				else --dir;
				nx = x + dx[dir];
				ny = y + dy[dir];
				if (1 > nx || nx > n || 1 > ny || ny > n || color[nx][ny] == 2) {
					v[num - 1].dir = dir;
					continue;
				}
			}
			for (int j = 0; j < map[x][y].size(); ++j) {
				if (map[x][y][j] == num) {
					st = j;
					break;
				}
			}
			for (int j = st; j < map[x][y].size(); ++j)
				temp.push_back(map[x][y][j]);
			map[x][y].erase(map[x][y].begin() + st, map[x][y].end());
			if (color[nx][ny] == 1) reverse(temp.begin(), temp.end());
			for (int j = 0; j < temp.size(); ++j) {
				map[nx][ny].push_back(temp[j]);
				v[temp[j] - 1].x = nx;
				v[temp[j] - 1].y = ny;
			}
			v[num - 1].dir = dir;
			if (check()) return l;
		}
	}
	return -1;
}
int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> n >> k;
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= n; ++j)
			cin >> color[i][j];
	for (int i = 1; i <= k; ++i) {
		cin >> x >> y >> dir;
		I = { i,x,y,dir };
		v.push_back(I);
		map[x][y].push_back(i);
	}
	cout << start();
}
