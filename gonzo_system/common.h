/**
 * @file
 * common.c のヘッダーファイル
 * 外部に対して全て公開する。
 * @author Arakawa
 * @date last updated : 2009/11/29-02:48:44
 */
/* コンパイルスイッチ */
#define DEBUG_PRINT 0		 /**< デバッグ用コンパイルスイッチ */

/* マクロ定義 */
#define TRUE 1				 /**< 真 */
#define FALSE 0				 /**< 偽 */
#define YES 0x0059			 /**< Y */
#define yes 0x0079			 /**< y */
#define NO 0x004e			 /**< N */
#define no 0x006e			 /**< n */
#define STRING_BUFFER 1024	 /**< 1要素の文字列の最大バッファ */
#define LINE_BUFFER 1024	 /**< 1行の最大読み取りバッファ */
#define INIT_INT -1			 /**< INTを初期化する際の値 */
#define PRINT_FORMAT_LEN 40	 /**< タイトル、メニューの最大バイト数 */

/* 共通関数 */
int cammna_search(char*, int);
int count_UTF8(const unsigned char *string);
int query_ok_ng();
int error_malloc(char *string);
void format_print_title(char string[PRINT_FORMAT_LEN]);
void format_print_menu(char string[][PRINT_FORMAT_LEN], int cnt);
void format_print_line();
void common_int_input(int* num);
void common_string_input(char* string);
