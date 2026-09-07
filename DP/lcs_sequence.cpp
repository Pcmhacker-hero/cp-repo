#include <bits/stdc++.h>
using namespace std;

string getLCS(string s1, string s2) {
    int n = s1.size();
    int m = s2.size();

    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));

    // Build LCS DP table
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            if(s1[i - 1] == s2[j - 1]) {
                dp[i][j] = 1 + dp[i - 1][j - 1];
            }
            else {
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }

    // Reconstruct LCS string
    string lcs = "";

    int i = n;
    int j = m;

    while(i > 0 && j > 0) {
        if(s1[i - 1] == s2[j - 1]) {
            lcs += s1[i - 1];
            i--;
            j--;
        }
        else if(dp[i - 1][j] >= dp[i][j - 1]) {
            i--;
        }
        else {
            j--;
        }
    }

    reverse(lcs.begin(), lcs.end());

    return lcs;
}

void solve() {
    string s1 = "apple";
    string s2 = "waffle";

    string lcs = getLCS(s1, s2);

    cout << "LCS Length: " << lcs.size() << endl;
    cout << "LCS String: " << lcs << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}
