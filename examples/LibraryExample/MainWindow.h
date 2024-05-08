#pragma once

#include <QMainWindow>
#include "ui_MainWindow.h"
#include "RibbonImpl.h"
#include <QTimer>
#include "ILA_Testbench_Generator.h"

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = nullptr);
	~MainWindow();

private slots:
	void onLoad();
	void onSave();

	void onAction_actionVersion_triggered();

private:
	void closeEvent(QCloseEvent* event) override;

	Ui::MainWindow ui;
	RibbonImpl* m_ribbon;
	QTimer m_timer;

	QString m_loadPath;
	QString m_savePath;

	QWidget* m_infoWidget = nullptr;
};
