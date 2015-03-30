#include "comparinginformation.h"

CComparingInformation::CComparingInformation(QWidget * parent) : QWidget (parent)
{
	m_statusbarLabel = NULL;
	m_statusbarListWidget = NULL;

	initLayout();
}

CComparingInformation::~CComparingInformation()
{
	if (NULL != m_statusbarLabel)
	{
		delete m_statusbarLabel;
		m_statusbarLabel = NULL;
	}
	if (NULL != m_statusbarListWidget)
	{
		delete m_statusbarListWidget;
		m_statusbarListWidget = NULL;
	}
}

QLabel * CComparingInformation::createLabel (const QString & text)
{
	QLabel * label = new QLabel;

	assert (NULL != label);

	label->setText(text);
	label->setFixedHeight(30);
	label->setAlignment(Qt::AlignBottom);

	return label;
}

QListWidget * CComparingInformation::createListWidget ( void )
{
	QListWidget * listWidget = new QListWidget;

	assert (NULL != listWidget);

	listWidget->setAutoScroll(true);
	listWidget->setFocusPolicy(Qt::NoFocus);

	return listWidget;
}

void CComparingInformation::initLayout( void )
{
	m_statusbarLabel = createLabel(tr("Statusbar"));
	m_statusbarListWidget = createListWidget();

	assert (NULL != m_statusbarLabel);
	assert (NULL != m_statusbarListWidget);


	/* 위젯 크기 고정 */
	setFixedHeight(130);

	QVBoxLayout * layout = new QVBoxLayout;

	layout->addWidget(m_statusbarLabel);
	layout->addWidget(m_statusbarListWidget);

	layout->setContentsMargins(0,0,0,0);

	setLayout(layout);
}

void CComparingInformation::addStatusbarListItem (const QString& strItem)
{
	assert (NULL != m_statusbarListWidget);
	assert (0 != strItem.length());

	m_statusbarListWidget->addItem(strItem);
	m_statusbarListWidget->scrollToBottom();
}
