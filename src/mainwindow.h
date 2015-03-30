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

public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();

private:		/* 함수 선언부 */
	void initMenus ( void );
	void initLayout ( void );

private slots:
	void openFiles ( void );

private:		/* 변수 선언부 */
	QMenu * m_cFileMenu;
	QAction * m_cOpen;
	QAction * m_cExit;

	CFileView *m_cLFileView;
	CFileView *m_cRFileView;

	CComparingResult * m_cCmpRes;
	CComparingInformation * m_cCmpInfo;

};

#endif // MAINWINDOW_H
