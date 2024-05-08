#include "IlaDataImport.h"
#include <QFile>
#include <QDebug>
#include <QTextStream>
#include <QString>
#include <QStringList>
#include <QRegExp>



namespace ILA_Testbench_Generator
{
	std::string IlaDataImport::Signal::getValueAsBitString(size_t index) const
	{
		std::string result(m_upperBound - m_lowerBound + 1, '0');
		if (index < m_values.size())
		{
			unsigned long long value = m_values[index];
			for (size_t i = 0; i < m_upperBound - m_lowerBound + 1; i++)
			{
				result[m_upperBound - m_lowerBound - i] = (value & 1) ? '1' : '0';
				value >>= 1;
			}
		}
		return result;
	}

	IlaDataImport::IlaDataImport()
	{

	}

	bool IlaDataImport::load(const std::string& filename)
	{
		// Read csv file line by line and save it to a vector of std::strings
		QFile file(QString::fromStdString(filename));
		if (!file.open(QIODevice::ReadOnly))
		{
			qDebug() << "Could not open file: " << filename.c_str();
			return false;
		}

		std::vector<Signal> readingSignals;
		QTextStream in(&file);
		int sinnalCount = 0;
		size_t lineIndex = -1;

		int signalStartColumn = 3;
		while (!in.atEnd())
		{
			lineIndex++;
			QString line = in.readLine();
			QStringList fields = line.split(",");

			if (fields.size() == 0)
			{
				qDebug() << "Invalid line: " << line;
				continue;
			}
			if (lineIndex == 0)
			{
				sinnalCount = fields.size() - signalStartColumn;
				// Regexp to match for 2 parameters in String "SignalName[31:0]"
				QRegExp rx("([a-zA-Z0-9_]+)\\[(\\d+):(\\d+)\\]");

				for (int i = signalStartColumn; i < fields.size(); i++)
				{
					Signal signal;
					QString signalName = fields[i];
					if (rx.indexIn(signalName) != -1)
					{
						signal.setName(rx.cap(1).toStdString());
						signal.setUpperBound(rx.cap(2).toUInt());
						signal.setLowerBound(rx.cap(3).toUInt());
					}
					else
					{
						qDebug() << "Invalid signal name: " << signalName;
						continue;
					}
					readingSignals.push_back(signal);
				}
				continue;
			}
			else if (lineIndex == 1)
				continue;

			// Read values
			for (int i = signalStartColumn; i < fields.size(); i++)
			{
				Signal& signal = readingSignals[i - signalStartColumn];
				// Read the value which is in hex format like "15c"
				QString value = fields[i];
				bool ok;
				unsigned long long valueInt = value.toULongLong(&ok, 16);
				if (!ok)
				{
					qDebug() << "Invalid value: " << value;
					continue;
				}
				signal.addValue(valueInt);
			}
		}
		m_signals = readingSignals;
		return true;
	}
}