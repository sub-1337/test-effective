#include "list-node.h"
#include "list.h"


int main() {
    try {
        ListNode* head = buildListFromText("inlet.in");
        serialize(head, "outlet.out");
        ListNode* restored = deserialize("outlet.out");
    }
    catch (const std::exception& ex) {
        std::cerr << "Error: " << ex.what() << std::endl;
    }
    return 0;
}