template <class T>
class Node {
private:
    int64_t m_id;
    T m_data;
public:
    Node(int64_t id, T data);
    bool operator==(const Node<T>& other) const;

    int64_t getId() const;
    T getData() const;

    template <class U>
    friend class Graph;
};