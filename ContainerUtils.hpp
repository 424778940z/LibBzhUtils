#ifndef CONTAINERUTILS_HPP
#define CONTAINERUTILS_HPP

#include <algorithm>
#include <array>
#include <cstdint>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <vector>

namespace bzh_utils
{
    namespace container
    {
        void print_stl_container(std::vector<uint8_t> pack, bool reverse = false, size_t bytes_per_line = 16)
        {
            std::ios oldState(nullptr);
            oldState.copyfmt(std::cout);
            size_t count = 0;
            if ( reverse )
                std::reverse(pack.begin(), pack.end());
            for ( int byte : pack )
            {
                count++;
                std::cout << std::setw(2) << std::setfill('0') << std::hex << byte << " ";
                if ( (count % bytes_per_line) == 0 )
                {
                    std::cout << std::endl;
                }
            }
            std::cout << std::endl;
            std::cout.copyfmt(oldState);
        }
        
        void print_raw_array(uint8_t* array, size_t len, bool reverse = false, size_t bytes_per_line = 16)
        {
            std::vector<uint8_t> pack;
            std::copy(array, array + len, std::back_inserter(pack));

            print_stl_container(pack, reverse, bytes_per_line);
        }

    }; // namespace utils

}; // namespace bzh

#endif // CONTAINERUTILS_HPP
