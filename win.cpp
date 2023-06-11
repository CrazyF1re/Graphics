#include "win.h"



Win::Win(QWidget *parent) : QWidget(parent)
{
    setWindowIconText("Charts Viewer"); // set Name and minimal sizes of window
    setMinimumHeight(500);
    setMinimumWidth(800);

    top_bar = new QWidget(this);

    QHBoxLayout* topLayout = new QHBoxLayout(top_bar);
    top_bar->setMaximumHeight(50);


    split = new QSplitter(this);
    list = new QListView(split);
    text = new QTextEdit(split);
    list->setMinimumWidth(200);
    list->setMaximumWidth(400);
    text->setMinimumWidth(600);


    split->addWidget(list);
    split->addWidget(text);;
    split->setChildrenCollapsible(false);






    browse = new QPushButton("Browse",this);//add button for next culculation
    graphic_type = new QComboBox(top_bar);
    black_white = new QCheckBox("Black&white" , top_bar);
    print = new QPushButton("Save as PDF",top_bar);
    graphic_type->addItem("First type");
    graphic_type->addItem("Second type");
    topLayout->addWidget(browse);
    topLayout->addWidget(graphic_type);
    topLayout->addWidget(black_white);
    topLayout->addWidget(print);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(top_bar);
    layout->addWidget(split);
}





Win::~Win()
{

}

