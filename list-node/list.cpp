#include  "list.h"

ListNode* buildListFromText(const std::string& filename) {
    std::ifstream in(filename);
    if (!in.is_open())
        throw std::runtime_error("Cannot open inlet file");

    std::vector<ListNode*> nodes;
    std::vector<long long> rand_indices;

    std::string line;
    while (std::getline(in, line)) {
        
    }
    return nullptr;
}
