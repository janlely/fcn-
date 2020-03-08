#include "catch.hpp"
//#include <fstream>
#include <iostream>
#include <cmath>
//#include <string>

using namespace std;

unsigned int Factorial( unsigned int number ) {
    return number <= 1 ? number : Factorial(number-1)*number;
}


//bool TestForLoop(){
    //ifstream f("/home/jay/Downloads/train-images-idx3-ubyte", ios::in);
    //f.seekg(4, std::ios::beg);
    //char * buffer = new char[4];
    //f.read(buffer, 4);
    //int a = int((unsigned char)(buffer[0]) << 24 |
            //(unsigned char)(buffer[1]) << 16 |
            //(unsigned char)(buffer[2]) << 8 |
            //(unsigned char)(buffer[3]));

    //cout<<a<<endl;
    //return true;
//}

bool TestExp(){
    double e = exp(1);
    cout<<e<<endl;
    //return true;
}


//bool TestS2D(){
    //string word = "123.123";
    //double lol = atof(word.c_str());
    //cout<<lol<<endl;
    //return true;
//}
TEST_CASE( "Factorials are computed", "[factorial]" ) {
    REQUIRE(TestExp());
    //REQUIRE(TestForLoop());
    //REQUIRE(TestS2D());
    //REQUIRE( Factorial(1) == 1 );
    //REQUIRE( Factorial(2) == 2 );
    //REQUIRE( Factorial(3) == 6 );
    //REQUIRE( Factorial(10) == 3628800 );
}

