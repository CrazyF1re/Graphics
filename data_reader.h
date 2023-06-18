#ifndef DATA_READER_H
#define DATA_READER_H


#include <QFileInfo>

#include <QSqlDatabase>
#include <QSqlQuery>

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QMessageBox>


struct unit
{
    QVariant key;
    QVariant value;

    bool operator==(const unit& p2) const
    {
        return key == p2.key && value == p2.value;
    }
};


class IReader:public QObject
{
    Q_OBJECT
public:
    virtual ~IReader(){}
    virtual QList<unit> read_data()=0;
    IReader(const QString& path):path(path)
    {
        connect(this,&IReader::error_message,this,&IReader::output_message);
    }
protected:
    QString path;
public slots:
    void output_message(QString message)
    {
        QMessageBox msgBox;
        msgBox.setText(message);
        msgBox.setStandardButtons(QMessageBox::Ok );
        msgBox.exec();
    }
signals:
   void error_message(QString message);
};

class sql_reader:public IReader
{





public:
    sql_reader(const QString& path):IReader(path)
    {
    }
    QList<unit> read_data()
    {
        QList<unit> result;// declare variable which will return

        QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");//create variable of database

        db.setDatabaseName(path);//set path of database

        if (!db.open()){//if database didnt opened  return empty result
            emit error_message("Database does not open");
            return result;
        }
        QSqlQuery query;//declare query through which we will get data

        if(db.tables().size()==0)//if database has no tables return empty result
        {
            emit error_message("Database has no tables");
            return result;
        }
        QString table_name = db.tables()[0];//get table name
        query.exec("select * from "+table_name);//make request to database to get data
        unit temp;
        while(query.next())// cycle into query
        {
            temp.key = query.value(0);//set values of key and value
            temp.value = query.value(1);
            result.append(temp);//append to result
        }
        db.close();//close database
        return result;
    }






};
class json_reader:public IReader
{
public:
    json_reader(const QString& path):IReader(path){}
    QList<unit> read_data()
    {

        QFile file(path);//declare QFile to open it and read
        QList<unit> result;// variable for data

        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {//error handler
            emit error_message("Failed to open file for reading");
            return result;
        }
        QByteArray content = file.readAll();//gets data into QByteArray
        file.close();//close file which we read

        QJsonDocument doc = QJsonDocument::fromJson(content);//declare json document and set up data into it

        if (doc.isNull()) {//error handler
            emit error_message("Failed to parse JSON data");
            return result;
        }

        QJsonArray jsonArray = doc.array();//gets array of json-type
        unit tmp;//temporary variable
        for (const QJsonValue& value : jsonArray)//cycle into json array for each element
        {
            if (value.isObject())//add unit if element is object only
            {
                QJsonObject obj = value.toObject();

                tmp.key = obj["key"].toVariant();
                tmp.value = obj["value"].toVariant();
                result.append(tmp);
            }
        }
        return result;
    }


};

class csv_reader:public IReader
{
public:
    csv_reader(const QString& path):IReader(path){}
    QList<unit> read_data()
    {
        QFile file(path);
        QList<unit> result;
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {//error handler
            emit error_message("Failed to open file for reading");
            return result;
        }
        if(file.size()==0)
        {
            emit error_message("File is empty");
            return result;
        }
        QTextStream in(&file);
        unit temp;
        while(!in.atEnd())
        {
            QStringList pair = in.readLine().split(",");

            if(pair.size()>=2)
            {
                temp.key = pair[0];
                temp.value = pair[1];


                result.append(temp);
            }
        }
        return result;
    }

};



#endif // DATA_READER_H
