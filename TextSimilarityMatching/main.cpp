#include <QtCore/QCoreApplication>
#include <QFile.h>
#include "JiabaSegment.h"

/*
 * �ο����ͣ�https://www.cnblogs.com/liangjf/p/8283519.html
 */

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);

	QString run_path = QCoreApplication::applicationDirPath();
	qDebug() << "run path:" << run_path;

	JiabaSegment* jieba = new JiabaSegment(run_path + "/dict/");
	qDebug() << jieba->WordSegment(QStringLiteral("����һ������"));

	return a.exec();
}
