#pragma once
#include <QtCore>

#ifndef DEF_LP_PLC_CONFIG_BASE_H_2023J
#define DEF_LP_PLC_CONFIG_BASE_H_2023J
//////////////////////////////////////////////////////////////////////////
namespace  PLCDATA {
	const QString CFG_PATH = "./lpIPUConfig/lpPLCConfig.json";

	// PLC组包: head + Len1 + head1/2 + addr + Len2 + data
	//   "500000FF03FF00"+ "001C" + "001014010000D*" + "012500" + "0001" + "0001"; // 示例为发送开始检测信号
	const QString head = "500000FF03FF00";
	const QString head_send = "001014010000D*";
	const QString head_read = "001004010000D*";
	const QString len1_read = "0018";
	// recv : head + len + "0000" + data
	const QString recv_head = "D00000FF03FF00";

	// cmd
	const QString C_HEART = "send_heartbeat";
	const QString C_STATIS = "read_statis";
	const QString C_STATUS = "read_status";
	const QString C_START = "send_start";
};

// read到的数据解析方法
enum class emDecodeType {
	D_NULL = 0,			// 不做解析,发送原始
	D_KEY,				// 使用key进行解析，通常指 read_statis
	D_REG,				// 使用reg进行解析，通常指 read_status 操作
	D_DIY,				// 使用专用的解析文件进行解析 注:找不到解析文件时，发送原始
};
enum class emDataType {
	PLC_INT=0,	// 0 int, num=1
	PLC_STR,    // 1 String
	PLC_TIME,   // 2 时间 num=7 分别代表: 年 月 日 时 分 秒 毫秒
	PLC_SID,    // 3 sid  其实就是多个int组成,每个int占1字
	PLC_SOURCE,	// 4 PLC原始数据,String形式，如"00020001"
};

// PLC运行状态寄存器信息值
typedef struct tagPLCRegCell{
	int ok_val{ 0 };
	int ng_val{ 1 }; 
	QString ok_txt;
	QString ng_txt;
	QString addr;
}TPLCRegCell;

// PLC自定义解析的配置
typedef struct tagPLCDecodeCell {
	QString addr_pos; // 字段起始地址
	QString key_; // 此字段存储的key, 如 panel_id, meter等
	int cnt{1}; // 字数 
	int data_type{ 0 };   // 数据类型 emDataType
}TPLCDecodeCell;

typedef struct tagPLCReadCell {
	int cnt;		  // 请求读取个数
	QString addr;

	// 数据解析时用到
	int decode_type{ 0 };	  // 数据解析方法 emDecodeType
	QStringList keys; // 读取到的数据每个字对应的key
	QMap<QString, TPLCRegCell> mpRegs;// read_status 专用
	QMap<QString, TPLCDecodeCell> mpDecodes;// 专用解析
}TPLCReadCell;

//////////////////////////////////////////////////////////////////////////
#endif//DEF_LP_PLC_CONFIG_BASE_H_2023J