#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#include <cstddef>
#include <iostream>
using std::cout, std::endl;

/*
    bst class header file
    class contains a struct for a node object which contains the data of type Comparable, 
    a pointer to the left and right children and a parameterized constructor just to make declaring new nodes easier
    private portion of the bst class contains recursive helper functions that are used for the public methods. This 
    was done to make breaking down the implementation of the bst easier and also friendlier for the user
*/
template <typename Comparable>
class BinarySearchTree 
{
private:
    struct BinaryNode
    {
        Comparable data;
        BinaryNode* left;
        BinaryNode* right;

        BinaryNode(const Comparable& value, BinaryNode* left, BinaryNode* right) //parameterized constructor. makes constructing a node in bst easier. 
        : data{value}, left{left}, right{right} {} 

    };
    BinaryNode* root; 

    //auxillary functions 
    /*
        will recursively delete all left and right nodes from given node untill nullptr
    */
    void destroy(BinaryNode* node)
    {
        if (!node)
        {
            return;
        }

        destroy(node->left);
        destroy(node->right);
        delete node;
    }

    /*
        min value value in tree will be located in left most of bst
        recursively will traverse to left most node of bst until nullptr
    */
    BinaryNode* find_min(BinaryNode *node) const
    {
        if (!node)
        {
            return nullptr;
        }
        if (!node->left)
        {
            return node;
        }
        return find_min(node->left);
    }

    /*
        max value in tree will be located in right most node of bst
        recursively will traverse to right most node of bst until nullptr
    */
    BinaryNode* find_max(BinaryNode* node) const
    {
        if (!node)
        {
            return nullptr;
        }
        if (!node->right)
        {
            return node;
        }
        return find_max(node->right);
    }

    
    //node is passed by pointer reference so we can change the left and right pointers directly 
    void insert(const Comparable& value, BinaryNode*& node)
    {
        
       if (this->contains(value)) // if value already exists
       {
           return;
       }

       if (!node) // if empty tree
       {
           node = new BinaryNode(value, nullptr, nullptr);
           root = node;
       }
       else 
       {
           if (value < node->data) // if value is less than current node assign left child to value otherwise recursively go further left down tree
           {
               if (!node->left) // if left child of node is null
               {
                   BinaryNode* tempLeft = new BinaryNode(value, nullptr, nullptr);
                   node->left = tempLeft;
               }
               else //recursively go further left down tree
               {
                   insert(value, node->left);
               }
           }
           else
           {
               if (!node->right) // if value is greater than current node assign right child to value otherwise recursively go further right down tree
               {
                   BinaryNode* tempRight = new BinaryNode (value, nullptr, nullptr);
                   node->right = tempRight;
               }
               else
               {
                   insert(value, node->right);
               }
           }
       }
    }

    /*contains function will go recursively left if value is less than current node or right if value is greater than current node
    untill the value is found or reaches nullptr(not found)
    */
    bool contains(const Comparable& value, BinaryNode *node) const
    {
        if (!node) 
        {
            return false;
        }
        else if (node->data < value)
        {
            return contains(value, node->right);
        }
        else if (node->data > value)
        {
            return contains(value, node->left);
        }
        else
        {
            return true;
        }
    }

    /*
    remove helper function checks if node to be removed is a leaf, single child, does not exists, or has 2 children
    */
    void remove(const Comparable& value, BinaryNode*& node)
    {
        if (!node) // if value does not exist
        {
            return;
        }
        //recursively traverse left or right of bst 
        if (value < node->data) 
        { 
            remove(value, node->left);
        }
        else if(node->data < value)
        {
            remove(value, node->right);
        }
        else if (node->left != nullptr && node->right != nullptr) // delete node with two children (minimum of right child tree)
        {
            /*
                replace node to be deleted with smallest node found in right subtree using find_min()
                then delete smallest node from the right subtree
            */
            node->data = find_min(node->right)->data;
            remove(node->data, node->right);
        }
        else // delete node with one child
        {
            BinaryNode* temp = node;
            /*
            check if node to be deleted has left child
            if it doesn't then replace node to be deleted with it's right child otherwise
            if node to be deleted has only a left child then replace deleted node with its left child
            then delete node
            */
            if (node->left)
            {
                node = node->left;
            }
            else
            {
                node = node->right;
            }
            delete temp;
        }
    }

   //helper function for copy constructor
   //will recursively copy all nodes and allocate memory in bst until nullptr
    BinaryNode* copy(BinaryNode* node) const
    {   
       if (!node)
       {
           return nullptr;
       }
       else
       {
           return new BinaryNode{ node->data, copy(node->left), copy(node->right) };
       }
    }


    /*
        tree is printed by reverse inOrder traversal (right - root - left)
        process right chil then print current node after given amount of spaces then process 
        left child until nullptr
    */
    void printTree(BinaryNode* node, int number_of_spaces) const
    {
        if (!node)
        {
            return;
        }

        number_of_spaces += 2;

        printTree(node->right, number_of_spaces);

        for (int i = 2; i < number_of_spaces; i++)
        {
            cout << " ";
        }

        cout << node->data << endl;

        printTree(node->left, number_of_spaces);
    }


public:
    BinarySearchTree() : root{nullptr} {}

    BinarySearchTree(const BinarySearchTree& other) : root{nullptr}
    {
        root = copy(other.root);
    }

    ~BinarySearchTree()
    {
        if (!is_empty())
        {
            destroy(root);
            root = nullptr;
        }
        return;
    } 

    BinarySearchTree& operator=(const BinarySearchTree& other) 
    {
        
       if (this == &other) // check for self assignment
       {
           return *this;
       }
       
        this->make_empty();
        root = copy(other.root);
        return *this;
    } 

    bool contains(const Comparable& value) const
    {
        return contains(value, root);
    }

    void insert(const Comparable& value)
    {
        insert(value, root);
    }

    void remove(const Comparable& value)
    {
        remove(value, root);
    }

    const Comparable& find_min() const
    {
        if (!is_empty())
        {
            return find_min(root)->data;
        }
        else
        {
            throw std::invalid_argument("tree is empty");
        }
    }

    const Comparable& find_max() const
    {
        if (!is_empty())
        {
            return find_max(root)->data;
        }
        else
        {
            throw std::invalid_argument("tree is empty");
        }
    }


    void print_tree(std::ostream& os=std::cout) const
    {
        if (root == nullptr)
        {
            os << "<empty>\n";
        }
        else
        {
            printTree(root, 0);
        }
    }
  

    bool is_empty() const
    {
        return (root == nullptr);
    }

    void make_empty()
    {
        if (!is_empty())
        {
            destroy(root);
            root = nullptr;
        }
    }
};

#endif
