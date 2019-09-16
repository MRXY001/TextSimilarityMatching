#include "ParagraphLocate.h"

/************************************************************************
* ��ȡ��λ����ľ�̬��������ֱ�ӵ���
************************************************************************/
int ParagraphLocate::locateOutlineByArticle(JiebaSegment* jieba, const QStringList& stop_words,
	const QString& artical, const QString& outline, int& start, int& ends)
{
	ParagraphLocate pl(jieba, stop_words);
	WordVector artical_vector = pl.stringToVector(artical);
	QStringList paras = outline.split("\n", QString::SkipEmptyParts);


	return 0;
}

/************************************************************************
* ���캯��
************************************************************************/
ParagraphLocate::ParagraphLocate(JiebaSegment*& jieba, const QStringList& stop_words) :
	jieba(jieba), stop_words(stop_words)
{
}

/************************************************************************
* ���ַ���ת���ɴ������
************************************************************************/
QStringList ParagraphLocate::stringToArray(const QString& text)
{
	QStringList words = jieba->WordSegment(text);
	for (int i = 0; i < words.size(); i++) // �����½ڴ����ÿһ��
	{
		if (stop_words.contains(words.at(i)))
		{
			words.removeAt(i--);
		}
	}
	return words;
}

/************************************************************************
* ���ַ���ת���ɴ�������
* map ��ʽ��["����" => ���ִ���]
************************************************************************/
WordVector ParagraphLocate::stringToVector(const QString& text)
{
	WordVector map;
	WordVector::iterator it;
	QStringList list = stringToArray(text);
	for each (QString word in list)
	{
		if ((it = map.find(word)) != map.end()) // ������������ڣ�ֵ+1
		{
			(*it)++;
		}
		else // ���������ﲻ���ڣ���Ӳ�����ֵΪ1
		{
			map.insert(word, 1);
		}
	}

	return map;
}