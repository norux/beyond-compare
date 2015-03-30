#include "comparingresult.h"

CComparingResult::CComparingResult(QWidget * parent) : QWidget (parent)
{
	m_paddingLabel = NULL;
	m_resultViewTable = NULL;

	m_copyToRightButton = NULL;

	initLayout ();
}

CComparingResult::~CComparingResult()
{
	if(NULL != m_paddingLabel)
	{
		delete m_paddingLabel;
		m_paddingLabel = NULL;
	}
	if(NULL != m_resultViewTable)
	{
		delete m_resultViewTable;
		m_resultViewTable = NULL;
	}
	if(NULL != m_copyToRightButton)
	{
		delete m_copyToRightButton;
		m_copyToRightButton = NULL;
	}
}

QLabel * CComparingResult::createLabel (const QString & text)
{
	QLabel * label = new QLabel;

	assert (NULL != label);

	label->setText(text);
	label->setFixedHeight(30);

	return label;
}

QTableWidget * CComparingResult::createTableWidget ()
{
	QTableWidget * tableWidget = new QTableWidget (0, 1);

	assert (NULL != tableWidget);

	QStringList labels;
	labels << "";

	tableWidget->setHorizontalHeaderLabels(labels);

// Qt version 5.4
	tableWidget->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);

// Qt version 4.8
//	tableWidget->horizontalHeader()->setResizeMode(0, QHeaderView::Stretch);

	tableWidget->setDisabled(true);
	tableWidget->viewport()->setFocusPolicy(Qt::NoFocus);

	return tableWidget;
}


QPushButton * CComparingResult::createButton (const QString &strImage, const char * slot) const
{
	QPushButton * pushButton = new QPushButton;

	assert (NULL != pushButton);
	assert (NULL != slot);

	QPixmap icon(strImage);
	pushButton->setIcon(icon);
	pushButton->setIconSize(QSize(25,25));
	pushButton->setStyleSheet("QPushButton{border: none; outline:none;}");
	pushButton->setFocusPolicy(Qt::NoFocus);

	pushButton->setFixedSize(30, 30);


	if (NULL != slot)
	{
		connect (pushButton, SIGNAL(clicked()), this, slot);
	}

	return pushButton;
}

void CComparingResult::slotCopyButtonClicked ( void )
{
	emit copyButtonClicked ();
}

void CComparingResult::initLayout ( void )
{
	m_paddingLabel = createLabel("");
	m_resultViewTable = createTableWidget();
	m_copyToRightButton = createButton(":/images/copy.png", SLOT(slotCopyButtonClicked()));

	assert (NULL != m_paddingLabel);
	assert (NULL != m_resultViewTable);
	assert (NULL != m_copyToRightButton);


	/* 위젯 크기 고정 */
//	setFixedWidth(50);

	QVBoxLayout * layout = new QVBoxLayout;
	assert (NULL != layout);

//	layout->addWidget(m_paddingLabel);
//	layout->addWidget(m_resultViewTable);
	layout->addWidget(m_copyToRightButton);
	layout->addStretch(1);

	layout->setSpacing(10);
	layout->setContentsMargins(0,0,0,0);

	setLayout(layout);
}
