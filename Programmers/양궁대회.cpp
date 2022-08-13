#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
vector<vector<int> > v;
vector<int> v2, v3;
int len;
int result = -1;
void brute(int index, vector<int> info, int a_sum, int l_sum, int cnt) {
    if (cnt == len && v2.size() == info.size()) {
        if (a_sum < l_sum) {
            int temp = l_sum - a_sum;
            if (result <= temp) {
                if (result < temp) v.clear();
                v3 = v2;
                reverse(v3.begin(), v3.end());
                v.push_back(v3);
                result = temp;
            }
        }
        return;
    }
    for (int i = index; i < info.size(); ++i) {
        int apeach = info[i];
        for (int j = 0; j <= len; ++j) {
            if (cnt + j <= len) {
                v2.push_back(j);
                if (apeach < j) brute(i + 1, info, a_sum, l_sum + (10 - i), cnt + j);
                else {
                    if (apeach) brute(i + 1, info, a_sum + (10 - i), l_sum, cnt + j);
                    else brute(i + 1, info, a_sum, l_sum, cnt + j);
                }
                v2.pop_back();
            }
        }
    }
}

vector<int> solution(int n, vector<int> info) {
    vector<int> answer;
    len = n;
    brute(0, info, 0, 0, 0);
    if (!v.size()) answer.push_back(-1);
    else {
        sort(v.begin(), v.end());
        reverse(v[v.size() - 1].begin(), v[v.size() - 1].end());
        answer = v[v.size() - 1];
    }
    return answer;
}
