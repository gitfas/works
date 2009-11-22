/**
 * @file
 * 共通関数ファイル
 * @author Arakawa
 * @date last updated : 2009/11/23-03:23:39
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common.h"


/**
 * タイトル文字列を整形出力する(テキスト)
 * @param char* string タイトル文字列
 */
void format_print_title(char string[PRINT_FORMAT_LEN]) {
  int i;

  printf("  +----- %s ", string);
  for(i = 0; i < (PRINT_FORMAT_LEN - strlen(string)) + 2; i++) {
	printf("-");
  }
  printf("+\n");
}

/**
 * メニュー文字列を整形出力する(テキスト)
 * @param char string[][PRINT_FORMAT_LEN] メニュー文字列
 * @param int cnt メニューの数
 */
void format_print_menu(char string[][PRINT_FORMAT_LEN], int cnt) {
  int i,j;
#if DEBUG_PRINT
  printf("メニューの数:%d\n", cnt);
#endif

  for(i = 0; i < cnt; i++) {
	printf("  | %d. %s ", (i + 1), string[i]);
	for(j = 0; j < (PRINT_FORMAT_LEN - (strlen(string[i])/3*2) - 4); j++) {
	  printf(" ");
	}
	printf("|\n");
  }
}

/**
 * 整形出力のラインを出力する(テキスト)
 */
void format_print_line() {
  int i;
  
  printf("  +");
  for(i = 0; i < PRINT_FORMAT_LEN + 1; i++) {
	printf("-");
  }
  printf("+\n");
}

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
