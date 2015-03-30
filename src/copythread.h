#ifndef CCOPYTHREAD_H
#define CCOPYTHREAD_H

#include <QWidget>

#include <QThread>
#include <QMutex>
#include <QFileInfo>
#include <QFile>
#include <QIODevice>
#include <QString>
#include <QDir>

#include "common.h"
#include <utime.h>
#include <sys/types.h>
#include <sys/stat.h>


class CCopyThread : public QThread
{
	Q_OBJECT

public: /* Public Enum  & Struct*/
	enum CopyFileStatus
	{
		CopySuccess  = 0,
		StopWhileCopying = 1,
		CopyFailedDontHavePermission = 2
	};

public:	/* 생성,소멸자 */
	explicit CCopyThread();
	virtual ~CCopyThread();

public:	/* set,get 함수 선언부 */
	qint64 getSizeOfFiles ( void );
	void setFiles (QFileInfoList files);
	void setPath (QString path);

public:	/* Public 함수 선언부 */
	void stop ();

protected:	/* Protected 함수 선언부  */
	void run ();

private:	/* Private 함수 선언부 */
	CCopyThread::CopyFileStatus copyFile( void );
	int setSameTime (const QString& fromFile, const QString& toFile);
	bool hasPermission ( void );

private slots:	/* Private Slot 선언부 */
	void slotFileWritten(qint64 bytes);

signals:	/* Signal 선언부 */
	void copyFileFinished ( int );
	void copyFileBytesWritten (int);
	void fileNameCopied(QString);

private:	/* Private 변수 선언부 */
	QMutex m_mutex;
	volatile bool m_bStopped;

	QFileInfoList m_copyFiles;
	qint64 m_sizeOfFiles;

	QString m_strPathCopied;
};

#endif // CCOPYTHREAD_H
