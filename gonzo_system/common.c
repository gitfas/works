/**
 * @file
 * 共通関数ファイル
 * @author Arakawa
 * @date last updated : 2009/10/19-01:39:27
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common.h"

/**
 * mallocでエラーが出た場合の文字列を出力する。
 * @param 関数名を渡す。
 * @return int EXIT_FAILUREを返す。
 */
int error_malloc(char *string) {
  printf("%s内でメモリ確保に失敗しました。\n", string);
  return EXIT_FAILURE;
}

/**
 * 文字列から、カンマ（，）の位置を検索する。
 * @param 文字列を渡す。
 * @retval int カンマがあった位置を返す。
 * @retval 0 カンマが見つからない場合に返す。
 */
int cammna_search(char *str, int now) {
  char *comma = ",";
  char *place;
  
  place = strstr((str + now), comma);
  //printf("'%s'の中に現れる'%s'という文字列は%d文字目にある.\n", str, comma, place - str + 1);
  if (place == NULL) {
	return -1;
  } else {
	return (int)(place - str + 1);
  }
}

/**
 * UTF-8の文字列の文字数をカウントする。
 * @param UTF-8の文字列を渡す。
 * @return int カウントした文字数を返す。
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

/**
 * yes/no を入力させ、True/Falseを返す。
 * @retval TRUE "Y","y"を入力した場合に返す。
 * @retval FALSE "N","n"を入力した場合に返す。
 */
int query_ok_ng() {
  // 定義、初期化
  int c;
  int flag;
  
  printf("以上の登録内容でよろしいですか。Y/N:");
  while((c = getchar()) != EOF) {
	switch(c) {
	case YES:
	case yes:
	  flag = TRUE;
	  goto LOOP_OUT;
	case NO:
	case no:
	  return FALSE;
	  goto LOOP_OUT;
	default:
	  printf("Y/N を入力してください。\n");
	}
  }
 LOOP_OUT:
  return flag;
}
