#include "ui.h"

UI::UI(Mechanics *mech, QWidget *parent)
    : QWidget(parent)
{
    mechanics = mech;

    //-----------------------Buttons-----------------------
    graphButton = new QPushButton(tr("Graph"));
    browseButton = new QPushButton(tr("Browse"));

    //---------------------TableWidget---------------------
    tableWidget = new QTableWidget(3,14);
        //в таблице из методички 14 столбцов, посему так
        //а ещё я пока хз, как убрать цифры 1,2,3 и.т.д. сверху
    QStringList verticalHeaders;
    verticalHeaders << "m" << "φ0" << "φ1" ;
    tableWidget->setVerticalHeaderLabels(verticalHeaders);
    tableWidget->setFixedHeight(143); //высоту вывел эмпирически

    //-----------------------Labels------------------------
    dLabel = new QLabel("d=");
    lLabel = new QLabel("λ=");
    nLabel = new QLabel("n=");

    //------------------QDoubleSpinBoxies------------------
    dSpinBox = new QDoubleSpinBox();
    lSpinBox = new QDoubleSpinBox();
    nLineEdit = new QLineEdit();

    dSpinBox->setDecimals(3);
    dSpinBox->setValue(0.5);
    lSpinBox->setDecimals(3);
    lSpinBox->setValue(0.651);
    nLineEdit->setReadOnly(true);

    //-----------------------Layouts-----------------------
    dLayout = new QHBoxLayout();
    dLayout->addWidget(dLabel);
    dLayout->addWidget(dSpinBox);

    lLayout = new QHBoxLayout();
    lLayout->addWidget(lLabel);
    lLayout->addWidget(lSpinBox);

    nLayout = new QHBoxLayout();
    nLayout->addWidget(nLabel);
    nLayout->addWidget(nLineEdit);

    dataLayout = new QVBoxLayout();
    dataLayout->addWidget(tableWidget);
    dataLayout->addLayout(dLayout);
    dataLayout->addLayout(lLayout);
    dataLayout->addLayout(nLayout);
    dataLayout->addWidget(browseButton);
    dataLayout->addWidget(graphButton);

    mainLayout = new QHBoxLayout();
    mainLayout->addWidget(mechanics);
    mainLayout->addLayout(dataLayout);
    setLayout(mainLayout);
}

UI::~UI()
{
    delete graphButton, browseButton;
    delete tableWidget;
    delete nLabel, lLabel, dLabel;
    delete dSpinBox, lSpinBox;
    delete nLineEdit;
    delete dLayout, lLayout, nLayout, dataLayout, mainLayout;
    delete mechanics;
}
