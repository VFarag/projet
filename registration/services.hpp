#pragma once

#include "models.hpp"

#include <memory>

class World;
class DataMapper;


std::unique_ptr<User> make_user(World *const world);

std::unique_ptr<User> get_user(DataMapper &DataMapper, int const id);
