#include "ui.h"

UI::UI(QWidget *parent)
    : QWidget(parent)
{
    mechanics = new Mechanics();

    //-----------------------Buttons-----------------------
    graphButton = new QPushButton(tr("Graph"));
    browseButton = new QPushButton(tr("Browse"));
    browseButton->setDisabled(true);

    //---------------------TableWidget---------------------
    tableWidget = new QTableWidget(2,14);
        //в таблице из методички 14 столбцов, посему так
    tableWidget->horizontalHeader()->hide();
    QStringList verticalHeaders;
    verticalHeaders << "m" << "φ1" ;
    tableWidget->setVerticalHeaderLabels(verticalHeaders);
    tableWidget->setFixedHeight(83); //величины вывел эмпирически
    tableWidget->setFixedWidth(233);

    for(int row = 0;row < 2; row++)
        for(int column = 0; column < 14; column++)
            tableWidget->setItem(row, column, new QTableWidgetItem("0.0"));

    //-----------------------Labels------------------------
    dLabel = new QLabel("d=");
    lLabel = new QLabel("λ=");
    nLabel = new QLabel("n=");
    fi0Label = new QLabel("φ<sub>0</sub>=");

    //---------------------VariablesIO---------------------
    dSpinBox = new QDoubleSpinBox();
    lSpinBox = new QDoubleSpinBox();
    fi0SpinBox = new QDoubleSpinBox();
    nLineEdit = new QLineEdit();

    dSpinBox->setDecimals(3);
    dSpinBox->setSingleStep(0.1);
    dSpinBox->setValue(mechanics->getD());

    lSpinBox->setDecimals(3);
    lSpinBox->setSingleStep(0.001);
    lSpinBox->setValue(mechanics->getL());

    fi0SpinBox->setDecimals(3);
    fi0SpinBox->setSingleStep(0.1);
    fi0SpinBox->setValue(mechanics->getFi0());

    nLineEdit->setReadOnly(true);

    //-----------------------Layouts-----------------------
    dLayout = new QHBoxLayout();
    dLayout->addWidget(dLabel);
    dLayout->addWidget(dSpinBox);
    dLayout->addSpacing(150);

    lLayout = new QHBoxLayout();
    lLayout->addWidget(lLabel);
    lLayout->addWidget(lSpinBox);
    lLayout->addSpacing(150);

    fi0Layout = new QHBoxLayout();
    fi0Layout->addWidget(fi0Label);
    fi0Layout->addWidget(fi0SpinBox);
    fi0Layout->addSpacing(150);

    nLayout = new QHBoxLayout();
    nLayout->addWidget(nLabel);
    nLayout->addWidget(nLineEdit);
    nLayout->addSpacing(150);

    dataLayout = new QVBoxLayout();
    dataLayout->addWidget(tableWidget);
    dataLayout->addLayout(dLayout);
    dataLayout->addLayout(lLayout);
    dataLayout->addLayout(fi0Layout);
    dataLayout->addLayout(nLayout);
    dataLayout->addWidget(browseButton);
    dataLayout->addWidget(graphButton);

    mainLayout = new QHBoxLayout();
    mainLayout->addWidget(mechanics);
    mainLayout->addLayout(dataLayout);
    setLayout(mainLayout);

    //---------------------Connections---------------------
    connect(graphButton, SIGNAL(clicked()), this, SLOT(prepareToGraph()));
    connect(this,SIGNAL(graph(qreal**)), mechanics, SLOT(graph(qreal**)));
    connect(dSpinBox,SIGNAL(valueChanged(double)), mechanics, SLOT(setD(qreal)));
    connect(lSpinBox,SIGNAL(valueChanged(double)), mechanics, SLOT(setL(qreal)));
    connect(fi0SpinBox,SIGNAL(valueChanged(double)), mechanics, SLOT(setFi0(qreal)));
}

//---------------------------------------------------------

UI::~UI()
{
    delete mechanics;
    delete graphButton, browseButton;
    delete tableWidget;
    delete nLabel, lLabel, dLabel, fi0Label;
    delete dSpinBox, lSpinBox, fi0SpinBox;
    delete nLineEdit;
    delete dLayout, lLayout, fi0Layout, nLayout, dataLayout, mainLayout;
}

//---------------------------------------------------------

void UI::prepareToGraph()
{
    qreal **array = new qreal*[2];
    for(int i = 0; i < 2; i++)
        array[i] = new qreal[14];

    for(int row = 0; row < 2; row++)
        for(int column = 0; column < 14; column++)
            if (tableWidget->item(row, column)->text().isEmpty())
                array[row][column] = 0;
            else
                array[row][column] = tableWidget->item(row, column)->text().toDouble();

    emit graph(array);
}
