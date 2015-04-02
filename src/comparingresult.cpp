#include "comparingresult.h"

CComparingResult::CComparingResult(QWidget * parent) : QWidget (parent)
{
	m_paddingLabel = NULL;
	m_resultViewTable = NULL;

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
	tableWidget->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
	tableWidget->setDisabled(true);
	tableWidget->viewport()->setFocusPolicy(Qt::NoFocus);

	return tableWidget;
}

void CComparingResult::initLayout ( void )
{
	m_paddingLabel = createLabel("");
	m_resultViewTable = createTableWidget();

	assert (NULL != m_paddingLabel);
	assert (NULL != m_resultViewTable);


	/* 위젯 크기 고정 */
	setFixedWidth(10);

	QVBoxLayout * layout = new QVBoxLayout;
	assert (NULL != layout);

//	layout->addWidget(m_paddingLabel);
//	layout->addWidget(m_resultViewTable);

	layout->setSpacing(10);
	layout->setContentsMargins(0,0,0,0);

	setLayout(layout);
}
