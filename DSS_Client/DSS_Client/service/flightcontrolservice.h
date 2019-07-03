#ifndef FLIGHTCONTROLSERVICE_H
#define FLIGHTCONTROLSERVICE_H
/**
 * @brief The FlightControlService class 用于飞控显示相关服务
 * @author zhaozihe
 */

class FlightControlService
{
public:
    FlightControlService();

    double Kph2Knots(double kph); // 将km/h转为节
};

#endif // FLIGHTCONTROLSERVICE_H
