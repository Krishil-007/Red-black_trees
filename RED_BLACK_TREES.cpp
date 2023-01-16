
#include <bits/stdc++.h>
using namespace std;
struct Node
{
    int data;
    Node *parent;
    Node *left;
    Node *right;
    int color; // 1 indicates Red , 0 indicates Black
};
typedef Node *NodePtr;
class Red_Black_Tree
{
    NodePtr root;
    NodePtr NIL;

    void initializeNode(NodePtr node, NodePtr parent)
    {
        node->data = 0;
        node->parent = parent;
        node->left = nullptr;
        node->right = nullptr;
        node->color = 0;
    }

    void preOrderHelper(NodePtr node)
    {
        if (node != NIL)
        {
            cout << node->data << " ";
            preOrderHelper(node->left);
            preOrderHelper(node->right);
        }
    }

    void inOrderHelper(NodePtr node)
    {
        if (node != NIL)
        {
            inOrderHelper(node->left);
            cout << node->data << " ";
            inOrderHelper(node->right);
        }
    }

    void postOrderHelper(NodePtr node)
    {
        if (node != NIL)
        {
            postOrderHelper(node->left);
            postOrderHelper(node->right);
            cout << node->data << " ";
        }
    }

    NodePtr searchT(NodePtr node, int key)
    {
        if (node == NIL || key == node->data)
            return node;

        if (key < node->data)
            return searchT(node->left, key);

        return searchT(node->right, key);
    }

    void fixDelete(NodePtr x)
    {
        NodePtr new_Node;
        while (x != root && x->color == 0)
        {
            if (x == x->parent->left)
            {
                new_Node = x->parent->right;

                if (new_Node->color == 1)
                {
                    // case 3.1
                    new_Node->color = 0;
                    x->parent->color = 1;
                    leftRotate(x->parent);
                    new_Node = x->parent->right;
                }

                if (new_Node->left->color == 0 && new_Node->right->color == 0)
                {
                    // case 3.2
                    new_Node->color = 1;
                    x = x->parent;
                }
                else
                {
                    if (new_Node->right->color == 0)
                    {
                        // case 3.3
                        new_Node->left->color = 0;
                        new_Node->color = 1;
                        rightRotate(new_Node);
                        new_Node = x->parent->right;
                    }

                    // case 3.4
                    new_Node->color = x->parent->color;
                    x->parent->color = 0;
                    new_Node->right->color = 0;
                    leftRotate(x->parent);
                    x = root;
                }
            }
            else
            {
                new_Node = x->parent->left;
                if (new_Node->color == 1)
                {
                    // case 3.1
                    new_Node->color = 0;
                    x->parent->color = 1;
                    rightRotate(x->parent);
                    new_Node = x->parent->left;
                }

                if (new_Node->right->color == 0 && new_Node->right->color == 0)
                {
                    // case 3.2
                    new_Node->color = 1;
                    x = x->parent;
                }
                else
                {
                    if (new_Node->left->color == 0)
                    {
                        // case 3.3
                        new_Node->right->color = 0;
                        new_Node->color = 1;
                        leftRotate(new_Node);
                        new_Node = x->parent->left;
                    }

                    // case 3.4
                    new_Node->color = x->parent->color;
                    x->parent->color = 0;
                    new_Node->left->color = 0;
                    rightRotate(x->parent);
                    x = root;
                }
            }
        }
        x->color = 0;
    }

    void rbTransplant(NodePtr u, NodePtr v)
    {
        if (u->parent == nullptr)
            root = v;
        else if (u == u->parent->left)
            u->parent->left = v;
        else
            u->parent->right = v;

        v->parent = u->parent;
    }

    void deleteNodeHelper(NodePtr node, int key)
    {
        // find the node containing key
        NodePtr z = NIL;
        NodePtr x, y;
        while (node != NIL)
        {
            if (node->data == key)
                z = node;

            if (node->data <= key)
                node = node->right;
            else
                node = node->left;
        }

        if (z == NIL)
        {
            cout << "Couldn't find key in the tree" << endl;
            return;
        }

        y = z;
        int y_original_color = y->color;

        if (z->left == NIL)
        {
            x = z->right;
            rbTransplant(z, z->right);
        }
        else if (z->right == NIL)
        {
            x = z->left;
            rbTransplant(z, z->left);
        }
        else
        {
            y = minimum(z->right);
            y_original_color = y->color;
            x = y->right;

            if (y->parent == z)
                x->parent = y;
            else
            {
                rbTransplant(y, y->right);
                y->right = z->right;
                y->right->parent = y;
            }

            rbTransplant(z, y);

            y->left = z->left;
            y->left->parent = y;
            y->color = z->color;
        }

        delete z;

        if (y_original_color == 0)
            fixDelete(x);
    }

    void fixInsert(NodePtr k)
    {
        NodePtr new_Node;
        while (k->parent->color == 1)
        {
            if (k->parent == k->parent->parent->right)
            {
                new_Node = k->parent->parent->left; // parent->sibling

                if (new_Node->color == 1)
                {
                    // case 3.1
                    new_Node->color = 0;
                    k->parent->color = 0;
                    k->parent->parent->color = 1;
                    k = k->parent->parent;
                }
                else
                {
                    if (k == k->parent->left)
                    {
                        // case 3.2.2
                        k = k->parent;
                        rightRotate(k);
                    }
                    // case 3.2.1
                    k->parent->color = 0;
                    k->parent->parent->color = 1;
                    leftRotate(k->parent->parent);
                }
            }
            else
            {
                new_Node = k->parent->parent->right; // parent->sibling

                if (new_Node->color == 1)
                {
                    // mirror case 3.1
                    new_Node->color = 0;
                    k->parent->color = 0;
                    k->parent->parent->color = 1;
                    k = k->parent->parent;
                }
                else
                {
                    if (k == k->parent->right)
                    {
                        // mirror case 3.2.2
                        k = k->parent;
                        leftRotate(k);
                    }
                    // mirror case 3.2.1
                    k->parent->color = 0;
                    k->parent->parent->color = 1;
                    rightRotate(k->parent->parent);
                }
            }
            if (k == root)
                break;
        }
        root->color = 0;
    }

    void showFullHorizontal(const Node *ptr, int space) const
    {
        // Analysis :- O(n)

        if (!ptr)
            return;

        space++;

        showFullHorizontal(ptr->right, space);

        for (int i = 1; i < space; i++)
            std::cout << "	  ";

        if (ptr->color == 1)
        {
            if (ptr->data != -1)
                cout << "R " << ptr->data << "\n";
            else
                cout << "R NULL"
                     << "\n";
        }
        else
        {
            if (ptr->data != -1)
                cout << "B " << ptr->data << "\n";
            else
                cout << "B NULL"
                     << "\n";
        }

        showFullHorizontal(ptr->left, space);
    }

public:
    Red_Black_Tree()
    {
        NIL = new Node;
        NIL->left = nullptr;
        NIL->right = nullptr;
        NIL->data = -1;
        NIL->color = 0;
        root = NIL;
    }
    
    void preorder()
    {
        preOrderHelper(this->root);
    }
    
    void inorder()
    {
        inOrderHelper(this->root);
    }
    
    void postorder()
    {
        postOrderHelper(this->root);
    }
    
    NodePtr searchTree(int k)
    {
        return searchT(this->root, k);
    }
    
    NodePtr minimum(NodePtr node)
    {
        while (node->left != NIL)
            node = node->left;
        return node;
    }

    NodePtr maximum(NodePtr node)
    {
        while (node->right != NIL)
            node = node->right;
        return node;
    }

    NodePtr successor(NodePtr x)
    {
        // if the right subtree is not null,
        // the successor is the leftmost node in the
        // right subtree
        if (x->right != NIL)
            return minimum(x->right);

        // else it is the lowest ancestor of x whose
        // left child is also an ancestor of x.
        NodePtr y = x->parent;
        while (y != NIL && x == y->right)
        {
            x = y;
            y = y->parent;
        }
        return y;
    }

    NodePtr predecessor(NodePtr x)
    {
        // if the left subtree is not null,
        // the predecessor is the rightmost node in the
        // left subtree
        if (x->left != NIL)
            return maximum(x->left);

        NodePtr y = x->parent;
        while (y != NIL && x == y->left)
        {
            x = y;
            y = y->parent;
        }

        return y;
    }

    void leftRotate(NodePtr x)
    {
        NodePtr y = x->right;
        x->right = y->left;
        if (y->left != NIL)
            y->left->parent = x;

        y->parent = x->parent;

        if (x->parent == nullptr)
            this->root = y;
        else if (x == x->parent->left)
            x->parent->left = y;
        else
            x->parent->right = y;

        y->left = x;
        x->parent = y;
    }

    void rightRotate(NodePtr x)
    {
        NodePtr y = x->left;
        x->left = y->right;
        if (y->right != NIL)
            y->right->parent = x;
        y->parent = x->parent;

        if (x->parent == nullptr)
            this->root = y;
        else if (x == x->parent->right)
            x->parent->right = y;
        else
            x->parent->left = y;

        y->right = x;
        x->parent = y;
    }

    void insert(int key)
    {
        // Ordinary Binary Search Insertion
        NodePtr node = new Node;
        node->data = key;
        node->left = NIL;
        node->right = NIL;
        node->parent = nullptr;
        node->color = 1; // new node must be red

        NodePtr y = nullptr;
        NodePtr x = this->root;

        while (x != NIL)
        {
            y = x;
            if (node->data < x->data)
                x = x->left;
            else
                x = x->right;
        }

        // y is parent of x
        node->parent = y;
        if (y == nullptr)
            root = node;
        else if (node->data < y->data)
            y->left = node;
        else
            y->right = node;

        // if new node is a root node, simply return
        if (node->parent == nullptr)
        {
            node->color = 0;
            return;
        }

        // if the grandparent is null, simply return
        if (node->parent->parent == nullptr)
            return;

        // Fix the tree
        fixInsert(node);
    }

    void deleteNode(int data)
    {

        deleteNodeHelper(this->root, data);
    }

    void prettyPrint()
    {
        if (root)
        {
            // printHelper(this->root, "", true);
            showFullHorizontal(this->root, 0);
        }
    }
};

void showMenu()
{
    printf("\n***************************************************************************************************************");
    printf("\n**                                                 MAIN MENU                                                 **");
    printf("\n***************************************************************************************************************");
    printf("\n**\t\t\t  1.   Insert                                                                        **");
    printf("\n**\t\t\t  2.   Delete                                                                        **");
    printf("\n**\t\t\t  3.   Display Tree                                                                  **");
    printf("\n**\t\t\t  4.   Preorder                                                                      **");
    printf("\n**\t\t\t  5.   Inorder                                                                       **");
    printf("\n**\t\t\t  6.   Postorder                                                                     **");
    printf("\n**\t\t\t  7.   Search Node                                                                   **");
    printf("\n**\t\t\t  8.   Exit                                                                          **");
    printf("\n***************************************************************************************************************");
    printf("\n\t\t\t---->> Enter your choice :");
}

int main()
{
    int c = 8;
    Red_Black_Tree tree;
    do
    {
        showMenu();
        cin >> c;

        switch (c)
        {
        case 1:
            int data;
            cout << "\nEnter data to be inseted(except -1) : ";
            cin >> data;
            tree.insert(data);
            break;

        case 2:
            cout << "\nEnter data to be deleted : ";
            cin >> data;
            tree.deleteNode(data);
            break;

        case 3:
            tree.prettyPrint();
            break;

        case 4:
            tree.preorder();
            break;

        case 5:
            tree.inorder();
            break;

        case 6:
            tree.postorder();
            break;

        case 7:
            cout << "\nEnter data to search : ";
            cin >> data;
            tree.searchTree(data);
            break;

        case 8:
            cout << "Thank You !!!\n";
            break;

        default:
            cout << "\nInvalid choice...";
            break;
        }

    } while (c != 8);

    return 0;
}