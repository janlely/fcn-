#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"
#include <iostream>
//#include <cmath>

using namespace std;

unsigned int Factorial( unsigned int number ) {
    return number <= 1 ? number : Factorial(number-1)*number;
}


bool TestS2D(){
    string word = "123.123";
    double lol = atof(word.c_str());
    cout<<"hello"<<endl;
    cout<<lol<<endl;
}

TEST_CASE( "Factorials are computed", "[factorial]" ) {
    REQUIRE(TestS2D());
}

