// https://www.acmicpc.net/problem/17136

#include<iostream>
#include<algorithm>
using namespace std;
int map[11][11];
int paper[6] = { 0,5,5,5,5,5 };
int result = 987654321;
bool find() {
	for (int i = 1; i < 11; i++)
		for (int j = 1; j < 11; j++)
			if (map[i][j]) return false;
	return true;
}
pair<int, int> range(int len) {
	for (int i = 1; i < 11; i++) {
		for (int j = 1; j < 11; j++) {
			if (map[i][j]) {
				for (int k = i; k < i + len; k++)
					for (int l = j; l < j + len; l++)
						if (!map[k][l]) return make_pair(0, 0);
				return make_pair(i, j);
			}
		}
	}
	return make_pair(0, 0);
}
void patch(pair<int, int> p, int len, int num) {
	int x = p.first;
	int y = p.second;
	for (int i = x; i < x + len; i++)
		for (int j = y; j < y + len; j++)
			map[i][j] = num;
}
void dfs(int cnt) {
	if (find()) {
		result = min(result, cnt);
		return;
	}
	for (int i = 5; i > 0; i--) {
		if (paper[i]) {
			pair<int, int> p = range(i);
			if (p.first) {--paper[i];
				patch(p, i, 0);
				dfs(cnt + 1);
				patch(p, i, 1);
				++paper[i];
			}
		}
	}
}
int main() {
	ios::sync_with_stdio(false); cin.tie(0);
	for (int i = 1; i < 11; i++)
		for (int j = 1; j < 11; j++)
			cin >> map[i][j];
	for (int i = 1; i < 6; i++)
	dfs(0);
	result == 987654321 ? cout << -1 : cout << result;
}
