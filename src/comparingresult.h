#ifndef CCOMPARINGRESULT_H
#define CCOMPARINGRESULT_H

#include <QWidget>
#include <QLayout>
#include <QTableWidget>
#include <QLabel>
#include <QHeaderView>
#include <QPushButton>

#include "common.h"

class CComparingResult : public QWidget
{
	Q_OBJECT

public: /* 생성,소멸자 */
	explicit CComparingResult(QWidget * parent = 0);
	virtual ~CComparingResult();


private:	/* Private 함수 선언부 */
	void initLayout ( void );

	QLabel * createLabel (const QString & text);
	QTableWidget * createTableWidget ();
	QPushButton * createButton (const QString &strImage, const char * slot) const;

private slots:	/* Private Slot 선언부 */
	void slotCopyButtonClicked ( void );

signals:	/* Signal 선언부 */
		void copyButtonClicked(void);

private:	/* Private 변수 선언부 */
	QLabel * m_paddingLabel;
	QTableWidget * m_resultViewTable;

	QPushButton * m_copyToRightButton;

};

#endif // CCOMPARINGRESULT_H
