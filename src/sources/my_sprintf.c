#include "../headers/my_sprintf.h"

int my_sprintf(char *str, const char *format, ...) {
  int position = 0;
  int flagProcent = 0;
  if (str != my_NULL) {
    *str = '\0';
    if (format == my_NULL) {
      position = -1;
    } else {
      va_list ap;
      va_start(ap, format);
      SprintfParams params = {0};
      char *ptr_format = (char *)format;
      while (*ptr_format != '\0') {
        if (*ptr_format != '%') {
          str[position] = *ptr_format;
          ptr_format++;
          position++;
        } else {
          flagProcent = 1;
          ptr_format++;
          initStruct(&params);
          while (CheckFlags(*ptr_format, &params)) {
            ptr_format++;
          }
          if (CheckNumber(*ptr_format)) {
            ptr_format = ToGetWidthOrPrecision(ptr_format, &params.width);
          }
          if (*ptr_format == '*') {
            params.width = va_arg(ap, int);
            ptr_format++;
          }
          if (*ptr_format == '.') {
            params.flag_precision = 1;
            ptr_format++;
            if (CheckNumber(*ptr_format)) {
              ptr_format = ToGetWidthOrPrecision(ptr_format, &params.precision);
            } else if (*ptr_format == '*') {
              params.precision = va_arg(ap, int);
              ptr_format++;
            }
          }
          if (parseLength(ptr_format, &params)) {
            ptr_format++;
          }
          if (ParseLetters(ptr_format, &params)) {
            ptr_format++;
          }
          if (!params.flag_precision) {
            params.precision = DEFAULT_PRECISION;
          }
          if (params.specificator == 's' && params.length == 'l') break;
          AnalisSpecificator(&params, ap, str, &position);
        }
      }
      str[position] = '\0';
      if (params.specificator == '\0' && flagProcent) position = -1;
      va_end(ap);
    }
  }
  return position;
}

void initStruct(SprintfParams *params) {
  params->flag.flag_hashtag = params->flag.flag_minus = params->flag.flag_plus =
      params->flag.flag_space = params->flag.flag_zero = 0;
  params->width = 0;
  params->precision = 0;
  params->flag_precision = 0;
  params->length = '\0';
  params->specificator = '\0';
}

int CheckFlags(char symbol, SprintfParams *params) {
  int check = 1;
  switch (symbol) {
    case '+':
      params->flag.flag_plus = 1;
      break;
    case '-':
      params->flag.flag_minus = 1;
      break;
    case ' ':
      params->flag.flag_space = 1;
      break;
    case '#':
      params->flag.flag_hashtag = 1;
      break;
    case '0':
      params->flag.flag_zero = 1;
      break;
    default:
      check = 0;
  }
  return check;
}

int CheckNumber(char symbol) { return (symbol >= 48 && symbol <= 57); }

char *ToGetWidthOrPrecision(char *ptr_format, my_size_t *width_or_precision) {
  StackForNumber *head = InitStack(*ptr_format);
  if (head != my_NULL) {
    while (CheckNumber(*(++ptr_format))) {
      head = Push(head, *ptr_format);
    }
    int index = 0;
    while (head->prev_number != my_NULL) {
      *width_or_precision += Pop(&head) * pow(10, index);
      index++;
    }
    *width_or_precision += head->number * pow(10, index);
    Clear(head);
  }
  return ptr_format;
}

int parseLength(char *ptr_format, SprintfParams *params) {
  int result = 0;
  if (*ptr_format == 'h' || *ptr_format == 'l' || *ptr_format == 'L') {
    params->length = *ptr_format;
    result = 1;
  }
  return result;
}

int ParseLetters(char *ptr_format, SprintfParams *params) {
  int result = 0;
  if ((*ptr_format >= 'c' && *ptr_format <= 'g') || *ptr_format == 'i' ||
      (*ptr_format >= 'n' && *ptr_format <= 'p') || *ptr_format == 's' ||
      *ptr_format == 'u' || *ptr_format == 'x' || *ptr_format == 'E' ||
      *ptr_format == 'G' || *ptr_format == 'X' || *ptr_format == '%') {
    params->specificator = *ptr_format;
    result = 1;
  }
  return result;
}

void AnalisSpecificator(SprintfParams *params, va_list ap, char *str,
                        int *position) {
  if (params->specificator == 'c') {
    Specifier_c(params, ap, str, position);
  } else if (params->specificator == 's') {
    Specifier_s(params, ap, str, position);
  } else if (params->specificator == 'g' || params->specificator == 'G' ||
             params->specificator == 'e' || params->specificator == 'E' ||
             params->specificator == 'f') {
    WorkspaceDouble(params, ap, str, position);
  } else if (params->specificator == 'n') {
    Specifier_n(ap, position);
  } else if (params->specificator == 'd' || params->specificator == 'i') {
    Specifiers_d_i(params, ap, str, position);
  } else if (params->specificator == 'x' || params->specificator == 'X') {
    Specifiers_x_X(params, ap, str, position);
  } else if (params->specificator == 'o') {
    Specifier_o(params, ap, str, position);
  } else if (params->specificator == 'u') {
    Specifier_u(params, ap, str, position);
  } else if (params->specificator == 'p') {
    Specifier_p(params, ap, str, position);
  } else if (params->specificator == '%') {
    printProcent(str, position);
  }
}

void printProcent(char *str, int *position) {
  putCharToStr(str, position, '%');
}

void Specifier_c(SprintfParams *params, va_list ap, char *str, int *position) {
  char arg_char = (char)va_arg(ap, int);
  int width = (params->width) - 1;
  if (params->flag.flag_minus) {
    putCharToStr(str, position, arg_char);
    while (width-- > 0) {
      putCharToStr(str, position, ' ');
    }
  } else {
    while (width-- > 0) {
      putCharToStr(str, position, ' ');
    }
    putCharToStr(str, position, arg_char);
  }
}

void putCharToStr(char *str, int *position, char symbol) {
  str[*position] = symbol;
  (*position)++;
}

void Specifier_s(SprintfParams *params, va_list ap, char *str, int *position) {
  char null[10] = "(null)";
  char *arg_string = va_arg(ap, char *);
  if (arg_string == my_NULL) {
    arg_string = null;
    params->precision = my_strlen(null);
  }
  my_size_t size = my_strlen(arg_string);
  if (!params->flag_precision) {
    params->precision = size;
  } else {
    params->precision = params->precision > size ? size : params->precision;
  }
  params->width =
      params->width > params->precision ? params->width - params->precision : 0;
  if (params->flag.flag_minus) {
    while (*arg_string != '\0' && params->precision != 0) {
      putCharToStr(str, position, *arg_string);
      arg_string++;
      params->precision--;
    }
    while (params->width) {
      putCharToStr(str, position, ' ');
      params->width--;
    }
  } else {
    while (params->width) {
      putCharToStr(str, position, ' ');
      params->width--;
    }
    while (*arg_string != '\0' && params->precision != 0) {
      putCharToStr(str, position, *arg_string);
      arg_string++;
      params->precision--;
    }
  }
}

void WorkspaceDouble(SprintfParams *params, va_list ap, char *str,
                     int *position) {
  long double arg_double = 0.0L;
  if (params->length == 'L') {
    arg_double = va_arg(ap, long double);
  } else {
    arg_double = va_arg(ap, double);
  }
  char *sign_before_num = signbit(arg_double)       ? "-"
                          : params->flag.flag_plus  ? "+"
                          : params->flag.flag_space ? " "
                                                    : "\0";
  arg_double = signbit(arg_double) ? -arg_double : arg_double;
  if (params->specificator == 'f') {
    Specifier_f(params, str, position, arg_double, sign_before_num);
  } else if (params->specificator == 'e' || params->specificator == 'E') {
    Specifier_e(params, str, position, arg_double, sign_before_num);
  } else if (params->specificator == 'g' || params->specificator == 'G') {
    Specifier_g(params, str, position, arg_double, sign_before_num);
  }
}

char *Specifier_f(SprintfParams *params, char *str, int *position,
                  long double arg_double, char *sign_before_num) {
  static char result_double_string[BUFFERSIZE] = {0};
  my_memset(result_double_string, '\0', BUFFERSIZE);
  long double unit = 0.0L;
  long double fract = modfl(arg_double, &unit);
  if (!params->precision) {
    unit += CheckFirstNumberInFract(fract);
  }
  char *fract_str = my_NULL;
  if (params->precision) {
    fract_str = convertFractToSymbol(params, fract);
    unit += *(--fract_str) - '0';
    fract_str++;
  }
  my_strcat(result_double_string, convertFloatToSymbol(params, unit, DEC));
  if (!params->precision && params->flag.flag_hashtag) {
    my_strcat(result_double_string, ".");
  }
  if (params->precision) {
    my_strcat(result_double_string, ".");
    my_strcat(result_double_string, fract_str);
  }
  if (!(params->specificator == 'g' || params->specificator == 'G')) {
    my_size_t size_arg = my_strlen(result_double_string);
    params->width = params->width > size_arg ? params->width : size_arg;

    if ((params->width - size_arg) > 0 && my_strcmp(sign_before_num, "\0"))
      params->width--;

    WriteDoubleToOutputArray(params, str, position, result_double_string,
                             size_arg, sign_before_num);
  }
  return result_double_string;
}

int CheckFirstNumberInFract(long double fract) {
  int unit = (int)(fract * 10.0);
  return (unit >= 5);
}

char *convertFractToSymbol(SprintfParams *params, long double fract) {
  char *mas1 = "0123456789";
  static char buffer[BUFFERSIZE] = {0};
  my_memset(buffer, '\0', BUFFERSIZE);
  buffer[0] = '0';
  char *ptr = &buffer[1];
  int unit = 0;
  my_size_t precision = params->precision;
  while (precision) {
    fract *= 10.0;
    unit = (int)(fract);
    fract -= unit;
    if (precision == 1) {
      unit += CheckFirstNumberInFract(fract);
    }
    *ptr = mas1[unit % 10];
    while (unit > 9) {
      unit /= 10;
      ptr--;
      unit += *ptr - '0';
      *ptr = mas1[unit % 10];
    }
    ptr++;
    precision--;
  }
  ptr = &buffer[1];
  return ptr;
}

char *convertFloatToSymbol(SprintfParams *params, long double num,
                           int systemBase) {
  char *mas1 = "0123456789abcdef";
  if (num < 0 && params->specificator != 'u') num *= -1;
  static char buffer[BUFFERSIZE] = {0};
  char *ptr = &buffer[BUFFERSIZE - 1];
  *ptr = '\0';
  if (params->specificator == 'X') mas1 = my_to_upper(mas1);
  do {
    *(--ptr) = mas1[(int)(fmodl(num, systemBase))];
    num /= systemBase;
    modfl(num, &num);
  } while (num != 0);
  if (params->specificator == 'X') free(mas1);
  return (ptr);
}

char *convertDigitToSymbol(SprintfParams *params, long long num,
                           int systemBase) {
  char *mas1 = "0123456789abcdef";
  if (num < 0 && params->specificator != 'u') num *= -1;
  static char buffer[BUFFERSIZE] = {0};
  char *ptr = &buffer[BUFFERSIZE - 1];
  *ptr = '\0';
  if (params->specificator == 'X') mas1 = my_to_upper(mas1);
  do {
    *(--ptr) = mas1[num % systemBase];
    num /= systemBase;
  } while (num != 0);
  if (params->specificator == 'X') free(mas1);
  return (ptr);
}
char *convertDigitToSymbol_U(SprintfParams *params, unsigned long long num,
                             int systemBase) {
  char *mas1 = "0123456789abcdef";
  static char buffer[BUFFERSIZE] = {0};
  char *ptr = &buffer[BUFFERSIZE - 1];
  *ptr = '\0';
  if (params->specificator == 'X') mas1 = my_to_upper(mas1);
  do {
    *(--ptr) = mas1[num % systemBase];
    num /= systemBase;
  } while (num != 0);
  if (params->specificator == 'X') free(mas1);
  return (ptr);
}

void WriteDoubleToOutputArray(SprintfParams *params, char *str, int *position,
                              char *nums_str, my_size_t size_arg,
                              char *sign_before_num) {
  if (params->flag.flag_minus || params->width == size_arg) {
    putStrToStr(str, position, sign_before_num);
    putStrToStr(str, position, nums_str);
    params->width -= size_arg;
    while (params->width) {
      putStrToStr(str, position, " ");
      params->width--;
    }
  } else {
    if (params->flag.flag_zero) {
      putStrToStr(str, position, sign_before_num);
      params->width -= size_arg;
      while (params->width) {
        putStrToStr(str, position, "0");
        params->width--;
      }
      putStrToStr(str, position, nums_str);
    } else {
      params->width -= size_arg;
      while (params->width) {
        putStrToStr(str, position, " ");
        params->width--;
      }
      putStrToStr(str, position, sign_before_num);
      putStrToStr(str, position, nums_str);
    }
  }
}

void putStrToStr(char *str, int *position, char *symbol) {
  while (*symbol != '\0') {
    str[*position] = *symbol;
    (*position)++;
    symbol++;
  }
}

char *Specifier_e(SprintfParams *params, char *str, int *position,
                  long double arg_double, char *sign_before_num) {
  static char result_double_string[BUFFERSIZE] = {0};
  my_memset(result_double_string, '\0', BUFFERSIZE);
  int flag_null = 0;
  if (arg_double < EPS_NULL) {
    flag_null = 1;
  }
  int rank = 0;
  if (!flag_null) {
    arg_double = getRank(arg_double, &rank);
  }
  long int unit = (long int)arg_double;
  long double fract = arg_double - unit;
  if (!params->precision) {
    unit += CheckFirstNumberInFract(fract);
  }
  char *unit_str = convertDigitToSymbol(params, unit, DEC);
  char *fract_str = my_NULL;
  if (params->specificator == 'g' || params->specificator == 'G') {
    params->precision =
        params->precision > my_strlen(unit_str) && my_strcmp(unit_str, "0")
            ? params->precision - my_strlen(unit_str)
            : params->precision;
  }
  if (params->precision) {
    fract_str = convertFractToSymbol(params, fract);
    unit += *(--fract_str) - '0';
    unit_str = convertDigitToSymbol(params, unit, DEC);
    fract_str++;
  }
  my_strcat(result_double_string, unit_str);
  if (!params->precision && params->flag.flag_hashtag) {
    my_strcat(result_double_string, ".");
  }
  if (params->precision) {
    my_strcat(result_double_string, ".");
    my_strcat(result_double_string, fract_str);
  }
  if (params->specificator == 'e' || params->specificator == 'g') {
    my_strcat(result_double_string, "e");
  } else {
    my_strcat(result_double_string, "E");
  }
  char *sign_rank = my_NULL;
  if (rank < 0) {
    rank *= -1;
    sign_rank = "-";
  } else {
    sign_rank = "+";
  }
  my_strcat(result_double_string, sign_rank);
  if (rank >= 0 && rank < 10) {
    my_strcat(result_double_string, "0");
  }
  my_strcat(result_double_string, convertDigitToSymbol(params, rank, DEC));
  if (!(params->specificator == 'g' || params->specificator == 'G')) {
    my_size_t size_arg = my_strlen(result_double_string);
    params->width = params->width > size_arg ? params->width : size_arg;
    if ((params->width - size_arg) > 0 && my_strcmp(sign_before_num, "\0"))
      params->width--;
    WriteDoubleToOutputArray(params, str, position, result_double_string,
                             size_arg, sign_before_num);
  }
  return result_double_string;
}

long double getRank(long double num, int *rank) {
  if (num >= 10) {
    while (num >= 10) {
      num /= 10.0;
      (*rank)++;
    }
  } else if (num >= 0 && num < 1) {
    while (num >= 0 && num < 1) {
      num *= 10.0;
      (*rank)--;
    }
  }
  return num;
}

void Specifier_g(SprintfParams *params, char *str, int *position,
                 long double arg_double, char *sign_before_num) {
  static char result_double_string[BUFFERSIZE] = {0};
  my_memset(result_double_string, '\0', BUFFERSIZE);
  if (params->precision == 0) {
    params->precision = 1;
  }
  int flag_null = 0;
  if (arg_double < EPS_NULL) {
    flag_null = 1;
  }
  int rank = 0;
  if (!flag_null) {
    getRank(arg_double, &rank);
  }
  char *ptr = my_NULL;
  if (rank <= -DEFAULT_PRECISION + 1 || rank >= (int)params->precision) {
    if (params->precision == 1) params->precision = 0;
    ptr = Specifier_e(params, str, position, arg_double, sign_before_num);
  } else {
    if (rank >= 0 && (int)params->precision > rank) {
      params->precision = params->precision - rank - 1;
    } else if (rank < 0) {
      params->precision -= rank + 1;
    }
    ptr = Specifier_f(params, str, position, arg_double, sign_before_num);
  }
  if (!params->flag.flag_hashtag) {
    deleteZero(ptr);
  }
  my_size_t size_arg = my_strlen(ptr);
  params->width = params->width > size_arg ? params->width : size_arg;
  if ((params->width - size_arg) > 0 && my_strcmp(sign_before_num, "\0"))
    params->width--;
  WriteDoubleToOutputArray(params, str, position, ptr, size_arg,
                           sign_before_num);
}

void deleteZero(char *bufferResult) {
  int sizeBuffer = my_strlen(bufferResult);
  char *ptrStart = &bufferResult[sizeBuffer];
  char suffix[10] = "\0";
  char *ptrCurrent = suffix;
  if (sizeBuffer > 4) {
    for (int j = 4; j < 6; j++) {
      if (bufferResult[sizeBuffer - j] == 'e' ||
          bufferResult[sizeBuffer - j] == 'E') {
        ptrStart = &bufferResult[sizeBuffer - j];
      }
    }
  }
  while (*ptrStart != '\0') {
    *ptrCurrent = *ptrStart;
    *ptrStart = '\0';
    ptrStart++;
    ptrCurrent++;
  }
  sizeBuffer = my_strlen(bufferResult);
  ptrStart = &bufferResult[sizeBuffer];
  ptrCurrent = &bufferResult[sizeBuffer - 1];
  int i = 0;
  while (*ptrCurrent == '0' && i < sizeBuffer - 1) {
    ptrStart = ptrCurrent;
    ptrCurrent--;
    i++;
  }
  if (*ptrCurrent == '.') {
    ptrStart = ptrCurrent;
  }
  while (*ptrCurrent != '.' && i < sizeBuffer - 1) {
    ptrCurrent--;
    i++;
  }
  if (*ptrCurrent == '.') {
    while (*ptrStart != '\0') {
      *ptrStart = '\0';
      ptrStart++;
    }
  }
  my_strcat(bufferResult, suffix);
}

void Specifier_n(va_list ap, int *position) {
  int *arg_int = va_arg(ap, int *);
  *arg_int = *position;
}

void Specifiers_d_i(SprintfParams *params, va_list ap, char *str,
                    int *position) {
  long arg_int = 0;
  if (params->length == 'h') {
    arg_int = va_arg(ap, int);
    arg_int = ConvertIntToShort(arg_int, params);
  } else if (params->length == 'l') {
    arg_int = va_arg(ap, long int);
  } else {
    arg_int = va_arg(ap, int);
  }
  char *nums_str = convertDigitToSymbol(params, arg_int, DEC);
  if (params->precision == 0 && arg_int == 0) {
    *nums_str = '\0';
  }
  my_size_t size_arg = my_strlen(nums_str);
  params->precision = params->precision > size_arg && params->flag_precision
                          ? params->precision
                          : size_arg;

  params->width =
      params->width > params->precision ? params->width : params->precision;
  char *sign_before_num = params->flag.flag_plus && arg_int >= 0 ? "+"
                          : arg_int < 0                          ? "-"
                          : params->flag.flag_space              ? " "
                                                                 : "\0";
  if ((params->width - params->precision) > 0 &&
      my_strcmp(sign_before_num, "\0"))
    params->width--;

  WriteIntToOutputArray(params, str, position, nums_str, size_arg,
                        sign_before_num);
}

int ConvertIntToShort(long int number, SprintfParams *params) {
  int range = MAX_SHORT_INT - MIN_SHORT_INT + 1;
  int max = MAX_SHORT_INT, min = MIN_SHORT_INT;
  if (params->specificator == 'u' || params->specificator == 'o' ||
      params->specificator == 'x' || params->specificator == 'X') {
    max -= MIN_SHORT_INT;
    min = 0;
  }
  if (number < min || number > max) {
    number %= range;
    number = number < min   ? number + range
             : number > max ? number - range
                            : number;
  }
  return number;
}

void WriteIntToOutputArray(SprintfParams *params, char *str, int *position,
                           char *nums_str, my_size_t size_arg,
                           char *sign_before_num) {
  if (params->flag.flag_minus || params->width == params->precision) {
    putStrToStr(str, position, sign_before_num);
    params->width -= params->precision;
    params->precision -= size_arg;
    while (params->precision) {
      putStrToStr(str, position, "0");
      params->precision--;
    }
    putStrToStr(str, position, nums_str);
    while (params->width) {
      putStrToStr(str, position, " ");
      params->width--;
    }
  } else {
    if (params->flag.flag_zero && !params->flag_precision) {
      putStrToStr(str, position, sign_before_num);
      params->width -= params->precision;
      while (params->width) {
        putStrToStr(str, position, "0");
        params->width--;
      }
      putStrToStr(str, position, nums_str);
    } else {
      params->width -= params->precision;
      while (params->width) {
        putStrToStr(str, position, " ");
        params->width--;
      }
      putStrToStr(str, position, sign_before_num);
      params->precision -= size_arg;
      while (params->precision) {
        putStrToStr(str, position, "0");
        params->precision--;
      }
      putStrToStr(str, position, nums_str);
    }
  }
}

void Specifiers_x_X(SprintfParams *params, va_list ap, char *str,
                    int *position) {
  long arg_int = 0;
  arg_int = params->length == 'l' ? va_arg(ap, unsigned long int)
                                  : va_arg(ap, unsigned int);
  if (params->length == 'h') {
    arg_int = ConvertIntToShort(arg_int, params);
  }
  char *nums_str = convertDigitToSymbol(params, arg_int, HEX);
  my_size_t size_arg = my_strlen(nums_str);
  params->precision = params->precision > size_arg && params->flag_precision
                          ? params->precision
                          : size_arg;
  params->width =
      params->width > params->precision ? params->width : params->precision;
  char *sign_before_num = "\0";
  if (params->flag.flag_hashtag && arg_int != 0) {
    sign_before_num = params->specificator == 'x' ? "0x" : "0X";
  }
  if ((params->width - params->precision) > 1 &&
      my_strcmp(sign_before_num, "\0"))
    params->width -= my_strlen(sign_before_num);
  else if ((params->width - params->precision) > 0 &&
           my_strcmp(sign_before_num, "\0"))
    params->width--;
  WriteIntToOutputArray(params, str, position, nums_str, size_arg,
                        sign_before_num);
}

void Specifier_o(SprintfParams *params, va_list ap, char *str, int *position) {
  long arg_int = 0;
  arg_int = params->length == 'l' ? va_arg(ap, unsigned long int)
                                  : va_arg(ap, unsigned int);
  if (params->length == 'h') {
    arg_int = ConvertIntToShort(arg_int, params);
  }
  char *nums_str = convertDigitToSymbol(params, arg_int, OCT);
  my_size_t size_arg = my_strlen(nums_str);
  params->precision = params->precision > size_arg && params->flag_precision
                          ? params->precision
                          : size_arg;
  params->width =
      params->width > params->precision ? params->width : params->precision;
  char *sign_before_num = "\0";
  if (params->flag.flag_hashtag) {
    sign_before_num = "0";
  }
  if ((params->precision - size_arg) > 0 && my_strcmp(sign_before_num, "\0"))
    params->precision--;
  if ((params->width - params->precision) > 0 &&
      my_strcmp(sign_before_num, "\0"))
    params->width--;
  WriteIntToOutputArray(params, str, position, nums_str, size_arg,
                        sign_before_num);
}

void Specifier_u(SprintfParams *params, va_list ap, char *str, int *position) {
  long arg_int = 0;
  arg_int = params->length == 'l' ? va_arg(ap, unsigned long int)
                                  : va_arg(ap, unsigned int);
  if (params->length == 'h') {
    arg_int = ConvertIntToShort(arg_int, params);
  }
  char *nums_str = convertDigitToSymbol_U(params, arg_int, DEC);
  if (params->precision == 0 && arg_int == 0) {
    *nums_str = '\0';
  }
  my_size_t size_arg = my_strlen(nums_str);
  params->precision = params->precision > size_arg && params->flag_precision
                          ? params->precision
                          : size_arg;
  params->width =
      params->width > params->precision ? params->width : params->precision;
  char *sign_before_num = "\0";
  WriteIntToOutputArray(params, str, position, nums_str, size_arg,
                        sign_before_num);
}

void Specifier_p(SprintfParams *params, va_list ap, char *str, int *position) {
  long *arg_ptr = va_arg(ap, long int *);
  long arg_int = (long int)arg_ptr;
  char *nums_str = convertDigitToSymbol(params, arg_int, HEX);
#ifdef __linux__
  if (arg_ptr == my_NULL) {
    nums_str -= 4;
    my_strcpy(nums_str, "(nil)");
    params->precision = my_strlen(nums_str);
    params->width++;
    params->flag.flag_hashtag = 0;
    params->flag.flag_plus = 0;
    params->flag.flag_space = 0;
    params->flag.flag_zero = 0;
  }
#endif
  my_size_t size_arg = my_strlen(nums_str);
  params->precision = params->precision > size_arg && params->flag_precision
                          ? params->precision
                          : size_arg;
  params->width =
      params->width > params->precision ? params->width : params->precision;
#ifdef __APPLE__
  char *sign_before_num = "0x";
#elif __linux__

  char *sign_before_num = arg_ptr == my_NULL        ? "\0"
                          : params->flag.flag_plus  ? "+0x"
                          : params->flag.flag_space ? " 0x"
                                                    : "0x";
#endif
  if ((params->width - params->precision) > 0 &&
      my_strlen(sign_before_num) > 0) {
    params->width--;
  }
  if ((params->width - params->precision) > 0 &&
      my_strlen(sign_before_num) == 3) {
    params->width--;
  }
  if ((params->width - params->precision) > 0) {
    params->width--;
  }
  WriteIntToOutputArray(params, str, position, nums_str, size_arg,
                        sign_before_num);
}
