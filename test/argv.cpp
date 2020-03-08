#include <cxxopts.hpp>
int main(int argc, char** argv)
{
    cxxopts::Options options("test", "A brief description");

    options.add_options()
        ("train-image", "train image", cxxopts::value<std::string>())
        ("train-label", "train label", cxxopts::value<std::string>())
        ("test-image", "test image", cxxopts::value<std::string>())
        ("test-label", "test label", cxxopts::value<std::string>())
        ("rate", "rate", cxxopts::value<std::string>()->default_value("0.3"))
        ("h,help", "Print usage")
    ;
    //options.add_options()
        //("bar", "Param bar", cxxopts::value<std::string>())
        //("debug", "Enable debugging", cxxopts::value<bool>()->default_value("false"))
        //("foo", "Param foo", cxxopts::value<int>()->default_value("10"))
        //("h,help", "Print usage")
    //;

    auto result = options.parse(argc, argv);

    if (result.count("help"))
    {
      std::cout << options.help() << std::endl;
      exit(0);
    }
    //bool debug = result["debug"].as<bool>();
    //std::string bar;
    //if (result.count("bar"))
      //bar = result["bar"].as<std::string>();
    //int foo = result["foo"].as<int>();

    return 0;

}
