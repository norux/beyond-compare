#include "comparinginformation.h"

CComparingInformation::CComparingInformation()
{
	m_statusbarLabel = NULL;
	m_statusbarListView = NULL;

	initLayout();
}

CComparingInformation::~CComparingInformation()
{
	/* TODO */
}

QLabel * CComparingInformation::createLabel (const QString & text)
{
	QLabel * label = new QLabel;

	assert (NULL != label);

	label->setText(text);
	label->setFixedHeight(30);

	return label;
}

QListView * CComparingInformation::createListView ( void )
{
	QListView * listView = new QListView;

	assert (NULL != listView);

	listView->setFixedHeight(100);
	listView->setAutoScroll(true);

	return listView;
}


void CComparingInformation::initLayout( void )
{
	m_statusbarLabel = createLabel(tr("Statusbar"));
	m_statusbarListView = createListView();

	addWidget(m_statusbarLabel);
	addWidget(m_statusbarListView);
}
