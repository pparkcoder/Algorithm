// https://www.acmicpc.net/problem/17471
// Tip -> dfs로 되지 않는 구조 존재, 브루트포스 사용

#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>
#include<cstring>
#include<climits>
using namespace std;
vector<int> v[11], v2;
queue<int> q;
bool choice[11], visit[11];
int people[11];
int n;
int result = INT_MAX;
bool check(int flag) {
	memset(visit, 0, sizeof(visit));
	for (int i = 1; i <= n; ++i) {
		if (choice[i] == flag) {
			q.push(i);
			visit[i] = 1;
			break;
		}
	}
	while (!q.empty()) {
		int now = q.front(); q.pop();
		for (int i = 0; i < v[now].size(); ++i) {
			int next = v[now][i];
			if (choice[next] == flag && !visit[next]) {
				q.push(next);
				visit[next] = 1;
			}
		}
	}
	for (int i = 1; i <= n; ++i) {
		if (choice[i] == flag && !visit[i]) return false;
	}
	return true;
}
void calc() {
	if (check(0) && check(1)) {
		int sum1 = 0, sum2 = 0;
		for (int i = 1; i <= n; ++i) {
			if (choice[i]) sum1 += people[i];
			else sum2 += people[i];
		}
		result = min(result, abs(sum1 - sum2));
	}
}
void dfs(int index) {
	if (v2.size() >= n) return;
	if (v2.size()) calc();
	for (int i = index; i <= n; ++i) {
		if (!choice[i]) {
			choice[i] = 1;
			v2.push_back(i);
			dfs(i + 1);
			v2.pop_back();
			choice[i] = 0;
		}
	}
}
int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int num, cnt;
	cin >> n;
	for (int i = 1; i <= n; ++i)
		cin >> people[i];
	for (int i = 1; i <= n; ++i) {
		cin >> cnt;
		for(int j=0;j<cnt;++j) {
			cin >> num;
			v[i].push_back(num);
		}
	}
	dfs(1);
	cout << (result == INT_MAX ? -1 : result);
}
