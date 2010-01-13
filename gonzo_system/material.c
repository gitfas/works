/**
 * @file
 * material 構造体用関数ファイル
 * @author Arakawa
 * @date last updated : 2009/12/20-23:43:24
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common.h"
#include "material.h"

/**
 * MATERIAL_FILE を読み込み読み込んだ行数を返す。
 * @retval int 成功した場合、EXIT_SUCCESSを返す。
 * @retval EXIT_FAILURE 失敗した場合、EXIT_FAILUREを返す。
 */
int material_file_read() {
  // 定義、初期化
  FILE *fp;
  char buf[LINE_BUFFER];
  int cnt = 0;
  
  if (mtrl_ptr != NULL) {
	free(mtrl_ptr);
  }
  mtrl_ptr = (struct material *) malloc(sizeof(struct material));
  
  // ファイルのオープン
  if ((fp = fopen(MATERIAL_FILE, "r")) == NULL) {
	printf("[%s]ファイルが開けません。\n", MATERIAL_FILE);
	return EXIT_FAILURE;
  }

  // ファイルを読み込み
  while (fgets(buf, LINE_BUFFER, fp) != NULL) {
	printf("%s", buf);
	line_buf_material((char*)buf);
	
	memset(buf, '\0', sizeof(LINE_BUFFER));
	cnt++;
  }
  printf("cnt : %d\n", 1);
  // ファイルを閉じる
  fclose(fp);
  
  return EXIT_SUCCESS;
}

/**
 * material をファイルへ追加書き込みする。
 * @retval EXIT_SUCCESS 追加書き込みに成功を返す。
 * @retval EXIT_FAILURE 追加書き込みに失敗を返す。
 */
int material_file_write_add(struct material tmp_mtrl) {
  // 定義、初期化
  FILE *fp;
  int i;
  char *joint_str[] = {
	(char *)tmp_mtrl.id,
	tmp_mtrl.model,
	tmp_mtrl.model_name,
	tmp_mtrl.control_id,
	tmp_mtrl.alias,
	tmp_mtrl.status,
	tmp_mtrl.place,
	tmp_mtrl.blame,
	tmp_mtrl.date
  };
  char jointed[sizeof(struct material)];

  if ((fp = fopen(MATERIAL_FILE, "a")) == NULL) {
    printf("[%s]ファイルが開けません。\n", MATERIAL_FILE);
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

  tmp_mtrl.model 
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
  
  printf("状態を入力:");
  scanf("%s", tmp_mtrl.status);
  
  printf("現在地を入力:");
  scanf("%s", tmp_mtrl.place);
  
  printf("責任者を入力:");
  scanf("%s", tmp_mtrl.blame);
  
  printf("最終更新日時を入力:");
  scanf("%s", tmp_mtrl.date);
  
  return tmp_mtrl;
}

/**
 * material を整形して表示する
 * @param material構造体を渡す。
 */
void format_material(struct material tmp_mtrl) {
  printf("------------------------------\n");
  printf("id:%d\n", tmp_mtrl.id);
  printf("モデル:%s\n", tmp_mtrl.model);
  printf("型名:%s\n", tmp_mtrl.model_name);
  printf("管理番号:%s\n", tmp_mtrl.control_id);
  printf("識別名:%s\n", tmp_mtrl.alias);
  printf("------------------------------\n");
}

/**
 * materialを初期化する。
 * @param materialを渡す。
 */
void init_material(struct material *mtrl) {
  mtrl -> id = 0;
  memset(mtrl -> model		, '\0', sizeof(mtrl -> model));
  memset(mtrl -> model_name	, '\0', sizeof(mtrl -> model_name));
  memset(mtrl -> control_id	, '\0', sizeof(mtrl -> control_id));
  memset(mtrl -> alias		, '\0', sizeof(mtrl -> alias));
  memset(mtrl -> status		, '\0', sizeof(mtrl -> status));
  memset(mtrl -> place		, '\0', sizeof(mtrl -> place));
  memset(mtrl -> blame		, '\0', sizeof(mtrl -> blame));
  memset(mtrl -> date		, '\0', sizeof(mtrl -> date));
}

/**
 * MATERIAL_FILEの1行をカンマ区切りで分解してmaterial構造体を生成する。
 * @param char[LINE_BUFFER] 1行
 * @return struct material 1行データから生成したmaterial構造体
 */
struct material line_buf_material(char buf[LINE_BUFFER]) {
  int place = 0;
  int place_old = 0;
  int cnt = 0;
  int i;
  char temp_buf[LINE_BUFFER];
  struct material mtrl_buf;

  while((place != -1) && (cnt < MATERIAL_NUM)) {
	place_old = place;
	place = cammna_search(buf, place);
#if DEBUG_PRINT
	printf("place:%d -> %d\n", place_old, place);
#endif
	if (place == -1) {
	  printf("csvデータが足りていない可能性があります。\n");
	  printf("%d列目のデータを見直してください。\n", (cnt + 1));
	  break;
	} else {
	  memset(temp_buf, '\0', sizeof(temp_buf));
	  memcpy(temp_buf, &buf[place_old], (place - place_old));
	  
	  for (i = 0; i < MATERIAL_NUM; i++) {
		switch (cnt) {
		case 0: mtrl_buf.id			= atoi(temp_buf);
		  break;
		case 1: mtrl_buf.model		= temp_buf;
		  break;
		case 2: mtrl_buf.model_name	= temp_buf;
		  break;
		case 3: mtrl_buf.control_id	= temp_buf;
		  break;
		case 4: mtrl_buf.alias		= temp_buf;
		  break;
		case 5: mtrl_buf.status		= temp_buf;
		  break;
		case 6: mtrl_buf.place		= temp_buf;
		  break;
		case 7: mtrl_buf.blame		= temp_buf;
		  break;
		case 8: mtrl_buf.date		= temp_buf;
		  break;
		default :
		  break;
		}
	  }
	  if (cnt < MATERIAL_NUM){
		cnt++;
	  }else{
		printf("MATERIAL_NUMを超えるカンマがありました");
		break;
	  }
	}
  }
  return mtrl_buf;
}
