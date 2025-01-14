

#include <math.h>

/*!
 *  Расчет длины штока
 *  Алгоритм с тоски
 */
float funcPUPl(const float a_rad)
{
    // Координаты привязки
    const float Xa = 0.310;
    const float Ya = 0.250;
    const float La2 = (Xa*Xa)+(Ya*Ya);
    const float La = sqrt(La2);
    //
    const float Xb = 1.250;
    const float Yb = 0.065;
    const float Lb2 = (Xb*Xb)+(Yb*Yb);
    const float Lb = sqrt(Lb2);
    //
    const float alpha0 = acos(Xa/La) + acos(Xb/Lb);
    //
    const float Hc2 = Lb2 + (La2) - La*Lb*2.0*cos(alpha0 + a_rad);
    const float H = sin(acos((Hc2+(La2)-(Lb2)) / (2*La*sqrt(Hc2))))*La;
    //
    const float a0 = 0.0;
    const float Xmin = 4.5e-3;
    const float X = Xmin+sqrt(Hc2)-sqrt(La2+Lb2-2.0*La*Lb*cos(alpha0));
    const float X0 = Xmin - sqrt(La2+Lb2-2.0*La*Lb*cos(alpha0)) + sqrt(La2+Lb2-2.0*La*Lb*cos(a0 + alpha0));
    //
    return H;
}

/*!
 *  Рассчет момента неуравновешенности
 */
float funcPUMn(const float a_rad)
{
    const float Xc = 0.774;
    const float Yc = 0.726;
    const float m_kg = 4129.0;
    const float Lc = sqrt((Xc*Xc) + (Yc*Yc));
    const float g = 9.81;
    const float Mn = (cos(asin(Yc*Yc) + a_rad) / Lc)*m_kg*Lc*g;
    return Mn;
}
