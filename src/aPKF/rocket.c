/*
 * 95Я6(57Э6-Е)   92.0 кг
 * РМ 95Я6-2М   107.0 кг
 * 57Э6М-Е   115.0 кг
 * 95Я6СМ   115.0 кг
 * РМ № 1   0.0 кг
 * РМ № 2   0.0 кг
 * Пакет малогабаритных ЗУР   122.0 кг
 * 19Ф6В   350.0 кг
 * РМ № 3   0.0 кг
 * Резерв   0.0 кг
 * Резерв   0.0 кг
 * 19Ф6З   141.0 кг
 * 19Ф6Р   144.0 кг
 * Резерв   0.0 кг
 * Резерв   0.0 кг
 */

float getMassKg95Ya6()   { return 92.0;   }
float getMassKg95Ya62M() { return 107.0;  }
float getMassKg57E6M()   { return 115.0;  }
float getMassKg95Ya6CM() { return 115.0;  }
float getMassKgPM1()     { return 0.0;    }
float getMassKgPM2()     { return 0.0;    }
float getMassKgPAKMZUP() { return 122.0;  }
float getMassKg19F6B()   { return 350.0;  }
float getMassKgPM3()     { return 0.0;    }
float getMassKg19F63()   { return 141.0;  }
float getMassKg19F6P()   { return 141.0;  }


/*
 *	Получить массу ракеты в зависимости от типа
 */
float getMassRocket(const short type)
{
  switch( type ) {
  case 0:  return 0.0;
  case 1:  return 92.0;
  case 2:  return 107.0;
  case 3:  return 115.0;
  case 4:  return 115.0;
  case 5:  return 0.0;
  case 6:  return 0.0;
  case 7:  return 122.0;
  case 8:  return 350.0;
  case 9:  return 0.0;
  case 10: return 0.0;
  case 11: return 0.0;
  case 12: return 141.0;
  case 13: return 144.0;
  case 14: return 0.0;
  case 15: return 0.0;
  default: return 0.0;
  }
}


/*
 * Получить число перестановок N (включая пустую)
 * N - кол-во загруженных ракет
 * N! = (N-1)! * N
 */
int getNRocket(const short N)
{
  int i = 1;
  int fact = 1;
  for (i = 1; i<N; i++) fact *= i;
  return (fact * N);
}

/*
 * Получить число размещенией
 * Под числом размещений понимают количество элементов которыми можно записать в ряд подпоследовательность из К
 * элементов некоторый перестановки из N элементов
 * N - кол-во типов ракет
 * K - кол-во ракет на пусковой
 *
 * N! / (N-K)!
 */
int getANKRocket(const short N, const short K)
{
  int i = 1;
  int fact1 = 1, fact2 = 1;
  for (i = 1; i<=N; i++) fact1 *= i;
  for (i = 1; i<=(N-K); i++) fact2 *= i;

  return (int)(fact1 / fact2);
}

/*
 * Получить число сочетаний
 * Под числом сочетаний понимают кол-во вариантов, которыми можно выбирать К элементов из некоторого множества,
 * состоящего из N элементов. При этом последовательности из одинаковых элементов, но с различным их порядком
 * следования считаются равными
 */
int getCNKRocket(const short N, const short K)
{
  int i = 1;
  int fact1 = 1, fact2 = 1, fact3 = 1;
  for (i = 1; i<=N; i++) fact1 *= i;
  for (i = 1; i<=(N-K); i++) fact2 *= i;
  for (i = 1; i<=K; i++) fact3 *= i;

  return (int)(fact1 / (fact2 * fact3));
}
