#ifndef HASH_TABLE_H
#define HASH_TABLE_H
#include <unordered_map>
#include <string>

class HashTable {
private:
    std::unordered_map<int, std::string> table;

public:
    void insert(int key, const std::string& value);
    bool search(int key, std::string& result) const;
};

#endif
