#include "mainwindow.h"
#include "ui_mainwindow.h"

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
	/* TODO */
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

	connect (m_openAction, SIGNAL(triggered()), this, SLOT(openFiles()));
	connect (m_exitAction, SIGNAL(triggered()), this, SLOT(close()));
}

void MainWindow::openFiles ( void )
{

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

	mainLayout->addLayout (m_cLFileView, 0, 0);
	mainLayout->addLayout (m_cRFileView, 0, 2);
	mainLayout->addLayout (m_cCmpRes, 0, 1);
	mainLayout->addLayout (m_cCmpInfo, 1, 0, 1, 3);

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
