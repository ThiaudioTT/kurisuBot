#include <iostream>
#include <dpp/dpp.h>

namespace Status {
    // main handler has the same name as the namespace
    void status(const dpp::slashcommand_t &event);

    std::string getCPUUsage();
    std::string getRamUsage();
    std::string getDiskUsage();
    std::string getUptime();
}