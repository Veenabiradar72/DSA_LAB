#include <stdio.h>
#include <stdlib.h>

struct tree {
    int data;
    struct tree *left;
    struct tree *right;
};

typedef struct tree TREE;

// Function prototypes
TREE* insert_into_bst(TREE *root, int data);
void inorder(TREE *root);
void preorder(TREE *root);
void postorder(TREE *root);
TREE* delete_from_bst(TREE *root, int data);

// Insert into BST
TREE* insert_into_bst(TREE *root, int data) {
    TREE *newnode, *currnode, *parent;

    newnode = (TREE*)malloc(sizeof(TREE));
    if (newnode == NULL) {
        printf("Memory allocation failed\n");
        return root;
    }

    newnode->data = data;
    newnode->left = NULL;
    newnode->right = NULL;

    if (root == NULL) {
        printf("Root node inserted\n");
        return newnode;
    }

    currnode = root;
    parent = NULL;

    while (currnode != NULL) {
        parent = currnode;
        if (data < currnode->data)
            currnode = currnode->left;
        else
            currnode = currnode->right;
    }

    if (data < parent->data)
        parent->left = newnode;
    else
        parent->right = newnode;

    printf("Node inserted successfully\n");
    return root;
}

// Inorder Traversal
void inorder(TREE *root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);
    }
}

// Preorder Traversal
void preorder(TREE *root) {
    if (root != NULL) {
        printf("%d ", root->data);
        preorder(root->left);
        preorder(root->right);
    }
}

// Postorder Traversal
void postorder(TREE *root) {
    if (root != NULL) {
        postorder(root->left);
        postorder(root->right);
        printf("%d ", root->data);
    }
}

// Find minimum node
TREE* findMin(TREE *root) {
    while (root->left != NULL)
        root = root->left;
    return root;
}

// Delete from BST
TREE* delete_from_bst(TREE *root, int data) {
    if (root == NULL) {
        printf("Tree is empty\n");
        return root;
    }

    if (data < root->data) {
        root->left = delete_from_bst(root->left, data);
    }
    else if (data > root->data) {
        root->right = delete_from_bst(root->right, data);
    }
    else {
        // Node found
        if (root->left == NULL) {
            TREE *temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL) {
            TREE *temp = root->left;
            free(root);
            return temp;
        }

        // Two children
        TREE *temp = findMin(root->right);
        root->data = temp->data;
        root->right = delete_from_bst(root->right, temp->data);
    }

    return root;
}

// Main function
int main() {
    TREE *root = NULL;
    int choice, data;

    while (1) {
        printf("\n******** Menu ********\n");
        printf("1. Insert into BST\n");
        printf("2. Inorder Traversal\n");
        printf("3. Preorder Traversal\n");
        printf("4. Postorder Traversal\n");
        printf("5. Delete from BST\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter data: ");
                scanf("%d", &data);
                root = insert_into_bst(root, data);
                break;

            case 2:
                printf("Inorder: ");
                inorder(root);
                break;

            case 3:
                printf("Preorder: ");
                preorder(root);
                break;

            case 4:
                printf("Postorder: ");
                postorder(root);
                break;

            case 5:
                printf("Enter data to delete: ");
                scanf("%d", &data);
                root = delete_from_bst(root, data);
                break;

            case 6:
                exit(0);

            default:
                printf("Invalid choice\n");
        }
    }
}
