#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct Node {
    int data;
    struct Node *l, *r;
};

struct Node* nodenew(int data) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->data = data;
    node->l = node->r = NULL;
    return node;
}

void preorder(struct Node* root) {
    if (root == NULL)
        return;
    printf("%d ", root->data);
    preorder(root->l);
    preorder(root->r);
}

void postorder(struct Node* root) {
    if (root == NULL)
        return;
    postorder(root->l);
    postorder(root->r);
    printf("%d ", root->data);
}

int getindex(int* arr, int start, int end, int value) {
    for (int i = start; i <= end; i++) {
        if (arr[i] == value)
            return i;
    }
    return -1;
}

struct Node* posttreemaker(int* inorder, int* postorder, int start, int end, int* postgetindex) {
    if (start > end)
        return NULL;

    struct Node* root = nodenew(postorder[*postgetindex]);
    (*postgetindex)--;

    if (start == end)
        return root;

    int ingetindex = getindex(inorder, start, end, root->data);
    root->r = posttreemaker(inorder, postorder, ingetindex + 1, end, postgetindex);
    root->l = posttreemaker(inorder, postorder, start, ingetindex - 1, postgetindex);

    return root;
}

struct Node* pretreemaker(int* inorder, int* preorder, int start, int end, int* preindex) {
    if (start > end)
        return NULL;

    struct Node* root = nodenew(preorder[*preindex]);
    (*preindex)++;

    if (start == end)
        return root;

    int ingetindex = getindex(inorder, start, end, root->data);
    root->l = pretreemaker(inorder, preorder, start, ingetindex - 1, preindex);
    root->r = pretreemaker(inorder, preorder, ingetindex + 1, end, preindex);

    return root;
}

void inorder(struct Node* root) {
    if (root == NULL)
        return;
    inorder(root->l);
    printf("%d ", root->data);
    inorder(root->r);
}

bool is_skewed(struct Node* root) {
    if (root == NULL)
        return true;
    if (root->l && root->r) 
        return false;
    return is_skewed(root->l) && is_skewed(root->r); 
}

bool has_duplicates(int* arr, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (arr[i] == arr[j]) {
                return true;
            }
        }
    }
    return false;
}

bool validate_input(int* inorder, int* order, int n) {
    if (has_duplicates(inorder, n) || has_duplicates(order, n)) {
        return false; }

    for (int i = 0; i < n; i++) {
        bool found = false;
        for (int j = 0; j < n; j++) {
            if (order[j] == inorder[i]) {
                found = true;
                break;
            }
        }
        if (!found)
            return false;
    }

    return true;
}

int main() {
    int n;
    printf("total node: ");
    scanf("%d", &n);

    int inorderArr[n], preorderArr[n], postorderArr[n];

    printf("Enter inorder sequence: ");
    for (int i = 0; i < n; i++)
        scanf("%d", &inorderArr[i]);

    int choice;
    printf("1. preorder+inorder\n2. postorder+inorder\n");
    scanf("%d", &choice);

    struct Node* root2 = NULL;

    if (choice == 1) {
        printf("Enter preorder sequence: ");
        for (int i = 0; i < n; i++)
            scanf("%d", &preorderArr[i]);

        if (!validate_input(inorderArr, preorderArr, n)) {
            printf("invalid input check again plz.\n");
            return 1;
        }

        int preindex = 0;
        root2 = pretreemaker(inorderArr, preorderArr, 0, n - 1, &preindex);

        printf("Postorder traversal of the constructed tree: ");
        postorder(root2); 
        printf("\n");

    } else if (choice == 2) {
        printf("Enter postorder sequence: ");
        for (int i = 0; i < n; i++)
            scanf("%d", &postorderArr[i]);

        if (!validate_input(inorderArr, postorderArr, n)) {
            printf("invalid input check again plz.\n");
            return 1;
        }

        int postgetindex = n - 1;
        root2 = posttreemaker(inorderArr, postorderArr, 0, n - 1, &postgetindex);

        printf("Preorder traversal of the constructed tree: ");
        preorder(root2);  
        printf("\n");

    } else {
        printf("somethign went wrong.\n");
        return 1;
    }

    if (is_skewed(root2)) {
        printf("The tree is skewed.\n");
    } else {
        printf("The tree is not skewed.\n");
    }

    return 0;
}
