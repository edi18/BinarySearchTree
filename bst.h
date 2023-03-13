#ifndef BST_H
#define BST_H

#include <vector>

template <typename T>
class BST
{
public:
    BST() : root(nullptr), n(0) {}

    BST(const std::vector<T>& v) : BST()
    {
        for (int i = 0; i < v.size(); i++)
        {
            push(v[i]);
        }
    }

    ~BST()
    {
        deleteRec(root);
    }

    int size() const { return n; }

    bool empty() const { return root == nullptr; }

    void push(const T& el)
    {
        if (root == nullptr)
        {
            root = new Node(nullptr, nullptr, nullptr, el);
            n++;
            return;
        }

        Node* node = root;
        Node* parent = nullptr;
        while (node != nullptr)
        {
            parent = node;
            if (el < node->el)
            {
                node = node->left;
            }
            else
            {
                node = node->right;
            }
        }
        
        if (el < parent->el)
        {
            parent->left = new Node(parent, nullptr, nullptr, el);
        }
        else
        {
            parent->right = new Node(parent, nullptr, nullptr, el);
        }

        n++;
    }

    bool exists(const T& el)
    {
        return findRec(root, el) != nullptr;
    }

    void forEach(void (f)(T&))
    {
        forEachRec(root, f);
    }

    T min()
    {
        return minSubTree(root)->el;
    }

    T max()
    {
        return maxSubTree(root)->el;
    }

    void erase(const T& el)
    {
        Node* toDelete = findRec(root, el);

        if (toDelete->left == nullptr && toDelete->right == nullptr)
        {
            if (toDelete->parent->left == toDelete)
            {
                toDelete->parent->left = nullptr;
                delete toDelete;
            }
            else
            {
                toDelete->parent->right = nullptr;
                delete toDelete;
            }
        }
        else if (toDelete->left != nullptr && toDelete->right == nullptr)
        {
            if (toDelete->parent->left == toDelete)
            {
                toDelete->parent->left = toDelete->left;
                toDelete->left->parent = toDelete->parent;
                delete toDelete;
            }
            else
            {
                toDelete->parent->right = toDelete->left;
                toDelete->left->parent = toDelete->parent;
                delete toDelete;
            }
        }
        else if (toDelete->left == nullptr && toDelete->right != nullptr)
        {
            if (toDelete->parent->left == toDelete)
            {
                toDelete->parent->left = toDelete->right;
                toDelete->right->parent = toDelete->parent;
                delete toDelete;
            }
            else
            {
                toDelete->parent->right = toDelete->right;
                toDelete->right->parent = toDelete->parent;
                delete toDelete;
            }
        }
        else
        {
            Node* minNode = minSubTree(toDelete->right);
            toDelete->el = minNode->el;
            eraseSimple(minNode);
        }
    }
private:
    struct Node
    {
        Node(Node* parent, Node* left, Node* right, const T& el) : parent(parent), left(left), right(right), el(el) {}
        Node* parent;
        Node* left;
        Node* right;
        T el;
    };

    Node* root;
    int n;

    // bool existsRec(Node* node, const T& el)
    // {
    //     if (node == nullptr)
    //     {
    //         return false;
    //     }

    //     if (el < node->el)
    //     {
    //         existsRec(node->left, el);
    //     }
    //     else if (el > node->el)
    //     {
    //         existsRec(node->right, el);
    //     }
    //     else
    //     {
    //         return true;
    //     }
    // }

    void forEachRec(Node* node, void (f)(T&))
    {
        if (node == nullptr)
        {
            return;
        }

        forEachRec(node->left, f);
        f(node->el);
        forEachRec(node->right, f);
    }

    void deleteRec(Node* node)
    {
        if (node == nullptr)
        {
            return;
        }

        deleteRec(node->left);
        deleteRec(node->right);
        delete node;
    }

    Node* minSubTree(Node* node)
    {
        while (node->left != nullptr)
        {
            node = node->left;
        }

        return node;
    }

    Node* maxSubTree(Node* node)
    {
        while (node->right != nullptr)
        {
            node = node->right;
        }

        return node;
    }

    Node* findRec(Node* node, const T& el)
    {
        if (node == nullptr)
        {
            return nullptr;
        }

        if (el < node->el)
        {
            findRec(node->left, el);
        }
        else if (el > node->el)
        {
            findRec(node->right, el);
        }
        else
        {
            return node;
        }
    }

    void eraseSimple(Node* toDelete)
    {
        if (toDelete->left == nullptr && toDelete->right == nullptr)
        {
            if (toDelete->parent->left == toDelete)
            {
                toDelete->parent->left = nullptr;
                delete toDelete;
            }
            else
            {
                toDelete->parent->right = nullptr;
                delete toDelete;
            }
        }
        else if (toDelete->left != nullptr && toDelete->right == nullptr)
        {
            if (toDelete->parent->left == toDelete)
            {
                toDelete->parent->left = toDelete->left;
                toDelete->left->parent = toDelete->parent;
                delete toDelete;
            }
            else
            {
                toDelete->parent->right = toDelete->left;
                toDelete->left->parent = toDelete->parent;
                delete toDelete;
            }
        }
        else if (toDelete->left == nullptr && toDelete->right != nullptr)
        {
            if (toDelete->parent->left == toDelete)
            {
                toDelete->parent->left = toDelete->right;
                toDelete->right->parent = toDelete->parent;
                delete toDelete;
            }
            else
            {
                toDelete->parent->right = toDelete->right;
                toDelete->right->parent = toDelete->parent;
                delete toDelete;
            }
        }
    }
};

#endif