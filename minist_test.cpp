#include <vector>
#include <cxxopts.hpp>
#include "network.hpp"
#include <fstream>
#include "progressbar.h"


int main(int argc, char* argv[]){
    //parse arguments


    Activator activator;
    arma::vec train_image(8);
    train_image.fill(0.1);
    arma::vec train_label(8);
    train_label.fill(0.1);
    Network network(new int[3] {8,3,8}, 3, activator);
    //std::cout<<"start check grad"<<std::endl;
    network.grad_check(train_image, train_label);

    return 0;
}
