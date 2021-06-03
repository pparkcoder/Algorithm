// 2019 카카오 블라인드
// https://programmers.co.kr/learn/courses/30/lessons/42889
//
// vector sort 시 사용자 정의 함수 구현 법
// ex) a가 큰 순서대로, a가 같다면 b가 작은순으로, b가 같다면 c가 큰 순으로 정렬
//typedef struct {
//	int a, b, c;
//}info;
// 
//bool cmp(info first, info second) { 첫번째 인자, 두번째 인자
//	if (first.a > second.a) return true; 
//	else if (first.a == second.a) {
//		if (first.b < second.b) return true;
//		else if (first.b == second.b) {
//			if (first.c > second.c) return true;
//			else return false;
//		}
//		else return false;
//	}
//	else return false;
//}
// 만족하지 않는 조건이 없도록 구현이 중요 + 부등호의 방향에 따라 정렬

#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
int counting[501];
bool cmp(const pair<double, int> a, const pair<double, int> b) // first value : 실패율, second value : stage num
{
	if (a.first == b.first) { // 실패율이 같다면 
		if (a.second < b.second) return true; // stage num이 작은 순으로 정렬 - a가 첫번째 인자, b가 두번째 인자 -> a < b : a가 앞 b가 뒤
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
