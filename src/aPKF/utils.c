#include <math.h>

/*!****************************************************************************
 * @function bw0(&Addr,Bit)
 * @bref Функция записи 0 бита в целочисленное число типа int
 * @param[out] Addr целочисленное число типа int c измененным 0 битом
 * @param[in] Bit величина бита, необходимого для записи
 *****************************************************************************/
void bw0 (int *Addr,int Bit) 
{if (Bit==1) *Addr=*Addr|0x1;    else *Addr=*Addr&(~0x1);}
/*!****************************************************************************
 * @function bw1(&Addr,Bit)
 * @bref Функция записи 1 бита в целочисленное число типа int
 * @param[out] Addr целочисленное число типа int c измененным 1 битом
 * @param[in] Bit величина бита, необходимого для записи
 *****************************************************************************/
void bw1 (int *Addr,int Bit) 
{if (Bit==1) *Addr=*Addr|0x2;    else *Addr=*Addr&(~0x2);}
/*!****************************************************************************
 * @function bw2(&Addr,Bit)
 * @bref Функция записи 2 бита в целочисленное число типа int
 * @param[out] Addr целочисленное число типа int c измененным 2 битом
 * @param[in] Bit величина бита, необходимого для записи
 *****************************************************************************/
void bw2 (int *Addr,int Bit) 
{if (Bit==1) *Addr=*Addr|0x4;    else *Addr=*Addr&(~0x4);}
/*!****************************************************************************
 * @function bw3(&Addr,Bit)
 * @bref Функция записи 3 бита в целочисленное число типа int
 * @param[out] Addr целочисленное число типа int c измененным 3 битом
 * @param[in] Bit величина бита, необходимого для записи
 *****************************************************************************/
void bw3 (int *Addr,int Bit) 
{if (Bit==1) *Addr=*Addr|0x8;    else *Addr=*Addr&(~0x8);}
/*!****************************************************************************
 * @function bw4(&Addr,Bit)
 * @bref Функция записи 4 бита в целочисленное число типа int
 * @param[out] Addr целочисленное число типа int c измененным 4 битом
 * @param[in] Bit величина бита, необходимого для записи
 *****************************************************************************/
void bw4 (int *Addr,int Bit) 
{if (Bit==1) *Addr=*Addr|0x10;   else *Addr=*Addr&(~0x10);}
/*!****************************************************************************
 * @function bw5(&Addr,Bit)
 * @bref Функция записи 5 бита в целочисленное число типа int
 * @param[out] Addr целочисленное число типа int c измененным 5 битом
 * @param[in] Bit величина бита, необходимого для записи
 *****************************************************************************/
void bw5 (int *Addr,int Bit) 
{if (Bit==1) *Addr=*Addr|0x20;   else *Addr=*Addr&(~0x20);}
/*!****************************************************************************
 * @function bw6(&Addr,Bit)
 * @bref Функция записи 6 бита в целочисленное число типа int
 * @param[out] Addr целочисленное число типа int c измененным 6 битом
 * @param[in] Bit величина бита, необходимого для записи
 *****************************************************************************/
void bw6 (int *Addr,int Bit) 
{if (Bit==1) *Addr=*Addr|0x40;   else *Addr=*Addr&(~0x40);}
/*!****************************************************************************
 * @function bw7(&Addr,Bit)
 * @bref Функция записи 7 бита в целочисленное число типа int
 * @param[out] Addr целочисленное число типа int c измененным 7 битом
 * @param[in] Bit величина бита, необходимого для записи
 *****************************************************************************/
void bw7 (int *Addr,int Bit) 
{if (Bit==1) *Addr=*Addr|0x80;   else *Addr=*Addr&(~0x80);}
/*!****************************************************************************
 * @function bw8(&Addr,Bit)
 * @bref Функция записи 8 бита в целочисленное число типа int
 * @param[out] Addr целочисленное число типа int c измененным 8 битом
 * @param[in] Bit величина бита, необходимого для записи
 *****************************************************************************/
void bw8 (int *Addr,int Bit) 
{if (Bit==1) *Addr=*Addr|0x100;  else *Addr=*Addr&(~0x100);}
/*!****************************************************************************
 * @function bw9(&Addr,Bit)
 * @bref Функция записи 9 бита в целочисленное число типа int
 * @param[out] Addr целочисленное число типа int c измененным 9 битом
 * @param[in] Bit величина бита, необходимого для записи
 *****************************************************************************/
void bw9 (int *Addr,int Bit) 
{if (Bit==1) *Addr=*Addr|0x200;  else *Addr=*Addr&(~0x200);}
/*!****************************************************************************
 * @function bw10(&Addr,Bit)
 * @bref Функция записи 10 бита в целочисленное число типа int
 * @param[out] Addr целочисленное число типа int c измененным 10 битом
 * @param[in] Bit величина бита, необходимого для записи
 *****************************************************************************/
void bw10(int *Addr,int Bit) 
{if (Bit==1) *Addr=*Addr|0x400;  else *Addr=*Addr&(~0x400);}
/*!****************************************************************************
 * @function bw11(&Addr,Bit)
 * @bref Функция записи 11 бита в целочисленное число типа int
 * @param[out] Addr целочисленное число типа int c измененным 11 битом
 * @param[in] Bit величина бита, необходимого для записи
 *****************************************************************************/
void bw11(int *Addr,int Bit) 
{if (Bit==1) *Addr=*Addr|0x800;  else *Addr=*Addr&(~0x800);}
/*!****************************************************************************
 * @function bw12(&Addr,Bit)
 * @bref Функция записи 12 бита в целочисленное число типа int
 * @param[out] Addr целочисленное число типа int c измененным 12 битом
 * @param[in] Bit величина бита, необходимого для записи
 *****************************************************************************/
void bw12(int *Addr,int Bit) 
{if (Bit==1) *Addr=*Addr|0x1000; else *Addr=*Addr&(~0x1000);}
/*!****************************************************************************
 * @function bw13(&Addr,Bit)
 * @bref Функция записи 13 бита в целочисленное число типа int
 * @param[out] Addr целочисленное число типа int c измененным 13 битом
 * @param[in] Bit величина бита, необходимого для записи
 *****************************************************************************/
void bw13(int *Addr,int Bit) 
{if (Bit==1) *Addr=*Addr|0x2000; else *Addr=*Addr&(~0x2000);}
/*!****************************************************************************
 * @function bw14(&Addr,Bit)
 * @bref Функция записи 14 бита в целочисленное число типа int
 * @param[out] Addr целочисленное число типа int c измененным 14 битом
 * @param[in] Bit величина бита, необходимого для записи
 *****************************************************************************/
void bw14(int *Addr,int Bit) 
{if (Bit==1) *Addr=*Addr|0x4000; else *Addr=*Addr&(~0x4000);}
/*!****************************************************************************
 * @function bw15(&Addr,Bit)
 * @bref Функция записи 15 бита в целочисленное число типа int
 * @param[out] Addr целочисленное число типа int c измененным 15 битом
 * @param[in] Bit величина бита, необходимого для записи
 *****************************************************************************/
void bw15(int *Addr,int Bit) 
{if (Bit==1) *Addr=*Addr|0x8000; else *Addr=*Addr&(~0x8000);}
/*!****************************************************************************
 * @function br0(Addr)
 * @bref Функция возвращает 0 бита целочисленное число типа int
 * @param[in] целочисленное число типа int
 * @return значение 0 бита 
 *****************************************************************************/
int br0 (const int Addr) {if ((Addr&0x1)!=0)    return 1; else return 0;}
/*!****************************************************************************
 * @function br1(Addr)
 * @bref Функция возвращает 1 бита целочисленное число типа int
 * @param[in] целочисленное число типа int
 * @return значение 1 бита 
 *****************************************************************************/
int br1 (const int Addr) {if ((Addr&0x2)!=0)    return 1; else return 0;}
/*!****************************************************************************
 * @function br2(Addr)
 * @bref Функция возвращает 2 бита целочисленное число типа int
 * @param[in] целочисленное число типа int
 * @return значение 2 бита 
 *****************************************************************************/
int br2 (const int Addr) {if ((Addr&0x4)!=0)    return 1; else return 0;}
/*!****************************************************************************
 * @function br3(Addr)
 * @bref Функция возвращает 3 бита целочисленное число типа int
 * @param[in] целочисленное число типа int
 * @return значение 3 бита 
 *****************************************************************************/
int br3 (const int Addr) {if ((Addr&0x8)!=0)    return 1; else return 0;}
/*!****************************************************************************
 * @function br4(Addr)
 * @bref Функция возвращает 4 бита целочисленное число типа int
 * @param[in] целочисленное число типа int
 * @return значение 4 бита 
 *****************************************************************************/
int br4 (const int Addr) {if ((Addr&0x10)!=0)   return 1; else return 0;}
/*!****************************************************************************
 * @function br5(Addr)
 * @bref Функция возвращает 5 бита целочисленное число типа int
 * @param[in] целочисленное число типа int
 * @return значение 5 бита 
 *****************************************************************************/
int br5 (const int Addr) {if ((Addr&0x20)!=0)   return 1; else return 0;}
/*!****************************************************************************
 * @function br6(Addr)
 * @bref Функция возвращает 6 бита целочисленное число типа int
 * @param[in] целочисленное число типа int
 * @return значение 6 бита 
 *****************************************************************************/
int br6 (const int Addr) {if ((Addr&0x40)!=0)   return 1; else return 0;}
/*!****************************************************************************
 * @function br7(Addr)
 * @bref Функция возвращает 7 бита целочисленное число типа int
 * @param[in] целочисленное число типа int
 * @return значение 7 бита 
 *****************************************************************************/
int br7 (const int Addr) {if ((Addr&0x80)!=0)   return 1; else return 0;}
/*!****************************************************************************
 * @function br8(Addr)
 * @bref Функция возвращает 8 бита целочисленное число типа int
 * @param[in] целочисленное число типа int
 * @return значение 8 бита 
 *****************************************************************************/
int br8 (const int Addr) {if ((Addr&0x100)!=0)  return 1; else return 0;}
/*!****************************************************************************
 * @function br9(Addr)
 * @bref Функция возвращает 9 бита целочисленное число типа int
 * @param[in] целочисленное число типа int
 * @return значение 9 бита 
 *****************************************************************************/
int br9 (const int Addr) {if ((Addr&0x200)!=0)  return 1; else return 0;}
/*!****************************************************************************
 * @function br10(Addr)
 * @bref Функция возвращает 10 бита целочисленное число типа int
 * @param[in] целочисленное число типа int
 * @return значение 10 бита 
 *****************************************************************************/
int br10(const int Addr) {if ((Addr&0x400)!=0)  return 1; else return 0;}
/*!****************************************************************************
 * @function br11(Addr)
 * @bref Функция возвращает 11 бита целочисленное число типа int
 * @param[in] целочисленное число типа int
 * @return значение 11 бита 
 *****************************************************************************/
int br11(const int Addr) {if ((Addr&0x800)!=0)  return 1; else return 0;}
/*!****************************************************************************
 * @function br12(Addr)
 * @bref Функция возвращает 12 бита целочисленное число типа int
 * @param[in] целочисленное число типа int
 * @return значение 12 бита 
 *****************************************************************************/
int br12(const int Addr) {if ((Addr&0x1000)!=0) return 1; else return 0;}
/*!****************************************************************************
 * @function br13(Addr)
 * @bref Функция возвращает 13 бита целочисленное число типа int
 * @param[in] целочисленное число типа int
 * @return значение 13 бита 
 *****************************************************************************/
int br13(const int Addr) {if ((Addr&0x2000)!=0) return 1; else return 0;}
/*!****************************************************************************
 * @function br14(Addr)
 * @bref Функция возвращает 14 бита целочисленное число типа int
 * @param[in] целочисленное число типа int
 * @return значение 14 бита 
 *****************************************************************************/
int br14(const int Addr) {if ((Addr&0x4000)!=0) return 1; else return 0;}
/*!****************************************************************************
 * @function br15(Addr)
 * @bref Функция возвращает 15 бита целочисленное число типа int
 * @param[in] целочисленное число типа int
 * @return значение 15 бита 
 *****************************************************************************/
int br15(const int Addr) {if ((Addr&0x8000)!=0) return 1; else return 0;}

/*!****************************************************************************
 * @function sign(par)
 * @brief Функиця определения сигнатуры
 * @param[in] входной сигнал
 * @return возвращает -1;0;1
 *****************************************************************************/
int sign(const float in)
{
  if (in > 0.0) return 1;
  else if (in < 0.0) return -1;
  else return 0.0;
}

/******************************************************************************
 *  
 ******************************************************************************/
short TKD (int In)
{
  return (short)(In*65535/4095);
}

/******************************************************************************
 *  Функция преобразования из кода в рад/сек
 ******************************************************************************/
float TKRS(const int in)
{
  return (float)(in*12.355);
}

/******************************************************************************
 *  Функция преобразования из радиан в доп.код
 ******************************************************************************/
short TRD(const float in)
{                           
  float tmp = in;
  if (tmp>M_PI) tmp=M_PI;
  if (tmp<-M_PI) tmp=-M_PI;
  if (tmp>=0) return (short)(tmp* 32767.0/M_PI);
  else  return (short)(tmp*32768.0/M_PI);
}

/******************************************************************************
 *  Функция преобразования к 12-ти разрядной сетке
 *  из дополнительного кода
 ******************************************************************************/
int TD12(const short in)
{
  return (int)(-in/(65536/4096));
}                     

/******************************************************************************
 *  Функция преобразования из радиан к 12-ти разрядной сетке
 ******************************************************************************/
int TR12(const float in)
{
  float tmp = in;
  if(tmp> M_PI) tmp=M_PI;
  if(tmp<-M_PI) tmp=-M_PI;
  return (int)(tmp*2047.0/M_PI);
}       

/******************************************************************************
 *  Функция преобразования из радиан к 13-ти разрядной сетке
 ******************************************************************************/
int TR13(const float in)
{
    float tmp = in;
    if(tmp> M_PI) tmp=M_PI;
    if(tmp<-M_PI) tmp=-M_PI;
    return (int)(tmp*4095.0/M_PI);
}       

/******************************************************************************
 *  Функция преобразования из доп. кода в радианы
 ******************************************************************************/
float TDR(const short in)
{
  if (in>=0) return (float)(in*M_PI/32767.0);
  else return (float)(in*M_PI/32768.0);
}                  

/******************************************************************************
 *  Функция преобразования из 12-разр. в радианы
 ******************************************************************************/
float T12R(const short in)
{
  short tmp = in;
  if(tmp>2048) tmp=2048;
  if(tmp<-2047)tmp=-2047;
  return (float)((tmp-2047)*M_PI/2047.0);
}

/******************************************************************************
 *  
 ******************************************************************************/
float TKR(const int in)
{
  return (float)(in*M_PI/32767.0);
}

/******************************************************************************
 *  
 ******************************************************************************/
float TKMr(const unsigned short in)
{                               
  return (float)((in-32768)*3141.6/32768.0);;
}

/******************************************************************************
 *  Функция преобразования из доп. кода в градусы
 ******************************************************************************/
float TDG(const short in)
{
  if (in>=0) return (float)(in*180.0/32767.0);
  else return (float)(in*180.0/32768.0);
}                  

/******************************************************************************
 *  Функция преобразования из градусов в доп. код
 ******************************************************************************/
short TGD(const float in)
{                           
  float tmp = in;
  if (tmp>180.0)  tmp =  180.0;
  if (tmp<-180.0) tmp = -180.0;
  if (tmp>=0.0) return (short)(tmp* 32767.0/180.0);
  else return (short)(tmp*32768.0/180.0);
}

/******************************************************************************
 *  
 ******************************************************************************/
int ToInt(int Dann1, int Dann2,int Dann3, int Dann4)
{
int Temp=0;
if (Dann1>255) Dann1=255;
if (Dann2>255) Dann2=255;
if (Dann3>255) Dann3=255;
if (Dann4>255) Dann4=255;
Temp=Dann1+(Dann2<<8)+(Dann3<<16)+(Dann4<<24);
return Temp;
}

/******************************************************************************
 *  Функция преобразования из радиан в градусы
 ******************************************************************************/
float TRG(const float in)
{
 return (in*180.0/M_PI);
}

/******************************************************************************
 *  Функция преобразования из градусов в радианы
 ******************************************************************************/
float TGR(const float in)
{
 return (in*M_PI/180.0);
}
