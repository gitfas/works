/**
 * @file
 * メイン処理ファイル
 * @author Arakawa
 * @date Last Change:2010/01/11 00:36:08.
 */
#include <stdio.h>
#include "common.h"
#include "gonzo.h"
#include "page.h"

/**
 * メイン処理
 * @return int 処理結果を返す。
 */
int main () {
  int while_flag = TRUE;
  init();
  
  while (while_flag == TRUE) {
    switch (status) {
    case PAGE_START :
      ptr = page_start;
      break;
    case PAGE_SHOW_ALL :
      ptr = page_show_all;
      break;
    case PAGE_LEND_RENEW :
      ptr = page_lend_renew;
      break;
    case PAGE_LEND_LOG :
      ptr = page_lend_log;
      break;
    case PAGE_EQUIPMENT_REGIST :
      ptr = page_equipment_regist;
      break;
    case PAGE_EQUIPMENT_DELETE :
      ptr = page_equipment_delete;
      break;
    case PAGE_EQUIPMENT_EDIT :
      ptr = page_equipment_edit;
      break;
    default :
      while_flag = FALSE;
      break;
    }
    (*ptr)();
  }
  return 0;
}

/**
 * 初期化
 */
static void init() {
  status = PAGE_START;
  ptr = NULL;
}
