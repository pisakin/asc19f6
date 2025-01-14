/*!
 * \file torque.c
 * Модуль рассчет моментов
 * Момент инерции нагрузки Jn, кг*м^2
 * Статический момент сопротивления Mtr, Н*м 100
 * Статический момент неуровновешенности Mn, Н*м 16700
 */

#include <math.h>

/*
 *
 */
void procTorque(const short ug)
{
//    const float Spr
}

/*!
 *  Рассчет момента неуравновешенности
 */
float procMn(const float a_rad)
{
    const float Xc = 0.774;
    const float Yc = 0.726;
    const float m_kg = 4129.0;
    const float Lc = sqrt((Xc*Xc) + (Yc*Yc));
    const float g = 9.81;
    const float Mn = cos(asin((Yc*Yc) / Lc))*m_kg*Lc*g;
    return Mn;
}
