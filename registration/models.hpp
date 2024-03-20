#pragma once

#include "../database/encryption.hpp"

#include <memory>

class World;
class Location;
class DataMapper;


class User {
    private:
        int _id;
        World *_world;
        Location *_location;
        std::unique_ptr<Password> _password;
        bool _is_logged_in;

        void set_location(
            World *const world,
            int const latitude, int const longitude);

    public:
        explicit User(World *const world);
        explicit User(
            int const id, World *const world,
            int const latitude, int const longitude);

        int id();
        void set_id(int const id);

        Password &password();
        void set_password(
            std::string &password, bool is_encrypted=false);
        int log_in(std::string &input_password);
        void log_out();
        bool is_logged_in();

        Location *const location();
        World &world();
        void print_location();

        enum Directions {
            UP = 1, DOWN = 2, LEFT = 3, RIGHT = 4};
        void move(enum Directions direction);

        static std::unique_ptr<User> get(
            DataMapper &data_mapper, int const id);
        void save(DataMapper &data_mapper);
};
