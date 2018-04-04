#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"
#include "figures.h"

TEST_CASE("Line length")
{
	Line line1(make_pair(0, 0), make_pair(3, 4));
	REQUIRE(line1.length() != 5.0);
}