#include "gtest/gtest.h"
#include <iostream>
#include "deque.h"
#include <random>
#include <deque>

enum OPERATION {
    PUSH_BACK,
    PUSH_FRONT,
    POP_BACK,
    POP_FRONT
};

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

void generateTestSequences(size_t valueSize, size_t startSize, size_t queries, std::vector<std::pair<OPERATION, size_t> >& res) {
    std::mt19937 generator(time(0));
    res.resize(queries);

    size_t curSize = startSize;

    for (size_t i = 0; i < queries; i++) {
        unsigned int c = generator();
        res[i].first = OPERATION(c % 4);

        switch (res[i].first) {
            case PUSH_BACK:
            case PUSH_FRONT: {
                res[i].second = generator() % valueSize;
                curSize++;
                break;
            }
            case POP_BACK:
            case POP_FRONT: {
                size_t toDelete = generator() % (curSize < 5 ? curSize : 5);
                res[i].second = toDelete;
                curSize -= toDelete;
                break;
            }
        }
    }
}

void checkResult(const std::vector<int>& values, size_t queryNum, const std::vector<std::pair<OPERATION, size_t> >& queries, std::deque<int>& deq, Deque<int>& Deq) {

    for (int i = 0; i < queryNum; i++) {
        auto q = queries[i];

        switch (q.first) {
            case PUSH_BACK: {
                deq.push_back(values[q.second]);
                Deq.push_back(values[q.second]);
                break;
            }
            case POP_BACK: {
                for (int j = 0; j < q.second; j++) {
                    deq.pop_back();
                    Deq.pop_back();
                }
                break;
            }
            case PUSH_FRONT: {
                deq.push_front(values[q.second]);
                Deq.push_front(values[q.second]);
                break;
            }
            case POP_FRONT: {
                for (int j = 0; j < q.second; j++) {
                    deq.pop_front();
                    Deq.pop_front();
                }
                break;
            }
        }
        back_front_checker(Deq, deq);
    }
}

void random_push(const std::vector<int>& values, size_t size, std::deque<int>& deq, Deque<int>& Deq) {
    std::mt19937 generator(time(0));
    for (int i = 0; i < size; i++) {
        if (generator() % 2) {
            Deq.push_front(values[i]);
            deq.push_front(values[i]);
        } else {
            Deq.push_back(values[i]);
            deq.push_back(values[i]);
        }
        back_front_checker(Deq, deq);
    }
}

void random_pop(size_t size, std::deque<int>& deq, Deque<int>& Deq) {
    std::mt19937 generator(time(0));

    for (int i = 0; i < size; i++) {
        ASSERT_EQ(deq.size(), Deq.size());
        back_front_checker(Deq, deq);
        if (generator() % 2) {
            deq.pop_back();
            Deq.pop_back();
        } else {
            deq.pop_front();
            Deq.pop_front();
        }
    }
    ASSERT_TRUE(!deq.size() && !Deq.size());
}