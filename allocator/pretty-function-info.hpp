#pragma once

#ifdef PRETTY_FUNCTION_INFO

#   include <iostream>

#   define pretty_function_info() std::cout << __PRETTY_FUNCTION__ << std::endl;
#else
#   define pretty_function_info()
#endif

