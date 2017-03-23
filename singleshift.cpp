#include "singleshift.h"
#include <list>
#include <cmath>
using namespace std;

SingleShift::SingleShift(QObject *parent) : QObject(parent)
{

}

bool compare(const SingleShift::KeyValuePair &first, const SingleShift::KeyValuePair &second) {
	return first.Value < second.Value;
}

QChar** Create2DArray(int rowCount, int colCount) {
	QChar** arr = new QChar*[rowCount];

	for (int i = 0; i < rowCount; ++i)
		arr[i] = new QChar[colCount];

	return arr;
}

QString SingleShift::PadRight(QString str, int max, QChar padChar) {
	int strLen = str.length();

	if (strLen < max) {
		int padLen = max - strLen;
		for (int i = 0; i < padLen; ++i) str += padChar;
	}

	return str;
}

int* SingleShift::GetShiftIndexes(QString key)
{
	int keyLength = key.length();
	int* indexes = new int[keyLength];
	list<KeyValuePair> sortedKey;
	int i;

	for (i = 0; i < keyLength; ++i)
		sortedKey.push_back(KeyValuePair{ i, key[i] });

	sortedKey.sort(compare);
	i = 0;

	for (auto pair : sortedKey) {
		indexes[pair.Key] = i;
		++i;
	}

	return indexes;
}

QString SingleShift::encrypt(QString input, QChar padChar)
{
	QString output = "";
	int totalChars = input.size();
	int keyLength = key.size();
	input = (totalChars % keyLength == 0) ? input : PadRight(input, totalChars - (totalChars % keyLength) + keyLength, padChar);
	totalChars = input.length();
	int totalColumns = keyLength;
	int totalRows = (int)ceil((double)totalChars / totalColumns);
	QChar** rowChars = Create2DArray(totalRows, totalColumns);
	QChar** colChars = Create2DArray(totalColumns, totalRows);
	QChar** sortedColChars = Create2DArray(totalColumns, totalRows);
	int currentRow, currentColumn, i, j;
	int* shiftIndexes = GetShiftIndexes(key);

	for (i = 0; i < totalChars; ++i)
	{
		currentRow = i / totalColumns;
		currentColumn = i % totalColumns;
		rowChars[currentRow][currentColumn] = input[i];
	}

	for (i = 0; i < totalRows; ++i)
		for (j = 0; j < totalColumns; ++j)
			colChars[j][i] = rowChars[i][j];

	for (i = 0; i < totalColumns; ++i)
		for (j = 0; j < totalRows; ++j)
			sortedColChars[shiftIndexes[i]][j] = colChars[i][j];

	for (i = 0; i < totalChars; ++i)
	{
		currentRow = i / totalRows;
		currentColumn = i % totalRows;
		output += sortedColChars[currentRow][currentColumn];
	}

	return output;
}

QString SingleShift::decrypt(QString input)
{
	QString output;
	int keyLength = key.length();
	int totalChars = input.length();
	int totalColumns = (int)ceil((double)totalChars / keyLength);
	int totalRows = keyLength;
	QChar** rowChars = Create2DArray(totalRows, totalColumns);
	QChar** colChars = Create2DArray(totalColumns, totalRows);
	QChar** unsortedColChars = Create2DArray(totalColumns, totalRows);
	int currentRow, currentColumn, i, j;
	int* shiftIndexes = GetShiftIndexes(key);
	for (i = 0; i < totalChars; ++i)
	{
		currentRow = i / totalColumns;
		currentColumn = i % totalColumns;
		rowChars[currentRow][currentColumn] = input[i];
	}

	for (i = 0; i < totalRows; ++i)
		for (j = 0; j < totalColumns; ++j)
			colChars[j][i] = rowChars[i][j];

	for (i = 0; i < totalColumns; ++i)
		for (j = 0; j < totalRows; ++j)
			unsortedColChars[i][j] = colChars[i][shiftIndexes[j]];

	for (i = 0; i < totalChars; ++i)
	{
		currentRow = i / totalRows;
		currentColumn = i % totalRows;
		output += unsortedColChars[currentRow][currentColumn];
	}

	return output;
}

SingleShift::~SingleShift()
{

}

void SingleShift::setKey(QString k)
{
 key = k;
}
