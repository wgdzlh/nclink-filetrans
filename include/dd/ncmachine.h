//数据字典——数控机床

#ifndef _NCM_H_
#define _NCM_H_

#include "general.h"

//数控机床
#define NCM_MACHINE	NLK_G_MACHINE

//组件
#define NCM_NC		NLK_G_CONTROLLER
#define NCM_AXIS	NLK_G_AXIS
#define NCM_TOOL_MAGAZINE	"TOOL_MAGAZINE"
//刀具参数
//#define NCM_TOOL_PARAMETER	"TOOL_PARAMETER"
#define NCM_TOOL_PARAMETER	"TOOL"

//config
#define NCM_TYPE					NLK_G_TYPE
#define NCM_NAME					NLK_G_NAME
#define NCM_NUMBER					NLK_G_NUMBER
#define NCM_MANUFACTURER			NLK_G_MANUFACTURER
#define NCM_MODEL					NLK_G_MODEL

//dataItem
#define NCM_STATUS					"STATUS"			//机床状态
#define NCM_FEED_OVERRIDE			"FEED_OVERRIDE"		//进给倍率
#define NCM_SPDL_OVERRIDE			"SPDL_OVERRIDE"		//主轴倍率
#define NCM_FEED_SPEED				"FEED_SPEED"		//进给速度
#define NCM_SPDL_SPEED				"SPDL_SPEED"		//主轴速度
#define NCM_PART_COUNT				"PART_COUNT"		//加工计数

//机床类型
#define NCM_TYPE_LATHE				"lathe"				//车床
#define NCM_TYPE_MILLER				"milling_machine"	//铣床
#define NCM_TYPE_DRILL				"drill_machine"		//钻床
#define NCM_TYPE_GRINDER			"grinding_machine"	//磨床
#define NCM_TYPE_BORER				"boring_machine"	//镗床


#define NCM_AXIS_SCREW					NLK_G_SCREW
#define NCM_AXIS_MOTOR					NLK_G_MOTOR
#define NCM_AXIS_TYPE					NLK_G_TYPE
#define NCM_AXIS_NAME					NLK_G_NAME
#define NCM_AXIS_NUMBER					NLK_G_NUMBER
//轴类型
#define NCM_AXIS_TYPE_LINEAR		"linear"
#define NCM_AXIS_TYPE_ROTARY		"rotary"

//状态值
#define NCM_STATUS_RUNNING		NLK_G_STATUS_RUNNING	//运行
#define	NCM_STATUS_FREE			NLK_G_STATUS_FREE		//空闲
//#define NCM_STATUS_ERROR		NLK_G_STATUS_ERROR		//异常
#define NCM_STATUS_HOLDING		"holding"			//进给保持
//#define NCM_STATUS_HOMING		"homing"				//回零
//#define NCM_STATUS_ESTOP		"emergency_stop"		//急停
//#define NCM_STATUS_MOVING		"moving"				//轴运动

//坐标系属性
#define NCM_CRDS_X	NLK_G_CRDS_X
#define NCM_CRDS_Y	NLK_G_CRDS_Y
#define NCM_CRDS_Z	NLK_G_CRDS_Z
#define NCM_CRDS_A	"a"
#define NCM_CRDS_B	"b"
#define NCM_CRDS_C	"c"

//参数属性
#define NCM_PARAMS_VALUE			NLK_G_PARAMS_VALUE	//值
#define NCM_PARAMS_NAME				NLK_G_PARAMS_NAME	//名称
#define NCM_PARAMS_ACTION_TYPE		"action_type"		//生效方式
#define NCM_PARAMS_MAX_VALUE		"max_value"			//最大值
#define NCM_PARAMS_MIN_VALUE		"min_value"			//最小值
#define NCM_PARAMS_DEFAULT_VALUE	"default_value"		//缺省值

//刀参属性
#define NCM_TOOL_LENGTH				"length"			//长度
#define NCM_TOOL_RADIUS				"radius"			//半径
#define NCM_TOOL_L_ABRASION			"length_abrasion"	//长度磨损
#define NCM_TOOL_R_ABRASION			"radius_abrasion"	//半径磨损

//报警
#define NCM_ALARM_NO		"number"	//报警编号
#define NCM_ALARM_TXT		"text"		//报警内容

//事件
#define NCM_EVENT_NO		"number"	//事件码
#define NCM_EVENT_SRC		"source"	//事件源
#define NCM_EVENT_TXT		"text"		//事件内容


#endif