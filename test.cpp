#include "gtest/gtest.h"
#include "testhelper.h"
#include "deque.h"
#include <vector>
#include <random>
#include <deque>
#include <exception>

TEST(main_test, full_random_test) {
    size_t size = 100000, queryNum = 100000;
    std::vector<int> values;
    generateSomeValues(size, values);

    Deque<int> Deq;
    std::deque<int> deq;

    push_values(Deq, values);
    push_values(deq, values);

    std::vector<std::pair<OPERATION, size_t> > queries;

    generateTestSequences(values.size(), values.size(), queryNum, queries);

    checkResult(values, queryNum, queries, deq, Deq);
}

TEST(main_test, random_test) {
    int size = 10000;

    std::mt19937 generator(time(0));

    Deque<int> Deq;
    std::deque<int> deq;

    for (int i = 0; i < size; i++) {

        if (deq.size() && !(generator() % 100)) {
            deq.pop_back();
            Deq.pop_back();
        }

        if (deq.size() && !(generator() % 100)) {
            if (generator() % 2) {
                deq.pop_front();
                Deq.pop_front();
            }
            else {
                deq.pop_back();
                Deq.pop_back();
            }
        }
        else {
            deq.push_front(i);
            Deq.push_front(i);
        }
        back_front_checker(Deq, deq);
    }
}

TEST(full_test, random_test) {
    size_t size = 1000000;
    std::mt19937 generator(time(0));

    std::vector<int> values;
    generateSomeValues(size, values);

    std::deque<int> deq;
    Deque<int> Deq;

    random_push(values, size, deq, Deq);

    random_pop(size, deq, Deq);
}

TEST(check_iterator_tests, main) {
    size_t size = 100000;

    Deque<int> deq;

    for (int i = 0; i < size; i++)
        deq.push_back(i);

    int i = 0;

    auto it1 = deq.begin();
    auto it2 = deq.cbegin();

    for (; it1 != deq.end() && it2 != deq.cend(); it1++, it2++, i++) {
        EXPECT_EQ(i, *it1);
        EXPECT_EQ(i, *it2);
    }
}

TEST(check_iterator_tests, reverse) {
    Deque<int> deq;

    int size = 100000;

    for (int i = 0; i < size; i++)
        deq.push_back(i);

    int i = 0;

    auto it1 = deq.rbegin();
    auto it2 = deq.crbegin();

    for (; it1 != deq.rend() && it2 != deq.crend(); it1++, it2++, i++) {
        EXPECT_EQ(size - i - 1, *it1);
        EXPECT_EQ(size - i - 1, *it2);
    }
}

TEST(iterator_tests, stl_sort) {
    std::vector<int> values;
    Deque<int> deq;
    int n = 100000;
    for (int i = 0; i < n; i++)
        values.push_back(n - i - 1);

    random_shuffle(values.begin(), values.end());

    for (int i = 0; i < n; i++)
        deq.push_back(values[i]);

    std::sort(deq.begin(), deq.end());

    int i = 0;
    for (Deque<int>::iterator it = deq.begin(); it != deq.end(); it++, i++)
        EXPECT_EQ(i, *it);
}

TEST(iterator_tests, stl_reverse_sort) {
    std::vector<int> values;
    Deque<int> deq;
    int size = 100000;

    for (int i = 0; i < size; i++)
        values.push_back(size - i - 1);

    random_shuffle(values.rbegin(), values.rend());

    for (int i = 0; i < size; i++)
        deq.push_back(values[i]);

    std::sort(deq.rbegin(), deq.rend());

    int i = 0;
    for (Deque<int>::iterator it = deq.begin(); it != deq.end(); it++, i++)
        EXPECT_EQ(size - 1 - i, *it);
}

TEST(method_testing, back_front_test) {
    Deque<int> Deq;
    std::deque<int> deq;
    int size = 1000000;
    for (int i = 0; i < size; i++) {
        if (deq.size() && !(rand() % 2)) {
            deq.pop_back();
            Deq.pop_back();
        }
        if (deq.size() && !(rand() % 2)) {
            deq.pop_front();
            Deq.pop_front();
        }
        else {
            deq.push_front(i);
            Deq.push_front(i);
        }
        back_front_checker(Deq, deq);
    }
}

int main(int argc, char ** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}