#ifndef FILEVIEW_H
#define FILEVIEW_H

#include <QObject>
#include <QWidget>
#include <QLayout>
#include <QLabel>
#include <QComboBox>
#include <QPushButton>
#include <QTreeWidget>
#include <QTableWidget>
#include <QHeaderView>

#include "common.h"

class CFileView : public QGridLayout
{

public:
	CFileView();
	virtual ~CFileView();

private slots:
	void testtesttest(QString string);

signals:

private: /* 함수 선언부 */
	void initLayout ( void );

	QComboBox * createComboBox ();
	QLabel * createLabel (const QString & text);
	QPushButton * createButton ();
	QTableWidget * createTableWidget ();

private:	/* 변수 선언부 */
	QLabel * m_pathLabel;
	QComboBox * m_pathComboBox;
	QPushButton *m_dirButton;
	QTableWidget * fileviewTable;

};

#endif // FILEVIEW_H
