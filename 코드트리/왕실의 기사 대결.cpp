// 매 턴마다 살아있는 기사들이 입은 데미지의 합을 구하는 것이 아닌
// Q턴 이후 살아있는 기사들이 입은 데미지의 합을 구해야 함(line 54)
#include<iostream>
#include<queue>
#include<cstring>
#include<vector>
#include<algorithm>
#define mp make_pair
using namespace std;
typedef struct {
	int r, c, h, w, hp, life;
}info;
info I;
queue<pair<int,int> > q;
vector<info> v;
int dx[4] = { -1,0,1,0 };
int dy[4] = { 0,1,0,-1 };
int map[41][41], board[41][41], sum[31];
bool moveCheck[31];
int L, N, Q;
void init() {
	while (!q.empty()) q.pop();
	memset(moveCheck, 0, sizeof(moveCheck));
}
void move(int num, int dir) {
	memset(board, 0, sizeof(board));
	for (int i = 1; i < v.size(); ++i) {
		if (!v[i].life) continue;
		int move_num = i;
		int cnt = 0;
		int r = v[move_num].r, c = v[move_num].c, h = v[move_num].h, w = v[move_num].w, hp = v[move_num].hp;
		for (int j = r; j < r + h; ++j) {
			for (int k = c; k < c + w; ++k) {
				if (moveCheck[move_num]) {
					board[j + dx[dir]][k + dy[dir]] = move_num;
					if (j == r && k == c) v[move_num].r = j + dx[dir], v[move_num].c = k + dy[dir];
					if (map[j + dx[dir]][k + dy[dir]] == 1) ++cnt;
				}
				else {
					board[j][k] = move_num;
				}
			}
		}
		if (num != move_num && moveCheck[move_num]) {
			if (hp - cnt <= 0) {
				for (int j = r; j < r + h; ++j)
					for (int k = c; k < c + w; ++k)
						board[j + dx[dir]][k + dy[dir]] = 0;
				v[move_num].life = 0;
			}
			else {
				v[move_num].hp = hp - cnt;
        //result += cnt;
				sum[move_num] += cnt;
			}
		}
	}
}
bool check(int num, int dir) {
	init();
	moveCheck[num] = 1;
	int r = v[num].r, c = v[num].c, h = v[num].h, w = v[num].w;
	int sr, sc, nr, nc, tnum;
	if (dir == 0 || dir == 2) {
		if (dir == 0) sr = r;
		else sr = r + h - 1;
		for (sc = c; sc < c + w; ++sc) {
			q.push(mp(sr,sc));
		}
	}
	else {
		if (dir == 1) sc = c + w - 1;
		else sc = c;
		for (sr = r; sr < r + h; ++sr) {
			q.push(mp(sr, sc));
		}
	}
	while (!q.empty()) {
		r = q.front().first;
		c = q.front().second;q.pop();
		nr = r + dx[dir];
		nc = c + dy[dir];
		if (1 > nr || nr > L || 1 > nc || nc > L || map[nr][nc] == 2) return false;
		if (board[nr][nc] && !moveCheck[board[nr][nc]]) {
			moveCheck[board[nr][nc]] = 1;
			int tr = v[board[nr][nc]].r, tc = v[board[nr][nc]].c, th = v[board[nr][nc]].h, tw = v[board[nr][nc]].w;
			if (dir == 0 || dir == 2) {
				if (dir == 0) sr = tr;
				else sr = tr + th - 1;
				for (sc = tc; sc < tc + tw; ++sc) {
					q.push(mp(sr,sc));
				}
			}
			else {
				if (dir == 1) sc = tc + tw - 1;
				else sc = tc;
				for (sr = tr; sr < tr + th; ++sr) {
					q.push(mp(sr, sc));
				}
			}
		}
	}
	return true;
}
void start() {
	for (int i = 1; i <= Q; ++i) {
		int num, dir;
		cin >> num >> dir;
		if (!v[num].life) continue;
		if (check(num, dir)) move(num, dir);
	}
	int result = 0;
	for (int i = 1; i <= N; ++i) {
		if (!v[i].life) continue;
		result += sum[i];
	}
	cout << result;
}
int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> L >> N >> Q;
	for (int i = 1; i <= L; ++i)
		for (int j = 1; j <= L; ++j)
			cin >> map[i][j];
	I = { 0,0,0,0,0,0 };
	v.push_back(I);
	for (int i = 1; i <= N; ++i) {
		int r, c, h, w, hp;
		cin >> r >> c >> h >> w >> hp;
		I = { r,c,h,w,hp,1 };
		v.push_back(I);
		for (int j = r; j < r + h; ++j)
			for (int k = c; k < c + w; ++k)
				board[j][k] = i;
	}
	start();
}
