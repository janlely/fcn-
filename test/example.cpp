#include <iostream>
#include <armadillo>

using namespace std;
using namespace arma;

int main()
{
    //arma::mat A = arma::ones<arma::mat>(4,5);
    //arma::mat B = arma::ones<arma::mat>(4,5);

    //mat A = ones<mat>(5,5);
    //cout<<A<<endl;
    //mat A = randu<mat>(4,5);
    //cout<<A<<endl;

    //A.for_each( [](mat::elem_type& val) { val++; } );
    //cout<<A<<endl;

    //mat B = expmat(A);
    //cout<<B<<endl;
    ////cout << A*B.t() << endl;
    //cout <<A.n_cols<< A.n_rows<<endl;
    //vec a = ones<vec>(10);
    //vec b = ones<vec>(10);
    //mat A = randu<mat>(3,8);
    //mat B = randu<mat>(8,3);

    //A.save("W_3_8_.txt", raw_ascii);
    //B.save("W_8_3_.txt", raw_ascii);

    mat A,B;
    A.load("W_3_8.txt", raw_ascii);
    B.load("W_8_3.txt", raw_ascii);
    cout<<A<<endl;
    cout<<B<<endl;
    return 0;
}
