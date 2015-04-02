#include "mainwindow.h"

#include <QMenuBar>
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

		m_cLFileView->updateTableWidgetItemColor (i, Qt::black);
		m_cRFileView->updateTableWidgetItemColor (nRightRow, Qt::black);
		qApp->processEvents();
	}

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
