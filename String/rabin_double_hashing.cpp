#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define vi vector<int>

const ll BASE1 = 31;
const ll MOD1 = 1000000007;

const ll BASE2 = 37;
const ll MOD2 = 1000000009;

int value(char ch) {
    return ch - 'a' + 1;
}

vi rabinKarp(string text, string pattern) {

    int n = text.size();
    int m = pattern.size();

    vi positions;

    if (m > n || m == 0)
        return positions;

    // BASE^(m-1)
    ll power1 = 1;
    ll power2 = 1;

    for (int i = 1; i < m; i++) {
        power1 = (power1 * BASE1) % MOD1;
        power2 = (power2 * BASE2) % MOD2;
    }

    // Hash of first window
    ll windowHash1 = 0;
    ll windowHash2 = 0;

    for (int i = 0; i < m; i++) {

        ll x = value(text[i]);

        windowHash1 =
            (windowHash1 * BASE1 + x) % MOD1;

        windowHash2 =
            (windowHash2 * BASE2 + x) % MOD2;
    }

    // Hash of pattern
    ll patternHash1 = 0;
    ll patternHash2 = 0;

    for (int i = 0; i < m; i++) {

        ll x = value(pattern[i]);

        patternHash1 =
            (patternHash1 * BASE1 + x) % MOD1;

        patternHash2 =
            (patternHash2 * BASE2 + x) % MOD2;
    }

    // Sliding window
    for (int i = 0; i <= n - m; i++) {

        // Both hashes must match
        if (windowHash1 == patternHash1 &&
            windowHash2 == patternHash2) {

            // Verify to completely avoid collision
            bool match = true;

            for (int j = 0; j < m; j++) {

                if (text[i + j] != pattern[j]) {
                    match = false;
                    break;
                }
            }

            if (match)
                positions.push_back(i);
        }

        // Rolling hash
        if (i < n - m) {

            ll oldValue = value(text[i]);
            ll newValue = value(text[i + m]);

            // Remove old character
            windowHash1 =
                (windowHash1 - oldValue * power1) % MOD1;

            windowHash2 =
                (windowHash2 - oldValue * power2) % MOD2;

            if (windowHash1 < 0)
                windowHash1 += MOD1;

            if (windowHash2 < 0)
                windowHash2 += MOD2;

            // Shift and add new character
            windowHash1 =
                (windowHash1 * BASE1 + newValue) % MOD1;

            windowHash2 =
                (windowHash2 * BASE2 + newValue) % MOD2;
        }
    }

    return positions;
}

int main() {

    string text = "ababcabcab";
    string pattern = "abc";

    vi ans = rabinKarp(text, pattern);

    for (int index : ans) {
        cout << index << " ";
    }

    return 0;
}
