
#include <tut/tut_cppunit_reporter.hpp>
#include "tests.hpp"

namespace tut
{
    test_runner_singleton runner;
}

int main()
{
	tut::cppunit_reporter reporter("tests/results/results.xml");
	tut::runner.get().set_callback(&reporter);

	tut::runner.get().run_tests();

	return !reporter.all_ok();
}
