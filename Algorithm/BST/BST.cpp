// BST.cpp 
#include <iostream>

struct node
{
    int data;
    node* left;
    node* right;
};

struct bst
{
    node* root = nullptr;

    node* find(int value)
    {
        return find_impl(root, value);
    }

    void insert(int value)
    {
        if (!root) root = new node{ value, nullptr, nullptr };
        else
            insert_impl(root, value);
    }

    void inorder()
    {
        inorder_impl(root);
    }

    // find successor
    node* successor(node* start)
    {
        node* current = start->right;
        while (current && current->left)
            current = current->left;
        return current;
    }

    void delete_value(int value)
    {
        root = delete_impl(root, value);
    }

private:
    node* find_impl(node* root, int value)
    {
        // if current node is nullptr, then return nullptr
        if (!root) return nullptr;

        if (root->data == value)
        {
            std::cout << value << " was found. " << std::endl;
            return root;
        }

        if (root->data < value)
            return find_impl(root->left, value);

        return find_impl(root->right, value);
    }

    void insert_impl(node* root, int value)
    {
        if (root->data > value)
        {
            // if the incoming node has no left, insert to left
            if (!root->left)
                root->left = new node{ value, nullptr, nullptr };
            else
                insert_impl(root->left, value);
        }
        else
        {
            if (!root->right)
                root->right = new node{ value, nullptr, nullptr };
            else
                insert_impl(root->right, value);
        }
    }

    void inorder_impl(node* start)
    {
        if (!start) return;
        inorder_impl(start->left);
        std::cout << start->data << " ";
        inorder_impl(start->right);
    }

    // return node* (tree) after element is deleted
    node* delete_impl(node* start, int value)
    {
        if (!start) return nullptr;
        // if the node*'s data is greater than value, then left
        if (start->data > value)
            start->left = delete_impl(start->left, value);
        else if(start->data < value)
            start->right = delete_impl(start->right, value);
        else
        {
            // if the root is the one we would like to delete
            if (!start->left) // if there is no children, or left node is empty
            {
                node* temp = start->right;
                delete start;
                return temp;
            }

            if (!start->right)
            {
                node* temp = start->left;
                delete start;
                return temp;
            }

            node* successorNode = successor(start);
            // Data Copy
            start->data = successorNode->data;
            start->right = delete_impl(start->left, successorNode->data);
        }

        return start;
    }
};

int main()
{
    bst tree;
    tree.insert(12);
    tree.insert(10);
    tree.insert(20);
    tree.insert(8);
    tree.insert(11);
    tree.insert(15);
    tree.insert(28);
    tree.insert(4);
    tree.insert(2);

    std::cout << "In order" << std::endl;
    tree.inorder();
    std::cout << std::endl;

    tree.delete_value(12);
    // delete 12 and in odrder
    tree.inorder();
    std::cout << std::endl;

    if (tree.find(12))
        std::cout << " element 12 is in the tree " << std::endl;
    else
        std::cout << " element 12 is not in the tree " << std::endl;

    return 0;
}