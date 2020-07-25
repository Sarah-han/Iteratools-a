#pragma once
#include <iterator>

namespace itertools{
    template<class IF,class C> class filterfalse {

    protected:
        //Fields
        const C& container;
        const IF& condition;
    public:
        //Constructor
        filterfalse( const IF& cond,const C& cont ):container(cont),condition(cond){}

        //inner class
        class iterator {

        private:
            //Fields
            const filterfalse& ff;
            decltype(container.begin()) iter; //for pass over the container

        public:
            //Constructor
            iterator(const filterfalse& ffT,decltype(container.begin()) iterT )
                    :ff(ffT),iter(iterT)
            {
                //find the first element that not stand in the condition
                while(iter!=ff.container.end() && ff.condition(*iter)) iter++;
            }

            auto operator*() const {
                return *iter;
            }

            //++iter
            iterator& operator++() {
                ++iter;
                //find the next element that not stand in the condition
                while(iter!=ff.container.end() && ff.condition(*iter))++iter ;
                return *this;
            }

            //iter++
            const iterator operator++(int) {
                iterator tmp= *this;
                ++iter;
                return tmp;
            }

            bool operator==(const iterator& iterator) const {
                return iterator.iter==iter;
            }

            bool operator!=(const iterator& iterator) const {
                return iterator.iter!=iter;
            }
        }; //End iterator


        iterator begin() const {
            return iterator(*this,container.begin());
        }

        iterator end() const {
            return iterator(*this,container.end());
        }
    };

}