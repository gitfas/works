/*
 * last updated : 2009/10/07-01:32:59
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common.h"

/*
 * ファイル読み込み関数
 */
int info_file_read() {
  // 定義、初期化
  int ret;
  char *file_name = INFO_FILE;
  FILE *fp;
  int cnt = 0;
  struct material *temp_ptr = NULL; // realloc用の一時ポインタ

  // materialのサイズ分のメモリ領域を取得
  if ((mtrl_ptr = (struct material *) malloc(sizeof(struct material))) == NULL) {
    printf("メモリ確保に失敗しました。\n");
	return EXIT_FAILURE;
  }
  //ファイルのオープン出来たかどうか。
  if ((fp = fopen(file_name, "r")) == NULL) {
    printf("[%s]ファイルが開けません。\n", INFO_FILE);
	return EXIT_FAILURE;
  }
  while ((ret = fscanf(fp, "%d,%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],",
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
	  return EXIT_FAILURE;
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

/*
 * 入力を要求して material に格納する
 */
struct material input_material() {
  // 定義、初期化
  struct material tmp_mtrl;

  // IDを決定が漏れてる
  tmp_mtrl.id = 10;
  
  printf("モデルを入力:");
  scanf("%s", tmp_mtrl.model);
  
  printf("型名を入力:");
  scanf("%s", tmp_mtrl.model_name);
  
  printf("管理番号を入力:");
  scanf("%s", tmp_mtrl.ctrl_number);
  
  printf("識別名を入力:");
  scanf("%s", tmp_mtrl.diff_name);
  
  printf("備考を入力:");
  scanf("%s", tmp_mtrl.note);
  
  printf("その他を入力:");
  scanf("%s", tmp_mtrl.others);

  return tmp_mtrl;
}

/*
 * material を整形して表示する
 */
void format_material(struct material tmp_mtrl) {
  printf("------------------------------\n");
  printf("id:%d", tmp_mtrl.id);
  printf("モデル:%s\n", tmp_mtrl.model);
  printf("型名:%s\n", tmp_mtrl.model_name);
  printf("管理番号:%s\n", tmp_mtrl.ctrl_number);
  printf("識別名:%s\n", tmp_mtrl.diff_name);
  printf("備考:%s\n", tmp_mtrl.note);
  printf("その他:%s\n", tmp_mtrl.others);
  printf("------------------------------\n");
}

/*
 * yes/no を入力させ、True/Falseを返す
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

/*
 * material をファイルへ追加書き込み
 * 返り値:T/F
 */
int info_file_write_add(struct material tmp_mtrl) {
  // 定義、初期化
  FILE *fp;
  int i;
  char *joint_str[] = {
	(char *)tmp_mtrl.id,
	tmp_mtrl.model,
	tmp_mtrl.model_name,
	tmp_mtrl.ctrl_number,
	tmp_mtrl.diff_name,
	tmp_mtrl.note,
	tmp_mtrl.others
  };
  char jointed[sizeof(struct material)];

  if ((fp = fopen(INFO_FILE, "a")) == NULL) {
    printf("[%s]ファイルが開けません。\n", INFO_FILE);
	return EXIT_FAILURE;
  }

  for (i = 0; i < 7; i++) {
	strcat(jointed, joint_str[i]);
  }
  fputs(jointed, fp);
  fclose(fp);

  return EXIT_SUCCESS;
}
