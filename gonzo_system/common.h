/**
 * @file
 * common.c �̃w�b�_�[�t�@�C��
 * �O���ɑ΂��đS�Č��J����B
 * @author Arakawa
 * @date last updated : 2009/11/29-02:48:44
 */
/* �R���p�C���X�C�b�` */
#define DEBUG_PRINT 0		 /**< �f�o�b�O�p�R���p�C���X�C�b�` */

/* �}�N����` */
#define TRUE 1				 /**< �^ */
#define FALSE 0				 /**< �U */
#define YES 0x0059			 /**< Y */
#define yes 0x0079			 /**< y */
#define NO 0x004e			 /**< N */
#define no 0x006e			 /**< n */
#define STRING_BUFFER 1024	 /**< 1�v�f�̕�����̍ő�o�b�t�@ */
#define LINE_BUFFER 1024	 /**< 1�s�̍ő�ǂݎ��o�b�t�@ */
#define INIT_INT -1			 /**< INT������������ۂ̒l */
#define PRINT_FORMAT_LEN 40	 /**< �^�C�g���A���j���[�̍ő�o�C�g�� */

/* ���ʊ֐� */
int cammna_search(char*, int);
int count_UTF8(const unsigned char *string);
int count_Shift_JIS(const unsigned char *string);
int query_ok_ng();
int error_malloc(char *string);
void format_print_title(char string[PRINT_FORMAT_LEN]);
void format_print_menu(char string[][PRINT_FORMAT_LEN], int cnt);
void format_print_line();
void common_int_input(int* num);
void common_string_input(char* string);
