/**
 * @file
 * material.c のヘッダーファイル
 * @author Arakawa
 * @date last updated : 2009/10/18-02:17:05
 */

/* マクロ定義 */
#define MATERIAL_NUM 7 /**< material構造体の要素数 */

/**
 * @struct material
 * 機材管理情報情報
 */
struct material{
  int id; /**< ユニークなマテリアルID */
  char *model; /**< モデルコード */
  char *model_name; /**< モデルの名前 */
  char *control_id; /**< 管理番号 */
  char *alias; /**< モデルの別名 */
  char *note; /**< コメント */
  char *others; /**< その他 */
};

/* プロトタイプ宣言 */
int info_file_read(void);
int info_file_write_add(struct material);
void format_material(struct material);
struct material input_material();
int* gen_int();
char* gen_char();
void init_material(struct material*);
struct material line_buf_material(char line[LINE_BUFFER]);
