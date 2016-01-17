/**
 * @file   error_log.hpp
 * @date   17.01.2016
 * @author Klemens
 *
 * Published under [Apache License 2.0](http://www.apache.org/licenses/LICENSE-2.0.html)
 */

#ifndef ERROR_LOG_HPP_
#define ERROR_LOG_HPP_

#include <iostream>

namespace DoxyFrame
{
namespace Log
{


//this implementation is temporary, currently the most easy format implementation possible. This is so the style is centrally organized
inline std::ostream& Error()
{
	return std::cerr <<  __FILE__ << "(" << __LINE__ << ") Error: ";
}

inline std::ostream& Error(const std::string &file_name, std::size_t line_nr = 0)
{
	return std::cerr <<  file_name << "(" << line_nr << ") Error: ";
}

inline std::ostream& Warn()
{
	return std::cerr <<  __FILE__ << "(" << __LINE__ << ") Warn: ";
}

inline std::ostream& Warn(const std::string &file_name, std::size_t line_nr = 0)
{
	return std::cerr <<  file_name << "(" << line_nr << ") Warn: ";
}

inline std::ostream& Note()
{
	return std::cerr <<  __FILE__ << "(" << __LINE__ << ") Note: ";
}

inline std::ostream& Note(const std::string &file_name, std::size_t line_nr = 0)
{
	return std::cerr <<  file_name << "(" << line_nr << ") Note: ";
}

}
}



#endif /* ERROR_LOG_HPP_ */
