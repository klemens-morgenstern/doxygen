/**
 * @file   boost_optional.hpp
 * @date   16.01.2016
 * @author Klemens
 *
 * Published under [Apache License 2.0](http://www.apache.org/licenses/LICENSE-2.0.html)
 */

#ifndef CEREAL_BOOST_OPTIONAL_HPP_
#define CEREAL_BOOST_OPTIONAL_HPP_

#include <cereal/cereal.hpp>

namespace cereal
{
 //! Saving for boost::variant
  template <class Archive, typename Type> inline
  void CEREAL_SAVE_FUNCTION_NAME( Archive & ar, boost::optional<Type> const & optional )
  {
    bool set = optional;
    ar( CEREAL_NVP_("set",  set) );
    if (set)
    	ar( CEREAL_NVP_("data", *optional) );
  }

  //! Loading for boost::variant
  template <class Archive, typename Type> inline
  void CEREAL_LOAD_FUNCTION_NAME( Archive & ar, boost::optional<Type> & optional )
  {

	bool set = false;
	ar( CEREAL_NVP_("set",  set) );
	if (set)
	{
		Type value;
		ar( CEREAL_NVP_("data", value));
		optional = std::move(value);
	}
	else
		optional = boost::none;
  }
}


#endif /* CEREAL_BOOST_OPTIONAL_HPP_ */
