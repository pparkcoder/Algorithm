// 2020 카카오 인턴십
// https://programmers.co.kr/learn/courses/30/lessons/67260
// Solving -> 아직 방문하지 않은 방은 뒤에 매달아 주기
// Tip -> queue로 구현 시 계속해서 추가되기에 TLE 발생 -> set,map 으로 insert 하여 계속 추가되지 않게 하기

#include <string>
#include <vector>
#include <queue>
#include <set>
#include <iostream>
using namespace std;
vector<int> connect[200001], before[200001], after[200001];
queue<int> q;
set<int> s;
bool visit[200001];
bool bfs(int n) {
	q.push(0);
	visit[0] = 1;
	int now, next;
	while (!q.empty()) {
		now = q.front(); q.pop();
		if (after[now].size() && s.find(after[now][0]) != s.end()) {
			if (visit[now]) {
				s.erase(after[now][0]);
				q.push(after[now][0]);
				visit[after[now][0]] = 1;
			}
		}
		for (int i = 0; i < connect[now].size(); ++i) {
			next = connect[now][i];
			if (!visit[next]) {
				if (before[next].size()) {
					if (visit[before[next][0]]) {
						q.push(next);
						visit[next] = 1;
					}
					else s.insert(next);
				}
				else {
					q.push(next);
					visit[next] = 1;
				}
			}
		}
	}
	for (int i = 0; i < n; ++i)
		if (!visit[i]) return false;
	return true;
}
bool solution(int n, vector<vector<int>> path, vector<vector<int>> order) {
	int len = path.size();
	int start, dest;
	for (int i = 0; i < len; ++i) {
		start = path[i][0];
		dest = path[i][1];
		connect[start].push_back(dest);
		connect[dest].push_back(start);
	}
	len = order.size();
	for (int i = 0; i < len; ++i) {
		start = order[i][0];
		dest = order[i][1];
		if (dest ==0 && start != 0) return false;
		before[dest].push_back(start);
		after[start].push_back(dest);
	}
	return bfs(n);
}

/*---------- TLE code ----------*/
#include <string>
#include <vector>
#include <queue>
#include <deque>
#include <iostream>
using namespace std;
vector<int> v[200001];
vector<int> v2[200001];
queue<int> q,q2;
bool visit[200001];
bool visit2[200001];
bool bfs(int n) {
	q.push(0);
	visit[0] = 1;
	int now, next, flag, check, len;
	while (1) {
		while (!q.empty()) {
			now = q.front(); q.pop();
			for (int i = 0; i < v[now].size(); ++i) {
				next = v[now][i];
				if (!visit[next]) {
					if (v2[next].size()) {
						check = v2[next][0];
						if (visit[check]) {
							q.push(next);
							visit[next] = 1;
						}
						else {
							if (!visit2[next]) {
								q2.push(next);
								visit2[next] = 1;
							}
						}
					}
					else {
						q.push(next);
						visit[next] = 1;
					}
				}
			}
		}
		if (q2.empty()) break;
		len = q2.size();
		while (len--) {
			now = q2.front(); q2.pop();
			check = v2[now][0];
			if (!visit[now]) {
				if (visit[check]) {
					q.push(now);
					visit[now] = 1;
				}
				else q2.push(now);
			}
		}
		if (q.empty()) break;
	}
	for (int i = 0; i < n; ++i)
		if (!visit[i]) return false;
	return true;
}
bool solution(int n, vector<vector<int>> path, vector<vector<int>> order) {
	int len = path.size();
	int start, dest;
	for (int i = 0; i < len; ++i) {
		start = path[i][0];
		dest = path[i][1];
		v[start].push_back(dest);
		v[dest].push_back(start);
	}
	len = order.size();
	for (int i = 0; i < len; ++i) {
		start = order[i][1];
		dest = order[i][0];
		if (start == 0 && dest != 0) return false;
		v2[start].push_back(dest);
	}
	return bfs(n);
}
/*---------- TLE code ----------*/
