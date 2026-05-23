#include "hash_table.h"

void HashTable::insert(int key, const std::string& value) {
    table[key] = value;
}

bool HashTable::search(int key, std::string& result) const {
    auto it = table.find(key);
    if (it != table.end()) {
        result = it->second;
        return true;
    }
    return false;
}
