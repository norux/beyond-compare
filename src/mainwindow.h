#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenu>

#include "fileview.h"
#include "comparinginformation.h"
#include "comparingresult.h"
#include "copythread.h"
#include "copyprocess.h"

#include "common.h"


class CCopyThread;

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:	/* 생성,소멸자 */
	explicit MainWindow(QWidget *parent = 0);
	virtual ~MainWindow();

private:		/* Private 함수 선언부 */
	void initMenus ( void );
	void initLayout ( void );
	void drawWindowAtCenter ( void );

	void compareFiles ( void );
	QFileInfoList obtainFilesCopied( void );

private slots:	/* Private Slot 함수 선언부 */
	void slotOpenFiles ( void );

	void slotRunFileview ( void );
	void slotSortContents (int column, Qt::SortOrder order);

	void slotCopyStart (void );
	void slotCopyFinished (int);

	void slotFileNameCopied (QString strFileName);


signals:	/* Signal 선언부 */
	// none

private:		/* Private 변수 선언부 */
	QMenu * m_fileMenu;
	QAction * m_openAction;
	QAction * m_exitAction;

	CFileView *m_cLFileView;
	CFileView *m_cRFileView;
	CComparingResult * m_cCmpRes;
	CComparingInformation * m_cCmpInfo;

	CCopyProcess * m_cCopyProcess;

	bool m_isReload;
};

#endif // MAINWINDOW_H
