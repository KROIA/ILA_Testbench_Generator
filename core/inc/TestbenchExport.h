#pragma once
#include "ILA_Testbench_Generator_base.h"

#include <vector>
#include "IlaDataImport.h"
#include <QString>

namespace ILA_Testbench_Generator
{
	class ILA_TESTBENCH_GENERATOR_EXPORT TestbenchExport
	{
	public:
		TestbenchExport() {}
		TestbenchExport(const TestbenchExport&) = delete;

		void setEntityName(const QString& entityName) { m_entityName = entityName; }
		void setSignals(const std::vector<IlaDataImport::Signal>& sigs) { m_signals = sigs; }

		bool exportToVerilog(const QString& path);
	private:

		QString getPort(const IlaDataImport::Signal& sig) const;
		QString getType(const IlaDataImport::Signal& sig) const;
		QString convertToVariable(const IlaDataImport::Signal& sig) const;
		QString getForLoopCode(const IlaDataImport::Signal& sig) const;

		QString m_entityName;
		std::vector<IlaDataImport::Signal> m_signals;

	};
}