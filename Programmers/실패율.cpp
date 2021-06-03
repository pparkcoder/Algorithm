// 2019 카카오 블라인드
// https://programmers.co.kr/learn/courses/30/lessons/42889

#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
int counting[501];
bool cmp(const pair<double, int> a, const pair<double, int> b) // a : 실패율, b : stage num
{
	if (a.first == b.first) { // 실패율이 같다면 stage num이 작은 순으로 정렬
		if (a.second < b.second) return true;
		else return false;
	}
	else if (a.first > b.first) return true; // 실패율이 큰 순으로 정렬
	else return false;
}
vector<int> solution(int N, vector<int> stages) {
	vector<int> answer;
	vector<pair<double, int> > temp;	
	int parent = stages.size();
	double num;
	for (int i = 0; i < parent; ++i) {
		if (stages[i] > N) continue;
		counting[stages[i]]++;
	}
	for (int i = 1; i <= N; ++i) {
		if (!parent) temp.push_back(make_pair(0, i));
		else {
			num = double(counting[i]) / parent;
			parent -= counting[i];
			temp.push_back(make_pair(num, i));
		}
	}
	sort(temp.begin(), temp.end(), cmp);
	for (int i = 0; i < temp.size(); ++i)
		answer.push_back(temp[i].second);
	return answer;
}
