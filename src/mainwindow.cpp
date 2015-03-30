#include "mainwindow.h"

#include <QMenuBar>
#include <QDesktopWidget>

#include <QDesktopWidget>

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent)
{
	/* 초기화 */
	m_fileMenu = NULL;
	m_openAction = NULL;
	m_exitAction = NULL;

	m_cLFileView = NULL;
	m_cRFileView = NULL;

	m_cCmpRes = NULL;
	m_cCmpInfo = NULL;

	m_cCopyProcess = NULL;

	m_isReload = false;

	/* 메뉴 생성 */
	initMenus ();

	/* 레이아웃 초기화 */
	initLayout();
}

MainWindow::~MainWindow()
{
	if (NULL != m_fileMenu)
	{
		delete m_fileMenu;
		m_fileMenu = NULL;
	}
	if (NULL != m_openAction)
	{
		delete m_openAction;
		m_openAction = NULL;
	}
	if (NULL != m_exitAction)
	{
		delete m_exitAction;
		m_exitAction = NULL;
	}
	if (NULL != m_cLFileView)
	{
		delete m_cLFileView;
		m_cLFileView = NULL;
	}
	if (NULL != m_cRFileView)
	{
		delete m_cRFileView;
		m_cRFileView = NULL;
	}
	if (NULL != m_cCmpRes)
	{
		delete m_cCmpRes;
		m_cCmpRes = NULL;
	}
	if (NULL != m_cCmpInfo)
	{
		delete m_cCmpInfo;
		m_cCmpInfo = NULL;
	}
	if (NULL != m_cCopyProcess)
	{
		delete m_cCopyProcess;
		m_cCopyProcess = NULL;
	}
}

void MainWindow::initMenus ( void )
{
	m_fileMenu = menuBar()->addMenu(tr("&File"));
	m_openAction = new QAction (tr("&Open"), this);
	m_exitAction = new QAction (tr("E&xit"), this);

	assert (NULL != m_fileMenu);
	assert (NULL != m_openAction);
	assert (NULL != m_exitAction);

	m_fileMenu->addAction(m_openAction);
	m_fileMenu->addAction(m_exitAction);

	connect (m_openAction, SIGNAL(triggered()), this, SLOT(slotOpenFiles()));
	connect (m_exitAction, SIGNAL(triggered()), this, SLOT(close()));
}

void MainWindow::slotOpenFiles ( void )
{
	// TODO
}

void MainWindow::drawWindowAtCenter ( void )
{
	/* 메인 윈도우를 화면 가운데에 그림 */
	QRect available_geom = QDesktopWidget().availableGeometry();
	QRect current_geom = frameGeometry();
	setGeometry(available_geom.width() / 2 - current_geom.width() / 2,
								available_geom.height() / 2 - current_geom.height() / 2,
								current_geom.width(),
								current_geom.height());
}

void MainWindow::slotRunFileview( void )
{
	assert (NULL != m_cLFileView);
	assert (NULL != m_cRFileView);

	if (true == m_cLFileView->isRunning() &&
		 true == m_cRFileView->isRunning())
	{
		compareFiles();
	}
	else
	{
		// do nothing
	}
}

void MainWindow::compareFiles ( void )
{
	assert (NULL != m_cLFileView);
	assert (NULL != m_cRFileView);
	assert (NULL != m_cCmpInfo);

	int nTotalLeftRows = m_cLFileView->getTableWidgetRows();
	int nTotalRightRows = m_cRFileView->getTableWidgetRows();
	QString strLeftName;
	int nRightRow = -1;

	/* 대조군 항목은 일단 빨간색으로 놓은 후, 최종적으로 동일파일 판단 되면 검정색으로 변경한다. */
	for (int i = 0; i < nTotalRightRows; i++)
	{
		m_cRFileView->updateTableWidgetItemColor (i, Qt::red);
	}
	for (int i = 0; i < nTotalLeftRows; i++)
	{
		// Compare Name
		strLeftName = m_cLFileView->getNameStringInTable(i);
		nRightRow = m_cRFileView->findNameInTable(strLeftName);

		if (-1 == nRightRow)
		{
			m_cLFileView->updateTableWidgetItemColor (i, Qt::red);
			qApp->processEvents();
			continue;
		}

		// Compare Size
		if (m_cLFileView->getSizeStringInTable(i) != m_cRFileView->getSizeStringInTable(nRightRow))
		{
			m_cLFileView->updateTableWidgetItemColor (i, Qt::red);
			m_cRFileView->updateTableWidgetItemColor (nRightRow, Qt::red);
			qApp->processEvents();
			continue;
		}

		// Compare Mod Time
		if (m_cLFileView->getTimeStringInTable(i) != m_cRFileView->getTimeStringInTable(nRightRow))
		{
			m_cLFileView->updateTableWidgetItemColor (i, Qt::red);
			m_cRFileView->updateTableWidgetItemColor (nRightRow, Qt::red);
			qApp->processEvents();
			continue;
		}

		// 동일파일 판정
		m_cLFileView->updateTableWidgetItemColor (i, Qt::black);
		m_cRFileView->updateTableWidgetItemColor (nRightRow, Qt::black);
		qApp->processEvents();
	}

	/* 상태메세지 출력 */
	if (false == m_isReload)
	{
		QString strMsg = tr("Complete: ") + m_cLFileView->getCurrentPath() + tr(" and ") + m_cRFileView->getCurrentPath();
		m_cCmpInfo->addStatusbarListItem(strMsg);
	}
}

void MainWindow::slotSortContents (int column ,Qt::SortOrder order)
{

	m_cLFileView->synchronizeColumnOrder(column, order);
	m_cRFileView->synchronizeColumnOrder(column, order);
}

void MainWindow::slotCopyFinished (int nResult)
{
	if (NULL != m_cCopyProcess)
	{
		delete m_cCopyProcess;
		m_cCopyProcess = NULL;
	}

	QString strMsg;
	if(CCopyThread::CopySuccess == nResult)
	{
		m_cLFileView->reload();
		m_cRFileView->reload();

		/* 상태메세지 출력 */
		strMsg = tr("Copy Completed.");
		m_cCmpInfo->addStatusbarListItem(strMsg);
	}
	else if (CCopyThread::StopWhileCopying == nResult)
	{
		/* 상태메세지 출력 */
		strMsg = tr("Copy Cancled.");
		m_cCmpInfo->addStatusbarListItem(strMsg);
	}
	else if (CCopyThread::CopyFailedDontHavePermission == nResult)
	{
		/* 상태메세지 출력 */
		strMsg = tr("Copy Failed: Doesn't Have Permission");
		m_cCmpInfo->addStatusbarListItem(strMsg);
	}
	else	/* nResult is Unknown */
	{
		/* 상태메세지 출력 */
		strMsg = tr("Unknown Error.");
		m_cCmpInfo->addStatusbarListItem(strMsg);
	}

	m_isReload = false;
}

QFileInfoList MainWindow::obtainFilesCopied( void )
{
	QFileInfoList files;

	assert (NULL != m_cLFileView);
	assert (NULL != m_cRFileView);

	int nTotalLeftRows = m_cLFileView->getTableWidgetRows();
	QString strLeftName;
	int nRightRow = -1;

	for (int i = 0; i < nTotalLeftRows; i++)
	{
		// Compare Name
		strLeftName = m_cLFileView->getNameStringInTable(i);
		nRightRow = m_cRFileView->findNameInTable(strLeftName);

		QFileInfo fileInfo;

		if (false == m_cLFileView->getFileInfoInEntries (strLeftName, &fileInfo))
		{
			qDebug() << "getFileInfoInEntries Error";
			break;
		}

		if (-1 == nRightRow)
		{

			files << fileInfo;

			qApp->processEvents();
			continue;
		}

		// Compare Size
		if (m_cLFileView->getSizeStringInTable(i) != m_cRFileView->getSizeStringInTable(nRightRow))
		{
			files << fileInfo;
			qApp->processEvents();
			continue;
		}

		// Compare Mod Time
		if (m_cLFileView->getTimeStringInTable(i) != m_cRFileView->getTimeStringInTable(nRightRow))
		{
			files << fileInfo;
			qApp->processEvents();
			continue;
		}

		// 동일파일 판정
		qApp->processEvents();
	}


	return files;
}

void MainWindow::slotFileNameCopied (QString strFileName)
{
	/* 상태메세지 출력 */
	{
		QString strMsg;
		if (false == strFileName.isEmpty())
		{
			strMsg = strFileName + " Copied..";
		}
		else /* true == strName.isEmpty() */
		{
			// do nothing
		}

		m_cCmpInfo->addStatusbarListItem(strMsg);
	}
}

void MainWindow::slotCopyStart (void )
{
	if (NULL != m_cCopyProcess)
	{
		qDebug() << "Alread Copy Process.";
		return;
	}

	if (m_cLFileView->isRunning() && m_cRFileView->isRunning())
	{
		QString strRightPath = m_cRFileView->getCurrentPath();

		QFileInfoList files = obtainFilesCopied();

		if (true == files.isEmpty())
		{
			QMessageBox::information(this, tr("Information"), tr("There are no files to be copied."));
		}
		else
		{
			m_cCopyProcess = new CCopyProcess(this);

			assert (NULL != m_cCopyProcess);

			connect (m_cCopyProcess, SIGNAL(fileNameCopyFinished(QString)), this, SLOT(slotFileNameCopied(QString)));
			connect (m_cCopyProcess, SIGNAL(finished(int)), this, SLOT(slotCopyFinished(int)));

			m_cCopyProcess->runCopy(files, strRightPath);
		}
	}
	else
	{
		QMessageBox::critical(this, tr("Error"), tr("Invalid Path"));
	}

	m_isReload = true;
}


/*
 * 함  수  명: initLayout
 * 파라미터: void
 * 리  턴  값: void
 * 역       할: QGridLayout을 이용하여 레이아웃을 그리고, 위젯을 담음
*/
void MainWindow::initLayout ( void )
{
	QGridLayout * mainLayout = new QGridLayout;
	assert (NULL != mainLayout);

	m_cLFileView = new CFileView;
	m_cRFileView = new CFileView;
	m_cCmpRes = new CComparingResult;
	m_cCmpInfo = new CComparingInformation;

	assert (NULL != m_cLFileView);
	assert (NULL != m_cRFileView);
	assert (NULL != m_cCmpRes);
	assert (NULL != m_cCmpInfo);

	connect (m_cLFileView, SIGNAL(beRun()), this, SLOT(slotRunFileview()));
	connect (m_cRFileView, SIGNAL(beRun()), this, SLOT(slotRunFileview()));
	connect (m_cLFileView, SIGNAL(sortBySectionClicked(int, Qt::SortOrder)), this, SLOT(slotSortContents(int, Qt::SortOrder)));
	connect (m_cRFileView, SIGNAL(sortBySectionClicked(int, Qt::SortOrder)), this, SLOT(slotSortContents(int, Qt::SortOrder)));

	connect (m_cCmpRes, SIGNAL(copyButtonClicked()), this, SLOT(slotCopyStart()));

	mainLayout->addWidget (m_cLFileView, 0, 0);
	mainLayout->addWidget (m_cRFileView, 0, 2);
	mainLayout->addWidget (m_cCmpRes, 0, 1);
	mainLayout->addWidget (m_cCmpInfo, 1, 0, 1, 3);

	mainLayout->setSpacing(1);

	QWidget * centralWidget = new QWidget;
	assert (NULL != centralWidget);

	centralWidget->setLayout( mainLayout );
	setCentralWidget(centralWidget);


	/* 축소할  수 있는 윈도우의 최소 크기 */
	setMinimumSize(1000,600);

	setWindowTitle(tr("Beyond Compare"));
	drawWindowAtCenter ();
}


void MainWindow::initMenus ( void )
{
	assert (NULL == m_cFileMenu);
	assert (NULL == m_cOpen);
	assert (NULL == m_cExit);

	if (NULL == m_cFileMenu)
	{
		m_cFileMenu = menuBar()->addMenu(tr("&File"));

		assert (NULL != m_cFileMenu);
	}

	if (NULL == m_cOpen)
	{
		m_cOpen = new QAction (tr("&Open"), this);

		assert (NULL != m_cOpen);

		m_cFileMenu->addAction(m_cOpen);
		connect (m_cOpen, SIGNAL(triggered()), this, SLOT(openFiles()));
	}

	if (NULL == m_cExit)
	{
		m_cExit = new QAction (tr("E&xit"), this);

		assert (NULL != m_cExit);

		m_cFileMenu->addAction(m_cExit);
		connect (m_cExit, SIGNAL(triggered()), this, SLOT(close()));
	}

}

void MainWindow::openFiles ( void )
{

}

void MainWindow::initLayout ( void )
{
	QGridLayout * mainLayout = new QGridLayout;
	assert (NULL != mainLayout);

	m_cLFileView = new CFileView;
	assert (NULL != m_cLFileView);
	m_cRFileView = new CFileView;
	assert (NULL != m_cRFileView);
	m_cCmpRes = new CComparingResult;
	assert (NULL != m_cCmpRes);
	m_cCmpInfo = new CComparingInformation;
	assert (NULL != m_cCmpInfo);


	mainLayout->addLayout (m_cLFileView, 0, 0, 2, 1);
	mainLayout->addLayout (m_cRFileView, 0, 2, 2,1);
	mainLayout->addWidget (m_cCmpRes, 1, 1);
	mainLayout->addWidget (m_cCmpInfo, 2, 0, 1, 3 );

	mainLayout->setContentsMargins(0,0,0,0);

	QWidget * centralWidget = new QWidget;
	assert (NULL != centralWidget);

	centralWidget->setLayout( mainLayout );
	setCentralWidget(centralWidget);


	resize(1000, 600);

	/* 메인 윈도우의 타이틀 명명 */
	setWindowTitle(tr("Beyond Compare"));

	/* 메인 윈도우를 화면 가운데에 그림 */
	QRect available_geom = QDesktopWidget().availableGeometry();
	QRect current_geom = frameGeometry();
	setGeometry(available_geom.width() / 2 - current_geom.width() / 2,
								available_geom.height() / 2 - current_geom.height() / 2,
								current_geom.width(),
								current_geom.height());
}
