#include "../headers/my_string.h"

#define BUFFER_SIZE 4096

#ifdef __APPLE__
static char *ErrorNames[] = {"Undefined error: 0",
                             "Operation not permitted",
                             "No such file or directory",
                             "No such process",
                             "Interrupted system call",
                             "Input/output error",
                             "Device not configured",
                             "Argument list too long",
                             "Exec format error",
                             "Bad file descriptor",
                             "No child processes",
                             "Resource deadlock avoided",
                             "Cannot allocate memory",
                             "Permission denied",
                             "Bad address",
                             "Block device required",
                             "Resource busy",
                             "File exists",
                             "Cross-device link",
                             "Operation not supported by device",
                             "Not a directory",
                             "Is a directory",
                             "Invalid argument",
                             "Too many open files in system",
                             "Too many open files",
                             "Inappropriate ioctl for device",
                             "Text file busy",
                             "File too large",
                             "No space left on device",
                             "Illegal seek",
                             "Read-only file system",
                             "Too many links",
                             "Broken pipe",
                             "Numerical argument out of domain",
                             "Result too large",
                             "Resource temporarily unavailable",
                             "Operation now in progress",
                             "Operation already in progress",
                             "Socket operation on non-socket",
                             "Destination address required",
                             "Message too long",
                             "Protocol wrong type for socket",
                             "Protocol not available",
                             "Protocol not supported",
                             "Socket type not supported",
                             "Operation not supported",
                             "Protocol family not supported",
                             "Address family not supported by protocol family",
                             "Address already in use",
                             "Can't assign requested address",
                             "Network is down",
                             "Network is unreachable",
                             "Network dropped connection on reset",
                             "Software caused connection abort",
                             "Connection reset by peer",
                             "No buffer space available",
                             "Socket is already connected",
                             "Socket is not connected",
                             "Can't send after socket shutdown",
                             "Too many references: can't splice",
                             "Operation timed out",
                             "Connection refused",
                             "Too many levels of symbolic links",
                             "File name too long",
                             "Host is down",
                             "No route to host",
                             "Directory not empty",
                             "Too many processes",
                             "Too many users",
                             "Disc quota exceeded",
                             "Stale NFS file handle",
                             "Too many levels of remote in path",
                             "RPC struct is bad",
                             "RPC version wrong",
                             "RPC prog. not avail",
                             "Program version wrong",
                             "Bad procedure for program",
                             "No locks available",
                             "Function not implemented",
                             "Inappropriate file type or format",
                             "Authentication error",
                             "Need authenticator",
                             "Device power is off",
                             "Device error",
                             "Value too large to be stored in data type",
                             "Bad executable (or shared library)",
                             "Bad CPU type in executable",
                             "Shared library version mismatch",
                             "Malformed Mach-o file",
                             "Operation canceled",
                             "Identifier removed",
                             "No message of desired type",
                             "Illegal byte sequence",
                             "Attribute not found",
                             "Bad message",
                             "EMULTIHOP (Reserved)",
                             "No message available on STREAM",
                             "ENOLINK (Reserved)",
                             "No STREAM resources",
                             "Not a STREAM",
                             "Protocol error",
                             "STREAM ioctl timeout",
                             "Operation not supported on socket",
                             "Policy not found",
                             "State not recoverable",
                             "Previous owner died",
                             "Interface output queue is full"};
#elif __linux__
static char *ErrorNames[] = {
    "Success",
    "Operation not permitted",
    "No such file or directory",
    "No such process",
    "Interrupted system call",
    "Input/output error",
    "No such device or address",
    "Argument list too long",
    "Exec format error",
    "Bad file descriptor",
    "No child processes",
    "Resource temporarily unavailable",
    "Cannot allocate memory",
    "Permission denied",
    "Bad address",
    "Block device required",
    "Device or resource busy",
    "File exists",
    "Invalid cross-device link",
    "No such device",
    "Not a directory",
    "Is a directory",
    "Invalid argument",
    "Too many open files in system",
    "Too many open files",
    "Inappropriate ioctl for device",
    "Text file busy",
    "File too large",
    "No space left on device",
    "Illegal seek",
    "Read-only file system",
    "Too many links",
    "Broken pipe",
    "Numerical argument out of domain",
    "Numerical result out of range",
    "Resource deadlock avoided",
    "File name too long",
    "No locks available",
    "Function not implemented",
    "Directory not empty",
    "Too many levels of symbolic links",
    "Unknown error 41",
    "No message of desired type",
    "Identifier removed",
    "Channel number out of range",
    "Level 2 not synchronized",
    "Level 3 halted",
    "Level 3 reset",
    "Link number out of range",
    "Protocol driver not attached",
    "No CSI structure available",
    "Level 2 halted",
    "Invalid exchange",
    "Invalid request descriptor",
    "Exchange full",
    "No anode",
    "Invalid request code",
    "Invalid slot",
    "Unknown error 58",
    "Bad font file format",
    "Device not a stream",
    "No data available",
    "Timer expired",
    "Out of streams resources",
    "Machine is not on the network",
    "Package not installed",
    "Object is remote",
    "Link has been severed",
    "Advertise error",
    "Srmount error",
    "Communication error on send",
    "Protocol error",
    "Multihop attempted",
    "RFS specific error",
    "Bad message",
    "Value too large for defined data type",
    "Name not unique on network",
    "File descriptor in bad state",
    "Remote address changed",
    "Can not access a needed shared library",
    "Accessing a corrupted shared library",
    ".lib section in a.out corrupted",
    "Attempting to link in too many shared libraries",
    "Cannot exec a shared library directly",
    "Invalid or incomplete multibyte or wide character",
    "Interrupted system call should be restarted",
    "Streams pipe error",
    "Too many users",
    "Socket operation on non-socket",
    "Destination address required",
    "Message too long",
    "Protocol wrong type for socket",
    "Protocol not available",
    "Protocol not supported",
    "Socket type not supported",
    "Operation not supported",
    "Protocol family not supported",
    "Address family not supported by protocol",
    "Address already in use",
    "Cannot assign requested address",
    "Network is down",
    "Network is unreachable",
    "Network dropped connection on reset",
    "Software caused connection abort",
    "Connection reset by peer",
    "No buffer space available",
    "Transport endpoint is already connected",
    "Transport endpoint is not connected",
    "Cannot send after transport endpoint shutdown",
    "Too many references: cannot splice",
    "Connection timed out",
    "Connection refused",
    "Host is down",
    "No route to host",
    "Operation already in progress",
    "Operation now in progress",
    "Stale file handle",
    "Structure needs cleaning",
    "Not a XENIX named type file",
    "No XENIX semaphores available",
    "Is a named type file",
    "Remote I/O error",
    "Disk quota exceeded",
    "No medium found",
    "Wrong medium type",
    "Operation canceled",
    "Required key not available",
    "Key has expired",
    "Key has been revoked",
    "Key was rejected by service",
    "Owner died",
    "State not recoverable",
    "Operation not possible due to RF-kill",
    "Memory page has hardware error"};
#endif

char *my_strtok(char *str, const char *delim) {
  static char *result_prev_search = my_NULL;
  char *ptr_start = my_NULL;
  char *ptr_end = my_NULL;
  if (str == my_NULL) {
    ptr_start = result_prev_search;
  } else {
    ptr_start = str;
  }
  if (ptr_start != my_NULL) {
    my_size_t offset = my_strspn(ptr_start, delim);
    if (offset == my_strlen(ptr_start)) {
      ptr_start = my_NULL;
    } else {
      ptr_start += offset;
      ptr_end = ptr_start;
      offset = my_strcspn(ptr_end, delim);
      ptr_end += offset;
      if (*ptr_end != '\0') {
        *ptr_end = '\0';
        ptr_end++;
      }
    }
  }
  result_prev_search = ptr_end;
  return ptr_start;
}

char *my_strcat(char *dest, const char *src) {
  char *ptr_start = my_NULL;
  size_t index = 0;
  while (dest[index] != '\0') {
    index++;
  }
  ptr_start = &dest[index];
  index = 0;
  while (src[index] != '\0') {
    ptr_start[index] = src[index];
    index++;
  }
  ptr_start[index] = '\0';
  return dest;
}

char *my_strncat(char *dest, const char *src, my_size_t n) {
  char *ptr_start = my_NULL;
  size_t index = 0;
  while (dest[index] != '\0') {
    index++;
  }
  ptr_start = &dest[index];
  index = 0;
  while (src[index] != '\0' && index < n) {
    ptr_start[index] = src[index];
    index++;
  }
  ptr_start[index] = '\0';
  return dest;
}

char *my_strerror(int errnum) {
  char *result_message = my_NULL;
#ifdef __APPLE__
  static char message[256] = "\0";
#elif __linux__
  static char message[256] = "\0";
#endif
  my_memset(message, '\0', 256);
#ifdef __APPLE__
  my_strcpy(message, "Unknown error: ");
#elif __linux__
  my_strcpy(message, "Unknown error ");
#endif
  char *convert_symbols = "0123456789";
  char buf[BUFFER_SIZE] = {0};
  int convert = 0;
#ifdef __APPLE__
  if (errnum < 0 || errnum > 106) {
    convert = 1;
  }
#elif __linux__
  if (errnum < 0 || errnum > 133) {
    convert = 1;
  }
#endif
  if (convert) {
    if (errnum < 0) {
      my_strcat(message, "-");
      errnum *= -1;
    }
    int int_part_num = errnum;
    int div = 0;
    char symbol;
    my_size_t index = 0;
    do {
      div = int_part_num % 10;
      int_part_num /= 10;
      symbol = convert_symbols[div];
      if (index == 0) {
        buf[index] = symbol;
      } else {
        int i = 0;
        char tmp = '\0';
        while (symbol != '\0') {
          tmp = buf[i];
          buf[i] = symbol;
          symbol = tmp;
          i++;
        }
      }
      index++;
    } while (int_part_num != 0);
    my_strcat(message, buf);
    result_message = message;
  } else {
    result_message = ErrorNames[errnum];
  }
  return result_message;
}
