#include "services.hpp"

using namespace std;


unique_ptr<User> make_user(World *const world) {
    return make_unique<User>(world);
}

unique_ptr<User> get_user(DataMapper &data_mapper, int const id) {
    return User::get(data_mapper, id);
}
