#ifndef CCOMPARINGRESULT_H
#define CCOMPARINGRESULT_H

#include <QListWidget>

#include "common.h"

class CComparingResult : public QListWidget
{
	Q_OBJECT
public:
	explicit CComparingResult(QListWidget *parent = 0);
	~CComparingResult();

signals:

public slots:
};

#endif // CCOMPARINGRESULT_H
