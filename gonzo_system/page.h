/**
 * @file
 * ページ単位処理ファイル
 * @author Arakawa
 * @date last updated : 2009/11/23-02:11:01
 */

/* define */
#define MENU_TITLE1_NAME "備品管理システム"	 /**< ページタイトル1 */
#define MENU_LIST1_NAME1 "備品一覧"			 /**< ページ名1 */
#define MENU_LIST1_NAME2 "備品貸出記録更新"	 /**< ページ名2 */
#define MENU_LIST1_NAME3 "貸出ログ"			 /**< ページ名3 */
#define MENU_LIST1_NAME4 "備品登録"			 /**< ページ名4 */
#define MENU_LIST1_NAME5 "備品削除"			 /**< ページ名5 */
#define MENU_LIST1_NAME6 "備品編集"			 /**< ページ名6 */

/**
 * @brief システムページのenum
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

/* 関数プロトタイプ */
void page_start();
void page_show_all();
void page_lend_renew();
void page_lend_log();
void page_equipment_regist();
void page_equipment_delete();
void page_equipment_edit();
