#include "comparingresult.h"

CComparingResult::CComparingResult()
{
	m_paddingLabel = NULL;
	m_resultViewTable = NULL;

	initLayout ();
}

CComparingResult::~CComparingResult()
{
	/* TODO */
}

QLabel * CComparingResult::createLabel (const QString & text)
{
	QLabel * label = new QLabel;

	assert (NULL != label);

	label->setText(text);
	label->setMinimumHeight(30);

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

	tableWidget->setMaximumWidth(30);

	return tableWidget;
}

void CComparingResult::initLayout ( void )
{
	m_paddingLabel = createLabel("");
	m_resultViewTable = createTableWidget();

	assert (NULL != m_paddingLabel);
	assert (NULL != m_resultViewTable);

	addWidget(m_paddingLabel);
	addWidget(m_resultViewTable);

	setSpacing(10);
}
