/*
 *	Гидроцилиндр АЮИж.306
 *      По результатам расчетов
 *  Из кинематич расчета

 *  fi_max = 80.5 град
 */

#include <math.h>

float getATriangle()
{
// см Длина между оси ЦАПФ и верхнего уха гидроцилиндра
  float a = 124.9;

  return a;
}

/*
 *  Расчет длины штока
 */
float procHc(const float ug)
{
// см Длина между оси ЦАПФ и верхнего уха гидроцилиндра
  float a=124.9;
// см Длина между оси ЦАПФ и нижнего уха гидроцилиндра
  float b=42.97;
// 0.7315 рад = 41.913 град
  const float alpha0=0.7315;
  float Hc = sqrt((a*a+b*b)-2*a*b*cos(ug+alpha0));
  return Hc;
}

/*
 *  Расчет плеча
 */
float procPl(const float ug)
{
// см Длина между оси ЦАПФ и верхнего уха гидроцилиндра
  const float a=124.9;
// см Длина между оси ЦАПФ и нижнего уха гидроцилиндра
  const float b=42.97;
  const float alpha0=0.7315;
  float Hc = procHc(ug);
  float Pl = (a*b*sin(ug+alpha0))/Hc/43.0;
  return Pl;
}

/*
 *  Коэфф. пропроциональности
 */
float procKLn(const float ug)
{
// см Длина штока на угле 5 град
//  const float L0=98.5;
  // см Длина штока на угле 70 град
  const float Lmax=142.75;
  float Hc = procHc(ug);
  float KLn = sqrt(Lmax/Hc);
  return KLn;
}

/*!
 * \brief funcGcPl
 * \param a_rad
 * \return
 */
float funcGcPl(const float a_rad)
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
 * \brief funcGcMn
 * \param a_rad
 * \return
 */
float funcGcMn(const float a_rad)
{
    const float Xc = 0.774;
    const float Yc = 0.726;
    const float m_kg = 4129.0;
    const float Lc = sqrt((Xc*Xc) + (Yc*Yc));
    const float g = 9.81;
    const float Mn = (cos(asin(Yc*Yc) + a_rad) / Lc)*m_kg*Lc*g;
    return Mn;
}
