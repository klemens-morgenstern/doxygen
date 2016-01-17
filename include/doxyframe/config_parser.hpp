/**
 * @file   config_parser.hpp
 * @date   15.01.2016
 * @author Klemens
 *
 * Published under [Apache License 2.0](http://www.apache.org/licenses/LICENSE-2.0.html)
 */

#ifndef CONFIG_PARSER_HPP_
#define CONFIG_PARSER_HPP_

#include <unordered_map>
#include <string>
#include <vector>
#include <boost/filesystem.hpp>

namespace DoxyFrame
{
namespace Config
{

struct RawOption
{
	std::string file_name;
	std::size_t line_nr;

	std::string comment;
	std::vector<std::string> data;
};

struct RawConfig : std::unordered_map<std::string, RawOption>
{
	std::string startComment;
	std::string endComment;

	RawConfig parse(const boost::filesystem::path& file_name);
};




}
}



#endif /* CONFIG_PARSER_HPP_ */
