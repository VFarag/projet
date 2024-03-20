#pragma once

#include "data_mappers.hpp"

#include <memory>


std::unique_ptr<DataMapper> make_data_mapper(
    std::string const &base_path,
    std::map<std::string, std::string> const &repositories
);

std::unique_ptr<LabyrinthBlockMapper> make_labyrinth_block_mapper(
    std::string const &base_path,
    std::map<std::string, std::string> const &repositories
);
