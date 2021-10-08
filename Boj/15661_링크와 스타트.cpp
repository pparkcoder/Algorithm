// https://www.acmicpc.net/problem/15661

#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
int map[21][21];
bool check[21];
int result = 987654321;
int n;
void start() {
	int sum1 = 0, sum2 = 0;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if (check[i] && check[j]) sum1 += map[i][j];
			else if (!check[i] && !check[j]) sum2 += map[i][j];
		}
	}
	result = min(result, abs(sum1 - sum2));
}
void dfs(int cnt, int index) {
	if (cnt) start();
	if (cnt == n) return;
	for (int i = index; i <= n; i++) {
		check[i] = 1;
		dfs(cnt + 1, i + 1);
		check[i] = 0;
	}
}
int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> n;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			cin >> map[i][j];
	dfs(0, 1);
	cout << result;
}
