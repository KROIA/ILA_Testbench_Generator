#pragma once

#include "RibbonWidget.h"

class RibbonImpl : public RibbonWidget::Ribbon
{
	Q_OBJECT
	public:
		RibbonImpl(QWidget* parent = nullptr);


	
		struct Buttons
		{
			RibbonWidget::RibbonButton* load;
			RibbonWidget::RibbonButton* save;
		};



		Buttons& buttons() { return m_buttons;}

	private:
		Buttons m_buttons;
};