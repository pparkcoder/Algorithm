// https://www.acmicpc.net/problem/17471
// Tip -> dfs로 되지 않는 구조 존재, 브루트포스 사용

#include<iostream>
#include<queue>
#include<algorithm>
#include<cmath>
#include<cstring>
#include<vector>
using namespace std;
queue<int> q;
vector<int> v[11];
int people[11];
bool visit[11], v_visit[11];
int result = 987654321;
int n, num1, num2;
bool check(int num) {
	memset(visit, 0, sizeof(visit));
	for (int i = 1; i <= n; ++i) {
		if (v_visit[i] == num) {
			q.push(i);
			visit[i] = 1;
			break;
		}
	}
	while (!q.empty()) {
		int now = q.front(); q.pop();
		for (int i = 0; i < v[now].size(); ++i) {
			int next = v[now][i];
			if (v_visit[next] == num && !visit[next]) {
				q.push(next);
				visit[next] = 1;
			}
		}
	}
	for (int i = 1; i <= n; ++i)
		if (v_visit[i] == num && !visit[i]) return false;
	return true;
}
int calc() {
	int ans1 = 0, ans2 = 0;
	for (int i = 1; i <= n; ++i) {
		if (v_visit[i]) ans1 += people[i];
		else ans2 += people[i];
	}
	return abs(ans1 - ans2);
}
void brute(int num, int flag) {
	if (flag && check(1) && check(0))
		result = min(result, calc());
	if (num == n) return;
	for (int i = num; i <= n; ++i) {
		if (!v_visit[i]) {
			v_visit[i] = 1;
			brute(i + 1, 1);
			v_visit[i] = 0;
		}
	}
}
int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> n;
	for (int i = 1; i <= n; ++i)
		cin >> people[i];
	for (int i = 1; i <= n; ++i) {
		cin >> num1;
		while (num1--) {
			cin >> num2;
			v[i].push_back(num2);
		}
	}
	brute(1, 0);
	result = (result == 987654321 ? -1 : result);
	cout << result;
}
