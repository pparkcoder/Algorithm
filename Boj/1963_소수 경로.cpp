// https://www.acmicpc.net/problem/1963

#include<iostream>
#include<queue>
#include<string>
#include<map>
#define mp make_pair
using namespace std;
queue<pair<string, int> > q;
map<string, int> visit;
bool prime[10000];
string target;
void make_prime() {
	for (int i = 2; i < 10000; ++i) {
		if (prime[i]) continue;
		for (int j = i + i; j < 10000; j += i)
			prime[j] = 1;
	}
}
int bfs() {
	while (!q.empty()) {
		string s = q.front().first;
		int cnt = q.front().second; q.pop();
		if (s == target) return cnt;
		for (int i = 3; i >= 0; --i) {
			int st = (i == 0 ? 1 : 0);
			string next = s;
			for (; st < 10; ++st) {
				next[i] = char(st +'0');
				if (!visit[next] && !prime[stoi(next)]) {
					q.push(mp(next, cnt + 1));
					visit[next] = 1;
				}
			}
		}
	}
}
int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	string s;
	int t;
	cin >> t;
	make_prime();
	while (t--) {
		cin >> s >> target;
		q.push(mp(s, 0));
		visit[s] = 1;
		cout << bfs() << "\n";
		while (!q.empty()) q.pop();
		visit.clear();
	}
}
