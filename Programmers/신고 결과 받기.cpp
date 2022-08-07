#include <string>
#include <vector>
#include <map>
#include <iostream>

using namespace std;
map<string, int> res, cnt;
map<pair<string,string> ,bool> check;

vector<int> solution(vector<string> id_list, vector<string> report, int k) {
    vector<int> answer;
    string s, a, b;
    int index;
    for (int i = 0; i < report.size(); ++i) {
        s = report[i];
        index = s.find(' ');
        a = s.substr(0, index);
        b = s.substr(index + 1, s.length());
        if(!check[make_pair(a,b)]){
            check[make_pair(a,b)] = 1;
            ++cnt[b];
        }
    }
    check.clear();
    for (int i = 0; i < report.size(); ++i) {
        s = report[i];
        index = s.find(' ');
        a = s.substr(0, index);
        b = s.substr(index + 1, s.length());
        if(!check[make_pair(a,b)]) {
            check[make_pair(a, b)] = 1;
            if (cnt[b] >= k) ++res[a];
        }
    }
    for (int i = 0; i < id_list.size(); ++i) {
        answer.push_back(res[id_list[i]]);
    }
    return answer;
}
