// 2021 카카오 블라인드
// https://programmers.co.kr/learn/courses/30/lessons/72411
// Tip -> string sort 후 brute force 진행

#include<iostream>
#include<vector>
#include<map>
#include<algorithm>
#include<string>
using namespace std;
map<string, int> check;
bool visit[11];
void brute(int index, int max_index, int now_len, int max_len, string result, string s) {
	if (index && visit[now_len]) 
		check[result]++;
	if ((index >= max_index) || (now_len >= max_len)) return;

	string temp;
	for (int i = index; i < max_index; ++i) {
		temp = result;
		temp += s[i];
		brute(i + 1, max_index, now_len + 1, max_len + 1, temp, s);
	}
}
vector<string> solution(vector<string> orders, vector<int> course) {
	vector<pair<int, string> > v[11];
	vector<string> answer;
	int max_len = 0;
	int len, temp;
	for (int i = 0; i < course.size(); ++i) {
		max_len = max(max_len, course[i]);
		visit[course[i]] = 1;
	}
	for (int i = 0; i < orders.size(); ++i) {
		string arr[11], s = "";
		len = orders[i].length();
		for (int j = 0; j < len; ++j)
			arr[j] = orders[i][j];
		sort(arr, arr + len);
		for (int j = 0; j < len; ++j)
			s += arr[j];
		brute(0, orders[i].length(), 0, max_len, "", s);
	}
	for (auto i = check.begin(); i != check.end(); ++i) 
		v[i->first.length()].push_back(make_pair(i->second, i->first));
	for (int i = 2; i <= max_len; ++i) {
		if (visit[i] && v[i].size()) {
			sort(v[i].begin(), v[i].end());
			temp = v[i].back().first;
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
