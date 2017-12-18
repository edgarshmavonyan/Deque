#include "gtest/gtest.h"
#include "deque.h"
#include <vector>
#include <random>
#include <deque>
#include <exception>

TEST(main_test, random_test) {

    std::mt19937 generator(time(0));

    Deque<int> Deq;
    std::deque<int> deq;

    int size = 10000;
    for (int i = 0; i < size; i++) {

        if (deq.size() && !(generator() % 100)) {
            deq.pop_back();
            Deq.pop_back();
        }

        if (deq.size() && !(generator() % 100)) {
            deq.pop_front();
            Deq.pop_front();
        }
        else {
            deq.push_front(i);
            Deq.push_front(i);
        }

        EXPECT_EQ(deq.size(), Deq.size());
        for (int i = 0; i < deq.size(); i++) {
            ASSERT_EQ(deq[i], Deq[i]);
        }
    }
}

TEST(check_iterator_tests, main) {
    Deque<int> deq;

    int size = 170000;

    for (int i = 0; i < size; i++)
        deq.push_back(i);

    int i = 0;

    for (Deque<int>::iterator it = deq.begin(); it != deq.end(); it++, i++)
        EXPECT_EQ(i, *it);
}

TEST(check_iterator_tests, reverse) {
    Deque<int> deq;

    int size = 170000;

    for (int i = 0; i < size; i++)
        deq.push_back(i);

    int i = 0;
    
    for (Deque<int>::reverse_iterator it = deq.rbegin(); it != deq.rend(); it++, i++)
        EXPECT_EQ(size - i - 1, *it);
}

TEST(iterator_tests, stl_sort) {
    std::vector<int> values;
    Deque<int> deq;
    int n = 170000;
    for (int i = 0; i < n; i++)
        values.push_back(n - i - 1);

    random_shuffle(values.begin(), values.end());

    for (int i = 0; i < n; i++)
        deq.push_back(values[i]);

    sort(deq.begin(), deq.end());

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

    sort(deq.rbegin(), deq.rend());

    int i = 0;
    for (Deque<int>::iterator it = deq.begin(); it != deq.end(); it++, i++)
        EXPECT_EQ(size - 1 - i, *it);
}

TEST(method_testing, back_front_test) {
    Deque<int> D;
    std::deque<int> d;
    int size = 1000000;
    for (int i = 0; i < size; i++) {

        if (d.size() && !(rand() % 2)) {
            d.pop_back();
            D.pop_back();
        }
        if (d.size() && !(rand() % 2)) {
            d.pop_front();
            D.pop_front();
        }
        else {
            d.push_front(i);
            D.push_front(i);
        }
        EXPECT_EQ(d.size(), D.size());

        if (d.size()) {
            ASSERT_EQ(d.front(), D.front());
            ASSERT_EQ(d.back(), D.back());
        }
    }
}

int main(int argc, char ** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}