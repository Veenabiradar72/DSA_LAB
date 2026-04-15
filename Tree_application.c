#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node {
    int id;
    char name[50];
    struct Node *left, *right;
};

// Create Node
struct Node* createNode(int id, char name[]) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->id = id;
    strcpy(newNode->name, name);
    newNode->left = newNode->right = NULL;
    return newNode;
}

// Insert Node
struct Node* insert(struct Node* root, int id, char name[]) {
    if (root == NULL)
        return createNode(id, name);

    if (id < root->id)
        root->left = insert(root->left, id, name);
    else if (id > root->id)
        root->right = insert(root->right, id, name);

    return root;
}

// Search Node
struct Node* search(struct Node* root, int id) {
    if (root == NULL || root->id == id)
        return root;

    if (id < root->id)
        return search(root->left, id);
    else
        return search(root->right, id);
}

// Find Minimum
struct Node* findMin(struct Node* root) {
    while (root->left != NULL)
        root = root->left;
    return root;
}

// Delete Node
struct Node* deleteNode(struct Node* root, int id) {
    if (root == NULL) return root;

    if (id < root->id)
        root->left = deleteNode(root->left, id);
    else if (id > root->id)
        root->right = deleteNode(root->right, id);
    else {
        // Case 1 & 2
        if (root->left == NULL) {
            struct Node* temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL) {
            struct Node* temp = root->left;
            free(root);
            return temp;
        }

        // Case 3
        struct Node* temp = findMin(root->right);
        root->id = temp->id;
        strcpy(root->name, temp->name);
        root->right = deleteNode(root->right, temp->id);
    }
    return root;
}

// Inorder Traversal
void inorder(struct Node* root) {
    if (root != NULL) {
        inorder(root->left);
        printf("ID: %d, Name: %s\n", root->id, root->name);
        inorder(root->right);
    }
}

// Main Function
int main() {
    struct Node* root = NULL;
    int choice, id;
    char name[50];

    do {
        printf("\n1.Insert\n2.Search\n3.Delete\n4.Display\n5.Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                printf("Enter ID: ");
                scanf("%d", &id);
                printf("Enter Name: ");
                scanf("%s", name);
                root = insert(root, id, name);
                break;

            case 2:
                printf("Enter ID to search: ");
                scanf("%d", &id);
                if (search(root, id) != NULL)
                    printf("Student Found\n");
                else
                    printf("Student Not Found\n");
                break;

            case 3:
                printf("Enter ID to delete: ");
                scanf("%d", &id);
                root = deleteNode(root, id);
                printf("Deletion attempted\n");
                break;

            case 4:
                printf("Student Records (Sorted):\n");
                inorder(root);
                break;

        }
    } while(choice != 5);

    return 0;
}
