/**
 * @file
 * material �\���̗p�֐��t�@�C��
 * @author Arakawa
 * @date last updated : 2010/01/31-00:17:48
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common.h"
#include "material.h"

/**
 * MATERIAL_FILE ��ǂݍ��ݓǂݍ��񂾍s����Ԃ��B
 * @retval int ���������ꍇ�AEXIT_SUCCESS��Ԃ��B
 * @retval EXIT_FAILURE ���s�����ꍇ�AEXIT_FAILURE��Ԃ��B
 */
int material_file_read() {
	// ��`�A������
	FILE *fp;
	char buf[LINE_BUFFER];
	int cnt = 0;

	if (mtrl_ptr != NULL) {
		free(mtrl_ptr);
	}
	mtrl_ptr = (struct material *) malloc(sizeof(struct material));

	// �t�@�C���̃I�[�v��
	if ((fp = fopen(MATERIAL_FILE, "r")) == NULL) {
		printf("[%s]�t�@�C�����J���܂���B\n", MATERIAL_FILE);
		return EXIT_FAILURE;
	}

	// �t�@�C����ǂݍ���
	while (fgets(buf, LINE_BUFFER, fp) != NULL) {
		printf("%s", buf);
		line_buf_material((char*)buf);

		memset(buf, '\0', sizeof(LINE_BUFFER));
		cnt++;
	}
	printf("cnt : %d\n", 1);
	// �t�@�C�������
	fclose(fp);

	return EXIT_SUCCESS;
}

/**
 * material ���t�@�C���֒ǉ��������݂���B
 * @retval EXIT_SUCCESS �ǉ��������݂ɐ�����Ԃ��B
 * @retval EXIT_FAILURE �ǉ��������݂Ɏ��s��Ԃ��B
 */
int material_file_write_add(struct material tmp_mtrl) {
	// ��`�A������
	FILE *fp;
	int i;
	char *joint_str[] = {
		(char *)tmp_mtrl.id,
		tmp_mtrl.model,
		tmp_mtrl.model_name,
		tmp_mtrl.control_id,
		tmp_mtrl.alias,
		tmp_mtrl.status,
		tmp_mtrl.place,
		tmp_mtrl.blame,
		tmp_mtrl.date
	};
	char jointed[sizeof(struct material)];

	if ((fp = fopen(MATERIAL_FILE, "a")) == NULL) {
		printf("[%s]�t�@�C�����J���܂���B\n", MATERIAL_FILE);
		return EXIT_FAILURE;
	}

	for (i = 0; i < 7; i++) {
		strcat(jointed, joint_str[i]);
	}
	fputs(jointed, fp);
	fclose(fp);

	return EXIT_SUCCESS;
}

/**
 * ���͂�v������ material �Ɋi�[����B
 * @return struct material ���͂��\���̂ɑ�����ĕԂ��B
 */
struct material input_material(void) {
	// ��`�A������
	struct material tmp_mtrl;
	// �|�C���^�ɑ΂��ė̈揉�����A���s
	init_material(&tmp_mtrl);

	// ID�����肪�R��Ă�
	tmp_mtrl.id = 10;

	printf("���f�������:");
	common_string_input(tmp_mtrl.model);

	printf("�^�������:");
	common_string_input(tmp_mtrl.model_name);

	printf("�Ǘ��ԍ������:");
	common_string_input(tmp_mtrl.control_id);

	printf("���ʖ������:");
	common_string_input(tmp_mtrl.alias);

	printf("��Ԃ����:");
	common_string_input(tmp_mtrl.status);

	printf("���ݒn�����:");
	common_string_input(tmp_mtrl.place);

	printf("�ӔC�҂����:");
	common_string_input(tmp_mtrl.blame);

	printf("�ŏI�X�V���������:");
	common_string_input(tmp_mtrl.date);

	return tmp_mtrl;
}

/**
 * material �𐮌`���ĕ\������
 * @param material�\���̂�n���B
 */
void format_material(struct material tmp_mtrl) {
	printf("------------------------------\n");
	printf("id:%d\n", tmp_mtrl.id);
	printf("���f��:%s\n", tmp_mtrl.model);
	printf("�^��:%s\n", tmp_mtrl.model_name);
	printf("�Ǘ��ԍ�:%s\n", tmp_mtrl.control_id);
	printf("���ʖ�:%s\n", tmp_mtrl.alias);
	printf("���:%s\n", tmp_mtrl.status);
	printf("���ݒn:%s\n", tmp_mtrl.place);
	printf("�ӔC��:%s\n", tmp_mtrl.blame);
	printf("�ŏI�X�V����:%s\n", tmp_mtrl.date);
	printf("------------------------------\n");
}

/**
 * material������������B
 * @param material��n���B
 */
void init_material(struct material *mtrl) {
	mtrl -> id			 = 0;
	mtrl -> model		 = (char*)malloc(STRING_BUFFER);
	mtrl -> model_name	 = (char*)malloc(STRING_BUFFER);
	mtrl -> control_id	 = (char*)malloc(STRING_BUFFER);
	mtrl -> alias		 = (char*)malloc(STRING_BUFFER);
	mtrl -> status		 = (char*)malloc(STRING_BUFFER);
	mtrl -> place		 = (char*)malloc(STRING_BUFFER);
	mtrl -> blame		 = (char*)malloc(STRING_BUFFER);
	mtrl -> date		 = (char*)malloc(STRING_BUFFER);
}

/**
 * malloc����material������������B
 * @param material��n��
 */
void free_material(struct material *mtrl) {
	free(mtrl -> model);
	free(mtrl -> model_name);
	free(mtrl -> control_id);
	free(mtrl -> alias);
	free(mtrl -> status);
	free(mtrl -> place);
	free(mtrl -> blame);
	free(mtrl -> date);
}

/**
 * MATERIAL_FILE��1�s���J���}��؂�ŕ�������material�\���̂𐶐�����B
 * @param char[LINE_BUFFER] 1�s
 * @return struct material 1�s�f�[�^���琶������material�\����
 */
struct material line_buf_material(char buf[LINE_BUFFER]) {
	int place = 0;
	int place_old = 0;
	int cnt = 0;
	int i;
	char temp_buf[LINE_BUFFER];
	struct material mtrl_buf;

	while((place != -1) && (cnt < MATERIAL_NUM)) {
		place_old = place;
		place = cammna_search(buf, place);
#if DEBUG_PRINT
		printf("place:%d -> %d\n", place_old, place);
#endif
		if (place == -1) {
			printf("csv�f�[�^������Ă��Ȃ��\��������܂��B\n");
			printf("%d��ڂ̃f�[�^���������Ă��������B\n", (cnt + 1));
			break;
		} else {
			memset(temp_buf, '\0', sizeof(temp_buf));
			memcpy(temp_buf, &buf[place_old], (place - place_old));

			for (i = 0; i < MATERIAL_NUM; i++) {
				switch (cnt) {
					case 0: mtrl_buf.id			= atoi(temp_buf);
							break;
					case 1: mtrl_buf.model		= temp_buf;
							break;
					case 2: mtrl_buf.model_name	= temp_buf;
							break;
					case 3: mtrl_buf.control_id	= temp_buf;
							break;
					case 4: mtrl_buf.alias		= temp_buf;
							break;
					case 5: mtrl_buf.status		= temp_buf;
							break;
					case 6: mtrl_buf.place		= temp_buf;
							break;
					case 7: mtrl_buf.blame		= temp_buf;
							break;
					case 8: mtrl_buf.date		= temp_buf;
							break;
					default :
							break;
				}
			}
			if (cnt < MATERIAL_NUM){
				cnt++;
			}else{
				printf("MATERIAL_NUM�𒴂���J���}������܂���");
				break;
			}
		}
	}
	return mtrl_buf;
}
