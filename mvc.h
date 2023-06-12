#ifndef MVC_H
#define MVC_H
#include <QFileSystemModel>
#include <QPushButton>

class MVC:public QFileSystemModel
{
public:
    MVC(QObject* parent):QFileSystemModel(parent)
    {
        setFilter(QDir::Files);//set filter to show only files without folders etc.
        setNameFilters(QStringList()<<"*.csv"<<"*.sqlite"<<"*.json");//add filters to files we want to see
        setNameFilterDisables(false);//set  FilterDisables parametr as false. Need to work filters
    }

};

#endif // MVC_H
