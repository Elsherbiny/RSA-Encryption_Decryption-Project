#include <iostream>
#include <time.h>
#include <stdio.h>
#include <vector>
#include <set>
#include <map>
#include <queue>
#include <stack>
#include <string>
#include <string.h>
#include <cmath>
#include <memory.h>
#include <algorithm>
using namespace std;
typedef long long ll;
using namespace std;
 
typedef long long ll;
#define sz(v) (int)v.size()
#define all(v) v.begin(), v.end()
 
#define SUB 30
 
void clr(string &str) {
if (sz(str) <= 2) return;
int cnt = 0;
for (; cnt < sz(str) && str[cnt] == '0'; cnt++)
;
str = str.substr(cnt);
return;
}
 
int eql(string &s1, string &s2) {
clr(s1);
clr(s2);
if (sz(s1) < sz(s2)) s1.insert(0, string(abs(sz(s1) - sz(s2)), '0'));
if (sz(s1) > sz(s2)) s2.insert(0, string(abs(sz(s1) - sz(s2)), '0'));
if ((sz(s1) & 1) && s1.size() != 1) {
s1.insert(s1.begin(), '0');
s2.insert(s2.begin(), '0');
}
return sz(s1);
}
 
int cmp(string B1, string B2) {
int len = eql(B1, B2);
for (int i = 0; i < len; i++) {
if (B1[i] > B2[i]) return 2;
if (B1[i] < B2[i]) return 1;
}
return 0;
}
 
string add(string s1, string s2) {
int len = eql(s1, s2);
string sum(len, '0');
int carry = 0;
for (int i = len - 1; i >= 0; i--) {
int d1 = s1[i] - '0';
int d2 = s2[i] - '0';
sum[i] = '0' + (d1 + d2 + carry) % 10;
carry = (d1 + d2 + carry >= 10);
}
if (carry) sum.insert(sum.begin(), '1');
return sum;
}
 
string sub(string s1, string s2) {
int len = eql(s1, s2);
if (cmp(s1, s2) == 1) s1.swap(s2);
for (int i = 0; i < len; i++) {
s2[i] = (('9' + (i == len - 1)) - s2[i] + '0');
}
string ret = add(s1, s2);
if ((int)ret.size() > len) return ret.substr(1);
return ret;
}
 
string mul(string X, string Y) {
string ret = "";
ret += '0' + ((X[0] - '0') * (Y[0] - '0')) % 10;
if (((X[0] - '0') * (Y[0] - '0')) >= 10) ret.insert(ret.begin(), '0' + ((X[0] - '0') * (Y[0] - '0')) / 10);
return ret;
}
 
string solve(string X, string Y) {
int len = eql(X, Y);
if (!len) return "";
if (len == 1) return mul(X, Y);
int mid = len / 2;
string xl(X.substr(0, mid));
string xr(X.substr(mid));
 
string yl(Y.substr(0, mid));
string yr(Y.substr(mid));
 
/*
P1 = xH * yH
P2 = xL * yL
P3 = (xH + xL)(yH + yL) – a – d
xy = P1*r^n + P3*r^(n/2) + P2
*/
 
string P1(solve(xl, yl)); // clr(P1);
string P2(solve(xr, yr)); // clr(P2);
string P3(sub(solve(add(xl, xr), add(yl, yr)), add(P1, P2))); // clr(P3);
string solveFirst(P1 + string(len, '0')); // clr(solveFirst);
string solveSecond(P3 + string(mid, '0')); // clr(solveSecond);
string ans = add(solveFirst, add(solveSecond, P2));
clr(ans);
return ans;
 
}
 
string o = "1";
 
pair<string, string> div(string a, string b) {
if (cmp(a, b) == 1) return make_pair("0", a);
pair<string, string> ret = div(a, add(b, b));
ret.first = add(ret.first, ret.first);
clr(ret.first);
clr(ret.second);
if (cmp(ret.second, b) == 1)
return ret;
 
else return make_pair(add(ret.first, o = "1"), sub(ret.second, b));
}
 
string EncryptAndDecrypt(string x, string p, string m) {
if (cmp(p, o = "0") == 0) return "1";
string y = EncryptAndDecrypt(x, div(p, "2").first, m);
clr(y);
y = div(y, m).second;
y = div(solve(y, y), m).second;
if (cmp(div(p, "2").second, o = "1") == 0) y = div(solve(y, x), m).second;
clr(y);
return y;
}
 
int main() {
//freopen("src.txt", "r", stdin);
//freopen("outABC.txt", "w", stdout);
int tc;
cin >> tc;
clock_t t = clock();
while (tc--) {
int is = 1;
string n, ed, mem;
cin >> n >> ed >> mem >> is;
 
cout << EncryptAndDecrypt(mem, ed, n) << endl;
cout << "TIME " << (double)(clock() - t)/CLOCKS_PER_SEC << endl;
}
}
