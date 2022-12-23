#include "common_server_func.h"

const char* get_iso_date(){
    auto now =  std::chrono::system_clock::now();
    auto seconds = std::chrono::time_point_cast<std::chrono::seconds>(now);
    auto fraction = now - seconds;
    time_t cnow =  std::chrono::system_clock::to_time_t(now);
    auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(fraction);
	std::tm* timePtr = localtime(&cnow);
    std::ostringstream result;
    result << timePtr->tm_year + 1900 << timePtr->tm_mon + 1 << timePtr->tm_mday << "T" <<  timePtr->tm_hour << timePtr->tm_min << timePtr->tm_sec << "." << milliseconds.count() << std::endl;
    std::cout << result.str() << std::endl;
}

int main(){
    std::cout << get_iso_date() << std::endl;
    return 0;
}