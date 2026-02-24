#include  "list.h"

ListNode* buildListFromText(const std::string& filename) {
    std::ifstream in(filename);
    if (!in.is_open())
        throw std::runtime_error("Cannot open inlet file");

    std::vector<ListNode*> nodes;
    std::vector<long long> rand_indices;

    std::string line;
    while (std::getline(in, line)) {
        size_t sep = line.rfind(';');
        if (sep == std::string::npos)
            throw std::runtime_error("Invalid input format");

        std::string data = line.substr(0, sep);
        long long rand_index = std::stoll(line.substr(sep + 1));

        ListNode* node = new ListNode();
        node->data = data;

        nodes.push_back(node);
        rand_indices.push_back(rand_index);
    }

    size_t n = nodes.size();

    for (size_t i = 0; i < n; ++i) {
        if (i > 0)
            nodes[i]->prev = nodes[i - 1];
        if (i + 1 < n)
            nodes[i]->next = nodes[i + 1];
    }

    for (size_t i = 0; i < n; ++i) {
        if (rand_indices[i] >= 0) {
            if (rand_indices[i] >= (long long)n)
                throw std::runtime_error("Invalid rand index");
            nodes[i]->rand = nodes[rand_indices[i]];
        }
    }

    return n > 0 ? nodes[0] : nullptr;
}

void serialize(ListNode* head, const std::string& filename)
{

}