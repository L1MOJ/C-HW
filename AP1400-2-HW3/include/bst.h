#ifndef BST_H
#define BST_H

#include <cstdio>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <ostream>
#include <queue>
#include <stack>

using std::cout;
using std::endl;
using std::ostream;
using std::queue;
using std::stack;

class BST
{
public:

    class Node
    {
    public:
	    Node(int value, Node* left, Node* right);
	    Node();
	    Node(const Node& node);

	    int value;
	    Node* left;
	    Node* right;

        friend ostream& operator<<(ostream& os, const BST::Node& node);
        friend bool operator>(int num, const BST::Node& node);
        friend bool operator>(const BST::Node& node, int num);
        friend bool operator==(int num, const BST::Node& node);
        friend bool operator==(const BST::Node& node, int num);
        friend bool operator<(int num, const BST::Node& node);
        friend bool operator<(const BST::Node& node, int num);
        friend bool operator>=(int num, const BST::Node& node);
        friend bool operator>=(const BST::Node& node, int num);
        friend bool operator<=(int num, const BST::Node& node);
        friend bool operator<=(const BST::Node& node, int num);

    };

    BST();
    BST(const BST& bst);
    BST(BST&& bst);
    BST(std::initializer_list<int> list);
    Node*& get_root();
    void bfs(std::function<void(Node*& node)> func) const;
    size_t length();
    bool add_node(int value);
    Node** find_node(int value);
    Node** find_parrent(int value);
    Node** find_successor(int value);
    bool delete_node(int value);
    // ~BST();
    friend ostream& operator<<(ostream& os, const BST& bst);
    BST& operator=(BST&& bst) noexcept;
    BST& operator=(const BST& bst) noexcept;
    BST& operator++();
    BST operator++(int);
private:
    Node* root;
};



#endif //BST_H