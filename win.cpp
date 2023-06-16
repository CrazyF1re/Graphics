#include "win.h"


Win::Win(QWidget *parent) : QWidget(parent)
{
    setWindowIconText("Charts Viewer"); // set Name and minimal sizes of window
    setMinimumHeight(500);
    setMinimumWidth(800);


//creating widget for upper like menu
    top_bar = new QWidget(this); // cereate top_bar
    top_bar->setMaximumHeight(50); // set minimum height for top bar

    //layoyt for top bar
    QHBoxLayout* topLayout = new QHBoxLayout(top_bar);//create horizontal layout for all what we need into top bar

    //button
    browse = new QPushButton("Browse",this);// add browse button

    //combobox
    graphic_type = new QComboBox(top_bar);// add combobox for choose type of graphic
    graphic_type->addItem("First type");
    graphic_type->addItem("Second type");

    //checkbox
    black_white = new QCheckBox("Black&&white" , top_bar);// check box for colorful or black&white type of graphic


    //button
    print = new QPushButton("Save as PDF",top_bar);//button to save graphic into PDF



    // add created elements into layout
    topLayout->addWidget(browse);
    topLayout->addWidget(graphic_type);
    topLayout->addWidget(black_white);
    topLayout->addWidget(print);


//create splitter and two parts of splitting
    split = new QSplitter(this);
    list = new QListView(split);
    chart = new QChartView(split);

    //set up sizes of its
    list->setMinimumWidth(100);
    list->setMaximumWidth(400);
    chart->setMinimumWidth(600);


    //add widgets to splitter
    split->addWidget(list);
    split->addWidget(chart);;

    //Forbid splitter Collapse widgets, so now they will not dissapear
    split->setChildrenCollapsible(false);


    //Create vertical layout contains top bar and splitter
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(top_bar);
    layout->addWidget(split);



    //set up QFileSystemModel and listView
    model = new MVC(this);
    model->setRootPath(QDir::currentPath());
    connect(browse, &QPushButton::clicked,this,&Win::clicked_browse);//connect button with slot
    connect(list, SIGNAL(clicked(QModelIndex)), this, SLOT(clicked_file(QModelIndex)));
    //connect(list, &list->clicked(QModelIndex),this,&Win::clicked_file(QModelIndex));//connect list when file choosen with slot
}





Win::~Win()
{

}

void Win::clicked_file(const QModelIndex& index)
{

    QString file_path = model->filePath(index);
    //далее выбрать стратегию с помощью которой будет прочитан файл и записан в переменную

    QFileInfo file(file_path);
    if(file.suffix() == "sqlite")
    {
        qDebug()<<"Strategy for sqlite";
        reader = new sql_reader(file.absoluteFilePath());

    }
    else if (file.suffix()== "json")
    {
        qDebug()<<"Strategy for json";
        reader = new json_reader(file.absoluteFilePath());
    }
    else if (file.suffix() == "csv")
    {
        qDebug()<<"Strategy for csv";
        reader = new csv_reader(file.absoluteFilePath());
    }

    data = reader->read_data();//записываем данные в data

    for( unit& pair:data)
    {

        qDebug()<<"Key: "<<pair.key.toString()<<"Value: "<<pair.value.toString();
    }



}

void Win::clicked_browse()
{
    //put into qstring path of choosen folder
    QString folderName = QFileDialog::getExistingDirectory(this, "Select folder");

    if (!folderName.isEmpty()) {//if its not empty and such dirrectory is exists then show files into it
        QDir dir(folderName);
        if(dir.exists())
        {
            model->setRootPath(folderName);//set path into our model

            list->setModel(model);//set our model into listView
            list->setRootIndex(model->index(folderName)); // set index to root folder



        }
    }
}

