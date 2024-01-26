#include "MyBinaryTree.h"
#include "Task.h"

#include <queue>
#include <stdexcept>

template class MyBinaryTree<Task>;


template<typename T>
MyBinaryTree<T>::Node::Node(T value)
    : m_value(value), m_parent(nullptr), m_left(nullptr), m_right(nullptr) {}

template<typename T>
MyBinaryTree<T>::Node::~Node() = default;

template<typename T>
MyBinaryTree<T>::Position::Position(Node* node) : m_node(node) {}


template<typename T>
MyBinaryTree<T>::Position::Position() = default;

template<typename T>
MyBinaryTree<T>::Position::~Position() = default;


template<typename T>
T& MyBinaryTree<T>::Position::operator*() const
{
    return m_node->m_value;
}

template<typename T>
bool MyBinaryTree<T>::Position::operator==(const Position& other) const
{
    return m_node == other.m_node;
}

template<typename T>
bool MyBinaryTree<T>::Position::operator!=(const Position& other) const
{
    return m_node != other.m_node;
}


template<typename T>
typename MyBinaryTree<T>::Position MyBinaryTree<T>::Position::left() const
{
    return Position(m_node->m_left);
}

template<typename T>
typename MyBinaryTree<T>::Position MyBinaryTree<T>::Position::right() const
{
    return Position(m_node->m_right);
}


template<typename T>
typename MyBinaryTree<T>::Position MyBinaryTree<T>::Position::parent() const
{
    return Position(m_node->m_parent);
}

template<typename T>
bool MyBinaryTree<T>::Position::isRoot() const
{
    return m_node->m_parent == nullptr;
}

template<typename T>
bool MyBinaryTree<T>::Position::isExternal() const
{
    if (m_node == nullptr)
        return true;
    return m_node->m_left == nullptr && m_node->m_right == nullptr;
}

template<typename T>
bool MyBinaryTree<T>::Position::isNull() const
{
    return (m_node == nullptr);
}

template<typename T>
MyBinaryTree<T>::MyBinaryTree(InsertionMethod insertionMethod)
{
    m_root = nullptr;
    m_size = 0;
    m_insStyle = insertionMethod;
}

template<typename T>
MyBinaryTree<T>::~MyBinaryTree()
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
int MyBinaryTree<T>::getSize() const
{
    return m_size;
}

template<typename T>
bool MyBinaryTree<T>::isEmpty() const
{
    return m_size == 0;
}

template<typename T>
void MyBinaryTree<T>::insert(const T& element)
{
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
bool MyBinaryTree<T>::remove(const T &element)
{
    Position target = search(m_root, element);

    if (target.isNull()) {
        return false;
    }


    if (target.isExternal()) {
        Node* parent = target.parent().m_node;
        if (parent->m_left == target.m_node) {
            delete parent->m_left;
            parent->m_left = nullptr;
        }
        else {
            delete parent->m_right;
            parent->m_right = nullptr;
        }

        m_size--;
    }

    else if (target.left().isNull() || target.right().isNull()) {
        Node* child = (target.left().isExternal()) ? target.right().m_node : target.left().m_node;
        Node* parent = target.parent().m_node;

        if (parent->m_left == target.m_node) {
            delete parent->m_left;
            parent->m_left = child;
        }
        else {
            delete parent->m_right;
            parent->m_right = child;
        }

        child->m_parent = parent;
        m_size--;
    }
    else {
        Position successor = target.right();
        while (!successor.left().isNull()) {
            successor = successor.left();
        }

        *target = *successor;

        Node* parent = successor.parent().m_node;
        if (parent->m_left == successor.m_node) {
            delete parent->m_left;
            parent->m_left = nullptr;
        }
        else {
            delete parent->m_right;
            parent->m_right = nullptr;
        }

        m_size--;
    }

    return true;
}

template<typename T>
std::list<T> MyBinaryTree<T>::preOrderList() const
{
    std::list<T> elements;
    std::list<Position> positions = preOrderPositions();
    for (const Position& position : positions) {
        elements.push_back(*position);
    }
    return elements;
}

template<typename T>
std::list<T> MyBinaryTree<T>::postOrderList() const
{
    std::list<T> elements;
    std::list<Position> positions = postOrderPositions();
    for (const Position& position : positions) {
        elements.push_back(*position);
    }
    return elements;
}

template<typename T>
std::list<T> MyBinaryTree<T>::inOrderList() const
{
    std::list<T> elements;
    std::list<Position> positions = inOrderPositions();
    for (const Position& position : positions) {
        elements.push_back(*position);
    }
    return elements;
}

template<typename T>
std::list<T> MyBinaryTree<T>::levelOrderList() const
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
int MyBinaryTree<T>::height() const
{
    return heightHelper(m_root);
}

template<typename T>
int MyBinaryTree<T>::depth(const T& value)
{
    Position target = search(m_root, value);
    int depth = depthHelper(target);
    return depth;
}

template<typename T>
typename MyBinaryTree<T>::Position MyBinaryTree<T>::root() const
{
    return Position(m_root);
}

template<typename T>
typename MyBinaryTree<T>::Position MyBinaryTree<T>::addRoot(const T& element)
{
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
typename MyBinaryTree<T>::Position MyBinaryTree<T>::addLeft(Position& position, const T& element)
{
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
typename MyBinaryTree<T>::Position MyBinaryTree<T>::addRight(Position& position, const T& element)
{
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
const T& MyBinaryTree<T>::set(Position& position, const T& newElement)
{
    T temp = *position;
    Node* target = position.m_node;
    target->m_value = newElement;
    return temp;
}

template<typename T>
void MyBinaryTree<T>::insertHelper(Node* current, Node* parent, const T& element)
{
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
typename MyBinaryTree<T>::Position MyBinaryTree<T>::insertHelperLevelOrder(Position position, const T& element)
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
typename MyBinaryTree<T>::Position MyBinaryTree<T>::search(const Position& current, const T value) const
{
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
typename std::list<typename MyBinaryTree<T>::Position> MyBinaryTree<T>::preOrderPositions() const
{
    std::list<Position> positions;
    preOrderHelper(m_root, positions);
    return positions;
}

template<typename T>
void MyBinaryTree<T>::preOrderHelper(const Position& current, std::list<Position>& positions) const
{
    positions.push_back(current);
    if (!current.left().isNull()) {
        preOrderHelper(current.left(), positions);
    }
    if (!current.right().isNull()) {
        preOrderHelper(current.right(), positions);
    }
}

template<typename T>
typename std::list<typename MyBinaryTree<T>::Position> MyBinaryTree<T>::postOrderPositions() const
{
    std::list<Position> positions;
    postOrderHelper(m_root, positions);
    return positions;
}

template<typename T>
void MyBinaryTree<T>::postOrderHelper(const Position& current, std::list<Position>& positions) const
{
    if (!current.left().isNull()) {
        postOrderHelper(current.left(), positions);
    }
    if (!current.right().isNull()) {
        postOrderHelper(current.right(), positions);
    }
    positions.push_back(current);
}

template<typename T>
typename std::list<typename MyBinaryTree<T>::Position> MyBinaryTree<T>::inOrderPositions() const
{
    std::list<Position> positions;
    inOrderHelper(m_root, nullptr, positions);
    return positions;
}

template<typename T>
void MyBinaryTree<T>::levelOrderHelper(const Position& parent, std::list<Position>& positions) const
{
    if (parent.isNull())
        return;

    positions.push_back(parent.left());
    positions.push_back(parent.right());

    levelOrderHelper(parent.left(), positions);
    levelOrderHelper(parent.right(), positions);
}

template<typename T>
std::list<typename MyBinaryTree<T>::Position> MyBinaryTree<T>::levelOrderPositions() const
{
    std::list<Position> positions;
    positions.push_back(m_root);
    levelOrderHelper(m_root, positions);
    return positions;
}

template<typename T>
void MyBinaryTree<T>::inOrderHelper(const Position& current, const Position& parent, std::list<Position>& positions) const
{
    if (!current.left().isNull()) {
        inOrderHelper(current.left(), parent, positions);
    }
    positions.push_back(current);
    if (!current.right().isNull()) {
        inOrderHelper(current.right(), parent, positions);
    }
}

template<typename T>
int MyBinaryTree<T>::heightHelper(const Position& parent) const
{
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
int MyBinaryTree<T>::depthHelper(const Position& child) const
{
    if (child.parent().isNull()) {
        return 0;
    }
    return 1 + depthHelper(child.parent());
}

