#include "ParagraphLocate.h"

/************************************************************************
* ��ȡ��λ����ľ�̬��������ֱ�ӵ���
************************************************************************/
int ParagraphLocate::locateOutlineByArticle(JiebaSegment* jieba, const QStringList& stop_words, 
	const QString& artical, const QString& outline, int& start, int& end)
{
	// �����ı�ת����
	ParagraphLocate pl(jieba, stop_words);
	WordVector artical_vector = pl.stringToVector(artical);

	// ÿ���ֶ�ת��Ϊ����
	QStringList paras = outline.split("\n", QString::SkipEmptyParts);
	QList<WordVector> para_vectors;
	foreach (QString para, paras)
	{
		para_vectors.append(pl.stringToVector(para.trimmed()));
	}

	// ��Ƶͳ�ƣ���ȡÿ���������Ҫ��


	// ����ÿ���ֶΣ���ȡ���ƶ�����һ��
	double max_simi = 0; // ������ƶ�
	int max_simi_index = -1; // ������ƶȵ�λ��
	for (int i = 0; i < para_vectors.size(); i++)
	{
		double simi = pl.getVectorSimilarity(artical_vector, para_vectors.at(i));
		if (simi > max_simi)
		{
			max_simi = simi;
			max_simi_index = i;
		}
	}
	if (max_simi_index > -1)
	{
		QString para = paras.at(max_simi_index);
		start = outline.indexOf(para);
		end = start + para.length();
	}

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
	foreach (QString word, list)
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

/************************************************************************
 * ����������������֮������ƶ�
 ************************************************************************/
double ParagraphLocate::getVectorSimilarity(const WordVector& a, const WordVector& b)
{
	// �� a �� b ͳһ�ʰ�
	QList<int> v1, v2;
	QStringList word_orders;
	for (WordVector::const_iterator it = a.begin(); it != a.end(); it++)
	{
		v1.append(it.value());
		v2.append(b.contains(it.key()) ? b[it.key()] : 0);
		word_orders.append(it.key());
	}
	for (WordVector::const_iterator it = b.begin(); it != b.end(); it++)
	{
		if (a.contains(it.key())) // ��������Ѿ���ǰ����ֹ���
			continue;
		v1.append(0);
		v2.append(it.value());
		word_orders.append(it.key());
	}

	qDebug() << word_orders;
	qDebug() << v1;
	qDebug() << v2;

	// ������������ֵ
	int numerator = 0, denominator1 = 0, denominator2 = 0; // ���Ӻͷ�ĸ
	for (int i = 0; i < v1.size(); i++)
	{
		numerator += v1.at(i) * v2.at(i);
		denominator1 += v1.at(i) * v1.at(i);
		denominator2 += v2.at(i) * v2.at(i);
	}
	double ans = numerator / sqrt(denominator1 * denominator2);
	qDebug() << "ans:" << ans;
	qDebug() << "-------------------";

	return ans;
}

/************************************************************************
 * ����TF-IDF����Ƶ-���ĵ�Ƶ�ʣ�������������֮������ƶ�
 ************************************************************************/
double ParagraphLocate::getVectorSimilarity(WordVector a, WordVector b, const QMap<QString, double> TF)
{
	return 0.0;
}
