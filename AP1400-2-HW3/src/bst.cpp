#include "bst.h"

BST::Node::Node(int value, Node *left, Node *right) : value(value), left(left), right(right) {}

BST::Node::Node(const Node &node)
{
    this->value = node.value;
    this->left = node.left;
    this->right = node.right;
}

BST::Node::Node()
{
    this->value = 0;
    this->left = nullptr;
    this->right = nullptr;
}

ostream &operator<<(ostream &os, const BST::Node &node)
{
    os << &node << "        => "
       << "value:" << node.value << "        "
       << "left:" << &(node.left) << "        "
       << "right:" << &(node.right) << '\n';
    return os;
}

bool operator>(int num, const BST::Node &node)
{
    return num > node.value;
}

bool operator>(const BST::Node &node, int num)
{
    return node.value > num;
}
bool operator>=(int num, const BST::Node &node)
{
    return num >= node.value;
}

bool operator>=(const BST::Node &node, int num)
{
    return node.value >= num;
}

bool operator==(int num, const BST::Node &node)
{
    return num == node.value;
}

bool operator==(const BST::Node &node, int num)
{
    return num == node.value;
}

bool operator<(int num, const BST::Node &node)
{
    return num < node.value;
}

bool operator<(const BST::Node &node, int num)
{
    return node.value < num;
}

bool operator<=(int num, const BST::Node &node)
{
    return num <= node.value;
}

bool operator<=(const BST::Node &node, int num)
{
    return node.value <= num;
}

BST::BST(BST &&bst)
{
    this->root = std::move(bst.root);
}

BST::BST()
{
    this->root = nullptr;
}

BST::BST(const BST &bst)
{
    this->root = bst.root;
}

// BST::~BST() {
//     std::vector<Node*> nodes;
//     bfs([&nodes](BST::Node*& node) { nodes.push_back(node); });
//     for (auto& node : nodes) delete node;
// }

BST::Node *&BST::get_root()
{
    return this->root;
}

bool BST::add_node(int value)
{
    if (this->root == nullptr)
    {
        this->root = new Node(value, nullptr, nullptr);
        return true;
    }
    Node *node = this->root;
    bool bigger = false;
    Node *tempNode = nullptr;
    while (node != nullptr)
    {
        tempNode = node;
        if (value > node->value)
        {
            bigger = true;
            if (node->right == nullptr)
            {
                break;
            }
            node = node->right;
        }
        else if (value < node->value)
        {
            bigger = false;
            if (node->left == nullptr)
            {
                break;
            }
            node = node->left;
        }
        else
        {
            return false;
        }
    }
    if (bigger)
    {
        tempNode->right = new Node(value, nullptr, nullptr);
    }
    else
    {
        tempNode->left = new Node(value, nullptr, nullptr);
    }
    return true;
}
void BST::bfs(std::function<void(Node *&node)> func) const
{
    if (this->root == nullptr)
    {
        return;
    }
    queue<Node *> q;
    q.push(this->root);
    while (!q.empty())
    {
        Node *node = q.front();
        func(node);
        if (node->left != nullptr)
        {
            q.push(node->left);
        }
        if (node->right != nullptr)
        {
            q.push(node->right);
        }
        q.pop();
    }
    return;
}

size_t BST::length()
{
    std::vector<Node *> nodes;
    this->bfs([&nodes](BST::Node *&node)
              { nodes.push_back(node); });
    return nodes.size();
}

void printNode(BST::Node *&node)
{
    std::cout << node << std::endl;
}

ostream &operator<<(ostream &os, const BST &bst)
{
    bst.bfs([&os](BST::Node *&node)
            { os << node->value << endl; });
    return os;
}

BST::Node **BST::find_node(int value)
{
    Node **nodePtr = &this->root;
    while (*nodePtr != nullptr && (*nodePtr)->value != value)
    {
        if (value > (*nodePtr)->value)
        {
            nodePtr = &(*nodePtr)->right;
        }
        else if (value < (*nodePtr)->value)
        {
            nodePtr = &(*nodePtr)->left;
        }
    }
    if (*nodePtr == nullptr)
    {
        return nullptr; // Value not found, return nullptr
    }

    return nodePtr;
}

BST::Node **BST::find_parrent(int value)
{
    if (this->find_node(value) == nullptr)
    {
        return nullptr;
    }
    Node **nodePtr = &this->root;
    if (this->root->value == value)
    {
        return nodePtr;
    }
    while (*nodePtr != nullptr)
    {
        if ((*nodePtr)->left != nullptr && (*nodePtr)->left->value == value)
        {
            return nodePtr;
        }
        if ((*nodePtr)->right != nullptr && (*nodePtr)->right->value == value)
        {
            return nodePtr;
        }

        if (value > (*nodePtr)->value)
        {
            nodePtr = &(*nodePtr)->right;
        }
        else if (value < (*nodePtr)->value)
        {
            nodePtr = &(*nodePtr)->left;
        }
    }
    return nullptr;
}

BST::Node **BST::find_successor(int value)
{
    auto b = find_node(value);

    if ((*b) == nullptr || (*b)->left == nullptr)
    {
        return nullptr;
    }
    auto p = (*b)->left;
    while (p->right != nullptr)
    {
        p = p->right;
    }
    auto res{new Node *{p}};

    return res;
}

bool BST::delete_node(int value)
{
    BST::Node **node{this->find_node(value)};

    if (node == nullptr)
    {
        return false;
    }
    BST::Node **parent{this->find_parrent(value)};
    auto successor = find_successor(value);

    // Leaf
    if ((*node)->left == nullptr && (*node)->right == nullptr)
    {
        // delete *node;
        (*node) = nullptr;
        if ((*parent)->value > value)
        {
            (*parent)->left = nullptr;
        }
        else
        {
            (*parent)->right = nullptr;
        }
        return true;
    }
    // One child
    else if ((*node)->left == nullptr || (*node)->right == nullptr)
    {
        if ((*parent)->value > value)
        {
            (*parent)->left = (*node)->left ? (*node)->left : (*node)->right;
        }
        else
        {
            (*parent)->right = (*node)->left ? (*node)->left : (*node)->right;
        }
        return true;
    }

    auto new_node = new Node{(*successor)->value, (*node)->left, (*node)->right};

    auto sParent = find_parrent((*successor)->value);

    // root case
    if (*node == get_root())
    {
        get_root() = new_node;
    }
    else
    {
        if ((*parent)->value > value)
        {
            (*parent)->left = new_node;
        }
        else
        {
            (*parent)->right = new_node;
        }
    }

    if (*sParent != nullptr)
    {
        if ((*sParent)->value > (*successor)->value)
        {
            (*sParent)->left = nullptr;
        }
        else
        {
            (*sParent)->right = nullptr;
        }
    }

    return true;
}

BST& BST::operator=(BST&& bst) noexcept{
    get_root() = std::move(bst.root);
    return *this;
}

//Deep copy required
BST::Node* copyTree(BST::Node* root) {
    if (root == nullptr)
        return nullptr;
    BST::Node* newRoot = new BST::Node(root->value, nullptr, nullptr);
    newRoot->left = copyTree(root->left);
    newRoot->right = copyTree(root->right);
    return newRoot;
}

BST& BST::operator=(const BST& bst) noexcept{
    this->root = copyTree(bst.root);
    return *this;
}
//++bst
BST& BST::operator++() {
    auto plus = [](BST::Node*& node) { node->value += 1; };
    bfs(plus);
    return *this;
}

BST BST::operator++(int) {
    BST b = *this;
    ++*this;
    return b;
}

BST::BST(std::initializer_list<int> list) {
    this->root = nullptr;
    if (list.size() == 0) {
    } else {
        for (auto num : list) {
            add_node(num);
        }
    }
}

// BST::~BST() {
//     std::vector<Node*> nodes;
//     bfs([&nodes](BST::Node*& node) { nodes.push_back(node); });
//     for (auto& node : nodes) delete node;
// }