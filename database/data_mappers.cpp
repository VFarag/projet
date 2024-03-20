#include "data_mappers.hpp"

#include "../location/models.hpp"
#include "../registration/models.hpp"

using namespace std;


Mapper::Mapper(std::unique_ptr<DBManager> &&database_manager):
    _database_manager(move(database_manager)) {}

LabyrinthBlockMapper::LabyrinthBlockMapper(
    unique_ptr<DBManager> &&database_manager):
        Mapper(move(database_manager)) {}


void LabyrinthBlockMapper::set_blocks(Labyrinth &labyrinth) {
    auto repo = _database_manager->repositories().at("maze");
    auto data = _database_manager->get_full_repo(repo);
    vector<vector<unique_ptr<Location>>> locations;

    locations.resize(data.size());
    for (auto i(0); i < data.size(); ++i) {
        locations[i].resize(data.size());
        for (auto j(0); j < data.size(); j++) {
            locations[i][j] = make_unique<Location>(j, i);
        }
    }
    labyrinth.set_locations(move(locations));
}


DataMapper::DataMapper(unique_ptr<DBManager> &&database_manager):
    Mapper(move(database_manager)) {}

DBManager &Mapper::database_manager() {
    return *_database_manager;}

string DataMapper::get_world_data(World &world) {
    // Transformation d'un objet en une chaine
    // de caractères (souvent en format JSON)
    // On parle de serialisation.
    auto width = to_string(world.width());
    auto height = to_string(world.height());
    auto id = to_string(world.id());
    return id + " " + width + " " + height;
}

shared_ptr<World> DataMapper::make_world(int id) {
    auto worlds_repo = database_manager().repositories().at("worlds");
    auto values = database_manager().get_values(worlds_repo, id);
    return make_world(values);
}

shared_ptr<World> DataMapper::make_world(vector<string> &values) {
    // Transformation d'une chaine de caractères
    // en objet. On parle de deserialisation.
    if (values.empty()) {return nullptr;}
    auto world_id = stoi(values[0]);
    auto width = stoi(values[1]);
    auto world = make_shared<World>(world_id, width);
    World::objects.insert(world);
    return world;
}

string DataMapper::get_user_data(User &user) {
    auto id = to_string(user.id());
    auto world_id = to_string(user.world().id());
    auto latitude = to_string(user.location()->latitude());
    auto longitude = to_string(user.location()->longitude());
    auto password = user.password().str();
    return id + " " + world_id + " " + latitude + " " + longitude + " " + password;
}

unique_ptr<User> DataMapper::make_user(int id) {
    auto users_repo = database_manager().repositories().at("users");
    auto values = database_manager().get_values(users_repo, id);
    return make_user(values);
}

unique_ptr<User> DataMapper::make_user(vector<string> &values) {
    if (values.empty()) {return nullptr;}
    auto user_id = stoi(values[0]);
    auto world_id = stoi(values[1]);
    auto latitude = stoi(values[2]);
    auto longitude = stoi(values[3]);
    auto password = values[4];

    World *user_world = World::get(*this, world_id).get();
    auto user = make_unique<User>(user_id, user_world, latitude, longitude);
    if (not password.empty()) {
        user->set_password(password, true);
    }
    user->log_out();
    return user;
}

void DataMapper::save_world(World &world) {
    auto worlds_repo = database_manager().repositories().at("worlds");
    if (not world.id()) {
        world.set_id(database_manager().get_next_id(worlds_repo));
    }

    auto db_values = database_manager().get_values(worlds_repo, world.id());
    if (not db_values.empty()) {
        database_manager().destroy(worlds_repo, world.id());
    }

    auto data = get_world_data(world);
    database_manager().write(worlds_repo, data);
}

void DataMapper::save_user(User &user) {
    auto users_repo = database_manager().repositories().at("users");
    if (not user.id()) {
        user.set_id(database_manager().get_next_id(users_repo));
    }

    auto db_values = database_manager().get_values(users_repo, user.id());
    if (not db_values.empty()) {
        database_manager().destroy(users_repo, user.id());
    }

    auto data = get_user_data(user);
    database_manager().write(users_repo, data);
}
