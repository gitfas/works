#define INFO_FILE "abc.txt"
#define MENU_LIST_NAME1 "備品一覧"
#define MENU_LIST_NAME2 "備品貸出記録更新"
#define MENU_LIST_NAME3 "貸出ログ"
#define MENU_LIST_NAME4 "備品登録"
#define MENU_LIST_NAME5 "備品削除"
#define MENU_LIST_NAME6 "備品編集"
#define TRUE 1
#define FALSE 0
#define YES 0x0059 // Y
#define yes 0x0079 // y
#define NO 0x004e // N
#define no 0x006e // n
#define EXIT_FAILURE -1
#define EXIT_SUCCESS 1

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
struct material {
  int id;
  char model[255];
  char model_name[255];
  char ctrl_number[255];
  char diff_name[255];
  char note[255];
  char others[255];
};

struct material *mtrl_ptr;
void (*ptr)();

/*
 * 共通関数
 */
int info_file_read(void);
int cammna_search(char*);
int count_UTF8(const unsigned char *string);
struct material input_material();
void format_material(struct material);
int query_ok_ng();
int info_file_write_add(struct material);

