#include "status.hpp"
#include <fstream>
#include <chrono>
#include <thread>

void Status::status(const dpp::slashcommand_t& event) {
    event.reply ("I'm alive, Sir!\n**CPU**: " + getCPUUsage() + 
                "\n**RAM**: " + getRamUsage());
}


std::vector<size_t> Status::getCpuJiffies() {
    std::ifstream stat("/proc/stat");
    stat.ignore(5, ' '); // ignore the first 5 characters "cpu  "
    std::vector<size_t> cpu_times;

    for(size_t time; stat >> time; cpu_times.push_back(time));

    stat.close();

    return cpu_times;
}


/**
 * @brief Returns the CPU usage of the system. Like: "6%"
 * 
 * @return std::string 
 */
std::string Status::getCPUUsage() {
    //https://rosettacode.org/wiki/Linux_CPU_utilization
    //https://support.checkpoint.com/results/sk/sk65143
    // https://www.idnt.net/en-US/kb/941772

    std::vector<size_t> cpu_jiffies1 = getCpuJiffies();
    // sleep(1); // TODO: can we use other thing instead of sleep? This is blocking the whole program
    // TODO: this is blocking the whole program, we should use async or threads. use event thinking or something
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    std::vector<size_t> cpu_jiffies2 = getCpuJiffies();

    const size_t total_time1 = std::accumulate(cpu_jiffies1.begin(), cpu_jiffies1.end(), 0);
    const size_t total_time2 = std::accumulate(cpu_jiffies2.begin(), cpu_jiffies2.end(), 0);

    const size_t delta_time = total_time2 - total_time1;
    const size_t cpu_idle = cpu_jiffies2[3] - cpu_jiffies1[3]; // idle time is the 4th element in the vector

    const size_t cpu_used = delta_time - cpu_idle;

    // calc the percentage
    return std::to_string(cpu_used * 100 / delta_time) + "%";
}

/**
 * @brief Returns the RAM usage of the system. Like: "6%"
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

        if(total_mem && available_mem) break; // break if we read all the values
    }

    meminfo.close();

    // check if we read the values
    if(total_mem == 0 || available_mem == 0) throw std::runtime_error("Failed to read memory info");

    // calculate the used memory
    return std::to_string((total_mem - available_mem) * 100 / total_mem) + "%";
}