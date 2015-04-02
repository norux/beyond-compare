#ifndef CCOMPARINGINFORMATION_H
#define CCOMPARINGINFORMATION_H

#include <QLayout>
#include <QLabel>
#include <QListWidget>

#include "common.h"

class CComparingInformation : public QWidget
{
	Q_OBJECT

public:
	CComparingInformation(QWidget * parent = 0);
	~CComparingInformation();


public:	/* 함수 선언부 */
	void addStatusbarListItem (const QString& strItem);

private:	/* 함수 선언부 */
	void initLayout ( void );

	QLabel * createLabel (const QString & text);
	QListWidget * createListWidget ( void );


private:	/* 변수 선언부 */
	QLabel * m_statusbarLabel;
	QListWidget * m_statusbarListWidget;
};

#endif // CCOMPARINGINFORMATION_H
