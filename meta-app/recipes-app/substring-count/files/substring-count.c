#include <stdint.h>
#include <stdio.h>
#include <string.h>

#define BUF_MAX_SIZE 1024

#define min(x, y) ((x)>(y)?(y):(x))

int n_match_bytes(uint8_t *buf1, uint8_t* buf2, int size) {
  for (int i =0 ;i  < size; i++) {
    if (*buf1 != *buf2) {
      return i;
    }
    buf1++;
    buf2++;
  }
  return size;
}
int main(int argc, char **args) {
  FILE *input_file;

  int overlap = 0;
  char* filename;
  char* substring;
  
  if (argc == 4 && strcmp("--overlap", args[1]) == 0) {
    overlap = 1;
    filename = args[2];
    substring = args[3];
   
    // overlap means "aaa" has 2 substring "aa"
    // not supported yet
    //
    printf("usage: substring-count <file path> <substring>\n");
    return -1;
  } else if (argc == 3) {
    overlap = 0;
    filename = args[1];
    substring = args[2];
  } else {
    printf("usage: substring-count <file path> <substring>\n");
    return -1;
  }
 
  input_file = fopen(args[1], "r");
  uint8_t buf[BUF_MAX_SIZE];
  int buf_len = 0;
  int buf_offset = 0;

  uint8_t* sstr = (uint8_t*)substring;
  int sstr_len = strlen(substring);
  int sstr_offset = 0;

  int max = 0;
  int sum = 0;

  // the file for ther first time
  // 
  // the buffer might not contains the whole content of the files
  // so we must store the current comparing position to continuously 
  // read the file
  //
  buf_len = fread(buf, 1, BUF_MAX_SIZE, input_file);


  while (buf_len) {

    // repeatly compare the file content with the input substring and
    // count it untils the sequence breaks.
    int count = 0;
    while (buf_len) {
      int n = min(buf_len-buf_offset, sstr_len - sstr_offset);

      // compare n valid bytes of the buffer and the input substring.
      // 
      // if matched, continue to read the file if match and increase
      // count var if match whole input substring.
      //
      // else the row is breaks, start to compare input substring
      // from the next bytes from the file.
      if (n_match_bytes(buf+buf_offset, sstr+ sstr_offset, n) == n){
        buf_offset += n;
        sstr_offset += n;
        
        if (buf_offset == buf_len) {
          buf_len = fread(buf, 1, BUF_MAX_SIZE, input_file);
          buf_offset = 0;
        }
        if (sstr_offset == sstr_len) {
          count += 1;
          sstr_offset = 0;
        }
      } else {
        buf_offset += 1;
        break;
      }
    }
    sum += count;
    if (count > max) {
      max = count;
    }
  }


  printf("\"%s\" occurs %d times, max %d times continuously\n", substring, sum, max);
  


  return 0;
}
