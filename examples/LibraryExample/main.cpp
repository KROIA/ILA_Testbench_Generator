#ifdef QT_ENABLED
#include <QApplication>
#include <QDebug>
#endif
#include <iostream>


#ifdef QT_WIDGETS_ENABLED
#include <QWidget>
#include "MainWindow.h"
#endif


int main(int argc, char* argv[])
{
#ifdef QT_WIDGETS_ENABLED
	QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
	QGuiApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
	QGuiApplication::setHighDpiScaleFactorRoundingPolicy(Qt::HighDpiScaleFactorRoundingPolicy::PassThrough);
#endif
#ifdef QT_ENABLED
	QApplication app(argc, argv);
#endif
	ILA_Testbench_Generator::Profiler::start();
	ILA_Testbench_Generator::LibraryInfo::printInfo();

	/*ILA_Testbench_Generator::IlaDataImport dataImport;
	dataImport.load("iladata.csv");
	ILA_Testbench_Generator::TestbenchExport testbenchExport;
	testbenchExport.setEntityName("testbenchData");
	testbenchExport.setSignals(dataImport.getSignals());
	testbenchExport.exportToVerilog("testbenchData.vhd");
	qDebug() << "Exported to testbenchData.vhd";*/

	MainWindow w;
	w.show();

#ifdef QT_WIDGETS_ENABLED
	
#endif
	int ret = 0;
#ifdef QT_ENABLED
	ret = app.exec();
#endif
	ILA_Testbench_Generator::Profiler::stop((std::string(ILA_Testbench_Generator::LibraryInfo::name)+".prof").c_str());
	return ret;
}