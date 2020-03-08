#include <vector>
#include <cxxopts.hpp>
#include "network.hpp"
#include <fstream>
//#include "spdlog/spdlog.h"
//#include "spdlog/sinks/basic_file_sink.h"
#include "progressbar.h"

int four_bytes_to_int(char *buffer){
    return int((unsigned char)(buffer[0]) << 24 |
            (unsigned char)(buffer[1]) << 16 |
            (unsigned char)(buffer[2]) << 8 |
            (unsigned char)(buffer[3]));
}

void load_train_data(std::vector<arma::vec> &image, std::vector<arma::vec> &label, std::string image_file, std::string label_file){
    std::ifstream img_f(image_file, std::ios::in);
    std::ifstream label_f(label_file, std::ios::in);
    img_f.seekg(4, std::ios::beg);
    label_f.seekg(8, std::ios::beg);

    char *buffer = new char[4];
    img_f.read(buffer, 4);
    int data_size = four_bytes_to_int(buffer);
    img_f.read(buffer, 4);
    int row_size = four_bytes_to_int(buffer);
    img_f.read(buffer, 4);
    int col_size = four_bytes_to_int(buffer);
    int input_vec_size = row_size * col_size;

    std::cout<<"data size: "<<data_size<<std::endl;
    std::cout<<"row size: "<<row_size<<std::endl;
    std::cout<<"col size: "<<col_size<<std::endl;
    std::cout<<"input_vec_size: "<<input_vec_size<<std::endl;
    std::cout<<"loading train data"<<std::endl;
    //progressbar *bar = progressbar_new("Loading data", data_size);
    for(unsigned int i = 0; i < data_size; i++){
        if(i % 10000 == 0){
            std::cout<<"1/6"<<std::endl;
        }
        //load image data
        arma::vec sample(input_vec_size, arma::fill::zeros);
        for(unsigned int j = 0; j < input_vec_size; j++){
            int c = img_f.get();
            sample(j) = c;
        }
        image.push_back(sample);
        //load labal
        int value = label_f.get();
        arma::vec label_vec(10, arma::fill::zeros);
        for(unsigned int j = 0; j < 10; j++){
            if(value == j){
                label_vec(j) = 0.9;
            }else{
                label_vec(j) = 0.1;
            }
        }
        label.push_back(label_vec);
        //std::cout<<"loading"<<std::endl;
        //progressbar_inc(bar);
    }
    //progressbar_finish(bar);
}

void load_test_data(std::vector<arma::vec> &image, std::vector<int> &label, std::string image_file, std::string label_file){
    std::ifstream img_f(image_file, std::ios::in);
    std::ifstream label_f(label_file, std::ios::in);
    img_f.seekg(4, std::ios::beg);
    label_f.seekg(8, std::ios::beg);

    char *buffer = new char[4];
    img_f.read(buffer, 4);
    int data_size = four_bytes_to_int(buffer);
    img_f.read(buffer, 4);
    int row_size = four_bytes_to_int(buffer);
    img_f.read(buffer, 4);
    int col_size = four_bytes_to_int(buffer);
    int input_vec_size = row_size * col_size;

    std::cout<<"data size: "<<data_size<<std::endl;
    std::cout<<"row size: "<<row_size<<std::endl;
    std::cout<<"col size: "<<col_size<<std::endl;
    std::cout<<"input_vec_size: "<<input_vec_size<<std::endl;
    std::cout<<"loading test data"<<std::endl;
    //progressbar *bar = progressbar_new("Loading data", data_size);
    for(unsigned int i = 0; i < data_size; i++){
        //load image data
        arma::vec sample(input_vec_size, arma::fill::zeros);
        for(unsigned int j = 0; j < input_vec_size; j++){
            int c = img_f.get();
            sample(j) = c;
        }
        image.push_back(sample);
        //load labal
        int value = label_f.get();
        label.push_back(value);
        //progressbar_inc(bar);
    }
    //progressbar_finish(bar);
}

int get_result(arma::vec output){
    double max_value = -100000000;
    int max_index = 0;
    for(unsigned int i = 0; i < output.n_rows; i++){
        double value = output[i];
        if(value > max_value){
            max_value = value;
            max_index = i;
        }
    }
    return max_index;
}



double evaluate(Network network, std::vector<arma::vec> test_data, std::vector<int> test_label){
    int error = 0;
    std::vector<arma::vec>::iterator d_iter;
    std::vector<int>::iterator l_iter;
    for(d_iter = test_data.begin(), l_iter = test_label.begin();
            d_iter != test_data.end() && l_iter != test_label.end();
            d_iter++, l_iter++){
        int predict = get_result(network.predict(*d_iter));
        if(predict != *l_iter){
            error += 1;
        }
    }
    return double(error) / test_data.size();
}

int main(int argc, char* argv[]){
    //parse arguments
    cxxopts::Options options("minis", "A neural network on minist data set");
    options.add_options()
        ("train-image", "train image", cxxopts::value<std::string>())
        ("train-label", "train label", cxxopts::value<std::string>())
        ("test-image", "test image", cxxopts::value<std::string>())
        ("test-label", "test label", cxxopts::value<std::string>())
        ("rate", "rate", cxxopts::value<std::string>()->default_value("0.3"))
        ("h,help", "Print usage")
    ;
    auto result = options.parse(argc, argv);

    if (result.count("help"))
    {
      std::cout << options.help() << std::endl;
      exit(0);
    }

    //init log config
    //auto file_logger = spdlog::basic_logger_mt("basic_logger", "logs/minist.log");
    //spdlog::set_default_logger(file_logger);
    //spdlog::set_pattern("[%H:%M:%S %z] [%n] [%^---%L---%$] [thread %t] %v");

    //load train data
    std::vector<arma::vec> train_image;
    std::vector<arma::vec> train_label;
    load_train_data(train_image, train_label, result["train-image"].as<std::string>(), result["train-label"].as<std::string>());
    //load test data
    std::vector<arma::vec> test_image;
    std::vector<int> test_label;
    load_test_data(test_image, test_label, result["test-image"].as<std::string>(), result["test-label"].as<std::string>());

    Activator activator;
    Network network(new int[3] {784,300,10}, 3, activator);
    int epoch = 0;
    double last_error_ratio = 1.0;
    double rate = atof(result["rate"].as<std::string>().c_str());
    while(1){
        epoch += 1;
        network.train(train_image, train_label, rate);
        std::cout<<"epoch: "<<epoch<<std::endl;
        if(epoch % 10 == 0){
            double error_ratio = evaluate(network, test_image, test_label);
            std::cout<<"error ratio: "<<error_ratio<<std::endl;
            //network.print_weight();
            //SPDLOG_INFO("error ratio: {}", error_ratio);
            if(error_ratio > last_error_ratio){
                break;
            }else{
                last_error_ratio = error_ratio;
           }
        }
    }
    network.print_weight();
    std::cout<<"finish"<<std::endl;

    //final_weight_f = open(args.final_weight, 'wb')
    //network.save_weights(final_weight_f)
    return 0;
}
