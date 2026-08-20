// Rabin-Karp: String pattern matching using rolling hash.
// Time: O(n + m) average | Space: O(1)

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
using pii = pair<int, int>;
using vvi = vector<vector<int>>;
using ll = long long;
using pll = pair<long long, long long>;
using vll = vector<long long>;

// ---------- Useful GCC Builtins ----------
// __builtin_popcount(x)      -> set bits in int
// __builtin_popcountll(x)    -> set bits in long long
// __builtin_clz(x)           -> leading zeros in int
// __builtin_clzll(x)         -> leading zeros in long long
// __builtin_ctz(x)           -> trailing zeros in int
// __builtin_ctzll(x)         -> trailing zeros in long long
// __builtin_parity(x)        -> 1 if set bits are odd

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

template<class T, class V>
void _print(pair<T,V> p){
    cerr << "{";
    _print(p.first);
    cerr << ", ";
    _print(p.second);
    cerr << "}";
}

template<class T>
void _print(vector<T> v){
    cerr << "[ ";
    for(auto &i : v){
        _print(i);
        cerr << " ";
    }
    cerr << "]";
}

template<class T>
void _print(set<T> s){
    cerr << "{ ";
    for(auto &i : s){
        _print(i);
        cerr << " ";
    }
    cerr << "}";
}

template<class T>
void _print(multiset<T> s){
    cerr << "{ ";
    for(auto &i : s){
        _print(i);
        cerr << " ";
    }
    cerr << "}";
}

template<class T>
void _print(unordered_set<T> s){
    cerr << "{ ";
    for(auto &i : s){
        _print(i);
        cerr << " ";
    }
    cerr << "}";
}

template<class K, class V>
void _print(map<K,V> m){
    cerr << "{ ";
    for(auto &i : m){
        _print(i);
        cerr << " ";
    }
    cerr << "}";
}

template<class K, class V>
void _print(unordered_map<K,V> m){
    cerr << "{ ";
    for(auto &i : m){
        _print(i);
        cerr << " ";
    }
    cerr << "}";
}

template<class T>
void _print(vector<vector<T>> vv){
    cerr << "[\n";
    for(auto &row : vv){
        cerr << "  ";
        _print(row);
        cerr << '\n';
    }
    cerr << "]";
}

int gcdll(int a, int b){
    return b ? gcdll(b, a % b) : a;
}

int lcmll(int a, int b){
    return a / gcdll(a, b) * b;
}

void yes(){ cout << "YES\n"; }
void no(){ cout << "NO\n"; }

// ---------- Rabin-Karp ----------

const int BASE = 31;
const int MOD = 1e9 + 7;

int value(char c){
    return c - 'a' + 1;
}

vector<int> rabinKarp(string text, string pattern){

    int n = text.size();
    int m = pattern.size();

    vector<int> positions;

    if(m > n)
        return positions;

    // base^(m-1)
    int power = 1;

    for(int i = 1; i < m; i++){
        power = (power * BASE) % MOD;
    }

    // Hash of pattern
    int patternHash = 0;

    for(int i = 0; i < m; i++){
        patternHash =
            (patternHash * BASE + value(pattern[i])) % MOD;
    }

    // Hash of first window
    int windowHash = 0;

    for(int i = 0; i < m; i++){
        windowHash =
            (windowHash * BASE + value(text[i])) % MOD;
    }

    // Sliding window
    for(int i = 0; i <= n - m; i++){

        // Hash match -> verify to avoid collision
        if(windowHash == patternHash){

            bool match = true;

            for(int j = 0; j < m; j++){
                if(text[i + j] != pattern[j]){
                    match = false;
                    break;
                }
            }

            if(match)
                positions.push_back(i);
        }

        // Roll the window
        if(i < n - m){

            // Remove leftmost character
            windowHash =
                (windowHash - value(text[i]) * power) % MOD;

            if(windowHash < 0)
                windowHash += MOD;

            // Shift and add new character
            windowHash =
                (windowHash * BASE + value(text[i + m])) % MOD;
        }
    }

    return positions;
}

signed main(){

    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string text = "ababcabcab";
    string pattern = "abc";

    vector<int> ans = rabinKarp(text, pattern); // it gives the at which indexs this pattern is matechd for e.g. 2,5

    for(auto index : ans)
        cout << index << " ";

    cout << endl;

    return 0;
}
