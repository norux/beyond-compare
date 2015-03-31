#ifndef CCOMPARINGINFORMATION_H
#define CCOMPARINGINFORMATION_H

#include <QLayout>
#include <QLabel>
#include <QListView>

#include "common.h"

class CComparingInformation : public QVBoxLayout
{
public:
	CComparingInformation();
	~CComparingInformation();

private:	/* 함수 선언부 */
	void initLayout ( void );

	QLabel * createLabel (const QString & text);
	QListView * createListView ( void );

private:	/* 변수 선언부 */
	QLabel * m_statusbarLabel;
	QListView * m_statusbarListView;
};

#endif // CCOMPARINGINFORMATION_H
