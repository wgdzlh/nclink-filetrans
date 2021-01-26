//�����ֵ䡪�����ػ���

#ifndef _NCM_H_
#define _NCM_H_

#include "general.h"

//���ػ���
#define NCM_MACHINE	NLK_G_MACHINE

//���
#define NCM_NC		NLK_G_CONTROLLER
#define NCM_AXIS	NLK_G_AXIS
#define NCM_TOOL_MAGAZINE	"TOOL_MAGAZINE"
//���߲���
//#define NCM_TOOL_PARAMETER	"TOOL_PARAMETER"
#define NCM_TOOL_PARAMETER	"TOOL"

//config
#define NCM_TYPE					NLK_G_TYPE
#define NCM_NAME					NLK_G_NAME
#define NCM_NUMBER					NLK_G_NUMBER
#define NCM_MANUFACTURER			NLK_G_MANUFACTURER
#define NCM_MODEL					NLK_G_MODEL

//dataItem
#define NCM_STATUS					"STATUS"			//����״̬
#define NCM_FEED_OVERRIDE			"FEED_OVERRIDE"		//��������
#define NCM_SPDL_OVERRIDE			"SPDL_OVERRIDE"		//���ᱶ��
#define NCM_FEED_SPEED				"FEED_SPEED"		//�����ٶ�
#define NCM_SPDL_SPEED				"SPDL_SPEED"		//�����ٶ�
#define NCM_PART_COUNT				"PART_COUNT"		//�ӹ�����

//��������
#define NCM_TYPE_LATHE				"lathe"				//����
#define NCM_TYPE_MILLER				"milling_machine"	//ϳ��
#define NCM_TYPE_DRILL				"drill_machine"		//�괲
#define NCM_TYPE_GRINDER			"grinding_machine"	//ĥ��
#define NCM_TYPE_BORER				"boring_machine"	//�۴�


#define NCM_AXIS_SCREW					NLK_G_SCREW
#define NCM_AXIS_MOTOR					NLK_G_MOTOR
#define NCM_AXIS_TYPE					NLK_G_TYPE
#define NCM_AXIS_NAME					NLK_G_NAME
#define NCM_AXIS_NUMBER					NLK_G_NUMBER
//������
#define NCM_AXIS_TYPE_LINEAR		"linear"
#define NCM_AXIS_TYPE_ROTARY		"rotary"

//״ֵ̬
#define NCM_STATUS_RUNNING		NLK_G_STATUS_RUNNING	//����
#define	NCM_STATUS_FREE			NLK_G_STATUS_FREE		//����
//#define NCM_STATUS_ERROR		NLK_G_STATUS_ERROR		//�쳣
#define NCM_STATUS_HOLDING		"holding"			//��������
//#define NCM_STATUS_HOMING		"homing"				//����
//#define NCM_STATUS_ESTOP		"emergency_stop"		//��ͣ
//#define NCM_STATUS_MOVING		"moving"				//���˶�

//����ϵ����
#define NCM_CRDS_X	NLK_G_CRDS_X
#define NCM_CRDS_Y	NLK_G_CRDS_Y
#define NCM_CRDS_Z	NLK_G_CRDS_Z
#define NCM_CRDS_A	"a"
#define NCM_CRDS_B	"b"
#define NCM_CRDS_C	"c"

//��������
#define NCM_PARAMS_VALUE			NLK_G_PARAMS_VALUE	//ֵ
#define NCM_PARAMS_NAME				NLK_G_PARAMS_NAME	//����
#define NCM_PARAMS_ACTION_TYPE		"action_type"		//��Ч��ʽ
#define NCM_PARAMS_MAX_VALUE		"max_value"			//���ֵ
#define NCM_PARAMS_MIN_VALUE		"min_value"			//��Сֵ
#define NCM_PARAMS_DEFAULT_VALUE	"default_value"		//ȱʡֵ

//��������
#define NCM_TOOL_LENGTH				"length"			//����
#define NCM_TOOL_RADIUS				"radius"			//�뾶
#define NCM_TOOL_L_ABRASION			"length_abrasion"	//����ĥ��
#define NCM_TOOL_R_ABRASION			"radius_abrasion"	//�뾶ĥ��

//����
#define NCM_ALARM_NO		"number"	//�������
#define NCM_ALARM_TXT		"text"		//��������

//�¼�
#define NCM_EVENT_NO		"number"	//�¼���
#define NCM_EVENT_SRC		"source"	//�¼�Դ
#define NCM_EVENT_TXT		"text"		//�¼�����


#endif