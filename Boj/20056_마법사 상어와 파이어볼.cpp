// https://www.acmicpc.net/problem/20056
// map 자체가 공 모양으로 이어져 있다고 생각
// Tip -> 파이어볼 이동 시 반복문 보다는 % 연산을 적용하면 더 빠르다

#include<iostream>
#include<vector>
using namespace std;
typedef struct {
	int r, c, m, s, d;
}info;
typedef struct {
	int m, s, d;
}info2;
info INFO;
info2 INFO2;
vector<info> v;
vector<info2> map[51][51];
int dx[8] = { -1,-1,0,1,1,1,0,-1 };
int dy[8] = { 0,1,1,1,0,-1,-1,-1 };
int N, M, k, r, c, m, s, d;
int result = 0;
void check() {
	v.clear();
	int temp_size, temp_d, sum_m, sum_s, flag;
	for (int i = 1; i <= N; ++i) {
		for (int j = 1; j <= N; ++j) {
			temp_size = map[i][j].size();
			if (temp_size) {
				if (temp_size == 1) {
					INFO = { i,j,map[i][j][0].m,map[i][j][0].s ,map[i][j][0].d };
					v.push_back(INFO);
				}
				else {
					flag = sum_m = sum_s = 0;
					temp_d = map[i][j][0].d % 2;
					for (int l = 0; l < temp_size; ++l) {
						sum_m += map[i][j][l].m;
						sum_s += map[i][j][l].s;
						if (l && !flag && map[i][j][l].d % 2 != temp_d) flag = 1;
					}
					if (sum_m / 5) {
						for (int l = flag; l < 8; l += 2) {
							INFO = { i,j,sum_m / 5,sum_s / temp_size,l };
							v.push_back(INFO);
						}
					}
				}
				map[i][j].clear();
			}
		}
	}
}
void start() {
	int ns, nr, nc;
	for (int l = 1; l <= k; ++l) {
		for (int i = 0; i < v.size(); ++i) {
			r = v[i].r;
			c = v[i].c;
			m = v[i].m;
			s = v[i].s;
			d = v[i].d;
			ns = s % N;
			nr = r + dx[d] * ns;
			nc = c + dy[d] * ns;
			if (nr > N) nr -= N;
			else if (nr < 1) nr += N;
			if (nc > N) nc -= N;
			else if (nc < 1) nc += N;
			INFO2 = { m,s,d };
			map[nr][nc].push_back(INFO2);
		}
		check();
	}
	for (int i = 0; i < v.size(); ++i)
		result += v[i].m;
	cout << result;
}
int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> N >> M >> k;
	for (int i = 0; i < M; ++i) {
		cin >> r >> c >> m >> s >> d;
		INFO = { r,c,m,s,d };
		v.push_back(INFO);
	}
	start();
}
