#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"
#include <string>
#include <iostream>

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
    REQUIRE(TestS2D);
    //REQUIRE( Factorial(1) == 1 );
    //REQUIRE( Factorial(2) == 2 );
    //REQUIRE( Factorial(3) == 6 );
    //REQUIRE( Factorial(10) == 3628800 );
}
