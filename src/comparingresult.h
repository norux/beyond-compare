#ifndef CCOMPARINGRESULT_H
#define CCOMPARINGRESULT_H

#include <QWidget>
#include <QLayout>
#include <QTableWidget>
#include <QLabel>
#include <QHeaderView>

#include "common.h"

class CComparingResult : public QWidget
{
	Q_OBJECT

public:
	CComparingResult(QWidget * parent = 0);
	~CComparingResult();

private:	/* 함수 선언부 */
	void initLayout ( void );

	QLabel * createLabel (const QString & text);
	QTableWidget * createTableWidget ();

private:	/* 변수 선언부 */
	QLabel * m_paddingLabel;
	QTableWidget * m_resultViewTable;

};

#endif // CCOMPARINGRESULT_H
