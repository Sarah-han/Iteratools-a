
#pragma once
#include <iostream>
#include <vector>
#include <iterator>

typedef struct {
    template <typename U>
    auto operator()(const U& x , const U& y) const{
        return x+y;
    }
} sum;

namespace itertools{

    template<class T,class F = sum>
    class accumulate{
        const T& collect;
        const F& func;
    public:
        accumulate(const T& c, const F& f=sum()):collect(c),func(f){} //Constructor
        class iterator {
            decltype(collect.begin()) it;
            typename std::decay<decltype(*(collect.begin()))>::type sum;
            const accumulate& myaccumulate;

        public:
            iterator(const accumulate& a,decltype(collect.begin()) i): myaccumulate(a),it(i)
            {       if (i != myaccumulate.collect.end())
                       sum=*i;
            }

            auto operator*() const {
                return sum;
            }

            iterator& operator++() {
                ++it;
                if(it!=myaccumulate.collect.end())
                {
                    sum=myaccumulate.func(sum,*(it));
                }
                return *this;
            }

            const iterator operator++(int) {
                iterator save=*this;
                it++;
                if(it!=myaccumulate.collect.end())
                {
                    sum=myaccumulate.func(sum,*(it));
                }
                return *save;
            }

            bool operator!=(const iterator& iterator) const {
                return iterator.it!=it;
            }
            bool operator==(const iterator& iterator) const {
                return iterator.it==it;
            }

        };

        iterator begin() const {
            return iterator(*this,collect.begin());
        }

        iterator end() const {
            return iterator(*this, collect.end());
        }
    };
}