#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

struct Node* createNode(int value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = value;
    newNode->left = newNode->right = NULL;
    return newNode;
}

struct Node* insert(struct Node* root, int value) {
    if (root == NULL)
        return createNode(value);

    if (value < root->data)
        root->left = insert(root->left, value);
    else if (value > root->data)
        root->right = insert(root->right, value);

    return root;
}

// inorder traversal without trailing space
void inorder(struct Node* root, int *first) {
    if (root != NULL) {
        inorder(root->left, first);

        if (*first) {
            printf("%d", root->data);
            *first = 0;
        } else {
            printf(" %d", root->data);
        }

        inorder(root->right, first);
    }
}

int main() {
    int n;

    scanf("%d", &n);

    // Check invalid n
    if (n == -1) {
        printf("Invalid input");
        return 0;
    }

    int arr[100];

    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
        if (arr[i] == -1) {
            printf("Invalid input");
            return 0;
        }
    }

    int insertVal;
    scanf("%d", &insertVal);

    if (insertVal == -1) {
        printf("Invalid input");
        return 0;
    }

    struct Node* root = NULL;

    // Build BST
    for (int i = 0; i < n; i++) {
        root = insert(root, arr[i]);
    }

    // Insert new router
    root = insert(root, insertVal);

    // Print inorder
    int first = 1;
    inorder(root, &first);

    printf("\n");

    return 0;
}
