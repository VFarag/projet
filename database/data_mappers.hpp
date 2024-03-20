#pragma once

#include "managers.hpp"

#include <memory>

class User;
class Labyrinth;


struct Mapper {
    explicit Mapper(std::unique_ptr<DBManager> &&database_manager);
    std::unique_ptr<DBManager> _database_manager = 0;
    virtual DBManager &database_manager();
};


struct DataMapper: protected Mapper {
    explicit DataMapper(std::unique_ptr<DBManager> &&database_manager);
    std::string get_user_data(User &user);
    std::unique_ptr<User> make_user(int id);
    std::unique_ptr<User> make_user(std::vector<std::string> &values);

    std::string get_world_data(World &world);
    std::shared_ptr<World> make_world(int id);
    std::shared_ptr<World> make_world(std::vector<std::string> &values);

    void save_world(World &world);
    void save_user(User &user);
};


struct LabyrinthBlockMapper: protected Mapper {
    explicit LabyrinthBlockMapper(std::unique_ptr<DBManager> &&database_manager);
    void set_blocks(Labyrinth &labyrinth);
};
