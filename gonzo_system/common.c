/**
 * @file
 * ���ʊ֐��t�@�C��
 * @author Arakawa
 * @date last updated : 2010/01/30-23:59:57
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "common.h"


/**
 * �^�C�g��������𐮌`�o�͂���(�e�L�X�g)
 * @param char* string �^�C�g��������
 */
void format_print_title(char string[PRINT_FORMAT_LEN]) {
	int i;

	printf("  +----- %s ", string);
	for(i = 0; i < (PRINT_FORMAT_LEN - strlen(string)) + 2; i++) {
		printf("-");
	}
	printf("+\n");
}

/**
 * ���j���[������𐮌`�o�͂���(�e�L�X�g)
 * @param char string[][PRINT_FORMAT_LEN] ���j���[������
 * @param int cnt ���j���[�̐�
 */
void format_print_menu(char string[][PRINT_FORMAT_LEN], int cnt) {
	int i,j;
#ifdef DEBUG_PRINT
	printf("���j���[�̐�:%d\n", cnt);
#endif

	for(i = 0; i < cnt; i++) {
		printf("  | %d. %s ", (i + 1), string[i]);
		for(j = 0; j < (PRINT_FORMAT_LEN - (strlen(string[i])/3*2) - 4); j++) {
			printf(" ");
		}
		printf("|\n");
	}
}

/**
 * ���`�o�͂̃��C�����o�͂���(�e�L�X�g)
 */
void format_print_line() {
	int i;

	printf("  +");
	for(i = 0; i < PRINT_FORMAT_LEN + 1; i++) {
		printf("-");
	}
	printf("+\n");
}

/**
 * malloc�ŃG���[���o���ꍇ�̕�������o�͂���B
 * @param �֐�����n���B
 * @return int EXIT_FAILURE��Ԃ��B
 */
int error_malloc(char *string) {
	printf("%s���Ń������m�ۂɎ��s���܂����B\n", string);
	return EXIT_FAILURE;
}

/**
 * �����񂩂�A�J���}�i�C�j�̈ʒu����������B
 * @param �������n���B
 * @retval int �J���}���������ʒu��Ԃ��B
 * @retval 0 �J���}��������Ȃ��ꍇ�ɕԂ��B
 */
int cammna_search(char *str, int now) {
	char *comma = ",";
	char *place;

	place = strstr((str + now), comma);
#ifdef DEBUG_PRINT
	printf("'%s'�̒��Ɍ����'%s'�Ƃ����������%d�����ڂɂ���.\n", str, comma, place - str + 1);
#endif
	if (place == NULL) {
		return -1;
	} else {
		return (int)(place - str + 1);
	}
}

/**
 * UTF-8�̕�����̕��������J�E���g����B
 * @param UTF-8�̕������n���B
 * @return int �J�E���g������������Ԃ��B
 */
int count_UTF8(const unsigned char *string) {
	int len = 0;

	while(*string) {
		if (*string < 0x1f || *string == 0x7f) {
			//����R�[�h
		} else if (*string <= 0x7f) {
			++len; // 1�o�C�g����
		} else if (*string <= 0xbf) {
			// �����̑���
		} else if (*string <= 0xdf) {
			++len; // 2�o�C�g����
		} else if (*string <= 0xef) {
			++len; // 3�o�C�g����
		} else if (*string <= 0xf7) {
			++len; // 4�o�C�g����
		} else if (*string <= 0xfb) {
			++len; // 5�o�C�g����
		} else if (*string <= 0xfd) {
			++len; // 6�o�C�g����
		} else {
			// �g���Ă��Ȃ�
		}
		string++;
	}

	return len;
}

/**
 * Shift-JIS�̕�����̕��������J�E���g����B
 * @param Shift-JIS�̕������n���B
 * @return int �J�E���g������������Ԃ��B
 */
int count_Shift_JIS(const unsigned char *string)
{
	int len = 0;

	while (*string) {
		if (*string < 0x1f || *string == 0x7f) {
			// ���䕶��
		} else if ((0x81 <= *string && *string <= 0x9F) || (0xE0 <= *string && *string <= 0xFC)) {
			// 2�o�C�g����
			++string;
			if ((0x40 <= *string && *string <= 0x7E) || (0x80 <= *string && *string <= 0xFC)) {
				++len;
			} else {
				break; // �s���ȕ���
			}
		} else {
			// 1�o�C�g����
			if(0x80 < *string)
			// ���p�J�i
			++len;
		}
		++string;
	}

	return len;
}

/**
 * yes/no ����͂����ATrue/False��Ԃ��B
 * @retval TRUE "Y","y"����͂����ꍇ�ɕԂ��B
 * @retval FALSE "N","n"����͂����ꍇ�ɕԂ��B
 */
int query_ok_ng() {
	// ��`�A������
	int		c;
	int		flag;
	int		result;

	printf("�ȏ�̓o�^���e�ł�낵���ł����BY/N:");
	while((c = getchar()) != EOF) {
		switch(c) {
			case YES:
			case yes:
				flag = TRUE;
				result = TRUE;
				break;
			case NO:
			case no:
				flag = TRUE;
				result = TRUE;
				break;
			default:
				printf("Y/N ����͂��Ă��������B\n");
				break;
		}
		if (flag == TRUE) {
			break;
		}
	}
	return result;
}

/**
 * �����̓��͎�t���s���B
 * @param int* ���͂��i�[����|�C���^
 */
void common_int_input(int* num) {
	/* ��`�A������ */
	char	input[256];
	int		flag;
	flag = FALSE;

	printf("���͎�t[����]�F");
	fgets(input, sizeof(input), stdin);
	fflush(stdin);

	*num = atoi(input);
}

/**
 * ������̓��͎�t���s���B
 * 255�o�C�g�܂œ��͉\�B
 * @param char* ���͂��i�[����|�C���^
 */
void common_string_input(char* string) {
	/* ��`�A������ */
	/* ���������A���͂��󂯎������̃G���[�������܂�A�B*/
	char	input[STRING_BUFFER];
	int		flag;
	int		cnt;
	flag = FALSE;

	printf("���͎�t[������]�F");
	fgets(input, sizeof(input), stdin);
	fflush(stdin);

	if (input[256 - 2] != '\0') {
		cnt = 256 - 2;
		while (1) {
			if (input[cnt] <= 0x7f) {
				break; // 1�o�C�g����,����R�[�h
			} else if (input[cnt] <= 0xbf) {
				input[cnt--] = '\0';
			} else if (input[cnt] <= 0xfd) {
				input[cnt--] = '\0';
				break; // 2-6�o�C�g����
			}
		}
	}
	strncpy(string, input, 256);
}
