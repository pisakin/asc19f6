/*
 *	Задающие воздействия синусов 100Hz
 */

#include <math.h>

/*
 * freq = 0.5 Hz amp = 18 deg
 */
short zvStep0_5HzAmp18(short *t, const float Tik)
{
  const short ampCod = 3277;
  const short N   = (short)(0.5 / Tik);

  if ((*t >= 0) && (*t < (4*N))) (*t)++; else *t = 0;

  if ((*t > (N/2)) && (*t <(3*N/2))) return  ampCod;
  if ((*t > (5*N/2)) && (*t < (7*N/2))) return -ampCod;
  return 0.0;
}

/*
 * freq = 0.5 Hz amp = 18 deg
 */
short zvStep0_35HzAmp18(short *t, const float Tik)
{
  const short ampCod = 3277;
  const short N   = (short)(0.35 / Tik);

  if ((*t >= 0) && (*t < (16*N))) (*t)++; else *t = 0;

  if ((*t > (2*N))  && (*t < (6*N))) return  ampCod;
  if ((*t > (10*N)) && (*t < (14*N))) return -ampCod;
  return 0.0;
}


/*
 * freq = 0.25 Hz amp = 18 deg
 */
short zvStep0_25HzAmp18(short *t, const float Tik)
{
  const short ampCod = 3277;
  const short N   = (short)(0.25 / Tik);

  if ((*t >= 0) && (*t < (16*N))) (*t)++; else *t = 0;

  if ((*t > (2*N))  && (*t < (6*N))) return  ampCod;
  if ((*t > (10*N)) && (*t < (14*N))) return -ampCod;
  return 0.0;
}

/*
 * freq = 0.25 Hz amp = 3 deg
 */
short zvStep0_25HzAmp3(short *t, const float Tik)
{
  const short ampCod = 546;
  const short N   = (short)(0.25 / Tik);

  if ((*t >= 0) && (*t < (16*N))) (*t)++; else *t = 0;

  if ((*t > (2*N))  && (*t < (6*N))) return  ampCod;
  if ((*t > (10*N)) && (*t < (14*N))) return -ampCod;
  return 0.0;
}

/*
 * freq = 0.25 Hz amp = 1 deg
 */
short zvStep0_25HzAmp1(short *t, const float Tik)
{
  const short ampCod = 182;
  const short N   = (short)(0.25 / Tik);

  if ((*t >= 0) && (*t < (16*N))) (*t)++; else *t = 0;

  if ((*t > (2*N))  && (*t < (6*N))) return  ampCod;
  if ((*t > (10*N)) && (*t < (14*N))) return -ampCod;
  return 0.0;
}

/*
 * freq = 0.25 Hz amp = 3 deg
 */
short zvStep0_25HzAmp0_5(short *t, const float Tik)
{
  const short ampCod = 91;
  const short N   = (short)(0.25 / Tik);

  if ((*t >= 0) && (*t < (16*N))) (*t)++; else *t = 0;

  if ((*t > (2*N))  && (*t < (6*N))) return  ampCod;
  if ((*t > (10*N)) && (*t < (14*N))) return -ampCod;
  return 0.0;
}
