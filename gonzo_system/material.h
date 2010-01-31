/**
 * @file
 * material.c のヘッダーファイル
 * @author Arakawa
 * @date last updated : 2009/11/23-18:09:07
 */

/* define */
#define MATERIAL_FILE "abc.txt"		 /**< 機材管理情報ファイル */

/* static */
static struct material *mtrl_ptr;	 /**< 保管データ */

/**
 * @struct material
 * 機材管理情報情報
 */
struct material{
  int  id;				 /**< ユニークなマテリアルID */
  char *model;			 /**< モデルコード */
  char *model_name;		 /**< モデルの名前 */
  char *control_id;		 /**< 管理番号 */
  char *alias;			 /**< モデルの別名 */
  char *status;			 /**< 状態 */
  char *place;			 /**< 現在地 */
  char *blame;			 /**< 責任者 */
  char *date;			 /**< 最終更新日時 */
};
#define MATERIAL_NUM 9	 /**< material構造体の要素数 */

/* 関数プロトタイプ宣言 */
int material_file_read(void);
int material_file_write_add(struct material);
void format_material(struct material);
struct material input_material();
int* gen_int();
char* gen_char();
void init_material(struct material*);
void free_material(struct material*);
struct material line_buf_material(char*);
