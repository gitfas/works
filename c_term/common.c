/*
 * last updated : 2009/09/27-23:01:10
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common.h"

/*
 * ファイル読み込み関数
 */
int file_read() {
  // 定義、初期化
  int ret;
  char *file_name = "abc.txt";
  FILE *fp = fopen(file_name, "r");
  int cnt = 0;
  struct material *temp_ptr = NULL; // realloc用の一時ポインタ

  // materialのサイズ分のメモリ領域を取得
  mtrl_ptr = (struct material *) malloc(sizeof(struct material));
  //ファイルのオープン出来たかどうか。			 
  if (fp == NULL) {
    printf("[%s]ファイルが開けません。\n", file_name);
  }
  while ( (ret = fscanf(fp, "%d,%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],",
			&(mtrl_ptr + cnt) -> id, 
			(mtrl_ptr + cnt) -> model, 
			(mtrl_ptr + cnt) -> model_name, 
			(mtrl_ptr + cnt) -> ctrl_number, 
			(mtrl_ptr + cnt) -> diff_name, 
			(mtrl_ptr + cnt) -> note, 
			(mtrl_ptr + cnt) -> others)) != EOF) {
    // 次のメモリを確保する
    cnt++;
    temp_ptr = realloc(mtrl_ptr, (sizeof(struct material) * (cnt + 1)));

    if (temp_ptr == NULL) {
      printf("メモリ確保に失敗しました。\n");
      free(mtrl_ptr);
      return -1;
    } else {
      mtrl_ptr = temp_ptr;
    }
  }
  
  // 使われ無かった最後のメモリを削除
  temp_ptr = realloc(mtrl_ptr, (sizeof(struct material) * (cnt)));

  if (temp_ptr == NULL) {
    printf("メモリ確保に失敗しました。\n");
    free(mtrl_ptr);
    return -1;
  } else {
    mtrl_ptr = temp_ptr;
  }
  
  // ファイルを閉じる
  fclose(fp);
  
  return cnt;
}

/*
 * 文字列から、カンマ（，）の位置を検索する
 */
int cammna_search(char *str) {
  char *comma = ",";
  char *place;
  
  place = strstr(str, comma);
  printf("'%s'の中に現れる'%s'という文字列は%d文字目にある.\n", str, comma, place - str + 1);
  return 1;
}

/*
 * UTF-8の文字列の文字数をカウントする
 */
int count_UTF8(const unsigned char *string) {
  int len = 0;
  
  while(*string) {
    if (*string < 0x1f || *string == 0x7f) {
      //制御コード
    } else if (*string <= 0x7f) {
      ++len; // 1バイト文字
    } else if (*string <= 0xbf) {
      // 文字の続き
    } else if (*string <= 0xdf) {
      ++len; // 2バイト文字
    } else if (*string <= 0xef) {
      ++len; // 3バイト文字
    } else if (*string <= 0xf7) {
      ++len; // 4バイト文字
    } else if (*string <= 0xfb) {
      ++len; // 5バイト文字
    } else if (*string <= 0xfd) {
      ++len; // 6バイト文字
    } else {
      // 使われていない
    }
    string++;
  }

  return len;
}
