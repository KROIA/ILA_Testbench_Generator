#include "MainWindow.h"
#include <QFileDialog>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	m_ribbon = new RibbonImpl(ui.ribbon_widget);
	setWindowTitle("ILA Testbench Generator");
	//
	//ui.pushButton->setIcon(RibbonWidget::DefaultIconLoader::getIcon(":/icons/arrowCClockwise.png"));
	////ui.pushButton->setIcon(QIcon(":/icons/live_folder_2.png"));
	//
	//auto buttons = m_ribbon->workButtons();
	//connect(buttons.open, &QToolButton::clicked, this, &MainWindow::onOpenClicked);
	//connect(buttons.save, &QToolButton::clicked, this, &MainWindow::onSaveClicked);
	//
	//connect(&m_timer, &QTimer::timeout, this, &MainWindow::onTimerFinished);
	//m_timer.start(50);

	auto buttons = m_ribbon->buttons();
	connect(buttons.load, &QToolButton::clicked, this, &MainWindow::onLoad);
	connect(buttons.save, &QToolButton::clicked, this, &MainWindow::onSave);


	connect(ui.actionVersion, &QAction::triggered, this, &MainWindow::onAction_actionVersion_triggered);

}

MainWindow::~MainWindow()
{
	if (m_infoWidget)
	{
		m_infoWidget->close();
		delete m_infoWidget;
	}
	delete m_ribbon;
}

void MainWindow::onLoad()
{
	m_loadPath = QFileDialog::getOpenFileName(this, tr("Open a CSV file, exported from the ILA Logic analyzer"), "", tr("Files (*.csv)"));
}
void MainWindow::onSave()
{
	m_savePath = QFileDialog::getSaveFileName(this, tr("Save testbench signal generator block"), "", tr("Files (*.*)"));
	if(m_savePath.isEmpty())
		return;
	ILA_Testbench_Generator::IlaDataImport dataImport;
	dataImport.load(m_loadPath.toStdString());
	ILA_Testbench_Generator::TestbenchExport testbenchExport;
	testbenchExport.setEntityName(ui.entityName_lineEdit->text());
	testbenchExport.setSignals(dataImport.getSignals());
	testbenchExport.exportToVerilog(m_savePath);
	qDebug() << "Exported to "<< m_savePath;
}
void MainWindow::onAction_actionVersion_triggered()
{
	if(!m_infoWidget)
		m_infoWidget = ILA_Testbench_Generator::LibraryInfo::createInfoWidget();
	if(m_infoWidget)
		m_infoWidget->show();
}

void MainWindow::closeEvent(QCloseEvent* event)
{
	if(m_infoWidget)
		m_infoWidget->close();
	QMainWindow::closeEvent(event);
}