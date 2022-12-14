#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_main.h"

#include "Visualizer.h"

class CGUI : public QMainWindow
{
	Q_OBJECT

public:
	CGUI(int argc, char* argv[], QWidget *parent = Q_NULLPTR);
	~CGUI() override;

	void init();

private Q_SLOTS:
	void __onActionLoad();
	void __onActionRemove();
	void __onActionSave();

private:
	void __refresh();
	void __loadConfig();
	void __initWidget();
	void __connectSignal();

private:
	std::shared_ptr<Ui::CMainGUI> m_pMainGUI;
	std::shared_ptr<visualization::CVisualizer> m_pVisualizer;

	std::string m_DirectoryOpenPath;
};
