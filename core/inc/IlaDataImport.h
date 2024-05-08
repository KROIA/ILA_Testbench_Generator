#pragma once
#include "ILA_Testbench_Generator_base.h"

#include <vector>
#include <string>

namespace ILA_Testbench_Generator
{
	class ILA_TESTBENCH_GENERATOR_EXPORT IlaDataImport
	{
	public:
		class ILA_TESTBENCH_GENERATOR_EXPORT Signal
		{
		public:
			Signal()
				: m_upperBound(0)
				, m_lowerBound(0)
			{}

			void setName(const std::string& name){ m_name = name;}
			const std::string& getName() const{ return m_name; }

			void setUpperBound(unsigned int upperBound){ m_upperBound = upperBound; }
			unsigned int getUpperBound() const{ return m_upperBound; }

			void setLowerBound(unsigned int lowerBound){ m_lowerBound = lowerBound; }
			unsigned int getLowerBound() const{ return m_lowerBound; }

			void setValues(const std::vector<unsigned long long>& values){ m_values = values; }
			const std::vector<unsigned long long>& getValues() const{ return m_values; }

			void addValue(unsigned long long value){ m_values.push_back(value); }
			void clearValues(){ m_values.clear(); }
			void reserveValues(size_t size){ m_values.reserve(size); }

			std::string getValueAsBitString(size_t index) const;

		private:
			std::string m_name;
			unsigned int m_upperBound;
			unsigned int m_lowerBound;
			std::vector<unsigned long long> m_values;
		};

		IlaDataImport();
		IlaDataImport(const IlaDataImport&) = delete;

		void addSignal(const Signal& signal){ m_signals.push_back(signal); }
		const std::vector<Signal>& getSignals() const{ return m_signals; }
		void clearSignals(){ m_signals.clear(); }
		void reserveSignals(size_t size){ m_signals.reserve(size); }

		bool load(const std::string& filename);


	private:

		std::vector<Signal> m_signals;
	};
}