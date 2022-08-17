#include <string>
#include <algorithm>
#include <cmath>

using namespace std;

string make_k(int n, int k) {
    int a = n;
    int b = 0;
    string s = "";
    while (a) {
        b = a % k;
        a /= k;
        s += to_string(b);
    }
    reverse(s.begin(), s.end());
    return s;
}
bool make_prime(long long num) {
    if(num < 2) return false;

    for(int i=2; i<=sqrt(num); ++i) {
        if(num % i == 0) return false;
    }
    return true;

}

int solution(int n, int k) {
    int index1 = 0, index2 = 0, result = 0;
    long long num;
    string s = make_k(n, k);
    while (index1 < s.length()) {
        index2 = s.find('0', index1);
        if (index1 != index2) {
            if (index2 != -1) num = stoll(s.substr(index1, index2 - index1));
            else num = stoll(s.substr(index1));
            if (make_prime(num)) ++result;
        }
        if (index2 == -1) break;
        index1 = (index2 + 1);
    }
    return result;
}
