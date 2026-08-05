#include <iostream>
#include <vector>
#include <stack>

using namespace std;

class Node {
public:
    int data;
    Node* left;
    Node* right;

    Node(int value) {
        data = value;
        left = nullptr;
        right = nullptr;
    }
};

/*
============================================================
                    ITERATIVE DFS TRAVERSALS
============================================================

1. Preorder  : Root -> Left -> Right
2. Inorder   : Left -> Root -> Right
3. Postorder : Left -> Right -> Root (Two Stacks)
4. Postorder : Left -> Right -> Root (One Stack)

Time Complexity  : O(N)
Space Complexity : O(H) to O(N)
(H = Height of the Tree)

============================================================
*/


//------------------------------------------------------------
// 1. Iterative Preorder Traversal
//------------------------------------------------------------
vector<int> preorder(Node* root) {
    vector<int> ans;

    if (root == nullptr)
        return ans;

    stack<Node*> st;
    st.push(root);

    while (!st.empty()) {
        Node* current = st.top();
        st.pop();

        ans.push_back(current->data);

        // Right is pushed first so that Left is processed first.
        if (current->right != nullptr)
            st.push(current->right);

        if (current->left != nullptr)
            st.push(current->left);
    }

    return ans;
}


//------------------------------------------------------------
// 2. Iterative Inorder Traversal
//------------------------------------------------------------
vector<int> inorder(Node* root) {
    vector<int> ans;

    stack<Node*> st;
    Node* current = root;

    while (current != nullptr || !st.empty()) {

        while (current != nullptr) {
            st.push(current);
            current = current->left;
        }

        current = st.top();
        st.pop();

        ans.push_back(current->data);

        current = current->right;
    }

    return ans;
}


//------------------------------------------------------------
// 3. Iterative Postorder Traversal (Two Stacks)
//------------------------------------------------------------
vector<int> postorderTwoStacks(Node* root) {
    vector<int> ans;

    if (root == nullptr)
        return ans;

    stack<Node*> st1;
    stack<Node*> st2;

    st1.push(root);

    while (!st1.empty()) {
        Node* current = st1.top();
        st1.pop();

        st2.push(current);

        if (current->left != nullptr)
            st1.push(current->left);

        if (current->right != nullptr)
            st1.push(current->right);
    }

    while (!st2.empty()) {
        ans.push_back(st2.top()->data);
        st2.pop();
    }

    return ans;
}


//------------------------------------------------------------
// 4. Iterative Postorder Traversal (One Stack)
//------------------------------------------------------------
vector<int> postorderOneStack(Node* root) {
    vector<int> ans;

    if (root == nullptr)
        return ans;

    stack<Node*> st;
    Node* current = root;
    Node* lastVisited = nullptr;

    while (current != nullptr || !st.empty()) {

        if (current != nullptr) {
            st.push(current);
            current = current->left;
        }
        else {
            Node* node = st.top();

            if (node->right != nullptr && lastVisited != node->right) {
                current = node->right;
            }
            else {
                ans.push_back(node->data);
                lastVisited = node;
                st.pop();
            }
        }
    }

    return ans;
}


//------------------------------------------------------------
// Utility Function
//------------------------------------------------------------
void printVector(const vector<int>& traversal) {
    for (int value : traversal)
        cout << value << " ";

    cout << '\n';
}


//------------------------------------------------------------
// Driver Code
//------------------------------------------------------------
int main() {

    /*
                 1
              /     \
             2       3
           /   \   /   \
          4     5 6     7

    Preorder  : 1 2 4 5 3 6 7
    Inorder   : 4 2 5 1 6 3 7
    Postorder : 4 5 2 6 7 3 1
    */

    Node* root = new Node(1);

    root->left = new Node(2);
    root->right = new Node(3);

    root->left->left = new Node(4);
    root->left->right = new Node(5);

    root->right->left = new Node(6);
    root->right->right = new Node(7);

    cout << "Preorder Traversal:\n";
    printVector(preorder(root));

    cout << "\nInorder Traversal:\n";
    printVector(inorder(root));

    cout << "\nPostorder Traversal (Two Stacks):\n";
    printVector(postorderTwoStacks(root));

    cout << "\nPostorder Traversal (One Stack):\n";
    printVector(postorderOneStack(root));

    return 0;
}
