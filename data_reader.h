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
    sql_reader(const QFileInfo& path):IReader(path)
    {

    }
    QList<unit> read_data()
    {
        QList<unit> result;
        QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName(file.absoluteFilePath());
        if (!db.open()){//if database didnt opened  return empty result
            return result;
        }
        QSqlQuery query;

        if(db.tables().size()==0)//if database has no tables return empty result
        {
            return result;
        }
        QString table_name = db.tables()[0];;
        query.exec("select * from "+table_name);
        while(query.next())
        {
            unit temp;
            temp.key = query.value(0);
            temp.value = query.value(1);
            result.append(temp);
        }
        db.close();
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
