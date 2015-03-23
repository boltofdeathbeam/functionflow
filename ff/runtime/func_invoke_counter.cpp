#include "utilities/func_invoke_counter.h"
#include <sstream>

namespace ff
{
thread_local_var<func_invoke_counter::counters_t> func_invoke_counter::m_oCounters;

void func_invoke_counter::init(){}

void func_invoke_counter::call(int tag)
{
  m_oCounters.get()[tag] ++;
}

bool func_invoke_counter::is_normal()
{
return true;
}

std::string func_invoke_counter::status()
{
  std::stringstream ss;
  auto ts = func_invoke_counter::tags();
  for(auto it = ts.begin(); it != ts.end(); ++it)
  {
    for(size_t i = 0; i < m_oCounters.size(); ++i)
    {
      ss<<i<<" : "<<it->second<<":"<<m_oCounters[it->first].get()<<"\n";
    }
  }
  return ss.str();
}
std::map<int, std::string> func_invoke_counter::tags()
{
  std::string[] ts = [
#define FUNC_TAG(a) #a ,
#include "utilities/func_tags.h"
#undef FUNC_TAG
    ];
  std::map<int, std::string> res ;
  for(int i = 0; i < func_counter;++i)
  {
    res.insert(std::make_pair(i, ts[i]));
  }
  return res;
}

}//end namespace ff
