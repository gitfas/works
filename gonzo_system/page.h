/**
 * @file
 * �y�[�W�P�ʏ����t�@�C��
 * @author Arakawa
 * @date last updated : 2009/11/23-02:11:01
 */

/* define */
#define MENU_TITLE1_NAME "���i�Ǘ��V�X�e��"	 /**< �y�[�W�^�C�g��1 */
#define MENU_LIST1_NAME1 "���i�ꗗ"			 /**< �y�[�W��1 */
#define MENU_LIST1_NAME2 "���i�ݏo�L�^�X�V"	 /**< �y�[�W��2 */
#define MENU_LIST1_NAME3 "�ݏo���O"			 /**< �y�[�W��3 */
#define MENU_LIST1_NAME4 "���i�o�^"			 /**< �y�[�W��4 */
#define MENU_LIST1_NAME5 "���i�폜"			 /**< �y�[�W��5 */
#define MENU_LIST1_NAME6 "���i�ҏW"			 /**< �y�[�W��6 */

/**
 * @brief �V�X�e���y�[�W��enum
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

/* �֐��v���g�^�C�v */
void page_start();
void page_show_all();
void page_lend_renew();
void page_lend_log();
void page_equipment_regist();
void page_equipment_delete();
void page_equipment_edit();
