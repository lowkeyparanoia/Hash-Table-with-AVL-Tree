#include <iostream>


// AVL Tree Node
struct AVLNode {
    string key;
    int value;
    int height;
    AVLNode *left;
    AVLNode *right;
    AVLNode(string k, int v) {
        key = k;
        value = v;
        left = right = NULL;
        height = 0;
    }
};

// AVL Tree Class
class AVLTree {
    AVLNode *root;
    int size;

public:
    AVLTree() {
        root = NULL;
        size = 0;
    }

    int getSize() {
        return size;
    }

    // get height of node
    int height(AVLNode *node) {
        if (node == NULL) {
            return 0;
        }
        return node->height;
    }

    // get maximum of two integers
    int max(int a, int b) {
        return (a > b) ? a : b;
    }

    // right rotate subtree rooted with node
    AVLNode* rightRotate(AVLNode *y) {
        AVLNode *x = y->left;
        AVLNode *T2 = x->right;

        // Perform rotation
        x->right = y;
        y->left = T2;

        // Update heights
        y->height = max(height(y->left), height(y->right)) + 1;
        x->height = max(height(x->left), height(x->right)) + 1;

        // Return new root
        return x;
    }

    // left rotate subtree rooted with node
    AVLNode* leftRotate(AVLNode *x) {
        AVLNode *y = x->right;
        AVLNode *T2 = y->left;

        // Perform rotation
        y->left = x;
        x->right = T2;

        // Update heights
        x->height = max(height(x->left), height(x->right)) + 1;
        y->height = max(height(y->left), height(y->right)) + 1;

        // Return new root
        return y;
    }

    // get balance factor of node
    int getBalanceFactor(AVLNode *node) {
        if (node == NULL) {
            return 0;
        }
        return height(node->left) - height(node->right);
    }

    // insert new node
    AVLNode* insert(AVLNode *node, string key, int value) {
        // 1. Perform normal BST insertion
        if (node == NULL) {
            size++;
            return (new AVLNode(key, value));
        }
        if (key < node->key) {
            node->left = insert(node->left, key, value);
        }
        else if (key > node->key) {
            node->right = insert(node->right, key, value);
        }
        else {
            return node;
        }

        // 2. Update height of this ancestor node
        node->height = 1 + max(height(node->left), height(node->right));

        // 3. Get the balance factor of this ancestor node to check whether this node became unbalanced
        int balance = getBalanceFactor(node);

        // If this node becomes unbalanced, then there are 4 cases
        // Left Left Case
        if (balance > 1 && key < node->left->key) {
            return rightRotate(node);
        }
        // Right Right Case
        if (balance < -1 && key > node->right->key) {
            return leftRotate(node);
        }
        // Left Right Case
        if (balance > 1 && key > node->left->key) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
        // Right Left Case
        if (balance < -1 && key < node->right->key) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        // return the (unchanged) node pointer
        return node;
    }

    // insert new node
    void insert(string key, int value) {
        root = insert(root, key, value);
    }

    // search value
    bool search(AVLNode *node, string key) {
        if (node == NULL) {
            return false;
        }
        if (node->key == key) {
            return true;
        }
        else if (key < node->key) {
            return search(node->left, key);
        }
        else {
            return search(node->right, key);
        }
    }

    // search value
    bool search(string key) {
        return search(root, key);
    }

    // get value of node
    int get(AVLNode *node, string key) {
        if (node == NULL) {
            return -1;
        }
        if (node->key == key) {
            return node->value;
        }
        else if (key < node->key) {
            return get(node->left, key);
        }
        else {
            return get(node->right, key);
        }
    }

    // get value of node
    int get(string key) {
        return get(root, key);
    }

    // delete node
    AVLNode* minValueNode(AVLNode* node) {
        AVLNode* current = node;

        /* loop down to find the leftmost leaf */
        while (current->left != NULL) {
            current = current->left;
        }
        return current;
    }

    AVLNode* deleteNode(AVLNode* root, string key) {
        // STEP 1: PERFORM STANDARD BST DELETE
        if (root == NULL) {
            return root;
        }

        // If the key to be deleted is smaller than the root's key, then it lies in left subtree
        if (key < root->key) {
            root->left = deleteNode(root->left, key);
        }
        // If the key to be deleted is greater than the root's key, then it lies in right subtree
        else if (key > root->key) {
            root->right = deleteNode(root->right, key);
        }
        // if key is same as root's key, then this is the node to be deleted
        else {
            // node with only one child or no child
            if ((root->left == NULL) || (root->right == NULL)) {
                AVLNode *temp = root->left ? root->left : root->right;

                // No child case
                if (temp == NULL) {
                    temp = root;
                    root = NULL;
                }
                else { // One child case
                    *root = *temp; // Copy the contents of the non-empty child
                    free(temp);
                }
            }
            else {
                // node with two children: Get the inorder successor (smallest in the right subtree)
                AVLNode* temp = minValueNode(root->right);

                // Copy the inorder successor's data to this node
                root->key = temp->key;
                root->value = temp->value;

                // Delete the inorder successor
                root->right = deleteNode(root->right, temp->key);
            }
        }

        // If the tree had only one node then return
        if (root == NULL) {
            return root;
        }

        // STEP 2: UPDATE HEIGHT OF THE CURRENT NODE
        root->height = 1 + max(height(root->left), height(root->right));

        // STEP 3: GET THE BALANCE FACTOR OF THIS NODE (to check whether this node became unbalanced)
        int balance = getBalanceFactor(root);

        // If this node becomes unbalanced, then there are 4 cases

        // Left Left Case
        if (balance > 1 && getBalanceFactor(root->left) >= 0) {
            return rightRotate(root);
        }

        // Left Right Case
        if (balance > 1 && getBalanceFactor(root->left) < 0) {
            root->left = leftRotate(root->left);
            return rightRotate(root);
        }

        // Right Right Case
        if (balance < -1 && getBalanceFactor(root->right) <= 0) {
            return leftRotate(root);
        }

        // Right Left Case
        if (balance < -1 && getBalanceFactor(root->right) > 0) {
            root->right = rightRotate(root->right);
            return leftRotate(root);
        }

        // return the (unchanged) node pointer
        return root;
    }

    // delete node
    void remove(string key) {
        root = deleteNode(root, key);
        size--;
    }
};
