#ifndef BINARYTREE_H
#define BINARYTREE_H

#include <list>

template <typename T>
class BinaryTree {
public:
    enum class InsertionMethod {
        LevelOrder,
        Sorted
    };

protected:

    struct Node {
        Node(T value);
        ~Node() = default;

        T m_value;
        Node* m_parent;
        Node* m_left;
        Node* m_right;
    };

public:

    class Position {
    public:
        Position(Node* node = nullptr);
        Position() = default;
        ~Position() = default;

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

        friend BinaryTree;
    };

public:

    BinaryTree(InsertionMethod insertionStyle);
    ~BinaryTree();

    int getSize() const;
    bool isEmpty() const;
    void insert(const T& element);
    std::list<T> preOrderList() const;
    std::list<T> postOrderList() const;
    std::list<T> inOrderList() const;
    std::list<T> levelOrderList() const;
    std::list<T> levelOrderList(int level) const;
    int height() const;
    int depth(int value);


private:

    void expandExternal(Position p, T leftValue, T rightValue);
    Position removeAboveExternal(Position p);
    Position root() const;
    Position addRoot(const T& element);
    Position addLeft(Position& position, const T& element);
    Position addRight(Position& position, const T& element);
    const T& set(Position& position, const T& newElement);
    void insertHelper(Node* current, Node* parent, const T& element);
    Position insertHelperLevelOrder(Position position, const T& element);
    const T& remove(Position& position);
    Position search(const Position& current, const int value) const;
    std::list<Position> preOrderPositions() const;
    void preOrderHelper(const Position& current, std::list<Position>& positions) const;
    std::list<Position> postOrderPositions() const;
    void postOrderHelper(const Position& current, std::list<Position>& positions) const;
    std::list<Position> inOrderPositions() const;
    void levelOrderHelper(const Position& parent, std::list<Position>& positions) const;
    std::list<Position> levelOrderPositions() const;
    void inOrderHelper(const Position& current, const Position& parent, std::list<Position>& positions) const;
    int heightHelper(const Position& current) const;
    int depthHelper(const Position& child) const;


private:
    Node* m_root;
    int m_size;
    InsertionMethod m_insStyle;
};

#endif // BINARYTREE_H
