#include "timer.hxx"
int main()
{
  boost::asio::io_context io;
  MSKBO_timer p(io, timer_log);
  io.run();

  return 0;
}