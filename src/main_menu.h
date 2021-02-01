#pragma once
#include <stdint.h>
#include <string>
#include <vector>

extern std::vector<std::string> MENU_TEXT_ARR;

int32_t main_menu();
void construct_menu(int32_t menu_type);
std::string get_difficulty_str(uint8_t difficulty_num);
