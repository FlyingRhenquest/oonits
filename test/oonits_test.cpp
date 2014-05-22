/*
 * Oonits test -- populate a vector with various units
 */

#include <celcius.hpp>
#include <converters.hpp>
#include <cppunit/extensions/HelperMacros.h>
#include <kilometers.hpp>
#include <math.h>
#include <meters.hpp>
#include <miles.hpp>
#include <vector>

class oonits_test : public CppUnit::TestFixture {

  CPPUNIT_TEST_SUITE(oonits_test);
  CPPUNIT_TEST(driver);
  CPPUNIT_TEST_SUITE_END();

  typedef std::vector<fr::oonits::meters> meter_vector;

  /*
   * Magic:
   *
   * This function is templatized, will therefore convert any
   * unit for which there is a converter to meters. So I can
   * feed it miles, meters or kilometers, but celcius will
   * result in a compilation error.
   */

  template <typename unit>
  void populate_vector(unit m, meter_vector *v)
  {
    v->push_back(fr::oonits::converter<fr::oonits::meters>()(m));
  }

  /**
   * Equalish to the precision I care about...
   */

  bool equalish(double left, double right)
  {
    return fmax(left, right) - fmin(left,right) < .1;
  }

public:

  /*
   * Test driver; populates vector with various units
   */  

  void driver()
  {
    meter_vector results;
    std::vector<double> inputs = {1.0, 10.0, 12.25};
    std::vector<double> expected = {1.0, 1000.0, 1609.34,
				    10.0, 10000.0, 16093.4,
				    12.25, 12250.0, 19714.5};
    for (double input : inputs) {
      populate_vector(fr::oonits::meters(input), &results);
      populate_vector(fr::oonits::kilometers(input), &results);
      populate_vector(fr::oonits::miles(input), &results);
      // Will result in a surprisingly informative error message
      // in gcc 4.9.0
      // populate_vector(fr::oonits::celcius(input), &results);
    }
    for (int i = 0; i < expected.size(); ++i) {
      std::cout << "Expected: " << expected[i] << " result: " << results[i].units << std::endl;
      CPPUNIT_ASSERT(equalish(expected[i], results[i].units));
    }
  }

};

CPPUNIT_TEST_SUITE_REGISTRATION(oonits_test);
