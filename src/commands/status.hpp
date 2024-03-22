#include <iostream>
#include <dpp/dpp.h>
#include <vector>

// todo: docs
namespace Status {
    // main handler has the same name as the namespace
    void status(const dpp::slashcommand_t &event);

    // helper functions
    std::string getCPUUsage();
    std::vector<size_t> getCpuJiffies();
    std::string getRamUsage();
    std::string getDiskUsage();
    std::string getUptime();
}