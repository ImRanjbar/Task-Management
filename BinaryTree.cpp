#include "BinaryTree.h"

#include <queue>
#include <stdexcept>

template<typename T>
BinaryTree<T>::Node::Node(T value)  : m_value(value), m_parent(nullptr), m_left(nullptr), m_right(nullptr) {}

template<typename T>
BinaryTree<T>::Position::Position(Node *node) : m_node(node) {}


template<typename T>
T &BinaryTree<T>::Position::operator*() const
{
    return m_node->m_value;
}

template<typename T>
bool BinaryTree<T>::Position::operator==(const Position &other) const
{
    return m_node == other.m_node;
}

template<typename T>
bool BinaryTree<T>::Position::operator!=(const Position &other) const
{
    return m_node != other.m_node;
}

template<typename T>
typename BinaryTree<T>::Position BinaryTree<T>::Position::left() const
{
    return Position(m_node->m_left);
}

template<typename T>
typename BinaryTree<T>::Position BinaryTree<T>::Position::right() const
{
    return Position(m_node->m_right);
}

template<typename T>
typename BinaryTree<T>::Position BinaryTree<T>::Position::parent() const
{
    return Position(m_node->m_parent);
}

template<typename T>
bool BinaryTree<T>::Position::isRoot() const
{
    return m_node->m_parent == nullptr;
}

template<typename T>
bool BinaryTree<T>::Position::isExternal() const
{
    if (m_node == nullptr)
        return true;
    return m_node->m_left == nullptr && m_node->m_right == nullptr;
}

template<typename T>
bool BinaryTree<T>::Position::isNull() const
{
    return (m_node == nullptr);
}

template<typename T>
BinaryTree<T>::BinaryTree(InsertionMethod insertionStyle)
    : m_root(nullptr), m_size(0), m_insStyle(insertionStyle) {}

template<typename T>
BinaryTree<T>::~BinaryTree()
{
    if (m_root != nullptr) {
        std::list<Position> postOrderNodes = postOrderPositions();

        for (const Position& pos : postOrderNodes) {
            delete pos.m_node;
        }

        m_root = nullptr;
        m_size = 0;
    }
}

template<typename T>
int BinaryTree<T>::getSize() const {
    return m_size;
}

template<typename T>
bool BinaryTree<T>::isEmpty() const {
    return m_size == 0;
}

template<typename T>
void BinaryTree<T>::insert(const T& element) {
    if (m_root == nullptr) {
        addRoot(element);
    }
    else {
        switch (m_insStyle)
        {
        case InsertionMethod::LevelOrder:
            insertHelperLevelOrder(Position(m_root), element);
            break;
        case InsertionMethod::Sorted:
            insertHelper(m_root, nullptr, element);
            break;
        default:
            break;
        }
    }
}

template<typename T>
std::list<T> BinaryTree<T>::preOrderList() const {
    std::list<T> elements;
    std::list<Position> positions = preOrderPositions();
    for (const Position& position : positions) {
        elements.push_back(*position);
    }
    return elements;
}

template<typename T>
std::list<T> BinaryTree<T>::postOrderList() const {
    std::list<T> elements;
    std::list<Position> positions = postOrderPositions();
    for (const Position& position : positions) {
        elements.push_back(*position);
    }
    return elements;
}

template<typename T>
std::list<T> BinaryTree<T>::inOrderList() const {
    std::list<T> elements;
    std::list<Position> positions = inOrderPositions();
    for (const Position& position : positions) {
        elements.push_back(*position);
    }
    return elements;
}

template<typename T>
inline std::list<T> BinaryTree<T>::levelOrderList() const
{
    std::list<T> elements;
    std::list<Position> positions = levelOrderPositions();
    for (const Position& position : positions) {
        if (!position.isNull())
            elements.push_back(*position);
    }

    return elements;
}

template<typename T>
inline std::list<T> BinaryTree<T>::levelOrderList(int level) const
{
    return std::list<T>();
}

template<typename T>
int BinaryTree<T>::height() const {
    return heightHelper(m_root);
}

template<typename T>
int BinaryTree<T>::depth(int value) {
    Position target = search(m_root, value);
    int depth = depthHelper(target);
    return depth;
}

template<typename T>
void BinaryTree<T>::expandExternal(Position p, T leftValue, T rightValue) {
    Node* node = p.m_node;
    node->m_left = new Node(leftValue);
    node->m_right = new Node(rightValue);
    node->m_left->m_parent = node;
    node->m_right->m_parent = node;
    m_size += 2;
}

template<typename T>
typename BinaryTree<T>::Position BinaryTree<T>::removeAboveExternal(Position p) {
    Node* node = p.m_node;
    Node* parent = node->m_parent;
    Node* sibling = (node == parent->m_left) ? parent->m_right : parent->m_left;

    if (parent == m_root) {
        m_root = sibling;
        sibling->m_parent = nullptr;
    }
    else {
        Node* grandParent = parent->m_parent;
        if (parent == grandParent->m_left) {
            grandParent->m_left = sibling;
        }
        else {
            grandParent->m_right = sibling;
        }
        sibling->m_parent = grandParent;
    }

    delete node;
    delete parent;
    m_size -= 2;
    return Position(sibling);
}

template<typename T>
typename BinaryTree<T>::Position BinaryTree<T>::root() const {
    return Position(m_root);
}

template<typename T>
typename BinaryTree<T>::Position BinaryTree<T>::addRoot(const T& element) {
    if (m_size == 0) {
        Node* root = new Node(element);
        m_root = root;
        m_size++;
        return Position(root);
    }
    else {
        throw std::runtime_error("Add root failed");
    }
}

template<typename T>
typename BinaryTree<T>::Position BinaryTree<T>::addLeft(Position& position, const T& element) {
    Node* parent = position.m_node;

    if (parent->m_left != nullptr) {
        throw std::runtime_error("addLeft Failed");
    }
    else {
        Node* newNode = new Node(element);
        newNode->m_parent = parent;
        parent->m_left = newNode;
        m_size++;
        return Position(newNode);
    }
}

template<typename T>
typename BinaryTree<T>::Position BinaryTree<T>::addRight(Position& position, const T& element) {
    Node* parent = position.m_node;

    if (parent->m_right != nullptr) {
        throw std::runtime_error("addRight Failed");
    }
    else {
        Node* newNode = new Node(element);
        newNode->m_parent = parent;
        parent->m_right = newNode;
        m_size++;
        return Position(newNode);
    }
}

template<typename T>
const T& BinaryTree<T>::set(Position& position, const T& newElement) {
    T temp = *position;
    Node* target = position.getNode();
    target->m_value = newElement;
    return temp;
}

template<typename T>
void BinaryTree<T>::insertHelper(Node* current, Node* parent, const T& element) {
    if (current == nullptr) {
        if (element < parent->m_value) {
            Position posParent = Position(parent);
            addLeft(posParent, element);
            return;
        }
        else {
            Position posParent = Position(parent);
            addRight(posParent, element);
            return;
        }
    }

    if (element < current->m_value) {
        insertHelper(current->m_left, current, element);
    }
    else {
        insertHelper(current->m_right, current, element);
    }
}

template<typename T>
inline typename BinaryTree<T>::Position BinaryTree<T>::insertHelperLevelOrder(Position position, const T& element)
{
    if (position.isNull()) {
        position = addRoot(element);
    }
    else {
        std::queue<Position> q;
        q.push(position);

        while (!q.empty()) {
            Position temp = q.front();
            q.pop();

            if (!temp.left().isNull()) {
                q.push(temp.left());
            }
            else {
                addLeft(temp, element);
                return position;
            }

            if (!temp.right().isNull()) {
                q.push(temp.right());
            }
            else {
                addRight(temp, element);
                return position;
            }
        }
    }

    return position;
}

template<typename T>
const T& BinaryTree<T>::remove(Position& position) {
    throw std::runtime_error("Remove not implemented");
}

template<typename T>
typename BinaryTree<T>::Position BinaryTree<T>::search(const Position& current, const int value) const {
    if (current.isNull()) {
        throw std::runtime_error("search Failed");
    }

    if (*current == value) {
        return current;
    }
    else if (value < *current) {
        return search(current.left(), value);
    }
    else if (value > *current) {
        return search(current.right(), value);
    }
    else {
        throw std::runtime_error("search Failed");
    }
}


template<typename T>
std::list<typename BinaryTree<T>::Position> BinaryTree<T>::preOrderPositions() const {
    std::list<Position> positions;
    preOrderHelper(m_root, positions);
    return positions;
}

template<typename T>
void BinaryTree<T>::preOrderHelper(const Position& current, std::list<Position>& positions) const {
    positions.push_back(current);
    if (!current.left().isNull()) {
        preOrderHelper(current.left(), positions);
    }
    if (!current.right().isNull()) {
        preOrderHelper(current.right(), positions);
    }
}

template<typename T>
std::list<typename BinaryTree<T>::Position> BinaryTree<T>::postOrderPositions() const {
    std::list<Position> positions;
    postOrderHelper(m_root, positions);
    return positions;
}

template<typename T>
void BinaryTree<T>::postOrderHelper(const Position& current, std::list<Position>& positions) const {
    if (!current.left().isNull()) {
        postOrderHelper(current.left(), positions);
    }
    if (!current.right().isNull()) {
        postOrderHelper(current.right(), positions);
    }
    positions.push_back(current);
}

template<typename T>
std::list<typename BinaryTree<T>::Position> BinaryTree<T>::inOrderPositions() const {
    std::list<Position> positions;
    inOrderHelper(m_root, nullptr, positions);
    return positions;
}

template<typename T>
inline void BinaryTree<T>::levelOrderHelper(const Position& parent, std::list<Position>& positions) const
{
    if (parent.isNull())
        return;

    positions.push_back(parent.left());
    positions.push_back(parent.right());

    levelOrderHelper(parent.left(), positions);
    levelOrderHelper(parent.right(), positions);
}

template<typename T>
inline std::list<typename BinaryTree<T>::Position> BinaryTree<T>::levelOrderPositions() const
{
    std::list<Position> positions;
    positions.push_back(m_root);
    levelOrderHelper(m_root, positions);
    return positions;
}

template<typename T>
void BinaryTree<T>::inOrderHelper(const Position& subTree, const Position& parent, std::list<Position>& positions) const {
    if (!subTree.left().isNull()) {
        inOrderHelper(subTree.left(), parent, positions);
    }
    positions.push_back(subTree);
    if (!subTree.right().isNull()) {
        inOrderHelper(subTree.right(), parent, positions);
    }
}

template<typename T>
int BinaryTree<T>::heightHelper(const Position& parent) const {
    int height = 0;
    if (!parent.left().isNull()) {
        height = std::max(height, 1 + heightHelper(parent.left()));
    }
    if (!parent.right().isNull()) {
        height = std::max(height, 1 + heightHelper(parent.right()));
    }
    return height;
}

template<typename T>
int BinaryTree<T>::depthHelper(const Position& child) const {
    if (child.parent().isNull()) {
        return 0;
    }
    return 1 + depthHelper(child.parent());
}
