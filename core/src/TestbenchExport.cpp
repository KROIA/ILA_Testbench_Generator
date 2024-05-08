#include "TestbenchExport.h"
#include "ILA_Testbench_Generator_info.h"
#include <QDebug>
#include <QFile>
#include <QDir>


namespace ILA_Testbench_Generator
{
	bool TestbenchExport::exportToVerilog(const QString& path)
	{
		size_t maxSignalCount = 0;
		for (const auto& signal : m_signals)
		{
			if (maxSignalCount < signal.getValues().size())
				maxSignalCount = signal.getValues().size();
		}
		for (const auto& signal : m_signals)
		{
			if (maxSignalCount != signal.getValues().size())
			{
				qDebug() << "Signal " << signal.getName().c_str() << " has not the same number of values as the maximum signal count";
				return false;
			}
		}

		QString filePath = path;
		// Check if the path is a directory
		QDir dir(filePath);
		if (dir.exists())
		{
			filePath += "/" + m_entityName + ".vhd";
		}
		else if(filePath.indexOf(".vhd") == -1)
			filePath += ".vhd";

		QFile file(filePath);

		if (!file.open(QIODevice::WriteOnly))
		{
			qDebug() << "Could not open file: " << filePath;
			return false;
		}

		QTextStream out(&file);

		// Header
		QString header = "-- "+QString::fromStdString(ILA_Testbench_Generator::LibraryInfo::getInfoStr());
		header.replace("\n", "\n-- ");
		out << "-- This file was generated by the ILA Testbench Generator\n";
		out << header << "\n\n";
		
		// Library
		out << "library IEEE;\n";
		out << "use IEEE.STD_LOGIC_1164.ALL;\n";
		out << "use IEEE.STD_LOGIC_ARITH.ALL;\n";

		// Entity
		out << "entity " << m_entityName << " is\n";
		out << "port (\n";
		for (size_t i=0; i<m_signals.size(); ++i)
		{
			out << "        " << getPort(m_signals[i]);
			if(i < m_signals.size()-1)
				out << ";\n";
			else
				out << "\n";
		}
		out << ");\n";
		out << "end " << m_entityName << ";\n\n";

		// Architecture
		out << "architecture Behavioral of " << m_entityName << " is\n";
		for (const auto& signal : m_signals)
		{
			out << "    " << getType(signal) << "\n";
		}
		out << "    constant ilaTickTime : time := 10ns;\n";
		out << "    constant tickCount   : natural := "<< maxSignalCount<<";\n";
		for (const auto& signal : m_signals)
		{
			out << "    " << convertToVariable(signal) << "\n";
		}
		out << "begin\n";

		/*
-- Process to generate the signal sequence
process
begin
    for i in 0 to tickCount-1 loop
        signal1 <= signal1_values(i);
        wait for ilaTickTime;
    end loop;
    wait;
end process;
		*/
		out << "    process\n";
		out << "    begin\n";
		out << "        for i in 0 to tickCount-1 loop\n";
		for (const auto& signal : m_signals)
		{
			out << "            " << getForLoopCode(signal) << "\n";
		}
		out << "            wait for ilaTickTime;\n";
		out << "        end loop;\n";
		out << "        wait;\n";
		out << "    end process;\n";

		out << "end Behavioral;\n";




		return true;
	}

	QString TestbenchExport::getPort(const IlaDataImport::Signal& sig) const
	{
		// signal signal1 : out std_logic_vector(7 downto  0)
		QString str = "signal ";
		str += sig.getName().c_str();
		str += " : out std_logic_vector(";
		str += QString::number(sig.getUpperBound());
		str += " downto ";
		str += QString::number(sig.getLowerBound());
		str += ")";
		return str;
	}
	QString TestbenchExport::getType(const IlaDataImport::Signal& sig) const
	{
		// "type SignalSequence is array (natural range <>) of std_logic_vector(7 downto 0);"
		QString str = "type ";
		str += QString::fromStdString(sig.getName()+"_type");
		str += " is array (natural range <>) of std_logic_vector(";
		str += QString::number(sig.getUpperBound());
		str += " downto ";
		str += QString::number(sig.getLowerBound());
		str += ");";
		return str;
	}
	QString TestbenchExport::convertToVariable(const IlaDataImport::Signal& sig) const
	{
		/*
			Creates a variable from the signal name
			Example:
				type SignalSequence is array (natural range <>) of std_logic_vector(7 downto 0);

				constant signal1_values : SignalSequence := (
				"00000000",
				"00000001",
				"00000010",
				"00000011");
		
		*/

		QString str = "constant ";
		str += QString::fromStdString(sig.getName() + "_values");
		str += " : ";
		str += QString::fromStdString(sig.getName() + "_type");
		str += " := (";
		for (size_t i = 0; i < sig.getValues().size(); i++)
		{
			str += "\"";
			str += QString::fromStdString(sig.getValueAsBitString(i));
			str += "\"";
			if (i != sig.getValues().size() - 1)
				str += ",\n";
		}
		str += ");";
		return str;
	}
	QString TestbenchExport::getForLoopCode(const IlaDataImport::Signal& sig) const
	{
		// signal1 <= signal1_values(i);
		QString str = sig.getName().c_str();
		str += " <= ";
		str += QString::fromStdString(sig.getName() + "_values(i);");
		return str;
	}
}