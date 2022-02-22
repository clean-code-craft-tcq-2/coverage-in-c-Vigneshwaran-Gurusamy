#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include "test/catch.hpp"
#include "typewise-alert.h"

TEST_CASE("infers the breach according to limits") {
  REQUIRE(inferBreachLowerLimit(12, 20) == TOO_LOW);
  REQUIRE(inferBreachUpperLimit(20, 15) == TOO_HIGH);
  REQUIRE(inferBreachLowerLimit(15, 10) == NORMAL);
  REQUIRE(inferBreachUpperLimit(15, 20) == NORMAL);
}

TEST_CASE("Classify the cooling type and infer the breach") {
  REQUIRE(classifyTemperatureBreach(PASSIVE_COOLING, -4) == TOO_LOW);
  REQUIRE(classifyTemperatureBreach(PASSIVE_COOLING, 30) == NORMAL);
  REQUIRE(classifyTemperatureBreach(PASSIVE_COOLING, 42) == TOO_HIGH);
  
  REQUIRE(classifyTemperatureBreach(HI_ACTIVE_COOLING, -2) == TOO_LOW);
  REQUIRE(classifyTemperatureBreach(HI_ACTIVE_COOLING, 42) == NORMAL);
  REQUIRE(classifyTemperatureBreach(HI_ACTIVE_COOLING, 51) == TOO_HIGH);
  
  REQUIRE(classifyTemperatureBreach(MED_ACTIVE_COOLING, -4) == TOO_LOW);
  REQUIRE(classifyTemperatureBreach(MED_ACTIVE_COOLING, 38) == NORMAL);
  REQUIRE(classifyTemperatureBreach(MED_ACTIVE_COOLING, 42) == TOO_HIGH);
}

TEST_CASE("Evaluate the breach type and send alerts") {
  AlertTarget a1 = TO_EMAIL;
  AlertTarget a2 = TO_CONTROLLER;
  BatteryCharacter b;
  b.coolingType = PASSIVE_COOLING;
  checkAndAlert( a1, b, 40);
   
  checkAndAlert( a2, b, -2);
  
  checkAndAlert( a1, b, 20);
}
