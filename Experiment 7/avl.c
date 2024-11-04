#include <stdio.h>
#include <stdlib.h>

struct Node {
    int key;
    struct Node* left;
    struct Node* right;
    int height;
};

int height(struct Node* n) {
    return (n == NULL) ? 0 : n->height;
}

struct Node* newnode(int key) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    if (!node) {
        printf("memory allocation went wrong critical\n");
        exit(1);
    }
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    return node;
}

void nuketree(struct Node* root) {
    if (root == NULL)
        return;
    nuketree(root->left);
    nuketree(root->right);
    free(root);
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

struct Node* RR(struct Node* y) {
    struct Node* x = y->left;
    struct Node* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

struct Node* LR(struct Node* x) {
    struct Node* y = x->right;
    struct Node* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;
}

int currbalance(struct Node* n) {
    return (n == NULL) ? 0 : height(n->left) - height(n->right);
}

void display(int key, char* rotation) {
    printf("node causing error: %d, how we rotate: %s\n", key, rotation);
}

struct Node* balanceTree(struct Node* node, int key) {
    int balance = currbalance(node);
   
    if (balance > 1 && key < node->left->key) {
        display(node->key, "LL");
        return RR(node);
    }

    if (balance < -1 && key > node->right->key) {
        display(node->key, "RR");
        return LR(node);
    }

    if (balance > 1 && key > node->left->key) {
        display(node->key, "LR");
        node->left = LR(node->left);
        return RR(node);
    }

    if (balance < -1 && key < node->right->key) {
        display(node->key, "RL");
        node->right = RR(node->right);
        return LR(node);
    }

    return node;
}

struct Node* insert(struct Node* node, int key) {
    if (node == NULL)
        return newnode(key);

    if (key < node->key)
        node->left = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);
    else
        return node;

    node->height = 1 + max(height(node->left), height(node->right));

    node = balanceTree(node, key);
    printf("Node: %d, Balance: %d\n", node->key, currbalance(node));
    return node;
}

struct Node* minnodevalue(struct Node* node) {
    struct Node* current = node;
    while (current->left != NULL)
        current = current->left;
    return current;
}

struct Node* delnode(struct Node* root, int key) {
    if (root == NULL)
        return root;

    if (key < root->key)
        root->left = delnode(root->left, key);
    else if (key > root->key)
        root->right = delnode(root->right, key);
    else {
        if (root->left == NULL || root->right == NULL) {
            struct Node* temp = root->left ? root->left : root->right;

            if (temp == NULL) {
                temp = root;
                root = NULL;
            } else
                *root = *temp;

            free(temp);
        } else {
            struct Node* temp = minnodevalue(root->right);
            root->key = temp->key;
            root->right = delnode(root->right, temp->key);
        }
    }

    if (root == NULL)
        return root;

    root->height = 1 + max(height(root->left), height(root->right));

    root = balanceTree(root, key);
    printf("Node: %d, Balance: %d\n", root->key, currbalance(root));
    return root;
}

void preOrder(struct Node* root) {
    if (root != NULL) {
        printf("%d ", root->key);
        preOrder(root->left);
        preOrder(root->right);
    }
}

int main() {
    struct Node* root = NULL;
    int choice, key;

    while (1) {
        printf("\n1. Insert\n2. Delete\n3. Exit\n");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            printf("num to insert: ");
            scanf("%d", &key);
            root = insert(root, key);
            preOrder(root);
            printf("\n");
            break;
        case 2:
            printf("num to del: ");
            scanf("%d", &key);
            root = delnode(root, key);
            preOrder(root);
            printf("\n");
            break;
        case 3:
            nuketree(root);
            exit(0);
        default:
            printf("wrong choice\n");
        }
    }

    return 0;
}
