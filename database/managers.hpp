#pragma once

#include <filesystem>
#include <vector>
#include <map>

class World;
class User;


class DBManager {
    private:
        std::map<std::string, std::string> const _repositories;
        std::filesystem::path const base_path;

    public:
        explicit DBManager(
            std::string const &base_path,
            std::map<std::string, std::string> const &repositories
        );
        std::map<std::string, std::string> const repositories();

        int get_next_id(std::string const &repository);

        std::vector<std::string> get_values(
            std::string const &repository, int const id);

        void write(std::string const &repository, std::string const &data);
        void destroy(std::string const &repository, int const id);

        std::vector<std::string> get_full_repo(std::string const &repository);
};
