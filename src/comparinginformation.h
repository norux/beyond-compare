#ifndef CCOMPARINGINFORMATION_H
#define CCOMPARINGINFORMATION_H

#include <QLayout>
#include <QLabel>
#include <QListWidget>

#include "common.h"

class CComparingInformation : public QWidget
{
	Q_OBJECT

public:	/* 생성,소멸자 */
	CComparingInformation(QWidget * parent = 0);
	~CComparingInformation();


public:	/* Public 함수 선언부 */
	void addStatusbarListItem (const QString& strItem);

private:	/* Private 함수 선언부 */
	void initLayout ( void );

	QLabel * createLabel (const QString & text);
	QListWidget * createListWidget ( void );


private:	/* Private 변수 선언부 */
	QLabel * m_statusbarLabel;
	QListWidget * m_statusbarListWidget;
};

#endif // CCOMPARINGINFORMATION_H
