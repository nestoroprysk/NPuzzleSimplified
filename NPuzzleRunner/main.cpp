#include <Runner.hpp>
#include <Utils.hpp>
#include <Parser.hpp>

#include <iostream>

namespace {

static constexpr auto g_usage = R"(
NPuzzle by omykolai & noprysk, 2019
usage:
  ./Run options

where options are:
  -c <Set|QueueOnVector|QueueOnDequeue> select container
  -f <filename>                         provide file with matrix
  -g <n>                                generate random n * n matrix
  -v <short|long|result>                display short, long report, or correctness
  -h <Manhattan|InPos|NearPos>          select the heuristic
  -gc <float in range [0.0, 1.0]>       set distance cost
  -hc <float in range [0.0, 1.0]>       set heuristic cost
  -n <number>                           run n times
  -t <'time' in seconds>                set time limit
  -d <filename>                         set custom desired solution
)";



void print(const std::string& i_error)
{
    static constexpr auto g_error_format = "\033[1;31m";
    static constexpr auto g_normal_format = "\033[0m";
    std::cout << g_error_format << i_error << g_normal_format << std::endl;
}

}

int main(const int argc, const char** argv)
{
    if (argc == 1){
        std::cout << g_usage << std::endl;
        return 1;
    }
    try{
        auto runner = Runner(argc, argv);
        do {
            try{
                runner.run();
            }
            catch (const std::logic_error& e){
                print(std::string("Unexpected logic error: ") + e.what());
            }
        } while (runner.hasSomethingToRun());
    }
    catch (const Parser::ParseError& e){
        print(e.what());
    }
    catch (const Runner::ConfigurationError& e){
      print(e.what());
      std::cout << g_usage << std::endl;
    }
    catch (...){
        print("Unexpected exception met");
    }
    return 0;
}
