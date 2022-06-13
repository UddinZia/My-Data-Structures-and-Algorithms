#ifndef AVL_TREE_H
#define AVL_TREE_H

#include <cstddef>
#include <iostream>

using std::cout, std::endl;

/*
    avl class header file
    class is simillar to the bst header file with mostly the same functions 
    includes new functions such as max, balance, and rotations that aid with 
    balancing the tree properly when inserting a node.
*/

template <typename Comparable>
class AVLTree {
private:
    struct avlNode
    {
        Comparable data;
        avlNode* left;
        avlNode* right;
        int height;

        avlNode(const Comparable& value, avlNode* left, avlNode* right, int height = 0)  //parameterized constructor. makes constructing a node in avl easier. 
        : data{value}, left{left}, right{right}, height{height} {} 
    };
    avlNode* root;

    //auxillary functions 
    /*
        recursive helper function for make_empty() and destructor
        will recursively delete all left and right nodes from given node untill nullptr
    */
    void destroy(avlNode* node)
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
    recursive helper function for public contains method
    contains function will go recursively left if value is less than current node or right if value is greater than current node
    untill the value is found or reaches nullptr(not found)
    */
    bool contains(const Comparable& value, avlNode *node) const
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

    //helper function for copy constructor
    //will recursively copy all nodes and allocate memory in bst until nullptr
    avlNode* copy(avlNode* node) const
    {   
       if (!node)
       {
           return nullptr;
       }
       else
       {
           return new avlNode{ node->data, copy(node->left), copy(node->right) };
       }
    }

    /*
     min value value in tree will be located in left most of bst
     recursively will traverse to left most node of bst until nullptr
     */
    avlNode* find_min(avlNode *node) const
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
        max value in tree will be located in right most node of avl
        recursively will traverse to right most node of avl until nullptr       
    */
    avlNode* find_max(avlNode* node) const
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

    // will return the height of a node otherwise return -1 
    int getHeight(avlNode* node)
    {
        if(!node)
        {
            return -1;
        }
        else
        {
            return node->height;
        }
    }

    /*
    function used for finding the max height between two nodes
    used for balancing the avl and performing appropiate rotations
    */
    int max(int x, int y)
    {
        if (x > y)
        {
            return x;
        }
        else
        {
            return y;
        }
    }

    // left child of node_a will act as a pivot and will be rotated and become parent
   void rotate_leftChild(avlNode*& node_a)
   {
       //rotation
       avlNode* node_b = node_a->left; //node_a's left child is saved as node_b
       node_a->left = node_b->right; //node_a's left child becomes node_b's right child
       node_b->right = node_a; // node_b becomes parent of node_a and is it's right child 

       //update height
       node_a->height = max(getHeight(node_a->left), getHeight(node_a->right)) + 1;
       node_b->height = max(getHeight(node_b->left), node_a->height) + 1;

       node_a = node_b;
   }

    /*
    right child of node_a will act as a pivot and will be rotated and become parent
    used as helper function in balanceTree function for balancing of avl
    */
   void rotate_RightChild(avlNode*& node_a)
   {
       avlNode* node_b = node_a->right; // node_a's right child is saved as node_b 
       node_a->right = node_b->left; // node_a's right child becomes node_b's left child
       node_b->left = node_a; // node_b becomes parent of node_a and is it's left child

       //update height
       node_a->height = max(getHeight(node_a->left), getHeight(node_a->right)) + 1;
       node_b->height = max(getHeight(node_b->left), node_a->height) + 1;

       node_a = node_b;
   }

   /*
   double left rotation 
   will make node_c the parent of node_a and node_b
   */
   void DoubleRotate_leftChild(avlNode*& node_c)
   {
       rotate_RightChild(node_c->left);
       rotate_leftChild(node_c);
   }

   /*
   double right rotation 
   will make node_c the parent of node_a and node_b
   */
   void DoubleRotate_RightChild(avlNode*& node_c)
   {
       rotate_leftChild(node_c->right);
       rotate_RightChild(node_c);
   }
   /*
    helper function used in recursive private insert function. used to balance tree
    */
    void balanceTree(avlNode*& node)
    {
        if (!node) // do nothing
        {
            return;
        }

        // if the balance factor is greater than 1. the avl needs to be balanced accordingly
    
        /*
        node that was inserted needs to be rotated left once or twice if height of left subtree is greater than right subtree
        */
        if ((getHeight(node->left) - getHeight(node->right)) > 1)
        {
            if(getHeight(node->left->left) >= getHeight(node->left->right))
            {
                rotate_leftChild(node);
            }
            else
            {
                DoubleRotate_leftChild(node);
            }
        }
        /*
        node that was inserted needs to be rotated right once or twice if height of right subtree is greater than left subtree
        */
        if ((getHeight(node->right) - getHeight(node->left)) > 1)
        {
            if(getHeight(node->right->right) >= getHeight(node->right->left))
            {
                rotate_RightChild(node);
            }
            else
            {
                DoubleRotate_RightChild(node);
            }
        }

        //update height of inserted node
        node->height = max(getHeight(node->left), getHeight(node->right)) + 1;
    }

    /*
    recursvive helper function for public insert method
    works like bst insertion but contains a call to balance function to balance tree if necessary

    */
    void insert(const Comparable& value, avlNode*& node)
    {
       if (this->contains(value)) // if value already exists
       {
           return;
       }

       if (!node) // if empty tree
       {
           node = new avlNode(value, nullptr, nullptr);
           root = node;
       }
       else 
       {
           if (value < node->data) // if value is less than current node assign left child to value otherwise recursively go further left down tree
           {
               if (!node->left) // if left child of node is null
               {
                   avlNode* tempLeft = new avlNode(value, nullptr, nullptr);
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
                   avlNode* tempRight = new avlNode(value, nullptr, nullptr);
                   node->right = tempRight;
               }
               else
               {
                   insert(value, node->right);
               }
           }
       }
       // after node is inserted rebalance tree accordingly
      balanceTree(node);
    }

    void remove(const Comparable& value, avlNode*& node)
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
            avlNode* temp = node; // temp points to node to be deleted
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

    /*
        tree is printed by reverse inOrder traversal (right - root - left)
        process right chil then print current node after given amount of spaces then process 
        left child until nullptr
    */
    void printTree(avlNode* node, int number_of_spaces) const
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
    AVLTree() : root{nullptr} {}
    AVLTree(const AVLTree& other) : root{nullptr}
    {
        root = copy(other.root);
    }
    ~AVLTree()
    {
        if (!is_empty())
        {
            destroy(root);
            root = nullptr;
        }
        return;
    }
    AVLTree& operator=(const AVLTree& other)
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
