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

#include "mvc.h"
#include <QVariant>
#include "data_reader.h"

#include "drawer.h"

#include "ioccontainer.h"

#include <QGraphicsColorizeEffect>

#include <QPrinter>
#include <QSystemTrayIcon>


class Win : public QWidget
{
    Q_OBJECT
    std::unique_ptr<QPushButton> browse;
    std::unique_ptr<QComboBox> graphic_type;
    std::unique_ptr<QCheckBox> black_white;
    std::unique_ptr<QPushButton> print;
    std::unique_ptr<QSplitter> split;


    std::unique_ptr<QChartView> chart;// variable to create graphic


    std::unique_ptr<QWidget> top_bar;// pannel with bittons

    std::unique_ptr<QHBoxLayout> topLayout;

    std::unique_ptr<QListView> list;//list will show files into folder
    std::unique_ptr<MVC> model;

    //should use another ways of store data,but use this because of lack of time.
    QList<unit>  data;//variable to save data we read from chosen file

    std::unique_ptr<IReader> reader;

    IOCContainer injector;


public:
    Win(QWidget *parent = nullptr);
    ~Win();

private slots:
    void clicked_file(const QModelIndex& index);
    void clicked_browse();
    void clicked_checkbox(int state);
    void comboBoxselected();
    void save_pdf();

};
#endif // WIDGET_H
