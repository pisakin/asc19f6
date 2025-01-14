#ifndef CASC19F6_H
#define CASC19F6_H

class CASC19F6
{
public:
    CASC19F6();
private:
    float Vsin;			//	Переменная автоколебаний
    float VAsin;		//	Амплитуда автоколебаний режима ЗА
    float VFsin;			//	Частота автоколебаний режима ЗА
    float L_Asin;			//	Амплитуда автоколебаний режима Пу Л
    float L_Fsin;		//	Частота автоколебаний режима Пу Л
    float P_Asin;			//	Амплитуда автоколебаний режима Пу Пр
    float P_Fsin;		//	Частота автоколебаний режима Пу Пр
    float VTsin;			//
    float VPsin;			//
    ///
    float VSk_T;
    float VSk_G;
    float VSk_W;
    ///	Переменные торможения
    float VaUD;			//	Поправка на угол торможения перед упором в режим "ЗА"
    float VaLUD;        //	Поправка на угол торможения перед упором в режим "Пу Л"
    float VaPUD;        //	Поправка на угол торможения перед упором в режим "Пу Пр"
    float VaUporV;     //	Верхний жесткий упор ЗА 85гр
    float VaUporN;    //	Нижний жесткий упор -1.5гр
    float VrLUporV;       //	Верхний жесткий упор Пу Л 85гр
    float VrLUporN;     //	Нижний жесткий упор Пу Л 6гр
    float VrPUporV;       //	Верхний жесткий упор Пу Пр 85гр
    float VrPUporN;     //	Нижний жесткий упор Пу Пр 6гр
    float UporSk;		//	Ограничение скорости подхода к упорам в режиме "ЗА" 19.5гр/с
    float UporLSk;		//	Ограничение скорости подхода к упорам в режиме Пу Л 2 гр/с
    float UporPSk;		//	Ограничение скорости подхода к упорам в режиме Пу Пр 2 гр/с
    float OgrSk;			//	Ограничение скорости 40.6 гр/с
    float VUskTa;     //  ускорение торможения в режима ЗА
    float VUskTrL;     //  ускорение торможения в режиме Пу Л
    float VUskTrP;     //  ускорение торможения в режимре Пу Пр
    int znSk ;				//	Знак скорости перед началом торможения
    ///	Переменные баланса
    float VBal;          	//  Баланс ЗА
    float VaBal;		//  Баланс ЗА
    float VrLBal;        	//  Баланс Пу Л
    float VrLBal0;       	//  Баланс Пу Л
    float VrPBal;        	//  Баланс Пу Пр
    float VrPBal0;       	//  Баланс Пу Пр
    ///	Задатчик интенсивности 2
    float Z2V_dmax;		//
    float Z2Va_dmax;		//
    ///	Апендикс сверху
    float Z2V_D;			//
    float Z2Va_D;		//
    float Z2VrL_D;		//
    float Z2VrP_D;		//
    float Z2V_Fm;		//
    float Z2Va_Fm;		//

    float Z2V_F2;			//
    float Z2Va_F2;			//
    float Z2VrL_F2;		//
    float Z2VrP_F2;		//	Ограничение ускорения (в лгоритме делится на 1000)
    float Z2V_dmin;		//	для сброса признака "переброс"
    float Z2V_Usk;			//
    float Z2V_Sk;				//
        float Z2V_UK;			//	Cкорость и ускорение из алгоритма ЗИ2
    int   Z2V_P;				//	Признак "переброс"
        float Z2V_W1;				//
    float Z2V_W2;				//
        float Z2V_W3;				//
    float Z2V_Ws;				//
        float Z2V_Out;			//
    float Z2V_S; 				//
        //
        float AFPV_Fmax;		//
    float AFPV_Uo;			//
        float AFPV_Y;			// 40 град - пороговое значение скачка после которого макс. Ускfloat AFPV_W1			//
    float AFPV_W2;			//
        //  фазы режима ЗА
    float fazaVnaOs;			//	Фаза ошибки ЗА
    float fazaVnaTU;			//	Фаза текущего угла ЗА
    float fazaVnaTS;			//	Фаза текущей скорости ЗА
    float fazaVnaUp;			//	Фаза управления ЗА
        //	фазы режима Пу Л
    float fazaVnrLOs;			//	Фаза ошибки Пу Л
    float fazaVnrLTU;			//	Фаза текущего угла Пу Л
    float fazaVnrLTS;			//	Фаза текущей скорости Пу Л
    float fazaVnrLUp;			//	Фаза управления Пу Л
        //	фазы режима Пу Пр
    float fazaVnrPOs;			//	Фаза ошибки Пу Пр
    float fazaVnrPTU;			//	Фаза текущего угла Пу Пр
    float fazaVnrPTS;			//	Фаза текущей скорости Пу Пр
    float fazaVnrPUp;			//	Фаза управления Пу Пр
        ///	Задатчик интенсивности 1
        float VZ1MaxOgr;		//	Максимальное ограничение входного сигнала
    float VZ1MinOgr;	//	Минимальное ограничение входного сигнала
        float VZ1St;       		//	Скорость(шаг) нарастания входного сигнала
        float VZ1StR;		//	Скорость нарастания входного сигнала для реж. Р
    float VZ1StA;  		//	Скорость нарастания входного сигнала для реж. А
    ///	Задатчик интенсивности 2
    float VZ2MaxOgr;		//	Максимальное ограничение входного сигнала
    float VZ2MinOgr;	//	Минимальное ограничение входного сигнала
    float VZ2St;     	//	Скорость(шаг) нарастания входного сигнала
    //	Диференцирующе - сглаживающее устройство 2
    float VD2K;				//	Переключатель фильтра 1-2 порядка
        float VD2T;			//	Постоянная времени фильтра
    float VD2ksi;			//	Коэффициент демпфирования
    //	Корректирующее звено
    float VTk1;				//	Постоянная времени корректирующего звена
    float VrLTk1;			//	Постоянная времени корректирующего звена
    float VrPTk1;			//	Постоянная времени корректирующего звена
    float Vksi;   			//	Коэффициент демпфирования
    float Vgam;				//	Отношение пост.вр. числителя к знаменателю
    float VrLgam;			//	Отношение пост.вр. числителя к знаменателю
    float VrPgam;			//	Отношение пост.вр. числителя к знаменателю
    float VKlk;			//	Ключ переключения каналов рад.*/
    float VKk1;				//
    float VrLKk1;				//
    float VrPKk1;				//
    float VK1;				//
    float VK2;				//
    float Vd1;				//
    ///	Интегратор
    float VKi;				//
    float VrLKi;				//
    float VrPKi; 			//	Коэффициент интегратора
    float VOI;				//	Ограничение интегратора рад.
    float VKl1;			//	Первый ключ рад.
    float VKl2;			//	Второй ключ рад.
    float VKend;			//	Коэффициент
    float VOend;		//	Последнее ограничение
    ///
    float VOZ1;				//	Предыдущий шаг задатчика интенсивности
    float VOZ2;				//	Предыдущий шаг задатчика интенсивности
    float VOD21;				//	Первый предыдущий шаг ДСУ2
    float VOD22;				//	Второй предыдущий шаг ДСУ2
    float VOKor;				//	Предыдущий шаг корректирующего звена
    float VOInt; 				//	Предыдущий шаг интегратора
        ///	Параметры ждущего одновибратора
        // Формирователь импульсов
        //	Переменные в зависимости от режима
    float TOV;				//	Время действия импульса
    float AOVV;			//	Величина 1 импульса
    float AOVN; 			//	Величина 2 импульса
    // Режим А
    float TOVa;			//	Время действия импульса
    float AOVaV;			//	Величина 1 импульса в режиме ЗА
    float AOVaN;		//	Величина 2 импульса в режиме ЗА
    // Режим Р
    float TOVr;			//	Время действия импульса
    float AOVrV;			//	Величина 1 импульса в режиме Р
    float AOVrN;			//	Величина 2 импульса в режиме Р
    //	Пу Л
    float TOVr_L0;			//	Время действия импульса
    float AOVrV_L0;		//	Величина 1 импульса в режиме Р - О ракет Пу Л
    float AOVrN_L0;		//	Величина 2 импульса в режиме Р - О ракет Пу Л
    float TOVr_L1; 		//	Время действия импульса
    float AOVrV_L1;		//	Величина 1 импульса в режиме Р - 1 ракет Пу Л
    float AOVrN_L1;		//	Величина 2 импульса в режиме Р - 1 ракет Пу Л
    float TOVr_L2;			//	Время действия импульса
    float AOVrV_L2;		//	Величина 1 импульса в режиме Р - 2 ракет Пу Л
    float AOVrN_L2; 		//	Величина 2 импульса в режиме Р - 2 ракет Пу Л
    float TOVr_L4;			//	Время действия импульса
    float AOVrV_L4;		//	Величина 1 импульса в режиме Р - 4 ракет Пу Л
    float AOVrN_L4; 		//	Величина 2 импульса в режиме Р - 4 ракет Пу Л
    float TOVr_L6;			//	Время действия импульса
    float AOVrV_L6;		//	Величина 1 импульса в режиме Р - 6 ракет Пу Л
    float AOVrN_L6; 		//	Величина 2 импульса в режиме Р - 6 ракет Пу Л
    //  Пу Пр
    float TOVr_P0;			//	Время действия импульса
    float AOVrV_P0;		//	Величина 1 импульса в режиме Р - О ракет Пу Пр
    float AOVrN_P0; 		//	Величина 2 импульса в режиме Р - О ракет Пу Пр
    float TOVr_P1;			//	Время действия импульса
    float AOVrV_P1;		//	Величина 1 импульса в режиме Р - 1 ракет Пу Пр
    float AOVrN_P1; 		//	Величина 2 импульса в режиме Р - 1 ракет Пу Пр
    float TOVr_P2;			//	Время действия импульса
    float AOVrV_P2;		//	Величина 1 импульса в режиме Р - 2 ракет Пу Пр
    float AOVrN_P2; 		//	Величина 2 импульса в режиме Р - 2 ракет Пу Пр
    float TOVr_P4;			//	Время действия импульса
    float AOVrV_P4;		//	Величина 1 импульса в режиме Р - 4 ракет Пу Пр
    float AOVrN_P4; 		//	Величина 2 импульса в режиме Р - 4 ракет Пу Пр
    float TOVr_P6;			//	Время действия импульса
    float AOVrV_P6;		//	Величина 1 импульса в режиме Р - 6 ракет Пу Пр
    float AOVrN_P6; 		//	Величина 2 импульса в режиме Р - 6 ракет Пу Пр
    ///	Параметры контура задающего ускорения
    float VUsk_K;			  //	Коэфф. задающего ускорения для режима ЗА
    float VrUsk_K;		  //	Коэфф. задающего ускорения для режима Р
    //	Пу Л
    float VrUsk_K_L0;	//	Коэфф. задающего ускорения для режима Р - 0 ракет Пу Л
    float VrUsk_K_L1;	//	Коэфф. задающего ускорения для режима Р - 1 ракет Пу Л
    float VrUsk_K_L2;	//	Коэфф. задающего ускорения для режима Р - 2 ракет Пу Л
    float VrUsk_K_L4;	//	Коэфф. задающего ускорения для режима Р - 4 ракет Пу Л
    float VrUsk_K_L6;	//	Коэфф. задающего ускорения для режима Р - 6 ракет Пу Л
    //	Пу Пр
    float VrUsk_K_P0;	//	Коэфф. задающего ускорения для режима Р - 0 ракет Пу Пр
    float VrUsk_K_P1;	//	Коэфф. задающего ускорения для режима Р - 1 ракет Пу Пр
    float VrUsk_K_P2;	//	Коэфф. задающего ускорения для режима Р - 2 ракет Пу Пр
    float VrUsk_K_P4;	//	Коэфф. задающего ускорения для режима Р - 4 ракет Пу Пр
    float VrUsk_K_P6;	//	Коэфф. задающего ускорения для режима Р - 6 ракет Пу Пр
    // Параметры контура задающей скорости
    float VSk_K;         //	Коэфф. задающей скорости для режима ЗА
    float VrSk_K;        //	Коэфф. задающей скорости для режима Р
    //	Пу Л
    float VrSk_K_L0;     //  Коэфф. задающей скорости для режима Р - 0 ракет Пу Л
    float VrSk_K_L1;     //	Коэфф. задающей скорости для режима Р - 1 ракет Пу Л
    float VrSk_K_L2;     //	Коэфф. задающей скорости для режима Р - 2 ракет Пу Л
    float VrSk_K_L4;     //	Коэфф. задающей скорости для режима Р - 4 ракет Пу Л
    float VrSk_K_L6;     //	Коэфф. задающей скорости для режима Р - 6 ракет Пу Л
    //	Пу Пр
    float VrSk_K_P0;     //	Коэфф. задающей скорости для режима Р - 0 ракет Пр Л
    float VrSk_K_P1;     //	Коэфф. задающей скорости для режима Р - 1 ракет Пр Л
    float VrSk_K_P2;     //	Коэфф. задающей скорости для режима Р - 2 ракет Пр Л
    float VrSk_K_P4;     //	Коэфф. задающей скорости для режима Р - 4 ракет Пр Л
    float VrSk_K_P6;     //	Коэфф. задающей скорости для режима Р - 6 ракет Пр Л
    // Параметры сумматора позиционного контура
    float VSum_K;        //  Коэфф. усиления режим ЗА
    float VSum_T;      //  Постоянная времени
    float VSum_G;           //  Диапазон звена
    float VSum_W;           //  Обратная связь - предидущий шаг
        //  Пу Л
    float VrLSum_K;      //  Коэфф. усиления в зависимости от режима Р - Пу Л
    float VrLSum_T;    //  Постоянная времени в зависимости от режима Р - Пу Л
    float VrLSum_G;       //  Диапазон звена в зависимости от режима Р - Пу Л
    float VrSum_K_L0;    //  Коэфф. усиления     для режима Р - 0 ракет Пу Л
    float VrSum_T_L0;   //  Постоянная времени  для режима Р - 0 ракет Пу Л
    float VrSum_G_L0;     //  Диапазон звена      для режима Р - 0 ракет Пу Л
    float VrSum_K_L1;    //  Коэфф. усиления     для режима Р - 1 ракет Пу Л
    float VrSum_T_L1;   //  Постоянная времени  для режима Р - 1 ракет Пу Л
    float VrSum_G_L1;     //  Диапазон звена      для режима Р - 1 ракет Пу Л
    float VrSum_K_L2;    //  Коэфф. усиления     для режима Р - 2 ракет Пу Л
    float VrSum_T_L2;   //  Постоянная времени  для режима Р - 2 ракет Пу Л
    float VrSum_G_L2;     //  Диапазон звена      для режима Р - 2 ракет Пу Л
    float VrSum_K_L4;    //  Коэфф. усиления     для режима Р - 4 ракет Пу Л
    float VrSum_T_L4;   //  Постоянная времени  для режима Р - 4 ракет Пу Л
    float VrSum_G_L4;     //  Диапазон звена      для режима Р - 4 ракет Пу Л
    float VrSum_K_L6;    //  Коэфф. усиления     для режима Р - 6 ракет Пу Л
    float VrSum_T_L6;   //  Постоянная времени  для режима Р - 6 ракет Пу Л
    float VrSum_G_L6;     //  Диапазон звена      для режима Р - 6 ракет Пу Л
    //  Пу Пр
    float VrPSum_K;      //  Коэфф. усиления в зависимости от режима Р - Пу Пр
    float VrPSum_T;    //  Постоянная времени в зависимости от режима Р - Пу Пр
    float VrPSum_G;       //  Диапазон звена в зависимости от режима Р - Пу Пр
    float VrSum_K_P0;    //  Коэфф. усиления     для режима Р - 0 ракет Пу Пр
    float VrSum_T_P0;   //  Постоянная времени  для режима Р - 0 ракет Пу Пр
    float VrSum_G_P0;     //  Диапазон звена      для режима Р - 0 ракет Пу Пр
    float VrSum_K_P1;    //  Коэфф. усиления     для режима Р - 1 ракет Пу Пр
    float VrSum_T_P1;   //  Постоянная времени  для режима Р - 1 ракет Пу Пр
    float VrSum_G_P1;     //  Диапазон звена      для режима Р - 1 ракет Пу Пр
    float VrSum_K_P2;    //  Коэфф. усиления     для режима Р - 2 ракет Пу Пр
    float VrSum_T_P2;   //  Постоянная времени  для режима Р - 2 ракет Пу Пр
    float VrSum_G_P2;     //  Диапазон звена      для режима Р - 2 ракет Пу Пр
    float VrSum_K_P4;    //  Коэфф. усиления     для режима Р - 4 ракет Пу Пр
    float VrSum_T_P4;   //  Постоянная времени  для режима Р - 4 ракет Пу Пр
    float VrSum_G_P4;     //  Диапазон звена      для режима Р - 4 ракет Пу Пр
    float VrSum_K_P6;    //  Коэфф. усиления     для режима Р - 6 ракет Пу Пр
    float VrSum_T_P6;   //  Постоянная времени  для режима Р - 6 ракет Пу Пр
    float VrSum_G_P6;     //  Диапазон звена      для режима Р - 6 ракет Пу Пр
    // Параметры сумматора скоростного контура
    float VSumSK_K;     //  Коэфф. усиления - режим ЗА
    float VSumSK_T;      //  Постоянная времени  - режим ЗА
    float VSumSK_G;      //  Диапазон звена - режим ЗА
    float VSumSK_W;         //  Обратная связь - предидущий шаг
        //  Пу Л
        float VrLSumSK_K;   //  Коэфф. усиления - режим Пу Л
    float VrLSumSK_T;    //  Постоянная времени - режим Пу Л
    float VrLSumSK_G;    //  Диапазон звена - режим Пу Л
    //  Пу Пр
    float VrPSumSK_K;   //  Коэфф. усиления - режим Пу Л
    float VrPSumSK_T;    //  Постоянная времени - режим Пу Л
    float VrPSumSK_G;    //  Диапазон звена - режим Пу Л
    //  Параметры контура обратной связи по скорости
    float VTG_K;
    float VTG_T;
    float VTG_G;
    float VTG_W;

    float VrTG_K_L0;
    float VrTG_T_L0;
    float VrTG_G_L0;
    float VrTG_K_L1;
    float VrTG_T_L1;
    float VrTG_G_L1;
    float VrTG_K_L2;
    float VrTG_T_L2;
    float VrTG_G_L2;
    float VrTG_K_L4;
    float VrTG_T_L4;
    float VrTG_G_L4;
    float VrTG_K_L6;
    float VrTG_T_L6;
    float VrTG_G_L6;

    float VrLTG_K;
    float VrLTG_T;
    float VrLTG_G;

    float VrTG_K_P0;
    float VrTG_T_P0;
    float VrTG_G_P0;

    float VrTG_K_P1;
    float VrTG_T_P1;
    float VrTG_G_P1;

    float VrTG_K_P2;
    float VrTG_T_P2;
    float VrTG_G_P2;

    float VrTG_K_P4;
    float VrTG_T_P4;
    float VrTG_G_P4;
    float VrTG_K_P6;
    float VrTG_T_P6;
    float VrTG_G_P6;

    float VrPTG_K;
    float VrPTG_T;
    float VrPTG_G;

    // Параметры контура по давлению
    float VP_K;
    float VP_T;
    float VP_T1;
    float VP_G;

    float VP_W;
    float VP_W1;
    float VFP_W;

    float VrP_K_L0;
    float VrP_T_L0;
    float VrP_T1_L0;
    float VrP_G_L0;
    float VrP_K_L1;
    float VrP_T_L1;
    float VrP_T1_L1;
    float VrP_G_L1;
    float VrP_K_L2;
    float VrP_T_L2;
    float VrP_T1_L2;
    float VrP_G_L2;
    float VrP_K_L4;
    float VrP_T_L4;
    float VrP_T1_L4;
    float VrP_G_L4;
    float VrP_K_L6;
    float VrP_T_L6;
    float VrP_T1_L6;
    float VrP_G_L6;

    float VrLP_K;
    float VrLP_T;
    float VrLP_T1;
    float VrLP_G;

    float VrP_K_P0;
    float VrP_T_P0;
    float VrP_T1_P0;
    float VrP_G_P0;

    float VrP_K_P1;
    float VrP_T_P1;
    float VrP_T1_P1;
    float VrP_G_P1;
    float VrP_K_P2;
    float VrP_T_P2;
    float VrP_T1_P2;
    float VrP_G_P2;
    float VrP_K_P4;
    float VrP_T_P4;
    float VrP_T1_P4;
    float VrP_G_P4;
    float VrP_K_P6;
    float VrP_T_P6;
    float VrP_T1_P6;
    float VrP_G_P6;

    float VrPP_K;
    float VrPP_T;
    float VrPP_T1;
    float VrPP_G;
    //---------------------------------------------------------------
    // Параметры корр. звена на выходе
    float VKolK;
    float VKolT;
    float VKolE;
    float VKolW1;
    float VKolW2;
    float VFSkT;
    float VFSkW;
    //---------------------------------------------------------------
    // Параметры Аварийного торможения
    float VnAAT;
    float VnTAT;
    float VTok;
    int   MsIvn[10];
    int   VnNAT;
        //---------------------------------------------------------------
    float ZIVnSk_W;       //
    float SKMax;        //
    float SKOgr;       //

    short VnN;
    short VMsTSk[31];				//	Массив текущих углов для расчета скорости
    short VMsSk[10];
};

#endif // CASC19F6_H
