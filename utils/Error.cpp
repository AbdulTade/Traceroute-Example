# include <stdarg.h>
# include <iostream>
# include <cstdio>
# include <string>
# include "../libs/libfmt/include/fmt/core.h"
# include "Utils.hpp"

void Error::write_error(const std::string &_msg)
{
    std::cerr << ERROR_COLOR << _msg << RESET_COLOR;
}

void Error::die_with_error(const std::string &_msg, int code)
{
    write_error(_msg);
    exit(code);
}

void Error::write_console(const std::string &_msg)
{
    std::cout << SUCCESS_COLOR << _msg << RESET_COLOR;
}

void Error::writeln(const std::string &_msg)
{
   std::cout << SUCCESS_COLOR << _msg << RESET_COLOR << std::endl;
}

void Error::writef(const char* fmt, ...)
{
    std::cout << SUCCESS_COLOR;
    va_list args;
    va_start(args,fmt);
    vprintf(fmt,args);
    va_end(args);
    std::cout << RESET_COLOR;
}