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



#include <QChartView>


#include <QFileSystemModel>
#include <QDir>
#include <QFileDialog>
#include <QStandardItemModel>
#include "mvc.h"




class Win : public QWidget
{
    Q_OBJECT
    QPushButton* browse;
    QComboBox* graphic_type;
    QCheckBox* black_white;
    QPushButton* print;
    QSplitter* split;


    QChartView* chart;//pass insted of graphic (charts)


    QWidget* top_bar;// pannel with bittons



    QListView* list;//list will show files into folder
    MVC* model;



public:
    Win(QWidget *parent = nullptr);
    ~Win();

private slots:
    clicked_browse();
};
#endif // WIDGET_H
