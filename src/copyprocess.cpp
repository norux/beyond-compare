#include "copyprocess.h"

CCopyProcess::CCopyProcess(QWidget * parent) : QDialog(parent)
{
	/* 초기화 */
	m_fileCopyProgressBar = NULL;
	m_fileNameLabel = NULL;

	m_cCopyThread = NULL;
	m_nCurrentFileBytes = 0;

	initLayout();
}

CCopyProcess::~CCopyProcess()
{
	if (NULL != m_cCopyThread)
	{
		delete m_cCopyThread;
		m_cCopyThread = NULL;
	}

	if (NULL != m_fileCopyProgressBar)
	{
		delete m_fileCopyProgressBar;
		m_fileCopyProgressBar = NULL;
	}
	if (NULL != m_fileNameLabel)
	{
		delete m_fileNameLabel;
		m_fileNameLabel = NULL;
	}
}

void CCopyProcess::closeEvent(QCloseEvent * event)
{
	m_cCopyThread->stop();
	m_cCopyThread->quit();
	m_cCopyThread->wait();

	event->accept();

	close ();
}

QLabel * CCopyProcess::createLabel ( void )
{
	QLabel * label = new QLabel;

	assert (NULL != label);

	return label;
}
QProgressBar * CCopyProcess::createProgressBar ( void )
{
	QProgressBar * progressBar = new QProgressBar;

	assert (NULL != progressBar);

	progressBar->setMinimum (0);
	progressBar->setMaximum(0);

	return progressBar;
}

void CCopyProcess::slotProgressBarAccumulated(int nBytes)
{
	m_nCurrentFileBytes += nBytes;
	m_fileCopyProgressBar->setValue(m_nCurrentFileBytes);
}

void CCopyProcess::slotCopyFinished ( int copyStatus)
{
	qDebug() << "Finish Copying Files";

	emit finished(copyStatus);
}

void CCopyProcess::slotFileNameCopied (QString strName)
{
	if (false == strName.isEmpty())
	{
		m_fileNameLabel->setText(tr("Copy File: ") + strName);
	}
	else /* true == strName.isEmpty() */
	{
		// do nothing
	}
	emit fileNameCopyFinished(strName);
}

void CCopyProcess::runCopy(QFileInfoList& copyFiles, QString& strToPath)
{
	assert (false == copyFiles.isEmpty());
	assert (false == strToPath.isEmpty());

	m_cCopyThread = new CCopyThread ();

	assert (NULL != m_cCopyThread);

	connect (m_cCopyThread, SIGNAL(copyFileBytesWritten(int)), this, SLOT(slotProgressBarAccumulated(int)));
	connect (m_cCopyThread, SIGNAL(copyFileFinished(int)), this, SLOT(slotCopyFinished(int)));
	connect (m_cCopyThread, SIGNAL(fileNameCopied(QString)), this, SLOT(slotFileNameCopied(QString)));
	connect (m_cCopyThread, SIGNAL(finished()), this, SLOT(deleteLater()));

	m_cCopyThread->setFiles(copyFiles);
	m_cCopyThread->setPath(strToPath);

	qint64 nTotalSize = m_cCopyThread->getSizeOfFiles ();

	qDebug () << "in runCoypy :: nTotalSize : " << nTotalSize;
	m_fileCopyProgressBar->setMaximum(nTotalSize);


	/* Thread Start */
	m_cCopyThread->start();
}

void CCopyProcess::initLayout (void )
{
	m_fileCopyProgressBar = createProgressBar();
	m_fileNameLabel = createLabel ();

	assert (NULL != m_fileCopyProgressBar);
	assert (NULL != m_fileNameLabel);

	QVBoxLayout * layout = new QVBoxLayout;

	assert (NULL != layout);

	layout->addWidget(m_fileNameLabel);
	layout->addWidget(m_fileCopyProgressBar);

	setLayout(layout);

	setFixedSize(500, 100);

	show();
}
