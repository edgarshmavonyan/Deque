#include <iostream>
#include "deque.h"
#include <deque>

int main() {

    Deque<int> deq;
    int q;
    std::cin >> q;
    for (int i = 0; i < q; i++) {
        int a, b;
        std::cin >> a;
        if (a == 1)
            deq.pop_back();
        if (a == 2)
            deq.pop_front();

        if (a == 3) {
            std::cin >> b;
            deq.push_back(b);
        }
        if (a == 4) {
            std::cin >> b;
            deq.push_front(b);
        }
        if (a == 5) {
            break;
        }

        std::cout << deq;
//        std::cout << deq;
//        std::cout << deq.size() << std::endl;
    }

//    std::cout << deq;

//    std::cout << deq.end() - deq.begin();

//    std::cout << deq;
    std::deque<int> t;

    std::sort(deq.begin(), deq.end());

    return 0;
}