// https://www.acmicpc.net/problem/20291
// vector sort VS map

#include<iostream>
#include<vector>
#include<algorithm>
#include<map>
using namespace std;
map<string,int> visit;
vector<string> v;
string target,name;
int n,idx;
int main(){
    ios::sync_with_stdio(0);cin.tie(0);
    cin >> n;
    for(int i=0;i<n;++i){
        cin >> target;
        idx = target.find('.');
        name = target.substr(target.length() - (target.length() - idx) + 1);
        v.push_back(name);
        ++visit[name];
    }
    std::sort(v.begin(), v.end());
    v.erase(unique(v.begin(),v.end()),v.end());
    for(int i=0;i<v.size();++i){
        cout << v[i] << " " << visit[v[i]] << "\n";
    }
}

#include<iostream>
#include<algorithm>
#include<map>
using namespace std;
map<string,int> visit;
string target,name;
int n;
int main(){
    ios::sync_with_stdio(0);cin.tie(0);
    cin >> n;
    for(int i=0;i<n;++i){
        cin >> target;
        name = target.substr(target.find('.') + 1,target.length());
        ++visit[name];
    }
    for(auto iter : visit)
        cout << iter.first << " " << iter.second << "\n";
}
