#include "ui.h"
#include "qmath.h"

UI::UI(QWidget *parent)
    : QWidget(parent)
{
    mechanics = new Mechanics();

    //-----------------------Buttons-----------------------
    graphButton = new QPushButton(tr("Найти n"));
    browseButton = new QPushButton(tr("Из файла"));
    aboutButton = new QPushButton(tr("О программе"));
    aboutButton->setDisabled(true);
    graphButton->setMaximumWidth(233);
    browseButton->setMaximumWidth(233);

    //---------------------TableWidget---------------------
    tableWidget = new QTableWidget(3,14);
        //в таблице из методички 14 столбцов, посему так
    tableWidget->horizontalHeader()->hide();
    QStringList verticalHeaders;
    verticalHeaders << "m" << "φ0" << "φ1" ;
    tableWidget->setVerticalHeaderLabels(verticalHeaders);
    tableWidget->setFixedHeight(113); //величины вывел эмпирически
    tableWidget->setFixedWidth(233);

    for(int row = 0;row < 3; row++)
        for(int column = 0; column < 14; column++)
            tableWidget->setItem(row, column, new QTableWidgetItem("0.0"));

    //-----------------------Labels------------------------
    dLabel = new QLabel("d=");
    d2Label = new QLabel(tr("(мм)"));
    lLabel = new QLabel("λ=");
    l2Label = new QLabel(tr("(мкм)"));
    nLabel = new QLabel("n=");

    //---------------------VariablesIO---------------------
    dSpinBox = new QDoubleSpinBox();
    lSpinBox = new QDoubleSpinBox();
    nLineEdit = new QLineEdit();

    dSpinBox->setDecimals(3);
    dSpinBox->setSingleStep(0.1);
    dSpinBox->setValue(mechanics->getD());

    lSpinBox->setDecimals(3);
    lSpinBox->setSingleStep(0.001);
    lSpinBox->setValue(mechanics->getL());

    nLineEdit->setReadOnly(true);

    //-----------------------Layouts-----------------------
    dLayout = new QHBoxLayout();
    dLayout->addWidget(dLabel);
    dLayout->addWidget(dSpinBox);
    dLayout->addWidget(d2Label);
    dLayout->setAlignment(Qt::AlignLeft);

    lLayout = new QHBoxLayout();
    lLayout->addWidget(lLabel);
    lLayout->addWidget(lSpinBox);
    lLayout->addWidget(l2Label);
    lLayout->setAlignment(Qt::AlignLeft);

    nLayout = new QHBoxLayout();
    nLayout->addWidget(nLabel);
    nLayout->addWidget(nLineEdit);
    nLayout->setAlignment(Qt::AlignLeft);

    dataLayout = new QVBoxLayout();
    dataLayout->addWidget(tableWidget);
    dataLayout->addLayout(dLayout);
    dataLayout->addLayout(lLayout);
    dataLayout->addLayout(nLayout);
    dataLayout->addWidget(browseButton);
    dataLayout->addWidget(graphButton);
    dataLayout->addWidget(aboutButton);

    mainLayout = new QHBoxLayout();
    mainLayout->addWidget(mechanics);
    mainLayout->addLayout(dataLayout);
    setLayout(mainLayout);

    //---------------------Connections---------------------
    connect(graphButton, SIGNAL(clicked()), mechanics, SLOT(graph()));
    connect(browseButton, SIGNAL(clicked()), this, SLOT(browse()));
    //connect(this, SIGNAL(graph(qreal**)), mechanics, SLOT(graph(qreal**)));
    connect(dSpinBox, SIGNAL(valueChanged(double)), mechanics, SLOT(setD(qreal)));
    connect(lSpinBox, SIGNAL(valueChanged(double)), mechanics, SLOT(setL(qreal)));
    connect(tableWidget, SIGNAL(cellChanged(int, int)), this, SLOT(prepareToGraph(int, int)));
    connect(this, SIGNAL(dataFromTable(int,int,qreal)), mechanics, SLOT(setDataToArray(int,int,qreal)));
}

//---------------------------------------------------------

UI::~UI()
{
    delete mechanics;
    delete graphButton, browseButton, aboutButton;
    delete tableWidget;
    delete nLabel, lLabel, dLabel, l2Label, d2Label;
    delete dSpinBox, lSpinBox;
    delete nLineEdit;
    delete dLayout, lLayout, nLayout, dataLayout, mainLayout;
}

//---------------------------------------------------------

void UI::prepareToGraph(int row, int column)
{
    bool ok;
    qreal data = tableWidget->item(row, column)->text().toDouble(&ok);
    if (ok)
        emit dataFromTable(row, column, data);
}

//---------------------------------------------------------

void UI::browse()
{
    QString path = QFileDialog::getOpenFileName();
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
            return;
    while (!file.atEnd())
    {
        QByteArray line = file.readLine();
    }

}

//---------------------------------------------------------
