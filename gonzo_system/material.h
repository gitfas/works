/**
 * @file
 * material.c �̃w�b�_�[�t�@�C��
 * @author Arakawa
 * @date last updated : 2009/11/23-18:09:07
 */

/* define */
#define MATERIAL_FILE "abc.txt"		 /**< �@�ފǗ����t�@�C�� */

/* static */
static struct material *mtrl_ptr;	 /**< �ۊǃf�[�^ */

/**
 * @struct material
 * �@�ފǗ������
 */
struct material{
  int  id;				 /**< ���j�[�N�ȃ}�e���A��ID */
  char *model;			 /**< ���f���R�[�h */
  char *model_name;		 /**< ���f���̖��O */
  char *control_id;		 /**< �Ǘ��ԍ� */
  char *alias;			 /**< ���f���̕ʖ� */
  char *status;			 /**< ��� */
  char *place;			 /**< ���ݒn */
  char *blame;			 /**< �ӔC�� */
  char *date;			 /**< �ŏI�X�V���� */
};
#define MATERIAL_NUM 9	 /**< material�\���̗̂v�f�� */

/* �֐��v���g�^�C�v�錾 */
int material_file_read(void);
int material_file_write_add(struct material);
void format_material(struct material);
struct material input_material();
int* gen_int();
char* gen_char();
void init_material(struct material*);
void free_material(struct material*);
struct material line_buf_material(char*);
