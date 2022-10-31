# include <cstdlib>
# include <iostream>
# include <netinet/in.h>
# include <sstream>
# include <string>
# include <sys/socket.h>
# include "../utils/Utils.hpp"

bool ip::IP::isValid()
{
    int count = 0;
    auto it = this->str_ip.cbegin();
    while(++it != this->str_ip.cend())
    {
        if((*it == '.'))
            count++;
    }
    return (count == 3);
}

uint32_t ip::IP::ip_str2int(const std::string &ip)
{
    uint32_t value = 0;
    int count = 0;
    std::string token;
    std::stringstream ss{ip};

    while(std::getline(ss,token,'.'))
    {
        int v = std::atoi(token.c_str());
        std::cout << v << std::endl;
        value = set_byte(value,v,count);
        count++;
    }

    return value;
}

