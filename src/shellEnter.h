#include <exception>
#include <iostream>

#ifndef SHELL_ENTER_H
#define SHELL_ENTER_H

// Exception pour géré si on fait un enter en console. 
class ShellEnter : public std::exception
{
};
#endif