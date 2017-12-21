#include "gtest/gtest.h"
#include "testhelper.h"
#include "deque.h"
#include <vector>
#include <random>
#include <deque>
#include <exception>

TEST(main_test, full_random_test) {
    int size = 100000, queryNum = 100000;
    std::vector<int> values;
    generateSomeValues(size, values);

    Deque<int> Deq;
    std::deque<int> deq;

    push_values(Deq, values);
    push_values(deq, values);

    std::vector<std::pair<int, int> > queries;

    generateTestSequences(values.size(), values.size(), queryNum, queries);

    for (int i = 0; i < queryNum; i++) {
        auto q = queries[i];

        switch (q.first) {
            case 0 : {
                deq.push_back(q.second);
                Deq.push_back(q.second);
                break;
            }
            case 1: {
                for (int j = 0; j < q.second; j++) {
                    deq.pop_back();
                    Deq.pop_back();
                }
                break;
            }
            case 2: {
                deq.push_front(q.second);
                Deq.push_front(q.second);
                break;
            }
            case 3: {
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
    int size = 1000000;
    std::mt19937 generator(time(0));

    std::vector<int> values;
    generateSomeValues(size, values);

    std::deque<int> deq;
    Deque<int> Deq;

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