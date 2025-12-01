#pragma once

#include <QtCore/qglobal.h>
#include <QWidget>
#ifndef BUILD_STATIC
# if defined(LPVISUALCONFIGTOOL_LIB)
#  define LPVISUALCONFIGTOOL_EXPORT Q_DECL_EXPORT
# else
#  define LPVISUALCONFIGTOOL_EXPORT Q_DECL_IMPORT
# endif
#else
# define LPVISUALCONFIGTOOL_EXPORT
#endif

class LPVISUALCONFIGTOOL_EXPORT lpVisualConfigToolMgr :public QWidget
{
	Q_OBJECT
public:
	lpVisualConfigToolMgr(QWidget *parent = nullptr) :QWidget(parent) {}
	virtual ~lpVisualConfigToolMgr() {}

public slots:
};

typedef QSharedPointer<lpVisualConfigToolMgr>LPVISUALCONFIGTOOL_SPTR;
LPVISUALCONFIGTOOL_EXPORT QSharedPointer<lpVisualConfigToolMgr>lpCreateVisualConfigTool(QWidget *parent = nullptr);