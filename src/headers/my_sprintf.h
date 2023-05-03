#ifndef STRINGPLUS_SRC_HEADERS_MY_SPRINTF_H_
#define STRINGPLUS_SRC_HEADERS_MY_SPRINTF_H_

#include <math.h>
#include <stdarg.h>

#include "my_string.h"
#include "stack.h"

#define MAX_SHORT_INT 32767
#define MIN_SHORT_INT -32768
#define BUFFERSIZE 4096
#define EPS 10e-4
#define EPS_NULL 10e-24
#define DEFAULT_PRECISION 6
#define DEC 10
#define HEX 16
#define OCT 8

typedef struct SprintfFlags {
  int flag_plus;
  int flag_minus;
  int flag_space;
  int flag_hashtag;
  int flag_zero;
} SprintfFlags;

typedef struct SprintfParams {
  /*В структуре хранится:
  flag {+,-,(space),#,0} - модификаторы;
  width {(число),*} - мин. кол-во печатаемых символов;
  precision {.(число), .*} - точность печатаемого числа;
  length {h,l,L} - длина;
  specificator {c,d,i,e,E,f,g,G,o,s,u,x,X,p,n}*/
  SprintfFlags flag;
  my_size_t width;
  my_size_t precision;
  int flag_precision;
  char length;
  char specificator;
} SprintfParams;

void initStruct(SprintfParams *params);
int CheckFlags(char symbol, SprintfParams *params);
int CheckNumber(char symbol);
char *ToGetWidthOrPrecision(char *ptr_format, my_size_t *width_or_precision);
int ParseLetters(char *ptr_format, SprintfParams *params);
void AnalisSpecificator(SprintfParams *params, va_list ap, char *str,
                        int *position);
void Specifier_c(SprintfParams *params, va_list ap, char *str, int *position);
void Specifier_s(SprintfParams *params, va_list ap, char *str, int *position);
void WorkspaceDouble(SprintfParams *params, va_list ap, char *str,
                     int *position);
void Specifier_n(va_list ap, int *position);
void Specifiers_d_i(SprintfParams *params, va_list ap, char *str,
                    int *position);
void Specifiers_x_X(SprintfParams *params, va_list ap, char *str,
                    int *position);
void Specifier_o(SprintfParams *params, va_list ap, char *str, int *position);
void Specifier_u(SprintfParams *params, va_list ap, char *str, int *position);
void Specifier_p(SprintfParams *params, va_list ap, char *str, int *position);
void putCharToStr(char *str, int *position, char symbol);
char *Specifier_f(SprintfParams *params, char *str, int *position,
                  long double arg_double, char *sign_before_num);
char *Specifier_e(SprintfParams *params, char *str, int *position,
                  long double arg_double, char *sign_before_num);
void Specifier_g(SprintfParams *params, char *str, int *position,
                 long double arg_double, char *sign_before_num);
int CheckFirstNumberInFract(long double fract);
char *convertFractToSymbol(SprintfParams *params, long double fract);
char *convertDigitToSymbol(SprintfParams *params, long long num,
                           int systemBase);
char *convertDigitToSymbol_U(SprintfParams *params, unsigned long long num,
                             int systemBase);
void WriteDoubleToOutputArray(SprintfParams *params, char *str, int *position,
                              char *nums_str, my_size_t size_arg,
                              char *sign_before_num);
void putStrToStr(char *str, int *position, char *symbol);
long double getRank(long double num, int *rank);
void deleteZero(char *bufferResult);
int ConvertIntToShort(long int number, SprintfParams *params);
void WriteIntToOutputArray(SprintfParams *params, char *str, int *position,
                           char *nums_str, my_size_t size_arg,
                           char *sign_before_num);
void printProcent(char *str, int *position);
int parseLength(char *ptr_format, SprintfParams *params);
char *convertFloatToSymbol(SprintfParams *params, long double num,
                           int systemBase);

#endif  // STRINGPLUS_SRC_HEADERS_MY_SPRINTF_H_
