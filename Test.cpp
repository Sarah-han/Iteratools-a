
#include "doctest.h"
#include <string>
#include <iostream>
#include <vector>
#include "range.hpp"
#include "accumulate.hpp"
#include "filterfalse.hpp"
#include "compress.hpp"

using namespace itertools;

TEST_CASE("Test (1)- easy tests") {
    int count=5;
    for (int i: range(5,9)){
        CHECK(i==count);
        count++;
    }

    count=0;
    for (int i: range(0,10)){
        CHECK(i==count);
        count++;
    }

    vector<int> temp={5,11,18,26};
    count=0;
    for (int i: accumulate(range(5,9))){   // 5 11 18 26
        CHECK(temp[count]==i);
        count++;
    }

    temp={5,11,18,26,35,45,56,68,81};
    count=0;
    for (int i: accumulate(range(5,14))){  // 5 11 18 26 35 45 56 68 81
        CHECK(temp[count]==i);
        count++;
    }

    vector<float> vecFloat = {-1, 0.3, 5.2, -8.3};
    vector<float> temp2 = {-1, -0.7, 4.5, -3.8};
    count=0;
    for (auto i: accumulate(vecFloat)){   //temp2
        CHECK(temp2[count]- i< 0.01);
        if(count>0)
            CHECK(temp2[count]!=vecFloat[count]);
        count++;
    }


}

TEST_CASE("Test (2)- accumulate of range with binary operator") {

    vector<int> answer={5,30,210,1680};
    int count=0;
    for (int i: accumulate(range(5,9), [](int x, int y){return x*y;})) {
        CHECK(answer[count] == i);
        count++;
    }
    vector<int> answer2={5,31,218,1745};  //((5*6+1)*7+1)*8+1
    count=0;
    for (int i: accumulate(range(5,9), [](int x, int y){return x*y+1;})) {
        CHECK(answer2[count] == i);
        count++;
    }
    vector<int> answer3={2,6,24};  //2 2*3=6 6*4
     count=0;
    for (int i: accumulate(range(2,5), [](int x, int y){return x*y;})) {
        CHECK(answer3[count] == i);
        count++;
    }

    vector<int> answer4={1,3,6,10};  //1 1+2 1+2+3 1+2+3+4  //
    count=0;
    for (int i: accumulate(range(1,5), [](int x, int y){return x+y;})) {
        CHECK(answer4[count] == i);
        count++;
    }


    vector<string> vec = {"H", "He", "Hel","Hell","Hello"};
    vector<string> answer5 = {"H", "HHe", "HHeHel","HHeHelHell","HHeHelHellHello"};

     count=0;
    for (auto i: accumulate(vec, [](string x, string y){return x+y;})) {
        CHECK(answer4[count] == i);
        count++;
    }


}

TEST_CASE("Test (3)- Filter False"){
    vector<int> answer={5,7};
    int count=0;
    cout << endl << "Filter out all even numbers in range(5,9): " << endl;
    for (auto i: filterfalse([](int i){return i%2==0;}, range(5,9)) ) {
        CHECK(answer[count] == i);
        count++;
    }

    answer={6,8};
    count=0;
    for (auto i: filterfalse([](int i){return i%2==1;}, range(5,9)) ) {
        CHECK(answer[count] == i);
        count++;
    }

    CHECK(1==1);
          

}
