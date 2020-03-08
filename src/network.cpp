#include "network.hpp"
#include "layer.hpp"
//#include "progressbar.h"


Network::Network(int layers[], int len, Activator activator){
    this->activator = activator;
    for(int i = 0; i < len - 1; i++){
        int input_size = layers[i];
        int output_size = layers[i+1];
        this->layers.push_back(FullConnectedLayer(input_size, output_size, activator));
    }
}

arma::vec Network::predict(arma::vec input_vec){
    arma::vec output = input_vec;
    for(FullConnectedLayer &layer : this->layers){
        output = layer.forward(output);
    }
    return output;
}

void Network::train(std::vector<arma::vec> &data, std::vector<arma::vec> &label, double rate){
    //progressbar *bar = progressbar_new("Training", data.size());
    std::vector<arma::vec>::iterator d_iter, l_iter;
    //int count = 0;
    for(d_iter = data.begin(), l_iter = label.begin();
            d_iter != data.end() && l_iter != label.end();
            d_iter++, l_iter++){
        //if(count % 10000 == 0){
            //std::cout<<"training progress: "<<count<<std::endl;
        //}
        //count++;
        this->train_on_sample(*d_iter, *l_iter, rate);
        //progressbar_inc(bar);
    }
    //progressbar_finish(bar);
}

void Network::train_on_sample(arma::vec sample, arma::vec label, double rate){
    arma::vec output = this->predict(sample);
    this->calc_gradient(output, label);
    this->update_weight(rate);
}

void Network::calc_gradient(arma::vec output, arma::vec label){
    arma::vec delta_vec = this->activator.backward(output) % (label - output);
    std::vector<FullConnectedLayer>::reverse_iterator r_iter;
    for(r_iter = this->layers.rbegin(); r_iter != this->layers.rend(); r_iter++){
        delta_vec = (*r_iter).backward(delta_vec);
    }
}

void Network::update_weight(double rate){
    for(FullConnectedLayer &layer : this->layers){
        layer.update(rate);
    }
}

void Network::print_weight(){
    for(FullConnectedLayer &layer : this->layers){
        layer.print_weight();
    }
}

double loss(arma::vec label, arma::vec output){
    return 0.5 * arma::sum((label - output) % (label - output));
}

void Network::grad_check(arma::vec data, arma::vec label){
    arma::vec output = predict(data);
    //std::cout<<output<<std::endl;
    calc_gradient(output, label);
    //for(FullConnectedLayer &layer : this->layers){
        //std::pair<int, int> shape = layer.get_shape();
        //for(int i = 0; i < shape.first; i++){
            //for(int j = 0; j < shape.second; j++){
                //double w_grad = layer.get_weight_grad(i, j);
                //if(w_grad > 0.1){
                    //printf("(%d, %d)\n");
                //}
            //}
        //}
    //}
    double epsilon = 10e-4;
    for(FullConnectedLayer &layer : this->layers){
        for(int i = 0; i < layer.output_size; i++){
            for(int j = 0; j < layer.input_size; j++){
                layer.W(i,j) += epsilon;
                arma::vec output = predict(data);
                double err1 = loss(label, output);
                layer.W(i,j) -= 2 * epsilon;
                output = predict(data);
                double err2 = loss(label, output);
                double expect_grad = (err1 - err2) / (2 * epsilon);
                layer.W(i,j) += epsilon;
                if(layer.W_grad.at(i,j) > 0.1){
                    printf("weight at (%d, %d), expected - actural %.4e - %.4e\n", i, j, expect_grad, layer.W_grad.at(i,j));
                }
            }
        }
    }
}
