#include "layermanagercontrol.h"

#include "layers/occLayer.h"

#include <QRadioButton>
#include <QVBoxLayout>

LayerManagerControl::LayerManagerControl(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	initConnection();
}

LayerManagerControl::~LayerManagerControl()
{

}

void LayerManagerControl::setLayers(const QVector<occLayer*>& layers)
{
	layers_ = layers;
}

void LayerManagerControl::loadLayers()
{
	QVBoxLayout* activeLayout = new QVBoxLayout();
	ui.activeArea->setLayout(activeLayout);

	for (const auto& layer : layers_)
	{
		QHBoxLayout* lineItem = new QHBoxLayout();
		QLabel* label = new QLabel(layer->getName());
		QRadioButton* btn = new QRadioButton();

		connect(btn, &QPushButton::clicked, [this, layer]() 
		{
			selectedLayer_ = layer;
		});
		lineItem->addWidget(label);
		lineItem->addWidget(btn);
		activeLayout->addLayout(lineItem);
	}
}

void LayerManagerControl::confirmBtnclicked()
{
	if (currentBtnState_ == ButtonState::Confirm)
	{
		currentBtnState_ = ButtonState::Return;
		ui.btn_confirm->setText("返回");

		//1 卸载当前ActiveArea的控件
		clearActiveArea();
		//2 根据当前选择的TestLayer，进行切换控制面板

		//3 attach对应功能
		if(selectedLayer_)
			selectedLayer_->attach();
	}
	else
	{
		currentBtnState_ = ButtonState::Confirm;
		ui.btn_confirm->setText("确认");

		//返回可选的TestLayer窗口
		if (selectedLayer_)
			selectedLayer_->detach();
		selectedLayer_ = nullptr;
		loadLayers();
	}
}

void LayerManagerControl::clearActiveArea()
{
	
}

void LayerManagerControl::initConnection()
{
	connect(ui.btn_confirm, &QPushButton::clicked, this, &LayerManagerControl::confirmBtnclicked);
}

