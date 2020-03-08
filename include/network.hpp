#ifndef _NETWORK_HPP
#define _NETWORK_HPP
#include <armadillo>
#include "layer.hpp"
#include <vector>


//using std::vector;

class Network
{
    public:
        std::vector<FullConnectedLayer> layers;
        Activator activator;
    public:
        arma::vec predict(arma::vec input_vec);
        void train(std::vector<arma::vec> &data, std::vector<arma::vec> &label, double rate);
        void train_on_sample(arma::vec data, arma::vec label, double rate);
        void calc_gradient(arma::vec output, arma::vec label);
        void update_weight(double rate);
        Network(int layers[], int len, Activator activator);
        void print_weight();
        void grad_check(arma::vec data, arma::vec label);
};
#endif
