#include<iostream>
#include<fstream>
using namespace std;

struct scan_info
{
    string model;
    int price;
    double x_size;
    double y_size;
    int optr;
    int grey;

    friend std::ostream& operator<< (std::ostream& out, const scan_info& scaninfo);

};

ostream& operator<< (std::ostream& out, const scan_info& scaninfo)
{
    out << scaninfo.model << " " << scaninfo.price << " " << scaninfo.x_size << " " << scaninfo.y_size << " " << scaninfo.optr << " " << scaninfo.grey << endl;
    return out;
}

class ScanFile
{
private:
    string path;
    bool is_open;
    fstream fs;
public:  
    static int RecordsCount; //количество записей
    /*static void setRecordsCount(int count)
    {
        ScanFile::RecordsCount = count;
    } */
    ScanFile(string path_to_file)
    {
        //fstream fs;
        this->path = path_to_file;
        fs.open(path, fstream::in | fstream::out | fstream::ate | fstream::binary);
        if (!fs.is_open())
        {
            cout << "Ошибка: не удалось открыть файл!" << endl;
            this->is_open = false;
        }
        else
        {
            this->is_open = true;
        }
    }
    ~ScanFile()
    {
        fs.close();
    }
    void writeStruct(scan_info record)
    {
        if (this->is_open)
        {
            try
            {
                fs.seekg(0, ios::beg);
                RecordsCount++;
                fs << RecordsCount;
                fs.seekg(0, ios::end);
                fs << record;
            }
            catch (const std::exception& ex)
            {
                cout << "Что-то пошло не так, скорее всего произошла проблема при работе с файлом" << endl;
                cout << "Error: " << ex.what() << endl;
            }
        }
        
    }
    scan_info createStruct()
    {
        scan_info si;
        cin >> si.model >> si.price >> si.x_size >> si.y_size >> si.optr >> si.grey;
        return si;
    }
};

int ScanFile::RecordsCount = 0;

int main()
{
    setlocale(LC_ALL, "ru");
    string path = "mainfile";
    ScanFile mainfile(path);
    scan_info a = mainfile.createStruct();
    mainfile.writeStruct(a);
    return 0;
    /*Че надо сделать..?
    * 1) Допилить функции так, чтобы RecordsCount правильно отображала число сделанных записей в файле
    * 2) Реализовать функцию №2 из ТЗ
    */
}