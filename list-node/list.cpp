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
    std::ofstream out(filename, std::ios::binary);
    if (!out.is_open())
        throw std::runtime_error("Cannot open outlet file");

    std::vector<ListNode*> nodes;
    for (ListNode* cur = head; cur != nullptr; cur = cur->next)
        nodes.push_back(cur);

    size_t count = nodes.size();
    out.write(reinterpret_cast<char*>(&count), sizeof(count));

    std::unordered_map<ListNode*, size_t> index_map;
    for (size_t i = 0; i < count; ++i)
        index_map[nodes[i]] = i;

    for (size_t i = 0; i < count; ++i) {
        size_t data_size = nodes[i]->data.size();
        out.write(reinterpret_cast<char*>(&data_size), sizeof(data_size));

        out.write(nodes[i]->data.data(), data_size);

        int64_t rand_index = -1;
        if (nodes[i]->rand != nullptr)
            rand_index = index_map[nodes[i]->rand];

        out.write(reinterpret_cast<char*>(&rand_index), sizeof(rand_index));
    }
}

ListNode* deserialize(const std::string& filename) {
    std::ifstream in(filename, std::ios::binary);
    if (!in.is_open())
        throw std::runtime_error("Cannot open binary file");

    size_t count;
    in.read(reinterpret_cast<char*>(&count), sizeof(count));

    std::vector<ListNode*> nodes(count);
    std::vector<int64_t> rand_indices(count);

    for (size_t i = 0; i < count; ++i) {
        nodes[i] = new ListNode();

        size_t data_size;
        in.read(reinterpret_cast<char*>(&data_size), sizeof(data_size));

        nodes[i]->data.resize(data_size);
        in.read(&nodes[i]->data[0], data_size);

        in.read(reinterpret_cast<char*>(&rand_indices[i]), sizeof(int64_t));
    }

    for (size_t i = 0; i < count; ++i) {
        if (i > 0)
            nodes[i]->prev = nodes[i - 1];
        if (i + 1 < count)
            nodes[i]->next = nodes[i + 1];
    }

    for (size_t i = 0; i < count; ++i) {
        if (rand_indices[i] >= 0)
            nodes[i]->rand = nodes[rand_indices[i]];
    }

    return count > 0 ? nodes[0] : nullptr;
}