#include "services.hpp"
#include "managers.hpp"

using namespace std;


unique_ptr<DataMapper> make_data_mapper(
    string const &base_path,
    map<string, string> const &repositories
) {
    auto db_manager = make_unique<DBManager>(
        base_path, repositories
    );
    return make_unique<DataMapper>(move(db_manager));
}


unique_ptr<LabyrinthBlockMapper> make_labyrinth_block_mapper(
    string const &base_path,
    map<string, string> const &repositories
) {
    auto db_manager = make_unique<DBManager>(
        base_path, repositories
    );
    return make_unique<LabyrinthBlockMapper>(move(db_manager));
};
