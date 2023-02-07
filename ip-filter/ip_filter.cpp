#include "ip.hpp"

int main(){

    try{
        std::vector<std::vector<uint8_t> > ip_pool;
        for(std::string line; std::getline(std::cin, line);){
            try{
                if(auto pos = line.find_first_of('\t'); pos != std::string::npos)
                    line.erase(pos);
                ip_pool.push_back(convert_ip_to_vector(line));
            }
            catch(const std::exception &e){
                std::cerr << e.what() << std::endl;
                continue;
            }
        }

        std::sort(ip_pool.begin(), ip_pool.end(), std::greater<std::vector<uint8_t>>());
        std::for_each(ip_pool.cbegin(), ip_pool.cend(), print_ip);

        ip_filter(ip_pool, [](const std::vector<uint8_t> &ip){ return (ip[0] == 1) ? true : false; }, print_ip);
        ip_filter(ip_pool, [](const std::vector<uint8_t> &ip){ return (ip[0] == 46 && ip[1] == 70) ? true : false; }, print_ip);
        ip_filter(ip_pool, [](const std::vector<uint8_t> &ip){
            for(const auto &it : ip){
                if(it == 46) return true;
            } return false;},
        print_ip);
    }
    catch(const std::exception &e){
        std::cerr << e.what() << std::endl;
    }    
    return 0;
}
