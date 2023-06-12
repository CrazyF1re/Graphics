#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QLabel>
#include <QComboBox>
#include <QCheckBox>
#include <QPushButton>
#include <QSplitter>
#include <QChartView>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QBoxLayout>
#include <QListView>
#include <QMap>


#include <QChartView>


#include <QFileSystemModel>
#include <QDir>
#include <QFileDialog>
#include <QStandardItemModel>
#include "mvc.h"
#include <QVariant>
#include "data_reader.h"



class Win : public QWidget
{
    Q_OBJECT
    QPushButton* browse;
    QComboBox* graphic_type;
    QCheckBox* black_white;
    QPushButton* print;
    QSplitter* split;


    QChartView* chart;// variable to create graphic


    QWidget* top_bar;// pannel with bittons



    QListView* list;//list will show files into folder
    MVC* model;

    //should use another ways of store data,but use this because of lack of time.
    QList<unit>  data;//variable to save data we read from chosen file

    IReader* reader;


public:
    Win(QWidget *parent = nullptr);
    ~Win();

private slots:
    void clicked_file(const QModelIndex& index);
    void clicked_browse();
};
#endif // WIDGET_H
