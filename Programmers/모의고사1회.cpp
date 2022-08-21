// 1번
#include <string.h>
#include <vector>
#include <iostream>
using namespace std;
int visit[10],visit2[10];
string solution(string X, string Y) {
    string answer = "";
    for(int i=0;i<X.length();++i){
        if('0' <= X[i] && X[i] <= '9') {
            ++visit[X[i] - '0'];
        }
    }
    for(int i=0;i<Y.length();++i) {
        if ('0' <= Y[i] && Y[i] <= '9') {
            ++visit2[Y[i] - '0'];
        }
    }
    for(int i=9;i>=0;--i){
        if(visit[i] && visit2[i]){
            --visit[i];
            --visit2[i];
            answer += (to_string(i));
            ++i;
        }
    }
    if(answer == "") return "-1";
    else if(answer[0] == '0') return "0";
    else return answer;
}

// 2번
#include <string>
#include <vector>
#include<map>
using namespace std;
map<string,int> check,temp;
int solution(vector<string> want, vector<int> number, vector<string> discount) {
    int result = 0, stop = 1;
    for(int i=0;i<want.size();++i) check[want[i]] = number[i];
    for(int i=0;i<10;++i) ++temp[discount[i]];
    for(int i=10;i<=discount.size();++i){
        int flag = 0;
        if(!stop) ++temp[discount[i - 1]];
        for(int j=0;j<want.size();++j){
            if(check[want[j]] != temp[want[j]]){
                flag = 1;
                break;
            }
        }
        if(!flag) ++result;
        stop = 0;
        --temp[discount[i - 10]];
    }
    return result;
}

// 3번
#include <string>
#include <vector>
#include <queue>
#include<stack>
#include<iostream>
using namespace std;
stack<int> s;
queue<int> q;
int solution(vector<int> order) {
    int result = 0;
    for(int i=1;i<=order.size();++i) q.push(i);
    for(int i=0;i<order.size();++i){
        if(!q.empty()){
            if(q.front() == order[i]){
                q.pop();
                ++result;
            }
            else{
                if(s.size() && s.top() == order[i]){
                    s.pop();
                    ++result;
                }
                else{
                    int temp = q.front();
                    q.pop();
                    s.push(temp);
                    --i;
                }
            }
        }
        else{
            if(s.top() == order[i]){
                s.pop();
                ++result;
            }
            else break;
        }
    }
    return result;
}

// 4번
#include <string>
#include <vector>
#include <cmath>

using namespace std;
vector<int> v, v2;
string s1, s2;
int n, m, result;

string make(int flag, string temp) {
    string ans = "";
    int map[11][11];
    int index = 0;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            map[i][j] = temp[index++] - '0';
        }
    }
    if (!flag) {
        for (int i = 0; i < v.size(); ++i) {
            index = v[i];
            for (int j = 1; j <= m; ++j)
                map[index][j] = abs(1 - map[index][j]);
        }
    } else {
        for (int i = 0; i < v2.size(); ++i) {
            index = v2[i];
            for (int j = 1; j <= n; ++j)
                map[j][index] = abs(1 - map[j][index]);
        }
    }
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
            ans += to_string(map[i][j]);
    return ans;
}

void brute_col(int index, int cnt, string temp2, int row_cnt) {
    if (v2.size() == cnt) {
        string temp3 = make(1, temp2);

        if (temp3 == s2) result = min(result, cnt + row_cnt);
        return;
    }
    for (int i = index; i <= m; ++i) {
        v2.push_back(i);
        brute_col(i + 1, cnt, temp2, row_cnt);
        v2.pop_back();
    }
}

void brute_row(int index, int cnt, string temp) {
    if (v.size() == cnt) {
        string temp2 = make(0, temp);
        for (int i = 0; i <= m; ++i) {
            brute_col(1, i, temp2, cnt);
        }
        return;
    }
    for (int i = index; i <= n; ++i) {
        v.push_back(i);
        brute_row(i + 1, cnt, temp);
        v.pop_back();
    }
}

int solution(vector<vector<int>> beginning, vector<vector<int>> target) {
    n = beginning.size();
    m = beginning[0].size();
    s1 = "", s2 = "";
    result = 987654321;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            s1 += to_string(beginning[i][j]);
            s2 += to_string(target[i][j]);
        }
    }
    if (s1 == s2) return 0;
    else {
        for (int i = 0; i <= n; ++i) {
            brute_row(1, i, s1);
        }
    }
    return (result == 987654321 ? -1 : result);
}
