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

    //---------------------TableWidget---------------------
    tableWidget = new QTableWidget(3,14);
        //в таблице из методички 14 столбцов, посему так
    tableWidget->horizontalHeader()->hide();
    QStringList verticalHeaders;
    verticalHeaders << "m" << "φ0" << "φ1" ;
    tableWidget->setVerticalHeaderLabels(verticalHeaders);
    tableWidget->setFixedHeight(92); //величины вывел эмпирически
    tableWidget->setFixedWidth(732);


    for(int column = 0; column < 14; column++)
    {
        for(int row = 0;row < 3; row++)
            tableWidget->setItem(row, column, new QTableWidgetItem("0.0"));
        tableWidget->setColumnWidth(column,50);
    }

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

    //----------------------aboutBox-----------------------
    aboutBox = new QMessageBox();
    aboutBox->setWindowTitle(tr("О программе"));
    aboutBox->setStandardButtons(QMessageBox::Ok);
    aboutBox->setText(tr("Программа, выполняющая лабораторную работу №2 \"Определение показателя преломления "
                         "интерферомическим методом\" из учебного пособия \"ОПТИКА. ФИЗИЧЕСКИЙ ПРАКТИКУМ\""
                         " (авторы А.В. Михельсон, Т.И.Папушина, А.А.Повзнер)"));

    //----------------------errorBox-----------------------
    errorBox = new QMessageBox();
    errorBox->setWindowTitle(tr("Ошибка"));
    aboutBox->setStandardButtons(QMessageBox::Ok);
    aboutBox->setText(tr("Вы не должны были увидеть эту ошибку. Мне очень жаль"));

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

    dataLayout = new QHBoxLayout();
    dataLayout->addLayout(dLayout);
    dataLayout->addLayout(lLayout);
    dataLayout->addLayout(nLayout);
    dataLayout->addWidget(browseButton);
    dataLayout->addWidget(graphButton);
    dataLayout->addWidget(aboutButton);

    mainLayout = new QVBoxLayout();
    mainLayout->addWidget(mechanics);
    mainLayout->addWidget(tableWidget);
    mainLayout->addLayout(dataLayout);
    setLayout(mainLayout);

    //---------------------Connections---------------------
    connect(graphButton, SIGNAL(clicked()), mechanics, SLOT(graph()));
    connect(browseButton, SIGNAL(clicked()), this, SLOT(browse()));
    connect(aboutButton, SIGNAL(clicked()), aboutBox, SLOT(exec()));
    connect(dSpinBox, SIGNAL(valueChanged(double)), mechanics, SLOT(setD(qreal)));
    connect(lSpinBox, SIGNAL(valueChanged(double)), mechanics, SLOT(setL(qreal)));
    connect(tableWidget, SIGNAL(cellChanged(int, int)), this, SLOT(prepareToGraph(int, int)));
    connect(this, SIGNAL(dataFromTable(int, int, qreal)), mechanics, SLOT(setDataToArray(int, int, qreal)));
    connect(mechanics, SIGNAL(nChanged(qreal)), this, SLOT(setN(qreal)));
    connect(mechanics, SIGNAL(err(int)), this, SLOT(error(int)));
}

//---------------------------------------------------------

UI::~UI()
{
    delete browseButton;
    delete aboutButton;

    delete tableWidget;

    delete nLabel;
    delete lLabel;
    delete dLabel;
    delete l2Label;
    delete d2Label;

    delete dSpinBox;
    delete lSpinBox;
    delete nLineEdit;

    delete dLayout;
    delete lLayout;
    delete nLayout;

    delete dataLayout;
    delete mainLayout;

    delete aboutBox;
    delete errorBox;
    delete mechanics;
}

//---------------------------------------------------------

void UI::prepareToGraph(int row, int column)
{
    bool ok;
    qreal data = tableWidget->item(row, column)->text().toDouble(&ok);
    if (ok)
        emit dataFromTable(row, column, data);
    else
        error(wrongData);
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

        switch(line[0])
        {
        case 'm':
            fileToTable(line, 0);
            break;

        case 'f':
            if(line[2] == '0')
                fileToTable(line, 1);
            if(line[2] == '1')
                fileToTable(line, 2);
            break;

        case 'd':
            fileToSpinBox(line, 0);
            break;

        case 'l':
            fileToSpinBox(line, 1);
            break;
        }

    }

}

//---------------------------------------------------------

void UI::fileToTable(QByteArray &line, int row)
{
    QString number = "";
    int column = 0;
    for(int i = 3; i <= line.size(); i++)
    {
        if((QChar(line[i]).isNumber()) || (line[i]) == '.')
            number += line[i];
        else
        {
            bool ok;
            number.toDouble(&ok);
            if (ok)
            {
                tableWidget->item(row, column)->setText(number);
                number.clear();
                column++;
            }

            if(column >= 14)
                break;
        }
    }
}

//---------------------------------------------------------

void UI::fileToSpinBox(QByteArray &line, int spinBox)
{
    QString number = "";
    for(int i = 3; i <= line.size(); i++)
    {
        if((QChar(line[i]).isNumber()) || (line[i]) == '.')
            number += line[i];
        else
        {
            bool ok;
            number.toDouble(&ok);
            if (ok)
            {
                if(spinBox == 0)
                    dSpinBox->setValue(number.toDouble());
                if(spinBox == 1)
                    lSpinBox->setValue(number.toDouble());
                number.clear();
            }
        }
    }
}

//---------------------------------------------------------

void UI::setN(qreal n)
{
    QString nString;
    nString.setNum(n);
    nLineEdit->setText(nString);
}

//---------------------------------------------------------

void UI::error(int code)
{
    switch(code)
    {
    case pointListIsEmpty:
        errorBox->setText(tr("Список точек пуст!"));
        break;
    case wrongData:
        errorBox->setText(tr("Ошибочные данные"));
        break;
    default:
        errorBox->setText(tr("Неизвестная ошибка"));
    }
    errorBox->exec();
}
