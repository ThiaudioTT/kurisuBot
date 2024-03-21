#include "status.hpp"
#include <fstream>

void Status::status(const dpp::slashcommand_t& event) {
    event.reply ("I'm alive, Sir!\nRam Usage: " + getRamUsage());
}


/**
 * @brief Returns the CPU usage of the system. Like: "6%"
 * 
 * Check https://www.baeldung.com/linux/proc-meminfo for more information
 * @return std::string 
 */
std::string Status::getRamUsage() {

    std::ifstream meminfo("/proc/meminfo");

    if(!meminfo.is_open()) throw std::runtime_error("Failed to open /proc/meminfo");


    long total_mem = 0, available_mem = 0;
    // long free_mem = 0;
    // long buffers = 0;
    // long cached = 0;

    //todo: refactor, prob a better way to do this
    std::string line;
    while(getline(meminfo, line)) {
        // if(line.compare(0, 9, "MemTotal:") == 0) {
        //     total_mem = std::stol(line.substr(9));
        // } else if(line.compare(0, 8, "MemFree:") == 0) {
        //     free_mem = std::stol(line.substr(8));
        // } else if (line.compare(0, 8, "Buffers:") == 0) {
        //     buffers = std::stol(line.substr(8));
        // } else if (line.compare(0, 7, "Cached:") == 0) {
        //     cached = std::stol(line.substr(7));
        // } else if (line.compare(0, 13, "MemAvailable:") == 0) {
        //     available = std::stol(line.substr(13));
        // }

        // if(total_mem && free_mem && buffers && cached) break; // break if we read all the values

        // we only need MemTotal, MemAvailable
        if(line.compare(0, 9, "MemTotal:") == 0) {
            total_mem = std::stol(line.substr(9));
        } else if (line.compare(0, 13, "MemAvailable:") == 0) {
            available_mem = std::stol(line.substr(13));
        }
    }

    meminfo.close();

    // check if we read the values
    if(total_mem == 0 || available_mem == 0) throw std::runtime_error("Failed to read memory info");

    // calculate the used memory
    return std::to_string((total_mem - available_mem) * 100 / total_mem) + "%";
}