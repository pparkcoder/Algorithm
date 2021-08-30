// 2021 카카오 블라인드
// https://programmers.co.kr/learn/courses/30/lessons/72411
// Tip -> string 원소 하나하나마다 sort 필요

#include<iostream>
#include<vector>
#include<map>
#include<algorithm>
#include<string>
using namespace std;
map<string, int> check;
bool visit[11];
void brute(int index, int max_index, int now_len, int max_len, string result, string s) {
	if (index && visit[now_len]) {
		sort(result.begin(),result.end());
		check[result]++;
	}
	if ((index >= max_index) || (now_len >= max_len)) return;

	for (int i = index; i < max_index; ++i) {
		string temp = result;
		temp += s[i];
		brute(i + 1, max_index, now_len + 1, max_len + 1, temp, s);
	}
}
vector<string> solution(vector<string> orders, vector<int> course) {
	vector<pair<int, string> > v[11];
	vector<string> answer;
	int max_len = 0;
	for (int i = 0; i < course.size(); ++i) {
		max_len = max(max_len, course[i]);
		visit[course[i]] = 1;
	}
	for (int i = 0; i < orders.size(); ++i) 
		brute(0, orders[i].length(), 0, max_len, "", orders[i]);
	for (auto i = check.begin(); i != check.end(); ++i) 
		v[i->first.length()].push_back(make_pair(i->second, i->first));
	for (int i = 2; i <= max_len; ++i) {
		if (visit[i] && v[i].size()) {
			sort(v[i].begin(), v[i].end());
			int temp = v[i].back().first;
			if (temp > 1) {
				answer.push_back(v[i].back().second);
				for (int j = v[i].size() - 2; j >= 0; --j) {
					if (temp == v[i][j].first) answer.push_back(v[i][j].second);
					else break;
				}
			}
		}
	}
	sort(answer.begin(), answer.end());
	return answer;
}
