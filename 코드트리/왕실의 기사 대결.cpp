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

// 재귀 사용
#include<iostream>
#include<vector>
#include<algorithm>
#include<cstring>
#define mp make_pair
using namespace std;

typedef struct {
	int x, y, h, w, k, life;
}info;
info I;
info people[31];
vector<pair<int, int> > order;
vector<int> move_list;
int dx[4] = { -1,0,1,0 };
int dy[4] = { 0,1,0,-1 };
int map[41][41], holl[41][41]; // 1 : 함정, 2 : 벽
int score[31], visit[31];
int L, N, Q;
bool len_check(int x, int y) {
	if (1 > x || x > L || 1 > y || y > L || holl[x][y] == 2) return false;
	return true;
}
void damage() {
	for (int t = 0; t < move_list.size() - 1; ++t) {
		int num = move_list[t];
		int x = people[num].x;
		int y = people[num].y;
		int h = people[num].h;
		int w = people[num].w;
		int k = people[num].k;
		int cnt = 0;
		for (int i = x; i < x + h; ++i) {
			for (int j = y; j < y + w; ++j) {
				if (holl[i][j] == 1) ++cnt;
			}
		}
		int nk = k - cnt;
		if (nk <= 0) {
			people[num].life = 0;
			for (int i = x; i < x + h; ++i)
				for (int j = y; j < y + w; ++j)
					map[i][j] = 0;
		}
		else {
			people[num].k = nk;
			score[num] += cnt;
		}
	}
}
void move(int dir) {
	reverse(move_list.begin(), move_list.end());
	for (int t = 0; t < move_list.size(); ++t) {
		int num = move_list[t];
		int x = people[num].x;
		int y = people[num].y;
		int h = people[num].h;
		int w = people[num].w;
		for (int i = x; i < x + h; ++i)
			for (int j = y; j < y + w; ++j)
				map[i][j] = 0;
	}
	for (int t = 0; t < move_list.size(); ++t) {
		int num = move_list[t];
		int x = people[num].x;
		int y = people[num].y;
		int h = people[num].h;
		int w = people[num].w;
		int k = people[num].k;
		for (int i = x; i < x + h; ++i) {
			for (int j = y; j < y + w; ++j) {
				int nx = i + dx[dir];
				int ny = j + dy[dir];
				map[nx][ny] = num;
				if (x == i && y == j) {
					people[num].x = nx;
					people[num].y = ny;
				}
			}
		}
	}
}
bool move_check(int num, int d) {
	move_list.push_back(num);
	visit[num] = 1;
	int x = people[num].x;
	int y = people[num].y;
	int h = people[num].h;
	int w = people[num].w;
	int nx, ny;
	if (d == 0) {
		for (int i = y; i < y + w; ++i) {
			nx = x + dx[d];
			ny = i + dy[d];
			if (!len_check(nx, ny)) return false;
			if (map[nx][ny] && !visit[map[nx][ny]]) {
				if (!move_check(map[nx][ny], d)) return false;
			}
		}
	}
	else if (d == 1) {
		for (int i = x; i < x + h; ++i) {
			nx = i + dx[d];
			ny = (y + w - 1) + dy[d];
			if (!len_check(nx, ny)) return false;
			if (map[nx][ny] && !visit[map[nx][ny]]) {
				if (!move_check(map[nx][ny], d)) return false;
			}
		}
	}
	else if (d == 2) {
		for (int i = y; i < y + w; ++i) {
			nx = (x + h - 1) + dx[d];
			ny = i + dy[d];
			if (!len_check(nx, ny)) return false;
			if (map[nx][ny] && !visit[map[nx][ny]]) {
				if (!move_check(map[nx][ny], d)) return false;
			}
		}
	}
	else if (d == 3) {
		for (int i = x; i < x + h; ++i) {
			nx = i + dx[d];
			ny = y + dy[d];
			if (!len_check(nx, ny)) return false;
			if (map[nx][ny] && !visit[map[nx][ny]]) {
				if (!move_check(map[nx][ny], d)) return false;
			}
		}
	}
	return true;
}
void start() {
	int result = 0;
	for (int i = 0; i < order.size(); ++i) {
		move_list.clear();
		memset(visit, 0, sizeof(visit));
		int num = order[i].first;
		int dir = order[i].second;
		if (!people[num].life || !move_check(num, dir)) continue;
		move(dir);
		damage();
	}
	for (int i = 1; i <= N; ++i) {
		if (!people[i].life) continue;
		result += score[i];
	}
	cout << result;
}
int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> L >> N >> Q;
	for (int i = 1; i <= L; ++i)
		for (int j = 1; j <= L; ++j)
			cin >> holl[i][j];
	for (int t = 1; t <= N; ++t) {
		int x, y, h, w, k;
		cin >> x >> y >> h >> w >> k;
		I = { x,y,h,w,k,1 };
		people[t] = I;
		for (int i = x; i < x + h; ++i)
			for (int j = y; j < y + w; ++j)
				map[i][j] = t;
	}
	for (int i = 1; i <= Q; ++i) {
		int num, dir;
		cin >> num >> dir;
		order.push_back(mp(num, dir));
	}
	start();
}
