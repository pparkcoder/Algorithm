// https://www.acmicpc.net/problem/2852

#include<iostream>
#include<vector>
#include<string>
#define mp make_pair
using namespace std;
vector<pair<int, string> > v;
int sum_a = 0, sum_b = 0;
int n, team_num;
string goal_time;
void make_string() {
	string h, m;
	int sum;
	for (int i = 0; i < 2; ++i) {
		if (!i) sum = sum_a;
		else sum = sum_b;
		h = to_string(sum / 60);
		m = to_string(sum % 60);
		if (h.length() == 1) h = "0" + h;
		if (m.length() == 1) m = "0" + m;
		cout << h << ":" << m << "\n";
	}
}
int calc(string a, string b) {
	int a_h = stoi(a.substr(0, 2));
	int a_m = stoi(a.substr(3));
	int b_h = stoi(b.substr(0, 2));
	int b_m = stoi(b.substr(3));
	return (b_h * 60 + b_m) - (a_h * 60 + a_m);
}
int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int score_a = 0, score_b = 0;
	string  time_a = "", time_b = "";
	cin >> n;
	for (int i = 0; i < n; ++i) {
		cin >> team_num >> goal_time;
		v.push_back(mp(team_num, goal_time));
	}
	for (int i = 0; i < n; ++i) {
		team_num = v[i].first;
		goal_time = v[i].second;
		if (team_num == 1) ++score_a;
		else ++score_b;
		if (score_a > score_b) {
			if (time_a == "") time_a = goal_time;
		}
		else if (score_a < score_b) {
			if (time_b == "") time_b = goal_time;
		}
		else {
			if (time_a != "") {
				sum_a += calc(time_a, goal_time);
				time_a = "";
			}
			else if (time_b != "") {
				sum_b += calc(time_b, goal_time);
				time_b = "";
			}
		}
	}
	if (time_a != "") sum_a += calc(time_a, "48:00");
	else if (time_b != "") sum_b += calc(time_b, "48:00");
	make_string();
}
