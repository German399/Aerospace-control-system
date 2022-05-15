#include <iostream>
#include <boost/asio.hpp>
#include <boost/bind/bind.hpp>
#include <nlohmann/json.hpp>
enum timerType
{
    timer_async_count,
    timer_count,
    timer_async_log,
    timer_log
};
using json = nlohmann::json;
class MSKBO_timer
{
public:
  MSKBO_timer(boost::asio::io_context& io,timerType bindTimerType)///вызывает каждые 100ГЦ
    : timer_(io, boost::asio::chrono::milliseconds(10)),
      count_(0),MSKBO_runtime(0.0)
  {
    switch (bindTimerType)
    {
    case timer_async_count:
        timer_.async_wait(boost::bind(&MSKBO_timer::step, this));
        break;
    case timer_async_log:
    
    timer_.async_wait(boost::bind(&MSKBO_timer::log, this));
    default:
        std::cout <<"bindTimerType switch for"<< bindTimerType<<" not implemented!"<< std::endl;
        break;
    }
    
  }

  ~MSKBO_timer()
  {
    std::cout << "Final count is " << count_ << std::endl;
  }

  void step()
  {
    //if (count_ < 500)
    //{  
      std::cout <<"step_num="<< count_<<" sec ="<<MSKBO_runtime<< std::endl;
      ++count_;
      MSKBO_runtime+=0.01;
      timer_.expires_at(timer_.expiry() + boost::asio::chrono::milliseconds(10));
      timer_.async_wait(boost::bind(&MSKBO_timer::log, this));
   // }
  }
  void log()
  {
    if (count_ < 500)
    {  
      std::cout <<"step_num="<< count_<<" sec ="<<MSKBO_runtime<< std::endl;
      
      //todo make json obj with step and num
      //pass obj to autolog
      ++count_;
      MSKBO_runtime+=0.01;
      timer_.expires_at(timer_.expiry() + boost::asio::chrono::milliseconds(10));
      timer_.async_wait(boost::bind(&MSKBO_timer::log, this));
    }
  }
private:
  boost::asio::steady_timer timer_;
  unsigned long count_;
  long double MSKBO_runtime;
};