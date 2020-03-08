#ifndef _ACTIVATOR_HPP
#define _ACTIVATOR_HPP
#include <armadillo>

class Activator
{
    public:
        arma::vec forward(arma::vec input);
        arma::vec backward(arma::vec input);
};
#endif
