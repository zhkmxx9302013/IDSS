#include "flightcontrolservice.h"

FlightControlService::FlightControlService()
{

}

/**
 * @brief FlightControlService::Kph2Knots
 * @param kph
 * @return knots
 */
double FlightControlService::Kph2Knots(double kph)
{
    return kph * 0.539956803;
}
