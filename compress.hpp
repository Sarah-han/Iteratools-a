#pragma once
#include <iterator>

namespace itertools{
    template <class T1 , class T2> class compress{

    protected:
        //Fields
        const T1& containerObj;
        const T2& containerBool;
    public:
        //Constructor
        compress(const T1& obj , const T2& bol) : containerObj(obj) , containerBool(bol){}

        //inner class
        class iterator{

        private:
            //Fields
            const compress& comp;
            decltype(containerObj.begin()) iterObj;
            decltype(containerBool.begin()) iterBool;
        public:
            //Constructor
            iterator(decltype(containerObj.begin()) itObj , decltype(containerBool.begin()) itBool , const compress& co)
                    : iterObj(itObj), comp(co)
            {
                if(iterBool!=co.containerBool.end()) iterBool=itBool;
                while(iterBool!=comp.containerBool.end() && *iterBool == false) {
                    iterObj++;
                    iterBool++;
                }
            }

            iterator& operator++(){
                ++iterObj;
                ++iterBool;
                while(iterBool!=comp.containerBool.end() && !(*iterBool)) {
                    iterObj++;
                    iterBool++;
                }
                return *this; //return current iter after ++iter
            }

            const iterator operator++(int){
                iterator temp = *this;
                ++iterObj;
                ++iterBool;
                return temp;
            }

            bool operator==(const iterator& it) const{
                return iterObj == it.iterObj;
            }

            bool operator!=(const iterator& it) const{
                return iterObj != it.iterObj;
            }

            auto operator*(){
                return *iterObj;
            }

        }; //End iterator

        iterator begin() const{
            return iterator(containerObj.begin(), containerBool.begin(), *this);
        }

        iterator end() const {
            return iterator(containerObj.end(), containerBool.end(), *this);
        };
    };
}