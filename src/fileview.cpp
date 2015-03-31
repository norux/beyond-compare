#include "fileview.h"


CFileView::CFileView()
{
	m_pathComboBox = NULL;
	m_pathLabel = NULL;
	fileviewTable = NULL;
	m_dirButton = NULL;

	initLayout ();
}

CFileView::~CFileView()
{
	/* TODO */
}

#include <QMessageBox>
void CFileView::testtesttest(QString string)
{
	QMessageBox msg;
	msg.setText(string);

	msg.exec();
}

QComboBox * CFileView::createComboBox ()
{
	QComboBox * comboBox = new QComboBox;

	assert (NULL != comboBox);

	comboBox->setEditable(true);
	comboBox->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
	comboBox->setMinimumContentsLength(1);

	connect(comboBox, SIGNAL(editTextChanged(QString)), this,  SLOT(testtesttest(QString)));
	connect(comboBox, SIGNAL(activated(QString)), this, SLOT(testtesttest(QString)));

	return comboBox;
}

QLabel * CFileView::createLabel (const QString & text)
{
	QLabel * label = new QLabel;

	assert (NULL != label);

	label->setText(text);

	return label;
}

QPushButton * CFileView::createButton ()
{
	QPushButton * pushButton = new QPushButton;

	assert (NULL != pushButton);

	pushButton->setFixedSize(30, 30);

	QPixmap icon(":/images/openFolder.png");
	pushButton->setIcon(icon);
	pushButton->setIconSize(QSize(25, 25));
	pushButton->setStyleSheet("QPushButton{border: none; outline:none;}");

	// TODO
	// connect

	return pushButton;
}

QTableWidget * CFileView::createTableWidget ()
{
	QTableWidget * tableWidget = new QTableWidget(0, 3);

	assert (NULL != tableWidget);

	QStringList labels;
	labels << tr("Filename") << tr("Size") << tr("Mod Time");

	tableWidget->setHorizontalHeaderLabels(labels);

	tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
	tableWidget->verticalHeader()->hide();
	tableWidget->setSortingEnabled(true);

	tableWidget->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);

	// TODO
	// connect ( tableWidget, SIGNAL(cellActivated(int,int)), this, SLOT(openFileOfItem(int,int))););

	return tableWidget;
}


void CFileView::initLayout ( void )
{
	m_pathComboBox = createComboBox ();
	m_pathLabel = createLabel(tr("Path"));
	fileviewTable = createTableWidget();
	m_dirButton = createButton();

	assert (NULL != m_pathComboBox);
	assert (NULL != m_pathLabel);
	assert (NULL != fileviewTable);
	assert (NULL != m_dirButton);

	addWidget(m_pathLabel, 0,0);
	addWidget(m_pathComboBox, 0, 1);
	addWidget(m_dirButton, 0, 2);

	setSpacing(10);

	addWidget(fileviewTable, 2, 0, 1, 3);
}
