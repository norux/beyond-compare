#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDesktopWidget>

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent)
{
	/* 초기화 */
	m_cFileMenu = NULL;
	m_cOpen = NULL;
	m_cExit = NULL;

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
