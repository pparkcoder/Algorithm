// https://www.codetree.ai/frequent-problems/battle-ground/description

#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
typedef struct {
	int x, y, s, g, d;
}info;
info I;
vector<info> v;
vector<int> map[31][31];
int check[31][31], result[31];
int dx[4] = { -1,0,1,0 };
int dy[4] = { 0,1,0,-1 };
int k, n, m, x, y, s, g, d, nx, ny, nd;
void get_gun(int player, int num, int tx,int ty) {
	sort(map[tx][ty].begin(), map[tx][ty].end());
	int max_num = map[tx][ty][map[tx][ty].size() - 1];
	if (max_num > num) {
		v[player].g = max_num;
		map[tx][ty][map[tx][ty].size() - 1] = num;
	}
}
void start() {
	int win, lose, p1, p2, num, score;
	for (int l = 1; l <= k; ++l) {
		for (int i = 1; i < v.size(); ++i) {
			x = v[i].x;
			y = v[i].y;
			s = v[i].s;
			g = v[i].g;
			d = v[i].d;
			nx = x + dx[d];
			ny = y + dy[d];
			if (1 > nx || nx > n || 1 > ny || ny > n) {
				nx = x - dx[d];
				ny = y - dy[d];
				if (d < 2) d += 2;
				else d -= 2;
				v[i].d = d;
			}
			if (!check[nx][ny]) {
				if (map[nx][ny].size()) get_gun(i, g, nx, ny);
				v[i].x = nx;
				v[i].y = ny;
				check[x][y] = 0;
				check[nx][ny] = i;
			}
			else {
				check[x][y] = 0;
				num = check[nx][ny];
				p1 = s + g;
				p2 = v[num].s + v[num].g;
				if (p1 > p2) win = i, lose = num;
				else if (p1 < p2) win = num, lose = i;
				else {
					if (s > v[num].s) win = i, lose = num;
					else win = num, lose = i;
				}
				score = (v[win].s + v[win].g) - (v[lose].s + v[lose].g);
				result[win] += score;
				//진놈 로직
				map[nx][ny].push_back(v[lose].g), v[lose].g = 0;
				int nd = v[lose].d, lose_nx, lose_ny;
				while (1) {
					lose_nx = nx + dx[nd];
					lose_ny = ny + dy[nd];
					if (!(1 > lose_nx || lose_nx > n || 1 > lose_ny || lose_ny > n || check[lose_nx][lose_ny])) {
						get_gun(lose, v[lose].g, lose_nx, lose_ny);
						v[lose].x = lose_nx;
						v[lose].y = lose_ny;
						v[lose].d = nd;
						check[nx][ny] = 0;
						check[lose_nx][lose_ny] = lose;
						break;
					}
					else {
						if (++nd > 3) nd = 0;
					}
				}
				//이긴놈 로직
				get_gun(win, v[win].g, nx, ny);
				v[win].x = nx;
				v[win].y = ny;
				check[nx][ny] = win;
			}
		}
	}
	for (int i = 1; i <= m; ++i)
		cout << result[i] << " ";
	
}
int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int temp;
	cin >> n >> m >> k;
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j) {
			cin >> temp;
			map[i][j].push_back(temp);
		}
	}
	I = { -1,-1,-1,-1,-1 };
	v.push_back(I);
	for (int i = 1; i <= m; ++i) {
		cin >> x >> y >> d >> s;
		I = { x,y,s,0,d };
		v.push_back(I);
		check[x][y] = i;
	}
	start();
}
