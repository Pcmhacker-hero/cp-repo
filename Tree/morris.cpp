/*
============================================================
                MORRIS TREE TRAVERSALS
============================================================

Contents
1. Morris Inorder Traversal   -> O(N) Time | O(1) Space
2. Morris Preorder Traversal  -> O(N) Time | O(1) Space

============================================================
*/

#include <bits/stdc++.h>
using namespace std;

class Node {
public:
    int val;
    Node* left;
    Node* right;

    Node(int value) {
        val = value;
        left = nullptr;
        right = nullptr;
    }
};

//============================================================
// Morris Inorder Traversal
// Time  : O(N)
// Space : O(1)
//============================================================

vector<int> morrisInorder(Node* root) {

    vector<int> inorder;
    Node* curr = root;

    while (curr != nullptr) {

        if (curr->left == nullptr) {

            inorder.push_back(curr->val);
            curr = curr->right;

        } else {

            Node* prev = curr->left;

            while (prev->right && prev->right != curr)
                prev = prev->right;

            if (prev->right == nullptr) {

                prev->right = curr;
                curr = curr->left;

            } else {

                prev->right = nullptr;
                inorder.push_back(curr->val);
                curr = curr->right;
            }
        }
    }

    return inorder;
}

//============================================================
// Morris Preorder Traversal
// Time  : O(N)
// Space : O(1)
//============================================================

vector<int> morrisPreorder(Node* root) {

    vector<int> preorder;
    Node* curr = root;

    while (curr != nullptr) {

        if (curr->left == nullptr) {

            preorder.push_back(curr->val);
            curr = curr->right;

        } else {

            Node* prev = curr->left;

            while (prev->right && prev->right != curr)
                prev = prev->right;

            if (prev->right == nullptr) {

                preorder.push_back(curr->val);
                prev->right = curr;
                curr = curr->left;

            } else {

                prev->right = nullptr;
                curr = curr->right;
            }
        }
    }

    return preorder;
}

//============================================================
// Driver Code
//============================================================

int main() {

    Node* root = new Node(1);
    root->left = new Node(2);
    root->right = new Node(3);
    root->left->left = new Node(4);
    root->left->right = new Node(5);
    root->right->left = new Node(6);
    root->right->right = new Node(7);

    vector<int> inorder = morrisInorder(root);
    vector<int> preorder = morrisPreorder(root);

    cout << "Morris Inorder  : ";
    for (int x : inorder)
        cout << x << " ";

    cout << "\n";

    cout << "Morris Preorder : ";
    for (int x : preorder)
        cout << x << " ";

    cout << "\n";

    return 0;
}
