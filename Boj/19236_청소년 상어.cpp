// https://www.acmicpc.net/problem/19236
// Solving -> 이동 전의 물고기의 좌표 및 방향을 기억해두고, 브루트포스 진행
// Tip -> 몰고기 이동 후 원래자리 0으로 바꿔주기, 초기화 진행 후 map 복원

#include<iostream>
#include<vector>
#include<algorithm>
#include<cstring>
using namespace std;
typedef struct {
	int num, x, y, dir, life;
}info;
info I;
vector<info> v;
int dx[9] = { 0,-1,-1,0,1,1,1,0,-1 };
int dy[9] = { 0,0,-1,-1,-1,0,1,1,1 };
int map[4][4];
int result = 0;
int fish_num;
bool cmp(info a, info b) {
	if (a.num < b.num) return true;
	else return false;
}
void restore(vector<info> &temp, int flag) {
	if (!flag) temp = v;
	else {
		v = temp;
		memset(map, 0, sizeof(map));
		for (int i = 0; i < 16; ++i) {
			if (!v[i].life) continue;
			int x = v[i].x;
			int y = v[i].y;
			map[x][y] = v[i].num;
		}
	}
}
void move_fish() {
	for (int i = 0; i < 16; ++i) {
		if (!v[i].life) continue;
		int x = v[i].x;
		int y = v[i].y;
		int dir = v[i].dir;
		for (int j = 1; j < 9; ++j) {
			int nx = x + dx[dir];
			int ny = y + dy[dir];
			if (0 > nx || nx > 3 || 0 > ny || ny > 3 || map[nx][ny] == -1) {
				if (++dir > 8) dir = 1;
			}
			else {
				map[x][y] = 0;
				if (map[nx][ny]) {
					fish_num = map[nx][ny];
					map[x][y] = fish_num;
					v[fish_num - 1].x = x;
					v[fish_num - 1].y = y;
				}
				v[i].x = nx;
				v[i].y = ny;
				v[i].dir = dir;
				map[nx][ny] = v[i].num;
				break;
			}
		}
	}
}
void brute(int x, int y, int dir, int sum) {
	result = max(result, sum);
	move_fish();
	vector<info> temp;
	for (int i = 1; i < 4; ++i) {
		int nx = x + dx[dir] * i;
		int ny = y + dy[dir] * i;
		if (0 <= nx && nx < 4 && 0 <= ny && ny < 4 && map[nx][ny]) {
			restore(temp, 0);
			fish_num = map[nx][ny];
			map[nx][ny] = -1;
			map[x][y] = 0;
			v[fish_num - 1].life = 0;
			brute(nx, ny, v[fish_num - 1].dir, sum + fish_num);
			v[fish_num - 1].life = 1;
			restore(temp, 1);
		}
	}
}
int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int a, b;
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			cin >> a >> b;
			I = { a,i,j,b,1 };
			v.push_back(I);
			map[i][j] = a;
		}
	}
	sort(v.begin(), v.end(), cmp);
	result = fish_num = map[0][0];
	map[0][0] = -1;
	v[fish_num - 1].life = 0;
	brute(0, 0, v[fish_num - 1].dir, fish_num);
	cout << result;
}
