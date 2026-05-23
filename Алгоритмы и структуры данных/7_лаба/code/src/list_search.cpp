#include "list_search.h"

bool listSearch(const std::list<int>& lst, int target) {
    for (auto it = lst.begin(); it != lst.end(); ++it) {
        if (*it == target) return true;
    }
    return false;
}
