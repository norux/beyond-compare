#ifndef CCOPYPROCESS_H
#define CCOPYPROCESS_H

#include <QWidget>
#include <QProgressBar>
#include <QLayout>
#include <QLabel>
#include <QString>
#include <QFileInfo>

#include <unistd.h>
#include <QCloseEvent>

#include "copythread.h"

#include "common.h"

class CCopyThread;

class CCopyProcess : public QDialog
{
	Q_OBJECT

public:	/* 생성,소멸자 */
	explicit CCopyProcess(QWidget * parent = 0);
	virtual ~CCopyProcess();


public:	/* Public 함수 선언부 */
	void runCopy(QFileInfoList& copyFiles, QString& strToPath);

protected:	/* Protected 함수 선언부 */
	void closeEvent(QCloseEvent * event);	/* Overrided */

private:	/* Private 함수 선언부 */
	void initLayout ( void );

	QLabel * createLabel ( void );
	QProgressBar * createProgressBar ( void );

private slots:	/* Private Slot 선언부 */
	void slotCopyFinished ( int copyStatus );
	void slotProgressBarAccumulated(int nBytes) ;
	void slotFileNameCopied (QString strName);

signals:	/* Signal 선언부 */
	void fileNameCopyFinished (QString);


private:	/* Private 변수 선언부 */
	QProgressBar * m_fileCopyProgressBar;
	QLabel * m_fileNameLabel;

	CCopyThread * m_cCopyThread;

	qint64 m_nCurrentFileBytes;
};

#endif // CCOPYPROCESS_H
