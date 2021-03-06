/**
 * @file
 * ページ単位処理ファイル
 * @author Arakawa
 * @date last updated : 2010/01/31-00:27:28
 */
#include <stdio.h>
#include <stdlib.h>
#include "common.h"
#include "material.h"
#include "renewlog.h"
#include "page.h"

/**
 * スタート画面
 */
void page_start() {
	int num;
	char page_name[][PRINT_FORMAT_LEN] = {
		MENU_LIST1_NAME1,
		MENU_LIST1_NAME2,
		MENU_LIST1_NAME3,
		MENU_LIST1_NAME4,
		MENU_LIST1_NAME5,
		MENU_LIST1_NAME6
	}; /**< メニューリストテーブル */

	/* メニューを整形出力 */
	format_print_title(MENU_TITLE1_NAME);
	format_print_menu(page_name, (sizeof(page_name)/sizeof(page_name[0])));
	format_print_line();

	common_int_input(&num);

	switch (num) {
		case 1:
			status = PAGE_SHOW_ALL;
			break;
		case 2:
			status = PAGE_LEND_RENEW;
			break;
		case 3:
			status = PAGE_LEND_LOG;
			break;
		case 4:
			status = PAGE_EQUIPMENT_REGIST;
			break;
		case 5:
			status = PAGE_EQUIPMENT_DELETE;
			break;
		case 6:
			status = PAGE_EQUIPMENT_EDIT;
			break;
		default :
			break;
	}

	if ((num > 0) && (num <= (sizeof(page_name)/sizeof(page_name[0])))) {
		printf("[%s] を選択\n", &page_name[num - 1][0]);
	} else {
		printf("1-6以外の番号が入力されています\n");
	}
}

/**
 * 機材一覧
 */
void page_show_all() {
	// 定義、初期化
	int cnt;

	printf("機材一覧を表示します\n");
	printf("|モデル   | 型名     | 管理番号 | 識別名 | 備考     | その他   |\n");
	printf("----------------------------------------------------------------\n");

	// 返り値に構造体の長さを返す
	cnt = material_file_read();
	printf("cnt : %d\n", cnt);
	cnt = EXIT_FAILURE;

	printf("%d", EXIT_FAILURE);
	// メモリの確保に失敗した場合
	if (cnt == EXIT_FAILURE) {
		printf("強制終了\n");
		status = PAGE_START;
		return;
	}

	printf("\n");
	free(mtrl_ptr);
	status = PAGE_START;
}

/**
 * 備品貸出記録更新
 */
void page_lend_renew() {
	printf("備品の状態を更新します\n");
	printf("\nここで備品一覧表示\n\n");
	printf("どの機材の記録を更新しますか？\n");

	int input;
	scanf("ID:%d", &input);
	printf("id %d の機材の記録を更新します\n", input);

	status = PAGE_START;
}

/**
 * 貸出ログ
 */
void page_lend_log() {
	printf("貸出ログ");
	status = PAGE_START;
}

/**
 * 備品登録
 */
void page_equipment_regist() {
	// 定義、初期化
	struct material regist;

	printf("備品登録\n");
	// 入力受付
	regist = input_material();
	// 整形表示
	format_material(regist);
	// yes/no
	if (query_ok_ng() == TRUE) {
		// ファイルへ書き込み
		printf("file write");
	}

	// mallocしている部分の開放
	free_material(&regist);
	status = PAGE_START;
}

/**
 * 備品削除
 */
void page_equipment_delete() {
	printf("備品削除");
	status = PAGE_START;
}

/**
 * 備品編集
 */
void page_equipment_edit() {
	printf("備品編集");
	status = PAGE_START;
}
