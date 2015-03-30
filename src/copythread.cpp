#include "copythread.h"

#include <string>

CCopyThread::CCopyThread()
{
	m_bStopped = false;

//	qDebug() << "Path Copied: " << m_strPathCopied ;

//	run ();
}

CCopyThread::~CCopyThread()
{
	// TODO
}

void CCopyThread::setFiles (QFileInfoList files)
{
	m_copyFiles = files;

	/* Mutex Lock */
	{
		QMutexLocker mutexLocker (&m_mutex);

		m_sizeOfFiles = 0;
		for (QFileInfoList::iterator iter = m_copyFiles.begin(); iter != m_copyFiles.end(); iter++)
		{
			m_sizeOfFiles += iter->size();
		}
	}
	/* Mutex Unlock */
}
void CCopyThread::setPath (QString path)
{
	m_strPathCopied = path;
}

void CCopyThread::stop ()
{
	/* Mutex Lock */
	{
		QMutexLocker mutexLocker(&m_mutex);

		m_bStopped = true;
	}
	/* Mutex Unlock */
}

qint64 CCopyThread::getSizeOfFiles ( void )
{
	return m_sizeOfFiles;
}

void CCopyThread::slotFileWritten(qint64 bytes)
{
	qDebug() << "in here?";
	emit copyFileBytesWritten(bytes);
}

inline static QString makePath (const QString& strPath, const QString& strFile)
{
	assert (false == strPath.isEmpty());
	assert (false == strFile.isEmpty());

	QString path;

	path = strPath;

	if ('/' != strPath[strPath.length() - 1])
	{
		path += '/';
	}

	path += strFile;

	return path;
}

int CCopyThread::setSameTime (const QString& fromFileName, const QString& toFileName)
{
	assert (false == fromFileName.isEmpty());
	assert (false == toFileName.isEmpty());

	std::string strFromFileName(fromFileName.toStdString());
	std::string strToFileName(toFileName.toStdString());

	const char * szFromFileName = strFromFileName.c_str();
	const char * szToFileName = strToFileName.c_str();

	struct stat fromFileStat;

	// if error happen, return -1
	if (0 != stat (szFromFileName, &fromFileStat))
	{
		qDebug() << "Stat Error";
		return -1;
	}

	struct utimbuf setTime;

	setTime.modtime	 = fromFileStat.st_mtim.tv_sec;
	setTime.actime = fromFileStat.st_atim.tv_sec;

	// if error happen, return -1
	int nResult = utime(szToFileName, &setTime);

	return nResult;
}

bool CCopyThread:: hasPermission ( void )
{
	QFileInfo fileInfo (m_strPathCopied);

	// Permission Check
	if (false == fileInfo.isWritable())
	{
		return false;
	}
	else
	{
		return true;
	}
}

CCopyThread::CopyFileStatus CCopyThread::copyFile( void )
{
	if (false == hasPermission())
	{
		return CopyFailedDontHavePermission;
	}

	for (QFileInfoList::iterator iter = m_copyFiles.begin(); iter != m_copyFiles.end(); iter++)
	{
		QString strFromFile = iter->absoluteFilePath();
		QString strToFile = makePath(m_strPathCopied, iter->fileName());
		qint64 nFileBytes = iter->size();

		QFile toFile (strToFile);
		QFile fromFile (strFromFile);

		if (true == toFile.exists())
		{
			toFile.remove();
		}

		emit fileNameCopied(fromFile.fileName());

		// Copy File
		if (false == fromFile.copy(toFile.fileName()))
		{
			qDebug() << "Error While copy file";
		}

		/* Mutex Lock */
		{
			QMutexLocker mutexLocker (&m_mutex);

			// if error happen, return -1
			if ( -1 == setSameTime(fromFile.fileName(), toFile.fileName()))
			{
				qDebug() << "setSameTime () error";
			}

			if (true == m_bStopped)
			{
				return StopWhileCopying;
			}
		}
		/* Mutex Unlock */

		emit copyFileBytesWritten(nFileBytes);
	}

	return CopySuccess;
}

void CCopyThread::run ()
{
	qDebug() <<"=========Start Thread=========";

	CCopyThread::CopyFileStatus copyStatus = CopySuccess;

	copyStatus = copyFile ();

	qDebug() <<"=========Exit Thread==========";
	emit copyFileFinished (copyStatus);
}
