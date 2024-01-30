#pragma once

#include <list>

template <typename T>
class MyBinaryTree {
public:
    enum class InsertionMethod {
        LevelOrder,
        Sorted
    };

private:

    class Node {
    public:
        Node(T value);
        ~Node();

        T m_value;
        Node* m_parent;
        Node* m_left;
        Node* m_right;
    };

public:

    class Position {
    public:
        Position(Node* node = nullptr);
        ~Position();

        T& operator*() const;
        bool operator==(const Position& other) const;
        bool operator!=(const Position& other) const;
        Position left() const;
        Position right() const;
        Position parent() const;
        bool isRoot() const;
        bool isExternal() const;
        bool isNull() const;

    private:
        Node* m_node;

        friend MyBinaryTree;
    };

public:

    MyBinaryTree(InsertionMethod insertionMethod = InsertionMethod::Sorted);
    ~MyBinaryTree();

    int getSize() const;
    bool isEmpty() const;
    void insert(const T& element);
    bool remove(const T& element);
    bool remove(const Position& element);
    bool contains(const T& element);
    std::list<T> preOrderList() const;
    std::list<T> postOrderList() const;
    std::list<T> inOrderList() const;
    std::list<T> levelOrderList() const;
    Position& editElement(T desiredElement);
    int height() const;
    int depth(const T& value);


private:

    Position root() const;
    Position addRoot(const T& element);
    Position addLeft(Position& position, const T& element);
    Position addRight(Position& position, const T& element);
    const T& set(Position& position, const T& newElement);
    void insertHelper(Node* current, Node* parent, const T& element);
    Position insertHelperLevelOrder(Position position, const T& element);
    Position search(const Position& current, const T value) const;
    std::list<Position> preOrderPositions() const;
    void preOrderHelper(const Position& current, std::list<Position>& positions) const;
    std::list<Position> postOrderPositions() const;
    void postOrderHelper(const Position& current, std::list<Position>& positions) const;
    std::list<Position> inOrderPositions() const;
    void levelOrderHelper(const Position& parent, std::list<Position>& positions) const;
    std::list<Position> levelOrderPositions() const;
    void inOrderHelper(const Position& current, const Position& parent, std::list<Position>& positions) const;
    int heightHelper(const Position& parent) const;
    int depthHelper(const Position& child) const;

    Node* m_root;
    int m_size;
    InsertionMethod m_insStyle;
};
