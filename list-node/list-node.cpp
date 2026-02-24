#include "list-node.h"
#include "list.h"


int main() {
    try {
        ListNode* head = buildListFromText("inlet.in");
    }
    catch (const std::exception& ex) {
        std::cerr << "Error: " << ex.what() << std::endl;
    }
    return 0;
}