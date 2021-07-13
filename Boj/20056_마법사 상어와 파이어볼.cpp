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
info I;
info2 I2;
vector<info2> map[51][51];
vector<info> v;
vector<int> temp;
int dx[8] = { -1,-1,0,1,1,1,0,-1 };
int dy[8] = { 0,1,1,1,0,-1,-1,-1 };
int N, M, t, r, c, m, s, d;
void start() {
	int result = 0;
	int len, ns, nr, nc, temp_m, temp_s, dir;
	while (t--) {
		for (int i = 0; i < v.size(); ++i) {
			r = v[i].r;
			c = v[i].c;
			m = v[i].m;
			s = v[i].s;
			d = v[i].d;
			ns = s % N; // 이동 후 최종 위치를 결정
			nr = r + dx[d] * ns;
			nc = c + dy[d] * ns;
			if (nr < 1) nr += N;
			else if (nr > N) nr -= N;
			if (nc < 1) nc += N;
			else if (nc > N) nc -= N;
			I2 = { m,s,d };
			map[nr][nc].push_back(I2);
		}
		v.clear();
		for (int i = 1; i <= N; ++i) {
			for (int j = 1; j <= N; ++j) {
				len = map[i][j].size();
				if (len >= 1) {
					if (len > 1) {
						temp_m = temp_s = dir = 0;
						temp.clear();
						for (int k = 0; k < len; ++k) {
							temp_m += map[i][j][k].m;
							temp_s += map[i][j][k].s;
							temp.push_back(map[i][j][k].d);
						}
						for (int k = 1; k < temp.size(); ++k) {
							if (temp[k - 1] % 2 != temp[k] % 2) {
								dir = 1;
								break;
							}
						}
						temp_m /= 5;
						temp_s /= len;
						if (temp_m) {
							for (int k = 0; k < 4; ++k, dir += 2) {
								I = { i,j,temp_m,temp_s,dir };
								v.push_back(I);
							}
						}
					}
					else {
						I = { i,j,map[i][j][0].m,map[i][j][0].s,map[i][j][0].d };
						v.push_back(I);
					}
					map[i][j].clear();
				}
			}
		}
	}
	for (int i = 0; i < v.size(); ++i) 
		result += v[i].m;
	cout << result;
}
int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> N >> M >> t;
	while (M--) {
		cin >> r >> c >> m >> s >> d;
		I = { r,c,m,s,d };
		v.push_back(I);
	}
	start();
}
