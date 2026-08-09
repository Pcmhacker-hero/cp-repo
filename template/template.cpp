#include "bits/stdc++.h"
using namespace std;

#define int long long
#define endl '\n'
#define all(x) (x).begin(), (x).end()
#define pb push_back
#define eb emplace_back
#define sz(x) (int)(x).size()
#define ff first
#define ss second

using vi = vector<int>;
using pii = pair<int,int>;
using vvi = vector<vector<int>>;
using ll = long long;
using pll = pair<long long,long long>;
using vll = vector<long long>;

// ---------- Debug ----------
#ifndef ONLINE_JUDGE
#define debug(x) cerr << #x << " = "; _print(x); cerr << endl;
#else
#define debug(x)
#endif

void _print(int32_t x){ cerr << x; }
void _print(long long x){ cerr << x; }
void _print(char x){ cerr << x; }
void _print(string x){ cerr << x; }
void _print(bool x){ cerr << (x ? "true" : "false"); }
void _print(double x){ cerr << x; }

template<class T,class V> void _print(pair<T,V> p){ cerr << "{"; _print(p.first); cerr << ", "; _print(p.second); cerr << "}"; }
template<class T> void _print(vector<T> v){ cerr << "[ "; for(auto &i:v){ _print(i); cerr << " "; } cerr << "]"; }
template<class T> void _print(set<T> s){ cerr << "{ "; for(auto &i:s){ _print(i); cerr << " "; } cerr << "}"; }
template<class T> void _print(multiset<T> s){ cerr << "{ "; for(auto &i:s){ _print(i); cerr << " "; } cerr << "}"; }
template<class T> void _print(unordered_set<T> s){ cerr << "{ "; for(auto &i:s){ _print(i); cerr << " "; } cerr << "}"; }
template<class K,class V> void _print(map<K,V> m){ cerr << "{ "; for(auto &i:m){ _print(i); cerr << " "; } cerr << "}"; }
template<class K,class V> void _print(unordered_map<K,V> m){ cerr << "{ "; for(auto &i:m){ _print(i); cerr << " "; } cerr << "}"; }
template<class T> void _print(vector<vector<T>> vv){ cerr << "[\n"; for(auto &row:vv){ cerr << "  "; _print(row); cerr << '\n'; } cerr << "]"; }
int gcdll(int a, int b){ return b ? gcdll(b, a % b) : a; }
int lcmll(int a, int b){ return a / gcdll(a,b) * b; }

void yes(){ cout << "YES\n"; }
void no(){ cout << "NO\n"; }
