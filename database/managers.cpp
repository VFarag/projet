#include "managers.hpp"

#include <memory>
#include <fstream>
#include <sstream>

using namespace std;


DBManager::DBManager(
    string const &base_path, map<string, string> const &repositories
): base_path(base_path), _repositories(repositories) {
    if (not filesystem::is_directory(base_path)) {
        filesystem::create_directory(base_path);
    }
    for (auto repository: repositories) {
        auto path = base_path + repository.second;
        if (not filesystem::exists(path)) {
            ofstream MyFile(path);
            MyFile.close();
        }
    }
}

void DBManager::write(string const &repository, string const &data) {
    ofstream MyFile(base_path / repository, ios::app);
    MyFile << data << endl;
    MyFile.close();
}

int DBManager::get_next_id(string const &repository) {
    ifstream file_in(base_path / repository);
    string line;
    int max_id = 0;
    while (getline(file_in, line)) {
        stringstream ss(line);
        int id;
        ss >> id;
        if (id > max_id) {max_id = id;}
    }
    file_in.close();
    return max_id + 1;
}

void DBManager::destroy(string const &repository, int const id) {
    auto const temp_file_name = "xxtempfilexx.txt";
    ifstream file_in(base_path / repository);
    ofstream file_out(temp_file_name);
    string line;
    string id_str = to_string(id);

    while (getline(file_in, line)) {
        if (line.substr(0, id_str.size()) != id_str) {
            file_out << line << "\n";}}
    file_in.close();
    file_out.close();
    filesystem::remove(base_path / repository);
    filesystem::rename(temp_file_name, base_path / repository);
}

vector<string> DBManager::get_full_repo(string const &repository) {
    ifstream reader(base_path / repository);
    string buffer;
    vector<string> values;
    while (getline(reader, buffer)) {
        stringstream ss(buffer);
        string word;
        ss >> word;
        values.push_back(word);
        while (ss >> word) {
            values.push_back(word);
        }
    }
    reader.close();
    return values;
}

vector<string> DBManager::get_values(string const &repository, int const id) {
    ifstream reader(base_path / repository);
    string buffer;
    vector<string> values;
    while (getline(reader, buffer)) {
        stringstream ss(buffer);
        string word;
        ss >> word;
        if (word == to_string(id)) {
            values.push_back(word);
            while (ss >> word) {
                values.push_back(word);}}}
    reader.close();
    return values;
}

map<string, string> const DBManager::repositories() {
    return _repositories;
}
