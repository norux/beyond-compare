#ifndef CCOMPARINGRESULT_H
#define CCOMPARINGRESULT_H

#include <QLayout>
#include <QTableWidget>
#include <QLabel>
#include <QHeaderView>

#include "common.h"

class CComparingResult : public QVBoxLayout
{
public:
	CComparingResult();
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
