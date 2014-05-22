/* Copyright 2014 Bruce Ide
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 * Oonits demo code - converters.
 */

#ifndef _HPP_OONITS_CONVERTERS
#define _HPP_OONITS_CONVERTERS

#include <kilometers.hpp>
#include <meters.hpp>
#include <miles.hpp>

namespace fr {

  namespace oonits {

    /*
     * First create a empty generic templatized struct like so... 
     */

    template <typename convert_to>
    struct converter {
      /*
       * I could probably use some template trickery to cause this
       * to always fail to compile if you ever actually try to
       * compile one. It probably will anyway, but it'd be nice
       * if it would tell you that's why it failed.
       */
    };

    /**
     * Now create specialized instances with each type you want
     * to convert TO...
     */
    
    template <>
    struct converter<meters> {
      // Inside, converters for all types you can convert FROM

      // Include a conversion FROM the same type TO the same type...
      meters operator()(const meters &m)
      {
	return m;
      }
 
      meters operator()(const kilometers &m)
      {
	return meters(m.units * 1000.0);	
      }
      
      meters operator()(const miles &m)
      {
	return meters(m.units * 1609.344);
      }

    };

    /**
     * Do one of these for all your conversion types
     */

    template<>
    struct converter<kilometers> {
      kilometers operator()(const kilometers &m)
      {
	return m;
      }

      kilometers operator()(const meters &m)
      {
	return kilometers(m.units / 1000.0);
      }

      kilometers operator()(const miles &m)
      {
	return kilometers(m.units * 1.60934);
      }
      
    };


    template<>
    struct converter<miles> {

      miles operator()(const miles &m)
      {
	return m;
      }

      miles operator()(const meters &m)
      {
	return miles(m.units * .000621371);
      }

      miles operator()(const kilometers &m)
      {
	return miles(m.units * .621371);
      }

    };

  }

}

#endif
