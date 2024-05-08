#include "RibbonImpl.h"


RibbonImpl::RibbonImpl(QWidget* parent)
	: RibbonWidget::Ribbon(parent)
{
	Q_INIT_RESOURCE(RibbonIcons); // Init the resource file
	// Create tabs
	RibbonWidget::RibbonTab* tabMain	= new RibbonWidget::RibbonTab("Main", "", this);

	// Create groups
	RibbonWidget::RibbonButtonGroup* groupMain	= new RibbonWidget::RibbonButtonGroup("Converter", tabMain);


	// Create buttons
	m_buttons.load = new RibbonWidget::RibbonButton("Load", "Load", ":/icons/live_folder_2.png", true, groupMain);
	m_buttons.save = new RibbonWidget::RibbonButton("Export", "Export to vhd block", ":/icons/floppy_disk.png", true, groupMain);



	// Add tabs
	addTab(tabMain);
}
