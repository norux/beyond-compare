#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenu>

#include "fileview.h"
#include "comparinginformation.h"
#include "comparingresult.h"

#include "common.h"

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:	/* 생성,소멸자 */
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();


private:		/* Private 함수 선언부 */
	void initMenus ( void );
	void initLayout ( void );
	void drawWindowAtCenter ( void );

	void compareFiles ( void );

private:		/* Private 변수 선언부 */
	QMenu * m_fileMenu;
	QAction * m_openAction;
	QAction * m_exitAction;

	CFileView *m_cLFileView;
	CFileView *m_cRFileView;
	CComparingResult * m_cCmpRes;
	CComparingInformation * m_cCmpInfo;

private slots:	/* Private Slot 함수 선언부 */
	void slotOpenFiles ( void );

	void slotRunFileview ( void );
	void slotSortContents (int column, Qt::SortOrder order);

signals:	/* Signal 선언부 */
	// none
};

#endif // MAINWINDOW_H
