#include<iostream>
#include<vector>
#include<cstring>
#include<queue>
#include<algorithm>
#define mp make_pair
using namespace std;
vector<pair<int, int> >v, temp;
queue<pair<int, int> > q;
int dx[6] = { 0,0,-1,1,1,1 }; // 짝
int dy[6] = { -1,1,0,0,-1,1 };
int dx2[6] = { 0,0,-1,1,-1,-1 }; // 홀
int dy2[6] = { -1,1,0,0,-1,1 };
int map[16][16];
bool visit[16][16], visit2[16][16];
int t, w, h, result;
int check(int now_x, int now_y) {
	memset(visit2, 0, sizeof(visit2));
	q.push(mp(now_x, now_y));
	visit2[now_x][now_y] = 1;
	int x,y, nx, ny;
	while (!q.empty()) {
		x = q.front().first;
		y = q.front().second; q.pop();
		for (int i = 0; i < 6; ++i) {
			if (y % 2) nx = x + dx2[i], ny = y + dy2[i];
			else nx = x + dx[i], ny = y + dy[i];
			if (0 < nx && nx <= h && 0 < ny && ny <= w && visit[nx][ny] && !visit2[nx][ny]) {
				q.push(mp(nx, ny));
				visit2[nx][ny] = 1;
			}
		}
	}
	int sum = 0;
	for (int i = 0; i < v.size(); ++i) {
		int x = v[i].first;
		int y = v[i].second;
		if (!visit2[x][y]) return -1;
		sum += map[x][y];
	}
	return sum * sum;
}
void brute(int index, int cnt) {
	if (cnt == 4) {
		int sum = check(v[0].first,v[0].second);
		if (sum > -1) result = max(result, sum);
		return;
	}
	for(int i=index;i<temp.size();++i){
		int x = temp[i].first;
		int y = temp[i].second;
		if (!visit[x][y]) {
			visit[x][y] = 1;
			v.push_back(mp(x, y));
			brute(i+1,cnt + 1);
			v.pop_back();
			visit[x][y] = 0;
		}
	}
}
int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> t;
	for (int l = 1; l <= t; ++l) {
		cin >> w >> h;
		for (int i = 1; i <= h; ++i) {
			for (int j = 1; j <= w; ++j) {
				cin >> map[i][j];
				temp.push_back(mp(i, j));
			}
		}
		brute(0, 0);
		cout << "#" << l << " " << result << "\n";
		v.clear();
	}
}
