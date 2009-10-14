/**
 * @file
 * 共通関数ファイル
 * @author Arakawa
 * @date last updated : 2009/10/15-01:52:59
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
 * 取得したintをmallocしてintポインタを返す。
 * @return int* mallocしたintポインタを返す。
 */
int* gen_int() {
  // 定義、初期化
  int *pack;

  if (pack = (int) malloc(sizeof(int)) == NULL) {
	return error_malloc("gen_int");
  }
  *pack = INIT_INT;
  return &pack;
}

/**
 * 取得charをmallocしてcharポインタを返す。
 * @return char* mallocしたcharポインタを返す。
 */
char* gen_char() {
  // 定義、初期化
  char *pack;

  if (pack = (char) malloc(sizeof(STRING_BUFFER) + 1) == NULL) {
	return error_malloc("gen_char");
  }
  memset(pack, INIT_CHAR, STRING_BUFFER);
  return pack;
}

/**
 * materialを初期化する。
 * @param materialを渡す。
 * @return struct material 初期化されたmaterialを返す。
 */
void init_material(struct material *mtrl) {
  mtrl -> id = gen_int();
  mtrl -> model = gen_char();
  mtrl -> model_name = gen_char();
  mtrl -> control_id = gen_char();
  mtrl -> alias = gen_char();
  mtrl -> note = gen_char();
  mtrl -> others = gen_char();
}

/**
 * INFO_FILE を読み込み読み込んだ行数を返す。
 * @return int 成功した場合、読み込んだ行数を返す。失敗した場合、EXIT_FAILUREを返す。
 */
int info_file_read() {
  // 定義、初期化
  int ret;
  char *file_name = INFO_FILE;
  FILE *fp;
  int cnt = 0;
  unsigned char buf[LINE_BUFFER];
  struct material m_val;
  struct material *temp_ptr = NULL; // realloc用の一時ポインタ
  init_material(m_val);
 
  // materialのサイズ分のメモリ領域を取得
  if ((mtrl_ptr = (struct material *) malloc(sizeof(struct material))) == NULL) {
	return error_malloc("info_file_read");
  }
  
  // ファイルのオープン
  if ((fp = fopen(INFO_FILE, "r")) == NULL) {
	printf("[%s]ファイルが開けません。\n", INFO_FILE);
	return EXIT_FAILURE;
  }

  while (fgets(buf, LINE_BUFFER, fp) != NULL) {
	// 空行の場合、処理しない
	if (sizeof(buf) == 1) {
	  continue;
	}
	
	// 改行文字が含まれているかの確認
	if (strchr(buf, '\n') != NULL) {
	  // 改行文字を終端記号に置換する
	  buf[strlen(buf) - 1] = '\0';
	} else {
	  // 超えている場合は、切って最後に終端文字を代入する
	  buf[LINE_BUFFER - 1] = '\0';
	}
	
	if (mtrl_ptr == NULL) {
	  // materialのサイズ分のメモリ領域を取得する。
	  if ((mtrl_ptr = (struct material *) malloc(sizeof(struct material))) == NULL) {
		fclose(fp);
		return error_malloc("info_file_read");
	  }
	} else {
	  // reallocする。
	  temp_ptr = realloc(mtrl_ptr, (sizeof(struct material) * (cnt + 1)));
	  
	  if (temp_ptr == NULL) {
		fclose(fp);
		free(mtrl_ptr);
		return error_malloc("info_file_read");
	  } else {
		mtrl_ptr = temp_ptr;
	  }
	}
	// 構造体を代入
	(mtrl_ptr + cnt) = line_buf_material(buf);
	// カウントを増やす
	cnt++;
	// bufを初期化
	memset(buf, '\0', LINE_BUFFER);
  }
  
  // ファイルを閉じる
  fclose(fp);
  
  return cnt;
}

/**
 * 行をカンマ分割して構造体に代入する。（ただし、先頭から７つまで）
 * @param 行。
 * @return struct material 行をmaterialに変換した構造体を返す。
 */
struct material line_buf_material(unsigned char buf[LINE_BUFFER]) {
  // 定義、初期化
  struct material line_mtrl;
  char temp[MATERIAL_NUM][STRING_BUFFER];
  int *place;
  int i = 0;
  int j = 0;
  init_material(line_mtrl);
  memset(temp, INIT_CHAR, (MTERIAL_NUM * STRING_BUFFER));
  
  while((place = cammna_search(*buf)) != NULL) {
	for(;i < (place - buf + 1); i++) {
	  temp[j] = buf;
	  buf++;
	}
	// 改行文字が含まれているかの確認
	if (strchr(temp, '\n') != NULL) {
	  // 改行文字を終端記号に置換する
	  temp[strlen(temp) - 1] = '\0';
	} else {
	  // 超えている場合は、切って最後に終端文字を代入する
	  temp[STRING_BUFFER - 1] = '\0';
	}
	j++;
  }

  line_mtrl.id = atoi(temp[0]);
  line_mtrl.model = temp[1];
  line_mtrl.model_name = temp[2];
  line_mtrl.control_id = temp[3];
  line_mtrl.alias = temp[4];
  line_mtrl.note = temp[5];
  line_mtrl.others = temp[6];
  
  return line_mtrl;
}

/**
 * 文字列から、カンマ（，）の位置を検索する。
 * @param 文字列を渡す。
 * @retval *int カンマがあった位置を返す。
 * @retval NULL カンマが見つからない場合に返す。
 */
int* cammna_search(char *str) {
  char *comma = ",";
  char *place;
  
  place = strstr(str, comma);
  //printf("'%s'の中に現れる'%s'という文字列は%d文字目にある.\n", str, comma, place - str + 1);
  if (place == NULL) {
	return NULL;
  } else {
	return place;
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
  scanf("%s", tmp_mtrl.ctrl_number);
  
  printf("識別名を入力:");
  scanf("%s", tmp_mtrl.diff_name);
  
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
  printf("管理番号:%s\n", tmp_mtrl.ctrl_number);
  printf("識別名:%s\n", tmp_mtrl.diff_name);
  printf("備考:%s\n", tmp_mtrl.note);
  printf("その他:%s\n", tmp_mtrl.others);
  printf("------------------------------\n");
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
