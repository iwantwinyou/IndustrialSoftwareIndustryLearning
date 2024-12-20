#pragma once
#include <QtCore>
#ifndef DEF_LP_OTHERAPP_CONFIG_BASE_H_2024J
#define DEF_LP_OTHERAPP_CONFIG_BASE_H_2024J
//////////////////////////////////////////////////////
#define INT "001002"
#define STRING "001003"
#define CONNOTHERAPP_VER  "v1.0.1.0"
namespace OTHERAPP
{
	const QString CFG_PATH = "./lpIPUConfig/SetConfig.json";

	//组包：head + type + data
	// "000007"+   "001002"+"1"; //1为Error  0为OK
	const QString dataLen = "000007";
	//const QString type = "001002";

	//recv: head+type+data
	//const QString recv_head = "000070";


};

enum class emDataType
{
	APP_INT = 0, //0 int， num=1
	APP_STR  //1 String
};

enum  class jobSwitchingType
{
	e_plc=0,
	e_otherApp
};

////////////////////////////////////////////////////
#endif//DEF_LP_OTHERAPP_CONFIG_BASE_H_2024J