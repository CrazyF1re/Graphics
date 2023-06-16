#ifndef DATA_READER_H
#define DATA_READER_H


#include <QFileInfo>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>

struct unit
{
    QVariant key;
    QVariant value;
    long int freq=0;
    bool operator==(const unit& p2) const
    {
        return key == p2.key && value == p2.value;
    }
};


class IReader
{
public:
    virtual ~IReader(){}
    virtual QList<unit> read_data()=0;
    IReader(const QFileInfo& path):file(path){}
protected:
    QFileInfo file;
};

class sql_reader:public IReader
{





public:

    QSqlDatabase db;
    sql_reader(const QFileInfo& path):IReader(path)
    {
        db = QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName(file.absoluteFilePath());
    }
    QList<unit> read_data()
    {
        QList<unit> result;


        if (!db.open()){
            qDebug()<<"Failed";
            return result;
        }
        QSqlQuery query;
        QString table_name = db.tables()[0];
        query.exec("select * from "+table_name);
        while(query.next())
        {
            unit temp;
            temp.key = query.value(0).toString();
            temp.value = query.value(1).toString();
            temp.freq = 1;
            result.append(temp);

            //something wrong, works too slow

//            long int index = result.indexOf(temp);
//            if (index != -1){
//                result[index].freq++;

//            }
//            else
//            {
//                result.append(temp);
//            }
        }
        query.finish();
        db.close();
        query.clear();
        return result;
    }

};
class json_reader:public IReader
{
public:
    json_reader(const QFileInfo& path):IReader(path){}
    QList<unit> read_data()
    {

    }

};

class csv_reader:public IReader
{
public:
    csv_reader(const QFileInfo& path):IReader(path){}
    QList<unit> read_data()
    {

    }

};



#endif // DATA_READER_H
