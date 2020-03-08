#include "activator.hpp"
#include <cmath>

arma::vec Activator::forward(arma::vec input){
    arma::vec result(input.n_rows, arma::fill::zeros);
    for(int i = 0; i < input.n_rows; i++){
        double sigmoid = 1.0 / (1.0 + exp(-1.0 * input[i]));
        result(i) = sigmoid;
    }
    return result;
}


arma::vec Activator::backward(arma::vec input){
    arma::vec result(input.n_rows, arma::fill::zeros);
    for(int i = 0; i < input.n_rows; i++){
        double sigmoid = input[i] * (1 - input[i]);
        result(i) = sigmoid;
    }
    return result;
}
