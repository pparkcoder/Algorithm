// 루돌프 자리 선정 시 해당 자리에서 산타까지의 거리 구한 뒤, 좌표 대소비교를 통해 dx,dy에서 index를 구해야 함
// dx,dy와 dx2,dy2의 0~4 index는 동일하게 맞추면 좋음 -> 산타 이동 시 루돌프의 dx,dy로 움직이기 때문
// 틀린 이유 : 루돌프 자리 선정 시 주변 8 방향에서 산타까지의 거리를 구함
/*
3 5 2 1 1
2 2
1 1 3
2 1 2
answer : 3 1
*/

#include<iostream>
#include<algorithm>
#include<vector>
#include<cmath>
using namespace std;
typedef struct {
	int x, y, life, sleep;
}info;
typedef struct {
	int dist, x, y, dir;
}info2;
info I;
info2 I2;
vector<info> people[31];
int map[51][51], sum[31];
int dx[8] = { -1,0,1,0,-1,1,1,-1 };
int dy[8] = { 0,1,0,-1,1,1,-1,-1 }; // 루돌프
int dx2[4] = { -1,0,1,0 };
int dy2[4] = { 0,1,0,-1 }; // 산타
int N, M, P, C, D, sx, sy;
bool check() {
	bool flag = true;
	for (int i = 1; i <= P; ++i) {
		if (people[i][0].life) {
			flag = false;
			sum[i]++;
			if (people[i][0].sleep)
				people[i][0].sleep--;
		}
	}
	return flag;
}
bool cmp(info2 a, info2 b) { // 루돌프 우선순위
	if (a.dist == b.dist) {
		if (a.x == b.x) return a.y > b.y;
		else return a.x > b.x;
	}
	else return a.dist < b.dist;
}
bool cmp2(info2 a, info2 b) { // 산타 우선순위
	if (a.dist == b.dist) return a.dir < b.dir;
	else return a.dist < b.dist;
}
void next_push(int x, int y, int num, int dir) {
	int nx = x + dx[dir];
	int ny = y + dy[dir];
	if (1 > nx || nx > N || 1 > ny || ny > N) people[num][0].life = 0;
	else {
		if (1 <= map[nx][ny] && map[nx][ny] <= P) next_push(nx, ny, map[nx][ny], dir);
		map[nx][ny] = num;
		people[num][0].x = nx;
		people[num][0].y = ny;
	}
}
void first_push(int x, int y, int num, int dir, int flag) {
	int nx, ny;
	if (!flag) { // 루돌프 -> 산타
		sum[num] += C;
		nx = x + dx[dir] * C;
		ny = y + dy[dir] * C;	
	}
	else { // 산타 -> 루돌프
		sum[num] += D;
		nx = x - dx[dir] * D;
		ny = y - dy[dir] * D;
	}
	if (1 > nx || nx > N || 1 > ny || ny > N) people[num][0].life = 0;
	else {
		people[num][0].sleep = 2;
		if (1 <= map[nx][ny] && map[nx][ny] <= P) {
			int ndir = dir;
			if (flag) {
				if (dir < 2) ndir += 2;
				else ndir -= 2;
			}
			next_push(nx, ny, map[nx][ny], ndir);
		}
		map[nx][ny] = num;
		people[num][0].x = nx;
		people[num][0].y = ny;
	}
}
void move_people() {
	for (int i = 1; i <= P; ++i) {
		if (!people[i][0].life || people[i][0].sleep) continue;
		int x = people[i][0].x;
		int y = people[i][0].y;
		int now_dist = pow((x - sx), 2) + pow((y - sy), 2);
		map[x][y] = 0;
		vector<info2> temp;
		for (int j = 0; j < 4; ++j) {
			int nx = x + dx2[j];
			int ny = y + dy2[j];
			int dist = pow((nx - sx), 2) + pow((ny - sy), 2);
			if (1 > nx || nx > N || 1 > ny || ny > N) continue;
			if (1 <= map[nx][ny] && map[nx][ny] <= P) continue;
			if (dist > now_dist) continue;
			I2 = { dist,nx,ny,j };
			temp.push_back(I2);
		}
		int nx, ny, nd;
		if (temp.size()) {
			sort(temp.begin(), temp.end(), cmp2);
			nx = temp[0].x;
			ny = temp[0].y;
			nd = temp[0].dir;
			if (map[nx][ny] == -1) first_push(nx, ny, i, nd, 1);
			else {
				map[nx][ny] = i;
				people[i][0].x = nx;
				people[i][0].y = ny;
			}
		}
		else {
			nx = x;
			ny = y;
			map[nx][ny] = i;
			people[i][0].x = nx;
			people[i][0].y = ny;
		}
	}
}
void move_deer() {
	vector<info2> temp;
	for (int i = 1; i <= P; ++i) {
		if (!people[i][0].life) continue;
		int px = people[i][0].x;
		int py = people[i][0].y;
		int dist = pow((sx - px), 2) + pow((sy - py), 2);
		I2 = { dist,px,py,0 };
		temp.push_back(I2);
	}
	sort(temp.begin(), temp.end(), cmp);
	int dest_x = temp[0].x;
	int dest_y = temp[0].y;
	int nx = 0;
	int ny = 0;
	int dir;
	if (sx > dest_x) nx = -1;
	else if (sx < dest_x) nx = 1;
	if (sy > dest_y) ny = -1;
	else if (sy < dest_y) ny = 1;
	for (int i = 0; i < 8; ++i) {
		if (nx == dx[i] && ny == dy[i]) {
			dir = i;
			break;
		}
	}
	map[sx][sy] = 0;
	sx += dx[dir];
	sy += dy[dir];
	if (1 <= map[sx][sy] && map[sx][sy] <= P) first_push(sx, sy, map[sx][sy], dir, 0);
	map[sx][sy] = -1;
}
void start() {
	for (int l = 1; l <= M; ++l) {
		move_deer();
		move_people();
		if (check()) break;
	}
	for (int i = 1; i <= P; ++i)
		cout << sum[i] << " ";
}
int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> N >> M >> P >> C >> D;
	cin >> sx >> sy;
	map[sx][sy] = -1;
	for (int i = 1; i <= P; ++i) {
		int num, x, y;
		cin >> num >> x >> y;
		I = { x,y,1,0 };
		people[num].push_back(I);
		map[x][y] = num;
	}
	start();
}
