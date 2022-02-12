#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
vector<int> v;
char map[11][11];
char cmap[11][11];
int dx[4] = { 0,0,-1,1 };
int dy[4] = { -1,1,0,0 };
int result = 987654321;
int n, m, rx, ry, bx, by, nrx, nry, nbx, nby, orx, ory, obx, oby, temp;
void move(int x, int y, int dir, int num) {
	cmap[x][y] = '.';
	if (num) {
		for (int i = 1;; i++) {
			nrx = x + dx[dir] * i;
			nry = y + dy[dir] * i;
			if (cmap[nrx][nry] == '#') {
				nrx -= dx[dir];
				nry -= dy[dir];
				break;
			}
			if (cmap[nrx][nry] == 'O') break;
		}
	}
	else {
		for (int i = 1;; i++) {
			nbx = x + dx[dir] * i;
			nby = y + dy[dir] * i;
			if (cmap[nbx][nby] == '#') {
				nbx -= dx[dir];
				nby -= dy[dir];
				break;
			}
			if (cmap[nbx][nby] == 'O') break;
		}
	}
}
int finish(int dir) {
	if (nrx == nbx && nry == nby) {
		int r_len = abs(nrx - rx) + abs(nry - ry);
		int b_len = abs(nbx - bx) + abs(nby - by);
		if (r_len > b_len) {
			nrx -= dx[dir];
			nry -= dy[dir];
		}
		else {
			nbx -= dx[dir];
			nby -= dy[dir];
		}
	}
	else{
		if (cmap[nbx][nby] == 'O') return -1;
		if (cmap[nrx][nry] == 'O') return 1;
	}
	cmap[nrx][nry] = 'R';
	cmap[nbx][nby] = 'B';
	rx = nrx, ry = nry;
	bx = nbx, by = nby;
	return 0;
}
void brute(int pre, int cnt) {
	if (cnt == 10) {
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= m; j++)
				cmap[i][j] = map[i][j];
		rx = orx, ry = ory, bx = obx, by = oby;
		for (int i = 1; i < 11; i++) {
			move(rx, ry, v[i - 1], 1);
			move(bx, by, v[i - 1], 0);
			temp = finish(v[i - 1]);
			if (temp < 0) break;
			if (temp > 0) {
				result = min(result, i);
				break;
			}
		}
		return;
	}
	for (int i = 0; i < 4; i++) {
		if (pre == i) continue;
		v.push_back(i);
		brute(i, cnt + 1);
		v.pop_back();
	}
}
int main() {
	ios::sync_with_stdio(false); cin.tie(0);
	cin >> n >> m;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			cin >> map[i][j];
			if (map[i][j] == 'R') orx = i, ory = j;
			else if (map[i][j] == 'B') obx = i, oby = j;
		}
	}
	brute(-1, 0);
	result == 987654321 ? cout << -1 : cout << result;
}

//#include<iostream>
//#include<algorithm>
//#include<vector>
//#include<cmath>
//#define mp make_pair
//#define upgrade ios::sync_with_stdio(0); cin.tie(0);
//using namespace std;
//char map[11][11], cmap[11][11];
//int dx[4] = { 0,0,-1,1 };
//int dy[4] = { -1,1,0,0 };
//vector<int> v;
//int result = 987654321;
//int n, m, start_red_x, start_red_y, start_blue_x, start_blue_y;
//int move() {
//	int now_red_x = start_red_x, now_red_y = start_red_y, now_blue_x = start_blue_x, now_blue_y = start_blue_y;
//	int dir, next_red_x, next_red_y, next_blue_x, next_blue_y, temp_red_x, temp_red_y, temp_blue_x, temp_blue_y, red_len, blue_len, red_flag, blue_flag;
//	for (int i = 0; i < 10; ++i) {
//		map[now_red_x][now_red_y] = map[now_blue_x][now_blue_y] = '.';
//		dir = v[i];
//		temp_red_x = now_red_x;
//		temp_red_y = now_red_y;
//		red_flag = 0, blue_flag = 0;
//		while (1) {
//			next_red_x = now_red_x + dx[dir];
//			next_red_y = now_red_y + dy[dir];
//			if (map[next_red_x][next_red_y] == '#') break;
//			if (map[next_red_x][next_red_y] == 'O') {
//				red_flag = 1;
//				break;
//			}
//			now_red_x = next_red_x;
//			now_red_y = next_red_y;
//		}
//		temp_blue_x = now_blue_x;
//		temp_blue_y = now_blue_y;
//		while (1) {
//			next_blue_x = now_blue_x + dx[dir];
//			next_blue_y = now_blue_y + dy[dir];
//			if (map[next_blue_x][next_blue_y] == '#') break;
//			if (map[next_blue_x][next_blue_y] == 'O') {
//				blue_flag = 1;
//				break;
//			}
//			now_blue_x = next_blue_x;
//			now_blue_y = next_blue_y;
//		}
//		if (red_flag && !blue_flag) return i + 1;
//		if ((red_flag && blue_flag) || (!red_flag && blue_flag)) return 987654321;
//		if (now_red_x == now_blue_x && now_red_y == now_blue_y) {
//			red_len = abs(now_red_x - temp_red_x) + abs(now_red_y - temp_red_y);
//			blue_len = abs(now_blue_x - temp_blue_x) + abs(now_blue_y - temp_blue_y);
//			if (red_len < blue_len) now_blue_x -= dx[dir], now_blue_y -= dy[dir];
//			else now_red_x -= dx[dir], now_red_y -= dy[dir];
//		}
//		map[now_red_x][now_red_y] = 'R';
//		map[now_blue_x][now_blue_y] = 'B';
//	}
//	return 987654321;
//}
//void brute(int pre_dir, int cnt) {
//	if (cnt == 10) {
//		for (int i = 1; i <= n; ++i)
//			for (int j = 1; j <= m; ++j)
//				map[i][j] = cmap[i][j];
//		result = min(result, move());
//		return;
//	}
//	for (int i = 0; i < 4; ++i) {
//		if (i == pre_dir) continue;
//		v.push_back(i);
//		brute(i, cnt + 1);
//		v.pop_back();
//	}
//}
//int main() {
//	upgrade;
//	cin >> n >> m;
//	for (int i = 1; i <= n; ++i) {
//		for (int j = 1; j <= m; ++j) {
//			cin >> cmap[i][j];
//			if (cmap[i][j] == 'R') start_red_x = i, start_red_y = j, cmap[i][j] = '.';
//			else if (cmap[i][j] == 'B') start_blue_x = i, start_blue_y = j, cmap[i][j] = '.';
//		}
//	}
//	brute(-1, 0);
//	result = (result == 987654321 ? -1 : result);
//	cout << result;
//}
