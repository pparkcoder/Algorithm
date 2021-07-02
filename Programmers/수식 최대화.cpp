// 2020 카카오 인턴십
// https://programmers.co.kr/learn/courses/30/lessons/67257
// 자료형 주의

#include<iostream>
#include<vector>
#include<string>
#include<climits>
using namespace std;
vector<string>v, v3;
vector<string>v2;
string symbol[3] = { "*","+","-" };
bool visit[3], visit2[3];
int symbol_cnt = 0;
long long result = -LLONG_MAX;
void calc() {
	v3 = v;
	int len;
	string temp;
	for (int i = 0; i < symbol_cnt; ++i) {
		len = v3.size();
		for (int j = 0; j < len; ++j) {
			if (j % 2 == 0)v3.push_back(v3[j]);
			else {
				if (v3[j] == v2[i]) {
					temp = v3.back();
					v3.pop_back();
					if (v2[i] == "+") v3.push_back(to_string(stoll(temp) + stoll(v3[j + 1])));
					else if (v2[i] == "*") v3.push_back(to_string(stoll(temp) * stoll(v3[j + 1])));
					else v3.push_back(to_string(stoll(temp) - stoll(v3[j + 1])));
					++j;
				}
				else v3.push_back(v3[j]);
			}
		}
		v3.erase(v3.begin(), v3.begin() + len);
	}
	long long ans = abs(stoll(v3.front()));
	if(result < ans) 
		result = ans;
	v3.clear();
}
void brute(int cnt) {
	if (cnt == symbol_cnt) {
		calc();
		return;
	}
	for (int i = 0; i < 3; ++i) {
		if (visit[i] && !visit2[i]) {
			visit2[i] = 1;
			v2.push_back(symbol[i]);
			brute(cnt + 1);
			v2.pop_back();
			visit2[i] = 0;
		}
	}
}
int solution(string ex) {
	string s = "";
	for (int i = 0; i < ex.length(); ++i) {
		if (!('0' <= ex[i] && ex[i] <= '9')) {
			v.push_back(s);
			if (ex[i] == '-') v.push_back("-");
			else if (ex[i] == '+') v.push_back("+");
			else if (ex[i] == '*') v.push_back("*");
			s = "";
			for (int j = 0; j < 3; ++j) {
				if (visit[j]) continue;
				if (symbol[j] == ex[i] + s) visit[j] = 1, ++symbol_cnt;
			}
		}
		else s += ex[i];
	}
	v.push_back(s);
	brute(0);
	return result;
}
