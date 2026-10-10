/*
==================== KRUSKAL ALGORITHM (MST) ====================

Time Complexity:
- O(E log E)   -> for sorting edges

Space Complexity:
- O(N)         -> for DSU (parent + size arrays)

Important Points:
- Used to find Minimum Spanning Tree (MST)
- Works for undirected weighted graphs
- Greedy algorithm: always pick smallest edge
- Use DSU (Disjoint Set) to avoid cycles
- Edge format: {weight, u, v}
- If find(u) != find(v) → include edge

Notes (for CP / GitHub saving):
- Always sort edges before processing
- DSU must have path compression + union by size/rank
- Stores MST cost + edges
- Does NOT work for directed graphs
- Graph should be connected for full MST (else gives forest)

===============================================================
*/
#include <bits/stdc++.h>
using namespace std;

/* TYPES  */
#define ll long long
#define pii pair<int, int>
#define pll pair<long long, long long>
#define vi vector<int>
#define vll vector<long long>
#define mii map<int, int>
#define si set<int>
#define sc set<char>
#define popcnt __builtin_popcount

/* FUNCTIONS */
#define f(i,s,e) for(long long int i=s;i<e;i++)
#define cf(i,s,e) for(long long int i=s;i<=e;i++)
#define rf(i,e,s) for(long long int i=e-1;i>=s;i--)
#define pb push_back
#define ppb pop_back
#define eb emplace_back
#define ff first
#define ss second



#define debug(x) cerr << #x << " = "; _print(x); cerr << endl;
void _print(int t) { cerr << t; }
void _print(long long t) { cerr << t; }
void _print(string t) { cerr << t; }
void _print(char t) { cerr << t; }
void _print(double t) { cerr << t; }
template <class T, class V> void _print(pair <T, V> p) { cerr << "{"; _print(p.first); cerr << ","; _print(p.second); cerr << "}"; }
template <class T> void _print(vector <T> v) { cerr << "[ "; for (T i : v) { _print(i); cerr << " "; } cerr << "]"; }
template <class T> void _print(set <T> v) { cerr << "[ "; for (T i : v) { _print(i); cerr << " "; } cerr << "]"; }
template <class T> void _print(multiset <T> v) { cerr << "[ "; for (T i : v) { _print(i); cerr << " "; } cerr << "]"; }
template <class T, class V> void _print(map <T, V> v) { cerr << "[ "; for (auto i : v) { _print(i); cerr << " "; } cerr << "]"; }
#define sz(x) (int)(x).size()
#define maxpq priority_queue<int>
#define minpq priority_queue<int, vector<int>, greater<int>>
#define tp tuple<int,int,int>
#define minpq_tuple priority_queue<tp, vector<tp>, greater<tp>>
#define maxpq_tuple priority_queue<tp>
#define all(x) (x).begin(), (x).end()

/* UTILS */
#define MOD 1000000007
#define PI 3.1415926535897932384626433832795
#define INF 1e18
#define nline "\n"

ll gcd(ll a,ll b) { if (b==0) return a; return gcd(b, a%b); }
ll lcm(ll a,ll b) { return a/gcd(a,b)*b; }
ll expo(ll a, ll b, ll mod) {ll res = 1; while (b > 0) {if (b & 1)res = (res * a) % mod; a = (a * a) % mod; b = b >> 1;} return res;}
void extendgcd(ll a, ll b, ll*v) {if (b == 0) {v[0] = 1; v[1] = 0; v[2] = a; return ;} extendgcd(b, a % b, v); ll x = v[1]; v[1] = v[0] - v[1] * (a / b); v[0] = x; return;} //pass an arry of size1 3
ll mminv(ll a, ll b) { ll arr[3]; extendgcd(a, b, arr); return (arr[0] % b + b) % b; } // for non-prime mod
ll mminvprime(ll a, ll b) {return expo(a, b - 2, b);}
ll mod_add(ll a, ll b, ll m) { a = a % m; b = b % m; return (((a + b) % m) + m) % m; }
ll mod_mul(ll a, ll b, ll m) { a = a % m; b = b % m; return (((a * b) % m) + m) % m; }
ll mod_sub(ll a, ll b, ll m) { a = a % m; b = b % m; return (((a - b) % m) + m) % m; }
ll mod_div(ll a, ll b, ll m) { a = a % m; b = b % m; return (mod_mul(a, mminvprime(b, m), m) + m) % m; } // only for prime m
bool revsort(ll a, ll b) {return a > b;}
ll combination(ll n, ll r, ll m, vector<ll> &fact, vector<ll> &ifact) {  if (r > n) return 0;   return (((fact[n] * ifact[r]) % m) * ifact[n - r]) % m;}
vector<ll> sieve(int n){vector<bool> isPrime(n+1,true);vector<ll> primes;isPrime[0]=isPrime[1]=false;for(ll i=2;i*i<=n;i++){if(isPrime[i]){for(ll j=i*i;j<=n;j+=i)isPrime[j]=false;}}for(ll i=2;i<=n;i++)if(isPrime[i])primes.pb(i);return primes;}
ll phin(ll n) {ll number = n; if (n % 2 == 0) {number /= 2; while (n % 2 == 0) n /= 2;} for (ll i = 3; i * i <= n; i += 2) {if (n % i == 0) {while (n % i == 0)n /= i; number = (number / i * (i - 1));}} if (n > 1)number = (number / n * (n - 1)) ; return number;} //O(sqrt(N)) -> for the coprime

void yes() { cout<<"YES\n"; }
void no() { cout<<"NO\n"; }

typedef long int int32;
typedef unsigned long int uint32;
typedef long long int int64;
typedef unsigned long long int uint64;

// ================== WRITE YOUR CODE BELOW ==================



struct DSU {
    vector<int> parent, size;
    DSU(int n) {
        parent.resize(n+1);
        size.resize(n+1,1);
        for(int i=0;i<=n;i++) parent[i]=i;
    }
    int find(int v){
        if(parent[v]==v) return v;
        return parent[v]=find(parent[v]);
    }
    void unite(int a,int b){
        a=find(a); b=find(b);
        if(a!=b){
            if(size[a]<size[b]) swap(a,b);
            parent[b]=a;
            size[a]+=size[b];
        }
    }
};

void Kruskal(vector<tuple<int,int,int>> &edges,int n) { // w u v
    sort(all(edges));
    DSU dsu(n);

    int mst_cost = 0;
    vector<pair<int,int>> mst_edges;

    for(auto [w,u,v] : edges){
        if(dsu.find(u) != dsu.find(v)){
            dsu.unite(u,v);
            mst_cost += w;
            mst_edges.push_back({u,v});
        }
    }

    cout << "MST cost: " << mst_cost << nline;
    for(auto [u,v] : mst_edges){
        cout << u << " " << v << nline;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;
    while (t--) {
        int n, m;
        cin >> n >> m;

        vector<tuple<int,int,int>> edges;

        for(int i = 0; i < m; i++){
            int u, v, w;
            cin >> u >> v >> w;
            edges.push_back({w,u,v});
        }

        Kruskal(edges, n);
    }
    return 0;
}
