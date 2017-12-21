#include "gtest/gtest.h"
#include <iostream>
#include "deque.h"
#include <random>
#include <deque>

void generateSomeValues(int size, std::vector<int>& res) {
    res.resize(size);
    std::mt19937 generator(time(0));

    for (int i = 0; i < size; i++)
        res[i] = generator();
}

template<typename T>
void back_front_checker(const Deque<T>& Deq, const std::deque<T>& deq) {
    EXPECT_EQ(deq.size(), Deq.size());
    if (!deq.size()) return;
    EXPECT_EQ(deq.front(), Deq.front());
    EXPECT_EQ(deq.back(), Deq.back());
}

template<typename DeqType>
void push_values(DeqType& deq, std::vector<int>& values) {
    for (auto elem: values)
        deq.push_back(elem);
}

void generateTestSequences(int valueSize, int startSize, int queries, std::vector<std::pair<int, int> >& res) {
    std::mt19937 generator(time(0));
    res.resize(queries);

    int curSize = startSize;

    for (int i = 0; i < queries; i++) {
        int c = (generator() % 1000 + 1000) % 1000;
        res[i] = std::make_pair((c % 4 + 4) % 4, 0);
        switch (c % 2) {
            case 0: {
                res[i].second = (generator() % valueSize + valueSize) % valueSize;
                curSize++;
                break;
            }
            case 1: {
                int toDelete = ((generator() % 5 + 5) % 5) % curSize;
                res[i].second = toDelete;
                curSize -= toDelete;
                break;
            }
        }

    }
}