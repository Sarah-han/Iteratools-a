
#pragma once
#include <vector>
#include <iostream>
#include "Itertool.hpp"

using namespace std;

namespace itertools {
    class range {
    public:
        int startIndex;
        int endIndex;

        range(int a, int b) {
            this->startIndex = a;
            this->endIndex = b;
        }

        range(range& other){
            this->startIndex = other.startIndex;
            this->endIndex = other.endIndex;
        }

        class iterator {
        private:
            int myIndex;
        public:
            iterator(int nIndex) {
                myIndex = nIndex;
            }

            int operator*() const {   //const int& operator*()
                return myIndex;
            }

            iterator& operator++() {
                ++myIndex;
                return *this;
            }

            iterator operator++(int) {
                iterator tmp = *this;
                ++myIndex;
                return tmp;
            }


            bool operator!=(const iterator &other) const { return myIndex != other.myIndex; }
            bool operator==(const iterator &other) const { return myIndex == other.myIndex; }




        };

        iterator begin() const  {
            return iterator(startIndex);
        }

        iterator end() const {
            return iterator(endIndex);
        }
    };
}




