// https://www.codetree.ai/frequent-problems/tree-kill-all/description
// 제초제 선정위치는 벽과 제초제가 뿌려진 위치를 제외한 모든점에서 생각 -> 선정된 점이 나무가 없는 점이면 그곳만 처리하고 continue
// 나무가 없거나 제초제가 뿌려진 위치에서는 더 이상 전파x

#include<iostream>
#include<vector>
#include<algorithm>
#define mp make_pair
using namespace std;
typedef struct {
	int x, y, num;
}info;
info I;
vector<info> tree, v;
int map[21][21], memo[21][21], check[21][21];
int dx1[4] = { 0,0,-1,1 };
int dy1[4] = { -1,1,0,0 };
int dx2[4] = { -1,-1,1,1 };
int dy2[4] = { -1,1,-1,1 };
int n, m, limit, c, len;
int result = 0;
bool cmp(info a, info b) {
	if (a.num == b.num) {
		if (a.x == b.x) return a.y < b.y;
		else return a.x < b.x;
	}
	else return a.num > b.num;
}
void kill() {
	int nx, ny, sum;
	for (int x = 1; x <= n; ++x) {
		for (int y = 1; y <= n; ++y) {
			if (map[x][y] < 0) continue;
			sum = map[x][y];
			if (sum) {
				for (int k = 0; k < 4; ++k) {
					for (int l = 1; l <= limit; ++l) {
						nx = x + dx2[k] * l;
						ny = y + dy2[k] * l;
						if (1 > nx || nx > n || 1 > ny || ny > n || map[nx][ny] < 1) break;
						sum += map[nx][ny];
					}
				}
			}
			I = { x,y,sum };
			v.push_back(I);
		}
	}
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j) {
			if (check[i][j] > 0 && --check[i][j] <= 0) {
				check[i][j] = map[i][j] = 0;
			}
		}
	}
	sort(v.begin(), v.end(), cmp);
	result += v[0].num;
	int x = v[0].x;
	int y = v[0].y;
	int pre = map[x][y];
	map[x][y] = -2;
	check[x][y] = c;
	v.clear();
	if (pre < 1) return;
	for (int i = 0; i < 4; ++i) {
		for (int j = 1; j <= limit; ++j) {
			nx = x + dx2[i] * j;
			ny = y + dy2[i] * j;
			if (0 < nx && nx <= n && 0 < ny && ny <= n) {
				if (map[nx][ny] == -1) break;
				if (map[nx][ny] == -2 || !map[nx][ny]) {
					map[nx][ny] = -2;
					check[nx][ny] = c;
					break;
				}
				map[nx][ny] = -2;
				check[nx][ny] = c;
			}
		}
	}
}
void spread() {
	int x, y, num, nx, ny, cnt;
	for (int i = 0; i < len; ++i) {
		x = tree[i].x;
		y = tree[i].y;
		num = tree[i].num;
		cnt = 0;
		vector<pair<int, int> > temp;
		for (int j = 0; j < 4; ++j) {
			nx = x + dx1[j];
			ny = y + dy1[j];
			if (0 < nx && nx <= n && 0 < ny && ny <= n && !map[nx][ny]) {
				++cnt;
				temp.push_back(mp(nx, ny));
			}
		}
		for (int j = 0; j < temp.size(); ++j) 
			memo[temp[j].first][temp[j].second] += (num / cnt);
	}
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j) {
			if (map[i][j] >= 0) {
				map[i][j] += memo[i][j];
				memo[i][j] = 0;
			}
		}
	}
}
void grow() {
	int x, y, num, nx, ny, cnt;
	for (int i = 0; i < len; ++i) {
		x = tree[i].x;
		y = tree[i].y;
		num = tree[i].num;
		cnt = 0;
		for (int j = 0; j < 4; ++j) {
			nx = x + dx1[j];
			ny = y + dy1[j];
			if (0 < nx && nx <= n && 0 < ny && ny <= n && map[nx][ny] > 0) ++cnt;
		}
		map[x][y] += cnt;
		tree[i].num = map[x][y];
	}
}
void make_tree() {
	tree.clear();
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j) {
			if (map[i][j] > 0) {
				I = { i,j,map[i][j] };
				tree.push_back(I);
			}
		}
	}
	len = tree.size();
}
int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> n >> m >> limit >> c;
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= n; ++j)
			cin >> map[i][j];
	for (int i = 1; i <= m; ++i) {
		make_tree();
		grow();
		spread();
		kill();
	}
	cout << result;
}
