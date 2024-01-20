// red, blue 모든 이동경로 후 저장
// 모든 이동경로 비교하며 조건 만족하는지 확인

#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#include <climits>
#include <iostream>
#define mp make_pair
using namespace std;
vector<vector<pair<int, int> > > red, blue; // 공 별 이동경로 저장
int dx[4] = { 0,0,-1,1 };
int dy[4] = { -1,1,0,0 };
int map[5][5], visit[5][5];
int n, m;
pair<int, int> red_start, blue_start, red_dest, blue_dest;
void dfs(int num, int x, int y, vector<pair<int, int> > dist) { // 모든 이동경로 찾기
	if (num == 1) {
		if (x == red_dest.first && y == red_dest.second) {
			red.push_back(dist);
			return;
		}
	}
	else {
		if (x == blue_dest.first && y == blue_dest.second) {
			blue.push_back(dist);
			return;
		}
	}
	vector<pair<int, int> > temp = dist;
	for (int i = 0; i < 4; ++i) {
		int nx = x + dx[i];
		int ny = y + dy[i];
		if (0 < nx && nx <= n && 0 < ny && ny <= m) {
			if (!visit[nx][ny] && map[nx][ny] != 5) {
				visit[nx][ny] = 1;
				temp.push_back(mp(nx, ny));
				dfs(num, nx, ny, temp);
				temp.pop_back();
				visit[nx][ny] = 0;
			}
		}
	}
}
int check(int red_index, int blue_index, int max_len) {
	int rx, ry, bx, by, rnx, rny, bnx, bny;
	for (int i = 0; i < max_len; ++i) {
		if (red[red_index].size() > i) rx = red[red_index][i].first, ry = red[red_index][i].second;
		if (blue[blue_index].size() > i) bx = blue[blue_index][i].first, by = blue[blue_index][i].second;
		if (rx == bx && ry == by) return 0;
		if (i + 1 < max_len) {
			rnx = red[red_index][i + 1].first;
			rny = red[red_index][i + 1].second;
			bnx = blue[blue_index][i + 1].first;
			bny = blue[blue_index][i + 1].second;
			if (rx == bnx && ry == bny && bx == rnx && by == rny) return 0;
		}
	}
	return max_len;
}
int solution(vector<vector<int>> maze) {
  int answer = 0;
	int result = INT_MAX;
	vector<pair<int, int> > temp;
	n = maze.size();
	m = maze[0].size();
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) {
			int num = maze[i - 1][j - 1];
			if (num == 1) red_start.first = i, red_start.second = j;
			else if (num == 3) red_dest.first = i, red_dest.second = j;
			else if (num == 2) blue_start.first = i, blue_start.second = j;
			else if (num == 4) blue_dest.first = i, blue_dest.second = j;
			else map[i][j] = num;
		}
	}
	// red 경로 입력
	visit[red_start.first][red_start.second] = 1;
	temp.push_back(mp(red_start.first, red_start.second));
	dfs(1, red_start.first, red_start.second, temp);
	temp.pop_back();
	visit[red_start.first][red_start.second] = 0;
  
	// blue 경로 입력
	visit[blue_start.first][blue_start.second] = 1;
	temp.push_back(mp(blue_start.first, blue_start.second));
	dfs(2, blue_start.first, blue_start.second, temp);
	temp.pop_back();
	visit[blue_start.first][blue_start.second] = 0;
	
	for (int i = 0; i < red.size(); ++i) {
		for (int j = 0; j < blue.size(); ++j) {
			int max_len = max(red[i].size(), blue[j].size());
			answer = check(i, j, max_len);
			if (answer) result = min(result, answer);
		}
	}
	return (result == INT_MAX ? 0 : result - 1);
}
