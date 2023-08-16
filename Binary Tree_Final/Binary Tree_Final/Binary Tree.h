#pragma once
#define SPACE 10 
using namespace std;

class TreeNode {
public:
    int value;
    TreeNode* left;
    TreeNode* right;

    TreeNode() {
        value = 0;
        left = NULL;
        right = NULL;
    }
    TreeNode(int v) {
        value = v;
        left = NULL;
        right = NULL;
    }
};

class BST {
public:
    TreeNode* root;
    BST() {
        root = NULL;
    }
    bool isTreeEmpty() {
        if (root == NULL) {
            return true;
        }
        else {
            return false;
        }
    }

    void insertNode(TreeNode* new_node) {
        if (root == NULL) {
            root = new_node;
            cout << "Value Inserted as root node!" << endl;
        }
        else {
            TreeNode* temp = root;
            while (temp != NULL) {
                if (new_node->value == temp->value) {
                    cout << "Value Already exist," <<
                        "Insert another value!" << endl;
                    return;
                }
                else if ((new_node->value < temp->value) && (temp->left == NULL)) {
                    temp->left = new_node;
                    cout << "Value Inserted to the left!" << endl;
                    break;
                }
                else if (new_node->value < temp->value) {
                    temp = temp->left;
                }
                else if ((new_node->value > temp->value) && (temp->right == NULL)) {
                    temp->right = new_node;
                    cout << "Value Inserted to the right!" << endl;
                    break;
                }
                else {
                    temp = temp->right;
                }
            }
        }
    }
    TreeNode* insertRecursive(TreeNode* r, TreeNode* new_node)
    {
        if (r == NULL)
        {
            r = new_node;
            cout << "Insertion successful" << endl;
            return r;
        }

        if (new_node->value < r->value)
        {
            r->left = insertRecursive(r->left, new_node);
        }
        else if (new_node->value > r->value)
        {
            r->right = insertRecursive(r->right, new_node);
        }
        else
        {
            cout << "No duplicate values allowed!" << endl;
            return r;
        }
        return r;
    }

    void print2D(TreeNode* r, int space) {
        if (r == NULL) // Base case  1
            return;
        space += SPACE; // Increase distance between levels   2
        print2D(r->right, space); // Process right child first 3 
        cout << endl;
        for (int i = SPACE; i < space; i++) // 5 
            cout << " "; // 5.1  
        cout << r->value << "\n"; // 6
        print2D(r->left, space); // Process left child  7
    }

    void printPreorder(TreeNode* r) //(current node, Left, Right) 
    {
        if (r == NULL)
            return;
        /* first print data of node */
        cout << r->value << " ";
        /* then recur on left sutree */
        printPreorder(r->left);
        /* now recur on right subtree */
        printPreorder(r->right);
    }

    void printInorder(TreeNode* r) //  (Left, current node, Right)
    {
        if (r == NULL)
            return;
        /* first recur on left child */
        printInorder(r->left);
        /* then print the data of node */
        cout << r->value << " ";
        /* now recur on right child */
        printInorder(r->right);
    }
    void printPostorder(TreeNode* r) //(Left, Right, Root)
    {
        if (r == NULL)
            return;
        // first recur on left subtree 
        printPostorder(r->left);
        // then recur on right subtree 
        printPostorder(r->right);
        // now deal with the node 
        cout << r->value << " ";
    }

    TreeNode* iterativeSearch(int v) {
        if (root == NULL) {
            return root;
        }
        else {
            TreeNode* temp = root;
            while (temp != NULL) {
                if (v == temp->value) {
                    return temp;
                }
                else if (v < temp->value) {
                    temp = temp->left;
                }
                else {
                    temp = temp->right;
                }
            }
            return NULL;
        }
    }

    TreeNode* recursiveSearch(TreeNode* r, int val) {
        if (r == NULL || r->value == val)
            return r;

        else if (val < r->value)
            return recursiveSearch(r->left, val);

        else
            return recursiveSearch(r->right, val);
    }

    int height(TreeNode* r) {
        if (r == NULL)
            return -1;
        else {
            /* compute the height of each subtree */
            int lheight = height(r->left);
            int rheight = height(r->right);

            /* use the larger one */
            if (lheight > rheight)
                return (lheight + 1);
            else return (rheight + 1);
        }
    }

    /* Print nodes at a given level */
    void printGivenLevel(TreeNode* r, int level) {
        if (r == NULL)
            return;
        else if (level == 0)
            cout << r->value << " ";
        else // level > 0  
        {
            printGivenLevel(r->left, level - 1);
            printGivenLevel(r->right, level - 1);
        }
    }
    void printLevelOrderBFS(TreeNode* r) {
        int h = height(r);
        for (int i = 0; i <= h; i++)
            printGivenLevel(r, i);
    }

    TreeNode* minValueNode(TreeNode* node) {
        TreeNode* current = node;
        /* loop down to find the leftmost leaf */
        while (current->left != NULL) {
            current = current->left;
        }
        return current;
    }

    TreeNode* deleteNode(TreeNode* r, int v) {
        // base case 
        if (r == NULL) {
            return NULL;
        }
        // If the key to be deleted is smaller than the root's key, 
        // then it lies in left subtree 
        else if (v < r->value) {
            r->left = deleteNode(r->left, v);
        }
        // If the key to be deleted is greater than the root's key, 
        // then it lies in right subtree 
        else if (v > r->value) {
            r->right = deleteNode(r->right, v);
        }
        // if key is same as root's key, then This is the node to be deleted 
        else {
            // node with only one child or no child 
            if (r->left == NULL) {
                TreeNode* temp = r->right;
                delete r;
                return temp;
            }
            else if (r->right == NULL) {
                TreeNode* temp = r->left;
                delete r;
                return temp;
            }
            else {
                // node with two children: Get the inorder successor (smallest 
                // in the right subtree) 
                TreeNode* temp = minValueNode(r->right);
                // Copy the inorder successor's content to this node 
                r->value = temp->value;
                // Delete the inorder successor 
                r->right = deleteNode(r->right, temp->value);
                //deleteNode(r->right, temp->value); 
            }
        }
        return r;
    }

};