#include "layer.hpp"
#include <utility>
#include <string>
#include <fstream>
//#include <format>

FullConnectedLayer::FullConnectedLayer(int input_size, int output_size, Activator activator){
    this->output_size = output_size;
    this->input_size = input_size;
    this->W = arma::randu<arma::mat>(output_size, input_size);
    //char filename[64];
    //sprintf(filename, "W_%d_%d.txt", output_size, input_size);
    //std::ifstream f(filename);
    //if(f.good()){
        //std::cout<<"read matrix from file"<<std::endl;
        //this->W.load(filename, arma::raw_ascii);
    //}else{
    this->W.for_each( [](arma::mat::elem_type& val) { val = val * 0.2 - 0.1; } );
        //this->W.save(filename, arma::raw_ascii);
    //}
    this->b = arma::zeros<arma::vec>(output_size);
    this->output = arma::zeros<arma::vec>(output_size);
    this->activator = activator;
}

arma::vec FullConnectedLayer::forward(arma::vec input_vec){
    this->input = input_vec;
    this->output = this->activator.forward(this->W * input_vec + this->b);
    return this->output;
}

arma::vec FullConnectedLayer::backward(arma::vec delta_vec){
    this->delta_vec = this->activator.backward(this->input) % (this->W.t() * delta_vec);
    this->W_grad = delta_vec * this->input.t();
    this->b_grad = delta_vec;
    return this->delta_vec;
}

void FullConnectedLayer::update(double rate){
    this->W += this->W_grad * rate;
    this->b += this->b_grad * rate;
}

void FullConnectedLayer::print_weight(){
    std::cout<<this->W<<std::endl;
}

//std::pair<int, int> FullConnectedLayer::get_shape(){
    //return std::make_pair(this->output_size, this->input_size);
//}

//double FullConnectedLayer::get_weight(int i, int j){
    //return this->W[i,j];
//}

//double FullConnectedLayer::get_weight_grad(int i, int j){
    //return this->W_grad[i,j];
//}
//void FullConnectedLayer::set_weight(int i, int j, double w){
    //this->W(i,j) = w;
//}
