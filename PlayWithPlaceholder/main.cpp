#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

//all credits to:
//https://accu.org/journals/overload/14/73/gibson_1397/

#include "binder.hpp"

std::string banner {"test"};

template<typename InIt, typename UnaryFn>
void my_for_each(InIt first, InIt last, UnaryFn fn) {
  for(; first != last; ++first)
      fn(*first);
}

int main()
{
    auto lmbd = [](std::string prefix, std::string suffix, std::string str){
        std::cout <<  prefix + str + suffix << std::endl;
    };

    std::vector<std::string> vecs {"foo","bar"};

    std::cout << "Hello World!" << std::endl;

    std::for_each(vecs.begin(),vecs.end(),bind(lmbd,std::string("a_"),std::string("_z"),_1));

    for(const auto & s :vecs)
        std::cout << s << " ";

    std::cout << "\nBye!" << std::endl;

    return 0;
}
