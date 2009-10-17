/**
 * @file
 * material 構造体用関数ファイル
 * @author Arakawa
 * @date last updated : 2009/10/18-03:21:38
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common.h"
#include "material.h"

/**
 * INFO_FILE を読み込み読み込んだ行数を返す。
 * @retval int 成功した場合、読み込んだ行数を返す。
 * @retval EXIT_FAILURE 失敗した場合、EXIT_FAILUREを返す。
 */
int info_file_read() {
  // 定義、初期化
  FILE *fp;
  char *buf = (char*) malloc(sizeof(LINE_BUFFER) + 1);
  int cnt = 0;

  // ファイルのオープン
  if ((fp = fopen(INFO_FILE, "r")) == NULL) {
	printf("[%s]ファイルが開けません。\n", INFO_FILE);
	return EXIT_FAILURE;
  }
  
  // ファイルを読み込み
  while (fgets(buf, LINE_BUFFER, fp) != NULL) {
	
  }
  
  // ファイルを閉じる
  fclose(fp);
  
  return cnt;
}

/**
 * material をファイルへ追加書き込みする。
 * @retval EXIT_SUCCESS 追加書き込みに成功を返す。
 * @retval EXIT_FAILURE 追加書き込みに失敗を返す。
 */
int info_file_write_add(struct material tmp_mtrl) {
  // 定義、初期化
  FILE *fp;
  int i;
  char *joint_str[] = {
	(char *)tmp_mtrl.id,
	tmp_mtrl.model,
	tmp_mtrl.model_name,
	tmp_mtrl.control_id,
	tmp_mtrl.alias,
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

/**
 * 入力を要求して material に格納する。
 * @return struct material 入力を構造体に代入して返す。
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
  scanf("%s", tmp_mtrl.control_id);
  
  printf("識別名を入力:");
  scanf("%s", tmp_mtrl.alias);
  
  printf("備考を入力:");
  scanf("%s", tmp_mtrl.note);
  
  printf("その他を入力:");
  scanf("%s", tmp_mtrl.others);

  return tmp_mtrl;
}

/**
 * material を整形して表示する
 * @param material構造体を渡す。
 */
void format_material(struct material tmp_mtrl) {
  printf("------------------------------\n");
  printf("id:%d", tmp_mtrl.id);
  printf("モデル:%s\n", tmp_mtrl.model);
  printf("型名:%s\n", tmp_mtrl.model_name);
  printf("管理番号:%s\n", tmp_mtrl.control_id);
  printf("識別名:%s\n", tmp_mtrl.alias);
  printf("備考:%s\n", tmp_mtrl.note);
  printf("その他:%s\n", tmp_mtrl.others);
  printf("------------------------------\n");
}

/**
 * materialを初期化する。
 * @param materialを渡す。
 */
void init_material(struct material *mtrl) {
  mtrl -> id = 0;
  memset(mtrl -> model, (int)NULL_CHAR, sizeof(mtrl -> model));
  memset(mtrl -> model_name, (int)NULL_CHAR, sizeof(mtrl -> model_name));
  memset(mtrl -> control_id, (int)NULL_CHAR, sizeof(mtrl -> control_id));
  memset(mtrl -> alias, (int)NULL_CHAR, sizeof(mtrl -> alias));
  memset(mtrl -> note, (int)NULL_CHAR, sizeof(mtrl -> note));
  memset(mtrl -> others, (int)NULL_CHAR, sizeof(mtrl -> others));
}
