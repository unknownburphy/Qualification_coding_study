#include <iostream>
#include <queue>

using namespace std;

class node{
    public:
        int val;
        node* left;
        node* right;
        node(int x) : val(x), left(nullptr), right(nullptr){}
};

//BFS

void BFS(node* root){
    if(!root) return;
    
    queue<node*> q;
    q.push(root);

    while(!q.empty()){
        node* n = q.front();
        q.pop();
        cout << n->val << "->";

        if (n->left) q.push(n->left);
        if (n->right) q.push(n->right);
    }
}

//DFS

void preorderDFS(node* root){
    if(!root) return;
    cout << root->val << "->";
    preorderDFS(root->left);
    preorderDFS(root->right);
}

void inorderDFS(node* root){
    if(!root) return;

    inorderDFS(root->left);
    cout << root->val <<  "->";
    inorderDFS(root->right);
}

void postorderDFS(node* root){
    if(!root) return;

    postorderDFS(root->left);
    cout << root->val <<  "->";
    postorderDFS(root->right);
}

int main() {
    // Creating a binary search tree
    node* root = new node(4);
    root->left = new node(2);
    root->right = new node(6);
    root->left->left = new node(1);
    root->left->right = new node(3);
    root->right->left = new node(5);
    root->right->right = new node(7);

    cout << "BFS (Level-order): ";
    BFS(root);
    cout << endl;

    cout << "DFS (Pre-order): ";
    preorderDFS(root);
    cout << endl;

    cout << "DFS (In-order): ";
    inorderDFS(root);
    cout << endl;

    cout << "DFS (Post-order): ";
    postorderDFS(root);
    cout << endl;

    // Clean up memory
    delete root->left->left;
    delete root->left->right;
    delete root->left;
    delete root->right->left;
    delete root->right->right;
    delete root->right;
    delete root;

    return 0;
}