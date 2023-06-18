#include "win.h"

int IOCContainer::s_nextTypeId = 1;

Win::Win(QWidget *parent) : QWidget(parent)
{
    setWindowIconText("Charts Viewer"); // set Name and minimal sizes of window
    setMinimumHeight(500);
    setMinimumWidth(800);


//creating widget for upper like menu
    top_bar = std::make_unique<QWidget>(this); // cereate top_bar
    top_bar->setMaximumHeight(50); // set minimum height for top bar

    //layoyt for top bar
    topLayout = std::make_unique<QHBoxLayout>(top_bar.get());//create horizontal layout for all what we need into top bar

    //button
    browse = std::make_unique<QPushButton>("Browse",this);// add browse button

    //combobox
    graphic_type = std::make_unique<QComboBox>(top_bar.get());// add combobox for choose type of graphic
    graphic_type->setPlaceholderText("Select type");
    graphic_type->addItem("Круговая диаграмма");
    graphic_type->addItem("Столбчатая диаграмма");
    graphic_type->addItem("Линейная диаграмма");

    //checkbox
    black_white = std::make_unique<QCheckBox>("Black&&white" , top_bar.get());// check box for colorful or black&white type of graphic


    //button
    print = std::make_unique<QPushButton>("Save as PDF",top_bar.get());//button to save graphic into PDF
    print.get()->setEnabled(false);


    // add created elements into layout
    topLayout->addWidget(browse.get());
    topLayout->addWidget(graphic_type.get());
    topLayout->addWidget(black_white.get());
    topLayout->addWidget(print.get());


//create splitter and two parts of splitting
    split = std::make_unique<QSplitter>(this);
    list = std::make_unique<QListView>(split.get());
    chart = std::make_unique<QChartView>(split.get());

    //set up sizes of its
    list->setMinimumWidth(100);
    list->setMaximumWidth(400);
    chart->setMinimumWidth(600);
    chart->chart()->setBackgroundBrush(QBrush(Qt::white));


    //add widgets to splitter
    split->addWidget(list.get());
    split->addWidget(chart.get());;

    //Forbid splitter Collapse widgets, so now they will not dissapear
    split->setChildrenCollapsible(false);


    //Create vertical layout contains top bar and splitter
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(top_bar.get());
    layout->addWidget(split.get());



    //set up QFileSystemModel and listView
    model = std::make_unique<MVC>(this);
    model->setRootPath(QDir::currentPath());


    connect(browse.get(), &QPushButton::clicked,this,&Win::clicked_browse);//connect button with slot
    connect(list.get(), SIGNAL(clicked(QModelIndex)), this, SLOT(clicked_file(QModelIndex)));
    connect(graphic_type.get(),&QComboBox::activated,this,&Win::comboBoxselected);
    connect(black_white.get(),&QCheckBox::stateChanged,this,&Win::clicked_checkbox);
    connect(print.get(),&QPushButton::clicked,this,&Win::save_pdf);

}

void Win::clicked_file(const QModelIndex& index)
{
    QString file_path = model->filePath(index);
    //далее выбрать стратегию с помощью которой будет прочитан файл и записан в переменную

    QFileInfo file(file_path);
    if(file.suffix() == "sqlite")
    {
        reader = std::make_unique<sql_reader>(file.absoluteFilePath());
    }
    else if (file.suffix()== "json")
    {
        reader = std::make_unique<json_reader>(file.absoluteFilePath());
    }
    else if (file.suffix() == "csv")
    {
        reader = std::make_unique<csv_reader>(file.absoluteFilePath());
    }
    data.clear();
    data = reader.get()->read_data();//add data into data

    int emptyIndex = graphic_type->findText(graphic_type->placeholderText());//find index of "Select type"
    graphic_type->setCurrentIndex(emptyIndex);//set up current index of combobox in found index
}

void Win::clicked_browse()
{
    //put into qstring path of choosen folder
    QString folderName = QFileDialog::getExistingDirectory(this, "Select folder");

    int emptyIndex = graphic_type->findText(graphic_type->placeholderText());//find index of "Select type"
    graphic_type->setCurrentIndex(emptyIndex);//set up current index of combobox in found index

    if (!folderName.isEmpty()) {//if its not empty and such dirrectory is exists then show files into it
        QDir dir(folderName);
        if(dir.exists())
        {
            model->setRootPath(folderName);//set path into our model

            list->setModel(model.get());//set our model into listView
            list->setRootIndex(model->index(folderName)); // set index to root folder
            print.get()->setEnabled(false);
        }
    }

}

void Win::clicked_checkbox(int state)
{
    if(state==2)
    {
        QGraphicsColorizeEffect* tmp = new QGraphicsColorizeEffect();
        tmp->setColor(Qt::black);
        chart->chart()->setGraphicsEffect(tmp);
    }
    else
    {
        chart->chart()->setGraphicsEffect(0);
    }

}

void Win::comboBoxselected()
{
    if(data.size()!=0)
    {
        if(graphic_type->currentText()=="Круговая диаграмма")
        {
            injector.RegisterInstance<IDrawer,CircleDrawer>();
            injector.GetObject<IDrawer>()->draw(data,chart.get());


        }
        else if (graphic_type->currentText()=="Столбчатая диаграмма")
        {
            injector.RegisterInstance<IDrawer,BarDrawer>();
            injector.GetObject<IDrawer>()->draw(data,chart.get());


        }
        else if (graphic_type->currentText()=="Линейная диаграмма")
        {
            injector.RegisterInstance<IDrawer,LineDrawer>();
            injector.GetObject<IDrawer>()->draw(data,chart.get());

        }
        print.get()->setEnabled(true);
    }
}

void Win::save_pdf()
{
    // Создаем объект QPrinter для печати и сохранения изображения в PDF формате
    QPrinter printer;
    printer.setOutputFormat(QPrinter::PdfFormat);
    QString fileName = model.get()->fileName(list.get()->currentIndex()).split(".")[0];
    printer.setOutputFileName(fileName+" "+graphic_type.get()->currentText()+".pdf");


    printer.setFullPage(true);

    // Рисуем график на принтере
    QPainter painter(&printer);
    chart->render(&painter);
    painter.end();
}

