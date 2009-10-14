/**
 * @file
 * common.c のヘッダーファイル
 * @author Arakawa
 * @date last updated : 2009/10/15-01:40:35
 */
#define INFO_FILE "abc.txt" /**< 機材管理情報ファイル */
#define TRUE 1 /**< 真 */
#define FALSE 0 /**< 偽 */
#define YES 0x0059 /**< Y */
#define yes 0x0079 /**< y */
#define NO 0x004e /**< N */
#define no 0x006e /**< n */
#define EXIT_FAILURE -1 /**< returnで成否を返す際の失敗値 */
#define EXIT_SUCCESS 1 /**< returndeで成否を返す際の成功値 */
#define STRING_BUFFER 1024 /**< 1要素の文字列の最大バッファ */
#define LINE_BUFFER 1024 /**< 1行の最大読み取りバッファ */
#define MENU_LIST_NAME1 "備品一覧"
#define MENU_LIST_NAME2 "備品貸出記録更新"
#define MENU_LIST_NAME3 "貸出ログ"
#define MENU_LIST_NAME4 "備品登録"
#define MENU_LIST_NAME5 "備品削除"
#define MENU_LIST_NAME6 "備品編集"
#define INIT_INT -1 /**< INTの初期値 */
#define INIT_CHAR "\0" /**< CHARの初期値 */

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

/**
 * @struct material
 * 機材管理情報情報
 */
struct material{
  int *id; /**< ユニークなマテリアルID */
  char *model; /**< モデルコード */
  char *model_name; /**< モデルの名前 */
  char *control_id; /**< 管理番号 */
  char *alias; /**< モデルの別名 */
  char *note; /**< コメント */
  char *others; /**< その他 */
};
#define MATERIAL_NUM 7 /**< material構造体の要素数 */

struct material *mtrl_ptr;
void (*ptr)();

/* 共通関数 */
int cammna_search(char*);
int count_UTF8(const unsigned char *string);
int query_ok_ng();
int error_malloc(char *string);

/* material用関数 */
int info_file_read(void);
int info_file_write_add(struct material);
void format_material(struct material);
struct material input_material();
int* gen_int();
char* gen_char();
void init_material(struct material*);

