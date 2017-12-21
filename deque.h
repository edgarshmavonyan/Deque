#include <cstring>
#include <iostream>
#include <vector>
#include <iterator>
#include <stddef.h>
#include <assert.h>
#include <type_traits>

#pragma once


template <class deque, class T>
class base_iterator : public std::iterator<std::random_access_iterator_tag, T> {

public:

    typedef T value_type;
    typedef ptrdiff_t difference_type;
    typedef T* pointer;
    typedef T& reference;
    typedef std::random_access_iterator_tag iterator_category;

    explicit base_iterator(deque& rhs) : deq_(&rhs), index_(ptrdiff_t(0)) {}
    base_iterator(deque& rhs, difference_type index) : deq_(&rhs), index_(index) {}
    base_iterator(const base_iterator &rhs) : deq_(rhs.deq_), index_(rhs.index_) {}

    inline reference operator*() { return deq_->operator[](index_); }
    inline reference operator*() const { return deq_->operator[](index_); }
    inline pointer operator->() const { return &(operator*()); }

    base_iterator& operator++() {
        index_++;
        return *this;
    }

    base_iterator operator++(int) {
        auto temp(*this);

        operator++();

        return temp;
    }

    base_iterator& operator--() {
        index_--;
        return *this;
    }

    base_iterator operator--(int) {
        auto temp(*this);

        operator--();

        return temp;
    }

    difference_type operator-(const base_iterator& other) const {
        return index_ - other.index_;
    }

    base_iterator& operator+=(difference_type n) {
        index_ += n;

        return *this;
    }

    base_iterator operator+(difference_type n) const {
        auto temp(*this);
        temp += n;
        return temp;
    }

    friend base_iterator operator+(difference_type n, base_iterator it) {
        it += n;
        return it;
    }

    base_iterator& operator-=(difference_type n) {
        index_ -= n;

        return *this;
    }

    base_iterator operator-(difference_type n) const {
        auto temp(*this);
        temp -= n;
        return temp;
    }

    reference operator[](difference_type n) const {
        return *(*this + n);
    }

    bool friend operator==(const base_iterator& first, const base_iterator& second) {
        return (first.deq_ == second.deq_ && first.index_ == second.index_);
    }

    bool friend operator!=(const base_iterator& first, const base_iterator& second) {
        return !(first == second);
    }

    bool friend operator<(const base_iterator& first, const base_iterator& second) {
        return (second - first > 0);
    }

    bool friend operator<=(const base_iterator& first, const base_iterator& second) {
        return first < second || first == second;
    }

    bool friend operator>(const base_iterator& first, const base_iterator& second) {
        return !(first <= second);
    }

    bool friend operator>=(const base_iterator& first, const base_iterator& second) {
        return !(first < second);
    }

protected:
    deque* deq_;
    difference_type index_;
};


template<typename T>
class Deque {
private:

    T* data_;
    T* head_;
    T* tail_;
    size_t size_;
    size_t capacity_;

public:

//    using iterator = base_iterator<T, Deque>;
    typedef base_iterator<Deque, T> iterator;

    typedef base_iterator<const Deque, const T > const_iterator;


    typedef std::reverse_iterator<base_iterator<Deque, T > > reverse_iterator;

    typedef std::reverse_iterator<base_iterator<const Deque, const T > > const_reverse_iterator;

    Deque() : data_(nullptr), head_(nullptr), tail_(nullptr), size_(0), capacity_(0) {}

    Deque(const Deque& other);

//    explicit Deque(const size_t& size) : data_(new T[size]), head_(data_), tail_(data_),  size_(0), capacity_(size) {}

    ~Deque() {
        delete[] data_;
    }

    void increaseSize();

    void decreaseSize();

    inline T& back() {
//        return operator[](size_ - 1);
        return *tail_;
    }

    inline const T& back() const {
//        return operator[](size_ - 1);
        return *tail_;

    }

    inline T& front() {
        return *head_;
    }

    inline const T& front() const {
        return *head_;
    }

    T& operator[](int i) {

        if (head_ + i < data_ + capacity_)
            return *(head_ + i);

        return *(head_ + i - capacity_);
    }

    const T& operator[](int i) const {

        if (head_ + i < data_ + capacity_)
            return *(head_ + i);

        return *(head_ + i - capacity_);
    }

    bool empty() const {
        return size() == 0;
    }

    size_t size() const;

    void push_back(const T& value);

    void push_front(const T& value);

    void pop_back();

    void pop_front();

    const_iterator cbegin() const {
        return const_iterator(*this, ptrdiff_t(0));
    }

    const_iterator begin() const {
        return const_iterator(*this, ptrdiff_t(0));
    }

    iterator begin() {
        return iterator(*this, ptrdiff_t(0));
    }

    const_iterator cend() const {
        return const_iterator(*this, ptrdiff_t(size_));
    }

    const_iterator end() const {
        return const_iterator(*this, ptrdiff_t(size_));
    }

    iterator end() {
        return iterator(*this, ptrdiff_t(size_));
    }

    std::reverse_iterator<const_iterator> crbegin() const {
        return std::reverse_iterator<const_iterator>(const_iterator(*this, ptrdiff_t(size_)));
    }

    std::reverse_iterator<iterator> rbegin() {
        return std::reverse_iterator<iterator>(iterator(*this, ptrdiff_t(size_)));
    }

    std::reverse_iterator<const_iterator> rbegin() const {
        return std::reverse_iterator<const_iterator>(const_iterator(*this, ptrdiff_t(size_)));
    }

    std::reverse_iterator<iterator> rend() {
        return std::reverse_iterator<iterator>(iterator(*this, ptrdiff_t(0)));
    }

    std::reverse_iterator<const_iterator> rend() const {
        return std::reverse_iterator<const_iterator>(const_iterator(*this, ptrdiff_t(0)));
    }

    std::reverse_iterator<const_iterator> crend() const {
        return std::reverse_iterator<const_iterator>(const_iterator(*this, ptrdiff_t(0)));
    }

};

template<typename T>
Deque<T>::Deque(const Deque& other) : data_(new T[other.capacity_]), head_((other.head_ - other.data_) + data_),
                                   tail_((other.tail_ - other.data_) + data_), size_(other.size_), capacity_(other.capacity_) {
    memcpy(data_, other.data_, sizeof(T) * other.capacity_);
}

template<typename T>
size_t Deque<T>::size() const {
    return size_;
}

template<typename T>
void Deque<T>::push_back(const T& value) {

    if (data_ == nullptr) {
        data_ = new T[4];
        tail_ = head_ = data_;
        capacity_ = 4;
        *tail_ = value;
        size_ = 1;
        return;
    }

    if (size() == capacity_)
        increaseSize();

    if (tail_ == data_ + capacity_ - 1)
        tail_ = data_;
    else
        tail_++;

    *tail_ = value;
    ++size_;
}

template<typename T>
void Deque<T>::increaseSize() {
    auto data = new T[2 * capacity_];

    if (head_ <= tail_)
        memcpy(data, head_, sizeof(T) * (tail_ - head_ + 1));
    else {
        size_t firstHalf = data_ + capacity_ - head_;
        size_t secondHalf = tail_ - data_ + 1;
        memcpy(data, head_, sizeof(T) * firstHalf);
        memcpy(data + firstHalf, data_, sizeof(T) * secondHalf);
    }

    delete[] data_;
    head_ = data_ = data;
    tail_ = data_ + capacity_ - 1;
    capacity_ *= 2;
}

template<typename T>
void Deque<T>::decreaseSize() {
    auto data = new T[capacity_ / 2];


    if (head_ <= tail_)
        memcpy(data, head_, sizeof(T) * (tail_ - head_ + 1));
    else {
        size_t firstHalf = data_ + capacity_ - head_;
        size_t secondHalf = tail_ - data_ + 1;
        memcpy(data, head_, sizeof(T) * firstHalf);
        memcpy(data + firstHalf, data_, sizeof(T) * secondHalf);
    }
    /*
    int i = 0;
    for (auto it = begin(); it != end(); ++it, ++i)
        *(data + i) = *it;
*/
    delete[] data_;
    head_ = data_ = data;
    tail_ = data_ + capacity_/4 - 1;
    capacity_ /= 2;

}

template<typename T>
void Deque<T>::push_front(const T& value) {

    if (data_ == nullptr) {
        data_ = new T[4];
        tail_ = head_ = data_;
        capacity_ = 4;
        *head_ = value;
        size_ = 1;
        return;
    }

    if (size() == capacity_)
        increaseSize();

    if (head_ == data_)
        head_ = data_ + capacity_ - 1;
    else
        head_--;

    *head_ = value;

    ++size_;
}

template<typename T>
void Deque<T>::pop_back() {

    if (tail_ == data_)
        tail_ = data_ + capacity_ - 1;
    else
        tail_--;

    --size_;

    if (capacity_ != 2 && capacity_ != 1 && capacity_ != 8 && capacity_ != 4 && size() == capacity_/4)
        decreaseSize();
}

template<typename T>
void Deque<T>::pop_front() {

    if (head_ == data_ + capacity_ - 1)
        head_ = data_;
    else
        head_++;

    --size_;

    if (capacity_ != 8 && capacity_ != 4 && size() == capacity_/4)
        decreaseSize();
}