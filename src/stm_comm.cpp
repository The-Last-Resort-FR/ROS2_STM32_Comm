#include <cstdio>
#include "StmComm.hpp"


int main(int argc, char ** argv)
{
  (void) argc;
  (void) argv;
  STComm::SerialComm sc("/dev/ttyACM0");
  
  STComm::PrintResponse(*sc.SendCommand(STComm::Commands::SET_TRIG_FREQ, 20));
  STComm::PrintResponse(*sc.SendCommand(STComm::Commands::GET_TRIG_FREQ, 0));


  return 0;
}
