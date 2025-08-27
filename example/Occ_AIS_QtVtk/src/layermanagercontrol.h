#pragma once

#include <QWidget>
#include "ui_layermanagercontrol.h"
#include <QVector>

class occLayer;

class LayerManagerControl : public QWidget
{
	Q_OBJECT

public:
	LayerManagerControl(QWidget *parent = nullptr);
	~LayerManagerControl();

	void setLayers(const QVector<occLayer*>& layers);
	void loadLayers();
private:
	void confirmBtnclicked();

	void clearActiveArea();
private:
	void initConnection();

private:
	Ui::LayerManagerControlClass ui;
	enum class ButtonState
	{
		Confirm,
		Return
	};
	ButtonState currentBtnState_ = ButtonState::Confirm;
	QVector<occLayer*> layers_;
	occLayer* selectedLayer_{};
};

