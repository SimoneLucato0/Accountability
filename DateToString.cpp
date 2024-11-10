#include "DateToString.h"

std::string DateToString(time_t t){
    tm* lt = std::localtime(&t);
    return std::to_string(lt->tm_mday) + "/" +  std::to_string(1 + lt->tm_mon) + "/" + std::to_string(1900 + lt->tm_year);
}
