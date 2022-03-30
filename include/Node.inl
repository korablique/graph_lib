template<class T>
Node<T>::Node(int64_t id, T data): m_id(id), m_data(data) {}

template<class T>
bool Node<T>::operator==(const Node<T> &other) const {
    return m_id == other.m_id;
}

template<class T>
int64_t Node<T>::getId() const {
    return m_id;
}

template<class T>
T Node<T>::getData() const {
    return m_data;
}