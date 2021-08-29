// https://www.acmicpc.net/problem/1525

#include<iostream>
#include<queue>
#include<string>
#include<map>
using namespace std;
typedef struct {
	int x, y;
	string s;
}info;
info I;
queue<info> q;
map<string, int> visit;
char board[4][4];
int dx[4] = { 0,0,-1,1 };
int dy[4] = { -1,1,0,0 };
string target = "123456780";
void make_arr(string s) {
	int index = 0;
	for (int i = 1; i < 4; i++)
		for (int j = 1; j < 4; j++)
			board[i][j] = s[index++];
}
string check(int x, int y, int nx, int ny, string s) {
	int index1, index2;
	char temp;
	for (int i = 0; i < s.length(); i++) {
		if (s[i] == board[x][y]) index1 = i;
		else if (s[i] == board[nx][ny]) index2 = i;
	}
	temp = s[index1];
	s[index1] = s[index2];
	s[index2] = temp;
	return s;
}
int bfs(int sx, int sy, string ss) {
	I = { sx,sy,ss };
	q.push(I);
	visit[ss] = 1;
	while (!q.empty()) {
		int x = q.front().x;
		int y = q.front().y;
		string s = q.front().s; q.pop();
		if (s == target) return visit[s] - 1;
		make_arr(s);
		for (int i = 0; i < 4; i++) {
			int nx = x + dx[i];
			int ny = y + dy[i];
			if (0 < nx && nx < 4 && 0 < ny && ny < 4) {
				string temp = check(x, y, nx, ny, s);
				if (!visit[temp]) {
					I = { nx,ny,temp };
					q.push(I);
					visit[temp] = visit[s] + 1;
				}
			}
		}
	}
	return -1;
}
int main() {
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	int sx, sy;
	char c;
	string s = "";
	for (int i = 1; i < 4; i++) {
		for (int j = 1; j < 4; j++) {
			cin >> c;
			if (c == '0') sx = i, sy = j;
			s += c;
		}
	}
	if (target != s) cout << bfs(sx, sy, s);
	else cout << 0;
}
