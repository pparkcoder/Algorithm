// https://www.acmicpc.net/problem/17837
// '턴이 진행되던 중에 말이 4개 이상 쌓이는 순간 게임이 종료' - 모든 말을 한번 씩 움직이고 검사X 
// 다음 칸이 파란색이거나 범위를 벗어난 경우 방향 바꿔주고 그 다음칸도 파란색이거나 범위를 벗어난 경우 바로 continue
// 그렇지 않으면 현재칸이 흰색이거나 빨간색인 경우 다시한번 게임규칙이 작용하여 오답

#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
typedef struct {
	int num, x, y, dir;
}info;
info I;
vector<info> v;
vector<int> map[13][13], temp;
int color[13][13];
int dx[5] = { 0,0,0,-1,1 };
int dy[5] = { 0,1,-1,0,0 };
int n, m, num;
int start() {
	int num, x, y, dir, nx, ny, start_index;
	for (int i = 1; i < 1001; ++i) {
		for (int j = 0; j < m; ++j) {
			temp.clear();
			num = v[j].num;
			x = v[j].x;
			y = v[j].y;
			dir = v[j].dir;
			for (int k = 0; k < map[x][y].size(); ++k) {
				if (map[x][y][k] == num) {
					start_index = k;
					break;
				}
			}
			for (int k = start_index; k < map[x][y].size(); ++k)
				temp.push_back(map[x][y][k]);
			nx = x + dx[dir];
			ny = y + dy[dir];
			if (1 > nx || nx > n || 1 > ny || ny > n || color[nx][ny] == 2) {
				if (dir == 1 || dir == 3) ++dir;
				else --dir;
				nx = x + dx[dir];
				ny = y + dy[dir];
				if (1 > nx || nx > n || 1 > ny || ny > n || color[nx][ny] == 2) {
					v[num].dir = dir;
					continue;
				}
			}
			if (color[nx][ny] == 1) reverse(temp.begin(), temp.end());
			for (int k = 0; k < temp.size(); ++k) {
				map[nx][ny].push_back(temp[k]);
				v[temp[k]].x = nx;
				v[temp[k]].y = ny;
			}
			v[num].dir = dir;
			map[x][y].erase(map[x][y].begin() + start_index, map[x][y].end());
			if(map[nx][ny].size() > 3) return i;
		}
	}
	return -1;
}
int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> n >> m;
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= n; ++j)
			cin >> color[i][j];
	int x, y, dir;
	for (int i = 0; i < m; ++i) {
		cin >> x >> y >> dir;
		I = { i,x,y,dir };
		v.push_back(I);
		map[x][y].push_back(i);
	}
	cout << start();
}
