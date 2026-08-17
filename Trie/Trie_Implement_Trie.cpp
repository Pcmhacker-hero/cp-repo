#include <bits/stdc++.h>
using namespace std;

/*
===========================================================
Problem: Implement Trie (Prefix Tree)
Platform: LeetCode
Problem: 208

Approach:
- Each Trie node contains 26 pointers, one for each lowercase
  English letter.
- `flag` tells whether a complete word ends at this node.
- During insertion, create a new node if the required character
  path does not exist.
- During search, traverse the Trie and check `flag` at the end.
- For startsWith, only check whether the complete prefix path exists.

Time Complexity:
- insert(word)     : O(L)
- search(word)     : O(L)
- startsWith(prefix): O(L)

Space Complexity:
- O(N * L) in the worst case
  where N = number of inserted words
  and L = average word length.

===========================================================
*/

struct Node {

    Node* links[26] = {};
    bool flag = false;

    bool containsKey(char ch) {
        return links[ch - 'a'] != nullptr;
    }

    void put(char ch, Node* node) {
        links[ch - 'a'] = node;
    }

    Node* get(char ch) {
        return links[ch - 'a'];
    }

    void setEnd() {
        flag = true;
    }
};


class Trie {

private:
    Node* root;

public:
    Trie() {
        root = new Node();
    }
    void insert(string word) {
        Node* node = root;
        for (int i = 0; i < word.size(); i++) {

            if (!node->containsKey(word[i])) {
                node->put(word[i], new Node());
            }
            node = node->get(word[i]);
        }

        node->setEnd();
    }

    bool search(string word) {
        Node* node = root;
        for (int i = 0; i < word.size(); i++) {
            if (!node->containsKey(word[i])) {
                return false;
            }
            node = node->get(word[i]);
        }
        return node->flag;
    }


    bool startsWith(string prefix) {
        Node* node = root;
        for (int i = 0; i < prefix.size(); i++) {
            if (!node->containsKey(prefix[i])) {
                return false;
            }
            node = node->get(prefix[i]);
        }
        return true;
    }
};



int main() {

    Trie trie;

    trie.insert("apple");

    cout << boolalpha;

    cout << trie.search("apple") << '\n';      // true
    cout << trie.search("app") << '\n';        // false
    cout << trie.startsWith("app") << '\n';    // true

    trie.insert("app");

    cout << trie.search("app") << '\n';        // true
    cout << trie.startsWith("ap") << '\n';     // true
    cout << trie.startsWith("xyz") << '\n';    // false

    return 0;
}
