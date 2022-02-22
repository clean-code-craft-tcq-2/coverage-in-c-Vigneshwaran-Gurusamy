#include "typewise-alert.h"
#include <stdio.h>

int limits[NUMBER_OF_COOLING_TYPES][NUMBER_OF_TEMP_LIMITS] = {{PASSIVE_COOLING_LOWER_LIMIT, PASSIVE_COOLING_UPPER_LIMIT}, 
                                                              {HI_ACTIVE_COOLING_LOWER_LIMIT, HI_ACTIVE_COOLING_UPPER_LIMIT}, 
                                                              {MED_ACTIVE_COOLING_LOWER_LIMIT, MED_ACTIVE_COOLING_UPPER_LIMIT}};
char alertMsgForEmail[NUMBER_OF_BREACH_TYPES][100] = {"Hi, the temperature is Normal\n"
                                                   "Hi, the temperature is too low\n",
                                                   "Hi, the temperature is too High\n"};
void (*AlertTargetfp[NUMBER_OF_ALERT_TARGETS])(BreachType) = {sendToController, sendToEmail};

BreachType inferBreach(double value, double lowerLimit, double upperlimit) 
{
  double BreachValue;
  if(value < lowerLimit)
  {
    BreachValue = TOO_LOW;
  }
  else if(value > upperLimit)
  {
    BreachValue = TOO_HIGH;
  }
  else
  {
    BreachValue = NORMAL;
  }
  return BreachValue;
}

BreachType classifyTemperatureBreach(CoolingType coolingType, double temperatureInC) 
{
  int lowerLimit = limits[coolingType][LOWERLIMIT_IDX];
  int upperLimit = limits[coolingType][UPPERLIMIT_IDX];
  return inferBreach(temperatureInC, lowerLimit, upperLimit);
}

void checkAndAlert(AlertTarget alertTarget, BatteryCharacter batteryChar, double temperatureInC) 
{
    BreachType breachType = classifyTemperatureBreach( batteryChar.coolingType, temperatureInC);
    AlertTargetfp[alertTarget](breachType);
}

void printRecepientAndAlertMsgForEmail(const char* receiver, BreachType breachType)
{
  printf("To: %s\n", receiver);
  printf("%s", alertMsgForEmail[breachType]);
}

void sendToController(BreachType breachType) 
{
  const unsigned short header = 0xfeed;
  printf("%x : %x\n", header, breachType);
}

void sendToEmail(BreachType breachType) {
  const char* recepient = "a.b@c.com";
  printRecepientAndAlertMsgForEmail(recepient, breachType);
}
