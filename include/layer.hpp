#ifndef _LAYER_HPP
#define _LAYER_HPP
#include <armadillo>
#include "activator.hpp"

class FullConnectedLayer
{
    public:
        int input_size;
        int output_size;
        arma::mat W;
        arma::mat W_grad;
        arma::vec b;
        arma::vec b_grad;
        arma::vec output;
        arma::vec input;
        arma::vec delta_vec;
        Activator activator;

    public:
        arma::vec forward(arma::vec input_vec);
        arma::vec backward(arma::vec delta_vec);
        void update(double rate);
        FullConnectedLayer(int input_size, int output_size, Activator activator);
        void print_weight();
        std::pair<int, int> get_shape();
        //double get_weight(int i, int j);
        //double get_weight_grad(int i, int j);
        //void set_weight(int i, int j, double w);
};
#endif
