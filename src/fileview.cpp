#include "fileview.h"
#include <QLabel>
#include <QLayout>

CFileView::CFileView()
{
	QLabel *label = new QLabel;

	label->setText(tr("test"));

	addWidget(label, 0,0, Qt::AlignTop);

}

CFileView::~CFileView()
{
	/* TODO */
}

