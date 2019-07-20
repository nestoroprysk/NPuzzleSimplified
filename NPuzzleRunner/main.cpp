#include <Runner.hpp>
#include <Utils.hpp>
#include <Parser.hpp>

#include <iostream>

namespace {

static constexpr auto g_usage = R"(
NPuzzle by omykolai & noprysk, 2019
usage:
  Run options

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
                std::cout << "Unexpected logic error: " << e.what() << std::endl;
            }
        } while (runner.hasSomethingToRun());
    }
    catch (const Parser::ParseError& e){
        std::cout << e.what() << std::endl;
    }
    catch (const Runner::ConfigurationError& e){
      std::cout << e.what() << std::endl;
      std::cout << g_usage << std::endl;
    }
    catch (...){
      std::cout << "Unexpected exception met" << std::endl;
    }
    return 0;
}
