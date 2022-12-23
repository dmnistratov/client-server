#ifndef COMMON_SERVER_FUNC_H
#define COMMON_SERVER_FUNC_H

#include <ctime>
#include <iostream>
#include <chrono>
#include <sstream>

//  YYYYMMDDThhmmss.fff например: 19851019T050107.333 - 19 октября 1985 года 5 часов 1 минута 7секунд 333 миллисекунды. Кодировка строк – UTF8.
const char* get_iso_date();
void fast_response_parser();
void slow_response_parser();

#endif 