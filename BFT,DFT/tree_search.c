#include <stdio.h>
#include <stdlib.h>

struct TreeNode {
    int val;
    struct TreeNode* left;
    struct TreeNode* right;
};

struct TreeNode* createNode(int val) {
    struct TreeNode* newNode = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    newNode->val = val;
    newNode->left = newNode->right = NULL;
    return newNode;
}

void BFS(struct TreeNode* root) {
    if (root == NULL) return;

    struct TreeNode* queue[100];
    int front = 0, rear = 0;

    queue[rear++] = root;

    while (front < rear) {
        struct TreeNode* node = queue[front++];
        printf("%d->", node->val);

        if (node->left) queue[rear++] = node->left;
        if (node->right) queue[rear++] = node->right;
    }
}

void preOrderDFS(struct TreeNode* root) {
    if (root == NULL) return;
    printf("%d->", root->val);
    preOrderDFS(root->left);
    preOrderDFS(root->right);
}

void inOrderDFS(struct TreeNode* root) {
    if (root == NULL) return;
    inOrderDFS(root->left);
    printf("%d->", root->val);
    inOrderDFS(root->right);
}

void postOrderDFS(struct TreeNode* root) {
    if (root == NULL) return;
    postOrderDFS(root->left);
    postOrderDFS(root->right);
    printf("%d->", root->val);
}

int main() {
    struct TreeNode* root = createNode(4);
    root->left = createNode(2);
    root->right = createNode(6);
    root->left->left = createNode(1);
    root->left->right = createNode(3);
    root->right->left = createNode(5);
    root->right->right = createNode(7);

    printf("BFS (Level-order):");
    BFS(root);
    printf("\n");

    printf("DFS (Pre-order):");
    preOrderDFS(root);
    printf("\n");

    printf("DFS (In-order):");
    inOrderDFS(root);
    printf("\n");

    printf("DFS (Post-order):");
    postOrderDFS(root);
    printf("\n");

    return 0;
}
