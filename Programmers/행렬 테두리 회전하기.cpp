// 2021 Dev-Matching
// https://programmers.co.kr/learn/courses/30/lessons/77485

#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;
int map[101][101];
int dx[4] = { 0,1,0,-1 };
int dy[4] = { 1,0,-1,0 };
int turn(int x1, int y1, int x2, int y2) {
	int now, pre, dir, x, y, nx, ny, result;
	result = 9876543241;
	dir = 0;
	x = x1;
	y = y1;
	pre = map[x][y];
	while (1) {
		result = min(result, map[x][y]);
		nx = x + dx[dir];
		ny = y + dy[dir];
		if (x1 > nx || nx > x2 || y1 > ny || ny > y2) {
			++dir;
			nx = x + dx[dir];
			ny = y + dy[dir];
		}
       		if(dir > 3) break;
		now = map[nx][ny];
		map[nx][ny] = pre;
		pre = now;
		x = nx;
		y = ny;
	}
	return result;
}
vector<int> solution(int r, int c, vector<vector<int>> v) {
	vector<int> answer;
	int num = 1;
	for (int i = 1; i <= r; ++i)
		for (int j = 1; j <= c; ++j)
			map[i][j] = num++;
	for (int i = 0; i < v.size(); ++i)
		answer.push_back(turn(v[i][0], v[i][1], v[i][2], v[i][3]));
	return answer;
}
