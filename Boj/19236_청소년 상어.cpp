// https://www.acmicpc.net/problem/19236
// Solving -> 이동 전의 물고기의 좌표 및 방향을 기억해두고, 브루트포스 진행
// Tip -> 몰고기 이동 후 원래자리 0으로 바꿔주기, 초기화 진행 후 map 복원

#include<iostream>
#include<vector>
#include<algorithm>
#include<cstring>
#include<climits>
using namespace std;
typedef struct {
	int num, live, x, y, dir;
}info;
info I;
vector<info> v;
int map[4][4];
int dx[9] = { 0,-1,-1,0,1,1,1,0,-1 };
int dy[9] = { 0,0,-1,-1,-1,0,1,1,1 };
int result = -INT_MAX;
bool cmp(info a, info b) { // 물고기 번호 오름차순
	if (a.num < b.num) return true;
	else return false;
}
void move_fish() {
	int x, y, dir, nx, ny, ndir, num;
	for (int i = 1; i < 17; ++i) {
		if (!v[i].live) continue;
		x = v[i].x;
		y = v[i].y;
		ndir = dir = v[i].dir;
		while (1) {
			nx = x + dx[dir];
			ny = y + dy[dir];
			if (0 > nx || nx > 3 || 0 > ny || ny > 3 || map[nx][ny] == -1) {
				if (++dir > 8) dir = 1;
				if (dir == ndir) break;
			}
			else {
				num = map[nx][ny];
				map[x][y] = 0; // 원래자리 0으로 변경
				if (1 <= num && num <= 16) {
					v[num].x = x;
					v[num].y = y;
					map[x][y] = num;
				}
				v[i].x = nx;
				v[i].y = ny;
				v[i].dir = dir;
				map[nx][ny] = i;
				break;
			}
		}
	}
}
void copy(vector<info> &temp, int flag) {
	if (!flag)  // 복사
		temp = v;
	else { // 복원	
		v = temp;
		int x, y, dir, num;
		memset(map, 0, sizeof(map)); // 0 으로 초기화 진행후 다시 쓰기
		for (int i = 1; i < 17; ++i) {
			if (!v[i].live) continue;
			x = v[i].x;
			y = v[i].y;
			map[x][y] = i;
		}
	}
}
void brute(int sx, int sy, int dir, int sum) {
	result = max(result, sum);
	move_fish();
	vector<info> temp;
	int num, nx, ny;
	for (int i = 1; i < 4; ++i) {
		nx = sx + dx[dir] * i;
		ny = sy + dy[dir] * i;
		if (0 > nx || nx > 3 || 0 > ny || ny > 3) return;
		else {
			num = map[nx][ny];
			if (1 <= num && num <= 16) {
				copy(temp, 0);
				map[sx][sy] = 0;
				map[nx][ny] = -1;
				v[num].live = 0;
				brute(nx, ny, v[num].dir, sum + num);
				v[num].live = 1;
				map[nx][ny] = num;
				map[sx][sy] = -1;
				copy(temp, 1);
			}
		}
	}
}
int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int a, b, num;
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			cin >> a >> b;
			I = { a,1,i,j,b };
			v.push_back(I);
			map[i][j] = a;
		}
	}
	I = { 0,0,0,0 };
	v.push_back(I);
	sort(v.begin(), v.end(), cmp);
	num = map[0][0];
	map[0][0] = -1;
	v[num].live = 0;
	brute(0, 0, v[num].dir, num);
	cout << result;
}
