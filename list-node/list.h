#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>

struct ListNode {
    ListNode* prev = nullptr;
    ListNode* next = nullptr;
    ListNode* rand = nullptr;
    std::string data;
};