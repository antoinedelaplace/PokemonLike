#include "LogManager.hh"

void LogManager::error_logs(std::string error) {
    std::ofstream file;
    file.open("houvet_b/resources/logs/pokemon.log");
    file << error << std::endl;
    file.close();
    std::cout << error << std::endl;
}

