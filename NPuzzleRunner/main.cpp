#include <iostream>

static constexpr auto g_usage = R"(
NPuzzle by omykolai & noprysk, 2019
usage:
  Run options

where options are:
  -c <Set|QueueOnVector|QueueOnDequeue> select container
  -f <filename>                         provide file with matrix
  -g <n>                                generate random n * n matrix
  -v <short|long>                       display short or long report
  -h <Manhattan|InPos|NearPos>          select the heuristic
  -gc <float in range [0.0, 1.0]>       set distance cost
  -hc <float in range [0.0, 1.0]>       set heuristic cost
  -n <number>                           run n times
  -t <'time' in second>                 set time limit
  -d <filename>                         set custom desired solution

)";

int main()
{
    std::cout << g_usage << std::endl;
}

