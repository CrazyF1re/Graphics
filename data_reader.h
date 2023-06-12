#ifndef DATA_READER_H
#define DATA_READER_H


#include <QFileInfo>



class IReader
{
public:
    virtual ~IReader(){}
    virtual QMap<QPair<QVariant,QVariant>,long int> read_data()=0;
    IReader(const QFileInfo& path):file(path){}
protected:
    QFileInfo file;
};

class sql_reader:public IReader
{
public:
    sql_reader(const QFileInfo& path):IReader(path){}
    QMap<QPair<QVariant,QVariant>,long int> read_data()
    {

    }

};
class json_reader:public IReader
{
public:
    json_reader(const QFileInfo& path):IReader(path){}
    QMap<QPair<QVariant,QVariant>,long int> read_data()
    {

    }

};

class csv_reader:public IReader
{
public:
    csv_reader(const QFileInfo& path):IReader(path){}
    QMap<QPair<QVariant,QVariant>,long int> read_data()
    {

    }

};



#endif // DATA_READER_H
