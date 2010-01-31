/**
 * @file
 * �y�[�W�P�ʏ����t�@�C��
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
 * �X�^�[�g���
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
	}; /**< ���j���[���X�g�e�[�u�� */

	/* ���j���[�𐮌`�o�� */
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
		printf("[%s] ��I��\n", &page_name[num - 1][0]);
	} else {
		printf("1-6�ȊO�̔ԍ������͂���Ă��܂�\n");
	}
}

/**
 * �@�ވꗗ
 */
void page_show_all() {
	// ��`�A������
	int cnt;

	printf("�@�ވꗗ��\�����܂�\n");
	printf("|���f��   | �^��     | �Ǘ��ԍ� | ���ʖ� | ���l     | ���̑�   |\n");
	printf("----------------------------------------------------------------\n");

	// �Ԃ�l�ɍ\���̂̒�����Ԃ�
	cnt = material_file_read();
	printf("cnt : %d\n", cnt);
	cnt = EXIT_FAILURE;

	printf("%d", EXIT_FAILURE);
	// �������̊m�ۂɎ��s�����ꍇ
	if (cnt == EXIT_FAILURE) {
		printf("�����I��\n");
		status = PAGE_START;
		return;
	}

	printf("\n");
	free(mtrl_ptr);
	status = PAGE_START;
}

/**
 * ���i�ݏo�L�^�X�V
 */
void page_lend_renew() {
	printf("���i�̏�Ԃ��X�V���܂�\n");
	printf("\n�����Ŕ��i�ꗗ�\��\n\n");
	printf("�ǂ̋@�ނ̋L�^���X�V���܂����H\n");

	int input;
	scanf("ID:%d", &input);
	printf("id %d �̋@�ނ̋L�^���X�V���܂�\n", input);

	status = PAGE_START;
}

/**
 * �ݏo���O
 */
void page_lend_log() {
	printf("�ݏo���O");
	status = PAGE_START;
}

/**
 * ���i�o�^
 */
void page_equipment_regist() {
	// ��`�A������
	struct material regist;

	printf("���i�o�^\n");
	// ���͎�t
	regist = input_material();
	// ���`�\��
	format_material(regist);
	// yes/no
	if (query_ok_ng() == TRUE) {
		// �t�@�C���֏�������
		printf("file write");
	}

	// malloc���Ă��镔���̊J��
	free_material(&regist);
	status = PAGE_START;
}

/**
 * ���i�폜
 */
void page_equipment_delete() {
	printf("���i�폜");
	status = PAGE_START;
}

/**
 * ���i�ҏW
 */
void page_equipment_edit() {
	printf("���i�ҏW");
	status = PAGE_START;
}
