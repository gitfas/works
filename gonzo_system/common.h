/**
 * @file
 * common.c のヘッダーファイル
 * @author Arakawa
 * @date last updated : 2009/10/18-02:55:12
 */
#define INFO_FILE "abc.txt" /**< 機材管理情報ファイル */
#define TRUE 1 /**< 真 */
#define FALSE 0 /**< 偽 */
#define YES 0x0059 /**< Y */
#define yes 0x0079 /**< y */
#define NO 0x004e /**< N */
#define no 0x006e /**< n */
#define STRING_BUFFER 1024 /**< 1要素の文字列の最大バッファ */
#define LINE_BUFFER 1024 /**< 1行の最大読み取りバッファ */
#define MENU_LIST_NAME1 "備品一覧"
#define MENU_LIST_NAME2 "備品貸出記録更新"
#define MENU_LIST_NAME3 "貸出ログ"
#define MENU_LIST_NAME4 "備品登録"
#define MENU_LIST_NAME5 "備品削除"
#define MENU_LIST_NAME6 "備品編集"
#define INIT_INT -1 /**< INTの初期値 */
#define NULL_CHAR "\0" /**< 終端文字 */

/**
 * @brief システムのページ
 */
enum GONZO_STATUS {
  PAGE_START = 0,
  PAGE_SHOW_ALL,
  PAGE_LEND_RENEW,
  PAGE_LEND_LOG,
  PAGE_EQUIPMENT_REGIST,
  PAGE_EQUIPMENT_DELETE,
  PAGE_EQUIPMENT_EDIT,
} status;

//グローバル変数
/*
struct material {
  int id;
  char model[255];
  char model_name[255];
  char ctrl_number[255];
  char diff_name[255];
  char note[255];
  char others[255];
};
*/

/* 共通関数 */
int cammna_search(char*);
int count_UTF8(const unsigned char *string);
int query_ok_ng();
int error_malloc(char *string);
