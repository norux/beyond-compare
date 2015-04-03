#ifndef FILEVIEW_H
#define FILEVIEW_H

#include <QWidget>
#include <QLayout>
#include <QLabel>
#include <QComboBox>
#include <QPushButton>
#include <QTreeWidget>
#include <QTableWidget>
#include <QHeaderView>
#include <QFileDialog>
#include <QFileInfo>
#include <QDateTime>
#include <QFileIconProvider>

#include "common.h"

class CFileView : public QWidget
{
	Q_OBJECT

public: /* 생성,소멸자 */
	explicit CFileView(QWidget * parent = 0);
	virtual ~CFileView();

public:	/* set,get 함수 선언부 */
	bool isRunning ( void ) const;
	QString getCurrentPath ( void ) const;

	int getTableWidgetRows ( void ) const;
	QString getNameStringInTable (int rows) const;
	QString getSizeStringInTable (int rows) const;
	QString getTimeStringInTable (int rows) const;

public: /* Public 함수 선언부 */
	/* return rows. if cannot find, -1 */
	int findNameInTable (const QString& strName) const;

	void synchronizeColumnOrder (int column, Qt::SortOrder order);
	void updateTableWidgetItemColor (int rows, Qt::GlobalColor color);


private: /* Private 함수 선언부 */
	void initLayout ( void );

	/* Create Object  Functions */
	QComboBox * createComboBox (const char * slot = NULL) const;
	QLabel * createLabel (const QString & strText) const;
	QPushButton * createButton (const QString &strText, const char * slot = NULL) const;
	QTableWidget * createTableWidget () const;
	QTableWidgetItem * createTableWidgetItem (const QString& strItem) const;

	void clearTableWidget ( void );

	void updateItem (const QString& strDirectory);
	void drawFileEntry(const QString &strDirectory);
	bool checkValidationOfDirctory (const QString &strDirectory) const;


private slots:	/* Private Slot 함수 선언부 */
	void slotDirButtonClicked();
	void slotPathComboBoxActivated(QString strDirectory);
	void slotHeaderSectionClicked(int column);
	void slotWidgetItemDoubleClicked(int rows /* int columns = unused*/);

signals:	/* Signal 선언부 */
	void beRun ( void );
	void sortBySectionClicked ( int, Qt::SortOrder );


private:	/* Private 변수 선언부 */
	QLabel * m_pathLabel;
	QComboBox * m_pathComboBox;
	QPushButton *m_dirButton;
	QTableWidget * m_fileviewTable;

	QFileInfoList m_fileEntries;
};

#endif // FILEVIEW_H
