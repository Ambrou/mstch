#ifndef _MSTCH_UTILS_H_
#define _MSTCH_UTILS_H_

#include <string>

namespace mstch {
    std::string strip_whitespace(const std::string& tmplt);
    std::string html_escape(std::string str);
}

#endif //_MSTCH_UTILS_H_
