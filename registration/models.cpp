#include "../location/models.hpp"
#include "../database/data_mappers.hpp"
#include "../registration/models.hpp"

#include <iostream>

using namespace std;


User::User(World *const world):
    _id(0), _world(world) {set_location(world, 0, 0);}

User::User(int const id, World *const world, int const latitude,
           int const longitude): _id(id), _world(world) {
    set_location(world, latitude, longitude);
}

int User::id() {return _id;}
void User::set_id(int const id) {_id = id;}

Location *const User::location() {return _location;}
World &User::world() {return *_world;}

void User::set_location(World *const world, int const x, int const y) {
    _location = world->locations().at(y).at(x).get();
}

void User::print_location() {
    cout << "Latitude : " << _location->latitude() << endl;
    cout << "Longitude : " << _location->longitude() << endl;
}

void User::move(enum Directions direction) {
    switch (direction) {
        case UP:
            _location = _location->up();
            break;

        case RIGHT:
            _location = _location->right();
            break;

        case DOWN:
            _location = _location->down();
            break;

        case LEFT:
            _location = _location->left();
            break;

        default:
            _location = _location;
            break;
    }
    print_location();
}

unique_ptr<User>User::get(DataMapper &data_mapper, int const id) {
    return data_mapper.make_user(id);
}

void User::save(DataMapper &data_mapper) {
    data_mapper.save_user(*this);
}

int User::log_in(string &input_password) {
    auto password_to_compare = Password(input_password);
    if (*_password.get() == password_to_compare) {
        _is_logged_in = true;
        return 0;
    }
    return 1;
}

void User::log_out() {_is_logged_in = false;}

bool User::is_logged_in() {return _is_logged_in;}

Password &User::password() {return *_password.get();}

void User::set_password(std::string &password, bool is_encrypted) {
    _password = make_unique<Password>(password, is_encrypted);
}
