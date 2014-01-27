#include "ui.h"

UI::UI(QWidget *parent)
    : QWidget(parent)
{
    mechanics = new Mechanics();

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
    for(int row = 0;row < 3; row++)
        for(int column = 0; column < 14; column++)
            tableWidget->setItem(row, column, new QTableWidgetItem("0.0"));

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

    //---------------------Connections---------------------
    connect(graphButton, SIGNAL(clicked()), this, SLOT(prepareToGraph()));
    connect(this,SIGNAL(graph(double**)), mechanics, SLOT(graph(double**)));
}

//---------------------------------------------------------

UI::~UI()
{
    delete mechanics;
    delete graphButton, browseButton;
    delete tableWidget;
    delete nLabel, lLabel, dLabel;
    delete dSpinBox, lSpinBox;
    delete nLineEdit;
    delete dLayout, lLayout, nLayout, dataLayout, mainLayout;
}

//---------------------------------------------------------

void UI::prepareToGraph()
{
    qreal **array = new qreal*[3];
    for(int i = 0; i < 3; i++)
        array[i] = new qreal[14];

    for(int row = 0; row < 3; row++)
        for(int column = 0; column < 14; column++)
            if (tableWidget->item(row, column)->text().isEmpty())
                array[row][column] = 0;
            else
                array[row][column] = tableWidget->item(row, column)->text().toDouble();
    graph(array);
}
