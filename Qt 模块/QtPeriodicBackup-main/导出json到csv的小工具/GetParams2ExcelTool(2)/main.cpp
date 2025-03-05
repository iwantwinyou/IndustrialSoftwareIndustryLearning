#include "GetParams2ExcelTool.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	GetParams2ExcelTool w;
	w.show();
	return a.exec();
}
